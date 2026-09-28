// hdx_archive.cpp - HDX index parsing and length-prefixed payload reads from the matching HDD file.
#include "formats/hdx_archive.h"

#include <cstdio>
#include <cstring>

#include "formats/binary.h"

namespace dl2 {

bool HdxArchive::open(const std::string& basePath, std::string* err) {
    entries_.clear();
    hddPath_ = basePath + ".HDD";

    std::vector<uint8_t> idx;
    if (!bin::readFile(basePath + ".HDX", idx, err)) return false;
    if (idx.size() < 4) return bin::fail(err, "HDX too short");

    const uint32_t count = bin::u32le(idx.data());
    if (idx.size() < 4 + size_t(count) * 12) return bin::fail(err, "HDX truncated index");

    entries_.reserve(count);
    for (uint32_t i = 0; i < count; ++i) {
        const uint8_t* p = idx.data() + 4 + size_t(i) * 12;
        HdxEntry e;
        const size_t len = strnlen(reinterpret_cast<const char*>(p), 8);
        e.name.assign(reinterpret_cast<const char*>(p), len);
        e.offset = bin::u32le(p + 8);
        entries_.push_back(std::move(e));
    }
    return true;
}

const HdxEntry* HdxArchive::find(std::string_view name) const {
    for (const HdxEntry& e : entries_)
        if (e.name == name) return &e;
    return nullptr;
}

uint32_t HdxArchive::payloadSize(const HdxEntry& entry) const {
    std::FILE* f = std::fopen(hddPath_.c_str(), "rb");
    if (!f) return 0;
    uint8_t len[4];
    uint32_t size = 0;
    if (std::fseek(f, static_cast<long>(entry.offset), SEEK_SET) == 0 && std::fread(len, 1, 4, f) == 4)
        size = bin::u32le(len);
    std::fclose(f);
    return size;
}

std::vector<uint8_t> HdxArchive::read(const HdxEntry& entry, std::string* err) const {
    std::vector<uint8_t> out;
    std::FILE* f = std::fopen(hddPath_.c_str(), "rb");
    if (!f) { bin::fail(err, "cannot open " + hddPath_); return out; }

    uint8_t len[4];
    if (std::fseek(f, static_cast<long>(entry.offset), SEEK_SET) != 0 || std::fread(len, 1, 4, f) != 4) {
        std::fclose(f);
        bin::fail(err, "cannot seek to entry " + entry.name);
        return out;
    }
    const uint32_t size = bin::u32le(len);
    out.resize(size);
    const size_t got = size ? std::fread(out.data(), 1, size, f) : 0;
    std::fclose(f);
    if (got != size) {
        out.clear();
        bin::fail(err, "short read on entry " + entry.name);
    }
    return out;
}

std::vector<uint8_t> HdxArchive::read(std::string_view name, std::string* err) const {
    const HdxEntry* e = find(name);
    if (!e) { bin::fail(err, "no HDX entry named " + std::string(name)); return {}; }
    return read(*e, err);
}

}  // namespace dl2
