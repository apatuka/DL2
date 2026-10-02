// Owned economic logistics leaves, not an economic turn or implicit pipeline.
#pragma once
#include "game/entity_creation.h"
#include "game/resource_needs.h"

namespace dl2::simulation {
struct EconomicLogisticsReport {
    std::vector<MaterialCollectionReport> collections; // Original call order.
    ResourceCollectionState collectionAfter;
    LoadedEventLog logAfter;
    AiReactionContext aiAfter;
    RngSnapshot rngAfter;
    std::vector<ConstructionOrderEvent> events;
    bool operator==(const EconomicLogisticsReport&) const = default;
};

//00472974 with REAL ordered LogEventEx60 local/AI dispatch. Explicit payer may
// differ from territory owner. Carries suppliers/transfers/log/AI/RNG forward;
// neither clears reservations nor consumes the delivered local material.
// apply=false is the original quote leaf, not a full affordability check.
bool collectMaterial(const save::Document& source, const MaterialCollectionRequest& request,
    const ConstructionOrderContext& context, save::Document& destination,
    EconomicLogisticsReport& report, save::Error& error);

//00472bf0: material1..10, reset supplier ID+fee for1..N at each material,
// repeatedly visit territories1..N and attempt min(wrapped deficit,10).
// Repeat iff ANY native collection return is not -1 (not merely any delivery).
// Keeps partial transfers and dispatches every original60 in exact call order.
bool importDeficits(const save::Document& source, const ConstructionOrderContext& context,
    save::Document& destination, EconomicLogisticsReport& report, save::Error& error);

//0046b9a0: write signed16(foodNeed)/signed16(energyNeed), sign-extended, to
// Territory+0xa82/+0xa86. Preserve all other reservations and stock. The absent
// native territory0 sentinel is not added to an archival Document.
bool recordFoodEnergyNeeds(const save::Document& source, save::Document& destination,
    NeedsPlan& report, save::Error& error);

//00471b20 +00471bec ONLY: clear the250-entry transfer ledger and reservations
// Territory+0xa7e[11] for1..N. Supplier cache/fees, +0xaaa and all saved fields
// are preserved. Other0046c7d4 resets belong to the caller's explicit pipeline.
bool resetEconomicLogistics(const save::Document& source, const ResourceCollectionState& before,
    save::Document& destination, ResourceCollectionState& after, save::Error& error);

// All operations are transactional, allow source==destination, clear error on
// success, and preserve both outputs on false. No hidden predecessor phase,
// native globals, presentation callbacks, turn advance or partial SAV export.
} // namespace dl2::simulation
