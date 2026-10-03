// Owned offline unit lifecycle. Not manufacturing/payment or a combat phase.
#pragma once
#include "game/save_document.h"
#include <array>
#include <cstdint>
#include <optional>
#include <vector>

namespace dl2::simulation {
struct ArmyCreationContext {
    // Original transient DAT_004c5140, used by FindTransport's AI/job filter.
    // Zero explicitly means no moving unit. Offline authoritative, non-editor.
    uint32_t movingArmyId = 0;
};
struct ArmyCreationRequest { uint32_t territory = 0; int owner = -1, unitType = 0; };
enum class ArmyCreationReason { Allowed, MissileBaseMissing, CarrierUnavailable, SeaUnitOnLand, StackLimit, ReservedPoolSlot };
struct ArmyCreationQuery {
    ArmyCreationReason reason = ArmyCreationReason::Allowed;
    int stackGroup = 0, sameGroup = 0, limit = 0;
    uint32_t carrierId = 0;
    bool poolAvailable = false; // Separate from the original CanCreateUnit query.
    bool operator==(const ArmyCreationQuery&) const = default;
};
struct ArmyRefund {
    uint32_t armyId = 0, territory = 0;
    int owner = -1;
    int32_t credits = 0;
    std::array<int32_t, 10> materials{};
    int16_t populationBefore = 0, populationAfter = 0;
    bool populationReturned = false, laborBalanced = false;
    bool operator==(const ArmyRefund&) const = default;
};
struct ArmyLifecycleReport {
    uint32_t primaryId = 0, territory = 0;
    std::vector<uint32_t> createdIds, removedIds; // Actual allocation/deletion order.
    int32_t counterBefore = 0, counterAfter = 0;
    uint32_t carrierId = 0, pairedMissileId = 0;
    bool pairedMissileAttempted = false;
    ArmyCreationReason pairedMissileDenial = ArmyCreationReason::Allowed;
    std::vector<ArmyRefund> refunds;
    // Original DeleteUnit leaves MaintainUnit minister jobs for later dispatch.
    // Their unchanged records are counted, not silently removed as a callback.
    uint32_t deferredMaintainJobs = 0;
    bool operator==(const ArmyLifecycleReport&) const = default;
};
enum class ArmyRemovalKind { DeleteUnit, DisbandUnit };
struct ArmyRemovalRequest {
    uint32_t armyId = 0;
    ArmyRemovalKind kind = ArmyRemovalKind::DeleteUnit;
    // Explicit caller step, NOT an invented effect inside DeleteUnit. Applies
    // RemoveArmyFromTaskForce to each unit in the impending cascade. Otherwise
    // task forces retain their IDs and typed pool-cell bindings until0040aebc;
    // deletion never silently performs that later cleanup.
    bool detachTaskForces = false;
};

// 00445b94: missile-base, transport/terrain and own-list stacking query. A true
// return means valid query, not permission; inspect reason and poolAvailable.
bool canCreateArmy(const save::Document& source, uint32_t territory, int unitType,
                   const ArmyCreationContext& context, ArmyCreationQuery& destination,
                   save::Error& error);
// 00477724/00445d30: NextGlobalId, default record, prepend own/foreign list,
// transport attachment and siege35->missile36 pair. No editor/battle resolution.
// Preserves the original bare-cruiser success if its missile is denied by stack
// or pool capacity: report exposes attempt/denial, and the attempted child ID is
// consumed. Unsafe IDs/reference corruption or unimplemented effects roll back
// the ENTIRE call, never become a hidden successful partial operation.
bool createArmy(const save::Document& source, const ArmyCreationRequest& request,
                const ArmyCreationContext& context, save::Document& destination,
                ArmyLifecycleReport& report, save::Error& error);
// 00445fd4/00445800: reciprocal cargo detachment, carrier/siege cascades, owning
// list removal. Disband also ports 00445f08 half-cost refunds and colonizer
// population/local labor. Cargo casualties receive no extra disband refund.
// Does not simulate a battle, kill reward/event, AI turn or manufacturing order.
bool removeArmy(const save::Document& source, const ArmyRemovalRequest& request,
                save::Document& destination, ArmyLifecycleReport& report, save::Error& error);

enum class BuildingRemovalKind { DeleteBuilding, DemolishBuilding };
struct BuildingRemovalRequest {
    uint32_t buildingId = 0;
    BuildingRemovalKind kind = BuildingRemovalKind::DeleteBuilding;
    // Original Demolish caller supplies Player*. Explicit slot, not an inferred
    // territory owner. Ignored by DeleteBuilding, required 0..6 by Demolish.
    int refundPlayer = -1;
};
//0044b8f8 stores ten pairs of Player*/Territory* in0059f104..0059f153.
// Own typed references instead. Flush0044b9e4 reads the player's CURRENT signed
// Player.index; therefore retain its physical slot, not an index snapshot.
inline constexpr size_t kPendingShrineCapacity=10;
struct PendingShrineEntry {
    int playerSlot=-1;
    uint32_t territory=0;
    bool operator==(const PendingShrineEntry&) const = default;
};
struct PendingShrineState {
    std::vector<PendingShrineEntry> entries; // Ordered, duplicates are meaningful.
    bool operator==(const PendingShrineState&) const = default;
};
struct BuildingRemovalContext {
    uint32_t campaignFlags=0; // Live DAT0059f100, NOT inferred from campaign number.
    std::array<int32_t,3> campaignProgress{}; // Live mutable goal states, NOT SAV bytes.
    PendingShrineState pendingShrines;
    bool operator==(const BuildingRemovalContext&) const = default;
};
struct BuildingLifecycleReport {
    uint32_t primaryId = 0, territory = 0;
    int site = -1;
    std::vector<uint32_t> removedIds;
    int refundPlayer = -1;
    int32_t credits = 0;
    std::array<int32_t, 10> materials{};
    bool localLaborBalanced = false;
    // Demolish reads B.territory after FreeBuilding zeroes B: the original road
    // target is sentinel territory0, NOT the demolished territory. No local
    // road rebuild is fabricated; the unpersisted sentinel has no Document row.
    bool originalRoadsTargetWasSentinel = false;
    uint32_t deferredBuildJobs = 0;
    bool shrineFlagCleared=false, shrinePenaltyQueued=false, campaignProtected=false;
    // Present only with the explicit-context overload, even for non-shrines.
    std::optional<BuildingRemovalContext> contextAfter;
    bool operator==(const BuildingLifecycleReport&) const = default;
};
// 0044cd50/0044cc40: free footprint or restore platform socket, unlink record.
// Deleting a platform does NOT cascade to its SeaHab/other socket buildings.
// Demolish additionally refunds paid/canonical half costs and balances local
// labor. Shrine DEMOLISH requires explicit live context and this overload fails;
// bare DeleteBuilding can remove a shrine and deliberately leaves T.flags alone.
// Location-based minister3 jobs are preserved, counted for deferred dispatch.
bool removeBuilding(const save::Document& source, const BuildingRemovalRequest& request,
                    save::Document& destination, BuildingLifecycleReport& report, save::Error& error);
// Non-editor0044cefc shrine branch: clear T.flags bit0x10 BEFORE refund/delete;
// query00450320 using live flag12 and the FIRST canonical goal12's live state;
// append Player-slot/Territory to pending queue unless that state is nonzero.
// Missing goal12 with flag12 set or queue overflow would use unsafe native
// storage and is an explicit atomic error. Existing pending references must be
// valid; no inferred/normalized campaign progress. Goal query does NOT evaluate
// victory or modify progress. Penalties/events80/81/AI are deferred0044b9e4,
// NOT executed here; queue is neither cleared nor deduplicated by demolition.
bool removeBuilding(const save::Document& source, const BuildingRemovalRequest& request,
                    const BuildingRemovalContext& context, save::Document& destination,
                    BuildingLifecycleReport& report, save::Error& error);
// All mutations are candidate-copy transactions (source/destination may alias).
// Failure preserves document and report; success clears error. No globals, RNG,
// native callback/pointer activation or I/O. Intended for EntitiesEdited only.
} // namespace dl2::simulation
