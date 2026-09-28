// rtl_compat.h - Reimplementación de las rutinas de la RTL de Borland C++ 5 que afectan al determinismo.
//
// El original usa rand()/srand()/random(n) de la RTL de Borland (FUN_004ae5b0 / FUN_004ae594 / ...):
// generador congruencial lineal de 32 bits, seed = seed * 0x015A4E35 + 1, resultado = (seed >> 16) & 0x7FFF.
// Para que las partidas de red (CalculateGameCRC) y la generación de mundos coincidan con el juego
// original hay que usar exactamente esta secuencia.
#pragma once
#include <cstdint>

namespace dl2::rtl {

void     srand(uint32_t seed);      // FUN_004ae594
uint32_t seed();                    // valor actual de la semilla (para guardar/sincronizar)
int      rand();                    // FUN_004ae5b0: 0..0x7FFF
int      random(int n);             // Borland random(n) = rand() % n  (macro de stdlib.h)
int      randomRange(int lo, int hi); // lo + random(hi - lo + 1)
// FUN_004ae5d8 (Borland _lrand): la semilla es de 64 bits (lo en +0x44, hi en +0x48 del bloque RTL);
// seed64 = seed64 * 0x0000015A00004E35 + 1 (multiplicador 64 bits 0x15A:0x4E35); devuelve hi & 0x7FFFFFFF. rand() sólo actualiza la mitad baja,
// srand() pone hi = 0. El juego lo usa vía FUN_0046c9d8(n, tag) = lrand() % n en la generación de
// mundos, colocación de shrines, eventos aleatorios, espionaje...
uint32_t lrand();
uint32_t seedHi();                  // mitad alta de la semilla (para depuración)

// Borland `time`/`GetTickCount`-based seeds: el juego usa timeGetTime() para semillas iniciales.
uint32_t timeSeed();

} // namespace dl2::rtl
