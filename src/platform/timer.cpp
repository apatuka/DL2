// timer.cpp - SDL-backed clock and frame limiter.
#include "platform/timer.h"

#include <SDL.h>

namespace dl2 {

uint64_t ticksMs() { return SDL_GetTicks64(); }

void sleepMs(uint32_t ms) { SDL_Delay(ms); }

void FrameLimiter::setTargetFps(int fps) {
    periodMs_ = fps > 0 ? 1000.0 / fps : 0.0;
    next_ = 0.0;
}

uint32_t FrameLimiter::endFrame() {
    uint64_t now = ticksMs();
    if (periodMs_ > 0.0) {
        if (next_ <= 0.0 || double(now) > next_ + periodMs_ * 4.0) next_ = double(now);  // (re)sync after stalls
        if (double(now) < next_) {
            SDL_Delay(uint32_t(next_ - double(now)));
            now = ticksMs();
        }
        next_ += periodMs_;
    }
    const uint32_t elapsed = last_ ? uint32_t(now - last_) : 0;
    last_ = now;
    return elapsed;
}

}  // namespace dl2
