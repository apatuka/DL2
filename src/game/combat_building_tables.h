// Exact225 signed words at004cfd68 in DEADLOCK.EXE.
// SHA256 7da13cf4ac15c2d6004a0e2172a525b9f1d27a0cb1d73590dd1fadff5d453a58.
//004513b8 reads [x*15+y]; never inferred from a rectangular footprint.
#pragma once
#include <array>
#include <cstdint>
namespace dl2::simulation::combat_building_tables {
inline constexpr std::array<int32_t,225> kSeaPlatformMask{{
    0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,
    0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,
    0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,
    0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
    1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,
    0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
    0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,
    0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,
    0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,
}};
} // namespace dl2::simulation::combat_building_tables
