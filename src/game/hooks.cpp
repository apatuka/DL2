// hooks.cpp - implementaciones por defecto (no-op / stderr) de los hooks de UI.
#include "game/hooks.h"

#include <chrono>
#include <cstdarg>
#include <cstdio>

namespace dl2::hooks {

UiHooks ui{};

int messageBox(const char* title, const char* text, unsigned flags) {
    if (ui.messageBox) return ui.messageBox(title, text, flags);
    std::fprintf(stderr, "[msgbox] %s: %s\n", title ? title : "", text ? text : "");
    return 1;
}

void debugMessage(const char* text) {
    if (ui.debugMessage) { ui.debugMessage(text); return; }
    std::fprintf(stderr, "[debug] %s\n", text ? text : "");
}

void debugLog(const char* tag) {
    if (ui.debugLog) { ui.debugLog(tag); return; }
    std::fprintf(stderr, "[log] %s\n", tag ? tag : "");
}

void refresh(const char* what) { if (ui.refresh) ui.refresh(what); }
void playSound(int soundId) { if (ui.playSound) ui.playSound(soundId); }
void playSpeech(const char* name) { if (ui.playSpeech) ui.playSpeech(name); }
void progress(const char* text, int percent) { if (ui.progress) ui.progress(text, percent); }
void pump() { if (ui.pump) ui.pump(); }

uint32_t ticks() {
    if (ui.ticks) return ui.ticks();
    using namespace std::chrono;
    return uint32_t(duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count());
}

void debugMessagef(const char* fmt, ...) {
    char buf[1024];
    va_list ap;
    va_start(ap, fmt);
    std::vsnprintf(buf, sizeof buf, fmt, ap);
    va_end(ap);
    debugMessage(buf);
}

} // namespace dl2::hooks
