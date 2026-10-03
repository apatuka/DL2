// Owned military upkeep and original bankruptcy/starvation disband substep.
#pragma once
#include "game/entity_creation.h"
#include "game/entity_lifecycle.h"
#include <array>
#include <cstdint>
#include <vector>

namespace dl2::simulation {
struct PlayerUpkeepChange {
    int player = -1;
    std::array<int32_t,4> unitCounts{}, groupCosts{}; // Troops,tanks,aircraft,ships.
    int32_t totalCost = 0, creditsBefore = 0, creditsAfter = 0;
    uint8_t flagsBefore = 0, flagsAfter = 0; // Player+09, not exclusively food flags.
    uint32_t selectedArmyId = 0;
    ArmyLifecycleReport disband;
    bool operator==(const PlayerUpkeepChange&) const = default;
};
struct EconomicUpkeepReport {
    std::vector<uint32_t> armyOrder; // Initial ascending unsigned16 global IDs.
    std::array<PlayerUpkeepChange,kMaxPlayers> players; // ALL7, even inactive.
    std::vector<uint32_t> retiredIds; // Physical removal order, including cargo.
    LoadedEventLog logAfter;
    AiReactionContext aiAfter;
    RngSnapshot rngAfter;
    std::vector<ConstructionOrderEvent> events;
    bool operator==(const EconomicUpkeepReport&) const = default;
};

// orig:0046b818 -> sort0046f89c/0046f85c ->0046b4d0/0046b3ac ->
//0046b3dc/SyncDisbandUnit00475898 ->DisbandUnit00445f08, OFFLINE.
// Canonical unit classes determine group counts. Per-group costs REPLACE the
// apparent sum of UnitDef.upkeep: RaceStats row60 times (n*n+max(n-20,0)^2)
// times {1,2,4,3}, wrapping at EACH32-bit operation before signed /100.
// Emits153..156 before debit; credit shortage sets flag1/warns once, repeated
// shortage sets flag4. Existing flag4 (e.g. ConsumeFood) also forces disband,
// even with enough credits. Clears4 AFTER the attempt, not before.
// Selects highest CANONICAL unit price, then lowest signed experience, then
// first ascending ID. One primary per player; cargo/paired casualties may add
// removals. Actual refunds/population/labor/list/cargo effects are executed.
// No invented task-force detachment: original caller has none. Deleted armies
// leave typed pool-cell bindings and unchanged job IDs for later0040aebc cleanup.
// Deferred MaintainUnit minister13 records remain, as in the original core.
// Uses explicit live event/AI/RNG context. Payment part of context is unused;
// this function does not reset logistics, consume food, fabricate a turn, or
// export a resumable SAV. False preserves both outputs, aliases supported.
bool processEconomicUpkeep(const save::Document& source,
                           const ConstructionOrderContext& context,
                           save::Document& destination, EconomicUpkeepReport& report,
                           save::Error& error);
} // namespace dl2::simulation
