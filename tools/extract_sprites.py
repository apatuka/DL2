#!/usr/bin/env python3
"""extract_sprites.py - dump every sprite-definition table of DEADLOCK.EXE (Deadlock II: Shrine Wars v1.20).

Outputs
  data/sprites.json                  all tables, anim scripts, palettes, phase lists (documented below)
  re/sprites/<id>_<name>.png         one contact sheet per table, rendered with the in-game palette
  src/sprites/sprite_tables.h/.cpp   the same data as static C++ arrays (no EXE dependency at runtime)

How the game indexes sprites (from the decompilation, see docs/SPRITES.md):

  SpriteTypeTable @ 0x004D02F4 : 427 records of 12 bytes
      struct SpriteType { SpriteDef* frames; uint16* animScript; uint16 rate; uint16 flags; };
  SpriteDef (16 bytes, table terminated by w == h == 0)
      struct SpriteDef { int16 hotX, hotY; int16 w, h; uint8* pixels /*0 in file*/; uint32 fileOffset; };
  pixel data: w*h bytes, 8 bpp, at fileOffset in SPRITENW.DAT. Value 0 = transparent in the file; the
  loader (FUN_00483038) remaps 0 -> 255 and 255 -> 192 and the CYLib blit uses 255 as colour key.

  A "sprite" is addressed as (type, frame): kSpriteTypes[type].frames[frame]. ANIM objects (FUN_00444f20)
  take a type and run its animScript, which selects frames of that type.

Palette (in-game, 8 bpp): working RGBQUAD[256] at 0x0051A8A4 is assembled at run time from
  master     RGBQUAD[256] @ 0x0051ACA4  (entries 10..245 copied at CreateMainWindow / new game)
  world[7]   RGBQUAD[64]  @ 0x00519ECC  -> entries 16..79, selected by the planet type (DAT_004d5b1c) in FUN_0046338c
  fixed6     RGBQUAD[6]   @ 0x0051A5CC  -> entries 10..15
  fixed112   RGBQUAD[112] @ 0x0051A5E4  -> entries 144..255
  dialog64   RGBQUAD[64]  @ 0x0051A7A4  -> entries 80..143 while a XenoWinG picture window is shown (CreateWinGWindow)
  entries 0..9 and 246..255 = the 20 Windows static colours (GetSystemPaletteEntries in FUN_00463738 / FUN_004637b4)
"""
import json
import os
import struct
import sys

try:
    import pefile
except ImportError:  # pragma: no cover
    sys.exit("pip install pefile")
try:
    from PIL import Image, ImageDraw
except ImportError:  # pragma: no cover
    sys.exit("pip install pillow")

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
GAME_DIR = os.environ.get("DL2_GAME_DIR", r"C:\GOG Games\Deadlock 2")
EXE = os.path.join(GAME_DIR, "DEADLOCK.EXE")
DAT = os.path.join(GAME_DIR, "SPRITENW.DAT")

TYPE_TABLE = 0x004D02F4
TYPE_COUNT = 427
DATA_LO, DATA_HI = 0x4B5000, 0x521C00          # initialised part of the DATA section

SCRIPT_LO, SCRIPT_HI = 0x00518D22, 0x00519ECC  # anim scripts (u16 stream) - ends where the palettes start
MISSILE_SCRIPT = 0x00519CCE                    # script forced by FUN_0043d184 / DestroyAnim for missiles

PAL_MASTER = 0x0051ACA4
PAL_WORLD = 0x00519ECC
PAL_FIXED6 = 0x0051A5CC
PAL_FIXED112 = 0x0051A5E4
PAL_DIALOG64 = 0x0051A7A4
PAL_WORKING_INITIAL = 0x0051A8A4

BUILDING_TABLE, BUILDING_STRIDE, BUILDING_COUNT = 0x004F9DBC, 0x32, 0x31
UNIT_TABLE, UNIT_STRIDE, UNIT_COUNT = 0x004FAF7C, 0x24, 0x26  # name ptr at +0, then the 0x4FAF80 record
RACE_TABLE = 0x004D0918                                       # 8 x {SpriteDef* table; 0; 0x32}

GLOBAL_LIST = (0x004D4DD0, 17)      # PreloadSprite2 -> LoadGlobalSprites
COMBAT_LIST_A = (0x004D4E14, 14)    # LoadCombatSprites + settlement phase
COMBAT_LIST_B = (0x004D4E4C, 6)     # LoadCombatSprites

# Known tables that are not reachable through the type table (address -> name).
EXTRA_TABLES = {
    0x004E2AAC: "WinGPictures",     # CreateWinGWindow(param_5 != 0): still pictures for dialogs
    0x004E2E1C: "WinGPortraits",    # CreateWinGWindow(param_5 == 0): painted by the stub FUN_004256ec
    0x004F625C: "RaceEmblems",      # FUN_0048192c: race emblem on the world map, indexed by race
    0x004E30BC: "Pictures1", 0x004E311C: "Pictures2", 0x004E317C: "Pictures3", 0x004E31DC: "Pictures4",
    0x004E330C: "Pictures5", 0x004EDFDC: "Icons32", 0x004F3EEC: "Pictures6", 0x004F60DC: "Pictures7",
    0x004F613C: "Pictures8", 0x004F64CC: "TinyIcons", 0x004F69DC: "TechPicturesA", 0x004F6AEC: "TechPicturesB",
    0x004F6BFC: "TechPicturesC",
}

RACE_NAMES = ["ChChT", "Cyth", "Human", "Maug", "ReLu", "Tarth", "UvaMosk", "Race7"]  # order of PTR_s_ChCh_t_00509038

WINDOWS_STATIC_COLOURS = [
    (0x00, 0x00, 0x00), (0x80, 0x00, 0x00), (0x00, 0x80, 0x00), (0x80, 0x80, 0x00), (0x00, 0x00, 0x80),
    (0x80, 0x00, 0x80), (0x00, 0x80, 0x80), (0xC0, 0xC0, 0xC0), (0xC0, 0xDC, 0xC0), (0xA6, 0xCA, 0xF0),
    (0xFF, 0xFB, 0xF0), (0xA0, 0xA0, 0xA4), (0x80, 0x80, 0x80), (0xFF, 0x00, 0x00), (0x00, 0xFF, 0x00),
    (0xFF, 0xFF, 0x00), (0x00, 0x00, 0xFF), (0xFF, 0x00, 0xFF), (0x00, 0xFF, 0xFF), (0xFF, 0xFF, 0xFF),
]


class Exe:
    def __init__(self, path):
        self.pe = pefile.PE(path)
        self.base = self.pe.OPTIONAL_HEADER.ImageBase

    def rd(self, va, n):
        return self.pe.get_data(va - self.base, n)

    def u16(self, va):
        return struct.unpack("<H", self.rd(va, 2))[0]

    def i16(self, va):
        return struct.unpack("<h", self.rd(va, 2))[0]

    def u32(self, va):
        return struct.unpack("<I", self.rd(va, 4))[0]

    def cstr(self, va, limit=80):
        out = bytearray()
        while len(out) < limit:
            c = self.rd(va, 1)
            if c == b"\0":
                break
            out += c
            va += 1
        return out.decode("latin-1")


# ----------------------------------------------------------------------------- sprite tables

def read_table(exe, addr, dat_size):
    """SpriteDef records until the w==h==0 terminator."""
    frames = []
    p = addr
    while True:
        hx, hy, w, h, ptr, off = struct.unpack("<hhhhII", exe.rd(p, 16))
        if w == 0 and h == 0:
            break
        if not (0 < w <= 640 and 0 < h <= 480 and off + w * h <= dat_size):
            raise ValueError("bad SpriteDef at %#x" % p)
        frames.append({"hotX": hx, "hotY": hy, "w": w, "h": h, "flags": ptr, "offset": off})
        p += 16
    return frames


def scan_untyped_tables(exe, dat_size, typed_addrs, min_entries=5):
    """Heuristic scan of the DATA section for SpriteDef runs not referenced by the type table."""
    data = exe.rd(DATA_LO, DATA_HI - DATA_LO)

    def ok(i):
        hx, hy, w, h, f, off = struct.unpack_from("<hhhhII", data, i)
        return f == 0 and 0 < w <= 640 and 0 < h <= 480 and off + w * h <= dat_size and -400 <= hx <= 400 and -400 <= hy <= 400

    found = []
    i = 0
    while i + 16 <= len(data):
        if ok(i):
            j, n = i, 0
            while j + 16 <= len(data) and ok(j):
                n += 1
                j += 16
            term = j + 16 <= len(data) and struct.unpack_from("<hhhh", data, j)[2:4] == (0, 0)
            if term and n >= 1 and DATA_LO + i not in typed_addrs and (n >= min_entries or DATA_LO + i in EXTRA_TABLES):
                found.append(DATA_LO + i)
            i = j + 16 if term else i + 4
        else:
            i += 4
    return found


# ----------------------------------------------------------------------------- anim scripts

OPNAMES = {1: "JUMP", 2: "SWITCH", 3: "LOOP", 4: "STEPDOWN", 5: "STEPUP", 6: "SET", 7: "RANDOM", 8: "KILL",
           9: "WAIT", 10: "WAITVAR"}


def disassemble_scripts(exe, entries):
    """Follow the control flow of every script entry point (FUN_00445270 interpreter).

    Returns (ops_by_addr, pointer_positions) where pointer_positions are the addresses of the u32 pointer
    operands (needed to relocate the blob into a position independent u16 array)."""
    ops = {}
    ptr_pos = set()
    work = list(entries)
    seen = set()

    def is_ptr(a):
        return SCRIPT_LO <= exe.u32(a) < SCRIPT_HI

    while work:
        a = work.pop()
        while SCRIPT_LO <= a < SCRIPT_HI and a not in seen:
            seen.add(a)
            op = exe.u16(a)
            if op < 0x8000:
                ops[a] = ("FRAME", op)
                a += 2
                continue
            code = op & 0xFF
            if code == 1:                                   # JUMP ptr
                t = exe.u32(a + 2); ptr_pos.add(a + 2)
                ops[a] = ("JUMP", t); work.append(t); break
            if code == 2:                                   # SWITCH reg, ptr[...]  (table indexed by var[reg])
                reg = exe.i16(a + 2)
                targets = []
                p = a + 4
                while p + 4 <= SCRIPT_HI and is_ptr(p):
                    targets.append(exe.u32(p)); ptr_pos.add(p); p += 4
                ops[a] = ("SWITCH", reg, targets); work.extend(targets); break
            if code == 3:                                   # LOOP reg, ptr : if var[reg] { var[reg]--; goto ptr }
                reg = exe.i16(a + 2); t = exe.u32(a + 4); ptr_pos.add(a + 4)
                ops[a] = ("LOOP", reg, t); work.append(t); a += 8; continue
            if code in (4, 5):                              # STEPDOWN/STEPUP reg, lo, hi, ptr
                reg = exe.i16(a + 2); lo = exe.i16(a + 4); hi = exe.i16(a + 6); t = exe.u32(a + 8); ptr_pos.add(a + 8)
                ops[a] = (OPNAMES[code], reg, lo, hi, t); work.append(t); a += 12; continue
            if code == 6:                                   # SET reg, value
                ops[a] = ("SET", exe.i16(a + 2), exe.i16(a + 4)); a += 6; continue
            if code == 7:                                   # RANDOM reg, lo, hi
                ops[a] = ("RANDOM", exe.i16(a + 2), exe.i16(a + 4), exe.i16(a + 6)); a += 8; continue
            if code == 8:                                   # KILL
                ops[a] = ("KILL",); break
            if code == 9:                                   # WAIT ticks
                ops[a] = ("WAIT", exe.i16(a + 2)); a += 4; continue
            if code == 10:                                  # WAITVAR reg
                ops[a] = ("WAITVAR", exe.i16(a + 2)); a += 4; continue
            ops[a] = ("NOP_%02X" % code,)                    # unknown opcode: the interpreter skips one word
            a += 2
    return ops, ptr_pos


def script_blob(exe, ptr_pos):
    """The script region as u16 words; u32 pointer operands become (word offset, 0xFFFF) pairs."""
    words = list(struct.unpack("<%dH" % ((SCRIPT_HI - SCRIPT_LO) // 2), exe.rd(SCRIPT_LO, SCRIPT_HI - SCRIPT_LO)))
    for p in ptr_pos:
        i = (p - SCRIPT_LO) // 2
        target = exe.u32(p)
        words[i] = (target - SCRIPT_LO) // 2
        words[i + 1] = 0xFFFF
    return words


def format_op(op):
    """Human readable form of one decoded op (pointers as hex, lists in brackets)."""
    ptr_ops = {"JUMP": (1,), "LOOP": (2,), "STEPDOWN": (4,), "STEPUP": (4,)}
    parts = [op[0]]
    for i, v in enumerate(op[1:], 1):
        if isinstance(v, list):
            parts.append("[" + ", ".join("%#x" % t for t in v) + "]")
        elif i in ptr_ops.get(op[0], ()):
            parts.append("%#x" % v)
        else:
            parts.append(str(v))
    return " ".join(parts)


OP_SIZE = {"FRAME": 2, "LOOP": 8, "STEPDOWN": 12, "STEPUP": 12, "SET": 6, "RANDOM": 8, "WAIT": 4, "WAITVAR": 4}


def format_script(ops, start):
    """Linear listing of one script from its entry point up to the first unconditional transfer."""
    lines = []
    a = start
    while a in ops:
        op = ops[a]
        lines.append("%#x: %s" % (a, format_op(op)))
        if op[0] in ("JUMP", "SWITCH", "KILL"):
            break
        a += OP_SIZE.get(op[0], 2)
    return lines


# ----------------------------------------------------------------------------- palettes

def read_quads(exe, addr, n):
    raw = exe.rd(addr, n * 4)
    return [(raw[i * 4 + 2], raw[i * 4 + 1], raw[i * 4]) for i in range(n)]  # RGBQUAD is B,G,R,x


def game_palette(pals, world, dialog=False):
    """The palette the game realises for planet type `world` (0..6). See FUN_0046338c/FUN_004637b4."""
    pal = list(pals["master"])
    pal[10:16] = pals["fixed6"]
    pal[16:80] = pals["world"][world]
    if dialog:
        pal[80:144] = pals["dialog64"]
    pal[144:256] = pals["fixed112"]
    pal[0:10] = WINDOWS_STATIC_COLOURS[:10]
    pal[246:256] = WINDOWS_STATIC_COLOURS[10:]
    return pal


# ----------------------------------------------------------------------------- naming

def build_names(exe, types, race_tables):
    names = {}

    def put(t, name):
        if 0 <= t < TYPE_COUNT and t not in names:
            names[t] = name

    buildings = []
    for i in range(BUILDING_COUNT):
        rec = BUILDING_TABLE + i * BUILDING_STRIDE
        nptr = exe.u32(rec)
        name = exe.cstr(nptr) if 0x400000 < nptr < 0x6C0000 else ""
        stype = exe.i16(rec + 4)
        buildings.append({"index": i, "name": name, "spriteType": stype, "sizeClass": exe.rd(rec + 7, 1)[0],
                          "footprint": exe.rd(rec + 9, 1)[0]})
        if not name or stype == 0:
            continue
        ident = "".join(c for c in name if c.isalnum())
        if i in (1, 2, 3, 0x17, 0x25, 0x27):       # per-race housing variants (FUN_004658a8)
            for r in range(7):
                put(stype + r, "Bldg_%s_%s" % (ident, RACE_NAMES[r]))
        else:
            put(stype, "Bldg_%s" % ident)

    units = []
    for i in range(UNIT_COUNT):
        rec = UNIT_TABLE + i * UNIT_STRIDE
        nptr = exe.u32(rec)
        name = exe.cstr(nptr) if 0x400000 < nptr < 0x6C0000 else ""
        s1, s2 = exe.i16(rec + 4), exe.i16(rec + 6)
        cls = exe.rd(rec + 4 + 7, 1)[0]
        units.append({"index": i, "name": name, "spriteType": s1, "spriteType2": s2, "unitClass": cls})
        if not name:
            continue
        ident = "".join(c for c in name if c.isalnum())
        if s1:
            if cls == 9:                              # missiles: +0 / +1 / +2 / +3 by warhead kind
                for k, suffix in enumerate(("", "_b", "_c", "_d")):
                    put(s1 + k, "Unit_%s%s" % (ident, suffix))
            elif cls == 10:                           # defence buildings used as units: same table as the building
                put(s1, "Unit_%s" % ident)
            elif cls == 0xC:                          # AAV: +7 variant
                for r in range(7):
                    put(s1 + r, "Unit_%s_%s" % (ident, RACE_NAMES[r]))
                put(s1 + 7, "Unit_%s_alt" % ident)
            else:
                for r in range(7):
                    put(s1 + r, "Unit_%s_%s" % (ident, RACE_NAMES[r]))
        if s2:
            put(s2, "Unit_%s_2" % ident)
        # combat "state" sprites: unit + 399 (FUN_004482cc) and unit + 395 (FUN_00448284)
        put(399 + i, "TrooperAlt_%s" % ident)
        put(395 + i, "TrooperAlt2_%s" % ident)

    for w in range(7):
        put(116 + w * 2, "Terrain_w%d_a" % w)
        put(117 + w * 2, "Terrain_w%d_b" % w)
    put(115, "TerrainSpecial")
    for r in range(7):
        put(98 + r, "Colonists_%s" % RACE_NAMES[r])          # FUN_00480be0: type 0x62 + race
    manual = {
        0: "BuildingIcons", 1: "BuildingIconsSmall", 2: "TileOutline", 3: "Cursor", 4: "BonusIcons", 5: "Global5",
        6: "ResourceIcons", 7: "Roads", 8: "EventPictures", 9: "Combat9", 10: "Dots", 11: "ControlIcons",
        12: "SmallIcons", 13: "Icons16", 14: "Icon29x15", 105: "ConstructionSmall", 106: "CraneA", 107: "CraneB",
        108: "ConstructionLarge", 109: "CraneC", 110: "CraneD", 111: "TileOutline78", 112: "TileOutline176",
        113: "CombatTerrain", 114: "CombatTerrainLarge", 115: "TerrainWasteland", 130: "Ambient", 173: "MiscIcons",
        174: "Sparks", 175: "Explosion1", 176: "Explosion2", 177: "Explosion3", 178: "Explosion4", 179: "MissileTrail",
        180: "Explosion6", 181: "Explosion7", 182: "LandMine2", 183: "Smoke",
        404: "ProjectileLaser", 405: "ProjectileFusion", 406: "ProjectileDisruptor", 407: "ProjectileHolocaust",
    }
    for t, n in manual.items():
        names[t] = n
    for r in range(8):
        names[131 + r] = "MapCity_%s" % RACE_NAMES[r]        # tables of PTR_DAT_004d0918 (race emblem at frame 20)
    for r in range(7):
        names[138 + r] = "MapUnits_%s" % RACE_NAMES[r] if r else names.get(138, "MapCity_Race7")
    names[138] = "MapCity_Race7"
    for base, label in ((139, "MapUnits"), (145, "UnitIconsA"), (152, "UnitIconsSea"), (159, "UnitIconsInfantry"), (166, "UnitIconsVehicles")):
        for r in range(7):
            if base == 139 and r == 6:
                break
            names[base + r] = "%s_%s" % (label, RACE_NAMES[r + (1 if base == 139 else 0)])
    for k in range(6):
        names[208 + k] = "Wreck%d" % k
    for t in range(TYPE_COUNT):
        put(t, "Type%d" % t)
    return names, buildings, units


# ----------------------------------------------------------------------------- rendering

def render_sheet(dat, frames, pal, path, label):
    if not frames:
        return
    cols = max(1, min(16, int(len(frames) ** 0.5 + 0.999)))
    cw = max(f["w"] for f in frames) + 4
    ch = max(f["h"] for f in frames) + 14
    rows = (len(frames) + cols - 1) // cols
    img = Image.new("RGB", (cols * cw, rows * ch + 12), (40, 40, 48))
    draw = ImageDraw.Draw(img)
    draw.text((2, 0), label, fill=(255, 255, 0))
    for i, f in enumerate(frames):
        dat.seek(f["offset"])
        px = dat.read(f["w"] * f["h"])
        tile = Image.new("RGB", (f["w"], f["h"]), (40, 40, 48))
        tp = tile.load()
        w = f["w"]
        for y in range(f["h"]):
            row = px[y * w:(y + 1) * w]
            for x, v in enumerate(row):
                if v:
                    tp[x, y] = pal[v]
        cx, cy = (i % cols) * cw + 2, 12 + (i // cols) * ch + 12
        img.paste(tile, (cx, cy))
        draw.text((cx, cy - 11), "%d %dx%d" % (i, f["w"], f["h"]), fill=(200, 200, 200))
    img.save(path)


# ----------------------------------------------------------------------------- C++ generation

def emit_cpp(out_h, out_cpp, types, extras, names, blob, script_entries, pals, lists, buildings, units):
    all_frames = []
    type_recs = []
    for t in types:
        first = len(all_frames)
        all_frames.extend(t["entries"])
        type_recs.append((first, len(t["entries"]), t["scriptOffset"], t["rate"], t["flags"], names[t["id"]]))
    extra_recs = []
    for e in extras:
        first = len(all_frames)
        all_frames.extend(e["entries"])
        extra_recs.append((e["address"], e["name"], first, len(e["entries"])))

    with open(out_h, "w", newline="\n") as h:
        h.write("""// sprite_tables.h - sprite definition tables of DEADLOCK.EXE (generated by tools/extract_sprites.py; do not edit).
// See docs/SPRITES.md for the layout and the addresses in the original executable.
#pragma once
#include <cstddef>
#include <cstdint>

namespace dl2::sprites {

// One frame: w*h 8 bpp pixels at fileOffset in SPRITENW.DAT. hotX/hotY are added to the object position
// when drawing (DrawSprite FUN_00444cf4: screenX = (x >> 8) + hotX).
struct SpriteDef {
    int16_t hotX, hotY;
    int16_t w, h;
    uint32_t fileOffset;
};

// One record of the sprite type table (0x004D02F4, 12 bytes in the EXE).
struct SpriteTypeDef {
    uint16_t firstFrame;   // index into kFrames
    uint16_t frameCount;
    uint16_t script;       // word offset into kAnimScript, kNoScript if none
    uint16_t rate;         // ANIM timer reload (frames between script steps)
    uint16_t flags;        // ANIM flags OR-ed into the object on creation
    const char* name;      // reconstructed name (not in the EXE)
};

// Tables that are not reachable through the type table (dialog pictures, race emblems ...).
struct ExtraTableDef {
    uint32_t address;      // address of the table in the EXE
    const char* name;
    uint16_t firstFrame;
    uint16_t frameCount;
};

struct Rgb8 { uint8_t r, g, b; };

constexpr uint16_t kNoScript = 0xFFFF;
constexpr int kTypeCount = %d;
constexpr int kFrameCount = %d;
constexpr int kExtraTableCount = %d;
constexpr int kAnimScriptWords = %d;
constexpr int kWorldCount = 7;

extern const SpriteDef kFrames[kFrameCount];
extern const SpriteTypeDef kSpriteTypes[kTypeCount];
extern const ExtraTableDef kExtraTables[kExtraTableCount];

// Anim script stream (FUN_00445270 interpreter). Pointer operands were relocated to word offsets:
// a u32 pointer in the EXE is stored as {offset, 0xFFFF}.
extern const uint16_t kAnimScript[kAnimScriptWords];
constexpr uint16_t kMissileScript = %d;    // script forced for missiles (DAT_00519cce)

// Palettes (RGB, converted from the RGBQUAD tables of the EXE).
extern const Rgb8 kPaletteMaster[256];            // 0x0051ACA4
extern const Rgb8 kPaletteWorld[kWorldCount][64];  // 0x00519ECC, entries 16..79 per planet type
extern const Rgb8 kPaletteFixed6[6];              // 0x0051A5CC, entries 10..15
extern const Rgb8 kPaletteFixed112[112];          // 0x0051A5E4, entries 144..255
extern const Rgb8 kPaletteDialog64[64];           // 0x0051A7A4, entries 80..143 for XenoWinG pictures
extern const Rgb8 kWindowsStaticColours[20];      // entries 0..9 and 246..255 on an 8 bpp display

// Sprite type lists used by the loaders.
extern const uint16_t kGlobalSpriteTypes[%d];     // 0x004D4DD0 (PreloadSprite2)
extern const uint16_t kCombatSpriteTypesA[%d];    // 0x004D4E14 (LoadCombatSprites, settlement)
extern const uint16_t kCombatSpriteTypesB[%d];    // 0x004D4E4C (LoadCombatSprites)

// Building / unit tables (sprite type columns only).
struct BuildingSprite { const char* name; int16_t spriteType; uint8_t sizeClass; uint8_t footprint; };
struct UnitSprite { const char* name; int16_t spriteType; int16_t spriteType2; uint8_t unitClass; };
extern const BuildingSprite kBuildings[%d];
extern const UnitSprite kUnits[%d];

}  // namespace dl2::sprites
""" % (len(type_recs), len(all_frames), len(extra_recs), len(blob), (MISSILE_SCRIPT - SCRIPT_LO) // 2,
            len(lists["global"]), len(lists["combatA"]), len(lists["combatB"]), len(buildings), len(units)))

    with open(out_cpp, "w", newline="\n") as c:
        c.write('// sprite_tables.cpp - generated by tools/extract_sprites.py from DEADLOCK.EXE v1.20; do not edit.\n')
        c.write('#include "sprites/sprite_tables.h"\n\nnamespace dl2::sprites {\n\n')
        c.write("const SpriteDef kFrames[kFrameCount] = {\n")
        for f in all_frames:
            c.write("    {%d,%d,%d,%d,%u},\n" % (f["hotX"], f["hotY"], f["w"], f["h"], f["offset"]))
        c.write("};\n\nconst SpriteTypeDef kSpriteTypes[kTypeCount] = {\n")
        for i, (first, n, so, rate, flags, name) in enumerate(type_recs):
            c.write('    {%d,%d,%s,%d,%d,"%s"},  // %d\n' % (first, n, "kNoScript" if so is None else so, rate, flags, name, i))
        c.write("};\n\nconst ExtraTableDef kExtraTables[kExtraTableCount] = {\n")
        for addr, name, first, n in extra_recs:
            c.write('    {0x%08X,"%s",%d,%d},\n' % (addr, name, first, n))
        c.write("};\n\nconst uint16_t kAnimScript[kAnimScriptWords] = {\n")
        for i in range(0, len(blob), 16):
            c.write("    " + ",".join("0x%04X" % w for w in blob[i:i + 16]) + ",\n")
        c.write("};\n\n")

        def pal(name, decl, entries):
            c.write("const Rgb8 %s = {\n" % decl)
            for i in range(0, len(entries), 8):
                c.write("    " + ",".join("{%d,%d,%d}" % e for e in entries[i:i + 8]) + ",\n")
            c.write("};\n\n")

        pal("master", "kPaletteMaster[256]", pals["master"])
        c.write("const Rgb8 kPaletteWorld[kWorldCount][64] = {\n")
        for w in range(7):
            c.write("    {\n")
            for i in range(0, 64, 8):
                c.write("        " + ",".join("{%d,%d,%d}" % e for e in pals["world"][w][i:i + 8]) + ",\n")
            c.write("    },\n")
        c.write("};\n\n")
        pal("fixed6", "kPaletteFixed6[6]", pals["fixed6"])
        pal("fixed112", "kPaletteFixed112[112]", pals["fixed112"])
        pal("dialog64", "kPaletteDialog64[64]", pals["dialog64"])
        pal("win", "kWindowsStaticColours[20]", WINDOWS_STATIC_COLOURS)
        for cname, key in (("kGlobalSpriteTypes", "global"), ("kCombatSpriteTypesA", "combatA"), ("kCombatSpriteTypesB", "combatB")):
            c.write("const uint16_t %s[%d] = {%s};\n" % (cname, len(lists[key]), ",".join(str(v) for v in lists[key])))
        c.write("\nconst BuildingSprite kBuildings[%d] = {\n" % len(buildings))
        for b in buildings:
            c.write('    {"%s",%d,%d,%d},\n' % (b["name"].replace('"', "'"), b["spriteType"], b["sizeClass"], b["footprint"]))
        c.write("};\n\nconst UnitSprite kUnits[%d] = {\n" % len(units))
        for u in units:
            c.write('    {"%s",%d,%d,%d},\n' % (u["name"].replace('"', "'"), u["spriteType"], u["spriteType2"], u["unitClass"]))
        c.write("};\n\n}  // namespace dl2::sprites\n")


# ----------------------------------------------------------------------------- main

def main():
    exe = Exe(EXE)
    dat_size = os.path.getsize(DAT)

    # 1. type table
    types = []
    for i in range(TYPE_COUNT):
        frames_addr, script, rate, flags = struct.unpack("<IIHH", exe.rd(TYPE_TABLE + i * 12, 12))
        types.append({"id": i, "frames": frames_addr, "script": script, "rate": rate, "flags": flags,
                      "entries": read_table(exe, frames_addr, dat_size)})
    typed_addrs = {t["frames"] for t in types}

    # 2. extra tables (known + scanned)
    extras = []
    for addr in sorted(set(EXTRA_TABLES) | set(scan_untyped_tables(exe, dat_size, typed_addrs))):
        extras.append({"address": addr, "name": EXTRA_TABLES.get(addr, "Table_%08X" % addr),
                       "entries": read_table(exe, addr, dat_size)})

    # 3. anim scripts
    entries = sorted({t["script"] for t in types if t["script"]} | {MISSILE_SCRIPT})
    ops, ptr_pos = disassemble_scripts(exe, entries)
    blob = script_blob(exe, ptr_pos)
    for t in types:
        t["scriptOffset"] = (t["script"] - SCRIPT_LO) // 2 if t["script"] else None
    scripts_json = {("%#x" % e): format_script(ops, e) for e in entries}
    # full listing (all reachable code, sorted) for the docs
    listing = ["%#x: %s" % (a, format_op(ops[a])) for a in sorted(ops)]

    # 4. palettes
    pals = {
        "master": read_quads(exe, PAL_MASTER, 256),
        "world": [read_quads(exe, PAL_WORLD + w * 0x100, 64) for w in range(7)],
        "fixed6": read_quads(exe, PAL_FIXED6, 6),
        "fixed112": read_quads(exe, PAL_FIXED112, 112),
        "dialog64": read_quads(exe, PAL_DIALOG64, 64),
        "workingInitial": read_quads(exe, PAL_WORKING_INITIAL, 256),
    }

    # 5. lists and names
    lists = {
        "global": list(struct.unpack("<%dI" % GLOBAL_LIST[1], exe.rd(GLOBAL_LIST[0], GLOBAL_LIST[1] * 4))),
        "combatA": list(struct.unpack("<%dI" % COMBAT_LIST_A[1], exe.rd(COMBAT_LIST_A[0], COMBAT_LIST_A[1] * 4))),
        "combatB": list(struct.unpack("<%dI" % COMBAT_LIST_B[1], exe.rd(COMBAT_LIST_B[0], COMBAT_LIST_B[1] * 4))),
    }
    race_tables = [exe.u32(RACE_TABLE + r * 12) for r in range(8)]
    names, buildings, units = build_names(exe, types, race_tables)

    # 6. JSON
    total_px = sum(f["w"] * f["h"] for t in types for f in t["entries"])
    doc = {
        "source": {"exe": EXE, "typeTable": "%#x" % TYPE_TABLE, "typeCount": TYPE_COUNT, "spriteDat": DAT, "spriteDatSize": dat_size,
                   "typedFrames": sum(len(t["entries"]) for t in types), "typedPixelBytes": total_px},
        "indexing": "sprite = kSpriteTypes[type].frames[frame]; SpriteDef{hotX,hotY,w,h,ptr,fileOffset}; pixels = w*h bytes at fileOffset in SPRITENW.DAT; loader remaps 0->255 (colour key) and 255->192",
        "types": [{"id": t["id"], "name": names[t["id"]], "table": "%#x" % t["frames"], "script": ("%#x" % t["script"]) if t["script"] else None,
                   "scriptWordOffset": t["scriptOffset"], "rate": t["rate"], "flags": t["flags"], "frames": t["entries"]} for t in types],
        "extraTables": [{"name": e["name"], "table": "%#x" % e["address"], "frames": e["entries"]} for e in extras],
        "animScripts": {"region": ["%#x" % SCRIPT_LO, "%#x" % SCRIPT_HI], "entries": scripts_json, "listing": listing,
                        "opcodes": {"<0x8000": "FRAME n: select frame n of the type, end of tick",
                                    "0x8001": "JUMP ptr", "0x8002": "SWITCH reg, ptr[]: goto ptr[var[reg]]",
                                    "0x8003": "LOOP reg, ptr: if var[reg] != 0 { var[reg]--; goto ptr }",
                                    "0x8004": "STEPDOWN reg, lo, hi, ptr: cur = frameIndex; if cur != var[reg] { setFrame(cur == lo ? hi : cur-1); goto ptr }",
                                    "0x8005": "STEPUP reg, lo, hi, ptr: cur = frameIndex; if cur != var[reg] { setFrame(cur == hi ? lo : cur+1); goto ptr }",
                                    "0x8006": "SET reg, value", "0x8007": "RANDOM reg, lo, hi: var[reg] = lo + rand() % (hi-lo+1)",
                                    "0x8008": "KILL: destroy the anim", "0x8009": "WAIT n: timer = n, end of tick",
                                    "0x800a": "WAITVAR reg: if var[reg] > 0 { timer = var[reg]; end of tick }",
                                    "other": "unknown opcode (0x800b appears in the data): skipped, 1 word"}},
        "palettes": {"layout": "0..9 windows static; 10..15 fixed6; 16..79 world[planetType]; 80..143 master (dialog64 inside XenoWinG picture windows); 144..245 fixed112; 246..255 windows static",
                     "master": pals["master"], "world": pals["world"], "fixed6": pals["fixed6"], "fixed112": pals["fixed112"],
                     "dialog64": pals["dialog64"], "workingInitial": pals["workingInitial"], "windowsStatic": WINDOWS_STATIC_COLOURS,
                     "game": [game_palette(pals, w) for w in range(7)]},
        "phaseLists": {"global": lists["global"], "combatA": lists["combatA"], "combatB": lists["combatB"],
                       "settlement": "combatA + world tileset (116+2*world, 117+2*world) + building sprite types (per-race for housing) + 145..172 per race",
                       "control": "131..137, 138..144, 145..172 (per race) + type 11",
                       "combat": "combatA + combatB + building sprites of the battlefield + unit sprites (+race) + 399+unit / 395+unit + 404..407"},
        "buildings": buildings, "units": units, "raceTables": ["%#x" % a for a in race_tables],
    }
    os.makedirs(os.path.join(ROOT, "data"), exist_ok=True)
    with open(os.path.join(ROOT, "data", "sprites.json"), "w") as f:
        json.dump(doc, f, indent=1)

    # 7. C++
    emit_cpp(os.path.join(ROOT, "src", "sprites", "sprite_tables.h"), os.path.join(ROOT, "src", "sprites", "sprite_tables.cpp"),
             types, extras, names, blob, entries, pals, lists, buildings, units)

    # 8. contact sheets
    if "--no-png" not in sys.argv:
        outdir = os.path.join(ROOT, "re", "sprites")
        os.makedirs(outdir, exist_ok=True)
        game_pals = [game_palette(pals, w) for w in range(7)]
        dialog_pal = game_palette(pals, 0, dialog=True)
        with open(DAT, "rb") as dat:
            for t in types:
                world = (t["id"] - 116) // 2 if 116 <= t["id"] <= 129 else 0
                render_sheet(dat, t["entries"], game_pals[world], os.path.join(outdir, "%03d_%s.png" % (t["id"], names[t["id"]])),
                             "type %d %s table=%#x script=%s rate=%d" % (t["id"], names[t["id"]], t["frames"], ("%#x" % t["script"]) if t["script"] else "-", t["rate"]))
            for e in extras:
                render_sheet(dat, e["entries"], dialog_pal if e["address"] in (0x4E2AAC, 0x4E2E1C) else game_pals[0],
                             os.path.join(outdir, "extra_%08X_%s.png" % (e["address"], e["name"])), "%s @ %#x" % (e["name"], e["address"]))
    print("types: %d, frames: %d (%d bytes of pixels), extra tables: %d, scripts: %d, script words: %d" %
          (len(types), sum(len(t["entries"]) for t in types), total_px, len(extras), len(entries), len(blob)))


if __name__ == "__main__":
    main()
