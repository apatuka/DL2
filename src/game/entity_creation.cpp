#include "game/entity_creation.h"
#include "game/data_tables.h"
#include "game/entity_rules.h"
#include "game/labor_balance.h"
#include "game/supplemental_tables.h"

#include <algorithm>
#include <bit>
#include <cstring>
#include <memory>
#include <new>
#include <stdexcept>
#include <string>
#include <utility>

namespace dl2::simulation {
namespace {
bool fail(save::Error& error, const std::string& message) {
    error = {save::ErrorCode::InvalidState, 0, "Entity creation: " + message};
    return false;
}
bool unusedId(const save::Document& d, uint16_t id) {
    return id != 0 && !d.buildingById(id) && !d.armyById(id);
}
// orig: AllocBuilding 0044cbec. Saved vector order need not be list order.
bool buildingTail(const save::Document& d, uint32_t& tail, save::Error& error) {
    const Building* head = nullptr;
    tail = 0;
    for (const auto& b : d.buildings) if (b.prev.raw == 0) {
        if (head) return fail(error, "building active list has more than one head");
        head = &b;
    }
    size_t visited = 0;
    for (auto* b = head; b; b = d.buildingById(b->next.raw)) {
        if (++visited > d.buildings.size() || b->prev.raw != tail)
            return fail(error, "building active list is cyclic or nonreciprocal");
        tail = b->id;
    }
    return visited == d.buildings.size() || fail(error, "building active list is disconnected");
}
uint8_t& road(BuildingSite& site) { return site.unk_05[11]; }
int16_t pathCost(const BuildingSite& site) {
    return std::bit_cast<int16_t>(uint16_t(uint16_t(site.unk_05[13]) | (uint16_t(site.unk_05[14]) << 8)));
}
void pathCost(BuildingSite& site, int value) {
    const auto low = uint16_t(value);
    site.unk_05[13] = uint8_t(low); site.unk_05[14] = uint8_t(low >> 8);
}

// orig: site roads 0047dfdc, recursive search 0047dd58/0047de94 and trace
// 0047ded8. These differ from world-tile roads: depth-first with cost pruning,
// no FIFO160, and trace stops without a write when no lower-cost neighbor exists.
struct SiteRoads {
    save::Document& document;
    Territory& territory;
    size_t steps = 0;
    int target = 0, best = 32767;
    static constexpr uint8_t out[4] = {1,2,4,8};  // low bytes of 004dcbc8
    static constexpr uint8_t back[4] = {4,8,1,2}; // low bytes of 004dcbd0

    bool search(int site, int cost, int depth, save::Error& error) {
        // Canonical positive costs bound recursion depth by the 36 sites.
        // The extra work cap is explicit rejection, never partial success.
        if (depth > kNumSites || ++steps > 1000000) {
            error = {save::ErrorCode::Limit, 0, "Site-road search exceeds its safety bound"};
            return false;
        }
        pathCost(territory.sites[site], cost);
        if (site == target) { best = cost; return true; }
        for (int direction = 0; direction < 4; ++direction) {
            const int x = site % 6 + data::kPathDelta1[direction];
            const int y = site / 6 + data::kPathDelta2[direction];
            if (x < 0 || x >= 6 || y < 0 || y >= 6) continue;
            const int next = x + y * 6;
            auto& neighbor = territory.sites[next];
            if ((neighbor.terrainFlags & 0xff00u) == 0x2000u) continue;
            int weight = 1;
            if (!road(neighbor)) {
                const unsigned terrain = neighbor.terrainFlags & 0xffu;
                if (terrain == 0xff) weight = 25;
                else {
                    if (terrain >= 7) return fail(error, "site-road terrain indexes outside the original movement-cost table");
                    weight = data::kTileMoveCost[terrain];
                }
            }
            const int nextCost = cost + weight;
            if (nextCost < pathCost(neighbor) && nextCost < best)
                if (!search(next, nextCost, depth + 1, error)) return false;
        }
        return true;
    }
    void trace(int site) {
        int cost = pathCost(territory.sites[site]);
        while (cost != 0) {
            int direction = -1, next = site;
            const auto coordinates = territory.sites[site].unk_00;
            const int x = std::bit_cast<int8_t>(uint8_t(coordinates));
            const int y = std::bit_cast<int8_t>(uint8_t(coordinates >> 8));
            for (int candidateDirection = 0; candidateDirection < 4; ++candidateDirection) {
                const int nx = x + data::kPathDelta1[candidateDirection];
                const int ny = y + data::kPathDelta2[candidateDirection];
                if (nx < 0 || nx >= 6 || ny < 0 || ny >= 6) continue;
                const int candidate = nx + ny * 6;
                if (pathCost(territory.sites[candidate]) < cost) {
                    cost = pathCost(territory.sites[candidate]);
                    direction = candidateDirection; next = candidate;
                }
            }
            if (direction < 0) return;
            if (road(territory.sites[next])) cost = 0;
            road(territory.sites[site]) |= out[direction];
            road(territory.sites[next]) |= back[direction];
            site = next;
        }
    }
    bool run(save::Error& error) {
        for (auto& site : territory.sites) road(site) = 0;
        if (territory.terrain == 0) return true;
        int firstHousing = -1;
        for (int site = 0; site < kNumSites; ++site) {
            const auto* b = document.buildingById(territory.sites[site].building.raw);
            if (b && b->category == 17) { firstHousing = site; break; }
        }
        if (firstHousing < 0) return true;
        for (int site = 0; site < kNumSites; ++site) {
            const auto* b = document.buildingById(territory.sites[site].building.raw);
            if (!b || b->type == 0 || site == firstHousing) continue;
            for (auto& entry : territory.sites) pathCost(entry, 32767);
            target = site; best = 32767;
            if (!search(firstHousing, 0, 1, error)) return false;
            trace(site);
        }
        return true;
    }
};
} // namespace

bool createCompletedBuilding(const save::Document& source, const BuildingCreationRequest& request,
                             save::Document& destination, BuildingCreationReport& report,
                             save::Error& error) try {
    BuildingPlacement placement;
    if (!checkBuildingPlacement(source, request.territory, request.buildingType,
                                request.site, placement, error)) return false;
    const auto& territory = source.territories[request.territory - 1].data;
    const auto& definition = data::kBuildingTypes[request.buildingType];
    if (territory.owner < 0 || territory.owner >= kMaxPlayers || territory.terrain == 0)
        return fail(error, "completed-building creation currently requires an owned land territory");
    if (request.buildingType == 38 || request.buildingType == 39 || definition.category == 11 ||
        (definition.size != 1 && definition.size != 2))
        return fail(error, "platform, Sea Hab and shrine creation branches are not implemented");
    if (placement.reason != PlacementReason::Allowed || !placement.footprint.fits)
        return fail(error, "explicit construction site denied (reason " + std::to_string(int(placement.reason)) + ")");
    for (uint8_t site : placement.footprint.sites) {
        const auto& cell = territory.sites[site];
        if ((cell.terrainFlags & 0x0f00u) != 0 || cell.building.raw)
            return fail(error, "platform or occupied footprint requires an unsupported creation branch");
        for (const auto& jobs : source.ministerJobs) for (const auto& job : jobs)
            if (job.type == 3 && job.param[0] == int32_t(request.territory) && job.param[1] == site)
                return fail(error, "footprint is referenced by a BUILD_BLDG minister job");
    }
    for (const auto& b : source.buildings)
        if (b.territory == int(request.territory) && b.minister != 0)
            return fail(error, "local labor redistribution of minister-managed buildings is not supported");
    if (source.buildings.size() >= 1199) {
        error = {save::ErrorCode::Limit, 0, "Completed building creation retains the last of 1200 pool slots"};
        return false;
    }
    uint32_t tail = 0;
    if (!buildingTail(source, tail, error)) return false;
    const int32_t nextCounter = std::bit_cast<int32_t>(uint32_t(source.options.nextGlobalId) + 1u);
    const auto id = uint16_t(uint32_t(nextCounter));
    if (!unusedId(source, id)) return fail(error, "NextGlobalId produced zero or an existing global ID; no ID search is performed");
    const bool racial = request.buildingType == 1 || request.buildingType == 2 || request.buildingType == 3 ||
                        request.buildingType == 37 || request.buildingType == 23;
    const int race = source.players[size_t(territory.owner)].race;
    if (racial && (race < 0 || race >= kMaxPlayers)) return fail(error, "owner race is outside the original racial table");

    auto candidate = std::make_unique<save::Document>(source);
    Building building{}; // Original free pool record is zeroed before reuse.
    building.id = id; building.flags = 6; building.type = uint8_t(request.buildingType);
    building.category = definition.category; building.race = racial ? uint8_t(race) : 0;
    building.territory = int16_t(request.territory); building.site = int8_t(request.site);
    building.prev.raw = tail;
    if (request.buildingType == 37) {
        // CountCityCenters observes the newly allocated/typed record too. Its
        // low byte minus one is narrowed to signed8, then extended to signed16.
        int count = 1;
        for (const auto& b : source.buildings)
            if (b.type == 37 && source.territories[size_t(b.territory - 1)].data.owner == territory.owner) ++count;
        building.hubLevel = std::bit_cast<int8_t>(uint8_t(count - 1));
    }
    if (tail) for (auto& b : candidate->buildings) if (b.id == tail) { b.next.raw = id; break; }
    candidate->buildings.push_back(building);
    auto& sites = candidate->territories[request.territory - 1].data.sites;
    sites[request.site].building.raw = id;
    // orig: 0044d7b4. The other size2 cells are occupancy quadrants, NOT
    // duplicate building anchors. Road writes are bytes at Site+0x10.
    if (definition.size == 2) {
        sites[request.site].terrainFlags |= 0x1000;
        sites[request.site + 1].terrainFlags |= 0x2000;
        sites[request.site - 6].terrainFlags |= 0x3000;
        sites[request.site - 5].terrainFlags |= 0x4000;
        road(sites[request.site + 1]) = 0;
        road(sites[request.site - 5]) &= 0xfb;
        road(sites[request.site]) &= 0xfd;
    } else sites[request.site].terrainFlags |= 0x3000;
    candidate->options.nextGlobalId = nextCounter;
    if (!prepareCreatedBuildingLabor(*candidate, id, *candidate, error)) return false;
    SiteRoads roads{*candidate, candidate->territories[request.territory - 1].data};
    if (!roads.run(error) || !save::validate(*candidate, error)) return false;

    BuildingCreationReport result;
    result.buildingId = id; result.territory = request.territory;
    result.buildingType = request.buildingType; result.site = request.site;
    result.counterBefore = source.options.nextGlobalId; result.counterAfter = nextCounter;
    result.footprint = std::move(placement.footprint.sites);
    result.localLaborBalanced = true; result.siteRoadsRebuilt = true;
    destination = std::move(*candidate); report = std::move(result); error = {};
    return true;
} catch (const std::bad_alloc&) {
    error = {save::ErrorCode::Limit, 0, "Entity creation allocation failed"}; return false;
} catch (const std::length_error&) {
    error = {save::ErrorCode::Limit, 0, "Entity creation exceeds container limits"}; return false;
}

bool initializeArmyTemplate(const save::Document& source, const ArmyTemplateRequest& request,
                            Army& destination, save::Error& error) try {
    for (const auto& army : source.armies)
        if (&army == &destination) return fail(error, "army template output cannot alias an input record");
    if (!save::validate(source, error)) return false;
    if (source.header.isMap) return fail(error, "army template requires a saved game");
    const auto* territory = source.territoryByIndex(request.territory);
    if (!territory || request.owner < 0 || request.owner >= kMaxPlayers ||
        request.unitType <= 0 || request.unitType >= data::kNumUnitTypes || !unusedId(source, request.id))
        return fail(error, "army template has an invalid type, owner, territory or nonunique ID");
    const int race = source.players[size_t(request.owner)].race;
    if (race < 0 || race >= kMaxPlayers) return fail(error, "army owner's race is outside the name table");
    const auto& definition = data::kUnitTypes[request.unitType];
    if (definition.unitClass == 4 || definition.unitClass == 19 || request.unitType == 35 || request.unitType == 36)
        return fail(error, "transport and paired siege initialization branches are not implemented");
    if ((territory->data.terrain == 0 && definition.domain == data::kDomainLand) ||
        (territory->data.terrain != 0 && definition.domain == data::kDomainSea))
        return fail(error, "army template would require cargo attachment or incompatible terrain");
    Army result{};
    result.id = request.id; result.type = uint8_t(request.unitType);
    result.unitClass = definition.unitClass; result.owner = int8_t(request.owner);
    // UnitMoves uses MOVSX WORD for the saved tech mask and narrows the sum.
    const uint32_t known = uint32_t(int32_t(std::bit_cast<int16_t>(source.techs[46].knownMask)));
    result.strength = uint8_t(int(definition.moves) + ((known & (1u << unsigned(request.owner))) ? 1 : 0));
    if (definition.unitClass == 6 || definition.unitClass == 11 || definition.unitClass == 13 || definition.unitClass == 17)
        result.moves = 26;
    result.health = 100;
    const std::string name = std::string(data::kRaceNames[race]) + " " + data::kUnitShortNames[request.unitType] +
                             " #" + std::to_string(request.id & 0x3ffu);
    std::memcpy(result.name, name.data(), std::min(name.size(), sizeof(result.name)));
    result.territory.raw = result.dest.raw = result.origin.raw = request.territory;
    destination = result; error = {};
    return true;
} catch (const std::bad_alloc&) {
    error = {save::ErrorCode::Limit, 0, "Army template allocation failed"}; return false;
} catch (const std::length_error&) {
    error = {save::ErrorCode::Limit, 0, "Army template exceeds container limits"}; return false;
}
} // namespace dl2::simulation
