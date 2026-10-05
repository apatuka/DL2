// Explicit treaty reconciliation, not a complete turn or implicit AI reset.
#pragma once
#include "game/ai_session.h"
#include "game/load_session.h"
#include <array>
#include <optional>
#include <vector>

namespace dl2::simulation {
struct AiPactReconciliationContext {
    AiReactionContext ai;
    // Required only if a changed pair routes betrayal event58 to local.
    std::optional<LoadedEventLog> log;
    std::array<int32_t,kMaxPlayers> cities{}; // Live0065e3cc for local event rules.
    bool operator==(const AiPactReconciliationContext&) const = default;
};
enum class AiPactDeliveryRoute { Ignored,LocalLog,AiReaction };
struct AiPactReconciliationDelivery {
    int recipient = -1,eventType = 0,player = -1,other = -1;
    uint32_t changed = 0;
    AiPactDeliveryRoute route = AiPactDeliveryRoute::Ignored;
    bool stored = false;
    // Full nested AI effects, including callback order; no fabricated log entry.
    std::optional<AiReactionReport> reaction;
    bool operator==(const AiPactReconciliationDelivery&) const = default;
};
struct AiPactReconciliationPair {
    int player = -1,other = -1;
    // Ordered {primary[p][q],primary[q][p],secondary[p][q],secondary[q][p]}.
    std::array<uint32_t,4> before{},after{};
    bool clearedInactive = false;
    uint32_t changed = 0; // XOR captured before any event callback.
    bool operator==(const AiPactReconciliationPair&) const = default;
};
struct AiPactReconciliationReport {
    AiPactReconciliationContext contextAfter;
    std::vector<RngEvent> draws; // One authoritative local+AI sequence.
    std::vector<AiPactReconciliationPair> pairs; // All numPlayers^2 visits.
    std::vector<AiPactReconciliationDelivery> deliveries;
    bool operator==(const AiPactReconciliationReport&) const = default;
};
// orig:00441400 ->004237d0 -> local log or real AI callbacks. Row-major,
// including diagonals; no allowAlliances guard and no00405378 reset/drift.
// Callbacks precede live pair intersection/baseline update. Consequently the
// earlier reverse pair can normalize away a later pair's betrayal notice.
// A nested human offer retains AiSession's explicit capability rejection.
// All outputs atomic, including source==destination and context/report alias.
// Document.events remains archival; contextAfter.log owns live local records.
bool reconcileAiPacts(const save::Document& source,const AiSession& ai,
    const AiPactReconciliationContext& context,save::Document& destination,
    AiPactReconciliationReport& report,save::Error& error);
} // namespace dl2::simulation
