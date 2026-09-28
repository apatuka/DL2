// tile.cpp - decodificacion y blit de TILEs (port de los blitters en ensamblador de pixel.c, 0x48e670-0x48f35c).
#include "engine/tile.h"

#include <cstring>

#include "engine/offport.h"
#include "engine/pixel.h"
#include "formats/binary.h"

namespace dl2::engine {

// ---------------------------------------------------------------------------------------------------------------
// TileView

size_t TileView::pixelBytes() const {
    if (!valid()) return 0;
    if (type() == kTileTypeRle) {
        const uint32_t po = paletteOffset();
        // El offset de paleta (+0x16) apunta al final de los datos comprimidos (relativo al inicio del payload).
        if (po > 0x1a && po <= data_.size()) return po - 0x1a;
        return data_.size() - 0x1a;
    }
    return size_t(pitch()) * size_t(height());
}

const uint8_t* TileView::paletteBlob(int index) const {
    if (!valid() || index < 0 || index >= paletteCount()) return nullptr;
    const uint8_t* p = data_.data() + 0x1a + pixelBytes();
    const uint8_t* end = data_.data() + data_.size();
    // FUN_0049b1fa: salta index tablas de (count*4 + 8) bytes.
    for (int i = 0; i < index; ++i) {
        if (p + 8 > end) return nullptr;
        p += bin::u16le(p + 2) * 4 + 8;
    }
    if (p + 8 > end) return nullptr;
    return p;
}

bool TileView::palette(int index, ColorTable& out) const {
    const uint8_t* blob = paletteBlob(index);
    if (!blob) return false;
    const size_t avail = size_t(data_.data() + data_.size() - blob);
    return out.parse(std::span<const uint8_t>(blob, avail));
}

bool TileView::pixelAt(int x, int y, uint32_t& value) const {
    if (!valid() || x < 0 || y < 0 || x >= width() || y >= height()) return false;
    const int bpp = bytesPerPixel();
    if (type() == kTileTypeRle) {
        // FUN_0049b47f: runs {u16 endX, u16 len|0x8000} + len pixeles.
        const uint8_t* base = pixels();
        const uint8_t* p = base + bin::u32le(base + size_t(y) * 4);
        for (;;) {
            const int endX = bin::u16le(p);
            const uint16_t lenWord = bin::u16le(p + 2);
            const int len = lenWord & 0x7fff;
            p += 4;
            const int startX = endX - len;
            if (x >= startX && x < endX) {
                value = bpp == 1 ? p[x - startX] : bin::u16le(p + (x - startX) * 2);
                return true;
            }
            if (x < startX || (lenWord & 0x8000)) return false;
            p += size_t(len) * size_t(bpp);
        }
    }
    const uint8_t* p = pixels() + size_t(y) * size_t(pitch()) + size_t(x) * size_t(bpp);
    value = bpp == 1 ? *p : bin::u16le(p);
    return true;
}

std::vector<uint8_t> TileView::decode8(uint8_t transparent) const {
    std::vector<uint8_t> out;
    if (!valid()) return out;
    const int w = width(), h = height();
    if (type() == kTileType8) {
        out.resize(size_t(w) * size_t(h));
        for (int y = 0; y < h; ++y) std::memcpy(out.data() + size_t(y) * size_t(w), pixels() + size_t(y) * size_t(pitch()), size_t(w));
        return out;
    }
    if (type() == kTileTypeRle && bytesPerPixel() == 1) {
        out.assign(size_t(w) * size_t(h), transparent);
        const uint8_t* base = pixels();
        const uint8_t* end = data_.data() + data_.size();
        for (int y = 0; y < h; ++y) {
            const uint8_t* p = base + bin::u32le(base + size_t(y) * 4);
            for (;;) {
                if (p + 4 > end) break;
                const int endX = bin::u16le(p);
                const uint16_t lenWord = bin::u16le(p + 2);
                const int len = lenWord & 0x7fff;
                p += 4;
                const int startX = endX - len;
                for (int i = 0; i < len; ++i) {
                    const int x = startX + i;
                    if (x >= 0 && x < w && p + i < end) out[size_t(y) * size_t(w) + size_t(x)] = p[i];
                }
                p += len;
                if (lenWord & 0x8000) break;
            }
        }
        return out;
    }
    return out;  // tipo 1 (16 bpp) no se decodifica a 8 bits
}

// ---------------------------------------------------------------------------------------------------------------
// Remap8

Remap8::Remap8() {
    for (int i = 0; i < 256; ++i) {
        table0[i] = table1[i] = uint8_t(i);
        palR[i] = palG[i] = palB[i] = uint8_t(i);
    }
    for (int i = 0; i < 4096; ++i) rgb444ToIndex[i] = uint8_t(i & 0xff);
}

Remap8& Remap8::current() {
    static Remap8 r;
    return r;
}

void Remap8::buildFromPalette(const ColorTable& pal) {
    // FUN_0049987a(0xfe entradas, paleta, 4 bits): para cada celda 4-4-4 el indice mas cercano (distancia euclidea).
    const size_t n = pal.size() < 254 ? pal.size() : 254;
    for (size_t i = 0; i < 256; ++i) {
        const ColorEntry& e = i < pal.size() ? pal[i] : ColorEntry{};
        palR[i] = e.r;
        palG[i] = e.g;
        palB[i] = e.b;
    }
    for (int r = 0; r < 16; ++r)
        for (int g = 0; g < 16; ++g)
            for (int b = 0; b < 16; ++b) {
                const int cr = (r << 4) | 8, cg = (g << 4) | 8, cb = (b << 4) | 8;
                long best = 1L << 30;
                uint8_t bi = 0;
                for (size_t i = 0; i < n; ++i) {
                    const long dr = cr - pal[i].r, dg = cg - pal[i].g, db = cb - pal[i].b;
                    const long d = dr * dr + dg * dg + db * db;
                    if (d < best) { best = d; bi = uint8_t(i); }
                }
                rgb444ToIndex[(r << 8) | (g << 4) | b] = bi;
            }
}

// ---------------------------------------------------------------------------------------------------------------
// Blitters

namespace {

struct BlitArgs {
    const TileView* tile;
    OffPort* port;
    int dstX, dstY;        // esquina superior izquierda ya recortada
    int clipLeft, clipTop; // pixeles del tile descartados por la izquierda / arriba
    int cols, rows;        // pixeles visibles
    int mode;
    const uint16_t* pal16; // paleta del tile convertida (modo 8->16)
    PixelFormat fmt;
};

// Tipo 2 (8 bpp lineal), destino 8 bpp: modos 0..6 (tabla PTR_LAB_0051e2f0, indice 0).
void blitT2to8(const BlitArgs& a) {
    const Remap8& rm = Remap8::current();
    const Pixel::ShadeTables* blendT = nullptr;
    const int level = Pixel::blendLevel();
    if (a.mode == 5) blendT = &Pixel::shadeTables(PixelFormat::Rgb555);
    const int pitch = a.tile->pitch();
    for (int y = 0; y < a.rows; ++y) {
        const uint8_t* s = a.tile->pixels() + size_t(a.clipTop + y) * size_t(pitch) + size_t(a.clipLeft);
        uint8_t* d = a.port->pixelPtr(a.dstX, a.dstY + y);
        switch (a.mode) {
            case 0:  // T2_M0: color clave 0xff
                for (int x = 0; x < a.cols; ++x) if (s[x] != 0xff) d[x] = s[x];
                break;
            case 1:  // T2_M1: 0xff transparente, 0xfe sombrea el destino con table1
                for (int x = 0; x < a.cols; ++x) {
                    if (s[x] == 0xff) continue;
                    d[x] = s[x] == 0xfe ? rm.table1[d[x]] : s[x];
                }
                break;
            case 2:  // T2_M2: origen remapeado con table0; 0xfe sombrea destino; 0xff transparente
                for (int x = 0; x < a.cols; ++x) {
                    if (s[x] == 0xff) continue;
                    d[x] = s[x] == 0xfe ? rm.table1[d[x]] : rm.table0[s[x]];
                }
                break;
            case 3:  // T2_M3: mascara: donde el origen != 0xff, destino = table1[destino]
                for (int x = 0; x < a.cols; ++x) if (s[x] != 0xff) d[x] = rm.table1[d[x]];
                break;
            case 4:  // T2_M4: idem con table0
                for (int x = 0; x < a.cols; ++x) if (s[x] != 0xff) d[x] = rm.table0[d[x]];
                break;
            case 5: {  // T2_M5: mezcla por componentes (paleta R/G/B, tabla de diferencias, 444 -> indice)
                const uint8_t* bl = blendT->blend8[level];
                for (int x = 0; x < a.cols; ++x) {
                    const uint8_t sv = s[x];
                    if (sv >= 0xfe) continue;
                    const uint8_t dv = d[x];
                    const int r = (bl[(int(rm.palR[dv]) - int(rm.palR[sv])) & 0x1ff] + rm.palR[sv]) & 0xf0;
                    const int g = (bl[(int(rm.palG[dv]) - int(rm.palG[sv])) & 0x1ff] + rm.palG[sv]) & 0xf0;
                    const int b = (bl[(int(rm.palB[dv]) - int(rm.palB[sv])) & 0x1ff] + rm.palB[sv]) & 0xf0;
                    d[x] = rm.rgb444ToIndex[(r << 4) | g | (b >> 4)];
                }
                break;
            }
            case 6:  // T2_M6: tabla 2D [src][dst]
                if (rm.table2d.size() >= 65536)
                    for (int x = 0; x < a.cols; ++x) if (s[x] != 0xff) d[x] = rm.table2d[size_t(s[x]) * 256 + d[x]];
                break;
            default:
                break;
        }
    }
}

// Tipo 2, destino 16 bpp con paleta (PTR_LAB_0051e310): modo 0 (clave 0xff) y 1 (0xf7..0xfe sombrean el destino).
void blitT2to16(const BlitArgs& a) {
    const int pitch = a.tile->pitch();
    for (int y = 0; y < a.rows; ++y) {
        const uint8_t* s = a.tile->pixels() + size_t(a.clipTop + y) * size_t(pitch) + size_t(a.clipLeft);
        uint16_t* d = reinterpret_cast<uint16_t*>(a.port->pixelPtr(a.dstX, a.dstY + y));
        if (a.mode == 0) {
            for (int x = 0; x < a.cols; ++x) if (s[x] != 0xff) d[x] = a.pal16[s[x]];
        } else if (a.mode == 1) {
            for (int x = 0; x < a.cols; ++x) {
                const uint8_t v = s[x];
                if (v == 0xff) continue;
                if (v >= 0xf7) d[x] = Pixel::shadePixel(d[x], (v + 1) & 7, a.fmt);
                else d[x] = a.pal16[v];
            }
        }
    }
}

// Tipo 1 con destino 8 bpp (PTR_FUN_0051e290[0] = FUN_0048e670): copia de `cols` bytes por fila (tal cual el original).
void blitT1to8(const BlitArgs& a) {
    if (a.mode != 0) return;
    const int pitch = a.tile->pitch();
    const int bpp = a.tile->bytesPerPixel();
    for (int y = 0; y < a.rows; ++y) {
        const uint8_t* s = a.tile->pixels() + size_t(a.clipTop + y) * size_t(pitch) + size_t(a.clipLeft) * size_t(bpp);
        std::memcpy(a.port->pixelPtr(a.dstX, a.dstY + y), s, size_t(a.cols));
    }
}

// "Tipo 1" con destino 16 bpp y origen 8 bpp (T1_H1_M0 = FUN_0048f264): copia opaca a traves de la paleta.
void blitT1_8to16(const BlitArgs& a) {
    if (a.mode != 0) return;
    const int pitch = a.tile->pitch();
    for (int y = 0; y < a.rows; ++y) {
        const uint8_t* s = a.tile->pixels() + size_t(a.clipTop + y) * size_t(pitch) + size_t(a.clipLeft);
        uint16_t* d = reinterpret_cast<uint16_t*>(a.port->pixelPtr(a.dstX, a.dstY + y));
        for (int x = 0; x < a.cols; ++x) d[x] = a.pal16[s[x]];
    }
}

// Tipo 1, 16 -> 16 (FUN_0048e670 con cols*2 bytes).
void blitT1to16(const BlitArgs& a) {
    if (a.mode != 0) return;
    const int pitch = a.tile->pitch();
    for (int y = 0; y < a.rows; ++y) {
        const uint8_t* s = a.tile->pixels() + size_t(a.clipTop + y) * size_t(pitch) + size_t(a.clipLeft) * 2;
        std::memcpy(a.port->pixelPtr(a.dstX, a.dstY + y), s, size_t(a.cols) * 2);
    }
}

// Recorre los runs visibles de una fila de un tile tipo 3 llamando a fn(dstX, srcPtr, count) por tramo visible.
template <typename Fn>
void forEachRun(const TileView& tile, int row, int clipLeft, int cols, int bpp, Fn fn) {
    const uint8_t* base = tile.pixels();
    const uint8_t* end = tile.raw() + tile.size();
    const uint8_t* p = base + bin::u32le(base + size_t(row) * 4);
    const int right = clipLeft + cols;
    for (;;) {
        if (p + 4 > end) return;
        const int endX = bin::u16le(p);
        const uint16_t lenWord = bin::u16le(p + 2);
        const int len = lenWord & 0x7fff;
        p += 4;
        const int startX = endX - len;
        // Tramo visible [max(startX, clipLeft), min(endX, right))
        const int vis0 = startX > clipLeft ? startX : clipLeft;
        const int vis1 = endX < right ? endX : right;
        if (vis1 > vis0) fn(vis0 - clipLeft, p + size_t(vis0 - startX) * size_t(bpp), vis1 - vis0);
        if (endX >= right || (lenWord & 0x8000)) return;
        p += size_t(len) * size_t(bpp);
    }
}

// Tipo 3, destino 8 bpp (T3_M0, corregido para usar la tabla de filas): modo 0.
void blitT3to8(const BlitArgs& a) {
    if (a.mode != 0) return;
    for (int y = 0; y < a.rows; ++y) {
        uint8_t* d = a.port->pixelPtr(a.dstX, a.dstY + y);
        forEachRun(*a.tile, a.clipTop + y, a.clipLeft, a.cols, 1, [&](int dx, const uint8_t* s, int n) {
            std::memcpy(d + dx, s, size_t(n));
        });
    }
}

// Tipo 3, destino 16 bpp con paleta (PTR_LAB_0051e230, indice 1): modos 0, 1, 5 y 7.
void blitT3to16(const BlitArgs& a) {
    for (int y = 0; y < a.rows; ++y) {
        uint16_t* d = reinterpret_cast<uint16_t*>(a.port->pixelPtr(a.dstX, a.dstY + y));
        switch (a.mode) {
            case 0:  // T3_H1_M0
                forEachRun(*a.tile, a.clipTop + y, a.clipLeft, a.cols, 1, [&](int dx, const uint8_t* s, int n) {
                    for (int i = 0; i < n; ++i) d[dx + i] = a.pal16[s[i]];
                });
                break;
            case 1:  // T3_H1_M1: valores >= 0xf7 sombrean el destino (nivel (v+1)&7)
                forEachRun(*a.tile, a.clipTop + y, a.clipLeft, a.cols, 1, [&](int dx, const uint8_t* s, int n) {
                    for (int i = 0; i < n; ++i) {
                        const uint8_t v = s[i];
                        d[dx + i] = v >= 0xf7 ? Pixel::shadePixel(d[dx + i], (v + 1) & 7, a.fmt) : a.pal16[v];
                    }
                });
                break;
            case 5:  // T3_H1_M5: mezcla; un valor >= 0xf7 salta el resto del run
                forEachRun(*a.tile, a.clipTop + y, a.clipLeft, a.cols, 1, [&](int dx, const uint8_t* s, int n) {
                    for (int i = 0; i < n; ++i) {
                        const uint8_t v = s[i];
                        if (v >= 0xf7) break;
                        d[dx + i] = Pixel::blendPixel(d[dx + i], a.pal16[v], a.fmt);
                    }
                });
                break;
            case 7:  // T3_H1_M7: como el 1 con la tabla de 4 niveles
                forEachRun(*a.tile, a.clipTop + y, a.clipLeft, a.cols, 1, [&](int dx, const uint8_t* s, int n) {
                    for (int i = 0; i < n; ++i) {
                        const uint8_t v = s[i];
                        d[dx + i] = v >= 0xf7 ? Pixel::shadePixel4(d[dx + i], (v + 1) & 7, a.fmt) : a.pal16[v];
                    }
                });
                break;
            default:
                break;
        }
    }
}

// Tipo 3 de 16 bpp sobre 16 bpp (T3_H2_M0).
void blitT3_16to16(const BlitArgs& a) {
    if (a.mode != 0) return;
    for (int y = 0; y < a.rows; ++y) {
        uint16_t* d = reinterpret_cast<uint16_t*>(a.port->pixelPtr(a.dstX, a.dstY + y));
        forEachRun(*a.tile, a.clipTop + y, a.clipLeft, a.cols, 2, [&](int dx, const uint8_t* s, int n) {
            std::memcpy(d + dx, s, size_t(n) * 2);
        });
    }
}

void dispatch(const TileView& tile, int x, int y, int mode, OffPort& port, const Rect& clip, int blitIndex, bool copyPalette) {
    (void)copyPalette;
    if (!tile.valid()) return;
    if (mode == -1) mode = tile.defaultMode();
    if (mode < 0 || mode > 7) return;
    x -= tile.hotX();
    y -= tile.hotY();
    int w = tile.width(), h = tile.height();
    // Descarte rapido (FUN_0049aa95).
    if (!(clip.x0 <= w + x && x < clip.x1 && clip.y0 <= h + y && y < clip.y1)) return;
    int clipLeft = 0, clipTop = 0;
    if (x < clip.x0) { clipLeft = clip.x0 - x; w -= clipLeft; x = clip.x0; }
    if (clip.x1 <= x + w) w = clip.x1 - x;
    if (y < clip.y0) { clipTop = clip.y0 - y; h -= clipTop; y = clip.y0; }
    if (clip.y1 <= y + h) h = clip.y1 - y;
    if (w <= 0 || h <= 0) return;

    BlitArgs a{&tile, &port, x, y, clipLeft, clipTop, w, h, mode, nullptr, port.format()};
    ColorTable pal;
    std::vector<uint16_t> pal16;
    if (blitIndex == 1) {
        // FUN_0049b1fa + FUN_0049b268: paleta del tile convertida al formato del port (o gris si no tiene).
        if (!tile.palette(0, pal)) pal = ColorTable::identity(256);
        pal16.assign(256, 0);
        for (size_t i = 0; i < 256 && i < pal.size(); ++i) pal16[i] = pal.to16(i, port.format());
        a.pal16 = pal16.data();
    }
    switch (tile.type()) {
        case kTileType8:
            if (blitIndex == 0) blitT2to8(a);
            else if (blitIndex == 1) blitT2to16(a);
            break;
        case kTileType16:
            if (blitIndex == 0) blitT1to8(a);
            else if (blitIndex == 1) blitT1_8to16(a);
            else blitT1to16(a);
            break;
        case kTileTypeRle:
            if (blitIndex == 0) blitT3to8(a);
            else if (blitIndex == 1) blitT3to16(a);
            else blitT3_16to16(a);
            break;
        default:
            break;
    }
}

}  // namespace

void drawTile(const TileView& tile, int x, int y, int mode, bool copyPalette) {
    OffPort* port = Pixel::port();
    if (!port) return;
    dispatch(tile, x, y, mode, *port, Pixel::clip(), Pixel::blitModeIndex(), copyPalette);
}

void drawTileTo(const TileView& tile, int x, int y, int mode, OffPort& port) {
    // FUN_0049ae0c: el indice de blit se deduce del port y de los bytes/pixel del tile.
    const uint32_t bm = (uint32_t(port.bpp()) << 16) | uint32_t(tile.bytesPerPixel() * 8);
    const int idx = bm == kBlit8to16 ? 1 : (bm == kBlit16to16 ? 2 : 0);
    dispatch(tile, x, y, mode, port, port.viewRect(), idx, true);
}

Rect tileRect(const TileView& tile, int x, int y) {
    return Rect::xywh(x - tile.hotX(), y - tile.hotY(), tile.width(), tile.height());
}

}  // namespace dl2::engine
