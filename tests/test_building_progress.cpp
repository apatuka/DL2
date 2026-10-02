// Original-function numeric oracles, not live DEADLOCK.EXE replay results.
#include "game/building_progress.h"
#include "game/data_tables.h"
#include "game/production_plan.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include <bit>
#include <cstring>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
using namespace dl2;
using namespace dl2::simulation;
void require(bool c,const char* text) { if (!c) throw std::runtime_error(text); }
std::unique_ptr<save::Document> fixture() {
    auto d=std::make_unique<save::Document>();
    std::memcpy(d->header.text,save::kHeaderText,sizeof(save::kHeaderText)); d->header.version=kSaveVersion;
    d->options.numPlayers=2; d->options.localPlayer=0; d->options.turn=19; d->options.nextGlobalId=500;
    d->options.victory=1; d->world.width=3; d->world.height=1; d->world.numTerritories=3;
    d->territories.resize(3); d->tiles.resize(3);
    for (int p=0;p<7;++p) {
        d->players[size_t(p)].index=uint8_t(p); d->players[size_t(p)].race=2; d->players[size_t(p)].type=p?3:1;
        d->ministerJobs[size_t(p)].resize(1); d->ministerJobs[size_t(p)][0].type=1;
        for (int row=0;row<64;++row) d->raceStats.v[row][p]=100;
    }
    for (int i=0;i<3;++i) {
        auto& t=d->territories[size_t(i)].data; t.index=uint16_t(i+1); t.owner=0; t.terrain=1;
        std::memcpy(t.name,"Alpha",6); t.population=1000; t.morale=100; t.knowledge=100;
        t.numTiles=1; t.tiles[0].raw=uint32_t(i); t.materials[2]=20000; t.production[7]=77; t.consumption[2]=-51;
        for (int site=0;site<36;++site) {
            t.sites[site].unk_00=uint16_t((site%6)|((site/6)<<8)); t.sites[site].terrainFlags=1;
            t.sites[site].unk_05[11]=0xa5;
        }
        d->tiles[size_t(i)].x=uint8_t(i); d->tiles[size_t(i)].territory=int16_t(i+1);
    }
    d->trailing={0,0x80,0xff}; d->localList={7,0}; return d;
}
Building& addBuilding(save::Document& d,int type,int site,int territory=1) {
    Building b{}; b.id=uint16_t(d.buildings.size()+1); b.flags=6; b.type=uint8_t(type);
    b.category=data::kBuildingTypes[type].category; b.race=2; b.site=int8_t(site); b.territory=int16_t(territory);
    if (!d.buildings.empty()) { b.prev.raw=d.buildings.back().id; d.buildings.back().next.raw=b.id; }
    d.territories[size_t(territory-1)].data.sites[site].building.raw=b.id;
    d.territories[size_t(territory-1)].data.sites[site].terrainFlags|=0x3000;
    d.buildings.push_back(b); return d.buildings.back();
}
void housing(save::Document& d,int workers=7) { auto& b=addBuilding(d,3,0); b.task[1]=20; b.labor[1]=workers; }
BuildingProgressContext context() {
    BuildingProgressContext c; SessionRng rng; save::Error e;
    require(rng.initialize(54,e),"explicit RNG initialization");
    c.events.rngBeforeEvents=c.ai.rng=c.log.rngAfterEvents=rng.snapshot(); c.events.citiesBeforeLoad[6]=99;
    return c;
}
std::vector<uint8_t> bytes(const save::Document& d) {
    std::vector<uint8_t> out; save::Error e;
    if (!save::encode(d,out,e)) throw std::runtime_error(e.message);
    for (const auto& t:d.territories) {
        const auto* p=reinterpret_cast<const uint8_t*>(&t.data);
        out.insert(out.end(),p+kTerritorySavedBytes,p+sizeof(Territory));
    }
    return out;
}
struct Outcome { std::unique_ptr<save::Document> d=std::make_unique<save::Document>(); BuildingProgressReport report; };
Outcome progress(const save::Document& d,BuildingProgressContext ctx=context()) {
    const auto before=bytes(d); Outcome out; save::Error e{save::ErrorCode::Io,1,"stale"};
    if (!progressBuildingWork(d,1,ctx,*out.d,out.report,e)) throw std::runtime_error(e.message);
    require(e.code==save::ErrorCode::None && e.message.empty() && bytes(d)==before,"progress clears error and preserves caller source");
    auto alias=std::make_unique<save::Document>(d); BuildingProgressReport report;
    require(progressBuildingWork(*alias,1,ctx,*alias,report,e) && bytes(*alias)==bytes(*out.d) && report==out.report,
            "work progression supports deterministic alias transaction");
    return out;
}
void reject(const save::Document& d,BuildingProgressContext ctx=context()) {
    const auto before=bytes(d); auto out=fixture(); const auto destination=bytes(*out);
    BuildingProgressReport report; report.territory=99; report.createdIds={7}; const auto old=report; save::Error e;
    require(!progressBuildingWork(d,1,ctx,*out,report,e) && e.code!=save::ErrorCode::None && !e.message.empty(),"invalid work domain is explicit");
    require(bytes(d)==before && bytes(*out)==destination && report==old,"work failure preserves source, destination and report");
}
void ordinaryAndRepair() {
    auto d=fixture(); housing(*d); auto& b=addBuilding(*d,21,2); b.turnsLeft=76; b.task[0]=2; b.labor[0]=3;
    auto partial=progress(*d);
    require(partial.report.changes.size()==1 && partial.report.changes[0].output==75 &&
            partial.d->buildings[1].turnsLeft==1 && partial.d->buildings[1].labor[0]==1 && partial.d->buildings[0].labor[1]==9 &&
            partial.report.events.empty(),"75work applied then redundant construction workers move3->1, housing7->9");
    d->buildings[1].flags|=0x100; auto locked=progress(*d);
    require(locked.d->buildings[1].labor[0]==3,"locked work slot skips IsBuildTaskDifferent trimming");
    d->buildings[1].flags=6; d->buildings[1].turnsLeft=75;
    auto complete=progress(*d);
    require(complete.report.changes[0].completed && complete.d->buildings[1].turnsLeft==0 && complete.d->buildings[1].task[1]==7 &&
            complete.d->buildings[1].labor[1]==3 && (complete.d->buildings[1].flags&0x40) &&
            complete.report.events.size()==1 && complete.report.events[0].type==62 && complete.report.rngAfter.counters.secondary15==1,
            "completion refreshes/distributes labor, marks announcement and emits real62 portrait");
    for (int site=0;site<36;++site) require(complete.d->territories[0].data.sites[site].unk_05[11]==0xa5,"ordinary completion has no site-road call");
    require(complete.d->territories[0].data.materials[2]==20000 && complete.d->territories[0].data.production[7]==77 &&
            complete.d->territories[0].data.consumption[2]==-51 && complete.d->options.turn==19 && complete.d->events.empty() &&
            complete.report.citiesAfter==context().events.citiesBeforeLoad,"isolated work branch creates no materials, stock clamp, SAV event or turn");
    d->buildings[1].flags|=0x40; auto repair=progress(*d);
    require(repair.report.events.size()==1 && repair.report.events[0].type==63,"previously announced building finishing damage work emits repair63");
    d->buildings[1].flags=2; auto inactive=progress(*d);
    require(inactive.report.changes.empty() && inactive.d->buildings[1].turnsLeft==75,"inactive record gets no progress despite initial local balance");
    d->buildings[1].flags=4; auto unpaid=progress(*d);
    require(unpaid.report.changes.empty() && unpaid.d->buildings[1].turnsLeft==75,"active but unpaid record is skipped");
    d=fixture(); housing(*d,9); auto& research=addBuilding(*d,19,2); research.turnsLeft=1; research.task[0]=2; research.labor[0]=1;
    auto firstResearch=progress(*d);
    require(firstResearch.report.events.size()==2 && firstResearch.report.events[0].type==62 && firstResearch.report.events[1].type==55 &&
            firstResearch.report.rngAfter.counters.secondary15==2,"first research building emits62 then55 in one shared portrait stream");
    d->buildings[1].turnsLeft=-32768; d->raceStats.v[2][2]=0;
    auto wrapped=progress(*d);
    require(wrapped.d->buildings[1].turnsLeft==32767 && wrapped.report.events.empty(),"signed16 subtraction wraps before clamp: -32768 minus minimum1 ->32767");
}
void upgradesAndRelocation() {
    auto d=fixture(); housing(*d,8); auto& b=addBuilding(*d,1,14); b.task[0]=21; b.task[1]=20; b.labor[0]=1;
    b.flags|=0x100; b.unk_16=100;
    auto upgraded=progress(*d);
    require(upgraded.report.changes.size()==1 && upgraded.report.changes[0].output==20 && upgraded.report.changes[0].upgraded &&
            upgraded.d->buildings[1].type==2 && upgraded.d->buildings[1].unk_16==0 && upgraded.report.events[0].type==75 &&
            upgraded.d->buildings[1].race==2 && upgraded.d->buildings[1].category==17,"120work Housing upgrade increments only type, preserves stored race/category and resets progress");
    d->buildings[1].unk_16=32760; auto wrap=progress(*d);
    require(wrap.d->buildings[1].type==1 && wrap.d->buildings[1].unk_16==-32756 && wrap.report.events.empty(),"upgrade accumulator adds lowWORD and compares signed after wrapping");
    d=fixture(); housing(*d,9); auto& farm=addBuilding(*d,6,14); farm.task[0]=21; farm.labor[0]=1; farm.flags|=0x100; farm.unk_16=290;
    d->techs[35].knownMask=1;
    const int sites[]={14,15,8,9}; const int16_t values[]={1000,2000,3000,3000};
    for (int n=0;n<4;++n) { auto& cell=d->territories[0].data.sites[sites[n]]; cell.terrainFlags=0x4001;
        std::memcpy(&cell.unk_05[3],&values[n],2); }
    auto shrink=progress(*d);
    require(shrink.d->buildings[1].type==7 && shrink.d->buildings[1].site==8 && shrink.report.changes[0].output==18 &&
            shrink.d->territories[0].data.sites[8].building.raw==2 && shrink.d->territories[0].data.sites[14].building.raw==0,
            "2x2->1x1 upgrade chooses strict-highest food+wood yield, first tie8 over9");
    require(shrink.d->territories[0].data.sites[8].terrainFlags==0x3001 && shrink.d->territories[0].data.sites[9].terrainFlags==1 &&
            shrink.d->territories[0].data.sites[14].terrainFlags==1 && shrink.d->territories[0].data.sites[15].terrainFlags==1,
            "upgrade clears old2x2 high flags before placing single new anchor");
    d->techs[35].knownMask=0; auto denied=progress(*d);
    require(denied.report.changes.empty() && denied.d->buildings[1].unk_16==290,"unavailable upgrade technology does not accumulate work");
}
void cityPlatformAiAndRollback() {
    auto d=fixture(); housing(*d,9); auto& city=addBuilding(*d,37,14); city.turnsLeft=1; city.task[0]=2; city.labor[0]=1;
    d->options.victory=0; auto& shrine=addBuilding(*d,46,0,3); (void)shrine;
    uint32_t known=1; std::memcpy(d->territories[2].data.unk_8b0,&known,4);
    auto local=progress(*d);
    uint32_t after; std::memcpy(&after,local.d->territories[2].data.unk_8b0,4);
    require(local.report.cityCountsRebuilt && local.report.citiesAfter[0]==1 && local.report.citiesAfter[6]==0 && after==0xff &&
            local.report.events.size()==1 && local.report.events[0].type==67 && local.report.rngAfter==context().events.rngBeforeEvents &&
            !(local.d->buildings[1].flags&0x40),"CityCenter victory0 recounts and emits67 deterministic city portrait; no62 flag write");
    d->territories[0].data.owner=1;
    auto enemy=progress(*d);
    require(enemy.report.events[0].type==65 && enemy.report.events[0].local && enemy.report.logAfter.entries[0].player==1,
            "nonlocal CityCenter notifies local recipient65 with Ex owner payload, needs no AI callback");
    d->options.allowAlliances=1; d->players[0].relations[1]=0x10; auto allied=progress(*d);
    require(allied.report.events[0].type==66,"allied CityCenter chooses66");
    d=fixture(); d->territories[0].data.terrain=0; auto& platform=addBuilding(*d,38,25);
    platform.turnsLeft=1; platform.task[0]=2; platform.labor[0]=1;
    auto sea=progress(*d);
    require(sea.d->buildings.size()==1 && sea.report.createdIds.empty() && sea.d->buildings[0].turnsLeft==0,
            "platform completion creates NO invented SeaHab or other record");
    d=fixture(); housing(*d,9); auto& ordinary=addBuilding(*d,21,2); ordinary.turnsLeft=1; ordinary.task[0]=2; ordinary.labor[0]=1;
    d->territories[0].data.owner=1; AiSession ai; save::Error error; require(ai.initializeAfterLoad(*d,error),"prepare owned AI session");
    auto ctx=context(); ctx.aiSession=&ai; auto aiDone=progress(*d,ctx);
    require(aiDone.report.events[0].aiDispatched && !aiDone.report.events[0].aiReport.handled && aiDone.d->buildings[1].labor[1]==1 &&
            aiDone.report.rngAfter==ctx.events.rngBeforeEvents,"AI completion installs original first-task labor and real default62 callback");
    reject(*d); // Late failure: work/refresh already applied to candidate before missing AI.
    d->territories[0].data.owner=0; ctx=context(); ctx.events.rngBeforeEvents.format=99; reject(*d,ctx);
    auto unrelated=addBuilding(*d,5,0,2); (void)unrelated; // off-grid2x2 producer outside this branch.
    d->territories[1].data.owner=1; d->players[1].index=31; d->players[1].race=-1;
    auto scoped=progress(*d);
    require(scoped.report.changes[0].completed,"addressed production leaf never evaluates unrelated world/max-output domains");
}
}
int main() {
    try {
        std::vector<uint8_t> globalState(sizeof(gs)),globalMisc(sizeof(gg));
        std::memcpy(globalState.data(),&gs,sizeof(gs)); std::memcpy(globalMisc.data(),&gg,sizeof(gg));
        const auto seed=rtl::seed(),seedHi=rtl::seedHi();
        ordinaryAndRepair(); upgradesAndRelocation(); cityPlatformAiAndRollback();
        require(std::memcmp(globalState.data(),&gs,sizeof(gs))==0 && std::memcmp(globalMisc.data(),&gg,sizeof(gg))==0 &&
                rtl::seed()==seed && rtl::seedHi()==seedHi,"building work never mutates globals or process RNG");
        std::cout<<"building_progress: work/completion/repair, upgrades/relocation, labor, cities, events/AI/RNG and rollback passed\n"; return 0;
    } catch (const std::exception& e) { std::cerr<<"building_progress: "<<e.what()<<'\n'; return 1; }
}
