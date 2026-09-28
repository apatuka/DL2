// cam_package.cpp - CYLBPC directory parsing and on-demand payload reads for .CAM packages.
#include "formats/cam_package.h"

#include <cstring>

#include "formats/binary.h"

namespace dl2 {

namespace {
constexpr size_t kHeaderSize = 20;    // magic[8] + u16 major + u16 minor + u32 sections + u32 dirSize
constexpr size_t kSectionRec = 8;     // char tag[4] + u32 offset
constexpr size_t kEntryRec = 28;      // char name[20] + u32 offset + u32 size
constexpr uint32_t kMaxSections = 64;
constexpr uint32_t kMaxEntries = 1u << 20;
}  // namespace

bool CamPackage::readAt(uint32_t offset, void* dst, size_t bytes) const {
    if (!file_) return false;
    if (std::fseek(file_.get(), static_cast<long>(offset), SEEK_SET) != 0) return false;
    return std::fread(dst, 1, bytes, file_.get()) == bytes;
}

bool CamPackage::open(const std::string& path, std::string* err) {
    sections_.clear();
    file_.reset(std::fopen(path.c_str(), "rb"));
    path_ = path;
    if (!file_) return bin::fail(err, "cannot open " + path);

    uint8_t hdr[kHeaderSize];
    if (!readAt(0, hdr, sizeof hdr)) return bin::fail(err, "CAM header too short");
    if (std::memcmp(hdr, "CYLBPC  ", 8) != 0) return bin::fail(err, "not a CYLBPC package: " + path);
    const uint16_t major = bin::u16le(hdr + 8);
    if (major != 1) return bin::fail(err, "unsupported CAM version " + std::to_string(major));
    const uint32_t numSections = bin::u32le(hdr + 12);
    if (numSections > kMaxSections) return bin::fail(err, "implausible section count");

    std::vector<uint8_t> table(size_t(numSections) * kSectionRec);
    if (!table.empty() && !readAt(kHeaderSize, table.data(), table.size()))
        return bin::fail(err, "CAM section table truncated");

    sections_.reserve(numSections);
    for (uint32_t s = 0; s < numSections; ++s) {
        const uint8_t* rec = table.data() + size_t(s) * kSectionRec;
        CamSection sec;
        sec.tag.assign(reinterpret_cast<const char*>(rec), 4);
        const uint32_t secOff = bin::u32le(rec + 4);

        uint8_t secHdr[8];
        if (!readAt(secOff, secHdr, sizeof secHdr)) return bin::fail(err, "CAM section " + sec.tag + " unreadable");
        const uint32_t count = bin::u32le(secHdr);
        sec.flags = bin::u32le(secHdr + 4);
        if (count > kMaxEntries) return bin::fail(err, "implausible entry count in " + sec.tag);

        std::vector<uint8_t> dir(size_t(count) * kEntryRec);
        if (!dir.empty() && !readAt(secOff + 8, dir.data(), dir.size()))
            return bin::fail(err, "CAM directory of " + sec.tag + " truncated");

        sec.entries.reserve(count);
        for (uint32_t i = 0; i < count; ++i) {
            const uint8_t* e = dir.data() + size_t(i) * kEntryRec;
            CamEntry ent;
            if (sec.flags & 1) {
                ent.name = std::to_string(bin::u32le(e));
            } else {
                const size_t len = strnlen(reinterpret_cast<const char*>(e), 20);
                ent.name.assign(reinterpret_cast<const char*>(e), len);
            }
            ent.offset = bin::u32le(e + 20);
            ent.size = bin::u32le(e + 24);
            ent.index = i;
            sec.entries.push_back(std::move(ent));
        }
        sections_.push_back(std::move(sec));
    }
    return true;
}

const CamSection* CamPackage::section(std::string_view tag) const {
    for (const CamSection& s : sections_)
        if (s.tag == tag) return &s;
    return nullptr;
}

const CamEntry* CamPackage::find(std::string_view tag, std::string_view name) const {
    const CamSection* s = section(tag);
    if (!s) return nullptr;
    for (const CamEntry& e : s->entries)
        if (e.name == name) return &e;
    return nullptr;
}

const CamEntry* CamPackage::find(std::string_view tag, size_t index) const {
    const CamSection* s = section(tag);
    if (!s || index >= s->entries.size()) return nullptr;
    return &s->entries[index];
}

std::vector<uint8_t> CamPackage::read(const CamEntry& entry, std::string* err) const {
    std::vector<uint8_t> out(entry.size);
    if (entry.size && !readAt(entry.offset, out.data(), out.size())) {
        out.clear();
        bin::fail(err, "cannot read CAM entry " + entry.name);
    }
    return out;
}

std::vector<uint8_t> CamPackage::read(std::string_view tag, std::string_view name, std::string* err) const {
    const CamEntry* e = find(tag, name);
    if (!e) { bin::fail(err, "no entry " + std::string(tag) + "/" + std::string(name)); return {}; }
    return read(*e, err);
}

std::vector<uint8_t> CamPackage::read(std::string_view tag, size_t index, std::string* err) const {
    const CamEntry* e = find(tag, index);
    if (!e) { bin::fail(err, "no entry " + std::string(tag) + "#" + std::to_string(index)); return {}; }
    return read(*e, err);
}

std::vector<uint8_t> CamPackage::readHead(const CamEntry& entry, size_t bytes) const {
    if (bytes > entry.size) bytes = entry.size;
    std::vector<uint8_t> out(bytes);
    if (bytes && !readAt(entry.offset, out.data(), bytes)) out.clear();
    return out;
}

}  // namespace dl2
