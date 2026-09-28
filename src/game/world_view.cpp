#include "game/world_view.h"
#include "game/army_state.h"
#include "game/data_tables.h"

#include <algorithm>
#include <cmath>
#include <limits>

namespace dl2::worldview {
namespace {

bool validWorld(const save::Document& d) {
    return d.world.width > 0 && d.world.width <= kMapMaxSize &&
           d.world.height > 0 && d.world.height <= kMapMaxSize;
}

bool contains(Rect r, int x, int y) {
    return r.w > 0 && r.h > 0 && x >= r.x && y >= r.y &&
           int64_t(x) < int64_t(r.x) + r.w && int64_t(y) < int64_t(r.y) + r.h;
}

int narrow(int64_t v) {
    return int(std::clamp(v, int64_t(std::numeric_limits<int>::min()),
                            int64_t(std::numeric_limits<int>::max())));
}

int64_t clampAxis(int64_t origin, int start, int viewportSize, int mapSize) {
    if (mapSize <= viewportSize) return int64_t(start) + (viewportSize - mapSize) / 2;
    return std::clamp(origin, int64_t(start) + viewportSize - mapSize, int64_t(start));
}

bool hasTerritory(const save::Document& d, uint32_t index) {
    if (index == 0 || index > d.world.numTerritories) return false;
    return d.header.isMap == 1 ? index <= d.mapTerritories.size()
                               : d.territoryByIndex(index) != nullptr;
}

std::optional<TileCoord> firstTile(const save::Document& d, uint32_t territory) {
    if (!validWorld(d)) return {};
    for (int y = 0; y < d.world.height; ++y) {
        for (int x = 0; x < d.world.width; ++x) {
            const auto* tile = d.tileAt(uint32_t(x), uint32_t(y));
            if (tile && tile->territory == int(territory)) return TileCoord{x, y};
        }
    }
    return {};
}

} // namespace

void Camera::fit(const save::Document& d, Rect viewport) {
    originX_ = viewport.x;
    originY_ = viewport.y;
    tileSize_ = kMinTileSize;
    if (!validWorld(d) || viewport.w <= 0 || viewport.h <= 0) return;
    tileSize_ = std::clamp(std::min(viewport.w / d.world.width, viewport.h / d.world.height),
                           kMinTileSize, kMaxTileSize);
    clamp(d, viewport);
}

void Camera::clamp(const save::Document& d, Rect viewport) {
    if (!validWorld(d) || viewport.w <= 0 || viewport.h <= 0) {
        originX_ = viewport.x;
        originY_ = viewport.y;
        return;
    }
    originX_ = clampAxis(originX_, viewport.x, viewport.w, d.world.width * tileSize_);
    originY_ = clampAxis(originY_, viewport.y, viewport.h, d.world.height * tileSize_);
}

void Camera::pan(int dx, int dy, const save::Document& d, Rect viewport) {
    originX_ += dx;
    originY_ += dy;
    clamp(d, viewport);
}

void Camera::zoom(int steps, int anchorX, int anchorY, const save::Document& d, Rect viewport) {
    if (!validWorld(d) || viewport.w <= 0 || viewport.h <= 0 || steps == 0) return;
    if (!contains(viewport, anchorX, anchorY)) {
        anchorX = narrow(int64_t(viewport.x) + viewport.w / 2);
        anchorY = narrow(int64_t(viewport.y) + viewport.h / 2);
    }
    // Even a hostile wheel delta cannot overflow or make pow()/conversion huge.
    const double scale = std::pow(1.25, std::clamp(steps, -32, 32));
    int size = int(std::round(std::clamp(tileSize_ * scale, double(kMinTileSize),
                                       double(kMaxTileSize))));
    // At tiny sizes rounding would otherwise make a single wheel step inert.
    if (size == tileSize_) size = std::clamp(size + (steps > 0 ? 1 : -1),
                                            kMinTileSize, kMaxTileSize);
    const double ratio = double(size) / tileSize_;
    originX_ = int64_t(std::llround(anchorX - (double(anchorX) - originX_) * ratio));
    originY_ = int64_t(std::llround(anchorY - (double(anchorY) - originY_) * ratio));
    tileSize_ = size;
    clamp(d, viewport);
}

std::optional<TileCoord> Camera::hitTest(int x, int y, const save::Document& d, Rect viewport) const {
    if (!validWorld(d) || !contains(viewport, x, y)) return {};
    const int64_t localX = int64_t(x) - originX_;
    const int64_t localY = int64_t(y) - originY_;
    if (localX < 0 || localY < 0) return {};
    const int64_t tx = localX / tileSize_;
    const int64_t ty = localY / tileSize_;
    if (tx >= d.world.width || ty >= d.world.height || !d.tileAt(uint32_t(tx), uint32_t(ty))) return {};
    return TileCoord{int(tx), int(ty)};
}

Rect Camera::tileRect(TileCoord tile) const {
    return {narrow(originX_ + int64_t(tile.x) * tileSize_),
            narrow(originY_ + int64_t(tile.y) * tileSize_), tileSize_, tileSize_};
}

bool SelectionModel::selectTile(const save::Document& d, int x, int y) {
    if (x < 0 || y < 0) return false;
    const auto* tile = d.tileAt(uint32_t(x), uint32_t(y));
    if (!tile || tile->territory < 0 ||
        (tile->territory != 0 && !hasTerritory(d, uint32_t(tile->territory)))) return false;
    selection_ = {TileCoord{x, y}, uint32_t(tile->territory), ObjectKind::None, 0};
    return true;
}

bool SelectionModel::selectTerritory(const save::Document& d, uint32_t index) {
    if (!hasTerritory(d, index)) return false;
    auto tile = firstTile(d, index);
    if (selection_.tile) {
        const auto prior = *selection_.tile;
        const auto* record = d.tileAt(uint32_t(prior.x), uint32_t(prior.y));
        if (record && record->territory == int(index)) tile = prior;
    }
    selection_ = {tile, index, ObjectKind::None, 0};
    return true;
}

bool SelectionModel::selectObject(const save::Document& d, ObjectKind kind, uint32_t id) {
    if (d.header.isMap == 1 || id == 0) return false;
    uint32_t territory = 0;
    if (kind == ObjectKind::Building) {
        const auto* b = d.buildingById(id);
        if (!b || b->territory < 1) return false;
        territory = uint32_t(b->territory);
    } else if (kind == ObjectKind::Army) {
        const auto* a = d.armyById(id);
        if (!a) return false;
        territory = army::current(*a);
    } else return false;
    if (!selectTerritory(d, territory)) return false;
    selection_.kind = kind;
    selection_.objectId = id;
    return true;
}

std::vector<ObjectRef> objectsInTerritory(const save::Document& d, uint32_t index) {
    std::vector<ObjectRef> objects;
    if (d.header.isMap == 1 || !hasTerritory(d, index)) return objects;
    for (const auto& b : d.buildings)
        if (b.id && b.territory == int(index)) objects.push_back({ObjectKind::Building, b.id});
    for (const auto& a : d.armies)
        if (a.id && army::current(a) == index) objects.push_back({ObjectKind::Army, a.id});
    return objects;
}

bool SelectionModel::cycleObject(const save::Document& d, int step) {
    if (step == 0) return false;
    const auto objects = objectsInTerritory(d, selection_.territory);
    if (objects.empty()) {
        selection_.kind = ObjectKind::None;
        selection_.objectId = 0;
        return false;
    }
    const ObjectRef current{selection_.kind, selection_.objectId};
    const auto found = std::find(objects.begin(), objects.end(), current);
    const auto count = int64_t(objects.size());
    const int64_t position = found == objects.end() ? (step > 0 ? -1 : 0) : found - objects.begin();
    const size_t next = size_t(((position + step) % count + count) % count);
    return selectObject(d, objects[next].kind, objects[next].id);
}

std::string boundedText(const char* text, size_t capacity) {
    std::string result;
    if (!text) return result;
    for (size_t i = 0; i < capacity && text[i] != '\0'; ++i) {
        const auto byte = static_cast<unsigned char>(text[i]);
        result.push_back(byte >= 32 && byte <= 126 ? char(byte) : '?');
    }
    return result;
}

std::string territoryName(const save::Document& d, uint32_t index) {
    if (!hasTerritory(d, index)) return "No territory";
    const char* name = d.header.isMap == 1 ? d.mapTerritories[index - 1].name
                                          : d.territories[index - 1].data.name;
    auto result = boundedText(name, sizeof(Territory::name));
    return result.empty() ? "Territory " + std::to_string(index) : result;
}

std::string ownerName(const save::Document& d, int owner) {
    if (owner == -1) return "Unowned";
    if (owner < 0 || owner >= kMaxPlayers || d.header.isMap == 1) return "Unknown owner";
    const auto& player = d.players[size_t(owner)];
    auto result = boundedText(player.name, sizeof(player.name));
    return result.empty() ? "Player " + std::to_string(owner + 1) : result;
}

std::string terrainName(int terrain) {
    return terrain >= 0 && terrain < 6 ? data::kTerrainNames[terrain] : "Unknown terrain";
}

} // namespace dl2::worldview
