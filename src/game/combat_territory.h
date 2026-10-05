// Territorial participant preparation, ending before combat execution004526b0.
#pragma once
#include "game/combat_auxiliaries.h"
#include "game/combat_buildings.h"

namespace dl2::simulation {
struct CombatTerritoryContext {
    CombatPreparationState preparation;
    int32_t militiaPopulation = 0; //005649c8; only assigned when a Battle is prepared
    bool operator==(const CombatTerritoryContext&) const = default;
};
struct CombatTerritorySelection {
    std::array<int32_t,kMaxPlayers> foreignCounts{};
    bool airOnly = true, minesFriendly = true;
    int32_t warheadOwner = -1, attacker = -1, opponent = -1, mineOwner = -1;
    bool prepared = false;
    // opponent is a selection gate, NOT Battle.defender: begin uses territory.owner.
    bool operator==(const CombatTerritorySelection&) const = default;
};
struct CombatSiteProjection {
    size_t site = 0;
    uint8_t beforeType = 0, beforeRace = 0, afterType = 0, afterRace = 0;
    std::optional<uint32_t> sourceBuilding;
    bool operator==(const CombatSiteProjection&) const = default;
};
struct CombatTerritoryArmyCall {
    uint32_t armyId = 0;
    bool foreign = false, seaDomainSkipped = false;
    std::optional<CombatCreationOutcome> outcome;
    std::optional<CombatantRef> created;
    size_t drawBegin = 0, drawCount = 0;
    bool placementFallback = false, missingPlaneRetreat = false;
    uint32_t testedPositions = 0, retreatAccessQueries = 0;
    int32_t thresholdDefense = 0;
    bool operator==(const CombatTerritoryArmyCall&) const = default;
};
struct CombatTerritoryBuildingCall {
    uint32_t buildingId = 0;
    size_t site = 0;
    CombatBuildingOutcome outcome{};
    std::optional<CombatCreationOutcome> warriorOutcome;
    std::optional<CombatStructureRef> structure;
    std::optional<CombatantRef> warrior;
    size_t drawBegin = 0, drawCount = 0;
    bool operator==(const CombatTerritoryBuildingCall&) const = default;
};
struct CombatTerritoryAuxiliaryCall {
    bool mines = false;
    std::optional<CombatStructureRef> structure;
    CombatCreationArmy syntheticArmy;
    int32_t laborBefore = 0, laborRemaining = 0;
    std::vector<CombatAuxiliaryAttempt> attempts; // draw ranges remain relative to this call
    std::vector<CombatAuxiliaryOccupancy> occupancy;
    size_t drawBegin = 0, drawCount = 0;
    bool operator==(const CombatTerritoryAuxiliaryCall&) const = default;
};
struct CombatTerritoryReport {
    CombatTerritoryContext contextAfter;
    CombatTerritorySelection selection;
    std::optional<CombatBattleRef> battle;
    std::vector<CombatSiteProjection> siteProjection;
    std::vector<CombatTerritoryArmyCall> armies; // foreign then own, each by ascending ID
    std::vector<CombatTerritoryBuildingCall> buildings; // between the two Army passes
    std::vector<CombatTerritoryAuxiliaryCall> auxiliaries; // structure order then mines
    std::vector<CombatCreationDraw> draws;
    uint32_t replaySeed = 0;
    bool defenseRebuilt = false;
    bool operator==(const CombatTerritoryReport&) const = default;
};

// Full-SAV APIs: errors preserve all outputs and caller state; success clears
// Error. Aliasing is supported. No global/SessionRng use, battle ticks or turn.
// orig:00456214. First linked node with smallest unsigned16 ID > signed after.
// A null head is an empty list, not a request to enumerate the whole Army pool.
bool nextCombatArmyById(const save::Document&, uint32_t headArmyId, int32_t after,
                        std::optional<uint32_t>&, save::Error&);
// orig:0044d230. Uses signed saved category, turnsLeft==0 and flags&4. The
// starting site is inclusive; >=36 returns-1, negative is an invalid API input.
bool findActiveCombatBuildingCategory(const save::Document&, uint32_t territory,
                                      int32_t category, int32_t from, int32_t& site,
                                      save::Error&);
// orig:00456618. Clears only cached type; cached race survives unless a source
// building is copied. Socket sources are exactly site+5/site+24 and must resolve.
bool rebuildCombatSiteProjection(const save::Document&, uint32_t territory,
                                  save::Document&, std::vector<CombatSiteProjection>&,
                                  save::Error&);
// orig:004568c8 through00451410, stopping immediately before004526b0. Native
// no-battle selection succeeds with document/context unchanged. Actual creation
// composes the real Army/building/militia/mine leaves, then saves private RNG to
// Battle.seed and builds defense penalties. Existing selection is used explicitly.
bool prepareTerritoryCombat(const save::Document&, uint32_t territory,
                            const CombatTerritoryContext&, save::Document&,
                            CombatTerritoryReport&, save::Error&);
// orig:00456c10 wrapper. Temporarily selects territory for creation, then
// restores the caller's exact selectedTerrainTerritory on success or failure.
bool prepareSelectedTerritoryCombat(const save::Document&, uint32_t territory,
                                    const CombatTerritoryContext&, save::Document&,
                                    CombatTerritoryReport&, save::Error&);
} // namespace dl2::simulation
