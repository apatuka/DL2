#pragma once
#include "game/entity_creation.h"
namespace dl2::simulation {
struct PopulationLimits {
    int32_t land=0,housing=0,maximum=0;
    bool operator==(const PopulationLimits&) const = default;
};
//0046b074/0046b0e4: Built completed housing only, signed saved row24.
bool territoryPopulationLimits(const save::Document&,uint32_t,PopulationLimits&,save::Error&);
struct PopulationGrowthContext {
    ConstructionOrderContext effects;
    uint32_t campaignFlags=0; // Live DAT0059f100, bit10 inhibits LOCAL growth.
};
struct PopulationGrowthChange {
    uint32_t territory=0;
    int16_t before=0,after=0,rateBefore=0,rateAfter=0;
    int32_t calculatedAfter=0,growthPercent=0,laborTrigger=0;
    PopulationLimits limits;
    bool balancedLabor=false,campaignSkipped=false;
    bool operator==(const PopulationGrowthChange&) const = default;
};
struct PopulationGrowthReport {
    std::vector<PopulationGrowthChange> territories;
    LoadedEventLog logAfter; AiReactionContext aiAfter; RngSnapshot rngAfter;
    std::vector<ConstructionOrderEvent> events;
    bool operator==(const PopulationGrowthReport&) const = default;
};
//0046b1ac(apply1). No implicit production/food/morale or turn. Full-width new
// population governs events/percentage, while stored population narrows WORD.
// Preserve original labor trigger new/100-(old-100), NOT a corrected delta.
bool processPopulationGrowth(const save::Document&,const PopulationGrowthContext&,
    save::Document&,PopulationGrowthReport&,save::Error&);
} // namespace dl2::simulation
