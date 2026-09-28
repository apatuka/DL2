// Headless regression checks. CHECK stays active in Release/RelWithDebInfo.
#define SDL_MAIN_HANDLED
#include <cstdio>
#include <vector>

#include "engine/cygame.h"
#include "engine/input_queue.h"
#include "engine/pixel.h"
#include "engine/smenu.h"
#include "engine/tile.h"
#include "platform/sdl_input.h"

using namespace dl2;
using namespace dl2::engine;

#define CHECK(expr) do { if (!(expr)) { std::fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, #expr); return false; } } while (false)

namespace {

bool raster() {
    OffPort src, dst;
    CHECK(src.create(3, 2, 8));
    CHECK(src.pitch() == 4);
    auto pal = std::make_shared<ColorTable>(256);
    (*pal)[1] = {255, 0, 0, 0};
    (*pal)[2] = {0, 255, 0, 0};
    (*pal)[3] = {0, 0, 255, 0};
    src.setPalette(pal);
    for (int y = 0; y < 2; ++y)
        for (int x = 0; x < 3; ++x) *src.pixelPtr(x, y) = uint8_t(x + 1);
    CHECK(dst.create(4, 3, 16));
    dst.clear(0x1234);
    const Rect clip{0, 1, 2, 3};
    dst.blitFrom(src, {-1, 1, 2, 3}, src.bounds(), &clip);
    const std::vector<uint16_t> converted = dst.toRgb555();
    CHECK(converted == std::vector<uint16_t>({0x1234, 0x1234, 0x1234, 0x1234,
                                             0x03e0, 0x001f, 0x1234, 0x1234,
                                             0x03e0, 0x001f, 0x1234, 0x1234}));
    Pixel::setPort(&dst);
    Pixel::resetClip();
    Pixel::pushClip();
    CHECK(Pixel::clipTo({1, 1, 3, 2}));
    Pixel::fillRect(-10, -10, 20, 20, colorRgb(255, 0, 0));
    const auto filled = dst.toRgb555();
    CHECK(filled[4] == 0x03e0 && filled[5] == 0x7c00 && filled[6] == 0x7c00 && filled[7] == 0x1234);
    CHECK(filled[1] == 0x1234 && filled[9] == 0x001f);
    Pixel::popClip();
    CHECK(Pixel::clip().width() == 4 && Pixel::clip().height() == 3);
    Pixel::setPort(nullptr);

    OffPort rgb565;
    CHECK(rgb565.create(1, 1, 16, PixelFormat::Rgb565));
    rgb565.clear(0xf81f);
    CHECK(rgb565.toRgb555()[0] == 0x7c1f);
    CHECK(pal->table16(PixelFormat::Rgb555)[2] == 0x03e0);
    CHECK(pal->table16(PixelFormat::Rgb565)[2] == 0x07e0);
    (*pal)[2] = {255, 255, 255, 0};
    CHECK(pal->table16(PixelFormat::Rgb555)[2] == 0x7fff);
    CHECK(pal->table16(PixelFormat::Rgb565)[2] == 0xffff);
    return true;
}

bool tileClipping() {
    // A 3x2 indexed TILE, padded rows, hotspot (1,1), and mode 0.
    std::vector<uint8_t> bytes(0x1a + 8, 0);
    bytes[0] = 2; bytes[2] = 2; bytes[4] = 3; bytes[6] = 4;
    bytes[10] = 1; bytes[12] = 1;
    bytes[0x1a] = 1; bytes[0x1b] = 2; bytes[0x1c] = 3;
    bytes[0x1e] = 4; bytes[0x1f] = 5; bytes[0x20] = 6;
    const TileView tile(bytes);
    CHECK(tile.valid());
    CHECK(tile.decode8() == std::vector<uint8_t>({1, 2, 3, 4, 5, 6}));
    uint32_t value = 0;
    CHECK(tile.pixelAt(2, 1, value) && value == 6);
    CHECK(!tile.pixelAt(3, 1, value));
    OffPort dst;
    CHECK(dst.create(3, 2, 8));
    dst.clear(9);
    Pixel::setPort(&dst);
    Pixel::resetClip();
    Pixel::setBlitMode(kBlit8to8);
    drawTile(tile, 0, 1, 0);
    CHECK(*dst.pixelPtr(0, 0) == 2 && *dst.pixelPtr(1, 0) == 3 && *dst.pixelPtr(2, 0) == 9);
    CHECK(*dst.pixelPtr(0, 1) == 5 && *dst.pixelPtr(1, 1) == 6 && *dst.pixelPtr(2, 1) == 9);
    Pixel::setPort(nullptr);
    return true;
}

bool input() {
    InputQueue& q = InputQueue::instance();
    q.clearKeys(); q.clearMouse();
    q.setMousePos(30, 40);
    q.pushMouse(kMouseLeftDown, 1, 2);
    q.pushMouse(kMouseRightDown, 3, 4);
    q.pushMouse(kMouseLeftDown, 5, 6);
    int x = 0, y = 0;
    CHECK(q.buttonDown(1, &x, &y, false) == 1 && x == 5 && y == 6);
    CHECK(q.buttonDown(1, &x, &y, true) == 1);
    CHECK(q.buttonDown(3, &x, &y, true) == 0 && x == 30 && y == 40);
    for (uint32_t key = 1; key <= 25; ++key) q.pushKey(key);
    CHECK(q.getKey() == 7);
    for (uint32_t key = 8; key <= 25; ++key) CHECK(q.getKey() == key);
    CHECK(q.getKey() == 0);

    CyGame& game = CyGame::instance();
    CHECK(game.init(64, 48, 16));
    InputState state;
    state.keys = {{SDLK_LEFT, SDL_SCANCODE_LEFT, KMOD_CTRL, true, false},
                  {SDLK_a, SDL_SCANCODE_A, KMOD_SHIFT, true, false},
                  {SDLK_ESCAPE, SDL_SCANCODE_ESCAPE, 0, false, false}};
    game.feedInput(state);
    CHECK(q.getKey() == (kKeyLeft | kKeyModCtrl));
    CHECK(q.getKey() == ('A' | kKeyModShift));
    CHECK(q.getKey() == 0);
    game.shutdown();
    return true;
}

bool firstClick() {
    CyGame& game = CyGame::instance();
    InputQueue& q = InputQueue::instance();
    q.clearKeys(); q.clearMouse();
    CHECK(game.init(64, 48, 16));
    InputState state;
    state.mouseX = 0; state.mouseY = 0;
    state.buttons = state.pressed = InputState::Left;
    game.feedInput(state);
    CHECK(q.buttonDown(1, nullptr, nullptr, true) == 1);
    CHECK(q.doubleClick(1, nullptr, nullptr, false) == 0);
    // Reinitializing must also discard a click from the preceding UI session.
    CHECK(game.init(64, 48, 16));
    game.feedInput(state);
    CHECK(q.buttonDown(1, nullptr, nullptr, true) == 1);
    CHECK(q.doubleClick(1, nullptr, nullptr, false) == 0);
    game.shutdown();
    return true;
}

bool menuEvents() {
    CHECK(CyGame::instance().init(64, 48, 16));
    constexpr uint32_t end = 0xffffffffu;
    const uint32_t words[] = {
        1000, 2, 0, 0, 64, 48, end,
        kItemButton, 2, 2, 3, 12, 10, 6, 42, 3, kStateReturnsId, end,
        kItemRadio, 2, 20, 3, 10, 10, 6, 43, 4, 7, end,
        kItemRadio, 2, 32, 3, 10, 10, 6, 44, 4, 7, end,
        end
    };
    auto menu = SMenu::fromWords(words);
    CHECK(menu && menu->items().size() == 3);
    menu->show();
    SMenuItem* button = menu->itemById(42);
    CHECK(button && menu->hitTest(3, 4) == button);
    CHECK(menu->hitTest(14, 4) == nullptr); // right edge is exclusive
    menu->setDisabled(button, true);
    CHECK(menu->hitTest(3, 4) == nullptr);
    menu->setDisabled(button, false);
    menu->setChecked(menu->itemById(43), true);
    menu->setChecked(menu->itemById(44), true);
    CHECK(!menu->itemById(43)->isChecked() && menu->itemById(44)->isChecked());

    InputQueue& q = InputQueue::instance();
    q.clearMouse(); q.clearKeys(); q.setButtonsHeld(1); q.setMousePos(3, 4);
    q.pushMouse(kMouseLeftDown, 3, 4);
    uint32_t hover = 0;
    CHECK(menu->process(&hover) && hover == 42 && menu->result() == 0);
    q.setButtonsHeld(0);
    q.pushMouse(kMouseLeftUp, 3, 4);
    CHECK(!menu->process(&hover) && menu->result() == 42);
    menu.reset();
    CHECK(SMenu::all().empty());
    SMenu::dirtyRects().clear();
    CyGame::instance().shutdown();
    return true;
}

} // namespace

int main() {
    bool ok = true;
    for (auto test : {raster, tileClipping, input, firstClick, menuEvents}) ok = test() && ok;
    std::puts(ok ? "engine: raster, TILE, input and SMenu checks passed" : "engine: FAILED");
    return ok ? 0 : 1;
}
