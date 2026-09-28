#include "game/runtime_state.h"
#include "game/army_state.h"
#include "game/data_tables.h"
#include <algorithm>
#include <atomic>
#include <exception>
#include <limits>
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
template<class T, class H> const T* at(const std::vector<T>& values, H h, uint64_t owner) {
    return h && h.identity == owner && h.slot <= values.size() ? &values[h.slot - 1] : nullptr;
}
// Process-local identity allocator only: not gameplay state, a file/global ID,
// RNG, or an ordering input to any rule. Failed transactions may consume tokens.
// Saturation is an explicit failure; wrapping would resurrect stale handles.
bool newIdentity(uint64_t& destination, save::Error& error) {
    static std::atomic<uint64_t> next{1};
    auto value = next.load(std::memory_order_relaxed);
    while (value != std::numeric_limits<uint64_t>::max()) {
        if (next.compare_exchange_weak(value, value + 1, std::memory_order_relaxed)) {
            destination = value; return true;
        }
    }
    return fail(error, save::ErrorCode::Limit, "Runtime handle identities exhausted");
}
template<class Slots, class H> uint32_t denseIndex(const Slots& slots, H h) {
    if (!h || h.slot > slots.size() || slots[h.slot - 1].identity != h.identity)
        return std::numeric_limits<uint32_t>::max();
    return slots[h.slot - 1].denseIndex;
}
template<class Slots, class Dense> bool allocateSlot(Slots& slots, Dense& dense, save::Error& error) {
    uint64_t identity;
    if (!newIdentity(identity, error)) return false;
    uint32_t slot = 0;
    for (; slot < slots.size(); ++slot) if (!slots[slot].identity) break;
    if (slot == slots.size()) slots.push_back({});
    slots[slot] = {identity, uint32_t(dense.size())};
    dense.push_back(slot + 1);
    return true;
}
template<class Slots, class Dense> void retireSlot(Slots& slots, Dense& dense, uint32_t index) {
    slots[dense[index] - 1] = {};
    dense.erase(dense.begin() + index);
    for (uint32_t i = index; i < dense.size(); ++i) slots[dense[i] - 1].denseIndex = i;
}

// New owned representation. Reference evidence: original block readers
// FUN_00460330 / 004606f4 / 00460afc / 00460f90 and the physical save codec.
// This does NOT perform the later LoadGame campaign/AI/visibility normalizations.
bool buildGraph(const save::Document& d, Graph& graph,
                const std::vector<BuildingHandle>& buildingHandles,
                const std::vector<ArmyHandle>& armyHandles,
                uint64_t preparationIdentity, save::Error& error) {
    std::unordered_map<uint32_t, BuildingHandle> buildings;
    std::unordered_map<uint32_t, ArmyHandle> armies;
    for (size_t i = 0; i < d.buildings.size(); ++i) buildings.emplace(d.buildings[i].id, buildingHandles[i]);
    for (size_t i = 0; i < d.armies.size(); ++i) armies.emplace(d.armies[i].id, armyHandles[i]);
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
        if (t.owner >= 0) graph.playerTerritories[size_t(t.owner)].push_back({uint32_t(i + 1), preparationIdentity});
        resolved.savedOwnHead = aRef(t.armies.raw);
        resolved.savedForeignHead = aRef(t.foreignArmies.raw);
        for (size_t k = 0; k < t.numTiles; ++k) {
            const auto xy = t.tiles[k].raw;
            // (0,0) is a valid file coordinate, never a null tile reference.
            resolved.tiles.push_back({1u + (xy >> 16) * d.world.width + (xy & 0xffffu), preparationIdentity});
        }
        for (size_t s = 0; s < kNumSites; ++s) resolved.sites[s] = bRef(t.sites[s].building.raw);
        for (uint32_t other = 1; other <= d.world.numTerritories; ++other)
            if (t.adjacency[other >> 4] & (1u << (other & 15))) resolved.adjacent.push_back({other, preparationIdentity});
        for (size_t q = 0; q < 5; ++q) {
            const auto& records = record.queues[q];
            Queue queue;
            queue.count = uint32_t(records.size());
            if (!records.empty()) queue.first = queue.cursor = {uint32_t(graph.queueNodes.size() + 1), preparationIdentity};
            for (size_t n = 0; n < records.size(); ++n) {
                QueueNode node;
                node.record = records[n]; node.record.next.raw = 0;
                if (n + 1 < records.size()) node.next = {uint32_t(graph.queueNodes.size() + 2), preparationIdentity};
                graph.queueNodes.push_back(node);
            }
            resolved.queues[q] = {uint32_t(graph.queues.size() + 1), preparationIdentity};
            graph.queues.push_back(queue);
        }
    }
    for (size_t i = 0; i < d.buildings.size(); ++i) {
        const auto& b = d.buildings[i];
        graph.buildings[i] = {{uint32_t(b.territory), preparationIdentity}, bRef(b.prev.raw), bRef(b.next.raw)};
        graph.territories[size_t(b.territory) - 1].buildings.push_back(buildingHandles[i]);
    }
    for (size_t i = 0; i < d.armies.size(); ++i) {
        const auto& a = d.armies[i]; auto& resolved = graph.armies[i];
        // ReLinkArmy (00445898) writes +0x3c; the legacy field name `dest` is
        // misleading. +0x38 is the turn-start/base location, NOT current position.
        resolved.current = {army::current(a), preparationIdentity}; resolved.turnStart = {army::turnStart(a), preparationIdentity};
        resolved.routeOrigin = {army::routeOrigin(a), preparationIdentity};
        resolved.previous = aRef(a.prev.raw); resolved.next = aRef(a.next.raw);
        for (size_t c = 0; c < 3; ++c) resolved.cargo[c] = aRef(a.cargo[c].raw);
        graph.territories[army::current(a) - 1].armies.push_back(armyHandles[i]);
    }
    for (size_t p = 0; p < kMaxPlayers; ++p) {
        const auto& records = d.ministerJobs[p];
        const auto first = uint32_t(graph.ministers.size() + 1);
        graph.ministerHeads[p] = records.empty() ? MinisterHandle{} : MinisterHandle{first, preparationIdentity};
        for (size_t n = 0; n < records.size(); ++n) {
            MinisterNode node;
            node.player = int(p); node.recordIndex = uint32_t(n);
            if (n) node.previous = {first + uint32_t(n) - 1, preparationIdentity};
            if (n + 1 < records.size()) node.next = {first + uint32_t(n) + 1, preparationIdentity};
            graph.ministers.push_back(node);
        }
        for (size_t j = 0; j < kJobsPerPlayer; ++j) {
            const auto& job = d.jobs[p][j]; auto& resolved = graph.jobs[p][j];
            if (job.destination.raw) resolved.destination = {job.destination.raw, preparationIdentity};
            for (size_t n = 0; n < 16; ++n) resolved.armies[n] = aRef(job.armyIds[n]);
        }
    }
    return true;
}

Building* mutableBuilding(save::Document& d, uint32_t id) {
    for (auto& value : d.buildings) if (value.id == id) return &value;
    return nullptr;
}
Army* mutableArmy(save::Document& d, uint32_t id) {
    for (auto& value : d.armies) if (value.id == id) return &value;
    return nullptr;
}

// These stronger checks belong to the mutation domain, not the archival codec
// or prepare: old historical lists may be inspectable without being editable.
bool buildingList(const save::Document& d, uint32_t& tail, save::Error& error) {
    tail = 0;
    if (d.buildings.empty()) return true;
    const Building* head = nullptr;
    for (const auto& b : d.buildings) if (!b.prev.raw) {
        if (head) return fail(error, save::ErrorCode::InvalidState, "Structural building edit requires one coherent active list");
        head = &b;
    }
    size_t count = 0;
    for (const Building* b = head; b; b = d.buildingById(b->next.raw)) {
        if (++count > d.buildings.size() || b->prev.raw != tail)
            return fail(error, save::ErrorCode::InvalidState, "Structural building edit found a nonreciprocal or cyclic active list");
        tail = b->id;
    }
    if (count != d.buildings.size())
        return fail(error, save::ErrorCode::InvalidState, "Structural building edit found disconnected active-list records");
    return true;
}

// Validate exactly the list that will change, including incoming list edges.
// Its canonical membership must use current +0x3c, never turn-start +0x38.
bool armyList(const save::Document& d, uint32_t territory, bool own, save::Error& error) {
    const auto& t = d.territories[territory - 1].data;
    const uint32_t head = own ? t.armies.raw : t.foreignArmies.raw;
    std::vector<uint32_t> members;
    uint32_t previous = 0;
    for (const Army* a = d.armyById(head); a; a = d.armyById(a->next.raw)) {
        if (members.size() >= d.armies.size() || a->prev.raw != previous ||
            army::current(*a) != territory || ((a->owner == t.owner) != own))
            return fail(error, save::ErrorCode::InvalidState, "Structural army edit requires a coherent current-territory list");
        members.push_back(a->id); previous = a->id;
    }
    const auto member = [&](uint32_t id) {
        return id && std::find(members.begin(), members.end(), id) != members.end();
    };
    for (const auto& a : d.armies) {
        const bool present = member(a.id);
        if ((army::current(a) == territory && ((a.owner == t.owner) == own)) != present)
            return fail(error, save::ErrorCode::InvalidState, "Structural army edit found incomplete current-territory membership");
        if (!present && (member(a.prev.raw) || member(a.next.raw)))
            return fail(error, save::ErrorCode::InvalidState, "Structural army edit found list links from another list");
    }
    for (const auto& record : d.territories) {
        const auto& other = record.data;
        if ((other.index != territory || !own) && member(other.armies.raw))
            return fail(error, save::ErrorCode::InvalidState, "Structural army edit found another owning-list head");
        if ((other.index != territory || own) && member(other.foreignArmies.raw))
            return fail(error, save::ErrorCode::InvalidState, "Structural army edit found another foreign-list head");
    }
    return true;
}

bool simpleBuilding(const save::Document& d, const Building& b, save::Error& error) {
    if (!b.id || !b.type || b.type >= data::kNumBuildingTypes ||
        b.territory < 1 || size_t(b.territory) > d.territories.size() || b.site < 0 || b.site >= kNumSites)
        return fail(error, save::ErrorCode::InvalidState, "Structural building edit has an invalid ID, type or location");
    const auto& definition = data::kBuildingTypes[b.type];
    const auto flags = d.territories[size_t(b.territory) - 1].data.sites[size_t(b.site)].terrainFlags;
    // Placement/deletion 0044d7b4 / 0044cd50 have extra footprint/platform
    // effects. This backend edits only an ordinary one-site anchor reference;
    // even its ordinary 0x3000 occupancy flags remain outside this operation.
    if (definition.size != 1 || b.type == 38 || b.type == 39 ||
        definition.category == 11 || b.category == 11 ||
        (flags & 0x0f00u) == 0x0100u || (flags & 0x0f00u) == 0x0200u)
        return fail(error, save::ErrorCode::InvalidState, "Structural building edit does not support special footprints, platforms or shrines");
    if (b.minister != 0)
        return fail(error, save::ErrorCode::InvalidState, "Structural building edit does not support minister-managed records");
    // DebugJobsDialog 00405d54 case 3 resolves BUILD_BLDG by location,
    // NOT by a global building ID. Insertion there would also retarget the job.
    for (const auto& list : d.ministerJobs) for (const auto& job : list)
        if (job.type == 3 && job.param[0] == b.territory && job.param[1] == b.site)
            return fail(error, save::ErrorCode::InvalidState, "Structural building edit is referenced by a BUILD_BLDG minister job");
    return true;
}

bool simpleArmy(const save::Document& d, const Army& a, bool inserting, save::Error& error) {
    if (!a.id || !a.type || a.type >= data::kNumUnitTypes || a.owner < 0 || a.owner >= kMaxPlayers || a.health > 100)
        return fail(error, save::ErrorCode::InvalidState, "Structural army edit has an invalid ID, type, owner or retreat threshold");
    for (const auto t : {army::current(a), army::turnStart(a), army::routeOrigin(a)})
        if (!t || t > d.territories.size())
            return fail(error, save::ErrorCode::InvalidState, "Structural army edit has an invalid territory reference");
    const auto& definition = data::kUnitTypes[a.type];
    // DeleteUnit 00445fd4 recursively removes class 4/19 cargo; creation
    // 00445d30 may create the 35/36 siege pair or board a land unit at sea.
    if (a.unitClass == 4 || a.unitClass == 19 || definition.unitClass == 4 || definition.unitClass == 19 ||
        a.type == 35 || a.type == 36 || a.job || a.cargo[0].raw || a.cargo[1].raw || a.cargo[2].raw)
        return fail(error, save::ErrorCode::InvalidState, "Structural army edit does not support transport, siege-pair or task-force dependencies");
    const auto terrain = d.territories[army::current(a) - 1].data.terrain;
    if (inserting && ((terrain == 0 && definition.domain == data::kDomainLand) ||
                      (terrain != 0 && definition.domain == data::kDomainSea)))
        return fail(error, save::ErrorCode::InvalidState, "Structural army insertion does not support land boarding at sea or naval units on land");
    return true;
}
}

State::State(State&& other) noexcept { *this = std::move(other); }
State& State::operator=(State&& other) noexcept {
    if (this != &other) {
        buildingSlots_ = std::move(other.buildingSlots_);
        armySlots_ = std::move(other.armySlots_);
        buildingDenseSlots_ = std::move(other.buildingDenseSlots_);
        armyDenseSlots_ = std::move(other.armyDenseSlots_);
        preparationIdentity_ = std::exchange(other.preparationIdentity_, 0);
        document_ = std::move(other.document_);
        graph_ = std::move(other.graph_);
        stage_ = std::exchange(other.stage_, Stage::Empty);
        other.graph_ = {};
        other.buildingSlots_.clear(); other.armySlots_.clear();
        other.buildingDenseSlots_.clear(); other.armyDenseSlots_.clear();
    }
    return *this;
}

bool State::rebuildGraph(save::Error& error) {
    std::vector<BuildingHandle> buildings;
    std::vector<ArmyHandle> armies;
    buildings.reserve(buildingDenseSlots_.size());
    armies.reserve(armyDenseSlots_.size());
    for (const auto slot : buildingDenseSlots_) buildings.push_back({slot, buildingSlots_[slot - 1].identity});
    for (const auto slot : armyDenseSlots_) armies.push_back({slot, armySlots_[slot - 1].identity});
    Graph candidate;
    if (!buildGraph(*document_, candidate, buildings, armies, preparationIdentity_, error)) return false;
    graph_ = std::move(candidate);
    return true;
}

bool State::copyForEdit(State& candidate, save::Error& error) const {
    if (!document_ || (stage_ != Stage::Prepared && stage_ != Stage::EntitiesEdited))
        return fail(error, save::ErrorCode::InvalidState, "Structural entity edits require a prepared or structurally edited state");
    candidate.document_ = std::make_unique<save::Document>(*document_);
    candidate.buildingSlots_ = buildingSlots_; candidate.armySlots_ = armySlots_;
    candidate.buildingDenseSlots_ = buildingDenseSlots_; candidate.armyDenseSlots_ = armyDenseSlots_;
    candidate.preparationIdentity_ = preparationIdentity_;
    return true;
}

bool State::finishEdit(State&& candidate, save::Error& error) {
    if (!save::validate(*candidate.document_, error) || !candidate.rebuildGraph(error)) return false;
    candidate.stage_ = Stage::EntitiesEdited;
    *this = std::move(candidate);
    error = {};
    return true;
}

bool State::prepare(const save::Document& source, save::Error& error) {
    return guarded([&] {
        if (!save::validate(source, error)) return false;
        if (source.header.isMap)
            return fail(error, save::ErrorCode::InvalidState, "Execution preparation requires a saved game, not a map");
        State candidate;
        candidate.document_ = std::make_unique<save::Document>(source);
        if (!newIdentity(candidate.preparationIdentity_, error)) return false;
        for (size_t i = 0; i < source.buildings.size(); ++i)
            if (!allocateSlot(candidate.buildingSlots_, candidate.buildingDenseSlots_, error)) return false;
        for (size_t i = 0; i < source.armies.size(); ++i)
            if (!allocateSlot(candidate.armySlots_, candidate.armyDenseSlots_, error)) return false;
        if (!candidate.rebuildGraph(error)) return false;
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

bool State::consumeEnergy(simulation::EnergyPlan& report, save::Error& error) {
    return guarded([&] {
        if (!document_ || stage_ != Stage::Prepared)
            return fail(error, save::ErrorCode::InvalidState,
                        "Isolated energy consumption requires a fresh prepared state; omitted phases cannot be chained");
        simulation::EnergyPlan candidate;
        if (!simulation::planEnergy(*document_, candidate, error)) return false;
        // All validation/allocation precedes the first write. The full report
        // owns shortage events; do not invent legacy event text or AI callbacks.
        report = std::move(candidate);
        for (const auto& result : report.territories) {
            auto& territory = document_->territories[result.territory - 1].data;
            territory.materials[2] = result.energyAfter;
            territory.knowledge = result.energyPercentAfter;
        }
        stage_ = Stage::EnergyApplied;
        error = {}; return true;
    }, error);
}

bool State::normalizeLabor(simulation::LaborBalancePlan& report, save::Error& error) {
    return guarded([&] {
        if (!document_ || stage_ != Stage::Prepared)
            return fail(error, save::ErrorCode::InvalidState,
                        "Labor normalization requires a fresh prepared state; full load/turn phases are not integrated");
        simulation::LaborBalancePlan candidate;
        if (!simulation::planLaborBalance(*document_, candidate, error)) return false;
        // The planner returns every building in document order. No identities,
        // locations or queue links change, so the existing typed graph stays valid.
        // All allocations and validation precede this no-throw scalar commit.
        report = std::move(candidate);
        for (size_t i = 0; i < report.buildings.size(); ++i) {
            auto& building = document_->buildings[i];
            const auto& after = report.buildings[i].after;
            building.flags = after.flags;
            for (size_t slot = 0; slot < 5; ++slot) {
                building.task[slot] = after.tasks[slot];
                building.labor[slot] = after.labor[slot];
            }
        }
        for (size_t i = 0; i < report.territories.size(); ++i) {
            auto& territory = document_->territories[i].data;
            const auto& after = report.territories[i];
            territory.morale = after.moraleAfter;
            for (size_t material = 0; material < kNumMaterials; ++material)
                territory.materials[material] = after.materialsAfter[material];
        }
        stage_ = Stage::LaborBalanced;
        error = {}; return true;
    }, error);
}

bool State::insertBuilding(const Building& record, BuildingHandle& created,
                           EntityEditReport& report, save::Error& error) {
    return guarded([&] {
        if (!document_ || (stage_ != Stage::Prepared && stage_ != Stage::EntitiesEdited))
            return fail(error, save::ErrorCode::InvalidState, "Structural building insertion requires a prepared or structurally edited state");
        Building value = record; // record may be borrowed from this State.
        if (!simpleBuilding(*document_, value, error)) return false;
        if (document_->buildings.size() >= kMaxBuildings - 1)
            return fail(error, save::ErrorCode::Limit, "Structural building insertion requires one reserved free pool slot");
        if (document_->buildingById(value.id) || value.prev.raw || value.next.raw)
            return fail(error, save::ErrorCode::InvalidState, "Structural building insertion requires an unused ID and detached list links");
        if (document_->territories[size_t(value.territory) - 1].data.sites[size_t(value.site)].building.raw)
            return fail(error, save::ErrorCode::InvalidState, "Structural building insertion requires an empty anchor site");
        uint32_t tail;
        if (!buildingList(*document_, tail, error)) return false;
        State candidate;
        if (!copyForEdit(candidate, error)) return false;
        auto& d = *candidate.document_;
        // AllocBuilding 0044cbec appends to the active tail. Native free-list
        // addresses/order are intentionally replaced by an owned slot registry.
        value.prev.raw = tail;
        if (tail) mutableBuilding(d, tail)->next.raw = value.id;
        d.territories[size_t(value.territory) - 1].data.sites[size_t(value.site)].building.raw = value.id;
        const auto count = uint32_t(d.buildings.size());
        d.buildings.push_back(value);
        if (!allocateSlot(candidate.buildingSlots_, candidate.buildingDenseSlots_, error)) return false;
        const auto slot = candidate.buildingDenseSlots_.back();
        const BuildingHandle result{slot, candidate.buildingSlots_[slot - 1].identity};
        const EntityEditReport outcome{EntityKind::Building, EntityEditOperation::Inserted,
            value.id, uint32_t(value.territory), value.site, count, count + 1, tail, 0};
        if (!finishEdit(std::move(candidate), error)) return false;
        created = result; report = outcome;
        return true;
    }, error);
}

bool State::retireBuilding(BuildingHandle handle, EntityEditReport& report, save::Error& error) {
    return guarded([&] {
        const Building* found = building(handle);
        if (!found) return fail(error, save::ErrorCode::InvalidState, "Structural building retirement received a null, stale or foreign handle");
        const Building value = *found;
        if (!simpleBuilding(*document_, value, error)) return false;
        uint32_t tail;
        if (!buildingList(*document_, tail, error)) return false;
        State candidate;
        if (!copyForEdit(candidate, error)) return false;
        auto& d = *candidate.document_;
        const auto index = denseIndex(candidate.buildingSlots_, handle);
        const auto count = uint32_t(d.buildings.size());
        // FreeBuilding 0044cc40 splices both neighbors; unlike _DeleteBuilding,
        // this operation does NOT clear terrain occupancy, roads or platforms.
        if (value.prev.raw) mutableBuilding(d, value.prev.raw)->next.raw = value.next.raw;
        if (value.next.raw) mutableBuilding(d, value.next.raw)->prev.raw = value.prev.raw;
        d.territories[size_t(value.territory) - 1].data.sites[size_t(value.site)].building.raw = 0;
        d.buildings.erase(d.buildings.begin() + index);
        retireSlot(candidate.buildingSlots_, candidate.buildingDenseSlots_, index);
        const EntityEditReport outcome{EntityKind::Building, EntityEditOperation::Retired,
            value.id, uint32_t(value.territory), value.site, count, count - 1, value.prev.raw, value.next.raw};
        if (!finishEdit(std::move(candidate), error)) return false;
        report = outcome;
        return true;
    }, error);
}

bool State::insertArmy(const Army& record, ArmyHandle& created,
                       EntityEditReport& report, save::Error& error) {
    return guarded([&] {
        if (!document_ || (stage_ != Stage::Prepared && stage_ != Stage::EntitiesEdited))
            return fail(error, save::ErrorCode::InvalidState, "Structural army insertion requires a prepared or structurally edited state");
        Army value = record;
        if (!simpleArmy(*document_, value, true, error)) return false;
        if (document_->armies.size() >= kMaxArmies - 1)
            return fail(error, save::ErrorCode::Limit, "Structural army insertion requires one reserved free pool slot");
        if (document_->armyById(value.id) || value.prev.raw || value.next.raw)
            return fail(error, save::ErrorCode::InvalidState, "Structural army insertion requires an unused ID and detached list links");
        const auto territory = army::current(value);
        const bool own = value.owner == document_->territories[territory - 1].data.owner;
        if (!armyList(*document_, territory, own, error)) return false;
        // A saved minister reference to an absent ID must not silently bind to
        // a newly inserted army. Same precise known reference as retirement.
        for (const auto& list : document_->ministerJobs) for (const auto& job : list)
            if (job.type == 13 && job.param[0] == value.id)
                return fail(error, save::ErrorCode::InvalidState, "Structural army insertion ID is referenced by a MAINTAIN_UNIT minister job");
        State candidate;
        if (!copyForEdit(candidate, error)) return false;
        auto& d = *candidate.document_;
        auto& t = d.territories[territory - 1].data;
        auto& head = own ? t.armies : t.foreignArmies;
        // Allocation 0044577c / initialization 00445d30 prepend to the selected
        // owning/foreign head; full creation's other effects remain unsupported.
        value.next.raw = head.raw;
        if (head.raw) mutableArmy(d, head.raw)->prev.raw = value.id;
        head.raw = value.id;
        const auto count = uint32_t(d.armies.size());
        d.armies.push_back(value);
        if (!allocateSlot(candidate.armySlots_, candidate.armyDenseSlots_, error)) return false;
        const auto slot = candidate.armyDenseSlots_.back();
        const ArmyHandle result{slot, candidate.armySlots_[slot - 1].identity};
        const EntityEditReport outcome{EntityKind::Army, EntityEditOperation::Inserted,
            value.id, territory, -1, count, count + 1, 0, value.next.raw};
        if (!finishEdit(std::move(candidate), error)) return false;
        created = result; report = outcome;
        return true;
    }, error);
}

bool State::retireArmy(ArmyHandle handle, EntityEditReport& report, save::Error& error) {
    return guarded([&] {
        const Army* found = army(handle);
        if (!found) return fail(error, save::ErrorCode::InvalidState, "Structural army retirement received a null, stale or foreign handle");
        const Army value = *found;
        if (!simpleArmy(*document_, value, false, error)) return false;
        for (const auto& other : document_->armies) for (const auto cargo : other.cargo)
            if (cargo.raw == value.id)
                return fail(error, save::ErrorCode::InvalidState, "Structural army retirement has an incoming cargo reference");
        for (const auto& jobs : document_->jobs) for (const auto& job : jobs) for (const auto id : job.armyIds)
            if (id == value.id)
                return fail(error, save::ErrorCode::InvalidState, "Structural army retirement is referenced by a task force");
        // DebugJobsDialog 00405d54 case 13: MAINTAIN_UNIT +0x1c is the global ID.
        for (const auto& list : document_->ministerJobs) for (const auto& job : list)
            if (job.type == 13 && job.param[0] == value.id)
                return fail(error, save::ErrorCode::InvalidState, "Structural army retirement is referenced by a MAINTAIN_UNIT minister job");
        const auto territory = army::current(value);
        const bool own = value.owner == document_->territories[territory - 1].data.owner;
        if (!armyList(*document_, territory, own, error)) return false;
        State candidate;
        if (!copyForEdit(candidate, error)) return false;
        auto& d = *candidate.document_;
        const auto index = denseIndex(candidate.armySlots_, handle);
        const auto count = uint32_t(d.armies.size());
        auto& t = d.territories[territory - 1].data;
        auto& head = own ? t.armies : t.foreignArmies;
        // DeleteArmy 00445800 list splice only; no DeleteUnit cargo cascade.
        if (value.prev.raw) mutableArmy(d, value.prev.raw)->next.raw = value.next.raw;
        if (value.next.raw) mutableArmy(d, value.next.raw)->prev.raw = value.prev.raw;
        if (head.raw == value.id) head.raw = value.next.raw;
        d.armies.erase(d.armies.begin() + index);
        retireSlot(candidate.armySlots_, candidate.armyDenseSlots_, index);
        const EntityEditReport outcome{EntityKind::Army, EntityEditOperation::Retired,
            value.id, territory, -1, count, count - 1, value.prev.raw, value.next.raw};
        if (!finishEdit(std::move(candidate), error)) return false;
        report = outcome;
        return true;
    }, error);
}

bool State::advanceTurn(save::Error& error) {
    return fail(error, save::ErrorCode::InvalidState,
                "Full turn unavailable: movement/combat, production/logistics, food/energy, upkeep, "
                "population/research, events and AI/campaign normalization are not integrated");
}

BuildingHandle State::buildingById(uint32_t id) const {
    if (document_ && id) for (size_t i = 0; i < document_->buildings.size(); ++i) {
        if (document_->buildings[i].id != id) continue;
        const auto slot = buildingDenseSlots_[i];
        return {slot, buildingSlots_[slot - 1].identity};
    }
    return {};
}
ArmyHandle State::armyById(uint32_t id) const {
    if (document_ && id) for (size_t i = 0; i < document_->armies.size(); ++i) {
        if (document_->armies[i].id != id) continue;
        const auto slot = armyDenseSlots_[i];
        return {slot, armySlots_[slot - 1].identity};
    }
    return {};
}
TerritoryHandle State::territoryByIndex(uint32_t index) const {
    return document_ && index && index <= document_->territories.size()
        ? TerritoryHandle{index, preparationIdentity_} : TerritoryHandle{};
}
TileHandle State::tileByIndex(uint32_t index) const {
    return document_ && index && index <= document_->tiles.size()
        ? TileHandle{index, preparationIdentity_} : TileHandle{};
}
const Building* State::building(BuildingHandle h) const {
    const auto index = denseIndex(buildingSlots_, h);
    return document_ && index < document_->buildings.size() ? &document_->buildings[index] : nullptr;
}
const Army* State::army(ArmyHandle h) const {
    const auto index = denseIndex(armySlots_, h);
    return document_ && index < document_->armies.size() ? &document_->armies[index] : nullptr;
}
const BuildingLinks* State::buildingLinks(BuildingHandle h) const {
    const auto index = denseIndex(buildingSlots_, h);
    return index < graph_.buildings.size() ? &graph_.buildings[index] : nullptr;
}
const ArmyLinks* State::armyLinks(ArmyHandle h) const {
    const auto index = denseIndex(armySlots_, h);
    return index < graph_.armies.size() ? &graph_.armies[index] : nullptr;
}
const save::TerritoryRecord* State::territory(TerritoryHandle h) const {
    return document_ ? at(document_->territories, h, preparationIdentity_) : nullptr;
}
const Tile* State::tile(TileHandle h) const { return document_ ? at(document_->tiles, h, preparationIdentity_) : nullptr; }
const Queue* State::queue(QueueHandle h) const { return at(graph_.queues, h, preparationIdentity_); }
const QueueNode* State::queueNode(QueueNodeHandle h) const { return at(graph_.queueNodes, h, preparationIdentity_); }
const MinisterNode* State::minister(MinisterHandle h) const { return at(graph_.ministers, h, preparationIdentity_); }
} // namespace dl2::runtime
