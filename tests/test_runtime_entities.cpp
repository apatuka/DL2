// Owned structural entity edits; these are NOT construction, combat or disband.
#include "game/runtime_state.h"
#include "game/save_files.h"
#include "game/data_tables.h"
#include "game/globals.h"
#include "game/rtl_compat.h"

#include <algorithm>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace {
using namespace dl2;
namespace rt = runtime;
namespace fs = std::filesystem;
using save::Document;

void require(bool condition, const char* message) {
    if (!condition) throw std::runtime_error(message);
}
void diagnostic(const save::Error& e) {
    require(e.code != save::ErrorCode::None && !e.message.empty(), "failure lacks diagnostic");
}
void cleared(const save::Error& e) {
    require(e.code == save::ErrorCode::None && !e.offset && e.message.empty(), "success did not clear error");
}
std::vector<uint8_t> encoded(const Document& d) {
    save::Error e; std::vector<uint8_t> bytes;
    if (!save::encode(d, bytes, e)) throw std::runtime_error("encode: " + e.message);
    return bytes;
}
Building building(uint16_t id, int territory = 1, int site = 0) {
    Building b{}; b.id = id; b.type = 1; b.category = 17; b.race = 0;
    b.territory = int16_t(territory); b.site = int8_t(site); b.flags = 6;
    b.task[1] = 20; b.labor[1] = 2; b.cost[7] = 17; b.taskData[3][10] = -909;
    b.unk_31[2] = 0xe1; b.unk_36[7] = 0xc7;
    return b;
}
Army army(uint16_t id, int owner = 0, int territory = 1) {
    Army a{}; a.id = id; a.type = 1; a.unitClass = 1; a.owner = int8_t(owner);
    a.health = 100; a.strength = 3;
    a.territory.raw = a.dest.raw = a.origin.raw = uint32_t(territory);
    std::memset(a.name, 'x', sizeof(a.name)); // Valid length-delimited, no required NUL.
    a.unk_04 = 0xa5c3; a.unk_2e[7] = 0xee;
    return a;
}
std::unique_ptr<Document> fixture(int territories = 2, bool populated = true) {
    auto d = std::make_unique<Document>();
    std::memcpy(d->header.text, save::kHeaderText, sizeof(save::kHeaderText));
    d->header.version = kSaveVersion; d->header.minusOne = -1; d->header.pad[19] = 0xa5;
    d->options.numPlayers = 2; d->options.turn = 173; d->options.gameSeed = 0x12345678;
    d->world.width = uint8_t(territories); d->world.height = 1;
    d->world.numTerritories = uint16_t(territories); d->world.rngSeed = 0x87654321;
    for (size_t p = 0; p < kMaxPlayers; ++p) {
        d->players[p].index = uint8_t(p); d->players[p].race = int8_t(p);
        d->players[p].credits = 1000 + int32_t(p); d->players[p].taxLevel = 2;
        d->raceStats.v[24][p] = 100; d->raceStats.v[26][p] = 100;
        d->ministerJobs[p].resize(1); d->ministerJobs[p][0].type = 1;
    }
    d->players[0].type = 1; d->players[1].type = 3;
    d->tiles.resize(size_t(territories)); d->territories.resize(size_t(territories));
    for (int i = 0; i < territories; ++i) {
        auto& t = d->territories[size_t(i)].data;
        t.index = uint16_t(i + 1); t.owner = int8_t(i == 1 ? 1 : 0); t.terrain = 1;
        t.population = 500; t.morale = 100; t.knowledge = 100;
        t.numTiles = 1; t.tiles[0].raw = uint32_t(i); t.materials[2] = 200;
        for (int s = 0; s < kNumSites; ++s) {
            t.sites[s].unk_00 = uint16_t((s % 6) | ((s / 6) << 8));
        }
        auto& tile = d->tiles[size_t(i)]; tile.x = uint8_t(i); tile.territory = int16_t(i + 1);
    }
    d->localList = {0xdeadbeef, 7};
    d->scratchJob1.armies[0].raw = 0xface1234; d->scratchJob2.destination.raw = 0xcafe1234;
    d->jobs[6][49].armies[15].raw = 0xdead1000; // Historical word, not a file ID.
    d->events.resize(1); d->options.eventCount = 1;
    d->events[0].record = {12, 4, 0, 99}; d->events[0].text = {'a', 0, 'b', 0xff};
    d->trailing = {0xca, 0xfe, 0, 0xff};
    if (populated) {
        d->buildings = {building(100, 1, 0), building(200, 1, 1)};
        d->buildings[0].next.raw = 200; d->buildings[1].prev.raw = 100;
        d->territories[0].data.sites[0].building.raw = 100;
        d->territories[0].data.sites[1].building.raw = 200;
        d->armies = {army(1000), army(2000), army(3000, 1)};
        d->armies[0].next.raw = 2000; d->armies[1].prev.raw = 1000;
        d->territories[0].data.armies.raw = 1000;
        d->territories[0].data.foreignArmies.raw = 3000;
    }
    return d;
}
void prepare(rt::State& s, const Document& d) {
    save::Error e;
    if (!s.prepare(d, e)) throw std::runtime_error("prepare: " + e.message);
    cleared(e);
}
rt::EntityEditReport sentinel() {
    rt::EntityEditReport r;
    r.kind = rt::EntityKind::Army; r.operation = rt::EntityEditOperation::Retired;
    r.id = 65000; r.territory = 81; r.site = 33;
    r.beforeCount = 999; r.afterCount = 777; r.previousId = 123; r.nextId = 456;
    return r;
}
template<class Operation> void rejected(rt::State& state, Operation&& operation) {
    const auto bytes = state.document() ? encoded(*state.document()) : std::vector<uint8_t>{};
    const auto stage = state.stage(); const auto* document = state.document();
    auto report = sentinel(); const auto oldReport = report;
    save::Error error;
    require(!operation(report, error), "unsafe entity operation unexpectedly succeeded");
    diagnostic(error);
    require(report == oldReport && state.stage() == stage && state.document() == document,
            "failed entity operation changed report, phase or owned document");
    if (document) require(encoded(*document) == bytes, "failed entity operation changed source bytes");
}
void rejectBuildingInsert(rt::State& s, const Building& b) {
    auto created = s.buildingById(100); const auto previous = created;
    rejected(s, [&](auto& r, auto& e) { return s.insertBuilding(b, created, r, e); });
    require(created == previous, "failed building insert changed output handle");
}
void rejectArmyInsert(rt::State& s, const Army& a) {
    auto created = s.armyById(1000); const auto previous = created;
    rejected(s, [&](auto& r, auto& e) { return s.insertArmy(a, created, r, e); });
    require(created == previous, "failed army insert changed output handle");
}
void phaseGates(rt::State& s) {
    require(s.stage() == rt::Stage::EntitiesEdited, "entity edits must enter explicit partial stage");
    auto destination = fixture(); const auto bytes = encoded(*destination);
    save::Error e; simulation::TaxPlan taxes; simulation::EnergyPlan energy;
    simulation::LaborBalancePlan labor;
    require(!s.capture(*destination, e), "edited state was exported as resumed gameplay"); diagnostic(e);
    require(encoded(*destination) == bytes, "failed edited capture changed destination");
    const auto before = encoded(*s.document());
    require(!s.collectTaxes(taxes, e) && !s.consumeEnergy(energy, e) &&
            !s.normalizeLabor(labor, e) && !s.advanceTurn(e), "entity edits chained unsupported gameplay phases");
    require(encoded(*s.document()) == before && s.stage() == rt::Stage::EntitiesEdited,
            "rejected phase changed entity-edited document");
}
void assertGraph(const rt::State& s) {
    const auto& d = *s.document();
    for (const auto& b : d.buildings) {
        const auto h = s.buildingById(b.id); const auto* links = s.buildingLinks(h);
        require(s.building(h) && links && links->territory == s.territoryByIndex(uint32_t(b.territory)),
                "building handle or location is stale after graph rebuild");
        require(links->previous == s.buildingById(b.prev.raw) && links->next == s.buildingById(b.next.raw),
                "building graph differs from edited file-ID links");
        require(s.graph().territories[size_t(b.territory - 1)].sites[size_t(b.site)] == h,
                "site has stale building handle");
    }
    for (const auto& a : d.armies) {
        const auto h = s.armyById(a.id); const auto* links = s.armyLinks(h);
        require(s.army(h) && links && links->current == s.territoryByIndex(a.dest.raw),
                "army handle or current location is stale after graph rebuild");
        require(links->previous == s.armyById(a.prev.raw) && links->next == s.armyById(a.next.raw),
                "army graph differs from edited file-ID links");
    }
}

void buildingLifecycle() {
    auto d = fixture(); const auto original = encoded(*d);
    rt::State s; prepare(s, *d); save::Error e;
    const auto first = s.buildingById(100), survivor = s.buildingById(200);
    const auto territory = s.territoryByIndex(1);
    const auto tile = s.tileByIndex(1);
    rt::BuildingHandle created; auto r = sentinel(); auto b = building(65535, 1, 5);
    const Building input = b;
    require(s.insertBuilding(b, created, r, e), "valid building insertion failed"); cleared(e);
    require(std::memcmp(&b, &input, sizeof(b)) == 0, "building insertion changed caller record");
    require(r.kind == rt::EntityKind::Building && r.operation == rt::EntityEditOperation::Inserted &&
            r.id == 65535 && r.territory == 1 && r.site == 5 && r.beforeCount == 2 && r.afterCount == 3,
            "building insertion report differs");
    require(s.building(created) && s.building(created)->cost[7] == 17 &&
            s.building(created)->taskData[3][10] == -909, "insertion rewrote caller's complete record");
    auto expected = std::make_unique<Document>(*d);
    auto linked = b; linked.prev.raw = 200;
    expected->buildings.back().next.raw = b.id; expected->buildings.push_back(linked);
    expected->territories[0].data.sites[5].building.raw = b.id;
    require(encoded(*s.document()) == encoded(*expected), "building insertion changed bytes beyond list/site/payload");
    require(r.previousId == 200 && r.nextId == 0, "building insertion is not original tail append");
    require(s.building(first) && s.building(survivor) && s.territory(territory) && s.tile(tile),
            "insertion invalidated surviving/static handles");
    assertGraph(s); phaseGates(s);
    require(s.retireBuilding(created, r, e), "retire inserted building failed"); cleared(e);
    require(r.operation == rt::EntityEditOperation::Retired && r.id == 65535 &&
            r.beforeCount == 3 && r.afterCount == 2, "building retirement report differs");
    require(!s.building(created) && !s.buildingLinks(created), "retired building handle still resolves");
    require(encoded(*s.document()) == original && encoded(*d) == original,
            "insert/retire changed unrelated archive bytes or input source");
    rejected(s, [&](auto& out, auto& err) { return s.retireBuilding(created, out, err); });
    require(s.retireBuilding(first, r, e), "retire original building head failed");
    require(s.building(survivor) && s.building(survivor)->id == 200 &&
            s.buildingById(200) == survivor, "dense erase broke survivor identity");
    rt::BuildingHandle replacement; b = building(100, 1, 0);
    require(s.insertBuilding(b, replacement, r, e), "reuse building ID/site failed");
    require(replacement != first && !s.building(first) && !s.buildingLinks(first),
            "reused building ID or pool slot resurrected stale handle");
    require(s.building(survivor) && s.territory(territory) && s.tile(tile), "slot reuse invalidated survivors");
    assertGraph(s);
}

void armyLifecycle() {
    auto d = fixture(); const auto original = encoded(*d);
    rt::State s; prepare(s, *d); save::Error e; auto r = sentinel();
    const auto first = s.armyById(1000), survivor = s.armyById(2000), foreign = s.armyById(3000);
    rt::ArmyHandle inserted; auto a = army(65535); const auto input = a;
    require(s.insertArmy(a, inserted, r, e), "own army insertion failed"); cleared(e);
    require(std::memcmp(&a, &input, sizeof(a)) == 0 && s.army(inserted)->unk_04 == 0xa5c3,
            "army insertion changed supplied payload");
    require(r.kind == rt::EntityKind::Army && r.operation == rt::EntityEditOperation::Inserted &&
            r.id == 65535 && r.territory == 1 && r.beforeCount == 3 && r.afterCount == 4,
            "army insertion report differs");
    require(s.document()->territories[0].data.armies.raw == 65535 &&
            s.army(inserted)->next.raw == 1000 && s.army(first)->prev.raw == 65535,
            "own insertion did not link at territory head");
    auto expected = std::make_unique<Document>(*d);
    auto linked = a; linked.next.raw = 1000;
    expected->armies[0].prev.raw = a.id; expected->armies.push_back(linked);
    expected->territories[0].data.armies.raw = a.id;
    require(encoded(*s.document()) == encoded(*expected), "army insertion changed bytes beyond list/head/payload");
    require(r.previousId == 0 && r.nextId == 1000 && r.site == -1, "army insertion neighbors/site differ");
    assertGraph(s);
    require(s.retireArmy(inserted, r, e), "retire newly inserted own army failed");
    require(encoded(*s.document()) == original, "own insert/retire altered unrelated archive bytes");
    a = army(65535, 1); require(s.insertArmy(a, inserted, r, e), "foreign army insertion failed");
    require(s.document()->territories[0].data.foreignArmies.raw == 65535 &&
            s.army(inserted)->next.raw == 3000 && s.army(foreign)->prev.raw == 65535,
            "foreign insertion updated wrong head");
    require(s.retireArmy(inserted, r, e) && encoded(*s.document()) == original,
            "foreign insert/retire did not restore exact source bytes");
    require(s.retireArmy(first, r, e), "retire original own head failed");
    require(s.army(survivor) && s.armyById(2000) == survivor && s.army(survivor)->prev.raw == 0 &&
            s.document()->territories[0].data.armies.raw == 2000, "own head retirement broke survivor");
    a = army(1000); require(s.insertArmy(a, inserted, r, e), "reuse army ID failed");
    require(inserted != first && !s.army(first) && !s.armyLinks(first), "army reuse resurrected stale handle");
    rejected(s, [&](auto& out, auto& err) { return s.retireArmy(first, out, err); });
    require(s.retireArmy(survivor, r, e) && s.army(inserted)->next.raw == 0,
            "retire own tail did not fix next");
    require(s.retireArmy(foreign, r, e) && !s.document()->territories[0].data.foreignArmies.raw,
            "retire only foreign army did not clear head");
    require(encoded(*d) == original, "army edits mutated caller's source");
    phaseGates(s); assertGraph(s);
}

void invalidInputsAndDependencies() {
    auto d = fixture(); rt::State s; prepare(s, *d);
    for (int kind = 0; kind < 9; ++kind) {
        auto b = building(900, 1, 4);
        switch (kind) {
        case 0: b.id = 0; break;
        case 1: b.id = 100; break;
        case 2: b.site = 0; break;
        case 3: b.site = 36; break;
        case 4: b.territory = 0; break;
        case 5: b.type = 48; break;
        case 6: b.prev.raw = 100; break;
        case 7: b.next.raw = 200; break;
        case 8: b.type = 5; break; // Two-site footprint not implemented here.
        }
        rejectBuildingInsert(s, b);
    }
    for (int type : {38, 39, 45, 46, 47}) {
        auto b = building(900, 1, 4); b.type = uint8_t(type); rejectBuildingInsert(s, b);
    }
    for (int kind = 0; kind < 12; ++kind) {
        auto a = army(9000);
        switch (kind) {
        case 0: a.id = 0; break;
        case 1: a.id = 1000; break;
        case 2: a.type = 0; break;
        case 3: a.type = 39; break;
        case 4: a.owner = -1; break;
        case 5: a.owner = 7; break;
        case 6: a.dest.raw = 0; break;
        case 7: a.health = 101; break;
        case 8: a.next.raw = 1000; break;
        case 9: a.prev.raw = 1000; break;
        case 10: a.cargo[2].raw = 2000; break;
        case 11: a.job = 1; break;
        }
        rejectArmyInsert(s, a);
    }
    for (int type : {12, 35, 36}) {
        auto a = army(9000); a.type = uint8_t(type); a.unitClass = data::kUnitTypes[type].unitClass;
        rejectArmyInsert(s, a);
    }
    rejected(s, [&](auto& r, auto& e) { return s.retireArmy({}, r, e); });
    rejected(s, [&](auto& r, auto& e) { return s.retireBuilding({}, r, e); });
    require(!s.army({1}) && !s.building({1}) && !s.territory({1}) && !s.tile({1}),
            "forged dense-only handles bypassed identity checks");
    for (int dependency = 0; dependency < 5; ++dependency) {
        auto dependent = fixture();
        if (dependency == 0) dependent->armies[0].cargo[0].raw = 2000;
        if (dependency == 1) dependent->armies[1].cargo[2].raw = 1000;
        if (dependency == 2) dependent->armies[0].job = 1;
        if (dependency == 3) dependent->jobs[6][49].armyIds[15] = 1000;
        if (dependency == 4) {
            dependent->ministerJobs[6].resize(2); dependent->ministerJobs[6][0].next.raw = 0xdead;
            dependent->ministerJobs[6][1].type = 13; dependent->ministerJobs[6][1].param[0] = 1000;
        }
        prepare(s, *dependent); const auto h = s.armyById(1000);
        rejected(s, [&](auto& r, auto& e) { return s.retireArmy(h, r, e); });
        require(s.army(h), "dependency rejection invalidated target handle");
    }
    // Archive validation is deliberately less strict than mutation validation.
    for (int issue = 0; issue < 5; ++issue) {
        auto incoherent = fixture();
        if (issue == 0) incoherent->armies[1].prev.raw = 0;
        if (issue == 1) incoherent->territories[0].data.foreignArmies.raw = 1000;
        if (issue == 2) incoherent->armies[0].owner = 1;
        if (issue == 3) incoherent->territories[0].data.armies.raw = 0;
        if (issue == 4) incoherent->armies[0].dest.raw = 2;
        prepare(s, *incoherent);
        rejected(s, [&](auto& r, auto& e) { return s.retireArmy(s.armyById(1000), r, e); });
    }
    auto badBuildings = fixture(); badBuildings->buildings[1].prev.raw = 0;
    prepare(s, *badBuildings);
    rejected(s, [&](auto& r, auto& e) { return s.retireBuilding(s.buildingById(100), r, e); });
    // Type 3 minister jobs reference a territory/site pair, not a building ID.
    auto siteJob = fixture();
    siteJob->ministerJobs[6].resize(2); siteJob->ministerJobs[6][0].next.raw = 0xdead;
    auto& job = siteJob->ministerJobs[6][1]; job.type = 3; job.param[0] = 1; job.param[1] = 0;
    prepare(s, *siteJob);
    rejected(s, [&](auto& r, auto& e) { return s.retireBuilding(s.buildingById(100), r, e); });
    job.param[1] = 5; prepare(s, *siteJob); rejectBuildingInsert(s, building(900, 1, 5));
    // A dangling opaque maintain-unit job must not become attached by ID reuse.
    auto futureArmy = fixture();
    futureArmy->ministerJobs[6].resize(2); futureArmy->ministerJobs[6][0].next.raw = 0xdead;
    futureArmy->ministerJobs[6][1].type = 13; futureArmy->ministerJobs[6][1].param[0] = 9000;
    prepare(s, *futureArmy); rejectArmyInsert(s, army(9000));
}

void domainAndStageGates() {
    rt::State s; save::Error e; rt::EntityEditReport report;
    rejectBuildingInsert(s, building(900, 1, 4)); rejectArmyInsert(s, army(9000));
    rejected(s, [&](auto& r, auto& error) { return s.retireArmy({}, r, error); });
    rejected(s, [&](auto& r, auto& error) { return s.retireBuilding({}, r, error); });
    auto d = fixture();
    for (int phase = 0; phase < 3; ++phase) {
        prepare(s, *d); simulation::TaxPlan taxes; simulation::EnergyPlan energy;
        simulation::LaborBalancePlan labor;
        bool applied = phase == 0 ? s.collectTaxes(taxes, e) :
                       phase == 1 ? s.consumeEnergy(energy, e) : s.normalizeLabor(labor, e);
        require(applied, "cannot prepare isolated phase for entity stage rejection");
        rejectBuildingInsert(s, building(900, 1, 4)); rejectArmyInsert(s, army(9000));
        rejected(s, [&](auto& r, auto& error) { return s.retireArmy(s.armyById(1000), r, error); });
        rejected(s, [&](auto& r, auto& error) { return s.retireBuilding(s.buildingById(100), r, error); });
    }
    for (uint16_t platform : {uint16_t(0x100), uint16_t(0x200)}) {
        auto p = fixture(); p->territories[0].data.sites[0].terrainFlags = platform;
        p->territories[0].data.sites[4].terrainFlags = platform; prepare(s, *p);
        rejectBuildingInsert(s, building(900, 1, 4));
        rejected(s, [&](auto& r, auto& error) { return s.retireBuilding(s.buildingById(100), r, error); });
    }
    for (int type : {5, 38, 39, 46, 47}) {
        auto special = fixture(); special->buildings[0].type = uint8_t(type);
        prepare(s, *special);
        rejected(s, [&](auto& r, auto& error) { return s.retireBuilding(s.buildingById(100), r, error); });
    }
    for (int type : {12, 35, 36}) {
        auto special = fixture(); special->armies[0].type = uint8_t(type);
        special->armies[0].unitClass = data::kUnitTypes[type].unitClass; prepare(s, *special);
        rejected(s, [&](auto& r, auto& error) { return s.retireArmy(s.armyById(1000), r, error); });
    }
    prepare(s, *d);
    for (uint8_t specialClass : {uint8_t(4), uint8_t(19)}) {
        auto a = army(9000); a.unitClass = specialClass; rejectArmyInsert(s, a);
    }
    auto sea = fixture(2, false); sea->territories[0].data.terrain = 0; prepare(s, *sea);
    rejectArmyInsert(s, army(9000)); // Would require transport attachment and AI callbacks.
    auto ship = army(9000); ship.type = 29; ship.unitClass = 14;
    rt::ArmyHandle shipHandle;
    require(s.insertArmy(ship, shipHandle, report, e) && s.retireArmy(shipHandle, report, e),
            "ordinary non-carrying sea unit structural lifecycle failed");
    require(encoded(*s.document()) == encoded(*sea), "sea unit lifecycle changed territory or economy");
    prepare(s, *d); rejectArmyInsert(s, ship); // Maritime unit cannot be inserted on land.

    // Interior unlink: both neighbors must reconnect, not only territory heads.
    rt::ArmyHandle extra;
    require(s.insertArmy(army(9000), extra, report, e), "cannot create interior unlink fixture");
    const auto tail = s.armyById(2000);
    require(s.retireArmy(s.armyById(1000), report, e) && s.army(extra)->next.raw == 2000 &&
            s.army(tail)->prev.raw == 9000, "interior army retirement broke neighbors");
    assertGraph(s);
}

void handleOwnershipAndReallocation() {
    auto d = fixture(); rt::State a, b; prepare(a, *d); prepare(b, *d);
    const auto ah = a.armyById(1000), bh = b.armyById(1000);
    const auto ab = a.buildingById(100), bb = b.buildingById(100);
    const auto at = a.territoryByIndex(1), bt = b.territoryByIndex(1);
    require(ah != bh && ab != bb && at != bt && !a.army(bh) && !b.army(ah) &&
            !a.building(bb) && !b.building(ab) && !a.territory(bt), "foreign handle accepted");
    rejected(a, [&](auto& r, auto& e) { return a.retireArmy(bh, r, e); });
    rejected(a, [&](auto& r, auto& e) { return a.retireBuilding(bb, r, e); });
    auto invalid = fixture(); invalid->armies[1].id = 1000; save::Error e;
    const auto before = encoded(*a.document());
    require(!a.prepare(*invalid, e) && a.army(ah) && a.building(ab) && a.territory(at) &&
            encoded(*a.document()) == before, "failed prepare invalidated live handles");
    prepare(a, *d);
    require(!a.army(ah) && !a.building(ab) && !a.territory(at), "successful prepare retained previous identity");
    const auto movedArmy = a.armyById(1000);
    const auto movedBuilding = a.buildingById(100);
    const auto movedTerritory = a.territoryByIndex(1);
    b = std::move(a);
    require(!a.document() && a.stage() == rt::Stage::Empty && !a.army(movedArmy) &&
            b.army(movedArmy) && b.building(movedBuilding) && b.territory(movedTerritory),
            "move assignment failed to transfer handle ownership");
    require(!b.army(bh) && !b.building(bb) && !b.territory(bt), "move kept destination's old handles alive");
    rt::State c(std::move(b));
    require(c.army(movedArmy) && !b.army(movedArmy) && b.stage() == rt::Stage::Empty,
            "move constructor failed to transfer handles");
    rt::EntityEditReport r; rt::ArmyHandle inserted;
    for (uint16_t id = 10000; id < 10096; ++id) {
        require(c.insertArmy(army(id), inserted, r, e), "reallocation army insertion failed");
        require(c.army(movedArmy) && c.building(movedBuilding) && c.territory(movedTerritory),
                "vector reallocation invalidated surviving handles");
    }
    assertGraph(c);
    for (uint16_t id = 10000; id < 10096; ++id)
        require(c.retireArmy(c.armyById(id), r, e), "retire reallocated army failed");
    require(encoded(*c.document()) == encoded(*d), "reallocation edits altered original records");
}

void capacities() {
    auto armySource = fixture(2, false);
    for (int i = 0; i < 558; ++i) {
        auto a = army(uint16_t(i + 1));
        a.prev.raw = i ? uint32_t(i) : 0; a.next.raw = i + 1 < 558 ? uint32_t(i + 2) : 0;
        armySource->armies.push_back(a);
    }
    armySource->territories[0].data.armies.raw = 1;
    rt::State s; prepare(s, *armySource); save::Error e; rt::EntityEditReport r; rt::ArmyHandle h;
    require(s.insertArmy(army(60000), h, r, e) && s.document()->armies.size() == 559,
            "army reserved-last-slot boundary denied the 559th active record");
    rejectArmyInsert(s, army(60001));
    require(s.retireArmy(h, r, e) && s.insertArmy(army(60001), h, r, e), "army free slot was not reusable");
    auto fullArmy = std::make_unique<Document>(*armySource);
    for (int i = 558; i < 560; ++i) {
        auto a = army(uint16_t(i + 1)); a.prev.raw = uint32_t(i);
        fullArmy->armies.back().next.raw = a.id; fullArmy->armies.push_back(a);
    }
    prepare(s, *fullArmy); // Physical 560-record saves remain inspectable.
    rejectArmyInsert(s, army(60002));
    auto buildings = fixture(34, false);
    for (int i = 0; i < 1198; ++i) {
        auto b = building(uint16_t(i + 1), i / kNumSites + 1, i % kNumSites);
        b.prev.raw = i ? uint32_t(i) : 0; b.next.raw = i + 1 < 1198 ? uint32_t(i + 2) : 0;
        buildings->territories[size_t(b.territory - 1)].data.sites[size_t(b.site)].building.raw = b.id;
        buildings->buildings.push_back(b);
    }
    prepare(s, *buildings); rt::BuildingHandle hb;
    require(s.insertBuilding(building(60000, 34, 10), hb, r, e) && s.document()->buildings.size() == 1199,
            "building reserved-last-slot boundary denied the 1199th record");
    rejectBuildingInsert(s, building(60001, 34, 11));
    require(s.retireBuilding(hb, r, e) && s.insertBuilding(building(60001, 34, 11), hb, r, e),
            "building free slot was not reusable");
    for (int i = 1198; i < 1200; ++i) {
        auto b = building(uint16_t(i + 1), i / kNumSites + 1, i % kNumSites); b.prev.raw = uint32_t(i);
        buildings->buildings.back().next.raw = b.id;
        buildings->territories[size_t(b.territory - 1)].data.sites[size_t(b.site)].building.raw = b.id;
        buildings->buildings.push_back(b);
    }
    prepare(s, *buildings); rejectBuildingInsert(s, building(60002, 34, 12));
}

std::vector<std::string> scenarioNames(const fs::path& path) {
    const auto size = fs::file_size(path);
    require(size >= 4 && size <= save::kMaxFileBytes, "invalid corpus index size");
    std::ifstream input(path, std::ios::binary); uint8_t raw[4]{};
    require(bool(input.read(reinterpret_cast<char*>(raw), 4)), "cannot read corpus index");
    const uint32_t count = uint32_t(raw[0]) | uint32_t(raw[1]) << 8 | uint32_t(raw[2]) << 16 | uint32_t(raw[3]) << 24;
    require(count <= (size - 4) / 12, "truncated corpus index");
    std::vector<std::string> names;
    for (uint32_t i = 0; i < count; ++i) {
        char entry[12]{}; require(bool(input.read(entry, 12)), "cannot read corpus index entry");
        names.emplace_back(entry, std::find(entry, entry + 8, '\0'));
    }
    return names;
}
void corpusOne(const Document& d, size_t& edited, size_t& domainRejected) {
    const auto original = encoded(d); rt::State s, other; prepare(s, d); prepare(other, d);
    auto captured = std::make_unique<Document>(); save::Error e;
    require(s.capture(*captured, e) && encoded(*captured) == original, "corpus preparation is not byte exact");
    assertGraph(s);
    for (const auto& a : d.armies)
        require(!other.army(s.armyById(a.id)), "corpus army handle accepted by another instance");
    for (const auto& b : d.buildings)
        require(!other.building(s.buildingById(b.id)), "corpus building handle accepted by another instance");
    uint16_t id = 65535;
    while (id && d.buildingById(id)) --id;
    bool attempted = false;
    for (size_t t = 0; t < d.territories.size() && !attempted; ++t) {
        if (d.territories[t].data.terrain == 0) continue;
        for (size_t site = 0; site < kNumSites && !attempted; ++site) {
            if (d.territories[t].data.sites[site].building.raw) continue;
            attempted = true;
            auto input = building(id, int(t + 1), int(site));
            auto report = sentinel(); const auto beforeReport = report;
            rt::BuildingHandle result{};
            if (s.insertBuilding(input, result, report, e)) {
                require(s.retireBuilding(result, report, e), "corpus inserted building cannot be retired");
                require(!s.building(result) && encoded(*s.document()) == original,
                        "corpus insert/retire changed unrelated bytes");
                assertGraph(s); ++edited;
            } else {
                diagnostic(e); require(!result && report == beforeReport && s.stage() == rt::Stage::Prepared &&
                    encoded(*s.document()) == original, "corpus domain rejection was not transactional");
                ++domainRejected;
            }
        }
    }
    require(encoded(d) == original, "corpus source changed");
}
void optionalCorpus(const fs::path& directory) {
    if (directory.empty() || !fs::is_regular_file(directory / "TUTORIAL.SAV")) {
        std::cout << "runtime entities: optional corpus unavailable; synthetic tests still ran\n"; return;
    }
    size_t count = 0, edited = 0, domainRejected = 0;
    for (const auto* relative : {"TUTORIAL.SAV", "Saves/AUTOSAVE.SAV", "Campaign/AUTOSAVE.CPN", "Campaign/ChCht001.CPN"}) {
        if (!fs::is_regular_file(directory / relative)) continue;
        auto d = std::make_unique<Document>(); save::Error e;
        if (!save::readDocument(directory / relative, *d, e)) throw std::runtime_error(e.message);
        try { corpusOne(*d, edited, domainRejected); } catch (const std::exception& ex) {
            throw std::runtime_error(std::string(relative) + ": " + ex.what());
        }
        ++count;
    }
    if (fs::is_regular_file(directory / "LEVELS.HDX") && fs::is_regular_file(directory / "LEVELS.HDD")) {
        for (const auto& name : scenarioNames(directory / "LEVELS.HDX")) {
            auto d = std::make_unique<Document>(); save::Error e;
            if (!save::readScenario(directory / "LEVELS", name, *d, e)) throw std::runtime_error(e.message);
            try { corpusOne(*d, edited, domainRejected); } catch (const std::exception& ex) {
                throw std::runtime_error(name + ": " + ex.what());
            }
            ++count;
        }
    }
    std::cout << "runtime entities corpus: " << count << " exact preparations; " << edited
              << " reversible edits; " << domainRejected << " safe domain rejections\n";
}
} // namespace

int main(int argc, char** argv) {
    try {
        gs.options.turn = 2468; gs.players[0].credits = 97531;
        gg.netGame = 1; gg.rng2Seed = 0xaabbccdd;
        rtl::srand(0x12345678); (void)rtl::lrand();
        const uint32_t seed = rtl::seed(), seedHi = rtl::seedHi();
        const auto* gsRaw = reinterpret_cast<const uint8_t*>(&gs);
        const auto* ggRaw = reinterpret_cast<const uint8_t*>(&gg);
        const std::vector<uint8_t> gsBefore(gsRaw, gsRaw + sizeof(gs));
        const std::vector<uint8_t> ggBefore(ggRaw, ggRaw + sizeof(gg));
        buildingLifecycle(); armyLifecycle(); invalidInputsAndDependencies(); domainAndStageGates();
        handleOwnershipAndReallocation(); capacities();
        optionalCorpus(argc > 1 ? fs::path(argv[1]) : fs::path{});
        require(std::memcmp(gsBefore.data(), &gs, sizeof(gs)) == 0 &&
                std::memcmp(ggBefore.data(), &gg, sizeof(gg)) == 0, "entity backend changed legacy globals");
        require(rtl::seed() == seed && rtl::seedHi() == seedHi, "entity backend changed global RNG");
        std::cout << "runtime entities: lifecycle, safe handles, dependencies, rollback, capacities and isolation passed\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "runtime entities: " << e.what() << '\n'; return 1;
    }
}
