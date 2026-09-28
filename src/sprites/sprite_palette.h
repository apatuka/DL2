// sprite_palette.h - the 256-colour palette DEADLOCK.EXE realises for SPRITENW.DAT sprites.
//
// Original: the working RGBQUAD[256] at 0x0051A8A4 is assembled by
//   CreateMainWindow / FUN_00467c8c / FUN_004684d0 : entries 10..245 <- master table 0x0051ACA4
//   FUN_0046338c (SetWorldPalette)                  : 10..15 <- 0x0051A5CC, 16..79 <- world table 0x00519ECC[planetType],
//                                                     144..255 <- 0x0051A5E4
//   CreateWinGWindow                                : 80..143 <- 0x0051A7A4 while a XenoWinG picture window is open
//   FUN_004637b4 (BuildLogPalette)                  : 0..9 and 246..255 <- GetSystemPaletteEntries (Windows static colours)
// The sprite loader (FUN_00483038) remaps pixel 0 -> 255 (colour key) and 255 -> 192, so white pixels use entry 192.
#pragma once
#include "formats/palette.h"

namespace dl2::sprites {

constexpr int kWorldTypes = 7;      // planet types (DAT_004d5b1c), each with its own terrain colours (entries 16..79)
constexpr int kColourKeyIndex = 255;    // transparent index after the loader remap (0 in the file)
constexpr int kWhiteRemapIndex = 192;   // file value 255 becomes this index

// Palette used in the game views for planet type `world` (0..6). `dialogPictures` selects the
// entries 80..143 that CreateWinGWindow installs for the race pictures of the diplomacy dialogs.
Palette makeGamePalette(int world, bool dialogPictures = false);

// The 20 Windows static colours (entries 0..9 and 246..255 of every 8 bpp palette).
Rgb windowsStaticColour(int index);

}  // namespace dl2::sprites
