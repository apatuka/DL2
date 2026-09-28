// EXPERIMENTAL / NOT BUILT: this historical gameplay loader is incomplete.
// Use game/save_document.h for the validated, independent physical file codec.
// Do not enable this implementation without completing gameplay activation and its safety audit.
// saveload.h - Guardar / cargar partidas, campañas, escenarios de LEVELS.HDD y mapas del editor.
//
// Port de SaveGame (FUN_00461488), LoadGame (FUN_004618e8), LoadMapFile (FUN_00461c68) y sus 16 pares
// escritor/lector (ver docs/SAVEFORMAT.md y re/names_structs.tsv). Este intento no está integrado
// ni verificado. Su conversión de punteros de 32 bits pretende usar índices/IDs al escribir y
// Ptr32 (índices 1-based, ver globals.h) al leer:
//   Building::prev/next, BuildingSite::building  <-> Building::id     (econ::FindBuildingByGlobalID)
//   Army::cargo/next/prev, Territory::armies/foreignArmies <-> Army::id (econ::FindArmyByGlobalID)
//   Army::territory/dest/origin, Job::destination <-> Territory::index
//   Territory::tiles[i] <-> x | y<<16 (ref(Tile*) = y*40+x+1)
//   Territory::queues[k] -> econ::AllocQueueHead() (pool de economy)
//   Player::localList -> pool de nodos {u32 val; next} de este módulo (LocalListNode)
//   MinisterJob::next/prev -> raw 1..7 = cabecera gs.ministerJobHeads[raw-1]; raw >= 8 = nodo del pool
//   EventLogEntry::text -> offset+1 en el pool lineal de textos (0xc00 bytes, PTR_DAT_004b7b54)
#pragma once
#include <cstddef>
#include <cstdint>
#include <vector>

#include "game/game_state.h"
#include "game/globals.h"

namespace dl2 {

// ----------------------------------------------------------------------------------------
// API principal
// ----------------------------------------------------------------------------------------
// orig: FUN_004618e8 (LoadGame). restoreLocalPlayer = param_2: restaura GameOptions::localPlayer,
// convierte en IA a los humanos que no son el local y regenera las personalidades IA.
bool loadGame(const char* path, bool restoreLocalPlayer);
bool loadGameFromMemory(const uint8_t* data, size_t size, bool restoreLocalPlayer);
// Escenario de LEVELS.HDX/HDD (entrada "CHCHT1".."UVA6"): lee el par HDX/HDD y carga la partida.
bool loadScenario(const char* hdxBasePath, const char* entryName, bool restoreLocalPlayer = true);
// orig: FUN_00461488 (SaveGame). isMap = local_8 (fichero de mapa del editor). makeBackup = param_3
// (renombra el fichero anterior a "<dir>Backup.bak" como hace el autosave).
bool saveGame(const char* path, bool isMap, bool makeBackup = false);
bool saveGameToMemory(std::vector<uint8_t>& out, bool isMap);
// orig: FUN_00461c68 (LoadMapFile): cabecera con isMap = 1, WorldParams, MapTerritory[N], tiles.
bool loadMapFile(const char* path);
bool loadMapFileFromMemory(const uint8_t* data, size_t size);

// Lectura de un contenedor HDX/HDD (u32 count; {char name[8]; u32 offset}[count]; HDD: u32 len + datos).
bool readHdxEntry(const char* hdxBasePath, const char* entryName, std::vector<uint8_t>& out);
int  hdxEntryNames(const char* hdxBasePath, std::vector<std::string>& names);

// Resultado detallado de la última carga (para tests / mensajes de error).
enum class LoadError { None = 0, CannotOpen, NewerVersion, NotValid, Corrupt };
LoadError lastLoadError();

// ----------------------------------------------------------------------------------------
// Cabecera y lectores/escritores individuales (bloques 1..16); expuestos para tests y para el
// módulo de red (SynchronizeGame usa los mismos bloques).
// ----------------------------------------------------------------------------------------
struct SaveWriter { std::vector<uint8_t> buf; void write(const void* p, size_t n); };
struct SaveReader {
    const uint8_t* p = nullptr; size_t n = 0; size_t off = 0;
    bool read(void* dst, size_t len);
    bool skip(size_t len);
    size_t remaining() const { return n > off ? n - off : 0; }
};

extern const char kSaveHeaderText[];         // DAT_004d1ea0 (88 bytes con NUL)
extern const char* const kOldHeaderTexts[4]; // versiones S/T/U/V (generaciones 0..3)

void WriteHeaderRaw(SaveWriter& w, int isMap);                       // FUN_00461f74
int  ReadHeaderRaw(SaveReader& r, SaveHeader& h, int* generation);   // FUN_00461ff4: 0 ok, 1 más nueva, 2 inválida
int  ReadSaveHeader(SaveReader& r);                                  // FUN_0045f608: fija gg.fileGeneration/gg.fileVersion
void SaveOptions(SaveWriter& w);                                     // FUN_0045f664 + FUN_004620dc
bool LoadOptions(SaveReader& r, bool restoreLocalPlayer);            // FUN_0045f828 + FUN_00462100
bool ReadOptionsRaw(SaveReader& r, GameOptions& o, int version, int generation); // FUN_00462100
void SaveWorld(SaveWriter& w);                                       // FUN_0045fa10
bool LoadWorld(SaveReader& r);                                       // FUN_0045fa34
bool SavePlayers(SaveWriter& w);                                     // FUN_0045fa4c
bool LoadPlayers(SaveReader& r);                                     // FUN_0045fae4
void SaveRaceStats(SaveWriter& w);                                   // FUN_0045fd04
bool LoadRaceStats(SaveReader& r);                                   // FUN_0045fd28
bool SaveTechs(SaveWriter& w);                                       // FUN_0045fe58
bool LoadTechs(SaveReader& r);                                       // FUN_0045fecc
bool SaveMinisterJobs(SaveWriter& w);                                // FUN_0045ff40
bool LoadMinisterJobs(SaveReader& r);                                // FUN_0045ff94
bool SaveEventLog(SaveWriter& w);                                    // FUN_0046002c
bool LoadEventLog(SaveReader& r);                                    // FUN_004600d0
bool SaveTiles(SaveWriter& w);                                       // FUN_00460188
bool LoadTiles(SaveReader& r);                                       // FUN_004601f0
bool SaveBuildings(SaveWriter& w);                                   // FUN_00460258
bool LoadBuildings(SaveReader& r);                                   // FUN_00460330
bool SaveArmies(SaveWriter& w);                                      // FUN_004605e0
bool LoadArmies(SaveReader& r);                                      // FUN_004606f4
bool SaveTerritories(SaveWriter& w);                                 // FUN_00460870
bool SaveQueue(SaveWriter& w, Ptr32<QueueHead> q);                   // FUN_004607d8
bool LoadTerritories(SaveReader& r);                                 // FUN_00460a74
bool LoadQueue(SaveReader& r, Ptr32<QueueHead>& q);                  // FUN_004609e8
bool SaveMapTerritories(SaveWriter& w);                              // FUN_00460d84
bool LoadMapTerritories(SaveReader& r);                              // FUN_00460e54
bool SaveJobs(SaveWriter& w);                                        // FUN_00460fa4
bool LoadJobs(SaveReader& r, bool restoreLocalPlayer);               // FUN_00461078
void JobsTerritoryPtrToIndex();                                      // FUN_00460f24
void JobsTerritoryIndexToPtr();                                      // FUN_00460f68
void JobValidateArmies(Job* job);                                    // FUN_0040aebc
void SaveRandomEvents(SaveWriter& w);                                // FUN_004612b0
bool LoadRandomEvents(SaveReader& r);                                // FUN_004612d4
void SaveScores(SaveWriter& w);                                      // FUN_00461308
bool LoadScores(SaveReader& r);                                      // FUN_00461328
bool SaveSpiesAndBlackMarket(SaveWriter& w);                         // FUN_0046136c
bool LoadSpiesAndBlackMarket(SaveReader& r);                         // FUN_00461418
void RebuildObjectLists();                                           // FUN_0046147c
void ClearEventLog();                                                // FUN_004238c8
int  AddEventLogEntry(const char* text, int type, int len);          // FUN_004234d4
int  EventTypeToTableIndex(int type);                                // FUN_0042278c
const char* EventText(const EventLogEntry& e);                       // texto del pool (o "")
int  ReadSavePlayerRace(const char* path);                           // FUN_00461d80: raza del jugador local de un .SAV
int  ReadSavePlayers(const char* path, uint8_t* raceMask);           // FUN_00461e9c: Player[7] de un .SAV (+ máscara de razas)

// ----------------------------------------------------------------------------------------
// Pools propios de este módulo
// ----------------------------------------------------------------------------------------
struct LocalListNode { uint32_t value; Ptr32<LocalListNode> next; };   // Player::localList (malloc(8))
LocalListNode* ptr(Ptr32<LocalListNode> p);
Ptr32<LocalListNode> AllocLocalListNode(uint32_t value);
void ResetLocalLists();                                              // FUN_0046c9f8 (parte de Player::localList)

MinisterJob* mjob(Ptr32<MinisterJob> p);                             // raw 1..7 cabecera, >= 8 nodo del pool
Ptr32<MinisterJob> mjobRef(const MinisterJob* j);
MinisterJob* AllocMinisterJobNode();                                 // malloc(0x44) (FUN_004b0b44)
void ResetMinisterJobs();                                            // FUN_00405798 ResetMinisterJobs
void FreeMinisterJobs();                                             // FUN_004057c4 FreeMinisterJobs

// Campos de la cabecera de fichero del último LoadGame (para tests)
const SaveHeader& lastSaveHeader();

} // namespace dl2
