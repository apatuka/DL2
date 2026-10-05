// Owned combat-stat projections and read-only queries. No battle execution.
#pragma once
#include "game/save_document.h"
#include <cstddef>
#include <cstdint>
#include <optional>
#include <vector>

namespace dl2::simulation {

// Local to one explicitly supplied CombatStatsContext. Not an Army ID, runtime
// handle, or a native Warrior pointer. Reordering the vector changes its meaning.
struct CombatantRef {
    size_t index = 0;
    bool operator==(const CombatantRef&) const = default;
};
struct Combatant {
    int32_t type = 0;           // Warrior+4, canonical UnitDef index0..38.
    int currentOwner = 0;      // Warrior+8: technology27 uses this player slot.
    int originalOwner = 0;     // Warrior+0x1e: race and skill use this slot.
    uint8_t orders = 0;        // Warrior+9, independent of strategic movement.
    int16_t experience = 0;    // Warrior+0x0a; projection caps only the upper end.
    bool supplyPenalty = false; // Warrior+0x1c; snapshot, not recomputed by queries.
    std::optional<CombatantRef> target; // Warrior+0x3c, resolved only when read.
    bool operator==(const Combatant&) const = default;
};
struct CombatStatsContext {
    std::vector<Combatant> combatants;
    bool operator==(const CombatStatsContext&) const = default;
};
enum class CombatStat : uint8_t { Attack, Defense, Speed, RateOfFire, SquaredRange, Accuracy };
struct CombatStats {
    int32_t attack = 0;
    int32_t defense = 0;
    int32_t speed = 0;          // 00447f44, despite the legacy UnitRange name.
    int32_t rateOfFire = 0;     // Original interval/index, not shots per second.
    int32_t squaredRange = 0;   // No square root or clamping to a UI range.
    int32_t accuracy = 0;       // Upper cap100 only: negative results are retained.
    bool operator==(const CombatStats&) const = default;
};

// orig: FUN_00447a40. Negative/99 ->0,100..400 ->1,401 and above ->2.
int32_t combatExperienceLevel(int32_t experience) noexcept;

// orig: FUN_00447a68. Copies Army+6,+8,+0x24,+0x28; experience=min(xp,1000).
// Both owner fields receive Army.owner, target is null, and supplyPenalty is
// (Player.foodFlags &3)!=0. Stored Army.unitClass/movement/health/damage and
// historical pointer words do not influence this projection. This is the
// statistics projection, NOT combat creation00451b68 (which has other effects).
bool projectArmyCombatant(const save::Document& document, uint32_t armyId,
                          Combatant& result, save::Error& error);

// orig:00447c2c,00447da4,00447f44,00448008,004480a8,00448118 and leaves
// 00447f1c,004481a4,00448210,00448284,004482cc. The target is inspected only for
// Command Corps/type15 and only by cadency/range queries; only its canonical
// type is needed, not its owner, race, or own target. Cycles are not traversed.
// Reads SAV racial modifiers, never default race tables or mutable globals.
// Domain: structurally valid full document, canonical type0..38, player slots
// 0..6. Accessed races must be0..6 and an accessed accuracy skill must be0..4.
// Unused targets/races/skills are not read or normalized. An order2 racial
// accuracy override100 bypasses the skill lookup, as in the original.
// Preserves signed division, arithmetic right shift, wrap32, and each stat's
// independent order of modifiers/minima. No experience multiplier is invented.
// On any error the previous result is untouched; success clears error. Inputs,
// global state, and RNG are unchanged. These queries do not advance a turn.
bool combatStat(const save::Document& document, const CombatStatsContext& context,
                CombatantRef combatant, CombatStat statistic, int32_t& result,
                save::Error& error);
bool combatStats(const save::Document& document, const CombatStatsContext& context,
                 CombatantRef combatant, CombatStats& result, save::Error& error);

} // namespace dl2::simulation
