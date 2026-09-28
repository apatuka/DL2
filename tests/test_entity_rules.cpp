// Oracles derived from FUN_0044d600 and its leaves, plus the jump table read
// from DEADLOCK.EXE. These tests do not claim observed original-game execution.
#include "game/entity_rules.h"
#include "game/data_tables.h"
#include "game/save_files.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include "formats/hdx_archive.h"

#include <algorithm>
#include <array>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
using namespace dl2;
using simulation::BuildingFootprint;
using simulation::BuildingPlacement;
using simulation::PlacementReason;

void require(bool condition, const char* message) {
    if (!condition) throw std::runtime_error(message);
}

std::unique_ptr<save::Document> fixture() {
    auto d = std::make_unique<save::Document>();
    std::memcpy(d->header.text, save::kHeaderText, sizeof(save::kHeaderText));
    d->header.version = kSaveVersion;
    d->options.numPlayers = 1; d->options.localPlayer = 0; d->options.turn = 41;
    d->options.nextGlobalId = 321;
    d->world.width = 3; d->world.height = 1; d->world.numTerritories = 3;
    d->world.rngSeed = 0x12345678;
    for (int player = 0; player < kMaxPlayers; ++player) {
        d->players[size_t(player)].index = uint8_t(player);
        d->players[size_t(player)].race = 2;
        d->ministerJobs[size_t(player)].resize(1);
    }
    d->players[0].type = 1;
    d->territories.resize(3); d->tiles.resize(3); d->buildings.reserve(36);
    for (int i = 0; i < 3; ++i) {
        auto& t = d->territories[size_t(i)].data;
        t.index = uint16_t(i + 1); t.owner = i == 0 ? 0 : -1;
        t.terrain = i == 1 ? 0 : 1; t.population = 500; t.morale = 75;
        t.numTiles = 1; t.tiles[0].raw = uint32_t(i);
        d->tiles[size_t(i)].x = uint8_t(i); d->tiles[size_t(i)].territory = int16_t(i + 1);
        for (int site = 0; site < kNumSites; ++site) {
            t.sites[site].unk_00 = uint16_t((site % 6) | ((site / 6) << 8));
            t.sites[site].terrainFlags = 1;
        }
    }
    return d;
}

void adjacent(save::Document& d, uint32_t a, uint32_t b) {
    d.territories[a - 1].data.adjacency[b >> 4] |= uint16_t(1u << (b & 15u));
    d.territories[b - 1].data.adjacency[a >> 4] |= uint16_t(1u << (a & 15u));
}

Building& addBuilding(save::Document& d, uint8_t type, int site, int territory = 1) {
    Building b{};
    b.id = uint16_t(100 + d.buildings.size()); b.type = type;
    b.category = data::kBuildingTypes[type].category;
    b.flags = 6; b.site = int8_t(site); b.territory = int16_t(territory);
    d.territories[size_t(territory - 1)].data.sites[size_t(site)].building.raw = b.id;
    d.buildings.push_back(b);
    return d.buildings.back();
}

std::vector<uint8_t> encode(const save::Document& d) {
    std::vector<uint8_t> bytes;
    save::Error error;
    if (!save::encode(d, bytes, error)) throw std::runtime_error("fixture encoding: " + error.message);
    // Nonserialized tails and raw queue-next words must be preserved too.
    for (const auto& record : d.territories) {
        const auto* begin = reinterpret_cast<const uint8_t*>(&record.data);
        bytes.insert(bytes.end(), begin + kTerritorySavedBytes, begin + sizeof(Territory));
        for (const auto& queue : record.queues)
            for (const auto& node : queue) {
                const auto* next = reinterpret_cast<const uint8_t*>(&node.next);
                bytes.insert(bytes.end(), next, next + sizeof(node.next));
            }
    }
    return bytes;
}

BuildingFootprint geometry(int type, int site) {
    BuildingFootprint result{99, true, {99}};
    save::Error error{save::ErrorCode::Io, 999, "stale"};
    if (!simulation::buildingFootprint(type, site, result, error)) throw std::runtime_error(error.message);
    require(error.code == save::ErrorCode::None && error.offset == 0 && error.message.empty(),
            "geometry success, including an off-grid answer, clears the previous error");
    return result;
}

BuildingPlacement query(const save::Document& d, uint32_t territory, int type, int site) {
    const auto before = encode(d);
    BuildingPlacement result;
    result.footprint.sites = {99};
    save::Error error{save::ErrorCode::Io, 999, "stale"};
    if (!simulation::checkBuildingPlacement(d, territory, type, site, result, error))
        throw std::runtime_error(error.message);
    require(error.code == save::ErrorCode::None && error.offset == 0 && error.message.empty(),
            "placement permission and semantic denial both clear previous errors");
    require(result.territory == territory && result.buildingType == type && result.site == site,
            "placement report identifies the exact query");
    require(result.footprint == geometry(type, site), "placement and standalone geometry agree");
    require(encode(d) == before, "placement query preserves document bytes and unpersisted territory tails");
    return result;
}

void footprints() {
    require(geometry(1, 0) == BuildingFootprint{1, true, {0}} &&
            geometry(1, 35) == BuildingFootprint{1, true, {35}}, "size1 corner footprints");
    require(geometry(6, 14) == BuildingFootprint{2, true, {14, 15, 8, 9}},
            "size2 footprint walks right then upward, not downward");
    require(geometry(6, 34) == BuildingFootprint{2, true, {34, 35, 28, 29}},
            "last valid size2 anchor covers the bottom-right square");
    require(geometry(38, 25) == BuildingFootprint{5, true, {
                25,26,27,28,29,19,20,21,22,23,13,14,15,16,17,7,8,9,10,11,1,2,3,4,5}},
            "Sea Platform footprint is the full 25-cell checked area, not just its six marked cells");
    require(!geometry(6, 5).fits && geometry(6, 5).sites.empty() &&
            !geometry(6, 35).fits && !geometry(38, 14).fits,
            "off-grid rectangular footprints are never partially enumerated");
    for (int site : {std::numeric_limits<int>::min(), -1, 36, std::numeric_limits<int>::max()})
        require(geometry(1, site) == BuildingFootprint{1, false, {}}, "extreme anchors fail geometry without overflow");

    // Independently transcribed BuildingDef size column, not an expected value
    // computed by calling or indexing the implementation's geometry helper.
    constexpr std::array<int, 11> sizeTwo = {5,6,8,14,18,23,26,27,35,37,45};
    for (int type = 1; type < 48; ++type) {
        const int size = type == 38 ? 5 :
            (std::find(sizeTwo.begin(), sizeTwo.end(), type) != sizeTwo.end() ? 2 : 1);
        size_t count = 0;
        for (int site = 0; site < 36; ++site) {
            const auto f = geometry(type, site);
            require(f.size == size, "all48 table rows use their documented footprint size");
            if (f.fits) {
                ++count;
                require(f.sites.size() == size_t(size * size) && f.sites.front() == site,
                        "fitting footprint has exactly size squared cells beginning at the anchor");
                for (const auto cell : f.sites) require(cell < 36, "every footprint cell is in the grid");
            }
        }
        require(count == (size == 1 ? 36u : size == 2 ? 25u : 4u), "complete-grid footprint count oracle");
    }
}

void basicReasonsAndCellPrecedence() {
    auto d = fixture();
    auto& t = d->territories[0].data;
    require(query(*d, 1, 6, 14).reason == PlacementReason::Allowed, "empty valid land footprint is accepted");
    require(query(*d, 1, 6, 5).reason == PlacementReason::OutOfBounds, "size2 anchor in top-right corner fails bounds");
    for (int site : {std::numeric_limits<int>::min(), -1, 36, std::numeric_limits<int>::max()})
        require(query(*d, 1, 1, site).reason == PlacementReason::OutOfBounds, "out-of-grid anchors yield original reason1");
    t.sites[15].terrainFlags = 0x2001;
    require(query(*d, 1, 6, 14).reason == PlacementReason::Occupied, "high quadrant byte occupies a nonanchor footprint cell");
    t.sites[15].terrainFlags = 1; t.sites[8].terrainFlags = 0xff;
    require(query(*d, 1, 6, 14).reason == PlacementReason::UnavailableTerrain, "low-byte FF is unavailable for ordinary buildings");
    t.sites[8].terrainFlags = 5;
    require(query(*d, 1, 6, 14).reason == PlacementReason::BlockedTerrain, "low-byte terrain5 has distinct reason6");
    t.sites[8].terrainFlags = 1; t.sites[14].terrainFlags = 0x2005;
    require(query(*d, 1, 6, 14).reason == PlacementReason::Occupied, "occupation check precedes blocked terrain in the same cell");
    t.sites[14].terrainFlags = 5; t.sites[15].terrainFlags = 0x2001;
    require(query(*d, 1, 6, 14).reason == PlacementReason::BlockedTerrain, "cell traversal precedes a later cell's stronger-looking denial");
    t.sites[14].terrainFlags = t.sites[15].terrainFlags = 1;
    addBuilding(*d, 1, 9);
    require(query(*d, 1, 6, 14).reason == PlacementReason::Occupied,
            "a nonzero saved building ID occupies a footprint cell even without high flag bits");
}

void categoryAndSeaOnlyPrecedence() {
    for (int type : {38,39,40,41,42,43,44,47}) {
        auto d = fixture();
        require(query(*d, 1, type, -1).reason == PlacementReason::SeaOnlyOnLand,
                "sea-only type restriction precedes out-of-bounds reason");
    }
    auto d = fixture();
    auto& existing = addBuilding(*d, 1, 0);
    existing.category = 9; existing.flags = 0; existing.turnsLeft = 100;
    require(query(*d, 1, 37, -1).reason == PlacementReason::ExistingCityCenter,
            "duplicate City Center uses stored category even when inactive, unfinished and a different type");
    existing.category = 11;
    require(query(*d, 1, 45, -1).reason == PlacementReason::ExistingShrine,
            "any stored shrine category blocks another shrine before bounds");
    d->territories[0].data.terrain = 0; existing.category = 20;
    require(query(*d, 1, 38, -1).reason == PlacementReason::ExistingSeaPlatform,
            "duplicate Sea Platform precedes bounds on a sea territory");
    d->territories[0].data.terrain = 1;
    require(query(*d, 1, 38, -1).reason == PlacementReason::SeaOnlyOnLand,
            "sea-only restriction precedes even duplicate-platform rejection");
    require(query(*d, 3, 37, 14).reason == PlacementReason::Allowed,
            "category uniqueness is local, not a global player/world restriction");
}

void portAdjacency() {
    auto d = fixture();
    require(query(*d, 1, 24, -1).reason == PlacementReason::PortWithoutAdjacentSea,
            "missing sea neighbor precedes invalid site for ports");
    adjacent(*d, 1, 2);
    require(query(*d, 1, 24, 14).reason == PlacementReason::Allowed,
            "land port accepts an adjacent inhabited-or-unowned valid sea territory");
    d->territories[1].data.flags |= 0x100;
    require(query(*d, 1, 25, 14).reason == PlacementReason::PortWithoutAdjacentSea,
            "NoTiles flag excludes a sea neighbor even with tile references");
    d->territories[1].data.flags = 0; d->territories[1].data.numTiles = 0;
    require(query(*d, 1, 24, 14).reason == PlacementReason::PortWithoutAdjacentSea,
            "empty sea neighbor does not satisfy adjacency");
    d->territories[1].data.numTiles = 1; d->territories[1].data.terrain = 1;
    require(query(*d, 1, 24, 14).reason == PlacementReason::PortWithoutAdjacentSea,
            "adjacent land does not satisfy a sea query");
    d->territories[1].data.terrain = 0; d->territories[1].data.flags = 0x200;
    require(query(*d, 1, 24, 14).reason == PlacementReason::Allowed,
            "other territory flags do not imply the specific NoTiles flag");
    d->territories[0].data.adjacency[0] |= 1; // Empty historical sentinel, not a saved territory.
    require(query(*d, 1, 24, 14).reason == PlacementReason::Allowed,
            "sentinel adjacency bit does not become an invalid document reference");
}

void platformTableAndEarlyReturn() {
    // Independent decoded truth set of the original jump table 0044d40f.
    constexpr std::array<int, 14> seaTypes = {19,20,24,25,28,30,33,34,39,40,41,42,43,44};
    auto d = fixture();
    d->territories[2].data.terrain = 0;
    adjacent(*d, 2, 3); // Make ports' earlier adjacency requirement pass.
    auto& slot = d->territories[1].data.sites[14];
    slot.terrainFlags = 0x5105; // PlatformFree with low terrain5: platform branch wins.
    for (int type = 1; type < 48; ++type) {
        const bool allowed = std::find(seaTypes.begin(), seaTypes.end(), type) != seaTypes.end();
        require(query(*d, 2, type, 14).reason ==
                    (allowed ? PlacementReason::Allowed : PlacementReason::UnsupportedPlatformBuilding),
                "platform-free early return exactly matches the original sea-building truth table");
    }
    // Size5 at anchor14 is globally off-grid, but its FIRST cell is a platform
    // slot and returns7. Geometry must not be used to prematurely return1.
    const auto platform = query(*d, 2, 38, 14);
    require(!platform.footprint.fits && platform.reason == PlacementReason::UnsupportedPlatformBuilding,
            "platform early denial has priority over later rectangular out-of-bounds cells");
    addBuilding(*d, 1, 14, 2);
    require(query(*d, 2, 19, 14).reason == PlacementReason::Allowed,
            "original platform early success precedes even an existing building ID in that cell");
    slot.terrainFlags = 0x3201;
    require(query(*d, 2, 19, 14).reason == PlacementReason::Occupied,
            "PlatformUsed is occupied, not another spelling of PlatformFree");
}

void noHiddenConstructionPolicy() {
    auto d = fixture();
    auto& t = d->territories[0].data;
    t.owner = -1; t.population = 0; t.flags = 0x100;
    d->players[0].credits = std::numeric_limits<int32_t>::min();
    d->players[0].race = -1;
    for (auto& site : t.sites) {
        site.unk_00 = 0xffff; // This query walks by site index, not these coordinates.
        site.value = 1;
    }
    require(query(*d, 1, 6, 14).reason == PlacementReason::Allowed,
            "placement does not invent population, ownership, affordability, tech, richness or coordinate requirements");
    // CheckConstructionSite is weaker than FindConstructionSite: with no Sea
    // Platform, the latter disallows most types, but the former can accept an
    // ordinary clear sea-territory cell. Do not fuse these distinct functions.
    require(query(*d, 2, 1, 0).reason == PlacementReason::Allowed,
            "site check alone does not require a Sea Platform in a sea territory");
    for (auto& site : d->territories[1].data.sites) site.terrainFlags = 0xff;
    require(query(*d, 2, 38, 25).reason == PlacementReason::Allowed &&
            query(*d, 2, 47, 0).reason == PlacementReason::Allowed &&
            query(*d, 2, 41, 0).reason == PlacementReason::UnavailableTerrain,
            "low terrainFF exemptions are only Sea Platform and Sea Shrine");
}

void transactionsAndPurity() {
    auto d = fixture();
    d->territories[0].data.production[3] = 0x123456;
    d->territories[0].data.consumption[8] = -99;
    d->territories[0].data.sites[14].unk_05[11] = 0xff; // Site+0x10 road byte must not change.
    d->localList = {0, 0xfeedface}; d->trailing = {0, 0xff, 0x80};
    d->events.resize(1); d->options.eventCount = 1;
    d->events[0].record.textLen = 3; d->events[0].text = {'A', 0, 0xff};
    const auto prior = query(*d, 1, 6, 14);
    auto destination = prior;
    save::Error error;
    const auto input = encode(*d);
    for (int type : {std::numeric_limits<int>::min(), -1, 0, 48, std::numeric_limits<int>::max()}) {
        auto f = prior.footprint;
        require(!simulation::buildingFootprint(type, 14, f, error) && f == prior.footprint &&
                error.code != save::ErrorCode::None && !error.message.empty(),
                "invalid geometry type preserves previous result and returns an error");
        require(!simulation::checkBuildingPlacement(*d, 1, type, 14, destination, error) && destination == prior,
                "invalid placement type preserves previous result");
    }
    for (uint32_t id : {0u, 4u, std::numeric_limits<uint32_t>::max()})
        require(!simulation::checkBuildingPlacement(*d, id, 6, 14, destination, error) && destination == prior,
                "invalid territory preserves prior result");
    d->territories[0].data.sites[14].building.raw = 9999;
    require(!simulation::checkBuildingPlacement(*d, 1, 6, 14, destination, error) && destination == prior &&
            d->territories[0].data.sites[14].building.raw == 9999,
            "invalid site reference is an error, not a fabricated occupied answer or an input repair");
    d->territories[0].data.sites[14].building.raw = 0;
    d->header.isMap = 1; d->mapTerritories.resize(3);
    require(!simulation::checkBuildingPlacement(*d, 1, 6, 14, destination, error) && destination == prior,
            "reduced map is not silently promoted to a saved-game document");
    d->header.isMap = 0; d->mapTerritories.clear();
    require(encode(*d) == input, "failed queries never change valid source state");

    std::vector<uint8_t> globalState(sizeof(gs)), globalMisc(sizeof(gg));
    std::memcpy(globalState.data(), &gs, sizeof(gs)); std::memcpy(globalMisc.data(), &gg, sizeof(gg));
    const auto seed = rtl::seed(), seedHi = rtl::seedHi();
    require(query(*d, 1, 6, 14) == prior && query(*d, 1, 6, 14) == prior,
            "placement query is deterministic and does not generate IDs or gameplay objects");
    require(!simulation::checkBuildingPlacement(*d, 0, 6, 14, destination, error), "also test failed query with global guard");
    require(std::memcmp(globalState.data(), &gs, sizeof(gs)) == 0 &&
            std::memcmp(globalMisc.data(), &gg, sizeof(gg)) == 0 && rtl::seed() == seed && rtl::seedHi() == seedHi &&
            encode(*d) == input && d->options.turn == 41 && d->options.nextGlobalId == 321,
            "success/failure preserve global state, both RNG words, saved seed, turn and ID counter");
}

void corpus(const std::filesystem::path& directory) {
    namespace fs = std::filesystem;
    if (directory.empty()) { std::cout << "entity rules optional corpus: no data directory\n"; return; }
    size_t documents = 0, territories = 0, buildings = 0;
    const auto inspect = [&](const save::Document& d, const std::string& label) {
        try {
            // One document-validated query per territory, not 48*36 queries per
            // territory. All47 types/all36 anchors are covered synthetically.
            for (const auto& record : d.territories) {
                const auto result = query(d, record.data.index, 1, 14);
                require(uint8_t(result.reason) <= 10, "corpus reports an original reason code");
                ++territories;
            }
            for (const auto& building : d.buildings) {
                const auto f = geometry(building.type, building.site);
                require(f.fits, "original corpus building has an in-grid footprint");
                ++buildings;
            }
            ++documents;
        } catch (const std::exception& error) {
            throw std::runtime_error(label + ": " + error.what());
        }
    };
    for (const char* relative : {"TUTORIAL.SAV", "Saves/AUTOSAVE.SAV", "Campaign/AUTOSAVE.CPN", "Campaign/ChCht001.CPN"}) {
        const auto path = directory / relative;
        if (!fs::is_regular_file(path)) continue;
        auto d = std::make_unique<save::Document>();
        save::Error error;
        if (!save::readDocument(path, *d, error)) throw std::runtime_error(error.message);
        inspect(*d, relative);
    }
    if (fs::is_regular_file(directory / "LEVELS.HDX") && fs::is_regular_file(directory / "LEVELS.HDD")) {
        HdxArchive archive;
        std::string why;
        if (!archive.open((directory / "LEVELS").string(), &why)) throw std::runtime_error(why);
        for (const auto& entry : archive.entries()) {
            auto d = std::make_unique<save::Document>();
            save::Error error;
            if (!save::readScenario(directory / "LEVELS", entry.name, *d, error)) throw std::runtime_error(error.message);
            inspect(*d, "LEVELS:" + entry.name);
        }
    }
    std::cout << "entity rules optional corpus: " << documents << " documents, " << territories
              << " territories, " << buildings << " buildings\n";
}
} // namespace

int main(int argc, char** argv) {
    try {
        footprints();
        basicReasonsAndCellPrecedence();
        categoryAndSeaOnlyPrecedence();
        portAdjacency();
        platformTableAndEarlyReturn();
        noHiddenConstructionPolicy();
        transactionsAndPurity();
        corpus(argc > 1 ? std::filesystem::path(argv[1]) : std::filesystem::path{});
        std::cout << "entity_rules: geometry, original reasons and precedence, platform table, adjacency, transaction and purity passed\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "entity_rules: " << error.what() << '\n';
        return 1;
    }
}
