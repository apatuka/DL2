// Owned execution preparation, separate from the legacy gs/gg and packed Ptr32s.
// Known file references resolve to typed, state-local handles. Opaque old words
// remain solely in the archival document and are never executable pointers.
#pragma once
#include <array>
#include <cstdint>
#include <memory>
#include <vector>
#include "game/save_document.h"
#include "game/tax_phase.h"
#include "game/resource_needs.h"

namespace dl2::runtime {
template<class Tag> struct Handle {
    uint32_t slot = 0; // 1-based; zero is null. Valid only for its owning State.
    explicit operator bool() const { return slot != 0; }
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

enum class Stage { Empty, Prepared, TaxesApplied, EnergyApplied };
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
    bool advanceTurn(save::Error& error); // Explicit unsupported operation, never a no-op success.
    Stage stage() const { return stage_; }
    const save::Document* document() const { return document_.get(); }
    const Graph& graph() const { return graph_; }
    BuildingHandle buildingById(uint32_t id) const;
    ArmyHandle armyById(uint32_t id) const;
    const Building* building(BuildingHandle h) const;
    const Army* army(ArmyHandle h) const;
    const save::TerritoryRecord* territory(TerritoryHandle h) const;
    const Tile* tile(TileHandle h) const;
    const Queue* queue(QueueHandle h) const;
    const QueueNode* queueNode(QueueNodeHandle h) const;
    const MinisterNode* minister(MinisterHandle h) const;
private:
    std::unique_ptr<save::Document> document_;
    Graph graph_;
    Stage stage_ = Stage::Empty;
};
} // namespace dl2::runtime
