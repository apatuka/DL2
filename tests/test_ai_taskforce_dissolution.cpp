// Task-force dissolution 0040beb4/0040b000/0040afa4 on an owned Document.
// Expected states are oracles DERIVED from the decompiled code and disassembly
// (plus PE byte checks below); none is an observed run of the original game.
#include "game/ai_taskforce_dissolution.h"
#include "game/army_pool.h"
#include "game/data_tables.h"
#include "game/globals.h"
#include "game/load_profile.h"
#include "game/rtl_compat.h"
#include "game/save_files.h"
#include <algorithm>
#include <array>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

namespace {
using namespace dl2;
using namespace dl2::simulation;
using save::Document;
using Action = TaskForceDissolutionAction;
namespace fs = std::filesystem;

void require(bool condition, const std::string& message) {
    if (!condition) throw std::runtime_error(message);
}
std::vector<uint8_t> bytes(const Document& d) {
    std::vector<uint8_t> result; save::Error error;
    if (!save::encode(d, result, error)) throw std::runtime_error(error.message);
    return result;
}
// Full owned-state snapshot, including invalid/non-archival documents and
// runtime-only territory tails. Never erase deferred bindings just to encode.
std::vector<uint8_t> fingerprint(const Document& d) {
    std::vector<uint8_t> result;
    auto scalar = [&]<class T>(const T& value) {
        static_assert(std::is_trivially_copyable_v<T>);
        const auto* raw = reinterpret_cast<const uint8_t*>(&value);
        result.insert(result.end(), raw, raw + sizeof(T));
    };
    auto sequence = [&](const auto& values) {
        scalar(values.size()); for (const auto& value : values) scalar(value);
    };
    scalar(d.header); scalar(d.options); scalar(d.world); scalar(d.players);
    sequence(d.localList); scalar(d.raceStats); scalar(d.techs);
    for (const auto& list : d.ministerJobs) sequence(list);
    scalar(d.events.size());
    for (const auto& event : d.events) { scalar(event.record); sequence(event.text); }
    sequence(d.tiles); sequence(d.buildings); sequence(d.armies);
    scalar(d.territories.size());
    for (const auto& territory : d.territories) {
        scalar(territory.data); for (const auto& queue : territory.queues) sequence(queue);
    }
    scalar(d.jobs); scalar(d.aiWarMask); scalar(d.scratchJob1); scalar(d.scratchJob2);
    scalar(d.continents); scalar(d.randomEvents); scalar(d.scores); scalar(d.spies);
    scalar(d.blackMarket); sequence(d.mapTerritories); sequence(d.trailing);
    scalar(d.armyPool.has_value());
    if (d.armyPool) {
        sequence(d.armyPool->liveIds); sequence(d.armyPool->freeSlots); scalar(d.armyPool->jobSlots);
    }
    return result;
}
bool same(const Document& a, const Document& b) {
    return fingerprint(a) == fingerprint(b);
}
int32_t word(const Job& job, size_t k) {
    int32_t value; std::memcpy(&value, job.unk_88 + k * 4, 4); return value;
}
void word(Job& job, size_t k, int32_t value) { std::memcpy(job.unk_88 + k * 4, &value, 4); }
bool zeroJob(const Job& job) {
    const auto* raw = reinterpret_cast<const uint8_t*>(&job);
    return std::all_of(raw, raw + sizeof(Job), [](uint8_t b) { return b == 0; });
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
    std::memset(reinterpret_cast<uint8_t*>(&t) + kTerritorySavedBytes, 0xa7,
                sizeof(Territory) - kTerritorySavedBytes);
    for (size_t p = 0; p < kMaxPlayers; ++p) {
        d->players[p].type = p == 0 ? 1 : p < 3 ? 3 : 0;
        d->players[p].index = uint8_t(p); d->players[p].race = int8_t(p);
        d->ministerJobs[p].resize(1); d->ministerJobs[p][0].type = 1;
        d->aiWarMask[p] = 0xabcd0000u + uint32_t(p);
        for (size_t j = 0; j < kJobsPerPlayer; ++j) {
            // Opaque words everywhere detect stray writes into foreign records.
            auto& job = d->jobs[p][j];
            job.owner = int16_t(p); job.goal = int32_t(100 + j); job.status = int32_t(p);
            job.targetPlayer = -1; job.param1 = int16_t(0x7000 + j); job.param2 = int16_t(j);
            job.strengthWanted = int32_t(1000 * p + j);
            std::memset(job.unk_18, int(0x50 + p), sizeof(job.unk_18));
        }
    }
    d->armies.resize(32);
    for (size_t i = 0; i < d->armies.size(); ++i) {
        auto& army = d->armies[i];
        army.id = i == 31 ? uint16_t(65000) : uint16_t(101 + i);
        army.type = 1; army.owner = 1; army.unitClass = 1; army.health = 80;
        army.territory.raw = army.dest.raw = army.origin.raw = 1;
        army.unk_04 = 0xbaba; army.unk_2a = -32767; army.experience = int16_t(10 * i);
        std::memset(army.name, int('A' + i), sizeof(army.name));
    }
    d->scratchJob1.armies[3].raw = 0xdeadbeef; d->trailing = {0xaa, 0, 0xff};
    save::Error error; require(save::validate(*d, error), "invalid dissolution fixture: " + error.message);
    return d;
}
uint16_t id(const Document& d, size_t army) { return d.armies[army].id; }
// One-based Army.job and a historical non-pointer word, like the AI fixture.
void bind(Document& d, int p, int j, int slot, size_t army) {
    d.jobs[size_t(p)][size_t(j)].armyIds[slot] = d.armies[army].id;
    d.jobs[size_t(p)][size_t(j)].armies[slot].raw = 0xf0000000u + uint32_t(army);
    d.armies[army].owner = int8_t(p); d.armies[army].job = int16_t(j + 1);
}
TaskForceDissolutionReport sentinel() {
    TaskForceDissolutionReport r; r.player = 6; r.jobIndex = 44; r.parentJobIndex = 3;
    TaskForceDissolutionStep s; s.action = Action::ParentLinkCleared; s.slot = 9; s.linkBefore = 77;
    s.removal.detachedArmyIds = {5, 6}; r.steps = {s, s}; return r;
}
TaskForceDissolutionStep released(int slot, uint32_t army, int16_t before) {
    TaskForceDissolutionStep s; s.action = Action::ArmyReleased; s.slot = slot; s.armyId = army;
    s.armyJobBefore = before; s.armyJobAfter = 0; return s;
}
TaskForceEditReport edit(TaskForceOutcome outcome, uint32_t army, int player, int job, int slot,
                         std::vector<uint32_t> detached = {}) {
    TaskForceEditReport r; r.outcome = outcome; r.armyId = army; r.player = player; r.jobIndex = job;
    r.slot = slot; r.detachedArmyIds = std::move(detached); return r;
}
TaskForceDissolutionStep transferred(int slot, uint32_t army, int16_t before, int16_t after,
                                     TaskForceEditReport removal, TaskForceEditReport insertion) {
    TaskForceDissolutionStep s; s.action = Action::ArmyTransferred; s.slot = slot; s.armyId = army;
    s.armyJobBefore = before; s.armyJobAfter = after;
    s.removal = std::move(removal); s.insertion = std::move(insertion); return s;
}
TaskForceDissolutionStep reparented(int k, int child, int32_t before, int rootSlot) {
    TaskForceDissolutionStep s; s.action = Action::ChildReparented; s.slot = k; s.jobIndex = child;
    s.linkBefore = before; s.linkAfter = 1; s.rootSlot = rootSlot; return s;
}
TaskForceDissolutionStep cleared(int k, int parent, int32_t before) {
    TaskForceDissolutionStep s; s.action = Action::ParentLinkCleared; s.slot = k; s.jobIndex = parent;
    s.linkBefore = before; s.linkAfter = 0; return s;
}

// Runs both a separate destination and source==destination; both must equal expected.
void expectSuccess(const Document& source, int p, int j, const Document& expected, int parent,
                   const std::vector<TaskForceDissolutionStep>& steps, const char* what) {
    const auto before = fingerprint(source);
    auto destination = fixture(); destination->options.turn = 99; // Must be fully replaced.
    TaskForceDissolutionReport report = sentinel();
    save::Error error{save::ErrorCode::Io, 42, "stale"};
    require(dissolveTaskForce(source, p, j, *destination, report, error),
            std::string(what) + ": dissolution failed: " + error.message);
    require(error.code == save::ErrorCode::None && error.message.empty() && error.offset == 0,
            std::string(what) + ": success left a stale error");
    require(fingerprint(source) == before, std::string(what) + ": const source changed");
    require(report.player == p && report.jobIndex == j && report.parentJobIndex == parent,
            std::string(what) + ": report identity differs");
    require(report.steps.size() == steps.size(),
            std::string(what) + ": step count " + std::to_string(report.steps.size()) +
            " differs from " + std::to_string(steps.size()));
    for (size_t i = 0; i < steps.size(); ++i)
        require(report.steps[i] == steps[i], std::string(what) + ": step " + std::to_string(i) + " differs");
    require(zeroJob(destination->jobs[size_t(p)][size_t(j)]), std::string(what) + ": dissolved job not fully zeroed");
    require(same(*destination, expected), std::string(what) + ": document differs from derived oracle");
    auto alias = std::make_unique<Document>(source); TaskForceDissolutionReport aliasReport;
    require(dissolveTaskForce(*alias, p, j, *alias, aliasReport, error) && aliasReport == report &&
            same(*alias, expected), std::string(what) + ": source==destination result differs");
}
void expectFailure(const Document& source, int p, int j, const char* what) {
    const auto before = fingerprint(source);
    auto destination = fixture(); destination->options.turn = 99; const auto kept = fingerprint(*destination);
    auto report = sentinel(); const auto keep = report;
    save::Error error{save::ErrorCode::Io, 42, "stale"};
    require(!dissolveTaskForce(source, p, j, *destination, report, error),
            std::string(what) + ": out-of-domain dissolution succeeded");
    require(error.code != save::ErrorCode::None && !error.message.empty() && error.message != "stale",
            std::string(what) + ": failure did not report an explicit error");
    require(fingerprint(source) == before && fingerprint(*destination) == kept && report == keep,
            std::string(what) + ": failure changed source, destination or report");
    auto alias = std::make_unique<Document>(source);
    require(!dissolveTaskForce(*alias, p, j, *alias, report, error) && report == keep &&
            fingerprint(*alias) == before, std::string(what) + ": aliased failure was not rolled back");
}

void canonicalDomains() {
    // Canonical UnitDef+0x11 values relied on below (verified against the PE when present).
    constexpr std::pair<int, int> domains[]{{1,1},{9,3},{12,2},{13,2},{27,6},{37,1},{38,1}};
    for (const auto& [type, domain] : domains)
        require(data::kUnitTypes[type].domain == domain, "canonical domain table changed: test premises invalid");
    require(data::kUnitTypes[12].unitClass == 4, "type12 is no longer the canonical sea transport");
}

void noParentReleases() {
    auto d = fixture();
    auto& army1 = d->armies[1]; army1.type = 12; army1.unitClass = 4;
    army1.cargo[0].raw = id(*d, 2); army1.cargo[1].raw = id(*d, 3);
    d->armies[4].type = 9; d->armies[4].unitClass = 3;
    bind(*d,1,5,0,0); bind(*d,1,5,3,1); bind(*d,1,5,15,4); bind(*d,1,5,7,5); bind(*d,1,5,9,6);
    d->armies[5].job = 0;              // Already detached: still written to zero.
    bind(*d,1,7,0,2);                  // Transport cargo in another job: NOT recursed.
    bind(*d,1,7,4,6); d->armies[6].job = 8; // Also listed by job7 and pointing there.
    auto expected = std::make_unique<Document>(*d);
    for (size_t army : {0, 1, 4, 5, 6}) expected->armies[army].job = 0;
    std::memset(&expected->jobs[1][5], 0, sizeof(Job)); // owner word too
    expectSuccess(*d, 1, 5, *expected, -1, {
        released(0, id(*d,0), 6), released(3, id(*d,1), 6), released(7, id(*d,5), 0),
        released(9, id(*d,6), 8), released(15, id(*d,4), 6)}, "no parent");
    require(expected->armies[2].job == 8 && expected->jobs[1][7].armyIds[4] == id(*d,6) &&
            expected->jobs[1][5].owner == 0, "oracle premise: cargo/foreign listing kept, owner cleared");
}

void parentTransfers() {
    auto d = fixture();
    auto& parent = d->jobs[1][2];
    bind(*d,1,2,0,10); bind(*d,1,2,2,11);
    word(parent,0,6); word(parent,1,9); word(parent,4,6); word(parent,14,6); // repeated links
    d->jobs[1][5].parentJob = 3;
    d->armies[0].unitClass = 4;                                   // saved class says transport
    d->armies[1].type = 12; d->armies[1].unitClass = 1;           // saved class says infantry
    d->armies[1].cargo[0].raw = id(*d,2); d->armies[1].cargo[1].raw = id(*d,7);
    d->armies[3].type = 9;  d->armies[3].unitClass = 3;           // air
    d->armies[4].type = 27; d->armies[4].unitClass = 12;          // amphibious AAV, domain6
    d->armies[5].type = 38; d->armies[5].unitClass = 20;          // sea mine, canonical domain1
    d->armies[6].type = 13; d->armies[6].unitClass = 5;           // sea
    for (int s = 0; s < 7; ++s) bind(*d,1,5,s,size_t(s));
    bind(*d,1,7,0,7);                                             // other cargo stays in job7
    auto expected = std::make_unique<Document>(*d);
    auto& p = expected->jobs[1][2];
    const std::array<std::pair<int,size_t>,3> inserted{{{1,0},{3,2},{4,5}}};
    for (const auto& [slot, army] : inserted) {
        p.armyIds[slot] = id(*d,army); p.armies[slot].raw = 0; expected->armies[army].job = 3;
    }
    for (size_t army : {1, 3, 4, 6}) expected->armies[army].job = 0;
    word(p,0,0); word(p,4,0); word(p,14,0);
    std::memset(&expected->jobs[1][5], 0, sizeof(Job));
    auto move = [&](int slot, size_t army, int parentSlot) {
        return transferred(slot, id(*d,army), 6, 3,
            edit(TaskForceOutcome::Removed, id(*d,army), 1, 5, slot, {id(*d,army)}),
            edit(TaskForceOutcome::Added, id(*d,army), 1, 2, parentSlot));
    };
    expectSuccess(*d, 1, 5, *expected, 2, {
        move(0,0,1), released(1,id(*d,1),6), move(2,2,3), released(3,id(*d,3),6),
        released(4,id(*d,4),6), move(5,5,4), released(6,id(*d,6),6),
        cleared(0,2,6), cleared(4,2,6), cleared(14,2,6)}, "parent transfers");
    require(expected->armies[7].job == 8 && expected->jobs[1][7].armyIds[0] == id(*d,7),
            "oracle premise: type12 release must not recurse into cargo");
}

void parentOutcomes() {
    // Full parent: removal stands, insertion does not happen, Army.job stays zero.
    auto d = fixture();
    for (int s = 0; s < 16; ++s) bind(*d,1,2,s,size_t(10 + s));
    d->jobs[1][5].parentJob = 3; bind(*d,1,5,0,0); bind(*d,1,5,1,1);
    auto expected = std::make_unique<Document>(*d);
    expected->armies[0].job = expected->armies[1].job = 0;
    std::memset(&expected->jobs[1][5], 0, sizeof(Job));
    auto full = [&](int slot, size_t army) {
        return transferred(slot, id(*d,army), 6, 0,
            edit(TaskForceOutcome::Removed, id(*d,army), 1, 5, slot, {id(*d,army)}),
            edit(TaskForceOutcome::Full, id(*d,army), 1, 2, -1));
    };
    expectSuccess(*d, 1, 5, *expected, 2, {full(0,0), full(1,1)}, "full parent");
    // Full returns before addArmyToTaskForce's owner arithmetic, as 0040b0c0 does.
    d->jobs[1][2].owner = -1; expected->jobs[1][2].owner = -1;
    expectSuccess(*d, 1, 5, *expected, 2, {full(0,0), full(1,1)}, "full parent with foreign owner word");

    // AlreadyPresent, already-detached army and Army.job naming another job.
    d = fixture();
    bind(*d,1,2,0,8);
    bind(*d,1,5,0,8);                         // listed by parent and dissolved job, job -> 6
    bind(*d,1,5,1,9); d->armies[9].job = 0;   // AlreadyDetached removal
    bind(*d,1,7,5,12); bind(*d,1,5,2,12);     // listed by job7 and job5...
    d->armies[12].job = 8;                    // ...but Army.job follows job7
    d->jobs[1][5].parentJob = 3;
    expected = std::make_unique<Document>(*d);
    expected->armies[8].job = 0;              // stays listed in parent slot0
    expected->jobs[1][2].armyIds[1] = id(*d,9); expected->jobs[1][2].armies[1].raw = 0; expected->armies[9].job = 3;
    expected->jobs[1][7].armyIds[5] = 0; expected->jobs[1][7].armies[5].raw = 0;
    expected->jobs[1][2].armyIds[2] = id(*d,12); expected->jobs[1][2].armies[2].raw = 0; expected->armies[12].job = 3;
    std::memset(&expected->jobs[1][5], 0, sizeof(Job));
    expectSuccess(*d, 1, 5, *expected, 2, {
        transferred(0, id(*d,8), 6, 0, edit(TaskForceOutcome::Removed, id(*d,8), 1, 5, 0, {id(*d,8)}),
                    edit(TaskForceOutcome::AlreadyPresent, id(*d,8), 1, 2, 0)),
        transferred(1, id(*d,9), 0, 3, edit(TaskForceOutcome::AlreadyDetached, id(*d,9), 1, -1, -1),
                    edit(TaskForceOutcome::Added, id(*d,9), 1, 2, 1)),
        transferred(2, id(*d,12), 8, 3, edit(TaskForceOutcome::Removed, id(*d,12), 1, 7, 5, {id(*d,12)}),
                    edit(TaskForceOutcome::Added, id(*d,12), 1, 2, 2))}, "present/detached/foreign-job outcomes");
    require(expected->jobs[1][2].armyIds[0] == id(*d,8) && expected->armies[8].job == 0,
            "oracle premise: AlreadyPresent leaves a listed army detached");
}

void childLinks() {
    auto d = fixture(); auto& job = d->jobs[1][5]; auto& root = d->jobs[1][0];
    word(job,0,10); word(job,2,11); word(job,3,10); word(job,14,12);
    word(root,0,20); word(root,2,21);
    d->jobs[1][9].parentJob = 6; d->jobs[1][10].parentJob = 6; d->jobs[1][11].parentJob = 0;
    auto expected = std::make_unique<Document>(*d); auto& r = expected->jobs[1][0];
    word(r,1,10); word(r,3,11); word(r,4,10); word(r,5,12);
    for (int child : {9, 10, 11}) expected->jobs[1][size_t(child)].parentJob = 1;
    std::memset(&expected->jobs[1][5], 0, sizeof(Job));
    expectSuccess(*d, 1, 5, *expected, -1, {
        reparented(0,9,6,1), reparented(2,10,6,3), reparented(3,9,1,4), reparented(14,11,0,5)},
        "child links and repeated link");
}

void fullRootBeforeParentClear() {
    // Parent IS job0 and its list is full: children receive parent1 without a
    // job0 word; the word freed afterwards by 0040afa4 is not reused.
    auto d = fixture(); auto& root = d->jobs[1][0];
    for (size_t k = 0; k < 15; ++k) word(root, k, int32_t(31 + k));
    word(root,7,6);
    auto& job = d->jobs[1][5]; job.parentJob = 1; word(job,0,10); word(job,1,12);
    d->jobs[1][9].parentJob = 6; d->jobs[1][11].parentJob = 6;
    d->jobs[1][11].owner = 3;  // Never consulted: no job0 word is written for it.
    auto expected = std::make_unique<Document>(*d);
    expected->jobs[1][9].parentJob = expected->jobs[1][11].parentJob = 1;
    word(expected->jobs[1][0],7,0);
    std::memset(&expected->jobs[1][5], 0, sizeof(Job));
    expectSuccess(*d, 1, 5, *expected, 0, {
        reparented(0,9,6,-1), reparented(1,11,6,-1), cleared(7,0,6)}, "full job0 child list");
}

void dissolveRoot() {
    // 00403350 can dissolve job0 itself: 0040b000 fills the words read later.
    auto d = fixture(); auto& root = d->jobs[1][0];
    word(root,0,5); bind(*d,1,0,0,0);
    auto expected = std::make_unique<Document>(*d);
    expected->armies[0].job = 0; expected->jobs[1][4].parentJob = 1;
    std::memset(&expected->jobs[1][0], 0, sizeof(Job));
    std::vector<TaskForceDissolutionStep> steps{released(0,id(*d,0),1)};
    for (int k = 0; k < 15; ++k) steps.push_back(reparented(k, 4, k ? 1 : 0, k < 14 ? k + 1 : -1));
    expectSuccess(*d, 1, 0, *expected, -1, steps, "dissolving job0");
}

void selfLinks() {
    // Self child: reparenting rewrites this job's parentJob, but the parent was
    // resolved before any effect, so the ORIGINAL parent loses its link.
    auto d = fixture(); auto& job = d->jobs[1][5];
    job.parentJob = 3; word(job,0,6); word(d->jobs[1][2],3,6);
    auto expected = std::make_unique<Document>(*d);
    word(expected->jobs[1][0],0,6); word(expected->jobs[1][2],3,0);
    std::memset(&expected->jobs[1][5], 0, sizeof(Job));
    expectSuccess(*d, 1, 5, *expected, 2, {reparented(0,5,3,0), cleared(3,2,6)}, "self child link");

    // Self parent: a land army is removed then reinserted into the same job,
    // keeping Army.job6 that refers to the record zeroed at the end.
    d = fixture(); auto& self = d->jobs[1][5];
    self.parentJob = 6; word(self,5,6);
    d->armies[0].type = 13; bind(*d,1,5,0,0); bind(*d,1,5,2,1);
    expected = std::make_unique<Document>(*d);
    expected->armies[0].job = 0; expected->armies[1].job = 6;
    word(expected->jobs[1][0],0,6);
    std::memset(&expected->jobs[1][5], 0, sizeof(Job));
    expectSuccess(*d, 1, 5, *expected, 5, {
        released(0,id(*d,0),6),
        transferred(2,id(*d,1),6,6, edit(TaskForceOutcome::Removed,id(*d,1),1,5,2,{id(*d,1)}),
                    edit(TaskForceOutcome::Added,id(*d,1),1,5,1)),
        reparented(5,5,6,0), cleared(5,5,6)}, "self parent");
}

void parentAddressArithmetic() {
    // 0040afa4 compares 32-bit addresses through the PARENT's owner word.
    auto d = fixture(); auto& job = d->jobs[2][4]; job.parentJob = 8;
    auto& parent = d->jobs[2][7]; parent.owner = 1;
    constexpr int32_t kWrap = int32_t(1) << 30;
    const int32_t words[]{5, 55, 55 + kWrap, 55 - kWrap, 55 + (kWrap >> 1), -1, 105};
    for (size_t k = 0; k < std::size(words); ++k) word(parent, k, words[k]);
    auto expected = std::make_unique<Document>(*d);
    for (size_t k : {1, 2, 3}) word(expected->jobs[2][7], k, 0);
    std::memset(&expected->jobs[2][4], 0, sizeof(Job));
    expectSuccess(*d, 2, 4, *expected, 7, {
        cleared(1,7,55), cleared(2,7,55 + kWrap), cleared(3,7,55 - kWrap)}, "parent address arithmetic");
    // Same owner: only the plain one-based index (and its 2^30 aliases) match.
    word(d->jobs[2][7],0,5); d->jobs[2][7].owner = 2;
    expected = std::make_unique<Document>(*d);
    word(expected->jobs[2][7],0,0);
    std::memset(&expected->jobs[2][4], 0, sizeof(Job));
    expectSuccess(*d, 2, 4, *expected, 7, {cleared(0,7,5)}, "parent same-owner link");
}

void freeRecords() {
    // 0040ad88 recycles free jobs whose owner word is still zero for players>0.
    auto d = fixture(); auto& job = d->jobs[3][9];
    job.owner = 0; job.goal = 77; job.destination.raw = 1; job.armies[4].raw = 0x12345678;
    auto expected = std::make_unique<Document>(*d);
    std::memset(&expected->jobs[3][9], 0, sizeof(Job));
    expectSuccess(*d, 3, 9, *expected, -1, {}, "free record with stale owner");
    // A historical Job.armies word alone is NOT a reference.
    require(expected->jobs[3][9].armies[4].raw == 0, "oracle premise");
    // An already-zero record still publishes a candidate equal to the source.
    auto zero = fixture(); std::memset(&zero->jobs[4][1], 0, sizeof(Job));
    expectSuccess(*zero, 4, 1, *zero, -1, {}, "all-zero record");
}

void domainErrors() {
    auto base = [] {
        auto d = fixture(); auto& job = d->jobs[1][5];
        job.parentJob = 3; bind(*d,1,5,0,0); bind(*d,1,5,1,1); bind(*d,1,5,2,2);
        word(job,0,10); word(job,1,11); word(d->jobs[1][2],0,6);
        return d;
    };
    {   // The unchanged base is in-domain: the failures below are late and isolated.
        auto d = base(); TaskForceDissolutionReport report; save::Error error;
        auto out = fixture();
        require(dissolveTaskForce(*d,1,5,*out,report,error) && report.steps.size() == 6,
                "domain-error base case should succeed");
    }
    for (const auto& [p, j] : {std::pair{-1,5}, {7,5}, {1,-1}, {1,50}})
        expectFailure(*base(), p, j, "player/job index outside array");
    {   auto d = base(); d->armies[3].owner = 2; bind(*d,1,5,15,3); d->armies[3].owner = 2;
        expectFailure(*d, 1, 5, "late foreign-owner army (0040aebc deferred)"); }
    for (int32_t bad : {51, 0x7fffffff, -3, int32_t(0x80000000u)}) {
        auto d = base(); word(d->jobs[1][5],2,bad);
        expectFailure(*d, 1, 5, "late child link outside owner array");
    }
    {   auto d = base(); word(d->jobs[1][5],2,13); d->jobs[1][12].owner = 0;
        expectFailure(*d, 1, 5, "late child owner would write cross-array job0 link"); }
    {   auto d = base(); d->jobs[1][0].owner = 4;
        expectFailure(*d, 1, 5, "job0 owner would write cross-array parent link"); }
    {   auto d = base(); d->jobs[1][2].owner = 0;
        expectFailure(*d, 1, 5, "insertion into parent with foreign owner word"); }
    {   auto d = base(); d->armies[1].job = 8;   // job7 does not list it
        expectFailure(*d, 1, 5, "removal through inconsistent Army.job"); }
    {   auto d = base(); d->armies[2].job = 51;
        expectFailure(*d, 1, 5, "removal through out-of-array Army.job"); }
    for (int32_t bad : {51, -2, 0x7fffffff}) {
        auto d = base(); d->jobs[1][5].parentJob = bad;
        expectFailure(*d, 1, 5, "parent index outside owner array");
    }
    {   auto d = base(); d->jobs[1][5].owner = 2;
        expectFailure(*d, 1, 5, "referenced job with foreign owner word"); }
    {   auto d = fixture(); d->jobs[1][5].owner = 0; word(d->jobs[1][5],3,7);
        expectFailure(*d, 1, 5, "child-only job with foreign owner word"); }
    {   auto d = fixture(); d->jobs[1][5].owner = 0; d->jobs[1][5].armyIds[4] = id(*d,0);
        expectFailure(*d, 1, 5, "army-only job with foreign owner word"); }
    {   auto d = base(); d->jobs[1][5].armyIds[9] = 4321; // unresolved: archival validation rejects it
        expectFailure(*d, 1, 5, "unresolved army ID"); }
    {   auto d = base(); d->header.isMap = 1;
        expectFailure(*d, 1, 5, "reduced map document"); }
}

void determinism() {
    auto d = fixture(); d->jobs[1][5].parentJob = 3;
    for (int s = 0; s < 5; ++s) bind(*d,1,5,s,size_t(s));
    word(d->jobs[1][5],0,10); word(d->jobs[1][2],0,6);
    auto a = std::make_unique<Document>(), b = std::make_unique<Document>();
    TaskForceDissolutionReport ra, rb; save::Error error;
    require(dissolveTaskForce(*d,1,5,*a,ra,error) && dissolveTaskForce(*d,1,5,*b,rb,error) &&
            ra == rb && same(*a,*b), "repeated dissolution is not deterministic");
    // Reusing the published result: a second dissolution of the zeroed record is a no-op.
    TaskForceDissolutionReport again;
    require(dissolveTaskForce(*a,1,5,*a,again,error) && again.steps.empty() && same(*a,*b),
            "dissolving the cleared record changed state");
}

TaskForceDissolutionStep pooled(TaskForceDissolutionStep step, uint32_t cell) {
    step.poolSlot = cell; return step;
}
void pool(Document& d) {
    save::Error error; require(ensureArmyPool(d, error), "cannot initialize dissolution pool: " + error.message);
}
void retire(Document& d, uint16_t oldId) {
    save::Error error; require(retireArmyPoolSlot(d, oldId, error), "cannot retire dissolution fixture cell");
    const auto found = std::find_if(d.armies.begin(), d.armies.end(), [=](const Army& a) { return a.id == oldId; });
    require(found != d.armies.end(), "retired fixture unit missing"); d.armies.erase(found);
    require(save::validate(d, error), "retired dissolution fixture invalid");
}
void allocate(Document& d, uint16_t newId, int16_t job) {
    Army a = d.armies.front(); a.id = newId; a.type = 1; a.owner = 1; a.job = job;
    d.armies.push_back(a); save::Error error;
    require(allocateArmyPoolSlot(d, newId, error), "cannot allocate dissolution fixture cell");
}
void clearJob(Document& d, int p, int j) {
    std::memset(&d.jobs[size_t(p)][size_t(j)], 0, sizeof(Job));
    d.armyPool->jobSlots[size_t(p)][size_t(j)].fill(0);
}
void physicalPoolDissolution() {
    {   // Regression: final memset must clear BOTH record and physical bindings.
        auto d = fixture(); bind(*d,1,5,0,0); pool(*d);
        auto expected = std::make_unique<Document>(*d);
        expected->armies[0].job = 0; clearJob(*expected,1,5);
        expectSuccess(*d,1,5,*expected,-1,{pooled(released(0,101,6),1)}, "pooled release");
        (void)bytes(*expected); // No ghost binding may obstruct archival encoding.
    }
    {   // NULL is skipped even if expectedID resolves a live army; stale owner is harmless.
        auto d = fixture(); pool(*d); d->jobs[1][5].armyIds[0] = 101;
        d->jobs[1][5].owner = 0; d->armies[0].job = 33;
        auto expected = std::make_unique<Document>(*d); clearJob(*expected,1,5);
        expectSuccess(*d,1,5,*expected,-1,{}, "null physical binding with stale expected ID");
    }
    for (const bool parent : {false, true}) {
        auto d = fixture(); bind(*d,1,5,0,0); if (parent) d->jobs[1][5].parentJob = 3;
        pool(*d); retire(*d,101);
        // NONNULL cleared cells are visited, including duplicates; no allocation or fake ID0 entity.
        d->armyPool->jobSlots[1][5][15] = 1; d->jobs[1][5].armyIds[15] = 0;
        auto expected = std::make_unique<Document>(*d); clearJob(*expected,1,5);
        expectSuccess(*d,1,5,*expected,parent?2:-1,
                      {pooled(released(0,0,0),1),pooled(released(15,0,0),1)}, "retired cell release");
        (void)bytes(*expected);
    }
    {   // Expected101 now exists ELSEWHERE. The job's cell1 instead contains60000.
        auto d = fixture(); bind(*d,1,5,0,0); d->jobs[1][5].parentJob = 3; pool(*d);
        retire(*d,101); allocate(*d,60000,6); allocate(*d,101,22);
        require(armyPoolSlot(*d,60000) == 1 && armyPoolSlot(*d,101) == 560, "reuse oracle premise");
        auto expected = std::make_unique<Document>(*d);
        expected->armies[31].job = 3; expected->jobs[1][2].armyIds[0] = 60000;
        expected->jobs[1][2].armies[0].raw = 0; expected->armyPool->jobSlots[1][2][0] = 1;
        clearJob(*expected,1,5);
        expectSuccess(*d,1,5,*expected,2,{pooled(transferred(0,60000,6,3,
            edit(TaskForceOutcome::Removed,60000,1,5,0,{60000}),
            edit(TaskForceOutcome::Added,60000,1,2,0)),1)}, "reused occupant not expected ID");
        require(expected->armyById(101)->job == 22, "expected-ID decoy must be untouched");
        (void)bytes(*expected);
        // Late failures must roll back the successful physical removal/insertion as well.
        word(d->jobs[1][5],14,51); expectFailure(*d,1,5,"pooled late child error");
        word(d->jobs[1][5],14,0); d->armies[31].owner = 2;
        expectFailure(*d,1,5,"foreign-owner reused occupant");
    }
    {   // A nonnull binding with expectedID0 is still a member.
        auto d = fixture(); bind(*d,1,5,0,0); pool(*d); d->jobs[1][5].armyIds[0] = 0;
        auto expected = std::make_unique<Document>(*d); expected->armies[0].job = 0; clearJob(*expected,1,5);
        expectSuccess(*d,1,5,*expected,-1,{pooled(released(0,101,6),1)}, "nonnull expected zero");
        d->jobs[1][5].owner = 0; expectFailure(*d,1,5,"nonnull expected zero owner validation");
    }
    {   // Retired nonnull parent members do NOT count as free slots.
        auto d = fixture(); bind(*d,1,5,0,0); d->jobs[1][5].parentJob = 3; pool(*d);
        for (size_t k = 0; k < 16; ++k) d->armyPool->jobSlots[1][2][k] = uint32_t(560-k);
        auto expected = std::make_unique<Document>(*d); expected->armies[0].job = 0; clearJob(*expected,1,5);
        expectSuccess(*d,1,5,*expected,2,{pooled(transferred(0,101,6,0,
            edit(TaskForceOutcome::Removed,101,1,5,0,{101}),
            edit(TaskForceOutcome::Full,101,1,2,-1)),1)}, "pooled full parent");
    }
    {   // AlreadyPresent compares cells; the parent's stale expected ID is not repaired.
        auto d = fixture(); bind(*d,1,5,0,0); d->jobs[1][5].parentJob = 3; pool(*d);
        d->armyPool->jobSlots[1][2][7] = 1;
        auto expected = std::make_unique<Document>(*d); expected->armies[0].job = 0; clearJob(*expected,1,5);
        expectSuccess(*d,1,5,*expected,2,{pooled(transferred(0,101,6,0,
            edit(TaskForceOutcome::Removed,101,1,5,0,{101}),
            edit(TaskForceOutcome::AlreadyPresent,101,1,2,7)),1)}, "pooled already present");
    }
    {   // Self-parent insertion chooses an earlier physical hole, not an expected-ID hole.
        auto d = fixture(); d->jobs[1][5].parentJob = 6; word(d->jobs[1][5],5,6);
        d->armies[0].type = 13; bind(*d,1,5,0,0); bind(*d,1,5,2,1); pool(*d);
        auto expected = std::make_unique<Document>(*d); expected->armies[0].job = 0;
        word(expected->jobs[1][0],0,6); clearJob(*expected,1,5);
        expectSuccess(*d,1,5,*expected,5,{pooled(released(0,101,6),1),
            pooled(transferred(2,102,6,6,edit(TaskForceOutcome::Removed,102,1,5,2,{102}),
                          edit(TaskForceOutcome::Added,102,1,5,1)),2),
            reparented(5,5,6,0),cleared(5,5,6)}, "pooled self parent");
    }
    {   // Invalid metadata is rejected before indexing the pool.
        auto d = fixture(); pool(*d); d->armyPool->jobSlots[1][5][0] = 561;
        expectFailure(*d,1,5,"out-of-range pool cell");
    }
}

class OriginalPe {
    std::vector<uint8_t> bytes_; uint32_t imageBase_ = 0; size_t sections_ = 0; uint16_t count_ = 0;
    uint8_t u8(size_t at) const { require(at < bytes_.size(), "truncated original PE"); return bytes_[at]; }
    uint16_t u16(size_t at) const { return uint16_t(u8(at) | uint16_t(u8(at+1)) << 8); }
    uint32_t u32(size_t at) const { return uint32_t(u8(at)) | uint32_t(u8(at+1)) << 8 | uint32_t(u8(at+2)) << 16 | uint32_t(u8(at+3)) << 24; }
    size_t offset(uint32_t address) const {
        require(address >= imageBase_, "PE address below image base"); const auto rva = address - imageBase_;
        for (size_t i = 0; i < count_; ++i) {
            const auto at = sections_ + 40*i; const auto start = u32(at+12), size = u32(at+16);
            if (rva >= start && rva - start < size) {
                const auto result = size_t(u32(at+20)) + size_t(rva - start);
                require(result < bytes_.size(), "PE raw offset outside file"); return result;
            }
        }
        throw std::runtime_error("address has no backed PE section");
    }
public:
    explicit OriginalPe(const fs::path& path) {
        const auto size = fs::file_size(path); require(size >= 64 && size <= 16*1024*1024, "invalid original EXE size");
        bytes_.resize(size_t(size)); std::ifstream in(path, std::ios::binary);
        require(bool(in.read(reinterpret_cast<char*>(bytes_.data()), std::streamsize(bytes_.size()))), "cannot read original EXE");
        require(u16(0) == 0x5a4d, "original EXE is not MZ"); const size_t pe = u32(0x3c);
        require(u32(pe) == 0x4550 && u16(pe+24) == 0x10b, "original EXE is not PE32");
        count_ = u16(pe+6); imageBase_ = u32(pe+52); sections_ = pe + 24 + u16(pe+20);
        require(count_ > 0 && count_ < 100 && sections_ <= bytes_.size() && size_t(count_)*40 <= bytes_.size() - sections_, "invalid PE sections");
    }
    uint8_t byte(uint32_t address) const { return u8(offset(address)); }
    bool code(uint32_t address, const std::vector<uint8_t>& expected) const {
        uint32_t at = address;
        for (const auto value : expected) if (byte(at++) != value) return false;
        return true;
    }
};
void canonicalPe(const fs::path& directory) {
    const auto path = directory/"DEADLOCK.EXE";
    if (directory.empty() || !fs::is_regular_file(path)) {
        std::cout << "Task-force dissolution: optional original PE unavailable\n"; return;
    }
    OriginalPe pe(path);
    require(pe.code(0x445841,{0x6a,0x5c,0x6a,0,0x53,0xe8,0xed,0x0f,6,0}) &&
            pe.code(0x445854,{0x89,0x53,0x54,0x33,0xc9,0x89,0x4b,0x58}),
            "DeleteArmy no longer clears type/job before writing only free-list links");
    for (uint32_t t = 0; t < uint32_t(data::kNumUnitTypes); ++t)
        require(int8_t(pe.byte(0x004faf8du + t * 0x24u)) == data::kUnitTypes[t].domain,
                "canonical unit domain differs from PE byte read by 0040bf0d");
    struct Anchor { uint32_t address; std::vector<uint8_t> bytes; const char* meaning; };
    const Anchor anchors[]{
        {0x0040bec5, {0x8b,0x87,0x84,0x00,0x00,0x00}, "parent word Job+0x84 read once"},
        {0x0040becf, {0x0f,0xbf,0x57,0x0a}, "MOVSX Job.owner for parent address"},
        {0x0040bef3, {0x8d,0x77,0x44}, "army pointer slots at Job+0x44"},
        {0x0040bef9, {0x8b,0x1e}, "slot reread every iteration"},
        {0x0040bf06, {0x0f,0xbe,0x53,0x06}, "MOVSX Army.type"},
        {0x0040bf0d, {0x0f,0xbe,0x04,0x8d,0x8d,0xaf,0x4f,0x00}, "MOVSX canonical UnitDef+0x11 domain"},
        {0x0040bf15, {0x48,0x75,0x12}, "domain-1 == 0 selects transfer"},
        {0x0040bf18, {0x53,0xe8,0xd6,0xee,0xff,0xff}, "RemoveArmyFromTaskForce0040adf4 first"},
        {0x0040bf23, {0xe8,0x98,0xf1,0xff,0xff}, "then 0040b0c0 into parent"},
        {0x0040bf2a, {0x66,0xc7,0x43,0x36,0x00,0x00}, "release writes Army.job=0 only"},
        {0x0040bf39, {0x83,0xf9,0x10}, "sixteen army slots"},
        {0x0040bf3e, {0xbe,0x01,0x00,0x00,0x00,0x8d,0x9f,0x88,0x00,0x00,0x00}, "child words from Job+0x88"},
        {0x0040bf69, {0x81,0xc0,0x84,0x25,0x52,0x00}, "new parent is the owner's job0"},
        {0x0040bf82, {0x83,0xfe,0x10}, "fifteen child words"},
        {0x0040bf93, {0xe8,0x0c,0xf0,0xff,0xff}, "0040afa4 after children"},
        {0x0040bf98, {0x68,0xc4,0x00,0x00,0x00,0x6a,0x00,0x57}, "memset(job,0,0xc4)"},
        {0x0040b017, {0x83,0x39,0x00,0x75,0x23}, "0040b000 first zero job0 word"},
        {0x0040b01c, {0x0f,0xbf,0x53,0x0a}, "child index from CHILD owner word"},
        {0x0040b03d, {0xeb,0x09}, "break after first free word"},
        {0x0040b043, {0x83,0xf8,0x10}, "fifteen job0 words"},
        {0x0040b048, {0x0f,0xbf,0x46,0x0a}, "parent index from job0 owner word"},
        {0x0040b065, {0x89,0x83,0x84,0x00,0x00,0x00}, "child parent written unconditionally"},
        {0x0040afbe, {0x0f,0xbf,0x73,0x0a}, "0040afa4 uses PARENT owner word"},
        {0x0040afdf, {0x85,0xc9,0x74,0x0b}, "non-null address test"},
        {0x0040afe6, {0x3b,0xce,0x75,0x04,0x33,0xc9,0x89,0x08}, "clear every matching word"},
        {0x0040aff2, {0x83,0xfa,0x10}, "fifteen parent words, no early break"},
    };
    for (const auto& anchor : anchors)
        require(pe.code(anchor.address, anchor.bytes), std::string("PE anchor differs: ") + anchor.meaning);
    std::cout << "Task-force dissolution: " << std::size(anchors) << " PE code anchors and "
              << data::kNumUnitTypes << " domain bytes verified\n";
}

std::vector<std::string> scenarioNames(const fs::path& path) {
    const auto size = fs::file_size(path); require(size >= 4 && size <= save::kMaxFileBytes, "invalid corpus index size");
    std::ifstream in(path, std::ios::binary); uint8_t raw[4]{};
    require(bool(in.read(reinterpret_cast<char*>(raw), 4)), "cannot read corpus index");
    const uint32_t n = uint32_t(raw[0]) | uint32_t(raw[1]) << 8 | uint32_t(raw[2]) << 16 | uint32_t(raw[3]) << 24;
    require(n <= (size - 4) / 12, "truncated corpus index"); std::vector<std::string> names;
    for (uint32_t i = 0; i < n; ++i) {
        char entry[12]{}; require(bool(in.read(entry, 12)), "cannot read corpus entry");
        names.emplace_back(entry, std::find(entry, entry + 8, '\0'));
    }
    return names;
}
struct CorpusTally {
    size_t documents = 0, jobs = 0, dissolved = 0, released = 0, transferred = 0, notIncorporated = 0,
           reparented = 0, parentLinks = 0;
    std::map<std::string, size_t> rejected;
};
void corpusOne(const Document& original, CorpusTally& tally) {
    auto d = std::make_unique<Document>(); LoadCoreReport core; save::Error error;
    if (!normalizeLoadCore(original, {}, *d, core, error)) throw std::runtime_error(error.message);
    const auto normalized = bytes(*d);
    ++tally.documents;
    for (int p = 0; p < kMaxPlayers; ++p) for (int j = 0; j < kJobsPerPlayer; ++j) {
        const Job& job = d->jobs[size_t(p)][size_t(j)];
        bool references = job.parentJob != 0;
        for (const auto armyId : job.armyIds) references |= armyId != 0;
        for (size_t k = 0; k < 15; ++k) references |= word(job, k) != 0;
        if (!references) continue;
        ++tally.jobs;
        auto first = std::make_unique<Document>(), second = std::make_unique<Document>();
        TaskForceDissolutionReport a, b; save::Error ea, eb;
        const bool okA = dissolveTaskForce(*d, p, j, *first, a, ea);
        const bool okB = dissolveTaskForce(*d, p, j, *second, b, eb);
        require(okA == okB && ea.message == eb.message && bytes(*d) == normalized,
                "corpus dissolution was nondeterministic or mutated its source");
        // These normalized shipped scenarios are a success regression corpus,
        // not merely a determinism check that could silently accept all errors.
        require(okA, "corpus dissolution unexpectedly rejected: " + ea.message);
        require(a == b && same(*first, *second) && zeroJob(first->jobs[size_t(p)][size_t(j)]),
                "corpus dissolution result differs or job not cleared");
        // Records of other players and armies of other owners are untouched.
        for (int q = 0; q < kMaxPlayers; ++q) if (q != p)
            require(std::memcmp(first->jobs[size_t(q)].data(), d->jobs[size_t(q)].data(), sizeof(d->jobs[0])) == 0,
                    "corpus dissolution touched another player's jobs");
        for (size_t i = 0; i < d->armies.size(); ++i) if (d->armies[i].owner != p)
            require(std::memcmp(&first->armies[i], &d->armies[i], sizeof(Army)) == 0,
                    "corpus dissolution touched a foreign army");
        ++tally.dissolved;
        for (const auto& step : a.steps) switch (step.action) {
            case Action::ArmyReleased: ++tally.released; break;
            case Action::ArmyTransferred:
                ++tally.transferred;
                if (step.insertion.outcome != TaskForceOutcome::Added) ++tally.notIncorporated;
                break;
            case Action::ChildReparented: ++tally.reparented; break;
            case Action::ParentLinkCleared: ++tally.parentLinks; break;
        }
    }
}
void optionalCorpus(const fs::path& directory) {
    if (directory.empty() || !fs::is_regular_file(directory/"TUTORIAL.SAV")) {
        std::cout << "Task-force dissolution: optional corpus unavailable\n"; return;
    }
    CorpusTally tally;
    for (const char* name : {"TUTORIAL.SAV","Saves/AUTOSAVE.SAV","Campaign/AUTOSAVE.CPN","Campaign/ChCht001.CPN"}) {
        if (!fs::is_regular_file(directory/name)) continue;
        auto d = std::make_unique<Document>(); save::Error error;
        if (!save::readDocument(directory/name, *d, error)) throw std::runtime_error(error.message);
        try { corpusOne(*d, tally); } catch (const std::exception& e) { throw std::runtime_error(std::string(name) + ": " + e.what()); }
    }
    if (fs::is_regular_file(directory/"LEVELS.HDX") && fs::is_regular_file(directory/"LEVELS.HDD"))
        for (const auto& name : scenarioNames(directory/"LEVELS.HDX")) {
            auto d = std::make_unique<Document>(); save::Error error;
            if (!save::readScenario(directory/"LEVELS", name, *d, error)) throw std::runtime_error(error.message);
            try { corpusOne(*d, tally); } catch (const std::exception& e) { throw std::runtime_error(name + ": " + e.what()); }
        }
    std::cout << "Task-force dissolution corpus: " << tally.documents << " documents, " << tally.jobs
              << " referenced jobs, " << tally.dissolved << " dissolved (" << tally.released << " released, "
              << tally.transferred << " transferred, " << tally.notIncorporated << " not incorporated, "
              << tally.reparented << " reparented, " << tally.parentLinks << " parent links)\n";
    for (const auto& [message, count] : tally.rejected)
        std::cout << "  rejected " << count << ": " << message << '\n';
}
} // namespace

int main(int argc, char** argv) {
    try {
        rtl::srand(0xf1234567u); (void)rtl::lrand(); gg.rng2Seed = 0xabcd0123;
        const auto low = rtl::seed(), high = rtl::seedHi();
        const auto globals = std::make_unique<GameGlobals>(gg); const auto game = std::make_unique<GameState>(gs);
        canonicalDomains(); noParentReleases(); parentTransfers(); parentOutcomes(); childLinks();
        fullRootBeforeParentClear(); dissolveRoot(); selfLinks(); parentAddressArithmetic();
        freeRecords(); domainErrors(); determinism(); physicalPoolDissolution();
        const fs::path directory = argc > 1 ? fs::path(argv[1]) : fs::path{};
        canonicalPe(directory); optionalCorpus(directory);
        require(rtl::seed() == low && rtl::seedHi() == high && std::memcmp(&gg, globals.get(), sizeof(gg)) == 0 &&
                std::memcmp(&gs, game.get(), sizeof(gs)) == 0, "task-force dissolution changed globals or RNG");
        std::cout << "Task-force dissolution tests passed\n"; return 0;
    } catch (const std::exception& e) {
        std::cerr << "Task-force dissolution: " << e.what() << '\n'; return 1;
    }
}
