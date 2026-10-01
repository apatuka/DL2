#include "game/labor_balance.h"
#include "game/data_tables.h"

#include <algorithm>
#include <bit>
#include <memory>
#include <new>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>

namespace dl2::simulation {
namespace {

int32_t add(int32_t a, int32_t b) {
    return std::bit_cast<int32_t>(uint32_t(a) + uint32_t(b));
}
int32_t subtract(int32_t a, int32_t b) {
    return std::bit_cast<int32_t>(uint32_t(a) - uint32_t(b));
}
int32_t multiply(int32_t a, int32_t b) {
    return std::bit_cast<int32_t>(uint32_t(a) * uint32_t(b));
}
int16_t signed16(int32_t value) {
    return std::bit_cast<int16_t>(uint16_t(uint32_t(value) & 0xffffu));
}
int8_t signed8(int32_t value) {
    return std::bit_cast<int8_t>(uint8_t(uint32_t(value) & 0xffu));
}
uint16_t slotLock(int slot) { return uint16_t(0x100u << slot); }
bool locked(const Building& b, int slot) { return (b.flags & slotLock(slot)) != 0; }
bool essential(uint8_t task) { return task == 15 || task == 7 || task == 12; }

bool fail(save::Error& error, const std::string& message) {
    error = {save::ErrorCode::InvalidState, 0, "Labor balance: " + message};
    return false;
}

BuildingLaborState snapshot(const Building& b) {
    BuildingLaborState state;
    state.flags = b.flags;
    std::copy_n(b.task, 5, state.tasks.begin());
    std::copy_n(b.labor, 5, state.labor.begin());
    return state;
}

// orig: FUN_0044ba18 (TotalLabor). Every addition uses original low 32 bits.
int32_t totalLabor(const Building& b) {
    int32_t total = 0;
    for (int32_t labor : b.labor) total = add(total, labor);
    return total;
}

// orig: FUN_004023dc and FUN_0044c978. First match in physical slot order.
int findTask(const Building& b, uint8_t task) {
    for (int slot = 0; slot < 5; ++slot) if (b.task[slot] == task) return slot;
    return -1;
}
int firstTask(const Building& b) {
    for (int slot = 0; slot < 5; ++slot) if (b.task[slot] != 0) return slot;
    return -1;
}

struct Work {
    save::Document& document;
    // 1-based slots in the owning buildings vector; zero means no building.
    // The saved site words remain untouched and are never used as pointers.
    std::vector<std::array<size_t, kNumSites>> sites;
    size_t transferSteps = 0;
    static constexpr size_t kMaxTransferSteps = 1000000; // Resource cap, not a gameplay rule.

    bool validate(save::Error& error) {
        sites.resize(document.territories.size());
        std::unordered_map<uint32_t, size_t> ids;
        for (size_t i = 0; i < document.buildings.size(); ++i) {
            const auto& b = document.buildings[i];
            if (b.type == 0 || b.type >= data::kNumBuildingTypes)
                return fail(error, "building " + std::to_string(b.id) + " type is outside its definition table");
            ids.emplace(b.id, i + 1);
        }
        for (size_t i = 0; i < document.territories.size(); ++i) {
            const auto& t = document.territories[i].data;
            if (t.owner < -1 || t.owner >= kMaxPlayers)
                return fail(error, "territory " + std::to_string(t.index) + " owner is out of range");
            for (size_t slot = 0; slot < kNumSites; ++slot) {
                const uint32_t id = t.sites[slot].building.raw;
                if (id == 0) continue;
                const auto found = ids.find(id);
                if (found == ids.end()) return fail(error, "site refers to an absent building");
                const auto& b = document.buildings[found->second - 1];
                if (b.territory != t.index || b.site != int(slot))
                    return fail(error, "building/site references are not reciprocal");
                sites[i][slot] = found->second;
                // Only this branch reads a racial table. Other/unused player
                // slots may contain opaque index/race values in real saves.
                if (b.category == 17 && b.turnsLeft == 0 && t.owner >= 0) {
                    const int race = document.players[size_t(t.owner)].race;
                    if (race < 0 || race >= kMaxPlayers)
                        return fail(error, "housing owner's race is outside the saved racial table");
                }
            }
        }
        return true;
    }

    Building* at(size_t territory, size_t site) {
        const size_t slot = sites[territory][site];
        return slot ? &document.buildings[slot - 1] : nullptr;
    }

    // Both GetBuildingTasks' Player.index&31 and CanUpgradeBuilding's owner
    // bit use MOVSX WORD for masks. A knownMask with bit15 set is sign-extended.
    bool knows(int tech, uint8_t playerBit) const {
        const int32_t mask = signed16(document.techs[size_t(tech)].knownMask);
        return (uint32_t(mask) & (1u << (playerBit & 31u))) != 0;
    }

    // orig: FUN_0044ba40 / FUN_0044be88 (MaxLabor / ActiveMaxLabor).
    int32_t maxLabor(const Building& b) const {
        if (b.turnsLeft != 0) return 4;
        int32_t capacity = signed8(data::kBuildingTypes[b.type].maxLabor);
        const auto& t = document.territories[size_t(b.territory - 1)].data;
        if (b.category == 17 && t.owner >= 0) {
            const int race = document.players[size_t(t.owner)].race;
            capacity = multiply(document.raceStats.v[24][size_t(race)], capacity) / 100;
        }
        return capacity;
    }
    int32_t activeMaxLabor(const Building& b) const {
        const int32_t capacity = maxLabor(b);
        return (b.flags & 4) ? capacity : 0;
    }

    // orig: FUN_0044c654 (CanUpgradeBuilding). Checks stored category for the
    // special exclusions, but adjacent definition categories for the successor.
    bool canUpgrade(const Building& b) const {
        const auto& t = document.territories[size_t(b.territory - 1)].data;
        if (t.owner < 0 || b.type > 46 || b.category == 18 || b.category == 11 ||
            b.type == 3 || b.type == 16 || b.type == 43) return false;
        const auto& definition = data::kBuildingTypes[b.type];
        const auto& next = data::kBuildingTypes[b.type + 1];
        if (definition.category != next.category) return false;
        const int tech = signed8(next.techRequired);
        return tech == 0 || knows(tech, uint8_t(t.owner));
    }

    // orig: FUN_0044b620 / FUN_0044b5bc / FUN_00484e88. Count owned queue
    // nodes, not QueueRecord::count and never a historical QueueHead pointer.
    bool hasQueue(const Building& b) const {
        const int category = data::kBuildingTypes[b.type].productionQueue;
        return category >= 1 && category <= 5 &&
               !document.territories[size_t(b.territory - 1)].queues[size_t(category - 1)].empty();
    }

    // orig: FUN_0044c320 (TransferLabor). No Active, Built, housing-category,
    // lock or completion precondition is added to the original capacity check.
    bool transfer(Building& source, int from, Building& destination, int to) {
        if (source.labor[from] != 0 &&
            (totalLabor(destination) < maxLabor(destination) || &source == &destination)) {
            source.labor[from] = subtract(source.labor[from], 1);
            destination.labor[to] = add(destination.labor[to], 1);
            return true;
        }
        return false;
    }

    // orig: MoveLaborToHousingNoNet 0044c368. The first site with spare capacity
    // and task20 wins, even if it is the source or has a non-housing category.
    bool moveToHousing(Building& source, int from) {
        const size_t territory = size_t(source.territory - 1);
        for (size_t site = 0; site < kNumSites; ++site) {
            auto* target = at(territory, site);
            if (!target || totalLabor(*target) >= maxLabor(*target)) continue;
            const int slot = findTask(*target, 20);
            if (slot >= 0) return transfer(source, from, *target, slot);
        }
        return false;
    }

    // orig: FUN_0044c49c (DistributeLabor), assembly 0044c589..0044c60a:
    // quotient is written as s16; remainder is a separate signed BYTE difference.
    bool distribute(Building& b, int32_t labor, save::Error& error) {
        if (b.turnsLeft != 0) {
            for (int slot = 0; slot < 5; ++slot) {
                b.labor[slot] = 0;
                b.flags &= uint16_t(~slotLock(slot));
            }
            b.labor[0] = labor;
            return true;
        }
        const bool queue = hasQueue(b);
        int open = 0, first = -1;
        int32_t held = 0;
        for (int slot = 0; slot < 5; ++slot) {
            if (b.task[slot] == 0) continue;
            if (!locked(b, slot) && b.task[slot] != 21 && (slot < 4 || queue)) {
                if (first < 0) first = slot;
                ++open;
            } else held = add(held, b.labor[slot]);
        }
        labor = subtract(labor, held);
        if (open == 0) {
            // Each iteration injects one worker into slot0 before attempting a
            // transfer; if transfer fails, that worker remains and the rest is
            // not redistributed. Preserve this unusual original behavior.
            while (labor > 0) {
                if (transferSteps == kMaxTransferSteps) {
                    error = {save::ErrorCode::Limit, 0, "Labor balance exceeds 1000000 transfer attempts"};
                    return false;
                }
                ++transferSteps;
                labor = subtract(labor, 1);
                b.labor[0] = add(b.labor[0], 1);
                if (!moveToHousing(b, 0)) break;
            }
            return true;
        }
        // Original's allLocked flag is necessarily false when open!=0.
        const int32_t quotient = labor / open;
        int32_t assigned = 0;
        for (int slot = 0; slot < 5; ++slot) {
            if (b.task[slot] != 0 && !locked(b, slot) && b.task[slot] != 21 && (slot < 4 || queue)) {
                b.labor[slot] = signed16(quotient);
                assigned = add(assigned, quotient); // Full quotient, NOT its narrowed stored value.
            }
        }
        b.labor[first] = add(b.labor[first], signed8(subtract(labor, assigned)));
        return true;
    }

    // orig: FUN_0044e600, dynamic task for Hidden/Sea Shrine slot1. These
    // overrides bypass the ordinary per-task technology gates.
    uint8_t shrineTask(const Building& b) const {
        constexpr uint8_t sea[] = {6, 8, 12, 15, 16, 14};
        constexpr uint8_t land[] = {3, 4, 12, 13, 15, 6, 8, 16, 14};
        if (b.type == 47) return sea[(b.territory + b.site) % 6];
        int selection = (b.territory + b.site) % 9;
        if (selection < 6) {
            const auto& site = document.territories[size_t(b.territory - 1)].data.sites[size_t(b.site)];
            switch (site.terrainFlags & 15u) {
            case 0: selection = 2; break;
            case 1: selection = 4; break;
            case 2: selection = 1; break;
            case 3: selection = 3; break;
            case 4: selection = 0; break;
            default: break;
            }
        }
        return land[selection];
    }

    // orig: GetBuildingTasks 0044e7ec. Tasks are rebuilt irrespective of Active
    // or Built. Locked disabled tasks lose workers but retain their lock bits.
    bool refresh(Building& b, const Player& owner, save::Error& error) {
        if (b.turnsLeft != 0) {
            b.task[0] = 2;
            b.labor[0] = totalLabor(b);
            for (int slot = 1; slot < 5; ++slot) {
                b.task[slot] = 0; b.labor[slot] = 0;
                b.flags &= uint16_t(~slotLock(slot));
            }
            return true;
        }
        int32_t displaced = 0;
        if (!canUpgrade(b)) {
            b.task[0] = 0;
            displaced = b.labor[0]; b.labor[0] = 0;
            b.flags &= uint16_t(~slotLock(0));
        } else {
            if (b.task[0] == 2 && !locked(b, 0)) {
                displaced = b.labor[0]; b.labor[0] = 0;
            }
            b.task[0] = 21;
        }
        for (int slot = 1; slot < 5; ++slot) {
            uint8_t task = data::kBuildingTypes[b.type].tasks[slot];
            if (slot == 1 && (b.type == 46 || b.type == 47)) task = shrineTask(b);
            else {
                int tech = 0;
                switch (task) {
                case 4: tech = 20; break;
                case 6: tech = 4; break;
                case 9: tech = 2; break;
                case 10: tech = 29; break;
                case 16: tech = 22; break;
                default: break;
                }
                if (tech != 0 && !knows(tech, owner.index)) task = 0;
            }
            b.task[slot] = task;
            if (task == 0) {
                displaced = add(displaced, b.labor[slot]); b.labor[slot] = 0;
            }
        }
        return displaced == 0 || distribute(b, add(totalLabor(b), displaced), error);
    }

    // orig: FUN_0046c3fc (TerritoryLaborPool). (100 - tier*10)/4 truncates
    // toward zero; assembly adds 3 before SAR when the numerator is negative.
    std::pair<int32_t, int32_t> laborPool(const Territory& t) const {
        const int32_t tier = (int32_t(t.morale) + 9) / 10;
        const int32_t percent = add(subtract(100, multiply(tier, 10)) / 4, multiply(tier, 10));
        int32_t pool = multiply(t.population, percent) / 10000;
        if (t.population != 0) pool = std::max(pool, 1);
        return {pool, std::max(subtract(int32_t(t.population) / 100, pool), 0)};
    }

    // Apply each narrowing separately: min(pool,old) is sign-extended from s16
    // BEFORE it is compared with capacity. Combining the minima is not exact.
    void trim(Building& b, int slot, int32_t& pool, int32_t& capacity) {
        const int32_t before = b.labor[slot];
        b.labor[slot] = signed16(std::min(pool, b.labor[slot]));
        b.labor[slot] = signed16(std::min(capacity, b.labor[slot]));
        pool = subtract(pool, b.labor[slot]);
        capacity = subtract(capacity, b.labor[slot]);
        if (b.labor[slot] != before) b.flags &= uint16_t(~slotLock(slot));
    }

    // orig: FUN_0044bea8. Keep all four passes and their distinct slot order.
    // In particular, later essential slots can drive capacity NEGATIVE after an
    // earlier ordinary slot has spent it. Do not repair that original oddity.
    bool balance(size_t territory, TerritoryLaborBalance& report, save::Error& error) {
        auto& t = document.territories[territory].data;
        if (t.population == 0) t.morale = 100;
        const auto available = laborPool(t);
        report.laborPool = available.first; report.unavailableLabor = available.second;
        int32_t pool = available.first;
        for (size_t site = 0; site < kNumSites; ++site) {
            auto* b = at(territory, site);
            if (!b) continue;
            int32_t capacity = activeMaxLabor(*b);
            for (int slot = 0; slot < 5; ++slot)
                if (essential(b->task[slot])) trim(*b, slot, pool, capacity);
        }
        for (size_t site = 0; site < kNumSites; ++site) {
            auto* b = at(territory, site);
            if (!b || b->category == 17) continue;
            int32_t capacity = activeMaxLabor(*b);
            for (int n = 0; n < 5; ++n) {
                const int slot = (n + 1) % 5;
                if (essential(b->task[slot])) capacity = subtract(capacity, b->labor[slot]);
                else trim(*b, slot, pool, capacity);
            }
        }
        for (size_t site = 0; site < kNumSites; ++site) {
            auto* b = at(territory, site);
            if (!b || b->category != 17) continue;
            int32_t capacity = maxLabor(*b); // Deliberately NOT ActiveMaxLabor.
            for (int slot = 0; slot < 5; ++slot) {
                if (essential(b->task[slot])) capacity = subtract(capacity, b->labor[slot]);
                else trim(*b, slot, pool, capacity);
            }
        }
        for (size_t site = 0; pool != 0 && site < kNumSites; ++site) {
            auto* b = at(territory, site);
            if (!b || b->category != 17) continue;
            int32_t capacity = activeMaxLabor(*b);
            for (int32_t labor : b->labor) capacity = subtract(capacity, labor);
            const int32_t amount = std::min(capacity, pool); // May be negative; preserve it.
            int slot = findTask(*b, 20);
            if (slot < 0) slot = firstTask(*b);
            if (slot < 0)
                return fail(error, "building " + std::to_string(b->id) + " has no housing fallback task (original writes slot -1)");
            b->labor[slot] = add(b->labor[slot], amount);
            pool = subtract(pool, amount);
        }
        report.unassignedLabor = pool;
        for (size_t site = 0; site < kNumSites; ++site)
            if (const auto* b = at(territory, site)) report.assignedLabor = add(report.assignedLabor, totalLabor(*b));
        report.moraleAfter = t.morale;
        return true;
    }
};

} // namespace

bool planLaborBalance(const save::Document& source, LaborBalancePlan& destination, save::Error& error) try {
    error = {};
    // Reject oversized/invalid documents before allocating an owning copy.
    if (!save::validate(source, error)) return false;
    if (source.header.isMap) return fail(error, "requires a saved game, not a map");
    // Keep the large packed document off the stack and own every mutable byte.
    auto candidate = std::make_unique<save::Document>(source);
    Work work{*candidate, {}};
    if (!work.validate(error)) return false;
    LaborBalancePlan result;
    result.buildings.reserve(source.buildings.size());
    result.territories.reserve(source.territories.size());
    // orig: FUN_0046c1f0. Complete the refresh for ALL owned territories before
    // performing any BalanceLabor calls; transfers can affect later buildings.
    for (size_t territory = 0; territory < candidate->territories.size(); ++territory) {
        const auto& t = candidate->territories[territory].data;
        if (t.owner < 0) continue;
        for (size_t site = 0; site < kNumSites; ++site)
            if (auto* b = work.at(territory, site))
                if (!work.refresh(*b, candidate->players[size_t(t.owner)], error)) return false;
    }
    // orig: FUN_0046c780. Balance and upper clamp apply even to unowned regions.
    for (size_t territory = 0; territory < candidate->territories.size(); ++territory) {
        const auto& before = source.territories[territory].data;
        auto& after = candidate->territories[territory].data;
        TerritoryLaborBalance report;
        report.territory = before.index; report.moraleBefore = before.morale;
        std::copy_n(before.materials, 11, report.materialsBefore.begin());
        if (!work.balance(territory, report, error)) return false;
        for (int material = 1; material < 11; ++material)
            if (after.materials[material] > 10000) after.materials[material] = 10000;
        std::copy_n(after.materials, 11, report.materialsAfter.begin());
        result.territories.push_back(report);
    }
    for (size_t i = 0; i < source.buildings.size(); ++i) {
        const auto& before = source.buildings[i];
        result.buildings.push_back({before.id, uint32_t(before.territory), uint8_t(before.site),
                                    snapshot(before), snapshot(candidate->buildings[i])});
    }
    destination = std::move(result);
    return true;
} catch (const std::bad_alloc&) {
    error = {save::ErrorCode::Limit, 0, "Labor balance allocation failed"};
    return false;
} catch (const std::length_error&) {
    error = {save::ErrorCode::Limit, 0, "Labor balance exceeds container limits"};
    return false;
}

bool prepareCreatedBuildingLabor(const save::Document& source, uint32_t buildingId,
                                 save::Document& destination, save::Error& error) try {
    if (!save::validate(source, error)) return false;
    if (source.header.isMap) return fail(error, "creation requires a saved game");
    const auto* fresh = source.buildingById(buildingId);
    if (!fresh || fresh->type == 0 || fresh->type >= data::kNumBuildingTypes ||
        fresh->turnsLeft != 0 || fresh->flags != 6 || fresh->minister != 0 ||
        fresh->type == 38 || fresh->type == 39 || data::kBuildingTypes[fresh->type].category == 11 ||
        fresh->category != data::kBuildingTypes[fresh->type].category)
        return fail(error, "creation helper requires a fresh ordinary finished building");
    for (int slot = 0; slot < 5; ++slot)
        if (fresh->labor[slot] || fresh->task[slot])
            return fail(error, "creation helper requires zero initial tasks/labor");
    const size_t territory = size_t(fresh->territory - 1);
    const int owner = source.territories[territory].data.owner;
    if (owner < 0 || owner >= kMaxPlayers)
        return fail(error, "creation helper requires an owned territory");
    auto candidate = std::make_unique<save::Document>(source);
    Work work{*candidate, {}};
    if (!work.validate(error)) return false;
    auto& building = *work.at(territory, size_t(fresh->site));
    if (!work.refresh(building, candidate->players[size_t(owner)], error)) return false;
    TerritoryLaborBalance ignored;
    if (!work.balance(territory, ignored, error)) return false;

    // orig: 0044c754 + 0044c9a0. Housing is identified by first task20, NOT
    // stored building category, and additions retain their signed low32 bits.
    int32_t available = 0;
    for (size_t site = 0; site < kNumSites; ++site) if (const auto* b = work.at(territory, site)) {
        const int slot = findTask(*b, 20);
        if (slot >= 0) available = add(available, b->labor[slot]);
    }
    const int32_t requested = std::min(available, work.maxLabor(building));
    int targetSlot = -1;
    for (int slot = 0; slot < 5; ++slot)
        if (building.task[slot] != 0 && building.task[slot] != 21) { targetSlot = slot; break; }
    // Finished ordinary table rows never select construction. Do not fake the
    // assistant/TaskUrgency dependency if that premise changes in the future.
    if (targetSlot >= 0 && building.task[targetSlot] == 2)
        return fail(error, "creation cannot execute the construction urgency branch");
    // orig: MoveHousingLabor 0044c79c. Failed moves do NOT end this loop.
    for (int32_t attempt = 0; targetSlot >= 0 && attempt < requested; ++attempt) {
        if (work.transferSteps == Work::kMaxTransferSteps) {
            error = {save::ErrorCode::Limit, 0, "Creation labor exceeds 1000000 transfer attempts"};
            return false;
        }
        ++work.transferSteps;
        const int32_t total = totalLabor(building), maximum = work.maxLabor(building);
        if (building.category == 17 && total == maximum) {
            const int housing = findTask(building, 20);
            if (housing >= 0 && building.labor[housing] != 0) {
                building.labor[targetSlot] = add(building.labor[targetSlot], 1);
                building.labor[housing] = subtract(building.labor[housing], 1);
            }
        } else if (total < maximum) {
            for (size_t site = 0; site < kNumSites; ++site) if (auto* b = work.at(territory, site)) {
                const int housing = findTask(*b, 20);
                if (housing >= 0 && b->labor[housing] != 0) {
                    building.labor[targetSlot] = add(building.labor[targetSlot], 1);
                    b->labor[housing] = subtract(b->labor[housing], 1);
                    break;
                }
            }
        }
    }
    destination = std::move(*candidate);
    error = {};
    return true;
} catch (const std::bad_alloc&) {
    error = {save::ErrorCode::Limit, 0, "Creation labor allocation failed"};
    return false;
} catch (const std::length_error&) {
    error = {save::ErrorCode::Limit, 0, "Creation labor exceeds container limits"};
    return false;
}

} // namespace dl2::simulation
