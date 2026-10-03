// Oracles from0044cefc/00450320/0044b8f8, not a replay of a native turn.
#include "game/entity_lifecycle.h"
#include "game/data_tables.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include "game/runtime_state.h"
#include <cstring>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <utility>

namespace {
using namespace dl2;
using namespace dl2::simulation;
constexpr auto demolish=BuildingRemovalKind::DemolishBuilding;
constexpr auto erase=BuildingRemovalKind::DeleteBuilding;
void check(bool value,const char* message) { if(!value) throw std::runtime_error(message); }
void ok(bool value,const save::Error& error) { if(!value) throw std::runtime_error(error.message); }
template<class T> void append(std::vector<uint8_t>& bytes,const T& value) {
    static_assert(std::is_trivially_copyable_v<T>);
    const auto* p=reinterpret_cast<const uint8_t*>(&value); bytes.insert(bytes.end(),p,p+sizeof(value));
}
std::vector<uint8_t> bytes(const save::Document& d) {
    std::vector<uint8_t> result; save::Error e; ok(save::encode(d,result,e),e);
    for(const auto& t:d.territories) append(result,t.data);
    for(const auto& b:d.buildings) append(result,b);
    append(result,d.jobs); return result;
}
std::unique_ptr<save::Document> fixture() {
    auto d=std::make_unique<save::Document>();
    std::memcpy(d->header.text,save::kHeaderText,sizeof(save::kHeaderText)); d->header.version=kSaveVersion;
    d->options.numPlayers=2; d->options.localPlayer=0; d->options.turn=73; d->options.nextGlobalId=900;
    d->world.width=2; d->world.height=1; d->world.numTerritories=2; d->world.rngSeed=193;
    d->territories.resize(2); d->tiles.resize(2); d->buildings.reserve(16);
    for(size_t p=0;p<7;++p) {
        auto& player=d->players[p]; player.index=uint8_t(p); player.type=p?3:1; player.race=2; player.credits=1000;
        d->ministerJobs[p].resize(1); d->ministerJobs[p][0].type=1;
        for(auto& job:d->jobs[p]) job.owner=int16_t(p);
        for(auto& row:d->raceStats.v) row[p]=100;
        d->raceStats.v[27][p]=0; // Fixed80 racial morale branch for the economic-continuation test.
    }
    for(size_t i=0;i<2;++i) {
        auto& t=d->territories[i].data; t.index=uint16_t(i+1); t.owner=0; t.terrain=1;
        t.population=300; t.morale=100; t.knowledge=100; t.flags=0xa000001f; t.numTiles=1;
        t.tiles[0].raw=uint32_t(i); t.production[2]=29; t.consumption[3]=-17;
        std::memcpy(t.name,i?"Beta":"Alpha",i?5:6);
        for(int m=1;m<11;++m) t.materials[m]=1000;
        for(int s=0;s<36;++s) {
            t.sites[s].unk_00=uint16_t(s%6+256*(s/6)); t.sites[s].terrainFlags=0x4a01;
            t.sites[s].unk_05[11]=0xa5;
        }
        d->tiles[i].x=uint8_t(i); d->tiles[i].territory=int16_t(i+1); d->tiles[i].terrain=1;
    }
    d->scores[0].nukesUsed=17; d->scores[1].nukesUsed=251; d->trailing={0xa5,0,0xff};
    return d;
}
uint32_t add(save::Document& d,int type,int site=14,int territory=1) {
    Building b{}; b.id=uint16_t(200+d.buildings.size()); b.type=uint8_t(type);
    b.category=data::kBuildingTypes[type].category; b.flags=6; b.race=2; b.site=int8_t(site); b.territory=int16_t(territory);
    if(type==2) { b.task[1]=20; b.labor[1]=3; }
    if(!d.buildings.empty()) { b.prev.raw=d.buildings.back().id; d.buildings.back().next.raw=b.id; }
    d.territories[size_t(territory-1)].data.sites[site].building.raw=b.id; d.buildings.push_back(b); return b.id;
}
Building& mutableBuilding(save::Document& d,uint32_t id) {
    for(auto& b:d.buildings) if(b.id==id) return b;
    throw std::runtime_error("fixture building absent");
}
struct Result { std::unique_ptr<save::Document> d=std::make_unique<save::Document>(); BuildingLifecycleReport report; };
Result run(const save::Document& source,BuildingRemovalRequest request,const BuildingRemovalContext& context) {
    const auto before=bytes(source); const auto oldContext=context; Result out;
    save::Error e{save::ErrorCode::Io,9,"stale"}; ok(removeBuilding(source,request,context,*out.d,out.report,e),e);
    check(bytes(source)==before && context==oldContext,"demolition never mutates source or borrowed live context");
    check(e.code==save::ErrorCode::None && !e.offset && e.message.empty(),"success clears stale error");
    auto alias=std::make_unique<save::Document>(source); BuildingLifecycleReport r;
    ok(removeBuilding(*alias,request,context,*alias,r,e),e);
    check(bytes(*alias)==bytes(*out.d) && r==out.report,"in-place and separate demolition agree"); return out;
}
void rejected(const save::Document& source,BuildingRemovalRequest request,const BuildingRemovalContext& context,
              save::ErrorCode code=save::ErrorCode::InvalidState) {
    auto dest=fixture(); const auto input=bytes(source),before=bytes(*dest); const auto oldContext=context;
    BuildingLifecycleReport r; r.primaryId=999; r.removedIds={5}; r.contextAfter=BuildingRemovalContext{};
    r.contextAfter->campaignProgress[2]=91; const auto old=r; save::Error e;
    check(!removeBuilding(source,request,context,*dest,r,e) && e.code==code && !e.message.empty(),"unsafe demolition domain fails explicitly");
    check(bytes(source)==input && bytes(*dest)==before && r==old && context==oldContext,"failure rolls back documents/report/pending queue");
    auto alias=std::make_unique<save::Document>(source);
    check(!removeBuilding(*alias,request,context,*alias,r,e) && bytes(*alias)==input && r==old,"in-place failure also rolls back");
}
void ordinaryAndDeferred() {
    for(int type:{45,46,47}) {
        auto d=fixture(); const auto shrine=add(*d,type); const auto house=add(*d,2,35);
        d->players[1].index=4; // Preserve physical Player*, NOT its current index or the territory owner.
        BuildingRemovalContext c; c.pendingShrines.entries={{6,2},{1,1}};
        auto out=run(*d,{shrine,demolish,1},c); const auto& r=out.report;
        check(r.shrineFlagCleared && r.shrinePenaltyQueued && !r.campaignProtected && r.contextAfter &&
              r.contextAfter->pendingShrines.entries==std::vector<PendingShrineEntry>({{6,2},{1,1},{1,1}}),
              "shrine demolition appends ordered duplicate physical player/territory references");
        const int refund=type==45?250:150;
        check(r.credits==refund && out.d->players[1].credits==1000+refund && out.d->players[0].credits==1000 &&
              out.d->players[4].credits==1000 && r.refundPlayer==1,"canonical half-cost refund follows explicit player slot");
        check(out.d->territories[0].data.flags==(d->territories[0].data.flags&~uint32_t(0x10)) &&
              out.d->territories[0].data.morale==100 && out.d->territories[1].data.morale==100 &&
              std::memcmp(&out.d->scores,&d->scores,sizeof(d->scores))==0 && out.d->events.empty(),
              "only shrine flag clears now: no premature morale, score or event penalty");
        check(!out.d->buildingById(shrine) && out.d->buildingById(house)->prev.raw==0 &&
              out.d->territories[0].data.sites[14].building.raw==0 && r.removedIds==std::vector<uint32_t>{shrine} &&
              r.localLaborBalanced && r.originalRoadsTargetWasSentinel,"existing deletion/unlink/local balance/sentinel roads remain real");
        for(int site:{14,15,8,9}) {
            if(type==45 || site==14) check(out.d->territories[0].data.sites[site].terrainFlags==1,"shrine footprint high byte clears");
            check(out.d->territories[0].data.sites[site].unk_05[11]==0xa5,"demolition does not invent a local road rebuild");
        }
        check(std::memcmp(&out.d->territories[1].data,&d->territories[1].data,sizeof(Territory))==0 &&
              out.d->options.nextGlobalId==900 && out.d->options.turn==73,"other colony, allocation counter and turn stay unchanged");
    }
    auto d=fixture(); const auto id=add(*d,46); auto& b=mutableBuilding(*d,id); b.flags=4; b.cost[0]=75; b.cost[1]=9;
    auto out=run(*d,{id,demolish,0},{});
    check(out.report.credits==37 && out.report.materials[0]==4 && out.d->territories[0].data.materials[1]==1004,
          "uncovered shrine refunds paid costs, not canonical costs");
    // The OLD no-context API must not silently assume an empty live queue/campaign.
    auto dest=fixture(); const auto before=bytes(*dest); BuildingLifecycleReport r; r.primaryId=123; const auto prior=r; save::Error e;
    check(!removeBuilding(*d,{id,demolish,0},*dest,r,e) && bytes(*dest)==before && r==prior,"old API still refuses shrine demolition without context");
    ok(removeBuilding(*d,{id,erase,-1},*dest,r,e),e);
    check(!r.contextAfter && dest->territories[0].data.flags==d->territories[0].data.flags,"bare Delete remains context-free and does not clear shrine flag");
    BuildingRemovalContext c; c.pendingShrines.entries={{2,1}}; c.campaignFlags=1u<<12;
    out=run(*d,{id,erase,-1},c);
    check(out.report.contextAfter==c && !out.report.shrinePenaltyQueued && !out.report.shrineFlagCleared && !out.report.localLaborBalanced,
          "explicit-context Delete does not query campaign or enqueue demolition effects");
    d=fixture(); const auto ordinary=add(*d,9); out=run(*d,{ordinary,demolish,0},c);
    check(out.report.contextAfter==c && !out.report.shrineFlagCleared,"non-shrine does not evaluate an irrelevant goal12 mask");
    ok(removeBuilding(*d,{ordinary,demolish,0},*dest,r,e),e); check(!r.contextAfter,"old ordinary demolition remains source compatible");
    // Original branch tests STORED category+05, not canonical type/category.
    d=fixture(); const auto disguised=add(*d,9); mutableBuilding(*d,disguised).category=11;
    out=run(*d,{disguised,demolish,0},{}); check(out.report.shrinePenaltyQueued,"stored category11 activates shrine side effects");
    d=fixture(); const auto hidden=add(*d,46); mutableBuilding(*d,hidden).category=1;
    ok(removeBuilding(*d,{hidden,demolish,0},*dest,r,e),e);
    check(!r.shrineFlagCleared && dest->territories[0].data.flags==d->territories[0].data.flags,"canonical shrine type alone does not activate category11 branch");
}
void campaignAndCapacity() {
    check(data::kCampaigns[36].goals[0].type==12,"canonical campaign36 goal0 is the protected-shrine goal");
    auto d=fixture(); const auto id=add(*d,46); d->options.campaign=36;
    BuildingRemovalContext c; c.campaignFlags=1u<<12; c.pendingShrines.entries={{0,2}};
    for(int32_t live:{1,-1,std::numeric_limits<int32_t>::min(),std::numeric_limits<int32_t>::max()}) {
        c.campaignProgress[0]=live; d->options.campaignBytes[0]=0;
        auto out=run(*d,{id,demolish,0},c);
        check(out.report.campaignProtected && !out.report.shrinePenaltyQueued && out.report.shrineFlagCleared && out.report.contextAfter==c &&
              out.report.credits==150 && !out.d->buildingById(id) && !(out.d->territories[0].data.flags&0x10),
              "any nonzero LIVE goal state protects queue only; flag clear/refund/delete still happen");
    }
    c.campaignProgress[0]=0; c.campaignProgress[1]=1; d->options.campaignBytes[0]=1;
    auto out=run(*d,{id,demolish,0},c);
    check(!out.report.campaignProtected && out.report.shrinePenaltyQueued && out.report.contextAfter->campaignProgress==c.campaignProgress &&
          out.d->options.campaignBytes[0]==1,"saved progress byte and other live goal slots are not inferred or rewritten");
    c.campaignFlags=0; c.campaignProgress[0]=1; out=run(*d,{id,demolish,0},c);
    check(out.report.shrinePenaltyQueued,"nonzero live goal alone is insufficient without live flag12");
    c.campaignFlags=1u<<12;
    for(int campaign:{-1,0,35,42,43}) { d->options.campaign=campaign; rejected(*d,{id,demolish,0},c); }
    d->options.campaign=36; c.campaignProgress[0]=0; c.pendingShrines.entries.assign(9,{6,2});
    out=run(*d,{id,demolish,0},c);
    check(out.report.contextAfter->pendingShrines.entries.size()==10 && out.report.contextAfter->pendingShrines.entries.back()==PendingShrineEntry{0,1},
          "ninth pending entry permits the tenth, without deduplication or numPlayers clipping");
    c.pendingShrines.entries.assign(10,{6,2}); rejected(*d,{id,demolish,0},c,save::ErrorCode::Limit);
    c.campaignProgress[0]=1; out=run(*d,{id,demolish,0},c);
    check(out.report.contextAfter==c && out.report.campaignProtected,"full queue still permits protected demolition because nothing appends");
    c.pendingShrines.entries.push_back({0,1}); rejected(*d,{id,demolish,0},c,save::ErrorCode::Limit);
    for(const auto invalid:std::vector<PendingShrineEntry>{{-1,1},{7,1},{0,0},{0,3}}) {
        c.pendingShrines.entries={invalid}; rejected(*d,{id,demolish,0},c);
    }
    c={}; rejected(*d,{id,demolish,-1},c); rejected(*d,{id,demolish,7},c); rejected(*d,{99999,demolish,0},c);
    // A genuine late BalanceLabor error follows the candidate's queue/refund/delete.
    d=fixture(); const auto shrine=add(*d,46); add(*d,1,35); // Housing has no task: original fallback would write slot-1.
    rejected(*d,{shrine,demolish,0},{});
}
void contextAliasing() {
    auto d=fixture(); const auto id=add(*d,46); BuildingRemovalContext c; c.pendingShrines.entries={{1,2}};
    auto expected=run(*d,{id,demolish,0},c); BuildingLifecycleReport r; r.contextAfter=c; save::Error e;
    ok(removeBuilding(*d,{id,demolish,0},*r.contextAfter,*d,r,e),e);
    check(r==expected.report && bytes(*d)==bytes(*expected.d),"source/destination AND report-owned input context may alias safely");
}
void runtimeContinuation() {
    auto d=fixture(); const auto first=add(*d,46); const auto second=add(*d,47,24); const auto house=add(*d,2,35);
    const auto untouched=bytes(*d); runtime::State s; save::Error e; ok(s.prepare(*d,e),e);
    const auto firstHandle=s.buildingById(first),secondHandle=s.buildingById(second),houseHandle=s.buildingById(house);
    const auto territory=s.territoryByIndex(1); const auto rng=s.sessionRng(); BuildingRemovalContext c; BuildingLifecycleReport r;
    ok(s.removeBuilding(firstHandle,demolish,0,c,r,e),e);
    check(s.buildingRemovalContext() && *s.buildingRemovalContext()==*r.contextAfter && !s.building(firstHandle) &&
          s.building(secondHandle) && s.building(houseHandle) && s.territory(territory) && s.stage()==runtime::Stage::EntitiesEdited,
          "runtime owns pending continuation and invalidates only demolished handle");
    const auto prior=r; const auto after=bytes(*s.document());
    check(!s.removeBuilding(secondHandle,demolish,0,c,r,e) && r==prior && bytes(*s.document())==after &&
          *s.buildingRemovalContext()==*prior.contextAfter && s.building(secondHandle),"stale empty context cannot rewind pending queue");
    check(!s.removeBuilding(firstHandle,demolish,0,*s.buildingRemovalContext(),r,e) && r==prior && bytes(*s.document())==after,
          "stale building handle rollback also preserves pending context");
    // Borrow context directly from State: internal candidate-copy must not invalidate it early.
    ok(s.removeBuilding(secondHandle,demolish,0,*s.buildingRemovalContext(),r,e),e);
    const auto continued=*s.buildingRemovalContext();
    check(continued.pendingShrines.entries==std::vector<PendingShrineEntry>({{0,1},{0,1}}) && !s.building(secondHandle) &&
          s.building(houseHandle) && s.sessionRng()==rng,"two demolitions continue ordered duplicate penalties without drawing RNG");
    BuildingControlReport order; ok(s.controlBuilding({0,house,BuildingControl::ToggleTaskLock,1},order,e),e);
    check(order.accepted && *s.buildingRemovalContext()==continued && s.building(houseHandle),"ordinary economic order/internal copy retains pending queue");
    auto output=fixture(); const auto oldOutput=bytes(*output);
    check(!s.capture(*output,e) && bytes(*output)==oldOutput && !s.advanceTurn(e),"partial lifecycle cannot export or claim a complete turn");
    auto bad=std::make_unique<save::Document>(*d); bad->world.width=0; const auto beforeFailedPrepare=bytes(*s.document());
    check(!s.prepare(*bad,e) && bytes(*s.document())==beforeFailedPrepare && *s.buildingRemovalContext()==continued && s.building(houseHandle),
          "failed prepare preserves both handles and shrine continuation");
    runtime::State moved(std::move(s));
    check(!s.document() && !s.buildingRemovalContext() && moved.building(houseHandle) && *moved.buildingRemovalContext()==continued,
          "move transfers pending context and live handles; source is empty");
    runtime::State destination; ok(destination.prepare(*d,e),e); const auto obsolete=destination.buildingById(house);
    destination=std::move(moved);
    check(!destination.building(obsolete) && destination.building(houseHandle) && !moved.buildingRemovalContext() &&
          *destination.buildingRemovalContext()==continued,"move assignment retires former destination handles, preserves transferred continuation");
    // Entire economic sequence must not flush penalties early (0044b9e4 is a later turn step).
    EconomicPhaseContext economic; SessionRng seeded; ok(seeded.initialize(123,e),e);
    economic.effects.events.rngBeforeEvents=economic.effects.ai.rng=economic.effects.log.rngAfterEvents=seeded.snapshot();
    const auto beforePhase=bytes(*destination.document());
    const auto* beforePointer=destination.document(); const auto beforeRng=destination.sessionRng();
    auto phase=std::make_unique<EconomicPhaseReport>();
    phase->completed={EconomicStep::FinalBalance}; phase->growth.territories.resize(2);
    economic.campaignFlags=1u<<4;
    check(!destination.runEconomicPhase(economic,*phase,e) && phase->completed==std::vector<EconomicStep>{EconomicStep::FinalBalance} &&
          phase->growth.territories.size()==2 &&
          destination.document()==beforePointer && bytes(*destination.document())==beforePhase &&
          *destination.buildingRemovalContext()==continued && destination.sessionRng()==beforeRng && destination.building(houseHandle),
          "economic phase cannot disagree with already-owned live campaign flags");
    ResearchOrderReport research; research.technology=999; const auto oldResearch=research;
    check(!destination.orderResearch({0,ResearchOrderKind::ClearQueue,0},{1u<<4,0},research,e) && research==oldResearch &&
          bytes(*destination.document())==beforePhase && *destination.buildingRemovalContext()==continued,
          "research order cannot override already-owned live campaign flags");
    economic.campaignFlags=continued.campaignFlags;
    ok(destination.runEconomicPhase(economic,*phase,e),e);
    check(*destination.buildingRemovalContext()==continued && destination.building(houseHandle) &&
          destination.document()->scores[0].nukesUsed==17 && destination.stage()==runtime::Stage::EconomyPhaseApplied,
          "economic phase preserves pending penalties without premature score update or queue drain");
    ok(destination.prepare(*d,e),e);
    check(!destination.buildingRemovalContext() && !destination.building(houseHandle) && destination.stage()==runtime::Stage::Prepared &&
          bytes(*d)==untouched,"successful prepare resets transient queue, invalidates old handles and leaves original source exact");
}
} // namespace
int main() {
    try {
        std::vector<uint8_t> globalState,globalMisc; append(globalState,gs); append(globalMisc,gg);
        const auto seed=rtl::seed(),seedHi=rtl::seedHi();
        ordinaryAndDeferred(); campaignAndCapacity(); contextAliasing(); runtimeContinuation();
        check(std::memcmp(globalState.data(),&gs,sizeof(gs))==0 && std::memcmp(globalMisc.data(),&gg,sizeof(gg))==0 &&
              rtl::seed()==seed && rtl::seedHi()==seedHi,"owned shrine demolition never touches legacy globals or RNG words");
        std::cout<<"shrine_demolition: live campaign, pending capacity, refunds, rollback and runtime continuation passed\n"; return 0;
    } catch(const std::exception& e) { std::cerr<<"shrine_demolition: "<<e.what()<<'\n'; return 1; }
}
