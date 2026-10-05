// Complete isolated militia/mine callers; no participant phase or combat tick.
#pragma once
#include "game/combat_preparation.h"

namespace dl2::simulation {
struct CombatAuxiliaryPosition {
    int32_t x = 0, y = 0;
    bool operator==(const CombatAuxiliaryPosition&) const = default;
};
struct CombatAuxiliaryAttempt {
    CombatCreationOutcome outcome = CombatCreationOutcome::PoolFull;
    std::optional<CombatantRef> created;
    // Militia overrides all six coordinates AFTER real generic placement.
    std::optional<CombatAuxiliaryPosition> overridePosition;
    size_t drawBegin = 0, drawCount = 0;
    bool placementFallback = false, missingPlaneRetreat = false;
    uint32_t testedPositions = 0, retreatAccessQueries = 0;
    int32_t thresholdDefense = 0;
    bool operator==(const CombatAuxiliaryAttempt&) const = default;
};
struct CombatAuxiliaryOccupancy {
    CombatAuxiliaryPosition position;
    bool occupied = false;
    std::optional<size_t> attemptIndex;
    bool operator==(const CombatAuxiliaryOccupancy&) const = default;
};
struct CombatAuxiliaryReport {
    CombatPreparationState after;
    CombatCreationArmy syntheticArmy;
    int32_t laborBefore = 0, laborRemaining = 0; // mines do not read labor
    std::vector<CombatAuxiliaryAttempt> attempts;
    std::vector<CombatantRef> created;
    std::vector<CombatCreationDraw> draws;
    std::vector<CombatAuxiliaryOccupancy> occupancy; // exact ordered grid probes
    bool operator==(const CombatAuxiliaryReport&) const = default;
};

// Atomic full-SAV queries/composition: all source/context bytes remain owned
// by callers and unchanged. Errors preserve report; context/report aliases work.
// Current Battle and fixed pool shapes are required. No SessionRng/global use.
// Native null creations are successful attempts and keep the caller's progress.
// maximumRandomDraws retains createPreparedCombatWarrior's per-attempt scope.

// orig:004522c0+004522c6 (one function split by disassembly), labor0044ba18,
// occupancy004511d8/004512d4. Null structure or null parent has zero labor;
// nonzero labor uses the physical signed/wrapped spiral, including negative
// totals. Generic placement consumes RNG first; successful militia is then
// relocated and occupies the requested cell. No labor is removed from SAV.
bool createCombatMilitia(const save::Document&, std::optional<CombatStructureRef>,
                         const CombatPreparationState&, CombatAuxiliaryReport&, save::Error&);
// orig:00452250. Exactly24 attempts, type38 on terrain0 and type37 otherwise.
// The supplied territory determines synthetic start/route and mine type; the
// already-selected Battle still controls placement and retreat dependencies.
bool createCombatMines(const save::Document&, int8_t owner, uint32_t territory,
                       const CombatPreparationState&, CombatAuxiliaryReport&, save::Error&);
} // namespace dl2::simulation
