// Source-derived00441400 cursor and00406dd8 human-continuation invariants.
// These assertions are not observations from executing the original EXE.
#include "game/ai_pact_transaction.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include <array>
#include <cstring>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

namespace {
using namespace dl2;
using namespace dl2::simulation;
void require(bool value,const char* text) { if (!value) throw std::runtime_error(text); }
void word(Job& block,int p,int q,int32_t value) {
    std::memcpy(reinterpret_cast<uint8_t*>(&block)+size_t(p*7+q)*4,&value,4);
}
std::vector<uint8_t> bytes(const save::Document& d) {
    std::vector<uint8_t> result; save::Error error;
    if (!save::encode(d,result,error)) throw std::runtime_error(error.message); return result;
}
std::unique_ptr<save::Document> fixture(int count=3,uint32_t existing=6) {
    auto d=std::make_unique<save::Document>();
    std::memcpy(d->header.text,save::kHeaderText,sizeof(save::kHeaderText));
    d->header.version=kSaveVersion; d->header.minusOne=-1;
    d->options.numPlayers=count; d->options.localPlayer=1; d->options.turn=7; d->options.allowAlliances=1;
    d->world.width=d->world.height=1; d->world.numTerritories=1;
    d->tiles.resize(1); d->tiles[0].territory=1; d->territories.resize(1); d->territories[0].data.index=1;
    for (int p=0;p<7;++p) {
        d->players[size_t(p)].index=uint8_t(p); d->players[size_t(p)].race=int8_t(p);
        d->players[size_t(p)].type=p==1?1:p<count?3:0; d->ministerJobs[size_t(p)].resize(1);
        for (int q=0;q<7;++q) word(d->scratchJob1,p,q,-50);
        for (auto& job:d->jobs[size_t(p)]) { job.owner=int16_t(p); job.targetPlayer=-1; }
    }
    // Lower-index0 secretly broke local1's military pact. The local event must
    // be logged before callbacks2..6, whose offers each need a human answer.
    d->players[0].relations[1]=0; d->players[1].relations[0]=2;
    d->players[0].relations2[1]=d->players[1].relations2[0]=2;
    for (int p=2;p<count;++p) {
        word(d->scratchJob1,p,1,50);
        d->players[size_t(p)].relations[1]=d->players[1].relations[p]=existing;
        d->players[size_t(p)].relations2[1]=d->players[1].relations2[p]=existing;
    }
    d->trailing={0x78,0x56}; save::Error error;
    require(save::validate(*d,error),"invalid pact cursor fixture"); return d;
}
AiPactReconciliationContext context(uint32_t seed=0) {
    AiPactReconciliationContext result;
    result.ai.rng.initialized=true; result.ai.rng.rtlLow=seed; result.ai.rng.secondary=seed;
    result.ai.negotiation.emplace(); result.log.emplace();
    result.ai.pendingMessages.push_back({0,2,31,7,{8,9,10}}); return result;
}
void initialize(AiSession& ai,const save::Document& d) {
    save::Error error; require(ai.initializeAfterLoad(d,error),"pact cursor AI binding failed");
}
uint32_t step(uint32_t& seed) { seed=seed*0x41c64e6du+0x3039u; return (seed>>16)&0x7fffu; }
void draws(const AiPactReconciliationReport& report,uint32_t seed,size_t count) {
    require(report.draws.size()==count,"pact cursor duplicated/lost a logical draw");
    auto state=seed;
    for (size_t i=0;i<count;++i)
        require(report.draws[i].value==step(state) && report.draws[i].ordinal==i+1 && report.draws[i].consumed &&
                report.draws[i].operation==RngOperation::Secondary15,"pact cursor RNG differs from independent LCG");
    require(report.contextAfter.ai.rng.secondary==state && report.contextAfter.ai.rng.rtlLow==seed &&
            report.contextAfter.ai.rng.counters.secondary15==count && report.contextAfter.ai.rng.counters.operations==count,
            "pact cursor RNG checkpoint differs");
}
void begin(AiPactReconciliationTransaction& tx,const save::Document& d,const AiPactReconciliationContext& c,
           const std::optional<BuildingRemovalContext>& campaign=std::nullopt) {
    AiSession ai; initialize(ai,d); save::Error error;
    if (!tx.begin(d,ai,c,campaign,error)) throw std::runtime_error(error.message);
}
void localLogAndOrderedDeliveries() {
    auto d=fixture(4); auto out=fixture(); AiSession ai; initialize(ai,*d);
    auto c=context(); const auto source=bytes(*d); const auto input=c; save::Error error;
    AiPactReconciliationReport prior; prior.contextAfter=context(55);
    const auto keptReport=prior; const auto kept=bytes(*out);
    require(!reconcileAiPacts(*d,ai,c,*out,prior,error) && prior==keptReport && bytes(*out)==kept &&
            error.message.find("human response")!=std::string::npos,"old reconciliation invented a human answer or leaked effects");
    AiPactReconciliationTransaction tx;
    require(tx.status()==AiEventTransactionStatus::Empty && !tx.report() && !tx.pending(),"new pact transaction is not empty");
    require(tx.begin(*d,ai,c,std::nullopt,error) && tx.pending() && !tx.completedDocument(),"pact reconciliation did not pause");
    require(bytes(*d)==source && c==input,"begin mutated its borrowed document, log or live context");
    const auto first=*tx.pending(); const auto firstSnapshot=tx.snapshot();
    require(first.player==2 && first.recipient==1 && first.mask==8 && first.ordinal==1 && first.transactionId &&
            first.checkpoint==tx.report()->contextAfter.ai && tx.report()->pairs.size()==1 &&
            tx.report()->pairs[0].player==0 && tx.report()->pairs[0].other==0 &&
            firstSnapshot.phase==AiPactReconciliationPhase::ThirdParties && firstSnapshot.nextRecipient==3 &&
            firstSnapshot.currentPair && firstSnapshot.currentPair->before==std::array<uint32_t,4>{0,2,2,2} &&
            firstSnapshot.currentPair->changed==2,"pending cursor changed before/changed or advanced pair intersection");
    const auto& deliveries=tx.report()->deliveries;
    require(deliveries.size()==2 && deliveries[0].route==AiPactDeliveryRoute::LocalLog && deliveries[0].stored &&
            deliveries[0].eventType==0x3a && deliveries[1].recipient==2 && deliveries[1].eventType==0x73 &&
            deliveries[1].reaction && deliveries[1].reaction->offers.back().outcome==AiOfferOutcome::AwaitingHuman &&
            tx.report()->contextAfter.log->entries.size()==1 && tx.report()->contextAfter.log->entries[0].type==0x3a &&
            tx.report()->contextAfter.log->entries[0].player==0 && tx.report()->contextAfter.log->entries[0].param==2 &&
            tx.report()->draws[0].tag=="LogEventPortrait","local betrayal did not precede the partial AI reaction");
    draws(*tx.report(),0,4);
    require(!tx.begin(*d,ai,c,std::nullopt,error) && tx.snapshot()==firstSnapshot,"begin discarded pending reconciliation");
    auto forged=first; ++forged.mask;
    require(!tx.answer(forged,AiHumanAnswer::Accept,error) && tx.snapshot()==firstSnapshot,"forged pact answer changed the cursor");
    AiPactReconciliationTransaction foreign; begin(foreign,*d,c);
    require(!tx.answer(*foreign.pending(),AiHumanAnswer::Reject,error) && tx.snapshot()==firstSnapshot,
            "pact cursor accepted foreign transaction offer");
    auto branch=tx;
    require(branch.answer(first,AiHumanAnswer::Reject,error) && branch.pending() && tx.snapshot()==firstSnapshot,
            "copied pact transaction changed the original or failed to advance to next callback");
    const auto second=*branch.pending(); const auto secondSnapshot=branch.snapshot();
    require(second.player==3 && second.recipient==1 && second.ordinal==1 && second.transactionId!=first.transactionId &&
            branch.report()->deliveries.size()==3 && branch.report()->deliveries[1].reaction->offers[0].outcome==AiOfferOutcome::Rejected &&
            branch.report()->contextAfter.log==tx.report()->contextAfter.log &&
            branch.report()->pairs.size()==1 && second.checkpoint==branch.report()->contextAfter.ai,
            "next delivery reused identity, logged twice or retained the previous partial report");
    draws(*branch.report(),0,7);
    require(!branch.answer(first,AiHumanAnswer::Accept,error) && branch.snapshot()==secondSnapshot,
            "old delivery token answered a newer delivery");
    require(!branch.answer(second,static_cast<AiHumanAnswer>(77),error) && branch.snapshot()==secondSnapshot,
            "invalid explicit response enum changed reconciliation");
    // Inputs can be changed/destroyed independently while the branch awaits.
    d->options.turn=99; d->players[3].race=6; c.log.reset(); ai=AiSession{};
    require(branch.answer(second,AiHumanAnswer::Reject,error) && branch.completedDocument() && !branch.pending() &&
            branch.status()==AiEventTransactionStatus::Completed && branch.report()->pairs.size()==16 &&
            branch.completedDocument()->options.turn==7 && branch.completedDocument()->players[3].race==3 &&
            branch.report()->contextAfter.log->entries.size()==1 && branch.completedDocument()->events.empty(),
            "completion lost owned source/bindings or repeated archival/live log effects");
    draws(*branch.report(),0,7);
    for (int i=0;i<16;++i)
        require(branch.report()->pairs[size_t(i)].player==i/4 && branch.report()->pairs[size_t(i)].other==i%4,
                "resumed pair order is not row-major");
    const auto completed=branch.snapshot(); const auto document=bytes(*branch.completedDocument());
    require(!branch.answer(second,AiHumanAnswer::Accept,error) && branch.snapshot()==completed &&
            bytes(*branch.completedDocument())==document,"duplicate response changed completed reconciliation");
    require(source!=bytes(*d) && input!=c,"ownership fixture did not mutate its external inputs");
}
void reentrantPairUsesLiveWords() {
    auto d=fixture(); word(d->scratchJob1,0,1,50); word(d->scratchJob1,0,2,50);
    auto c=context(); c.ai.negotiation->lastOfferTurn[0][2]=7;
    AiPactReconciliationTransaction tx; begin(tx,*d,c); save::Error error;
    const auto first=*tx.pending();
    require(tx.answer(first,AiHumanAnswer::Accept,error) && tx.pending(),"accepted observer pact did not suspend recursive repair");
    const auto second=*tx.pending();
    require(second.transactionId==first.transactionId && second.ordinal==2 && second.player==0 && second.recipient==1 &&
            second.mask==12 && second.checkpoint.negotiation->offerState[2]==3 &&
            tx.snapshot().currentPair->changed==2 && tx.snapshot().currentPair->before==std::array<uint32_t,4>{0,2,2,2} &&
            tx.report()->pairs.size()==1,"recursive repair lost original pair checkpoint or nested identity");
    draws(*tx.report(),0,8);
    require(tx.answer(second,AiHumanAnswer::Accept,error) && tx.completedDocument(),"recursive pair repair did not complete");
    require(tx.report()->pairs[1].changed==2 && tx.report()->pairs[1].before==std::array<uint32_t,4>{0,2,2,2} &&
            tx.report()->pairs[1].after==std::array<uint32_t,4>{12,12,12,12} &&
            tx.completedDocument()->players[0].relations[1]==12 && tx.completedDocument()->players[1].relations2[0]==12 &&
            tx.report()->contextAfter.log->entries.size()==1,"intersection used pre-callback words or overwrote live repairs");
    draws(*tx.report(),0,9);
}
void campaignAndLateFailures() {
    auto d=fixture(3,13); d->options.campaign=1;
    auto c=context(); AiPactReconciliationTransaction missing; begin(missing,*d,c); save::Error error;
    const auto offer=*missing.pending(); const auto before=missing.snapshot();
    require(offer.mask==2 && !missing.answer(offer,AiHumanAnswer::Accept,error) && missing.snapshot()==before &&
            !missing.completedDocument(),"late missing campaign state leaked partial reconciliation");
    require(missing.answer(offer,AiHumanAnswer::Reject,error) && missing.completedDocument() &&
            missing.report()->contextAfter.log->entries.size()==1,"failed acceptance prevented real refusal or repeated log");
    BuildingRemovalContext campaign; campaign.campaignFlags=2; campaign.campaignProgress={99999,-12345,654321};
    campaign.pendingShrines.entries={{1,1},{1,1}};
    AiPactReconciliationTransaction accepted; begin(accepted,*d,c,campaign); const auto choice=*accepted.pending();
    require(choice.campaignCheckpoint==campaign && accepted.answer(choice,AiHumanAnswer::Accept,error) && accepted.completedDocument(),
            "explicit campaign pact acceptance failed in reconciliation");
    auto expected=campaign; expected.campaignProgress[0]=1;
    require(accepted.campaignAfter() && *accepted.campaignAfter()==expected &&
            accepted.completedDocument()->players[2].relations[1]==14 && accepted.report()->contextAfter.log->entries.size()==1,
            "reconciliation lost exact campaign state/duplicate shrine queue or accepted pact");
    // A later callback can fail after this human response and earlier log.
    // The original pending token and all its effects remain retryable.
    d=fixture(4); d->players[3].type=0; AiSession ai; initialize(ai,*d); d->players[3].type=3;
    AiPactReconciliationTransaction late;
    require(late.begin(*d,ai,context(),std::nullopt,error) && late.pending(),"late-failure fixture did not pause");
    const auto pending=*late.pending(); const auto snapshot=late.snapshot();
    require(!late.answer(pending,AiHumanAnswer::Reject,error) && late.snapshot()==snapshot && !late.completedDocument(),
            "unbound later recipient published partial response/log/RNG/cursor");
}
void noHumanParityAndFailedBegin() {
    auto out=fixture(); save::Error error;
    for (uint32_t seed=0;seed<8;++seed) {
        auto d=fixture(); for (int p=0;p<7;++p) for (int q=0;q<7;++q) word(d->scratchJob1,p,q,-50);
        if (seed==2) d->options.allowAlliances=0;
        if (seed==3) d->players[0].type=0;
        if (seed==4) { // Earlier inverse row suppresses higher-index breakup.
            d->players[0].relations[1]=2; d->players[1].relations[0]=0;
        }
        AiSession ai; initialize(ai,*d); auto c=context(seed); AiPactReconciliationReport expected;
        require(reconcileAiPacts(*d,ai,c,*out,expected,error),"legacy parity reconciliation failed");
        AiPactReconciliationTransaction tx;
        require(tx.begin(*d,ai,c,std::nullopt,error) && tx.completedDocument() && *tx.report()==expected &&
                bytes(*tx.completedDocument())==bytes(*out),"cursor changed existing no-human reconciliation behavior");
        const auto before=tx.snapshot(); const auto output=bytes(*tx.completedDocument());
        c.ai.rng.initialized=false;
        require(!tx.begin(*d,ai,c,std::nullopt,error) && tx.snapshot()==before && bytes(*tx.completedDocument())==output,
                "failed new begin discarded last completed reconciliation");
    }
    auto d=fixture(); AiSession ai; initialize(ai,*d); auto c=context(); c.log.reset();
    AiPactReconciliationTransaction tx;
    require(!tx.begin(*d,ai,c,std::nullopt,error) && tx.status()==AiEventTransactionStatus::Empty && !tx.report(),
            "missing required existing local log fabricated continuation");
}
}
int main() {
    try {
        rtl::srand(0xdead4321); (void)rtl::lrand(); gg.rng2Seed=0x1379abcd;
        const auto low=rtl::seed(),high=rtl::seedHi();
        const auto globals=std::make_unique<GameGlobals>(gg); const auto game=std::make_unique<GameState>(gs);
        localLogAndOrderedDeliveries(); reentrantPairUsesLiveWords(); campaignAndLateFailures(); noHumanParityAndFailedBegin();
        require(rtl::seed()==low && rtl::seedHi()==high && std::memcmp(&gg,globals.get(),sizeof(gg))==0 &&
                std::memcmp(&gs,game.get(),sizeof(gs))==0,"reconciliation transaction touched global state or RNG");
        std::cout<<"AI pact transaction tests passed\n"; return 0;
    } catch (const std::exception& e) { std::cerr<<"AI pact transaction: "<<e.what()<<'\n'; return 1; }
}
