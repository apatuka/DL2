// Read-only, headless inspector state. This is new UI support, not a port of
// original gameplay: no gs/gg activation, saved-pointer dereference or mutation.
#pragma once
#include <cstddef>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include "game/save_document.h"

namespace dl2::worldview {

struct TileCoord {
    int x = 0, y = 0;
    bool operator==(const TileCoord&) const = default;
};
struct Rect { int x = 0, y = 0, w = 0, h = 0; };

// Pixel-aligned rectangular overview, not the original isometric projection.
// Coordinates and viewport are half-open. Camera stores no Document references.
class Camera {
public:
    static constexpr int kMinTileSize = 2;
    static constexpr int kMaxTileSize = 96;
    void fit(const save::Document& document, Rect viewport);
    void pan(int dx, int dy, const save::Document& document, Rect viewport);
    void zoom(int steps, int anchorX, int anchorY,
              const save::Document& document, Rect viewport);
    std::optional<TileCoord> hitTest(int x, int y, const save::Document& document,
                                     Rect viewport) const;
    Rect tileRect(TileCoord tile) const;
    int tileSize() const { return tileSize_; }

private:
    void clamp(const save::Document& document, Rect viewport);
    int tileSize_ = kMinTileSize;
    int64_t originX_ = 0, originY_ = 0;
};

enum class ObjectKind { None, Building, Army };
struct ObjectRef {
    ObjectKind kind = ObjectKind::None;
    uint32_t id = 0;
    bool operator==(const ObjectRef&) const = default;
};
struct Selection {
    std::optional<TileCoord> tile;
    uint32_t territory = 0; // File index, 1-based. Zero means no territory.
    ObjectKind kind = ObjectKind::None;
    uint32_t objectId = 0; // Global file ID, never an array index/native pointer.
};

class SelectionModel {
public:
    void reset() { selection_ = {}; }
    bool selectTile(const save::Document& document, int x, int y);
    bool selectTerritory(const save::Document& document, uint32_t index);
    bool selectObject(const save::Document& document, ObjectKind kind, uint32_t id);
    // Buildings in file order, then armies whose current (+0x3c) territory
    // matches. Turn-start (+0x38) is not location; saved lists are not followed.
    bool cycleObject(const save::Document& document, int step);
    const Selection& selection() const { return selection_; }

private:
    Selection selection_;
};

std::vector<ObjectRef> objectsInTerritory(const save::Document& document, uint32_t index);
// Fixed-size saved text is not guaranteed to end in NUL. Replace control/high
// bytes with '?' for the inspector's ASCII font; never modify the document.
std::string boundedText(const char* text, size_t capacity);
std::string territoryName(const save::Document& document, uint32_t index);
std::string ownerName(const save::Document& document, int owner);
// Territory::terrain only; Tile::terrain is a DIFFERENT graphical enumeration.
std::string terrainName(int terrain);

} // namespace dl2::worldview
