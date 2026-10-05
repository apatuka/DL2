// Owned offline human-offer continuation. No native callbacks or UI effects.
#pragma once
#include "game/ai_session.h"
#include "game/entity_lifecycle.h"
#include <memory>
#include <optional>
#include <vector>

namespace dl2::simulation {
enum class AiEventTransactionStatus { Empty,AwaitingHuman,Completed };
enum class AiHumanAnswer { Accept,Reject };
struct AiHumanOffer {
    uint64_t transactionId=0;
    uint32_t ordinal=0;
    int player=-1,recipient=-1;
    uint32_t mask=0;
    std::string portrait;
    // State AFTER dialog portrait selection, with both offer states2.
    AiReactionContext checkpoint;
    std::optional<BuildingRemovalContext> campaignCheckpoint;
    bool operator==(const AiHumanOffer&) const = default;
};
struct AiHumanResponse {
    AiHumanOffer offer;
    AiHumanAnswer answer=AiHumanAnswer::Reject;
    bool operator==(const AiHumanResponse&) const = default;
};
struct AiEventTransactionSnapshot {
    AiEventTransactionStatus status=AiEventTransactionStatus::Empty;
    uint64_t transactionId=0;
    std::optional<AiHumanOffer> pending;
    AiReactionReport report;
    std::optional<BuildingRemovalContext> campaignAfter;
    std::vector<AiHumanResponse> responses;
    bool operator==(const AiEventTransactionSnapshot&) const = default;
};
namespace ai_event_detail {
// Private engine protocol: the only caller is AiEventTransaction through its
// friend binding. Data-only interception never executes caller callbacks.
inline constexpr size_t kMaxHumanResponses=128;
struct ReplayState {
    uint64_t transactionId=0;
    std::vector<AiHumanResponse> responses;
    size_t consumed=0;
    std::optional<AiHumanOffer> pending;
    std::optional<BuildingRemovalContext> campaign;
};
}

class AiEventTransaction {
public:
    // Copies share immutable private snapshots; answering one copy publishes
    // only that copy's candidate. This supports runtime's copy-before-edit.
    // No caller Document/context/session pointer is retained. A second begin
    // cannot silently discard a pending response. Completed transactions may
    // start a new operation, which receives a new identity.
    bool begin(const save::Document& source,const AiSession& ai,const AiEventRequest& request,
               const AiReactionContext& context,const std::optional<BuildingRemovalContext>& campaign,
               save::Error& error);
    // The supplied offer must exactly match pending(), including its owned
    // checkpoint. Refused/failed/stale/duplicate answers leave this transaction
    // unchanged. Only these explicit answers substitute the original buttons.
    bool answer(const AiHumanOffer& offer,AiHumanAnswer answer,save::Error& error);
    AiEventTransactionStatus status() const noexcept;
    const AiHumanOffer* pending() const noexcept;
    // Pending candidate documents are deliberately unavailable for export.
    // Const views below remain valid until this instance successfully changes.
    const save::Document* completedDocument() const noexcept;
    const AiReactionReport* report() const noexcept;
    const BuildingRemovalContext* campaignAfter() const noexcept;
    AiEventTransactionSnapshot snapshot() const;
private:
    struct State;
    std::shared_ptr<const State> state_;
    bool replay(const std::shared_ptr<const State>& initial,const std::vector<AiHumanResponse>& responses,
                std::shared_ptr<const State>& output,save::Error& error) const;
};
} // namespace dl2::simulation
