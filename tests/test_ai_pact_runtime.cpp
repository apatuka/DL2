// Source-derived publication/locking contracts for resumable00441400.
// No assertion here represents execution of the original game binary.
#include "game/runtime_state.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include <cstring>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

namespace {
using namespace dl2;
using namespace dl2::simulation;
void require(bool value,const char* message) { if (!value) throw std::runtime_error(message); }
void word(Job& job,int p,int q,int32_t value) {
    std::memcpy(reinterpret_cast<uint8_t*>(&job)+size_t(p*7+q)*4,&value,4);
}
std::vector<uint8_t> bytes(const save::Document& document) {
    std::vector<uint8_t> result; save::Error error;
    if (!save::encode(document,result,error)) throw std::runtime_error(error.message);
    return result;
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
    d->players[0].relations[1]=0; d->players[1].relations[0]=2;
    d->players[0].relations2[1]=d->players[1].relations2[0]=2;
    for (int p=2;p<count;++p) {
        word(d->scratchJob1,p,1,50);
        d->players[size_t(p)].relations[1]=d->players[1].relations[p]=existing;
        d->players[size_t(p)].relations2[1]=d->players[1].relations2[p]=existing;
    }
    d->armies.resize(1); auto& army=d->armies[0];
    army.id=101; army.type=1; army.unitClass=1; army.owner=2; army.health=100;
    army.territory.raw=army.dest.raw=army.origin.raw=1;
    d->trailing={0x78,0x56}; save::Error error;
    require(save::validate(*d,error),"invalid runtime pact fixture"); return d;
}
AiPactReconciliationContext context(uint32_t seed=0) {
    AiPactReconciliationContext c;
    c.ai.rng.initialized=true; c.ai.rng.rtlLow=seed; c.ai.rng.secondary=seed;
    c.ai.negotiation.emplace(); c.ai.pendingMessages.push_back({0,2,31,7,{8,9,10}});
    c.log.emplace(); c.cities={5,8,3,1,0,0,0}; return c;
}
void checkDraws(const AiPactReconciliationReport& report,size_t count) {
    require(report.draws.size()==count,"runtime reconciliation duplicated or lost draws");
    uint32_t seed=0;
    for (size_t i=0;i<count;++i) {
        seed=seed*0x41c64e6du+0x3039u;
        require(report.draws[i].operation==RngOperation::Secondary15 && report.draws[i].consumed &&
                report.draws[i].value==((seed>>16)&0x7fffu) && report.draws[i].ordinal==i+1,
                "runtime reconciliation draw differs from independent LCG");
    }
    require(report.contextAfter.ai.rng.secondary==seed && report.contextAfter.ai.rng.rtlLow==0 &&
            report.contextAfter.ai.rng.counters.secondary15==count &&
            report.contextAfter.ai.rng.counters.operations==count,"runtime reconciliation RNG checkpoint differs");
}
void checkPublished(const runtime::State& state,const AiPactReconciliationReport& report,
                    runtime::ArmyHandle army,runtime::TerritoryHandle territory) {
    require(!state.pendingAiOffer() && state.stage()==runtime::Stage::EntitiesEdited &&
            state.aiSession() && state.aiReactionContext() && *state.aiReactionContext()==report.contextAfter.ai &&
            state.loadedEvents() && report.contextAfter.log && *state.loadedEvents()==*report.contextAfter.log &&
            state.eventCities() && *state.eventCities()==report.contextAfter.cities &&
            state.sessionRng()==report.contextAfter.ai.rng && state.army(army) && state.armyById(101)==army &&
            state.territoryByIndex(1)==territory && state.armyLinks(army)->current==territory &&
            state.armyLinks(army)->turnStart==territory && state.armyLinks(army)->routeOrigin==territory &&
            state.document()->events.empty() && state.document()->options.turn==7,
            "pact completion failed to publish one owned continuation or changed stable identities");
}
void pendingLocksAndOrderedCompletion() {
    auto d=fixture(4); auto captured=fixture(); runtime::State state; save::Error error;
    require(state.prepare(*d,error),"runtime pact preparation failed");
    const auto original=bytes(*state.document()); const auto pointer=state.document(); const auto rng=state.sessionRng();
    const auto army=state.armyById(101); const auto territory=state.territoryByIndex(1);
    auto c=context(); const auto input=c; AiPactReconciliationReport report;
    require(state.beginAiPactReconciliation(c,std::nullopt,report,error) && state.pendingAiOffer(),
            "runtime reconciliation did not suspend on the first human offer");
    const auto first=*state.pendingAiOffer(); const auto pendingReport=report;
    require(first.player==2 && first.recipient==1 && first.mask==8 && report.pairs.size()==1 &&
            report.deliveries.size()==2 && report.contextAfter.log->entries.size()==1 &&
            report.contextAfter.log->entries[0].type==0x3a && report.contextAfter.log->entries[0].player==0 &&
            report.contextAfter.log->entries[0].param==2 && report.draws.front().tag=="LogEventPortrait",
            "runtime progress lost pre-offer local event payload/order");
    checkDraws(report,4);
    auto unchanged=[&] {
        require(state.document()==pointer && bytes(*state.document())==original && state.stage()==runtime::Stage::Prepared &&
                state.sessionRng()==rng && !state.aiSession() && !state.aiReactionContext() && !state.loadedEvents() &&
                !state.eventCities() && !state.buildingRemovalContext() && state.army(army) &&
                state.armyById(101)==army && state.territoryByIndex(1)==territory && state.pendingAiOffer() &&
                *state.pendingAiOffer()==first,"pending reconciliation changed its published baseline or identities");
    };
    unchanged();
    MovementCrossingsContext crossings; crossings.ai = input.ai;
    crossings.log = input.log; crossings.cities = input.cities;
    MovementCrossingsReport crossingReport;
    require(!state.resolveMovementCrossings(crossings,crossingReport,error) &&
            error.message == "A human AI offer awaits its explicit answer",
            "crossings bypassed the pending human reconciliation lock");
    unchanged();
    const auto capturedBefore=bytes(*captured); TaxPlan tax; EnergyPlan energy; LaborBalancePlan labor;
    runtime::LoadReport load; ArmyLifecycleReport removal; AiReactionReport event;
    require(!state.capture(*captured,error) && bytes(*captured)==capturedBefore && !state.prepare(*d,error) &&
            !state.collectTaxes(tax,error) && !state.consumeEnergy(energy,error) && !state.normalizeLabor(labor,error) &&
            !state.normalizeLoad({},load,error) && !state.removeArmy(army,ArmyRemovalKind::DeleteUnit,true,removal,error) &&
            !state.reactAiEvent({2,0x40,0,0},c.ai,event,error) &&
            !state.beginAiEvent({2,0x73,0,1},c.ai,std::nullopt,event,error) &&
            !state.beginAiPactReconciliation(c,std::nullopt,report,error) && report==pendingReport &&
            !state.answerAiOffer(first,AiHumanAnswer::Reject,event,error) && !state.advanceTurn(error),
            "pending reconciliation permitted another edit, transaction, answer route or export");
    auto forged=first; ++forged.mask;
    require(!state.answerAiPactOffer(forged,AiHumanAnswer::Accept,report,error) && report==pendingReport,
            "runtime accepted forged pact offer payload");
    runtime::State foreign; AiPactReconciliationReport foreignReport;
    require(foreign.prepare(*d,error) && foreign.beginAiPactReconciliation(c,std::nullopt,foreignReport,error) &&
            !state.answerAiPactOffer(*foreign.pendingAiOffer(),AiHumanAnswer::Reject,report,error) && report==pendingReport,
            "runtime accepted pact offer from a foreign state");
    unchanged();
    // A pending cursor owns its document/context despite later caller changes.
    d->options.turn=99; c.log.reset(); c.cities.fill(99);
    runtime::State moved=std::move(state);
    require(!state.document() && !state.pendingAiOffer() && moved.pendingAiOffer() && *moved.pendingAiOffer()==first &&
            moved.army(army) && moved.territoryByIndex(1)==territory,"moving State lost pending pact identity or entity handles");
    require(moved.answerAiPactOffer(first,AiHumanAnswer::Reject,report,error) && moved.pendingAiOffer(),
            "runtime did not continue to second ordered observer");
    const auto second=*moved.pendingAiOffer(); const auto secondReport=report;
    require(second.player==3 && second.recipient==1 && second.transactionId!=first.transactionId &&
            bytes(*moved.document())==original && moved.sessionRng()==rng && !moved.loadedEvents() &&
            moved.stage()==runtime::Stage::Prepared && report.contextAfter.cities==input.cities &&
            report.contextAfter.log->entries.size()==1 && report.pairs.size()==1,
            "second pause prematurely published/repeated effects or retained borrowed inputs");
    checkDraws(report,7);
    require(!moved.answerAiPactOffer(first,AiHumanAnswer::Accept,report,error) && report==secondReport &&
            !moved.answerAiPactOffer(second,static_cast<AiHumanAnswer>(77),report,error) && report==secondReport &&
            *moved.pendingAiOffer()==second,"stale/invalid response consumed the second pending offer");
    require(moved.answerAiPactOffer(second,AiHumanAnswer::Reject,report,error),"second explicit rejection did not finish");
    checkPublished(moved,report,army,territory); checkDraws(report,7);
    require(report.pairs.size()==16 && moved.loadedEvents()->entries.size()==1 &&
            moved.document()->players[0].relations[1]==0 && moved.document()->players[1].relations2[0]==0 &&
            moved.document()->players[2].relations[1]==6 && moved.document()->players[3].relations2[1]==6,
            "completion missed live intersections, changed rejected pacts or repeated local betrayal log");
    const auto complete=bytes(*moved.document()); const auto completeReport=report;
    require(!moved.answerAiPactOffer(second,AiHumanAnswer::Accept,report,error) && report==completeReport &&
            bytes(*moved.document())==complete && !moved.capture(*captured,error) && !moved.advanceTurn(error),
            "completed reconciliation allowed duplicate response or partial-turn export");
}
void acceptedContinuationAndRewinds() {
    auto d=fixture(); runtime::State state; save::Error error; AiPactReconciliationReport report;
    const auto initial=context(); require(state.prepare(*d,error),"acceptance runtime prepare failed");
    const auto army=state.armyById(101); const auto territory=state.territoryByIndex(1);
    require(state.beginAiPactReconciliation(initial,std::nullopt,report,error),"acceptance reconciliation begin failed");
    const auto offer=*state.pendingAiOffer();
    require(state.answerAiPactOffer(offer,AiHumanAnswer::Accept,report,error),"human pact acceptance did not complete");
    checkPublished(state,report,army,territory); checkDraws(report,5);
    require(report.pairs.size()==9 && state.document()->players[2].relations[1]==14 &&
            state.document()->players[1].relations2[2]==14,"accepted pact was not published in all words");
    const auto complete=bytes(*state.document()); const auto savedReport=report; const auto owned=report.contextAfter;
    for (int variant=0;variant<5;++variant) {
        auto stale=owned;
        if (variant==0) stale.ai.pendingMessages.clear();
        if (variant==1) stale.ai.rng.secondary=0;
        if (variant==2) stale.log.reset();
        if (variant==3) stale.log->entries[0].param^=4;
        if (variant==4) ++stale.cities[0];
        require(!state.beginAiPactReconciliation(stale,std::nullopt,report,error) && report==savedReport &&
                bytes(*state.document())==complete && *state.loadedEvents()==*owned.log &&
                *state.eventCities()==owned.cities && state.sessionRng()==owned.ai.rng && !state.pendingAiOffer(),
                "runtime permitted a log, city, message or RNG continuation rewind");
    }
    // Deliberately alias report.contextAfter with the input context.
    require(state.beginAiPactReconciliation(report.contextAfter,std::nullopt,report,error) && !state.pendingAiOffer() &&
            report.draws.empty() && report.deliveries.empty() && report.pairs.size()==9 && report.contextAfter==owned &&
            bytes(*state.document())==complete,"current owned context was rejected or repeated previous effects");
    AiReactionReport reaction;
    require(state.beginAiEvent({2,0x40,0,0},*state.aiReactionContext(),std::nullopt,reaction,error) &&
            !state.pendingAiOffer() && *state.loadedEvents()==*owned.log && *state.eventCities()==owned.cities,
            "pact continuation did not feed the existing AI event API or lost live log/cities");
}
void campaignFailureRetryAndCrossLock() {
    auto d=fixture(3,13); d->options.campaign=1; runtime::State state; save::Error error;
    AiPactReconciliationReport report; require(state.prepare(*d,error),"missing campaign runtime prepare failed");
    require(state.beginAiPactReconciliation(context(),std::nullopt,report,error),"missing campaign begin failed");
    const auto pending=*state.pendingAiOffer(); const auto beforeReport=report;
    const auto before=bytes(*state.document()); const auto rng=state.sessionRng();
    require(pending.mask==2 && !state.answerAiPactOffer(pending,AiHumanAnswer::Accept,report,error) &&
            report==beforeReport && *state.pendingAiOffer()==pending && bytes(*state.document())==before &&
            state.sessionRng()==rng && !state.loadedEvents() && !state.buildingRemovalContext(),
            "late missing campaign state leaked pending document, log, RNG or report");
    require(state.answerAiPactOffer(pending,AiHumanAnswer::Reject,report,error) && !state.pendingAiOffer() &&
            state.loadedEvents()->entries.size()==1,"failed campaign acceptance prevented genuine rejection");
    runtime::State accepted; require(accepted.prepare(*d,error),"explicit campaign runtime prepare failed");
    BuildingRemovalContext campaign; campaign.campaignFlags=2; campaign.campaignProgress={99999,-12345,654321};
    campaign.pendingShrines.entries={{1,1},{1,1}};
    require(accepted.beginAiPactReconciliation(context(),campaign,report,error),"explicit campaign reconciliation failed");
    const auto offer=*accepted.pendingAiOffer();
    require(offer.campaignCheckpoint==campaign && !accepted.buildingRemovalContext() &&
            accepted.answerAiPactOffer(offer,AiHumanAnswer::Accept,report,error),"explicit campaign pact response failed");
    auto expected=campaign; expected.campaignProgress[0]=1;
    require(accepted.buildingRemovalContext() && *accepted.buildingRemovalContext()==expected &&
            accepted.loadedEvents()->entries.size()==1 && accepted.document()->players[2].relations[1]==14,
            "campaign acceptance lost flags, native progress or duplicate shrine queue");
    const auto complete=bytes(*accepted.document()); const auto completedReport=report;
    require(!accepted.beginAiPactReconciliation(report.contextAfter,campaign,report,error) && report==completedReport &&
            bytes(*accepted.document())==complete && *accepted.buildingRemovalContext()==expected,
            "runtime rewound campaign/shrine continuation after pact acceptance");
    require(accepted.beginAiPactReconciliation(report.contextAfter,expected,report,error) && !accepted.pendingAiOffer(),
            "runtime rejected the current campaign continuation");
    // Conversely, an ordinary pending AI event excludes the pact transaction.
    d=fixture(); runtime::State eventState; AiReactionReport reaction; const auto c=context();
    require(eventState.prepare(*d,error) &&
            eventState.beginAiEvent({2,0x73,0,1},c.ai,std::nullopt,reaction,error) && eventState.pendingAiOffer(),
            "cross-lock event fixture did not pause");
    const auto eventOffer=*eventState.pendingAiOffer(); const auto kept=report;
    require(!eventState.beginAiPactReconciliation(c,std::nullopt,report,error) && report==kept &&
            !eventState.answerAiPactOffer(eventOffer,AiHumanAnswer::Reject,report,error) && report==kept &&
            *eventState.pendingAiOffer()==eventOffer,"pact API replaced or answered an ordinary pending event");
    require(eventState.answerAiOffer(eventOffer,AiHumanAnswer::Reject,reaction,error) && !eventState.pendingAiOffer(),
            "pact rejection damaged the ordinary event continuation");
}
void synchronousParityAndFailedBegin() {
    auto d=fixture(); for (int p=0;p<7;++p) for (int q=0;q<7;++q) word(d->scratchJob1,p,q,-50);
    AiSession ai; save::Error error; auto out=fixture(); const auto c=context(); AiPactReconciliationReport expected;
    require(ai.initializeAfterLoad(*d,error) && reconcileAiPacts(*d,ai,c,*out,expected,error),"no-human parity leaf failed");
    runtime::State state; AiPactReconciliationReport report; require(state.prepare(*d,error),"no-human runtime prepare failed");
    const auto army=state.armyById(101); const auto territory=state.territoryByIndex(1);
    require(state.beginAiPactReconciliation(c,std::nullopt,report,error) && report==expected &&
            bytes(*state.document())==bytes(*out),"runtime changed synchronous reconciliation behavior");
    checkPublished(state,report,army,territory);
    runtime::State invalid; require(invalid.prepare(*d,error),"invalid-begin state prepare failed");
    const auto before=bytes(*invalid.document()); const auto saved=report; auto missing=c; missing.log.reset();
    require(!invalid.beginAiPactReconciliation(missing,std::nullopt,report,error) && report==saved &&
            bytes(*invalid.document())==before && invalid.stage()==runtime::Stage::Prepared && !invalid.pendingAiOffer() &&
            !invalid.loadedEvents() && !invalid.aiSession() && !invalid.aiReactionContext(),
            "failed begin published a partial log/session or changed the previous output");
    TaxPlan taxes; require(invalid.collectTaxes(taxes,error),"terminal-stage fixture tax plan failed");
    require(!invalid.beginAiPactReconciliation(c,std::nullopt,report,error) && report==saved &&
            invalid.stage()==runtime::Stage::TaxesApplied,"reconciliation bypassed an experimental terminal stage");
}
} // namespace
int main() {
    try {
        rtl::srand(0x73ac2468); (void)rtl::lrand(); gg.rng2Seed=0xdeadbeef;
        const auto low=rtl::seed(),high=rtl::seedHi();
        const auto globals=std::make_unique<GameGlobals>(gg); const auto game=std::make_unique<GameState>(gs);
        pendingLocksAndOrderedCompletion(); acceptedContinuationAndRewinds();
        campaignFailureRetryAndCrossLock(); synchronousParityAndFailedBegin();
        require(rtl::seed()==low && rtl::seedHi()==high && std::memcmp(&gg,globals.get(),sizeof(gg))==0 &&
                std::memcmp(&gs,game.get(),sizeof(gs))==0,"runtime pact transaction touched global state or RNG");
        std::cout<<"AI pact runtime tests passed\n"; return 0;
    } catch (const std::exception& e) { std::cerr<<"AI pact runtime: "<<e.what()<<'\n'; return 1; }
}
