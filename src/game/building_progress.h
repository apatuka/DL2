// Isolated original building-work branches; not the full production pass/turn.
#pragma once
#include "game/entity_creation.h"
#include "game/load_derived.h"
#include <array>
#include <cstdint>
#include <vector>

namespace dl2::simulation {
struct BuildingProgressContext {
    LoadedEventLog log;
    EventLoadContext events;
    AiReactionContext ai;
    const AiSession* aiSession = nullptr; // Borrowed, never persisted as a callback.
};
struct BuildingWorkChange {
    uint32_t buildingId = 0;
    int slot = 0;
    uint8_t task = 0, typeBefore = 0, typeAfter = 0;
    int8_t siteBefore = 0, siteAfter = 0;
    int32_t output = 0;
    int16_t workBefore = 0, workAfter = 0, upgradeBefore = 0, upgradeAfter = 0;
    bool completed = false, upgraded = false;
    bool operator==(const BuildingWorkChange&) const = default;
};
struct BuildingProgressReport {
    uint32_t territory = 0;
    bool initialLaborBalanced = false, cityCountsRebuilt = false;
    std::vector<BuildingWorkChange> changes; // Execution order, including repeated site visits.
    std::vector<uint32_t> createdIds; // These original branches allocate no new records.
    LoadDerivedReport counts; // CountShrines-only when CityCenter finishes under victory0.
    std::array<int32_t,kMaxPlayers> citiesAfter{};
    LoadedEventLog logAfter;
    AiReactionContext aiAfter;
    RngSnapshot rngAfter;
    std::vector<ConstructionOrderEvent> events;
    bool operator==(const BuildingProgressReport&) const = default;
};
// orig: ProcessTerritoryProduction0044f3f0 mutating pass1, cases2/21 ONLY.
// Balances this territory first; walks sites ascending and uses output cached
// once per visited building with tasks read live as refresh/upgrade changes them.
// Applies signed16 work, completion/repair notices, upgrade relocation, original
// labor reduction and site roads. No stocks/research/training/manufacturing or
// other task branches, no full-turn claim, and no new SeaHab on platform finish.
// Events/AI use one explicit RNG and owned continuation, not SAV text injection.
// Transactions include all partial work/events; false preserves both outputs.
bool progressBuildingWork(const save::Document& source, uint32_t territory,
                         const BuildingProgressContext& context, save::Document& destination,
                         BuildingProgressReport& report, save::Error& error);
} // namespace dl2::simulation
