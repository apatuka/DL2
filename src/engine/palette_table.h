// palette_table.h - "color table" de CYLib (offport.c / pixel.c): cabecera de 8 bytes {u16 flags; u16 count; u32 0}
// seguida de count entradas {r,g,b,flags}. Es el formato de PALT y de la paleta incrustada tras los píxeles de cada TILE.
#pragma once
#include <cstdint>
#include <memory>
#include <span>
#include <vector>

#include "formats/palette.h"

namespace dl2::engine {

struct ColorEntry {
    uint8_t r = 0, g = 0, b = 0;
    uint8_t flags = 0;   // bit0: entrada reservada (FUN_00499a4f la ignora al buscar el color más parecido)
};

enum class PixelFormat : uint8_t { Indexed8 = 1, Rgb555 = 2, Rgb565 = 3, Rgb888 = 4 };

class ColorTable {
public:
    ColorTable() = default;
    explicit ColorTable(size_t count) : entries_(count) {}

    // Decodifica el blob (8 bytes de cabecera + count*4). Devuelve false si está truncado.
    bool parse(std::span<const uint8_t> data);
    // Construye una tabla identidad de `count` grises (FUN_0048d740 + FUN_0048d713).
    static ColorTable identity(size_t count = 256);
    static ColorTable fromPalette(const Palette& pal);

    size_t size() const { return entries_.size(); }
    const ColorEntry& operator[](size_t i) const { return entries_[i]; }
    ColorEntry& operator[](size_t i) { dirty_ = true; return entries_[i]; }
    const std::vector<ColorEntry>& entries() const { return entries_; }
    std::vector<ColorEntry>& entries() { dirty_ = true; return entries_; }

    // Conversión a color nativo de 16 bits (FUN_0049b268 / FUN_0049b339).
    uint16_t to16(size_t i, PixelFormat fmt) const;
    // Tabla de 256 entradas convertida a 16 bits (se cachea por formato).
    const uint16_t* table16(PixelFormat fmt) const;
    // Índice de la entrada más parecida a (r,g,b) con la métrica original 3*dr² + 4*dg² + 2*db² (FUN_00499a4f).
    uint8_t nearest(uint8_t r, uint8_t g, uint8_t b) const;

    Palette toPalette() const;

private:
    std::vector<ColorEntry> entries_;
    mutable std::vector<uint16_t> cache555_, cache565_;
    mutable bool dirty_ = true;
};

using ColorTablePtr = std::shared_ptr<ColorTable>;

inline uint16_t rgbTo555(uint8_t r, uint8_t g, uint8_t b) {
    return uint16_t(((r & 0xf8) << 7) | ((g & 0xf8) << 2) | (b >> 3));
}
inline uint16_t rgbTo565(uint8_t r, uint8_t g, uint8_t b) {
    return uint16_t(((r & 0xf8) << 8) | ((g & 0xfc) << 3) | (b >> 3));
}
inline uint16_t rgbToNative16(uint8_t r, uint8_t g, uint8_t b, PixelFormat fmt) {
    return fmt == PixelFormat::Rgb565 ? rgbTo565(r, g, b) : rgbTo555(r, g, b);
}

}  // namespace dl2::engine
