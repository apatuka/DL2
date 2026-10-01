// economy.h - Módulo "economy" de DEADLOCK.EXE: territorios, edificios, producción, trabajo (labor),
// población, comida, moral, motines/revueltas, colas de producción, pools de edificios/ejércitos,
// logística de materiales y objetivos de campaña.
//
// Rangos portados: 0x4455fc-0x446000 (pool de ejércitos), 0x446084-0x4474b0 (unidades en territorios,
// shrines, caminos), 0x447a40-0x448d94 (estadísticas de unidad y Colony Assistant de trabajo),
// 0x44b5bc-0x44fcd4 (edificios/producción), 0x44fd14-0x450380 (campaña), 0x450c38-0x450cb8 (mercado
// negro), 0x46a9d8-0x46c7d4 (población), 0x46e56c/0x46e6b8/0x46e730 (propiedad de territorios),
// 0x471a98-0x472ca0 (logística "Collect Material"), 0x474cfc/0x4750c4/0x47510c (IDs globales) y
// 0x484c2c-0x484fa0 (colas de producción).  Ver docs/ECONOMY.md.
//
// Convenciones: cada función lleva `// orig: FUN_xxxxxxxx (Nombre)`.  Los punteros del original son
// Ptr32<T> con índice 1-based (ver globals.h).  Los objetos de heap (QueueHead/QueueRecord) viven en
// pools de este módulo (queues.cpp) con índices 1-based en los Ptr32.
#pragma once
#include <cstdint>
#include <functional>
#include <array>
#include <span>

#include "game/game_state.h"
#include "game/globals.h"
#include "game/queue_pool.h"   // pool de QueueHead/QueueRecord (módulo gameflow): dl2::ptr(Ptr32<QueueHead>), QueueAlloc...
#include "game/data_tables.h"
#include "game/supplemental_tables.h"
#include "game/table_views.h"
#include "game/legacy_fields.h"

namespace dl2::econ {

// ----------------------------------------------------------------------------------------
// Constantes del original
// ----------------------------------------------------------------------------------------
// Valores de Building::task[] (tabla kBuildingTaskNames es 0-based: valor = índice + 2).
namespace task {
constexpr uint8_t None = 0, Idle = 1, Construction = 2, MineIron = 3, MineEndurium = 4, Research = 5,
    ElectronicParts = 6, Culture = 7, CreateArt = 8, IronToSteel = 9, EnduriumToTriidium = 10,
    BuildUnits = 11, Food = 12, Wood = 13, Trade = 14, Energy = 15, AntiMatterPods = 16, Clone = 17,
    TrainUnits = 18, HealMilitia = 19, HousePopulace = 20, Upgrade = 21;
}
// Building::category (BuildingTypeDef+7).
namespace cat {
constexpr uint8_t None = 0, Farm = 1, Mine = 2, Energy = 3, Factory = 4, Research = 5, Culture = 6,
    Port = 7, Airport = 8, CityCenter = 9, MissileBase = 10, Shrine = 11, FuelDepot = 12, Cloning = 13,
    Hospital = 14, Training = 15, Weather = 16, Housing = 17, Defense = 18, Bunker = 19,
    SeaPlatform = 20;
}
// Building::flags
namespace bflag {
constexpr uint16_t Built = 0x0002, Active = 0x0004, Site = 0x0020, Announced = 0x0040;
inline uint16_t Locked(int slot) { return uint16_t(0x100u << slot); }   // trabajo bloqueado en la ranura
}
// Territory::flags
namespace tflag {
constexpr uint32_t Capital = 0x1, ShrinePlaced = 0x10, Plague = 0x20, Poisoned = 0x40, NoTiles = 0x100;
inline uint32_t PathVisited(int player) { return 0x2000u << player; }
}
// BuildingSite::terrainFlags
namespace sflag {
constexpr uint16_t TerrainMask = 0x00ff, PlatformFree = 0x0100, PlatformUsed = 0x0200, HiMask = 0x0f00;
}
// Misiones de unidad (Army+0x25, tabla PTR_s_No_Mission_00509dcc; ver ai_taskforce.h Mission)
namespace mission {
constexpr uint8_t None = 0, Patrol = 0x0a, Repair = 0x0b, Suppress = 0x0d, Train = 0x0e;
}
// Dominio de unidad (UnitTypeDef+0x11)
namespace domain { constexpr int8_t Land = 1, Sea = 2, Air = 3; }

constexpr int kMaterialCap = 10000;      // FUN_0046c780 / FUN_00472974
constexpr int kNumQueues = 5;
constexpr int kNumCampaigns = data::kNumCampaigns; // All 43 records, including no-campaign row 0.

// ----------------------------------------------------------------------------------------
// Legacy row adapters derived from data::* (economy_tables.cpp). Not SAV layouts.
// Field spellings are retained for excluded legacy consumers; values have one source.
// ----------------------------------------------------------------------------------------
struct BldgType {              // DAT_004f9dbc, 48 x 0x32 (kBuildingTypes)
    const char* name;          // +0x00
    uint16_t sprite;           // +0x04
    uint8_t  icon;             // +0x06
    uint8_t  category;         // +0x07 -> Building::category
    uint8_t  maxLabor;         // +0x08 colonos máximos
    uint8_t  size;             // +0x09 1, 2 ó 5 (Sea Platform)
    uint16_t work;             // +0x0a trabajo de construcción (Building::turnsLeft inicial)
    int8_t   energyUse;        // +0x0c energía consumida por turno
    uint8_t  unk0d;            // +0x0d
    int16_t  rate[5];          // +0x0e % base de producción por ranura (ranura 0 = construcción)
    uint8_t  task[5];          // +0x18 tarea por ranura (task::*), ranura 0 = principal
    uint8_t  units[10];        // +0x1d unidades fabricables (0 = fin)
    int8_t   tech;             // +0x27 tecnología requerida (0 = ninguna)
    uint16_t unk28;            // +0x28
    int32_t  queueCat;         // +0x2a cola de producción de unidades 1..5 (0 = ninguna)
    int32_t  helpId;           // +0x2e
};
struct UnitType {              // PTR_s_No_Unit_004faf7c, 39 x 0x24 (kUnitTypes)
    const char* name;          // +0x00
    uint16_t sprite;           // +0x04
    uint16_t unk06;            // +0x06
    uint16_t unk08;            // +0x08
    uint8_t  unk0a;            // +0x0a
    uint8_t  unitClass;        // +0x0b -> Army::unitClass (1..0x14)
    uint16_t work;             // +0x0c trabajo de fabricación (cost[0])
    int8_t   maintenance;      // +0x0e coste de mantenimiento base (FUN_0046b4d0)
    int8_t   tech;             // +0x0f tecnología requerida (cost[12])
    int8_t   moves;            // +0x10 puntos de movimiento (FUN_00447190)
    int8_t   domain;           // +0x11 1 tierra, 2 mar, 3 aire
    int8_t   unk12;            // +0x12
    int8_t   attack;           // +0x13 (FUN_00447c2c)
    int8_t   defense;          // +0x14 (FUN_00447da4)
    int8_t   range;            // +0x15 legacy spelling: SPEED, not attack range (FUN_00447f44)
    int8_t   rof;              // +0x16 (FUN_00448008)
    int8_t   unk17;            // +0x17 squared attack range (FUN_004480a8)
    int32_t  unk18;            // +0x18 sound ID (full dword, not int16)
};
struct CampaignGoal {          // 0x44 bytes dentro de la tabla de campañas (DAT_004c61a0 + k*0x44)
    int32_t type;              // +0x00 0 ninguno, 1.. (FUN_0044fe38: 1 y 11 = "unidad")
    int32_t count;             // +0x04 nº de parámetros / turnos
    int32_t param[14];         // +0x08
    int32_t done;              // +0x40 (DAT_004c61e0) turno de cumplimiento / flag (se modifica en juego)
};
struct CampaignDef {           // DAT_004c6194 + camp*0xd8
    uint8_t  victory;          // +0x00 VictoryCondition
    int32_t  param1;           // +0x04 winCities (victory 0) / winShrines (victory 2)
    int32_t  param2;           // +0x08 winTurns (victory 2)
    CampaignGoal goal[3];      // +0x0c
};

extern const std::array<BldgType, data::kNumBuildingTypes> kBuildingTypes;
extern const std::array<UnitType, data::kNumUnitTypes> kUnitTypes;
inline constexpr data::MemberTableView<data::BuildingDef, data::kNumBuildingTypes, &data::BuildingDef::cost>
    kBuildingCosts{data::kBuildingTypes};
inline constexpr data::MemberTableView<data::UnitDef, data::kNumUnitTypes, &data::UnitDef::cost>
    kUnitCosts{data::kUnitTypes};
inline constexpr auto& kLaborYield = data::kLaborProductionTable;
using data::kSiteOrder;
inline constexpr auto& kGrowthByTerrain = data::kPopulationGrowthByTerrain;
inline constexpr auto& kCrowdingByTerrain = data::kTerrainMaxPopulation;
inline constexpr auto& kTaxIncomeByLevel = data::kTaxIncomePercent;
inline constexpr auto& kStarvationMorale = data::kMoraleByLevel;
using data::kTaxMoraleByLevel; // Exactly six levels, 0..5 (0046adac clamps).
using data::kMetalForSteel;
using data::kMetalSteelValue;
using data::kAssistantPriority;
using data::kSkillMoraleAdjust;
inline constexpr auto& kCityCenterCost = data::kBuildingTypes[37].cost;
inline constexpr auto& kCityCenterWork = data::kBuildingTypes[37].buildLabor;
inline constexpr auto& kCityCenterTech = data::kBuildingTypes[37].techRequired;
inline constexpr auto& kUnitGroupLimitLand = data::kMaxUnitsPerTerritoryLand; // 004faf6c, not terrain predicate
inline constexpr auto& kUnitGroupLimitSea = data::kMaxUnitsPerTerritorySea;   // 004faf5c
using data::kMaterialNames;
using data::kMaterialNamesLower;
inline constexpr std::span<const char* const, 20> kBuildingTaskNames{data::kTaskNames + 2, 20};
using data::kRaceNames;
using data::kUnitShortNames;
extern const std::array<CampaignDef, kNumCampaigns> kCampaignDefaults;
// Explicit LEGACY mutable bridge only, shared with turn/campaign headers.
// New owned runtime/document code must not use or mutate this global.
extern std::array<CampaignDef, kNumCampaigns> gCampaigns;
static_assert(sizeof(CampaignGoal) == 0x44 && sizeof(CampaignDef) == 0xd8);

// ----------------------------------------------------------------------------------------
// Accesores a campos de las structs que game_state.h todavía llama unk_XX
// ----------------------------------------------------------------------------------------
inline int8_t&   starvation(Territory& t)      { return reinterpret_cast<int8_t&>(t.unk_28[1]); }   // +0x29 nivel de hambruna 0..7
inline int16_t&  culture(Territory& t)         { return t.unk_2c; }                                   // +0x2c cultura producida
inline int16_t&  growthPct(Territory& t)       { return t.unk_32; }                                   // +0x32 % crecimiento último turno
inline uint8_t&  freeLaborShown(Territory& t)  { return reinterpret_cast<uint8_t&>(t.unk_36); }       // +0x36 (UI)
inline uint8_t&  powerLevel(Territory& t)      { return t.knowledge; }                                // +0x35 % energía satisfecha
inline int8_t&   taxLocal(Territory& t)        { return t.tradeState; }                               // +0x26 ajuste local de impuestos
inline int16_t&  moneyProduced(Territory& t)   { return t.taxAdjust; }                                // +0x2a créditos producidos (Trade)
inline int16_t&  researchProduced(Territory& t){ return t.tradeIncome; }                              // +0x2e investigación producida
inline int8_t&   visLevel(Territory& t, int p) { return reinterpret_cast<int8_t&>(t.unk_6d[p]); }     // +0x6d nivel de visión por jugador (12 = nada)
inline uint32_t& shrineFoundMask(Territory& t) { return *reinterpret_cast<uint32_t*>(&t.unk_8b0[0]); } // +0x8b0 jugadores que han hallado el shrine
inline int8_t&   foodWoodBonus(Territory& t)   { return reinterpret_cast<int8_t&>(t.unk_8b0[0xe4]); } // +0x994 % extra de comida/madera
inline int16_t&  pathDist(Territory& t, int p) { return *reinterpret_cast<int16_t*>(&t.unk_9b4[0xbc + p * 2]); } // +0xa70 distancia (FUN_00446440)
inline uint8_t&  repeatFlags(Territory& t)     { return t.hoverway; }                                 // +0x9ae bit k = repetir cola k
inline uint16_t& healPoints(Territory& t)      { return t.colonyFlag; }                               // +0x9b2 puntos de curación (Heal Militia)
inline uint32_t& supplierRaw(Territory& t)     { return *reinterpret_cast<uint32_t*>(&t.unk_ad6[0]); } // +0xad6 territorio proveedor (Ptr32)
inline int16_t&  supplierCost(Territory& t)    { return *reinterpret_cast<int16_t*>(&t.unk_ad6[4]); }  // +0xada coste de transporte por unidad
inline int16_t&  upgradeProgress(Building& b)  { return b.unk_16; }                                   // +0x16 trabajo de mejora acumulado
inline int16_t&  buildingParam10(Building& b)  { return b.unk_10; }                                   // +0x10 (_SetBuildingFlags)
inline uint8_t&  siteRoad(BuildingSite& s)     { return s.unk_05[0x0b]; }                             // +0x10 bits de carretera
inline int16_t&  siteRoadCost(BuildingSite& s) { return *reinterpret_cast<int16_t*>(&s.unk_05[0x0d]); } // +0x12
inline int16_t&  siteResource(BuildingSite& s, int k) { return *reinterpret_cast<int16_t*>(&s.unk_05[1 + k * 2]); } // +0x06.. 0 energía,1 comida,2 madera,3 hierro,4 endurium
inline uint8_t&  siteKnownRace(BuildingSite& s){ return s.unk_18[1]; }                                // +0x19 (fog of war)
inline uint8_t&  siteKnownType(BuildingSite& s){ return s.unk_18[2]; }                                // +0x1a
inline uint8_t&  siteKnownTurns(BuildingSite& s){ return s.unk_18[3]; }                               // +0x1b
inline uint8_t&  siteKnownHasBldg(BuildingSite& s){ return s.unk_18[4]; }                             // +0x1c
inline int32_t&  siteKnownLabor(BuildingSite& s, int k){ return *reinterpret_cast<int32_t*>(&s.unk_18[6 + k * 4]); } // +0x1e
inline uint16_t& siteKnownFlags(BuildingSite& s){ return *reinterpret_cast<uint16_t*>(&s.unk_18[0x1a]); } // +0x32
inline int16_t&  researchPoints(Player& p)     { return p.lastIncome; }                               // +0x40 investigación acumulada del turno
inline uint16_t& techKnown(int tech)           { return gs.techs[tech].knownMask; }
inline bool      techKnownBy(int tech, int player) { return dl2::techKnown(tech, player); }
inline int16_t   raceStat(int row, int race)   { return gs.raceStats.v[row][race]; }                  // DAT_00559e00[row][race]
inline Territory* terrOf(const Building& b)    { return &gs.territories[b.territory]; }
inline Player*    ownerOf(const Territory& t)  { return t.owner < 0 ? nullptr : &gs.players[t.owner]; }
inline int        terrIndex(const Territory* t){ return int(t - gs.territories); }
inline Territory* terrAt(int i)                { return &gs.territories[i]; }

// Argumento de evento del Event Log (LogEvent recibe enteros y punteros mezclados).
struct EventArg {
    enum Kind { Int, Str, Terr, Bldg, ArmyP, Ptr } kind = Int;
    int64_t i = 0;
    const void* p = nullptr;
    EventArg() = default;
    EventArg(int v) : kind(Int), i(v) {}
    EventArg(unsigned v) : kind(Int), i(v) {}
    EventArg(const char* s) : kind(Str), p(s) {}
    EventArg(const Territory* t) : kind(Terr), p(t) {}
    EventArg(Territory* t) : kind(Terr), p(t) {}
    EventArg(const Building* b) : kind(Bldg), p(b) {}
    EventArg(Building* b) : kind(Bldg), p(b) {}
    EventArg(const Army* a) : kind(ArmyP), p(a) {}
    EventArg(Army* a) : kind(ArmyP), p(a) {}
};

// ----------------------------------------------------------------------------------------
// Llamadas a otros módulos (event log, red, tecnología, dibujo de carreteras...).  Todas tienen un
// valor por defecto seguro; el integrador las apunta a las implementaciones reales.
// ----------------------------------------------------------------------------------------
struct Externals {
    // LogEvent (FUN_00423690) / LogEventEx (FUN_004237d0): (jugador, tipo, 4 args, p7, p8)
    std::function<void(int player, int type, EventArg a, EventArg b, EventArg c, EventArg d, int p7, int p8)> logEvent;
    // FUN_0047dfdc: recalcula carreteras/bits de casilla tras crear/borrar un edificio (módulo settlement view).
    std::function<void(Territory*)> recomputeSiteRoads;
    // FUN_00486964 CountShrines (módulo victoria).  Por defecto: port local.
    std::function<void()> countShrines;
    // FUN_00483d58 LearnTech(player, tech) (módulo tecnología).  Por defecto: sólo marca knownMask.
    std::function<void(int player, int tech)> learnTech;
    // FUN_00484114 (investigación del turno: Player, puntos).  Por defecto: no-op.
    std::function<void(Player*, int points)> applyResearch;
    // FindArtifact (0x46de44) al descubrir un shrine.  Por defecto: no-op.
    std::function<void(Territory*, int player)> findArtifact;
    // FUN_00471d34 "Not enough Stuff!" (UI).  Por defecto: no-op.
    std::function<void(const char* what, unsigned missingMask, const int32_t cost[13])> notEnoughStuff;
    // FUN_0040cd0c: fusión de task forces al embarcar (IA).  Por defecto: no-op.
    std::function<void(Army* transport, Army* cargo)> taskForceMerge;
    // RemoveArmyFromTaskForce (0x40adf4).  Por defecto: no-op.
    std::function<void(Army*)> removeArmyFromTaskForce;
    // FUN_0046e338 / FUN_0047dd24 / FUN_004837fc / FUN_0045ac80 (efectos de mar, sprites, UI) en FUN_0046e730.
    std::function<void()> afterMovePhaseUi;
    // Ruta de red de SyncCreateUnit / SyncCreateBuilding / SyncDisbandUnit / NetReassignLabor /
    // NetStartConstruction / NetDemolishBuilding.  Sólo se usan si gg.netGame != 0; por defecto se
    // ejecuta la ruta local.
    std::function<Army*(Territory*, int player, int unitType)> netCreateUnit;
    std::function<Building*(Territory*, int type)> netCreateBuilding;
    std::function<void(Army*)> netDisbandUnit;
    std::function<void(Territory*, Building* from, int fromSlot, Building* to, int toSlot)> netReassignLabor;
    std::function<Building*(Territory*, int type, int site)> netStartConstruction;
    std::function<void(Territory*, int site, int flag)> netDemolish;
};
extern Externals ext;

inline void LogEvent(int player, int type, EventArg a = {}, EventArg b = {}, EventArg c = {}, EventArg d = {}) {
    if (ext.logEvent) ext.logEvent(player, type, a, b, c, d, 0, 0);
}
inline void LogEventEx(int player, int type, EventArg a, EventArg b, EventArg c, EventArg d, int p7, int p8) {
    if (ext.logEvent) ext.logEvent(player, type, a, b, c, d, p7, p8);
}

// Aleatorios: rtl::rand()/rtl::lrand() (rtl_compat.h) y dl2::RandRangeTagged / rand2 / srand2 (gameflow.h).

// ----------------------------------------------------------------------------------------
// queues.cpp - colas de producción (sobre el pool de queue_pool.h) e IDs globales.
// QueueInit/QueueFree/QueueAppend/QueueCount/QueueFirst/QueueNext/QueueCurUnitType/QueueCurCount/
// QueueCurData ya están en dl2:: (queue_pool.cpp); aquí van las que faltaban.
// ----------------------------------------------------------------------------------------
void UnitList_Insert(QueueHead* q, const uint8_t rec[0x30]); // UnitList::Insert (0x484c74): inserta antes del cursor
void UnitList_Delete(QueueHead* q);                          // UnitList::Delete (0x484d2c): borra el nodo del cursor
int  QueuePopFront(QueueHead* q, uint8_t rec[0x30]);         // FUN_00484e24
void     QueueSetCurUnitType(QueueHead* q, uint8_t t);       // FUN_00484ef8
void     QueueSetCurCount(QueueHead* q, uint16_t n);         // FUN_00484f2c
void     QueueSetCurData(QueueHead* q, const int32_t data[11]); // FUN_00484f74
int  MilitiaTrainingBonus(Army* a, int* accum);              // FUN_00484fa0

uint16_t  NextGlobalId();                     // FUN_00474cfc
Building* FindBuildingByGlobalID(unsigned id); // FUN_004750c4
Army*     FindArmyByGlobalID(unsigned id);     // FUN_0047510c

// ----------------------------------------------------------------------------------------
// buildings.cpp - objetos Building, casillas, trabajo (labor), construcción, demolición
// ----------------------------------------------------------------------------------------
QueueHead* GetQueue(Territory* t, int queueCat);   // FUN_0044b5bc
QueueHead* BuildingQueue(Building* b);             // FUN_0044b620
int  TotalUnitLabor(Territory* t, int queueCat);   // TotalUnitLabor
int  TotalTaskLabor(Territory* t, int taskId);     // TotalTaskLabor
int  HousingSpareLabor(Territory* t);              // FUN_0044b7d8
int  MoveLaborToHousing(Territory* t, Building* b, int slot);        // MoveLaborToHousing (vía red)
void QueueNukeUse(Player* p, Territory* t);        // FUN_0044b8f8
void RegisterNukeUse(int player, Territory* t);    // FUN_0044b924
void FlushNukeQueue();                             // FUN_0044b9e4
int  TotalLabor(const Building* b);                // FUN_0044ba18
int  MaxLabor(const Building* b);                  // FUN_0044ba40
void ResetLaborToHousing(Territory* t);            // FUN_0044bacc
bool IsBuildTaskDifferent(Building* b, int slot, int labor1, int labor2); // IsBuildTaskDifferent
int  FindSlotToAddLabor(Building* b);              // FUN_0044bc68
int  FindSlotToRemoveLabor(Building* b);           // FUN_0044bd0c
int  AdjustLabor(Building* b, int delta);          // FUN_0044bddc
int  ActiveMaxLabor(const Building* b);            // FUN_0044be88
void BalanceLabor(Territory* t);                   // FUN_0044bea8
void BalanceLaborNoNet(Territory* t);              // FUN_0044c238
int  AllSlotsEmptyOrLocked(const Building* b);     // FUN_0044c248
int  AllTasksNoneOrLocked(const Building* b);      // FUN_0044c284
int  MoveOneLabor(Territory* t, Building* from, Building* to);           // FUN_0044c2c0
int  TransferLabor(Territory* t, Building* from, int fromSlot, Building* to, int toSlot); // FUN_0044c320
int  MoveLaborToHousingNoNet(Territory* t, Building* b, int slot);       // MoveLaborToHousingNoNet
void SetPortTarget(Territory* t, int16_t target);  // FUN_0044c3e4
void SetBuildingLabor(Building* b, const int32_t labor[5], uint8_t repeatFlags); // FUN_0044c3fc
void _SetBuildingFlags(Building* b, uint16_t flags, int16_t param10);    // FUN_0044c44c (_SetBuildingFlags)
void DistributeLabor(Building* b, int labor);      // FUN_0044c49c
int  CanUpgradeBuilding(Building* b);              // CanUpgradeBuilding
int  UpgradeCost(Building* b);                     // FUN_0044c718
int  HousedLabor(Territory* t);                    // FUN_0044c754
int  MoveHousingLabor(Territory* t, Building* b, int slot);  // MoveHousingLabor
int  MoveHousingLaborNet(Territory* t, Building* b, int slot); // FUN_0044c8ac
int  FirstTaskSlot(const Building* b);             // FUN_0044c978
void AssignLaborFromHousing(Territory* t, int count, Building* b); // FUN_0044c9a0
void InitBuildingPool();                           // FUN_0044ca34
void RebuildBuildingLists();                       // FUN_0044cabc (RebuildBuildingLists)
Building* AllocBuilding();                         // FUN_0044cbec (AllocBuilding)
void FreeBuilding(Building* b);                    // FUN_0044cc40
void ClearSiteArea(Territory* t, int col, int row, int size); // FUN_0044cce4
int  _DeleteBuilding(Territory* t, int site);      // _DeleteBuilding
void _DemolishBuilding(Player* p, Territory* t, int site); // _DemolishBuilding
int  CountBuildingsByCategory(Territory* t, int category);        // FUN_0044d034
int  CountFinishedByCategory(Territory* t, int category);         // FUN_0044d06c
int  CountBuildingsByType(Territory* t, int type);                // FUN_0044d0ac
int  ReplaceBuildingForType(Territory* t, int type);              // FUN_0044d0e4
int  FindBuildingByCategory(Territory* t, int category, int from);         // FUN_0044d1a4
int  FindFinishedByCategory(Territory* t, int category, int from);         // FUN_0044d1e4
int  FindActiveByCategory(Territory* t, int category, int from);           // FUN_0044d230
int  HasAdjacentLand(Territory* t);                // FUN_0044d284
int  HasAdjacentTerrain(Territory* t, int terrain);// FUN_0044d2f8
int  AreaHasResourceSite(Territory* t, int type, int site); // FUN_0044d36c
int  CanBuildAtSea(int type);                      // FUN_0044d3f4
int  IsSeaOnlyBuilding(int type);                  // FUN_0044d440
int  FindConstructionSite(Territory* t, int type); // FindConstructionSite
Territory* FindTerritoryWithSite(int player, int type); // FUN_0044d5a8
int  CheckConstructionSite(Territory* t, int type, int site); // FUN_0044d600 (0 = ok, 1..10 = motivo)
void PlaceBuildingOnSite(Territory* t, Building* b, int site, int size); // FUN_0044d7b4
void InitBuilding(Territory* t, Building* b, int type, int site, int16_t work); // FUN_0044d890 (InitBuilding)
int  FindPortTargetTerritory(Territory* t);        // FUN_0044da3c
Building* StartConstruction(Territory* t, int type, int site, uint16_t id); // FUN_0044db50
int  StartConstructionAuto(Territory* t, int type);// FUN_0044dcc8
Building* CreateBuilding(Territory* t, int type, uint16_t id, uint16_t habId, int site); // FUN_0044dcf4 (CreateBuilding)
void GetUnitCost(Player* p, int unitType, int32_t out[13]);     // FUN_0044ddf4
int  CountCityCenters(int player);                 // FUN_0044de48
void GetBuildingCost(Player* p, int type, int terrain, int32_t out[13]); // FUN_0044de9c
void GetCityCenterCost(Building* b, int32_t out[13]);            // FUN_0044df30
int  QueueUnit(Territory* t, Player* p, int unitType);           // FUN_0044df94
int  DequeueUnit(Territory* t, Player* p, int queueCat, int index); // FUN_0044e0a8
Building* NetStartConstruction(Territory* t, int type, int site); // FUN_0047597c (local: NextGlobalId + StartConstruction)
void NetDemolishBuilding(Territory* t, int site, int flag);      // FUN_00475a60 (local: _DemolishBuilding)
void NetReassignLabor(Territory* t, Building* from, int fromSlot, Building* to, int toSlot); // FUN_00475ce8 (local: TransferLabor)
unsigned NetQueueUnit(Territory* t, Player* p, int unitType);    // FUN_00475f80 (local: QueueUnit)
void NetSetPortTarget(Territory* t, int16_t target);             // FUN_00476324 (local: SetPortTarget)
void NetDisbandUnit(Army* a);                                    // FUN_00475854 (local: DisbandUnit)
// Instala en dl2::flow::cb (gameflow.h) los callbacks que este módulo implementa.
void InstallCallbacks();

// Colony Assistant (asignación automática de trabajo) 0x4483d0-0x448d94
struct TaskSummary {           // DAT_0056421c, 28 x 0x18
    Ptr32<Building> lastBuilding;  // +0x00
    int32_t count;                 // +0x04 edificios con la tarea
    int32_t labor;                 // +0x08 colonos asignados
    int32_t freeActive;            // +0x0c huecos libres en edificios activos
    int32_t freeInactive;          // +0x10 huecos libres en edificios inactivos
    int32_t output;                // +0x14 producción
};
extern TaskSummary gTaskSummary[28];
extern int gAssistantMaxMoves;                 // DAT_00564404
void BuildTaskSummary(Territory* t);           // FUN_004483d0
int  TaskUrgency(int taskId, Territory* t, Building* b);          // FUN_004484fc
Building* FindLaborSource(Territory* t, int fromTask, int toTask); // FUN_004485e8
Building* FindLaborTarget(Territory* t, Building* exclude, int toTask); // FUN_00448700
int  AssistantMoveOne(Territory* t, int fromTask, int toTask);    // FUN_004487b8
int  AssistantMoveN(Territory* t, int fromTask, int toTask, int n); // FUN_00448844
bool AssistantHasSource(Territory* t, int fromTask, int toTask);  // FUN_00448878
void AssistantFreeTask(Territory* t, int taskId);                 // FUN_0044889c
int  QueuedUnitCount(Territory* t, int queueCat);                 // FUN_004488c8
int  MilitiaNeedsTraining(Territory* t, int bonus);               // FUN_0044890c
int  AssistantTaskWanted(Territory* t, int taskId, int pass);     // FUN_004489e0
void AssistantPass(Territory* t, int pass);                       // FUN_00448d1c
void RunColonyAssistant(Territory* t);                            // FUN_00448d94
int  FindTaskSlot(const Building* b, int taskId);                 // FUN_004023dc
int  SumTaskOutput(Territory* t, int taskId, int useMax);         // FUN_0040552c

// ----------------------------------------------------------------------------------------
// production.cpp - tareas, producción por turno, colas de unidades
// ----------------------------------------------------------------------------------------
void ProduceUnits(Territory* t, int queueCat, int work);         // ProduceUnits
void GetBuildingTasks(Player* p, Building* b);                   // GetBuildingTasks
int  ShrineTaskInfo(Building* b, int wantTask);                  // FUN_0044e600 (0: %, 1: tarea)
int  SiteYield(Territory* t, BuildingSite* s, int taskId, int base, int size); // FUN_0044e9e4
void BuildingTaskOutputs(Player* p, Territory* t, int site, int32_t out[5], int useMax); // FUN_0044eb4c
int  TaskOutput(Player* p, Territory* t, int site, int slot, int labor); // FUN_0044eeb4
void ProcessBuildingCosts();                                     // FUN_0044f110 (ProcessBuildingCosts)
int  FindBestUpgradeSite(Territory* t, Building* b);             // FUN_0044f1e8
void TrainMilitia(Territory* t, int16_t xp);                     // FUN_0044f2fc
void ProcessTerritoryProduction(Territory* t, int apply, int pass); // FUN_0044f3f0
void ProduceAllTerritories(int pass, int apply);                 // FUN_0044fcd4

// ----------------------------------------------------------------------------------------
// logistics.cpp - "Collect Material": importación de materiales entre territorios (0x471a98..)
// ----------------------------------------------------------------------------------------
struct TransferLogEntry { int32_t from, to, material, amount, cost; }; // DAT_006520a8
extern TransferLogEntry gTransferLog[1000];
extern int gTransferLogCount;                                    // DAT_004d6330
void LogTransfer(Territory* to, Territory* from, int material, int amount, int cost); // FUN_00471a98
void ResetTransferLog();                                         // FUN_00471b20
void ResetProductionCounters();                                  // FUN_00471bec
void SumPlayerMaterials(int player, int32_t out[11]);            // FUN_00471c1c
int  SteelEquivalent(const int32_t* m);                          // FUN_00471cc0 (m[4..7])
int  PlayerHasMaterial(int player, int material, int amount);    // FUN_00471cec
unsigned CheckAffordable(Player* p, Territory* t, const int32_t cost[13]); // FUN_00471e58
int  TerritorySteelEquivalent(Territory* t);                     // FUN_00471fec
int  CollectSteel(Territory* t, int amount, int apply);          // FUN_00472018
unsigned CollectRequiredResources(Territory* t, const int32_t cost[13], int32_t paid[11]); // FUN_004720f4
int  PayCosts(Player* p, Territory* t, const int32_t cost[13], int32_t paid[11]); // FUN_004722e0
void MarkReachable(Territory* t, Territory* target, int hops, int player, int mode); // FUN_00472578
int  ReachMode(Territory* from, Territory* to, int player);      // FUN_004726cc
int  TransportCost(int mode, int player);                        // FUN_00472730
int  TransportCostTo(Territory* from, Territory* to);            // FUN_004727dc
void ResetSuppliers();                                           // FUN_0047280c
int  FindSupplier(Territory* t, int player, int material, int maxMode); // FUN_00472844
int  CollectMaterial(Territory* t, int player, int material, int amount, int apply, int* left, int* cost); // FUN_00472974
void ImportDeficits();                                           // FUN_00472bf0
int  ImportCostEstimate(Territory* t, const int32_t cost[13]);   // FUN_00472ca0
unsigned CheckBuildingAffordable(int type, Territory* t);        // FUN_00471f5c

// ----------------------------------------------------------------------------------------
// population.cpp - población, impuestos, comida, energía, moral, motines y revueltas
// ----------------------------------------------------------------------------------------
struct MoraleBreakdown {       // DAT_0058f150 .. DAT_0058f178
    int32_t base;              // +0x00 moral actual (o 100/80)
    int32_t crowding;          // +0x04 hacinamiento
    int32_t starvation;        // +0x08 hambruna
    int32_t occupation;        // +0x0c ocupación enemiga
    int32_t energy;            // +0x10 (fila 22 de RaceStats x edificios cat 13)
    int32_t tax;               // +0x14 impuestos
    int32_t police;            // +0x18 unidades en modo policía
    int32_t culture;           // +0x1c cultura (máx 25)
    int32_t art;               // +0x20 arte (máx 10)
    int32_t hospitals;         // +0x24 hospitales
    int32_t total;             // +0x28 (DAT_0058f178)
};
struct MaintenanceBreakdown {  // DAT_0058f17c .. DAT_0058f198
    int32_t cost[4];           // +0x00 tierra, mar, aire, otros (DAT_0058f17c..188)
    int32_t count[4];          // +0x10 (DAT_0058f18c..198)
};
extern MoraleBreakdown gMorale;
extern MaintenanceBreakdown gMaintenance;
extern int gProductionPhase;                                     // DAT_004d5804

int  ISqrt(int v);                                               // FUN_0046a9d8
void AccumulateBuildingUpkeep(Territory* t);                     // FUN_0046aa10
void AccumulateTerritoryStats(Territory* t, int32_t* stats);     // FUN_0046ab18 (AccumulateTerritoryStats)
void ComputePlayerStats(int32_t stats[30], int player);          // FUN_0046ac44 (ComputePlayerStats)
int  EffectiveTaxLevel(Player* p, Territory* t);                 // FUN_0046adac
int  TerritoryTaxIncome(Player* p, Territory* t);                // FUN_0046ae1c
int  _MovePopulation(Territory* from, Territory* to, int amount, int noNet, int16_t site, int16_t slot); // _MovePopulation
int  TerritoryPopulationCap(Territory* t);                       // FUN_0046b074
int  TerritoryMaxPopulation(Territory* t);                       // FUN_0046b0e4 (TerritoryMaxPopulation)
void GrowPopulation(int apply);                                  // FUN_0046b1ac
int  IPow(int base, int exp);                                    // FUN_0046b3ac
void DisbandMostExpensiveUnit(int player);                       // FUN_0046b3dc
int  UnitMaintenance(int player);                                // FUN_0046b4d0
void PayMaintenance();                                           // FUN_0046b818
int  TerritoryEnergyUse(Territory* t);                           // FUN_0046b910
int  TerritoryFoodNeed(Territory* t);                            // FUN_0046b958
void RecordFoodEnergyNeeds();                                    // FUN_0046b9a0
void ConsumeFood();                                              // ConsumeFood
void ConsumeEnergy();                                            // FUN_0046bc28
int  PoliceStrength(Territory* t);                               // FUN_0046bce4
int  OccupationPenalty(Territory* t);                            // FUN_0046bd3c
int  ComputeMorale(Territory* t);                                // FUN_0046bdfc
void UpdateMorale(int apply);                                    // FUN_0046c1a8
void RefreshAllBuildingTasks();                                  // FUN_0046c1f0
Territory* FindRevoltTarget(Territory* t);                       // FUN_0046c254
void DoRiot(Territory* t, int16_t lost);                         // DoRiot
void TerritoryLaborPool(Territory* t, int* pool, int* spare);    // FUN_0046c3fc
void CheckRevolt(Territory* t);                                  // FUN_0046c49c
void CollectTaxes();                                             // FUN_0046c728
void EndTurnBalance();                                           // FUN_0046c780
void ProductionPhase();                                          // FUN_0046c7d4 (fase completa del turno)
void CountShrines();                                             // FUN_00486964 (port local por defecto)
int  BlackMarketRoll();                                          // FUN_00450c38
void BlackMarketReset();                                         // FUN_00450c9c
void BlackMarketTurn();                                          // FUN_00450cb8

// ----------------------------------------------------------------------------------------
// armies.cpp - pool de ejércitos, creación/borrado, listas por territorio, unidades en territorios
// ----------------------------------------------------------------------------------------
void ArmyFreeListCheck(int tag);                                 // FUN_004455fc
void InitArmyPool();                                             // FUN_0044569c
void RebuildArmyFreeList();                                      // FUN_00445710
Army* AllocArmy(Ptr32<Army>* list);                              // FUN_0044577c
void DeleteArmy(Army* a, Ptr32<Army>* list);                     // DeleteArmy
int  ReLinkArmy(Army* a, Territory* t, Ptr32<Army>* from, Ptr32<Army>* to); // ReLinkArmy
Army* FindTransportWithSpace(Army* list);                        // FUN_00445940
int  FirstFreeCargoSlot(Army* transport);                        // FUN_004459bc
int  IsCargoOf(Army* transport, Army* a);                        // FUN_004459dc
int  LoadIntoTransport(Army* a);                                 // FUN_00445a04
int  UnloadFromTransport(Army* a);                               // FUN_00445a74
void RelinkCargo(Army* transport, Territory* t, Ptr32<Army>* from, Ptr32<Army>* to); // FUN_00445aac
void DisbandExcessUnit(Territory* t, int unitType);              // FUN_00445ae4
int  CanCreateUnit(Territory* t, int unitType);                  // FUN_00445b94 (CanCreateUnit)
Army* CreateUnit(Territory* t, int player, int unitType, uint16_t id); // FUN_00445d30 (CreateUnit)
int  ListContains(Army* a, Ptr32<Army>* list);                   // FUN_00445ee0
void DisbandUnit(Army* a);                                       // FUN_00445f08
void DeleteUnit(Army* a);                                        // DeleteUnit
Army* SyncCreateUnit(Territory* t, int player, int unitType);    // SyncCreateUnit (0x477784)
Building* SyncCreateBuilding(Territory* t, int type);            // SyncCreateBuilding (0x477904)
void SyncDisbandUnit(Army* a);                                   // SyncDisbandUnit (0x475898)
int  UnitGroupLand(int unitClass);                               // FUN_004594b8
int  UnitGroupSea(int unitClass);                                // FUN_0045951c
int  ExperienceLevel(int xp);                                    // FUN_00447a40
int  UnitMoves(const Army* a);                                   // FUN_00447190
int  IsMobileUnit(const Army* a);                                // FUN_00446bf0 (clase con movimiento propio)
int  HasPact(int p1, int p2, unsigned mask);                     // FUN_004412d4 (HasPact)
int  HasPact2(int p1, int p2, unsigned mask);                    // FUN_00441388
int  CanUnitEnterTerrain(int player, int unitType);              // FUN_00416c28
int  UnitCanDoStance(Army* a, int action, int race);             // FUN_00416e70
void ClearTerritoryFlagBits(uint32_t mask);                      // FUN_0045dfb0
void SetPathDistAll(int16_t value, int player);                  // FUN_00446b08
void ComputePathDistances(Territory* from, int range, int unitClass, int player, uint32_t mask); // FUN_00446b3c
void ComputePathDistancesTo(Territory* from, Territory* to, int range, int unitClass, int player, uint32_t mask); // FUN_00446b94
void FloodPathDistance(Territory* t, int dist, int range, int unitClass, int player, uint32_t mask); // FUN_00446440
int  NextStepTowards(Territory* from, Territory* to, int player, int maxDist, int flag, int unitType, Ptr32<Territory>* path); // FUN_004467e8
int  HasHostileForeignUnits(Territory* t);                       // FUN_00446c34
int  DetectsShrine(Territory* t, int unitType);                  // DetectsShrine
void CheckDiscovery(Territory* t, int player, int unitType);     // CheckDiscovery
int  ControlsTerritory(Territory* t, int player);                // FUN_00446e30
void UpdateVisibilityFrom(Territory* t, int player);             // FUN_00446fd4
void UpdateAllVisibility();                                      // FUN_00447090
void AutoTrainStance(Army* a);                                   // FUN_00447158
void ResolveTerritoryUnits(Territory* t);                        // FUN_004471c0
void EnforceUnitLimits(Territory* t);                            // FUN_004474b0
int  _MoveUnit(Army* a, Territory* to, Territory* origin);       // FUN_00446084
void SetTerritoryOwner(Territory* t, int player);                // FUN_0046e56c
void AbandonIfEmpty(Territory* t);                               // FUN_0046e6b8
void AfterMovePhase(int loading);                                // FUN_0046e730
// Estadísticas de combate de unidad (0x447a68-0x448210): struct temporal de 0x4c bytes
struct UnitStats {             // FUN_00447a68 rellena
    int32_t unk00; int32_t type; uint8_t owner; uint8_t moves; int16_t xp; uint8_t pad0c[0x10];
    uint8_t starving; uint8_t pad1d; uint8_t ownerB; uint8_t pad1f[0x1d]; int32_t parent; uint8_t pad40[0xc];
};
void UnitStatsInit(const Army* a, UnitStats* s);                 // FUN_00447a68
int  UnitAttack(const UnitStats* s);                             // FUN_00447c2c
int  UnitDefense(const UnitStats* s);                            // FUN_00447da4
int  UnitRange(const UnitStats* s);                              // FUN_00447f44
int  UnitRof(const UnitStats* s);                                // FUN_00448008
int  UnitStat17(const UnitStats* s);                             // FUN_004480a8
int  UnitHitChance(const UnitStats* s);                          // FUN_00448118
int  UnitBonusA(const UnitStats* s);                             // FUN_004481a4
int  UnitBonusB(const UnitStats* s);                             // FUN_00448210
int  UnitBonusC(const UnitStats* s);                             // FUN_00448284
int  UnitBonusD(const UnitStats* s);                             // FUN_004482cc
int  ArmyAttack(const Army* a);                                  // FUN_00447b0c
int  ArmyDefense(const Army* a);                                 // FUN_00447b30
int  ArmyRange(const Army* a);                                   // FUN_00447b54
int  ArmyStat17(const Army* a);                                  // FUN_00447b78
int  ArmyRof(const Army* a);                                     // FUN_00447b9c
int  ArmyHitChance(const Army* a);                               // FUN_00447bc0
int  StealableTech(int thief, int victim);                       // FUN_0048514c
int  RandomEventAdd(int type, int param, int turns);             // FUN_0047ca98
void SortArmiesById();                                           // FUN_0046f89c
void SortBuildingsById();                                        // FUN_0046f908
extern int gSortedArmies[kMaxArmies];                            // DAT_005904dc
extern int gSortedBuildings[kMaxBuildings];                      // DAT_0058f21c

// ----------------------------------------------------------------------------------------
// campaign.cpp - objetivos de campaña (0x44fd14-0x450380)
// ----------------------------------------------------------------------------------------
int  CampaignApplyOptions(int clearDone);                        // FUN_0044fd14
int  CampaignFindGoal(int type);                                 // FUN_0044fdf0
unsigned CampaignFlagTest(int type);                             // FUN_0044fe1c
int  CampaignGoalIsUnit(int type);                               // FUN_0044fe38
void CampaignGoalSetDone(int type);                              // FUN_0044fe58
void CampaignGoalClearDone(int type);                            // FUN_0044fe8c
int  CampaignGoalDone(int type);                                 // FUN_0044febc
int  CampaignRestrictsUnit7(int unitType);                       // FUN_0044feec
int  CampaignRestrictsUnit7b(int unitType);                      // FUN_0044ff28
int  CampaignRestrictsBuilding7(int type);                       // FUN_0044ff80
int  CampaignGoal9TurnsElapsed();                                // FUN_0044ffbc
int  CampaignGoalHasParam(int type, int value);                  // FUN_00450000
int  CampaignUnitAllowed(int unitType);                          // FUN_00450058
int  CampaignUnitGoalsPending();                                 // FUN_00450094
int  CampaignMaterialGoalMet();                                  // FUN_004500d8
int  CampaignTechAllowed(int race, int tech);                    // FUN_00450150
void CampaignClearForbiddenResearch();                           // FUN_004501b0
int  CampaignTerritoryGoalMet(int type);                         // FUN_00450204
int  CampaignGoal12Done();                                       // FUN_00450320
int  CampaignGoal12Victory();                                    // FUN_00450340
int  CampaignVictoryCheck();                                     // FUN_00450380

} // namespace dl2::econ
