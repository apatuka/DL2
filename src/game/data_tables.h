// data_tables.h - Tablas estaticas de DEADLOCK.EXE (Deadlock II: Shrine Wars v1.20)
//
// GENERADO por tools/extract_tables.py a partir del ejecutable original; no editar a mano.
// Cada tabla lleva la direccion original en la seccion DATA y las funciones que la leen
// (evidencia completa en docs/DATA_TABLES.md).  Los indices coinciden con los enums de
// game_state.h (BuildingType, UnitType, TechId, Race, Terrain, Material).
#pragma once
#include <cstddef>
#include <cstdint>

namespace dl2::data {

constexpr int kNumBuildingTypes = 48;
constexpr int kNumUnitTypes     = 39;
constexpr int kNumTechs         = 48;
constexpr int kNumMaterials     = 11;
constexpr int kNumRaces         = 7;
constexpr int kNumRaceStatRows  = 64;
constexpr int kNumEventDefs     = 156;
constexpr int kNumCampaigns     = 43;
constexpr int kNumAiArrivals    = 10;
constexpr int kNumBlackMarket   = 25;

// Los ids de tarea que usa el juego (BuildingTypeDef::tasks, Building::task[]) indexan la
// tabla de cadenas 0x509178: 0 = " " (ninguna), 1 = "Unassigned", 2 = "Construction", ...
// es decir, id = BuildingTask(enum de game_state.h) + kTaskIdBase.
constexpr int kTaskIdBase = 2;
enum TaskId : uint8_t {
    kTaskNone = 0, kTaskUnassigned = 1, kTaskConstruction = 2, kTaskMineIron = 3,
    kTaskMineEndurium = 4, kTaskResearch = 5, kTaskElectronicParts = 6, kTaskCulture = 7,
    kTaskCreateArt = 8, kTaskIronToSteel = 9, kTaskEnduriumToTriidium = 10, kTaskBuildUnits = 11,
    kTaskFood = 12, kTaskWood = 13, kTaskTrade = 14, kTaskEnergy = 15, kTaskAntiMatterPods = 16,
    kTaskClone = 17, kTaskTrainUnits = 18, kTaskHealMilitia = 19, kTaskHousePopulace = 20,
    kTaskUpgrade = 21, kTaskUnused = 22, kTaskBuildLandUnits = 23
};

// Dominio de movimiento de una unidad (UnitDef::domain, FUN_00445b94 / CheckSubUnit)
enum UnitDomain : int8_t { kDomainLand = 1, kDomainSea = 2, kDomainAir = 3, kDomainAmphibious = 6 };

// Clases de unidad (UnitDef::unitClass -> Army::unitClass); grupos de FUN_00447c2c/FUN_0046b4d0
enum UnitClass : uint8_t {
    kClassInfantry = 1, kClassArmor = 2, kClassAir = 3, kClassSeaTransport = 4, kClassWarship = 5,
    kClassCommandCorps = 6, kClassScout = 7, kClassColonizer = 8, kClassWarhead = 9, kClassFort = 10,
    kClassMedic = 11, kClassAAV = 12, kClassAirCommand = 13, kClassDestroyer = 14, kClassSubmarine = 15,
    kClassSeaColonizer = 16, kClassSeaCommand = 17, kClassFlakShip = 18, kClassSiegeCruiser = 19,
    kClassMine = 20
};

// ---- Edificios: DAT_004f9dbc (48 x 0x32) + costes DAT_004fa71c (48 x int32[11]) ----
struct BuildingDef {
    const char* name;           // +0x00
    uint16_t    sprite;         // +0x04 indice base de sprite (PTR_DAT_004d02f4); +raza en viviendas/CC/SeaHab/Kelp
    uint8_t     icon;           // +0x06 imagen en IMAG "BU01" (FUN_0041beac)
    uint8_t     category;       // +0x07 -> Building::category (0x11 vivienda, 0x0b shrine, 0x12 defensa, 0x07 puerto...)
    uint8_t     maxLabor;       // +0x08 trabajadores maximos (FUN_0044ba40; viviendas x fila 24 de RaceStats)
    uint8_t     size;           // +0x09 casillas que ocupa: 1, 2 o 5 (FUN_0044d7b4)
    uint16_t    buildLabor;     // +0x0a puntos de trabajo para construirlo (Building+0x14 inicial; FUN_0044de9c cost[0])
    uint16_t    energyUse;      // +0x0c energia consumida por turno (FUN_0046b910)
    int16_t     taskRate[5];    // +0x0e rendimiento por ranura de tarea (FUN_0044eb4c; [0] = construccion = 100)
    uint8_t     tasks[5];       // +0x18 TaskId por ranura ([0] siempre 0; GetBuildingTasks lee 1..4)
    uint8_t     units[10];      // +0x1d unidades construibles (UnitType, 0 = fin; FUN_004383a4)
    uint8_t     techRequired;   // +0x27 TechId necesaria (FUN_0044de9c cost[12], "Tech: %s")
    uint8_t     hitPoints;      // +0x28 resistencia (FUN_004526b0: dano -> puntos de construccion perdidos)
    uint8_t     unk_29;         // +0x29 siempre 0, sin lectores
    int32_t     productionQueue;// +0x2a cola de Territory::queues (1 Factory..5 City Center; 0 = ninguna) (FUN_0044f3f0)
    int32_t     dialogAnim;     // +0x2e animacion del dialogo de produccion (FUN_0041ccb0 -> FUN_00482b38(4,id); -1 = ninguna)
    int32_t     cost[kNumMaterials]; // DAT_004fa71c: coste por Material (Money..Art)
};
extern const BuildingDef kBuildingTypes[kNumBuildingTypes];

// ---- Unidades: PTR_s_No_Unit_004faf7c (39 x 0x24) + costes DAT_004fb4f8 (39 x int32[11]) ----
struct UnitDef {
    const char* name;           // +0x00
    uint16_t    combatSprite;   // +0x04 sprite de combate (LoadCombatSprites; fuertes = sprite del edificio)
    uint16_t    moveAnim;       // +0x06 id ANIM del vehiculo (0 = infanteria por raza)
    uint16_t    portraitGroup;  // +0x08 grupo de retrato (FUN_004382d0: 0x9f inf, 0x91 medic, 0x98, 0xa6, 0xad)
    int8_t      portraitIndex;  // +0x0a indice dentro del grupo (+raza*N)
    uint8_t     unitClass;      // +0x0b UnitClass -> Army::unitClass (FUN_00445d30)
    uint16_t    buildLabor;     // +0x0c puntos de trabajo ("%d Labor"; FUN_0044ddf4 cost[0])
    int8_t      upkeep;         // +0x0e creditos de mantenimiento por turno (FUN_0046b4d0)
    int8_t      techRequired;   // +0x0f TechId (FUN_0044ddf4 cost[12])
    int8_t      moves;          // +0x10 puntos de movimiento (FUN_00447190 -> Army+0x0a; +1 con Transporters)
    int8_t      domain;         // +0x11 UnitDomain (1 tierra, 2 mar, 3 aire, 6 anfibio)
    int8_t      unk_12;         // +0x12 sin lectores en el codigo (4 inf, 2 blindados, 3 aire/mar, 0 fuertes)
    int8_t      attack;         // +0x13 ataque (FUN_00447c2c; x fila 29/35/37/39/41/43 de RaceStats)
    int8_t      defense;        // +0x14 defensa (FUN_00447da4; x fila 30/36/38/40/42/44)
    int8_t      speed;          // +0x15 velocidad en combate, menor = mas rapido; -1 inmovil (FUN_00447f44 + fila 46)
    int8_t      rateOfFire;     // +0x16 cadencia: kRateOfFireNames[rof+1] (FUN_00448008)
    int8_t      range;          // +0x17 alcance de disparo al cuadrado (FUN_004480a8)
    int32_t     sound;          // +0x18 id de sonido de disparo (FUN_0043d2d8 -> FUN_00482ac4)
    int32_t     cost[kNumMaterials]; // DAT_004fb4f8: coste por Material
};
extern const UnitDef kUnitTypes[kNumUnitTypes];
extern const int32_t kMaxUnitsPerTerritorySea[4];   // DAT_004faf5c (FUN_00445b94, por clase de apilado)
extern const int32_t kMaxUnitsPerTerritoryLand[4];  // DAT_004faf6c

// ---- Tecnologias: DAT_004fbbac (48 x 0x32), parte estatica ----
struct TechDef {
    const char* name;           // +0x14
    uint32_t    treeItemId;     // +0x18 id de item SMenu en el arbol (FUN_0043c540); 0 = no se muestra
    uint16_t    level;          // +0x20 nivel 1..8
    uint16_t    cost;           // +0x22 coste de investigacion
    uint16_t    prereq[3];      // +0x24 TechId requeridas (0 = ninguna)
    int16_t     treeIcon;       // +0x2c 1 / -1: variante de icono en el arbol
    uint16_t    treeY;          // +0x2e posicion en el arbol
    uint16_t    treeX;          // +0x30
};
extern const TechDef kTechs[kNumTechs];

// ---- Modificadores raciales: DAT_004fc50c int16[64][8] (columna 7 sin uso) ----
extern const int16_t kRaceStatsDefault[kNumRaceStatRows][8];
extern const int16_t kRaceStatsRows61[3][8];        // DAT_004fc8dc: filas 61..63 para ficheros antiguos

// ---- Produccion por trabajadores: DAT_004f9bc4 int32[maxLabor][labor] (%; FUN_0044eb4c) ----
extern const int32_t kLaborProductionTable[11][11];

// ---- Event Log: DAT_004fc90c (157 x 0x12; FUN_0042278c busca por id) ----
struct EventDef {
    int16_t     priority;       // +0x00 prioridad (FUN_004233e0 desaloja el mas antiguo de menor prioridad)
    int16_t     id;             // +0x06 id de evento (EventLogEntry::type)
    int16_t     category;       // +0x08 pestana del Event Log (FUN_004228d4); -1 = general
    int16_t     unk_0a;         // +0x0a
    int16_t     portrait;       // +0x0c retrato (FUN_004503f4; -1 ninguno; 7 = comparacion de ciudades)
    const char* format;         // +0x0e formato sprintf
};
extern const EventDef kEventDefs[kNumEventDefs];

// ---- Campanas: DAT_004c6194 (43 x 0xd8; indice = GameOptions::campaign, 0 = ninguna) ----
struct CampaignGoal {
    int32_t type;               // +0x00 tipo de objetivo (0 = vacio; 6 = llegada de IA; 0xd = territorios marinos...)
    int32_t turns;              // +0x04 turnos que hay que mantenerlo / nº de llegadas (tipo 6)
    int32_t count;              // +0x08 cantidad requerida (territorios de list[]) / 1er indice de llegada (tipo 6)
    int32_t list[13];           // +0x0c territorios / (turno, indice de kAiArrivals) para el tipo 6
    int32_t state;              // +0x40 MUTABLE en el original: 0 / 1 / turno en que se cumplio (se guarda)
};
struct CampaignDef {
    uint8_t      victory;       // +0x00 VictoryCondition
    int32_t      param1;        // +0x04 Win Cities (victory 0) / Win Shrines (victory 2)
    int32_t      param2;        // +0x08 Win Turns (victory 2)
    CampaignGoal goals[3];      // +0x0c
};
extern const CampaignDef kCampaigns[kNumCampaigns];

// ---- Llegada de colonias IA en campana: DAT_004dc434 (x 0x9c; FUN_0047c730) ----
struct AiArrivalDef {
    int32_t race;               // +0x00
    int32_t sites[4];           // +0x04 territorios candidatos de aterrizaje (FUN_0047c6c0)
    int32_t techLevel;          // +0x14 conoce todas las tecnologias de nivel <= techLevel
    int32_t credits;            // +0x18
    int32_t materials[10];      // +0x1c Territory::materials[1..10]
    int32_t units[10][2];       // +0x44 {UnitType, cantidad} (experiencia 200)
    int32_t allyRace;           // +0x94 raza con la que fija relacion
    int32_t allyPact;           // +0x98 valor de la relacion (FUN_00441700)
};
extern const AiArrivalDef kAiArrivals[kNumAiArrivals];

// ---- Eventos aleatorios ----
struct OrigFunction { uint32_t addr; const char* name; };
extern const OrigFunction kRandomEventHandlers[10];  // PTR_FUN_004dcab0[RandomEvent::type]
extern const char* const  kRandomEventNames[10];     // nombre por tipo (derivado del evento de log que emiten)
extern const int32_t  kBonusMaterials[5];            // DAT_004dca4c: Material de Bonus/NoBonus/Shaman
extern const uint16_t kSpyMissionRisk[4];            // DAT_004dca60: riesgo base % por Spy::mission
struct ScandalEffect { int16_t moraleLoss; int16_t globalMoraleLoss; int16_t riotChance; };
extern const ScandalEffect kScandalTable[12];        // DAT_004dca68: por Player::scandals (0..11)

// ---- Rutas (FUN_0047da24 / FUN_0047dd58) ----
extern const int16_t kPathDelta1[4];                 // DAT_004dcbd8
extern const int16_t kPathDelta2[4];                 // DAT_004dcbe0
extern const int32_t kTileMoveCost[7];               // DAT_004dcbe8 por Tile::terrain

// ---- Economia / poblacion ----
extern const int32_t  kTaxMoraleByLevel[6];          // DAT_004d57ec: morale, NOT tax income
extern const int32_t  kTaxIncomePercent[6];         // DAT_004d5838: FUN_0046ae1c
extern const int32_t  kPopulationGrowthByTerrain[6];// DAT_004d5808: FUN_0046b1ac
extern const int32_t  kTaxRates[6];                 // Legacy name: same MORALE values as kTaxMoraleByLevel
extern const int32_t  kTerrainMaxPopulation[6];      // DAT_004d5820: por Terrain (x fila 24 / 100)
extern const int32_t  kPopGrowthTable[5];            // Legacy misnomer: tax income[1..5], NOT growth
extern const int32_t  kMoraleByLevel[8];             // DAT_004d5850: por Territory+0x29 (FUN_0046bdfc)

// ---- Opciones de partida / mundo ----
extern const uint16_t kMapSizes[4];                  // DAT_004d5144: ancho/alto por tamano
extern const uint16_t kTerrainPctTable[5][6];        // DAT_004d514c: % de terreno por tamano (4 = "huge" raro)
extern const int32_t  kWinCitiesChoices[5];          // DAT_004c425c
extern const int32_t  kWinShrinesChoices[3];         // DAT_004c4274
extern const int32_t  kWinTurnsChoices[3];           // DAT_004c4280

// ---- Mercado negro Skirineen: DAT_004c42f8 (25 x 0xe) ----
struct BlackMarketOffer { int32_t unitType; int16_t experience; int32_t price; int32_t minTurn; };
extern const BlackMarketOffer kBlackMarketOffers[kNumBlackMarket];

// ---- IA ----
// Personalidad de IA (PTR_DAT_004b502c + tipo*0x18; solo existe el tipo 3 "Machiavelli").
// FUN_00401830 copia fn[0..3] a Player+0x46 y fn[4] a Player+0x56; fn[1] = turno de IA (RunAITurns),
// fn[4] = receptor de eventos (FUN_00423690).
struct AiTypeDef { const char* name; OrigFunction fn[5]; };
extern const AiTypeDef kAiType3;
struct MinisterVtable { int32_t id; OrigFunction fn[4]; };
extern const MinisterVtable kMinisterVtable[6];      // PTR_FUN_004b508c (FUN_0040233c)
extern const int32_t kMinisterOrder[6];              // DAT_004b5104: orden de ejecucion (FUN_00402494)
struct MinisterConfig { int32_t kind; int32_t param; };
extern const MinisterConfig kAiMinisterConfigDefault[6]; // DAT_004b62f4 (FUN_00408784)

// ---- Tablas de cadenas ----
extern const char* const kRaceNames[7];              // 0x509038
extern const char* const kTerrainNames[6];           // 0x509054
extern const char* const kMaterialNames[11];         // 0x50906c
extern const char* const kMaterialNamesLower[11];    // 0x509098
extern const char* const kTaskNames[24];             // 0x509178 (indice = TaskId)
extern const char* const kUnitSpeedNames[9];         // 0x509a64 (indice = speed+1)
extern const char* const kRateOfFireNames[10];       // 0x509a84 (indice = rateOfFire+1)
extern const char* const kAiLeaderNames[7];          // 0x509938
extern const char* const kRaceShortNames[7];         // 0x5099cf
extern const char* const kTaskForceGoalNames[21];    // 0x4b6bd4
extern const char* const kTaskForceStatusNames[6];   // 0x4b6c7c
extern const char* const kMinisterJobNames[14];      // 0x4b5fe8
extern const char* const kMinisterNames[6];          // 0x4b5fd0
extern const char* const kIniKeys[44];               // 0x4d5f60
extern const char* const kIniValues[8];              // 0x4d6010
extern const char* const kIniMapSizeNames[5];        // 0x4d6030
extern const char* const kIniWorldTypeNames[7];      // 0x4d6044
extern const char* const kIniRoleNames[2];           // 0x4d6060

// ---- Ayudas ----
inline const char* BuildingName(int type) { return (type >= 0 && type < kNumBuildingTypes) ? kBuildingTypes[type].name : ""; }
inline const char* UnitName(int type)     { return (type >= 0 && type < kNumUnitTypes) ? kUnitTypes[type].name : ""; }
inline const char* TechName(int tech)     { return (tech >= 0 && tech < kNumTechs) ? kTechs[tech].name : ""; }
inline const char* TaskName(int taskId)   { return (taskId >= 0 && taskId < 24) ? kTaskNames[taskId] : ""; }
// Edificio de defensa -> unidad de fuerte equivalente (FUN_00451de4: tipo-10; Torpedo Fort 40 -> 32)
inline int FortUnitForBuilding(int bldg) { return bldg == 40 ? 32 : (bldg >= 29 && bldg <= 32 ? bldg - 10 : 0); }

} // namespace dl2::data
