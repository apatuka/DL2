#include "app/inspector_session.h"
#include "game/save_files.h"

#include <exception>
#include <system_error>
#include <utility>

namespace dl2::app {
namespace {
namespace fs = std::filesystem;

std::string ascii(const std::string& text) {
    return worldview::boundedText(text.data(), text.size());
}

std::string pathLabel(const fs::path& path) {
    const auto bytes = path.u8string();
    return worldview::boundedText(reinterpret_cast<const char*>(bytes.data()), bytes.size());
}

std::string detail(const save::Error& error) {
    return " at byte " + std::to_string(error.offset) + ": " + ascii(error.message);
}

void chooseInitialSelection(const save::Document& d, worldview::SelectionModel& selection) {
    bool selected = false;
    if (d.header.isMap != 1) {
        const int local = d.options.localPlayer;
        if (local >= 0 && local < kMaxPlayers) {
            const int home = d.players[size_t(local)].homeTerritory;
            if (home > 0) selected = selection.selectTerritory(d, uint32_t(home));
        }
        if (!selected) {
            for (uint32_t index = 1; index <= d.world.numTerritories; ++index) {
                if (!worldview::objectsInTerritory(d, index).empty()) {
                    selected = selection.selectTerritory(d, index);
                    if (selected) break;
                }
            }
        }
    }
    if (!selected) selection.selectTerritory(d, 1);
    selection.cycleObject(d, 1);
}

} // namespace

bool InspectorSession::fail(std::string message) {
    status_ = std::move(message);
    failed_ = true;
    return false;
}

bool InspectorSession::loadSource(const fs::path& path, const std::string& entry, bool archive) {
    try {
        std::error_code pathError;
        auto absolute = fs::absolute(path, pathError);
        if (pathError) return fail("Cannot resolve source path: " + ascii(pathError.message()));
        auto candidate = std::make_unique<save::Document>();
        save::Error error;
        const bool loaded = archive ? save::readScenario(absolute, entry, *candidate, error)
                                    : save::readDocument(absolute, *candidate, error);
        if (!loaded) return fail("Load failed" + detail(error));

        worldview::SelectionModel selected;
        worldview::Camera camera;
        chooseInitialSelection(*candidate, selected);
        camera.fit(*candidate, kMapViewport);
        auto label = pathLabel(absolute);
        if (archive) label += " :: " + ascii(entry);
        auto storedEntry = entry;
        auto success = std::string(candidate->header.isMap == 1 ? "Loaded map. " : "Loaded save. ") +
                       "Read-only inspection; turns and movement are disabled.";

        // Everything potentially allocating above completes before commit. All
        // members below are swapped/moved from local values; old session survives
        // read/parse failures and source aliases such as reload(sourcePath_).
        document_.swap(candidate);
        sourcePath_.swap(absolute);
        sourceEntry_.swap(storedEntry);
        sourceLabel_.swap(label);
        status_.swap(success);
        sourceIsArchive_ = archive;
        selection_ = selected;
        camera_ = camera;
        failed_ = false;
        return true;
    } catch (const std::exception& error) {
        return fail("Load failed: " + ascii(error.what()));
    }
}

bool InspectorSession::load(const fs::path& path) {
    return loadSource(path, {}, false);
}

bool InspectorSession::loadScenario(const fs::path& base, const std::string& entry) {
    return loadSource(base, entry, true);
}

bool InspectorSession::reload() {
    if (!document_) return fail("No document to reload.");
    return loadSource(sourcePath_, sourceEntry_, sourceIsArchive_);
}

bool InspectorSession::saveCopy(const fs::path& newPath) {
    if (!document_) return fail("No document to save.");
    try {
        auto success = "Saved unchanged copy: " + pathLabel(newPath);
        save::Error error;
        if (!save::writeDocumentCopy(newPath, *document_, error))
            return fail("Save failed" + detail(error));
        status_.swap(success);
        failed_ = false;
        return true;
    } catch (const std::exception& error) {
        return fail("Save failed: " + ascii(error.what()));
    }
}

void InspectorSession::fit() {
    if (document_) camera_.fit(*document_, kMapViewport);
}

} // namespace dl2::app
