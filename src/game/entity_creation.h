// Completed-entity initialization, separate from paid construction orders.
#pragma once
#include "game/save_document.h"
#include "game/ai_session.h"
#include "game/construction_payment.h"
#include "game/entity_rules.h"
#include "game/load_session.h"
#include <cstdint>
#include <vector>

namespace dl2::simulation {
struct BuildingCreationRequest {
    uint32_t territory = 0;
    int buildingType = 0;
    int site = -1; // Explicit 0..35 only; no hidden FindConstructionSite RNG.
};
struct BuildingCreationReport {
    uint32_t buildingId = 0, territory = 0;
    int buildingType = 0, site = -1;
    int32_t counterBefore = 0, counterAfter = 0;
    std::vector<uint8_t> footprint;
    bool localLaborBalanced = false, siteRoadsRebuilt = false;
    std::vector<uint32_t> createdIds; // Allocation order: platform before SeaHab.
    uint32_t companionBuildingId = 0;
    bool companionAttempted = false, companionAllocationFailed = false;
    bool operator==(const BuildingCreationReport&) const = default;
};

// orig: NextGlobalId 00474cfc, InitBuilding 0044d890, CreateBuilding 0044dcf4,
// PlaceBuildingOnSite 0044d7b4, RedistributeLabor 0044c9a0, site roads 0047dfdc.
// Creates a FINISHED building with exact local labor/footprint/road effects.
// Supports land/sea, size1/2/5, platforms with their SeaHab, and shrines.
// Unowned nonracial types are supported; unowned racial initialization is not.
// Requires CheckConstructionSite==Allowed and an explicit vacant footprint as a
// deliberate safe-domain restriction (original explicit-site CreateBuilding
// bypasses that check). Rejects minister-managed local records/site jobs.
// Original increments the 32-bit counter once and truncates to u16. Here a
// zero/colliding ID fails transactionally; no search/skip to a free ID occurs.
// Capacity keeps the original pool's last reserved slot (1199 active maximum).
// Platform reserves the companion ID FIRST, then its own. If only one slot is
// available, original platform-only success is explicit in the report; both IDs
// are consumed. Other failures roll back the entire operation.
// No costs, payments, events, AI, automatic site, editor, transport, turn, tiles
// or deletion semantics. This is NOT StartConstruction or a completed order.
// Failure preserves source/destination/report; source and destination may alias.
// Success clears error. No globals, RNG, callbacks or filesystem access.
bool createCompletedBuilding(const save::Document& source, const BuildingCreationRequest& request,
                             save::Document& destination, BuildingCreationReport& report,
                             save::Error& error);

struct ConstructionOrderContext {
    ConstructionPaymentContext payment;
    LoadedEventLog log;
    EventLoadContext events; // CURRENT RNG/city counts, not the original load snapshot.
    AiReactionContext ai;
    const AiSession* aiSession = nullptr; // Borrowed; required only by nonlocal AI events.
};
enum class ConstructionOrderDenial { None, Placement, ReservedPoolSlot, Payment };
struct ConstructionOrderEvent {
    uint16_t type = 0;
    int recipient = -1;
    bool local = false, aiDispatched = false;
    LocalEventReport localReport;
    AiReactionReport aiReport;
    bool operator==(const ConstructionOrderEvent&) const = default;
};
struct ConstructionOrderReport {
    bool accepted = false;
    ConstructionOrderDenial denial = ConstructionOrderDenial::None;
    PlacementReason placementReason = PlacementReason::Allowed;
    uint32_t territory = 0, attemptedId = 0;
    std::vector<uint32_t> createdIds;
    int32_t counterBefore = 0, counterAfter = 0;
    bool paymentEvaluated = false, localLaborBalanced = false, siteRoadsRebuilt = false;
    uint16_t portTargetBefore = 0, portTargetAfter = 0;
    ConstructionPaymentReport payment;
    LoadedEventLog logAfter;
    AiReactionContext aiAfter;
    RngSnapshot rngAfter; // Authoritative shared stream, including last AI event.
    std::vector<ConstructionOrderEvent> events;
    bool operator==(const ConstructionOrderReport&) const = default;
};
// orig: offline0047597c -> StartConstruction0044db50, costs/payment004722e0,
// logger00423690/004237d0, local labor0044c9a0, roads0047dfdc, port0044da3c.
// True means EVALUATED: inspect accepted. Ordinary placement/pool/payment denial
// retains the original consumed ID and payment/search effects, and creates no
// entity. An unsafe ID/domain/callback/table failure returns false atomically.
// Successful building flags6 mean paid/active, NOT completed: work is retained.
// No work progression, SeaHab companion on platform start, hidden auto-site,
// editor, UI, turn or SAV-event serialization. Context is borrowed/unchanged;
// report owns the continuation log/AI/collection/RNG. Source may equal dest.
bool startConstruction(const save::Document& source, const BuildingCreationRequest& request,
                       const ConstructionOrderContext& context, save::Document& destination,
                       ConstructionOrderReport& report, save::Error& error);

struct ArmyTemplateRequest {
    uint32_t territory = 0;
    int owner = -1, unitType = 0;
    uint16_t id = 0;
};
// Pure record initializer from 00445d30/00447190/004a6b48. Does NOT allocate,
// increment IDs, check capacity/placement, link a list, attach cargo, pay, emit
// events or run CanCreateUnit. Special transport/siege and sea-land cargo
// branches are rejected; the result is explicitly a detached TEMPLATE.
// The ID must be unused globally, and owner/race/territory must be valid.
// Failure preserves destination; success clears error; input stays untouched.
// An output aliasing an existing input Army record is rejected explicitly.
bool initializeArmyTemplate(const save::Document& source, const ArmyTemplateRequest& request,
                            Army& destination, save::Error& error);
} // namespace dl2::simulation
