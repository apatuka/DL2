// tile_image.h - TILE sprite header (deadcyb.cam, CYLib img.c layout); pixel decoding is not implemented yet.
#pragma once
#include <cstddef>
#include <cstdint>
#include <span>

#include "formats/binary.h"

namespace dl2 {

// Header of every TILE payload: 8 shorts documented in docs/FORMATS.md, then 5 shorts of unknown
// meaning; pixel data starts at +0x1a. Observed: type 2, e.g. h=47 w=33 pitch=33.
struct TileHeader {
    uint16_t type = 0;      // 1 = 16 bpp, 2 = 8 bpp linear rows of `pitch` bytes, 3 = row-coded (RLE)
    uint16_t height = 0;
    uint16_t width = 0;
    uint16_t pitch = 0;
    uint16_t flags = 0;     // bits 0-1 = bytes per pixel - 1
    int16_t hotX = 0;
    int16_t hotY = 0;
    uint16_t drawMode = 0;  // default blit routine 0..7 (normal, colour key, shadow, ...)
    uint16_t unknown[5] = {};  // +16..+25 (observed e.g. 0x57, 0, 1, 0x629, 0)
};

constexpr size_t kTileHeaderSize = 0x1a;  // pixel data offset

inline bool parseTileHeader(std::span<const uint8_t> tile, TileHeader& out) {
    if (tile.size() < kTileHeaderSize) return false;
    const uint8_t* p = tile.data();
    out.type = bin::u16le(p);
    out.height = bin::u16le(p + 2);
    out.width = bin::u16le(p + 4);
    out.pitch = bin::u16le(p + 6);
    out.flags = bin::u16le(p + 8);
    out.hotX = static_cast<int16_t>(bin::u16le(p + 10));
    out.hotY = static_cast<int16_t>(bin::u16le(p + 12));
    out.drawMode = bin::u16le(p + 14);
    for (size_t i = 0; i < 5; ++i) out.unknown[i] = bin::u16le(p + 16 + i * 2);
    return out.type >= 1 && out.type <= 3;
}

// TODO: decode the pixel data at +0x1a. Type 2 should be `height` rows of `pitch` bytes (8 bpp),
// type 3 is row-coded (see FUN_0049aa95 in the decompiled EXE) and type 1 is 16 bpp; the payload is
// larger than header + width*height, so confirm the trailing data before implementing.

}  // namespace dl2
