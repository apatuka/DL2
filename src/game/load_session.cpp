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
            for (const auto& saved : d.events) {
                // The original lookup's spurious 157th row aliases "No Building".
                // ID 0x646c matches those bytes and would read invalid metadata.
                if (saved.record.type == 0x646c)
                    return fail(error, save::ErrorCode::InvalidState, "Event ID aliases the original out-of-table lookup; native replay is unsafe");
                if (std::find(saved.text.begin(), saved.text.end(), uint8_t(0)) != saved.text.end())
                    return fail(error, save::ErrorCode::InvalidState, "Native event replay excludes embedded NUL text; archival bytes remain supported");
                // next < base+0xbff, strict comparison including trailing NUL.
                if (saved.text.size() + 1 >= 3071u - result.poolBytes)
                    return fail(error, save::ErrorCode::Limit, "Native event replay would require unported pool eviction");
                result.poolBytes += uint32_t(saved.text.size() + 1);
                const auto& def = definition(saved.record.type);
                LoadedEvent event{saved.record.type, saved.record.player, saved.record.param,
                                  def.category, saved.text, {}};
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
                const auto index = uint32_t(result.entries.size());
                result.entries.push_back(std::move(event));
                const int tab = page(def.category);
                if (tab >= 0) result.pageIndices[size_t(tab)].push_back(index);
            }
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
