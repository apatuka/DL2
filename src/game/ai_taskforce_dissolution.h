// Owned dissolution of a live AI task force: FUN_0040beb4 with its link leaves
// 0040b000 (reparent a child to the owner's job0) and 0040afa4 (drop parent links).
// Operates on an explicit save::Document; never on gs/gg, RNG or native pointers.
#pragma once
#include "game/ai_session.h"
#include <cstdint>
#include <vector>

namespace dl2::simulation {
enum class TaskForceDissolutionAction : uint8_t {
    ArmyReleased,      // Army.job = 0; the dissolved slot keeps its ID until the final clear.
    ArmyTransferred,   // Canonical land: RemoveArmyFromTaskForce0040adf4, then 0040b0c0 into the parent.
    ChildReparented,   // 0040b000(job0, child): job0 link when a word is free, then child.parentJob = 1.
    ParentLinkCleared  // 0040afa4: one parent child word addressing the dissolved job became zero.
};
struct TaskForceDissolutionStep {
    TaskForceDissolutionAction action = TaskForceDissolutionAction::ArmyReleased;
    int slot = -1;                  // Army slot 0..15, or child word 0..14 (dissolved job / parent).
    uint32_t armyId = 0;            // CURRENT occupant; 0 for a nonnull cleared pool cell.
    uint32_t poolSlot = 0;          // Physical cell1..560; 0 without pool metadata / non-army action.
    int16_t armyJobBefore = 0, armyJobAfter = 0; // Army.job around an army action.
    // ArmyTransferred: reports of the reused public removeArmyFromTaskForce and
    // addArmyToTaskForce. insertion.outcome Full/AlreadyPresent means the army was
    // detached without a new insertion. AlreadyPresent keeps the parent's
    // existing binding even though Army.job may now be0.
    TaskForceEditReport removal, insertion;
    int jobIndex = -1;              // Zero-based child (ChildReparented) or parent (ParentLinkCleared).
    int32_t linkBefore = 0, linkAfter = 0; // child.parentJob, or the cleared parent child word.
    int rootSlot = -1;              // ChildReparented: job0 word written; -1 when its list was full.
    bool operator==(const TaskForceDissolutionStep&) const = default;
};
struct TaskForceDissolutionReport {
    int player = -1, jobIndex = -1; // Physical player array and zero-based dissolved job.
    int parentJobIndex = -1;        // Zero-based parent read BEFORE any effect; -1 without parent.
    // Exact original order: 16 army slots, 15 child words, parent words. A success
    // always ends with all 0xc4 bytes of the dissolved job zeroed (owner included).
    std::vector<TaskForceDissolutionStep> steps;
    bool operator==(const TaskForceDissolutionReport&) const = default;
};

// orig: FUN_0040beb4, FUN_0040b000, FUN_0040afa4 (no recovered names).
// With armyPool, jobSlots are authoritative: visit each nonnull physical cell,
// using its CURRENT occupant, never looking up the stale expected armyIds.
// A cleared cell stays nonnull and receives the original harmless job0 write
// (reported as ArmyReleased with armyId0). Null bindings are skipped even with
// expectedID!=0. Without metadata, validated archival IDs resolve the members.
// Historical Job.armies words are never pointers. All slots and links are read live,
// so effects on aliased records (job0, self links, repeated links) follow the
// original order. Without parent every army is released; with parent only
// CANONICAL unit domain1 (data::kUnitTypes[type], not saved Army.unitClass) is
// removed and offered to the parent, whose Full/AlreadyPresent result is kept.
// Child words are reparented to job0 even when job0's list is full; parent words
// matching the dissolved job are all cleared, then the whole job AND its pool
// bindings are zeroed. No implicit pool initialization or0040aebc cleanup.
// Domain: player0..6, jobIndex0..49. A record without parent, armies or children
// is cleared whatever its owner (0040ad88 recycling of free jobs). Otherwise
// Job.owner must equal player, the parent and child words must address1..50, and
// each visited LIVE occupant must have Army.owner == player. Foreign-owner
// reuse rejects atomically; it is not silently repaired or pruned. Cleared
// cells are explicitly supported without manufacturing live ID0 records.
// 0040b000 may only write owner-local links (job0/child owner == player).
// Any domain failure, even after earlier effects, retains source, destination
// and report; success publishes the candidate and clears error.
// source and destination may be the same object. No RNG, globals, AI decisions,
// messages, war/pact changes or entity deletion are implied.
bool dissolveTaskForce(const save::Document& source, int player, int jobIndex,
                       save::Document& destination, TaskForceDissolutionReport& report,
                       save::Error& error);
} // namespace dl2::simulation
