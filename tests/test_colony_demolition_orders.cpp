// Collective0045b304 expectations derived from exported code and fresh assembly.
// These checks do not claim an observed replay of the original executable.
#include "game/colony_demolition_orders.h"
#include "game/data_tables.h"
#include "game/entity_creation.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include "game/save_files.h"
#include <algorithm>
#include <array>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>
#include <vector>

namespace {
using namespace dl2;
using namespace dl2::simulation;
void require(bool yes,const char* message) { if (!yes) throw std::runtime_error(message); }
void checked(bool yes,const save::Error& error) { if (!yes) throw std::runtime_error(error.message); }
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
        for (int site=0;site<36;++site) {
            t.sites[site].unk_00=uint16_t((site%6)|((site/6)<<8)); t.sites[site].terrainFlags=1;
            t.sites[site].unk_05[11]=uint8_t(0x80+site);
        }
        t.production[3]=12345; t.consumption[6]=-99; t.materials[2]=20000;
        std::fill_n(t.unk_8b0+(0x994-0x8b0),6,uint8_t(0xa0+i));
    }
    d->trailing={0xff,0,0x80}; return d;
}
uint32_t building(save::Document& d,int type,int site,int territory=1) {
    Building b{}; b.id=uint16_t(50000+d.buildings.size()); b.type=uint8_t(type);
    b.category=data::kBuildingTypes[type].category; b.flags=6;
    b.territory=int16_t(territory); b.site=int8_t(site);
    if (!d.buildings.empty()) { b.prev.raw=d.buildings.back().id; d.buildings.back().next.raw=b.id; }
    d.territories[size_t(territory-1)].data.sites[site].building.raw=b.id;
    d.buildings.push_back(b); return b.id;
}
std::vector<uint8_t> bytes(const save::Document& d) {
    std::vector<uint8_t> result; save::Error error; checked(save::encode(d,result,error),error);
    for (const auto& record:d.territories) {
        const auto* raw=reinterpret_cast<const uint8_t*>(&record.data);
        result.insert(result.end(),raw+kTerritorySavedBytes,raw+sizeof(Territory));
    }
    return result;
}
std::array<uint8_t,6> sea(const save::Document& d,int territory) {
    std::array<uint8_t,6> result{};
    const auto& t=d.territories[size_t(territory-1)].data;
    std::copy_n(t.unk_8b0+(0x994-0x8b0),6,result.begin()); return result;
}
struct Outcome {
    std::unique_ptr<save::Document> document=std::make_unique<save::Document>();
    DemolishColonyOrderReport report;
};
Outcome demolish(const save::Document& source,uint32_t territory=1,const BuildingRemovalContext& context={},int actor=0) {
    const auto before=bytes(source); const auto savedContext=context;
    Outcome out; save::Error error{save::ErrorCode::Io,33,"old error"};
    checked(orderDemolishColony(source,{actor,territory},context,*out.document,out.report,error),error);
    require(error.code==save::ErrorCode::None && error.message.empty() && error.offset==0 &&
            bytes(source)==before && context==savedContext,"collective success changed inputs or retained prior error");
    auto alias=std::make_unique<save::Document>(source); DemolishColonyOrderReport aliasReport;
    aliasReport.contextAfter=context;
    checked(orderDemolishColony(*alias,{actor,territory},aliasReport.contextAfter,*alias,aliasReport,error),error);
    require(bytes(*alias)==bytes(*out.document) && aliasReport==out.report,
            "collective document/report-context aliases differ from separate output");
    return out;
}
void reject(const save::Document& source,DemolishColonyOrderRequest request,
            const BuildingRemovalContext& context={}) {
    auto destination=fixture(); const auto before=bytes(source),prior=bytes(*destination); const auto input=context;
    DemolishColonyOrderReport report; report.territory=99; report.removedIds={555};
    report.contextAfter.pendingShrines.entries.push_back({1,3}); const auto saved=report; save::Error error;
    require(!orderDemolishColony(source,request,context,*destination,report,error) &&
            error.code!=save::ErrorCode::None && !error.message.empty(),"unsafe collective command was accepted");
    require(bytes(source)==before && bytes(*destination)==prior && report==saved && context==input,
            "failed collective command changed document/report/context");
    auto alias=std::make_unique<save::Document>(source);
    require(!orderDemolishColony(*alias,request,context,*alias,report,error) && bytes(*alias)==before && report==saved,
            "failed collective alias published partial demolition");
}

void siteOrderRefundsAndCategory() {
    auto d=fixture();
    const auto last=building(*d,29,20); // Vector/list order differs from site order.
    const auto shrine=building(*d,46,10);
    const auto first=building(*d,29,0);
    auto& paid=d->buildings.back(); paid.flags=4; paid.cost[0]=-3;
    paid.cost[1]=131071; paid.cost[2]=std::numeric_limits<int32_t>::min(); paid.cost[3]=65536;
    const auto savedShrine=building(*d,29,7); d->buildings.back().category=11;
    d->buildings.back().task[1]=12; d->buildings.back().labor[1]=999;
    const auto canonicalShrine=building(*d,46,15); d->buildings.back().category=18;
    const auto foreign=building(*d,29,0,3);
    d->territories[0].data.flags|=0x10;
    d->ministerJobs[0][0].type=3; d->ministerJobs[0][0].param[0]=1; d->ministerJobs[0][0].param[1]=15;
    BuildingRemovalContext context; context.campaignFlags=(1u<<12); context.campaignProgress={123,-3,1};
    context.pendingShrines.entries.assign(kPendingShrineCapacity,{1,3});
    const auto out=demolish(*d,1,context);
    require(out.report.territory==1 && out.report.removedIds==std::vector<uint32_t>({first,canonicalShrine,last}) &&
            out.report.removals.size()==3 && out.document->buildings.size()==3 &&
            out.document->buildingById(shrine) && out.document->buildingById(savedShrine) &&
            out.document->buildingById(foreign),"collective selection used canonical category or vector order");
    require(out.report.removals[0].site==0 && out.report.removals[1].site==15 && out.report.removals[2].site==20 &&
            out.report.removals[0].credits==-2 && out.report.removals[1].credits==150 && out.report.removals[2].credits==37 &&
            out.document->players[0].credits==185 && out.document->players[1].credits==0,
            "ordered paid/canonical half-cost refunds differ from original arithmetic");
    require(out.report.removals[0].materials[0]==-1 && out.report.removals[0].materials[1]==0 &&
            out.report.removals[0].materials[2]==-32768 && out.document->territories[0].data.materials[4]==7 &&
            out.document->territories[0].data.materials[2]==20000,"refund materials lost SAR1/signed16 or clamped stock");
    for (const auto& removal:out.report.removals)
        require(removal.refundPlayer==0 && removal.localLaborBalanced && removal.originalRoadsTargetWasSentinel &&
                removal.contextAfter==context && !removal.shrinePenaltyQueued && !removal.shrineFlagCleared,
                "each collective removal must balance/refund without shrine processing");
    require(out.document->buildingById(savedShrine)->labor[1]==0 && out.report.removals[1].deferredBuildJobs==1 &&
            out.report.contextAfter==context && (out.document->territories[0].data.flags&0x10) &&
            out.document->events.empty() && out.document->scores[0].nukesUsed==0,
            "collective order omitted real labor or invented delayed shrine consequences");
    for (int t=1;t<=3;++t) require(sea(*out.document,t)==sea(*d,t),"collective order rebuilt marine flags");
    for (int site=0;site<36;++site)
        require(out.document->territories[0].data.sites[site].unk_05[11]==uint8_t(0x80+site),"collective order rebuilt local roads");
    require(std::memcmp(&out.document->territories[2].data,&d->territories[2].data,sizeof(Territory))==0,
            "collective order changed a different territory");
}

void emptyAndAuthority() {
    auto d=fixture(); BuildingRemovalContext context; context.campaignFlags=0xfedc1234u;
    context.campaignProgress={-1,345,0}; context.pendingShrines.entries={{0,1},{1,3},{0,1}};
    auto empty=demolish(*d,1,context);
    require(empty.report.territory==1 && empty.report.removedIds.empty() && empty.report.removals.empty() &&
            empty.report.contextAfter==context && bytes(*empty.document)==bytes(*d),"empty collective operation was not explicit zero removals");
    building(*d,46,0); auto onlyShrine=demolish(*d,1,context);
    require(onlyShrine.report.removedIds.empty() && bytes(*onlyShrine.document)==bytes(*d),"shrine-only order mutated colony");
    for (int actor:{-1,1,7}) reject(*d,{actor,1},context);
    reject(*d,{0,0},context); reject(*d,{0,99},context);
    d->players[0].index=1; reject(*d,{0,1}); d->players[0].index=0;
    d->players[0].type=3; reject(*d,{0,1}); d->players[0].type=1;
    d->territories[0].data.visibility[0]=3; reject(*d,{0,1}); d->territories[0].data.visibility[0]=4;
    d->territories[0].data.owner=1; reject(*d,{0,1}); d->territories[0].data.owner=0;
    context.pendingShrines.entries.assign(kPendingShrineCapacity+1,{0,1}); reject(*d,{0,1},context);
    context.pendingShrines.entries={{7,1}}; reject(*d,{0,1},context);
    context.pendingShrines.entries={{0,0}}; reject(*d,{0,1},context);
    d->header.isMap=1; d->mapTerritories.resize(3); reject(*d,{0,1});

    // Refund owner must remain explicit even when localPlayer is not slot0.
    d=fixture(); d->options.localPlayer=1; d->players[0].type=3; d->players[1].type=1;
    const auto id=building(*d,29,2,3); auto localOne=demolish(*d,3,{},1);
    require(localOne.report.removedIds==std::vector<uint32_t>{id} && localOne.report.removals[0].refundPlayer==1 &&
            localOne.document->players[1].credits==37 && localOne.document->players[0].credits==0,
            "nonzero local owner did not receive its collective refund");
}

void platformsAndOrphanHab() {
    auto d=fixture(); save::Error error; BuildingCreationReport created;
    checked(createCompletedBuilding(*d,{2,38,25},*d,created,error),error);
    const auto platform=created.buildingId,hab=created.companionBuildingId;
    std::array<uint32_t,4> sockets{}; const int sites[]{3,13,17,27};
    for (size_t i=0;i<sockets.size();++i) {
        checked(createCompletedBuilding(*d,{2,19,sites[i]},*d,created,error),error); sockets[i]=created.buildingId;
    }
    auto out=demolish(*d,2);
    require(out.report.removedIds==std::vector<uint32_t>({sockets[0],sockets[1],hab,sockets[2],platform,sockets[3]}) &&
            out.report.removals.size()==6 && out.document->buildings.empty(),
            "collective platform path used individual cascade order or SeaHab redirection");
    for (const auto& site:out.document->territories[1].data.sites)
        require(!site.building.raw && !(site.terrainFlags&0xff00u),"collective platform footprint/socket final state differs");
    // A skipped socket survives the earlier platform deletion at25. Its live
    // anchor stays present at27 although the platform cleared its high flags.
    for (auto& b:d->buildings) if (b.id==sockets[3]) b.category=11;
    out=demolish(*d,2);
    require(out.report.removedIds==std::vector<uint32_t>({sockets[0],sockets[1],hab,sockets[2],platform}) &&
            out.document->buildingById(sockets[3]) && out.document->territories[1].data.sites[27].building.raw==sockets[3] &&
            out.document->territories[1].data.sites[27].terrainFlags==1 && out.report.contextAfter.pendingShrines.entries.empty(),
            "platform demolition cascaded to a category11 socket or restored a deleted platform");
    d=fixture(); const auto orphan=building(*d,39,15,2);
    out=demolish(*d,2);
    require(out.report.removedIds==std::vector<uint32_t>{orphan} && out.report.removals[0].credits==0 &&
            out.document->buildings.empty(),"collective SeaHab removal incorrectly requires a platform");
}

void lateRollback() {
    auto d=fixture(); const auto first=building(*d,29,0);
    building(*d,5,35); // Valid archival anchor, unsafe2x2 footprint only on its later removal.
    auto intermediate=fixture(); BuildingLifecycleReport firstReport; save::Error error;
    BuildingRemovalContext context; context.pendingShrines.entries={{1,3}};
    checked(removeBuilding(*d,{first,BuildingRemovalKind::DemolishBuilding,0},context,*intermediate,firstReport,error),error);
    require(firstReport.credits==37 && intermediate->players[0].credits==37,"late-failure premise must allow first refund");
    reject(*d,{0,1},context);
}

void optionalTutorial(const std::filesystem::path& directory) {
    const auto file=directory/"TUTORIAL.SAV";
    if (directory.empty() || !std::filesystem::is_regular_file(file)) {
        std::cout<<"collective demolition: optional tutorial unavailable\n"; return;
    }
    auto d=std::make_unique<save::Document>(); save::Error error;
    checked(save::readDocument(file,*d,error),error);
    const int actor=d->options.localPlayer; size_t count=0;
    for (const auto& record:d->territories) {
        if (record.data.owner!=actor || record.data.visibility[size_t(actor)]!=4) continue;
        std::vector<uint32_t> expected;
        for (const auto& site:record.data.sites) {
            const auto* b=d->buildingById(site.building.raw);
            if (b && b->category!=11) expected.push_back(b->id);
        }
        if (expected.empty()) continue;
        auto out=demolish(*d,record.data.index,{},actor);
        require(out.report.removedIds==expected,"tutorial removal order differs from original site traversal");
        for (auto id:expected) require(!out.document->buildingById(id),"tutorial retained an eligible building");
        ++count;
    }
    require(count>0,"tutorial did not exercise an owned nonempty colony");
    std::cout<<"collective demolition tutorial: "<<count<<" colonies, original preserved\n";
}
} // namespace
int main(int argc,char** argv) {
    try {
        rtl::srand(0xf134579bu); (void)rtl::lrand(); gg.rng2Seed=0xabcdfed0u;
        const auto low=rtl::seed(),high=rtl::seedHi();
        const auto globals=std::make_unique<GameGlobals>(gg); const auto state=std::make_unique<GameState>(gs);
        siteOrderRefundsAndCategory(); emptyAndAuthority(); platformsAndOrphanHab(); lateRollback();
        optionalTutorial(argc>1?std::filesystem::path(argv[1]):std::filesystem::path{});
        require(rtl::seed()==low && rtl::seedHi()==high && std::memcmp(&gg,globals.get(),sizeof(gg))==0 &&
                std::memcmp(&gs,state.get(),sizeof(gs))==0,"collective demolition touched globals/RNG");
        std::cout<<"Collective colony demolition tests passed\n"; return 0;
    } catch (const std::exception& e) { std::cerr<<"Collective demolition: "<<e.what()<<'\n'; return 1; }
}
