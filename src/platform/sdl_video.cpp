// sdl_video.cpp - SDL2 window/renderer management, clipped 8-bit and 16-bit blits, palette conversion and presentation.
#include "platform/sdl_video.h"

#include <algorithm>
#include <cstring>

#include "formats/iff_pbm.h"

namespace dl2 {

namespace {

inline uint32_t argb(Rgb c) { return 0xFF000000u | (uint32_t(c.r) << 16) | (uint32_t(c.g) << 8) | c.b; }

// Clips a blit rectangle against the framebuffer; returns false if nothing is left.
bool clipRect(int& dx, int& dy, int& w, int& h, int& sx, int& sy) {
    sx = sy = 0;
    if (dx < 0) { sx = -dx; w += dx; dx = 0; }
    if (dy < 0) { sy = -dy; h += dy; dy = 0; }
    w = std::min(w, Video::kWidth - dx);
    h = std::min(h, Video::kHeight - dy);
    return w > 0 && h > 0;
}

}  // namespace

Video::~Video() { shutdown(); }

bool Video::init(const char* title, int scale, bool fullscreen, std::string* err) {
    shutdown();
    if (!SDL_WasInit(SDL_INIT_VIDEO) && SDL_InitSubSystem(SDL_INIT_VIDEO) != 0) {
        if (err) *err = SDL_GetError();
        return false;
    }
    scale_ = std::max(1, scale);
    Uint32 flags = SDL_WINDOW_RESIZABLE;
    if (fullscreen) flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    window_ = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, kWidth * scale_,
                               kHeight * scale_, flags);
    if (!window_) {
        if (err) *err = SDL_GetError();
        return false;
    }
    SDL_SetWindowMinimumSize(window_, kWidth, kHeight);
    fullscreen_ = fullscreen;

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer_) renderer_ = SDL_CreateRenderer(window_, -1, 0);
    if (!renderer_) {
        if (err) *err = SDL_GetError();
        shutdown();
        return false;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");  // nearest neighbour for crisp pixels
    texture_ = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, kWidth, kHeight);
    if (!texture_) {
        if (err) *err = SDL_GetError();
        shutdown();
        return false;
    }

    fb_.assign(size_t(kWidth) * kHeight, 0);
    overlay_.assign(size_t(kWidth) * kHeight, 0);
    overlayUsed_ = false;
    Palette grey;
    for (int i = 0; i < 256; ++i) grey.colors[size_t(i)] = Rgb{uint8_t(i), uint8_t(i), uint8_t(i)};
    setPalette(grey);
    updateDestRect();
    return true;
}

void Video::shutdown() {
    if (texture_) SDL_DestroyTexture(texture_);
    if (renderer_) SDL_DestroyRenderer(renderer_);
    if (window_) SDL_DestroyWindow(window_);
    texture_ = nullptr;
    renderer_ = nullptr;
    window_ = nullptr;
}

void Video::setPalette(const Palette& pal) {
    palette_ = pal;
    for (size_t i = 0; i < 256; ++i) palArgb_[i] = argb(pal.colors[i]);
}

void Video::setPaletteEntry(int index, Rgb c) {
    if (index < 0 || index > 255) return;
    palette_.colors[size_t(index)] = c;
    palArgb_[size_t(index)] = argb(c);
}

void Video::clear(uint8_t color) {
    std::memset(fb_.data(), color, fb_.size());
    if (overlayUsed_) {
        std::memset(overlay_.data(), 0, overlay_.size() * sizeof(uint32_t));
        overlayUsed_ = false;
    }
}

void Video::clearOverlay(int x, int y, int w, int h) {
    if (!overlayUsed_) return;
    int sx, sy;
    if (!clipRect(x, y, w, h, sx, sy)) return;
    for (int row = 0; row < h; ++row)
        std::memset(overlay_.data() + size_t(y + row) * kWidth + x, 0, size_t(w) * sizeof(uint32_t));
}

void Video::fillRect(int x, int y, int w, int h, uint8_t color) {
    int sx, sy;
    if (!clipRect(x, y, w, h, sx, sy)) return;
    clearOverlay(x, y, w, h);
    for (int row = 0; row < h; ++row) std::memset(fb_.data() + size_t(y + row) * kWidth + x, color, size_t(w));
}

void Video::blit8(const uint8_t* src, int w, int h, int pitch, int dx, int dy, int colorKey) {
    if (!src || w <= 0 || h <= 0) return;
    int sx, sy;
    if (!clipRect(dx, dy, w, h, sx, sy)) return;
    clearOverlay(dx, dy, w, h);
    for (int row = 0; row < h; ++row) {
        const uint8_t* s = src + size_t(sy + row) * size_t(pitch) + sx;
        uint8_t* d = fb_.data() + size_t(dy + row) * kWidth + dx;
        if (colorKey < 0) {
            std::memcpy(d, s, size_t(w));
        } else {
            const uint8_t key = uint8_t(colorKey);
            for (int x = 0; x < w; ++x)
                if (s[x] != key) d[x] = s[x];
        }
    }
}

void Video::blitRGB16(const uint16_t* src, int w, int h, int pitchPixels, int dx, int dy, Pixel16 fmt) {
    if (!src || w <= 0 || h <= 0) return;
    int sx, sy;
    if (!clipRect(dx, dy, w, h, sx, sy)) return;
    overlayUsed_ = true;
    for (int row = 0; row < h; ++row) {
        const uint16_t* s = src + size_t(sy + row) * size_t(pitchPixels) + sx;
        uint32_t* d = overlay_.data() + size_t(dy + row) * kWidth + dx;
        if (fmt == Pixel16::Rgb555)
            for (int x = 0; x < w; ++x) d[x] = argb(rgb555ToRgb(s[x]));
        else
            for (int x = 0; x < w; ++x) d[x] = argb(rgb565ToRgb(s[x]));
    }
}

void Video::updateDestRect() {
    if (!window_) return;
    int ww = kWidth, wh = kHeight;
    SDL_GetRendererOutputSize(renderer_, &ww, &wh);
    scale_ = std::max(1, std::min(ww / kWidth, wh / kHeight));
    dest_.w = kWidth * scale_;
    dest_.h = kHeight * scale_;
    dest_.x = (ww - dest_.w) / 2;
    dest_.y = (wh - dest_.h) / 2;
}

void Video::present() {
    if (!texture_) return;
    void* px = nullptr;
    int pitch = 0;
    if (SDL_LockTexture(texture_, nullptr, &px, &pitch) == 0) {
        for (int y = 0; y < kHeight; ++y) {
            uint32_t* dst = reinterpret_cast<uint32_t*>(static_cast<uint8_t*>(px) + size_t(y) * size_t(pitch));
            const uint8_t* s = fb_.data() + size_t(y) * kWidth;
            if (overlayUsed_) {
                const uint32_t* o = overlay_.data() + size_t(y) * kWidth;
                for (int x = 0; x < kWidth; ++x) dst[x] = (o[x] & 0xFF000000u) ? o[x] : palArgb_[s[x]];
            } else {
                for (int x = 0; x < kWidth; ++x) dst[x] = palArgb_[s[x]];
            }
        }
        SDL_UnlockTexture(texture_);
    }
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderClear(renderer_);
    SDL_RenderCopy(renderer_, texture_, nullptr, &dest_);
    SDL_RenderPresent(renderer_);
}

void Video::setFullscreen(bool on) {
    if (!window_ || on == fullscreen_) return;
    SDL_SetWindowFullscreen(window_, on ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
    fullscreen_ = on;
    updateDestRect();
}

bool Video::handleEvent(const SDL_Event& ev) {
    if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_RETURN && (ev.key.keysym.mod & KMOD_ALT) &&
        !ev.key.repeat) {
        toggleFullscreen();
        return true;
    }
    if (ev.type == SDL_WINDOWEVENT && (ev.window.event == SDL_WINDOWEVENT_SIZE_CHANGED ||
                                       ev.window.event == SDL_WINDOWEVENT_RESIZED ||
                                       ev.window.event == SDL_WINDOWEVENT_EXPOSED)) {
        updateDestRect();
        return ev.window.event != SDL_WINDOWEVENT_EXPOSED;
    }
    return false;
}

void Video::windowToFramebuffer(int wx, int wy, int& fx, int& fy) const {
    fx = std::clamp((wx - dest_.x) / scale_, 0, kWidth - 1);
    fy = std::clamp((wy - dest_.y) / scale_, 0, kHeight - 1);
}

}  // namespace dl2
