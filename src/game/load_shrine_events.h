// LoadGame CountShrines notices are real log/AI effects, not just UI requests.
#pragma once
#include "game/ai_session.h"
#include "game/load_derived.h"
#include "game/load_session.h"
#include <optional>
#include <vector>

namespace dl2::simulation {
enum class ShrineEventRoute { LocalLog, AiReaction, Ignored };
struct ShrineEventDelivery {
    ShrineNotice notice;
    ShrineEventRoute route = ShrineEventRoute::Ignored;
    bool stored = false; // Local log insertion; AI effects are in aiAfter/draws.
    bool operator==(const ShrineEventDelivery&) const = default;
};
struct LoadShrineEventsReport {
    // The log's own trace/RNG describe its last local-log operation (or the
    // supplied prior log if none). The fields below combine ALL local+AI draws.
    LoadedEventLog logAfter;
    std::optional<AiReactionContext> aiAfter;
    RngSnapshot rngAfter; // Authoritative post-notice state, before final reseed.
    std::vector<RngEvent> draws;
    std::vector<ShrineEventDelivery> deliveries;
    bool operator==(const LoadShrineEventsReport&) const = default;
};
// orig:004618e8 -> CountShrines00486964 -> LogEventEx004237d0.
// Source/derived must describe the same POST-CountShrines document. Consume its
// notices in original order after AInit, before AfterMove(load=1). Local messages
// format canonical race/territory names and store payload{owner,0}; nonlocal AI
// receives the ACTUAL extended arguments{owner,0}; other slots are skipped.
// Unlike ordinary LogEvent00423690, these extra arguments are not both zero.
// previousAi is required only if a notice routes to a nonlocal signed type>=3.
// rngBeforeNotices is authoritative AFTER loaded portraits/changed-world draws:
// priorAi.rng is deliberately replaced while masks/queue/gameAborted are kept.
// The load orchestrator supplies reset gameAborted=false, not a hidden default.
// No final LoadGame RNG reseed, window delivery or AI turn is performed here.
// Transactional document+report, including source==destination and report/context
// aliases. Missing context is an error, never an empty-success substitute.
bool replayLoadShrineEvents(const save::Document& postDerived,
    const LoadDerivedReport& derived, const AiSession& ai,
    const LoadedEventLog& previousLog, const RngSnapshot& rngBeforeNotices,
    const std::optional<AiReactionContext>& previousAi,
    save::Document& destination, LoadShrineEventsReport& report, save::Error& error);
} // namespace dl2::simulation
