// Exact needs and an isolated energy projection, not a complete economic turn.
#pragma once
#include <cstdint>
#include <vector>
#include "game/save_document.h"

namespace dl2::simulation {

struct TerritoryNeeds {
    uint32_t territory = 0;
    int32_t foodNeed = 0;   // FUN_0046b958: population * saved RaceStats[61][race] / 10000.
    int32_t energyNeed = 0; // FUN_0046b910: completed, active buildings, in site order.
    // FUN_0046b9a0 narrows each need to signed 16 bits before recording it in
    // Territory+0xa82/+0xa86. Those original scratch fields are NOT saved.
    int32_t foodReserve = 0;
    int32_t energyReserve = 0;
};
struct NeedsPlan { std::vector<TerritoryNeeds> territories; };

struct TerritoryEnergy {
    uint32_t territory = 0;
    int32_t energyBefore = 0;
    int32_t need = 0;
    int16_t consumed = 0; // Original subtraction narrows min(stock, need) to s16.
    int32_t energyAfter = 0;
    uint8_t energyPercentBefore = 0;
    uint8_t energyPercentAfter = 0; // Physical byte Territory+0x35 (legacy knowledge).
};
struct EnergyShortfall {
    uint16_t type = 0x33;
    int recipient = -1;
    uint32_t territory = 0;
    int32_t shortage = 0; // Original event argument: 100 - signed byte of new percent.
};
struct EnergyPlan {
    std::vector<TerritoryEnergy> territories;
    // Semantic LogEventEx requests in territory order. These are NOT serialized
    // event records and do not execute the original UI or AI event callbacks.
    std::vector<EnergyShortfall> shortfalls;
};

// All plans are pure and transactional: failure preserves output; success clears
// error. Maps are rejected. No global state, RNG, callbacks or document writes.
// Needs are for the CURRENT snapshot, not a forecast of production/imports.
bool planNeeds(const save::Document& source, NeedsPlan& output, save::Error& error);
// orig: FUN_0046bc28 (ConsumeEnergy), numerical effects and semantic event requests
// only. This isolated projection does not imply prior production/logistics/food
// have run, and never advances a turn. Undefined original divisions are rejected.
bool planEnergy(const save::Document& source, EnergyPlan& output, save::Error& error);

} // namespace dl2::simulation
