// Independent paper oracles:0044b9e4/0044b924, logger00423690/004237d0,
// AI004047a0 and secondary LCG0046ca40. No execution of the original binary.
#include "game/shrine_consequences.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
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
std::unique_ptr<save::Document> fixture() {
    auto d=std::make_unique<save::Document>();
    std::memcpy(d->header.text,save::kHeaderText,sizeof(save::kHeaderText)); d->header.version=kSaveVersion;
    d->world.width=6; d->world.height=1; d->world.numTerritories=6;
    d->territories.resize(6); d->tiles.resize(6);
    d->options.numPlayers=2; d->options.localPlayer=0; d->options.turn=17;
    for (size_t p=0;p<7;++p) {
        d->players[p].index=uint8_t(p); d->players[p].race=2; d->players[p].type=p?0:1;
        d->ministerJobs[p].resize(1); d->ministerJobs[p][0].type=1;
        d->scores[p].score=int32_t(500+p); d->scores[p].unk_05=0xa7;
    }
    constexpr int8_t morale[]{100,19,20,-128,127,65};
    for (size_t i=0;i<6;++i) {
        auto& t=d->territories[i].data; t.index=uint16_t(i+1); t.owner=i==5?1:0;
        t.morale=morale[i]; t.population=500; t.terrain=1; t.numTiles=1; t.tiles[0].raw=uint32_t(i);
        std::memcpy(t.name,i?"Beta":"Alpha",i?5:6); t.flags=0x81234567u;
        d->tiles[i].x=uint8_t(i); d->tiles[i].territory=int16_t(i+1);
    }
    d->scores[0].nukesUsed=255; d->localList={0,0x80,0xff};
    return d;
}
std::vector<uint8_t> bytes(const save::Document& d) {
    std::vector<uint8_t> result; save::Error error; ok(save::encode(d,result,error),error);
    for (const auto& record:d.territories) {
        const auto* raw=reinterpret_cast<const uint8_t*>(&record.data);
        result.insert(result.end(),raw+kTerritorySavedBytes,raw+sizeof(Territory));
    }
    return result;
}
ConstructionOrderContext context(uint32_t seed=0) {
    ConstructionOrderContext c; SessionRng rng; save::Error error; ok(rng.initialize(seed,error),error);
    c.events.rngBeforeEvents=c.ai.rng=c.log.rngAfterEvents=rng.snapshot();
    c.events.citiesBeforeLoad={7,5,3,2,1,4,6}; c.researchCampaignFlags=0x12345678u;
    return c;
}
uint32_t secondary(uint32_t& state) {
    state=state*0x41c64e6du+0x3039u; return (state>>16)&0x7fffu;
}
std::string text(const LoadedEvent& e) { return std::string(e.text.begin(),e.text.end()); }
int32_t attitude(const Job& matrix,int player,int other) {
    int32_t value; std::memcpy(&value,reinterpret_cast<const uint8_t*>(&matrix)+size_t(player*7+other)*4,4); return value;
}
void setAttitude(Job& matrix,int player,int other,int32_t value) {
    std::memcpy(reinterpret_cast<uint8_t*>(&matrix)+size_t(player*7+other)*4,&value,4);
}
struct Outcome { std::unique_ptr<save::Document> document=fixture(); ShrineConsequencesReport report; };
Outcome run(const save::Document& source,const PendingShrineState& pending,const ConstructionOrderContext& c=context()) {
    const auto input=bytes(source); const auto queue=pending; const auto log=c.log; const auto ai=c.ai;
    const auto rng=c.events.rngBeforeEvents,citiesRng=c.log.rngAfterEvents;
    Outcome output; save::Error error{save::ErrorCode::Io,35,"old"};
    ok(processPendingShrineConsequences(source,pending,c,*output.document,output.report,error),error);
    require(error.code==save::ErrorCode::None && !error.offset && error.message.empty(),"success clears error");
    require(bytes(source)==input && pending==queue && c.log==log && c.ai==ai &&
        c.events.rngBeforeEvents==rng && c.log.rngAfterEvents==citiesRng,"inputs and explicit continuation are immutable");
    require(output.report.pendingAfter==pending && output.report.citiesAfter==c.events.citiesBeforeLoad,
        "processing must not drain/deduplicate queue or infer new city counts");
    auto alias=std::make_unique<save::Document>(source); ShrineConsequencesReport repeated;
    ok(processPendingShrineConsequences(*alias,pending,c,*alias,repeated,error),error);
    require(bytes(*alias)==bytes(*output.document) && repeated==output.report,"source/output alias is deterministic");
    return output;
}
void localPenaltyAndSignedness() {
    auto d=fixture(); auto c=context(); c.log.slotPayloads[0]={42,99};
    const PendingShrineState pending{{{0,1}}}; auto out=run(*d,pending,c);
    constexpr int8_t after[]{80,0,0,0,107,65};
    auto expected=std::make_unique<save::Document>(*d);
    for (size_t i=0;i<6;++i) expected->territories[i].data.morale=after[i];
    expected->scores[0].nukesUsed=0;
    require(bytes(*out.document)==bytes(*expected),"only same-index owner morale and byte-wrapped score counter may change");
    const auto& r=out.report;
    require(r.penalties.size()==1 && r.penalties[0].playerSlot==0 && r.penalties[0].playerIndex==0 &&
        r.penalties[0].territory==1 && r.penalties[0].nukesUsedBefore==255 && r.penalties[0].nukesUsedAfter==0 &&
        r.penalties[0].morale.size()==5,"signed morale and score audit report");
    require(r.events.size()==7 && r.events[0].type==80 && r.events[0].recipient==0 && r.events[0].local,
        "event80 is first, local to the offender");
    for (size_t i=1;i<7;++i)
        require(r.events[i].type==81 && r.events[i].recipient==int(i) && !r.events[i].local && !r.events[i].aiDispatched,
            "event81 visits all other slots, including inactive and beyond numPlayers");
    require(r.logAfter.entries.size()==1 && text(r.logAfter.entries[0])==
        "Our forces destroyed the shrine in Alpha! Several of our colonists have not taken this very well. Many wander the streets in absolute shock.",
        "original event80 canonical text");
    require(r.logAfter.entries[0].player==42 && r.logAfter.entries[0].param==99,
        "plain LogEvent80 retains inactive-slot payload, not a fabricated offender payload");
    uint32_t state=0; const auto draw=secondary(state);
    require(r.events[0].localReport.randomDraws.size()==1 && r.events[0].localReport.randomDraws[0].value==draw &&
        r.rngAfter.secondary==state && r.rngAfter.counters.secondary15==1 && r.rngAfter.rtlLow==0 &&
        r.rngAfter.rtlHigh==0 && r.aiAfter.rng==r.rngAfter,"one genuine portrait draw and shared stream");
}
void currentIndexAndDuplicates() {
    auto d=fixture(); d->players[2].index=1; d->players[2].race=5; d->players[2].type=255;
    d->territories[0].data.owner=1; d->scores[1].nukesUsed=254;
    const PendingShrineState pending{{{2,1},{2,1}}}; auto c=context(1); auto out=run(*d,pending,c);
    require(out.report.penalties.size()==2 && out.report.penalties[0].playerSlot==2 &&
        out.report.penalties[0].playerIndex==1 && out.document->territories[0].data.morale==60 &&
        out.document->territories[5].data.morale==25 && out.document->territories[1].data.morale==19 &&
        out.document->scores[1].nukesUsed==0 && out.document->scores[2].nukesUsed==0,
        "current signed Player.index, not physical pointer slot, controls repeated morale/score effects");
    require(out.report.events.size()==14 && out.report.events[0].recipient==1 && out.report.events[1].recipient==0 &&
        out.report.events[1].local && out.report.events[1].type==81 && out.report.events[2].recipient==2 &&
        !out.report.events[2].aiDispatched,"offender80 precedes ascending other-slot81 dispatch and signed type255 is not AI");
    require(text(out.report.logAfter.entries[0])==
        "The uncompromising Human have reduced the shrine in Alpha to rubble!  All knowledge contained within this shrine is lost forever." &&
        out.report.logAfter.entries[0].player==1 && out.report.logAfter.entries[0].param==0,
        "event81 uses race of resolved index1, not queued slot2, and real extended payload");
    require(out.report.rngAfter.counters.secondary15==2,"each duplicate emits its own portrait");
    auto next=c; next.log=out.report.logAfter; next.ai=out.report.aiAfter; next.events.rngBeforeEvents=out.report.rngAfter;
    auto again=run(*out.document,out.report.pendingAfter,next);
    require(again.document->territories[0].data.morale==20 && again.document->territories[5].data.morale==0 &&
        again.document->scores[1].nukesUsed==2 && again.report.rngAfter.counters.secondary15==4,
        "retained queue is deliberately processed again, not implicitly marked completed");
    // Pending source itself may be a member of the destination report.
    save::Error error; auto alias=std::make_unique<save::Document>(*out.document); auto report=out.report;
    ok(processPendingShrineConsequences(*alias,report.pendingAfter,next,*alias,report,error),error);
    require(bytes(*alias)==bytes(*again.document) && report==again.report,"report/pending alias remains safe until commit");
}
void aiDispatchAndContinuation() {
    auto d=fixture(); d->players[1].type=3; AiSession session; save::Error error;
    ok(session.initializeAfterLoad(*d,error),error); const auto installed=session.snapshot();
    auto c=context(); c.aiSession=&session; auto out=run(*d,{{{0,1}}},c);
    const auto& event=out.report.events[1];
    require(event.aiDispatched && event.aiReport.handled && event.aiReport.attitudes.size()==1 &&
        event.aiReport.attitudes[0].applied && attitude(out.document->scratchJob1,1,0)==-20 &&
        attitude(out.document->scratchJob2,1,0)==-10 && out.document->aiWarMask[1]==1,
        "event81 is actual hostility with correct extended offender and new war, not a no-op callback");
    uint32_t state=0; secondary(state); const auto warDraw=secondary(state);
    require(event.aiReport.draws.size()==1 && event.aiReport.draws[0].tag=="AiNewWarMessage00403408" &&
        event.aiReport.draws[0].value==warDraw && event.aiReport.draws[0].ordinal==2 &&
        out.report.rngAfter.secondary==state && out.report.rngAfter.counters.secondary15==2,
        "local portrait consumes first draw, AI war decision consumes second");
    require(out.report.aiAfter.pendingMessages.size()==size_t(!(warDraw&1u)) && session.snapshot()==installed,
        "actual message parity and immutable installed AI bindings");
    auto next=c; next.log=out.report.logAfter; next.ai=out.report.aiAfter; next.events.rngBeforeEvents=out.report.rngAfter;
    auto repeated=run(*out.document,{{{0,1}}},next);
    require(!repeated.report.events[1].aiReport.attitudes[0].applied &&
        attitude(repeated.document->scratchJob1,1,0)==-20 && repeated.report.aiAfter.pendingMessages.size()==size_t(!(warDraw&1u))+1 &&
        repeated.report.aiAfter.pendingMessages.back().category==32 && repeated.report.rngAfter.counters.secondary15==4,
        "continued relation-change mask blocks second penalty but existing-war chat still executes");
    // For offender1, its plain80 goes through AI's authentic default return,
    // while local81's extended word becomes1 rather than the territory ID.
    out=run(*d,{{{1,6}}},c);
    require(out.report.events[0].aiDispatched && !out.report.events[0].aiReport.handled &&
        out.report.events[0].aiReport.draws.empty() && out.report.events[1].local &&
        out.report.logAfter.entries[0].player==1 && out.report.rngAfter.counters.secondary15==1,
        "AI event80 default return is dispatched, not confused with event81 hostility");
}
void emptyCapacityAndLogRejection() {
    auto d=fixture(); auto c=context(); auto out=run(*d,{},c);
    require(bytes(*out.document)==bytes(*d) && out.report.events.empty() && out.report.penalties.empty() &&
        out.report.logAfter==c.log && out.report.aiAfter==c.ai && out.report.rngAfter==c.events.rngBeforeEvents,
        "explicit empty pending queue is a true no-op");
    PendingShrineState ten; ten.entries.assign(kPendingShrineCapacity,{0,1}); out=run(*d,ten,c);
    require(out.report.penalties.size()==10 && out.report.events.size()==70 && out.document->scores[0].nukesUsed==9 &&
        out.document->territories[0].data.morale==0 && out.report.rngAfter.counters.secondary15==10,
        "all ten native queue entries are accepted in order without deduplication");
    // Fifty higher-priority events block80. This is evaluated success, so the
    // subsequent moral/score effects still occur; the rejected log has no draw.
    c=context(); c.log.entries.resize(kMaxEvents); c.log.poolBytes=2*kMaxEvents;
    for (auto& event:c.log.entries) { event.type=134; event.category=2; event.text={'X'}; }
    out=run(*d,{{{0,1}}},c);
    require(!out.report.events[0].localReport.stored && out.report.logAfter.entries.size()==kMaxEvents &&
        out.report.rngAfter==c.events.rngBeforeEvents && out.document->scores[0].nukesUsed==0 &&
        out.document->territories[0].data.morale==80,"priority rejection is not phase failure or skipped penalty");
}
void failuresRollback() {
    auto source=fixture(); auto output=fixture(); output->options.turn=99;
    ShrineConsequencesReport report; report.penalties.push_back({}); report.citiesAfter[3]=884;
    const auto oldReport=report; const auto oldOutput=bytes(*output); save::Error error;
    const auto reject=[&](const PendingShrineState& pending,const ConstructionOrderContext& c) {
        const auto input=bytes(*source);
        require(!processPendingShrineConsequences(*source,pending,c,*output,report,error) &&
            report==oldReport && bytes(*output)==oldOutput && bytes(*source)==input && error.code!=save::ErrorCode::None,
            "unsafe shrine branch must preserve all input/output/report/RNG state");
    };
    auto c=context();
    for (const auto& entry:{PendingShrineEntry{-1,1},{7,1},{0,0},{0,7}}) reject({{entry}},c);
    PendingShrineState overflow; overflow.entries.assign(kPendingShrineCapacity+1,{0,1}); reject(overflow,c);
    require(error.code==save::ErrorCode::Limit,"queue overflow is explicit native storage limit");
    source->players[2].index=255; reject({{{0,1},{2,1}}},c);
    require(error.message.find("index")!=std::string::npos,"late second-entry signed-index failure rolls back first penalty");
    source=fixture(); source->players[0].race=7; reject({{{0,1}}},c);
    source=fixture(); std::memset(source->territories[0].data.name,'X',sizeof(Territory::name)); reject({{{0,1}}},c);
    source=fixture(); c.ai.rng=context(1).ai.rng; reject({{{0,1}}},c);
    require(error.message.find("shared")!=std::string::npos,"mismatched AI/event streams are not silently normalized");
    c=context(); c.ai.rng.format=c.events.rngBeforeEvents.format=99; reject({{{0,1}}},c);
    c=context(); source->players[1].type=3; reject({{{0,1}}},c);
    require(error.message.find("AI")!=std::string::npos,"missing AI binding rejects after local event without partial commit");
    AiSession ai; ok(ai.initializeAfterLoad(*source,error),error); c.aiSession=&ai;
    source->players[1].relations[0]=1; reject({{{0,1}}},c);
    require(error.message.find("pact-break")!=std::string::npos,"unported AI pact-break branch rolls back local log and attitude");
    source->players[1].relations[0]=0; source->aiWarMask[1]=2;
    // Choose an independent seed whose SECOND draw (after local portrait) has
    // low3bits0, thereby entering original existing-war dissolution dependency.
    uint32_t seed=0;
    for (;;++seed) { auto state=seed; secondary(state); if ((secondary(state)&7u)==0) break; }
    c=context(seed); c.aiSession=&ai; reject({{{0,1}}},c);
    require(error.message.find("task-force dissolution")!=std::string::npos,"unported dissolution is not replaced by successful partial shrine effect");
    // Clamp-before-hostility can decline a war using its actual preexisting
    // attitude; the unrelated old-war mask must not force a false dependency.
    setAttitude(source->scratchJob1,1,0,50); auto out=run(*source,{{{0,1}}},c);
    require(out.document->aiWarMask[1]==2 && attitude(out.document->scratchJob1,1,0)==30 &&
        out.report.events[1].aiReport.handled,"authentic war-decline branch is allowed despite old war");
}
}
int main() {
    try {
        std::vector<uint8_t> global(sizeof(gs)),runtime(sizeof(gg));
        std::memcpy(global.data(),&gs,sizeof(gs)); std::memcpy(runtime.data(),&gg,sizeof(gg));
        const auto seed=rtl::seed(),high=rtl::seedHi();
        localPenaltyAndSignedness(); currentIndexAndDuplicates(); aiDispatchAndContinuation();
        emptyCapacityAndLogRejection(); failuresRollback();
        require(!std::memcmp(global.data(),&gs,sizeof(gs)) && !std::memcmp(runtime.data(),&gg,sizeof(gg)) &&
            seed==rtl::seed() && high==rtl::seedHi(),"owned shrine effects leave all legacy globals and RNG untouched");
        std::cout<<"shrine_consequences: ordered real events/AI, signed morale, retained queue and atomic rollback passed\n";
        return 0;
    } catch (const std::exception& error) { std::cerr<<"shrine_consequences: "<<error.what()<<'\n'; return 1; }
}
