#include "game/load_session.h"
#include "game/data_tables.h"
#include "game/event_portraits.h"
#include <algorithm>
#include <exception>
#include <stdexcept>
#include <utility>

namespace dl2::simulation {
namespace {
bool fail(save::Error& e, save::ErrorCode code, const char* message) {
    e = {code, 0, message}; return false;
}
const data::EventDef& definition(uint16_t type) {
    // 0042278c's last (157th) iteration reads adjacent string storage, not an
    // EventDef. Known IDs occupy the 156 canonical rows. Unknown IDs use row0.
    for (const auto& row : data::kEventDefs) if (row.id == int(type)) return row;
    return data::kEventDefs[0];
}
bool allied(const save::Document& d, int first, int second) {
    return d.options.allowAlliances && first >= 0 && second >= 0 &&
        first < d.options.numPlayers && second < d.options.numPlayers &&
        (d.players[size_t(first)].relations[size_t(second)] & 0x10u);
}
int page(int category) {
    switch (category) {
    case 0: return 0;
    case -1: case 2: return 1;
    case 8: case 9: case 12: case 13: return 2;
    case 5: case 10: return 3;
    case 1: case 3: case 4: case 11: return 4;
    case 6: return 5;
    default: return -1;
    }
}
// orig: 00423380 and Borland qsort 004b14e8 -> 004b1304. The comparator
// returns -1 on ties, so std::sort/stable_sort would be undefined/different.
// Keep the original median partition, small-array cases and swap order.
void sortForEviction(std::array<LoadedEvent, kMaxEvents>& entries, size_t first, size_t count) {
    const auto compare = [&](size_t a, size_t b) {
        const int difference = definition(entries[b].type).priority - definition(entries[a].type).priority;
        return difference ? difference : -1;
    };
    const auto swap = [&](size_t a, size_t b) { std::swap(entries[a], entries[b]); };
    while (count >= 3) {
        size_t right = first + count - 1, middle = first + count / 2;
        if (compare(middle, right) > 0) swap(middle, right);
        if (compare(middle, first) <= 0) {
            if (compare(first, right) > 0) swap(first, right);
        } else swap(middle, first);
        if (count == 3) { swap(first, middle); return; }
        size_t left = first + 1, equals = left;
        bool reachedEnd = false;
        do {
            int comparison;
            while ((comparison = compare(left, first)) <= 0) {
                if (comparison == 0) swap(left, equals++);
                if (right <= left) { reachedEnd = true; break; }
                ++left;
            }
            if (reachedEnd) break;
            for (; left < right; --right) {
                comparison = compare(first, right);
                if (comparison >= 0) {
                    swap(left, right);
                    if (comparison != 0) { ++left; --right; }
                    break;
                }
            }
        } while (left < right);
        if (compare(left, first) <= 0) ++left;
        for (size_t a = first, b = left - 1; a < equals && equals <= b; ++a, --b) swap(a, b);
        const size_t lower = left - equals, upper = first + count - left;
        if (upper < lower) { sortForEviction(entries, left, upper); count = lower; }
        else { sortForEviction(entries, first, lower); first = left; count = upper; }
    }
    if (count == 2 && compare(first, first + 1) > 0) swap(first, first + 1);
}
}

bool rebuildLoadedEvents(const save::Document& d, const EventLoadContext& context,
                         LoadedEventLog& destination, save::Error& error) {
    try {
        if (!save::validate(d, error)) return false;
        if (d.header.isMap) return fail(error, save::ErrorCode::InvalidState, "Event load requires a saved game");
        LoadedEventLog result;
        SessionRng rng;
        if (!rng.restore(context.rngBeforeEvents, error)) return false;
        result.firstVisible = d.options.eventLogFirst;
        // The original discards pre-current-version text without any RNG draw.
        if (d.header.version == kSaveVersion) {
            const int local = d.options.localPlayer;
            const int race = d.players[size_t(local)].race;
            std::array<LoadedEvent, kMaxEvents> slots{};
            size_t count = 0;
            for (size_t savedIndex = 0; savedIndex < d.events.size(); ++savedIndex) {
                const auto& saved = d.events[savedIndex];
                // The original lookup's spurious 157th row aliases "No Building".
                // ID 0x646c matches those bytes and would read invalid metadata.
                if (saved.record.type == 0x646c)
                    return fail(error, save::ErrorCode::InvalidState, "Event ID aliases the original out-of-table lookup; native replay is unsafe");
                if (std::find(saved.text.begin(), saved.text.end(), uint8_t(0)) != saved.text.end())
                    return fail(error, save::ErrorCode::InvalidState, "Native event replay excludes embedded NUL text; archival bytes remain supported");
                const auto& def = definition(saved.record.type);
                // LoadEventLog writes the payload into the FILE index before
                // AddEvent may evict/sort. Do not fix the resulting historical
                // payload displacement by attaching it to the appended index.
                slots[savedIndex].player = saved.record.player;
                slots[savedIndex].param = saved.record.param;
                while (saved.text.size() + 1 >= 3071u - result.poolBytes) {
                    if (!count) return fail(error, save::ErrorCode::Limit, "Event text cannot fit the native pool");
                    sortForEviction(slots, 0, count);
                    if (definition(slots[0].type).priority > def.priority)
                        return fail(error, save::ErrorCode::Limit, "Event pool priority prevents eviction");
                    result.poolBytes -= uint32_t(slots[0].text.size() + 1);
                    for (size_t i = 1; i < count; ++i) slots[i - 1] = std::move(slots[i]);
                    slots[--count] = {};
                    ++result.evictedEvents;
                }
                result.poolBytes += uint32_t(saved.text.size() + 1);
                auto& event = slots[count];
                event.type = saved.record.type; event.category = def.category;
                event.text = saved.text; event.portraitResource.clear();
                if (def.portrait >= 0) {
                    const auto portraits = data::eventPortraitNames(race, def.portrait);
                    if (portraits.empty())
                        return fail(error, save::ErrorCode::InvalidState, "Event portrait race/category is outside the verified table");
                    uint32_t choice;
                    if (def.portrait == 7) {
                        int32_t own = 0, enemy = 0;
                        for (int p = 0; p < kMaxPlayers; ++p) {
                            auto& maximum = p == local || allied(d, local, p) ? own : enemy;
                            maximum = std::max(maximum, context.citiesBeforeLoad[size_t(p)]);
                        }
                        choice = enemy < own ? 0u : enemy == own ? 1u :
                            (saved.record.type == 0x42 || saved.record.type == 0x43) ? 3u : 2u;
                    } else {
                        RngEvent draw;
                        if (!rng.apply({RngOperation::Secondary15, 0, 0, "LoadEventLogPortrait"}, draw, error)) return false;
                        choice = draw.value;
                        result.randomDraws.push_back(std::move(draw));
                    }
                    event.portraitResource = portraits[choice % portraits.size()];
                }
                ++count;
            }
            for (size_t index = 0; index < count; ++index) {
                const int tab = page(slots[index].category);
                if (tab >= 0) result.pageIndices[size_t(tab)].push_back(uint32_t(index));
                result.entries.push_back(std::move(slots[index]));
            }
            for (size_t i = 0; i < slots.size(); ++i)
                result.slotPayloads[i] = {slots[i].player, slots[i].param};
        }
        result.rngAfterEvents = rng.snapshot();
        destination = std::move(result); error = {}; return true;
    } catch (const std::bad_alloc&) {
        return fail(error, save::ErrorCode::Limit, "Insufficient memory rebuilding owned event log");
    } catch (const std::length_error&) {
        return fail(error, save::ErrorCode::Limit, "Owned event log exceeds allocation limits");
    } catch (const std::exception& e) {
        error = {save::ErrorCode::InvalidState, 0, e.what()}; return false;
    }
}

bool logLocalEvent(const save::Document& d, const LoadedEventLog& previous,
                   const EventLoadContext& context, const LocalEventRequest& request,
                   LoadedEventLog& destination, LocalEventReport& report, save::Error& error) try {
    if (!save::validate(d, error)) return false;
    if (d.header.isMap || request.type == 0x646c || request.arguments.size() > 4 ||
        previous.entries.size() > kMaxEvents)
        return fail(error, save::ErrorCode::InvalidState, "Invalid local event domain");
    SessionRng rng;
    if (!rng.restore(context.rngBeforeEvents, error)) return false;
    auto arguments = request.arguments;
    // orig: LogEvent58 converts its first two machine words to race/pact names.
    if (request.type == 0x3a) {
        static constexpr const char* pacts[32] = {
            "None", "Non-aggression", "Military", "ILLEGAL", "Intelligence",
            "Intelligence and Non-aggression", "Intelligence and Military", "ILLEGAL",
            "Technology", "Technology and Non-aggression", "Technology and Military", "ILLEGAL",
            "Technology and Intelligence", "Technology, Intelligence, and Non-aggression",
            "Technology, Intelligence, and Military", "ILLEGAL", "Victory", "ILLEGAL",
            "Victory and Military", "ILLEGAL", "Victory and Intelligence", "ILLEGAL",
            "Victory, Intelligence, and Military", "ILLEGAL", "Victory and Technology", "ILLEGAL",
            "Victory, Technology, and Military", "ILLEGAL", "Victory, Technology, and Intelligence",
            "ILLEGAL", "Victory, Technology, Intelligence, and Military", "ILLEGAL"
        };
        if (arguments.size() < 2 || !std::holds_alternative<int32_t>(arguments[0]) ||
            !std::holds_alternative<int32_t>(arguments[1]))
            return fail(error, save::ErrorCode::InvalidState, "Event58 requires player and pact integers");
        const int player = std::get<int32_t>(arguments[0]), pact = std::get<int32_t>(arguments[1]);
        if (player < 0 || player >= 7 || pact < 0 || pact >= 32 ||
            d.players[size_t(player)].race < 0 || d.players[size_t(player)].race >= 7)
            return fail(error, save::ErrorCode::InvalidState, "Event58 name lookup outside canonical tables");
        arguments[0] = std::string(data::kRaceNames[d.players[size_t(player)].race]);
        arguments[1] = std::string(pacts[pact]);
    }
    const auto& def = definition(request.type);
    std::string text;
    size_t argument = 0;
    for (const char* format = def.format; *format; ++format) {
        if (*format != '%') { text.push_back(*format); continue; }
        ++format;
        if (*format == '%') { text.push_back('%'); continue; }
        if (argument >= arguments.size())
            return fail(error, save::ErrorCode::InvalidState, "Canonical event format is missing an argument");
        const auto& value = arguments[argument++];
        if (*format == 's' && std::holds_alternative<std::string>(value)) {
            const auto& string = std::get<std::string>(value);
            if (string.size() > 1023 || string.find('\0') != std::string::npos)
                return fail(error, save::ErrorCode::Limit, "Event string cannot fit the native text domain");
            text += string;
        } else if (*format == 'd' && std::holds_alternative<int32_t>(value)) text += std::to_string(std::get<int32_t>(value));
        else return fail(error, save::ErrorCode::InvalidState, "Event argument type does not match canonical format");
    }
    if (text.size() > 1023) return fail(error, save::ErrorCode::Limit, "Formatted event exceeds native1024-byte buffer");
    LoadedEventLog result = previous;
    LocalEventReport outcome;
    result.entries.clear(); result.randomDraws.clear();
    for (auto& indices : result.pageIndices) indices.clear();
    std::array<LoadedEvent, kMaxEvents> slots{};
    for (size_t i = 0; i < slots.size(); ++i) {
        slots[i].player = previous.slotPayloads[i].player;
        slots[i].param = previous.slotPayloads[i].param;
    }
    size_t count = previous.entries.size();
    uint32_t bytes = 0;
    for (size_t i = 0; i < count; ++i) {
        const auto& entry = previous.entries[i];
        if (entry.type == 0x646c || entry.text.size() > 1023 ||
            entry.category != definition(entry.type).category ||
            std::find(entry.text.begin(), entry.text.end(), uint8_t(0)) != entry.text.end())
            return fail(error, save::ErrorCode::InvalidState, "Existing local event log is not native-compatible");
        bytes += uint32_t(entry.text.size() + 1); slots[i] = entry;
    }
    if (bytes != previous.poolBytes || bytes >= 3071)
        return fail(error, save::ErrorCode::InvalidState, "Existing event pool byte count is inconsistent");
    bool accepted = true;
    while (count >= kMaxEvents || text.size() + 1 >= 3071u - bytes) {
        if (!count) { accepted = false; break; }
        sortForEviction(slots, 0, count);
        if (definition(slots[0].type).priority > def.priority) { accepted = false; break; }
        if (result.evictedEvents == UINT32_MAX)
            return fail(error, save::ErrorCode::Limit, "Event eviction counter exhausted");
        bytes -= uint32_t(slots[0].text.size() + 1);
        for (size_t i = 1; i < count; ++i) slots[i - 1] = std::move(slots[i]);
        slots[--count] = {}; ++result.evictedEvents; ++outcome.evictedEvents;
    }
    if (accepted) {
        auto& event = slots[count];
        event.type = request.type; event.category = def.category;
        event.text.assign(text.begin(), text.end()); event.portraitResource.clear();
        if (def.portrait >= 0) {
            const int local = d.options.localPlayer;
            const auto names = data::eventPortraitNames(d.players[size_t(local)].race, def.portrait);
            if (names.empty()) return fail(error, save::ErrorCode::InvalidState, "Local event portrait outside canonical table");
            uint32_t choice = 0;
            if (def.portrait == 7) {
                int32_t own = 0, enemy = 0;
                for (int p = 0; p < 7; ++p) {
                    auto& maximum = p == local || allied(d, local, p) ? own : enemy;
                    maximum = std::max(maximum, context.citiesBeforeLoad[size_t(p)]);
                }
                choice = enemy < own ? 0u : enemy == own ? 1u :
                    (request.type == 0x42 || request.type == 0x43) ? 3u : 2u;
            } else {
                RngEvent draw;
                if (!rng.apply({RngOperation::Secondary15, 0, 0, "LogEventPortrait"}, draw, error)) return false;
                choice = draw.value; outcome.randomDraws.push_back(std::move(draw));
            }
            event.portraitResource = names[choice % names.size()];
        }
        if (request.payload) {
            event.player = request.payload->player; event.param = request.payload->param;
            if (request.type == 0x7b) {
                if (event.player < 0 || event.player >= 7 || d.players[size_t(event.player)].race < 0 ||
                    d.players[size_t(event.player)].race > 8)
                    return fail(error, save::ErrorCode::InvalidState, "Eliminated player portrait outside original table");
                event.portraitResource = data::eliminationPortrait(d.players[size_t(d.options.localPlayer)].race,
                                                                  d.players[size_t(event.player)].race);
            }
        }
        outcome.stored = true; outcome.index = int32_t(count++); bytes += uint32_t(text.size() + 1);
    }
    for (size_t i = 0; i < slots.size(); ++i) result.slotPayloads[i] = {slots[i].player, slots[i].param};
    for (size_t i = 0; i < count; ++i) {
        const int tab = page(slots[i].category);
        if (tab >= 0) result.pageIndices[size_t(tab)].push_back(uint32_t(i));
        result.entries.push_back(std::move(slots[i]));
    }
    result.poolBytes = bytes; outcome.rngAfter = rng.snapshot();
    result.rngAfterEvents = outcome.rngAfter; result.randomDraws = outcome.randomDraws;
    destination = std::move(result); report = std::move(outcome); error = {}; return true;
} catch (const std::bad_alloc&) {
    return fail(error, save::ErrorCode::Limit, "Local event allocation failed");
} catch (const std::length_error&) {
    return fail(error, save::ErrorCode::Limit, "Local event allocation exceeds limits");
}

bool planLoadTimer(const save::Document& d, const LoadTimerState& previous,
                   uint32_t nowMs, LoadTimerReport& destination, save::Error& error) {
    try {
        if (!save::validate(d, error)) return false;
        if (d.header.isMap) return fail(error, save::ErrorCode::InvalidState, "Load timer requires a saved game");
        LoadTimerReport result;
        result.state = previous;
        for (int p = 0; p < d.options.numPlayers; ++p) if (d.players[size_t(p)].type) ++result.activePlayers;
        // The finished-player reader walks all seven slots, unlike the first.
        for (const auto& player : d.players) if (player.type && player.turnDone) ++result.finishedPlayers;
        if (d.options.autoTimer || (d.options.lastPlayerTimer && !result.state.running &&
            result.activePlayers - 1 == result.finishedPlayers)) {
            result.state = {true, nowMs, d.options.autoTimer ? d.options.autoTimerClock : d.options.lastPlayerClock};
            result.restarted = true;
        }
        destination = result; error = {}; return true;
    } catch (const std::bad_alloc&) {
        return fail(error, save::ErrorCode::Limit, "Insufficient memory validating timer load");
    } catch (const std::exception& e) {
        error = {save::ErrorCode::InvalidState, 0, e.what()}; return false;
    }
}
}
