// Explicit, partial legacy load normalization. Archival prepare is separate.
#pragma once
#include <array>
#include <cstdint>
#include <string>
#include "game/save_document.h"

namespace dl2::simulation {
struct LoadProfile {
    // This profile covers generation 4, versions 0x26..0x120, offline gameplay
    // (not editor/network rejoin). Earlier layouts remain inspectable by codec.
    int localPlayer = -1; // -1 restores the file's slot; otherwise explicit 0..6.
    std::string localPlayerName = "New Player"; // Explicit preference, at most 32 bytes.
};
struct LoadCoreReport {
    uint32_t version = 0;
    int localPlayer = 0;
    int32_t aiSkillBefore = 0, aiSkillAfter = 0;
    uint32_t campaignGoalMask = 0;
    std::array<uint8_t, 3> campaignProgress{};
    std::array<uint8_t, kMaxPlayers> playerTypesBefore{}, playerTypesAfter{};
    uint32_t discardedEvents = 0, armyJobBindings = 0;
    uint8_t forbiddenResearchPlayers = 0; // Apply AFTER derived state and labor.
    bool operator==(const LoadCoreReport&) const = default;
};

// orig: LoadOptions 0045f828, CampaignApplyOptions 0044fd14, LoadPlayers
// 0045fae4, LoadArmies 004606f4, LoadJobs 00461078, RebuildBuildingLists
// 0044cabc, plus ResetVictoryCounters 00486910 and LoadEventLog 004600d0.
// Transactional source->destination; does not initialize executable AI, repair
// visibility, invoke timers, consume RNG or produce a playable session.
// Historical callback/pointer words remain inert; native references live in Graph.
bool normalizeLoadCore(const save::Document& source, const LoadProfile& profile,
                       save::Document& destination, LoadCoreReport& report, save::Error& error);
} // namespace dl2::simulation
