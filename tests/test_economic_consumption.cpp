#include "game/economic_consumption.h"
#include "game/army_pool.h"
#include "game/data_tables.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include <algorithm>
#include <cstring>
#include <iostream>
#include <memory>
#include <stdexcept>

namespace {
using namespace dl2;
using namespace dl2::simulation;
void check(bool yes, const char* text) { if (!yes) throw std::runtime_error(text); }
void ok(bool yes, const save::Error& error) { if (!yes) throw std::runtime_error(error.message); }
std::unique_ptr<save::Document> fixture(int n = 1) {
    auto d = std::make_unique<save::Document>();
    std::memcpy(d->header.text, save::kHeaderText, sizeof(save::kHeaderText));
    d->header.version = kSaveVersion; d->options.numPlayers = 2; d->options.localPlayer = 0; d->options.turn = 29;
    d->world.width = uint8_t(n); d->world.height = 1; d->world.numTerritories = uint16_t(n);
    d->territories.resize(size_t(n)); d->tiles.resize(size_t(n));
    for (size_t p = 0; p < 7; ++p) {
        d->players[p].index = uint8_t(p); d->players[p].race = int8_t(p); d->players[p].credits = 100;
        d->players[p].type = p ? 3 : 1; d->raceStats.v[61][p] = 100; d->ministerJobs[p].resize(1);
        d->ministerJobs[p][0].type = 1;
    }
    for (int i = 0; i < n; ++i) {
        auto& t = d->territories[size_t(i)].data;
        t.index = uint16_t(i + 1); t.owner = 0; t.terrain = 1; t.population = 1000; t.numTiles = 1;
        t.tiles[0].raw = uint32_t(i); t.materials[1] = 12; t.production[1] = 10;
        std::memcpy(t.name, "Alpha", 6); t.centerTile = 0;
        d->tiles[size_t(i)].x = uint8_t(i); d->tiles[size_t(i)].territory = int16_t(i + 1);
        d->tiles[size_t(i)].terrain = 1;
    }
    return d;
}
ConstructionOrderContext context() {
    ConstructionOrderContext c; SessionRng rng; save::Error error; ok(rng.initialize(42, error), error);
    c.events.rngBeforeEvents = c.ai.rng = c.log.rngAfterEvents = rng.snapshot(); c.payment.selectedTerritory = 1; return c;
}
std::vector<uint8_t> bytes(const save::Document& d) {
    save::Error e; std::vector<uint8_t> out; ok(save::encode(d, out, e), e);
    for (const auto& t : d.territories) {
        const auto* b = reinterpret_cast<const uint8_t*>(&t.data);
        out.insert(out.end(), b + kTerritorySavedBytes, b + sizeof(Territory));
    }
    return out;
}
void addArmy(save::Document& d, uint16_t id, int type = 1, uint8_t mission = 0) {
    Army a{}; a.id = id; a.type = uint8_t(type); a.unitClass = data::kUnitTypes[type].unitClass;
    a.owner = 0; a.unk_25 = mission; a.territory.raw = a.dest.raw = a.origin.raw = 1;
    a.next.raw = d.territories[0].data.armies.raw;
    if (a.next.raw) for (auto& old : d.armies) if (old.id == a.next.raw) old.prev.raw = id;
    d.territories[0].data.armies.raw = id; d.armies.push_back(a);
}
void civilianAndPhysicalOrder() {
    auto d = fixture(); addArmy(*d, 50); addArmy(*d, 10); addArmy(*d, 30);
    auto& t = d->territories[0].data; t.unk_28[1] = 4;
    const auto before = bytes(*d); auto out = fixture(); FoodConsumptionReport r; save::Error e; const auto c = context();
    ok(consumeFood(*d, c, *out, r, e), e);
    check(bytes(*d) == before && e.code == save::ErrorCode::None, "food preserves source, clears error");
    check(r.territories[0].consumed == 10 && r.territories[0].stockAfter == 2 && r.territories[0].reserveAfter == 0 && r.territories[0].hungerAfter == 3,
          "civilians consume first, decrement reserve and reduce hunger");
    check(r.armies.size() == 3 && r.armies[0].army == 50 && r.armies[1].army == 10 && r.armies[2].army == 30,
          "food must not sort physical units by ID or linked list");
    check(r.armies[0].source == UnitFoodSource::LocalStock && r.armies[1].source == UnitFoodSource::LocalStock &&
          r.armies[2].source == UnitFoodSource::Starved, "stock reaches first two physical units only");
    check((out->players[0].foodFlags & 2) && !(out->players[0].foodFlags & 4) && r.events.back().type == 2,
          "first army starvation emits2 and sets bit2, not repeated flag4");
    check(out->options.turn == 29 && out->armies.size() == 3, "food itself does not disband or advance turn");
    auto alias = std::make_unique<save::Document>(*d); FoodConsumptionReport same;
    ok(consumeFood(*alias, c, *alias, same, e), e);
    check(bytes(*alias) == bytes(*out) && same == r, "food source/destination alias is exact");
    auto next = c; next.log = r.logAfter; next.ai = r.aiAfter; next.events.rngBeforeEvents = r.rngAfter; next.payment.collection = r.collectionAfter;
    ok(consumeFood(*out, next, *out, same, e), e);
    check((out->players[0].foodFlags & 6) == 6, "second army starvation requests later upkeep disband");
    for (const auto& ev : same.events) check(ev.type != 2, "repeat starvation suppresses first-warning2");
}
void reusedPhysicalOrder() {
    auto d = fixture(); addArmy(*d,50); addArmy(*d,10); addArmy(*d,30);
    save::Error e; ok(ensureArmyPool(*d,e),e);
    check(armyPoolSlot(*d,50) == 1 && armyPoolSlot(*d,10) == 2 && armyPoolSlot(*d,30) == 3,
          "initial file order must occupy physical cells1..3");
    ok(retireArmyPoolSlot(*d,50,e),e);
    // Fixture removal preserves the reciprocal territory list30->10. Pool
    // retirement is deliberately before dense erasure, like DeleteArmy.
    d->armies[1].next.raw = 0; d->armies.erase(d->armies.begin());
    addArmy(*d,900); ok(allocateArmyPoolSlot(*d,900,e),e);
    check(armyPoolSlot(*d,900) == 1 && d->armies[0].id == 10 && d->armies[2].id == 900,
          "reuse fixture must separate physical order from dense append order");
    // Ten food for civilians, then ONE unit ration. The new unit in cell1
    // eats first, while IDs10/30 in cells2/3 starve. No sorting/list traversal.
    d->territories[0].data.materials[1] = 11;
    const auto c = context(); const auto before = bytes(*d); const auto poolBefore = d->armyPool;
    auto out = fixture(); FoodConsumptionReport r;
    ok(consumeFood(*d,c,*out,r,e),e);
    check(bytes(*d) == before && d->armyPool == poolBefore && out->armyPool == poolBefore,
          "food modified source or allocator/binding metadata");
    check(r.armies.size() == 3 && r.armies[0].army == 900 && r.armies[1].army == 10 && r.armies[2].army == 30 &&
          r.armies[0].source == UnitFoodSource::LocalStock && r.armies[1].source == UnitFoodSource::Starved &&
          r.armies[2].source == UnitFoodSource::Starved && out->territories[0].data.materials[1] == 0,
          "scarce food did not prioritize the reused low physical cell");
    check(out->armies[0].id == 10 && out->armies[1].id == 30 && out->armies[2].id == 900,
          "physical traversal must not reorder dense records");
    // Independent archival control has the SAME physical order in its dense
    // load records. Its complete report proves no event/logistics/RNG drift.
    auto control = std::make_unique<save::Document>(*d); control->armyPool.reset();
    std::rotate(control->armies.begin(),control->armies.end()-1,control->armies.end());
    auto expected = fixture(); FoodConsumptionReport reference;
    ok(consumeFood(*control,c,*expected,reference,e),e);
    check(r == reference && out->players[0].foodFlags == expected->players[0].foodFlags &&
          out->options.turn == 29 && out->armies.size() == 3,
          "pool traversal changed effects, RNG, flags or army lifetimes beyond ordering");
    auto alias = std::make_unique<save::Document>(*d); FoodConsumptionReport aliased;
    ok(consumeFood(*alias,c,*alias,aliased,e),e);
    check(aliased == r && bytes(*alias) == bytes(*out) && alias->armyPool == poolBefore,
          "physical consumption alias lost allocator metadata or effects");
    auto bad = std::make_unique<save::Document>(*d); bad->armyPool->liveIds[1] = 55555;
    const auto invalidPool = bad->armyPool; const auto outputBefore = bytes(*out); const auto reportBefore = r;
    check(!consumeFood(*bad,c,*out,r,e) && e.code == save::ErrorCode::InvalidState &&
          bad->armyPool == invalidPool && bytes(*out) == outputBefore && out->armyPool == poolBefore && r == reportBefore,
          "invalid physical occupant did not reject without changing output/context/allocator");
}
void hungerAndNarrowing() {
    auto d = fixture(); auto out = fixture(); auto c = context(); save::Error e; FoodConsumptionReport r;
    d->territories[0].data.materials[1] = 3;
    ok(consumeFood(*d, c, *out, r, e), e);
    check(r.territories[0].hungerAfter == 1 && r.events.size() == 1 && r.events[0].type == 50 && r.events[0].local,
          "first civilian shortfall produces real50 event");
    check(r.logAfter.entries.size() == 1 && r.logAfter.entries[0].player == 1, "LogEventEx payload identifies territory");
    d->territories[0].data.unk_28[1] = 7;
    ok(consumeFood(*d, c, *out, r, e), e);
    check(r.territories[0].hungerAfter == 7 && r.events.empty(), "hunger clamps at7, no repeated50");
    d->territories[0].data.unk_28[1] = 255;
    ok(consumeFood(*d, c, *out, r, e), e);
    check(r.territories[0].hungerAfter == 0, "hunger byte is read signed");
    d->territories[0].data.population = 32767; d->raceStats.v[61][0] = 32767;
    d->territories[0].data.materials[1] = 200000;
    ok(consumeFood(*d, c, *out, r, e), e);
    check(r.territories[0].need == 107367 && r.territories[0].consumed == -23705 && r.territories[0].stockAfter == 223705,
          "consumed amount narrows before subtraction, not before shortage comparison");
}
void freeSupplierAndMission() {
    auto d = fixture(2); d->territories[0].data.population = 0; d->territories[0].data.materials[1] = 0;
    d->territories[1].data.population = 0; d->territories[1].data.materials[1] = 4;
    d->territories[0].data.adjacency[0] = 4; d->territories[1].data.adjacency[0] = 2;
    d->territories[0].data.production[1] = d->territories[1].data.production[1] = 0;
    addArmy(*d, 51, 1, 1);
    FoodConsumptionReport r; auto c = context(); save::Error e; auto out = fixture();
    ok(consumeFood(*d, c, *out, r, e), e);
    check(r.armies[0].source == UnitFoodSource::FreeSupplier && r.armies[0].supplier == 2 && out->territories[1].data.materials[1] == 3,
          "mobile mission fetches one food directly from reachable donor");
    check(out->players[0].credits == 100 && r.collectionAfter.transfers.empty() && r.collectionAfter.suppliers[1].territory == 0,
          "free food does not charge freight/log transfer and clears supplier ID");
    d->armies[0].unk_25 = 0;
    ok(consumeFood(*d, c, *out, r, e), e);
    check(r.armies[0].source == UnitFoodSource::Collected && !r.collectionAfter.transfers.empty(),
          "unitClass1 alone is not mobileMission: mission0 invokes collector");
}
void energyAndAtomicity() {
    auto d = fixture(); Building b{}; b.id = 200; b.type = 20; b.territory = 1; b.flags = 4;
    d->buildings.push_back(b); d->territories[0].data.sites[0].building.raw = 200;
    d->territories[0].data.materials[2] = 39;
    auto out = fixture(); auto c = context(); EnergyConsumptionReport r; save::Error e;
    ok(consumeEconomicEnergy(*d, c, *out, r, e), e);
    check(out->territories[0].data.materials[2] == 0 && out->territories[0].data.knowledge == 97 &&
          r.events.size() == 1 && r.events[0].type == 51 && r.logAfter.entries[0].player == 1,
          "energy applies exact97percent and real shortage event51");
    auto bad = std::make_unique<save::Document>(*d); std::memset(bad->territories[0].data.name, 'X', 25);
    const auto destination = bytes(*out); const auto log = r.logAfter; const auto rng = r.rngAfter;
    check(!consumeEconomicEnergy(*bad, c, *out, r, e) && bytes(*out) == destination && r.logAfter == log && r.rngAfter == rng,
          "late energy formatting failure rolls back document, report and RNG");
    FoodConsumptionReport food; bad->territories[0].data.materials[1] = 0;
    const auto unchanged = food;
    check(!consumeFood(*bad, c, *out, food, e) && bytes(*out) == destination && food == unchanged, "late food event error is atomic");
}
void aiAndGlobalIsolation() {
    auto d = fixture(); d->territories[0].data.owner = 1; d->territories[0].data.materials[1] = 0;
    auto c = context(); AiSession ai; save::Error e; ok(ai.initializeAfterLoad(*d, e), e); c.aiSession = &ai;
    FoodConsumptionReport r; auto out = fixture();
    gs.options.turn = 12345; gg.rng2Seed = 1234; rtl::srand(54321); const int expected = rtl::rand(); rtl::srand(54321);
    ok(consumeFood(*d, c, *out, r, e), e);
    check(r.events.size() == 1 && r.events[0].aiDispatched && !r.events[0].aiReport.handled && r.logAfter.entries.empty(),
          "nonlocal50 invokes actual owned AI default, not a fake local event");
    check(gs.options.turn == 12345 && gg.rng2Seed == 1234 && rtl::rand() == expected, "food isolated from legacy globals/RNG");
}
}
int main() {
    try { civilianAndPhysicalOrder(); reusedPhysicalOrder(); hungerAndNarrowing(); freeSupplierAndMission(); energyAndAtomicity(); aiAndGlobalIsolation();
        std::cout << "economic_consumption: PASS\n"; return 0;
    } catch (const std::exception& e) { std::cerr << e.what() << '\n'; return 1; }
}
