#include "game/economic_phase.h"
#include <memory>
#include <stdexcept>

namespace dl2::simulation {
namespace {
template<class Report> void follow(ConstructionOrderContext& next, const Report& r) {
    next.log = r.logAfter; next.ai = r.aiAfter; next.events.rngBeforeEvents = r.rngAfter;
}
}
// orig: FUN_0046c7d4 (ProductionPhase), owned allocator validation replaces the
// native free-list checks; the production flag is structural call scope, no global.
bool runEconomicPhase(const save::Document& source, const EconomicPhaseContext& context,
    save::Document& destination, EconomicPhaseReport& report, save::Error& error) {
    try {
        if (!save::validate(source, error)) return false;
        auto owned = std::make_unique<save::Document>(source); auto& d = *owned;
        auto outcome = std::make_unique<EconomicPhaseReport>(); auto& r = *outcome;
        if (!runEconomicProductionPrefix(d, context, d, r.prefix, error)) return false;
        auto next = context.effects;
        // One authoritative live campaign mask across growth, research and
        // technology acquired by deserters. Never infer bit4 from the SAV.
        next.researchCampaignFlags = context.campaignFlags;
        follow(next, r.prefix); next.payment.collection = r.prefix.collectionAfter;
        next.events.citiesBeforeLoad = r.prefix.citiesAfter;
        r.completed = r.prefix.completed;
        if (!processPopulationGrowth(d, {next, context.campaignFlags}, d, r.growth, error)) return false;
        follow(next, r.growth); r.completed.push_back(EconomicStep::PopulationGrowth);
        if (!processColonyMorale(d, next, d, r.morale, error)) return false;
        follow(next, r.morale); r.completed.push_back(EconomicStep::Morale);
        if (!processResearch(d, next, d, r.research, error)) return false;
        follow(next, r.research); r.completed.push_back(EconomicStep::Research);
        if (!processWorldUnrest(d, next, d, r.unrest, error)) return false;
        follow(next, r.unrest); r.completed.push_back(EconomicStep::Unrest);
        if (!planLaborBalance(d, r.balance, error)) return false;
        // Planner returns all records in physical document order, never changes
        // allocation or references. Apply its exact tasks/labor/morale/stock caps.
        for (size_t i = 0; i < r.balance.buildings.size(); ++i) {
            auto& b = d.buildings[i]; const auto& after = r.balance.buildings[i].after;
            b.flags = after.flags;
            for (size_t s = 0; s < 5; ++s) { b.task[s] = after.tasks[s]; b.labor[s] = after.labor[s]; }
        }
        for (size_t i = 0; i < r.balance.territories.size(); ++i) {
            auto& t = d.territories[i].data; const auto& after = r.balance.territories[i];
            t.morale = after.moraleAfter;
            for (size_t m = 0; m < kNumMaterials; ++m) t.materials[m] = after.materialsAfter[m];
        }
        r.completed.push_back(EconomicStep::FinalBalance);
        r.logAfter = std::move(next.log); r.aiAfter = std::move(next.ai);
        r.rngAfter = next.events.rngBeforeEvents; r.collectionAfter = std::move(next.payment.collection);
        r.citiesAfter = next.events.citiesBeforeLoad;
        if (!save::validate(d, error)) return false;
        destination = std::move(d); report = std::move(r); error = {}; return true;
    } catch (const std::bad_alloc&) {
        error = {save::ErrorCode::Limit, 0, "Economic phase allocation failed"};
    } catch (const std::exception& e) {
        error = {save::ErrorCode::InvalidState, 0, std::string("Economic phase: ") + e.what()};
    }
    return false;
}
} // namespace dl2::simulation
