// Active numeric checks from 0046b910/0046b958/0046b9a0/0046bc28.
#include "game/resource_needs.h"
#include "game/save_files.h"
#include "game/globals.h"
#include "game/rtl_compat.h"

#include <algorithm>
#include <array>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>

namespace {
using namespace dl2;
namespace fs = std::filesystem;
using simulation::NeedsPlan;
using simulation::EnergyPlan;

void require(bool value, const char* message) {
    if (!value) throw std::runtime_error(message);
}
std::unique_ptr<save::Document> fixture(int territories = 1) {
    auto d = std::make_unique<save::Document>();
    std::memcpy(d->header.text, save::kHeaderText, sizeof(save::kHeaderText));
    d->header.version = kSaveVersion; d->header.minusOne = -1; d->header.pad[51] = 0xab;
    d->options.numPlayers = 2; d->options.turn = 123;
    d->world.width = uint8_t(territories); d->world.height = 1;
    d->world.numTerritories = uint16_t(territories); d->world.rngSeed = 0x11223344;
    for (size_t p = 0; p < kMaxPlayers; ++p) {
        d->players[p].index = uint8_t(p); d->players[p].race = int8_t(p);
        d->players[p].credits = 1234 + int(p); d->raceStats.v[61][p] = 100;
        d->ministerJobs[p].resize(1);
    }
    d->players[0].type = 1;
    d->tiles.resize(size_t(territories)); d->territories.resize(size_t(territories));
    for (int i = 0; i < territories; ++i) {
        auto& t = d->territories[size_t(i)].data;
        t.index = uint16_t(i + 1); t.owner = 0; t.population = 1000; t.knowledge = 37;
        t.numTiles = 1; t.tiles[0].raw = uint32_t(i); t.materials[2] = 100;
        d->tiles[size_t(i)].x = uint8_t(i); d->tiles[size_t(i)].territory = int16_t(i + 1);
    }
    d->events.resize(1); d->options.eventCount = 1;
    d->events[0].record = {12, 4, 0, 99}; d->events[0].text = {'a', 0, 'b', 0xff};
    d->trailing = {0xde, 0xad, 0, 0xff};
    return d;
}
void addBuilding(save::Document& d, int type = 20, int territory = 1, int site = 0,
                 uint16_t flags = 4, int16_t work = 0) {
    Building b{};
    b.id = uint16_t(40000 + d.buildings.size()); b.type = uint8_t(type);
    b.territory = int16_t(territory); b.site = int8_t(site); b.flags = flags; b.turnsLeft = work;
    d.territories[size_t(territory - 1)].data.sites[size_t(site)].building.raw = b.id;
    d.buildings.push_back(b);
}
std::vector<uint8_t> encoded(const save::Document& d) {
    save::Error error; std::vector<uint8_t> bytes;
    if (!save::encode(d, bytes, error)) throw std::runtime_error(error.message);
    return bytes;
}
bool same(const NeedsPlan& a, const NeedsPlan& b) {
    if (a.territories.size() != b.territories.size()) return false;
    for (size_t i = 0; i < a.territories.size(); ++i) {
        const auto& x = a.territories[i]; const auto& y = b.territories[i];
        if (x.territory != y.territory || x.foodNeed != y.foodNeed || x.energyNeed != y.energyNeed ||
            x.foodReserve != y.foodReserve || x.energyReserve != y.energyReserve) return false;
    }
    return true;
}
bool same(const EnergyPlan& a, const EnergyPlan& b) {
    if (a.territories.size() != b.territories.size() || a.shortfalls.size() != b.shortfalls.size()) return false;
    for (size_t i = 0; i < a.territories.size(); ++i) {
        const auto& x = a.territories[i]; const auto& y = b.territories[i];
        if (x.territory != y.territory || x.energyBefore != y.energyBefore || x.need != y.need ||
            x.consumed != y.consumed || x.energyAfter != y.energyAfter ||
            x.energyPercentBefore != y.energyPercentBefore || x.energyPercentAfter != y.energyPercentAfter) return false;
    }
    for (size_t i = 0; i < a.shortfalls.size(); ++i) {
        const auto& x = a.shortfalls[i]; const auto& y = b.shortfalls[i];
        if (x.type != y.type || x.recipient != y.recipient || x.territory != y.territory || x.shortage != y.shortage) return false;
    }
    return true;
}
NeedsPlan needs(const save::Document& d) {
    const auto bytes = encoded(d);
    NeedsPlan output; save::Error error{save::ErrorCode::Io, 123, "stale"};
    if (!simulation::planNeeds(d, output, error)) throw std::runtime_error(error.message);
    require(error.code == save::ErrorCode::None && error.offset == 0 && error.message.empty(), "needs success clears error");
    require(encoded(d) == bytes, "needs mutated the input document");
    return output;
}
EnergyPlan energy(const save::Document& d) {
    const auto bytes = encoded(d);
    EnergyPlan output; save::Error error{save::ErrorCode::Io, 123, "stale"};
    if (!simulation::planEnergy(d, output, error)) throw std::runtime_error(error.message);
    require(error.code == save::ErrorCode::None && error.offset == 0 && error.message.empty(), "energy success clears error");
    require(encoded(d) == bytes, "energy mutated the input document or event log");
    return output;
}

void foodArithmetic() {
    auto d = fixture(); auto& t = d->territories[0].data;
    require(needs(*d).territories[0].foodNeed == 10, "population1000 * saved100 /10000");
    d->raceStats.v[61][0] = 50;
    require(needs(*d).territories[0].foodNeed == 5, "saved food modifier, not static race defaults");
    for (int16_t population : {int16_t(199), int16_t(-199)}) {
        t.population = population;
        require(needs(*d).territories[0].foodNeed == 0, "food division truncates toward zero");
    }
    t.population = -200;
    require(needs(*d).territories[0].foodNeed == -1, "negative population is signed, not clamped");
    d->raceStats.v[61][0] = -50;
    require(needs(*d).territories[0].foodNeed == 1, "negative saved modifier is signed");
    t.population = 32767; d->raceStats.v[61][0] = 32767;
    auto p = needs(*d).territories[0];
    require(p.foodNeed == 107367 && p.foodReserve == -23705, "record-needs narrows food requirement to s16");
    t.population = -32768; d->raceStats.v[61][0] = -32768;
    p = needs(*d).territories[0];
    require(p.foodNeed == 107374 && p.foodReserve == -23698, "signed16 extremes multiply without UB");
    d->raceStats.v[61][0] = 32767;
    p = needs(*d).territories[0];
    require(p.foodNeed == -107370 && p.foodReserve == 23702, "negative need narrowing sign-extends lower16");
    t.owner = -1; d->players[0].race = 127;
    require(needs(*d).territories[0].foodNeed == 0, "unowned territory needs no civilian food or valid player race");
    t.owner = 6; t.population = 1000;
    d->players[6].race = 6; d->players[6].type = 0; d->players[6].index = 99;
    d->raceStats.v[61][6] = 100; d->options.fastProduction = -1;
    require(needs(*d).territories[0].foodNeed == 10,
            "food need ignores type/index/numPlayers/fastProduction and uses owner slot");
    t.owner=0; d->players[0].race=-1; d->raceStats.v[60][6]=230;
    require(needs(*d).territories[0].foodNeed==23,"signed race-1 physically reads row60column6");
    d->players[0].race=7; d->raceStats.v[62][0]=310;
    require(needs(*d).territories[0].foodNeed==31,"race7 physically reads row62column0 without normalization");
}

void buildingConditions() {
    auto d = fixture();
    addBuilding(*d, 20, 1, 0, 4);     //40: Active without Built.
    addBuilding(*d, 7, 1, 1, 2);      //Inactive, ignored.
    addBuilding(*d, 4, 1, 2, 6, 1);   //Unfinished, ignored.
    addBuilding(*d, 4, 1, 3, 6, -1);  //Only EXACTLY zero work qualifies.
    addBuilding(*d, 16, 1, 4, 4);     //25.
    addBuilding(*d, 7, 1, 35, 4);     //10, final site must participate.
    auto p = needs(*d).territories[0];
    require(p.energyNeed == 75 && p.energyReserve == 75, "energy building condition/site-order oracle");
    d->buildings[0].flags |= 2; d->buildings[0].category = 0xff;
    require(needs(*d).territories[0].energyNeed == 75, "Built/category/labor are not energy predicates");
    d->territories[0].data.owner = -1;
    require(needs(*d).territories[0].energyNeed == 75, "unowned building energy is not silently skipped");
    d = fixture();
    for (int site = 0; site < kNumSites; ++site) addBuilding(*d, 20, 1, site);
    require(needs(*d).territories[0].energyNeed == 1440, "all36 sites contribute the signed byte40");
}

void oneEnergy(save::Document& d, int32_t stock, int16_t consumed, int32_t after,
               uint8_t percent, int shortage = -1) {
    d.territories[0].data.materials[2] = stock;
    const auto p = energy(d);
    require(p.territories.size() == 1, "one physical territory, no invented sentinel0");
    const auto& t = p.territories[0];
    require(t.territory == 1 && t.energyBefore == stock && t.need == 40 &&
            t.consumed == consumed && t.energyAfter == after &&
            t.energyPercentBefore == d.territories[0].data.knowledge && t.energyPercentAfter == percent,
            "energy arithmetic oracle");
    if (shortage == -1) require(p.shortfalls.empty(), "sufficient energy must not produce a shortfall");
    else require(p.shortfalls.size() == 1 && p.shortfalls[0].type == 0x33 &&
                 p.shortfalls[0].recipient == d.territories[0].data.owner && p.shortfalls[0].territory == 1 &&
                 p.shortfalls[0].shortage == shortage, "semantic shortage event fields");
}

void energyArithmetic() {
    auto d = fixture(); addBuilding(*d);
    oneEnergy(*d, 100, 40, 60, 100);
    oneEnergy(*d, 40, 40, 0, 100);
    oneEnergy(*d, 39, 39, 0, 97, 3);
    oneEnergy(*d, 20, 20, 0, 50, 50);
    oneEnergy(*d, 19, 19, 0, 50, 50);
    oneEnergy(*d, 0, 0, 0, 50, 50);
    oneEnergy(*d, -1, -1, 0, 50, 50);
    oneEnergy(*d, -32769, 32767, -65536, 50, 50);
    oneEnergy(*d, std::numeric_limits<int32_t>::min(), 0, std::numeric_limits<int32_t>::min(), 50, 50);
    // Multiplication wraps BEFORE division; percent stores a byte, and the event
    // interprets that byte as signed. These are derived CPU-arithmetic oracles.
    oneEnergy(*d, -21474837, 20971, -21495808, 49, 51);
    oneEnergy(*d, -21474897, 20911, -21495808, 155, 201);
    d->territories[0].data.owner = -1;
    oneEnergy(*d, 0, 0, 0, 50, 50); // Semantic recipient -1 retained, never dispatched.
    d = fixture();
    d->territories[0].data.knowledge = 255;
    auto p = energy(*d);
    require(p.territories[0].need == 0 && p.territories[0].consumed == 0 &&
            p.territories[0].energyAfter == 100 && p.territories[0].energyPercentAfter == 100 && p.shortfalls.empty(),
            "zero need resets power to100 without dividing");
    d->territories[0].data.materials[2] = 0;
    require(energy(*d).territories[0].energyPercentAfter == 100, "zero stock with zero need is sufficient");
}

void transactionality() {
    auto d = fixture(2); addBuilding(*d, 20, 1);
    d->territories[0].data.materials[2] = 0;
    NeedsPlan n = needs(*d); EnergyPlan e = energy(*d);
    const auto priorN = n; const auto priorE = e;
    auto failure = [&](bool ok, const save::Error& error) {
        require(!ok && error.code != save::ErrorCode::None && !error.message.empty(), "failure requires diagnostic");
        require(same(n, priorN) && same(e, priorE), "failed plan replaced the prior output");
    };
    save::Error error;
    d->players[0].race = 127; //row61+127 lies OUTSIDE the actual saved block.
    failure(simulation::planNeeds(*d, n, error), error);
    // Energy has no race dependency and must not inherit food-only validation.
    require(simulation::planEnergy(*d, e, error) && same(e, priorE), "energy does not read owner race");
    d->players[0].race = 0;
    d->territories[1].data.materials[2] = -1; //need0 -> original divide by zero.
    const auto original = encoded(*d);
    failure(simulation::planEnergy(*d, e, error), error);
    require(encoded(*d) == original, "late energy failure changed source or partial events");
    d->territories[1].data.materials[2] = 100;
    d->territories[0].data.sites[0].building.raw = 65535;
    failure(simulation::planNeeds(*d, n, error), error);
    failure(simulation::planEnergy(*d, e, error), error);
    d = fixture(); d->territories[0].data.owner = 7;
    failure(simulation::planNeeds(*d, n, error), error);
    failure(simulation::planEnergy(*d, e, error), error);
    auto map = std::make_unique<save::Document>();
    map->header = d->header; map->header.isMap = 1; map->world = d->world;
    map->tiles = d->tiles; map->mapTerritories.resize(1);
    require(save::validate(*map, error), "valid physical map fixture");
    failure(simulation::planNeeds(*map, n, error), error);
    failure(simulation::planEnergy(*map, e, error), error);
}

std::vector<std::string> scenarioNames(const fs::path& path) {
    const auto size = fs::file_size(path);
    require(size >= 4 && size <= save::kMaxFileBytes, "invalid optional corpus index size");
    std::ifstream file(path, std::ios::binary); uint8_t c[4]{};
    require(bool(file.read(reinterpret_cast<char*>(c), 4)), "read corpus count");
    const uint32_t count = uint32_t(c[0]) | uint32_t(c[1]) << 8 | uint32_t(c[2]) << 16 | uint32_t(c[3]) << 24;
    require(count <= (size - 4) / 12, "truncated corpus index");
    std::vector<std::string> names;
    for (uint32_t i = 0; i < count; ++i) {
        char record[12]{}; require(bool(file.read(record, 12)), "read corpus index entry");
        names.emplace_back(record, std::find(record, record + 8, '\0'));
    }
    return names;
}
void corpus(const fs::path& directory) {
    if (directory.empty() || !fs::is_regular_file(directory / "TUTORIAL.SAV")) {
        std::cout << "resource needs: optional original corpus unavailable\n"; return;
    }
    size_t count = 0, shortfalls = 0;
    auto check = [&](const save::Document& d) {
        const auto n = needs(d); const auto e = energy(d);
        require(same(n, needs(d)) && same(e, energy(d)), "resource plans must be deterministic");
        require(n.territories.size() == d.territories.size() && e.territories.size() == d.territories.size(),
                "all physical territories must be reported");
        for (size_t i = 0; i < n.territories.size(); ++i)
            require(n.territories[i].energyNeed == e.territories[i].need, "need and energy projections disagree");
        ++count; shortfalls += e.shortfalls.size();
    };
    for (const char* relative : {"TUTORIAL.SAV", "Saves/AUTOSAVE.SAV", "Campaign/AUTOSAVE.CPN", "Campaign/ChCht001.CPN"}) {
        if (!fs::is_regular_file(directory / relative)) continue;
        auto d = std::make_unique<save::Document>(); save::Error error;
        if (!save::readDocument(directory / relative, *d, error)) throw std::runtime_error(error.message);
        check(*d);
    }
    if (fs::is_regular_file(directory / "LEVELS.HDX") && fs::is_regular_file(directory / "LEVELS.HDD")) {
        for (const auto& name : scenarioNames(directory / "LEVELS.HDX")) {
            auto d = std::make_unique<save::Document>(); save::Error error;
            if (!save::readScenario(directory / "LEVELS", name, *d, error)) throw std::runtime_error(error.message);
            try { check(*d); } catch (const std::exception& e) { throw std::runtime_error(name + ": " + e.what()); }
        }
    }
    std::cout << "resource corpus: " << count << " deterministic immutable plans, " << shortfalls << " semantic shortfalls\n";
}
} // namespace

int main(int argc, char** argv) {
    try {
        gs.options.turn = 54321; gg.netGame = 1; gg.rng2Seed = 0xaabbccdd;
        rtl::srand(0x12345678); (void)rtl::lrand();
        const auto lo = rtl::seed(), hi = rtl::seedHi();
        const auto* global = reinterpret_cast<const uint8_t*>(&gs);
        const std::vector<uint8_t> gsBefore(global, global + sizeof(gs));
        const auto* loose = reinterpret_cast<const uint8_t*>(&gg);
        const std::vector<uint8_t> ggBefore(loose, loose + sizeof(gg));
        foodArithmetic(); buildingConditions(); energyArithmetic(); transactionality();
        corpus(argc > 1 ? fs::path(argv[1]) : fs::path{});
        require(std::memcmp(gsBefore.data(), &gs, sizeof(gs)) == 0 &&
                std::memcmp(ggBefore.data(), &gg, sizeof(gg)) == 0, "resource planning changed legacy globals");
        require(rtl::seed() == lo && rtl::seedHi() == hi, "resource planning consumed RNG");
        std::cout << "resource needs: formulas, energy conditions, events, arithmetic and transactionality passed\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "resource needs: " << error.what() << '\n'; return 1;
    }
}
