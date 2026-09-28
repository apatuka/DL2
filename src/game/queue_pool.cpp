// queue_pool.cpp - Pool de QueueHead / QueueRecord y primitivas del original.
#include "game/queue_pool.h"

#include <cstring>
#include <memory>
#include <vector>

namespace dl2 {
namespace {

// El original usa malloc: insertar otras cabeceras/nodos no invalida direcciones.
// Los unique_ptr reproducen esa propiedad conservando índices Ptr32 compactos.
template <class T>
class Pool {
    struct Slot {
        std::unique_ptr<T> value;
        bool used = false;
    };
    std::vector<Slot> slots;

public:
    Ptr32<T> alloc() {
        for (size_t i = 0; i < slots.size(); ++i) {
            if (!slots[i].used) {
                *slots[i].value = T{};
                slots[i].used = true;
                return {uint32_t(i) + 1u};
            }
        }
        slots.push_back({std::make_unique<T>(), true});
        return {uint32_t(slots.size())};
    }

    T* get(Ptr32<T> p) const {
        if (!p.raw || p.raw > slots.size() || !slots[p.raw - 1].used) return nullptr;
        return slots[p.raw - 1].value.get();
    }

    Ptr32<T> index(const T* value) const {
        if (value) {
            for (size_t i = 0; i < slots.size(); ++i)
                if (slots[i].used && slots[i].value.get() == value)
                    return {uint32_t(i) + 1u};
        }
        return {0};
    }

    void release(Ptr32<T> p) {
        if (get(p)) {
            *slots[p.raw - 1].value = T{};
            slots[p.raw - 1].used = false;
        }
    }

    void clear() { slots.clear(); }
};

Pool<QueueHead> g_heads;
Pool<QueueRecord> g_records;

} // namespace

QueueHead* ptr(Ptr32<QueueHead> p) { return g_heads.get(p); }
QueueRecord* ptr(Ptr32<QueueRecord> p) { return g_records.get(p); }
Ptr32<QueueHead> ref(const QueueHead* q) { return g_heads.index(q); }
Ptr32<QueueRecord> ref(const QueueRecord* r) { return g_records.index(r); }

// orig: FUN_00460a74 (LoadTerritories) / RaceInit: malloc(8) + QueueInit
Ptr32<QueueHead> QueueAlloc() { return g_heads.alloc(); }

// orig: FUN_00484c2c (QueueInit)
void QueueInit(QueueHead* q) { q->first.raw = q->cursor.raw = 0; }

// orig: FUN_00484c40 (QueueFree)
void QueueFree(Ptr32<QueueHead> qp, uint8_t flags) {
    QueueHead* q = ptr(qp);
    if (!q) return;
    while (q->first.raw) {
        const auto current = q->first;
        q->first = ptr(current)->next;
        g_records.release(current);
    }
    // El original deja el cursor colgando; el port conserva un estado vacío válido.
    q->cursor.raw = 0;
    if (flags & 1) g_heads.release(qp);
}

// orig: FUN_00484da8 (QueueAppend), FUN_00484bf0 (constructor del nodo)
void QueueAppend(QueueHead* q, const uint8_t rec[0x30]) {
    const auto index = g_records.alloc();
    QueueRecord* node = ptr(index);
    std::memcpy(node, rec, kQueueRecordSaved);
    node->next.raw = 0;
    if (!q->first.raw) {
        q->first = index;
    } else {
        QueueRecord* last = ptr(q->first);
        while (last->next.raw) last = ptr(last->next);
        last->next = index;
    }
}

// orig: FUN_00484e88 (QueueCount)
int QueueCount(const QueueHead* q) {
    int count = 0;
    for (auto p = q->first; p.raw; p = ptr(p)->next) ++count;
    return count;
}

// orig: FUN_00484ea4 (QueueFirst)
bool QueueFirst(QueueHead* q) { q->cursor = q->first; return q->cursor.raw != 0; }

// orig: FUN_00484ebc (QueueNext)
bool QueueNext(QueueHead* q) {
    if (q->cursor.raw) q->cursor = ptr(q->cursor)->next;
    return q->cursor.raw != 0;
}

// orig: FUN_00484ee0 (QueueCurUnitType)
uint8_t QueueCurUnitType(const QueueHead* q) { return q->cursor.raw ? ptr(q->cursor)->unitType : 0; }

// orig: FUN_00484f10 (QueueCurCount)
uint16_t QueueCurCount(const QueueHead* q) { return q->cursor.raw ? ptr(q->cursor)->count : 0; }

// orig: FUN_00484f48 (QueueCurData)
void QueueCurData(const QueueHead* q, int32_t out[11]) {
    if (q->cursor.raw) std::memcpy(out, ptr(q->cursor)->data, sizeof(int32_t) * 11);
}

void QueuePoolReset() { g_heads.clear(); g_records.clear(); }

} // namespace dl2
