#include "game/production_plan.h"
#include "game/data_tables.h"

#include <algorithm>
#include <bit>
#include <new>
#include <stdexcept>
#include <string>
#include <utility>

namespace dl2::simulation {
namespace {

int32_t add(int32_t a, int32_t b) {
    return std::bit_cast<int32_t>(uint32_t(a) + uint32_t(b));
}
int32_t multiply(int32_t a, int32_t b) {
    return std::bit_cast<int32_t>(uint32_t(a) * uint32_t(b));
}
int16_t signed16(int32_t value) {
    return std::bit_cast<int16_t>(uint16_t(uint32_t(value) & 0xffffu));
}
int8_t signed8(uint8_t value) { return std::bit_cast<int8_t>(value); }
int16_t read16(const uint8_t* bytes) {
    return std::bit_cast<int16_t>(uint16_t(uint16_t(bytes[0]) | (uint16_t(bytes[1]) << 8)));
}
bool fail(save::Error& error, const std::string& message) {
    error = {save::ErrorCode::InvalidState, 0, "Production: " + message};
    return false;
}
bool buildingFailure(save::Error& error, const Building& b, const char* message) {
    return fail(error, "building " + std::to_string(b.id) + ": " + message);
}

// Production uses signed bytes even where archival fields/tables are unsigned.
// DAT_004f9dc8 is the LOW BYTE of BuildingDef::energyUse, not the whole uint16.
bool usesEnergy(const data::BuildingDef& definition) {
    return signed8(uint8_t(definition.energyUse & 0xffu)) != 0;
}

bool validateInputs(const save::Document& d, save::Error& error) {
    if (!save::validate(d, error)) return false;
    if (d.header.isMap) return fail(error, "queries require a saved game, not a map");
    for (const auto& record : d.territories) {
        const auto& t = record.data;
        if (t.owner < -1 || t.owner >= kMaxPlayers) return fail(error, "territory owner is out of range");
        if (t.owner >= 0) {
            const auto& owner = d.players[size_t(t.owner)];
            // Unused player slots in real saves may retain index=0. Only
            // producers' owners supply the race and technology-mask bit below.
            if (owner.index != t.owner) return fail(error, "owning player index differs from its slot");
            if (owner.race < 0 || owner.race >= kMaxPlayers)
                return fail(error, "owning player race is out of range");
        }
        for (size_t i = 0; i < kNumSites; ++i) {
            const auto& site = t.sites[i];
            if (site.building.raw == 0) continue;
            const auto* b = d.buildingById(site.building.raw);
            if (!b || b->territory != t.index || b->site != int(i))
                return fail(error, "site building does not refer back to its territory/site");
        }
    }
    for (const auto& b : d.buildings) {
        if (b.type == 0 || b.type >= data::kNumBuildingTypes)
            return buildingFailure(error, b, "type is out of range");
        if (b.category > 20) return buildingFailure(error, b, "category is out of range");
        for (int slot = 0; slot < 5; ++slot) {
            // Task is a signed byte indexing saved RaceStats[64], not merely
            // the named UI enumeration 0..21. Rows 22..63 remain valid inputs.
            if (b.task[slot] >= kNumRaceStatRows)
                return buildingFailure(error, b, "task exceeds the racial-stat table");
            if (b.labor[slot] < 0) return buildingFailure(error, b, "negative labor");
        }
    }
    return true;
}

// orig: FUN_0044ba40 (MaxLabor). Construction has capacity 4; completed
// housing uses the owner's SAVED racial row 24, not static defaults.
int32_t maximumLabor(const save::Document& d, const Territory& t, const Building& b) {
    if (b.turnsLeft != 0) return 4;
    int32_t value = signed8(data::kBuildingTypes[b.type].maxLabor);
    if (b.category == 17 && t.owner != -1)
        value = multiply(d.raceStats.v[24][size_t(d.players[size_t(t.owner)].race)], value) / 100;
    return value;
}

// orig: FUN_0046b074 (land population ceiling), including the category-only
// sea-platform test 0044d1a4 (no Active/Built/completion condition).
int32_t landPopulation(const save::Document& d, const Territory& t) {
    if (t.terrain == 0) {
        for (const auto& site : t.sites) {
            const auto* b = d.buildingById(site.building.raw);
            if (b && b->category == 20) return 2000;
        }
    }
    int32_t sites = 0;
    for (const auto& site : t.sites) if ((site.terrainFlags & 0xffu) < 5) ++sites;
    return ((sites * 139 + 50) / 100) * 100;
}

// orig: FUN_0046b0e4 (TerritoryMaxPopulation). Built bit2 and completion,
// NOT Active bit4. Only exact housing types 1,2,3,39 contribute.
int32_t maximumPopulation(const save::Document& d, const Territory& t) {
    int32_t capacity = 0;
    for (const auto& site : t.sites) {
        const auto* b = d.buildingById(site.building.raw);
        if (!b || !(b->flags & 2) || b->turnsLeft != 0) continue;
        switch (b->type) {
        case 1: capacity += 500; break;
        case 2: capacity += 1000; break;
        case 3: case 39: capacity += 1500; break;
        default: break;
        }
    }
    if (t.owner != -1)
        capacity = multiply(d.raceStats.v[24][size_t(d.players[size_t(t.owner)].race)], capacity) / 100;
    return std::min(capacity, landPopulation(d, t));
}

// orig: FUN_0044e600: hidden/sea shrine slot 1 dynamically selects task/rate.
// The territory and site numbers, NOT file ID or position in buildings[], seed it.
std::pair<uint8_t, int32_t> shrineTask(const Territory& t, const Building& b) {
    static constexpr uint8_t seaTasks[] = {6, 8, 12, 15, 16, 14};
    static constexpr int32_t seaRates[] = {5, 50, 100, 100, 5, 50};
    static constexpr uint8_t landTasks[] = {3, 4, 12, 13, 15, 6, 8, 16, 14};
    static constexpr int32_t landRates[] = {100, 100, 100, 100, 100, 5, 50, 5, 50};
    if (b.type == 47) {
        const int index = (b.territory + b.site) % 6;
        return {seaTasks[index], seaRates[index]};
    }
    int index = (b.territory + b.site) % 9;
    if (index < 6) {
        switch (t.sites[size_t(b.site)].terrainFlags & 0xfu) {
        case 0: index = 2; break;
        case 1: index = 4; break;
        case 2: index = 1; break;
        case 3: index = 3; break;
        case 4: index = 0; break;
        default: break; // Original keeps the modulo result for other codes.
        }
    }
    return {landTasks[index], landRates[index]};
}

bool terrainTask(uint8_t task) {
    return task == 3 || task == 4 || task == 12 || task == 13 || task == 15;
}

// orig: FUN_0044e9e4 (site yield). Saved site bytes +00/+01 are real x/y,
// initialized by 0046686c to index%6,index/6 and preserved by save/load.
// No implicit normalization: reject inconsistent coordinates/unsafe footprints.
bool siteYield(const save::Document& d, const Territory& t, const Building& b,
               uint8_t task, int32_t input, int32_t& result, save::Error& error) {
    const auto& anchor = t.sites[size_t(b.site)];
    const int x = signed8(uint8_t(anchor.unk_00 & 0xffu));
    const int y = signed8(uint8_t(anchor.unk_00 >> 8));
    const int side = signed8(data::kBuildingTypes[b.type].size);
    if (x != b.site % 6 || y != b.site / 6)
        return buildingFailure(error, b, "saved site coordinates disagree with its grid index");
    if (side < 1 || x + side > 6 || y - side + 1 < 0)
        return buildingFailure(error, b, "production footprint is outside the 6x6 site grid");
    int resource = 0, matching = 0;
    switch (task) {
    case 3: resource = 3; matching = 4; break;
    case 4: resource = 4; matching = 6; break;
    case 12: resource = 1; matching = 1; break;
    case 13: resource = 2; matching = 3; break;
    case 15: resource = 0; matching = 2; break;
    default: return buildingFailure(error, b, "invalid terrain-production task");
    }
    int32_t richness = 0, factor = 2;
    for (int row = y; row > y - side; --row) {
        for (int column = x; column < x + side; ++column) {
            const auto& site = t.sites[size_t(row * 6 + column)];
            richness = add(richness, read16(&site.unk_05[1 + resource * 2]));
            if (signed8(site.value) == matching) ++factor;
        }
    }
    if (d.options.fastProduction != 0 && task != 7 && task != 5) input = multiply(input, 2);
    result = multiply(multiply(input, factor), richness) / (side * side * 20000);
    return true;
}

bool calculate(const save::Document& d, const Territory& t, const Building& b,
               uint8_t task, int32_t labor, int32_t rate, bool maximum,
               bool foodWoodBonus, int32_t& result, save::Error& error) {
    int32_t output = 0;
    if (task != 0) {
        const int32_t capacity = maximumLabor(d, t, b);
        if (capacity < 0 || labor < 0) return buildingFailure(error, b, "negative production-table index");
        const auto& definition = data::kBuildingTypes[b.type];
        int32_t power = 100;
        if (!maximum && usesEnergy(definition) && b.turnsLeft == 0)
            power = multiply(signed8(t.knowledge), 100) / 100;
        output = multiply(data::kLaborProductionTable[std::min(capacity, 10)][std::min(labor, 10)], power);
        output = multiply(output, d.raceStats.v[task][size_t(d.players[size_t(t.owner)].race)]);
        output = multiply(output, rate) / 100000;
    }
    if (b.category == 11) {
        output = multiply(output, 2);
        // DAT_004fc21e = TechSaved[33].knownMask (Native Languages).
        if (d.techs[33].knownMask & (1u << d.players[size_t(t.owner)].index)) output = multiply(output, 2);
    }
    if (terrainTask(task)) {
        if (!siteYield(d, t, b, task, output / 10, output, error)) return false;
        if (foodWoodBonus && (task == 12 || task == 13))
            output = add(output, signed16(multiply(signed8(t.unk_8b0[0xe4]), output) / 100));
        if (task == 12 && (t.flags & 0x40)) output /= 2;
    } else {
        output = add(output, 9) / 10;
        if (d.options.fastProduction != 0 && task != 7 && task != 5) output = multiply(output, 2);
    }
    if (labor != 0) output = std::max(output, 1);
    result = output;
    return true;
}

bool querySlot(const save::Document& d, const Territory& t, const Building& b,
               int slot, bool maximum, int32_t maxPopulation, SlotProduction& result,
               save::Error& error) {
    const auto& definition = data::kBuildingTypes[b.type];
    uint8_t task = maximum ? definition.tasks[slot] : b.task[slot];
    int32_t rate = definition.taskRate[slot];
    if (slot == 1 && (b.type == 46 || b.type == 47)) {
        const auto shrine = shrineTask(t, b);
        task = shrine.first; rate = shrine.second;
    }
    result.task = task;
    if (task == 0) return true; // Deliberate safe replacement of original stack/carry bug.
    result.labor = maximum ? std::min(maxPopulation, int32_t(signed8(definition.maxLabor))) : b.labor[slot];
    if (result.labor < 0) return buildingFailure(error, b, "negative hypothetical labor");
    if (!maximum && !(b.flags & 4)) return true;
    return calculate(d, t, b, task, result.labor, rate, maximum, true, result.output, error);
}

} // namespace

bool planProduction(const save::Document& d, ProductionPlan& destination, save::Error& error) try {
    error = {};
    if (!validateInputs(d, error)) return false;
    ProductionPlan candidate;
    candidate.territories.reserve(d.territories.size());
    for (const auto& record : d.territories) {
        const auto& t = record.data;
        TerritoryProduction territory;
        territory.territory = t.index; territory.owner = t.owner;
        const int32_t population = t.owner < 0 ? 0 : maximumPopulation(d, t);
        for (size_t site = 0; site < kNumSites; ++site) {
            const auto* b = d.buildingById(t.sites[site].building.raw);
            if (!b) continue;
            BuildingProduction building;
            building.buildingId = b->id; building.site = uint8_t(site);
            building.type = b->type; building.category = b->category;
            building.active = (b->flags & 4) != 0; building.built = (b->flags & 2) != 0;
            if (t.owner >= 0) {
                building.evaluated = true;
                building.maxLabor = maximumLabor(d, t, *b);
                if (building.maxLabor < 0 || population < 0)
                    return buildingFailure(error, *b, "negative labor/population capacity");
                for (int slot = 0; slot < 5; ++slot)
                    if (!querySlot(d, t, *b, slot, false, population, building.assigned[size_t(slot)], error) ||
                        !querySlot(d, t, *b, slot, true, population, building.maximum[size_t(slot)], error)) return false;
            }
            territory.buildings.push_back(building);
        }
        candidate.territories.push_back(std::move(territory));
    }
    destination = std::move(candidate);
    return true;
} catch (const std::bad_alloc&) {
    error = {save::ErrorCode::Limit, 0, "Production query allocation failed"};
    return false;
} catch (const std::length_error&) {
    error = {save::ErrorCode::Limit, 0, "Production query exceeds container limits"};
    return false;
}

bool taskOutput(const save::Document& d, uint32_t buildingId, int slot,
                int32_t labor, int32_t& result, save::Error& error) try {
    error = {};
    if (!validateInputs(d, error)) return false;
    if (slot < 0 || slot >= 5 || labor < 0) return fail(error, "slot/labor argument is out of range");
    const auto* b = d.buildingById(buildingId);
    if (!b) return fail(error, "building ID does not exist");
    const auto& t = d.territories[size_t(b->territory - 1)].data;
    if (t.owner < 0) return buildingFailure(error, *b, "no owning player for a racial production query");
    int32_t candidate = 0;
    if (b->flags & 4) {
        uint8_t task = b->task[slot];
        int32_t rate = data::kBuildingTypes[b->type].taskRate[slot];
        if (slot == 1 && (b->type == 46 || b->type == 47)) {
            const auto shrine = shrineTask(t, *b);
            task = shrine.first; rate = shrine.second;
        }
        if (!calculate(d, t, *b, task, labor, rate, false, false, candidate, error)) return false;
    }
    result = candidate;
    return true;
} catch (const std::bad_alloc&) {
    error = {save::ErrorCode::Limit, 0, "Production query allocation failed"};
    return false;
} catch (const std::length_error&) {
    error = {save::ErrorCode::Limit, 0, "Production query exceeds container limits"};
    return false;
}

} // namespace dl2::simulation
