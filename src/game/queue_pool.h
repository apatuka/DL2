// queue_pool.h - Colas de producción sobre pools con índices 1-based (0 = nullptr).
// Recuperado de la sesión Claude y contrastado con FUN_00484c2c .. FUN_00484f48.
// Las direcciones nativas se mantienen al crecer el pool; liberar/reutilizar un
// objeto o QueuePoolReset invalida sus referencias. No conservar handles liberados.
#pragma once
#include <cstdint>

#include "game/game_state.h"

namespace dl2 {

QueueHead* ptr(Ptr32<QueueHead> p);
QueueRecord* ptr(Ptr32<QueueRecord> p);
Ptr32<QueueHead> ref(const QueueHead* q);
Ptr32<QueueRecord> ref(const QueueRecord* r);

Ptr32<QueueHead> QueueAlloc();
void QueueInit(QueueHead* q);                             // FUN_00484c2c
void QueueFree(Ptr32<QueueHead> q, uint8_t flags);         // FUN_00484c40; bit 0 libera cabecera
void QueueAppend(QueueHead* q, const uint8_t rec[0x30]);   // FUN_00484da8; no mueve cursor
int QueueCount(const QueueHead* q);                      // FUN_00484e88
bool QueueFirst(QueueHead* q);                           // FUN_00484ea4
bool QueueNext(QueueHead* q);                            // FUN_00484ebc
uint8_t QueueCurUnitType(const QueueHead* q);             // FUN_00484ee0
uint16_t QueueCurCount(const QueueHead* q);               // FUN_00484f10
void QueueCurData(const QueueHead* q, int32_t out[11]);   // FUN_00484f48; cursor nulo no escribe
void QueuePoolReset();

} // namespace dl2
