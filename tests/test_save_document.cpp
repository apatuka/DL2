// Active checks even with NDEBUG. Synthetic coverage for branches empty in GOG saves.
#include "game/save_document.h"
#include "game/globals.h"
#include "game/queue_pool.h"
#include "game/rtl_compat.h"

#include <algorithm>
#include <cstring>
#include <iostream>
#include <memory>
#include <stdexcept>

namespace {
using namespace dl2;
using save::Document;

void require(bool value, const char* message) {
    if (!value) throw std::runtime_error(message);
}

std::unique_ptr<Document> fixture() {
    auto d = std::make_unique<Document>();
    std::memcpy(d->header.text, save::kHeaderText, sizeof(save::kHeaderText));
    d->header.version = kSaveVersion;
    d->header.minusOne = -1;
    d->header.pad[51] = 0xa5;
    d->options.turn = 17;
    d->options.numPlayers = 2;
    d->options.playersMask = 3;
    d->options.hasWon[1] = 1;
    d->options.campaignBytes[1] = 0x51;
    d->world.width = 2;
    d->world.height = 1;
    d->world.numTerritories = 1;
    d->world.rngSeed = 123;
    for (int p = 0; p < kMaxPlayers; ++p) {
        d->players[p].index = uint8_t(p);
        d->players[p].race = int8_t(p);
        d->players[p].credits = p * 100 + 123;
        d->ministerJobs[p].resize(1);
        d->ministerJobs[p][0].type = 1;
    }
    d->players[0].type = 1;
    d->players[1].type = 3;
    std::memcpy(d->players[0].name, "Original Name", 14);
    d->localList = {7, 42};
    d->ministerJobs[0].resize(4);
    for (size_t i = 0; i < 4; ++i) {
        auto& node = d->ministerJobs[0][i];
        node.type = i ? 2 : 1;
        node.next.raw = i < 3 ? uint32_t(0xdead0000 + i * 0x44) : 0;
        node.prev.raw = i ? uint32_t(0xbeef0000 + i * 0x44) : 0;
        node.priority = int(i * 9);
    }
    d->events.resize(2);
    d->options.eventCount = 2;
    d->events[0].record = {12, 4, 0, 99};
    d->events[0].text = {'a', 0, 'b', 0xff};
    d->events[1].record = {20, 0, -1, 123};
    d->tiles.resize(2);
    for (int x = 0; x < 2; ++x) {
        d->tiles[x].x = uint8_t(x);
        d->tiles[x].territory = 1;
        d->tiles[x].terrain = 1;
    }
    d->territories.resize(1);
    auto& t = d->territories[0];
    t.data.index = 1;
    t.data.owner = 0;
    t.data.terrain = 1;
    t.data.numTiles = 2;
    t.data.tiles[0].raw = 0; // (0,0) is a valid file coordinate, not a null handle.
    t.data.tiles[1].raw = 1;
    t.data.materials[1] = 256;
    t.data.flags = 0x1234;
    t.data.sites[0].building.raw = 8192;
    t.data.armies.raw = 8193;
    t.data.queues[0].raw = 0xfeed1234; // Historical token is retained, never dereferenced.
    t.queues[0].resize(2);
    t.queues[0][0].unitType = 1;
    t.queues[0][0].count = 9;
    t.queues[0][0].data[10] = -27;
    t.queues[0][1].unitType = 2;
    t.queues[0][1].count = 3;
    d->buildings.resize(1);
    auto& b = d->buildings[0];
    b.id = 8192; b.type = 1; b.territory = 1; b.site = 0;
    d->armies.resize(1);
    auto& a = d->armies[0];
    a.id = 8193; a.type = 1; a.owner = 0; a.health = 100;
    a.territory.raw = a.dest.raw = a.origin.raw = 1;
    d->jobs[0][0].destination.raw = 1;
    d->jobs[0][0].armyIds[0] = 8193;
    d->jobs[0][0].armies[0].raw = 0x00645370; // Original runtime word, resolved through armyIds.
    d->scratchJob1.destination.raw = 0x005a43d0; // Scratch fields are opaque in the file.
    d->raceStats.v[63][6] = -19;
    d->techs[47].progress[6] = 543;
    d->continents[31].bonus = 7;
    d->randomEvents[24].turnsLeft = 33;
    d->scores[6].score = 6789;
    d->spies[6][24].turns = 31;
    d->blackMarket[6].turn = 44;
    d->trailing = {0xde, 0xad, 0, 0xff};
    return d;
}

std::vector<uint8_t> encoded(const Document& document) {
    std::vector<uint8_t> bytes;
    save::Error error;
    if (!save::encode(document, bytes, error)) throw std::runtime_error("encode: " + error.message);
    return bytes;
}

void roundtripAndEdit() {
    auto d = fixture();
    const auto original = encoded(*d);
    auto result = std::make_unique<Document>();
    save::Error error;
    require(save::decode(original, *result, error), "decode synthetic save");
    require(error.code == save::ErrorCode::None, "success must clear error");
    require(encoded(*result) == original, "synthetic roundtrip must preserve every byte");
    require(result->localList == d->localList, "local values survive");
    require(result->ministerJobs[0].size() == 4 && result->ministerJobs[0][3].priority == 27, "minister nodes survive");
    require(result->events[0].text == d->events[0].text, "binary event text survives including NUL");
    require(result->territories[0].queues[0][0].data[10] == -27, "queue data survives");
    require(result->raceStats.v[63][6] == -19 && result->techs[47].progress[6] == 543, "race/tech survive");
    require(result->scores[6].score == 6789 && result->spies[6][24].turns == 31 && result->blackMarket[6].turn == 44,
            "final blocks survive");
    require(result->buildingById(8192) == &result->buildings[0] && !result->buildingById(999), "building resolver");
    require(result->armyById(8193) == &result->armies[0] && !result->armyById(0), "army resolver");
    require(result->territoryByIndex(1) == &result->territories[0] && !result->territoryByIndex(0), "territory resolver");
    require(result->tileAt(0, 0) == &result->tiles[0] && !result->tileAt(2, 0), "tile resolver");

    result->players[0].credits = -12345;
    result->territories[0].data.materials[1] = 999;
    result->territories[0].queues[0][0].count = 77;
    result->events[0].text[2] = 'z';
    result->ministerJobs[0][2].priority = 90;
    const auto edited = encoded(*result);
    require(edited != original, "writer must serialize edited fields, not replay original bytes");
    auto reread = std::make_unique<Document>();
    require(save::decode(edited, *reread, error), "decode edited save");
    require(reread->players[0].credits == -12345 && reread->territories[0].data.materials[1] == 999,
            "edits persist to typed state");
    require(reread->territories[0].queues[0][0].count == 77 && reread->events[0].text[2] == 'z' &&
            reread->ministerJobs[0][2].priority == 90, "dynamic edits persist");
}

void failuresAreTransactional() {
    auto d = fixture();
    const auto bytes = encoded(*d);
    save::Error error;
    auto target = fixture();
    target->options.turn = 90210;
    const auto before = encoded(*target);
    auto reject = [&](const std::vector<uint8_t>& bad) {
        require(!save::decode(bad, *target, error), "invalid save was accepted");
        require(error.code != save::ErrorCode::None && !error.message.empty(), "missing diagnostic");
        require(encoded(*target) == before, "failed decode changed destination");
    };
    // The trailing bytes are legitimately optional, so only truncate within real blocks.
    const size_t body = bytes.size() - d->trailing.size();
    for (size_t cut = 0; cut < body; cut += std::max<size_t>(1, body / 128))
        reject({bytes.begin(), bytes.begin() + cut});
    for (size_t cut : {size_t(87), size_t(155), size_t(327), body - 1})
        reject({bytes.begin(), bytes.begin() + cut});
    auto mutate32 = [&](size_t offset, uint32_t value) {
        auto bad = bytes;
        std::memcpy(bad.data() + offset, &value, sizeof(value));
        reject(bad);
    };
    mutate32(88, kSaveVersion + 1);
    mutate32(88, 34);
    mutate32(92, 2);
    mutate32(sizeof(SaveHeader) + offsetof(GameOptions, numPlayers), 8);
    mutate32(sizeof(SaveHeader) + offsetof(GameOptions, localPlayer), 7);
    mutate32(sizeof(SaveHeader) + offsetof(GameOptions, eventCount), 51);
    auto bad = bytes; bad[0] = '!'; reject(bad);
    bad = bytes; bad[sizeof(SaveHeader) + sizeof(GameOptions) + offsetof(WorldParams, width)] = 41; reject(bad);
    size_t eventOffset = sizeof(SaveHeader) + sizeof(GameOptions) + sizeof(WorldParams) + sizeof(Player) * kMaxPlayers +
                         (d->localList.size() + 1) * 4 + sizeof(RaceStats) + sizeof(TechSaved) * kNumTechs;
    for (const auto& list : d->ministerJobs) eventOffset += list.size() * sizeof(MinisterJob);
    bad = bytes; bad[eventOffset + 2] = bad[eventOffset + 3] = 0xff; reject(bad);
    const size_t buildingCountOffset = eventOffset + sizeof(EventSaved) * 2 + 4 + sizeof(Tile) * 2;
    mutate32(buildingCountOffset, 1201);
    mutate32(buildingCountOffset + 4 + sizeof(Building), 561);
    const size_t territoryOffset = buildingCountOffset + 4 + sizeof(Building) + 4 + sizeof(Army);
    bad = bytes; bad[territoryOffset + offsetof(Territory, numTiles)] = 49; reject(bad);
    mutate32(territoryOffset + offsetof(Territory, sites) + offsetof(BuildingSite, building), 99999);

    auto invalid = fixture();
    std::vector<uint8_t> output = {11, 22, 33};
    invalid->territories[0].queues[0].resize(256);
    require(!save::encode(*invalid, output, error) && output == std::vector<uint8_t>({11, 22, 33}),
            "invalid encode must preserve destination");
    invalid = fixture(); invalid->localList.push_back(0xffffffffu);
    require(!save::validate(*invalid, error), "local sentinel cannot be a value");
    invalid = fixture(); invalid->ministerJobs[0].back().next.raw = 1;
    require(!save::validate(*invalid, error), "minister termination must match stored list");
    invalid = fixture(); invalid->armies[0].next.raw = invalid->armies[0].id;
    require(!save::validate(*invalid, error), "army cycle must be rejected");
    invalid = fixture(); invalid->events[0].text.resize(1024); invalid->events[0].record.textLen = 1024;
    require(!save::validate(*invalid, error), "oversized event text");
    std::vector<uint8_t> oversized(save::kMaxFileBytes + 1);
    reject(oversized);
}

void limitsVersionsAndMap() {
    auto d = fixture();
    save::Error error;
    d->territories[0].queues[0].resize(255, d->territories[0].queues[0][0]);
    d->events[0].text.resize(1023, 'x'); d->events[0].record.textLen = 1023;
    d->ministerJobs[1].resize(save::kMaxListNodes);
    for (size_t i = 0; i < d->ministerJobs[1].size(); ++i) {
        d->ministerJobs[1][i].type = i ? 2 : 1;
        d->ministerJobs[1][i].next.raw = i + 1 < d->ministerJobs[1].size() ? 1u : 0u;
    }
    auto bytes = encoded(*d);
    auto reread = std::make_unique<Document>();
    require(save::decode(bytes, *reread, error) && encoded(*reread) == bytes, "maximum lists/queue/text roundtrip");
    d = fixture();
    // Version35 physically lacks spies/black market. Other fields remain unchanged.
    d->header.version = 35;
    require(!save::validate(*d, error), "downgrade must not silently discard populated newer blocks");
    d->spies = {}; d->blackMarket = {};
    bytes = encoded(*d);
    require(save::decode(bytes, *reread, error) && encoded(*reread) == bytes, "version35 roundtrip");
    require(reread->raceStats.v[63][6] == -19, "version35 includes all 64 race rows");
    d->header.version = 36;
    require(encoded(*d).size() == bytes.size() + 0x578 + 0x38, "version36 adds spies and black market");

    auto map = std::make_unique<Document>();
    std::memcpy(map->header.text, save::kHeaderText, sizeof(save::kHeaderText));
    map->header.version = kSaveVersion; map->header.isMap = 1; map->header.minusOne = -1;
    map->world = d->world; map->tiles = d->tiles; map->mapTerritories.resize(1);
    map->mapTerritories[0].terrain = 1;
    map->mapTerritories[0].sites[0] = {1, 4, 0xee};
    map->trailing = {123};
    bytes = encoded(*map);
    require(save::decode(bytes, *reread, error) && encoded(*reread) == bytes, "map byte-exact roundtrip");
    require(reread->mapTerritories[0].sites[0].pad == 0xee, "map padding retained");
}

void linksAndMutations() {
    auto d = fixture();
    Building second{};
    second.id = 8194; second.type = 1; second.territory = 1; second.site = 1;
    second.prev.raw = 8192;
    d->buildings.push_back(second);
    d->buildings[0].next.raw = 8194;
    d->territories[0].data.sites[1].building.raw = 8194;
    // +0x116 is unrelated opaque data, not Building::prev (+0x11a).
    const uint32_t opaque = 0xffed00fdu;
    std::memcpy(reinterpret_cast<uint8_t*>(&d->buildings[0]) + 0x116, &opaque, 4);
    const auto bytes = encoded(*d);
    save::Error error;
    auto target = std::make_unique<Document>();
    require(save::decode(bytes, *target, error), "linked building fixture");
    require(target->buildings[1].prev.raw == 8192 && target->buildings[0].next.raw == 8194,
            "building list IDs must use correct offsets");
    require(encoded(*target) == bytes, "opaque building bytes retained");
    d->buildings[1].prev.raw = 65000;
    require(!save::validate(*d, error), "unknown previous building ID rejected");
    d->buildings[1].prev.raw = 8192;
    d->buildings[1].id = 8192;
    require(!save::validate(*d, error), "duplicate building ID rejected");
    // Deterministic mutation smoke check: accepted inputs must still roundtrip
    // losslessly; rejected ones must not change the previous document.
    uint32_t random = 0x13579bdf;
    for (int trial = 0; trial < 256; ++trial) {
        auto mutated = bytes;
        random = random * 1664525u + 1013904223u;
        const size_t position = random % mutated.size();
        mutated[position] ^= uint8_t(1u << ((random >> 24) & 7));
        const auto prior = encoded(*target);
        if (save::decode(mutated, *target, error))
            require(encoded(*target) == mutated, "accepted mutation failed lossless encoding");
        else
            require(encoded(*target) == prior, "mutation failure changed prior document");
    }
    const char oldHeader[] = "Deadlock 2  (c)1997 Accolade Inc.  All Rights Reserved.\nPre-release version S (7/21/97)";
    auto old = bytes;
    std::fill_n(old.begin(), 88, uint8_t(0));
    std::memcpy(old.data(), oldHeader, sizeof(oldHeader));
    require(!save::decode(old, *target, error) && error.code == save::ErrorCode::UnsupportedVersion,
            "old generation should fail explicitly as unsupported");
}

void noGlobalSideEffects() {
    gs.options.turn = 314159;
    gg.localPlayer = 6; gg.gameStarted = 123;
    rtl::srand(123456);
    const auto seed = rtl::seed();
    const auto handle = QueueAlloc();
    const auto address = ptr(handle);
    auto d = fixture();
    auto bytes = encoded(*d);
    save::Error error;
    require(save::decode(bytes, *d, error), "decode in presence of active globals");
    require(gs.options.turn == 314159 && gg.localPlayer == 6 && gg.gameStarted == 123 && rtl::seed() == seed,
            "codec must not activate or modify game state/RNG");
    require(ptr(handle) == address, "codec must not reset global queue pools");
    QueueFree(handle, 1);
}
} // namespace

int main() {
    try {
        roundtripAndEdit();
        failuresAreTransactional();
        limitsVersionsAndMap();
        linksAndMutations();
        noGlobalSideEffects();
        std::cout << "save document: roundtrip, edits, binary events, lists, bounds, versions, map and transaction checks passed\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "save document failure: " << error.what() << '\n';
        return 1;
    }
}
