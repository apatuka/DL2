// Oracles derived from0047597c/0044db50/004484fc, not a live original replay.
#include "game/entity_creation.h"
#include "game/runtime_state.h"
#include "game/data_tables.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include <algorithm>
#include <bit>
#include <cstring>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
using namespace dl2;
using namespace dl2::simulation;
void require(bool condition,const char* message) { if (!condition) throw std::runtime_error(message); }
std::unique_ptr<save::Document> fixture(int count=3) {
    auto d=std::make_unique<save::Document>();
    std::memcpy(d->header.text,save::kHeaderText,sizeof(save::kHeaderText)); d->header.version=kSaveVersion;
    d->options.numPlayers=2; d->options.localPlayer=0; d->options.turn=19; d->options.nextGlobalId=411;
    d->options.gameId=54; d->world.width=uint8_t(count); d->world.height=1; d->world.numTerritories=uint16_t(count);
    d->territories.resize(size_t(count)); d->tiles.resize(size_t(count));
    for (int p=0;p<7;++p) {
        d->players[size_t(p)].index=uint8_t(p); d->players[size_t(p)].race=2;
        d->players[size_t(p)].type=p==0?1:3; d->players[size_t(p)].credits=10000;
        d->ministerJobs[size_t(p)].resize(1); d->ministerJobs[size_t(p)][0].type=1;
        d->raceStats.v[24][p]=100; d->raceStats.v[2][p]=100;
    }
    for (int i=0;i<count;++i) {
        auto& t=d->territories[size_t(i)].data; t.index=uint16_t(i+1); t.owner=0; t.terrain=1;
        std::memcpy(t.name,"Alpha",6); t.numTiles=1; t.tiles[0].raw=uint32_t(i); t.population=500; t.morale=100;
        for (int m=1;m<11;++m) t.materials[m]=2000;
        for (auto& value:t.production) value=77;
        t.consumption[7]=1234; t.portTarget=2;
        for (int s=0;s<36;++s) {
            t.sites[s].unk_00=uint16_t((s%6)|((s/6)<<8)); t.sites[s].terrainFlags=1;
            t.sites[s].unk_05[11]=0x55;
        }
        d->tiles[size_t(i)].x=uint8_t(i); d->tiles[size_t(i)].territory=int16_t(i+1);
    }
    d->trailing={0,0xff,0x80}; d->localList={0,99}; return d;
}
Building& building(save::Document& d,int type,int site=0,int territory=1) {
    Building b{}; b.id=uint16_t(2000+d.buildings.size()); b.type=uint8_t(type); b.category=data::kBuildingTypes[type].category;
    b.territory=int16_t(territory); b.site=int8_t(site); b.flags=6; b.race=2;
    if (!d.buildings.empty()) { b.prev.raw=d.buildings.back().id; d.buildings.back().next.raw=b.id; }
    auto& cell=d.territories[size_t(territory-1)].data.sites[site]; cell.building.raw=b.id; cell.terrainFlags|=0x3000;
    if (type==1) { b.task[1]=20; b.labor[1]=5; }
    d.buildings.push_back(b); return d.buildings.back();
}
void adjacent(save::Document& d,int a,int b) {
    d.territories[size_t(a-1)].data.adjacency[b/16]|=uint16_t(1u<<(b%16));
    d.territories[size_t(b-1)].data.adjacency[a/16]|=uint16_t(1u<<(a%16));
}
std::vector<uint8_t> bytes(const save::Document& d) {
    std::vector<uint8_t> result; save::Error error;
    if (!save::encode(d,result,error)) throw std::runtime_error(error.message);
    for (const auto& r:d.territories) {
        const auto* ptr=reinterpret_cast<const uint8_t*>(&r.data);
        result.insert(result.end(),ptr+kTerritorySavedBytes,ptr+sizeof(Territory));
    }
    return result;
}
ConstructionOrderContext context() {
    ConstructionOrderContext c; c.payment.selectedTerritory=1;
    SessionRng rng; save::Error error; require(rng.initialize(54,error),"initialize explicit test RNG");
    c.events.rngBeforeEvents=c.ai.rng=c.log.rngAfterEvents=rng.snapshot();
    c.log.slotPayloads[0]={71,93}; return c;
}
struct Outcome { std::unique_ptr<save::Document> d=std::make_unique<save::Document>(); ConstructionOrderReport report; };
Outcome order(const save::Document& d,BuildingCreationRequest request,ConstructionOrderContext ctx=context()) {
    const auto before=bytes(d); const auto priorLog=ctx.log; const auto priorAi=ctx.ai;
    Outcome out; save::Error error{save::ErrorCode::Io,17,"stale"};
    if (!startConstruction(d,request,ctx,*out.d,out.report,error)) throw std::runtime_error(error.message);
    require(error.code==save::ErrorCode::None && error.offset==0 && error.message.empty(),"evaluated order clears error");
    require(bytes(d)==before && ctx.log==priorLog && ctx.ai==priorAi,"order preserves input and borrowed continuation context");
    auto alias=std::make_unique<save::Document>(d); ConstructionOrderReport repeated;
    require(startConstruction(*alias,request,ctx,*alias,repeated,error) && bytes(*alias)==bytes(*out.d) && repeated==out.report,
            "in-place order is deterministic and transactionally equivalent");
    return out;
}
void reject(const save::Document& d,BuildingCreationRequest request,ConstructionOrderContext ctx=context()) {
    const auto before=bytes(d); auto destination=fixture(); const auto oldDestination=bytes(*destination);
    ConstructionOrderReport report; report.accepted=true; report.attemptedId=999; report.createdIds={1,2}; const auto old=report;
    save::Error error;
    require(!startConstruction(d,request,ctx,*destination,report,error) && error.code!=save::ErrorCode::None && !error.message.empty(),
            "unsafe construction domain fails explicitly");
    require(bytes(d)==before && bytes(*destination)==oldDestination && report==old,"false result rolls back all document/context/report effects");
}
void paidConstructionAndLabor() {
    auto d=fixture(); building(*d,1);
    auto housing=order(*d,{1,1,2}); const auto* b=housing.d->buildingById(412);
    require(housing.report.accepted && housing.report.createdIds==std::vector<uint32_t>{412} && b && b->flags==6 &&
            b->turnsLeft==10 && b->cost[0]==50 && b->cost[3]==10 && b->task[0]==2 && b->labor[0]==1 &&
            housing.d->buildings[0].labor[1]==4,"Housing paid but NOT completed; urgency stops at one worker capable of25work");
    require(housing.d->players[0].credits==9950 && housing.d->territories[0].data.materials[3]==1990 &&
            housing.report.localLaborBalanced && housing.report.siteRoadsRebuilt && housing.d->options.turn==19,
            "real payment/labor/roads without turn progress");
    require(housing.report.events.size()==1 && housing.report.events[0].local && housing.report.events[0].localReport.stored &&
            housing.report.logAfter.entries.size()==1 && housing.report.logAfter.entries[0].type==64 &&
            housing.report.logAfter.entries[0].player==71 && housing.report.logAfter.entries[0].param==93,
            "ordinary construction log preserves inactive-slot payload, unlike LogEventEx");
    const auto& text=housing.report.logAfter.entries[0].text;
    require(std::string(text.begin(),text.end())=="Our colonists have started construction on the Housing in Alpha. It should be finished after a while.",
            "canonical original construction event text");
    require(housing.report.rngAfter.counters.secondary15==1 && housing.report.rngAfter==housing.report.aiAfter.rng &&
            housing.report.logAfter.rngAfterEvents==housing.report.rngAfter && housing.d->events.empty(),
            "one real portrait draw shared with AI continuation, no partial SAV event serialization");
    auto farm=order(*d,{1,5,14});
    require(farm.d->buildingById(412)->turnsLeft==75 && farm.d->buildingById(412)->labor[0]==3 &&
            farm.d->buildings[0].labor[1]==2,"Farm75work needs exactly3 of4 possible workers");
    d->options.fastProduction=1; auto fast=order(*d,{1,5,14});
    require(fast.d->buildingById(412)->labor[0]==2,"fast-production urgency doubles scalar output and stops at2workers");
    d->options.fastProduction=0; d->techs[33].knownMask=1;
    auto shrine=order(*d,{1,45,14});
    require(shrine.d->buildingById(412)->turnsLeft==100 && shrine.d->buildingById(412)->labor[0]==1 &&
            !(shrine.d->territories[0].data.flags&0x10),"shrine task2 output doubles twice with Native Languages, no editor shrine flag");
    // StartConstruction is allowed to be the action performed by an existing
    // minister3; no hidden callback or fabricated job completion is necessary.
    d->ministerJobs[0][0].type=3; d->ministerJobs[0][0].param[0]=1; d->ministerJobs[0][0].param[1]=2;
    auto managed=order(*d,{1,1,2});
    require(managed.d->ministerJobs[0][0].type==3 && managed.d->buildings.back().minister==0,"caller minister job persists without fabricated dispatch");
}
void denialsAndFailures() {
    auto d=fixture(); building(*d,1); const auto ctx=context();
    auto occupied=order(*d,{1,1,0});
    require(!occupied.report.accepted && occupied.report.denial==ConstructionOrderDenial::Placement &&
            occupied.report.placementReason==PlacementReason::Occupied && occupied.d->options.nextGlobalId==412 &&
            occupied.d->territories[0].data.production[1]==77 && !occupied.report.paymentEvaluated &&
            occupied.report.logAfter==ctx.log && occupied.report.rngAfter==ctx.events.rngBeforeEvents,
            "ordinary placement refusal consumesID but does not quote, log, clear reservations or draw RNG");
    d->players[0].credits=0;
    auto poor=order(*d,{1,1,2});
    require(!poor.report.accepted && poor.report.denial==ConstructionOrderDenial::Payment && poor.report.payment.failureMask==1 &&
            poor.report.paymentEvaluated && !poor.report.payment.collectionAttempted && poor.d->options.nextGlobalId==412 &&
            poor.d->buildings.size()==1 && poor.d->territories[0].data.production[1]==0 && poor.d->players[0].credits==0 &&
            poor.report.events.empty(),"financial denial retains ID and real reservation scratch, never creates a paid-success shell");
    d->players[0].credits=10000;
    d->options.nextGlobalId=65535; reject(*d,{1,1,2}); d->options.nextGlobalId=1999; reject(*d,{1,1,2});
    d->options.nextGlobalId=411; reject(*d,{0,1,2}); reject(*d,{1,48,2});
    auto noRng=ctx; noRng.events.rngBeforeEvents={}; reject(*d,{1,1,2},noRng);
    std::memset(d->territories[0].data.name,'X',25); reject(*d,{1,1,2}); std::memcpy(d->territories[0].data.name,"Alpha",6);
    d->territories[0].data.sites[1].terrainFlags=254; reject(*d,{1,1,2}); //After provisional payment/event/labor.
    d=fixture(35); d->options.nextGlobalId=4000;
    for (int n=0;n<1199;++n) building(*d,29,n%36,n/36+1);
    auto full=order(*d,{35,29,0});
    require(!full.report.accepted && full.report.denial==ConstructionOrderDenial::ReservedPoolSlot &&
            full.d->options.nextGlobalId==4001 && full.d->buildings.size()==1199 && !full.report.paymentEvaluated,
            "pool refusal retains one original reserve and still consumes the attempted ID");
}
void importsPortsAndSpecialStarts() {
    auto d=fixture(); building(*d,1); d->territories[0].data.materials[3]=0;
    d->territories[1].data.materials[3]=20; adjacent(*d,1,2);
    auto imported=order(*d,{1,1,2});
    require(imported.report.accepted && imported.report.payment.transportQuote==20 && imported.report.payment.collection.transfers.size()==1 &&
            imported.d->players[0].credits==9930 && imported.d->territories[1].data.materials[3]==10 &&
            imported.d->buildingById(412)->cost[3]==10,"real wood import, fee and paid-cost record integrated with construction");
    d=fixture(); building(*d,1); adjacent(*d,1,2); adjacent(*d,1,3);
    d->territories[1].data.terrain=0; d->territories[1].data.owner=-1; d->territories[2].data.terrain=0;
    auto port=order(*d,{1,24,2});
    require(port.report.accepted && port.report.portTargetBefore==2 && port.report.portTargetAfter==3 &&
            port.d->territories[0].data.portTarget==3,"port chooses first own creatable adjacent sea over earlier unowned candidate");
    d=fixture(); d->territories[0].data.terrain=0; d->techs[19].knownMask=1;
    auto platform=order(*d,{1,38,25});
    require(platform.report.accepted && platform.report.createdIds==std::vector<uint32_t>{412} && platform.d->buildings.size()==1 &&
            platform.d->buildings[0].turnsLeft==0 && platform.d->territories[0].data.sites[15].terrainFlags==0x5101,
            "StartConstruction platform does not fabricate CreateBuilding's SeaHab companion, consumes only one ID");

    // Canonical Hydroponic Farm:100 credits,50 wood,50 iron. Transporters makes
    // own connected route free, but collect(fee0) still caps quantity by credits.
    // Quote succeeds before base payment; then disconnected Triidium emits60,
    // and now-zero credits prevent even the free Iron import. No rollback is
    // fabricated for this NORMAL original payment refusal.
    d=fixture();
    for (auto& record:d->territories) for (auto& stock:record.data.materials) stock=0;
    d->territories[0].data.materials[3]=50; d->territories[1].data.materials[4]=50;
    d->territories[2].data.materials[7]=1; adjacent(*d,1,2);
    d->players[0].credits=100; d->techs[11].knownMask=1; d->techs[46].knownMask=1;
    auto partial=order(*d,{1,6,14});
    require(!partial.report.accepted && partial.report.denial==ConstructionOrderDenial::Payment &&
            partial.report.payment.collectionAttempted && partial.report.payment.failureMask==0x10 &&
            partial.report.payment.paid[0]==100 && partial.report.payment.paid[3]==50 && partial.report.payment.paid[4]==0 &&
            partial.d->players[0].credits==0 && partial.d->territories[0].data.materials[3]==0 && partial.d->buildings.empty(),
            "original partial payment refusal retains spent credits/wood but frees the provisional building");
    require(partial.report.events.size()==1 && partial.report.events[0].type==60 && partial.report.logAfter.entries.size()==1 &&
            partial.report.logAfter.entries[0].player==1 && partial.report.logAfter.entries[0].param==7 &&
            partial.report.rngAfter.counters.secondary15==1,"import LogEventEx stores territory/material payload and advances shared portrait RNG before denied order");
    const auto& blockade=partial.report.logAfter.entries[0].text;
    require(std::string(blockade.begin(),blockade.end())=="A blockade of Alpha has cut off our much needed shipments of triidium!",
            "canonical blockade text uses lowercase material table");
}
void aiAndPurity() {
    auto d=fixture(); building(*d,1); d->territories[0].data.owner=1;
    AiSession session; save::Error error; require(session.initializeAfterLoad(*d,error),"initialize actual owned AI session");
    auto ctx=context(); ctx.aiSession=&session;
    std::vector<uint8_t> globalState(sizeof(gs)),globalMisc(sizeof(gg));
    std::memcpy(globalState.data(),&gs,sizeof(gs)); std::memcpy(globalMisc.data(),&gg,sizeof(gg));
    const auto seed=rtl::seed(),seedHi=rtl::seedHi();
    auto ai=order(*d,{1,1,2},ctx);
    require(ai.report.accepted && !ai.report.localLaborBalanced && ai.d->buildings[0].labor[1]==5 &&
            ai.d->buildingById(412)->labor[0]==0 && ai.d->buildingById(412)->task[0]==2 &&
            ai.report.events.size()==1 && ai.report.events[0].aiDispatched && !ai.report.events[0].aiReport.handled &&
            ai.report.rngAfter==ctx.events.rngBeforeEvents && ai.report.logAfter==ctx.log,
            "AI order initializes tasks but skips human balance, dispatches real default64 with no portrait draw");
    auto missing=ctx; missing.aiSession=nullptr; reject(*d,{1,1,2},missing);
    auto mismatch=ctx; mismatch.ai.rng.rtlLow^=1; reject(*d,{1,1,2},mismatch);
    d->players[1].type=255;
    auto signedHuman=order(*d,{1,1,2});
    require(signedHuman.report.accepted && signedHuman.report.localLaborBalanced && signedHuman.d->buildingById(412)->labor[0]==1 &&
            !signedHuman.report.events[0].aiDispatched && !signedHuman.report.events[0].local,
            "signed player.type255 takes human labor but nonlocal logger returns without AI callback");
    require(std::memcmp(globalState.data(),&gs,sizeof(gs))==0 && std::memcmp(globalMisc.data(),&gg,sizeof(gg))==0 &&
            rtl::seed()==seed && rtl::seedHi()==seedHi,"construction uses no game globals or process RNG");
}
void runtimeContinuation() {
    auto d=fixture(); const auto oldId=building(*d,1).id; const auto before=bytes(*d);
    runtime::State state; save::Error error; require(state.prepare(*d,error),"runtime prepares paid-construction fixture");
    const auto survivor=state.buildingById(oldId); const auto territory=state.territoryByIndex(1);
    auto ctx=context();
    if (state.sessionRng().initialized) ctx.events.rngBeforeEvents=ctx.ai.rng=ctx.log.rngAfterEvents=state.sessionRng();
    runtime::BuildingHandle first; ConstructionOrderReport report;
    require(state.startConstruction({1,1,2},ctx,first,report,error) && report.accepted && state.building(first) &&
            state.buildingLinks(first)->territory==territory && state.buildingLinks(first)->previous==survivor &&
            state.building(survivor) && state.stage()==runtime::Stage::EntitiesEdited,"runtime commits paid entity with new handle and survivor graph intact");
    const auto firstBytes=bytes(*state.document()); const auto firstReport=report; const auto firstRng=state.sessionRng();
    auto second=first;
    require(!state.startConstruction({1,5,14},ctx,second,report,error) && bytes(*state.document())==firstBytes && report==firstReport && second==first,
            "runtime rejects stale continuation instead of rewinding paid event/RNG state");
    ctx.log=report.logAfter; ctx.ai=report.aiAfter; ctx.events.rngBeforeEvents=report.rngAfter;
    ctx.payment.collection=report.payment.collection;
    require(state.startConstruction({1,5,14},ctx,second,report,error) && report.accepted && state.building(first) && state.building(second) &&
            state.buildingLinks(first)->next==second && state.sessionRng().counters.secondary15==firstRng.counters.secondary15+1,
            "runtime chains explicit current context and retains earlier building lifetime");
    ctx.log=report.logAfter; ctx.ai=report.aiAfter; ctx.events.rngBeforeEvents=report.rngAfter; ctx.payment.collection=report.payment.collection;
    auto denied=first;
    require(state.startConstruction({1,1,2},ctx,denied,report,error) && !report.accepted && !denied &&
            state.building(first) && state.building(second) && state.document()->options.nextGlobalId==414,
            "evaluated normal denial commits consumedID, clears output handle and preserves all live identities");
    auto out=fixture(); const auto outBefore=bytes(*out);
    require(!state.capture(*out,error) && bytes(*out)==outBefore && !state.advanceTurn(error) && bytes(*d)==before,
            "paid order remains isolated/nonexportable until full turn and activation are integrated");
}
} // namespace
int main() {
    try {
        paidConstructionAndLabor(); denialsAndFailures(); importsPortsAndSpecialStarts(); aiAndPurity(); runtimeContinuation();
        std::cout<<"construction_order: paid work, ordinary denials, imports, labor urgency, ports, events/AI/RNG and rollback passed\n"; return 0;
    } catch (const std::exception& e) { std::cerr<<"construction_order: "<<e.what()<<'\n'; return 1; }
}
