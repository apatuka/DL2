// Source-derived00406dd8/00476b8c/0042d0ac continuation expectations.
// No original execution oracle or automatic answer is implied.
#include "game/ai_event_transaction.h"
#include "game/event_portraits.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include <array>
#include <cstring>
#include <filesystem>
#include <fstream>
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
int32_t word(const Job& block,int p,int q) {
    int32_t value; std::memcpy(&value,reinterpret_cast<const uint8_t*>(&block)+size_t(p*7+q)*4,4); return value;
}
std::unique_ptr<save::Document> fixture(int active=2,uint32_t baseline=6,uint32_t primary=0) {
    auto d=std::make_unique<save::Document>();
    std::memcpy(d->header.text,save::kHeaderText,sizeof(save::kHeaderText));
    d->header.version=kSaveVersion; d->header.minusOne=-1;
    d->options.numPlayers=active; d->options.localPlayer=0; d->options.turn=7; d->options.allowAlliances=1;
    d->world.width=d->world.height=1; d->world.numTerritories=1;
    d->tiles.resize(1); d->tiles[0].territory=1; d->territories.resize(1); d->territories[0].data.index=1;
    for (int p=0;p<7;++p) {
        d->players[size_t(p)].index=uint8_t(p); d->players[size_t(p)].race=int8_t(p);
        d->players[size_t(p)].type=p==0?1:p<active?3:0;
        d->ministerJobs[size_t(p)].resize(1);
        for (int q=0;q<7;++q) word(d->scratchJob1,p,q,-50);
        for (auto& job:d->jobs[size_t(p)]) { job.owner=int16_t(p); job.targetPlayer=-1; }
    }
    word(d->scratchJob1,1,0,50);
    d->players[1].relations2[0]=d->players[0].relations2[1]=baseline;
    d->players[1].relations[0]=d->players[0].relations[1]=primary;
    d->trailing={0xca,0xfe}; save::Error error;
    require(save::validate(*d,error),"invalid human continuation fixture"); return d;
}
std::vector<uint8_t> bytes(const save::Document& d) {
    std::vector<uint8_t> result; save::Error error;
    if (!save::encode(d,result,error)) throw std::runtime_error(error.message); return result;
}
uint32_t step(uint32_t& state) { state=state*0x41c64e6du+0x3039u; return (state>>16)&0x7fffu; }
template<class Predicate> uint32_t seedFor(Predicate predicate) {
    for (uint32_t seed=0;seed<100000;++seed) {
        auto s=seed; std::array<uint32_t,12> draws{}; for (auto& draw:draws) draw=step(s);
        if (predicate(draws)) return seed;
    }
    throw std::runtime_error("no independent LCG witness for continuation");
}
AiReactionContext context(uint32_t seed=0) {
    AiReactionContext c; c.rng.initialized=true; c.rng.rtlLow=seed; c.rng.secondary=seed;
    c.negotiation.emplace(); c.pendingMessages.push_back({1,1,31,4,{7,8,9}}); return c;
}
void draws(const AiReactionReport& report,uint32_t seed,size_t count) {
    require(report.draws.size()==count,"continuation duplicated or omitted a logical RNG draw");
    auto s=seed;
    for (size_t n=0;n<count;++n)
        require(report.draws[n].ordinal==n+1 && report.draws[n].value==step(s) &&
                report.draws[n].operation==RngOperation::Secondary15 && report.draws[n].consumed,
                "continuation draw differs from independent LCG");
    require(report.contextAfter.rng.secondary==s && report.contextAfter.rng.rtlLow==seed &&
            report.contextAfter.rng.counters.secondary15==count && report.contextAfter.rng.counters.operations==count,
            "continuation RNG snapshot differs");
}
void start(AiEventTransaction& transaction,const save::Document& d,const AiReactionContext& c,
           std::optional<BuildingRemovalContext> campaign=std::nullopt) {
    AiSession ai; save::Error error;
    require(ai.initializeAfterLoad(d,error),"human fixture AI binding failed");
    if (!transaction.begin(d,ai,{1,0x73,2,0},c,campaign,error)) throw std::runtime_error(error.message);
    require(transaction.pending()!=nullptr,"fixture did not reach its human offer");
}
void pauseRejectAndOwnership() {
    auto d=fixture(); const auto original=bytes(*d); auto c=context(); AiSession ai; save::Error error;
    require(ai.initializeAfterLoad(*d,error),"human fixture initialization failed");
    auto output=fixture(); AiReactionReport prior; prior.handled=true; const auto kept=bytes(*output); const auto saved=prior;
    require(!ai.reactEvent(*d,{1,0x73,2,0},c,*output,prior,error) && prior==saved && bytes(*output)==kept &&
            error.message.find("real human response")!=std::string::npos,"legacy API invented a human answer");
    AiEventTransaction tx; require(tx.status()==AiEventTransactionStatus::Empty && !tx.report(),"new transaction is not empty");
    require(tx.begin(*d,ai,{1,0x73,2,0},c,std::nullopt,error),"cannot begin human continuation");
    require(tx.status()==AiEventTransactionStatus::AwaitingHuman && !tx.completedDocument(),"pending document escaped for export");
    const auto offer=*tx.pending(); const auto before=tx.snapshot();
    require(offer.player==1 && offer.recipient==0 && offer.mask==8 && offer.ordinal==1 && offer.transactionId &&
            offer.portrait=="YYALLYN" && offer.checkpoint==tx.report()->contextAfter &&
            offer.checkpoint.negotiation->offerState[1]==2 && offer.checkpoint.negotiation->offerState[0]==2 &&
            offer.checkpoint.negotiation->lastOfferTurn[1][0]==7 &&
            offer.checkpoint.negotiation->processedOfferMask==c.negotiation->processedOfferMask &&
            tx.report()->offers==std::vector<AiPactOffer>{{1,0,8,AiOfferOutcome::AwaitingHuman}},
            "human pause state, portrait or payload differs from original call boundary");
    draws(*tx.report(),0,3);
    require(tx.report()->draws[2].tag=="AiHumanOfferPortrait0042d0ac" && tx.report()->attitudes.empty(),
            "human response accidentally executed AI assessment/attitude code");
    require(!tx.begin(*d,ai,{1,8,0,0},c,std::nullopt,error) && tx.snapshot()==before,"begin discarded a pending offer");
    auto fabricated=offer; ++fabricated.ordinal;
    require(!tx.answer(fabricated,AiHumanAnswer::Accept,error) && tx.snapshot()==before,"fabricated ordinal was accepted");
    fabricated=offer; fabricated.checkpoint.rng.secondary^=1;
    require(!tx.answer(fabricated,AiHumanAnswer::Reject,error) && tx.snapshot()==before,"fabricated checkpoint was accepted");
    require(!tx.answer(offer,static_cast<AiHumanAnswer>(77),error) && tx.snapshot()==before,"invalid response enum was accepted");
    AiEventTransaction independent; start(independent,*d,c);
    require(!tx.answer(*independent.pending(),AiHumanAnswer::Reject,error) && tx.snapshot()==before,"foreign transaction token was accepted");
    auto copy=tx;
    // Destroy/mutate all borrowed inputs after begin; private replay owns them.
    d->players[1].race=6; word(d->scratchJob1,1,0,-50); c.negotiation.reset(); ai=AiSession{};
    require(copy.answer(offer,AiHumanAnswer::Reject,error) && copy.status()==AiEventTransactionStatus::Completed &&
            tx.snapshot()==before,"answering a copied transaction altered the original snapshot");
    require(word(copy.completedDocument()->scratchJob1,1,0)==42 &&
            copy.completedDocument()->players[1].race==1 && copy.report()->attitudes.size()==1 &&
            copy.report()->attitudes[0].player==1 && copy.report()->contextAfter.negotiation->offerState[0]==0 &&
            copy.report()->contextAfter.negotiation->offerState[1]==0 &&
            copy.report()->contextAfter.negotiation->processedOfferMask[0]==0 &&
            copy.report()->contextAfter.pendingMessages==offer.checkpoint.pendingMessages,
            "explicit rejection lost owned inputs, proposer penalty or human state reset");
    draws(*copy.report(),0,3); const auto done=copy.snapshot();
    require(!copy.answer(offer,AiHumanAnswer::Accept,error) && copy.snapshot()==done,"duplicate answer changed completed operation");
    auto bad=context(); bad.rng.initialized=false;
    require(!copy.begin(*d,AiSession{}, {1,8,0,0},bad,std::nullopt,error) && copy.snapshot()==done,
            "failed new begin discarded the last completed result");
    require(original!=bytes(*d),"ownership test did not mutate its source fixture");
}
void acceptAndNestedStack() {
    auto d=fixture(); AiEventTransaction tx; start(tx,*d,context()); save::Error error;
    auto offer=*tx.pending(); require(tx.answer(offer,AiHumanAnswer::Accept,error),"technology acceptance failed");
    const auto& out=*tx.completedDocument();
    require(out.players[1].relations[0]==8 && out.players[0].relations[1]==8 &&
            out.players[1].relations2[0]==14 && out.players[0].relations2[1]==14 &&
            tx.report()->pacts==std::vector<AiPactEdit>{{1,0,AiPactAction::Make,8,8,true}} &&
            tx.report()->attitudes.size()==1 && tx.report()->attitudes[0].baselineAfter==4 &&
            tx.report()->contextAfter.negotiation->processedOfferMask[0]==0,
            "human acceptance changed pact masks, proposer reward or processed AI bitmap");
    draws(*tx.report(),0,3);
    // Outer accepted sender must remain3 while recipient0 is available to a
    // third party's recursive72 offer. Full stack reconstruction is exercised.
    const uint32_t seed=seedFor([](const auto& r){return !(r[0]&1u) && r[1]%100<90 && !(r[3]&1u) && r[4]%100<90;});
    d=fixture(3); word(d->scratchJob1,2,1,50); word(d->scratchJob1,2,0,50);
    d->players[2].relations2[0]=d->players[0].relations2[2]=6;
    auto nestedContext=context(seed); nestedContext.negotiation->lastOfferTurn[2][1]=7;
    AiEventTransaction nested; start(nested,*d,nestedContext); const auto first=*nested.pending();
    require(nested.answer(first,AiHumanAnswer::Accept,error) && nested.pending(),"recursive human offer was not suspended");
    const auto second=*nested.pending(); const auto atSecond=nested.snapshot();
    require(second.ordinal==2 && second.transactionId==first.transactionId && second.player==2 && second.recipient==0 &&
            second.checkpoint.negotiation->offerState[1]==3 && second.checkpoint.negotiation->offerState[2]==2 &&
            second.checkpoint.negotiation->offerState[0]==2 && nested.report()->pacts.size()==1 &&
            nested.report()->pactEvents==std::vector<AiPactEvent>{{2,0x72,1,0}} &&
            nested.snapshot().responses==std::vector<AiHumanResponse>{{first,AiHumanAnswer::Accept}},
            "recursive offer did not preserve sender3/recipient0 ordering or transcript");
    draws(*nested.report(),seed,6);
    require(!nested.answer(first,AiHumanAnswer::Reject,error) && nested.snapshot()==atSecond,"stale first offer answered the second");
    require(nested.answer(second,AiHumanAnswer::Reject,error) && !nested.pending() && nested.completedDocument(),
            "recursive rejection failed to resume outer callback stack");
    require(nested.report()->offers.size()==2 && nested.report()->offers[0].outcome==AiOfferOutcome::Accepted &&
            nested.report()->offers[1].outcome==AiOfferOutcome::Rejected &&
            nested.report()->attitudes.back().player==1 && nested.report()->attitudes.back().baselineAfter==4 &&
            nested.report()->contextAfter.negotiation->offerState==std::array<int32_t,7>{},
            "outer reward/reset did not occur after nested continuation");
    draws(*nested.report(),seed,6);
}
void campaignAndLateFailure() {
    save::Error error;
    BuildingRemovalContext campaign; campaign.campaignFlags=2; campaign.campaignProgress={123456,654321,-777};
    campaign.pendingShrines.entries.push_back({0,1});
    for (const auto mask:{2u,16u}) {
        auto d=fixture(2,mask==2?13u:14u,mask==2?0u:14u); d->options.campaign=1;
        AiEventTransaction tx; start(tx,*d,context(),campaign); const auto offer=*tx.pending();
        require(offer.mask==mask && offer.campaignCheckpoint==campaign,"campaign fixture selected wrong offer");
        require(tx.answer(offer,AiHumanAnswer::Accept,error),"campaign pact acceptance failed");
        auto expected=campaign; expected.campaignProgress[0]=1;
        require(tx.campaignAfter() && *tx.campaignAfter()==expected &&
                tx.completedDocument()->options.campaignBytes[0]==d->options.campaignBytes[0],
                "campaign acceptance lost live int32/progress queue or modified SAV byte archive");
    }
    auto d=fixture(2,13); d->options.campaign=1; AiEventTransaction missing; start(missing,*d,context());
    const auto offer=*missing.pending(); const auto checkpoint=missing.snapshot();
    require(!missing.answer(offer,AiHumanAnswer::Accept,error) && missing.snapshot()==checkpoint && !missing.completedDocument(),
            "missing campaign state leaked partial acceptance");
    require(missing.answer(offer,AiHumanAnswer::Reject,error) && missing.completedDocument(),
            "failed acceptance prevented explicit rejection");
    // Flag2 requires a canonical goal1, but zero flags must not inspect it.
    d->options.campaign=0; AiEventTransaction noGoal; start(noGoal,*d,context(),campaign);
    const auto noGoalOffer=*noGoal.pending(); const auto noGoalBefore=noGoal.snapshot();
    require(!noGoal.answer(noGoalOffer,AiHumanAnswer::Accept,error) && noGoal.snapshot()==noGoalBefore,
            "out-of-row native campaign objective write was silently invented");
    campaign.campaignFlags=0; AiEventTransaction disabled; start(disabled,*d,context(),campaign);
    require(disabled.answer(*disabled.pending(),AiHumanAnswer::Accept,error) && *disabled.campaignAfter()==campaign,
            "disabled campaign lookup changed live progress");
    // Exact equality2/16, not a bit test: military+technology10 does not need
    // campaign state and must leave it untouched when supplied.
    const auto combinedSeed=seedFor([](const auto& r){return !(r[0]&1u) && r[1]%100<80 && r[2]%100<70;});
    d=fixture(2,5); AiEventTransaction combined; start(combined,*d,context(combinedSeed));
    require(combined.pending()->mask==10 && combined.answer(*combined.pending(),AiHumanAnswer::Accept,error) &&
            !combined.campaignAfter(),"combined pact incorrectly entered exact-mask campaign branch");
    // Objective write precedes even the clear-incompatible73 callbacks; their
    // recursive human pause must already own its updated campaign checkpoint.
    const auto recursiveSeed=seedFor([](const auto& r){return !(r[0]&1u) && r[1]%100<80 && !(r[3]&1u) && r[4]%100<90;});
    d=fixture(3,13); d->options.campaign=1; word(d->scratchJob1,2,0,50);
    d->players[2].relations2[0]=d->players[0].relations2[2]=6;
    campaign.campaignFlags=2; AiEventTransaction recursive;
    start(recursive,*d,context(recursiveSeed),campaign); const auto first=*recursive.pending();
    require(recursive.answer(first,AiHumanAnswer::Accept,error) && recursive.pending(),
            "clear-incompatible callback did not suspend at its human offer");
    const auto second=*recursive.pending(); auto expected=campaign; expected.campaignProgress[0]=1;
    require(second.player==2 && second.ordinal==2 && second.campaignCheckpoint==expected &&
            second.checkpoint.negotiation->offerState[1]==3 &&
            recursive.report()->pactEvents==std::vector<AiPactEvent>{{2,0x73,1,0}},
            "campaign goal update did not precede clear callback or sender3 was reset early");
    require(recursive.answer(second,AiHumanAnswer::Reject,error) && recursive.completedDocument() &&
            *recursive.campaignAfter()==expected && recursive.completedDocument()->players[1].relations[0]==2,
            "clear-callback continuation failed to finish its outer accepted military pact");
}
void aiOnlyParity() {
    auto d=fixture(); d->players[0].type=3; d->players[6].type=1; d->options.localPlayer=6; word(d->scratchJob1,0,1,50);
    AiSession ai; save::Error error; require(ai.initializeAfterLoad(*d,error),"AI parity binding failed");
    auto output=fixture(); AiReactionReport expected;
    require(ai.reactEvent(*d,{1,0x73,2,0},context(),*output,expected,error),"legacy AI parity operation failed");
    AiEventTransaction tx;
    require(tx.begin(*d,ai,{1,0x73,2,0},context(),std::nullopt,error) && tx.completedDocument() &&
            *tx.report()==expected && bytes(*tx.completedDocument())==bytes(*output) && tx.snapshot().responses.empty(),
            "explicit transaction changed AI-only behavior");
}
class OriginalPe {
    std::vector<uint8_t> data_; size_t sections_=0; uint16_t count_=0; uint32_t base_=0;
    uint32_t u32(size_t p) const { require(p+4<=data_.size(),"truncated original PE"); return uint32_t(data_[p])|uint32_t(data_[p+1])<<8|uint32_t(data_[p+2])<<16|uint32_t(data_[p+3])<<24; }
    uint16_t u16(size_t p) const { return uint16_t(u32(p)); }
    size_t offset(uint32_t va) const {
        require(va>=base_,"original PE VA below base"); auto rva=va-base_;
        for (size_t n=0;n<count_;++n) { const auto p=sections_+n*40; const auto start=u32(p+12),size=u32(p+16);
            if (rva>=start && rva-start<size) return size_t(u32(p+20))+rva-start; }
        throw std::runtime_error("unbacked original PE address");
    }
public:
    explicit OriginalPe(const std::filesystem::path& path) {
        auto size=std::filesystem::file_size(path); require(size>=64 && size<=16*1024*1024,"invalid original PE size");
        data_.resize(size_t(size)); std::ifstream in(path,std::ios::binary);
        require(bool(in.read(reinterpret_cast<char*>(data_.data()),std::streamsize(size))),"cannot read original PE");
        auto pe=u32(0x3c); require(u16(0)==0x5a4d && u32(pe)==0x4550 && u16(pe+24)==0x10b,"not original PE32");
        count_=u16(pe+6); base_=u32(pe+52); sections_=pe+24+u16(pe+20);
        require(count_>0 && count_<100 && sections_+count_*40<=data_.size(),"invalid PE sections");
    }
    uint32_t word(uint32_t va) const { return u32(offset(va)); }
    std::string string(uint32_t va) const {
        std::string s; for (size_t p=offset(va);p<data_.size() && s.size()<32;++p) {
            if (!data_[p]) return s; s.push_back(char(data_[p])); }
        throw std::runtime_error("invalid original portrait string");
    }
};
void portraitPe(const std::filesystem::path& directory) {
    if (directory.empty() || !std::filesystem::is_regular_file(directory/"DEADLOCK.EXE")) {
        std::cout<<"AI event transaction: optional original PE unavailable\n"; return;
    }
    OriginalPe pe(directory/"DEADLOCK.EXE");
    for (int race=0;race<7;++race) {
        const auto names=data::eventPortraitNames(race,15); const auto cell=0x4ca3b0u+15u*56u+uint32_t(race)*8u;
        require(pe.word(cell+4)==names.size(),"category15 count differs from shipped PE");
        const auto pointers=pe.word(cell);
        for (size_t n=0;n<names.size();++n)
            require(pe.string(pe.word(pointers+uint32_t(n)*4))==names[n],"category15 portrait name differs from shipped PE");
    }
}
}
int main(int argc,char** argv) {
    try {
        rtl::srand(0xabcd0123); (void)rtl::lrand(); gg.rng2Seed=0x413579bd;
        const auto low=rtl::seed(),high=rtl::seedHi();
        const auto globals=std::make_unique<GameGlobals>(gg); const auto game=std::make_unique<GameState>(gs);
        pauseRejectAndOwnership(); acceptAndNestedStack(); campaignAndLateFailure(); aiOnlyParity();
        portraitPe(argc>1?std::filesystem::path(argv[1]):std::filesystem::path{});
        require(rtl::seed()==low && rtl::seedHi()==high && std::memcmp(&gg,globals.get(),sizeof(gg))==0 &&
                std::memcmp(&gs,game.get(),sizeof(gs))==0,"human continuation touched process globals/RNG");
        std::cout<<"AI event transaction tests passed\n"; return 0;
    } catch (const std::exception& e) { std::cerr<<"AI event transaction: "<<e.what()<<'\n'; return 1; }
}
