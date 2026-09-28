// Headless, always-on assertions for new inspector support (not gameplay).
#include "game/world_view.h"

#include <algorithm>
#include <cstring>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>

namespace {
using namespace dl2;
using namespace dl2::worldview;

void require(bool condition, const char* message) {
    if (!condition) throw std::runtime_error(message);
}

std::unique_ptr<save::Document> fixture() {
    auto d = std::make_unique<save::Document>();
    std::memcpy(d->header.text, save::kHeaderText, sizeof(save::kHeaderText));
    d->header.version = kSaveVersion;
    d->header.minusOne = -1;
    d->options.numPlayers = 2;
    d->options.localPlayer = 0;
    d->world.width = 8;
    d->world.height = 6;
    d->world.numTerritories = 3;
    d->world.rngSeed = 0xabcdefu;
    d->players[0].race = 2;
    d->players[0].type = 1;
    std::memcpy(d->players[0].name, "Human colony", 13);
    for (auto& jobs : d->ministerJobs) jobs.resize(1);
    d->territories.resize(3);
    for (size_t i = 0; i < d->territories.size(); ++i) {
        auto& t = d->territories[i].data;
        t.index = uint16_t(i + 1);
        t.owner = i == 0 ? 0 : -1;
        t.terrain = uint8_t(i + 1);
    }
    std::memcpy(d->territories[0].data.name, "New Sol", 8);
    d->tiles.resize(48);
    for (int y = 0; y < 6; ++y) {
        for (int x = 0; x < 8; ++x) {
            auto& tile = d->tiles[size_t(y * 8 + x)];
            tile.x = uint8_t(x);
            tile.y = uint8_t(y);
            tile.territory = (x == 7 && y == 5) ? 0 : (x < 4 ? 1 : 2);
            tile.terrain = 6; // Graphic code: NOT the Territory terrain enum.
            if (tile.territory) {
                auto& t = d->territories[size_t(tile.territory - 1)].data;
                t.tiles[t.numTiles++].raw = uint32_t(x) | (uint32_t(y) << 16);
            }
        }
    }
    d->buildings.resize(3);
    const uint16_t ids[] = {200, 300, 100};
    for (size_t i = 0; i < d->buildings.size(); ++i) {
        auto& b = d->buildings[i];
        b.id = ids[i];
        b.type = uint8_t(i + 1);
        b.territory = i == 1 ? 2 : 1;
        b.site = i == 2 ? 1 : 0;
        d->territories[size_t(b.territory - 1)].data.sites[size_t(b.site)].building.raw = b.id;
    }
    d->armies.resize(2);
    for (size_t i = 0; i < d->armies.size(); ++i) {
        auto& a = d->armies[i];
        // ID 200 deliberately appears in both object kinds.
        a.id = i == 0 ? 200 : 600;
        a.type = 1;
        a.owner = 0;
        a.health = 100;
        a.territory.raw = uint32_t(i + 1);
        a.dest.raw = 2;
        a.origin.raw = 1;
    }
    return d;
}

void cameraTests(const save::Document& d) {
    Camera camera;
    const Rect viewport{8, 76, 410, 298};
    camera.fit(d, viewport);
    require(camera.tileSize() == 49, "fit chooses largest whole-pixel tile size");
    const Rect origin = camera.tileRect({0, 0});
    require(origin.x == 17 && origin.y == 78, "fit centers world on both axes");
    require(!camera.hitTest(origin.x - 1, origin.y, d, viewport), "left map margin is not tile zero");
    require(!camera.hitTest(origin.x, origin.y - 1, d, viewport), "top map margin is not tile zero");
    for (int y = 0; y < d.world.height; ++y) {
        for (int x = 0; x < d.world.width; ++x) {
            const Rect tile = camera.tileRect({x, y});
            const auto topLeft = camera.hitTest(tile.x, tile.y, d, viewport);
            const auto bottomRight = camera.hitTest(tile.x + tile.w - 1, tile.y + tile.h - 1, d, viewport);
            require(topLeft == TileCoord{x, y} && bottomRight == TileCoord{x, y},
                    "hitTest and tileRect agree on every edge pixel");
        }
    }
    require(!camera.hitTest(origin.x + 8 * 49, origin.y, d, viewport), "right map edge is exclusive");
    require(!camera.hitTest(origin.x, origin.y + 6 * 49, d, viewport), "bottom map edge is exclusive");
    require(!camera.hitTest(viewport.x + viewport.w, viewport.y, d, viewport), "right viewport edge is exclusive");
    require(!camera.hitTest(viewport.x, viewport.y + viewport.h, d, viewport), "bottom viewport edge is exclusive");

    camera.pan(1000, -1000, d, viewport);
    require(camera.tileRect({0, 0}).x == origin.x && camera.tileRect({0, 0}).y == origin.y,
            "pan leaves smaller centered map fixed");
    const Rect anchorTile = camera.tileRect({3, 2});
    const int anchorX = anchorTile.x + anchorTile.w / 2;
    const int anchorY = anchorTile.y + anchorTile.h / 2;
    camera.zoom(1, anchorX, anchorY, d, viewport);
    require(camera.tileSize() == 61, "zoom uses bounded integer scale");
    require(camera.hitTest(anchorX, anchorY, d, viewport) == TileCoord{3, 2}, "zoom preserves tile under anchor");
    camera.pan(std::numeric_limits<int>::max(), std::numeric_limits<int>::max(), d, viewport);
    require(camera.tileRect({0, 0}).x == viewport.x && camera.tileRect({0, 0}).y == viewport.y,
            "large positive pan clamps at map top-left");
    camera.pan(std::numeric_limits<int>::min(), std::numeric_limits<int>::min(), d, viewport);
    const Rect last = camera.tileRect({7, 5});
    require(last.x + last.w == viewport.x + viewport.w && last.y + last.h == viewport.y + viewport.h,
            "large negative pan clamps at map bottom-right");
    camera.zoom(std::numeric_limits<int>::max(), -100, -100, d, viewport);
    require(camera.tileSize() == Camera::kMaxTileSize, "huge zoom stops at upper bound");
    camera.zoom(std::numeric_limits<int>::min(), -100, -100, d, viewport);
    require(camera.tileSize() == Camera::kMinTileSize, "huge negative zoom stops at lower bound");
    camera.zoom(1, anchorX, anchorY, d, viewport);
    require(camera.tileSize() == 3, "single zoom step at minimum is not rounded away");
    camera.zoom(-1, anchorX, anchorY, d, viewport);
    require(camera.tileSize() == 2, "single negative step at tiny size is not rounded away");

    camera.fit(d, {1, 2, 0, 0});
    require(!camera.hitTest(1, 2, d, {1, 2, 0, 0}), "zero viewport cannot select");
    auto empty = std::make_unique<save::Document>();
    camera.fit(*empty, viewport);
    camera.zoom(1, 20, 80, *empty, viewport);
    camera.pan(3, 4, *empty, viewport);
    require(!camera.hitTest(20, 80, *empty, viewport), "empty document is safe");
    empty->world.width = 8;
    empty->world.height = 6;
    camera.fit(*empty, viewport);
    require(!camera.hitTest(20, 80, *empty, viewport), "missing tile vector cannot be hit");
    // Overflow-resistant arithmetic even for synthetic extreme screen coordinates.
    const Rect extreme{std::numeric_limits<int>::max() - 20,
                       std::numeric_limits<int>::min() + 20, 100, 100};
    camera.fit(d, extreme);
    camera.pan(std::numeric_limits<int>::max(), std::numeric_limits<int>::min(), d, extreme);
    camera.zoom(30, 0, 0, d, extreme);
    (void)camera.tileRect({std::numeric_limits<int>::max(), std::numeric_limits<int>::min()});
}

void selectionTests(const save::Document& d) {
    SelectionModel model;
    require(model.selection().territory == 0 && !model.selection().tile, "selection starts empty");
    require(model.selectTile(d, 3, 4), "select a dense row-major tile");
    require(model.selection().territory == 1 && model.selection().tile == TileCoord{3, 4}, "tile selects its territory");
    require(!model.selectTile(d, -1, 0) && !model.selectTile(d, 8, 0) && !model.selectTile(d, 0, 6),
            "invalid tile coordinates rejected");
    require(model.selection().tile == TileCoord{3, 4}, "failed selection preserves prior state");
    require(model.selectTerritory(d, 1) && model.selection().tile == TileCoord{3, 4},
            "territory reselect preserves matching tile");
    const auto objects = objectsInTerritory(d, 1);
    require(objects == std::vector<ObjectRef>{{ObjectKind::Building, 200}, {ObjectKind::Building, 100},
                                             {ObjectKind::Army, 200}},
            "objects use file order and separate ID domains");
    require(objectsInTerritory(d, 2).size() == 2, "transit army is not duplicated at destination");
    require(objectsInTerritory(d, 0).empty() && objectsInTerritory(d, 4).empty(), "invalid territory has no objects");
    require(!model.cycleObject(d, 0), "zero cycle is a no-op");
    require(model.cycleObject(d, 1) && model.selection().objectId == 200 && model.selection().kind == ObjectKind::Building,
            "first forward cycle selects first building");
    require(model.cycleObject(d, 1) && model.selection().objectId == 100, "second cycle follows file order");
    require(model.cycleObject(d, 1) && model.selection().objectId == 200 && model.selection().kind == ObjectKind::Army,
            "third cycle selects army even with same numeric building ID");
    require(model.cycleObject(d, 1) && model.selection().kind == ObjectKind::Building, "forward cycle wraps");
    require(model.cycleObject(d, -1) && model.selection().kind == ObjectKind::Army, "backward cycle wraps");
    require(model.cycleObject(d, std::numeric_limits<int>::min()), "large negative cycle remains valid");
    require(model.selectObject(d, ObjectKind::Army, 600) && model.selection().territory == 2,
            "direct object selection changes to its actual territory");
    require(model.selection().tile == TileCoord{4, 0}, "new territory anchors at first dense tile");
    require(!model.selectObject(d, ObjectKind::None, 600) && !model.selectObject(d, ObjectKind::Army, 999) &&
            !model.selectObject(d, ObjectKind::Building, 0), "invalid object selections rejected");
    require(model.selection().objectId == 600, "failed object selection preserves state");
    require(model.selectTerritory(d, 3) && !model.selection().tile, "territory without tiles is inspectable");
    require(!model.cycleObject(d, 1) && model.selection().objectId == 0, "empty territory has no stale object");
    require(!model.selectTerritory(d, 0) && !model.selectTerritory(d, 4), "invalid territories rejected");
    require(model.selectTile(d, 7, 5) && model.selection().territory == 0, "unassigned tile is selectable");
    require(!model.cycleObject(d, -1), "unassigned tile has no objects");
    model.reset();
    require(model.selection().territory == 0 && !model.selection().tile && model.selection().kind == ObjectKind::None,
            "reset clears all state");
}

void textAndMapTests(const save::Document& d) {
    require(boundedText(nullptr, 100).empty(), "null text is safe");
    const char text[] = {'N', 'o', 'N', 'u', 'l'};
    require(boundedText(text, sizeof(text)) == "NoNul", "fixed strings do not need NUL");
    const char opaque[] = {'a', '\n', char(0xff), '\0', 'z'};
    require(boundedText(opaque, sizeof(opaque)) == "a??", "control and non-ASCII bytes sanitized and NUL bounded");
    require(boundedText(text, 0).empty(), "zero capacity reads no bytes");
    require(territoryName(d, 1) == "New Sol" && territoryName(d, 2) == "Territory 2", "territory names and fallback");
    require(territoryName(d, 0) == "No territory", "invalid territory name fallback");
    require(ownerName(d, 0) == "Human colony" && ownerName(d, 1) == "Player 2", "bounded owner names");
    require(ownerName(d, -1) == "Unowned" && ownerName(d, 7) == "Unknown owner", "owner sentinel and bounds");
    require(terrainName(1) == "Plains" && terrainName(6) == "Unknown terrain", "only territory terrain uses name enum");

    auto map = std::make_unique<save::Document>(d);
    map->header.isMap = 1;
    map->mapTerritories.resize(3);
    map->territories.clear();
    std::memcpy(map->mapTerritories[0].name, "Map region", 11);
    SelectionModel model;
    require(model.selectTile(*map, 0, 0) && model.selection().territory == 1, "map selects reduced territory");
    require(territoryName(*map, 1) == "Map region", "map gets name from reduced record");
    require(objectsInTerritory(*map, 1).empty(), "map never exposes irrelevant live-style objects");
    require(!model.selectObject(*map, ObjectKind::Building, 200), "map object selection rejected");

    auto changed = std::make_unique<save::Document>(d);
    require(model.selectObject(d, ObjectKind::Building, 200), "choose object in first document");
    // No cached addresses: reallocation and replacement are safe with same IDs.
    changed->buildings.reserve(100);
    changed->territories.reserve(100);
    require(model.selectObject(*changed, ObjectKind::Army, 600), "selection resolves IDs against supplied document");
    changed->armies[1].territory.raw = 999;
    require(!model.selectObject(*changed, ObjectKind::Army, 600), "dangling object territory is rejected");
    changed->tiles[0].territory = -1;
    require(!model.selectTile(*changed, 0, 0), "malformed negative territory rejected");
    // Inspector walks owning arrays, not opaque saved linked-list words.
    changed->territories[0].data.armies.raw = 0xffffffffu;
    changed->armies[0].next.raw = 0xffffffffu;
    require(objectsInTerritory(*changed, 1).size() == 3, "opaque linked-list values are never dereferenced");
}

} // namespace

int main() {
    try {
        auto document = fixture();
        save::Error error;
        std::vector<uint8_t> before, after;
        require(save::encode(*document, before, error), "fixture is a valid encodable save");
        cameraTests(*document);
        selectionTests(*document);
        textAndMapTests(*document);
        require(save::encode(*document, after, error), "inspection preserves validity");
        require(before == after, "all inspector operations leave save bytes identical");
        std::cout << "world_view: camera, selection, transit IDs, text, maps and read-only checks passed\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "world_view: " << error.what() << '\n';
        return 1;
    }
}
