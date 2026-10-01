// Compatibility adapters only. data::* is the single source of table values.
// Replaces the former second generated copy (including only 32 campaigns).
// No gs/gg initialization, callbacks, RNG or gameplay activation is performed.
#include "game/economy.h"
#include "game/campaign_flow.h"
#include <bit>

namespace dl2::econ {
const std::array<BldgType, data::kNumBuildingTypes> kBuildingTypes = [] {
    std::array<BldgType, data::kNumBuildingTypes> result{};
    for (size_t i = 0; i < result.size(); ++i) {
        const auto& from = data::kBuildingTypes[i]; auto& to = result[i];
        to.name = from.name; to.sprite = from.sprite; to.icon = from.icon;
        to.category = from.category; to.maxLabor = from.maxLabor; to.size = from.size;
        to.work = from.buildLabor;
        // Original energy readers use the signed LOW byte of +0x0c.
        to.energyUse = std::bit_cast<int8_t>(uint8_t(from.energyUse));
        to.unk0d = uint8_t(from.energyUse >> 8);
        for (size_t k = 0; k < 5; ++k) { to.rate[k] = from.taskRate[k]; to.task[k] = from.tasks[k]; }
        for (size_t k = 0; k < 10; ++k) to.units[k] = from.units[k];
        to.tech = std::bit_cast<int8_t>(from.techRequired);
        to.unk28 = uint16_t(from.hitPoints | (uint16_t(from.unk_29) << 8));
        to.queueCat = from.productionQueue; to.helpId = from.dialogAnim;
    }
    return result;
}();

const std::array<UnitType, data::kNumUnitTypes> kUnitTypes = [] {
    std::array<UnitType, data::kNumUnitTypes> result{};
    for (size_t i = 0; i < result.size(); ++i) {
        const auto& from = data::kUnitTypes[i]; auto& to = result[i];
        to.name = from.name; to.sprite = from.combatSprite; to.unk06 = from.moveAnim;
        to.unk08 = from.portraitGroup; to.unk0a = uint8_t(from.portraitIndex);
        to.unitClass = from.unitClass; to.work = from.buildLabor; to.maintenance = from.upkeep;
        to.tech = from.techRequired; to.moves = from.moves; to.domain = from.domain;
        to.unk12 = from.unk_12; to.attack = from.attack; to.defense = from.defense;
        to.range = from.speed; to.rof = from.rateOfFire; to.unk17 = from.range; to.unk18 = from.sound;
    }
    return result;
}();

const std::array<CampaignDef, kNumCampaigns> kCampaignDefaults = [] {
    std::array<CampaignDef, kNumCampaigns> result{};
    for (size_t i = 0; i < result.size(); ++i) {
        const auto& from = data::kCampaigns[i]; auto& to = result[i];
        to.victory = from.victory; to.param1 = from.param1; to.param2 = from.param2;
        for (size_t k = 0; k < 3; ++k) {
            const auto& goal = from.goals[k]; auto& old = to.goal[k];
            old.type = goal.type;
            old.count = goal.turns; // +4, NOT canonical goal.count at +8.
            old.param[0] = goal.count;
            for (size_t n = 0; n < 13; ++n) old.param[n + 1] = goal.list[n];
            old.done = goal.state;
        }
    }
    return result;
}();
std::array<CampaignDef, kNumCampaigns> gCampaigns = kCampaignDefaults;
} // namespace dl2::econ

namespace dl2 {
const std::array<CampaignPlayerDef, kNumCampaignPlayers> kCampaignPlayers = [] {
    std::array<CampaignPlayerDef, kNumCampaignPlayers> result{};
    for (size_t i = 0; i < result.size(); ++i) {
        const auto& from = data::kAiArrivals[i]; auto& to = result[i];
        to.race = uint8_t(from.race);
        for (size_t k = 0; k < 4; ++k) to.territory[k] = from.sites[k];
        to.techLevel = from.techLevel; to.credits = from.credits;
        for (size_t k = 0; k < 10; ++k) {
            to.materials[k] = from.materials[k];
            to.units[k] = {from.units[k][0], from.units[k][1]};
        }
        to.pactRace = from.allyRace; to.pactType = from.allyPact;
    }
    return result;
}();
// Explicit legacy table reset, not campaign activation or progress evaluation.
void CampaignTableReset() { econ::gCampaigns = econ::kCampaignDefaults; }
} // namespace dl2
