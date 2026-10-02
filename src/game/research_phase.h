// Owned offline research resolution and technology acquisition/selection leaves.
#pragma once
#include "game/entity_creation.h"
#include <vector>

namespace dl2::simulation {
struct StealableTechnologyReport {
    int technology = 0; // Native0: no eligible technology OR eligible technology0.
    RngSnapshot rngAfter;
    RngEvent draw;
    bool operator==(const StealableTechnologyReport&) const = default;
};
struct TechnologyAcquisition {
    int player = -1, technology = 0;
    bool newlyKnown = false;
    int researchBefore = 0, researchAfter = 0;
    std::vector<uint32_t> removedFromLocalQueue;
    std::vector<int> newlyAvailable;
    std::vector<uint32_t> revealedShrines;
    bool operator==(const TechnologyAcquisition&) const = default;
};
struct ResearchPlayerChange {
    int slot = -1, playerIndex = -1, technology = 0;
    int32_t points = 0, required = 0;
    int16_t progressBefore = 0, progressAfter = 0;
    bool thresholdReached = false;
    bool operator==(const ResearchPlayerChange&) const = default;
};
struct ResearchMaterialChange {
    int player = -1;
    uint32_t territory = 0;
    int32_t before = 0, after = 0, amount = 0; // Electronic parts, material8.
    bool operator==(const ResearchMaterialChange&) const = default;
};
struct ResearchReport {
    std::vector<ResearchPlayerChange> players;
    std::vector<TechnologyAcquisition> acquisitions;
    std::vector<ResearchMaterialChange> excess;
    std::vector<AiAttitudeChange> attitudes;
    LoadedEventLog logAfter;
    AiReactionContext aiAfter;
    RngSnapshot rngAfter;
    std::vector<ConstructionOrderEvent> events;
    bool operator==(const ResearchReport&) const = default;
};
//0048514c: exactly one tagged range48 draw, then circular scan of ALL48
// signed16 known masks. No acquisition or availability/campaign filtering.
// Player arguments are bytes in the original; accept0..255 and use bit&31.
// False preserves destination and caller RNG; report owns the advanced stream.
bool chooseStealableTechnology(const save::Document& source,int thief,int victim,
    const RngSnapshot& rng,StealableTechnologyReport& report,save::Error& error);

//00483d58 and local queue00483bd4/00483b84/00483a30/0048424c. Tech0 is
// meaningful here, even though the steal selector also uses0 as its sentinel.
// Tech33 reveals shrine sites; known/available masks, full local research queue,
// selection/event57 and campaign/prerequisite availability are applied in native
// order. Both original feature-limit functions return10 for selector3; no fake
// callback or caller-chosen tech limit is installed. The fourth prerequisite
// WORD(+2a) is zero in all48 original PE rows (checked by optional tests).
// context.researchCampaignFlags supplies LIVE DAT0059f100 explicitly. Bit4
// disabled means no campaign restriction, even with a nonzero campaign number.
// Enabled bit4 requires an actual type4 goal; missing goal rejects the original
// out-of-object fourth-goal lookup rather than inferring or fabricating a goal.
// Already-known is an authentic evaluated early return. No automatic labor,
// entity allocation, research progress reset, final tech or turn completion.
bool acquireTechnology(const save::Document& source,int player,int technology,
    const ConstructionOrderContext& context,save::Document& destination,
    ResearchReport& report,save::Error& error);

//0046c7d4's player0..numPlayers-1 loop ->00484114. The actual input budget
// is signed Player.lastIncome(+40) accumulated by preceding production. Progress
// is indexed by signed Player.index, not necessarily the physical player slot.
// Progress updates even for technology0/budget0. Overflow recycling tech4,
// discovery54, treaty sharing56/acquisition and AI attitude0040526c are real.
// One log/AI/RNG continuation across players; source/destination may alias and
// all outputs roll back together on unsafe indices, callbacks or late failures.
// No AI turn, network sync, native presentation, turn counter or export claim.
bool processResearch(const save::Document& source,const ConstructionOrderContext& context,
    save::Document& destination,ResearchReport& report,save::Error& error);
} // namespace dl2::simulation
