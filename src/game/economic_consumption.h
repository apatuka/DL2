// Owned food and energy consumption, with actual local/AI event delivery.
#pragma once
#include "game/entity_creation.h"
#include "game/resource_needs.h"

namespace dl2::simulation {
struct TerritoryFoodChange {
    uint32_t territory = 0;
    int32_t need = 0, stockBefore = 0, stockAfter = 0;
    int32_t reserveBefore = 0, reserveAfter = 0;
    int16_t consumed = 0;
    uint8_t hungerBefore = 0, hungerAfter = 0; // Territory+29, read signed.
    bool operator==(const TerritoryFoodChange&) const = default;
};
enum class UnitFoodSource { LocalStock, FreeSupplier, Collected, Starved, MissingTerritory };
struct UnitFoodChange {
    uint32_t army = 0, territory = 0, supplier = 0;
    UnitFoodSource source = UnitFoodSource::MissingTerritory;
    int32_t collectionResult = 0;
    bool operator==(const UnitFoodChange&) const = default;
};
struct FoodConsumptionReport {
    std::vector<TerritoryFoodChange> territories;
    std::vector<UnitFoodChange> armies; // Owned physical order, not ID-sorted.
    std::array<uint8_t, kMaxPlayers> flagsBefore{}, flagsAfter{};
    LoadedEventLog logAfter;
    AiReactionContext aiAfter;
    RngSnapshot rngAfter;
    ResourceCollectionState collectionAfter;
    std::vector<ConstructionOrderEvent> events;
    bool operator==(const FoodConsumptionReport&) const = default;
};
struct EnergyConsumptionReport {
    EnergyPlan energy;
    LoadedEventLog logAfter;
    AiReactionContext aiAfter;
    RngSnapshot rngAfter;
    std::vector<ConstructionOrderEvent> events;
};
//0046b9e8: civilians first, then active armies in physical allocation order,
// first friendly stock / free supply search for eligible missions or aircraft /
// CollectMaterial fallback. Starvation flags and actual events50/60/2 retain
// native order. A null current territory is a reported diagnostic skip, matching
// the original DebugMessage branch. No army damage/disband or population growth.
bool consumeFood(const save::Document& source, const ConstructionOrderContext& context,
                 save::Document& destination, FoodConsumptionReport& report, save::Error& error);
//0046bc28: numerical plan plus actual event51 dispatch, rather than only notices.
// Both calls are transactional (including alias), no globals, turn increment or
// resumable save. Caller must supply and retain the real shared continuation.
bool consumeEconomicEnergy(const save::Document& source, const ConstructionOrderContext& context,
                           save::Document& destination, EnergyConsumptionReport& report, save::Error& error);
} // namespace dl2::simulation
