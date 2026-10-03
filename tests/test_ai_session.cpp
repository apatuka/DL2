// Original-data oracles for AInit/minister RET dispatch and task-force helpers.
#include "game/ai_session.h"
#include "game/army_pool.h"
#include "game/data_tables.h"
#include "game/save_files.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include "game/runtime_state.h"
#include <algorithm>
#include <array>
#include <bit>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
using namespace dl2;
using namespace dl2::simulation;
using save::Document;
namespace fs = std::filesystem;
void require(bool condition, const char* message) {
    if (!condition) throw std::runtime_error(message);
}
std::vector<uint8_t> bytes(const Document& d) {
    std::vector<uint8_t> result; save::Error error;
    if (!save::encode(d, result, error)) throw std::runtime_error(error.message);
    return result;
}
std::unique_ptr<Document> fixture() {
    auto d = std::make_unique<Document>();
    std::memcpy(d->header.text, save::kHeaderText, sizeof(save::kHeaderText));
    d->header.version = kSaveVersion; d->header.minusOne = -1;
    d->options.numPlayers = 3; d->options.localPlayer = 0; d->options.turn = 7;
    d->world.width = d->world.height = 1; d->world.numTerritories = 1;
    d->tiles.resize(1); d->tiles[0].territory = 1;
    d->territories.resize(1); auto& t = d->territories[0].data;
    t.index = 1; t.owner = 1; t.terrain = 1; t.numTiles = 1;
    for (size_t p = 0; p < kMaxPlayers; ++p) {
        d->players[p].type = p == 0 ? 1 : p < 3 ? 3 : 0;
        d->players[p].index = uint8_t(p); d->players[p].race = int8_t(p);
        d->players[p].aiVtbl[0] = 0xffffffff; d->players[p].aiParam2 = 0x87654321;
        std::memset(d->players[p].ministers, 0xa5, sizeof(d->players[p].ministers));
        d->ministerJobs[p].resize(1); d->ministerJobs[p][0].type = 1;
        d->aiWarMask[p] = 0xabcd0000u + uint32_t(p);
        for (auto& job : d->jobs[p]) job.owner = int16_t(p);
    }
    d->players[6].type = 255; d->players[6].race = -1; d->players[6].index = 250;
    d->armies.resize(20);
    for (size_t i = 0; i < d->armies.size(); ++i) {
        auto& army = d->armies[i];
        army.id = i == 19 ? uint16_t(65000) : uint16_t(101 + i);
        army.type = 1; army.owner = 1; army.unitClass = 1; army.health = 80;
        army.territory.raw = army.dest.raw = army.origin.raw = 1;
        army.unk_04 = 0xbaba; army.unk_2a = -32767;
        std::memset(army.name, int('A' + i), sizeof(army.name));
    }
    d->scratchJob1.armies[3].raw = 0xdeadbeef; d->trailing = {0xaa, 0, 0xff};
    save::Error error; require(save::validate(*d, error), "invalid AI fixture"); return d;
}
void bind(Document& d, int p, int j, int slot, size_t army) {
    d.jobs[size_t(p)][size_t(j)].armyIds[slot] = d.armies[army].id;
    d.jobs[size_t(p)][size_t(j)].armies[slot].raw = 0xf0000000u + uint32_t(army);
    d.armies[army].owner = int8_t(p); d.armies[army].job = int16_t(j + 1);
}
TaskForceEditReport sentinel() {
    TaskForceEditReport r; r.outcome = TaskForceOutcome::Full;
    r.armyId = 999; r.player = 6; r.jobIndex = 44; r.slot = 12; r.detachedArmyIds = {32, 43}; return r;
}
void initializationAndDispatch() {
    auto d = fixture(); const auto before = bytes(*d); AiSession session;
    AiDispatchReport output; output.invocations.push_back({AiBinding::EventMachiavelli, 9, 9, 123});
    const auto untouched = output; save::Error error;
    require(!session.dispatch({1, AiOperation::MinisterPhase, 0}, output, error) && output == untouched,
            "uninitialized dispatch did not reject transactionally");
    error = {save::ErrorCode::Io, 99, "old"};
    require(session.initializeAfterLoad(*d, error) && error.code == save::ErrorCode::None, "AI initialization failed");
    const auto state = session.snapshot();
    require(state.initializationComplete && !state.aiTurnImplemented && state.diplomacyImplemented && state.data.initialized &&
            !state.data.aiExecutable && state.data.localPlayer == 0 && state.data.hostPlayer == 0 &&
            !state.data.netGame && !state.data.netJoined && !state.data.netRestore && !state.data.gameAborted,
            "AI initialization overstated turn capability or lost offline reset flags");
    constexpr int parameters[]{20, 10, 0, 30, 40, 50};
    for (size_t p = 0; p < kMaxPlayers; ++p) {
        const auto& ai = state.data.ai[p];
        require(ai.initialized == (p == 1 || p == 2), "wrong AI slots initialized");
        if (!ai.initialized) {
            for (const auto binding : state.personalityBindings[p]) require(binding == AiBinding::None, "inactive callback installed");
            continue;
        }
        require(ai.initializations == 1 && ai.personality == LoadAiPersonality::Machiavelli &&
                ai.strategyState == 0 && ai.strategyCountdown == 40 && ai.unknown53317c == 0,
                "Machiavelli strategy initial values differ");
        require(state.personalityBindings[p][0] == AiBinding::InitializeMachiavelli &&
                state.personalityBindings[p][1] == AiBinding::TurnMachiavelli &&
                state.personalityBindings[p][2] == AiBinding::DiplomacyMachiavelli &&
                state.personalityBindings[p][3] == AiBinding::VerifiedReturn &&
                state.personalityBindings[p][4] == AiBinding::EventMachiavelli, "personality binding layout differs");
        for (size_t m = 0; m < 6; ++m) {
            const auto& minister = ai.ministers[m];
            require(minister.role == Minister(m) && minister.kind == m && minister.parameter == parameters[m],
                    "minister role/kind/parameter initializer differs");
            require(std::all_of(minister.scratch.begin(), minister.scratch.end(), [](uint8_t v) { return v == 0; }),
                    "minister scratch was not reset");
            for (const auto binding : state.ministerBindings[p][m]) require(binding == AiBinding::VerifiedReturn, "minister binding missing");
        }
    }
    constexpr int order[]{0, 5, 1, 4, 3, 2};
    for (int phase = 0; phase < 4; ++phase) {
        require(session.dispatch({1, AiOperation::MinisterPhase, phase}, output, error), "minister phase failed");
        require(output.invocations.size() == 6 && !output.stateChanged && session.snapshot() == state,
                "canonical RET phase changed owned AI state");
        for (size_t i = 0; i < 6; ++i)
            require(output.invocations[i] == AiInvocation{AiBinding::VerifiedReturn, order[i], phase,
                    data::kMinisterVtable[order[i]].fn[phase].addr}, "minister dispatch order or target differs");
    }
    const auto reportBefore = output;
    for (const auto request : {AiRequest{1,AiOperation::Turn,0}, {1,AiOperation::Diplomacy,0},
                              {1,AiOperation::Event,0}, {1,AiOperation::MinisterPhase,4},
                              {1,AiOperation::MinisterPhase,-1}, {0,AiOperation::Initialize,0},
                              {7,AiOperation::Initialize,0}, {1,AiOperation(255),0}})
        require(!session.dispatch(request, output, error) && output == reportBefore && session.snapshot() == state,
                "unsupported AI operation succeeded or changed state/report");
    require(session.dispatch({1,AiOperation::Initialize,0}, output, error) && output.stateChanged &&
            session.snapshot().data.ai[1].initializations == 2 &&
            session.snapshot().data.ai[2] == state.data.ai[2], "explicit initializer failed or reset another player");
    const auto resetState = session.snapshot();
    d->players[1].type = 2;
    require(!session.initializeAfterLoad(*d,error) && session.snapshot() == resetState, "pre-conversion network human accepted");
    d->players[1].type = 4;
    require(!session.initializeAfterLoad(*d,error) && session.snapshot() == resetState, "unknown personality accepted");
    d->players[1].type = 3; d->players[0].type = 3;
    require(!session.initializeAfterLoad(*d,error) && session.snapshot() == resetState, "non-normalized local player accepted");
    d->players[0].type = 1;
    require(bytes(*d) == before, "AI initializer mutated packed callbacks, jobs or archival source");
    for (int count = 2; count < 255; ++count) require(session.dispatch({1,AiOperation::Initialize,0},output,error), "initializer audit counter failed early");
    const auto exhausted = session.snapshot(); const auto last = output;
    require(!session.dispatch({1,AiOperation::Initialize,0},output,error) && error.code == save::ErrorCode::Limit &&
            session.snapshot() == exhausted && output == last, "initialization counter overflow was not transactional");
}

void removals() {
    auto d = fixture(); d->armies[0].type = 12; d->armies[0].cargo[0].raw = 102; d->armies[0].cargo[2].raw = 103;
    d->armies[2].type = 12; d->armies[2].cargo[0].raw = 101; // Cycle stops after job0 reset.
    bind(*d,1,0,3,0); bind(*d,1,1,1,1); bind(*d,1,49,15,2);
    d->jobs[1][0].armyIds[4] = 101; d->jobs[1][0].armies[4].raw = 0xfeed0004;
    auto expected = std::make_unique<Document>(*d);
    for (const auto entry : {std::array<size_t,3>{0,3,0}, {1,1,1}, {49,15,2}}) {
        expected->jobs[1][entry[0]].armyIds[entry[1]] = 0;
        expected->jobs[1][entry[0]].armies[entry[1]].raw = 0; expected->armies[entry[2]].job = 0;
    }
    TaskForceEditReport report; save::Error error;
    require(removeArmyFromTaskForce(*d,101,report,error) && report.outcome == TaskForceOutcome::Removed &&
            report.player == 1 && report.jobIndex == 0 && report.slot == 3 &&
            report.detachedArmyIds == std::vector<uint32_t>{101,102,103} && bytes(*d) == bytes(*expected),
            "Remove first-match/type12 recursion differs or overwrote opaque fields");
    bind(*d,1,2,0,1); // job0 root must not recurse into its now reattached cargo.
    const auto before = bytes(*d); const auto* oldPointer = d->armies.data();
    error = {save::ErrorCode::Io,123,"old"};
    require(removeArmyFromTaskForce(*d,101,report,error) && report.outcome == TaskForceOutcome::AlreadyDetached &&
            report.detachedArmyIds.empty() && bytes(*d) == before && d->armies.data() == oldPointer &&
            error.code == save::ErrorCode::None, "job0 early return recursed, changed document or left stale error");
    d = fixture(); d->armies[0].type = 14; d->armies[0].unitClass = 4; d->armies[0].cargo[0].raw = 102;
    bind(*d,1,0,0,0); bind(*d,1,1,0,1);
    require(removeArmyFromTaskForce(*d,101,report,error) && report.detachedArmyIds == std::vector<uint32_t>{101} &&
            d->armies[1].job == 2, "Remove used carrier class instead of exact type12");
    d = fixture(); d->armies[0].type = 12; d->armies[0].cargo[0].raw = 102;
    bind(*d,1,0,0,0); d->armies[1].job = 51;
    const auto invalid = bytes(*d); report = sentinel(); const auto keep = report;
    require(!removeArmyFromTaskForce(*d,101,report,error) && bytes(*d) == invalid && report == keep,
            "late cargo job error failed to roll back root removal");
    d->armies[1].job = 2; // No matching ID in that job, original DebugMessage branch.
    const auto missing = bytes(*d);
    require(!removeArmyFromTaskForce(*d,101,report,error) && bytes(*d) == missing && report == keep,
            "inconsistent owner-local binding was hidden");
    require(!removeArmyFromTaskForce(*d,0,report,error) && !removeArmyFromTaskForce(*d,0x10065,report,error) &&
            bytes(*d) == missing && report == keep, "unresolved/full-width ID was narrowed or accepted");
}

void additions() {
    auto d = fixture(); bind(*d,1,0,2,19); const auto originalId = d->armies[19].id;
    auto expected = std::make_unique<Document>(*d);
    expected->jobs[1][0].armyIds[2] = 0; expected->jobs[1][0].armies[2].raw = 0;
    expected->jobs[1][49].armyIds[0] = originalId; expected->jobs[1][49].armies[0].raw = 0; expected->armies[19].job = 50;
    TaskForceEditReport report; save::Error error;
    require(addArmyToTaskForce(*d,1,49,originalId,report,error) && report.outcome == TaskForceOutcome::Added &&
            report.slot == 0 && report.jobIndex == 49 && report.detachedArmyIds == std::vector<uint32_t>{65000} &&
            bytes(*d) == bytes(*expected), "Add remove-first/free-slot/high-ID semantics differ");
    d->armies[19].job = -2; d->jobs[1][49].owner = -1; // AlreadyPresent reads neither of these fields.
    const auto present = bytes(*d); auto* pointer = d->armies.data();
    require(addArmyToTaskForce(*d,1,49,originalId,report,error) && report.outcome == TaskForceOutcome::AlreadyPresent &&
            report.slot == 0 && bytes(*d) == present && d->armies.data() == pointer,
            "AlreadyPresent changed source or needlessly validated fields not read");
    d = fixture(); bind(*d,1,1,4,0);
    for (size_t slot = 0; slot < 16; ++slot) d->jobs[1][0].armyIds[slot] = d->armies[slot + 1].id;
    d->jobs[1][0].owner = -1; // Full returns before owner arithmetic.
    const auto full = bytes(*d); pointer = d->armies.data();
    require(addArmyToTaskForce(*d,1,0,101,report,error) && report.outcome == TaskForceOutcome::Full &&
            report.slot == -1 && bytes(*d) == full && d->armies.data() == pointer && d->armies[0].job == 2,
            "Full result detached army or claimed insertion");
    d->jobs[1][0].armyIds[7] = 0; const auto unsafe = bytes(*d); report = sentinel(); const auto keep = report;
    require(!addArmyToTaskForce(*d,1,0,101,report,error) && bytes(*d) == unsafe && report == keep,
            "mismatched Job.owner accepted or rollback failed");
    for (const auto pair : {std::array<int,2>{-1,0}, {7,0}, {1,-1}, {1,50}})
        require(!addArmyToTaskForce(*d,pair[0],pair[1],101,report,error) && report == keep && bytes(*d) == unsafe,
                "out-of-range task-force target accepted");
    d->jobs[1][0].owner = 1; d->armies[0].owner = 2;
    const auto foreign = bytes(*d);
    require(!addArmyToTaskForce(*d,1,0,101,report,error) && bytes(*d) == foreign && report == keep,
            "foreign army was added to incompatible owner-local task force");
}

// Pending physical bindings are intentionally not encodable. For transaction
// checks retain their complete metadata and Job bytes separately, while the
// remaining archival fields use the existing strict codec as a byte witness.
struct TaskForceWitness {
    std::vector<uint8_t> archive, jobs;
    std::optional<save::ArmyPoolState> pool;
    bool operator==(const TaskForceWitness&) const = default;
};
TaskForceWitness taskForceWitness(const Document& d) {
    auto projected = std::make_unique<Document>(d);
    TaskForceWitness result; result.pool = d.armyPool;
    result.jobs.resize(sizeof(d.jobs));
    std::memcpy(result.jobs.data(), &d.jobs, sizeof(d.jobs));
    projected->armyPool.reset();
    for (auto& player : projected->jobs) for (auto& job : player)
        std::fill(std::begin(job.armyIds), std::end(job.armyIds), uint16_t(0));
    result.archive = bytes(*projected); return result;
}
uint32_t reuseArmyCell(Document& d, uint16_t oldId, uint16_t newId) {
    save::Error error;
    const auto old = std::find_if(d.armies.begin(), d.armies.end(),
                                  [oldId](const Army& a) { return a.id == oldId; });
    require(old != d.armies.end(), "pool reuse fixture lacks original army");
    Army replacement = *old;
    const uint32_t cell = armyPoolSlot(d, oldId);
    require(cell && retireArmyPoolSlot(d, oldId, error), "pool reuse fixture retirement failed");
    d.armies.erase(old); replacement.id = newId; d.armies.push_back(replacement);
    require(allocateArmyPoolSlot(d, newId, error) && armyPoolSlot(d, newId) == cell,
            "native free-list head did not reuse the just-retired physical cell");
    require(save::validate(d, error), "reused-cell fixture failed strict owned validation");
    return cell;
}
void pooledTaskForces() {
    save::Error error; TaskForceEditReport report;
    {
        auto d = fixture(); bind(*d,1,0,2,0);
        d->jobs[1][0].armyIds[5] = 101; d->jobs[1][0].armies[5].raw = 0xfeed0005;
        require(ensureArmyPool(*d,error), "pooled Remove setup failed");
        const auto cell = reuseArmyCell(*d,101,900);
        require(d->jobs[1][0].armyIds[2] == 101 &&
                taskForceTarget(*d,1,0,2) == d->armyById(900),
                "reused fixture accidentally followed expected ID instead of cell");
        auto expected = std::make_unique<Document>(*d);
        expected->jobs[1][0].armyIds[2] = 0; expected->jobs[1][0].armies[2].raw = 0;
        expected->armyPool->jobSlots[1][0][2] = 0; expected->armies.back().job = 0;
        error = {save::ErrorCode::Io,123,"old"};
        require(removeArmyFromTaskForce(*d,900,report,error) && report.outcome == TaskForceOutcome::Removed &&
                report.slot == 2 && report.detachedArmyIds == std::vector<uint32_t>{900} &&
                taskForceWitness(*d) == taskForceWitness(*expected) && error.code == save::ErrorCode::None,
                "pooled Remove did not clear the first pointer match transactionally");
        require(d->armyPool->jobSlots[1][0][5] == cell && d->jobs[1][0].armyIds[5] == 101 &&
                d->jobs[1][0].armies[5].raw == 0xfeed0005,
                "pooled Remove eagerly cleaned a duplicate deferred binding");
        std::vector<uint8_t> out{9,8,7}; const auto before = out;
        require(!save::encode(*d,out,error) && out == before,
                "a retained mismatched binding was silently exported");
    }
    {
        auto d = fixture(); bind(*d,1,0,7,0);
        require(ensureArmyPool(*d,error), "pooled AlreadyPresent setup failed");
        reuseArmyCell(*d,101,900);
        d->armies.back().job = -2; d->jobs[1][0].owner = -1;
        const auto before = taskForceWitness(*d); const auto* pointer = d->armies.data();
        const auto* poolPointer = d->armyPool->liveIds.data();
        require(addArmyToTaskForce(*d,1,0,900,report,error) &&
                report.outcome == TaskForceOutcome::AlreadyPresent && report.slot == 7 &&
                report.detachedArmyIds.empty() && taskForceWitness(*d) == before &&
                d->armies.data() == pointer && d->armyPool->liveIds.data() == poolPointer,
                "reused-pointer AlreadyPresent read stale ID/owner or replaced no-op storage");
    }
    {
        auto d = fixture(); require(ensureArmyPool(*d,error), "null binding fixture setup failed");
        //0040ab54 does not see the saved ID101 here: its pointer is NULL.
        d->jobs[1][0].armyIds[0] = 101; d->jobs[1][0].armies[0].raw = 0xabcdef01;
        require(addArmyToTaskForce(*d,1,0,101,report,error) && report.outcome == TaskForceOutcome::Added &&
                report.slot == 0 && report.detachedArmyIds.empty() && d->armies[0].job == 1 &&
                d->jobs[1][0].armyIds[0] == 101 && d->jobs[1][0].armies[0].raw == 0 &&
                d->armyPool->jobSlots[1][0][0] == armyPoolSlot(*d,101),
                "null pointer with nonzero expected ID was not the first free insertion slot");
    }
    {
        auto d = fixture(); bind(*d,1,1,4,0);
        require(ensureArmyPool(*d,error), "cleared-cell Full fixture setup failed");
        // All pointers are nonnull cleared cells, despite every expected ID0.
        // Native0040b0c0 therefore returns Full BEFORE ownership validation.
        for (size_t k = 0; k < 16; ++k)
            d->armyPool->jobSlots[1][0][k] = uint32_t(kMaxArmies - k);
        d->jobs[1][0].owner = -1;
        const auto before = taskForceWitness(*d); const auto* pointer = d->armies.data();
        require(addArmyToTaskForce(*d,1,0,101,report,error) && report.outcome == TaskForceOutcome::Full &&
                report.slot == -1 && report.detachedArmyIds.empty() && taskForceWitness(*d) == before &&
                d->armies.data() == pointer && d->armies[0].job == 2,
                "nonnull cleared cells were reused as free task-force members");
        d->jobs[1][0].owner = 1; d->armyPool->jobSlots[1][0][9] = 0;
        d->jobs[1][0].armyIds[9] = 55555; // NULL with unresolved saved ID is still free.
        require(addArmyToTaskForce(*d,1,0,101,report,error) && report.outcome == TaskForceOutcome::Added &&
                report.slot == 9 && report.detachedArmyIds == std::vector<uint32_t>{101} &&
                d->armyPool->jobSlots[1][1][4] == 0 && d->jobs[1][1].armyIds[4] == 0 &&
                d->armyPool->jobSlots[1][0][9] == armyPoolSlot(*d,101) && d->jobs[1][0].armyIds[9] == 101,
                "pooled Add lost remove-first/first-null semantics or synchronized the wrong binding");
    }
    {
        auto d = fixture(); d->armies[0].type = 12; d->armies[0].cargo[0].raw = 102;
        bind(*d,1,0,0,0); bind(*d,1,1,3,1);
        require(ensureArmyPool(*d,error), "pooled recursive rollback setup failed");
        // Saved IDs look correct, but the cargo's typed binding is NULL. Root
        // removal succeeds on the candidate before this later error occurs.
        d->armyPool->jobSlots[1][1][3] = 0;
        const auto before = taskForceWitness(*d); report = sentinel(); const auto keep = report;
        const auto* pointer = d->armies.data();
        require(!removeArmyFromTaskForce(*d,101,report,error) && report == keep &&
                taskForceWitness(*d) == before && d->armies.data() == pointer,
                "late missing cargo pointer did not roll back IDs, bindings and report");
        d->armyPool->jobSlots[1][1][3] = armyPoolSlot(*d,102);
        require(removeArmyFromTaskForce(*d,101,report,error) &&
                report.detachedArmyIds == std::vector<uint32_t>{101,102} &&
                d->armyPool->jobSlots[1][0][0] == 0 && d->armyPool->jobSlots[1][1][3] == 0 &&
                d->jobs[1][0].armyIds[0] == 0 && d->jobs[1][1].armyIds[3] == 0 &&
                d->armies[0].job == 0 && d->armies[1].job == 0,
                "type12 recursive Remove did not synchronize every touched pool binding");
        // Absence of a sidecar still means strict archival ID resolution.
        d = fixture(); d->jobs[1][0].armyIds[0] = 55555; report = keep;
        require(!addArmyToTaskForce(*d,1,0,101,report,error) && report == keep && !d->armyPool,
                "task-force Add silently installed metadata to admit an archival orphan");
    }
}

void scoutQueries() {
    auto d = fixture(); Army army = d->armies[0]; bool result = false; save::Error error;
    require(canScoutOwned(*d,army,result,error) && !result, "plain laser squad gained scouting");
    d->raceStats.v[54][1] = -1; army.unitClass = 5; // Stored class deliberately disagrees.
    require(canScoutOwned(*d,army,result,error) && result, "race scouting ignored signed modifier or canonical class");
    army.type = 12;
    require(canScoutOwned(*d,army,result,error) && !result, "race trait alone granted transport scouting");
    d->techs[43].knownMask = 1; d->players[1].index = 0;
    require(canScoutOwned(*d,army,result,error) && !result, "scout tech used Player.index instead of owner");
    d->techs[43].knownMask = 2;
    require(canScoutOwned(*d,army,result,error) && result, "tech43 transport scout rule differs");
    army.type = 5;
    require(canScoutOwned(*d,army,result,error) && !result, "tech scouting granted artillery class");
    d->players[1].race = -1; d->raceStats.v[53][6] = 12; d->techs[43].knownMask = 0; army.type = 1;
    require(canScoutOwned(*d,army,result,error) && result, "signed-race in-block word address was clamped");
    d->players[1].race = 70; result = true;
    require(!canScoutOwned(*d,army,result,error) && result, "out-of-block race query failed to preserve output");
    for (const auto type : {11,24}) {
        army.type = uint8_t(type); require(canScoutOwned(*d,army,result,error) && result && error.code == save::ErrorCode::None,
                                         "explicit scout type did not short-circuit race lookup");
    }
    army.type = 255;
    require(!canScoutOwned(*d,army,result,error) && result, "invalid canonical unit table selector accepted");
}

void maintainJobs() {
    auto d = fixture(); auto& jobs = d->ministerJobs[1]; jobs.resize(6);
    for (size_t i = 0; i < jobs.size(); ++i) {
        jobs[i].type = i ? 13 : 1; jobs[i].priority = int32_t(100 + i); jobs[i].param[0] = 101;
        jobs[i].next.raw = i + 1 < jobs.size() ? 0x8000u + uint32_t(i + 1) : 0;
        jobs[i].prev.raw = i ? 0x8000u + uint32_t(i - 1) : 0;
    }
    jobs[1].param[0] = 444; // Missing.
    jobs[2].param[0] = 102; d->armies[1].owner = 2; // Existing foreign unit.
    jobs[3].param[0] = 0x10065; // Do not narrow to the existing ID101.
    jobs[4].type = 3; jobs[4].param[0] = 444; // Other handlers remain unimplemented, untouched.
    jobs[5].param[0] = 101; jobs[5].unk_10 = 1; // Valid branch is NOT a generic reaper.
    auto expected = std::make_unique<Document>(*d);
    expected->ministerJobs[1] = {jobs[0], jobs[4], jobs[5]};
    expected->ministerJobs[1][0].next.raw = 0x8004;
    expected->ministerJobs[1][1].prev.raw = 0x8000;
    MaintainUnitPruneReport report; save::Error error;
    require(pruneInvalidMaintainUnitJobs(*d,report,error) && report.removed[1] == 3 && bytes(*d) == bytes(*expected),
            "deferred maintain-unit terminal cleanup differs or processed valid/other jobs");
    const auto before = bytes(*d); const auto* oldList = d->ministerJobs[1].data();
    require(pruneInvalidMaintainUnitJobs(*d,report,error) && report.removed == std::array<uint32_t,kMaxPlayers>{} &&
            bytes(*d) == before && oldList == d->ministerJobs[1].data(), "no-op deferred cleanup changed document");
    d->ministerJobs[1][2].param[0] = 0; report.removed[4] = 123; const auto keep = report;
    const auto unsupported = bytes(*d);
    require(!pruneInvalidMaintainUnitJobs(*d,report,error) && report == keep && bytes(*d) == unsupported,
            "ID0 free-pool lookup was silently approximated");
}

uint32_t secondaryStep(uint32_t& seed) {
    seed = seed * 0x41c64e6du + 0x3039u; return (seed >> 16) & 0x7fffu;
}
uint32_t seedForRoll(uint32_t roll) {
    for (uint32_t seed = 0; seed < 100000; ++seed) {
        auto next = seed; if (secondaryStep(next) % 100 == roll) return seed;
    }
    throw std::runtime_error("no deterministic seed for test roll");
}
AiReactionContext reactionContext(uint32_t seed) {
    SessionRng rng; save::Error error; require(rng.initialize(seed,error),"reaction RNG initialization failed");
    AiReactionContext result; result.rng = rng.snapshot(); return result;
}
void word(Job& block, int p, int other, int32_t value) {
    std::memcpy(reinterpret_cast<uint8_t*>(&block) + size_t(p*7+other)*4,&value,4);
}
int32_t word(const Job& block, int p, int other) {
    int32_t value; std::memcpy(&value,reinterpret_cast<const uint8_t*>(&block) + size_t(p*7+other)*4,4); return value;
}
void diplomacyReactions() {
    auto d = fixture(); auto output = fixture(); AiSession ai; save::Error error;
    require(ai.initializeAfterLoad(*d,error),"AI setup failed for diplomacy");
    constexpr uint32_t counts[]{26,24,27,23,20}; // Race0 below, distinct from fixture race1.
    d->players[1].race = 0;
    word(d->scratchJob1,1,0,7); word(d->scratchJob2,1,0,-9);
    const auto sourceBytes = bytes(*d); AiReactionReport report;
    for (int category = 31; category <= 35; ++category) for (uint32_t roll : {0u,1u,50u,51u,80u,81u,99u}) {
        const uint32_t seed = seedForRoll(roll); const auto context = reactionContext(seed);
        uint32_t step = seed; const auto draw1 = secondaryStep(step); const auto draw2 = secondaryStep(step);
        int response;
        if (category == 31 || roll == 0) response = 31;
        else if (category == 32) response = 32;
        else if (category == 33 || category == 34) response = roll <= 50 ? 31 : 35;
        else response = roll <= 80 ? 33 : 35;
        const int delta = response == 31 ? -4 : response == 32 ? -8 : response == 33 ? 0 : 4;
        error = {save::ErrorCode::Io,77,"old"};
        require(ai.reactDiplomacy(*d,{1,0,category},context,*output,report,error) && report.handled &&
                error.code == save::ErrorCode::None && bytes(*d) == sourceBytes, "diplomacy query failed or changed source");
        require(report.draws.size() == 2 && report.draws[0].value == draw1 && report.draws[1].value == draw2 &&
                report.draws[0].ordinal == 1 && report.draws[1].ordinal == 2 &&
                report.contextAfter.rng.secondary == step && report.contextAfter.rng.counters.secondary15 == 2 &&
                report.contextAfter.rng.rtlLow == seed && report.contextAfter.rng.rtlHigh == 0,
                "diplomacy primitive order/count or unrelated RNG stream differs");
        require(report.messages.size() == 1 && report.messages[0].outcome == AiMessageOutcome::Queued &&
                report.messages[0].message == AiDiplomacyMessage{1,1,response,int(draw2 % counts[response-31]),{}} &&
                report.contextAfter.pendingMessages == std::vector<AiDiplomacyMessage>{report.messages[0].message},
                "diplomacy response boundary/variant/owned queue differs");
        require(word(output->scratchJob1,1,0) == 7+delta && word(output->scratchJob2,1,0) == -9+delta/2 &&
                report.contextAfter.relationChangeMask[1] == uint32_t(delta ? 1 : 0) &&
                report.attitudes.size() == size_t(delta ? 1 : 0), "diplomacy matrix offsets or response deltas differ");
        auto expected = std::make_unique<Document>(*d);
        word(expected->scratchJob1,1,0,7+delta); word(expected->scratchJob2,1,0,-9+delta/2);
        require(bytes(*output) == bytes(*expected), "diplomacy altered other packed fields");
    }
    auto context = reactionContext(seedForRoll(1));
    context.relationChangeMask[1] = 1;
    require(ai.reactDiplomacy(*d,{1,0,32},context,*output,report,error) && !report.attitudes[0].applied &&
            bytes(*output) == sourceBytes && report.draws.size() == 2, "once-per-period attitude mask was ignored");
    context.relationChangeMask[1] = 0; d->options.playerSkill[1] = 4;
    require(ai.reactDiplomacy(*d,{1,0,32},context,*output,report,error) && !report.attitudes[0].applied,
            "player-skill4 attitude lock ignored");
    d->options.playerSkill[1] = 0; d->options.campaign = 6;
    require(ai.reactDiplomacy(*d,{1,0,32},context,*output,report,error) && !report.attitudes[0].applied,
            "campaign wildcard attitude lock ignored");
    d->options.campaign = 1; d->players[1].race = 1; // row{1,0,-20,1}, other race0.
    require(ai.reactDiplomacy(*d,{1,0,32},context,*output,report,error) && !report.attitudes[0].applied,
            "campaign specific race attitude lock ignored");
    d->options.campaign = 0; d->players[1].race = 0;
    word(d->scratchJob1,1,0,-2147483647-1); word(d->scratchJob2,1,0,-2147483647-1);
    require(ai.reactDiplomacy(*d,{1,0,32},context,*output,report,error) &&
            word(output->scratchJob1,1,0) == 50 && word(output->scratchJob2,1,0) == 50,
            "attitude must wrap signed32 before clamping, not saturate the addition");
    word(d->scratchJob1,1,0,-49); word(d->scratchJob2,1,0,-49);
    require(ai.reactDiplomacy(*d,{1,0,32},context,*output,report,error) &&
            word(output->scratchJob1,1,0) == -50 && word(output->scratchJob2,1,0) == -50,
            "attitude lower bound differs");
    context.pendingMessages.resize(kAiMessageCapacity);
    require(ai.reactDiplomacy(*d,{1,0,32},context,*output,report,error) && report.messages[0].outcome == AiMessageOutcome::Full &&
            report.contextAfter.pendingMessages == context.pendingMessages && report.draws.size() == 2 &&
            report.attitudes[0].applied, "full queue lost prior RNG/attitude effects or exceeded capacity41");
    context.pendingMessages.clear();
    require(ai.reactDiplomacy(*d,{1,2,32},context,*output,report,error) &&
            report.messages[0].outcome == AiMessageOutcome::NoHumanRecipient && report.contextAfter.pendingMessages.empty() &&
            report.draws.size() == 2, "AI-only recipient filter skipped earlier RNG or queued forbidden chat");
    // Signed dormant type counts as nonzero and <3 in the original filter.
    require(ai.reactDiplomacy(*d,{1,6,32},context,*output,report,error) &&
            report.messages[0].outcome == AiMessageOutcome::Queued, "queue human predicate lost signed-byte comparison");
    context.gameAborted = true;
    require(ai.reactDiplomacy(*d,{1,99,32},context,*output,report,error) && !report.handled && report.draws.empty() &&
            bytes(*output) == bytes(*d) && report.contextAfter == context, "game-aborted guard did not precede input reads/draws");
    context.gameAborted = false;
    require(ai.reactDiplomacy(*d,{1,99,30},context,*output,report,error) && !report.handled && report.draws.empty(),
            "unknown diplomacy category is not the original default return");
    const auto destinationBefore = bytes(*output); const auto savedReport = report;
    context.pendingMessages.resize(kAiMessageCapacity+1);
    require(!ai.reactDiplomacy(*d,{1,0,32},context,*output,report,error) && bytes(*output) == destinationBefore && report == savedReport,
            "oversize queue failure did not roll back destination/report");
    context.pendingMessages.clear(); d->players[1].race = -1;
    require(!ai.reactDiplomacy(*d,{1,0,32},context,*output,report,error) && bytes(*output) == destinationBefore && report == savedReport,
            "late chat table failure leaked earlier relation change or RNG");
    d->players[1].race = 0;
    require(ai.reactDiplomacy(*d,{1,0,31},context,*d,report,error), "in-place diplomacy failed");
    const auto nextContext = report.contextAfter;
    require(ai.reactDiplomacy(*d,{1,0,31},report.contextAfter,*d,report,error) &&
            report.contextAfter.pendingMessages.size() == nextContext.pendingMessages.size()+1 &&
            report.contextAfter.rng.counters.secondary15 == nextContext.rng.counters.secondary15+2,
            "report.contextAfter alias was invalidated before use");
}

void eventReactions() {
    auto d = fixture(); auto output = fixture(); AiSession ai; save::Error error; AiReactionReport report;
    require(ai.initializeAfterLoad(*d,error), "event AI setup failed");
    auto context = reactionContext(0);
    // Seed0 first secondary draw0 even; second21468 even; third9988.
    uint32_t step = 0; const auto first = secondaryStep(step), second = secondaryStep(step), third = secondaryStep(step);
    require((first&1u) == 0 && (second&1u) == 0, "manual event RNG oracle seed changed");
    require(ai.reactEvent(*d,{1,8,0,999},context,*output,report,error) && report.handled && report.draws.size() == 3 &&
            report.draws[0].value == first && report.draws[1].value == second && report.draws[2].value == third &&
            report.messages[0].message.category == 31 && report.messages[0].message.variant == int(third%26),
            "event chat order or extra1 actor semantics differ");
    require(ai.reactEvent(*d,{1,8,-1,0},context,*output,report,error) && report.draws.size() == 1 && report.messages.empty(),
            "negative event actor incorrectly skipped first random chat draw");
    require(ai.reactEvent(*d,{1,0x1f,-1,0},context,*output,report,error) && report.draws.empty(),
            "gratitude actor guard incorrectly consumed random draw");
    require(ai.reactEvent(*d,{1,0x1f,0,0},context,*output,report,error) && report.draws.size() == 2 &&
            report.attitudes[0].after == 4 && report.attitudes[0].baselineAfter == 2 && report.messages[0].message.category == 35,
            "gratitude relation/queue order differs");
    context.gameAborted = true; // Unlike00404cec,004047a0 has NO aborted guard.
    require(ai.reactEvent(*d,{1,0x3a,0,0x1e},context,*output,report,error) && report.draws.empty() &&
            report.attitudes[0].after == -50 && report.attitudes[0].baselineAfter == -50,
            "pact-break doubled penalty or absent Event abort guard differs");
    context.gameAborted = false;
    d->aiWarMask[1] = 0; word(d->scratchJob1,1,0,0); word(d->scratchJob2,1,0,0);
    require(ai.reactEvent(*d,{1,10,0,0},context,*output,report,error) && output->aiWarMask[1] == 1 &&
            report.attitudes[0].after == -20 && report.draws.size() == 1 &&
            report.messages.size() == 2 && report.messages[0].message == AiDiplomacyMessage{1,1,-1,0,{0,0,0}} &&
            report.messages[1].message == AiDiplomacyMessage{1,64,-1,2,{0,0,0}},
            "dependency-free new-war path or human semantic requests differ");
    // Type255 player6 participates in the signed human loop, but source AI2 does not.
    d->aiWarMask[1] = 1;
    require(ai.reactEvent(*d,{1,0x25,0,1234},context,*output,report,error) && report.draws.empty() &&
            report.messages[0].message == AiDiplomacyMessage{1,1,-1,5,{1234,0,0}},
            "already-war event25 semantic request payload differs");
    d->aiWarMask[1] = 4; // Draw0 passes1-in8 gate then unported old-war dissolution.
    const auto beforeOutput = bytes(*output); const auto beforeReport = report; const auto beforeSource = bytes(*d);
    require(!ai.reactEvent(*d,{1,10,0,0},context,*output,report,error) && bytes(*output) == beforeOutput &&
            bytes(*d) == beforeSource && report == beforeReport, "unsupported task-force branch leaked preceding effects");
    d->aiWarMask[1] = 0; d->players[1].relations[0] = 2;
    require(!ai.reactEvent(*d,{1,10,0,0},context,*output,report,error) && bytes(*output) == beforeOutput && report == beforeReport,
            "unsupported pact-break branch was approximated");
    require(!ai.reactEvent(*d,{1,0x72,0,2},context,*output,report,error) &&
            !ai.reactEvent(*d,{1,0x73,0,2},context,*output,report,error) && report == beforeReport,
            "negotiation was answered implicitly or leaked RNG");
    const auto odd = reactionContext(seedForRoll(1));
    require(ai.reactEvent(*d,{1,0x72,0,2},odd,*output,report,error) && report.draws.size() == 1 && report.messages.empty(),
            "actual skipped negotiation branch rejected or invented effects");
    d->options.allowAlliances = 1; d->players[1].relations[2] = 0x10; d->aiWarMask[1] = 0;
    require(ai.reactEvent(*d,{1,0x74,0,2},context,*output,report,error) && report.messages[0].message.category == 32 &&
            report.attitudes[0].after == -8 && report.draws.size() == 1, "event74 allied target branch differs");
    d->aiWarMask[1] = 4;
    require(ai.reactEvent(*d,{1,0x74,0,2},context,*output,report,error) && report.messages[0].message.category == 35 &&
            report.attitudes[0].after == 8, "event74 war target gratitude branch differs");
    require(ai.reactEvent(*d,{1,0x40,999,999},context,*output,report,error) && !report.handled && report.draws.empty() &&
            bytes(*output) == bytes(*d), "construction event40 original default invented AI effects");
}

void runtimeReactions() {
    auto d = fixture(); auto captured = fixture(); save::Error error; runtime::State state;
    require(state.prepare(*d,error), "runtime prepare for AI reaction failed");
    const auto army = state.armyById(101);
    const auto territory = state.territoryByIndex(1);
    const auto source = bytes(*d); const auto context = reactionContext(seedForRoll(1));
    AiReactionReport report;
    require(state.reactDiplomacy({1,0,32},context,report,error) &&
            state.stage() == runtime::Stage::EntitiesEdited && state.aiSession() && state.aiReactionContext() &&
            *state.aiReactionContext() == report.contextAfter && state.sessionRng() == report.contextAfter.rng &&
            state.armyById(101) == army && state.territoryByIndex(1) == territory && state.army(army) &&
            bytes(*d) == source, "runtime did not publish document/context/RNG atomically or changed identities/source");
    const auto after = bytes(*state.document()); const auto continuation = *state.aiReactionContext();
    const auto snapshot = state.aiSession()->snapshot(); const auto savedReport = report; const auto* pointer = state.document();
    require(!state.reactDiplomacy({1,0,32},context,report,error) && report == savedReport &&
            state.document() == pointer && bytes(*state.document()) == after &&
            *state.aiReactionContext() == continuation && state.sessionRng() == continuation.rng,
            "runtime allowed reaction context/RNG rewind or changed state on rejection");
    auto forged = continuation; forged.pendingMessages.clear();
    require(!state.reactDiplomacy({1,0,32},forged,report,error) && report == savedReport,
            "runtime allowed queue rewind with unchanged RNG");
    require(!state.reactDiplomacy({1,7,32},continuation,report,error) && report == savedReport &&
            state.aiSession()->snapshot() == snapshot && state.document() == pointer,
            "runtime invalid reaction mutated AI/document before failure");
    require(!state.capture(*captured,error) && !state.advanceTurn(error), "runtime exported or advanced partial reaction experiment");
    require(state.reactAiEvent({1,0x40,0,0},*state.aiReactionContext(),report,error) &&
            !report.handled && state.sessionRng() == continuation.rng && state.armyById(101) == army,
            "runtime event consumer failed on genuine default branch or invalidated identity");
    runtime::State moved = std::move(state);
    require(moved.aiReactionContext() && moved.aiSession() && moved.army(army) && !state.document() &&
            !state.aiReactionContext() && !state.aiSession(), "AI reaction owned state did not move with document");
    require(moved.prepare(*d,error) && !moved.aiReactionContext() && !moved.aiSession() &&
            !moved.army(army) && !moved.sessionRng().initialized,
            "new prepare retained old AI context/RNG or lifetime handles");
}

class OriginalPe {
    std::vector<uint8_t> bytes_; uint32_t imageBase_ = 0; size_t sections_ = 0; uint16_t count_ = 0;
    uint8_t u8(size_t at) const { require(at < bytes_.size(), "truncated original PE"); return bytes_[at]; }
    uint16_t u16(size_t at) const { return uint16_t(u8(at) | uint16_t(u8(at+1)) << 8); }
    uint32_t u32(size_t at) const { return uint32_t(u8(at)) | uint32_t(u8(at+1)) << 8 | uint32_t(u8(at+2)) << 16 | uint32_t(u8(at+3)) << 24; }
    size_t offset(uint32_t address) const {
        require(address >= imageBase_, "PE address below image base"); const auto rva = address-imageBase_;
        for (size_t i = 0; i < count_; ++i) {
            const auto at = sections_ + 40*i; const auto start = u32(at+12), size = u32(at+16);
            if (rva >= start && rva-start < size) {
                const auto result = size_t(u32(at+20)) + size_t(rva-start);
                require(result < bytes_.size(), "PE raw offset outside file"); return result;
            }
        }
        throw std::runtime_error("AI target has no backed PE section");
    }
public:
    explicit OriginalPe(const fs::path& path) {
        const auto size = fs::file_size(path); require(size >= 64 && size <= 16*1024*1024, "invalid original EXE size");
        bytes_.resize(size_t(size)); std::ifstream in(path,std::ios::binary);
        require(bool(in.read(reinterpret_cast<char*>(bytes_.data()),std::streamsize(bytes_.size()))), "cannot read original EXE");
        require(u16(0) == 0x5a4d, "original EXE is not MZ"); const size_t pe = u32(0x3c);
        require(u32(pe) == 0x4550 && u16(pe+24) == 0x10b, "original EXE is not PE32");
        count_ = u16(pe+6); imageBase_ = u32(pe+52); sections_ = pe+24+u16(pe+20);
        require(count_ > 0 && count_ < 100 && sections_ <= bytes_.size() && size_t(count_)*40 <= bytes_.size()-sections_, "invalid PE sections");
    }
    uint32_t word(uint32_t address) const { return u32(offset(address)); }
    uint8_t byte(uint32_t address) const { return u8(offset(address)); }
};
void canonicalPe(const fs::path& directory) {
    const auto path = directory/"DEADLOCK.EXE";
    if (directory.empty() || !fs::is_regular_file(path)) {
        std::cout << "AI session: optional original PE unavailable\n"; return;
    }
    OriginalPe pe(path);
    for (size_t f = 0; f < 5; ++f)
        require(pe.word(0x004b502cu + 3*24 + 4 + uint32_t(f)*4) == data::kAiType3.fn[f].addr,
                "personality function offsets differ from PE (name word is not a callback)");
    constexpr uint8_t ret8[]{0x55,0x8b,0xec,0x5d,0xc2,0x08,0x00};
    for (size_t m = 0; m < 6; ++m) {
        require(pe.word(0x004b508cu + uint32_t(m)*20) == uint32_t(data::kMinisterVtable[m].id) &&
                pe.word(0x004b5104u + uint32_t(m)*4) == uint32_t(data::kMinisterOrder[m]) &&
                pe.word(0x004b62f4u + uint32_t(m)*8) == uint32_t(data::kAiMinisterConfigDefault[m].kind) &&
                pe.word(0x004b62f8u + uint32_t(m)*8) == uint32_t(data::kAiMinisterConfigDefault[m].param),
                "minister table/order/config differs from original PE");
        for (size_t f = 0; f < 4; ++f) {
            const auto addr = pe.word(0x004b5090u + uint32_t(m)*20 + uint32_t(f)*4);
            require(addr == data::kMinisterVtable[m].fn[f].addr, "minister target differs from PE");
            for (size_t b = 0; b < sizeof(ret8); ++b) require(pe.byte(addr+uint32_t(b)) == ret8[b], "claimed minister RET actually performs work");
        }
    }
    constexpr uint32_t responseTables[]{0x4b5684,0x4b55d0,0x4b560c,0x4b5648,0x4b56c0};
    constexpr uint32_t probabilities[5][5]{{100,0,0,0,0},{0,100,0,0,0},{50,0,0,0,50},{50,0,0,0,50},{0,0,80,0,20}};
    constexpr uint32_t variants[5][7]{{26,26,26,26,26,26,27},{24,28,26,25,24,27,26},
        {27,26,26,26,27,26,25},{23,23,24,24,23,24,23},{20,20,20,20,20,20,20}};
    for (size_t category = 0; category < 5; ++category) {
        for (uint32_t band = 0; band < 3; ++band) for (uint32_t option = 0; option < 5; ++option)
            require(pe.word(responseTables[category] + band*20 + option*4) == probabilities[category][option],
                    "diplomacy probability row differs from original PE");
        for (uint32_t race = 0; race < 7; ++race)
            require(pe.word(0x4ca3b4u + uint32_t(category+31)*56 + race*8) == variants[category][race],
                    "chat variant count differs from original PE");
    }
    // Exercise the module's lock predicate against all43*7*7 original rows,
    // independently reading the PE rather than duplicating its516 integers.
    auto d = fixture(); auto output = fixture(); AiSession ai; save::Error error; AiReactionReport report;
    require(ai.initializeAfterLoad(*d,error), "campaign lock oracle initialization failed");
    const auto context = reactionContext(seedForRoll(1));
    for (int campaign = 0; campaign < 43; ++campaign) for (int race = 0; race < 7; ++race) for (int other = 0; other < 7; ++other) {
        d->options.campaign = campaign; d->players[1].race = int8_t(race); d->players[0].race = int8_t(other);
        bool locked = false;
        if (campaign) for (uint32_t row = 0; row < 3; ++row) {
            const uint32_t at = 0x4b57c0u + uint32_t(campaign)*48 + row*16;
            const auto a = std::bit_cast<int32_t>(pe.word(at)), b = std::bit_cast<int32_t>(pe.word(at+4));
            locked |= (a == race || a == 7) && (b == other || b == 7) && pe.word(at+12) != 0;
        }
        require(ai.reactDiplomacy(*d,{1,0,31},context,*output,report,error) && report.attitudes[0].applied == !locked,
                "campaign attitude lock predicate differs from original PE");
    }
    std::cout << "AI session: all24 minister RET8 bodies and tables match original PE\n";
}
std::vector<std::string> scenarioNames(const fs::path& path) {
    const auto size = fs::file_size(path); require(size >= 4 && size <= save::kMaxFileBytes, "invalid corpus index size");
    std::ifstream in(path,std::ios::binary); uint8_t raw[4]{};
    require(bool(in.read(reinterpret_cast<char*>(raw),4)), "cannot read corpus index");
    const uint32_t n = uint32_t(raw[0]) | uint32_t(raw[1]) << 8 | uint32_t(raw[2]) << 16 | uint32_t(raw[3]) << 24;
    require(n <= (size-4)/12, "truncated corpus index"); std::vector<std::string> names;
    for (uint32_t i = 0; i < n; ++i) { char entry[12]{}; require(bool(in.read(entry,12)), "cannot read corpus entry"); names.emplace_back(entry,std::find(entry,entry+8,'\0')); }
    return names;
}
void corpusOne(const Document& original) {
    const auto before = bytes(original); auto d = std::make_unique<Document>(); LoadCoreReport core; save::Error error;
    if (!normalizeLoadCore(original,{},*d,core,error)) throw std::runtime_error(error.message);
    const auto normalized = bytes(*d); AiSession first,second;
    if (!first.initializeAfterLoad(*d,error) || !second.initializeAfterLoad(*d,error)) throw std::runtime_error(error.message);
    require(first.snapshot() == second.snapshot() && bytes(*d) == normalized && bytes(original) == before,
            "corpus AI initialization was nondeterministic or mutated source");
    AiDispatchReport report; const auto initialized = first.snapshot();
    for (size_t p = 0; p < kMaxPlayers; ++p) if (d->players[p].type == 3) {
        const auto& ai = initialized.data.ai[p];
        require(ai.initialized && ai.initializations == 1 && ai.strategyCountdown == 40,
                "corpus final AInit values differ");
        for (int phase = 0; phase < 4; ++phase)
            require(first.dispatch({int(p),AiOperation::MinisterPhase,phase},report,error) && report.invocations.size() == 6,
                    "corpus minister binding dispatch failed");
    }
    for (const auto& army : d->armies) {
        bool scout = false; if (!canScoutOwned(*d,army,scout,error)) throw std::runtime_error(error.message);
    }
}
void optionalCorpus(const fs::path& directory) {
    if (directory.empty() || !fs::is_regular_file(directory/"TUTORIAL.SAV")) {
        std::cout << "AI session: optional corpus unavailable\n"; return;
    }
    size_t count = 0;
    for (const char* name : {"TUTORIAL.SAV","Saves/AUTOSAVE.SAV","Campaign/AUTOSAVE.CPN","Campaign/ChCht001.CPN"}) {
        if (!fs::is_regular_file(directory/name)) continue;
        auto d = std::make_unique<Document>(); save::Error error;
        if (!save::readDocument(directory/name,*d,error)) throw std::runtime_error(error.message);
        try { corpusOne(*d); } catch (const std::exception& e) { throw std::runtime_error(std::string(name)+": "+e.what()); } ++count;
    }
    if (fs::is_regular_file(directory/"LEVELS.HDX") && fs::is_regular_file(directory/"LEVELS.HDD"))
        for (const auto& name : scenarioNames(directory/"LEVELS.HDX")) {
            auto d = std::make_unique<Document>(); save::Error error;
            if (!save::readScenario(directory/"LEVELS",name,*d,error)) throw std::runtime_error(error.message);
            try { corpusOne(*d); } catch (const std::exception& e) { throw std::runtime_error(name+": "+e.what()); } ++count;
        }
    std::cout << "AI session corpus: " << count << " documents, source preserved\n";
}
} // namespace
int main(int argc, char** argv) {
    try {
        rtl::srand(0xf1234567u); (void)rtl::lrand(); gg.rng2Seed = 0xabcd0123;
        const auto low = rtl::seed(), high = rtl::seedHi();
        const auto globals = std::make_unique<GameGlobals>(gg); const auto game = std::make_unique<GameState>(gs);
        initializationAndDispatch(); removals(); additions(); pooledTaskForces(); scoutQueries(); maintainJobs();
        diplomacyReactions(); eventReactions(); runtimeReactions();
        const fs::path directory = argc > 1 ? fs::path(argv[1]) : fs::path{};
        canonicalPe(directory); optionalCorpus(directory);
        require(rtl::seed() == low && rtl::seedHi() == high && std::memcmp(&gg,globals.get(),sizeof(gg)) == 0 &&
                std::memcmp(&gs,game.get(),sizeof(gs)) == 0, "owned AI helpers changed globals or RNG");
        std::cout << "AI session tests passed\n"; return 0;
    } catch (const std::exception& e) { std::cerr << "AI session: " << e.what() << '\n'; return 1; }
}
