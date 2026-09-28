// Independent numeric oracles derived from GetBuildingTasks (0044e7ec),
// DistributeLabor (0044c49c), BalanceLabor (0044bea8), TerritoryLaborPool
// (0046c3fc) and EndTurnBalance (0046c780). These are NOT observations obtained
// by running the original executable, nor tests of a complete economic turn.
#include "game/labor_balance.h"
#include "game/data_tables.h"
#include "game/save_files.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include "formats/hdx_archive.h"

#include <algorithm>
#include <array>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

namespace {
using namespace dl2;
using simulation::BuildingLaborChange;
using simulation::BuildingLaborState;
using simulation::LaborBalancePlan;
using simulation::TerritoryLaborBalance;
using Labor = std::array<int32_t, 5>;
using Tasks = std::array<uint8_t, 5>;

void require(bool condition, const char* message) {
    if (!condition) throw std::runtime_error(message);
}

// Capture every owned member, including nonserialized territory tails and
// opaque queue words. An encode-only comparison would miss those mutations.
template<class T> void append(std::vector<uint8_t>& bytes, const T& value) {
    static_assert(std::is_trivially_copyable_v<T>);
    const auto* begin = reinterpret_cast<const uint8_t*>(&value);
    bytes.insert(bytes.end(), begin, begin + sizeof(T));
}
template<class T> void appendVector(std::vector<uint8_t>& bytes, const std::vector<T>& values) {
    append(bytes, uint64_t(values.size()));
    for (const auto& value : values) append(bytes, value);
}
std::vector<uint8_t> snapshot(const save::Document& d) {
    std::vector<uint8_t> bytes;
    append(bytes, d.header); append(bytes, d.options); append(bytes, d.world);
    append(bytes, d.players); appendVector(bytes, d.localList);
    append(bytes, d.raceStats); append(bytes, d.techs);
    for (const auto& list : d.ministerJobs) appendVector(bytes, list);
    append(bytes, uint64_t(d.events.size()));
    for (const auto& event : d.events) {
        append(bytes, event.record); appendVector(bytes, event.text);
    }
    appendVector(bytes, d.tiles); appendVector(bytes, d.buildings); appendVector(bytes, d.armies);
    append(bytes, uint64_t(d.territories.size()));
    for (const auto& territory : d.territories) {
        append(bytes, territory.data);
        for (const auto& queue : territory.queues) appendVector(bytes, queue);
    }
    append(bytes, d.jobs); append(bytes, d.aiWarMask);
    append(bytes, d.scratchJob1); append(bytes, d.scratchJob2);
    append(bytes, d.continents); append(bytes, d.randomEvents); append(bytes, d.scores);
    append(bytes, d.spies); append(bytes, d.blackMarket);
    appendVector(bytes, d.mapTerritories); appendVector(bytes, d.trailing);
    return bytes;
}

std::unique_ptr<save::Document> fixture() {
    auto d = std::make_unique<save::Document>();
    std::memcpy(d->header.text, save::kHeaderText, sizeof(save::kHeaderText));
    d->header.version = kSaveVersion;
    d->options.numPlayers = 1; d->options.localPlayer = 0; d->options.turn = 41;
    d->world.width = 2; d->world.height = 1; d->world.numTerritories = 2;
    d->world.rngSeed = 0x12345678;
    d->buildings.reserve(72); // Test references remain stable while adding buildings.
    d->territories.resize(2); d->tiles.resize(2);
    for (int player = 0; player < kMaxPlayers; ++player) {
        d->players[size_t(player)].index = uint8_t(player);
        d->players[size_t(player)].race = 2;
        d->ministerJobs[size_t(player)].resize(1);
        for (int row = 0; row < kNumRaceStatRows; ++row)
            d->raceStats.v[row][player] = 100;
    }
    d->players[0].type = 1;
    for (int i = 0; i < 2; ++i) {
        auto& t = d->territories[size_t(i)].data;
        t.index = uint16_t(i + 1); t.owner = i == 0 ? 0 : -1;
        t.terrain = 1; t.population = 2000; t.morale = 100; t.knowledge = 100;
        t.numTiles = 1; t.tiles[0].raw = uint32_t(i);
        d->tiles[size_t(i)].x = uint8_t(i);
        d->tiles[size_t(i)].territory = int16_t(i + 1);
        for (int site = 0; site < kNumSites; ++site) {
            t.sites[site].unk_00 = uint16_t((site % 6) | ((site / 6) << 8));
            t.sites[site].terrainFlags = 1;
        }
    }
    return d;
}

Building& addBuilding(save::Document& d, uint8_t type, int site, int territory = 1) {
    Building b{};
    b.id = uint16_t(100 + d.buildings.size()); b.type = type;
    b.category = data::kBuildingTypes[type].category;
    b.flags = 6; b.site = int8_t(site); b.territory = int16_t(territory);
    std::copy_n(data::kBuildingTypes[type].tasks, 5, b.task);
    d.territories[size_t(territory - 1)].data.sites[size_t(site)].building.raw = b.id;
    d.buildings.push_back(b);
    return d.buildings.back();
}

BuildingLaborState stateOf(const Building& b) {
    BuildingLaborState state;
    state.flags = b.flags;
    std::copy_n(b.task, 5, state.tasks.begin());
    std::copy_n(b.labor, 5, state.labor.begin());
    return state;
}
void labor(Building& b, Labor values) { std::copy(values.begin(), values.end(), b.labor); }
void tasks(Building& b, Tasks values) { std::copy(values.begin(), values.end(), b.task); }

const BuildingLaborChange& building(const LaborBalancePlan& report, uint32_t id) {
    for (const auto& entry : report.buildings) if (entry.buildingId == id) return entry;
    throw std::runtime_error("missing building in labor report");
}
const TerritoryLaborBalance& territory(const LaborBalancePlan& report, uint32_t id) {
    for (const auto& entry : report.territories) if (entry.territory == id) return entry;
    throw std::runtime_error("missing territory in labor report");
}

LaborBalancePlan plan(const save::Document& d) {
    const auto before = snapshot(d);
    LaborBalancePlan result;
    result.buildings.resize(1); result.territories.resize(1); // Must replace, not append.
    save::Error error{save::ErrorCode::Io, 999, "stale"};
    if (!simulation::planLaborBalance(d, result, error)) throw std::runtime_error(error.message);
    require(error.code == save::ErrorCode::None && error.offset == 0 && error.message.empty(),
            "success clears all previous error fields");
    require(snapshot(d) == before, "labor planning preserves every owned document field");
    require(result.buildings.size() == d.buildings.size() && result.territories.size() == d.territories.size(),
            "report contains every building and territory, including unchanged/unowned ones");
    for (size_t i = 0; i < d.buildings.size(); ++i) {
        const auto& b = d.buildings[i];
        const auto& change = result.buildings[i];
        require(change.buildingId == b.id && change.territory == uint32_t(b.territory) &&
                change.site == uint8_t(b.site) && change.before == stateOf(b),
                "building report is in document order and retains its exact before-state");
    }
    for (size_t i = 0; i < d.territories.size(); ++i) {
        const auto& t = d.territories[i].data;
        const auto& change = result.territories[i];
        require(change.territory == i + 1 && change.moraleBefore == t.morale,
                "territory report is in file-index order with its original morale");
        for (size_t resource = 0; resource < 11; ++resource)
            require(change.materialsBefore[resource] == t.materials[resource],
                    "territory report retains every original stock value");
    }
    return result;
}

void laborPoolOracles() {
    // Numeric boundaries computed directly on paper from 0046c3fc. Morale is a
    // signed byte, population a signed short; divisions truncate toward zero.
    struct Case { int16_t population; int8_t morale; int32_t pool, unavailable; };
    constexpr Case cases[] = {
        {0, -128, 0, 0}, {1, 0, 1, 0}, {99, 100, 1, 0}, {100, 0, 1, 0},
        {1000, 0, 2, 8}, {1000, 1, 3, 7}, {1000, 10, 3, 7}, {1000, 11, 4, 6},
        {1000, 50, 6, 4}, {1000, 90, 9, 1}, {1000, 91, 10, 0}, {1000, 100, 10, 0},
        {1000, 127, 12, 0}, {1000, -128, 1, 9}, {-1000, 100, 1, 0},
        {-1000, -128, 5, 0}, {32767, 127, 403, 0}
    };
    for (const auto& test : cases) {
        auto d = fixture();
        for (auto& record : d->territories) {
            record.data.population = test.population; record.data.morale = test.morale;
        }
        const auto report = plan(*d);
        for (const auto& t : report.territories) {
            require(t.laborPool == test.pool && t.unavailableLabor == test.unavailable &&
                    t.assignedLabor == 0 && t.unassignedLabor == test.pool,
                    "signed population/morale labor-pool oracle, owned and unowned");
            require(t.moraleAfter == (test.population == 0 ? 100 : test.morale),
                    "only zero population resets morale to 100");
        }
    }
}

void constructionAndOverflow() {
    auto d = fixture();
    auto& b = addBuilding(*d, 6, 14);
    b.flags = 0x1f26; b.turnsLeft = 10;
    labor(b, {1, 2, 1, 2, 1});
    auto result = plan(*d);
    const auto& after = building(result, b.id).after;
    require(after.tasks == Tasks{2, 0, 0, 0, 0} && after.labor == Labor{4, 0, 0, 0, 0},
            "unfinished building consolidates all labor into construction then caps at four");
    require(after.flags == 0x26 && territory(result, 1).assignedLabor == 4 &&
            territory(result, 1).unassignedLabor == 16,
            "construction clears other locks; clipping clears lock zero but preserves unrelated flags");
    b.turnsLeft = -1;
    require(plan(*d) == result, "any nonzero signed construction counter takes the construction branch");
    b.flags = 0x1f06;
    labor(b, {1, 1, 1, 0, 0});
    result = plan(*d);
    require(building(result, b.id).after.flags == 0x106 &&
            building(result, b.id).after.labor == Labor{3, 0, 0, 0, 0},
            "construction lock zero survives when its merged allocation needs no clipping");
    b.flags = 6;
    labor(b, {std::numeric_limits<int32_t>::max(), std::numeric_limits<int32_t>::max(), 0, 0, 0});
    result = plan(*d);
    require(building(result, b.id).after.labor == Labor{-2, 0, 0, 0, 0} &&
            territory(result, 1).assignedLabor == -2 && territory(result, 1).unassignedLabor == 22,
            "TotalLabor wraps to -2 before construction and signed-short balance, without C++ overflow");
}

void upgradeAndConstructionTransition() {
    auto d = fixture();
    auto& farm = addBuilding(*d, 5, 14);
    farm.task[0] = 2; labor(farm, {2, 1, 1, 0, 0});
    auto report = plan(*d);
    require(building(report, farm.id).after.tasks == Tasks{0, 12, 13, 0, 0} &&
            building(report, farm.id).after.labor == Labor{0, 2, 2, 0, 0},
            "completed construction without upgrade technology redistributes its workers");
    d->techs[11].knownMask = 1;
    report = plan(*d);
    require(building(report, farm.id).after.tasks == Tasks{21, 12, 13, 0, 0} &&
            building(report, farm.id).after.labor == Labor{0, 2, 2, 0, 0},
            "unlocked completed construction does not automatically assign workers to the new upgrade task");
    farm.flags |= 0x100;
    report = plan(*d);
    require(building(report, farm.id).after.labor == Labor{2, 1, 1, 0, 0} &&
            (building(report, farm.id).after.flags & 0x100),
            "locked construction transitions to upgrade with its workers intact");
    d->techs[11].knownMask = 2;
    report = plan(*d);
    require(building(report, farm.id).after.tasks[0] == 0 &&
            !(building(report, farm.id).after.flags & 0x100),
            "upgrade technology belonging only to another player does not qualify");
    // CanUpgrade uses territory owner, whereas task tech gates use Player.index.
    d->players[0].index = 1; d->techs[11].knownMask = 1;
    require(building(plan(*d), farm.id).after.tasks[0] == 21,
            "upgrade ownership mask is not incorrectly derived from Player.index");

    struct UpgradeCase { uint8_t type; bool permitted; };
    constexpr UpgradeCase cases[] = {
        {1, true}, {2, true}, {3, false}, {5, true}, {6, true}, {7, false},
        {14, true}, {15, true}, {16, false}, {21, true}, {22, false},
        {29, false}, {30, false}, {31, false}, {37, false}, {43, false},
        {45, false}, {46, false}, {47, false}
    };
    for (const auto& test : cases) {
        auto sample = fixture();
        for (auto& tech : sample->techs) tech.knownMask = 0xffff;
        const auto id = addBuilding(*sample, test.type, 14).id;
        require(building(plan(*sample), id).after.tasks[0] == (test.permitted ? 21 : 0),
                "CanUpgrade exclusions and next-type category boundary match the original");
    }
}

void technologyMasksAndShrines() {
    // Gate IDs are obtained from (DAT address - 004fbbac) / sizeof(TechSaved),
    // not inferred from names: 4->20, 6->4, 9->2, 10->29, 16->22.
    struct Gate { uint8_t type, slot, task, tech; };
    constexpr Gate gates[] = {{8, 2, 4, 20}, {18, 2, 6, 4}, {14, 2, 9, 2},
                              {14, 3, 10, 29}, {11, 2, 16, 22}};
    for (const auto& gate : gates) {
        auto d = fixture();
        const auto id = addBuilding(*d, gate.type, 14).id;
        require(building(plan(*d), id).after.tasks[gate.slot] == 0, "unknown technology suppresses its task");
        d->techs[gate.tech].knownMask = 1;
        require(building(plan(*d), id).after.tasks[gate.slot] == gate.task, "known technology enables its task");
        d->players[0].index = 1;
        require(building(plan(*d), id).after.tasks[gate.slot] == 0, "task gate uses player index, not owner slot");
        d->techs[gate.tech].knownMask = 2;
        require(building(plan(*d), id).after.tasks[gate.slot] == gate.task, "distinct player index bit is preserved");
        d->players[0].index = 32; d->techs[gate.tech].knownMask = 1;
        require(building(plan(*d), id).after.tasks[gate.slot] == gate.task, "x86 shift count masks Player.index by 31");
        d->players[0].index = 31; d->techs[gate.tech].knownMask = 0x8000;
        require(building(plan(*d), id).after.tasks[gate.slot] == gate.task,
                "signed 16-bit technology mask sign-extends before a high player-index bit test");
    }
    auto d = fixture();
    const auto hidden = addBuilding(*d, 46, 1).id;
    const auto sea = addBuilding(*d, 47, 3).id;
    d->territories[0].data.sites[1].terrainFlags = 0x202;
    auto report = plan(*d);
    require(building(report, hidden).after.tasks == Tasks{0, 4, 0, 0, 0} &&
            building(report, sea).after.tasks == Tasks{0, 16, 0, 0, 0},
            "dynamic hidden/sea shrine task bypasses the ordinary technology gate");
    d->territories[0].data.sites[1].terrainFlags = 0x104;
    require(building(plan(*d), hidden).after.tasks[1] == 3, "hidden shrine uses terrain low nibble only");
    constexpr uint8_t hiddenByTerrain[] = {12, 15, 4, 13, 3};
    for (uint16_t terrain = 0; terrain < 5; ++terrain) {
        d->territories[0].data.sites[1].terrainFlags = terrain;
        require(building(plan(*d), hidden).after.tasks[1] == hiddenByTerrain[terrain],
                "hidden shrine natural-task terrain mapping");
    }
}

void redistributionQueuesAndLocks() {
    auto d = fixture();
    auto& factory = addBuilding(*d, 14, 14);
    d->techs[2].knownMask = 1; // Steel remains available; Triidium tech29 does not.
    labor(factory, {0, 1, 1, 3, 0});
    auto report = plan(*d);
    require(building(report, factory.id).after.tasks == Tasks{0, 14, 9, 0, 11} &&
            building(report, factory.id).after.labor == Labor{0, 3, 2, 0, 0},
            "removed task labor splits among eligible tasks, remainder goes to the first slot");
    QueueRecord queued{}; queued.unitType = 1; queued.count = 0;
    queued.next.raw = 0xfedcba98; // Opaque nonserialized word; never dereference it.
    d->territories[0].queues[0].push_back(queued);
    d->territories[0].data.queues[0].raw = 0x12345678;
    report = plan(*d);
    require(building(report, factory.id).after.labor == Labor{0, 3, 1, 0, 1},
            "presence of a queue node admits slot4 even if its unit count is zero");
    factory.flags |= 0x200;
    report = plan(*d);
    require(building(report, factory.id).after.labor == Labor{0, 1, 2, 0, 2} &&
            (building(report, factory.id).after.flags & 0x200),
            "locked eligible task retains its labor while the remainder is split elsewhere");
    d->territories[0].queues[0].clear();
    report = plan(*d);
    require(building(report, factory.id).after.labor == Labor{0, 1, 4, 0, 0},
            "raw queue address alone cannot make an empty owned queue nonempty");

    auto mineDoc = fixture();
    auto& mine = addBuilding(*mineDoc, 8, 14);
    labor(mine, {0, 1, 3, 0, 0}); mine.flags |= 0x400;
    const auto mineResult = building(plan(*mineDoc), mine.id).after;
    require(mineResult.tasks == Tasks{0, 3, 0, 0, 0} && mineResult.labor == Labor{0, 4, 0, 0, 0} &&
            (mineResult.flags & 0x400),
            "refresh zeroes a disabled locked task's labor without inventing a lock-clear operation");
}

void transferDependency() {
    auto d = fixture();
    // MoveLaborToHousingNoNet checks task20 and spare MaxLabor, NOT category17.
    // Using a nonhousing stored category makes the transfer observable: the
    // final automatic-housing pass cannot subsequently hide a missing transfer.
    auto& target = addBuilding(*d, 1, 0);
    target.category = 14;
    auto& source = addBuilding(*d, 28, 1);
    source.task[0] = 2; source.labor[0] = 3;
    auto report = plan(*d);
    require(building(report, target.id).after.labor == Labor{0, 3, 0, 0, 0} &&
            building(report, source.id).after.labor == Labor{} &&
            territory(report, 1).assignedLabor == 3 && territory(report, 1).unassignedLabor == 17,
            "redistribution with no eligible task uses the real task20 transfer dependency");
    d->players[0].race = -1;
    require(plan(*d) == report,
            "nonhousing task20 recipient does not read or validate the housing-only racial statistic");
}

void prioritiesAndOrder() {
    auto d = fixture();
    d->territories[0].data.population = 500;
    // Deliberately opposite document/site order. Both foods must be considered
    // before any wood, not all slots of the first building before the next.
    const auto lateId = addBuilding(*d, 5, 20).id;
    const auto earlyId = addBuilding(*d, 5, 8).id;
    labor(d->buildings[0], {0, 2, 3, 0, 0});
    labor(d->buildings[1], {0, 2, 3, 0, 0});
    d->buildings[0].flags = d->buildings[1].flags = 0x606;
    auto result = plan(*d);
    require(building(result, earlyId).after.labor == Labor{0, 2, 1, 0, 0} &&
            building(result, lateId).after.labor == Labor{0, 2, 0, 0, 0},
            "global priority pass preserves both food jobs before earlier-site wood consumes the rest");
    require(building(result, earlyId).after.flags == 0x206 &&
            building(result, lateId).after.flags == 0x206,
            "only clipped wood locks clear; unchanged food locks remain");
    require(result.buildings[0].buildingId == lateId && result.buildings[1].buildingId == earlyId,
            "execution site order must not change the requested document-order report");
    std::reverse(d->buildings.begin(), d->buildings.end());
    const auto reversed = plan(*d);
    require(building(reversed, earlyId) == building(result, earlyId) &&
            building(reversed, lateId) == building(result, lateId),
            "per-building result is independent of physical building-vector order");

    auto three = fixture();
    three->territories[0].data.population = 500;
    const auto food = addBuilding(*three, 6, 20).id;
    const auto energy = addBuilding(*three, 11, 0).id;
    const auto culture = addBuilding(*three, 21, 10).id;
    for (auto& b : three->buildings) b.labor[1] = 3;
    result = plan(*three);
    require(building(result, energy).after.labor[1] == 3 &&
            building(result, culture).after.labor[1] == 2 && building(result, food).after.labor[1] == 0,
            "energy, culture and food share one priority pass ordered by site");

    auto upgrade = fixture();
    upgrade->territories[0].data.population = 400;
    auto& farm = addBuilding(*upgrade, 5, 14);
    upgrade->techs[11].knownMask = 1;
    farm.task[0] = 21; farm.flags = 0x706; labor(farm, {3, 2, 3, 0, 0});
    result = plan(*upgrade);
    require(building(result, farm.id).after.labor == Labor{0, 2, 2, 0, 0} &&
            building(result, farm.id).after.flags == 0x206,
            "nonhousing priority is slots1,2,3,4,0, putting upgrade last despite its lock");
}

void inactiveHousingAndCapacity() {
    auto d = fixture();
    auto& housing = addBuilding(*d, 1, 0);
    housing.flags = 0x202; housing.labor[1] = 3;
    d->territories[0].data.population = 300;
    auto report = plan(*d);
    require(building(report, housing.id).after.labor == Labor{0, 3, 0, 0, 0} &&
            territory(report, 1).unassignedLabor == 0,
            "inactive housing preserves its occupants when pass3 exhausts the pool");
    d->territories[0].data.population = 400;
    report = plan(*d);
    require(building(report, housing.id).after.labor == Labor{} &&
            territory(report, 1).assignedLabor == 0 && territory(report, 1).unassignedLabor == 4 &&
            (building(report, housing.id).after.flags & 0x200),
            "inactive housing pass4 negative free capacity removes occupants without clearing their lock");
    const auto active = addBuilding(*d, 1, 1).id;
    report = plan(*d);
    require(building(report, active).after.labor == Labor{0, 4, 0, 0, 0} &&
            territory(report, 1).unassignedLabor == 0,
            "later active housing absorbs the occupants removed from inactive housing");

    auto racial = fixture();
    const auto id = addBuilding(*racial, 1, 0).id;
    racial->raceStats.v[24][2] = 200;
    report = plan(*racial);
    require(building(report, id).after.labor == Labor{0, 10, 0, 0, 0} &&
            territory(report, 1).unassignedLabor == 10,
            "housing capacity scales by the saved owner's racial row24");
    racial->buildings[0].flags = 4;
    require(building(plan(*racial), id).after.labor == Labor{0, 10, 0, 0, 0},
            "housing labor capacity needs Active but not the Built flag");
    racial->buildings[0].flags = 6; racial->raceStats.v[24][2] = -100;
    report = plan(*racial);
    require(building(report, id).after.labor == Labor{-5, 0, 0, 0, 0} &&
            territory(report, 1).assignedLabor == -5 && territory(report, 1).unassignedLabor == 25,
            "negative signed racial capacity is not normalized away");

    auto ordinary = fixture();
    auto& farm = addBuilding(*ordinary, 6, 14);
    farm.flags = 0x602; labor(farm, {0, 3, 3, 0, 0});
    const auto state = building(plan(*ordinary), farm.id).after;
    require(state.labor == Labor{} && state.flags == 2,
            "inactive nonhousing gets zero active capacity and loses clipped slot locks");
}

void generatedNegativeLaborAndUnownedTasks() {
    auto d = fixture();
    auto& center = addBuilding(*d, 37, 14);
    center.flags = 0x1f06; labor(center, {0, 6, 6, 0, 0});
    auto result = plan(*d);
    // Pass1 keeps culture6. Pass2 starts with capacity8, keeps trade6, then
    // subtracts culture6, leaving -4; the following empty slot receives -4.
    // Replacing this with a precomputed/nonnegative capacity changes the game.
    require(building(result, center.id).after.labor == Labor{0, 6, 6, -4, 0} &&
            building(result, center.id).after.flags == 0x1606 &&
            territory(result, 1).assignedLabor == 8 && territory(result, 1).unassignedLabor == 12,
            "later priority slot can generate negative labor in an empty slot exactly as the original");
    auto applied = std::make_unique<save::Document>(*d);
    for (size_t i = 0; i < result.buildings.size(); ++i) {
        const auto& after = result.buildings[i].after;
        applied->buildings[i].flags = after.flags;
        tasks(applied->buildings[i], after.tasks);
        labor(applied->buildings[i], after.labor);
    }
    for (size_t i = 0; i < result.territories.size(); ++i) {
        const auto& after = result.territories[i];
        applied->territories[i].data.morale = after.moraleAfter;
        std::copy(after.materialsAfter.begin(), after.materialsAfter.end(), applied->territories[i].data.materials);
    }
    (void)plan(*applied); // Reapplication accepts its own signed output; no idempotence promise.

    auto unowned = fixture();
    unowned->territories[1].data.population = 400;
    auto& b = addBuilding(*unowned, 6, 14, 2);
    tasks(b, {21, 13, 15, 12, 7}); labor(b, {2, 2, 2, 2, 2}); b.flags = 0x1f06;
    result = plan(*unowned);
    require(building(result, b.id).after.tasks == Tasks{21, 13, 15, 12, 7} &&
            building(result, b.id).after.labor == Labor{0, 0, 2, 2, 0} &&
            building(result, b.id).after.flags == 0xc06,
            "unowned buildings retain saved tasks but still participate in all balance passes");
    const auto house = addBuilding(*unowned, 1, 0, 2).id;
    unowned->raceStats.v[24][2] = 300;
    unowned->territories[1].data.population = 1000;
    unowned->buildings[0].flags = 2; // Inactivate the nonhousing workload.
    result = plan(*unowned);
    require(building(result, house).after.labor == Labor{0, 5, 0, 0, 0},
            "unowned housing uses the unscaled table capacity without reading a nonexistent owner's race");
}

void signedInputLaborOracles() {
    struct Case { int16_t population; int32_t input; Labor after; int32_t assigned, unassigned; };
    constexpr Case cases[] = {
        {100, std::numeric_limits<int32_t>::min(), {0, 0, 0, 0, 0}, 0, 1},
        {100, std::numeric_limits<int32_t>::max(), {0, 1, 0, 0, 0}, 1, 0},
        {100, -32769, {0, 8, -7, 0, 0}, 1, 0},
        {1000, -3, {0, -3, 0, 0, 0}, -3, 13}
    };
    for (const auto& test : cases) {
        auto d = fixture();
        auto& farm = addBuilding(*d, 5, 14, 2); // Unowned: no task refresh obscures the input.
        d->territories[1].data.population = test.population;
        farm.labor[1] = test.input;
        const auto result = plan(*d);
        // The two minima each narrow to signed16. In particular -32769 becomes
        // 32767 after the first minimum, then capacity8; the resulting pool -7
        // is assigned to wood. Collapsing the minima/casts would change this.
        require(building(result, farm.id).after.labor == test.after &&
                territory(result, 2).assignedLabor == test.assigned &&
                territory(result, 2).unassignedLabor == test.unassigned,
                "signed input labor preserves both sequential short narrowings and the original pool arithmetic");
    }
}

void stockCapsAndOpaqueState() {
    auto d = fixture();
    constexpr std::array<int32_t, 11> before = {
        20001, -300, 0, 9999, 10000, 10001, std::numeric_limits<int32_t>::max(),
        std::numeric_limits<int32_t>::min(), 12000, 17, 10002
    };
    constexpr std::array<int32_t, 11> after = {
        20001, -300, 0, 9999, 10000, 10000, 10000,
        std::numeric_limits<int32_t>::min(), 10000, 17, 10000
    };
    for (auto& record : d->territories) {
        std::copy(before.begin(), before.end(), record.data.materials);
        record.data.production[3] = 0x13579;
        record.data.consumption[8] = -0x2468;
        record.data.colonyFlag = 0xabcd;
    }
    d->options.eventCount = 1;
    d->events.resize(1); d->events[0].text = {'A', 0, 0xff, 'B'};
    d->events[0].record.textLen = 4;
    d->localList = {0, 0xfeedface}; d->trailing = {0x00, 0xfe, 0x41};
    d->players[0].aiVtbl[0] = 0xdeadbeef;
    const auto report = plan(*d);
    for (const auto& t : report.territories)
        require(t.materialsBefore == before && t.materialsAfter == after,
                "only materials1..10 get an upper cap, including unowned stock; money and negative stock persist");
    require(d->options.turn == 41 && d->world.rngSeed == 0x12345678,
            "labor planning neither advances the turn nor changes the saved seed");
}

void validationAndGlobalPurity() {
    auto d = fixture();
    addBuilding(*d, 1, 0);
    addBuilding(*d, 6, 14).labor[1] = 3;
    const auto prior = plan(*d);
    auto destination = prior;
    save::Error error;
    const auto fails = [&](const char* message) {
        const auto input = snapshot(*d);
        require(!simulation::planLaborBalance(*d, destination, error), message);
        require(error.code != save::ErrorCode::None && !error.message.empty(),
                "invalid input returns an explicit diagnostic");
        require(destination == prior && snapshot(*d) == input,
                "failed planning preserves both prior destination and every input field");
    };
    d->territories[1].data.owner = -2; fails("owner below -1 must be rejected"); d->territories[1].data.owner = -1;
    d->territories[1].data.owner = 7; fails("owner above six must be rejected"); d->territories[1].data.owner = -1;
    d->players[0].race = 7; fails("out-of-range race read by owned housing must be rejected"); d->players[0].race = 2;
    d->buildings[1].type = 48; fails("building type outside table must be rejected"); d->buildings[1].type = 6;
    d->buildings[1].site = 36; fails("invalid site must be rejected"); d->buildings[1].site = 14;
    d->buildings[1].territory = 0; fails("sentinel territory is not a saved building location"); d->buildings[1].territory = 1;
    d->territories[0].data.sites[14].building.raw = 9999;
    fails("missing building ID must be rejected"); d->territories[0].data.sites[14].building.raw = d->buildings[1].id;
    d->buildings[1].id = d->buildings[0].id; fails("duplicate building IDs must be rejected"); d->buildings[1].id = 101;
    d->territories[1].data.index = 1; fails("territory index mismatch must be rejected"); d->territories[1].data.index = 2;
    d->header.isMap = 1; d->mapTerritories.resize(2);
    fails("map document cannot stand in for a labor-bearing saved game"); d->header.isMap = 0; d->mapTerritories.clear();

    // Failure after an earlier owned territory could already have been planned:
    // an unowned housing object receives no task refresh, so final placement
    // would write slot -1 in the original. Reject it atomically.
    const auto badId = addBuilding(*d, 1, 0, 2).id;
    tasks(d->buildings.back(), {});
    fails("housing without any task must reject the original slot-minus-one write");
    d->territories[1].data.sites[0].building.raw = 0;
    require(d->buildings.back().id == badId, "remove only the test's last building");
    d->buildings.pop_back();

    // Unused players have no phase requirements. Their index/race values must
    // never be eagerly validated just because they exist in the physical file.
    for (size_t player = 1; player < d->players.size(); ++player) {
        d->players[player].index = 255; d->players[player].race = -1;
    }
    require(plan(*d) == prior, "unused player metadata cannot alter or block planning");
    std::vector<uint8_t> globalState(sizeof(gs)), globalMisc(sizeof(gg));
    std::memcpy(globalState.data(), &gs, sizeof(gs)); std::memcpy(globalMisc.data(), &gg, sizeof(gg));
    const auto seed = rtl::seed(), seedHi = rtl::seedHi();
    const auto source = snapshot(*d);
    require(plan(*d) == plan(*d), "repeating the same pure query is deterministic");
    d->players[0].race = 7; fails("failure also has no global effects"); d->players[0].race = 2;
    require(snapshot(*d) == source && std::memcmp(globalState.data(), &gs, sizeof(gs)) == 0 &&
            std::memcmp(globalMisc.data(), &gg, sizeof(gg)) == 0 && rtl::seed() == seed && rtl::seedHi() == seedHi,
            "success and failure preserve global game state and both global RNG words");
}

void corpus(const std::filesystem::path& directory) {
    namespace fs = std::filesystem;
    if (directory.empty()) { std::cout << "labor optional corpus: no data directory\n"; return; }
    size_t documents = 0, buildings = 0;
    const auto inspect = [&](const save::Document& d, const std::string& label) {
        try {
            const auto report = plan(d);
            require(plan(d) == report, "corpus query deterministic for unchanged input");
            // Do not impose a nonnegative output or idempotent application:
            // the original ordered passes have counterexamples tested above.
            for (const auto& t : report.territories) {
                require(t.materialsAfter[0] == t.materialsBefore[0], "corpus money is never capped");
                for (size_t resource = 1; resource < 11; ++resource)
                    require(t.materialsAfter[resource] == std::min(t.materialsBefore[resource], int32_t(10000)),
                            "corpus stock cap is upper-only");
            }
            buildings += report.buildings.size(); ++documents;
        } catch (const std::exception& error) {
            throw std::runtime_error(label + ": " + error.what());
        }
    };
    for (const char* relative : {"TUTORIAL.SAV", "Saves/AUTOSAVE.SAV", "Campaign/AUTOSAVE.CPN", "Campaign/ChCht001.CPN"}) {
        const auto path = directory / relative;
        if (!fs::is_regular_file(path)) continue;
        auto d = std::make_unique<save::Document>();
        save::Error error;
        if (!save::readDocument(path, *d, error)) throw std::runtime_error(error.message);
        inspect(*d, relative);
    }
    if (fs::is_regular_file(directory / "LEVELS.HDX") && fs::is_regular_file(directory / "LEVELS.HDD")) {
        HdxArchive archive;
        std::string why;
        if (!archive.open((directory / "LEVELS").string(), &why)) throw std::runtime_error(why);
        for (const auto& entry : archive.entries()) {
            auto d = std::make_unique<save::Document>();
            save::Error error;
            if (!save::readScenario(directory / "LEVELS", entry.name, *d, error)) throw std::runtime_error(error.message);
            inspect(*d, "LEVELS:" + entry.name);
        }
    }
    std::cout << "labor optional corpus: " << documents << " documents, " << buildings << " buildings\n";
}
} // namespace

int main(int argc, char** argv) {
    try {
        laborPoolOracles();
        constructionAndOverflow();
        upgradeAndConstructionTransition();
        technologyMasksAndShrines();
        redistributionQueuesAndLocks();
        transferDependency();
        prioritiesAndOrder();
        inactiveHousingAndCapacity();
        generatedNegativeLaborAndUnownedTasks();
        signedInputLaborOracles();
        stockCapsAndOpaqueState();
        validationAndGlobalPurity();
        corpus(argc > 1 ? std::filesystem::path(argv[1]) : std::filesystem::path{});
        std::cout << "labor_balance: numeric oracles, refresh, queues, locks, ordered balance, signed quirks, caps and purity passed\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "labor_balance: " << error.what() << '\n';
        return 1;
    }
}
