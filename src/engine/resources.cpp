// resources.cpp - gestor de librerias CYLib: cache de recursos por (tag,id) con translators por tipo.
#include "engine/resources.h"

#include <algorithm>
#include <cstring>

#include "formats/binary.h"
#include "formats/text_table.h"

namespace dl2::engine {

namespace {

std::string baseName(std::string_view path) {
    const size_t p = path.find_last_of("/\\");
    std::string s(p == std::string_view::npos ? path : path.substr(p + 1));
    for (char& c : s) c = char(std::tolower(uint8_t(c)));
    return s;
}

bool translatePalt(Resource& r) {
    auto pal = std::make_shared<ColorTable>();
    if (!pal->parse(r.data)) return false;
    r.palette = std::move(pal);
    return true;
}

bool translateFont(Resource& r) {
    auto f = std::make_shared<FontView>(std::span<const uint8_t>(r.data));
    if (!f->valid()) return false;
    r.font = std::move(f);
    return true;
}

bool translateStrt(Resource& r) {
    std::string err;
    return decodeStringTable(r.data, r.strings, &err);
}

bool translateWave(Resource& r) {
    auto snd = std::make_shared<PcmSound>();
    std::string err;
    if (decodeRiffWave(r.data, *snd, &err) || decodeRawSound(r.data, *snd, &err)) {
        r.sound = std::move(snd);
        return true;
    }
    return false;
}

bool translateTile(Resource& r) { return TileView(r.data).valid(); }
bool translateImag(Resource& r) { return ImagView(r.data).valid(); }
bool translateSmnu(Resource& r) { return r.data.size() >= 8 && (r.data.size() % 4) == 0; }

}  // namespace

ResourceManager::ResourceManager() {
    // FUN_00490d98 / FUN_00491898 / FUN_0049981f / FUN_00496284: translators registrados por el arranque.
    setTranslator(kTagTILE, translateTile);
    setTranslator(kTagIMAG, translateImag);
    setTranslator(kTagFONT, translateFont);
    setTranslator(kTagPALT, translatePalt);
    setTranslator(kTagSTRT, translateStrt);
    setTranslator(kTagSMNU, translateSmnu);
    setTranslator(kTagWAVE, translateWave);
}

int ResourceManager::addLibrary(const std::string& path, std::string* err) {
    const std::string base = baseName(path);
    for (size_t i = 0; i < libs_.size(); ++i)
        if (baseName(libs_[i].path) == base) return int(i) + 1;
    auto cam = std::make_unique<CamPackage>();
    if (!cam->open(path, err)) return 0;
    libs_.push_back(Lib{path, std::move(cam)});
    return int(libs_.size());
}

void ResourceManager::closeLibrary(int lib) {
    if (lib < 1 || lib > int(libs_.size())) return;
    for (auto it = cache_.begin(); it != cache_.end();) {
        if (it->first.lib == lib) it = cache_.erase(it);
        else ++it;
    }
    libs_[size_t(lib - 1)].cam.reset();
}

const CamPackage* ResourceManager::library(int lib) const {
    if (lib < 1 || lib > int(libs_.size())) return nullptr;
    return libs_[size_t(lib - 1)].cam.get();
}

int ResourceManager::findLibrary(std::string_view fileName) const {
    const std::string base = baseName(fileName);
    for (size_t i = 0; i < libs_.size(); ++i)
        if (libs_[i].cam && baseName(libs_[i].path) == base) return int(i) + 1;
    return 0;
}

void ResourceManager::setTranslator(Tag tag, Translator fn) {
    if (fn) translators_[tag] = std::move(fn);
    else translators_.erase(tag);
}

uint32_t ResourceManager::entryId(const CamSection& sec, const CamEntry& e) {
    if (sec.flags & 1) return e.index;
    return makeTag(e.name);
}

ResPtr ResourceManager::load(int libIndex, const CamSection& sec, const CamEntry& e, Tag tag) {
    auto r = std::make_shared<Resource>();
    r->tag = tag;
    r->id = entryId(sec, e);
    r->name = e.name;
    r->library = libIndex + 1;
    r->index = e.index;
    r->data = libs_[size_t(libIndex)].cam->read(e);
    if (r->data.empty() && e.size != 0) return nullptr;
    auto it = translators_.find(tag);
    if (it != translators_.end() && !it->second(*r)) return nullptr;
    return r;
}

ResPtr ResourceManager::get(Tag tag, uint32_t id, int lib, uint32_t flags) {
    const int first = lib > 0 ? lib - 1 : 0;
    const int last = lib > 0 ? lib - 1 : int(libs_.size()) - 1;
    for (int li = first; li <= last && li < int(libs_.size()); ++li) {
        const Key key{tag, id, li + 1};
        auto cached = cache_.find(key);
        if (cached != cache_.end()) {
            if (flags & kResRef) cached->second->refCount++;
            return cached->second;
        }
        const CamPackage* cam = libs_[size_t(li)].cam.get();
        if (!cam) continue;
        const CamSection* sec = cam->section(tagToString(tag));
        if (!sec) continue;
        const CamEntry* found = nullptr;
        // FUN_004904bf modo 0: secciones sin nombre -> indice; con nombre -> 4 primeros chars como u32.
        if ((id & 0xff000000u) == 0 && (sec->flags & 1)) {
            if (id < sec->entries.size()) found = &sec->entries[id];
        } else {
            for (const CamEntry& e : sec->entries)
                if (entryId(*sec, e) == id) { found = &e; break; }
        }
        if (!found) continue;
        ResPtr r = load(li, *sec, *found, tag);
        if (!r) return nullptr;
        if (flags & kResRef) r->refCount++;
        cache_[key] = r;
        return r;
    }
    return nullptr;
}

ResPtr ResourceManager::getByName(Tag tag, std::string_view name, int lib, uint32_t flags) {
    const int first = lib > 0 ? lib - 1 : 0;
    const int last = lib > 0 ? lib - 1 : int(libs_.size()) - 1;
    for (int li = first; li <= last && li < int(libs_.size()); ++li) {
        const CamPackage* cam = libs_[size_t(li)].cam.get();
        if (!cam) continue;
        const CamSection* sec = cam->section(tagToString(tag));
        if (!sec) continue;
        for (const CamEntry& e : sec->entries) {
            if (e.name != name) continue;
            return get(tag, entryId(*sec, e), li + 1, flags);
        }
    }
    return nullptr;
}

void ResourceManager::release(const ResPtr& res, bool force) {
    if (!res) return;
    if (res->refCount > 0) res->refCount--;
    if (force || res->refCount <= 0) {
        const Key key{res->tag, res->id, res->library};
        auto it = cache_.find(key);
        if (it != cache_.end() && it->second == res) cache_.erase(it);
    }
}

void ResourceManager::purge() {
    for (auto it = cache_.begin(); it != cache_.end();) {
        if (it->second->refCount <= 0 && it->second.use_count() == 1) it = cache_.erase(it);
        else ++it;
    }
}

TileView ResourceManager::tile(uint32_t index, int lib) {
    ResPtr r = get(kTagTILE, index, lib, kResRef);
    return r ? r->tile() : TileView{};
}

TileLookup ResourceManager::tileLookup(int lib) {
    return [this, lib](uint32_t id) { return tile(id, lib); };
}

FontPtr ResourceManager::font(uint32_t id, int lib) {
    ResPtr r = get(kTagFONT, id, lib, kResRef);
    return r ? r->font : nullptr;
}

ColorTablePtr ResourceManager::palette(uint32_t id, int lib) {
    ResPtr r = get(kTagPALT, id, lib, kResRef);
    return r ? r->palette : nullptr;
}

std::string ResourceManager::string(uint32_t strtId, int index, int lib) {
    ResPtr r = get(kTagSTRT, strtId, lib, kResRef);
    const char* s = stringPtr(r, index);
    return s ? std::string(s) : std::string();
}

const char* ResourceManager::stringPtr(const ResPtr& strt, int index) {
    // FUN_0049117e: u32 count; u16 offsets[]; el indice fuera de rango devuelve nulo.
    if (!strt || strt->data.size() < 4) return nullptr;
    const uint32_t count = bin::u32le(strt->data.data());
    if (index < 0 || uint32_t(index) >= count) return nullptr;
    const size_t off = bin::u16le(strt->data.data() + 4 + size_t(index) * 2);
    if (off >= strt->data.size()) return nullptr;
    return reinterpret_cast<const char*>(strt->data.data() + off);
}

ResourceManager& resources() {
    static ResourceManager mgr;
    return mgr;
}

}  // namespace dl2::engine
