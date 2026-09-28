// offport.cpp - implementacion de OffPort (superficies de CYLib) sobre memoria.
#include "engine/offport.h"

#include <algorithm>
#include <cstring>

namespace dl2::engine {

bool OffPort::create(int w, int h, int bpp, PixelFormat fmt16) {
    if (w <= 0 || h <= 0 || (bpp != 8 && bpp != 16)) return false;
    width_ = w;
    height_ = h;
    bpp_ = bpp;
    // FUN_0048be9b: pitch = bytes por fila redondeado a multiplo de 4.
    pitch_ = (w * ((bpp + 7) >> 3) + 3) & ~3;
    format_ = bpp == 8 ? PixelFormat::Indexed8 : fmt16;
    pixels_.assign(size_t(pitch_) * size_t(h), 0);
    view_ = Rect{0, 0, w, h};
    originX_ = originY_ = 0;
    return true;
}

void OffPort::clear(uint32_t c) {
    if (bpp_ == 8) {
        std::memset(pixels_.data(), int(c & 0xff), pixels_.size());
    } else {
        fillRaw(0, 0, width_, height_, c);
    }
}

uint32_t OffPort::nativeColor(ColorRef c) const {
    if (!colorIsRgb(c)) return c;
    const uint8_t r = uint8_t(c >> 16), g = uint8_t(c >> 8), b = uint8_t(c);
    if (bpp_ == 8) return palette_ ? palette_->nearest(r, g, b) : 0;
    return rgbToNative16(r, g, b, format_);
}

void OffPort::fillRaw(int x0, int y0, int x1, int y1, uint32_t c) {
    if (x0 >= x1 || y0 >= y1) return;
    if (bpp_ == 8) {
        for (int y = y0; y < y1; ++y) std::memset(pixelPtr(x0, y), int(c & 0xff), size_t(x1 - x0));
    } else {
        const uint16_t v = uint16_t(c);
        for (int y = y0; y < y1; ++y) {
            uint16_t* p = reinterpret_cast<uint16_t*>(pixelPtr(x0, y));
            std::fill(p, p + (x1 - x0), v);
        }
    }
}

void OffPort::blitFrom(const OffPort& src, const Rect& dstRectIn, const Rect& srcRectIn, const Rect* clipDst,
                       const Rect* clipSrc, int mode) {
    if (!valid() || !src.valid()) return;
    Rect d = dstRectIn, s = srcRectIn;
    // Recorte al origen y a los rectangulos de clip (FUN_0048c85e).
    const int sx0 = s.x0, sy0 = s.y0;
    s.intersect(src.bounds());
    if (clipSrc && !s.intersect(*clipSrc)) return;
    d.offset(s.x0 - sx0, s.y0 - sy0);
    const int dx0 = d.x0, dy0 = d.y0;
    d.intersect(bounds());
    if (clipDst && !d.intersect(*clipDst)) return;
    s.offset(d.x0 - dx0, d.y0 - dy0);
    const int w = std::min(s.width(), d.width()), h = std::min(s.height(), d.height());
    if (w <= 0 || h <= 0) return;
    // FUN_0048c662: solo el modo 0 existe en todas las tablas "tipo 1".
    if (mode != 0) return;
    if (bpp_ == 8 && src.bpp_ == 8) {
        for (int y = 0; y < h; ++y) std::memcpy(pixelPtr(d.x0, d.y0 + y), src.pixelPtr(s.x0, s.y0 + y), size_t(w));
    } else if (bpp_ == 16 && src.bpp_ == 16) {
        for (int y = 0; y < h; ++y) std::memcpy(pixelPtr(d.x0, d.y0 + y), src.pixelPtr(s.x0, s.y0 + y), size_t(w) * 2);
    } else if (bpp_ == 16 && src.bpp_ == 8) {
        // 8 -> 16: tabla de paleta del origen convertida al formato del destino (FUN_0049b268).
        static const ColorTable grey = ColorTable::identity(256);
        const uint16_t* pal = (src.palette_ ? *src.palette_ : grey).table16(format_);
        for (int y = 0; y < h; ++y) {
            const uint8_t* sp = src.pixelPtr(s.x0, s.y0 + y);
            uint16_t* dp = reinterpret_cast<uint16_t*>(pixelPtr(d.x0, d.y0 + y));
            for (int x = 0; x < w; ++x) dp[x] = pal[sp[x]];
        }
    }
    // 16 -> 8 no existe en el original.
}

std::vector<uint16_t> OffPort::toRgb555() const {
    std::vector<uint16_t> out(size_t(width_) * size_t(height_));
    if (bpp_ == 16) {
        for (int y = 0; y < height_; ++y) {
            const uint16_t* row = reinterpret_cast<const uint16_t*>(pixelPtr(0, y));
            uint16_t* o = out.data() + size_t(y) * size_t(width_);
            if (format_ == PixelFormat::Rgb565) {
                for (int x = 0; x < width_; ++x) {
                    const uint16_t v = row[x];
                    o[x] = uint16_t(((v >> 1) & 0x7fe0) | (v & 0x1f));
                }
            } else {
                std::memcpy(o, row, size_t(width_) * 2);
            }
        }
    } else {
        static const ColorTable grey = ColorTable::identity(256);
        const uint16_t* pal = (palette_ ? *palette_ : grey).table16(PixelFormat::Rgb555);
        for (int y = 0; y < height_; ++y) {
            const uint8_t* row = pixelPtr(0, y);
            uint16_t* o = out.data() + size_t(y) * size_t(width_);
            for (int x = 0; x < width_; ++x) o[x] = pal[row[x]];
        }
    }
    return out;
}

}  // namespace dl2::engine
