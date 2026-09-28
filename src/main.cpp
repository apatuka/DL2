// main.cpp - deadlock2 smoke test: draws PICT I000 as background and the SMNU D000 main interface through the
// CYLib engine port (16 bpp screen), with mouse hover/press highlighting via the SMenu API. Space plays WAVE #0,
// Left/Right cycle the background picture, Escape exits. Data dir: argv[1], DL2_DATA or the GOG default.
#include <SDL.h>

#include <charconv>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <string>

#include "engine/cygame.h"
#include "engine/input_queue.h"
#include "engine/offport.h"
#include "engine/pixel.h"
#include "engine/resources.h"
#include "engine/smenu.h"
#include "engine/sound.h"
#include "formats/cam_package.h"
#include "formats/iff_pbm.h"
#include "platform/sdl_audio.h"
#include "platform/sdl_input.h"
#include "platform/sdl_video.h"
#include "platform/timer.h"

using namespace dl2;
using namespace dl2::engine;

namespace {

const char* const kDefaultDataDir = "C:\\GOG Games\\Deadlock 2";

std::string resolveDataDir() {
    if (const char* env = std::getenv("DL2_DATA"); env && *env) return env;
    return kDefaultDataDir;
}

void fatal(const std::string& msg, bool nonInteractive) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", msg.c_str());
    if (!nonInteractive) SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Deadlock II", msg.c_str(), nullptr);
}

// Decodes PICT `index` of deadcyb.cam into an 8 bpp OffPort with its own palette (nullptr if unsupported).
OffPortPtr loadPicture(size_t index, std::string& status) {
    const CamPackage* cyb = resources().library(resources().findLibrary("deadcyb.cam"));
    const CamSection* picts = cyb ? cyb->section("PICT") : nullptr;
    if (!picts || picts->entries.empty()) return nullptr;
    index %= picts->entries.size();
    const CamEntry& e = picts->entries[index];
    std::string err;
    const std::vector<uint8_t> data = cyb->read(e, &err);
    auto port = std::make_shared<OffPort>();
    if (pictType(data) == uint32_t(PictType::IffPbm)) {
        Image8 img;
        if (!decodePictType2(data, img, &err)) { status = "PICT " + e.name + ": " + err; return nullptr; }
        port->create(img.width, img.height, 8);
        for (int y = 0; y < img.height; ++y) std::memcpy(port->pixelPtr(0, y), img.pixels.data() + size_t(y) * size_t(img.width), size_t(img.width));
        ColorTablePtr pal;
        if (img.hasPalette) pal = std::make_shared<ColorTable>(ColorTable::fromPalette(img.palette));
        else pal = resources().palette(makeTag("DPAL"));
        port->setPalette(pal);
        status = "PICT " + e.name + " (IFF PBM)";
    } else if (pictType(data) == uint32_t(PictType::Rgb555)) {
        Image16 img;
        if (!decodePictType1(data, img, &err)) { status = "PICT " + e.name + ": " + err; return nullptr; }
        port->create(img.width, img.height, 16, PixelFormat::Rgb555);
        for (int y = 0; y < img.height; ++y) std::memcpy(port->pixelPtr(0, y), img.pixels.data() + size_t(y) * size_t(img.width), size_t(img.width) * 2);
        status = "PICT " + e.name + " (RGB555)";
    } else {
        status = "PICT " + e.name + ": unsupported type";
        return nullptr;
    }
    return port;
}

}  // namespace

int main(int argc, char* argv[]) {
    std::string dataDir = resolveDataDir();
    int smokeFrames = 0;
    bool haveDataDir = false;
    for (int i = 1; i < argc; ++i) {
        const std::string arg = argv[i];
        if (arg == "--help") {
            std::puts("Usage: deadlock2 [data-directory] [--smoke-frames N]\n"
                      "SMenu/resource demo. --smoke-frames exits after N frames (1..10000) for automated checks.");
            return 0;
        }
        if (arg == "--smoke-frames" && i + 1 < argc) {
            const char* value = argv[++i];
            const char* end = value + std::strlen(value);
            const auto parsed = std::from_chars(value, end, smokeFrames);
            if (parsed.ec == std::errc{} && parsed.ptr == end && smokeFrames > 0 && smokeFrames <= 10000) continue;
            std::fputs("--smoke-frames requires an integer from 1 to 10000.\n", stderr);
            return 2;
        }
        if (!arg.empty() && arg.front() != '-' && !haveDataDir) {
            dataDir = arg;
            haveDataDir = true;
            continue;
        }
        std::fprintf(stderr, "Invalid argument: %s (see --help).\n", arg.c_str());
        return 2;
    }
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) != 0) {
        fatal(std::string("SDL_Init failed: ") + SDL_GetError(), smokeFrames > 0);
        return 1;
    }
    std::string err;
    Video video;
    if (!video.init("Deadlock II smoke test - SMenu D000", 1, false, &err)) {
        fatal("video: " + err, smokeFrames > 0);
        SDL_Quit();
        return 1;
    }
    Audio audio;
    if (!audio.init(&err)) SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "audio disabled: %s", err.c_str());

    CyGame& game = CyGame::instance();
    if (!game.init(640, 480, 16, &video, audio.isOpen() ? &audio : nullptr)) {
        fatal("cannot create CYLib screen", smokeFrames > 0);
        audio.shutdown();
        video.shutdown();
        SDL_Quit();
        return 1;
    }
    if (game.openLibraries(dataDir, &err) < 2) {
        fatal("cannot open the CAM packages in " + dataDir + (err.empty() ? "" : ": " + err) +
              "\n(pass the data directory as argv[1] or set DL2_DATA)", smokeFrames > 0);
        game.shutdown();
        audio.shutdown();
        video.shutdown();
        SDL_Quit();
        return 1;
    }
    SMenu::setSoundPlayer([](uint32_t id) { SoundSystem::instance().playOnce(id); });

    std::unique_ptr<SMenu> menu = SMenu::load(makeTag("D000"));
    if (!menu) {
        fatal("cannot load SMNU D000 from deadtext.cam", smokeFrames > 0);
        game.shutdown();
        audio.shutdown();
        video.shutdown();
        SDL_Quit();
        return 1;
    }
    if (menu->palette && menu->palette->palette) game.setSystemPalette(menu->palette->palette);
    menu->show();

    size_t pictIndex = 0;
    std::string pictStatus;
    OffPortPtr background = loadPicture(pictIndex, pictStatus);

    Input input;
    FrameLimiter limiter(60);
    SMenuItem* hoverItem = nullptr;
    bool running = true;
    uint32_t lastResult = 0;
    int presentedFrames = 0;
    while (running) {
        input.poll(&video);
        const InputState& in = input.state();
        if (in.quit) running = false;
        for (const KeyEvent& k : in.keys) {
            if (!k.down || k.repeat) continue;
            if (k.key == SDLK_ESCAPE) running = false;
            else if (k.key == SDLK_LEFT) { pictIndex = pictIndex == 0 ? 8 : pictIndex - 1; background = loadPicture(pictIndex, pictStatus); }
            else if (k.key == SDLK_RIGHT) { ++pictIndex; background = loadPicture(pictIndex, pictStatus); }
            else if (k.key == SDLK_SPACE) SoundSystem::instance().playOnce(0);
        }
        game.feedInput(in);
        SoundSystem::instance().update();

        // SMenu event processing (FUN_004a2cb5) + hover highlight through the item state API.
        uint32_t hoverId = 0;
        const bool held = menu->process(&hoverId);
        SMenuItem* nowHover = hoverId ? menu->itemById(hoverId) : nullptr;
        if (!held && nowHover != hoverItem) {
            if (hoverItem) menu->setHighlight(hoverItem, 0, false);
            if (nowHover && nowHover->type != kItemText && nowHover->type != kItemPicture) menu->setHighlight(nowHover, 0, true);
            hoverItem = nowHover;
        }
        if (menu->result() != 0 && menu->result() != lastResult) {
            lastResult = menu->result();
            SDL_Log("SMenu D000: item %u activated", lastResult);
            menu->clearResult();
        }

        // Frame: background picture, then the whole menu (dirty rects are cleared since we redraw everything).
        OffPort& screen = game.screen();
        Pixel::setPort(&screen);
        Pixel::resetClip();
        if (background) screen.blitFrom(*background, screen.bounds(), background->bounds());
        else screen.clear(0);
        SMenu::dirtyRects().clear();
        menu->draw();
        game.present();

        const std::string title = "Deadlock II smoke test - SMNU D000 over " + pictStatus + "  |  hover id " +
                                  std::to_string(hoverId) + "  |  Left/Right: picture, Space: sound, Alt+Enter: fullscreen, Esc: quit";
        SDL_SetWindowTitle(video.window(), title.c_str());
        limiter.endFrame();
        if (smokeFrames > 0 && ++presentedFrames >= smokeFrames) running = false;
    }

    menu.reset();
    game.shutdown();
    audio.shutdown();
    video.shutdown();
    SDL_Quit();
    return 0;
}
