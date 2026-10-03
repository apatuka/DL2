// Source/assembly-derived integer oracles; not an original EXE replay.
#include "game/population_orders.h"
#include "game/data_tables.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include "game/save_files.h"
#include <cstring>
#include <filesystem>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>

namespace {
using namespace dl2;
using namespace dl2::simulation;
void require(bool value,const char* why) { if (!value) throw std::runtime_error(why); }
void ok(bool value,const save::Error& error) { if (!value) throw std::runtime_error(error.message); }
Territory& t(save::Document& d,int index) { return d.territories[size_t(index-1)].data; }
const Territory& t(const save::Document& d,int index) { return d.territories[size_t(index-1)].data; }
Building& b(save::Document& d,uint32_t id) { for (auto& item:d.buildings) if (item.id==id) return item; throw std::runtime_error("fixture building missing"); }
uint32_t building(save::Document& d,int territory,int site,int type=2) {
    Building b{}; b.id=uint16_t(100+d.buildings.size()); b.type=uint8_t(type); b.category=data::kBuildingTypes[type].category;
    b.race=2; b.territory=int16_t(territory); b.site=int8_t(site); b.flags=6; b.task[1]=20;
    if (!d.buildings.empty()) { b.prev.raw=d.buildings.back().id; d.buildings.back().next.raw=b.id; }
    t(d,territory).sites[site].building.raw=b.id; d.buildings.push_back(b); return b.id;
}
std::unique_ptr<save::Document> fixture() {
    auto d=std::make_unique<save::Document>(); std::memcpy(d->header.text,save::kHeaderText,sizeof(save::kHeaderText)); d->header.version=kSaveVersion;
    d->world.width=3; d->world.height=1; d->world.numTerritories=3; d->territories.resize(3); d->tiles.resize(3);
    d->options.numPlayers=2; d->options.localPlayer=0; d->options.turn=17; d->options.nextGlobalId=600;
    for (size_t p=0;p<7;++p) { d->players[p].index=uint8_t(p); d->players[p].type=p?3:1; d->players[p].race=2; d->players[p].credits=1000;
        d->ministerJobs[p].resize(1); d->ministerJobs[p][0].type=1; }
    d->raceStats.v[24][2]=100;
    for (int i=0;i<3;++i) { auto& region=t(*d,i+1); region.index=uint16_t(i+1); region.owner=0; region.terrain=1;
        region.population=i?100:1000; region.morale=int8_t(i?20:80); region.numTiles=1; region.tiles[0].raw=uint32_t(i); region.knowledge=100;
        std::memcpy(region.name,"Alpha",6); region.materials[1]=20000; d->tiles[size_t(i)].x=uint8_t(i); d->tiles[size_t(i)].territory=int16_t(i+1);
        for (int s=0;s<36;++s) { region.sites[s].unk_00=uint16_t(s%6+256*(s/6)); region.sites[s].terrainFlags=1; }
    }
    building(*d,1,0); building(*d,2,0); b(*d,100).labor[1]=8; b(*d,101).labor[1]=1;
    d->localList={0,255,128}; d->events.resize(1); d->events[0].text={'x',0,255}; d->events[0].record.textLen=3; d->options.eventCount=1;
    return d;
}
std::vector<uint8_t> bytes(const save::Document& d) {
    save::Error e; std::vector<uint8_t> out; ok(save::encode(d,out,e),e);
    for (const auto& region:d.territories) { const auto* p=reinterpret_cast<const uint8_t*>(&region.data);
        out.insert(out.end(),p+kTerritorySavedBytes,p+sizeof(Territory)); }
    return out;
}
struct Outcome { std::unique_ptr<save::Document> d=fixture(); PopulationMoveReport r; };
Outcome run(const save::Document& d,PopulationMoveRequest request={1,2,100,0,-1,-1},PopulationMoveContext context={},int actor=-99) {
    const auto original=bytes(d); const auto oldContext=context; Outcome out; save::Error e{save::ErrorCode::Io,9,"old"};
    auto invoke=[&](const save::Document& source,save::Document& destination,PopulationMoveReport& report) {
        return actor==-99?movePopulationOffline(source,request,context,destination,report,e):commandMovePopulation(source,actor,request,context,destination,report,e);
    };
    ok(invoke(d,*out.d,out.r),e); require(e.code==save::ErrorCode::None && !e.offset && e.message.empty(),"population order clears prior error");
    require(bytes(d)==original && context==oldContext,"population order does not mutate source/context");
    auto alias=std::make_unique<save::Document>(d); PopulationMoveReport repeated; ok(invoke(*alias,*alias,repeated),e);
    require(bytes(*alias)==bytes(*out.d) && repeated==out.r,"population order alias replay differs");
    require(out.d->options.turn==d.options.turn && out.d->options.nextGlobalId==d.options.nextGlobalId && out.d->localList==d.localList &&
            out.d->events[0].text==d.events[0].text && t(*out.d,1).materials[1]==20000,"no turn, IDs, event text, binary local queue or material cap side effects");
    return out;
}
void ordinary() {
    auto d=fixture(); auto out=run(*d);
    require(out.r.nativeResult && out.r.denial==PopulationMoveDenial::None && out.r.fee==25 && out.r.capacity==1000 &&
            out.r.before==PopulationMoveState{1000,1000,100,80,20} && out.r.after==PopulationMoveState{975,900,200,80,50},
            "100 people cost25 and weighted morale(100*20+100*80)/200=50");
    require(out.r.balancedTerritories==std::vector<uint32_t>({1,2}) && b(*out.d,100).labor[1]==7 && b(*out.d,101).labor[1]==1,
            "balance source then destination with morale-adjusted labor7/1");
    for (int mode:{1,-1,INT32_MIN,INT32_MAX}) { auto alternative=run(*d,{1,2,100,mode,-1,-1});
        require(bytes(*alternative.d)==bytes(*out.d) && alternative.r==out.r,"0044c238 mode0 is the same BalanceLabor as every nonzero mode"); }
    auto zero=run(*d,{1,2,0,0,-1,99}); require(zero.r.nativeResult && zero.r.fee==0 && zero.r.after.toMorale==20 &&
            zero.r.balancedTerritories==std::vector<uint32_t>({1,2}),"zero amount is valid and fromSite-1 ignores unread fromSlot99");
    for (auto pair:{std::pair{1,1},std::pair{4,1},std::pair{5,2},std::pair{99,25},std::pair{101,26}}) {
        auto amount=run(*d,{1,2,pair.first,0,-1,-1}); require(amount.r.nativeResult && amount.r.fee==pair.second,"fee rounds positive amount upward in quarters");
    }
    d->players[0].credits=25; out=run(*d); require(out.r.nativeResult && out.d->players[0].credits==0,"exact fee equality accepted");
    d=fixture(); t(*d,1).population=100; out=run(*d); require(out.r.nativeResult && t(*out.d,1).population==0 && t(*out.d,1).morale==100,"empty source gets morale100 from balance, not weighted formula");
    d=fixture(); t(*d,2).population=900; out=run(*d); require(out.r.nativeResult && out.r.after.toPopulation==1000,"exact destination capacity accepted");
}
void denialsAndCommand() {
    auto d=fixture(); auto deny=[&](PopulationMoveRequest request,PopulationMoveDenial reason) {
        const auto before=bytes(*d); auto out=run(*d,request); require(!out.r.nativeResult && out.r.denial==reason && bytes(*out.d)==before,"ordinary denial is evaluated with no mutation");
    };
    t(*d,1).owner=-1; deny({1,1,100,0,-1,-1},PopulationMoveDenial::Unowned); // Ownership check precedes identity.
    d=fixture(); deny({1,1,100,0,-1,-1},PopulationMoveDenial::SameTerritory);
    t(*d,2).owner=1; deny({1,2,100,0,-1,-1},PopulationMoveDenial::DifferentOwner);
    d=fixture(); d->players[0].credits=24; deny({1,2,100,0,-1,-1},PopulationMoveDenial::Credits);
    d=fixture(); deny({1,2,1001,0,-1,-1},PopulationMoveDenial::Population);
    t(*d,2).population=901; deny({1,2,100,0,-1,-1},PopulationMoveDenial::Capacity);
    d=fixture(); b(*d,101).category=1; deny({1,2,100,0,-1,-1},PopulationMoveDenial::NoHousing); // Type still contributes capacity but no category17.
    d=fixture(); for (int s=3;s<36;++s) t(*d,2).sites[s].terrainFlags=5; t(*d,2).population=350;
    deny({1,2,51,0,-1,-1},PopulationMoveDenial::Capacity); auto out=run(*d,{1,2,50,0,-1,-1});
    require(out.r.capacity==400 && out.r.nativeResult,"three usable sites give landcap400 despite housing1000");
    d=fixture(); const auto before=bytes(*d); out=run(*d,{1,2,100,0,-1,-1},{},1);
    require(out.r.denial==PopulationMoveDenial::NotLocalActor && bytes(*out.d)==before,"checked command rejects nonlocal actor");
    out=run(*d,{1,2,100,0,-1,-1},{},0); require(out.r.nativeResult,"checked local owner allowed");
    t(*d,1).owner=t(*d,2).owner=1; out=run(*d,{1,2,100,0,-1,-1},{},0);
    require(out.r.denial==PopulationMoveDenial::NotLocalActor,"local actor cannot move another owner's population");
    out=run(*d); require(out.r.nativeResult && out.d->players[1].credits==975,"low-level original leaf supports nonlocal owner with no invented actor/UI/RNG restriction");
}
void signedArithmetic() {
    auto d=fixture(); t(*d,2).population=300; auto out=run(*d,{1,2,-100,0,-1,-1});
    require(out.r.nativeResult && out.r.fee==-24 && out.r.after==PopulationMoveState{1024,1100,200,80,-10},
            "negative amount credits24, signed populations and weighted morale-10 are preserved");
    out=run(*d,{1,2,-3,0,-1,-1}); require(out.r.fee==0 && out.r.after.fromPopulation==1003 && out.r.after.toPopulation==297,"negative amount-3 fee0, not a positivity clamp");
    out=run(*d,{1,2,-7,0,-1,-1}); require(out.r.fee==-1,"negative fee truncates toward zero after+3");
    d=fixture(); out=run(*d,{1,2,INT32_MIN,0,-1,-1});
    require(out.r.nativeResult && out.r.fee==-536870911 && out.r.after.credits==536871911 && out.r.after.fromPopulation==1000 &&
            out.r.after.toPopulation==100 && out.r.after.toMorale==0,"INT_MIN full-width fee/morale but low16 population, without C++ overflow");
    out=run(*d,{1,2,INT32_MAX,0,-1,-1});
    require(!out.r.nativeResult && out.r.denial==PopulationMoveDenial::Population && out.r.fee==-536870911,"INT_MAX fee uses wrapped+3/+6 before native population denial");
    d=fixture(); t(*d,1).population=32767; out=run(*d,{1,2,-32768,0,-1,-1});
    require(out.r.nativeResult && out.r.after.fromPopulation==-1 && out.r.after.toPopulation==-32668,"signed16 population narrowing wraps source32767-(-32768) to-1");
    d=fixture(); b(*d,101).flags=0; b(*d,101).turnsLeft=9;
    out=run(*d,{1,2,-200,0,-1,-1}); require(out.r.nativeResult && out.r.capacity==0 && out.r.after.toPopulation==-100 && out.r.after.toMorale==-116,
            "category17 existence has no Active/Built/completed check; weighted140 narrows to signedbyte-116");
}
void sourceLaborAndPartialReturn() {
    auto d=fixture(); b(*d,100).flags|=0x200; auto out=run(*d,{1,2,100,0,0,1});
    require(out.r.nativeResult && out.r.adjustedLabor && out.r.nativeLaborResult && b(*out.d,100).labor[1]==7 && (b(*out.d,100).flags&0x200) &&
            out.r.balancedTerritories==std::vector<uint32_t>{2},"explicit slot subtracts1 even locked; source is NOT balanced or unlocked");
    out=run(*d,{1,2,900,0,0,1}); require(out.r.nativeResult && !out.r.adjustedLabor && b(*out.d,100).labor[1]==8,"insufficient chosen labor skips removal but population/payment still occur");
    d=fixture(); out=run(*d,{1,2,100,0,0,-1});
    require(out.r.adjustedLabor && out.r.nativeLaborResult && b(*out.d,100).labor[1]==7,"whole-building removal uses exact0044bddc selector");
    b(*d,100).flags|=0x200; out=run(*d,{1,2,100,0,0,-1});
    require(out.r.nativeResult && out.r.adjustedLabor && !out.r.nativeLaborResult && b(*out.d,100).labor[1]==8,"ignored native labor failure when all tasks locked does not undo population move");
    d=fixture(); out=run(*d,{1,2,99,0,0,-1});
    require(out.r.nativeResult && out.r.adjustedLabor && !out.r.nativeLaborResult && b(*out.d,100).labor[1]==8,"amount99 calls AdjustLabor0 returningfalse, still native population success");
    d=fixture(); t(*d,2).population=300; out=run(*d,{1,2,-100,0,0,1});
    require(b(*out.d,100).labor[1]==9 && out.r.nativeLaborResult,"negative transfer adds labor to explicit slot and leaves source unbalanced");
    out=run(*d,{1,2,-100,0,0,-1}); require(b(*out.d,100).labor[1]==9 && out.r.nativeLaborResult,"negative transfer invokes positive AdjustLabor through unlocked selector");
    d=fixture(); out=run(*d,{1,2,100,0,35,-1});
    require(!out.r.nativeResult && out.r.denial==PopulationMoveDenial::MissingSourceBuildingAfterTransfer && out.r.after==PopulationMoveState{975,900,200,80,50} &&
            out.r.balancedTerritories.empty() && b(*out.d,100).labor[1]==8,"missing source building returnsfalse AFTER committing cost/morale/pop, without either balance");
}
void plagueAndBindings() {
    auto d=fixture(); t(*d,1).flags|=0x20; d->randomEvents[0].type=8; d->randomEvents[0].unk_04=0x5a4eac;
    d->randomEvents[1].unk_04=0x123456; d->randomEvents[1].turnsLeft=29; d->randomEvents[1].unk_0c[2]=77;
    auto out=run(*d);
    require(out.r.plagueAttempted && out.r.scheduledPlague==PlagueSchedule{1,2,-4} && out.r.bindingsAfter[1]==2 &&
            out.d->randomEvents[1].type==1 && out.d->randomEvents[1].unk_04==0 && out.d->randomEvents[1].turnsLeft==-4 && out.d->randomEvents[1].unk_0c[2]==77,
            "first free event stores delayed plague-4, retains tail, target in owned sidecar instead of native address");
    require(!std::memcmp(&d->randomEvents[0],&out.d->randomEvents[0],sizeof(RandomEvent)) &&
            !std::memcmp(&d->spies,&out.d->spies,sizeof(d->spies)) && !(t(*out.d,2).flags&0x20),"existing native event bytes and spies untouched; scheduling does not start plague or set destflag");
    PopulationMoveContext continuation{out.r.bindingsAfter}; auto next=run(*out.d,{1,2,0,0,-1,-1},continuation);
    require(next.r.scheduledPlague==PlagueSchedule{2,2,-4} && next.r.bindingsAfter[1]==2 && next.r.bindingsAfter[2]==2,"zero amount STILL schedules plague; continuation retains previous binding without deduplicating");
    out=run(*d,{1,2,100,0,35,-1}); require(!out.r.nativeResult && out.r.scheduledPlague==PlagueSchedule{1,2,-4} && out.r.bindingsAfter[1]==2,
            "native false-after-transfer retains scheduled plague metadata");
    d=fixture(); t(*d,1).flags|=0x20; for (size_t i=0;i+1<d->randomEvents.size();++i) d->randomEvents[i].type=8;
    out=run(*d); require(out.r.scheduledPlague==PlagueSchedule{24,2,-4},"last owned slot24 is usable, not reserved");
}
void failures() {
    auto d=fixture(), destination=fixture(); destination->options.turn=99; PopulationMoveReport r; r.fee=777; const auto old=r;
    const auto previous=bytes(*destination); save::Error e; PopulationMoveContext c;
    auto fails=[&](PopulationMoveRequest request) { const auto source=bytes(*d); require(!movePopulationOffline(*d,request,c,*destination,r,e) &&
        bytes(*d)==source && bytes(*destination)==previous && r==old,"unsafe population branch must roll back document/report/context"); };
    fails({1,2,-100,0,-1,-1}); require(e.message.find("division")!=std::string::npos,"zero weighted denominator diagnosed");
    fails({0,2,100,0,-1,-1}); fails({1,2,100,0,36,-1}); fails({1,2,100,0,0,5}); fails({1,2,100,0,-2,-1});
    t(*d,1).owner=t(*d,2).owner=7; fails({1,2,100,0,-1,-1});
    d=fixture(); t(*d,1).flags|=0x20; for (auto& event:d->randomEvents) event.type=8;
    fails({1,2,100,0,-1,-1}); require(e.code==save::ErrorCode::Limit && e.message.find("Spies")!=std::string::npos,"25 full slots reject native out-of-owned-pool scan explicitly");
    d=fixture(); c.bindings[0]=2; fails({1,2,100,0,-1,-1});
    d->randomEvents[0].type=1; d->randomEvents[0].unk_04=123; fails({1,2,100,0,-1,-1});
    d->randomEvents[0].unk_04=0; c.bindings[0]=99; fails({1,2,100,0,-1,-1});
    c={}; d=fixture(); b(*d,101).task[1]=0; b(*d,101).labor[1]=0;
    fails({1,2,100,0,-1,-1}); require(e.message.find("fallback")!=std::string::npos,"late destination balance failure reverts earlier source balance/payment/morale");
    d=fixture(); b(*d,100).task[1]=0; b(*d,100).task[0]=1; b(*d,100).labor[1]=8; // Total8, but only selectable task has0 workers.
    fails({1,2,100,0,0,-1}); require(e.code==save::ErrorCode::Limit,"native removal nonprogressing loop is bounded and whole transfer rolls back");
}
void corpus(const std::filesystem::path& directory) {
    if (directory.empty()) return;
    size_t checked=0;
    for (const char* name:{"TUTORIAL.SAV","Saves/AUTOSAVE.SAV","Campaign/AUTOSAVE.CPN","Campaign/ChCht001.CPN"}) {
        const auto path=directory/name; if (!std::filesystem::is_regular_file(path)) continue;
        auto d=std::make_unique<save::Document>(); save::Error e; ok(save::readDocument(path,*d,e),e); const auto before=bytes(*d);
        const auto& first=d->territories[0].data; auto output=std::make_unique<save::Document>(); PopulationMoveReport report;
        // Same-territory is an original evaluated denial before capacity/labor.
        ok(movePopulationOffline(*d,{1,1,100,0,-1,-1},{},*output,report,e),e);
        require(!report.nativeResult && report.denial==(first.owner==-1?PopulationMoveDenial::Unowned:PopulationMoveDenial::SameTerritory) &&
                bytes(*d)==before && bytes(*output)==before,"archival corpus denial preserves every byte and unknown reference"); ++checked;
    }
    std::cout<<"population_orders: "<<checked<<" archival corpus denial variants\n";
}
}
int main(int argc,char** argv) {
    try {
        std::vector<uint8_t> game(sizeof(gs)),global(sizeof(gg)); std::memcpy(game.data(),&gs,sizeof(gs)); std::memcpy(global.data(),&gg,sizeof(gg));
        const auto low=rtl::seed(),high=rtl::seedHi(); ordinary(); denialsAndCommand(); signedArithmetic(); sourceLaborAndPartialReturn(); plagueAndBindings(); failures();
        corpus(argc>1?std::filesystem::path(argv[1]):std::filesystem::path{});
        require(!std::memcmp(game.data(),&gs,sizeof(gs)) && !std::memcmp(global.data(),&gg,sizeof(gg)) && low==rtl::seed() && high==rtl::seedHi(),"population orders alter legacy globals or RNG");
        std::cout<<"population_orders: native arithmetic/denials/partial return, owned plague, labor and atomic rollback passed\n"; return 0;
    } catch (const std::exception& e) { std::cerr<<"population_orders: "<<e.what()<<'\n'; return 1; }
}
