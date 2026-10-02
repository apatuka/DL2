// Explicit offline ResetVariables/load completion data, not a Win32/UI engine.
#pragma once
#include "game/session_rng.h"
#include <array>

namespace dl2::simulation {
struct LoadStartupContext {
    RngSnapshot rngBeforeReset;
};
struct LoadStartupReport {
    // These generated values are subsequently overwritten by LoadOptions/World.
    uint32_t discardedGameSeed = 0, discardedWorldSeed = 0, discardedWorldRngSeed = 0;
    std::array<RngEvent, 3> resetDraws;
    RngSnapshot rngBeforeEvents;
    // Live, nonserialized reset storage. Persistent arrays belong to Document
    // and must NOT be erased after loading. No original addresses are pointers.
    std::array<uint8_t, 0x50> sessionScratch{}; // 0059f104
    std::array<uint8_t, 0xf960> combatWarriors{}; // 005649e8
    std::array<uint8_t, 0x79e0> combatActions{}; // 00574350
    std::array<uint8_t, 0x10c0> combatEffects{}; // 0057bd38
    int32_t combatActive = 0, actionCount = 0, actionLast = 0x347;
    int32_t effectCount = 0, effectLast = 0x4af;
    // Scalar reset words whose semantics are not yet proven, ordered by the
    // named addresses in load_startup.cpp; remain inert owned data, not code.
    std::array<int32_t, 11> resetWords{};
    int32_t winCitiesEffective = 0;
    std::array<int16_t, kMaxPlayers> victoryScratch{}; // 0065e43a
    int32_t victoryState = 0; // 0065e3ac
    bool loadedFromSave = false; // 004d598c reset0; not inferred from its name
    bool gameAborted = false, loadingMap = false, seaWindowOpen = false;
    bool gameStarted = true, redrawRequested = true; // LoadGame final writes
    bool eventLogActive = true; // AfterMove(load=1),0053b8cc=1; not window delivery.
    bool operator==(const LoadStartupReport&) const = default;
};
// orig: 0046da14(param1=1) -> 0046c9cc/004ae5b0, 004571d4, 00486910,
// plus final offline 004618e8 flags. Read-only source, atomic report/RNG. Input
// is AFTER load profile for final options; generated reset seeds are diagnostic
// only and MUST NOT overwrite options.gameSeed or either loaded world seed.
// No window destruction, UI delivery, full AI turn or game activation is claimed.
bool planLoadStartup(const save::Document& loaded, const LoadStartupContext& context,
                     LoadStartupReport& destination, save::Error& error);

struct SaveRngPlan {
    int32_t gameId = 0;
    std::array<RngEvent, 2> operations;
    RngSnapshot after;
    bool operator==(const SaveRngPlan&) const = default;
};
// orig: 00461488 non-editor/offline -> TaggedRange(10000,"SaveGame") then
// SyncSetRandomSeed. Pure save-boundary planning, not authorization to export a
// partial runtime. The eventual complete-save transaction must commit ID+RNG
// together with a valid saved state; archival copies never call this function.
bool planOfflineSaveRng(const RngSnapshot& before, SaveRngPlan& destination, save::Error& error);
}
