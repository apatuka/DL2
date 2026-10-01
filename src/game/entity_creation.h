// Completed-entity initialization, separate from paid construction orders.
#pragma once
#include "game/save_document.h"
#include <cstdint>
#include <vector>

namespace dl2::simulation {
struct BuildingCreationRequest {
    uint32_t territory = 0;
    int buildingType = 0;
    int site = -1; // Explicit 0..35 only; no hidden FindConstructionSite RNG.
};
struct BuildingCreationReport {
    uint32_t buildingId = 0, territory = 0;
    int buildingType = 0, site = -1;
    int32_t counterBefore = 0, counterAfter = 0;
    std::vector<uint8_t> footprint;
    bool localLaborBalanced = false, siteRoadsRebuilt = false;
    bool operator==(const BuildingCreationReport&) const = default;
};

// orig: NextGlobalId 00474cfc, InitBuilding 0044d890, CreateBuilding 0044dcf4,
// PlaceBuildingOnSite 0044d7b4, RedistributeLabor 0044c9a0, site roads 0047dfdc.
// Creates a FINISHED building with exact local labor/footprint/road effects.
// Supported: owned land territory, explicit vacant size1/2 footprint, ordinary
// non-shrine/non-platform type. Requires CheckConstructionSite==Allowed as a
// deliberate safe-domain restriction (original explicit-site CreateBuilding
// bypasses that check). Rejects minister-managed local records/site jobs.
// Original increments the 32-bit counter once and truncates to u16. Here a
// zero/colliding ID fails transactionally; no search/skip to a free ID occurs.
// Capacity keeps the original pool's last reserved slot (1199 active maximum).
// No costs, payments, events, AI, automatic site, editor, transport, turn, tiles
// or deletion semantics. This is NOT StartConstruction or a completed order.
// Failure preserves source/destination/report; source and destination may alias.
// Success clears error. No globals, RNG, callbacks or filesystem access.
bool createCompletedBuilding(const save::Document& source, const BuildingCreationRequest& request,
                             save::Document& destination, BuildingCreationReport& report,
                             save::Error& error);

struct ArmyTemplateRequest {
    uint32_t territory = 0;
    int owner = -1, unitType = 0;
    uint16_t id = 0;
};
// Pure record initializer from 00445d30/00447190/004a6b48. Does NOT allocate,
// increment IDs, check capacity/placement, link a list, attach cargo, pay, emit
// events or run CanCreateUnit. Special transport/siege and sea-land cargo
// branches are rejected; the result is explicitly a detached TEMPLATE.
// The ID must be unused globally, and owner/race/territory must be valid.
// Failure preserves destination; success clears error; input stays untouched.
// An output aliasing an existing input Army record is rejected explicitly.
bool initializeArmyTemplate(const save::Document& source, const ArmyTemplateRequest& request,
                            Army& destination, save::Error& error);
} // namespace dl2::simulation
