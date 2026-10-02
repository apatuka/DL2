#include "game/runtime_state.h"
#include "game/army_state.h"
#include "game/data_tables.h"
#include <algorithm>
#include <atomic>
#include <bit>
#include <cstring>
#include <exception>
#include <limits>
#include <new>
#include <stdexcept>
#include <string>
#include <type_traits>
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
                uint64_t preparationIdentity, uint64_t queueNodeIdentity, save::Error& error) {
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
            if (!records.empty()) queue.first = queue.cursor = {uint32_t(graph.queueNodes.size() + 1), queueNodeIdentity};
            for (size_t n = 0; n < records.size(); ++n) {
                QueueNode node;
                node.record = records[n]; node.record.next.raw = 0;
                if (n + 1 < records.size()) node.next = {uint32_t(graph.queueNodes.size() + 2), queueNodeIdentity};
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
        queueNodeIdentity_ = std::exchange(other.queueNodeIdentity_, 0);
        document_ = std::move(other.document_);
        graph_ = std::move(other.graph_);
        stage_ = std::exchange(other.stage_, Stage::Empty);
        rng_ = other.rng_;
        other.rng_ = {};
        core_ = std::move(other.core_); other.core_.reset();
        derived_ = std::move(other.derived_); other.derived_.reset();
        shrineEvents_ = std::move(other.shrineEvents_); other.shrineEvents_.reset();
        events_ = std::move(other.events_); other.events_.reset();
        timer_ = std::move(other.timer_); other.timer_.reset();
        startup_ = std::move(other.startup_);
        world_ = std::move(other.world_); other.world_.reset();
        ai_ = std::move(other.ai_); other.ai_.reset();
        aiReaction_ = std::move(other.aiReaction_); other.aiReaction_.reset();
        collection_ = std::move(other.collection_); other.collection_.reset();
        eventCities_ = std::move(other.eventCities_); other.eventCities_.reset();
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
    if (!buildGraph(*document_, candidate, buildings, armies, preparationIdentity_, queueNodeIdentity_, error)) return false;
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
    candidate.queueNodeIdentity_ = queueNodeIdentity_;
    candidate.rng_ = rng_;
    candidate.core_ = core_; candidate.events_ = events_; candidate.timer_ = timer_;
    candidate.derived_ = derived_;
    candidate.shrineEvents_ = shrineEvents_;
    if (startup_) candidate.startup_ = std::make_unique<simulation::LoadStartupReport>(*startup_);
    candidate.world_ = world_; candidate.ai_ = ai_; candidate.aiReaction_ = aiReaction_;
    candidate.collection_ = collection_;
    candidate.eventCities_ = eventCities_;
    return true;
}

bool State::finishEdit(State&& candidate, save::Error& error, bool queueNodesReplaced) {
    // Nodes are positional, unlike stable entity registries. Never let an old
    // handle silently resolve to another item after erase/reinsert/append. A
    // rejected transaction consumes at most an internal token, not live handles.
    bool queuesChanged = queueNodesReplaced || document_->territories.size() != candidate.document_->territories.size();
    for (size_t t = 0; !queuesChanged && t < document_->territories.size(); ++t) {
        for (size_t q = 0; !queuesChanged && q < 5; ++q) {
            const auto& before = document_->territories[t].queues[q];
            const auto& after = candidate.document_->territories[t].queues[q];
            queuesChanged = before.size() != after.size();
            for (size_t n = 0; !queuesChanged && n < before.size(); ++n)
                queuesChanged = std::memcmp(&before[n], &after[n], kQueueRecordSaved) != 0;
        }
    }
    if (queuesChanged && !newIdentity(candidate.queueNodeIdentity_, error)) return false;
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
        candidate.queueNodeIdentity_ = candidate.preparationIdentity_;
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

const char* missingLoadCapabilityName(MissingLoadCapability capability) {
    switch (capability) {
    case MissingLoadCapability::AiInitialization: return "ai_initialization";
    case MissingLoadCapability::Visibility: return "visibility";
    case MissingLoadCapability::Contacts: return "contacts";
    case MissingLoadCapability::BuildingIntelligence: return "building_intelligence";
    case MissingLoadCapability::NativeEventLog: return "native_event_log";
    case MissingLoadCapability::TransientSessionState: return "transient_session_state";
    case MissingLoadCapability::ChangedWorldScan: return "changed_world_scan";
    case MissingLoadCapability::AiExecution: return "ai_execution";
    case MissingLoadCapability::NativePresentation: return "native_presentation";
    case MissingLoadCapability::ShrineEventDelivery: return "shrine_event_delivery";
    }
    return "unknown";
}

bool State::normalizeLoad(const simulation::LoadProfile& profile, LoadReport& report,
                          save::Error& error, LoadScope scope, const LoadContext& context) {
    return guarded([&] {
        if (scope != LoadScope::Partial)
            return fail(error, save::ErrorCode::InvalidState,
                "Complete load activation unavailable: native presentation delivery and playable turn execution are not integrated; headless effects require explicit context");
        if (!document_ || stage_ != Stage::Prepared)
            return fail(error, save::ErrorCode::InvalidState, "Load normalization requires a fresh prepared snapshot");
        if (context.startup && context.events)
            return fail(error, save::ErrorCode::InvalidState, "Supply either pre-reset or pre-event RNG context, not both");
        State candidate;
        LoadReport result;
        if (!copyForEdit(candidate, error)) return false;
        auto& d = *candidate.document_;
        if (!simulation::normalizeLoadCore(d, profile, d, result.core, error)) return false;
        auto eventsContext = context.events;
        if (context.startup) {
            candidate.startup_ = std::make_unique<simulation::LoadStartupReport>();
            if (!simulation::planLoadStartup(d, *context.startup, *candidate.startup_, error)) return false;
            result.startupRebuilt = true;
            eventsContext = simulation::EventLoadContext{candidate.startup_->rngBeforeEvents, context.citiesBeforeLoad};
        }
        // LoadEventLog precedes CountShrines: special portraits compare prior
        // session city counts, not the counts rebuilt from this document later.
        if (eventsContext || d.events.empty()) {
            simulation::LoadedEventLog log;
            if (!simulation::rebuildLoadedEvents(d, eventsContext.value_or(simulation::EventLoadContext{}), log, error)) return false;
            result.eventsRebuilt = true; result.loadedEvents = uint32_t(log.entries.size());
            result.eventRandomDraws = uint32_t(log.randomDraws.size());
            result.evictedEvents = log.evictedEvents;
            std::erase(result.missing, MissingLoadCapability::NativeEventLog);
            candidate.events_ = std::move(log);
        }
        if (context.previousWorld) {
            if (!candidate.events_)
                return fail(error, save::ErrorCode::InvalidState, "Changed-world reconstruction requires the preceding event context");
            candidate.world_.emplace();
            simulation::LoadWorldPresentationContext worldContext{*context.previousWorld,
                candidate.events_->rngAfterEvents, context.previousShadingSlope};
            if (!simulation::rebuildLoadWorldPresentation(d, worldContext, d, *candidate.world_, error)) return false;
            result.worldPresentationRebuilt = true;
            std::erase(result.missing, MissingLoadCapability::ChangedWorldScan);
        }
        candidate.ai_.emplace();
        if (!candidate.ai_->initializeAfterLoad(d, error)) return false;
        result.aiInitialized = true;
        if (!simulation::rebuildLoadDerived(d, d, result.derived, error)) return false;
        const auto noticeRng = candidate.world_ ? candidate.world_->rngAfter :
            candidate.events_ ? candidate.events_->rngAfterEvents : simulation::RngSnapshot{};
        const bool requiresAi = std::any_of(result.derived.notices.begin(), result.derived.notices.end(), [&](const auto& notice) {
            return notice.recipient != d.options.localPlayer &&
                std::bit_cast<int8_t>(d.players[size_t(notice.recipient)].type) >= 3;
        });
        if (candidate.events_ && (!requiresAi || context.previousAi) &&
            (noticeRng.initialized || result.derived.notices.empty())) {
            candidate.shrineEvents_.emplace();
            auto previousAi = context.previousAi;
            if (previousAi) previousAi->gameAborted = false; // ResetVariables, before loaded notices.
            if (!simulation::replayLoadShrineEvents(d, result.derived, *candidate.ai_, *candidate.events_, noticeRng,
                previousAi, d, *candidate.shrineEvents_, error)) return false;
            candidate.events_ = candidate.shrineEvents_->logAfter;
            candidate.aiReaction_ = candidate.shrineEvents_->aiAfter;
            result.shrineNoticesDelivered = true;
            result.shrineRandomDraws = uint32_t(candidate.shrineEvents_->draws.size());
        } else if (result.derived.notices.empty()) result.shrineNoticesDelivered = true;
        if (result.shrineNoticesDelivered) std::erase(result.missing, MissingLoadCapability::ShrineEventDelivery);
        candidate.derived_ = result.derived;
        candidate.eventCities_ = result.derived.cities;
        if (!simulation::rebuildLoadIntelligence(d, context.intelligence, d, result.intelligence, error) ||
            !simulation::planLaborBalance(d, result.labor, error)) return false;
        for (size_t i = 0; i < result.labor.buildings.size(); ++i) {
            auto& b = d.buildings[i];
            const auto& after = result.labor.buildings[i].after;
            b.flags = after.flags;
            for (size_t slot = 0; slot < 5; ++slot) {
                b.task[slot] = after.tasks[slot]; b.labor[slot] = after.labor[slot];
            }
        }
        for (size_t i = 0; i < result.labor.territories.size(); ++i) {
            auto& t = d.territories[i].data;
            const auto& after = result.labor.territories[i];
            t.morale = after.moraleAfter;
            for (size_t m = 0; m < kNumMaterials; ++m) t.materials[m] = after.materialsAfter[m];
        }
        // orig: 004501b0, AFTER AfterMovePhase(load=1)/EndTurnBalance.
        // The fixed address 004fc4dc is tech[47].availableMask, NOT the
        // forbidden technology's mask. Preserve the original oddity.
        for (size_t p = 0; p < kMaxPlayers; ++p) if (result.core.forbiddenResearchPlayers & (1u << p)) {
            d.techs[47].availableMask &= uint16_t(~(1u << p));
            d.players[p].currentResearch = 0;
        }
        if (context.clockMs) {
            simulation::LoadTimerReport timer;
            if (!simulation::planLoadTimer(d, context.previousTimer, *context.clockMs, timer, error)) return false;
            result.timerPlanned = true; candidate.timer_ = timer;
        }
        if (result.startupRebuilt && result.timerPlanned)
            std::erase(result.missing, MissingLoadCapability::TransientSessionState);
        if (!candidate.rng_.initializeAfterLegacyLoad(d, error) ||
            !save::validate(d, error) || !candidate.rebuildGraph(error)) return false;
        result.rng = candidate.rng_.snapshot();
        if (candidate.aiReaction_) candidate.aiReaction_->rng = result.rng; // Final shared reseed, after notices.
        result.headlessComplete = std::all_of(result.missing.begin(), result.missing.end(), [](auto missing) {
            return missing == MissingLoadCapability::NativePresentation;
        });
        candidate.core_ = result.core;
        candidate.stage_ = Stage::LoadNormalized;
        // Everything that can allocate or reject precedes this no-throw commit.
        report = std::move(result);
        *this = std::move(candidate);
        error = {}; return true;
    }, error);
}

bool State::reactDiplomacy(const simulation::AiDiplomacyRequest& request,
                           const simulation::AiReactionContext& context,
                           simulation::AiReactionReport& report, save::Error& error) {
    return guarded([&] {
        if ((aiReaction_ && context != *aiReaction_) ||
            (rng_.snapshot().initialized && context.rng != rng_.snapshot()))
            return fail(error, save::ErrorCode::InvalidState, "AI reaction context differs from the owned continuation");
        State candidate;
        if (!copyForEdit(candidate, error)) return false;
        if (!candidate.ai_) {
            candidate.ai_.emplace();
            if (!candidate.ai_->initializeAfterLoad(*candidate.document_, error)) return false;
        }
        simulation::AiReactionReport result;
        if (!candidate.ai_->reactDiplomacy(*candidate.document_, request, context, *candidate.document_, result, error) ||
            !candidate.rng_.restore(result.contextAfter.rng, error)) return false;
        candidate.aiReaction_ = result.contextAfter;
        if (!finishEdit(std::move(candidate), error)) return false;
        report = std::move(result); return true;
    }, error);
}

bool State::reactAiEvent(const simulation::AiEventRequest& request,
                         const simulation::AiReactionContext& context,
                         simulation::AiReactionReport& report, save::Error& error) {
    return guarded([&] {
        if ((aiReaction_ && context != *aiReaction_) ||
            (rng_.snapshot().initialized && context.rng != rng_.snapshot()))
            return fail(error, save::ErrorCode::InvalidState, "AI reaction context differs from the owned continuation");
        State candidate;
        if (!copyForEdit(candidate, error)) return false;
        if (!candidate.ai_) {
            candidate.ai_.emplace();
            if (!candidate.ai_->initializeAfterLoad(*candidate.document_, error)) return false;
        }
        simulation::AiReactionReport result;
        if (!candidate.ai_->reactEvent(*candidate.document_, request, context, *candidate.document_, result, error) ||
            !candidate.rng_.restore(result.contextAfter.rng, error)) return false;
        candidate.aiReaction_ = result.contextAfter;
        if (!finishEdit(std::move(candidate), error)) return false;
        report = std::move(result); return true;
    }, error);
}

bool State::createCompletedBuilding(const simulation::BuildingCreationRequest& request,
                                    BuildingHandle& created, simulation::BuildingCreationReport& report,
                                    save::Error& error) {
    return guarded([&] {
        State candidate;
        if (!copyForEdit(candidate, error)) return false;
        simulation::BuildingCreationReport result;
        auto& d = *candidate.document_;
        if (!simulation::createCompletedBuilding(d, request, d, result, error)) return false;
        const size_t original = document_->buildings.size();
        if (d.buildings.size() != original + result.createdIds.size() || result.createdIds.empty())
            return fail(error, save::ErrorCode::InvalidState, "Building creation report does not match appended records");
        BuildingHandle handle;
        for (size_t i = 0; i < result.createdIds.size(); ++i) {
            if (d.buildings[original + i].id != result.createdIds[i])
                return fail(error, save::ErrorCode::InvalidState, "Building allocation order differs from creation report");
            if (!allocateSlot(candidate.buildingSlots_, candidate.buildingDenseSlots_, error)) return false;
            const auto slot = candidate.buildingDenseSlots_.back();
            if (result.createdIds[i] == result.buildingId) handle = {slot, candidate.buildingSlots_[slot - 1].identity};
        }
        if (!handle.slot) return fail(error, save::ErrorCode::InvalidState, "Building creation has no primary entity");
        if (!finishEdit(std::move(candidate), error)) return false;
        created = handle; report = std::move(result); return true;
    }, error);
}

bool State::startConstruction(const simulation::BuildingCreationRequest& request,
                              const simulation::ConstructionOrderContext& context,
                              BuildingHandle& created, simulation::ConstructionOrderReport& report,
                              save::Error& error) {
    return guarded([&] {
        if ((rng_.snapshot().initialized && context.events.rngBeforeEvents != rng_.snapshot()) ||
            (aiReaction_ && context.ai != *aiReaction_) || (events_ && context.log != *events_) ||
            (collection_ && context.payment.collection != *collection_) ||
            (eventCities_ && context.events.citiesBeforeLoad != *eventCities_))
            return fail(error, save::ErrorCode::InvalidState, "Construction context differs from the owned continuation");
        State candidate;
        if (!copyForEdit(candidate, error)) return false;
        auto inputs = context;
        const auto* territory = candidate.document_->territoryByIndex(request.territory);
        if (territory && territory->data.owner >= 0 && territory->data.owner < kMaxPlayers &&
            territory->data.owner != candidate.document_->options.localPlayer &&
            std::bit_cast<int8_t>(candidate.document_->players[size_t(territory->data.owner)].type) >= 3) {
            if (!candidate.ai_) {
                candidate.ai_.emplace();
                if (!candidate.ai_->initializeAfterLoad(*candidate.document_, error)) return false;
            }
            inputs.aiSession = &*candidate.ai_;
        } else inputs.aiSession = nullptr;
        simulation::ConstructionOrderReport result;
        if (!simulation::startConstruction(*candidate.document_, request, inputs, *candidate.document_, result, error)) return false;
        const size_t original = document_->buildings.size();
        if (candidate.document_->buildings.size() != original + result.createdIds.size() ||
            (result.accepted != !result.createdIds.empty()))
            return fail(error, save::ErrorCode::InvalidState, "Construction report does not match allocated buildings");
        BuildingHandle handle;
        for (size_t i = 0; i < result.createdIds.size(); ++i) {
            if (candidate.document_->buildings[original + i].id != result.createdIds[i])
                return fail(error, save::ErrorCode::InvalidState, "Construction allocation order differs from report");
            if (!allocateSlot(candidate.buildingSlots_, candidate.buildingDenseSlots_, error)) return false;
            const auto slot = candidate.buildingDenseSlots_.back();
            if (result.createdIds[i] == result.attemptedId) handle = {slot, candidate.buildingSlots_[slot - 1].identity};
        }
        if (result.accepted && !handle)
            return fail(error, save::ErrorCode::InvalidState, "Accepted construction has no primary entity");
        if (!candidate.rng_.restore(result.rngAfter, error)) return false;
        candidate.events_ = result.logAfter;
        candidate.aiReaction_ = result.aiAfter;
        candidate.collection_ = result.paymentEvaluated ? result.payment.collection : context.payment.collection;
        candidate.eventCities_ = context.events.citiesBeforeLoad;
        if (!finishEdit(std::move(candidate), error)) return false;
        created = handle; report = std::move(result); return true;
    }, error);
}

bool State::progressBuildingWork(uint32_t territory, const simulation::BuildingProgressContext& context,
                                simulation::BuildingProgressReport& report, save::Error& error) {
    return guarded([&] {
        if ((rng_.snapshot().initialized && context.events.rngBeforeEvents != rng_.snapshot()) ||
            (aiReaction_ && context.ai != *aiReaction_) || (events_ && context.log != *events_) ||
            (eventCities_ && context.events.citiesBeforeLoad != *eventCities_))
            return fail(error, save::ErrorCode::InvalidState, "Building progress context differs from the owned continuation");
        State candidate;
        if (!copyForEdit(candidate, error)) return false;
        // This caller recounts shrines only under victory0, where notices77/78
        // are disabled. Other nonlocal human players do not require AI bindings.
        auto inputs = context; inputs.aiSession = nullptr;
        const auto* region = candidate.document_->territoryByIndex(territory);
        if (region && region->data.owner >= 0 && region->data.owner < kMaxPlayers &&
            region->data.owner != candidate.document_->options.localPlayer &&
            std::bit_cast<int8_t>(candidate.document_->players[size_t(region->data.owner)].type) >= 3) {
            if (!candidate.ai_) {
                candidate.ai_.emplace();
                if (!candidate.ai_->initializeAfterLoad(*candidate.document_, error)) return false;
            }
            inputs.aiSession = &*candidate.ai_;
        }
        simulation::BuildingProgressReport result;
        if (!simulation::progressBuildingWork(*candidate.document_, territory, inputs, *candidate.document_, result, error)) return false;
        if (candidate.document_->buildings.size() != document_->buildings.size() || !result.createdIds.empty())
            return fail(error, save::ErrorCode::InvalidState, "Building work unexpectedly allocated entities");
        for (size_t i = 0; i < document_->buildings.size(); ++i)
            if (candidate.document_->buildings[i].id != document_->buildings[i].id)
                return fail(error, save::ErrorCode::InvalidState, "Building work changed entity identity or allocation order");
        if (!candidate.rng_.restore(result.rngAfter, error)) return false;
        candidate.events_ = result.logAfter; candidate.aiReaction_ = result.aiAfter;
        candidate.eventCities_ = result.citiesAfter;
        if (!finishEdit(std::move(candidate), error)) return false;
        report = std::move(result); return true;
    }, error);
}

template<class Request> bool State::applyManufacturing(const Request& request,
    const simulation::UnitManufacturingContext& context,
    simulation::UnitManufacturingReport& report, save::Error& error) {
    return guarded([&] {
        const auto& effects = context.effects;
        if ((rng_.snapshot().initialized && effects.events.rngBeforeEvents != rng_.snapshot()) ||
            (aiReaction_ && effects.ai != *aiReaction_) || (events_ && effects.log != *events_) ||
            (collection_ && effects.payment.collection != *collection_) ||
            (eventCities_ && effects.events.citiesBeforeLoad != *eventCities_))
            return fail(error, save::ErrorCode::InvalidState, "Manufacturing context differs from the owned continuation");
        State candidate;
        if (!copyForEdit(candidate, error)) return false;
        auto inputs = context; inputs.effects.aiSession = nullptr;
        const auto* region = candidate.document_->territoryByIndex(request.territory);
        if (region && region->data.owner >= 0 && region->data.owner < kMaxPlayers &&
            region->data.owner != candidate.document_->options.localPlayer &&
            std::bit_cast<int8_t>(candidate.document_->players[size_t(region->data.owner)].type) >= 3) {
            if (!candidate.ai_) {
                candidate.ai_.emplace();
                if (!candidate.ai_->initializeAfterLoad(*candidate.document_, error)) return false;
            }
            inputs.effects.aiSession = &*candidate.ai_;
        }
        simulation::UnitManufacturingReport result;
        if constexpr (std::is_same_v<Request, simulation::QueueUnitRequest>) {
            if (!simulation::queueUnit(*candidate.document_, request, inputs, *candidate.document_, result, error)) return false;
        } else {
            if (!simulation::produceUnits(*candidate.document_, request, inputs, *candidate.document_, result, error)) return false;
        }
        const size_t original = document_->armies.size();
        if (candidate.document_->armies.size() != original + result.createdIds.size())
            return fail(error, save::ErrorCode::InvalidState, "Manufacturing report does not match allocated units");
        for (size_t i = 0; i < result.createdIds.size(); ++i) {
            if (candidate.document_->armies[original + i].id != result.createdIds[i])
                return fail(error, save::ErrorCode::InvalidState, "Manufacturing allocation order differs from report");
            if (!allocateSlot(candidate.armySlots_, candidate.armyDenseSlots_, error)) return false;
        }
        if (!candidate.rng_.restore(result.rngAfter, error)) return false;
        candidate.events_ = result.logAfter; candidate.aiReaction_ = result.aiAfter;
        candidate.collection_ = result.collectionAfter;
        candidate.eventCities_ = effects.events.citiesBeforeLoad;
        if (!finishEdit(std::move(candidate), error, result.queueStructureChanged)) return false;
        report = std::move(result); return true;
    }, error);
}

bool State::queueUnit(const simulation::QueueUnitRequest& request,
                      const simulation::UnitManufacturingContext& context,
                      simulation::UnitManufacturingReport& report, save::Error& error) {
    return applyManufacturing(request, context, report, error);
}
bool State::produceUnits(const simulation::ProduceUnitsRequest& request,
                         const simulation::UnitManufacturingContext& context,
                         simulation::UnitManufacturingReport& report, save::Error& error) {
    return applyManufacturing(request, context, report, error);
}
bool State::dequeueUnit(const simulation::DequeueUnitRequest& request,
                        simulation::UnitDequeueReport& report, save::Error& error) {
    return guarded([&] {
        State candidate;
        if (!copyForEdit(candidate, error)) return false;
        simulation::UnitDequeueReport result;
        if (!simulation::dequeueUnit(*candidate.document_, request, *candidate.document_, result, error)) return false;
        if (!finishEdit(std::move(candidate), error)) return false;
        report = std::move(result); return true;
    }, error);
}

bool State::createArmy(const simulation::ArmyCreationRequest& request,
                       const simulation::ArmyCreationContext& context, ArmyHandle& created,
                       simulation::ArmyLifecycleReport& report, save::Error& error) {
    return guarded([&] {
        State candidate;
        if (!copyForEdit(candidate, error)) return false;
        simulation::ArmyLifecycleReport result;
        if (!simulation::createArmy(*candidate.document_, request, context, *candidate.document_, result, error)) return false;
        const size_t original = document_->armies.size();
        if (candidate.document_->armies.size() != original + result.createdIds.size() || result.createdIds.empty())
            return fail(error, save::ErrorCode::InvalidState, "Army creation report does not match appended records");
        ArmyHandle primary;
        for (size_t i = 0; i < result.createdIds.size(); ++i) {
            if (candidate.document_->armies[original + i].id != result.createdIds[i])
                return fail(error, save::ErrorCode::InvalidState, "Army allocation order differs from lifecycle report");
            if (!allocateSlot(candidate.armySlots_, candidate.armyDenseSlots_, error)) return false;
            const auto slot = candidate.armyDenseSlots_.back();
            if (result.createdIds[i] == result.primaryId) primary = {slot, candidate.armySlots_[slot - 1].identity};
        }
        if (!primary.slot) return fail(error, save::ErrorCode::InvalidState, "Army creation has no primary entity");
        if (!finishEdit(std::move(candidate), error)) return false;
        created = primary; report = std::move(result); return true;
    }, error);
}

bool State::removeArmy(ArmyHandle handle, simulation::ArmyRemovalKind kind, bool detachTaskForces,
                       simulation::ArmyLifecycleReport& report, save::Error& error) {
    return guarded([&] {
        const auto* value = army(handle);
        if (!value) return fail(error, save::ErrorCode::InvalidState, "Army removal received a null, stale or foreign handle");
        State candidate;
        if (!copyForEdit(candidate, error)) return false;
        simulation::ArmyLifecycleReport result;
        if (!simulation::removeArmy(*candidate.document_, {value->id, kind, detachTaskForces},
                                   *candidate.document_, result, error)) return false;
        // Retire by original dense position, from back to front. Removal order
        // can be recursive and unrelated to vector order; survivors keep slots.
        size_t removed = 0;
        for (size_t i = document_->armies.size(); i-- > 0; ) {
            if (!candidate.document_->armyById(document_->armies[i].id)) {
                retireSlot(candidate.armySlots_, candidate.armyDenseSlots_, uint32_t(i)); ++removed;
            }
        }
        if (removed != result.removedIds.size() || candidate.document_->armies.size() + removed != document_->armies.size())
            return fail(error, save::ErrorCode::InvalidState, "Army removal report does not match retired records");
        if (!finishEdit(std::move(candidate), error)) return false;
        report = std::move(result); return true;
    }, error);
}

bool State::removeBuilding(BuildingHandle handle, simulation::BuildingRemovalKind kind, int refundPlayer,
                           simulation::BuildingLifecycleReport& report, save::Error& error) {
    return guarded([&] {
        const auto* value = building(handle);
        if (!value) return fail(error, save::ErrorCode::InvalidState, "Building removal received a null, stale or foreign handle");
        State candidate;
        if (!copyForEdit(candidate, error)) return false;
        simulation::BuildingLifecycleReport result;
        if (!simulation::removeBuilding(*candidate.document_, {value->id, kind, refundPlayer},
                                       *candidate.document_, result, error)) return false;
        size_t removed = 0;
        for (size_t i = document_->buildings.size(); i-- > 0; ) {
            if (!candidate.document_->buildingById(document_->buildings[i].id)) {
                retireSlot(candidate.buildingSlots_, candidate.buildingDenseSlots_, uint32_t(i)); ++removed;
            }
        }
        if (removed != result.removedIds.size() || candidate.document_->buildings.size() + removed != document_->buildings.size())
            return fail(error, save::ErrorCode::InvalidState, "Building removal report does not match retired records");
        if (!finishEdit(std::move(candidate), error)) return false;
        report = std::move(result); return true;
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
const QueueNode* State::queueNode(QueueNodeHandle h) const { return at(graph_.queueNodes, h, queueNodeIdentity_); }
const MinisterNode* State::minister(MinisterHandle h) const { return at(graph_.ministers, h, preparationIdentity_); }
} // namespace dl2::runtime
