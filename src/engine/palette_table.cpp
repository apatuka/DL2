// palette_table.cpp - decodificación y conversión de las tablas de color de CYLib.
#include "engine/palette_table.h"

#include <climits>

#include "formats/binary.h"

namespace dl2::engine {

bool ColorTable::parse(std::span<const uint8_t> data) {
    if (data.size() < 8) return false;
    const size_t count = bin::u16le(data.data() + 2);
    if (data.size() < 8 + count * 4) return false;
    entries_.resize(count);
    for (size_t i = 0; i < count; ++i) {
        const uint8_t* q = data.data() + 8 + i * 4;
        entries_[i] = ColorEntry{q[0], q[1], q[2], q[3]};
    }
    dirty_ = true;
    return true;
}

ColorTable ColorTable::identity(size_t count) {
    ColorTable t(count);
    for (size_t i = 0; i < count; ++i) t.entries_[i] = ColorEntry{uint8_t(i), uint8_t(i), uint8_t(i), 0};
    return t;
}

ColorTable ColorTable::fromPalette(const Palette& pal) {
    ColorTable t(256);
    for (size_t i = 0; i < 256; ++i) t.entries_[i] = ColorEntry{pal.colors[i].r, pal.colors[i].g, pal.colors[i].b, 0};
    return t;
}

uint16_t ColorTable::to16(size_t i, PixelFormat fmt) const {
    if (i >= entries_.size()) return 0;
    const ColorEntry& e = entries_[i];
    return rgbToNative16(e.r, e.g, e.b, fmt);
}

const uint16_t* ColorTable::table16(PixelFormat fmt) const {
    std::vector<uint16_t>& cache = fmt == PixelFormat::Rgb565 ? cache565_ : cache555_;
    if (dirty_ || cache.size() != 256) {
        cache555_.assign(256, 0);
        cache565_.assign(256, 0);
        for (size_t i = 0; i < entries_.size() && i < 256; ++i) {
            cache555_[i] = to16(i, PixelFormat::Rgb555);
            cache565_[i] = to16(i, PixelFormat::Rgb565);
        }
        dirty_ = false;
    }
    return cache.data();
}

uint8_t ColorTable::nearest(uint8_t r, uint8_t g, uint8_t b) const {
    int best = 0;
    long bestDist = LONG_MAX;
    for (size_t i = 0; i < entries_.size(); ++i) {
        const ColorEntry& e = entries_[i];
        if (e.flags & 1) continue;
        const long dr = long(r) - e.r, dg = long(g) - e.g, db = long(b) - e.b;
        long d = dr * dr * 3 + dg * dg * 4 + db * db * 2;
        if (d < 0) d = -d;
        if (d < bestDist) {
            bestDist = d;
            best = int(i);
            if (d == 0) break;
        }
    }
    return uint8_t(best);
}

Palette ColorTable::toPalette() const {
    Palette p;
    for (size_t i = 0; i < 256 && i < entries_.size(); ++i) p.colors[i] = Rgb{entries_[i].r, entries_[i].g, entries_[i].b};
    return p;
}

}  // namespace dl2::engine
