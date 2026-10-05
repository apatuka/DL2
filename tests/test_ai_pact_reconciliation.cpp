// Assembly-derived00441400 invariants; not an executed original-game oracle.
#include "game/ai_pact_reconciliation.h"
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
void require(bool value,const char* message) { if (!value) throw std::runtime_error(message); }
std::unique_ptr<save::Document> fixture(int local=2) {
    auto d=std::make_unique<save::Document>();
    std::memcpy(d->header.text,save::kHeaderText,sizeof(save::kHeaderText));
    d->header.version=kSaveVersion; d->header.minusOne=-1;
    d->options.numPlayers=3; d->options.localPlayer=local; d->options.allowAlliances=1; d->options.turn=7;
    d->world.width=d->world.height=1; d->world.numTerritories=1;
    d->tiles.resize(1); d->tiles[0].territory=1;
    d->territories.resize(1); d->territories[0].data.index=1;
    for (int p=0;p<kMaxPlayers;++p) {
        d->players[size_t(p)].index=uint8_t(p); d->players[size_t(p)].race=int8_t(p);
        d->players[size_t(p)].type=p==local?1:p<3?3:0;
        d->ministerJobs[size_t(p)].resize(1);
    }
    save::Error error; require(save::validate(*d,error),"invalid reconciliation fixture"); return d;
}
std::vector<uint8_t> bytes(const save::Document& d) {
    save::Error error; std::vector<uint8_t> result;
    if (!save::encode(d,result,error)) throw std::runtime_error(error.message);
    return result;
}
void word(Job& block,int p,int q,int32_t value) {
    std::memcpy(reinterpret_cast<uint8_t*>(&block)+size_t(p*7+q)*4,&value,4);
}
int32_t word(const Job& block,int p,int q) {
    int32_t value; std::memcpy(&value,reinterpret_cast<const uint8_t*>(&block)+size_t(p*7+q)*4,4); return value;
}
AiPactReconciliationContext context(uint32_t seed=0) {
    AiPactReconciliationContext c; SessionRng rng; save::Error error;
    require(rng.initialize(seed,error),"cannot initialize reconciliation RNG"); c.ai.rng=rng.snapshot(); return c;
}
void broken(save::Document& d,int p,int q,uint32_t mask) {
    d.players[size_t(p)].relations[q]=0;
    d.players[size_t(q)].relations[p]=mask;
    d.players[size_t(p)].relations2[q]=mask;
    d.players[size_t(q)].relations2[p]=mask;
}
void orderAndAiVictim() {
    auto d=fixture(); auto output=fixture(); AiSession ai; save::Error error;
    require(ai.initializeAfterLoad(*d,error),"AI initialization failed");
    auto c=context(); AiPactReconciliationReport r;
    // Lower-index reverse row intersects and copies both baselines first.
    // The original consequently never reports this higher-index secret break.
    broken(*d,1,0,2); const auto original=bytes(*d);
    require(reconcileAiPacts(*d,ai,c,*output,r,error),"reverse-order reconciliation failed");
    require(r.pairs.size()==9 && r.deliveries.empty() && r.draws.empty() && r.contextAfter==c &&
            output->players[0].relations[1]==0 && output->players[1].relations2[0]==0 &&
            bytes(*d)==original,"original reverse-order suppression changed");
    for (int i=0;i<9;++i)
        require(r.pairs[size_t(i)].player==i/3 && r.pairs[size_t(i)].other==i%3,"pair traversal is not row-major");
    d=fixture(); broken(*d,0,1,2); c.ai.relationChangeMask[1]=0x80000000u;
    d->options.allowAlliances=0; // No guard in00441400.
    require(reconcileAiPacts(*d,ai,c,*output,r,error) && r.deliveries.size()==1 && r.draws.empty(),
            "alliances-disabled raw reconciliation was skipped");
    const auto& delivery=r.deliveries[0];
    require(delivery.recipient==1 && delivery.eventType==0x3a && delivery.player==0 && delivery.changed==2 &&
            delivery.route==AiPactDeliveryRoute::AiReaction && delivery.reaction &&
            word(output->scratchJob1,1,0)==-40 && word(output->scratchJob2,1,0)==-20 &&
            r.contextAfter.ai.relationChangeMask[1]==0x80000001u &&
            output->players[0].relations[1]==0 && output->players[1].relations2[0]==0,
            "victim extended payload, doubled penalty, or preserved mask differs");
    // Full32-bit XOR reaches AI; only defined treaty penalty bits are used.
    d=fixture(); broken(*d,0,1,0x80000002u); c=context();
    require(reconcileAiPacts(*d,ai,c,*output,r,error) && r.deliveries[0].changed==0x80000002u &&
            word(output->scratchJob1,1,0)==-40,"AI betrayal truncated the changed word");
}
void localAndAtomicity() {
    auto d=fixture(); auto output=fixture(); AiSession ai; save::Error error;
    require(ai.initializeAfterLoad(*d,error),"local fixture AI initialization failed");
    broken(*d,0,2,2); d->aiWarMask[1]=5; // Observer1 cannot negotiate either party.
    auto c=context(); c.log.emplace(); const auto original=bytes(*d);
    AiPactReconciliationReport r;
    error={save::ErrorCode::Io,99,"old"};
    require(reconcileAiPacts(*d,ai,c,*output,r,error) && error.code==save::ErrorCode::None,
            "local betrayal reconciliation failed");
    require(r.deliveries.size()==2 && r.deliveries[0].route==AiPactDeliveryRoute::LocalLog &&
            r.deliveries[0].stored && r.deliveries[1].recipient==1 && r.deliveries[1].eventType==0x73 &&
            r.deliveries[1].reaction && r.draws.size()==2 &&
            r.draws[0].tag=="LogEventPortrait" && r.draws[1].tag=="AiPactEventGate004047a0",
            "local log must precede third-party callback and RNG");
    const auto& log=*r.contextAfter.log;
    require(log.entries.size()==1 && log.entries[0].type==0x3a && log.entries[0].player==0 &&
            log.entries[0].param==2 && !log.entries[0].portraitResource.empty() &&
            std::string(log.entries[0].text.begin(),log.entries[0].text.end()).find("secretly ended the Military")!=std::string::npos &&
            log.rngAfterEvents.counters.secondary15==1 && r.contextAfter.ai.rng.counters.secondary15==2 &&
            output->events.empty() && bytes(*d)==original,"live event log/payload or archival event separation differs");
    const auto kept=r; const auto outputBytes=bytes(*output);
    c.log.reset();
    require(!reconcileAiPacts(*d,ai,c,*output,r,error) && r==kept && bytes(*output)==outputBytes && bytes(*d)==original,
            "missing existing log changed output or report");
    c.log.emplace(); broken(*d,0,2,0x80000002u);
    require(!reconcileAiPacts(*d,ai,c,*output,r,error) && r==kept && bytes(*output)==outputBytes,
            "invalid native local mask name lookup fabricated an event");
    // A valid log is produced privately before the late observer reaches a
    // human offer. Nothing may leak when that capability is unavailable.
    d=fixture(); broken(*d,0,2,1);
    for (int p=0;p<3;++p) for (int q=0;q<3;++q) word(d->scratchJob1,p,q,50);
    c=context(); c.log.emplace(); c.ai.negotiation.emplace();
    const auto beforeFailure=bytes(*d);
    require(!reconcileAiPacts(*d,ai,c,*output,r,error) && error.message.find("human response")!=std::string::npos &&
            r==kept && bytes(*output)==outputBytes && bytes(*d)==beforeFailure,
            "late human offer did not roll back local log, RNG, or matrix edits");
    require(!reconcileAiPacts(*d,ai,c,*d,r,error) && bytes(*d)==beforeFailure && r==kept,
            "late human offer broke aliased transaction");
}
void inactiveAndSevenSlotCallbacks() {
    auto d=fixture(); auto output=fixture(); AiSession ai; save::Error error;
    require(ai.initializeAfterLoad(*d,error),"inactive fixture initialization failed");
    broken(*d,0,2,31); d->players[2].type=0;
    const auto c=context(); AiPactReconciliationReport r;
    require(reconcileAiPacts(*d,ai,c,*output,r,error) && r.deliveries.empty() && r.draws.empty() &&
            r.pairs[2].clearedInactive && r.pairs[2].changed==0 &&
            r.pairs[2].after==std::array<uint32_t,4>{},"inactive pair emitted effects before clearing");
    d=fixture(); broken(*d,0,1,2); d->players[6].type=3; d->aiWarMask[6]=3;
    require(ai.initializeAfterLoad(*d,error),"outside-count AI binding initialization failed");
    require(reconcileAiPacts(*d,ai,c,*output,r,error) && r.deliveries.size()==2 &&
            r.deliveries[0].recipient==1 && r.deliveries[1].recipient==6 && r.draws.size()==1 &&
            r.pairs.size()==9,"third-party scan incorrectly stopped at numPlayers");
    d->players[6].type=255;
    require(reconcileAiPacts(*d,ai,c,*output,r,error) && r.deliveries.size()==1 && r.draws.empty(),
            "signed-negative player received AI callback");
    d=fixture(); broken(*d,0,0,2); d->players[0].relations[0]=0; d->aiWarMask[1]=1;
    require(ai.initializeAfterLoad(*d,error) && reconcileAiPacts(*d,ai,c,*output,r,error) &&
            r.pairs[0].changed==2 && r.deliveries[0].recipient==0 &&
            word(output->scratchJob1,0,0)==-40 && output->players[0].relations2[0]==0,
            "diagonal aliases or callback payload differ");
}
void reentrantLivePairAndAliases() {
    // Find a deterministic source-derived witness of a callback restoring the
    // currently visited pair. This specifically detects stale pre-callback
    // matrix snapshots being intersected or written after nested negotiations.
    bool witnessed=false;
    for (uint32_t seed=0;seed<64 && !witnessed;++seed) {
        auto d=fixture(6); auto output=fixture(6); AiSession ai; save::Error error;
        broken(*d,0,1,1);
        for (int p=0;p<3;++p) for (int q=0;q<3;++q) word(d->scratchJob1,p,q,50);
        require(ai.initializeAfterLoad(*d,error),"reentrant fixture initialization failed");
        auto c=context(seed); c.ai.negotiation.emplace();
        AiPactReconciliationReport r;
        if (!reconcileAiPacts(*d,ai,c,*output,r,error)) throw std::runtime_error(error.message);
        if (!r.pairs[1].after[0]) continue;
        witnessed=true;
        require(r.pairs[1].before[0]==0 && r.pairs[1].changed==1 &&
                r.pairs[1].after[0]==r.pairs[1].after[1] && r.pairs[1].after[0]==r.pairs[1].after[2] &&
                r.pairs[1].after[0]==r.pairs[1].after[3],"callback edit lost before live intersection");
        auto alias=std::make_unique<save::Document>(*d); AiPactReconciliationReport aliasReport;
        aliasReport.contextAfter=c;
        require(reconcileAiPacts(*alias,ai,aliasReport.contextAfter,*alias,aliasReport,error) &&
                aliasReport==r && bytes(*alias)==bytes(*output),"document/context/report alias changed reconciliation");
    }
    require(witnessed,"no reentrant live-pair witness within the specified64 seeds");
}
} // namespace
int main() {
    try {
        rtl::srand(0xf1234567u); (void)rtl::lrand(); gg.rng2Seed=0xabcd0123;
        const auto low=rtl::seed(),high=rtl::seedHi();
        const auto globals=std::make_unique<GameGlobals>(gg); const auto game=std::make_unique<GameState>(gs);
        orderAndAiVictim(); localAndAtomicity(); inactiveAndSevenSlotCallbacks(); reentrantLivePairAndAliases();
        require(rtl::seed()==low && rtl::seedHi()==high && std::memcmp(&gg,globals.get(),sizeof(gg))==0 &&
                std::memcmp(&gs,game.get(),sizeof(gs))==0,"reconciliation touched global state/RNG");
        std::cout<<"AI pact reconciliation tests passed\n"; return 0;
    } catch (const std::exception& exception) {
        std::cerr<<"AI pact reconciliation: "<<exception.what()<<'\n'; return 1;
    }
}
