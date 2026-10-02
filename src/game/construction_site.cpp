#include "game/construction_site.h"
#include "game/entity_rules.h"
#include "game/supplemental_tables.h"

#include <new>
#include <stdexcept>
#include <string>
#include <utility>

namespace dl2::simulation {
namespace {
bool invalid(save::Error& error, const char* message) {
    error = {save::ErrorCode::InvalidState,0,std::string("Automatic construction site: ") + message};
    return false;
}

// orig: FUN_0044d1a4. Stored category, not type, Active, Built or completion.
bool hasCategory(const save::Document& source, const Territory& territory, uint8_t category) {
    for (const auto& site : territory.sites) {
        const auto* building = source.buildingById(site.building.raw);
        if (building && building->category == category) return true;
    }
    return false;
}

// orig: FUN_0044d3f4. Same decoded jump-table truth set as entity_rules.
bool canBuildAtSea(int type) {
    switch (type) {
    case 19: case 20: case 24: case 25: case 28: case 30: case 33: case 34:
    case 39: case 40: case 41: case 42: case 43: case 44: return true;
    default: return false;
    }
}

// orig: FUN_0044d36c. Site+04 is tested for nonzero over the entire rectangle,
// traversed x++/y-- by INDEX, not persisted Site+00/+01 coordinates. Placement
// is consulted first. All accepted canonical types have an in-grid footprint.
bool resourceSite(const Territory& territory, const BuildingFootprint& footprint) {
    for (const uint8_t site : footprint.sites)
        if (territory.sites[site].value != 0) return true;
    return false;
}

// orig: FindConstructionSite0044d464. Earlier category7/9 tests are also the
// first tests of CheckConstructionSite; repeating them for each candidate is
// observably equivalent (pure, no random draws) and shares canonical policy.
bool select(const save::Document& source, uint32_t territory, int type,
            const Territory& territoryData, SessionRng& rng, ConstructionSiteReport& result,
            save::Error& error) {
    if (territoryData.terrain == 0) {
        if (type == 47) {
            if (hasCategory(source,territoryData,11)) return true;
            RngEvent draw;
            if (!rng.apply({RngOperation::TaggedRange,4,0,"FindConstructionSite"},draw,error)) return false;
            constexpr int corners[4] = {0,5,30,35};
            result.site = corners[draw.value];
            result.draws.push_back(std::move(draw));
            return true;
        }
        if (!hasCategory(source,territoryData,20)) {
            if (type != 38) return true;
        } else if (!canBuildAtSea(type)) return true;
    } else if ((type >= 38 && type <= 44) || type == 47) return true;

    for (const int site : data::kSiteOrder) {
        BuildingPlacement placement;
        if (!checkBuildingPlacement(source,territory,type,site,placement,error)) return false;
        if (placement.reason != PlacementReason::Allowed) continue;
        if (!placement.footprint.fits)
            return invalid(error,"resource scan would leave the 6x6 site array");
        result.site = site;
        if (!resourceSite(territoryData,placement.footprint)) return true;
    }
    return true;
}
} // namespace

bool findConstructionSite(const save::Document& source, uint32_t territory,
                          int buildingType, const RngSnapshot& rngBefore,
                          ConstructionSiteReport& destination, save::Error& error) try {
    if (!save::validate(source,error)) return false;
    if (source.header.isMap) return invalid(error,"requires a saved game, not a reduced map");
    if (buildingType < 1 || buildingType >= data::kNumBuildingTypes)
        return invalid(error,"building type must be 1 through 47");
    const auto* record = source.territoryByIndex(territory);
    if (!record) return invalid(error,"territory index is outside the saved world");
    SessionRng rng;
    if (!rng.restore(rngBefore,error)) return false;
    ConstructionSiteReport next;
    if (!select(source,territory,buildingType,record->data,rng,next,error)) return false;
    next.found = next.site != -1;
    next.rngAfter = rng.snapshot();
    destination = std::move(next);
    error = {};
    return true;
} catch (const std::bad_alloc&) {
    error = {save::ErrorCode::Limit,0,"Automatic construction site allocation failed"}; return false;
} catch (const std::length_error&) {
    error = {save::ErrorCode::Limit,0,"Automatic construction site exceeds allocation limits"}; return false;
} catch (const std::exception& exception) {
    error = {save::ErrorCode::InvalidState,0,
             "Automatic construction site failed: " + std::string(exception.what())};
    return false;
}
} // namespace dl2::simulation
