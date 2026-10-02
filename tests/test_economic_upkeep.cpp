// Independent0046b818/0046b4d0/0046b3dc oracles, not an original-binary replay.
#include "game/economic_upkeep.h"
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
    d->world.width=2; d->world.height=1; d->world.numTerritories=2; d->territories.resize(2); d->tiles.resize(2);
    for (int p=0;p<7;++p) {
        d->players[size_t(p)].index=uint8_t(p); d->players[size_t(p)].race=2; d->players[size_t(p)].type=p?3:1;
        d->players[size_t(p)].credits=1000000; d->ministerJobs[size_t(p)].resize(1); d->ministerJobs[size_t(p)][0].type=1;
        for (auto& row:d->raceStats.v) row[p]=100;
        for (auto& job:d->jobs[size_t(p)]) job.owner=int16_t(p);
    }
    for (int i=0;i<2;++i) {
        auto& t=d->territories[size_t(i)].data; t.index=uint16_t(i+1); t.owner=0; t.terrain=1;
        t.population=500; t.morale=100; t.numTiles=1; t.tiles[0].raw=uint32_t(i); std::memcpy(t.name,i?"Beta":"Alpha",i?5:6);
        for (int s=0;s<36;++s) { t.sites[s].unk_00=uint16_t(s%6+256*(s/6)); t.sites[s].terrainFlags=1; }
        d->tiles[size_t(i)].x=uint8_t(i); d->tiles[size_t(i)].territory=int16_t(i+1);
    }
    d->trailing={0,255,128}; return d;
}
Army& addArmy(save::Document& d,int id,int type,int owner=0,int territory=1) {
    Army a{}; a.id=uint16_t(id); a.type=uint8_t(type); a.unitClass=data::kUnitTypes[type].unitClass;
    a.owner=int8_t(owner); a.health=100; a.territory.raw=a.dest.raw=a.origin.raw=uint32_t(territory);
    std::memcpy(a.name,"Named unit",11); a.unk_2e[3]=0xa5;
    auto& t=d.territories[size_t(territory-1)].data; auto& head=t.owner==owner?t.armies:t.foreignArmies;
    a.next.raw=head.raw; for (auto& prior:d.armies) if (prior.id==head.raw) prior.prev.raw=a.id;
    head.raw=a.id; d.armies.push_back(a); return d.armies.back();
}
ConstructionOrderContext context() {
    ConstructionOrderContext c; SessionRng rng; save::Error e; ok(rng.initialize(54,e),e);
    c.events.rngBeforeEvents=c.ai.rng=c.log.rngAfterEvents=rng.snapshot(); c.log.slotPayloads[0]={71,93}; return c;
}
std::vector<uint8_t> bytes(const save::Document& d) {
    std::vector<uint8_t> out; save::Error e; ok(save::encode(d,out,e),e);
    for (const auto& t:d.territories) { const auto* p=reinterpret_cast<const uint8_t*>(&t.data);
        out.insert(out.end(),p+kTerritorySavedBytes,p+sizeof(Territory)); }
    return out;
}
struct Outcome { std::unique_ptr<save::Document> d=std::make_unique<save::Document>(); EconomicUpkeepReport report; };
Outcome process(const save::Document& d,ConstructionOrderContext c=context()) {
    const auto before=bytes(d); const auto priorLog=c.log; const auto priorAi=c.ai;
    Outcome out; save::Error e{save::ErrorCode::Io,9,"old"};
    ok(processEconomicUpkeep(d,c,*out.d,out.report,e),e);
    require(bytes(d)==before && c.log==priorLog && c.ai==priorAi && e.code==save::ErrorCode::None && !e.offset && e.message.empty(),
            "upkeep preserves source/context and clears errors");
    auto alias=std::make_unique<save::Document>(d); EconomicUpkeepReport repeated;
    ok(processEconomicUpkeep(*alias,c,*alias,repeated,e),e);
    require(bytes(*alias)==bytes(*out.d) && repeated==out.report,"upkeep alias transaction differs"); return out;
}
void costs() {
    auto d=fixture();
    for (int i=0;i<21;++i) addArmy(*d,100+i,i%2?4:23).unitClass=99; //Class must come from CANONICAL type, not saved field.
    for (int i=0;i<3;++i) addArmy(*d,200+i,5);
    addArmy(*d,300,9); addArmy(*d,301,11); addArmy(*d,400,12); addArmy(*d,401,13);
    addArmy(*d,450,26); addArmy(*d,451,16); addArmy(*d,452,19); //Medic/warhead/fort excluded.
    auto out=process(*d); const auto& p=out.report.players[0];
    require(p.unitCounts==std::array<int32_t,4>{21,3,2,2} && p.groupCosts==std::array<int32_t,4>{442,18,16,12} &&
            p.totalCost==488 && p.creditsAfter==1000000-488 && out.report.retiredIds.empty(),
            "upkeep uses nonlinear count formula, not sum of variable UnitDef.upkeep");
    require(out.report.events.size()==4 && out.report.events[0].type==153 && out.report.events[3].type==156 &&
            out.report.rngAfter==context().events.rngBeforeEvents,"four real maintenance notices have no portraits/RNG");
    const auto& entry=out.report.logAfter.entries.front(); const std::string text(entry.text.begin(),entry.text.end());
    require(text=="We have paid 442 credits in maintenance costs for 21 troopers." && entry.player==71 && entry.param==93,
            "canonical upkeep text uses amount/count but ordinary LogEvent preserves inactive payload");
    for (int player=0;player<7;++player) require(out.report.players[size_t(player)].player==player,"all seven players evaluated");
    d=fixture(); addArmy(*d,1,1); addArmy(*d,2,1); d->players[0].race=-1; d->raceStats.v[59][6]=150;
    out=process(*d); require(out.report.players[0].totalCost==6,"signed race reads neighboring in-bounds RaceStats WORD");
    d=fixture(); for (int i=0;i<560;++i) addArmy(*d,i+1,1); d->raceStats.v[60][2]=32767;
    out=process(*d);
    require(out.report.players[0].groupCosts[0]==-16442480 && out.d->players[0].credits==17442480,
            "full pool preserves signed32 multiplication overflow before /100, not widened formula");
}
void shortagesAndSelection() {
    auto d=fixture(); addArmy(*d,10,1); d->players[0].credits=0;
    auto first=process(*d);
    require(first.report.players[0].creditsAfter==0 && first.report.players[0].flagsAfter==1 && first.report.retiredIds.empty() &&
            first.report.events.size()==2 && first.report.events[0].type==153 && first.report.events[1].type==1,
            "first bankruptcy warns after cost report but does not disband");
    auto second=process(*first.d);
    require(second.report.retiredIds==std::vector<uint32_t>{10} && second.report.players[0].creditsAfter==17 &&
            second.report.players[0].flagsAfter==1 && second.report.events.size()==2 && second.report.events[1].type==3 && second.d->armies.empty(),
            "second shortage disbands, refunds half35=>17, leaves flag1, clears4, no duplicate warning");
    d=fixture(); addArmy(*d,10,1); d->players[0].credits=100; d->players[0].foodFlags=0x87;
    auto hunger=process(*d);
    require(hunger.report.retiredIds==std::vector<uint32_t>{10} && hunger.report.players[0].creditsAfter==116 &&
            hunger.report.players[0].flagsAfter==0x82 && hunger.report.events[1].type==3,
            "pre-existing hunger bit4 forces disband even with funds; preserve bit2/80, clear recovered credit1");
    d->players[0].foodFlags=1; d->players[0].credits=1; auto exact=process(*d);
    require(exact.report.retiredIds.empty() && exact.d->players[0].foodFlags==0 && exact.d->players[0].credits==0,
            "credits exactly sufficient is recovery, not shortage");
    d=fixture(); d->players[6].type=0; d->players[6].credits=-1; d->players[6].foodFlags=4;
    auto noArmy=process(*d);
    require(noArmy.report.players[6].creditsAfter==0 && noArmy.report.players[6].flagsAfter==1 && noArmy.report.retiredIds.empty() &&
            noArmy.report.events.size()==1 && noArmy.report.events[0].recipient==6,"inactive player still evaluated, original no-army attempt clears4");
    d=fixture(); addArmy(*d,40,8).experience=-100; addArmy(*d,2,8).experience=10;
    addArmy(*d,5,8).experience=-100; addArmy(*d,3,11).experience=-32768;
    d->players[0].credits=1000; d->players[0].foodFlags=4;
    auto tie=process(*d);
    require(tie.report.armyOrder==std::vector<uint32_t>({2,3,5,40}) && tie.report.players[0].selectedArmyId==5 &&
            tie.report.retiredIds==std::vector<uint32_t>{5} && tie.report.players[0].creditsAfter==1228,
            "disband picks canonical price500 over upkeep12, signed experience then smallest ID, real250 refund");
    d=fixture(); addArmy(*d,7,26); d->players[0].foodFlags=4;
    auto medic=process(*d); require(medic.report.players[0].totalCost==0 && medic.report.retiredIds==std::vector<uint32_t>{7},
            "disband candidate may be excluded from maintenance groups");
}
void cascadesAndContexts() {
    auto d=fixture(); addArmy(*d,50,12); addArmy(*d,51,1,1);
    d->armies[0].cargo[0].raw=51; d->armies[1].cargo[0].raw=50;
    d->players[0].foodFlags=4; d->players[0].credits=1000;
    // Removal is independent of passenger owner: player1 is counted AFTER the
    // earlier player's real carrier cascade, following original player order.
    auto cascade=process(*d);
    require(cascade.report.retiredIds==std::vector<uint32_t>({51,50}) && cascade.report.players[0].disband.refunds.size()==1 &&
            cascade.report.players[0].creditsAfter==1022 && cascade.report.players[1].unitCounts[0]==0 && cascade.d->armies.empty(),
            "cargo removed postorder without duplicate refund; later player's groups see removed passenger");
    d=fixture(); addArmy(*d,8,1,1); d->players[1].credits=0; d->players[1].foodFlags=1;
    AiSession ai; save::Error e; ok(ai.initializeAfterLoad(*d,e),e); auto c=context(); c.aiSession=&ai;
    auto remote=process(*d,c);
    require(remote.report.events.size()==2 && remote.report.events[0].aiDispatched && remote.report.events[1].aiDispatched &&
            remote.report.logAfter.entries.empty() && remote.report.retiredIds==std::vector<uint32_t>{8} && remote.report.rngAfter==c.ai.rng,
            "nonlocal upkeep and disband use real default AI dispatch without portrait draws");
    auto output=fixture(); EconomicUpkeepReport report; report.retiredIds={999}; const auto old=report;
    const auto before=bytes(*d), prior=bytes(*output);
    require(!processEconomicUpkeep(*d,context(),*output,report,e) && bytes(*d)==before && bytes(*output)==prior && report==old,
            "missing AI rolls back entire upkeep pass");
    d=fixture(); addArmy(*d,1,1); d->players[0].foodFlags=4; d->armies[0].job=1; d->jobs[0][0].armyIds[0]=1;
    const auto linked=bytes(*d);
    require(!processEconomicUpkeep(*d,context(),*d,report,e) && bytes(*d)==linked && report==old && e.message.find("task-force")!=std::string::npos,
            "late core deletion refuses task-force dangling refs; no invented detach, in-place rollback");
    d->armies[0].job=0; d->jobs[0][0].armyIds[0]=0;
    d->ministerJobs[0].resize(2); d->ministerJobs[0][0].next.raw=1;
    d->ministerJobs[0][1].type=13; d->ministerJobs[0][1].param[0]=1;
    auto deferred=process(*d);
    require(deferred.report.players[0].disband.deferredMaintainJobs==1 && deferred.d->ministerJobs[0][1].param[0]==1,
            "MaintainUnit jobs survive exactly for later original dispatch");
    d=fixture(); addArmy(*d,1,1); d->players[0].foodFlags=4; std::fill(std::begin(d->armies[0].name),std::end(d->armies[0].name),'X');
    const auto unnamed=bytes(*d);
    require(!processEconomicUpkeep(*d,context(),*d,report,e) && bytes(*d)==unnamed && report==old,"unbounded disband name rejects late atomically");
    d=fixture(); d->players[6].race=127;
    require(!processEconomicUpkeep(*d,context(),*output,report,e) && bytes(*output)==prior && report==old,
            "inactive player unsafe racial address still fails, because original reads all seven");
}
void corpus(const fs::path& directory) {
    if (directory.empty() || !fs::is_regular_file(directory/"TUTORIAL.SAV")) return;
    size_t count=0;
    auto one=[&](const save::Document& source) {
        // Cost-pass variants avoid manufacturing bankruptcies from historical
        // task-force state: preserve ALL armies, give explicit credit budget and
        // clear forced-disband4 only. These are not original-turn replay claims.
        const auto archival=bytes(source); auto d=std::make_unique<save::Document>(); save::Error e;
        LoadCoreReport loaded;
        ok(normalizeLoadCore(source,{-1,"Corpus"},*d,loaded,e),e);
        for (auto& p:d->players) { p.credits=100000000; p.foodFlags&=0xfbu; }
        AiSession ai; ok(ai.initializeAfterLoad(*d,e),e); auto c=context(); c.aiSession=&ai;
        auto out=process(*d,c);
        require(out.report.retiredIds.empty() && bytes(source)==archival,
                "funded normalized corpus cost pass must retain armies and archival source"); ++count;
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
    std::cout<<"economic upkeep: "<<count<<" core-normalized corpus funded cost-pass variants\n";
}
}
int main(int argc,char** argv) {
    try {
        rtl::srand(0x12345678); (void)rtl::lrand(); gg.rng2Seed=0xabcdef01;
        const auto low=rtl::seed(),high=rtl::seedHi(); const auto globals=std::make_unique<GameGlobals>(gg);
        const auto game=std::make_unique<GameState>(gs);
        costs(); shortagesAndSelection(); cascadesAndContexts(); corpus(argc>1?fs::path(argv[1]):fs::path{});
        require(rtl::seed()==low && rtl::seedHi()==high && std::memcmp(globals.get(),&gg,sizeof(gg))==0 &&
                std::memcmp(game.get(),&gs,sizeof(gs))==0,"upkeep modified global state/RNG");
        std::cout<<"economic upkeep tests passed\n"; return 0;
    } catch (const std::exception& e) { std::cerr<<"economic upkeep: "<<e.what()<<'\n'; return 1; }
}
