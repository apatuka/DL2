#include "game/entity_rules.h"
#include "game/data_tables.h"

#include <new>
#include <stdexcept>
#include <string>
#include <utility>

namespace dl2::simulation {
namespace {

bool invalid(save::Error& error, const char* message) {
    error = {save::ErrorCode::InvalidState, 0, std::string("Building placement: ") + message};
    return false;
}

template<class Operation> bool guarded(Operation&& operation, save::Error& error) {
    try { return operation(); }
    catch (const std::bad_alloc&) {
        error = {save::ErrorCode::Limit, 0, "Insufficient memory while checking building placement"};
    } catch (const std::length_error&) {
        error = {save::ErrorCode::Limit, 0, "Building placement allocation exceeds limits"};
    } catch (const std::exception& exception) {
        error = {save::ErrorCode::InvalidState, 0,
                 "Building placement failed: " + std::string(exception.what())};
    }
    return false;
}

bool validType(int type, save::Error& error) {
    if (type < 1 || type >= data::kNumBuildingTypes)
        return invalid(error, "building type must be 1 through 47");
    return true;
}

// orig: FUN_0044d600 / FUN_0044cce4 / FUN_0044d36c. They use the site index,
// not the persisted Site+0/+1 coordinates, to walk x++ and y--.
BuildingFootprint footprint(int type, int site) {
    BuildingFootprint result;
    result.size = data::kBuildingTypes[type].size;
    if (site < 0 || site >= kNumSites) return result;
    const int x = site % 6;
    const int y = site / 6;
    const int size = result.size;
    if (x + size > 6 || y + 1 < size) return result;
    result.fits = true;
    result.sites.reserve(size_t(size) * size_t(size));
    for (int row = y; row > y - size; --row)
        for (int column = x; column < x + size; ++column)
            result.sites.push_back(uint8_t(row * 6 + column));
    return result;
}

// orig: FUN_0044d1a4. Stored Building.category controls this lookup, with no
// completion, Built, Active or owner filter. Only the 36 site anchors count.
bool hasCategory(const save::Document& document, const Territory& territory, uint8_t category) {
    for (const auto& site : territory.sites) {
        const auto* building = document.buildingById(site.building.raw);
        if (building && building->category == category) return true;
    }
    return false;
}

// orig: FUN_0044d2f8. Unlike HasAdjacentLand, this function does not require
// the source territory itself to be sea. The queried terrain is zero here.
bool hasAdjacentSea(const save::Document& document, const Territory& territory) {
    for (uint32_t index = 1; index <= document.territories.size(); ++index) {
        if (!(territory.adjacency[index >> 4] & (1u << (index & 15u)))) continue;
        const auto& other = document.territories[index - 1].data;
        if (other.numTiles != 0 && other.terrain == 0 && !(other.flags & 0x100u)) return true;
    }
    // The original zero-filled sentinel territory 0 has numTiles==0 and never
    // qualifies. Document contains only the real saved territories 1..N.
    return false;
}

// orig: FUN_0044d3f4. Jump bytes at 0044d40f were checked against DEADLOCK.EXE;
// jump targets 0044d438/0044d431 return zero/one. Do not infer this from names.
bool canBuildAtSea(int type) {
    static constexpr uint8_t allowed[26] = {
        1,1,0,0,0,1,1,0,0,1,0,1,0,0,1,1,0,0,0,0,1,1,1,1,1,1
    };
    return type >= 0x13 && type <= 0x2c && allowed[type - 0x13] != 0;
}

// orig: FUN_0044d440.
bool seaOnly(int type) { return (type >= 0x26 && type <= 0x2c) || type == 0x2f; }

// orig: FUN_0044d600. Keep checks in original order: global category/adjacency
// denials precede geometry; within a cell, platform-free precedes occupation.
PlacementReason check(const save::Document& document, const Territory& territory, int type, int site) {
    const auto& definition = data::kBuildingTypes[type];
    if (territory.terrain != 0 && seaOnly(type)) return PlacementReason::SeaOnlyOnLand;
    if (definition.category == 9 && hasCategory(document, territory, 9))
        return PlacementReason::ExistingCityCenter;
    if (definition.category == 20 && hasCategory(document, territory, 20))
        return PlacementReason::ExistingSeaPlatform;
    if (definition.category == 11 && hasCategory(document, territory, 11))
        return PlacementReason::ExistingShrine;
    if (definition.category == 7 && !hasAdjacentSea(document, territory))
        return PlacementReason::PortWithoutAdjacentSea;
    // Reject an off-grid anchor before division/arithmetic so even INT_MIN/MAX
    // inputs have a defined result. Such anchors fail the original first cell.
    if (site < 0 || site >= kNumSites) return PlacementReason::OutOfBounds;
    const int size = definition.size;
    const int x = site % 6;
    const int y = site / 6;
    for (int row = y; row > y - size; --row) {
        for (int column = x; column < x + size; ++column) {
            if (column < 0 || row < 0 || column > 5 || row > 5)
                return PlacementReason::OutOfBounds;
            const auto& candidate = territory.sites[size_t(row * 6 + column)];
            if ((candidate.terrainFlags & 0x0f00u) == 0x0100u)
                return canBuildAtSea(type) ? PlacementReason::Allowed : PlacementReason::UnsupportedPlatformBuilding;
            if (candidate.building.raw != 0 || (candidate.terrainFlags >> 8) != 0)
                return PlacementReason::Occupied;
            const auto terrain = candidate.terrainFlags & 0xffu;
            if (terrain == 0xff && type != 0x26 && type != 0x2f)
                return PlacementReason::UnavailableTerrain;
            if (terrain == 5) return PlacementReason::BlockedTerrain;
        }
    }
    return PlacementReason::Allowed;
}

} // namespace

bool buildingFootprint(int buildingType, int site, BuildingFootprint& destination, save::Error& error) {
    return guarded([&] {
        if (!validType(buildingType, error)) return false;
        auto next = footprint(buildingType, site);
        destination = std::move(next);
        error = {};
        return true;
    }, error);
}

bool checkBuildingPlacement(const save::Document& document, uint32_t territory,
                            int buildingType, int site, BuildingPlacement& destination,
                            save::Error& error) {
    return guarded([&] {
        if (!save::validate(document, error)) return false;
        if (document.header.isMap) return invalid(error, "placement requires a saved-game document, not a reduced map");
        if (!validType(buildingType, error)) return false;
        const auto* record = document.territoryByIndex(territory);
        if (!record) return invalid(error, "territory index is outside the saved world");
        BuildingPlacement next;
        next.territory = territory;
        next.buildingType = buildingType;
        next.site = site;
        next.footprint = footprint(buildingType, site);
        next.reason = check(document, record->data, buildingType, site);
        destination = std::move(next);
        error = {};
        return true;
    }, error);
}

} // namespace dl2::simulation
