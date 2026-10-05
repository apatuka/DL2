// Building participants and footprint leaves, isolated from battle resolution.
#pragma once
#include "game/combat_preparation.h"

namespace dl2::simulation {
enum class CombatBuildingOutcome {
    StructureCreated, FortificationCreated, StructurePoolFull,
    FortificationPoolFull, FortificationNotCreated
};
struct CombatFootprintReport {
    CombatCreationGrid after;
    uint32_t markedCells = 0; // Original OR3 writes, including already occupied cells.
    bool operator==(const CombatFootprintReport&) const = default;
};
struct CombatBuildingReport {
    CombatBuildingOutcome outcome = CombatBuildingOutcome::StructurePoolFull;
    std::optional<CombatStructureRef> structure;
    std::optional<CombatantRef> warrior;
    CombatPreparationState after;
    uint32_t footprintCells = 0;
    std::optional<CombatCreationArmy> syntheticArmy;
    std::optional<CombatCreationOutcome> warriorOutcome;
    std::vector<CombatCreationDraw> draws;
    bool placementFallback = false, missingPlaneRetreat = false;
    uint32_t testedPositions = 0, retreatAccessQueries = 0;
    int32_t thresholdDefense = 0;
    bool operator==(const CombatBuildingReport&) const = default;
};

// All bool APIs are transactional and permit inputs nested in the previous
// output. SAV/globals/RNG session never change; success clears Error.
// orig:00451360. Signed wrap32 computes span=size*3-1 and loop endpoints.
// Empty native loops succeed unchanged; every reached write must resolve
// inside the owned36x36 grid. Only flag bits0/1 are ORed, penalty is preserved.
bool markCombatBuildingFootprint(const CombatCreationGrid&, int32_t x, int32_t y,
                                 int32_t size, CombatFootprintReport&, save::Error&);
// orig:004513b8. Exact225-word PE mask, indexed[x*15+y], not transposed.
bool markCombatSeaPlatformFootprint(const CombatCreationGrid&, int32_t x, int32_t y,
                                    CombatFootprintReport&, save::Error&);
// orig:0047f440. selectedTerritory supplies owner/terrain independently of
// Building. Computes signed completion percentage BEFORE testing Built flag;
// a zero labor divisor is an API error, including the unbuilt branch.
bool combatBuildingConstructionSprite(const save::Document&, uint32_t buildingId,
                                      uint32_t selectedTerritory, uint8_t&, save::Error&);
// orig:00451de4. Marks footprint BEFORE testing full pools. Full-pool native
// outcomes retain grid writes. A fort uses a real synthetic Army and00451b68;
// on success replaces parent with Building ID and all three position pairs.
// Otherwise appends to the physical1200 structure ring, preserving untouched
// padding. Battle territory/defender are explicit and not inferred from source
// Building ownership. In-progress sprite temporarily uses Battle territory;
// saved selectedTerrainTerritory is always preserved. No synthetic callers,
// militia, mines, grid defense, battle ticks, SAV effects or full-turn success.
bool addCombatBuilding(const save::Document&, uint32_t buildingId,
                       const CombatPreparationState&, CombatBuildingReport&, save::Error&);
} // namespace dl2::simulation
