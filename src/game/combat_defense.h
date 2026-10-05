// Fortification influence grid; no battle tick or strategic consequences.
#pragma once
#include "game/combat_preparation.h"

namespace dl2::simulation {
struct CombatDefenseSource {
    CombatantRef warrior;
    int32_t squaredRange = 0;
    std::vector<size_t> cells; // Physical grid offsets, in native write order.
    bool operator==(const CombatDefenseSource&) const = default;
};
struct CombatDefenseReport {
    CombatPreparationState after;
    std::vector<CombatDefenseSource> sources;
    bool operator==(const CombatDefenseReport&) const = default;
};
// orig:00451410 ->004480a8,004511a4,00451180. Clears all1296 penalty
// bytes, then adds10 (byte wrap) per active canonical class10 Warrior whose
// current position is within strict signed squared-distance < squaredRange.
// Uses the original valid-cell mask and wrapped, half-open loop endpoints.
// Cells outside the physical grid are skipped without evaluating distance,
// exactly as004511a4 would reject them. Flags, RNG and all pools are preserved.
// Only the selected Battle's first/next chain is followed; cycles and accessed
// invalid references/types fail atomically. Unused owners/targets stay opaque.
// Inputs may alias report.after. Success clears Error. No global state writes.
bool rebuildCombatDefense(const save::Document&, const CombatPreparationState&,
                          CombatDefenseReport&, save::Error&);
} // namespace dl2::simulation
