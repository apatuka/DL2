// Independent load-time event/timer oracles derived from original functions.
// Does not assert that a whole game has been activated or a turn executed.
#include "game/load_session.h"
#include "game/load_startup.h"
#include "game/event_portraits.h"
#include "game/data_tables.h"
#include "game/save_files.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include <algorithm>
#include <array>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
using namespace dl2;
using namespace dl2::simulation;
using save::Document;
namespace fs = std::filesystem;
void require(bool condition, const char* message) {
    if (!condition) throw std::runtime_error(message);
}
void cleared(const save::Error& error) {
    require(error.code==save::ErrorCode::None && error.offset==0 && error.message.empty(),
            "successful load-session operation did not clear error");
}
std::unique_ptr<Document> fixture() {
    auto d=std::make_unique<Document>();
    std::memcpy(d->header.text,save::kHeaderText,sizeof(save::kHeaderText));
    d->header.version=kSaveVersion; d->header.minusOne=-1;
    d->options.numPlayers=3; d->options.localPlayer=0; d->options.eventLogFirst=37;
    d->options.gameId=7151; d->options.gameSeed=0x12345678; d->options.turn=51;
    d->options.allowAlliances=1;
    d->world.width=d->world.height=1; d->world.numTerritories=1; d->world.rngSeed=0xfedcba98;
    d->tiles.resize(1); d->tiles[0].territory=1;
    d->territories.resize(1); auto& t=d->territories[0].data;
    t.index=1; t.owner=0; t.terrain=1; t.numTiles=1; t.tiles[0].raw=0;
    for (size_t p=0;p<kMaxPlayers;++p) {
        auto& player=d->players[p]; player.index=uint8_t(p); player.race=int8_t(p);
        player.type=p<3?uint8_t(p+1):uint8_t(0);
        d->ministerJobs[p].resize(1); d->ministerJobs[p][0].type=1;
    }
    d->players[0].race=2;
    return d;
}
void add(Document& d,uint16_t type,std::vector<uint8_t> text,int32_t player=-17,int32_t param=1234567) {
    require(text.size()<=UINT16_MAX,"test event is too large");
    d.events.push_back({{type,uint16_t(text.size()),player,param},std::move(text)});
    d.options.eventCount=int32_t(d.events.size());
}
std::vector<uint8_t> bytes(const Document& d) {
    std::vector<uint8_t> result; save::Error error;
    require(save::encode(d,result,error),"test document is not archivally valid"); return result;
}
EventLoadContext context(uint32_t seed=1) {
    SessionRng rng; save::Error error;
    require(rng.initialize(seed,error),"cannot initialize explicit test RNG");
    return {rng.snapshot(),{2,5,0,0,0,0,0}};
}
LoadedEventLog sentinelLog() {
    LoadedEventLog log;
    log.entries.push_back({321,-7,8,-1,{1,2,3},"sentinel"});
    log.pageIndices[4]={9,8}; log.poolBytes=999; log.firstVisible=-73;
    log.randomDraws.push_back({42,RngOperation::TaggedRange,17,0,12,"old",true});
    log.rngAfterEvents=context(99).rngBeforeEvents; return log;
}
void replay(const Document& d,const EventLoadContext& input,LoadedEventLog& result) {
    save::Error error{save::ErrorCode::Io,71,"old"};
    if (!rebuildLoadedEvents(d,input,result,error)) throw std::runtime_error(error.message);
    cleared(error);
}
void rejectReplay(const Document& d,const EventLoadContext& input) {
    const auto before=bytes(d); const auto rngBefore=input.rngBeforeEvents;
    const auto citiesBefore=input.citiesBeforeLoad;
    auto result=sentinelLog(); const auto resultBefore=result; save::Error error;
    require(!rebuildLoadedEvents(d,input,result,error) && error.code!=save::ErrorCode::None && !error.message.empty(),
            "unsupported event replay succeeded or lacked a diagnostic");
    require(result==resultBefore && bytes(d)==before && input.rngBeforeEvents==rngBefore &&
            input.citiesBeforeLoad==citiesBefore,"event replay failure changed source, context or prior output");
}

void goldenReplay() {
    auto d=fixture();
    add(*d,0,{'r','a','w'},std::numeric_limits<int32_t>::min(),std::numeric_limits<int32_t>::max());
    add(*d,1,{'%',0xff,'s'}); // Preserved bytes, never interpreted as a format.
    add(*d,65,{'c','i','t','i','e','s'});
    add(*d,54,{'t','e','c','h'});
    add(*d,59,{});
    add(*d,91,{'h','i','d','d','e','n'}); // Category7 has no visible page.
    add(*d,123,{'l','o','s','t'});
    add(*d,0xffff,{'u','n','k','n','o','w','n'}); // Original unknown-ID fallback row0.
    const auto original=bytes(*d); auto input=context(); const auto before=input.rngBeforeEvents;
    auto out=sentinelLog(); replay(*d,input,out);
    constexpr int16_t categories[]{0,2,2,1,6,7,-1,0};
    const char* portraits[]{"","HHWARND","HHXENOC","HHTECHB","","HHEXITJ","HHELIMC",""};
    require(out.entries.size()==8 && out.poolBytes==41 && out.firstVisible==37,"golden event count/pool/firstVisible mismatch");
    for (size_t i=0;i<out.entries.size();++i) {
        const auto& event=out.entries[i]; const auto& saved=d->events[i];
        require(event.type==saved.record.type && event.player==saved.record.player && event.param==saved.record.param &&
                event.category==categories[i] && event.text==saved.text && event.portraitResource==portraits[i],
                "golden event payload/category/portrait differs");
    }
    const std::array<std::vector<uint32_t>,6> pages{{{0,7},{1,2,6},{},{},{3},{4}}};
    require(out.pageIndices==pages,"event page membership/order differs from 004228d4");
    constexpr uint32_t draws[]{16838,5758,10113,17515};
    require(out.randomDraws.size()==4,"city/no-portrait event unexpectedly consumed RNG");
    for (size_t i=0;i<4;++i) {
        const RngEvent expected{uint64_t(i+1),RngOperation::Secondary15,0,0,draws[i],"LoadEventLogPortrait",true};
        require(out.randomDraws[i]==expected,"portrait RNG did not consume the fixed secondary sequence in file order");
    }
    auto expected=before; expected.secondary=3295386429u;
    expected.counters.operations=expected.counters.secondary15=4;
    require(out.rngAfterEvents==expected && input.rngBeforeEvents==before && bytes(*d)==original,
            "portrait replay touched RTL/source/context or produced the wrong final secondary state");
    auto again=sentinelLog(); replay(*d,input,again); require(again==out,"event replay is not deterministic");
    d->options.gameId=-1; d->options.gameSeed=777; d->world.rngSeed=0;
    replay(*d,input,again); require(again==out,"event replay invented a pre-event seed from SAV gameId/world seeds");
    auto other=context(0); replay(*d,other,again);
    require(again.randomDraws.front().value==0 && again.entries[1].portraitResource=="HHWARNA",
            "explicit pre-load RNG context was ignored");
    // Own all outputs: later source mutation must not alias event text.
    d->events[1].text[0]='!';
    require(out.entries[1].text[0]=='%',"loaded log borrowed source text storage");
}

void cityComparisonAndPages() {
    auto d=fixture(); add(*d,65,{}); add(*d,66,{}); add(*d,67,{});
    auto input=context(); LoadedEventLog out;
    const auto check=[&](const char* first,const char* other) {
        replay(*d,input,out);
        require(out.entries[0].portraitResource==first && out.entries[1].portraitResource==other &&
                out.entries[2].portraitResource==other && out.randomDraws.empty() && out.rngAfterEvents==input.rngBeforeEvents,
                "category7 city comparison or explicit no-RNG choice differs");
    };
    check("HHXENOC","HHXENOD"); // Enemy ahead, special IDs0x42/0x43 use3.
    input.citiesBeforeLoad={5,5,0,0,0,0,0}; check("HHXENOB","HHXENOB");
    input.citiesBeforeLoad[0]=6; check("HHXENOA","HHXENOA");
    input.citiesBeforeLoad={2,5,0,0,0,0,0}; d->players[0].relations[1]=0x10;
    check("HHXENOA","HHXENOA");
    d->options.allowAlliances=0; check("HHXENOC","HHXENOD");
    d->options.allowAlliances=1; d->players[0].relations[1]=0;
    d->players[1].relations[0]=0x10; check("HHXENOC","HHXENOD"); // Directed relation only.
    input.citiesBeforeLoad={1,0,0,0,0,0,9}; d->players[0].relations[6]=0x10;
    check("HHXENOC","HHXENOD"); // Slot6 outside numPlayers is not an ally.
    d->options.numPlayers=7; check("HHXENOA","HHXENOA"); // Type0 does not exclude its city counter.
    input.citiesBeforeLoad.fill(-1); check("HHXENOB","HHXENOB"); // Original maxima begin0.
    input.citiesBeforeLoad[0]=std::numeric_limits<int32_t>::max(); check("HHXENOA","HHXENOA");
    input.rngBeforeEvents={}; check("HHXENOA","HHXENOA"); // A non-random log needs no invented seed.

    d=fixture();
    const uint16_t types[]{34,1,88,4,54,59,61,68,69,50,51,123,91};
    for (const auto type:types) add(*d,type,{});
    replay(*d,context(),out);
    const std::array<std::vector<uint32_t>,6> pages{{{0},{1,11},{2,8,9,10},{3},{4,6,7},{5}}};
    require(out.pageIndices==pages && out.entries[12].category==7,"page-category grouping lost rows or included hidden category7");
}

void eventBoundariesAndRollback() {
    auto d=fixture(); auto input=context(); LoadedEventLog result;
    add(*d,1,std::vector<uint8_t>(1023,'a'));
    add(*d,1,std::vector<uint8_t>(1023,'b'));
    add(*d,1,std::vector<uint8_t>(1021,'c'));
    replay(*d,input,result); require(result.poolBytes==3070,"strict pool boundary should admit3070 bytes including terminators");
    d->events[2].text.push_back('c'); ++d->events[2].record.textLen;
    replay(*d,input,result);
    require(result.poolBytes==2047 && result.evictedEvents==1 && result.entries.size()==2 &&
        result.entries[0].text.front()=='b' && result.entries[1].text.front()=='c' &&
        result.entries[1].player==0 && result.entries[1].param==0 && result.randomDraws.size()==3,
        "pool eviction must preserve file-index payload displacement and consume each portrait once");
    // Priority30 sorts first and cannot be evicted by incoming priority20.
    d->events[0].record.type=6; rejectReplay(*d,input);
    d=fixture(); add(*d,1,{'v'}); add(*d,0,{'a',0,'b'}); rejectReplay(*d,input);
    // Lookup0042278c reads a 157th row in adjacent "No Building" text. Its
    // accidental id0x646c would use category28265/portrait28488 as table indices.
    // This known unsafe original domain must not be normalized into row0.
    d=fixture(); add(*d,1,{}); add(*d,0x646c,{}); rejectReplay(*d,input);
    d=fixture(); add(*d,1,{}); d->players[0].race=-1; rejectReplay(*d,input);
    d->players[0].race=7; rejectReplay(*d,input);
    d->players[0].race=2;
    auto invalid=input; ++invalid.rngBeforeEvents.format; rejectReplay(*d,invalid);
    invalid=input; invalid.rngBeforeEvents.counters.operations=1; rejectReplay(*d,invalid);
    invalid=input; invalid.rngBeforeEvents={}; rejectReplay(*d,invalid);
    invalid=input;
    invalid.rngBeforeEvents.counters.operations=invalid.rngBeforeEvents.counters.secondary15=std::numeric_limits<uint64_t>::max();
    rejectReplay(*d,invalid);
    // Pre-current logs are discarded before text/portrait processing, including
    // NUL/oversized-pool text that the archival codec supports.
    d=fixture(); add(*d,1,std::vector<uint8_t>(1023,0)); add(*d,1,std::vector<uint8_t>(1023,'b'));
    add(*d,1,std::vector<uint8_t>(1023,'c')); add(*d,1,std::vector<uint8_t>(1023,'d'));
    for (uint32_t version:{35u,36u,37u,0x11fu}) {
        d->header.version=version; replay(*d,input,result);
        require(result.entries.empty() && result.randomDraws.empty() && !result.poolBytes && result.firstVisible==37 &&
                result.rngAfterEvents==input.rngBeforeEvents,"old logs must discard bytes without RNG or portrait selection");
        for (const auto& page:result.pageIndices) require(page.empty(),"discarded event left a native page index");
    }
    d=fixture(); add(*d,0,{}); d->players[0].race=-1;
    EventLoadContext empty; replay(*d,empty,result);
    require(result.entries.size()==1 && result.entries[0].portraitResource.empty() && !result.rngAfterEvents.initialized,
            "no-portrait event should not require a race table or RNG seed");
    d=fixture(); d->header.isMap=1; d->mapTerritories.resize(1); rejectReplay(*d,input);
}

void evictionSortOracles() {
    auto d=fixture();
    // Four equal-priority entries sort [B,D,C,A] in Borland's qsort.
    // Neither stable sorting nor oldest-first reproduces that permutation.
    for (int i=0;i<4;++i) add(*d,1,std::vector<uint8_t>(700,uint8_t('A'+i)),10+i,20+i);
    add(*d,1,std::vector<uint8_t>(400,'E'),14,24);
    LoadedEventLog result; replay(*d,context(),result);
    require(result.evictedEvents==1 && result.poolBytes==2504 && result.entries.size()==4,
        "four-entry eviction pool accounting differs");
    require(result.entries[0].text.front()=='D' && result.entries[1].text.front()=='C' &&
        result.entries[2].text.front()=='A' && result.entries[3].text.front()=='E',
        "equal-priority tie order must match literal Borland qsort");
    require(result.entries[0].player==13 && result.entries[1].player==12 &&
        result.entries[2].player==10 && result.entries[3].player==0,
        "eviction must move complete records and clear the tail, not repair payloads");
    require(result.randomDraws.size()==5 && result.pageIndices[1]==std::vector<uint32_t>({0,1,2,3}),
        "eviction cannot repeat RNG or retain stale page indices");
    // Three equal entries sort [B,A,C].
    d=fixture(); for (int i=0;i<3;++i) add(*d,1,std::vector<uint8_t>(900,uint8_t('A'+i)),i,0);
    add(*d,1,std::vector<uint8_t>(1023,'D'),3,0);
    replay(*d,context(),result);
    require(result.evictedEvents==1 && result.entries[0].text.front()=='A' &&
        result.entries[1].text.front()=='C' && result.entries[2].text.front()=='D',
        "three-entry tie permutation differs");
    // Mixed priorities exercise both partition recursion paths and repeated eviction.
    d=fixture();
    for (int i=0;i<49;++i) add(*d,uint16_t(i%2?1:6),std::vector<uint8_t>(60,uint8_t('A'+i%26)),i,0);
    add(*d,6,std::vector<uint8_t>(1023,'!'),49,0);
    replay(*d,context(),result);
    require(result.evictedEvents==16 && result.entries.size()==34 && result.poolBytes==3037,
        "repeated evictions have incorrect byte/count totals");
    require(result.randomDraws.size()==24 && result.entries.back().player==0,
        "eviction consumes no portrait RNG and file-index payload remains displaced");
}

void startupAndSaveRng() {
    auto d=fixture(); const auto before=bytes(*d);
    auto result=std::make_unique<LoadStartupReport>();
    auto input=context(1).rngBeforeEvents;
    save::Error error;
    require(planLoadStartup(*d,{input},*result,error),"explicit startup reset failed");
    require(result->discardedGameSeed==346 && result->discardedWorldSeed==130 &&
        result->discardedWorldRngSeed==10982 && result->rngBeforeEvents.rtlLow==2867233980u,
        "ResetVariables must consume its three original rand15 values in order");
    require(result->rngBeforeEvents.secondary==1 && result->rngBeforeEvents.rtlHigh==0 &&
        result->rngBeforeEvents.counters.operations==3 && result->rngBeforeEvents.counters.rand15==3,
        "reset must not reseed or consume the secondary stream");
    require(result->resetDraws[0].tag=="GameSeed" && result->resetDraws[0].ordinal==1 &&
        result->resetDraws[2].ordinal==3 && result->gameStarted && result->redrawRequested &&
        !result->gameAborted && !result->seaWindowOpen && result->actionLast==0x347 && result->effectLast==0x4af,
        "owned startup state/reset flags differ from original");
    for(const auto v:result->combatWarriors) require(v==0,"combat scratch not reset");
    for(const auto v:result->sessionScratch) require(v==0,"session scratch not reset");
    require(bytes(*d)==before,"startup seeds must not overwrite the loaded document");
    auto saved=std::make_unique<LoadStartupReport>(*result);
    require(!planLoadStartup(*d,{},*result,error) && *result==*saved,"missing startup RNG must roll back");
    auto exhausted=input;
    exhausted.counters.operations=exhausted.counters.rand15=UINT64_MAX-1;
    require(!planLoadStartup(*d,{exhausted},*result,error) && *result==*saved,
        "late reset draw failure must preserve all owned transient storage");
    require(planLoadStartup(*d,{result->rngBeforeEvents},*result,error),"startup snapshot/output alias rejected");
    require(result->rngBeforeEvents.counters.rand15==6,"aliased reset snapshot consumed wrong ordinal");
    SaveRngPlan savePlan;
    require(planOfflineSaveRng(input,savePlan,error) && savePlan.gameId==346 &&
        savePlan.operations[0].operation==RngOperation::TaggedRange && savePlan.operations[0].bound==10000 &&
        savePlan.operations[0].tag=="SaveGame" && savePlan.operations[1].operation==RngOperation::SeedBoth &&
        savePlan.after.rtlLow==346 && savePlan.after.rtlHigh==0 && savePlan.after.secondary==346 &&
        savePlan.after.counters.operations==2 && savePlan.after.counters.long31==1 && savePlan.after.counters.seedBoth==1,
        "offline save must draw lrand%10000 then reseed both streams");
    const auto savedPlan=savePlan;
    require(!planOfflineSaveRng(exhausted,savePlan,error) && savePlan==savedPlan,
        "failed save reseed must roll back after the candidate draw");
    require(!planOfflineSaveRng({},savePlan,error) && savePlan==savedPlan,"save must never invent a missing RNG seed");
    require(planOfflineSaveRng(savePlan.after,savePlan,error) && savePlan.operations[0].ordinal==3 &&
        savePlan.operations[1].ordinal==4 && bytes(*d)==before,"save planning must handle output snapshot alias and stay read-only");
}

void timersAndAliasing() {
    auto d=fixture(); d->players[0].turnDone=1; d->players[1].turnDone=1;
    const LoadTimerState prior{false,123,45};
    LoadTimerReport result; save::Error error;
    const auto plan=[&](const LoadTimerState& previous,uint32_t now) {
        error={save::ErrorCode::Io,19,"old"};
        require(planLoadTimer(*d,previous,now,result,error),"valid load timer rejected"); cleared(error);
        require(result.activePlayers==3 && result.finishedPlayers==2,"timer count oracle differs");
    };
    plan(prior,500); require(result.state==prior && !result.restarted,"disabled load timers changed previous state");
    d->options.lastPlayerTimer=1; d->options.lastPlayerClock=90;
    plan(prior,500); require(result.state==LoadTimerState{true,500,90} && result.restarted,"last-player timer did not start");
    plan(result.state,800); require(result.state==LoadTimerState{true,500,90} && !result.restarted,
            "running last-player timer restarted or previous/output aliasing failed");
    d->options.autoTimer=1; d->options.autoTimerClock=120;
    plan(result.state,0xfffffff0u);
    require(result.state==LoadTimerState{true,0xfffffff0u,120} && result.restarted,"auto timer must restart even an active timer");
    d->options.autoTimerClock=std::numeric_limits<int32_t>::min();
    plan(result.state,0); require(result.state.seconds==std::numeric_limits<int32_t>::min() && result.state.startedMs==0,
            "timer planner invented duration clamps or rejected clock wrap");
    d->options.autoTimer=0; d->players[6].type=255; d->players[6].turnDone=255;
    require(planLoadTimer(*d,prior,900,result,error),"all-seven finished-player count rejected");
    require(result.activePlayers==3 && result.finishedPlayers==3 && !result.restarted && result.state==prior,
            "finished count must include nonzero signed-byte sentinel types outside numPlayers");
    d->players[6].turnDone=0; d->players[2].type=0;
    require(planLoadTimer(*d,prior,900,result,error) && result.activePlayers==2 && result.finishedPlayers==2 && !result.restarted,
            "inactive slots or last-player equality were changed");
    d->players[0].type=d->players[1].type=0;
    require(planLoadTimer(*d,prior,900,result,error) && result.activePlayers==0 && result.finishedPlayers==0 && !result.restarted,
            "offline timer invented the editor's empty-player fallback");
    const auto before=result;
    d->options.localPlayer=7;
    require(!planLoadTimer(*d,result.state,55,result,error) && error.code!=save::ErrorCode::None && result==before,
            "invalid timer request overwrote an aliased previous state/report");
    d=fixture(); d->header.isMap=1; d->mapTerritories.resize(1);
    require(!planLoadTimer(*d,result.state,55,result,error) && error.code!=save::ErrorCode::None && result==before,
            "reduced map acquired a gameplay load timer");
}

void runtimeEvents() {
    auto d = fixture(); const auto original = bytes(*d);
    save::Error error; LoadedEventLog log; LocalEventReport result;
    auto ctx = context(1);
    require(logLocalEvent(*d, log, ctx, {64, {std::string("Housing Complex"), std::string("Eden")}, {}},
                          log, result, error), "construction event failed");
    cleared(error);
    const std::string construction = "Our colonists have started construction on the Housing Complex in Eden. It should be finished after a while.";
    require(result.stored && result.index == 0 && result.randomDraws.size() == 1 &&
            result.randomDraws[0].value == 16838 && log.entries[0].text == std::vector<uint8_t>(construction.begin(), construction.end()) &&
            log.entries[0].portraitResource == "HHEVENTD" && log.pageIndices[4] == std::vector<uint32_t>{0},
            "canonical construction event text/portrait/page mismatch");
    const auto firstPortrait = log.entries[0].portraitResource;
    ctx.rngBeforeEvents = result.rngAfter;
    require(logLocalEvent(*d, log, ctx, {153, {int32_t(-2147483647-1), int32_t(4)}, EventPayload{2,9}},
                          log, result, error), "numeric event failed");
    const std::string maintenance = "We have paid -2147483648 credits in maintenance costs for 4 troopers.";
    require(result.randomDraws.empty() && log.entries[0].portraitResource == firstPortrait &&
            log.entries[1].text == std::vector<uint8_t>(maintenance.begin(), maintenance.end()) &&
            log.entries[1].player == 2 && log.entries[1].param == 9 && result.rngAfter == ctx.rngBeforeEvents,
            "LogEventEx payload or integer formatting/no-portrait RNG mismatch");
    require(logLocalEvent(*d, log, ctx, {58, {int32_t(1), int32_t(10)}, {}}, log, result, error), "betrayal conversion failed");
    const std::string betrayal(log.entries.back().text.begin(), log.entries.back().text.end());
    require(betrayal.find(data::kRaceNames[1]) != std::string::npos &&
            betrayal.find("Technology and Military") != std::string::npos, "Event58 player/pact lookup mismatch");
    ctx.rngBeforeEvents = result.rngAfter;
    require(logLocalEvent(*d, log, ctx, {123, {std::string("ChCh't")}, EventPayload{0,17}}, log, result, error), "extended elimination failed");
    require(result.randomDraws.size() == 1 && log.entries.back().portraitResource.empty(),
            "same-race elimination override must clear portrait AFTER consuming its original random draw");
    const auto saved = log; const auto reportSaved = result;
    require(!logLocalEvent(*d, log, ctx, {64, {int32_t(1), std::string("x")}, {}}, log, result, error) &&
            log == saved && result == reportSaved, "format failure published state");
    require(!logLocalEvent(*d, log, ctx, {34, {std::string(1024, 'x')}, {}}, log, result, error) && log == saved,
            "text buffer overflow must fail atomically");
    auto exhausted = ctx; exhausted.rngBeforeEvents.counters.operations = UINT64_MAX;
    exhausted.rngBeforeEvents.counters.secondary15 = UINT64_MAX;
    require(!logLocalEvent(*d, log, exhausted, {64, {std::string("x"),std::string("y")}, {}}, log, result, error) &&
            log == saved && result == reportSaved, "late portrait failure published pool mutation");
    require(bytes(*d) == original, "local event logging mutated the source document");
    // Count limit: actual original maximum50, independent of text byte pool.
    d->events.clear(); d->options.eventCount = 0;
    for (int i = 0; i < 50; ++i) add(*d, 0, {uint8_t('A' + i % 26)});
    replay(*d, context(1), log); ctx = context(1);
    require(logLocalEvent(*d, log, ctx, {0, {}, {}}, log, result, error) && result.stored &&
            result.evictedEvents == 1 && log.entries.size() == 50 && log.entries.back().player == 0,
            "count-limit eviction differs from native logging");
    d->events.clear(); d->options.eventCount = 0;
    for (int i = 0; i < 50; ++i) add(*d, 34, {uint8_t('A' + i % 26)});
    replay(*d, context(1), log); const auto deniedBefore = log;
    require(logLocalEvent(*d, log, ctx, {0, {}, {}}, log, result, error) && !result.stored &&
            result.index == -1 && result.evictedEvents == 0 && result.rngAfter == ctx.rngBeforeEvents &&
            log.entries != deniedBefore.entries, "priority denial must retain the real sort and consume no RNG");
    // Saved payload words above active count survive LoadEventLog eviction and
    // are reused by ordinary LogEvent (Ex replaces them after the append).
    d->events.clear(); d->options.eventCount = 0;
    add(*d, 0, std::vector<uint8_t>(1023,'a'), 1,11);
    add(*d, 0, std::vector<uint8_t>(1023,'b'), 2,22);
    add(*d, 0, std::vector<uint8_t>(1022,'c'), 3,33);
    replay(*d, context(1), log);
    require(log.entries.size() == 2 && log.slotPayloads[2] == EventPayload{3,33}, "inactive loader payload was lost");
    require(logLocalEvent(*d, log, ctx, {0, {}, {}}, log, result, error) && log.entries.back().player == 3 &&
            log.entries.back().param == 33, "ordinary LogEvent must reuse inactive payload words");
}

// Read-only PE parser adapted from test_table_contracts; no native image loading.
class OriginalPe {
    std::vector<uint8_t> bytes_;
    uint32_t imageBase_=0; size_t sections_=0; uint16_t count_=0;
    uint8_t u8(size_t at) const { require(at<bytes_.size(),"truncated original PE"); return bytes_[at]; }
    uint16_t u16(size_t at) const { return uint16_t(u8(at)|uint16_t(u8(at+1))<<8); }
    uint32_t u32(size_t at) const {
        return uint32_t(u8(at))|uint32_t(u8(at+1))<<8|uint32_t(u8(at+2))<<16|uint32_t(u8(at+3))<<24;
    }
    size_t offset(uint32_t address) const {
        require(address>=imageBase_,"PE address below image base"); const auto rva=address-imageBase_;
        for (size_t i=0;i<count_;++i) {
            const auto section=sections_+40*i; const auto start=u32(section+12),size=u32(section+16);
            if (rva>=start && rva-start<size) {
                const auto result=size_t(u32(section+20))+size_t(rva-start);
                require(result<bytes_.size(),"PE raw offset outside file"); return result;
            }
        }
        throw std::runtime_error("portrait table is not backed by a PE section");
    }
public:
    explicit OriginalPe(const fs::path& path) {
        const auto size=fs::file_size(path); require(size>=64 && size<=16*1024*1024,"invalid original EXE size");
        bytes_.resize(size_t(size)); std::ifstream in(path,std::ios::binary);
        require(bool(in.read(reinterpret_cast<char*>(bytes_.data()),std::streamsize(bytes_.size()))),"cannot read original EXE");
        require(u16(0)==0x5a4d,"original EXE is not MZ"); const size_t pe=u32(0x3c);
        require(u32(pe)==0x4550 && u16(pe+24)==0x10b,"original EXE is not PE32");
        count_=u16(pe+6); imageBase_=u32(pe+24+28); sections_=pe+24+u16(pe+20);
        require(count_>0 && count_<100 && sections_<=bytes_.size() && size_t(count_)*40<=bytes_.size()-sections_,
                "invalid original PE section table");
    }
    uint32_t word(uint32_t address) const { return u32(offset(address)); }
    std::string text(uint32_t address) const {
        std::string result; size_t at=offset(address);
        while (u8(at)) { require(result.size()<1024,"unterminated original string"); result.push_back(char(u8(at++))); }
        return result;
    }
};
void portraitTables(const fs::path& directory) {
    constexpr int categories[]{1,2,3,4,5,6,7,8,12,13,21,24,25,26,27};
    constexpr size_t counts[]{5,5,5,5,5,5,4,12,3,3,3,2,6,1,1};
    size_t total=0;
    for (size_t i=0;i<std::size(categories);++i) for (int race=0;race<7;++race) {
        const auto names=data::eventPortraitNames(race,categories[i]);
        require(names.size()==counts[i],"verified portrait table extent differs"); total+=names.size();
        for (const auto name:names) require(!name.empty() && name.size()<16,"invalid portrait resource name");
    }
    require(total==455 && data::eventPortraitNames(-1,1).empty() && data::eventPortraitNames(7,1).empty() &&
            data::eventPortraitNames(0,-1).empty() && data::eventPortraitNames(0,9).empty(),"portrait-domain/count contract differs");
    const auto path=directory/"DEADLOCK.EXE";
    if (directory.empty() || !fs::is_regular_file(path)) {
        std::cout<<"load session: optional original PE unavailable; portrait extents checked\n"; return;
    }
    OriginalPe pe(path);
    for (int observer=0; observer<7; ++observer) for (int defeated=0; defeated<7; ++defeated) {
        const auto pointer=pe.word(0x004cac00u+uint32_t(observer*7+defeated)*4);
        require(data::eliminationPortrait(observer,defeated)==(pointer?pe.text(pointer):std::string{}),
                "elimination portrait table differs from original PE");
    }
    require((pe.word(0x004fd40a)&0xffffu)==0x646cu &&
            pe.text(0x004fd404)=="No Building","original phantom event row evidence changed");
    for (const auto category:categories) for (int race=0;race<7;++race) {
        const uint32_t row=0x004ca3b0u+uint32_t(category)*0x38u+uint32_t(race)*8u;
        const auto names=data::eventPortraitNames(race,category);
        require(pe.word(row+4)==names.size(),"portrait list count differs from original PE");
        const auto list=pe.word(row);
        for (size_t i=0;i<names.size();++i)
            require(pe.text(pe.word(list+uint32_t(i)*4u))==names[i],"portrait resource string/order differs from original PE");
    }
    std::cout<<"load session: all455 portrait names match original PE tables\n";
}

std::vector<std::string> scenarioNames(const fs::path& path) {
    const auto size=fs::file_size(path); require(size>=4 && size<=save::kMaxFileBytes,"invalid corpus index size");
    std::ifstream in(path,std::ios::binary); uint8_t raw[4]{};
    require(bool(in.read(reinterpret_cast<char*>(raw),4)),"cannot read corpus index");
    const uint32_t n=uint32_t(raw[0])|(uint32_t(raw[1])<<8)|(uint32_t(raw[2])<<16)|(uint32_t(raw[3])<<24);
    require(n<=(size-4)/12,"truncated corpus index"); std::vector<std::string> names;
    for (uint32_t i=0;i<n;++i) { char e[12]{}; require(bool(in.read(e,12)),"cannot read corpus entry"); names.emplace_back(e,std::find(e,e+8,'\0')); }
    return names;
}
void corpusOne(const Document& d) {
    const auto before=bytes(d); auto input=context(0xabcdef01); LoadedEventLog first,second;
    replay(d,input,first); replay(d,input,second);
    require(first==second && bytes(d)==before,"corpus event replay is nondeterministic or changed source");
    if (d.header.version!=kSaveVersion)
        require(first.entries.empty() && first.randomDraws.empty() && first.rngAfterEvents==input.rngBeforeEvents,
                "old corpus log unexpectedly replayed events/RNG");
    else {
        require(first.entries.size()==d.events.size(),"current corpus events disappeared");
        for (size_t i=0;i<first.entries.size();++i)
            require(first.entries[i].text==d.events[i].text && first.entries[i].type==d.events[i].record.type &&
                    first.entries[i].player==d.events[i].record.player && first.entries[i].param==d.events[i].record.param,
                    "current corpus event bytes or metadata changed");
    }
    LoadTimerReport timer; save::Error error;
    require(planLoadTimer(d,{false,42,99},123456789,timer,error),"corpus timer planning failed");
    int active=0,finished=0;
    for (int p=0;p<d.options.numPlayers;++p) active+=d.players[size_t(p)].type!=0;
    for (const auto& p:d.players) finished+=p.type!=0 && p.turnDone!=0;
    require(timer.activePlayers==active && timer.finishedPlayers==finished && bytes(d)==before,
            "corpus timer reader changed source or count domains");
}
void optionalCorpus(const fs::path& directory) {
    if (directory.empty() || !fs::is_regular_file(directory/"TUTORIAL.SAV")) {
        std::cout<<"load session: optional corpus unavailable; synthetic tests ran\n"; return;
    }
    size_t count=0;
    for (const char* name:{"TUTORIAL.SAV","Saves/AUTOSAVE.SAV","Campaign/AUTOSAVE.CPN","Campaign/ChCht001.CPN"}) {
        if (!fs::is_regular_file(directory/name)) continue;
        auto d=std::make_unique<Document>(); save::Error error;
        if (!save::readDocument(directory/name,*d,error)) throw std::runtime_error(error.message);
        try { corpusOne(*d); } catch (const std::exception& ex) { throw std::runtime_error(std::string(name)+": "+ex.what()); }
        ++count;
    }
    if (fs::is_regular_file(directory/"LEVELS.HDX") && fs::is_regular_file(directory/"LEVELS.HDD"))
        for (const auto& name:scenarioNames(directory/"LEVELS.HDX")) {
            auto d=std::make_unique<Document>(); save::Error error;
            if (!save::readScenario(directory/"LEVELS",name,*d,error)) throw std::runtime_error(error.message);
            try { corpusOne(*d); } catch (const std::exception& ex) { throw std::runtime_error(name+": "+ex.what()); }
            ++count;
        }
    std::cout<<"load session corpus: "<<count<<" documents, source preserved\n";
}
} // namespace

int main(int argc,char** argv) {
    try {
        rtl::srand(0xf1234567u); (void)rtl::lrand(); gg.rng2Seed=0xabcd0123;
        const auto low=rtl::seed(),high=rtl::seedHi();
        const auto globals=std::make_unique<GameGlobals>(gg);
        const auto game=std::make_unique<GameState>(gs);
        goldenReplay(); cityComparisonAndPages(); eventBoundariesAndRollback(); evictionSortOracles();
        startupAndSaveRng(); timersAndAliasing(); runtimeEvents();
        const fs::path directory=argc>1?fs::path(argv[1]):fs::path{};
        portraitTables(directory); optionalCorpus(directory);
        require(rtl::seed()==low && rtl::seedHi()==high && std::memcmp(&gg,globals.get(),sizeof(gg))==0 &&
                std::memcmp(&gs,game.get(),sizeof(gs))==0,"load session changed global game or RNG state");
        std::cout<<"load session tests passed\n"; return 0;
    } catch (const std::exception& ex) { std::cerr<<"load session: "<<ex.what()<<'\n'; return 1; }
}
