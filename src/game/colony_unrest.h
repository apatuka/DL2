// Owned0046c49c/DoRiot. No control transfer, allocation or invented callbacks.
#pragma once
#include "game/colony_morale.h"
#include "game/labor_balance.h"
#include "game/research_phase.h"

namespace dl2::simulation {
enum class ColonyUnrestOutcome { Skipped, Stable, MigrationAttempt, Migrated, Unhappy, Agitated, Riot, DirectRiot };
struct RiotBuildingDamage {
    uint32_t buildingId=0;
    int site=0,type=0;
    int16_t workBefore=0,workAfter=0;
    bool operator==(const RiotBuildingDamage&) const = default;
};
struct ColonyUnrestReport {
    uint32_t territory=0,destination=0;
    ColonyUnrestOutcome outcome=ColonyUnrestOutcome::Skipped;
    int16_t populationBefore=0,populationAfter=0,destinationBefore=0,destinationAfter=0;
    LaborAvailability labor;
    int32_t revoltStrength=0,migrants=0,riotDeaths=0;
    int technology=0;
    ColonyMoraleMetrics morale;
    std::vector<RiotBuildingDamage> damage;
    std::vector<RngEvent> draws; // Explicit revolt/riot/steal draws, in call order.
    ResearchReport acquisition;
    LoadedEventLog logAfter; AiReactionContext aiAfter; RngSnapshot rngAfter;
    std::vector<ConstructionOrderEvent> events;
    bool operator==(const ColonyUnrestReport&) const = default;
};
struct WorldUnrestReport {
    std::vector<ColonyUnrestReport> territories;
    LoadedEventLog logAfter; AiReactionContext aiAfter; RngSnapshot rngAfter;
    std::vector<ConstructionOrderEvent> events;
    bool operator==(const WorldUnrestReport&) const = default;
};
//0046c310: signed16 population subtraction, then one TaggedRange100("DoRiot")
// for EACH occupied site, INCLUDING type38. Qualified non-platform buildings
// gain half canonical labor, capped at canonical labor, emit REAL event83.
// No flags/labor/task refresh or deletion is performed by the original leaf.
bool doColonyRiot(const save::Document& source,uint32_t territory,int16_t deaths,
    const ConstructionOrderContext& context,save::Document& destination,
    ColonyUnrestReport& report,save::Error& error);

//0046c49c: labor query, Revolt draw, army suppression strength, migration OR
// raw morale comparison and riot branch. Migration search0046c254/00446b3c
// uses mode3/range500, strict distance then territory order; only populations
// transfer, never ownership. Tech selection precedes events/acquisition and
// AcquireTech is called even for technology0. Preserves original signedness,
// event order, donor/destination population narrowing and search scratch.
// IMPORTANT authentic undefined branch: assembly0046c5dc emits87 with an
// integer where its PE format expects %s;0046c60c emits86 with swapped shape.
// A migration TO the local player is rejected atomically rather than inventing
// text, swapping IDs silently, or interpreting an integer as a native pointer.
// Nonlocal AI/remote-human dispatch preserves those original IDs and payloads.
bool processColonyUnrest(const save::Document& source,uint32_t territory,
    const ConstructionOrderContext& context,save::Document& destination,
    ColonyUnrestReport& report,save::Error& error);
//0046c7d4 loops territories1..N after research, sharing RNG/log/AI. Later
// territory failure rolls back the WHOLE operation. No hidden morale/growth,
// balance, turn advance or partial-save permission is added.
bool processWorldUnrest(const save::Document& source,const ConstructionOrderContext& context,
    save::Document& destination,WorldUnrestReport& report,save::Error& error);
// All APIs are owned and transactional, including source==destination. No
// native gs/gg/RNG, executable archive pointers, UI or fake simulation hooks.
} // namespace dl2::simulation
