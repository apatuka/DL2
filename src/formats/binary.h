// binary.h - little/big-endian byte readers and a whole-file loader shared by the format decoders.
#pragma once
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <string>
#include <vector>

namespace dl2::bin {

inline uint16_t u16le(const uint8_t* p) { return static_cast<uint16_t>(p[0] | (p[1] << 8)); }
inline uint32_t u32le(const uint8_t* p) {
    return uint32_t(p[0]) | (uint32_t(p[1]) << 8) | (uint32_t(p[2]) << 16) | (uint32_t(p[3]) << 24);
}
inline uint16_t u16be(const uint8_t* p) { return static_cast<uint16_t>((p[0] << 8) | p[1]); }
inline uint32_t u32be(const uint8_t* p) {
    return (uint32_t(p[0]) << 24) | (uint32_t(p[1]) << 16) | (uint32_t(p[2]) << 8) | uint32_t(p[3]);
}

// Sets *err (when non-null) and returns false; lets decoders write `return fail(err, "...")`.
inline bool fail(std::string* err, const std::string& msg) {
    if (err) *err = msg;
    return false;
}

// Reads a whole file into `out`. Returns false (with message) if it cannot be opened.
inline bool readFile(const std::string& path, std::vector<uint8_t>& out, std::string* err = nullptr) {
    std::FILE* f = std::fopen(path.c_str(), "rb");
    if (!f) return fail(err, "cannot open " + path);
    std::fseek(f, 0, SEEK_END);
    long size = std::ftell(f);
    std::fseek(f, 0, SEEK_SET);
    if (size < 0) { std::fclose(f); return fail(err, "cannot size " + path); }
    out.resize(static_cast<size_t>(size));
    size_t got = size ? std::fread(out.data(), 1, out.size(), f) : 0;
    std::fclose(f);
    if (got != out.size()) return fail(err, "short read on " + path);
    return true;
}

}  // namespace dl2::bin
