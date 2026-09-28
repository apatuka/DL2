// sprite_bank.cpp - see sprite_bank.h
#include "sprites/sprite_bank.h"

#include <algorithm>
#include <cstring>

#include "formats/binary.h"
#include "sprites/sprite_palette.h"

namespace dl2::sprites {

namespace {

// Building table indices whose sprite type is per race (FUN_004658a8: 1, 2, 3, 0x17, 0x25, 0x27).
constexpr int kPerRaceBuildings[] = {1, 2, 3, 0x17, 0x25, 0x27};
constexpr int kBuildingCount = int(sizeof(kBuildings) / sizeof(kBuildings[0]));
constexpr int kUnitCount = int(sizeof(kUnits) / sizeof(kUnits[0]));

bool isPerRaceBuilding(int b) {
    for (int k : kPerRaceBuildings)
        if (k == b) return true;
    return false;
}

void pushUnique(std::vector<int>& v, int t) {
    if (t < 0 || t >= kTypeCount) return;
    if (std::find(v.begin(), v.end(), t) == v.end()) v.push_back(t);
}

}  // namespace

void remapSpritePixels(uint8_t* pixels, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        if (pixels[i] == 0xFF) pixels[i] = uint8_t(kWhiteRemapIndex);
        else if (pixels[i] == 0) pixels[i] = uint8_t(kColourKeyIndex);
    }
}

SpriteBank::SpriteBank() : blocks_(kTypeCount), loaded_(kTypeCount, 0) {}
SpriteBank::~SpriteBank() = default;

bool SpriteBank::open(const std::string& path, std::string* err) {
    std::string p = path;
    if (!p.empty() && p.back() != '/' && p.back() != '\\') {
        // accept a directory as well as the file itself
        std::FILE* probe = std::fopen(p.c_str(), "rb");
        if (!probe) p += "/SPRITENW.DAT";
        else std::fclose(probe);
    } else {
        p += "SPRITENW.DAT";
    }
    std::FILE* f = std::fopen(p.c_str(), "rb");
    if (!f) return bin::fail(err, "cannot open " + p);
    file_.reset(f);
    path_ = p;
    return true;
}

bool SpriteBank::readAt(uint32_t offset, void* dst, size_t bytes) {
    if (!file_) return false;
    if (std::fseek(file_.get(), long(offset), SEEK_SET) != 0) return false;
    return std::fread(dst, 1, bytes, file_.get()) == bytes;
}

// ---- static table access -------------------------------------------------------------------------

const SpriteTypeDef* SpriteBank::type(int t) {
    if (t < 0 || t >= kTypeCount) return nullptr;
    return &kSpriteTypes[t];
}

int SpriteBank::frameCount(int t) {
    const SpriteTypeDef* td = type(t);
    return td ? td->frameCount : 0;
}

const SpriteDef* SpriteBank::def(int t, int frame) {
    const SpriteTypeDef* td = type(t);
    if (!td || frame < 0 || frame >= td->frameCount) return nullptr;
    return &kFrames[td->firstFrame + frame];
}

uint32_t SpriteBank::typePixelBytes(int t) {   // FUN_0048300c
    const SpriteTypeDef* td = type(t);
    if (!td) return 0;
    uint32_t total = 0;
    for (int i = 0; i < td->frameCount; ++i) {
        const SpriteDef& d = kFrames[td->firstFrame + i];
        total += uint32_t(d.w) * uint32_t(d.h);
    }
    return total;
}

int SpriteBank::findType(const char* name) {
    if (!name) return -1;
    for (int i = 0; i < kTypeCount; ++i)
        if (std::strcmp(kSpriteTypes[i].name, name) == 0) return i;
    return -1;
}

const ExtraTableDef* SpriteBank::findExtraTable(const char* name) {
    if (!name) return nullptr;
    for (int i = 0; i < kExtraTableCount; ++i)
        if (std::strcmp(kExtraTables[i].name, name) == 0) return &kExtraTables[i];
    return nullptr;
}

// ---- loading -------------------------------------------------------------------------------------

bool SpriteBank::isLoaded(int t) const {
    return t >= 0 && t < kTypeCount && loaded_[size_t(t)] != 0;
}

bool SpriteBank::loadType(int t, std::string* err) {   // FUN_00483098 for one table
    const SpriteTypeDef* td = type(t);
    if (!td) return bin::fail(err, "bad sprite type");
    if (loaded_[size_t(t)]) return true;
    if (!file_) return bin::fail(err, "SPRITENW.DAT not open");
    TypeBlock& blk = blocks_[size_t(t)];
    blk.pixels.resize(typePixelBytes(t));
    blk.frameOffset.resize(td->frameCount);
    uint32_t pos = 0;
    for (int i = 0; i < td->frameCount; ++i) {
        const SpriteDef& d = kFrames[td->firstFrame + i];
        const size_t bytes = size_t(d.w) * size_t(d.h);
        blk.frameOffset[size_t(i)] = pos;
        if (!readAt(d.fileOffset, blk.pixels.data() + pos, bytes)) {
            blk.pixels.clear();
            blk.frameOffset.clear();
            return bin::fail(err, "short read in " + path_);
        }
        remapSpritePixels(blk.pixels.data() + pos, bytes);   // FUN_00483038
        pos += uint32_t(bytes);
    }
    loaded_[size_t(t)] = 1;
    return true;
}

void SpriteBank::unloadType(int t) {   // FUN_00482fc8
    if (t < 0 || t >= kTypeCount) return;
    loaded_[size_t(t)] = 0;
    blocks_[size_t(t)].pixels.clear();
    blocks_[size_t(t)].pixels.shrink_to_fit();
    blocks_[size_t(t)].frameOffset.clear();
}

void SpriteBank::unloadAll() {   // FUN_004835bc
    popAllPhaseSets();
    for (uint16_t t : globalSet_) unloadType(t);
    globalSet_.clear();
    for (int t = 0; t < kTypeCount; ++t) unloadType(t);   // memset(DAT_00657e60, 0)
}

bool SpriteBank::loadPhaseSprites(std::span<const uint16_t> types, std::string* err) {   // LoadPhaseSprites
    std::vector<uint16_t> fresh;
    for (uint16_t t : types) {
        if (isLoaded(t)) continue;
        if (!loadType(t, err)) {
            for (uint16_t u : fresh) unloadType(u);   // FUN_00483224 failure path
            return false;
        }
        fresh.push_back(t);
    }
    if (fresh.empty()) return true;   // "if (local_8 == 0) return 1"
    phaseSets_.push_back(std::move(fresh));   // FUN_004831ac
    return true;
}

bool SpriteBank::loadPhaseSprites(std::span<const int> types, std::string* err) {
    std::vector<uint16_t> v;
    v.reserve(types.size());
    for (int t : types)
        if (t >= 0 && t < kTypeCount) v.push_back(uint16_t(t));
    return loadPhaseSprites(std::span<const uint16_t>(v), err);
}

bool SpriteBank::popOldestPhaseSet() {   // FUN_00483538
    if (phaseSets_.empty()) return false;
    for (uint16_t t : phaseSets_.front()) unloadType(t);
    phaseSets_.erase(phaseSets_.begin());
    return true;
}

void SpriteBank::popAllPhaseSets() {   // FUN_004835a8
    while (popOldestPhaseSet()) {}
}

bool SpriteBank::loadGlobalSprites(std::string* err) {   // PreloadSprite2 -> LoadGlobalSprites
    unloadAll();   // FUN_004835bc is the first thing LoadGlobalSprites does
    for (uint16_t t : kGlobalSpriteTypes) {
        if (!loadType(t, err)) {
            for (uint16_t u : globalSet_) unloadType(u);
            globalSet_.clear();
            return false;
        }
        globalSet_.push_back(t);
    }
    return true;
}

int SpriteBank::buildingSpriteType(int b, int race) {
    if (b < 0 || b >= kBuildingCount) return -1;
    const int base = kBuildings[b].spriteType;
    if (base == 0) return -1;
    if (isPerRaceBuilding(b) && race >= 0 && race < 7) return base + race;
    return base;
}

int SpriteBank::unitSpriteType(int u, int race, int warheadKind, bool night) {
    if (u < 0 || u >= kUnitCount) return -1;
    int t = kUnits[u].spriteType;
    if (t == 0) return -1;
    const int cls = kUnits[u].unitClass;
    if (cls == 0xC && night) t += 7;                          // AAV night variant (LoadCombatSprites)
    if (cls == 9) {                                           // missiles: offset by warhead kind
        if (warheadKind == 1) t += 3;
        else if (warheadKind == 2) t += 1;
        else if (warheadKind == 4) t += 2;
    } else if (cls != 10) {                                   // defence buildings share the building table
        if (race >= 0 && race < 7) t += race;
    }
    return t;
}

std::vector<int> SpriteBank::settlementTypes(int world, std::span<const int> playerRaces) {   // FUN_004658a8
    std::vector<int> v;
    if (world < 0 || world >= kWorldTypes) world = 0;
    pushUnique(v, 116 + world * 2);
    pushUnique(v, 117 + world * 2);
    for (uint16_t t : kCombatSpriteTypesA) pushUnique(v, t);
    for (int b = 0; b < kBuildingCount; ++b) {
        if (isPerRaceBuilding(b)) {
            for (int r : playerRaces) pushUnique(v, buildingSpriteType(b, r));
        } else {
            pushUnique(v, buildingSpriteType(b, 0));
        }
    }
    for (int r : playerRaces) {
        if (r < 0 || r >= 7) continue;
        pushUnique(v, 159 + r);   // DAT_0058e1c8
        pushUnique(v, 166 + r);   // DAT_0058e1e4
        pushUnique(v, 145 + r);   // DAT_0058e190
        pushUnique(v, 152 + r);   // DAT_0058e1ac
    }
    std::sort(v.begin(), v.end());   // the original walks the flag array in type order
    return v;
}

std::vector<int> SpriteBank::controlTypes(std::span<const int> playerRaces) {   // FUN_00465ac8
    std::vector<int> v;
    for (int r : playerRaces) {
        if (r < 0 || r >= 7) continue;
        pushUnique(v, 131 + r);   // DAT_0058e158
        pushUnique(v, 138 + r);   // DAT_0058e174
        pushUnique(v, 159 + r);
        pushUnique(v, 166 + r);
        pushUnique(v, 145 + r);
        pushUnique(v, 152 + r);
    }
    pushUnique(v, 11);            // DAT_0058df78
    std::sort(v.begin(), v.end());
    return v;
}

std::vector<int> SpriteBank::combatBaseTypes() {   // LoadCombatSprites, fixed part
    std::vector<int> v;
    for (uint16_t t : kCombatSpriteTypesA) pushUnique(v, t);
    for (uint16_t t : kCombatSpriteTypesB) pushUnique(v, t);
    return v;
}

bool SpriteBank::loadSettlementSprites(int world, std::span<const int> playerRaces, std::string* err) {
    return loadPhaseSprites(std::span<const int>(settlementTypes(world, playerRaces)), err);
}

bool SpriteBank::loadControlSprites(std::span<const int> playerRaces, std::string* err) {
    return loadPhaseSprites(std::span<const int>(controlTypes(playerRaces)), err);
}

bool SpriteBank::loadCombatSprites(std::span<const int> extraTypes, std::string* err) {
    std::vector<int> v = combatBaseTypes();
    for (int t : extraTypes) pushUnique(v, t);
    std::sort(v.begin(), v.end());
    return loadPhaseSprites(std::span<const int>(v), err);
}

bool SpriteBank::loadPhase(Phase phase, int world, std::span<const int> playerRaces, std::span<const int> extraTypes,
                           std::string* err) {   // FUN_00465df8
    switch (phase) {
    case Phase::Control: return loadControlSprites(playerRaces, err);
    case Phase::Settlement: return loadSettlementSprites(world, playerRaces, err);
    case Phase::Combat: return loadCombatSprites(extraTypes, err);
    }
    return false;
}

// ---- frame access --------------------------------------------------------------------------------

const uint8_t* SpriteBank::pixels(int t, int frame) const {
    if (!isLoaded(t)) return nullptr;
    const TypeBlock& blk = blocks_[size_t(t)];
    if (frame < 0 || size_t(frame) >= blk.frameOffset.size()) return nullptr;
    return blk.pixels.data() + blk.frameOffset[size_t(frame)];
}

SpriteFrame SpriteBank::frame(int t, int idx, std::string* err) {
    SpriteFrame f;
    f.def = def(t, idx);
    if (!f.def) return f;
    if (!isLoaded(t) && !loadType(t, err)) return f;
    f.pixels = pixels(t, idx);
    return f;
}

bool SpriteBank::readPixels(const SpriteDef& d, std::vector<uint8_t>& out, bool remap, std::string* err) {
    if (!file_) return bin::fail(err, "SPRITENW.DAT not open");
    const size_t bytes = size_t(d.w) * size_t(d.h);
    out.resize(bytes);
    if (!readAt(d.fileOffset, out.data(), bytes)) return bin::fail(err, "short read in " + path_);
    if (remap) remapSpritePixels(out.data(), bytes);
    return true;
}

}  // namespace dl2::sprites
