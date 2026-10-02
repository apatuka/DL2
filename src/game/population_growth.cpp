#include "game/population_growth.h"
#include "game/data_tables.h"
#include "game/labor_balance.h"
#include <algorithm>
#include <bit>
#include <cstring>
#include <limits>
#include <memory>
#include <stdexcept>
namespace dl2::simulation {
namespace {
int32_t add(int32_t a,int32_t b) { return std::bit_cast<int32_t>(uint32_t(a)+uint32_t(b)); }
int32_t sub(int32_t a,int32_t b) { return std::bit_cast<int32_t>(uint32_t(a)-uint32_t(b)); }
int32_t mul(int32_t a,int32_t b) { return std::bit_cast<int32_t>(uint32_t(a)*uint32_t(b)); }
int16_t short16(int32_t v) { return std::bit_cast<int16_t>(uint16_t(uint32_t(v))); }
int32_t divided(int32_t a,int32_t b) {
    if (!b || (a==INT32_MIN && b==-1)) throw std::domain_error("Population growth: original signed division would trap");
    return a/b;
}
bool fail(save::Error& e,const char* m) { e={save::ErrorCode::InvalidState,0,m}; return false; }
int16_t racial(const save::Document& d,int owner,int row) {
    if (owner<0 || owner>=kMaxPlayers) throw std::domain_error("Population owner outside player array");
    const int word=row*kMaxPlayers+d.players[size_t(owner)].race;
    if (word<0 || word>=64*kMaxPlayers) throw std::domain_error("Population racial address outside saved block");
    int16_t v; std::memcpy(&v,reinterpret_cast<const uint8_t*>(&d.raceStats)+size_t(word)*2,2); return v;
}
PopulationLimits limits(const save::Document& d,uint32_t territory) {
    const auto& t=d.territories[territory-1].data; PopulationLimits out; int32_t sites=0; bool platform=false;
    if (t.owner<-1 || t.owner>=kMaxPlayers) throw std::domain_error("Population owner outside -1..6");
    for (const auto& site:t.sites) {
        if ((site.terrainFlags&255u)<5) ++sites;
        const auto* b=d.buildingById(site.building.raw); if (!b) continue;
        if (b->category==20) platform=true;
        if (!(b->flags&2) || b->turnsLeft) continue;
        switch (b->type) { case 1:out.housing+=500;break;case 2:out.housing+=1000;break;
            case 3:case 39:out.housing+=1500;break; default:break; }
    }
    out.land=t.terrain==0 && platform?2000:((sites*139+50)/100)*100;
    if (t.owner!=-1) out.housing=mul(out.housing,racial(d,t.owner,24))/100;
    out.maximum=std::min(out.land,out.housing); return out;
}
bool emit(save::Document& d,uint32_t territory,int owner,uint16_t type,
          const ConstructionOrderContext& context,PopulationGrowthReport& result,save::Error& error) {
    ConstructionOrderEvent event; event.type=type; event.recipient=owner;
    if (owner==d.options.localPlayer) {
        const auto& t=d.territories[territory-1].data;
        const auto* end=static_cast<const char*>(std::memchr(t.name,0,sizeof(t.name)));
        if (!end) return fail(error,"Population-growth event name has no bounded terminator");
        LocalEventRequest request{type,{std::string(t.name,size_t(end-t.name))},EventPayload{int32_t(territory),0}};
        auto input=context.events; input.rngBeforeEvents=result.rngAfter; event.local=true;
        if (!logLocalEvent(d,result.logAfter,input,request,result.logAfter,event.localReport,error)) return false;
        result.rngAfter=event.localReport.rngAfter;
    } else if (std::bit_cast<int8_t>(d.players[size_t(owner)].type)>=3) {
        if (!context.aiSession || context.ai.rng!=context.events.rngBeforeEvents)
            return fail(error,"Population-growth event requires owned AI bindings and one initial RNG");
        result.aiAfter.rng=result.rngAfter; event.aiDispatched=true;
        if (!context.aiSession->reactEvent(d,{owner,type,int32_t(territory),0},result.aiAfter,d,event.aiReport,error)) return false;
        result.aiAfter=event.aiReport.contextAfter; result.rngAfter=result.aiAfter.rng;
    }
    result.aiAfter.rng=result.rngAfter; result.events.push_back(std::move(event)); return true;
}
}
// orig: FUN_0046b074/FUN_0046b0e4.
bool territoryPopulationLimits(const save::Document& d,uint32_t territory,PopulationLimits& result,save::Error& e) try {
    if (!save::validate(d,e)) return false;
    if (d.header.isMap || !d.territoryByIndex(territory)) return fail(e,"Population limits require saved-game territory");
    const auto out=limits(d,territory); result=out; e={}; return true;
} catch (const std::exception& ex) { return fail(e,ex.what()); }

// orig: FUN_0046b1ac(apply1). Assembly0046b302 LEA EDX,[ESI-100], SUB
// EAX,EDX confirms the peculiar labor trigger; it is not oldPopulation/100.
bool processPopulationGrowth(const save::Document& source,const PopulationGrowthContext& context,
    save::Document& destination,PopulationGrowthReport& report,save::Error& error) try {
    if (!save::validate(source,error)) return false;
    if (source.header.isMap) return fail(error,"Population growth requires saved game");
    if (context.effects.ai.rng!=context.effects.events.rngBeforeEvents)
        return fail(error,"Population growth requires one shared initial RNG");
    SessionRng rng; if (!rng.restore(context.effects.events.rngBeforeEvents,error)) return false;
    auto candidate=std::make_unique<save::Document>(source); auto& d=*candidate;
    PopulationGrowthReport result; result.logAfter=context.effects.log; result.aiAfter=context.effects.ai;
    result.rngAfter=rng.snapshot(); result.aiAfter.rng=result.rngAfter;
    for (uint32_t index=1;index<=d.territories.size();++index) {
        auto& t=d.territories[index-1].data;
        if (t.owner==-1 || !t.population) continue;
        const int owner=t.owner;
        if (owner<0 || owner>=kMaxPlayers) return fail(error,"Population-growth owner outside0..6");
        PopulationGrowthChange change; change.territory=index; change.before=change.after=t.population;
        change.rateBefore=change.rateAfter=t.unk_32; change.calculatedAfter=t.population;
        if (owner==d.options.localPlayer && (context.campaignFlags&(1u<<10))) {
            change.campaignSkipped=true; result.territories.push_back(change); continue;
        }
        change.limits=limits(d,index); int32_t next=change.limits.maximum;
        const int32_t old=t.population;
        if (old<=change.limits.maximum) {
            const int terrain=std::bit_cast<int8_t>(t.terrain);
            if (terrain<0 || terrain>=6) return fail(error,"Growth terrain address outside canonical table");
            const int32_t densityHalf=divided(mul(old,100),change.limits.maximum)/2;
            int32_t percent=t.unk_28[1]? -10:mul(mul(data::kPopulationGrowthByTerrain[terrain],sub(100,densityHalf)),racial(d,owner,25))/10000;
            if (d.options.fastProduction) percent=mul(percent,2);
            change.growthPercent=percent;
            next=add(mul(old,percent)/100,old);
            if (percent>0 && next<100) next=add(next,20);
            if (next==old) next=add(next,25);
            next=std::min(next,change.limits.maximum);
        }
        change.calculatedAfter=next; t.population=short16(next); change.after=t.population;
        change.laborTrigger=sub(next/100,sub(old,100));
        //0044c9a0(T,n,0,...): when no target building, ONLY BalanceLabor runs.
        if (change.laborTrigger>0) {
            if (!balanceTerritoryLabor(d,index,d,error)) return false;
            change.balancedLabor=true;
        }
        if (old!=next) {
            const auto fresh=limits(d,index);
            const uint16_t notice=next>=fresh.land?52:(next>=fresh.maximum?53:0);
            if (notice && !emit(d,index,owner,notice,context.effects,result,error)) return false;
        }
        change.rateAfter=short16(divided(mul(sub(next,old),100),old));
        d.territories[index-1].data.unk_32=change.rateAfter;
        result.territories.push_back(change);
    }
    if (!save::validate(d,error)) return false;
    destination=std::move(d); report=std::move(result); error={}; return true;
} catch (const std::bad_alloc&) { error={save::ErrorCode::Limit,0,"Population growth allocation failed"}; return false; }
  catch (const std::exception& ex) { return fail(error,ex.what()); }
} // namespace dl2::simulation
