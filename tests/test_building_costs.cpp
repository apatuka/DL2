// Oracles derived from0044f110/0044df30; not execution of the original binary.
#include "game/building_costs.h"
#include "game/data_tables.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include "game/save_files.h"
#include "game/load_profile.h"
#include <algorithm>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>

namespace {
using namespace dl2;
using namespace dl2::simulation;
namespace fs=std::filesystem;
void require(bool value,const char* message) { if (!value) throw std::runtime_error(message); }
void ok(bool value,const save::Error& e) { if (!value) throw std::runtime_error(e.message); }
std::unique_ptr<save::Document> fixture() {
    auto d=std::make_unique<save::Document>();
    std::memcpy(d->header.text,save::kHeaderText,sizeof(save::kHeaderText)); d->header.version=kSaveVersion;
    d->options.numPlayers=2; d->options.localPlayer=0; d->options.turn=19; d->options.nextGlobalId=1000;
    d->world.width=3; d->world.height=1; d->world.numTerritories=3; d->territories.resize(3); d->tiles.resize(3);
    for (int p=0;p<7;++p) {
        d->players[size_t(p)].index=uint8_t(p); d->players[size_t(p)].race=2; d->players[size_t(p)].type=p?3:1;
        d->players[size_t(p)].credits=1000; d->ministerJobs[size_t(p)].resize(1); d->ministerJobs[size_t(p)][0].type=1;
        for (auto& row:d->raceStats.v) row[p]=100;
    }
    for (auto& tech:d->techs) tech.knownMask=0x7f;
    for (int i=0;i<3;++i) {
        auto& t=d->territories[size_t(i)].data; t.index=uint16_t(i+1); t.owner=i==2?-1:0; t.terrain=1;
        t.population=500; t.morale=100; t.numTiles=1; t.tiles[0].raw=uint32_t(i); std::memcpy(t.name,"Alpha",6);
        for (int s=0;s<36;++s) { t.sites[s].unk_00=uint16_t(s%6+256*(s/6)); t.sites[s].terrainFlags=1; }
        d->tiles[size_t(i)].x=uint8_t(i); d->tiles[size_t(i)].territory=int16_t(i+1);
    }
    d->trailing={0,255,128}; return d;
}
Building& addBuilding(save::Document& d,int id,int type,int site,int territory=1,uint16_t flags=4) {
    Building b{}; b.id=uint16_t(id); b.type=uint8_t(type); b.category=data::kBuildingTypes[type].category;
    b.flags=flags; b.site=int8_t(site); b.territory=int16_t(territory); b.race=2; b.turnsLeft=31;
    b.unk_35=0xa5; b.taskData[3][10]=-12345;
    if (!d.buildings.empty()) { b.prev.raw=d.buildings.back().id; d.buildings.back().next.raw=b.id; }
    d.territories[size_t(territory-1)].data.sites[site].building.raw=b.id;
    d.buildings.push_back(b); return d.buildings.back();
}
ConstructionOrderContext context() {
    ConstructionOrderContext c; SessionRng rng; save::Error e; ok(rng.initialize(54,e),e);
    c.events.rngBeforeEvents=c.ai.rng=c.log.rngAfterEvents=rng.snapshot(); c.payment.selectedTerritory=1;
    c.log.slotPayloads[0]={71,93}; return c;
}
std::vector<uint8_t> bytes(const save::Document& d) {
    std::vector<uint8_t> out; save::Error e; ok(save::encode(d,out,e),e);
    for (const auto& t:d.territories) { const auto* p=reinterpret_cast<const uint8_t*>(&t.data);
        out.insert(out.end(),p+kTerritorySavedBytes,p+sizeof(Territory)); }
    return out;
}
struct Outcome { std::unique_ptr<save::Document> d=std::make_unique<save::Document>(); BuildingCostsReport report; };
Outcome process(const save::Document& d,ConstructionOrderContext c=context()) {
    const auto before=bytes(d); const auto priorLog=c.log; const auto priorAi=c.ai;
    Outcome out; save::Error e{save::ErrorCode::Io,9,"old"};
    ok(processBuildingCosts(d,c,*out.d,out.report,e),e);
    require(bytes(d)==before && c.log==priorLog && c.ai==priorAi && e.code==save::ErrorCode::None && !e.offset && e.message.empty(),
            "building costs must preserve source/context and clear errors");
    auto alias=std::make_unique<save::Document>(d); BuildingCostsReport repeated;
    ok(processBuildingCosts(*alias,c,*alias,repeated,e),e);
    require(bytes(*alias)==bytes(*out.d) && repeated==out.report,"building costs alias transaction differs"); return out;
}
void orderingAndFilters() {
    auto d=fixture();
    addBuilding(*d,65530,1,0).cost[0]=77;
    addBuilding(*d,5,1,1).turnsLeft=0;
    addBuilding(*d,2,1,2,1,6).cost[3]=91; //Already paid, untouched.
    addBuilding(*d,3,1,3,1,0).cost[3]=92; //Inactive, untouched.
    addBuilding(*d,4,1,0,3).cost[3]=93; //Unowned, untouched.
    d->territories[0].data.materials[3]=10; d->territories[2].data.materials[3]=777;
    d->players[0].credits=-20;
    auto out=process(*d);
    require(out.report.order==std::vector<uint32_t>{5,65530} && out.report.buildings.size()==2,
            "sort must be unsigned ID, independent of file order, work or tasks");
    require((out.d->buildingById(5)->flags&2) && !(out.d->buildingById(65530)->flags&2) &&
            out.report.buildings[1].payment.failureMask==8 && out.d->buildingById(65530)->cost[0]==77,
            "lower global ID receives scarce materials first; shortage retains paid data");
    require(out.d->players[0].credits==-20 && out.d->buildingById(5)->turnsLeft==0 &&
            out.d->buildingById(2)->cost[3]==91 && out.d->buildingById(3)->cost[3]==92 && out.d->buildingById(4)->cost[3]==93 &&
            out.report.events.empty(),"no base-money, affordability, task, completion or inactive/unowned effects");
    for (const auto& b:out.d->buildings) require(b.unk_35==0xa5 && b.taskData[3][10]==-12345,"unrelated building payload changed");
    auto empty=fixture(); auto none=process(*empty);
    require(none.report.order.empty() && bytes(*none.d)==bytes(*empty),"empty pass is a real evaluated scan");
}
void councilAndPartial() {
    for (int level:{-32768,-1,0,1,3,32767}) {
        auto d=fixture(); auto& b=addBuilding(*d,11,37,7); b.hubLevel=int16_t(level); b.cost[0]=-333;
        auto out=process(*d); const auto& change=out.report.buildings[0];
        require(change.requirements.labor==600 && change.requirements.technology==0 &&
                change.requirements.materials[0]==(level<1?125:level*500) &&
                change.requirements.materials[2]==(level<1?50:level*50) &&
                change.requirements.materials[4]==(level<1?250:level*250),
                "Council costs must use SAVED signed hub level, not current count or race");
        require(change.paidAfter[0]==-333 && out.d->players[0].credits==1000,"partial Council leaves base paid money unchanged");
    }
    auto d=fixture(); auto& b=addBuilding(*d,7,30,0); b.cost[0]=-90; b.flags=0x184; b.cost[2]=2;
    d->techs[6].knownMask=0; d->territories[0].data.materials[2]=3;
    d->territories[0].data.materials[4]=50; d->territories[0].data.materials[8]=2;
    auto first=process(*d);
    require(first.report.buildings[0].payment.failureMask==0x100 && first.d->buildings[0].cost[2]==5 &&
            first.d->buildings[0].cost[4]==50 && first.d->buildings[0].cost[8]==2 && first.d->buildings[0].flags==0x184,
            "partial collection accumulates saved11words and retains all flags");
    first.d->territories[0].data.materials[8]=3;
    auto second=process(*first.d); const auto& paid=second.report.buildings[0];
    require(!paid.payment.failureMask && !paid.payment.affordabilityEvaluated && !paid.payment.requirementsAccepted &&
            paid.payment.paid[0]==-90 && paid.payment.paid[8]==5 && second.d->buildings[0].flags==0x186 &&
            std::all_of(paid.paidAfter.begin(),paid.paidAfter.end(),[](int32_t n){return n==0;}),
            "success ignores lost technology/base money, sets only paid bit and clears all paid words");
    require(second.d->buildings[0].turnsLeft==31 && second.report.events.empty(),"financing must not finish construction");
}
void eventsAndRollback() {
    auto d=fixture(); addBuilding(*d,1,1,0); d->territories[0].data.materials[3]=3;
    d->territories[1].data.materials[3]=50; //Existing donor but disconnected: actual import60.
    auto out=process(*d);
    require(out.report.events.size()==1 && out.report.events[0].type==60 && out.report.events[0].local &&
            out.report.logAfter.entries.size()==1 && out.report.logAfter.entries[0].player==1 && out.report.logAfter.entries[0].param==3 &&
            out.report.buildings[0].paidAfter[3]==3,"actual local import60 plus partial payment");
    const auto& textBytes=out.report.logAfter.entries[0].text; const std::string text(textBytes.begin(),textBytes.end());
    require(text.find("Alpha")!=std::string::npos && text.find("wood")!=std::string::npos,"canonical event60 formatted names");
    d->territories[0].data.adjacency[0]|=uint16_t(1u<<2);
    d->territories[1].data.adjacency[0]|=uint16_t(1u<<1);
    for (int p=0;p<7;++p) d->raceStats.v[53][p]=0;
    auto imported=process(*d);
    require(imported.report.events.empty() && imported.report.collectionAfter.transfers.size()==1 &&
            imported.report.collectionAfter.transfers[0].amount==7 && imported.d->territories[1].data.materials[3]==43 &&
            (imported.d->buildings[0].flags&2),"connected donor is actually imported and recorded");
    d->territories[0].data.adjacency[0]=d->territories[1].data.adjacency[0]=0;
    d->territories[0].data.owner=d->territories[1].data.owner=1;
    AiSession ai; save::Error e; ok(ai.initializeAfterLoad(*d,e),e); auto c=context(); c.aiSession=&ai;
    auto remote=process(*d,c);
    require(remote.report.events.size()==1 && remote.report.events[0].aiDispatched && remote.report.logAfter.entries.empty() &&
            remote.report.rngAfter==c.events.rngBeforeEvents,"real default AI import reaction, no local text or fabricated draw");
    const auto before=bytes(*d), destination=bytes(*out.d); const auto old=out.report;
    require(!processBuildingCosts(*d,context(),*out.d,out.report,e) && bytes(*d)==before && bytes(*out.d)==destination && out.report==old,
            "missing AI late after collection rolls back document and report");
    d->territories[0].data.owner=d->territories[1].data.owner=0;
    std::fill(std::begin(d->territories[0].data.name),std::end(d->territories[0].data.name),'X'); const auto unnamed=bytes(*d);
    require(!processBuildingCosts(*d,context(),*d,out.report,e) && bytes(*d)==unnamed && out.report==old,"invalid local event rolls back alias");
    c=context(); c.events.rngBeforeEvents.format=99;
    require(!processBuildingCosts(*d,c,*out.d,out.report,e) && bytes(*out.d)==destination && out.report==old,"invalid RNG snapshot is transactional");
}
void corpus(const fs::path& directory) {
    if (directory.empty() || !fs::is_regular_file(directory/"TUTORIAL.SAV")) return;
    size_t count=0;
    auto one=[&](const save::Document& source) {
        const auto archival=bytes(source); auto d=std::make_unique<save::Document>(); save::Error e;
        LoadCoreReport loaded;
        // Original offline load converts saved remote humans BEFORE installing
        // AI bindings. Exercise the actual core normalization, not a permissive
        // test-only AiSession or a hand-edited personality byte.
        ok(normalizeLoadCore(source,{-1,"Corpus"},*d,loaded,e),e);
        AiSession ai; ok(ai.initializeAfterLoad(*d,e),e);
        auto c=context(); c.aiSession=&ai; auto out=process(*d,c);
        require(std::is_sorted(out.report.order.begin(),out.report.order.end()) && bytes(source)==archival,
                "normalized corpus finance order and untouched archival source"); ++count;
    };
    for (const char* name:{"TUTORIAL.SAV","Saves/AUTOSAVE.SAV","Campaign/AUTOSAVE.CPN","Campaign/ChCht001.CPN"})
        if (fs::is_regular_file(directory/name)) { auto d=std::make_unique<save::Document>(); save::Error e;
            ok(save::readDocument(directory/name,*d,e),e); one(*d); }
    std::ifstream index(directory/"LEVELS.HDX",std::ios::binary);
    if (index) { uint32_t total=0; require(bool(index.read(reinterpret_cast<char*>(&total),4)) && total<=4096,"invalid corpus index");
        for (uint32_t i=0;i<total;++i) { char entry[12]{}; require(bool(index.read(entry,12)),"truncated corpus index");
            auto d=std::make_unique<save::Document>(); save::Error e; const std::string name(entry,std::find(entry,entry+8,'\0'));
            ok(save::readScenario(directory/"LEVELS",name,*d,e),e); one(*d); }
    }
    std::cout<<"building costs: "<<count<<" core-normalized corpus documents\n";
}
}
int main(int argc,char** argv) {
    try {
        rtl::srand(0x12345678); (void)rtl::lrand(); gg.rng2Seed=0xabcdef01;
        const auto low=rtl::seed(),high=rtl::seedHi(); const auto globals=std::make_unique<GameGlobals>(gg);
        const auto game=std::make_unique<GameState>(gs);
        orderingAndFilters(); councilAndPartial(); eventsAndRollback(); corpus(argc>1?fs::path(argv[1]):fs::path{});
        require(rtl::seed()==low && rtl::seedHi()==high && std::memcmp(globals.get(),&gg,sizeof(gg))==0 &&
                std::memcmp(game.get(),&gs,sizeof(gs))==0,"building costs modified global state/RNG");
        std::cout<<"building costs tests passed\n"; return 0;
    } catch (const std::exception& e) { std::cerr<<"building costs: "<<e.what()<<'\n'; return 1; }
}
