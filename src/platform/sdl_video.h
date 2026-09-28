// sdl_video.h - Video: SDL window + 640x480 8-bit indexed framebuffer and palette, presented via an RGBA streaming texture.
#pragma once
#include <SDL.h>

#include <array>
#include <cstdint>
#include <string>
#include <vector>

#include "formats/palette.h"

namespace dl2 {

class Video {
public:
    static constexpr int kWidth = 640;
    static constexpr int kHeight = 480;
    enum class Pixel16 { Rgb555, Rgb565 };

    Video() = default;
    ~Video();
    Video(const Video&) = delete;
    Video& operator=(const Video&) = delete;

    // Creates a resizable window sized kWidth*scale x kHeight*scale and the presentation texture.
    bool init(const char* title, int scale = 1, bool fullscreen = false, std::string* err = nullptr);
    void shutdown();
    bool isOpen() const { return window_ != nullptr; }
    SDL_Window* window() const { return window_; }
    SDL_Renderer* renderer() const { return renderer_; }

    // Indexed framebuffer (kWidth * kHeight bytes, pitch kWidth) and its palette.
    uint8_t* pixels() { return fb_.data(); }
    const uint8_t* pixels() const { return fb_.data(); }
    int pitch() const { return kWidth; }
    void setPalette(const Palette& pal);
    void setPaletteEntry(int index, Rgb c);
    const Palette& palette() const { return palette_; }

    // Drawing; everything is clipped to the framebuffer.
    void clear(uint8_t color = 0);
    void fillRect(int x, int y, int w, int h, uint8_t color);
    // 8 bpp blit; colorKey >= 0 makes that index transparent. pitch is in bytes.
    void blit8(const uint8_t* src, int w, int h, int pitch, int dx, int dy, int colorKey = -1);
    // 16 bpp direct-colour blits (PICT type 1). They write a direct-colour overlay that present()
    // composites above the indexed framebuffer; indexed drawing over the same area replaces it.
    void blitRGB16(const uint16_t* src, int w, int h, int pitchPixels, int dx, int dy, Pixel16 fmt);
    void blitRGB565(const uint16_t* src, int w, int h, int pitchPixels, int dx, int dy) {
        blitRGB16(src, w, h, pitchPixels, dx, dy, Pixel16::Rgb565);
    }
    void blitRGB555(const uint16_t* src, int w, int h, int pitchPixels, int dx, int dy) {
        blitRGB16(src, w, h, pitchPixels, dx, dy, Pixel16::Rgb555);
    }

    // Converts the framebuffer to RGBA, integer-scales it centred in the window and shows it.
    void present();

    void setFullscreen(bool on);
    bool fullscreen() const { return fullscreen_; }
    void toggleFullscreen() { setFullscreen(!fullscreen_); }
    // Handles Alt+Enter and window events. Returns true if the event was consumed.
    bool handleEvent(const SDL_Event& ev);
    // Maps window coordinates to framebuffer coordinates (letterboxed integer scale), clamped.
    void windowToFramebuffer(int wx, int wy, int& fx, int& fy) const;

private:
    void updateDestRect();
    // Clears the overlay (alpha = 0) over a clipped rectangle so indexed pixels show through.
    void clearOverlay(int x, int y, int w, int h);

    SDL_Window* window_ = nullptr;
    SDL_Renderer* renderer_ = nullptr;
    SDL_Texture* texture_ = nullptr;
    SDL_Rect dest_{0, 0, kWidth, kHeight};
    int scale_ = 1;
    bool fullscreen_ = false;

    std::vector<uint8_t> fb_;         // kWidth * kHeight palette indices
    std::vector<uint32_t> overlay_;   // kWidth * kHeight ARGB8888; alpha != 0 marks a direct-colour pixel
    bool overlayUsed_ = false;
    Palette palette_;
    std::array<uint32_t, 256> palArgb_{};
};

}  // namespace dl2
