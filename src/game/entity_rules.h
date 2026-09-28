// Pure structural placement queries. These are NOT an affordability check or
// StartConstruction/CreateBuilding, and never allocate a gameplay entity.
#pragma once
#include <cstdint>
#include <vector>
#include "game/save_document.h"

namespace dl2::simulation {

// Original return codes of CheckConstructionSite (FUN_0044d600).
enum class PlacementReason : uint8_t {
    Allowed = 0,
    OutOfBounds = 1,
    Occupied = 2,
    UnavailableTerrain = 3,
    ExistingCityCenter = 4,
    PortWithoutAdjacentSea = 5,
    BlockedTerrain = 6,
    UnsupportedPlatformBuilding = 7,
    ExistingSeaPlatform = 8,
    SeaOnlyOnLand = 9,
    ExistingShrine = 10
};

struct BuildingFootprint {
    uint8_t size = 0;
    bool fits = false;
    // All size*size sites, anchor row first and descending, columns ascending.
    // Empty when the anchor or the complete rectangle lies outside the 6x6 grid.
    // For Sea Platform this is the checked/cleared 5x5 area, NOT a list of cells
    // written by PlaceBuildingOnSite, which marks only selected platform cells.
    std::vector<uint8_t> sites;
    bool operator==(const BuildingFootprint&) const = default;
};

struct BuildingPlacement {
    uint32_t territory = 0;
    int buildingType = 0;
    int site = -1;
    BuildingFootprint footprint;
    PlacementReason reason = PlacementReason::OutOfBounds;
    bool operator==(const BuildingPlacement&) const = default;
};

// Geometry shared by CheckConstructionSite (0044d600), ClearSiteArea (0044cce4)
// and AreaHasResourceSite (0044d36c). Type must be 1..47. An off-grid site/area
// is a successful query with fits=false, not an error and not auto-placement.
bool buildingFootprint(int buildingType, int site, BuildingFootprint& destination,
                       save::Error& error);

// orig: FUN_0044d600 plus Count/FindBuildingByCategory 0044d1a4,
// HasAdjacentTerrain 0044d2f8, CanBuildAtSea 0044d3f4 and IsSeaOnly 0044d440.
// Preserves original reason precedence and the platform-free early return.
// A true return means a valid QUERY; inspect reason for placement permission.
// No owner/population/technology/payment/logistics/capacity/ID check is implied.
// No FindConstructionSite RNG, road writes, task changes or turn advancement.
// Requires a structurally valid saved-game Document, not a reduced map.
// Original semantic denials clear error. Invalid source/type/territory or an
// allocation failure returns false and preserves the previous destination.
// Both APIs preserve all input, globals, RNG and filesystem state.
bool checkBuildingPlacement(const save::Document& document, uint32_t territory,
                            int buildingType, int site, BuildingPlacement& destination,
                            save::Error& error);

} // namespace dl2::simulation
