// buildings.cpp - Objetos Building (pool y listas activa/libre), casillas de construcción, trabajo
// (labor), construcción/demolición/mejora y el Colony Assistant de trabajo.
// Rango original: 0x4483d0-0x448d94 y 0x44b5bc-0x44e0a8 (+ helpers FUN_004023dc / FUN_0040552c).
#include "game/economy.h"

#include <cstring>

#include "game/gameflow.h"
#include "game/hooks.h"

namespace dl2::econ {

Externals ext{};
TaskSummary gTaskSummary[28] = {};
int gAssistantMaxMoves = 0;            // DAT_00564404 (lo fija la UI del Colony Assistant)

namespace {
inline Building* siteBldg(Territory* t, int i) { return ptr(t->sites[i].building); }
inline const BldgType& BT(int type) { return kBuildingTypes[type]; }
inline const BldgType& BT(const Building* b) { return kBuildingTypes[b->type]; }
inline bool locked(const Building* b, int slot) { return (b->flags & bflag::Locked(slot)) != 0; }
inline bool isLaborTask(uint8_t t) { return t == task::Energy || t == task::Culture || t == task::Food; }

// Cola de "nukes" pendientes de registrar (DAT_0059f104, pares {jugador, territorio}; DAT_004d5a9c)
struct NukeEntry { int player; Ptr32<Territory> territory; };
NukeEntry gNukeQueue[10];
int gNukeQueueCount = 0;
} // namespace

// orig: FUN_004023dc (FindTaskSlot)  Ranura 0..4 cuya tarea es taskId, o -1.
int FindTaskSlot(const Building* b, int taskId) {
    for (int i = 0; i < 5; ++i)
        if (b->task[i] == taskId) return i;
    return -1;
}

// orig: FUN_0040552c (SumTaskOutput)  Suma TaskOutput de la tarea en todos los edificios del territorio
// (useMax: con el máximo de colonos en vez de los asignados).
int SumTaskOutput(Territory* t, int taskId, int useMax) {
    int sum = 0;
    for (int i = 0; i < kNumSites; ++i) {
        Building* b = siteBldg(t, i);
        if (!b) continue;
        int slot = FindTaskSlot(b, taskId);
        int labor = (useMax == 0) ? (slot >= 0 ? b->labor[slot] : b->labor[-1 + 1] /*no se usa*/) : MaxLabor(b);
        if (slot != -1) sum += TaskOutput(ownerOf(*t), t, b->site, slot, labor);
    }
    return sum;
}

// orig: FUN_0044b5bc (GetQueue)  Cabecera de la cola de producción 1..5 del territorio.
QueueHead* GetQueue(Territory* t, int queueCat) {
    if (!t) return nullptr;
    if (queueCat < 1 || queueCat > kNumQueues) return nullptr;
    return ptr(t->queues[queueCat - 1]);
}

// orig: FUN_0044b620 (BuildingQueue)  Cola del territorio asociada a la categoría del edificio.
QueueHead* BuildingQueue(Building* b) {
    if (!b) return nullptr;
    return GetQueue(terrOf(*b), BT(b).queueCat);
}

// orig: 0044b65c (TotalUnitLabor)  Producción de "Build Units" de los edificios de la cola queueCat
// (usa la ranura 4: out[3]... el original lee local_10 = out[4]).
int TotalUnitLabor(Territory* t, int queueCat) {
    if (!t) { hooks::debugMessage("NULL pTerritory in TotalUnitLabor()"); return 0; }
    if (queueCat < 0 || queueCat > 5) { hooks::debugMessage("Invalid uqThis in TotalUnitLabor()"); return 0; }
    Player* p = ownerOf(*t);
    int total = 0;
    for (int i = 0; i < kNumSites; ++i) {
        Building* b = siteBldg(t, i);
        if (b && queueCat == BT(b).queueCat) {
            int32_t out[5] = {};
            BuildingTaskOutputs(p, t, i, out, 0);
            total += out[4];
        }
    }
    return total;
}

// orig: 0044b714 (TotalTaskLabor)  Producción total de una tarea en el territorio.
int TotalTaskLabor(Territory* t, int taskId) {
    if (!t) { hooks::debugMessage("NULL pTerritory in TotalTaskLabor()"); return 0; }
    if (taskId < 1 || taskId > 0x15) { hooks::debugMessage("Invalid pTerritory in TotalTaskLabor()"); return 0; }
    Player* p = ownerOf(*t);
    int total = 0;
    for (int i = 0; i < kNumSites; ++i) {
        Building* b = siteBldg(t, i);
        if (!b) continue;
        int32_t out[5] = {};
        BuildingTaskOutputs(p, t, i, out, 0);
        for (int s = 0; s < 5; ++s)
            if (b->task[s] == taskId) { total += out[s]; break; }
    }
    return total;
}

// orig: FUN_0044b7d8 (HousingSpareLabor)  Capacidad libre de las viviendas: MaxLabor - colonos en
// ranuras distintas de "House Populace".
int HousingSpareLabor(Territory* t) {
    int total = 0;
    for (int i = 0; i < kNumSites; ++i) {
        Building* b = siteBldg(t, i);
        if (!b || BT(b).category != cat::Housing) continue;
        int hs = FindTaskSlot(b, task::HousePopulace);
        if (hs == -1) continue;
        total += MaxLabor(b);
        for (int s = 0; s < 5; ++s)
            if (s != hs && b->labor[s] != 0) total -= b->labor[s];
    }
    return total;
}

// orig: 0044b860 (MoveLaborToHousing)  Devuelve un colono de la ranura a la primera vivienda con hueco
// (vía red: FUN_00475ce8).
int MoveLaborToHousing(Territory* t, Building* b, int slot) {
    if (!t || !b) { hooks::debugMessage("Invalid arguments in MoveLaborToHousing()"); return 0; }
    if (b->labor[slot] < 1) { hooks::debugMessage("No labor in MoveLaborToHousing()"); return 0; }
    for (int i = 0; i < kNumSites; ++i) {
        Building* h = siteBldg(t, i);
        if (!h) continue;
        if (TotalLabor(h) < MaxLabor(h)) {
            int hs = FindTaskSlot(h, task::HousePopulace);
            if (hs != -1) {
                NetReassignLabor(t, b, slot, h, hs);
                return 1;
            }
        }
    }
    return 0;
}

// orig: FUN_0044b8f8 (QueueNukeUse)  Apunta un uso de arma nuclear para registrarlo al final del turno.
void QueueNukeUse(Player* p, Territory* t) {
    if (gNukeQueueCount < 10) {
        gNukeQueue[gNukeQueueCount].player = p->index;
        gNukeQueue[gNukeQueueCount].territory = ref(t);
    }
    gNukeQueueCount++;
}

// orig: FUN_0044b924 (RegisterNukeUse)  Evento 0x50 al autor, 0x51 al resto, -20 de moral en todos sus
// territorios y ++nukesUsed.
void RegisterNukeUse(int player, Territory* t) {
    LogEvent(player, 0x50, t);
    for (int i = 0; i < kMaxPlayers; ++i)
        if (player != i) LogEventEx(i, 0x51, kRaceNames[gs.players[player].race], t, 0, 0, player, 0);
    for (int i = 0; i <= gs.world.numTerritories; ++i) {
        Territory& T = gs.territories[i];
        if (player == T.owner) {
            int m = T.morale - 0x14;
            if (m < 0) m = 0;
            T.morale = int8_t(m);
        }
    }
    gs.scores[player].nukesUsed = uint8_t(gs.scores[player].nukesUsed + 1);
}

// orig: FUN_0044b9e4 (FlushNukeQueue)
void FlushNukeQueue() {
    for (int i = 0; i < gNukeQueueCount && i < 10; ++i)
        RegisterNukeUse(gNukeQueue[i].player, ptr(gNukeQueue[i].territory));
}

// orig: FUN_0044ba18 (TotalLabor)  Suma de las 5 ranuras.
int TotalLabor(const Building* b) {
    if (!b) return 0;
    int n = 0;
    for (int i = 0; i < 5; ++i) n += b->labor[i];
    return n;
}

// orig: FUN_0044ba40 (MaxLabor)  Colonos máximos: 4 en obras; viviendas x fila 24 de RaceStats.
int MaxLabor(const Building* b) {
    if (!b || b->type == 0) return 0;
    if (b->turnsLeft != 0) return 4;
    int n = BT(b).maxLabor;
    if (b->category == cat::Housing) {
        int owner = gs.territories[b->territory].owner;
        if (owner != -1) n = (raceStat(24, gs.players[owner].race) * n) / 100;
    }
    return n;
}

// orig: FUN_0044bacc (ResetLaborToHousing)  Vacía todas las ranuras y reparte la mano de obra entre
// las viviendas; luego BalanceLabor.
void ResetLaborToHousing(Territory* t) {
    int pool = 0, spare = 0;
    TerritoryLaborPool(t, &pool, &spare);
    for (int i = 0; i < kNumSites; ++i) {
        Building* b = siteBldg(t, i);
        if (!b) continue;
        for (int s = 0; s < 5; ++s) b->labor[s] = 0;
        int hs = FindTaskSlot(b, task::HousePopulace);
        if (hs != -1) {
            int mx = MaxLabor(b);
            int n = (pool < mx) ? pool : mx;
            pool -= n;
            b->labor[hs] = n;
        }
    }
    BalanceLabor(t);
}

// orig: 0044bb60 (IsBuildTaskDifferent)  ¿Cambia el nº de turnos de construcción/mejora al pasar de
// labor1 a labor2 colonos en la ranura?
bool IsBuildTaskDifferent(Building* b, int slot, int labor1, int labor2) {
    if (!b) { hooks::debugMessage("Invalid building in IsBuildTaskDifferent()"); return false; }
    uint8_t tk = b->task[slot];
    Territory* t = terrOf(*b);
    Player* p = ownerOf(*t);
    int turns1 = 0, turns2 = 0;
    int o1 = TaskOutput(p, t, b->site, slot, labor1);
    int o2 = TaskOutput(p, t, b->site, slot, labor2);
    if (tk == task::Construction) {
        if (o1 != 0) turns1 = (b->turnsLeft + o1 - 1) / o1;
        if (o2 != 0) turns2 = (b->turnsLeft + o2 - 1) / o2;
    } else {
        if (o1 != 0) turns1 = ((UpgradeCost(b) - upgradeProgress(*b)) + o1 - 1) / o1;
        if (o2 != 0) turns2 = ((UpgradeCost(b) - upgradeProgress(*b)) + o2 - 1) / o2;
    }
    return turns1 != turns2;
}

// orig: FUN_0044bc68 (FindSlotToAddLabor)  Ranura desbloqueada con menos colonos (construcción,
// mejora y House Populace cuentan como 999; Build Units sólo con cola no vacía).
int FindSlotToAddLabor(Building* b) {
    int best = 1000, bestSlot = -1;
    QueueHead* q = BuildingQueue(b);
    for (int s = 0; s < 5; ++s) {
        uint8_t tk = b->task[s];
        if (tk == 0 || locked(b, s)) continue;
        int v = 999;
        if (tk != task::Upgrade && tk != task::Construction && tk != task::HousePopulace) {
            if (tk == task::BuildUnits && QueueCount(q) < 1) { /* v = 999 */ }
            else v = b->labor[s];
        }
        if (v < best) { best = v; bestSlot = s; }
    }
    return bestSlot;
}

// orig: FUN_0044bd0c (FindSlotToRemoveLabor)  Ranura desbloqueada con más colonos; prioriza House
// Populace, Build Units con cola y construcción/mejora cuyo tiempo no cambia.
int FindSlotToRemoveLabor(Building* b) {
    int best = -1000, bestSlot = -1;
    QueueHead* q = BuildingQueue(b);
    for (int s = 0; s < 5; ++s) {
        uint8_t tk = b->task[s];
        if (tk == 0 || locked(b, s)) continue;
        int v = 0;
        if (tk == task::HousePopulace || (tk == task::BuildUnits && QueueCount(q) > 0) ||
            ((tk == task::Upgrade || tk == task::Construction) &&
             !IsBuildTaskDifferent(b, s, b->labor[s], b->labor[s] - 1))) {
            if (b->labor[s] != 0) return s;
        } else {
            v = b->labor[s];
        }
        if (best < v) { best = v; bestSlot = s; }
    }
    return bestSlot;
}

// orig: FUN_0044bddc (AdjustLabor)  Añade (delta > 0) o quita (delta < 0) colonos al edificio.
int AdjustLabor(Building* b, int delta) {
    int before = TotalLabor(b);
    int ok = 0;
    if (delta < 1) {
        if (delta < 0) {
            for (int left = -delta; left != 0;) {
                int s = FindSlotToRemoveLabor(b);
                if (s < 0) return 0;
                int n = (left <= b->labor[s]) ? left : b->labor[s];
                b->labor[s] -= n;
                left -= n;
            }
            ok = 1;
        }
    } else {
        int s = FindSlotToAddLabor(b);
        if (s > -1) { b->labor[s] += delta; ok = 1; }
    }
    if (delta > 0 && before == 0 && BT(b).energyUse != 0) b->flags |= bflag::Active;
    return ok;
}

// orig: FUN_0044be88 (ActiveMaxLabor)  MaxLabor si el edificio está activo, 0 si no.
int ActiveMaxLabor(const Building* b) {
    int n = MaxLabor(b);
    if (b && (b->flags & bflag::Active) == 0) n = 0;
    return n;
}

// orig: FUN_0044bea8 (BalanceLabor)  Recorta los colonos de cada ranura a la mano de obra disponible
// (energía/cultura/comida primero, luego el resto, luego las viviendas) y devuelve el sobrante a las
// viviendas.
void BalanceLabor(Territory* t) {
    if (t->population == 0) t->morale = 100;
    int pool = 0, spare = 0;
    TerritoryLaborPool(t, &pool, &spare);
    // pasada 1: energía / cultura / comida
    for (int i = 0; i < kNumSites; ++i) {
        Building* b = siteBldg(t, i);
        if (!b) continue;
        int active = ActiveMaxLabor(b);
        for (int s = 0; s < 5; ++s) {
            if (!isLaborTask(b->task[s])) continue;
            int old = b->labor[s];
            b->labor[s] = int16_t(b->labor[s] < pool ? b->labor[s] : pool);
            b->labor[s] = int16_t(b->labor[s] < active ? b->labor[s] : active);
            pool -= b->labor[s];
            active -= b->labor[s];
            if (b->labor[s] != old) b->flags &= uint16_t(~bflag::Locked(s));
        }
    }
    // pasada 2: resto de tareas de edificios que no son viviendas (ranuras 1,2,3,4,0)
    for (int i = 0; i < kNumSites; ++i) {
        Building* b = siteBldg(t, i);
        if (!b || b->category == cat::Housing) continue;
        int active = ActiveMaxLabor(b);
        for (int k = 0; k < 5; ++k) {
            int s = (k + 1) % 5;
            if (isLaborTask(b->task[s])) { active -= b->labor[s]; continue; }
            int old = b->labor[s];
            b->labor[s] = int16_t(b->labor[s] < pool ? b->labor[s] : pool);
            b->labor[s] = int16_t(b->labor[s] < active ? b->labor[s] : active);
            pool -= b->labor[s];
            active -= b->labor[s];
            if (b->labor[s] != old) b->flags &= uint16_t(~bflag::Locked(s));
        }
    }
    // pasada 3: viviendas
    for (int i = 0; i < kNumSites; ++i) {
        Building* b = siteBldg(t, i);
        if (!b || b->category != cat::Housing) continue;
        int mx = MaxLabor(b);
        for (int s = 0; s < 5; ++s) {
            if (isLaborTask(b->task[s])) { mx -= b->labor[s]; continue; }
            int old = b->labor[s];
            b->labor[s] = int16_t(b->labor[s] < pool ? b->labor[s] : pool);
            b->labor[s] = int16_t(b->labor[s] < mx ? b->labor[s] : mx);
            mx -= b->labor[s];
            pool -= b->labor[s];
            if (b->labor[s] != old) b->flags &= uint16_t(~bflag::Locked(s));
        }
    }
    // pasada 4: el sobrante va a las viviendas con hueco
    for (int i = 0; pool != 0 && i < kNumSites; ++i) {
        Building* b = siteBldg(t, i);
        if (!b || b->category != cat::Housing) continue;
        int freeL = ActiveMaxLabor(b);
        for (int s = 0; s < 5; ++s) freeL -= b->labor[s];
        int n = (freeL < pool) ? freeL : pool;
        int s = FindTaskSlot(b, task::HousePopulace);
        if (s == -1) s = FirstTaskSlot(b);
        b->labor[s] += n;
        pool -= n;
    }
}

// orig: FUN_0044c238 (BalanceLaborNoNet)
void BalanceLaborNoNet(Territory* t) { BalanceLabor(t); }

// orig: FUN_0044c248 (AllSlotsEmptyOrLocked)  1 si no hay ninguna ranura con colonos y desbloqueada.
int AllSlotsEmptyOrLocked(const Building* b) {
    for (int s = 0; s < 5; ++s)
        if (b->labor[s] != 0 && !locked(b, s)) return 0;
    return 1;
}

// orig: FUN_0044c284 (AllTasksNoneOrLocked)  1 si no hay ninguna ranura con tarea y desbloqueada.
int AllTasksNoneOrLocked(const Building* b) {
    for (int s = 0; s < 5; ++s)
        if (b->task[s] != 0 && !locked(b, s)) return 0;
    return 1;
}

// orig: FUN_0044c2c0 (MoveOneLabor)  Mueve un colono de `from` a `to` (NetReassignLabor local).
int MoveOneLabor(Territory* /*t*/, Building* from, Building* to) {
    if (AllSlotsEmptyOrLocked(from) != 0) return 0;
    if (AllTasksNoneOrLocked(to) != 0) return 0;
    if (TotalLabor(to) < MaxLabor(to)) {
        if (AdjustLabor(from, -1) != 0 && AdjustLabor(to, 1) != 0) return 1;
        return 0;
    }
    return 0;
}

// orig: FUN_0044c320 (TransferLabor)  Mueve un colono entre ranuras de dos edificios.
int TransferLabor(Territory* /*t*/, Building* from, int fromSlot, Building* to, int toSlot) {
    if (from->labor[fromSlot] != 0) {
        if (TotalLabor(to) < MaxLabor(to) || to == from) {
            from->labor[fromSlot]--;
            to->labor[toSlot]++;
            return 1;
        }
    }
    return 0;
}

// orig: 0044c368 (MoveLaborToHousingNoNet)
int MoveLaborToHousingNoNet(Territory* t, Building* b, int slot) {
    if (!t || !b) { hooks::debugMessage("Invalid arguments in MoveLaborToHousingNoNet"); return 0; }
    for (int i = 0; i < kNumSites; ++i) {
        Building* h = siteBldg(t, i);
        if (!h) continue;
        if (TotalLabor(h) < MaxLabor(h)) {
            int hs = FindTaskSlot(h, task::HousePopulace);
            if (hs != -1) return TransferLabor(t, b, slot, h, hs);
        }
    }
    return 0;
}

// orig: FUN_0044c3e4 (SetPortTarget)
void SetPortTarget(Territory* t, int16_t target) { t->portTarget = uint16_t(target); }

// orig: FUN_0044c3fc (SetBuildingLabor)  Asigna las 5 ranuras (-1 = no tocar) y los flags de repetición
// del territorio (NetBuildingTasks).
void SetBuildingLabor(Building* b, const int32_t labor[5], uint8_t flags) {
    if (!b) return;
    for (int s = 0; s < 5; ++s)
        if (labor[s] > -1) b->labor[s] = int16_t(labor[s]);
    repeatFlags(gs.territories[b->territory]) = flags;
}

// orig: FUN_0044c44c (_SetBuildingFlags)
void _SetBuildingFlags(Building* b, uint16_t flags, int16_t param10) {
    if (gg.netGame != 0 && !b) {
        hooks::debugMessage("Non-existant building passed to _SetBuildingFlags");
        return;
    }
    if (b) {
        b->flags = flags;
        buildingParam10(*b) = param10;
    }
    BalanceLabor(b ? terrOf(*b) : &gs.territories[0]);
}

// orig: FUN_0044c49c (DistributeLabor)  Reparte `labor` colonos entre las ranuras desbloqueadas del
// edificio (o todo en la ranura 0 si está en obras).
void DistributeLabor(Building* b, int labor) {
    if (!b) return;
    bool allLocked = true;
    QueueHead* q = BuildingQueue(b);
    if (b->turnsLeft == 0) {
        int nOpen = 0, first = -1, lockedSum = 0;
        for (int s = 0; s < 5; ++s) {
            if (b->task[s] == 0) continue;
            if (!locked(b, s) && b->task[s] != task::Upgrade && (s < 4 || (q && QueueCount(q) != 0))) {
                allLocked = false;
                if (first == -1) first = s;
                nOpen++;
            } else {
                lockedSum += b->labor[s];
            }
        }
        labor -= lockedSum;
        if (nOpen == 0) {
            if (labor > 0) {
                do {
                    if (labor == 0) return;
                    labor--;
                    b->labor[0]++;
                } while (MoveLaborToHousingNoNet(terrOf(*b), b, 0) != 0);
            }
        } else {
            if (allLocked) nOpen++;
            int assigned = 0;
            for (int s = 0; s < 5; ++s) {
                if (b->task[s] != 0 && !locked(b, s) && (b->task[s] != task::Upgrade || allLocked) &&
                    (s < 4 || (q && QueueCount(q) != 0))) {
                    b->labor[s] = int16_t(labor / nOpen);
                    assigned += labor / nOpen;
                }
            }
            b->labor[first] += int8_t(int8_t(labor) - int8_t(assigned));
        }
    } else {
        for (int s = 0; s < 5; ++s) {
            b->labor[s] = 0;
            b->flags &= uint16_t(~bflag::Locked(s));
        }
        b->labor[0] = labor;
    }
}

// orig: 0044c654 (CanUpgradeBuilding)  El siguiente tipo de la tabla debe ser de la misma categoría y
// su tecnología conocida; nunca shrines, defensas (18), Luxury Housing, Replication Station ni Kelp Farm.
int CanUpgradeBuilding(Building* b) {
    if (!b) { hooks::debugMessage("NULL building in CanUpgradeBuilding()"); return 0; }
    int type = b->type;
    Territory* t = terrOf(*b);
    if (t->owner == -1 || type > 0x2e || b->category == cat::Defense || b->category == cat::Shrine ||
        type == 3 || type == 0x10 || type == 0x2b || BT(type).category != BT(type + 1).category)
        return 0;
    int tech = BT(type + 1).tech;
    if (tech != 0 && !techKnownBy(tech, t->owner)) return 0;
    return 1;
}

// orig: FUN_0044c718 (UpgradeCost)  (trabajo del tipo siguiente - trabajo del actual) x 3, o -1.
int UpgradeCost(Building* b) {
    if (CanUpgradeBuilding(b) == 0) return -1;
    return (int(BT(b->type + 1).work) - int(BT(b->type).work)) * 3;
}

// orig: FUN_0044c754 (HousedLabor)  Colonos en las ranuras "House Populace" del territorio.
int HousedLabor(Territory* t) {
    int n = 0;
    for (int i = 0; i < kNumSites; ++i) {
        Building* b = siteBldg(t, i);
        if (!b) continue;
        int hs = FindTaskSlot(b, task::HousePopulace);
        if (hs != -1) n += b->labor[hs];
    }
    return n;
}

// orig: 0044c79c (MoveHousingLabor)  Lleva un colono de una vivienda a la ranura `slot` de `b`.
int MoveHousingLabor(Territory* t, Building* b, int slot) {
    if (!t || !b) { hooks::debugMessage("Invalid arguments to MoveHousingLabor()"); return 0; }
    if (b->category == cat::Housing && TotalLabor(b) == MaxLabor(b)) {
        int hs = FindTaskSlot(b, task::HousePopulace);
        if (hs != -1 && slot != -1 && b->labor[hs] != 0) {
            b->labor[slot]++;
            b->labor[hs]--;
            return 1;
        }
        return 0;
    }
    if (TotalLabor(b) < MaxLabor(b)) {
        int tk = b->task[slot];
        if ((tk != task::Construction && tk != task::Upgrade) || TaskUrgency(tk, t, b) > 0) {
            for (int i = 0; i < kNumSites; ++i) {
                Building* h = siteBldg(t, i);
                if (!h) continue;
                int hs = FindTaskSlot(h, task::HousePopulace);
                if (hs != -1 && slot != -1 && h->labor[hs] != 0) {
                    b->labor[slot]++;
                    h->labor[hs]--;
                    return 1;
                }
            }
        }
    }
    return 0;
}

// orig: FUN_0044c8ac (MoveHousingLaborNet)  Igual que MoveHousingLabor pero vía NetReassignLabor.
int MoveHousingLaborNet(Territory* t, Building* b, int slot) {
    if (b->category == cat::Housing && TotalLabor(b) == MaxLabor(b)) {
        int hs = FindTaskSlot(b, task::HousePopulace);
        if (hs != -1 && slot != -1 && b->labor[hs] != 0) {
            NetReassignLabor(t, b, hs, b, slot);
            return 1;
        }
        return 0;
    }
    if (t && b && TotalLabor(b) < MaxLabor(b)) {
        for (int i = 0; i < kNumSites; ++i) {
            Building* h = siteBldg(t, i);
            if (!h) continue;
            int hs = FindTaskSlot(h, task::HousePopulace);
            if (hs != -1 && slot != -1 && h->labor[hs] != 0) {
                NetReassignLabor(t, h, hs, b, slot);
                return 1;
            }
        }
    }
    return 0;
}

// orig: FUN_0044c978 (FirstTaskSlot)  Primera ranura con tarea, o -1.
int FirstTaskSlot(const Building* b) {
    if (b)
        for (int s = 0; s < 5; ++s)
            if (b->task[s] != 0) return s;
    return -1;
}

// orig: FUN_0044c9a0 (AssignLaborFromHousing)  BalanceLabor y, si b != NULL, mueve hasta `count`
// (-1 = todos) colonos de las viviendas a la primera ranura de b que no sea Upgrade.
void AssignLaborFromHousing(Territory* t, int count, Building* b) {
    BalanceLabor(t);
    if (!b) return;
    int housed = HousedLabor(t);
    if (count == -1 || housed < count) count = housed;
    int mx = MaxLabor(b);
    count = (count < mx) ? count : mx;
    int s = 0;
    for (; s < 5; ++s)
        if (b->task[s] != task::Upgrade && b->task[s] != 0) break;
    if (s != 5 && count > 0)
        for (int i = 0; i < count; ++i) MoveHousingLabor(t, b, s);
}

// orig: FUN_0044ca34 (InitBuildingPool)  memset de los 1200 Building y encadenado prev/next de la lista
// libre (ResetVariables).
void InitBuildingPool() {
    std::memset(gs.buildings, 0, sizeof(gs.buildings));
    for (int i = 0; i < kMaxBuildings; ++i) {
        gs.buildings[i].prev = (i == kMaxBuildings - 1) ? Ptr32<Building>{} : ref(&gs.buildings[i + 1]);
        gs.buildings[i].next = (i == 0) ? Ptr32<Building>{} : ref(&gs.buildings[i - 1]);
    }
    gg.freeBuildingsTail = ref(&gs.buildings[0]);
    gg.activeBuildingsTail = Ptr32<Building>{};
}

// orig: FUN_0044cabc (RebuildBuildingLists)  Reconstruye las listas activa (type != 0) y libre.
void RebuildBuildingLists() {
    gg.activeBuildingsTail = Ptr32<Building>{};
    for (int i = 0; i < kMaxBuildings; ++i) {
        Building& b = gs.buildings[i];
        if (b.type == 0) continue;
        if (!gg.activeBuildingsTail) {
            b.prev = Ptr32<Building>{};
            b.next = Ptr32<Building>{};
        } else {
            ptr(gg.activeBuildingsTail)->next = ref(&b);
            b.next = gg.activeBuildingsTail;   // el original escribe +0x116..0x119: es el "prev" lógico
            b.prev = Ptr32<Building>{};
        }
        gg.activeBuildingsTail = ref(&b);
    }
    gg.freeBuildingsTail = Ptr32<Building>{};
    for (int i = 0; i < kMaxBuildings; ++i) {
        Building& b = gs.buildings[i];
        if (b.type != 0) continue;
        if (!gg.freeBuildingsTail) {
            b.prev = Ptr32<Building>{};
            b.next = Ptr32<Building>{};
        } else {
            ptr(gg.freeBuildingsTail)->next = ref(&b);
            b.next = gg.freeBuildingsTail;
            b.prev = Ptr32<Building>{};
        }
        gg.freeBuildingsTail = ref(&b);
    }
}

// orig: FUN_0044cbec (AllocBuilding)  Saca la cabeza de la lista libre y la pone en la activa.
Building* AllocBuilding() {
    Building* b = ptr(gg.freeBuildingsTail);
    if (!b || !b->prev) return nullptr;
    gg.freeBuildingsTail = b->prev;
    ptr(gg.freeBuildingsTail)->next = Ptr32<Building>{};
    if (!gg.activeBuildingsTail) {
        b->prev = Ptr32<Building>{};
    } else {
        b->prev = gg.activeBuildingsTail;
        ptr(gg.activeBuildingsTail)->next = ref(b);
    }
    gg.activeBuildingsTail = ref(b);
    return b;
}

// orig: FUN_0044cc40 (FreeBuilding)  Saca el edificio de la lista activa, lo pone a cero y lo devuelve
// a la libre.
void FreeBuilding(Building* b) {
    Building* it = ptr(gg.activeBuildingsTail);
    while (it) {
        if (it == b) break;
        it = ptr(it->prev);
    }
    if (!it) return;
    if (b->next) ptr(b->next)->prev = b->prev;
    if (b->prev) ptr(b->prev)->next = b->next;
    if (ref(b).raw == gg.activeBuildingsTail.raw) gg.activeBuildingsTail = b->prev;
    std::memset(b, 0, sizeof(Building));
    b->prev = gg.freeBuildingsTail;
    b->next = Ptr32<Building>{};
    if (gg.freeBuildingsTail) ptr(gg.freeBuildingsTail)->next = ref(b);
    gg.freeBuildingsTail = ref(b);
}

// orig: FUN_0044cce4 (ClearSiteArea)  Limpia los bits altos de terrainFlags en el cuadrado size x size
// que empieza en (col,row) y anula el puntero del edificio de la casilla base.
void ClearSiteArea(Territory* t, int col, int row, int size) {
    for (int r = row; row - size < r; --r)
        for (int c = col; c < size + col; ++c)
            t->sites[r * 6 + c].terrainFlags &= sflag::TerrainMask;
    t->sites[col + row * 6].building = Ptr32<Building>{};
}

// orig: 0044cd50 (_DeleteBuilding)  Quita el edificio de la casilla (restaurando la plataforma marina
// si estaba sobre ella) y lo libera.
int _DeleteBuilding(Territory* t, int site) {
    Building* b = siteBldg(t, site);
    if (gg.netGame != 0 && !b) {
        hooks::debugMessage("Invalid building in _DeleteBuilding");
        return 0;
    }
    if (!b) return 0;
    int size = BT(b).size;
    int hub = FindBuildingByCategory(t, cat::SeaPlatform, 0);
    if (size == 5 || hub == -1 || (t->sites[site].terrainFlags & sflag::HiMask) != sflag::PlatformUsed) {
        ClearSiteArea(t, site % 6, site / 6, size);
    } else {
        // tabla de saltos 0x44ce2e: índice = hub - site + 2 -> restaura el bit 0x100 de la plataforma
        unsigned idx = unsigned(hub - site + 2);
        if (idx < 0x19) {
            static const uint8_t kCase[25] = {5,0,0,0,0,0,0,0,0,0,4,0,3,0,2,0,0,0,0,0,0,0,0,0,1};
            static const uint16_t kFlag[6] = {0, 0x3100, 0x1100, 0x5100, 0x4100, 0x2100};
            int c = kCase[idx];
            if (c != 0)
                t->sites[site].terrainFlags = uint16_t((t->sites[site].terrainFlags & sflag::TerrainMask) | kFlag[c]);
        }
        t->sites[site].building = Ptr32<Building>{};
    }
    FreeBuilding(b);
    return 1;
}

// orig: 0044cefc (_DemolishBuilding)  Devuelve la mitad de los materiales (o de lo pagado en obras),
// borra el edificio y rebalancea.  Un shrine demolido registra un "nuke".
void _DemolishBuilding(Player* p, Territory* t, int site) {
    Building* b = siteBldg(t, site);
    if (gg.netGame != 0 && !b) {
        hooks::debugMessage("Invalid building in _DemolishBuilding");
        return;
    }
    if (!b) return;
    if (b->category == cat::Shrine) {
        t->flags &= ~tflag::ShrinePlaced;
        if (gg.editorMode == 0 && CampaignGoal12Done() == 0) QueueNukeUse(p, t);
    }
    int32_t cost[13] = {};
    if ((b->flags & bflag::Built) == 0) {
        for (int k = 0; k < 11; ++k) cost[k] = b->cost[k];
    } else if (b->type == 0x25) {
        GetCityCenterCost(b, cost);
    } else {
        GetBuildingCost(p, b->type, t->terrain, cost);
    }
    if (gg.editorMode == 0) p->credits += int16_t(cost[0] >> 1);
    if (gg.editorMode == 0)
        for (int k = 1; k < 11; ++k) t->materials[k] += int16_t(cost[k] >> 1);
    _DeleteBuilding(t, site);
    BalanceLabor(t);
    if (ext.recomputeSiteRoads) ext.recomputeSiteRoads(&gs.territories[b->territory]);
}

// orig: FUN_0044d034 (CountBuildingsByCategory)
int CountBuildingsByCategory(Territory* t, int category) {
    int n = 0;
    for (int i = 0; i < kNumSites; ++i) {
        Building* b = siteBldg(t, i);
        if (b && category == b->category) n++;
    }
    return n;
}

// orig: FUN_0044d06c (CountFinishedByCategory)
int CountFinishedByCategory(Territory* t, int category) {
    int n = 0;
    for (int i = 0; i < kNumSites; ++i) {
        Building* b = siteBldg(t, i);
        if (b && category == b->category && b->turnsLeft == 0) n++;
    }
    return n;
}

// orig: FUN_0044d0ac (CountBuildingsByType)
int CountBuildingsByType(Territory* t, int type) {
    int n = 0;
    for (int i = 0; i < kNumSites; ++i) {
        Building* b = siteBldg(t, i);
        if (b && type == b->type) n++;
    }
    return n;
}

// orig: FUN_0044d0e4 (ReplaceBuildingForType)  Si no hay casilla para `type`, demuele un edificio del
// mismo tamaño (preferiblemente de la misma categoría) que no sea vivienda/shrine/City Center.
int ReplaceBuildingForType(Territory* t, int type) {
    if (FindConstructionSite(t, type) != -1) return 1;
    Building* victim = nullptr;
    for (int i = 0; i < kNumSites; ++i) {
        Building* b = siteBldg(t, i);
        Building* nv = victim;
        if (b && BT(b).size == BT(type).size && b->category != cat::Housing && b->type != type &&
            b->category != cat::Shrine && b->category != cat::CityCenter) {
            nv = b;
            if (victim != nullptr) {
                nv = victim;
                if (b->category == BT(type).category) nv = b;
            }
        }
        victim = nv;
    }
    if (!victim) return 0;
    NetDemolishBuilding(t, victim->site, 0);
    return 1;
}

// orig: FUN_0044d1a4 (FindBuildingByCategory)  Índice de casilla desde `from` con edificio de esa categoría.
int FindBuildingByCategory(Territory* t, int category, int from) {
    for (; from <= 0x23; ++from) {
        Building* b = siteBldg(t, from);
        if (b && category == b->category) return from;
    }
    return -1;
}

// orig: FUN_0044d1e4 (FindFinishedByCategory)  Igual pero terminado (turnsLeft == 0).
int FindFinishedByCategory(Territory* t, int category, int from) {
    for (; from <= 0x23; ++from) {
        Building* b = siteBldg(t, from);
        if (b && category == b->category && b->turnsLeft == 0) return from;
    }
    return -1;
}

// orig: FUN_0044d230 (FindActiveByCategory)  Igual pero terminado y activo.
int FindActiveByCategory(Territory* t, int category, int from) {
    for (; from <= 0x23; ++from) {
        Building* b = siteBldg(t, from);
        if (b && category == b->category && b->turnsLeft == 0 && (b->flags & bflag::Active) != 0) return from;
    }
    return -1;
}

namespace {
// Recorre los territorios adyacentes (máscara de 112 bits) llamando f(Territory*) hasta que devuelva true.
template <class F>
bool forAdjacent(Territory* t, F f) {
    for (int w = 0; w < 7; ++w) {
        uint16_t bits = t->adjacency[w];
        for (int k = 0; bits != 0 && k < 16; ++k) {
            if (bits & 1) {
                Territory* a = &gs.territories[w * 16 + k];
                if (f(a)) return true;
            }
            bits = uint16_t(int16_t(bits) >> 1);
        }
    }
    return false;
}
} // namespace

// orig: FUN_0044d284 (HasAdjacentLand)  Territorio marítimo con algún vecino terrestre válido.
int HasAdjacentLand(Territory* t) {
    if (t->terrain != 0) return 0;
    return forAdjacent(t, [](Territory* a) {
        return a->numTiles != 0 && a->terrain != 0 && (a->flags & tflag::NoTiles) == 0;
    }) ? 1 : 0;
}

// orig: FUN_0044d2f8 (HasAdjacentTerrain)  Algún vecino válido con ese terreno (0 = mar).
int HasAdjacentTerrain(Territory* t, int terrain) {
    return forAdjacent(t, [terrain](Territory* a) {
        return a->numTiles != 0 && a->terrain == terrain && (a->flags & tflag::NoTiles) == 0;
    }) ? 1 : 0;
}

// orig: FUN_0044d36c (AreaHasResourceSite)  Alguna casilla del área del edificio tiene `value` != 0.
int AreaHasResourceSite(Territory* t, int type, int site) {
    int size = BT(type).size;
    for (int r = site / 6; site / 6 - size < r; --r)
        for (int c = site % 6; c < size + site % 6; ++c)
            if (t->sites[r * 6 + c].value != 0) return 1;
    return 0;
}

// orig: FUN_0044d3f4 (CanBuildAtSea)  Tabla de saltos 0x44d40f para los tipos 0x13..0x2c.
int CanBuildAtSea(int type) {
    static const uint8_t kTable[26] = {1,1,0,0,0,1,1,0,0,1,0,1,0,0,1,1,0,0,0,0,1,1,1,1,1,1};
    unsigned i = unsigned(type - 0x13);
    if (i < 0x1a) return kTable[i];
    return 0;
}

// orig: FUN_0044d440 (IsSeaOnlyBuilding)  Tipos 0x26..0x2c y 0x2f.
int IsSeaOnlyBuilding(int type) {
    return (unsigned(type - 0x26) < 7 || type == 0x2f) ? 1 : 0;
}

// orig: 0044d464 (FindConstructionSite)  Casilla para un edificio (-1 si no cabe / no procede).
int FindConstructionSite(Territory* t, int type) {
    int category = BT(type).category;
    if (t->terrain == 0) {
        if (type == 0x2f) {
            if (FindBuildingByCategory(t, cat::Shrine, 0) != -1) return -1;
            int r = RandRangeTagged(4, "FindConstructionSite");
            if (r == 0) return 0;
            if (r == 1) return 5;
            if (r == 2) return 0x1e;
            if (r == 3) return 0x23;
        } else {
            if (FindBuildingByCategory(t, cat::SeaPlatform, 0) == -1) {
                if (type != 0x2f && type != 0x26) return -1;
            } else if (CanBuildAtSea(type) == 0 && type != 0x2f) {
                return -1;
            }
        }
    } else if (IsSeaOnlyBuilding(type) != 0) {
        return -1;
    }
    int result = -1;
    if (category == cat::Port && HasAdjacentTerrain(t, 0) == 0) return -1;
    if (category == cat::CityCenter && FindBuildingByCategory(t, cat::CityCenter, 0) != -1) return -1;
    for (int k = 0; k < kNumSites; ++k) {
        int site = kSiteOrder[k];
        if (CheckConstructionSite(t, type, site) == 0) {
            if (AreaHasResourceSite(t, type, site) == 0) return site;
            result = site;
        }
    }
    return result;
}

// orig: FUN_0044d5a8 (FindTerritoryWithSite)  Primer territorio poblado del jugador con casilla libre.
Territory* FindTerritoryWithSite(int player, int type) {
    for (int i = 1; i <= gs.world.numTerritories; ++i) {
        Territory* t = &gs.territories[i];
        if (player == t->owner && t->population != 0 && FindConstructionSite(t, type) != -1) return t;
    }
    return nullptr;
}

// orig: FUN_0044d600 (CheckConstructionSite)  0 = se puede construir; si no, código de motivo:
// 1 fuera del tablero, 2 ocupada, 3 terreno 0xff, 4 ya hay City Center, 5 puerto sin mar adyacente,
// 6 terreno 5, 7 casilla de plataforma con edificio no marino, 8 ya hay plataforma, 9 edificio sólo
// marino en tierra, 10 ya hay shrine.
int CheckConstructionSite(Territory* t, int type, int site) {
    int size = BT(type).size;
    int row = site / 6;
    int category = BT(type).category;
    if (t->terrain != 0 && IsSeaOnlyBuilding(type) != 0) return 9;
    if (category == cat::CityCenter && FindBuildingByCategory(t, cat::CityCenter, 0) != -1) return 4;
    if (category == cat::SeaPlatform && FindBuildingByCategory(t, cat::SeaPlatform, 0) != -1) return 8;
    if (category == cat::Shrine && FindBuildingByCategory(t, cat::Shrine, 0) != -1) return 10;
    if (category == cat::Port && HasAdjacentTerrain(t, 0) == 0) return 5;
    for (int r = row; row - size < r; --r) {
        for (int c = site % 6; c < site % 6 + size; ++c) {
            if (c < 0 || r < 0 || c > 5 || r > 5) return 1;
            BuildingSite& s = t->sites[r * 6 + c];
            if ((s.terrainFlags & sflag::HiMask) == sflag::PlatformFree)
                return CanBuildAtSea(type) != 0 ? 0 : 7;
            if (s.building || (s.terrainFlags >> 8) != 0) return 2;
            unsigned terr = s.terrainFlags & sflag::TerrainMask;
            if (terr == 0xff && type != 0x26 && type != 0x2f) return 3;
            if (terr == 5) return 6;
        }
    }
    return 0;
}

// orig: FUN_0044d7b4 (PlaceBuildingOnSite)  Enlaza el edificio a la casilla y marca los bits altos del
// área (tamaño 1: 0x3000/0x3200; tamaño 2: 0x1000..0x4000; plataforma: casillas satélite 0xX100/0x6000).
void PlaceBuildingOnSite(Territory* t, Building* b, int site, int size) {
    t->sites[site].building = ref(b);
    auto flagsAt = [t](int idx) -> uint16_t& { return t->sites[idx].terrainFlags; };
    if (size == 5) {
        flagsAt(site - 22) |= 0x3100;
        flagsAt(site - 12) |= 0x1100;
        flagsAt(site - 10) |= 0x5100;
        flagsAt(site - 8) |= 0x4100;
        flagsAt(site + 2) |= 0x2100;
        flagsAt(site - 24) |= 0x6000;
    } else if (size == 2) {
        flagsAt(site) |= 0x1000;
        flagsAt(site + 1) |= 0x2000;
        flagsAt(site - 6) |= 0x3000;
        flagsAt(site - 5) |= 0x4000;
        t->sites[site + 1].building = Ptr32<Building>{};   // byte +0x184 (puntero de la casilla +1, byte bajo)
        reinterpret_cast<uint8_t*>(&t->sites[site - 5])[0x14] &= 0xfb;   // +0x4c
        reinterpret_cast<uint8_t*>(&t->sites[site])[0x10] &= 0xfd;       // +0x150 (bits de carretera)
    } else {
        uint16_t f = flagsAt(site);
        if ((f & sflag::HiMask) == sflag::PlatformFree) flagsAt(site) = uint16_t((f & sflag::TerrainMask) | 0x3200);
        else flagsAt(site) |= 0x3000;
    }
}

// orig: FUN_0044d890 (InitBuilding)  Rellena un Building recién asignado.
void InitBuilding(Territory* t, Building* b, int type, int site, int16_t work) {
    b->type = uint8_t(type);
    b->category = BT(type).category;
    b->flags = 4;
    b->site = int8_t(site);
    b->territory = int16_t(t->index);
    b->unk_0a = 0;
    if (gg.editorMode == 0) {
        b->turnsLeft = work;
    } else {
        b->turnsLeft = 0;
        if (BT(b->type).category == cat::Shrine) t->flags |= tflag::ShrinePlaced;
    }
    if (type == 0x25 && t->owner != -1) b->hubLevel = int16_t(int8_t(CountCityCenters(t->owner) - 1));
    else b->hubLevel = 0;
    b->unk_10 = 0;
    b->unk_12 = 0;
    b->unk_16 = 0;
    std::memset(b->labor, 0, sizeof(b->labor));
    std::memset(b->task, 0, sizeof(b->task));
    std::memset(b->unk_31, 0, sizeof(b->unk_31));
    std::memset(b->unk_36, 0, sizeof(b->unk_36));
    std::memset(b->cost, 0, sizeof(b->cost));
    std::memset(b->taskData, 0, sizeof(b->taskData));
    if (t->owner != -1) GetBuildingTasks(&gs.players[t->owner], b);
    if (type == 1 || type == 2 || type == 3 || type == 0x27 || type == 0x25 || type == 0x17) {
        if (gg.editorMode == 0 || t->owner != -1) b->race = uint8_t(gs.players[t->owner].race);
        else b->race = uint8_t(gs.players[gg.localPlayer].race);
    } else {
        b->race = 0;
    }
}

// orig: FUN_0044da3c (FindPortTargetTerritory)  Territorio marítimo vecino donde botar barcos:
// preferencia propio+con hueco (retorno inmediato), luego por puntuación (1 primero, 2 sin dueño,
// 4 propio, 8 con hueco).
int FindPortTargetTerritory(Territory* t) {
    Territory* best = nullptr;
    uint8_t bestScore = 0;
    for (int w = 0; w < 7; ++w) {
        uint16_t bits = t->adjacency[w];
        for (int k = 0; bits != 0 && k < 16; ++k) {
            if (bits & 1) {
                int idx = w * 16 + k;
                Territory* a = &gs.territories[idx];
                if (a->terrain == 0 && (a->flags & tflag::NoTiles) == 0 && a->numTiles != 0) {
                    if (t->owner == a->owner && CanCreateUnit(a, 0xc) != 0) return a->index;
                    uint8_t score = uint8_t(best == nullptr);
                    if (a->owner == -1) score |= 2;
                    if (a->owner == t->owner) score |= 4;
                    if (CanCreateUnit(a, 0xc) != 0) score |= 8;
                    if (bestScore < score) { best = a; bestScore = score; }
                }
            }
            bits = uint16_t(int16_t(bits) >> 1);
        }
    }
    return best ? best->index : 0;
}

// orig: FUN_0044db50 (StartConstruction)  Crea una obra en la casilla, paga los materiales, asigna
// colonos (jugadores humanos) y fija el destino de puerto.
Building* StartConstruction(Territory* t, int type, int site, uint16_t id) {
    Player* p = ownerOf(*t);
    if (CheckConstructionSite(t, type, site) != 0) return nullptr;
    Building* b = AllocBuilding();
    if (!b) { hooks::debugMessage("No Free Buildings!"); return nullptr; }
    int32_t cost[13] = {};
    GetBuildingCost(p, type, t->terrain, cost);
    InitBuilding(t, b, type, site, int16_t(cost[0]));
    int r = PayCosts(p, t, cost, b->cost);
    if (r == 0) {
        b->id = id;
        b->flags |= bflag::Built;
        LogEvent(t->owner, 0x40, BT(b->type).name, t);
        PlaceBuildingOnSite(t, b, site, BT(type).size);
        if (p->type < 3) AssignLaborFromHousing(t, -1, b);
        if (ext.recomputeSiteRoads) ext.recomputeSiteRoads(t);
        if (b->category == cat::Port) t->portTarget = uint16_t(FindPortTargetTerritory(t));
        return b;
    }
    FreeBuilding(b);
    if (t->owner == gg.localPlayer && ext.notEnoughStuff) ext.notEnoughStuff(BT(type).name, unsigned(r), cost);
    return nullptr;
}

// orig: FUN_0044dcc8 (StartConstructionAuto)  FindConstructionSite + NetStartConstruction.
int StartConstructionAuto(Territory* t, int type) {
    int site = FindConstructionSite(t, type);
    if (site == -1) return 0;
    return NetStartConstruction(t, type, site) != nullptr ? 1 : 0;
}

// orig: FUN_0044dcf4 (CreateBuilding)  Crea un edificio terminado (aterrizaje, campaña, editor);
// una Sea Platform crea además el SeaHab en la casilla site-10.
Building* CreateBuilding(Territory* t, int type, uint16_t id, uint16_t habId, int site) {
    if (site == -1) site = FindConstructionSite(t, type);
    if (site == -1) return nullptr;
    Building* b = AllocBuilding();
    if (!b) return nullptr;
    InitBuilding(t, b, type, site, 0);
    b->id = id;
    b->flags |= bflag::Built;
    PlaceBuildingOnSite(t, b, site, BT(type).size);
    AssignLaborFromHousing(t, -1, b);
    if (ext.recomputeSiteRoads) ext.recomputeSiteRoads(t);
    if (b->type == 0x26) {
        Building* hab = AllocBuilding();
        if (hab) {
            InitBuilding(t, hab, 0x27, int16_t(site - 10), 0);
            hab->id = habId;
            hab->flags |= bflag::Built;
            PlaceBuildingOnSite(t, hab, int16_t(site - 10), BT(0x27).size);
            AssignLaborFromHousing(t, -1, hab);
            if (ext.recomputeSiteRoads) ext.recomputeSiteRoads(t);
        }
    }
    return b;
}

// orig: FUN_0044ddf4 (GetUnitCost)  out[0] = trabajo, out[1..11] = materiales, out[12] = tecnología.
void GetUnitCost(Player* /*p*/, int unitType, int32_t out[13]) {
    out[0] = kUnitTypes[unitType].work;
    for (int k = 0; k < 11; ++k) out[1 + k] = kUnitCosts[unitType][k];
    out[12] = kUnitTypes[unitType].tech;
}

// orig: FUN_0044de48 (CountCityCenters)  City Centers del jugador en todo el mapa.
int CountCityCenters(int player) {
    int n = 0;
    for (int i = 0; i < kMaxBuildings; ++i) {
        const Building& b = gs.buildings[i];
        if (b.type == 0x25 && player == gs.territories[b.territory].owner) n++;
    }
    return n;
}

// orig: FUN_0044de9c (GetBuildingCost)  out[0] = trabajo, out[1..11] = materiales, out[12] = tecnología.
// El City Center cuesta x nº de City Centers ya construidos (o 1/4 de créditos si es el primero).
void GetBuildingCost(Player* p, int type, int /*terrain*/, int32_t out[13]) {
    out[0] = BT(type).work;
    for (int k = 0; k < 11; ++k) out[1 + k] = kBuildingCosts[type][k];
    if (type == 0x25) {
        int n = CountCityCenters(p->index);
        if (n == 0) out[1] = out[1] >> 2;
        else for (int k = 1; k < 12; ++k) out[k] = n * out[k];
    }
    out[12] = BT(type).tech;
}

// orig: FUN_0044df30 (GetCityCenterCost)  Coste del City Center según su hubLevel (tabla DAT_004fad78).
void GetCityCenterCost(Building* b, int32_t out[13]) {
    out[0] = kCityCenterWork;
    for (int k = 0; k < 11; ++k) out[1 + k] = kCityCenterCost[k];
    out[12] = kCityCenterTech;
    int16_t lvl = b->hubLevel;
    if (lvl < 1) out[1] = out[1] >> 2;
    else for (int k = 1; k < 12; ++k) out[k] = lvl * out[k];
}

// orig: FUN_0044df94 (QueueUnit)  Paga y añade la unidad a la cola de su clase.  Devuelve la máscara de
// materiales que faltan (0 = ok; -1 = sin cola aplicable... el original devuelve 0 si no hay cola).
int QueueUnit(Territory* t, Player* p, int unitType) {
    int qcat = 0;
    switch (kUnitTypes[unitType].unitClass) {
    case 1: case 2: qcat = 1; break;
    case 3: case 0xd: qcat = 3; break;
    case 4: case 5: case 0xc: case 0xe: case 0xf: case 0x10: case 0x11: case 0x12: case 0x13: qcat = 2; break;
    case 6: case 7: case 8: case 0xb: qcat = 5; break;
    case 9: qcat = 4; break;
    default: break;
    }
    uint8_t rec[0x30];
    std::memset(rec, 0, sizeof rec);
    QueueHead* q = GetQueue(t, qcat);
    int r = -1;
    if (!q) {
        r = 0;
    } else if ((unitType != 0x19 && unitType != 0x1f) || t->population > 100) {
        int32_t cost[13] = {};
        GetUnitCost(p, unitType, cost);
        int32_t* paid = reinterpret_cast<int32_t*>(rec + 4);
        r = PayCosts(p, t, cost, paid);
        if (r == 0) {
            rec[0] = uint8_t(unitType);
            uint16_t cnt = uint16_t(cost[0]);
            std::memcpy(rec + 2, &cnt, 2);
            QueueAppend(q, rec);
            if (unitType == 0x19 || unitType == 0x1f) {
                t->population = int16_t(t->population - 100);
                BalanceLabor(t);
            }
        }
    }
    return r;
}

// orig: FUN_0044e0a8 (DequeueUnit)  Quita la entrada `index` de la cola devolviendo créditos y materiales.
int DequeueUnit(Territory* t, Player* p, int queueCat, int index) {
    QueueHead* q = GetQueue(t, queueCat);
    if (!q) return 0;
    int ok = QueueFirst(q);
    while (ok != 0) {
        if (index == 0) {
            uint8_t ut = QueueCurUnitType(q);
            int32_t data[11] = {};
            QueueCurData(q, data);
            int32_t cost[13] = {};
            GetUnitCost(p, ut, cost);
            p->credits += data[0];
            for (int k = 1; k < 11; ++k) t->materials[k] += int16_t(data[k]);
            if (ut == 0x19 || ut == 0x1f) {
                t->population = int16_t(t->population + 100);
                BalanceLabor(t);
            }
            UnitList_Delete(q);
            return 1;
        }
        ok = QueueNext(q);
        index--;
    }
    return 0;
}

// orig: FUN_0047597c (NetStartConstruction)  Local: NextGlobalId + StartConstruction.
Building* NetStartConstruction(Territory* t, int type, int site) {
    if (gg.netGame == 0 || !ext.netStartConstruction) {
        uint16_t id = NextGlobalId();
        return StartConstruction(t, type, site, id);
    }
    return ext.netStartConstruction(t, type, site);
}

// orig: FUN_00475a60 (NetDemolishBuilding)  Local: _DemolishBuilding.
void NetDemolishBuilding(Territory* t, int site, int flag) {
    if (gg.netGame == 0 || !ext.netDemolish) {
        _DemolishBuilding(&gs.players[t->owner], t, site);
        return;
    }
    ext.netDemolish(t, site, flag);
}

// orig: FUN_00475ce8 (NetReassignLabor)  Local: TransferLabor.
void NetReassignLabor(Territory* t, Building* from, int fromSlot, Building* to, int toSlot) {
    if (gg.netGame == 0 || !ext.netReassignLabor) {
        TransferLabor(t, from, fromSlot, to, toSlot);
        return;
    }
    ext.netReassignLabor(t, from, fromSlot, to, toSlot);
}

// orig: FUN_00475f80 (NetQueueUnit)  Local (y maestro de red): QueueUnit.
unsigned NetQueueUnit(Territory* t, Player* p, int unitType) {
    return unsigned(QueueUnit(t, p, unitType));
}

// orig: FUN_00476324 (NetSetPortTarget)  Local: SetPortTarget.
void NetSetPortTarget(Territory* t, int16_t target) { SetPortTarget(t, target); }

// ----------------------------------------------------------------------------------------
// Colony Assistant (asignación automática de trabajo) 0x4483d0-0x448d94
// ----------------------------------------------------------------------------------------

// orig: FUN_004483d0 (BuildTaskSummary)  Tabla por tarea (Build Units -> 0x16 + cola) de edificios,
// colonos, huecos libres (activos/inactivos) y producción.
void BuildTaskSummary(Territory* t) {
    std::memset(gTaskSummary, 0, sizeof gTaskSummary);
    Player* p = ownerOf(*t);
    for (int i = 0; i < kNumSites; ++i) {
        Building* b = siteBldg(t, i);
        if (!b) continue;
        int32_t out[5] = {};
        BuildingTaskOutputs(p, t, b->site, out, 0);
        int freeL = MaxLabor(b) - TotalLabor(b);
        for (int s = 0; s < 5; ++s) {
            int tk = b->task[s];
            if (tk == task::BuildUnits) tk = BT(b).queueCat + 0x16;
            if (tk == 0) continue;
            TaskSummary& ts = gTaskSummary[tk];
            ts.lastBuilding = ref(b);
            ts.count++;
            ts.labor += b->labor[s];
            if ((b->flags & bflag::Active) == 0) ts.freeInactive += freeL;
            else ts.freeActive += freeL;
            ts.output += out[s];
        }
    }
}

// orig: FUN_004484fc (TaskUrgency)  Construcción/mejora: 10000 - trabajo restante (menor = más urgente);
// otras: producción con 1 colono.
int TaskUrgency(int taskId, Territory* t, Building* b) {
    int slot = FindTaskSlot(b, taskId);
    Player* p = ownerOf(*t);
    int v;
    if (taskId == task::Construction) {
        v = TaskOutput(p, t, b->site, slot, slot >= 0 ? b->labor[slot] : 0);
        v = b->turnsLeft - v;
        if (v > 0) v = 10000 - v;
    } else if (taskId == task::Upgrade) {
        v = UpgradeCost(b) - upgradeProgress(*b);
        v -= TaskOutput(p, t, b->site, slot, slot >= 0 ? b->labor[slot] : 0);
        if (v > 0) v = 10000 - v;
    } else {
        v = TaskOutput(p, t, b->site, slot, 1);
    }
    return v;
}

namespace {
inline int normTask(int tk) { return tk > 0x16 ? task::BuildUnits : tk; }
}

// orig: FUN_004485e8 (FindLaborSource)  Edificio con colonos en la tarea `fromTask` de menor urgencia
// (con las restricciones de cola y de disponibilidad de `toTask`).
Building* FindLaborSource(Territory* t, int fromTask, int toTask) {
    int best = 10000;
    Building* bestB = nullptr;
    int fromN = normTask(fromTask), toN = normTask(toTask);
    for (int i = 0; i < kNumSites; ++i) {
        Building* b = siteBldg(t, i);
        if (!b) continue;
        if (!(fromTask < 0x16 || BT(b).queueCat == fromTask - 0x16)) continue;
        if (!(gTaskSummary[toTask].freeActive != 0 || toTask < 0x16 || BT(b).queueCat == toTask - 0x16)) continue;
        int slot = FindTaskSlot(b, fromN);
        if (slot == -1) continue;
        if (gTaskSummary[toTask].freeActive == 0 && FindTaskSlot(b, toN) == -1) continue;
        int u = TaskUrgency(fromN, t, b);
        if (b->labor[slot] > 0 && u < best) { bestB = b; best = u; }
    }
    return bestB;
}

// orig: FUN_00448700 (FindLaborTarget)  Edificio activo con hueco (o `exclude`) y la tarea `toTask` de
// mayor urgencia.
Building* FindLaborTarget(Territory* t, Building* exclude, int toTask) {
    int best = 0;
    Building* bestB = nullptr;
    int toN = normTask(toTask);
    for (int i = 0; i < kNumSites; ++i) {
        Building* b = siteBldg(t, i);
        if (!b) continue;
        if (!(toTask < 0x16 || BT(b).queueCat == toTask - 0x16)) continue;
        if ((b->flags & bflag::Active) == 0) continue;
        if (TotalLabor(b) < MaxLabor(b) || b == exclude) {
            if (FindTaskSlot(b, toN) != -1) {
                int u = TaskUrgency(toN, t, b);
                if (best < u) { bestB = b; best = u; }
            }
        }
    }
    return bestB;
}

// orig: FUN_004487b8 (AssistantMoveOne)  Mueve un colono de la tarea fromTask a toTask.
int AssistantMoveOne(Territory* t, int fromTask, int toTask) {
    int ok = 0;
    Building* src = FindLaborSource(t, fromTask, toTask);
    Building* dst = FindLaborTarget(t, src, toTask);
    if (src && dst) {
        int fs = FindTaskSlot(src, normTask(fromTask));
        int ts = FindTaskSlot(dst, normTask(toTask));
        NetReassignLabor(t, src, fs, dst, ts);
        ok = 1;
    }
    BuildTaskSummary(t);
    return ok;
}

// orig: FUN_00448844 (AssistantMoveN)
int AssistantMoveN(Territory* t, int fromTask, int toTask, int n) {
    int moved = 0;
    for (; moved < n; ++moved)
        if (AssistantMoveOne(t, fromTask, toTask) == 0) return moved;
    return moved;
}

// orig: FUN_00448878 (AssistantHasSource)
bool AssistantHasSource(Territory* t, int fromTask, int toTask) {
    return FindLaborSource(t, fromTask, toTask) != nullptr;
}

// orig: FUN_0044889c (AssistantFreeTask)  Mueve todos los colonos de una tarea a sí misma (recoloca).
void AssistantFreeTask(Territory* t, int taskId) {
    BuildTaskSummary(t);
    AssistantMoveN(t, taskId, taskId, gTaskSummary[taskId].labor);
}

// orig: FUN_004488c8 (QueuedUnitCount)  Suma de `count` (trabajo pendiente) de la cola.
int QueuedUnitCount(Territory* t, int queueCat) {
    int n = 0;
    QueueHead* q = GetQueue(t, queueCat);
    if (!q) return 0;
    for (int ok = QueueFirst(q); ok != 0; ok = QueueNext(q)) n += QueueCurCount(q);
    return n;
}

// orig: FUN_0044890c (MilitiaNeedsTraining)  Alguna milicia (misión Train) propia aquí o en territorios
// terrestres propios adyacentes con experiencia + bonus < 100.
int MilitiaNeedsTraining(Territory* t, int bonus) {
    for (Army* a = ptr(t->armies); a; a = ptr(a->next))
        if (a->unk_25 == mission::Train && a->experience + bonus < 100) return 1;
    return forAdjacent(t, [t, bonus](Territory* n) {
        if (n->terrain != 0 || n->owner != t->owner) return false;
        for (Army* a = ptr(n->armies); a; a = ptr(a->next))
            if (a->unk_25 == mission::Train && a->experience + bonus < 100) return true;
        return false;
    }) ? 1 : 0;
}

// orig: FUN_004489e0 (AssistantTaskWanted)  ¿Conviene poner más colonos en la tarea? (pass 0: sólo
// cultura/comida/energía deficitarias; pass 1/2: resto de reglas).
int AssistantTaskWanted(Territory* t, int taskId, int pass) {
    if (gTaskSummary[taskId].freeActive == 0) return 0;
    Player* lp = &gs.players[gg.localPlayer];
    int want = 0;
    if (pass == 0) {
        if (taskId == task::Culture) {
            if (ComputeMorale(t) < 100 && gMorale.culture < 0x19 && raceStat(27, lp->race) != 0) want = 1;
        } else if (taskId == task::Food) {
            if (SumTaskOutput(t, task::Food, 0) < TerritoryFoodNeed(t)) want = 1;
        } else if (taskId == task::Energy) {
            if (SumTaskOutput(t, task::Energy, 0) < TerritoryEnergyUse(t)) want = 1;
        }
        return want;
    }
    switch (taskId) {
    case task::Construction:
        for (int i = 0; i < kNumSites; ++i) {
            Building* b = siteBldg(t, i);
            if (b && b->turnsLeft != 0) {
                int slot = FindTaskSlot(b, task::Construction);
                int o = TaskOutput(lp, t, b->site, slot, slot >= 0 ? b->labor[slot] : 0);
                if (o < b->turnsLeft) want = 1;
            }
        }
        break;
    case task::Research: {
        int tech = lp->currentResearch;
        int32_t stats[30] = {};
        ComputePlayerStats(stats, gg.localPlayer);
        int cost = gs.techs[tech].cost;
        if (int(gs.techs[tech].progress[gg.localPlayer]) + stats[4] < cost) want = 1;
        break;
    }
    case task::Culture:
        if (ComputeMorale(t) < 100 && gMorale.culture < 0x19 && raceStat(27, lp->race) != 0) want = 1;
        break;
    case task::Clone:
        if (SumTaskOutput(t, task::Clone, 0) + t->population < TerritoryMaxPopulation(t)) want = 1;
        break;
    case task::TrainUnits:
        want = MilitiaNeedsTraining(t, SumTaskOutput(t, task::TrainUnits, 0));
        break;
    case task::Upgrade:
        for (int i = 0; i < kNumSites; ++i) {
            Building* b = siteBldg(t, i);
            if (b && CanUpgradeBuilding(b) != 0) {
                int slot = FindTaskSlot(b, task::Upgrade);
                int o = TaskOutput(lp, t, b->site, slot, slot >= 0 ? b->labor[slot] : 0);
                if (upgradeProgress(*b) + o < UpgradeCost(b)) want = 1;
            }
        }
        break;
    case 0x17: case 0x18: case 0x19: case 0x1a: case 0x1b:
        if (TotalUnitLabor(t, taskId - 0x16) < QueuedUnitCount(t, taskId - 0x16)) want = 1;
        break;
    default:
        if (pass > 1 || (taskId != task::Food && taskId != task::Energy)) want = 1;
        break;
    }
    return want;
}

// orig: FUN_00448d1c (AssistantPass)  Mientras haya movimientos, saca colonos de House Populace hacia
// las tareas deseadas en orden de prioridad.
void AssistantPass(Territory* t, int pass) {
    bool again = true;
    int left = gAssistantMaxMoves;
    while (again && left != 0) {
        again = false;
        for (int i = 0; i < 23; ++i) {
            int tk = kAssistantPriority[i];
            if (AssistantTaskWanted(t, tk, pass) != 0 && left != 0) {
                again = true;
                AssistantMoveOne(t, task::HousePopulace, tk);
                left--;
            }
        }
    }
}

// orig: FUN_00448d94 (RunColonyAssistant)  Devuelve todos los colonos a las viviendas y ejecuta las
// tres pasadas.
void RunColonyAssistant(Territory* t) {
    BuildTaskSummary(t);
    int labor[28];
    for (int i = 0; i < 28; ++i) {
        labor[i] = gTaskSummary[i].labor;
        if (labor[i] != 0) AssistantMoveN(t, i, task::HousePopulace, labor[i]);
    }
    AssistantPass(t, 0);
    AssistantPass(t, 1);
    AssistantPass(t, 2);
}

} // namespace dl2::econ
