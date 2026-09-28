// gameflow.cpp - segundo RNG del juego, RandRangeTagged, SyncSetRandomSeed y tabla de callbacks.
#include "game/gameflow.h"

#include "game/rtl_compat.h"

namespace dl2 {

namespace flow {
Callbacks cb{};
}

// orig: FUN_0046ca40 (Rand2)  LCG "ANSI" con semilla DAT_0058f1f8 (UI, IA, selección de raza, tipo de mundo)
int rand2() {
    gg.rng2Seed = gg.rng2Seed * 0x41C64E6Du + 0x3039u;
    return int((gg.rng2Seed >> 16) & 0x7FFFu);
}

// orig: FUN_0046ca60 (SRand2)
void srand2(uint32_t seed) { gg.rng2Seed = seed; }

// orig: FUN_0046c9d8 (RandRangeTagged)  lrand() % n; la etiqueta ("SaveGame", "Place", "Scandal"...)
// sólo se usa para depuración en el original.
int RandRangeTagged(int n, const char* /*tag*/) {
    if (n == 0) return 0;
    return int(rtl::lrand()) % n;   // FUN_0046c9d8 usa división con signo, también si n < 0.
}

// orig: FUN_00477394 (SyncSetRandomSeed)
void SyncSetRandomSeed(uint32_t seed) {
    if (gg.netGame == 0) {
        rtl::srand(seed);
        srand2(seed);
    } else if (flow::cb.broadcastRandomSeed) {
        flow::cb.broadcastRandomSeed(seed);
    }
}

} // namespace dl2
