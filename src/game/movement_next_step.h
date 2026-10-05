// Owned selection004467e8 over explicit signed-distance/flag scratch.
#pragma once
#include "game/movement_paths.h"
#include <cstddef>
#include <cstdint>
#include <optional>
#include <vector>

namespace dl2::simulation {
struct MovementNextStepRequest {
    // Native parameters1/2. The AI callers start descent at the desired goal
    // (origin here), with the army's turn-start territory as destination.
    // Destination is excluded from ranked candidates, not an arrival to select.
    uint32_t origin = 0, destination = 0;
    int player = -1;
    int32_t range = 0;
    int32_t flag = 0; // Native parameter5; zero enables the origin-in-range branch.
    int unitType = 0;
    bool operator==(const MovementNextStepRequest&) const = default;
};
struct MovementNextStepContext {
    int distancePlayer = -1; // Must equal request.player.
    // Index0..N, directly reusable from MovementPathReport.territories. Signed
    // negative distances are allowed. No distances are calculated or rewritten.
    std::vector<MovementTerritoryPath> territories;
    ArmyCreationContext creation;
    // nullopt = native param7==nullptr. Otherwise this is the exact writable
    // caller buffer, using owned territory indices (0=null), with explicit
    // capacity and previous contents. Values in untouched cells stay opaque.
    // Original AI callers reserve50 words; overflow is an atomic API error.
    std::optional<std::vector<uint32_t>> traceBuffer;
};
struct MovementNextStepTraceWrite {
    size_t offset = 0;
    uint32_t territory = 0;
    bool operator==(const MovementNextStepTraceWrite&) const = default;
};
struct MovementNextStepReport {
    int32_t nextTerritory = -1; // Native returned index or-1; false is an API error.
    std::vector<MovementTerritoryPath> territoriesAfter;
    std::optional<std::vector<uint32_t>> traceAfter;
    std::vector<MovementNextStepTraceWrite> traceWrites; // In exact native order.
    bool startWithinRange = false, destinationAdjacent = false;
    uint32_t iterations = 0, rankingImprovements = 0;
    uint32_t creationQueryCount = 0, scoutQueryCount = 0;
    uint8_t finalRanking = 0; // Bit ranking0..30, not a distance or path length.
    bool operator==(const MovementNextStepReport&) const = default;
};

// orig: FUN_004467e8; uses0045dfb0,00445b94,004412d4 and00416c28.
// Full saved-game Document, player0..6, unitType1..38, origin/destination1..N,
// and exactly N+1 scratch rows are required. A nonzero movingArmyId must resolve.
// The original explicitly ignores adjacency bits ABOVE N; bit0 is rejected
// when encountered because the document has no native sentinel metadata.
// Clears only mask0x2000<<player, then marks each current descent node. Excludes
// both endpoints from candidate ranking; candidates must be unmarked, not
// NoTiles, and strictly closer than the current node. Ranking distance bits
// compare against the CURRENT best candidate, not a fixed shortest distance.
// Equal ranks retain the first ascending adjacency. Saved player type is signed;
// neutral AI preference reads the actual int32 scratch at Territory+0xa58.
// canCreateArmy supplies access/stack/transport eligibility, independently of
// pool space. canScoutOwned supplies canonical scout/race54/technology43 rules.
// Offline authoritative, non-editor semantics of those owned queries apply.
//
// traceAfter is NOT a route: the native buffer stores every interim ranking
// improvement, may overwrite its first three words on origin-in-range success,
// or just word0 on failure; previously written tail words survive a terminator.
// traceWrites exposes those exact writes. A trace-capacity failure rolls back
// the whole query instead of reproducing native memory corruption.
// A successful API call may return nextTerritory==-1. Source, context, globals
// and RNG remain unchanged; only the report publishes scratch/writes. Errors
// retain the prior report; success clears error. No movement/turn is executed.
bool selectMovementNextStep(const save::Document& source, const MovementNextStepRequest& request,
                            const MovementNextStepContext& context, MovementNextStepReport& report,
                            save::Error& error);
} // namespace dl2::simulation
