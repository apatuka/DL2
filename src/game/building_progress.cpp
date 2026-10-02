#include "game/building_progress.h"
#include "game/data_tables.h"
#include "game/labor_balance.h"
#include "game/production_plan.h"
#include <algorithm>
#include <bit>
#include <cstring>
#include <limits>
#include <memory>
#include <new>
#include <stdexcept>
#include <string>
#include <unordered_set>

namespace dl2::simulation {
namespace {
bool fail(save::Error& e,const std::string& why) { e={save::ErrorCode::InvalidState,0,"Building work: "+why}; return false; }
int32_t add(int32_t a,int32_t b) { return std::bit_cast<int32_t>(uint32_t(a)+uint32_t(b)); }
int32_t sub(int32_t a,int32_t b) { return std::bit_cast<int32_t>(uint32_t(a)-uint32_t(b)); }
int32_t mul(int32_t a,int32_t b) { return std::bit_cast<int32_t>(uint32_t(a)*uint32_t(b)); }
int16_t short16(int32_t v) { return std::bit_cast<int16_t>(uint16_t(uint32_t(v))); }
Building& building(save::Document& d,uint32_t id) {
    for (auto& b:d.buildings) if (b.id==id) return b;
    throw std::logic_error("work record unexpectedly disappeared");
}
int32_t labor(const Building& b) { int32_t n=0; for (int32_t v:b.labor) n=add(n,v); return n; }
bool pact(const save::Document& d,int a,int b) {
    if (!d.options.allowAlliances || a<0 || b<0 || a>=d.options.numPlayers || b>=d.options.numPlayers) return false;
    return (d.players[size_t(a)].relations[size_t(b)]&0x10u)!=0;
}
bool name(const Territory& t,std::string& out,save::Error& e) {
    const auto* end=static_cast<const char*>(std::memchr(t.name,0,sizeof(t.name)));
    if (!end) return fail(e,"event territory name lacks a bounded terminator");
    out.assign(t.name,size_t(end-t.name)); return true;
}
bool emit(save::Document& d,int recipient,LocalEventRequest request,const BuildingProgressContext& ctx,
          BuildingProgressReport& result,save::Error& error) {
    if (recipient<0 || recipient>=kMaxPlayers) return fail(error,"event recipient outside0..6");
    ConstructionOrderEvent event; event.type=request.type; event.recipient=recipient;
    if (recipient==d.options.localPlayer) {
        event.local=true; auto context=ctx.events; context.rngBeforeEvents=result.rngAfter; context.citiesBeforeLoad=result.citiesAfter;
        if (!logLocalEvent(d,result.logAfter,context,request,result.logAfter,event.localReport,error)) return false;
        result.rngAfter=event.localReport.rngAfter;
    } else if (std::bit_cast<int8_t>(d.players[size_t(recipient)].type)>=3) {
        if (!ctx.aiSession || ctx.ai.rng!=ctx.events.rngBeforeEvents) return fail(error,"event requires owned AI and a single shared initial RNG");
        event.aiDispatched=true; result.aiAfter.rng=result.rngAfter;
        const auto payload=request.payload.value_or(EventPayload{});
        if (!ctx.aiSession->reactEvent(d,{recipient,request.type,payload.player,payload.param},result.aiAfter,d,event.aiReport,error)) return false;
        result.aiAfter=event.aiReport.contextAfter; result.rngAfter=result.aiAfter.rng;
    }
    result.aiAfter.rng=result.rngAfter; result.events.push_back(std::move(event)); return true;
}

// CountShrines00486964, invoked here ONLY under victory0 by CityCenter finish.
// Its notices77/78 are disabled in that mode; no unrelated continents/roads.
bool countCitiesAndShrines(save::Document& d,BuildingProgressReport& result,save::Error& error) {
    LoadDerivedReport counts;
    for (auto& record:d.territories) {
        auto& t=record.data;
        if (t.owner<-1 || t.owner>=kMaxPlayers) return fail(error,"CountShrines owner outside-1..6");
        if (!t.numTiles || (t.flags&0x100u)) continue;
        bool city=false;
        for (const auto& site:t.sites) {
            const auto* b=d.buildingById(site.building.raw);
            if (b && b->category==9 && !b->turnsLeft) city=true;
        }
        if (t.owner>=0) { ++counts.territories[size_t(t.owner)]; if (city) ++counts.cities[size_t(t.owner)]; }
        for (const auto& site:t.sites) {
            const auto* b=d.buildingById(site.building.raw);
            if (!b || b->category!=11) continue;
            ++counts.totalShrines;
            uint32_t known; std::memcpy(&known,t.unk_8b0,4);
            if (b->turnsLeft || t.owner<0 || !(known&(1u<<t.owner))) continue;
            for (int p=0;p<kMaxPlayers;++p)
                if (p!=t.owner && d.players[size_t(p)].type && pact(d,p,t.owner)) ++counts.shrines[size_t(p)];
            ++counts.shrines[size_t(t.owner)]; known=0xff; std::memcpy(t.unk_8b0,&known,4);
        }
    }
    counts.shrineCountsRebuilt=true; result.citiesAfter=counts.cities; result.counts=std::move(counts); result.cityCountsRebuilt=true; return true;
}

// TaskOutputs0044eb4c cached values. The existing query explicitly normalizes
// unused task0 output; that indeterminate value is never consumed by cases2/21.
bool cachedOutput(const save::Document& d,uint32_t id,std::array<int32_t,5>& output,save::Error& error) {
    return assignedBuildingOutputs(d,id,output,error);
}

// IsBuildTaskDifferent0044bb60; keep wrapped numerators and IDIV domains.
bool different(const save::Document& d,uint32_t id,int slot,bool& result,save::Error& error) {
    const auto& b=*d.buildingById(id); const int32_t n=b.labor[slot];
    int32_t first,second;
    if (!buildingTaskOutput(d,id,slot,n,first,error) || !buildingTaskOutput(d,id,slot,sub(n,1),second,error)) return false;
    int32_t remaining=b.turnsLeft;
    if (b.task[slot]!=2) { int32_t required; if (!queryBuildingUpgrade(d,id,required,error)) return false; remaining=sub(required,b.unk_16); }
    const auto turns=[&](int32_t output,int32_t& value) {
        value=0; if (!output) return true;
        const int32_t numerator=sub(add(remaining,output),1);
        if (numerator==std::numeric_limits<int32_t>::min() && output==-1) return fail(error,"IsBuildTaskDifferent signed division would trap");
        value=numerator/output; return true;
    };
    int32_t a,bTurns;
    if (!turns(first,a) || !turns(second,bTurns)) return false;
    result=a!=bTurns; return true;
}
std::string laborKey(const save::Document& d,uint32_t territory) {
    std::string key;
    for (const auto& site:d.territories[territory-1].data.sites) if (const auto* b=d.buildingById(site.building.raw)) {
        key.append(reinterpret_cast<const char*>(&b->id),sizeof(b->id));
        key.append(reinterpret_cast<const char*>(&b->flags),sizeof(b->flags));
        key.append(reinterpret_cast<const char*>(b->labor),sizeof(b->labor));
    }
    return key;
}
bool reduceLabor(save::Document& d,uint32_t id,int slot,bool upgrade,save::Error& error) {
    if (building(d,id).flags & (0x100u<<slot)) return true;
    std::unordered_set<std::string> seen;
    for (size_t steps=0;building(d,id).labor[slot]!=0;++steps) {
        if (steps>=1000000 || !seen.insert(laborKey(d,uint32_t(building(d,id).territory))).second)
            return fail(error,"original work-labor reduction does not converge within safety bound");
        bool differs;
        if (!different(d,id,slot,differs,error)) return false;
        if (differs) break;
        if (upgrade) {
            auto& b=building(d,id); b.labor[slot]=sub(b.labor[slot],1);
            const int32_t total=add(labor(b),1);
            if (!distributeBuildingLabor(d,id,total,d,error)) return false;
        } else {
            bool moved;
            if (!moveBuildingLaborToHousing(d,id,slot,d,moved,error)) return false;
            if (!moved) break;
        }
    }
    return true;
}

// Upgrade relocation0044f1e8 + one-cell GetSiteYield0044e9e4.
bool shrinkSite(save::Document& d,uint32_t id,save::Error& error) {
    auto& b=building(d,id); auto& t=d.territories[size_t(b.territory-1)].data;
    BuildingFootprint footprint;
    if (!buildingFootprint(b.type,b.site,footprint,error)) return false;
    if (!footprint.fits) return fail(error,"upgrade footprint extends outside site grid");
    const int anchor=b.site;
    for (uint8_t site:footprint.sites) t.sites[site].terrainFlags&=0xff;
    t.sites[size_t(anchor)].building.raw=0;
    int primary=0,secondary=0;
    if (b.category==1) { primary=12; secondary=13; }
    else if (b.category==2) { primary=3; secondary=4; }
    else if (b.category==3) primary=15;
    int bestSite=anchor; int32_t best=0;
    const auto score=[&](int index,int task,int32_t& value) {
        const auto coordinates=t.sites[index].unk_00;
        const int x=std::bit_cast<int8_t>(uint8_t(coordinates)),y=std::bit_cast<int8_t>(uint8_t(coordinates>>8));
        if (x<0 || x>=6 || y<0 || y>=6) return fail(error,"upgrade yield has unsafe saved site coordinates");
        const auto& cell=t.sites[y*6+x]; int resource=0,match=2;
        switch (task) { case 3:resource=3;match=4;break; case 4:resource=4;match=6;break;
            case 12:resource=1;match=1;break; case 13:resource=2;match=3;break; default:break; }
        int16_t richness; std::memcpy(&richness,&cell.unk_05[1+resource*2],2);
        value=mul(mul(d.options.fastProduction?200:100,2+(std::bit_cast<int8_t>(cell.value)==match?1:0)),richness)/20000;
        return true;
    };
    if (primary) for (int row=0;row<2;++row) for (int column=0;column<2;++column) {
        const int site=anchor+column-row*6; int32_t value,other=0;
        if (!score(site,primary,value) || (secondary && !score(site,secondary,other))) return false;
        value=add(value,other); if (best<value) { best=value; bestSite=site; }
    }
    b.site=int8_t(bestSite); t.sites[bestSite].building.raw=id;
    auto& flags=t.sites[bestSite].terrainFlags;
    flags=(flags&0xf00u)==0x100u?uint16_t((flags&0xffu)|0x3200u):uint16_t(flags|0x3000u);
    return true;
}
} // namespace

bool progressBuildingWork(const save::Document& source,uint32_t territory,const BuildingProgressContext& context,
                         save::Document& destination,BuildingProgressReport& report,save::Error& error) try {
    if (!save::validate(source,error)) return false;
    const auto* original=source.territoryByIndex(territory);
    if (source.header.isMap || !original || original->data.owner<0 || original->data.owner>=kMaxPlayers)
        return fail(error,"requires an owned saved-game territory");
    SessionRng validatedRng;
    if (!validatedRng.restore(context.events.rngBeforeEvents,error)) return false;
    auto candidate=std::make_unique<save::Document>(source); auto& d=*candidate;
    BuildingProgressReport result; result.territory=territory;
    result.logAfter=context.log; result.aiAfter=context.ai; result.rngAfter=context.events.rngBeforeEvents;
    result.aiAfter.rng=result.rngAfter; result.citiesAfter=context.events.citiesBeforeLoad;
    if (!balanceTerritoryLabor(d,territory,d,error)) return false;
    result.initialLaborBalanced=true;
    const int owner=original->data.owner;
    for (int site=0;site<kNumSites;++site) {
        const uint32_t id=d.territories[territory-1].data.sites[site].building.raw;
        if (!id) continue;
        const auto& b=building(d,id);
        if (!b.type || (b.flags&6)!=6) continue;
        if (std::none_of(std::begin(b.task),std::end(b.task),[](uint8_t task){return task==2 || task==21;})) continue;
        const int32_t total=labor(b); std::array<int32_t,5> outputs{};
        if (!cachedOutput(d,id,outputs,error)) return false;
        for (int slot=0;slot<5;++slot) {
            auto& current=building(d,id); const uint8_t task=current.task[slot];
            if (task!=2 && task!=21) continue;
            int32_t required=-1;
            if (task==21 && (!queryBuildingUpgrade(d,id,required,error) || required==-1)) {
                if (error.code!=save::ErrorCode::None) return false;
                continue;
            }
            BuildingWorkChange change{id,slot,task,current.type,current.type,current.site,current.site,outputs[size_t(slot)],
                current.turnsLeft,current.turnsLeft,current.unk_16,current.unk_16};
            if (task==2) {
                current.turnsLeft=std::max<int16_t>(short16(sub(current.turnsLeft,short16(outputs[size_t(slot)]))),0);
                if (current.turnsLeft==0) {
                    change.completed=true;
                    if (!refreshBuildingLabor(d,id,d,error)) return false;
                    if (std::bit_cast<int8_t>(d.players[size_t(owner)].type)<3) {
                        if (!distributeBuildingLabor(d,id,total,d,error)) return false;
                    } else {
                        auto& finished=building(d,id); std::fill_n(finished.labor,5,0);
                        finished.labor[finished.task[1]?1:0]=total;
                    }
                    std::string territoryName;
                    if (!name(d.territories[territory-1].data,territoryName,error)) return false;
                    if (d.options.victory==0 && building(d,id).type==37) {
                        if (!countCitiesAndShrines(d,result,error)) return false;
                        LocalEventRequest request;
                        if (owner==d.options.localPlayer) { request.type=67; request.arguments={territoryName}; }
                        else {
                            const int race=d.players[size_t(owner)].race;
                            if (race<0 || race>=kMaxPlayers) return fail(error,"CityCenter event race outside name table");
                            request.type=uint16_t(pact(d,d.options.localPlayer,owner)?66:65);
                            request.arguments={std::string(data::kRaceNames[race])}; request.payload=EventPayload{owner,0};
                        }
                        if (!emit(d,d.options.localPlayer,std::move(request),context,result,error)) return false;
                    } else {
                        const auto value=building(d,id);
                        const uint16_t type=(value.flags&0x40)?63:62;
                        if (!emit(d,owner,{type,{std::string(data::kBuildingTypes[value.type].name),territoryName},{}},context,result,error)) return false;
                        if (!(value.flags&0x40)) {
                            building(d,id).flags|=0x40;
                            if (value.category==5 && !d.players[size_t(owner)].currentResearch)
                                if (!emit(d,owner,{55,{},{}},context,result,error)) return false;
                        }
                    }
                } else if (!reduceLabor(d,id,slot,false,error)) return false;
            } else {
                current.unk_16=short16(add(current.unk_16,short16(outputs[size_t(slot)])));
                if (required<=current.unk_16) {
                    change.upgraded=true;
                    const int oldType=current.type;
                    if (data::kBuildingTypes[oldType].size==2 && data::kBuildingTypes[oldType+1].size==1)
                        if (!shrinkSite(d,id,error)) return false;
                    std::string territoryName;
                    if (!name(d.territories[territory-1].data,territoryName,error)) return false;
                    if (!emit(d,owner,{75,{std::string(data::kBuildingTypes[oldType].name),territoryName,
                        std::string(data::kBuildingTypes[oldType+1].name)},{}},context,result,error)) return false;
                    auto& upgraded=building(d,id); ++upgraded.type; upgraded.unk_16=0; // Stored category/race are not recomputed.
                    if (!refreshBuildingLabor(d,id,d,error) || !balanceTerritoryLabor(d,territory,d,error)) return false;
                    int32_t next;
                    if (!queryBuildingUpgrade(d,id,next,error)) return false;
                    if (next==-1 && !distributeBuildingLabor(d,id,labor(building(d,id)),d,error)) return false;
                    if (!rebuildTerritorySiteRoads(d,territory,d,error)) return false;
                }
                // Original still trims after an upgrade, with the CURRENT task
                // (possibly0), and can loop forever; repeated states fail safely.
                if (!reduceLabor(d,id,slot,true,error)) return false;
            }
            const auto& after=building(d,id); change.typeAfter=after.type; change.siteAfter=after.site;
            change.workAfter=after.turnsLeft; change.upgradeAfter=after.unk_16;
            result.changes.push_back(change);
        }
    }
    if (!save::validate(d,error)) return false;
    destination=std::move(d); report=std::move(result); error={}; return true;
} catch (const std::bad_alloc&) { error={save::ErrorCode::Limit,0,"Building-work allocation failed"}; return false; }
  catch (const std::length_error&) { error={save::ErrorCode::Limit,0,"Building-work container bound exceeded"}; return false; }
  catch (const std::exception& e) { error={save::ErrorCode::InvalidState,0,e.what()}; return false; }
} // namespace dl2::simulation
