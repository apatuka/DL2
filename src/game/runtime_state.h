// Owned execution preparation, separate from the legacy gs/gg and packed Ptr32s.
// Known file references resolve to typed, state-local handles. Opaque old words
// remain solely in the archival document and are never executable pointers.
#pragma once
#include <array>
#include <cstdint>
#include <memory>
#include <optional>
#include <vector>
#include "game/save_document.h"
#include "game/tax_phase.h"
#include "game/resource_needs.h"
#include "game/labor_balance.h"
#include "game/load_profile.h"
#include "game/load_derived.h"
#include "game/session_rng.h"
#include "game/load_session.h"
#include "game/load_intelligence.h"
#include "game/entity_creation.h"

namespace dl2::runtime {
template<class Tag> struct Handle {
    uint32_t slot = 0; // Stable, 1-based registry slot; NOT a document vector index.
    uint64_t identity = 0; // Opaque lifetime token; never serialized or reused.
    explicit operator bool() const { return slot != 0 && identity != 0; }
    bool operator==(const Handle&) const = default;
};
struct BuildingTag; struct ArmyTag; struct TerritoryTag; struct TileTag;
struct QueueTag; struct QueueNodeTag; struct MinisterTag;
using BuildingHandle = Handle<BuildingTag>;
using ArmyHandle = Handle<ArmyTag>;
using TerritoryHandle = Handle<TerritoryTag>;
using TileHandle = Handle<TileTag>;
using QueueHandle = Handle<QueueTag>;
using QueueNodeHandle = Handle<QueueNodeTag>;
using MinisterHandle = Handle<MinisterTag>;

struct BuildingLinks {
    TerritoryHandle territory;
    BuildingHandle previous, next; // Resolved historical list, not followed to enumerate objects.
};
struct ArmyLinks {
    TerritoryHandle current, turnStart, routeOrigin;
    ArmyHandle previous, next;
    std::array<ArmyHandle, 3> cargo{};
};
struct TerritoryLinks {
    std::vector<TileHandle> tiles;
    std::vector<TerritoryHandle> adjacent;
    std::array<BuildingHandle, kNumSites> sites{};
    std::array<QueueHandle, 5> queues{};
    // Canonical membership from object locations, independent of stale legacy heads.
    std::vector<BuildingHandle> buildings;
    std::vector<ArmyHandle> armies;
    ArmyHandle savedOwnHead, savedForeignHead;
};
struct QueueNode {
    QueueRecord record{}; // next.raw is cleared; use the typed next below.
    QueueNodeHandle next;
};
struct Queue {
    QueueNodeHandle first, cursor; // Cursor starts at first, as LoadQueue does.
    uint32_t count = 0;
};
struct MinisterNode {
    int player = 0;
    uint32_t recordIndex = 0; // Index in document.ministerJobs[player], includes head.
    MinisterHandle previous, next; // Rebuilt by file order, NOT old pointer numbers.
};
struct JobLinks {
    TerritoryHandle destination;
    std::array<ArmyHandle, 16> armies{}; // From armyIds, never Job::armies raw words.
};
struct Graph {
    std::vector<BuildingLinks> buildings;
    std::vector<ArmyLinks> armies;
    std::vector<TerritoryLinks> territories;
    std::vector<Queue> queues;
    std::vector<QueueNode> queueNodes;
    std::vector<MinisterNode> ministers;
    std::array<MinisterHandle, kMaxPlayers> ministerHeads{};
    std::array<std::array<JobLinks, kJobsPerPlayer>, kMaxPlayers> jobs{};
    std::array<std::vector<TerritoryHandle>, kMaxPlayers> playerTerritories;
};

enum class EntityKind { Building, Army };
enum class EntityEditOperation { Inserted, Retired };
struct EntityEditReport {
    EntityKind kind = EntityKind::Building;
    EntityEditOperation operation = EntityEditOperation::Inserted;
    uint32_t id = 0, territory = 0;
    int32_t site = -1; // No building site for armies.
    uint32_t beforeCount = 0, afterCount = 0;
    uint32_t previousId = 0, nextId = 0; // Inserted/retired node's list neighbors.
    bool operator==(const EntityEditReport&) const = default;
};

enum class LoadScope { Partial, Complete };
enum class MissingLoadCapability {
    AiInitialization, Visibility, Contacts, BuildingIntelligence,
    NativeEventLog, TransientSessionState, ChangedWorldScan
};
struct LoadReport {
    simulation::LoadCoreReport core;
    simulation::LoadDerivedReport derived;
    simulation::LoadIntelligenceReport intelligence;
    simulation::LaborBalancePlan labor;
    simulation::RngSnapshot rng;
    bool complete = false;
    bool eventsRebuilt = false, timerPlanned = false;
    uint32_t loadedEvents = 0, eventRandomDraws = 0;
    std::vector<MissingLoadCapability> missing{
        MissingLoadCapability::AiInitialization,
        MissingLoadCapability::NativeEventLog, MissingLoadCapability::TransientSessionState,
        MissingLoadCapability::ChangedWorldScan};
    bool operator==(const LoadReport&) const = default;
};
const char* missingLoadCapabilityName(MissingLoadCapability capability);
struct LoadContext {
    simulation::LoadIntelligenceContext intelligence;
    // Omit only for a partial load. A nonempty native event log requires its
    // actual pre-event RNG/city context, not an invented seed from the SAV.
    std::optional<simulation::EventLoadContext> events;
    std::optional<uint32_t> clockMs;
    simulation::LoadTimerState previousTimer;
};

enum class Stage { Empty, Prepared, TaxesApplied, EnergyApplied, LaborBalanced, EntitiesEdited, LoadNormalized };
class State {
public:
    State() = default;
    State(State&&) noexcept;
    State& operator=(State&&) noexcept;
    State(const State&) = delete;
    State& operator=(const State&) = delete;
    // Transactional. Maps are inspectable documents but are not execution states.
    bool prepare(const save::Document& source, save::Error& error);
    // Prepared snapshots roundtrip exactly. A partial economic phase CANNOT be
    // exported as a resumable save until a complete turn implementation exists.
    bool capture(save::Document& destination, save::Error& error) const;
    // One real fiscal phase, once per preparation. Does not advance options.turn.
    // Failure preserves state and report; no RNG, hooks, globals or I/O involved.
    bool collectTaxes(simulation::TaxPlan& report, save::Error& error);
    // Isolated ConsumeEnergy experiment on the prepared snapshot, NOT the next
    // economic step after taxes: production/imports/food must precede it in a turn.
    // Changes only energy stock and energy percentage; reports semantic events.
    bool consumeEnergy(simulation::EnergyPlan& report, save::Error& error);
    // Explicit EndTurnBalance normalization: refresh tasks, balance workers,
    // cap material stocks. NOT full LoadGame activation or a production phase.
    // Once from Prepared; cannot chain experiments or publish a partial save.
    bool normalizeLabor(simulation::LaborBalancePlan& report, save::Error& error);
    // Offline generation-4 load subset, in explicit order: core profile/events,
    // continents/shrines/tile roads, intelligence, labor, research restriction,
    // final owned RNG reseed. NOT playable activation. Complete scope rejects.
    // Once from Prepared; all-or-nothing, including graph, handles and RNG.
    // No normalized SAV export, no partial-to-full-turn chaining.
    bool normalizeLoad(const simulation::LoadProfile& profile, LoadReport& report,
                       save::Error& error, LoadScope scope = LoadScope::Partial,
                       const LoadContext& context = {});
    simulation::RngSnapshot sessionRng() const { return rng_.snapshot(); }
    const simulation::LoadCoreReport* loadCore() const { return core_ ? &*core_ : nullptr; }
    const simulation::LoadedEventLog* loadedEvents() const { return events_ ? &*events_ : nullptr; }
    const simulation::LoadTimerReport* loadTimer() const { return timer_ ? &*timer_ : nullptr; }
    // Completed-building initializer with real local labor/footprint/roads.
    // Not a paid construction order; shares the explicit nonplayable edit stage.
    bool createCompletedBuilding(const simulation::BuildingCreationRequest& request,
                                 BuildingHandle& created, simulation::BuildingCreationReport& report,
                                 save::Error& error);
    // Structural storage operations, NOT construction, manufacturing, demolition
    // or combat orders. Callers supply complete payloads and explicit file IDs;
    // only list references and the building's anchor-site reference are derived.
    // No costs, defaults, terrain/roads/footprints, labor, AI, RNG or events change.
    // Restricted to simple size-one non-platform/non-shrine buildings and armies
    // without transport/siege/job dependencies. Coherent affected lists required.
    // Counts retain the original allocator's reserved free node (1199 / 559).
    // Success enters EntitiesEdited: more structural edits are allowed, but
    // capture/economic experiments/full turns are not. Failure changes no output.
    bool insertBuilding(const Building& record, BuildingHandle& created,
                        EntityEditReport& report, save::Error& error);
    bool retireBuilding(BuildingHandle handle, EntityEditReport& report, save::Error& error);
    bool insertArmy(const Army& record, ArmyHandle& created,
                    EntityEditReport& report, save::Error& error);
    bool retireArmy(ArmyHandle handle, EntityEditReport& report, save::Error& error);
    bool advanceTurn(save::Error& error); // Explicit unsupported operation, never a no-op success.
    Stage stage() const { return stage_; }
    const save::Document* document() const { return document_.get(); }
    const Graph& graph() const { return graph_; }
    BuildingHandle buildingById(uint32_t id) const;
    ArmyHandle armyById(uint32_t id) const;
    TerritoryHandle territoryByIndex(uint32_t fileIndex) const;
    TileHandle tileByIndex(uint32_t oneBasedIndex) const;
    const Building* building(BuildingHandle h) const;
    const Army* army(ArmyHandle h) const;
    const BuildingLinks* buildingLinks(BuildingHandle h) const;
    const ArmyLinks* armyLinks(ArmyHandle h) const;
    const save::TerritoryRecord* territory(TerritoryHandle h) const;
    const Tile* tile(TileHandle h) const;
    const Queue* queue(QueueHandle h) const;
    const QueueNode* queueNode(QueueNodeHandle h) const;
    const MinisterNode* minister(MinisterHandle h) const;
private:
    struct EntitySlot {
        uint64_t identity = 0; // Zero denotes a reusable free slot.
        uint32_t denseIndex = 0;
    };
    // The document remains densely ordered; stable slots resolve through these
    // registries. Erasure preserves the order and identities of all survivors.
    std::vector<EntitySlot> buildingSlots_, armySlots_;
    std::vector<uint32_t> buildingDenseSlots_, armyDenseSlots_;
    uint64_t preparationIdentity_ = 0; // Static graph handles' owning lifetime.
    bool rebuildGraph(save::Error& error);
    bool copyForEdit(State& candidate, save::Error& error) const;
    bool finishEdit(State&& candidate, save::Error& error);
    std::unique_ptr<save::Document> document_;
    Graph graph_;
    simulation::SessionRng rng_;
    std::optional<simulation::LoadCoreReport> core_;
    std::optional<simulation::LoadedEventLog> events_;
    std::optional<simulation::LoadTimerReport> timer_;
    Stage stage_ = Stage::Empty;
};
// All returned pointers and Graph references are borrowed until the next
// successful structural mutation, load normalization or prepare/move assignment.
// Keep handles, not pointers: surviving identities endure edits/normalization.
} // namespace dl2::runtime
