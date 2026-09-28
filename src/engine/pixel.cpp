// pixel.cpp - estado de dibujo de CYLib (pixel.c): port actual, recorte, modo de blit, rellenos y tablas HSL.
#include "engine/pixel.h"

#include <cmath>
#include <cstdlib>
#include <memory>

namespace dl2::engine {

namespace {

struct PixelState {
    OffPort* port = nullptr;
    Rect clip;
    std::vector<Rect> clipStack;
    std::vector<OffPort*> portStack;
    uint32_t blitMode = kBlit8to8;
    int blendLevel = 4;
    std::unique_ptr<Pixel::ShadeTables> tables555, tables565;
};

PixelState& st() {
    static PixelState s;
    return s;
}

// FUN_00499fd7: RGB (0..1) -> H (grados), S, L.
void rgbToHsl(double r, double g, double b, double& h, double& s, double& l) {
    const double mx = std::max(r, std::max(g, b));
    const double mn = std::min(r, std::min(g, b));
    l = (mx + mn) * 0.5;
    if (mx == mn) {
        s = 0.0;
        h = 0.0;
        return;
    }
    const double d = mx - mn;
    s = l > 0.5 ? d / (2.0 - (mx + mn)) : d / (mx + mn);
    if (r == mx) h = (g - b) / d;
    else if (g == mx) h = (b - r) / d + 2.0;
    else h = (r - g) / d + 4.0;
    h = double(float(h) * 60.0f);
    if (h < 0.0) h = double(float(h) + 360.0f);
}

// FUN_0049a13b: H (grados), S, L -> RGB (0..1).
void hslToRgb(double h, double s, double l, double& r, double& g, double& b) {
    const double v = l > 0.5 ? (l + s) - l * s : double((float(s) + 1.0f) * float(l));
    if (v == 0.0) {
        r = g = b = l;
        return;
    }
    const double m = double(float(l) * 2.0f - float(v));
    const double hh = h / 60.0;
    const int sextant = int(std::lround(hh));  // el original redondea (FUN_004ae068 = round)
    const double fract = hh - sextant;
    const double sv = v * ((v - m) / v) * fract;
    const double mid1 = m + sv, mid2 = v - sv;
    switch (sextant) {
        case 0: r = v; g = mid1; b = m; break;
        case 1: r = mid2; g = v; b = m; break;
        case 2: r = m; g = v; b = mid1; break;
        case 3: r = m; g = mid2; b = v; break;
        case 4: r = mid1; g = m; b = v; break;
        case 5: r = v; g = m; b = mid2; break;
        default: r = v; g = m; b = mid2; break;
    }
}

int clamp255(double v) {
    const long x = std::lround(v);
    return x < 0 ? 0 : (x > 255 ? 255 : int(x));
}

std::unique_ptr<Pixel::ShadeTables> buildTables(PixelFormat fmt) {
    auto t = std::make_unique<Pixel::ShadeTables>();
    t->format = fmt;
    const bool is565 = fmt == PixelFormat::Rgb565;
    const int gBits = is565 ? 64 : 32;
    // Tabla directa: color 16 bpp -> HSL empaquetado (FUN_0049a317).
    t->toHsl.assign(65536, 0);
    for (int r = 0; r < 32; ++r)
        for (int g = 0; g < gBits; ++g)
            for (int b = 0; b < 32; ++b) {
                double h, s, l;
                rgbToHsl((r << 3) / 256.0, (is565 ? (g << 2) : (g << 3)) / 256.0, (b << 3) / 256.0, h, s, l);
                const int h8 = clamp255(h * 255.0 / 360.0), s8 = clamp255(s * 255.0), l8 = clamp255(l * 255.0);
                const uint16_t packed = uint16_t(((h8 >> 3) << 11) | ((s8 >> 3) << 6) | (l8 >> 2));
                const uint16_t px = is565 ? uint16_t((r << 11) | (g << 5) | b) : uint16_t((r << 10) | (g << 5) | b);
                t->toHsl[px] = packed;
            }
    // Tabla inversa: (h5, s5, l6) -> color 16 bpp.
    t->fromHsl.assign(65536, 0);
    for (int h = 0; h < 32; ++h)
        for (int s = 0; s < 32; ++s)
            for (int l = 0; l < 64; ++l) {
                double r, g, b;
                hslToRgb((h << 3) * 360.0 / 256.0, (s << 3) / 256.0, (l << 2) / 256.0, r, g, b);
                const int r8 = clamp255(r * 255.0), g8 = clamp255(g * 255.0), b8 = clamp255(b * 255.0);
                const uint16_t px = is565 ? rgbTo565(uint8_t(r8), uint8_t(g8), uint8_t(b8)) : rgbTo555(uint8_t(r8), uint8_t(g8), uint8_t(b8));
                t->fromHsl[size_t((h << 11) | (s << 6) | l)] = px;
            }
    // FUN_00499d88(0x32, 6): 8 tablas de luminancia al 50%,56%,...,92%.
    for (int k = 0; k < 8; ++k) {
        const int pct = 0x32 + 6 * k;
        for (int i = 0; i < 64; ++i) t->shade8[k][i] = uint16_t((i * pct) / 100);
    }
    // FUN_00499dfc(0x32, 0xc): 4 tablas 50%,62%,74%,86%.
    for (int k = 0; k < 4; ++k) {
        const int pct = 0x32 + 12 * k;
        for (int i = 0; i < 64; ++i) t->shade4[k][i] = uint16_t((i * pct) / 100);
    }
    // FUN_00499e70(10, 6) / FUN_00499f04(0x1e, 0xc): tablas aditivas.
    for (int k = 0; k < 8; ++k) {
        const int add = ((10 + 6 * k) << 5) / 100;
        for (int i = 0; i < 64; ++i) t->bright8[k][i] = uint16_t(add + i < 0x3f ? add + i : 0x3f);
    }
    for (int k = 0; k < 4; ++k) {
        const int add = ((0x1e + 12 * k) << 5) / 100;
        for (int i = 0; i < 64; ++i) t->bright4[k][i] = uint16_t(add + i < 0x3f ? add + i : 0x3f);
    }
    // FUN_00499c5d: 9 tablas de mezcla (10%..90%): [i] = i*f/100, [0x1ff-i] = -i*f/100 (diferencias con signo).
    for (int k = 0; k < 9; ++k) {
        const int f = 10 + 10 * k;
        for (int i = 0; i < 256; ++i) {
            t->blend[k][i] = int16_t((i * f) / 100);
            t->blend[k][0x1ff - i] = int16_t((-i * f) / 100);
            t->blend8[k][i] = uint8_t((i * f) / 100);
            t->blend8[k][0x1ff - i] = uint8_t((-i * f) / 100);
        }
    }
    return t;
}

}  // namespace

OffPort* Pixel::setPort(OffPort* port) {
    OffPort* prev = st().port;
    st().port = port;
    return prev;
}
OffPort* Pixel::port() { return st().port; }

void Pixel::pushPort(OffPort* port) {
    st().portStack.push_back(st().port);
    st().port = port;
}
void Pixel::popPort() {
    if (st().portStack.empty()) return;
    st().port = st().portStack.back();
    st().portStack.pop_back();
}

bool Pixel::setClip(const Rect& r) {
    st().clip = r;
    return !r.empty();
}
const Rect& Pixel::clip() { return st().clip; }

bool Pixel::clipTo(const Rect& r) {
    Rect c = r;
    c.intersect(st().clip);
    st().clip = c;
    return !c.empty();
}
void Pixel::pushClip() { st().clipStack.push_back(st().clip); }
void Pixel::popClip() {
    if (st().clipStack.empty()) return;
    st().clip = st().clipStack.back();
    st().clipStack.pop_back();
}
void Pixel::resetClip() { st().clip = st().port ? st().port->bounds() : Rect{}; }

uint32_t Pixel::setBlitMode(uint32_t mode) {
    const uint32_t prev = st().blitMode;
    if (mode == 0) mode = blitModeFor(8);
    if ((mode & 0xffff0000u) == 0) mode |= mode << 16;
    st().blitMode = mode;
    return prev;
}
uint32_t Pixel::blitMode() { return st().blitMode; }
int Pixel::blitModeIndex() {
    switch (st().blitMode) {
        case kBlit8to16: return 1;
        case kBlit16to16: return 2;
        default: return 0;
    }
}
uint32_t Pixel::blitModeFor(int srcBpp) {
    const int dst = st().port ? st().port->bpp() : 8;
    return (uint32_t(dst) << 16) | uint32_t(srcBpp);
}

uint32_t Pixel::nativeColor(ColorRef c) {
    return st().port ? st().port->nativeColor(c) : c;
}

void Pixel::fillRect(int x0, int y0, int x1, int y1, ColorRef c) {
    OffPort* p = st().port;
    if (!p) return;
    const Rect& cl = st().clip;
    if (x0 >= cl.x1) return;
    if (x0 < cl.x0) x0 = cl.x0;
    if (x1 < cl.x0) return;
    if (x1 > cl.x1) x1 = cl.x1;
    if (x0 >= x1 || y0 >= cl.y1) return;
    if (y0 < cl.y0) y0 = cl.y0;
    if (y1 == cl.y0) return;
    if (y1 > cl.y1) y1 = cl.y1;
    if (y0 >= y1) return;
    p->fillRaw(x0, y0, x1, y1, p->nativeColor(c));
}

void Pixel::frameRect(int x0, int y0, int x1, int y1, ColorRef c) {
    fillRect(x0, y0, x1, y0 + 1, c);
    fillRect(x1 - 1, y0, x1, y1, c);
    fillRect(x0, y1 - 1, x1, y1, c);
    fillRect(x0, y0, x0 + 1, y1, c);
}

void Pixel::line(int x0, int y0, int x1, int y1, ColorRef c) {
    const int dx = std::abs(x1 - x0), dy = std::abs(y1 - y0);
    const int sx = x0 < x1 ? 1 : -1, sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;
    for (;;) {
        fillRect(x0, y0, x0 + 1, y0 + 1, c);
        if (x0 == x1 && y0 == y1) break;
        const int e2 = err * 2;
        if (e2 > -dy) { err -= dy; x0 += sx; }
        if (e2 < dx) { err += dx; y0 += sy; }
    }
}

const Pixel::ShadeTables& Pixel::shadeTables(PixelFormat fmt) {
    std::unique_ptr<ShadeTables>& slot = fmt == PixelFormat::Rgb565 ? st().tables565 : st().tables555;
    if (!slot) slot = buildTables(fmt);
    return *slot;
}

uint16_t Pixel::shadePixel(uint16_t px, int level, PixelFormat fmt) {
    const ShadeTables& t = shadeTables(fmt);
    const uint16_t hsl = t.toHsl[px];
    return t.fromHsl[size_t((hsl & 0xffc0) | t.shade8[level & 7][hsl & 0x3f])];
}

uint16_t Pixel::shadePixel4(uint16_t px, int level, PixelFormat fmt) {
    const ShadeTables& t = shadeTables(fmt);
    const uint16_t hsl = t.toHsl[px];
    return t.fromHsl[size_t((hsl & 0xffc0) | t.shade4[level & 3][hsl & 0x3f])];
}

void Pixel::setBlendLevel(int level) { st().blendLevel = level < 0 ? 0 : (level > 8 ? 8 : level); }
int Pixel::blendLevel() { return st().blendLevel; }

uint16_t Pixel::blendPixel(uint16_t dst, uint16_t src, PixelFormat fmt) {
    // FUN_0048f5b3 (555) / FUN_0048f670 (565): por componente, dst' = src + tabla[(dst - src) & 0x1ff].
    const ShadeTables& t = shadeTables(fmt);
    const int16_t* tb = t.blend[st().blendLevel];
    if (fmt == PixelFormat::Rgb565) {
        const int g = (tb[((int(dst & 0x7e0) - int(src & 0x7e0)) >> 5) & 0x1ff] * 0x20 + int(src & 0x7e0)) & 0x7e0;
        const int r = (tb[((int(dst & 0xf800) - int(src & 0xf800)) >> 11) & 0x1ff] * 0x800 + int(src & 0xf800)) & 0xf800;
        const int b = (tb[(int(dst & 0x1f) - int(src & 0x1f)) & 0x1ff] + int(src & 0x1f)) & 0x1f;
        return uint16_t(r | g | b);
    }
    const int g = (tb[((int(dst & 0x3e0) - int(src & 0x3e0)) >> 5) & 0x1ff] * 0x20 + int(src & 0x3e0)) & 0x3e0;
    const int r = (tb[((int(dst & 0x7c00) - int(src & 0x7c00)) >> 10) & 0x1ff] * 0x400 + int(src & 0x7c00)) & 0x7c00;
    const int b = (tb[(int(dst & 0x1f) - int(src & 0x1f)) & 0x1ff] + int(src & 0x1f)) & 0x1f;
    return uint16_t(r | g | b);
}

}  // namespace dl2::engine
