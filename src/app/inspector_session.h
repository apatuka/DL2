// Owning read-only application session. Loading a file never activates gameplay.
#pragma once
#include <filesystem>
#include <memory>
#include <string>

#include "game/world_view.h"

namespace dl2::app {

class InspectorSession {
public:
    static constexpr worldview::Rect kMapViewport{8, 76, 410, 298};

    // Failure changes only status/failed, preserving prior source, document,
    // selection and camera. A successful load resets camera and selection.
    bool load(const std::filesystem::path& path);
    bool loadScenario(const std::filesystem::path& base, const std::string& entry);
    bool reload();
    // Publish a new file exclusively; source never changes, even on success.
    bool saveCopy(const std::filesystem::path& newPath);

    const save::Document* document() const { return document_.get(); }
    const std::string& sourceLabel() const { return sourceLabel_; }
    const std::string& status() const { return status_; }
    bool failed() const { return failed_; }
    worldview::SelectionModel& selection() { return selection_; }
    const worldview::SelectionModel& selection() const { return selection_; }
    worldview::Camera& camera() { return camera_; }
    const worldview::Camera& camera() const { return camera_; }
    void fit();

private:
    bool loadSource(const std::filesystem::path& path, const std::string& entry, bool archive);
    bool fail(std::string message);

    std::unique_ptr<save::Document> document_;
    std::filesystem::path sourcePath_;
    std::string sourceEntry_;
    bool sourceIsArchive_ = false;
    std::string sourceLabel_;
    std::string status_ = "Open a save or scenario. Read-only world inspector.";
    bool failed_ = false;
    worldview::SelectionModel selection_;
    worldview::Camera camera_;
};

} // namespace dl2::app
