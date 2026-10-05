#include "app/world_inspector.h"
#include "platform/sdl_video.h"
#include "platform/timer.h"
#include <SDL.h>
#include <cstdio>
#include <exception>
#include <memory>

namespace dl2::app {
namespace {
namespace fs = std::filesystem;
void report(const std::string& error, bool automated) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", error.c_str());
    if (!automated) SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "World inspector", error.c_str(), nullptr);
}
bool screenshot(const engine::OffPort& port, const fs::path& destination, std::string& error) {
    auto pixels = port.toRgb555();
    using Surface = std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)>;
    Surface surface(SDL_CreateRGBSurfaceFrom(pixels.data(), port.width(), port.height(), 16,
                    port.width() * 2, 0x7c00, 0x03e0, 0x001f, 0), SDL_FreeSurface);
    if (!surface) { error = SDL_GetError(); return false; }
#ifdef _WIN32
    auto* file = _wfopen(destination.c_str(), L"wbx");
#else
    auto* file = std::fopen(destination.c_str(), "wbx");
#endif
    if (!file) { error = "Screenshot path must be a new writable file"; return false; }
    // Official SDL Windows binaries can disable SDL_RWFromFP. Keep stdio in
    // this executable's CRT and retain the exclusive creation above.
    auto* rw = SDL_AllocRW();
    if (rw) {
        rw->type = SDL_RWOPS_UNKNOWN;
        rw->hidden.unknown.data1 = file;
        rw->size = [](SDL_RWops*) -> Sint64 { return SDL_SetError("Size query unsupported"); };
        rw->seek = [](SDL_RWops* stream, Sint64 offset, int origin) -> Sint64 {
            auto* output = static_cast<FILE*>(stream->hidden.unknown.data1);
#ifdef _WIN32
            if (_fseeki64(output, offset, origin) != 0) return SDL_SetError("BMP seek failed");
            return _ftelli64(output);
#else
            if (fseeko(output, offset, origin) != 0) return SDL_SetError("BMP seek failed");
            return ftello(output);
#endif
        };
        rw->read = [](SDL_RWops*, void*, size_t, size_t) -> size_t { return 0; };
        rw->write = [](SDL_RWops* stream, const void* data, size_t size, size_t count) -> size_t {
            return std::fwrite(data, size, count, static_cast<FILE*>(stream->hidden.unknown.data1));
        };
        rw->close = [](SDL_RWops* stream) -> int {
            const int result = std::fclose(static_cast<FILE*>(stream->hidden.unknown.data1));
            SDL_FreeRW(stream);
            return result;
        };
    }
    if (!rw) { std::fclose(file); error = SDL_GetError(); }
    else if (SDL_SaveBMP_RW(surface.get(), rw, 1) == 0) return true;
    else error = SDL_GetError();
    std::error_code ignored; fs::remove(destination, ignored); // Only the new file we just created.
    return false;
}
void saveAutomaticCopy(InspectorSession& session) {
    if (!session.document()) { session.saveCopy({}); return; }
    char* base = SDL_GetBasePath();
    if (!base) { report("Cannot find the executable directory for saves", false); return; }
    const auto directory = pathFromUtf8(base) / "saves";
    SDL_free(base);
    std::error_code error;
    fs::create_directories(directory, error);
    if (error) { report("Cannot create saves directory: " + error.message(), false); return; }
    for (int n = 1; n <= 10000; ++n) {
        const auto target = directory / ("inspection-copy-" + std::to_string(n) + ".sav");
        if (fs::exists(target, error)) continue;
        if (error) { report(error.message(), false); return; }
        session.saveCopy(target); // Exclusive publication also protects against races.
        SDL_Log("%s", session.status().c_str());
        return;
    }
    report("The saves directory already contains 10000 inspector copies", false);
}
}

int runWorldInspector(const InspectorOptions& options) {
    const bool automated = options.smokeFrames > 0;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        report(SDL_GetError(), automated); return 1;
    }
    // Objects below are destroyed before SDL_Quit, including on exceptions.
    struct QuitSDL { ~QuitSDL() { SDL_Quit(); } } cleanup;
    try {
        Video video;
        std::string error;
        if (!video.init("Deadlock II - read-only world inspector", 2, false, &error)) {
            report(error, automated); return 1;
        }
        WorldInspector view;
        if (!view.initialize(options.dataDirectory, error)) { report(error, automated); return 1; }
        InspectorSession session;
        const bool loaded = !options.scenario.empty()
            ? session.loadScenario(options.dataDirectory / "LEVELS", options.scenario)
            : session.load(options.loadFile.empty() ? options.dataDirectory / "TUTORIAL.SAV" : options.loadFile);
        if (!loaded) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", session.status().c_str());
            if (automated) return 1;
        }
        Input input;
        FrameLimiter limiter(60);
        int frames = 0;
        bool running = true;
        while (running) {
            input.poll(&video);
            for (const auto& path : input.state().droppedFiles) {
                session.load(pathFromUtf8(path));
                SDL_Log("%s", session.status().c_str());
            }
            switch (view.input(session, input.state())) {
            case InspectorAction::Quit: running = false; break;
            case InspectorAction::Reload: session.reload(); SDL_Log("%s", session.status().c_str()); break;
            case InspectorAction::SaveCopy: saveAutomaticCopy(session); break;
            case InspectorAction::None: break;
            }
            view.draw(session);
            const auto pixels = view.screen().toRgb555();
            video.blitRGB555(pixels.data(), 640, 480, 640, 0, 0);
            video.present();
            if (automated && ++frames >= options.smokeFrames) running = false;
            limiter.endFrame();
        }
        if (!options.screenshot.empty() && !screenshot(view.screen(), options.screenshot, error)) {
            report(error, automated); return 1;
        }
        return 0;
    } catch (const std::exception& error) {
        report(error.what(), automated); return 1;
    }
}
} // namespace dl2::app
