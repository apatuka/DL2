#include "game/economic_prefix.h"
#include <algorithm>
#include <memory>
#include <stdexcept>

namespace dl2::simulation {
const char* economicStepName(EconomicStep step) {
    switch (step) {
    case EconomicStep::Reset: return "reset";
    case EconomicStep::Taxes: return "taxes";
    case EconomicStep::PrimaryProduction: return "primary_production";
    case EconomicStep::RecordNeeds: return "record_needs";
    case EconomicStep::Imports: return "imports";
    case EconomicStep::Food: return "food";
    case EconomicStep::Energy: return "energy";
    case EconomicStep::Upkeep: return "upkeep";
    case EconomicStep::Refinement: return "refinement";
    case EconomicStep::BuildingCosts: return "building_costs";
    }
    return "unknown";
}
namespace {
template<class Report> void followEffects(ConstructionOrderContext& next, const Report& r) {
    next.log = r.logAfter; next.ai = r.aiAfter; next.events.rngBeforeEvents = r.rngAfter;
}
template<class Report> void followCollection(ConstructionOrderContext& next, const Report& r) {
    followEffects(next, r); next.payment.collection = r.collectionAfter;
}
}
// orig: FUN_0046c7d4, contiguous prefix only (no false whole-turn success).
bool runEconomicProductionPrefix(const save::Document& source,
    const EconomicPrefixContext& context, save::Document& destination,
    EconomicPrefixReport& report, save::Error& error) {
    try {
        if (!save::validate(source, error)) return false;
        if (source.header.isMap || source.options.numPlayers > kMaxPlayers || source.options.numPlayers < 0) {
            error = {save::ErrorCode::InvalidState, 0, "Economic prefix requires a saved game and player count0..7"}; return false;
        }
        SessionRng rng;
        if (!rng.restore(context.effects.events.rngBeforeEvents, error)) return false;
        if (context.effects.ai.rng != context.effects.events.rngBeforeEvents) {
            error = {save::ErrorCode::InvalidState, 0, "Economic prefix requires a single shared event/AI RNG"}; return false;
        }
        auto owned = std::make_unique<save::Document>(source); auto& d = *owned;
        // Keep this large report off the stack (nested reports retain event pools).
        auto outcome = std::make_unique<EconomicPrefixReport>(); auto& r = *outcome;
        auto next = context;
        if (!resetEconomicLogistics(d, next.effects.payment.collection, d, next.effects.payment.collection, error)) return false;
        for (int p = 0; p < d.options.numPlayers; ++p) d.players[size_t(p)].lastIncome = 0;
        for (auto& region : d.territories) {
            region.data.colonyFlag = 0;
            std::fill(std::begin(region.data.consumption), std::end(region.data.consumption), 0);
            std::fill(std::begin(region.data.production), std::end(region.data.production), 0);
        }
        r.completed.push_back(EconomicStep::Reset);
        if (!planTaxes(d, r.taxes, error)) return false;
        for (size_t p = 0; p < kMaxPlayers; ++p) d.players[p].credits = r.taxes.creditsAfter[p];
        r.completed.push_back(EconomicStep::Taxes);
        if (!processWorldProduction(d, ProductionPass::Primary, next, d, r.primary, error)) return false;
        followCollection(next.effects, r.primary); next.effects.events.citiesBeforeLoad = r.primary.citiesAfter;
        r.completed.push_back(EconomicStep::PrimaryProduction);
        if (!recordFoodEnergyNeeds(d, d, r.needs, error)) return false;
        r.completed.push_back(EconomicStep::RecordNeeds);
        if (!importDeficits(d, next.effects, d, r.imports, error)) return false;
        followCollection(next.effects, r.imports); r.completed.push_back(EconomicStep::Imports);
        if (!consumeFood(d, next.effects, d, r.food, error)) return false;
        followCollection(next.effects, r.food); r.completed.push_back(EconomicStep::Food);
        if (!consumeEconomicEnergy(d, next.effects, d, r.energy, error)) return false;
        followEffects(next.effects, r.energy); r.completed.push_back(EconomicStep::Energy);
        if (!processEconomicUpkeep(d, next.effects, d, r.upkeep, error)) return false;
        followEffects(next.effects, r.upkeep); r.completed.push_back(EconomicStep::Upkeep);
        if (!processWorldProduction(d, ProductionPass::Refinement, next, d, r.refinement, error)) return false;
        followCollection(next.effects, r.refinement); next.effects.events.citiesBeforeLoad = r.refinement.citiesAfter;
        r.completed.push_back(EconomicStep::Refinement);
        if (!processBuildingCosts(d, next.effects, d, r.costs, error)) return false;
        followCollection(next.effects, r.costs); r.completed.push_back(EconomicStep::BuildingCosts);
        r.createdIds = r.primary.createdIds;
        r.createdIds.insert(r.createdIds.end(), r.refinement.createdIds.begin(), r.refinement.createdIds.end());
        r.retiredIds = r.upkeep.retiredIds;
        r.queueStructureChanged = r.primary.queueStructureChanged || r.refinement.queueStructureChanged;
        r.logAfter = std::move(next.effects.log); r.aiAfter = std::move(next.effects.ai);
        r.rngAfter = next.effects.events.rngBeforeEvents; r.citiesAfter = next.effects.events.citiesBeforeLoad;
        r.collectionAfter = std::move(next.effects.payment.collection);
        if (!save::validate(d, error)) return false;
        destination = std::move(d); report = std::move(r); error = {}; return true;
    } catch (const std::bad_alloc&) {
        error = {save::ErrorCode::Limit, 0, "Economic prefix allocation failed"};
    } catch (const std::exception& e) {
        error = {save::ErrorCode::InvalidState, 0, std::string("Economic prefix: ") + e.what()};
    }
    return false;
}
} // namespace dl2::simulation
