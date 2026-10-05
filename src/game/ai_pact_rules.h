// Owned read-only pact rules. Live victory counters and RNG are explicit.
#pragma once
#include "game/session_rng.h"
#include <array>
#include <cstdint>
#include <vector>

namespace dl2::simulation {
struct AiVictoryMetrics {
    // Live00486964 counters, not PlayerScore or a fresh territory recount.
    std::array<int32_t,kMaxPlayers> cities{};      //0065e3cc
    std::array<int32_t,kMaxPlayers> territories{}; //0065e3b0
    std::array<int32_t,kMaxPlayers> shrines{};     //0065e3e8
    bool operator==(const AiVictoryMetrics&) const = default;
};
//004412d4 (primary) /00441388 (second): bit16 implies effective0x1e.
// Safe scalar queries: no document validation, mutation, RNG or callbacks.
// Disabled alliances and invalid logical/physical indices return false.
bool hasAiPact(const save::Document& source,int player,int other,
               uint32_t required,bool second = false) noexcept;
//00444274 accepts player==numPlayers, unlike the pact queries. A physical
// index outside0..6, inactive player or unsupported victory selector returns0.
int32_t aiVictoryMetric(const save::Document& source,int player,
                       const AiVictoryMetrics& metrics) noexcept;

struct AiPactAssessmentRequest {
    int player = -1,other = -1;
    uint32_t mask = 0;
    bool initiating = true; //00406b1c arg4: zero gives recipient bonus20.
};
struct AiPactAssessmentReport {
    bool accepted = false,warBlocked = false;
    int32_t threshold = 0,playerMetric = 0,otherMetric = 0;
    RngSnapshot rngAfter;
    std::vector<RngEvent> draws;
    bool operator==(const AiPactAssessmentReport&) const = default;
};
//00406b1c. Full signed32 multiplication then division, strict roll<threshold,
// one Secondary15 draw except the war early return. All outputs atomic;
// source and global RNG remain untouched. A valid empty RNG is acceptable
// only when war prevents the draw. No offer is sent or treaty enacted.
bool assessAiPact(const save::Document& source,const AiPactAssessmentRequest& request,
                  const AiVictoryMetrics& metrics,const RngSnapshot& initialRng,
                  AiPactAssessmentReport& report,save::Error& error);
//00406d10. Remove incompatible candidate bits, add missing alliance terms.
// Does not change either relation matrix. Unknown candidate bits survive.
bool normalizeAiPactOffer(const save::Document& source,int player,int other,
                          uint32_t mask,uint32_t& output,save::Error& error);
} // namespace dl2::simulation
