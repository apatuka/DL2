// Independent integer/control-flow oracles from FindConstructionSite0044d464,
// its leaves and original site-order table. No execution of DEADLOCK.EXE is
// claimed; repeated port execution is only a determinism check.
#include "game/construction_site.h"
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
#include <source_location>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
using namespace dl2;
using namespace dl2::simulation;
void require(bool condition, const char* message) { if (!condition) throw std::runtime_error(message); }
// Diagnostics only, never part of game state or expected-value calculation.
uint32_t lastQueryTerritory = 0;
int lastQueryType = 0;

std::unique_ptr<save::Document> fixture() {
    auto d = std::make_unique<save::Document>();
    std::memcpy(d->header.text,save::kHeaderText,sizeof(save::kHeaderText));
    d->header.version = kSaveVersion;
    d->options.numPlayers = 1; d->options.localPlayer = 0; d->options.turn = 41;
    d->options.nextGlobalId = 321; d->options.gameId = 555;
    d->world.width = 3; d->world.height = 1; d->world.numTerritories = 3;
    d->world.rngSeed = 0x12345678;
    for (int p = 0; p < kMaxPlayers; ++p) {
        d->players[size_t(p)].index = uint8_t(p); d->players[size_t(p)].race = 2;
        d->ministerJobs[size_t(p)].resize(1);
    }
    d->players[0].type = 1;
    d->territories.resize(3); d->tiles.resize(3); d->buildings.reserve(36);
    for (int i = 0; i < 3; ++i) {
        auto& t = d->territories[size_t(i)].data;
        t.index = uint16_t(i+1); t.owner = i ? -1 : 0; t.terrain = i ? 0 : 1;
        t.numTiles = 1; t.tiles[0].raw = uint32_t(i);
        d->tiles[size_t(i)].x = uint8_t(i); d->tiles[size_t(i)].territory = int16_t(i+1);
        for (int site = 0; site < 36; ++site) {
            t.sites[site].unk_00 = uint16_t((site%6) | ((site/6)<<8));
            t.sites[site].terrainFlags = 1;
        }
    }
    return d;
}
void adjacent(save::Document& d, uint32_t a, uint32_t b) {
    d.territories[a-1].data.adjacency[b/16] |= uint16_t(1u << (b%16));
    d.territories[b-1].data.adjacency[a/16] |= uint16_t(1u << (a%16));
}
Building& building(save::Document& d, uint32_t territory, uint8_t type, int site) {
    Building b{};
    b.id = uint16_t(100+d.buildings.size()); b.type = type;
    b.category = data::kBuildingTypes[type].category;
    b.territory = int16_t(territory); b.site = int8_t(site);
    b.turnsLeft = 100; // Category detection must not require completion.
    d.territories[territory-1].data.sites[site].building.raw = b.id;
    d.buildings.push_back(b); return d.buildings.back();
}
std::vector<uint8_t> snapshot(const save::Document& d) {
    std::vector<uint8_t> bytes; save::Error error;
    if (!save::encode(d,bytes,error)) throw std::runtime_error(error.message);
    for (const auto& record : d.territories) {
        const auto* raw = reinterpret_cast<const uint8_t*>(&record.data);
        bytes.insert(bytes.end(),raw+kTerritorySavedBytes,raw+sizeof(Territory));
    }
    return bytes;
}
RngSnapshot rng(uint32_t low = 1, uint32_t high = 0) {
    RngSnapshot result; result.initialized = true;
    result.rtlLow = low; result.rtlHigh = high; result.secondary = 0x13579bdf;
    return result;
}
ConstructionSiteReport query(const save::Document& d, uint32_t territory, int type,
                             RngSnapshot before = {}) {
    lastQueryTerritory = territory;
    lastQueryType = type;
    const auto input = snapshot(d);
    const auto rngInput = before;
    ConstructionSiteReport result; result.site = 987; result.found = true;
    save::Error error{save::ErrorCode::Io,99,"stale"};
    if (!findConstructionSite(d,territory,type,before,result,error)) throw std::runtime_error(error.message);
    require(error.code == save::ErrorCode::None && error.offset == 0 && error.message.empty(),
            "success, including no site, clears stale error");
    require(result.found == (result.site >= 0 && result.site < 36),"site/found report is coherent");
    require(result.found || result.site == -1,"absence is original -1, not a fabricated cell");
    require(snapshot(d) == input && before == rngInput,"query preserves every owned byte and input RNG");
    return result;
}
void noDraw(const ConstructionSiteReport& result, int site, const RngSnapshot& before = {},
            const std::source_location location = std::source_location::current()) {
    if (result.site != site || result.found != (site != -1))
        throw std::runtime_error("deterministic site oracle at line " + std::to_string(location.line()) +
                                 " (territory " + std::to_string(lastQueryTerritory) + ", type " +
                                 std::to_string(lastQueryType) + ")" +
                                 ": expected " + std::to_string(site) + ", got " + std::to_string(result.site));
    require(result.draws.empty() && result.rngAfter == before,"deterministic branches consume no RNG");
}

void orderAndResources() {
    // Independent transcription from004c5e58, not data::kSiteOrder as expected.
    constexpr std::array<int,36> order = {
        14,15,20,21,8,9,13,16,19,22,26,27,28,25,7,10,2,3,
        12,18,17,23,32,33,1,4,6,11,24,29,31,34,0,5,30,35};
    auto d = fixture(); auto& t = d->territories[0].data;
    for (const int expected : order) {
        noDraw(query(*d,1,1),expected);
        t.sites[expected].terrainFlags = 0x2001;
    }
    noDraw(query(*d,1,1),-1);
    for (auto& site : t.sites) { site.terrainFlags = 1; site.value = 1; }
    noDraw(query(*d,1,1),35); // Last legal resource site, not first.
    t.sites[35].terrainFlags = 5;
    noDraw(query(*d,1,1),30);
    t.sites[0].value = 0;
    noDraw(query(*d,1,1),0); // First resource-free always beats previous fallback.
    t.sites[14].value = 0;
    noDraw(query(*d,1,1),14);

    d = fixture(); auto& sites = d->territories[0].data.sites;
    sites[8].value = 0xff; // Non-anchor cell of14's 2x2 footprint.
    noDraw(query(*d,1,6),15); // 15 covers15,16,9,10 and avoids8.
    for (auto& site : sites) { site.value = 1; site.unk_00 = 0xffff; }
    // Anchor30 follows34 in004c5e58 and covers30,31,24,25 (x++/y--),
    // so it, not34, is the LAST legal resource-bearing2x2 footprint.
    noDraw(query(*d,1,6),30); // Persisted Site+00/+01 coordinates are ignored.
    for (auto& site : sites) site.terrainFlags = 5;
    for (int site : {14,15,8,9}) sites[site].terrainFlags = 1;
    noDraw(query(*d,1,6),14); // Only this resource-bearing footprint fits.
    sites[9].terrainFlags = 0xff;
    noDraw(query(*d,1,6),-1);
}

void seaGatesAndCategories() {
    auto d = fixture();
    for (int type = 1; type <= 47; ++type) {
        if (type == 38 || type == 47) continue;
        noDraw(query(*d,2,type),-1); // No Sea Platform: stronger than site check.
    }
    noDraw(query(*d,2,38),25); // First fitting 5x5 in canonical order.
    for (auto& site : d->territories[1].data.sites) { site.value = 1; site.terrainFlags = 0xff; }
    noDraw(query(*d,2,38),30); // Last fitting5x5, lowFF exemption survives.
    for (int type : {38,39,40,41,42,43,44,47}) noDraw(query(*d,1,type),-1);

    d = fixture(); adjacent(*d,2,3);
    auto& platform = building(*d,2,1,0);
    platform.category = 20; platform.flags = 0; // Type irrelevant, unfinished accepted.
    constexpr std::array<int,14> permitted = {19,20,24,25,28,30,33,34,39,40,41,42,43,44};
    for (int type = 1; type <= 46; ++type) {
        const bool allowed = std::find(permitted.begin(),permitted.end(),type) != permitted.end();
        noDraw(query(*d,2,type),allowed ? 14 : -1);
    }
    d->territories[1].data.sites[14].terrainFlags = 0x5105;
    building(*d,2,1,14);
    noDraw(query(*d,2,19),14); // Preserve placement's early platform success.

    d = fixture();
    noDraw(query(*d,1,24),-1); // Port requires adjacent nonempty unflaggedsea.
    adjacent(*d,1,2); noDraw(query(*d,1,24),14);
    d->territories[1].data.flags = 0x100; noDraw(query(*d,1,24),-1);
    d->territories[1].data.flags = 0; d->territories[1].data.numTiles = 0;
    noDraw(query(*d,1,24),-1);
    auto& category = building(*d,1,1,0);
    category.category = 9; noDraw(query(*d,1,37),-1);
    category.category = 11; noDraw(query(*d,1,45),-1);
    category.category = 1; noDraw(query(*d,1,37),14);
}

void shrineRngAndBypass() {
    auto d = fixture();
    for (auto& site : d->territories[1].data.sites) { site.value = 255; site.terrainFlags = 5; }
    for (const int corner : {0,5,30,35}) building(*d,2,1,corner);
    // Independent first Long31 arithmetic with multiplier high346/low20021:
    // (low,high) -> (low',high'), remainder4. These distinguish Long31 from
    // Rand15 and preserve the secondary stream. Occupied corners STILL win.
    struct Oracle { uint32_t low,high,nextLow,nextHigh,value; int site; };
    constexpr Oracle oracles[] = {
        {0,0,1,0,0,0}, {0,1,1,20021,1,5},
        {1,0,20022,346,2,30}, {1,1,20022,20367,3,35}};
    for (const auto& oracle : oracles) {
        const auto before = rng(oracle.low,oracle.high);
        const auto result = query(*d,2,47,before);
        require(result.found && result.site == oracle.site,"sea shrine original corner mapping");
        auto expected = before; expected.rtlLow = oracle.nextLow; expected.rtlHigh = oracle.nextHigh;
        expected.counters.operations = expected.counters.taggedRange = expected.counters.long31 = 1;
        require(result.rngAfter == expected,"exact one Long31 draw and no Rand15/secondary/seed operation");
        require(result.draws.size() == 1 && result.draws[0] ==
            RngEvent{1,RngOperation::TaggedRange,4,0,oracle.value,"FindConstructionSite",true},
            "owned draw report preserves tag, bound, ordinal and consumed value");
        BuildingPlacement placement; save::Error error;
        require(checkBuildingPlacement(*d,2,47,result.site,placement,error) &&
                placement.reason == PlacementReason::Occupied,
                "automatic sea shrine intentionally returns a site that explicit placement rejects");
    }
    // Nonzero prior counters are not reset, and rngBefore may reference the
    // old destination's own snapshot without a stale alias during commit.
    const auto before = rng(0,1); auto result = query(*d,2,47,before);
    const auto prior = result.rngAfter; save::Error error;
    require(findConstructionSite(*d,2,47,result.rngAfter,result,error),"input snapshot/output report alias is safe");
    require(result.draws.size() == 1 && result.draws[0].ordinal == 2 &&
            result.rngAfter.counters.long31 == 2 && result.rngAfter.secondary == prior.secondary,
            "chained calls preserve prior counter order and secondary state");
    // A different stored type with category11 suppresses the draw, before any
    // access to uninitialized RNG; a platform does not suppress it.
    d->buildings[0].category = 11;
    noDraw(query(*d,2,47),-1);
    noDraw(query(*d,2,47,before),-1,before);
    d->buildings[0].category = 20;
    require(query(*d,2,47,before).site == 5,"sea shrine precedes platform suitability gate");
    noDraw(query(*d,1,47,before),-1,before);
}

void errorsAndIsolation() {
    auto d = fixture();
    d->territories[0].data.owner = -1; d->players[0].race = -1;
    d->players[0].credits = std::numeric_limits<int32_t>::min();
    d->territories[0].data.production[3] = -77; d->territories[0].data.consumption[4] = 881;
    d->events.resize(1); d->options.eventCount = 1;
    d->events[0].text = {'A',0,0xff}; d->events[0].record.textLen = 3;
    d->localList = {0,0xfeedface}; d->trailing = {0xff,0,0x80};
    const auto input = snapshot(*d); const auto before = rng();
    const auto prior = query(*d,1,6,before); auto result = prior; save::Error error;
    noDraw(prior,14,before); // No hidden owner/race/cost/tech/population gates.
    const auto failed = [&](uint32_t territory, int type, const RngSnapshot& state) {
        require(!findConstructionSite(*d,territory,type,state,result,error) && result == prior &&
                error.code != save::ErrorCode::None && !error.message.empty(),
                "invalid query preserves previous full report and returns explicit error");
    };
    for (int type : {std::numeric_limits<int>::min(),-1,0,48,std::numeric_limits<int>::max()}) failed(1,type,before);
    for (uint32_t territory : {0u,4u,std::numeric_limits<uint32_t>::max()}) failed(territory,1,before);
    failed(2,47,{}); // Only branch needing a draw rejects empty session.
    auto invalid = before; invalid.format = 999; failed(1,1,invalid);
    invalid = {}; invalid.rtlLow = 1; failed(1,1,invalid);
    invalid = before; invalid.counters.operations = 1; failed(1,1,invalid);
    auto exhausted = before;
    exhausted.counters.operations = exhausted.counters.long31 = std::numeric_limits<uint64_t>::max();
    failed(2,47,exhausted);
    noDraw(query(*d,1,1,exhausted),14,exhausted); // No artificial RNG requirement.
    d->territories[0].data.sites[0].building.raw = 9999; failed(1,1,before);
    d->territories[0].data.sites[0].building.raw = 0;
    d->header.isMap = 1; d->mapTerritories.resize(3); failed(1,1,before);
    d->header.isMap = 0; d->mapTerritories.clear();
    require(snapshot(*d) == input,"failed queries never repair or mutate input");

    std::vector<uint8_t> globalState(sizeof(gs)), globalMisc(sizeof(gg));
    std::memcpy(globalState.data(),&gs,sizeof(gs)); std::memcpy(globalMisc.data(),&gg,sizeof(gg));
    const auto low = rtl::seed(), high = rtl::seedHi();
    noDraw(query(*d,1,6,before),14,before);
    const auto randomResult = query(*d,2,47,before);
    require(query(*d,2,47,before) == randomResult,"explicit RNG makes repeat query deterministic");
    failed(2,47,{});
    require(std::memcmp(globalState.data(),&gs,sizeof(gs)) == 0 && std::memcmp(globalMisc.data(),&gg,sizeof(gg)) == 0 &&
            rtl::seed() == low && rtl::seedHi() == high && snapshot(*d) == input,
            "all success/failure/random branches leave globals, global RNG, save/turn/IDs untouched");
}

void corpus(const std::filesystem::path& directory) {
    namespace fs = std::filesystem;
    if (directory.empty()) { std::cout << "construction site optional corpus: no data directory\n"; return; }
    size_t documents = 0;
    const auto inspect = [&](const save::Document& d, const std::string& label) {
        try {
            const auto bytes = snapshot(d); const auto before = rng();
            auto result = query(d,1,6,before);
            require(result.draws.empty() && result.rngAfter == before,"ordinary corpus query has no RNG");
            if (result.found) {
                BuildingPlacement placement; save::Error error;
                require(checkBuildingPlacement(d,1,6,result.site,placement,error) &&
                        placement.reason == PlacementReason::Allowed,"ordinary automatic result obeys placement");
            }
            uint32_t selected = 1;
            for (const auto& record : d.territories)
                if (record.data.terrain == 0) { selected = record.data.index; break; }
            const auto& territory = d.territories[selected-1].data;
            bool shrine = false;
            for (const auto& site : territory.sites) {
                const auto* object = d.buildingById(site.building.raw);
                shrine = shrine || (object && object->category == 11);
            }
            result = query(d,selected,47,before);
            if (territory.terrain == 0 && !shrine)
                require(result.site == 30 && result.draws.size() == 1 && result.rngAfter.rtlLow == 20022 &&
                        result.rngAfter.rtlHigh == 346,"corpus random branch matches independent seed1 oracle");
            else noDraw(result,-1,before);
            require(snapshot(d) == bytes,"corpus source stays read-only"); ++documents;
        } catch (const std::exception& error) { throw std::runtime_error(label + ": " + error.what()); }
    };
    for (const char* relative : {"TUTORIAL.SAV","Saves/AUTOSAVE.SAV","Campaign/AUTOSAVE.CPN","Campaign/ChCht001.CPN"}) {
        if (!fs::is_regular_file(directory/relative)) continue;
        auto d = std::make_unique<save::Document>(); save::Error error;
        if (!save::readDocument(directory/relative,*d,error)) throw std::runtime_error(error.message);
        inspect(*d,relative);
    }
    if (fs::is_regular_file(directory/"LEVELS.HDX") && fs::is_regular_file(directory/"LEVELS.HDD")) {
        HdxArchive archive; std::string why;
        if (!archive.open((directory/"LEVELS").string(),&why)) throw std::runtime_error(why);
        for (const auto& entry : archive.entries()) {
            auto d = std::make_unique<save::Document>(); save::Error error;
            if (!save::readScenario(directory/"LEVELS",entry.name,*d,error)) throw std::runtime_error(error.message);
            inspect(*d,"LEVELS:"+entry.name);
        }
    }
    std::cout << "construction site optional corpus: " << documents << " documents\n";
}
} // namespace
int main(int argc, char** argv) {
    try {
        orderAndResources(); seaGatesAndCategories(); shrineRngAndBypass(); errorsAndIsolation();
        corpus(argc > 1 ? std::filesystem::path(argv[1]) : std::filesystem::path{});
        std::cout << "construction_site: exact order/resources, sea gates, Long31 corners, rollback and isolation passed\n";
        return 0;
    } catch (const std::exception& error) { std::cerr << "construction_site: " << error.what() << '\n'; return 1; }
}
