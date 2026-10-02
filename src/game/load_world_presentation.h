// Owned changed-world branch of LoadGame; no native window/global state.
#pragma once
#include "game/save_document.h"
#include "game/session_rng.h"
#include <array>
#include <cstdint>
#include <vector>

namespace dl2::simulation {
struct LoadWorldPresentationContext {
    WorldParams previousWorld{}; // All20 bytes compared, as004618e8 does.
    RngSnapshot rng; // Immediately BEFORE changed-world branch, after events.
    int32_t shadingSlope = 0; // Prior0058f148; zero is an explicit cold-session choice.
};
struct LoadPalettePatch {
    uint32_t offset = 0; // Relative to0051a8cc; not a native address.
    std::vector<uint8_t> bytes;
    bool operator==(const LoadPalettePatch&) const = default;
};
struct LoadWorldPresentationReport {
    bool changedWorld = false, mapRebuilt = false, selectionReset = false;
    // Successful headless work requests these presentation actions; it does
    // NOT claim to have recreated windows, loaded sprites or applied a palette.
    bool windowRecreationRequested = false, paletteApplicationRequested = false;
    uint32_t width = 0, height = 0; // Pixels, original32 pixels per map tile.
    std::vector<uint8_t> heightMap, colorMap; // Original compacted height/color bytes.
    std::vector<LoadPalettePatch> palettePatches; // Untouched gaps are NOT zero-filled.
    uint32_t selectedTerritory = 0;
    bool cameraTargetValid = false;
    uint8_t cameraTileX = 0, cameraTileY = 0; // Semantic focus, not viewport offsets.
    int32_t shadingSlopeAfter = 0;
    // Draw counts in order: terrain, heights, colors, shading, rivers, scaling.
    std::array<uint64_t, 6> long31ByPhase{};
    RngSnapshot rngAfter;
    bool operator==(const LoadWorldPresentationReport&) const = default;
};

// orig004618e8 -> srand004ae594(world.rngSeed),0046a844 and its terrain,
// height, flattening, patches, shading, river and compaction leaves;0046338c;
// flags&=0xfff0; offline selection0046f5d4->0045e274->0045dfd4.
// ALL visual draws are004ae5d8/Long31, NOT Rand15. Secondary state is unchanged.
// No UI callback/cancellation, executable legacy pointer, global RNG or float.
// The previous world and RNG are explicit: not inferred from gameId/SAV.
// An unchanged world preserves the entire document, RNG and shading scratch,
// returns no map/patches and does not reset the existing presentation selection.
// Validated generation4 saves, dimensions1..40; malformed centers/tiles fail.
// Run after events and before CountShrines/intelligence/labor. Success clears
// error. Failure preserves destination/report, also when source==destination.
bool rebuildLoadWorldPresentation(const save::Document& source,
    const LoadWorldPresentationContext& context, save::Document& destination,
    LoadWorldPresentationReport& report, save::Error& error);
} // namespace dl2::simulation
