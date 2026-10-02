#include "game/resource_needs.h"
#include "game/data_tables.h"

#include <algorithm>
#include <bit>
#include <cstring>
#include <exception>
#include <limits>
#include <new>
#include <stdexcept>
#include <string>
#include <utility>

namespace dl2::simulation {
namespace {

int32_t wrapAdd(int32_t a, int32_t b) {
    return std::bit_cast<int32_t>(uint32_t(a) + uint32_t(b));
}
int32_t wrapSubtract(int32_t a, int32_t b) {
    return std::bit_cast<int32_t>(uint32_t(a) - uint32_t(b));
}
int32_t wrapMultiply(int32_t a, int32_t b) {
    return std::bit_cast<int32_t>(uint32_t(a) * uint32_t(b));
}
int16_t signed16(int32_t value) {
    return std::bit_cast<int16_t>(uint16_t(uint32_t(value) & 0xffffu));
}
int8_t signed8(uint8_t value) { return std::bit_cast<int8_t>(value); }

bool invalid(save::Error& error, uint32_t territory, const char* message) {
    error = {save::ErrorCode::InvalidState, 0,
             "Resource territory " + std::to_string(territory) + ": " + message};
    return false;
}

bool validateSource(const save::Document& source, save::Error& error) {
    if (!save::validate(source, error)) return false;
    if (source.header.isMap) {
        error = {save::ErrorCode::InvalidState, 0, "Resource planning requires a saved game, not a map"};
        return false;
    }
    for (const auto& record : source.territories)
        if (record.data.owner < -1 || record.data.owner >= kMaxPlayers)
            return invalid(error, record.data.index, "owner is outside -1..6");
    return true;
}

template<class Operation> bool guarded(Operation&& operation, save::Error& error) {
    try { return operation(); }
    catch (const std::bad_alloc&) {
        error = {save::ErrorCode::Limit, 0, "Insufficient memory while planning resources"};
    } catch (const std::length_error&) {
        error = {save::ErrorCode::Limit, 0, "Resource plan allocation exceeds limits"};
    } catch (const std::exception& exception) {
        error = {save::ErrorCode::InvalidState, 0, "Resource planning failed: " + std::string(exception.what())};
    }
    return false;
}

// orig: FUN_0046b910 (TerritoryEnergyUse). Resolve each of the 36 saved site
// IDs; don't enumerate all buildings or substitute the category. The original
// reads a signed BYTE from BuildingDef+0x0c, despite the table's uint16 field.
int32_t energyNeed(const save::Document& source, const Territory& territory) {
    int32_t total = 0;
    for (const auto& site : territory.sites) {
        const auto* building = source.buildingById(site.building.raw);
        if (building && building->turnsLeft == 0 && (building->flags & 4)) {
            const auto raw = uint8_t(data::kBuildingTypes[building->type].energyUse & 0xffu);
            total = wrapAdd(total, signed8(raw));
        }
    }
    return total;
}

// orig: FUN_0046b958 (TerritoryFoodNeed). The offset 0055a156 is saved/runtime
// RaceStats row61 (7 columns), not a static race default or population divisor.
bool foodNeed(const save::Document& source, const Territory& territory,
              int32_t& result, save::Error& error) {
    const int owner = territory.owner;
    if (owner < 0 || owner >= kMaxPlayers) { result = 0; return true; }
    const int race = source.players[size_t(owner)].race;
    // The original adds signed race to a flat row61 address. Cross-row reads
    // remain defined while inside the actual saved RaceStats block.
    const int word=61*kMaxPlayers+race;
    if (word<0 || word>=int(sizeof(RaceStats)/sizeof(int16_t)))
        return invalid(error, territory.index, "food racial address is outside the saved RaceStats block");
    int16_t racial;
    std::memcpy(&racial,reinterpret_cast<const uint8_t*>(&source.raceStats)+size_t(word)*2,2);
    result = wrapMultiply(territory.population, racial) / 10000;
    return true;
}

} // namespace

bool planNeeds(const save::Document& source, NeedsPlan& output, save::Error& error) {
    return guarded([&] {
        error = {};
        if (!validateSource(source, error)) return false;
        NeedsPlan candidate;
        candidate.territories.reserve(source.territories.size());
        // Original loops include the engine's territory0 sentinel. A Document
        // contains only physical territories1..N; no fictitious record is added.
        for (const auto& record : source.territories) {
            TerritoryNeeds needs;
            needs.territory = record.data.index;
            if (!foodNeed(source, record.data, needs.foodNeed, error)) return false;
            needs.energyNeed = energyNeed(source, record.data);
            // orig: FUN_0046b9a0 (RecordFoodEnergyNeeds): s16, then sign-extend.
            needs.foodReserve = signed16(needs.foodNeed);
            needs.energyReserve = signed16(needs.energyNeed);
            candidate.territories.push_back(needs);
        }
        output = std::move(candidate);
        error = {}; return true;
    }, error);
}

bool planEnergy(const save::Document& source, EnergyPlan& output, save::Error& error) {
    return guarded([&] {
        error = {};
        if (!validateSource(source, error)) return false;
        EnergyPlan candidate;
        candidate.territories.reserve(source.territories.size());
        for (const auto& record : source.territories) {
            const auto& territory = record.data;
            TerritoryEnergy change;
            change.territory = territory.index;
            change.energyBefore = territory.materials[2];
            change.need = energyNeed(source, territory);
            change.energyPercentBefore = territory.knowledge;
            // orig: FUN_0046bc28 (ConsumeEnergy). Comparison uses the full
            // signed min; only the amount SUBTRACTED narrows to signed16.
            const int32_t amount = std::min(change.energyBefore, change.need);
            change.consumed = signed16(amount);
            change.energyAfter = wrapSubtract(change.energyBefore, change.consumed);
            if (amount < change.need) {
                const int32_t numerator = wrapMultiply(amount, 100);
                if (change.need == 0 ||
                    (numerator == std::numeric_limits<int32_t>::min() && change.need == -1))
                    return invalid(error, territory.index, "energy shortage would execute an undefined signed division");
                const int32_t percent = std::max(50, numerator / change.need);
                change.energyPercentAfter = uint8_t(uint32_t(percent) & 0xffu);
                candidate.shortfalls.push_back({0x33, territory.owner, territory.index,
                                                100 - int(signed8(change.energyPercentAfter))});
            } else {
                change.energyPercentAfter = 100;
            }
            candidate.territories.push_back(change);
        }
        output = std::move(candidate);
        error = {}; return true;
    }, error);
}

} // namespace dl2::simulation
