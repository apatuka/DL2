// Headless rendering/input integration. Original assets are strictly read-only.
#define SDL_MAIN_HANDLED
#include "app/world_inspector.h"
#include "engine/pixel.h"
#include "formats/hdx_archive.h"
#include "game/save_files.h"

#include <algorithm>
#include <chrono>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <memory>
#include <set>
#include <stdexcept>
#include <utility>
#include <vector>

namespace {
namespace fs = std::filesystem;
using namespace dl2;
using app::InspectorAction;
using app::InspectorSession;
using app::WorldInspector;
using worldview::ObjectKind;

void require(bool condition, const char* message) {
    if (!condition) throw std::runtime_error(message);
}

std::vector<uint8_t> bytes(const save::Document& document) {
    save::Error error;
    std::vector<uint8_t> output;
    if (!save::encode(document, output, error)) throw std::runtime_error(error.message);
    return output;
}

InputState key(SDL_Keycode code, uint16_t modifiers = 0) {
    InputState input;
    input.keys.push_back({code, SDL_SCANCODE_UNKNOWN, modifiers, true, false});
    return input;
}

InputState click(int x, int y) {
    InputState input;
    input.mouseX = x;
    input.mouseY = y;
    input.pressed = InputState::Left;
    return input;
}

void unchanged(const InspectorSession& session, const std::vector<uint8_t>& original) {
    require(session.document() && bytes(*session.document()) == original,
            "inspector navigation or rendering changed persistent document bytes");
}

void screenChecks(const WorldInspector& inspector) {
    const auto& screen = inspector.screen();
    require(screen.valid() && screen.width() == 640 && screen.height() == 480 &&
            screen.bpp() == 16 && screen.format() == engine::PixelFormat::Rgb555,
            "inspector screen must be 640x480 RGB555");
    const auto rgb = screen.toRgb555();
    const auto background = engine::rgbTo555(12, 20, 29);
    require(rgb.size() == 640 * 480 &&
            std::count_if(rgb.begin(), rgb.end(), [&](uint16_t p) { return p != background; }) > 1000,
            "inspector rendered an empty screen");
}

void spritePreviewCheck(const WorldInspector& inspector) {
    // The static preview box is separate from labels. A missing-sprite message
    // has one text colour; the original building/unit pixels have several.
    const auto rgb = inspector.screen().toRgb555();
    std::set<uint16_t> colors;
    for (int y = 252; y < 346; ++y)
        for (int x = 438; x < 626; ++x) colors.insert(rgb[size_t(y) * 640 + x]);
    require(colors.size() > 3, "original sprite preview was not rendered");
}

void realSave(WorldInspector& inspector, const fs::path& dataDirectory) {
    InspectorSession session;
    require(session.load(dataDirectory / "TUTORIAL.SAV"), "cannot load TUTORIAL.SAV");
    const auto& document = *session.document();
    const auto original = bytes(document);
    require(!document.buildings.empty() && !document.armies.empty(), "tutorial lacks preview objects");

    engine::OffPort priorPort;
    require(priorPort.create(16, 16, 16), "cannot create prior render target");
    auto* oldPort = engine::Pixel::setPort(&priorPort);
    const auto oldClip = engine::Pixel::clip();
    const auto oldMode = engine::Pixel::setBlitMode(engine::kBlit8to16);
    const auto oldPalette = engine::Text::palette();
    const auto priorPalette = std::make_shared<engine::ColorTable>(engine::ColorTable::identity());
    engine::Text::setPalette(priorPalette);
    const engine::Rect priorClip{2, 3, 12, 14};
    engine::Pixel::setClip(priorClip);
    inspector.draw(session);
    require(engine::Pixel::port() == &priorPort && engine::Pixel::clip().x0 == priorClip.x0 &&
            engine::Pixel::clip().y0 == priorClip.y0 && engine::Pixel::clip().x1 == priorClip.x1 &&
            engine::Pixel::clip().y1 == priorClip.y1 && engine::Pixel::blitMode() == engine::kBlit8to16,
            "inspector failed to restore the prior pixel target, clip or mode");
    require(engine::Text::palette() == priorPalette, "inspector failed to restore the prior text palette");
    engine::Text::setPalette(oldPalette);
    engine::Pixel::setPort(oldPort);
    engine::Pixel::setClip(oldClip);
    engine::Pixel::setBlitMode(oldMode);
    screenChecks(inspector);

    const auto& building = document.buildings.front();
    require(session.selection().selectObject(document, ObjectKind::Building, building.id),
            "cannot select tutorial building");
    inspector.draw(session);
    spritePreviewCheck(inspector);
    const auto& army = document.armies.front();
    require(session.selection().selectObject(document, ObjectKind::Army, army.id),
            "cannot select tutorial army");
    inspector.draw(session);
    spritePreviewCheck(inspector);

    const int initialSize = session.camera().tileSize();
    InputState wheel;
    wheel.wheel = 3;
    wheel.mouseX = 210;
    wheel.mouseY = 225;
    require(inspector.input(session, wheel) == InspectorAction::None &&
            session.camera().tileSize() > initialSize, "wheel zoom did not change tile size");
    const auto beforePan = session.camera().tileRect({0, 0});
    inspector.input(session, key(SDLK_RIGHT));
    inspector.input(session, key(SDLK_DOWN));
    const auto afterPan = session.camera().tileRect({0, 0});
    require(beforePan.x != afterPan.x || beforePan.y != afterPan.y, "arrow keys did not pan the zoomed view");
    inspector.draw(session);
    inspector.input(session, key(SDLK_MINUS));
    inspector.input(session, key(SDLK_PLUS));
    inspector.input(session, key(SDLK_f));
    require(session.camera().tileSize() == initialSize, "fit did not restore the fitted tile size");

    // Use a tile known to be visible at fit and ensure mouse hit-testing reaches
    // its persistent territory; follow-up object selection must preserve it.
    auto target = std::find_if(document.tiles.begin(), document.tiles.end(),
                              [](const Tile& tile) { return tile.territory > 0; });
    require(target != document.tiles.end(), "tutorial has no territory tiles");
    const auto rectangle = session.camera().tileRect({target->x, target->y});
    const auto mouse = click(rectangle.x + rectangle.w / 2, rectangle.y + rectangle.h / 2);
    const auto hit = session.camera().hitTest(mouse.mouseX, mouse.mouseY, document, InspectorSession::kMapViewport);
    require(hit && hit->x == target->x && hit->y == target->y, "camera hit test missed the visible tile");
    inspector.input(session, mouse);
    require(session.selection().selection().territory == uint32_t(target->territory) &&
            session.selection().selection().tile == hit, "map click did not select the expected tile and territory");

    const auto selectedTerritory = session.selection().selection().territory;
    inspector.input(session, key(SDLK_RIGHTBRACKET));
    require(session.selection().selection().territory == selectedTerritory % document.world.numTerritories + 1,
            "next-territory key did not advance");
    inspector.input(session, key(SDLK_LEFTBRACKET));
    require(session.selection().selection().territory == selectedTerritory, "previous-territory key did not restore selection");

    require(session.selection().selectObject(document, ObjectKind::Army, army.id), "cannot select army for cycling");
    const auto objects = worldview::objectsInTerritory(document, session.selection().selection().territory);
    require(objects.size() > 1, "tutorial needs multiple objects for cycling regression");
    const auto priorSelection = session.selection().selection();
    inspector.input(session, key(SDLK_TAB));
    require(session.selection().selection().objectId != priorSelection.objectId ||
            session.selection().selection().kind != priorSelection.kind, "Tab did not cycle objects");
    inspector.input(session, key(SDLK_TAB, KMOD_SHIFT));
    require(session.selection().selection().objectId == priorSelection.objectId &&
            session.selection().selection().kind == priorSelection.kind, "Shift+Tab did not reverse object cycling");

    inspector.draw(session);
    const auto terrainPixels = inspector.screen().toRgb555();
    const bool ownersBefore = inspector.ownerColors();
    inspector.input(session, key(SDLK_o));
    require(inspector.ownerColors() != ownersBefore, "owner-colour keyboard toggle failed");
    inspector.draw(session);
    require(inspector.screen().toRgb555() != terrainPixels, "owner-colour toggle did not affect rendering");
    inspector.input(session, click(80, 54));
    require(inspector.ownerColors() == ownersBefore, "owner-colour button toggle failed");

    require(inspector.input(session, key(SDLK_r)) == InspectorAction::Reload, "reload keyboard action");
    require(inspector.input(session, click(230, 54)) == InspectorAction::Reload, "reload button action");
    require(inspector.input(session, key(SDLK_F5)) == InspectorAction::SaveCopy, "save-copy keyboard action");
    require(inspector.input(session, click(310, 54)) == InspectorAction::SaveCopy, "save-copy button action");
    require(inspector.input(session, key(SDLK_ESCAPE)) == InspectorAction::Quit, "quit keyboard action");
    InputState quit; quit.quit = true;
    require(inspector.input(session, quit) == InspectorAction::Quit, "window quit action");
    unchanged(session, original);
}

void optionalCorpus(WorldInspector& inspector, const fs::path& dataDirectory) {
    std::set<int> renderedUnitTypes;
    size_t scenarios = 0, saves = 0;
    auto renderLoaded = [&](InspectorSession& session) {
        const auto& document = *session.document();
        const auto original = bytes(document);
        inspector.draw(session);
        screenChecks(inspector);
        if (!document.buildings.empty()) {
            require(session.selection().selectObject(document, ObjectKind::Building, document.buildings.front().id),
                    "cannot select first corpus building");
            inspector.draw(session);
        }
        // Render the first unit in every document and each additional unit type
        // once across the corpus, including mine portrait fallbacks when present.
        bool first = true;
        for (const auto& army : document.armies) {
            const bool newType = renderedUnitTypes.insert(army.type).second;
            if (!first && !newType) continue;
            first = false;
            require(session.selection().selectObject(document, ObjectKind::Army, army.id),
                    "cannot select corpus army");
            inspector.draw(session);
        }
        unchanged(session, original);
    };
    if (fs::is_regular_file(dataDirectory / "LEVELS.HDX") && fs::is_regular_file(dataDirectory / "LEVELS.HDD")) {
        HdxArchive archive;
        std::string error;
        if (!archive.open((dataDirectory / "LEVELS").string(), &error)) throw std::runtime_error(error);
        require(!archive.entries().empty(), "scenario archive has no entries");
        for (const auto& entry : archive.entries()) {
            InspectorSession session;
            if (!session.loadScenario(dataDirectory / "LEVELS", entry.name))
                throw std::runtime_error(entry.name + ": " + session.status());
            renderLoaded(session);
            ++scenarios;
        }
    }
    for (const auto* relative : {"Saves/AUTOSAVE.SAV", "Campaign/AUTOSAVE.CPN", "Campaign/ChCht001.CPN"}) {
        const auto path = dataDirectory / relative;
        if (!fs::is_regular_file(path)) continue;
        InspectorSession session;
        if (!session.load(path)) throw std::runtime_error(std::string(relative) + ": " + session.status());
        renderLoaded(session);
        ++saves;
    }
    std::cout << "world inspector optional corpus: " << scenarios << " scenarios, " << saves
              << " saves/campaigns, " << renderedUnitTypes.size() << " distinct unit previews\n";
}

struct Scratch {
    fs::path path;
    Scratch() {
        const auto parent = fs::current_path();
        const auto nonce = std::chrono::steady_clock::now().time_since_epoch().count();
        for (int attempt = 0; attempt < 100; ++attempt) {
            auto candidate = parent / ("inspector-render-test-" + std::to_string(nonce) + "-" + std::to_string(attempt));
            if (fs::create_directory(candidate)) { path = std::move(candidate); return; }
        }
        throw std::runtime_error("cannot create exclusive render-test directory");
    }
    ~Scratch() {
        // Remove only the two named files within our exclusively created child.
        if (path.empty()) return;
        std::error_code ignored;
        fs::remove(path / "paged.sav", ignored);
        fs::remove(path / "map.sav", ignored);
        fs::remove(path, ignored);
    }
};

void writeFixture(const fs::path& path, const save::Document& document) {
    save::Error error;
    if (!save::writeDocumentCopy(path, document, error)) throw std::runtime_error(error.message);
}

void pagedObjectsAndMap(WorldInspector& inspector, const fs::path& dataDirectory) {
    Scratch scratch;
    InspectorSession session;
    require(session.load(dataDirectory / "TUTORIAL.SAV"), "cannot reload tutorial fixture");
    auto paged = std::make_unique<save::Document>(*session.document());
    require(!paged->armies.empty(), "tutorial needs an army for paged fixture");
    const auto territory = paged->armies[0].territory.raw;
    int added = 0;
    for (uint16_t id = 60000; worldview::objectsInTerritory(*paged, territory).size() < 6; ++id) {
        require(id != 0, "cannot allocate unique fixture army ID");
        if (paged->buildingById(id) || paged->armyById(id)) continue;
        Army army{};
        army.id = id; army.type = added == 0 ? 37 : added == 1 ? 38 : 1;
        army.health = 100; army.owner = 0;
        army.territory.raw = army.dest.raw = army.origin.raw = territory;
        paged->armies.push_back(army);
        ++added;
    }
    writeFixture(scratch.path / "paged.sav", *paged);
    require(session.load(scratch.path / "paged.sav"), "cannot load paged fixture");
    const auto original = bytes(*session.document());
    const auto objects = worldview::objectsInTerritory(*session.document(), territory);
    require(objects.size() >= 6 && session.selection().selectObject(*session.document(), objects[3].kind, objects[3].id),
            "cannot select final object of first page");
    inspector.input(session, key(SDLK_TAB));
    require(session.selection().selection().objectId == objects[4].id &&
            session.selection().selection().kind == objects[4].kind, "Tab did not select second object page");
    inspector.draw(session);
    inspector.input(session, click(220, 408)); // Second row-column slot of page 2.
    require(session.selection().selection().objectId == objects[5].id &&
            session.selection().selection().kind == objects[5].kind, "click selected wrong object on second page");
    inspector.draw(session);
    screenChecks(inspector);
    for (const auto& army : session.document()->armies) {
        if (army.type != 37 && army.type != 38) continue;
        require(session.selection().selectObject(*session.document(), ObjectKind::Army, army.id),
                "cannot select fixture mine");
        inspector.draw(session);
        spritePreviewCheck(inspector);
    }
    unchanged(session, original);

    auto map = std::make_unique<save::Document>();
    std::memcpy(map->header.text, save::kHeaderText, sizeof(save::kHeaderText));
    map->header.version = kSaveVersion; map->header.isMap = 1; map->header.minusOne = -1;
    map->world.width = 3; map->world.height = 1; map->world.numTerritories = 2;
    map->mapTerritories.resize(2);
    std::memcpy(map->mapTerritories[0].name, "Map west", 9);
    std::memcpy(map->mapTerritories[1].name, "Map east", 9);
    map->mapTerritories[0].terrain = 1; map->mapTerritories[1].terrain = 4;
    map->tiles.resize(3);
    for (int x = 0; x < 3; ++x) {
        map->tiles[x].x = uint8_t(x);
        map->tiles[x].territory = int16_t(x == 2 ? 0 : x + 1);
    }
    map->trailing = {0xaa, 0, 0xff};
    writeFixture(scratch.path / "map.sav", *map);
    require(session.load(scratch.path / "map.sav"), "cannot load map fixture");
    const auto originalMap = bytes(*session.document());
    inspector.draw(session);
    screenChecks(inspector);
    require(session.selection().selection().kind == ObjectKind::None, "map invented a gameplay object");
    inspector.input(session, key(SDLK_TAB));
    inspector.input(session, key(SDLK_RIGHTBRACKET));
    require(session.selection().selection().territory == 2 &&
            session.selection().selection().kind == ObjectKind::None, "map navigation failed");
    const auto borderTile = session.camera().tileRect({2, 0});
    const auto borderClick = click(borderTile.x + borderTile.w / 2, borderTile.y + borderTile.h / 2);
    inspector.input(session, borderClick);
    require(session.selection().selection().territory == 0, "map border click did not select territory zero");
    inspector.input(session, key(SDLK_LEFTBRACKET));
    require(session.selection().selection().territory == 2, "previous territory from zero must select the final territory");
    inspector.input(session, borderClick);
    inspector.input(session, key(SDLK_RIGHTBRACKET));
    require(session.selection().selection().territory == 1, "next territory from zero must select the first territory");
    inspector.input(session, key(SDLK_o));
    inspector.draw(session);
    unchanged(session, originalMap);
}

} // namespace

int main(int argc, char** argv) {
    if (argc < 2 || !*argv[1]) {
        std::cout << "SKIP: original inspector assets unavailable; configure DL2_DATA_DIR.\n";
        return 77;
    }
    const fs::path dataDirectory(argv[1]);
    for (const auto* name : {"TUTORIAL.SAV", "deadtext.cam", "SPRITENW.DAT"}) {
        if (!fs::is_regular_file(dataDirectory / name)) {
            std::cout << "SKIP: missing inspector asset " << name << '\n';
            return 77;
        }
    }
    SDL_SetMainReady();
    if (SDL_Init(SDL_INIT_EVENTS) != 0) {
        std::cerr << "world inspector: SDL events init: " << SDL_GetError() << '\n';
        return 1;
    }
    int status = 1;
    try {
        WorldInspector inspector;
        std::string error;
        if (!inspector.initialize(dataDirectory, error)) throw std::runtime_error(error);
        InspectorSession empty;
        inspector.draw(empty);
        screenChecks(inspector);
        realSave(inspector, dataDirectory);
        pagedObjectsAndMap(inspector, dataDirectory);
        optionalCorpus(inspector, dataDirectory);
        std::cout << "world inspector: real fonts/sprites, RGB555 rendering, selection, navigation, pages, actions, map and immutable documents passed\n";
        status = 0;
    } catch (const std::exception& error) {
        std::cerr << "world inspector: " << error.what() << '\n';
    }
    engine::Pixel::setPort(nullptr);
    SDL_Quit();
    return status;
}
