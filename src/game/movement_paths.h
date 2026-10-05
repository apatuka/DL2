// Owned distance search00446b3c/00446b94. Does not move or create armies.
#pragma once
#include "game/entity_lifecycle.h"
#include <cstdint>
#include <optional>
#include <vector>

namespace dl2::simulation {
struct MovementPathRequest {
    uint32_t origin = 0; // SAV territory index1..N, never a native pointer.
    std::optional<uint32_t> target; // Absent:00446b3c; present:00446b94.
    int32_t range = 0;
    int domain = 1; // Original search argument1..6, not Army.unitClass.
    int player = -1;
    uint32_t markMask = 0;
    bool operator==(const MovementPathRequest&) const = default;
};
struct MovementPathContext {
    ArmyCreationContext creation; // movingArmyId, used by domain5 transport lookup.
    bool editorMode = false; //004d5aa0: bypass terrain, zero edge cost; pacts still apply.
    uint32_t sentinelFlags = 0; // Explicit flags of native territory0, absent from SAV.
    //004c5294 /00564218 are NOT reset by the wrappers. Values are signed32
    // scratch continuations, with native wrap on recursive increment/decrement.
    int32_t recursionDepth = 0;
    int32_t maximumRecursionDepth = 0;
};
struct MovementTerritoryPath {
    int16_t distance = 1000; // Native signed WORD at Territory+0xa70+player*2.
    uint32_t flags = 0;      // All other flag bits preserved.
    bool operator==(const MovementTerritoryPath&) const = default;
};
struct MovementPathReport {
    MovementPathRequest request;
    // Indexed by SAV territory index. Row0 is reset-only sentinel scratch,
    // with flags from context.sentinelFlags. It is NEVER a traversal target.
    // Unrepresented pool rows above N are not synthesized or traversed.
    std::vector<MovementTerritoryPath> territories;
    int32_t bestTargetDistance = 10000; //004c5290, even when no target supplied.
    int32_t recursionDepthAfter = 0;
    int32_t maximumRecursionDepthAfter = 0;
    uint32_t visitCount = 0; // Recursive entries, including the negative-range origin.
    bool operator==(const MovementPathReport&) const = default;
};

// orig:00446b08,00446b3c,00446b94,00446440,0045dfb0; queries004412d4,
//0044d1e4 and00445b94 (via hasAiPact/canCreateArmy).
// Domain: structurally valid full Document; origin/target1..N, player0..6,
// search domain1..6, and a resolving creation.movingArmyId when nonzero.
// A traversed adjacency to0 or above N fails atomically, never aliases row0.
// Range0 clears markMask and resets selected-player distances including row0,
// without entering DFS. A negative range enters origin but does not mark it;
// target==origin still sets bestTargetDistance0. The signed16 initial1000 is
// an actual strict-improvement bound: a large range cannot discover cost>=1000.
// DFS follows seven adjacency WORDs and their bits in ascending order, with
// strict improvements and native target pruning. No shortest-path reordering.
// Costs1/2/5/100, departure-owner/origin rules, own completed fuel depots,
// directional pacts and completed cities preserve their original order.
// Building CATEGORY is saved, completion means turnsLeft==0 (no Built/Active
// gate). Domain5 may board only from land into own sea with an available
// type12 transport; capacity and moving-army AI/job restrictions are reused.
// Pool availability is not permission and never gates this search.
// Offline authoritative semantics of ArmyCreationContext apply. Network-client
// exceptions, NextStep004467e8, movement, transport attachment, discovery,
// combat and turns are outside this query. No globals or RNG are accessed.
// Error leaves report unchanged; success publishes all scratch and clears error.
// Source is always unchanged, including flags and other players' distances.
bool findMovementPaths(const save::Document& source, const MovementPathRequest& request,
                       const MovementPathContext& context, MovementPathReport& report,
                       save::Error& error);
} // namespace dl2::simulation
