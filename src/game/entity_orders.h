// Confirmed individual offline player orders, not presentation or turn flow.
#pragma once
#include "game/entity_lifecycle.h"
#include <array>

namespace dl2::simulation {
struct DisbandUnitOrderRequest { int actor=-1; uint32_t armyId=0; };
struct DemolishBuildingOrderRequest { int actor=-1; uint32_t buildingId=0; };
struct SeaManipulationChange {
    uint32_t territory=0;
    std::array<uint8_t,6> before{},after{}; // Territory +0x994..+0x999.
    bool operator==(const SeaManipulationChange&) const = default;
};
struct DemolishBuildingOrderReport {
    uint32_t requestedId=0,primaryId=0,territory=0;
    bool platformRedirected=false,seaFlagsRebuilt=false;
    std::vector<uint32_t> removedIds; // Physical retirement order, including sockets.
    std::vector<BuildingLifecycleReport> removals; // Refund/balance for EACH call.
    BuildingRemovalContext contextAfter;
    std::vector<SeaManipulationChange> seaChanges; // Changed territories, index order.
    bool operator==(const DemolishBuildingOrderReport&) const = default;
};

// orig: individual selected-unit branch00419924 -> offline00475854 ->00445f08.
// Request means the caller has ALREADY confirmed this one selected unit. This
// is not the keyboard/Alt multi-selection traversal or a simulated dialog.
// Native root-unit ownership gate is retained; current territory need NOT be
// actor-owned. Cargo casualties keep the native cascade/no-extra-refund rules.
// No task-force detach: the UI caller does not perform it. The lifecycle's
// explicit dangling-job safety rejection remains, with full rollback.
// Both commands additionally enforce actor==localPlayer, Player.type==1 and
// Player.index==actor as an explicit offline COMMAND policy, not new native
// leaf rules. Authority denial is an Error, not a successful empty operation.
bool orderDisbandUnit(const save::Document& source,const DisbandUnitOrderRequest& request,
                      save::Document& destination,ArmyLifecycleReport& report,save::Error& error);

// orig: confirmed individual0045b094, gate0045b304, offline00475a60.
// Requires native visibility[actor]==4 AND territory.owner==actor. The latter
// is a deliberate authority policy against stale visibility, not a claim that
// 0045b304 itself checks owner. Refund player is always the territory owner.
// SeaHab39 redirects to the FIRST stored-category20 platform, as0044d1a4 does;
// platform38 demolishes dynamically resolved sockets in order -22,-8,-12,+2,-10,
// then itself. Malformed/missing platform and unsafe footprints fail atomically.
// Every accepted single order rebuilds marine flags0046f0e0(0), including land
// demolitions: no RNG is consumed, but unrelated territories can change.
// Shrines enqueue their genuine delayed penalty using explicit live context;
// this order does NOT flush that queue or invoke AfterMove/UI/campaign victory.
// Not the separate 'demolish all' UI path (which skips shrines and does not
// rebuild these marine flags). No networking, editor, selection or dialogs.
// Source/destination may alias. Failure preserves both outputs and input;
// success clears error. No globals, RNG, native callbacks or I/O.
bool orderDemolishBuilding(const save::Document& source,const DemolishBuildingOrderRequest& request,
                          const BuildingRemovalContext& context,save::Document& destination,
                          DemolishBuildingOrderReport& report,save::Error& error);
} // namespace dl2::simulation
