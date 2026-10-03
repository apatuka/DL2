// Runtime authority/identity/continuation contracts, not duplicate rule oracles.
#include "game/runtime_state.h"
#include "game/data_tables.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include <algorithm>
#include <cstring>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>

namespace {
using namespace dl2;
using namespace dl2::simulation;
void require(bool value,const char* why) { if (!value) throw std::runtime_error(why); }
void ok(bool value,const save::Error& e) { if (!value) throw std::runtime_error(e.message); }
std::unique_ptr<save::Document> fixture() {
    auto d=std::make_unique<save::Document>(); std::memcpy(d->header.text,save::kHeaderText,sizeof(save::kHeaderText)); d->header.version=kSaveVersion;
    d->options.numPlayers=2; d->options.localPlayer=0; d->options.turn=19; d->options.nextGlobalId=1000;
    d->world.width=2; d->world.height=1; d->world.numTerritories=2; d->territories.resize(2); d->tiles.resize(2);
    for (size_t p=0;p<7;++p) {
        d->players[p].index=uint8_t(p); d->players[p].type=p?3:1; d->players[p].race=2; d->players[p].credits=1000; d->players[p].taxLevel=2;
        d->ministerJobs[p].resize(1); d->ministerJobs[p][0].type=1;
        for (auto& row:d->raceStats.v) row[p]=100;
        d->raceStats.v[27][p]=0;
    }
    for (size_t i=0;i<2;++i) {
        auto& t=d->territories[i].data; t.index=uint16_t(i+1); t.owner=0; t.terrain=1; t.numTiles=1; t.tiles[0].raw=uint32_t(i);
        t.population=int16_t(i?100:500); t.morale=100; t.knowledge=100; std::memcpy(t.name,"Alpha",6);
        d->tiles[i].x=uint8_t(i); d->tiles[i].territory=int16_t(i+1); d->tiles[i].terrain=1;
        for (int s=0;s<36;++s) { t.sites[s].unk_00=uint16_t(s%6+256*(s/6)); t.sites[s].terrainFlags=1; }
        for (int m=1;m<11;++m) t.materials[m]=1000;
    }
    const auto add=[&](int id,int type,int territory,int site,int labor) {
        Building b{}; b.id=uint16_t(id); b.type=uint8_t(type); b.category=data::kBuildingTypes[type].category;
        b.territory=int16_t(territory); b.site=int8_t(site); b.race=2; b.flags=6; b.labor[1]=labor;
        std::copy_n(data::kBuildingTypes[type].tasks,5,b.task);
        if (!d->buildings.empty()) { b.prev.raw=d->buildings.back().id; d->buildings.back().next.raw=b.id; }
        d->territories[size_t(territory-1)].data.sites[site].building.raw=b.id; d->buildings.push_back(b);
    };
    add(100,2,1,0,4); add(200,19,1,2,1); add(300,2,2,0,1);
    d->techs[1].availableMask=d->techs[2].availableMask=1; d->localList={1,1,2};
    QueueRecord q{}; q.unitType=1; q.count=30; q.data[0]=35; d->territories[0].queues[0].push_back(q);
    return d;
}
std::vector<uint8_t> bytes(const save::Document& d) {
    std::vector<uint8_t> result; save::Error e; ok(save::encode(d,result,e),e);
    for (const auto& r:d.territories) { const auto* p=reinterpret_cast<const uint8_t*>(&r.data);
        result.insert(result.end(),p+kTerritorySavedBytes,p+sizeof(Territory)); }
    return result;
}
struct Handles {
    runtime::BuildingHandle housing,lab,other;
    runtime::TerritoryHandle territory;
    runtime::TileHandle tile;
    runtime::QueueHandle queue;
    runtime::QueueNodeHandle node;
    runtime::MinisterHandle minister;
    explicit Handles(const runtime::State& s):housing(s.buildingById(100)),lab(s.buildingById(200)),other(s.buildingById(300)),
        territory(s.territoryByIndex(1)),tile(s.tileByIndex(1)),queue(s.graph().territories[0].queues[0]),
        node(s.queue(queue)->first),minister(s.graph().ministerHeads[0]) {}
    void check(const runtime::State& s) const {
        require(s.building(housing) && s.building(lab) && s.building(other) && s.territory(territory) && s.tile(tile) &&
                s.queue(queue) && s.queueNode(node) && s.minister(minister),"orders preserve all surviving entity/static/production-queue handles");
        require(s.buildingById(100)==housing && s.queue(queue)->first==node && s.queueNode(node)->record.count==30,"research draft replacement does not retire production queue nodes");
    }
};
EconomicPhaseContext context() {
    EconomicPhaseContext c; SessionRng rng; save::Error e; ok(rng.initialize(123,e),e);
    c.effects.events.rngBeforeEvents=c.effects.ai.rng=c.effects.log.rngAfterEvents=rng.snapshot(); return c;
}
void sequenceAndTerminal() {
    auto d=fixture(); const auto archived=bytes(*d); save::Error e; runtime::State state; ok(state.prepare(*d,e),e); Handles h(state);
    const auto emptyRng=state.sessionRng(); ColonyLaborOrderReport labor;
    ok(state.transferLabor(0,{1,100,200,1,1},labor,e),e);
    require(labor.accepted && state.building(h.housing)->labor[1]==3 && state.building(h.lab)->labor[1]==2 && state.stage()==runtime::Stage::EntitiesEdited,"slot transfer commits real worker change"); h.check(state);
    ok(state.moveLabor(0,{1,200,100},labor,e),e); require(labor.accepted && state.building(h.housing)->labor[1]==4,"auto worker move composes with explicit transfer");
    ok(state.resetLabor(0,1,labor,e),e); require(labor.accepted && state.building(h.housing)->labor[1]==5 && state.building(h.lab)->labor[1]==0,"reset labor uses real housing and balance");
    ResearchOrderReport research; ok(state.orderResearch({0,ResearchOrderKind::Select,1},{},research,e),e);
    require(research.accepted && research.queueStructureChanged && state.document()->localList==std::vector<uint32_t>{1} && state.document()->players[0].currentResearch==1,"research command commits its own draft and setter");
    ok(state.orderResearch({0,ResearchOrderKind::ToggleQueue,2},{},research,e),e);
    require(state.document()->localList==std::vector<uint32_t>({1,2}),"research toggle appends real queue entry"); h.check(state);
    BuildingControlReport control; ok(state.controlBuilding({0,200,BuildingControl::ToggleTaskLock,1},control,e),e);
    require(control.accepted && (state.building(h.lab)->flags&0x200),"task lock commits without replacement identity");
    ok(state.controlBuilding({0,200,BuildingControl::ToggleActive,0},control,e),e);
    require(!(state.building(h.lab)->flags&4) && !(state.building(h.lab)->flags&0x200),"deactivation clears locks via real command");
    ok(state.controlBuilding({0,200,BuildingControl::ToggleActive,0},control,e),e); require(state.building(h.lab)->flags&4,"reactivation composes");
    PopulationMoveReport population; ok(state.movePopulation(0,{1,2,100,0,-1,-1},{},population,e),e);
    require(population.nativeResult && state.document()->territories[0].data.population==400 && state.document()->territories[1].data.population==200 &&
            state.populationEvents() && *state.populationEvents()==population.bindingsAfter,"population order commits and owns even empty initial sidecar"); h.check(state);
    require(state.sessionRng()==emptyRng && !state.loadedEvents() && !state.aiReactionContext() && bytes(*d)==archived,"manual orders do not fabricate RNG/event/AI state or mutate archival input");
    auto capture=fixture(); const auto oldCapture=bytes(*capture); require(!state.capture(*capture,e) && bytes(*capture)==oldCapture,"edited snapshot cannot be exported");
    const auto sidecar=*state.populationEvents(); auto phase=std::make_unique<EconomicPhaseReport>(); ok(state.runEconomicPhase(context(),*phase,e),e);
    require(state.stage()==runtime::Stage::EconomyPhaseApplied && phase->completed.size()==15 && state.document()->options.turn==19 &&
            state.populationEvents() && *state.populationEvents()==sidecar,"orders can feed real economic phase without losing sidecar or claiming full turn"); h.check(state);
    const auto final=bytes(*state.document()); const auto rng=state.sessionRng(); const auto oldLabor=labor; const auto oldResearch=research;
    const auto oldPopulation=population; const auto oldControl=control;
    require(!state.transferLabor(0,{1,100,200,1,1},labor,e) && !state.moveLabor(0,{1,100,200},labor,e) && !state.resetLabor(0,1,labor,e),"terminal phase rejects every labor wrapper");
    require(!state.orderResearch({0,ResearchOrderKind::ClearQueue,0},{},research,e) && !state.movePopulation(0,{1,2,1,0,-1,-1},{sidecar},population,e) &&
            !state.controlBuilding({0,200,BuildingControl::ToggleActive,0},control,e),"terminal phase rejects research/population/building wrappers");
    require(labor==oldLabor && research==oldResearch && population==oldPopulation && control==oldControl && bytes(*state.document())==final && state.sessionRng()==rng,
            "terminal rejections preserve every report, byte and RNG");
    require(!state.capture(*capture,e) && !state.advanceTurn(e),"economic completion still neither saveable nor a full turn");
}
void denialsAndAuthority() {
    auto d=fixture(); save::Error e; runtime::State state; ok(state.prepare(*d,e),e); Handles h(state); const auto original=bytes(*state.document());
    ColonyLaborOrderReport labor; e={save::ErrorCode::Io,9,"old"}; ok(state.transferLabor(0,{1,100,200,0,1},labor,e),e);
    require(!labor.accepted && e.code==save::ErrorCode::None && !e.offset && e.message.empty() && state.stage()==runtime::Stage::Prepared,"evaluated empty-slot denial clears error and keeps Prepared");
    ResearchOrderReport research; ok(state.orderResearch({0,ResearchOrderKind::Select,47},{},research,e),e);
    require(!research.accepted && research.denial==ResearchOrderDenial::NotQueueable && state.stage()==runtime::Stage::Prepared,"unqueueable technology denial does not commit draft");
    BuildingControlReport control; ok(state.controlBuilding({0,200,BuildingControl::ToggleTaskLock,0},control,e),e);
    require(!control.accepted && control.denial==BuildingControlDenial::EmptyTask && state.stage()==runtime::Stage::Prepared,"empty task lock denial stays Prepared");
    PopulationMoveReport population; ok(state.movePopulation(0,{1,1,100,0,-1,-1},{},population,e),e);
    require(!population.nativeResult && !state.populationEvents() && state.stage()==runtime::Stage::Prepared,"no-change population denial does not install transient metadata");
    h.check(state); require(bytes(*state.document())==original,"all ordinary denials preserve document");
    auto captured=fixture(); ok(state.capture(*captured,e),e); require(bytes(*captured)==original,"unchanged Prepared snapshot remains capturable");
    const auto priorLabor=labor; const auto priorResearch=research; const auto priorControl=control; const auto priorPopulation=population;
    require(!state.transferLabor(1,{1,100,200,1,1},labor,e) && !state.moveLabor(1,{1,100,200},labor,e) && !state.resetLabor(1,1,labor,e),"wrong actor rejected at runtime before labor changes");
    require(!state.orderResearch({1,ResearchOrderKind::Select,1},{},research,e) && !state.controlBuilding({1,200,BuildingControl::ToggleActive,0},control,e) &&
            !state.movePopulation(1,{1,2,100,0,-1,-1},{},population,e),"research/building/population enforce same runtime local actor");
    require(labor==priorLabor && research==priorResearch && control==priorControl && population==priorPopulation && bytes(*state.document())==original && state.stage()==runtime::Stage::Prepared,
            "authority errors preserve reports and state");
    require(!state.transferLabor(0,{1,100,200,7,1},labor,e) && labor==priorLabor && !state.moveLabor(0,{1,100,300},labor,e),"unsafe slots/cross-territory entities fail atomically"); h.check(state);
    for (bool wrongType:{false,true}) {
        auto invalid=fixture(); if (wrongType) invalid->players[0].type=3; else invalid->players[0].index=1;
        runtime::State denied; ok(denied.prepare(*invalid,e),e); require(!denied.resetLabor(0,1,labor,e) && labor==priorLabor && denied.stage()==runtime::Stage::Prepared,
            "local actor must be human with matching physical player index");
    }
    d=fixture(); d->territories[1].data.owner=1; runtime::State foreign; ok(foreign.prepare(*d,e),e);
    require(!foreign.resetLabor(0,2,labor,e) && !foreign.movePopulation(0,{2,1,100,0,-1,-1},{},population,e),"territory-aware wrappers reject non-owned colony");
    ok(foreign.controlBuilding({0,300,BuildingControl::ToggleActive,0},control,e),e);
    require(!control.accepted && control.denial==BuildingControlDenial::NotOwner && foreign.stage()==runtime::Stage::Prepared,"building ownership denial remains an evaluated unchanged command");
}
void plagueContinuationAndPartial() {
    auto d=fixture(); d->territories[0].data.flags|=0x20; save::Error e; runtime::State state; ok(state.prepare(*d,e),e); Handles h(state);
    PopulationMoveReport r; ok(state.movePopulation(0,{1,2,100,0,35,-1},{},r,e),e);
    require(!r.nativeResult && r.denial==PopulationMoveDenial::MissingSourceBuildingAfterTransfer && state.stage()==runtime::Stage::EntitiesEdited &&
            state.document()->players[0].credits==975 && state.document()->territories[0].data.population==400 && state.document()->territories[1].data.population==200,
            "native false after payment/population MUST commit, not be mistaken for ordinary denial");
    require(r.scheduledPlague==PlagueSchedule{0,2,-4} && state.populationEvents() && (*state.populationEvents())[0]==2 &&
            state.document()->randomEvents[0].unk_04==0 && state.document()->randomEvents[0].turnsLeft==-4,"partial outcome commits owned plague target with neutral raw word"); h.check(state);
    const auto first=bytes(*state.document()); const auto old=r; const auto bindings=*state.populationEvents();
    require(!state.movePopulation(0,{1,2,0,0,-1,-1},{},r,e) && r==old && bytes(*state.document())==first && *state.populationEvents()==bindings,
            "stale empty sidecar cannot replace owned plague bindings");
    PopulationMoveContext next{bindings}; ok(state.movePopulation(0,{1,2,0,0,-1,-1},next,r,e),e);
    require(r.nativeResult && r.scheduledPlague==PlagueSchedule{1,2,-4} && (*state.populationEvents())[0]==2 && (*state.populationEvents())[1]==2,
            "continued zero-population move retains slot0 and schedules real new slot1");
    const auto retained=*state.populationEvents(); BuildingControlReport control; ok(state.controlBuilding({0,200,BuildingControl::ToggleTaskLock,1},control,e),e);
    ResearchOrderReport research; ok(state.orderResearch({0,ResearchOrderKind::Select,1},{},research,e),e);
    require(state.populationEvents() && *state.populationEvents()==retained,"unrelated orders preserve sidecar through copyForEdit/finishEdit"); h.check(state);
    runtime::State moved(std::move(state)); require(moved.populationEvents() && *moved.populationEvents()==retained,"State move construction preserves sidecar"); h.check(moved);
    runtime::State assigned; assigned=std::move(moved); require(assigned.populationEvents() && *assigned.populationEvents()==retained,"State move assignment preserves sidecar"); h.check(assigned);
    auto bad=next; bad.bindings=retained; bad.bindings[0]=1; const auto before=bytes(*assigned.document()); const auto previous=r;
    require(!assigned.movePopulation(0,{1,2,0,0,-1,-1},bad,r,e) && r==previous && bytes(*assigned.document())==before && *assigned.populationEvents()==retained,
            "plausible but foreign target binding is rejected, not silently rebound");
    ok(assigned.prepare(*d,e),e); require(!assigned.populationEvents() && !assigned.building(h.housing) && assigned.stage()==runtime::Stage::Prepared,"successful fresh preparation clears sidecar and retires previous handles");
    d=fixture(); d->territories[0].data.flags|=0x20; for (auto& event:d->randomEvents) event.type=8; ok(assigned.prepare(*d,e),e);
    const auto full=bytes(*assigned.document()); const auto reportBefore=r;
    require(!assigned.movePopulation(0,{1,2,100,0,-1,-1},{},r,e) && e.code==save::ErrorCode::Limit && r==reportBefore &&
            bytes(*assigned.document())==full && !assigned.populationEvents() && assigned.stage()==runtime::Stage::Prepared,"full plague pool reverts preceding payment/morale and metadata installation");
}
}
int main() {
    try {
        std::vector<uint8_t> gsBefore(sizeof(gs)),ggBefore(sizeof(gg)); std::memcpy(gsBefore.data(),&gs,sizeof(gs)); std::memcpy(ggBefore.data(),&gg,sizeof(gg));
        const auto low=rtl::seed(),high=rtl::seedHi(); sequenceAndTerminal(); denialsAndAuthority(); plagueContinuationAndPartial();
        require(!std::memcmp(gsBefore.data(),&gs,sizeof(gs)) && !std::memcmp(ggBefore.data(),&gg,sizeof(gg)) && low==rtl::seed() && high==rtl::seedHi(),"runtime orders must not mutate legacy globals/RNG");
        std::cout<<"economic_orders_runtime: authority, edits, stable handles, sidecars, partial returns and terminal phase passed\n"; return 0;
    } catch (const std::exception& e) { std::cerr<<"economic_orders_runtime: "<<e.what()<<'\n'; return 1; }
}
