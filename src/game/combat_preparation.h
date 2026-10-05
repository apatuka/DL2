// Isolated combat prefix, Battle initialization and grid construction.
// This does not select participants, resolve combat or advance a game turn.
#pragma once
#include "game/combat_creation.h"
#include "game/session_rng.h"

namespace dl2::simulation {
inline constexpr size_t kCombatStructureCapacity = 1200;
inline constexpr size_t kCombatBattleCapacity = 32;
struct CombatBattleRef { size_t index = 0; bool operator==(const CombatBattleRef&) const = default; };

// Owned counterpart of the native0x1a combat-building cell. Preparation only
// clears/preserves these fields; combat_buildings implements their creation.
struct CombatStructure {
    std::optional<uint32_t> parentBuildingId;       // +00
    int16_t type = 0;                              // +04
    int32_t x = 0, y = 0;                          // +06,+0a
    int16_t damage = 0, state10 = 0;               // +0e,+10
    uint8_t state12 = 0, preserved13 = 0;           // +12,+13
    int16_t defense = 0;                           // +14
    std::optional<CombatStructureRef> next;         // +16
    bool operator==(const CombatStructure&) const = default;
};
// All bytes of the native0x86 Battle are represented. The core is the single
// authoritative view also consumed by createCombatWarrior, never a cached copy.
struct CombatBattleRecord {
    uint32_t seed = 0;                             // +00
    CombatCreationBattle core;                     // +04,+08,+0c..29,+74,+78,+84
    int16_t attacker = 0;                         // +0a
    uint8_t preserved2a = 0, preserved2b = 0;       // +2a,+2b
    std::array<int16_t,36> roads{};                // +2c..73: signed Site+10 byte or replay word
    std::optional<CombatStructureRef> firstStructure, lastStructure; // +7c,+80
    uint8_t preserved85 = 0;                      // +85
    CombatBattleRecord() { core.defender = 0; }     // memset0, unlike standalone creation's -1 default
    bool operator==(const CombatBattleRecord&) const = default;
};
struct CombatPreparationState {
    std::vector<CombatWarrior> warriors = std::vector<CombatWarrior>(kCombatWarriorCapacity);
    std::vector<CombatStructure> structures = std::vector<CombatStructure>(kCombatStructureCapacity);
    std::vector<CombatBattleRecord> battles = std::vector<CombatBattleRecord>(kCombatBattleCapacity);
    int32_t battleCount = 0, turn = 0, tick = 0, deadline = 0; //005649cc/d0/d4/d8
    uint32_t attackerCount = 0, defenderCount = 0;  //005649e0/e4
    uint32_t warriorCursor = 0, warriorLimit = 839; //00574348/4c
    uint32_t structureCursor = 0, structureLimit = 1199; //0057bd30/34
    std::optional<CombatBattleRef> currentBattle;   //0057cdf8; survives reset as the same physical index
    CombatCreationGrid grid;
    uint32_t privateRng = 0;                       //0057e240, never SessionRng
    int32_t replayMode = 0;                        //004cf850, full32-bit nonzero predicate
    int32_t placementDomain = 0, useGridPenalty = 0;
    std::optional<uint32_t> selectedTerrainTerritory;
    ArmyCreationContext creation;
    uint32_t maximumRandomDraws = 1000000;
    bool operator==(const CombatPreparationState&) const;
};
struct CombatBattleRequest {
    uint32_t territory = 0;
    int16_t defender = 0, attacker = 0; // raw words; begin does not dereference players
    int32_t mode = 0; // branch uses full int32; Battle stores ONLY its low byte
    bool operator==(const CombatBattleRequest&) const = default;
};
struct CombatPhasePreparationReport {
    CombatPreparationState after;
    RngSnapshot sessionRngAfter;
    std::array<RngEvent,kCombatBattleCapacity> draws;
    bool operator==(const CombatPhasePreparationReport&) const = default;
};
struct CombatBattlePreparationReport {
    CombatBattleRef created;
    CombatPreparationState after;
    bool operator==(const CombatBattlePreparationReport&) const = default;
};
struct CombatPreparedWarriorReport {
    CombatCreationOutcome outcome = CombatCreationOutcome::PoolFull;
    std::optional<CombatantRef> created;
    CombatPreparationState after;
    std::vector<CombatCreationDraw> draws;
    bool placementFallback = false, missingPlaneRetreat = false;
    uint32_t testedPositions = 0, retreatAccessQueries = 0;
    int32_t thresholdDefense = 0;
    bool operator==(const CombatPreparedWarriorReport&) const = default;
};

// All bool APIs are atomic: errors preserve destination/report and inputs;
// success clears Error. Input/output aliasing is supported. A full SAV is
// required by document-taking functions. No globals, SAV writes or callbacks.
// Fixed pool shapes are validated; untouched/stale references are NOT followed.

// orig:004571d4. Clears pools/count/cursors/limits ONLY. In particular preserves
// selected Battle index, grid, both clocks, side counters and private RNG.
bool resetCombatPools(const CombatPreparationState&, CombatPreparationState&, save::Error&);
// orig:00457624 prefix, stopping BEFORE0045727c. reset + replayMode0 + turn +
// exactly32 Rand15("Combat") via0046c9cc/004ae5b0. No Long31 or private draw.
bool prepareCombatPhase(const save::Document&, const CombatPreparationState&,
                        const RngSnapshot&, CombatPhasePreparationReport&, save::Error&);
// orig:00456150. Selects next physical Battle0..31; no modulo or overwrite.
// Preserves its seed/support/roads/padding except roads overwritten by mode!=0
// with replayMode0. Seeds private RNG, clears lists/masks/counters and grid.
// Mode0 sea fills flags0x60; mode!=0 ALWAYS builds the colony terrain/road grid.
bool beginCombatBattle(const save::Document&, const CombatBattleRequest&,
                       const CombatPreparationState&, CombatBattlePreparationReport&, save::Error&);
// orig:0045209c. Requires a resolvable selected Battle. Uses sites by ordinal,
// ignoring stored x/y. Replay0 sign-extends Site+10; replay!=0 uses old roads.
// Does not place buildings, run00456618, apply defense or infer occupancy.
bool rebuildCombatGrid(const save::Document&, uint32_t territory,
                       const CombatPreparationState&, CombatPreparationState&, save::Error&);
// orig:004512a8/0045130c/00451340. Explicit physical36x36 bounds x/y=-9..26;
// geometric movement mask is irrelevant here. Terrain bits are ORed, not set.
CombatCreationGrid clearedCombatGrid() noexcept;
bool setCombatGridRoad(const CombatCreationGrid&, int32_t x, int32_t y, int32_t flag,
                       CombatCreationGrid&, save::Error&);
bool addCombatGridTerrain(const CombatCreationGrid&, int32_t x, int32_t y, uint8_t terrain,
                          CombatCreationGrid&, save::Error&);
// Projects the selected Battle and common pools/scratch for the existing leaf.
// This is a snapshot for a call, never a second authoritative state in preparation.
bool projectPreparedCombatCreation(const CombatPreparationState&, CombatCreationContext&, save::Error&);
// Real composition of projection +00451b68 + publication into the same pools.
// Other Battles, structures, clocks and replay mode are preserved. Native null
// creation outcomes succeed unchanged. This does not create missing callers.
bool createPreparedCombatWarrior(const save::Document&, const CombatCreationArmy&,
                                const CombatPreparationState&, CombatPreparedWarriorReport&, save::Error&);
} // namespace dl2::simulation
