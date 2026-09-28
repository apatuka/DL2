// ai_api.h - Contrato entre los módulos de IA/unidades: funciones que un módulo necesita de otro y
// que NO están ya declaradas en economy.h (módulo economy) ni en gameflow.h.
//
// Cada declaración lleva la dirección original (FUN_xxxxxxxx) y el módulo que la IMPLEMENTA.  Quien
// necesite una función de otro módulo la declara aquí (append) con la firma que va a usar; el módulo
// propietario debe implementarla con exactamente esa firma.  test_ai_taskforce.cpp aporta stubs de
// todo lo que aún no exista (macros DL2_HAVE_MINISTERS / DL2_HAVE_NETWORK / DL2_HAVE_ECONOMY).
//
// Módulos:
//   ai_ministers  = sistema de ministros (0x401000-0x40A000, 0x472000-0x474000)
//   ai_taskforce  = task forces (0x40A000-0x410000 + 0x4100e0-0x410870) y órdenes de unidades
//                   (unit_orders.cpp: FUN_00401108/FUN_00401440/FUN_00401ac0..., misiones 0x416c28-0x4171e0,
//                   SetRetreat 0x451928, reglas de misiles 0x45c384/0x45c560)
//   economy       = economy.h (dl2::econ): edificios, colas, rutas entre territorios (FUN_00446440..),
//                   CanCreateUnit, pactos, campaña, estadísticas de unidad, IDs globales
//   network       = mensajes de red (0x474000-0x47E000); combat = combate (0x451000-0x457000)
#pragma once
#include <cstdint>
#include <vector>

#include "game/game_state.h"

namespace dl2 {

// =========================================================================================
// Implementadas por ai_taskforce (ai_taskforce.cpp / unit_orders.cpp).  Lista completa en
// ai_taskforce.h; aquí las que otros módulos llaman.
// =========================================================================================
// --- Turno de la IA (FUN_00408a88 del módulo de ministros las llama en este orden relativo) ---
void JobValidateAllTaskForces(int player);            // FUN_0040af0c  (tras cargar / al inicio del turno IA)
void LaborMinisterThink(int player);                  // FUN_0040a098  ministro 5: comida, población, arte, techs
void TechMinisterThink(int player);                   // FUN_0040a420  ministro 4: investigación, universidades
void WarMinisterThink(int player);                    // FUN_0040aaa4  ministro 1: RESERVE, task forces de guerra/expansión
void RunTaskForces(int player);                       // FUN_0040c21c  (asigna ejércitos sueltos y ejecuta los 50 jobs)
void CreateExpandTaskForces(int player, int priority, int evalIndex); // FUN_0040a524 (la llaman FUN_00409f6c / FUN_00407e78)
int  PlayerHasCloaking(int player);                   // FUN_0040a6a0
int  PlayerHasHullOrCloaking(int player);             // FUN_0040a6d8
// --- Handlers de MinisterJob despachados por FUN_004059bc (ministros) según MinisterJob::type ---
void HandleFillTaskForceJob(int player, MinisterJob* job);   // FUN_00410164  type 4  FILL_TASKFORCE
void HandleCreateUnitJob(int player, MinisterJob* job);      // FUN_0041026c  type 5  CREATE_UNIT
void HandleBuildUnitJob(int player, MinisterJob* job);       // FUN_004105e8  type 6  BUILD_UNIT
void HandleLearnTechJob(int player, MinisterJob* job);       // FUN_0040cea4  type 7  LEARN_TECH
void HandleMaintainMoraleJob(int player, MinisterJob* job);  // FUN_0040d3bc  type 9  MAINTAIN_MORALE
void HandleGrowPopulationJob(int player, MinisterJob* job);  // FUN_0040d080  type 10 GROW_POPULATION
void HandleHealPlagueJob(int player, MinisterJob* job);      // FUN_0040d228  type 11 HEAL_PLAGUE
void HandleMaintainUnitJob(int player, MinisterJob* job);    // FUN_00410870  type 13 MAINTAIN_UNIT
// --- Creadores de MinisterJob que viven en el rango de ai_taskforce (mergePrio: si ya existe uno igual, sube su prioridad) ---
MinisterJob* CreateLearnTechJob(int player, int minister, int priority, int tech, int mergePrio);            // FUN_0040cdfc type 7
MinisterJob* CreateGrowPopulationJob(int player, int minister, int priority, int territory, int mergePrio);  // FUN_0040cffc type 10
MinisterJob* CreateHealPlagueJob(int player, int minister, int priority, int territory, int mergePrio);      // FUN_0040d1a4 type 11
MinisterJob* CreateMaintainMoraleJob(int player, int minister, int priority, int territory, int mergePrio);  // FUN_0040d338 type 9
MinisterJob* CreateFillTaskForceJob(int player, int minister, int priority, int jobSlot, int mergePrio);     // FUN_004100e0 type 4
MinisterJob* CreateCreateUnitJob(int player, int minister, int priority, int unitType, int territory, int mergePrio); // FUN_004101d4 type 5
MinisterJob* CreateBuildUnitJob(int player, int minister, int priority, int territory, int unitType, int param2, int mergePrio); // FUN_00410558 type 6
MinisterJob* CreateMaintainUnitJob(int player, int minister, int priority, int armyId, int mergePrio);       // FUN_004107ec type 13
// --- Unidades (unit_orders.cpp) ---
int  MoveArmyTo(Army* army, Territory* dest, int forceFullPath);   // FUN_00401ac0 (regla de choque de aviones incluida)
int  ArmyStrength(Army* army, int hasMedic, int hasCommandCorps, int hasAirCommand); // FUN_00401108 (parte baja del undefined8)
int  CanArmyReach(Army* army, Territory* t, int allowLanding);     // FUN_00401440
int  CanUnitHaveMission(Army* army, int mission, int race);        // FUN_00416e70 (= econ::UnitCanDoStance)
int  CanUnitHaveTactic(Army* army, int tactic, int race);          // FUN_004171e0
int  UnitTypeIsScoutLike(int player, int unitType);                // FUN_00416c28 (= econ::CanUnitEnterTerrain)
int  ArmyIsScoutLike(Army* army);                                  // FUN_00416ca4
int  ArmyCanTrain(Army* army);                                     // FUN_00416d08
void OnArmyEnteredTransport(Army* transport, Army* cargo);         // FUN_0040cd0c (econ::ext.taskForceMerge)
void RemoveArmyFromTaskForce(Army* army);                          // 0x40adf4 (econ::ext.removeArmyFromTaskForce)
uint32_t SetRetreat(const struct CombatUnitView* cu);              // 0x451928 (índice de territorio de retirada o 0xffffffff)

// =========================================================================================
// Requeridas por ai_taskforce.  IMPLEMENTA: ai_ministers.
// =========================================================================================
// Pool de MinisterJob (el original hace malloc(0x44)/free; el port usa un pool con índices 1-based en
// MinisterJob::next/prev).  AllocMinisterJob devuelve un nodo puesto a cero.
MinisterJob* AllocMinisterJob();                                   // FUN_004b0b44(0x44)+memset (RTL)
void         FreeMinisterJob(MinisterJob* job);                    // FUN_004b0a30 (RTL)
MinisterJob* FindMinisterJob(int player, MinisterJob* proto);      // FUN_004058e0: nodo equivalente (FUN_00405890) en la lista del jugador
int          AddMinisterJob(int player, MinisterJob* job);         // FUN_004056fc: inserta al principio de la lista del jugador
MinisterJob* CreateGetMaterialJob(int player, int minister, int priority, int material, int amount, int mergePrio); // FUN_00408b58 type 8
MinisterJob* CreateStockpileJob(int player, int minister, int priority, int material, int mergePrio);            // FUN_00408f58 type 12
MinisterJob* CreateBuildingJob(int player, int minister, int priority, int buildingType, int territory, int param2, int mergePrio); // FUN_00407d60 type 2 CREATE_BLDG
Territory*   FindTerritoryForBuilding(int player, int buildingType, int territoryIndex, int param4);  // FUN_00402cc0
int          EvaluateBuildingSite(Territory* t, int buildingType, int task, int* bestSite, int* bestValue); // FUN_00402548
uint32_t     TerritoryBorderMask(Territory* t, int player);        // FUN_00401670: direcciones (1/2/4/8) con territorio enemigo alcanzable
void         HandleSpyTaskForce(Job* job);                         // FUN_00407594: goals LAND_SPY(6)/SEA_SPY(14)
int          PickEnemyPlayer(int player);                          // FUN_004089d4: enemigo para un task force sin objetivo
int          MinisterFindLabor(int player, Territory* t, int task, int a, int b, int c);   // FUN_004067d0
int          MinisterHasTaskCapacity(int task, Territory* t);      // FUN_004054d8
int          MinisterTaskOutput(int task, int a);                  // FUN_004055c4 (suma de SumTaskOutput en los territorios propios)
int          MinisterCanAffordBuilding(int player, Territory* t);  // FUN_00406424
int          MinisterAssignLabor(int player, Territory* t, int category);   // FUN_004068f8
void         MinisterRandomEventJobs(int player);                  // FUN_00409d9c
void         MinisterPopulationJobs(int player);                   // FUN_00409e2c
void         MinisterRaceJobs(int player);                         // FUN_00409ef0
void         MinisterFoodJobs(int player);                         // FUN_00409f6c
int          PickResearchTech(Player* p, int flag);                // FUN_00483cbc (módulo tecnología)
// Lista circular DAT_00521bb4 de territorios del jugador IA en curso (la construye FUN_004064a0 al
// empezar el turno de ese jugador).  Se devuelve en el mismo orden que la lista original.
const std::vector<Territory*>& AiOwnedTerritories();

// =========================================================================================
// Requeridas por ai_taskforce.  IMPLEMENTA: network (0x474000-0x47E000)
// =========================================================================================
int   MoveUnit(Army* a, Territory* dest, Territory* via);           // FUN_004757c0 (local: econ::_MoveUnit; red: msg 0x13)
void  DisbandUnitNet(Army* a);                                      // FUN_00475854 (local: econ::DisbandUnit; red: msg 0x14)
void  SendUnitOrders(Army* a, int broadcastName);                   // FUN_00476f24 (msg 0x11: táctica/misión/retirada/job)
int   NetQueueUnit(Territory* t, Player* p, int unitType);          // FUN_00475f80 (0 = puesto en cola)
void  NetSetPortTarget(Territory* t, int targetIndex);              // FUN_00476324
void  SetPlayerResearch(int player, int tech);                      // FUN_004764dc (local: FUN_0048424c; red: msg 0x22)

// =========================================================================================
// Requeridas por ai_taskforce.  IMPLEMENTA: combat
// =========================================================================================
Territory* CombatCurrentTerritory();                                // *(DAT_0057cdf8+4): territorio del combate en curso (SetRetreat)

// Unidad de combate (objeto de 0x4c bytes del módulo de combate, = econ::UnitStats).  SetRetreat sólo
// usa +0 army (Ptr32 raw), +4 unitType y +0x1e owner.
#pragma pack(push, 1)
struct CombatUnitView {
    uint32_t    armyRaw;     // 0x00 Ptr32<Army>::raw
    int32_t     unitType;    // 0x04
    uint8_t     owner8;      // 0x08
    uint8_t     tactic;      // 0x09
    int16_t     experience;  // 0x0a
    uint8_t     unk_0c[0x10];// 0x0c
    uint8_t     halfStrength;// 0x1c
    uint8_t     unk_1d;
    uint8_t     owner;       // 0x1e
    uint8_t     unk_1f[0x2d];// 0x1f..0x4c
};
#pragma pack(pop)
static_assert(sizeof(CombatUnitView) == 0x4c);

} // namespace dl2
