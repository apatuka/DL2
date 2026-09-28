// newgame.h - Arranque de partida: ResetVariables, RaceInit (aterrizaje), reglas de sitios de
// aterrizaje, colocación de shrines, RaceStatsInit y la máquina de estados de GetGameOptions.
//
// Rangos: 0x426000-0x428000 (reglas de aterrizaje, sólo lógica), 0x46d2e8-0x46da14 (PlayerLanding,
// RaceInit, ResetVariables), 0x467c8c-0x469074 (GetGameOptions y sus manejadores, sólo la lógica),
// 0x441128 (RaceStatsInit), 0x466508 (PlaceShrines), 0x474718 (AddPlayerAtTerritory).
#pragma once
#include <cstdint>

#include "game/game_state.h"
#include "game/globals.h"

namespace dl2 {

// ----------------------------------------------------------------------------------------
// Tablas del EXE
// ----------------------------------------------------------------------------------------
extern const char* const kRaceNames[7];         // PTR_s_ChCh_t_00509038
extern const char* const kAiLeaderNames[7];     // PTR_s_Sting_00509938
extern const char       kRaceShortNames[7][6];  // s_ChCht_005099cf ("%s%03d")
extern const char* const kRaceUpperNames[7];    // PTR_s_CHCHT_004d5188 (entradas de LEVELS.HDD "%s%d")
extern const int16_t     kRaceStatsDefault[64][8]; // DAT_004fc50c
extern const int16_t     kRaceStatsRows61[3][8];   // DAT_004fc8dc
extern const int32_t     kLandingTerrainScore[6];  // DAT_004b7d5c (FUN_00427854)
extern const int32_t     kWinCitiesChoices[5];     // DAT_004c425c {2,3,5,7,10}
extern const int32_t     kWinShrinesChoices[3];    // DAT_004c4274 {2,3,5}
extern const int32_t     kWinTurnsChoices[3];      // DAT_004c4280 {3,5,8}

// ----------------------------------------------------------------------------------------
// Reset / inicialización
// ----------------------------------------------------------------------------------------
void ResetVariables(int resetNetwork);           // orig: FUN_0046da14 (ResetVariables)
void ResetVictoryCounters(int all);              // orig: FUN_00486910
void ResetQueuesAndLocalLists();                 // orig: FUN_0046c9f8
void ResetSpies();                               // orig: FUN_0047d460 (port local; el módulo de espionaje puede sustituirlo vía flow::cb.resetSpies)
void RaceStatsInit();                            // orig: FUN_00441128 (RaceStatsInit)
void RaceStatsAdjust(int race, int16_t delta);   // orig: FUN_004410fc

// ----------------------------------------------------------------------------------------
// Aterrizaje (RaceInit) y reglas de sitio
// ----------------------------------------------------------------------------------------
enum class LandingVerdict { Ok = 0, Ocean, Wasteland, AdjacentToEnemy, Owned, NoTerritory };
extern const char* const kLandingMessages[5];    // "We may land here." / "Can't Land: ..."

LandingVerdict CanLandAt(int territoryIndex, char* message = nullptr, size_t messageSize = 0); // orig: FUN_00427ab0 (reglas)
int  BestLandingSite(int player, int allowUnowned, int ignoreEnemies);   // orig: FUN_00427854
int  LandingFirstPlayer();                                               // orig: FUN_00427008 (SelectInit): índice de orden
int  LandingNextPlayer(int orderIndex);                                  // orig: FUN_00426eb8: siguiente jugador (decrementa)
void AutoLanding(int player);                                            // orig: FUN_00426f20: elige sitio para IA/no locales
void PlayerLanding(int player, Territory* t);                            // orig: FUN_0046d2e8 (PlayerLanding)
int  AddPlayerAtTerritory(Territory* t, int race, uint8_t skill);        // orig: FUN_00474718 (editor: 0 ok, 1 ocupado, 2 no válido, 3 lleno)
int  PlaceShrines();                                                     // orig: FUN_00466508 ("Place"/"Place3"/"Place4"/"Place5")
void SwitchLocalPlayer(int player);                                      // orig: FUN_00472fb4 (-1 = siguiente)
int  RaceInit();                                                         // orig: FUN_0046d4ac (RaceInit): devuelve nº de huecos IA
void SetupLandingOrder();                                                // orig: FUN_0042d660 (tabla DAT_00557c54 de orden de jugadores)

// Orden de selección de sitios (DAT_00557c54[7], DAT_0055778c, DAT_00557580, DAT_00557788)
struct LandingState {
    int order[7] = {};      // DAT_00557c54: jugador en cada posición
    int orderIndex = 0;     // DAT_0055778c
    int firstPlayer = 0;    // DAT_00557580
    int current = 0;        // DAT_00557788 jugador que elige ahora
    int done = 0;           // DAT_00557578
    int allowEnemyAdjacent = 0; // DAT_00557784
    int selected = 0;       // DAT_00557790 territorio marcado
};
extern LandingState landing;

// ----------------------------------------------------------------------------------------
// GetGameOptions (FUN_00469074): máquina de estados del menú principal / nueva partida.
// Los estados son los valores 0x15..0x55 que devuelven los manejadores; las pantallas se piden a la
// UI mediante hooks::ui.menu (ver hooks.h) y aquí sólo se aplica la lógica.
// ----------------------------------------------------------------------------------------
enum GameOptionsState : int {
    GO_LoadCampaignRace = 0x15,   // FUN_00467fc0: selección de raza -> primera campaña
    GO_LoadScenarioMenu = 0x2c,   // FUN_004680ac
    GO_LoadGame         = 0x2e,   // FUN_00468d3c
    GO_EditorMenu       = 0x2f,   // FUN_004680e4
    GO_Quit             = 0x33,   // devuelve 0
    GO_Start            = 0x34,   // FUN_0046787c -> 0x35
    GO_MainMenu         = 0x35,   // FUN_00467c8c
    GO_GameStyle        = 0x36,   // FUN_004681ac
    GO_NetworkInit      = 0x37,   // FUN_00468214
    GO_NetworkInit2     = 0x38,   // FUN_00468214
    GO_NotImplemented   = 0x39,   // FUN_00468384
    GO_GameName         = 0x3b,   // FUN_00468470
    GO_GameOptions      = 0x3c,   // FUN_00468394
    GO_WorldOptions     = 0x3d,   // FUN_004684d0
    GO_MemoryCheck      = 0x3e,   // FUN_0046878c
    GO_PlayerName       = 0x3f,   // FUN_00468800
    GO_NetRegister      = 0x40,   // FUN_00468a28
    GO_NetConnect       = 0x41,   // FUN_00468c94
    GO_NetStart         = 0x43,   // FUN_00468ea4
    GO_Play             = 0x46,   // devuelve 1
    GO_LoadMap          = 0x55    // FUN_004687d4
};
int GetGameOptionsStep(int state);   // ejecuta el manejador de `state` y devuelve el siguiente (0/1 = fin)
int GetGameOptions();                // orig: FUN_00469074 (GetGameOptions): bucle desde 0x34; 1 = jugar, 0 = salir
int MainMenuStep();                  // orig: FUN_00467c8c
int WorldOptionsStep();              // orig: FUN_004684d0 (WorldOptionsDialog) - lógica
void WorldOptionsApply(int sizeIndex, int players, int winCitiesIndex, int aiSkill, int victory); // orig: FUN_00467b2c
int GameOptionsStep();               // orig: FUN_00468394
int StartCampaignForRace(int race);  // orig: FUN_00467fc0 (con la raza ya elegida)
void NextCampaignChapter();          // orig: FUN_00468030
int CheckWorldMemory();              // orig: FUN_00466ddc (siempre 1 en el port)

} // namespace dl2
