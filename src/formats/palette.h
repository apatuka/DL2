// palette.h - 256-colour palette type and the PALT (deadcyb.cam) decoder.
#pragma once
#include <array>
#include <cstdint>
#include <span>
#include <string>

namespace dl2 {

struct Rgb {
    uint8_t r = 0, g = 0, b = 0;
};

struct Palette {
    std::array<Rgb, 256> colors{};
};

// PALT payload (1032 bytes): 12-byte header, then 255 RGBx quads for indices 0..254;
// index 255 is implicitly white.
bool decodePalt(std::span<const uint8_t> data, Palette& out, std::string* err = nullptr);

}  // namespace dl2
