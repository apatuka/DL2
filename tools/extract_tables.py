#!/usr/bin/env python3
"""extract_tables.py - vuelca las tablas estaticas de DEADLOCK.EXE (Deadlock II v1.20).

Lee el ejecutable con pefile, decodifica cada tabla de la seccion DATA con los campos
identificados en re/decomp (ver docs/DATA_TABLES.md para la evidencia) y genera:

  data/tables.json            todas las tablas con nombres de campo
  src/game/data_tables.h      declaraciones (namespace dl2::data)
  src/game/data_tables.cpp    definiciones de los arrays

Uso:  python tools/extract_tables.py [ruta a DEADLOCK.EXE]
"""
import json
import os
import re
import struct
import sys
from pathlib import Path

import pefile

ROOT = Path(__file__).resolve().parents[1]
EXE_DEFAULT = r"C:\GOG Games\Deadlock 2\DEADLOCK.EXE"
IMAGE_BASE = 0x400000
DATA_LO, DATA_HI = 0x4B5000, 0x6A3000

# ---------------------------------------------------------------------------------------
# Direcciones de las tablas (seccion DATA)
# ---------------------------------------------------------------------------------------
A = dict(
    building_types=0x4F9DBC,        # BuildingTypeDef[48] paso 0x32
    building_costs=0x4FA71C,        # int32[48][11] (FUN_0044de9c)
    unit_types=0x4FAF7C,            # UnitTypeDef[39] paso 0x24
    unit_costs=0x4FB4F8,            # int32[39][11] (FUN_0044ddf4)
    max_units_sea=0x4FAF5C,         # int32[4] (FUN_00445b94, territorio maritimo)
    max_units_land=0x4FAF6C,        # int32[4] (FUN_00445b94, territorio terrestre)
    techs=0x4FBBAC,                 # TechEntry[48] paso 0x32
    race_stats=0x4FC50C,            # int16[64][8]
    race_stats_rows61=0x4FC8DC,     # int16[3][8]
    labor_table=0x4F9BC4,           # int32[11][11] (FUN_0044eb4c)
    event_defs=0x4FC90C,            # EventDef[157] paso 0x12 (FUN_0042278c)
    campaigns=0x4C6194,             # CampaignDef[43] paso 0xd8 (FUN_0044fd14)
    ai_arrivals=0x4DC434,           # AiArrivalDef[] paso 0x9c (FUN_0047c730)
    random_event_handlers=0x4DCAB0, # void(*)[10]
    bonus_materials=0x4DCA4C,       # int32[5]
    spy_mission_risk=0x4DCA60,      # uint16[4]
    scandal_table=0x4DCA68,         # int16[12][3] (FUN_0047d49c)
    path_delta1=0x4DCBD8,           # int16[4]
    path_delta2=0x4DCBE0,           # int16[4]
    tile_move_cost=0x4DCBE8,        # int32[7] (FUN_0047dd58)
    tax_rates=0x4D57EC,             # int32[6]
    terrain_max_pop=0x4D5820,       # int32[6] (FUN_0046bdfc)
    pop_growth=0x4D583C,            # int32[5] (FUN_0046b1ac)
    morale_by_level=0x4D5850,       # int32[8] (FUN_0046bdfc)
    map_sizes=0x4D5144,             # uint16[4]
    terrain_pct=0x4D514C,           # uint16[5][6]
    win_cities=0x4C425C,            # int32[5]
    win_shrines=0x4C4274,           # int32[3]
    win_turns=0x4C4280,             # int32[3]
    black_market=0x4C42F8,          # BlackMarketOffer[25] paso 0xe
    ai_type_table=0x4B502C,         # 6 dwords por tipo de jugador (solo tipo 3 valido)
    minister_vtable=0x4B508C,       # {id, fn[4]}[6]
    minister_order=0x4B5104,        # int32[6]
    minister_config=0x4B62F4,       # {kind, param}[6]
    # tablas de cadenas
    race_names=0x509038, terrain_names=0x509054, material_names=0x50906C,
    material_names_lower=0x509098, task_names=0x509178, unit_speed_names=0x509A64,
    rof_names=0x509A84, ai_leader_names=0x509938, race_short_names=0x5099CF,
    tf_goal_names=0x4B6BD4, tf_status_names=0x4B6C7C, minister_job_names=0x4B5FE8,
    minister_names=0x4B5FD0, ini_keys=0x4D5F60, ini_values=0x4D6010,
    ini_map_size_names=0x4D6030, ini_world_type_names=0x4D6044, ini_role_names=0x4D6060,
)

N_BUILDINGS, N_UNITS, N_TECHS, N_MATERIALS = 48, 39, 48, 11
N_EVENTS = 156             # FUN_0042278c itera hasta 0x9d, pero la entrada 156 ya es la cadena "No Building"
N_CAMPAIGNS = 43           # CampaignNumDialog: 1..42 (0 = sin campana)
N_BLACK_MARKET = 25

# nombres del enum BuildingTask+2 (indice de la tabla 0x509178)
TASK_UNLOCK_TECH = {4: 20, 6: 4, 9: 2, 10: 29, 0x10: 22}   # GetBuildingTasks

# Efectos de tecnologias codificados en el juego (no en tablas), con la funcion que los lee.
TECH_CODE_EFFECTS = {
    2:  "Iron -> Steel task (GetBuildingTasks)",
    4:  "Electronic Parts task (GetBuildingTasks)",
    12: "+1 alcance aereo para la IA (FUN_0040f794)",
    20: "Mine Endurium task (GetBuildingTasks)",
    22: "Anti-Matter Pods task (GetBuildingTasks)",
    27: "ROF -10% y velocidad -25% (mas rapido) en combate (FUN_00448008, FUN_00447f44)",
    29: "End. -> Tri. task (GetBuildingTasks)",
    33: "produccion de shrines x2 (FUN_0044eb4c, categoria 0xb)",
    46: "+1 punto de movimiento a todas las unidades (FUN_00447190)",
    47: "fondo alternativo del arbol tecnologico (FUN_0043c540)",
}


# Nombres de los tipos de RandomEvent (indice en PTR_FUN_004dcab0), por el evento de log que generan
RANDOM_EVENT_NAMES = ['None', 'Plague', 'Earthquake', 'Crop Disease', 'Ion Storm', 'No Bonus', 'Flood',
                      'Happy Colonists', 'Bonus', 'Natives']


class Exe:
    def __init__(self, path):
        self.pe = pefile.PE(path)
        self.base = self.pe.OPTIONAL_HEADER.ImageBase
        assert self.base == IMAGE_BASE, hex(self.base)

    def rd(self, va, n):
        return self.pe.get_data(va - self.base, n)

    def u8(self, va): return self.rd(va, 1)[0]
    def s8(self, va): return struct.unpack('<b', self.rd(va, 1))[0]
    def u16(self, va): return struct.unpack('<H', self.rd(va, 2))[0]
    def s16(self, va): return struct.unpack('<h', self.rd(va, 2))[0]
    def u32(self, va): return struct.unpack('<I', self.rd(va, 4))[0]
    def s32(self, va): return struct.unpack('<i', self.rd(va, 4))[0]

    def cstr(self, va, maxlen=1024):
        d = self.rd(va, maxlen)
        return d.split(b'\0')[0].decode('latin1')

    def ptr_str(self, va):
        p = self.u32(va)
        if DATA_LO <= p < DATA_HI:
            return self.cstr(p)
        return None

    def str_table(self, va, n):
        return [self.ptr_str(va + 4 * i) for i in range(n)]

    def arr(self, va, fmt, n):
        sz = struct.calcsize('<' + fmt)
        return [struct.unpack('<' + fmt, self.rd(va + i * sz, sz))[0] for i in range(n)]


def decomp_names():
    """addr -> nombre de funcion segun re/decomp/<addr>_<name>.c"""
    names = {}
    d = ROOT / 're' / 'decomp'
    if d.is_dir():
        for f in os.listdir(d):
            m = re.match(r'([0-9a-f]{8})_(.+)\.c$', f)
            if m:
                names[int(m.group(1), 16)] = m.group(2)
    return names


# ---------------------------------------------------------------------------------------
# Decodificadores
# ---------------------------------------------------------------------------------------
def building_types(x):
    rows = []
    for i in range(N_BUILDINGS):
        b = A['building_types'] + i * 0x32
        c = A['building_costs'] + i * 0x2C
        rows.append(dict(
            index=i,
            name=x.ptr_str(b),
            sprite=x.u16(b + 0x04),
            icon=x.u8(b + 0x06),
            category=x.u8(b + 0x07),
            maxLabor=x.u8(b + 0x08),
            size=x.u8(b + 0x09),
            buildLabor=x.u16(b + 0x0A),
            energyUse=x.u16(b + 0x0C),
            taskRate=x.arr(b + 0x0E, 'h', 5),
            tasks=list(x.rd(b + 0x18, 5)),
            units=list(x.rd(b + 0x1D, 10)),
            techRequired=x.u8(b + 0x27),
            hitPoints=x.u8(b + 0x28),
            unk_29=x.u8(b + 0x29),
            productionQueue=x.s32(b + 0x2A),
            dialogAnim=x.s32(b + 0x2E),
            cost=x.arr(c, 'i', N_MATERIALS),
        ))
    return rows


def unit_types(x):
    rows = []
    for i in range(N_UNITS):
        u = A['unit_types'] + i * 0x24
        c = A['unit_costs'] + i * 0x2C
        rows.append(dict(
            index=i,
            name=x.ptr_str(u),
            combatSprite=x.u16(u + 0x04),
            moveAnim=x.u16(u + 0x06),
            portraitGroup=x.u16(u + 0x08),
            portraitIndex=x.s8(u + 0x0A),
            unitClass=x.u8(u + 0x0B),
            buildLabor=x.u16(u + 0x0C),
            upkeep=x.s8(u + 0x0E),
            techRequired=x.s8(u + 0x0F),
            moves=x.s8(u + 0x10),
            domain=x.s8(u + 0x11),
            unk_12=x.s8(u + 0x12),
            attack=x.s8(u + 0x13),
            defense=x.s8(u + 0x14),
            speed=x.s8(u + 0x15),
            rateOfFire=x.s8(u + 0x16),
            range=x.s8(u + 0x17),
            sound=x.s32(u + 0x18),
            unk_1c=list(x.rd(u + 0x1C, 8)),
            cost=x.arr(c, 'i', N_MATERIALS),
        ))
    return rows


def techs(x):
    rows = []
    for i in range(N_TECHS):
        t = A['techs'] + i * 0x32
        rows.append(dict(
            index=i,
            name=x.ptr_str(t + 0x14),
            treeItemId=x.u32(t + 0x18),
            descPtr=x.ptr_str(t + 0x1C),
            level=x.u16(t + 0x20),
            cost=x.u16(t + 0x22),
            prereq=x.arr(t + 0x24, 'H', 3),
            unk_2a=x.u16(t + 0x2A),
            treeIcon=x.s16(t + 0x2C),
            treeY=x.u16(t + 0x2E),
            treeX=x.u16(t + 0x30),
        ))
    return rows


def event_defs(x):
    rows = []
    for i in range(N_EVENTS):
        e = A['event_defs'] + i * 0x12
        rows.append(dict(
            index=i,
            priority=x.s16(e + 0x00),
            zero=x.u32(e + 0x02),
            id=x.s16(e + 0x06),
            category=x.s16(e + 0x08),
            unk_0a=x.s16(e + 0x0A),
            portrait=x.s16(e + 0x0C),
            format=x.ptr_str(e + 0x0E),
        ))
    return rows


def campaigns(x):
    rows = []
    for c in range(N_CAMPAIGNS):
        b = A['campaigns'] + c * 0xD8
        goals = []
        for k in range(3):
            g = b + 0x0C + k * 0x44
            goals.append(dict(
                type=x.s32(g), turns=x.s32(g + 4), count=x.s32(g + 8),
                list=x.arr(g + 0x0C, 'i', 13), state=x.s32(g + 0x40)))
        rows.append(dict(index=c, victory=x.u8(b), param1=x.s32(b + 4), param2=x.s32(b + 8),
                         goals=goals))
    return rows


def ai_arrivals(x):
    rows = []
    for i in range(16):
        b = A['ai_arrivals'] + i * 0x9C
        v = x.arr(b, 'i', 39)
        race, tech, credits = v[0], v[5], v[6]
        if not (0 <= race <= 6 and 0 <= tech <= 8 and credits == 20000):
            break
        rows.append(dict(
            index=i, race=race, sites=v[1:5], techLevel=tech, credits=credits,
            materials=v[7:17], units=[[v[17 + 2 * j], v[18 + 2 * j]] for j in range(10)],
            allyRace=v[37], allyPact=v[38]))
    return rows


def black_market(x):
    rows = []
    for i in range(N_BLACK_MARKET):
        b = A['black_market'] + i * 0x0E
        rows.append(dict(index=i, unitType=x.s32(b), experience=x.s16(b + 4),
                         price=x.s32(b + 6), minTurn=x.s32(b + 0x0A)))
    return rows


def scandal_table(x):
    return [dict(moraleLoss=x.s16(A['scandal_table'] + i * 6),
                 globalMoraleLoss=x.s16(A['scandal_table'] + i * 6 + 2),
                 riotChance=x.s16(A['scandal_table'] + i * 6 + 4)) for i in range(12)]


def extract(x):
    names = decomp_names()

    def fn(addr):
        if not (0x401000 <= addr < 0x4B5000):
            return dict(addr=addr, name='DAT_%08x' % addr)
        return dict(addr=addr, name=names.get(addr, 'FUN_%08x' % addr))

    t = {}
    t['building_types'] = building_types(x)
    t['unit_types'] = unit_types(x)
    t['techs'] = techs(x)
    t['race_stats_default'] = [x.arr(A['race_stats'] + r * 16, 'h', 8) for r in range(64)]
    t['race_stats_rows61'] = [x.arr(A['race_stats_rows61'] + r * 16, 'h', 8) for r in range(3)]
    t['labor_table'] = [x.arr(A['labor_table'] + r * 0x2C, 'i', 11) for r in range(11)]
    t['max_units_sea'] = x.arr(A['max_units_sea'], 'i', 4)
    t['max_units_land'] = x.arr(A['max_units_land'], 'i', 4)
    t['event_defs'] = event_defs(x)
    t['campaigns'] = campaigns(x)
    t['ai_arrivals'] = ai_arrivals(x)
    t['random_event_handlers'] = [fn(x.u32(A['random_event_handlers'] + 4 * i)) for i in range(10)]
    t['bonus_materials'] = x.arr(A['bonus_materials'], 'i', 5)
    t['spy_mission_risk'] = x.arr(A['spy_mission_risk'], 'H', 4)
    t['scandal_table'] = scandal_table(x)
    t['path_delta1'] = x.arr(A['path_delta1'], 'h', 4)
    t['path_delta2'] = x.arr(A['path_delta2'], 'h', 4)
    t['tile_move_cost'] = x.arr(A['tile_move_cost'], 'i', 7)
    t['tax_rates'] = x.arr(A['tax_rates'], 'i', 6)
    t['terrain_max_pop'] = x.arr(A['terrain_max_pop'], 'i', 6)
    t['pop_growth'] = x.arr(A['pop_growth'], 'i', 5)
    t['morale_by_level'] = x.arr(A['morale_by_level'], 'i', 8)
    t['map_sizes'] = x.arr(A['map_sizes'], 'H', 4)
    t['terrain_pct'] = [x.arr(A['terrain_pct'] + r * 12, 'H', 6) for r in range(5)]
    t['win_cities'] = x.arr(A['win_cities'], 'i', 5)
    t['win_shrines'] = x.arr(A['win_shrines'], 'i', 3)
    t['win_turns'] = x.arr(A['win_turns'], 'i', 3)
    t['black_market'] = black_market(x)
    row3 = A['ai_type_table'] + 3 * 0x18
    t['ai_type3'] = dict(name=x.ptr_str(row3), fn=[fn(x.u32(row3 + 4 * i)) for i in range(1, 6)])
    t['random_event_names'] = RANDOM_EVENT_NAMES
    t['minister_vtable'] = [dict(id=x.s32(A['minister_vtable'] + i * 0x14),
                                 fn=[fn(x.u32(A['minister_vtable'] + i * 0x14 + 4 + 4 * j))
                                     for j in range(4)]) for i in range(6)]
    t['minister_order'] = x.arr(A['minister_order'], 'i', 6)
    t['minister_config'] = [dict(kind=x.s32(A['minister_config'] + 8 * i),
                                 param=x.s32(A['minister_config'] + 8 * i + 4)) for i in range(6)]
    # cadenas
    t['race_names'] = x.str_table(A['race_names'], 7)
    t['terrain_names'] = x.str_table(A['terrain_names'], 6)
    t['material_names'] = x.str_table(A['material_names'], 11)
    t['material_names_lower'] = x.str_table(A['material_names_lower'], 11)
    t['task_names'] = x.str_table(A['task_names'], 24)
    t['unit_speed_names'] = x.str_table(A['unit_speed_names'], 9)
    t['rof_names'] = x.str_table(A['rof_names'], 10)
    t['ai_leader_names'] = x.str_table(A['ai_leader_names'], 7)
    t['race_short_names'] = [x.cstr(A['race_short_names'] + 6 * i) for i in range(7)]
    t['tf_goal_names'] = x.str_table(A['tf_goal_names'], 21)
    t['tf_status_names'] = x.str_table(A['tf_status_names'], 6)
    t['minister_job_names'] = x.str_table(A['minister_job_names'], 14)
    t['minister_names'] = x.str_table(A['minister_names'], 6)
    t['ini_keys'] = x.str_table(A['ini_keys'], 44)
    t['ini_values'] = x.str_table(A['ini_values'], 8)
    t['ini_map_size_names'] = x.str_table(A['ini_map_size_names'], 5)
    t['ini_world_type_names'] = x.str_table(A['ini_world_type_names'], 7)
    t['ini_role_names'] = x.str_table(A['ini_role_names'], 2)

    # derivados: que desbloquea cada tecnologia
    for tech in t['techs']:
        i = tech['index']
        tech['unlocksBuildings'] = [b['index'] for b in t['building_types'] if b['techRequired'] == i and i]
        tech['unlocksUnits'] = [u['index'] for u in t['unit_types'] if u['techRequired'] == i and i]
        tech['unlocksTasks'] = [task for task, tt in TASK_UNLOCK_TECH.items() if tt == i]
        tech['codeEffects'] = TECH_CODE_EFFECTS.get(i, '')
    return t


# ---------------------------------------------------------------------------------------
# Comprobaciones
# ---------------------------------------------------------------------------------------
def validate(t):
    b = {r['name']: r for r in t['building_types']}
    u = {r['name']: r for r in t['unit_types']}
    k = {r['name']: r for r in t['techs']}
    rof = t['rof_names']
    checks = [
        ("Turbo Wing Fighter moves == 2 (README 'range 2')", u['Turbo Wing Fighter']['moves'] == 2),
        ("Starflare Bomber moves == 2 (README)", u['Starflare Bomber']['moves'] == 2),
        ("Air Command moves == 3 (README)", u['Air Command']['moves'] == 3),
        ("Supernova Spyjet moves == 3 (README 'reduced to 3')", u['Supernova Spyjet']['moves'] == 3),
        ("Flak Ship ROF muestra '33' (README)", rof[u['Flak Ship']['rateOfFire'] + 1] == '33'),
        ("Flak Launcher ROF muestra '33' (README)", rof[u['Flak Launcher']['rateOfFire'] + 1] == '33'),
        ("Anti Matter Defense ROF muestra '25' (README)", rof[u['Anti Matter Defense']['rateOfFire'] + 1] == '25'),
        ("TW Fighter ROF muestra '40' (README)", rof[u['Turbo Wing Fighter']['rateOfFire'] + 1] == '40'),
        ("Starflare Bomber ROF muestra '40' (README)", rof[u['Starflare Bomber']['rateOfFire'] + 1] == '40'),
        ("Air Command ROF muestra '40' (README)", rof[u['Air Command']['rateOfFire'] + 1] == '40'),
        ("Laser Cannon upkeep 1, Fusion Cannon 2 (README ejemplo)", u['Laser Cannon']['upkeep'] == 1 and u['Fusion Cannon']['upkeep'] == 2),
        ("Command Corps y Medic upkeep 1 (README ejemplo)", u['Command Corps']['upkeep'] == 1 and u['Medic']['upkeep'] == 1),
        ("SAM Trooper requiere Surface to Air Missiles", u['SAM Trooper']['techRequired'] == k['Surface to Air Missiles']['index']),
        ("Flak Launcher (edificio y unidad) requiere Flak", b['Flak Launcher']['techRequired'] == k['Flak']['index'] and u['Flak Launcher']['techRequired'] == k['Flak']['index']),
        ("Cloning Center requiere Cloning", b['Cloning Center']['techRequired'] == k['Cloning']['index']),
        ("Fuel Depot requiere Neutrionic Fuel", b['Fuel Depot']['techRequired'] == k['Neutrionic Fuel']['index']),
        ("Factory construye Laser Squad..Holocaust Cannon (1..8)", b['Factory']['units'][:8] == list(range(1, 9))),
        ("Airport construye TW Fighter, Starflare, Spyjet, Air Command", b['Airport']['units'][:4] == [9, 10, 11, 28]),
        ("Missile Base construye las 3 cabezas nucleares", b['Missile Base']['units'][:3] == [16, 17, 18]),
        ("Farm: tareas Food(12) y Wood(13) -> nombres", [t['task_names'][x] for x in b['Farm']['tasks'][1:3]] == ['Food', 'Wood']),
        ("Housing: tarea House Populace", t['task_names'][b['Housing']['tasks'][1]] == 'House Populace'),
        ("Cola de produccion: Factory 1, Shipyard 2, Airport 3, Missile Base 4, City Center 5",
         [b[n]['productionQueue'] for n in ('Factory', 'Shipyard', 'Airport', 'Missile Base', 'City Center')] == [1, 2, 3, 4, 5]),
        ("Fila 24 de RaceStats: ChCh't 200% poblacion", t['race_stats_default'][24][0] == 200),
        ("Fila 61: Cyth mantenimiento 50%", t['race_stats_default'][61][1] == 50),
        ("Opciones Win Cities {2,3,5,7,10}", t['win_cities'] == [2, 3, 5, 7, 10]),
        ("Todas las campanas tienen victoria 0..2", all(c['victory'] <= 2 for c in t['campaigns'])),
        ("156 eventos con id unico y formato valido", len({e['id'] for e in t['event_defs']}) == N_EVENTS and all(e['format'] for e in t['event_defs'])),
        ("Personalidad IA tipo 3 = Machiavelli", t['ai_type3']['name'] == 'Machiavelli'),
        ("Manejadores de eventos aleatorios en CODE", all(0x401000 <= h['addr'] < 0x4B5000 for h in t['random_event_handlers'])),
    ]
    ok = True
    for msg, res in checks:
        print(('  OK   ' if res else '  FAIL ') + msg)
        ok &= bool(res)
    return ok


# ---------------------------------------------------------------------------------------
# Generacion C++
# ---------------------------------------------------------------------------------------
def cstr(s):
    if s is None:
        return 'nullptr'
    out = ''
    for ch in s:
        if ch == '"':
            out += '\\"'
        elif ch == '\\':
            out += '\\\\'
        elif ch == '\n':
            out += '\\n'
        elif ch == '\t':
            out += '\\t'
        elif 32 <= ord(ch) < 127:
            out += ch
        else:
            out += '\\x%02x" "' % (ord(ch) & 0xFF)
    return '"' + out + '"'


def ilist(v):
    return '{' + ', '.join(str(i) for i in v) + '}'


def gen_header(t):
    n_arr = len(t['ai_arrivals'])
    return f'''// data_tables.h - Tablas estaticas de DEADLOCK.EXE (Deadlock II: Shrine Wars v1.20)
//
// GENERADO por tools/extract_tables.py a partir del ejecutable original; no editar a mano.
// Cada tabla lleva la direccion original en la seccion DATA y las funciones que la leen
// (evidencia completa en docs/DATA_TABLES.md).  Los indices coinciden con los enums de
// game_state.h (BuildingType, UnitType, TechId, Race, Terrain, Material).
#pragma once
#include <cstddef>
#include <cstdint>

namespace dl2::data {{

constexpr int kNumBuildingTypes = {N_BUILDINGS};
constexpr int kNumUnitTypes     = {N_UNITS};
constexpr int kNumTechs         = {N_TECHS};
constexpr int kNumMaterials     = {N_MATERIALS};
constexpr int kNumRaces         = 7;
constexpr int kNumRaceStatRows  = 64;
constexpr int kNumEventDefs     = {N_EVENTS};
constexpr int kNumCampaigns     = {N_CAMPAIGNS};
constexpr int kNumAiArrivals    = {n_arr};
constexpr int kNumBlackMarket   = {N_BLACK_MARKET};

// Los ids de tarea que usa el juego (BuildingTypeDef::tasks, Building::task[]) indexan la
// tabla de cadenas 0x509178: 0 = " " (ninguna), 1 = "Unassigned", 2 = "Construction", ...
// es decir, id = BuildingTask(enum de game_state.h) + kTaskIdBase.
constexpr int kTaskIdBase = 2;
enum TaskId : uint8_t {{
    kTaskNone = 0, kTaskUnassigned = 1, kTaskConstruction = 2, kTaskMineIron = 3,
    kTaskMineEndurium = 4, kTaskResearch = 5, kTaskElectronicParts = 6, kTaskCulture = 7,
    kTaskCreateArt = 8, kTaskIronToSteel = 9, kTaskEnduriumToTriidium = 10, kTaskBuildUnits = 11,
    kTaskFood = 12, kTaskWood = 13, kTaskTrade = 14, kTaskEnergy = 15, kTaskAntiMatterPods = 16,
    kTaskClone = 17, kTaskTrainUnits = 18, kTaskHealMilitia = 19, kTaskHousePopulace = 20,
    kTaskUpgrade = 21, kTaskUnused = 22, kTaskBuildLandUnits = 23
}};

// Dominio de movimiento de una unidad (UnitDef::domain, FUN_00445b94 / CheckSubUnit)
enum UnitDomain : int8_t {{ kDomainLand = 1, kDomainSea = 2, kDomainAir = 3, kDomainAmphibious = 6 }};

// Clases de unidad (UnitDef::unitClass -> Army::unitClass); grupos de FUN_00447c2c/FUN_0046b4d0
enum UnitClass : uint8_t {{
    kClassInfantry = 1, kClassArmor = 2, kClassAir = 3, kClassSeaTransport = 4, kClassWarship = 5,
    kClassCommandCorps = 6, kClassScout = 7, kClassColonizer = 8, kClassWarhead = 9, kClassFort = 10,
    kClassMedic = 11, kClassAAV = 12, kClassAirCommand = 13, kClassDestroyer = 14, kClassSubmarine = 15,
    kClassSeaColonizer = 16, kClassSeaCommand = 17, kClassFlakShip = 18, kClassSiegeCruiser = 19,
    kClassMine = 20
}};

// ---- Edificios: DAT_004f9dbc (48 x 0x32) + costes DAT_004fa71c (48 x int32[11]) ----
struct BuildingDef {{
    const char* name;           // +0x00
    uint16_t    sprite;         // +0x04 indice base de sprite (PTR_DAT_004d02f4); +raza en viviendas/CC/SeaHab/Kelp
    uint8_t     icon;           // +0x06 imagen en IMAG "BU01" (FUN_0041beac)
    uint8_t     category;       // +0x07 -> Building::category (0x11 vivienda, 0x0b shrine, 0x12 defensa, 0x07 puerto...)
    uint8_t     maxLabor;       // +0x08 trabajadores maximos (FUN_0044ba40; viviendas x fila 24 de RaceStats)
    uint8_t     size;           // +0x09 casillas que ocupa: 1, 2 o 5 (FUN_0044d7b4)
    uint16_t    buildLabor;     // +0x0a puntos de trabajo para construirlo (Building+0x14 inicial; FUN_0044de9c cost[0])
    uint16_t    energyUse;      // +0x0c energia consumida por turno (FUN_0046b910)
    int16_t     taskRate[5];    // +0x0e rendimiento por ranura de tarea (FUN_0044eb4c; [0] = construccion = 100)
    uint8_t     tasks[5];       // +0x18 TaskId por ranura ([0] siempre 0; GetBuildingTasks lee 1..4)
    uint8_t     units[10];      // +0x1d unidades construibles (UnitType, 0 = fin; FUN_004383a4)
    uint8_t     techRequired;   // +0x27 TechId necesaria (FUN_0044de9c cost[12], "Tech: %s")
    uint8_t     hitPoints;      // +0x28 resistencia (FUN_004526b0: dano -> puntos de construccion perdidos)
    uint8_t     unk_29;         // +0x29 siempre 0, sin lectores
    int32_t     productionQueue;// +0x2a cola de Territory::queues (1 Factory..5 City Center; 0 = ninguna) (FUN_0044f3f0)
    int32_t     dialogAnim;     // +0x2e animacion del dialogo de produccion (FUN_0041ccb0 -> FUN_00482b38(4,id); -1 = ninguna)
    int32_t     cost[kNumMaterials]; // DAT_004fa71c: coste por Material (Money..Art)
}};
extern const BuildingDef kBuildingTypes[kNumBuildingTypes];

// ---- Unidades: PTR_s_No_Unit_004faf7c (39 x 0x24) + costes DAT_004fb4f8 (39 x int32[11]) ----
struct UnitDef {{
    const char* name;           // +0x00
    uint16_t    combatSprite;   // +0x04 sprite de combate (LoadCombatSprites; fuertes = sprite del edificio)
    uint16_t    moveAnim;       // +0x06 id ANIM del vehiculo (0 = infanteria por raza)
    uint16_t    portraitGroup;  // +0x08 grupo de retrato (FUN_004382d0: 0x9f inf, 0x91 medic, 0x98, 0xa6, 0xad)
    int8_t      portraitIndex;  // +0x0a indice dentro del grupo (+raza*N)
    uint8_t     unitClass;      // +0x0b UnitClass -> Army::unitClass (FUN_00445d30)
    uint16_t    buildLabor;     // +0x0c puntos de trabajo ("%d Labor"; FUN_0044ddf4 cost[0])
    int8_t      upkeep;         // +0x0e creditos de mantenimiento por turno (FUN_0046b4d0)
    int8_t      techRequired;   // +0x0f TechId (FUN_0044ddf4 cost[12])
    int8_t      moves;          // +0x10 puntos de movimiento (FUN_00447190 -> Army+0x0a; +1 con Transporters)
    int8_t      domain;         // +0x11 UnitDomain (1 tierra, 2 mar, 3 aire, 6 anfibio)
    int8_t      unk_12;         // +0x12 sin lectores en el codigo (4 inf, 2 blindados, 3 aire/mar, 0 fuertes)
    int8_t      attack;         // +0x13 ataque (FUN_00447c2c; x fila 29/35/37/39/41/43 de RaceStats)
    int8_t      defense;        // +0x14 defensa (FUN_00447da4; x fila 30/36/38/40/42/44)
    int8_t      speed;          // +0x15 velocidad en combate, menor = mas rapido; -1 inmovil (FUN_00447f44 + fila 46)
    int8_t      rateOfFire;     // +0x16 cadencia: kRateOfFireNames[rof+1] (FUN_00448008)
    int8_t      range;          // +0x17 alcance de disparo al cuadrado (FUN_004480a8)
    int32_t     sound;          // +0x18 id de sonido de disparo (FUN_0043d2d8 -> FUN_00482ac4)
    int32_t     cost[kNumMaterials]; // DAT_004fb4f8: coste por Material
}};
extern const UnitDef kUnitTypes[kNumUnitTypes];
extern const int32_t kMaxUnitsPerTerritorySea[4];   // DAT_004faf5c (FUN_00445b94, por clase de apilado)
extern const int32_t kMaxUnitsPerTerritoryLand[4];  // DAT_004faf6c

// ---- Tecnologias: DAT_004fbbac (48 x 0x32), parte estatica ----
struct TechDef {{
    const char* name;           // +0x14
    uint32_t    treeItemId;     // +0x18 id de item SMenu en el arbol (FUN_0043c540); 0 = no se muestra
    uint16_t    level;          // +0x20 nivel 1..8
    uint16_t    cost;           // +0x22 coste de investigacion
    uint16_t    prereq[3];      // +0x24 TechId requeridas (0 = ninguna)
    int16_t     treeIcon;       // +0x2c 1 / -1: variante de icono en el arbol
    uint16_t    treeY;          // +0x2e posicion en el arbol
    uint16_t    treeX;          // +0x30
}};
extern const TechDef kTechs[kNumTechs];

// ---- Modificadores raciales: DAT_004fc50c int16[64][8] (columna 7 sin uso) ----
extern const int16_t kRaceStatsDefault[kNumRaceStatRows][8];
extern const int16_t kRaceStatsRows61[3][8];        // DAT_004fc8dc: filas 61..63 para ficheros antiguos

// ---- Produccion por trabajadores: DAT_004f9bc4 int32[maxLabor][labor] (%; FUN_0044eb4c) ----
extern const int32_t kLaborProductionTable[11][11];

// ---- Event Log: DAT_004fc90c (157 x 0x12; FUN_0042278c busca por id) ----
struct EventDef {{
    int16_t     priority;       // +0x00 prioridad (FUN_004233e0 desaloja el mas antiguo de menor prioridad)
    int16_t     id;             // +0x06 id de evento (EventLogEntry::type)
    int16_t     category;       // +0x08 pestana del Event Log (FUN_004228d4); -1 = general
    int16_t     unk_0a;         // +0x0a
    int16_t     portrait;       // +0x0c retrato (FUN_004503f4; -1 ninguno; 7 = comparacion de ciudades)
    const char* format;         // +0x0e formato sprintf
}};
extern const EventDef kEventDefs[kNumEventDefs];

// ---- Campanas: DAT_004c6194 (43 x 0xd8; indice = GameOptions::campaign, 0 = ninguna) ----
struct CampaignGoal {{
    int32_t type;               // +0x00 tipo de objetivo (0 = vacio; 6 = llegada de IA; 0xd = territorios marinos...)
    int32_t turns;              // +0x04 turnos que hay que mantenerlo / nº de llegadas (tipo 6)
    int32_t count;              // +0x08 cantidad requerida (territorios de list[]) / 1er indice de llegada (tipo 6)
    int32_t list[13];           // +0x0c territorios / (turno, indice de kAiArrivals) para el tipo 6
    int32_t state;              // +0x40 MUTABLE en el original: 0 / 1 / turno en que se cumplio (se guarda)
}};
struct CampaignDef {{
    uint8_t      victory;       // +0x00 VictoryCondition
    int32_t      param1;        // +0x04 Win Cities (victory 0) / Win Shrines (victory 2)
    int32_t      param2;        // +0x08 Win Turns (victory 2)
    CampaignGoal goals[3];      // +0x0c
}};
extern const CampaignDef kCampaigns[kNumCampaigns];

// ---- Llegada de colonias IA en campana: DAT_004dc434 (x 0x9c; FUN_0047c730) ----
struct AiArrivalDef {{
    int32_t race;               // +0x00
    int32_t sites[4];           // +0x04 territorios candidatos de aterrizaje (FUN_0047c6c0)
    int32_t techLevel;          // +0x14 conoce todas las tecnologias de nivel <= techLevel
    int32_t credits;            // +0x18
    int32_t materials[10];      // +0x1c Territory::materials[1..10]
    int32_t units[10][2];       // +0x44 {{UnitType, cantidad}} (experiencia 200)
    int32_t allyRace;           // +0x94 raza con la que fija relacion
    int32_t allyPact;           // +0x98 valor de la relacion (FUN_00441700)
}};
extern const AiArrivalDef kAiArrivals[kNumAiArrivals];

// ---- Eventos aleatorios ----
struct OrigFunction {{ uint32_t addr; const char* name; }};
extern const OrigFunction kRandomEventHandlers[10];  // PTR_FUN_004dcab0[RandomEvent::type]
extern const char* const  kRandomEventNames[10];     // nombre por tipo (derivado del evento de log que emiten)
extern const int32_t  kBonusMaterials[5];            // DAT_004dca4c: Material de Bonus/NoBonus/Shaman
extern const uint16_t kSpyMissionRisk[4];            // DAT_004dca60: riesgo base % por Spy::mission
struct ScandalEffect {{ int16_t moraleLoss; int16_t globalMoraleLoss; int16_t riotChance; }};
extern const ScandalEffect kScandalTable[12];        // DAT_004dca68: por Player::scandals (0..11)

// ---- Rutas (FUN_0047da24 / FUN_0047dd58) ----
extern const int16_t kPathDelta1[4];                 // DAT_004dcbd8
extern const int16_t kPathDelta2[4];                 // DAT_004dcbe0
extern const int32_t kTileMoveCost[7];               // DAT_004dcbe8 por Tile::terrain

// ---- Economia / poblacion ----
extern const int32_t  kTaxRates[6];                  // DAT_004d57ec: % por Player::taxLevel
extern const int32_t  kTerrainMaxPopulation[6];      // DAT_004d5820: por Terrain (x fila 24 / 100)
extern const int32_t  kPopGrowthTable[5];            // DAT_004d583c (FUN_0046b1ac)
extern const int32_t  kMoraleByLevel[8];             // DAT_004d5850: por Territory+0x29 (FUN_0046bdfc)

// ---- Opciones de partida / mundo ----
extern const uint16_t kMapSizes[4];                  // DAT_004d5144: ancho/alto por tamano
extern const uint16_t kTerrainPctTable[5][6];        // DAT_004d514c: % de terreno por tamano (4 = "huge" raro)
extern const int32_t  kWinCitiesChoices[5];          // DAT_004c425c
extern const int32_t  kWinShrinesChoices[3];         // DAT_004c4274
extern const int32_t  kWinTurnsChoices[3];           // DAT_004c4280

// ---- Mercado negro Skirineen: DAT_004c42f8 (25 x 0xe) ----
struct BlackMarketOffer {{ int32_t unitType; int16_t experience; int32_t price; int32_t minTurn; }};
extern const BlackMarketOffer kBlackMarketOffers[kNumBlackMarket];

// ---- IA ----
// Personalidad de IA (PTR_DAT_004b502c + tipo*0x18; solo existe el tipo 3 "Machiavelli").
// FUN_00401830 copia fn[0..3] a Player+0x46 y fn[4] a Player+0x56; fn[1] = turno de IA (RunAITurns),
// fn[4] = receptor de eventos (FUN_00423690).
struct AiTypeDef {{ const char* name; OrigFunction fn[5]; }};
extern const AiTypeDef kAiType3;
struct MinisterVtable {{ int32_t id; OrigFunction fn[4]; }};
extern const MinisterVtable kMinisterVtable[6];      // PTR_FUN_004b508c (FUN_0040233c)
extern const int32_t kMinisterOrder[6];              // DAT_004b5104: orden de ejecucion (FUN_00402494)
struct MinisterConfig {{ int32_t kind; int32_t param; }};
extern const MinisterConfig kAiMinisterConfigDefault[6]; // DAT_004b62f4 (FUN_00408784)

// ---- Tablas de cadenas ----
extern const char* const kRaceNames[7];              // 0x509038
extern const char* const kTerrainNames[6];           // 0x509054
extern const char* const kMaterialNames[11];         // 0x50906c
extern const char* const kMaterialNamesLower[11];    // 0x509098
extern const char* const kTaskNames[24];             // 0x509178 (indice = TaskId)
extern const char* const kUnitSpeedNames[9];         // 0x509a64 (indice = speed+1)
extern const char* const kRateOfFireNames[10];       // 0x509a84 (indice = rateOfFire+1)
extern const char* const kAiLeaderNames[7];          // 0x509938
extern const char* const kRaceShortNames[7];         // 0x5099cf
extern const char* const kTaskForceGoalNames[21];    // 0x4b6bd4
extern const char* const kTaskForceStatusNames[6];   // 0x4b6c7c
extern const char* const kMinisterJobNames[14];      // 0x4b5fe8
extern const char* const kMinisterNames[6];          // 0x4b5fd0
extern const char* const kIniKeys[44];               // 0x4d5f60
extern const char* const kIniValues[8];              // 0x4d6010
extern const char* const kIniMapSizeNames[5];        // 0x4d6030
extern const char* const kIniWorldTypeNames[7];      // 0x4d6044
extern const char* const kIniRoleNames[2];           // 0x4d6060

// ---- Ayudas ----
inline const char* BuildingName(int type) {{ return (type >= 0 && type < kNumBuildingTypes) ? kBuildingTypes[type].name : ""; }}
inline const char* UnitName(int type)     {{ return (type >= 0 && type < kNumUnitTypes) ? kUnitTypes[type].name : ""; }}
inline const char* TechName(int tech)     {{ return (tech >= 0 && tech < kNumTechs) ? kTechs[tech].name : ""; }}
inline const char* TaskName(int taskId)   {{ return (taskId >= 0 && taskId < 24) ? kTaskNames[taskId] : ""; }}
// Edificio de defensa -> unidad de fuerte equivalente (FUN_00451de4: tipo-10; Torpedo Fort 40 -> 32)
inline int FortUnitForBuilding(int bldg) {{ return bldg == 40 ? 32 : (bldg >= 29 && bldg <= 32 ? bldg - 10 : 0); }}

}} // namespace dl2::data
'''


def gen_cpp(t):
    L = []
    w = L.append
    w('// data_tables.cpp - GENERADO por tools/extract_tables.py desde DEADLOCK.EXE; no editar a mano.')
    w('#include "game/data_tables.h"')
    w('')
    w('namespace dl2::data {')
    w('')
    # buildings
    w('const BuildingDef kBuildingTypes[kNumBuildingTypes] = {')
    for b in t['building_types']:
        w('    /* %2d */ {%s, %d, %d, %d, %d, %d, %d, %d, %s, %s, %s, %d, %d, %d, %d, %d, %s},' % (
            b['index'], cstr(b['name']), b['sprite'], b['icon'], b['category'], b['maxLabor'], b['size'],
            b['buildLabor'], b['energyUse'], ilist(b['taskRate']), ilist(b['tasks']), ilist(b['units']),
            b['techRequired'], b['hitPoints'], b['unk_29'], b['productionQueue'], b['dialogAnim'], ilist(b['cost'])))
    w('};')
    w('')
    w('const UnitDef kUnitTypes[kNumUnitTypes] = {')
    for u in t['unit_types']:
        w('    /* %2d */ {%s, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %s},' % (
            u['index'], cstr(u['name']), u['combatSprite'], u['moveAnim'], u['portraitGroup'], u['portraitIndex'],
            u['unitClass'], u['buildLabor'], u['upkeep'], u['techRequired'], u['moves'], u['domain'], u['unk_12'],
            u['attack'], u['defense'], u['speed'], u['rateOfFire'], u['range'], u['sound'], ilist(u['cost'])))
    w('};')
    w('const int32_t kMaxUnitsPerTerritorySea[4]  = %s;' % ilist(t['max_units_sea']))
    w('const int32_t kMaxUnitsPerTerritoryLand[4] = %s;' % ilist(t['max_units_land']))
    w('')
    w('const TechDef kTechs[kNumTechs] = {')
    for k in t['techs']:
        w('    /* %2d */ {%s, %d, %d, %d, %s, %d, %d, %d},' % (
            k['index'], cstr(k['name']), k['treeItemId'], k['level'], k['cost'], ilist(k['prereq']),
            k['treeIcon'], k['treeY'], k['treeX']))
    w('};')
    w('')
    w('const int16_t kRaceStatsDefault[kNumRaceStatRows][8] = {')
    for i, r in enumerate(t['race_stats_default']):
        w('    /* %2d */ %s,' % (i, ilist(r)))
    w('};')
    w('const int16_t kRaceStatsRows61[3][8] = {')
    for r in t['race_stats_rows61']:
        w('    %s,' % ilist(r))
    w('};')
    w('const int32_t kLaborProductionTable[11][11] = {')
    for r in t['labor_table']:
        w('    %s,' % ilist(r))
    w('};')
    w('')
    w('const EventDef kEventDefs[kNumEventDefs] = {')
    for e in t['event_defs']:
        w('    {%d, %d, %d, %d, %d, %s},' % (e['priority'], e['id'], e['category'], e['unk_0a'], e['portrait'], cstr(e['format'])))
    w('};')
    w('')
    w('const CampaignDef kCampaigns[kNumCampaigns] = {')
    for c in t['campaigns']:
        goals = ', '.join('{%d, %d, %d, %s, %d}' % (g['type'], g['turns'], g['count'], ilist(g['list']), g['state'])
                          for g in c['goals'])
        w('    /* %2d */ {%d, %d, %d, {%s}},' % (c['index'], c['victory'], c['param1'], c['param2'], goals))
    w('};')
    w('')
    w('const AiArrivalDef kAiArrivals[kNumAiArrivals] = {')
    for a in t['ai_arrivals']:
        units = '{' + ', '.join(ilist(u) for u in a['units']) + '}'
        w('    /* %d */ {%d, %s, %d, %d, %s, %s, %d, %d},' % (
            a['index'], a['race'], ilist(a['sites']), a['techLevel'], a['credits'], ilist(a['materials']),
            units, a['allyRace'], a['allyPact']))
    w('};')
    w('')

    def fnlist(name, fns):
        w('const OrigFunction %s = {' % name)
        for f in fns:
            w('    {0x%08x, %s},' % (f['addr'], cstr(f['name'])))
        w('};')

    fnlist('kRandomEventHandlers[10]', t['random_event_handlers'])
    w('const char* const kRandomEventNames[10] = {%s};' % ', '.join(cstr(n) for n in t['random_event_names']))
    w('const int32_t  kBonusMaterials[5]  = %s;' % ilist(t['bonus_materials']))
    w('const uint16_t kSpyMissionRisk[4]  = %s;' % ilist(t['spy_mission_risk']))
    w('const ScandalEffect kScandalTable[12] = {')
    for s in t['scandal_table']:
        w('    {%d, %d, %d},' % (s['moraleLoss'], s['globalMoraleLoss'], s['riotChance']))
    w('};')
    w('const int16_t kPathDelta1[4]  = %s;' % ilist(t['path_delta1']))
    w('const int16_t kPathDelta2[4]  = %s;' % ilist(t['path_delta2']))
    w('const int32_t kTileMoveCost[7] = %s;' % ilist(t['tile_move_cost']))
    w('')
    w('const int32_t  kTaxRates[6]             = %s;' % ilist(t['tax_rates']))
    w('const int32_t  kTerrainMaxPopulation[6] = %s;' % ilist(t['terrain_max_pop']))
    w('const int32_t  kPopGrowthTable[5]       = %s;' % ilist(t['pop_growth']))
    w('const int32_t  kMoraleByLevel[8]        = %s;' % ilist(t['morale_by_level']))
    w('const uint16_t kMapSizes[4]             = %s;' % ilist(t['map_sizes']))
    w('const uint16_t kTerrainPctTable[5][6] = {')
    for r in t['terrain_pct']:
        w('    %s,' % ilist(r))
    w('};')
    w('const int32_t kWinCitiesChoices[5]  = %s;' % ilist(t['win_cities']))
    w('const int32_t kWinShrinesChoices[3] = %s;' % ilist(t['win_shrines']))
    w('const int32_t kWinTurnsChoices[3]   = %s;' % ilist(t['win_turns']))
    w('')
    w('const BlackMarketOffer kBlackMarketOffers[kNumBlackMarket] = {')
    for o in t['black_market']:
        w('    {%d, %d, %d, %d},' % (o['unitType'], o['experience'], o['price'], o['minTurn']))
    w('};')
    w('')
    w('const AiTypeDef kAiType3 = {%s, {%s}};' % (cstr(t['ai_type3']['name']), ', '.join(
        '{0x%08x, %s}' % (f['addr'], cstr(f['name'])) for f in t['ai_type3']['fn'])))
    w('const MinisterVtable kMinisterVtable[6] = {')
    for m in t['minister_vtable']:
        fns = ', '.join('{0x%08x, %s}' % (f['addr'], cstr(f['name'])) for f in m['fn'])
        w('    {%d, {%s}},' % (m['id'], fns))
    w('};')
    w('const int32_t kMinisterOrder[6] = %s;' % ilist(t['minister_order']))
    w('const MinisterConfig kAiMinisterConfigDefault[6] = {%s};' % ', '.join(
        '{%d, %d}' % (m['kind'], m['param']) for m in t['minister_config']))
    w('')

    def strs(name, key):
        w('const char* const %s[%d] = {%s};' % (name, len(t[key]), ', '.join(cstr(s) for s in t[key])))

    strs('kRaceNames', 'race_names')
    strs('kTerrainNames', 'terrain_names')
    strs('kMaterialNames', 'material_names')
    strs('kMaterialNamesLower', 'material_names_lower')
    strs('kTaskNames', 'task_names')
    strs('kUnitSpeedNames', 'unit_speed_names')
    strs('kRateOfFireNames', 'rof_names')
    strs('kAiLeaderNames', 'ai_leader_names')
    strs('kRaceShortNames', 'race_short_names')
    strs('kTaskForceGoalNames', 'tf_goal_names')
    strs('kTaskForceStatusNames', 'tf_status_names')
    strs('kMinisterJobNames', 'minister_job_names')
    strs('kMinisterNames', 'minister_names')
    strs('kIniKeys', 'ini_keys')
    strs('kIniValues', 'ini_values')
    strs('kIniMapSizeNames', 'ini_map_size_names')
    strs('kIniWorldTypeNames', 'ini_world_type_names')
    strs('kIniRoleNames', 'ini_role_names')
    w('')
    w('} // namespace dl2::data')
    w('')
    return '\n'.join(L)


def main():
    exe = sys.argv[1] if len(sys.argv) > 1 else EXE_DEFAULT
    x = Exe(exe)
    t = extract(x)
    print('Tablas extraidas:')
    for k, v in t.items():
        print('  %-24s %s' % (k, len(v)))
    print('Validaciones:')
    ok = validate(t)

    out = dict(source=os.path.basename(exe), image_base=IMAGE_BASE,
               addresses={k: '0x%08x' % v for k, v in A.items()}, tables=t)
    (ROOT / 'data').mkdir(exist_ok=True)
    with open(ROOT / 'data' / 'tables.json', 'w', encoding='utf-8') as f:
        json.dump(out, f, indent=1, ensure_ascii=False)
    with open(ROOT / 'src' / 'game' / 'data_tables.h', 'w', encoding='utf-8', newline='\n') as f:
        f.write(gen_header(t))
    with open(ROOT / 'src' / 'game' / 'data_tables.cpp', 'w', encoding='utf-8', newline='\n') as f:
        f.write(gen_cpp(t))
    print('Escritos data/tables.json, src/game/data_tables.h, src/game/data_tables.cpp')
    return 0 if ok else 1


if __name__ == '__main__':
    sys.exit(main())
