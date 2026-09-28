// Pruebas independientes de SDL; los checks siguen activos en Release/NDEBUG.
#include "game/economy.h"
#include "game/gameflow.h"
#include "game/hooks.h"
#include "game/queue_pool.h"
#include "game/rtl_compat.h"

#include <array>
#include <cstdio>
#include <cstring>
#include <limits>
#include <stdexcept>

namespace {
using namespace dl2;

void require(bool condition, const char* message) {
    if (!condition) throw std::runtime_error(message);
}

std::array<uint8_t, kQueueRecordSaved> record(uint8_t unit, uint16_t count) {
    QueueRecord node{};
    node.unitType = unit;
    node.unk_01 = 0x7b;
    node.count = count;
    for (int i = 0; i < 11; ++i) node.data[i] = i * 17 - 3;
    std::array<uint8_t, kQueueRecordSaved> bytes{};
    std::memcpy(bytes.data(), &node, bytes.size());
    return bytes;
}

void testQueueLifetime() {
    QueuePoolReset();
    const auto firstHead = QueueAlloc();
    QueueHead* const headAddress = ptr(firstHead);
    const auto bytes = record(7, 12);
    QueueAppend(headAddress, bytes.data());
    require(headAddress->cursor.raw == 0, "append must leave cursor unchanged");
    const auto firstRecord = headAddress->first;
    QueueRecord* const recordAddress = ptr(firstRecord);
    for (int i = 0; i < 2048; ++i) {
        const auto other = QueueAlloc();
        QueueAppend(ptr(other), bytes.data());
    }
    require(ptr(firstHead) == headAddress, "growing head pool invalidated native pointer");
    require(ptr(firstRecord) == recordAddress, "growing record pool invalidated native pointer");
    require(ref(headAddress).raw == firstHead.raw, "head round-trip after pool growth");
    require(ref(recordAddress).raw == firstRecord.raw, "record round-trip after pool growth");
    QueueAppend(headAddress, bytes.data());
    require(QueueCount(headAddress) == 2, "append after pool growth");
    require(recordAddress->next.raw != 0, "original node must remain linked after growth");
    require(QueueFirst(headAddress), "non-empty queue should have first item");
    QueueFree(firstHead, 0);
    require(ptr(firstHead) == headAddress, "free nodes must retain head allocation");
    require(!ptr(firstRecord), "freed record handle should resolve to null before reuse");
    require(QueueCount(headAddress) == 0 && !QueueFirst(headAddress), "free nodes resets list");
    require(headAddress->cursor.raw == 0, "free nodes clears dangling cursor");
    QueueAppend(headAddress, bytes.data());
    require(headAddress->first.raw == firstRecord.raw, "record pool should reuse vacant slots");
    QueueFree(firstHead, 1);
    require(!ptr(firstHead), "freed head handle should resolve to null before reuse");
    QueueFree(firstHead, 1); // liberar de nuevo no afecta otra cabecera
    const auto reused = QueueAlloc();
    require(reused.raw == firstHead.raw, "head pool should reuse vacant slots");
    require(QueueCount(ptr(reused)) == 0 && ptr(reused)->cursor.raw == 0, "reused head must be empty");
    require(!ptr(Ptr32<QueueHead>{std::numeric_limits<uint32_t>::max()}), "invalid head handle");
    require(!ptr(Ptr32<QueueRecord>{std::numeric_limits<uint32_t>::max()}), "invalid record handle");
    QueueHead foreign{};
    require(!ref(&foreign).raw, "unowned head must not become pool handle");
    QueuePoolReset();
    require(!ptr(reused), "reset must clear all head allocations");
    require(!ptr(firstRecord), "reset must clear all record allocations");
}

void testQueueEditing() {
    QueuePoolReset();
    const auto handle = QueueAlloc();
    QueueHead* q = ptr(handle);
    auto first = record(1, 10), third = record(3, 30), second = record(2, 20);
    int32_t data[11];
    for (int& value : data) value = 77;
    QueueCurData(q, data);
    require(data[0] == 77 && data[10] == 77, "null cursor must leave data output alone");
    require(!QueueNext(q) && !QueueCurCount(q) && !QueueCurUnitType(q), "empty queue accessors");
    QueueAppend(q, first.data());
    QueueAppend(q, third.data());
    require(QueueFirst(q) && QueueNext(q), "cursor moves to second node");
    econ::UnitList_Insert(q, second.data());
    require(QueueCount(q) == 3 && QueueCurUnitType(q) == 2, "insert before cursor selects inserted node");
    require(QueueCurCount(q) == 20, "insert preserves count");
    QueueCurData(q, data);
    require(data[0] == -3 && data[10] == 167, "insert preserves all eleven material values");
    require(QueueNext(q) && QueueCurUnitType(q) == 3, "insert preserves successor");
    econ::UnitList_Delete(q);
    require(QueueCount(q) == 2 && QueueCurUnitType(q) == 2, "delete middle/tail selects predecessor");
    std::array<uint8_t, kQueueRecordSaved> popped{};
    require(econ::QueuePopFront(q, popped.data()) == 1 && popped == first, "pop preserves record payload");
    require(QueueCurUnitType(q) == 2, "pop preserves cursor when cursor is not first");
    econ::QueueSetCurUnitType(q, 9);
    econ::QueueSetCurCount(q, 65535);
    for (int& value : data) value = -999;
    econ::QueueSetCurData(q, data);
    require(QueueCurUnitType(q) == 9 && QueueCurCount(q) == 65535, "cursor setters");
    std::memset(data, 0, sizeof(data));
    QueueCurData(q, data);
    require(data[0] == -999 && data[10] == -999, "cursor material setter");
    require(econ::QueuePopFront(q, popped.data()) == 1, "pop final node");
    require(q->first.raw == 0 && q->cursor.raw == 0, "pop final cursor clears list");
    require(econ::QueuePopFront(q, popped.data()) == 0, "pop empty queue");
    econ::UnitList_Insert(q, first.data());
    econ::UnitList_Insert(q, second.data());
    require(QueueCount(q) == 2 && QueueCurUnitType(q) == 2, "insert empty/front");
    econ::UnitList_Delete(q);
    require(QueueCurUnitType(q) == 1, "delete first moves cursor to next");
    require(!QueueNext(q), "move cursor beyond end");
    econ::UnitList_Insert(q, third.data());
    require(QueueCurUnitType(q) == 3 && QueueCount(q) == 2, "null cursor inserts at front");
    QueuePoolReset();
}

int broadcastCount = 0;
uint32_t broadcastSeed = 0;
void broadcast(uint32_t seed) { ++broadcastCount; broadcastSeed = seed; }

void testRandom() {
    // Vectores de las recurrencias documentadas en los tres decompilados RTL/LCG.
    constexpr int expected2[] = {16838, 5758, 10113, 17515, 31051, 5627, 23010, 7419};
    constexpr int expectedRand[] = {346, 130, 10982, 1090, 11656, 7117, 17595, 6415};
    constexpr uint32_t expectedLong[] = {346, 13854878, 1621890440, 816282396,
                                       1778554774, 821126358, 1407482132, 991758756};
    srand2(1);
    for (int value : expected2) require(rand2() == value, "rand2 golden sequence");
    require(gg.rng2Seed == 2633739833u, "rand2 wraps at 32 bits");
    rtl::srand(1);
    for (int value : expectedRand) require(rtl::rand() == value, "Borland rand golden sequence");
    rtl::srand(1);
    for (uint32_t value : expectedLong) require(rtl::lrand() == value, "Borland lrand golden sequence");
    require(rtl::seed() == 1558657561u && rtl::seedHi() == 991758756u, "lrand complete state");
    rtl::srand(1);
    require(RandRangeTagged(0, "test") == 0 && rtl::seed() == 1, "zero range must not consume RNG");
    require(RandRangeTagged(-7, "test") == 3, "tagged range uses signed remainder");
    gg.netGame = 0;
    SyncSetRandomSeed(42);
    require(rtl::seed() == 42 && rtl::seedHi() == 0 && gg.rng2Seed == 42, "local seed updates both RNGs");
    gg.netGame = 1;
    flow::cb.broadcastRandomSeed = broadcast;
    SyncSetRandomSeed(12345);
    require(broadcastCount == 1 && broadcastSeed == 12345, "network seed dispatches callback");
    require(rtl::seed() == 42 && gg.rng2Seed == 42, "network sender waits for synchronized seed");
    gg.netGame = 0;
    flow::cb = {};
}

void testIdsAndTraining() {
    resetGameState();
    gs.options.nextGlobalId = 65534;
    require(econ::NextGlobalId() == 65535 && econ::NextGlobalId() == 0, "global ID truncates to u16");
    gs.options.nextGlobalId = std::numeric_limits<int32_t>::max();
    require(econ::NextGlobalId() == 0 && gs.options.nextGlobalId == std::numeric_limits<int32_t>::min(),
            "global ID counter wraps without signed overflow");
    gs.buildings[kMaxBuildings - 1].id = 8765;
    gs.armies[kMaxArmies - 1].id = 9876;
    require(econ::FindBuildingByGlobalID(8765) == &gs.buildings[kMaxBuildings - 1], "building lookup scans final slot");
    require(econ::FindArmyByGlobalID(9876) == &gs.armies[kMaxArmies - 1], "army lookup scans final slot");
    require(!econ::FindBuildingByGlobalID(60000) && !econ::FindArmyByGlobalID(60000), "missing ID returns null");
    require(econ::ExperienceLevel(99) == 0 && econ::ExperienceLevel(100) == 1 &&
            econ::ExperienceLevel(400) == 1 && econ::ExperienceLevel(401) == 2, "experience thresholds");
    Army militia{};
    militia.type = 0x18;
    int bonus = 0;
    require(econ::MilitiaTrainingBonus(&militia, &bonus) == 5, "rookie militia bonus");
    militia.experience = 100;
    require(econ::MilitiaTrainingBonus(&militia, &bonus) == 10, "trained militia bonus");
    militia.experience = 401;
    require(econ::MilitiaTrainingBonus(&militia, &bonus) == 10 && bonus == 25, "training bonus caps at 25");
    require(econ::MilitiaTrainingBonus(&militia, &bonus) == 0, "training cap stays saturated");
    militia.type = 1;
    bonus = 0;
    require(econ::MilitiaTrainingBonus(&militia, &bonus) == 0 && bonus == 0, "non-militia training has no bonus");
}
} // namespace

int main() {
    try {
        // Los dos fallos de búsqueda esperados no deben generar diálogos ni ensuciar logs.
        dl2::hooks::ui.debugMessage = [](const char*) {};
        testQueueLifetime();
        testQueueEditing();
        testRandom();
        testIdsAndTraining();
        std::puts("game infrastructure: queues, pool lifetime, RNG, global IDs and training passed");
        return 0;
    } catch (const std::exception& error) {
        std::fprintf(stderr, "game infrastructure failure: %s\n", error.what());
        return 1;
    }
}
