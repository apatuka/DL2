// saveload.cpp - SaveGame / LoadGame / LoadMapFile y los 16 pares escritor/lector (docs/SAVEFORMAT.md).
#include "game/saveload.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

#include "game/campaign_flow.h"
#include "game/economy.h"
#include "game/gameflow.h"
#include "game/hooks.h"
#include "game/newgame.h"
#include "game/rtl_compat.h"

namespace dl2 {

// ----------------------------------------------------------------------------------------
// Constantes y tablas
// ----------------------------------------------------------------------------------------
const char kSaveHeaderText[] =
    "Deadlock 2  (c)1997 Accolade Inc.  All Rights Reserved.\nPre-release version XXXXXXXXXXX";   // DAT_004d1ea0
const char* const kOldHeaderTexts[4] = {                                                            // DAT_004d1d40..
    "Deadlock 2  (c)1997 Accolade Inc.  All Rights Reserved.\nPre-release version S (7/21/97)",
    "Deadlock 2  (c)1997 Accolade Inc.  All Rights Reserved.\nPre-release version T (7/31/97)",
    "Deadlock 2  (c)1997 Accolade Inc.  All Rights Reserved.\nPre-release version U (8/04/97)",
    "Deadlock 2  (c)1997 Accolade Inc.  All Rights Reserved.\nPre-release version V (9/05/97)",
};
static_assert(sizeof(kSaveHeaderText) == 88);

// Tabla de eventos DAT_004fc90c (paso 0x12): {u16 prioridad (+0), u16 id (+6)} para AddEventLogEntry /
// EventTypeToTableIndex; 0x9d entradas (la última es relleno del EXE).
struct EventTableRow { uint16_t prio, id; };
static const EventTableRow kEventTable[0x9d] = {
    {0,0},{20,1},{20,2},{20,3},{29,4},{28,5},{30,6},{30,7},{30,8},{30,9},{30,10},{30,11},{30,12},{30,13},{30,14},{30,15},
    {30,16},{30,17},{30,18},{30,19},{30,20},{30,21},{30,22},{30,23},{30,24},{30,25},{31,26},{31,27},{30,28},{30,29},{30,30},{30,31},
    {30,32},{111,34},{109,35},{110,36},{110,37},{110,38},{110,39},{110,40},{110,41},{110,42},{110,43},{110,44},{110,45},{110,46},{30,47},{30,48},
    {35,49},{20,50},{20,51},{20,52},{20,53},{20,54},{20,55},{20,56},{20,57},{70,58},{10,59},{90,60},{20,61},{10,62},{10,63},{20,64},
    {100,65},{100,66},{100,67},{20,68},{15,69},{15,70},{15,71},{15,72},{15,73},{17,74},{10,75},{70,76},{70,77},{70,78},{60,79},{65,80},
    {65,81},{60,82},{40,83},{40,84},{40,85},{50,86},{50,87},{40,88},{40,89},{40,90},{10,91},{40,92},{40,93},{39,94},{39,95},{39,96},
    {40,97},{40,98},{40,99},{40,100},{40,101},{40,102},{40,103},{40,104},{40,105},{40,106},{40,107},{50,108},{50,109},{50,110},{50,111},{50,112},
    {50,113},{50,114},{50,115},{50,116},{40,117},{40,118},{40,119},{40,120},{40,121},{40,122},{90,123},{90,124},{80,125},{80,126},{80,127},{80,128},
    {80,129},{80,130},{80,131},{80,132},{100,133},{69,134},{91,135},{81,136},{81,137},{81,138},{81,139},{81,140},{81,141},{81,142},{100,143},{69,145},
    {69,146},{70,147},{109,148},{30,149},{30,150},{30,151},{100,152},{50,153},{50,154},{50,155},{50,156},{0,144},{28494,25708},
};

namespace {
LoadError  g_lastError = LoadError::None;
SaveHeader g_lastHeader{};

// ---- pool de Player::localList ----
std::vector<LocalListNode> g_localNodes;
// ---- pool de nodos MinisterJob ----
std::vector<MinisterJob> g_mjobNodes;
std::vector<uint8_t>     g_mjobUsed;
// ---- pool lineal de textos del Event Log (DAT_0053b8dc, 0xc00 bytes; PTR_DAT_004b7b54 = puntero de asignación) ----
constexpr int kEventPoolSize = 0xc00;
constexpr int kEventPoolEnd  = 0xbff;     // &DAT_0053c4db - &DAT_0053b8dc
char g_eventPool[kEventPoolSize];
int  g_eventPoolPtr = 0;

// Copia con relleno de ceros (FUN_004a6b48 = strncpy de la RTL)
void strncpyZ(char* dst, const char* src, size_t n) {
    size_t i = 0;
    for (; i < n && src[i]; ++i) dst[i] = src[i];
    for (; i < n; ++i) dst[i] = 0;
}
} // namespace

// ----------------------------------------------------------------------------------------
// Reader / Writer
// ----------------------------------------------------------------------------------------
void SaveWriter::write(const void* p, size_t n) {
    const uint8_t* b = static_cast<const uint8_t*>(p);
    buf.insert(buf.end(), b, b + n);
}
bool SaveReader::read(void* dst, size_t len) {
    if (off + len > n) { off = n; return false; }   // ReadFile devuelve 0 (fin de fichero): carga corrupta
    std::memcpy(dst, p + off, len);
    off += len;
    return true;
}
bool SaveReader::skip(size_t len) {
    if (off + len > n) { off = n; return false; }
    off += len;
    return true;
}

LoadError lastLoadError() { return g_lastError; }
const SaveHeader& lastSaveHeader() { return g_lastHeader; }

// ----------------------------------------------------------------------------------------
// Pools
// ----------------------------------------------------------------------------------------
LocalListNode* ptr(Ptr32<LocalListNode> p) {
    return (p.raw && p.raw <= g_localNodes.size()) ? &g_localNodes[p.raw - 1] : nullptr;
}
Ptr32<LocalListNode> AllocLocalListNode(uint32_t value) {
    g_localNodes.push_back({value, {0}});
    return {uint32_t(g_localNodes.size())};
}
void ResetLocalLists() {
    g_localNodes.clear();
    for (int i = 0; i < 8 && i < kMaxPlayers; ++i) gs.players[i].localList.raw = 0;   // bucle "< 8" del original
}

MinisterJob* mjob(Ptr32<MinisterJob> p) {
    if (p.raw == 0) return nullptr;
    if (p.raw <= uint32_t(kMaxPlayers)) return &gs.ministerJobHeads[p.raw - 1];
    uint32_t i = p.raw - kMaxPlayers - 1;
    return i < g_mjobNodes.size() ? &g_mjobNodes[i] : nullptr;
}
Ptr32<MinisterJob> mjobRef(const MinisterJob* j) {
    if (!j) return {0};
    if (j >= gs.ministerJobHeads && j < gs.ministerJobHeads + kMaxPlayers)
        return {uint32_t(j - gs.ministerJobHeads) + 1u};
    return {uint32_t(j - g_mjobNodes.data()) + uint32_t(kMaxPlayers) + 1u};
}
MinisterJob* AllocMinisterJobNode() {
    for (size_t i = 0; i < g_mjobUsed.size(); ++i)
        if (!g_mjobUsed[i]) { g_mjobUsed[i] = 1; std::memset(&g_mjobNodes[i], 0, sizeof(MinisterJob)); return &g_mjobNodes[i]; }
    g_mjobNodes.emplace_back();
    std::memset(&g_mjobNodes.back(), 0, sizeof(MinisterJob));
    g_mjobUsed.push_back(1);
    return &g_mjobNodes.back();
}

// orig: FUN_00405798 (ResetMinisterJobs)  memset(0x1dc) + type = HEAD_JOB en las 7 cabeceras
void ResetMinisterJobs() {
    std::memset(gs.ministerJobHeads, 0, sizeof(gs.ministerJobHeads));
    for (int i = 0; i < kMaxPlayers; ++i) gs.ministerJobHeads[i].type = 1;
}

// orig: FUN_004057c4 (FreeMinisterJobs)  libera los nodos de cada lista con cabecera HEAD_JOB y reinicia
void FreeMinisterJobs() {
    if (flow::cb.freeMinisterJobs) { flow::cb.freeMinisterJobs(); return; }
    g_mjobNodes.clear();
    g_mjobUsed.clear();
    ResetMinisterJobs();
}

// ----------------------------------------------------------------------------------------
// Event log (FUN_004238c8, FUN_0042278c, FUN_004234d4, FUN_004233e0)
// ----------------------------------------------------------------------------------------
// orig: FUN_004238c8 (ClearEventLog)
void ClearEventLog() {
    std::memset(gs.events, 0, sizeof(gs.events));
    gs.options.eventCount = 0;
    g_eventPoolPtr = 0;
    std::memset(g_eventPool, 0, sizeof(g_eventPool));
}

// orig: FUN_0042278c (EventTypeToTableIndex)
int EventTypeToTableIndex(int type) {
    for (int i = 0; i < 0x9d; ++i)
        if (kEventTable[i].id == type) return i;
    return 0;
}

const char* EventText(const EventLogEntry& e) {
    if (e.text.raw == 0 || e.text.raw > uint32_t(kEventPoolSize)) return "";
    return g_eventPool + (e.text.raw - 1);
}

// orig: FUN_00423380  comparador de qsort: prioridad descendente (empates -> -1)
static int EventPrioCompare(const void* a, const void* b) {
    const EventLogEntry* ea = static_cast<const EventLogEntry*>(a);
    const EventLogEntry* eb = static_cast<const EventLogEntry*>(b);
    int d = int(kEventTable[EventTypeToTableIndex(eb->type)].prio) - int(kEventTable[EventTypeToTableIndex(ea->type)].prio);
    return d == 0 ? -1 : d;
}

// orig: FUN_004233e0  expulsa el evento de mayor prioridad si su prioridad <= prio (hace hueco en el pool)
static int EvictEvent(int prio) {
    if (gs.options.eventCount == 0) return 0;
    std::qsort(gs.events, size_t(gs.options.eventCount), sizeof(EventLogEntry), EventPrioCompare);   // FUN_004233c4
    if (kEventTable[EventTypeToTableIndex(gs.events[0].type)].prio > prio) return 0;
    int textOff = int(gs.events[0].text.raw) - 1;
    int len = int(std::strlen(g_eventPool + textOff)) + 1;
    std::memmove(g_eventPool + textOff, g_eventPool + textOff + len, size_t(g_eventPoolPtr - (textOff + len)));
    g_eventPoolPtr -= len;
    std::memset(g_eventPool + g_eventPoolPtr, 0, size_t(len));
    for (int i = 1; i <= gs.options.eventCount; ++i)
        if (gs.events[i].text.raw > uint32_t(textOff + 1)) gs.events[i].text.raw -= uint32_t(len);
    std::memmove(&gs.events[0], &gs.events[1], size_t(gs.options.eventCount - 1) * sizeof(EventLogEntry));
    std::memset(&gs.events[gs.options.eventCount - 1], 0, sizeof(EventLogEntry));
    gs.options.eventCount--;
    return 1;
}

// orig: FUN_004234d4 (AddEventLogEntry)  reserva len+1 bytes en el pool y añade la entrada.
// El retrato (EventLogEntry::portrait, FUN_004503f4) es un recurso gráfico: en el port se deja a 0.
int AddEventLogEntry(const char* text, int type, int len) {
    int prio = kEventTable[EventTypeToTableIndex(type)].prio;
    int need = len + 1;
    for (;;) {
        if (g_eventPoolPtr + need < kEventPoolEnd) {
            EventLogEntry& e = gs.events[gs.options.eventCount];
            e.text.raw = uint32_t(g_eventPoolPtr) + 1u;
            strncpyZ(g_eventPool + g_eventPoolPtr, text, size_t(need));
            g_eventPool[g_eventPoolPtr + need - 1] = 0;
            g_eventPoolPtr += need;
            e.type = uint16_t(type);
            e.portrait = 0;
            return gs.options.eventCount++;
        }
        if (!EvictEvent(prio)) break;
    }
    hooks::debugMessage("Not enough memory to log event.");
    return -1;
}

// ----------------------------------------------------------------------------------------
// 1. Cabecera
// ----------------------------------------------------------------------------------------
// orig: FUN_00461f74 (WriteHeaderRaw)  texto[88], version, isMap, 0, -1, 52 bytes (20 a cero; el resto es
// basura de pila en el original: aquí se escriben ceros).
void WriteHeaderRaw(SaveWriter& w, int isMap) {
    SaveHeader h{};
    std::memcpy(h.text, kSaveHeaderText, sizeof(kSaveHeaderText));
    h.version = kSaveVersion;
    h.isMap = isMap;
    h.zero = 0;
    h.minusOne = -1;
    std::memset(h.pad, 0, sizeof(h.pad));
    w.write(&h, sizeof(h));
}

// orig: FUN_00461ff4 (ReadHeaderRaw)  0 ok, 1 fichero de versión más nueva, 2 cabecera inválida
int ReadHeaderRaw(SaveReader& r, SaveHeader& h, int* generation) {
    if (!r.read(&h, sizeof(h))) return 2;
    if (std::memcmp(h.text, kSaveHeaderText, std::strlen(kSaveHeaderText)) == 0) {
        *generation = kHeaderGeneration;
    } else {
        int g = -1;
        for (int i = 0; i < 4; ++i)
            if (std::memcmp(h.text, kOldHeaderTexts[i], 0x58) == 0) { g = i; break; }
        if (g < 0) return 2;
        *generation = g;
    }
    return (int(h.version) > int(kSaveVersion)) ? 1 : 0;
}

// orig: FUN_0045f608 (ReadSaveHeader)  además exige que isMap coincida con gg.loadingMap
int ReadSaveHeader(SaveReader& r) {
    int rc = ReadHeaderRaw(r, g_lastHeader, &gg.fileGeneration);
    if (rc != 0) return rc;
    bool ok = (gg.loadingMap == 0 || g_lastHeader.isMap == 1) && (gg.loadingMap != 0 || g_lastHeader.isMap == 0);
    if (!ok) return 2;
    gg.fileVersion = int(g_lastHeader.version);
    return 0;
}

// ----------------------------------------------------------------------------------------
// 2. GameOptions
// ----------------------------------------------------------------------------------------
// orig: FUN_0045f664 (SaveOptions) + FUN_004620dc (WriteOptionsRaw)
void SaveOptions(SaveWriter& w) {
    GameOptions o{};
    std::memset(&o, 0, sizeof(o));
    o.turn = gs.options.turn;
    o.gameSeed = gs.options.gameSeed;
    o.gameId = gs.options.gameId;
    o.numPlayers = gs.options.numPlayers;
    o.winCities = gs.options.winCities;
    o.winShrines = gs.options.winShrines;
    o.winTurns = gs.options.winTurns;
    o.victory = gs.options.victory;
    o.fastProduction = gs.options.fastProduction;
    o.randomEvents = gs.options.randomEvents;
    o.aiSkill = gs.options.aiSkill;
    std::memset(o.reserved_2a, 0, sizeof(o.reserved_2a));
    o.netFlags = gs.options.netFlags;
    o.localPlayer = gg.localPlayer;
    o.eventLogFirst = gs.options.eventLogFirst;
    o.eventCount = gs.options.eventCount;
    o.autoTimer = gs.options.autoTimer;
    o.reserved_4e = gs.options.reserved_4e;
    o.autoTimerClock = gs.options.autoTimerClock;
    o.lastPlayerTimer = gs.options.lastPlayerTimer;
    o.lastPlayerClock = gs.options.lastPlayerClock;
    o.racialAbilities = gs.options.racialAbilities;
    std::memcpy(o.hasWon, gs.options.hasWon, sizeof(o.hasWon));
    o.worldResources = gs.options.worldResources;
    o.nextGlobalId = gs.options.nextGlobalId;
    o.campaign = gs.options.campaign;
    for (int i = 0; i < kMaxPlayers; ++i) {
        o.playerSkill[i] = gs.options.playerSkill[i];
        o.shrineTurns[i] = gs.options.shrineTurns[i];
    }
    o.playersMask = gs.options.playersMask;
    int camp = gs.options.campaign;
    for (int k = 0; k < 3; ++k) {
        uint32_t done = (camp >= 0 && camp < econ::kNumCampaigns) ? uint32_t(econ::gCampaigns[camp].goal[k].done) : 0u;
        o.campaignBytes[k] = uint8_t(done);
    }
    o.allowAlliances = gs.options.allowAlliances;
    w.write(&o, sizeof(o));
}

// orig: FUN_00462100 (ReadOptionsRaw)  tamaños por generación/versión y valores por defecto
bool ReadOptionsRaw(SaveReader& r, GameOptions& o, int version, int generation) {
    uint8_t* raw = reinterpret_cast<uint8_t*>(&o);
    std::memset(raw, 0, sizeof(o));
    auto u32at = [&](int off) -> uint32_t& { return *reinterpret_cast<uint32_t*>(raw + off); };
    if (generation < 4) {
        if (!r.read(raw, 0x74)) return false;
        u32at(0x74) = 1;                          // worldResources
        u32at(0x7c) = 0;                          // campaign
        int16_t maxId = 0;
        for (int i = 0; i < 8; ++i) {             // formato antiguo: 8 x u16 contadores de id en +0x2a
            uint16_t c = *reinterpret_cast<uint16_t*>(raw + 0x2a + 2 * i);
            if (int(maxId) < int(c)) maxId = int16_t(c);
            raw[0x80 + i] = 2;                    // playerSkill (escribe 8: pisa playersMask con 2)
            u32at(0x88 + 4 * i) = 0;              // shrineTurns (8 dwords: pisa 0xa4..0xa7)
        }
        std::memset(raw + 0xa4, 0, 3);
        u32at(0x78) = uint32_t(int32_t(maxId));   // nextGlobalId
        u32at(0xa8) = 1;                          // allowAlliances
    } else if (version < 3) {
        if (!r.read(raw, 0x88)) return false;
        for (int i = 0; i < 7; ++i) u32at(0x88 + 4 * i) = 0;
        std::memset(raw + 0xa4, 0, 3);
        u32at(0xa8) = 1;
    } else if (version < 9) {
        int cut = version < 7 ? 6 : 2;
        if (!r.read(raw, 0xac - size_t(cut))) return false;
        std::memset(raw + 0xa4, 0, 3);
        u32at(0xa8) = 1;
    } else {
        if (!r.read(raw, 0xac)) return false;
    }
    if (version == 0) {
        for (int i = 0; i < 7; ++i) {
            raw[0x80 + i] = 2;
            if (i < int(u32at(0x0c))) raw[0x87] |= uint8_t(1u << i);
        }
    }
    return true;
}

// orig: FUN_0045f828 (LoadOptions)  reparte el bloque a los globales; NO restaura hasWon (+0x66)
bool LoadOptions(SaveReader& r, bool restoreLocalPlayer) {
    GameOptions o;
    if (!ReadOptionsRaw(r, o, gg.fileVersion, gg.fileGeneration)) return false;
    GameOptions& g = gs.options;
    g.turn = o.turn;
    g.gameSeed = o.gameSeed;
    g.gameId = o.gameId;
    g.numPlayers = o.numPlayers;
    g.winCities = o.winCities;
    g.winShrines = o.winShrines;
    g.winTurns = o.winTurns;
    g.victory = o.victory;
    g.fastProduction = o.fastProduction;
    g.randomEvents = o.randomEvents;
    // Acotación de aiSkill tal como la genera el compilador: si el valor del fichero es < 1 -> 0; si no,
    // se toma el valor del fichero y se satura a 4 cuando es > 3 (min/max con temporales en pila).
    {
        int v = o.aiSkill < 1 ? 0 : o.aiSkill;
        if (v > 3) v = 4;
        g.aiSkill = v;
    }
    g.netFlags = o.netFlags;
    if (restoreLocalPlayer) gg.localPlayer = o.localPlayer;
    g.localPlayer = o.localPlayer;
    g.eventLogFirst = o.eventLogFirst;
    g.eventCount = o.eventCount;
    g.autoTimer = o.autoTimer;
    g.allowAlliances = o.allowAlliances;
    g.reserved_4e = o.reserved_4e;
    g.autoTimerClock = o.autoTimerClock;
    g.lastPlayerTimer = o.lastPlayerTimer;
    g.lastPlayerClock = o.lastPlayerClock;
    g.racialAbilities = o.racialAbilities;
    g.worldResources = o.worldResources;
    g.nextGlobalId = o.nextGlobalId;
    g.campaign = o.campaign;
    for (int i = 0; i < kMaxPlayers; ++i) {
        g.playerSkill[i] = o.playerSkill[i];
        g.shrineTurns[i] = o.shrineTurns[i];
    }
    g.playersMask = o.playersMask;
    std::memcpy(g.campaignBytes, o.campaignBytes, 3);
    if (g.campaign >= 0 && g.campaign < econ::kNumCampaigns)
        for (int k = 0; k < 3; ++k) econ::gCampaigns[g.campaign].goal[k].done = int32_t(o.campaignBytes[k]);
    return econ::CampaignApplyOptions(0) != 0;
}

// ----------------------------------------------------------------------------------------
// 3. WorldParams
// ----------------------------------------------------------------------------------------
// orig: FUN_0045fa10 (SaveWorld) + FUN_00462308
void SaveWorld(SaveWriter& w) { w.write(&gs.world, sizeof(WorldParams)); }
// orig: FUN_0045fa34 (LoadWorld) + FUN_00462328  (el original ignora el resultado de ReadFile)
bool LoadWorld(SaveReader& r) { r.read(&gs.world, sizeof(WorldParams)); return true; }

// ----------------------------------------------------------------------------------------
// 4. Player[7] + lista local
// ----------------------------------------------------------------------------------------
// orig: FUN_0045fa4c (SavePlayers)
bool SavePlayers(SaveWriter& w) {
    w.write(gs.players, sizeof(gs.players));
    for (Ptr32<LocalListNode> p = Ptr32<LocalListNode>{gs.players[gg.localPlayer].localList.raw}; p.raw; p = ptr(p)->next)
        w.write(&ptr(p)->value, 4);
    uint32_t end = 0xffffffffu;
    w.write(&end, 4);
    return true;
}

// orig: FUN_0045fae4 (LoadPlayers)
bool LoadPlayers(SaveReader& r) {
    if (gg.fileGeneration < 3) {
        size_t n = size_t(gs.options.numPlayers) * sizeof(Player);
        std::vector<uint8_t> tmp(n);
        if (!r.read(tmp.data(), n)) return false;
        std::memset(gs.players, 0, sizeof(gs.players));
        std::memcpy(gs.players, tmp.data(), n < sizeof(gs.players) ? n : sizeof(gs.players));
    } else {
        if (!r.read(gs.players, sizeof(gs.players))) return false;
        if (gg.fileGeneration < 4 || (gs.options.campaign != 0 && gs.options.turn == 1)) {
            for (int i = 0; i < gs.options.numPlayers; ++i) {
                if (int8_t(gs.players[i].type) > 0) {
                    gs.options.playersMask |= uint8_t(1u << i);
                    gs.players[i].defeated = 0;
                }
            }
        }
    }
    for (int i = 0; i < gs.options.numPlayers; ++i) gs.players[i].localList.raw = 0;
    if (gg.fileVersion >= 7) {
        Ptr32<LocalListNode> last{0};
        for (;;) {
            int32_t v;
            if (!r.read(&v, 4)) return false;
            if (v == -1) break;
            Ptr32<LocalListNode> node = AllocLocalListNode(uint32_t(v));
            if (last.raw == 0) gs.players[gg.localPlayer].localList.raw = node.raw;
            else ptr(last)->next = node;
            last = node;
        }
    }
    // LAB_0045fc80: se regeneran los nombres del jugador local ("New Player" = nombre de DL2.PRF) y de las IA
    for (int i = 0; i < kMaxPlayers; ++i) {
        Player& p = gs.players[i];
        if (i == gg.localPlayer)
            std::snprintf(p.name, sizeof(p.name), "%s", gg.defaultPlayerName);
        else if (int8_t(p.type) > 2)
            std::snprintf(p.name, sizeof(p.name), "%s", kAiLeaderNames[(p.race >= 0 && p.race < 7) ? p.race : 0]);
    }
    return true;
}

// ----------------------------------------------------------------------------------------
// 5. RaceStats
// ----------------------------------------------------------------------------------------
// orig: FUN_0045fd04 (SaveRaceStats)
void SaveRaceStats(SaveWriter& w) { w.write(&gs.raceStats, sizeof(RaceStats)); }

// orig: FUN_0045fd28 (LoadRaceStats)  version < 0x23: 0x356 (gen 0) ó 0x364 bytes, filas 61..63 de la tabla
bool LoadRaceStats(SaveReader& r) {
    if (gg.fileVersion < 0x23) {
        int16_t old[0x364 / 2] = {};
        if (gg.fileGeneration < 1) { if (!r.read(old, 0x356)) return false; }
        else                       { if (!r.read(old, 0x364)) return false; }
        for (int row = 0; row < 0x3e; ++row)
            for (int c = 0; c < 7; ++c) gs.raceStats.v[row][c] = old[row * 7 + c];
        for (int c = 0; c < 7; ++c) {
            if (gg.fileGeneration < 1) gs.raceStats.v[61][c] = kRaceStatsRows61[0][c];
            gs.raceStats.v[62][c] = kRaceStatsRows61[1][c];
            gs.raceStats.v[63][c] = kRaceStatsRows61[2][c];
        }
        return true;
    }
    return r.read(&gs.raceStats, sizeof(RaceStats));
}

// ----------------------------------------------------------------------------------------
// 6. Tecnologías
// ----------------------------------------------------------------------------------------
// orig: FUN_0045fe58 (SaveTechs)
bool SaveTechs(SaveWriter& w) {
    for (int i = 0; i < kNumTechs; ++i) {
        TechSaved t;
        t.knownMask = gs.techs[i].knownMask;
        t.availableMask = gs.techs[i].availableMask;
        std::memcpy(t.progress, gs.techs[i].progress, sizeof(t.progress));
        w.write(&t, sizeof(t));
    }
    return true;
}
// orig: FUN_0045fecc (LoadTechs)
bool LoadTechs(SaveReader& r) {
    for (int i = 0; i < kNumTechs; ++i) {
        TechSaved t;
        if (!r.read(&t, sizeof(t))) return false;
        gs.techs[i].knownMask = t.knownMask;
        gs.techs[i].availableMask = t.availableMask;
        std::memcpy(gs.techs[i].progress, t.progress, sizeof(t.progress));
    }
    return true;
}

// ----------------------------------------------------------------------------------------
// 7. Trabajos de ministros
// ----------------------------------------------------------------------------------------
// orig: FUN_0045ff40 (SaveMinisterJobs)  cabecera + nodos siguiendo next (los punteros van crudos)
bool SaveMinisterJobs(SaveWriter& w) {
    for (int i = 0; i < kMaxPlayers; ++i)
        for (MinisterJob* j = &gs.ministerJobHeads[i]; j; j = mjob(j->next))
            w.write(j, sizeof(MinisterJob));
    return true;
}
// orig: FUN_0045ff94 (LoadMinisterJobs)
bool LoadMinisterJobs(SaveReader& r) {
    if (gg.fileGeneration == 0 || gg.fileGeneration == 1) { ResetMinisterJobs(); return true; }
    for (int i = 0; i < kMaxPlayers; ++i) {
        MinisterJob* prev = &gs.ministerJobHeads[i];
        if (!r.read(prev, sizeof(MinisterJob))) return false;
        while (prev->next.raw != 0) {
            MinisterJob* node = AllocMinisterJobNode();
            if (!r.read(node, sizeof(MinisterJob))) return false;
            prev->next = mjobRef(node);
            node->prev = mjobRef(prev);
            prev = node;
        }
    }
    return true;
}

// ----------------------------------------------------------------------------------------
// 8. Event Log
// ----------------------------------------------------------------------------------------
// orig: FUN_0046002c (SaveEventLog)
bool SaveEventLog(SaveWriter& w) {
    for (int i = 0; i < gs.options.eventCount; ++i) {
        const EventLogEntry& e = gs.events[i];
        const char* text = EventText(e);
        int len = int(std::strlen(text));
        EventSaved s;
        s.type = e.type;
        s.textLen = uint16_t(len < 0x400 ? len : 0x3ff);
        s.player = e.player;
        s.param = e.param;
        w.write(&s, sizeof(s));
        w.write(text, s.textLen);
    }
    return true;
}
// orig: FUN_004600d0 (LoadEventLog)  sólo reconstruye las entradas si version == kSaveVersion
bool LoadEventLog(SaveReader& r) {
    int count = gs.options.eventCount;
    ClearEventLog();
    for (int i = 0; i < count; ++i) {
        EventSaved s;
        char text[1024];
        if (!r.read(&s, sizeof(s))) return false;
        if (!r.read(text, s.textLen)) return false;
        if (s.textLen < sizeof(text)) text[s.textLen] = 0; else text[sizeof(text) - 1] = 0;
        if (gg.fileVersion == int(kSaveVersion)) {
            gs.events[i].player = s.player;
            gs.events[i].param = s.param;
            if (AddEventLogEntry(text, s.type, s.textLen) == -1) return false;
        }
    }
    // FUN_00422d18: reconstruye los índices de las 6 categorías del Event Log (UI) - no aplica al port
    return true;
}

// ----------------------------------------------------------------------------------------
// 9. Tiles
// ----------------------------------------------------------------------------------------
// orig: FUN_00460188 (SaveTiles)
bool SaveTiles(SaveWriter& w) {
    for (int y = 0; y < gs.world.height; ++y)
        for (int x = 0; x < gs.world.width; ++x) w.write(&gs.tiles[y][x], sizeof(Tile));
    return true;
}
// orig: FUN_004601f0 (LoadTiles)
bool LoadTiles(SaveReader& r) {
    for (int y = 0; y < gs.world.height; ++y)
        for (int x = 0; x < gs.world.width; ++x)
            if (!r.read(&gs.tiles[y][x], sizeof(Tile))) return false;
    return true;
}

// ----------------------------------------------------------------------------------------
// 10. Edificios
// ----------------------------------------------------------------------------------------
// orig: FUN_00460258 (SaveBuildings)
bool SaveBuildings(SaveWriter& w) {
    int32_t n = 0;
    for (int i = 0; i < kMaxBuildings; ++i) if (gs.buildings[i].type != 0) ++n;
    w.write(&n, 4);
    for (int i = 0; i < kMaxBuildings; ++i) {
        if (gs.buildings[i].type == 0) continue;
        Building b;
        std::memcpy(&b, &gs.buildings[i], sizeof(Building));
        if (b.prev.raw) b.prev.raw = ptr(gs.buildings[i].prev)->id;
        if (b.next.raw) b.next.raw = ptr(gs.buildings[i].next)->id;
        w.write(&b, sizeof(Building));
    }
    return true;
}

// orig: FUN_00460330 (LoadBuildings)  gen 0/1: registros de 0x136 convertidos campo a campo
bool LoadBuildings(SaveReader& r) {
    std::memset(gs.buildings, 0, sizeof(gs.buildings));
    int32_t n;
    if (!r.read(&n, 4)) return false;
    if (n < 0 || n > kMaxBuildings) return false;
    if (gg.fileGeneration == 0 || gg.fileGeneration == 1) {
        std::vector<uint8_t> old(size_t(n) * 0x136);
        if (!r.read(old.data(), old.size())) return false;
        for (int i = 0; i < n; ++i) {
            const uint8_t* s = old.data() + size_t(i) * 0x136;
            uint8_t* d = reinterpret_cast<uint8_t*>(&gs.buildings[i]);
            std::memcpy(d + 0x00, s + 0x00, 2);  std::memcpy(d + 0x02, s + 0x02, 2);
            d[4] = s[4]; d[5] = s[5]; d[6] = s[6]; d[7] = s[7];
            std::memcpy(d + 0x08, s + 0x08, 2);  std::memcpy(d + 0x0a, s + 0x0a, 2);  std::memcpy(d + 0x0c, s + 0x0c, 2);
            d[0x0e] = s[0x0e]; d[0x0f] = s[0x0f];
            std::memcpy(d + 0x10, s + 0x10, 2);  std::memcpy(d + 0x12, s + 0x12, 2);
            std::memcpy(d + 0x14, s + 0x14, 2);  std::memcpy(d + 0x16, s + 0x16, 2);
            std::memcpy(d + 0x11a, s + 0x12e, 4); std::memcpy(d + 0x11e, s + 0x132, 4);
            for (int k = 0; k < 5; ++k) {
                std::memcpy(d + 0x18 + 4 * k, s + 0x18 + 4 * k, 4);   // labor[k]
                d[0x2c + k] = s[0x2c + k];                            // task[k]
                if (k < 4) {
                    d[0x31 + k] = s[0x31 + k];
                    std::memcpy(d + 0x36 + 2 * k, s + 0x36 + 2 * k, 2);
                }
            }
            for (int m = 0; m < 11; ++m) {
                std::memcpy(d + 0x3e + 4 * m, s + 0x3e + 4 * m, 4);   // cost[m]
                for (int t = 0; t < 4; ++t)
                    std::memcpy(d + 0x3e + 4 * m + 0x2c * (t + 1), s + 0x3e + 4 * m + 0x2c * (t + 1), 4);   // taskData[t][m]
            }
        }
    } else {
        if (!r.read(gs.buildings, size_t(n) * sizeof(Building))) return false;
    }
    for (int i = 0; i < n; ++i) {
        Building& b = gs.buildings[i];
        if (b.prev.raw) b.prev = ref(econ::FindBuildingByGlobalID(b.prev.raw));
        if (b.next.raw) b.next = ref(econ::FindBuildingByGlobalID(b.next.raw));
    }
    return true;
}

// ----------------------------------------------------------------------------------------
// 11. Ejércitos
// ----------------------------------------------------------------------------------------
// orig: FUN_004605e0 (SaveArmies)
bool SaveArmies(SaveWriter& w) {
    int32_t n = 0;
    for (int i = 0; i < kMaxArmies; ++i) if (gs.armies[i].type != 0) ++n;
    w.write(&n, 4);
    for (int i = 0; i < kMaxArmies; ++i) {
        const Army& src = gs.armies[i];
        if (src.type == 0) continue;
        Army a;
        std::memcpy(&a, &src, sizeof(Army));
        if (a.territory.raw) a.territory.raw = uint32_t(int32_t(int16_t(ptr(src.territory)->index)));
        if (a.dest.raw)      a.dest.raw      = uint32_t(int32_t(int16_t(ptr(src.dest)->index)));
        if (a.origin.raw)    a.origin.raw    = uint32_t(int32_t(int16_t(ptr(src.origin)->index)));
        if (a.next.raw)      a.next.raw      = ptr(src.next)->id;
        if (a.prev.raw)      a.prev.raw      = ptr(src.prev)->id;
        for (int k = 0; k < 3; ++k)
            if (a.cargo[k].raw) a.cargo[k].raw = ptr(src.cargo[k])->id;
        w.write(&a, sizeof(Army));
    }
    return true;
}

// orig: FUN_004606f4 (LoadArmies)  los territorios se resuelven en LoadTerritories
bool LoadArmies(SaveReader& r) {
    std::memset(gs.armies, 0, sizeof(gs.armies));
    int32_t n;
    if (!r.read(&n, 4)) return false;
    if (n < 0 || n > kMaxArmies) return false;
    if (!r.read(gs.armies, size_t(n) * sizeof(Army))) return false;
    for (int i = 0; i < n; ++i) {
        Army& a = gs.armies[i];
        if (a.next.raw) a.next = ref(econ::FindArmyByGlobalID(a.next.raw));
        if (a.prev.raw) a.prev = ref(econ::FindArmyByGlobalID(a.prev.raw));
        for (int k = 0; k < 3; ++k)
            if (a.cargo[k].raw) a.cargo[k] = ref(econ::FindArmyByGlobalID(a.cargo[k].raw));
        a.unk_44.raw = 0;
        a.job = 0;
    }
    return true;
}

// ----------------------------------------------------------------------------------------
// 12. Territorios y colas
// ----------------------------------------------------------------------------------------
// orig: FUN_004607d8 (SaveQueue)  u8 n + n registros de 0x30 (el byte 1 de cada registro es basura de
// pila en el original; aquí 0)
bool SaveQueue(SaveWriter& w, Ptr32<QueueHead> qp) {
    QueueHead* q = econ::qhead(qp);
    uint8_t n = 0;
    if (q) { n = uint8_t(econ::QueueCount(q)); econ::QueueFirst(q); }
    w.write(&n, 1);
    while (n != 0) {
        --n;
        uint8_t rec[0x30] = {};
        rec[0] = econ::QueueCurUnitType(q);
        uint16_t c = econ::QueueCurCount(q);
        std::memcpy(rec + 2, &c, 2);
        int32_t data[11] = {};
        econ::QueueCurData(q, data);
        std::memcpy(rec + 4, data, sizeof(data));
        w.write(rec, sizeof(rec));
        econ::QueueNext(q);
    }
    return true;
}

// orig: FUN_00460870 (SaveTerritories)  0x9b2 bytes por territorio + 5 colas
bool SaveTerritories(SaveWriter& w) {
    for (int i = 1; i <= int(gs.world.numTerritories); ++i) {
        const Territory& src = gs.territories[i];
        Territory t;
        std::memcpy(&t, &src, sizeof(Territory));
        if (gg.editorMode) t.knowledge = 100;
        if (t.armies.raw)        t.armies.raw        = ptr(src.armies)->id;
        if (t.foreignArmies.raw) t.foreignArmies.raw = ptr(src.foreignArmies)->id;
        for (int k = 0; k < int(int8_t(t.numTiles)); ++k) {
            const Tile* tl = ptr(src.tiles[k]);
            t.tiles[k].raw = (uint32_t(int8_t(tl->x)) & 0xffffu) | (uint32_t(int32_t(int8_t(tl->y))) << 16);
        }
        for (int k = 0; k < kNumSites; ++k)
            if (t.sites[k].building.raw) t.sites[k].building.raw = ptr(src.sites[k].building)->id;
        w.write(&t, kTerritorySavedBytes);
        for (int k = 0; k < 5; ++k)
            if (!SaveQueue(w, src.queues[k])) return false;
    }
    return true;
}

// orig: FUN_004609e8 (LoadQueue)  cabecera nueva (malloc(8) + QueueInit) y nodos si gen >= 2
bool LoadQueue(SaveReader& r, Ptr32<QueueHead>& q) {
    q = econ::AllocQueueHead();
    if (gg.fileGeneration > 1) {
        uint8_t n;
        if (!r.read(&n, 1)) return false;
        while (n != 0) {
            --n;
            uint8_t rec[0x30];
            if (!r.read(rec, sizeof(rec))) return false;
            econ::QueueAppend(econ::qhead(q), rec);
        }
    }
    return true;
}

// orig: FUN_00460a74 (LoadTerritories)
bool LoadTerritories(SaveReader& r) {
    std::memset(gs.territories, 0, sizeof(gs.territories));
    for (int i = 1; i <= int(gs.world.numTerritories); ++i) {
        Territory& t = gs.territories[i];
        if (gg.fileGeneration == 0 || gg.fileGeneration == 1) {
            if (!r.read(&t, 0xac4 - kTerritoryUnsavedTail)) return false;
            for (int k = 0; k < 5; ++k) t.queues[k] = econ::AllocQueueHead();
            t.hoverway = 0;
        } else {
            if (!r.read(&t, kTerritorySavedBytes)) return false;
            for (int k = 0; k < 5; ++k)
                if (!LoadQueue(r, t.queues[k])) return false;
        }
        if (t.armies.raw)        t.armies        = ref(econ::FindArmyByGlobalID(t.armies.raw));
        if (t.foreignArmies.raw) t.foreignArmies = ref(econ::FindArmyByGlobalID(t.foreignArmies.raw));
        for (int k = 0; k < int(int8_t(t.numTiles)); ++k) {
            uint32_t v = t.tiles[k].raw;
            int x = int(v & 0xffffu), y = int(v >> 16);
            t.tiles[k] = ref(&gs.tiles[0][0] + (size_t(y) * kTileRowBytes + size_t(x) * sizeof(Tile)) / sizeof(Tile));
        }
        for (int k = 0; k < kNumSites; ++k)
            if (t.sites[k].building.raw) t.sites[k].building = ref(econ::FindBuildingByGlobalID(t.sites[k].building.raw));
    }
    if (gg.fileGeneration == 0 || gg.fileGeneration == 1) {
        for (int i = 1; i <= int(gs.world.numTerritories); ++i)
            gs.territories[i].portTarget = uint16_t(flow::cb.findPortTargetTerritory ? flow::cb.findPortTargetTerritory(&gs.territories[i]) : 0);
    }
    for (int i = 0; i < kMaxArmies && gs.armies[i].type != 0; ++i) {
        Army& a = gs.armies[i];
        if (a.territory.raw) a.territory = ref(&gs.territories[a.territory.raw]);
        if (a.dest.raw)      a.dest      = ref(&gs.territories[a.dest.raw]);
        if (a.origin.raw)    a.origin    = ref(&gs.territories[a.origin.raw]);
    }
    return true;
}

// orig: FUN_00460d84 (SaveMapTerritories)  modo mapa: nombre[25] + terreno + 36 x {u16 terreno&0xf, u8 valor, u8}
bool SaveMapTerritories(SaveWriter& w) {
    for (int i = 1; i <= int(gs.world.numTerritories); ++i) {
        const Territory& t = gs.territories[i];
        MapTerritory m{};
        std::memset(&m, 0, sizeof(m));                 // el original deja basura de pila tras el NUL del nombre
        std::strncpy(m.name, t.name, sizeof(m.name) - 1);
        m.terrain = t.terrain;
        for (int k = 0; k < kNumSites; ++k) {
            m.sites[k].terrain = uint16_t(t.sites[k].terrainFlags & 0xf);
            m.sites[k].value = t.sites[k].value;
            m.sites[k].pad = 0;
        }
        w.write(&m, sizeof(m));
    }
    return true;
}

// orig: FUN_00460e54 (LoadMapTerritories)
bool LoadMapTerritories(SaveReader& r) {
    for (int i = 1; i <= int(gs.world.numTerritories); ++i) {
        MapTerritory m;
        if (!r.read(&m, sizeof(m))) return false;
        Territory& t = gs.territories[i];
        std::strncpy(t.name, m.name, sizeof(t.name));
        t.terrain = m.terrain;
        for (int k = 0; k < kNumSites; ++k) {
            t.sites[k].terrainFlags = m.sites[k].terrain;
            t.sites[k].value = m.sites[k].value;
        }
    }
    return true;
}

// ----------------------------------------------------------------------------------------
// 13. Jobs (task forces IA), máscara de guerra, jobs de trabajo y continentes
// ----------------------------------------------------------------------------------------
// orig: FUN_0040aebc (JobValidateArmies)
void JobValidateArmies(Job* job) {
    for (int i = 0; i < 16; ++i) {
        if (job->armies[i].raw == 0) continue;
        const Army* a = ptr(job->armies[i]);
        if (!a || a->id != job->armyIds[i] || int(a->owner) != int(job->owner)) {
            job->armies[i].raw = 0;
            job->armyIds[i] = 0;
        }
    }
}
// orig: FUN_00460f24 (JobsTerritoryPtrToIndex)  destination = (ptr - gTerritories) / 0xadc
void JobsTerritoryPtrToIndex() {
    for (int p = 0; p < kMaxPlayers; ++p)
        for (int j = 0; j < kJobsPerPlayer; ++j) {
            Ptr32<Territory>& d = gs.jobs[p][j].destination;
            if (d.raw) d.raw = uint32_t(ptr(d) - gs.territories);
        }
}
// orig: FUN_00460f68 (JobsTerritoryIndexToPtr)
void JobsTerritoryIndexToPtr() {
    for (int p = 0; p < kMaxPlayers; ++p)
        for (int j = 0; j < kJobsPerPlayer; ++j) {
            Ptr32<Territory>& d = gs.jobs[p][j].destination;
            if (d.raw) d = ref(&gs.territories[d.raw]);
        }
}

// orig: FUN_00460fa4 (SaveJobs)
bool SaveJobs(SaveWriter& w) {
    for (int p = 0; p < kMaxPlayers; ++p)
        for (int j = 0; j < kJobsPerPlayer; ++j) JobValidateArmies(&gs.jobs[p][j]);
    JobsTerritoryPtrToIndex();
    w.write(gs.jobs, sizeof(gs.jobs));
    w.write(gs.aiWarMask, sizeof(gs.aiWarMask));
    w.write(&gs.scratchJob1, sizeof(Job));
    w.write(&gs.scratchJob2, sizeof(Job));
    w.write(gs.continents, sizeof(gs.continents));
    JobsTerritoryIndexToPtr();
    return true;
}

// orig: FUN_00461078 (LoadJobs)
bool LoadJobs(SaveReader& r, bool restoreLocalPlayer) {
    if (gg.fileGeneration < 3) {
        if (!r.skip(0xc40)) return false;
        std::memset(gs.jobs, 0, sizeof(gs.jobs));
    } else {
        if (!r.read(gs.jobs, sizeof(gs.jobs))) return false;
        if (gg.fileVersion < 0x26) std::memset(gs.jobs, 0, sizeof(gs.jobs));
    }
    if (!r.read(gs.aiWarMask, sizeof(gs.aiWarMask))) return false;
    if (!r.read(&gs.scratchJob1, sizeof(Job))) return false;
    if (!r.read(&gs.scratchJob2, sizeof(Job))) return false;
    if (!r.read(gs.continents, sizeof(gs.continents))) return false;
    ComputeContinents();
    if (restoreLocalPlayer) {
        for (int i = 0; i < kMaxPlayers; ++i) {
            Player& p = gs.players[i];
            if (i == gg.localPlayer) {
                p.type = 1;
                gg.localPlayer = i;
                gg.localPlayerPtrIndex = i;
                gg.hostPlayer = i;
            } else if ((p.type == 1 || p.type == 2) && gg.netGame == 0) {
                if (gg.editorMode == 0) {
                    p.type = 3;
                    if (flow::cb.initAiPlayer) flow::cb.initAiPlayer(i);
                } else {
                    p.type = 1;
                }
            }
        }
    }
    for (int p = 0; p < kMaxPlayers; ++p)
        for (int j = 0; j < kJobsPerPlayer; ++j) {
            Job& job = gs.jobs[p][j];
            for (int k = 0; k < 16; ++k) {
                if (job.armyIds[k] == 0) { job.armies[k].raw = 0; continue; }
                Army* a = econ::FindArmyByGlobalID(job.armyIds[k]);
                job.armies[k] = ref(a);
                if (a) a->job = int16_t(j + 1);
            }
        }
    JobsTerritoryIndexToPtr();
    return true;
}

// ----------------------------------------------------------------------------------------
// 14..16. Eventos aleatorios, puntuaciones, espías y mercado negro
// ----------------------------------------------------------------------------------------
void SaveRandomEvents(SaveWriter& w) { w.write(gs.randomEvents, sizeof(gs.randomEvents)); }          // FUN_004612b0
bool LoadRandomEvents(SaveReader& r) {                                                                // FUN_004612d4
    if (gg.fileGeneration < 3) return true;
    return r.read(gs.randomEvents, sizeof(gs.randomEvents));
}
void SaveScores(SaveWriter& w) { w.write(gs.scores, sizeof(gs.scores)); }                            // FUN_00461308
bool LoadScores(SaveReader& r) {                                                                      // FUN_00461328
    if (gg.fileVersion < 0x11) { std::memset(gs.scores, 0, sizeof(gs.scores)); return true; }
    return r.read(gs.scores, sizeof(gs.scores));
}
// orig: FUN_0046136c (SaveSpiesAndBlackMarket)  en red el mercado negro se escribe como {0,-1}
bool SaveSpiesAndBlackMarket(SaveWriter& w) {
    w.write(gs.spies, sizeof(gs.spies));
    if (gg.netGame == 0) {
        w.write(gs.blackMarket, sizeof(gs.blackMarket));
    } else {
        BlackMarketState bm[kMaxPlayers];
        for (int i = 0; i < kMaxPlayers; ++i) { bm[i].pending = 0; bm[i].turn = -1; }
        w.write(bm, sizeof(bm));
    }
    return true;
}
// orig: FUN_00461418 (LoadSpiesAndBlackMarket)
bool LoadSpiesAndBlackMarket(SaveReader& r) {
    if (gg.fileVersion < 0x24) { ResetSpies(); econ::BlackMarketReset(); return true; }
    if (!r.read(gs.spies, sizeof(gs.spies))) return false;
    return r.read(gs.blackMarket, sizeof(gs.blackMarket));
}

// orig: FUN_0046147c (RebuildObjectLists)
void RebuildObjectLists() {
    econ::RebuildBuildingLists();
    econ::RebuildArmyFreeList();
}

// ----------------------------------------------------------------------------------------
// SaveGame
// ----------------------------------------------------------------------------------------
// orig: FUN_00461488 (SaveGame) - imagen del fichero en memoria
bool saveGameToMemory(std::vector<uint8_t>& out, bool isMap) {
    SaveWriter w;
    if (!isMap) {
        WriteHeaderRaw(w, 0);
        SaveOptions(w);
        SaveWorld(w);
        if (!SavePlayers(w)) return false;
        SaveRaceStats(w);
        if (!SaveTechs(w)) return false;
        if (!SaveMinisterJobs(w)) return false;
        if (!SaveEventLog(w)) return false;
        if (!SaveTiles(w)) return false;
        if (!SaveBuildings(w)) return false;
        if (!SaveArmies(w)) return false;
        if (!SaveTerritories(w)) return false;
        if (!SaveJobs(w)) return false;
        SaveRandomEvents(w);
        SaveScores(w);
        if (!SaveSpiesAndBlackMarket(w)) return false;
    } else {
        WriteHeaderRaw(w, 1);
        SaveWorld(w);
        if (!SaveMapTerritories(w)) return false;
        if (!SaveTiles(w)) return false;
    }
    out.swap(w.buf);
    return true;
}

// orig: FUN_00461488 (SaveGame)  (la parte de diálogo de nombre de fichero, FUN_004396a0, es UI: el
// llamador pasa la ruta; DefaultSaveName()/BuildSavePath() de campaign_flow.h reproducen "%s%03d")
bool saveGame(const char* path, bool isMap, bool makeBackup) {
    if (gg.editorMode != 0) {
        // Editor: el original pide con FUN_00416af0 qué raza será la local (UI) y llama a SwitchLocalPlayer;
        // aquí se conserva el jugador local actual.
        gg.numShrinesPlaced = 0;
        SwitchLocalPlayer(gg.localPlayer);
    }
    if (gg.netGame == 0) {
        gs.options.gameId = RandRangeTagged(10000, "SaveGame");
        SyncSetRandomSeed(uint32_t(gs.options.gameId));
    }
    if (gg.editorMode != 0 && !isMap) {
        for (int i = 0; i < kMaxPlayers; ++i)
            if (i != gg.localPlayer && flow::cb.initAiPlayer) flow::cb.initAiPlayer(i);
        if (flow::cb.aiRelationsInit) flow::cb.aiRelationsInit();
        gs.options.turn = 1;
        ClearEventLog();
    }
    if (gg.editorMode != 0 && gs.options.victory == 2 && !isMap) {
        econ::CountShrines();
        if (gg.totalShrines < gs.options.winShrines &&
            hooks::messageBox("Save Game Error",
                              "This scenario map does not have enough shrines to complete the SHRINE WARS victory condition. Are you sure you want to save?",
                              0x18) == 2)
            return false;
    }
    if (makeBackup) {
        char backup[512];
        BackupPath(backup, sizeof(backup), CurrentSaveKind(isMap));
        std::remove(backup);
        std::rename(path, backup);
    }
    std::vector<uint8_t> image;
    if (!saveGameToMemory(image, isMap)) return false;
    std::FILE* f = std::fopen(path, "wb");
    if (!f) return false;
    bool ok = std::fwrite(image.data(), 1, image.size(), f) == image.size();
    std::fclose(f);
    if (!ok) {
        // "Unable to save current game.\nWould you like to try again?" (param_2): el llamador decide reintentar
        return false;
    }
    return true;
}

// ----------------------------------------------------------------------------------------
// LoadGame
// ----------------------------------------------------------------------------------------
static bool readWholeFile(const char* path, std::vector<uint8_t>& out) {
    std::FILE* f = std::fopen(path, "rb");
    if (!f) return false;
    std::fseek(f, 0, SEEK_END);
    long sz = std::ftell(f);
    std::fseek(f, 0, SEEK_SET);
    if (sz < 0) { std::fclose(f); return false; }
    out.resize(size_t(sz));
    bool ok = sz == 0 || std::fread(out.data(), 1, size_t(sz), f) == size_t(sz);
    std::fclose(f);
    return ok;
}

// orig: FUN_004618e8 (LoadGame)
bool loadGameFromMemory(const uint8_t* data, size_t size, bool restoreLocalPlayer) {
    WorldParams worldBefore;
    std::memcpy(&worldBefore, &gs.world, sizeof(WorldParams));
    SaveReader r{data, size, 0};
    int hdr = ReadSaveHeader(r);
    if (hdr != 0) {
        g_lastError = hdr == 1 ? LoadError::NewerVersion : LoadError::NotValid;
        hooks::messageBox("Load Game Error", hdr == 1 ? "%s is a savefile from a newer version of deadlock. Unable to load game."
                                                      : "%s is not a valid saved game.  Unable to load game.", 4);
        return false;
    }
    ResetVariables(restoreLocalPlayer ? 1 : 0);
    ClearEventLog();
    if (flow::cb.resetSeaManipulation) flow::cb.resetSeaManipulation();
    bool ok = LoadOptions(r, restoreLocalPlayer) && LoadWorld(r) && LoadPlayers(r) && LoadRaceStats(r) &&
              LoadTechs(r) && LoadMinisterJobs(r) && LoadEventLog(r) && LoadTiles(r) && LoadBuildings(r) &&
              LoadArmies(r) && LoadTerritories(r) && LoadJobs(r, restoreLocalPlayer) && LoadRandomEvents(r) &&
              LoadScores(r) && LoadSpiesAndBlackMarket(r);
    if (!ok) {
        gg.gameAborted = 1;
        g_lastError = LoadError::Corrupt;
        hooks::messageBox("Load Game Error", "%s is corrupt.  Unable to load game.", 4);
        return false;
    }
    RebuildObjectLists();
    if (std::memcmp(&gs.world, &worldBefore, sizeof(WorldParams)) != 0) {
        // FUN_004360ec / FUN_0046ce10(0) / PreloadSprite2 / FUN_0042e434... : liberación de la pantalla y
        // sprites de la partida anterior (UI). Aquí sólo la parte de lógica.
        hooks::refresh("LoadGame:NewWorld");
        rtl::srand(gs.world.rngSeed);
        PrepareLongRangeScan();                      // FUN_0046a844 (worldgen): mapa de alturas / colores
        if (gg.gameAborted == 0) {
            // FUN_0046338c: paleta del tipo de mundo (gráficos)
            for (int i = 1; i <= int(gs.world.numTerritories); ++i) gs.territories[i].flags &= 0xfff0u;
            // FUN_0046f5d4: crea la ventana de juego y selecciona el territorio inicial (parte lógica):
            SelectInitialTerritory();
        } else {
            std::memset(&gs.world, 0, sizeof(WorldParams));
        }
    }
    if (gg.gameAborted != 0) {
        g_lastError = LoadError::Corrupt;
        return false;
    }
    if (restoreLocalPlayer && flow::cb.initAiPlayer)
        for (int i = 0; i < kMaxPlayers; ++i) flow::cb.initAiPlayer(i);
    econ::CountShrines();
    econ::AfterMovePhase(1);                         // FUN_0046e730(1)
    gg.winCitiesEffective = gs.options.winCities;
    gg.gameStarted = 1;                              // DAT_004d59bc = 1 (DAT_004d1bf4 = 1 es un flag de UI)
    econ::CampaignClearForbiddenResearch();          // FUN_004501b0
    if (gs.options.autoTimer != 0 && flow::cb.startTurnTimer) flow::cb.startTurnTimer(gs.options.autoTimerClock);
    if (flow::cb.lastPlayerTimerCheck) flow::cb.lastPlayerTimerCheck();
    if (gg.netGame == 0) SyncSetRandomSeed(uint32_t(gs.options.gameId));
    if (gs.options.turn == 1 && gs.options.campaign > 0 && flow::cb.campaignIntro)
        flow::cb.campaignIntro((gs.options.campaign - 1) % 6, 0);
    g_lastError = LoadError::None;
    return true;
}

bool loadGame(const char* path, bool restoreLocalPlayer) {
    std::vector<uint8_t> data;
    if (!readWholeFile(path, data)) {
        g_lastError = LoadError::CannotOpen;
        char msg[512];
        std::snprintf(msg, sizeof(msg), "Could not open file %s.", path);
        hooks::messageBox("Load Game Error", msg, 4);
        return false;
    }
    return loadGameFromMemory(data.data(), data.size(), restoreLocalPlayer);
}

// ----------------------------------------------------------------------------------------
// LEVELS.HDX / LEVELS.HDD
// ----------------------------------------------------------------------------------------
#pragma pack(push, 1)
struct HdxEntry { char name[8]; uint32_t offset; };
#pragma pack(pop)

int hdxEntryNames(const char* hdxBasePath, std::vector<std::string>& names) {
    std::vector<uint8_t> hx;
    if (!readWholeFile((std::string(hdxBasePath) + ".HDX").c_str(), hx) || hx.size() < 4) return 0;
    uint32_t n; std::memcpy(&n, hx.data(), 4);
    for (uint32_t i = 0; i < n && 4 + (i + 1) * sizeof(HdxEntry) <= hx.size(); ++i) {
        HdxEntry e; std::memcpy(&e, hx.data() + 4 + i * sizeof(HdxEntry), sizeof(e));
        char nm[9]; std::memcpy(nm, e.name, 8); nm[8] = 0;
        names.emplace_back(nm);
    }
    return int(names.size());
}

bool readHdxEntry(const char* hdxBasePath, const char* entryName, std::vector<uint8_t>& out) {
    std::vector<uint8_t> hx;
    if (!readWholeFile((std::string(hdxBasePath) + ".HDX").c_str(), hx) || hx.size() < 4) return false;
    uint32_t n; std::memcpy(&n, hx.data(), 4);
    for (uint32_t i = 0; i < n && 4 + (i + 1) * sizeof(HdxEntry) <= hx.size(); ++i) {
        HdxEntry e; std::memcpy(&e, hx.data() + 4 + i * sizeof(HdxEntry), sizeof(e));
        char nm[9]; std::memcpy(nm, e.name, 8); nm[8] = 0;
        if (std::strcmp(nm, entryName) != 0) continue;
        std::FILE* f = std::fopen((std::string(hdxBasePath) + ".HDD").c_str(), "rb");
        if (!f) return false;
        uint32_t len = 0;
        bool ok = std::fseek(f, long(e.offset), SEEK_SET) == 0 && std::fread(&len, 1, 4, f) == 4;
        if (ok) { out.resize(len); ok = std::fread(out.data(), 1, len, f) == len; }
        std::fclose(f);
        return ok;
    }
    return false;
}

bool loadScenario(const char* hdxBasePath, const char* entryName, bool restoreLocalPlayer) {
    std::vector<uint8_t> data;
    if (!readHdxEntry(hdxBasePath, entryName, data)) { g_lastError = LoadError::CannotOpen; return false; }
    return loadGameFromMemory(data.data(), data.size(), restoreLocalPlayer);
}

// ----------------------------------------------------------------------------------------
// LoadMapFile
// ----------------------------------------------------------------------------------------
// orig: FUN_00461c68 (LoadMapFile)
bool loadMapFileFromMemory(const uint8_t* data, size_t size) {
    SaveReader r{data, size, 0};
    int saved = gg.loadingMap;
    gg.loadingMap = 1;
    int hdr = ReadSaveHeader(r);
    gg.loadingMap = saved;
    if (hdr != 0) {
        g_lastError = hdr == 1 ? LoadError::NewerVersion : LoadError::NotValid;
        hooks::messageBox("Load Game Error", hdr == 1 ? "%s is a savefile from a newer version of deadlock. Unable to load game."
                                                      : "%s is not a valid saved game.  Unable to load game.", 4);
        return false;
    }
    if (!(LoadWorld(r) && LoadMapTerritories(r) && LoadTiles(r))) {
        g_lastError = LoadError::Corrupt;
        hooks::messageBox("Load Game Error", "%s is corrupt.  Unable to load game.", 4);
        return false;
    }
    g_lastError = LoadError::None;
    return true;
}

bool loadMapFile(const char* path) {
    std::vector<uint8_t> data;
    if (!readWholeFile(path, data)) {
        g_lastError = LoadError::CannotOpen;
        char msg[512];
        std::snprintf(msg, sizeof(msg), "Could not open file %s.", path);
        hooks::messageBox("Load Game Error", msg, 4);
        return false;
    }
    return loadMapFileFromMemory(data.data(), data.size());
}

// ----------------------------------------------------------------------------------------
// Lecturas parciales de un .SAV (menú de carga en red)
// ----------------------------------------------------------------------------------------
// orig: FUN_00461d80  raza del jugador local (Player[localPlayer].race) de un fichero de partida
int ReadSavePlayerRace(const char* path) {
    std::vector<uint8_t> d;
    if (!readWholeFile(path, d)) return -1;
    SaveReader r{d.data(), d.size(), 0};
    GameOptions o; WorldParams w;
    if (!r.skip(0x9c) || !r.read(&o, sizeof(o)) || !r.read(&w, sizeof(w))) return -1;
    if (!r.skip(size_t(o.localPlayer) * sizeof(Player))) return -1;
    Player p;
    if (!r.read(&p, sizeof(p))) return -1;   // el original devuelve la raza sólo si ReadFile FALLA (bug): aquí se devuelve siempre
    return p.race;
}

// orig: FUN_00461e9c  Player[7] de un fichero (offset 0x15c) -> gs.players; devuelve nº de jugadores con type > 0
int ReadSavePlayers(const char* path, uint8_t* raceMask) {
    std::vector<uint8_t> d;
    if (!readWholeFile(path, d)) {
        char msg[512];
        std::snprintf(msg, sizeof(msg), "Could not open file %s.", path);
        hooks::messageBox("Load Game Error", msg, 4);
        return -1;
    }
    SaveReader r{d.data(), d.size(), 0};
    int count = 0;
    if (r.skip(0x15c) && r.read(gs.players, sizeof(gs.players))) {
        *raceMask = 0;
        for (int i = 0; i < kMaxPlayers; ++i)
            if (int8_t(gs.players[i].type) > 0) { ++count; *raceMask |= uint8_t(1u << (gs.players[i].race & 0x1f)); }
    }
    return count;
}

} // namespace dl2
