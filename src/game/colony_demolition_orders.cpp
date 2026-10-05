#include "game/colony_demolition_orders.h"
#include <memory>
#include <new>
#include <stdexcept>
#include <string>
#include <utility>

namespace dl2::simulation {
namespace {
bool fail(save::Error& error,const char* message) {
    error={save::ErrorCode::InvalidState,0,std::string("Collective demolition: ")+message}; return false;
}
bool validContext(const save::Document& source,const BuildingRemovalContext& context,save::Error& error) {
    if (context.pendingShrines.entries.size()>kPendingShrineCapacity) {
        error={save::ErrorCode::Limit,0,"Collective demolition pending shrine queue exceeds ten entries"}; return false;
    }
    for (const auto& entry:context.pendingShrines.entries)
        if (entry.playerSlot<0 || entry.playerSlot>=kMaxPlayers || !source.territoryByIndex(entry.territory))
            return fail(error,"pending shrine context has an invalid player slot or territory");
    return true;
}
} // namespace

// orig: FUN_0045b304, confirmed collective branch; FUN_00475a60 offline leaf.
bool orderDemolishColony(const save::Document& source,const DemolishColonyOrderRequest& request,
                         const BuildingRemovalContext& context,save::Document& destination,
                         DemolishColonyOrderReport& report,save::Error& error) try {
    if (!save::validate(source,error)) return false;
    if (source.header.isMap) return fail(error,"requires a game document, not an editor map");
    if (request.actor<0 || request.actor>=kMaxPlayers || request.actor!=source.options.localPlayer)
        return fail(error,"actor must be the local player");
    const auto& actor=source.players[size_t(request.actor)];
    if (actor.type!=1 || actor.index!=request.actor)
        return fail(error,"actor must be a local human with a matching physical player index");
    const auto* territory=source.territoryByIndex(request.territory);
    if (!territory) return fail(error,"requested territory does not exist");
    if (territory->data.visibility[size_t(request.actor)]!=4 || territory->data.owner!=request.actor)
        return fail(error,"territory must be actor-owned and have native visibility level4");
    if (!validContext(source,context,error)) return false;

    auto candidate=std::make_unique<save::Document>(source);
    DemolishColonyOrderReport result; result.territory=request.territory; result.contextAfter=context;
    for (int site=0;site<kNumSites;++site) {
        // removeBuilding replaces the candidate's arrays. Never retain a
        // Territory/Building pointer across calls or snapshot the36 IDs.
        const auto& current=candidate->territories[size_t(request.territory-1)].data;
        const uint32_t id=current.sites[site].building.raw;
        if (!id) continue;
        const auto* building=candidate->buildingById(id);
        if (!building) return fail(error,"live site contains an unresolved building");
        if (building->category==11) continue;
        const int refundPlayer=current.owner;
        BuildingLifecycleReport removal;
        if (!removeBuilding(*candidate,{id,BuildingRemovalKind::DemolishBuilding,refundPlayer},
                            result.contextAfter,*candidate,removal,error)) return false;
        if (!removal.contextAfter) return fail(error,"building removal omitted its explicit continuation");
        result.contextAfter=*removal.contextAfter;
        result.removedIds.insert(result.removedIds.end(),removal.removedIds.begin(),removal.removedIds.end());
        result.removals.push_back(std::move(removal));
    }
    if (!save::validate(*candidate,error)) return false;
    destination=std::move(*candidate); report=std::move(result); error={}; return true;
} catch (const std::bad_alloc&) {
    error={save::ErrorCode::Limit,0,"Collective demolition allocation failed"}; return false;
} catch (const std::length_error&) {
    error={save::ErrorCode::Limit,0,"Collective demolition exceeds container limits"}; return false;
}
} // namespace dl2::simulation
