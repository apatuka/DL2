// iff_pbm.h - PICT decoders: type 2 (IFF FORM/PBM, ByteRun1, 8 bpp + CMAP) and type 1 (48-byte header + 640x480 RGB555).
#pragma once
#include <cstdint>
#include <span>
#include <string>
#include <vector>

#include "formats/palette.h"

namespace dl2 {

// 8-bit indexed image, row-major, top-down.
struct Image8 {
    int width = 0, height = 0;
    std::vector<uint8_t> pixels;   // width * height
    Palette palette;
    bool hasPalette = false;       // true when the picture carried its own CMAP
};

// 16-bit direct-colour image, xRGB1555 (0RRRRRGGGGGBBBBB), row-major, top-down.
struct Image16 {
    int width = 0, height = 0;
    std::vector<uint16_t> pixels;  // width * height
};

enum class PictType : uint32_t { Rgb555 = 1, IffPbm = 2, Smacker = 6 };

// Leading u32 of a PICT payload (0 if the payload is shorter than 4 bytes).
uint32_t pictType(std::span<const uint8_t> pict);

// IFF "FORM" ... "PBM " stream (BMHD/CMAP/BODY). `iff` starts at the FORM tag.
bool decodeIffPbm(std::span<const uint8_t> iff, Image8& out, std::string* err = nullptr);
// PICT type 2: u32 type = 2 followed by the IFF stream.
bool decodePictType2(std::span<const uint8_t> pict, Image8& out, std::string* err = nullptr);
// PICT type 1: 48-byte header (u32 type = 1, u16 w/h at +16/+18) then w*h u16 xRGB1555 pixels stored bottom-up.
bool decodePictType1(std::span<const uint8_t> pict, Image16& out, std::string* err = nullptr);

inline Rgb rgb555ToRgb(uint16_t v) {
    const uint8_t r = static_cast<uint8_t>((v >> 10) & 31), g = static_cast<uint8_t>((v >> 5) & 31),
                  b = static_cast<uint8_t>(v & 31);
    return Rgb{static_cast<uint8_t>((r << 3) | (r >> 2)), static_cast<uint8_t>((g << 3) | (g >> 2)),
               static_cast<uint8_t>((b << 3) | (b >> 2))};
}
inline Rgb rgb565ToRgb(uint16_t v) {
    const uint8_t r = static_cast<uint8_t>((v >> 11) & 31), g = static_cast<uint8_t>((v >> 5) & 63),
                  b = static_cast<uint8_t>(v & 31);
    return Rgb{static_cast<uint8_t>((r << 3) | (r >> 2)), static_cast<uint8_t>((g << 2) | (g >> 4)),
               static_cast<uint8_t>((b << 3) | (b >> 2))};
}

}  // namespace dl2
