// Compiles legacy consumers together without pulling absent gameplay fallbacks.
#include "game/economy.h"
#include "game/newgame.h"
#include "game/campaign_flow.h"
#include "game/turn_api.h"
#include "game/ai_taskforce.h"
#include "game/rtl_compat.h"

#include <algorithm>
#include <bit>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

namespace {
using namespace dl2;
namespace fs = std::filesystem;
void require(bool value, const char* message) {
    if (!value) throw std::runtime_error(message);
}
static_assert(data::kNumCampaigns == 43 && econ::kNumCampaigns == 43 &&
              dl2::kNumCampaigns == 43 && kNumCampaignDefs == 43);
static_assert(std::is_same_v<UnitTypeRow, data::UnitDef> &&
              std::is_same_v<BuildingTypeRow, data::BuildingDef> &&
              std::is_same_v<TechStaticRow, data::TechDef>);
static_assert(sizeof(Army) == 0x5c && sizeof(Building) == 0x122);
static_assert(sizeof(econ::CampaignGoal) == 0x44 && sizeof(econ::CampaignDef) == 0xd8);
static_assert(offsetof(econ::CampaignGoal, done) == 0x40 && offsetof(econ::CampaignDef, goal) == 0xc);
static_assert(sizeof(CampaignPlayerDef) == 0x9c);
static_assert(std::size(data::kDepositNames) == 5 && std::size(econ::kTaxMoraleByLevel) == 6);
static_assert(std::is_same_v<decltype(ext::deleteUnit), void (*)(Army*)>);
static_assert(std::is_same_v<decltype(econ::kUnitTypes[0].unk18), int32_t>);
static_assert(legacy::techMaskContains(0x8000, 15) && legacy::techMaskContains(0x8000, 31));
static_assert(legacy::techMaskContains(0x8000, -1) && !legacy::techMaskContains(0x8000, 0));
static_assert(legacy::techMaskContains(1, 32) && legacy::techMaskContains(1, std::numeric_limits<int>::min()));

void sharedFieldContracts() {
    Army a{};
    require(&armyMission(a) == &a.unk_25 && &armyDamage(a) == &a.unk_2c, "shared army field offsets differ");
    armyMission(a) = 14; armyDamage(a) = -32768;
    require(a.unk_25 == 14 && a.unk_2c == -32768, "shared army accessors changed storage semantics");
    for (uint32_t mask = 0; mask <= 0xffffu; ++mask) for (int player = 0; player < 7; ++player)
        require(legacy::techMaskContains(uint16_t(mask), player) == bool((mask >> player) & 1u),
                "shared tech mask changed valid-player behavior");
    require(legacy::techMaskContains(0x8000, 16) && !legacy::techMaskContains(0x7fff, 16) &&
            !legacy::techMaskContains(0, -1) && legacy::techMaskContains(0xffff, -1),
            "shared tech mask lost x86 sign-extension or masked-shift semantics");
}

void aliasesAndRows() {
    require(&kUnitTable[0] == &data::kUnitTypes[0] && &kBuildingTable[0] == &data::kBuildingTypes[0] &&
            &kTechTable[0] == &data::kTechs[0], "turn contracts do not alias canonical storage");
    require(&kRaceNames[0] == &data::kRaceNames[0] && &econ::kRaceNames[0] == &data::kRaceNames[0] &&
            &kRaceStatsDefault[0][0] == &data::kRaceStatsDefault[0][0], "race table storage is duplicated");
    require(&econ::kLaborYield[0][0] == &data::kLaborProductionTable[0][0] &&
            &econ::kTaxIncomeByLevel[0] == &data::kTaxIncomePercent[0] &&
            &econ::kTaxMoraleByLevel[0] == &data::kTaxMoraleByLevel[0] &&
            &econ::kGrowthByTerrain[0] == &data::kPopulationGrowthByTerrain[0] &&
            &econ::kCrowdingByTerrain[0] == &data::kTerrainMaxPopulation[0] &&
            &econ::kStarvationMorale[0] == &data::kMoraleByLevel[0], "economic scalar arrays are not canonical aliases");
    require(econ::kBuildingTypes.size() == 48 && econ::kUnitTypes.size() == 39 &&
            econ::kBuildingCosts.size() == 48 && econ::kUnitCosts.size() == 39 &&
            kBuildingNames.size() == 48, "table extents differ");
    for (size_t i = 0; i < econ::kBuildingTypes.size(); ++i) {
        const auto& c = data::kBuildingTypes[i]; const auto& b = econ::kBuildingTypes[i];
        require(b.name == c.name && kBuildingNames[i] == c.name && b.sprite == c.sprite && b.icon == c.icon &&
                b.category == c.category && b.maxLabor == c.maxLabor && b.size == c.size && b.work == c.buildLabor,
                "building adapter header differs");
        require(uint8_t(b.energyUse) == uint8_t(c.energyUse) && b.unk0d == uint8_t(c.energyUse >> 8) &&
                uint8_t(b.tech) == c.techRequired && b.unk28 == uint16_t(c.hitPoints | uint16_t(c.unk_29) << 8) &&
                b.queueCat == c.productionQueue && b.helpId == c.dialogAnim, "building scalar adapter differs");
        for (size_t slot = 0; slot < 5; ++slot)
            require(b.rate[slot] == c.taskRate[slot] && b.task[slot] == c.tasks[slot], "building task mapping differs");
        for (size_t unit = 0; unit < 10; ++unit) require(b.units[unit] == c.units[unit], "building unit list differs");
        for (size_t material = 0; material < 11; ++material)
            require(&econ::kBuildingCosts[i][material] == &c.cost[material] &&
                    &kBuildingCosts[i][material] == &c.cost[material], "building costs are a duplicate or wrong projection");
    }
    for (size_t i = 0; i < econ::kUnitTypes.size(); ++i) {
        const auto& c = data::kUnitTypes[i]; const auto& u = econ::kUnitTypes[i];
        require(u.name == c.name && u.sprite == c.combatSprite && u.unk06 == c.moveAnim &&
                u.unk08 == c.portraitGroup && u.unk0a == uint8_t(c.portraitIndex) && u.unitClass == c.unitClass &&
                u.work == c.buildLabor && u.maintenance == c.upkeep && u.tech == c.techRequired &&
                u.moves == c.moves && u.domain == c.domain && u.unk12 == c.unk_12 &&
                u.attack == c.attack && u.defense == c.defense && u.range == c.speed &&
                u.rof == c.rateOfFire && u.unk17 == c.range && u.unk18 == c.sound, "unit row adapter differs");
        for (size_t material = 0; material < 11; ++material)
            require(&econ::kUnitCosts[i][material] == &c.cost[material], "unit costs are duplicated");
        require(UnitTypeClass(int(i)) == c.unitClass && UnitTypeTech(int(i)) == c.techRequired &&
                UnitTypeRange(int(i)) == c.moves && UnitTypeDomain(int(i)) == c.domain,
                "AI header helpers do not resolve canonical adapted rows");
    }
    for (size_t i = 0; i < 20; ++i)
        require(econ::kBuildingTaskNames[i] == data::kTaskNames[i + 2], "legacy task-name offset must be +2");
    require(econ::kCityCenterWork == 600 && econ::kCityCenterTech == 0 &&
            &econ::kCityCenterCost[0] == &data::kBuildingTypes[37].cost[0], "city-center aliases differ");
    require(kUnitTable[1].buildLabor == 30 && econ::kUnitCosts[1][0] == 35,
            "manufacturing work was incorrectly conflated with credits");
    require(kUnitTable[19].speed == -1 && kUnitTable[19].range == 49 && kUnitTable[16].rateOfFire == -1,
            "signed speed/ROF or squared-range contract regressed");
    require(econ::kUnitTypes[36].unk18 == 130 && kUnitTable[36].sound == 130, "sound-ID width regressed");
    require(&econ::kUnitGroupLimitLand[0] == &data::kMaxUnitsPerTerritoryLand[0] &&
            &econ::kUnitGroupLimitSea[0] == &data::kMaxUnitsPerTerritorySea[0], "group-limit address aliases swapped");
    require(std::strcmp(data::kUnitShortNames[3], "Trooper.") == 0 &&
            std::strcmp(data::kUnitShortNames[15], "Commander") == 0 &&
            std::strcmp(data::kUnitTypes[15].name, "Command Corps") == 0, "short and full unit names were conflated");
}

void campaignContracts() {
    require(econ::gCampaigns.size() == 43 && kCampaignDefaults.size() == 43 &&
            &kCampaignTable == &econ::gCampaigns && &kCampaignDefaults == &econ::kCampaignDefaults,
            "campaign headers do not share all 43 records");
    CampaignTableReset();
    for (size_t i = 0; i < 43; ++i) {
        const auto& c = data::kCampaigns[i]; const auto& b = econ::gCampaigns[i];
        require(b.victory == c.victory && b.param1 == c.param1 && b.param2 == c.param2, "campaign header differs");
        for (size_t goal = 0; goal < 3; ++goal) {
            const auto& from = c.goals[goal]; const auto& to = b.goal[goal];
            require(to.type == from.type && to.count == from.turns && to.param[0] == from.count &&
                    to.done == from.state, "campaign offsets +4/+8/+40 were conflated");
            for (size_t n = 0; n < 13; ++n) require(to.param[n + 1] == from.list[n], "campaign parameter mapping differs");
        }
    }
    require(kCampaignDefaults[42].victory == 2 && kCampaignDefaults[42].param1 == 2 &&
            kCampaignDefaults[42].param2 == 10, "campaign 42 was omitted or zero-filled");
    const auto original = data::kCampaigns[42].goals[0].state;
    kCampaignTable[42].goal[0].done = 777;
    require(econ::gCampaigns[42].goal[0].done == 777 && data::kCampaigns[42].goals[0].state == original &&
            kCampaignDefaults[42].goal[0].done == original, "mutable bridge overwrote immutable defaults");
    CampaignTableReset();
    require(kCampaignTable[42].goal[0].done == original, "explicit reset failed to restore campaign defaults");
    for (int race = 0; race < 7; ++race) for (int chapter = 1; chapter <= 6; ++chapter) {
        const int index = campaignIndex(race, chapter);
        require(index >= 1 && index <= 42 && campaignRace(index) == race && campaignChapter(index) == chapter,
                "campaign race/chapter contract differs");
    }
    require(kCampaignPlayers.size() == 10, "campaign arrival count differs");
    for (size_t i = 0; i < kCampaignPlayers.size(); ++i) {
        const auto& c = data::kAiArrivals[i]; const auto& p = kCampaignPlayers[i];
        require(p.race == c.race && p.techLevel == c.techLevel && p.credits == c.credits &&
                p.pactRace == c.allyRace && p.pactType == c.allyPact, "campaign arrival header differs");
        for (size_t n = 0; n < 4; ++n) require(p.territory[n] == c.sites[n], "arrival territory differs");
        for (size_t n = 0; n < 10; ++n)
            require(p.materials[n] == c.materials[n] && p.units[n].unitType == c.units[n][0] &&
                    p.units[n].count == c.units[n][1], "arrival materials/units differ");
    }
}

// Optional independent read-only PE comparison. No platform loader or execution.
class OriginalPe {
    std::vector<uint8_t> bytes_;
    uint32_t imageBase_ = 0; size_t sections_ = 0; uint16_t count_ = 0;
    uint16_t u16(size_t at) const { return uint16_t(u8(at) | uint16_t(u8(at + 1)) << 8); }
    uint8_t u8(size_t at) const { require(at < bytes_.size(), "truncated original PE"); return bytes_[at]; }
    uint32_t u32(size_t at) const {
        return uint32_t(u8(at)) | uint32_t(u8(at + 1)) << 8 | uint32_t(u8(at + 2)) << 16 | uint32_t(u8(at + 3)) << 24;
    }
    size_t offset(uint32_t address) const {
        require(address >= imageBase_, "PE address below image base"); const auto rva = address - imageBase_;
        for (size_t i = 0; i < count_; ++i) {
            const auto section = sections_ + 40 * i; const auto start = u32(section + 12);
            const auto size = u32(section + 16);
            if (rva >= start && rva - start < size) {
                const auto result = size_t(u32(section + 20)) + size_t(rva - start);
                require(result < bytes_.size(), "PE raw offset outside file"); return result;
            }
        }
        throw std::runtime_error("original table address not backed by a PE section");
    }
public:
    explicit OriginalPe(const fs::path& path) {
        const auto size = fs::file_size(path); require(size >= 64 && size <= 16 * 1024 * 1024, "invalid original EXE size");
        bytes_.resize(size_t(size)); std::ifstream input(path, std::ios::binary);
        require(bool(input.read(reinterpret_cast<char*>(bytes_.data()), std::streamsize(bytes_.size()))), "cannot read original EXE");
        require(u16(0) == 0x5a4d, "original EXE is not MZ"); const size_t pe = u32(0x3c);
        require(u32(pe) == 0x4550 && u16(pe + 24) == 0x10b, "original EXE is not PE32");
        count_ = u16(pe + 6); imageBase_ = u32(pe + 24 + 28);
        sections_ = pe + 24 + u16(pe + 20);
        require(count_ > 0 && count_ < 100 && sections_ <= bytes_.size() &&
                size_t(count_) * 40 <= bytes_.size() - sections_, "invalid original PE section table");
    }
    uint32_t word(uint32_t address) const { return u32(offset(address)); }
    std::string text(uint32_t address) const {
        std::string result; size_t at = offset(address);
        while (u8(at)) { require(result.size() < 1024, "unterminated original string"); result.push_back(char(u8(at++))); }
        return result;
    }
    template<size_t N> void numbers(uint32_t address, const int32_t (&values)[N]) const {
        for (size_t i = 0; i < N; ++i) require(word(address + uint32_t(4 * i)) == uint32_t(values[i]), "numeric table differs from original EXE");
    }
    template<size_t N> void strings(uint32_t address, const char* const (&values)[N]) const {
        for (size_t i = 0; i < N; ++i) require(text(word(address + uint32_t(4 * i))) == values[i], "string table differs from original EXE");
    }
};
void optionalOriginal(const fs::path& directory) {
    const auto path = directory / "DEADLOCK.EXE";
    if (directory.empty() || !fs::is_regular_file(path)) {
        std::cout << "table contracts: original EXE unavailable; canonical/adapter checks still ran\n"; return;
    }
    OriginalPe pe(path);
    pe.numbers(0x4c5e58, data::kSiteOrder); pe.numbers(0x4d6334, data::kMetalForSteel);
    pe.numbers(0x4d6344, data::kMetalSteelValue); pe.numbers(0x4c53f4, data::kAssistantPriority);
    pe.numbers(0x4c52c8, data::kSkillMoraleAdjust); pe.numbers(0x4d5034, data::kDepositTerrainValue);
    pe.numbers(0x4b7d5c, data::kLandingTerrainScore); pe.numbers(0x4d57ec, data::kTaxMoraleByLevel);
    pe.strings(0x5095e4, data::kUnitShortNames); pe.strings(0x5090f0, data::kMaterialUnitNames);
    pe.strings(0x509304, data::kDepositNames); pe.strings(0x509318, data::kAmountNames);
    pe.strings(0x4d5188, data::kRaceUpperNames);
    for (uint32_t i = 0; i < 43; ++i) {
        const auto address = 0x4c6194 + i * 0xd8; const auto& c = data::kCampaigns[i];
        require((pe.word(address) & 0xffu) == c.victory && pe.word(address + 4) == uint32_t(c.param1) &&
                pe.word(address + 8) == uint32_t(c.param2), "campaign header differs from original EXE");
        for (uint32_t g = 0; g < 3; ++g) {
            const auto goalAddress = address + 12 + g * 0x44; const auto& goal = c.goals[g];
            require(pe.word(goalAddress) == uint32_t(goal.type) && pe.word(goalAddress + 4) == uint32_t(goal.turns) &&
                    pe.word(goalAddress + 8) == uint32_t(goal.count) && pe.word(goalAddress + 0x40) == uint32_t(goal.state),
                    "campaign goal differs from original EXE");
            for (uint32_t n = 0; n < 13; ++n)
                require(pe.word(goalAddress + 12 + n * 4) == uint32_t(goal.list[n]), "campaign list differs from original EXE");
        }
    }
    std::cout << "table contracts: supplemental tables and all 43 campaigns match original EXE bytes\n";
}
} // namespace

int main(int argc, char** argv) {
    try {
        gs.options.turn = 13579; gg.rng2Seed = 0x12345678;
        const auto* g = reinterpret_cast<const uint8_t*>(&gs); const auto* globals = reinterpret_cast<const uint8_t*>(&gg);
        const std::vector<uint8_t> before(g, g + sizeof(gs)), beforeGlobals(globals, globals + sizeof(gg));
        rtl::srand(0x76543210); const auto lo = rtl::seed(), hi = rtl::seedHi();
        sharedFieldContracts(); aliasesAndRows(); campaignContracts(); optionalOriginal(argc > 1 ? fs::path(argv[1]) : fs::path{});
        require(std::memcmp(before.data(), &gs, sizeof(gs)) == 0 && std::memcmp(beforeGlobals.data(), &gg, sizeof(gg)) == 0,
                "table adapters or campaign reset modified gs/gg");
        require(lo == rtl::seed() && hi == rtl::seedHi(), "table adapters consumed RNG");
        std::cout << "table contracts: canonical aliases, complete adapters, shared campaign bridge and isolation passed\n";
        return 0;
    } catch (const std::exception& e) { std::cerr << "table contracts: " << e.what() << '\n'; return 1; }
}
