// text_table.h - STRT string-table decoder (deadtext.cam): u32 count; u16 offsets[count]; NUL-terminated strings.
#pragma once
#include <cstdint>
#include <span>
#include <string>
#include <vector>

namespace dl2 {

// Offsets are relative to the start of the payload (the first one equals 4 + 2 * count).
bool decodeStringTable(std::span<const uint8_t> data, std::vector<std::string>& out, std::string* err = nullptr);

}  // namespace dl2
