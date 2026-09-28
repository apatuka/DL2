// One reconstructed economy subphase, not a complete turn or game activation.
#pragma once
#include <array>
#include <cstdint>
#include <vector>

#include "game/save_document.h"

namespace dl2::simulation {

struct TerritoryTax {
    uint32_t territory = 0;
    int owner = -1;
    int32_t calculated = 0; // TerritoryTaxIncome before CollectTaxes narrows to s16.
    int16_t applied = 0;
};
struct TaxPlan {
    std::array<int32_t, kMaxPlayers> creditsBefore{};
    std::array<int32_t, kMaxPlayers> creditsAfter{};
    std::array<int32_t, kMaxPlayers> collected{};
    std::vector<TerritoryTax> territories; // Owned territories, ascending file index.
};

// orig: FUN_0046c728 (CollectTaxes), evaluated without changing the document.
// Uses saved race modifiers/local tax bytes, not assumed defaults. Unowned
// territories are skipped. IDs are resolved within the owning Document only.
// Failure preserves destination; success resets error. Does not change a turn,
// use RNG/callbacks, add events or activate original pointer/global state.
bool planTaxes(const save::Document& document, TaxPlan& destination, save::Error& error);

} // namespace dl2::simulation
