#include "game/tax_phase.h"
#include "game/data_tables.h"

#include <algorithm>
#include <bit>
#include <new>
#include <stdexcept>
#include <string>
#include <utility>

namespace dl2::simulation {
namespace {

// DAT_004d5838 is now extracted as data::kTaxIncomePercent. The historical
// kTaxRates and kPopGrowthTable names refer to different/mislabelled data.

int32_t wrapAdd(int32_t a, int32_t b) {
    return std::bit_cast<int32_t>(uint32_t(a) + uint32_t(b));
}
int32_t wrapMultiply(int32_t a, int32_t b) {
    return std::bit_cast<int32_t>(uint32_t(a) * uint32_t(b));
}
int16_t narrowSigned16(int32_t value) {
    return std::bit_cast<int16_t>(uint16_t(uint32_t(value) & 0xffffu));
}

// orig: FUN_0046a9d8 (ISqrt). This is deliberately not std::sqrt: the original
// exits early for input magnitude 2 and returns +/-2 rather than +/-1. Its sole
// tax caller passes sign-extended Territory::population (int16_t), so abs and
// the trial square cannot overflow int32_t, including population == -32768.
int32_t originalPopulationRoot(int16_t population) {
    int32_t value = population;
    const bool negative = value < 0;
    if (negative) value = -value;
    int32_t root = 0;
    if (value > 0) {
        do {
            if (value < root * root) {
                --root;
                break;
            }
            ++root;
        } while (root < value);
    }
    return negative ? -root : root;
}

// orig: FUN_0044d1e4 (FindFinishedByCategory), category 9 = City Center.
// Original taxes test completion only, NOT Built/Active flags or owner race.
bool hasFinishedCityCenter(const save::Document& d, const Territory& territory) {
    for (const auto& site : territory.sites) {
        const auto* b = d.buildingById(site.building.raw);
        if (b && b->category == 9 && b->turnsLeft == 0) return true;
    }
    return false;
}

// orig: FUN_0046adac (EffectiveTaxLevel). +0x26 is the signed local tax
// adjustment, despite the historical Territory::tradeState field name.
int effectiveTaxLevel(const Player& player, const Territory& territory) {
    return std::clamp(int(player.taxLevel) + int(territory.tradeState), 0, 5);
}

// orig: FUN_0046ae1c (TerritoryTaxIncome). Preserve both integer divisions and
// the order of multiplication; combining percentages changes truncation.
int32_t territoryTaxIncome(const save::Document& d, const Player& player, const Territory& territory) {
    int32_t income = 0;
    if (player.index == territory.owner) {
        const int level = effectiveTaxLevel(player, territory);
        const int32_t populationRoot = originalPopulationRoot(territory.population);
        income = wrapMultiply(populationRoot, data::kTaxIncomePercent[size_t(level)]) / 100;
        // DAT_00559f6c = runtime RaceStats row 26, seven columns in saved state.
        income = wrapMultiply(d.raceStats.v[26][size_t(player.race)], income) / 100;
        if (hasFinishedCityCenter(d, territory)) income = wrapMultiply(income, 2);
    }
    if (d.options.fastProduction != 0) income = wrapMultiply(income, 2);
    return income;
}

bool invalid(save::Error& error, const Territory& territory, const char* message) {
    error = {save::ErrorCode::InvalidState, 0,
             "Tax territory " + std::to_string(territory.index) + ": " + message};
    return false;
}

} // namespace

bool planTaxes(const save::Document& d, TaxPlan& destination, save::Error& error) try {
    error = {};
    if (!save::validate(d, error)) return false;
    if (d.header.isMap != 0) {
        error = {save::ErrorCode::InvalidState, 0, "Tax planning requires a saved game, not a map"};
        return false;
    }
    TaxPlan candidate;
    for (size_t i = 0; i < d.players.size(); ++i) {
        candidate.creditsBefore[i] = d.players[i].credits;
        candidate.creditsAfter[i] = d.players[i].credits;
    }
    candidate.territories.reserve(d.territories.size());
    // orig: FUN_0046c728 (CollectTaxes), territories 1..N, no filters based on
    // player type/defeated flag/numPlayers, and a signed 16-bit cast PER territory.
    for (const auto& record : d.territories) {
        const auto& territory = record.data;
        const int owner = territory.owner;
        if (owner == -1) continue;
        if (owner < 0 || owner >= kMaxPlayers) return invalid(error, territory, "owner is outside -1..6");
        const auto& player = d.players[size_t(owner)];
        if (player.race < 0 || player.race >= 7) return invalid(error, territory, "owner race is outside 0..6");
        if (player.index != owner) return invalid(error, territory, "owner Player.index does not match its slot");
        const int32_t calculated = territoryTaxIncome(d, player, territory);
        const int16_t applied = narrowSigned16(calculated);
        candidate.territories.push_back({territory.index, owner, calculated, applied});
        candidate.collected[size_t(owner)] = wrapAdd(candidate.collected[size_t(owner)], applied);
        candidate.creditsAfter[size_t(owner)] = wrapAdd(candidate.creditsAfter[size_t(owner)], applied);
    }
    destination = std::move(candidate);
    error = {};
    return true;
} catch (const std::bad_alloc&) {
    error = {save::ErrorCode::Limit, 0, "Insufficient memory while planning taxes"};
    return false;
} catch (const std::length_error&) {
    error = {save::ErrorCode::Limit, 0, "Invalid allocation size while planning taxes"};
    return false;
} catch (const std::exception& exception) {
    error = {save::ErrorCode::InvalidState, 0, "Tax planning failed: " + std::string(exception.what())};
    return false;
}

} // namespace dl2::simulation
