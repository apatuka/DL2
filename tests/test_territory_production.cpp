// Numeric/control-flow oracles from0044f3f0/0044fcd4, not live EXE replay.
#include "game/territory_production.h"
#include "game/data_tables.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include <algorithm>
#include <bit>
#include <cstring>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>
namespace {
using namespace dl2; using namespace dl2::simulation;
void require(bool value,const char* message) { if (!value) throw std::runtime_error(message); }
void ok(bool value,const save::Error& e) { if (!value) throw std::runtime_error(e.message); }
std::unique_ptr<save::Document> fixture() {
    auto d=std::make_unique<save::Document>();
    std::memcpy(d->header.text,save::kHeaderText,sizeof(save::kHeaderText)); d->header.version=kSaveVersion;
    d->options.numPlayers=2; d->options.localPlayer=0; d->options.turn=19; d->options.nextGlobalId=1000; d->options.victory=1;
    d->world.width=3; d->world.height=1; d->world.numTerritories=3; d->territories.resize(3); d->tiles.resize(3);
    for (size_t p=0;p<7;++p) {
        d->players[p].index=uint8_t(p); d->players[p].race=2; d->players[p].type=p?3:1; d->players[p].credits=100;
        d->ministerJobs[p].resize(1); d->ministerJobs[p][0].type=1;
        for (auto& row:d->raceStats.v) row[p]=100;
    }
    for (size_t i=0;i<3;++i) {
        auto& t=d->territories[i].data; t.index=uint16_t(i+1); t.owner=i?-1:0; t.terrain=1;
        t.population=1000; t.morale=100; t.knowledge=100; t.numTiles=1; t.tiles[0].raw=uint32_t(i);
        t.production[3]=31; t.consumption[4]=43; t.materials[0]=909;
        std::memcpy(t.name,"Alpha",6); d->tiles[i].x=uint8_t(i); d->tiles[i].territory=int16_t(i+1);
        for (int s=0;s<36;++s) { t.sites[s].unk_00=uint16_t(s%6+256*(s/6)); t.sites[s].terrainFlags=1; }
    }
    d->trailing={0,255,128}; return d;
}
uint32_t building(save::Document& d,int type,int site,int territory=1) {
    Building b{}; b.id=uint16_t(d.buildings.size()+1); b.flags=6; b.type=uint8_t(type); b.site=int8_t(site);
    b.territory=int16_t(territory); b.category=data::kBuildingTypes[type].category; b.race=2;
    if (!d.buildings.empty()) { b.prev.raw=d.buildings.back().id; d.buildings.back().next.raw=b.id; }
    d.territories[size_t(territory-1)].data.sites[site].building.raw=b.id;
    d.territories[size_t(territory-1)].data.sites[site].terrainFlags|=0x3000;
    d.buildings.push_back(b); return b.id;
}
Building& b(save::Document& d,uint32_t id) { for (auto& value:d.buildings) if (value.id==id) return value; throw std::runtime_error("bad test ID"); }
void housing(save::Document& d,int workers=0,int territory=1) {
    const auto id=building(d,3,35,territory); b(d,id).task[1]=20; b(d,id).labor[1]=workers;
}
uint32_t militia(save::Document& d,int territory,int experience,int mission=14,bool foreign=false) {
    Army a{}; a.id=uint16_t(300+d.armies.size()); a.type=23; a.unitClass=1; a.owner=foreign?1:0;
    a.territory.raw=a.dest.raw=a.origin.raw=uint32_t(territory); a.unk_25=uint8_t(mission); a.experience=int16_t(experience); a.unk_2a=7;
    auto& head=foreign?d.territories[size_t(territory-1)].data.foreignArmies:d.territories[size_t(territory-1)].data.armies;
    a.next.raw=head.raw; for (auto& old:d.armies) if (old.id==head.raw) old.prev.raw=a.id;
    head.raw=a.id; d.armies.push_back(a); return a.id;
}
std::vector<uint8_t> bytes(const save::Document& d) {
    std::vector<uint8_t> result; save::Error e; ok(save::encode(d,result,e),e);
    for (const auto& r:d.territories) {
        const auto* start=reinterpret_cast<const uint8_t*>(&r.data);
        result.insert(result.end(),start+kTerritorySavedBytes,start+sizeof(Territory));
    }
    return result;
}
TerritoryProductionContext context(uint32_t seed=1) {
    TerritoryProductionContext c; SessionRng rng; save::Error e; ok(rng.initialize(seed,e),e);
    c.effects.events.rngBeforeEvents=c.effects.ai.rng=c.effects.log.rngAfterEvents=rng.snapshot();
    c.effects.payment.selectedTerritory=1; c.effects.events.citiesBeforeLoad[6]=13; return c;
}
struct Outcome { std::unique_ptr<save::Document> d=std::make_unique<save::Document>(); TerritoryProductionReport report; };
Outcome run(const save::Document& d,ProductionPass pass=ProductionPass::Primary,TerritoryProductionContext c=context()) {
    const auto source=bytes(d); Outcome out; save::Error e{save::ErrorCode::Io,99,"stale"};
    ok(processTerritoryProduction(d,1,pass,c,*out.d,out.report,e),e);
    require(bytes(d)==source && e.code==save::ErrorCode::None && e.message.empty(),"production source immutable and error cleared");
    auto alias=std::make_unique<save::Document>(d); TerritoryProductionReport repeated;
    ok(processTerritoryProduction(*alias,1,pass,c,*alias,repeated,e),e);
    require(bytes(*alias)==bytes(*out.d) && repeated==out.report,"production alias transaction matches separate deterministic result");
    return out;
}
void denied(const save::Document& d,ProductionPass pass=ProductionPass::Primary,TerritoryProductionContext c=context()) {
    auto dest=fixture(); const auto original=bytes(d),before=bytes(*dest); TerritoryProductionReport report; report.createdIds={55}; const auto old=report; save::Error e;
    require(!processTerritoryProduction(d,1,pass,c,*dest,report,e) && e.code!=save::ErrorCode::None && !e.message.empty(),"unsafe production is explicit failure");
    require(bytes(d)==original && bytes(*dest)==before && report==old,"late failure preserves source,destination,report");
}
void completionAndArtOrder() {
    auto d=fixture(); housing(*d,5);
    const auto art=building(*d,23,0); b(*d,art).task[1]=8; b(*d,art).labor[1]=4;
    const auto culture=building(*d,21,2); b(*d,culture).task[0]=2; b(*d,culture).labor[0]=1; b(*d,culture).turnsLeft=1;
    const auto out=run(*d);
    require(out.report.events.size()==2 && out.report.events[0].type==61 && out.report.events[1].type==62,
            "art event occurs before later work completion, not a separate works-then-gains traversal");
    require(out.report.totals.artDraws.size()==1 && out.report.totals.artDraws[0].value==46 && out.report.totals.artDraws[0].tag=="Art" &&
            out.report.rngAfter.counters.long31==1 && out.report.rngAfter.counters.secondary15==2,"art uses exact tagged range100 and shared effect ordering");
    require(out.report.totals.culture==1 && out.d->territories[0].data.unk_2c==1 && out.d->territories[0].data.materials[10]==1,
            "newly activated culture slot consumes cached empty-slot carry1, not fresh output or normalized0");
    require(out.report.citiesAfter==context().effects.events.citiesBeforeLoad && out.d->events.empty() && out.d->options.turn==19 &&
            out.d->territories[0].data.materials[0]==909 && out.d->territories[0].data.production[3]==31 && out.d->territories[0].data.consumption[4]==43,
            "no hidden turn, event SAV serialization, scratch reset or money-material write");
    d=fixture(); housing(*d); const auto emptyArt=building(*d,23,0); b(*d,emptyArt).task[1]=8;
    const auto zero=run(*d);
    require(zero.report.totals.artDraws.size()==1 && zero.report.events.empty() && zero.report.totals.materials[10]==0,"zero art output STILL draws range100");
    auto invalid=context(); invalid.effects.events.rngBeforeEvents={}; invalid.effects.ai.rng={}; denied(*d,ProductionPass::Primary,invalid);
}
void gainsAndTraining() {
    auto d=fixture(); housing(*d,5);
    const auto producer=building(*d,14,14);
    const uint8_t tasks[]{12,13,3,4,6};
    for (int i=0;i<5;++i) { b(*d,producer).task[i]=tasks[i]; b(*d,producer).labor[i]=1; }
    auto out=run(*d);
    for (int m:{1,3,4,6}) require(out.report.totals.materials[size_t(m)]==1 && out.d->territories[0].data.materials[m]==1,"terrain material task map and minimum-one output");
    require(out.report.totals.materials[8]==3 && out.d->territories[0].data.materials[8]==3,
            "task6 uses nonterrain slot4 rate20: ceil(12*20/100)=3 electronics");
    require(out.d->territories[0].data.materials[2]==0 && out.d->territories[0].data.materials[5]==0 && out.d->territories[0].data.materials[7]==0,
            "unproduced energy/refined resources remain unchanged in primary pass");
    d=fixture(); housing(*d,5); const auto p=building(*d,14,14);
    const uint8_t more[]{14,5,7,17,19};
    for (int i=0;i<5;++i) { b(*d,p).task[i]=more[i]; b(*d,p).labor[i]=1; }
    d->players[0].lastIncome=32767; d->territories[0].data.colonyFlag=65535;
    out=run(*d);
    require(out.report.totals.credits==12 && out.report.totals.research==3 && out.report.totals.culture==2 && out.report.totals.population==2 &&
            out.report.totals.healing==3 && out.d->players[0].credits==112 && out.d->players[0].lastIncome==-32766 &&
            out.d->territories[0].data.colonyFlag==2 && out.d->territories[0].data.population==1002,
            "money/research/culture/pop/heal map, full credits and separate lowWORD wrapping");
    require(out.d->territories[0].data.taxAdjust==12 && out.d->territories[0].data.tradeIncome==3,"pass1 stores last production income and research words");
    d=fixture(); housing(*d,9); const auto trainer=building(*d,35,14); b(*d,trainer).task[1]=18; b(*d,trainer).labor[1]=1;
    d->territories[1].data.owner=0; d->territories[1].data.terrain=0; d->territories[2].data.owner=0;
    d->territories[0].data.adjacency[0]=(1u<<2)|(1u<<3);
    d->territories[1].data.adjacency[0]=1u<<1; d->territories[2].data.adjacency[0]=1u<<1;
    const auto local=militia(*d,1,95), sea=militia(*d,2,32767), land=militia(*d,3,10), foreign=militia(*d,1,10,14,true), other=militia(*d,1,10,13);
    out=run(*d);
    require(out.report.totals.training==10 && out.d->armyById(local)->experience==100 && out.d->armyById(local)->unk_2a==1 &&
            out.d->armyById(sea)->experience==-32759 && out.d->armyById(sea)->unk_2a==0 && out.d->armyById(land)->experience==10 &&
            out.d->armyById(foreign)->experience==10 && out.d->armyById(other)->experience==10,
            "mission14 own and same-owner adjacent SEA only; signed wrapping precedes upper clamp and rank");
    d->territories[0].data.terrain=0; d->territories[0].data.adjacency[0]=1u<<1;
    d->territories[1].data.adjacency[0]=0; d->territories[2].data.adjacency[0]=0;
    for (auto& a:d->armies) if (a.id==local) a.experience=80;
    out=run(*d); require(out.d->armyById(local)->experience==100,"self adjacency intentionally trains own list a second time");
}
void queuesBeforeGains() {
    auto d=fixture(); housing(*d,8); const auto factory=building(*d,14,14);
    b(*d,factory).task[1]=14; b(*d,factory).labor[1]=1; b(*d,factory).task[4]=11; b(*d,factory).labor[4]=1;
    QueueRecord queue{}; queue.unitType=1; queue.count=1; d->territories[0].queues[0].push_back(queue); d->players[0].credits=34;
    auto out=run(*d);
    require(out.report.manufacturing.size()==1 && out.report.manufacturing[0].headFinancingBlocked && out.report.createdIds.empty() &&
            out.d->territories[0].queues[0][0].count==1 && out.d->players[0].credits==37 && out.report.events[0].type==74,
            "unpaid queue sees34 before income3, so denied financing is NOT repaired by current-pass profits");
    d->players[0].credits=100; const auto second=building(*d,14,22); b(*d,second).task[4]=11; b(*d,second).labor[4]=1;
    out=run(*d);
    require(out.report.manufacturing.size()==1 && out.report.manufacturing[0].productionBefore==6 && out.d->players[0].credits==68 &&
            out.d->territories[0].queues[0][0].count==24,"two factories aggregate6 and finance initial head once before income3");
    std::copy_n(data::kUnitTypes[1].cost,11,std::begin(d->territories[0].queues[0][0].data)); d->territories[0].queues[0][0].count=1;
    out=run(*d);
    require(out.report.createdIds==std::vector<uint32_t>{1001} && out.report.queueStructureChanged && out.report.events[0].type==68 &&
            out.report.events[1].type==69 && out.d->armies[0].dest.raw==1,"production wires actual queue lifecycle and ordered completion/empty events");
}
void refinementAndZeroEffects() {
    auto d=fixture(); housing(*d,8); const auto factory=building(*d,14,14);
    b(*d,factory).task[2]=9; b(*d,factory).labor[2]=1; b(*d,factory).task[3]=10; b(*d,factory).labor[3]=1;
    d->territories[0].data.materials[4]=3; d->territories[0].data.materials[6]=3;
    d->territories[0].data.taxAdjust=17; d->territories[0].data.unk_2c=18; d->territories[0].data.tradeIncome=19;
    auto out=run(*d,ProductionPass::Refinement);
    require(out.report.totals.steel==2 && out.report.totals.electronics==2 && out.report.steelConverted==2 && out.report.electronicsConverted==2 &&
            out.d->territories[0].data.materials[4]==1 && out.d->territories[0].data.materials[5]==2 && out.d->territories[0].data.materials[6]==1 &&
            out.d->territories[0].data.materials[7]==2 && out.report.refinements.empty(),"pass2 locally refines iron->steel and endurium->triidium");
    require(out.d->territories[0].data.taxAdjust==17 && out.d->territories[0].data.unk_2c==18 && out.d->territories[0].data.tradeIncome==19,
            "pass2 preserves pass1 income/culture/research snapshots");
    d->territories[0].data.materials[4]=1; d->territories[0].data.materials[6]=1; d->players[0].credits=0;
    // Event60 means existing but unreachable stock, not global nonexistence.
    d->territories[1].data.owner=0;
    d->territories[1].data.materials[4]=2; d->territories[1].data.materials[6]=2;
    out=run(*d,ProductionPass::Refinement);
    require(out.report.refinements.size()==2 && out.report.events.size()==2 && out.report.events[0].type==60 && out.report.events[1].type==60 &&
            out.report.refinements[0].collections[0].request.material==4 && out.report.refinements[1].collections[0].request.material==6 &&
            out.report.steelConverted==1 && out.report.electronicsConverted==1,"ordered failed imports still convert available stocks");
    d->players[0].credits=100; d->territories[1].data.owner=0;
    d->territories[0].data.adjacency[0]=1u<<2; d->territories[1].data.adjacency[0]=1u<<1;
    d->territories[1].data.materials[4]=2; d->territories[1].data.materials[6]=2;
    for (auto& v:d->raceStats.v[53]) v=0; d->techs[46].knownMask=1;
    out=run(*d,ProductionPass::Refinement);
    require(out.report.refinements.size()==2 && out.report.events.empty() && out.report.steelConverted==2 && out.report.electronicsConverted==2 &&
            out.d->territories[1].data.materials[4]==1 && out.d->territories[1].data.materials[6]==1 && out.report.collectionAfter.transfers.size()==2,
            "pass2 uses real connected free-freight imports and carries transfer ledger between materials");
    d=fixture(); const auto id=militia(*d,1,401); d->territories[0].data.population=500;
    out=run(*d,ProductionPass::Refinement);
    require(out.d->territories[0].data.population==0 && out.d->armyById(id)->experience==100 && out.d->armyById(id)->unk_2a==1,
            "even empty pass2 calls maxpopulation clamp and TrainMilitia0");
}
void worldAndFailures() {
    auto d=fixture(); housing(*d); const auto art=building(*d,23,0); b(*d,art).task[1]=8; b(*d,art).labor[1]=4;
    d->territories[2].data.owner=0; housing(*d,0,3);
    const auto original=bytes(*d); auto dest=fixture(); WorldProductionReport world; save::Error e;
    ok(processWorldProduction(*d,ProductionPass::Primary,context(),*dest,world,e),e);
    require(bytes(*d)==original && world.territories.size()==2 && world.territories[0].territory==1 && world.territories[1].territory==3 &&
            world.rngAfter==world.territories.back().rngAfter && world.territories[1].logAfter==world.logAfter,"world sweep1..N skips ONLY unowned and carries continuation");
    d->territories[2].data.adjacency[0]=1; // Missing native sentinel, reached AFTER T1 art/RNG/event.
    const auto before=bytes(*dest); const auto reportBefore=world;
    require(!processWorldProduction(*d,ProductionPass::Primary,context(),*dest,world,e) && bytes(*dest)==before && world==reportBefore,
            "late territory failure rolls back earlier art, events, RNG and all document mutations");
    d->territories[0].data.adjacency[0]=1; denied(*d);
    d->territories[0].data.adjacency[0]=0; denied(*d,ProductionPass(3));
    auto bad=context(); bad.effects.events.rngBeforeEvents.format=99; denied(*d,ProductionPass::Primary,bad);
    d->territories[0].data.owner=1; denied(*d); // Late nonlocal art notice requires actual AI bindings.
    AiSession ai; ok(ai.initializeAfterLoad(*d,e),e); auto aiContext=context(); aiContext.effects.aiSession=&ai;
    const auto real=run(*d,ProductionPass::Primary,aiContext);
    require(real.report.events[0].aiDispatched && !real.report.events[0].aiReport.handled && real.report.rngAfter.counters.long31==1 &&
            real.report.rngAfter.counters.secondary15==0,"nonlocal art dispatches actual AI default, not local portrait RNG");
}
}
int main() {
    try {
        std::vector<uint8_t> beforeGs(sizeof(gs)),beforeGg(sizeof(gg));
        std::memcpy(beforeGs.data(),&gs,sizeof(gs)); std::memcpy(beforeGg.data(),&gg,sizeof(gg));
        const auto seed=rtl::seed(),seedHi=rtl::seedHi();
        completionAndArtOrder(); gainsAndTraining(); queuesBeforeGains(); refinementAndZeroEffects(); worldAndFailures();
        require(std::memcmp(beforeGs.data(),&gs,sizeof(gs))==0 && std::memcmp(beforeGg.data(),&gg,sizeof(gg))==0 && rtl::seed()==seed && rtl::seedHi()==seedHi,
                "territorial production leaves global game and process RNG intact");
        std::cout<<"territory_production: interleaved slots/work/art, queues before gains, training, refinement/imports and world rollback passed\n"; return 0;
    } catch (const std::exception& e) { std::cerr<<"territory_production: "<<e.what()<<'\n'; return 1; }
}
