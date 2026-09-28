// font.cpp - port de font.c: fuentes de mapa de bits, estado de texto, dibujado y medida.
#include "engine/font.h"

#include <cstring>
#include <vector>

#include "engine/offport.h"
#include "engine/pixel.h"
#include "formats/binary.h"

namespace dl2::engine {

// ---------------------------------------------------------------------------------------------------------------
// FontView

FontView::FontView(std::span<const uint8_t> data) : data_(data) {
    if (data.size() < 2) return;
    const size_t nameLen = data[0];
    if (1 + nameLen + 2 > data.size()) return;
    name_.assign(reinterpret_cast<const char*>(data.data() + 1), nameLen);
    const uint8_t* p = data.data() + 1 + nameLen;
    // FUN_00491b46: hdr = p + u16(p) * 2 (la palabra cuenta las palabras de informacion incluida ella misma).
    const size_t infoWords = bin::u16le(p);
    const uint8_t* hdr = p + infoWords * 2;
    if (hdr + 0x1c > data.data() + data.size()) return;
    first_ = int16_t(bin::u16le(hdr + 2));
    last_ = int16_t(bin::u16le(hdr + 4));
    cellHeight_ = int16_t(bin::u16le(hdr + 6));
    xAdd_ = int16_t(bin::u16le(hdr + 8));
    rows_ = bin::u16le(hdr + 0xe);
    ascent_ = int16_t(bin::u16le(hdr + 0x12));
    descent_ = int16_t(bin::u16le(hdr + 0x14));
    lineGap_ = int16_t(bin::u16le(hdr + 0x16));
    rowPitch_ = bin::u16le(hdr + 0x18) * 2;
    const size_t widthsOff = size_t(bin::u16le(hdr + 0x10)) * 2 + 0x10;
    const int nchars = last_ - first_ + 1;
    if (nchars <= 0 || last_ < first_) return;
    const size_t bitsOff = widthsOff - size_t(nchars + 2) * 2;
    if (hdr + widthsOff + size_t(nchars + 2) * 2 > data.data() + data.size() || widthsOff < size_t(nchars + 2) * 2 + 0x1a) return;
    hdr_ = hdr;
    widths_ = hdr + widthsOff;
    bits_ = hdr + bitsOff;
    bitmap_ = hdr + 0x1a;
}

int FontView::glyphIndex(int ch) const {
    if (!hdr_) return 0;
    int g = (ch & 0xff) - first_;
    if (g < 0 || g >= glyphCount()) g = glyphCount();
    else if (bin::u16le(widths_ + size_t(g) * 2) == 0xffff) g = glyphCount();
    return g;
}
int FontView::advance(int g) const { return hdr_ ? (bin::u16le(widths_ + size_t(g) * 2) & 0xff) : 0; }
int FontView::xOffset(int g) const {
    if (!hdr_) return 0;
    if (g == 0x20 - first_) return 0;   // FUN_00491bf7 borra el desplazamiento del espacio
    return int8_t(bin::u16le(widths_ + size_t(g) * 2) >> 8) + xAdd_;
}
int FontView::bitStart(int g) const { return hdr_ ? bin::u16le(bits_ + size_t(g) * 2) : 0; }
int FontView::bitWidth(int g) const {
    if (!hdr_) return 0;
    if (g == 0x20 - first_) return -1;   // el espacio no tiene bits (local_38 = -1)
    return int(bin::u16le(bits_ + size_t(g + 1) * 2)) - int(bin::u16le(bits_ + size_t(g) * 2));
}
bool FontView::bit(int g, int col, int row) const {
    if (!hdr_ || row < 0 || row >= rows_ || col < 0 || col >= bitWidth(g)) return false;
    const int bitPos = bitStart(g) + col;
    const uint8_t* rowp = bitmap_ + size_t(row) * size_t(rowPitch_) + size_t(bitPos >> 3);
    if (rowp >= data_.data() + data_.size()) return false;
    return (*rowp & (0x80 >> (bitPos & 7))) != 0;
}

// ---------------------------------------------------------------------------------------------------------------
// Estado global de texto

namespace {

struct TextState {
    FontPtr font;
    ColorTablePtr palette;
    uint8_t color = 0xff;          // DAT_0065ec10
    uint8_t background = 0xff;     // DAT_0065ec14
    uint8_t shadowColor = 0;       // DAT_0051dc14
    uint8_t selText = 0;           // DAT_0065ec18
    uint8_t selBack = 0;           // DAT_0065ec1c
    bool shadow = false;           // DAT_0065ec54
    int shadowDx = 1, shadowDy = 1;  // DAT_0065ec58 / DAT_0065ec5c
    int mode = 0;                  // DAT_0065ec50
    int charExtra = 0, spaceExtra = 0;  // DAT_0065ec28 / DAT_0065ec2c
    int tabSize = 32;              // DAT_0051dc18
    int penX = 0, penY = 0;        // DAT_0065ec40 / DAT_0065ec3c
};

TextState& ts() {
    static TextState s;
    return s;
}
std::vector<TextState>& stack() {
    static std::vector<TextState> s;
    return s;
}

uint8_t toIndex(ColorRef c) {
    if (colorIsRgb(c)) {
        const ColorTablePtr& pal = ts().palette;
        if (!pal) return 0;
        return pal->nearest(uint8_t(c >> 16), uint8_t(c >> 8), uint8_t(c));
    }
    return uint8_t(c);
}

inline bool isNewline(unsigned char c) { return c == '\r' || c == '\n'; }

}  // namespace

void Text::setFont(FontPtr font) { ts().font = std::move(font); }
const FontView* Text::font() { return ts().font.get(); }
void Text::setPalette(ColorTablePtr pal) { ts().palette = std::move(pal); }
const ColorTablePtr& Text::palette() { return ts().palette; }
void Text::setColor(ColorRef c) { ts().color = toIndex(c); }
void Text::setBackground(ColorRef c) { ts().background = toIndex(c); }
void Text::setShadowColor(ColorRef c) { ts().shadowColor = toIndex(c); }
void Text::setShadow(bool on, int dx, int dy) { ts().shadow = on; ts().shadowDx = dx; ts().shadowDy = dy; }
void Text::setSelectionColors(ColorRef text, ColorRef back) { ts().selText = toIndex(text); ts().selBack = toIndex(back); }
void Text::setMode(int mode) { ts().mode = mode; }
void Text::setSpacing(int charExtra, int spaceExtra) { ts().charExtra = charExtra; ts().spaceExtra = spaceExtra; }
void Text::setTabSize(int px) { ts().tabSize = px > 0 ? px : 1; }
uint8_t Text::color() { return ts().color; }
uint8_t Text::background() { return ts().background; }
void Text::moveTo(int x, int y) { ts().penX = x; ts().penY = y; }
int Text::penX() { return ts().penX; }
int Text::penY() { return ts().penY; }

void Text::push(FontPtr font) {
    stack().push_back(ts());
    if (font) setFont(std::move(font));
}
void Text::pop() {
    if (stack().empty()) return;
    // FUN_00491ace restaura fuente, colores, modo, sombra y desplazamientos (no el lapiz ni la paleta).
    TextState saved = stack().back();
    stack().pop_back();
    TextState& s = ts();
    s.font = saved.font;
    s.color = saved.color;
    s.background = saved.background;
    s.mode = saved.mode;
    s.shadowColor = saved.shadowColor;
    s.shadow = saved.shadow;
    s.shadowDx = saved.shadowDx;
    s.shadowDy = saved.shadowDy;
    s.selText = saved.selText;
    s.selBack = saved.selBack;
}

int Text::charWidth(int ch) {
    const FontView* f = font();
    if (!f) return 0;
    const int g = f->glyphIndex(ch);
    const bool space = (ch & 0xff) == 0x20;   // FUN_00492290 compara el caracter con 0x20
    return f->advance(g) + (space ? ts().spaceExtra : ts().charExtra);
}

int Text::textWidth(const char* s) {
    if (!font() || !s) return 0;
    int w = 0;
    for (; *s; ++s) w += charWidth(uint8_t(*s));
    return w;
}

int Text::maxLineWidth(const char* s) {
    if (!s) return 0;
    int cur = 0, best = 0;
    for (; *s; ++s) {
        const unsigned char c = uint8_t(*s);
        if (c == 1 || c == 2) continue;
        if (c == '\r') {
            if (cur > best) best = cur;
            cur = 0;
        } else {
            cur += charWidth(c);
        }
    }
    return cur > best ? cur : best;
}

void Text::drawChar(int ch) {
    TextState& s = ts();
    const FontView* f = s.font.get();
    OffPort* port = Pixel::port();
    if (!f || !port) return;
    const int g = f->glyphIndex(ch);
    const bool space = g == 0x20;   // FUN_00492578 compara el indice de glifo con 0x20
    const int adv = f->advance(g);
    const int xoff = space ? 0 : f->xOffset(g);
    const int penX = s.penX;
    int bufX = penX + xoff;
    if (penX < bufX) bufX = penX;
    const int top = s.penY - f->ascent();
    int cellRight = adv + penX;
    int bottom = s.penY + f->descent();
    s.penX += adv + (space ? s.spaceExtra : s.charExtra);
    int bufW = adv, bufH = f->height();
    if (s.shadow) {
        cellRight += s.shadowDx;
        bottom += s.shadowDy;
        bufW += s.shadowDx;
        bufH += s.shadowDy;
    }
    const Rect& clip = Pixel::clip();
    if (!(top < clip.y1 && clip.y0 < top + f->height() && bufX < clip.x1 && clip.x0 < cellRight)) return;
    const int glyphBits = space ? -1 : f->bitWidth(g);
    const bool transparent = s.background == 0xff;
    const bool dst16 = port->bpp() == 16;
    static const ColorTable grey = ColorTable::identity(256);
    const uint16_t* pal16 = dst16 ? (s.palette ? *s.palette : grey).table16(port->format()) : nullptr;

    auto putPixel = [&](int x, int y, uint8_t idx) {
        if (!clip.contains(x, y)) return;
        if (dst16) {
            uint16_t* d = reinterpret_cast<uint16_t*>(port->pixelPtr(x, y));
            if (s.mode == 1 && idx >= 0xf7 && idx != 0xff) *d = Pixel::shadePixel(*d, (idx + 1) & 7, port->format());
            else *d = pal16[idx];
        } else {
            *port->pixelPtr(x, y) = idx;
        }
    };
    // Fondo opaco de la celda (advance x alto).
    if (!transparent) {
        for (int y = 0; y < bufH; ++y)
            for (int x = 0; x < bufW; ++x) putPixel(bufX + x, top + y, s.background);
    }
    // Sombra (FUN_00492578, primera pasada) y glifo (segunda pasada), ambos recortados al buffer [0,bufW).
    auto drawGlyph = [&](int gx, int gy, uint8_t idx) {
        if (glyphBits < 1) return;
        for (int row = 0; row < f->height(); ++row)
            for (int col = 0; col < adv && col < glyphBits; ++col) {
                const int bx = gx + col;
                if (bx < 0 || bx >= bufW) continue;
                if (f->bit(g, col, row)) putPixel(bufX + bx, top + gy + row, idx);
            }
    };
    if (s.shadow) drawGlyph(xoff + s.shadowDx, s.shadowDy, s.shadowColor);
    drawGlyph(xoff, 0, s.color);
}

void Text::drawString(const char* s) {
    if (!s) return;
    for (; *s; ++s) drawChar(uint8_t(*s));
}

const char* Text::nextLine(const char* p) {
    for (;;) {
        const unsigned char c = uint8_t(*p);
        if (c == 0) return p;
        if (c == '\n' || c == '\r') break;
        if (c > ' ') return p;
        ++p;
    }
    if ((p[0] == '\n' && p[1] == '\r') || (p[0] == '\r' && p[1] == '\n')) ++p;
    return p + 1;
}

int Text::measureLine(const char* text, int maxWidth, int breakIndex, int* count, int* lineWidth, bool firstLine, int* indent) {
    int breakCount = -1, breakWidth = 0;
    int index = 0, width = 0, prevWidth = 0;
    unsigned char prev = ' ';
    bool stop = false;
    int breakX = -1;
    int localIndent = indent ? *indent : 0;
    const unsigned char* p = reinterpret_cast<const unsigned char*>(text);
    if (firstLine && (p[0] == '{' || p[0] == 0xfa)) {
        int ind = charWidth('{');
        const unsigned char* q = p;
        while (*++q == ' ') ind += charWidth(' ');
        if (indent) *indent = ind;
        localIndent = 0;
    }
    while (*p && !stop) {
        const unsigned char c = *p;
        if (index == breakIndex) breakX = width;
        const int before = width;
        if (isNewline(c)) {
            if ((c == '\r' && p[1] == '\n') || (c == '\n' && p[1] == '\r')) ++p;
            stop = true;
            if (prev > ' ') { breakCount = index; breakWidth = before; }
            if (indent) *indent = 0;
        } else {
            if (c == ' ') {
                if (prev > ' ') { breakCount = index; breakWidth = before; }
                width += charWidth(' ');
            } else if (c == '\t') {
                width = (width / ts().tabSize) * ts().tabSize + ts().tabSize;
            } else if (c > ' ') {
                width += charWidth(c);
            }
            ++index;
        }
        if (maxWidth - localIndent < width) stop = true;
        ++p;
        prev = c;
        prevWidth = before;
    }
    if (*p == 0 && prev > ' ' && !stop) { breakCount = index; breakWidth = width; }
    if (breakCount == -1) { breakCount = index; breakWidth = prevWidth; }
    if (breakWidth < breakX) breakX = -1;
    if (count) *count = breakCount;
    if (lineWidth) *lineWidth = breakWidth + localIndent;
    return breakX == -1 ? -1 : breakX + localIndent;
}

int Text::lineCount(const char* s, int maxWidth, int* maxLineW, bool firstLine) {
    int lines = 0, widest = 0, indent = 0;
    if (s) {
        while (*s) {
            int n = 0, w = 0;
            measureLine(s, maxWidth, -1, &n, &w, firstLine, &indent);
            s = nextLine(s + n);
            ++lines;
            if (w > widest) widest = w;
        }
    }
    if (maxLineW) *maxLineW = widest;
    return lines;
}

const char* Text::drawBlock(const TextBlock& block) {
    const char* text = block.text;
    if (!text) return nullptr;
    TextState& s = ts();
    push();
    if (block.flags & kTextShadow) {
        setMode(1);
        setShadowColor(0xf7);
        setShadow(true, s.shadowDx, s.shadowDy);
    }
    const FontView* f = font();
    if (!f) { pop(); return text; }
    const int ascent = f->ascent(), lineH = f->lineHeight();
    const int x0 = block.rect.x0, top = block.rect.y0, bottom = block.rect.y1;
    int selLo = 0, selHi = 0;
    if (block.flags & kTextSelection) {
        selLo = std::min(block.selStart, block.selEnd);
        selHi = std::max(block.selStart, block.selEnd);
    }
    if (block.flags & kTextFillBackground) Pixel::fillRect(block.rect, s.background);
    setBackground(0xff);
    const int maxW = block.rect.width();
    int y;
    if (block.flags & kTextVCenter) {
        const int n = lineCount(text, maxW, nullptr, false);
        int off = ((bottom - top) - n * lineH) / 2;
        if (off + top < top) off = 0;
        y = top + off + ascent;
    } else {
        y = top + ascent;
    }
    int indent = 0;
    const uint32_t prevMode = Pixel::setBlitMode(Pixel::blitModeFor(8));
    int charPos = 0;
    const char* p = text;
    while (*p) {
        int n = 0, w = 0;
        measureLine(p, maxW, -1, &n, &w, false, &indent);
        if (block.flags & kTextCenter) moveTo(((maxW - indent) - w) / 2 + x0 + indent, y);
        else if (block.flags & kTextRight) moveTo((maxW + x0 + indent) - w, y);
        else moveTo(indent + x0, y);
        // Color de fondo de la seleccion convertido al port (FUN_00499b9f sobre la paleta del texto).
        ColorRef selBackRef = s.selBack;
        if (s.palette && s.selBack < s.palette->size()) {
            const ColorEntry& e = (*s.palette)[s.selBack];
            selBackRef = colorRgb(e.r, e.g, e.b);
        }
        for (int i = 0; *p && i < n; ++i, ++p, ++charPos) {
            const unsigned char c = uint8_t(*p);
            const bool selected = (block.flags & kTextSelection) && charPos >= selLo && charPos < selHi;
            if (!selected) {
                if (c == '\t') moveTo(((penX() - x0) / s.tabSize) * s.tabSize + s.tabSize + x0, penY());
                else drawChar(c);
            } else {
                int gx = 0, gw;
                if (c == '\t') gw = ((penX() - x0) / s.tabSize) * s.tabSize + s.tabSize - penX();
                else { gx = f->xOffset(f->glyphIndex(c)); gw = f->advance(f->glyphIndex(c)); }
                Pixel::fillRect(penX() + gx, penY() - (ascent + 1), penX() + gw, f->descent() + penY() + 1, selBackRef);
                const uint8_t savedColor = s.color, savedBg = s.background;
                setColor(s.selText);
                setBackground(s.selBack);
                if (c == '\t') moveTo(penX() + gw, penY());
                else drawChar(c);
                setColor(savedColor);
                setBackground(savedBg);
            }
        }
        const char* nl = nextLine(p);
        charPos += int(nl - p);
        p = nl;
        if (*p == 0) break;
        y += lineH;
        if (y >= bottom) break;
        indent = 0;
    }
    Pixel::setBlitMode(prevMode);
    pop();
    return p;
}

void Text::drawText(const char* text, const Rect& r, uint32_t flags) {
    TextBlock b;
    b.text = text;
    b.rect = r;
    b.flags = flags;
    drawBlock(b);
}

bool Text::hitTest(const TextBlock& block, int x, int y, int* charIndex) {
    const FontView* f = font();
    if (!f || !block.text) return false;
    if (x < block.rect.x0 || x >= block.rect.x1 || y < block.rect.y0 || y >= block.rect.y1) return false;
    const int maxW = block.rect.width();
    const int lineH = f->lineHeight();
    int yOff = 0;
    if (block.flags & kTextVCenter) {
        const int n = lineCount(block.text, maxW);
        yOff = ((block.rect.height()) - n * lineH) / 2;
        if (yOff < 0) yOff = 0;
    }
    int indent = 0, lineStart = 0;
    const char* p = block.text;
    while (*p) {
        int n = 0, w = 0;
        measureLine(p, maxW, -1, &n, &w, false, &indent);
        const int relY = y - block.rect.y0;
        if (yOff <= relY && relY < yOff + f->ascent() + f->descent()) {
            int lx = (block.flags & kTextCenter) ? ((maxW - indent) - w) / 2 + indent
                   : (block.flags & kTextRight) ? (maxW + indent) - w : indent;
            const int relX = x - block.rect.x0;
            for (int i = 0; i < n; ++i) {
                const int cw = p[i] == '\t' ? (lx / ts().tabSize) * ts().tabSize + ts().tabSize - lx : charWidth(uint8_t(p[i]));
                if (lx <= relX && relX < lx + cw) { *charIndex = lineStart + i; return true; }
                lx += cw;
            }
            *charIndex = lineStart + n;
            return true;
        }
        yOff += lineH;
        const char* nl = nextLine(p + n);
        lineStart = int(nl - block.text);
        p = nl;
    }
    *charIndex = lineStart;
    return true;
}

void Text::caretPos(const char* text, int maxWidth, int maxHeight, int index, int* outX, int* outY, bool firstLine, uint32_t flags) {
    const FontView* f = font();
    int x = 0, y = 0, indent = 0;
    if (!f || !text) { *outX = 0; *outY = 0; return; }
    const int lineH = f->lineHeight();
    const char* p = text;
    int remaining = index;
    int lineWidth = 0;
    for (;;) {
        int n = 0, w = 0;
        const int bx = measureLine(p, maxWidth, remaining, &n, &w, firstLine, &indent);
        lineWidth = w;
        if (bx != -1 || *p == 0) { x = bx == -1 ? w : bx; break; }
        p += n;
        remaining -= n;
        // Blancos al final de la linea: si el indice cae en ellos, la x es el final de la linea.
        int extra = 0;
        bool found = false;
        while (*p && uint8_t(*p) <= ' ') {
            if (*p == ' ') extra += charWidth(' ');
            if (isNewline(uint8_t(*p))) {
                if ((p[0] == '\r' && p[1] == '\n') || (p[0] == '\n' && p[1] == '\r')) { ++p; --remaining; }
                ++p; --remaining;
                break;
            }
            if (remaining == 0) { x = w + extra; found = true; break; }
            ++p; --remaining;
        }
        if (found) break;
        if (*p == 0) { x = w + extra; break; }
        y += lineH;
        firstLine = false;
    }
    if (flags & kTextCenter) x += ((maxWidth - indent) - lineWidth) / 2 + indent;
    else if (flags & kTextRight) x += (maxWidth + indent) - lineWidth;
    if (flags & kTextVCenter) {
        int n = lineCount(text, maxWidth);
        if (n < 1) n = 1;
        y += (maxHeight - n * lineH) / 2;
    }
    *outX = x;
    *outY = y;
}

}  // namespace dl2::engine
