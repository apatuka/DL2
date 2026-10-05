// Owned0045727c crossing withdrawals, not battle setup or a complete turn.
#pragma once
#include "game/unit_movement.h"
#include "game/ai_session.h"
#include "game/load_session.h"
#include "game/entity_lifecycle.h"
#include <array>
#include <optional>

namespace dl2::simulation {
struct ArmyPowerRequest {
    uint32_t armyId=0;
    // Native args2..5. Nonzero predicates, not multipliers. Crossings pass0,0,0,0.
    // Fourth flag retains the original impossible domain2 && domain6 test.
    std::array<int32_t,4> flags{};
    bool operator==(const ArmyPowerRequest&) const = default;
};
struct ArmyPowerReport {
    int32_t defense=0,remainingDefense=0,accuracy=0,attack=0,rateOfFire=0,product=0,score=0;
    bool operator==(const ArmyPowerReport&) const = default;
};
// orig:00401108 (five args, RET14), wrappers00447b30/bc0/b0c/b9c.
// Independent projected-stat queries, wrap32 products, signed divisions and
// technology19/23. No score floor or post-bonus accuracy cap; no RNG/mutations.
bool scoreArmyPower(const save::Document&,const ArmyPowerRequest&,ArmyPowerReport&,save::Error&);

struct MovementCrossingsContext {
    UnitMovementContext movement;
    AiReactionContext ai;
    std::optional<LoadedEventLog> log; // Required only when152 reaches local.
    std::array<int32_t,kMaxPlayers> cities{};
    std::optional<BuildingRemovalContext> campaign; // Preserved live continuation.
    uint32_t maximumTraversalSteps=1000000; // Explicit guard, not a native iteration bound.
    bool operator==(const MovementCrossingsContext&) const = default;
};
struct MovementCrossingGroup {
    int32_t origin=0,player=0,power=0,count=0;
    bool operator==(const MovementCrossingGroup&) const = default;
};
struct MovementCrossingContribution {
    uint32_t territory=0,armyId=0;
    int group=-1; // All ten occupied: ignored, and score is NOT evaluated.
    std::optional<ArmyPowerReport> score;
    bool operator==(const MovementCrossingContribution&) const = default;
};
enum class MovementCrossingEventRoute { Ignored,LocalLog,AiReaction };
struct MovementCrossingEvent {
    int recipient=-1,winner=-1;
    uint16_t type=152;
    uint32_t from=0,retreatTo=0;
    MovementCrossingEventRoute route=MovementCrossingEventRoute::Ignored;
    std::optional<LocalEventReport> local;
    std::optional<AiReactionReport> reaction; // Logger152 extra1/extra2 BOTH0.
    bool operator==(const MovementCrossingEvent&) const = default;
};
struct MovementCrossingResolution {
    uint32_t territoryA=0,territoryB=0;
    int groupA=-1,groupB=-1;
    int32_t productA=0,productB=0;
    int loser=-1,winner=-1;
    uint32_t from=0,retreatTo=0;
    std::vector<UnitMovementReport> moves; // Native false still emits152 after loop.
    MovementCrossingEvent event;
    bool operator==(const MovementCrossingResolution&) const = default;
};
struct MovementCrossingsReport {
    MovementCrossingsContext contextAfter;
    // Original memset4600:112 rows INCLUDING unused0, ten16-byte groups each.
    std::array<std::array<MovementCrossingGroup,10>,kMaxTerritories> groups{};
    std::vector<MovementCrossingContribution> contributions;
    std::vector<MovementCrossingResolution> crossings;
    std::vector<RngEvent> draws; // Exact shared local/AI sequence, if any.
    uint32_t traversalSteps=0; // Live withdrawal visits, including skipped/revisited nodes.
    bool operator==(const MovementCrossingsReport&) const = default;
};
// orig:0045727c, filter0045723c. Snapshot only numTiles!=0 foreign lists;
// first matching/empty group, no11th. Nested territory/group order and signed
// wrap32(power*count) comparison; equal products withdraw the group in B.
// Walk each losing LIVE foreign list, capture next BEFORE moving each node,
// and re-resolve IDs after replacements. Transport can change a saved-next
// node's following link; never substitute a precomputed list of unit IDs.
// Event152 follows the whole losing-group traversal, even if no unit moved.
// Logger payload is not Ex: local slot payloads survive; AI gets0/0 extras.
// Caller owns movement scratch/movingArmyId, log, AI/RNG and campaign; no
// implicit movingArmyId substitution, list rebuild, RNG reseed or turn setup.
// Full saved Document, resolving acyclic lists/territories and offline host;
// Unsafe references or unavailable real callbacks fail atomically. Withdrawal
// visits beyond maximumTraversalSteps are an explicit atomic Limit error; a
// repeated node is NOT itself a cycle because transport can change its state.
// Source/context may alias destination/report; no globals/native UI callbacks.
bool resolveMovementCrossings(const save::Document& source,const AiSession& bindings,
    const MovementCrossingsContext& context,save::Document& destination,
    MovementCrossingsReport& report,save::Error& error);
} // namespace dl2::simulation
