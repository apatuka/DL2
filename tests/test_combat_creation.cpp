// Calculated oracles from00451b68 and assembly leaves. PE bytes verify static
// tables; no result is claimed to be a runtime observation of DEADLOCK.EXE.
#include "game/combat_creation.h"
#include "game/combat_creation_tables.h"
#include "game/data_tables.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include "game/save_files.h"
#include <algorithm>
#include <bit>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>

namespace {
using namespace dl2;
using namespace dl2::simulation;
void require(bool value, const char* message) { if (!value) throw std::runtime_error(message); }
void ok(bool value, const save::Error& e) { if (!value) throw std::runtime_error(e.message); }
size_t grid(int x,int y) { return size_t((y+9)*36+x+9); }
std::unique_ptr<save::Document> fixture() {
    auto d = std::make_unique<save::Document>();
    std::memcpy(d->header.text,save::kHeaderText,sizeof(save::kHeaderText));
    d->header.version = kSaveVersion; d->world.width = 4; d->world.height = 1;
    d->world.numTerritories = 4; d->tiles.resize(4); d->territories.resize(4);
    d->options.numPlayers = 2; d->options.allowAlliances = 1;
    for (size_t p = 0; p < 7; ++p) {
        d->players[p].index = uint8_t(p); d->players[p].type = p ? 3 : 1;
        d->players[p].race = 0; d->ministerJobs[p].resize(1);
    }
    for (size_t t = 0; t < 4; ++t) {
        auto& tile = d->tiles[t]; tile.x = uint8_t(t); tile.territory = int16_t(t+1);
        auto& territory = d->territories[t].data;
        territory.index = uint16_t(t+1); territory.owner = t ? 1 : 0;
        territory.terrain = 1; territory.numTiles = 1; territory.secondTile = 0;
        territory.tiles[0].raw = uint32_t(t);
    }
    return d;
}
CombatCreationArmy input(uint8_t type = 1) { return {std::nullopt,4,type,1,0,0,100,1500,7,2,2}; }
CombatCreationContext context() {
    CombatCreationContext c; c.battle.territory = 1; c.battle.defender = 0;
    c.selectedTerrainTerritory = 1; c.rng = 1; return c;
}
std::vector<uint8_t> bytes(const save::Document& d) {
    std::vector<uint8_t> result; save::Error e; ok(save::encode(d,result,e),e); return result;
}
CombatCreationReport create(const save::Document& d, const CombatCreationArmy& in, const CombatCreationContext& c) {
    const auto before = bytes(d);
    const auto oldInput = in;
    const auto original = c;
    save::Error e{save::ErrorCode::Io,888,"old"}; CombatCreationReport result;
    ok(createCombatWarrior(d,in,c,result,e),e);
    require(e.code == save::ErrorCode::None && e.offset == 0 && e.message.empty(),"success clears error");
    require(bytes(d) == before && in == oldInput && c == original,"creation never changes document or caller input/context");
    return result;
}
const CombatWarrior& warrior(const CombatCreationReport& r) {
    require(r.created.has_value(),"expected created warrior"); return r.after.warriors[r.created->index];
}
uint32_t appendArmy(save::Document& d, uint32_t territory, int8_t owner, uint8_t mission = 0, uint8_t type = 1) {
    Army a{}; a.id = uint16_t(100+d.armies.size()); a.type = type; a.unitClass = data::kUnitTypes[type].unitClass;
    a.owner = owner; a.unk_25 = mission; a.health = 100; a.experience = 1200;
    a.territory.raw = a.dest.raw = a.origin.raw = territory;
    auto& t = d.territories[territory-1].data;
    auto& head = owner == t.owner ? t.armies : t.foreignArmies;
    a.next.raw = head.raw;
    for (auto& other : d.armies) if (other.id == head.raw) other.prev.raw = a.id;
    head.raw = a.id; d.armies.push_back(a); return a.id;
}

void creationAndPreservedSlot() {
    auto d = fixture(); auto c = context(); auto in = input();
    auto& old = c.warriors[0]; old.parent = CombatBuildingParent{88}; old.supplyPenalty = 3;
    old.preserved15 = 15; old.preserved1f = 31; old.preserved31 = 49; old.preserved37 = 55;
    old.secondaryArmyId = 444; old.workNext = CombatantRef{9999};
    old.target = CombatantRef{999}; old.structureTarget = CombatStructureRef{101}; old.next = CombatantRef{999};
    const auto r = create(*d,in,c); const auto& w = warrior(r);
    require(kCombatWarriorCapacity == 0x348 && kCombatWarriorCapacity*0x4c == 0xf960 && c.limit == 0x347,
            "physical Warrior pool is840 slots, matching reset0xf960 and stride0x4c");
    require(r.created == CombatantRef{0} && r.after.cursor == 1 && r.after.battle.first == r.created && r.after.battle.last == r.created,
            "allocation appends the original physical cell then advances its ring cursor");
    require(w.type == 1 && w.currentOwner == 1 && w.originalOwner == 1 && w.orders == 0 && w.experience == 1500,
            "creation copies raw experience without projection cap1000");
    require(r.thresholdDefense == 2 && w.retreatDamage == 2 && w.supplyPenalty == 0,
            "first defense uses PREVIOUS pool supply byte before food flags replace it");
    require(w.x == 21 && w.y == 11 && w.facing == 8 && w.currentX == w.x && w.initialX == w.x &&
            w.currentY == w.y && w.initialY == w.y && w.initialFacing == 8 && w.damage == 7 && w.initialDamage == 7,
            "attacker east entry preserves canonical coordinates and snapshots");
    require(w.active == 1 && w.speedCounter == 4 && w.fireCounter == 5 && w.state36 == 0 && w.retreatTerritory == 0xffff,
            "combat statistics initialize actual speed/fire counters and no adjacent retreat");
    require(std::get<CombatCreationArmy>(w.parent) == in && !w.next && !w.target && !w.structureTarget &&
            w.secondaryArmyId == old.secondaryArmyId && w.workNext == old.workNext &&
            w.preserved15 == 15 && w.preserved1f == 31 && w.preserved31 == 49 && w.preserved37 == 55,
            "only original writes replace stale references and padding; synthetic source is owned");
    require(r.after.attackerCount == 1 && r.after.defenderCount == 0 && r.after.battle.playerMask == 2 &&
            r.after.battle.approachMask == 2 && (r.after.grid.flags[grid(21,11)] & 1) && r.draws.empty() && r.after.rng == c.rng,
            "attacker registration, occupancy, side mask and private RNG effects are exact");
    require(r.after.placementDomain == 1 && r.after.useGridPenalty == 0,"placement publishes scratch selectors");
    auto filled = r.after; filled.cursor = 839; filled.limit = 400;
    auto wrapped = create(*d,in,filled);
    require(wrapped.created == CombatantRef{839} && wrapped.after.cursor == 0 && wrapped.after.warriors[0].next == wrapped.created,
            "physical slot839 appends and wraps modulo840");
    d->players[1].foodFlags = 2; c.warriors[0].supplyPenalty = 0;
    const auto supplied = create(*d,in,c);
    require(supplied.thresholdDefense == 5 && warrior(supplied).retreatDamage == 5 && warrior(supplied).supplyPenalty == 0xff,
            "new supply penalty is snapshot ff after threshold calculation");
}

void nativeNullAndProjection() {
    auto d = fixture(); auto in = input(); auto c = context();
    for (uint8_t mission : std::array<uint8_t,9>{1,2,3,4,5,6,15,16,19}) {
        in.mission = mission; const auto r = create(*d,in,c);
        require(r.outcome == CombatCreationOutcome::MissionExcluded && !r.created && r.after == c && r.draws.empty(),
                "every original excluded mission is a native null without allocation or RNG");
    }
    in = input(16); in.owner = 0;
    const auto missile = create(*d,in,c);
    require(missile.outcome == CombatCreationOutcome::DefenderWarhead && missile.after == c,"defending warhead is a native null");
    in = input(); c.cursor = c.limit; c.battle.first = CombatantRef{999};
    const auto full = create(*d,in,c);
    require(full.outcome == CombatCreationOutcome::PoolFull && full.after == c,"full pool returns before consulting stale battle links");
    c = context(); in.mission = 7;
    require(create(*d,in,c).created.has_value(),"unlisted mission7 remains eligible");
    const auto id = appendArmy(*d,2,1); auto& a = d->armies.back(); a.experience = 32767; a.moves = 4; a.unk_2c = -123;
    a.unk_44.raw = 0xdeadbeef; save::Error e; CombatCreationArmy projected;
    ok(projectCombatCreationArmy(*d,id,projected,e),e);
    require(projected.liveArmyId == id && projected.id == id && projected.experience == 32767 && projected.orders == 4 &&
            projected.damage == -123 && projected.turnStart == 2 && projected.routeOrigin == 2,"live projection uses exact Army fields");
    require(std::get<CombatArmyParent>(warrior(create(*d,projected,c)).parent).id == id,"live creation stores an owned Army ID parent");
    auto old = projected;
    require(!projectCombatCreationArmy(*d,9999,projected,e) && projected == old,"bad projection preserves old destination");
}

void placementAndRng() {
    auto d = fixture(); auto in = input(); auto c = context();
    // Rebind selected tiles on a valid canonical4x4 map; archival Tile bytes
    // must keep their actual row-major coordinates and territory ownership.
    auto geometryAt = [&](int x1,int y1,int x2,int y2) {
        d->world.height = 4; d->tiles.clear(); d->tiles.resize(16);
        for (size_t i = 0; i < d->tiles.size(); ++i) { d->tiles[i].x = uint8_t(i%4); d->tiles[i].y = uint8_t(i/4); }
        const std::array<std::array<int,2>,4> positions{{{{x2,y2}},{{x1,y1}},{{2,3}},{{3,3}}}};
        for (size_t i = 0; i < positions.size(); ++i) {
            const auto x = uint32_t(positions[i][0]), y = uint32_t(positions[i][1]);
            d->territories[i].data.tiles[0].raw = x | (y << 16);
            d->tiles[size_t(y)*4+x].territory = int16_t(i+1);
        }
    };
    const std::array<std::array<int,4>,4> geometry{{{{1,1,1,2}},{{2,1,1,1}},{{1,2,1,1}},{{1,1,2,1}}}};
    const std::array<uint8_t,4> direction{1,2,4,8}, facing{4,8,1,2};
    const std::array<std::array<int,2>,4> expected{{{{6,-4}},{{21,11}},{{11,21}},{{-4,6}}}};
    for (size_t i = 0; i < geometry.size(); ++i) {
        geometryAt(geometry[i][0],geometry[i][1],geometry[i][2],geometry[i][3]);
        const auto r = create(*d,in,c); const auto& w = warrior(r);
        require(r.after.battle.approachMask == direction[i] && w.facing == facing[i] && w.x == expected[i][0] && w.y == expected[i][1],
                "four attack direction tables resolve actual signed Tile bytes");
    }
    geometryAt(2,2,1,1);
    require(create(*d,in,c).after.battle.approachMask == 4,"diagonal tie chooses vertical approach");
    geometryAt(0,0,1,0);
    require(create(*d,in,c).after.battle.approachMask == 8,"west approach resolves selected tile references");
    d->territories[0].data.terrain = 4;
    require(create(*d,in,c).after.battle.approachMask == 4,"terrain4 remaps ordinary west approach8 to4");
    auto missile = input(16);
    const auto m = create(*d,missile,c);
    require(m.after.battle.approachMask == 8 && warrior(m).x == -127,"terrain4 does not remap warhead approach");

    d = fixture(); in = input(); in.owner = 0; c.battle.approachMask = 1;
    auto r = create(*d,in,c);
    require(r.draws == std::vector<CombatCreationDraw>{{1,1103527590u,4,2}} && r.after.rng == 1103527590u &&
            warrior(r).x == 8 && warrior(r).y == 2 && warrior(r).facing == 1,
            "defender uses private32 LCG and side1 table for first seed1 draw");
    c.battle.approachMask = 2;
    r = create(*d,in,c);
    require(r.draws.size() > 1 && warrior(r).facing == 2,"defender consumes rejected side draws before enabled side");
    uint32_t rng = 1;
    for (const auto& draw : r.draws) {
        const auto next = uint32_t(uint64_t(rng)*1103515245u+12345u);
        require(draw.before == rng && draw.after == next && draw.value == ((next>>16)%4),"LCG upper16 includes bit31, no rand15 mask");
        rng = next;
    }
    require(r.after.defenderCount == 1 && r.after.attackerCount == 0,"defending registration chooses defender counter");
    in.orders = 2;
    require(warrior(create(*d,in,c)).orders == 3,"defender order2 becomes order3 before statistic queries");

    in = input(); c = context(); c.grid.flags.fill(0x12); c.grid.penalty.fill(255); c.useGridPenalty = 123;
    r = create(*d,in,c);
    require(r.placementFallback && r.testedPositions == 54 && warrior(r).x == 21 && warrior(r).y == 11 &&
            r.after.grid.flags[grid(21,11)] == 0x13 && r.after.useGridPenalty == 0,
            "all blocked cells still create at counter%54 and mark occupied, retaining nonoccupancy flag bits");
    c = context(); c.grid.flags[grid(21,11)] = 1;
    r = create(*d,in,c);
    require(r.testedPositions == 2 && warrior(r).y == 10,"occupied first cell skips to the next original table row");
    in.id = 5; c = context();
    require(warrior(create(*d,in,c)).y == 10,"low unsigned ID bits offset initial table cursor");
    in.id = 4; c.attackerCount = 55; c.grid.flags.fill(2);
    r = create(*d,in,c);
    require(r.placementFallback && r.testedPositions == 0 && warrior(r).y == 10,"oversized nonnegative counter falls back without grid reads");
    c.attackerCount = UINT32_MAX; in.id = 5;
    r = create(*d,in,c);
    require(r.after.attackerCount == 0 && r.placementFallback,"index and native attacker counter use defined wrap32");
}

void specialClassesAndThresholds() {
    auto d = fixture(); auto c = context(); auto in = input(19);
    auto& slot = c.warriors[0]; slot.parent = CombatBuildingParent{777}; slot.x = INT32_MAX; slot.y = INT32_MIN; slot.facing = 91;
    c.attackerCount = UINT32_MAX;
    auto r = create(*d,in,c); const auto& fort = warrior(r);
    require(fort.parent == slot.parent && fort.x == slot.x && fort.y == slot.y && fort.facing == 91 && fort.initialFacing == 91 &&
            fort.currentX == INT32_MAX && fort.currentY == INT32_MIN && fort.retreatTerritory == 0xffff && r.after.attackerCount == 0 &&
            r.draws.empty() && r.after.grid == c.grid,"fort preserves stale parent/placement and bypasses placement/occupancy/retreat queries");
    require(fort.speedCounter == 0 && fort.fireCounter == 8,"fort calls real min-clamped speed and canonical fire query");
    const std::array<uint8_t,9> percents{0,1,2,6,10,127,128,250,254};
    const std::array<int16_t,9> thresholds{0,1,1,2,3,32,-31,-1,0};
    for (size_t i = 0; i < percents.size(); ++i) {
        in.retreatPercent = percents[i];
        require(warrior(create(*d,in,c)).retreatDamage == thresholds[i],"x87 product/100+.5 truncation, signed-byte percentage and positive minimum");
    }
    in.retreatPercent = 100; d->raceStats.v[44][0] = 32767;
    r = create(*d,in,c);
    require(r.thresholdDefense == 81942 && warrior(r).retreatDamage == 16406,"threshold narrows low WORD without saturation");
    d->raceStats.v[44][0] = 0; d->raceStats.v[46][0] = 300;
    require(warrior(create(*d,in,c)).speedCounter == 43,"speed299 narrows to raw byte43");
    d->raceStats.v[46][0] = 0;
    c = context(); in = input(16); in.orders = 4; d->players[1].foodFlags = 3;
    r = create(*d,in,c);
    require(r.thresholdDefense == 4 && warrior(r).retreatDamage == 2 && warrior(r).orders == 23 && warrior(r).fireCounter == 0 &&
            warrior(r).x == 127 && warrior(r).y == 9 && r.after.grid == c.grid,
            "warhead second defense reads new supply; order23 technology override occurs AFTER counter initialization");
    d->players[1].foodFlags = 0; d->raceStats.v[42][0] = 32767; d->techs[23].knownMask = 2;
    r = create(*d,in,c);
    require(warrior(r).orders == 4 && warrior(r).retreatDamage == 54,"tech23 preserves order and warhead defense13110 narrows through BYTE54");
    d->raceStats.v[42][0] = 0;
    in = input(9); c.battle.outsidePlacement = 1;
    r = create(*d,in,c);
    require(warrior(r).x == 26 && warrior(r).y == 11 && warrior(r).facing == 8 && warrior(r).retreatTerritory == 2 &&
            r.after.placementDomain == 1 && r.after.grid == c.grid,"attacking air shifts five cells outside and retreats to turn-start, no occupancy");
    in.owner = 0; c.battle.approachMask = 1;
    r = create(*d,in,c);
    require(warrior(r).facing == 2 && warrior(r).initialFacing == 2 && warrior(r).y == 7,"defender air overrides facing only after side-based position shift");
    in.turnStart = 0;
    r = create(*d,in,c);
    require(warrior(r).retreatTerritory == 0xffff && r.missingPlaneRetreat,"native missing-plane parent territory produces diagnostic andffff without false API failure");
    for (auto [type,index] : std::array<std::pair<uint8_t,size_t>,4>{{{15,0},{33,1},{28,2},{26,3}}}) {
        c = context(); c.grid.flags.fill(0x60); in = input(type);
        r = create(*d,in,c);
        require(r.after.battle.support[index][1] == 1,"support class marks exact original-owner column");
    }
    c = context(); in = input(23);
    r = create(*d,in,c);
    require(r.after.grid == c.grid && warrior(r).retreatTerritory == 0xffff && r.after.attackerCount == 1,
            "militia still positions and counts but caller must later mark occupancy");
}

void mineAndTerrainPlacement() {
    auto d = fixture(); auto c = context(); auto in = input(37); in.owner = 0;
    for (uint8_t outside : std::array<uint8_t,2>{0,1}) {
        c.battle.outsidePlacement = outside;
        const auto r = create(*d,in,c); const auto& w = warrior(r);
        const bool inside = w.x >= 0 && w.x < 18 && w.y >= 0 && w.y < 18;
        require(inside != bool(outside) && combat_creation_tables::kValidCells[grid(w.x,w.y)] && !r.draws.empty() &&
                r.draws.size()%2 == 0 && r.after.grid == c.grid && r.after.attackerCount == 0 && r.after.defenderCount == 0,
                "mine samples paired coordinates with exact inside/outside rule, but never occupies or increments combat counts");
    }
    d->territories[0].data.terrain = 4; c.battle.outsidePlacement = 1;
    auto r = create(*d,in,c);
    require(warrior(r).x >= 0 && warrior(r).y >= 0,"terrain4 mine rejects both negative coordinate axes");
    d = fixture(); c = context(); in = input(12);
    c.grid.flags.fill(0x50); c.grid.flags[grid(21,10)] = 0x60;
    r = create(*d,in,c);
    require(warrior(r).y == 10 && r.testedPositions == 2,"naval placement needs grid high nibble6");
    in = input(1);
    c.grid.flags.fill(0x50); c.grid.flags[grid(21,10)] = 0x54;
    r = create(*d,in,c);
    require(warrior(r).y == 10,"land cell flag4 overrides otherwise expensive terrain");
    c.grid.flags.fill(0x50); in = input(27); c.selectedTerrainTerritory = 2; d->territories[1].data.terrain = 0;
    r = create(*d,in,c);
    require(warrior(r).y == 11 && r.testedPositions == 1,"amphibious cost reads explicit selected territory independently from battle territory");
    c.selectedTerrainTerritory = 1;
    require(create(*d,in,c).placementFallback,"amphibious selected land follows original high-cost fallback");
}

void retreatAndAtomicErrors() {
    auto d = fixture(); auto c = context(); auto in = input();
    d->territories[0].data.adjacency[0] = (1u<<3)|(1u<<4);
    d->territories[2].data.adjacency[0] = d->territories[3].data.adjacency[0] = 1u<<1;
    auto r = create(*d,in,c);
    require(warrior(r).retreatTerritory == 3 && r.retreatAccessQueries == 1,"retreat takes first ascending accessible owned neighbor");
    const auto enemyId = appendArmy(*d,3,0);
    r = create(*d,in,c);
    require(warrior(r).retreatTerritory == 4 && r.retreatAccessQueries == 2,"active hostile foreign army excludes otherwise valid retreat");
    d->armies[0].unk_25 = 19;
    require(warrior(create(*d,in,c)).retreatTerritory == 3,"excluded foreign mission does not block retreat");
    d->armies[0].unk_25 = 0; d->players[1].relations[0] = 2;
    require(warrior(create(*d,in,c)).retreatTerritory == 3,"directional effective transit pact permits foreign army");
    d->players[1].relations[0] = 0; d->players[0].relations[1] = 2;
    require(warrior(create(*d,in,c)).retreatTerritory == 4,"reverse pact alone does not permit foreign army");
    d->territories[3].data.flags |= 0x100;
    require(warrior(create(*d,in,c)).retreatTerritory == 0xffff,"NoTiles neighbor is excluded before access");
    in.orders = 1; d->raceStats.v[33][0] = -1;
    require(create(*d,in,c).retreatAccessQueries == 0,"nonzero infantry racial order1 disables retreat before adjacency reads");
    in.orders = 0; d->raceStats.v[33][0] = 0;
    d->territories[3].data.flags = 0; d->territories[2].data.terrain = 0;
    require(warrior(create(*d,in,c)).retreatTerritory == 4,"land retreat at sea needs actual carrier eligibility");
    (void)enemyId;

    auto previous = r, out = r; save::Error e;
    auto fails = [&](const CombatCreationArmy& source,const CombatCreationContext& ctx) {
        const auto snapshot = bytes(*d);
        require(!createCombatWarrior(*d,source,ctx,out,e) && out == previous && e.code != save::ErrorCode::None && bytes(*d) == snapshot,
                "late combat-creation error preserves prior report, source, pool, grid and RNG");
    };
    auto badInput = in; badInput.type = 39; fails(badInput,c);
    badInput = in; badInput.type = 0; fails(badInput,c);
    badInput = in; badInput.owner = -1; fails(badInput,c);
    auto bad = c; bad.warriors.pop_back(); fails(in,bad);
    bad = c; bad.cursor = 840; fails(in,bad);
    bad = c; bad.limit = 840; fails(in,bad);
    bad = c; bad.battle.first = CombatantRef{0}; bad.battle.last = CombatantRef{0}; fails(in,bad);
    bad = c; bad.battle.first = CombatantRef{1}; bad.battle.last = CombatantRef{1}; bad.warriors[1].next = CombatantRef{1}; fails(in,bad);
    bad = c; bad.battle.first = CombatantRef{999}; bad.battle.last = bad.battle.first; fails(in,bad);
    bad = c; bad.attackerCount = 0x80000000u; fails(in,bad);
    badInput = in; badInput.routeOrigin = 0; fails(badInput,c);
    badInput = input(27); bad = c; bad.selectedTerrainTerritory.reset(); fails(badInput,bad);
    badInput = input(); badInput.owner = 0; bad = c; bad.battle.approachMask = 1; bad.maximumRandomDraws = 0;
    fails(badInput,bad); require(e.code == save::ErrorCode::Limit,"draw guard is a transactional Limit error");
    bad.battle.approachMask = 0; fails(badInput,bad);
    badInput = input(37); badInput.owner = 0; bad = c; bad.maximumRandomDraws = 1; fails(badInput,bad);
    require(e.code == save::ErrorCode::Limit,"mine odd draw-budget failure after X draw rolls back RNG and allocated slot");
    d->territories[1].data.secondTile = -1; fails(in,c); d->territories[1].data.secondTile = 0;
    d->players[1].race = 127; fails(in,c); d->players[1].race = 0;
    d->territories[3].data.flags = 0x100;
    d->territories[0].data.adjacency[6] = 0x8000; fails(in,c); d->territories[0].data.adjacency[6] = 0;
    d->territories[3].data.flags = 0;
    d->territories[0].data.adjacency[0] |= 1; fails(in,c); d->territories[0].data.adjacency[0] &= 0xfffeu;
    CombatCreationArmy live; ok(projectCombatCreationArmy(*d,d->armies[0].id,live,e),e); ++live.experience; fails(live,c);
    d->header.version = 0;
    require(!createCombatWarrior(*d,in,c,out,e) && e.code == save::ErrorCode::UnsupportedVersion && out == previous,
            "codec rejection retains original error and output");

    d = fixture(); c = context(); in = input(); out = create(*d,in,c);
    const auto expected = create(*d,in,out.after);
    ok(createCombatWarrior(*d,in,out.after,out,e),e);
    require(out == expected,"report.after input aliases report output safely");
    const auto& aliasedInput = std::get<CombatCreationArmy>(out.after.warriors[0].parent);
    const auto expected2 = create(*d,aliasedInput,out.after);
    ok(createCombatWarrior(*d,aliasedInput,out.after,out,e),e);
    require(out == expected2,"owned synthetic source may also alias destination report");
}

class Pe {
    std::vector<uint8_t> bytes_; size_t sections_ = 0; uint16_t count_ = 0; uint32_t base_ = 0;
    uint16_t u16(size_t p) const { require(p+2 <= bytes_.size(),"truncated PE word"); return uint16_t(bytes_[p]|uint16_t(bytes_[p+1])<<8); }
    uint32_t u32(size_t p) const { require(p+4 <= bytes_.size(),"truncated PE dword"); return uint32_t(bytes_[p])|uint32_t(bytes_[p+1])<<8|uint32_t(bytes_[p+2])<<16|uint32_t(bytes_[p+3])<<24; }
    size_t offset(uint32_t va) const {
        require(va >= base_,"PE address below base"); const auto rva = va-base_;
        for (size_t i = 0; i < count_; ++i) { const auto p = sections_+i*40; const auto begin = u32(p+12), size = u32(p+16);
            if (rva >= begin && rva-begin < size) return size_t(u32(p+20))+rva-begin; }
        throw std::runtime_error("unbacked PE address");
    }
public:
    explicit Pe(const std::filesystem::path& path) {
        std::ifstream file(path,std::ios::binary); require(bool(file),"cannot open original PE");
        const auto n = std::filesystem::file_size(path); require(n >= 64 && n < 16*1024*1024,"invalid PE size");
        bytes_.resize(size_t(n)); require(bool(file.read(reinterpret_cast<char*>(bytes_.data()),std::streamsize(n))),"cannot read PE");
        const auto pe = u32(0x3c); require(u16(0) == 0x5a4d && u32(pe) == 0x4550 && u16(pe+24) == 0x10b,"not original PE32");
        count_ = u16(pe+6); base_ = u32(pe+52); sections_ = size_t(pe)+24+u16(pe+20);
        require(count_ > 0 && count_ < 100 && sections_+size_t(count_)*40 <= bytes_.size(),"invalid PE section table");
    }
    uint8_t byte(uint32_t va) const { const auto p = offset(va); require(p < bytes_.size(),"PE byte outside file"); return bytes_[p]; }
    uint32_t word(uint32_t va) const { return u32(offset(va)); }
};
void originalTables(const std::filesystem::path& directory) {
    const Pe pe(directory/"DEADLOCK.EXE");
    for (size_t i = 0; i < combat_creation_tables::kPlacementXY.size(); ++i)
        require(std::bit_cast<int32_t>(pe.word(0x4ce850+uint32_t(i)*4)) == combat_creation_tables::kPlacementXY[i],"placement table differs from PE");
    for (size_t i = 0; i < combat_creation_tables::kTerrainCost.size(); ++i)
        require(std::bit_cast<int32_t>(pe.word(0x4cf810+uint32_t(i)*4)) == combat_creation_tables::kTerrainCost[i],"terrain cost differs from PE");
    for (size_t i = 0; i < combat_creation_tables::kValidCells.size(); ++i)
        require(pe.byte(0x4cf858+uint32_t(i)) == combat_creation_tables::kValidCells[i],"grid mask differs from PE");
    constexpr uint8_t scale[]{0x00,0xd8,0xa3,0x70,0x3d,0x0a,0xd7,0xa3,0xf8,0x3f};
    for (size_t i = 0; i < sizeof(scale); ++i) require(pe.byte(0x451dd4+uint32_t(i)) == scale[i],"80-bit threshold constant differs from PE");
    require(pe.word(0x451de0) == 0x3f000000,"threshold adds exactly float0.5");
    require(pe.word(0x451bcc) == kCombatWarriorCapacity,"native creation ring modulus differs from840");
    require(pe.byte(0x4ae076) == 0x80 && pe.byte(0x4ae079) == 0x0c,"conversion must force x87 round-toward-zero");
}
void realArmyInputs(const std::filesystem::path& directory) {
    auto d = std::make_unique<save::Document>(); save::Error e;
    ok(save::readDocument(directory/"TUTORIAL.SAV",*d,e),e);
    size_t count = 0;
    for (const auto& a : d->armies) {
        CombatCreationArmy source; ok(projectCombatCreationArmy(*d,a.id,source,e),e);
        auto c = context(); c.battle.territory = a.dest.raw; c.battle.defender = a.owner;
        c.battle.approachMask = 15; c.selectedTerrainTerritory = a.dest.raw;
        c.creation.movingArmyId = a.id;
        const auto first = create(*d,source,c), second = create(*d,source,c);
        require(first == second,"real SAV army creation is deterministic with explicit standalone battle/grid context"); ++count;
    }
    require(count > 0,"tutorial has real creation inputs");
    std::cout << "combat creation: " << count << " real army inputs, explicit synthetic battle context\n";
}
} // namespace
int main(int argc,char** argv) {
    try {
        std::vector<uint8_t> oldGs(sizeof(gs)),oldGg(sizeof(gg));
        std::memcpy(oldGs.data(),&gs,sizeof(gs)); std::memcpy(oldGg.data(),&gg,sizeof(gg));
        const auto seed = rtl::seed(), hi = rtl::seedHi();
        creationAndPreservedSlot(); nativeNullAndProjection(); placementAndRng();
        specialClassesAndThresholds(); mineAndTerrainPlacement(); retreatAndAtomicErrors();
        const auto directory = argc > 1 ? std::filesystem::path(argv[1]) : std::filesystem::path("C:/GOG Games/Deadlock 2");
        originalTables(directory); realArmyInputs(directory);
        require(!std::memcmp(oldGs.data(),&gs,sizeof(gs)) && !std::memcmp(oldGg.data(),&gg,sizeof(gg)) && seed == rtl::seed() && hi == rtl::seedHi(),
                "combat creation isolates all global state and shared RNG");
        std::cout << "combat_creation: physical pool, native outcomes, placement, retreat, stats, private RNG and rollback passed\n";
        return 0;
    } catch (const std::exception& e) { std::cerr << "combat_creation: " << e.what() << '\n'; return 1; }
}
