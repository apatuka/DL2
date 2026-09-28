// Headless SDL event ownership and per-frame input regression checks.
#define SDL_MAIN_HANDLED
#include "platform/sdl_input.h"

#include <array>
#include <cstdio>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

struct TrackedPayload {
    void* pointer = nullptr;
    int frees = 0;
};
std::array<TrackedPayload, 3> payloads;
SDL_free_func originalFree = nullptr;

void SDLCALL trackFree(void* pointer) {
    for (auto& payload : payloads) {
        if (payload.pointer && payload.pointer == pointer) {
            ++payload.frees;
            // Turn a second release into a test failure instead of asking the
            // system allocator to act on an already released address.
            if (payload.frees > 1) return;
            break;
        }
    }
    originalFree(pointer);
}

void require(bool condition, const char* message) {
    if (!condition) throw std::runtime_error(message);
}

void push(SDL_Event& event) {
    if (SDL_PushEvent(&event) != 1)
        throw std::runtime_error(std::string("SDL_PushEvent: ") + SDL_GetError());
}

void pushDrop(Uint32 type, const char* text, size_t index) {
    SDL_Event event{};
    event.type = type;
    event.drop.file = SDL_strdup(text);
    require(event.drop.file != nullptr, "cannot allocate drop payload");
    payloads[index] = {event.drop.file, 0};
    if (SDL_PushEvent(&event) != 1) {
        SDL_free(event.drop.file); // The queue did not take ownership.
        throw std::runtime_error(std::string("SDL_PushEvent drop: ") + SDL_GetError());
    }
}

void droppedFilesAndExistingEvents() {
    SDL_EventState(SDL_DROPFILE, SDL_ENABLE);
    SDL_EventState(SDL_DROPTEXT, SDL_ENABLE);
    dl2::Input input;
    input.poll();
    const std::string first = "C:\\partidas\\colonia-\xc3\xb1.SAV";
    const std::string second = "C:\\partidas\\campaign.CPN";

    SDL_Event event{};
    event.type = SDL_DROPBEGIN;
    push(event);
    pushDrop(SDL_DROPFILE, first.c_str(), 0);
    pushDrop(SDL_DROPTEXT, "text is not a filename", 1);
    pushDrop(SDL_DROPFILE, second.c_str(), 2);
    event = {};
    event.type = SDL_DROPCOMPLETE;
    push(event);
    event = {};
    event.type = SDL_KEYDOWN;
    event.key.keysym.sym = SDLK_RETURN;
    event.key.keysym.scancode = SDL_SCANCODE_RETURN;
    push(event);
    event = {};
    event.type = SDL_MOUSEWHEEL;
    event.wheel.y = 2;
    push(event);
    event = {};
    event.type = SDL_MOUSEMOTION;
    event.motion.x = 12;
    event.motion.y = 34;
    push(event);

    input.poll();
    const auto& firstFrame = input.state();
    require(firstFrame.droppedFiles == std::vector<std::string>({first, second}),
            "drop paths must retain UTF-8 bytes and arrival order, ignoring dropped text");
    for (const auto& payload : payloads)
        require(payload.frees == 1, "each SDL drop payload must be released exactly once");
    // Stop tracking these addresses before later SDL allocations can reuse them.
    payloads = {};
    require(firstFrame.keyPressed(SDLK_RETURN) && firstFrame.keyDown(SDL_SCANCODE_RETURN),
            "keyboard events must still work alongside file drops");
    require(firstFrame.wheel == 2 && firstFrame.mouseX == 12 && firstFrame.mouseY == 34,
            "mouse events must still work alongside file drops");

    input.poll();
    require(input.state().droppedFiles.empty() && input.state().keys.empty() && input.state().wheel == 0,
            "per-frame drop, keyboard and wheel events must clear on the next poll");
    require(input.state().keyDown(SDL_SCANCODE_RETURN), "held keys must survive an empty poll");

    event = {};
    event.type = SDL_KEYUP;
    event.key.keysym.sym = SDLK_RETURN;
    event.key.keysym.scancode = SDL_SCANCODE_RETURN;
    push(event);
    event = {};
    event.type = SDL_MOUSEBUTTONDOWN;
    event.button.button = SDL_BUTTON_LEFT;
    event.button.x = 9;
    event.button.y = 10;
    push(event);
    event = {};
    event.type = SDL_DROPFILE; // A defensive null payload must not become a filename.
    event.drop.file = nullptr;
    push(event);
    event = {};
    event.type = SDL_DROPTEXT;
    event.drop.file = nullptr;
    push(event);
    event = {};
    event.type = SDL_QUIT;
    push(event);
    input.poll();
    require(input.state().droppedFiles.empty(), "null drop payloads must be ignored");
    require(!input.state().keyDown(SDL_SCANCODE_RETURN) && input.state().keys.size() == 1 &&
            !input.state().keys[0].down, "keyboard release must still work after file drops");
    require(input.state().pressed == dl2::InputState::Left && input.state().mouseX == 9 &&
            input.state().mouseY == 10 && input.state().quit,
            "mouse button and quit events must still work after file drops");
}

} // namespace

int main() {
    SDL_malloc_func originalMalloc = nullptr;
    SDL_calloc_func originalCalloc = nullptr;
    SDL_realloc_func originalRealloc = nullptr;
    SDL_GetMemoryFunctions(&originalMalloc, &originalCalloc, &originalRealloc, &originalFree);
    if (SDL_SetMemoryFunctions(originalMalloc, originalCalloc, originalRealloc, trackFree) != 0) {
        std::fprintf(stderr, "input: cannot instrument SDL allocation: %s\n", SDL_GetError());
        return 1;
    }
    SDL_SetMainReady();
    bool ok = false;
    if (SDL_Init(SDL_INIT_EVENTS) != 0) {
        std::fprintf(stderr, "input: SDL_Init(events): %s\n", SDL_GetError());
    } else {
        try {
            droppedFilesAndExistingEvents();
            std::puts("input: UTF-8 drops, exact payload release, frame reset and existing events passed");
            ok = true;
        } catch (const std::exception& error) {
            std::fprintf(stderr, "input: %s\n", error.what());
        }
    }
    payloads = {};
    SDL_Quit();
    SDL_SetMemoryFunctions(originalMalloc, originalCalloc, originalRealloc, originalFree);
    return ok ? 0 : 1;
}
