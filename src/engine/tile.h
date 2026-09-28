// tile.h - TILE de CYLib (img.c/pixel.c): vista sobre el payload (cabecera de 13 shorts, pixeles en +0x1a y
// paleta incrustada tras ellos) y el dibujado con los 8 modos de blit de las tablas DAT_0069ee90/94/98.
#pragma once
#include <cstdint>
#include <memory>
#include <span>
#include <vector>

#include "engine/engine_types.h"
#include "engine/palette_table.h"

namespace dl2::engine {

class OffPort;

// Tipos de TILE (short +0): 1 = 16 bpp lineal, 2 = 8 bpp lineal, 3 = codificado por filas (runs).
enum TileType : uint16_t { kTileType16 = 1, kTileType8 = 2, kTileTypeRle = 3 };

// Vista de solo lectura sobre un TILE en memoria (el payload tal cual sale del CAM).
class TileView {
public:
    TileView() = default;
    explicit TileView(std::span<const uint8_t> data) : data_(data) {}
    bool valid() const { return data_.size() >= 0x1a && type() >= 1 && type() <= 3; }

    const uint8_t* raw() const { return data_.data(); }
    size_t size() const { return data_.size(); }
    uint16_t s16u(size_t off) const { return uint16_t(data_[off] | (data_[off + 1] << 8)); }
    int16_t s16(size_t off) const { return int16_t(s16u(off)); }

    uint16_t type() const { return s16u(0); }
    int height() const { return s16(2); }
    int width() const { return s16(4); }
    int pitch() const { return s16(6); }          // bytes por fila (tipo 1/2)
    uint16_t flags() const { return s16u(8); }     // bits0-1 = bytes/pixel-1; bits2-3 = formato 16 bpp (4=555, 8=565); bit4 = volteado
    int bytesPerPixel() const { return (flags() & 3) + 1; }
    int hotX() const { return s16(10); }
    int hotY() const { return s16(12); }
    int defaultMode() const { return s16(14); }
    int paletteCount() const { return s16(0x14); }     // numero de tablas de color tras los pixeles
    uint32_t paletteOffset() const { return uint32_t(data_[0x16]) | (uint32_t(data_[0x17]) << 8) | (uint32_t(data_[0x18]) << 16) | (uint32_t(data_[0x19]) << 24); }
    const uint8_t* pixels() const { return data_.data() + 0x1a; }
    size_t pixelBytes() const;
    // Tabla de color n (FUN_0049b1fa): blob {u16,u16 count,u32, entradas}. Devuelve nullptr si no existe.
    const uint8_t* paletteBlob(int index = 0) const;
    // Decodifica la tabla de color n a un ColorTable.
    bool palette(int index, ColorTable& out) const;

    // Pixel (x,y) sin dibujar (FUN_0049b5b7): devuelve false si esta fuera o es transparente (tipo 3).
    bool pixelAt(int x, int y, uint32_t& value) const;

    // Decodifica a un buffer indexado (tipo 2/3) o de 16 bits (tipo 1) lineal de width*height, 0xff = transparente
    // para tipo 3 (los huecos entre runs).
    std::vector<uint8_t> decode8(uint8_t transparent = 0xff) const;

private:
    std::span<const uint8_t> data_;
};

// Tablas de remapeo de 8 bpp usadas por los modos 1..6 (DAT_0051c3d0/d4/d8/dc, DAT_0051d3dc..).
struct Remap8 {
    uint8_t table0[256];        // 0x51c3d0: remapeo del origen (modo 2) / del destino (modo 4)
    uint8_t table1[256];        // 0x51c3d4: remapeo del destino (modos 1, 2, 3)
    std::vector<uint8_t> table2d;  // 0x51c3d8: 256x256 [src][dst] (modo 6)
    uint8_t rgb444ToIndex[4096];   // 0x51c3dc: (r4<<8|g4<<4|b4) -> indice (modo 5)
    uint8_t palR[256], palG[256], palB[256];  // 0x51d3dc/0x51d4dc/0x51d5dc
    Remap8();
    // FUN_00499a30 / FUN_0049987a: construye rgb444ToIndex y palR/G/B a partir de la paleta.
    void buildFromPalette(const ColorTable& pal);
    static Remap8& current();
};

// FUN_0049aa95: dibuja el tile en el port actual (Pixel::port()) en (x,y) menos su hotspot, con recorte al clip
// actual y el modo 0..7 (-1 = modo por defecto del tile). `copyPalette` (param_5) obliga a usar una copia de la
// paleta al convertirla (no altera el tile). El modo de blit debe haberse fijado con Pixel::setBlitMode.
void drawTile(const TileView& tile, int x, int y, int mode = -1, bool copyPalette = true);
// FUN_0049ae0c: igual pero sobre un port explicito usando su rectangulo de vista como clip.
void drawTileTo(const TileView& tile, int x, int y, int mode, OffPort& port);
// Rectangulo que ocupa el tile dibujado en (x,y) (hotspot aplicado).
Rect tileRect(const TileView& tile, int x, int y);

}  // namespace dl2::engine
