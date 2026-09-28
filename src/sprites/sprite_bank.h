// sprite_bank.h - SPRITENW.DAT loader: sprite type tables, lazy per-type pixel loading and the phase
// sprite sets of the original (global / settlement / control / combat).
//
// Original functions (DEADLOCK.EXE v1.20):
//   FUN_0048300c TypePixelBytes(table)      sum of w*h over a SpriteDef table
//   FUN_0048307c TypePixelBytesByType(type)
//   FUN_00483038 RemapSpritePixels(def)     0 -> 255, 255 -> 192 after loading
//   FUN_00483098 ReadTypeFrames(file, table, dst)   reads every frame of a table into one block
//   FUN_00483120 ReadTypeFramesSkipFirst    (LoadPhaseSpriteFile variant that skips frame 0 of the last type)
//   FUN_00482fc8 UnloadType(type)           clears the loaded bit and the pixel pointers
//   FUN_004831ac PushPhaseSet / FUN_00483538 PopOldestPhaseSet / FUN_004835a8 PopAllPhaseSets
//   FUN_004835bc UnloadAllSprites            (also frees the global block DAT_004dcf50)
//   FUN_00483524 InitSpriteSets
//   LoadGlobalSprites FUN_00483600, LoadPhaseSprites FUN_004836fc, LoadPhaseSpriteFile FUN_00483340
//   PreloadSprite2 FUN_00465e54 (global set), FUN_004658a8 LoadSettlementSprites,
//   FUN_00465ac8 LoadControlSprites, LoadCombatSprites FUN_00465b9c, FUN_00465df8 LoadPhaseSpritesFor(phase)
//   DAT_00657e60: "type loaded" bit set;  ReadDataFileChunk FUN_0046ca70: raw read used by still pictures.
#pragma once
#include <cstdint>
#include <cstdio>
#include <memory>
#include <span>
#include <string>
#include <vector>

#include "sprites/sprite_tables.h"

namespace dl2::sprites {

// FUN_00465df8 parameter values.
enum class Phase : int { Control = 1, Settlement = 2, Combat = 3 };

struct SpriteFrame {
    const SpriteDef* def = nullptr;   // null when (type, frame) is out of range
    const uint8_t* pixels = nullptr;  // w*h bytes, colour key kColourKeyIndex; null when not loaded
    bool valid() const { return def && pixels; }
};

class SpriteBank {
public:
    SpriteBank();
    ~SpriteBank();
    SpriteBank(const SpriteBank&) = delete;
    SpriteBank& operator=(const SpriteBank&) = delete;

    // Opens <dir>/SPRITENW.DAT (or a full path to the file).
    bool open(const std::string& path, std::string* err = nullptr);
    bool isOpen() const { return file_ != nullptr; }

    // ---- static table access -------------------------------------------------------------------
    static int typeCount() { return kTypeCount; }
    static const SpriteTypeDef* type(int type);
    static int frameCount(int type);
    static const SpriteDef* def(int type, int frame);           // null if out of range
    static uint32_t typePixelBytes(int type);                   // FUN_0048307c
    static int findType(const char* name);                      // by reconstructed name, -1 if unknown
    static const ExtraTableDef* findExtraTable(const char* name);

    // ---- loading (the original loads a whole type at once) ---------------------------------------
    bool isLoaded(int type) const;                              // DAT_00657e60 bit
    bool loadType(int type, std::string* err = nullptr);        // FUN_00483098 on one type
    void unloadType(int type);                                  // FUN_00482fc8
    void unloadAll();                                           // FUN_004835bc
    // LoadPhaseSprites FUN_004836fc: loads every listed type that is not loaded yet and records them
    // as one phase set (FUN_004831ac). Returns false on I/O error (nothing stays loaded then).
    bool loadPhaseSprites(std::span<const uint16_t> types, std::string* err = nullptr);
    bool loadPhaseSprites(std::span<const int> types, std::string* err = nullptr);
    bool popOldestPhaseSet();                                   // FUN_00483538
    void popAllPhaseSets();                                     // FUN_004835a8
    size_t phaseSetCount() const { return phaseSets_.size(); }

    // Phase sets as the original builds them (see docs/SPRITES.md for the derivation):
    bool loadGlobalSprites(std::string* err = nullptr);         // PreloadSprite2 -> LoadGlobalSprites(kGlobalSpriteTypes)
    // FUN_004658a8: combat list A, the terrain tables of the planet type, every building (per-race
    // housing only for the races present) and the unit icon sets of the races present.
    bool loadSettlementSprites(int world, std::span<const int> playerRaces, std::string* err = nullptr);
    // FUN_00465ac8: map icons + unit icons of the races present, plus type 11.
    bool loadControlSprites(std::span<const int> playerRaces, std::string* err = nullptr);
    // LoadCombatSprites: lists A and B plus the caller supplied building/unit types (unitSpriteType()).
    bool loadCombatSprites(std::span<const int> extraTypes, std::string* err = nullptr);
    bool loadPhase(Phase phase, int world, std::span<const int> playerRaces, std::span<const int> extraTypes,
                   std::string* err = nullptr);                 // FUN_00465df8

    // The type lists the phase loaders compute (exposed for tools/tests).
    static std::vector<int> settlementTypes(int world, std::span<const int> playerRaces);
    static std::vector<int> controlTypes(std::span<const int> playerRaces);
    static std::vector<int> combatBaseTypes();
    // Sprite type of a building for a race (housing/city centre/art complex/seahab are per race).
    static int buildingSpriteType(int buildingIndex, int race);
    // Sprite type of a unit in combat (BirthCombatSprites / LoadCombatSprites): race offset for
    // ordinary units, warhead kind (1,2,4,8 -> +3,+1,+2,+0) for missiles (class 9), +7 for the AAV at night.
    static int unitSpriteType(int unitIndex, int race, int warheadKind = 8, bool night = false);

    // ---- frame access ----------------------------------------------------------------------------
    // Loads the type on demand (the original never draws an unloaded type; DrawSprite would report
    // "Null pointer in DrawSprite").
    SpriteFrame frame(int type, int frame, std::string* err = nullptr);
    const uint8_t* pixels(int type, int frame) const;           // null when not loaded

    // ReadDataFileChunk: raw pixels of any SpriteDef (also extra tables). remap applies FUN_00483038.
    bool readPixels(const SpriteDef& d, std::vector<uint8_t>& out, bool remap = true, std::string* err = nullptr);

private:
    struct FileCloser { void operator()(std::FILE* f) const { if (f) std::fclose(f); } };
    struct TypeBlock {
        std::vector<uint8_t> pixels;          // all frames back to back (FUN_00483098 layout)
        std::vector<uint32_t> frameOffset;    // per frame offset into pixels
    };
    bool readAt(uint32_t offset, void* dst, size_t bytes);

    std::unique_ptr<std::FILE, FileCloser> file_;
    std::string path_;
    std::vector<TypeBlock> blocks_;           // kTypeCount entries
    std::vector<uint8_t> loaded_;             // kTypeCount flags (DAT_00657e60)
    std::vector<std::vector<uint16_t>> phaseSets_;   // FUN_004831ac ring (0x800 entries in the original)
    std::vector<uint16_t> globalSet_;         // DAT_004dcf50
};

// FUN_00483038: the loader's pixel remap (0 -> colour key 255, 255 -> 192).
void remapSpritePixels(uint8_t* pixels, size_t count);

}  // namespace dl2::sprites
