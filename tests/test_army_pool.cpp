// Oracles derived from LoadArmies/AllocArmy/FreeArmy and0040aebc assembly.
// No claim of an observed original-game replay; all fixtures are owned copies.
#include "game/army_pool.h"
#include "game/entity_lifecycle.h"
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
#include <vector>

namespace {
using namespace dl2;
using namespace dl2::simulation;
void check(bool value,const char* why) { if(!value) throw std::runtime_error(why); }
void ok(bool value,const save::Error& e) { if(!value) throw std::runtime_error(e.message); }
std::unique_ptr<save::Document> fixture() {
    auto d=std::make_unique<save::Document>();
    std::memcpy(d->header.text,save::kHeaderText,sizeof(save::kHeaderText)); d->header.version=kSaveVersion;
    d->options.numPlayers=2; d->options.localPlayer=0; d->options.nextGlobalId=1000;
    d->world.width=1; d->world.height=1; d->world.numTerritories=1; d->territories.resize(1); d->tiles.resize(1);
    auto& t=d->territories[0].data; t.index=1; t.owner=0; t.terrain=1; t.population=500; t.morale=100;
    for(int p=0;p<kMaxPlayers;++p) {
        d->players[size_t(p)].index=uint8_t(p); d->players[size_t(p)].type=p?3:1; d->players[size_t(p)].race=2;
        d->ministerJobs[size_t(p)].resize(1); d->ministerJobs[size_t(p)][0].type=1;
        for(auto& job:d->jobs[size_t(p)]) job.owner=int16_t(p);
        for(auto& row:d->raceStats.v) row[p]=100;
    }
    d->trailing={0,128,255}; return d;
}
void append(save::Document& d,uint16_t id,int owner=0) {
    Army a{}; a.id=id; a.type=1; a.unitClass=1; a.owner=int8_t(owner); a.health=100;
    a.territory.raw=a.dest.raw=a.origin.raw=1; std::memcpy(a.name,"Pool unit",10);
    auto& t=d.territories[0].data; auto& head=owner==t.owner?t.armies:t.foreignArmies;
    a.next.raw=head.raw;
    for(auto& prior:d.armies) if(prior.id==head.raw) prior.prev.raw=id;
    head.raw=id; d.armies.push_back(a);
}
void bind(save::Document& d,int p,int j,int k,uint16_t id) {
    d.jobs[size_t(p)][size_t(j)].armyIds[k]=id;
    d.jobs[size_t(p)][size_t(j)].armies[k].raw=0xde000000u+id; // Opaque historical bits, not a pointer.
}
std::vector<uint8_t> archive(const save::Document& d) {
    std::vector<uint8_t> bytes; save::Error e; ok(save::encode(d,bytes,e),e); return bytes;
}
template<class T> void appendBytes(std::vector<uint8_t>& out,const T& object) {
    const auto* p=reinterpret_cast<const uint8_t*>(&object); out.insert(out.end(),p,p+sizeof(T));
}
// Test-only structural snapshot, NOT a SAV encoder for deferred bindings.
// Encode ordinary fields separately, then retain original job/pool bytes and scratch.
std::vector<uint8_t> snapshot(const save::Document& d) {
    auto copy=std::make_unique<save::Document>(d); copy->armyPool.reset();
    for(auto& player:copy->jobs) for(auto& job:player) std::fill(std::begin(job.armyIds),std::end(job.armyIds),uint16_t(0));
    auto result=archive(*copy); appendBytes(result,d.jobs);
    const bool present=d.armyPool.has_value(); appendBytes(result,present);
    if(d.armyPool) {
        const auto& pool=*d.armyPool; appendBytes(result,pool.liveIds.size());
        for(auto id:pool.liveIds) appendBytes(result,id);
        appendBytes(result,pool.freeSlots.size()); for(auto slot:pool.freeSlots) appendBytes(result,slot);
        appendBytes(result,pool.jobSlots);
    }
    for(const auto& t:d.territories) {
        const auto* p=reinterpret_cast<const uint8_t*>(&t.data);
        result.insert(result.end(),p+kTerritorySavedBytes,p+sizeof(Territory));
    }
    return result;
}
void retire(save::Document& d,uint16_t id) {
    save::Error e; ok(retireArmyPoolSlot(d,id,e),e);
    const auto found=std::find_if(d.armies.begin(),d.armies.end(),[&](const Army& a){return a.id==id;});
    check(found!=d.armies.end(),"fixture retirement ID exists"); const Army a=*found;
    for(auto& other:d.armies) {
        if(other.prev.raw==id) other.prev.raw=a.prev.raw;
        if(other.next.raw==id) other.next.raw=a.next.raw;
    }
    auto& t=d.territories[0].data;
    if(t.armies.raw==id) t.armies.raw=a.next.raw;
    if(t.foreignArmies.raw==id) t.foreignArmies.raw=a.next.raw;
    d.armies.erase(found); ok(save::validate(d,e),e);
}
void allocate(save::Document& d,uint16_t id,int owner=0) {
    append(d,id,owner); save::Error e; ok(allocateArmyPoolSlot(d,id,e),e); ok(save::validate(d,e),e);
}
void rejectsArchive(const save::Document& d) {
    const auto before=snapshot(d); std::vector<uint8_t> sentinel{7,1,9}; save::Error e;
    check(!save::encode(d,sentinel,e) && e.code!=save::ErrorCode::None && !e.message.empty() &&
          sentinel==std::vector<uint8_t>({7,1,9}) && snapshot(d)==before,
          "nonrepresentable binding cannot encode or mutate input/output");
}
void initialOrderAndCapacity() {
    auto d=fixture(); append(*d,40); append(*d,7); append(*d,90); bind(*d,0,0,0,7);
    const auto original=archive(*d); save::Error e{save::ErrorCode::Io,8,"old"};
    ok(ensureArmyPool(*d,e),e);
    check(e.code==save::ErrorCode::None && !e.offset && e.message.empty(),"pool init clears stale error");
    check(d->armyPool->liveIds.size()==560 && armyPoolSlot(*d,40)==1 && armyPoolSlot(*d,7)==2 &&
          armyPoolSlot(*d,90)==3 && d->armyPool->jobSlots[0][0][0]==2 && taskForceTarget(*d,0,0,0)->id==7,
          "LoadArmies uses physical file order, not sorted IDs or historical pointer words");
    check(d->armyPool->freeSlots.size()==557 && d->armyPool->freeSlots.front()==4 && d->armyPool->freeSlots.back()==560,
          "free-list is ascending storage with native head560 at the back");
    for(size_t i=0;i<d->armyPool->freeSlots.size();++i) check(d->armyPool->freeSlots[i]==i+4,"every initial free cell appears in native order");
    check(archive(*d)==original,"representable sidecar does not add bytes or rewrite original opaque words");
    const auto initialized=snapshot(*d); ok(ensureArmyPool(*d,e),e); check(snapshot(*d)==initialized,"ensure is idempotent");
    allocate(*d,100); check(armyPoolSlot(*d,100)==560 && d->armyPool->freeSlots.back()==559,"allocation pops head560");
    retire(*d,40); retire(*d,7); allocate(*d,200); allocate(*d,201);
    check(armyPoolSlot(*d,200)==2 && armyPoolSlot(*d,201)==1,"frees push LIFO, surviving cells do not compact");

    d=fixture(); for(int id=1;id<=558;++id) append(*d,uint16_t(id)); ok(ensureArmyPool(*d,e),e);
    allocate(*d,1000); check(armyPoolSlot(*d,1000)==560 && d->armyPool->freeSlots==std::vector<uint32_t>{559},"559th live unit leaves one reserved cell");
    append(*d,1001); const auto reserved=snapshot(*d);
    check(!allocateArmyPoolSlot(*d,1001,e) && snapshot(*d)==reserved,"allocation refuses to consume the last free cell atomically");
    d=fixture(); for(int id=1;id<=560;++id) append(*d,uint16_t(id)); ok(ensureArmyPool(*d,e),e);
    check(d->armyPool->freeSlots.empty() && armyPoolSlot(*d,560)==560,"loaded completely full pool is representable even though new allocation reserves a cell");
    const auto full=snapshot(*d);
    check(!retireArmyPoolSlot(*d,560,e) && snapshot(*d)==full,"full imported pool rejects native retirement's null free-head dereference atomically");
}
void freeReuseAndCleanup() {
    auto source=fixture(); append(*source,7); bind(*source,0,0,0,7); save::Error e; ok(ensureArmyPool(*source,e),e);
    const auto untouched=snapshot(*source); const auto slot=armyPoolSlot(*source,7);
    auto freed=std::make_unique<save::Document>(*source); retire(*freed,7);
    check(freed->jobs[0][0].armyIds[0]==7 && freed->armyPool->jobSlots[0][0][0]==slot &&
          !taskForceTarget(*freed,0,0,0) && freed->armyPool->liveIds[slot-1]==0 && freed->armyPool->freeSlots.back()==slot,
          "retirement clears occupant but preserves job ID and nonnull cell binding");
    rejectsArchive(*freed);
    auto cleaned=fixture(); TaskForcePruneReport report; report.cleared.resize(3);
    ok(pruneTaskForceArmies(*freed,0,0,*cleaned,report,e),e);
    check(report.cleared.size()==1 && report.cleared[0].reason==TaskForcePruneReason::IdMismatch &&
          report.cleared[0].expectedId==7 && report.cleared[0].observedId==0 && report.cleared[0].observedOwner==0 &&
          report.cleared[0].poolSlot==slot && !cleaned->jobs[0][0].armyIds[0] && !cleaned->armyPool->jobSlots[0][0][0],
          "0040aebc sees cleared cell id0/owner0 and explicitly nulls ID plus binding");
    (void)archive(*cleaned);
    auto different=std::make_unique<save::Document>(*freed); allocate(*different,9);
    check(taskForceTarget(*different,0,0,0)->id==9 && different->jobs[0][0].armyIds[0]==7,"reused cell resolves current occupant rather than expected ID");
    rejectsArchive(*different); ok(pruneTaskForceArmies(*different,0,0,*different,report,e),e);
    check(report.cleared.size()==1 && report.cleared[0].observedId==9 && different->armyById(9),"ID mismatch prunes binding without deleting reused unit");

    auto same=std::make_unique<save::Document>(*freed); allocate(*same,7); same->armies[0].job=23; same->armies[0].type=2;
    const auto sameBefore=snapshot(*same); ok(pruneTaskForceArmies(*same,0,0,*same,report,e),e);
    check(report.cleared.empty() && snapshot(*same)==sameBefore && taskForceTarget(*same,0,0,0)->id==7 && same->armies[0].job==23,
          "same-ID same-owner new lifetime survives native cleanup regardless of type/generation/Army.job");
    (void)archive(*same);
    auto changedOwner=std::make_unique<save::Document>(*freed); allocate(*changedOwner,7,1);
    (void)archive(*changedOwner); // Owner mismatch is a prune rule, not a SAV reference error.
    ok(pruneTaskForceArmies(*changedOwner,0,0,*changedOwner,report,e),e);
    check(report.cleared.size()==1 && report.cleared[0].reason==TaskForcePruneReason::OwnerMismatch &&
          report.cleared[0].expectedOwner==0 && report.cleared[0].observedOwner==1 && changedOwner->armies[0].owner==1,
          "same ID but changed signed owner clears only the taskforce binding");
    for(int owner:{-1,256}) {
        auto wrongWord=std::make_unique<save::Document>(*source); wrongWord->jobs[0][0].owner=int16_t(owner);
        ok(pruneTaskForceArmies(*wrongWord,0,0,*wrongWord,report,e),e);
        check(report.cleared.size()==1 && report.cleared[0].expectedOwner==owner &&
              report.cleared[0].reason==TaskForcePruneReason::OwnerMismatch,"Job.owner compares as signed WORD without byte truncation");
    }
    check(snapshot(*source)==untouched,"independent pool copies cannot share mutable cells, free lists or bindings");
}
void nullAndTraversal() {
    auto d=fixture(); append(*d,7); bind(*d,0,0,0,7); save::Error e; ok(ensureArmyPool(*d,e),e);
    d->armyPool->jobSlots[0][0][0]=0; const auto before=snapshot(*d); TaskForcePruneReport report;
    ok(pruneTaskForceArmies(*d,0,0,*d,report,e),e);
    check(report.cleared.empty() && snapshot(*d)==before && !taskForceTarget(*d,0,0,0),"NULL plus nonzero expected ID is untouched by0040aebc");
    rejectsArchive(*d);
    d->jobs[0][0].armyIds[0]=0; d->armyPool->jobSlots[0][0][0]=560;
    const auto zero=snapshot(*d); ok(pruneTaskForceArmies(*d,0,0,*d,report,e),e);
    check(report.cleared.empty() && snapshot(*d)==zero,"nonnull cleared cell id0 owner0 equals expected0 owner0 and is retained");
    rejectsArchive(*d);
    d=fixture(); append(*d,7); bind(*d,0,4,2,7); bind(*d,0,0,9,7); bind(*d,1,2,0,7);
    ok(ensureArmyPool(*d,e),e); retire(*d,7);
    auto all=std::make_unique<save::Document>(*d); ok(pruneAllTaskForceArmies(*all,*all,report,e),e);
    check(report.cleared.size()==3 && report.cleared[0].player==0 && report.cleared[0].jobIndex==0 && report.cleared[0].member==9 &&
          report.cleared[1].jobIndex==4 && report.cleared[1].member==2 && report.cleared[2].player==1 && report.cleared[2].jobIndex==2,
          "all cleanup follows player/job/member native traversal order");
    ok(prunePlayerTaskForceArmies(*d,0,*d,report,e),e);
    check(report.cleared.size()==2 && d->jobs[1][2].armyIds[0]==7 && d->armyPool->jobSlots[1][2][0]!=0,"player cleanup preserves other players' deferred bindings");
    check(!taskForceTarget(*d,-1,0,0) && !taskForceTarget(*d,7,0,0) && !taskForceTarget(*d,0,50,0) &&
          !taskForceTarget(*d,0,0,16) && !armyPoolSlot(*d,999),"invalid lookup coordinates are null, never dereferenced");
}
void malformedAndRollback() {
    auto source=fixture(); append(*source,7); bind(*source,0,0,0,7); save::Error e; ok(ensureArmyPool(*source,e),e);
    auto invalid=[&](const save::Document& bad) {
        const auto before=snapshot(bad); auto dest=std::make_unique<save::Document>(*source); const auto prior=snapshot(*dest);
        TaskForcePruneReport r; r.cleared.resize(1); r.cleared[0].expectedId=999; const auto old=r;
        check(!save::validate(bad,e) && !validateArmyPool(bad,e),"malformed typed sidecar is rejected independently and by document validation");
        check(!pruneAllTaskForceArmies(bad,*dest,r,e) && snapshot(*dest)==prior && r==old && snapshot(bad)==before,
              "malformed-sidecar cleanup preserves source, destination and report");
        auto alias=std::make_unique<save::Document>(bad);
        check(!pruneAllTaskForceArmies(*alias,*alias,r,e) && snapshot(*alias)==before && r==old,"aliased malformed-sidecar cleanup rolls back");
        check(!ensureArmyPool(*alias,e) && snapshot(*alias)==before,"ensure never repairs malformed metadata by rediscovering IDs");
        rejectsArchive(bad);
    };
    for(int variant=0;variant<7;++variant) {
        auto bad=std::make_unique<save::Document>(*source); auto& p=*bad->armyPool;
        switch(variant) {
            case 0:p.liveIds.pop_back();break;
            case 1:p.freeSlots.push_back(p.freeSlots.back());break;
            case 2:p.freeSlots.pop_back();break;
            case 3:p.freeSlots.back()=0;break;
            case 4:p.jobSlots[0][0][0]=561;break;
            case 5:p.liveIds[0]=999;break;
            case 6:p.liveIds[1]=7;p.freeSlots.erase(p.freeSlots.begin());break;
        }
        invalid(*bad);
    }
    auto missing=fixture(); missing->jobs[0][0].armyIds[0]=7;
    check(!save::validate(*missing,e),"archival document without explicit metadata still rejects dangling expected IDs");
    auto target=std::make_unique<save::Document>(*source); const auto stable=snapshot(*target);
    TaskForcePruneReport r; r.cleared.resize(1); const auto old=r;
    for(const auto [p,j]:{std::pair{-1,0},std::pair{7,0},std::pair{0,-1},std::pair{0,50}})
        check(!pruneTaskForceArmies(*target,p,j,*target,r,e) && snapshot(*target)==stable && r==old,"invalid cleanup indices are atomic");
    check(!retireArmyPoolSlot(*target,999,e) && snapshot(*target)==stable,"retiring absent ID does not mutate native pool");
    const auto encoded=archive(*source); auto decoded=fixture(); ok(save::decode(encoded,*decoded,e),e);
    check(!decoded->armyPool && archive(*decoded)==encoded,"strict file round trip neither persists nor reconstructs transient pool metadata");
}
void runtimeLifetimes() {
    for(bool reuseSameId:{false,true}) {
        auto d=fixture(); append(*d,7); bind(*d,0,0,0,7); d->armies[0].job=1;
        d->options.nextGlobalId=reuseSameId?6:99;
        runtime::State state; save::Error e; ok(state.prepare(*d,e),e);
        const auto old=state.armyById(7); ArmyLifecycleReport removal;
        ok(state.removeArmy(old,ArmyRemovalKind::DeleteUnit,false,removal,e),e);
        const auto slot=state.graph().jobs[0][0].poolSlots[0];
        check(!state.army(old) && slot!=0 && state.graph().jobs[0][0].pointerPresent[0] && !state.graph().jobs[0][0].armies[0] &&
              state.document()->jobs[0][0].armyIds[0]==7,"retired public handle is stale while Graph retains nonnull physical cell");
        runtime::State another; ok(another.prepare(*d,e),e); const auto foreign=another.armyById(7);
        const auto otherBefore=snapshot(*another.document());
        check(!another.prepare(*state.document(),e) && another.army(foreign) && snapshot(*another.document())==otherBefore,
              "prepare cannot reclassify a nonarchivable pending simulation as a fresh prepared state");
        runtime::ArmyHandle created; ArmyLifecycleReport creation;
        ok(state.createArmy({1,0,1},{},created,creation,e),e);
        check(state.army(created) && created!=old && !state.army(old) && state.graph().jobs[0][0].armies[0]==created &&
              state.graph().jobs[0][0].poolSlots[0]==slot && state.document()->jobs[0][0].armyIds[0]==7,
              "Graph follows reused physical cell, never revives an old lifetime handle or silently rewrites expected ID");
        const auto id=state.army(created)->id; check(id==(reuseSameId?7:100),"fixture controls same-ID versus different-ID reuse");
        const auto before=snapshot(*state.document()); const auto prior=removal;
        check(!state.removeArmy(old,ArmyRemovalKind::DeleteUnit,false,removal,e) && removal==prior && snapshot(*state.document())==before && state.army(created),
              "stale lifetime cannot delete a reused physical cell and failure preserves report");
        runtime::EntityEditReport structural; structural.id=12345; const auto structuralBefore=structural;
        check(!state.retireArmy(created,structural,e) && structural==structuralBefore && snapshot(*state.document())==before && state.army(created),
              "structural retirement rejects a physical incoming job binding even when expected ID differs and new Army.job is0");
        TaskForcePruneReport pruned; ok(state.pruneTaskForceArmies(0,0,pruned,e),e);
        check(state.army(created) && pruned.cleared.size()==(reuseSameId?0u:1u) &&
              state.graph().jobs[0][0].pointerPresent[0]==reuseSameId && bool(state.graph().jobs[0][0].armies[0])==reuseSameId,
              "explicit cleanup respects native identity rule without retiring the replacement lifetime");
    }
}
}
int main() {
    try {
        const auto game=std::make_unique<GameState>(gs); const auto globals=std::make_unique<GameGlobals>(gg);
        const auto low=rtl::seed(),high=rtl::seedHi();
        initialOrderAndCapacity(); freeReuseAndCleanup(); nullAndTraversal(); malformedAndRollback(); runtimeLifetimes();
        check(std::memcmp(game.get(),&gs,sizeof(gs))==0 && std::memcmp(globals.get(),&gg,sizeof(gg))==0 && rtl::seed()==low && rtl::seedHi()==high,
              "physical pool, cleanup and owned runtime must not mutate legacy globals/RNG");
        std::cout<<"army_pool: LIFO, deferred bindings, reuse, native cleanup, strict codec, rollback and lifetime handles passed\n"; return 0;
    } catch(const std::exception& e) { std::cerr<<"army_pool: "<<e.what()<<'\n'; return 1; }
}
