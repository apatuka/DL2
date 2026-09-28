// timer.h - millisecond clock (SDL_GetTicks64) and a simple frame-rate limiter.
#pragma once
#include <cstdint>

namespace dl2 {

// Milliseconds since SDL was initialised.
uint64_t ticksMs();
void sleepMs(uint32_t ms);

class FrameLimiter {
public:
    explicit FrameLimiter(int targetFps = 60) { setTargetFps(targetFps); }
    void setTargetFps(int fps);
    // Call once per frame after presenting: sleeps as needed to hold the target rate and
    // returns the time elapsed since the previous call, in milliseconds.
    uint32_t endFrame();

private:
    double periodMs_ = 1000.0 / 60.0;
    double next_ = 0.0;   // scheduled start of the next frame
    uint64_t last_ = 0;   // time of the previous endFrame()
};

}  // namespace dl2
