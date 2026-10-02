// Owned mutating production passes, not a complete turn or preview query.
#pragma once
#include "game/building_progress.h"
#include "game/unit_manufacturing.h"
#include "game/economic_logistics.h"

namespace dl2::simulation {
enum class ProductionPass { Primary=1, Refinement=2 };
using TerritoryProductionContext = UnitManufacturingContext;
struct ProductionTaskVisit {
    uint32_t buildingId=0; int site=0,slot=0; uint8_t task=0; int32_t output=0;
    bool operator==(const ProductionTaskVisit&) const = default;
};
struct ProductionTotals {
    std::array<int32_t,11> materials{};
    std::array<int32_t,6> queues{};
    int32_t credits=0,culture=0,research=0,population=0,training=0,healing=0;
    int32_t steel=0,electronics=0;
    std::vector<ProductionTaskVisit> visits;
    std::vector<RngEvent> artDraws;
    bool operator==(const ProductionTotals&) const = default;
};
struct MilitiaTrainingChange {
    uint32_t armyId=0,territory=0;
    int16_t before=0,after=0,levelBefore=0,levelAfter=0;
    bool operator==(const MilitiaTrainingChange&) const = default;
};
struct TerritoryProductionReport {
    uint32_t territory=0; ProductionPass pass=ProductionPass::Primary;
    ProductionTotals totals;
    BuildingProgressReport work;
    std::vector<UnitManufacturingReport> manufacturing;
    std::vector<EconomicLogisticsReport> refinements;
    std::vector<MilitiaTrainingChange> training;
    int16_t populationBefore=0,populationAfter=0;
    int32_t populationLimit=0,steelConverted=0,electronicsConverted=0;
    bool queueStructureChanged=false;
    std::vector<uint32_t> createdIds;
    std::array<int32_t,kMaxPlayers> citiesAfter{};
    LoadedEventLog logAfter; AiReactionContext aiAfter; RngSnapshot rngAfter;
    ResourceCollectionState collectionAfter;
    std::vector<ConstructionOrderEvent> events;
    bool operator==(const TerritoryProductionReport&) const = default;
};
struct WorldProductionReport {
    ProductionPass pass=ProductionPass::Primary;
    std::vector<TerritoryProductionReport> territories;
    bool queueStructureChanged=false;
    std::vector<uint32_t> createdIds;
    std::array<int32_t,kMaxPlayers> citiesAfter{};
    LoadedEventLog logAfter; AiReactionContext aiAfter; RngSnapshot rngAfter;
    ResourceCollectionState collectionAfter;
    std::vector<ConstructionOrderEvent> events;
    bool operator==(const WorldProductionReport&) const = default;
};
//0044f3f0 with apply=1. Balance first, visit live slots with output cached per
// building, interleave work/upgrade/art and sums, manufacture queues1..5 BEFORE
// any income/population/material gains, train militia and apply refinement.
// Both passes include the original population clamp and training even with0.
// No preview(param2=0), costs-finishing pass0044f110, growth, research resolution,
// morale, reset, tax or complete-turn orchestration is silently performed.
// False preserves source/destination/report, including aliases and late errors.
bool processTerritoryProduction(const save::Document& source,uint32_t territory,
    ProductionPass pass,const TerritoryProductionContext& context,
    save::Document& destination,TerritoryProductionReport& report,save::Error& error);
//0044fcd4: ascending saved territories1..N, skipping owner==-1 only. One shared
// effect/collection continuation; failure in a later territory rolls all back.
bool processWorldProduction(const save::Document& source,ProductionPass pass,
    const TerritoryProductionContext& context,save::Document& destination,
    WorldProductionReport& report,save::Error& error);
namespace detail {
// Internal shared loop, not a user callback: preserves legacy isolated-work API
// while complete production consumes every branch at its original slot position.
bool accumulateBuildingProduction(const save::Document& source,uint32_t territory,
    ProductionPass pass,const BuildingProgressContext& context,save::Document& destination,
    BuildingProgressReport& work,ProductionTotals& totals,save::Error& error);
}
} // namespace dl2::simulation
