// Read-only production queries, not execution of either production turn pass.
#pragma once
#include <array>
#include <cstdint>
#include <vector>
#include "game/save_document.h"

namespace dl2::simulation {

struct SlotProduction {
    uint8_t task = 0;
    int32_t labor = 0;
    int32_t output = 0;
    bool operator==(const SlotProduction&) const = default;
};
struct BuildingProduction {
    uint32_t buildingId = 0;
    uint8_t site = 0, type = 0, category = 0;
    bool active = false, built = false, evaluated = false;
    int32_t maxLabor = 0;
    std::array<SlotProduction, 5> assigned{}, maximum{};
    bool operator==(const BuildingProduction&) const = default;
};
struct TerritoryProduction {
    uint32_t territory = 0;
    int owner = -1;
    std::vector<BuildingProduction> buildings; // In original site order.
    bool operator==(const TerritoryProduction&) const = default;
};
struct ProductionPlan {
    std::vector<TerritoryProduction> territories; // Includes unowned territories.
    bool operator==(const ProductionPlan&) const = default;
};

// orig: FUN_0044eb4c (TaskOutputs), both assigned and maximum-output modes.
// All territories/buildings are represented. Unowned buildings are NOT evaluated
// (evaluated=false); their zero-initialized fields are not a production estimate.
// "maximum" assigns hypothetical labor independently to each default task; the
// five maxima do not represent a simultaneously feasible labor distribution.
// TaskOutputs has a confirmed uninitialized/carried labor read for task==0.
// Deliberate safe contract: its unused slots have labor/output=0, WITHOUT claiming
// parity with that original bug. Nonempty slots preserve integer arithmetic.
// Neither mode balances labor, consumes inputs, creates units, rolls art chance,
// applies resources, completes construction, or advances a turn. Active/Built
// flags are reported separately; TaskOutputs itself does not require Built.
// No state/global/RNG mutation. Failure preserves destination; success clears error.
bool planProduction(const save::Document& document, ProductionPlan& destination,
                    save::Error& error);

// orig: FUN_0044eeb4 (TaskOutput), a DIFFERENT query with explicit labor >= 0.
// Uses the assigned task, including shrine overrides. Unlike TaskOutputs, it
// omits the food/wood bonus at Territory+0x994. Its defined task==0 behavior is
// preserved: an active building with nonzero labor returns 1 (otherwise 0).
// Requires an owned building and slot 0..4. Failure leaves result unchanged.
bool taskOutput(const save::Document& document, uint32_t buildingId, int slot,
                int32_t labor, int32_t& result, save::Error& error);

// Execution leaves: same original assigned/scalar arithmetic, validating only
// the addressed producer/table accesses (plus archive structural validation).
// No hypothetical maxima or unrelated producers. Assigned task0 is explicitly
// zero because its original carried/uninitialized labor is not a valid oracle.
// Scalar task0 retains the defined active/nonzero-labor result1. Signed race
// offsets must stay inside RaceStats; technology shifts retain index&31.
bool assignedBuildingOutputs(const save::Document& document, uint32_t buildingId,
                             std::array<int32_t,5>& result, save::Error& error);
bool buildingTaskOutput(const save::Document& document, uint32_t buildingId, int slot,
                        int32_t labor, int32_t& result, save::Error& error);

} // namespace dl2::simulation
