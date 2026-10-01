// Owned AfterMovePhase(loading=1) intelligence; never activates raw pointers.
#pragma once
#include "game/save_document.h"
#include <cstdint>

namespace dl2::simulation {
struct LoadIntelligenceContext {
    // Session cheats, NOT SAV fields or OS preferences. Original default is0.
    // 004d63d8:0 normal,1 human explored,2 human visible (004732d0).
    int fogMode = 0;
    bool revealAll = false; // 00583c20 debug reveal for the local player.
    bool operator==(const LoadIntelligenceContext&) const = default;
};
struct LoadIntelligenceReport {
    bool detectionRebuilt = false, visibilityRebuilt = false;
    bool buildingIntelligenceRebuilt = false, populationKnownRebuilt = false;
    uint32_t detectorSources = 0, sitesCopied = 0, sitesCleared = 0;
    // 0046e730 loading!=0 skips 004471c0 (CheckDiscovery), relinking/removal,
    // ownership changes and battles. No invented contact discovery on load.
    bool contactDiscoverySkippedOnLoad = false;
    bool operator==(const LoadIntelligenceReport&) const = default;
};
// Executes 00447090/00446fd4/00446440(mode3), 0046e730 site/population
// snapshots, and 0046e338/0046e064. Intended AFTER CountShrines and BEFORE
// EndTurnBalance; tile roads commute with these fields. No labor, roads, AI,
// events, RNG, UI, editor mode or complete-turn effects are hidden here.
// Rebuilds T+6d detector thresholds, per-source flags and T+a70 distance scratch;
// T+66 visibility; site+19/1a/1b/1c/1e/32; low byte T+36, T+38, flags&~0x40.
// Ordinary size2/5 anchors keep existing type/race/labor intelligence, matching
// the original: only size1 anchors or special top-right tiles copy a building.
// Signed racial addressing matches original bytes: inactive race=-1 reads
// RaceStats row51[6], not row52[-1] through an invalid C++ subscript. Addresses
// outside the owned stats block, invalid owners, out-of-range site references,
// and unsupported fixed-pool overrun domains fail explicitly, not normalize.
// Transactional, including alias source==destination; failure preserves both
// outputs, success clears error. Context is explicit and never read globally.
bool rebuildLoadIntelligence(const save::Document& source,
                             const LoadIntelligenceContext& context,
                             save::Document& destination, LoadIntelligenceReport& report,
                             save::Error& error);
} // namespace dl2::simulation
