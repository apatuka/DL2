// globals.h - Estado global del juego (equivalente a la sección DATA del EXE) y helpers Ptr32<->objeto.
#pragma once
#include <cstdint>
#include <cstring>

#include "game/game_state.h"

namespace dl2 {

// ----------------------------------------------------------------------------------------
// Globales "sueltos" del original que no forman parte de GameState (ver re/globals.tsv).
// Nombre original (dirección) en el comentario para poder buscar en re/decomp.
// ----------------------------------------------------------------------------------------
struct GameGlobals {
    // --- identidad / red ---
    int      localPlayer = 0;        // DAT_0058f1f4 gLocalPlayer (también GameOptions::localPlayer)
    int      hostPlayer = 0;         // DAT_004d5a58 gHostPlayer
    int      netGame = 0;            // DAT_0058f1fc gNetGame
    int      netJoined = 0;          // DAT_004d5a50 gNetJoined
    int      gameAborted = 0;        // DAT_0058f1ec gGameAborted
    // --- modo / carga ---
    uint8_t  editorMode = 0;         // DAT_004d5aa0 gEditorMode
    int      loadingMap = 0;         // DAT_004d5a88 gLoadingMap
    int      fileGeneration = 4;     // DAT_00583da4 gFileGeneration
    int      fileVersion = 0;        // DAT_00583da8 gFileVersion
    int      mapSizeIndex = 0;       // DAT_004d512c gMapSizeIndex
    // --- listas enlazadas de objetos (índices 1-based, 0 = null; ver ptr()/ref()) ---
    Ptr32<Army>     freeArmies;          // DAT_004c515c gFreeArmies
    Ptr32<Building> activeBuildingsTail; // DAT_005644f4 gActiveBuildingsTail
    Ptr32<Building> freeBuildingsTail;   // DAT_005644f0 gFreeBuildingsTail
    // --- victoria / puntuación ---
    int      playerCities[kMaxPlayers] = {};         // DAT_0065e3cc gPlayerCities
    int      playerShrines[kMaxPlayers] = {};        // DAT_0065e3e8 gPlayerShrines
    int      playerTerritoryCount[kMaxPlayers] = {}; // DAT_0065e3b0 gPlayerTerritoryCount
    int      totalShrines = 0;       // DAT_0065e420 gTotalShrines
    int      winCitiesEffective = 0; // DAT_0065e424 gWinCitiesEffective
    // --- UI / selección (la lógica sólo los lee) ---
    int      selectedTerritory = 0;  // DAT_004c5b50 gSelectedTerritory
    Ptr32<Building> selectedBuilding; // DAT_0053b850 gSelectedBuilding
    int      uiScreen = 0;           // DAT_004d59b4 gUiScreen
    // --- opciones de dispositivo ---
    int      smallSprites = 0;       // DAT_004d5990
    int      lowMem = 0;             // DAT_004d5994
    int      videoOn = 1;            // DAT_004d5aa8
    int      musicOn = 1;            // DAT_004d5aac
    int      soundOn = 1;            // DAT_004d5ab0
    // --- temporizador de turno ---
    int      turnTimerRunning = 0;   // DAT_004d1c84
    uint32_t turnTimerStart = 0;     // DAT_00583da0
    // --- [gameflow] segundo generador (FUN_0046ca40 / FUN_0046ca60), tablas de campaña y arranque ---
    uint32_t rng2Seed = 0;           // DAT_0058f1f8 semilla del LCG 0x41C64E6D (FUN_0046ca40)
    uint32_t campaignFlags = 0;      // DAT_0059f100 gCampaignFlags (CampaignApplyOptions FUN_0044fd14)
    int      startupMode = 0;        // DAT_004d59a8 modo de arranque desde deadlock.ini (bits 1/2/4/0x10)
    int      loadedFromSave = 0;     // DAT_004d598c 1 = partida cargada (no hay RaceInit)
    int      landingDone = 0;        // DAT_004d5a7c 1 cuando termina la selección de sitios de aterrizaje
    int      gameStarted = 0;        // DAT_004d59bc partida en curso (LoadGame lo pone a 1)
    int      netMasterSlave = 0;     // DAT_004d5a4c 0 = maestro en red
    int      netRestore = 0;         // DAT_004d513c 1 = restaurando partida de red desde fichero
    uint8_t  savedRaceMask = 0;      // DAT_0058f12e máscara de razas de la partida guardada de red (FUN_00461e9c)
    int      gameKind = 0;           // DAT_004d5ae0 (2 = tutorial; prefs +0x4c)
    int      numShrinesPlaced = 0;   // DAT_0058eca4 shrines colocados por PlaceShrines (FUN_00466508)
    int      autoSaveVariant = 0;    // DAT_004d5ad0 (prefs +0xd)
    char     scenarioPath[0x400] = {}; // DAT_005597d5 ruta del fichero seleccionado (mapa/partida)
    char     netSavePath[0x400] = {};  // DAT_0058ed2e ruta de la partida de red a restaurar
    int      localPlayerPtrIndex = 0;  // PTR_DAT_004d5988 (índice del jugador local; siempre = localPlayer)
    // --- [ai_taskforce] movimiento de unidades ---
    Ptr32<Army> movingArmy;          // DAT_004c5140 ejército que se está moviendo/evaluando (FUN_00401ac0, FUN_00401a18,
                                     //   FUN_0040e1fc); FUN_00445940 FindTransportWithSpace lo consulta
};

extern GameState   gs;   // todo el estado persistente (Player[], Territory[], Building[], Army[], ...)
extern GameGlobals gg;   // globales sueltos

// ----------------------------------------------------------------------------------------
// Convención de punteros: el original guarda punteros de 32 bits (Ptr32<T>) a objetos que viven
// en arrays globales. En el port, Ptr32<T>::raw contiene el índice 1-based en el array global
// correspondiente (0 = nullptr). ptr() y ref() convierten en ambos sentidos.
// ----------------------------------------------------------------------------------------
inline Building*  ptr(Ptr32<Building> p)  { return p.raw ? &gs.buildings[p.raw - 1] : nullptr; }
inline Army*      ptr(Ptr32<Army> p)      { return p.raw ? &gs.armies[p.raw - 1] : nullptr; }
inline Territory* ptr(Ptr32<Territory> p) { return p.raw ? &gs.territories[p.raw - 1] : nullptr; }
inline Player*    ptr(Ptr32<Player> p)    { return p.raw ? &gs.players[p.raw - 1] : nullptr; }
inline Job*       ptr(Ptr32<Job> p)       { return p.raw ? &gs.jobs[0][0] + (p.raw - 1) : nullptr; }

inline Ptr32<Building>  ref(const Building* b)  { return {b ? uint32_t(b - gs.buildings) + 1u : 0u}; }
inline Ptr32<Army>      ref(const Army* a)      { return {a ? uint32_t(a - gs.armies) + 1u : 0u}; }
inline Ptr32<Territory> ref(const Territory* t) { return {t ? uint32_t(t - gs.territories) + 1u : 0u}; }
inline Ptr32<Player>    ref(const Player* p)    { return {p ? uint32_t(p - gs.players) + 1u : 0u}; }
inline Ptr32<Job>       ref(const Job* j)       { return {j ? uint32_t(j - &gs.jobs[0][0]) + 1u : 0u}; }

// Accesos habituales del original: DAT_005a43d0 + i*0xadc, DAT_0059f160 + i*0x2d8, tiles[y][x]
inline Territory& territory(int index) { return gs.territories[index]; }   // índices 1..numTerritories
inline Player&    player(int index)    { return gs.players[index]; }
inline Tile&      tile(int x, int y)   { return gs.tiles[y][x]; }
inline Player&    localPlayer()        { return gs.players[gg.localPlayer]; }

// Reinicia todo el estado (ResetVariables, FUN_0046da14, hace memset de estos bloques).
void resetGameState();

// [gameflow] Punteros a Tile (Territory::tiles[]): raw = y*kMapMaxSize + x + 1 (0 = nullptr).
inline Tile*      ptr(Ptr32<Tile> p)   { return p.raw ? &gs.tiles[0][0] + (p.raw - 1) : nullptr; }
inline Ptr32<Tile> ref(const Tile* t)  { return {t ? uint32_t(t - &gs.tiles[0][0]) + 1u : 0u}; }
inline int tileX(const Tile* t)        { return int((t - &gs.tiles[0][0]) % kMapMaxSize); }
inline int tileY(const Tile* t)        { return int((t - &gs.tiles[0][0]) / kMapMaxSize); }

} // namespace dl2
