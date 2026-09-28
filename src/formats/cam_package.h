// cam_package.h - reader for Cyberlore "CYLBPC" .CAM resource packages (tagged sections of named or indexed entries).
#pragma once
#include <cstdint>
#include <cstdio>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

namespace dl2 {

struct CamEntry {
    std::string name;     // entry name; for unnamed sections (flags bit0) the decimal index
    uint32_t offset = 0;  // absolute file offset of the payload
    uint32_t size = 0;    // payload size in bytes
    uint32_t index = 0;   // position inside its section
};

struct CamSection {
    std::string tag;      // 4-character tag: PALT, IMAG, TILE, PICT, WAVE, SMNU, STRT, FONT
    uint32_t flags = 0;   // bit0: entries are unnamed (name field holds a u32 index)
    std::vector<CamEntry> entries;
};

class CamPackage {
public:
    bool open(const std::string& path, std::string* err = nullptr);
    bool isOpen() const { return file_ != nullptr; }
    const std::string& path() const { return path_; }

    const std::vector<CamSection>& sections() const { return sections_; }
    const CamSection* section(std::string_view tag) const;
    const CamEntry* find(std::string_view tag, std::string_view name) const;
    const CamEntry* find(std::string_view tag, size_t index) const;

    // Whole payload of an entry. Empty vector on error.
    std::vector<uint8_t> read(const CamEntry& entry, std::string* err = nullptr) const;
    std::vector<uint8_t> read(std::string_view tag, std::string_view name, std::string* err = nullptr) const;
    std::vector<uint8_t> read(std::string_view tag, size_t index, std::string* err = nullptr) const;
    // First min(bytes, entry.size) bytes of a payload (cheap peek for listings).
    std::vector<uint8_t> readHead(const CamEntry& entry, size_t bytes) const;

private:
    struct FileCloser { void operator()(std::FILE* f) const { if (f) std::fclose(f); } };
    bool readAt(uint32_t offset, void* dst, size_t bytes) const;

    std::unique_ptr<std::FILE, FileCloser> file_;
    std::string path_;
    std::vector<CamSection> sections_;
};

}  // namespace dl2
