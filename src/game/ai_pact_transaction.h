// Owned00441400 continuation through explicit human pact responses.
#pragma once
#include "game/ai_event_transaction.h"
#include "game/ai_pact_reconciliation.h"
#include <memory>
#include <optional>

namespace dl2::simulation {
enum class AiPactReconciliationPhase { PairStart,Victim,ThirdParties,Intersection,Finished };
struct AiPactTransactionSnapshot {
    AiEventTransactionStatus status=AiEventTransactionStatus::Empty;
    AiPactReconciliationPhase phase=AiPactReconciliationPhase::PairStart;
    int player=0,other=0,nextRecipient=0;
    std::optional<AiPactReconciliationPair> currentPair;
    std::optional<AiHumanOffer> pending;
    AiPactReconciliationReport report;
    std::optional<BuildingRemovalContext> campaignAfter;
    bool operator==(const AiPactTransactionSnapshot&) const = default;
};
class AiPactReconciliationTransaction {
public:
    // Copies share immutable snapshots. Source, AI bindings and all contexts
    // are owned; begin/answer publish only their successful private candidate.
    // A new begin cannot discard a pending decision. No original/network/UI
    // callbacks are executed, and no answer is supplied implicitly.
    bool begin(const save::Document& source,const AiSession& ai,
               const AiPactReconciliationContext& context,
               const std::optional<BuildingRemovalContext>& campaign,save::Error& error);
    bool answer(const AiHumanOffer& offer,AiHumanAnswer answer,save::Error& error);
    AiEventTransactionStatus status() const noexcept;
    const AiHumanOffer* pending() const noexcept;
    const save::Document* completedDocument() const noexcept;
    // While pending, pairs contains only completed intersections and the last
    // delivery's reaction is partial. contextAfter.ai equals the offer's exact
    // checkpoint, including RNG; log/cities retain completed prior effects.
    // Resuming replaces this partial reaction and its draw suffix, never logs
    // an event again or appends repeated replay draws. Views remain valid until
    // this instance successfully changes; copy the offer before replying.
    const AiPactReconciliationReport* report() const noexcept;
    const BuildingRemovalContext* campaignAfter() const noexcept;
    AiPactTransactionSnapshot snapshot() const;
private:
    struct State;
    std::shared_ptr<const State> state_;
    static bool advance(State& state,save::Error& error);
    static bool dispatch(State& state,int recipient,int eventType,save::Error& error);
    static bool publishDelivery(State& state,save::Error& error);
};
} // namespace dl2::simulation
