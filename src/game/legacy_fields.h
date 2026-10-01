// Shared legacy scalar contracts. The tech wrapper is gs-only; it is not an
// accessor for save::Document. These functions never interpret file Ptr32 words.
#pragma once
#include <bit>
#include <cstdint>
#include "game/globals.h"

namespace dl2 {
// Original Army +0x25 / +0x2c, shared by AI and combat readers.
inline uint8_t& armyMission(Army& a) { return a.unk_25; }
inline int16_t& armyDamage(Army& a) { return a.unk_2c; }

namespace legacy {
// MOVSX knownMask16, SHL32 by CL: the hardware masks the shift to five bits.
// Evidence: 0044c654, 0044e7ec and 00447190. Use unsigned math to avoid 1<<31 UB.
constexpr bool techMaskContains(uint16_t knownMask, int player) {
    const auto extended = uint32_t(int32_t(std::bit_cast<int16_t>(knownMask)));
    return (extended & (uint32_t{1} << (uint32_t(player) & 31u))) != 0;
}
} // namespace legacy

// Legacy callers must supply a valid tech table index; owner bits retain the
// original signed-mask/shift semantics even for malformed player values.
inline bool techKnown(int tech, int player) {
    return legacy::techMaskContains(gs.techs[tech].knownMask, player);
}
} // namespace dl2
