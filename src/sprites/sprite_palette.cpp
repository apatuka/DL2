// sprite_palette.cpp - see sprite_palette.h
#include "sprites/sprite_palette.h"

#include "sprites/sprite_tables.h"

namespace dl2::sprites {

namespace {
Rgb toRgb(const Rgb8& c) { return Rgb{c.r, c.g, c.b}; }
}  // namespace

Rgb windowsStaticColour(int index) {
    if (index < 0 || index >= 20) return Rgb{};
    return toRgb(kWindowsStaticColours[index]);
}

Palette makeGamePalette(int world, bool dialogPictures) {
    if (world < 0 || world >= kWorldTypes) world = 0;
    Palette pal;
    // CreateMainWindow: memcpy(&working[10], &master[10], 236 * 4)
    for (int i = 0; i < 256; ++i) pal.colors[size_t(i)] = toRgb(kPaletteMaster[i]);
    // FUN_0046338c (SetWorldPalette)
    for (int i = 0; i < 6; ++i) pal.colors[size_t(10 + i)] = toRgb(kPaletteFixed6[i]);
    for (int i = 0; i < 64; ++i) pal.colors[size_t(16 + i)] = toRgb(kPaletteWorld[world][i]);
    for (int i = 0; i < 112; ++i) pal.colors[size_t(144 + i)] = toRgb(kPaletteFixed112[i]);
    // CreateWinGWindow: memcpy(&working[80], dialog64, 64 * 4)
    if (dialogPictures)
        for (int i = 0; i < 64; ++i) pal.colors[size_t(80 + i)] = toRgb(kPaletteDialog64[i]);
    // FUN_004637b4: the static system colours at both ends
    for (int i = 0; i < 10; ++i) {
        pal.colors[size_t(i)] = toRgb(kWindowsStaticColours[i]);
        pal.colors[size_t(246 + i)] = toRgb(kWindowsStaticColours[10 + i]);
    }
    return pal;
}

}  // namespace dl2::sprites
