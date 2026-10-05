// CX-02 integrated offline pact effects. The RNG oracle below is independent
// of SessionRng; these are export/assembly-derived expectations, not runs of EXE.
#include "game/ai_session.h"
#include "game/event_portraits.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include "game/save_document.h"
#include <array>
#include <bit>
#include <cstring>
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
void require(bool value,const char* message) { if (!value) throw std::runtime_error(message); }
void word(Job& block,int p,int other,int32_t value) {
    std::memcpy(reinterpret_cast<uint8_t*>(&block)+size_t(p*7+other)*4,&value,4);
}
int32_t word(const Job& block,int p,int other) {
    int32_t value; std::memcpy(&value,reinterpret_cast<const uint8_t*>(&block)+size_t(p*7+other)*4,4); return value;
}
std::vector<uint8_t> bytes(const Document& d) {
    std::vector<uint8_t> result; save::Error error;
    if (!save::encode(d,result,error)) throw std::runtime_error(error.message);
    return result;
}
std::unique_ptr<Document> fixture(int active=3) {
    auto d=std::make_unique<Document>();
    std::memcpy(d->header.text,save::kHeaderText,sizeof(save::kHeaderText));
    d->header.version=kSaveVersion; d->header.minusOne=-1;
    d->options.numPlayers=active; d->options.localPlayer=0; d->options.turn=7;
    d->options.allowAlliances=1;
    d->world.width=d->world.height=1; d->world.numTerritories=1;
    d->tiles.resize(1); d->tiles[0].territory=1;
    d->territories.resize(1); auto& t=d->territories[0].data;
    t.index=1; t.owner=1; t.terrain=1; t.numTiles=1;
    for (int p=0;p<kMaxPlayers;++p) {
        d->players[size_t(p)].index=uint8_t(p); d->players[size_t(p)].race=int8_t(p);
        d->players[size_t(p)].type=p==0?1:p<active?3:0;
        d->ministerJobs[size_t(p)].resize(1); d->ministerJobs[size_t(p)][0].type=1;
        for (auto& job:d->jobs[size_t(p)]) { job.owner=int16_t(p); job.targetPlayer=-1; }
        for (int other=0;other<kMaxPlayers;++other) word(d->scratchJob1,p,other,-50);
    }
    d->trailing={0xde,0,0xad};
    save::Error error; require(save::validate(*d,error),"invalid negotiation fixture"); return d;
}
uint32_t step(uint32_t& state) { state=state*0x41c64e6du+0x3039u; return (state>>16)&0x7fffu; }
template<class Predicate> uint32_t seedFor(Predicate predicate) {
    for (uint32_t seed=0;seed<100000;++seed) {
        auto state=seed; std::array<uint32_t,8> draws{};
        for (auto& value:draws) value=step(state);
        if (predicate(draws)) return seed;
    }
    throw std::runtime_error("independent LCG could not find test seed");
}
AiReactionContext context(uint32_t seed,bool negotiation=false) {
    AiReactionContext result;
    result.rng.initialized=true; result.rng.rtlLow=seed; result.rng.secondary=seed;
    if (negotiation) result.negotiation.emplace();
    return result;
}
void verifyDraws(const AiReactionReport& result,uint32_t seed,size_t count) {
    require(result.draws.size()==count,"unexpected number of integrated RNG draws");
    auto state=seed;
    for (size_t i=0;i<count;++i) {
        const auto& draw=result.draws[i];
        require(draw.value==step(state) && draw.ordinal==i+1 && draw.consumed &&
                draw.operation==RngOperation::Secondary15,"integrated draw differs from independent LCG sequence");
    }
    require(result.contextAfter.rng.secondary==state && result.contextAfter.rng.rtlLow==seed &&
            result.contextAfter.rng.rtlHigh==0 && result.contextAfter.rng.counters.operations==count &&
            result.contextAfter.rng.counters.secondary15==count,"integrated RNG state/counter differs");
}
void initialize(AiSession& ai,const Document& d) {
    save::Error error; require(ai.initializeAfterLoad(d,error),"negotiation AI initialization failed");
}
void run(AiSession& ai,const Document& source,const AiEventRequest& request,
         const AiReactionContext& input,Document& output,AiReactionReport& report) {
    save::Error error{save::ErrorCode::Io,77,"sentinel"};
    if (!ai.reactEvent(source,request,input,output,report,error)) throw std::runtime_error(error.message);
    require(error.code==save::ErrorCode::None,"successful reaction did not clear prior error");
}

void unilateralAndRejectedAck() {
    auto d=fixture(); auto out=fixture(); AiSession ai; initialize(ai,*d);
    constexpr uint32_t original=0x8123000eu;
    d->players[1].relations[2]=original; d->players[2].relations[1]=0x4567001fu;
    d->players[1].relations2[2]=0xfeed001fu; d->players[2].relations2[1]=0xbeef001fu;
    const auto input=context(1); const auto source=bytes(*d); AiReactionReport report;
    run(ai,*d,{1,10,2,0},input,*out,report);
    require(report.pacts==std::vector<AiPactEdit>{{1,2,AiPactAction::SecretBreak,original,14,true}} &&
            out->players[1].relations[2]==0x81230000u && out->players[2].relations[1]==0x4567001fu &&
            out->players[1].relations2[2]==0xfeed001fu && out->players[2].relations2[1]==0xbeef001fu,
            "secret break lost uint16 transport or changed reciprocal/snapshot relations");
    require(report.pactEvents.empty() && report.pactNotices.empty() && report.offers.empty() &&
            out->aiWarMask[1]==4 && bytes(*d)==source,"secret break fabricated notifications or changed source");
    verifyDraws(report,1,2);
    require(report.draws[0].tag=="AiBreakPactChoice004071b0" &&
            report.draws[1].tag=="AiNewWarMessage00403408","secret-break draw ordering differs");

    d->options.allowAlliances=0;
    run(ai,*d,{1,10,2,0},input,*out,report);
    require(report.pacts.size()==1 && !report.pacts[0].accepted && out->players[1].relations[2]==original &&
            out->aiWarMask[1]==4 && report.pactEvents.empty(),"native rejected ACK stopped war or cleared pact");
    verifyDraws(report,1,2);
    // Public rejected ACK follows the same native false-return contract.
    auto locked=input; locked.relationChangeMask[1]=4; word(d->scratchJob1,1,2,0);
    run(ai,*d,{1,10,2,0},locked,*out,report);
    require(report.pacts[0].action==AiPactAction::PublicBreak && !report.pacts[0].accepted &&
            out->players[2].relations[1]==0x4567001fu && out->aiWarMask[1]==4,
            "public rejected ACK applied downstream effects");
    verifyDraws(report,1,2);
}

void publicCallbacksAndNotice() {
    auto d=fixture(5); auto out=fixture(); AiSession ai; initialize(ai,*d);
    for (int p:{1,2}) {
        const int other=p==1?2:1; d->players[size_t(p)].relations[other]=14;
        d->players[size_t(p)].relations2[other]=14;
    }
    word(d->scratchJob1,1,2,0); word(d->scratchJob1,2,1,0);
    auto input=context(0); input.relationChangeMask[1]=4;
    AiReactionReport report; run(ai,*d,{1,10,2,0},input,*out,report);
    require(!out->players[1].relations[2] && !out->players[2].relations[1] &&
            !out->players[1].relations2[2] && !out->players[2].relations2[1],"public break did not clear four masks");
    require(report.pactEvents==std::vector<AiPactEvent>{{3,0x73,1,2},{4,0x73,1,2}} &&
            word(out->scratchJob1,2,1)==-36 && word(out->scratchJob2,2,1)==-18,
            "public break changed callback slots/arguments or final target penalty");
    verifyDraws(report,0,4);
    require(report.draws[1].tag=="AiPactEventGate004047a0" &&
            report.draws[2].tag=="AiPactEventGate004047a0" &&
            report.draws[3].tag=="AiNewWarMessage00403408","public callback RNG order differs");

    d=fixture(2); initialize(ai,*d); word(d->scratchJob1,1,0,0);
    d->players[1].relations[0]=d->players[0].relations[1]=2;
    d->players[1].relations2[0]=d->players[0].relations2[1]=2;
    input=context(0); input.relationChangeMask[1]=1;
    const auto source=bytes(*d); const auto unchanged=input;
    run(ai,*d,{1,10,0,0},input,*out,report);
    auto oracle=uint32_t(0); (void)step(oracle); const auto portrait=step(oracle)%5;
    require(report.pactNotices==std::vector<AiPactNotice>{{1,0,2,std::string(data::eventPortraitNames(1,20)[portrait])}} &&
            report.pactEvents.empty() && report.contextAfter.pendingMessages.size()<=1 &&
            bytes(*d)==source && input==unchanged,"human notice invented an event or lost owned input");
    verifyDraws(report,0,3);
    require(report.draws[1].tag=="AiBreakPactPortrait004503f4","human portrait did not consume middle draw");
    auto alias=std::make_unique<Document>(*d); AiReactionReport aliasReport; aliasReport.contextAfter=input;
    run(ai,*alias,{1,10,0,0},aliasReport.contextAfter,*alias,aliasReport);
    require(bytes(*alias)==bytes(*out) && aliasReport==report,"source/output or report-context alias changed result");

    const auto kept=bytes(*out); const auto saved=report; save::Error error;
    d->players[1].relations[0]=32;
    require(!ai.reactEvent(*d,{1,10,0,0},input,*out,report,error) && bytes(*out)==kept && report==saved,
            "invalid human pact-name index did not roll back earlier clear");
}

void event72AndLiveSwap() {
    auto d=fixture(); auto out=fixture(); AiSession ai; initialize(ai,*d);
    word(d->scratchJob1,1,2,-20); word(d->scratchJob1,1,0,0);
    d->players[1].relations[0]=0x80000000u; d->players[2].relations2[0]=0;
    auto input=context(0,true); input.negotiation->victory.cities[0]=2;
    input.negotiation->victory.cities[1]=1;
    AiReactionReport report; run(ai,*d,{1,0x72,2,0},input,*out,report);
    require(report.messages.size()==1 && report.messages[0].message==AiDiplomacyMessage{1,1,-1,9,{2,0,0}} &&
            report.messages[0].outcome==AiMessageOutcome::Queued && report.attitudes.empty() &&
            bytes(*out)==bytes(*d),"event72 did not use signed raw masks, live metric, or command9 payload");
    verifyDraws(report,0,1);
    // The first direction changes -19 to -23, so the swapped handler MUST
    // now enter its hostile branch and edit the other column as well.
    word(d->scratchJob1,1,0,-19); input.negotiation.reset();
    run(ai,*d,{1,0x72,2,0},input,*out,report);
    require(report.attitudes.size()==2 && report.attitudes[0].other==0 && report.attitudes[1].other==2 &&
            word(out->scratchJob1,1,0)==-23 && word(out->scratchJob1,1,2)==-24 &&
            report.messages.empty(),"event72 swapped direction did not observe first direction's attitude");
    verifyDraws(report,0,1);
}

std::unique_ptr<Document> oneTechnologyOffer() {
    auto d=fixture(); word(d->scratchJob1,1,2,50); word(d->scratchJob1,2,1,50);
    // Original snapshot has military+intelligence. Only missing technology is
    // assessed; live masks0 prevent the later victory proposal prerequisite.
    d->players[1].relations2[2]=d->players[2].relations2[1]=6;
    return d;
}
void cooldownBusyAndAccepted() {
    auto d=oneTechnologyOffer(); auto out=fixture(); AiSession ai; initialize(ai,*d);
    auto input=context(0,true); input.negotiation->lastOfferTurn[1][2]=3;
    AiReactionReport report; run(ai,*d,{1,0x73,3,2},input,*out,report);
    require(report.offers.empty() && bytes(*out)==bytes(*d) &&
            report.contextAfter.negotiation==input.negotiation,"four-turn cooldown mutated negotiation");
    verifyDraws(report,0,1);
    input.negotiation->lastOfferTurn[1][2]=2; input.negotiation->offerState[2]=4;
    run(ai,*d,{1,0x73,3,2},input,*out,report);
    require(report.offers==std::vector<AiPactOffer>{{1,2,8,AiOfferOutcome::Busy}} && report.pacts.empty() &&
            report.contextAfter.negotiation->lastOfferTurn[1][2]==7 &&
            report.contextAfter.negotiation->offerState[1]==0 && report.contextAfter.negotiation->offerState[2]==4 &&
            report.attitudes.empty(),"busy target did not keep target state or write cooldown/reset proposer");
    verifyDraws(report,0,2);
    d->options.turn=std::numeric_limits<int32_t>::min();
    input.negotiation->lastOfferTurn[1][2]=std::numeric_limits<int32_t>::max()-4;
    run(ai,*d,{1,0x73,3,2},input,*out,report);
    require(report.offers.size()==1 && report.contextAfter.negotiation->lastOfferTurn[1][2]==d->options.turn,
            "cooldown signed32 subtraction did not wrap to five");
    verifyDraws(report,0,2);
    input.negotiation->lastOfferTurn[1][2]=std::numeric_limits<int32_t>::max()-3;
    run(ai,*d,{1,0x73,3,2},input,*out,report);
    require(report.offers.empty(),"wrapped four-turn cooldown did not skip offer"); verifyDraws(report,0,1);

    d=oneTechnologyOffer(); initialize(ai,*d); input=context(0,true);
    run(ai,*d,{1,0x73,3,2},input,*out,report);
    require(report.offers==std::vector<AiPactOffer>{{1,2,8,AiOfferOutcome::Accepted}} &&
            report.pacts==std::vector<AiPactEdit>{{1,2,AiPactAction::Make,8,8,true}} &&
            out->players[1].relations[2]==8 && out->players[2].relations[1]==8 &&
            out->players[1].relations2[2]==14 && out->players[2].relations2[1]==14,
            "AI accepted technology offer did not commit four original masks");
    require(report.contextAfter.negotiation->processedOfferMask[2]==2 &&
            report.contextAfter.negotiation->offerState[1]==0 && report.contextAfter.negotiation->offerState[2]==0 &&
            report.attitudes.size()==2 && report.attitudes[0].player==2 && report.attitudes[1].player==1 &&
            word(out->scratchJob2,2,1)==2 && word(out->scratchJob2,1,2)==4,
            "AI offer response order, processed mask, final state or baseline deltas differ");
    verifyDraws(report,0,3);
}

void rejectedAndRepeatedOffers() {
    auto d=oneTechnologyOffer(); auto out=fixture(); AiSession ai; initialize(ai,*d);
    word(d->scratchJob1,2,1,0); // Recipient threshold10; rejection uses a NEW parity draw.
    const auto seed=seedFor([](const auto& r){return !(r[0]&1u) && r[1]%100<90 && r[2]%100>=10 && !(r[3]&1u);});
    auto input=context(seed,true); AiReactionReport report;
    run(ai,*d,{1,0x73,3,2},input,*out,report);
    require(report.offers==std::vector<AiPactOffer>{{1,2,8,AiOfferOutcome::Rejected}} && report.pacts.empty() &&
            word(out->scratchJob1,2,1)==4 && word(out->scratchJob1,1,2)==42 &&
            report.contextAfter.negotiation->processedOfferMask[2]==2,
            "AI rejected offer lost rejection gate or proposer penalty");
    verifyDraws(report,seed,4);
    require(report.draws[3].tag=="AiOfferRejectionAttitude00406c64","rejection parity draw order differs");

    input=context(0,true); input.negotiation->processedOfferMask[2]=2;
    run(ai,*d,{1,0x73,3,2},input,*out,report);
    require(report.offers[0].outcome==AiOfferOutcome::Rejected && report.attitudes.size()==1 &&
            report.attitudes[0].player==1 && word(out->scratchJob1,2,1)==0 &&
            report.contextAfter.negotiation->processedOfferMask[2]==2,
            "repeat offer did not skip recipient assessment/gate/attitude");
    verifyDraws(report,0,2);
}

void humanResponseRollback() {
    auto d=fixture(); auto out=fixture(); AiSession ai; initialize(ai,*d);
    d->aiWarMask[1]=8; word(d->scratchJob1,1,0,0); word(d->scratchJob1,2,0,50);
    d->players[1].relations[0]=d->players[0].relations[1]=2;
    d->players[1].relations2[0]=d->players[0].relations2[1]=2;
    d->players[2].relations2[0]=6;
    const auto seed=seedFor([](const auto& r){return !(r[0]&7u) && !(r[2]&1u) && r[3]%100<90;});
    auto input=context(seed,true); input.relationChangeMask[1]=1;
    input.pendingMessages.push_back({0,2,31,7,{1,2,3}});
    AiReactionReport report; report.handled=true; report.contextAfter=context(123,true);
    report.pacts.push_back({6,5,AiPactAction::Make,16,16,true});
    const auto prior=report; const auto unchanged=input; const auto source=bytes(*d), kept=bytes(*out);
    save::Error error;
    require(!ai.reactEvent(*d,{1,10,0,0},input,*out,report,error) &&
            error.message.find("real human response")!=std::string::npos && report==prior &&
            bytes(*d)==source && bytes(*out)==kept && input==unchanged,
            "human response failure leaked old-war, public-clear, callback, queue or RNG effects");
    require(!ai.reactEvent(*d,{1,10,0,0},input,*d,report,error) && bytes(*d)==source && report==prior,
            "human response failure leaked source/output alias mutation");
    // Missing context must likewise reject only when the callback needs it.
    input.negotiation.reset();
    require(!ai.reactEvent(*d,{1,10,0,0},input,*out,report,error) && report==prior && bytes(*out)==kept,
            "missing live negotiation state was silently reset");
}

void missingCallbackBinding() {
    auto d=fixture(2); auto out=fixture(); AiSession ai; initialize(ai,*d);
    // The public-break traversal visits all seven physical slots, including
    // this newly changed slot outside numPlayers. Its saved type cannot create
    // an owned callback binding that was absent at initializeAfterLoad.
    d->players[2].type=3; word(d->scratchJob1,1,0,0);
    d->players[1].relations[0]=d->players[0].relations[1]=14;
    d->players[1].relations2[0]=d->players[0].relations2[1]=14;
    auto input=context(0); input.relationChangeMask[1]=1;
    AiReactionReport report; report.handled=true;
    report.pactEvents.push_back({6,0x72,4,5}); report.contextAfter=context(55,true);
    const auto saved=report; const auto source=bytes(*d), kept=bytes(*out); save::Error error;
    require(!ai.reactEvent(*d,{1,10,0,0},input,*out,report,error) &&
            error.message.find("initialized")!=std::string::npos && report==saved &&
            bytes(*d)==source && bytes(*out)==kept,
            "uninitialized third-party callback did not roll back prior public pact clear");
}
} // namespace
int main() {
    try {
        rtl::srand(0x913579bdu); (void)rtl::lrand(); gg.rng2Seed=0xabcdef01u;
        const auto low=rtl::seed(),high=rtl::seedHi();
        const auto globals=std::make_unique<GameGlobals>(gg);
        const auto game=std::make_unique<GameState>(gs);
        unilateralAndRejectedAck(); publicCallbacksAndNotice(); event72AndLiveSwap();
        cooldownBusyAndAccepted(); rejectedAndRepeatedOffers(); humanResponseRollback(); missingCallbackBinding();
        require(rtl::seed()==low && rtl::seedHi()==high && std::memcmp(&gg,globals.get(),sizeof(gg))==0 &&
                std::memcmp(&gs,game.get(),sizeof(gs))==0,"owned pact operations touched globals/RNG");
        std::cout<<"AI integrated negotiation tests passed\n"; return 0;
    } catch (const std::exception& e) { std::cerr<<"AI negotiation: "<<e.what()<<'\n'; return 1; }
}
