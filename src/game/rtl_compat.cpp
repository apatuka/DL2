// rtl_compat.cpp - LCG de Borland C++ 5 (rand/srand/random) reproducido bit a bit.
#include "game/rtl_compat.h"

#include <chrono>

namespace dl2::rtl {

static uint32_t g_seed = 0x015A4E35u;   // valor inicial de _seed en la RTL de Borland (lo, +0x44)
static uint32_t g_seedHi = 0;           // mitad alta (+0x48): sólo la toca lrand()

void srand(uint32_t s) { g_seed = s; g_seedHi = 0; }   // FUN_004ae594
uint32_t seed() { return g_seed; }
uint32_t seedHi() { return g_seedHi; }

// FUN_004ae5d8 (desensamblado): edx:eax = lo*0x4E35; edx += lo*0x15A + hi*0x4E35; +1 con acarreo.
// Es decir, seed64 = seed64 * 0x0000015A_00004E35 + 1 (el multiplicador de 64 bits es 0x15A:0x4E35,
// NO 0x015A4E35). La mitad baja evoluciona como lo*0x4E35+1 (distinto de rand()).
uint32_t lrand() {
    uint64_t s = (uint64_t(g_seedHi) << 32) | g_seed;
    s = s * 0x0000015A00004E35ull + 1ull;
    g_seed = uint32_t(s);
    g_seedHi = uint32_t(s >> 32);
    return g_seedHi & 0x7FFFFFFFu;
}

int rand() {
    g_seed = g_seed * 0x015A4E35u + 1u;
    return int((g_seed >> 16) & 0x7FFFu);
}

int random(int n) { return n > 0 ? rand() % n : 0; }
int randomRange(int lo, int hi) { return lo + random(hi - lo + 1); }

uint32_t timeSeed() {
    using namespace std::chrono;
    return uint32_t(duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count());
}

} // namespace dl2::rtl
