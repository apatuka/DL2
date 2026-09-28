// font.h - fuentes de mapa de bits de CYLib (font.c): vista sobre el payload FONT, estado global de texto
// (fuente, colores, sombra, posicion del lapiz) y dibujado/medida de texto con el formato de glifos original.
#pragma once
#include <cstdint>
#include <memory>
#include <span>
#include <string>
#include <vector>

#include "engine/engine_types.h"
#include "engine/palette_table.h"

namespace dl2::engine {

// Formato FONT: u8 nameLen; char name[nameLen]; u16 infoWords; u16 info[infoWords-1]; cabecera de 14 shorts
// (hdr): [1] primer char, [2] ultimo char, [3] alto de celda, [4] x extra, [7] filas del bitmap, [8] offset de la
// tabla de anchos ((hdr+0x10)+[8]*2), [9] ascenso, [10] descenso, [11] interlineado extra, [12] pitch del bitmap /2;
// bitmap 1 bpp en hdr+0x1a; tabla de bits (u16 columna inicial por glifo, nchars+2 entradas) justo antes de la
// tabla de anchos (u16: byte bajo = avance, byte alto = desplazamiento x con signo; 0xffff = glifo ausente).
class FontView {
public:
    FontView() = default;
    explicit FontView(std::span<const uint8_t> data);
    bool valid() const { return hdr_ != nullptr; }

    std::string name() const { return name_; }
    int firstChar() const { return first_; }
    int lastChar() const { return last_; }
    int glyphCount() const { return last_ - first_ + 1; }
    int cellHeight() const { return cellHeight_; }   // hdr[3]
    int height() const { return rows_; }             // filas del bitmap (hdr[7])
    int ascent() const { return ascent_; }           // hdr[9]
    int descent() const { return descent_; }         // hdr[10]
    int lineGap() const { return lineGap_; }         // hdr[11]
    int lineHeight() const { return ascent_ + descent_ + lineGap_; }
    int xAdd() const { return xAdd_; }               // hdr[4] (se suma al desplazamiento x de cada glifo)

    // Indice de glifo para un caracter (aplica el glifo por defecto si falta).
    int glyphIndex(int ch) const;
    int advance(int glyph) const;            // byte bajo de widths[]
    int xOffset(int glyph) const;            // byte alto con signo de widths[] (+ xAdd), 0 para el espacio
    int bitStart(int glyph) const;           // columna inicial en el bitmap
    int bitWidth(int glyph) const;           // bits[g+1] - bits[g]
    // Bit (col, row) del glifo (true = pixel encendido).
    bool bit(int glyph, int col, int row) const;

private:
    std::span<const uint8_t> data_;
    const uint8_t* hdr_ = nullptr;
    std::string name_;
    int first_ = 0, last_ = 0, cellHeight_ = 0, rows_ = 0, ascent_ = 0, descent_ = 0, lineGap_ = 0, xAdd_ = 0;
    const uint8_t* widths_ = nullptr;
    const uint8_t* bits_ = nullptr;
    const uint8_t* bitmap_ = nullptr;
    int rowPitch_ = 0;
};

using FontPtr = std::shared_ptr<const FontView>;

// Bloque de texto (estructura de 0x20 bytes de FUN_00492d67 / FUN_0049ddf8).
struct TextBlock {
    const char* text = nullptr;
    Rect rect;
    uint32_t flags = 0;   // kTextCenter | kTextFillBackground | kTextShadow | kTextVCenter | kTextSelection | kTextRight
    int selStart = 0, selEnd = 0;
};
enum TextFlags : uint32_t {
    kTextCenter = 1,
    kTextFillBackground = 2,
    kTextShadow = 4,        // sombra "grabada" (modo de blit 1 con color 0xf7)
    kTextVCenter = 8,
    kTextSelection = 0x10,
    kTextRight = 0x20,
};

// Estado global de texto de font.c (DAT_0065ebf8..DAT_0065ec70).
class Text {
public:
    // FUN_00491bf7: fuente actual (nullptr = ninguna).
    static void setFont(FontPtr font);
    static const FontView* font();
    // FUN_00491d38: paleta con la que se convierten los indices de color del texto en ports de 16 bpp.
    static void setPalette(ColorTablePtr pal);
    static const ColorTablePtr& palette();

    // FUN_00491e02 / FUN_00491efa / FUN_00491f47: colores (indice de paleta o 0x80000000|RGB -> indice mas cercano).
    static void setColor(ColorRef c);            // color de los glifos
    static void setBackground(ColorRef c);       // 0xff = transparente
    static void setShadowColor(ColorRef c);
    static void setShadow(bool on, int dx = 1, int dy = 1);   // FUN_00491f94 + FUN_00491fad
    static void setSelectionColors(ColorRef text, ColorRef back);   // FUN_00492036 / FUN_00491fe9
    static void setMode(int mode);               // FUN_00491df3: modo de blit de los glifos (0 normal, 1 sombreado)
    static void setSpacing(int charExtra, int spaceExtra);   // DAT_0065ec28 / DAT_0065ec2c
    static void setTabSize(int px);              // DAT_0051dc18
    static uint8_t color();
    static uint8_t background();

    // FUN_00492aac: posicion del lapiz (x, linea base y).
    static void moveTo(int x, int y);
    static int penX();
    static int penY();

    // FUN_00491a2b / FUN_00491ace: guarda y restaura todo el estado (pila de 20). font puede ser nullptr.
    static void push(FontPtr font = nullptr);
    static void pop();

    // FUN_00492290: ancho de avance de un caracter con el espaciado actual.
    static int charWidth(int ch);
    // FUN_004921f8: ancho de una cadena (sin saltos de linea).
    static int textWidth(const char* s);
    // FUN_0049f978: ancho de la linea mas ancha (lineas separadas por CR); ignora los codigos 1 y 2.
    static int maxLineWidth(const char* s);
    // FUN_00492578: dibuja un caracter en la posicion del lapiz y avanza.
    static void drawChar(int ch);
    // FUN_00492aee: dibuja una cadena sin formato.
    static void drawString(const char* s);
    // FUN_00492d67: dibuja un bloque de texto con ajuste de linea; devuelve el puntero al texto no dibujado.
    static const char* drawBlock(const TextBlock& block);
    // FUN_00493108: bloque simple (texto, rect, flags).
    static void drawText(const char* s, const Rect& r, uint32_t flags);
    // FUN_00492b47: mide/ajusta una linea. Devuelve el numero de caracteres de la linea en *count y su ancho en
    // *width. breakIndex (o -1) pide la x del caracter con ese indice (valor devuelto, -1 si no esta en la linea).
    static int measureLine(const char* s, int maxWidth, int breakIndex, int* count, int* width, bool firstLine, int* indent);
    // FUN_00492b0c: avanza al comienzo de la siguiente linea (salta blancos y un CR/LF).
    static const char* nextLine(const char* s);
    // FUN_00493149: numero de lineas al ajustar a maxWidth (y ancho maximo en *maxLineW).
    static int lineCount(const char* s, int maxWidth, int* maxLineW = nullptr, bool firstLine = false);
    // FUN_0049331e: caracter bajo (x,y) en un bloque; devuelve false si esta fuera del rect.
    static bool hitTest(const TextBlock& block, int x, int y, int* charIndex);
    // FUN_004931b0: posicion (x,y) del caracter `index` dentro de un bloque ajustado a maxWidth.
    static void caretPos(const char* s, int maxWidth, int maxHeight, int index, int* x, int* y, bool firstLine, uint32_t flags);
};

}  // namespace dl2::engine
