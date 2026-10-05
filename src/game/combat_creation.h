// Owned isolated Warrior creation. No combat tick, battle setup or SAV mutation.
#pragma once
#include "game/combat_stats.h"
#include "game/entity_lifecycle.h"
#include <array>
#include <optional>
#include <variant>

namespace dl2::simulation {
inline constexpr size_t kCombatWarriorCapacity = 840;
inline constexpr size_t kCombatGridWidth = 36;
inline constexpr size_t kCombatGridCells = kCombatGridWidth * kCombatGridWidth;

// The exact Army fields read by00451b68 and its callees. Synthetic callers
// (forts/militia/mines) may supply a value without a liveArmyId. A live binding
// must match this snapshot; no native pointer or borrowed caller record remains.
struct CombatCreationArmy {
    std::optional<uint32_t> liveArmyId;
    uint16_t id = 0;
    uint8_t type = 0;
    int8_t owner = 0;
    uint8_t orders = 0, mission = 0, retreatPercent = 0;
    int16_t experience = 0, damage = 0;
    uint32_t turnStart = 0, routeOrigin = 0;
    bool operator==(const CombatCreationArmy&) const = default;
};
struct CombatArmyParent { uint32_t id = 0; bool operator==(const CombatArmyParent&) const = default; };
struct CombatBuildingParent { uint32_t id = 0; bool operator==(const CombatBuildingParent&) const = default; };
struct CombatStructureRef { size_t index = 0; bool operator==(const CombatStructureRef&) const = default; };
using CombatWarriorParent = std::variant<std::monostate, CombatArmyParent, CombatBuildingParent, CombatCreationArmy>;

// Pool cell, not a packed native layout. All original reference fields are
// typed/owned. Untouched scalar padding and links remain explicit stale state.
struct CombatWarrior {
    CombatWarriorParent parent;                    // +00
    int32_t type = 0;                              // +04
    uint8_t currentOwner = 0, orders = 0;           // +08,+09
    int16_t experience = 0;                        // +0a
    int32_t x = 0, y = 0;                          // +0c,+10
    uint8_t facing = 0, preserved15 = 0;            // +14,+15
    int16_t damage = 0, retreatDamage = 0;          // +16,+18
    uint16_t retreatTerritory = 0;                 // +1a; ffff means none
    uint8_t supplyPenalty = 0, active = 0;          // +1c,+1d
    uint8_t originalOwner = 0, preserved1f = 0;     // +1e,+1f
    int32_t currentX = 0, currentY = 0;             // +20,+24
    int32_t initialX = 0, initialY = 0;             // +28,+2c
    uint8_t initialFacing = 0, preserved31 = 0;     // +30,+31
    int16_t initialDamage = 0;                     // +32
    uint8_t speedCounter = 0, fireCounter = 0;      // +34,+35
    uint8_t state36 = 0, preserved37 = 0;           // +36,+37
    std::optional<uint32_t> secondaryArmyId;        // +38, retained
    std::optional<CombatantRef> target;             // +3c
    std::optional<CombatStructureRef> structureTarget; // +40
    std::optional<CombatantRef> next, workNext;     // +44,+48
    bool operator==(const CombatWarrior&) const = default;
};
struct CombatCreationBattle {
    uint32_t territory = 0;                        // Battle+04
    int16_t defender = -1;                         // +08, permits neutral -1
    uint8_t playerMask = 0, outsidePlacement = 0;   // +0c,+0d (nonzero predicate)
    std::array<std::array<uint8_t, kMaxPlayers>, 4> support{}; // +0e,+15,+1c,+23
    std::optional<CombatantRef> first, last;        // +74,+78
    uint8_t approachMask = 0;                      // +84
    bool operator==(const CombatCreationBattle&) const = default;
};
struct CombatCreationGrid {
    // Flat[(y+9)*36+(x+9)], x/y=-9..26. Geometric validity is the
    // canonical EXE mask; these two arrays are live battle data, not inferred.
    std::array<uint8_t, kCombatGridCells> flags{};   // 0057ce00; logical0=0057cf4d
    std::array<uint8_t, kCombatGridCells> penalty{}; // 0057d310; logical0=0057d45d
    bool operator==(const CombatCreationGrid&) const = default;
};
struct CombatCreationContext {
    std::vector<CombatWarrior> warriors = std::vector<CombatWarrior>(kCombatWarriorCapacity);
    uint32_t cursor = 0, limit = 839; //004571d4 reset; cursor==limit is native full
    CombatCreationBattle battle;
    CombatCreationGrid grid;
    uint32_t attackerCount = 0, defenderCount = 0; //005649e0/e4, wrap32
    uint32_t rng = 0; //0057e240, PRIVATE combat LCG, never SessionRng/rtl RNG
    int32_t placementDomain = 0, useGridPenalty = 0; //0057e248,004cf854
    std::optional<uint32_t> selectedTerrainTerritory; //00657de0, NOT inferred from battle
    ArmyCreationContext creation; // Real00445b94 context when retreat queries it
    uint32_t maximumRandomDraws = 1000000; // Explicit guard against native infinite retry
    bool operator==(const CombatCreationContext&) const;
};
enum class CombatCreationOutcome { Created, MissionExcluded, DefenderWarhead, PoolFull };
struct CombatCreationDraw {
    uint32_t before = 0, after = 0, bound = 0, value = 0;
    bool operator==(const CombatCreationDraw&) const = default;
};
struct CombatCreationReport {
    CombatCreationOutcome outcome = CombatCreationOutcome::PoolFull;
    std::optional<CombatantRef> created;
    CombatCreationContext after;
    std::vector<CombatCreationDraw> draws;
    bool placementFallback = false, missingPlaneRetreat = false;
    uint32_t testedPositions = 0, retreatAccessQueries = 0;
    int32_t thresholdDefense = 0; // First query uses PREVIOUS slot supply byte.
    bool operator==(const CombatCreationReport&) const = default;
};

// Projects ONLY input fields, preserving raw signed XP (no projection cap1000).
bool projectCombatCreationArmy(const save::Document&, uint32_t armyId,
                              CombatCreationArmy&, save::Error&);
// orig:00451b68 and complete creation leaves, including placement00451550,
// direction00448314, retreat00451928, grid cost00454c2c and RNG00450da4.
// All scalars/links not written by the original are retained. Class10 retains
// parent/coordinates; its BUILDING caller must subsequently supply those data.
// The first defense query occurs before updating supply; XP is not capped.
// Speed/fire results narrow to raw bytes. Native no-room placement FALLS BACK
// to counter%tableLength, even on an occupied/blocked cell. It is not a denial.
// Native null outcomes publish unchanged context with created=nullopt. API
// errors (invalid refs/undefined table indices/draw-limit) publish nothing.
// Input/output aliasing is supported; source document and globals never change.
// Adjacent retreat IDs must be represented1..N; no fake sentinel metadata.
// Missing plane turn-start returnsffff plus a diagnostic, as the original.
// Creation does NOT initialize battle/grid, simulate movement/fire/damage,
// synthesize building/militia callers, or make a partial combat resumable.
bool createCombatWarrior(const save::Document&, const CombatCreationArmy&,
                         const CombatCreationContext&, CombatCreationReport&, save::Error&);
} // namespace dl2::simulation
