#include "game/combat_stats.h"
#include "game/army_state.h"
#include "game/data_tables.h"
#include "game/supplemental_tables.h"
#include <algorithm>
#include <bit>
#include <new>
#include <stdexcept>

namespace dl2::simulation {
namespace {
int32_t add(int32_t a, int32_t b) { return std::bit_cast<int32_t>(uint32_t(a) + uint32_t(b)); }
int32_t sub(int32_t a, int32_t b) { return std::bit_cast<int32_t>(uint32_t(a) - uint32_t(b)); }
int32_t mul(int32_t a, int32_t b) { return std::bit_cast<int32_t>(uint32_t(a) * uint32_t(b)); }
int32_t sar1(int32_t a) { return std::bit_cast<int32_t>((uint32_t(a) >> 1) | (uint32_t(a) & 0x80000000u)); }
bool fail(save::Error& error, const char* message) {
    error = {save::ErrorCode::InvalidState, 0, message};
    return false;
}
bool checkedDocument(const save::Document& d, save::Error& error) {
    return save::validate(d, error) &&
           (!d.header.isMap || fail(error, "Combat statistics require a full saved-game document"));
}
const data::UnitDef& definition(int32_t type) {
    if (type < 0 || type >= data::kNumUnitTypes)
        throw std::domain_error("Combatant type outside canonical unit table");
    return data::kUnitTypes[type];
}
void checkOwner(int owner) {
    if (owner < 0 || owner >= kMaxPlayers)
        throw std::domain_error("Combatant owner outside player slots0..6");
}
const Combatant& resolve(const CombatStatsContext& context, CombatantRef ref) {
    if (ref.index >= context.combatants.size())
        throw std::domain_error("Combatant reference outside the supplied context");
    return context.combatants[ref.index];
}
void checkCombatant(const Combatant& c) {
    (void)definition(c.type);
    checkOwner(c.currentOwner);
    checkOwner(c.originalOwner);
}
int32_t racial(const save::Document& d, const Combatant& c, int row) {
    const int race = d.players[size_t(c.originalOwner)].race;
    if (race < 0 || race >= data::kNumRaces)
        throw std::domain_error("Combatant original-owner race outside canonical races0..6");
    return d.raceStats.v[row][race];
}

// orig: FUN_00447f1c. DAT004fc0f2 = technology27 knownMask; owner+8.
bool technology27(const save::Document& d, const Combatant& c) {
    return (uint32_t(int32_t(std::bit_cast<int16_t>(d.techs[27].knownMask))) &
            (uint32_t(1) << unsigned(c.currentOwner))) != 0;
}
// orig: FUN_00448284 / FUN_004482cc. Boolean use of the original signed words.
int32_t orderBonus(const save::Document& d, const Combatant& c, uint8_t order, int row) {
    return c.orders == order && definition(c.type).unitClass == 1 ? racial(d, c, row) : 0;
}
// orig: FUN_004481a4 / FUN_00448210. Only type15; target classes9/10
// excluded in both, target type23 excluded only in the row32 leaf.
int32_t commandBonus(const save::Document& d, const CombatStatsContext& context,
                     const Combatant& c, int row) {
    if (c.type != 15 || !c.target) return 0;
    const auto& target = resolve(context, *c.target);
    const int targetClass = definition(target.type).unitClass;
    if (targetClass == 9 || targetClass == 10 || (row == 32 && target.type == 23)) return 0;
    return racial(d, c, row);
}
int modifierRow(int unitClass, bool defense) {
    switch (unitClass) {
    case 1: case 6: case 7: case 8: case 11: return defense ? 30 : 29;
    case 2: case 12: return defense ? 36 : 35;
    case 3: case 13: return defense ? 38 : 37;
    case 16: return defense ? 30 : 39; // Sea Colonizer uses different groups.
    case 4: case 5: case 14: case 15: case 17: case 18: case 19: return defense ? 40 : 39;
    case 9: case 20: return defense ? 42 : 41;
    case 10: return defense ? 44 : 43;
    default: return -1;
    }
}
// orig: FUN_00447c2c / FUN_00447da4.
int32_t strength(const save::Document& d, const Combatant& c, bool defense) {
    const auto& def = definition(c.type);
    int32_t value = defense ? def.defense : def.attack;
    if (orderBonus(d, c, 1, 33) || orderBonus(d, c, 2, 34)) value = mul(value, 2);
    const int row = modifierRow(def.unitClass, defense);
    int32_t adjustment = row < 0 ? 0 : racial(d, c, row);
    if (adjustment < 0) adjustment = std::min(mul(adjustment, value) / 10, -1);
    else if (adjustment > 0) adjustment = std::max(mul(adjustment, value) / 10, 1);
    value = add(value, adjustment);
    if (c.supplyPenalty) value = sar1(value);
    return std::max(value, 1);
}
// orig: FUN_00447f44 (speed, not range).
int32_t speed(const save::Document& d, const Combatant& c) {
    int32_t value = add(definition(c.type).speed, racial(d, c, 46));
    if (c.orders == 4) value = mul(value, 2);
    if (orderBonus(d, c, 2, 34)) value /= 2;
    if (technology27(d, c)) value = sub(value, std::max(mul(value, 25) / 100, 1));
    return std::max(value, 0);
}
// orig: FUN_00448008. Command bonuses are predicates, not multipliers here.
int32_t rateOfFire(const save::Document& d, const CombatStatsContext& context, const Combatant& c) {
    int32_t value = definition(c.type).rateOfFire;
    if (commandBonus(d, context, c, 32) || commandBonus(d, context, c, 31)) value = mul(value, 2);
    if (technology27(d, c)) value = sub(value, std::max(mul(value, 10) / 100, 1));
    if (c.orders == 4) value = add(value, 1);
    return std::max(value, -1);
}
// orig: FUN_004480a8. Row32 is a replacement range, row31 squares it.
int32_t squaredRange(const save::Document& d, const CombatStatsContext& context, const Combatant& c) {
    if (orderBonus(d, c, 2, 34)) return 2;
    int32_t value = commandBonus(d, context, c, 32);
    if (!value) value = definition(c.type).range;
    if (commandBonus(d, context, c, 31)) value = mul(value, value);
    return std::max(value, 0);
}
// orig: FUN_00448118. No lower clamp and no supply penalty.
int32_t accuracy(const save::Document& d, const Combatant& c) {
    if (orderBonus(d, c, 2, 34)) return 100;
    const int32_t modifier = racial(d, c, 45);
    const auto skill = d.options.playerSkill[size_t(c.originalOwner)];
    if (skill >= 5) throw std::domain_error("Combatant accuracy skill outside table0..4");
    return std::min(add(add(add(mul(combatExperienceLevel(c.experience), 15), modifier),
                           data::kSkillMoraleAdjust[skill]), 50), 100);
}
int32_t query(const save::Document& d, const CombatStatsContext& context, const Combatant& c,
              CombatStat statistic) {
    switch (statistic) {
    case CombatStat::Attack: return strength(d, c, false);
    case CombatStat::Defense: return strength(d, c, true);
    case CombatStat::Speed: return speed(d, c);
    case CombatStat::RateOfFire: return rateOfFire(d, context, c);
    case CombatStat::SquaredRange: return squaredRange(d, context, c);
    case CombatStat::Accuracy: return accuracy(d, c);
    }
    throw std::domain_error("Unknown combat statistic");
}
} // namespace

// orig: FUN_00447a40.
int32_t combatExperienceLevel(int32_t experience) noexcept {
    return experience < 100 ? 0 : (experience < 401 ? 1 : 2);
}

// orig: FUN_00447a68.
bool projectArmyCombatant(const save::Document& d, uint32_t armyId, Combatant& result, save::Error& error) {
    try {
        if (!checkedDocument(d, error)) return false;
        const auto* a = d.armyById(armyId);
        if (!a) return fail(error, "Combat-stat projection requires a live Army ID");
        (void)definition(int32_t(std::bit_cast<int8_t>(a->type)));
        checkOwner(a->owner);
        Combatant candidate;
        candidate.type = int32_t(std::bit_cast<int8_t>(a->type));
        candidate.currentOwner = candidate.originalOwner = a->owner;
        candidate.orders = army::combatOrders(*a);
        candidate.experience = std::min<int16_t>(a->experience, 1000);
        candidate.supplyPenalty = (d.players[size_t(a->owner)].foodFlags & 3u) != 0;
        result = candidate;
        error = {};
        return true;
    } catch (const std::bad_alloc&) { return fail(error, "Combat-stat projection allocation failed"); }
      catch (const std::exception& e) { return fail(error, e.what()); }
}

bool combatStat(const save::Document& d, const CombatStatsContext& context, CombatantRef ref,
                CombatStat statistic, int32_t& result, save::Error& error) {
    try {
        if (!checkedDocument(d, error)) return false;
        const auto& c = resolve(context, ref);
        checkCombatant(c);
        const int32_t candidate = query(d, context, c, statistic);
        result = candidate;
        error = {};
        return true;
    } catch (const std::bad_alloc&) { return fail(error, "Combat-stat query allocation failed"); }
      catch (const std::exception& e) { return fail(error, e.what()); }
}

bool combatStats(const save::Document& d, const CombatStatsContext& context, CombatantRef ref,
                 CombatStats& result, save::Error& error) {
    try {
        if (!checkedDocument(d, error)) return false;
        const auto& c = resolve(context, ref);
        checkCombatant(c);
        CombatStats candidate;
        candidate.attack = strength(d, c, false);
        candidate.defense = strength(d, c, true);
        candidate.speed = speed(d, c);
        candidate.rateOfFire = rateOfFire(d, context, c);
        candidate.squaredRange = squaredRange(d, context, c);
        candidate.accuracy = accuracy(d, c);
        result = candidate;
        error = {};
        return true;
    } catch (const std::bad_alloc&) { return fail(error, "Combat-stat query allocation failed"); }
      catch (const std::exception& e) { return fail(error, e.what()); }
}
} // namespace dl2::simulation
