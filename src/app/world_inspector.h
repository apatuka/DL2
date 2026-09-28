// New read-only overview UI, not the original settlement renderer or game loop.
#pragma once
#include <filesystem>
#include <string>
#include <string_view>
#include "app/inspector_session.h"
#include "engine/offport.h"
#include "engine/resources.h"
#include "platform/sdl_input.h"
#include "sprites/sprite_bank.h"

namespace dl2::app {
inline std::filesystem::path pathFromUtf8(std::string_view value) {
    return std::filesystem::path(std::u8string(value.begin(), value.end()));
}
enum class InspectorAction { None, Quit, Reload, SaveCopy };
class WorldInspector {
public:
    bool initialize(const std::filesystem::path& dataDirectory, std::string& error);
    InspectorAction input(InspectorSession& session, const InputState& input);
    void draw(InspectorSession& session);
    const engine::OffPort& screen() const { return screen_; }
    bool ownerColors() const { return ownerColors_; }
private:
    void text(int x, int y, int width, const std::string& value,
              engine::ColorRef color, bool title = false);
    void preview(const save::Document&, const worldview::Selection&);
    engine::ResourceManager resources_;
    engine::ResPtr smallFont_, titleFont_;
    engine::ColorTablePtr uiPalette_;
    sprites::SpriteBank sprites_;
    engine::OffPort screen_;
    bool ownerColors_ = false;
};

struct InspectorOptions {
    std::filesystem::path dataDirectory;
    std::filesystem::path loadFile;
    std::string scenario;
    std::filesystem::path screenshot; // Optional automation output; must not exist.
    int smokeFrames = 0;
};
int runWorldInspector(const InspectorOptions& options);
} // namespace dl2::app
