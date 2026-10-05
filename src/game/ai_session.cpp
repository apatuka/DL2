#include "game/ai_session.h"
#include "game/ai_event_transaction.h"
#include "game/ai_taskforce_dissolution.h"
#include "game/army_pool.h"
#include "game/data_tables.h"
#include "game/event_portraits.h"
#include <algorithm>
#include <bit>
#include <cstring>
#include <exception>
#include <memory>
#include <stdexcept>
#include <utility>

namespace dl2::simulation {
namespace {
bool fail(save::Error& error, const char* message,
          save::ErrorCode code = save::ErrorCode::InvalidState) {
    error = {code, 0, message}; return false;
}
bool gameDocument(const save::Document& d, save::Error& error) {
    if (!save::validate(d, error)) return false;
    return !d.header.isMap || fail(error, "AI session requires a saved game, not a reduced map");
}
constexpr std::array<AiBinding, 5> kMachiavelliBindings{
    AiBinding::InitializeMachiavelli, AiBinding::TurnMachiavelli,
    AiBinding::DiplomacyMachiavelli, AiBinding::VerifiedReturn, AiBinding::EventMachiavelli
};
// orig: AInit00401830 -> MachiavelliInit00408784 -> ConfigureMinisters0040233c.
// Player+46 contains the personality NAME; the five callbacks start at+4a.
// These native bindings never read/cast packed callback words from the save.
bool initializePlayer(AiSessionSnapshot& next, size_t p, save::Error& error) {
    auto& ai = next.data.ai[p];
    if (ai.initializations == UINT8_MAX)
        return fail(error, "AI initialization audit counter is exhausted", save::ErrorCode::Limit);
    const uint8_t count = uint8_t(ai.initializations + 1);
    const auto resetWord = ai.unknown53317c; // AInit does not write this ResetAI word.
    ai = {};
    ai.initialized = true; ai.initializations = count;
    ai.personality = LoadAiPersonality::Machiavelli;
    ai.strategyCountdown = 40; ai.unknown53317c = resetWord;
    next.personalityBindings[p] = kMachiavelliBindings;
    for (size_t m = 0; m < 6; ++m) {
        const auto config = data::kAiMinisterConfigDefault[m];
        if (config.kind < 0 || config.kind >= 6 || config.param < 0 || config.param > UINT8_MAX)
            return fail(error, "AI session canonical minister configuration is invalid");
        auto& minister = ai.ministers[m];
        minister.role = Minister(m); minister.kind = uint8_t(config.kind);
        minister.parameter = uint8_t(config.param);
        next.ministerBindings[p][m].fill(AiBinding::VerifiedReturn);
    }
    return true;
}
Army* findArmy(save::Document& d, uint32_t id) {
    if (!id || id > UINT16_MAX) return nullptr;
    const auto found = std::find_if(d.armies.begin(), d.armies.end(),
                                  [id](const Army& a) { return a.id == id; });
    return found == d.armies.end() ? nullptr : &*found;
}
// orig:0040ab54 and RemoveArmyFromTaskForce0040adf4 compare Army POINTERS,
// not the separately saved IDs. Once physical pool metadata exists, an old
// binding observes that cell's current occupant even after retirement/reuse.
// Without metadata, validated archival IDs are the initial loaded resolution.
int taskForceMember(const save::Document& d, size_t player, size_t job, uint16_t id) {
    if (d.armyPool) {
        const uint32_t physical = armyPoolSlot(d, id);
        if (!physical) return -1;
        const auto& slots = d.armyPool->jobSlots[player][job];
        const auto found = std::find(slots.begin(), slots.end(), physical);
        return found == slots.end() ? -1 : int(found - slots.begin());
    }
    const auto& ids = d.jobs[player][job].armyIds;
    const auto found = std::find(std::begin(ids), std::end(ids), id);
    return found == std::end(ids) ? -1 : int(found - std::begin(ids));
}
// orig:0040b0c0 tests the pointer array for NULL. A cleared physical cell is
// still nonnull; conversely a null binding is free even with a stale saved ID.
int freeTaskForceMember(const save::Document& d, size_t player, size_t job) {
    if (d.armyPool) {
        const auto& slots = d.armyPool->jobSlots[player][job];
        const auto found = std::find(slots.begin(), slots.end(), uint32_t(0));
        return found == slots.end() ? -1 : int(found - slots.begin());
    }
    const auto& ids = d.jobs[player][job].armyIds;
    const auto found = std::find(std::begin(ids), std::end(ids), uint16_t(0));
    return found == std::end(ids) ? -1 : int(found - std::begin(ids));
}
// orig: RemoveArmyFromTaskForce0040adf4. Archival Job.armies words are inert.
// Each successful recursion sets Army.job=0 before visiting cargo, so cycles
// terminate. The original missing-match DebugMessage is an explicit error here.
bool detach(save::Document& d, Army& army, TaskForceEditReport& report,
            save::Error& error, size_t depth = 0) {
    if (!army.job) return true;
    if (depth > d.armies.size())
        return fail(error, "Task force cargo recursion exceeds the owned army count", save::ErrorCode::Limit);
    if (army.owner < 0 || army.owner >= kMaxPlayers || army.job < 1 || army.job > kJobsPerPlayer)
        return fail(error, "Task force owner or one-based Army.job is outside its array");
    const size_t player = size_t(army.owner), jobIndex = size_t(army.job - 1);
    auto& job = d.jobs[player][jobIndex];
    const int member = taskForceMember(d, player, jobIndex, army.id);
    if (member < 0)
        return fail(error, "Army.job has no matching army binding in its owner-local task force");
    const size_t slot = size_t(member);
    job.armyIds[slot] = 0; job.armies[slot].raw = 0;
    if (d.armyPool) d.armyPool->jobSlots[player][jobIndex][slot] = 0;
    army.job = 0;
    report.detachedArmyIds.push_back(army.id);
    // TYPE 12 only, NOT every carrier class. Empty slots1/2 fall back to slot0;
    // this apparent redundancy exists in the original and is kept verbatim.
    if (army.type == 12) for (size_t c = 0; c < 3; ++c) {
        const uint32_t id = army.cargo[c].raw ? army.cargo[c].raw : army.cargo[0].raw;
        if (id) {
            auto* cargo = findArmy(d, id);
            if (!cargo) return fail(error, "Task force cargo ID is unresolved");
            if (!detach(d, *cargo, report, error, depth + 1)) return false;
        }
    }
    return true;
}
template<class Action> bool transaction(save::Document& d, TaskForceEditReport& report,
                                        save::Error& error, Action action) {
    try {
        if (!gameDocument(d, error)) return false;
        auto next = std::make_unique<save::Document>(d);
        TaskForceEditReport result;
        if (!action(*next, result) || !save::validate(*next, error)) return false;
        // Preserve identity/address as well as bytes for original early returns.
        if (result.outcome != TaskForceOutcome::AlreadyDetached &&
            result.outcome != TaskForceOutcome::AlreadyPresent && result.outcome != TaskForceOutcome::Full)
            d = std::move(*next);
        report = std::move(result); error = {}; return true;
    } catch (const std::bad_alloc&) {
        return fail(error, "Insufficient memory maintaining a task force", save::ErrorCode::Limit);
    } catch (const std::length_error&) {
        return fail(error, "Task force allocation exceeds limits", save::ErrorCode::Limit);
    } catch (const std::exception& e) {
        error = {save::ErrorCode::InvalidState, 0, e.what()}; return false;
    }
}
} // namespace

bool AiSession::initializeAfterLoad(const save::Document& d, save::Error& error) {
    try {
        if (!gameDocument(d, error)) return false;
        AiSessionSnapshot next;
        next.data.localPlayer = next.data.hostPlayer = d.options.localPlayer;
        for (size_t p = 0; p < kMaxPlayers; ++p) {
            const int type = d.players[p].type < 128 ? d.players[p].type : int(d.players[p].type) - 256;
            if (int(p) == d.options.localPlayer) {
                if (type != 1) return fail(error, "AI session requires final offline local-human normalization");
            } else if (type == 1 || type == 2) {
                return fail(error, "AI session requires nonlocal human-to-AI load conversion first");
            }
            if (type > 3) return fail(error, "AI session does not support this personality selector");
            if (type == 3 && !initializePlayer(next, p, error)) return false;
        }
        next.data.initialized = true; next.initializationComplete = true; next.diplomacyImplemented = true;
        state_ = std::move(next); error = {}; return true;
    } catch (const std::bad_alloc&) {
        return fail(error, "Insufficient memory initializing AI", save::ErrorCode::Limit);
    } catch (const std::exception& e) {
        error = {save::ErrorCode::InvalidState, 0, e.what()}; return false;
    }
}

bool AiSession::dispatch(const AiRequest& request, AiDispatchReport& report, save::Error& error) {
    try {
        if (!state_.initializationComplete || request.player < 0 || request.player >= kMaxPlayers ||
            !state_.data.ai[size_t(request.player)].initialized)
            return fail(error, "AI dispatch requires an initialized owned personality");
        auto next = state_; AiDispatchReport result;
        const size_t p = size_t(request.player);
        switch (request.operation) {
        case AiOperation::Initialize:
            if (!initializePlayer(next, p, error)) return false;
            result.invocations.push_back({AiBinding::InitializeMachiavelli, -1, -1, data::kAiType3.fn[0].addr});
            break;
        case AiOperation::MinisterPhase:
            if (request.phase < 0 || request.phase >= 4)
                return fail(error, "AI minister phase must be zero through three");
            // Every target in the six canonical four-entry vtables is precisely
            // 55 8b ec 5d c2 08 00 (prologue, epilogue, RET8) in DEADLOCK.EXE.
            // They have no gameplay effects. This is NOT a fallback for any of
            // the substantial Machiavelli turn/event/diplomacy entry points.
            for (const int slot : data::kMinisterOrder) {
                if (slot < 0 || slot >= 6) return fail(error, "AI minister execution order is invalid");
                const auto& minister = next.data.ai[p].ministers[size_t(slot)];
                if (minister.kind >= 6 || next.ministerBindings[p][size_t(slot)][size_t(request.phase)] != AiBinding::VerifiedReturn)
                    return fail(error, "AI minister callback is not an implemented canonical binding");
                result.invocations.push_back({AiBinding::VerifiedReturn, slot, request.phase,
                    data::kMinisterVtable[minister.kind].fn[request.phase].addr});
            }
            break;
        case AiOperation::Turn:
            return fail(error, "Machiavelli turn00408a88 gameplay dependencies are not implemented");
        case AiOperation::Diplomacy:
            return fail(error, "Diplomacy requires explicit request, document, RNG, relation mask and message queue");
        case AiOperation::Event:
            return fail(error, "AI event requires explicit payload, document, RNG, relation mask and message queue");
        default: return fail(error, "Unknown AI operation");
        }
        result.stateChanged = next != state_;
        state_ = std::move(next); report = std::move(result); error = {}; return true;
    } catch (const std::bad_alloc&) {
        return fail(error, "Insufficient memory dispatching AI", save::ErrorCode::Limit);
    } catch (const std::exception& e) {
        error = {save::ErrorCode::InvalidState, 0, e.what()}; return false;
    }
}

bool removeArmyFromTaskForce(save::Document& d, uint32_t armyId,
                             TaskForceEditReport& report, save::Error& error) {
    return transaction(d, report, error, [&](save::Document& next, TaskForceEditReport& result) {
        auto* army = findArmy(next, armyId);
        if (!army) return fail(error, "Task force removal army ID is unresolved");
        result.armyId = armyId; result.player = army->owner;
        if (!army->job) return true;
        result.jobIndex = int(army->job) - 1;
        if (army->owner >= 0 && army->owner < kMaxPlayers && army->job >= 1 && army->job <= kJobsPerPlayer) {
            result.slot = taskForceMember(next, size_t(army->owner), size_t(army->job - 1), army->id);
        }
        if (!detach(next, *army, result, error)) return false;
        result.outcome = TaskForceOutcome::Removed; return true;
    });
}

bool addArmyToTaskForce(save::Document& d, int player, int jobIndex, uint32_t armyId,
                        TaskForceEditReport& report, save::Error& error) {
    return transaction(d, report, error, [&](save::Document& next, TaskForceEditReport& result) {
        if (player < 0 || player >= kMaxPlayers || jobIndex < 0 || jobIndex >= kJobsPerPlayer)
            return fail(error, "Task force target player or job index is outside its array");
        auto* army = findArmy(next, armyId);
        if (!army) return fail(error, "Task force insertion army ID is unresolved");
        auto& job = next.jobs[size_t(player)][size_t(jobIndex)];
        result.armyId = armyId; result.player = player; result.jobIndex = jobIndex;
        const int present = taskForceMember(next, size_t(player), size_t(jobIndex), army->id);
        if (present >= 0) {
            result.slot = present; result.outcome = TaskForceOutcome::AlreadyPresent; return true;
        }
        const int free = freeTaskForceMember(next, size_t(player), size_t(jobIndex));
        if (free < 0) { result.outcome = TaskForceOutcome::Full; return true; }
        // Explicit safe domain: original address subtraction uses Job.owner;
        // Remove subsequently selects Army.owner. Different owners would create
        // a binding that cannot be maintained safely in an owner-local array.
        if (job.owner != player || army->owner != player)
            return fail(error, "Task force insertion requires matching job, army and target owners");
        result.slot = free;
        if (!detach(next, *army, result, error)) return false;
        job.armyIds[result.slot] = army->id; job.armies[result.slot].raw = 0;
        if (next.armyPool)
            next.armyPool->jobSlots[size_t(player)][size_t(jobIndex)][size_t(result.slot)] = armyPoolSlot(next, army->id);
        army->job = int16_t(jobIndex + 1); result.outcome = TaskForceOutcome::Added; return true;
    });
}

bool canScoutOwned(const save::Document& d, const Army& army, bool& result, save::Error& error) {
    try {
        if (!gameDocument(d, error)) return false;
        if (army.owner < 0 || army.owner >= kMaxPlayers || army.type >= data::kNumUnitTypes)
            return fail(error, "Scout query owner or signed unit-type table address is invalid");
        bool value = army.type == 24 || army.type == 11;
        if (!value) {
            const auto cls = data::kUnitTypes[army.type].unitClass;
            const int word = 54 * 7 + int(d.players[size_t(army.owner)].race);
            if (word < 0 || size_t(word) >= sizeof(RaceStats) / sizeof(int16_t))
                return fail(error, "Scout query signed race address leaves the saved RaceStats block");
            int16_t modifier;
            std::memcpy(&modifier, reinterpret_cast<const uint8_t*>(&d.raceStats) + size_t(word) * 2, 2);
            value = modifier != 0 && (cls == 1 || cls == 11);
            // Original MOVSX knownMask, shift by owner&31. Owners0..6 make
            // low-bit membership identical without relying on signed shifts.
            value |= (d.techs[43].knownMask & (uint32_t(1) << uint32_t(army.owner))) != 0 &&
                     (army.type == 12 || cls == 1 || cls == 11);
        }
        result = value; error = {}; return true;
    } catch (const std::bad_alloc&) {
        return fail(error, "Insufficient memory validating scout query", save::ErrorCode::Limit);
    } catch (const std::exception& e) {
        error = {save::ErrorCode::InvalidState, 0, e.what()}; return false;
    }
}

bool pruneInvalidMaintainUnitJobs(save::Document& d, MaintainUnitPruneReport& report, save::Error& error) {
    try {
        if (!gameDocument(d, error)) return false;
        auto next = std::make_unique<save::Document>(d); MaintainUnitPruneReport result;
        for (size_t p = 0; p < kMaxPlayers; ++p) {
            auto& jobs = next->ministerJobs[p];
            for (size_t i = 1; i < jobs.size();) {
                const auto& job = jobs[i];
                if (job.type == 13 && job.param[0] == 0)
                    return fail(error, "Maintain-unit target ID0 depends on legacy free-pool lookup, not an owned live entity");
                // FindArmyByGlobalID0047510c compares FULL u32 to zero-extended
                // ID16; no narrowing of MinisterJob.param[0] is appropriate.
                const auto* army = next->armyById(uint32_t(job.param[0]));
                if (job.type != 13 || (army && army->owner == int(p))) { ++i; continue; }
                // Owned adjacency replaces native pointers. Historical words
                // are spliced as opaque payload, never resolved or fabricated.
                const auto removed = job;
                jobs[i - 1].next = removed.next;
                if (i + 1 < jobs.size()) jobs[i + 1].prev = removed.prev;
                jobs.erase(jobs.begin() + std::ptrdiff_t(i)); ++result.removed[p];
            }
        }
        if (!save::validate(*next, error)) return false;
        if (std::any_of(result.removed.begin(), result.removed.end(), [](uint32_t count) { return count != 0; }))
            d = std::move(*next);
        report = result; error = {}; return true;
    } catch (const std::bad_alloc&) {
        return fail(error, "Insufficient memory pruning deferred maintain-unit jobs", save::ErrorCode::Limit);
    } catch (const std::length_error&) {
        return fail(error, "Maintain-unit job allocation exceeds limits", save::ErrorCode::Limit);
    } catch (const std::exception& e) {
        error = {save::ErrorCode::InvalidState, 0, e.what()}; return false;
    }
}

namespace {
// Canonical original DATA at004b5684,004b55d0,004b560c,004b5648,004b56c0.
// All three attitude bands contain the same probabilities in this executable.
constexpr int32_t kResponseWeights[5][5]{
    {100,0,0,0,0}, {0,100,0,0,0}, {50,0,0,0,50},
    {50,0,0,0,50}, {0,0,80,0,20}
};
// DATA004ca3b4+category*56+race*8;004504a4 consumes a draw even when
// the message will subsequently be dropped by queue filtering/capacity.
constexpr uint32_t kChatVariantCounts[5][7]{
    {26,26,26,26,26,26,27}, {24,28,26,25,24,27,26},
    {27,26,26,26,27,26,25}, {23,23,24,24,23,24,23},
    {20,20,20,20,20,20,20}
};
// DATA004b57c0:43 campaign rows of3 {race,otherRace,initialAttitude,locked}.
// Only the locked predicate is used here; the initial values are not reapplied
// over loaded attitude matrices. Keeping all four words makes PE verification
// possible without hiding the -1 wildcard-like UNUSED rows (only7 is wildcard).
constexpr int32_t kCampaignAttitudes[43][12]{
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {1,0,-20,1,2,0,0,0,5,0,-20,1}, {1,0,-20,1,6,1,-50,0,4,0,-50,0},
    {1,0,-20,1,-1,-1,-1,-1,-1,-1,-1,-1}, {1,0,-50,1,5,0,-50,1,1,5,-50,1},
    {1,3,-20,1,3,0,8,1,5,3,-20,1}, {7,7,-20,1,-1,-1,-1,-1,-1,-1,-1,-1},
    {0,2,20,0,2,0,20,0,5,1,8,0}, {0,6,20,1,6,0,20,1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, {3,1,0,0,4,2,20,0,2,4,20,0},
    {3,5,50,0,5,3,50,0,-1,-1,-1,-1}, {7,7,-20,1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, {0,2,20,0,5,1,-20,1,-1,-1,-1,-1},
    {3,6,8,0,6,3,8,0,-1,-1,-1,-1}, {0,2,-50,1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, {7,7,-20,1,-1,-1,-1,-1,-1,-1,-1,-1},
    {1,3,-20,0,-1,-1,-1,-1,-1,-1,-1,-1}, {2,3,0,0,-1,-1,-1,-1,-1,-1,-1,-1},
    {4,3,8,0,7,7,-20,1,-1,-1,-1,-1}, {1,5,20,0,5,1,20,0,6,3,8,0},
    {0,3,-50,0,5,3,-50,0,-1,-1,-1,-1}, {7,7,-20,1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, {1,4,-20,0,6,4,-20,0,-1,-1,-1,-1},
    {2,4,-50,0,5,4,-50,0,-1,-1,-1,-1}, {2,4,-20,0,5,2,8,0,2,5,8,0},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, {7,7,-20,1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, {0,5,-20,1,0,2,20,0,2,0,20,0},
    {0,5,-20,1,-1,-1,-1,-1,-1,-1,-1,-1}, {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, {7,7,-20,1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, {4,6,-20,1,-1,-1,-1,-1,-1,-1,-1,-1},
    {2,3,20,0,3,2,20,1,-1,-1,-1,-1}, {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {2,6,-50,1,5,6,-50,1,-1,-1,-1,-1}, {7,7,-20,1,-1,-1,-1,-1,-1,-1,-1,-1}
};
static_assert(sizeof(Job) == 7 * 7 * sizeof(int32_t));
int32_t attitude(const Job& block, int p, int other) {
    int32_t value; std::memcpy(&value, reinterpret_cast<const uint8_t*>(&block) + size_t(p * 7 + other) * 4, 4); return value;
}
void attitude(Job& block, int p, int other, int32_t value) {
    std::memcpy(reinterpret_cast<uint8_t*>(&block) + size_t(p * 7 + other) * 4, &value, 4);
}
int signedType(const Player& p) { return p.type < 128 ? p.type : int(p.type) - 256; }
int32_t wrapAdd(int32_t a, int32_t b) { return std::bit_cast<int32_t>(uint32_t(a) + uint32_t(b)); }
struct ReactionWork {
    save::Document& d; AiReactionReport& result; SessionRng& rng; save::Error& error;
    const AiSessionSnapshot* bindings = nullptr;
    ai_event_detail::ReplayState* replay = nullptr;
    unsigned eventDepth = 0;
    bool player(int p) { return (p >= 0 && p < kMaxPlayers) || fail(error, "AI reaction player index leaves its seven-player array"); }
    bool draw(uint32_t& value, const char* tag) {
        RngEvent event;
        if (!rng.apply({RngOperation::Secondary15,0,0,tag}, event, error)) return false;
        value = event.value; result.draws.push_back(std::move(event)); return true;
    }
    bool change(int p, int other, int32_t delta) {
        if (!player(p) || !player(other)) return false;
        AiAttitudeChange change{p,other,attitude(d.scratchJob1,p,other),0,attitude(d.scratchJob2,p,other),0,false};
        change.after = change.before; change.baselineAfter = change.baselineBefore;
        bool locked = d.options.playerSkill[p] == 4;
        //004051c4 checks skill before touching campaign selectors/races.
        if (!locked && d.options.campaign) {
            if (d.options.campaign < 0 || d.options.campaign >= 43)
                return fail(error, "AI reaction campaign selector leaves its43-row attitude table");
            const auto& rules = kCampaignAttitudes[d.options.campaign];
            for (int i = 0; i < 3; ++i)
                if ((rules[i*4] == 7 || rules[i*4] == d.players[size_t(p)].race) &&
                    (rules[i*4+1] == 7 || rules[i*4+1] == d.players[size_t(other)].race) && rules[i*4+3]) locked = true;
        }
        const uint32_t bit = uint32_t(1) << uint32_t(other);
        if (!locked && !(result.contextAfter.relationChangeMask[size_t(p)] & bit)) {
            //0040526c: wrapping signed32 additions, clamp[-50,50], baseline
            // gets delta/2 truncated toward zero (SAR plus odd-negative fix).
            change.after = std::clamp(wrapAdd(change.before,delta),-50,50);
            change.baselineAfter = std::clamp(wrapAdd(change.baselineBefore,delta/2),-50,50);
            attitude(d.scratchJob1,p,other,change.after); attitude(d.scratchJob2,p,other,change.baselineAfter);
            result.contextAfter.relationChangeMask[size_t(p)] |= bit; change.applied = true;
        }
        result.attitudes.push_back(change); return true;
    }
    void enqueue(const AiDiplomacyMessage& message) {
        bool human = false;
        for (int p = 0; p < kMaxPlayers; ++p)
            if ((message.recipients & (uint32_t(1) << uint32_t(p))) &&
                signedType(d.players[size_t(p)]) != 0 && signedType(d.players[size_t(p)]) < 3) human = true;
        AiMessageOutcome outcome = AiMessageOutcome::Queued;
        if (signedType(d.players[size_t(message.sender)]) > 2 && !human) outcome = AiMessageOutcome::NoHumanRecipient;
        else if (result.contextAfter.pendingMessages.size() == kAiMessageCapacity) outcome = AiMessageOutcome::Full;
        else result.contextAfter.pendingMessages.push_back(message);
        // For category-1, original offline004776b8->MasterDispatch0x10 only
        // acknowledges. The human-facing semantic request remains in this FIFO.
        result.messages.push_back({message,outcome});
    }
    bool chat(int p, int other, int category) {
        if (!player(other)) return false;
        const int race = d.players[size_t(p)].race;
        if (race < 0 || race >= 7 || category < 31 || category > 35)
            return fail(error, "AI chat variant selector leaves its canonical race/category table");
        uint32_t variant;
        if (!draw(variant,"AiChatVariant004504a4")) return false;
        variant %= kChatVariantCounts[category - 31][race];
        enqueue({p,uint32_t(1) << uint32_t(other),category,int(variant),{}}); return true;
    }
    bool pact(int p, int other, uint32_t required, bool second = false) {
        if (!d.options.allowAlliances || p < 0 || p >= d.options.numPlayers || other < 0 || other >= d.options.numPlayers) return false;
        const uint32_t bits = second ? d.players[size_t(p)].relations2[other] : d.players[size_t(p)].relations[other];
        return required == ((bits & 0x10u) ? (required & 0x1eu) : (bits & required));
    }
    bool negotiationState() {
        return result.contextAfter.negotiation.has_value() ||
            fail(error,"AI negotiation needs explicit live cooldowns, offer states, masks and victory metrics");
    }
    bool assess(int p, int other, uint32_t mask, bool initiating, bool& accepted) {
        if (!negotiationState()) return false;
        AiPactAssessmentReport assessment;
        if (!assessAiPact(d,{p,other,mask,initiating},result.contextAfter.negotiation->victory,
                          rng.snapshot(),assessment,error)) return false;
        if (!rng.restore(assessment.rngAfter,error)) return false;
        result.draws.insert(result.draws.end(),assessment.draws.begin(),assessment.draws.end());
        accepted=assessment.accepted; return true;
    }
    //004237d0 keeps the two explicit callback arguments, unlike00423690.
    // Both pact leaves notify third-party AI slots only; no human log is forged.
    bool notifyPact(int eventType, int p, int other) {
        for (int recipient=0;recipient<kMaxPlayers;++recipient) {
            if (recipient==p || recipient==other || signedType(d.players[size_t(recipient)])<=2) continue;
            if (d.players[size_t(recipient)].type!=3)
                return fail(error,"Pact notification requires an unimplemented AI personality");
            if (!bindings || !bindings->data.ai[size_t(recipient)].initialized ||
                bindings->personalityBindings[size_t(recipient)][4]!=AiBinding::EventMachiavelli)
                return fail(error,"Pact notification requires an initialized owned event binding");
            result.pactEvents.push_back({recipient,eventType,p,other});
            if (!event({recipient,eventType,p,other})) return false;
        }
        return true;
    }
    //004415d0: all four masks are cleared before any synchronous AI callback.
    bool clearPublicPact(int p,int other,uint32_t mask) {
        d.players[size_t(p)].relations[other]&=~mask;
        d.players[size_t(other)].relations[p]&=~mask;
        d.players[size_t(p)].relations2[other]&=~mask;
        d.players[size_t(other)].relations2[p]&=~mask;
        return notifyPact(0x73,p,other);
    }
    //004071b0 ->00476aac/e4 -> offline handlers00476970/00476a70.
    bool breakPacts(int p,int other) {
        const uint32_t requested=d.players[size_t(p)].relations[other];
        if (!requested) return true;
        const int32_t threshold=std::bit_cast<int32_t>(uint32_t(attitude(d.scratchJob1,p,other))*uint32_t(-100))/50;
        uint32_t chance; if (!draw(chance,"AiBreakPactChoice004071b0")) return false;
        const bool secret=int32_t(chance%100)<threshold;
        const uint32_t mask=uint16_t(requested); //004779c0 message payload
        result.pacts.push_back({p,other,secret?AiPactAction::SecretBreak:AiPactAction::PublicBreak,
                                requested,mask,d.options.allowAlliances!=0});
        // A rejected native ACK is ignored by these wrappers: war still starts.
        if (!d.options.allowAlliances) return true;
        if (secret) { d.players[size_t(p)].relations[other]&=~mask; return true; }
        if (!clearPublicPact(p,other,mask)) return false;
        if (signedType(d.players[size_t(other)])>=3) {
            int delta=0;
            if (mask&2u) delta=-20;
            if (mask&8u) delta-=8;
            if (mask&4u) delta-=8;
            if (mask&16u) delta-=20;
            return change(other,p,delta); //00407248 with multiply flag0
        }
        if (other==d.options.localPlayer) {
            const int race=d.players[size_t(p)].race;
            const auto portraits=data::eventPortraitNames(race,20);
            if (race<0 || race>=7 || mask>=32 || portraits.empty())
                return fail(error,"Pact-break portrait leaves its verified race/category domain");
            uint32_t selected; if (!draw(selected,"AiBreakPactPortrait004503f4")) return false;
            result.pactNotices.push_back({p,other,mask,std::string(portraits[selected%portraits.size()])});
        }
        return true;
    }
    //00441700 via the uint16 offline wire payload. Reentrant events can change
    // the same masks before the outer call resumes; always read the live copy.
    bool makePact(int p,int other,uint32_t requested) {
        const uint32_t mask=uint16_t(requested);
        result.pacts.push_back({p,other,AiPactAction::Make,requested,mask,d.options.allowAlliances!=0});
        if (!d.options.allowAlliances) return true;
        if ((p==d.options.localPlayer || other==d.options.localPlayer) && (mask==2 || mask==16)) {
            if (!replay || !replay->campaign)
                return fail(error,"Human pact acceptance requires explicit live campaign objective state");
            //0044fe1c(1) precedes0044fdf0/0044fe58. Do not reconstruct these
            // mutable int32 progress words from the three archival SAV bytes.
            if (replay->campaign->campaignFlags&2u) {
                const int campaign=d.options.campaign;
                if (campaign<0 || campaign>=data::kNumCampaigns)
                    return fail(error,"Pact campaign objective indexes outside its canonical table");
                size_t slot=0;
                while (slot<3 && data::kCampaigns[campaign].goals[slot].type!=1) ++slot;
                if (slot==3)
                    return fail(error,"Live campaign flag1 has no canonical goal1 (original out-of-row write)");
                replay->campaign->campaignProgress[slot]=1;
            }
        }
        if ((mask&1u) && !clearPublicPact(p,other,2)) return false;
        if ((mask&2u) && !clearPublicPact(p,other,1)) return false;
        d.players[size_t(p)].relations[other]|=mask;
        d.players[size_t(other)].relations[p]|=mask;
        d.players[size_t(p)].relations2[other]|=mask;
        d.players[size_t(other)].relations2[p]|=mask;
        return notifyPact(0x72,p,other);
    }
    //00406c64: a previously seen offer returns without a draw or attitude edit.
    bool respondToOffer(int p,int other,uint32_t mask,bool& accepted) {
        auto& live=*result.contextAfter.negotiation;
        accepted=false; const uint32_t bit=uint32_t(1)<<uint32_t(p);
        if (live.processedOfferMask[size_t(other)]&bit) return true;
        if (signedType(d.players[size_t(other)])>2 && attitude(d.scratchJob1,other,p)>=0 &&
            !(d.aiWarMask[size_t(other)]&bit) && !assess(other,p,mask,false,accepted)) return false;
        uint32_t chance=0;
        if (!accepted && !draw(chance,"AiOfferRejectionAttitude00406c64")) return false;
        if ((accepted || !(chance&1u)) && !change(other,p,4)) return false;
        live.processedOfferMask[size_t(other)]|=bit;
        return true;
    }
    //00476b8c -> successful dialog0042d0ac ->004503f4(category15).
    // Only the explicit transaction enables suspension/recorded decisions.
    // Presentation allocation failures/network arrivals are outside this
    // offline successful-presentation profile; no missing UI implies refusal.
    bool humanOffer(int p,int other,uint32_t mask,bool& accepted) {
        if (!replay)
            return fail(error,"AI pact offer requires a real human response; pending negotiation is not answered implicitly");
        if (other!=d.options.localPlayer || d.players[size_t(other)].type!=1)
            return fail(error,"Human pact continuation requires the normalized local human recipient");
        if (replay->consumed>=ai_event_detail::kMaxHumanResponses)
            return fail(error,"AI event human response transcript exceeds its supported limit",save::ErrorCode::Limit);
        const int race=d.players[size_t(p)].race;
        const auto names=data::eventPortraitNames(race,15);
        if (race<0 || race>=7 || names.empty())
            return fail(error,"Human pact offer portrait leaves its canonical race/category domain");
        uint32_t selected;
        if (!draw(selected,"AiHumanOfferPortrait0042d0ac")) return false;
        AiHumanOffer offer;
        offer.transactionId=replay->transactionId; offer.ordinal=uint32_t(replay->consumed+1);
        offer.player=p; offer.recipient=other; offer.mask=uint16_t(mask);
        offer.portrait=std::string(names[selected%names.size()]);
        offer.checkpoint=result.contextAfter; offer.checkpoint.rng=rng.snapshot();
        offer.campaignCheckpoint=replay->campaign;
        if (replay->consumed==replay->responses.size()) {
            replay->pending=std::move(offer); return false;
        }
        const auto& response=replay->responses[replay->consumed];
        if (response.offer!=offer ||
            (response.answer!=AiHumanAnswer::Accept && response.answer!=AiHumanAnswer::Reject))
            return fail(error,"AI event replay disagrees with its recorded human offer checkpoint");
        accepted=response.answer==AiHumanAnswer::Accept; ++replay->consumed; return true;
    }
    //00406dd8,00476c44/00476b8c. Human decisions are not synthesized.
    bool negotiate(int p,int other) {
        if (!player(p) || !player(other)) return false;
        if (!d.players[size_t(other)].type) return true;
        if (!negotiationState()) return false;
        auto& live=*result.contextAfter.negotiation;
        const int32_t elapsed=std::bit_cast<int32_t>(uint32_t(d.options.turn)-uint32_t(live.lastOfferTurn[size_t(p)][size_t(other)]));
        if (elapsed<5) return true;
        uint32_t mask=0; bool accepted=false;
        if (!pact(p,other,1,true) && !pact(p,other,2,true)) {
            if (!assess(p,other,1,true,accepted)) return false;
            if (accepted) mask=1;
        }
        if (!pact(p,other,2,true) && !mask) {
            if (!assess(p,other,2,true,accepted)) return false;
            if (accepted) mask=2;
        }
        if (!pact(p,other,8,true)) {
            if (!assess(p,other,mask|8u,true,accepted)) return false;
            if (accepted) mask|=8;
        }
        if (!pact(p,other,4,true)) {
            if (!assess(p,other,mask|4u,true,accepted)) return false;
            if (accepted) mask|=4;
        }
        if (!pact(p,other,0x10,true) && pact(p,other,0xe)) {
            if (!assess(p,other,0x10,true,accepted)) return false;
            if (accepted) mask=0x10;
        }
        if (!normalizeAiPactOffer(d,p,other,mask,mask,error)) return false;
        if (!mask) return true;
        live.offerState[size_t(p)]=2;
        live.lastOfferTurn[size_t(p)][size_t(other)]=d.options.turn;
        const size_t offerIndex=result.offers.size();
        result.offers.push_back({p,other,mask,AiOfferOutcome::Busy});
        if (live.offerState[size_t(other)]!=0) live.offerState[size_t(p)]=1;
        else {
            live.offerState[size_t(other)]=2;
            if (other==d.options.localPlayer || signedType(d.players[size_t(other)])<3) {
                if (!humanOffer(p,other,mask,accepted)) {
                    if (replay && replay->pending) result.offers[offerIndex].outcome=AiOfferOutcome::AwaitingHuman;
                    return false;
                }
            } else {
                if (d.players[size_t(other)].type!=3)
                    return fail(error,"Pact offer requires an unimplemented AI personality");
                if (!respondToOffer(p,other,uint16_t(mask),accepted)) return false;
            }
            live.offerState[size_t(p)]=accepted?3:4;
            live.offerState[size_t(other)]=0;
        }
        const int32_t response=live.offerState[size_t(p)];
        if (response==3) {
            result.offers[offerIndex].outcome=AiOfferOutcome::Accepted;
            if (!makePact(p,other,mask) || !change(p,other,8)) return false;
        } else if (response==0 || response==4) {
            result.offers[offerIndex].outcome=AiOfferOutcome::Rejected;
            if (!change(p,other,-8)) return false;
        }
        live.offerState[size_t(p)]=0;
        return true;
    }
    bool pactEvent(int eventType,int p,int other,int third) {
        if (!player(other) || !player(third)) return false;
        const uint32_t bit=uint32_t(1)<<uint32_t(third);
        const int32_t relation=attitude(d.scratchJob1,p,other);
        const bool friendly=attitude(d.scratchJob1,p,third)>=0 && !(d.aiWarMask[size_t(p)]&bit);
        if (eventType==0x73) return !friendly || negotiate(p,third);
        if (relation < -19) {
            if (friendly && std::bit_cast<int32_t>(d.players[size_t(p)].relations[third])<
                            std::bit_cast<int32_t>(d.players[size_t(other)].relations2[third])) {
                if (!negotiationState()) return false;
                const auto& metrics=result.contextAfter.negotiation->victory;
                if (aiVictoryMetric(d,p,metrics)<aiVictoryMetric(d,third,metrics)) {
                    enqueue({p,bit,-1,9,{other,0,0}}); return true;
                }
            }
            return change(p,third,-4);
        }
        if (relation>19 && friendly) return change(p,third,4) && negotiate(p,third);
        return true;
    }
    bool diplomacy(const AiDiplomacyRequest& request) {
        if (result.contextAfter.gameAborted || request.category < 31 || request.category > 35) return true;
        if (!player(request.other)) return false;
        result.handled = true;
        uint32_t random;
        if (!draw(random,"AiDiplomacyResponse00404c74")) return false;
        random %= 100; int choice = 0;
        // Original subtracts BEFORE testing signed<=0: roll0 can select a
        // zero-weight first entry, and a threshold50 includes BOTH0 and50.
        while (choice < 4) {
            random -= uint32_t(kResponseWeights[request.category - 31][choice]);
            if (std::bit_cast<int32_t>(random) < 1) break;
            ++choice;
        }
        constexpr int delta[]{-4,-8,0,4,4};
        if (choice != 2 && !change(request.player,request.other,delta[choice])) return false;
        return chat(request.player,request.other,choice+31);
    }
    // orig:004033d0 ->00403350. Clear the bit, emit the end-war message, then
    // visit ALL50 live targetPlayer words (including zeroed/free records).
    bool endWars(int p) {
        for (int other = 0; other < kMaxPlayers && d.aiWarMask[size_t(p)] != 0; ++other) {
            const uint32_t bit = uint32_t(1) << uint32_t(other);
            if (!(d.aiWarMask[size_t(p)] & bit)) continue;
            AiWarEnd ended; ended.player = p; ended.other = other;
            ended.maskBefore = d.aiWarMask[size_t(p)];
            d.aiWarMask[size_t(p)] &= ~bit; ended.maskAfter = d.aiWarMask[size_t(p)];
            enqueue({p,bit,-1,1,{}});
            for (int j = 0; j < kJobsPerPlayer; ++j) {
                if (d.jobs[size_t(p)][size_t(j)].targetPlayer != other) continue;
                TaskForceDissolutionReport dissolution;
                if (!dissolveTaskForce(d,p,j,d,dissolution,error)) return false;
                ended.dissolvedJobs.push_back(j);
            }
            result.warsEnded.push_back(std::move(ended));
        }
        return true;
    }
    bool hostility(const AiEventRequest& request) {
        const int p = request.player, other = request.extra1;
        if (other < 0) return true;
        if (!player(other) || !change(p,other,-20)) return false;
        const uint32_t bit = uint32_t(1) << uint32_t(other);
        bool reconsider = !(d.aiWarMask[size_t(p)] & bit);
        if (reconsider && d.aiWarMask[size_t(p)]) {
            uint32_t chance; if (!draw(chance,"AiHostilityWarGate004047a0")) return false;
            reconsider = (chance & 7u) == 0;
        }
        if (reconsider) {
            //00403408 can decline without its gameplay leaves.
            if ((d.options.playerSkill[p] == 4 && signedType(d.players[size_t(other)]) >= 3) ||
                attitude(d.scratchJob1,p,other) >= 8) return chat(p,other,31);
            if (!endWars(p)) return false;
            if (!breakPacts(p,other)) return false;
            d.aiWarMask[size_t(p)] |= bit;
            uint32_t chance; if (!draw(chance,"AiNewWarMessage00403408")) return false;
            if (!(chance & 1u)) enqueue({p,bit,-1,0,{other,0,0}});
            for (int recipient = 0; recipient < kMaxPlayers; ++recipient)
                if (recipient != other && signedType(d.players[size_t(recipient)]) != 0 &&
                    signedType(d.players[size_t(recipient)]) < 3 && !pact(recipient,other,0x10,true) &&
                    !(d.aiWarMask[size_t(p)] & (uint32_t(1) << uint32_t(recipient))))
                    enqueue({p,uint32_t(1) << uint32_t(recipient),-1,2,{other,0,0}});
            return true;
        }
        if (request.eventType == 0x25 || request.eventType == 0x26) {
            enqueue({p,bit,-1,request.eventType == 0x25 ? 5 : 6,{request.extra2,0,0}}); return true;
        }
        return chat(p,other,32);
    }
    bool event(const AiEventRequest& request) {
        if (eventDepth>=64) return fail(error,"AI pact callback nesting exceeds the supported limit",save::ErrorCode::Limit);
        struct Depth { unsigned& value; explicit Depth(unsigned& v):value(v){++value;} ~Depth(){--value;} } depth(eventDepth);
        const int p = request.player, other = request.extra1;
        uint32_t chance = 0; int alternate = 0;
        result.handled = true;
        switch (request.eventType) {
        case 8: case 9: case 0xd: case 0x27: case 0x2e: case 0x41: case 0x4e: case 0x96:
            alternate = 34; break;
        case 0xb: case 0xf: case 0x13: case 0x14: case 0x16: case 0x19: case 0x24: case 0x2c: case 0x76: case 0x77: case 0x95:
            alternate = 33; break;
        case 10: case 0xe: case 0x25: case 0x26: case 0x28: case 0x2b: case 0x2d: case 0x51: case 0x75: case 0x7a:
            return hostility(request);
        case 0x1f: case 0x38: case 0x42: case 0x4d:
            if (other < 0) return true;
            if (!player(other) || !draw(chance,"AiGratitudeGate004047a0")) return false;
            if (chance & 1u) return true;
            return change(p,other,4) && chat(p,other,35);
        case 0x3a: {
            int delta = 0; const uint32_t bits = uint32_t(request.extra2);
            if (bits & 2u) delta = -20;
            if (bits & 8u) delta -= 8;
            if (bits & 4u) delta -= 8;
            if (bits & 16u) delta -= 20;
            return change(p,other,delta*2);
        }
        case 0x72: case 0x73:
            if (!draw(chance,"AiPactEventGate004047a0")) return false;
            if (chance & 1u) return true;
            return pactEvent(request.eventType,p,other,request.extra2) &&
                   pactEvent(request.eventType,p,request.extra2,other);
        case 0x74: {
            const int third = request.extra2;
            if (!player(other) || !player(third)) return false;
            const int32_t relation = attitude(d.scratchJob1,p,other);
            if (!(d.aiWarMask[size_t(p)] & (uint32_t(1) << uint32_t(third))) || relation < -19) {
                if (pact(p,third,0x10) && relation < 20) return chat(p,other,32) && change(p,other,-8);
                return true;
            }
            return chat(p,other,35) && change(p,other,8);
        }
        default: result.handled = false; return true;
        }
        // Unlike gratitude, these groups draw BEFORE testing negative other.
        if (!draw(chance,"AiEventChatGate004047a0")) return false;
        if ((chance & 1u) || other < 0) return true;
        if (!player(other) || !draw(chance,"AiEventChatChoice004047a0")) return false;
        return chat(p,other,(chance & 1u) ? alternate : 31);
    }
};
template<class Request, class Action>
bool reaction(const AiSessionSnapshot& state, const save::Document& source, const Request& request,
              const AiReactionContext& context, save::Document& destination,
              AiReactionReport& report, save::Error& error, Action action,
              ai_event_detail::ReplayState* replay = nullptr) {
    try {
        if (!state.initializationComplete || request.player < 0 || request.player >= kMaxPlayers ||
            !state.data.ai[size_t(request.player)].initialized)
            return fail(error, "AI reaction requires an initialized owned Machiavelli binding");
        if (!gameDocument(source,error)) return false;
        if (source.players[size_t(request.player)].type != 3)
            return fail(error, "AI reaction document no longer matches its installed personality binding");
        if (context.pendingMessages.size() > kAiMessageCapacity)
            return fail(error, "AI message FIFO exceeds its original41-message capacity", save::ErrorCode::Limit);
        SessionRng rng; if (!rng.restore(context.rng,error)) return false;
        auto candidate = std::make_unique<save::Document>(source); AiReactionReport result;
        result.contextAfter = context;
        ReactionWork work{*candidate,result,rng,error,&state,replay};
        if (!action(work,request) && (!replay || !replay->pending)) return false;
        if (!save::validate(*candidate,error)) return false;
        result.contextAfter.rng = rng.snapshot();
        destination = std::move(*candidate); report = std::move(result); error = {}; return true;
    } catch (const std::bad_alloc&) {
        return fail(error, "Insufficient memory reacting through owned AI", save::ErrorCode::Limit);
    } catch (const std::length_error&) {
        return fail(error, "Owned AI reaction exceeds allocation limits", save::ErrorCode::Limit);
    } catch (const std::exception& e) {
        error = {save::ErrorCode::InvalidState,0,e.what()}; return false;
    }
}
} // namespace

bool AiSession::reactDiplomacy(const save::Document& source, const AiDiplomacyRequest& request,
                              const AiReactionContext& context, save::Document& destination,
                              AiReactionReport& report, save::Error& error) const {
    return reaction(state_,source,request,context,destination,report,error,
                    [](ReactionWork& work, const AiDiplomacyRequest& input) { return work.diplomacy(input); });
}
bool AiSession::reactEvent(const save::Document& source, const AiEventRequest& request,
                          const AiReactionContext& context, save::Document& destination,
                          AiReactionReport& report, save::Error& error) const {
    return reaction(state_,source,request,context,destination,report,error,
                    [](ReactionWork& work, const AiEventRequest& input) { return work.event(input); });
}
bool AiSession::replayEvent(const save::Document& source,const AiEventRequest& request,
    const AiReactionContext& context,ai_event_detail::ReplayState& replay,
    save::Document& destination,AiReactionReport& report,save::Error& error) const {
    return reaction(state_,source,request,context,destination,report,error,
                    [](ReactionWork& work,const AiEventRequest& input) { return work.event(input); },&replay);
}

bool changeAiAttitude(const save::Document& source,const AiAttitudeRequest& request,
                      const AiReactionContext& context,save::Document& destination,
                      AiReactionReport& report,save::Error& error) {
    try {
        if (!gameDocument(source,error)) return false;
        SessionRng rng;
        if (!rng.restore(context.rng,error)) return false;
        if (context.pendingMessages.size()>kAiMessageCapacity)
            return fail(error,"AI message FIFO exceeds its original41-message capacity",save::ErrorCode::Limit);
        auto candidate=std::make_unique<save::Document>(source); AiReactionReport result;
        result.contextAfter=context; result.handled=true;
        ReactionWork work{*candidate,result,rng,error};
        if (!work.change(request.player,request.other,request.delta) || !save::validate(*candidate,error)) return false;
        destination=std::move(*candidate); report=std::move(result); error={}; return true;
    } catch (const std::bad_alloc&) { return fail(error,"Insufficient memory changing owned AI attitude",save::ErrorCode::Limit); }
      catch (const std::exception& e) { error={save::ErrorCode::InvalidState,0,e.what()}; return false; }
}
} // namespace dl2::simulation
