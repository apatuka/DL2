// Derived original-function oracles, not an assertion of a live game replay.
#include "game/entity_lifecycle.h"
#include "game/army_pool.h"
#include "game/entity_creation.h"
#include "game/ai_session.h"
#include "game/data_tables.h"
#include "game/save_files.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include "game/runtime_state.h"
#include "formats/hdx_archive.h"
#include <algorithm>
#include <bit>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
using namespace dl2;
using namespace dl2::simulation;
void require(bool condition, const char* text) { if (!condition) throw std::runtime_error(text); }
std::unique_ptr<save::Document> fixture() {
    auto d=std::make_unique<save::Document>();
    std::memcpy(d->header.text,save::kHeaderText,sizeof(save::kHeaderText)); d->header.version=kSaveVersion;
    d->options.numPlayers=2; d->options.localPlayer=0; d->options.turn=17; d->options.nextGlobalId=1000;
    d->world.width=1; d->world.height=1; d->world.numTerritories=2; d->world.rngSeed=123;
    d->tiles.resize(1); d->territories.resize(2);
    for (int p=0;p<7;++p) {
        d->players[size_t(p)].race=2; d->players[size_t(p)].index=uint8_t(p);
        d->players[size_t(p)].type=p==0?1:3; d->raceStats.v[24][p]=100;
        d->ministerJobs[size_t(p)].resize(1); d->ministerJobs[size_t(p)][0].type=1;
        for (auto& job : d->jobs[size_t(p)]) job.owner=int16_t(p);
    }
    for (int i=0;i<2;++i) {
        auto& t=d->territories[size_t(i)].data; t.index=uint16_t(i+1); t.owner=0;
        t.terrain=i==0?1:0; t.population=500; t.morale=100; t.materials[2]=20000;
        t.production[4]=1234; t.consumption[2]=-77;
        for (int s=0;s<36;++s) { t.sites[s].unk_00=uint16_t((s%6)|((s/6)<<8)); t.sites[s].terrainFlags=1; }
    }
    d->localList={0,0x12345678}; d->trailing={0,0xff,0x80};
    return d;
}
Army& addArmy(save::Document& d,int type,int territory=1,int owner=0) {
    Army a{}; a.id=uint16_t(d.armies.size()+1); a.type=uint8_t(type); a.unitClass=data::kUnitTypes[type].unitClass;
    a.owner=int8_t(owner); a.health=100; a.territory.raw=a.dest.raw=a.origin.raw=uint32_t(territory);
    auto& t=d.territories[size_t(territory-1)].data;
    auto& head=t.owner==owner?t.armies:t.foreignArmies;
    a.next.raw=head.raw;
    for (auto& prior:d.armies) if (prior.id==head.raw) prior.prev.raw=a.id;
    head.raw=a.id; d.armies.push_back(a); return d.armies.back();
}
Building& addBuilding(save::Document& d,int type,int site=0,int territory=1) {
    Building b{}; b.id=uint16_t(50000+d.buildings.size()); b.type=uint8_t(type);
    b.category=data::kBuildingTypes[type].category; b.flags=6; b.site=int8_t(site); b.territory=int16_t(territory);
    if (!d.buildings.empty()) { b.prev.raw=d.buildings.back().id; d.buildings.back().next.raw=b.id; }
    d.territories[size_t(territory-1)].data.sites[site].building.raw=b.id;
    d.buildings.push_back(b); return d.buildings.back();
}
void join(save::Document& d,uint32_t id,int jobIndex,int slot) {
    auto found=std::find_if(d.armies.begin(),d.armies.end(),[&](auto a){return a.id==id;});
    found->job=int16_t(jobIndex+1);
    auto& job=d.jobs[size_t(found->owner)][size_t(jobIndex)];
    job.armyIds[slot]=uint16_t(id); job.armies[slot].raw=0xabcdef00u+id;
}
std::vector<uint8_t> bytes(const save::Document& d) {
    std::vector<uint8_t> result; save::Error error;
    if (!save::encode(d,result,error)) throw std::runtime_error(error.message);
    for (const auto& record:d.territories) {
        const auto* first=reinterpret_cast<const uint8_t*>(&record.data);
        result.insert(result.end(),first+kTerritorySavedBytes,first+sizeof(Territory));
    }
    return result;
}
struct Outcome { std::unique_ptr<save::Document> doc=std::make_unique<save::Document>(); ArmyLifecycleReport report; };
Outcome create(const save::Document& d,int type,int territory=1,int owner=0,ArmyCreationContext context={}) {
    const auto before=bytes(d); Outcome out; save::Error error{save::ErrorCode::Io,1,"old"};
    if (!createArmy(d,{uint32_t(territory),owner,type},context,*out.doc,out.report,error)) throw std::runtime_error(error.message);
    require(error.code==save::ErrorCode::None && error.offset==0 && error.message.empty(),"create clears stale error");
    require(bytes(d)==before,"create leaves input and scratch untouched"); return out;
}
Outcome remove(const save::Document& d,uint32_t id,ArmyRemovalKind kind=ArmyRemovalKind::DeleteUnit,bool detach=false) {
    const auto before=bytes(d); Outcome out; save::Error error{save::ErrorCode::Io,1,"old"};
    if (!removeArmy(d,{id,kind,detach},*out.doc,out.report,error)) throw std::runtime_error(error.message);
    require(error.code==save::ErrorCode::None && error.message.empty(),"remove clears error");
    require(bytes(d)==before,"remove leaves input unchanged"); return out;
}
ArmyCreationQuery query(const save::Document& d,int type,int territory=1,ArmyCreationContext context={}) {
    ArmyCreationQuery result; save::Error error;
    if (!canCreateArmy(d,uint32_t(territory),type,context,result,error)) throw std::runtime_error(error.message);
    return result;
}
void rejectCreate(const save::Document& d,ArmyCreationRequest request,ArmyCreationContext context={}) {
    auto out=fixture(); const auto before=bytes(d), destination=bytes(*out);
    ArmyLifecycleReport report; report.primaryId=999; report.createdIds={9}; const auto old=report; save::Error error;
    require(!createArmy(d,request,context,*out,report,error) && error.code!=save::ErrorCode::None && !error.message.empty(),"create rejection is explicit");
    require(bytes(d)==before && bytes(*out)==destination && report==old,"failed create is fully transactional");
    auto alias=std::make_unique<save::Document>(d);
    require(!createArmy(*alias,request,context,*alias,report,error) && bytes(*alias)==before && report==old,"in-place create failure rolls back");
}
void rejectRemove(const save::Document& d,ArmyRemovalRequest request) {
    auto out=fixture(); const auto before=bytes(d), destination=bytes(*out); ArmyLifecycleReport report;
    report.primaryId=999; report.removedIds={8}; const auto old=report; save::Error error;
    require(!removeArmy(d,request,*out,report,error) && error.code!=save::ErrorCode::None && !error.message.empty(),"remove rejection is explicit");
    require(bytes(d)==before && bytes(*out)==destination && report==old,"failed remove preserves both documents/report");
}
void creationAndQueries() {
    auto d=fixture();
    require(query(*d,16).reason==ArmyCreationReason::MissileBaseMissing,"warhead requires completed missile base");
    auto& base=addBuilding(*d,33); base.turnsLeft=1;
    require(query(*d,16).reason==ArmyCreationReason::MissileBaseMissing,"unfinished base does not qualify");
    base.turnsLeft=0; base.flags=0;
    require(query(*d,16).reason==ArmyCreationReason::Allowed,"completed base qualifies without Built or Active flags");
    for (int i=0;i<4;++i) addArmy(*d,36);
    const auto full=query(*d,16);
    require(full.reason==ArmyCreationReason::StackLimit && full.stackGroup==3 && full.sameGroup==4 && full.limit==4,
            "all own warhead classes share the original four-unit stack limit");
    require(query(*d,13).reason==ArmyCreationReason::SeaUnitOnLand,"ships cannot be created on land");
    require(query(*d,1,2).reason==ArmyCreationReason::CarrierUnavailable,"land-at-sea needs own-head transport capacity");
    require(query(*d,27,2).reason==ArmyCreationReason::Allowed,"amphibious AAV does not require a carrier");
    d=fixture(); for (int i=0;i<4;++i) addArmy(*d,36,1,1);
    require(query(*d,36).reason==ArmyCreationReason::Allowed && query(*d,36).sameGroup==0,"foreign missiles do not count toward own-list limit");
    auto own=create(*d,1); const auto* made=own.doc->armyById(1001);
    require(made && own.report.createdIds==std::vector<uint32_t>{1001} && made->next.raw==0 &&
            own.doc->territories[0].data.armies.raw==1001 && made->strength==3 && made->health==100 &&
            std::string(made->name)=="Human Laser Squad #1001", "real creation initializes and links own head with canonical defaults/name");
    auto foreign=create(*own.doc,1,1,1);
    require(foreign.doc->armyById(1002)->next.raw==4 && foreign.doc->armyById(4)->prev.raw==1002 &&
            foreign.doc->territories[0].data.foreignArmies.raw==1002,"foreign insertion prepends to foreign head only");
    auto alias=std::make_unique<save::Document>(*d); ArmyLifecycleReport report; save::Error error;
    require(createArmy(*alias,{1,0,1},{},*alias,report,error) && bytes(*alias)==bytes(*own.doc) && report==own.report,
            "in-place and separate create destinations agree");
    const auto before=bytes(*d); ArmyCreationQuery sentinel; sentinel.sameGroup=123; const auto old=sentinel;
    require(!canCreateArmy(*d,0,1,{},sentinel,error) && sentinel==old && bytes(*d)==before,"invalid query preserves output/source");
}
void carriersAndSiege() {
    auto d=fixture(); auto transport=create(*d,12,2);
    require(transport.doc->armyById(1001)->moves==26,"Sea Transport gets real support tactic26");
    auto first=create(*transport.doc,1,2); auto second=create(*first.doc,1,2); auto third=create(*second.doc,1,2);
    const auto* host=third.doc->armyById(1001);
    require(host->cargo[0].raw==1002 && host->cargo[1].raw==1003 && host->cargo[2].raw==1004 &&
            third.doc->armyById(1004)->cargo[0].raw==1001 && third.report.carrierId==1001,"three cargo slots attach in ascending order with reciprocal parent");
    rejectCreate(*third.doc,{2,0,1});
    auto unloaded=remove(*third.doc,1003);
    require(unloaded.doc->armyById(1001)->cargo[1].raw==0 && unloaded.report.removedIds==std::vector<uint32_t>{1003},"passenger deletion frees only its carrier slot");
    auto refill=create(*unloaded.doc,1,2);
    require(refill.doc->armyById(1001)->cargo[1].raw==1005,"new passenger fills first vacated slot without renumbering survivors");
    auto sunk=remove(*third.doc,1001);
    require(sunk.doc->armies.empty() && sunk.report.removedIds==std::vector<uint32_t>({1002,1003,1004,1001}) &&
            !sunk.doc->territories[1].data.armies.raw && sunk.report.refunds.empty(),"DeleteUnit carrier kills cargo in slot order before parent, no fabricated refunds");
    // CanCreate starts on own head; Attach starts on the newly inserted foreign
    // node. No foreign carrier exists, so original CreateUnit ignores attach0.
    auto foreign=create(*transport.doc,1,2,1);
    require(foreign.doc->armyById(1002)->cargo[0].raw==0 && foreign.report.carrierId==0 &&
            foreign.doc->armyById(1001)->cargo[0].raw==0,"preserve original differing query/attachment heads for foreign land-at-sea creation");
    auto siege=create(*d,35,2);
    require(siege.report.createdIds==std::vector<uint32_t>({1001,1002}) && siege.report.pairedMissileAttempted &&
            siege.report.pairedMissileId==1002 && siege.doc->armyById(1001)->cargo[0].raw==1002 &&
            siege.doc->armyById(1002)->cargo[0].raw==1001 && siege.doc->territories[1].data.armies.raw==1002,
            "siege creates second ID and reciprocal missile, whose allocation prepends before host");
    auto fired=remove(*siege.doc,1002);
    require(fired.doc->armies.size()==1 && fired.doc->armyById(1001)->cargo[0].raw==0,"missile deletion detaches from siege host");
    auto destroyed=remove(*siege.doc,1001);
    require(destroyed.report.removedIds==std::vector<uint32_t>({1002,1001}) && destroyed.doc->armies.empty(),"siege death cascades to its missile");
    for (int i=0;i<4;++i) addArmy(*d,36,2);
    auto bare=create(*d,35,2);
    require(bare.report.createdIds==std::vector<uint32_t>{1001} && bare.report.pairedMissileAttempted &&
            !bare.report.pairedMissileId && bare.report.pairedMissileDenial==ArmyCreationReason::StackLimit &&
            bare.doc->options.nextGlobalId==1002,"original bare-cruiser success reports child stack refusal and consumed attempted ID");
}
void jobsAndDeferredMinisters() {
    auto d=fixture(); const uint32_t host=addArmy(*d,12,2).id;
    join(*d,host,0,0); d->jobs[0][0].goal=3;
    auto passenger=create(*d,1,2);
    require(passenger.doc->armyById(1001)->job==1 && passenger.doc->jobs[0][0].armyIds[1]==1001 &&
            passenger.doc->jobs[0][0].armies[1].raw==0 && passenger.doc->armyById(host)->cargo[0].raw==1001,
            "cargo compatible with transport taskforce is removed/added using authoritative file IDs");
    const auto hostSlot=armyPoolSlot(*passenger.doc,host), passengerSlot=armyPoolSlot(*passenger.doc,1001);
    auto deferred=remove(*passenger.doc,host,ArmyRemovalKind::DeleteUnit,false);
    require(deferred.doc->armies.empty() && deferred.report.removedIds==std::vector<uint32_t>({1001,host}) &&
            deferred.doc->jobs[0][0].armyIds[0]==host && deferred.doc->jobs[0][0].armyIds[1]==1001 &&
            deferred.doc->armyPool->jobSlots[0][0][0]==hostSlot && deferred.doc->armyPool->jobSlots[0][0][1]==passengerSlot &&
            !taskForceTarget(*deferred.doc,0,0,0) && !taskForceTarget(*deferred.doc,0,0,1),
            "native carrier cascade leaves both taskforce IDs bound to their cleared physical cells");
    save::Error deferredError; require(save::validate(*deferred.doc,deferredError),"deferred cascade is valid simulation state");
    std::vector<uint8_t> refused{4,2};
    require(!save::encode(*deferred.doc,refused,deferredError) && refused==std::vector<uint8_t>({4,2}),
            "deferred taskforce references cannot silently become a SAV");
    TaskForcePruneReport pruned;
    require(pruneTaskForceArmies(*deferred.doc,0,0,*deferred.doc,pruned,deferredError) && pruned.cleared.size()==2 &&
            !deferred.doc->jobs[0][0].armyIds[0] && !deferred.doc->jobs[0][0].armyIds[1],
            "explicit native cleanup clears cascade references in member order");
    auto detached=remove(*passenger.doc,host,ArmyRemovalKind::DeleteUnit,true);
    require(detached.doc->armies.empty() && !detached.doc->jobs[0][0].armyIds[0] && !detached.doc->jobs[0][0].armyIds[1],
            "explicit caller taskforce cleanup precedes cascade and clears affected IDs/cache words");
    d->jobs[0][0].goal=5; rejectCreate(*d,{2,0,1});
    d->jobs[0][0].goal=4; d->raceStats.v[54][2]=1;
    passenger=create(*d,1,2);
    require(passenger.doc->armyById(1001)->job==1,"scout-capable racial infantry joins transport scout taskforce");
    d->jobs[0][0].goal=3;
    auto& moving=addArmy(*d,1,1,1); moving.job=2; const auto movingId=moving.id;
    require(query(*d,1,2,{movingId}).reason==ArmyCreationReason::CarrierUnavailable && query(*d,1,2).reason==ArmyCreationReason::Allowed,
            "explicit moving-AI context filters carriers by taskforce without consulting globals");
    d->players[1].type=255;
    require(query(*d,1,2,{movingId}).reason==ArmyCreationReason::Allowed,"FindTransport compares stored player type as signed byte, so255 is below3");
    d=fixture(); const auto id=addArmy(*d,1).id;
    auto& jobs=d->ministerJobs[0]; jobs[0].next.raw=0x1234; jobs.emplace_back(); jobs.back().type=13; jobs.back().param[0]=int32_t(id);
    auto killed=remove(*d,id);
    require(killed.report.deferredMaintainJobs==1 && killed.doc->ministerJobs[0][1].type==13 &&
            killed.doc->ministerJobs[0][1].param[0]==int32_t(id) && killed.doc->ministerJobs[0][1].unk_10==0,
            "DeleteUnit preserves MaintainUnit job until its real deferred scheduler, rather than inventing callback cleanup");
    killed.doc->options.nextGlobalId=int32_t(id)-1;
    rejectCreate(*killed.doc,{1,0,1});
    d=fixture(); const auto carrierId=addArmy(*d,12,2).id; join(*d,carrierId,0,0); d->jobs[0][0].goal=3;
    for (int slot=1;slot<16;++slot) { const auto unitId=addArmy(*d,1).id; join(*d,unitId,0,slot); }
    auto full=create(*d,1,2);
    require(full.doc->armyById(1001)->job==0 && full.doc->armyById(1001)->cargo[0].raw==carrierId,
            "full taskforce preserves original Add early return while still attaching cargo");
}
void disbandRefundsAndColonizers() {
    auto d=fixture(); const auto laser=addArmy(*d,1).id;
    d->players[0].credits=std::numeric_limits<int32_t>::max()-10;
    auto refund=remove(*d,laser,ArmyRemovalKind::DisbandUnit);
    require(refund.report.refunds.size()==1 && refund.report.refunds[0].credits==17 &&
            refund.doc->players[0].credits==std::numeric_limits<int32_t>::min()+6 && refund.doc->options.turn==17,
            "disband35-credit unit refunds17 with low32 wrap and never advances turn");
    d=fixture(); auto host=addArmy(*d,12,2).id; auto child=addArmy(*d,1,2).id;
    d->armies[0].cargo[0].raw=child; d->armies[1].cargo[0].raw=host;
    refund=remove(*d,host,ArmyRemovalKind::DisbandUnit);
    require(refund.doc->armies.empty() && refund.report.refunds.size()==1 && refund.report.refunds[0].credits==25 &&
            refund.doc->players[0].credits==25 && refund.doc->territories[1].data.materials[4]==12,
            "disband refunds carrier only; cargo is killed without additional refund");
    d=fixture(); auto& housing=addBuilding(*d,2); housing.task[1]=20; housing.labor[1]=5;
    const auto colonizer=addArmy(*d,25).id;
    const auto untouched=d->territories[1].data;
    auto returned=remove(*d,colonizer,ArmyRemovalKind::DisbandUnit);
    require(returned.doc->territories[0].data.population==600 && returned.doc->buildings[0].labor[1]==6 &&
            returned.doc->territories[0].data.materials[3]==5 && returned.doc->territories[0].data.materials[2]==20000 &&
            returned.report.refunds[0].populationReturned && returned.report.refunds[0].laborBalanced,
            "colonizer returns100 population, caps housing/land, balances local labor only and refunds halfwood");
    require(std::memcmp(&untouched,&returned.doc->territories[1].data,sizeof(Territory))==0,"disband local labor does not touch another territory");
    d->territories[0].data.population=32760;
    auto wrapped=remove(*d,colonizer,ArmyRemovalKind::DisbandUnit);
    require(wrapped.doc->territories[0].data.population==-32676,"colonizer population add narrows signed16 before max comparison");
    d=fixture(); const auto seaColonizer=addArmy(*d,31,2).id;
    auto noPlatform=remove(*d,seaColonizer,ArmyRemovalKind::DisbandUnit);
    require(noPlatform.doc->territories[1].data.population==500 && !noPlatform.report.refunds[0].populationReturned &&
            noPlatform.report.refunds[0].credits==50,"sea colonizer without platform gets costs back but no population");
    addBuilding(*d,38,25,2); auto& hab=addBuilding(*d,39,15,2); hab.task[1]=20;
    auto seaPopulation=remove(*d,seaColonizer,ArmyRemovalKind::DisbandUnit);
    require(seaPopulation.doc->territories[1].data.population==600 && seaPopulation.report.refunds[0].populationReturned,
            "stored platform category20 permits sea colonizer population refund");
}
void capacityFailuresAndPurity() {
    auto d=fixture(); for (int i=0;i<558;++i) addArmy(*d,13,2);
    auto last=create(*d,35,2);
    require(last.doc->armies.size()==559 && last.report.createdIds==std::vector<uint32_t>{1001} &&
            last.report.pairedMissileDenial==ArmyCreationReason::ReservedPoolSlot && last.doc->options.nextGlobalId==1002,
            "559th record is permitted but child allocation preserves final reserved node and consumes attempted ID");
    rejectCreate(*last.doc,{2,0,13});
    d=fixture(); for (int32_t counter : {-1,65535,std::numeric_limits<int32_t>::max()}) { d->options.nextGlobalId=counter; rejectCreate(*d,{1,0,1}); }
    d->options.nextGlobalId=std::numeric_limits<int32_t>::min();
    auto wrapped=create(*d,1);
    require(wrapped.doc->options.nextGlobalId==std::numeric_limits<int32_t>::min()+1 && wrapped.report.primaryId==1,"signed global counter wrap/truncation has defined behavior");
    d=fixture(); auto& existing=addBuilding(*d,1); const auto oldId=existing.id; existing.id=1001;
    d->territories[0].data.sites[0].building.raw=1001; (void)oldId;
    rejectCreate(*d,{1,0,1});
    d=fixture(); addArmy(*d,1); addArmy(*d,1);
    d->armies[0].prev.raw=0; rejectCreate(*d,{1,0,1}); rejectRemove(*d,{1,ArmyRemovalKind::DeleteUnit,false});
    d=fixture(); auto host=addArmy(*d,12,2).id; auto child=addArmy(*d,1,2).id;
    d->armies[0].cargo[0].raw=child; // deliberately missing reciprocal passenger link
    rejectRemove(*d,{host,ArmyRemovalKind::DeleteUnit,false});
    d=fixture(); const auto id=addArmy(*d,1).id;
    const auto before=bytes(*d); std::vector<uint8_t> savedGs(sizeof(gs)),savedGg(sizeof(gg));
    std::memcpy(savedGs.data(),&gs,sizeof(gs)); std::memcpy(savedGg.data(),&gg,sizeof(gg));
    const auto seed=rtl::seed(),seedHi=rtl::seedHi();
    auto created=create(*d,1); auto deleted=remove(*d,id);
    auto alias=std::make_unique<save::Document>(*d); ArmyLifecycleReport report; save::Error error;
    require(removeArmy(*alias,{id,ArmyRemovalKind::DeleteUnit,false},*alias,report,error) && bytes(*alias)==bytes(*deleted.doc) && report==deleted.report,
            "aliased removal is byte-identical to separate output");
    require(created.doc->armies.size()==2 && bytes(*d)==before && std::memcmp(savedGs.data(),&gs,sizeof(gs))==0 &&
            std::memcmp(savedGg.data(),&gg,sizeof(gg))==0 && rtl::seed()==seed && rtl::seedHi()==seedHi,
            "lifecycle changes only owned candidate; global state and both RNG words remain identical");
}
void runtimeIntegration() {
    auto d=fixture(); const auto existingArmyId=addArmy(*d,1).id; const auto existingBuildingId=addBuilding(*d,1).id;
    const auto input=bytes(*d); runtime::State state; save::Error error;
    require(state.prepare(*d,error),"runtime lifecycle fixture prepares");
    const auto survivor=state.armyById(existingArmyId);
    const auto building=state.buildingById(existingBuildingId);
    const auto territory=state.territoryByIndex(2);
    const auto rng=state.sessionRng();
    runtime::ArmyHandle siege; ArmyLifecycleReport report;
    require(state.createArmy({2,0,35},{},siege,report,error) && state.army(siege)->id==1001 && state.stage()==runtime::Stage::EntitiesEdited,
            "runtime creates siege with stable identity in nonplayable edit stage");
    const auto missile=state.armyById(1002);
    require(state.army(missile) && state.armyLinks(siege)->cargo[0]==missile && state.armyLinks(missile)->cargo[0]==siege &&
            state.graph().territories[1].savedOwnHead==missile && state.armyLinks(siege)->current==territory,
            "runtime graph resolves siege pair, current territory and prepended missile head");
    require(state.removeArmy(siege,ArmyRemovalKind::DeleteUnit,false,report,error) && !state.army(siege) && !state.army(missile) &&
            state.army(survivor) && state.building(building) && state.territory(territory),
            "runtime cascade invalidates all retired lifetimes and preserves survivors/static handles");
    const auto after=bytes(*state.document()); const auto previous=report;
    require(!state.removeArmy(siege,ArmyRemovalKind::DeleteUnit,false,report,error) && report==previous && bytes(*state.document())==after,
            "retired handle cannot delete a reused dense slot or mutate previous report");
    runtime::ArmyHandle transport;
    require(state.createArmy({2,0,12},{},transport,report,error),"runtime creates real transport");
    runtime::ArmyHandle passenger;
    require(state.createArmy({2,0,1},{},passenger,report,error) && state.armyLinks(passenger)->cargo[0]==transport &&
            state.armyLinks(transport)->cargo[0]==passenger,"runtime cargo links resolve to durable typed handles");
    require(state.removeArmy(passenger,ArmyRemovalKind::DisbandUnit,false,report,error) && !state.army(passenger) &&
            state.army(transport) && !state.armyLinks(transport)->cargo[0],"runtime disband detaches passenger without invalidating carrier");
    auto created=passenger; const auto oldReport=report; const auto beforeFailure=bytes(*state.document());
    require(!state.createArmy({2,0,99},{},created,report,error) && created==passenger && report==oldReport &&
            bytes(*state.document())==beforeFailure && state.army(transport) && state.army(survivor),
            "failed runtime creation preserves source, stale output handle, report and survivor lifetimes");
    runtime::State other; require(other.prepare(*d,error),"foreign fixture prepares");
    require(!state.removeArmy(other.armyById(existingArmyId),ArmyRemovalKind::DeleteUnit,false,report,error) && report==oldReport,
            "foreign handle is not interchangeable with same file ID in local instance");
    auto captured=fixture(); const auto capturedBefore=bytes(*captured);
    require(!state.capture(*captured,error) && bytes(*captured)==capturedBefore && !state.advanceTurn(error) &&
            state.sessionRng()==rng && bytes(*d)==input,"lifecycle does not become exportable/playable or touch caller/RNG");
}
struct BuildingOutcome {
    std::unique_ptr<save::Document> doc=std::make_unique<save::Document>();
    BuildingLifecycleReport report;
};
BuildingOutcome removeB(const save::Document& d,uint32_t id,BuildingRemovalKind kind=BuildingRemovalKind::DeleteBuilding,int player=-1) {
    const auto before=bytes(d); BuildingOutcome out; save::Error error{save::ErrorCode::Io,8,"stale"};
    if (!removeBuilding(d,{id,kind,player},*out.doc,out.report,error)) throw std::runtime_error(error.message);
    require(error.code==save::ErrorCode::None && error.message.empty() && bytes(d)==before,"building removal clears error and preserves source");
    auto alias=std::make_unique<save::Document>(d); BuildingLifecycleReport aliasReport;
    require(removeBuilding(*alias,{id,kind,player},*alias,aliasReport,error) && bytes(*alias)==bytes(*out.doc) && aliasReport==out.report,
            "building removal supports exact alias transaction");
    return out;
}
void rejectB(const save::Document& d,BuildingRemovalRequest request) {
    auto destination=fixture(); const auto sourceBefore=bytes(d), destinationBefore=bytes(*destination);
    BuildingLifecycleReport report; report.primaryId=999; report.removedIds={1,9}; const auto old=report; save::Error error;
    require(!removeBuilding(d,request,*destination,report,error) && error.code!=save::ErrorCode::None && !error.message.empty(),"building rejection is explicit");
    require(bytes(d)==sourceBefore && bytes(*destination)==destinationBefore && report==old,"building failure preserves all outputs and input");
}
void buildingsDeleteAndDemolish() {
    std::vector<uint8_t> globalState(sizeof(gs)), globalMisc(sizeof(gg));
    std::memcpy(globalState.data(),&gs,sizeof(gs)); std::memcpy(globalMisc.data(),&gg,sizeof(gg));
    const auto seed=rtl::seed(), seedHi=rtl::seedHi();
    auto source=fixture();
    auto& housing=addBuilding(*source,1); housing.task[1]=20; housing.labor[1]=2;
    auto& factory=addBuilding(*source,5,14); const auto id=factory.id; factory.task[1]=12; factory.labor[1]=3;
    const auto survivor=addBuilding(*source,29,35).id;
    auto& t=source->territories[0].data;
    for (int site:{14,15,8,9}) { t.sites[site].terrainFlags=0x4a83; t.sites[site].unk_05[11]=0xa5; }
    source->ministerJobs[0][0].type=3; source->ministerJobs[0][0].param[0]=1; source->ministerJobs[0][0].param[1]=14;
    auto deleted=removeB(*source,id);
    require(deleted.doc->buildings.size()==2 && deleted.doc->buildings[0].next.raw==survivor &&
            deleted.doc->buildingById(survivor)->prev.raw==50000 && deleted.report.removedIds==std::vector<uint32_t>{id} &&
            deleted.report.deferredBuildJobs==1 && !deleted.report.localLaborBalanced,"Delete unlinks only requested building, preserves location minister job");
    for (int site:{14,15,8,9}) require(deleted.doc->territories[0].data.sites[site].terrainFlags==0x83 &&
            deleted.doc->territories[0].data.sites[site].unk_05[11]==0xa5,"Delete clears footprint high byte but not roads");
    require(deleted.doc->buildings[0].labor[1]==2 && deleted.doc->players[0].credits==source->players[0].credits &&
            deleted.doc->territories[0].data.materials[2]==20000,"bare Delete performs no refunds, balance or stock clamp");
    auto demolished=removeB(*source,id,BuildingRemovalKind::DemolishBuilding,1);
    require(demolished.report.credits==25 && demolished.doc->players[1].credits==25 && demolished.doc->players[0].credits==0 &&
            demolished.doc->buildings[0].labor[1]==5 && demolished.report.localLaborBalanced && demolished.report.originalRoadsTargetWasSentinel,
            "Demolish farm refunds explicit player (not owner), balances freed workers locally, preserves original sentinel-road target");
    for (int site:{14,15,8,9}) require(demolished.doc->territories[0].data.sites[site].unk_05[11]==0xa5,"Demolish does not silently fix original dangling-read roads bug");
    require(std::memcmp(&demolished.doc->territories[1].data,&source->territories[1].data,sizeof(Territory))==0 &&
            demolished.doc->territories[0].data.materials[2]==20000,"Demolish touches no other territory or stock cap");
    rejectB(*source,{id,BuildingRemovalKind::DemolishBuilding,-1}); rejectB(*source,{999,BuildingRemovalKind::DeleteBuilding,-1});

    source=fixture(); auto& incomplete=addBuilding(*source,29); incomplete.flags=4; incomplete.cost[0]=-3;
    incomplete.cost[1]=131071; incomplete.cost[2]=std::numeric_limits<int32_t>::min(); incomplete.cost[3]=65536;
    const auto incompleteId=incomplete.id;
    auto paid=removeB(*source,incompleteId,BuildingRemovalKind::DemolishBuilding,0);
    require(paid.report.credits==-2 && paid.report.materials[0]==-1 && paid.report.materials[1]==0 && paid.report.materials[2]==-32768,
            "uncovered building uses paid costs with SAR1 then signed16, including negative and overflow edges");
    source->buildings[0].flags=6; source->players[0].credits=std::numeric_limits<int32_t>::max();
    auto canonical=removeB(*source,incompleteId,BuildingRemovalKind::DemolishBuilding,0);
    require(canonical.report.credits==37 && canonical.report.materials[3]==7 &&
            canonical.doc->players[0].credits==std::bit_cast<int32_t>(0x80000024u),"built defense uses canonical75/15 costs and wrap32 credit addition");
    for (int level:{-1,0,1,2,32767}) {
        source=fixture(); auto& city=addBuilding(*source,37,14); city.hubLevel=int16_t(level);
        auto out=removeB(*source,city.id,BuildingRemovalKind::DemolishBuilding,0);
        const int32_t cost=level<1?125:500*level;
        const auto expected=std::bit_cast<int16_t>(uint16_t(uint32_t(cost)>>1));
        require(out.report.credits==expected && out.report.materials[1]==(level<1?25:std::bit_cast<int16_t>(uint16_t(25*level))),
                "CityCenter refund uses stored signed hub level, only money quartered for first center");
    }
    source=fixture(); auto& shrine=addBuilding(*source,46); source->territories[0].data.flags|=0x10;
    rejectB(*source,{shrine.id,BuildingRemovalKind::DemolishBuilding,0});
    auto shrineDeleted=removeB(*source,shrine.id);
    require(shrineDeleted.doc->territories[0].data.flags&0x10,"bare Delete shrine does not perform Demolish campaign/flag effect");
    source=fixture(); auto& offGrid=addBuilding(*source,5,0); rejectB(*source,{offGrid.id,BuildingRemovalKind::DeleteBuilding,-1});

    source=fixture(); BuildingCreationReport built; save::Error error;
    require(createCompletedBuilding(*source,{2,38,25},*source,built,error),"prepare platform and companion for deletion");
    const auto platformId=built.buildingId, habId=built.companionBuildingId;
    auto platformDeleted=removeB(*source,platformId);
    require(platformDeleted.doc->buildingById(habId) && platformDeleted.doc->territories[1].data.sites[15].building.raw==habId &&
            platformDeleted.doc->territories[1].data.sites[15].terrainFlags==1 && platformDeleted.report.removedIds.size()==1,
            "Delete platform clears5x5 but deliberately does not cascade to its SeaHab anchor");
    auto habDeleted=removeB(*source,habId);
    require(habDeleted.doc->territories[1].data.sites[15].terrainFlags==0x5101 && habDeleted.doc->buildingById(platformId),
            "Delete SeaHab restores platform center socket");
    const int sockets[]={3,13,17,27}; const uint16_t restored[]={0x3101,0x1101,0x4101,0x2101};
    for (size_t i=0;i<4;++i) {
        auto trial=std::make_unique<save::Document>(*source);
        require(createCompletedBuilding(*trial,{2,19,sockets[i]},*trial,built,error),"socket building created");
        auto out=removeB(*trial,built.buildingId);
        require(out.doc->territories[1].data.sites[sockets[i]].terrainFlags==restored[i],"exact platform removal switch restores each sparse socket");
    }
    auto& odd=addBuilding(*source,19,0,2); const auto oddId=odd.id; source->territories[1].data.sites[0].terrainFlags=0x9201;
    auto defaultSocket=removeB(*source,oddId);
    require(defaultSocket.doc->territories[1].data.sites[0].terrainFlags==0x9201,"platform switch default preserves unusual high flags");
    require(std::memcmp(globalState.data(),&gs,sizeof(gs))==0 && std::memcmp(globalMisc.data(),&gg,sizeof(gg))==0 &&
            rtl::seed()==seed && rtl::seedHi()==seedHi,"building lifecycle never touches globals or either RNG word");
}

void runtimeBuildingLifecycle() {
    auto source=fixture(); const auto oldId=addBuilding(*source,29).id; const auto before=bytes(*source);
    runtime::State state; save::Error error; require(state.prepare(*source,error),"runtime building fixture prepares");
    const auto old=state.buildingById(oldId); const auto territory=state.territoryByIndex(2); const auto rng=state.sessionRng();
    runtime::BuildingHandle platform; BuildingCreationReport created;
    require(state.createCompletedBuilding({2,38,25},platform,created,error),"runtime creates platform plus companion");
    const auto hab=state.buildingById(created.companionBuildingId);
    require(state.building(platform) && state.building(hab) && state.building(old) &&
            state.buildingLinks(platform)->next==hab && state.buildingLinks(hab)->previous==platform &&
            state.buildingLinks(platform)->territory==territory,"both special creations have owned stable registry handles and graph links");
    BuildingLifecycleReport removed;
    require(state.removeBuilding(platform,BuildingRemovalKind::DeleteBuilding,-1,removed,error) && !state.building(platform) &&
            state.building(hab) && state.building(old) && state.buildingLinks(old)->next==hab,"platform retirement invalidates only itself and preserves companion lifetime");
    const auto after=bytes(*state.document()); const auto prior=removed;
    require(!state.removeBuilding(platform,BuildingRemovalKind::DeleteBuilding,-1,removed,error) && removed==prior && bytes(*state.document())==after,
            "stale building handle rejection leaves state and report intact");
    require(!state.removeBuilding(hab,BuildingRemovalKind::DemolishBuilding,-1,removed,error) && removed==prior && bytes(*state.document())==after,
            "failed demolition preserves lifetime, bytes and report");
    require(state.removeBuilding(hab,BuildingRemovalKind::DemolishBuilding,0,removed,error) && !state.building(hab) && state.building(old) &&
            removed.originalRoadsTargetWasSentinel && state.sessionRng()==rng,"runtime demolition transfers refunds/labor and invalidates only retired lifetime without RNG");
    auto output=fixture(); const auto outputBefore=bytes(*output);
    require(!state.capture(*output,error) && bytes(*output)==outputBefore && !state.advanceTurn(error) && bytes(*source)==before,
            "completed entity lifecycle remains nonexportable and caller source stays exact");
}

void corpus(const std::filesystem::path& directory) {
    namespace fs=std::filesystem; if (directory.empty()) return;
    size_t documents=0,created=0,removed=0;
    const auto inspect=[&](const save::Document& d) {
        ++documents; const auto before=bytes(d);
        for (const auto& t:d.territories) {
            if (!t.data.terrain || t.data.owner<0 || d.players[size_t(t.data.owner)].race<0 || d.players[size_t(t.data.owner)].race>=7) continue;
            auto out=std::make_unique<save::Document>(d); ArmyLifecycleReport report; save::Error error;
            if (createArmy(d,{t.data.index,t.data.owner,37},{},*out,report,error)) { ++created; require(out->armyById(report.primaryId)!=nullptr,"corpus created ID resolves"); }
            else require(bytes(*out)==before && report==ArmyLifecycleReport{},"corpus create refusal has no partial output");
            break;
        }
        if (!d.armies.empty()) {
            auto out=std::make_unique<save::Document>(d); ArmyLifecycleReport report; save::Error error;
            if (removeArmy(d,{d.armies.front().id,ArmyRemovalKind::DeleteUnit,true},*out,report,error)) { ++removed; require(!out->armyById(d.armies.front().id),"corpus removed ID is absent"); }
            else require(bytes(*out)==before && report==ArmyLifecycleReport{},"corpus removal refusal preserves full candidate");
        }
        require(bytes(d)==before,"all original corpus data remains unchanged");
    };
    for (const char* name:{"TUTORIAL.SAV","Saves/AUTOSAVE.SAV","Campaign/AUTOSAVE.CPN","Campaign/ChCht001.CPN"}) if (fs::is_regular_file(directory/name)) {
        auto d=std::make_unique<save::Document>(); save::Error error;
        if (!save::readDocument(directory/name,*d,error)) throw std::runtime_error(error.message); inspect(*d);
    }
    if (fs::is_regular_file(directory/"LEVELS.HDX") && fs::is_regular_file(directory/"LEVELS.HDD")) {
        HdxArchive archive; std::string error;
        if (!archive.open((directory/"LEVELS").string(),&error)) throw std::runtime_error(error);
        for (const auto& entry:archive.entries()) {
            auto d=std::make_unique<save::Document>(); save::Error why;
            if (!save::readScenario(directory/"LEVELS",entry.name,*d,why)) throw std::runtime_error(why.message); inspect(*d);
        }
    }
    std::cout<<"lifecycle optional corpus: "<<documents<<" documents, "<<created<<" creations, "<<removed<<" removals\n";
    require(!documents || created>0,"corpus exercises supported creation");
}
} // namespace
int main(int argc,char** argv) {
    try {
        creationAndQueries(); carriersAndSiege(); jobsAndDeferredMinisters(); disbandRefundsAndColonizers(); capacityFailuresAndPurity(); runtimeIntegration();
        buildingsDeleteAndDemolish(); runtimeBuildingLifecycle();
        corpus(argc>1?std::filesystem::path(argv[1]):std::filesystem::path{});
        std::cout<<"entity_lifecycle: creation, carriers/siege, stacking, taskforces, delete/disband and rollback passed\n"; return 0;
    } catch (const std::exception& error) { std::cerr<<"entity_lifecycle: "<<error.what()<<'\n'; return 1; }
}
