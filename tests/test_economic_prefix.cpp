#include "game/runtime_state.h"
#include "game/data_tables.h"
#include "game/save_files.h"
#include <algorithm>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <memory>
#include <stdexcept>

namespace {
using namespace dl2;
using namespace dl2::simulation;
void check(bool yes, const char* why) { if (!yes) throw std::runtime_error(why); }
void ok(bool yes, const save::Error& error) { if (!yes) throw std::runtime_error(error.message); }
void addBuilding(save::Document& d, uint16_t id, int type, int site) {
    Building b{}; b.id = id; b.type = uint8_t(type); b.category = data::kBuildingTypes[type].category;
    b.race = 2; b.territory = 1; b.site = int8_t(site); b.flags = 6;
    std::copy(std::begin(data::kBuildingTypes[type].tasks), std::end(data::kBuildingTypes[type].tasks), std::begin(b.task));
    if (!d.buildings.empty()) { b.prev.raw = d.buildings.back().id; d.buildings.back().next.raw = id; }
    d.buildings.push_back(b); d.territories[0].data.sites[site].building.raw = id;
}
std::unique_ptr<save::Document> fixture() {
    auto d = std::make_unique<save::Document>();
    std::memcpy(d->header.text, save::kHeaderText, sizeof(save::kHeaderText)); d->header.version = kSaveVersion;
    d->options.numPlayers = 2; d->options.localPlayer = 0; d->options.turn = 19; d->options.nextGlobalId = 1000;
    d->world.width = d->world.height = 1; d->world.numTerritories = 1; d->territories.resize(1); d->tiles.resize(1);
    for (size_t p = 0; p < 7; ++p) {
        auto& player = d->players[p]; player.index = uint8_t(p); player.race = 2; player.type = p ? 3 : 1;
        player.credits = 1000; player.taxLevel = 2; player.lastIncome = 77;
        d->ministerJobs[p].resize(1); d->ministerJobs[p][0].type = 1;
        for (auto& row : d->raceStats.v) row[p] = 100;
    }
    auto& t = d->territories[0].data; t.index = 1; t.owner = 0; t.terrain = 1; t.numTiles = 1;
    t.population = 500; t.morale = 100; t.knowledge = 100; t.centerTile = 0; std::memcpy(t.name, "Alpha", 6);
    for (int s = 0; s < 36; ++s) { t.sites[s].unk_00 = uint16_t((s % 6) | ((s / 6) << 8)); t.sites[s].terrainFlags = 1; }
    for (int m = 1; m < 11; ++m) { t.materials[m] = 1000; t.production[m] = 999; t.consumption[m] = 888; }
    t.colonyFlag = 123; d->tiles[0].territory = 1; d->tiles[0].terrain = 1;
    addBuilding(*d, 100, 1, 0); d->buildings.back().labor[1] = 1;
    addBuilding(*d, 200, 15, 2); d->buildings.back().labor[4] = 4;
    QueueRecord q{}; q.unitType = 1; q.count = 1; q.data[0] = 35; d->territories[0].queues[0].push_back(q);
    addBuilding(*d, 300, 1, 4); auto& pending = d->buildings.back(); pending.flags = 4; pending.turnsLeft = 10;
    pending.task[0] = 2; pending.task[1] = 0; // Unpaid: no work in either pass.
    return d;
}
EconomicPrefixContext context() {
    EconomicPrefixContext c; SessionRng rng; save::Error e; ok(rng.initialize(123, e), e);
    c.effects.events.rngBeforeEvents = c.effects.ai.rng = c.effects.log.rngAfterEvents = rng.snapshot();
    c.effects.payment.collection.transfers.push_back({1, 1, 1, 77, 11});
    return c;
}
std::vector<uint8_t> bytes(const save::Document& d) {
    save::Error e; std::vector<uint8_t> out; ok(save::encode(d, out, e), e);
    for (const auto& t : d.territories) {
        const auto* p = reinterpret_cast<const uint8_t*>(&t.data);
        out.insert(out.end(), p + kTerritorySavedBytes, p + sizeof(Territory));
    }
    return out;
}
const std::vector<EconomicStep> order{EconomicStep::Reset, EconomicStep::Taxes, EconomicStep::PrimaryProduction,
    EconomicStep::RecordNeeds, EconomicStep::Imports, EconomicStep::Food, EconomicStep::Energy,
    EconomicStep::Upkeep, EconomicStep::Refinement, EconomicStep::BuildingCosts};
void connectedSequenceAndHandles() {
    auto d = fixture(); auto c = context(); const auto original = bytes(*d); save::Error e;
    runtime::State state; ok(state.prepare(*d, e), e);
    const auto housing = state.buildingById(100), factory = state.buildingById(200), pending = state.buildingById(300);
    const auto territory = state.territoryByIndex(1); const auto queue = state.graph().territories[0].queues[0];
    const auto node = state.queue(queue)->first;
    auto r = std::make_unique<EconomicPrefixReport>();
    ok(state.runEconomicProductionPrefix(c, *r, e), e);
    check(r->completed == order && state.stage() == runtime::Stage::EconomyPrefixApplied, "ten contiguous original steps, explicit terminal prefix stage");
    check(r->createdIds.size() == 1 && r->primary.territories[0].totals.queues[1] > 0 &&
          r->primary.territories[0].manufacturing[0].productionBefore == r->primary.territories[0].totals.queues[1],
          "factory's actual assigned output feeds manufacturing");
    const auto newArmy = state.armyById(r->createdIds[0]);
    check(state.army(newArmy) && state.armyLinks(newArmy) && state.queue(queue)->count == 0 && !state.queueNode(node),
          "manufactured army has stable identity; consumed positional node is retired");
    check(r->food.armies.size() == 1 && r->food.armies[0].army == r->createdIds[0] && r->upkeep.players[0].unitCounts[0] == 1,
          "new unit consumes food and owes upkeep during same sequence");
    check(r->food.territories[0].stockBefore == 1000 && r->food.territories[0].consumed == 5 &&
          r->energy.energy.territories[0].need == 5 && r->upkeep.players[0].totalCost == 1,
          "civilian demand, energy and upkeep are evaluated in order");
    check(state.building(pending)->flags == 6 && state.building(pending)->turnsLeft == 10 &&
          state.document()->territories[0].data.materials[3] == 990 && r->costs.buildings.size() == 1,
          "pending finance occurs after BOTH passes; does not receive work retroactively");
    check(state.document()->players[0].credits == r->taxes.creditsAfter[0] - 1,
          "tax gains precede production and upkeep; already-paid queue/base building money not charged twice");
    check(state.document()->players[0].lastIncome == 0 && state.document()->players[1].lastIncome == 0 &&
          state.document()->players[2].lastIncome == 77 && state.document()->territories[0].data.colonyFlag == 0,
          "prefix resets only declared player count and territory healing");
    check(std::all_of(std::begin(state.document()->territories[0].data.consumption),
          std::end(state.document()->territories[0].data.consumption), [](int n) { return n == 0; }) && r->collectionAfter.transfers.empty(),
          "reset removes old consultation balances and transfer ledger");
    check(state.building(housing) && state.building(factory) && state.territory(territory) && state.document()->options.turn == 19,
          "surviving/static handles remain and turn not incremented");
    const auto finalBytes = bytes(*state.document()); const auto finalLog = r->logAfter;
    const auto finalRng = state.sessionRng(); const auto finalSteps = r->completed;
    check(!state.runEconomicProductionPrefix(c, *r, e) && bytes(*state.document()) == finalBytes && r->completed == finalSteps,
          "prefix cannot be run twice on same experimental state");
    auto target = fixture(); check(!state.capture(*target, e) && !state.advanceTurn(e), "prefix cannot export/advance a complete game");
    UnitDequeueReport dq; check(!state.dequeueUnit({1, 1, 0}, dq, e), "no unrelated structural edits after incomplete economic prefix");
    check(state.sessionRng() == finalRng && *state.loadedEvents() == finalLog && state.army(newArmy), "rejections preserve continuations and handles");
    auto alias = std::make_unique<save::Document>(*d); auto again = std::make_unique<EconomicPrefixReport>();
    ok(runEconomicProductionPrefix(*alias, c, *alias, *again, e), e);
    check(bytes(*alias) == finalBytes && again->logAfter == finalLog && again->rngAfter == finalRng,
          "pure alias prefix and runtime wrapper agree exactly");
    runtime::State moved = std::move(state);
    check(moved.army(newArmy) && moved.building(housing) && !state.army(newArmy), "prefix state move retains identities");
    check(bytes(*d) == original, "archive source never changed");
}
void createdThenDisbanded() {
    auto d = fixture(); d->players[0].foodFlags = 4;
    runtime::State state; save::Error e; ok(state.prepare(*d, e), e);
    const auto housing = state.buildingById(100); const auto queue = state.graph().territories[0].queues[0];
    auto r = std::make_unique<EconomicPrefixReport>(); ok(state.runEconomicProductionPrefix(context(), *r, e), e);
    check(r->createdIds.size() == 1 && r->retiredIds == r->createdIds && state.document()->armies.empty() &&
          !state.armyById(r->createdIds[0]) && state.building(housing) && state.queue(queue),
          "unit created and disbanded in same transaction has no dangling registry slot");
}
void rollbackAfterUpkeep() {
    auto d = fixture();
    // A task force attached to the newly chosen old army fails during upkeep,
    // AFTER taxes, production, food and energy have all succeeded privately.
    d->territories[0].queues[0].clear(); Army a{}; a.id = 20; a.type = 1; a.unitClass = 1; a.owner = 0;
    a.dest.raw = a.territory.raw = a.origin.raw = 1; a.job = 1; std::memcpy(a.name, "Guard", 6);
    d->armies.push_back(a); d->territories[0].data.armies.raw = 20;
    d->jobs[0][0].owner = 0; d->jobs[0][0].armyIds[0] = 20; d->players[0].foodFlags = 4;
    runtime::State state; save::Error e; ok(state.prepare(*d, e), e); const auto army = state.armyById(20);
    const auto before = bytes(*state.document()); const auto rng = state.sessionRng();
    auto r = std::make_unique<EconomicPrefixReport>(); r->createdIds = {987}; r->completed = {EconomicStep::BuildingCosts};
    check(!state.runEconomicProductionPrefix(context(), *r, e) && !e.message.empty(), "unsafe task force disband rejects instead of inventing detach");
    check(bytes(*state.document()) == before && state.stage() == runtime::Stage::Prepared && state.army(army) &&
          state.sessionRng() == rng && !state.loadedEvents() && r->createdIds == std::vector<uint32_t>{987} &&
          r->completed == std::vector<EconomicStep>{EconomicStep::BuildingCosts}, "late failure rolls back every earlier step, report and handles");
    auto bad = context(); bad.effects.events.rngBeforeEvents.format = 99;
    check(!state.runEconomicProductionPrefix(bad, *r, e) && bytes(*state.document()) == before, "malformed initial RNG fails atomically");
}
void originalSaves(const std::filesystem::path& data) {
    int count = 0;
    for (const char* name : {"TUTORIAL.SAV", "Saves/AUTOSAVE.SAV", "Campaign/AUTOSAVE.CPN", "Campaign/ChCht001.CPN"}) {
        if (!std::filesystem::is_regular_file(data / name)) continue;
        auto d = std::make_unique<save::Document>(); save::Error e; ok(save::readDocument(data / name, *d, e), e);
        const auto before = bytes(*d); runtime::State state; ok(state.prepare(*d, e), e);
        auto c = context(); c.effects.payment.collection.transfers.clear();
        auto r = std::make_unique<EconomicPrefixReport>(); ok(state.runEconomicProductionPrefix(c, *r, e), e);
        check(r->completed == order && state.document()->options.turn == d->options.turn && bytes(*d) == before,
              "real-save prefix runs with explicit cold context, no claim of original live-session replay");
        ++count;
    }
    std::cout << "economic prefix: " << count << " read-only original saves passed\n";
}
}
int main(int argc, char** argv) {
    try { connectedSequenceAndHandles(); createdThenDisbanded(); rollbackAfterUpkeep();
        if (argc > 1) originalSaves(argv[1]); std::cout << "economic_prefix: PASS\n"; return 0;
    } catch (const std::exception& e) { std::cerr << e.what() << '\n'; return 1; }
}
