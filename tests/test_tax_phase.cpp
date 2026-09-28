// Numeric oracles from FUN_0046adac/0046ae1c/0046c728, not inferred game rules.
#include "game/tax_phase.h"
#include "game/globals.h"
#include "game/rtl_compat.h"

#include <array>
#include <cstring>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>

namespace {
using namespace dl2;
using simulation::TaxPlan;

void require(bool condition, const char* message) {
    if (!condition) throw std::runtime_error(message);
}

std::unique_ptr<save::Document> fixture(int count = 1) {
    auto d = std::make_unique<save::Document>();
    std::memcpy(d->header.text, save::kHeaderText, sizeof(save::kHeaderText));
    d->header.version = kSaveVersion;
    d->options.numPlayers = 1;
    d->options.localPlayer = 0;
    d->options.turn = 41;
    d->world.width = uint8_t(count);
    d->world.height = 1;
    d->world.numTerritories = uint16_t(count);
    d->world.rngSeed = 0x12345678;
    for (int p = 0; p < kMaxPlayers; ++p) {
        d->players[size_t(p)].index = uint8_t(p);
        d->players[size_t(p)].race = 2;
        d->players[size_t(p)].taxLevel = 2;
        d->players[size_t(p)].credits = 1000 + p;
        d->raceStats.v[26][p] = 100;
        d->ministerJobs[size_t(p)].resize(1);
    }
    d->players[0].type = 1;
    d->territories.resize(size_t(count));
    d->tiles.resize(size_t(count));
    for (int i = 0; i < count; ++i) {
        auto& t = d->territories[size_t(i)].data;
        t.index = uint16_t(i + 1);
        t.owner = 0;
        t.population = 1000;
        t.numTiles = 1;
        t.tiles[0].raw = uint32_t(i);
        d->tiles[size_t(i)].x = uint8_t(i);
        d->tiles[size_t(i)].territory = int16_t(i + 1);
    }
    return d;
}

std::vector<uint8_t> encode(const save::Document& d) {
    std::vector<uint8_t> bytes;
    save::Error error;
    require(save::encode(d, bytes, error), "valid tax fixture encoding");
    return bytes;
}

TaxPlan plan(const save::Document& d) {
    const auto before = encode(d);
    TaxPlan result;
    save::Error error{save::ErrorCode::Io, 999, "stale error"};
    if (!simulation::planTaxes(d, result, error))
        throw std::runtime_error("tax plan: " + error.message);
    require(error.code == save::ErrorCode::None && error.offset == 0 && error.message.empty(),
            "successful plan clears prior error");
    require(encode(d) == before, "planning never modifies source bytes");
    return result;
}

void oneTax(const save::Document& d, int32_t calculated, int16_t applied) {
    const auto result = plan(d);
    require(result.territories.size() == 1, "one owned territory report");
    require(result.territories[0].territory == 1 && result.territories[0].owner == 0,
            "territory report identifies source");
    require(result.territories[0].calculated == calculated && result.territories[0].applied == applied,
            "numeric income oracle");
    require(result.collected[0] == applied, "collected sums narrowed amounts");
}

void addCity(save::Document& d, int site = 0) {
    Building b{};
    b.id = uint16_t(d.buildings.size() + 1);
    b.type = 37;
    b.category = 9;
    b.territory = 1;
    b.site = int8_t(site);
    // No Built or Active flag: the original tax multiplier does not require them.
    d.territories[0].data.sites[size_t(site)].building.raw = b.id;
    d.buildings.push_back(b);
}

void rootAndRounding() {
    auto d = fixture();
    d->players[0].taxLevel = 3; // 100%, saved race modifier also 100%.
    constexpr std::array<int16_t, 20> populations{
        0, 1, 2, 3, 4, 8, 9, 15, 16, -1, -2, -3, -4, -8, -9, -15, -16,
        std::numeric_limits<int16_t>::min(), 32766, 32767};
    constexpr std::array<int16_t, 20> roots{
        0, 1, 2, 1, 2, 2, 3, 3, 4, -1, -2, -1, -2, -2, -3, -3, -4, -181, 181, 181};
    for (size_t i = 0; i < populations.size(); ++i) {
        d->territories[0].data.population = populations[i];
        oneTax(*d, roots[i], roots[i]);
    }
    d->territories[0].data.population = 99; // Original root = 9.
    d->players[0].taxLevel = 1; // 40%: 9*40/100 = 3, not 3.6.
    d->raceStats.v[26][2] = 120; // 3*120/100 = 3, NOT floor(9*.4*1.2)=4.
    oneTax(*d, 3, 3);
    d->territories[0].data.population = -99;
    oneTax(*d, -3, -3); // Signed division truncates toward zero, not floor.
    d->raceStats.v[26][2] = -120;
    oneTax(*d, 3, 3); // Signed saved modifiers are not silently clamped.
}

void levelsAndMultipliers() {
    auto d = fixture(); // root(1000)=31, saved race modifier=100.
    constexpr std::array<int16_t, 6> incomes{0, 12, 23, 31, 38, 46};
    for (int level = 0; level < 6; ++level) {
        d->players[0].taxLevel = int8_t(level);
        oneTax(*d, incomes[size_t(level)], incomes[size_t(level)]);
    }
    d->players[0].taxLevel = 2;
    d->raceStats.v[26][2] = 120;
    oneTax(*d, 27, 27);
    addCity(*d);
    oneTax(*d, 54, 54);
    d->buildings[0].flags = 6;
    oneTax(*d, 54, 54); // Active/Built flags do not change the tax test.
    d->buildings[0].turnsLeft = 1;
    oneTax(*d, 27, 27);
    d->buildings[0].turnsLeft = -1;
    oneTax(*d, 27, 27); // Only exactly zero is completed.
    d->buildings[0].turnsLeft = 0;
    d->buildings[0].category = 8;
    oneTax(*d, 27, 27); // Category, not merely type 37, drives original lookup.
    d->buildings[0].category = 9;
    addCity(*d, 1);
    oneTax(*d, 54, 54); // Multiple City Centers do not stack the multiplier.
    d->options.fastProduction = -7;
    oneTax(*d, 108, 108); // Any nonzero fastProduction enables the multiplier.
    d->territories[0].data.tradeState = 1;
    oneTax(*d, 148, 148); // (31*100/100)*120/100 =37, then city2 and fast2.
    d->territories[0].data.taxAdjust = 32767;
    oneTax(*d, 148, 148); // +0x2a is NOT the signed local tax byte at +0x26.
    d->territories[0].data.tradeState = -128;
    oneTax(*d, 0, 0);
    d->players[0].taxLevel = 127;
    d->territories[0].data.tradeState = 127;
    oneTax(*d, 220, 220); // Effective level capped at5: 31*150/100=46; *120/100=55.

    // No tech mask grants a tax multiplier; never substitute an unrelated rule.
    for (auto& tech : d->techs) tech.knownMask = 0xffffu;
    oneTax(*d, 220, 220);
}

void narrowingAndCredits() {
    auto d = fixture();
    d->territories[0].data.population = 32767; // root181.
    d->players[0].taxLevel = 5; // 181*150/100 =271.
    d->raceStats.v[26][2] = 32767; // 271*32767/100 =88798 (integer).
    addCity(*d);
    d->options.fastProduction = 1;
    oneTax(*d, 355192, 27512); // 88798*2*2; lower16 bits 27512.
    d->options.fastProduction = 0;
    oneTax(*d, 177596, -19012); // Signed narrowing is observable, not saturation.
    d->buildings[0].turnsLeft = 1;
    oneTax(*d, 88798, 23262);

    d = fixture();
    d->players[0].credits = std::numeric_limits<int32_t>::max() - 10;
    auto result = plan(*d); // +23 wraps, as 32-bit Borland signed add on the CPU.
    require(result.creditsAfter[0] == std::numeric_limits<int32_t>::min() + 12,
            "credit addition wraps without C++ signed overflow");
    require(result.creditsBefore[0] == d->players[0].credits, "credits before captured exactly");
    d->players[0].credits = std::numeric_limits<int32_t>::min() + 10;
    d->territories[0].data.population = -1000;
    result = plan(*d);
    require(result.creditsAfter[0] == std::numeric_limits<int32_t>::max() - 12,
            "negative income credit wrap defined");

    d = fixture(3);
    d->territories[1].data.owner = -1;
    d->territories[2].data.owner = 6;
    d->players[6].type = 0;
    d->players[6].defeated = 1;
    result = plan(*d);
    require(result.territories.size() == 2 && result.territories[0].territory == 1 &&
            result.territories[1].territory == 3, "unowned skipped and file order retained");
    require(result.collected[0] == 23 && result.collected[6] == 23,
            "owned territory taxed even if player type/defeated/numPlayers would hide it in UI");
    require(result.creditsAfter[6] == 1029, "last player slot updated");
    for (size_t p = 1; p < 6; ++p)
        require(result.collected[p] == 0 && result.creditsBefore[p] == result.creditsAfter[p],
                "unaffected player credits preserved");
    d->territories[1].data.owner = 0;
    result = plan(*d);
    require(result.collected[0] == 46 && result.creditsAfter[0] == 1046, "multiple territories accumulate");
}

bool equalPlan(const TaxPlan& a, const TaxPlan& b) {
    if (a.creditsBefore != b.creditsBefore || a.creditsAfter != b.creditsAfter ||
        a.collected != b.collected || a.territories.size() != b.territories.size()) return false;
    for (size_t i = 0; i < a.territories.size(); ++i) {
        const auto& x = a.territories[i]; const auto& y = b.territories[i];
        if (x.territory != y.territory || x.owner != y.owner || x.calculated != y.calculated || x.applied != y.applied)
            return false;
    }
    return true;
}

void rejectionAndPurity() {
    auto d = fixture(2);
    TaxPlan destination = plan(*d);
    const TaxPlan previous = destination;
    save::Error error;
    auto fails = [&] {
        require(!simulation::planTaxes(*d, destination, error), "bad tax domain must fail");
        require(error.code != save::ErrorCode::None && !error.message.empty(), "failed plan has explicit error");
        require(equalPlan(destination, previous), "failed plan leaves destination unchanged after partial evaluation");
    };
    d->territories[1].data.owner = 7;
    fails();
    d->territories[1].data.owner = -2;
    fails();
    d->territories[1].data.owner = 6;
    d->players[6].race = 7;
    fails();
    d->players[6].race = -1;
    fails();
    d->players[6].race = 2;
    d->players[6].index = 0;
    fails();
    d->players[6].index = 6;
    d->territories[1].data.index = 9;
    fails(); // Codec validation also remains a prerequisite.
    d->territories[1].data.index = 2;
    d->header.isMap = 1;
    d->mapTerritories.resize(2);
    fails(); // Structurally valid map, but not an executable economic document.
    d->header.isMap = 0;

    // No gs/gg, RNG, callbacks or turn change are permitted while planning.
    std::vector<uint8_t> globalState(sizeof(gs)), globalMisc(sizeof(gg));
    std::memcpy(globalState.data(), &gs, sizeof(gs));
    std::memcpy(globalMisc.data(), &gg, sizeof(gg));
    const auto seed = rtl::seed();
    const auto seedHi = rtl::seedHi();
    const auto first = plan(*d);
    const auto second = plan(*d);
    require(equalPlan(first, second), "identical input gives identical plans");
    require(std::memcmp(globalState.data(), &gs, sizeof(gs)) == 0 &&
            std::memcmp(globalMisc.data(), &gg, sizeof(gg)) == 0 && rtl::seed() == seed && rtl::seedHi() == seedHi,
            "tax planning does not mutate globals or RNG");
    require(d->options.turn == 41 && d->world.rngSeed == 0x12345678,
            "tax subphase never increments turn or stored seed");
}

} // namespace

int main() {
    try {
        rootAndRounding();
        levelsAndMultipliers();
        narrowingAndCredits();
        rejectionAndPurity();
        std::cout << "tax_phase: original rounding, multipliers, signed narrowing, wrap, validation and purity passed\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "tax_phase: " << error.what() << '\n';
        return 1;
    }
}
