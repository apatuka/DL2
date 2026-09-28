// dl2tool.cpp - command-line asset tool: list/extract CAM packages and HDX/HDD archives, PICT to BMP, STRT dump.
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <span>
#include <string>
#include <vector>

#include "formats/binary.h"
#include "formats/cam_package.h"
#include "formats/hdx_archive.h"
#include "formats/iff_pbm.h"
#include "formats/palette.h"
#include "formats/text_table.h"
#include "formats/tile_image.h"
#include "formats/wave.h"
#include "engine/cygame.h"
#include "engine/imag.h"
#include "engine/pixel.h"
#include "engine/resources.h"
#include "engine/smenu.h"
#include "engine/tile.h"
#include "sprites/anim.h"
#include "sprites/sprite_bank.h"
#include "sprites/sprite_draw.h"
#include "sprites/sprite_palette.h"
#include "sprites/sprite_tables.h"

namespace fs = std::filesystem;
using namespace dl2;

namespace {

int usage() {
    std::fputs(
        "usage:\n"
        "  dl2tool cam list <file.cam>\n"
        "  dl2tool cam extract <file.cam> <outdir>\n"
        "  dl2tool hdd list <BASE>            (BASE without .HDX/.HDD extension)\n"
        "  dl2tool hdd extract <BASE> <outdir>\n"
        "  dl2tool pict2bmp <file.cam> <name> <out.bmp>\n"
        "  dl2tool strt <file.cam> <name>\n"
        "  dl2tool tile <file.cam> <index>     (print a TILE header)\n"
        "  dl2tool sprite-list [filter]        (sprite types of SPRITENW.DAT; filter matches the name)\n"
        "  dl2tool render-sprite <table> <index> <out.bmp> [world]   (table = type number/name or extra:<name>)\n"
        "  dl2tool sprite-sheet <table> <out.bmp> [world]\n"
        "  dl2tool anim-demo <type> <ticks> <out.bmp> [world]        (runs the ANIM script of a type)\n"
        "  game data dir: DL2_GAME_DIR (default C:\\GOG Games\\Deadlock 2)\n",
        stderr);
    return 2;
}

std::string hexHead(std::span<const uint8_t> b, size_t n = 8) {
    std::string s;
    char buf[4];
    for (size_t i = 0; i < b.size() && i < n; ++i) {
        std::snprintf(buf, sizeof buf, "%02x", b[i]);
        if (!s.empty()) s += ' ';
        s += buf;
    }
    return s;
}

std::string sanitize(const std::string& name) {
    std::string s = name;
    for (char& c : s)
        if (!(std::isalnum(static_cast<unsigned char>(c)) || c == '_' || c == '-' || c == '.')) c = '_';
    return s.empty() ? "_" : s;
}

bool writeFile(const fs::path& path, const void* data, size_t size) {
    std::FILE* f = std::fopen(path.string().c_str(), "wb");
    if (!f) { std::fprintf(stderr, "cannot write %s\n", path.string().c_str()); return false; }
    const bool ok = size == 0 || std::fwrite(data, 1, size, f) == size;
    std::fclose(f);
    return ok;
}

void put16(std::vector<uint8_t>& v, uint16_t x) { v.push_back(uint8_t(x)); v.push_back(uint8_t(x >> 8)); }
void put32(std::vector<uint8_t>& v, uint32_t x) { put16(v, uint16_t(x)); put16(v, uint16_t(x >> 16)); }

// 24-bit bottom-up BMP from top-down RGB pixels.
bool writeBmp24(const fs::path& path, int w, int h, const std::vector<Rgb>& rgb) {
    const size_t rowBytes = (size_t(w) * 3 + 3) & ~size_t(3);
    const uint32_t imageSize = uint32_t(rowBytes * size_t(h));
    std::vector<uint8_t> out;
    out.reserve(54 + imageSize);
    out.push_back('B'); out.push_back('M');
    put32(out, 54 + imageSize); put32(out, 0); put32(out, 54);
    put32(out, 40); put32(out, uint32_t(w)); put32(out, uint32_t(h)); put16(out, 1); put16(out, 24);
    put32(out, 0); put32(out, imageSize); put32(out, 2835); put32(out, 2835); put32(out, 0); put32(out, 0);
    for (int y = h - 1; y >= 0; --y) {
        const Rgb* row = rgb.data() + size_t(y) * size_t(w);
        for (int x = 0; x < w; ++x) { out.push_back(row[x].b); out.push_back(row[x].g); out.push_back(row[x].r); }
        for (size_t p = size_t(w) * 3; p < rowBytes; ++p) out.push_back(0);
    }
    return writeFile(path, out.data(), out.size());
}

// RIFF WAVE wrapper around decoded PCM.
bool writeWav(const fs::path& path, const PcmSound& s) {
    std::vector<uint8_t> out;
    const uint32_t dataSize = uint32_t(s.data.size());
    out.reserve(44 + dataSize);
    out.insert(out.end(), {'R', 'I', 'F', 'F'}); put32(out, 36 + dataSize); out.insert(out.end(), {'W', 'A', 'V', 'E'});
    out.insert(out.end(), {'f', 'm', 't', ' '}); put32(out, 16);
    put16(out, 1); put16(out, s.format.channels); put32(out, s.format.sampleRate);
    put32(out, uint32_t(s.format.sampleRate * s.format.blockAlign())); put16(out, uint16_t(s.format.blockAlign()));
    put16(out, s.format.bitsPerSample);
    out.insert(out.end(), {'d', 'a', 't', 'a'}); put32(out, dataSize);
    out.insert(out.end(), s.data.begin(), s.data.end());
    return writeFile(path, out.data(), out.size());
}

bool looksLikeRawPcm(std::span<const uint8_t> b) {
    if (b.size() < 20) return false;
    const uint16_t tag = bin::u16le(b.data()), ch = bin::u16le(b.data() + 2), bits = bin::u16le(b.data() + 14);
    const uint32_t rate = bin::u32le(b.data() + 4);
    return tag == 1 && (ch == 1 || ch == 2) && (bits == 8 || bits == 16) && rate >= 4000 && rate <= 96000;
}

bool looksLikeText(std::span<const uint8_t> b) {
    if (b.empty()) return false;
    for (size_t i = 0; i < b.size() && i < 64; ++i) {
        const uint8_t c = b[i];
        if (c == 0 && i == b.size() - 1) break;  // trailing NUL is fine
        if (c < 0x20 && c != '\r' && c != '\n' && c != '\t') return false;
        if (c > 0x7E) return false;
    }
    return true;
}

int camList(const char* file) {
    CamPackage cam;
    std::string err;
    if (!cam.open(file, &err)) { std::fprintf(stderr, "%s\n", err.c_str()); return 1; }
    for (const CamSection& s : cam.sections()) {
        std::printf("[%s] count=%zu flags=%u\n", s.tag.c_str(), s.entries.size(), s.flags);
        for (const CamEntry& e : s.entries) {
            const std::vector<uint8_t> head = cam.readHead(e, 8);
            std::printf("   %-20s off=%10u size=%9u head=%s\n", e.name.c_str(), e.offset, e.size, hexHead(head).c_str());
        }
    }
    return 0;
}

int camExtract(const char* file, const char* outdir) {
    CamPackage cam;
    std::string err;
    if (!cam.open(file, &err)) { std::fprintf(stderr, "%s\n", err.c_str()); return 1; }
    size_t written = 0;
    for (const CamSection& s : cam.sections()) {
        const fs::path dir = fs::path(outdir) / s.tag;
        fs::create_directories(dir);
        for (const CamEntry& e : s.entries) {
            std::vector<uint8_t> blob = cam.read(e, &err);
            if (blob.empty() && e.size) { std::fprintf(stderr, "%s/%s: %s\n", s.tag.c_str(), e.name.c_str(), err.c_str()); continue; }
            const char* ext = ".bin";
            size_t skip = 0;
            if (blob.size() >= 4 && std::memcmp(blob.data(), "RIFF", 4) == 0) ext = ".wav";
            else if (blob.size() >= 8 && std::memcmp(blob.data() + 4, "SMK2", 4) == 0) { ext = ".smk"; skip = 4; }
            const fs::path out = dir / (sanitize(e.name) + ext);
            if (writeFile(out, blob.data() + skip, blob.size() - skip)) ++written;
        }
    }
    std::printf("extracted %zu entries to %s\n", written, outdir);
    return 0;
}

int hddList(const char* base) {
    HdxArchive hdx;
    std::string err;
    if (!hdx.open(base, &err)) { std::fprintf(stderr, "%s\n", err.c_str()); return 1; }
    std::printf("%zu entries in %s\n", hdx.entries().size(), hdx.hddPath().c_str());
    for (const HdxEntry& e : hdx.entries()) {
        const std::vector<uint8_t> blob = hdx.read(e, &err);
        std::printf("   %-9s off=%10u size=%9zu head=%s\n", e.name.c_str(), e.offset, blob.size(), hexHead(blob).c_str());
    }
    return 0;
}

int hddExtract(const char* base, const char* outdir) {
    HdxArchive hdx;
    std::string err;
    if (!hdx.open(base, &err)) { std::fprintf(stderr, "%s\n", err.c_str()); return 1; }
    fs::create_directories(outdir);
    size_t written = 0;
    for (const HdxEntry& e : hdx.entries()) {
        const std::vector<uint8_t> blob = hdx.read(e, &err);
        if (blob.empty()) { std::fprintf(stderr, "%s: %s\n", e.name.c_str(), err.c_str()); continue; }
        const fs::path stem = fs::path(outdir) / sanitize(e.name);
        bool ok;
        if (blob.size() >= 2 && blob[0] == 'B' && blob[1] == 'M') {
            ok = writeFile(stem.string() + ".bmp", blob.data(), blob.size());
        } else if (looksLikeRawPcm(blob)) {
            PcmSound snd;
            ok = decodeRawSound(blob, snd, &err) && writeWav(stem.string() + ".wav", snd);
        } else if (blob.size() > 10 && std::memcmp(blob.data(), "Deadlock 2", 10) == 0) {
            ok = writeFile(stem.string() + ".sav", blob.data(), blob.size());
        } else {
            ok = writeFile(stem.string() + (looksLikeText(blob) ? ".txt" : ".bin"), blob.data(), blob.size());
        }
        if (ok) ++written;
    }
    std::printf("extracted %zu entries to %s\n", written, outdir);
    return 0;
}

int pict2bmp(const char* file, const char* name, const char* outPath) {
    CamPackage cam;
    std::string err;
    if (!cam.open(file, &err)) { std::fprintf(stderr, "%s\n", err.c_str()); return 1; }
    const std::vector<uint8_t> data = cam.read("PICT", name, &err);
    if (data.empty()) { std::fprintf(stderr, "%s\n", err.c_str()); return 1; }

    int w = 0, h = 0;
    std::vector<Rgb> rgb;
    const uint32_t type = pictType(data);
    if (type == uint32_t(PictType::IffPbm)) {
        Image8 img;
        if (!decodePictType2(data, img, &err)) { std::fprintf(stderr, "%s\n", err.c_str()); return 1; }
        Palette pal = img.palette;
        if (!img.hasPalette) {
            if (!decodePalt(cam.read("PALT", "DPAL"), pal, &err)) { std::fprintf(stderr, "no CMAP and no DPAL: %s\n", err.c_str()); return 1; }
            std::printf("note: no CMAP in picture, using PALT/DPAL\n");
        }
        w = img.width; h = img.height;
        rgb.resize(img.pixels.size());
        for (size_t i = 0; i < img.pixels.size(); ++i) rgb[i] = pal.colors[img.pixels[i]];
        std::printf("%s: PICT type 2 (IFF PBM) %dx%d%s\n", name, w, h, img.hasPalette ? " with CMAP" : "");
    } else if (type == uint32_t(PictType::Rgb555)) {
        Image16 img;
        if (!decodePictType1(data, img, &err)) { std::fprintf(stderr, "%s\n", err.c_str()); return 1; }
        w = img.width; h = img.height;
        rgb.resize(img.pixels.size());
        for (size_t i = 0; i < img.pixels.size(); ++i) rgb[i] = rgb555ToRgb(img.pixels[i]);
        std::printf("%s: PICT type 1 (RGB555) %dx%d\n", name, w, h);
    } else {
        std::fprintf(stderr, "%s: unsupported PICT type %u\n", name, type);
        return 1;
    }
    if (!writeBmp24(outPath, w, h, rgb)) return 1;
    std::printf("wrote %s\n", outPath);
    return 0;
}

int strtDump(const char* file, const char* name) {
    CamPackage cam;
    std::string err;
    if (!cam.open(file, &err)) { std::fprintf(stderr, "%s\n", err.c_str()); return 1; }
    std::vector<std::string> strings;
    if (!decodeStringTable(cam.read("STRT", name, &err), strings, &err)) { std::fprintf(stderr, "%s\n", err.c_str()); return 1; }
    for (size_t i = 0; i < strings.size(); ++i) std::printf("%3zu: %s\n", i, strings[i].c_str());
    return 0;
}

int tileInfo(const char* file, const char* indexArg) {
    CamPackage cam;
    std::string err;
    if (!cam.open(file, &err)) { std::fprintf(stderr, "%s\n", err.c_str()); return 1; }
    const size_t index = size_t(std::strtoul(indexArg, nullptr, 10));
    const CamEntry* e = cam.find("TILE", index);
    if (!e) { std::fprintf(stderr, "no TILE #%zu\n", index); return 1; }
    const std::vector<uint8_t> data = cam.read(*e, &err);
    TileHeader th;
    if (!parseTileHeader(data, th)) { std::fprintf(stderr, "TILE #%zu: bad header (%s)\n", index, err.c_str()); return 1; }
    std::printf("TILE #%zu: size=%u type=%u h=%u w=%u pitch=%u flags=0x%x hot=(%d,%d) mode=%u unknown=%04x %04x %04x %04x %04x\n",
                index, e->size, th.type, th.height, th.width, th.pitch, th.flags, th.hotX, th.hotY, th.drawMode,
                th.unknown[0], th.unknown[1], th.unknown[2], th.unknown[3], th.unknown[4]);
    std::printf("   pixel bytes after header: %zu (w*h=%u, pitch*h=%u)\n", data.size() - kTileHeaderSize,
                unsigned(th.width) * th.height, unsigned(th.pitch) * th.height);
    return 0;
}


// ---- sprites (SPRITENW.DAT through the dl2sprites library) ---------------------------------------

std::string gameDir() {
    const char* env = std::getenv("DL2_GAME_DIR");
    return env && *env ? env : "C:\\GOG Games\\Deadlock 2";
}

// Resolves "<number>", "<type name>" or "extra:<name>" to a frame range of the generated tables.
struct TableRef {
    const char* name = "";
    int type = -1;                 // >= 0 for a sprite type
    uint16_t firstFrame = 0, frameCount = 0;
};

bool resolveTable(const char* arg, TableRef& out) {
    using namespace dl2::sprites;
    if (std::strncmp(arg, "extra:", 6) == 0) {
        const ExtraTableDef* e = SpriteBank::findExtraTable(arg + 6);
        if (!e) return false;
        out.name = e->name; out.firstFrame = e->firstFrame; out.frameCount = e->frameCount;
        return true;
    }
    char* end = nullptr;
    const long n = std::strtol(arg, &end, 10);
    const int t = (end && *end == 0) ? int(n) : SpriteBank::findType(arg);
    const SpriteTypeDef* td = SpriteBank::type(t);
    if (!td) return false;
    out.name = td->name; out.type = t; out.firstFrame = td->firstFrame; out.frameCount = td->frameCount;
    return true;
}

Palette spritePalette(int world, const TableRef& ref) {
    const bool dialog = std::strcmp(ref.name, "WinGPictures") == 0 || std::strcmp(ref.name, "WinGPortraits") == 0;
    if (ref.type >= 116 && ref.type <= 129 && world < 0) world = (ref.type - 116) / 2;   // terrain of that planet type
    return dl2::sprites::makeGamePalette(world < 0 ? 0 : world, dialog);
}

bool writeCanvasBmp(const fs::path& path, const std::vector<uint8_t>& canvas, int w, int h, const Palette& pal) {
    std::vector<Rgb> rgb(canvas.size());
    for (size_t i = 0; i < canvas.size(); ++i) rgb[i] = pal.colors[canvas[i]];
    return writeBmp24(path, w, h, rgb);
}

int spriteList(const char* filter) {
    using namespace dl2::sprites;
    for (int t = 0; t < kTypeCount; ++t) {
        const SpriteTypeDef& td = kSpriteTypes[t];
        if (filter && !std::strstr(td.name, filter)) continue;
        const SpriteDef& f0 = kFrames[td.firstFrame];
        std::printf("%3d %-36s frames=%-3d first=%dx%d hot=(%d,%d) script=%d rate=%d flags=%d\n", t, td.name, td.frameCount,
                    f0.w, f0.h, f0.hotX, f0.hotY, td.script == kNoScript ? -1 : int(td.script), td.rate, td.flags);
    }
    for (int i = 0; i < kExtraTableCount; ++i) {
        const ExtraTableDef& e = kExtraTables[i];
        if (filter && !std::strstr(e.name, filter)) continue;
        std::printf("extra:%-30s @%08X frames=%d\n", e.name, e.address, e.frameCount);
    }
    return 0;
}

int renderSprite(const char* table, const char* indexArg, const char* outPath, int world) {
    using namespace dl2::sprites;
    TableRef ref;
    if (!resolveTable(table, ref)) { std::fprintf(stderr, "unknown sprite table %s\n", table); return 1; }
    const int index = int(std::strtol(indexArg, nullptr, 10));
    if (index < 0 || index >= ref.frameCount) { std::fprintf(stderr, "%s has %d frames\n", ref.name, ref.frameCount); return 1; }
    SpriteBank bank;
    std::string err;
    if (!bank.open(gameDir(), &err)) { std::fprintf(stderr, "%s\n", err.c_str()); return 1; }
    const SpriteDef& def = kFrames[ref.firstFrame + index];
    std::vector<uint8_t> pixels;
    if (ref.type >= 0) {
        const SpriteFrame f = bank.frame(ref.type, index, &err);   // loads the whole type, as the game does
        if (!f.valid()) { std::fprintf(stderr, "%s\n", err.c_str()); return 1; }
        pixels.assign(f.pixels, f.pixels + size_t(def.w) * def.h);
    } else if (!bank.readPixels(def, pixels, true, &err)) {
        std::fprintf(stderr, "%s\n", err.c_str()); return 1;
    }
    // Draw through the sprite layer onto an 8 bpp canvas the size of the frame (hotspot cancelled).
    std::vector<uint8_t> canvas(size_t(def.w) * def.h, uint8_t(kColourKeyIndex));
    Surface8 dst{canvas.data(), def.w, def.h, def.w};
    Clipper clip(def.w, def.h);
    drawSpriteDef(dst, clip, def, pixels.data(), -def.hotX, -def.hotY);
    Palette pal = spritePalette(world, ref);
    pal.colors[kColourKeyIndex] = Rgb{255, 0, 255};   // show the colour key as magenta
    if (!writeCanvasBmp(outPath, canvas, def.w, def.h, pal)) return 1;
    std::printf("%s[%d]: %dx%d hot=(%d,%d) offset=%u -> %s\n", ref.name, index, def.w, def.h, def.hotX, def.hotY, def.fileOffset, outPath);
    return 0;
}

int spriteSheet(const char* table, const char* outPath, int world) {
    using namespace dl2::sprites;
    TableRef ref;
    if (!resolveTable(table, ref)) { std::fprintf(stderr, "unknown sprite table %s\n", table); return 1; }
    SpriteBank bank;
    std::string err;
    if (!bank.open(gameDir(), &err)) { std::fprintf(stderr, "%s\n", err.c_str()); return 1; }
    int cellW = 0, cellH = 0;
    for (int i = 0; i < ref.frameCount; ++i) {
        const SpriteDef& d = kFrames[ref.firstFrame + i];
        cellW = std::max(cellW, int(d.w)); cellH = std::max(cellH, int(d.h));
    }
    cellW += 2; cellH += 2;
    int cols = 1;
    while (cols * cols < ref.frameCount) ++cols;
    cols = std::min(std::max(cols, 1), 16);
    const int rows = (ref.frameCount + cols - 1) / cols;
    const int w = cols * cellW, h = std::max(rows, 1) * cellH;
    std::vector<uint8_t> canvas(size_t(w) * h, uint8_t(kColourKeyIndex));
    Surface8 dst{canvas.data(), w, h, w};
    Clipper clip(w, h);
    std::vector<uint8_t> buf;
    for (int i = 0; i < ref.frameCount; ++i) {
        const SpriteDef& d = kFrames[ref.firstFrame + i];
        const int cx = (i % cols) * cellW + 1, cy = (i / cols) * cellH + 1;
        if (ref.type >= 0) {
            drawSprite(dst, clip, bank, ref.type, i, cx - d.hotX, cy - d.hotY);
        } else if (bank.readPixels(d, buf, true, &err)) {
            drawSpriteDef(dst, clip, d, buf.data(), cx - d.hotX, cy - d.hotY);
        }
    }
    Palette pal = spritePalette(world, ref);
    pal.colors[kColourKeyIndex] = Rgb{40, 40, 48};
    if (!writeCanvasBmp(outPath, canvas, w, h, pal)) return 1;
    std::printf("%s: %d frames, %dx%d cells, %dx%d sheet -> %s\n", ref.name, ref.frameCount, cellW, cellH, w, h, outPath);
    return 0;
}

// Creates one ANIM of the type, runs its script for `ticks` updates and draws the frames it went through
// side by side (exercises the interpreter, the z-list and DrawSprite).
int animDemo(const char* table, const char* ticksArg, const char* outPath, int world) {
    using namespace dl2::sprites;
    TableRef ref;
    if (!resolveTable(table, ref) || ref.type < 0) { std::fprintf(stderr, "unknown sprite type %s\n", table); return 1; }
    SpriteBank bank;
    std::string err;
    if (!bank.open(gameDir(), &err)) { std::fprintf(stderr, "%s\n", err.c_str()); return 1; }
    if (!bank.loadType(ref.type, &err)) { std::fprintf(stderr, "%s\n", err.c_str()); return 1; }
    const int ticks = std::max(1, int(std::strtol(ticksArg, nullptr, 10)));
    // Cell = union of every frame's hotspot box, so the object position maps to the same cell point.
    int minX = 0, minY = 0, maxX = 1, maxY = 1;
    for (int i = 0; i < ref.frameCount; ++i) {
        const SpriteDef& d = kFrames[ref.firstFrame + i];
        minX = std::min(minX, int(d.hotX)); minY = std::min(minY, int(d.hotY));
        maxX = std::max(maxX, d.hotX + d.w); maxY = std::max(maxY, d.hotY + d.h);
    }
    const int cellW = maxX - minX + 2, cellH = maxY - minY + 2, cols = 10;
    const int rows = (ticks + cols - 1) / cols;
    const int w = cols * cellW, h = rows * cellH;
    std::vector<uint8_t> canvas(size_t(w) * h, uint8_t(kColourKeyIndex));
    Surface8 dst{canvas.data(), w, h, w};
    Clipper clip(w, h);
    AnimSystem anims;
    anims.random().seed(12345);
    Anim* a = anims.create(ref.type, 1 - minX, 1 - minY);
    if (!a) { std::fprintf(stderr, "cannot create anim\n"); return 1; }
    std::printf("type %d %s: script=%d rate=%d frames=%d\n", ref.type, ref.name, a->pc, a->rate, ref.frameCount);
    for (int t = 0; t < ticks; ++t) {
        anims.update(1);
        if (!anims.isActive(a)) { std::printf("tick %d: killed by script\n", t); break; }
        const int cx = (t % cols) * cellW, cy = (t / cols) * cellH;
        clip.set(cx, cy, cellW, cellH);
        a->setPosition(cx + 1 - minX, cy + 1 - minY);
        anims.resetDrawnList();
        anims.drawAll(dst, clip, bank);
        std::printf("tick %3d: frame %2d pc=%d timer=%d var={%d,%d,%d,%d}\n", t, a->frame, a->pc, a->timer,
                    a->var[0], a->var[1], a->var[2], a->var[3]);
    }
    Palette pal = spritePalette(world, ref);
    pal.colors[kColourKeyIndex] = Rgb{40, 40, 48};
    if (!writeCanvasBmp(outPath, canvas, w, h, pal)) return 1;
    std::printf("wrote %s\n", outPath);
    return 0;
}


// Writes an engine OffPort (8 or 16 bpp) as a 24-bit BMP.
bool writePortBmp(const fs::path& path, const engine::OffPort& port) {
    const std::vector<uint16_t> rgb555 = port.toRgb555();
    std::vector<Rgb> rgb(rgb555.size());
    for (size_t i = 0; i < rgb555.size(); ++i) rgb[i] = rgb555ToRgb(rgb555[i]);
    return writeBmp24(path, port.width(), port.height(), rgb);
}

// Opens the sibling CAM packages of `camPath` (deadcyb + deadtext at least) in the engine resource manager.
bool openEngineLibraries(const char* camPath) {
    const fs::path dir = fs::path(camPath).parent_path();
    std::string err;
    int opened = engine::CyGame::instance().openLibraries(dir.string(), &err);
    if (opened == 0) { std::fprintf(stderr, "no CAM packages found next to %s (%s)\n", camPath, err.c_str()); return false; }
    return true;
}

int renderTile(const char* file, const char* indexArg, const char* outPath) {
    engine::CyGame& game = engine::CyGame::instance();
    if (!openEngineLibraries(file)) return 1;
    const uint32_t index = uint32_t(std::strtoul(indexArg, nullptr, 10));
    const engine::TileView tile = engine::resources().tile(index);
    if (!tile.valid()) { std::fprintf(stderr, "no TILE #%u\n", index); return 1; }
    const int w = tile.width(), h = tile.height();
    game.init(w > 0 ? w : 1, h > 0 ? h : 1, 16);
    game.screen().clear(engine::rgbTo555(255, 0, 255));   // magenta = transparent
    engine::Pixel::setBlitMode(engine::Pixel::blitModeFor(tile.bytesPerPixel() * 8));
    engine::drawTile(tile, tile.hotX(), tile.hotY(), tile.defaultMode());
    engine::ColorTable pal;
    std::printf("TILE #%u: type %u %dx%d pitch %d flags 0x%x hot (%d,%d) mode %d palettes %d%s\n", index, tile.type(), w, h,
                tile.pitch(), tile.flags(), tile.hotX(), tile.hotY(), tile.defaultMode(), tile.paletteCount(),
                tile.palette(0, pal) ? " (own palette)" : "");
    if (!writePortBmp(outPath, game.screen())) return 1;
    std::printf("wrote %s\n", outPath);
    return 0;
}

int smnuDump(const char* file, const char* name) {
    if (!openEngineLibraries(file)) return 1;
    engine::ResPtr res = engine::resources().get(engine::kTagSMNU, engine::makeTag(name));
    if (!res) { std::fprintf(stderr, "no SMNU %s\n", name); return 1; }
    const std::span<const uint32_t> w = res->words();
    std::printf("SMNU %s: %zu words\n", name, w.size());
    size_t i = 0;
    while (i < w.size() && w[i] != 0xffffffffu) {
        std::printf("record %u:", w[i]);
        ++i;
        while (i < w.size() && w[i] != 0xffffffffu) {
            const uint32_t op = w[i++];
            int nargs = 1;
            if (op == 2 || op == 0x2a) nargs = 4;
            else if (op >= 0x22 && op <= 0x25) nargs = int(w[i]) + 1;
            else if (op == 0x17) {
                std::printf(" cells{");
                while (i < w.size() && w[i] != 0x18) {
                    const uint32_t o = w[i++];
                    if (o == 1 || o == 7 || o == 0xc || o == 0xd || o == 0x11 || o == 0x19 || o == 0x1a) std::printf(" %x=%u", o, w[i++]);
                    else std::printf(" %x", o);
                }
                ++i;
                std::printf(" }");
                continue;
            }
            std::printf(" %x=", op);
            for (int a = 0; a < nargs && i < w.size(); ++a, ++i) std::printf("%s%x", a ? "," : "", w[i]);
        }
        ++i;
        std::printf("\n");
    }
    return 0;
}

int renderMenu(const char* file, const char* name, const char* outPath) {
    engine::CyGame& game = engine::CyGame::instance();
    if (!openEngineLibraries(file)) return 1;
    game.init(640, 480, 16);
    std::unique_ptr<engine::SMenu> menu = engine::SMenu::load(engine::makeTag(name));
    if (!menu) { std::fprintf(stderr, "cannot load SMNU %s\n", name); return 1; }
    // Background: the menu palette's entry 0 (black) like a cleared DirectDraw surface.
    game.screen().clear(0);
    if (menu->palette && menu->palette->palette) game.setSystemPalette(menu->palette->palette);
    menu->show();
    menu->draw();
    std::printf("SMNU %s: %d items at (%d,%d) %dx%d, flags 0x%x, font %s, palette %s, strt %s\n", name, int(menu->items().size()),
                menu->x, menu->y, menu->w, menu->h, menu->flags, menu->font ? menu->font->name().c_str() : "-",
                menu->palette ? menu->palette->name.c_str() : "-", menu->strt ? menu->strt->name.c_str() : "-");
    for (const auto& it : menu->items())
        std::printf("   item id %u type %d kind %u at (%d,%d) %dx%d state 0x%x image %u text \"%s\"\n", it->id, it->type,
                    it->graphicKind(), it->x, it->y, it->w, it->h, it->state, it->imageId, it->text.c_str());
    if (!writePortBmp(outPath, game.screen())) return 1;
    std::printf("wrote %s\n", outPath);
    return 0;
}

}  // namespace

int main(int argc, char** argv) {
    if (argc < 3) return usage();
    const std::string cmd = argv[1];
    if (cmd == "cam" && argc >= 4) {
        const std::string sub = argv[2];
        if (sub == "list") return camList(argv[3]);
        if (sub == "extract" && argc >= 5) return camExtract(argv[3], argv[4]);
    } else if (cmd == "hdd" && argc >= 4) {
        const std::string sub = argv[2];
        if (sub == "list") return hddList(argv[3]);
        if (sub == "extract" && argc >= 5) return hddExtract(argv[3], argv[4]);
    } else if (cmd == "pict2bmp" && argc >= 5) {
        return pict2bmp(argv[2], argv[3], argv[4]);
    } else if (cmd == "strt" && argc >= 4) {
        return strtDump(argv[2], argv[3]);
    } else if (cmd == "tile" && argc >= 4) {
        return tileInfo(argv[2], argv[3]);
    } else if (cmd == "render-tile" && argc >= 5) {
        return renderTile(argv[2], argv[3], argv[4]);
    } else if (cmd == "render-menu" && argc >= 5) {
        return renderMenu(argv[2], argv[3], argv[4]);
    } else if (cmd == "smnu" && argc >= 4) {
        return smnuDump(argv[2], argv[3]);
    } else if (cmd == "sprite-list") {
        return spriteList(argc >= 3 ? argv[2] : nullptr);
    } else if (cmd == "render-sprite" && argc >= 5) {
        return renderSprite(argv[2], argv[3], argv[4], argc >= 6 ? std::atoi(argv[5]) : -1);
    } else if (cmd == "sprite-sheet" && argc >= 4) {
        return spriteSheet(argv[2], argv[3], argc >= 5 ? std::atoi(argv[4]) : -1);
    } else if (cmd == "anim-demo" && argc >= 5) {
        return animDemo(argv[2], argv[3], argv[4], argc >= 6 ? std::atoi(argv[5]) : -1);
    }
    return usage();
}
