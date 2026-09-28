// offport.h - OffPort: superficie de dibujo de CYLib (offport.c). Buffer de 8 bpp indexado o 16 bpp (RGB555/565)
// con paleta asociada, origen y rectángulo de vista. Sustituye a las superficies DirectDraw / DIB del original.
#pragma once
#include <cstdint>
#include <memory>
#include <vector>

#include "engine/engine_types.h"
#include "engine/palette_table.h"

namespace dl2::engine {

class OffPort {
public:
    OffPort() = default;
    // FUN_0048c28d / FUN_0048bf93: crea una superficie w x h de bpp bits (8 o 16). El formato de 16 bits
    // es el de la pantalla (RGB555 por defecto, como en el juego original).
    bool create(int w, int h, int bpp, PixelFormat fmt16 = PixelFormat::Rgb555);
    bool valid() const { return !pixels_.empty(); }

    int width() const { return width_; }
    int height() const { return height_; }
    int bpp() const { return bpp_; }
    int bytesPerPixel() const { return (bpp_ + 7) >> 3; }
    int pitch() const { return pitch_; }
    PixelFormat format() const { return format_; }
    void setFormat(PixelFormat f) { format_ = f; }   // FUN_0048c62f (conversion 555<->565 de un port)
    Rect bounds() const { return Rect{0, 0, width_, height_}; }

    // Puntero al pixel (x,y) (FUN_0048d03e).
    uint8_t* pixelPtr(int x, int y) { return pixels_.data() + size_t(y) * size_t(pitch_) + size_t(x) * size_t(bytesPerPixel()); }
    const uint8_t* pixelPtr(int x, int y) const { return pixels_.data() + size_t(y) * size_t(pitch_) + size_t(x) * size_t(bytesPerPixel()); }
    uint8_t* data() { return pixels_.data(); }
    const uint8_t* data() const { return pixels_.data(); }

    // Origen del port (+0x14/+0x18): desplazamiento que se suma a las coordenadas al blitear (FUN_0048c85e).
    int originX() const { return originX_; }
    int originY() const { return originY_; }
    void setOrigin(int x, int y) { originX_ = x; originY_ = y; }
    // Rectangulo de vista (+0x2c..+0x38, FUN_0048bb80 / FUN_0048bbbb).
    const Rect& viewRect() const { return view_; }
    void setViewRect(const Rect& r) { view_ = r; }

    // Paleta asociada (+0x3c, FUN_0048d391). En 8 bpp define los colores de la superficie; en 16 bpp se usa como
    // paleta de "presentacion" para las conversiones de color de texto y rellenos.
    const ColorTablePtr& palette() const { return palette_; }
    void setPalette(ColorTablePtr p) { palette_ = std::move(p); }

    // Flags originales (+0x28): bit0 = objeto adjunto, bit1 = primaria, bit3 = propiedad de la libreria.
    uint16_t flags() const { return flags_; }
    void setFlags(uint16_t f) { flags_ = f; }

    void clear(uint32_t nativeColor = 0);
    // Convierte un ColorRef al valor nativo de este port (FUN_00499b9f).
    uint32_t nativeColor(ColorRef c) const;
    // Rellena [x0,x1)x[y0,y1) SIN recorte (el recorte lo hace pixel.cpp).
    void fillRaw(int x0, int y0, int x1, int y1, uint32_t nativeColor);

    // FUN_0048c85e / FUN_0048c662: copia srcRect de src en dstRect de this (mismo tamano; se recorta al menor),
    // aplicando el modo de blit 0..7 de la tabla "tipo 1" (8->8: copia; 8->16: paleta del origen; 16->16: copia).
    void blitFrom(const OffPort& src, const Rect& dstRect, const Rect& srcRect, const Rect* clipDst = nullptr,
                  const Rect* clipSrc = nullptr, int mode = 0);

    // Copia de un OffPort a un buffer RGB555 top-down (para presentar / exportar).
    std::vector<uint16_t> toRgb555() const;

private:
    int width_ = 0, height_ = 0, bpp_ = 0, pitch_ = 0;
    int originX_ = 0, originY_ = 0;
    PixelFormat format_ = PixelFormat::Indexed8;
    uint16_t flags_ = 0;
    Rect view_;
    std::vector<uint8_t> pixels_;
    ColorTablePtr palette_;
};

using OffPortPtr = std::shared_ptr<OffPort>;

}  // namespace dl2::engine
