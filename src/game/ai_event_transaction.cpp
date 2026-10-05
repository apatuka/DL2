#include "game/ai_event_transaction.h"
#include <atomic>
#include <exception>
#include <limits>
#include <new>
#include <stdexcept>
#include <utility>

namespace dl2::simulation {
namespace {
bool fail(save::Error& error,const char* message,
          save::ErrorCode code=save::ErrorCode::InvalidState) {
    error={code,0,message}; return false;
}
template<class F> bool guarded(F&& operation,save::Error& error) {
    try { return operation(); }
    catch (const std::bad_alloc&) { return fail(error,"Insufficient memory continuing an AI event",save::ErrorCode::Limit); }
    catch (const std::length_error&) { return fail(error,"AI event continuation exceeds allocation limits",save::ErrorCode::Limit); }
    catch (const std::exception& exception) { error={save::ErrorCode::InvalidState,0,exception.what()}; return false; }
}
bool nextIdentity(uint64_t& identity,save::Error& error) {
    // Ownership identity only: never seeds or consumes the gameplay RNG.
    static std::atomic<uint64_t> next{1};
    auto current=next.load(std::memory_order_relaxed);
    do {
        if (current==std::numeric_limits<uint64_t>::max())
            return fail(error,"AI event transaction identity exhausted",save::ErrorCode::Limit);
    } while (!next.compare_exchange_weak(current,current+1,std::memory_order_relaxed));
    identity=current; return true;
}
struct Inputs {
    save::Document source;
    AiSession ai;
    AiEventRequest request;
    AiReactionContext context;
    std::optional<BuildingRemovalContext> campaign;
    uint64_t identity=0;
};
} // namespace
struct AiEventTransaction::State {
    std::shared_ptr<const Inputs> inputs;
    save::Document document;
    AiReactionReport report;
    std::optional<BuildingRemovalContext> campaign;
    std::vector<AiHumanResponse> responses;
    std::optional<AiHumanOffer> pending;
    AiEventTransactionStatus status=AiEventTransactionStatus::Empty;
};

bool AiEventTransaction::replay(const std::shared_ptr<const State>& initial,
    const std::vector<AiHumanResponse>& responses,std::shared_ptr<const State>& output,save::Error& error) const {
    const auto& inputs=*initial->inputs;
    auto result=std::make_shared<State>(); result->inputs=initial->inputs; result->responses=responses;
    ai_event_detail::ReplayState execution;
    execution.transactionId=inputs.identity; execution.responses=responses; execution.campaign=inputs.campaign;
    if (!inputs.ai.replayEvent(inputs.source,inputs.request,inputs.context,execution,
                               result->document,result->report,error)) return false;
    if (execution.consumed!=responses.size())
        return fail(error,"AI event replay left supplied human answers unused");
    result->campaign=std::move(execution.campaign); result->pending=std::move(execution.pending);
    result->status=result->pending ? AiEventTransactionStatus::AwaitingHuman : AiEventTransactionStatus::Completed;
    output=std::move(result); error={}; return true;
}
bool AiEventTransaction::begin(const save::Document& source,const AiSession& ai,const AiEventRequest& request,
    const AiReactionContext& context,const std::optional<BuildingRemovalContext>& campaign,save::Error& error) {
    return guarded([&] {
        if (status()==AiEventTransactionStatus::AwaitingHuman)
            return fail(error,"An AI event is already awaiting its explicit human answer");
        auto inputs=std::make_shared<Inputs>();
        inputs->source=source; inputs->ai=ai; inputs->request=request; inputs->context=context; inputs->campaign=campaign;
        if (!nextIdentity(inputs->identity,error)) return false;
        auto initial=std::make_shared<State>(); initial->inputs=std::move(inputs);
        std::shared_ptr<const State> result;
        if (!replay(initial,{},result,error)) return false;
        state_=std::move(result); error={}; return true;
    },error);
}
bool AiEventTransaction::answer(const AiHumanOffer& offer,AiHumanAnswer answerValue,save::Error& error) {
    return guarded([&] {
        if (!state_ || state_->status!=AiEventTransactionStatus::AwaitingHuman || !state_->pending)
            return fail(error,"No AI event is awaiting a human answer");
        if (answerValue!=AiHumanAnswer::Accept && answerValue!=AiHumanAnswer::Reject)
            return fail(error,"Unknown human pact response");
        if (offer!=*state_->pending)
            return fail(error,"Human pact response does not match the pending transaction, offer and checkpoint");
        if (state_->responses.size()>=ai_event_detail::kMaxHumanResponses)
            return fail(error,"AI event human response transcript exceeds its supported limit",save::ErrorCode::Limit);
        auto responses=state_->responses; responses.push_back({offer,answerValue});
        std::shared_ptr<const State> result;
        if (!replay(state_,responses,result,error)) return false;
        state_=std::move(result); error={}; return true;
    },error);
}
AiEventTransactionStatus AiEventTransaction::status() const noexcept {
    return state_ ? state_->status : AiEventTransactionStatus::Empty;
}
const AiHumanOffer* AiEventTransaction::pending() const noexcept {
    return state_ && state_->pending ? &*state_->pending : nullptr;
}
const save::Document* AiEventTransaction::completedDocument() const noexcept {
    return status()==AiEventTransactionStatus::Completed ? &state_->document : nullptr;
}
const AiReactionReport* AiEventTransaction::report() const noexcept { return state_ ? &state_->report : nullptr; }
const BuildingRemovalContext* AiEventTransaction::campaignAfter() const noexcept {
    return state_ && state_->campaign ? &*state_->campaign : nullptr;
}
AiEventTransactionSnapshot AiEventTransaction::snapshot() const {
    AiEventTransactionSnapshot result;
    if (!state_) return result;
    result.status=state_->status; result.transactionId=state_->inputs->identity;
    result.pending=state_->pending; result.report=state_->report;
    result.campaignAfter=state_->campaign; result.responses=state_->responses; return result;
}
} // namespace dl2::simulation
