#include "game/ai_taskforce_dissolution.h"
#include "game/army_pool.h"
#include "game/data_tables.h"
#include <algorithm>
#include <bit>
#include <cstddef>
#include <cstring>
#include <exception>
#include <memory>
#include <new>
#include <stdexcept>
#include <utility>

namespace dl2::simulation {
namespace {
// Job+0x88..+0xc4: fifteen one-based child words (loops 1..0x10 exclusive).
constexpr size_t kChildWords = 15;
constexpr size_t kArmySlots = 16;
static_assert(offsetof(Job, unk_88) == 0x88 && sizeof(Job::unk_88) == kChildWords * sizeof(int32_t));
static_assert(sizeof(Job) * kJobsPerPlayer == 0x2648); // Player stride is exactly fifty jobs.

bool fail(save::Error& error, const char* message, save::ErrorCode code = save::ErrorCode::InvalidState) {
    error = {code, 0, message}; return false;
}
int32_t childWord(const Job& job, size_t k) {
    int32_t value;
    std::memcpy(&value, reinterpret_cast<const uint8_t*>(&job) + offsetof(Job, unk_88) + k * 4, 4);
    return value;
}
void childWord(Job& job, size_t k, int32_t value) {
    std::memcpy(reinterpret_cast<uint8_t*>(&job) + offsetof(Job, unk_88) + k * 4, &value, 4);
}
Army* findArmy(save::Document& d, uint32_t id) {
    const auto found = std::find_if(d.armies.begin(), d.armies.end(),
                                  [id](const Army& a) { return a.id == id; });
    return found == d.armies.end() ? nullptr : &*found;
}
// orig: FUN_0040afa4 compares owner*0x2648 + word*0xc4 (plus the table base) with
// the dissolved job's address in 32-bit arithmetic. As 0x2648 == 50*0xc4 and
// 0xc4 == 4*49, this is exactly equality of linear job indices modulo 2^30. Its
// non-null test is implied, the dissolved job's address is never null. No memory
// is read through the word, so arbitrary parent words are compared, not rejected.
bool addressesJob(int16_t owner, int32_t word, int player, int jobIndex) {
    const int64_t delta = int64_t(owner) * kJobsPerPlayer + word -
                          (int64_t(player) * kJobsPerPlayer + jobIndex + 1);
    return (uint64_t(delta) & ((uint64_t(1) << 30) - 1)) == 0;
}

// orig: FUN_0040beb4. All records are re-acquired after each public call:
// a successful edit replaces the candidate's storage.
bool dissolve(save::Document& d, int player, int jobIndex,
              TaskForceDissolutionReport& result, save::Error& error) {
    const size_t p = size_t(player), j = size_t(jobIndex);
    {
        const Job& job = d.jobs[p][j];
        bool references = job.parentJob != 0;
        if (d.armyPool) {
            for (const auto cell : d.armyPool->jobSlots[p][j]) references |= cell != 0;
        } else {
            for (const auto id : job.armyIds) references |= id != 0;
        }
        for (size_t k = 0; k < kChildWords; ++k) references |= childWord(job, k) != 0;
        // A free record is merely zeroed (0040ad88 recycles jobs whose owner word
        // is still zero). Any reference makes the original address through Job.owner.
        if (references && job.owner != player)
            return fail(error, "Dissolved task force owner differs from its physical player array");
        // The parent is resolved ONCE, before any effect: later child reparenting
        // may rewrite this job's own parentJob through a self link.
        if (job.parentJob != 0) {
            if (job.parentJob < 1 || job.parentJob > kJobsPerPlayer)
                return fail(error, "Dissolved task force parent index leaves its owner-local array");
            result.parentJobIndex = job.parentJob - 1;
        }
    }
    const bool hasParent = result.parentJobIndex >= 0;
    for (size_t slot = 0; slot < kArmySlots; ++slot) {
        // Read live: earlier removals/insertions may have edited this job.
        const uint32_t cell = d.armyPool ? d.armyPool->jobSlots[p][j][slot] : 0;
        const uint32_t id = d.armyPool ? (cell ? d.armyPool->liveIds[cell - 1] : 0)
                                      : d.jobs[p][j].armyIds[slot];
        if (d.armyPool ? !cell : !id) continue;
        TaskForceDissolutionStep step;
        step.slot = int(slot); step.armyId = id; step.poolSlot = cell;
        if (!id) {
            // DeleteArmy00445800 zeroes0x5c, then only writes free-list links
            // at+54/+58. A NONNULL cleared cell therefore has type0/job0.
            // Canonical type0 is not land:0040beb4 writes job0 again, without
            // unlinking the cell or altering the free-list. Do not fake an Army.
            if (hasParent && data::kUnitTypes[0].domain == 1)
                return fail(error, "Cleared pool cell unexpectedly has canonical land domain");
            step.action = TaskForceDissolutionAction::ArmyReleased;
            result.steps.push_back(std::move(step));
            continue;
        }
        Army* army = findArmy(d, id);
        if (!army)
            return fail(error, "Dissolved task force current army ID is unresolved");
        if (army->owner != player)
            return fail(error, "Dissolved task force army owner differs; its 0040aebc cleanup is deferred");
        step.armyJobBefore = army->job;
        bool land = false;
        if (hasParent) {
            // MOVSX type byte, MOVSX canonical domain byte (UnitDef+0x11), DEC/JNE:
            // the saved Army.unitClass is never consulted.
            const int type = std::bit_cast<int8_t>(army->type);
            if (type < 0 || type >= data::kNumUnitTypes)
                return fail(error, "Dissolved task force army type leaves the canonical unit table");
            land = data::kUnitTypes[type].domain == 1;
        }
        if (!land) {
            // Only Army.job is written; the slot itself stays until the final clear.
            army->job = 0;
            step.action = TaskForceDissolutionAction::ArmyReleased;
        } else {
            step.action = TaskForceDissolutionAction::ArmyTransferred;
            // RemoveArmyFromTaskForce0040adf4 follows Army.job, then 0040b0c0 may
            // return Full/AlreadyPresent: the detachment is NOT undone.
            if (!removeArmyFromTaskForce(d, id, step.removal, error) ||
                !addArmyToTaskForce(d, player, result.parentJobIndex, id, step.insertion, error))
                return false;
            army = findArmy(d, id);
            if (!army) return fail(error, "Transferred task force army disappeared from the candidate");
        }
        step.armyJobAfter = army->job;
        result.steps.push_back(std::move(step));
    }
    for (size_t k = 0; k < kChildWords; ++k) {
        // job0 may be the dissolved job itself: 0040b000 can fill words read later.
        const int32_t child = childWord(d.jobs[p][j], k);
        if (!child) continue;
        if (child < 1 || child > kJobsPerPlayer)
            return fail(error, "Dissolved task force child link leaves its owner-local array");
        Job& root = d.jobs[p][0];
        Job& target = d.jobs[p][size_t(child - 1)];
        TaskForceDissolutionStep step;
        step.action = TaskForceDissolutionAction::ChildReparented;
        step.slot = int(k); step.jobIndex = child - 1;
        // orig: FUN_0040b000(job0, child). The first free job0 word receives an
        // index derived from the CHILD's owner word; a full list skips it.
        for (size_t w = 0; w < kChildWords; ++w) {
            if (childWord(root, w)) continue;
            if (target.owner != player)
                return fail(error, "Reparented child owner would produce a cross-array job0 link");
            childWord(root, w, child); step.rootSlot = int(w);
            break;
        }
        // The child's parent is written unconditionally, from job0's owner word.
        if (root.owner != player)
            return fail(error, "Owner job0 word would produce a cross-array parent link");
        step.linkBefore = target.parentJob;
        target.parentJob = 1;
        step.linkAfter = target.parentJob;
        result.steps.push_back(std::move(step));
    }
    if (hasParent) {
        Job& parent = d.jobs[p][size_t(result.parentJobIndex)];
        for (size_t k = 0; k < kChildWords; ++k) {
            const int32_t word = childWord(parent, k);
            if (!word || !addressesJob(parent.owner, word, player, jobIndex)) continue;
            TaskForceDissolutionStep step;
            step.action = TaskForceDissolutionAction::ParentLinkCleared;
            step.slot = int(k); step.jobIndex = result.parentJobIndex;
            step.linkBefore = word; step.linkAfter = 0;
            childWord(parent, k, 0);
            result.steps.push_back(std::move(step));
        }
    }
    // memset(job, 0, 0xc4): owner is NOT restored.
    std::memset(&d.jobs[p][j], 0, sizeof(Job));
    if (d.armyPool) d.armyPool->jobSlots[p][j].fill(0);
    return true;
}
} // namespace

bool dissolveTaskForce(const save::Document& source, int player, int jobIndex,
                       save::Document& destination, TaskForceDissolutionReport& report,
                       save::Error& error) {
    try {
        if (!save::validate(source, error)) return false;
        if (source.header.isMap)
            return fail(error, "Task force dissolution requires a saved game, not a reduced map");
        if (player < 0 || player >= kMaxPlayers || jobIndex < 0 || jobIndex >= kJobsPerPlayer)
            return fail(error, "Task force dissolution player or zero-based job index is outside its array");
        // source may alias destination: only the private candidate is edited.
        auto candidate = std::make_unique<save::Document>(source);
        TaskForceDissolutionReport result;
        result.player = player; result.jobIndex = jobIndex;
        if (!dissolve(*candidate, player, jobIndex, result, error) || !save::validate(*candidate, error))
            return false;
        destination = std::move(*candidate); report = std::move(result); error = {}; return true;
    } catch (const std::bad_alloc&) {
        return fail(error, "Insufficient memory dissolving a task force", save::ErrorCode::Limit);
    } catch (const std::length_error&) {
        return fail(error, "Task force dissolution allocation exceeds limits", save::ErrorCode::Limit);
    } catch (const std::exception& e) {
        error = {save::ErrorCode::InvalidState, 0, e.what()}; return false;
    }
}
} // namespace dl2::simulation
