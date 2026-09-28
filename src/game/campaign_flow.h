// campaign_flow.h - Progresión de campaña, rutas de ficheros y AutoSave (módulo game flow).
//
// Los OBJETIVOS de campaña (FUN_0044fd14 .. FUN_00450380, tabla DAT_004c6194) los porta el módulo
// economy (src/game/economy.h: econ::gCampaigns, econ::CampaignApplyOptions...). Aquí va el resto:
//   - kCampaignDefaults: los 43 registros de 0xd8 bytes de DAT_004c6194 (índice 0 = sin campaña,
//     1..42 = raza*6 + capítulo; ver campaignRace()/campaignChapter()),
//   - tabla de jugadores de campaña DAT_004dc434 (10 x 0x9c) y CampaignAddPlayer (FUN_0047c730),
//   - rutas "saves\\", "campaign\\", "custom\\", "maps\\", "%s%03d" (FUN_00438fe0 / FUN_004399dc),
//   - AutoSave (FUN_00470740), extracción del escenario de LEVELS.HDD (FUN_00467e58) y arranque de
//     campaña (FUN_00467fc0 / FUN_00468030).
#pragma once
#include <cstdint>

#include "game/economy.h"
#include "game/game_state.h"
#include "game/globals.h"

namespace dl2 {

constexpr int kNumCampaignDefs = 43;                      // DAT_004c6194: registros 0..42
extern const econ::CampaignDef kCampaignDefaults[kNumCampaignDefs];
void CampaignTableReset();                                // copia kCampaignDefaults en econ::gCampaigns
inline int campaignRace(int campaign)    { return (campaign - 1) / 6; }         // FUN_00468030: 1..42 -> raza 0..6
inline int campaignChapter(int campaign) { return (campaign - 1) % 6 + 1; }     // 1..6
inline int campaignIndex(int race, int chapter) { return race * 6 + chapter; }

struct CampaignPlayerDef {           // DAT_004dc434 + i*0x9c (FUN_0047c730)
    uint8_t  race;                   // +0x00
    uint8_t  pad[3];
    int32_t  territory[4];           // +0x04 candidatos de territorio (FUN_0047c6c0)
    int32_t  techLevel;              // +0x14 se aprenden las tecnologías con TechEntry::level <= techLevel
    int32_t  credits;                // +0x18
    int32_t  materials[10];          // +0x1c Territory::materials[1..10]
    struct { int32_t unitType, count; } units[10]; // +0x44
    int32_t  pactRace;               // +0x94 raza con la que pacta (FUN_00441700)
    int32_t  pactType;               // +0x98
};
static_assert(sizeof(CampaignPlayerDef) == 0x9c);
constexpr int kNumCampaignPlayers = 10;
extern const CampaignPlayerDef kCampaignPlayers[kNumCampaignPlayers];

int  CampaignPlayerTerritory(int defIndex);               // orig: FUN_0047c6c0
void CampaignAddPlayer();                                 // orig: FUN_0047c730 (CampaignAddPlayer): se llama cada turno

// Rutas (FUN_00438fe0 / FUN_004399dc / SaveGame): directorio y extensión según el modo.
enum class SaveKind { Saves = 0, Campaign = 1, MultiSaves = 2, Custom = 3, Maps = 4 };
SaveKind CurrentSaveKind(bool isMap);                     // netGame -> MultiSaves; campaign > 0 -> Campaign; ...
const char* SaveDir(SaveKind k);                          // "saves\\", "campaign\\", "msaves\\", "custom\\", "maps\\"
const char* SaveExt(SaveKind k);                          // ".SAV", ".CPN", ".MSV", ".SCE", ".MAP"
void DefaultSaveName(char* out, size_t n);                // "%s%03d" (raza corta del jugador local + turno) (SaveGame)
void BuildSavePath(char* out, size_t n, const char* baseName, SaveKind k); // "%s%s%s"
void AutoSavePath(char* out, size_t n);                   // "%sAUTOSAVE%s" (AutoSave)
void BackupPath(char* out, size_t n, SaveKind k);         // "%sBackup.bak"
void AutoSave();                                          // orig: FUN_00470740 (AutoSave)

// Extrae la entrada "<RAZA><capítulo>" de LEVELS.HDD a campaign\AUTOSAVE.CPN (FUN_00467e58) y devuelve la ruta.
bool ExtractCampaignScenario(const char* levelsBasePath, int race, int chapter, char* outPath, size_t n);

} // namespace dl2
