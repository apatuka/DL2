// turn_api.h - Legacy declarations for future turn/combat/events ports.
// Static tables resolve to canonical data and the explicit legacy campaign bridge.
// Gameplay callbacks below are DECLARATIONS ONLY: no fallback is installed and
// including this header must not link invented no-op implementations. The owning
// modules must provide real definitions before any callback can be called.
#pragma once
#include <cstdint>
#include <cstring>

#include "game/game_state.h"
#include "game/globals.h"
#include "game/campaign_flow.h"
#include "game/legacy_fields.h"

namespace dl2 {

// ----------------------------------------------------------------------------------------
// Tablas estáticas del EXE
// ----------------------------------------------------------------------------------------
// Canonical table contracts. The former hand-written rows assigned incorrect
// meanings/types to several offsets and declared data with no definition.
// Consumers of this header use data:: field names (buildLabor/upkeep/defense,
// speed/range, productionQueue/dialogAnim, treeIcon/treeY/treeX).
constexpr int kNumUnitTypes = data::kNumUnitTypes;
constexpr int kNumBuildingTypes = data::kNumBuildingTypes;
using UnitTypeRow = data::UnitDef;
using BuildingTypeRow = data::BuildingDef;
using TechStaticRow = data::TechDef;
inline constexpr auto& kUnitTable = data::kUnitTypes;
inline constexpr auto& kBuildingTable = data::kBuildingTypes;
inline constexpr auto& kTechTable = data::kTechs;
inline constexpr data::MemberTableView<data::BuildingDef, data::kNumBuildingTypes, &data::BuildingDef::name>
    kBuildingNames{data::kBuildingTypes};
using econ::kBuildingCosts;
// Declaration only: legacy gs tech initialization is not integrated.
void initTechTable();
using data::kRaceStatsDefault;
using data::kRaceNames;
using data::kMaterialNamesLower;
using data::kMaterialUnitNames;
using data::kDepositNames; // Five entries; AmountNames begins immediately afterwards.
using data::kAmountNames;
inline constexpr auto& kDepositMaterials = data::kBonusMaterials;
using data::kDepositTerrainValue;

// One explicitly legacy mutable campaign bridge, never used by owned runtime.
// Aliased member names are goal[].count/param[]/done, not the obsolete cond[].flag.
using CampaignCondition = econ::CampaignGoal;
using CampaignRow = econ::CampaignDef;
constexpr int kNumCampaigns = data::kNumCampaigns;
inline auto& kCampaignTable = econ::gCampaigns;
using CampaignPlayerRow = CampaignPlayerDef; // kCampaignPlayers from campaign_flow.h

// ----------------------------------------------------------------------------------------
// RTL de Borland: lrand() (FUN_004ae5d8) y RandRangeTagged (FUN_0046c9d8)
// ----------------------------------------------------------------------------------------
// lrand(): estado de 64 bits (lo = semilla de rand(), hi en +0x48): state = state * 0x0000015A00004E35 + 1,
// devuelve hi & 0x7fffffff. Comparte la palabra baja con rtl::rand()/rtl::srand(); la palabra alta la
// mantiene este módulo (se pone a 0 con lrandReset(), que debe llamarse tras cada srand).
uint32_t lrand();
void     lrandReset();
int      randRangeTagged(int n, const char* tag);   // FUN_0046c9d8: n==0 ? 0 : lrand() % n

// ----------------------------------------------------------------------------------------
// Acceso a campos de las estructuras cuyo significado se ha demostrado en este módulo
// ----------------------------------------------------------------------------------------
// Legacy gs-only helpers, NOT for save::Document. Army +0x3c is CURRENT location:
// ReLinkArmy writes it and DeleteUnit removes the unit from that territory.
// +0x38 is the turn-start/base location; _MoveUnit leaves it unchanged and
// FUN_004471c0 later synchronizes it. It is NOT an order destination.
// Use game/army_state.h for the owning document's file-index representation.
inline Territory* armyCurrent(const Army& a)     { return ptr(a.dest); }
inline Territory* armyTurnStart(const Army& a) { return ptr(a.territory); }
inline void       setArmyCurrent(Army& a, Territory* t)     { a.dest = ref(t); }
inline void       setArmyTurnStart(Army& a, Territory* t) { a.territory = ref(t); }
// Army+0x24 ("moves" en game_state.h) son las ÓRDENES de combate (FUN_00447a68 -> Warrior+9):
// 1 asalto, 2 especial, 4 carga, 0x10 atacar shrine, 0x17 misil sin Targetting Computers, 0x1a evadir, 5+cat atacar edificios.
inline uint8_t& armyOrders(Army& a) { return a.moves; }
// Army+0x2c = daño acumulado (unk_2c), +0x2a = nivel de veteranía (unk_2a), +0x25 = misión (unk_25), +0x44 objetivo de misil.
inline int16_t& armyVetLevel(Army& a) { return a.unk_2a; }
// armyDamage / armyMission are defined once in legacy_fields.h.
// Territory+0x8a8 (exploredMask): máscara de jugadores que han MINADO el territorio (FUN_00485344 la fija,
// FUN_0045d984 "blow away mines?" la borra, el combate crea 24 minas por ella).
inline uint32_t& territoryMineMask(Territory& t) { return t.exploredMask; }
// Territory+0x8b0: máscara de jugadores que conocen el shrine (FUN_00486964, FUN_00483d58).
inline uint32_t& territoryShrineMask(Territory& t) { return *reinterpret_cast<uint32_t*>(&t.unk_8b0[0]); }
// Territory+0xa70 + jugador*2: distancia de ruta (FUN_00446b3c/FUN_00446b94 la calculan).
inline int16_t& territoryPathDist(Territory& t, int player) {
    return *reinterpret_cast<int16_t*>(&t.unk_9b4[0xa70 - 0x9b4 + player * 2]);
}
// Territory+0x9b2 (colonyFlag): contador de bajas de población pendientes en combate (int16 con signo).
inline int16_t& territoryPopLoss(Territory& t) { return *reinterpret_cast<int16_t*>(&t.colonyFlag); }
// BuildingSite+0x10: banderas de carretera/hoverway de la casilla (FUN_0045209c -> terreno del combate).
inline int8_t siteRoadFlags(const BuildingSite& s) { return int8_t(s.unk_05[0x10 - 0x05]); }
// BuildingSite+0x18/+0x19: tipo/raza del edificio dibujado en la casilla (FUN_00456618).
inline uint8_t& siteCachedType(BuildingSite& s) { return s.unk_18[0]; }
inline uint8_t& siteCachedRace(BuildingSite& s) { return s.unk_18[1]; }
// Building+0x14 (turnsLeft): en edificios terminados acumula el DAÑO de combate (FUN_004526b0).
// Tile: Ptr32<Tile>::raw = 1 + y*kMapMaxSize + x (0 = null). Convención de este módulo (ver informe).
inline Tile* tilePtr(Ptr32<Tile> p) { return p.raw ? &gs.tiles[0][0] + (p.raw - 1) : nullptr; }
inline Ptr32<Tile> tileRef(int x, int y) { return {uint32_t(1 + y * kMapMaxSize + x)}; }

// techKnown's shared signed-mask / shift contract lives in legacy_fields.h.

// Territorio i (1..numTerritories) y número de territorios.
inline int numTerritories() { return gs.world.numTerritories; }

// ----------------------------------------------------------------------------------------
// Unimplemented cross-module contracts (no automatic fallback binding)
// ----------------------------------------------------------------------------------------
namespace ext {

using Arg = std::intptr_t;   // argumentos de LogEvent: char*, Territory*, int, ...
inline Arg arg(const char* s)  { return reinterpret_cast<Arg>(s); }
inline Arg arg(Territory* t)   { return reinterpret_cast<Arg>(t); }
inline Arg arg(const Territory* t) { return reinterpret_cast<Arg>(t); }
inline Arg arg(int v)          { return Arg(v); }
inline Arg arg(unsigned v)     { return Arg(v); }

// Historical proposed event ABI; no fallback event implementation is integrated.
struct EventRecord { int player; int type; Arg a, b, c, d; int p7, p8; };

namespace fb {
    int  logEvent(int player, int type, Arg a, Arg b, Arg c, Arg d);
    void logEventEx(int player, int type, Arg a, Arg b, Arg c, Arg d, int p7, int p8);
    bool hasPact(int p1, int p2, unsigned mask);
    bool hasPact2(int p1, int p2, unsigned mask);
    int  makePact(int p1, int p2, unsigned mask);
    int  breakPact(int p1, int p2, unsigned mask);
    void deleteUnit(Army* a);
    int  relinkArmy(Army* a, Territory* t, Ptr32<Army>* from, Ptr32<Army>* to);
    int  moveUnit(Army* a, Territory* dest, Territory* origin);
    void removeArmyFromTaskForce(Army* a);
    void disbandUnit(Army* a);
    int  canCreateUnit(Territory* t, int unitType);
    Army* syncCreateUnit(Territory* t, int player, int unitType);
    Building* syncCreateBuilding(Territory* t, int buildingType);
    int  deleteBuilding(Territory* t, int site);
    void redistributeLabor(Territory* t, int count, Building* b, int, int);
    void buildingCost(const Player* p, int buildingType, int terrain, int out[13]);
    void recalcTerritory(Territory* t);
    void getBuildingTasks(Player* p, Building* b);
    void moveLaborToHousingNoNet(Territory* t, Building* b, int slot);
    int  territoryMaxPopulation(Territory* t);
    void doRiot(Territory* t, int amount);
    int  addDeposit(Territory* t, int material);
    int  removeDeposit(Territory* t, int material);
    void resetTerritoryForOwner(Territory* t, int player);
    int  canDoMission(Army* a, int mission, int race);
    int  canBuildSettlement(Army* a);
    void checkDiscovery(Territory* t, int player, int unitType);
    void computePathDistances(Territory* from, int player, int maxDist, int flags);
    void runAITurns();
    void aiPostTurn();
    void playerInitAI(int player);
    void aiInitJobs(int player);
    void raceStatsInit();
    void logisticsPhase();
    void productionPhase();
    void seaPhase();
    void seaManipulationFlags(int);
    void seaManipulationEffects();
    void endOfTurnEconomy();
    void longRangeScan(int);
    void pactsExpire();
    void transferArrivals();
    void refreshMap();
    void waitSync(const char* tag);
    void syncBeginTurn(int turn);
    void synchronizeGame();
    void netProgressBegin(int, const char* title, const char* text, int, int);
    void netProgressEnd();
    void netProgressPump();
    void netResync();
    void setTurnDone(int player);
    void autoSave();
    void rebuildBuildingLists();
    void rebuildArmyFreeList();
    // Eventos registrados por fb::logEvent/fb::logEventEx (para tests).
    const EventRecord* events(int* count);
    void clearEvents();
}

extern int  (*logEvent)(int, int, Arg, Arg, Arg, Arg);         // FUN_00423690 LogEvent (mensajes)
extern void (*logEventEx)(int, int, Arg, Arg, Arg, Arg, int, int);       // FUN_004237d0 LogEventEx (mensajes)
extern bool (*hasPact)(int, int, unsigned);          // FUN_004412d4 HasPact (pactos)
extern bool (*hasPact2)(int, int, unsigned);         // FUN_00441388 (pactos, relations2)
extern int  (*makePact)(int, int, unsigned);         // FUN_00441700 (pactos)
extern int  (*breakPact)(int, int, unsigned);        // FUN_004415d0 BreakPact (pactos)
extern void (*deleteUnit)(Army*);       // FUN_00445fd4 DeleteUnit (ejércitos)
extern int  (*relinkArmy)(Army*, Territory*, Ptr32<Army>*, Ptr32<Army>*);     // FUN_00445898 ReLinkArmy (ejércitos)
extern int  (*moveUnit)(Army*, Territory*, Territory*);         // FUN_00446084 _MoveUnit (unidades)
extern void (*removeArmyFromTaskForce)(Army*); // FUN_0040adf4 (task forces)
extern void (*disbandUnit)(Army*);      // FUN_00445f08 (ejércitos)
extern int  (*canCreateUnit)(Territory*, int);    // FUN_00445b94 CanCreateUnit (unidades)
extern Army* (*syncCreateUnit)(Territory*, int, int);   // FUN_00477784 SyncCreateUnit (red)
extern Building* (*syncCreateBuilding)(Territory*, int); // FUN_00477904 SyncCreateBuilding (red)
extern int  (*deleteBuilding)(Territory*, int);   // FUN_0044cd50 _DeleteBuilding (edificios)
extern void (*redistributeLabor)(Territory*, int, Building*, int, int);// FUN_0044c9a0 (edificios)
extern void (*buildingCost)(const Player*, int, int, int[13]);     // FUN_0044de9c (edificios)
extern void (*recalcTerritory)(Territory*);  // FUN_0044bea8 (edificios/trabajo)
extern void (*getBuildingTasks)(Player*, Building*); // FUN_0044e7ec GetBuildingTasks (edificios)
extern void (*moveLaborToHousingNoNet)(Territory*, Building*, int); // FUN_0044c368 (edificios)
extern int  (*territoryMaxPopulation)(Territory*); // FUN_0046b0e4 (población)
extern void (*doRiot)(Territory*, int);           // FUN_0046c310 DoRiot (población)
extern int  (*addDeposit)(Territory*, int);       // FUN_004667ac (mundo)
extern int  (*removeDeposit)(Territory*, int);    // FUN_0046681c "RemoveB" (mundo)
extern void (*resetTerritoryForOwner)(Territory*, int); // FUN_0046e56c (población)
extern int  (*canDoMission)(Army*, int, int);     // FUN_00416e70 (misiones)
extern int  (*canBuildSettlement)(Army*); // FUN_00416e20 (misiones)
extern void (*checkDiscovery)(Territory*, int, int);   // FUN_00446cf0 CheckDiscovery (unidades)
extern void (*computePathDistances)(Territory*, int, int, int); // FUN_00446b3c (unidades)
extern void (*runAITurns)();       // FUN_0045f2d8 RunAITurns (ministros)
extern void (*aiPostTurn)();       // FUN_00405378 (ministros)
extern void (*playerInitAI)(int);     // FUN_00401830 PlayerInitAI (ministros)
extern void (*aiInitJobs)(int);       // FUN_00404f5c (ministros)
extern void (*raceStatsInit)();    // FUN_00441128 RaceStatsInit
extern void (*logisticsPhase)();   // FUN_0046f804 (investigación auto; ver research.cpp)
extern void (*productionPhase)();  // FUN_0046c780 (economía)
extern void (*seaPhase)();         // FUN_0046eea0 (mar)
extern void (*seaManipulationFlags)(int); // FUN_0046f0e0 (mar)
extern void (*seaManipulationEffects)(); // FUN_0046f404 SeaManipulationEffects
extern void (*endOfTurnEconomy)(); // FUN_0046c7d4 (economía: comida, producción, revueltas; llama a ResearchProgress)
extern void (*longRangeScan)(int);    // FUN_0046e730 (visibilidad)
extern void (*pactsExpire)();      // FUN_00441400 (pactos)
extern void (*transferArrivals)(); // FUN_00471b3c (transferencias)
extern void (*refreshMap)();       // FUN_0046e338 (visibilidad/UI)
extern void (*waitSync)(const char*);         // FUN_0046e9f4 WaitSync (red)
extern void (*syncBeginTurn)(int);    // FUN_0046ed64 SyncBeginTurn (red)
extern void (*synchronizeGame)();  // FUN_0047b3a8 SynchronizeGame (red)
extern void (*netProgressBegin)(int, const char*, const char*, int, int); // FUN_00427eb4 (UI red)
extern void (*netProgressEnd)();   // FUN_00427ee8 (UI red)
extern void (*netProgressPump)();  // FUN_00427f04 (UI red)
extern void (*netResync)();        // FUN_00478090 (red)
extern void (*setTurnDone)(int);      // FUN_00476ffc (red: msg 0x32 + turnDone)
extern void (*autoSave)();         // FUN_00470740 AutoSave (guardar)
extern void (*rebuildBuildingLists)(); // FUN_0044cabc
extern void (*rebuildArmyFreeList)();  // FUN_00445710

} // namespace ext

// Nombre de raza de un jugador (PTR_s_ChCh_t_00509038[Player::race]).
inline const char* raceNameOf(int player) {
    int r = gs.players[player].race;
    return (r >= 0 && r < 7) ? kRaceNames[r] : "";
}

} // namespace dl2
