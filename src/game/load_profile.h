// Explicit, partial legacy load normalization. Archival prepare is separate.
#pragma once
#include <array>
#include <cstdint>
#include <string>
#include "game/save_document.h"

namespace dl2::simulation {
struct LoadProfile {
    // This profile covers generation 4, versions 35..0x120, offline gameplay
    // (not editor/network rejoin). This is not a playable-load guarantee.
    int localPlayer = -1; // -1 restores the file's slot; otherwise explicit 0..6.
    std::string localPlayerName = "New Player"; // Explicit preference, at most 32 bytes.
};
enum class LoadAiPersonality : uint8_t { None = 0, Machiavelli = 3 };
struct LoadMinisterResetMetadata {
    Minister role = Minister::Defense; // Slot in the six-minister array.
    uint8_t kind = 0; // Canonical kMinisterVtable selector, NOT a native callback.
    uint8_t parameter = 0; // Packed minister +01, default table 004b62f4.
    std::array<uint8_t, 0x48> scratch{}; // Packed minister +12..+59.
    bool operator==(const LoadMinisterResetMetadata&) const = default;
};
struct LoadAiPlayerResetMetadata {
    bool initialized = false; // True only for a final live AI personality.
    uint8_t initializations = 0; // Converted humans: twice; existing AI: once.
    LoadAiPersonality personality = LoadAiPersonality::None;
    int32_t strategyState = 0; // 0052206c, reset by 00408784.
    int32_t strategyCountdown = 0; // 00522088; original initial value 40 for AI.
    int32_t unknown53317c = 0; // ResetAI zeroes this per-player word.
    std::array<LoadMinisterResetMetadata, 6> ministers{};
    bool operator==(const LoadAiPlayerResetMetadata&) const = default;
};
struct LoadSessionResetMetadata {
    bool initialized = false; // Owned data initialization, NOT session activation.
    bool aiExecutable = false; // No AI/ministry callback implementation installed.
    int localPlayer = 0, hostPlayer = 0;
    bool netGame = false, netJoined = false, netRestore = false, gameAborted = false;
    std::array<LoadAiPlayerResetMetadata, kMaxPlayers> ai{};
    bool operator==(const LoadSessionResetMetadata&) const = default;
};
struct LoadCoreReport {
    uint32_t version = 0; // Original file version, before migration.
    uint32_t normalizedVersion = 0;
    bool discardedLegacyJobs = false, initializedMissingSpiesMarket = false;
    int localPlayer = 0;
    int32_t aiSkillBefore = 0, aiSkillAfter = 0;
    uint32_t campaignGoalMask = 0;
    std::array<uint8_t, 3> campaignProgress{};
    std::array<uint8_t, kMaxPlayers> playerTypesBefore{}, playerTypesAfter{};
    uint32_t discardedEvents = 0, armyJobBindings = 0;
    uint8_t forbiddenResearchPlayers = 0; // Apply AFTER derived state and labor.
    LoadSessionResetMetadata session; // Effective AI/reset data, separate from raw words.
    bool operator==(const LoadCoreReport&) const = default;
};

// orig: LoadOptions 0045f828, CampaignApplyOptions 0044fd14, LoadPlayers
// 0045fae4, LoadArmies 004606f4, LoadJobs 00461078, RebuildBuildingLists
// 0044cabc, plus ResetVictoryCounters 00486910 and LoadEventLog 004600d0;
// legacy defaults 00461418/0047d460/00450c9c and ResetAI/PlayerInitAI
// 004018d8/00401830 -> 00408784 -> 0040233c.
// Transactional source->destination; does not initialize executable AI, repair
// visibility, invoke timers, consume RNG or produce a playable session.
// Version 35 is explicitly promoted to 36 in the normalized candidate ONLY,
// because nonzero spy/market defaults cannot be represented by the v35 codec.
// Versions 35..37 discard the entire normal jobs block, not scratch/minister jobs.
// Not an archival conversion or a re-saveable gameplay result. Raw callback/
// pointer words and packed AI regions remain inert and unmodified; effective AI
// reset data is session metadata, and native object references live in Graph.
bool normalizeLoadCore(const save::Document& source, const LoadProfile& profile,
                       save::Document& destination, LoadCoreReport& report, save::Error& error);
} // namespace dl2::simulation
