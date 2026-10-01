// Small original DATA tables not emitted by extract_tables.py yet.
// Canonical ownership is data::; legacy headers only alias these declarations.
#pragma once
#include <cstdint>
#include "game/data_tables.h"

namespace dl2::data {
extern const int32_t kSiteOrder[36];              // 004c5e58, FindConstructionSite
extern const int32_t kMetalForSteel[4];           // 004d6334
extern const int32_t kMetalSteelValue[4];         // 004d6344
extern const int32_t kAssistantPriority[23];      // 004c53f4
extern const int32_t kSkillMoraleAdjust[5];       // 004c52c8
extern const char* const kUnitShortNames[39];     // 005095e4, CreateUnit (not full UnitName)
extern const char* const kMaterialUnitNames[11];  // 005090f0
extern const char* const kDepositNames[5];        // 00509304, random(5) at 0047ce94
extern const char* const kAmountNames[6];         // 00509318 immediately follows deposit names
extern const int32_t kDepositTerrainValue[8];     // 004d5034
extern const char* const kRaceUpperNames[7];      // 004d5188
extern const int32_t kLandingTerrainScore[6];     // 004b7d5c
} // namespace dl2::data
