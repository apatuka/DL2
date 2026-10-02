// A contiguous original ProductionPhase prefix. Explicitly NOT the whole phase.
#pragma once
#include "game/territory_production.h"
#include "game/tax_phase.h"
#include "game/economic_consumption.h"
#include "game/economic_upkeep.h"
#include "game/building_costs.h"

namespace dl2::simulation {
enum class EconomicStep { Reset, Taxes, PrimaryProduction, RecordNeeds, Imports,
                          Food, Energy, Upkeep, Refinement, BuildingCosts,
                          PopulationGrowth, Morale, Research, Unrest, FinalBalance };
const char* economicStepName(EconomicStep step);
using EconomicPrefixContext = TerritoryProductionContext;
struct EconomicPrefixReport {
    std::vector<EconomicStep> completed;
    TaxPlan taxes;
    WorldProductionReport primary;
    NeedsPlan needs;
    EconomicLogisticsReport imports;
    FoodConsumptionReport food;
    EnergyConsumptionReport energy;
    EconomicUpkeepReport upkeep;
    WorldProductionReport refinement;
    BuildingCostsReport costs;
    std::vector<uint32_t> createdIds, retiredIds;
    bool queueStructureChanged = false;
    LoadedEventLog logAfter;
    AiReactionContext aiAfter;
    RngSnapshot rngAfter;
    ResourceCollectionState collectionAfter;
    std::array<int32_t, kMaxPlayers> citiesAfter{};
};
//0046c7d4 FROM its resets THROUGH0044f110. Run once from a snapshot explicitly
// representing entry into production. It does NOT execute prior movement/AI or
// the subsequent growth, morale, research resolution, riots, EndTurnBalance.
// Work and outputs are interleaved inside each actual territory pass; factory
// budgets come from assigned labor, not caller-supplied or maximum production.
// One stream/log/AI/cache across ALL steps, all-or-nothing even on a late error.
// No options.turn change, playable activation, serialization or global flag.
bool runEconomicProductionPrefix(const save::Document& source,
    const EconomicPrefixContext& context, save::Document& destination,
    EconomicPrefixReport& report, save::Error& error);
} // namespace dl2::simulation
