// pixel.h - estado global de dibujo de CYLib (pixel.c): port actual, pila de rectangulos de recorte, modo de
// blit (profundidad destino/origen), rellenos con recorte y tablas de sombreado/mezcla para 16 bpp.
#pragma once
#include <cstdint>
#include <memory>
#include <vector>

#include "engine/engine_types.h"
#include "engine/offport.h"

namespace dl2::engine {

// Modo de blit (DAT_0051e35c): (bpp destino << 16) | bpp origen. FUN_0049a72d lo reduce a un indice de tabla.
enum BlitMode : uint32_t {
    kBlit8to8 = 0x00080008,     // indice 0
    kBlit8to16 = 0x00100008,    // indice 1: origen indexado con su propia paleta -> destino 16 bpp
    kBlit16to16 = 0x00100010,   // indice 2
};

class Pixel {
public:
    // Port de destino actual (DAT_0051bddc, FUN_0048c434). Devuelve el anterior.
    static OffPort* setPort(OffPort* port);
    static OffPort* port();
    // Pila de ports (FUN_0048d2e7 / FUN_0048d32c, maximo 20).
    static void pushPort(OffPort* port);
    static void popPort();

    // Rectangulo de recorte (DAT_0065e570.., FUN_0049a9e7). Devuelve false si queda vacio.
    static bool setClip(const Rect& r);
    static const Rect& clip();
    // FUN_0049aa64: recorta r contra el clip actual y lo instala.
    static bool clipTo(const Rect& r);
    // FUN_0049a8ed / FUN_0049a93f: guarda / restaura el clip (pila de 20).
    static void pushClip();
    static void popClip();
    // Clip = todo el port actual.
    static void resetClip();

    // FUN_0049a760: fija el modo de blit y devuelve el anterior (0 = deducirlo del port actual y 8 bpp de origen).
    static uint32_t setBlitMode(uint32_t mode);
    static uint32_t blitMode();
    static int blitModeIndex();                 // FUN_0049a72d
    static uint32_t blitModeFor(int srcBpp);    // (port->bpp << 16) | srcBpp, como hacen los llamadores

    // FUN_004935fc: rellena [x0,x1)x[y0,y1) del port actual con recorte. c es un ColorRef.
    static void fillRect(int x0, int y0, int x1, int y1, ColorRef c);
    static void fillRect(const Rect& r, ColorRef c) { fillRect(r.x0, r.y0, r.x1, r.y1, c); }
    // FUN_0049372b: marco de 1 pixel dentro de [x0,x1)x[y0,y1).
    static void frameRect(int x0, int y0, int x1, int y1, ColorRef c);
    // FUN_00493b24: linea (Bresenham) de 1 pixel.
    static void line(int x0, int y0, int x1, int y1, ColorRef c);
    // FUN_00499b9f: ColorRef -> color nativo del port actual.
    static uint32_t nativeColor(ColorRef c);

    // Tablas de sombreado 16 bpp (FUN_0049a317 / FUN_00499d88 ...). Se construyen bajo demanda para el formato.
    struct ShadeTables {
        PixelFormat format = PixelFormat::Rgb555;
        std::vector<uint16_t> toHsl;       // 0x67ee30: color 16 bpp -> (h5<<11 | s5<<6 | l6)
        std::vector<uint16_t> fromHsl;     // 0x65ee30: (h,s,l) -> color 16 bpp
        uint16_t shade8[8][64];            // 0x69ee30: 8 niveles (50%..92%) sobre la luminancia
        uint16_t shade4[4][64];            // 0x69ee70: 4 niveles (50%..86%)
        uint16_t bright8[8][64];           // 0x69ee50: +10%..+52% (saturado a 63)
        uint16_t bright4[4][64];           // 0x69ee80
        int16_t blend[9][512];             // 0x51d6e0: 9 niveles (10%..90%) de diferencia con signo
        uint8_t blend8[9][512];            // 0x51d6dc (version de 8 bits)
    };
    static const ShadeTables& shadeTables(PixelFormat fmt);
    // Aplica el nivel de sombra (0..7) a un pixel de 16 bpp (T2_H1_M1 / T3_H1_M1).
    static uint16_t shadePixel(uint16_t px, int level, PixelFormat fmt);
    static uint16_t shadePixel4(uint16_t px, int level, PixelFormat fmt);  // tabla de 4 niveles (modo 7)
    // Mezcla origen sobre destino con el nivel actual (T3_H1_M5, FUN_0048f5b3/FUN_0048f670).
    static uint16_t blendPixel(uint16_t dst, uint16_t src, PixelFormat fmt);
    static void setBlendLevel(int level);   // 0..8 (10%..90% del origen)
    static int blendLevel();
};

}  // namespace dl2::engine
