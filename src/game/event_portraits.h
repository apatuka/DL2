// Event portrait selection lists from DEADLOCK.EXE, table 004ca3b0.
// Only categories referenced by canonical EventDef; races 0..6. Not pointers.
#pragma once
#include <cstdint>
#include <span>
#include <string_view>
namespace dl2::data {
std::span<const std::string_view> eventPortraitNames(int race, int category);
}
