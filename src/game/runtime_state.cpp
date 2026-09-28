#include "game/runtime_state.h"
#include "game/army_state.h"
#include <exception>
#include <new>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>

namespace dl2::runtime {
namespace {
bool fail(save::Error& e, save::ErrorCode code, std::string message) {
    e = {code, 0, std::move(message)}; return false;
}
template<class Operation> bool guarded(Operation&& operation, save::Error& error) {
    try { return operation(); }
    catch (const std::bad_alloc&) {
        return fail(error, save::ErrorCode::Limit, "Insufficient memory preparing execution state");
    } catch (const std::length_error&) {
        return fail(error, save::ErrorCode::Limit, "Execution state allocation exceeds limits");
    } catch (const std::exception& e) {
        return fail(error, save::ErrorCode::InvalidState, e.what());
    }
}
template<class T, class H> const T* at(const std::vector<T>& values, H h) {
    return h.slot && h.slot <= values.size() ? &values[h.slot - 1] : nullptr;
}

// New owned representation. Reference evidence: original block readers
// FUN_00460330 / 004606f4 / 00460afc / 00460f90 and the physical save codec.
// This does NOT perform the later LoadGame campaign/AI/visibility normalizations.
bool buildGraph(const save::Document& d, Graph& graph, save::Error& error) {
    std::unordered_map<uint32_t, BuildingHandle> buildings;
    std::unordered_map<uint32_t, ArmyHandle> armies;
    for (size_t i = 0; i < d.buildings.size(); ++i) buildings.emplace(d.buildings[i].id, BuildingHandle{uint32_t(i + 1)});
    for (size_t i = 0; i < d.armies.size(); ++i) armies.emplace(d.armies[i].id, ArmyHandle{uint32_t(i + 1)});
    const auto bRef = [&](uint32_t id) { return id ? buildings.at(id) : BuildingHandle{}; };
    const auto aRef = [&](uint32_t id) { return id ? armies.at(id) : ArmyHandle{}; };
    graph.buildings.resize(d.buildings.size());
    graph.armies.resize(d.armies.size());
    graph.territories.resize(d.territories.size());
    graph.queues.reserve(d.territories.size() * 5);
    for (size_t i = 0; i < d.territories.size(); ++i) {
        const auto& record = d.territories[i]; const auto& t = record.data;
        auto& resolved = graph.territories[i];
        if (t.owner < -1 || t.owner >= kMaxPlayers)
            return fail(error, save::ErrorCode::InvalidState, "Execution territory owner is outside -1..6");
        if (t.owner >= 0) graph.playerTerritories[size_t(t.owner)].push_back({uint32_t(i + 1)});
        resolved.savedOwnHead = aRef(t.armies.raw);
        resolved.savedForeignHead = aRef(t.foreignArmies.raw);
        for (size_t k = 0; k < t.numTiles; ++k) {
            const auto xy = t.tiles[k].raw;
            // (0,0) is a valid file coordinate, never a null tile reference.
            resolved.tiles.push_back({1u + (xy >> 16) * d.world.width + (xy & 0xffffu)});
        }
        for (size_t s = 0; s < kNumSites; ++s) resolved.sites[s] = bRef(t.sites[s].building.raw);
        for (uint32_t other = 1; other <= d.world.numTerritories; ++other)
            if (t.adjacency[other >> 4] & (1u << (other & 15))) resolved.adjacent.push_back({other});
        for (size_t q = 0; q < 5; ++q) {
            const auto& records = record.queues[q];
            Queue queue;
            queue.count = uint32_t(records.size());
            if (!records.empty()) queue.first = queue.cursor = {uint32_t(graph.queueNodes.size() + 1)};
            for (size_t n = 0; n < records.size(); ++n) {
                QueueNode node;
                node.record = records[n]; node.record.next.raw = 0;
                if (n + 1 < records.size()) node.next = {uint32_t(graph.queueNodes.size() + 2)};
                graph.queueNodes.push_back(node);
            }
            resolved.queues[q] = {uint32_t(graph.queues.size() + 1)};
            graph.queues.push_back(queue);
        }
    }
    for (size_t i = 0; i < d.buildings.size(); ++i) {
        const auto& b = d.buildings[i];
        graph.buildings[i] = {{uint32_t(b.territory)}, bRef(b.prev.raw), bRef(b.next.raw)};
        graph.territories[size_t(b.territory) - 1].buildings.push_back({uint32_t(i + 1)});
    }
    for (size_t i = 0; i < d.armies.size(); ++i) {
        const auto& a = d.armies[i]; auto& resolved = graph.armies[i];
        // ReLinkArmy (00445898) writes +0x3c; the legacy field name `dest` is
        // misleading. +0x38 is the turn-start/base location, NOT current position.
        resolved.current = {army::current(a)}; resolved.turnStart = {army::turnStart(a)};
        resolved.routeOrigin = {army::routeOrigin(a)};
        resolved.previous = aRef(a.prev.raw); resolved.next = aRef(a.next.raw);
        for (size_t c = 0; c < 3; ++c) resolved.cargo[c] = aRef(a.cargo[c].raw);
        graph.territories[army::current(a) - 1].armies.push_back({uint32_t(i + 1)});
    }
    for (size_t p = 0; p < kMaxPlayers; ++p) {
        const auto& records = d.ministerJobs[p];
        const auto first = uint32_t(graph.ministers.size() + 1);
        graph.ministerHeads[p] = records.empty() ? MinisterHandle{} : MinisterHandle{first};
        for (size_t n = 0; n < records.size(); ++n) {
            MinisterNode node;
            node.player = int(p); node.recordIndex = uint32_t(n);
            if (n) node.previous = {first + uint32_t(n) - 1};
            if (n + 1 < records.size()) node.next = {first + uint32_t(n) + 1};
            graph.ministers.push_back(node);
        }
        for (size_t j = 0; j < kJobsPerPlayer; ++j) {
            const auto& job = d.jobs[p][j]; auto& resolved = graph.jobs[p][j];
            resolved.destination = {job.destination.raw};
            for (size_t n = 0; n < 16; ++n) resolved.armies[n] = aRef(job.armyIds[n]);
        }
    }
    return true;
}
}

State::State(State&& other) noexcept { *this = std::move(other); }
State& State::operator=(State&& other) noexcept {
    if (this != &other) {
        document_ = std::move(other.document_);
        graph_ = std::move(other.graph_);
        stage_ = std::exchange(other.stage_, Stage::Empty);
        other.graph_ = {};
    }
    return *this;
}

bool State::prepare(const save::Document& source, save::Error& error) {
    return guarded([&] {
        if (!save::validate(source, error)) return false;
        if (source.header.isMap)
            return fail(error, save::ErrorCode::InvalidState, "Execution preparation requires a saved game, not a map");
        State candidate;
        candidate.document_ = std::make_unique<save::Document>(source);
        if (!buildGraph(*candidate.document_, candidate.graph_, error)) return false;
        candidate.stage_ = Stage::Prepared;
        // Unique-owned document + handle graph move together only after success.
        *this = std::move(candidate);
        error = {}; return true;
    }, error);
}

bool State::capture(save::Document& destination, save::Error& error) const {
    return guarded([&] {
        if (!document_ || stage_ != Stage::Prepared)
            return fail(error, save::ErrorCode::InvalidState,
                        "Only a prepared snapshot can be saved; an incomplete turn is not resumable");
        save::Document candidate = *document_;
        if (!save::validate(candidate, error)) return false;
        destination = std::move(candidate);
        error = {}; return true;
    }, error);
}

bool State::collectTaxes(simulation::TaxPlan& report, save::Error& error) {
    return guarded([&] {
        if (!document_ || stage_ != Stage::Prepared)
            return fail(error, save::ErrorCode::InvalidState, "Taxes require a prepared state and can run only once");
        simulation::TaxPlan candidate;
        if (!simulation::planTaxes(*document_, candidate, error)) return false;
        // The phase writes exactly these seven scalar fields. All allocations
        // and possible failures finish before the first persistent write.
        report = std::move(candidate);
        for (size_t p = 0; p < kMaxPlayers; ++p) document_->players[p].credits = report.creditsAfter[p];
        stage_ = Stage::TaxesApplied;
        error = {}; return true;
    }, error);
}

bool State::advanceTurn(save::Error& error) {
    return fail(error, save::ErrorCode::InvalidState,
                "Full turn unavailable: movement/combat, production/logistics, food/energy, upkeep, "
                "population/research, events and AI/campaign normalization are not integrated");
}

BuildingHandle State::buildingById(uint32_t id) const {
    if (document_ && id) for (size_t i = 0; i < document_->buildings.size(); ++i)
        if (document_->buildings[i].id == id) return {uint32_t(i + 1)};
    return {};
}
ArmyHandle State::armyById(uint32_t id) const {
    if (document_ && id) for (size_t i = 0; i < document_->armies.size(); ++i)
        if (document_->armies[i].id == id) return {uint32_t(i + 1)};
    return {};
}
const Building* State::building(BuildingHandle h) const { return document_ ? at(document_->buildings, h) : nullptr; }
const Army* State::army(ArmyHandle h) const { return document_ ? at(document_->armies, h) : nullptr; }
const save::TerritoryRecord* State::territory(TerritoryHandle h) const { return document_ ? at(document_->territories, h) : nullptr; }
const Tile* State::tile(TileHandle h) const { return document_ ? at(document_->tiles, h) : nullptr; }
const Queue* State::queue(QueueHandle h) const { return at(graph_.queues, h); }
const QueueNode* State::queueNode(QueueNodeHandle h) const { return at(graph_.queueNodes, h); }
const MinisterNode* State::minister(MinisterHandle h) const { return at(graph_.ministers, h); }
} // namespace dl2::runtime
