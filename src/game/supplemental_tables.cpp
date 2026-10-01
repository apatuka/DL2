// Byte-checked against DEADLOCK.EXE v1.20 at the addresses in the header.
// These values previously existed only in the excluded economy table duplicate,
// or as unresolved turn/newgame declarations. No executable callbacks here.
#include "game/supplemental_tables.h"

namespace dl2::data {
const int32_t kSiteOrder[36] = {14,15,20,21,8,9,13,16,19,22,26,27,28,25,7,10,2,3,12,18,17,23,32,33,1,4,6,11,24,29,31,34,0,5,30,35};
const int32_t kMetalForSteel[4] = {7,5,6,4};
const int32_t kMetalSteelValue[4] = {10,5,5,1};
const int32_t kAssistantPriority[23] = {2,21,23,24,25,26,27,14,12,15,5,17,19,7,10,4,9,3,16,6,18,8,13};
const int32_t kSkillMoraleAdjust[5] = {-10,-5,0,5,10};
const char* const kUnitShortNames[39] = {"No Unit","Laser Squad","Trooper","Trooper.","Trooper","Cannon","Cannon","Cannon","Cannon","Fighter","Bomber","Spyjet","Transport","Dreadnought","Carrier","Commander","Warhead","Warhead","Warhead","Defense","Defense","Defense","Defense","Militia","Scout","Colonizer","Medic","AAV","Air Command","Destroyer","Submarine","Sea Colonizer","Sea Fort","Sea Command","Flak Ship","Siege Cruiser","Siege Missile","Land Mine","Sea Mine"};
const char* const kMaterialUnitNames[11] = {"credits","tons of food","KW of energy","tons of wood","tons of iron","tons of steel","tons of endurium","tons of triidium","electronic components","anti-matter pods","art objects"};
const char* const kDepositNames[5] = {"iron deposit","endurium deposit","energy deposit","fertile plot","hardwood grove"};
const char* const kAmountNames[6] = {"no","almost no","noticeable amounts of","sizable amounts of","tremendous amounts of","horrible amounts of"};
const int32_t kDepositTerrainValue[8] = {0,0,1,3,4,0,2,0};
const char* const kRaceUpperNames[7] = {"CHCHT","CYTH","HUMAN","MAUG","RELU","TARTH","UVA"};
const int32_t kLandingTerrainScore[6] = {0,8,8,3,5,0};
} // namespace dl2::data
