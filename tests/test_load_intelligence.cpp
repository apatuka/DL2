// Small independent oracles transcribed from 00447090 / 00446440(mode3) /
// 0046e730(load=1) / 0046e064. Not observed original-game execution results.
#include "game/load_intelligence.h"
#include "game/data_tables.h"
#include "game/save_files.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include "formats/hdx_archive.h"
#include <array>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
using namespace dl2;
using simulation::LoadIntelligenceContext;
using simulation::LoadIntelligenceReport;
void require(bool condition, const char* message) {
    if (!condition) throw std::runtime_error(message);
}
template<class T> T get(const void* pointer) {
    T value; std::memcpy(&value, pointer, sizeof(value)); return value;
}
template<class T> void put(void* pointer, T value) { std::memcpy(pointer, &value, sizeof(value)); }
uint8_t* raw(Territory& t) { return reinterpret_cast<uint8_t*>(&t); }
const uint8_t* raw(const Territory& t) { return reinterpret_cast<const uint8_t*>(&t); }
uint8_t* raw(BuildingSite& s) { return reinterpret_cast<uint8_t*>(&s); }
const uint8_t* raw(const BuildingSite& s) { return reinterpret_cast<const uint8_t*>(&s); }
int16_t distance(const save::Document& d, size_t territory, int player = 0) {
    return get<int16_t>(raw(d.territories[territory - 1].data) + 0xa70 + player * 2);
}
std::unique_ptr<save::Document> fixture(int count = 3) {
    auto d = std::make_unique<save::Document>();
    std::memcpy(d->header.text, save::kHeaderText, sizeof(save::kHeaderText));
    d->header.version = kSaveVersion;
    d->options.numPlayers = 7; d->options.localPlayer = 0; d->options.turn = 81;
    d->options.nextGlobalId = 987; d->options.gameId = 313;
    d->world.width = uint8_t(count <= 40 ? count : 40);
    d->world.height = uint8_t((count + d->world.width - 1) / d->world.width);
    d->world.numTerritories = uint16_t(count);
    for (size_t p = 0; p < 7; ++p) {
        d->players[p].index = uint8_t(p); d->players[p].race = int8_t(p);
        d->players[p].type = p ? 3 : 1; d->ministerJobs[p].resize(1);
    }
    d->territories.resize(size_t(count));
    d->tiles.resize(size_t(d->world.width) * d->world.height);
    d->buildings.reserve(20); d->armies.reserve(20);
    for (size_t i = 0; i < d->tiles.size(); ++i) {
        d->tiles[i].x = uint8_t(i % d->world.width); d->tiles[i].y = uint8_t(i / d->world.width);
    }
    for (int i = 0; i < count; ++i) {
        auto& t = d->territories[size_t(i)].data;
        t.index = uint16_t(i + 1); t.owner = -1; t.terrain = 1;
        t.population = 1000; t.morale = 100; t.knownPopulation = 777;
        t.numTiles = 1; t.tiles[0].raw = uint32_t((i % d->world.width) | ((i / d->world.width) << 16));
        t.centerTile = 0; d->tiles[size_t(i)].territory = int16_t(i + 1);
        for (int s = 0; s < 36; ++s) {
            t.sites[s].unk_00 = uint16_t((s % 6) | ((s / 6) << 8));
            t.sites[s].terrainFlags = 1;
            std::memset(t.sites[s].unk_18, 0xaa, sizeof(t.sites[s].unk_18));
        }
    }
    return d;
}
void adjacent(save::Document& d, uint32_t a, uint32_t b) {
    d.territories[a - 1].data.adjacency[b >> 4] |= uint16_t(1u << (b & 15));
    d.territories[b - 1].data.adjacency[a >> 4] |= uint16_t(1u << (a & 15));
}
Building& building(save::Document& d, int territory, int site, int type = 1) {
    Building b{}; b.id = uint16_t(100 + d.buildings.size()); b.type = uint8_t(type);
    b.category = data::kBuildingTypes[type].category;
    b.territory = int16_t(territory); b.site = int8_t(site);
    d.territories[size_t(territory - 1)].data.sites[site].building.raw = b.id;
    d.buildings.push_back(b); return d.buildings.back();
}
Army& unit(save::Document& d, int territory, int owner, int type, bool foreign = false) {
    Army a{}; a.id = uint16_t(700 + d.armies.size()); a.type = uint8_t(type); a.owner = int8_t(owner);
    a.territory.raw = a.dest.raw = a.origin.raw = uint32_t(territory);
    auto& t = d.territories[size_t(territory - 1)].data;
    auto& head = foreign ? t.foreignArmies.raw : t.armies.raw;
    a.next.raw = head;
    for (auto& old : d.armies) if (old.id == head) old.prev.raw = a.id;
    head = a.id; d.armies.push_back(a); return d.armies.back();
}
std::vector<uint8_t> snapshot(const save::Document& d) {
    std::vector<uint8_t> result; save::Error error;
    if (!save::encode(d, result, error)) throw std::runtime_error("fixture encoding: " + error.message);
    for (const auto& record : d.territories) {
        const auto* p = raw(record.data);
        result.insert(result.end(), p + kTerritorySavedBytes, p + sizeof(Territory));
        for (const auto& q : record.queues) for (const auto& n : q) {
            const auto* next = reinterpret_cast<const uint8_t*>(&n.next);
            result.insert(result.end(), next, next + sizeof(n.next));
        }
    }
    return result;
}
std::unique_ptr<save::Document> rebuild(const save::Document& d, LoadIntelligenceReport& report,
                                        LoadIntelligenceContext context = {}) {
    const auto before = snapshot(d);
    auto result = fixture(); save::Error error{save::ErrorCode::Io, 99, "previous"};
    if (!simulation::rebuildLoadIntelligence(d, context, *result, report, error)) throw std::runtime_error(error.message);
    require(error.code == save::ErrorCode::None && error.offset == 0 && error.message.empty(), "success clears previous error");
    require(snapshot(d) == before, "input document remains unchanged");
    require(report.detectionRebuilt && report.visibilityRebuilt && report.buildingIntelligenceRebuilt &&
            report.populationKnownRebuilt && report.contactDiscoverySkippedOnLoad, "report distinguishes reconstruction and deliberately skipped contact discovery");
    return result;
}

void snapshotsAndPopulation() {
    auto d = fixture(1); auto& t = d->territories[0].data;
    t.owner = 0; t.flags = 0x2040; t.population = 32767; t.morale = -128;
    put(raw(t) + 0x36, uint16_t(0xab00));
    auto& small = building(*d, 1, 0); small.race = 6; small.turnsLeft = -258;
    small.labor[0] = -3; small.labor[1] = 0x12345678; small.labor[4] = -2147483647 - 1;
    t.sites[0].terrainFlags = 0x3001; raw(t.sites[0])[0x10] = 0x87; t.sites[0].value = 0x44;
    auto& farm = building(*d, 1, 14, 5); farm.race = 4; farm.turnsLeft = 0x1234;
    for (int k = 0; k < 5; ++k) farm.labor[k] = 10 * (k + 1);
    t.sites[14].terrainFlags = 0x1001; t.sites[9].terrainFlags = 0x4001;
    auto& platform = building(*d, 1, 25, 38); platform.race = 2; platform.labor[1] = 77;
    t.sites[1].terrainFlags = 0x60ff;
    t.sites[35].terrainFlags = 0x4100; // bit0100 suppresses the +5 branch, even at edge.
    LoadIntelligenceReport report; auto result = rebuild(*d, report);
    const auto& out = result->territories[0].data;
    require(raw(out.sites[0])[0x19] == 6 && raw(out.sites[0])[0x1a] == 1 && raw(out.sites[0])[0x1b] == 0xfe &&
            get<int32_t>(raw(out.sites[0]) + 0x1e) == -3 && get<int32_t>(raw(out.sites[0]) + 0x22) == 0x12345678,
            "size-one cache copies race/type, low signed-turn byte and full signed32 labor");
    require(raw(out.sites[0])[0x1c] == 0x87 && get<uint16_t>(raw(out.sites[0]) + 0x32) == 0x3001 &&
            raw(out.sites[0])[0x18] == 0xaa && raw(out.sites[0])[0x1d] == 0xaa,
            "cache road copies Site+10, flags copies +02, unrelated +18/+1d survive");
    require(raw(out.sites[14])[0x1a] == 0xaa && get<uint32_t>(raw(out.sites[14]) + 0x1e) == 0xaaaaaaaa &&
            raw(out.sites[25])[0x1a] == 0xaa, "size2 and size5 anchors preserve their prior intelligence");
    require(raw(out.sites[9])[0x19] == 4 && raw(out.sites[9])[0x1a] == 5 && raw(out.sites[9])[0x1b] == 0x34 &&
            get<int32_t>(raw(out.sites[9]) + 0x2e) == 50, "4000 cell copies anchor at site+5");
    require(raw(out.sites[1])[0x1a] == 38 && get<int32_t>(raw(out.sites[1]) + 0x22) == 77,
            "6000 cell copies platform anchor at site+24");
    require(raw(out.sites[35])[0x1a] == 0 && raw(out.sites[35])[0x19] == 0xaa &&
            raw(out.sites[35])[0x1b] == 0xaa && get<int32_t>(raw(out.sites[35]) + 0x1e) == 0,
            "empty cell clears only cached type/labor, not stale race/turn bytes");
    require(report.sitesCopied == 3 && report.sitesCleared == 31, "cache report counts persistent sites, not an extra zeroed pool slot");
    require(get<uint16_t>(raw(out) + 0x36) == 0xab46 && out.knownPopulation == 32767 && out.flags == 0x2000,
            "unavailable326 narrows to70 in LOW byte only, population is copied, only flag40 cleared");
    struct Case { int16_t population; int8_t morale; uint8_t unavailable; };
    for (const Case c : {Case{1000,100,0}, Case{1000,0,8}, Case{1000,1,7}, Case{1000,11,6},
                         Case{1000,127,0}, Case{-1000,-128,0}, Case{-1000,100,0}, Case{0,0,0}}) {
        t.population = c.population; t.morale = c.morale;
        result = rebuild(*d, report);
        require(raw(result->territories[0].data)[0x36] == c.unavailable &&
                result->territories[0].data.knownPopulation == c.population &&
                result->territories[0].data.morale == c.morale, "signed labor oracle updates intelligence without applying labor/morale normalization");
    }
}

void detectionOracles() {
    auto d = fixture(6);
    for (uint32_t i = 1; i < 6; ++i) adjacent(*d, i, i + 1);
    d->territories[0].data.owner = 0;
    auto& scanner = building(*d, 1, 0); scanner.category = 12;
    for (auto& r : d->territories) r.data.flags = 0x4000;
    LoadIntelligenceReport report; auto result = rebuild(*d, report);
    constexpr std::array<int16_t,6> expectedCost{0,1,2,3,4,1000};
    constexpr std::array<uint8_t,6> expectedThreshold{9,9,9,10,11,12};
    for (size_t i = 0; i < 6; ++i) {
        const auto& t = result->territories[i].data;
        require(distance(*result, i + 1) == expectedCost[i] && t.unk_6d[0] == expectedThreshold[i],
                "range4 detection produces independent distance/threshold oracle");
        require(bool(t.flags & 0x2000) == (i < 5) && (t.flags & 0x4000), "flags rebuilt only for players having detector sources");
    }
    require(result->territories[2].data.visibility[0] == 0 && result->territories[1].data.visibility[0] == 3,
            "detection radius is not itself world visibility");
    d->techs[12].knownMask = 1;
    result = rebuild(*d, report);
    require(distance(*result, 6) == 5 && result->territories[5].data.unk_6d[0] == 11 &&
            result->territories[4].data.unk_6d[0] == 10, "004fbe04 is technology12, increasing range to5");
    d->techs[12].knownMask = 0; d->techs[24].knownMask = 1;
    result = rebuild(*d, report);
    require(distance(*result, 6) == 1000, "do not substitute technology24 based on its suggestive name");
    d->territories[5].data.owner = 0;
    building(*d, 6, 0).category = 8;
    result = rebuild(*d, report);
    require(report.detectorSources == 2 && distance(*result, 1) == 1000 && distance(*result, 6) == 0 &&
            !(result->territories[0].data.flags & 0x2000) && result->territories[0].data.unk_6d[0] == 9,
            "threshold takes min across sources, but flags/distance preserve LAST source, not union");
    auto& carrier = unit(*d, 3, 0, 14); carrier.territory.raw = 1; carrier.unitClass = 0;
    result = rebuild(*d, report);
    require(report.detectorSources == 3 && distance(*result, 3) == 0 && distance(*result, 1) == 2,
            "unit TYPE14 detected in physical order after buildings, using current+3c not turn-start+38");
    carrier.type = 29; carrier.unitClass = 14;
    result = rebuild(*d, report);
    require(report.detectorSources == 2, "unit CLASS14 alone does not create a detector source");

    d = fixture(2); adjacent(*d, 1, 2); d->options.allowAlliances = 1;
    d->territories[0].data.owner = 0; d->territories[1].data.owner = 1;
    building(*d, 1, 0).category = 12;
    d->players[0].relations[1] = 1;
    result = rebuild(*d, report); require(distance(*result, 2) == 1000, "directional pact1 blocks scanning across hostile target");
    d->players[0].relations[1] = 0; d->players[1].relations[0] = 1;
    result = rebuild(*d, report); require(distance(*result, 2) == 1, "reverse-only pact is not silently made symmetric");
    d->players[0].relations[1] = 2;
    auto& city = building(*d, 2, 0, 37);
    result = rebuild(*d, report); require(distance(*result, 2) == 1000, "pact2 without full alliance blocks completed-city target");
    city.turnsLeft = 1;
    result = rebuild(*d, report); require(distance(*result, 2) == 1, "unfinished city does not block detection");
    city.turnsLeft = 0; d->players[0].relations[1] = 0x10;
    result = rebuild(*d, report); require(distance(*result, 2) == 1, "full alliance implies2 but not1, and waives city blockade");
    d->territories[1].data.flags |= 0x100;
    result = rebuild(*d, report); require(distance(*result, 2) == 1000, "target NoTiles bit blocks propagation");
    d->buildings[0].turnsLeft = 1;
    put(raw(d->territories[0].data) + 0xa70, int16_t(321));
    d->territories[0].data.flags = 0x2000;
    result = rebuild(*d, report);
    require(report.detectorSources == 0 && distance(*result, 1) == 321 &&
            (result->territories[0].data.flags & 0x2000) && result->territories[0].data.unk_6d[0] == 12,
            "without sources thresholds reset12 but flags/distance are not blanket-cleared");
}

void visibilityOracles() {
    auto d = fixture(3); adjacent(*d, 1, 2); adjacent(*d, 2, 3);
    d->territories[2].data.owner = 0;
    put(d->territories[0].data.unk_8b0, uint32_t(1));
    d->territories[0].data.exploredMask = 0x87654321;
    LoadIntelligenceReport report; auto result = rebuild(*d, report);
    require(result->territories[0].data.visibility[0] == 0 && result->territories[1].data.visibility[0] == 3 &&
            result->territories[2].data.visibility[0] == 4, "ordinary ownership sees self4, adjacent3, not distance-two territory");
    auto& air = unit(*d, 3, 0, 28);
    result = rebuild(*d, report);
    require(result->territories[0].data.visibility[0] == 3, "type28 AirCommand on a second-hop territory grants visibility3");
    air.type = 27;
    result = rebuild(*d, report);
    require(result->territories[0].data.visibility[0] == 0, "other unit type is not a two-hop scanner");
    d->options.allowAlliances = 1; d->players[0].relations[1] = 4;
    result = rebuild(*d, report);
    require(result->territories[2].data.visibility[1] == 3 && result->territories[2].data.visibility[0] == 4,
            "directional vision pact shares3, not owner4, with receiver");
    d->players[0].relations[1] = 0; d->players[1].relations[0] = 4;
    result = rebuild(*d, report);
    require(result->territories[2].data.visibility[1] == 0, "reverse vision pact is not equivalent");
    unit(*d, 1, 1, 1, true);
    result = rebuild(*d, report);
    require(result->territories[0].data.visibility[1] == 3 && result->territories[1].data.visibility[1] == 3,
            "foreign-list unit grants visibility at its territory and usable adjacent territory");
    d->territories[0].data.flags |= 0x100;
    result = rebuild(*d, report);
    require(result->territories[0].data.visibility[1] == 3 && result->territories[1].data.visibility[1] == 0,
            "direct foreign unit ignores its target NoTiles flag, neighboring visibility requires usable territory");

    d = fixture(1);
    d->techs[31].knownMask = 4;
    result = rebuild(*d, report); require(result->territories[0].data.visibility[2] == 2, "orbital tech31 grants knowledge2");
    raw(d->territories[0].data)[0x997] = 4;
    result = rebuild(*d, report); require(result->territories[0].data.visibility[2] == 0, "territory jammer bit suppresses orbital knowledge");
    raw(d->territories[0].data)[0x997] = 0; d->options.netFlags = 1;
    result = rebuild(*d, report); require(result->territories[0].data.visibility[2] == 0, "netFlags bit0 gates orbital visibility even in owned offline computation");
    d->raceStats.v[52][2] = -1;
    result = rebuild(*d, report); require(result->territories[0].data.visibility[2] == 2, "nonzero signed racial row52 also grants knowledge2");
    d->raceStats.v[52][2] = 0; d->techs[31].knownMask = 0;
    building(*d, 1, 0, 37);
    result = rebuild(*d, report);
    for (uint8_t value : result->territories[0].data.visibility) require(value == 1, "completed city gives every perspective base knowledge1 regardless flags");
    d->buildings[0].turnsLeft = 1;
    result = rebuild(*d, report, {1,false});
    require(result->territories[0].data.visibility[0] == 2 && result->territories[0].data.visibility[1] == 0,
            "fog cheat1 explores type1 human players only");
    result = rebuild(*d, report, {2,false});
    require(result->territories[0].data.visibility[0] == 3 && result->territories[0].data.visibility[1] == 0,
            "fog cheat2 shows type1 human players but does not make ownership4");
    d->options.allowAlliances = 1; d->players[0].relations[1] = 4;
    put(d->territories[0].data.unk_8b0, uint32_t(1));
    result = rebuild(*d, report, {0,true});
    require(result->territories[0].data.visibility[0] == 4 && result->territories[0].data.visibility[1] == 3 &&
            get<uint32_t>(result->territories[0].data.unk_8b0) == 1,
            "debug reveal is local4/shared3, but tautological shrine OR does not invent discovery bits");

    // Original queries ALL seven perspectives. Saved inactive slots can have
    // race=-1: MOVSX at0046e16e then WORD[55a0d8+race*2] at0046e176 reads the
    // preceding owned row's last element. It does not substitute a valid race.
    d = fixture(1); d->players[6].type = 0; d->players[6].race = -1;
    d->raceStats.v[52][0] = 7;
    result = rebuild(*d, report);
    require(result->territories[0].data.visibility[6] == 0 && result->territories[0].data.visibility[0] == 2,
            "inactive sentinel race is not normalized to race0 and does not skip perspective computation");
    d->raceStats.v[51][6] = -9;
    result = rebuild(*d, report);
    require(result->territories[0].data.visibility[6] == 2 && result->players[6].race == -1,
            "inactive race=-1 reads the signed previous-row word without changing the saved race");
    d->players[6].race = -128; d->raceStats.v[33][5] = 1;
    result = rebuild(*d, report);
    require(result->territories[0].data.visibility[6] == 2, "signed race minimum still addresses a word inside RaceStats");
    d->players[6].race = 83; d->raceStats.v[63][6] = 1;
    result = rebuild(*d, report);
    require(result->territories[0].data.visibility[6] == 2, "last owned racial-stat address is admitted without out-of-bounds indexing");
}

void failuresAndIsolation() {
    auto d = fixture(2); adjacent(*d, 1, 2); d->territories[0].data.owner = 0;
    building(*d, 1, 0).category = 12;
    d->localList = {0,0xdeadbeef}; d->trailing = {0,0x80,0xff};
    d->events.resize(1); d->options.eventCount = 1;
    d->events[0].record.textLen = 3; d->events[0].text = {'A',0,0xff};
    d->territories[0].data.production[8] = -53;
    LoadIntelligenceReport report; auto result = rebuild(*d, report);
    const auto input = snapshot(*d), prior = snapshot(*result); const auto oldReport = report;
    const auto failure = [&](LoadIntelligenceContext context = {}) {
        save::Error error;
        require(!simulation::rebuildLoadIntelligence(*d, context, *result, report, error) &&
                error.code != save::ErrorCode::None && !error.message.empty() && report == oldReport &&
                snapshot(*result) == prior, "failure preserves prior report and full destination including unsaved tails");
    };
    failure({-1,false}); failure({3,false});
    d->territories[0].data.sites[35].terrainFlags = 0x4000; failure();
    d->territories[0].data.sites[35].terrainFlags = 1;
    d->territories[0].data.sites[20].terrainFlags = 0x6000; failure();
    d->territories[0].data.sites[20].terrainFlags = 1;
    d->territories[0].data.sites[5].terrainFlags = 0x4000; failure();
    d->territories[0].data.sites[5].terrainFlags = 1;
    d->players[6].race = 84; failure();
    d->players[6].race = 127; failure(); d->players[6].race = 6;
    d->territories[0].data.owner = 7; failure(); d->territories[0].data.owner = 0;
    d->territories[0].data.sites[1].building.raw = 9999; failure();
    d->territories[0].data.sites[1].building.raw = 0;
    require(snapshot(*d) == input, "late failed cache/visibility passes leave source untouched");
    auto overrun = fixture(111); save::Error error;
    require(!simulation::rebuildLoadIntelligence(*overrun, {}, *result, report, error) && report == oldReport &&
            snapshot(*result) == prior, "N111 original off-by-one pool overrun explicitly rejected");
    auto boundary = fixture(110); auto safe = rebuild(*boundary, report);
    require(safe->territories.size() == 110, "last safe fixed-pool population is accepted");
    auto badUnit = std::make_unique<save::Document>(*d);
    unit(*badUnit, 1, 7, 14);
    require(!simulation::rebuildLoadIntelligence(*badUnit, {}, *result, report, error), "detector owner must be a valid player index");
    badUnit->armies[0].owner = 0; badUnit->armies[0].dest.raw = 0;
    require(!simulation::rebuildLoadIntelligence(*badUnit, {}, *result, report, error), "detector current territory cannot be a null original pointer");

    std::vector<uint8_t> gsBefore(sizeof(gs)), ggBefore(sizeof(gg));
    std::memcpy(gsBefore.data(), &gs, sizeof(gs)); std::memcpy(ggBefore.data(), &gg, sizeof(gg));
    const auto low = rtl::seed(), high = rtl::seedHi();
    auto again = rebuild(*d, report); require(report == oldReport && snapshot(*again) == prior, "deterministic result from identical source");
    auto alias = std::make_unique<save::Document>(*d);
    require(simulation::rebuildLoadIntelligence(*alias, {}, *alias, report, error) && snapshot(*alias) == prior,
            "source/destination alias uses a private candidate");
    failure({3,false});
    require(std::memcmp(gsBefore.data(), &gs, sizeof(gs)) == 0 && std::memcmp(ggBefore.data(), &gg, sizeof(gg)) == 0 &&
            rtl::seed() == low && rtl::seedHi() == high, "no global state, context or RNG touched on success/failure");
    require(result->events[0].text == d->events[0].text && result->localList == d->localList &&
            result->options.turn == 81 && result->options.nextGlobalId == 987 && result->options.gameId == 313 &&
            result->territories[0].data.production[8] == -53 && result->buildings[0].flags == d->buildings[0].flags,
            "no event fabrication, labor/production, counters or turns changed outside intelligence contract");
}

void corpus(const std::filesystem::path& directory) {
    namespace fs = std::filesystem;
    if (directory.empty()) { std::cout << "load intelligence optional corpus: no directory\n"; return; }
    size_t count = 0, unsupported = 0;
    const auto inspect = [&](const save::Document& d, const std::string& label) {
        try {
            if (d.territories.size() == 111) {
                auto destination = fixture(); const auto before = snapshot(*destination);
                LoadIntelligenceReport report; save::Error error;
                require(!simulation::rebuildLoadIntelligence(d, {}, *destination, report, error) && snapshot(*destination) == before,
                        "corpus N111 must reject unsupported original memory-overrun domain");
                ++unsupported; return;
            }
            LoadIntelligenceReport first, second;
            auto a = rebuild(d, first); auto b = rebuild(d, second);
            require(snapshot(*a) == snapshot(*b) && first == second, "corpus deterministic independent candidates");
            require(a->events.size() == d.events.size() && a->armies.size() == d.armies.size(),
                    "load deliberately skips contacts/events/deletion cascades");
            ++count;
        } catch (const std::exception& exception) { throw std::runtime_error(label + ": " + exception.what()); }
    };
    for (const char* relative : {"TUTORIAL.SAV", "Saves/AUTOSAVE.SAV", "Campaign/AUTOSAVE.CPN", "Campaign/ChCht001.CPN"}) {
        const auto path = directory / relative; if (!fs::is_regular_file(path)) continue;
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
    std::cout << "load intelligence optional corpus: " << count << " reconstructed, " << unsupported << " unsupported N111\n";
}
} // namespace
int main(int argc, char** argv) {
    try {
        snapshotsAndPopulation(); detectionOracles(); visibilityOracles(); failuresAndIsolation();
        corpus(argc > 1 ? std::filesystem::path(argv[1]) : std::filesystem::path{});
        std::cout << "load_intelligence: snapshot/detection/visibility oracles, load contact skip, rollback and isolation passed\n";
        return 0;
    } catch (const std::exception& exception) {
        std::cerr << "load_intelligence: " << exception.what() << '\n'; return 1;
    }
}
