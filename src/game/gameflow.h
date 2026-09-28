// gameflow.h - Infraestructura común del módulo "game flow" (saveload / worldgen / newgame / campaign_flow):
//   - segundo generador de números aleatorios del juego (FUN_0046ca40 / FUN_0046ca60),
//   - RandRangeTagged (FUN_0046c9d8) y SyncSetRandomSeed (FUN_00477394),
//   - callbacks hacia módulos de lógica de otros agentes que todavía no exponen cabecera (IA,
//     tecnologías, pactos, temporizador, red...). Por defecto son nullptr y las llamadas se omiten;
//     cada módulo instala la suya al arrancar (igual que hooks::ui para la UI).
//
// Lo que sí tiene cabecera (src/game/economy.h, ai_api.h) se llama directamente: colas de producción,
// IDs globales, FindBuildingByGlobalID/FindArmyByGlobalID, RebuildBuildingLists, RebuildArmyFreeList,
// HasPact, CountShrines, SyncCreateUnit/SyncCreateBuilding, objetivos de campaña (econ::gCampaigns)...
#pragma once
#include <cstdint>

#include "game/globals.h"

namespace dl2 {

// ----------------------------------------------------------------------------------------
// Generadores de números aleatorios del juego
// ----------------------------------------------------------------------------------------
int  rand2();                                  // orig: FUN_0046ca40  seed = seed*0x41C64E6D + 0x3039; (seed>>16)&0x7fff
void srand2(uint32_t seed);                    // orig: FUN_0046ca60  DAT_0058f1f8 = seed
int  RandRangeTagged(int n, const char* tag);  // orig: FUN_0046c9d8  n ? lrand() % n : 0 (tag: sólo depuración)
void SyncSetRandomSeed(uint32_t seed);         // orig: FUN_00477394  local: srand+srand2; red: mensaje 0x4b

// ----------------------------------------------------------------------------------------
// Callbacks a otros módulos de lógica (no UI). nullptr = no disponible (se omite la llamada).
// ----------------------------------------------------------------------------------------
namespace flow {

struct Callbacks {
    // IA (módulo ai_ministers / ai_taskforce)
    void (*initAiPlayer)(int player) = nullptr;                 // FUN_00401830 PlayerInitAI
    void (*resetAi)() = nullptr;                                // FUN_004018d8 (memsets de jobs + PlayerInitAI de las IA)
    void (*aiRelationsInit)() = nullptr;                        // FUN_004050ac (tabla de actitudes IA)
    void (*freeMinisterJobs)() = nullptr;                       // FUN_004057c4 (libera los nodos de las 7 listas)
    // tecnologías / diplomacia
    void (*learnTech)(int player, int tech) = nullptr;          // FUN_00483d58
    void (*makePact)(int p1, int p2, int type) = nullptr;       // FUN_00441700
    void (*checkDiscovery)(Territory* t, int player, int mode) = nullptr;     // FUN_00446cf0 CheckDiscovery
    // turno / temporizadores / victoria
    void (*syncBeginTurn)(int turn) = nullptr;                  // FUN_0046ed64 SyncBeginTurn
    void (*startTurnTimer)(int seconds) = nullptr;              // FUN_0045efd0 TurnTimerStart
    void (*lastPlayerTimerCheck)() = nullptr;                    // FUN_0045f148
    void (*resetCombat)() = nullptr;                            // FUN_004571d4
    void (*resetSeaManipulation)() = nullptr;                   // FUN_0046ee88
    void (*resetSpies)() = nullptr;                             // FUN_0047d460 ResetSpies (si es nullptr se hace un port local)
    // red
    void (*broadcastRandomSeed)(uint32_t seed) = nullptr;       // FUN_004779c0(local, 0x4b, ...) (SyncSetRandomSeed en red)
    void (*netDropPlayer)(int player, int flag) = nullptr;      // FUN_004780e4
    // formato antiguo (gen 0/1)
    int (*findPortTargetTerritory)(Territory* t) = nullptr;     // FUN_0044da3c
    // UI de campaña (intro de capítulo FUN_0042f0c4)
    void (*campaignIntro)(int chapter, int flag) = nullptr;
};

extern Callbacks cb;

} // namespace flow
} // namespace dl2
