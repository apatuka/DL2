#include "game/load_shrine_events.h"
#include "game/data_tables.h"
#include <algorithm>
#include <memory>
#include <new>
#include <stdexcept>
#include <string>
#include <utility>

namespace dl2::simulation {
namespace {
bool fail(save::Error& error, const char* message, save::ErrorCode code = save::ErrorCode::InvalidState) {
    error = {code,0,message}; return false;
}
int signedType(uint8_t value) { return value < 128 ? value : int(value) - 256; }
}
bool replayLoadShrineEvents(const save::Document& source,
    const LoadDerivedReport& derived, const AiSession& ai,
    const LoadedEventLog& previousLog, const RngSnapshot& rngBeforeNotices,
    const std::optional<AiReactionContext>& previousAi,
    save::Document& destination, LoadShrineEventsReport& report, save::Error& error) try {
    if (!save::validate(source,error)) return false;
    if (source.header.isMap) return fail(error,"Load shrine notices require a saved game");
    // At most six notices per live shrine; this bound also rejects hostile
    // in-memory reports before allocating/copying their delivery vector.
    if (derived.notices.size() > size_t(kMaxBuildings) * size_t(kMaxPlayers - 1))
        return fail(error,"Load shrine notices exceed the live-building/player bound",save::ErrorCode::Limit);
    SessionRng rng;
    if (!rng.restore(rngBeforeNotices,error)) return false;
    // Validate every address/context dependency before any candidate processing.
    for (const auto& notice : derived.notices) {
        const auto* territory = source.territoryByIndex(notice.territory);
        if (!territory || notice.recipient < 0 || notice.recipient >= kMaxPlayers ||
            notice.owner < 0 || notice.owner >= kMaxPlayers || notice.owner != territory->data.owner ||
            notice.recipient == notice.owner || (notice.eventCode != 0x4d && notice.eventCode != 0x4e))
            return fail(error,"Load shrine notice does not match a valid post-derived territory/recipient");
        if (notice.recipient != source.options.localPlayer && signedType(source.players[size_t(notice.recipient)].type) >= 3 && !previousAi)
            return fail(error,"Load shrine notice to AI requires the previous explicit relation-mask/message-queue context");
    }
    if (previousAi && previousAi->pendingMessages.size() > kAiMessageCapacity)
        return fail(error,"Load shrine AI message queue exceeds its original41-message capacity",save::ErrorCode::Limit);
    auto candidate = std::make_unique<save::Document>(source);
    LoadShrineEventsReport result;
    result.logAfter = previousLog; result.aiAfter = previousAi;
    result.rngAfter = rng.snapshot();
    if (result.aiAfter) result.aiAfter->rng = result.rngAfter;
    for (const auto& notice : derived.notices) {
        ShrineEventDelivery delivery{notice,ShrineEventRoute::Ignored,false};
        if (notice.recipient == candidate->options.localPlayer) {
            const int race = candidate->players[size_t(notice.owner)].race;
            if (race < 0 || race >= kMaxPlayers)
                return fail(error,"Local shrine notice owner race leaves its canonical name table");
            const auto& territory = candidate->territories[notice.territory - 1].data;
            const auto* end = std::find(std::begin(territory.name),std::end(territory.name),'\0');
            if (end == std::end(territory.name))
                return fail(error,"Local shrine notice territory name has no bounded NUL terminator");
            LocalEventRequest request;
            request.type = notice.eventCode;
            request.arguments = {std::string(data::kRaceNames[race]),std::string(std::begin(territory.name),end)};
            request.payload = EventPayload{notice.owner,0};
            LocalEventReport local;
            if (!logLocalEvent(*candidate,result.logAfter,{result.rngAfter,derived.cities},request,result.logAfter,local,error)) return false;
            result.rngAfter = local.rngAfter;
            result.draws.insert(result.draws.end(),local.randomDraws.begin(),local.randomDraws.end());
            delivery.route = ShrineEventRoute::LocalLog; delivery.stored = local.stored;
        } else if (signedType(candidate->players[size_t(notice.recipient)].type) >= 3) {
            result.aiAfter->rng = result.rngAfter;
            AiReactionReport reaction;
            if (!ai.reactEvent(*candidate,{notice.recipient,notice.eventCode,notice.owner,0},*result.aiAfter,*candidate,reaction,error)) return false;
            result.aiAfter = std::move(reaction.contextAfter); result.rngAfter = result.aiAfter->rng;
            result.draws.insert(result.draws.end(),reaction.draws.begin(),reaction.draws.end());
            delivery.route = ShrineEventRoute::AiReaction;
        }
        result.deliveries.push_back(delivery);
    }
    if (result.aiAfter) result.aiAfter->rng = result.rngAfter;
    // The nested log retains logLocalEvent's LAST-local-operation trace/RNG.
    // This report's draws/rngAfter cover the combined local+AI sequence.
    if (!save::validate(*candidate,error)) return false;
    destination = std::move(*candidate); report = std::move(result); error = {}; return true;
} catch (const std::bad_alloc&) {
    return fail(error,"Insufficient memory replaying load shrine notices",save::ErrorCode::Limit);
} catch (const std::length_error&) {
    return fail(error,"Load shrine notice allocation exceeds limits",save::ErrorCode::Limit);
}
} // namespace dl2::simulation
