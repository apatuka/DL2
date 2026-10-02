// Integration/identity contracts, independent of the standalone rule oracles.
#include "game/runtime_state.h"
#include "game/data_tables.h"
#include "game/save_files.h"
#include <bit>
#include <cstring>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>

namespace {
using namespace dl2;
using namespace dl2::simulation;
void check(bool value, const char* message) { if (!value) throw std::runtime_error(message); }
void ok(bool value, const save::Error& error) { if (!value) throw std::runtime_error(error.message); }
std::unique_ptr<save::Document> fixture() {
    auto d = std::make_unique<save::Document>();
    std::memcpy(d->header.text, save::kHeaderText, sizeof(save::kHeaderText));
    d->header.version = kSaveVersion; d->options.numPlayers = 2; d->options.localPlayer = 0;
    d->options.turn = 19; d->options.gameId = 54; d->options.nextGlobalId = 411;
    d->world.width = d->world.height = 1; d->world.numTerritories = 1;
    d->territories.resize(1); d->tiles.resize(1);
    for (int p = 0; p < 7; ++p) {
        auto& player = d->players[size_t(p)];
        player.index = uint8_t(p); player.race = 2; player.type = p ? 3 : 1; player.credits = 1000;
        d->ministerJobs[size_t(p)].resize(1); d->ministerJobs[size_t(p)][0].type = 1;
        d->raceStats.v[24][p] = 100; d->raceStats.v[2][p] = 100;
    }
    auto& t = d->territories[0].data;
    t.index = 1; t.owner = 0; t.terrain = 1; t.numTiles = 1; t.population = 500; t.morale = 100;
    std::memcpy(t.name, "Alpha", 6);
    for (int s = 0; s < 36; ++s) {
        t.sites[s].unk_00 = uint16_t((s % 6) | ((s / 6) << 8)); t.sites[s].terrainFlags = 1;
    }
    for (int m = 1; m < 11; ++m) t.materials[m] = 2000;
    d->tiles[0].territory = 1;
    Building b{}; b.id = 2000; b.type = 1; b.category = 17; b.territory = 1;
    b.flags = 6; b.race = 2; b.task[1] = 20; b.labor[1] = 5;
    d->buildings.push_back(b); t.sites[0].building.raw = b.id; t.sites[0].terrainFlags |= 0x3000;
    return d;
}
std::vector<uint8_t> bytes(const save::Document& d) {
    std::vector<uint8_t> result; save::Error error;
    ok(save::encode(d, result, error), error);
    for (const auto& t : d.territories) {
        const auto* begin = reinterpret_cast<const uint8_t*>(&t.data);
        result.insert(result.end(), begin + kTerritorySavedBytes, begin + sizeof(Territory));
    }
    return result;
}
UnitManufacturingContext context() {
    UnitManufacturingContext c; SessionRng rng; save::Error error;
    ok(rng.initialize(54, error), error);
    c.effects.events.rngBeforeEvents = c.effects.ai.rng = c.effects.log.rngAfterEvents = rng.snapshot();
    c.effects.payment.selectedTerritory = 1; return c;
}
void follow(UnitManufacturingContext& c, const UnitManufacturingReport& r) {
    c.effects.log = r.logAfter; c.effects.ai = r.aiAfter;
    c.effects.events.rngBeforeEvents = r.rngAfter; c.effects.payment.collection = r.collectionAfter;
}
void runtimeContracts() {
    auto d = fixture(); d->players[1].type = 2; // Untouched remote human, not an AI effect recipient.
    const auto archived = bytes(*d); save::Error error;
    runtime::State state; ok(state.prepare(*d, error), error);
    const auto territory = state.territoryByIndex(1);
    const auto tile = state.tileByIndex(1);
    const auto housing = state.buildingById(2000);
    const auto queue = state.graph().territories[0].queues[0];
    auto ctx = context(); UnitManufacturingReport result;
    ok(state.queueUnit({1, 1}, ctx, result, error), error);
    check(result.queued && result.queue == 1 && state.document()->players[0].credits == 965, "queue charges canonical35 credits");
    check(!state.aiSession(), "local queue does not require unrelated human-to-AI load conversion");
    follow(ctx, result);
    const auto first = state.queue(queue)->first;
    check(state.queueNode(first) && state.queueNode(first)->record.count == 30, "queue count field is remaining30work");
    runtime::BuildingHandle defense; BuildingCreationReport created;
    ok(state.createCompletedBuilding({1, 29, 4}, defense, created, error), error);
    check(state.queueNode(first) && state.building(housing) && state.building(defense), "unrelated entity edits preserve queue-node identities");
    ok(state.queueUnit({1, 1}, ctx, result, error), error); follow(ctx, result);
    check(state.queue(queue)->count == 2 && !state.queueNode(first), "append retires positional node handles, preserves queue handle");
    const auto nextFirst = state.queue(queue)->first;
    const auto second = state.queueNode(nextFirst)->next;
    UnitDequeueReport removed;
    ok(state.dequeueUnit({1, 1, 1}, removed, error), error);
    check(removed.removed && removed.creditsRefunded == 35 && !state.queueNode(second) && !state.queueNode(nextFirst), "cancel refunds and retires positional handles");
    const auto unchanged = state.queue(queue)->first;
    ok(state.dequeueUnit({1, 1, 77}, removed, error), error);
    check(!removed.removed && state.queueNode(unchanged), "missing ordinal is ordinary denial with unchanged node generation");
    const auto before = bytes(*state.document()); const auto oldReport = result; const auto rng = state.sessionRng();
    check(!state.produceUnits({1, 0, 30}, ctx, result, error) && !error.message.empty(), "invalid queue fails explicitly");
    check(bytes(*state.document()) == before && result == oldReport && state.sessionRng() == rng && state.queueNode(unchanged), "failed edit preserves all outputs and handles");
    ok(state.produceUnits({1, 1, 29}, ctx, result, error), error); follow(ctx, result);
    check(result.createdIds.empty() && state.queueNode(state.queue(queue)->first)->record.count == 1 && !state.queueNode(unchanged), "29work leaves one, no premature spawn");
    const auto prior = ctx;
    ok(state.produceUnits({1, 1, 1}, ctx, result, error), error); follow(ctx, result);
    check(result.createdIds.size() == 1 && state.queue(queue)->count == 0 && result.events.size() == 2, "final work creates real unit and completion/queue-empty events");
    const auto army = state.armyById(result.createdIds[0]);
    check(state.army(army) && state.army(army)->type == 1 && state.armyLinks(army), "manufactured unit has owned stable identity and links");
    const auto completed = bytes(*state.document()); const auto finishedReport = result;
    check(!state.queueUnit({1, 1}, prior, result, error), "old RNG/log continuation cannot be replayed");
    check(bytes(*state.document()) == completed && result == finishedReport && state.army(army), "rewind denial is atomic");
    auto wrongCities = ctx; wrongCities.effects.events.citiesBeforeLoad[0] = 1;
    check(!state.queueUnit({1, 1}, wrongCities, result, error) && bytes(*state.document()) == completed,
          "city counters used for new event portraits cannot be silently replaced");
    runtime::BuildingHandle newHousing; ConstructionOrderReport order;
    ok(state.startConstruction({1, 1, 2}, ctx.effects, newHousing, order, error), error);
    BuildingProgressContext work{order.logAfter, ctx.effects.events, order.aiAfter};
    work.events.rngBeforeEvents = order.rngAfter;
    BuildingProgressReport progress;
    ok(state.progressBuildingWork(1, work, progress, error), error);
    check(!state.aiSession(), "local building completion needs no fabricated AI initialization");
    check(state.building(newHousing) && state.building(newHousing)->turnsLeft == 0 && state.building(newHousing)->task[1] == 20,
          "paid construction chains to assigned-labor completion and housing tasks");
    check(state.buildingById(state.building(newHousing)->id) == newHousing && state.army(army) && state.building(housing),
          "completion preserves original and created entity identities");
    check(state.territory(territory) && state.tile(tile) && state.queue(queue) && state.document()->options.turn == 19,
          "static handles survive edits and no partial step increments turn");
    auto snapshot = fixture(); const auto saved = bytes(*snapshot);
    check(!state.capture(*snapshot, error) && bytes(*snapshot) == saved && !state.advanceTurn(error), "partial production cannot save or advance turn");
    runtime::State foreign; ok(foreign.prepare(*d, error), error);
    check(!foreign.queue(queue) && !foreign.army(army) && !foreign.building(newHousing), "foreign handles rejected");
    runtime::State moved = std::move(state);
    check(moved.queue(queue) && moved.army(army) && moved.building(newHousing) && !state.queue(queue), "move transfers owned identities");
    ok(moved.prepare(*d, error), error);
    check(!moved.queue(queue) && !moved.army(army) && !moved.building(newHousing), "replacement retires old identities");
    check(bytes(*d) == archived, "original input never modified");
}
void identicalRepeatRetiresNode() {
    auto d = fixture(); d->territories[0].data.hoverway = 2; // queue1 repeat bit
    runtime::State state; save::Error error; ok(state.prepare(*d, error), error);
    auto ctx = context(); UnitManufacturingReport result;
    ok(state.queueUnit({1, 1}, ctx, result, error), error); follow(ctx, result);
    const auto queue = state.graph().territories[0].queues[0];
    const auto node = state.queue(queue)->first;
    const auto record = state.queueNode(node)->record;
    ok(state.produceUnits({1, 1, 30}, ctx, result, error), error);
    check(result.createdIds.size() == 1 && result.queueStructureChanged && state.queue(queue)->count == 1,
          "automatic repeat creates a unit then replaces the queue node");
    const auto replacement = state.queue(queue)->first;
    check(std::memcmp(&record, &state.queueNode(replacement)->record, kQueueRecordSaved) == 0,
          "repeat regression setup has byte-identical queue record");
    check(replacement != node && !state.queueNode(node), "same bytes cannot resurrect a retired manufacturing node");
}
void lateEventFailureIsAtomic() {
    auto d = fixture(); std::memset(d->territories[0].data.name, 'X', sizeof(d->territories[0].data.name));
    QueueRecord record{}; record.unitType = 1; record.count = 1; record.data[0] = 35;
    d->territories[0].queues[0].push_back(record);
    runtime::State state; save::Error error; ok(state.prepare(*d, error), error);
    const auto queue = state.graph().territories[0].queues[0], foreignQueue = runtime::QueueHandle{};
    const auto node = state.queue(queue)->first;
    const auto before = bytes(*state.document()); const auto rng = state.sessionRng();
    UnitManufacturingReport report; report.createdIds = {999}; const auto previous = report;
    check(!state.produceUnits({1, 1, 1}, context(), report, error) && error.message.find("terminator") != std::string::npos,
          "unterminated event name fails after candidate unit creation");
    check(bytes(*state.document()) == before && state.sessionRng() == rng && report == previous && state.queueNode(node) &&
          state.stage() == runtime::Stage::Prepared && !state.loadedEvents() && !state.resourceCollection() && !state.queue(foreignQueue),
          "late runtime failure preserves document, queue epoch, RNG, context and report");
}
}
int main() {
    try { runtimeContracts(); identicalRepeatRetiresNode(); lateEventFailureIsAtomic(); std::cout << "manufacturing runtime: owned continuations, queue epochs, stable entities, atomic errors and nonturn boundaries passed\n"; return 0; }
    catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}
