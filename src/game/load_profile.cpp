#include "game/load_profile.h"
#include "game/data_tables.h"
#include <algorithm>
#include <cstring>
#include <exception>
#include <memory>
#include <stdexcept>
#include <unordered_map>
#include <utility>

namespace dl2::simulation {
namespace {
bool fail(save::Error& e, save::ErrorCode code, const char* message) {
    e = {code, 0, message}; return false;
}
// sprintf in 0045fae4 writes through the NUL, not the remainder of name[33].
void name(Player& player, const std::string& value) {
    std::memcpy(player.name, value.data(), value.size());
    player.name[value.size()] = '\0';
}
// orig: 0044fd14 / 00450150 / 00450000 / 004501b0. Goal type 4's
// +04 (`turns`) is the number of race entries; payload begins at +08 (`count`).
bool campaign(save::Document& d, LoadCoreReport& result, save::Error& error) {
    if (d.options.campaign < 0 || d.options.campaign >= data::kNumCampaigns)
        return fail(error, save::ErrorCode::InvalidState, "Load profile: campaign index must be 0..42");
    for (size_t k = 0; k < 3; ++k) result.campaignProgress[k] = d.options.campaignBytes[k];
    if (!d.options.campaign) return true;
    const auto& definition = data::kCampaigns[d.options.campaign];
    d.options.victory = definition.victory;
    if (definition.victory == 0) d.options.winCities = definition.param1;
    else if (definition.victory == 2) {
        d.options.winShrines = definition.param1; d.options.winTurns = definition.param2;
    }
    const data::CampaignGoal* research = nullptr;
    for (const auto& goal : definition.goals) {
        if (goal.type) result.campaignGoalMask |= uint32_t(1) << (uint32_t(goal.type) & 31u);
        if (goal.type == 4 && !research) research = &goal;
    }
    if (!research) return true;
    const int races = research->turns;
    if (races < 0 || races >= 14)
        return fail(error, save::ErrorCode::InvalidState, "Load profile: campaign research list exceeds its table row");
    const auto payload = [&](int index) { return index ? research->list[index - 1] : research->count; };
    for (int p = 0; p < d.options.numPlayers; ++p) {
        const auto& player = d.players[size_t(p)];
        bool raceListed = false;
        for (int k = 0; k < races; ++k) raceListed |= player.race == payload(k);
        if (raceListed && player.currentResearch == payload(races))
            result.forbiddenResearchPlayers |= uint8_t(1u << p);
    }
    return true;
}
// orig: LoadJobs 00461078 reads all 350 jobs, then clears all 0x10bf8 bytes
// for versions <0x26. Its following aiWarMask/scratch blocks are still loaded.
// LoadSpiesAndBlackMarket 00461418 supplies defaults only before version 0x24.
void migrateLegacyBlocks(save::Document& d, LoadCoreReport& result) {
    if (result.version < 0x26) {
        std::memset(d.jobs.data(), 0, sizeof(d.jobs));
        result.discardedLegacyJobs = true;
    }
    if (result.version < 0x24) {
        // orig: ResetSpies 0047d460 and BlackMarketReset 00450c9c.
        for (auto& playerSpies : d.spies) for (auto& spy : playerSpies)
            spy = Spy{-1, 0, 0, 0};
        for (auto& market : d.blackMarket) market = BlackMarketState{0, -1};
        result.initializedMissingSpiesMarket = true;
        // Deliberate representation migration, NOT an original header write:
        // v35 has no spy/market block and archival validation rejects nonzero
        // values there. Keep the source/report version intact and use the first
        // capable layout for this partial, non-capturable runtime candidate.
        d.header.version = 0x24;
    }
    result.normalizedVersion = d.header.version;
}
// orig: ResetVariables 0046da14 -> ResetAI 004018d8, LoadJobs 00461078 and
// LoadGame 004618e8 -> PlayerInitAI 00401830 -> 00408784 -> 0040233c.
// ResetAI happens BEFORE loading players, minister jobs, aiWarMask and scratch
// jobs. Do not erase those loaded records. The six 0040231c reset callees are
// actual RET functions in this executable, not missing simulation callbacks.
bool initializeSessionMetadata(const save::Document& d, LoadCoreReport& result, save::Error& error) {
    auto& session = result.session;
    session.localPlayer = session.hostPlayer = result.localPlayer;
    for (size_t p = 0; p < kMaxPlayers; ++p) {
        auto& ai = session.ai[p];
        if (d.players[p].type != uint8_t(LoadAiPersonality::Machiavelli)) continue;
        ai.initialized = true;
        ai.personality = LoadAiPersonality::Machiavelli;
        const auto savedType = result.playerTypesBefore[p];
        ai.initializations = savedType == 1 || savedType == 2 ? 2 : 1;
        ai.strategyCountdown = 40;
        for (size_t m = 0; m < ai.ministers.size(); ++m) {
            const auto& config = data::kAiMinisterConfigDefault[m];
            if (config.kind < 0 || config.kind >= 6 || config.param < 0 || config.param > UINT8_MAX)
                return fail(error, save::ErrorCode::InvalidState, "Load profile: invalid canonical minister configuration");
            auto& minister = ai.ministers[m];
            minister.role = Minister(m);
            minister.kind = uint8_t(config.kind);
            minister.parameter = uint8_t(config.param);
            // Scratch/state remain zero from the owned metadata constructor.
            // Personality and minister selectors identify canonical bindings;
            // never copy EXE addresses or install success-shaped no-op callbacks.
        }
    }
    session.initialized = true;
    return true;
}
}

bool normalizeLoadCore(const save::Document& source, const LoadProfile& profile,
                       save::Document& destination, LoadCoreReport& report, save::Error& error) {
    try {
        if (!save::validate(source, error)) return false;
        if (source.header.isMap)
            return fail(error, save::ErrorCode::InvalidState, "Load profile requires a saved game, not a reduced map");
        if (profile.localPlayer < -1 || profile.localPlayer >= kMaxPlayers ||
            profile.localPlayerName.size() > 32 || profile.localPlayerName.find('\0') != std::string::npos)
            return fail(error, save::ErrorCode::InvalidState, "Load profile has an invalid local player slot or name");
        auto next = std::make_unique<save::Document>(source);
        auto& d = *next;
        LoadCoreReport result;
        result.version = d.header.version;
        result.localPlayer = profile.localPlayer < 0 ? d.options.localPlayer : profile.localPlayer;
        result.aiSkillBefore = d.options.aiSkill;
        // Confirmed assembly 0045f8dd stores the loaded value before clamping.
        result.aiSkillAfter = d.options.aiSkill = std::clamp(d.options.aiSkill, 0, 4);
        d.options.localPlayer = result.localPlayer;
        std::fill(std::begin(d.options.hasWon), std::end(d.options.hasWon), uint16_t(0));
        if (!campaign(d, result, error)) return false;
        for (size_t p = 0; p < kMaxPlayers; ++p) {
            auto& player = d.players[p];
            result.playerTypesBefore[p] = player.type;
            // Original signed-char type comparisons: supported live types 1..3.
            // A dormant slot may retain a sentinel type >=128, never an AI index.
            const int signedType = player.type < 128 ? player.type : int(player.type) - 256;
            if (signedType > 3)
                return fail(error, save::ErrorCode::InvalidState, "Load profile: unsupported AI personality type");
            if ((signedType > 0 || int(p) == result.localPlayer) &&
                (player.race < 0 || player.race >= kMaxPlayers || player.index != p))
                return fail(error, save::ErrorCode::InvalidState, "Load profile: active player index or race is invalid");
            if (d.options.campaign && d.options.turn == 1 && p < size_t(d.options.numPlayers) && signedType > 0) {
                d.options.playersMask |= uint8_t(1u << p); player.defeated = 0;
            }
            // Names are loaded BEFORE LoadJobs converts other human players to AI.
            if (int(p) == result.localPlayer) name(player, profile.localPlayerName);
            else if (signedType > 2) name(player, data::kAiLeaderNames[player.race]);
            if (int(p) == result.localPlayer) player.type = 1;
            else if (player.type == 1 || player.type == 2) player.type = 3;
            result.playerTypesAfter[p] = player.type;
        }
        if (!initializeSessionMetadata(d, result, error)) return false;
        // Event text is opaque binary here; native EventLog rebuild/indices are
        // not simulated. Original discards ALL stored events for older versions.
        if (result.version != kSaveVersion) {
            result.discardedEvents = uint32_t(d.events.size());
            d.events.clear(); d.options.eventCount = 0;
        }
        migrateLegacyBlocks(d, result);
        for (auto& record : d.territories) {
            auto* first = reinterpret_cast<uint8_t*>(&record.data) + kTerritorySavedBytes;
            std::fill(first, reinterpret_cast<uint8_t*>(&record.data) + sizeof(Territory), uint8_t(0));
        }
        std::unordered_map<uint32_t, Army*> armies;
        for (auto& army : d.armies) {
            army.unk_44.raw = 0; army.job = 0; armies.emplace(army.id, &army);
        }
        // Assembly 0046124a uses MOVZX, not the decompiler's signed-short cast.
        // Last encountered job wins, including duplicate references across players.
        for (const auto& jobs : d.jobs) for (size_t j = 0; j < jobs.size(); ++j)
            for (const auto id : jobs[j].armyIds) if (id) {
                armies.at(id)->job = int16_t(j + 1); ++result.armyJobBindings;
            }
        // Loaded records fill the physical building pool in file order before
        // RebuildBuildingLists; active prev/next are rebuilt in that same order.
        for (size_t i = 0; i < d.buildings.size(); ++i) {
            d.buildings[i].prev.raw = i ? d.buildings[i - 1].id : 0;
            d.buildings[i].next.raw = i + 1 < d.buildings.size() ? d.buildings[i + 1].id : 0;
        }
        if (!save::validate(d, error)) return false;
        destination = std::move(d); report = result; error = {}; return true;
    } catch (const std::bad_alloc&) {
        return fail(error, save::ErrorCode::Limit, "Insufficient memory normalizing load profile");
    } catch (const std::length_error&) {
        return fail(error, save::ErrorCode::Limit, "Load profile allocation exceeds limits");
    } catch (const std::exception& e) {
        error = {save::ErrorCode::InvalidState, 0, e.what()}; return false;
    }
}
} // namespace dl2::simulation
