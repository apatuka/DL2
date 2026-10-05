// Independent original-function oracles, not an observed native-game replay.
#include "game/entity_orders.h"
#include "game/army_pool.h"
#include "game/entity_creation.h"
#include "game/runtime_state.h"
#include "game/data_tables.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include <algorithm>
#include <array>
#include <cstring>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

namespace {
using namespace dl2;
using namespace dl2::simulation;
void require(bool yes,const char* why) { if (!yes) throw std::runtime_error(why); }
void checked(bool yes,const save::Error& e) { if (!yes) throw std::runtime_error(e.message); }
std::unique_ptr<save::Document> fixture() {
    auto d=std::make_unique<save::Document>();
    std::memcpy(d->header.text,save::kHeaderText,sizeof(save::kHeaderText)); d->header.version=kSaveVersion;
    d->options.numPlayers=2; d->options.localPlayer=0; d->options.turn=17; d->options.nextGlobalId=1000;
    d->world.width=3; d->world.height=1; d->world.numTerritories=3; d->tiles.resize(3); d->territories.resize(3);
    for (int p=0;p<7;++p) {
        d->players[size_t(p)].index=uint8_t(p); d->players[size_t(p)].type=p==0?1:3;
        d->players[size_t(p)].race=2; d->raceStats.v[24][p]=100;
        d->ministerJobs[size_t(p)].resize(1); d->ministerJobs[size_t(p)][0].type=1;
        for (auto& job:d->jobs[size_t(p)]) job.owner=int16_t(p);
    }
    for (int i=0;i<3;++i) {
        auto& t=d->territories[size_t(i)].data;
        t.index=uint16_t(i+1); t.owner=int8_t(i==2?1:0); t.terrain=uint8_t(i==1?0:1);
        t.population=500; t.morale=100; t.numTiles=1; t.visibility[size_t(t.owner)]=4;
        t.tiles[0].raw=uint32_t(i); d->tiles[size_t(i)].x=uint8_t(i); d->tiles[size_t(i)].territory=int16_t(i+1);
        for (int s=0;s<36;++s) { t.sites[s].unk_00=uint16_t((s%6)|((s/6)<<8)); t.sites[s].terrainFlags=1; }
        t.production[3]=12345; t.consumption[6]=-99;
    }
    d->trailing={0xff,0,0x80}; return d;
}
uint32_t building(save::Document& d,int type,int site=0,int territory=1) {
    Building b{}; b.id=uint16_t(50000+d.buildings.size()); b.type=uint8_t(type); b.category=data::kBuildingTypes[type].category;
    b.flags=6; b.territory=int16_t(territory); b.site=int8_t(site);
    if (!d.buildings.empty()) { b.prev.raw=d.buildings.back().id; d.buildings.back().next.raw=b.id; }
    d.territories[size_t(territory-1)].data.sites[site].building.raw=b.id; d.buildings.push_back(b); return b.id;
}
uint32_t army(save::Document& d,int type=1,int territory=1,int owner=0) {
    Army a{}; a.id=uint16_t(d.armies.size()+1); a.type=uint8_t(type); a.unitClass=data::kUnitTypes[type].unitClass;
    a.owner=int8_t(owner); a.health=100; a.territory.raw=a.dest.raw=a.origin.raw=uint32_t(territory);
    auto& t=d.territories[size_t(territory-1)].data; auto& head=t.owner==owner?t.armies:t.foreignArmies;
    a.next.raw=head.raw; for (auto& prior:d.armies) if (prior.id==head.raw) prior.prev.raw=a.id;
    head.raw=a.id; d.armies.push_back(a); return a.id;
}
std::vector<uint8_t> bytes(const save::Document& d) {
    std::vector<uint8_t> result; save::Error error; checked(save::encode(d,result,error),error);
    for (const auto& t:d.territories) {
        const auto* raw=reinterpret_cast<const uint8_t*>(&t.data);
        result.insert(result.end(),raw+kTerritorySavedBytes,raw+sizeof(Territory));
    }
    return result;
}
std::array<uint8_t,6> sea(const save::Document& d,int t) {
    std::array<uint8_t,6> result{};
    const auto* raw=reinterpret_cast<const uint8_t*>(&d.territories[size_t(t-1)].data);
    std::copy_n(raw+0x994,6,result.begin()); return result;
}
struct Demolition {
    std::unique_ptr<save::Document> document=std::make_unique<save::Document>();
    DemolishBuildingOrderReport report;
};
Demolition demolish(const save::Document& source,uint32_t id,const BuildingRemovalContext& context={}) {
    const auto before=bytes(source); Demolition out; save::Error error{save::ErrorCode::Io,4,"old"};
    checked(orderDemolishBuilding(source,{0,id},context,*out.document,out.report,error),error);
    require(error.code==save::ErrorCode::None && error.offset==0 && error.message.empty() && bytes(source)==before,
            "demolition preserves source and clears error");
    auto alias=std::make_unique<save::Document>(source); DemolishBuildingOrderReport aliasReport;
    checked(orderDemolishBuilding(*alias,{0,id},context,*alias,aliasReport,error),error);
    require(bytes(*alias)==bytes(*out.document) && aliasReport==out.report,"in-place demolition is byte/report identical");
    return out;
}
void rejectDemolition(const save::Document& source,DemolishBuildingOrderRequest request,const BuildingRemovalContext& context={}) {
    auto destination=fixture(); const auto before=bytes(source),priorDestination=bytes(*destination);
    DemolishBuildingOrderReport report; report.requestedId=999; report.removedIds={7}; const auto old=report; save::Error error;
    require(!orderDemolishBuilding(source,request,context,*destination,report,error) && error.code!=save::ErrorCode::None && !error.message.empty(),
            "demolition rejects unsafe/unauthorized command explicitly");
    require(bytes(source)==before && bytes(*destination)==priorDestination && report==old,"demolition failure preserves all outputs");
    auto alias=std::make_unique<save::Document>(source);
    require(!orderDemolishBuilding(*alias,request,context,*alias,report,error) && bytes(*alias)==before && report==old,
            "failed in-place demolition preserves document and report");
}
void permissionsRefundsAndShrines() {
    auto d=fixture(); auto id=building(*d,29);
    auto out=demolish(*d,id);
    require(out.report.requestedId==id && out.report.primaryId==id && out.report.territory==1 && out.report.seaFlagsRebuilt &&
            out.report.removals.size()==1 && out.report.removals[0].refundPlayer==0 && out.report.removals[0].credits==37 &&
            out.document->players[0].credits==37 && out.document->players[1].credits==0 &&
            out.report.removals[0].originalRoadsTargetWasSentinel,"local command supplies owner refund and preserves native road quirk");
    rejectDemolition(*d,{1,id}); rejectDemolition(*d,{-1,id}); rejectDemolition(*d,{7,id}); rejectDemolition(*d,{0,999});
    d->players[0].index=2; rejectDemolition(*d,{0,id}); d->players[0].index=0;
    d->players[0].type=3; rejectDemolition(*d,{0,id}); d->players[0].type=1;
    d->territories[0].data.visibility[0]=3; rejectDemolition(*d,{0,id}); d->territories[0].data.visibility[0]=4;
    d->territories[0].data.owner=1; rejectDemolition(*d,{0,id}); // Stale native visibility alone is insufficient policy.
    d=fixture(); id=building(*d,29); d->buildings[0].flags=4; d->buildings[0].cost[0]=13;
    require(demolish(*d,id).report.removals[0].credits==6,"unfinished demolition refunds paid rather than canonical money");
    d=fixture(); id=building(*d,37,14); d->buildings[0].hubLevel=2;
    require(demolish(*d,id).report.removals[0].credits==500,"Council stored hub-level cost reused by command");
    d=fixture(); id=building(*d,46); d->territories[0].data.flags|=0x10u;
    BuildingRemovalContext context; context.pendingShrines.entries.push_back({1,3});
    out=demolish(*d,id,context);
    require(out.report.contextAfter.pendingShrines.entries==std::vector<PendingShrineEntry>({{1,3},{0,1}}) &&
            out.report.removals[0].shrinePenaltyQueued && !(out.document->territories[0].data.flags&0x10u) &&
            out.document->territories[0].data.morale==100 && out.document->scores[0].nukesUsed==0 &&
            out.document->events.empty(),"shrine queues after existing entries; order does not flush penalties or fabricate events");
    context.pendingShrines.entries.assign(kPendingShrineCapacity,{0,1}); rejectDemolition(*d,{0,id},context);
}
void disbandAuthorizationAndDependencies() {
    auto d=fixture(); const auto id=army(*d,2,3,0); const auto before=bytes(*d);
    auto destination=fixture(); ArmyLifecycleReport report; save::Error error{save::ErrorCode::Io,5,"old"};
    checked(orderDisbandUnit(*d,{0,id},*destination,report,error),error);
    require(report.removedIds==std::vector<uint32_t>{id} && report.refunds.size()==1 && report.refunds[0].credits==30 &&
            destination->players[0].credits==30 && destination->territories[2].data.materials[4]==5 &&
            destination->territories[2].data.materials[8]==2 && bytes(*d)==before && error.code==save::ErrorCode::None,
            "own unit on foreign territory can disband; materials go to its CURRENT territory");
    auto alias=std::make_unique<save::Document>(*d); ArmyLifecycleReport aliasReport;
    checked(orderDisbandUnit(*alias,{0,id},*alias,aliasReport,error),error);
    require(bytes(*alias)==bytes(*destination) && aliasReport==report,"disband aliases exactly");
    const auto output=bytes(*destination); const auto old=report;
    for (int actor:{-1,1,7}) require(!orderDisbandUnit(*d,{actor,id},*destination,report,error) && report==old && bytes(*destination)==output,
                                     "disband authority error is transactional");
    d=fixture(); const auto foreign=army(*d,1,1,1);
    require(!orderDisbandUnit(*d,{0,foreign},*destination,report,error) && report==old,"cannot disband another owner's unit");
    d=fixture(); const auto jobUnit=army(*d); d->armies[0].job=1; d->jobs[0][0].armyIds[0]=uint16_t(jobUnit);
    const auto jobBytes=bytes(*d);
    checked(orderDisbandUnit(*d,{0,jobUnit},*destination,report,error),error);
    require(report.removedIds==std::vector<uint32_t>{jobUnit} && destination->armies.empty() &&
            destination->jobs[0][0].armyIds[0]==jobUnit && destination->armyPool->jobSlots[0][0][0]!=0 &&
            !taskForceTarget(*destination,0,0,0) && bytes(*d)==jobBytes,
            "UI disband succeeds and leaves the taskforce bound to the freed cell for explicit cleanup");
    checked(save::validate(*destination,error),error);
    std::vector<uint8_t> denied{9,8};
    require(!save::encode(*destination,denied,error) && denied==std::vector<uint8_t>({9,8}),
            "UI disband cannot export deferred dangling bindings as file IDs");
    d->armies[0].job=0; d->jobs[0][0].armyIds[0]=0;
    d->ministerJobs[0][0].type=13; d->ministerJobs[0][0].param[0]=int32_t(jobUnit);
    checked(orderDisbandUnit(*d,{0,jobUnit},*destination,report,error),error);
    require(report.deferredMaintainJobs==1 && destination->ministerJobs[0][0].param[0]==int32_t(jobUnit),
            "native deferred maintain-unit reference is not eagerly pruned by command");
    d=fixture(); const auto carrier=army(*d,12,2,0); const auto passenger=army(*d,1,2,1);
    d->armies[0].cargo[0].raw=passenger; d->armies[1].cargo[0].raw=carrier;
    checked(orderDisbandUnit(*d,{0,carrier},*destination,report,error),error);
    require(report.removedIds==std::vector<uint32_t>({passenger,carrier}) && report.refunds.size()==1 &&
            destination->players[0].credits==25 && destination->players[1].credits==0,"carrier command cascades mixed-owner cargo without child refund");
}
struct PlatformFixture {
    std::unique_ptr<save::Document> document;
    uint32_t platform=0,hab=0,survivor=0;
    std::vector<uint32_t> retirement;
};
PlatformFixture platformFixture() {
    PlatformFixture f; f.document=fixture(); f.survivor=building(*f.document,29);
    save::Error error; BuildingCreationReport created;
    checked(createCompletedBuilding(*f.document,{2,38,25},*f.document,created,error),error);
    f.platform=created.buildingId; f.hab=created.companionBuildingId;
    for (int site:{3,17,13,27}) {
        checked(createCompletedBuilding(*f.document,{2,19,site},*f.document,created,error),error);
        f.retirement.push_back(created.buildingId);
    }
    f.retirement.push_back(f.hab); f.retirement.push_back(f.platform); return f;
}
void platformOrderAndRollback() {
    auto f=platformFixture(); auto out=demolish(*f.document,f.hab);
    require(out.report.platformRedirected && out.report.primaryId==f.platform && out.report.removedIds==f.retirement &&
            out.report.removals.size()==6 && out.document->buildings.size()==1 && out.document->buildingById(f.survivor),
            "SeaHab selection redirects; socket deletion order is -22,-8,-12,+2,-10 then platform");
    for (const auto& cell:out.document->territories[1].data.sites)
        require(cell.building.raw==0 && (cell.terrainFlags&0xff00u)==0,"platform order clears each child and complete footprint");
    auto direct=demolish(*f.document,f.platform);
    require(!direct.report.platformRedirected && direct.report.removedIds==f.retirement && bytes(*direct.document)==bytes(*out.document),
            "direct platform selection has same complete native cascade");
    auto bare=fixture(); BuildingCreationReport created; save::Error error;
    checked(createCompletedBuilding(*bare,{2,38,25},*bare,created,error),error);
    require(demolish(*bare,created.buildingId).report.removedIds==std::vector<uint32_t>({created.companionBuildingId,created.buildingId}),
            "free sockets resolve back to platform and are skipped dynamically");
    bare=fixture(); const auto orphan=building(*bare,39,15,2); bare->buildings[0].task[1]=20;
    rejectDemolition(*bare,{0,orphan});
    // Late error after all six candidate removals/refunds: an unrelated marine
    // generator tries to read a territory not represented by this document.
    building(*f.document,43,1,1); f.document->territories[0].data.adjacency[0]=uint16_t(1u<<7);
    rejectDemolition(*f.document,{0,f.hab});
}
void marineFlagOracles() {
    auto d=fixture(); const auto id=building(*d,29);
    building(*d,43,0,2); building(*d,43,1,2); building(*d,44,2,2);
    d->territories[1].data.adjacency[0]=uint16_t(1u<<3);
    d->territories[2].data.adjacency[0]=uint16_t(1u<<2);
    for (auto& t:d->territories) std::fill_n(t.data.unk_8b0+(0x994-0x8b0),6,uint8_t(0xa5));
    auto out=demolish(*d,id);
    require(sea(*out.document,1)==std::array<uint8_t,6>{} &&
            sea(*out.document,2)==std::array<uint8_t,6>{40,50,25,126,1,0} &&
            sea(*out.document,3)==std::array<uint8_t,6>{0,0,25,0,1,0} && out.report.seaChanges.size()==3,
            "marine flags clear globally then add25 cap50, protection40 and enemy mask without random flooding");
    d->options.allowAlliances=1; d->players[0].relations[1]=0x80000000u;
    out=demolish(*d,id);
    require(sea(*out.document,2)==std::array<uint8_t,6>{40,50,25,124,1,0} &&
            sea(*out.document,3)==std::array<uint8_t,6>{40,0,25,124,1,0},"ANY nonzero relation counts, not pact4 or alliance16");
    army(*d,12,2,0); // Sea DOMAIN2, stored class4: deliberately distinguish them.
    army(*d,11,3,1); // Air DOMAIN3, foreign ally protects weather effect.
    out=demolish(*d,id);
    require(sea(*out.document,2)==std::array<uint8_t,6>{40,0,25,124,1,0} &&
            sea(*out.document,3)==std::array<uint8_t,6>{40,0,0,124,0,0},"protection uses canonical movement DOMAIN and both owning lists");
    d->armies.clear(); d->territories[1].data.armies.raw=0; d->territories[2].data.armies.raw=0;
    army(*d,27,2,0); // Special AAV DOMAIN6 also blocks tidal effects.
    require(sea(*demolish(*d,id).document,2)[1]==0,"AAV27 is an explicit additional tidal blocker");
    d->armies.clear(); d->territories[1].data.armies.raw=0;
    d->territories[2].data.owner=-1;
    require(sea(*demolish(*d,id).document,3)[0]==0,"neutral owner reads actual zero minister tail with alliances enabled");
    d->players[0].ministers[5].unk_12[0x44]=1;
    require(sea(*demolish(*d,id).document,3)[0]==40,"native relation[-1] aliases Player+276 data, not inferred false");
    d->buildings[1].flags=0; d->buildings[2].turnsLeft=1; d->buildings[3].turnsLeft=-1;
    d->buildings[3].flags=4; d->buildings[3].category=18; // Canonical category16 still selects it.
    out=demolish(*d,id);
    require(sea(*out.document,2)==std::array<uint8_t,6>{40,0,25,124,1,0},"active, signed work<=0, canonical category; Built is not required");
    d->territories[1].data.adjacency[0]|=1; rejectDemolition(*d,{0,id});
    d->territories[1].data.adjacency[0]&=uint16_t(0xfffeu);
    d->territories[2].data.owner=7; rejectDemolition(*d,{0,id});
    // Codec validation is the canonical type-table guard even for unrelated
    // buildings reached by the global marine rebuild, not only the selection.
    d=fixture(); const auto selected=building(*d,29); building(*d,43,0,2);
    const auto validBytes=bytes(*d); d->buildings.back().type=255;
    auto destination=fixture(); const auto priorDestination=bytes(*destination);
    DemolishBuildingOrderReport report; report.primaryId=888; const auto priorReport=report; save::Error error;
    require(!orderDemolishBuilding(*d,{0,selected},{},*destination,report,error) &&
            error.code==save::ErrorCode::InvalidState && d->buildings.back().type==255 &&
            report==priorReport && bytes(*destination)==priorDestination,"unrelated active type255 is rejected before table access or output publication");
    d->buildings.back().type=43;
    require(bytes(*d)==validBytes,"invalid unrelated type rejection leaves every input byte unchanged");
}
void runtimeOrders() {
    auto f=platformFixture(); const auto unit=army(*f.document);
    runtime::State state,foreign; save::Error error;
    checked(state.prepare(*f.document,error),error); checked(foreign.prepare(*f.document,error),error);
    const auto platform=state.buildingById(f.platform),hab=state.buildingById(f.hab),survivor=state.buildingById(f.survivor);
    const auto ownedUnit=state.armyById(unit); const auto rng=state.sessionRng();
    DemolishBuildingOrderReport report; report.requestedId=999; const auto old=report;
    const auto* pointer=state.document(); const auto before=bytes(*pointer);
    require(!state.orderDemolishBuilding(1,hab,{},report,error) && state.document()==pointer && bytes(*state.document())==before && report==old,
            "runtime unauthorized order keeps handles, pointer, bytes and report");
    require(!state.orderDemolishBuilding(0,foreign.buildingById(f.hab),{},report,error) && state.document()==pointer,
            "runtime foreign handle cannot acquire authority by matching file ID");
    BuildingRemovalContext context; context.pendingShrines.entries={{0,1}};
    checked(state.orderDemolishBuilding(0,hab,context,report,error),error);
    require(!state.building(platform) && !state.building(hab) && state.building(survivor) && state.army(ownedUnit) &&
            report.removedIds==f.retirement && state.buildingRemovalContext() && *state.buildingRemovalContext()==context &&
            state.stage()==runtime::Stage::EntitiesEdited && state.sessionRng()==rng,"runtime cascades retire lifetimes but preserve survivors/context/RNG");
    const auto after=bytes(*state.document()); const auto saved=report;
    require(!state.orderDemolishBuilding(0,hab,context,report,error) && report==saved && bytes(*state.document())==after,"stale handle rollback");
    require(!state.orderDemolishBuilding(0,survivor,{},report,error) && report==saved && bytes(*state.document())==after,
            "owned shrine continuation cannot be rewound by a later command");
    ArmyLifecycleReport unitReport;
    checked(state.orderDisbandUnit(0,ownedUnit,unitReport,error),error);
    require(!state.army(ownedUnit) && state.building(survivor) && *state.buildingRemovalContext()==context,
            "unit order preserves independently owned shrine continuation");
    BuildingLifecycleReport lowLevel;
    checked(state.removeBuilding(survivor,BuildingRemovalKind::DeleteBuilding,-1,lowLevel,error),error);
    require(*state.buildingRemovalContext()==context,"context-free low-level edit does not discard prior sidecar");
    auto captured=fixture(); const auto capturedBefore=bytes(*captured);
    require(!state.capture(*captured,error) && bytes(*captured)==capturedBefore && !state.advanceTurn(error),"orders do not make partial state exportable/playable");
    checked(state.prepare(*f.document,error),error);
    require(!state.buildingRemovalContext() && !state.army(ownedUnit) && !state.building(survivor),"reprepare resets continuation and invalidates prior identities");
}
void runtimeCollectiveDemolition() {
    auto d=fixture();
    const auto later=building(*d,29,35),first=building(*d,29,0);
    const auto shrine=building(*d,46,14),foreign=building(*d,29,0,3);
    const auto unit=army(*d); const auto input=bytes(*d);
    runtime::State state; save::Error error; checked(state.prepare(*d,error),error);
    const auto firstHandle=state.buildingById(first),laterHandle=state.buildingById(later);
    const auto shrineHandle=state.buildingById(shrine),foreignHandle=state.buildingById(foreign);
    const auto unitHandle=state.armyById(unit);
    const auto territoryHandle=state.territoryByIndex(1);
    const auto rng=state.sessionRng();
    BuildingRemovalContext context; context.pendingShrines.entries={{1,3}};
    context.campaignProgress={11,22,33};
    DemolishColonyOrderReport report;
    checked(state.orderDemolishColony({0,1},context,report,error),error);
    require(report.removedIds==std::vector<uint32_t>({first,later}) &&
            !state.building(firstHandle) && !state.building(laterHandle) &&
            state.building(shrineHandle) && state.building(foreignHandle) && state.army(unitHandle) &&
            state.territoryByIndex(1)==territoryHandle &&
            state.graph().territories[0].sites[14]==shrineHandle &&
            !state.graph().territories[0].sites[0] && !state.graph().territories[0].sites[35],
            "collective order must retire only site-ordered eligible lifetimes and rebuild graph");
    require(state.stage()==runtime::Stage::EntitiesEdited && state.sessionRng()==rng &&
            *state.buildingRemovalContext()==context && report.contextAfter==context && bytes(*d)==input,
            "collective order lost continuation, RNG or source isolation");
    const auto after=bytes(*state.document()); const auto* pointer=state.document(); const auto saved=report;
    require(!state.orderDemolishColony({0,1},{},report,error) && report==saved &&
            state.document()==pointer && bytes(*state.document())==after && state.building(shrineHandle),
            "collective order must reject a rewound continuation even when no buildings are eligible");
    require(!state.orderDemolishColony({0,3},context,report,error) && report==saved &&
            state.document()==pointer && bytes(*state.document())==after,
            "collective authority rejection must keep graph, document and report");
    checked(state.orderDemolishColony({0,1},report.contextAfter,report,error),error);
    require(report.removedIds.empty() && bytes(*state.document())==after &&
            report.contextAfter==context && state.building(shrineHandle) && state.building(foreignHandle),
            "empty collective repeat must preserve survivor identities and aliased context");
    auto captured=fixture(); const auto oldCapture=bytes(*captured);
    require(!state.capture(*captured,error) && bytes(*captured)==oldCapture && !state.advanceTurn(error),
            "collective order must not activate export or a partial turn");
}
} // namespace
int main() {
    try {
        std::vector<uint8_t> globalState(sizeof(dl2::gs)),globalMisc(sizeof(dl2::gg));
        std::memcpy(globalState.data(),&dl2::gs,sizeof(dl2::gs)); std::memcpy(globalMisc.data(),&dl2::gg,sizeof(dl2::gg));
        const auto seed=dl2::rtl::seed(),seedHi=dl2::rtl::seedHi();
        permissionsRefundsAndShrines(); disbandAuthorizationAndDependencies(); platformOrderAndRollback(); marineFlagOracles(); runtimeOrders(); runtimeCollectiveDemolition();
        require(std::memcmp(globalState.data(),&dl2::gs,sizeof(dl2::gs))==0 && std::memcmp(globalMisc.data(),&dl2::gg,sizeof(dl2::gg))==0 &&
                dl2::rtl::seed()==seed && dl2::rtl::seedHi()==seedHi,"all orders preserve global state and both RNG words");
        std::cout<<"entity_orders: authority, native refunds/cascades/marine flags, shrine continuation and rollback passed\n"; return 0;
    } catch (const std::exception& e) { std::cerr<<"entity_orders: "<<e.what()<<'\n'; return 1; }
}
