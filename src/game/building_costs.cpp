#include "game/building_costs.h"
#include "game/data_tables.h"
#include <algorithm>
#include <bit>
#include <cstring>
#include <memory>
#include <new>
#include <stdexcept>
#include <string>

namespace dl2::simulation {
namespace {
bool fail(save::Error& error,const char* message) {
    error={save::ErrorCode::InvalidState,0,message}; return false;
}
int32_t mul(int32_t a,int32_t b) { return std::bit_cast<int32_t>(uint32_t(a)*uint32_t(b)); }
Building& building(save::Document& d,uint32_t id) {
    for (auto& b:d.buildings) if (b.id==id) return b;
    throw std::logic_error("Building-cost record disappeared during collection");
}
ConstructionRequirements requirements(const Building& b) {
    const auto& def=data::kBuildingTypes[b.type]; ConstructionRequirements result;
    result.labor=std::bit_cast<int16_t>(def.buildLabor);
    result.technology=std::bit_cast<int8_t>(def.techRequired);
    std::copy_n(def.cost,kNumMaterials,result.materials.begin());
    // orig:0044df30. DAT004fa500/004fa51d/004fad78 are exactly type37's
    // labor/technology/cost table entries. Saved +0c, not current city count.
    if (b.type==37) {
        if (b.hubLevel<1) result.materials[0]>>=2; // SAR, defined arithmetic shift in C++20.
        else for (auto& cost:result.materials) cost=mul(cost,b.hubLevel);
    }
    return result;
}
bool emitImport(save::Document& d,const MaterialImportFailure& notice,
                const ConstructionOrderContext& context,BuildingCostsReport& result,
                save::Error& error) {
    if (!notice.territory || notice.territory>d.territories.size() || notice.owner<0 ||
        notice.owner>=kMaxPlayers || notice.material<1 || notice.material>=kNumMaterials)
        return fail(error,"Building-cost import event has invalid references");
    ConstructionOrderEvent event; event.type=notice.eventType; event.recipient=notice.owner;
    if (notice.owner==d.options.localPlayer) {
        const auto& t=d.territories[notice.territory-1].data;
        const auto* end=static_cast<const char*>(std::memchr(t.name,0,sizeof(t.name)));
        if (!end) return fail(error,"Building-cost event name lacks a bounded terminator");
        LocalEventRequest request{notice.eventType,
            {std::string(t.name,size_t(end-t.name)),std::string(data::kMaterialNamesLower[notice.material])},
            EventPayload{int32_t(notice.territory),notice.material}};
        auto input=context.events; input.rngBeforeEvents=result.rngAfter; event.local=true;
        if (!logLocalEvent(d,result.logAfter,input,request,result.logAfter,event.localReport,error)) return false;
        result.rngAfter=event.localReport.rngAfter;
    } else if (std::bit_cast<int8_t>(d.players[size_t(notice.owner)].type)>=3) {
        if (!context.aiSession || context.ai.rng!=context.events.rngBeforeEvents)
            return fail(error,"Building-cost AI event requires owned bindings and shared initial RNG");
        event.aiDispatched=true; result.aiAfter.rng=result.rngAfter;
        if (!context.aiSession->reactEvent(d,{notice.owner,notice.eventType,int32_t(notice.territory),notice.material},
                                           result.aiAfter,d,event.aiReport,error)) return false;
        result.aiAfter=event.aiReport.contextAfter; result.rngAfter=result.aiAfter.rng;
    }
    result.aiAfter.rng=result.rngAfter; result.events.push_back(std::move(event)); return true;
}
} // namespace

bool processBuildingCosts(const save::Document& source,const ConstructionOrderContext& context,
                          save::Document& destination,BuildingCostsReport& report,save::Error& error) try {
    if (!save::validate(source,error)) return false;
    if (source.header.isMap) return fail(error,"Building costs require a saved game");
    SessionRng rng;
    if (!rng.restore(context.events.rngBeforeEvents,error)) return false;
    auto candidate=std::make_unique<save::Document>(source); auto& d=*candidate;
    BuildingCostsReport result; result.logAfter=context.log; result.aiAfter=context.ai;
    result.rngAfter=context.events.rngBeforeEvents; result.aiAfter.rng=result.rngAfter;
    result.collectionAfter=context.payment.collection;
    std::vector<uint32_t> sorted; sorted.reserve(d.buildings.size());
    for (const auto& b:d.buildings) sorted.push_back(b.id);
    // orig:0046f908/0046f8cc compares zero-extended WORD IDs by subtraction.
    // IDs are unique and in0..65535, so neither tie behavior nor overflow matters.
    std::sort(sorted.begin(),sorted.end());
    for (uint32_t id:sorted) {
        const auto& before=building(d,id);
        if (!before.type || (before.flags&2u) || !(before.flags&4u)) continue;
        const uint32_t territory=uint32_t(before.territory);
        const int owner=d.territories[territory-1].data.owner;
        if (owner==-1) continue;
        if (owner<0 || owner>=kMaxPlayers) return fail(error,"Building-cost owner is outside0..6");
        BuildingCostChange change; change.buildingId=id; change.territory=territory;
        change.flagsBefore=before.flags; std::copy_n(before.cost,kNumMaterials,change.paidBefore.begin());
        change.requirements=requirements(before);
        auto paymentContext=context.payment; paymentContext.collection=result.collectionAfter;
        if (!collectConstructionRequirements(d,territory,change.requirements,change.paidBefore,
                                             paymentContext,d,change.payment,error)) return false;
        result.collectionAfter=change.payment.collection;
        auto& after=building(d,id);
        std::copy(change.payment.paid.begin(),change.payment.paid.end(),std::begin(after.cost));
        if (!change.payment.failureMask) {
            after.flags|=2u; std::fill_n(after.cost,kNumMaterials,0);
        }
        change.flagsAfter=after.flags; std::copy_n(after.cost,kNumMaterials,change.paidAfter.begin());
        //004720f4 emits60 while collecting. Its original AI branch returns
        // immediately; local formatting reads only names, so dispatching these
        // ordered notices now preserves effects without borrowing partial state.
        for (const auto& notice:change.payment.importFailures)
            if (!emitImport(d,notice,context,result,error)) return false;
        result.order.push_back(id); result.buildings.push_back(std::move(change));
    }
    if (!save::validate(d,error)) return false;
    destination=std::move(d); report=std::move(result); error={}; return true;
} catch (const std::bad_alloc&) { error={save::ErrorCode::Limit,0,"Building-cost allocation failed"}; return false; }
  catch (const std::length_error&) { error={save::ErrorCode::Limit,0,"Building-cost container exceeds bounds"}; return false; }
  catch (const std::exception& e) { error={save::ErrorCode::InvalidState,0,e.what()}; return false; }
} // namespace dl2::simulation
