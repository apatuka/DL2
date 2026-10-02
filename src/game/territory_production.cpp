#include "game/territory_production.h"
#include <algorithm>
#include <bit>
#include <cstring>
#include <memory>
#include <new>
#include <stdexcept>
#include <unordered_set>

namespace dl2::simulation {
namespace {
bool fail(save::Error& e,const char* why) { e={save::ErrorCode::InvalidState,0,std::string("Territory production: ")+why}; return false; }
int32_t add(int32_t a,int32_t b) { return std::bit_cast<int32_t>(uint32_t(a)+uint32_t(b)); }
int32_t sub(int32_t a,int32_t b) { return std::bit_cast<int32_t>(uint32_t(a)-uint32_t(b)); }
int32_t mul(int32_t a,int32_t b) { return std::bit_cast<int32_t>(uint32_t(a)*uint32_t(b)); }
int16_t low16(int32_t value) { return std::bit_cast<int16_t>(uint16_t(uint32_t(value))); }
bool valid(const save::Document& d,ProductionPass pass,save::Error& e) {
    if (!save::validate(d,e)) return false;
    if (d.header.isMap) return fail(e,"requires a saved game");
    if (pass!=ProductionPass::Primary && pass!=ProductionPass::Refinement) return fail(e,"pass must be1 or2");
    return true;
}
// orig: FUN_0046b074/FUN_0046b0e4. Only completed Built housing exact types
// contribute. Stored race is a SIGNED byte used as a physical row24 address.
int32_t maxPopulation(const save::Document& d,uint32_t territory) {
    const auto& t=d.territories[territory-1].data;
    int32_t land=0,capacity=0; bool platform=false;
    for (const auto& site:t.sites) {
        if ((site.terrainFlags&0xffu)<5) ++land;
        const auto* b=d.buildingById(site.building.raw);
        if (!b) continue;
        if (b->category==20) platform=true;
        if (!(b->flags&2) || b->turnsLeft) continue;
        switch (b->type) { case 1:capacity+=500;break; case 2:capacity+=1000;break;
            case 3:case 39:capacity+=1500;break; default:break; }
    }
    land=t.terrain==0 && platform?2000:((land*139+50)/100)*100;
    const int word=24*kMaxPlayers+d.players[size_t(t.owner)].race;
    int16_t racial; std::memcpy(&racial,reinterpret_cast<const uint8_t*>(&d.raceStats)+size_t(word)*2,2);
    return std::min(land,mul(capacity,racial)/100);
}
Army* army(save::Document& d,uint32_t id) { for (auto& a:d.armies) if (a.id==id) return &a; return nullptr; }
// orig: FUN_0044f2fc (TrainMilitia) and FUN_00447a40 (veterancy level).
// Mission+25==14, NOT class14. The own list and then maritime same-owner
// adjacent lists are visited in raw list/bit order; self-adjacency repeats work.
bool train(save::Document& d,uint32_t territory,int32_t amount,std::vector<MilitiaTrainingChange>& out,save::Error& e) {
    const auto visit=[&](uint32_t index) {
        std::unordered_set<uint32_t> seen;
        uint32_t id=d.territories[index-1].data.armies.raw;
        while (id) {
            auto* a=army(d,id);
            if (!a || !seen.insert(id).second) return fail(e,"militia list is unresolved or cyclic");
            if (a->unk_25==14) {
                MilitiaTrainingChange change{id,index,a->experience,0,a->unk_2a,0};
                a->experience=std::min<int16_t>(low16(add(a->experience,low16(amount))),100);
                a->unk_2a=a->experience<100?0:(a->experience<401?1:2);
                change.after=a->experience; change.levelAfter=a->unk_2a; out.push_back(change);
            }
            id=a->next.raw;
        }
        return true;
    };
    if (!visit(territory)) return false;
    const auto& t=d.territories[territory-1].data;
    for (uint32_t index=0;index<kMaxTerritories;++index) if (t.adjacency[index/16]&(1u<<(index%16))) {
        if (!index || index>d.territories.size()) return fail(e,"militia adjacency reads an absent native territory slot");
        const auto& neighbor=d.territories[index-1].data;
        if (neighbor.terrain==0 && neighbor.owner==t.owner && !visit(index)) return false;
    }
    return true;
}
template<class Report> ConstructionOrderContext continued(const ConstructionOrderContext& original,const Report& result) {
    auto next=original; next.log=result.logAfter; next.ai=result.aiAfter; next.ai.rng=result.rngAfter;
    next.events.rngBeforeEvents=result.rngAfter; next.events.citiesBeforeLoad=result.citiesAfter;
    next.payment.collection=result.collectionAfter; return next;
}
template<class Effects> void absorb(TerritoryProductionReport& result,const Effects& effects) {
    result.logAfter=effects.logAfter; result.aiAfter=effects.aiAfter; result.rngAfter=effects.rngAfter;
    result.collectionAfter=effects.collectionAfter;
    result.events.insert(result.events.end(),effects.events.begin(),effects.events.end());
}
template<class Report> bool initialize(const TerritoryProductionContext& context,Report& report,save::Error& e) {
    SessionRng rng; if (!rng.restore(context.effects.events.rngBeforeEvents,e)) return false;
    report.logAfter=context.effects.log; report.aiAfter=context.effects.ai;
    report.rngAfter=rng.snapshot(); report.aiAfter.rng=report.rngAfter;
    report.collectionAfter=context.effects.payment.collection; report.citiesAfter=context.effects.events.citiesBeforeLoad;
    return true;
}
}

// orig: FUN_0044f3f0 (ProcessTerritoryProduction), apply=1.
bool processTerritoryProduction(const save::Document& source,uint32_t territory,ProductionPass pass,
    const TerritoryProductionContext& context,save::Document& destination,TerritoryProductionReport& report,save::Error& error) try {
    if (!valid(source,pass,error)) return false;
    const auto* input=source.territoryByIndex(territory);
    if (!input || input->data.owner<0 || input->data.owner>=kMaxPlayers) return fail(error,"requires an owned territory");
    const int owner=input->data.owner;
    auto candidate=std::make_unique<save::Document>(source); auto& d=*candidate;
    TerritoryProductionReport result; result.territory=territory; result.pass=pass;
    if (!initialize(context,result,error)) return false;
    const BuildingProgressContext workContext{context.effects.log,context.effects.events,context.effects.ai,context.effects.aiSession};
    if (!detail::accumulateBuildingProduction(d,territory,pass,workContext,d,result.work,result.totals,error)) return false;
    result.logAfter=result.work.logAfter; result.aiAfter=result.work.aiAfter; result.rngAfter=result.work.rngAfter;
    result.citiesAfter=result.work.citiesAfter; result.events=result.work.events;
    // Original local_b8 six-DWORD template at004c5ee8 is all zero. Queue0 is
    // accumulated but never passed to ProduceUnits. Finance sees pre-gain stock.
    for (int queue=1;queue<6;++queue) if (result.totals.queues[size_t(queue)]!=0) {
        auto next=context; next.effects=continued(context.effects,result);
        UnitManufacturingReport manufactured;
        if (!produceUnits(d,{territory,queue,result.totals.queues[size_t(queue)]},next,d,manufactured,error)) return false;
        absorb(result,manufactured);
        result.queueStructureChanged=result.queueStructureChanged || manufactured.queueStructureChanged;
        result.createdIds.insert(result.createdIds.end(),manufactured.createdIds.begin(),manufactured.createdIds.end());
        result.manufacturing.push_back(std::move(manufactured));
    }
    d.players[size_t(owner)].credits=add(d.players[size_t(owner)].credits,result.totals.credits);
    auto& beforeTraining=d.territories[territory-1].data;
    result.populationBefore=beforeTraining.population;
    beforeTraining.population=low16(add(beforeTraining.population,low16(result.totals.population)));
    result.populationLimit=maxPopulation(d,territory);
    beforeTraining.population=low16(std::min(int32_t(beforeTraining.population),result.populationLimit));
    result.populationAfter=beforeTraining.population;
    if (!train(d,territory,result.totals.training,result.training,error)) return false;
    auto& t=d.territories[territory-1].data;
    t.colonyFlag=uint16_t(add(t.colonyFlag,low16(result.totals.healing)));
    d.players[size_t(owner)].lastIncome=low16(add(d.players[size_t(owner)].lastIncome,low16(result.totals.research)));
    for (int material=1;material<11;++material) t.materials[material]=add(t.materials[material],low16(result.totals.materials[size_t(material)]));
    if (pass==ProductionPass::Refinement) {
        // Imports occur in this order BEFORE either conversion. The native
        // caller aliases remaining/cost outputs; neither return value is read.
        for (const auto [material,wanted]:{std::pair{4,result.totals.steel},std::pair{6,result.totals.electronics}}) {
            const int32_t stock=d.territories[territory-1].data.materials[material];
            if (stock<wanted) {
                EconomicLogisticsReport collected;
                if (!collectMaterial(d,{territory,owner,material,sub(wanted,stock),true},continued(context.effects,result),d,collected,error)) return false;
                absorb(result,collected); result.refinements.push_back(std::move(collected));
            }
        }
        auto& stocks=d.territories[territory-1].data.materials;
        result.steelConverted=low16(std::min(result.totals.steel,stocks[4]));
        result.electronicsConverted=low16(std::min(result.totals.electronics,stocks[6]));
        stocks[4]=sub(stocks[4],result.steelConverted); stocks[5]=add(stocks[5],result.steelConverted);
        stocks[6]=sub(stocks[6],result.electronicsConverted); stocks[7]=add(stocks[7],result.electronicsConverted);
    }
    if (pass==ProductionPass::Primary) {
        auto& after=d.territories[territory-1].data;
        after.taxAdjust=low16(result.totals.credits); after.unk_2c=low16(result.totals.culture); after.tradeIncome=low16(result.totals.research);
    }
    if (!save::validate(d,error)) return false;
    destination=std::move(d); report=std::move(result); error={}; return true;
} catch (const std::bad_alloc&) { error={save::ErrorCode::Limit,0,"Territory production allocation failed"}; return false; }
  catch (const std::length_error&) { error={save::ErrorCode::Limit,0,"Territory production exceeds container limits"}; return false; }

// orig: FUN_0044fcd4 (all owned territories, ascending index).
bool processWorldProduction(const save::Document& source,ProductionPass pass,const TerritoryProductionContext& context,
    save::Document& destination,WorldProductionReport& report,save::Error& error) try {
    if (!valid(source,pass,error)) return false;
    auto candidate=std::make_unique<save::Document>(source); auto& d=*candidate;
    WorldProductionReport result; result.pass=pass;
    if (!initialize(context,result,error)) return false;
    for (uint32_t territory=1;territory<=d.territories.size();++territory) {
        if (d.territories[territory-1].data.owner==-1) continue;
        auto next=context; next.effects=continued(context.effects,result);
        TerritoryProductionReport processed;
        if (!processTerritoryProduction(d,territory,pass,next,d,processed,error)) return false;
        result.logAfter=processed.logAfter; result.aiAfter=processed.aiAfter; result.rngAfter=processed.rngAfter;
        result.collectionAfter=processed.collectionAfter; result.citiesAfter=processed.citiesAfter;
        result.queueStructureChanged=result.queueStructureChanged || processed.queueStructureChanged;
        result.createdIds.insert(result.createdIds.end(),processed.createdIds.begin(),processed.createdIds.end());
        result.events.insert(result.events.end(),processed.events.begin(),processed.events.end());
        result.territories.push_back(std::move(processed));
    }
    destination=std::move(d); report=std::move(result); error={}; return true;
} catch (const std::bad_alloc&) { error={save::ErrorCode::Limit,0,"World production allocation failed"}; return false; }
  catch (const std::length_error&) { error={save::ErrorCode::Limit,0,"World production exceeds container limits"}; return false; }
} // namespace dl2::simulation
