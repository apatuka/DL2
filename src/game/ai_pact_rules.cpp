#include "game/ai_pact_rules.h"
#include <bit>
#include <cstring>
#include <exception>
#include <new>
#include <stdexcept>
#include <utility>

namespace dl2::simulation {
namespace {
bool fail(save::Error& error,const char* message,
          save::ErrorCode code = save::ErrorCode::InvalidState) {
    error = {code,0,message}; return false;
}
bool physicalPlayer(int player) { return player >= 0 && player < kMaxPlayers; }
bool validInput(const save::Document& source,int player,int other,save::Error& error) {
    if (!save::validate(source,error)) return false;
    if (source.header.isMap) return fail(error,"AI pact rules require a saved game, not a reduced map");
    if (!physicalPlayer(player) || !physicalPlayer(other))
        return fail(error,"AI pact player index leaves its seven-player array");
    return true;
}
template<class F> bool guarded(F&& operation,save::Error& error) {
    try { return operation(); }
    catch (const std::bad_alloc&) {
        return fail(error,"Insufficient memory evaluating AI pact rules",save::ErrorCode::Limit);
    } catch (const std::length_error&) {
        return fail(error,"AI pact diagnostic exceeds allocation limits",save::ErrorCode::Limit);
    } catch (const std::exception& exception) {
        error = {save::ErrorCode::InvalidState,0,exception.what()}; return false;
    }
}
int32_t attitude(const save::Document& source,int player,int other) {
    static_assert(sizeof(Job) == 7 * 7 * sizeof(int32_t));
    int32_t result;
    std::memcpy(&result,reinterpret_cast<const uint8_t*>(&source.scratchJob1) +
                        size_t(player * 7 + other) * sizeof(int32_t),sizeof(result));
    return result;
}
} // namespace

// orig: FUN_004412d4 / FUN_00441388.
bool hasAiPact(const save::Document& source,int player,int other,
               uint32_t required,bool second) noexcept {
    if (!source.options.allowAlliances || !physicalPlayer(player) || !physicalPlayer(other) ||
        player >= source.options.numPlayers || other >= source.options.numPlayers) return false;
    const auto& p = source.players[size_t(player)];
    const uint32_t bits = second ? p.relations2[other] : p.relations[other];
    return required == ((bits & 0x10u) ? (required & 0x1eu) : (bits & required));
}

// orig: FUN_00444274. Preserve the unusual strictly-greater logical bound.
int32_t aiVictoryMetric(const save::Document& source,int player,
                       const AiVictoryMetrics& metrics) noexcept {
    if (!physicalPlayer(player) || player > source.options.numPlayers ||
        source.players[size_t(player)].type == 0) return 0;
    switch (source.options.victory) {
    case 0: return metrics.cities[size_t(player)];
    case 1: return metrics.territories[size_t(player)];
    case 2: return metrics.shrines[size_t(player)];
    default: return 0;
    }
}

// orig: FUN_00406b1c. Assembly00406c2e..00406c3f: SHL/LEA/LEA,
// CDQ/IDIV50, ADD. Multiplication must wrap BEFORE signed division.
bool assessAiPact(const save::Document& source,const AiPactAssessmentRequest& request,
                  const AiVictoryMetrics& metrics,const RngSnapshot& initialRng,
                  AiPactAssessmentReport& report,save::Error& error) {
    return guarded([&] {
        if (!validInput(source,request.player,request.other,error)) return false;
        SessionRng rng;
        if (!rng.restore(initialRng,error)) return false;
        AiPactAssessmentReport result; result.rngAfter = initialRng;
        const int player = request.player,other = request.other;
        if (source.aiWarMask[size_t(player)] & (uint32_t(1) << uint32_t(other))) {
            result.warBlocked = true;
        } else {
            int32_t score = request.initiating ? 0 : 20;
            if (request.mask & 2u) score -= 20;
            if (request.mask & 8u) score -= 10;
            if (request.mask & 4u) score -= 10;
            if (request.mask & 16u) score -= 30;
            if (hasAiPact(source,player,other,1)) score += 10;
            if (hasAiPact(source,player,other,2)) score += 20;
            if (hasAiPact(source,player,other,8)) score += 10;
            if (hasAiPact(source,player,other,4)) score += 10;
            for (int p = 0; p < kMaxPlayers; ++p)
                if (source.players[size_t(p)].type != 0 && hasAiPact(source,player,p,16)) score -= 20;
            result.otherMetric = aiVictoryMetric(source,other,metrics);
            result.playerMetric = aiVictoryMetric(source,player,metrics);
            if (result.otherMetric > result.playerMetric) score += 10;
            else if (result.otherMetric < result.playerMetric) score -= 10;
            const int32_t product = std::bit_cast<int32_t>(uint32_t(attitude(source,player,other)) * 100u);
            result.threshold = std::bit_cast<int32_t>(uint32_t(score) + uint32_t(product / 50));
            RngEvent draw;
            if (!rng.apply({RngOperation::Secondary15,0,0,"AiPactWillingness00406b1c"},draw,error)) return false;
            result.accepted = int32_t(draw.value % 100u) < result.threshold;
            result.draws.push_back(std::move(draw)); result.rngAfter = rng.snapshot();
        }
        report = std::move(result); error = {}; return true;
    },error);
}

// orig: FUN_00406d10. This normalizes candidate bits, never stored treaties.
bool normalizeAiPactOffer(const save::Document& source,int player,int other,
                          uint32_t mask,uint32_t& output,save::Error& error) {
    return guarded([&] {
        if (!validInput(source,player,other,error)) return false;
        uint32_t candidate = mask;
        if (candidate & 16u) {
            for (int p = 0; p < kMaxPlayers; ++p)
                if (source.players[size_t(p)].type != 0 &&
                    (hasAiPact(source,player,p,16,true) || hasAiPact(source,other,p,16,true)))
                    candidate &= ~16u;
        }
        if (candidate & 16u) {
            if (!hasAiPact(source,player,other,2,true)) candidate |= 2u;
            if (!hasAiPact(source,player,other,8,true)) candidate |= 8u;
            if (!hasAiPact(source,player,other,4,true)) candidate |= 4u;
        }
        if ((candidate & 1u) && ((candidate & 2u) || hasAiPact(source,player,other,2,true)))
            candidate &= ~1u;
        output = candidate; error = {}; return true;
    },error);
}
} // namespace dl2::simulation
