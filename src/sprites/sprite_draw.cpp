// sprite_draw.cpp - see sprite_draw.h
#include "sprites/sprite_draw.h"

#include <algorithm>
#include <cstring>

#include "platform/sdl_video.h"
#include "sprites/sprite_palette.h"

namespace dl2::sprites {

void Clipper::reset(int surfaceW, int surfaceH) {   // FUN_00463da8 -> FUN_00463d00(0, 0, w, h)
    surfW_ = surfaceW;
    surfH_ = surfaceH;
    set(0, 0, surfaceW, surfaceH);
}

void Clipper::set(int x, int y, int w, int h) {   // FUN_00463d00
    rect_.x0 = std::max(x, 0);
    rect_.x1 = std::min(x + w, surfW_);
    rect_.y0 = std::max(y, 0);
    rect_.y1 = std::min(y + h, surfH_);
}

bool Clipper::clip(const uint8_t*& src, int& x, int& y, int& w, int& h, int pitch) const {   // BlitSprite8
    if (!src) return false;
    if (y < rect_.y0) {
        src += size_t(rect_.y0 - y) * size_t(pitch);
        h -= rect_.y0 - y;
        y = rect_.y0;
    }
    if (x < rect_.x0) {
        src += rect_.x0 - x;
        w -= rect_.x0 - x;
        x = rect_.x0;
    }
    if (!(x < rect_.x1 && y < rect_.y1 && w > 0 && h > 0)) return false;
    if (rect_.x1 < x + w) w = rect_.x1 - x;
    if (rect_.y1 < y + h) h = rect_.y1 - y;
    return w >= 0 && h >= 0;
}

bool blitSprite8(Surface8& dst, const Clipper& clip, const uint8_t* src, int x, int y, int w, int h, int pitch,
                 BlitMode mode) {
    if (!src || !dst.pixels) return false;   // "Null Pointer in ClipBlit!"
    if (!clip.clip(src, x, y, w, h, pitch)) return false;
    // Also stay inside the surface (the clip rectangle is already clamped, this only guards bad callers).
    if (x + w > dst.width) w = dst.width - x;
    if (y + h > dst.height) h = dst.height - y;
    if (w <= 0 || h <= 0) return false;
    for (int row = 0; row < h; ++row) {
        const uint8_t* s = src + size_t(row) * size_t(pitch);
        uint8_t* d = dst.pixels + size_t(y + row) * size_t(dst.pitch) + x;
        if (mode == BlitMode::Opaque) {
            std::memcpy(d, s, size_t(w));
        } else {
            for (int i = 0; i < w; ++i)
                if (s[i] != uint8_t(kColourKeyIndex)) d[i] = s[i];
        }
    }
    return true;
}

bool blitSprite8(Video& video, const Clipper& clip, const uint8_t* src, int x, int y, int w, int h, int pitch,
                 BlitMode mode) {
    if (!src) return false;
    if (!clip.clip(src, x, y, w, h, pitch)) return false;
    if (w <= 0 || h <= 0) return false;
    video.blit8(src, w, h, pitch, x, y, mode == BlitMode::ColourKey ? kColourKeyIndex : -1);
    return true;
}

bool drawSpriteDef(Surface8& dst, const Clipper& clip, const SpriteDef& def, const uint8_t* pixels, int x, int y,
                   BlitMode mode) {
    return blitSprite8(dst, clip, pixels, x + def.hotX, y + def.hotY, def.w, def.h, def.w, mode);
}

bool drawSpriteDef(Video& video, const Clipper& clip, const SpriteDef& def, const uint8_t* pixels, int x, int y,
                   BlitMode mode) {
    return blitSprite8(video, clip, pixels, x + def.hotX, y + def.hotY, def.w, def.h, def.w, mode);
}

bool drawSprite(Surface8& dst, const Clipper& clip, SpriteBank& bank, int type, int frame, int x, int y,
                BlitMode mode) {
    const SpriteFrame f = bank.frame(type, frame);
    if (!f.valid()) return false;
    return drawSpriteDef(dst, clip, *f.def, f.pixels, x, y, mode);
}

bool drawSprite(Video& video, const Clipper& clip, SpriteBank& bank, int type, int frame, int x, int y,
                BlitMode mode) {
    const SpriteFrame f = bank.frame(type, frame);
    if (!f.valid()) return false;
    return drawSpriteDef(video, clip, *f.def, f.pixels, x, y, mode);
}

bool drawSpriteCentered(Video& video, const Clipper& clip, SpriteBank& bank, const SpriteDef& def, int x, int y,
                        int w, int h) {   // DrawSpriteCentered FUN_004497ac
    std::vector<uint8_t> buf;
    if (!bank.readPixels(def, buf, false)) return false;   // ReadDataFileChunk: still pictures are not remapped
    const int dx = (w - def.w) / 2, dy = (h - def.h) / 2;   // C division truncates toward zero as the original
    return blitSprite8(video, clip, buf.data(), x + dx, y + dy, def.w, def.h, def.w, BlitMode::ColourKey);
}

}  // namespace dl2::sprites
