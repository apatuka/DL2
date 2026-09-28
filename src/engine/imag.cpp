// imag.cpp - acceso a IMAG (img.c) y dibujado de rejillas de tiles.
#include "engine/imag.h"

#include "engine/pixel.h"
#include "formats/binary.h"

namespace dl2::engine {

ImagCell ImagLayer::cell(int row, int col) const {
    ImagCell c;
    if (!cells || row < 0 || col < 0 || row >= rows || col >= cols) return ImagCell{0, 0, 0x40000000u};
    const uint8_t* p = cells + (size_t(row) * size_t(cols) + size_t(col)) * 8;
    c.x = int16_t(bin::u16le(p));
    c.y = int16_t(bin::u16le(p + 2));
    c.ref = bin::u32le(p + 4);
    return c;
}

bool ImagView::valid() const {
    if (data_.size() < 0x18) return false;
    const size_t n = bin::u32le(data_.data() + 0x14);
    return data_.size() >= 0x18 + n * 8;
}

uint32_t ImagView::version() const { return data_.size() >= 4 ? bin::u32le(data_.data()) : 0; }
int ImagView::entryCount() const { return valid() ? int(bin::u32le(data_.data() + 0x14)) : 0; }

ImagEntry ImagView::entry(int i) const {
    ImagEntry e;
    if (i < 0 || i >= entryCount()) return e;
    const uint8_t* p = data_.data() + 0x18 + size_t(i) * 8;
    e.id = bin::u32le(p);
    e.offset = bin::u32le(p + 4);
    return e;
}

int ImagView::findEntry(uint32_t id24, int nth, uint32_t* fullId) const {
    const int n = entryCount();
    for (int i = 0; i < n; ++i) {
        const ImagEntry e = entry(i);
        if ((e.id & 0xffffff) == (id24 & 0xffffff)) {
            if (nth == 0) {
                if (fullId) *fullId = e.id;
                return i;
            }
            --nth;
        }
    }
    return -1;
}

int ImagView::layerCount(int entryIndex) const {
    const ImagEntry e = entry(entryIndex);
    if (e.offset == 0 || e.offset + 4 > data_.size()) return 0;
    return int(bin::u32le(data_.data() + e.offset));
}

ImagLayer ImagView::layer(int entryIndex, int layerIndex) const {
    ImagLayer L;
    const ImagEntry e = entry(entryIndex);
    if (e.offset == 0 || layerIndex < 0 || layerIndex >= layerCount(entryIndex)) return L;
    const size_t base = e.offset;
    const size_t offTab = base + 0x40 + size_t(layerIndex) * 4;
    if (offTab + 4 > data_.size()) return L;
    const size_t lo = base + bin::u32le(data_.data() + offTab);
    if (lo + 0x20 > data_.size()) return L;
    const uint8_t* p = data_.data() + lo;
    L.offX = int16_t(bin::u16le(p + 0x18));
    L.offY = int16_t(bin::u16le(p + 0x1a));
    L.rows = bin::u16le(p + 0x1c);
    L.cols = bin::u16le(p + 0x1e);
    if (lo + 0x20 + size_t(L.rows) * size_t(L.cols) * 8 > data_.size()) { L.rows = L.cols = 0; return L; }
    L.cells = p + 0x20;
    return L;
}

bool ImagView::cell(uint32_t id24, int layerIndex, int row, int col, ImagCell& out, int nth) const {
    const int ei = findEntry(id24, nth);
    if (ei < 0) return false;
    const ImagLayer L = layer(ei, layerIndex);
    if (!L.cells || row < 0 || col < 0 || row >= L.rows || col >= L.cols) return false;
    out = L.cell(row, col);
    return true;
}

namespace {

// Recorre las entradas con el mismo id de 24 bits como FUN_00496e80 / FUN_00496cc3: la entrada principal
// (byte alto 0) usa `layer`/`col`; las "overlay" (byte alto != 0) usan la columna 0 y se desplazan por el
// offX/offY de la capa correspondiente de la ultima entrada principal.
template <typename Fn>
void forEachCell(const ImagView& imag, uint32_t id24, int layer, int col, Fn fn) {
    int offX = 0, offY = 0, baseLayer = 0;
    for (int nth = 0;; ++nth) {
        uint32_t fullId = 0;
        const int ei = imag.findEntry(id24, nth, &fullId);
        if (ei < 0) break;
        const int useCol = (fullId == (id24 & 0xffffff)) ? col : 0;
        if ((fullId >> 24) == 0) {
            baseLayer = layer;
            offX = offY = 0;
        } else if (baseLayer < imag.layerCount(ei)) {
            const ImagLayer bl = imag.layer(ei, baseLayer);
            offX = bl.offX;
            offY = bl.offY;
        }
        if (layer >= imag.layerCount(ei)) continue;
        const ImagLayer L = imag.layer(ei, layer);
        if (!L.cells) continue;
        for (int row = 0; row < L.rows; ++row) {
            if (useCol >= L.cols) continue;
            fn(L.cell(row, useCol), offX, offY);
        }
    }
}

}  // namespace

void drawImag(const ImagView& imag, uint32_t id24, int layer, int col, int x, int y, int mode, const TileLookup& getTile) {
    if (!imag.valid()) return;
    forEachCell(imag, id24, layer, col, [&](const ImagCell& c, int offX, int offY) {
        if (c.empty()) return;
        const TileView t = getTile(c.tileId());
        if (!t.valid()) return;
        const uint32_t prev = Pixel::setBlitMode(Pixel::blitModeFor(t.bytesPerPixel() * 8));
        drawTile(t, c.x + x + offX, c.y + y + offY, mode == -1 ? t.defaultMode() : mode, true);
        Pixel::setBlitMode(prev);
    });
}

bool imagBounds(const ImagView& imag, uint32_t id24, int layer, int col, Rect& out, const TileLookup& getTile) {
    out = Rect{};
    bool any = false;
    if (!imag.valid()) return false;
    forEachCell(imag, id24, layer, col, [&](const ImagCell& c, int offX, int offY) {
        if (c.empty() || (c.ref & 0x10000000u)) return;
        const TileView t = getTile(c.tileId());
        if (!t.valid()) return;
        const Rect r = tileRect(t, c.x + offX, c.y + offY);
        if (!any) { out = r; any = true; } else out.unite(r);
    });
    return any && !out.empty();
}

TileView imagCellTile(const ImagView& imag, uint32_t id24, int layer, int row, int col, const TileLookup& getTile,
                      uint32_t* cellFlags) {
    ImagCell c;
    if (!imag.cell(id24, layer, row, col, c)) return TileView{};
    if (cellFlags) *cellFlags = c.ref;
    if (c.empty() || c.is3d()) return TileView{};
    return getTile(c.tileId());
}

}  // namespace dl2::engine
