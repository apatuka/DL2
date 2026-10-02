#include "game/entity_creation.h"
#include "game/data_tables.h"
#include "game/entity_rules.h"
#include "game/entity_lifecycle.h"
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

bool racialType(int type) { return type == 1 || type == 2 || type == 3 || type == 39 || type == 37 || type == 23; }

// orig: InitBuilding 0044d890 / PlaceBuildingOnSite 0044d7b4 / CreateBuilding
// 0044dcf4. Each invocation finishes its local labor/roads before the companion.
void appendInitialized(save::Document& d, uint32_t territory, int type, int site,
                       uint16_t id, uint32_t tail, int16_t work,
                       const std::array<int32_t,kNumMaterials>* paid = nullptr) {
    const auto& definition = data::kBuildingTypes[type];
    const auto& t = d.territories[territory - 1].data;
    Building building{};
    building.id = id; building.flags = 6; building.type = uint8_t(type);
    building.category = definition.category;
    building.race = racialType(type) ? uint8_t(d.players[size_t(t.owner)].race) : 0;
    building.territory = int16_t(territory); building.site = int8_t(site);
    building.turnsLeft = work;
    if (paid) std::copy(paid->begin(),paid->end(),building.cost);
    building.prev.raw = tail;
    if (type == 37 && t.owner >= 0) {
        int count = 1; // Init observes its newly allocated/typed record too.
        for (const auto& b : d.buildings)
            if (b.type == 37 && d.territories[size_t(b.territory - 1)].data.owner == t.owner) ++count;
        building.hubLevel = std::bit_cast<int8_t>(uint8_t(count - 1));
    }
    if (tail) for (auto& b : d.buildings) if (b.id == tail) { b.next.raw = id; break; }
    d.buildings.push_back(building);
    auto& sites = d.territories[territory - 1].data.sites;
    sites[site].building.raw = id;
    if (definition.size == 2) {
        sites[site].terrainFlags |= 0x1000;
        sites[site + 1].terrainFlags |= 0x2000;
        sites[site - 6].terrainFlags |= 0x3000;
        sites[site - 5].terrainFlags |= 0x4000;
        road(sites[site + 1]) = 0;
        road(sites[site - 5]) &= 0xfb;
        road(sites[site]) &= 0xfd;
    } else if (definition.size == 5) {
        // Platform anchor receives its ID but NO occupancy flags of its own.
        sites[site - 22].terrainFlags |= 0x3100;
        sites[site - 12].terrainFlags |= 0x1100;
        sites[site - 10].terrainFlags |= 0x5100;
        sites[site - 8].terrainFlags |= 0x4100;
        sites[site + 2].terrainFlags |= 0x2100;
        sites[site - 24].terrainFlags |= 0x6000;
    } else if ((sites[site].terrainFlags & 0x0f00u) == 0x100u) {
        sites[site].terrainFlags = uint16_t((sites[site].terrainFlags & 0xffu) | 0x3200u);
    } else sites[site].terrainFlags |= 0x3000;
}
bool appendCompleted(save::Document& d, uint32_t territory, int type, int site,
                     uint16_t id, uint32_t tail, save::Error& error) {
    appendInitialized(d,territory,type,site,id,tail,0);
    if (!prepareCreatedBuildingLabor(d, id, d, error)) return false;
    SiteRoads roads{d, d.territories[territory - 1].data};
    return roads.run(error);
}
} // namespace

bool createCompletedBuilding(const save::Document& source, const BuildingCreationRequest& request,
                             save::Document& destination, BuildingCreationReport& report,
                             save::Error& error) try {
    BuildingPlacement placement;
    if (!checkBuildingPlacement(source, request.territory, request.buildingType,
                                request.site, placement, error)) return false;
    const auto& territory = source.territories[request.territory - 1].data;
    const auto& definition = data::kBuildingTypes[request.buildingType];
    if (territory.owner < -1 || territory.owner >= kMaxPlayers)
        return fail(error, "completed-building creation has an invalid territory owner");
    const bool racial = racialType(request.buildingType) || request.buildingType == 38;
    if (racial && territory.owner < 0)
        return fail(error, "non-editor racial initialization would read Player[-1]");
    if (racial && (source.players[size_t(territory.owner)].race < 0 ||
                   source.players[size_t(territory.owner)].race >= kMaxPlayers))
        return fail(error, "owner race is outside the original racial table");
    if (placement.reason != PlacementReason::Allowed || !placement.footprint.fits)
        return fail(error, "explicit construction site denied (reason " + std::to_string(int(placement.reason)) + ")");
    for (uint8_t site : placement.footprint.sites) {
        const auto& cell = territory.sites[site];
        const bool freeSocket = definition.size == 1 && (cell.terrainFlags & 0x0f00u) == 0x100u;
        if ((!freeSocket && (cell.terrainFlags >> 8) != 0) || cell.building.raw)
            return fail(error, "explicit footprint would overwrite an occupied cell");
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
    const bool platform = request.buildingType == 38;
    const int32_t companionCounter = std::bit_cast<int32_t>(uint32_t(source.options.nextGlobalId) + 1u);
    const auto companionId = platform ? uint16_t(uint32_t(companionCounter)) : uint16_t(0);
    const int32_t nextCounter = std::bit_cast<int32_t>(uint32_t(source.options.nextGlobalId) + (platform ? 2u : 1u));
    const auto id = uint16_t(uint32_t(nextCounter));
    if (!unusedId(source, id) || (platform && !unusedId(source, companionId)))
        return fail(error, "NextGlobalId produced zero or an existing global ID; no ID search is performed");

    auto candidate = std::make_unique<save::Document>(source);
    candidate->options.nextGlobalId = nextCounter;
    BuildingCreationReport result;
    if (!appendCompleted(*candidate, request.territory, request.buildingType, request.site, id, tail, error)) return false;
    result.createdIds.push_back(id);
    if (platform) {
        result.companionAttempted = true;
        if (candidate->buildings.size() >= 1199) result.companionAllocationFailed = true;
        else {
            if (!appendCompleted(*candidate, request.territory, 39, request.site - 10, companionId, id, error)) return false;
            result.createdIds.push_back(companionId); result.companionBuildingId = companionId;
        }
    }
    if (!save::validate(*candidate, error)) return false;
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

namespace {
bool emitConstructionEvent(save::Document& d, int owner, uint32_t territory, uint16_t eventType,
                           int detail, const ConstructionOrderContext& context,
                           ConstructionOrderReport& report, save::Error& error) {
    ConstructionOrderEvent emitted; emitted.type = eventType; emitted.recipient = owner;
    if (owner == d.options.localPlayer) {
        emitted.local = true;
        const auto& t = d.territories[territory - 1].data;
        const auto* end = static_cast<const char*>(std::memchr(t.name,0,sizeof(t.name)));
        if (!end) return fail(error,"construction event territory name lacks a bounded terminator");
        const std::string name(t.name,size_t(end-t.name));
        LocalEventRequest request; request.type = eventType;
        if (eventType == 64) request.arguments = {std::string(data::kBuildingTypes[detail].name),name};
        else {
            request.arguments = {name,std::string(data::kMaterialNamesLower[detail])};
            request.payload = EventPayload{int32_t(territory),detail}; // Actual LogEventEx.
        }
        auto eventContext = context.events; eventContext.rngBeforeEvents = report.rngAfter;
        if (!logLocalEvent(d,report.logAfter,eventContext,request,report.logAfter,emitted.localReport,error)) return false;
        report.rngAfter = emitted.localReport.rngAfter;
    } else if (std::bit_cast<int8_t>(d.players[size_t(owner)].type) >= 3) {
        if (!context.aiSession) return fail(error,"nonlocal construction event requires an initialized owned AI session");
        if (context.ai.rng != context.events.rngBeforeEvents)
            return fail(error,"construction event and AI contexts must share one initial RNG snapshot");
        emitted.aiDispatched = true;
        report.aiAfter.rng = report.rngAfter;
        const AiEventRequest request{owner,eventType,eventType==60?int32_t(territory):0,eventType==60?detail:0};
        if (!context.aiSession->reactEvent(d,request,report.aiAfter,d,emitted.aiReport,error)) return false;
        report.aiAfter = emitted.aiReport.contextAfter; report.rngAfter = report.aiAfter.rng;
    }
    // Offline host's nonlocal signed type<3 branch deliberately does nothing.
    report.aiAfter.rng = report.rngAfter;
    report.events.push_back(std::move(emitted));
    return true;
}

// orig: 0044da3c. Ascending adjacency, first own creatable sea wins; otherwise
// retain the first strict-highest score. CanCreateUnit does NOT test pool space.
bool constructionPortTarget(const save::Document& d, uint32_t territory, uint16_t& destination, save::Error& error) {
    const auto& t = d.territories[territory - 1].data;
    uint16_t best = 0; unsigned bestScore = 0;
    for (uint32_t i = 1; i <= d.territories.size(); ++i) {
        if (!(t.adjacency[i/16] & (1u << (i%16)))) continue;
        const auto& other = d.territories[i-1].data;
        if (other.terrain != 0 || (other.flags & 0x100u) || !other.numTiles) continue;
        ArmyCreationQuery query;
        if (!canCreateArmy(d,i,12,{},query,error)) return false;
        const bool canCreate = query.reason == ArmyCreationReason::Allowed;
        if (other.owner == t.owner && canCreate) { destination = other.index; return true; }
        const unsigned score = (!best ? 1u : 0u) | (other.owner == -1 ? 2u : 0u) |
                               (other.owner == t.owner ? 4u : 0u) | (canCreate ? 8u : 0u);
        if (bestScore < score) { best = other.index; bestScore = score; }
    }
    destination = best; return true;
}
} // namespace

bool startConstruction(const save::Document& source, const BuildingCreationRequest& request,
                       const ConstructionOrderContext& context, save::Document& destination,
                       ConstructionOrderReport& report, save::Error& error) try {
    BuildingPlacement placement;
    if (!checkBuildingPlacement(source,request.territory,request.buildingType,request.site,placement,error)) return false;
    const auto& original = source.territories[request.territory-1].data;
    const int owner = original.owner;
    if (owner < 0 || owner >= kMaxPlayers) return fail(error,"StartConstruction requires an owned territory");
    const int32_t counter = std::bit_cast<int32_t>(uint32_t(source.options.nextGlobalId)+1u);
    const auto id = uint16_t(uint32_t(counter));
    if (!unusedId(source,id)) return fail(error,"construction NextGlobalId is zero or globally colliding; no ID search occurs");
    auto candidate = std::make_unique<save::Document>(source);
    candidate->options.nextGlobalId = counter;
    ConstructionOrderReport result;
    result.territory = request.territory; result.attemptedId = id;
    result.counterBefore = source.options.nextGlobalId; result.counterAfter = counter;
    result.placementReason = placement.reason;
    result.portTargetBefore = result.portTargetAfter = original.portTarget;
    result.logAfter = context.log; result.aiAfter = context.ai;
    result.rngAfter = context.events.rngBeforeEvents;
    result.aiAfter.rng = result.rngAfter;
    result.payment.collection = context.payment.collection;
    if (placement.reason != PlacementReason::Allowed) result.denial = ConstructionOrderDenial::Placement;
    else if (candidate->buildings.size() >= 1199) result.denial = ConstructionOrderDenial::ReservedPoolSlot;
    else {
        if (!placement.footprint.fits) return fail(error,"accepted construction has an out-of-grid physical footprint");
        const auto& definition = data::kBuildingTypes[request.buildingType];
        for (uint8_t site : placement.footprint.sites) {
            const auto& cell = original.sites[site];
            const bool freeSocket = definition.size == 1 && (cell.terrainFlags & 0xf00u) == 0x100u;
            if (cell.building.raw || (!freeSocket && (cell.terrainFlags >> 8)))
                return fail(error,"construction query early exit would overwrite an existing footprint");
        }
        uint32_t tail = 0;
        if (!buildingTail(source,tail,error)) return false;
        ConstructionRequirements requirements;
        if (!buildingConstructionRequirements(source,request.territory,request.buildingType,requirements,error)) return false;
        if (!payConstructionRequirements(*candidate,request.territory,requirements,context.payment,*candidate,result.payment,error)) return false;
        result.paymentEvaluated = true;
        // Collection callbacks60 precede the success64 callback. Replaying the
        // real dispatch after collection is equivalent here: event60's original
        // AI handler is a verified default return, local formatting reads names
        // only; the ordered RNG/log/payload effects are preserved, not omitted.
        for (const auto& event : result.payment.importFailures)
            if (!emitConstructionEvent(*candidate,event.owner,event.territory,event.eventType,event.material,context,result,error)) return false;
        if (result.payment.failureMask) result.denial = ConstructionOrderDenial::Payment;
        else {
            appendInitialized(*candidate,request.territory,request.buildingType,request.site,id,tail,
                              std::bit_cast<int16_t>(uint16_t(uint32_t(requirements.labor))),&result.payment.paid);
            // Original logs before placement. An owned Document cannot expose
            // an unanchored live record to validating APIs; place first. The
            // exact64 callback reads no tasks/sites (verified AI default), so
            // its data/format/RNG effects commute with these footprint writes.
            if (!emitConstructionEvent(*candidate,owner,request.territory,64,request.buildingType,context,result,error)) return false;
            const bool human = std::bit_cast<int8_t>(candidate->players[size_t(owner)].type) < 3;
            if (!prepareStartedBuildingLabor(*candidate,id,human,*candidate,error)) return false;
            result.localLaborBalanced = human;
            SiteRoads roads{*candidate,candidate->territories[request.territory-1].data};
            if (!roads.run(error)) return false;
            result.siteRoadsRebuilt = true;
            if (definition.category == 7) {
                if (!constructionPortTarget(*candidate,request.territory,result.portTargetAfter,error)) return false;
                candidate->territories[request.territory-1].data.portTarget = result.portTargetAfter;
            }
            result.accepted = true; result.createdIds.push_back(id);
        }
    }
    if (!save::validate(*candidate,error)) return false;
    destination = std::move(*candidate); report = std::move(result); error = {}; return true;
} catch (const std::bad_alloc&) {
    error = {save::ErrorCode::Limit,0,"Construction order allocation failed"}; return false;
} catch (const std::length_error&) {
    error = {save::ErrorCode::Limit,0,"Construction order exceeds container limits"}; return false;
}

bool rebuildTerritorySiteRoads(const save::Document& source, uint32_t territory,
                               save::Document& destination, save::Error& error) try {
    if (!save::validate(source,error)) return false;
    if (source.header.isMap || !source.territoryByIndex(territory)) return fail(error,"site roads require a saved-game territory");
    auto candidate=std::make_unique<save::Document>(source);
    SiteRoads roads{*candidate,candidate->territories[territory-1].data};
    if (!roads.run(error)) return false;
    destination=std::move(*candidate); error={}; return true;
} catch (const std::bad_alloc&) { error={save::ErrorCode::Limit,0,"Site roads allocation failed"}; return false; }
  catch (const std::length_error&) { error={save::ErrorCode::Limit,0,"Site roads exceeds allocation limits"}; return false; }

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
