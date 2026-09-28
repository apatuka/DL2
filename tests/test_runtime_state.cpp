// Headless runtime preparation: real references, no legacy-global activation.
#include "game/runtime_state.h"
#include "game/save_files.h"
#include "game/globals.h"
#include "game/rtl_compat.h"

#include <algorithm>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace {
using namespace dl2;
using save::Document;
namespace rt = runtime;
namespace fs = std::filesystem;

void require(bool condition, const char* message) {
    if (!condition) throw std::runtime_error(message);
}

std::vector<uint8_t> encoded(const Document& d) {
    save::Error error;
    std::vector<uint8_t> result;
    if (!save::encode(d, result, error)) throw std::runtime_error("encode: " + error.message);
    return result;
}

bool samePlan(const simulation::TaxPlan& a, const simulation::TaxPlan& b) {
    if (a.creditsBefore != b.creditsBefore || a.creditsAfter != b.creditsAfter ||
        a.collected != b.collected || a.territories.size() != b.territories.size()) return false;
    for (size_t i = 0; i < a.territories.size(); ++i) {
        const auto& x = a.territories[i]; const auto& y = b.territories[i];
        if (x.territory != y.territory || x.owner != y.owner ||
            x.calculated != y.calculated || x.applied != y.applied) return false;
    }
    return true;
}

simulation::TaxPlan sentinelReport() {
    simulation::TaxPlan report;
    report.creditsBefore.fill(1234); report.creditsAfter.fill(-9876);
    report.collected.fill(42); report.territories.push_back({77, 5, -32, -32});
    return report;
}

std::unique_ptr<Document> fixture() {
    auto d = std::make_unique<Document>();
    std::memcpy(d->header.text, save::kHeaderText, sizeof(save::kHeaderText));
    d->header.version = kSaveVersion; d->header.minusOne = -1; d->header.pad[51] = 0xa5;
    d->options.turn = 17; d->options.numPlayers = 2; d->options.playersMask = 3;
    d->options.gameSeed = 0x11223344; d->options.gameId = 7654;
    d->world.width = 2; d->world.height = 2; d->world.numTerritories = 2;
    d->world.rngSeed = 0x55667788;
    for (int p = 0; p < kMaxPlayers; ++p) {
        d->players[p].index = uint8_t(p); d->players[p].race = int8_t(p);
        d->players[p].credits = 123 + p * 100; d->players[p].taxLevel = 2;
        d->raceStats.v[26][p] = 100;
        d->ministerJobs[p].resize(1);
    }
    d->players[0].type = 1; d->players[1].type = 3;
    d->players[0].homeTerritory = 1; d->players[1].homeTerritory = 2;
    d->localList = {0xdead1234, 0x76543210};
    d->ministerJobs[0].resize(3);
    for (size_t i = 0; i < 3; ++i) {
        auto& node = d->ministerJobs[0][i];
        node.type = i ? 2 : 1;
        node.next.raw = i < 2 ? uint32_t(0xdead0000 + i * 0x44) : 0;
        node.prev.raw = i ? uint32_t(0xbeef0000 + i * 0x44) : 0;
        node.priority = int(i * 9);
    }
    d->tiles.resize(4);
    for (int y = 0; y < 2; ++y) for (int x = 0; x < 2; ++x) {
        auto& tile = d->tiles[size_t(y * 2 + x)];
        tile.x = uint8_t(x); tile.y = uint8_t(y); tile.territory = int16_t(x + 1);
    }
    d->territories.resize(2);
    for (int i = 0; i < 2; ++i) {
        auto& t = d->territories[size_t(i)].data;
        t.index = uint16_t(i + 1); t.owner = int8_t(i); t.terrain = 1;
        t.population = int16_t(i ? 900 : 400); t.morale = 80; t.knowledge = 100;
        t.numTiles = 2; t.tiles[0].raw = uint32_t(i); t.tiles[1].raw = 0x10000u | uint32_t(i);
        t.adjacency[0] = uint16_t(1u << (i ? 1 : 2));
        t.materials[1] = 700; t.materials[2] = 900;
    }
    d->buildings.resize(2);
    auto& first = d->buildings[0];
    first.id = 50000; first.type = 37; first.category = 9; first.race = 0;
    first.territory = 1; first.site = 0; first.next.raw = 7;
    auto& second = d->buildings[1];
    second.id = 7; second.type = 1; second.category = 17; second.race = 1;
    second.territory = 2; second.site = 0; second.prev.raw = 50000;
    d->territories[0].data.sites[0].building.raw = first.id;
    d->territories[1].data.sites[0].building.raw = second.id;
    d->armies.resize(2);
    auto& moving = d->armies[0];
    moving.id = 60000; moving.type = 1; moving.owner = 0; moving.health = 100;
    moving.territory.raw = 1; moving.dest.raw = 2; moving.origin.raw = 1;
    moving.prev.raw = 42; moving.cargo[0].raw = 42;
    auto& stationary = d->armies[1];
    stationary.id = 42; stationary.type = 1; stationary.owner = 1; stationary.health = 100;
    stationary.territory.raw = stationary.dest.raw = 1; stationary.origin.raw = 2;
    stationary.next.raw = 60000;
    // This old list includes the moved unit. Canonical membership must use +0x3c.
    d->territories[0].data.armies.raw = 42;
    d->territories[1].data.foreignArmies.raw = 60000;
    auto& queue = d->territories[0].queues[0];
    queue.resize(2); queue[0].unitType = 1; queue[0].count = 9; queue[0].data[10] = -27;
    queue[1].unitType = 2; queue[1].count = 3;
    queue[0].next.raw = 0xdeadbeef; queue[1].next.raw = 0xbaadf00d;
    d->territories[0].data.queues[0].raw = 0xfeed1234;
    d->jobs[0][0].destination.raw = 2;
    d->jobs[0][0].armyIds[0] = 60000; d->jobs[0][0].armyIds[1] = 42;
    d->jobs[0][0].armies[0].raw = 0x00645370;
    d->jobs[0][0].armies[1].raw = 0xffffffff;
    d->scratchJob1.destination.raw = 0x005a43d0;
    d->scratchJob2.armies[0].raw = 0xdeadbeef;
    d->events.resize(1); d->options.eventCount = 1;
    d->events[0].record = {12, 4, 0, 99}; d->events[0].text = {'a', 0, 'b', 0xff};
    d->trailing = {0xde, 0xad, 0, 0xff};
    return d;
}

void diagnostics(const save::Error& error) {
    require(error.code != save::ErrorCode::None && !error.message.empty(), "failure needs a diagnostic");
}

void safeAccessors(const rt::State& state) {
    constexpr uint32_t bad = std::numeric_limits<uint32_t>::max();
    require(!state.buildingById(0) && !state.buildingById(bad), "unknown building ID must be null");
    require(!state.armyById(0) && !state.armyById(bad), "unknown army ID must be null");
    require(!state.building({}) && !state.building({bad}), "building bounds");
    require(!state.army({}) && !state.army({bad}), "army bounds");
    require(!state.territory({}) && !state.territory({bad}), "territory bounds");
    require(!state.tile({}) && !state.tile({bad}), "tile bounds");
    require(!state.queue({}) && !state.queue({bad}), "queue bounds");
    require(!state.queueNode({}) && !state.queueNode({bad}), "queue-node bounds");
    require(!state.minister({}) && !state.minister({bad}), "minister bounds");
}

void checkGraph(const rt::State& state) {
    const auto& g = state.graph();
    require(g.buildings.size() == 2 && g.armies.size() == 2 && g.territories.size() == 2,
            "runtime object arrays must be dense and omit a dummy slot");
    require(state.buildingById(50000).slot == 1 && state.buildingById(7).slot == 2,
            "building IDs are not dense handles");
    require(state.armyById(60000).slot == 1 && state.armyById(42).slot == 2,
            "army IDs are not dense handles");
    require(state.building({1})->id == 50000 && state.army({1})->id == 60000,
            "typed accessors resolve the owning document");
    require(g.buildings[0].territory.slot == 1 && g.buildings[0].next.slot == 2 &&
            g.buildings[1].previous.slot == 1 && !g.buildings[1].next, "building links");
    require(g.armies[0].current.slot == 2 && g.armies[0].turnStart.slot == 1 &&
            g.armies[0].routeOrigin.slot == 1, "Army +0x3c is current, +0x38 is turn start");
    require(g.armies[0].previous.slot == 2 && !g.armies[0].next &&
            g.armies[0].cargo[0].slot == 2 && !g.armies[0].cargo[1], "army links and cargo");
    require(g.territories[0].armies == std::vector<rt::ArmyHandle>{{2}} &&
            g.territories[1].armies == std::vector<rt::ArmyHandle>{{1}}, "canonical current-territory membership");
    require(g.territories[0].savedOwnHead.slot == 2 && g.territories[1].savedForeignHead.slot == 1,
            "historical heads resolve separately from canonical membership");
    require(g.territories[0].buildings == std::vector<rt::BuildingHandle>{{1}} &&
            g.territories[1].sites[0].slot == 2, "building membership and site links");
    require(g.territories[0].tiles == std::vector<rt::TileHandle>{{1}, {3}} &&
            g.territories[1].tiles == std::vector<rt::TileHandle>{{2}, {4}}, "file coordinates resolve to dense tile handles");
    require(state.tile({1})->x == 0 && state.tile({1})->y == 0 &&
            state.tile({4})->x == 1 && state.tile({4})->y == 1, "zero coordinate is not a null tile");
    require(g.territories[0].adjacent == std::vector<rt::TerritoryHandle>{{2}} &&
            g.territories[1].adjacent == std::vector<rt::TerritoryHandle>{{1}}, "adjacency bit numbering");
    require(g.playerTerritories[0] == std::vector<rt::TerritoryHandle>{{1}} &&
            g.playerTerritories[1] == std::vector<rt::TerritoryHandle>{{2}}, "player territory membership");
    const auto* queue = state.queue(g.territories[0].queues[0]);
    require(g.queues.size() == 10 && g.queueNodes.size() == 2, "five owned queues per territory, including empty queues");
    require(queue && queue->count == 2 && queue->first == queue->cursor, "queue cursor starts at first node");
    const auto* first = state.queueNode(queue->first);
    require(first && first->record.unitType == 1 && first->record.count == 9 &&
            first->record.data[10] == -27 && first->record.next.raw == 0, "queue payload and cleared raw next");
    const auto* last = state.queueNode(first->next);
    require(last && last->record.unitType == 2 && last->record.count == 3 &&
            last->record.next.raw == 0 && !last->next, "queue links rebuilt from physical order");
    for (const auto& territory : g.territories) for (auto handle : territory.queues) {
        const auto* q = state.queue(handle);
        require(q != nullptr, "every territory queue needs a valid owned handle");
        if (q->count == 0) require(!q->first && !q->cursor, "empty queue must have null cursors");
    }
    auto ministerHandle = g.ministerHeads[0];
    rt::MinisterHandle previous{};
    for (uint32_t i = 0; i < 3; ++i) {
        const auto* minister = state.minister(ministerHandle);
        require(minister && minister->player == 0 && minister->recordIndex == i &&
                minister->previous == previous, "minister file-order links");
        previous = ministerHandle; ministerHandle = minister->next;
    }
    require(!ministerHandle, "minister tail must terminate regardless of stale pointer values");
    require(g.jobs[0][0].destination.slot == 2 && g.jobs[0][0].armies[0].slot == 1 &&
            g.jobs[0][0].armies[1].slot == 2 && !g.jobs[0][0].armies[2], "jobs resolve armyIds, not raw pointers");
    safeAccessors(state);
}

void onlyCreditsChanged(const Document& before, const Document& after) {
    const auto oldBytes = encoded(before), newBytes = encoded(after);
    require(oldBytes.size() == newBytes.size(), "tax phase changed serialized length");
    const size_t playersOffset = sizeof(SaveHeader) + sizeof(GameOptions) + sizeof(WorldParams);
    for (size_t i = 0; i < oldBytes.size(); ++i) {
        if (oldBytes[i] == newBytes[i]) continue;
        require(i >= playersOffset && i < playersOffset + sizeof(Player) * kMaxPlayers,
                "tax phase changed a non-player byte");
        const size_t field = (i - playersOffset) % sizeof(Player);
        require(field >= offsetof(Player, credits) && field < offsetof(Player, credits) + sizeof(int32_t),
                "tax phase changed a non-credit player byte");
    }
    require(after.options.turn == before.options.turn, "fiscal subphase must not advance a turn");
}

void prepareAndTransactions() {
    auto source = fixture(); const auto original = encoded(*source);
    rt::State state; save::Error error;
    auto destination = fixture(); destination->options.turn = 90210;
    const auto destinationBefore = encoded(*destination);
    require(state.stage() == rt::Stage::Empty && !state.document(), "new state must be empty");
    safeAccessors(state);
    require(!state.capture(*destination, error), "empty capture must fail"); diagnostics(error);
    require(encoded(*destination) == destinationBefore, "empty capture changed destination");
    auto report = sentinelReport(); const auto priorReport = report;
    require(!state.collectTaxes(report, error), "empty fiscal phase must fail"); diagnostics(error);
    require(samePlan(report, priorReport), "failed fiscal phase changed report");
    require(!state.advanceTurn(error), "empty full turn is unsupported"); diagnostics(error);
    require(state.prepare(*source, error) && error.code == save::ErrorCode::None, "prepare synthetic runtime");
    require(state.stage() == rt::Stage::Prepared && state.document() != source.get(), "state must own a prepared copy");
    checkGraph(state);
    require(state.capture(*destination, error) && encoded(*destination) == original, "prepared capture must be byte exact");
    require(encoded(*source) == original, "prepare changed source document");
    source->players[0].credits += 999;
    require(encoded(*state.document()) == original, "runtime aliases the caller's document");
    auto reject = [&](const Document& bad) {
        const auto* owned = state.document();
        require(!state.prepare(bad, error), "invalid runtime input accepted"); diagnostics(error);
        require(state.document() == owned && state.stage() == rt::Stage::Prepared &&
                encoded(*state.document()) == original, "failed prepare replaced previous state");
        checkGraph(state);
        require(state.capture(*destination, error) && encoded(*destination) == original,
                "failed prepare damaged capture");
    };
    auto bad = fixture(); bad->armies[1].id = bad->armies[0].id; reject(*bad);
    bad = fixture(); bad->territories[0].data.sites[0].building.raw = 65535; reject(*bad);
    bad = fixture(); bad->territories[0].data.owner = 7; reject(*bad);
    bad = fixture(); bad->armies[0].cargo[0].raw = 65535; reject(*bad);
    auto map = std::make_unique<Document>();
    map->header = source->header; map->header.isMap = 1; map->world = source->world;
    map->tiles = source->tiles; map->mapTerritories.resize(2);
    require(save::validate(*map, error), "map fixture must be physically valid"); reject(*map);
    require(!state.advanceTurn(error), "prepared full turn must not report success"); diagnostics(error);
    require(state.stage() == rt::Stage::Prepared && encoded(*state.document()) == original,
            "unsupported full turn changed state");
    rt::State moved(std::move(state));
    require(state.stage() == rt::Stage::Empty && !state.document(), "moved-from state must become empty");
    safeAccessors(state); checkGraph(moved);
    require(moved.capture(*destination, error) && encoded(*destination) == original,
            "move constructor separated the document and graph");
    state = std::move(moved);
    require(moved.stage() == rt::Stage::Empty && !moved.document(), "move assignment must empty the source");
    safeAccessors(moved); checkGraph(state);
}

void taxes(const Document& source, bool tutorial = false) {
    const auto original = encoded(source);
    rt::State left, right; save::Error error;
    if (!left.prepare(source, error) || !right.prepare(source, error)) throw std::runtime_error(error.message);
    auto snapshot = std::make_unique<Document>();
    require(left.capture(*snapshot, error) && encoded(*snapshot) == original, "corpus prepared capture mismatch");
    simulation::TaxPlan a, b;
    require(left.collectTaxes(a, error) && right.collectTaxes(b, error), "first fiscal subphase failed");
    require(error.code == save::ErrorCode::None && left.stage() == rt::Stage::TaxesApplied &&
            right.stage() == rt::Stage::TaxesApplied, "fiscal transition must be explicit");
    require(samePlan(a, b) && encoded(*left.document()) == encoded(*right.document()), "taxes must be deterministic");
    onlyCreditsChanged(source, *left.document());
    require(encoded(source) == original, "runtime fiscal phase changed source");
    for (size_t p = 0; p < source.players.size(); ++p)
        require(left.document()->players[p].credits == a.creditsAfter[p] &&
                a.creditsBefore[p] == source.players[p].credits, "fiscal report differs from resulting credits");
    if (tutorial) require(a.collected[0] == 20 && a.collected[1] == 32 &&
                          a.creditsAfter[0] == 520 && a.creditsAfter[1] == 532,
                          "TUTORIAL fiscal golden values differ");
    const auto partial = encoded(*left.document());
    const auto priorReport = a;
    require(!left.collectTaxes(a, error), "same preparation must not collect taxes twice"); diagnostics(error);
    require(samePlan(a, priorReport) && encoded(*left.document()) == partial,
            "repeated tax failure changed state or report");
    snapshot->options.turn = 90210; const auto snapshotBefore = encoded(*snapshot);
    require(!left.capture(*snapshot, error), "partial economic phase must not export a resumable save"); diagnostics(error);
    require(encoded(*snapshot) == snapshotBefore, "partial capture changed destination");
    require(!left.advanceTurn(error), "partial state must not pretend to advance a turn"); diagnostics(error);
    require(left.stage() == rt::Stage::TaxesApplied && encoded(*left.document()) == partial,
            "unsupported turn changed partial state");
    auto invalid = std::make_unique<Document>(source); invalid->territories[0].data.owner = 7;
    require(!left.prepare(*invalid, error), "invalid replacement of partial state accepted"); diagnostics(error);
    require(left.stage() == rt::Stage::TaxesApplied && encoded(*left.document()) == partial,
            "failed prepare lost the partial stage");
    require(left.prepare(source, error) && left.stage() == rt::Stage::Prepared &&
            left.capture(*snapshot, error) && encoded(*snapshot) == original, "fresh prepare must reset phase safely");
}

bool sameEnergy(const simulation::EnergyPlan& a, const simulation::EnergyPlan& b) {
    if (a.territories.size() != b.territories.size() || a.shortfalls.size() != b.shortfalls.size()) return false;
    for (size_t i = 0; i < a.territories.size(); ++i) {
        const auto& x = a.territories[i]; const auto& y = b.territories[i];
        if (x.territory != y.territory || x.energyBefore != y.energyBefore || x.need != y.need ||
            x.consumed != y.consumed || x.energyAfter != y.energyAfter ||
            x.energyPercentBefore != y.energyPercentBefore || x.energyPercentAfter != y.energyPercentAfter) return false;
    }
    for (size_t i = 0; i < a.shortfalls.size(); ++i) {
        const auto& x = a.shortfalls[i]; const auto& y = b.shortfalls[i];
        if (x.type != y.type || x.recipient != y.recipient || x.territory != y.territory || x.shortage != y.shortage) return false;
    }
    return true;
}

void energy(const Document& source) {
    const auto original = encoded(source);
    rt::State left, right; save::Error error;
    simulation::EnergyPlan a, b;
    require(!left.consumeEnergy(a, error), "empty energy experiment must fail"); diagnostics(error);
    require(left.prepare(source, error) && right.prepare(source, error), "prepare energy experiments");
    require(left.consumeEnergy(a, error) && right.consumeEnergy(b, error), "isolated energy failed");
    require(error.code == save::ErrorCode::None && left.stage() == rt::Stage::EnergyApplied,
            "energy stage must be explicit");
    require(sameEnergy(a, b) && encoded(*left.document()) == encoded(*right.document()), "energy determinism");
    auto expected = std::make_unique<Document>(source);
    for (const auto& t : a.territories) {
        require(t.energyBefore == source.territories[t.territory - 1].data.materials[2], "energy before differs");
        expected->territories[t.territory - 1].data.materials[2] = t.energyAfter;
        expected->territories[t.territory - 1].data.knowledge = t.energyPercentAfter;
    }
    require(encoded(*expected) == encoded(*left.document()), "energy changed bytes beyond stock and percentage");
    require(encoded(source) == original && source.options.turn == left.document()->options.turn,
            "energy changed source or turn");
    const auto partial = encoded(*left.document()); const auto reportBefore = a;
    require(!left.consumeEnergy(a, error) && sameEnergy(a, reportBefore), "energy repeated or report damaged");
    require(!left.capture(*expected, error), "energy partial snapshot must not be exported");
    require(encoded(*expected) == partial, "failed energy capture changed destination");
    auto taxReport = sentinelReport(); const auto savedTax = taxReport;
    require(!left.collectTaxes(taxReport, error) && samePlan(taxReport, savedTax), "taxes must not follow isolated energy");
    require(!left.advanceTurn(error) && encoded(*left.document()) == partial, "energy must not complete a turn");
    auto bad = std::make_unique<Document>(source); bad->territories[0].data.owner = 7;
    require(!left.prepare(*bad, error) && left.stage() == rt::Stage::EnergyApplied &&
            encoded(*left.document()) == partial, "failed prepare lost isolated energy state");
    require(left.prepare(source, error) && left.capture(*expected, error) && encoded(*expected) == original,
            "fresh prepare must reset energy stage");
    require(left.collectTaxes(taxReport, error), "fresh tax preparation failed");
    const auto taxed = encoded(*left.document());
    require(!left.consumeEnergy(a, error) && sameEnergy(a, reportBefore) && encoded(*left.document()) == taxed,
            "energy must not skip production and imports after taxes");
}

void labor(const Document& source) {
    const auto original = encoded(source);
    rt::State left, right; save::Error error;
    simulation::LaborBalancePlan a, b;
    require(!left.normalizeLabor(a, error), "empty labor normalization must fail"); diagnostics(error);
    require(left.prepare(source, error) && right.prepare(source, error), "prepare labor normalization");
    const auto* documentBefore = left.document();
    const auto* graphBefore = left.graph().territories.data();
    if (!left.normalizeLabor(a, error) || !right.normalizeLabor(b, error))
        throw std::runtime_error("labor normalization: " + error.message);
    require(error.code == save::ErrorCode::None && left.stage() == rt::Stage::LaborBalanced,
            "labor stage must be explicit and clear error");
    require(a == b && encoded(*left.document()) == encoded(*right.document()), "labor normalization determinism");
    require(left.document() == documentBefore && left.graph().territories.data() == graphBefore,
            "scalar labor commit must not invalidate graph or owned document");
    require(a.buildings.size() == source.buildings.size() && a.territories.size() == source.territories.size(),
            "labor plan must cover every building and territory");
    auto expected = std::make_unique<Document>(source);
    for (size_t i = 0; i < a.buildings.size(); ++i) {
        const auto& effect = a.buildings[i]; const auto& old = source.buildings[i];
        auto& changed = expected->buildings[i];
        require(effect.buildingId == old.id && effect.territory == uint32_t(old.territory) && effect.site == old.site &&
                effect.before.flags == old.flags, "building report identity/order/before flags differ");
        changed.flags = effect.after.flags;
        for (size_t s = 0; s < 5; ++s) {
            require(effect.before.tasks[s] == old.task[s] && effect.before.labor[s] == old.labor[s],
                    "labor report before snapshot differs");
            changed.task[s] = effect.after.tasks[s]; changed.labor[s] = effect.after.labor[s];
        }
    }
    for (size_t i = 0; i < a.territories.size(); ++i) {
        const auto& effect = a.territories[i]; const auto& old = source.territories[i].data;
        auto& changed = expected->territories[i].data;
        require(effect.territory == old.index && effect.moraleBefore == old.morale, "territory report before differs");
        changed.morale = effect.moraleAfter;
        for (size_t m = 0; m < kNumMaterials; ++m) {
            require(effect.materialsBefore[m] == old.materials[m], "labor stock report before differs");
            changed.materials[m] = effect.materialsAfter[m];
        }
    }
    const auto partial = encoded(*left.document()); const auto reportBefore = a;
    require(encoded(*expected) == partial, "labor commit changed bytes outside tasks/labor/locks/morale/stocks");
    require(encoded(source) == original && source.options.turn == left.document()->options.turn,
            "labor normalization changed source or advanced turn");
    require(!left.normalizeLabor(a, error) && a == reportBefore, "labor normalization must not repeat");
    require(!left.capture(*expected, error) && encoded(*expected) == partial,
            "partial load normalization must not export a resumable save");
    simulation::TaxPlan taxReport; simulation::EnergyPlan energyReport;
    require(!left.collectTaxes(taxReport, error) && !left.consumeEnergy(energyReport, error),
            "labor experiment must not silently chain omitted load/turn phases");
    require(!left.advanceTurn(error) && encoded(*left.document()) == partial, "labor normalization must not complete a turn");
    auto bad = std::make_unique<Document>(source); bad->territories[0].data.owner = 7;
    require(!left.prepare(*bad, error) && left.stage() == rt::Stage::LaborBalanced && encoded(*left.document()) == partial,
            "failed prepare must preserve normalized state");
    rt::State moved(std::move(left));
    require(left.stage() == rt::Stage::Empty && !left.document() && moved.stage() == rt::Stage::LaborBalanced &&
            encoded(*moved.document()) == partial, "move must retain normalization stage with its document");
    require(moved.prepare(source, error) && moved.capture(*expected, error) && encoded(*expected) == original,
            "fresh preparation restores archival snapshot, not a hidden normalization");
    require(moved.collectTaxes(taxReport, error), "fresh taxes for labor gating");
    const auto taxed = encoded(*moved.document());
    require(!moved.normalizeLabor(a, error) && a == reportBefore && encoded(*moved.document()) == taxed,
            "labor normalization must not chain after isolated taxes");
    require(moved.prepare(source, error) && moved.consumeEnergy(energyReport, error), "fresh energy for labor gating");
    const auto powered = encoded(*moved.document());
    require(!moved.normalizeLabor(a, error) && a == reportBefore && encoded(*moved.document()) == powered,
            "labor normalization must not chain after isolated energy");
}

void laborGoldenAndFailure() {
    auto d = fixture();
    auto& empty = d->territories[0].data;
    empty.population = 0; empty.morale = 13;
    empty.materials[0] = 12345; empty.materials[1] = 20000;
    empty.materials[2] = -20; empty.materials[10] = 10001;
    d->buildings[0].turnsLeft = 10; d->buildings[0].flags = 0x1f06;
    d->buildings[0].labor[0] = 3; d->buildings[0].labor[1] = 2;
    d->buildings[1].flags = 6; d->raceStats.v[24][1] = 100;
    rt::State state; save::Error error; simulation::LaborBalancePlan report;
    require(state.prepare(*d, error) && state.normalizeLabor(report, error), "labor runtime golden failed");
    const auto& zero = state.document()->territories[0].data;
    require(zero.morale == 100 && zero.population == 0, "empty territory resets morale, not population");
    require(zero.materials[0] == 12345 && zero.materials[1] == 10000 && zero.materials[2] == -20 &&
            zero.materials[10] == 10000, "stock caps exclude money and do not clamp negative stocks");
    const auto* construction = state.building({1});
    require(construction->task[0] == 2 && construction->labor[0] == 0 && construction->flags == 6,
            "construction tasks rebuilt before zero-population labor reduction and unlock");
    require(state.building({2})->task[1] == 20 && state.building({2})->labor[1] == 5,
            "housing receives five of the seven available workers at population900/morale80");
    require(report.territories[1].laborPool == 7 && report.territories[1].unavailableLabor == 2 &&
            report.territories[1].assignedLabor == 5 && report.territories[1].unassignedLabor == 2,
            "labor report distinguishes morale-unavailable and available-but-unassigned workers");
    checkGraph(state);
    auto overloaded = fixture();
    overloaded->territories[0].data.population = 2000;
    overloaded->territories[0].data.morale = 100;
    overloaded->buildings[0].flags = 6;
    overloaded->buildings[0].labor[1] = 6; overloaded->buildings[0].labor[2] = 6;
    require(state.prepare(*overloaded, error) && state.normalizeLabor(report, error) &&
            state.building({1})->labor[3] == -4, "runtime must preserve the original generated signed labor");
    labor(*overloaded);
    auto bad = fixture(); bad->players[1].race = 7;
    require(state.prepare(*bad, error), "out-of-range housing race must pass structural preparation");
    const auto before = encoded(*state.document()); const auto priorReport = report;
    require(!state.normalizeLabor(report, error), "unsafe housing race-table index must fail"); diagnostics(error);
    require(state.stage() == rt::Stage::Prepared && report == priorReport && encoded(*state.document()) == before,
            "failed labor normalization must preserve document, stage and report");
}

void invalidEnergy() {
    auto d = fixture();
    // Structurally valid, but original stock<need branch would divide by zero.
    for (auto& b : d->buildings) b.turnsLeft = 1;
    d->territories[0].data.materials[2] = -1;
    rt::State state; save::Error error;
    require(state.prepare(*d, error), "invalid energy arithmetic fixture must pass structural preparation");
    const auto before = encoded(*state.document());
    simulation::EnergyPlan report; report.shortfalls.push_back({0x33, 5, 3, 42});
    const auto saved = report;
    require(!state.consumeEnergy(report, error), "undefined energy division must fail"); diagnostics(error);
    require(state.stage() == rt::Stage::Prepared && encoded(*state.document()) == before && sameEnergy(report, saved),
            "energy arithmetic failure must be transactional");
}

void energyGolden() {
    auto d = fixture();
    d->buildings[0].type = 4; d->buildings[0].flags = 4; // Cloning Center, 25 energy.
    d->buildings[1].type = 17; d->buildings[1].flags = 4; // Hospital, 2 energy.
    d->territories[0].data.materials[2] = 20;
    d->territories[0].data.knowledge = 12;
    d->territories[1].data.materials[2] = 0;
    rt::State state; save::Error error; simulation::EnergyPlan report;
    require(state.prepare(*d, error) && state.consumeEnergy(report, error), "energy runtime golden failed");
    require(report.territories[0].consumed == 20 && report.territories[0].energyAfter == 0 &&
            report.territories[0].energyPercentAfter == 80 && state.document()->territories[0].data.knowledge == 80,
            "partial supply must produce 80 percent and subtract energy");
    require(report.territories[1].consumed == 0 && report.territories[1].energyPercentAfter == 50 &&
            state.document()->territories[1].data.knowledge == 50, "starved energy must retain the original 50 percent floor");
    require(report.shortfalls.size() == 2 && report.shortfalls[0].type == 0x33 &&
            report.shortfalls[0].recipient == 0 && report.shortfalls[0].shortage == 20 &&
            report.shortfalls[1].recipient == 1 && report.shortfalls[1].shortage == 50, "energy semantic events differ");
    require(state.document()->events.size() == d->events.size(), "semantic energy events must not invent saved log text");
    energy(*d);
}

std::vector<std::string> scenarioNames(const fs::path& indexPath) {
    // Enumerate only index names; each scenario is read/validated through save_files.
    // Keeping this helper local avoids a graphics/formats library dependency.
    const auto size = fs::file_size(indexPath);
    require(size >= 4 && size <= save::kMaxFileBytes, "corpus index size is invalid");
    std::ifstream input(indexPath, std::ios::binary);
    uint8_t rawCount[4]{};
    require(bool(input.read(reinterpret_cast<char*>(rawCount), 4)), "cannot read corpus index count");
    const uint32_t count = uint32_t(rawCount[0]) | uint32_t(rawCount[1]) << 8 |
                           uint32_t(rawCount[2]) << 16 | uint32_t(rawCount[3]) << 24;
    require(count <= (size - 4) / 12, "corpus index is truncated");
    std::vector<std::string> names;
    for (uint32_t i = 0; i < count; ++i) {
        char entry[12]{};
        require(bool(input.read(entry, 12)), "cannot read corpus index entry");
        names.emplace_back(entry, std::find(entry, entry + 8, '\0'));
    }
    return names;
}

void optionalCorpus(const fs::path& directory) {
    if (directory.empty() || !fs::is_regular_file(directory / "TUTORIAL.SAV")) {
        std::cout << "runtime: optional original corpus unavailable; synthetic checks still ran\n";
        return;
    }
    size_t count = 0;
    for (const auto* relative : {"TUTORIAL.SAV", "Saves/AUTOSAVE.SAV", "Campaign/AUTOSAVE.CPN", "Campaign/ChCht001.CPN"}) {
        const auto path = directory / relative;
        if (!fs::is_regular_file(path)) continue;
        auto d = std::make_unique<Document>(); save::Error error;
        if (!save::readDocument(path, *d, error)) throw std::runtime_error(std::string(relative) + ": " + error.message);
        taxes(*d, std::string(relative) == "TUTORIAL.SAV"); energy(*d); labor(*d); ++count;
    }
    if (fs::is_regular_file(directory / "LEVELS.HDX") && fs::is_regular_file(directory / "LEVELS.HDD")) {
        for (const auto& entry : scenarioNames(directory / "LEVELS.HDX")) {
            auto d = std::make_unique<Document>(); save::Error error;
            if (!save::readScenario(directory / "LEVELS", entry, *d, error))
                throw std::runtime_error(entry + ": " + error.message);
            try { taxes(*d); energy(*d); labor(*d); } catch (const std::exception& e) {
                throw std::runtime_error(entry + ": " + e.what());
            }
            ++count;
        }
    }
    std::cout << "runtime corpus: " << count << " exact captures and deterministic isolated tax/energy/labor experiments\n";
}
} // namespace

int main(int argc, char** argv) {
    try {
        // Nonzero sentinels expose accidental ResetVariables/gs/gg activation.
        gs.options.turn = 2468; gs.players[0].credits = 97531;
        gg.netGame = 1; gg.rng2Seed = 0xaabbccdd;
        rtl::srand(0x12345678); (void)rtl::lrand();
        const uint32_t lo = rtl::seed(), hi = rtl::seedHi();
        const auto* gsBytes = reinterpret_cast<const uint8_t*>(&gs);
        const auto* ggBytes = reinterpret_cast<const uint8_t*>(&gg);
        const std::vector<uint8_t> gsBefore(gsBytes, gsBytes + sizeof(gs));
        const std::vector<uint8_t> ggBefore(ggBytes, ggBytes + sizeof(gg));
        prepareAndTransactions();
        auto d = fixture(); taxes(*d); energy(*d); labor(*d); invalidEnergy(); energyGolden(); laborGoldenAndFailure();
        optionalCorpus(argc > 1 ? fs::path(argv[1]) : fs::path{});
        require(std::memcmp(gsBefore.data(), &gs, sizeof(gs)) == 0 &&
                std::memcmp(ggBefore.data(), &gg, sizeof(gg)) == 0, "runtime changed legacy globals");
        require(rtl::seed() == lo && rtl::seedHi() == hi, "runtime consumed or reseeded Borland RNG");
        std::cout << "runtime: graph, transactionality, capture, fiscal gating and global/RNG isolation passed\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "runtime: " << error.what() << '\n';
        return 1;
    }
}
