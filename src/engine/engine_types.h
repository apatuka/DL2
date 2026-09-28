// engine_types.h - tipos básicos compartidos por el port de CYLib: rectángulos (x0,y0,x1,y1 exclusivo),
// puntos, códigos de 4 caracteres (tags) y valores de color "ColorRef" con la codificación original.
#pragma once
#include <algorithm>
#include <cstdint>
#include <string>
#include <string_view>

namespace dl2::engine {

// Rectángulo CYLib: {left, top, right, bottom}, right/bottom exclusivos (igual que el original).
struct Rect {
    int x0 = 0, y0 = 0, x1 = 0, y1 = 0;
    int width() const { return x1 - x0; }
    int height() const { return y1 - y0; }
    bool empty() const { return x0 >= x1 || y0 >= y1; }                       // FUN_00495c6c
    bool contains(int x, int y) const { return x >= x0 && x < x1 && y >= y0 && y < y1; }  // FUN_00495d89
    bool containsInclusive(int x, int y) const { return x >= x0 && x <= x1 && y >= y0 && y <= y1; }  // FUN_00495db5
    void offset(int dx, int dy) { x0 += dx; x1 += dx; y0 += dy; y1 += dy; }  // FUN_00495c51
    // Interseca con `o`; devuelve true si queda algo (FUN_00495cc4).
    bool intersect(const Rect& o) {
        y0 = std::max(y0, o.y0); y1 = std::min(y1, o.y1);
        x0 = std::max(x0, o.x0); x1 = std::min(x1, o.x1);
        return !empty();
    }
    // Une `o` en este rectángulo; si `this` está vacío toma `o` (FUN_00495bf0 con los papeles: dst=this).
    void unite(const Rect& o) {
        if (empty()) { *this = o; return; }
        if (o.empty()) return;
        x0 = std::min(x0, o.x0); y0 = std::min(y0, o.y0);
        x1 = std::max(x1, o.x1); y1 = std::max(y1, o.y1);
    }
    void normalize() {  // FUN_00495c95
        if (x1 < x0) std::swap(x0, x1);
        if (y1 < y0) std::swap(y0, y1);
    }
    static Rect xywh(int x, int y, int w, int h) { return Rect{x, y, x + w, y + h}; }
};

struct Point {
    int x = 0, y = 0;
};

// Código de recurso de 4 caracteres tal y como lo usa el EXE: u32 little-endian ('TILE' = 0x454c4954).
using Tag = uint32_t;
constexpr Tag makeTag(char a, char b, char c, char d) {
    return uint32_t(uint8_t(a)) | (uint32_t(uint8_t(b)) << 8) | (uint32_t(uint8_t(c)) << 16) | (uint32_t(uint8_t(d)) << 24);
}
inline Tag makeTag(std::string_view s) {
    char c[4] = {' ', ' ', ' ', ' '};
    for (size_t i = 0; i < 4 && i < s.size(); ++i) c[i] = s[i];
    return makeTag(c[0], c[1], c[2], c[3]);
}
inline std::string tagToString(Tag t) {
    std::string s(4, ' ');
    for (int i = 0; i < 4; ++i) s[size_t(i)] = char((t >> (8 * i)) & 0xff);
    return s;
}

constexpr Tag kTagTILE = makeTag('T', 'I', 'L', 'E');
constexpr Tag kTagTILG = makeTag('T', 'I', 'L', 'G');
constexpr Tag kTagIMAG = makeTag('I', 'M', 'A', 'G');
constexpr Tag kTagPICT = makeTag('P', 'I', 'C', 'T');
constexpr Tag kTagPALT = makeTag('P', 'A', 'L', 'T');
constexpr Tag kTagFONT = makeTag('F', 'O', 'N', 'T');
constexpr Tag kTagSTRT = makeTag('S', 'T', 'R', 'T');
constexpr Tag kTagSMNU = makeTag('S', 'M', 'N', 'U');
constexpr Tag kTagWAVE = makeTag('W', 'A', 'V', 'E');
constexpr Tag kTagCY3D = makeTag('C', 'Y', '3', 'D');

// Valor de color CYLib ("ColorRef"):
//   bit31 (0x80000000) = los 24 bits bajos son RGB (se convierte al formato del port al usarse)
//   bit30 (0x40000000) = "sin definir" (SMenu usa el color del menú en su lugar)
//   sin bits altos     = valor nativo del port: índice de paleta (8 bpp) o color 555/565 (16 bpp)
using ColorRef = uint32_t;
constexpr ColorRef kColorNone = 0x40000000u;
constexpr ColorRef colorRgb(uint8_t r, uint8_t g, uint8_t b) {
    return 0x80000000u | (uint32_t(r) << 16) | (uint32_t(g) << 8) | b;
}
constexpr bool colorIsRgb(ColorRef c) { return (c & 0x80000000u) != 0; }
constexpr bool colorIsUnset(ColorRef c) { return (c & 0x40000000u) != 0; }

}  // namespace dl2::engine
