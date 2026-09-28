#!/usr/bin/env python3
"""savparse.py - parser/validador del formato de partida guardada de Deadlock II (v1.20).

Reproduce la lógica de LoadGame (FUN_004618e8) y sus lectores para los formatos
"generación 4" (cabecera "Pre-release version XXXXXXXXXXX") y, parcialmente, los
formatos antiguos S/T/U/V.  Ver docs/SAVEFORMAT.md y src/game/game_state.h.

Uso:
    python tools/savparse.py                # TUTORIAL.SAV + las 42 entradas de LEVELS.HDD
    python tools/savparse.py archivo.sav    # un archivo concreto (.SAV/.CPN)
    python tools/savparse.py -v ...         # más detalle (edificios, ejércitos, eventos)
    python tools/savparse.py --check        # comprobaciones cruzadas (sitios<->edificios, tiles, ...)
"""
import os
import struct
import sys

GAME_DIR = r"C:\GOG Games\Deadlock 2"

# --- constantes del EXE -----------------------------------------------------
HEADER_TEXT = b"Deadlock 2  (c)1997 Accolade Inc.  All Rights Reserved.\nPre-release version XXXXXXXXXXX"
OLD_HEADERS = [
    b"Deadlock 2  (c)1997 Accolade Inc.  All Rights Reserved.\nPre-release version S (7/21/97)",
    b"Deadlock 2  (c)1997 Accolade Inc.  All Rights Reserved.\nPre-release version T (7/31/97)",
    b"Deadlock 2  (c)1997 Accolade Inc.  All Rights Reserved.\nPre-release version U (8/04/97)",
    b"Deadlock 2  (c)1997 Accolade Inc.  All Rights Reserved.\nPre-release version V (9/05/97)",
]
CURRENT_GEN = 4            # DAT_004d1d3c
CURRENT_VERSION = 0x120    # DAT_004d5ae8 (1.20)

SZ_HEADER = 0x9c
SZ_OPTIONS = 0xac
SZ_WORLD = 0x14
SZ_PLAYER = 0x2d8
NUM_PLAYERS = 7
SZ_RACESTATS = 0x380
NUM_TECHS = 0x30
SZ_TECH_SAVED = 0x12
SZ_MINJOB = 0x44
SZ_EVENT_SAVED = 0xc
SZ_TILE = 10
TILE_ROW = 400
SZ_BUILDING = 0x122
MAX_BUILDINGS = 1200
SZ_ARMY = 0x5c
MAX_ARMIES = 560
SZ_TERRITORY = 0xadc
TERR_UNSAVED_TAIL = 0x12a          # DAT_004d1cf8
SZ_TERRITORY_SAVED = SZ_TERRITORY - TERR_UNSAVED_TAIL   # 0x9b2
SZ_TERRITORY_SAVED_OLD = 0xac4 - TERR_UNSAVED_TAIL       # 0x99a (gen 0/1)
SZ_QUEUE_REC = 0x30
SZ_SITE = 0x34
NUM_SITES = 36
SZ_JOB = 0xc4
JOBS_PER_PLAYER = 50
SZ_JOBS = 7 * JOBS_PER_PLAYER * SZ_JOB   # 0x10bf8
SZ_WARMASK = 0x1c
SZ_CONTINENTS = 0x3440
SZ_RANDOMEVENTS = 700
SZ_SCORES = 0x2a
SZ_SPIES = 0x578
SZ_BLACKMARKET = 0x38
SZ_MAPTERR = 0xaa

RACES = ["ChCh't", "Cyth", "Human", "Maug", "Re'lu", "Tarth", "Uva Mosk"]
RACE_LETTER = "CYHMRTU"
TERRAIN = ["Sea", "Plains", "Forest", "Swamp", "Mountains", "Wasteland"]
VICTORY = ["Manifest Destiny", "Conquest", "Shrine Wars"]
PLAYER_TYPE = {0: "none", 1: "local human", 2: "remote human", 3: "AI"}
MATERIALS = ["Money", "Food", "Energy", "Wood", "Iron", "Steel", "Endurium", "Triidium",
             "Electronic Parts", "Anti-Matter Pods", "Art"]


class R:
    """Lector secuencial con comprobación de límites."""

    def __init__(self, data, name):
        self.d = data
        self.o = 0
        self.name = name

    def take(self, n):
        if self.o + n > len(self.d):
            raise EOFError("%s: faltan %d bytes en offset 0x%x" % (self.name, self.o + n - len(self.d), self.o))
        b = self.d[self.o:self.o + n]
        self.o += n
        return b

    def u8(self):
        return self.take(1)[0]

    def s8(self):
        return struct.unpack('<b', self.take(1))[0]

    def u16(self):
        return struct.unpack('<H', self.take(2))[0]

    def s16(self):
        return struct.unpack('<h', self.take(2))[0]

    def u32(self):
        return struct.unpack('<I', self.take(4))[0]

    def s32(self):
        return struct.unpack('<i', self.take(4))[0]

    def eof(self):
        return self.o >= len(self.d)


def cstr(b):
    return b.split(b'\0')[0].decode('latin-1')


def parse_header(r):
    b = r.take(SZ_HEADER)
    text = b[:88]
    if text.startswith(HEADER_TEXT):
        gen = CURRENT_GEN
    else:
        gen = None
        for i, h in enumerate(OLD_HEADERS):
            if text.startswith(h):
                gen = i
        if gen is None:
            raise ValueError("cabecera desconocida: %r" % text[:40])
    version, is_map, zero, minus1 = struct.unpack_from('<IiiI', b, 88)
    return dict(gen=gen, version=version, is_map=is_map, text=cstr(text))


def parse_options(r, gen, version):
    """FUN_00462100: tamaños distintos según versión; devolvemos siempre 0xac bytes."""
    if gen < 4:
        raw = bytearray(r.take(0x74)) + bytearray(SZ_OPTIONS - 0x74)
    elif version < 3:
        raw = bytearray(r.take(0x88)) + bytearray(SZ_OPTIONS - 0x88)
    elif version < 9:
        n = SZ_OPTIONS - (6 if version < 7 else 2)
        raw = bytearray(r.take(n)) + bytearray(SZ_OPTIONS - n)
    else:
        raw = bytearray(r.take(SZ_OPTIONS))
    g = lambda fmt, off: struct.unpack_from(fmt, raw, off)[0]
    o = dict(
        turn=g('<i', 0x00), gameSeed=g('<I', 0x04), gameId=g('<i', 0x08),
        numPlayers=g('<i', 0x0c), winCities=g('<i', 0x10), winShrines=g('<i', 0x14),
        winTurns=g('<i', 0x18), victory=g('<B', 0x1c), fastProduction=g('<i', 0x1e),
        randomEvents=g('<i', 0x22), aiSkill=g('<i', 0x26),
        flags=g('<I', 0x3a), localPlayer=g('<i', 0x3e), eventLogFirst=g('<i', 0x42),
        eventCount=g('<i', 0x46), autoTimer=g('<i', 0x4a), reserved4e=g('<i', 0x4e),
        autoTimerClock=g('<i', 0x52), lastPlayerTimer=g('<i', 0x56),
        lastPlayerClock=g('<i', 0x5a), racialAbilities=g('<i', 0x5e),
        hasWon=list(struct.unpack_from('<7H', raw, 0x66)),
        worldResources=g('<i', 0x74), nextGlobalId=g('<i', 0x78), campaign=g('<i', 0x7c),
        playerSkill=list(raw[0x80:0x87]), playersMask=raw[0x87],
        shrineTurns=list(struct.unpack_from('<7i', raw, 0x88)),
        campaignBytes=list(raw[0xa4:0xa7]), allowAlliances=g('<i', 0xa8),
    )
    return o


def parse_world(r):
    b = r.take(SZ_WORLD)
    seed1, seed2, nterr, w, h, wtype = struct.unpack_from('<IIHBBB', b, 0)
    pct = list(b[0xd:0x13])
    return dict(seed1=seed1, rngSeed=seed2, numTerritories=nterr, width=w, height=h,
                worldType=wtype, terrainPct=pct, numColonySites=b[0x13])


def parse_player(b):
    g = lambda fmt, off: struct.unpack_from(fmt, b, off)[0]
    return dict(
        index=b[0], type=b[1], race=g('<b', 2), netId=g('<H', 4), homeTerritory=g('<h', 6),
        turnDone=b[8], foodFlags=b[9], scandals=b[0xa], taxLevel=g('<b', 0xb),
        credits=g('<i', 0xc), currentResearch=g('<b', 0x3e),
        relations=list(struct.unpack_from('<7I', b, 0x27a)),
        name=cstr(b[0x2b3:0x2d4]), defeated=g('<i', 0x2d4),
    )


def parse_territory_saved(b):
    g = lambda fmt, off: struct.unpack_from(fmt, b, off)[0]
    t = dict(
        name=cstr(b[0:25]), index=g('<H', 0x1a), flags=g('<I', 0x1c), owner=g('<b', 0x20),
        terrain=b[0x21], continent=g('<b', 0x22), morale=g('<b', 0x27),
        taxAdjust=g('<h', 0x2a), population=g('<h', 0x30), knowledge=b[0x35],
        knownPopulation=g('<h', 0x38),
        materials=list(struct.unpack_from('<11i', b, 0x3a)),
        visibility=list(b[0x66:0x6d]), centerTile=g('<b', 0x74), secondTile=g('<b', 0x75),
        armies=g('<I', 0x76), foreignArmies=g('<I', 0x7a), numTiles=b[0x7e],
        tiles=[struct.unpack_from('<I', b, 0x80 + 4 * i)[0] for i in range(48)],
        adjacency=list(struct.unpack_from('<7H', b, 0x890)),
    )
    sites = []
    for i in range(NUM_SITES):                       # BuildingSite[36] en +0x140 (paso 0x34)
        s = b[0x140 + i * SZ_SITE:0x140 + (i + 1) * SZ_SITE]
        sites.append(dict(terrain=struct.unpack_from('<H', s, 2)[0], value=s[4],
                          building=struct.unpack_from('<I', s, 0x14)[0]))
    t['sites'] = sites
    t['freeSites'] = b[0x89f]
    t['adjContinents'] = g('<I', 0x8a0)
    t['exploredMask'] = g('<I', 0x8a8)
    t['coastal'] = g('<I', 0x8ac)
    t['hoverway'] = b[0x9ae]
    t['portTarget'] = g('<H', 0x9b0)
    return t


def deep_check(s):
    """Comprobaciones cruzadas entre estructuras (validan los offsets internos)."""
    w = s['world']
    N = w['numTerritories']
    T = {t['index']: t for t in s['territories']}
    B = {b['id']: b for b in s['buildings']}
    A = {a['id']: a for a in s['armies']}
    r = dict(sites=0, sites_ok=0, blds=0, blds_ok=0, tiles=0, tiles_ok=0, tlist=0, tlist_ok=0,
             adj=0, adj_ok=0, armies=0, armies_ok=0, alists=0, alists_ok=0)
    for t in s['territories']:
        for k, st in enumerate(t['sites']):
            if st['building']:
                r['sites'] += 1
                b = B.get(st['building'])
                if b and b['territory'] == t['index'] and b['site'] == k:
                    r['sites_ok'] += 1
        for k in range(t['numTiles']):
            v = t['tiles'][k]
            x, y = v & 0xffff, v >> 16
            r['tlist'] += 1
            if x < w['width'] and y < w['height']:
                tb = s['tiles'][y * w['width'] + x]
                if struct.unpack_from('<h', tb, 2)[0] == t['index']:
                    r['tlist_ok'] += 1
        for j in range(1, N + 1):
            if (t['adjacency'][j >> 4] >> (j & 15)) & 1:
                r['adj'] += 1
                u = T[j]
                if (u['adjacency'][t['index'] >> 4] >> (t['index'] & 15)) & 1:
                    r['adj_ok'] += 1
        # listas de ejércitos del territorio: cabeza -> Army::next...
        for head in ('armies', 'foreignArmies'):
            aid = t[head]
            seen = 0
            while aid and seen < 600:
                r['alists'] += 1
                a = A.get(aid)
                # Alias legacy: dest (+3c) = actual/enlazado; territory (+38) = inicio del turno.
                # Se conserva la comprobación permisiva histórica del parser.
                if a and (a['territory'] == t['index'] or a['dest'] == t['index']):
                    r['alists_ok'] += 1
                aid = a['next'] if a else 0
                seen += 1
    for b in s['buildings']:
        r['blds'] += 1
        t = T.get(b['territory'])
        if t and 0 <= b['site'] < NUM_SITES and t['sites'][b['site']]['building'] == b['id']:
            r['blds_ok'] += 1
    for i, tb in enumerate(s['tiles']):
        r['tiles'] += 1
        terr = struct.unpack_from('<h', tb, 2)[0]
        if tb[0] == i % w['width'] and tb[1] == i // w['width'] and 0 <= terr <= N:
            r['tiles_ok'] += 1
    for a in s['armies']:
        r['armies'] += 1
        if (1 <= a['territory'] <= N and 1 <= a['dest'] <= N and 1 <= a['origin'] <= N
                and 0 <= a['owner'] < 7 and 1 <= a['type'] < 39 and a['health'] <= 100
                and all(c == 0 or c in A for c in a['cargo'])
                and (a['next'] == 0 or a['next'] in A) and (a['prev'] == 0 or a['prev'] in A)):
            r['armies_ok'] += 1
    return r


def parse_building(b):
    g = lambda fmt, off: struct.unpack_from(fmt, b, off)[0]
    return dict(id=g('<H', 0), flags=g('<H', 2), type=b[4], category=b[5], race=b[6],
                site=g('<b', 7), territory=g('<h', 8), minister=g('<b', 0xe),
                turnsLeft=g('<h', 0x14), labor=list(struct.unpack_from('<5i', b, 0x18)),
                tasks=list(b[0x2c:0x31]), unk116=g('<I', 0x116), prev=g('<I', 0x11a),
                next=g('<I', 0x11e))


def parse_army(b):
    # Claves legacy estables: territory (+38) = inicio de turno, dest (+3c) = actual,
    # origin (+40) = ancla de ruta; moves (+24) = orden de combate, no movimiento;
    # health (+26) = umbral de retirada %, no salud. El movimiento restante está en +0a.
    g = lambda fmt, off: struct.unpack_from(fmt, b, off)[0]
    return dict(id=g('<H', 0), type=b[6], cls=b[7], owner=g('<b', 8), name=cstr(b[0xb:0x23]),
                moves=b[0x24], health=b[0x26], experience=g('<h', 0x28), job=g('<h', 0x36),
                territory=g('<i', 0x38), dest=g('<i', 0x3c), origin=g('<i', 0x40),
                cargo=list(struct.unpack_from('<3I', b, 0x48)), next=g('<I', 0x54), prev=g('<I', 0x58))


def parse_save(data, name, verbose=False):
    r = R(data, name)
    hdr = parse_header(r)
    gen, ver = hdr['gen'], hdr['version']
    if ver > CURRENT_VERSION:
        raise ValueError("versión más nueva (%d)" % ver)
    out = dict(header=hdr)
    if hdr['is_map']:
        out['world'] = w = parse_world(r)
        terrs = []
        for i in range(1, w['numTerritories'] + 1):
            b = r.take(SZ_MAPTERR)
            sites = [struct.unpack_from('<HBB', b, 0x1a + 4 * k) for k in range(NUM_SITES)]
            terrs.append(dict(name=cstr(b[:25]), terrain=b[25], sites=sites))
        out['territories'] = terrs
        out['tiles'] = [r.take(SZ_TILE) for _ in range(w['width'] * w['height'])]
        out['trailing'] = len(data) - r.o
        return out

    out['options'] = opt = parse_options(r, gen, ver)
    out['world'] = w = parse_world(r)
    # Player[7]  (gen<3: numPlayers*0x2d8, sólo se conservan los 7 primeros bloques)
    if gen < 3:
        pl = r.take(opt['numPlayers'] * SZ_PLAYER)[:NUM_PLAYERS * SZ_PLAYER]
    else:
        pl = r.take(NUM_PLAYERS * SZ_PLAYER)
    out['players'] = [parse_player(pl[i * SZ_PLAYER:(i + 1) * SZ_PLAYER]) for i in range(NUM_PLAYERS)]
    # lista de u32 del jugador local (terminada en -1), sólo version >= 7
    lst = []
    if ver >= 7:
        while True:
            v = r.s32()
            if v == -1:
                break
            lst.append(v)
    out['localList'] = lst
    # RaceStats s16[64][7]
    if ver < 0x23:
        r.take(0x356 if gen < 1 else 0x364)
        out['raceStats'] = None
    else:
        out['raceStats'] = r.take(SZ_RACESTATS)
    # Tech[48] x 0x12
    techs = []
    for i in range(NUM_TECHS):
        b = r.take(SZ_TECH_SAVED)
        techs.append(dict(known=struct.unpack_from('<H', b, 0)[0], f2=struct.unpack_from('<H', b, 2)[0],
                          perPlayer=list(struct.unpack_from('<7H', b, 4))))
    out['techs'] = techs
    # listas de trabajos de ministros (7 cabeceras + nodos)
    minjobs = []
    if gen >= 2:
        for p in range(NUM_PLAYERS):
            nodes = []
            head = r.take(SZ_MINJOB)
            nxt = struct.unpack_from('<I', head, 0x14)[0]
            while nxt != 0:
                nb = r.take(SZ_MINJOB)
                nodes.append(nb)
                nxt = struct.unpack_from('<I', nb, 0x14)[0]
            minjobs.append(nodes)
    out['ministerJobs'] = minjobs
    # Event log
    events = []
    for i in range(opt['eventCount']):
        b = r.take(SZ_EVENT_SAVED)
        etype, elen, a, bb = struct.unpack_from('<HHii', b, 0)
        text = r.take(elen)
        events.append(dict(type=etype, player=a, param=bb, text=cstr(text)))
    out['events'] = events
    # Tiles h x w x 10
    tiles = []
    for y in range(w['height']):
        for x in range(w['width']):
            tiles.append(r.take(SZ_TILE))
    out['tiles'] = tiles
    # Buildings
    nb = r.s32()
    if nb < 0 or nb > MAX_BUILDINGS:
        raise ValueError("nº de edificios absurdo: %d" % nb)
    if gen < 2:
        blds = [r.take(0x136) for _ in range(nb)]
        out['buildings'] = []
    else:
        out['buildings'] = [parse_building(r.take(SZ_BUILDING)) for _ in range(nb)]
    # Armies
    na = r.s32()
    if na < 0 or na > MAX_ARMIES:
        raise ValueError("nº de ejércitos absurdo: %d" % na)
    out['armies'] = [parse_army(r.take(SZ_ARMY)) for _ in range(na)]
    # Territories 1..N
    terrs = []
    for i in range(1, w['numTerritories'] + 1):
        if gen < 2:
            b = r.take(SZ_TERRITORY_SAVED_OLD)
            queues = [[] for _ in range(5)]
        else:
            b = r.take(SZ_TERRITORY_SAVED)
            queues = []
            for q in range(5):
                cnt = r.u8()
                queues.append([r.take(SZ_QUEUE_REC) for _ in range(cnt)])
        t = parse_territory_saved(b)
        t['queues'] = queues
        if t['index'] != i:
            raise ValueError("territorio %d tiene índice %d" % (i, t['index']))
        terrs.append(t)
    out['territories'] = terrs
    # Jobs (task forces de la IA)
    if gen < 3:
        r.take(0xc40)
    else:
        r.take(SZ_JOBS)
    r.take(SZ_WARMASK)
    r.take(SZ_JOB)
    r.take(SZ_JOB)
    r.take(SZ_CONTINENTS)
    if gen >= 3:
        out['randomEvents'] = r.take(SZ_RANDOMEVENTS)
    if ver >= 0x11:
        out['scores'] = r.take(SZ_SCORES)
    if ver >= 0x24:
        out['spies'] = r.take(SZ_SPIES)
        out['blackMarket'] = r.take(SZ_BLACKMARKET)
    out['trailing'] = len(data) - r.o
    return out


def summarize(name, s, verbose=False):
    h = s['header']
    print("== %s  (gen %d, version %d, %s)" % (name, h['gen'], h['version'], "MAPA" if h['is_map'] else "partida"))
    w = s['world']
    print("   mapa %dx%d, %d territorios, tipo %d, terreno%% %s, sitios %d, semillas %08x/%08x" % (
        w['width'], w['height'], w['numTerritories'], w['worldType'], w['terrainPct'],
        w['numColonySites'], w['seed1'], w['rngSeed']))
    if h['is_map']:
        for t in s['territories'][:4]:
            print("   terr %-24s %s" % (t['name'], TERRAIN[t['terrain']] if t['terrain'] < 6 else t['terrain']))
        print("   bytes sobrantes: %d" % s['trailing'])
        return
    o = s['options']
    print("   turno %d, jugadores %d, victoria %s (cities %d, shrines %d x %d turnos), local %d, "
          "skill %d, alianzas %d, eventos %d, nextId %d, campaña %d" % (
              o['turn'], o['numPlayers'], VICTORY[o['victory']] if o['victory'] < 3 else o['victory'],
              o['winCities'], o['winShrines'], o['winTurns'], o['localPlayer'], o['aiSkill'],
              o['allowAlliances'], o['eventCount'], o['nextGlobalId'], o['campaign']))
    for p in s['players']:
        if p['type'] == 0:
            continue
        race = RACES[p['race']] if 0 <= p['race'] < 7 else "race%d" % p['race']
        print("   jugador %d: %-20s %-8s %-12s home=%-3d cr=%-6d tax=%d research=%d" % (
            p['index'], repr(p['name']), race, PLAYER_TYPE.get(p['type'], p['type']),
            p['homeTerritory'], p['credits'], p['taxLevel'], p['currentResearch']))
    print("   edificios %d, ejércitos %d, territorios %d, cola local %d, minjobs %s" % (
        len(s['buildings']), len(s['armies']), len(s['territories']), len(s['localList']),
        [len(x) for x in s['ministerJobs']]))
    # comprobaciones de coherencia
    bad = 0
    ids = {b['id'] for b in s['buildings']}
    for t in s['territories']:
        if t['numTiles'] > 48:
            bad += 1
        for st in t['sites']:
            if st['building'] and st['building'] not in ids:
                bad += 1
    aids = {a['id'] for a in s['armies']}
    for a in s['armies']:
        for c in a['cargo']:
            if c and c not in aids:
                bad += 1
        if not (0 <= a['territory'] <= w['numTerritories']):
            bad += 1
    owned = [t for t in s['territories'] if t['owner'] >= 0]
    for t in owned[:5]:
        print("   terr %2d %-22s dueño %d %-9s pob %4d moral %3d food %5d energy %5d cont %d tiles %d" % (
            t['index'], repr(t['name']), t['owner'], TERRAIN[t['terrain']] if t['terrain'] < 6 else t['terrain'],
            t['population'], t['morale'], t['materials'][1], t['materials'][2], t['continent'], t['numTiles']))
    print("   refs incoherentes: %d, bytes sobrantes: %d" % (bad, s['trailing']))
    if CHECK:
        r = deep_check(s)
        print("   check: sitios %d/%d edificios %d/%d tiles %d/%d listaTiles %d/%d adyacencia %d/%d "
              "ejercitos %d/%d listasEj %d/%d" % (
                  r['sites_ok'], r['sites'], r['blds_ok'], r['blds'], r['tiles_ok'], r['tiles'],
                  r['tlist_ok'], r['tlist'], r['adj_ok'], r['adj'], r['armies_ok'], r['armies'],
                  r['alists_ok'], r['alists']))
        for k in ('sites', 'blds', 'tiles', 'tlist', 'adj', 'armies', 'alists'):
            if r[k] != r[k + '_ok']:
                bad += r[k] - r[k + '_ok']
    if verbose:
        for e in s['events'][:6]:
            print("   evento tipo %3d: %s" % (e['type'], e['text'][:70]))
        for b in s['buildings'][:8]:
            print("   edificio id %4d tipo %2d terr %2d sitio %2d flags %04x turnos %d" % (
                b['id'], b['type'], b['territory'], b['site'], b['flags'], b['turnsLeft']))
        for a in s['armies'][:8]:
            print("   ejercito id %4d tipo %2d dueño %d %-28s hp %3d terr %d" % (
                a['id'], a['type'], a['owner'], repr(a['name']), a['health'], a['territory']))
    return bad


def read_hdx(base):
    hx = open(base + ".HDX", "rb").read()
    hd = open(base + ".HDD", "rb").read()
    n = struct.unpack_from('<I', hx, 0)[0]
    for i in range(n):
        name = hx[4 + 12 * i:12 + 12 * i].rstrip(b'\0').decode('latin-1')
        off = struct.unpack_from('<I', hx, 12 + 12 * i)[0]
        ln = struct.unpack_from('<I', hd, off)[0]
        yield name, hd[off + 4:off + 4 + ln]


CHECK = False


def main(argv):
    global CHECK
    verbose = '-v' in argv
    CHECK = '--check' in argv
    files = [a for a in argv[1:] if a not in ('-v', '--check')]
    ok = fail = 0
    if not files:
        items = [("TUTORIAL.SAV", open(os.path.join(GAME_DIR, "TUTORIAL.SAV"), "rb").read())]
        for p in ("Saves\\AUTOSAVE.SAV", "Campaign\\AUTOSAVE.CPN", "Campaign\\ChCht001.CPN"):
            fp = os.path.join(GAME_DIR, p)
            if os.path.exists(fp):
                items.append((p, open(fp, "rb").read()))
        items += list(read_hdx(os.path.join(GAME_DIR, "LEVELS")))
    else:
        items = [(f, open(f, "rb").read()) for f in files]
    for name, data in items:
        try:
            s = parse_save(data, name, verbose)
            bad = summarize(name, s, verbose)
            if bad:
                fail += 1
            else:
                ok += 1          # los bytes sobrantes de LEVELS.HDD son relleno de versiones previas
        except Exception as e:  # noqa
            fail += 1
            print("== %s: ERROR %s" % (name, e))
    print("\n%d correctos, %d con problemas" % (ok, fail))


if __name__ == '__main__':
    try:
        sys.stdout.reconfigure(encoding='utf-8')
    except Exception:  # noqa
        pass
    main(sys.argv)
