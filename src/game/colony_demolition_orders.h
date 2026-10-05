// Confirmed collective demolition, distinct from the individual building order.
#pragma once
#include "game/entity_lifecycle.h"

namespace dl2::simulation {
struct DemolishColonyOrderRequest { int actor=-1; uint32_t territory=0; };
struct DemolishColonyOrderReport {
    uint32_t territory=0;
    std::vector<uint32_t> removedIds; // Live site traversal order, not vector order.
    std::vector<BuildingLifecycleReport> removals; // Refund and balance after EACH removal.
    BuildingRemovalContext contextAfter;
    bool operator==(const DemolishColonyOrderReport&) const = default;
};

// orig: confirmed collective non-editor0045b304 -> offline00475a60.
// The caller has already confirmed the whole-territory order. Native gate:
// visibility[actor]==4. Additional explicit command policy (as entity_orders):
// actor==localPlayer, human type1, matching Player.index, territory.owner==actor.
// Resolve each of36 site anchors AFTER all earlier removals/balances. Skip only
// stored category11, even if it differs from the canonical building category.
// Refund the current territory owner through removeBuilding(...,context,...).
// No individual-order SeaHab redirect, platform cascade, marine-flag rebuild,
// editor behavior, dialog, networking or delayed shrine consequence execution.
// Context is validated and returned even with no eligible buildings. Source and
// destination may alias, as may context and report.contextAfter. Any error
// preserves source/destination/report/context; success clears error. No globals
// or RNG. This partial command does not enable a playable turn or SAV capture.
bool orderDemolishColony(const save::Document& source,const DemolishColonyOrderRequest& request,
                         const BuildingRemovalContext& context,save::Document& destination,
                         DemolishColonyOrderReport& report,save::Error& error);
} // namespace dl2::simulation
