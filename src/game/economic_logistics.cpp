#include "game/economic_logistics.h"
#include "game/data_tables.h"
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
bool fail(save::Error& error,const char* message,save::ErrorCode code=save::ErrorCode::InvalidState) {
    error={code,0,message}; return false;
}
int32_t sub(int32_t a,int32_t b) { return std::bit_cast<int32_t>(uint32_t(a)-uint32_t(b)); }
bool sourceValid(const save::Document& source,save::Error& error) {
    if (!save::validate(source,error)) return false;
    return !source.header.isMap || fail(error,"Economic logistics requires a saved game");
}
bool collectionValid(const save::Document& d,const ResourceCollectionState& c,save::Error& error) {
    for (size_t i=0;i<c.suppliers.size();++i)
        if (c.suppliers[i].territory>d.territories.size() || (i>d.territories.size() && c.suppliers[i].territory))
            return fail(error,"Economic supplier cache refers outside the owned graph");
    if (c.transfers.size()>250) return fail(error,"Economic transfer ledger exceeds250 records",save::ErrorCode::Limit);
    for (const auto& entry:c.transfers)
        if (!entry.from || !entry.to || entry.from>d.territories.size() || entry.to>d.territories.size() ||
            entry.material<1 || entry.material>=kNumMaterials)
            return fail(error,"Economic transfer ledger has invalid references");
    return true;
}
bool initialize(const save::Document& source,const ConstructionOrderContext& context,
                EconomicLogisticsReport& result,save::Error& error) {
    if (!sourceValid(source,error) || !collectionValid(source,context.payment.collection,error)) return false;
    SessionRng rng; if (!rng.restore(context.events.rngBeforeEvents,error)) return false;
    result.collectionAfter=context.payment.collection; result.logAfter=context.log;
    result.aiAfter=context.ai; result.rngAfter=rng.snapshot(); result.aiAfter.rng=result.rngAfter;
    return true;
}
// orig: FUN_004237d0 (LogEventEx), event60 emitted by00472974. Local portrait
// processing and the actual owned AI handler are required, never fake callbacks.
bool emit(save::Document& d,const MaterialImportFailure& notice,const ConstructionOrderContext& context,
          EconomicLogisticsReport& result,save::Error& error) {
    if (notice.eventType!=60 || notice.owner<0 || notice.owner>=kMaxPlayers || !notice.territory ||
        notice.territory>d.territories.size() || notice.material<1 || notice.material>=kNumMaterials)
        return fail(error,"Economic import event has invalid arguments");
    ConstructionOrderEvent event; event.type=60; event.recipient=notice.owner;
    if (notice.owner==d.options.localPlayer) {
        const auto& region=d.territories[notice.territory-1].data;
        const auto* end=static_cast<const char*>(std::memchr(region.name,0,sizeof(region.name)));
        if (!end) return fail(error,"Economic import event territory name has no bounded terminator");
        LocalEventRequest request{60,{std::string(region.name,size_t(end-region.name)),
            std::string(data::kMaterialNamesLower[notice.material])},EventPayload{int32_t(notice.territory),notice.material}};
        auto input=context.events; input.rngBeforeEvents=result.rngAfter;
        event.local=true;
        if (!logLocalEvent(d,result.logAfter,input,request,result.logAfter,event.localReport,error)) return false;
        result.rngAfter=event.localReport.rngAfter;
    } else if (std::bit_cast<int8_t>(d.players[size_t(notice.owner)].type)>=3) {
        if (!context.aiSession) return fail(error,"Economic import event requires initialized owned AI bindings");
        if (context.ai.rng!=context.events.rngBeforeEvents)
            return fail(error,"Economic AI/event contexts must share the initial RNG");
        result.aiAfter.rng=result.rngAfter; event.aiDispatched=true;
        if (!context.aiSession->reactEvent(d,{notice.owner,60,int32_t(notice.territory),notice.material},
            result.aiAfter,d,event.aiReport,error)) return false;
        result.aiAfter=event.aiReport.contextAfter; result.rngAfter=result.aiAfter.rng;
    }
    result.aiAfter.rng=result.rngAfter; result.events.push_back(std::move(event)); return true;
}
bool collect(save::Document& d,const MaterialCollectionRequest& request,const ConstructionOrderContext& context,
             EconomicLogisticsReport& result,save::Error& error) {
    MaterialCollectionReport collection;
    if (!collectMaterialResources(d,request,result.collectionAfter,d,collection,error)) return false;
    result.collectionAfter=collection.collection;
    // A60 handler does not change supply/stock: original AI default return;
    // local formatting reads territory name and consumes only portrait RNG.
    // Dispatch after the atomic leaf preserves its exact order and effects.
    for (const auto& notice:collection.importFailures)
        if (!emit(d,notice,context,result,error)) return false;
    result.collections.push_back(std::move(collection)); return true;
}
template<class Operation> bool guarded(Operation&& operation,save::Error& error) {
    try { return operation(); }
    catch (const std::bad_alloc&) { return fail(error,"Economic logistics allocation failed",save::ErrorCode::Limit); }
    catch (const std::length_error&) { return fail(error,"Economic logistics container bound exceeded",save::ErrorCode::Limit); }
    catch (const std::exception& exception) { error={save::ErrorCode::InvalidState,0,exception.what()}; return false; }
}
}

bool collectMaterial(const save::Document& source,const MaterialCollectionRequest& request,
    const ConstructionOrderContext& context,save::Document& destination,
    EconomicLogisticsReport& report,save::Error& error) {
    return guarded([&] {
        EconomicLogisticsReport result;
        if (!initialize(source,context,result,error)) return false;
        auto candidate=std::make_unique<save::Document>(source);
        if (!collect(*candidate,request,context,result,error)) return false;
        destination=std::move(*candidate); report=std::move(result); error={}; return true;
    },error);
}

// orig: FUN_00472bf0 (ImportDeficits), including0047280c at EACH material.
bool importDeficits(const save::Document& source,const ConstructionOrderContext& context,
    save::Document& destination,EconomicLogisticsReport& report,save::Error& error) {
    return guarded([&] {
        EconomicLogisticsReport result;
        if (!initialize(source,context,result,error)) return false;
        for (const auto& region:source.territories)
            if (region.data.owner<-1 || region.data.owner>=kMaxPlayers)
                return fail(error,"Economic import territory owner is outside-1..6");
        auto candidate=std::make_unique<save::Document>(source);
        size_t attempts=0;
        for (int material=1;material<kNumMaterials;++material) {
            for (size_t i=1;i<=candidate->territories.size();++i) result.collectionAfter.suppliers[i]={};
            bool again;
            do {
                again=false;
                for (uint32_t i=1;i<=candidate->territories.size();++i) {
                    // The called collector replaces the candidate Document;
                    // no reference into it survives the call.
                    const auto& t=candidate->territories[i-1].data;
                    if (t.owner==-1 || t.materials[material]>=t.production[material]) continue;
                    if (++attempts>1000000)
                        return fail(error,"Economic deficit import exceeded the finite traversal budget",save::ErrorCode::Limit);
                    const MaterialCollectionRequest request{i,t.owner,material,
                        std::min(sub(t.production[material],t.materials[material]),10),true};
                    if (!collect(*candidate,request,context,result,error)) return false;
                    if (result.collections.back().result!=-1) again=true;
                }
            } while (again);
        }
        destination=std::move(*candidate); report=std::move(result); error={}; return true;
    },error);
}

// orig: FUN_0046b9a0 ->0046b958/0046b910. Signed race offsets address the
// actual saved RaceStats block, not a fabricated normalized race table.
bool recordFoodEnergyNeeds(const save::Document& source,save::Document& destination,
    NeedsPlan& report,save::Error& error) {
    return guarded([&] {
        NeedsPlan result;
        if (!planNeeds(source,result,error)) return false;
        auto candidate=std::make_unique<save::Document>(source);
        for (const auto& needs:result.territories) {
            auto& t=candidate->territories[needs.territory-1].data;
            t.production[1]=needs.foodReserve; t.production[2]=needs.energyReserve;
        }
        destination=std::move(*candidate); report=std::move(result); error={}; return true;
    },error);
}

// orig: FUN_00471b20 (ResetTransfers), FUN_00471bec (ClearReservations).
bool resetEconomicLogistics(const save::Document& source,const ResourceCollectionState& before,
    save::Document& destination,ResourceCollectionState& after,save::Error& error) {
    return guarded([&] {
        if (!sourceValid(source,error)) return false;
        auto candidate=std::make_unique<save::Document>(source); auto result=before;
        result.transfers.clear();
        for (auto& region:candidate->territories) std::fill_n(region.data.production,kNumMaterials,0);
        destination=std::move(*candidate); after=std::move(result); error={}; return true;
    },error);
}
} // namespace dl2::simulation
