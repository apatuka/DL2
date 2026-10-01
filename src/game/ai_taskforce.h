// ai_taskforce.h - Task forces de la IA (Job, 0x40A000-0x410000 + 0x4100e0-0x410870) y órdenes de
// unidades (unit_orders.cpp: movimiento entre territorios, misiones, retirada, misiles).
//
// Modelo (ver docs/AI_TASKFORCE.md):
//   - Cada jugador tiene 50 Job (gs.jobs[player][0..49]).  El slot 0 es el RESERVE (goal 1); los slots
//     1..49 se reciclan eligiendo el de menor prioridad (FUN_0040ad88).
//   - Los "ids" de job guardados en Army::job, Job::parentJob y en los 15 hijos (Job+0x88) son 1-based:
//     id -> gs.jobs[owner][id-1].
//   - Job::armies[16] son punteros (Ptr32<Army>) y armyIds[16] los ids globales; JobValidateArmies
//     anula los que no coincidan.
#pragma once
#include <cstdint>
#include <vector>

#include "game/ai_api.h"
#include "game/economy.h"
#include "game/game_state.h"
#include "game/globals.h"
#include "game/legacy_fields.h"

namespace dl2 {

// -----------------------------------------------------------------------------------------
// Constantes y tablas del EXE
// -----------------------------------------------------------------------------------------
constexpr int kJobArmies   = 16;   // Job::armies / armyIds
constexpr int kJobChildren = 15;   // Job+0x88 .. Job+0xC4: ids de jobs hijos (1-based), índices 1..15
constexpr int kNumGoals    = 21;
constexpr int kNumMissions = 27;
constexpr int kNumTactics  = 27;
constexpr int kNumUnitClasses = 21;

enum UnitClass : int {              // UnitTypeDef+0x0b (tabla PTR_s_UC_NOCLASS_004b6c28)
    UC_NOCLASS = 0, UC_TROOPER, UC_ARTILLERY, UC_BOMBER, UC_TRANSPORT, UC_BATTLESHIP, UC_GENERAL,
    UC_SPY, UC_COLONIZER, UC_MISSILE, UC_FORT, UC_MEDIC, UC_AAV, UC_ACOM, UC_DEST, UC_SUB,
    UC_SEA_COLONIZER, UC_AEGIS, UC_FSHIP, UC_SIEGE, UC_MINE
};

enum MoveDomain : int {             // UnitTypeDef+0x11 (FUN_00446440 decide el paso entre territorios)
    DOM_LAND = 1, DOM_SEA = 2, DOM_AIR = 3, DOM_TRANSPORTED = 5 /* interno: tierra embarcable */, DOM_AMPHIB = 6
};

enum Mission : int {                // Army+0x25 (tabla PTR_s_No_Mission_00509dcc)
    MISSION_NONE = 0, MISSION_SPY, MISSION_SUBVERT, MISSION_POISON_LAND, MISSION_STEAL_TECH,
    MISSION_STEAL_RESOURCES, MISSION_MECH_SABOTAGE, MISSION_SHAMAN_DANCE, MISSION_BUILD_SETTLEMENT,
    MISSION_BUILD_PLATFORM, MISSION_PATROL, MISSION_REPAIR, MISSION_UNCLOAK, MISSION_SUPPRESS,
    MISSION_TRAIN, MISSION_SILENT_RUNNING, MISSION_HUNT, MISSION_UNDERWATER_SEARCH,
    MISSION_MINE_TERRITORY, MISSION_DISARM_MINES, MISSION_TRANSFER_CHCHT /*20..26 = 20+raza*/
};

enum Tactic : int {                 // Army+0x24 (tabla PTR_s_Attack_Units_Only_00509e38)
    TACTIC_ATTACK_UNITS_ONLY = 0, TACTIC_BERSERK, TACTIC_JUGGERNAUT, TACTIC_ATTACK_ALL, TACTIC_AVOID_MINES,
    TACTIC_ATTACK_BUILDINGS, TACTIC_ATTACK_FARMS, TACTIC_ATTACK_MINES, TACTIC_ATTACK_POWER_PLANTS,
    TACTIC_ATTACK_FACTORIES, TACTIC_ATTACK_RESEARCH, TACTIC_ATTACK_CULTURE, TACTIC_ATTACK_SEA_PORTS,
    TACTIC_ATTACK_AIRPORTS, TACTIC_ATTACK_CITY_CENTERS, TACTIC_ATTACK_MISSILE_BASES, TACTIC_ATTACK_SHRINES,
    TACTIC_ATTACK_FUEL_DEPOTS, TACTIC_ATTACK_CLONING, TACTIC_ATTACK_HOSPITALS, TACTIC_ATTACK_TRAINING,
    TACTIC_ATTACK_OCEAN_CONTROLS, TACTIC_ATTACK_HOUSING, TACTIC_ATTACK_FORTS, TACTIC_ATTACK_BUNKERS,
    TACTIC_ATTACK_SEA_PLATFORMS, TACTIC_COMBAT_SUPPORT
};

extern const char* const kTaskForceGoalNames[kNumGoals];        // PTR_s_NO_TF_GOAL_004b6bd4
extern const char* const kTaskForceStatusNames[6];              // PTR_s_NEED_SPACE_004b6c7c
extern const char* const kUnitClassNames[kNumUnitClasses];      // PTR_s_UC_NOCLASS_004b6c28
extern const char* const kMissionNames[kNumMissions];           // PTR_s_No_Mission_00509dcc
extern const char* const kTacticNames[kNumTactics];             // PTR_s_Attack_Units_Only_00509e38
extern const int32_t kGoalUnitClasses[kNumGoals][16];           // DAT_004b6640: clases deseadas por goal ([0] = principal)
extern const int32_t kGoalPrimaryCount[kNumGoals];              // DAT_004b6b80: nº de unidades de la clase principal
extern const int32_t kProductionBuilding[6];                    // DAT_004b6f74: edificio por categoría de producción (FUN_0040f5e0)
extern const int16_t kTerritoryEvalA[6];                        // DAT_004b6f5c (FUN_0040dd80 -> FUN_00402548: tipo de edificio)
extern const int16_t kTerritoryEvalB[6];                        // DAT_004b6f68 (tarea)
extern const int32_t kLaborMinisterTechs[];                     // DAT_004b65d0 (termina en 0)
extern const int32_t kTechMinisterTechs[];                      // DAT_004b65e8
extern const int32_t kWarMinisterTechs[];                       // DAT_004b65f8
extern const int32_t kWorldResourceMods[6][5];                  // DAT_004d4f94 (paso 0x14)

// Tabla estática de unidades: econ::kUnitTypes (PTR_s_No_Unit_004faf7c).
inline int UnitTypeClass(int t)   { return econ::kUnitTypes[t].unitClass; }  // +0x0b UC_*
inline int UnitTypeTech(int t)    { return econ::kUnitTypes[t].tech; }       // +0x0f TechId requerida
inline int UnitTypeRange(int t)   { return econ::kUnitTypes[t].moves; }      // +0x10 movimiento base (FUN_00447190)
inline int UnitTypeDomain(int t)  { return econ::kUnitTypes[t].domain; }     // +0x11 MoveDomain

// -----------------------------------------------------------------------------------------
// Vistas sobre campos aún sin nombre en game_state.h (no se modifica el layout; ver docs/AI_TASKFORCE.md)
// -----------------------------------------------------------------------------------------
#pragma pack(push, 1)
struct TerritoryAi {                 // Territory::unk_9b4 (0x9b4..0xa7e): datos transitorios de la IA (no se guardan)
    int8_t   unk_9b4;                // 0x9b4 (FUN_0040e188)
    uint8_t  unk_9b5;
    int16_t  unitClassCount[21];     // 0x9b6 unidades enemigas por clase UC_* (FUN_0040e470, FUN_00402548)
    uint8_t  unk_9e0[0x2a];          // 0x9e0
    int32_t  ownStrength;            // 0xa0a fuerza propia (FUN_0040c578, FUN_0040da78, FUN_0040e9f4)
    int32_t  unk_a0e;                // 0xa0e
    int32_t  ownDefense;             // 0xa12 (FUN_0040ec50, FUN_0040f154, FUN_0040d4a8, FUN_00409270)
    uint8_t  unk_a16[0x3a];          // 0xa16
    int32_t  strengthA;              // 0xa50 (FUN_0040e164)
    int32_t  strengthB;              // 0xa54 (FUN_0040e164)
    int32_t  defenseValue;           // 0xa58 (FUN_0040c510: fuerza objetivo para atacar/cazar)
    int32_t  unk_a5c;                // 0xa5c
    int32_t  enemyStrength;          // 0xa60 (FUN_0040c4d4: fuerza necesaria = enemyStrength - ownStrength)
    uint8_t  unk_a64[8];             // 0xa64
    int16_t  threat;                 // 0xa6c (<3 objetivo válido, <2 bonificación; >2 abortar expansión)
    int16_t  claims;                 // 0xa6e se resta al valor del territorio (FUN_0040df44, FUN_0040f974)
    int16_t  pathCost[7];            // 0xa70 coste de ruta por jugador (FUN_00446440 / FUN_00446b08; = econ::pathDist)
};
static_assert(sizeof(TerritoryAi) == 0xca);
#pragma pack(pop)

inline TerritoryAi&       aiData(Territory& t)       { return *reinterpret_cast<TerritoryAi*>(t.unk_9b4); }
inline const TerritoryAi& aiData(const Territory& t) { return *reinterpret_cast<const TerritoryAi*>(t.unk_9b4); }
inline int16_t& pathCost(Territory& t, int player)   { return aiData(t).pathCost[player]; }
// Territory+0x978 + player*4: estado de búsqueda de shrine por jugador (-1 = sin explorar; >0 = shrine conocido)
inline int32_t& shrineSearch(Territory& t, int player) { return *reinterpret_cast<int32_t*>(t.unk_8b0 + (0x978 - 0x8b0) + player * 4); }
// Territory+0x6d + player: tipo de avión mínimo que llega (9..11; 12 = ninguno). Aviones con tipo menor se estrellan.
inline int8_t& airReach(Territory& t, int player)    { return reinterpret_cast<int8_t&>(t.unk_6d[player]); }
inline bool territoryInvalid(const Territory& t)     { return (t.flags & 0x100) != 0; }   // bit 8 (+0x1d & 1)
inline uint32_t continentReach(int c)                { return *reinterpret_cast<const uint32_t*>(&gs.continents[c].unk_0c[0]); } // Continent+0xc (DAT_0055a82c)

// Army: campos con significado demostrado por este módulo
inline uint8_t& armyMovesLeft(Army& a) { return a.strength; }   // Army+0x0a: movimiento restante (FUN_00446084: rango - coste)
inline uint8_t& armyTactic(Army& a)    { return a.moves; }      // Army+0x24: Tactic
inline uint8_t& armyRetreatPct(Army& a){ return a.health; }     // Army+0x26 (FUN_0040f060 lo pone a 100 al atacar)
// armyMission (+0x25) / armyDamage (+0x2c): shared legacy_fields.h contracts.

// Job: enlaces padre/hijos (Job+0x84: [0] padre, [1..15] hijos; ids 1-based) y campos auxiliares
inline int32_t* jobLinks(Job& j)     { return &j.parentJob; }
inline int32_t& jobTurns(Job& j)     { return *reinterpret_cast<int32_t*>(j.unk_18 + 0); }   // Job+0x18 (FUN_0040e470)
inline int32_t& jobFlag1c(Job& j)    { return *reinterpret_cast<int32_t*>(j.unk_18 + 4); }   // Job+0x1c
inline int16_t& jobPriority(Job& j)  { return j.param2; }                                    // Job+0x0e (FUN_0040ad88 recicla el menor)
inline Job*  jobById(int owner, int id) { return id ? &gs.jobs[owner][id - 1] : nullptr; }  // &DAT_005224c0 + owner*0x2648 + id*0xc4
inline int   jobId(const Job& j)        { return int(&j - &gs.jobs[j.owner][0]) + 1; }
inline int   jobSlot(const Job& j)      { return int(&j - &gs.jobs[j.owner][0]); }
inline Job*  armyJob(const Army& a)     { return a.job ? &gs.jobs[a.owner][a.job - 1] : nullptr; }
inline Territory* firstTerritory()      { return &gs.territories[1]; }                       // &DAT_005a4eac
inline Territory* lastTerritory()       { return &gs.territories[gs.world.numTerritories]; } // bucle <= &DAT_005a43d0 + N*0xadc
inline int  playerType(int p)           { return gs.players[p].type; }
inline int  playerRace(int p)           { return gs.players[p].race; }
inline uint8_t ministerLevel(int p, int m) { return gs.players[p].ministers[m].unk_01; }     // DAT_0059f1bf + m*0x5a (prioridad/fuerza base)
// techKnown: shared legacy_fields.h signed-mask/shift contract.
inline uint32_t pathMask(int p)         { return 0x2000u << (p & 31); }                      // 0x2000 << player (Territory::flags)
// MinisterJob: campos de estado que ponen los handlers (+0xc "trabajado este turno", +0x10 "terminado: borrar")
inline int32_t& mjobWorked(MinisterJob& j) { return j.unk_0c; }
inline int32_t& mjobDone(MinisterJob& j)   { return j.unk_10; }

// -----------------------------------------------------------------------------------------
// Task forces (ai_taskforce.cpp) - nombres originales cuando se conocen
// -----------------------------------------------------------------------------------------
// Gestión de jobs
Job*  CreateTaskForceJob(int player, int param1, int targetPlayer, Territory* dest, int goal, int priority); // FUN_0040be04
int   FindFreeJobSlot(int player);                                  // FUN_0040ad88 (borra el de menor prioridad; -1 si ninguno)
void  DeleteTaskForce(Job* job);                                    // FUN_0040beb4
void  LinkChildJob(Job* parent, Job* child);                        // FUN_0040b000
void  UnlinkChildJob(Job* parent, Job* child);                      // FUN_0040afa4
int   IsChildJob(Job* parent, Job* child);                          // FUN_0040af44
void  JobValidateArmies(Job* job);                                  // FUN_0040aebc
Job*  FindTaskForce(int player, int goal, Territory* dest);         // FUN_0040c68c
Job*  FindTaskForceVsPlayer(int player, int goal, int targetPlayer);// FUN_0040c6e8
Job*  FindTaskForceByGoal(int player, int goal);                    // FUN_0040c74c
int   CountTaskForcesByGoal(int player, int goal);                  // FUN_0040c888
int   ArmyInOtherJob(int player, Army* army, int slot, int index);  // FUN_0040c158
void  ClearArmyFromJobs(int player);                                // FUN_0040bce0
// Ejércitos de un task force
int   JobHasArmy(Job* job, Army* army);                             // FUN_0040ab54
Army* JobFindArmyOfType(Job* job, int unitType);                    // FUN_0040ab80 (recursivo en hijos)
int   ArmyFitsClass(Army* army, int unitClass);                     // FUN_0040ac00
int   JobCountClass(Job* job, int unitClass);                       // FUN_0040ac58 (con hijos)
int   JobCountUnits(Job* job);                                      // FUN_0040ace4 (hijos: sólo terrestres)
void  JobAddArmyAt(Job* job, Army* army, int index);                // FUN_0040b074
void  JobAddArmy(Job* job, Army* army);                             // FUN_0040b0c0
void  JobReleaseArmyIfStrong(Job* job, Army* army);                 // FUN_0040b968
Army* JobFirstArmy(Job* job);                                       // FUN_0040c668
int   JobArmiesAtDestination(Job* job);                             // FUN_0040c5cc
int   JobArmiesAtOrNearDestination(Job* job);                       // FUN_0040c61c
int   JobAllArmiesCanReach(Job* job, Territory* t, int landing);    // FUN_0040c538
int   JobAllArmiesInRange(Job* job);                                // FUN_0040f2a4
int   JobAllNonSeaInRange(Job* job);                                // FUN_0040e284
int   JobHasLandUnits(Job* job);                                    // FUN_0040daf4
int   JobHasLoadedLandUnit(Job* job);                               // FUN_0040db30
Territory* JobUnloadedLandUnitDest(Job* job);                       // FUN_0040da38
int   JobLandUnitCanReachDest(Job* job);                            // FUN_0040db74
int   JobLandUnitsNearDest(Job* job);                               // FUN_0040d9d4
int   JobHasThreeLandUnits(Job* job);                               // FUN_0040d990
int   TransportHasNonMissileCargo(Army* transport);                 // FUN_0040b0fc
// Fuerza
int   TaskForceStrength(Job* job);                                  // FUN_0040c3b8 (suma de fuerzas x nº unidades)
void  TaskForceComposition(Job* job, int* hasMedic, int* hasCC, int* hasACom, int* hasSCom); // FUN_0040c260
int   StrengthNeeded(Territory* t);                                 // FUN_0040c4d4
int   TargetStrength(Territory* t);                                 // FUN_0040c510
Territory* BestSurplusTerritory(Army* army);                        // FUN_0040c578
int   JobNeedsMedic(Job* job);                                      // FUN_0040b1b8
int   JobNeedsCommandCorps(Job* job);                               // FUN_0040b2d4
int   JobNeedsAirCommand(Job* job);                                 // FUN_0040b3d0
int   JobNeedsSeaCommand(Job* job);                                 // FUN_0040b4d0
// Reclutamiento
int   ArmyCanLeaveJob(Job* job, Army* army);                        // FUN_0040b12c
int   ScoreArmyForJob(Job* job, Army* army);                        // FUN_0040b644
Army* FindBestArmyForJob(Job* job);                                 // FUN_0040b788
Army* FindBestArmyOfClass(Job* job, int unitClass);                 // FUN_0040b87c
void  FillTaskForce(Job* job);                                      // FUN_0040b994
int   NextClassToBuild(Job* job);                                   // FUN_0040ba64
int   IsLandClass(int unitClass);                                   // FUN_0040bb7c
int   IsSeaClass(int unitClass);                                    // FUN_0040bbb8
void  RequestFuelDepot(Job* job, int unitType);                     // FUN_0040b5cc
void  RequestUnitsForTaskForce(int player, MinisterJob* mjob);      // FUN_0040febc
int   PreferredUnitType(int player, int unitClass);                 // FUN_0040fc14
int   UnitUpgradeTech(int player, int unitType);                    // FUN_0040fbb0
int   ArmyIsObsolete(int player, Army* army);                       // FUN_0040ee34
// Movimiento del task force
void  MoveTaskForce(Job* job, int forceFull, int which);            // FUN_0040bbf4 (which: 0 todos menos misiles, 1 no-tierra, 2 tierra, 3 todos)
void  SetTaskForceMission(Job* job, int mission);                   // FUN_0040bfb4
void  SetAttackTactics(Job* job);                                   // FUN_0040f060
void  ScatterTaskForce(Job* job);                                   // FUN_0040f248
Territory* BestAdjacentTarget(Army* army, Territory* around);       // FUN_0040f154
int   ArmyCanEnterEnemyContinent(Army* army, Territory* t);         // FUN_0040b8f4
Job*  FindTransportJobFor(Army* army, Territory* dest);             // FUN_0040c7a4
// Territorios
Territory* FindAdjacentSea(Territory* t, int territoryIndex);       // FUN_0040d4a8
int   TerritoriesAdjacent(Territory* a, Territory* b);              // FUN_0040d920
int   TerritoryValue(Territory* t, int evalIndex, int player);      // FUN_0040dd80
int   HasOwnPopulatedNeighbour(int player, Territory* t);           // FUN_0040ded0
Territory* FindExpandTarget(int player, int evalIndex, int sea);    // FUN_0040df44
Territory* FindWeakEnemyTerritory(int player, int enemy, int land); // FUN_0040a60c
Territory* FindFriendlyNearby(int player, Territory* near);         // FUN_0040da78
Territory* FindEmbarkTerritory(Job* job, Territory* from, Territory* dest);      // FUN_0040d64c
Territory* FindLandingTerritory(Job* job, Territory* from, Territory* dest);     // FUN_0040d808
int   TransportCanUnloadNear(Territory* from, Territory* t, int player);         // FUN_0040d768
int   TerritoryAcceptsCargo(Territory* t, Job* job);                // FUN_0040d5c0
int   PathCostBetween(Territory* from, Territory* to, int player, int domain);   // FUN_0040d614
int   ArmyInRangeOf(Army* army, Territory* t);                      // FUN_0040e1fc
int   TerritoryHasEnemyBusyUnit(int player, Territory* t);          // FUN_0040e348
int   FreeSitesForMines(Territory* t);                              // FUN_0040e868
Territory* FindShrineSearchTarget(Job* job, Army* army);            // FUN_0040e8f0
Territory* FindBesiegeTarget(Job* job);                             // FUN_0040e9f4
Territory* FindMiningTarget(Job* job);                              // FUN_0040eb34
Territory* FindTrainingTerritory(Army* army);                       // FUN_0040ec50
int   TerritoryCanTrain(Territory* t, Army* army);                  // FUN_0040ecec
Territory* FindTrainingCenterSite(Army* army);                      // FUN_0040edcc
Territory* FindHuntTarget(Job* job);                                // FUN_0040f3d8
Territory* TerritoryHasTrainingCenter(Army* army, Territory* t);    // FUN_00410720
int   PlayerMarkedTerritory(Territory* t, int player);              // FUN_0040e188 (sin llamadores)
int   TerritoryTotalStrength(Territory* t);                         // FUN_0040e164 (sin llamadores)
int   CountTerritoriesWithMissileBase(int player, const std::vector<Territory*>& list); // FUN_0040e440
// Handlers de goal (FUN_0040e6e4 despacha por Job::goal)
void  RunTaskForce(Job* job);                                       // FUN_0040e6e4
void  HandleReserve(Job* job);                                      // FUN_0040ef18  RESERVE
void  HandleExpand(Job* job);                                       // FUN_0040e050  LAND_EXPAND / SEA_EXPAND
void  HandleAttack(Job* job);                                       // FUN_0040f2e0  LAND_ATTACK / SEA_ATTACK
void  HandleHunt(Job* job);                                         // FUN_0040f478  LAND_HUNT / SEA_HUNT
void  HandleDefend(Job* job);                                       // FUN_0040e384  LAND_DEFEND / SEA_DEFEND
void  HandleMine(Job* job);                                         // FUN_0040ec04  LAND_MINE / SEA_MINE
void  HandleShrine(Job* job);                                       // FUN_0040e994  LAND_SHRINE / SEA_SHRINE
void  HandleTransport(Job* job);                                    // FUN_0040dbc4  TRANSPORT_UNITS
void  HandleBesiege(Job* job);                                      // FUN_0040eadc  SEA_BESIEGE
void  HandleAirAttack(Job* job);                                    // FUN_0040f4fc  AIR_ATTACK
void  HandleAmphibAttack(Job* job);                                 // FUN_0040f540  AMPHIB_ATTACK
void  HandleSpecial(Job* job);                                      // FUN_0040e8ac  SPECIAL
void  RequestAirSeaAttackJobs(Job* job);                            // FUN_0040effc
void  RetargetTaskForce(Job* job);                                  // FUN_0040e2f4
void  HandleSpecialSearch(Job* job);                                // FUN_0040e470 (sin llamadores)
void  RandomDestination(Job* job);                                  // FUN_0040e10c (sin llamadores)
void  DeleteIfEmpty(Job* job);                                      // FUN_0040dd68 (sin llamadores)
// Turno
void  AssignLooseArmies(int player);                                // FUN_0040c018
void  TaskForceStatistics(int player);                              // FUN_0040c1b0 (bucles vacíos)
// Ministros (funciones del rango 0x40a000-0x40aaa4 y 0x40cda0-0x40d3bc)
void  RequestFirstUnknownTech(int player, int minister, const int32_t* techList);  // FUN_0040a14c
int   NextResearchableTech(int player, int tech);                   // FUN_0040a1c0
void  RequestResearchBuildings(int player);                         // FUN_0040a2a4
int   NoOtherTechAvailable(int player, int tech);                   // FUN_0040a338
int   AllyIsResearching(int player, int tech);                      // FUN_0040a37c
int   PickTechNotResearchedByAllies(int player);                    // FUN_0040a3c0
void  RequestFactories(int player);                                 // FUN_0040a5a4
void  CreateWarTaskForces(int player);                              // FUN_0040a710
void  CreateShrineWarTaskForces(int player);                        // FUN_0040a898
int   ResearchCompletesThisTurn(int player);                        // FUN_0040cda0
// Producción de unidades (FUN_0040f584 .. FUN_0040fb14)
int   TerritoryLacksProductionLabor(Territory* t, int prodCategory);// FUN_0040f584
int   ProductionCategory(int unitType);                             // FUN_0040f5e0 (1 fábrica, 2 astillero, 3 aeropuerto, 4 base de misiles, 5 city center)
int   QueuedUnitsBefore(Territory* t, int unitType);                // FUN_0040f658
int   UnitTypeQueued(Territory* t, int unitType);                   // FUN_0040f6b0
int   TerritoryCanReachFrom(Territory* t, Territory* target, int unitType, int landing); // FUN_0040f700
int   AirRangeReaches(int player, Territory* from, Territory* to, int unitType);        // FUN_0040f794
Territory* FindTerritoryQueuing(int unitType, int targetIndex, int landing);           // FUN_0040f818
int   TerritoryHasIdleFactory(Territory* t, int unitType);          // FUN_0040f874
Territory* FindTerritoryWithShortestQueue(int unitType, int targetIndex, int landing); // FUN_0040f8cc
void  RequestProductionBuilding(int player, int priority, int unitType, int targetIndex); // FUN_0040f974
Territory* FindTerritoryWithFactorySite(int unitType, int targetIndex, int landing);   // FUN_0040fb14
int   FindLandingTerritoryIndex(Job* job);                          // FUN_0040fe58
// Diálogo de depuración (sólo el modelo: texto de FUN_0040c8c8 sin Win32)
int   FormatTaskForceReport(int player, char* buf, int bufSize);    // FUN_0040c8c8 (parte no-UI)

// -----------------------------------------------------------------------------------------
// Órdenes de unidades (unit_orders.cpp)
// -----------------------------------------------------------------------------------------
Territory* NearestReachableOnPath(Army* army, Territory* dest);     // FUN_00401a18
int   TerritoryFriendlyFor(int player, Territory* t);               // FUN_004013ec
int   AirUnitCanReach(Army* army, Territory* t);                    // FUN_00401320
int   ArmyDomain(int unitType);                                     // dominio con 1 -> 5 (embarcable), como FUN_00446084/FUN_0040e1fc
int   CountActiveTrainingCenters(Territory* t);                     // FUN_00416cc0
int   CanBuildPlatform(Army* army);                                 // FUN_00416df4
int   CanMineTerritory(Army* army);                                 // FUN_00416e20
// Misiles / órdenes desde la UI (reglas, sin selección global)
int   CanLaunchMissileInto(Army* missile, Territory* t);            // regla "Missiles can only be launched into neutral or enemy territories"
void  OrderArmyMove(Army* army, Territory* t, int groupMove);       // FUN_0045c384 (reglas; DAT_00583d64 -> parámetro)
void  OrderTerritoryUnitsMove(Territory* from, Territory* to, int category, int all); // FUN_0045c560
int   UnitSelectCategorySea(int unitClass);                         // FUN_0045965c
int   UnitSelectCategoryLand(int unitClass);                        // FUN_004596d0

} // namespace dl2
