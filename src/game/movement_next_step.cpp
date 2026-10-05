#include "game/movement_next_step.h"
#include "game/ai_pact_rules.h"
#include "game/ai_session.h"
#include "game/data_tables.h"
#include <bit>
#include <cstring>
#include <new>
#include <stdexcept>
#include <utility>

namespace dl2::simulation {
namespace {
bool fail(save::Error& error, const char* message, save::ErrorCode code = save::ErrorCode::InvalidState) {
    error = {code,0,message};
    return false;
}
int32_t defenseScratch(const Territory& territory) {
    int32_t value;
    std::memcpy(&value, reinterpret_cast<const uint8_t*>(&territory) + 0xa58, sizeof(value));
    return value;
}
struct Selection {
    const save::Document& source;
    const MovementNextStepRequest& request;
    const MovementNextStepContext& context;
    MovementNextStepReport result;
    save::Error& error;
    size_t nextTraceWord = 0;

    bool trace(size_t offset, uint32_t territory) {
        if (!result.traceAfter) return true;
        if (offset >= result.traceAfter->size())
            return fail(error,"Movement next-step trace exceeds the caller's explicit buffer capacity",save::ErrorCode::Limit);
        (*result.traceAfter)[offset] = territory;
        result.traceWrites.push_back({offset,territory});
        return true;
    }
    bool access(uint32_t territory, bool& allowed) {
        ArmyCreationQuery query;
        ++result.creationQueryCount;
        if (!canCreateArmy(source,territory,request.unitType,context.creation,query,error)) return false;
        allowed = query.reason == ArmyCreationReason::Allowed;
        return true;
    }
    bool scout(bool& allowed) {
        Army prospective{};
        prospective.type = uint8_t(request.unitType);
        prospective.owner = int8_t(request.player);
        ++result.scoutQueryCount;
        return canScoutOwned(source,prospective,allowed,error);
    }
    // orig: FUN_004467e8. The native ranking lives in a dword in assembly,
    // but only bits0..4 can be set; uint8_t preserves its complete value domain.
    bool run() {
        const uint32_t mark = 0x2000u << unsigned(request.player);
        for (auto& t : result.territoriesAfter) t.flags &= ~mark; //0045dfb0.
        result.startWithinRange = request.flag == 0 &&
            result.territoriesAfter[request.origin].distance <= request.range;
        uint32_t current = request.origin, chosen = 0;
        for (;;) {
            ++result.iterations;
            result.territoriesAfter[current].flags |= mark;
            const auto& from = source.territories[current-1].data;
            const int32_t currentDistance = result.territoriesAfter[current].distance;
            int32_t chosenDistance = currentDistance;
            uint8_t chosenRank = 0;
            chosen = 0;
            for (uint32_t group = 0; group < 7; ++group) {
                for (uint32_t bit = 0; bit < 16; ++bit) {
                    if (!(from.adjacency[group] & (uint32_t(1) << bit))) continue;
                    const uint32_t next = group * 16 + bit;
                    // Assembly004468d5..de explicitly compares against N.
                    if (next > source.territories.size()) continue;
                    if (!next) return fail(error,"Movement next-step adjacency reaches unrepresented sentinel0");
                    if (next == request.destination && result.startWithinRange) result.destinationAdjacent = true;
                    const auto& state = result.territoriesAfter[next];
                    if (next == request.destination || next == request.origin || (state.flags & mark) ||
                        (state.flags & 0x100u) || state.distance >= currentDistance) continue;
                    const auto& candidate = source.territories[next-1].data;
                    uint8_t ranking = state.distance == chosenDistance ? 1u : 0u;
                    if (state.distance < chosenDistance) ranking |= 2u;
                    bool allowed;
                    if (!access(next,allowed)) return false;
                    if (allowed) ranking |= 4u;
                    if (candidate.owner == -1 &&
                        (std::bit_cast<int8_t>(source.players[size_t(request.player)].type) < 3 ||
                         defenseScratch(candidate) == 0)) ranking |= 8u;
                    if (candidate.owner == request.player || hasAiPact(source,request.player,candidate.owner,2)) ranking |= 16u;
                    if (data::kUnitTypes[request.unitType].domain != 3) {
                        bool scoutAllowed;
                        if (!scout(scoutAllowed)) return false;
                        if (!scoutAllowed && ranking < 8) ranking = 0;
                    }
                    if (chosenRank < ranking) {
                        chosenDistance = state.distance;
                        chosen = next;
                        chosenRank = ranking;
                        ++result.rankingImprovements;
                        if (result.traceAfter && !trace(nextTraceWord++,next)) return false;
                    }
                }
            }
            result.finalRanking = chosenRank;
            if (chosen != request.destination && chosen != 0) {
                bool continueDescent = request.range < chosenDistance;
                if (!continueDescent) {
                    bool allowed;
                    if (!access(chosen,allowed)) return false;
                    continueDescent = !allowed;
                }
                // Even the origin-in-range branch performs the preceding
                // selected-node access query when its distance is within range.
                if (continueDescent && !result.startWithinRange) { current = chosen; continue; }
            }
            break;
        }
        if (result.startWithinRange) {
            result.nextTerritory = int32_t(std::bit_cast<int16_t>(source.territories[request.origin-1].data.index));
            if (result.traceAfter && (!trace(0,request.origin) ||
                !trace(1,result.destinationAdjacent ? request.destination : chosen) || !trace(2,0))) return false;
        } else if (!chosen) {
            result.nextTerritory = -1;
            if (!trace(0,0)) return false;
        } else {
            result.nextTerritory = int32_t(std::bit_cast<int16_t>(source.territories[chosen-1].data.index));
            if (!trace(nextTraceWord,0)) return false;
        }
        return true;
    }
};
} // namespace

// orig: FUN_004467e8 (NextStepTowards, descriptive legacy name).
bool selectMovementNextStep(const save::Document& source, const MovementNextStepRequest& request,
                            const MovementNextStepContext& context, MovementNextStepReport& report,
                            save::Error& error) try {
    if (!save::validate(source,error)) return false;
    if (source.header.isMap) return fail(error,"Movement next-step query requires a full saved-game document");
    if (!request.origin || request.origin > source.territories.size() ||
        !request.destination || request.destination > source.territories.size())
        return fail(error,"Movement next-step endpoints must address territories1..N");
    if (request.player < 0 || request.player >= kMaxPlayers || context.distancePlayer != request.player)
        return fail(error,"Movement next-step player must be0..6 and match the supplied distance column");
    if (request.unitType < 1 || request.unitType >= data::kNumUnitTypes)
        return fail(error,"Movement next-step unit type must be canonical1..38");
    if (context.territories.size() != source.territories.size()+1)
        return fail(error,"Movement next-step scratch must include exactly sentinel0 and territories1..N");
    if (context.creation.movingArmyId && !source.armyById(context.creation.movingArmyId))
        return fail(error,"Movement next-step moving-army context does not resolve");
    Selection selection{source,request,context,{},error};
    selection.result.territoriesAfter = context.territories;
    selection.result.traceAfter = context.traceBuffer;
    if (!selection.run()) return false;
    report = std::move(selection.result);
    error = {};
    return true;
} catch (const std::bad_alloc&) {
    return fail(error,"Movement next-step allocation failed",save::ErrorCode::Limit);
} catch (const std::length_error&) {
    return fail(error,"Movement next-step allocation exceeds limits",save::ErrorCode::Limit);
}
} // namespace dl2::simulation
