#include "game/runtime_state.h"
#include "game/army_pool.h"
#include "game/data_tables.h"
#include "game/save_files.h"
#include <algorithm>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <memory>
#include <stdexcept>
namespace {
using namespace dl2;
using namespace dl2::simulation;
void check(bool b,const char* m) { if(!b) throw std::runtime_error(m); }
void ok(bool b,const save::Error& e) { if(!b) throw std::runtime_error(e.message); }
std::unique_ptr<save::Document> fixture() {
    auto d=std::make_unique<save::Document>();
    std::memcpy(d->header.text,save::kHeaderText,sizeof(save::kHeaderText)); d->header.version=kSaveVersion;
    d->options.numPlayers=2; d->options.localPlayer=0; d->options.turn=19; d->options.nextGlobalId=1000;
    d->world.width=d->world.height=1; d->world.numTerritories=1; d->territories.resize(1); d->tiles.resize(1);
    for(size_t p=0;p<7;++p) {
        auto& player=d->players[p]; player.index=uint8_t(p); player.race=2; player.type=p?3:1;
        player.credits=1000; player.taxLevel=2; player.lastIncome=77;
        d->ministerJobs[p].resize(1); d->ministerJobs[p][0].type=1;
        for(auto& row:d->raceStats.v) row[p]=100;
        d->raceStats.v[27][p]=0; // Actual racial fixed80 morale branch, not a mocked callback.
    }
    auto& t=d->territories[0].data; t.index=1; t.owner=0; t.terrain=1; t.numTiles=1;
    t.population=400; t.morale=100; t.knowledge=100; std::memcpy(t.name,"Alpha",6);
    for(int s=0;s<36;++s) { t.sites[s].unk_00=uint16_t((s%6)|((s/6)<<8)); t.sites[s].terrainFlags=1; }
    for(int m=1;m<11;++m) t.materials[m]=1000;
    t.materials[3]=11000; d->tiles[0].territory=1; d->tiles[0].terrain=1;
    const auto add=[&](uint16_t id,int type,int site) {
        Building b{}; b.id=id; b.type=uint8_t(type); b.category=data::kBuildingTypes[type].category;
        b.race=2; b.territory=1; b.site=int8_t(site); b.flags=6;
        std::copy(std::begin(data::kBuildingTypes[type].tasks),std::end(data::kBuildingTypes[type].tasks),std::begin(b.task));
        if(!d->buildings.empty()) { b.prev.raw=d->buildings.back().id; d->buildings.back().next.raw=id; }
        d->buildings.push_back(b); t.sites[site].building.raw=id;
    };
    add(100,2,0); d->buildings.back().labor[1]=1;
    add(200,15,2); d->buildings.back().labor[4]=2;
    add(300,19,4); d->buildings.back().labor[1]=1;
    d->players[0].currentResearch=1; d->techs[1].progress[0]=uint16_t(data::kTechs[1].cost-1);
    d->localList={1,2};
    QueueRecord q{}; q.unitType=1; q.count=1; q.data[0]=35; d->territories[0].queues[0].push_back(q);
    return d;
}
EconomicPhaseContext context() {
    EconomicPhaseContext c; SessionRng rng; save::Error e; ok(rng.initialize(123,e),e);
    c.effects.events.rngBeforeEvents=c.effects.ai.rng=c.effects.log.rngAfterEvents=rng.snapshot(); return c;
}
std::vector<uint8_t> bytes(const save::Document& d) {
    std::vector<uint8_t> out; save::Error e; ok(save::encode(d,out,e),e);
    for(const auto& t:d.territories) {
        const auto* p=reinterpret_cast<const uint8_t*>(&t.data);
        out.insert(out.end(),p+kTerritorySavedBytes,p+sizeof(Territory));
    }
    return out;
}
const std::vector<EconomicStep> order{EconomicStep::Reset,EconomicStep::Taxes,EconomicStep::PrimaryProduction,
    EconomicStep::RecordNeeds,EconomicStep::Imports,EconomicStep::Food,EconomicStep::Energy,EconomicStep::Upkeep,
    EconomicStep::Refinement,EconomicStep::BuildingCosts,EconomicStep::PopulationGrowth,EconomicStep::Morale,
    EconomicStep::Research,EconomicStep::Unrest,EconomicStep::FinalBalance};
void connected() {
    auto d=fixture(); const auto original=bytes(*d); auto c=context(); save::Error e; runtime::State state;
    ok(state.prepare(*d,e),e); const auto housing=state.buildingById(100),factory=state.buildingById(200);
    const auto t=state.territoryByIndex(1); const auto queue=state.graph().territories[0].queues[0];
    const auto node=state.queue(queue)->first;
    auto r=std::make_unique<EconomicPhaseReport>(); ok(state.runEconomicPhase(c,*r,e),e);
    check(r->completed==order && state.stage()==runtime::Stage::EconomyPhaseApplied,"15 original steps, terminal economic stage");
    check(r->prefix.createdIds.size()==1 && state.army(state.armyById(r->prefix.createdIds[0])) &&
          !state.queueNode(node) && state.queue(queue)->count==0,"manufacturing retains real allocation and queue retirement");
    check(state.building(housing) && state.building(factory) && state.territory(t),"surviving stable handles");
    check(r->growth.territories.size()==1 && r->growth.territories[0].before==400 && r->growth.territories[0].after>400,
          "growth follows actual production/food and precedes morale");
    check(r->morale.territories[0].before==100 && r->morale.territories[0].after==80 &&
          r->unrest.territories[0].populationBefore==r->growth.territories[0].after,"unrest sees new population and morale");
    check(r->research.players.size()==2 && r->research.players[0].points>0 &&
          r->research.players[0].points==state.document()->players[0].lastIncome,"research uses actual accumulated production budget");
    check(r->research.players[0].thresholdReached && (state.document()->techs[1].knownMask&1) &&
          r->research.acquisitions.size()==1 && state.document()->players[0].currentResearch==2,
          "generated research budget discovers technology and advances the real local queue");
    check(r->balance.territories[0].moraleBefore==80 && state.document()->territories[0].data.materials[3]==10000,
          "final labor and cap run after all economic predecessors");
    check(state.sessionRng()==r->rngAfter && state.sessionRng().counters.operations>r->prefix.rngAfter.counters.operations &&
          *state.loadedEvents()==r->logAfter && *state.aiReactionContext()==r->aiAfter,"one owned continuation through unrest");
    check(bytes(*d)==original && state.document()->options.turn==19,"source preserved and turn unchanged");
    auto pure=std::make_unique<save::Document>(*d); auto again=std::make_unique<EconomicPhaseReport>();
    AiSession ai; ok(ai.initializeAfterLoad(*pure,e),e); c.effects.aiSession=&ai;
    ok(runEconomicPhase(*pure,c,*pure,*again,e),e);
    check(bytes(*pure)==bytes(*state.document()) && again->rngAfter==r->rngAfter && again->logAfter==r->logAfter,
          "pure alias phase equals runtime sequence with real AI binding");
    const auto final=bytes(*state.document()); const auto steps=r->completed; const auto rng=state.sessionRng();
    check(!state.runEconomicPhase(c,*r,e) && !state.capture(*pure,e) && !state.advanceTurn(e),"cannot repeat/export/advance whole turn");
    UnitDequeueReport dq; check(!state.dequeueUnit({1,1,0},dq,e),"terminal phase cannot accept further structural experiments");
    MovementCrossingsContext crossingContext;
    crossingContext.ai = *state.aiReactionContext(); crossingContext.log = *state.loadedEvents();
    crossingContext.cities = *state.eventCities();
    if (state.buildingRemovalContext()) crossingContext.campaign = *state.buildingRemovalContext();
    MovementCrossingsReport crossingReport;
    check(!state.resolveMovementCrossings(crossingContext,crossingReport,e) &&
          e.message == "Structural entity edits require a prepared or structurally edited state" &&
          crossingReport.crossings.empty() && state.stage()==runtime::Stage::EconomyPhaseApplied,
          "crossings must not bypass the missing phase contract after economics");
    check(bytes(*state.document())==final && r->completed==steps && state.sessionRng()==rng,"failed operations preserve final state/report");
}
void lateRollback() {
    auto d=fixture(); d->players[0].currentResearch=-1; save::Error e; runtime::State state; ok(state.prepare(*d,e),e);
    const auto before=bytes(*state.document()); const auto h=state.buildingById(100); const auto rng=state.sessionRng();
    auto r=std::make_unique<EconomicPhaseReport>(); r->completed={EconomicStep::FinalBalance}; r->growth.territories.resize(2);
    check(!state.runEconomicPhase(context(),*r,e) && e.message.find("Research")!=std::string::npos,
          "research error occurs after production, costs, growth and morale");
    check(bytes(*state.document())==before && state.building(h) && state.stage()==runtime::Stage::Prepared &&
          state.sessionRng()==rng && !state.loadedEvents() && r->growth.territories.size()==2 &&
          r->completed==std::vector<EconomicStep>{EconomicStep::FinalBalance},"late failure rolls back ALL phases and handles/report/context");
}
void campaignSkipAndDisband() {
    auto d=fixture(); auto c=context(); c.campaignFlags=1u<<10; d->players[0].foodFlags=4;
    save::Error e; runtime::State state; ok(state.prepare(*d,e),e); auto r=std::make_unique<EconomicPhaseReport>();
    ok(state.runEconomicPhase(c,*r,e),e);
    check(r->growth.territories[0].campaignSkipped && r->growth.territories[0].after==400,"live campaign flag inhibits local growth only");
    check(r->prefix.createdIds==r->prefix.retiredIds && r->prefix.createdIds.size()==1 && state.document()->armies.empty(),
          "created then disbanded army has no phantom slot in completed economic phase");
}
void deferredTaskForceDisband() {
    auto d=fixture(); d->territories[0].queues[0].clear(); d->players[0].foodFlags=4;
    Army a{}; a.id=20; a.type=1; a.unitClass=1; a.owner=0; a.health=100; a.job=1;
    a.dest.raw=a.territory.raw=a.origin.raw=1; std::memcpy(a.name,"Guard",6);
    d->armies.push_back(a); d->territories[0].data.armies.raw=20; d->jobs[0][0].armyIds[0]=20;
    const auto original=bytes(*d); runtime::State state; save::Error e; ok(state.prepare(*d,e),e);
    const auto old=state.armyById(20); auto r=std::make_unique<EconomicPhaseReport>();
    ok(state.runEconomicPhase(context(),*r,e),e);
    check(r->completed==order && r->prefix.retiredIds==std::vector<uint32_t>{20} && !state.army(old) &&
          state.document()->jobs[0][0].armyIds[0]==20 && state.graph().jobs[0][0].pointerPresent[0] &&
          state.graph().jobs[0][0].poolSlots[0]!=0 && !state.graph().jobs[0][0].armies[0] && bytes(*d)==original,
          "all15 steps preserve native deferred job target after upkeep retirement and invalidate public handle");
    ok(save::validate(*state.document(),e),e);
    std::vector<uint8_t> denied{1,9};
    check(!save::encode(*state.document(),denied,e) && denied==std::vector<uint8_t>({1,9}),
          "economic phase with retained freed-cell binding cannot be archived");
}
void liveResearchCampaignFlag() {
    auto d=fixture(); d->options.campaign=6; d->players[0].currentResearch=46;
    d->localList.clear(); d->techs[46].progress[0]=uint16_t(data::kTechs[46].cost-1);
    for(size_t i=1;i<46;++i) d->techs[i].knownMask=1;
    save::Error e; runtime::State unrestricted,restricted;
    ok(unrestricted.prepare(*d,e),e); ok(restricted.prepare(*d,e),e);
    auto off=context(),on=context(); on.campaignFlags=1u<<4;
    // The full sequence's mask is authoritative over isolated-leaf fields.
    off.effects.researchCampaignFlags=1u<<4;
    auto a=std::make_unique<EconomicPhaseReport>(),b=std::make_unique<EconomicPhaseReport>();
    ok(unrestricted.runEconomicPhase(off,*a,e),e); ok(restricted.runEconomicPhase(on,*b,e),e);
    check((unrestricted.document()->techs[46].knownMask&1) && (restricted.document()->techs[46].knownMask&1) &&
          (unrestricted.document()->techs[47].availableMask&1) && !(restricted.document()->techs[47].availableMask&1),
          "live campaign bit4 governs research restrictions; saved campaign alone must not enable them");
}
void corpus(const std::filesystem::path& path) {
    int n=0;
    for(const char* name:{"TUTORIAL.SAV","Saves/AUTOSAVE.SAV","Campaign/AUTOSAVE.CPN","Campaign/ChCht001.CPN"}) {
        if(!std::filesystem::is_regular_file(path/name)) continue;
        auto d=std::make_unique<save::Document>(); save::Error e; ok(save::readDocument(path/name,*d,e),e);
        const auto original=bytes(*d); runtime::State state; ok(state.prepare(*d,e),e);
        auto r=std::make_unique<EconomicPhaseReport>(); ok(state.runEconomicPhase(context(),*r,e),e);
        check(r->completed==order && state.document()->options.turn==d->options.turn && bytes(*d)==original,
              "readonly original-save phase, explicit cold lab not historical session replay"); ++n;
    }
    std::cout<<"economic phase: "<<n<<" read-only originals passed\n";
}
}
int main(int argc,char** argv) {
    try { connected(); lateRollback(); campaignSkipAndDisband(); deferredTaskForceDisband(); liveResearchCampaignFlag(); if(argc>1) corpus(argv[1]);
        std::cout<<"economic_phase: PASS\n"; return 0;
    } catch(const std::exception& e) { std::cerr<<e.what()<<'\n'; return 1; }
}
