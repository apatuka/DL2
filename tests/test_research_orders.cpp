// Independent original-function oracles plus explicit command-policy checks.
#include "game/research_orders.h"
#include "game/research_rules.h"
#include "game/load_profile.h"
#include "game/save_files.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include <algorithm>
#include <bit>
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
    d->options.numPlayers=2; d->options.localPlayer=0; d->options.turn=19; d->options.nextGlobalId=100;
    d->world.width=1; d->world.height=1; d->world.numTerritories=1; d->territories.resize(1); d->tiles.resize(1);
    for (int p=0;p<7;++p) {
        d->players[size_t(p)].index=uint8_t(p); d->players[size_t(p)].race=2; d->players[size_t(p)].type=p?3:1;
        d->ministerJobs[size_t(p)].resize(1); d->ministerJobs[size_t(p)][0].type=1;
    }
    auto& t=d->territories[0].data; t.index=1; t.owner=0; t.numTiles=1; t.population=100;
    std::memcpy(t.name,"Alpha",6); d->tiles[0].territory=1;
    d->trailing={3,255,77}; return d;
}
std::vector<uint8_t> bytes(const save::Document& d) {
    std::vector<uint8_t> out; save::Error e; ok(save::encode(d,out,e),e);
    for (const auto& t:d.territories) { const auto* p=reinterpret_cast<const uint8_t*>(&t.data);
        out.insert(out.end(),p+kTerritorySavedBytes,p+sizeof(Territory)); }
    return out;
}
struct Outcome { std::unique_ptr<save::Document> d=std::make_unique<save::Document>(); ResearchOrderReport r; };
Outcome run(const save::Document& d,ResearchOrderKind kind,int tech,ResearchOrderContext context={0,-1},int actor=0) {
    const auto before=bytes(d); Outcome out; save::Error e{save::ErrorCode::Io,9,"old"};
    ok(applyResearchOrder(d,{actor,kind,tech},context,*out.d,out.r,e),e);
    require(bytes(d)==before && e.code==save::ErrorCode::None && !e.offset && e.message.empty(),"research order changed source or did not clear error");
    auto alias=std::make_unique<save::Document>(d); ResearchOrderReport repeated;
    ok(applyResearchOrder(*alias,{actor,kind,tech},context,*alias,repeated,e),e);
    require(bytes(*alias)==bytes(*out.d) && repeated==out.r,"aliased research order differs"); return out;
}
void lowLevelAndDefault() {
    auto d=fixture(); d->localList={999,0,5}; d->players[1].index=255; d->techs[3].progress[1]=65535;
    for (int value:{0,3,47,128,255}) {
        auto dest=fixture(); const auto source=bytes(*d); auto expected=std::make_unique<save::Document>(*d);
        expected->players[1].currentResearch=std::bit_cast<int8_t>(uint8_t(value));
        ResearchSelectionChange r; save::Error e{save::ErrorCode::Io,42,"old"};
        ok(setResearchSelectionOffline(*d,1,uint8_t(value),*dest,r,e),e);
        require(bytes(*dest)==bytes(*expected) && bytes(*d)==source && r.player==1 && r.after==expected->players[1].currentResearch &&
                r.setterInvoked && e.code==save::ErrorCode::None,"low-level setter must change only physical player's byte, no authority/queue/prereq checks");
        ok(setResearchSelectionOffline(*dest,1,uint8_t(value),*dest,r,e),e);
        require(bytes(*dest)==bytes(*expected) && r.setterInvoked,"same-byte setter still really invoked, aliases supported");
    }
    d=fixture(); int choice=-88; save::Error e;
    ok(chooseDefaultResearch(*d,0,0,choice,e),e); require(choice==47,"no available tech falls back to unknown47 WITHOUT prerequisites");
    d->techs[47].knownMask=1; ok(chooseDefaultResearch(*d,0,0,choice,e),e); require(choice==0,"known47 prevents fallback");
    d->techs[9].availableMask=d->techs[2].availableMask=d->techs[2].knownMask=1;
    d->options.campaign=15; ok(chooseDefaultResearch(*d,0,16,choice,e),e);
    require(choice==2,"lowest available wins despite already-known and campaign-forbidden flags");
    d->options.campaign=43; ok(chooseDefaultResearch(*d,0,16,choice,e),e);
    require(choice==2,"available early return must not inspect invalid campaign selector");
    d=fixture(); d->players[0].index=255; d->techs[6].availableMask=0x8000;
    ok(chooseDefaultResearch(*d,0,0,choice,e),e); require(choice==6,"default selection sign-extends WORD and masks Player.index&31");
    d=fixture(); d->players[0].index=32; d->techs[3].availableMask=1;
    ok(chooseDefaultResearch(*d,0,0,choice,e),e); require(choice==3,"default selector does not replace Player.index with physical slot");
    d=fixture(); d->options.campaign=6; ok(chooseDefaultResearch(*d,0,16,choice,e),e); require(choice==0,"active campaign6 blocks fallback47");
    ok(chooseDefaultResearch(*d,0,0,choice,e),e); require(choice==47,"disabled live flag4 does not derive campaign restrictions");
    d->options.campaign=0; choice=91;
    require(!chooseDefaultResearch(*d,0,16,choice,e) && choice==91,"inconsistent campaign mask must preserve query output");
}
void selectionAndCommit() {
    auto d=fixture(); d->localList={1,2,2,7}; d->players[0].currentResearch=5; d->techs[2].availableMask=1;
    auto out=run(*d,ResearchOrderKind::Select,2,{0,2});
    require(out.r.accepted && out.r.candidateResearch==2 && !out.r.setterInvoked && out.r.setterPlayer==-1 &&
            out.r.researchBefore==5 && out.r.researchAfter==5 && out.d->players[0].currentResearch==5 &&
            out.d->localList==std::vector<uint32_t>{2} && out.r.duplicatesDiscarded==std::vector<uint32_t>{2} &&
            out.r.removed==std::vector<uint32_t>({1,2,7}) && out.r.queueStructureChanged,
            "commitComparison is explicit global, NOT the current selection; replacing queue need not write selection");
    out=run(*d,ResearchOrderKind::Select,2,{0,5});
    require(out.r.setterInvoked && out.r.setterPlayer==0 && out.r.researchAfter==2,"different comparison invokes real setter");
    d->localList={2}; d->players[0].currentResearch=2; out=run(*d,ResearchOrderKind::Select,2,{0,-1});
    require(bytes(*out.d)==bytes(*d) && out.r.setterInvoked && out.r.queueStructureChanged,
            "byte-identical replacement still replaces queue nodes and invokes requested native setter");
    d=fixture(); d->localList={1,1}; d->players[0].currentResearch=4;
    out=run(*d,ResearchOrderKind::Select,5);
    require(!out.r.accepted && out.r.denial==ResearchOrderDenial::NotQueueable && bytes(*out.d)==bytes(*d) &&
            out.r.duplicatesDiscarded.empty() && !out.r.queueStructureChanged && !out.r.setterInvoked,
            "denied Select checks EMPTY queue, rolls back even draft dedup, never silently commits");
    out=run(*d,ResearchOrderKind::Select,1);
    require(out.r.accepted && out.r.researchAfter==1,"basic tech with no prerequisites is queueable even when available bit is absent");
    d->techs[1].knownMask=1; out=run(*d,ResearchOrderKind::Select,1);
    require(!out.r.accepted,"known tech without available bit denied by native queue predicate");
    d->techs[1].availableMask=1; out=run(*d,ResearchOrderKind::Select,1);
    require(out.r.accepted,"available-mask early return wins even when technology is known");
    d=fixture(); d->options.campaign=15; out=run(*d,ResearchOrderKind::Select,2,{16,-1});
    require(!out.r.accepted && out.r.denial==ResearchOrderDenial::CampaignRestriction,"campaign advice represented as denial, no fabricated event");
    out=run(*d,ResearchOrderKind::Select,2,{0,-1}); require(out.r.accepted,"explicit flags0 permits otherwise restricted technology");
}
void togglesAndClear() {
    auto d=fixture(); d->localList={1,2,2,3};
    auto out=run(*d,ResearchOrderKind::ToggleQueue,7);
    require(out.r.accepted && out.d->localList==std::vector<uint32_t>({1,2,3,7}) && out.r.duplicatesDiscarded==std::vector<uint32_t>{2} &&
            out.r.researchAfter==1,"queued prerequisites permit append after first-occurrence dedup");
    auto removed=run(*out.d,ResearchOrderKind::ToggleQueue,2);
    require(removed.r.removed==std::vector<uint32_t>({2,7}) && removed.d->localList==std::vector<uint32_t>({1,3}),
            "remove prerequisite prunes newly ineligible dependent in original list order");
    d->localList={1,2,2}; out=run(*d,ResearchOrderKind::ToggleQueue,7);
    require(!out.r.accepted && out.d->localList==d->localList,
            "opening dedup means duplicate2 cannot fake both missing prerequisites for Fusion Cannon");
    d->localList={1,2,3,7}; d->raceStats.v[55][2]=1; out=run(*d,ResearchOrderKind::ToggleQueue,2);
    require(out.d->localList==std::vector<uint32_t>({1,3,7}) && out.r.removed==std::vector<uint32_t>{2},
            "racial prerequisite OR preserves dependent with one remaining queued prerequisite");
    d=fixture(); d->localList={1,2}; d->players[0].currentResearch=6;
    out=run(*d,ResearchOrderKind::ClearQueue,999,{0,-1});
    require(out.r.accepted && out.r.usedDefault && out.r.researchAfter==47 && out.d->localList.empty() &&
            out.r.removed==std::vector<uint32_t>({1,2}),"Clear ignores technology argument and uses actual default fallback47, no Stop0 invention");
    d->options.campaign=6; out=run(*d,ResearchOrderKind::ClearQueue,0,{16,0});
    require(out.r.candidateResearch==0 && !out.r.setterInvoked && out.r.researchAfter==6 && out.d->localList.empty(),
            "empty queue/default0 with comparison0 does NOT clear actual research6");
    out=run(*d,ResearchOrderKind::ClearQueue,0,{16,-1});
    require(out.r.setterInvoked && out.r.researchAfter==0,"comparison sentinel changes native setter branch explicitly");
    d=fixture(); out=run(*d,ResearchOrderKind::ClearQueue,0);
    require(!out.r.queueStructureChanged && out.r.setterInvoked && out.r.researchAfter==47,"empty-to-empty commit has no queue allocation but selection effect");
    d=fixture(); d->localList={0,1}; d->techs[1].availableMask=1; out=run(*d,ResearchOrderKind::ToggleQueue,2,{0,-1});
    require(!out.r.accepted,"literal zero prerequisites match saved queue0 and affect eligibility");
}
void automatic() {
    auto d=fixture(); d->techs[0].knownMask=1; d->techs[2].availableMask=1; d->localList={5,1};
    auto dest=fixture(); ResearchAutoReport r; save::Error e;
    ok(autoResearchLocal(*d,0,*dest,r,e),e);
    require(r.searchedBuildings && !r.foundResearchBuilding && !r.setterInvoked && bytes(*dest)==bytes(*d),"zero current and no research building returns before known0");
    Building b{}; b.id=77; b.type=1; b.category=5; b.flags=6; b.territory=1; b.site=0; b.turnsLeft=-1;
    d->buildings.push_back(b); d->territories[0].data.owner=-1; d->territories[0].data.sites[0].building.raw=77;
    const auto before=bytes(*d); ok(autoResearchLocal(*d,0,*dest,r,e),e);
    require(r.foundResearchBuilding && r.knownSelection && r.setterInvoked && r.researchAfter==2 && dest->localList==d->localList && bytes(*d)==before,
            "ANY saved category5 building with flags6 qualifies regardless type, owner or signed work; queue untouched");
    auto alias=std::make_unique<save::Document>(*d); ResearchAutoReport repeated;
    ok(autoResearchLocal(*alias,0,*alias,repeated,e),e); require(bytes(*alias)==bytes(*dest) && r==repeated,"auto research alias differs");
    d->techs[0].knownMask=0; ok(autoResearchLocal(*d,0,*dest,r,e),e);
    require(r.foundResearchBuilding && !r.knownSelection && !r.setterInvoked,"building alone does not select research unless tech0 is known");
    d->techs[0].knownMask=1; d->buildings[0].flags=4; ok(autoResearchLocal(*d,0,*dest,r,e),e);
    require(!r.foundResearchBuilding && !r.setterInvoked,"auto research needs BOTH flag2 and flag4");
    d->players[0].currentResearch=1; d->players[0].index=1; d->techs[1].knownMask=1; d->techs[3].availableMask=2;
    ok(autoResearchLocal(*d,0,*dest,r,e),e);
    require(!r.searchedBuildings && r.knownSelection && r.researchAfter==3 && dest->players[1].currentResearch==0,
            "auto known guard uses LOCAL slot, default uses Player.index, setter writes local slot");
    d->techs[1].knownMask=2; ok(autoResearchLocal(*d,0,*dest,r,e),e);
    require(!r.knownSelection && !r.setterInvoked,"auto guard must not use Player.index known mask");
}
void failuresAndSharedLeaves() {
    auto d=fixture(), dest=fixture(); dest->options.turn=99; const auto previous=bytes(*dest);
    ResearchOrderReport report; report.removed={777}; const auto old=report; save::Error e;
    const auto rejected=[&](ResearchOrderRequest request,ResearchOrderContext context={0,-1}) {
        const auto before=bytes(*d);
        require(!applyResearchOrder(*d,request,context,*dest,report,e) && bytes(*d)==before && bytes(*dest)==previous && report==old,
                "invalid research order must roll back document and report");
    };
    rejected({1,ResearchOrderKind::Select,1}); rejected({0,ResearchOrderKind::Select,0}); rejected({0,ResearchOrderKind::ToggleQueue,48});
    rejected({0,static_cast<ResearchOrderKind>(99),1});
    d->players[0].index=1; rejected({0,ResearchOrderKind::ClearQueue,0}); d->players[0].index=0;
    d->players[0].type=3; rejected({0,ResearchOrderKind::Select,1}); d->players[0].type=1;
    d->localList={1,999}; rejected({0,ResearchOrderKind::ClearQueue,0});
    d->localList={1,2}; rejected({0,ResearchOrderKind::ClearQueue,0},{16,-1}); //failure AFTER cleared draft.
    const auto source=bytes(*d);
    require(!applyResearchOrder(*d,{0,ResearchOrderKind::ClearQueue,0},{16,-1},*d,report,e) && bytes(*d)==source && report==old,
            "late default-selection campaign failure rolls back in-place clear");
    ResearchSelectionChange selection{6,2,3,true}; const auto oldSelection=selection;
    require(!setResearchSelectionOffline(*d,7,255,*dest,selection,e) && bytes(*dest)==previous && selection==oldSelection,"low-level player bound is transactional");
    ResearchAutoReport automatic; automatic.player=6; const auto oldAuto=automatic; d->players[0].currentResearch=-1;
    require(!autoResearchLocal(*d,0,*dest,automatic,e) && bytes(*dest)==previous && automatic==oldAuto,"auto unsafe selected technology rejects transactionally");
    d=fixture(); bool answer=true; std::vector<uint32_t> oversized(save::kMaxListNodes+1,1);
    require(!research_detail::canQueue(*d,0,oversized,7,0,answer,e) && answer && e.code==save::ErrorCode::Limit,"query resource limit does not change result");
    std::vector<uint32_t> queue{1,999}, removed{77}; const auto priorQueue=queue;
    require(!research_detail::pruneQueue(*d,0,0,queue,removed,e) && queue==priorQueue && removed==std::vector<uint32_t>{77},"shared pruning error leaves both outputs intact");
    require(!research_detail::pruneQueue(*d,0,0,queue,queue,e) && queue==priorQueue,"shared pruning refuses aliased output vectors");
    // Shared exact predicate still counts duplicates. Only opening a UI draft
    // deduplicates; acquisition/ordinary predicate must not acquire that policy.
    queue={2,2}; answer=false; ok(research_detail::canQueue(*d,0,queue,7,0,answer,e),e);
    require(answer,"shared query preserves literal duplicate prerequisite count");
}
void corpus(const fs::path& directory) {
    if (directory.empty() || !fs::is_regular_file(directory/"TUTORIAL.SAV")) return;
    size_t count=0;
    auto one=[&](const save::Document& archival) {
        const auto before=bytes(archival); auto d=std::make_unique<save::Document>(); save::Error e; LoadCoreReport loaded;
        ok(normalizeLoadCore(archival,{-1,"Research orders"},*d,loaded,e),e);
        const int actor=d->options.localPlayer;
        // Caller-selected lab comparison, EXPLICITLY not restoration of the
        // original unsaved UI global. Campaign mask is the real load report.
        auto out=run(*d,ResearchOrderKind::ClearQueue,0,{loaded.campaignGoalMask,d->players[size_t(actor)].currentResearch},actor);
        require(out.r.accepted && out.d->localList.empty() && bytes(archival)==before,"corpus clear order changes only normalized owned copy");
        ResearchAutoReport automatic; ok(autoResearchLocal(*d,loaded.campaignGoalMask,*out.d,automatic,e),e); ++count;
    };
    for (const char* name:{"TUTORIAL.SAV","Saves/AUTOSAVE.SAV","Campaign/AUTOSAVE.CPN","Campaign/ChCht001.CPN"})
        if (fs::is_regular_file(directory/name)) { auto d=std::make_unique<save::Document>(); save::Error e; ok(save::readDocument(directory/name,*d,e),e); one(*d); }
    std::ifstream index(directory/"LEVELS.HDX",std::ios::binary);
    if (index) { uint32_t total=0; require(bool(index.read(reinterpret_cast<char*>(&total),4)) && total<=4096,"invalid corpus index");
        for (uint32_t i=0;i<total;++i) { char entry[12]{}; require(bool(index.read(entry,12)),"truncated corpus index");
            auto d=std::make_unique<save::Document>(); save::Error e; const std::string name(entry,std::find(entry,entry+8,'\0'));
            ok(save::readScenario(directory/"LEVELS",name,*d,e),e); one(*d); }
    }
    std::cout<<"research orders: "<<count<<" core-normalized corpus variants\n";
}
} // namespace
int main(int argc,char** argv) {
    try {
        rtl::srand(0x12345678); (void)rtl::lrand(); gg.rng2Seed=0xabcdef01;
        const auto low=rtl::seed(),high=rtl::seedHi(); const auto globals=std::make_unique<GameGlobals>(gg); const auto game=std::make_unique<GameState>(gs);
        lowLevelAndDefault(); selectionAndCommit(); togglesAndClear(); automatic(); failuresAndSharedLeaves();
        corpus(argc>1?fs::path(argv[1]):fs::path{});
        require(rtl::seed()==low && rtl::seedHi()==high && std::memcmp(globals.get(),&gg,sizeof(gg))==0 && std::memcmp(game.get(),&gs,sizeof(gs))==0,
                "research orders consumed RNG or modified global state");
        std::cout<<"research order tests passed\n"; return 0;
    } catch (const std::exception& e) { std::cerr<<"research orders: "<<e.what()<<'\n'; return 1; }
}
