#include "game/combat_preparation.h"
#include <algorithm>
#include <bit>
#include <new>
#include <stdexcept>
#include <utility>

namespace dl2::simulation {
namespace {
bool fail(save::Error& error, const char* text, save::ErrorCode code = save::ErrorCode::InvalidState) {
    error = {code,0,text}; return false;
}
bool shape(const CombatPreparationState& s, save::Error& e) {
    return (s.warriors.size() == kCombatWarriorCapacity && s.structures.size() == kCombatStructureCapacity &&
            s.battles.size() == kCombatBattleCapacity) || fail(e,"Combat preparation requires exactly840 Warriors,1200 structures and32 Battles");
}
bool documentValid(const save::Document& d, save::Error& e) {
    return save::validate(d,e) && (!d.header.isMap || fail(e,"Combat preparation requires a full saved-game document"));
}
bool selected(const CombatPreparationState& s, save::Error& e) {
    return (s.currentBattle && s.currentBattle->index < s.battles.size()) ||
        fail(e,"Combat preparation requires a represented selected Battle");
}
const Territory* territory(const save::Document& d, uint32_t id, save::Error& e) {
    if (id == 0 || id > d.territories.size()) {
        fail(e,"Combat preparation reached an unrepresented territory (including sentinel0)"); return nullptr;
    }
    return &d.territories[id-1].data;
}
bool coordinate(int32_t x, int32_t y) { return x >= -9 && x <= 26 && y >= -9 && y <= 26; }
size_t cell(int32_t x, int32_t y) { return size_t((y+9)*36+x+9); }
// orig:0045130c. The caller has already checked physical bounds.
void road(CombatCreationGrid& g, int32_t x, int32_t y, int32_t flag) {
    auto& value = g.flags[cell(x,y)];
    if (flag) value |= 4u; else value &= 0xfbu;
}
// orig:00451340. Only AL survives the shift into the byte destination.
void terrainBits(CombatCreationGrid& g, int32_t x, int32_t y, uint8_t terrain) {
    g.flags[cell(x,y)] |= uint8_t(uint32_t(terrain) << 4);
}
// orig:004571d4. References not dereferenced by this reset remain uninterpreted.
void reset(CombatPreparationState& s) {
    std::fill(s.warriors.begin(),s.warriors.end(),CombatWarrior{});
    std::fill(s.structures.begin(),s.structures.end(),CombatStructure{});
    std::fill(s.battles.begin(),s.battles.end(),CombatBattleRecord{});
    s.battleCount = 0;
    s.warriorCursor = 0; s.warriorLimit = 839;
    s.structureCursor = 0; s.structureLimit = 1199;
}
// orig:0045209c. Called with a checked Territory and selected Battle.
void rebuild(const Territory& t, CombatPreparationState& s) {
    s.grid = clearedCombatGrid();
    for (int32_t y = -9; y <= 26; ++y)
        for (int32_t x = -9; x <= 26; ++x)
            if (x < 0 || y < 0 || x >= 18 || y >= 18) s.grid.flags[cell(x,y)] |= 0x70u;
    auto& roads = s.battles[s.currentBattle->index].roads;
    static_assert(offsetof(BuildingSite,unk_05)+11 == 0x10);
    for (size_t i = 0; i < roads.size(); ++i) {
        const auto& site = t.sites[i];
        const int32_t x = int32_t(i%6)*3, y = int32_t(i/6)*3;
        const uint8_t terrain = site.terrainFlags == 0xff ? 6 : uint8_t(site.terrainFlags & 0xfu);
        for (int32_t dy = 0; dy < 3; ++dy)
            for (int32_t dx = 0; dx < 3; ++dx) terrainBits(s.grid,x+dx,y+dy,terrain);
        if (s.replayMode == 0) roads[i] = std::bit_cast<int8_t>(site.unk_05[11]);
        const uint16_t bits = uint16_t(roads[i]);
        if (bits != 0 && bits != 2 && bits != 4) road(s.grid,x,y,1);
        if (bits & 4u) { road(s.grid,x,y+1,1); road(s.grid,x,y+2,1); }
        if (bits == 1) road(s.grid,x,y+1,1);
        if (bits & 2u) { road(s.grid,x+1,y,1); road(s.grid,x+2,y,1); }
        if (bits == 8) road(s.grid,x+1,y,1);
    }
}
void project(const CombatPreparationState& s, CombatCreationContext& c) {
    c.warriors = s.warriors; c.cursor = s.warriorCursor; c.limit = s.warriorLimit;
    c.battle = s.battles[s.currentBattle->index].core; c.grid = s.grid;
    c.attackerCount = s.attackerCount; c.defenderCount = s.defenderCount; c.rng = s.privateRng;
    c.placementDomain = s.placementDomain; c.useGridPenalty = s.useGridPenalty;
    c.selectedTerrainTerritory = s.selectedTerrainTerritory; c.creation = s.creation;
    c.maximumRandomDraws = s.maximumRandomDraws;
}
void publish(CombatCreationContext&& c, CombatPreparationState& s) {
    s.warriors = std::move(c.warriors); s.warriorCursor = c.cursor; s.warriorLimit = c.limit;
    s.battles[s.currentBattle->index].core = c.battle; s.grid = c.grid;
    s.attackerCount = c.attackerCount; s.defenderCount = c.defenderCount; s.privateRng = c.rng;
    s.placementDomain = c.placementDomain; s.useGridPenalty = c.useGridPenalty;
    s.selectedTerrainTerritory = c.selectedTerrainTerritory; s.creation = c.creation;
    s.maximumRandomDraws = c.maximumRandomDraws;
}
} // namespace

bool CombatPreparationState::operator==(const CombatPreparationState& b) const {
    return warriors == b.warriors && structures == b.structures && battles == b.battles &&
        battleCount == b.battleCount && turn == b.turn && tick == b.tick && deadline == b.deadline &&
        attackerCount == b.attackerCount && defenderCount == b.defenderCount &&
        warriorCursor == b.warriorCursor && warriorLimit == b.warriorLimit &&
        structureCursor == b.structureCursor && structureLimit == b.structureLimit && currentBattle == b.currentBattle &&
        grid == b.grid && privateRng == b.privateRng && replayMode == b.replayMode &&
        placementDomain == b.placementDomain && useGridPenalty == b.useGridPenalty &&
        selectedTerrainTerritory == b.selectedTerrainTerritory && creation.movingArmyId == b.creation.movingArmyId &&
        maximumRandomDraws == b.maximumRandomDraws;
}

// orig:004512a8.
CombatCreationGrid clearedCombatGrid() noexcept { return {}; }
bool setCombatGridRoad(const CombatCreationGrid& before, int32_t x, int32_t y, int32_t flag,
                       CombatCreationGrid& after, save::Error& e) {
    if (!coordinate(x,y)) return fail(e,"Combat road cell lies outside the owned36x36 grid");
    auto result = before; road(result,x,y,flag); after = result; e = {}; return true;
}
bool addCombatGridTerrain(const CombatCreationGrid& before, int32_t x, int32_t y, uint8_t terrain,
                          CombatCreationGrid& after, save::Error& e) {
    if (!coordinate(x,y)) return fail(e,"Combat terrain cell lies outside the owned36x36 grid");
    auto result = before; terrainBits(result,x,y,terrain); after = result; e = {}; return true;
}
bool resetCombatPools(const CombatPreparationState& before, CombatPreparationState& after, save::Error& e) try {
    if (!shape(before,e)) return false;
    auto result = before; reset(result); after = std::move(result); e = {}; return true;
} catch (const std::bad_alloc&) { return fail(e,"Combat pool reset allocation failed",save::ErrorCode::Limit);
} catch (const std::length_error&) { return fail(e,"Combat pool reset allocation exceeds limits",save::ErrorCode::Limit); }

bool prepareCombatPhase(const save::Document& d, const CombatPreparationState& before,
                        const RngSnapshot& rngBefore, CombatPhasePreparationReport& report, save::Error& e) try {
    if (!documentValid(d,e) || !shape(before,e)) return false;
    SessionRng rng;
    if (!rng.restore(rngBefore,e)) return false;
    CombatPhasePreparationReport result;
    result.after = before; result.after.replayMode = 0; reset(result.after); result.after.turn = d.options.turn;
    for (size_t i = 0; i < result.draws.size(); ++i) {
        if (!rng.apply({RngOperation::Rand15,0,0,"Combat"},result.draws[i],e)) return false;
        result.after.battles[i].seed = result.draws[i].value;
    }
    result.sessionRngAfter = rng.snapshot(); report = std::move(result); e = {}; return true;
} catch (const std::bad_alloc&) { return fail(e,"Combat prefix allocation failed",save::ErrorCode::Limit);
} catch (const std::length_error&) { return fail(e,"Combat prefix allocation exceeds limits",save::ErrorCode::Limit); }

bool beginCombatBattle(const save::Document& d, const CombatBattleRequest& request,
                       const CombatPreparationState& before, CombatBattlePreparationReport& report, save::Error& e) try {
    if (!documentValid(d,e) || !shape(before,e)) return false;
    if (before.battleCount < 0 || before.battleCount >= int32_t(kCombatBattleCapacity))
        return fail(e,"Combat Battle allocation lies outside the32 physical slots",save::ErrorCode::Limit);
    const auto* t = territory(d,request.territory,e); if (!t) return false;
    CombatBattlePreparationReport result; result.after = before;
    auto& s = result.after;
    s.tick = 0; s.deadline = -1; s.attackerCount = s.defenderCount = 0;
    result.created = {size_t(s.battleCount)}; s.currentBattle = result.created; ++s.battleCount;
    auto& b = s.battles[result.created.index];
    b.core.territory = request.territory; b.core.defender = request.defender; b.attacker = request.attacker;
    b.core.outsidePlacement = uint8_t(uint32_t(request.mode));
    b.core.first.reset(); b.core.last.reset(); b.firstStructure.reset(); b.lastStructure.reset();
    b.core.playerMask = 0; b.core.approachMask = 0; s.privateRng = b.seed; //00450dd0
    if (request.mode != 0) rebuild(*t,s);
    else {
        s.grid = clearedCombatGrid();
        if (t->terrain == 0) s.grid.flags.fill(0x60);
    }
    report = std::move(result); e = {}; return true;
} catch (const std::bad_alloc&) { return fail(e,"Combat Battle initialization allocation failed",save::ErrorCode::Limit);
} catch (const std::length_error&) { return fail(e,"Combat Battle initialization allocation exceeds limits",save::ErrorCode::Limit); }

bool rebuildCombatGrid(const save::Document& d, uint32_t id,
                       const CombatPreparationState& before, CombatPreparationState& after, save::Error& e) try {
    if (!documentValid(d,e) || !shape(before,e) || !selected(before,e)) return false;
    const auto* t = territory(d,id,e); if (!t) return false;
    auto result = before; rebuild(*t,result); after = std::move(result); e = {}; return true;
} catch (const std::bad_alloc&) { return fail(e,"Combat grid reconstruction allocation failed",save::ErrorCode::Limit);
} catch (const std::length_error&) { return fail(e,"Combat grid reconstruction allocation exceeds limits",save::ErrorCode::Limit); }

bool projectPreparedCombatCreation(const CombatPreparationState& before, CombatCreationContext& after, save::Error& e) try {
    if (!shape(before,e) || !selected(before,e)) return false;
    CombatCreationContext result; project(before,result); after = std::move(result); e = {}; return true;
} catch (const std::bad_alloc&) { return fail(e,"Combat creation projection allocation failed",save::ErrorCode::Limit);
} catch (const std::length_error&) { return fail(e,"Combat creation projection allocation exceeds limits",save::ErrorCode::Limit); }

bool createPreparedCombatWarrior(const save::Document& d, const CombatCreationArmy& input,
                                const CombatPreparationState& before, CombatPreparedWarriorReport& report, save::Error& e) try {
    CombatCreationContext context;
    if (!projectPreparedCombatCreation(before,context,e)) return false;
    CombatCreationReport creation;
    if (!createCombatWarrior(d,input,context,creation,e)) return false;
    CombatPreparedWarriorReport result;
    result.after = before; publish(std::move(creation.after),result.after);
    result.outcome = creation.outcome; result.created = creation.created; result.draws = std::move(creation.draws);
    result.placementFallback = creation.placementFallback; result.missingPlaneRetreat = creation.missingPlaneRetreat;
    result.testedPositions = creation.testedPositions; result.retreatAccessQueries = creation.retreatAccessQueries;
    result.thresholdDefense = creation.thresholdDefense;
    report = std::move(result); e = {}; return true;
} catch (const std::bad_alloc&) { return fail(e,"Prepared Warrior creation allocation failed",save::ErrorCode::Limit);
} catch (const std::length_error&) { return fail(e,"Prepared Warrior creation allocation exceeds limits",save::ErrorCode::Limit); }
} // namespace dl2::simulation
