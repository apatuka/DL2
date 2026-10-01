// Owned event/timer reconstruction, with explicit pre-load context.
#pragma once
#include <array>
#include <cstdint>
#include <string>
#include <vector>
#include "game/session_rng.h"

namespace dl2::simulation {
struct EventLoadContext {
    RngSnapshot rngBeforeEvents;
    // Original city counters are not reset or loaded before LoadEventLog.
    // Supply the previous session's values, or explicit zeros for a fresh one.
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
struct LoadedEventLog {
    std::vector<LoadedEvent> entries;
    std::array<std::vector<uint32_t>, 6> pageIndices;
    uint32_t poolBytes = 0;
    int32_t firstVisible = 0;
    std::vector<RngEvent> randomDraws;
    RngSnapshot rngAfterEvents;
    bool operator==(const LoadedEventLog&) const = default;
};
// 004600d0 -> 004234d4/004503f4, 00422d18. Supports known portrait races/categories
// and the original pool without eviction. Rejects oversize/embedded-NUL domains
// and ID0x646c (the original lookup aliases adjacent non-table storage).
// Existing text is not formatted, translated or invented. RNG advances for the
// random portrait index selector (-1); EventDef.portrait<0 means NO portrait.
// Event portrait category7 uses city comparison, without consuming RNG.
// Caller runs after profile/options/player load, BEFORE CountShrines/AI/roads.
// Input/context untouched; failure preserves report, including its RNG state.
bool rebuildLoadedEvents(const save::Document& document, const EventLoadContext& context,
                         LoadedEventLog& destination, save::Error& error);

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
