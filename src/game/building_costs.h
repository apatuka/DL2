// Owned ProcessBuildingCosts0044f110; not work progression or a whole turn.
#pragma once
#include "game/entity_creation.h"
#include <array>
#include <cstdint>
#include <vector>

namespace dl2::simulation {
struct BuildingCostChange {
    uint32_t buildingId = 0, territory = 0;
    uint16_t flagsBefore = 0, flagsAfter = 0;
    std::array<int32_t,kNumMaterials> paidBefore{}, paidAfter{};
    ConstructionRequirements requirements;
    ConstructionPaymentReport payment;
    bool operator==(const BuildingCostChange&) const = default;
};
struct BuildingCostsReport {
    std::vector<uint32_t> order; // Eligible records, ascending unsigned16 global ID.
    std::vector<BuildingCostChange> buildings; // Same execution order.
    LoadedEventLog logAfter;
    AiReactionContext aiAfter;
    RngSnapshot rngAfter;
    ResourceCollectionState collectionAfter;
    std::vector<ConstructionOrderEvent> events;
    bool operator==(const BuildingCostsReport&) const = default;
};

// orig:0044f110 -> sort0046f908/0046f8cc -> requirements0044de9c/0044df30
// -> incremental collector004720f4. Processes ALL active (flag4), unpaid
// (!flag2), nonzero-type buildings in owned territories. Neither remaining
// work nor task assignment gates this pass. Original sorting covers1200 pool
// slots; owned IDs are unique, so empty slots cannot change observable order.
// City Center37 uses its SAVED signed hubLevel(+0x0c): <1 quarters money only,
// otherwise multiplies ALL11 costs. It does NOT recount current cities.
// No affordability/tech gate or base-credit debit here. Actual freight/imports
// still apply. On collector success set flag2 and clear ALL11 saved paid words;
// on shortage retain accumulated payments and flags. No progress/refresh event.
// Event60 is dispatched via the actual owned local log or AI reaction, with
// explicit shared RNG/city/logistics continuation. No callback/global/I/O.
// False preserves both outputs (including source==destination); success clears
// error. This isolated substep does not authorize a turn or resumable export.
bool processBuildingCosts(const save::Document& source,
                          const ConstructionOrderContext& context,
                          save::Document& destination, BuildingCostsReport& report,
                          save::Error& error);
} // namespace dl2::simulation
