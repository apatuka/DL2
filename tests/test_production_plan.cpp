// Numeric oracles derived from the original functions/assembly, not observed
// original-game execution. No production turn pass is applied by these queries.
#include "game/production_plan.h"
#include "game/data_tables.h"
#include "game/save_files.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include "formats/hdx_archive.h"

#include <algorithm>
#include <bit>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>

namespace {
using namespace dl2;
using simulation::ProductionPlan;

void require(bool condition, const char* message) {
    if (!condition) throw std::runtime_error(message);
}

std::unique_ptr<save::Document> fixture() {
    auto d = std::make_unique<save::Document>();
    std::memcpy(d->header.text, save::kHeaderText, sizeof(save::kHeaderText));
    d->header.version = kSaveVersion;
    d->options.numPlayers = 1; d->options.localPlayer = 0; d->options.turn = 41;
    d->world.width = 2; d->world.height = 1; d->world.numTerritories = 2;
    d->world.rngSeed = 0x12345678;
    for (int p = 0; p < kMaxPlayers; ++p) {
        d->players[size_t(p)].index = uint8_t(p);
        d->players[size_t(p)].race = 2;
        d->ministerJobs[size_t(p)].resize(1);
        for (int row = 0; row < kNumRaceStatRows; ++row) d->raceStats.v[row][p] = 100;
    }
    d->players[0].type = 1;
    d->territories.resize(2); d->tiles.resize(2);
    for (int i = 0; i < 2; ++i) {
        auto& t = d->territories[size_t(i)].data;
        t.index = uint16_t(i + 1); t.owner = i == 0 ? 0 : -1;
        t.terrain = 1; t.population = 500; t.knowledge = 100;
        t.numTiles = 1; t.tiles[0].raw = uint32_t(i);
        d->tiles[size_t(i)].x = uint8_t(i); d->tiles[size_t(i)].territory = int16_t(i + 1);
        for (int s = 0; s < kNumSites; ++s) {
            auto& site = t.sites[size_t(s)];
            site.unk_00 = uint16_t((s % 6) | ((s / 6) << 8));
            site.terrainFlags = 1; site.value = 1;
            for (int resource = 0; resource < 5; ++resource) {
                site.unk_05[1 + resource * 2] = uint8_t(10000 & 0xff);
                site.unk_05[2 + resource * 2] = uint8_t(10000 >> 8);
            }
        }
    }
    return d;
}

Building& addBuilding(save::Document& d, uint8_t type, int site, int territory = 1) {
    Building b{};
    b.id = uint16_t(100 + d.buildings.size()); b.type = type;
    b.category = data::kBuildingTypes[type].category;
    b.flags = 6; b.site = int8_t(site); b.territory = int16_t(territory);
    std::copy_n(data::kBuildingTypes[type].tasks, 5, b.task);
    d.territories[size_t(territory - 1)].data.sites[size_t(site)].building.raw = b.id;
    d.buildings.push_back(b);
    return d.buildings.back();
}

std::vector<uint8_t> encode(const save::Document& d) {
    save::Error error;
    std::vector<uint8_t> bytes;
    if (!save::encode(d, bytes, error)) throw std::runtime_error("fixture encoding: " + error.message);
    return bytes;
}

ProductionPlan plan(const save::Document& d) {
    const auto before = encode(d);
    ProductionPlan result;
    save::Error error{save::ErrorCode::Io, 999, "stale"};
    if (!simulation::planProduction(d, result, error)) throw std::runtime_error(error.message);
    require(error.code == save::ErrorCode::None && error.offset == 0 && error.message.empty(),
            "success clears the previous production error");
    require(encode(d) == before, "production queries preserve exact document bytes");
    return result;
}

int32_t scalar(const save::Document& d, uint32_t id, int slot, int32_t labor) {
    int32_t result = -123;
    save::Error error{save::ErrorCode::Io, 999, "stale"};
    if (!simulation::taskOutput(d, id, slot, labor, result, error)) throw std::runtime_error(error.message);
    require(error.code == save::ErrorCode::None && error.offset == 0 && error.message.empty(),
            "success clears the previous scalar error");
    return result;
}

void numericalOutputs() {
    auto d = fixture();
    addBuilding(*d, 1, 0); // Completed Built housing enables hypothetical labor.
    auto& farm = addBuilding(*d, 6, 14); // 2x2 footprint: 14,15,8,9.
    farm.labor[1] = 3; farm.labor[2] = 3;
    auto& t = d->territories[0].data;
    t.unk_8b0[0xe4] = 25;
    auto report = plan(*d);
    const auto& output = report.territories[0].buildings[1];
    require(output.buildingId == farm.id && output.site == 14 && output.maxLabor == 6 && output.evaluated,
            "report identifies producer and its capacity");
    // Food: 54*100*100*120/100000=648; /10=64; 64*6*40000/80000=192;
    // saved food/wood bonus adds short(25*192/100)=48, giving 240.
    require(output.assigned[1] == simulation::SlotProduction{12, 3, 240}, "assigned food oracle");
    // Wood: 810/10=81; no matching richness bonus, 81 + short(81*25/100)=101.
    require(output.assigned[2].output == 101, "assigned wood intermediate truncation");
    require(output.maximum[1] == simulation::SlotProduction{12, 6, 450} && output.maximum[2].output == 187,
            "maximum outputs use independent full labor and preserve truncation");
    require(scalar(*d, farm.id, 1, 3) == 192 && scalar(*d, farm.id, 2, 3) == 81,
            "scalar query deliberately lacks the batch food/wood bonus");
    t.flags |= 0x40;
    require(plan(*d).territories[0].buildings[1].assigned[1].output == 120 && scalar(*d, farm.id, 1, 3) == 96,
            "poison halves food after bonus; wood is unaffected");
    t.flags &= ~0x40u;
    d->options.fastProduction = 1;
    require(plan(*d).territories[0].buildings[1].assigned[1].output == 480 && scalar(*d, farm.id, 1, 3) == 384,
            "fast natural production doubles before richness and bonus");
    d->options.fastProduction = 0;
    t.knowledge = 50;
    require(plan(*d).territories[0].buildings[1].assigned[1].output == 120 &&
            plan(*d).territories[0].buildings[1].maximum[1].output == 450,
            "assigned output uses energy satisfaction; maximum ignores it");
    t.knowledge = 255; // Signed -1, never interpreted as 255%.
    require(scalar(*d, farm.id, 1, 3) == 1, "signed energy satisfaction and minimum-one rule");
    t.knowledge = 100;
    farm.flags = 4; // No Built bit: TaskOutputs still computes it.
    require(plan(*d).territories[0].buildings[1].assigned[1].output == 240,
            "query needs Active but not Built");
    farm.flags = 2;
    report = plan(*d);
    require(report.territories[0].buildings[1].assigned[1].output == 0 &&
            report.territories[0].buildings[1].maximum[1].output == 450 && scalar(*d, farm.id, 1, 3) == 0,
            "inactive assigned/scalar return zero but maximum still evaluates");
}

void emptyTasksConstructionAndWrap() {
    auto d = fixture();
    addBuilding(*d, 1, 0);
    auto& farm = addBuilding(*d, 6, 14);
    farm.labor[1] = 3;
    require(plan(*d).territories[0].buildings[1].assigned[0] == simulation::SlotProduction{},
            "unused first slot is safely normalized instead of reading original uninitialized stack");
    farm.labor[4] = 7;
    require(plan(*d).territories[0].buildings[1].assigned[4] == simulation::SlotProduction{},
            "unused later slot does not inherit the prior slot's labor");
    require(scalar(*d, farm.id, 0, 7) == 1 && scalar(*d, farm.id, 0, 0) == 0,
            "defined scalar empty-task behavior is distinct from batch normalization");
    farm.turnsLeft = 10; farm.task[0] = 2; farm.labor[0] = 2;
    d->territories[0].data.knowledge = 0;
    require(plan(*d).territories[0].buildings[1].maxLabor == 4 && scalar(*d, farm.id, 0, 2) == 50,
            "construction capacity four and no power penalty before completion");
    farm.turnsLeft = 0; farm.task[0] = 0; farm.labor[0] = 0;
    farm.task[1] = 63; farm.labor[1] = 3;
    d->territories[0].data.knowledge = 100; d->raceStats.v[63][2] = 125;
    require(scalar(*d, farm.id, 1, 3) == 81 && plan(*d).territories[0].buildings[1].assigned[1].output == 81,
            "valid unnamed task row63 is not arbitrarily rejected");
    d->raceStats.v[63][2] = 32767; d->territories[0].data.knowledge = 127;
    // 100*127*32767*120 wraps to -1602699552; /100000=-16026;
    // (-16026+9)/10=-1601, finally raised to 1 for nonzero labor.
    require(scalar(*d, farm.id, 1, 6) == 1, "32-bit multiply wraps before signed division");
    require(scalar(*d, farm.id, 1, std::numeric_limits<int32_t>::max()) == 1,
            "large labor uses row6/column10 zero then minimum1, never an out-of-bounds access");
}

void shrineAndPopulation() {
    auto d = fixture();
    addBuilding(*d, 1, 0);
    auto& shrine = addBuilding(*d, 45, 14);
    shrine.labor[1] = 2; shrine.labor[2] = 2;
    require(scalar(*d, shrine.id, 1, 2) == 20 && scalar(*d, shrine.id, 2, 2) == 30,
            "shrine category doubles culture/research");
    d->techs[33].knownMask = 1;
    d->options.fastProduction = 1;
    require(scalar(*d, shrine.id, 1, 2) == 40 && scalar(*d, shrine.id, 2, 2) == 60,
            "Native Languages doubles shrine output; fast excludes culture/research");
    shrine.type = 46; shrine.category = 11; shrine.task[1] = 0; shrine.labor[1] = 1;
    d->options.fastProduction = 0; d->techs[33].knownMask = 0;
    // (territory1 + site14)%9=6 -> task8/rate50, row3 labor1=33%.
    auto report = plan(*d);
    require(report.territories[0].buildings[1].assigned[1] == simulation::SlotProduction{8, 1, 33},
            "hidden shrine overrides saved/default task and static rate");
    require(scalar(*d, shrine.id, 1, 1) == 33, "scalar shares dynamic shrine selection");
    shrine.type = 47;
    // (1+14)%6=3 -> energy15, rate100; natural footprint is size1.
    require(plan(*d).territories[0].buildings[1].assigned[1].task == 15,
            "sea shrine task derives from territory plus site modulo six");
    shrine.type = 46;
    shrine.site = 2;
    d->territories[0].data.sites[14].building.raw = 0;
    d->territories[0].data.sites[2].building.raw = shrine.id;
    d->territories[0].data.sites[2].terrainFlags = 4;
    require(plan(*d).territories[0].buildings[1].assigned[1].task == 3,
            "hidden shrine initial modulo0..5 is remapped by terrain low nibble");

    auto other = fixture();
    addBuilding(*other, 1, 0).flags = 2; // Built but inactive housing contributes.
    auto& f = addBuilding(*other, 6, 14);
    f.labor[1] = 3;
    require(plan(*other).territories[0].buildings[1].maximum[1].labor == 6,
            "inactive completed Built housing contributes population capacity");
    other->buildings[0].flags = 4;
    require(plan(*other).territories[0].buildings[1].maximum[1].labor == 0,
            "active housing without Built does not provide hypothetical population");
    other->buildings[0].flags = 2;
    other->raceStats.v[24][2] = 200;
    require(plan(*other).territories[0].buildings[0].maxLabor == 10,
            "housing capacity uses saved racial row24");
    other->territories[0].data.terrain = 0;
    for (auto& site : other->territories[0].data.sites) site.terrainFlags = 5;
    require(plan(*other).territories[0].buildings[1].maximum[1].labor == 0,
            "zero habitable land caps hypothetical population at zero");
    addBuilding(*other, 38, 35).flags = 0; // Category-only sea platform, even inactive/unfinished.
    require(plan(*other).territories[0].buildings[1].maximum[1].labor == 6,
            "sea-platform category supplies the original sea population ceiling");
}

void validationAndPurity() {
    auto d = fixture();
    addBuilding(*d, 1, 0);
    addBuilding(*d, 6, 14).labor[1] = 3;
    addBuilding(*d, 45, 14, 2);
    ProductionPlan destination = plan(*d);
    require(destination.territories.size() == 2 && !destination.territories[1].buildings[0].evaluated,
            "unowned territory/building retained without fabricated production");
    // Real saves leave unused slots at index0; their race/index are not read.
    for (size_t p = 1; p < d->players.size(); ++p) {
        d->players[p].index = 0;
        d->players[p].race = -1;
    }
    require(plan(*d) == destination && scalar(*d, 101, 1, 3) == 192,
            "unused player index/race do not restrict production queries");
    const auto prior = destination;
    save::Error error;
    auto fails = [&] {
        require(!simulation::planProduction(*d, destination, error) && error.code != save::ErrorCode::None,
                "invalid production domain must fail explicitly");
        require(destination == prior, "failure preserves prior report even after partial evaluation");
    };
    d->buildings[1].labor[1] = -1; fails(); d->buildings[1].labor[1] = 3;
    d->buildings[1].task[1] = 64; fails(); d->buildings[1].task[1] = 12;
    d->buildings[1].type = 48; fails(); d->buildings[1].type = 6;
    d->players[0].race = 7; fails(); d->players[0].race = 2;
    d->players[0].index = 6; fails(); d->players[0].index = 0;
    d->territories[1].data.owner = -2; fails(); d->territories[1].data.owner = -1;
    d->territories[0].data.sites[14].unk_00 = 0; fails();
    d->territories[0].data.sites[14].unk_00 = 0x202;
    d->buildings[1].site = 5;
    d->territories[0].data.sites[14].building.raw = 0;
    d->territories[0].data.sites[5].building.raw = d->buildings[1].id;
    fails(); // 2x2 footprint leaves grid despite valid anchor bytes [5,0].
    d->buildings[1].site = 14;
    d->territories[0].data.sites[5].building.raw = 0;
    d->territories[0].data.sites[14].building.raw = d->buildings[1].id;
    d->raceStats.v[24][2] = -100; fails(); d->raceStats.v[24][2] = 100;
    int32_t output = 12345;
    for (const int slot : {-1, 5}) {
        require(!simulation::taskOutput(*d, 101, slot, 1, output, error) && output == 12345,
                "bad scalar slot preserves result");
    }
    require(!simulation::taskOutput(*d, 101, 1, -1, output, error) && output == 12345,
            "negative scalar labor preserves result");
    require(!simulation::taskOutput(*d, 9999, 1, 1, output, error) && output == 12345,
            "missing scalar ID preserves result");
    require(!simulation::taskOutput(*d, 102, 1, 1, output, error) && output == 12345,
            "unowned scalar producer fails instead of inventing racial stats");

    std::vector<uint8_t> globalState(sizeof(gs)), globalMisc(sizeof(gg));
    std::memcpy(globalState.data(), &gs, sizeof(gs)); std::memcpy(globalMisc.data(), &gg, sizeof(gg));
    const auto seed = rtl::seed(), seedHi = rtl::seedHi();
    const auto before = encode(*d);
    require(plan(*d) == plan(*d), "production query deterministic for identical input");
    (void)scalar(*d, 101, 1, 3);
    require(encode(*d) == before && d->options.turn == 41 && d->world.rngSeed == 0x12345678,
            "queries never change persistent state or turn");
    require(std::memcmp(globalState.data(), &gs, sizeof(gs)) == 0 &&
            std::memcmp(globalMisc.data(), &gg, sizeof(gg)) == 0 && rtl::seed() == seed && rtl::seedHi() == seedHi,
            "queries never touch globals or either RNG word");
}

void corpus(const std::filesystem::path& directory) {
    namespace fs = std::filesystem;
    if (directory.empty()) { std::cout << "production optional corpus: no data directory\n"; return; }
    size_t documents = 0, buildings = 0;
    auto inspect = [&](const save::Document& d) {
        const auto report = plan(d);
        require(report.territories.size() == d.territories.size(), "corpus includes every territory");
        size_t represented = 0;
        for (const auto& territory : report.territories) {
            represented += territory.buildings.size();
            for (const auto& building : territory.buildings) {
                if (!building.evaluated) continue;
                for (int slot = 0; slot < 5; ++slot)
                    (void)scalar(d, building.buildingId, slot, building.assigned[size_t(slot)].labor);
            }
        }
        require(represented == d.buildings.size(), "corpus includes every building exactly once");
        buildings += represented; ++documents;
    };
    for (const char* relative : {"TUTORIAL.SAV", "Saves/AUTOSAVE.SAV", "Campaign/AUTOSAVE.CPN", "Campaign/ChCht001.CPN"}) {
        const auto path = directory / relative;
        if (!fs::is_regular_file(path)) continue;
        auto d = std::make_unique<save::Document>();
        save::Error error;
        if (!save::readDocument(path, *d, error)) throw std::runtime_error(error.message);
        inspect(*d);
    }
    if (fs::is_regular_file(directory / "LEVELS.HDX") && fs::is_regular_file(directory / "LEVELS.HDD")) {
        HdxArchive archive;
        std::string why;
        if (!archive.open((directory / "LEVELS").string(), &why)) throw std::runtime_error(why);
        for (const auto& entry : archive.entries()) {
            auto d = std::make_unique<save::Document>();
            save::Error error;
            if (!save::readScenario(directory / "LEVELS", entry.name, *d, error)) throw std::runtime_error(error.message);
            inspect(*d);
        }
    }
    std::cout << "production optional corpus: " << documents << " documents, " << buildings << " buildings\n";
}

} // namespace

int main(int argc, char** argv) {
    try {
        numericalOutputs();
        emptyTasksConstructionAndWrap();
        shrineAndPopulation();
        validationAndPurity();
        corpus(argc > 1 ? std::filesystem::path(argv[1]) : std::filesystem::path{});
        std::cout << "production_plan: numeric outputs, signed fields, wrap, shrines, population, validation and purity passed\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "production_plan: " << error.what() << '\n';
        return 1;
    }
}
