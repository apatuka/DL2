// palette.cpp - PALT palette decoding.
#include "formats/palette.h"

#include "formats/binary.h"

namespace dl2 {

namespace {
constexpr size_t kPaltHeader = 12;
constexpr size_t kPaltEntries = 255;
}  // namespace

bool decodePalt(std::span<const uint8_t> data, Palette& out, std::string* err) {
    if (data.size() < kPaltHeader + kPaltEntries * 4)
        return bin::fail(err, "PALT too short (" + std::to_string(data.size()) + " bytes)");
    for (size_t i = 0; i < kPaltEntries; ++i) {
        const uint8_t* q = data.data() + kPaltHeader + i * 4;
        out.colors[i] = Rgb{q[0], q[1], q[2]};
    }
    out.colors[255] = Rgb{255, 255, 255};
    return true;
}

}  // namespace dl2
