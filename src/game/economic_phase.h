// Owned ProductionPhase, not a complete turn or a playable activation.
#pragma once
#include "game/economic_prefix.h"
#include "game/population_growth.h"
#include "game/colony_unrest.h"

namespace dl2::simulation {
struct EconomicPhaseContext : EconomicPrefixContext {
    // Authoritative live DAT0059f100 for this sequence, not recovered from SAV.
    // Overrides effects.researchCampaignFlags (the isolated research-leaf input).
    uint32_t campaignFlags = 0;
};
struct EconomicPhaseReport {
    EconomicPrefixReport prefix;
    std::vector<EconomicStep> completed;
    PopulationGrowthReport growth;
    ColonyMoraleReport morale;
    ResearchReport research;
    WorldUnrestReport unrest;
    LaborBalancePlan balance;
    LoadedEventLog logAfter;
    AiReactionContext aiAfter;
    RngSnapshot rngAfter;
    ResourceCollectionState collectionAfter;
    std::array<int32_t, kMaxPlayers> citiesAfter{};
};
//0046c7d4: reset -> BOTH production passes and intervening costs/consumption
// -> population -> morale -> research -> unrest -> EndTurnBalance. All-or-nothing.
// Caller explicitly supplies an entry-to-production snapshot and live context;
// preceding movement, diplomacy, AI turns and following turn phases are NOT run.
// Native undefined/unsupported domains in any leaf reject the WHOLE phase.
// No turn increment, full-turn claim, playable activation or partial SAV export.
bool runEconomicPhase(const save::Document&, const EconomicPhaseContext&,
    save::Document&, EconomicPhaseReport&, save::Error&);
} // namespace dl2::simulation
