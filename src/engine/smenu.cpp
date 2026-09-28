// smenu.cpp - port del sistema SMenu de CYLib: carga de SMNU, mensajes, dibujado, deteccion y eventos.
#include "engine/smenu.h"

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>

#include "engine/input_queue.h"
#include "engine/pixel.h"
#include "engine/tile.h"
#include "formats/binary.h"
#include "formats/iff_pbm.h"

namespace dl2::engine {

std::function<void(uint32_t)> SMenu::soundPlayer_;

namespace {

constexpr uint32_t kOpEnd = 0xffffffffu;
constexpr uint32_t kRecMenu = 1000;

int div2(int v) { return v / 2; }   // (v >> 1) con ajuste de signo del original == division entera hacia cero

// FUN_0049fa76: coloca `inner` (0,0,w,h) dentro de `outer` segun los bits de alineacion.
void placeRect(const Rect& outer, Rect& inner, uint32_t align) {
    const int w = inner.width(), h = inner.height();
    auto setX = [&](int x0) { inner.x0 = x0; inner.x1 = x0 + w; };
    auto setY = [&](int y0) { inner.y0 = y0; inner.y1 = y0 + h; };
    switch (align) {
        case 0: inner = outer; break;
        case kStateAlignTopLeft: setY(outer.y0); setX(outer.x0); break;
        case kStateAlignTop: setY(outer.y0); setX(div2(outer.width() - w) + outer.x0); break;
        case kStateAlignTopRight: setY(outer.y0); setX(outer.x1 - w); break;
        case kStateAlignRight: setY(div2(outer.height() - h) + outer.y0); setX(outer.x1 - w); break;
        case kStateAlignBottomRight: setY(outer.y1 - h); setX(outer.x1 - w); break;
        case kStateAlignBottom: setY(outer.y1 - h); setX(div2(outer.width() - w) + outer.x0); break;
        case kStateAlignBottomLeft: setY(outer.y1 - h); setX(outer.x0); break;
        case kStateAlignLeft: setY(div2(outer.height() - h) + outer.y0); setX(outer.x0); break;
        case kStateAlignCenter: setY(div2(outer.height() - h) + outer.y0); setX(div2(outer.width() - w) + outer.x0); break;
        default: break;
    }
}

// Linea base del texto de un boton (FUN_004a016e y familia).
int buttonBaseline(int y0, int y1, int ascent) {
    const int half = div2(y1 - y0), halfAsc = div2(ascent);
    return y0 + (ascent <= half + halfAsc ? half + halfAsc : ascent);
}

ColorRef pick(ColorRef itemColor, ColorRef menuColor) { return colorIsUnset(itemColor) ? menuColor : itemColor; }

}  // namespace

// ---------------------------------------------------------------------------------------------------------------
// SMenuItem

int SMenuItem::stateIndex() const {
    if (state & kStateDisabled) return 2;
    return (state & kStateHighlight) ? 1 : 0;
}

int SMenuItem::layerIndex() const {
    int plus = 0;
    if ((type == kItemCheckBox || type == kItemRadio) && isChecked()) plus = 3;
    return stateIndex() + plus;
}

// ---------------------------------------------------------------------------------------------------------------
// Globales

std::vector<SMenu*>& SMenu::all() {
    static std::vector<SMenu*> list;
    return list;
}
std::vector<Rect>& SMenu::dirtyRects() {
    static std::vector<Rect> list;
    return list;
}
void SMenu::setSoundPlayer(std::function<void(uint32_t)> fn) { soundPlayer_ = std::move(fn); }

void SMenu::addDirty(const Rect& rIn) {
    // FUN_004a60b1 (simplificado): une con los rectangulos que solapan; maximo 20.
    Rect r = rIn;
    if (r.empty()) return;
    std::vector<Rect>& list = dirtyRects();
    for (size_t i = 0; i < list.size();) {
        Rect t = list[i];
        if (t.intersect(r)) {
            r.unite(list[i]);
            list.erase(list.begin() + std::ptrdiff_t(i));
        } else {
            ++i;
        }
    }
    if (list.size() >= 20) {
        for (const Rect& t : list) r.unite(t);
        list.clear();
    }
    list.push_back(r);
}

void SMenu::redrawDirty() {
    std::vector<Rect> rects;
    rects.swap(dirtyRects());
    if (rects.empty()) return;
    Pixel::pushClip();
    for (const Rect& r : rects) {
        if (!Pixel::setClip(r)) continue;
        // FUN_004a421e(0): de abajo arriba (el primero de la lista es el ultimo creado)
        std::vector<SMenu*>& menus = all();
        for (size_t i = menus.size(); i-- > 0;) {
            SMenu* m = menus[i];
            if (m->flags & kMenuHidden) continue;
            Rect mr = m->menuRect();
            if (mr.intersect(r)) m->draw();
        }
    }
    Pixel::popClip();
}

// ---------------------------------------------------------------------------------------------------------------
// Carga (FUN_004a3de6 / FUN_004a3d26 / FUN_004a39f7 / FUN_004a3533)

std::unique_ptr<SMenu> SMenu::load(uint32_t id, int lib) {
    ResPtr res = resources().get(kTagSMNU, id, lib);
    if (!res) return nullptr;
    std::unique_ptr<SMenu> m = fromWords(res->words(), id, lib);
    resources().release(res);
    return m;
}

std::unique_ptr<SMenu> SMenu::fromWords(std::span<const uint32_t> words, Tag tag, int lib) {
    std::unique_ptr<SMenu> m(new SMenu());
    m->tag = tag;
    m->lib = lib;
    m->sounds[0] = m->sounds[1] = m->sounds[2] = -1;
    if (tag != 0xffffffffu) m->strt = resources().get(kTagSTRT, tag, lib, kResRef);   // FUN_00491159
    m->parseMenuRecord(words);
    if (!m->parseItems(words)) return nullptr;
    all().insert(all().begin(), m.get());   // FUN_00495454 sobre DAT_0051e384 (el nuevo va primero)
    return m;
}

namespace {
// FUN_004a335b: salta un opcode y sus argumentos.
const uint32_t* skipOpcode(const uint32_t* p, const uint32_t* end) {
    if (p >= end) return end;
    const uint32_t op = *p;
    switch (op) {
        case 2: case 0x2a: return p + 5;
        case 0x17: {  // lista de celdas hasta 0x18
            ++p;
            while (p < end && *p != 0x18) {
                const uint32_t o = *p++;
                if (o == 1 || o == 7 || o == 0xc || o == 0xd || o == 0x11 || o == 0x19 || o == 0x1a) ++p;
            }
            return p < end ? p + 1 : end;
        }
        case 0x22: case 0x23: case 0x24: case 0x25:
            return (p + 1 < end) ? p + 2 + p[1] : end;
        case kOpEnd: return p + 1;
        default: return p + 2;
    }
}
}  // namespace

void SMenu::parseMenuRecord(std::span<const uint32_t> words) {
    const uint32_t* p = words.data();
    const uint32_t* end = words.data() + words.size();
    while (p < end && *p != kOpEnd) {
        if (*p != kRecMenu) {
            // FUN_004a33f3: saltar el registro de item
            ++p;
            while (p < end && *p != kOpEnd) p = skipOpcode(p, end);
            if (p < end) ++p;
            continue;
        }
        ++p;
        while (p < end && *p != kOpEnd) {
            const uint32_t op = *p;
            switch (op) {
                case 2: if (p + 4 < end) { x = int(p[1]); y = int(p[2]); w = int(p[3]); h = int(p[4]); } p += 5; break;
                case 3: if (p + 1 < end) flags |= p[1]; p += 2; break;
                case 10: if (p + 1 < end) menuParam = p[1]; p += 2; break;
                case 0xb: if (p + 1 < end && p[1] != 0 && p[1] != kOpEnd) palette = resources().get(kTagPALT, p[1], 0, kResRef); p += 2; break;   // FUN_004a1835
                case 0xc: if (p + 1 < end) param34 = p[1]; p += 2; break;
                case 0x12: if (p + 1 < end && p[1] != 0 && p[1] != kOpEnd) font = resources().font(p[1]); p += 2; break;   // FUN_004a17b0
                case 0x27: if (p + 1 < end) sounds[0] = int(p[1]); p += 2; break;
                case 0x28: if (p + 1 < end) sounds[1] = int(p[1]); p += 2; break;
                default: p = skipOpcode(p, end); break;
            }
        }
        if (p < end) ++p;
    }
}

void SMenu::parseGridCells(SMenuItem& it, const uint32_t*& p, const uint32_t* end) {
    // FUN_0049d315: opcodes hasta 0x18 -> nueva celda al final.
    GridCell cell;
    while (p < end && *p != 0x18) {
        const uint32_t op = *p++;
        if (p >= end) break;
        switch (op) {
            case 1: ++p; break;   // puntero a cadena (solo desde memoria)
            case 7: cell.text = resources().stringPtr(strt, int(*p)) ? resources().stringPtr(strt, int(*p)) : ""; ++p; break;
            case 0xc: cell.graphic.imag = *p++; break;
            case 0xd: cell.graphic.imageId = *p++; break;
            case 0x11: cell.data = int(*p++); break;
            case 0x19: cell.graphic.layer = *p++; break;
            case 0x1a: cell.graphic.col = *p++; break;
            default: break;
        }
    }
    if (p < end) ++p;   // 0x18
    it.cells.push_back(std::move(cell));
}

bool SMenu::parseItems(std::span<const uint32_t> words) {
    const uint32_t* p = words.data();
    const uint32_t* end = words.data() + words.size();
    while (p < end && *p != kOpEnd) {
        if (*p == kRecMenu) {
            ++p;
            while (p < end && *p != kOpEnd) p = skipOpcode(p, end);
            if (p < end) ++p;
            continue;
        }
        auto it = std::make_unique<SMenuItem>();
        // FUN_004a3439: valores por defecto
        it->menu = this;
        it->visible = 1;
        it->buttonMask = 9;
        it->colors[0][0] = 0xc0000000; it->colors[0][1] = 0xc0000000; it->colors[0][2] = 0xc03f3f3f;
        it->colors[1][0] = 0xc0ffffff; it->colors[1][1] = 0xc0ffffff; it->colors[1][2] = 0xc07f7f7f;
        it->colors[2][0] = 0xc0000000; it->colors[2][1] = 0xc0000000; it->colors[2][2] = 0xc03f3f3f;
        it->colors[3][0] = 0xc0ffffff; it->colors[3][1] = 0xc0ffffff; it->colors[3][2] = 0xc07f7f7f;
        it->colors[4][0] = 0xc0000000; it->colors[4][1] = 0xc000ff00; it->colors[4][2] = 0xc03f3f3f;
        it->colors[5][0] = 0xc0ffffff; it->colors[5][1] = 0xc0ffffff; it->colors[5][2] = 0xc07f7f7f;
        it->sounds[0] = it->sounds[1] = it->sounds[2] = -1;
        it->type = int(*p++);
        while (p < end && *p != kOpEnd) {
            const uint32_t op = *p;
            const uint32_t* a = p + 1;
            const bool hasArg = a < end;
            switch (op) {
                case 1: p += 2; break;   // cadena por puntero (no en archivo)
                case 2: if (p + 4 < end) { it->x = int(a[0]); it->y = int(a[1]); it->w = int(a[2]); it->h = int(a[3]); } p += 5; break;
                case 3: if (hasArg) it->state |= *a; p += 2; break;
                case 4: if (hasArg) it->param = *a; p += 2; break;
                case 5: if (hasArg) it->hotkey = *a; p += 2; break;
                case 6: if (hasArg) it->id = *a; p += 2; break;
                case 7:
                    if (hasArg) {
                        const char* s = resources().stringPtr(strt, int(*a));
                        it->text = s ? s : "";
                        it->hasText = true;
                    }
                    p += 2; break;
                case 8: case 9: it->listWidth = 0; p += 2; break;
                case 10: if (hasArg) it->flags |= *a; p += 2; break;
                case 0xb: if (hasArg && *a != 0 && *a != kOpEnd) it->palette = resources().get(kTagPALT, *a, 0, kResRef); p += 2; break;
                case 0xc: p += 2; if (hasArg) setAttribute(it.get(), 0xc, *a); break;
                case 0xd: if (hasArg) it->imageId = *a; p += 2; break;
                case 0xe: if (hasArg) it->animPeriod = int(*a); p += 2; break;
                case 0xf: if (hasArg) it->loop = int(*a); p += 2; break;
                case 0x11: if (hasArg) it->p68 = int(*a); p += 2; break;
                case 0x12: if (hasArg && *a != 0 && *a != kOpEnd) it->font = resources().font(*a); p += 2; break;
                case 0x13: if (hasArg) it->value = int(*a); p += 2; break;
                case 0x14: if (hasArg) it->textFlags |= *a; p += 2; break;
                case 0x15: if (hasArg) it->colors[0][0] = *a; p += 2; break;
                case 0x16: if (hasArg) it->colors[1][0] = *a; p += 2; break;
                case 0x17: ++p; parseGridCells(*it, p, end); break;
                case 0x1b: if (hasArg) it->colWidth = int(*a); p += 2; break;
                case 0x1c: if (hasArg) it->rowHeight = int(*a); p += 2; break;
                case 0x1d: if (hasArg) it->cellImageWidth = int(*a); p += 2; break;
                case 0x1e: if (hasArg) it->columns = int(*a); p += 2; break;
                case 0x1f: if (hasArg) it->rangeMin = int(*a); p += 2; break;
                case 0x20: if (hasArg) it->rangeMax = int(*a); p += 2; break;
                case 0x21:
                    if (hasArg) {
                        const char* s = resources().stringPtr(strt, int(*a));
                        it->tooltip = s ? s : "";
                    }
                    p += 2; break;
                case 0x22: case 0x23: case 0x24: case 0x25: {
                    if (!hasArg) { p = end; break; }
                    const uint32_t n = *a;
                    const int set = op == 0x22 ? 4 : (op == 0x23 ? 5 : (op == 0x24 ? 0 : 1));   // FUN_0049e9e8
                    for (uint32_t i = 0; i < 3; ++i) {
                        if (i < n && a + 1 + i < end) {
                            const uint32_t v = a[1 + i];
                            if ((v & 0x20000000u) == 0) it->colors[set][i] = v;
                        } else {
                            it->colors[set][i] = kColorNone;
                        }
                    }
                    p += 2 + n;
                    break;
                }
                case 0x26: if (hasArg) it->buttonMask = *a; p += 2; break;
                case 0x27: if (hasArg) it->sounds[0] = int(*a); p += 2; break;
                case 0x28: if (hasArg) it->sounds[1] = int(*a); p += 2; break;
                case 0x2a: if (p + 4 < end) { it->extra[0] = int(a[0]); it->extra[1] = int(a[1]); it->extra[2] = int(a[2]); it->extra[3] = int(a[3]); } p += 5; break;
                default: p = skipOpcode(p, end); break;   // "Unknown opcode in SMenu item list"
            }
        }
        if (p < end) ++p;
        // FUN_004a3533: los items de texto (5) reciben el mensaje 0x1c (seleccion) nada mas crearse
        if (it->type == kItemText && !(it->state & kStateStatic)) sendMessage(it.get(), kMsgSelectRange, 4, nullptr);
        items_.push_back(std::move(it));
    }
    return true;
}

SMenu::~SMenu() {
    // FUN_004a4025
    for (auto& it : items_) disposeItem(*it);
    items_.clear();
    std::vector<SMenu*>& list = all();
    list.erase(std::remove(list.begin(), list.end(), this), list.end());
}

void SMenu::disposeItem(SMenuItem& it) {
    if (it.proc) it.proc(it, kMsgDispose, 0, nullptr);
    sendMessage(&it, kMsgPlaySound, 0x81, nullptr);
    it.graphic.reset();
    it.picture.reset();
    it.font.reset();
    it.textBlock.reset();
    it.cells.clear();
}

// ---------------------------------------------------------------------------------------------------------------
// Atributos (FUN_004a19b4 / FUN_004a1c75)

bool SMenu::setAttribute(SMenuItem* it, int opcode, uint32_t value) {
    if (!it) return false;
    switch (opcode) {
        case 2: return false;
        case 3: it->state = value; return true;
        case 4: it->param = value; return true;
        case 5: it->hotkey = value; return true;
        case 6: it->id = value; return true;
        case 10: it->flags = value; return true;
        case 0xb: it->palette = value ? resources().get(kTagPALT, value, 0, kResRef) : nullptr; return true;
        case 0xc: {   // FUN_004a1607
            if (value == 0 || value == kOpEnd) return true;
            const uint32_t kind = it->graphicKind();
            if (kind == kGraphicImag) {
                it->graphic = resources().get(kTagIMAG, value, 0, kResRef);
            } else if (kind == kGraphicPict) {
                it->graphic = resources().get(kTagPICT, value, 0, kResRef);
                if (it->graphic) {
                    Image8 img;
                    Image16 img16;
                    std::string err;
                    auto pict = std::make_shared<OffPort>();
                    if (pictType(it->graphic->data) == uint32_t(PictType::IffPbm) && decodePictType2(it->graphic->data, img, &err)) {
                        pict->create(img.width, img.height, 8);
                        for (int yy = 0; yy < img.height; ++yy) std::memcpy(pict->pixelPtr(0, yy), img.pixels.data() + size_t(yy) * size_t(img.width), size_t(img.width));
                        pict->setPalette(std::make_shared<ColorTable>(ColorTable::fromPalette(img.palette)));
                        it->picture = pict;
                    } else if (pictType(it->graphic->data) == uint32_t(PictType::Rgb555) && decodePictType1(it->graphic->data, img16, &err)) {
                        pict->create(img16.width, img16.height, 16, PixelFormat::Rgb555);
                        for (int yy = 0; yy < img16.height; ++yy) std::memcpy(pict->pixelPtr(0, yy), img16.pixels.data() + size_t(yy) * size_t(img16.width), size_t(img16.width) * 2);
                        it->picture = pict;
                    }
                }
            }
            if (it->graphic) it->graphicId = value;
            return it->graphic != nullptr;
        }
        case 0xd: sendMessage(it, kMsgInvalidate); it->imageId = value; sendMessage(it, kMsgInvalidate); return true;
        case 0xe: it->animPeriod = int(value); return true;
        case 0xf: it->loop = int(value); return true;
        case 0x11: it->p68 = int(value); return true;
        case 0x12: it->font = (value && value != kOpEnd) ? resources().font(value) : nullptr; return true;   // FUN_004a1715
        case 0x13: sendMessage(it, kMsgInvalidate); it->value = int(value); return true;
        case 0x14: it->textFlags = value; return true;
        case 0x15: it->colors[0][0] = value; return true;
        case 0x16: it->colors[1][0] = value; return true;
        case 0x1b: it->colWidth = int(value); return true;
        case 0x1c: it->rowHeight = int(value); return true;
        case 0x1d: it->cellImageWidth = int(value); return true;
        case 0x1e: it->columns = int(value); return true;
        case 0x1f: sendMessage(it, kMsgInvalidate); it->rangeMin = int(value); return true;
        case 0x20: sendMessage(it, kMsgInvalidate); it->rangeMax = int(value); return true;
        case 0x26: it->buttonMask = value; return true;
        case 0x27: it->sounds[0] = int(value); return true;
        case 0x28: it->sounds[1] = int(value); return true;
        default: return false;
    }
}

bool SMenu::getAttribute(SMenuItem* it, int opcode, uint32_t* value) {
    if (!it || !value) return false;
    switch (opcode) {
        case 3: *value = it->state; return true;
        case 4: *value = it->param; return true;
        case 5: *value = it->hotkey; return true;
        case 6: *value = it->id; return true;
        case 10: *value = it->flags; return true;
        case 0xc: *value = it->graphicId; return true;
        case 0xd: *value = it->imageId; return true;
        case 0xe: *value = uint32_t(it->animPeriod); return true;
        case 0xf: *value = uint32_t(it->loop); return true;
        case 0x11: *value = uint32_t(it->p68); return true;
        case 0x13: *value = uint32_t(it->value); return true;
        case 0x14: *value = it->textFlags; return true;
        case 0x15: *value = it->colors[0][0]; return true;
        case 0x16: *value = it->colors[1][0]; return true;
        case 0x1b: *value = uint32_t(it->colWidth); return true;
        case 0x1c: *value = uint32_t(it->rowHeight); return true;
        case 0x1d: *value = uint32_t(it->cellImageWidth); return true;
        case 0x1e: *value = uint32_t(it->columns); return true;
        case 0x1f: *value = uint32_t(it->rangeMin); return true;
        case 0x20: *value = uint32_t(it->rangeMax); return true;
        case 0x26: *value = it->buttonMask; return true;
        case 0x27: *value = uint32_t(it->sounds[0]); return true;
        case 0x28: *value = uint32_t(it->sounds[1]); return true;
        default: return false;
    }
}

// ---------------------------------------------------------------------------------------------------------------
// Busqueda y rectangulos

SMenuItem* SMenu::itemById(uint32_t id) {
    for (auto& it : items_) if (it->id == id) return it.get();
    return nullptr;
}
SMenuItem* SMenu::itemByIndex(int index) {
    if (index < 0 || index >= int(items_.size())) return nullptr;
    return items_[size_t(index)].get();
}
int SMenu::itemIndex(const SMenuItem* item) const {
    for (size_t i = 0; i < items_.size(); ++i) if (items_[i].get() == item) return int(i);
    return -1;
}

Rect SMenu::menuRect() {
    Rect r = Rect::xywh(x, y, w, h);
    if (hook) hook(*this, 1, &r);
    return r;
}

Rect SMenu::itemRect(const SMenuItem& it) const {
    if (it.type == kItemHotKey) return Rect{};
    if (it.type == kItemListBox && (it.state & kStateHighlight)) {
        // Desplegable abierto: union de las filas desplazada al origen de la lista, limitada al port.
        Rect r;
        SMenuItem& mut = const_cast<SMenuItem&>(it);
        for (int i = 0; i < it.listCount; ++i) {
            Rect row = const_cast<SMenu*>(this)->listRowRect(mut, i);
            r.unite(row);
        }
        r.offset(x + it.x + it.listOffX, y + it.y + it.listOffY);
        if (it.state & 0x20) {
            Rect sel = const_cast<SMenu*>(this)->listRowRect(mut, int(it.param));
            r.offset(-sel.x0, -sel.y0);
        }
        const OffPort* p = port ? port : Pixel::port();
        if (p) {
            if (r.x1 > p->width()) r.offset(p->width() - r.x1, 0);
            if (r.x0 < 0) r.offset(-r.x0, 0);
            if (r.y1 > p->height()) r.offset(0, p->height() - r.y1);
            if (r.y0 < 0) r.offset(0, -r.y0);
        }
        return r;
    }
    return Rect::xywh(x + it.x, y + it.y, it.w, it.h);
}

int SMenu::subHitTest(SMenuItem& it, int px, int py, int* subX, int* subY) {
    // FUN_0049f31e
    if (it.type == kItemListBox) {
        if (!(it.state & kStateHighlight)) return -1;
        const Rect base = itemRect(it);
        for (int i = 0; i < it.listCount; ++i) {
            Rect r = listRowRect(it, i);
            r.offset(base.x0, base.y0);
            if (r.contains(px, py)) {
                if (subX) *subX = px - r.x0;
                if (subY) *subY = py - r.y0;
                return i;
            }
        }
        return -1;
    }
    if (it.type == kItemGrid) {
        const int rh = int(sendMessage(&it, kMsgGetRowHeight));
        const int cw = int(sendMessage(&it, kMsgGetColWidth));
        const int cols = int(sendMessage(&it, kMsgGetColumns));
        const int count = int(sendMessage(&it, kMsgGetCount));
        const Rect base = itemRect(it);
        Rect cell = base;
        cell.y1 = base.y0 + rh;
        int index = it.scrollTop;
        while (index < count && cell.y0 < base.y1) {
            cell.x0 = base.x0;
            cell.x1 = base.x0 + cw;
            for (int c = 0; c < cols && index < count; ++c, ++index) {
                if (cell.contains(px, py)) {
                    if (subX) *subX = px - cell.x0;
                    if (subY) *subY = py - cell.y0;
                    return index;
                }
                cell.offset(cw, 0);
            }
            cell.offset(0, rh);
        }
        return -1;
    }
    return -1;
}

Rect SMenu::subRect(SMenuItem& it, int sub) {
    if (it.type == kItemScrollBar) {
        Rect r;
        scrollPartRect(it, sub, r);
        return r;
    }
    return itemRect(it);
}

SMenuItem* SMenu::hitTest(int px, int py, int* sub, int* subX, int* subY) {
    if (sub) *sub = 0;
    if (subX) *subX = 0;
    if (subY) *subY = 0;
    // FUN_0049f4c2: desde el ultimo item (el de arriba) hacia el primero.
    for (size_t i = items_.size(); i-- > 0;) {
        SMenuItem& it = *items_[i];
        if (it.state & (kStateDisabled | kStateStatic)) continue;
        if (it.visible <= 0) continue;
        const Rect r = itemRect(it);
        if (!r.contains(px, py)) continue;
        if (it.type == kItemListBox || it.type == kItemGrid) {
            int sx = 0, sy = 0;
            const int row = subHitTest(it, px, py, &sx, &sy);
            if (row != -1 && sendMessage(&it, kMsgGetSubState, uint32_t(row)) != 2) {
                if (subX) *subX = sx;
                if (subY) *subY = sy;
                if (sub) *sub = 0;
                return &it;
            }
            continue;
        }
        int part = 0;
        if (it.type == kItemScrollBar) part = scrollHitPart(it, px, py);
        if (sub) *sub = part;
        const Rect sr = subRect(it, part);
        if (subX) *subX = px - sr.x0;
        if (subY) *subY = py - sr.y0;
        return &it;
    }
    return nullptr;
}

SMenuItem* SMenu::focusedItem() {
    for (auto& it : items_) if (it->hasFocus()) return it.get();
    return nullptr;
}

void SMenu::setFocus(SMenuItem* item) {
    // FUN_0049f696
    for (auto& it : items_) {
        if (it.get() == item) {
            if (!it->hasFocus()) sendMessage(it.get(), kMsgSetFocus, 1);
        } else if (it->hasFocus()) {
            sendMessage(it.get(), kMsgSetFocus, 0);
        }
    }
}

SMenuItem* SMenu::nextFocusable(SMenuItem* from, bool backwards) {
    // FUN_0049f752: recorre circularmente buscando un item con el bit 0x1000000 ("enfocable").
    if (items_.empty()) return nullptr;
    int start = from ? itemIndex(from) : (backwards ? 0 : int(items_.size()) - 1);
    if (start < 0) start = 0;
    const int n = int(items_.size());
    int i = start;
    do {
        i = backwards ? (i - 1 + n) % n : (i + 1) % n;
        if (items_[size_t(i)]->state & 0x1000000u) return items_[size_t(i)].get();
    } while (i != start);
    return nullptr;
}

// ---------------------------------------------------------------------------------------------------------------
// Estado

void SMenu::setHighlight(SMenuItem* it, int sub, bool on) {
    // FUN_004a228a
    if (!it || (it->state & kStateDisabled)) return;
    const bool cur = (it->state & kStateHighlight) != 0;
    if (cur == on) return;
    sendMessage(it, kMsgInvalidate);
    it->state = (it->state & ~uint32_t(kStateHighlight | kStateDisabled)) | (on ? kStateHighlight : 0);
    it->pressSub = sub;
    sendMessage(it, kMsgInvalidate);
    sendMessage(it, kMsgSync);
}

void SMenu::setDisabled(SMenuItem* it, bool on) {
    // FUN_004a2307
    if (!it) return;
    const bool cur = (it->state & kStateDisabled) != 0;
    if (cur == on) return;
    sendMessage(it, kMsgInvalidate);
    it->state = (it->state & ~uint32_t(kStateHighlight | kStateDisabled)) | (on ? kStateDisabled : 0);
    sendMessage(it, kMsgInvalidate);
    sendMessage(it, kMsgSync);
}

void SMenu::setChecked(SMenuItem* it, bool on) {
    // FUN_0049f947 / FUN_0049f8dd / FUN_0049f8a1
    if (!it) return;
    if (it->type == kItemRadio) {
        for (auto& o : items_)
            if (o->type == kItemRadio && o->param == it->param && o->isChecked()) {
                sendMessage(o.get(), kMsgInvalidate);
                o->state &= ~uint32_t(kStateChecked);
            }
        sendMessage(it, kMsgInvalidate);
        it->state |= kStateChecked;
        return;
    }
    sendMessage(it, kMsgInvalidate);
    it->state = (it->state & ~uint32_t(kStateChecked)) | (on ? kStateChecked : 0);
}

void SMenu::setHidden(bool on) {
    if (on) flags |= kMenuHidden; else flags &= ~uint32_t(kMenuHidden);
    invalidate();
}

void SMenu::invalidate() {
    // FUN_0049f83e
    Rect r = menuRect();
    r.unite(Rect::xywh(x, y, w, h));
    if (invalidateHook) invalidateHook(*this, r);
    else addDirty(r);
}

void SMenu::invalidateItem(SMenuItem& it) {
    // FUN_0049f7c9 / FUN_0049efae: rect del item unido al de su grafico IMAG (con hotspot)
    Rect r = Rect::xywh(x + it.x, y + it.y, it.w, it.h);
    if (it.graphicKind() == kGraphicImag && it.graphic) {
        uint32_t cf = 0;
        const int layer = it.stateIndex();
        const TileView t = imagCellTile(it.graphic->imag(), it.imageId, layer, 0, (it.state & kStateAnimated) ? it.frame : 0, resources().tileLookup(), &cf);
        if (t.valid()) r.unite(tileRect(t, x + it.x, y + it.y));
    }
    if (invalidateHook) invalidateHook(*this, r);
    else addDirty(r);
}

void SMenu::colorsFromPalette(const ColorTable& pal) {
    // FUN_0049e638 (rama de 16 bpp; en 8 bpp serian indices de la paleta del port)
    OffPort* p = port ? port : Pixel::port();
    const PixelFormat fmt = p ? p->format() : PixelFormat::Rgb555;
    const bool indexed = p && p->bpp() == 8;
    auto conv = [&](int idx) -> ColorRef {
        if (indexed) return uint32_t(idx);
        return pal.to16(size_t(idx), fmt);
    };
    for (int s = 0; s < 3; ++s) {
        colors[kFill][s] = conv(0x10 + s);
        colors[kLight][s] = conv(0x13 + s);
        colors[kDark][s] = conv(0x16 + s);
        colors[kBg][s] = conv(0x20 + s);
        colors[kBgLight][s] = conv(0x23 + s);
        colors[kBgDark][s] = conv(0x26 + s);
        colors[kCheck][s] = conv(0x40 + s);
        colors[kTextFg][s] = uint32_t(0x30 + s);
        colors[kSelBack][s] = uint32_t(0x33 + s);
        colors[kSelText][s] = uint32_t(0x36 + s);
        colors[kTextBg][s] = uint32_t(0x10 + s);
    }
}

// ---------------------------------------------------------------------------------------------------------------
// show / layout

void SMenu::layoutItem(SMenuItem& it) {
    // FUN_004a1eb4
    if (it.graphicKind() == kGraphicImag && it.graphic && (it.h == -1 || it.w == -1)) {
        const TileView t = imagCellTile(it.graphic->imag(), it.imageId, 0, 0, 0, resources().tileLookup());
        if (t.valid()) {
            if (it.h == -1) it.h = t.height();
            if (it.w == -1) it.w = t.width();
        }
    } else if (it.graphicKind() == kGraphicPict && it.picture) {
        if (it.h == -1) it.h = it.picture->height();
        if (it.w == -1) it.w = it.picture->width();
    }
    if (it.x == -1) it.x = div2(w - it.w);
    if (it.y == -1) it.y = div2(h - it.h);
    if (it.proc) it.proc(it, kMsgInit, 0, nullptr);
}

void SMenu::show() {
    // FUN_004a2004
    OffPort* p = port ? port : Pixel::port();
    if (x == -1) x = p ? div2(p->width() - w) : 0;
    if (y == -1) y = p ? div2(p->height() - h) : 0;
    for (auto& it : items_) layoutItem(*it);
    invalidate();
    if (palette && palette->palette) colorsFromPalette(*palette->palette);
}

// ---------------------------------------------------------------------------------------------------------------
// Dibujado

bool SMenu::selectFont(SMenuItem& it) {
    // FUN_0049eb9f
    if (it.font) { Text::setFont(it.font); return true; }
    if (font) { Text::setFont(font); return true; }
    return false;
}

void SMenu::draw() {
    // FUN_004a2078
    Pixel::pushClip();
    if (Pixel::clipTo(menuRect())) {
        if (port) Pixel::pushPort(port);
        ColorTablePtr savedPal = Text::palette();
        if (palette && palette->palette) Text::setPalette(palette->palette);
        bool drewBg = hook ? hook(*this, 3, nullptr) != 0 : false;
        if (!drewBg && menuParam != 1) {   // FUN_004a10b3 / FUN_004a0ff9
            const Rect r = Rect::xywh(x, y, w, h);
            Pixel::fillRect(r.x0 + 1, r.y0 + 1, r.x1 - 1, r.y1 - 1, colors[kBg][0]);
            Pixel::fillRect(r.x0, r.y0, r.x1, r.y0 + 1, colors[kBgLight][0]);
            Pixel::fillRect(r.x0, r.y0, r.x0 + 1, r.y1 - 1, colors[kBgLight][0]);
            Pixel::fillRect(r.x0, r.y1 - 1, r.x1, r.y1, colors[kBgDark][0]);
            Pixel::fillRect(r.x1 - 1, r.y0 + 1, r.x1, r.y1, colors[kBgDark][0]);
        }
        for (auto& it : items_) if (!(it->state & kStateHighlight)) drawItem(*it);
        for (auto& it : items_) if (it->state & kStateHighlight) drawItem(*it);
        if (palette && palette->palette) Text::setPalette(savedPal);
        if (port) Pixel::popPort();
    }
    Pixel::popClip();
}

void SMenu::drawItem(SMenuItem& it) {
    // FUN_004a0f18
    if (it.visible <= 0) return;
    Pixel::pushClip();
    bool handled = false;
    if (it.proc) handled = it.proc(it, kMsgDraw, 0, nullptr) != 0;
    if (!handled) drawItemDefault(it);
    Pixel::popClip();
}

void SMenu::drawItemDefault(SMenuItem& it) {
    switch (it.type) {
        case kItemButton: drawButton(it); break;
        case kItemCheckBox: drawCheckBox(it); break;
        case kItemRadio: drawRadio(it); break;
        case kItemPicture: drawPicture(it); break;
        case kItemListBox: drawListBox(it); break;
        case kItemText: drawTextItem(it); break;
        case kItemGrid: drawGrid(it); break;
        case kItemScrollBar: drawScrollBar(it); break;
        default: break;
    }
}

void SMenu::drawButtonText(const char* text, int s) {
    // FUN_0049f9c0
    const int startX = Text::penX();
    Text::setColor(colors[kTextFg][s]);
    const uint32_t prev = Pixel::setBlitMode(Pixel::blitModeFor(8));
    const FontView* f = Text::font();
    for (; text && *text; ++text) {
        const unsigned char c = uint8_t(*text);
        if (c == 1) Text::setColor(colors[kTextFg][s]);
        else if (c == 2) Text::setColor(colors[kSelBack][s]);
        else if (c == '\r') Text::moveTo(startX, Text::penY() + (f ? f->lineHeight() : 0));
        else Text::drawChar(c);
    }
    Pixel::setBlitMode(prev);
}

bool SMenu::graphicSize(SMenuItem& it, int layer, uint32_t imageId, int col, int* gw, int* gh) {
    // FUN_0049fca2
    if (!it.graphic || it.graphicKind() != kGraphicImag) return false;
    if (imageId == 0) imageId = it.imageId;
    const TileView t = imagCellTile(it.graphic->imag(), imageId, layer, 0, col, resources().tileLookup());
    if (!t.valid()) return false;
    *gw = t.width();
    *gh = t.height();
    return true;
}

void SMenu::drawImagCell(SMenuItem& it, const Rect& clipRect, int px, int py, int layer, uint32_t imageId, int col) {
    // FUN_0049fd2e
    if (!it.graphic || it.graphicKind() != kGraphicImag) return;
    if (imageId == 0) imageId = it.imageId;
    uint32_t cf = 0;
    const TileView t = imagCellTile(it.graphic->imag(), imageId, layer, 0, col, resources().tileLookup(), &cf);
    if (!t.valid() || (cf & 0x40000000u)) return;
    const uint32_t prev = Pixel::setBlitMode(Pixel::blitModeFor(t.bytesPerPixel() * 8));
    Pixel::pushClip();
    Pixel::clipTo(clipRect);
    drawTile(t, clipRect.x0 + px, clipRect.y0 + py, t.defaultMode(), false);
    Pixel::popClip();
    Pixel::setBlitMode(prev);
}

void SMenu::drawGraphic(SMenuItem& it, const Rect& r) {
    // FUN_0049fe03
    if (!it.graphic) return;
    const int layer = it.layerIndex();
    const int col = (it.state & kStateAnimated) ? it.frame : 0;
    uint32_t cf = 0;
    const TileView t = imagCellTile(it.graphic->imag(), it.imageId, layer, 0, col, resources().tileLookup(), &cf);
    if (!t.valid() || (cf & 0x40000000u)) return;
    const uint32_t prev = Pixel::setBlitMode(Pixel::blitModeFor(t.bytesPerPixel() * 8));
    Pixel::pushClip();
    if (Pixel::clipTo(r)) {
        Rect inner = Rect{0, 0, t.width(), t.height()};
        const uint32_t align = it.state & kStateAlignMask;
        placeRect(r, inner, align);
        if (align != 0) inner.offset(t.hotX(), t.hotY());
        drawTile(t, inner.x0, inner.y0, t.defaultMode(), false);
    }
    Pixel::popClip();
    Pixel::setBlitMode(prev);
}

void SMenu::drawGraphicText(SMenuItem& it, const Rect& rIn) {
    // FUN_0049ff48
    if (!it.hasText || it.text.empty()) return;
    Rect r = rIn;
    Text::push();
    if (!selectFont(it)) { Text::pop(); return; }
    int s = it.layerIndex();
    uint32_t centerFlag = 0;
    if (it.extra[2] != 0 && it.extra[3] != 0) {
        Rect tr;
        tr.x0 = it.extra[0];
        tr.y0 = it.extra[1];
        tr.x1 = (it.extra[2] == -1 ? r.width() : it.extra[2]) + tr.x0;
        tr.y1 = (it.extra[3] == -1 ? r.height() : it.extra[3]) + tr.y0;
        tr.offset(r.x0, r.y0);
        r.intersect(tr);
    } else {
        int gw = 0, gh = 0;
        graphicSize(it, s, 0, 0, &gw, &gh);
        switch (it.state & kStateAlignMask) {
            case 0: centerFlag = kTextCenter; break;
            case kStateAlignTop: centerFlag = kTextCenter; r.y0 += gh + 4; break;
            case kStateAlignTopLeft: case kStateAlignTopRight: r.y0 += gh + 4; break;
            case kStateAlignRight: r.x1 -= gw + 4; break;
            case kStateAlignBottom: centerFlag = kTextCenter; r.y1 -= gh + 4; break;
            case kStateAlignBottomRight: case kStateAlignBottomLeft: r.y1 -= gh + 4; break;
            case kStateAlignLeft: r.x0 += gw + 4; break;
            case kStateAlignCenter: centerFlag = kTextCenter; break;
            default: break;
        }
    }
    if (s > 2) s -= 3;
    Text::setBackground(pick(it.colors[1][s], colors[kTextBg][s]));
    Text::setColor(pick(it.colors[0][s], colors[kTextFg][s]));
    if (!r.empty()) Text::drawText(it.text.c_str(), r, it.textFlags | centerFlag | kTextVCenter);
    Text::pop();
}

void SMenu::drawButton(SMenuItem& it) {
    // FUN_004a016e
    const Rect r = itemRect(it);
    const int s = it.stateIndex();
    const uint32_t kind = it.graphicKind();
    if (kind == kGraphicPlain) {
        Pixel::fillRect(r.x0 + 1, r.y0 + 1, r.x1 - 1, r.y1 - 1, colors[kFill][s]);
        Pixel::fillRect(r.x0, r.y0, r.x1, r.y0 + 1, colors[kLight][s]);
        Pixel::fillRect(r.x0, r.y0, r.x0 + 1, r.y1 - 1, colors[kLight][s]);
        Pixel::fillRect(r.x0, r.y1 - 1, r.x1, r.y1, colors[kDark][s]);
        Pixel::fillRect(r.x1 - 1, r.y0 + 1, r.x1, r.y1, colors[kDark][s]);
    } else if (kind == kGraphicImag) {
        drawGraphic(it, r);
        drawGraphicText(it, r);
        return;
    } else if (kind != kGraphicTextOnly) {
        return;
    }
    Text::push();
    Text::setBackground(colors[kTextBg][s]);
    if (selectFont(it) && it.hasText) {
        const FontView* f = Text::font();
        const int baseline = buttonBaseline(r.y0, r.y1, f->ascent());
        int off = div2(r.width() - Text::maxLineWidth(it.text.c_str()));
        if (off < 0) off = 0;
        Text::moveTo(r.x0 + off, baseline);
        drawButtonText(it.text.c_str(), s);
    }
    Text::pop();
}

void SMenu::drawCheckBox(SMenuItem& it) {
    // FUN_004a03cf
    const Rect r = itemRect(it);
    const int s = it.stateIndex();
    const uint32_t kind = it.graphicKind();
    if (kind == kGraphicImag) {
        if ((it.state & kStateAlignMask) == 0 && it.hasText) it.state |= kStateAlignLeft;
        drawGraphic(it, r);
        drawGraphicText(it, r);
        return;
    }
    if (kind == kGraphicNone) return;
    const int mid = div2(r.height()) + r.y0;
    const int top = mid - 8, x1 = r.x0 + 0x10;
    Pixel::fillRect(r.x0 + 1, mid - 7, r.x0 + 0xf, mid + 7, colors[kFill][s]);
    Pixel::fillRect(r.x0, top, x1, mid - 7, colors[kDark][0]);
    Pixel::fillRect(r.x0, top, r.x0 + 1, mid + 7, colors[kDark][0]);
    Pixel::fillRect(r.x0, mid + 7, x1, mid + 8, colors[kLight][0]);
    Pixel::fillRect(r.x0 + 0xf, mid - 7, x1, mid + 8, colors[kLight][0]);
    if (it.isChecked()) {
        for (int i = 4; i < 0xc; ++i) {
            Pixel::fillRect(r.x0 + i, top + i, r.x0 + i + 2, top + i + 1, colors[kCheck][s]);
            Pixel::fillRect(r.x0 + i, (mid + 7) - i, r.x0 + i + 2, (mid + 8) - i, colors[kCheck][s]);
        }
    }
    Text::push();
    Text::setBackground(colors[kTextBg][0]);
    if (selectFont(it) && it.hasText) {
        const FontView* f = Text::font();
        Text::moveTo(r.x0 + 0x14, buttonBaseline(r.y0, r.y1, f->ascent()));
        drawButtonText(it.text.c_str(), s == 2 ? 2 : 0);
    }
    Text::pop();
}

void SMenu::drawRadio(SMenuItem& it) {
    // FUN_004a060f
    const Rect r = itemRect(it);
    const int s = it.stateIndex();
    const uint32_t kind = it.graphicKind();
    if (kind == kGraphicImag) {
        if ((it.state & kStateAlignMask) == 0 && it.hasText) it.state |= kStateAlignLeft;
        drawGraphic(it, r);
        drawGraphicText(it, r);
        return;
    }
    if (kind == kGraphicNone) return;
    const int mid = div2(r.height()) + r.y0;
    const int x0 = r.x0, x1 = r.x0 + 0xf;
    Pixel::fillRect(x0 + 1, mid - 6, x0 + 0xe, mid + 7, colors[kFill][s]);
    Pixel::fillRect(x0, mid - 7, x1, mid - 6, colors[kDark][0]);
    Pixel::fillRect(x0, mid - 7, x0 + 1, mid + 7, colors[kDark][0]);
    Pixel::fillRect(x0, mid + 7, x1, mid + 8, colors[kLight][0]);
    Pixel::fillRect(x0 + 0xe, mid - 6, x1, mid + 8, colors[kLight][0]);
    if (it.isChecked()) {
        Pixel::fillRect(x0 + 5, mid - 4, x0 + 10, mid - 3, colors[kCheck][s]);
        Pixel::fillRect(x0 + 3, mid - 3, x0 + 0xc, mid - 1, colors[kCheck][s]);
        Pixel::fillRect(x0 + 2, mid - 1, x0 + 0xd, mid + 2, colors[kCheck][s]);
        Pixel::fillRect(x0 + 3, mid + 2, x0 + 0xc, mid + 4, colors[kCheck][s]);
        Pixel::fillRect(x0 + 5, mid + 4, x0 + 10, mid + 5, colors[kCheck][s]);
    }
    Text::push();
    Text::setBackground(colors[kTextBg][0]);
    if (selectFont(it) && it.hasText) {
        const FontView* f = Text::font();
        Text::moveTo(r.x0 + 0x13, buttonBaseline(r.y0, r.y1, f->ascent()));
        drawButtonText(it.text.c_str(), s == 2 ? 2 : 0);
    }
    Text::pop();
}

void SMenu::drawPicture(SMenuItem& it) {
    // FUN_004a034a
    const Rect r = itemRect(it);
    const uint32_t kind = it.graphicKind();
    if (kind == kGraphicImag) {
        drawGraphic(it, r);
        drawGraphicText(it, r);
    } else if (kind == kGraphicPict && it.picture) {
        OffPort* dst = Pixel::port();
        if (!dst) return;
        const Rect clip = Pixel::clip();
        dst->blitFrom(*it.picture, r, it.picture->bounds(), &clip, nullptr, 0);
    }
}

Rect SMenu::listRowRect(SMenuItem& it, int row) {
    // FUN_0049ebfb (tipo 4)
    Text::push();
    Rect r;
    if (selectFont(it)) {
        if (it.listWidth < 1) {
            int widest = 0;
            for (int i = 0; i < it.listCount; ++i) {
                const char* s = resources().stringPtr(it.listStrt, i);
                const int tw = s ? Text::textWidth(s) : 0;
                if (tw > widest) widest = tw;
            }
            it.listWidth = widest + 8;
        }
        const FontView* f = Text::font();
        const int rh = f->ascent() + f->descent() + 6;
        r = Rect{0, rh * row, it.listWidth, rh * row + rh};
    }
    Text::pop();
    return r;
}

void SMenu::drawListBox(SMenuItem& it) {
    // FUN_004a08c5
    const Rect r = itemRect(it);
    const int s = it.stateIndex();
    const uint32_t kind = it.graphicKind();
    if (s == 1) {
        if (kind == kGraphicCombo) {
            it.state &= ~uint32_t(kStateHighlight);
            const Rect box = itemRect(it);
            it.state |= kStateHighlight;
            Pixel::fillRect(box.x0 + 1, box.y0 + 1, box.x1 - 1, box.y1 - 1, colors[kFill][1]);
            Text::push();
            Text::setBackground(colors[kTextBg][1]);
            if (selectFont(it) && it.hasText) {
                const FontView* f = Text::font();
                int off = div2(box.width() - Text::maxLineWidth(it.text.c_str()));
                if (off < 0) off = 0;
                Text::moveTo(box.x0 + off, buttonBaseline(box.y0, box.y1, f->ascent()));
                drawButtonText(it.text.c_str(), 1);
                it.listOffX = 0;
                it.listOffY = (box.y1 - y) + 1;
            }
            Text::pop();
        }
        Pixel::fillRect(r.x0 + 1, r.y0 + 1, r.x1 - 1, r.y1 - 1, colors[kFill][0]);
        Pixel::fillRect(r.x0, r.y0, r.x1, r.y0 + 1, colors[kLight][0]);
        Pixel::fillRect(r.x0, r.y0, r.x0 + 1, r.y1 - 1, colors[kLight][0]);
        Pixel::fillRect(r.x0, r.y1 - 1, r.x1, r.y1, colors[kDark][0]);
        Pixel::fillRect(r.x1 - 1, r.y0 + 1, r.x1, r.y1, colors[kDark][0]);
        Text::push();
        Text::setBackground(colors[kTextBg][0]);
        if (selectFont(it) && it.listStrt) {
            const FontView* f = Text::font();
            for (int i = 0; i < it.listCount; ++i) {
                Rect row = listRowRect(it, i);
                row.offset(r.x0, r.y0);
                Text::moveTo(row.x0 + 4, buttonBaseline(row.y0, row.y1, f->ascent()));
                const char* str = resources().stringPtr(it.listStrt, i);
                drawButtonText(str ? str : "", (i + 1 == it.listSel) ? 1 : 0);
            }
        }
        Text::pop();
        return;
    }
    if (kind == kGraphicCombo) {
        Pixel::fillRect(r.x0 + 1, r.y0 + 1, r.x1 - 1, r.y1 - 1, colors[kFill][s]);
        Text::push();
        Text::setBackground(colors[kTextBg][s]);
        if (selectFont(it) && it.hasText) {
            const FontView* f = Text::font();
            int off = div2(r.width() - Text::maxLineWidth(it.text.c_str()));
            if (off < 0) off = 0;
            Text::moveTo(r.x0 + off, buttonBaseline(r.y0, r.y1, f->ascent()));
            drawButtonText(it.text.c_str(), s);
            it.listOffX = 0;
            it.listOffY = (r.y1 - y) + 1;
        }
        Text::pop();
        return;
    }
    Pixel::fillRect(r.x0 + 1, r.y0 + 1, r.x1 - 1, r.y1 - 1, colors[kFill][s]);
    Pixel::fillRect(r.x0, r.y0, r.x1, r.y0 + 1, colors[kLight][s]);
    Pixel::fillRect(r.x0, r.y0, r.x0 + 1, r.y1 - 1, colors[kLight][s]);
    Pixel::fillRect(r.x0, r.y1 - 1, r.x1, r.y1, colors[kDark][s]);
    Pixel::fillRect(r.x1 - 1, r.y0 + 1, r.x1, r.y1, colors[kDark][s]);
    Text::push();
    Text::setBackground(colors[kTextBg][s]);
    if (selectFont(it) && it.listStrt) {
        const FontView* f = Text::font();
        Text::moveTo(r.x0 + 4, buttonBaseline(r.y0, r.y1, f->ascent()));
        const char* str = resources().stringPtr(it.listStrt, int(it.param));
        drawButtonText(str ? str : "", s);
    }
    Text::pop();
}

void SMenu::textBlockFor(SMenuItem& it) {
    // FUN_0049ddf8
    if (!it.textBlock) it.textBlock = std::make_unique<TextBlock>();
    it.textBlock->text = it.text.c_str();
    it.textBlock->rect = itemRect(it);
    it.textBlock->flags = it.textFlags | (it.hasFocus() ? kTextSelection : 0);
}

void SMenu::drawTextItem(SMenuItem& it) {
    // FUN_0049e47a
    const Rect r = itemRect(it);
    int s = it.stateIndex();
    const uint32_t kind = it.graphicKind();
    if (kind != kGraphicPlain && kind != kGraphicTextOnly) return;
    if (!it.hasText && !(it.flags & kItemFlagEdit)) return;
    Text::push();
    if (selectFont(it)) {
        if ((it.flags & kItemFlagEdit) && s == 1) s = 0;
        Text::setBackground(pick(it.colors[1][s], colors[kTextBg][s]));
        Text::setColor(pick(it.colors[0][s], colors[kTextFg][s]));
        Text::setSelectionColors(pick(it.colors[3][s], colors[kSelText][s]), pick(it.colors[2][s], colors[kSelBack][s]));
        textBlockFor(it);
        TextBlock& b = *it.textBlock;
        Text::drawBlock(b);
        if ((it.flags & kItemFlagEdit)) {
            const int len = int(it.text.size());
            if (b.selEnd < 0 || b.selEnd > len) { b.selEnd = len; b.selStart = len; }
            if ((it.caret & 0xc0000000u) == 0 && b.selStart == b.selEnd && it.hasFocus() && !(it.state & kStateDisabled)) {
                int cx = 0, cy = 0;
                Text::caretPos(it.text.c_str(), r.width(), r.height(), b.selEnd, &cx, &cy, false, b.flags);
                const FontView* f = Text::font();
                Pixel::fillRect(r.x0 + cx, r.y0 + cy, r.x0 + cx + 1, r.y0 + cy + f->ascent() + f->descent(), colorRgb(255, 255, 255));
            }
        }
    }
    Text::pop();
}

int SMenu::gridRowHeight(SMenuItem& it) {
    if (it.rowHeight) return it.rowHeight;
    Text::push();
    int h2 = 0;
    if (selectFont(it)) h2 = Text::font()->ascent() + Text::font()->descent() + 4;
    Text::pop();
    return h2;
}
int SMenu::gridColWidth(SMenuItem& it) { return it.colWidth ? it.colWidth : it.w; }
int SMenu::gridColumns(SMenuItem&) { return 1; }
int SMenu::gridVisibleRows(SMenuItem& it) {
    // FUN_0049d06a(0): filas completas (redondeo hacia arriba)
    const Rect r = itemRect(it);
    const int rh = int(sendMessage(&it, kMsgGetRowHeight));
    if (rh <= 0) return 0;
    return (r.height() + rh - 1) / rh;
}

void SMenu::drawGrid(SMenuItem& it) {
    // FUN_0049da81
    const Rect r = Rect::xywh(x + it.x, y + it.y, it.w, it.h);
    int s = it.stateIndex();
    if (s == 1) s = 0;
    const uint32_t kind = it.graphicKind();
    if (kind == kGraphicPlain) {
        Pixel::fillRect(r.x0 + 1, r.y0 + 1, r.x1 - 1, r.y1 - 1, pick(it.colors[5][s], colors[kFill][s]));
        Pixel::fillRect(r.x0, r.y0, r.x1, r.y0 + 1, colors[kDark][s]);
        Pixel::fillRect(r.x0, r.y0, r.x0 + 1, r.y1 - 1, colors[kDark][s]);
        Pixel::fillRect(r.x0, r.y1 - 1, r.x1, r.y1, colors[kLight][s]);
        Pixel::fillRect(r.x1 - 1, r.y0 + 1, r.x1, r.y1, colors[kLight][s]);
    } else if (kind != kGraphicTextOnly) {
        return;
    }
    const int rh = int(sendMessage(&it, kMsgGetRowHeight));
    const int cw = int(sendMessage(&it, kMsgGetColWidth));
    const int cols = int(sendMessage(&it, kMsgGetColumns));
    const int count = int(sendMessage(&it, kMsgGetCount));
    Pixel::pushClip();
    Pixel::clipTo(r);
    Rect cell = r;
    cell.y1 = r.y0 + rh;
    int index = it.scrollTop;
    while (index < count && cell.y0 < r.y1) {
        cell.x0 = r.x0;
        cell.x1 = r.x1;
        for (int c = 0; c < cols && index < count; ++c, ++index) {
            sendMessage(&it, kMsgDrawCell, uint32_t(index), &cell);
            cell.offset(cw, 0);
        }
        cell.offset(0, rh);
    }
    Pixel::popClip();
}

void SMenu::drawGridCell(SMenuItem& it, int index, const Rect& cellRect) {
    // FUN_0049d7f4
    if (index < 0 || index >= int(it.cells.size())) return;
    const GridCell& cell = it.cells[size_t(index)];
    Text::push();
    int s = it.stateIndex() == 2 ? 2 : ((cell.flags & 1) ? 1 : 0);
    if (selectFont(it)) {
        if (s == 1) Pixel::fillRect(cellRect, pick(it.colors[5][1], colors[kFill][1]));
        Text::setBackground(pick(it.colors[1][s], colors[kTextBg][s]));
        Text::setColor(pick(it.colors[0][s], colors[kTextFg][s]));
        if (cell.graphic.imag != 0) {
            ResPtr imag = resources().get(kTagIMAG, cell.graphic.imag, 0, kResRef);
            if (imag) {
                uint32_t cf = 0;
                const TileView t = imagCellTile(imag->imag(), cell.graphic.imageId, int(cell.graphic.layer), 0, int(cell.graphic.col), resources().tileLookup(), &cf);
                if (t.valid() && !(cf & 0x40000000u)) {
                    Rect area = cellRect;
                    area.x1 = area.x0 + it.cellImageWidth;
                    if (area.intersect(cellRect)) {
                        Rect inner = Rect{0, 0, t.width(), t.height()};
                        placeRect(area, inner, kStateAlignCenter);
                        Pixel::pushClip();
                        const uint32_t prev = Pixel::setBlitMode(Pixel::blitModeFor(t.bytesPerPixel() * 8));
                        if (Pixel::clipTo(area)) drawTile(t, inner.x0 + t.hotX(), inner.y0 + t.hotY(), t.defaultMode(), false);
                        Pixel::setBlitMode(prev);
                        Pixel::popClip();
                    }
                }
                resources().release(imag);
            }
        }
        Rect tr = cellRect;
        tr.x0 += it.cellImageWidth ? it.cellImageWidth : 4;
        tr.x1 -= 4;
        if (!cell.text.empty()) Text::drawText(cell.text.c_str(), tr, it.textFlags | kTextVCenter);
    }
    Text::pop();
}

// --- barras de desplazamiento (tipo 9) --------------------------------------------------------------------------

void SMenu::scrollThumbSize(SMenuItem& it, int* tw, int* th) {
    // FUN_0049ba80
    const Rect r = itemRect(it);
    *tw = *th = 0;
    const uint32_t kind = it.graphicKind();
    const bool horizontal = (it.flags & kItemFlagVertical) != 0;   // bit 0x40: horizontal
    const bool noThumb = (it.flags & 0x40000000u) != 0;
    if (kind == kGraphicPlain) {
        if (!horizontal) { *th = noThumb ? 0 : 0x14; *tw = r.width(); }
        else { *tw = noThumb ? 0 : 0x14; *th = r.height(); }
    } else if (kind == kGraphicImag) {
        if (noThumb) { if (!horizontal) *tw = r.width(); else *th = r.height(); }
        else graphicSize(it, 0, it.imageId + 2, 0, tw, th);
    }
}

void SMenu::scrollPartRect(SMenuItem& it, int part, Rect& out) {
    // FUN_0049bb73: 1 = boton inicial, 2 = boton final, 3 = pulgar, 4 = pista, 5 = pista antes, 6 = pista despues
    out = itemRect(it);
    const uint32_t kind = it.graphicKind();
    const bool horizontal = (it.flags & kItemFlagVertical) != 0;
    const bool noButtons = (it.flags & kItemFlagNoEndButtons) != 0;
    int bw = 0x14, bh = 0x14;
    if (kind == kGraphicImag) {
        int gw = 0, gh = 0;
        if (part == 1) { if (!noButtons && graphicSize(it, 0, it.imageId, 0, &gw, &gh)) { bw = gw; bh = gh; } else bw = bh = 0; }
        if (part == 2) { if (!noButtons && graphicSize(it, 0, it.imageId + 1, 0, &gw, &gh)) { bw = gw; bh = gh; } else bw = bh = 0; }
    } else if (noButtons) {
        bw = bh = 0;
    }
    Rect track, thumb;
    switch (part) {
        case 1:
            if (!horizontal) out.y1 = out.y0 + bh; else out.x1 = out.x0 + bw;
            break;
        case 2:
            if (!horizontal) out.y0 = out.y1 - bh; else out.x0 = out.x1 - bw;
            break;
        case 4: {
            Rect a, b;
            scrollPartRect(it, 1, a);
            scrollPartRect(it, 2, b);
            if (!horizontal) { out.y0 = a.y1; out.y1 = b.y0; } else { out.x0 = a.x1; out.x1 = b.x0; }
            break;
        }
        case 3: {
            scrollPartRect(it, 4, track);
            int tw = 0, th = 0;
            scrollThumbSize(it, &tw, &th);
            out = Rect{0, 0, tw, th};
            if (!horizontal) out.offset(track.x0 + div2(track.width() - tw), track.y0 + it.thumbPos);
            else out.offset(track.x0 + it.thumbPos, track.y0 + div2(track.height() - th));
            break;
        }
        case 5: {
            Rect a;
            scrollPartRect(it, 1, a);
            scrollPartRect(it, 3, thumb);
            if (!horizontal) { out.y0 = a.y1; out.y1 = thumb.y0; } else { out.x0 = a.x1; out.x1 = thumb.x0; }
            break;
        }
        case 6: {
            Rect b;
            scrollPartRect(it, 2, b);
            scrollPartRect(it, 3, thumb);
            if (!horizontal) { out.y0 = thumb.y1; out.y1 = b.y0; } else { out.x0 = thumb.x1; out.x1 = b.x0; }
            break;
        }
        default: break;
    }
}

void SMenu::scrollUpdateThumb(SMenuItem& it, bool redraw) {
    // FUN_0049c244
    Rect track;
    scrollPartRect(it, 4, track);
    int tw = 0, th = 0;
    scrollThumbSize(it, &tw, &th);
    const int old = it.thumbPos;
    it.thumbPos = 0;
    const bool horizontal = (it.flags & kItemFlagVertical) != 0;
    const int free = horizontal ? track.width() - tw : track.height() - th;
    const int range = std::abs(it.rangeMax - it.rangeMin);
    if (free > 0 && range != 0) it.thumbPos = std::abs(it.value - it.rangeMin) * free / range;
    if (redraw && old != it.thumbPos) invalidateItem(it);
}

int SMenu::scrollHitPart(SMenuItem& it, int px, int py) {
    // FUN_0049c45d
    for (int part : {1, 2, 3, 5, 6}) {
        Rect r;
        scrollPartRect(it, part, r);
        if (!r.empty() && r.contains(px, py)) return part;
    }
    return 0;
}

bool SMenu::scrollDragThumb(SMenuItem& it, int px, int py) {
    // FUN_0049c0e4 + FUN_0049c14c
    Rect track;
    scrollPartRect(it, 4, track);
    const bool horizontal = (it.flags & kItemFlagVertical) != 0;
    if (!horizontal) { if (px < track.x0 - 0x14 || px > track.x1 + 0x14) return false; }
    else { if (py < track.y0 - 0x14 || py > track.y1 + 0x14) return false; }
    int tw = 0, th = 0;
    scrollThumbSize(it, &tw, &th);
    int pos = it.thumbPos;
    if (!horizontal) {
        if (py > track.y0) pos = (py < track.y1 - th) ? py - track.y0 : (track.y1 - th) - track.y0;
        else pos = 0;
    } else {
        if (px > track.x0) pos = (px < track.x1 - tw) ? px - track.x0 : (track.x1 - tw) - track.x0;
        else pos = 0;
    }
    if (pos != it.thumbPos) {
        it.thumbPos = pos;
        invalidateItem(it);
    }
    return true;
}

int SMenu::scrollValueFromThumb(SMenuItem& it) {
    // FUN_0049c313
    if (it.rangeMax == it.rangeMin) return it.rangeMin;
    Rect track;
    scrollPartRect(it, 4, track);
    int tw = 0, th = 0;
    scrollThumbSize(it, &tw, &th);
    const bool horizontal = (it.flags & kItemFlagVertical) != 0;
    const int trackLen = horizontal ? track.width() : track.height();
    const int thumbLen = horizontal ? tw : th;
    if (it.thumbPos < 1) return it.rangeMin;
    if (it.thumbPos < trackLen - thumbLen) {
        const double v = double(it.thumbPos) * double(it.rangeMax - it.rangeMin) / double(trackLen - thumbLen);
        return int(std::lround(v)) + it.rangeMin;
    }
    return it.rangeMax;
}

void SMenu::scrollSetValue(SMenuItem& it, const ScrollInfo& si) {
    // FUN_0049b7f0
    bool changed = false;
    if ((si.mask & 2) && it.rangeMin != si.minValue) { it.rangeMin = si.minValue; changed = true; }
    if ((si.mask & 4) && it.rangeMax != si.maxValue) { it.rangeMax = si.maxValue; changed = true; }
    if ((si.mask & 1) && it.value != si.pos) { it.value = si.pos; changed = true; }
    if ((si.mask & 8) && it.pageSize != si.page) { it.pageSize = si.page; changed = true; }
    if (it.value < it.rangeMin) { it.value = it.rangeMin; changed = true; }
    if (it.value > it.rangeMax) { it.value = it.rangeMax; changed = true; }
    scrollUpdateThumb(it, false);
    if (changed) {
        invalidateItem(it);
        sendMessage(&it, kMsgSync, 0x32, nullptr);
    }
}

void SMenu::scrollByPart(SMenuItem& it, int part, uint32_t buttons) {
    // FUN_0049cc43
    int msg;
    switch (part) {
        case 1: msg = kMsgScrollLineUp; break;
        case 2: msg = kMsgScrollLineDown; break;
        case 5: msg = kMsgScrollPageUp; break;
        case 6: msg = kMsgScrollPageDown; break;
        default: msg = kMsgPress; break;
    }
    sendMessage(&it, msg, uint32_t(part), reinterpret_cast<void*>(uintptr_t(buttons & 0x20)));
}

void SMenu::drawScrollBar(SMenuItem& it) {
    // FUN_0049c710
    const int s = it.stateIndex();
    const Rect r = itemRect(it);
    const uint32_t kind = it.graphicKind();
    const bool trackFill = (it.flags & 0x20000000u) != 0;
    auto partState = [&](int part) { return (s == 1) ? (it.pressSub == part ? 1 : 0) : s; };
    auto button = [&](const Rect& b, int st) {   // FUN_0049c54a
        Pixel::fillRect(b.x0 + 1, b.y0 + 1, b.x1 - 1, b.y1 - 1, colors[kFill][st]);
        Pixel::fillRect(b.x0, b.y0, b.x1, b.y0 + 1, colors[kLight][st]);
        Pixel::fillRect(b.x0, b.y0, b.x0 + 1, b.y1 - 1, colors[kLight][st]);
        Pixel::fillRect(b.x0, b.y1 - 1, b.x1, b.y1, colors[kDark][st]);
        Pixel::fillRect(b.x1 - 1, b.y0 + 1, b.x1, b.y1, colors[kDark][st]);
    };
    auto arrow = [&](const Rect& b, int dir, int st) {   // FUN_0049c5e7: 0 arriba, 2 abajo, 1 izquierda, 3 derecha
        const ColorRef c = colors[kCheck][st];
        if (dir == 0 || dir == 2) {
            const int n = b.height() / 3;
            int yy = div2(b.height() - n) + b.y0;
            const int cx = div2(b.width()) + b.x0;
            int k = dir == 0 ? 0 : n - 1, step = dir == 0 ? 1 : -1;
            for (int i = 0; i < n; ++i, ++yy, k += step) Pixel::fillRect(cx - k, yy, cx + k + 1, yy + 1, c);
        } else {
            const int n = b.width() / 3;
            int xx = div2(b.width() - n) + b.x0;
            const int cy = div2(b.height()) + b.y0;
            int k = dir == 3 ? 0 : n - 1, step = dir == 3 ? 1 : -1;
            for (int i = 0; i < n; ++i, ++xx, k += step) Pixel::fillRect(xx, cy - k, xx + 1, cy + k + 1, c);
        }
    };
    const bool horizontal = (it.flags & kItemFlagVertical) != 0;
    Rect part;
    if (kind == kGraphicPlain) {
        const int s2 = s == 1 ? 0 : s;
        if (!trackFill) {
            Pixel::frameRect(r.x0, r.y0, r.x1, r.y1, colors[kDark][s2]);
        } else {
            scrollPartRect(it, 5, part);
            Pixel::fillRect(part, pick(it.colors[4][s2], colors[kDark][s2]));
        }
        scrollPartRect(it, 1, part);
        if (!part.empty()) { button(part, partState(1)); arrow(part, horizontal ? 1 : 0, partState(1)); }
        scrollPartRect(it, 2, part);
        if (!part.empty()) { button(part, partState(2)); arrow(part, horizontal ? 3 : 2, partState(2)); }
        scrollPartRect(it, 3, part);
        if (!part.empty()) button(part, partState(3));
    } else if (kind == kGraphicImag) {
        const int s2 = s == 1 ? 0 : s;
        if (trackFill) {
            scrollPartRect(it, 5, part);
            Pixel::fillRect(part, pick(it.colors[4][s2], colors[kDark][s2]));
        }
        for (int p = 1; p <= 3; ++p) {
            scrollPartRect(it, p, part);
            if (part.empty()) continue;
            const int st = partState(p);
            int gw = 0, gh = 0;
            const uint32_t img = it.imageId + uint32_t(p - 1);
            if (!graphicSize(it, st, img, 0, &gw, &gh)) continue;
            int oy = div2(part.height() - gh); if (oy < 0) oy = 0;
            int ox = div2(part.width() - gw); if (ox < 0) ox = 0;
            drawImagCell(it, r, (part.x0 - r.x0) + ox, (part.y0 - r.y0) + oy, st, img, 0);
        }
    }
}

// ---------------------------------------------------------------------------------------------------------------
// Mensajes

uint32_t SMenu::sendMessage(SMenuItem* it, int msg, uint32_t param, void* ptr) {
    if (!it) return 0;
    if (it->proc) return it->proc(*it, msg, param, ptr);
    return defaultProc(*it, msg, param, ptr);
}

void SMenu::playSound(SMenuItem& it, int kind) {
    // FUN_004a1555
    if (kind < 0 || kind > 2) return;
    int id = it.sounds[kind];
    if (id == -1) id = sounds[kind];
    if (id == -1) return;
    if (soundPlayer_) soundPlayer_(uint32_t(id));
}

int SMenu::gridSelect(SMenuItem& it, int from, int to, int mode) {
    // FUN_0049d5e9: 0 = seleccionar rango, 1 = deseleccionar rango, 2 = alternar rango, 3 = deseleccionar todo,
    // 4 = seleccionar todo, 5 = seleccionar rango y deseleccionar el resto
    for (int i = 0; i < int(it.cells.size()); ++i) {
        GridCell& c = it.cells[size_t(i)];
        const bool inRange = i >= from && i <= to;
        auto select = [&](bool on) {
            if (((c.flags & 1) != 0) == on) return;
            if (sendMessage(&it, kMsgCellSelecting, uint32_t(i))) {
                c.flags = (c.flags & ~1u) | (on ? 1u : 0u);
                sendMessage(&it, kMsgCellSelected, uint32_t(i), reinterpret_cast<void*>(uintptr_t(on)));
            }
            Rect r;
            if (subRect(it, i).empty()) {}
            invalidateItem(it);
        };
        switch (mode) {
            case 3: select(false); break;
            case 4: select(true); break;
            case 0: if (inRange) select(true); break;
            case 1: if (inRange) select(false); break;
            case 2: if (inRange) { if (sendMessage(&it, kMsgCellSelecting, uint32_t(i))) { c.flags ^= 1u; sendMessage(&it, kMsgCellSelected, uint32_t(i), reinterpret_cast<void*>(uintptr_t(c.flags & 1))); } invalidateItem(it); } break;
            case 5: select(inRange); break;
            default: break;
        }
    }
    return 1;
}

int SMenu::gridScrollTo(SMenuItem& it, int mode, int value) {
    // FUN_0049cf41: mode 1 = absoluto, 2 = relativo, 3 = paginas
    const int rh = int(sendMessage(&it, kMsgGetRowHeight));
    const int cols = int(sendMessage(&it, kMsgGetColumns));
    const int count = int(sendMessage(&it, kMsgGetCount));
    const Rect r = itemRect(it);
    int visible = rh > 0 ? (r.height() + rh - 1) / rh : 1;
    visible *= cols;
    if (mode == 3) value = value * visible + it.scrollTop;
    else if (mode == 2) value += it.scrollTop;
    if (count < visible + value) { mode = 1; value = count - visible; }
    if (value < 0) { mode = 1; value = 0; }
    if (mode == 1) {
        if (value != it.scrollTop) { it.scrollTop = value; invalidateItem(it); }
    } else if (value < it.scrollTop) {
        it.scrollTop = value;
        invalidateItem(it);
    } else if (it.scrollTop + visible <= value) {
        it.scrollTop = value - (visible - 1);
        invalidateItem(it);
    }
    sendMessage(&it, kMsgSync);
    return it.scrollTop;
}

void SMenu::syncLinked(SMenuItem& it, bool fromScroll) {
    // FUN_004a4156 / FUN_0049dc81 / FUN_0049b94f
    SMenuItem* other = it.linked;
    if (!other) return;
    if (it.type == kItemGrid && other->type == kItemScrollBar) {
        other->linked = nullptr;
        const int count = int(sendMessage(&it, kMsgGetCount));
        const int visible = int(sendMessage(&it, kMsgGetVisible));
        ScrollInfo si;
        if (!fromScroll) {
            sendMessage(other, kMsgGetScrollInfo, 0, &si);
            si.mask = 0xf;
            si.minValue = 0;
            si.maxValue = std::max(0, count - visible);
            si.pos = it.scrollTop;
            sendMessage(other, kMsgSetScrollInfo, 0, &si);
        } else {
            si.mask = 0xf;
            si.minValue = 0;
            si.maxValue = std::max(0, count - visible);
            si.page = 2;
            si.pos = 0;
            sendMessage(other, kMsgSetScrollInfo, 0, &si);
        }
        if (!other->linked) other->linked = &it;
    } else if (it.type == kItemScrollBar && other->type == kItemGrid) {
        other->linked = nullptr;
        if (!fromScroll) {
            ScrollInfo si;
            sendMessage(&it, kMsgGetScrollInfo, 0, &si);
            sendMessage(other, kMsgScrollTo, 1, reinterpret_cast<void*>(intptr_t(si.pos)));
        } else {
            const int count = int(sendMessage(other, kMsgGetCount));
            const int visible = int(sendMessage(other, kMsgGetVisible));
            ScrollInfo si;
            si.mask = 0xf;
            si.minValue = 0;
            si.maxValue = std::max(1, count - visible);
            si.page = 0;
            si.pos = 0;
            sendMessage(&it, kMsgSetScrollInfo, 0, &si);
        }
        if (!other->linked) other->linked = &it;
    }
}

uint32_t SMenu::defaultProc(SMenuItem& it, int msg, uint32_t param, void* ptr) {
    // FUN_004a43da
    switch (msg) {
        case kMsgGetRect:
            if (!ptr) return 0;
            *static_cast<Rect*>(ptr) = Rect::xywh(it.x, it.y, it.w, it.h);
            return 1;
        case kMsgDispose: disposeItem(it); return 1;
        case kMsgDraw: drawItemDefault(it); return 1;
        case kMsgSetProc: return 1;
        case kMsgInvalidate: invalidateItem(it); return 1;
        case kMsgSetHighlight: setHighlight(&it, int(reinterpret_cast<intptr_t>(ptr)), param != 0); return 1;
        case kMsgSetDisabled: setDisabled(&it, param != 0); return 1;
        case kMsgSetChecked: setChecked(&it, param != 0); return 1;
        case kMsgIsChecked: return it.isChecked() ? 1 : 0;
        case kMsgSetRect: {   // FUN_004a120c
            if (!ptr) return 0;
            const Rect& r = *static_cast<const Rect*>(ptr);
            invalidateItem(it);
            it.x = r.x0;
            it.y = r.y0;
            if (r.height() > 0) it.h = r.height();
            if (r.width() > 0) it.w = r.width();
            invalidateItem(it);
            return 1;
        }
        case kMsgGetText:
            if (!it.hasText) return 0;
            if (!ptr) return uint32_t(it.text.size());
            if (it.text.size() < param) { std::strcpy(static_cast<char*>(ptr), it.text.c_str()); return 1; }
            return 0;
        case kMsgSetText:
            it.text = ptr ? static_cast<const char*>(ptr) : "";
            it.hasText = ptr != nullptr;
            sendMessage(&it, kMsgSelectRange, 3);
            invalidateItem(it);
            return 1;
        case kMsgGetFont: if (!ptr) return 0; *static_cast<FontPtr*>(ptr) = it.font; return 1;
        case kMsgSetFont: return setAttribute(&it, 0x12, param) ? 1 : 0;
        case kMsgGetColors: {   // FUN_0049e971
            if (!ptr) return 0;
            uint32_t* arr = static_cast<uint32_t*>(ptr);
            const int set = param == 0 ? 4 : (param == 1 ? 5 : (param == 2 ? 0 : (param == 3 ? 1 : -1)));
            if (set < 0) return 0;
            for (uint32_t i = 0; i < arr[0]; ++i) arr[1 + i] = i < 3 ? it.colors[set][i] : 0x20000000u;
            return 1;
        }
        case kMsgSetColors: {   // FUN_0049e9e8
            if (!ptr) return 0;
            const uint32_t* arr = static_cast<const uint32_t*>(ptr);
            const int set = param == 0 ? 4 : (param == 1 ? 5 : (param == 2 ? 0 : (param == 3 ? 1 : -1)));
            if (set < 0) return 0;
            for (uint32_t i = 0; i < 3; ++i) {
                if (i < arr[0]) { if ((arr[1 + i] & 0x20000000u) == 0) it.colors[set][i] = arr[1 + i]; }
                else it.colors[set][i] = kColorNone;
            }
            return 1;
        }
        case kMsgGetTextFlags: return it.textFlags;
        case kMsgSetTextFlags: it.textFlags = param; return 1;
        case kMsgGetRowHeight: return it.type == kItemGrid ? uint32_t(gridRowHeight(it)) : 0;
        case kMsgGetCount: return it.type == kItemGrid ? uint32_t(it.cells.size()) : 0;
        case kMsgDrawCell: if (!ptr) return 0; drawGridCell(it, int(param), *static_cast<const Rect*>(ptr)); return 1;
        case kMsgGetColWidth: return uint32_t(gridColWidth(it));
        case kMsgGetColumns: return uint32_t(gridColumns(it));
        case kMsgSelect: case kMsgSelectRange: {   // FUN_0049edb2
            if (it.type == kItemText) {
                if (msg != kMsgSelectRange) return 0;
                // FUN_0049df38: param = (fin << 16) | inicio, ptr = modo (0/5 rango, 3 fin, 4 todo)
                if (!(it.flags & kItemFlagEdit)) return 0;
                textBlockFor(it);
                TextBlock& b = *it.textBlock;
                const int len = int(it.text.size());
                const int mode = int(reinterpret_cast<intptr_t>(ptr));
                const int a = int(param & 0xffff), e = int(param >> 16);
                if (mode == 0 || mode == 5) { b.selStart = std::clamp(a, 0, len); b.selEnd = std::clamp(e, 0, len); }
                else if (mode == 3) { b.selStart = b.selEnd = len; }
                else if (mode == 4) { b.selStart = 0; b.selEnd = len; }
                else return 1;
                invalidateItem(it);
                return 0;
            }
            if (it.type == kItemGrid) {
                if (msg == kMsgSelect) return uint32_t(gridSelect(it, int(param), int(param), 5));
                return uint32_t(gridSelect(it, int(param & 0xffff), int(param >> 16), int(reinterpret_cast<intptr_t>(ptr))));
            }
            return 0;
        }
        case kMsgGetSubRect: {   // FUN_0049ebfb
            if (!ptr) return 0;
            Rect& r = *static_cast<Rect*>(ptr);
            if (it.type == kItemListBox) { r = listRowRect(it, int(param)); return 1; }
            if (it.type == kItemGrid) {
                const int idx = int(param);
                const int count = int(sendMessage(&it, kMsgGetCount));
                if (idx < it.scrollTop || idx >= count) { r = Rect{}; return 0; }
                const int rh = int(sendMessage(&it, kMsgGetRowHeight));
                const int cw = int(sendMessage(&it, kMsgGetColWidth));
                const int cols = std::max(1, int(sendMessage(&it, kMsgGetColumns)));
                const int rel = idx - it.scrollTop;
                r.y0 = (rel / cols) * rh + it.y;
                r.x0 = (rel % cols) * cw + it.x;
                r.y1 = r.y0 + rh;
                r.x1 = r.x0 + cw;
                Rect bounds = Rect::xywh(it.x, it.y, it.w, it.h);
                return r.intersect(bounds) ? 1 : 0;
            }
            r = Rect{};
            return 0;
        }
        case kMsgGetSubState: {   // FUN_0049ee46 / FUN_0049d4ef
            if (it.type == kItemListBox || it.type != kItemGrid) return 2;
            if (it.stateIndex() == 2 || param >= it.cells.size()) return 2;
            const GridCell& c = it.cells[param];
            if (c.flags & 0xc) return 2;
            return (c.flags & 1) ? 1 : 0;
        }
        case kMsgScrollTo:
            if (it.type != kItemGrid) return 0;
            return uint32_t(gridScrollTo(it, int(param), int(reinterpret_cast<intptr_t>(ptr))));
        case kMsgNextSelected: {   // FUN_0049d54f
            int i = int(param);
            while (i < int(it.cells.size()) && !(it.cells[size_t(i)].flags & 1)) ++i;
            return uint32_t(i);
        }
        case kMsgSetCellText: case kMsgSetCellRect: case kMsgSetCellData: {   // FUN_0049d1dd
            if (it.type != kItemGrid || param >= it.cells.size()) return 0;
            GridCell& c = it.cells[param];
            if (msg == kMsgSetCellText) c.text = ptr ? static_cast<const char*>(ptr) : "";
            else if (msg == kMsgSetCellRect) { if (ptr) std::memcpy(&c.graphic, ptr, sizeof(c.graphic)); }
            else c.data = int(reinterpret_cast<intptr_t>(ptr));
            sendMessage(&it, kMsgSync);
            return 1;
        }
        case kMsgInsertCell: {   // FUN_0049ee8f / FUN_0049d105
            if (it.type != kItemGrid) return 0;
            const int at = int(param);
            GridCell c;
            c.text = ptr ? static_cast<const char*>(ptr) : "";
            int idx;
            if (at < 0 || at >= int(it.cells.size())) { it.cells.push_back(std::move(c)); idx = int(it.cells.size()); }
            else { it.cells.insert(it.cells.begin() + at, std::move(c)); idx = at + 1; }
            invalidateItem(it);
            sendMessage(&it, kMsgSync);
            return uint32_t(idx);
        }
        case kMsgDeleteCell:   // FUN_0049eef7 / FUN_0049d18d
            if (it.type != kItemGrid || param >= it.cells.size()) return 0;
            it.cells.erase(it.cells.begin() + std::ptrdiff_t(param));
            invalidateItem(it);
            sendMessage(&it, kMsgSync);
            return 1;
        case kMsgGetScrollInfo: {   // FUN_0049b90a
            if (it.type != kItemScrollBar || !ptr) return 0;
            ScrollInfo& si = *static_cast<ScrollInfo*>(ptr);
            si.minValue = it.rangeMin;
            si.maxValue = it.rangeMax;
            si.pos = it.value;
            si.page = it.pageSize;
            return 1;
        }
        case kMsgSetScrollInfo:
            if (it.type != kItemScrollBar || !ptr) return 0;
            scrollSetValue(it, *static_cast<const ScrollInfo*>(ptr));
            return 1;
        case kMsgScrollLineUp: case kMsgScrollLineDown: case kMsgScrollPageUp: case kMsgScrollPageDown: {   // FUN_0049cb2f
            if (it.type != kItemScrollBar) return 1;
            ScrollInfo si;
            sendMessage(&it, kMsgGetScrollInfo, 0, &si);
            si.mask = 1;
            if (msg == kMsgScrollLineUp) si.pos -= 1;
            else if (msg == kMsgScrollLineDown) si.pos += 1;
            else if (msg == kMsgScrollPageUp) si.pos -= si.page;
            else si.pos += si.page;
            scrollSetValue(it, si);
            sendMessage(&it, kMsgSync);
            return 1;
        }
        case kMsgScrollChanged: return 0;
        case kMsgFilterKey: {   // FUN_004a412b / FUN_0049deac
            if (it.type != kItemText) return param;
            const uint32_t k = param;
            if (k != kKeyDelete && k != kKeyLeft && k != kKeyRight && k != 8 && k != kKeyHome && k != kKeyEnd) {
                if (it.rangeMax > 0 && int(it.text.size()) >= it.rangeMax) return 0;
                if ((k & 0xffff) < 0x20 || (k & 0xffff) > 0x7e) return 0;
            }
            return k;
        }
        case kMsgLink: {   // 0x31
            if (it.linked) it.linked->linked = nullptr;
            it.linked = param == 2 ? static_cast<SMenuItem*>(ptr) : (param == 1 ? itemById(uint32_t(reinterpret_cast<uintptr_t>(ptr))) : itemByIndex(int(reinterpret_cast<intptr_t>(ptr))));
            if (it.linked) it.linked->linked = &it;
            sendMessage(&it, kMsgSync, 1);
            return 1;
        }
        case kMsgSync: syncLinked(it, param != 0); return 1;
        case kMsgGetVisible: return it.type == kItemGrid ? uint32_t(gridVisibleRows(it)) : 0;
        case kMsgSetFocus: {   // 0x34
            invalidateItem(it);
            it.state = (it.state & ~uint32_t(kStateFocus)) | (param ? kStateFocus : 0);
            if (it.type == kItemText) {
                // FUN_0049e2d5: modo 1 (foco) = cursor visible; modo 0 = oculto
                if (param) { it.caret &= 0x3fffffffu; it.animNext = InputQueue::instance().nowMs() + 1000; }
                else { it.caret = 0x80000000u; it.animNext = InputQueue::instance().nowMs() + 500; }
            }
            invalidateItem(it);
            return 0;
        }
        case kMsgGetCellText: case kMsgGetCellRect: case kMsgGetCellData: {   // FUN_0049d27f
            if (it.type != kItemGrid || param >= it.cells.size()) return 0;
            const GridCell& c = it.cells[param];
            if (msg == kMsgGetCellText) {
                if (!ptr) return uint32_t(c.text.size());
                std::strcpy(static_cast<char*>(ptr), c.text.c_str());
            } else if (msg == kMsgGetCellRect) { if (ptr) std::memcpy(ptr, &c.graphic, sizeof(c.graphic)); }
            else if (ptr) *static_cast<int*>(ptr) = c.data;
            return 1;
        }
        case kMsgGetTooltip:
            if (it.tooltip.empty() || !ptr || it.tooltip.size() >= param) return 0;
            std::strcpy(static_cast<char*>(ptr), it.tooltip.c_str());
            return 1;
        case kMsgSetTooltip: it.tooltip = ptr ? static_cast<const char*>(ptr) : ""; invalidateItem(it); return 1;
        case kMsgCellSelecting: case kMsgCellSelected: return 1;
        case kMsgShow: {   // 0x3c
            if (!ptr) it.visible += param ? 1 : -1;
            else if (param == 0) { if (it.visible != 0) --it.visible; }
            else if (it.visible == 0) ++it.visible;
            if (it.visible == 1 || it.visible == 0) {
                sendMessage(&it, kMsgSetDisabled, it.visible == 0 ? 1 : 0);
                invalidateItem(it);
            }
            return uint32_t(it.visible);
        }
        case kMsgPlaySound: playSound(it, int(param)); return 1;
        case kMsgSetSound: if (param < 3) it.sounds[param] = int(reinterpret_cast<intptr_t>(ptr)); return 0;
        case kMsgGetGraphicId: if (!ptr) return 0; *static_cast<uint32_t*>(ptr) = it.graphicId; return 1;
        case kMsgSetGraphic: {   // FUN_004a196e
            invalidateItem(it);
            it.graphic.reset();
            it.picture.reset();
            it.graphicId = 0;
            const bool ok = setAttribute(&it, 0xc, uint32_t(reinterpret_cast<uintptr_t>(ptr)));
            invalidateItem(it);
            return ok ? 1 : 0;
        }
        case kMsgGetImageIndex: if (!ptr) return 0; *static_cast<uint32_t*>(ptr) = it.imageId; return 1;
        case kMsgSetImageIndex: invalidateItem(it); it.imageId = uint32_t(reinterpret_cast<uintptr_t>(ptr)); invalidateItem(it); return 1;
        case kMsgGetFlags: if (!ptr) return 0; *static_cast<uint32_t*>(ptr) = it.flags; return 1;
        case kMsgSetGraphicKind:
            if ((it.flags & kItemFlagKindMask) != (param & kItemFlagKindMask)) {
                invalidateItem(it);
                it.graphic.reset();
                it.picture.reset();
                it.flags = (it.flags & ~uint32_t(kItemFlagKindMask)) | (param & kItemFlagKindMask);
            }
            return 1;
        case kMsgRelease: return 0;
        case kMsgSetNumber: {   // FUN_004a42f0
            char buf[32];
            const int v = int(param);
            const uint32_t f = uint32_t(reinterpret_cast<uintptr_t>(ptr));
            if (!(f & 4)) {
                if (!(f & 1)) std::snprintf(buf, sizeof buf, "%d", v);
                else if (v < 1 && ((f & 3) == 0 || v != 0)) std::snprintf(buf, sizeof buf, "%d", v);
                else std::snprintf(buf, sizeof buf, "+%d", v);
            } else if (v == 0 && (f & 3) == 0) std::snprintf(buf, sizeof buf, "%d", 0);
            else std::snprintf(buf, sizeof buf, "%d%%", v);
            it.text = buf;
            it.hasText = true;
            sendMessage(&it, kMsgSelectRange, 3);
            invalidateItem(it);
            return 1;
        }
        default: return 0;
    }
}

// ---------------------------------------------------------------------------------------------------------------
// Eventos

void SMenu::animate() {
    // FUN_004a26e8
    InputQueue& q = InputQueue::instance();
    for (auto& up : items_) {
        SMenuItem& it = *up;
        if (!(it.state & kStateAnimated)) {
            if (it.type == kItemText && (it.flags & kItemFlagEdit)) {
                // FUN_0049e2d5(item, 2): parpadeo del cursor
                if (it.animNext < q.nowMs()) {
                    it.caret ^= 0x40000000u;
                    it.animNext = q.nowMs() + ((it.caret & 0x40000000u) ? 500 : 1000);
                    invalidateItem(it);
                }
            }
            continue;
        }
        if (it.animNext < q.nowMs()) {
            it.animNext = q.nowMs() + uint32_t(it.animPeriod);
            if (it.proc && it.proc(it, kMsgAnimate, 0, nullptr)) continue;
            if (it.graphicKind() == kGraphicImag && it.graphic) {
                const ImagView iv = it.graphic->imag();
                const int ei = iv.findEntry(it.imageId, 0);
                if (ei >= 0) {
                    const ImagLayer L = iv.layer(ei, it.stateIndex());
                    if (L.cells) {
                        invalidateItem(it);
                        if (++it.frame >= L.cols) it.frame = 0;
                        invalidateItem(it);
                    }
                }
            }
        }
    }
}

SMenuItem* SMenu::findHotkey(uint32_t key) {
    // FUN_004a240f
    if (key == 0) return nullptr;
    for (auto& up : items_) {
        SMenuItem& it = *up;
        if (it.visible <= 0 || it.hotkey == 0 || (it.state & kStateDisabled)) continue;
        uint32_t mask = 0xffffffffu;
        const uint32_t k16 = it.hotkey & 0xffff;
        if (!(it.state & 0x40000u) && k16 > 0x20 && k16 < 0x100) mask = 0xfffbffffu;   // ignora shift en letras
        if ((mask & key) == it.hotkey) return &it;
    }
    return nullptr;
}

uint32_t SMenu::keyHookCall(int op, uint32_t key) {
    // FUN_004a2be7 / FUN_004a2ac6
    if (keyHook) return keyHook(*this, op, key);
    InputQueue& q = InputQueue::instance();
    if (op == 3) {
        if ((key & 0xffff) == 9) {   // Tab: siguiente / anterior enfocable
            SMenuItem* next = nextFocusable(focusedItem(), (key & kKeyModShift) != 0);
            if (next) {
                setFocus(next);
                if (next->type == kItemText) sendMessage(next, kMsgSelectRange, 0, reinterpret_cast<void*>(intptr_t(4)));
            }
            keyHookCall(1, 0);
            return 1;
        }
        return 0;
    }
    if (!(flags & kMenuRunLoop)) {
        if (op == 0) return q.peekKey();
        if (op == 1 || op == 2) return q.getKey();
        return 0;
    }
    if (op == 0) return keyPending;
    if (op == 1 || op == 2) keyPending = 0;
    return 0;
}

bool SMenu::editKey(SMenuItem& it, uint32_t rawKey) {
    // FUN_0049e007
    if (!(it.flags & kItemFlagEdit) || !it.hasFocus() || (it.state & kStateDisabled)) return false;
    textBlockFor(it);
    TextBlock& b = *it.textBlock;
    const uint32_t key = sendMessage(&it, kMsgFilterKey, rawKey);
    if (key == 0) return false;
    const bool shift = InputQueue::instance().shiftDown();
    const int len = int(it.text.size());
    auto clampSel = [&]() { b.selStart = std::clamp(b.selStart, 0, len); b.selEnd = std::clamp(b.selEnd, 0, len); };
    clampSel();
    switch (key & 0xffff) {
        case kKeyLeft:
            if (b.selEnd > 0) { b.selEnd--; if (!shift) b.selStart = b.selEnd; invalidateItem(it); }
            return true;
        case kKeyRight:
            if (b.selEnd < len) { b.selEnd++; if (!shift) b.selStart = b.selEnd; invalidateItem(it); }
            return true;
        case kKeyEnd: b.selEnd = len; if (!shift) b.selStart = b.selEnd; invalidateItem(it); return true;
        case kKeyHome: b.selEnd = 0; if (!shift) b.selStart = b.selEnd; invalidateItem(it); return true;
        case kKeyPageUp: case kKeyPageDown: case kKeyUp: case kKeyDown: return true;
        case 8: case kKeyDelete: {
            const int lo = std::min(b.selStart, b.selEnd), hi = std::max(b.selStart, b.selEnd);
            if (lo != hi) it.text.erase(size_t(lo), size_t(hi - lo));
            else if ((key & 0xffff) == 8) { if (lo > 0) it.text.erase(size_t(lo - 1), 1); else return true; }
            else { if (lo < len) it.text.erase(size_t(lo), 1); else return true; }
            b.selStart = b.selEnd = ((key & 0xffff) == 8 && lo == hi) ? lo - 1 : lo;
            invalidateItem(it);
            return true;
        }
        default: {
            const int lo = std::min(b.selStart, b.selEnd), hi = std::max(b.selStart, b.selEnd);
            if (lo != hi) it.text.erase(size_t(lo), size_t(hi - lo));
            it.text.insert(size_t(lo), 1, char(key & 0xff));
            it.hasText = true;
            b.selStart = b.selEnd = lo + 1;
            invalidateItem(it);
            return true;
        }
    }
}

bool SMenu::gridKey(SMenuItem& it, uint32_t key) {
    // FUN_0049cd32
    const int count = int(sendMessage(&it, kMsgGetCount));
    int cur = int(sendMessage(&it, kMsgNextSelected, 0));
    if (cur >= count) cur = -1;
    const uint32_t k = key & 0xffff;
    if (k >= 0x20 && k < 0x100) {
        // busqueda por primera letra a partir de la seleccion (dos vueltas)
        int start = cur + 1;
        for (int pass = 0; pass < 2; ++pass) {
            for (int i = start; i < count; ++i) {
                const std::string& t = it.cells[size_t(i)].text;
                if (!t.empty() && std::toupper(uint8_t(t[0])) == std::toupper(int(k))) {
                    sendMessage(&it, kMsgSelect, uint32_t(i));
                    sendMessage(&it, kMsgScrollTo, 0, reinterpret_cast<void*>(intptr_t(i)));
                    return true;
                }
            }
            start = 0;
        }
    }
    switch (k) {
        case kKeyPageUp: sendMessage(&it, kMsgScrollTo, 3, reinterpret_cast<void*>(intptr_t(-1))); sendMessage(&it, kMsgSelect, uint32_t(it.scrollTop)); return true;
        case kKeyPageDown: {
            sendMessage(&it, kMsgScrollTo, 3, reinterpret_cast<void*>(intptr_t(1)));
            int sel = int(sendMessage(&it, kMsgGetVisible)) + it.scrollTop - 1;
            if (sel >= count) sel = count - 1;
            if (sel < 0) sel = 0;
            sendMessage(&it, kMsgSelect, uint32_t(sel));
            return true;
        }
        case kKeyDown:
            if (cur < count - 1) { sendMessage(&it, kMsgSelect, uint32_t(cur + 1)); sendMessage(&it, kMsgScrollTo, 0, reinterpret_cast<void*>(intptr_t(cur + 1))); }
            return true;
        case kKeyUp:
            if (cur > 0) { sendMessage(&it, kMsgSelect, uint32_t(cur - 1)); sendMessage(&it, kMsgScrollTo, 0, reinterpret_cast<void*>(intptr_t(cur - 1))); }
            return true;
        case kKeyEnd: sendMessage(&it, kMsgScrollTo, 0, reinterpret_cast<void*>(intptr_t(0x7fff))); return true;
        case kKeyHome: sendMessage(&it, kMsgScrollTo, 0, reinterpret_cast<void*>(intptr_t(0))); return true;
        default: return false;
    }
}

bool SMenu::giveKeyToFocused(uint32_t key) {
    // FUN_004a2498
    SMenuItem* f = focusedItem();
    if (!f) return false;
    if (f->type == kItemText) return editKey(*f, key);
    if (f->type == kItemGrid) return gridKey(*f, key);
    return false;
}

void SMenu::sendSubIndex(SMenuItem& it, int sub) {
    // FUN_004a2238
    if (!(it.flags & 0x20u)) sendMessage(&it, kMsgSelect, uint32_t(sub));
    else sendMessage(&it, kMsgSelectRange, uint32_t(sub) | (uint32_t(sub) << 16), nullptr);
    sendMessage(&it, kMsgSync);
}

void SMenu::hoverSound(SMenuItem& it) {
    // FUN_004a2c32
    if (it.type == kItemScrollBar) return;
    const bool same = active == hover && pressSub == hoverSub;
    const bool hl = active && active->stateIndex() == 1;
    if (same && !hl) sendMessage(active, kMsgPlaySound, 0);
    else if (!same && hl) sendMessage(active, kMsgPlaySound, 1);
}

bool SMenu::itemStillHit(SMenuItem& it, int px, int py, const PressEvent& ev) {
    // FUN_004a2a27
    if (it.type == kItemScrollBar) {
        if (ev.sub == 3 || ((it.flags & 0x20000000u) && (ev.sub == 5 || ev.sub == 6))) {
            Rect track;
            scrollPartRect(it, 4, track);
            const bool horizontal = (it.flags & kItemFlagVertical) != 0;
            if (!horizontal) return px >= track.x0 - 0x14 && px <= track.x1 + 0x14;
            return py >= track.y0 - 0x14 && py <= track.y1 + 0x14;
        }
    }
    if ((it.state & (kStateDisabled | kStateStatic)) || it.visible <= 0) return false;
    return itemRect(it).contains(px, py);
}

void SMenu::pressItem(SMenuItem& it, PressEvent& ev) {
    // FUN_004a2847
    if (it.type == kItemText) {
        // FUN_0049e3d7: coloca el cursor / la seleccion en el caracter pulsado
        if ((it.flags & kItemFlagEdit) && it.hasFocus()) {
            textBlockFor(it);
            Text::push();
            if (selectFont(it)) {
                int idx = 0;
                if (Text::hitTest(*it.textBlock, ev.x, ev.y, &idx)) {
                    TextBlock& b = *it.textBlock;
                    if (!(ev.buttons & 0x20)) { if (b.selStart != idx) { b.selStart = idx; invalidateItem(it); } }
                    else if (b.selEnd != idx) { b.selEnd = idx; invalidateItem(it); }
                }
            }
            Text::pop();
        }
        if (!(ev.buttons & 0x20)) setFocus(&it);
        return;
    }
    if (it.type == kItemScrollBar) {
        if (!(ev.buttons & 0x20)) setFocus(&it);
        InputQueue& q = InputQueue::instance();
        if (ev.sub == 3) {
            scrollDragThumb(it, ev.x - ev.subX, ev.y - ev.subY);
            const int nv = scrollDragThumb(it, ev.x - ev.subX, ev.y - ev.subY) ? scrollValueFromThumb(it) : pressValue;
            if (nv != it.value) {
                const int old = it.value;
                it.value = nv;
                if (sendMessage(&it, kMsgScrollChanged, 0, reinterpret_cast<void*>(intptr_t(old)))) it.value = std::clamp(it.value, it.rangeMin, it.rangeMax);
            }
        } else if (!(it.flags & 0x20000000u) || (ev.sub != 5 && ev.sub != 6)) {
            const int period = it.animPeriod ? it.animPeriod : 10;
            if (!(ev.buttons & 0x20)) {
                it.animNext = q.ticks14() + uint32_t(period * 2);
                scrollByPart(it, ev.sub, ev.buttons);
            } else if (it.animNext <= q.ticks14()) {
                it.animNext = q.ticks14() + uint32_t(period);
                scrollByPart(it, ev.sub, ev.buttons);
            }
        } else {
            const int nv = scrollDragThumb(it, ev.x, ev.y) ? scrollValueFromThumb(it) : pressValue;
            if (nv != it.value) {
                const int old = it.value;
                it.value = nv;
                if (sendMessage(&it, kMsgScrollChanged, 0, reinterpret_cast<void*>(intptr_t(old)))) it.value = std::clamp(it.value, it.rangeMin, it.rangeMax);
            }
        }
        return;
    }
    if (!(ev.buttons & 0x20)) {
        sendMessage(&it, kMsgPress, 0, &ev);
        setFocus(&it);
    }
}

void SMenu::releaseItem(SMenuItem& it, const PressEvent& ev) {
    // FUN_004a2962
    if (it.type == kItemScrollBar) {
        if (ev.sub == 3 || ((it.flags & 0x20000000u) && (ev.sub == 5 || ev.sub == 6))) {
            scrollUpdateThumb(it, false);
            invalidateItem(it);
        }
        return;
    }
    sendMessage(&it, kMsgRelease, uint32_t(ev.sub), const_cast<PressEvent*>(&ev));
}

void SMenu::dragItem(SMenuItem& it, const PressEvent& ev) {
    // FUN_004a29cb (solo barras)
    if (it.type != kItemScrollBar) return;
    if (ev.sub == 3 || ((it.flags & 0x20000000u) && (ev.sub == 5 || ev.sub == 6))) {
        const int px = ev.sub == 3 ? ev.x - ev.subX : ev.x, py = ev.sub == 3 ? ev.y - ev.subY : ev.y;
        const int nv = scrollDragThumb(it, px, py) ? scrollValueFromThumb(it) : pressValue;
        if (nv != it.value) {
            const int old = it.value;
            it.value = nv;
            if (sendMessage(&it, kMsgScrollChanged, 0, reinterpret_cast<void*>(intptr_t(old)))) it.value = std::clamp(it.value, it.rangeMin, it.rangeMax);
        }
    }
}

bool SMenu::activateItem(SMenuItem& it, uint32_t) {
    // FUN_004a2376: devuelve true si el menu debe devolver el id del item
    if (it.state & kStateDisabled) return false;
    if (it.type == kItemCheckBox || it.type == kItemRadio) {
        sendMessage(&it, kMsgSetChecked, it.isChecked() ? 0 : 1);
        return (it.state & kStateReturnsId) != 0;
    }
    if (it.type == kItemListBox) {
        if (it.listSel != 0) it.param = uint32_t(it.listSel - 1);
        if (it.graphicKind() == kGraphicCombo) return it.listSel != 0;
        return (it.state & kStateReturnsId) != 0;
    }
    return (it.state & kStateReturnsId) != 0;
}

bool SMenu::process(uint32_t* hoverId) {
    // FUN_004a2cb5
    InputQueue& q = InputQueue::instance();
    if (hoverId) *hoverId = 0;
    if (flags & (kMenuDisabled | kMenuHidden)) return false;
    if (port) Pixel::pushPort(port);
    if (!initialized) {
        hoverSub = 0;
        clicked = keyActivated = pressed = hover = active = keyActivated = keyItem = nullptr;
        result_ = 0;
        if (!focusedItem() && !items_.empty()) setFocus(items_.front().get());
        initialized = true;
    }
    animate();
    int mx = 0, my = 0;
    q.mousePos(&mx, &my);
    if (!active) {
        hover = hitTest(mx, my, &hoverSub, nullptr, nullptr);
    } else {
        PressEvent ev{mx, my, pressSub, pressSubX, pressSubY, pressButtons};
        hover = itemStillHit(*active, mx, my, ev) ? active : nullptr;
    }
    if (hoverId) *hoverId = hover ? hover->id : 0;
    uint32_t buttons = 0;
    if (!pressed) {
        int bx = mx, by = my;
        buttons = uint32_t(q.buttonDown(3, &bx, &by, false));
        if (buttons == 0) {
            buttons = uint32_t(q.doubleClick(3, &bx, &by, false));
            if (buttons) buttons |= 0x10;
        }
        if (buttons != 0) {
            if (bx < x || bx >= x + w || by < y || by >= y + h) {
                buttons = 0;
            } else {
                if ((buttons & 3) == 3) buttons &= ~2u;
                if (buttons & 0x10) q.doubleClick(buttons & 3, &bx, &by, true);
                else q.buttonDown(buttons & 3, &bx, &by, true);
                SMenuItem* it = hitTest(bx, by, &pressSub, &pressSubX, &pressSubY);
                if (it && !(it->buttonMask & buttons)) it = nullptr;
                pressed = it;
                pressButtons = buttons;
                if (pressed) {
                    pressValue = pressed->value;
                    PressEvent ev{bx, by, pressSub, pressSubX, pressSubY, pressButtons};
                    pressItem(*pressed, ev);
                }
            }
        }
    } else {
        int bx = mx, by = my;
        if (q.buttonUp(pressButtons & 3, &bx, &by, true)) {
            if (hover && hover == pressed) {
                clicked = hover;
                if (clicked->state & kStateReturnsId) result_ = clicked->id;
            }
            PressEvent ev{bx, by, pressSub, pressSubX, pressSubY, pressButtons};
            releaseItem(*pressed, ev);
            pressed = nullptr;
        }
    }
    // Teclado
    if (!keyItem) {
        const uint32_t key = keyHookCall(0, 0);
        if (key != 0 && keyHookCall(3, key) == 0) {
            keyItem = findHotkey(key);
            if (!keyItem) {
                if (!giveKeyToFocused(key)) { if (!(flags & kMenuPassKeys)) keyHookCall(2, key); }
                else keyHookCall(2, key);
            } else {
                keyHookCall(1, key);
                buttons = 8;
            }
        }
    } else {
        keyActivated = keyItem;
        if (keyActivated->state & kStateReturnsId) result_ = keyActivated->id;
        keyItem = nullptr;
    }
    if (buttons == 0) {
        if (active) {
            if (!pressed) {
                if (clicked || keyActivated) {
                    setHighlight(active, pressSub, false);
                    sendMessage(active, kMsgPlaySound, 1);
                    if (active == clicked || active == keyActivated) {
                        if (activateItem(*active, 0) && result_ == 0) result_ = active->id;
                        if (result_ != 0) initialized = false;
                        else clicked = nullptr;
                        if (result_ != 0 && hoverId) *hoverId = result_;
                    }
                }
                active = nullptr;
                keyActivated = nullptr;
            } else {
                SMenuItem* target = active->type == kItemListBox ? active : hover;
                hoverSound(*active);
                const bool on = target == active && pressSub == hoverSub;
                setHighlight(active, pressSub, on);
                if (target == active) {
                    int sx = 0, sy = 0;
                    const int sub = subHitTest(*active, mx, my, &sx, &sy);
                    sendSubIndex(*active, sub);
                    PressEvent ev{mx, my, pressSub, pressSubX, pressSubY, pressButtons | 0x20};
                    pressItem(*active, ev);
                } else {
                    PressEvent ev{mx, my, pressSub, pressSubX, pressSubY, pressButtons};
                    dragItem(*active, ev);
                }
            }
        }
    } else {
        SMenuItem* it = pressed ? pressed : keyItem;
        if (active && it != active) {
            setHighlight(active, 0, false);
            sendMessage(active, kMsgPlaySound, 1);
        }
        active = it;
        setHighlight(active, pressSub, true);
        if (active) {
            int sx = 0, sy = 0;
            const int sub = subHitTest(*active, mx, my, &sx, &sy);
            sendSubIndex(*active, sub);
            sendMessage(active, kMsgPlaySound, 0);
        }
    }
    if (port) Pixel::popPort();
    return pressed != nullptr;
}

uint32_t SMenu::run(const std::function<bool()>& pump) {
    // FUN_004a32d7: modo bucle; pump() debe alimentar InputQueue, redibujar (redrawDirty) y presentar;
    // devuelve false para abortar.
    const uint32_t savedFlags = flags;
    flags |= kMenuRunLoop;
    result_ = 0;
    uint32_t id = 0;
    for (;;) {
        if (!pump()) break;
        InputQueue& q = InputQueue::instance();
        keyPending = q.peekKey();
        if (keyPending) q.getKey();
        uint32_t hoverId = 0;
        const bool held = process(&hoverId);
        redrawDirty();
        if (!held && result_ != 0 && !initialized) { id = result_; break; }
    }
    flags = savedFlags;
    return id;
}

}  // namespace dl2::engine
