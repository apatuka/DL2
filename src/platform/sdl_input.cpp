// sdl_input.cpp - SDL event pump filling InputState.
#include "platform/sdl_input.h"

#include <memory>

#include "platform/sdl_video.h"

namespace dl2 {

namespace {
uint8_t buttonBit(Uint8 sdlButton) {
    switch (sdlButton) {
        case SDL_BUTTON_LEFT: return InputState::Left;
        case SDL_BUTTON_MIDDLE: return InputState::Middle;
        case SDL_BUTTON_RIGHT: return InputState::Right;
        default: return 0;
    }
}
}  // namespace

void Input::poll(Video* video) {
    state_.pressed = 0;
    state_.released = 0;
    state_.wheel = 0;
    state_.keys.clear();
    state_.droppedFiles.clear();

    SDL_Event ev;
    while (SDL_PollEvent(&ev)) {
        // SDL transfers ownership of both drop payload kinds to the recipient.
        // Handle them before any event consumer can skip their cleanup; the
        // owner also frees exactly once if copying a filename throws.
        if (ev.type == SDL_DROPFILE || ev.type == SDL_DROPTEXT) {
            const std::unique_ptr<char, decltype(&SDL_free)> payload(ev.drop.file, &SDL_free);
            if (ev.type == SDL_DROPFILE && payload)
                state_.droppedFiles.emplace_back(payload.get());
            continue;
        }
        if (video && video->handleEvent(ev)) continue;
        switch (ev.type) {
            case SDL_QUIT:
                state_.quit = true;
                break;
            case SDL_KEYDOWN:
            case SDL_KEYUP: {
                KeyEvent k;
                k.key = ev.key.keysym.sym;
                k.scancode = ev.key.keysym.scancode;
                k.mod = ev.key.keysym.mod;
                k.down = ev.type == SDL_KEYDOWN;
                k.repeat = ev.key.repeat != 0;
                if (k.scancode > SDL_SCANCODE_UNKNOWN && k.scancode < SDL_NUM_SCANCODES)
                    state_.held[size_t(k.scancode)] = k.down;
                state_.keys.push_back(k);
                break;
            }
            case SDL_MOUSEMOTION:
                if (video) video->windowToFramebuffer(ev.motion.x, ev.motion.y, state_.mouseX, state_.mouseY);
                else { state_.mouseX = ev.motion.x; state_.mouseY = ev.motion.y; }
                break;
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP: {
                if (video) video->windowToFramebuffer(ev.button.x, ev.button.y, state_.mouseX, state_.mouseY);
                else { state_.mouseX = ev.button.x; state_.mouseY = ev.button.y; }
                const uint8_t bit = buttonBit(ev.button.button);
                if (ev.type == SDL_MOUSEBUTTONDOWN) {
                    state_.buttons |= bit;
                    state_.pressed |= bit;
                } else {
                    state_.buttons &= uint8_t(~bit);
                    state_.released |= bit;
                }
                break;
            }
            case SDL_MOUSEWHEEL:
                state_.wheel += ev.wheel.y;
                break;
            default:
                break;
        }
    }
}

}  // namespace dl2
