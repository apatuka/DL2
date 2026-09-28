// turn_api.h - Interfaz del módulo de proceso de turno (turn/combat/events/spies/research/victory)
// con el resto de módulos de src/game.
//
// 1. Tablas estáticas de la sección DATA de DEADLOCK.EXE que la lógica de turno necesita
//    (tipos de unidad, tipos de edificio, tecnologías, RaceStats por defecto, campañas).
//    Extraídas byte a byte del ejecutable (ver docs/TURN_AND_COMBAT.md).
// 2. `lrand()` de la RTL de Borland (FUN_004ae5d8) y `RandRangeTagged` (FUN_0046c9d8).
// 3. Declaraciones de las funciones de OTROS módulos que el proceso de turno invoca. Para no
//    provocar símbolos duplicados mientras esos módulos se portan en paralelo, se invocan a
//    través de punteros (`dl2::ext::*`) inicializados a implementaciones de respaldo
//    (`dl2::ext::fb::*`, ports mínimos/fieles de las funciones originales pequeñas). El módulo
//    propietario debe rebindear el puntero a su implementación real:  `ext::hasPact = &HasPact;`
//    Cada puntero lleva la dirección original y el módulo dueño.
#pragma once
#include <cstdint>
#include <cstring>

#include "game/game_state.h"
#include "game/globals.h"

namespace dl2 {

// ----------------------------------------------------------------------------------------
// Tablas estáticas del EXE
// ----------------------------------------------------------------------------------------
constexpr int kNumUnitTypes     = 39;   // PTR_s_No_Unit_004faf7c, paso 0x24
constexpr int kNumBuildingTypes = 48;   // DAT_004f9dbc, paso 0x32

// Fila de la tabla de unidades (offsets del registro original de 0x24 bytes en el comentario).
struct UnitTypeRow {
    const char* name;      // +0x00
    uint16_t sprite;       // +0x04
    uint16_t unk_06;       // +0x06
    uint16_t icon;         // +0x08
    uint8_t  unk_0a;       // +0x0a
    uint8_t  unitClass;    // +0x0b  DAT_004faf87 (Army::unitClass): 1 infantería, 2 cañón, 3 avión, 9 cabeza nuclear, 10 defensa, 0x14 mina...
    uint16_t cost;         // +0x0c  créditos
    uint8_t  buildTime;    // +0x0e
    uint8_t  techRequired; // +0x0f  DAT_004faf8b  TechId necesaria
    uint8_t  moves;        // +0x10  DAT_004faf8c  puntos de movimiento (FUN_00447190)
    uint8_t  domain;       // +0x11  DAT_004faf8d  1 tierra, 2 mar, 3 aire, 6 hover (AAV)
    uint8_t  unk_12;       // +0x12
    int8_t   attack;       // +0x13  DAT_004faf8f  fuerza de ataque (FUN_00447c2c)
    int8_t   hitPoints;    // +0x14  DAT_004faf90  puntos de vida (FUN_00447da4)
    int8_t   speed;        // +0x15  DAT_004faf91  velocidad (cuenta atrás de movimiento, FUN_00447f44); -1 inmóvil
    int8_t   rof;          // +0x16  DAT_004faf92  cadencia (cuenta atrás de disparo, FUN_00448008); -1 no dispara
    int8_t   range;        // +0x17  DAT_004faf93  alcance al CUADRADO (FUN_004480a8 vs distancia² FUN_00451180)
    uint8_t  sound;        // +0x18
};
extern const UnitTypeRow kUnitTable[kNumUnitTypes];

// Fila de la tabla de edificios (registro original de 0x32 bytes; el nombre va aparte).
struct BuildingTypeRow {
    uint16_t sprite;       // +0x04
    uint8_t  icon;         // +0x06
    uint8_t  category;     // +0x07  DAT_004f9dc3 -> Building::category (0x0b shrine, 0x11 vivienda, 0x12 defensa, 0x13 bunker, 0x14 plataforma)
    uint8_t  labor;        // +0x08  DAT_004f9dc4
    uint8_t  size;         // +0x09  DAT_004f9dc5  casillas de lado (1, 2 o 5 = plataforma marina)
    uint16_t hitPoints;    // +0x0a  DAT_004f9dc6  puntos de construcción / vida (FUN_0044de9c[0])
    uint16_t f0c, f0e, f10, f12, f14, f16;
    uint8_t  f18;
    uint8_t  tasks[4];     // +0x19  tareas por ranura (GetBuildingTasks)
    uint8_t  units[10];    // +0x1d  unidades fabricables
    uint8_t  techRequired; // +0x27  DAT_004f9de3
    int8_t   armor;        // +0x28  DAT_004f9de4  vida en combate (FUN_00451de4) / divisor de daño
    uint8_t  f29;
    uint8_t  buildCategory;// +0x2a
    uint8_t  f2b, f2c, f2d;
    uint8_t  anim;         // +0x2e
    uint8_t  f2f, f30, f31;
};
extern const char* const  kBuildingNames[kNumBuildingTypes];
extern const BuildingTypeRow kBuildingTable[kNumBuildingTypes];
extern const int32_t      kBuildingCosts[kNumBuildingTypes][kNumMaterials];   // DAT_004fa71c (FUN_0044de9c)

// Parte estática de la tabla de tecnologías (DAT_004fbbac + i*0x32, offsets 0x14..0x30).
struct TechStaticRow {
    const char* name;      // +0x14
    uint16_t level;        // +0x20
    uint16_t cost;         // +0x22
    uint16_t prereq[3];    // +0x24
    int16_t  flag2c;       // +0x2c
    uint16_t sprite;       // +0x2e
};
extern const TechStaticRow kTechTable[kNumTechs];
void initTechTable();      // copia level/cost/prereq de kTechTable en gs.techs[] (no toca knownMask/progress)

extern const int16_t kRaceStatsDefault[kNumRaceStatRows][8];   // DAT_004fc50c (fuente de gRaceStats)
extern const char* const kRaceNames[7];                          // PTR_s_ChCh_t_00509038
extern const char* const kMaterialNamesLower[kNumMaterials];     // PTR_s_credits_00509098
extern const char* const kMaterialUnitNames[kNumMaterials];      // PTR_s_credits_005090f0 ("tons of food"...)
extern const char* const kDepositNames[7];                       // PTR_s_iron_deposit_00509304
extern const char* const kAmountNames[6];                        // PTR_DAT_00509318 ("no".."horrible amounts of")
extern const int32_t     kDepositMaterials[5];                   // DAT_004dca4c: material de cada tipo de yacimiento
extern const int32_t     kDepositTerrainValue[8];                // DAT_004d5034: valor de casilla por material

// Campañas (DAT_004c6194, 43 entradas de 0xd8): condición k en +0xc + k*0x44.
struct CampaignCondition {
    int32_t type;          // +0x00 (0 = sin condición). Tipos: 1 pacto, 2 territorios, 3 raza viva, 4 tecnologías
                           //       prohibidas, 5 la IA no gana, 6 llegada de jugador, 7/13 territorios propios, 8 recursos,
                           //       9 límite de turnos, 11 raza a eliminar, 12 shrines especiales
    int32_t count;         // +0x04
    int32_t params[14];    // +0x08
    int32_t flag;          // +0x40  estado dinámico (FUN_0044fe58 lo pone a 1; FUN_00450204 guarda el turno)
};
struct CampaignRow {
    int8_t  victory;       // +0x00 -> gVictoryCondition
    int32_t winCities;     // +0x04
    int32_t winShrinesOrTurns; // +0x08
    CampaignCondition cond[3]; // +0x0c
};
constexpr int kNumCampaigns = 43;
extern CampaignRow kCampaignTable[kNumCampaigns];   // NO const: FUN_0044fe58/FUN_00450204 escriben en cond[].flag

// Jugadores de campaña (DAT_004dc434, 10 x 0x9c) usados por FUN_0047c730.
struct CampaignPlayerRow {
    int32_t race;          // +0x00
    int32_t territories[4];// +0x04  candidatos de aterrizaje (FUN_0047c6c0)
    int32_t techLevel;     // +0x14  aprende todas las tecnologías con level <= techLevel
    int32_t credits;       // +0x18
    int32_t materials[10]; // +0x1c  Territory::materials[1..10]
    int32_t units[10][2];  // +0x44  (tipo, cantidad)
    int32_t pactRace;      // +0x94
    int32_t pactMask;      // +0x98
};
extern const CampaignPlayerRow kCampaignPlayers[10];

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
// Army: +0x38 es el DESTINO de la orden de movimiento y +0x3c el territorio ACTUAL (donde está enlazado):
// ReLinkArmy pone +0x3c = territorio nuevo, DeleteUnit busca la lista en +0x3c, FUN_0045723c compara
// +0x38 != +0x3c para saber si hay orden pendiente. game_state.h los nombra al revés (territory/dest).
inline Territory* armyCurrent(const Army& a)     { return ptr(a.dest); }
inline Territory* armyDestination(const Army& a) { return ptr(a.territory); }
inline void       setArmyCurrent(Army& a, Territory* t)     { a.dest = ref(t); }
inline void       setArmyDestination(Army& a, Territory* t) { a.territory = ref(t); }
// Army+0x24 ("moves" en game_state.h) son las ÓRDENES de combate (FUN_00447a68 -> Warrior+9):
// 1 asalto, 2 especial, 4 carga, 0x10 atacar shrine, 0x17 misil sin Targetting Computers, 0x1a evadir, 5+cat atacar edificios.
inline uint8_t& armyOrders(Army& a) { return a.moves; }
// Army+0x2c = daño acumulado (unk_2c), +0x2a = nivel de veteranía (unk_2a), +0x25 = misión (unk_25), +0x44 objetivo de misil.
inline int16_t& armyDamage(Army& a)   { return a.unk_2c; }
inline int16_t& armyVetLevel(Army& a) { return a.unk_2a; }
inline uint8_t& armyMission(Army& a)  { return a.unk_25; }
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

// Tecnología conocida por un jugador (TechEntry::knownMask).
inline bool techKnown(int tech, int player) { return (gs.techs[tech].knownMask >> player) & 1; }

// Territorio i (1..numTerritories) y número de territorios.
inline int numTerritories() { return gs.world.numTerritories; }

// ----------------------------------------------------------------------------------------
// Funciones de otros módulos (punteros rebindeables con implementaciones de respaldo)
// ----------------------------------------------------------------------------------------
namespace ext {

using Arg = std::intptr_t;   // argumentos de LogEvent: char*, Territory*, int, ...
inline Arg arg(const char* s)  { return reinterpret_cast<Arg>(s); }
inline Arg arg(Territory* t)   { return reinterpret_cast<Arg>(t); }
inline Arg arg(const Territory* t) { return reinterpret_cast<Arg>(t); }
inline Arg arg(int v)          { return Arg(v); }
inline Arg arg(unsigned v)     { return Arg(v); }

// Registro que dejan las implementaciones de respaldo de LogEvent (útil para los tests).
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

inline int  (*logEvent)(int, int, Arg, Arg, Arg, Arg)                 = &fb::logEvent;         // FUN_00423690 LogEvent (mensajes)
inline void (*logEventEx)(int, int, Arg, Arg, Arg, Arg, int, int)      = &fb::logEventEx;       // FUN_004237d0 LogEventEx (mensajes)
inline bool (*hasPact)(int, int, unsigned)                             = &fb::hasPact;          // FUN_004412d4 HasPact (pactos)
inline bool (*hasPact2)(int, int, unsigned)                            = &fb::hasPact2;         // FUN_00441388 (pactos, relations2)
inline int  (*makePact)(int, int, unsigned)                            = &fb::makePact;         // FUN_00441700 (pactos)
inline int  (*breakPact)(int, int, unsigned)                           = &fb::breakPact;        // FUN_004415d0 BreakPact (pactos)
inline void (*deleteUnit)(Army*)                                       = &fb::deleteUnit;       // FUN_00445fd4 DeleteUnit (ejércitos)
inline int  (*relinkArmy)(Army*, Territory*, Ptr32<Army>*, Ptr32<Army>*) = &fb::relinkArmy;     // FUN_00445898 ReLinkArmy (ejércitos)
inline int  (*moveUnit)(Army*, Territory*, Territory*)                 = &fb::moveUnit;         // FUN_00446084 _MoveUnit (unidades)
inline void (*removeArmyFromTaskForce)(Army*)                          = &fb::removeArmyFromTaskForce; // FUN_0040adf4 (task forces)
inline void (*disbandUnit)(Army*)                                      = &fb::disbandUnit;      // FUN_00445f08 (ejércitos)
inline int  (*canCreateUnit)(Territory*, int)                          = &fb::canCreateUnit;    // FUN_00445b94 CanCreateUnit (unidades)
inline Army* (*syncCreateUnit)(Territory*, int, int)                   = &fb::syncCreateUnit;   // FUN_00477784 SyncCreateUnit (red)
inline Building* (*syncCreateBuilding)(Territory*, int)                = &fb::syncCreateBuilding; // FUN_00477904 SyncCreateBuilding (red)
inline int  (*deleteBuilding)(Territory*, int)                         = &fb::deleteBuilding;   // FUN_0044cd50 _DeleteBuilding (edificios)
inline void (*redistributeLabor)(Territory*, int, Building*, int, int) = &fb::redistributeLabor;// FUN_0044c9a0 (edificios)
inline void (*buildingCost)(const Player*, int, int, int[13])          = &fb::buildingCost;     // FUN_0044de9c (edificios)
inline void (*recalcTerritory)(Territory*)                             = &fb::recalcTerritory;  // FUN_0044bea8 (edificios/trabajo)
inline void (*getBuildingTasks)(Player*, Building*)                    = &fb::getBuildingTasks; // FUN_0044e7ec GetBuildingTasks (edificios)
inline void (*moveLaborToHousingNoNet)(Territory*, Building*, int)     = &fb::moveLaborToHousingNoNet; // FUN_0044c368 (edificios)
inline int  (*territoryMaxPopulation)(Territory*)                      = &fb::territoryMaxPopulation; // FUN_0046b0e4 (población)
inline void (*doRiot)(Territory*, int)                                 = &fb::doRiot;           // FUN_0046c310 DoRiot (población)
inline int  (*addDeposit)(Territory*, int)                             = &fb::addDeposit;       // FUN_004667ac (mundo)
inline int  (*removeDeposit)(Territory*, int)                          = &fb::removeDeposit;    // FUN_0046681c "RemoveB" (mundo)
inline void (*resetTerritoryForOwner)(Territory*, int)                 = &fb::resetTerritoryForOwner; // FUN_0046e56c (población)
inline int  (*canDoMission)(Army*, int, int)                           = &fb::canDoMission;     // FUN_00416e70 (misiones)
inline int  (*canBuildSettlement)(Army*)                               = &fb::canBuildSettlement; // FUN_00416e20 (misiones)
inline void (*checkDiscovery)(Territory*, int, int)                    = &fb::checkDiscovery;   // FUN_00446cf0 CheckDiscovery (unidades)
inline void (*computePathDistances)(Territory*, int, int, int)         = &fb::computePathDistances; // FUN_00446b3c (unidades)
inline void (*runAITurns)()                                            = &fb::runAITurns;       // FUN_0045f2d8 RunAITurns (ministros)
inline void (*aiPostTurn)()                                            = &fb::aiPostTurn;       // FUN_00405378 (ministros)
inline void (*playerInitAI)(int)                                       = &fb::playerInitAI;     // FUN_00401830 PlayerInitAI (ministros)
inline void (*aiInitJobs)(int)                                         = &fb::aiInitJobs;       // FUN_00404f5c (ministros)
inline void (*raceStatsInit)()                                         = &fb::raceStatsInit;    // FUN_00441128 RaceStatsInit
inline void (*logisticsPhase)()                                        = &fb::logisticsPhase;   // FUN_0046f804 (investigación auto; ver research.cpp)
inline void (*productionPhase)()                                       = &fb::productionPhase;  // FUN_0046c780 (economía)
inline void (*seaPhase)()                                              = &fb::seaPhase;         // FUN_0046eea0 (mar)
inline void (*seaManipulationFlags)(int)                               = &fb::seaManipulationFlags; // FUN_0046f0e0 (mar)
inline void (*seaManipulationEffects)()                                = &fb::seaManipulationEffects; // FUN_0046f404 SeaManipulationEffects
inline void (*endOfTurnEconomy)()                                      = &fb::endOfTurnEconomy; // FUN_0046c7d4 (economía: comida, producción, revueltas; llama a ResearchProgress)
inline void (*longRangeScan)(int)                                      = &fb::longRangeScan;    // FUN_0046e730 (visibilidad)
inline void (*pactsExpire)()                                           = &fb::pactsExpire;      // FUN_00441400 (pactos)
inline void (*transferArrivals)()                                      = &fb::transferArrivals; // FUN_00471b3c (transferencias)
inline void (*refreshMap)()                                            = &fb::refreshMap;       // FUN_0046e338 (visibilidad/UI)
inline void (*waitSync)(const char*)                                   = &fb::waitSync;         // FUN_0046e9f4 WaitSync (red)
inline void (*syncBeginTurn)(int)                                      = &fb::syncBeginTurn;    // FUN_0046ed64 SyncBeginTurn (red)
inline void (*synchronizeGame)()                                       = &fb::synchronizeGame;  // FUN_0047b3a8 SynchronizeGame (red)
inline void (*netProgressBegin)(int, const char*, const char*, int, int) = &fb::netProgressBegin; // FUN_00427eb4 (UI red)
inline void (*netProgressEnd)()                                        = &fb::netProgressEnd;   // FUN_00427ee8 (UI red)
inline void (*netProgressPump)()                                       = &fb::netProgressPump;  // FUN_00427f04 (UI red)
inline void (*netResync)()                                             = &fb::netResync;        // FUN_00478090 (red)
inline void (*setTurnDone)(int)                                        = &fb::setTurnDone;      // FUN_00476ffc (red: msg 0x32 + turnDone)
inline void (*autoSave)()                                              = &fb::autoSave;         // FUN_00470740 AutoSave (guardar)
inline void (*rebuildBuildingLists)()                                  = &fb::rebuildBuildingLists; // FUN_0044cabc
inline void (*rebuildArmyFreeList)()                                   = &fb::rebuildArmyFreeList;  // FUN_00445710

} // namespace ext

// Nombre de raza de un jugador (PTR_s_ChCh_t_00509038[Player::race]).
inline const char* raceNameOf(int player) {
    int r = gs.players[player].race;
    return (r >= 0 && r < 7) ? kRaceNames[r] : "";
}

} // namespace dl2
