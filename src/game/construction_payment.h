// Original construction costs, affordability and material collection, owned.
#pragma once
#include "game/save_document.h"
#include <array>
#include <cstdint>
#include <vector>

namespace dl2::simulation {
struct ConstructionRequirements {
    int32_t labor = 0;
    std::array<int32_t, kNumMaterials> materials{}; // Money then materials1..10.
    int32_t technology = 0;
    bool operator==(const ConstructionRequirements&) const = default;
};
struct MaterialSupplier {
    uint32_t territory = 0; //0 null; an owned index, NEVER Territory+ad6 pointer.
    int16_t fee = 0; // Original signed short atTerritory+ada.
    bool operator==(const MaterialSupplier&) const = default;
};
struct MaterialTransfer {
    uint32_t from = 0, to = 0;
    int material = 0;
    int32_t amount = 0, credits = 0;
    bool operator==(const MaterialTransfer&) const = default;
};
struct ResourceCollectionState {
    std::array<MaterialSupplier, kMaxTerritories> suppliers{}; //1-based;0 sentinel.
    //00471b20 clears5000 bytes:250 records, not the legacy header's1000.
    std::vector<MaterialTransfer> transfers;
    bool operator==(const ResourceCollectionState&) const = default;
};
struct ConstructionPaymentContext {
    uint32_t selectedTerritory = 0; //00471e58 shortage diagnostics use UI selection!
    ResourceCollectionState collection;
};
struct MaterialImportFailure {
    uint16_t eventType = 0x3c;
    uint32_t territory = 0;
    int owner = -1, material = 0;
    bool operator==(const MaterialImportFailure&) const = default;
};
struct ConstructionPaymentReport {
    uint32_t territory = 0;
    int owner = -1;
    ConstructionRequirements requirements;
    int32_t transportQuote = 0, creditsBefore = 0, creditsAfter = 0;
    uint32_t failureMask = 0; //1credits, bits1..10 materials,1000tech,2000imports.
    bool affordabilityEvaluated = false;
    bool requirementsAccepted = false, collectionAttempted = false;
    std::array<int32_t, kNumMaterials> paid{}; // DELIVERED amounts, not remainder.
    ResourceCollectionState collection;
    std::vector<MaterialImportFailure> importFailures; //Semantic events, not SAV text.
    bool operator==(const ConstructionPaymentReport&) const = default;
};

struct MaterialCollectionRequest {
    uint32_t territory = 0;
    int player = -1, material = 0;
    int32_t amount = 0;
    bool apply = true;
    bool operator==(const MaterialCollectionRequest&) const = default;
};
struct MaterialCollectionReport {
    MaterialCollectionRequest request;
    int32_t remaining = 0, cost = 0, result = 0;
    ResourceCollectionState collection;
    std::vector<MaterialImportFailure> importFailures;
    bool operator==(const MaterialCollectionReport&) const = default;
};
struct SupplierSearchRequest {
    uint32_t territory = 0;
    int player = -1, material = 0, maximumMode = 0;
    bool operator==(const SupplierSearchRequest&) const = default;
};
struct SupplierSearchReport {
    bool found = false, stockExists = false;
    ResourceCollectionState collection;
    bool operator==(const SupplierSearchReport&) const = default;
};

//00472974 alone. Player is explicit: army food can be collected in foreign or
// unowned territory. No reservation/cache reset and no local-stock consumption.
// apply=false reserves donor stock and restores only cached supplier ID (not
// its fee); apply=true transfers stock/debits freight and reports semantic60.
// result is the native return: cost when remaining==0, otherwise -1, including
// amount<=0. Both output words are always written. Events are NOT dispatched by
// this low-level leaf; economic_logistics::collectMaterial provides that layer.
// No affordability quote, base-money charge, RNG/global use or native pointers.
// False preserves BOTH outputs even with aliased source/destination.
bool collectMaterialResources(const save::Document& source,
    const MaterialCollectionRequest& request, const ResourceCollectionState& before,
    save::Document& destination, MaterialCollectionReport& report, save::Error& error);

//00472844 alone: territory-order first affordable reachable donor, retaining
// search scratch and cached supplier exactly. No stock/credit debit or event.
// maximumMode0..3 is explicit (ConsumeFood uses3 even without technology46).
bool findMaterialSupplier(const save::Document& source,
    const SupplierSearchRequest& request, const ResourceCollectionState& before,
    save::Document& destination, SupplierSearchReport& report, save::Error& error);

//0044de9c/0044de48. Call BEFORE InitBuilding for City Center price scaling:
// original count uses Player.index, not necessarily its physical owner slot.
bool buildingConstructionRequirements(const save::Document& source,
    uint32_t territory, int buildingType, ConstructionRequirements& destination,
    save::Error& error);

//004722e0 ->00471e58/00472ca0 ->004720f4, full00472974 imports, supplier
// search00472844/00472578, fees00472730, metal substitution and transfer log.
// No construction object, placement, work progression, UI, AI, RNG or turn.
// True means faithfully evaluated, NOT approved: inspect failureMask. A denied
// quote may still change reservations/search scratch; a later collection failure
// may retain original partial payment. These are reported, not erased or hidden.
// Native supplier pointers are never read/written in Document; caller supplies
// and retains ResourceCollectionState. Quoting restores donorID but NOT its fee.
// A false return is an unsafe/unsupported domain/resource failure and preserves
// BOTH outputs, including source==destination. Success clears error.
bool payConstructionRequirements(const save::Document& source, uint32_t territory,
    const ConstructionRequirements& requirements, const ConstructionPaymentContext& context,
    save::Document& destination, ConstructionPaymentReport& report, save::Error& error);

//004720f4 ONLY, for already-started buildings and the partial-paid HEAD in
// ProduceUnits0044e174. Accumulates into paidBefore instead of clearing it.
// Does NOT quote affordability, check technology or charge base money: paid[0]
// is preserved verbatim, even when below requirements.materials[0]. The caller
// must perform any original direct credit-deficit debit BEFORE this operation.
// Freight can still debit credits, imports can fail/partially succeed, and all
// territory reservation scratch is reset as in the original collector.
// report.affordabilityEvaluated/requirementsAccepted stay false (not checked),
// collectionAttempted=true; failureMask only describes material collection.
// selectedTerritory and requirements.technology are not read by this leaf.
// Same transactional and owned-state guarantees as payConstructionRequirements.
bool collectConstructionRequirements(const save::Document& source, uint32_t territory,
    const ConstructionRequirements& requirements,
    const std::array<int32_t, kNumMaterials>& paidBefore,
    const ConstructionPaymentContext& context, save::Document& destination,
    ConstructionPaymentReport& report, save::Error& error);
} // namespace dl2::simulation
