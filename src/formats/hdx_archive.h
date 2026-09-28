// hdx_archive.h - reader for the BASE/LEVELS/CHAT/SCRIPT/DIFF/SOUND .HDX index + .HDD data file pairs.
#pragma once
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

namespace dl2 {

struct HdxEntry {
    std::string name;     // up to 8 characters
    uint32_t offset = 0;  // absolute offset in the .HDD of the u32 length prefix
};

class HdxArchive {
public:
    // basePath is the pair's path without extension ("C:/.../BASE"); ".HDX" and ".HDD" are appended.
    bool open(const std::string& basePath, std::string* err = nullptr);

    const std::vector<HdxEntry>& entries() const { return entries_; }
    const HdxEntry* find(std::string_view name) const;

    // Payload length stored in the .HDD (0 on error).
    uint32_t payloadSize(const HdxEntry& entry) const;
    // Payload bytes (length prefix stripped). Empty vector on error.
    std::vector<uint8_t> read(const HdxEntry& entry, std::string* err = nullptr) const;
    std::vector<uint8_t> read(std::string_view name, std::string* err = nullptr) const;

    const std::string& hddPath() const { return hddPath_; }

private:
    std::string hddPath_;
    std::vector<HdxEntry> entries_;
};

}  // namespace dl2
