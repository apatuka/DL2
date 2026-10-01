// Explicit, partial reconstruction of deterministic LoadGame-derived data.
// Not complete activation: visibility/contact rules and their context are absent.
#pragma once
#include "game/save_document.h"
#include <array>
#include <cstdint>
#include <vector>

namespace dl2::simulation {
enum class LoadDerivedScope { Core, Complete };
struct ShrineNotice {
    uint32_t territory = 0;
    int recipient = 0, owner = 0;
    uint8_t eventCode = 0; // 0x4d allied shrine, 0x4e non-allied shrine.
    bool operator==(const ShrineNotice&) const = default;
};
struct LoadDerivedReport {
    std::array<int32_t, kMaxPlayers> territories{}, cities{}, shrines{};
    int32_t totalShrines = 0;
    std::vector<ShrineNotice> notices; // Semantic only; no EventSaved/text invented.
    bool continentsRebuilt = false, roadsRebuilt = false, shrineCountsRebuilt = false;
    bool visibilityRebuilt = false, contactsRebuilt = false;
    bool operator==(const LoadDerivedReport&) const = default;
};
// Core: ComputeContinents(004423b4), CountShrines(00486964), and tile roads
// (0047dd24), in load order. Does not rebuild site roads (0047dfdc), run labor,
// populate building intelligence snapshots, or clear/reset unrelated state.
// Territory +8a0/+8a4 retain original OR semantics, rather than being cleared.
// Continents are fully cleared/rebuilt; +0c contains second-hop continent bits.
// Roads change Tile::overlay/pathCost, using the original 160-entry FIFO and
// direction order; only tile coordinates listed by territories are cleared.
// Nonterminating signed continent-mask walks and invalid accessed indices fail
// explicitly. An unreachable road trace retains the original self-marking quirk;
// a bounded safety guard additionally prevents accidental nontermination.
// Complete is unsupported explicitly. All failures preserve both outputs;
// success clears error. Source/destination may alias. No globals, RNG or I/O.
bool rebuildLoadDerived(const save::Document& source, save::Document& destination,
                        LoadDerivedReport& report, save::Error& error,
                        LoadDerivedScope scope = LoadDerivedScope::Core);
} // namespace dl2::simulation
