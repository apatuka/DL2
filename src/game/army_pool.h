// Owned physical army-pool references, distinct from public lifetime handles.
#pragma once
#include "game/save_document.h"

namespace dl2::simulation {
// orig: LoadArmies004606f4 then RebuildArmyFreeList00445710. A fresh projection
// puts file-order records in cells1..N and pushes free cellsN+1..560 in order;
// back() is the original head560. Job IDs are resolved here exactly once;
// historical Job.armies words are never interpreted as native references.
// The caller validates the document first. Existing metadata is validated but
// NEVER reconstructed by ID: a native pointer survives retirement and reuse.
bool ensureArmyPool(save::Document& document,save::Error& error);

// The pool must be initialized BEFORE the caller inserts/removes a record.
// Allocate is called AFTER inserting exactly this new ID, and pops the native
// head only when at least two free cells remain (one reserved native cell).
// Retire is called BEFORE erasing the record; it clears the cell to id0/owner0
// and pushes it to the free head. It does not detach or clean any job binding.
// A completely full imported pool rejects retirement too: native DeleteArmy
// unconditionally dereferences the old free head, which would be null there.
// Successful retirement leaves a short-lived record/pool mismatch until the
// caller erases that record; the encompassing lifecycle owns the transaction.
// Each helper itself publishes metadata atomically and leaves records alone.
bool allocateArmyPoolSlot(save::Document& document,uint32_t id,save::Error& error);
bool retireArmyPoolSlot(save::Document& document,uint32_t id,save::Error& error);

// Checks metadata only, never recursively calls save::validate. Absent metadata
// is valid archival state. Present metadata must biject live IDs with records,
// partition all560 cells into live/free, and bound every nullable job cell.
// Expected job IDs/owners need NOT match the current occupant before cleanup.
bool validateArmyPool(const save::Document& document,save::Error& error);
// Additional encoding gate, called after full validation. Null bindings require
// expectedID0; nonnull bindings require a LIVE current occupant with matching
// ID16. Owner equality is not an archival rule. No raw words are rewritten.
bool validateArchivalArmyBindings(const save::Document& document,save::Error& error);
// Zero/null for absent metadata, invalid indices or cleared cells. taskForceTarget
// returns the CURRENT occupant, even if its ID/owner differs from the job's
// expectation or it belongs to a new lifetime. Never an expected-ID relookup.
uint32_t armyPoolSlot(const save::Document& document,uint32_t id);
const Army* taskForceTarget(const save::Document& document,int player,int jobIndex,int member);

enum class TaskForcePruneReason { IdMismatch,OwnerMismatch };
struct TaskForcePruneEntry {
    int player=-1,jobIndex=-1,member=-1;
    uint32_t poolSlot=0;
    uint16_t expectedId=0,observedId=0;
    int16_t expectedOwner=0;
    int8_t observedOwner=0;
    TaskForcePruneReason reason=TaskForcePruneReason::IdMismatch;
    bool operator==(const TaskForcePruneEntry&) const = default;
};
struct TaskForcePruneReport {
    std::vector<TaskForcePruneEntry> cleared; // Actual player/job/member traversal.
    bool operator==(const TaskForcePruneReport&) const = default;
};
// orig:0040aebc, confirmed assembly0040aed7..0040aef2. A NULL target is untouched
// even with expectedID!=0. A nonnull cleared cell exposes id0/owner0. Compare
// WORD IDs first, then signed BYTE Army.owner with signed WORD Job.owner. Clear
// both expected ID and target only on mismatch; never change Army.job. Neither
// type nor generation is checked: same-ID/same-owner reuse survives natively.
bool pruneTaskForceArmies(const save::Document& source,int player,int jobIndex,
                          save::Document& destination,TaskForcePruneReport& report,save::Error& error);
// orig:0040af0c, all50 jobs for one player in index order.
bool prunePlayerTaskForceArmies(const save::Document& source,int player,
                                save::Document& destination,TaskForcePruneReport& report,save::Error& error);
// orig:00460fa4's BEFORE-WRITE loop, player0..6/job0..49. This is only its
// cleanup leaf, not SaveGame, AI execution, scheduling, or permission to export.
bool pruneAllTaskForceArmies(const save::Document& source,save::Document& destination,
                             TaskForcePruneReport& report,save::Error& error);
// Pruning initializes missing pool metadata explicitly, then commits document
// and report together; source may equal destination. All errors are atomic;
// success resets Error. No globals, RNG, native pointers, callbacks or I/O.
} // namespace dl2::simulation
