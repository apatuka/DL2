#include "game/colony_unrest.h"
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
bool fail(save::Error& error,const char* text,save::ErrorCode code=save::ErrorCode::InvalidState) {
    error={code,0,text}; return false;
}
int32_t add(int32_t a,int32_t b) { return std::bit_cast<int32_t>(uint32_t(a)+uint32_t(b)); }
int32_t sub(int32_t a,int32_t b) { return std::bit_cast<int32_t>(uint32_t(a)-uint32_t(b)); }
int32_t mul(int32_t a,int32_t b) { return std::bit_cast<int32_t>(uint32_t(a)*uint32_t(b)); }
int16_t low16(int32_t value) { return std::bit_cast<int16_t>(uint16_t(uint32_t(value))); }
bool valid(const save::Document& source,save::Error& error) {
    if (!save::validate(source,error)) return false;
    return !source.header.isMap || fail(error,"Colony unrest requires a saved game");
}
template<class Report> bool initialize(const ConstructionOrderContext& context,Report& report,save::Error& error) {
    if (context.ai.rng!=context.events.rngBeforeEvents)
        return fail(error,"Colony unrest requires a shared initial AI/event RNG");
    SessionRng rng; if (!rng.restore(context.events.rngBeforeEvents,error)) return false;
    report.logAfter=context.log; report.aiAfter=context.ai; report.rngAfter=rng.snapshot();
    report.aiAfter.rng=report.rngAfter; return true;
}
template<class Report> ConstructionOrderContext continued(const ConstructionOrderContext& context,const Report& result) {
    auto next=context; next.log=result.logAfter; next.ai=result.aiAfter; next.ai.rng=result.rngAfter;
    next.events.rngBeforeEvents=result.rngAfter; return next;
}
bool draw(ColonyUnrestReport& report,int32_t bound,const char* tag,uint32_t& value,save::Error& error) {
    SessionRng rng; RngEvent event;
    if (!rng.restore(report.rngAfter,error) || !rng.apply({RngOperation::TaggedRange,bound,0,tag},event,error)) return false;
    value=event.value; report.draws.push_back(std::move(event)); report.rngAfter=rng.snapshot();
    report.aiAfter.rng=report.rngAfter; return true;
}
bool name(const save::Document& d,uint32_t territory,std::string& result,save::Error& error) {
    const auto& t=d.territories[territory-1].data;
    const auto* end=static_cast<const char*>(std::memchr(t.name,0,sizeof(t.name)));
    if (!end) return fail(error,"Unrest event territory name lacks a bounded terminator");
    result.assign(t.name,size_t(end-t.name)); return true;
}
bool raceName(const save::Document& d,int owner,std::string& result,save::Error& error) {
    if (owner<0 || owner>=kMaxPlayers || d.players[size_t(owner)].race<0 || d.players[size_t(owner)].race>=kMaxPlayers)
        return fail(error,"Unrest event race lies outside the canonical name table");
    result=data::kRaceNames[size_t(d.players[size_t(owner)].race)]; return true;
}
// orig:00423690/004237d0. Events83..89 use verified default AI handlers,
// but call the real owned dispatcher and preserve the shared stream/order.
bool emit(save::Document& d,int recipient,LocalEventRequest request,const ConstructionOrderContext& context,
          ColonyUnrestReport& report,save::Error& error) {
    if (recipient<0 || recipient>=kMaxPlayers) return fail(error,"Unrest event owner outside0..6");
    ConstructionOrderEvent event; event.type=request.type; event.recipient=recipient;
    if (recipient==d.options.localPlayer) {
        event.local=true; auto input=context.events; input.rngBeforeEvents=report.rngAfter;
        if (!logLocalEvent(d,report.logAfter,input,request,report.logAfter,event.localReport,error)) return false;
        report.rngAfter=event.localReport.rngAfter;
    } else if (std::bit_cast<int8_t>(d.players[size_t(recipient)].type)>=3) {
        if (!context.aiSession || context.ai.rng!=context.events.rngBeforeEvents)
            return fail(error,"Unrest event requires owned AI bindings and a shared initial RNG");
        const auto payload=request.payload.value_or(EventPayload{});
        event.aiDispatched=true; report.aiAfter.rng=report.rngAfter;
        if (!context.aiSession->reactEvent(d,{recipient,request.type,payload.player,payload.param},report.aiAfter,d,event.aiReport,error)) return false;
        report.aiAfter=event.aiReport.contextAfter; report.rngAfter=report.aiAfter.rng;
    }
    report.aiAfter.rng=report.rngAfter; report.events.push_back(std::move(event)); return true;
}
Building* building(save::Document& d,uint32_t id) {
    for (auto& b:d.buildings) if (b.id==id) return &b;
    return nullptr;
}
bool riot(save::Document& d,uint32_t territory,int16_t deaths,const ConstructionOrderContext& context,
          ColonyUnrestReport& report,save::Error& error) {
    const int owner=d.territories[territory-1].data.owner;
    if (owner<0 || owner>=kMaxPlayers) return fail(error,"DoRiot requires an owner in0..6");
    auto& initial=d.territories[territory-1].data;
    report.riotDeaths=deaths; initial.population=low16(sub(initial.population,deaths));
    for (int site=0;site<kNumSites;++site) {
        const uint32_t id=d.territories[territory-1].data.sites[site].building.raw;
        if (!id) continue;
        uint32_t roll;
        if (!draw(report,100,"DoRiot",roll,error)) return false;
        auto* b=building(d,id); if (!b) return fail(error,"DoRiot site references a missing building");
        //100U-signed morale, then UNSIGNED shift. Morale>100 wraps rather
        // than clamping. Type38 still consumed its original draw above.
        const uint32_t threshold=(100u-uint32_t(int32_t(d.territories[territory-1].data.morale)))>>2;
        if (roll>threshold || b->type==38) continue;
        if (b->type>=data::kNumBuildingTypes) return fail(error,"DoRiot type outside canonical building table");
        const int32_t labor=std::bit_cast<int16_t>(data::kBuildingTypes[b->type].buildLabor);
        //0044de9c's CityCenter scaling affects money/materials, NOT labor.
        // Only outputword0 is observed here; no artificial requirements gate.
        const int16_t before=b->turnsLeft;
        b->turnsLeft=low16(std::min(labor,add(before,labor/2)));
        report.damage.push_back({id,site,b->type,before,b->turnsLeft});
        const int type=b->type; std::string territoryName;
        if (!name(d,territory,territoryName,error)) return false;
        if (!emit(d,owner,{83,{territoryName,std::string(data::kBuildingTypes[type].name)},{}},context,report,error)) return false;
    }
    return true;
}
bool pact(const save::Document& d,int a,int b,uint32_t mask) {
    if (!d.options.allowAlliances || a<0 || b<0 || a>=d.options.numPlayers || b>=d.options.numPlayers) return false;
    const auto flags=d.players[size_t(a)].relations[size_t(b)];
    return mask==((flags&0x10u)?(mask&0x1eu):(flags&mask));
}
//0046c254 ->00446b3c ->00446440(mode3). Exactly the same passability as the
// load detector's air-mode leaf, now range500 and no detector threshold writes.
bool migrationDestination(save::Document& d,uint32_t source,uint32_t& destination,save::Error& error) {
    const int owner=d.territories[source-1].data.owner; const uint32_t flag=0x2000u<<owner;
    std::vector<Territory> regions(d.territories.size()+1); std::vector<bool> city(regions.size());
    for (size_t i=1;i<regions.size();++i) {
        regions[i]=d.territories[i-1].data;
        if (regions[i].owner<-1 || regions[i].owner>=kMaxPlayers) return fail(error,"Migration search has invalid territory owner");
        for (size_t next=regions.size();next<kMaxTerritories;++next)
            if (regions[i].adjacency[next/16]&(1u<<(next%16))) return fail(error,"Migration adjacency reaches an absent native pool slot");
        for (const auto& site:regions[i].sites) {
            const auto* b=d.buildingById(site.building.raw);
            if (b && b->category==9 && b->turnsLeft==0) city[i]=true;
        }
    }
    const auto distance=[&](size_t i) {
        int16_t value; std::memcpy(&value,reinterpret_cast<const uint8_t*>(&regions[i])+0xa70+size_t(owner)*2,2); return value;
    };
    const auto setDistance=[&](size_t i,int16_t value) {
        std::memcpy(reinterpret_cast<uint8_t*>(&regions[i])+0xa70+size_t(owner)*2,&value,2);
    };
    for (size_t i=0;i<regions.size();++i) { regions[i].flags&=~flag; setDistance(i,1000); }
    size_t calls=0;
    const auto scan=[&](auto&& self,size_t index,int cost)->bool {
        if (++calls>1000000) return fail(error,"Migration traversal exceeds finite safety bound",save::ErrorCode::Limit);
        regions[index].flags|=flag; setDistance(index,int16_t(cost));
        if (cost>=500) return true;
        for (size_t next=0;next<regions.size();++next) {
            if (!(regions[index].adjacency[next/16]&(1u<<(next%16)))) continue;
            const auto& target=regions[next];
            if (target.flags&0x100u) continue;
            if (target.owner!=owner && pact(d,owner,target.owner,1)) continue;
            if (target.owner!=owner && pact(d,owner,target.owner,2) && !pact(d,owner,target.owner,0x10) && city[next]) continue;
            if (cost+1<distance(next) && !self(self,next,cost+1)) return false;
        }
        return true;
    };
    if (!scan(scan,source,0)) return false;
    int16_t closest=1000; destination=0;
    for (size_t i=1;i<regions.size();++i) {
        const auto& t=regions[i];
        if (t.owner!=owner && t.owner!=-1 && t.numTiles && !(t.flags&0x100u) && (t.flags&flag) && distance(i)<closest) {
            closest=distance(i); destination=uint32_t(i);
        }
        d.territories[i-1].data=t;
    }
    return true;
}
bool row27(const save::Document& d,int owner,int32_t& result,save::Error& error) {
    const int word=27*kMaxPlayers+d.players[size_t(owner)].race;
    if (word<0 || word>=int(sizeof(RaceStats)/sizeof(int16_t))) return fail(error,"Unrest racial threshold lies outside saved RaceStats");
    int16_t value; std::memcpy(&value,reinterpret_cast<const uint8_t*>(&d.raceStats)+size_t(word)*2,2);
    result=value; return true;
}
template<class Operation> bool guarded(Operation&& operation,save::Error& error) {
    try { return operation(); }
    catch (const std::bad_alloc&) { return fail(error,"Colony unrest allocation failed",save::ErrorCode::Limit); }
    catch (const std::length_error&) { return fail(error,"Colony unrest container limit exceeded",save::ErrorCode::Limit); }
    catch (const std::exception& e) { error={save::ErrorCode::InvalidState,0,e.what()}; return false; }
}
}

// orig: DoRiot0046c310.
bool doColonyRiot(const save::Document& source,uint32_t territory,int16_t deaths,const ConstructionOrderContext& context,
    save::Document& destination,ColonyUnrestReport& report,save::Error& error) {
    return guarded([&] {
        if (!valid(source,error)) return false;
        if (!source.territoryByIndex(territory)) return fail(error,"DoRiot requires a saved territory1..N");
        ColonyUnrestReport result; if (!initialize(context,result,error)) return false;
        result.territory=territory; result.outcome=ColonyUnrestOutcome::DirectRiot;
        result.populationBefore=source.territories[territory-1].data.population;
        auto candidate=std::make_unique<save::Document>(source);
        if (!riot(*candidate,territory,deaths,context,result,error)) return false;
        result.populationAfter=candidate->territories[territory-1].data.population;
        if (!save::validate(*candidate,error)) return false;
        destination=std::move(*candidate); report=std::move(result); error={}; return true;
    },error);
}

// orig: FUN_0046c49c (colony migration/riots).
bool processColonyUnrest(const save::Document& source,uint32_t territory,const ConstructionOrderContext& context,
    save::Document& destination,ColonyUnrestReport& report,save::Error& error) {
    return guarded([&] {
        if (!valid(source,error)) return false;
        const auto* original=source.territoryByIndex(territory);
        if (!original) return fail(error,"Unrest requires territory1..N");
        const int owner=original->data.owner;
        ColonyUnrestReport result; result.territory=territory;
        if (!initialize(context,result,error)) return false;
        result.populationBefore=result.populationAfter=original->data.population;
        auto candidate=std::make_unique<save::Document>(source); auto& d=*candidate;
        if (original->data.population!=0 && owner!=-1) {
            if (owner<0 || owner>=kMaxPlayers) return fail(error,"Unrest territory owner outside0..6");
            if (!territoryLaborAvailability(d,territory,result.labor,error)) return false;
            uint32_t roll;
            if (!draw(result,100,"Revolt",roll,error) || !colonyRevoltStrength(d,territory,result.revoltStrength,error)) return false;
            result.outcome=ColonyUnrestOutcome::Stable;
            if (roll<uint32_t(result.revoltStrength)) {
                result.outcome=ColonyUnrestOutcome::MigrationAttempt;
                if (!draw(result,std::max(mul(result.labor.unavailable,100),100),"Revolt2",roll,error)) return false;
                result.migrants=std::min(add(std::bit_cast<int32_t>(roll),1),sub(d.territories[territory-1].data.population,50));
                // The original always searches even if migrants<=0.
                if (!migrationDestination(d,territory,result.destination,error)) return false;
                if (result.migrants>0 && result.destination) {
                    const int receiver=d.territories[result.destination-1].data.owner;
                    // Assembly0046c5dc/0046c60c and PE004fcf06/004fcf18:
                    // do NOT "repair" swapped native event87/86 varargs.
                    if (receiver==d.options.localPlayer)
                        return fail(error,"Original unrest migration to local player has undefined event87/86 format arguments (0046c5dc/0046c60c)");
                    StealableTechnologyReport stolen;
                    if (!chooseStealableTechnology(d,receiver,owner,result.rngAfter,stolen,error)) return false;
                    result.technology=stolen.technology; result.draws.push_back(stolen.draw);
                    result.rngAfter=stolen.rngAfter; result.aiAfter.rng=result.rngAfter;
                    result.destinationBefore=d.territories[result.destination-1].data.population;
                    d.territories[territory-1].data.population=low16(sub(d.territories[territory-1].data.population,low16(result.migrants)));
                    d.territories[result.destination-1].data.population=low16(add(result.destinationBefore,low16(result.migrants)));
                    result.destinationAfter=d.territories[result.destination-1].data.population;
                    std::string fromName,toName,fromRace,toRace;
                    if (!name(d,territory,fromName,error) || !name(d,result.destination,toName,error) ||
                        !raceName(d,owner,fromRace,error) || !raceName(d,receiver,toRace,error)) return false;
                    if (!emit(d,owner,{85,{result.migrants,fromName,toRace},{}},context,result,error) ||
                        !emit(d,receiver,{87,{result.migrants,fromRace,toName},{}},context,result,error)) return false;
                    if (result.technology && !emit(d,receiver,{86,{fromRace,std::string(data::kTechs[result.technology].name)},
                        EventPayload{result.technology,0}},context,result,error)) return false;
                    if (!acquireTechnology(d,receiver,result.technology,continued(context,result),d,result.acquisition,error)) return false;
                    result.logAfter=result.acquisition.logAfter; result.aiAfter=result.acquisition.aiAfter; result.rngAfter=result.acquisition.rngAfter;
                    result.events.insert(result.events.end(),result.acquisition.events.begin(),result.acquisition.events.end());
                    result.outcome=ColonyUnrestOutcome::Migrated;
                }
            } else {
                if (!colonyMoraleMetrics(d,territory,result.morale,error)) return false;
                if (result.morale.total<=result.morale.baseline) {
                    int32_t threshold;
                    if (!row27(d,owner,threshold,error)) return false;
                    const int32_t morale=d.territories[territory-1].data.morale;
                    std::string territoryName;
                    if (morale<threshold) {
                        if (!draw(result,100,"Revolt3",roll,error) || !name(d,territory,territoryName,error)) return false;
                        if (roll<uint32_t(sub(threshold,morale))) {
                            result.outcome=ColonyUnrestOutcome::Riot;
                            const int32_t losses=mul(result.labor.unavailable,50);
                            if (!emit(d,owner,{84,{territoryName,losses},{}},context,result,error) ||
                                !riot(d,territory,low16(losses),context,result,error)) return false;
                        } else {
                            result.outcome=ColonyUnrestOutcome::Agitated;
                            if (!emit(d,owner,{89,{territoryName},{}},context,result,error)) return false;
                        }
                    } else if (morale<mul(threshold,2)) {
                        result.outcome=ColonyUnrestOutcome::Unhappy;
                        if (!name(d,territory,territoryName,error) || !emit(d,owner,{88,{territoryName},{}},context,result,error)) return false;
                    }
                }
            }
        }
        result.populationAfter=d.territories[territory-1].data.population;
        if (!save::validate(d,error)) return false;
        destination=std::move(d); report=std::move(result); error={}; return true;
    },error);
}

bool processWorldUnrest(const save::Document& source,const ConstructionOrderContext& context,
    save::Document& destination,WorldUnrestReport& report,save::Error& error) {
    return guarded([&] {
        if (!valid(source,error)) return false;
        WorldUnrestReport result; if (!initialize(context,result,error)) return false;
        auto candidate=std::make_unique<save::Document>(source); auto& d=*candidate;
        for (uint32_t i=1;i<=d.territories.size();++i) {
            ColonyUnrestReport step;
            if (!processColonyUnrest(d,i,continued(context,result),d,step,error)) return false;
            result.logAfter=step.logAfter; result.aiAfter=step.aiAfter; result.rngAfter=step.rngAfter;
            result.events.insert(result.events.end(),step.events.begin(),step.events.end()); result.territories.push_back(std::move(step));
        }
        destination=std::move(d); report=std::move(result); error={}; return true;
    },error);
}
} // namespace dl2::simulation
