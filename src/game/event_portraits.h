// Event portrait selection lists from DEADLOCK.EXE, table 004ca3b0.
// EventDef categories plus pact-offer15/public pact-break20; races0..6. Not pointers.
#pragma once
#include <cstdint>
#include <span>
#include <string_view>
namespace dl2::data {
std::span<const std::string_view> eventPortraitNames(int race, int category);
// orig:0045046c /49 pointers at004cac00. Empty for same race or race7/8.
std::string_view eliminationPortrait(int observerRace, int defeatedRace);
}
