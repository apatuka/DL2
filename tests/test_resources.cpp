// Original assets remain external and are opened read-only; rendering is in memory.
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <string>

#include "engine/cygame.h"
#include "engine/pixel.h"
#include "engine/resources.h"
#include "engine/smenu.h"
#include "formats/iff_pbm.h"

using namespace dl2;
using namespace dl2::engine;
namespace fs = std::filesystem;

#define CHECK(expr) do { if (!(expr)) { std::fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, #expr); return false; } } while (false)

namespace {

bool cacheAndReopen(const fs::path& path) {
    ResourceManager mgr;
    std::string err;
    const int lib = mgr.addLibrary(path.string(), &err);
    CHECK(lib != 0);
    auto first = mgr.get(kTagPALT, makeTag("DPAL"), lib, kResRef);
    CHECK(first && first->palette && first->palette->size() == 256);
    auto second = mgr.get(kTagPALT, makeTag("DPAL"), lib, kResRef);
    CHECK(first == second && first->refCount == 2);
    mgr.release(second);
    CHECK(first->refCount == 1);
    mgr.release(first);
    auto reloaded = mgr.get(kTagPALT, makeTag("DPAL"), lib);
    CHECK(reloaded && reloaded != first);
    mgr.closeLibrary(lib);
    CHECK(mgr.library(lib) == nullptr && mgr.findLibrary(path.filename().string()) == 0);
    CHECK(mgr.get(kTagPALT, makeTag("DPAL"), lib) == nullptr);
    const int reopened = mgr.addLibrary(path.string(), &err);
    CHECK(reopened == lib && mgr.library(reopened) != nullptr);
    CHECK(mgr.libraryCount() == 1);
    CHECK(mgr.get(kTagPALT, makeTag("DPAL"), reopened) != nullptr);
    return true;
}

bool assets(const fs::path& dir) {
    CyGame& game = CyGame::instance();
    std::string err;
    CHECK(game.init(640, 480, 16));
    CHECK(game.openLibraries(dir.string(), &err) >= 2);
    ResourceManager& mgr = resources();
    size_t validated = 0, pictures = 0, menus = 0;
    for (const char* file : {"deadcyb.cam", "deadtext.cam"}) {
        const int lib = mgr.findLibrary(file);
        const CamPackage* cam = mgr.library(lib);
        CHECK(cam);
        for (const CamSection& sec : cam->sections()) {
            std::printf("%s %s: %zu resources\n", file, sec.tag.c_str(), sec.entries.size());
            for (const CamEntry& entry : sec.entries) {
                const Tag tag = makeTag(sec.tag);
                const uint32_t id = (sec.flags & 1) ? entry.index : makeTag(entry.name);
                const ResPtr resource = mgr.get(tag, id, lib);
                if (!resource) std::fprintf(stderr, "cannot decode %s %s %s\n", file, sec.tag.c_str(), entry.name.c_str());
                CHECK(resource && resource->data.size() == entry.size);
                if (tag == kTagPICT) {
                    Image8 image8;
                    Image16 image16;
                    const uint32_t type = pictType(resource->data);
                    if (type == uint32_t(PictType::Rgb555)) {
                        CHECK(decodePictType1(resource->data, image16, &err));
                        CHECK(image16.pixels.size() == size_t(image16.width) * size_t(image16.height));
                        ++pictures;
                    } else if (type == uint32_t(PictType::IffPbm)) {
                        CHECK(decodePictType2(resource->data, image8, &err));
                        CHECK(image8.pixels.size() == size_t(image8.width) * size_t(image8.height));
                        ++pictures;
                    }
                } else if (tag == kTagSMNU) {
                    // Pass 0: referenced IMAG/FONT/PALT live in sibling libraries.
                    auto menu = SMenu::load(id);
                    CHECK(menu);
                    game.screen().clear(0);
                    Pixel::setPort(&game.screen());
                    Pixel::resetClip();
                    if (menu->palette && menu->palette->palette) game.setSystemPalette(menu->palette->palette);
                    menu->show();
                    menu->draw();
                    if (id == makeTag("D000")) {
                        CHECK(!menu->items().empty());
                        const auto pixels = game.screen().toRgb555();
                        CHECK(std::any_of(pixels.begin(), pixels.end(), [](uint16_t p) { return p != 0; }));
                    }
                    ++menus;
                }
                ++validated;
            }
        }
    }
    CHECK(menus > 0 && pictures > 0);
    CHECK(SMenu::all().empty());
    SMenu::dirtyRects().clear();
    const int soundLib = mgr.findLibrary("dl2sound.cam");
    if (soundLib) {
        const ResPtr sound = mgr.get(kTagWAVE, 0, soundLib);
        CHECK(sound && sound->sound);
    }
    game.shutdown();
    std::printf("resources: %zu payloads validated, %zu pictures decoded, %zu menus rendered headlessly\n", validated, pictures, menus);
    return true;
}

} // namespace

int main(int argc, char** argv) {
    const char* dataDir = argc > 1 && argv[1][0] ? argv[1] : std::getenv("DL2_DATA");
    if (!dataDir || !*dataDir) {
        std::puts("SKIP: pass the original data directory or set DL2_DATA");
        return 77;
    }
    const fs::path dir(dataDir);
    if (!fs::exists(dir / "deadcyb.cam") || !fs::exists(dir / "deadtext.cam")) {
        std::printf("SKIP: missing original deadcyb.cam/deadtext.cam in %s\n", dataDir);
        return 77;
    }
    const bool cacheOk = cacheAndReopen(dir / "deadcyb.cam");
    const bool assetsOk = assets(dir);
    return cacheOk && assetsOk ? 0 : 1;
}
