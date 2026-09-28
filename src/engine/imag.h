// imag.h - IMAG de CYLib (img.c): coleccion de "imagenes" identificadas por id de 24 bits, cada una con capas
// (layers) que son rejillas rows x cols de celdas {x, y, tileId|flags} que referencian TILEs de la libreria.
#pragma once
#include <cstdint>
#include <functional>
#include <span>
#include <vector>

#include "engine/engine_types.h"
#include "engine/tile.h"

namespace dl2::engine {

class ResourceManager;
struct ResHandle;

// Celda de una capa (8 bytes): posicion relativa y referencia al tile.
struct ImagCell {
    int16_t x = 0, y = 0;
    uint32_t ref = 0;   // bits 0-23: indice de TILE; bit30 (0x40000000): vacia; bit28 (0x10000000): objeto CY3D;
                        // bit 0x10 del byte 3 se usa como "oculta" en FUN_00496cc3
    uint32_t tileId() const { return ref & 0xffffff; }
    bool empty() const { return (ref & 0x40000000u) != 0; }
    bool is3d() const { return (ref & 0x10000000u) != 0; }
};

struct ImagLayer {
    int16_t offX = 0, offY = 0;   // +0x18/+0x1a: desplazamiento de las entradas "overlay" (byte alto del id != 0)
    uint16_t rows = 0, cols = 0;  // +0x1c/+0x1e
    const uint8_t* cells = nullptr;
    ImagCell cell(int row, int col) const;
};

struct ImagEntry {
    uint32_t id = 0;      // id completo (24 bits + flags en el byte alto)
    uint32_t offset = 0;  // offset de la imagen dentro del payload
};

class ImagView {
public:
    ImagView() = default;
    explicit ImagView(std::span<const uint8_t> data) : data_(data) {}
    bool valid() const;

    uint32_t version() const;
    int entryCount() const;                 // +0x14
    ImagEntry entry(int i) const;           // tabla en +0x18
    // FUN_0049698a: n-esima entrada cuyo id de 24 bits coincide (n = 0: la principal). Devuelve el indice de la
    // tabla o -1. *fullId recibe el id con sus flags.
    int findEntry(uint32_t id24, int nth, uint32_t* fullId = nullptr) const;
    int layerCount(int entryIndex) const;   // u32 en +0 de la imagen
    ImagLayer layer(int entryIndex, int layerIndex) const;   // offsets en +0x40 de la imagen
    // FUN_00496c03 / FUN_00496b64: celda (row, col) de la capa `layer` de la imagen `id24`; false si no existe.
    bool cell(uint32_t id24, int layer, int row, int col, ImagCell& out, int nth = 0) const;

private:
    std::span<const uint8_t> data_;
};

// FUN_00496e80: dibuja la columna `col` (todas las filas) de la capa `layer` de la imagen `id24` en (x,y) del port
// actual, incluyendo las entradas "overlay" del mismo id. mode = -1 usa el modo por defecto de cada tile.
// `getTile` resuelve un indice de TILE a su vista (normalmente ResourceManager::tile).
using TileLookup = std::function<TileView(uint32_t tileId)>;
void drawImag(const ImagView& imag, uint32_t id24, int layer, int col, int x, int y, int mode, const TileLookup& getTile);
// FUN_00496cc3: rectangulo que ocupa la columna `col` de la capa (union de los tiles). false si esta vacio.
bool imagBounds(const ImagView& imag, uint32_t id24, int layer, int col, Rect& out, const TileLookup& getTile);
// FUN_00496c61: tile de la celda (row, col); devuelve una vista vacia si no hay tile (o es CY3D).
TileView imagCellTile(const ImagView& imag, uint32_t id24, int layer, int row, int col, const TileLookup& getTile,
                      uint32_t* cellFlags = nullptr);

}  // namespace dl2::engine
