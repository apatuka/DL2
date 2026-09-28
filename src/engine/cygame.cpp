// cygame.cpp - fachada CYGame: pantalla, librerias, presentacion y entrada.
#include "engine/cygame.h"

#include <SDL.h>

#include "engine/input_queue.h"
#include "engine/pixel.h"
#include "engine/resources.h"
#include "engine/smenu.h"
#include "engine/sound.h"
#include "platform/sdl_audio.h"
#include "platform/sdl_input.h"
#include "platform/sdl_video.h"
#include "platform/timer.h"

namespace dl2::engine {

CyGame& CyGame::instance() {
    static CyGame g;
    return g;
}

bool CyGame::init(int w, int h, int bpp, Video* video, Audio* audio) {
    video_ = video;
    audio_ = audio;
    if (!screen_.create(w, h, bpp, PixelFormat::Rgb555)) return false;
    screen_.setFlags(2);   // primaria
    Pixel::setPort(&screen_);
    Pixel::resetClip();
    Pixel::setBlitMode(0);
    SoundSystem::instance().init(audio);
    startMs_ = ticksMs();
    hasLastClick_[0] = hasLastClick_[1] = false;
    InputQueue::instance().setTicks(0);
    return true;
}

void CyGame::shutdown() {
    SoundSystem::instance().stopAll();
    Pixel::setPort(nullptr);
    video_ = nullptr;
    audio_ = nullptr;
}

int CyGame::openLibraries(const std::string& dataDir, std::string* err) {
    static const char* const kLibs[] = {"deadcyb.cam", "deadtext.cam", "dl2sound.cam", "dl2music.cam",
                                        "dl2segue.cam", "deadanim.cam", "deadcine.cam"};
    int opened = 0;
    std::string firstErr;
    for (const char* name : kLibs) {
        std::string path = dataDir;
        if (!path.empty() && path.back() != '\\' && path.back() != '/') path += '\\';
        path += name;
        std::string e;
        if (resources().addLibrary(path, &e)) ++opened;
        else if (firstErr.empty()) firstErr = e;
    }
    if (err) *err = firstErr;
    return opened;
}

void CyGame::setSystemPalette(const ColorTablePtr& pal) {
    screen_.setPalette(pal);
    if (video_ && pal && screen_.bpp() == 8) video_->setPalette(pal->toPalette());
}

void CyGame::present() {
    if (!video_) return;
    if (screen_.bpp() == 16) {
        const std::vector<uint16_t> rgb = screen_.toRgb555();
        video_->blitRGB555(rgb.data(), screen_.width(), screen_.height(), screen_.width(), 0, 0);
    } else {
        if (screen_.palette()) video_->setPalette(screen_.palette()->toPalette());
        video_->blit8(screen_.data(), screen_.width(), screen_.height(), screen_.pitch(), 0, 0);
    }
    video_->present();
}

uint32_t CyGame::ticks() const { return uint32_t(ticksMs() - startMs_); }

namespace {
// FUN_0048d920: teclas virtuales -> codigos CYLib.
uint32_t translateKey(const KeyEvent& k) {
    uint32_t code = 0;
    switch (k.key) {
        case SDLK_PAGEUP: code = kKeyPageUp; break;
        case SDLK_RIGHT: code = kKeyRight; break;
        case SDLK_PAGEDOWN: code = kKeyPageDown; break;
        case SDLK_DOWN: code = kKeyDown; break;
        case SDLK_END: code = kKeyEnd; break;
        case SDLK_LEFT: code = kKeyLeft; break;
        case SDLK_HOME: code = kKeyHome; break;
        case SDLK_UP: code = kKeyUp; break;
        case SDLK_INSERT: code = kKeyInsert; break;
        case SDLK_DELETE: code = kKeyDelete; break;
        case SDLK_RETURN: case SDLK_KP_ENTER: code = '\r'; break;
        case SDLK_ESCAPE: code = 0x1b; break;
        case SDLK_TAB: code = 9; break;
        case SDLK_BACKSPACE: code = 8; break;
        default:
            if (k.key >= SDLK_F1 && k.key <= SDLK_F15) code = kKeyF1 + uint32_t(k.key - SDLK_F1);
            else if (k.key >= 0x20 && k.key < 0x7f) {
                code = uint32_t(k.key);
                const bool shift = (k.mod & KMOD_SHIFT) != 0;
                if (code >= 'a' && code <= 'z' && (shift ^ ((k.mod & KMOD_CAPS) != 0))) code -= 0x20;
                else if (shift) {
                    static const char* const from = "1234567890-=[]\\;',./`";
                    static const char* const to = "!@#$%^&*()_+{}|:\"<>?~";
                    for (int i = 0; from[i]; ++i) if (uint32_t(from[i]) == code) { code = uint32_t(to[i]); break; }
                }
            }
            break;
    }
    if (code == 0) return 0;
    if (k.mod & KMOD_SHIFT) code |= kKeyModShift;
    if (k.mod & KMOD_CTRL) code |= kKeyModCtrl;
    if (k.mod & KMOD_ALT) code |= kKeyModAlt;
    return code;
}
}  // namespace

void CyGame::feedInput(const InputState& in) {
    InputQueue& q = InputQueue::instance();
    q.setTicks(ticks());
    q.setMousePos(in.mouseX, in.mouseY);
    q.setModifiers(in.keyDown(SDL_SCANCODE_LSHIFT) || in.keyDown(SDL_SCANCODE_RSHIFT),
                   in.keyDown(SDL_SCANCODE_LCTRL) || in.keyDown(SDL_SCANCODE_RCTRL),
                   in.keyDown(SDL_SCANCODE_LALT) || in.keyDown(SDL_SCANCODE_RALT));
    uint32_t held = 0;
    if (in.buttons & InputState::Left) held |= 1;
    if (in.buttons & InputState::Right) held |= 2;
    q.setButtonsHeld(held);
    const uint32_t now = ticks();
    for (int b = 0; b < 2; ++b) {
        const uint8_t sdlMask = b == 0 ? InputState::Left : InputState::Right;
        if (in.pressed & sdlMask) {
            // Doble clic: dos pulsaciones en < 400 ms y a menos de 4 px (GetDoubleClickTime tipico).
            const bool dbl = hasLastClick_[b] && now - lastClickMs_[b] < 400 &&
                             std::abs(in.mouseX - lastClickX_[b]) < 4 && std::abs(in.mouseY - lastClickY_[b]) < 4;
            q.pushMouse(dbl ? (b == 0 ? kMouseLeftDouble : kMouseRightDouble) : (b == 0 ? kMouseLeftDown : kMouseRightDown), in.mouseX, in.mouseY);
            // A timestamp of zero is a valid click during the first frame, not "no previous click".
            hasLastClick_[b] = !dbl;
            lastClickMs_[b] = now;
            lastClickX_[b] = in.mouseX;
            lastClickY_[b] = in.mouseY;
        }
        if (in.released & sdlMask) q.pushMouse(b == 0 ? kMouseLeftUp : kMouseRightUp, in.mouseX, in.mouseY);
    }
    for (const KeyEvent& k : in.keys) {
        if (!k.down) continue;
        const uint32_t code = translateKey(k);
        if (code) q.pushKey(code);
    }
    lastButtons_ = held;
}

}  // namespace dl2::engine
