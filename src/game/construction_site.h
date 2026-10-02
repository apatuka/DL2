// Owned automatic site selection, not placement, construction or payment.
#pragma once
#include <vector>
#include "game/session_rng.h"

namespace dl2::simulation {

struct ConstructionSiteReport {
    int site = -1;
    bool found = false;
    RngSnapshot rngAfter;
    std::vector<RngEvent> draws;
    bool operator==(const ConstructionSiteReport&) const = default;
};

// orig: FindConstructionSite 0044d464 and AreaHasResourceSite 0044d36c.
// Uses the original 36-entry preference order: first legal resource-free
// footprint wins; otherwise the LAST legal resource-bearing footprint wins.
// On sea, type47 without an existing category11 draws TaggedRange(4) through
// Long31 and returns corner0/5/30/35 WITHOUT testing its placement or resources.
// Every other branch consumes no RNG. A canonical empty snapshot is sufficient
// only for those deterministic branches; no seed is inferred from the save.
// Semantic failure to find a site is true with found=false/site=-1. Invalid
// source/type/territory/RNG or resource exhaustion returns false, preserving
// the destination. Input document, input RNG and all globals remain unchanged.
// No owner, affordability, technology, labor, entity/ID allocation or full
// CanBuild permission is implied. In the original, StartConstruction0044db50
// does NOT auto-select: its separate wrapper0044dcc8 invokes this function;
// CreateBuilding0044dcf4 does so only when its signed-short site equals -1.
bool findConstructionSite(const save::Document& source, uint32_t territory,
                          int buildingType, const RngSnapshot& rngBefore,
                          ConstructionSiteReport& destination, save::Error& error);

} // namespace dl2::simulation
