// text_table.cpp - STRT string-table decoding.
#include "formats/text_table.h"

#include <cstring>

#include "formats/binary.h"

namespace dl2 {

bool decodeStringTable(std::span<const uint8_t> data, std::vector<std::string>& out, std::string* err) {
    out.clear();
    if (data.size() < 4) return bin::fail(err, "STRT too short");
    const uint32_t count = bin::u32le(data.data());
    if (data.size() < 4 + size_t(count) * 2) return bin::fail(err, "STRT offset table truncated");

    out.reserve(count);
    for (uint32_t i = 0; i < count; ++i) {
        const size_t off = bin::u16le(data.data() + 4 + size_t(i) * 2);
        if (off >= data.size()) return bin::fail(err, "STRT string " + std::to_string(i) + " offset out of range");
        const char* s = reinterpret_cast<const char*>(data.data() + off);
        out.emplace_back(s, strnlen(s, data.size() - off));
    }
    return true;
}

}  // namespace dl2
