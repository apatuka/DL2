// Owned QueueUnit/Dequeue/ProduceUnits substeps, not a complete production turn.
#pragma once
#include "game/entity_creation.h"
#include "game/entity_lifecycle.h"
#include <array>
#include <vector>

namespace dl2::simulation {
struct UnitManufacturingContext {
    ConstructionOrderContext effects;
    ArmyCreationContext creation;
};
struct QueueUnitRequest { uint32_t territory = 0; int unitType = 0; };
struct ProduceUnitsRequest { uint32_t territory = 0; int queue = 0; int32_t production = 0; };
struct DequeueUnitRequest { uint32_t territory = 0; int queue = 0; uint32_t index = 0; };
struct UnitManufacturingReport {
    uint32_t territory = 0;
    int queue = 0; // Original categories1..5, not a zero-based vector index.
    bool queued = false, headFinancingBlocked = false, creationBlocked = false;
    bool queueStructureChanged = false; // Allocation/free, even if final bytes match.
    uint32_t failureMask = 0; // Native QueueUnit result; population denial is UINT32_MAX.
    int32_t productionBefore = 0, productionRemaining = 0;
    int16_t populationBefore = 0, populationAfter = 0;
    ArmyCreationReason creationDenial = ArmyCreationReason::Allowed;
    std::vector<uint32_t> createdIds; // Includes physically created paired missiles.
    std::vector<ArmyLifecycleReport> creations;
    std::vector<ConstructionPaymentReport> payments;
    LoadedEventLog logAfter;
    AiReactionContext aiAfter;
    RngSnapshot rngAfter;
    ResourceCollectionState collectionAfter;
    std::vector<ConstructionOrderEvent> events;
    bool operator==(const UnitManufacturingReport&) const = default;
};
struct UnitDequeueReport {
    bool removed = false;
    uint32_t territory = 0, index = 0;
    int queue = 0, unitType = 0;
    int32_t creditsRefunded = 0;
    std::array<int32_t,10> materialsRefunded{};
    int16_t populationBefore = 0, populationAfter = 0;
    bool operator==(const UnitDequeueReport&) const = default;
};
//0044ddf4: canonical signed work/technology and11 full-width costs. Player is
// unused by the original. Queue category derives from canonical unitClass.
bool unitManufacturingRequirements(int unitType, ConstructionRequirements& destination,
                                  save::Error& error);
//0044df94: pay first, append one record only for result0, colonizers25/31
// require population>100 and subtract100 with local labor balance. No hidden
// completion/start64 event; only actual collection/import events are emitted.
// Unsupported factory classes have queue0 and original evaluated result0 but
// queued=false. The codec's255 nodes is an explicit safety limit, not gameplay.
bool queueUnit(const save::Document& source, const QueueUnitRequest& request,
               const UnitManufacturingContext& context, save::Document& destination,
               UnitManufacturingReport& report, save::Error& error);
//0044e0a8: zero-based ordinal; missing ordinal is an evaluated removed=false.
// Refunds CANONICAL full money but signed LOW16 of saved paid materials1..10;
// colonizer population+100 wraps signed16 and balances labor. No clamp invented.
bool dequeueUnit(const save::Document& source, const DequeueUnitRequest& request,
                 save::Document& destination, UnitDequeueReport& report, save::Error& error);
//0044e174: explicit production is supplied by the real caller, not synthesized
// from hypothetical maximum outputs. Refinance only the initial head once;
// count+02 is signed16 WORK remaining, not a number of units. Zero/negative
// remaining work can create without consuming production. Sea units use portTarget.
// T+9ae bits1..5 are repeat bits in THIS consumer (legacy name hoverway).
// Repetition retains original0xf001 mask quirk, partial payments, prepend and
// event order. Failed spawn consumes attempted ID, retains work0 head, stops.
// No native queue pointers/cursors are installed. Newly allocated opaque byte+01
// is deliberately zero; reinserting a record preserves its saved opaque byte.
// This is a safe owner representation, not parity with uninitialized malloc.
// Ordinary evaluated denials may change payment/search/RNG/IDs. API errors
// preserve document+report atomically, including aliases. No global state/I/O,
// population growth, task-force turn, native presentation or resumable SAV.
bool produceUnits(const save::Document& source, const ProduceUnitsRequest& request,
                  const UnitManufacturingContext& context, save::Document& destination,
                  UnitManufacturingReport& report, save::Error& error);
} // namespace dl2::simulation
