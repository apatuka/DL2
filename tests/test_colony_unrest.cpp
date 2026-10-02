// Paper/assembly oracles for0046c49c/0046c310/0046c254. No original EXE replay.
#include "game/colony_unrest.h"
#include "game/data_tables.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include <algorithm>
#include <cstring>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

namespace {
using namespace dl2;
using namespace dl2::simulation;
void require(bool value,const char* why) { if (!value) throw std::runtime_error(why); }
void ok(bool value,const save::Error& error) { if (!value) throw std::runtime_error(error.message); }
std::unique_ptr<save::Document> fixture(int count=3) {
    auto d=std::make_unique<save::Document>();
    std::memcpy(d->header.text,save::kHeaderText,sizeof(save::kHeaderText)); d->header.version=kSaveVersion;
    d->world.width=uint8_t(count); d->world.height=1; d->world.numTerritories=uint16_t(count);
    d->territories.resize(size_t(count)); d->tiles.resize(size_t(count));
    d->options.numPlayers=2; d->options.localPlayer=0; d->options.turn=19; d->options.nextGlobalId=500;
    for (size_t p=0;p<7;++p) {
        d->players[p].index=uint8_t(p); d->players[p].race=2; d->players[p].type=p?3:1; d->players[p].taxLevel=2;
        d->ministerJobs[p].resize(1); d->ministerJobs[p][0].type=1;
    }
    d->raceStats.v[24][2]=100; d->raceStats.v[27][2]=20;
    for (int i=0;i<count;++i) {
        auto& t=d->territories[size_t(i)].data; t.index=uint16_t(i+1); t.owner=i?-1:0;
        t.population=1000; t.morale=50; t.terrain=1; t.knowledge=100; t.numTiles=1; t.tiles[0].raw=uint32_t(i);
        std::memcpy(t.name,i?"Beta":"Alpha",i?5:6); t.flags=0x40000000u;
        d->tiles[size_t(i)].x=uint8_t(i); d->tiles[size_t(i)].territory=int16_t(i+1);
        for (int s=0;s<36;++s) { t.sites[s].unk_00=uint16_t(s%6+256*(s/6)); t.sites[s].terrainFlags=1; }
    }
    d->localList={0,0xff,0x80}; // Never treated as text or normalized by unrest.
    return d;
}
Territory& t(save::Document& d,int index=1) { return d.territories[size_t(index-1)].data; }
const Territory& t(const save::Document& d,int index=1) { return d.territories[size_t(index-1)].data; }
void edge(save::Document& d,int a,int b) {
    t(d,a).adjacency[b/16]|=uint16_t(1u<<(b%16)); t(d,b).adjacency[a/16]|=uint16_t(1u<<(a%16));
}
uint32_t building(save::Document& d,int type,int site,int territory=1,int work=0,uint16_t flags=0) {
    Building b{}; b.id=uint16_t(100+d.buildings.size()); b.type=uint8_t(type);
    b.category=data::kBuildingTypes[type].category; b.race=2; b.territory=int16_t(territory);
    b.site=int8_t(site); b.flags=flags; b.turnsLeft=int16_t(work); b.task[0]=21; b.labor[0]=3;
    if (!d.buildings.empty()) { b.prev.raw=d.buildings.back().id; d.buildings.back().next.raw=b.id; }
    t(d,territory).sites[site].building.raw=b.id; d.buildings.push_back(b); return b.id;
}
const Building& b(const save::Document& d,uint32_t id) {
    const auto* found=d.buildingById(id); if (!found) throw std::runtime_error("test building missing"); return *found;
}
void suppressor(save::Document& d,int territory=1) {
    Army a{}; a.id=uint16_t(300+d.armies.size()); a.type=1; a.unitClass=1; a.owner=t(d,territory).owner;
    a.strength=3; a.unk_25=13; a.territory.raw=a.dest.raw=a.origin.raw=uint32_t(territory);
    a.next.raw=t(d,territory).armies.raw;
    for (auto& other:d.armies) if (other.id==a.next.raw) other.prev.raw=a.id;
    t(d,territory).armies.raw=a.id; d.armies.push_back(a);
    // Canonical laser attack2 + (1000*2)/10 =202, larger than any range100.
    d.raceStats.v[29][2]=1000;
}
std::vector<uint8_t> bytes(const save::Document& d) {
    save::Error error; std::vector<uint8_t> out; ok(save::encode(d,out,error),error);
    for (const auto& r:d.territories) {
        const auto* start=reinterpret_cast<const uint8_t*>(&r.data);
        out.insert(out.end(),start+kTerritorySavedBytes,start+sizeof(Territory));
    }
    return out;
}
int16_t distance(const save::Document& d,int territory,int player) {
    int16_t n; std::memcpy(&n,reinterpret_cast<const uint8_t*>(&t(d,territory))+0xa70+player*2,2); return n;
}
ConstructionOrderContext context(uint32_t seed=0) {
    ConstructionOrderContext c; SessionRng rng; save::Error error; ok(rng.initialize(seed,error),error);
    c.ai.rng=c.events.rngBeforeEvents=c.log.rngAfterEvents=rng.snapshot(); return c;
}
struct Outcome { std::unique_ptr<save::Document> document=fixture(); ColonyUnrestReport report; };
Outcome run(const save::Document& source,ConstructionOrderContext c=context(),bool direct=false,int16_t deaths=0) {
    const auto before=bytes(source); const auto log=c.log; const auto ai=c.ai; const auto rng=c.events.rngBeforeEvents;
    Outcome result; save::Error error{save::ErrorCode::Io,99,"old"};
    const auto invoke=[&](const save::Document& in,save::Document& out,ColonyUnrestReport& report) {
        return direct?doColonyRiot(in,1,deaths,c,out,report,error):processColonyUnrest(in,1,c,out,report,error);
    };
    ok(invoke(source,*result.document,result.report),error);
    require(error.code==save::ErrorCode::None && error.offset==0 && error.message.empty(),"success clears previous error");
    require(bytes(source)==before && c.log==log && c.ai==ai && c.events.rngBeforeEvents==rng,"unrest preserves source and context");
    auto alias=std::make_unique<save::Document>(source); ColonyUnrestReport repeated;
    ok(invoke(*alias,*alias,repeated),error);
    require(bytes(*alias)==bytes(*result.document) && repeated==result.report,"alias/replay is byte-identical and deterministic");
    require(result.document->options.turn==source.options.turn && result.document->options.nextGlobalId==source.options.nextGlobalId &&
            result.document->localList==source.localList,"unrest never advances turn, allocates IDs, or edits binary localList");
    return result;
}
void directDamage() {
    auto d=fixture(); t(*d).morale=101; // unsigned (100-101)>>2 makes EVERY roll qualify.
    const auto a=building(*d,1,0,1,0,0), p=building(*d,38,1,1,-4,6);
    const auto z=building(*d,1,2,1,9,6), negative=building(*d,1,3,1,-10,0), city=building(*d,37,4);
    auto out=run(*d,context(),true,200);
    require(t(*out.document).population==800 && out.report.riotDeaths==200 && out.report.damage.size()==4,"direct riot subtracts signed deaths and skips platform damage");
    require(b(*out.document,a).turnsLeft==5 && b(*out.document,p).turnsLeft==-4 && b(*out.document,z).turnsLeft==10 &&
            b(*out.document,negative).turnsLeft==-5 && b(*out.document,city).turnsLeft==300,"canonical labor half/cap10 and city labor600 unaffected by money scaling");
    const std::vector<uint32_t> rolls{0,46,78,40,96};
    require(out.report.draws.size()==rolls.size(),"one DoRiot draw per occupied site including platform");
    for (size_t i=0;i<rolls.size();++i) require(out.report.draws[i].value==rolls[i] && out.report.draws[i].tag=="DoRiot" && out.report.draws[i].bound==100,"independent seed0 Long31 oracle including platform draw");
    require(out.report.events.size()==4 && std::all_of(out.report.events.begin(),out.report.events.end(),[](const auto& e){return e.type==83 && e.local;}),"real local damage event83 for each damaged building");
    for (const auto& original:d->buildings) {
        auto expected=original; expected.turnsLeft=b(*out.document,original.id).turnsLeft;
        require(!std::memcmp(&expected,&b(*out.document,original.id),sizeof(Building)),"damage changes only work, never flags/tasks/labor or links");
    }
    d=fixture(); t(*d).morale=100; const auto first=building(*d,1,0),second=building(*d,1,1);
    out=run(*d,context(),true);
    require(b(*out.document,first).turnsLeft==5 && b(*out.document,second).turnsLeft==0 && out.report.damage.size()==1,"threshold comparison is inclusive: morale100 roll0 hits, roll46 misses");
    d=fixture(); t(*d).population=100; out=run(*d,context(),true,200);
    require(t(*out.document).population==-100 && out.report.rngAfter==context().events.rngBeforeEvents,"population can become negative; no buildings means no RNG");
    t(*d).population=INT16_MIN; out=run(*d,context(),true,1); require(t(*out.document).population==INT16_MAX,"signed16 population subtraction wraps");
    t(*d).population=100; out=run(*d,context(),true,-50); require(t(*out.document).population==150,"negative signed deaths add population without clamp");
}
void branches() {
    auto d=fixture(); t(*d).population=0; auto out=run(*d);
    require(out.report.outcome==ColonyUnrestOutcome::Skipped && out.report.draws.empty() && out.report.rngAfter==context().events.rngBeforeEvents,"population0 skips all unrest work");
    t(*d).population=1000; t(*d).owner=-1; out=run(*d);
    require(out.report.outcome==ColonyUnrestOutcome::Skipped && out.report.draws.empty(),"unowned skips all unrest work");
    d=fixture(); out=run(*d);
    require(out.report.outcome==ColonyUnrestOutcome::Stable && out.report.draws.size()==1 && out.report.draws[0].value==0 && out.report.events.empty(),"normal morale still consumes initial Revolt draw");
    t(*d).morale=30; out=run(*d);
    require(out.report.outcome==ColonyUnrestOutcome::Unhappy && out.report.morale.total==30 && out.report.morale.baseline==30 &&
            out.report.events.size()==1 && out.report.events[0].type==88,"morale20..39 emits unhappy88 after raw total<=baseline");
    t(*d).materials[10]=1; out=run(*d);
    require(out.report.outcome==ColonyUnrestOutcome::Stable && out.report.morale.total==32 && out.report.events.empty(),"improving raw morale suppresses warnings");
    t(*d).materials[10]=0; t(*d).morale=10; out=run(*d);
    require(out.report.outcome==ColonyUnrestOutcome::Agitated && out.report.draws.size()==2 && out.report.draws[1].value==46 &&
            out.report.events.size()==1 && out.report.events[0].type==89,"seed0 Revolt3=46 exceeds threshold10, emits agitation89");
    t(*d).morale=-30; out=run(*d);
    require(out.report.outcome==ColonyUnrestOutcome::Riot && out.report.labor.available==1 && out.report.labor.unavailable==9 &&
            out.report.riotDeaths==450 && t(*out.document).population==550 && out.report.events.size()==1 && out.report.events[0].type==84,"signed morale-30 threshold50 hits roll46; unavailable9 kills450");
    d->raceStats.v[27][2]=0; out=run(*d);
    require(out.report.morale.total==80 && out.report.morale.baseline==80 && out.report.outcome==ColonyUnrestOutcome::Agitated,"zero racial morale ignores modifiers but signed morale still drives threshold0 test");
    d=fixture(); t(*d).morale=101; d->raceStats.v[27][2]=200; building(*d,1,0);
    out=run(*d);
    require(out.report.outcome==ColonyUnrestOutcome::Riot && out.report.events.size()==2 && out.report.events[0].type==84 && out.report.events[1].type==83 &&
            out.report.draws.size()==3 && out.report.draws[2].value==78 && out.report.damage.size()==1,"event84 precedes DoRiot and event83; portrait RNG does not perturb Long31");
}
void migration() {
    auto d=fixture(); t(*d).morale=0; t(*d,2).owner=t(*d,3).owner=1; edge(*d,1,3); edge(*d,1,2); suppressor(*d);
    d->techs[1].knownMask=1; AiSession ai; save::Error error; ok(ai.initializeAfterLoad(*d,error),error); auto c=context(); c.aiSession=&ai;
    auto out=run(*d,c);
    require(out.report.outcome==ColonyUnrestOutcome::Migrated && out.report.revoltStrength==202 && out.report.labor.unavailable==8 &&
            out.report.destination==2 && out.report.migrants==347 && out.report.technology==1,"seed0 Revolt2=346%800 yields347; equal-distance tie chooses lower territory");
    require(t(*out.document).population==653 && t(*out.document,2).population==1347 && t(*out.document,3).population==1000 &&
            t(*out.document).owner==0 && t(*out.document,2).owner==1,"migration moves signed populations only, without ownership transfer");
    require(out.report.draws.size()==3 && out.report.draws[0].tag=="Revolt" && out.report.draws[1].tag=="Revolt2" &&
            out.report.draws[1].value==346 && out.report.draws[2].tag=="Steal Tech" && out.report.draws[2].value==14,"steal RNG precedes event portraits and cycles from14 to eligibletech1");
    require(out.report.events.size()==3 && out.report.events[0].type==85 && out.report.events[0].local &&
            out.report.events[1].type==87 && out.report.events[1].aiDispatched && !out.report.events[1].aiReport.handled &&
            out.report.events[2].type==86 && out.report.events[2].aiDispatched && !out.report.events[2].aiReport.handled,"native85,87,86 order uses real default AI dispatch, not swapped IDs");
    require((out.document->techs[1].knownMask&2) && out.report.acquisition.acquisitions.size()==1 && out.report.acquisition.acquisitions[0].newlyKnown,"selected technology is actually acquired");
    require(distance(*out.document,1,0)==0 && distance(*out.document,2,0)==1 && distance(*out.document,3,0)==1 &&
            (t(*out.document,2).flags&0x2000) && (t(*out.document,2).flags&0x40000000u),"migration publishes original search distance and only owner mark bit");
    d->techs[1].knownMask=0; out=run(*d,c);
    require(out.report.technology==0 && out.report.events.size()==2 && (out.document->techs[0].knownMask&2) &&
            out.report.acquisition.acquisitions.size()==1 && out.report.acquisition.acquisitions[0].technology==0,"sentinel0 still calls AcquireTech0 and omits only event86");
    d->techs[0].knownMask=2; out=run(*d,c);
    require(!out.report.acquisition.acquisitions[0].newlyKnown,"already-known technology0 takes authentic acquisition early return");
    t(*d,2).population=32700; out=run(*d,c);
    require(t(*out.document,2).population==-32489 && out.report.destinationAfter==-32489,"destination population wraps signed16 with no invented capacity clamp");
    t(*d).population=50; out=run(*d,c);
    require(out.report.outcome==ColonyUnrestOutcome::MigrationAttempt && out.report.migrants==0 && out.report.destination==2 && out.report.draws.size()==2 &&
            distance(*out.document,2,0)==1 && out.report.events.empty(),"population50 still searches although migrants0; no steal/event/acquire");
}
void pathRules() {
    auto d=fixture(); t(*d).morale=0; t(*d,2).owner=t(*d,3).owner=1; suppressor(*d); edge(*d,1,2); edge(*d,1,3);
    // Remote human branch authentic return: no AI callback is needed.
    d->players[1].type=2; t(*d,2).flags|=0x100; auto out=run(*d);
    require(out.report.destination==3 && distance(*out.document,2,0)==1000,"excluded territory100 is neither visited nor selected");
    t(*d,2).flags&=~0x100u; d->options.allowAlliances=1; d->players[0].relations[1]=1; out=run(*d);
    require(out.report.outcome==ColonyUnrestOutcome::MigrationAttempt && out.report.destination==0 && out.report.draws.size()==2,"pact1 prevents entry to foreign territory");
    d->players[0].relations[1]=2; building(*d,37,0,2,0,0); out=run(*d);
    require(out.report.destination==3,"pact2 prevents entry to finished city even with Active/Built both off");
    d->players[0].relations[1]=0x10; out=run(*d); require(out.report.destination==2,"pact10 supplies pact2 but not pact1, bypasses city veto");
    d->players[0].relations[1]=0; t(*d,2).terrain=0; out=run(*d); require(out.report.destination==2,"mode3 crosses land/sea uniformly at unit cost");
    d=fixture(4); t(*d).morale=0; t(*d,2).owner=1; t(*d,3).owner=0; t(*d,4).owner=1; d->players[1].type=2;
    edge(*d,1,3); edge(*d,3,2); edge(*d,1,4); suppressor(*d); out=run(*d);
    require(out.report.destination==4 && distance(*out.document,2,0)==2 && distance(*out.document,4,0)==1,"strict shortest distance wins before territory index");
}
void rollbackAndWorld() {
    auto d=fixture(); auto output=fixture(); ColonyUnrestReport report; report.migrants=771; const auto previous=report; save::Error error;
    const auto before=bytes(*output); auto c=context();
    for (int owner:{-2,7}) { t(*d).owner=int8_t(owner); require(!processColonyUnrest(*d,1,c,*output,report,error) && report==previous && bytes(*output)==before,"invalid owner rejected transactionally"); }
    d=fixture(); t(*d).owner=1; t(*d).morale=101; building(*d,1,0);
    require(!doColonyRiot(*d,1,200,c,*output,report,error) && report==previous && bytes(*output)==before && error.message.find("AI")!=std::string::npos,"missing real AI binding rolls back prior population/building edits");
    d=fixture(); t(*d).morale=101; building(*d,1,0); std::memset(t(*d).name,'X',sizeof(t(*d).name));
    require(!doColonyRiot(*d,1,200,c,*output,report,error) && report==previous && bytes(*output)==before,"unterminated event name rolls back damage and population");
    d=fixture(); t(*d).owner=1; t(*d).morale=0; t(*d,2).owner=0; edge(*d,1,2); suppressor(*d);
    const auto input=bytes(*d);
    require(!processColonyUnrest(*d,1,c,*output,report,error) && report==previous && bytes(*output)==before && bytes(*d)==input &&
            error.message.find("undefined event87/86")!=std::string::npos,"native local-recipient varargs mismatch is explicit and fully transactional, not silently repaired");
    d=fixture(); t(*d).morale=0; t(*d,2).owner=1; suppressor(*d); t(*d).adjacency[0]|=1u<<7;
    require(!processColonyUnrest(*d,1,c,*output,report,error) && report==previous && bytes(*output)==before,"search refuses adjacency to absent native pool slot");
    d=fixture(); c.events.rngBeforeEvents.format=2;
    require(!processColonyUnrest(*d,1,c,*output,report,error) && report==previous && bytes(*output)==before,"invalid explicit RNG snapshot preserves outputs");
    c=context(); c.ai.rng=context(1).ai.rng;
    require(!processColonyUnrest(*d,1,c,*output,report,error) && report==previous && bytes(*output)==before,"mismatched AI/event streams rejected before any draw or silent normalization");
    WorldUnrestReport mismatch; mismatch.events.push_back({}); const auto mismatchBefore=mismatch;
    require(!processWorldUnrest(*d,c,*output,mismatch,error) && mismatch==mismatchBefore && bytes(*output)==before,"world continuation does not normalize incoherent input RNG");
    c=context(); t(*d).morale=30; t(*d,2).owner=0; t(*d,2).morale=30;
    WorldUnrestReport world; ok(processWorldUnrest(*d,c,*output,world,error),error);
    require(world.territories.size()==3 && world.territories[0].draws[0].value==0 && world.territories[1].draws[0].value==46 &&
            world.territories[2].outcome==ColonyUnrestOutcome::Skipped && world.events.size()==2 && world.events[0].type==88 && world.events[1].type==88,"world visits1..N with one continued stream, retaining skipped reports");
    auto alias=std::make_unique<save::Document>(*d); WorldUnrestReport duplicate;
    ok(processWorldUnrest(*alias,c,*alias,duplicate,error),error); require(bytes(*alias)==bytes(*output) && duplicate==world,"whole-world alias is deterministic");
    const auto oldWorld=world; const auto oldOutput=bytes(*output);
    t(*d,2).owner=1; t(*d,2).morale=0; suppressor(*d,2); edge(*d,1,2);
    require(!processWorldUnrest(*d,c,*output,world,error) && world==oldWorld && bytes(*output)==oldOutput &&
            error.message.find("undefined event87/86")!=std::string::npos,"late world migration failure also rolls back earlier warning/log/RNG");
}
}
int main() {
    try {
        std::vector<uint8_t> global(sizeof(gs)),runtime(sizeof(gg)); std::memcpy(global.data(),&gs,sizeof(gs)); std::memcpy(runtime.data(),&gg,sizeof(gg));
        const auto seed=rtl::seed(),high=rtl::seedHi();
        directDamage(); branches(); migration(); pathRules(); rollbackAndWorld();
        require(!std::memcmp(global.data(),&gs,sizeof(gs)) && !std::memcmp(runtime.data(),&gg,sizeof(gg)) && seed==rtl::seed() && high==rtl::seedHi(),"unrest leaves all legacy globals and process RNG untouched");
        std::cout<<"colony_unrest: exact riot/migration/events/RNG, path rules, signed arithmetic and atomic rollback passed\n"; return 0;
    } catch (const std::exception& error) { std::cerr<<"colony_unrest: "<<error.what()<<'\n'; return 1; }
}
