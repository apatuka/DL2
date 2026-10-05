#include "game/combat_buildings.h"
#include "game/combat_building_tables.h"
#include "game/data_tables.h"
#include <bit>
#include <limits>
#include <new>
#include <stdexcept>
#include <utility>

namespace dl2::simulation {
namespace {
bool fail(save::Error& e,const char* text,save::ErrorCode code = save::ErrorCode::InvalidState) {
    e = {code,0,text}; return false;
}
int32_t signed32(uint32_t value) { return std::bit_cast<int32_t>(value); }
int32_t signed8(uint8_t value) { return std::bit_cast<int8_t>(value); }
int16_t signed16(uint32_t value) { return std::bit_cast<int16_t>(uint16_t(value)); }
bool coordinate(int64_t x,int64_t y) { return x >= -9 && x <= 26 && y >= -9 && y <= 26; }
size_t cell(int64_t x,int64_t y) { return size_t((y+9)*36+x+9); }
bool documentValid(const save::Document& d,save::Error& e) {
    return save::validate(d,e) && (!d.header.isMap || fail(e,"Combat building creation requires a full saved-game document"));
}
bool shape(const CombatPreparationState& s,save::Error& e) {
    return (s.warriors.size() == kCombatWarriorCapacity && s.structures.size() == kCombatStructureCapacity &&
            s.battles.size() == kCombatBattleCapacity) || fail(e,"Combat building creation requires the840/1200/32 physical pools");
}
const Territory* territory(const save::Document& d,uint32_t id,save::Error& e) {
    if (!id || id > d.territories.size()) { fail(e,"Combat building query reached an unrepresented territory"); return nullptr; }
    return &d.territories[id-1].data;
}
bool divide(int32_t numerator,int32_t denominator,int32_t& result,save::Error& e) {
    if (!denominator || (numerator == std::numeric_limits<int32_t>::min() && denominator == -1))
        return fail(e,"Combat building query would trap in original signed division");
    result = numerator/denominator; return true;
}
// orig:0044de9c, projection of out[0] ONLY. Labor is a signed table WORD,
// unaffected by owner/terrain or City Center price scaling. Unlike the public
// construction-payment query, this caller supplies Player independently from
// territory.owner. Player.index is read only for City Center's discarded cost
// outputs; retain that access domain without fabricating a territory owner.
bool labor(const save::Document& d,int player,uint8_t type,int32_t& result,save::Error& e) {
    if (type < 1 || type >= data::kNumBuildingTypes) return fail(e,"Combat building type is outside1..47");
    if (type == 37) {
        if (player < 0 || player >= kMaxPlayers) return fail(e,"City Center construction cost reaches an invalid player");
        (void)d.players[size_t(player)].index;
    }
    result = signed16(data::kBuildingTypes[type].buildLabor); return true;
}
// orig:0047f440. Native EAX is105..112, despite the old decompiler's char return.
bool sprite(const save::Document& d,const Building& b,uint32_t selection,uint8_t& value,save::Error& e) {
    const auto* t = territory(d,selection,e); if (!t) return false;
    int32_t cost,percent;
    if (!labor(d,t->owner,b.type,cost,e)) return false;
    const int32_t remaining = signed32(uint32_t(cost)-uint32_t(int32_t(b.turnsLeft)));
    if (!divide(signed32(uint32_t(remaining)*100u),cost,percent,e)) return false;
    const bool large = signed8(data::kBuildingTypes[b.type].size) == 2;
    value = uint8_t(!(b.flags & 2u) ? 111+int(large) : (percent < 30 ? 105 : percent < 60 ? 106 : 107)+3*int(large));
    return true;
}
bool structures(const CombatPreparationState& s,const CombatBattleRecord& b,save::Error& e) {
    if (s.structureCursor >= kCombatStructureCapacity || s.structureLimit >= kCombatStructureCapacity)
        return fail(e,"Combat structure cursors must be physical indices0..1199");
    if (s.structureCursor == s.structureLimit) return true; // No list dereference in native full branch.
    if (bool(b.firstStructure) != bool(b.lastStructure)) return fail(e,"Combat structure head and tail disagree");
    std::array<bool,kCombatStructureCapacity> seen{};
    std::optional<CombatStructureRef> last;
    for (auto at = b.firstStructure; at; at = s.structures[at->index].next) {
        if (at->index >= s.structures.size() || seen[at->index] || at->index == s.structureCursor)
            return fail(e,"Combat structure list contains an invalid, cyclic or allocating cell reference");
        seen[at->index] = true; last = at;
    }
    return last == b.lastStructure || fail(e,"Combat structure tail does not terminate its owning chain");
}
} // namespace

// orig:00451360.
bool markCombatBuildingFootprint(const CombatCreationGrid& before,int32_t x,int32_t y,int32_t size,
                                 CombatFootprintReport& report,save::Error& e) {
    const int32_t span = signed32(uint32_t(size)*3u-1u);
    const int32_t endX = signed32(uint32_t(x)+uint32_t(span)), endY = signed32(uint32_t(y)+uint32_t(span));
    CombatFootprintReport result; result.after = before;
    if (x < endX && y < endY) {
        if (!coordinate(x,y) || !coordinate(int64_t(endX)-1,int64_t(endY)-1))
            return fail(e,"Combat building footprint writes outside the owned36x36 grid");
        for (int32_t row = y; row < endY; ++row) for (int32_t col = x; col < endX; ++col) {
            result.after.flags[cell(col,row)] |= 3u; ++result.markedCells;
        }
    }
    report = result; e = {}; return true;
}
// orig:004513b8.
bool markCombatSeaPlatformFootprint(const CombatCreationGrid& before,int32_t x,int32_t y,
                                    CombatFootprintReport& report,save::Error& e) {
    CombatFootprintReport result; result.after = before;
    for (int32_t row = 0; row < 15; ++row) for (int32_t col = 0; col < 15; ++col) {
        if (combat_building_tables::kSeaPlatformMask[size_t(col*15+row)] == 0) continue;
        const int64_t px = int64_t(x)+col, py = int64_t(y)+row;
        if (!coordinate(px,py)) return fail(e,"Combat platform footprint writes outside the owned36x36 grid");
        result.after.flags[cell(px,py)] |= 3u; ++result.markedCells;
    }
    report = result; e = {}; return true;
}
bool combatBuildingConstructionSprite(const save::Document& d,uint32_t id,uint32_t selection,
                                      uint8_t& value,save::Error& e) try {
    if (!documentValid(d,e)) return false;
    const auto* b = d.buildingById(id); if (!b) return fail(e,"Combat sprite query requires a live Building ID");
    uint8_t result;
    if (!sprite(d,*b,selection,result,e)) return false;
    value = result; e = {}; return true;
} catch (const std::bad_alloc&) { return fail(e,"Combat building sprite query allocation failed",save::ErrorCode::Limit); }

// orig:00451de4.
bool addCombatBuilding(const save::Document& d,uint32_t id,const CombatPreparationState& before,
                       CombatBuildingReport& report,save::Error& e) try {
    if (!documentValid(d,e) || !shape(before,e)) return false;
    const auto* building = d.buildingById(id); if (!building) return fail(e,"Combat building creation requires a live Building ID");
    const auto& b = *building;
    const int32_t size = signed8(data::kBuildingTypes[b.type].size);
    const int32_t x = (int32_t(b.site)%6)*3+1, y = (int32_t(b.site)/6)*3+1-(size*3-3);
    CombatFootprintReport footprint;
    if (b.type == 38) { if (!markCombatSeaPlatformFootprint(before.grid,x,y,footprint,e)) return false; }
    else if (!markCombatBuildingFootprint(before.grid,x,y,size,footprint,e)) return false;
    CombatBuildingReport result; result.after = before; result.after.grid = footprint.after; result.footprintCells = footprint.markedCells;
    auto& s = result.after;
    const bool fort = b.category == 18 && b.turnsLeft == 0 && (b.flags & 4u);
    // Native structure-full return occurs before consulting selected Battle.
    if (!fort && s.structureCursor == s.structureLimit) {
        if (s.structureCursor >= kCombatStructureCapacity) return fail(e,"Combat structure cursor lies outside physical pool");
        result.outcome = CombatBuildingOutcome::StructurePoolFull;
        report = std::move(result); e = {}; return true;
    }
    if (!s.currentBattle || s.currentBattle->index >= s.battles.size())
        return fail(e,"Combat building creation requires a represented selected Battle");
    auto& battle = s.battles[s.currentBattle->index];
    if (fort) {
        CombatCreationArmy army;
        army.owner = std::bit_cast<int8_t>(uint8_t(uint16_t(battle.core.defender)));
        army.type = b.type == 40 ? 32 : uint8_t(uint32_t(b.type)-10u);
        army.orders = 26; army.retreatPercent = 100;
        if (!territory(d,battle.core.territory,e)) return false; // Original reads terrain before0044de9c.
        int32_t cost;
        if (!labor(d,battle.core.defender,b.type,cost,e)) return false;
        if (cost != 0) {
            if (army.type >= data::kNumUnitTypes) return fail(e,"Synthetic fort type reaches an unrepresented UnitDef");
            int32_t damage;
            if (!divide(signed32(uint32_t(int32_t(data::kUnitTypes[army.type].defense))*uint32_t(int32_t(b.turnsLeft))),cost,damage,e)) return false;
            army.damage = signed16(uint32_t(damage));
        }
        result.syntheticArmy = army;
        CombatPreparedWarriorReport creation;
        if (!createPreparedCombatWarrior(d,army,s,creation,e)) return false;
        result.after = std::move(creation.after); result.warrior = creation.created; result.warriorOutcome = creation.outcome;
        result.draws = std::move(creation.draws); result.placementFallback = creation.placementFallback;
        result.missingPlaneRetreat = creation.missingPlaneRetreat; result.testedPositions = creation.testedPositions;
        result.retreatAccessQueries = creation.retreatAccessQueries; result.thresholdDefense = creation.thresholdDefense;
        if (result.warrior) {
            auto& w = result.after.warriors[result.warrior->index];
            w.parent = CombatBuildingParent{id}; w.initialX = w.x = w.currentX = x; w.initialY = w.y = w.currentY = y;
            result.outcome = CombatBuildingOutcome::FortificationCreated;
        } else result.outcome = creation.outcome == CombatCreationOutcome::PoolFull ?
            CombatBuildingOutcome::FortificationPoolFull : CombatBuildingOutcome::FortificationNotCreated;
    } else {
        if (!structures(s,battle,e)) return false;
        const CombatStructureRef slot{s.structureCursor}; s.structureCursor = (s.structureCursor+1u)%uint32_t(kCombatStructureCapacity);
        if (battle.lastStructure) s.structures[battle.lastStructure->index].next = slot;
        else battle.firstStructure = slot;
        battle.lastStructure = slot;
        auto& structure = s.structures[slot.index]; structure.next.reset(); structure.parentBuildingId = id;
        structure.type = int16_t(b.type); structure.x = x; structure.y = y; structure.damage = 0;
        if (b.turnsLeft == 0) structure.state10 = b.category == 18 ? -2 : 0;
        else {
            uint8_t icon;
            if (!sprite(d,b,battle.core.territory,icon,e)) return false;
            structure.state10 = int16_t(uint16_t(icon)*2u);
        }
        structure.state12 = b.race; // +13 padding deliberately untouched.
        if (!territory(d,battle.core.territory,e)) return false;
        int32_t cost;
        if (!labor(d,battle.core.defender,b.type,cost,e)) return false;
        const auto hp = data::kBuildingTypes[b.type].hitPoints;
        if (cost == 0) structure.defense = int16_t(hp); // MOV AL into cleared EAX.
        else {
            const int32_t remaining = signed32(uint32_t(cost)-uint32_t(int32_t(b.turnsLeft)));
            int32_t defense;
            if (!divide(signed32(uint32_t(remaining)*uint32_t(signed8(hp))),cost,defense,e)) return false;
            structure.defense = int16_t(uint8_t(uint32_t(defense)));
        }
        result.structure = slot; result.outcome = CombatBuildingOutcome::StructureCreated;
    }
    report = std::move(result); e = {}; return true;
} catch (const std::bad_alloc&) { return fail(e,"Combat building creation allocation failed",save::ErrorCode::Limit);
} catch (const std::length_error&) { return fail(e,"Combat building creation allocation exceeds limits",save::ErrorCode::Limit); }
} // namespace dl2::simulation
