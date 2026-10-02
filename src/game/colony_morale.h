#pragma once
#include "game/entity_creation.h"
namespace dl2::simulation {
struct ColonyMoraleMetrics {
    uint32_t territory=0;
    // Baseline,crowding,food,occupation,cloning,tax,garrison,culture,art,hospital.
    std::array<int32_t,10> components{};
    int32_t baseline=0,total=0,value=0;
    bool operator==(const ColonyMoraleMetrics&) const = default;
};
//0046bce4: mission13 eligible own-list attack strength; also used by unrest.
bool colonyRevoltStrength(const save::Document&,uint32_t,int32_t&,save::Error&);
//0046bdfc: total is RAW DAT58f178, NOT clamped return value. Racial row27=0
// returns fixed80 and does not evaluate other domains; unowned returns100.
bool colonyMoraleMetrics(const save::Document&,uint32_t,ColonyMoraleMetrics&,save::Error&);
struct ColonyMoraleChange {
    uint32_t territory=0; int8_t before=0,after=0; ColonyMoraleMetrics metrics;
    bool operator==(const ColonyMoraleChange&) const = default;
};
struct ColonyMoraleReport {
    std::vector<ColonyMoraleChange> territories;
    LoadedEventLog logAfter; AiReactionContext aiAfter; RngSnapshot rngAfter;
    std::vector<ConstructionOrderEvent> events; // Original morale pass emits none.
    bool operator==(const ColonyMoraleReport&) const = default;
};
//0046c1a8(apply1), owned saved territories1..N. Absent native zero sentinel
// has no saved payload to update. No balance, events, riots or RNG draw.
bool processColonyMorale(const save::Document&,const ConstructionOrderContext&,
    save::Document&,ColonyMoraleReport&,save::Error&);
} // namespace dl2::simulation
