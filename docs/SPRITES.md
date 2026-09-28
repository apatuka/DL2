# Sprites y animación (SPRITENW.DAT) — ingeniería inversa y port

Fuente: decompilado de `DEADLOCK.EXE` v1.20 (`re/decomp/`), verificado renderizando todas las tablas
(`re/sprites/*.png`, generadas por `tools/extract_sprites.py`) y con `dl2tool render-sprite / sprite-sheet /
anim-demo` (código C++ de `src/sprites/`). Nombres de funciones nuevos en `re/names_sprites.tsv`.

## 1. Formato y tablas

`SPRITENW.DAT` (11 499 144 bytes) es un blob de píxeles 8 bpp sin cabecera. Todo el índice vive en la sección
DATA del EXE:

```
struct SpriteDef {            // 16 bytes; una tabla termina con w == h == 0
    int16  hotX, hotY;        // se SUMAN a la posición del objeto al dibujar (DrawSprite: sx = (x >> 8) + hotX)
    int16  w, h;
    uint8* pixels;            // 0 en el fichero; el cargador lo rellena (FUN_00483098)
    uint32 fileOffset;        // w*h bytes en SPRITENW.DAT
};
struct SpriteType {           // tabla de tipos @ 0x004D02F4, 427 registros de 12 bytes
    SpriteDef* frames;        // tabla de frames del tipo
    uint16*    animScript;    // script de animación (0 = ninguno), ver §4
    uint16     rate;          // ticks entre pasos del script (0,1,2,3,4,5,50)
    uint16     flags;         // OR-eado en los flags del ANIM al crearlo (0 u 8)
};
```

**Indexación**: un sprite es `(tipo, frame)` → `SpriteTypeTable[tipo].frames[frame]`. El juego nunca usa
índices globales de frame; los `SpriteDef*` que circulan por el código apuntan dentro de la tabla de su tipo
(p. ej. `GetBuildingSpriteDef` FUN_0047f4ec devuelve `tabla + 0x10` = frame 1 si el edificio está activo).
Total: 427 tipos, 6 771 frames, 8 879 940 bytes de píxeles (los últimos terminan exactamente en el final del
fichero; los píxeles no se solapan entre tipos salvo tablas compartidas).

Píxel 0 = transparente en el fichero. Al cargar, `RemapSpritePixels` FUN_00483038 hace `0 → 255` y
`255 → 192`, y el blit CYLib 8 bpp usa **255 como color clave**; por eso el blanco de los sprites usa la
entrada 192 (`EF EF EF`). Las imágenes fijas (`StillPic`, `DrawSpriteCentered`, `CreateWinGWindow`) se leen
crudas con `ReadDataFileChunk` FUN_0046ca70 y se dibujan opacas.

### 1.1 Cómo se reparten los 427 tipos

| Tipos | Contenido (nombre en `sprites.json`) | Quién los usa |
|---|---|---|
| 0, 1 | iconos de edificio 80×60 / 40×40 (`BuildingIcons*`) | UI (globales) |
| 2, 111, 112 | contornos de casilla isométrica 78×39 / 176×88 | selección |
| 3 cursor, 4 `BonusIcons`, 6 `ResourceIcons`, 7 `Roads` (128×128), 8 `EventPictures` 64×64, 10–14 iconos | globales / control |
| 15–97 | edificios (`Bldg_<nombre>`); tabla de edificios @ 0x4F9DBC (stride 0x32, `+4` = tipo base). Housing, Apartment, Luxury Housing, Art Complex, City Center y SeaHab tienen 7 tipos consecutivos (uno por raza) | asentamiento |
| 98–104 | `Colonists_<raza>` (figuras 17×17, FUN_00480be0 crea tipo `0x62 + raza`) | asentamiento |
| 105–110 | obras: `ConstructionSmall/Large` (poste + llamas) y grúas `CraneA..D` (14 frames, script 0x518de8) | asentamiento/combate |
| 113, 114 | `CombatTerrain*` (rombos de terreno del campo de batalla) | combate |
| 115 | `TerrainWasteland` 28 frames (4 grupos de 7 para la clase de casilla 5) | `DrawTerrainTile` |
| 116–129 | `Terrain_w<planeta>_a/b`: 7 juegos de casillas (planeta = `DAT_004d5b1c`), FUN_0047f9a0 elige `116 + 2*planeta` | asentamiento |
| 130 `Ambient` (pájaros), 173 `MiscIcons`, 174 `Sparks`, 183 `Smoke` | ANIMs decorativos |
| 131–138 | `MapCity_<raza>` (8 tablas de `PTR_DAT_004d0918`; frame 20 = emblema para el mapa) | control |
| 139–144 | `MapUnits_<raza>`, 145–172 `UnitIcons{A,Sea,Infantry,Vehicles}_<raza>` | control/asentamiento |
| 175–181 | explosiones (`DestroyAnim` usa 175..180), 182 mina, 179 estela de misil | combate |
| 184–199 | cabezas nucleares/misiles: `base + {0,3,1,2}` según tipo de cabeza (`+0x14`: 8,1,2,4) | combate |
| 200–394 | unidades `Unit_<nombre>_<raza>` (tabla de unidades @ 0x4FAF7C: nombre, `+4` tipo base, `+6` tipo secundario, `+0xb` clase); tipo = base + raza; AAV +7 de noche | combate |
| 395–398, 399–403 | `TrooperAlt2_<u>` (395+u) y `TrooperAlt_<u>` (399+u): variantes de infantería (FUN_00448284 / FUN_004482cc) | combate |
| 404–407 | proyectiles (láser, fusión, disruptor, holocausto); `CreateHit` usa 405/407 | combate |
| 408–426 | tipos secundarios de unidades (`Unit_<nombre>_2`: torretas, sombras) | combate |

Tablas **fuera** de la tabla de tipos (`extraTables` del JSON, `kExtraTables` en C++), localizadas por
escaneo de la sección DATA y por referencias directas: `WinGPictures` @ 0x4E2AAC (7 retratos de cuerpo entero
200×248, `CreateWinGWindow`), `WinGPortraits` @ 0x4E2E1C, `RaceEmblems` @ 0x4F625C (13×11, FUN_0048192c),
`Pictures1..8`/`TechPictures*` (148×148, diálogos de tecnología) e `Icons32`/`TinyIcons`.

### 1.2 Conjuntos por fase (cargadores)

`DAT_00657e60` es el mapa de bits "tipo cargado". Cada carga lee **todos** los frames de un tipo a un bloque
contiguo (`AllocMem`, "G Sprite"/"P Sprite"/"Phase Sprite") y guarda los tipos en un anillo de 0x800 conjuntos
(`PushPhaseSet` FUN_004831ac); cuando no hay memoria se descarga el conjunto más antiguo (`PopOldestPhaseSet`).

| Conjunto | Función | Tipos |
|---|---|---|
| Global | `PreloadSprite2` → `LoadGlobalSprites(DAT_004d4dd0, 17)` | 2,3,4,12,14,10,173,13,0,98–104,7 |
| Asentamiento (2) | FUN_004658a8 `LoadSettlementSprites` | lista A (0x4D4E14: 105–115,9,6,130) + `116/117 + 2*planeta` + todos los edificios (vivienda por raza presente) + 145/152/159/166 + raza |
| Control (1) | FUN_00465ac8 `LoadControlSprites` | 131,138,145,152,159,166 + raza, y 11 |
| Combate (3) | `LoadCombatSprites` | lista A + lista B (0x4D4E4C: 175–178,180,181) + edificios del campo + unidades (`unitSpriteType`) + 404/405, 406/407 |

Port: `dl2::sprites::SpriteBank` (`loadGlobalSprites`, `loadSettlementSprites(planeta, razas)`,
`loadControlSprites`, `loadCombatSprites`, `loadPhaseSprites`, `popOldestPhaseSet`, `frame(tipo, i)` con carga
perezosa por tipo, `readPixels` para tablas extra).

## 2. Paleta

**Respuesta**: la paleta del juego no es `DPAL`/`TTIP` ni el CMAP de las PICT: está **incrustada en el EXE**
como tablas `RGBQUAD` (B,G,R,x) y se ensambla en la paleta de trabajo `0x0051A8A4`:

| Entradas | Origen | Función |
|---|---|---|
| 0–9, 246–255 | los 20 colores estáticos de Windows (`GetSystemPaletteEntries`) | FUN_00463738 / FUN_004637b4 `BuildLogPalette` |
| 10–15 | `0x0051A5CC` (6 entradas) | FUN_0046338c `SetWorldPalette` |
| 16–79 | `0x00519ECC + planeta*0x100` (7 juegos de 64 = colores del terreno) | FUN_0046338c, planeta = `DAT_004d5b1c` (0..6, elegido en `SetupNewWorld`) |
| 80–143 | maestra `0x0051ACA4` (copiada 10..245 en `CreateMainWindow`); dentro de una ventana XenoWinG de retrato se sustituyen por `0x0051A7A4` (64 entradas) | `CreateWinGWindow` |
| 144–245 | `0x0051A5E4` (112 entradas) | FUN_0046338c |

La paleta se realiza vía `CreatePalette` (GDI, flags `PC_RESERVED`) y se copia al objeto paleta de CYLib
(`UpdateCYLibPalette` FUN_004639f4) para la ruta DirectDraw. `StillPic` puede parchear un rango de entradas para
una imagen fija. Port: `sprites::makeGamePalette(planeta, retratos)`; los datos están en `sprite_tables.cpp`
(`kPaletteMaster`, `kPaletteWorld[7][64]`, `kPaletteFixed6`, `kPaletteFixed112`, `kPaletteDialog64`).
La tabla de trabajo inicial del EXE (`0x51A8A4`) contiene una paleta antigua que nunca se usa tal cual.

## 3. Dibujo

`BlitSprite8` FUN_004647a0 `(buf, x, y, w, h, pitch, modo)`: recorta al rectángulo `DAT_0058df34..40`
(`SetClipRect` FUN_00463d00, restablecido por `SelectSurface` FUN_00463da8) y llama a la rutina CYLib 8 bpp
del formato actual (`DAT_0069ee98[modo]`; modo 0 = color clave 255, modo 1 = copia opaca usada para fondos,
minimapa y diálogos). Hotspot: los llamadores suman `hotX/hotY` (y +50 en las vistas de casillas:
`DrawTerrainTile`, `DrawSTileBuilding`, `DrawResourceIcon`). Port: `sprites::Clipper` + `blitSprite8` (sobre
`Video::blit8` o sobre una `Surface8`), `drawSpriteDef`, `drawSprite`, `drawSpriteCentered`.

## 4. Sistema ANIM (0x441000–0x446000)

150 objetos de 64 bytes en `DAT_00561a34`; lista activa doblemente enlazada ordenada por `z` (cabeza
`DAT_00561a30`, cola `DAT_00563fb4`), lista libre `DAT_00563fb8` (siempre queda un centinela: máximo 149
activos), rectángulo sucio `DAT_00561a20..2c` y lista de dibujados `DAT_00563fbc`.

```
+00 u16 flags   0x04 activo (ejecuta script), 0x08 (+0x04) = seleccionable por HitTest, 0x10 tiene padre
+02 i16 type    +04 i16 z    +06 i32 x  +0a i32 y   (punto fijo 24.8)
+0e i16 sx,sy   +12 i16 w,h  (último dibujo)
+16 SpriteDef* frame   +1a SpriteDef* frames   +1e i16 timer   +20 i16 rate
+22 i16 dx  +24 i16 dy  (por tick, 24.8)   +2a i16 moveDelay
+2c i16 var[4]  0 estado, 1 aux, 2 dirección (los hijos reinician su script cuando cambia la del padre), 3 índice del padre (propio al crear)
+34 u16* pc   +38 next   +3c prev
```

| Original | Port (`sprites::AnimSystem`) | Notas |
|---|---|---|
| FUN_00444e88 | `reset()` | memset + lista libre |
| FUN_00444a00 / FUN_00444ae4 | `alloc(z)` / `free()` | inserción ordenada por z; "Freeing an invalid ANIM." |
| FUN_00444f20 CreateAnim | `create(tipo, x, y, script)` | flags = tipo.flags\|4, z = 1, frame 0, timer 1, rate del tipo |
| FUN_00444fd4 | `kill()` | recursivo sobre hijos (flag 0x10 y var[3] == índice) |
| FUN_00444b74 | `setZ()` | reordena y marca rectángulos sucios |
| FUN_00445040 | `setState(estado, reiniciar)` | pc = script del tipo, timer = 1 |
| FUN_004451d4 | `setFrame(i)` | frame sin píxeles → frame 0; timer = rate |
| FUN_00445270 UpdateAnims | `update(ticks)` | intérprete + movimiento (dx/dy tras `moveDelay`) |
| FUN_00444cf4 DrawSprite | `drawSprite()` | sx = (x>>8)+hotX, o relativo al padre: `padre.sx - padre.hotX + hotX` |
| FUN_00445190 | `drawUpTo(desde, zMax)` | la vista de asentamiento intercala casillas y ANIMs por bandas de z (`z = fila*100 + 0x32/0x4b/0x63`) |
| FUN_00445100 / FUN_00445074 / FUN_004450e0 | `hitTest` / `addDirtyRect` / `resetDirtyRect` | |
| FUN_0046ca40 | `GameRandom` | `seed = seed*0x41C64E6D + 0x3039; (seed>>16)&0x7FFF` |

### 4.1 Scripts de animación

Región `0x00518D22–0x00519ECC` (2 261 palabras u16), 26 puntos de entrada desde la tabla de tipos más el script
de misiles `0x00519CCE` (forzado por FUN_0043d184/`DestroyAnim`). Cada tick, si `--timer < 1` se ejecutan
opcodes hasta uno que "termina el tick":

| Palabra | Op | Operandos | Efecto |
|---|---|---|---|
| `< 0x8000` | FRAME n | — | `setFrame(n)` (timer = rate); termina |
| `0x8001` | JUMP | ptr (u32) | pc = ptr |
| `0x8002` | SWITCH | reg, ptr[] | pc = tabla[var[reg]] |
| `0x8003` | LOOP | reg, ptr | si var[reg] ≠ 0: var[reg]--, pc = ptr |
| `0x8004` | STEPDOWN | reg, lo, hi, ptr | si frameActual ≠ var[reg]: setFrame(actual == lo ? hi : actual-1); pc = ptr; termina |
| `0x8005` | STEPUP | reg, lo, hi, ptr | igual con actual == hi ? lo : actual+1 |
| `0x8006` | SET | reg, valor | var[reg] = valor |
| `0x8007` | RANDOM | reg, lo, hi | var[reg] = lo + rand % (hi-lo+1) |
| `0x8008` | KILL | — | destruye el ANIM |
| `0x8009` | WAIT | n | timer = n; termina |
| `0x800a` | WAITVAR | reg | si var[reg] > 0: timer = var[reg]; termina |
| otro (`0x800b` aparece) | NOP | — | se salta una palabra |

Ejemplo (`0x518d22`, edificios): `RANDOM 0 0 3; SWITCH 0 [4 bucles]; FRAME 2..9; JUMP` → llamas de chimenea.
Las torretas (`0x518fd2`) usan `RANDOM 2 lo hi` + STEPUP/STEPDOWN para girar frame a frame hasta la dirección
`var[2]`. En el port los punteros están relocalizados a offsets de palabra (`{offset, 0xFFFF}`) en
`kAnimScript[]`; `data/sprites.json` incluye el desensamblado completo (`animScripts.listing`).

## 5. Ficheros del port

- `tools/extract_sprites.py` → `data/sprites.json`, `re/sprites/*.png`, `src/sprites/sprite_tables.{h,cpp}`.
- `src/sprites/sprite_tables.*` tablas estáticas (frames, tipos, tablas extra, scripts, paletas, listas, edificios/unidades).
- `src/sprites/sprite_palette.*` `makeGamePalette`; `sprite_bank.*` cargador; `sprite_draw.*` blit/clip; `anim.*` ANIM.
- `dl2tool sprite-list [filtro] | render-sprite <tabla> <i> <bmp> [planeta] | sprite-sheet <tabla> <bmp> [planeta] | anim-demo <tipo> <ticks> <bmp>`
  (`DL2_GAME_DIR` para la ruta del juego). `<tabla>` = número, nombre (`Bldg_Factory`) o `extra:<nombre>`.

## 6. Mapa de funciones (resumen; completo en `re/names_sprites.tsv`)

| Dirección | Nombre | |
|---|---|---|
| 0x0046ca70 | ReadDataFileChunk | lectura cruda |
| 0x00483098 / 0x00483038 | ReadTypeFrames / RemapSpritePixels | carga y remapeo |
| 0x004836fc / 0x00483340 / 0x00483600 | LoadPhaseSprites / LoadPhaseSpriteFile / LoadGlobalSprites | |
| 0x004658a8 / 0x00465ac8 / 0x00465b9c | LoadSettlementSprites / LoadControlSprites / LoadCombatSprites | |
| 0x0046338c / 0x004637b4 / 0x004639f4 | SetWorldPalette / BuildLogPalette / UpdateCYLibPalette | paleta |
| 0x00463d00 / 0x00463da8 / 0x004647a0 | SetClipRect / SelectSurface / BlitSprite8 | dibujo |
| 0x00444f20 / 0x00445270 / 0x00444cf4 / 0x00445190 | CreateAnim / UpdateAnims / DrawSprite / DrawAnimsUpTo | ANIM |
| 0x0047f9a0 / 0x0047f7a4 / 0x00480150 / 0x00480d78 | DrawTerrainTile / DrawSTileBuilding / DrawSettlementView / CreateSettlementAnims | vista de asentamiento |
| 0x0043ddcc / 0x0043d6e4 / 0x0043db88 | BirthCombatSprites / CreateHit / DestroyAnim | combate |
| 0x00487bec / 0x00466e60 | CreateWinGWindow / StillPic | imágenes fijas |

## 7. Pendiente / dudas

- Tablas extra no referenciadas por el decompilado (`Pictures1..8`, `TechPictures*`, `Icons32`, `TinyIcons`): se
  llegan seguramente por punteros calculados en los diálogos de tecnología; los nombres son provisionales.
- El 8.º registro de `PTR_DAT_004d0918` (tipo 138, `MapCity_Race7`) no corresponde a ninguna raza jugable.
- Los nombres `UnitIcons{A,Sea,Infantry,Vehicles}`, `Wreck0..5`, `TrooperAlt*` son inferidos de las imágenes.
- El opcode `0x800b` (presente en los datos) no tiene caso en el intérprete original; se salta una palabra.
- La tabla de trabajo inicial `0x51A8A4` difiere de la maestra en 200 entradas: parece una paleta heredada.
