// sprite_draw.h - 8 bpp sprite blitting with the clipping and hotspot semantics of DEADLOCK.EXE.
//
// Original functions:
//   FUN_00463d00 SetClipRect(x, y, w, h)     DAT_0058df34/38/3c/40 = clip rectangle (x0, y0, x1, y1)
//   FUN_00463da8 SelectSurface(index)        resets the clip rectangle to the whole surface
//   BlitSprite8 FUN_004647a0(buf, x, y, w, h, pitch, mode)   "Null Pointer in ClipBlit!"
//        mode 0 = colour-keyed (CYLib 8 bpp routine 0, key 255), mode 1 = opaque copy
//   DrawSpriteCentered FUN_004497ac          reads a SpriteDef from SPRITENW.DAT and blits it centred in a box
//   DrawSprite FUN_00444cf4                  screenX = (x >> 8) + def.hotX, screenY = (y >> 8) + def.hotY
//   FUN_0047f9a0 DrawTerrainTile             screen = tileX + hotX + 50, tileY + hotY + 50 (tile centre offset)
#pragma once
#include <cstdint>
#include <vector>

#include "sprites/sprite_bank.h"

namespace dl2 {
class Video;
}

namespace dl2::sprites {

enum class BlitMode : int { ColourKey = 0, Opaque = 1 };   // BlitSprite8 param_7

// A plain 8 bpp destination (used by the tools; Video is used by the game).
struct Surface8 {
    uint8_t* pixels = nullptr;
    int width = 0, height = 0, pitch = 0;
};

struct ClipRect {
    int x0 = 0, y0 = 0, x1 = 0, y1 = 0;   // half open, in destination pixels
};

// The clip rectangle is global in the original (one per selected surface); here it is a small object.
class Clipper {
public:
    explicit Clipper(int surfaceW = 640, int surfaceH = 480) { reset(surfaceW, surfaceH); }
    void reset(int surfaceW, int surfaceH);                 // FUN_00463da8
    void set(int x, int y, int w, int h);                   // FUN_00463d00 (clamped to the surface)
    const ClipRect& rect() const { return rect_; }
    int surfaceWidth() const { return surfW_; }
    int surfaceHeight() const { return surfH_; }

    // BlitSprite8 clipping: adjusts src/x/y/w/h in place, returns false when nothing is visible.
    bool clip(const uint8_t*& src, int& x, int& y, int& w, int& h, int pitch) const;

private:
    ClipRect rect_;
    int surfW_ = 640, surfH_ = 480;
};

// BlitSprite8 on an 8 bpp surface / on the Video framebuffer (via Video::blit8).
bool blitSprite8(Surface8& dst, const Clipper& clip, const uint8_t* src, int x, int y, int w, int h, int pitch,
                 BlitMode mode = BlitMode::ColourKey);
bool blitSprite8(Video& video, const Clipper& clip, const uint8_t* src, int x, int y, int w, int h, int pitch,
                 BlitMode mode = BlitMode::ColourKey);

// Draws a frame at (x, y) applying the hotspot: blit at (x + hotX, y + hotY).
bool drawSpriteDef(Surface8& dst, const Clipper& clip, const SpriteDef& def, const uint8_t* pixels, int x, int y,
                   BlitMode mode = BlitMode::ColourKey);
bool drawSpriteDef(Video& video, const Clipper& clip, const SpriteDef& def, const uint8_t* pixels, int x, int y,
                   BlitMode mode = BlitMode::ColourKey);
// Same for (type, frame) of the bank; loads the type on demand.
bool drawSprite(Surface8& dst, const Clipper& clip, SpriteBank& bank, int type, int frame, int x, int y,
                BlitMode mode = BlitMode::ColourKey);
bool drawSprite(Video& video, const Clipper& clip, SpriteBank& bank, int type, int frame, int x, int y,
                BlitMode mode = BlitMode::ColourKey);

// DrawSpriteCentered FUN_004497ac: the frame centred in the box (x, y, w, h) (no hotspot).
bool drawSpriteCentered(Video& video, const Clipper& clip, SpriteBank& bank, const SpriteDef& def, int x, int y,
                        int w, int h);

// FUN_0047f9a0 / FUN_0047f178 / DrawSTileBuilding: settlement tiles are drawn at tile origin + hotspot + 50.
constexpr int kTileHotspotOffset = 0x32;

}  // namespace dl2::sprites
