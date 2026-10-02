// Owned event/timer reconstruction, with explicit pre-load context.
#pragma once
#include <array>
#include <cstdint>
#include <string>
#include <vector>
#include <optional>
#include <variant>
#include "game/session_rng.h"

namespace dl2::simulation {
struct EventLoadContext {
    RngSnapshot rngBeforeEvents;
    // Original city counters are not reset or loaded before LoadEventLog.
    // Supply the previous session's values, or explicit zeros for a fresh one.
    // For NEW LogEvent calls this same field supplies the CURRENT counters;
    // retain citiesAfter when a gameplay step executes CountShrines.
    std::array<int32_t, kMaxPlayers> citiesBeforeLoad{};
};
struct LoadedEvent {
    uint16_t type = 0;
    int32_t player = 0, param = 0;
    int16_t category = 0;
    std::vector<uint8_t> text; // Exact bytes, NOT a native EXE pointer.
    std::string portraitResource; // Resolved resource name, not an address.
    bool operator==(const LoadedEvent&) const = default;
};
struct EventPayload {
    int32_t player = 0, param = 0;
    bool operator==(const EventPayload&) const = default;
};
struct LoadedEventLog {
    std::vector<LoadedEvent> entries;
    std::array<std::vector<uint32_t>, 6> pageIndices;
    uint32_t poolBytes = 0;
    uint32_t evictedEvents = 0;
    int32_t firstVisible = 0;
    std::vector<RngEvent> randomDraws;
    RngSnapshot rngAfterEvents;
    // LoadEventLog can leave payload words in inactive slots after eviction.
    // Preserve them so later LogEvent (without Ex) observes the same words.
    std::array<EventPayload, kMaxEvents> slotPayloads{};
    bool operator==(const LoadedEventLog&) const = default;
};
// 004600d0 -> 004234d4/004503f4, 00422d18. Supports known portrait races/categories
// and the original pool with Borland-priority eviction. Rejects embedded-NUL domains
// and ID0x646c (the original lookup aliases adjacent non-table storage).
// Existing text is not formatted, translated or invented. RNG advances for the
// random portrait index selector (-1); EventDef.portrait<0 means NO portrait.
// Event portrait category7 uses city comparison, without consuming RNG.
// Caller runs after profile/options/player load, BEFORE CountShrines/AI/roads.
// Input/context untouched; failure preserves report, including its RNG state.
bool rebuildLoadedEvents(const save::Document& document, const EventLoadContext& context,
                         LoadedEventLog& destination, save::Error& error);

using EventArgument = std::variant<int32_t, std::string>;
struct LocalEventRequest {
    uint16_t type = 0;
    std::vector<EventArgument> arguments; // sprintf arguments, at most four.
    std::optional<EventPayload> payload; // LogEventEx, not LoadEventLog's file-index rule.
};
struct LocalEventReport {
    bool stored = false;
    int32_t index = -1;
    uint32_t evictedEvents = 0;
    RngSnapshot rngAfter;
    std::vector<RngEvent> randomDraws;
    bool operator==(const LocalEventReport&) const = default;
};
// orig: LogEvent 00423690 / LogEventEx 004237d0, LOCAL recipient branch only.
// Canonical %s/%d text, exact count/pool eviction and portrait consumption.
// Event58 takes player index + pact mask integers, as the original does.
// Strings must have no NUL and formatted text must fit the original1024-byte
// buffer. Invalid/undefined original domains fail atomically, not overflow.
// A priority rejection is a successful evaluated operation with stored=false:
// the original still sorts and may evict entries before returning -1.
// Does not invoke an AI recipient or deliver native windows. Caller must route
// nonlocal recipients to the actual AI handler separately. The log's draw list
// describes this operation only; previous portraits never consume RNG again.
// Caller supplies CURRENT gameplay RNG/city counts, not the load-time snapshot.
bool logLocalEvent(const save::Document& document, const LoadedEventLog& previous,
                   const EventLoadContext& context, const LocalEventRequest& request,
                   LoadedEventLog& destination, LocalEventReport& report, save::Error& error);

struct LoadTimerState {
    bool running = false;
    uint32_t startedMs = 0;
    int32_t seconds = 0;
    bool operator==(const LoadTimerState&) const = default;
};
struct LoadTimerReport {
    LoadTimerState state;
    int32_t activePlayers = 0, finishedPlayers = 0;
    bool restarted = false;
    bool operator==(const LoadTimerReport&) const = default;
};
// 0045efd0 / 0045f148, offline non-editor. Explicit clock/previous timer,
// no OS calls and no timer-triggered turn until the turn engine exists.
bool planLoadTimer(const save::Document& document, const LoadTimerState& previous,
                   uint32_t nowMs, LoadTimerReport& destination, save::Error& error);
}
