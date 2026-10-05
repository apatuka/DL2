// State publication contracts for the assembly-derived crossing leaf.
// These fixtures do not claim an observed execution of DEADLOCK.EXE.
#include "game/runtime_state.h"
#include "game/data_tables.h"
#include <cstring>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

namespace {
using namespace dl2;
using namespace dl2::simulation;
void require(bool value, const char* message) { if (!value) throw std::runtime_error(message); }
void ok(bool value, const save::Error& error) { if (!value) throw std::runtime_error(error.message); }
std::unique_ptr<save::Document> fixture() {
    auto d = std::make_unique<save::Document>();
    std::memcpy(d->header.text, save::kHeaderText, sizeof(save::kHeaderText));
    d->header.version = kSaveVersion; d->world.width = 2; d->world.height = 1;
    d->world.numTerritories = 2; d->tiles.resize(2); d->territories.resize(2);
    d->options.numPlayers = 2; d->options.localPlayer = 0; d->options.turn = 17;
    d->options.allowAlliances = 1;
    for (size_t p = 0; p < kMaxPlayers; ++p) {
        d->players[p].index = uint8_t(p); d->players[p].type = p ? 3 : 1;
        d->players[p].race = 0; d->ministerJobs[p].resize(1);
        for (auto& job : d->jobs[p]) job.owner = int16_t(p);
    }
    for (size_t n = 0; n < 2; ++n) {
        auto& tile = d->tiles[n]; tile.x = uint8_t(n); tile.territory = int16_t(n + 1);
        auto& t = d->territories[n].data;
        t.index = uint16_t(n + 1); t.owner = int8_t(n); t.terrain = 1;
        t.numTiles = 1; t.tiles[0].raw = uint32_t(n); t.secondTile = 0;
        t.adjacency[0] = uint16_t(1u << (2 - n));
        std::memcpy(t.name, n ? "East" : "West", 4);
        Army a{}; a.id = uint16_t(101 + n); a.type = 1;
        a.unitClass = data::kUnitTypes[1].unitClass; a.owner = int8_t(1 - n);
        a.health = 100; a.strength = 3; a.territory.raw = uint32_t(2 - n);
        a.dest.raw = a.origin.raw = uint32_t(n + 1);
        t.foreignArmies.raw = a.id; d->armies.push_back(a);
    }
    return d;
}
MovementCrossingsContext context() {
    MovementCrossingsContext c; SessionRng rng; save::Error error;
    ok(rng.initialize(7, error), error); c.ai.rng = rng.snapshot();
    c.log.emplace(); c.log->rngAfterEvents = c.ai.rng;
    c.cities[0] = 4; c.cities[1] = 9;
    c.movement.paths.sentinelFlags = 0x2040;
    c.movement.paths.recursionDepth = 2;
    c.movement.paths.maximumRecursionDepth = 2;
    c.campaign.emplace(); c.campaign->campaignFlags = 0x20;
    return c;
}
std::vector<uint8_t> bytes(const save::Document& d) {
    std::vector<uint8_t> result; save::Error error; ok(save::encode(d, result, error), error);
    for (const auto& t : d.territories) {
        const auto* raw = reinterpret_cast<const uint8_t*>(&t.data);
        result.insert(result.end(), raw + kTerritorySavedBytes, raw + sizeof(Territory));
    }
    return result;
}
void publicationAndContinuation() {
    auto d = fixture(); auto expected = std::make_unique<save::Document>();
    auto c = context(); const auto initial = c; save::Error error;
    AiSession bindings; ok(bindings.initializeAfterLoad(*d, error), error);
    MovementCrossingsReport leaf;
    ok(resolveMovementCrossings(*d, bindings, c, *expected, leaf, error), error);
    runtime::State state; ok(state.prepare(*d, error), error);
    const auto west = state.territoryByIndex(1), east = state.territoryByIndex(2);
    const auto local = state.armyById(102), other = state.armyById(101);
    MovementCrossingsReport report;
    ok(state.resolveMovementCrossings(c, report, error), error);
    require(report == leaf && bytes(*state.document()) == bytes(*expected) && c == initial,
            "runtime crossing result differs from the owned leaf or mutates its caller");
    require(state.stage() == runtime::Stage::EntitiesEdited && state.document()->options.turn == 17 &&
            state.armyById(102) == local && state.armyById(101) == other &&
            state.territoryByIndex(1) == west && state.territoryByIndex(2) == east &&
            state.armyLinks(local)->current == west && state.armyLinks(local)->turnStart == west &&
            state.armyLinks(local)->routeOrigin == west && state.armyLinks(other)->current == west,
            "crossing publication loses stable handles, relink graph or turn boundary");
    require(state.loadedEvents() && state.loadedEvents()->entries.size() == 1 &&
            state.loadedEvents()->entries[0].type == 152 && state.document()->events.empty() &&
            *state.loadedEvents() == *report.contextAfter.log && state.aiSession() &&
            *state.aiReactionContext() == report.contextAfter.ai && state.sessionRng() == report.contextAfter.ai.rng &&
            *state.eventCities() == report.contextAfter.cities &&
            *state.movementContext() == report.contextAfter.movement &&
            *state.buildingRemovalContext() == *report.contextAfter.campaign,
            "crossing completion did not publish one coherent transient continuation");
    const auto completed = bytes(*state.document()); const auto savedReport = report;
    for (int variant = 0; variant < 8; ++variant) {
        auto stale = report.contextAfter;
        switch (variant) {
        case 0: stale.ai.rng.secondary ^= 1; break;
        case 1: stale.log.reset(); break;
        case 2: ++stale.cities[0]; break;
        case 3: stale.campaign.reset(); break;
        case 4: stale.movement.paths.sentinelFlags ^= 4; break;
        case 5: ++stale.movement.paths.recursionDepth; break;
        case 6: ++stale.movement.paths.maximumRecursionDepth; break;
        case 7: stale.log->entries[0].param ^= 1; break;
        }
        require(!state.resolveMovementCrossings(stale, report, error) && report == savedReport &&
                bytes(*state.document()) == completed && state.armyById(102) == local &&
                state.sessionRng() == savedReport.contextAfter.ai.rng,
                "stale crossing input rewinds a continuation or changes a failed output");
    }
    runtime::State moved = std::move(state);
    require(!state.document() && moved.army(local) && moved.loadedEvents() && moved.movementContext(),
            "moving runtime State dropped crossing context or stable handles");
    // Alias the input context to the output report. With the local army back
    // home there is no crossing: retaining the previous log must not replay it.
    ok(moved.resolveMovementCrossings(report.contextAfter, report, error), error);
    require(report.crossings.empty() && report.draws.empty() && bytes(*moved.document()) == completed &&
            *moved.loadedEvents() == *savedReport.contextAfter.log && moved.armyById(102) == local,
            "continued crossing pass repeated a past event or broke context/report aliasing");
    AiPactReconciliationContext pacts;
    pacts.ai = report.contextAfter.ai; pacts.log = report.contextAfter.log; pacts.cities = report.contextAfter.cities;
    AiPactReconciliationReport pactReport;
    ok(moved.beginAiPactReconciliation(pacts, report.contextAfter.campaign, pactReport, error), error);
    require(!moved.pendingAiOffer() && *moved.loadedEvents() == *savedReport.contextAfter.log &&
            *moved.movementContext() == savedReport.contextAfter.movement && moved.armyById(102) == local,
            "another consumer cannot continue the joint crossing state");
    const auto beforeCapture = bytes(*d);
    require(!moved.capture(*d, error) && bytes(*d) == beforeCapture && !moved.advanceTurn(error),
            "isolated crossings enabled partial save export or advanceTurn");
}
void lateFailureAndTerminalStages() {
    auto d = fixture(); runtime::State state; save::Error error; MovementCrossingsReport report;
    ok(state.prepare(*d, error), error);
    const auto baseline = bytes(*state.document()); const auto pointer = state.document();
    const auto handle = state.armyById(102); auto incomplete = context(); incomplete.log.reset();
    const auto before = report;
    require(!state.resolveMovementCrossings(incomplete, report, error) && report == before &&
            state.document() == pointer && bytes(*state.document()) == baseline &&
            state.stage() == runtime::Stage::Prepared && !state.sessionRng().initialized &&
            !state.aiSession() && !state.aiReactionContext() && !state.loadedEvents() &&
            !state.movementContext() && !state.eventCities() && !state.buildingRemovalContext() && state.army(handle),
            "missing local log after private movement partially committed the State");
    ok(state.resolveMovementCrossings(context(), report, error), error);
    require(state.armyLinks(handle)->current == state.territoryByIndex(1), "retry after late failure did not run");
    runtime::State taxed; ok(taxed.prepare(*d, error), error); TaxPlan tax;
    ok(taxed.collectTaxes(tax, error), error); const auto taxedBytes = bytes(*taxed.document());
    const auto saved = report;
    require(!taxed.resolveMovementCrossings(context(), report, error) && report == saved &&
            taxed.stage() == runtime::Stage::TaxesApplied && bytes(*taxed.document()) == taxedBytes,
            "crossings bypassed a terminal experiment stage");
    runtime::State empty;
    require(!empty.resolveMovementCrossings(context(), report, error) && report == saved && !empty.document(),
            "crossings accepted an unprepared runtime");
}
} // namespace
int main() {
    try { publicationAndContinuation(); lateFailureAndTerminalStages(); }
    catch (const std::exception& e) { std::cerr << e.what() << '\n'; return 1; }
    std::cout << "movement crossing runtime contracts passed\n"; return 0;
}
