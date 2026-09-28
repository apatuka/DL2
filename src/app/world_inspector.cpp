#include "app/world_inspector.h"
#include "engine/pixel.h"
#include "game/army_state.h"
#include "game/data_tables.h"
#include "sprites/sprite_palette.h"

#include <algorithm>
#include <array>
#include <cstring>

namespace dl2::app {
using namespace engine;
using worldview::ObjectKind;
namespace {
constexpr auto bg = colorRgb(12, 20, 29), panel = colorRgb(22, 34, 45);
constexpr auto white = colorRgb(231, 237, 223), muted = colorRgb(151, 175, 182);
constexpr auto gold = colorRgb(245, 198, 95), border = colorRgb(57, 77, 83);
constexpr std::array<ColorRef, 6> terrains{
    colorRgb(34, 67, 94), colorRgb(123, 128, 70),
    colorRgb(50, 91, 63), colorRgb(76, 99, 89),
    colorRgb(124, 119, 116), colorRgb(156, 114, 80)};
constexpr std::array<ColorRef, 7> owners{
    colorRgb(165, 76, 72), colorRgb(89, 125, 190), colorRgb(170, 151, 76),
    colorRgb(142, 101, 173), colorRgb(76, 153, 140), colorRgb(172, 115, 71),
    colorRgb(101, 146, 80)};
constexpr Rect mapRect{8, 76, 418, 374};
constexpr std::array<Rect, 8> buttons{{
    {8, 44, 54, 66}, {60, 44, 134, 66}, {140, 44, 172, 66}, {178, 44, 210, 66},
    {216, 44, 282, 66}, {288, 44, 392, 66}, {432, 44, 478, 66}, {484, 44, 530, 66}}};
constexpr std::array<const char*, 8> buttonNames{
    "Fit", "Owners", "< T", "T >", "Reload", "Save copy", "< Obj", "Obj >"};

std::string number(int64_t n) { return std::to_string(n); }
std::string ascii(const std::string& s) { return worldview::boundedText(s.data(), s.size()); }
int terrain(const save::Document& d, int index) {
    if (index < 1 || index > d.world.numTerritories) return 0;
    if (d.header.isMap) return d.mapTerritories[size_t(index - 1)].terrain;
    return d.territories[size_t(index - 1)].data.terrain;
}
int owner(const save::Document& d, int index) {
    if (d.header.isMap || index < 1 || index > d.world.numTerritories) return -1;
    return d.territories[size_t(index - 1)].data.owner;
}
std::string objectName(const save::Document& d, worldview::ObjectRef ref) {
    if (ref.kind == ObjectKind::Building) {
        if (auto* b = d.buildingById(ref.id)) return "B " + number(b->id) + "  " + data::BuildingName(b->type);
    } else if (auto* a = d.armyById(ref.id)) {
        return "U " + number(a->id) + "  " + data::UnitName(a->type);
    }
    return "Unknown object";
}
size_t objectPage(const std::vector<worldview::ObjectRef>& objects, const worldview::Selection& s) {
    auto found = std::find(objects.begin(), objects.end(), worldview::ObjectRef{s.kind, s.objectId});
    return found == objects.end() ? 0 : size_t(found - objects.begin()) / 4;
}
Rect objectRow(size_t slot) {
    const int x = 8 + int(slot % 2) * 208, y = 402 + int(slot / 2) * 18;
    return {x, y, x + 202, y + 16};
}
}

bool WorldInspector::initialize(const std::filesystem::path& dir, std::string& error) {
    if (!resources_.addLibrary((dir / "deadtext.cam").string(), &error)) return false;
    smallFont_ = resources_.get(kTagFONT, makeTag("SM09"));
    titleFont_ = resources_.get(kTagFONT, makeTag("DL02"));
    if (!smallFont_ || !smallFont_->font || !titleFont_ || !titleFont_->font) {
        error = "Missing SM09 / DL02 fonts in deadtext.cam"; return false;
    }
    if (!sprites_.open((dir / "SPRITENW.DAT").string(), &error)) return false;
    uiPalette_ = std::make_shared<ColorTable>(ColorTable::identity());
    (*uiPalette_)[1] = {231, 237, 223, 0};
    (*uiPalette_)[2] = {151, 175, 182, 0};
    (*uiPalette_)[3] = {245, 198, 95, 0};
    (*uiPalette_)[4] = {242, 123, 110, 0};
    if (!screen_.create(640, 480, 16, PixelFormat::Rgb555)) { error = "Cannot create screen"; return false; }
    screen_.setPalette(uiPalette_);
    error.clear(); return true;
}

void WorldInspector::text(int x, int y, int width, const std::string& value, ColorRef color, bool title) {
    Text::setFont(title ? titleFont_->font : smallFont_->font);
    Text::setColor(color);
    std::string label = ascii(value);
    if (Text::textWidth(label.c_str()) > width) {
        while (!label.empty() && Text::textWidth((label + "...").c_str()) > width) label.pop_back();
        label += "...";
    }
    Pixel::pushClip(); Pixel::clipTo({x, y, x + width, y + (title ? 17 : 11)});
    Text::moveTo(x, y + Text::font()->ascent()); Text::drawString(label.c_str());
    Pixel::popClip();
}

InspectorAction WorldInspector::input(InspectorSession& session, const InputState& in) {
    if (in.quit || in.keyPressed(SDLK_ESCAPE)) return InspectorAction::Quit;
    if (in.keyPressed(SDLK_r)) return InspectorAction::Reload;
    if (in.keyPressed(SDLK_F5)) return InspectorAction::SaveCopy;
    const auto* d = session.document();
    if (!d) return InspectorAction::None;
    auto& selection = session.selection(); auto& camera = session.camera();
    if (in.keyPressed(SDLK_f)) session.fit();
    if (in.keyPressed(SDLK_o)) ownerColors_ = !ownerColors_;
    if (in.keyPressed(SDLK_TAB)) {
        const bool shift = std::any_of(in.keys.begin(), in.keys.end(), [](const KeyEvent& k) {
            return k.down && k.key == SDLK_TAB && (k.mod & KMOD_SHIFT); });
        selection.cycleObject(*d, shift ? -1 : 1);
    }
    auto nextTerritory = [&](int step) {
        const int n = d->world.numTerritories;
        const int current = int(selection.selection().territory);
        if (n) { selection.selectTerritory(*d, uint32_t(current == 0 ? (step < 0 ? n : 1) : (current - 1 + step + n) % n + 1));
                 selection.cycleObject(*d, 1); }
    };
    if (in.keyPressed(SDLK_LEFTBRACKET)) nextTerritory(-1);
    if (in.keyPressed(SDLK_RIGHTBRACKET)) nextTerritory(1);
    for (const auto& k : in.keys) if (k.down) {
        if (k.key == SDLK_LEFT) camera.pan(24, 0, *d, InspectorSession::kMapViewport);
        if (k.key == SDLK_RIGHT) camera.pan(-24, 0, *d, InspectorSession::kMapViewport);
        if (k.key == SDLK_UP) camera.pan(0, 24, *d, InspectorSession::kMapViewport);
        if (k.key == SDLK_DOWN) camera.pan(0, -24, *d, InspectorSession::kMapViewport);
        if (k.key == SDLK_EQUALS || k.key == SDLK_PLUS || k.key == SDLK_KP_PLUS)
            camera.zoom(1, 213, 225, *d, InspectorSession::kMapViewport);
        if (k.key == SDLK_MINUS || k.key == SDLK_KP_MINUS)
            camera.zoom(-1, 213, 225, *d, InspectorSession::kMapViewport);
    }
    if (in.wheel && mapRect.contains(in.mouseX, in.mouseY))
        camera.zoom(in.wheel, in.mouseX, in.mouseY, *d, InspectorSession::kMapViewport);
    if (!(in.pressed & InputState::Left)) return InspectorAction::None;
    for (size_t i = 0; i < buttons.size(); ++i) if (buttons[i].contains(in.mouseX, in.mouseY)) {
        switch (i) {
        case 0: session.fit(); break;
        case 1: ownerColors_ = !ownerColors_; break;
        case 2: nextTerritory(-1); break;
        case 3: nextTerritory(1); break;
        case 4: return InspectorAction::Reload;
        case 5: return InspectorAction::SaveCopy;
        case 6: selection.cycleObject(*d, -1); break;
        case 7: selection.cycleObject(*d, 1); break;
        }
        return InspectorAction::None;
    }
    if (auto t = camera.hitTest(in.mouseX, in.mouseY, *d, InspectorSession::kMapViewport)) {
        selection.selectTile(*d, t->x, t->y); selection.cycleObject(*d, 1);
    }
    const auto objects = worldview::objectsInTerritory(*d, selection.selection().territory);
    const auto start = objectPage(objects, selection.selection()) * 4;
    for (size_t i = 0; i < 4 && start + i < objects.size(); ++i)
        if (objectRow(i).contains(in.mouseX, in.mouseY))
            selection.selectObject(*d, objects[start + i].kind, objects[start + i].id);
    return InspectorAction::None;
}

void WorldInspector::preview(const save::Document& d, const worldview::Selection& s) {
    constexpr Rect box{438, 252, 626, 346};
    Pixel::fillRect(box, bg);
    int type = -1, index = 0;
    if (s.kind == ObjectKind::Building) {
        if (auto* b = d.buildingById(s.objectId)) {
            type = sprites::SpriteBank::buildingSpriteType(b->type, b->race);
            if ((b->flags & 4) && sprites::SpriteBank::frameCount(type) > 1) index = 1;
        }
    } else if (s.kind == ObjectKind::Army) {
        if (auto* a = d.armyById(s.objectId); a && a->type < data::kNumUnitTypes) {
            const int race = a->owner >= 0 && a->owner < kMaxPlayers ? d.players[a->owner].race : 0;
            if (a->type < 37) type = sprites::SpriteBank::unitSpriteType(a->type, race);
            if (type < 1) {
                const auto& def = data::kUnitTypes[a->type];
                type = def.portraitGroup + ((def.unitClass == 9 || def.unitClass == 10 || def.unitClass == 20) ? 0 : race);
                index = def.portraitIndex;
            }
        }
    }
    const auto frame = sprites_.frame(type, index);
    if (!frame.valid() || frame.def->w <= 0 || frame.def->h <= 0) {
        text(447, 291, 172, "No sprite preview", muted); return;
    }
    const auto pal = ColorTable::fromPalette(sprites::makeGamePalette(d.world.worldType));
    const auto* colors = pal.table16(PixelFormat::Rgb555);
    const double scale = std::min({1.0, double(box.width() - 8) / frame.def->w, double(box.height() - 8) / frame.def->h});
    const int w = std::max(1, int(frame.def->w * scale)), h = std::max(1, int(frame.def->h * scale));
    const int x0 = box.x0 + (box.width() - w) / 2, y0 = box.y0 + (box.height() - h) / 2;
    for (int y = 0; y < h; ++y) {
        auto* row = reinterpret_cast<uint16_t*>(screen_.pixelPtr(x0, y0 + y));
        for (int x = 0; x < w; ++x) {
            const auto c = frame.pixels[size_t(y * frame.def->h / h) * frame.def->w + size_t(x * frame.def->w / w)];
            if (c != 255) row[x] = colors[c];
        }
    }
}

void WorldInspector::draw(InspectorSession& session) {
    Pixel::pushPort(&screen_); Pixel::pushClip(); Pixel::resetClip();
    const auto oldMode = Pixel::setBlitMode(0);
    const auto oldPalette = Text::palette();
    Text::push(); Text::setPalette(uiPalette_); Text::setBackground(255);
    Text::setShadow(false); Text::setMode(0); Text::setSpacing(0, 0);
    screen_.clear(rgbTo555(12, 20, 29));
    text(8, 7, 405, "DEADLOCK II / WORLD INSPECTOR", white, true);
    text(432, 11, 200, "READ ONLY - NO TURN SIMULATION", gold);
    text(8, 29, 624, session.sourceLabel(), muted);
    for (size_t i = 0; i < buttons.size(); ++i) {
        const auto r = buttons[i]; Pixel::fillRect(r, panel);
        Pixel::frameRect(r.x0, r.y0, r.x1, r.y1, i == 1 && ownerColors_ ? gold : border);
        text(r.x0 + 6, r.y0 + 6, r.width() - 10, buttonNames[i], white);
    }
    text(540, 50, 92, "Drop SAV / CPN", muted);
    Pixel::fillRect(mapRect, colorRgb(6, 13, 20));
    Pixel::fillRect({432, 76, 632, 374}, panel);
    const auto* doc = session.document();
    if (doc) {
        const auto& d = *doc; const auto& s = session.selection().selection();
        auto& camera = session.camera();
        std::array<int, kMaxTerritories> count{}, sx{}, sy{}, buildings{}, units{};
        for (const auto& b : d.buildings) if (b.territory > 0 && b.territory < kMaxTerritories) ++buildings[b.territory];
        for (const auto& a : d.armies) if (army::current(a) < kMaxTerritories) ++units[army::current(a)];
        Pixel::pushClip(); Pixel::clipTo(mapRect);
        for (int y = 0; y < d.world.height; ++y) for (int x = 0; x < d.world.width; ++x) {
            const auto* tile = d.tileAt(uint32_t(x), uint32_t(y)); if (!tile) continue;
            const int id = tile->territory;
            const auto r = camera.tileRect({x, y});
            const int t = terrain(d, id), p = owner(d, id);
            const auto color = ownerColors_ && p >= 0 && p < kMaxPlayers ? owners[p] : terrains[size_t(std::clamp(t, 0, 5))];
            Pixel::fillRect(r.x, r.y, r.x + r.w, r.y + r.h, color);
            if (id > 0 && id < kMaxTerritories) { ++count[id]; sx[id] += x; sy[id] += y; }
            const auto edge = id > 0 && id == int(s.territory) ? gold : colorRgb(16, 28, 31);
            auto same = [&](int nx, int ny) { const auto* n = d.tileAt(uint32_t(nx), uint32_t(ny)); return n && n->territory == id; };
            if (!same(x - 1, y)) Pixel::line(r.x, r.y, r.x, r.y + r.h - 1, edge);
            if (!same(x + 1, y)) Pixel::line(r.x + r.w - 1, r.y, r.x + r.w - 1, r.y + r.h - 1, edge);
            if (!same(x, y - 1)) Pixel::line(r.x, r.y, r.x + r.w - 1, r.y, edge);
            if (!same(x, y + 1)) Pixel::line(r.x, r.y + r.h - 1, r.x + r.w - 1, r.y + r.h - 1, edge);
        }
        // Markers are territory aggregates, NOT invented building/unit positions.
        for (int id = 1; id <= d.world.numTerritories; ++id) if (count[id] && (buildings[id] || units[id])) {
            int best = 1000000, bx = 0, by = 0;
            for (int y = 0; y < d.world.height; ++y) for (int x = 0; x < d.world.width; ++x) {
                const auto* t = d.tileAt(uint32_t(x), uint32_t(y));
                if (!t || t->territory != id) continue;
                const int dx = x - sx[id] / count[id], dy = y - sy[id] / count[id], dist = dx * dx + dy * dy;
                if (dist < best) { best = dist; bx = x; by = y; }
            }
            const auto r = camera.tileRect({bx, by});
            const int x = r.x + r.w / 2, y = r.y + r.h / 2;
            Pixel::fillRect(x - 4, y - 4, x + 5, y + 5, bg);
            if (buildings[id]) Pixel::fillRect(x - 2, y - 2, x + 2, y + 2, white);
            if (units[id]) Pixel::line(x - 3, y + 3, x + 3, y + 3, gold);
        }
        if (s.tile) {
            const auto r = camera.tileRect(*s.tile);
            Pixel::frameRect(r.x, r.y, r.x + r.w, r.y + r.h, white);
        }
        Pixel::popClip();
        text(438, 82, 188, worldview::territoryName(d, s.territory), gold, true);
        text(438, 103, 188, "Territory " + number(s.territory) + " / " + number(d.world.numTerritories) + "  -  " + worldview::terrainName(terrain(d, int(s.territory))), muted);
        const auto* territory = d.territoryByIndex(s.territory);
        if (!d.header.isMap && territory) {
            const auto& t = territory->data;
            text(438, 118, 188, worldview::ownerName(d, t.owner), white);
            text(438, 132, 188, "Population " + number(t.population) + "   Morale " + number(t.morale), white);
            text(438, 146, 188, "Food " + number(t.materials[1]) + "   Energy " + number(t.materials[2]), white);
            text(438, 160, 188, "Buildings " + number(buildings[s.territory]) + "   Units " + number(units[s.territory]), muted);
        } else text(438, 124, 188, "Map data / no economy", muted);
        Pixel::line(438, 176, 626, 176, border);
        text(438, 184, 188, s.kind == ObjectKind::None ? "Select a territory / object" : objectName(d, {s.kind, s.objectId}), white);
        if (s.kind == ObjectKind::Building) {
            if (const auto* b = d.buildingById(s.objectId)) {
                text(438, 199, 188, "Site " + number(b->site) + "   Race " + number(b->race), muted);
                text(438, 213, 188, "Work remaining " + number(b->turnsLeft), white);
                text(438, 227, 188, std::string("Active ") + ((b->flags & 4) ? "yes" : "no") + "   Flags " + number(b->flags), muted);
            }
        } else if (s.kind == ObjectKind::Army) {
            if (const auto* a = d.armyById(s.objectId)) {
                text(438, 199, 188, worldview::boundedText(a->name, sizeof(a->name)), muted);
                text(438, 213, 188, "Retreat " + number(army::retreatThreshold(*a)) + "%   Moves " + number(army::movementPoints(*a)), white);
                text(438, 227, 188, "At " + number(army::current(*a)) + "   Start " + number(army::turnStart(*a)), muted);
            }
        }
        preview(d, s);
        text(438, 354, 188, "Original asset / static preview", muted);
        const auto objects = worldview::objectsInTerritory(d, s.territory);
        const size_t page = objectPage(objects, s), pages = std::max(size_t(1), (objects.size() + 3) / 4);
        text(8, 385, 412, "OBJECTS IN TERRITORY  " + number(objects.size()) + "   |   Page " + number(page + 1) + "/" + number(pages) + "   Tab: next", muted);
        for (size_t i = 0; i < 4 && page * 4 + i < objects.size(); ++i) {
            const auto ref = objects[page * 4 + i]; const auto row = objectRow(i);
            const bool selected = ref.kind == s.kind && ref.id == s.objectId;
            Pixel::fillRect(row, selected ? colorRgb(62, 60, 40) : panel);
            text(row.x0 + 4, row.y0 + 3, row.width() - 8, objectName(d, ref), selected ? gold : white);
        }
        text(432, 385, 200, "Turn " + number(d.options.turn) + "   Version " + number(d.header.version), white);
        text(432, 402, 200, "World " + number(d.world.width) + " x " + number(d.world.height) + "   All data visible", muted);
        text(432, 420, 200, "Square: buildings   Line: units", muted);
    } else text(24, 90, 378, "Drop a SAV / CPN file to inspect it", white, true);
    Pixel::frameRect(7, 75, 419, 375, border);
    Pixel::line(8, 443, 632, 443, border);
    text(8, 449, 624, session.status(), session.failed() ? colorRgb(242, 123, 110) : gold);
    text(8, 465, 624, "Click: select   Wheel/+/-: zoom   Arrows: pan   F: fit   O: owners   R: reload   F5: copy   Esc: quit", muted);
    Text::pop(); Text::setPalette(oldPalette);
    Pixel::setBlitMode(oldMode); Pixel::popClip(); Pixel::popPort();
}
} // namespace dl2::app
