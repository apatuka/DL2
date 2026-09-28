// sdl_input.h - Input: polls SDL events into a per-frame InputState (mouse in 640x480 space, buttons, key events, quit).
#pragma once
#include <SDL.h>

#include <array>
#include <cstdint>
#include <vector>

namespace dl2 {

class Video;

struct KeyEvent {
    SDL_Keycode key = SDLK_UNKNOWN;
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;
    uint16_t mod = 0;   // KMOD_* bits
    bool down = false;
    bool repeat = false;
};

struct InputState {
    enum Button : uint8_t { Left = 1, Middle = 2, Right = 4 };

    int mouseX = 0, mouseY = 0;      // framebuffer (640x480) coordinates
    uint8_t buttons = 0;             // currently held
    uint8_t pressed = 0;             // went down this frame
    uint8_t released = 0;            // went up this frame
    int wheel = 0;                   // vertical wheel ticks this frame
    std::vector<KeyEvent> keys;      // key events this frame, in order
    std::array<bool, SDL_NUM_SCANCODES> held{};
    bool quit = false;

    bool keyDown(SDL_Scancode sc) const { return held[size_t(sc)]; }
    // True if a (non-repeat) key-down event for `key` happened this frame.
    bool keyPressed(SDL_Keycode key) const {
        for (const KeyEvent& e : keys)
            if (e.down && !e.repeat && e.key == key) return true;
        return false;
    }
};

class Input {
public:
    // Pumps all pending SDL events. If `video` is given, window events and Alt+Enter go to it and
    // mouse coordinates are mapped into framebuffer space.
    void poll(Video* video = nullptr);
    const InputState& state() const { return state_; }

private:
    InputState state_;
};

}  // namespace dl2
