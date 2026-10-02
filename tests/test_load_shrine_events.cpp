// Independent CountShrines00486964 -> LogEventEx004237d0 load oracles.
// These tests do not claim a native window or RunAITurns was executed.
#include "game/load_shrine_events.h"
#include "game/event_portraits.h"
#include "game/runtime_state.h"
#include "game/save_files.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include <algorithm>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
using namespace dl2;
using namespace dl2::simulation;
namespace fs = std::filesystem;
void require(bool value, const char* message) { if (!value) throw std::runtime_error(message); }
void ok(bool value, const save::Error& e) { if (!value) throw std::runtime_error(e.message); }
std::vector<uint8_t> bytes(const save::Document& d) {
    std::vector<uint8_t> result; save::Error e; ok(save::encode(d,result,e),e); return result;
}
int32_t attitude(const Job& block, int player, int other) {
    int32_t result;
    std::memcpy(&result,reinterpret_cast<const uint8_t*>(&block)+size_t(player*7+other)*4,4);
    return result;
}
RngSnapshot seed(uint32_t value) {
    SessionRng rng; save::Error e; ok(rng.initialize(value,e),e); return rng.snapshot();
}
std::unique_ptr<save::Document> fixture() {
    auto d=std::make_unique<save::Document>();
    std::memcpy(d->header.text,save::kHeaderText,sizeof(save::kHeaderText));
    d->header.version=kSaveVersion; d->header.minusOne=-1;
    d->options.numPlayers=3; d->options.localPlayer=0; d->options.turn=15;
    d->options.gameId=192; d->options.gameSeed=657;
    d->options.victory=2; d->options.allowAlliances=1; d->options.aiSkill=2;
    d->world.width=2; d->world.height=1; d->world.numTerritories=2;
    d->world.rngSeed=975;
    for (size_t p=0;p<kMaxPlayers;++p) {
        auto& player=d->players[p]; player.index=uint8_t(p); player.race=int8_t(p);
        player.type=p==0?1:p<3?3:0;
        d->ministerJobs[p].resize(1); d->ministerJobs[p][0].type=1;
        for (auto& row:d->raceStats.v) row[p]=100;
    }
    d->players[0].relations[1]=0x10; d->players[2].relations[1]=0x10;
    d->tiles.resize(2); d->territories.resize(2);
    for (int i=0;i<2;++i) {
        auto& t=d->territories[size_t(i)].data;
        t.index=uint16_t(i+1); t.owner=int8_t(i==0?1:-1); t.terrain=1;
        t.population=400; t.morale=80; t.knowledge=100;
        t.numTiles=1; t.tiles[0].raw=uint32_t(i); t.centerTile=0;
        for (int site=0;site<kNumSites;++site) {
            t.sites[site].unk_00=uint16_t(site%6+(site/6)*256); t.sites[site].terrainFlags=1;
        }
        auto& tile=d->tiles[size_t(i)]; tile.x=uint8_t(i); tile.territory=int16_t(i+1); tile.terrain=3;
    }
    std::memcpy(d->territories[0].data.name,"Amber Landing",14);
    std::memcpy(d->territories[1].data.name,"West",5);
    uint32_t known=2; std::memcpy(d->territories[0].data.unk_8b0,&known,4);
    Building b{}; b.id=180; b.type=46; b.category=11; b.territory=1; b.site=6;
    d->buildings.push_back(b); d->territories[0].data.sites[6].building.raw=b.id;
    d->trailing={0xa7,0,0xff}; return d;
}
struct Prepared {
    std::unique_ptr<save::Document> document;
    LoadDerivedReport derived;
    AiSession ai;
};
Prepared prepared() {
    Prepared p; p.document=fixture(); save::Error e;
    ok(p.ai.initializeAfterLoad(*p.document,e),e);
    ok(rebuildLoadDerived(*p.document,*p.document,p.derived,e),e);
    require(p.derived.notices==std::vector<ShrineNotice>{{1,0,1,0x4d},{1,2,1,0x4d}},
            "real CountShrines must generate local then AI notices from original owner-known mask");
    return p;
}
AiReactionContext priorAi() {
    AiReactionContext result; result.rng=seed(0xfedcba98);
    result.gameAborted=true; result.relationChangeMask[5]=0xa50000ff;
    result.pendingMessages.push_back({1,1,31,4,{7,8,9}}); return result;
}
void goldenRoutes() {
    auto p=prepared(); const auto before=bytes(*p.document); const auto aiBefore=p.ai.snapshot();
    LoadedEventLog log; log.firstVisible=73;
    log.slotPayloads[0]={-999,7788};
    std::optional<AiReactionContext> context=priorAi(); const auto contextBefore=context;
    auto output=fixture(); LoadShrineEventsReport report; save::Error e{save::ErrorCode::Io,99,"old"};
    ok(replayLoadShrineEvents(*p.document,p.derived,p.ai,log,seed(0),context,*output,report,e),e);
    require(e.code==save::ErrorCode::None && !e.offset && e.message.empty(),"success clears prior error");
    require(bytes(*p.document)==before && p.ai.snapshot()==aiBefore && context==contextBefore && log.entries.empty(),
            "load shrine replay must preserve all sources and initialized AI bindings");
    require(report.deliveries==std::vector<ShrineEventDelivery>{
        {{1,0,1,0x4d},ShrineEventRoute::LocalLog,true},{{1,2,1,0x4d},ShrineEventRoute::AiReaction,false}},
        "local and nonlocal AI must follow original notice order");
    require(report.logAfter.entries.size()==1 && report.logAfter.firstVisible==73,"local log entry/view position differs");
    const auto& event=report.logAfter.entries[0];
    const std::string text(event.text.begin(),event.text.end());
    require(text=="Our allies, the Cyth, have discovered a hidden shrine in Amber Landing!  You may want to compliment them on their success." &&
            event.type==0x4d && event.player==1 && event.param==0 && event.category==2,
            "canonical shrine formatting and Ex payload must name the owner, not recipient or local player");
    require(event.portraitResource==data::eventPortraitNames(0,2)[0] &&
            report.logAfter.slotPayloads[0]==EventPayload{1,0} &&
            report.logAfter.pageIndices[1]==std::vector<uint32_t>{0},"portrait/page/payload native insertion differs");
    require(report.draws.size()==3 && report.draws[0].value==0 && report.draws[1].value==21468 &&
            report.draws[2].value==9988 && report.rngAfter.secondary==2802067423u,
            "seed0 independent secondary LCG golden sequence must run portrait before AI gratitude/variant");
    for (size_t i=0;i<report.draws.size();++i)
        require(report.draws[i].ordinal==i+1 && report.draws[i].operation==RngOperation::Secondary15 && report.draws[i].consumed,
                "combined notice trace must retain ordered actual primitive draws");
    require(report.draws[0].tag=="LogEventPortrait" && report.draws[1].tag=="AiGratitudeGate004047a0" &&
            report.logAfter.randomDraws.size()==1 && report.logAfter.rngAfterEvents.secondary==12345,
            "nested log describes last local operation; combined trace includes later AI draws");
    require(report.aiAfter && report.aiAfter->rng==report.rngAfter && report.aiAfter->gameAborted &&
            report.aiAfter->relationChangeMask[5]==0xa50000ff && report.aiAfter->relationChangeMask[2]==2 &&
            report.aiAfter->pendingMessages==context->pendingMessages,
            "authoritative RNG replaces stale prior RNG while mask/queue/abort state is preserved");
    require(attitude(output->scratchJob1,2,1)==4 && attitude(output->scratchJob2,2,1)==2 &&
            attitude(output->scratchJob1,2,0)==0 && output->events.empty(),
            "LogEventEx must react to owner1, not ordinary LogEvent extras0; owned log is not fabricated SAV events");
    // Hostile shrine uses a different exact format and consumes portrait + three
    // AI draws (gate21468, choice9988, variant22117), but does not change attitudes.
    for (auto& notice:p.derived.notices) notice.eventCode=0x4e;
    ok(replayLoadShrineEvents(*p.document,p.derived,p.ai,log,seed(0),context,*output,report,e),e);
    const auto& hostile=report.logAfter.entries[0];
    require(std::string(hostile.text.begin(),hostile.text.end())==
        "The vile Cyth have uncovered a hidden shrine in Amber Landing.  Capture it, colony leader, before they rob both the planet and us of its vital secrets..." &&
        report.draws.size()==4 && report.draws[3].value==22117 && attitude(output->scratchJob1,2,1)==0,
        "nonallied shrine follows hostile chat branch without gratitude relation change");
}
void emptyHumanAndAliases() {
    auto p=prepared(); save::Error e; auto output=fixture(); LoadShrineEventsReport report;
    LoadedEventLog log; log.firstVisible=19;
    p.derived.notices.resize(1); // Local only needs no AI transient state/binding.
    AiSession uninitialized;
    ok(replayLoadShrineEvents(*p.document,p.derived,uninitialized,log,seed(0),std::nullopt,*output,report,e),e);
    require(!report.aiAfter && report.draws.size()==1,"local shrine should not invent AI context or require its initialization");
    // Mutating human type after AInit is safe for this pure router test; no AI
    // function is reached for that recipient, and the signed negative slot skips.
    p.document->players[2].type=2; p.document->players[3].type=255;
    p.derived.notices={{1,2,1,0x4d},{1,3,1,0x4e}};
    ok(replayLoadShrineEvents(*p.document,p.derived,uninitialized,log,{},std::nullopt,*output,report,e),e);
    require(report.draws.empty() && report.logAfter==log && !report.rngAfter.initialized &&
            std::all_of(report.deliveries.begin(),report.deliveries.end(),[](const auto& d){return d.route==ShrineEventRoute::Ignored;}),
            "nonlocal human/negative types are native returns and require no RNG or AI context");
    p.derived.notices.clear(); auto old=bytes(*p.document);
    ok(replayLoadShrineEvents(*p.document,p.derived,uninitialized,log,{},std::nullopt,*p.document,report,e),e);
    require(bytes(*p.document)==old && report.logAfter==log && report.deliveries.empty(),"zero notices preserve document/log and permit alias");
    p=prepared(); std::optional<AiReactionContext> context=priorAi();
    ok(replayLoadShrineEvents(*p.document,p.derived,p.ai,log,seed(0),context,*output,report,e),e);
    auto expected=fixture(); LoadShrineEventsReport second;
    ok(replayLoadShrineEvents(*output,p.derived,p.ai,report.logAfter,report.rngAfter,report.aiAfter,*expected,second,e),e);
    ok(replayLoadShrineEvents(*output,p.derived,p.ai,report.logAfter,report.rngAfter,report.aiAfter,*output,report,e),e);
    require(report==second && bytes(*output)==bytes(*expected),"document/log/context/RNG report aliases must be safe together");
}
void rollbacks() {
    auto p=prepared(); auto output=fixture(); const auto source=bytes(*p.document), destination=bytes(*output);
    LoadShrineEventsReport report; report.rngAfter=seed(1234); report.logAfter.firstVisible=456; const auto sentinel=report;
    LoadedEventLog log; std::optional<AiReactionContext> context=priorAi(); save::Error e;
    auto unchanged=[&] {
        require(bytes(*p.document)==source && bytes(*output)==destination && report==sentinel,
                "failed shrine replay partially committed document/report");
    };
    require(!replayLoadShrineEvents(*p.document,p.derived,p.ai,log,seed(0),std::nullopt,*output,report,e),
            "nonlocal AI notice without explicit masks/queue must reject"); unchanged();
    // Valid local insertion then missing AI binding: all prior work rolls back.
    AiSession noBindings;
    require(!replayLoadShrineEvents(*p.document,p.derived,noBindings,log,seed(0),context,*output,report,e),
            "missing initialized recipient binding must reject even after local event"); unchanged();
    auto invalid=seed(0); invalid.format=99;
    require(!replayLoadShrineEvents(*p.document,p.derived,p.ai,log,invalid,context,*output,report,e),"invalid authoritative RNG accepted"); unchanged();
    context->rng.format=99; // Previous RNG is deliberately NOT validated/read.
    LoadShrineEventsReport successful;
    ok(replayLoadShrineEvents(*p.document,p.derived,p.ai,log,seed(0),context,*output,successful,e),e);
    *output=*fixture();
    context->pendingMessages.resize(kAiMessageCapacity+1);
    require(!replayLoadShrineEvents(*p.document,p.derived,p.ai,log,seed(0),context,*output,report,e),"oversized prior queue accepted"); unchanged();
    context=priorAi(); auto notices=p.derived;
    notices.notices.back().owner=4;
    require(!replayLoadShrineEvents(*p.document,notices,p.ai,log,seed(0),context,*output,report,e),"mismatched notice owner accepted"); unchanged();
    p.derived.notices.resize(1);
    log.poolBytes=1;
    require(!replayLoadShrineEvents(*p.document,p.derived,p.ai,log,seed(0),context,*output,report,e),"inconsistent existing log pool accepted"); unchanged();
    log={}; std::fill(std::begin(p.document->territories[0].data.name),std::end(p.document->territories[0].data.name),'X');
    const auto malformed=bytes(*p.document);
    require(!replayLoadShrineEvents(*p.document,p.derived,p.ai,log,seed(0),context,*p.document,report,e) &&
            bytes(*p.document)==malformed && report==sentinel,"unterminated source name must reject without alias mutation");
}
bool has(const runtime::LoadReport& report,runtime::MissingLoadCapability capability) {
    return std::find(report.missing.begin(),report.missing.end(),capability)!=report.missing.end();
}
void runtimeIntegration() {
    auto source=fixture(); const auto before=bytes(*source); save::Error e;
    runtime::LoadContext context; context.startup=LoadStartupContext{seed(0)};
    context.previousWorld=source->world; context.clockMs=975321; context.previousAi=priorAi();
    runtime::State state; runtime::LoadReport report;
    ok(state.prepare(*source,e),e); const auto building=state.buildingById(180);
    ok(state.normalizeLoad({},report,e,runtime::LoadScope::Partial,context),e);
    require(report.headlessComplete && !report.complete && report.shrineNoticesDelivered && report.shrineRandomDraws==3 &&
            report.missing==std::vector<runtime::MissingLoadCapability>{runtime::MissingLoadCapability::NativePresentation},
            "complete explicit context must deliver load effects without claiming native/playable activation");
    require(state.loadDerived() && state.loadDerived()->notices.size()==2 && state.loadShrineEvents() &&
            state.loadedEvents() && state.loadedEvents()->entries.size()==1 && state.aiReactionContext() &&
            !state.aiReactionContext()->gameAborted && state.aiReactionContext()->relationChangeMask[5]==0xa50000ff &&
            state.aiReactionContext()->pendingMessages==context.previousAi->pendingMessages,
            "State must own effective derived/notices/AI log; native reset clears only abort, not queue/masks");
    require(state.sessionRng()==seed(uint32_t(source->options.gameId)) &&
            state.aiReactionContext()->rng==state.sessionRng() &&
            state.loadShrineEvents()->rngAfter!=state.sessionRng() && state.buildingById(180)==building && bytes(*source)==before,
            "notice sequence precedes final load reseed and preserves entity identities/source");
    runtime::State moved=std::move(state);
    require(moved.loadShrineEvents() && moved.loadDerived() && !state.loadShrineEvents() && !state.loadDerived(),
            "effective shrine/derived state must transfer on move");
    ok(moved.prepare(*source,e),e);
    require(!moved.loadShrineEvents() && !moved.loadDerived() && !moved.aiReactionContext(),"prepare must discard prior load-session effects");
    context.previousAi.reset();
    ok(moved.normalizeLoad({},report,e,runtime::LoadScope::Partial,context),e);
    require(!report.headlessComplete && !report.shrineNoticesDelivered &&
            has(report,runtime::MissingLoadCapability::ShrineEventDelivery) && !moved.loadShrineEvents() &&
            moved.loadedEvents()->entries.empty(),"absent AI context leaves explicit missing capability, no partially delivered local notice");
    // Force a later labor failure AFTER both notices: unowned housing has no
    // refresh and no task, so original Balance would write slot-1.
    Building bad{}; bad.id=181; bad.type=1; bad.category=17; bad.territory=2; bad.site=0;
    source->buildings.push_back(bad); source->territories[1].data.sites[0].building.raw=181;
    context.previousAi=priorAi(); ok(moved.prepare(*source,e),e);
    const auto* old=moved.document(); const auto oldBytes=bytes(*old); const auto oldReport=report;
    require(!moved.normalizeLoad({},report,e,runtime::LoadScope::Partial,context) && moved.document()==old &&
            moved.stage()==runtime::Stage::Prepared && bytes(*moved.document())==oldBytes && report==oldReport &&
            !moved.loadShrineEvents() && !moved.loadedEvents() && !moved.aiReactionContext() && !moved.sessionRng().initialized,
            "late labor error must roll back earlier document/log/AI/RNG and all derived state");
}
std::vector<std::string> scenarioNames(const fs::path& path) {
    const auto size=fs::file_size(path); require(size>=4 && size<=save::kMaxFileBytes,"invalid corpus index size");
    std::ifstream in(path,std::ios::binary); uint8_t raw[4]{};
    require(bool(in.read(reinterpret_cast<char*>(raw),4)),"cannot read corpus index");
    const uint32_t count=uint32_t(raw[0])|(uint32_t(raw[1])<<8)|(uint32_t(raw[2])<<16)|(uint32_t(raw[3])<<24);
    require(count<=(size-4)/12,"truncated corpus index"); std::vector<std::string> names;
    for (uint32_t i=0;i<count;++i) { char entry[12]{}; require(bool(in.read(entry,12)),"cannot read corpus entry"); names.emplace_back(entry,std::find(entry,entry+8,'\0')); }
    return names;
}
size_t corpusOne(const save::Document& source) {
    const auto before=bytes(source); auto normalized=std::make_unique<save::Document>();
    LoadCoreReport core; LoadDerivedReport derived; AiSession ai; save::Error e;
    ok(normalizeLoadCore(source,{},*normalized,core,e),e);
    ok(ai.initializeAfterLoad(*normalized,e),e);
    LoadedEventLog log; const EventLoadContext initial{seed(0xabcdef01),{}};
    ok(rebuildLoadedEvents(*normalized,initial,log,e),e);
    ok(rebuildLoadDerived(*normalized,*normalized,derived,e),e);
    const auto normalizedBefore=bytes(*normalized);
    auto first=std::make_unique<save::Document>(),second=std::make_unique<save::Document>();
    LoadShrineEventsReport a,b; const std::optional<AiReactionContext> context=priorAi();
    ok(replayLoadShrineEvents(*normalized,derived,ai,log,log.rngAfterEvents,context,*first,a,e),e);
    ok(replayLoadShrineEvents(*normalized,derived,ai,log,log.rngAfterEvents,context,*second,b,e),e);
    require(a==b && bytes(*first)==bytes(*second) && bytes(source)==before && bytes(*normalized)==normalizedBefore,
            "corpus shrine replay must be deterministic and preserve archival/normalized sources");
    require(a.deliveries.size()==derived.notices.size() && a.aiAfter && a.aiAfter->rng==a.rngAfter,
            "corpus notices/context were silently omitted");
    return a.deliveries.size();
}
void optionalCorpus(const fs::path& directory) {
    if (directory.empty() || !fs::is_regular_file(directory/"TUTORIAL.SAV")) {
        std::cout<<"load shrine events: optional corpus unavailable; synthetic tests ran\n"; return;
    }
    size_t count=0,notices=0;
    for (const char* name:{"TUTORIAL.SAV","Saves/AUTOSAVE.SAV","Campaign/AUTOSAVE.CPN","Campaign/ChCht001.CPN"}) {
        if (!fs::is_regular_file(directory/name)) continue;
        auto d=std::make_unique<save::Document>(); save::Error e; ok(save::readDocument(directory/name,*d,e),e);
        try { notices+=corpusOne(*d); } catch (const std::exception& ex) { throw std::runtime_error(std::string(name)+": "+ex.what()); }
        ++count;
    }
    if (fs::is_regular_file(directory/"LEVELS.HDX") && fs::is_regular_file(directory/"LEVELS.HDD"))
        for (const auto& name:scenarioNames(directory/"LEVELS.HDX")) {
            auto d=std::make_unique<save::Document>(); save::Error e; ok(save::readScenario(directory/"LEVELS",name,*d,e),e);
            try { notices+=corpusOne(*d); } catch (const std::exception& ex) { throw std::runtime_error(name+": "+ex.what()); }
            ++count;
        }
    std::cout<<"load shrine events corpus: "<<count<<" documents, "<<notices<<" notices, sources preserved\n";
}
}
int main(int argc,char** argv) {
    try {
        rtl::srand(0x12345678); (void)rtl::lrand(); gg.rng2Seed=0xabcd5678;
        const auto low=rtl::seed(),high=rtl::seedHi();
        const auto game=std::make_unique<GameState>(gs); const auto globals=std::make_unique<GameGlobals>(gg);
        goldenRoutes(); emptyHumanAndAliases(); rollbacks(); runtimeIntegration();
        optionalCorpus(argc>1?fs::path(argv[1]):fs::path{});
        require(rtl::seed()==low && rtl::seedHi()==high && std::memcmp(game.get(),&gs,sizeof(gs))==0 &&
                std::memcmp(globals.get(),&gg,sizeof(gg))==0,"load shrine replay changed global game/RNG state");
        std::cout<<"load shrine event tests passed\n"; return 0;
    } catch (const std::exception& e) { std::cerr<<"load shrine events: "<<e.what()<<'\n'; return 1; }
}
