#include "game/ai_pact_transaction.h"
#include <bit>
#include <exception>
#include <new>
#include <stdexcept>
#include <utility>

namespace dl2::simulation {
namespace {
bool fail(save::Error& error,const char* message,save::ErrorCode code=save::ErrorCode::InvalidState) {
    error={code,0,message}; return false;
}
template<class F> bool guarded(F&& operation,save::Error& error) {
    try { return operation(); }
    catch (const std::bad_alloc&) { return fail(error,"Insufficient memory continuing pact reconciliation",save::ErrorCode::Limit); }
    catch (const std::length_error&) { return fail(error,"Pact reconciliation continuation exceeds allocation limits",save::ErrorCode::Limit); }
    catch (const std::exception& exception) { error={save::ErrorCode::InvalidState,0,exception.what()}; return false; }
}
int signedType(uint8_t type) { return type<128 ? type : int(type)-256; }
std::array<uint32_t,4> pairWords(const save::Document& d,int p,int q) {
    return {d.players[size_t(p)].relations[q],d.players[size_t(q)].relations[p],
            d.players[size_t(p)].relations2[q],d.players[size_t(q)].relations2[p]};
}
} // namespace
struct AiPactReconciliationTransaction::State {
    save::Document document;
    AiSession ai;
    AiPactReconciliationReport report;
    std::optional<BuildingRemovalContext> campaign;
    AiEventTransactionStatus status=AiEventTransactionStatus::Empty;
    AiPactReconciliationPhase phase=AiPactReconciliationPhase::PairStart;
    int player=0,other=0,nextRecipient=0;
    std::optional<AiPactReconciliationPair> pair;
    std::optional<AiEventTransaction> delivery;
    size_t deliveryIndex=0,drawPrefix=0;
};

// The nested event owns its immutable base and validated answer transcript.
// Replace its visible suffix after replay; prior log/delivery effects stay in
// this cursor's document/report and are never replayed by the outer operation.
bool AiPactReconciliationTransaction::publishDelivery(State& state,save::Error& error) {
    if (!state.delivery || !state.delivery->report() || state.deliveryIndex>=state.report.deliveries.size() ||
        state.drawPrefix>state.report.draws.size()) return fail(error,"Invalid pact reconciliation delivery checkpoint");
    const auto& reaction=*state.delivery->report();
    state.report.deliveries[state.deliveryIndex].reaction=reaction;
    state.report.contextAfter.ai=reaction.contextAfter;
    state.report.draws.resize(state.drawPrefix);
    state.report.draws.insert(state.report.draws.end(),reaction.draws.begin(),reaction.draws.end());
    if (const auto* campaign=state.delivery->campaignAfter()) state.campaign=*campaign;
    else state.campaign.reset();
    if (state.delivery->status()==AiEventTransactionStatus::AwaitingHuman) {
        state.status=AiEventTransactionStatus::AwaitingHuman; return true;
    }
    const auto* completed=state.delivery->completedDocument();
    if (state.delivery->status()!=AiEventTransactionStatus::Completed || !completed)
        return fail(error,"Pact reconciliation delivery neither completed nor awaits a human answer");
    state.document=*completed;
    state.delivery.reset();
    return true;
}
bool AiPactReconciliationTransaction::dispatch(State& state,int recipient,int eventType,save::Error& error) {
    const int p=state.player,q=state.other;
    const uint32_t changed=state.pair->changed; // Captured before any callback.
    AiPactReconciliationDelivery delivery;
    delivery.recipient=recipient; delivery.eventType=eventType;
    delivery.player=p; delivery.other=q; delivery.changed=changed;
    if (recipient==state.document.options.localPlayer) {
        if (eventType!=0x3a)
            return fail(error,"Pact reconciliation local slot must retain its offline human type");
        if (!state.report.contextAfter.log)
            return fail(error,"Pact betrayal requires the explicit existing local event log");
        LocalEventRequest request; request.type=0x3a;
        request.arguments={int32_t(p),std::bit_cast<int32_t>(changed),int32_t(0),int32_t(0)};
        request.payload=EventPayload{p,std::bit_cast<int32_t>(changed)};
        LocalEventReport local;
        if (!logLocalEvent(state.document,*state.report.contextAfter.log,
                {state.report.contextAfter.ai.rng,state.report.contextAfter.cities},request,
                *state.report.contextAfter.log,local,error)) return false;
        state.report.contextAfter.ai.rng=local.rngAfter;
        state.report.draws.insert(state.report.draws.end(),local.randomDraws.begin(),local.randomDraws.end());
        delivery.route=AiPactDeliveryRoute::LocalLog; delivery.stored=local.stored;
    } else if (signedType(state.document.players[size_t(recipient)].type)>=3) {
        const int32_t extra2=eventType==0x3a?std::bit_cast<int32_t>(changed):q;
        AiEventTransaction reaction;
        if (!reaction.begin(state.document,state.ai,{recipient,eventType,p,extra2},
                            state.report.contextAfter.ai,state.campaign,error)) return false;
        delivery.route=AiPactDeliveryRoute::AiReaction;
        state.deliveryIndex=state.report.deliveries.size();
        state.report.deliveries.push_back(std::move(delivery));
        state.drawPrefix=state.report.draws.size(); state.delivery=std::move(reaction);
        return publishDelivery(state,error);
    }
    state.report.deliveries.push_back(std::move(delivery)); return true;
}

//00441400 row-major cursor. Advance beyond a dispatch BEFORE it can suspend.
// No list of pairs/differences is precomputed: later visits see callback edits.
bool AiPactReconciliationTransaction::advance(State& state,save::Error& error) {
    if (state.delivery) return fail(error,"Cannot advance reconciliation before its pending event completes");
    for (;;) {
        const int p=state.player,q=state.other;
        auto& d=state.document;
        switch (state.phase) {
        case AiPactReconciliationPhase::PairStart: {
            if (p>=d.options.numPlayers) {
                if (!save::validate(d,error)) return false;
                state.phase=AiPactReconciliationPhase::Finished; state.status=AiEventTransactionStatus::Completed;
                error={}; return true;
            }
            AiPactReconciliationPair pair; pair.player=p; pair.other=q; pair.before=pairWords(d,p,q);
            if (d.players[size_t(p)].type==0 || d.players[size_t(q)].type==0) {
                d.players[size_t(p)].relations[q]=d.players[size_t(q)].relations[p]=0;
                d.players[size_t(p)].relations2[q]=d.players[size_t(q)].relations2[p]=0;
                pair.clearedInactive=true;
            }
            pair.changed=d.players[size_t(p)].relations[q]^d.players[size_t(p)].relations2[q];
            state.phase=pair.changed?AiPactReconciliationPhase::Victim:AiPactReconciliationPhase::Intersection;
            state.pair=pair; break;
        }
        case AiPactReconciliationPhase::Victim:
            state.phase=AiPactReconciliationPhase::ThirdParties; state.nextRecipient=0;
            if (!dispatch(state,q,0x3a,error)) return false;
            if (state.delivery) { error={}; return true; }
            break;
        case AiPactReconciliationPhase::ThirdParties:
            while (state.nextRecipient<kMaxPlayers) {
                const int recipient=state.nextRecipient++;
                if (recipient==p || recipient==q || signedType(d.players[size_t(recipient)].type)<3) continue;
                if (!dispatch(state,recipient,0x73,error)) return false;
                if (state.delivery) { error={}; return true; }
            }
            state.phase=AiPactReconciliationPhase::Intersection; break;
        case AiPactReconciliationPhase::Intersection:
            //0044152c..00441548: reread primary words after the entire callback
            // stack, intersect live values, THEN copy both secondary words.
            if (d.players[size_t(q)].relations[p]!=d.players[size_t(p)].relations[q]) {
                d.players[size_t(p)].relations[q]&=d.players[size_t(q)].relations[p];
                d.players[size_t(q)].relations[p]&=d.players[size_t(p)].relations[q];
            }
            d.players[size_t(p)].relations2[q]=d.players[size_t(p)].relations[q];
            d.players[size_t(q)].relations2[p]=d.players[size_t(q)].relations[p];
            state.pair->after=pairWords(d,p,q); state.report.pairs.push_back(*state.pair); state.pair.reset();
            if (++state.other>=d.options.numPlayers) { state.other=0; ++state.player; }
            state.phase=AiPactReconciliationPhase::PairStart; break;
        case AiPactReconciliationPhase::Finished:
            return fail(error,"Completed reconciliation cannot advance again");
        }
    }
}
bool AiPactReconciliationTransaction::begin(const save::Document& source,const AiSession& ai,
    const AiPactReconciliationContext& context,const std::optional<BuildingRemovalContext>& campaign,save::Error& error) {
    return guarded([&] {
        if (status()==AiEventTransactionStatus::AwaitingHuman)
            return fail(error,"Pact reconciliation is already awaiting an explicit human answer");
        if (!save::validate(source,error)) return false;
        if (source.header.isMap) return fail(error,"Pact reconciliation requires a saved game");
        if (context.ai.pendingMessages.size()>kAiMessageCapacity)
            return fail(error,"Pact reconciliation message FIFO exceeds its original capacity",save::ErrorCode::Limit);
        SessionRng rng; if (!rng.restore(context.ai.rng,error)) return false;
        auto state=std::make_shared<State>(); state->document=source; state->ai=ai;
        state->report.contextAfter=context; state->campaign=campaign;
        if (!advance(*state,error)) return false;
        state_=std::move(state); error={}; return true;
    },error);
}
bool AiPactReconciliationTransaction::answer(const AiHumanOffer& offer,AiHumanAnswer answerValue,save::Error& error) {
    return guarded([&] {
        if (!state_ || state_->status!=AiEventTransactionStatus::AwaitingHuman || !state_->delivery)
            return fail(error,"No pact reconciliation is awaiting a human answer");
        // COW keeps both the cursor and child transaction unchanged on failure.
        auto state=std::make_shared<State>(*state_);
        if (!state->delivery->answer(offer,answerValue,error) || !publishDelivery(*state,error)) return false;
        if (!state->delivery && !advance(*state,error)) return false;
        state_=std::move(state); error={}; return true;
    },error);
}
AiEventTransactionStatus AiPactReconciliationTransaction::status() const noexcept {
    return state_?state_->status:AiEventTransactionStatus::Empty;
}
const AiHumanOffer* AiPactReconciliationTransaction::pending() const noexcept {
    return state_ && state_->delivery?state_->delivery->pending():nullptr;
}
const save::Document* AiPactReconciliationTransaction::completedDocument() const noexcept {
    return status()==AiEventTransactionStatus::Completed?&state_->document:nullptr;
}
const AiPactReconciliationReport* AiPactReconciliationTransaction::report() const noexcept {
    return state_?&state_->report:nullptr;
}
const BuildingRemovalContext* AiPactReconciliationTransaction::campaignAfter() const noexcept {
    return state_ && state_->campaign?&*state_->campaign:nullptr;
}
AiPactTransactionSnapshot AiPactReconciliationTransaction::snapshot() const {
    AiPactTransactionSnapshot snapshot;
    if (!state_) return snapshot;
    snapshot.status=state_->status; snapshot.phase=state_->phase;
    snapshot.player=state_->player; snapshot.other=state_->other; snapshot.nextRecipient=state_->nextRecipient;
    snapshot.currentPair=state_->pair; if (const auto* offer=pending()) snapshot.pending=*offer;
    snapshot.report=state_->report; snapshot.campaignAfter=state_->campaign; return snapshot;
}
} // namespace dl2::simulation
