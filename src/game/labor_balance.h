// Owned, transactional projection of task refresh and EndTurnBalance.
// This is an isolated preparation/economic operation, not a complete turn.
#pragma once
#include <array>
#include <cstdint>
#include <vector>
#include "game/save_document.h"

namespace dl2::simulation {

struct BuildingLaborState {
    uint16_t flags = 0;
    std::array<uint8_t, 5> tasks{};
    std::array<int32_t, 5> labor{};
    bool operator==(const BuildingLaborState&) const = default;
};
struct BuildingLaborChange {
    uint32_t buildingId = 0;
    uint32_t territory = 0;
    uint8_t site = 0;
    BuildingLaborState before, after;
    bool operator==(const BuildingLaborChange&) const = default;
};
struct TerritoryLaborBalance {
    uint32_t territory = 0;
    int32_t laborPool = 0, unavailableLabor = 0;
    int32_t assignedLabor = 0, unassignedLabor = 0;
    int8_t moraleBefore = 0, moraleAfter = 0;
    std::array<int32_t, 11> materialsBefore{}, materialsAfter{};
    bool operator==(const TerritoryLaborBalance&) const = default;
};
struct LaborBalancePlan {
    std::vector<BuildingLaborChange> buildings; // ALL buildings, in Document order.
    std::vector<TerritoryLaborBalance> territories; // ALL territories, indices 1..N.
    bool operator==(const LaborBalancePlan&) const = default;
};

// orig: GetBuildingTasks 0044e7ec, Refresh 0046c1f0, BalanceLabor 0044bea8,
// and EndTurnBalance 0046c780, including their labor/upgrade/queue dependencies.
// Refreshes tasks only in owned territories, in territory/site order. Then
// balances EVERY territory and caps materials[1..10] at 10000 (upper bound only;
// material[0] is untouched). The original empty territory-0 sentinel is absent
// from Document and has no saved objects to process.
// All operations occur on a temporary copy; input, globals, RNG and I/O are
// untouched. Success clears error; failure preserves the previous destination.
// No production/resources are generated, no turn increments, no objects added.
// Labor is signed throughout, including negative input and generated values.
// Rejects unsafe references/table domains and the original
// final-housing slot=-1 write. A resource guard rejects pathological transfer
// loops rather than hanging or claiming a partial success. Signed wrap/narrowing
// otherwise follows the original, including inactive-housing peculiarities.
bool planLaborBalance(const save::Document& document, LaborBalancePlan& destination,
                      save::Error& error);

} // namespace dl2::simulation
