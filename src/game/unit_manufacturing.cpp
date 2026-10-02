#include "game/unit_manufacturing.h"
#include "game/data_tables.h"
#include "game/labor_balance.h"
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
int32_t add(int32_t a,int32_t b) { return std::bit_cast<int32_t>(uint32_t(a)+uint32_t(b)); }
int32_t sub(int32_t a,int32_t b) { return std::bit_cast<int32_t>(uint32_t(a)-uint32_t(b)); }
int32_t mul(int32_t a,int32_t b) { return std::bit_cast<int32_t>(uint32_t(a)*uint32_t(b)); }
int16_t short16(int32_t value) { return std::bit_cast<int16_t>(uint16_t(uint32_t(value))); }
int32_t steel(const std::array<int32_t,11>& paid) {
    return add(add(add(mul(paid[7],10),mul(paid[5],5)),mul(paid[6],5)),paid[4]);
}
bool basic(const save::Document& d,uint32_t territory,save::Error& e) {
    if (!save::validate(d,e)) return false;
    if (d.header.isMap || !territory || territory>d.territories.size())
        return fail(e,"Unit manufacturing requires saved-game territory1..N");
    const int owner=d.territories[territory-1].data.owner;
    return (owner>=0 && owner<kMaxPlayers) || fail(e,"Unit manufacturing requires an owned territory");
}
bool validQueue(int queue,save::Error& e) {
    return (queue>=1 && queue<=5) || fail(e,"Unit manufacturing queue category is outside1..5");
}
// orig: QueueUnit0044df94 class switch. Forts/mines have no manufacturing queue.
int category(int type) {
    switch(data::kUnitTypes[type].unitClass) {
    case 1: case 2: return 1;
    case 3: case 13: return 3;
    case 4: case 5: case 12: case 14: case 15: case 16: case 17: case 18: case 19: return 2;
    case 6: case 7: case 8: case 11: return 5;
    case 9: return 4;
    default: return 0;
    }
}
struct Work {
    save::Document& d;
    const UnitManufacturingContext& context;
    UnitManufacturingReport& report;
    save::Error& error;
    uint32_t territory;
    int owner;
    std::vector<QueueRecord>& queue(int q) { return d.territories[territory-1].queues[size_t(q-1)]; }
    Territory& t() { return d.territories[territory-1].data; }
    bool emit(uint16_t type,int detail=0,uint32_t eventTerritory=0,int recipient=-1) {
        if (!eventTerritory) eventTerritory=territory;
        if (recipient<0) recipient=owner;
        if (eventTerritory>d.territories.size() || recipient>=kMaxPlayers)
            return fail(error,"Unit manufacturing event address is invalid");
        ConstructionOrderEvent event; event.type=type; event.recipient=recipient;
        if (recipient==d.options.localPlayer) {
            const auto& region=d.territories[eventTerritory-1].data;
            const auto* end=static_cast<const char*>(std::memchr(region.name,0,sizeof(region.name)));
            if (!end) return fail(error,"Unit manufacturing event name has no bounded NUL terminator");
            const std::string name(region.name,size_t(end-region.name));
            LocalEventRequest request; request.type=type;
            if (type==60) {
                if (detail<0 || detail>=kNumMaterials) return fail(error,"Manufacturing import event material is invalid");
                request.arguments={name,std::string(data::kMaterialNamesLower[detail])};
                request.payload=EventPayload{int32_t(eventTerritory),detail};
            } else if (type==64 || type==68 || type==74) {
                if (detail<1 || detail>=data::kNumUnitTypes) return fail(error,"Manufacturing event unit type is invalid");
                const std::string unit(data::kUnitTypes[detail].name);
                request.arguments=type==74?std::vector<EventArgument>{name,unit}:std::vector<EventArgument>{unit,name};
            } else request.arguments={name};
            auto input=context.effects.events; input.rngBeforeEvents=report.rngAfter;
            event.local=true;
            if (!logLocalEvent(d,report.logAfter,input,request,report.logAfter,event.localReport,error)) return false;
            report.rngAfter=event.localReport.rngAfter;
        } else if (std::bit_cast<int8_t>(d.players[size_t(recipient)].type)>=3) {
            if (!context.effects.aiSession) return fail(error,"Manufacturing AI event requires initialized owned bindings");
            if (context.effects.ai.rng!=context.effects.events.rngBeforeEvents)
                return fail(error,"Manufacturing event/AI contexts must share their initial RNG snapshot");
            report.aiAfter.rng=report.rngAfter; event.aiDispatched=true;
            const AiEventRequest request{recipient,type,type==60?int32_t(eventTerritory):0,type==60?detail:0};
            if (!context.effects.aiSession->reactEvent(d,request,report.aiAfter,d,event.aiReport,error)) return false;
            report.aiAfter=event.aiReport.contextAfter; report.rngAfter=report.aiAfter.rng;
        }
        report.aiAfter.rng=report.rngAfter; report.events.push_back(std::move(event)); return true;
    }
    bool payment(const ConstructionRequirements& requirements,const std::array<int32_t,11>* paid,
                 ConstructionPaymentReport& result) {
        auto input=context.effects.payment; input.collection=report.collectionAfter;
        const bool success=paid?collectConstructionRequirements(d,territory,requirements,*paid,input,d,result,error):
                                payConstructionRequirements(d,territory,requirements,input,d,result,error);
        if (!success) return false;
        report.collectionAfter=result.collection;
        // Actual import60 handlers return from the original AI default branch.
        // Local formatting observes names only. Ordered dispatch after collection
        // preserves all log/RNG effects without a half-valid borrowed Document.
        for (const auto& notice:result.importFailures)
            if (!emit(notice.eventType,notice.material,notice.territory,notice.owner)) return false;
        report.payments.push_back(result); return true;
    }
    bool enqueue(int type,uint32_t& failure,bool& appended) {
        ConstructionRequirements requirements;
        if (!unitManufacturingRequirements(type,requirements,error)) return false;
        const int q=category(type); failure=0; appended=false;
        if (!q) return true; // Authentic QueueUnit no-queue result0.
        if ((type==25 || type==31) && t().population<=100) { failure=UINT32_MAX; return true; }
        ConstructionPaymentReport paid;
        if (!payment(requirements,nullptr,paid)) return false;
        failure=paid.failureMask;
        if (failure) return true;
        if (queue(q).size()>=255) return fail(error,"Unit queue exceeds archival255-record bound",save::ErrorCode::Limit);
        QueueRecord value{}; value.unitType=uint8_t(type); value.count=uint16_t(uint32_t(requirements.labor));
        std::copy(paid.paid.begin(),paid.paid.end(),std::begin(value.data));
        queue(q).push_back(value); appended=true; report.queueStructureChanged=true;
        if (type==25 || type==31) {
            t().population=short16(sub(t().population,100));
            if (!balanceTerritoryLabor(d,territory,d,error)) return false;
        }
        return true;
    }
    bool financeHead(int q,bool& blocked) {
        blocked=false;
        if (queue(q).empty()) return true;
        const int type=queue(q).front().unitType;
        ConstructionRequirements needs;
        if (!unitManufacturingRequirements(type,needs,error)) return false;
        std::array<int32_t,11> paid; std::copy_n(queue(q).front().data,11,paid.begin());
        bool deficit=paid[0]<needs.materials[0];
        for (size_t material=1;material<11 && !deficit;++material) {
            if (material>=5 && material<=7) continue;
            deficit=(material==4?steel(paid):paid[material])<needs.materials[material];
        }
        if (!deficit) return true;
        bool moneyMissing=false;
        if (paid[0]<needs.materials[0]) {
            const int32_t difference=sub(needs.materials[0],paid[0]);
            auto& money=d.players[size_t(owner)].credits;
            if (money<difference) moneyMissing=true;
            else { money=sub(money,difference); paid[0]=needs.materials[0]; }
        }
        ConstructionPaymentReport collection;
        if (!payment(needs,&paid,collection)) return false;
        if (moneyMissing || collection.failureMask) {
            blocked=true; report.headFinancingBlocked=true;
            report.failureMask=collection.failureMask|(moneyMissing?1u:0u);
            if (!emit(74,type)) return false;
            std::copy(collection.paid.begin(),collection.paid.end(),std::begin(queue(q).front().data));
        } else {
            // Exact0044e174: only QueueCurSetCount, NOT QueueCurSetData. A later
            // incomplete reinsert retains old paid data and may charge again.
            queue(q).front().count=uint16_t(uint32_t(needs.labor));
        }
        return true;
    }
    bool spawn(int type,bool& created) {
        uint32_t target=territory;
        if (data::kUnitTypes[type].domain==data::kDomainSea) {
            const int destination=std::bit_cast<int16_t>(t().portTarget);
            if (destination<=0 || size_t(destination)>d.territories.size())
                return fail(error,"Manufacturing sea unit requires a real positive portTarget; sentinel0 is unsupported");
            target=uint32_t(destination);
        }
        ArmyCreationQuery allowed;
        if (!canCreateArmy(d,target,type,context.creation,allowed,error)) return false;
        if (allowed.reason!=ArmyCreationReason::Allowed || !allowed.poolAvailable) {
            // SyncCreateUnit00477784 consumes ID BEFORE its denied CreateUnit.
            const int32_t next=add(d.options.nextGlobalId,1);
            const uint16_t id=uint16_t(uint32_t(next));
            if (!id || d.armyById(id) || d.buildingById(id))
                return fail(error,"Denied manufacturing spawn attempted zero/colliding ID");
            d.options.nextGlobalId=next; created=false;
            report.creationBlocked=true;
            report.creationDenial=allowed.poolAvailable?allowed.reason:ArmyCreationReason::ReservedPoolSlot;
            return true;
        }
        ArmyLifecycleReport creation;
        if (!createArmy(d,{target,owner,type},context.creation,d,creation,error)) return false;
        report.createdIds.insert(report.createdIds.end(),creation.createdIds.begin(),creation.createdIds.end());
        report.creations.push_back(std::move(creation)); created=true; return true;
    }
};
bool initialize(const save::Document& source,uint32_t territory,const UnitManufacturingContext& context,
                UnitManufacturingReport& result,save::Error& error) {
    if (!basic(source,territory,error)) return false;
    SessionRng rng; if (!rng.restore(context.effects.events.rngBeforeEvents,error)) return false;
    result.territory=territory;
    result.populationBefore=result.populationAfter=source.territories[territory-1].data.population;
    result.logAfter=context.effects.log; result.aiAfter=context.effects.ai;
    result.rngAfter=rng.snapshot(); result.aiAfter.rng=result.rngAfter;
    result.collectionAfter=context.effects.payment.collection; return true;
}
template<class Action> bool guarded(Action action,save::Error& error) {
    try { return action(); }
    catch (const std::bad_alloc&) { return fail(error,"Manufacturing allocation failed",save::ErrorCode::Limit); }
    catch (const std::length_error&) { return fail(error,"Manufacturing allocation exceeds limits",save::ErrorCode::Limit); }
    catch (const std::exception& e) { error={save::ErrorCode::InvalidState,0,e.what()}; return false; }
}
} // namespace

bool unitManufacturingRequirements(int unitType,ConstructionRequirements& destination,save::Error& error) {
    if (unitType<1 || unitType>=data::kNumUnitTypes) return fail(error,"Unit manufacturing type outside1..38");
    const auto& def=data::kUnitTypes[unitType]; ConstructionRequirements result;
    result.labor=std::bit_cast<int16_t>(def.buildLabor);
    result.technology=def.techRequired; std::copy_n(def.cost,11,result.materials.begin());
    destination=result; error={}; return true;
}
bool queueUnit(const save::Document& source,const QueueUnitRequest& request,const UnitManufacturingContext& context,
               save::Document& destination,UnitManufacturingReport& report,save::Error& error) {
    return guarded([&] {
        UnitManufacturingReport result;
        if (!initialize(source,request.territory,context,result,error)) return false;
        ConstructionRequirements requirements;
        if (!unitManufacturingRequirements(request.unitType,requirements,error)) return false;
        result.queue=category(request.unitType);
        auto candidate=std::make_unique<save::Document>(source);
        Work work{*candidate,context,result,error,request.territory,candidate->territories[request.territory-1].data.owner};
        if (!work.enqueue(request.unitType,result.failureMask,result.queued)) return false;
        result.populationAfter=work.t().population;
        if (!save::validate(*candidate,error)) return false;
        destination=std::move(*candidate); report=std::move(result); error={}; return true;
    },error);
}
bool dequeueUnit(const save::Document& source,const DequeueUnitRequest& request,
                 save::Document& destination,UnitDequeueReport& report,save::Error& error) {
    return guarded([&] {
        if (!basic(source,request.territory,error) || !validQueue(request.queue,error)) return false;
        auto candidate=std::make_unique<save::Document>(source);
        UnitDequeueReport result; result.territory=request.territory; result.queue=request.queue; result.index=request.index;
        result.populationBefore=result.populationAfter=candidate->territories[request.territory-1].data.population;
        const auto& queue=candidate->territories[request.territory-1].queues[size_t(request.queue-1)];
        if (request.index<queue.size()) {
            const QueueRecord record=queue[request.index]; ConstructionRequirements canonical;
            if (!unitManufacturingRequirements(record.unitType,canonical,error)) return false;
            auto& t=candidate->territories[request.territory-1].data;
            auto& money=candidate->players[size_t(t.owner)].credits;
            result.removed=true; result.unitType=record.unitType;
            result.creditsRefunded=canonical.materials[0]; money=add(money,result.creditsRefunded);
            for (size_t material=1;material<11;++material) {
                result.materialsRefunded[material-1]=short16(record.data[material]);
                t.materials[material]=add(t.materials[material],result.materialsRefunded[material-1]);
            }
            if (record.unitType==25 || record.unitType==31) {
                t.population=short16(add(t.population,100));
                if (!balanceTerritoryLabor(*candidate,request.territory,*candidate,error)) return false;
            }
            // Balance sees this queue BEFORE deletion, matching original order.
            auto& nodes=candidate->territories[request.territory-1].queues[size_t(request.queue-1)];
            nodes.erase(nodes.begin()+request.index);
            result.populationAfter=candidate->territories[request.territory-1].data.population;
        }
        if (!save::validate(*candidate,error)) return false;
        destination=std::move(*candidate); report=std::move(result); error={}; return true;
    },error);
}
bool produceUnits(const save::Document& source,const ProduceUnitsRequest& request,const UnitManufacturingContext& context,
                  save::Document& destination,UnitManufacturingReport& report,save::Error& error) {
    return guarded([&] {
        UnitManufacturingReport result;
        if (!initialize(source,request.territory,context,result,error) || !validQueue(request.queue,error)) return false;
        result.queue=request.queue; result.productionBefore=result.productionRemaining=request.production;
        auto candidate=std::make_unique<save::Document>(source);
        Work work{*candidate,context,result,error,request.territory,candidate->territories[request.territory-1].data.owner};
        bool blocked=false,produced=false;
        if (!work.financeHead(request.queue,blocked)) return false;
        size_t iterations=0;
        while (!blocked && result.productionRemaining>0 && !work.queue(request.queue).empty()) {
            if (++iterations>4096) return fail(error,"Manufacturing exceeds4096 queue-pop safety bound",save::ErrorCode::Limit);
            QueueRecord current=work.queue(request.queue).front(); current.next.raw=0;
            work.queue(request.queue).erase(work.queue(request.queue).begin());
            result.queueStructureChanged=true;
            ConstructionRequirements requirements;
            if (!unitManufacturingRequirements(current.unitType,requirements,error)) return false;
            int remaining=std::bit_cast<int16_t>(current.count);
            if (remaining>0) {
                const int used=std::min(remaining,result.productionRemaining);
                remaining-=used; result.productionRemaining-=used; current.count=uint16_t(remaining);
            }
            bool reinsert=remaining>0;
            if (!reinsert) {
                bool created=false;
                if (!work.spawn(current.unitType,created)) return false;
                if (!created) { reinsert=true; result.productionRemaining=0; }
                else {
                    produced=true;
                    if (!work.emit(68,current.unitType)) return false;
                    if ((uint32_t(int32_t(std::bit_cast<int8_t>(work.t().hoverway))) & (1u<<unsigned(request.queue)))!=0) {
                        uint32_t failure=0; bool appended=false;
                        if (!work.enqueue(current.unitType,failure,appended)) return false;
                        result.queued=result.queued||appended; result.failureMask=failure;
                        if ((failure&0xf001u)==0) {
                            // A material-only failure may enter this branch with
                            // NO node appended. Preserve this native mask quirk.
                            if (!work.emit(64,current.unitType)) return false;
                        } else {
                            if (!work.emit(74,current.unitType)) return false;
                            reinsert=true; result.productionRemaining=0;
                            if (failure&1u) requirements.materials[0]=0;
                            for (size_t material=1;material<11;++material)
                                if (failure&(1u<<material)) requirements.materials[material]=0;
                            ConstructionPaymentReport partial;
                            if (!work.payment(requirements,nullptr,partial)) return false;
                            std::copy(partial.paid.begin(),partial.paid.end(),std::begin(current.data));
                            current.count=uint16_t(uint32_t(requirements.labor));
                        }
                    }
                }
            }
            if (reinsert) {
                if (work.queue(request.queue).size()>=255)
                    return fail(error,"Reinsert exceeds archival255-node queue bound",save::ErrorCode::Limit);
                work.queue(request.queue).insert(work.queue(request.queue).begin(),current);
            }
        }
        if (produced && work.queue(request.queue).empty())
            if (!work.emit(uint16_t(68+request.queue))) return false;
        result.populationAfter=work.t().population;
        if (!save::validate(*candidate,error)) return false;
        destination=std::move(*candidate); report=std::move(result); error={}; return true;
    },error);
}
} // namespace dl2::simulation
