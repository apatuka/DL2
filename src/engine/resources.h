// resources.h - gestor de librerias CYLib (cylib.c): abre paquetes CAM, resuelve recursos por (tag, id) o
// nombre, los cachea con recuento de referencias y aplica un "translator" por tipo (TILE, IMAG, FONT, STRT,
// PALT, SMNU, WAVE) que decodifica el payload la primera vez que se carga.
#pragma once
#include <cstdint>
#include <functional>
#include <memory>
#include <span>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "engine/engine_types.h"
#include "engine/font.h"
#include "engine/imag.h"
#include "engine/palette_table.h"
#include "engine/tile.h"
#include "formats/cam_package.h"
#include "formats/wave.h"

namespace dl2::engine {

// Recurso cargado ("handle" de FUN_00490ab3): entrada de directorio + payload + vistas decodificadas.
struct Resource {
    Tag tag = 0;
    uint32_t id = 0;            // id de busqueda: indice (secciones sin nombre) o los 4 primeros chars del nombre
    std::string name;           // nombre completo de la entrada (20 chars)
    int library = 0;            // indice de libreria + 1
    uint32_t index = 0;         // posicion dentro de la seccion
    std::vector<uint8_t> data;  // payload tal cual
    int refCount = 0;           // referencias tomadas con kResRef

    // Vistas por tipo (rellenadas por el translator):
    ColorTablePtr palette;                   // PALT
    FontPtr font;                            // FONT
    std::vector<std::string> strings;        // STRT
    std::shared_ptr<PcmSound> sound;         // WAVE (RIFF) o SOUND.HDD (PCM crudo)

    TileView tile() const { return TileView(data); }
    ImagView imag() const { return ImagView(data); }
    std::span<const uint32_t> words() const {   // SMNU: lista de u32
        return std::span<const uint32_t>(reinterpret_cast<const uint32_t*>(data.data()), data.size() / 4);
    }
};
using ResPtr = std::shared_ptr<Resource>;

// Flags de FUN_00490ab3: bit31 = tomar referencia (el recurso sigue cargado hasta release()); bit30 = cargar
// con el modo 5 del translator (WAVE en streaming); byte bajo = tipo de memoria (0 GlobalAlloc, 1 nativa, 2 offport).
constexpr uint32_t kResRef = 0x80000000u;
constexpr uint32_t kResStream = 0x40000000u;

// Translator: decodifica/valida un recurso recien leido. Devuelve false para rechazarlo (FUN_00490122).
using Translator = std::function<bool(Resource&)>;

class ResourceManager {
public:
    ResourceManager();

    // FUN_00490bca: abre una libreria (la busca antes por ruta). Devuelve su handle (indice+1) o 0.
    int addLibrary(const std::string& path, std::string* err = nullptr);
    // FUN_00490ce4: cierra la libreria y libera sus recursos.
    void closeLibrary(int lib);
    int libraryCount() const { return int(libs_.size()); }
    const CamPackage* library(int lib) const;
    int findLibrary(std::string_view fileName) const;   // por nombre de archivo (sin ruta), 0 si no esta

    // FUN_00490122: registra un translator para un tag (fn nulo = quitarlo).
    void setTranslator(Tag tag, Translator fn);

    // FUN_00490ab3 modo 0: recurso por id (lib = 0 busca en todas las librerias por orden de apertura).
    ResPtr get(Tag tag, uint32_t id, int lib = 0, uint32_t flags = 0);
    ResPtr get(Tag tag, std::string_view tag4, int lib = 0, uint32_t flags = 0) { return get(tag, makeTag(tag4), lib, flags); }
    // FUN_00490ab3 modo 1: por nombre completo de la entrada.
    ResPtr getByName(Tag tag, std::string_view name, int lib = 0, uint32_t flags = 0);
    // FUN_00490796: suelta una referencia (force = liberar aunque queden referencias).
    void release(const ResPtr& res, bool force = false);
    // Libera todo lo que no tiene referencias.
    void purge();

    // Accesos directos con cache (FUN_00490ab3 + translator correspondiente):
    TileView tile(uint32_t index, int lib = 0);
    TileLookup tileLookup(int lib = 0);
    ResPtr imag(uint32_t id, int lib = 0) { return get(kTagIMAG, id, lib, kResRef); }
    FontPtr font(uint32_t id, int lib = 0);
    ColorTablePtr palette(uint32_t id, int lib = 0);
    // FUN_0049117e: cadena `index` de la tabla STRT `id` (vacia si no existe).
    std::string string(uint32_t strtId, int index, int lib = 0);
    const char* stringPtr(const ResPtr& strt, int index);   // puntero interno (valido mientras viva el recurso)

private:
    struct Lib {
        std::string path;
        std::unique_ptr<CamPackage> cam;
    };
    struct Key {
        Tag tag; uint32_t id; int lib;
        bool operator==(const Key& o) const { return tag == o.tag && id == o.id && lib == o.lib; }
    };
    struct KeyHash {
        size_t operator()(const Key& k) const { return std::hash<uint64_t>()((uint64_t(k.tag) << 32) ^ (uint64_t(k.id) * 0x9e3779b1u) ^ uint64_t(k.lib)); }
    };
    ResPtr load(int libIndex, const CamSection& sec, const CamEntry& e, Tag tag);
    static uint32_t entryId(const CamSection& sec, const CamEntry& e);

    std::vector<Lib> libs_;
    std::unordered_map<Key, ResPtr, KeyHash> cache_;
    std::unordered_map<Tag, Translator> translators_;
};

// Instancia global (el original usa DAT_0051daf8).
ResourceManager& resources();

}  // namespace dl2::engine
