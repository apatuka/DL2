// Independent small-map oracles from 004423b4 / 00486964 / 0047dd24.
// These are derived from original code, not original-game execution results.
#include "game/load_derived.h"
#include "game/data_tables.h"
#include "game/save_files.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include "formats/hdx_archive.h"
#include <cstring>
#include <filesystem>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
using namespace dl2;
using simulation::LoadDerivedReport;
using simulation::LoadDerivedScope;
void require(bool condition, const char* message) {
    if (!condition) throw std::runtime_error(message);
}
uint32_t word(const uint8_t* bytes) {
    uint32_t value;
    std::memcpy(&value, bytes, 4);
    return value;
}
void word(uint8_t* bytes, uint32_t value) { std::memcpy(bytes, &value, 4); }

std::unique_ptr<save::Document> fixture(int count = 3) {
    auto d = std::make_unique<save::Document>();
    std::memcpy(d->header.text, save::kHeaderText, sizeof(save::kHeaderText));
    d->header.version = kSaveVersion;
    d->options.numPlayers = 3; d->options.localPlayer = 0;
    d->options.turn = 71; d->options.nextGlobalId = 234;
    d->options.gameSeed = 0x87654321; d->options.gameId = 321;
    d->world.width = uint8_t(count); d->world.height = 1;
    d->world.numTerritories = uint16_t(count); d->world.rngSeed = 0x12345678;
    for (size_t p = 0; p < kMaxPlayers; ++p) {
        d->players[p].index = uint8_t(p); d->players[p].race = uint8_t(p);
        d->players[p].type = p < 3 ? 1 : 0; d->ministerJobs[p].resize(1);
    }
    d->territories.resize(size_t(count)); d->tiles.resize(size_t(count));
    d->buildings.reserve(30);
    for (int i = 0; i < count; ++i) {
        auto& t = d->territories[size_t(i)].data;
        t.index = uint16_t(i + 1); t.owner = -1; t.terrain = 1; t.continent = int8_t(i);
        t.population = 500; t.morale = 75; t.numTiles = 1; t.centerTile = 0;
        t.tiles[0].raw = uint32_t(i); t.knowledge = 97;
        for (int s = 0; s < 36; ++s) {
            t.sites[s].unk_00 = uint16_t((s % 6) | ((s / 6) << 8));
            t.sites[s].terrainFlags = 1;
        }
        auto& tile = d->tiles[size_t(i)];
        tile.x = uint8_t(i); tile.territory = int16_t(i + 1);
        tile.terrain = 3; tile.overlay = 0xab; tile.pathCost = int16_t(100 + i);
    }
    return d;
}
void adjacent(save::Document& d, uint32_t a, uint32_t b) {
    d.territories[a - 1].data.adjacency[b >> 4] |= uint16_t(1u << (b & 15));
    d.territories[b - 1].data.adjacency[a >> 4] |= uint16_t(1u << (a & 15));
}
Building& building(save::Document& d, int territoryIndex, int site, int type) {
    Building b{};
    b.id = uint16_t(100 + d.buildings.size()); b.type = uint8_t(type);
    b.category = data::kBuildingTypes[type].category;
    b.site = int8_t(site); b.territory = int16_t(territoryIndex);
    d.territories[size_t(territoryIndex - 1)].data.sites[size_t(site)].building.raw = b.id;
    d.buildings.push_back(b);
    return d.buildings.back();
}
std::vector<uint8_t> snapshot(const save::Document& d) {
    std::vector<uint8_t> bytes;
    save::Error error;
    if (!save::encode(d, bytes, error)) throw std::runtime_error("fixture encoding: " + error.message);
    for (const auto& t : d.territories) {
        const auto* p = reinterpret_cast<const uint8_t*>(&t.data);
        bytes.insert(bytes.end(), p + kTerritorySavedBytes, p + sizeof(Territory));
        for (const auto& q : t.queues) for (const auto& node : q) {
            const auto* next = reinterpret_cast<const uint8_t*>(&node.next);
            bytes.insert(bytes.end(), next, next + sizeof(node.next));
        }
    }
    return bytes;
}
std::unique_ptr<save::Document> derive(const save::Document& d, LoadDerivedReport& report) {
    const auto before = snapshot(d);
    auto result = fixture();
    save::Error error{save::ErrorCode::Io, 44, "previous"};
    if (!simulation::rebuildLoadDerived(d, *result, report, error)) throw std::runtime_error(error.message);
    require(error.code == save::ErrorCode::None && error.offset == 0 && error.message.empty(), "success clears prior error");
    require(snapshot(d) == before, "derived reconstruction does not mutate source");
    require(report.continentsRebuilt && report.roadsRebuilt && report.shrineCountsRebuilt &&
            !report.visibilityRebuilt && !report.contactsRebuilt, "scope is explicitly partial, never full activation");
    return result;
}

void continentOracles() {
    auto d = fixture();
    adjacent(*d, 1, 2); adjacent(*d, 2, 3);
    for (auto& c : d->continents) std::memset(&c, 0xa5, sizeof(c));
    d->territories[1].data.terrain = 3;
    d->territories[2].data.terrain = 5;
    LoadDerivedReport report;
    auto result = derive(*d, report);
    require(result->continents[0].hasLand == 1 && result->continents[0].terrainMask == 8 &&
            result->continents[1].terrainMask == 1 && result->continents[2].terrainMask == 0x16,
            "original terrain flags include wasteland 0x16, not a synthesized bit5");
    require(result->continents[0].adjContinents == 2 && result->continents[1].adjContinents == 5 &&
            result->continents[2].adjContinents == 2, "continent chain first-hop masks");
    require(word(result->continents[0].unk_0c) == 4 && word(result->continents[1].unk_0c) == 0 &&
            word(result->continents[2].unk_0c) == 1, "continent second hop excludes its own bit");
    require(result->territories[0].data.unk_8a4 == 5 && result->territories[1].data.unk_8a4 == 2 &&
            result->territories[2].data.unk_8a4 == 5, "territory second hop preserves original ESI32 quirk and includes own bit");
    const Continent zero{};
    require(std::memcmp(&result->continents[31], &zero, sizeof(zero)) == 0 && result->continents[0].bonus == 0,
            "entire saved continent array is reset, including bonuses and opaque tails");

    d->territories[0].data.adjContinents = 8;
    d->territories[0].data.unk_8a4 = 0x40000000;
    result = derive(*d, report);
    require(result->territories[0].data.adjContinents == 10 && result->continents[0].adjContinents == 10 &&
            result->territories[0].data.unk_8a4 == 0x40000005,
            "saved territory masks are OR accumulators, not silently recomputed from zero");

    d = fixture(2); d->territories[1].data.continent = 0; d->territories[1].data.terrain = 0;
    result = derive(*d, report);
    require(result->continents[0].hasLand == 0 && result->continents[0].terrainMask == 8,
            "last sea territory overwrites continent hasLand despite earlier land");
    d->territories[0].data.terrain = 0; d->territories[1].data.terrain = 2;
    result = derive(*d, report);
    require(result->continents[0].hasLand == 1 && result->continents[0].terrainMask == 4,
            "last land territory reverses hasLand assignment");

    d = fixture(1); d->territories[0].data.continent = 31;
    result = derive(*d, report);
    require(result->continents[31].hasLand == 1, "continent31 itself is safe without a signed mask walk");
    d->territories[0].data.continent = -1;
    d->territories[0].data.adjacency[0] = 1; // Fixed sentinel0 has continent0.
    result = derive(*d, report);
    require(result->territories[0].data.adjContinents == 0, "invalid continent is skipped by original first pass");
    d->territories[0].data.continent = 2;
    result = derive(*d, report);
    require(result->continents[2].adjContinents == 1, "sentinel adjacency reads a zero-initialized original territory");
}

void shrineOracles() {
    auto d = fixture();
    d->options.allowAlliances = 1; d->options.victory = 2;
    d->players[1].relations[0] = 0x10;
    auto& t = d->territories[0].data;
    t.owner = 0; word(t.unk_8b0, 0x80000001);
    building(*d, 1, 0, 37); building(*d, 1, 1, 37); // Count a city TERRITORY only once.
    building(*d, 1, 2, 46); building(*d, 1, 3, 45);
    building(*d, 1, 4, 47).turnsLeft = 1;
    building(*d, 2, 0, 46); // Unowned shrine counts total, not claimed.
    d->territories[2].data.owner = 2;
    d->territories[2].data.flags = 0x100;
    building(*d, 3, 0, 46); // Invalid/no-tiles flag excludes the whole territory.
    LoadDerivedReport report;
    auto result = derive(*d, report);
    require(report.territories == std::array<int32_t, 7>{1,0,0,0,0,0,0} &&
            report.cities == std::array<int32_t, 7>{1,0,0,0,0,0,0},
            "territory/city count ignores Active/Built but requires city turnsLeft==0");
    require(report.totalShrines == 4 && report.shrines == std::array<int32_t, 7>{2,2,0,0,0,0,0},
            "unfinished/unowned shrines count total; completed known shrine credits owner and full ally");
    require(report.notices == std::vector<simulation::ShrineNotice>{{1,1,0,0x4d},{1,2,0,0x4e}},
            "original shrine notices ordered by territory/site/player, only once after reveal mask");
    require(word(result->territories[0].data.unk_8b0) == 0xff && result->events.empty(),
            "shrine known mask replaced by 0xff, but semantic notice is not fabricated EventSaved");
    auto second = derive(*result, report);
    require(report.notices.empty() && report.shrines[0] == 2 && report.shrines[1] == 2,
            "repeated derived reconstruction counts again but does not notify already-known shrine");
    require(snapshot(*second) == snapshot(*result), "same shrine reveal is otherwise idempotent");

    word(t.unk_8b0, 0); result = derive(*d, report);
    require(report.shrines[0] == 0 && report.shrines[1] == 0 && report.notices.empty() && report.totalShrines == 4,
            "even completed owner shrine is not credited when owner-known bit is absent");
    word(t.unk_8b0, 1); d->options.allowAlliances = 0;
    result = derive(*d, report);
    require(report.shrines[0] == 2 && report.shrines[1] == 0 && report.notices[0].eventCode == 0x4e,
            "disabled alliances ignore a stored full-alliance relation");
    d->options.allowAlliances = 1; d->players[1].relations[0] = 4;
    result = derive(*d, report);
    require(report.shrines[1] == 0, "vision treaty alone is not a full shrine alliance");
    d->players[1].relations[0] = 0x10; d->options.numPlayers = 1;
    result = derive(*d, report);
    require(report.shrines[1] == 0, "HasPact respects options.numPlayers, not just seven storage slots");
    d->options.numPlayers = 3; d->options.victory = 0;
    result = derive(*d, report);
    require(report.notices.empty() && report.shrines[1] == 2, "non-shrine victory suppresses notices, not counters/reveal");
    t.numTiles = 0;
    result = derive(*d, report);
    require(report.totalShrines == 1 && report.territories[0] == 0, "zero tile count excludes all counting for a territory");
}

void roadOracles() {
    auto d = fixture();
    for (auto& r : d->territories) r.data.owner = 0;
    adjacent(*d, 1, 2); adjacent(*d, 2, 3);
    for (auto& r : d->territories) r.data.sites[0].unk_05[11] = 0xa9;
    LoadDerivedReport report;
    auto result = derive(*d, report);
    require(result->tiles[0].overlay == 2 && result->tiles[1].overlay == 10 && result->tiles[2].overlay == 8,
            "three local adjacent centers form east/east-west/west map roads");
    require(result->tiles[0].pathCost == 32767 && result->tiles[1].pathCost == 32767 && result->tiles[2].pathCost == 0,
            "final reverse pair retains source0 and unwritten goal32767, not a generic distance field");
    for (const auto& r : result->territories)
        require(r.data.sites[0].unk_05[11] == 0xa9, "map road rebuild never overwrites site road bytes");

    // Centers at x0/x2; the x1 tile belongs to territory1 and is an intermediate.
    // Last pair runs x2 -> x0: final middle cost is independently table cost.
    d = fixture(2); d->world.width = 3; d->tiles.resize(3);
    auto& left = d->territories[0].data; auto& right = d->territories[1].data;
    left.owner = right.owner = 0; left.numTiles = 2; left.tiles[1].raw = 1;
    right.tiles[0].raw = 2;
    d->tiles[1].territory = 1; d->tiles[2].x = 2; d->tiles[2].territory = 2;
    d->tiles[2].terrain = 3; adjacent(*d, 1, 2);
    constexpr int16_t costs[] = {10,4,3,2,3,5,30};
    for (uint8_t terrain = 0; terrain < 7; ++terrain) {
        d->tiles[1].terrain = terrain;
        result = derive(*d, report);
        require(result->tiles[1].pathCost == costs[terrain] && result->tiles[0].pathCost == 32767 &&
                result->tiles[2].pathCost == 0, "road costs come from signed WORD004dcc04, not movement004dcbe8");
        require(result->tiles[0].overlay == 2 && result->tiles[1].overlay == 10 && result->tiles[2].overlay == 8,
                "cost-weighted path still reconstructs the exact one-row directions");
    }

    // Nonlocal intermediate makes both routes unreachable. Original trace does
    // not abort: it applies N/S bits to its own target, then stops on that overlay.
    d = fixture(); d->territories[0].data.owner = d->territories[2].data.owner = 0;
    d->territories[1].data.owner = 1; adjacent(*d, 1, 3);
    result = derive(*d, report);
    require(result->tiles[0].overlay == 5 && result->tiles[1].overlay == 0 && result->tiles[2].overlay == 5,
            "unreachable original trace self-marks bits1|4; do not invent a prettier path or zero it");

    // Listed tiles alone are cleared; original unused dense tile bytes survive.
    d = fixture(1); d->world.width = 2; d->tiles.resize(2);
    d->tiles[1].x = 1; d->tiles[1].territory = 0; d->tiles[1].overlay = 0x55; d->tiles[1].pathCost = -77;
    result = derive(*d, report);
    require(result->tiles[0].overlay == 0 && result->tiles[0].pathCost == 100 &&
            result->tiles[1].overlay == 0x55 && result->tiles[1].pathCost == -77,
            "without an eligible route, costs remain saved and only listed overlays are cleared");
    d = fixture(2); adjacent(*d, 1, 2);
    d->territories[0].data.owner = d->territories[1].data.owner = 1;
    result = derive(*d, report);
    require(result->tiles[0].overlay == 0 && result->tiles[1].overlay == 0,
            "roads are for the local viewer, not all players or allies");
}

void transactionsAndPurity() {
    auto d = fixture(); adjacent(*d, 1, 2);
    d->territories[0].data.owner = d->territories[1].data.owner = 0;
    d->localList = {0, 0xfeedface}; d->trailing = {0, 0x80, 0xff};
    d->events.resize(1); d->options.eventCount = 1;
    d->events[0].record.textLen = 3; d->events[0].text = {'X',0,0xff};
    d->territories[0].data.production[8] = -73;
    d->territories[0].data.visibility[2] = 4;
    d->territories[0].data.unk_6d[2] = 10;
    LoadDerivedReport report;
    auto result = derive(*d, report);
    const auto original = snapshot(*d), prior = snapshot(*result);
    const auto oldReport = report;
    const auto bad = [&](LoadDerivedScope scope = LoadDerivedScope::Core) {
        save::Error error;
        require(!simulation::rebuildLoadDerived(*d, *result, report, error, scope) &&
                error.code != save::ErrorCode::None && !error.message.empty() &&
                snapshot(*result) == prior && report == oldReport, "failure preserves destination and report atomically");
    };
    bad(LoadDerivedScope::Complete);
    d->territories[0].data.adjContinents = 0x80000000; bad();
    d->territories[0].data.adjContinents = 0;
    d->territories[1].data.continent = 31; bad();
    d->territories[1].data.continent = 1;
    d->territories[0].data.owner = 7; bad(); d->territories[0].data.owner = 0;
    d->territories[0].data.centerTile = -1; bad(); d->territories[0].data.centerTile = 0;
    d->tiles[1].terrain = 7; bad(); d->tiles[1].terrain = 3;
    d->territories[0].data.sites[0].building.raw = 999; bad();
    d->territories[0].data.sites[0].building.raw = 0;
    d->header.isMap = 1; d->mapTerritories.resize(3); bad();
    d->header.isMap = 0; d->mapTerritories.clear();
    require(snapshot(*d) == original, "failed transformations did not mutate source");

    std::vector<uint8_t> globalState(sizeof(gs)), globalMisc(sizeof(gg));
    std::memcpy(globalState.data(), &gs, sizeof(gs)); std::memcpy(globalMisc.data(), &gg, sizeof(gg));
    const auto seed = rtl::seed(), high = rtl::seedHi();
    auto repeated = derive(*d, report);
    require(snapshot(*repeated) == prior && report == oldReport, "same source gives identical derived document and report");
    bad(LoadDerivedScope::Complete);
    auto aliased = std::make_unique<save::Document>(*d);
    save::Error error;
    require(simulation::rebuildLoadDerived(*aliased, *aliased, report, error) && snapshot(*aliased) == prior,
            "input/output alias supported through candidate ownership");
    require(std::memcmp(globalState.data(), &gs, sizeof(gs)) == 0 &&
            std::memcmp(globalMisc.data(), &gg, sizeof(gg)) == 0 && rtl::seed() == seed && rtl::seedHi() == high,
            "success and failure do not consume RNG or touch legacy global state");
    require(result->events[0].text == d->events[0].text && result->localList == d->localList &&
            result->trailing == d->trailing && result->options.turn == 71 && result->options.nextGlobalId == 234 &&
            result->options.gameSeed == 0x87654321 && result->world.rngSeed == 0x12345678 &&
            result->territories[0].data.production[8] == -73 && result->territories[0].data.visibility[2] == 4 &&
            result->territories[0].data.unk_6d[2] == 10, "unimplemented phases, seeds, binary text and opaque state are untouched");
}

void corpus(const std::filesystem::path& directory) {
    namespace fs = std::filesystem;
    if (directory.empty()) { std::cout << "load derived optional corpus: no data directory\n"; return; }
    size_t count = 0;
    const auto inspect = [&](const save::Document& d, const std::string& label) {
        try {
            LoadDerivedReport first, again;
            const auto before = snapshot(d);
            auto result = derive(d, first);
            auto repeat = derive(d, again);
            require(first == again && snapshot(*result) == snapshot(*repeat), "corpus determinism from identical source");
            require(snapshot(d) == before, "corpus source preserved");
            require(result->options.turn == d.options.turn && result->buildings.size() == d.buildings.size() &&
                    result->armies.size() == d.armies.size(), "derived reconstruction does not invent turns/entities");
            if (label == "TUTORIAL.SAV") {
                std::cout << "TUTORIAL derived (code-derived, not original executed): total shrines " << first.totalShrines << '\n';
            }
            ++count;
        } catch (const std::exception& error) { throw std::runtime_error(label + ": " + error.what()); }
    };
    for (const char* relative : {"TUTORIAL.SAV", "Saves/AUTOSAVE.SAV", "Campaign/AUTOSAVE.CPN", "Campaign/ChCht001.CPN"}) {
        const auto path = directory / relative;
        if (!fs::is_regular_file(path)) continue;
        auto d = std::make_unique<save::Document>(); save::Error error;
        if (!save::readDocument(path, *d, error)) throw std::runtime_error(error.message);
        inspect(*d, relative);
    }
    if (fs::is_regular_file(directory / "LEVELS.HDX") && fs::is_regular_file(directory / "LEVELS.HDD")) {
        HdxArchive archive; std::string why;
        if (!archive.open((directory / "LEVELS").string(), &why)) throw std::runtime_error(why);
        for (const auto& entry : archive.entries()) {
            auto d = std::make_unique<save::Document>(); save::Error error;
            if (!save::readScenario(directory / "LEVELS", entry.name, *d, error)) throw std::runtime_error(error.message);
            inspect(*d, "LEVELS:" + entry.name);
        }
    }
    std::cout << "load derived optional corpus: " << count << " documents\n";
}
} // namespace
int main(int argc, char** argv) {
    try {
        continentOracles(); shrineOracles(); roadOracles(); transactionsAndPurity();
        corpus(argc > 1 ? std::filesystem::path(argv[1]) : std::filesystem::path{});
        std::cout << "load_derived: continent/shrine/map-road oracles, unsupported domains and transactional ownership passed\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "load_derived: " << error.what() << '\n'; return 1;
    }
}
