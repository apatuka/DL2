// queues.cpp - Colas de producción de unidades (0x484c74-0x484fa0) e IDs globales (0x474cfc, 0x4750c4,
// 0x47510c).  El pool de QueueHead/QueueRecord es el de queue_pool.cpp (módulo gameflow); como ese pool
// sólo expone QueueFree (libera todos los nodos) y QueueAppend, las operaciones que borran o insertan
// un nodo suelto reconstruyen la cola: los índices Ptr32 de los nodos pueden cambiar, pero nadie fuera
// de la cola conserva punteros a nodos (el cursor se recoloca aquí mismo).
#include "game/economy.h"

#include <cstdio>
#include <cstring>
#include <vector>

#include "game/hooks.h"

namespace dl2::econ {

namespace {

struct Rec { uint8_t bytes[kQueueRecordSaved]; };

// Vuelca los nodos de la cola (en orden) y devuelve la posición del cursor (-1 = ninguno).
int dumpQueue(QueueHead* q, std::vector<Rec>& out) {
    int cursorPos = -1, i = 0;
    for (Ptr32<QueueRecord> p = q->first; p.raw; p = ptr(p)->next, ++i) {
        if (p.raw == q->cursor.raw) cursorPos = i;
        Rec r;
        std::memcpy(r.bytes, ptr(p), kQueueRecordSaved);
        out.push_back(r);
    }
    return cursorPos;
}

// Reconstruye la cola con los nodos dados y coloca el cursor en la posición pedida.
void rebuildQueue(QueueHead* q, const std::vector<Rec>& recs, int cursorPos) {
    QueueFree(ref(q), 0);
    for (const Rec& r : recs) QueueAppend(q, r.bytes);
    q->cursor.raw = 0;
    int i = 0;
    for (Ptr32<QueueRecord> p = q->first; p.raw; p = ptr(p)->next, ++i)
        if (i == cursorPos) { q->cursor = p; break; }
}

} // namespace

// orig: 00484c74 (UnitList::Insert)  Inserta un nodo nuevo delante del cursor (o al principio si el
// cursor es NULL o es el primero); el cursor pasa a ser el nodo nuevo.
void UnitList_Insert(QueueHead* q, const uint8_t rec[0x30]) {
    std::vector<Rec> recs;
    int cursorPos = dumpQueue(q, recs);
    Rec r;
    std::memcpy(r.bytes, rec, kQueueRecordSaved);
    if (q->cursor.raw == 0 || q->cursor.raw == q->first.raw) {
        recs.insert(recs.begin(), r);
        rebuildQueue(q, recs, 0);
        return;
    }
    if (cursorPos < 0) {   // el cursor no está en la lista
        hooks::debugMessage("pThis NULL in UnitList::Insert()");
        return;
    }
    recs.insert(recs.begin() + cursorPos, r);
    rebuildQueue(q, recs, cursorPos);
}

// orig: 00484d2c (UnitList::Delete)  Borra el nodo del cursor; el cursor pasa al siguiente si era el
// primero, o al anterior en otro caso.
void UnitList_Delete(QueueHead* q) {
    if (q->cursor.raw == 0) {
        hooks::debugMessage("pIterance NULL in UnitList::Delete()");
        return;
    }
    std::vector<Rec> recs;
    int cursorPos = dumpQueue(q, recs);
    if (q->cursor.raw == q->first.raw) {
        recs.erase(recs.begin());
        rebuildQueue(q, recs, recs.empty() ? -1 : 0);
        return;
    }
    if (cursorPos < 0) {
        hooks::debugMessage("pThis NULL in UnitList::Delete()");
        return;
    }
    recs.erase(recs.begin() + cursorPos);
    rebuildQueue(q, recs, cursorPos - 1);
}

// orig: FUN_00484e24 (QueuePopFront)  Copia el primer nodo (0x30 bytes) y lo libera.  1 si había nodo.
int QueuePopFront(QueueHead* q, uint8_t rec[0x30]) {
    if (q->first.raw == 0) return 0;
    std::vector<Rec> recs;
    int cursorPos = dumpQueue(q, recs);
    std::memcpy(rec, recs[0].bytes, kQueueRecordSaved);
    bool cursorWasFirst = (q->cursor.raw == q->first.raw);
    recs.erase(recs.begin());
    // el original: si cursor == first -> cursor = first->next; first = first->next
    int newCursor = cursorWasFirst ? (recs.empty() ? -1 : 0) : (cursorPos > 0 ? cursorPos - 1 : -1);
    rebuildQueue(q, recs, newCursor);
    return 1;
}

// orig: FUN_00484ef8 (QueueSetCurUnitType)
void QueueSetCurUnitType(QueueHead* q, uint8_t t) {
    if (q->cursor.raw) ptr(q->cursor)->unitType = t;
}

// orig: FUN_00484f2c (QueueSetCurCount)
void QueueSetCurCount(QueueHead* q, uint16_t n) {
    if (q->cursor.raw) ptr(q->cursor)->count = n;
}

// orig: FUN_00484f74 (QueueSetCurData)  Copia los 11 dwords al nodo del cursor.
void QueueSetCurData(QueueHead* q, const int32_t data[11]) {
    if (q->cursor.raw) std::memcpy(ptr(q->cursor)->data, data, sizeof(int32_t) * 11);
}

// orig: FUN_00484fa0 (MilitiaTrainingBonus)  Bonificación de entrenamiento de una milicia (tipo 0x18)
// según su nivel de experiencia (5/10/15), limitada a 25 acumulados en *accum.
int MilitiaTrainingBonus(Army* a, int* accum) {
    int bonus = 0;
    if (a->type == 0x18) {
        int lvl = ExperienceLevel(a->experience);
        if (lvl == 0) bonus = 5;
        else if (lvl == 1) bonus = 10;
        else if (lvl == 2) bonus = 15;
        int room = 0x19 - *accum;
        if (!(bonus < room)) bonus = room;
        if (bonus < 0) bonus = 0;
        *accum += bonus;
    }
    return bonus;
}

// orig: FUN_00447a40 (ExperienceLevel). Compartido por entrenamiento y combate.
int ExperienceLevel(int xp) { return xp < 100 ? 0 : (xp < 401 ? 1 : 2); }

// orig: FUN_00474cfc (NextGlobalId)  ++gNextGlobalId truncado a u16.
uint16_t NextGlobalId() {
    gs.options.nextGlobalId = int32_t(uint32_t(gs.options.nextGlobalId) + 1u);
    return uint16_t(gs.options.nextGlobalId);
}

// orig: FUN_004750c4 (FindBuildingByGlobalID)  Recorre los 1200 Building buscando id; NULL + DebugMessage.
Building* FindBuildingByGlobalID(unsigned id) {
    for (int i = 0; i < kMaxBuildings; ++i)
        if (gs.buildings[i].id == id) return &gs.buildings[i];
    char buf[128];
    std::snprintf(buf, sizeof buf, "NULL building from FindBuildingByGlobalID, looking for: %X", id);
    hooks::debugMessage(buf);
    return nullptr;
}

// orig: FUN_0047510c (FindArmyByGlobalID)  Recorre los 560 Army buscando id; NULL + DebugMessage.
Army* FindArmyByGlobalID(unsigned id) {
    for (int i = 0; i < kMaxArmies; ++i)
        if (gs.armies[i].id == id) return &gs.armies[i];
    char buf[128];
    std::snprintf(buf, sizeof buf, "NULL army from FindArmyByGlobalID, looking for: %X", id);
    hooks::debugMessage(buf);
    return nullptr;
}

} // namespace dl2::econ
