# Deadlock II: Shrine Wars — Formatos de archivo (ingeniería inversa)

Todos los enteros son little-endian salvo que se indique. Verificado con `tools/camtool.py`
y con los decodificadores C++ de `src/formats/` (`dl2tool`) contra los archivos de la instalación GOG (v1.20).

## 1. Archivos `.HDX` / `.HDD` (archivo indexado simple)

Pares `BASE`, `LEVELS`, `CHAT`, `SCRIPT`, `DIFF`, `SOUND`. El EXE los abre con `"%s.HDX"` / `"%s.HDD"`.

```
HDX:
  u32  count
  struct { char name[8]; u32 offset; } entries[count]   // name con relleno \0 (sin terminador si mide 8), offset absoluto en el .HDD
HDD (en offset):
  u32  length
  u8   payload[length]
```

Contenido por archivo:

| Archivo | Entradas | Payload |
|---|---|---|
| BASE | 49 (`C0N`,`H3N`,`T7N`…) | BMP de Windows (retratos base de líderes, 41082 bytes cada uno) |
| DIFF | 3964 (`C01_1`, `C1CG_2`…) | BMP: expresiones/diferencias de los retratos (animación de "cabezas") |
| CHAT | 2084 (`CCACPTA`…) | texto ASCII terminado en `\0` (frases diplomáticas) |
| SCRIPT | 2037 | script de animación de cabeza: `nombre.wav\r\n<raza>\r\n<texto>\r\n<ruta origen>\r\n<n>\r\nBEGIN\r\n<frames…>\r\nEND` |
| SOUND | 2036 | audio PCM crudo: cabecera `PCMWAVEFORMAT` de 16 bytes (`u16 wFormatTag=1; u16 nChannels=1; u32 nSamplesPerSec=11025; u32 nAvgBytesPerSec=22050; u16 nBlockAlign=2; u16 wBitsPerSample=16`, sin `cbSize`) + muestras s16 (`formats/wave.h: decodeRawSound`) |
| LEVELS | 42 (`CHCHT1`…`UVA6`) | escenarios; mismo formato que `.SAV` (cabecera de texto de 88 bytes) |

Nombres: primera letra = raza (`C`=ChCh-t, `Y`=Cyth, `H`=Human, `M`=Maug, `R`=Re'Lu, `S`=Skirineen, `T`=Tarth, `U`=Uva Mosk, `O`=?).

Formato de línea de frame en SCRIPT: `<idx> <K|T> <n> <mouth> <cmd> <frameName>` — `K`=keyframe (usa BMP de BASE), `T`=transición (BMP de DIFF).

## 2. Paquetes `.CAM` (Cyberlore "CYLBPC")

`deadcyb.cam` (gráficos), `deadtext.cam` (menús/strings/fuentes), `deadanim.cam` / `deadcine.cam` (vídeo Smacker),
`dl2music.cam`, `dl2segue.cam`, `dl2sound.cam` (WAV).

```
u8   magic[8]  = "CYLBPC  "
u16  ver_major = 1
u16  ver_minor = 1
u32  num_sections
u32  directory_size              // tamaño total de los directorios de sección
struct { char tag[4]; u32 section_offset; } sections[num_sections]
// en section_offset:
u32  count
u32  flags                       // bit0: entradas sin nombre (name[0..3] = índice u32)
struct { char name[20]; u32 offset; u32 size; } entries[count]   // offset absoluto en el archivo
```

Los payloads son contiguos y siguen inmediatamente a los directorios. Lector C++: `formats/cam_package.h`
(lee los directorios al abrir y cada payload bajo demanda; `deadcine.cam` mide 102 MB).

IFF PBM (PICT tipo 2): `BMHD` big-endian (`u16 w; u16 h; i16 x; i16 y; u8 planes=8; u8 mask; u8 compr=1; …`),
`CMAP` 256×RGB, `BODY` ByteRun1; cada fila ocupa `w` redondeado a par (irrelevante con 640).

### Secciones y payloads

| Tag | Archivo | Payload |
|---|---|---|
| `PALT` | deadcyb | 1032 bytes: cabecera 12 bytes (`00 00 00 01 00 00 00 00 00 00 00 00`) + 255 × `RGBx` (índice 255 = blanco implícito). `TTIP`, `DPAL`, `DPL2` |
| `IMAG` | deadcyb | atlas de UI: `u32 type=2; u32 ?; u32 ?; u32 ?; u32 ?; u32 count; struct{u32 id; u32 offset;}[count]` seguido de subimágenes (ver TILE) |
| `TILE` | deadcyb (1953) | sprite (CYLib `img.c`/`pixel.c`, blit `FUN_0049aa95`): cabecera de shorts `[0]=type (1,2,3) [1]=h [2]=w [3]=pitch [4]=flags (bits0-1 = bytes/píxel-1) [5]=hotX [6]=hotY [7]=modo de dibujo por defecto (0..7)`, píxeles en `+0x1a`. type 2 = 8 bpp lineal con `pitch`; type 3 = codificado (RLE) que se decodifica por filas; type 1 = 16 bpp. El modo (0..7) selecciona una rutina de blit (normal, color clave, sombra, …) de las tablas `DAT_0069ee90/94/98` |
| `IMAG` | deadcyb (52) | pantalla compuesta de tiles: cabecera `u32 type=2; …; u32 count @+0x14; struct{u32 id; u32 offset;}[count] @+0x18` (id: 24 bits + flags en el byte alto; `FUN_0049698a`). Cada *layer* (`+0x10*4` tabla de offsets) tiene `+0x18 s16 offX, +0x1a s16 offY, +0x1c u16 rows, +0x1e u16 cols` y celdas de 8 bytes `{s16 x; s16 y; u32 tileId\|flags}` (bit30 = vacío; byte3 bit4 = oculto) que referencian `TILE` por id (`FUN_00496e80` dibuja la rejilla) |
| `PICT` | deadcyb | `u32 type`: `2` = IFF `FORM/PBM ` (Deluxe Paint, ByteRun1) 640×480 8bpp con CMAP propio (I000–I002); `1` = cabecera 48 bytes + 640×480×2 en **RGB555 (xRGB1555, bit 15 siempre 0)** con las filas **de abajo arriba** (orden DIB), I003–I008. Cabecera tipo 1: `u32 type=1; u16 0; u16 2; u32 0; u32 0; u16 w=640; u16 h=480; u16 0x0110; u16 basura; u8 pad[24]=0`. El EXE convierte 555→565 en tiempo de ejecución sólo si la superficie DirectDraw es 565 (comprueba máscaras `0xf800/0x7e0/0x1f` vs `0x7c00/0x3e0/0x1f`). Decodificadores: `formats/iff_pbm.h` |
| `PICT` | deadanim / deadcine | `u32 type=6` + vídeo Smacker (`SMK2`), 640×480 o 360×240 |
| `WAVE` | dl2*.cam | RIFF WAVE estándar (PCM) |
| `SMNU` | deadtext | definición de menú/pantalla: `u32 w=1000?; u32 2; …` referencias a `DL01` (fuente), `DPAL` (paleta), `MI00` (IMAG) |
| `STRT` | deadtext | tabla de strings: `u32 count; u16 offsets[count]; char strings[]` (offset relativo al inicio del payload, incluido el `count`: el primero vale `4+2*count`; `\0`-terminados). `formats/text_table.h` |
| `FONT` | deadtext | fuente bitmap propia: `u8 nameLen; char name[]; …` (`SM09`=small, `MI05`=Mini5, `DL01`=GCFont, `DL02`=CyberPlain, …) |

## 3. `SPRITENW.DAT` (11.5 MB)

Blob de píxeles 8 bpp sin cabecera (color clave 0 en el fichero; 255 tras el remapeo del cargador). El índice
(427 tipos × tablas `SpriteDef` de 16 bytes @ 0x004D02F4), los scripts de animación y la paleta del juego están
en el EXE: ver `docs/SPRITES.md`, `data/sprites.json` y `tools/extract_sprites.py`.

## 4. `.SAV` / `LEVELS.HDD` / `Campaign/*.CPN`

```
char header[88]  = "Deadlock 2  (c)1997 Accolade Inc.  All Rights Reserved.\nPre-release version XXXXXXXXXXX\0"
u32  version      // 0x30 = v1.20 en TUTORIAL.SAV, 0x26 en LEVELS
... estructura de GameState volcada tal cual (ver game/game_state.h cuando se reconstruya)
```

## 5. `DL2.PRF` (134 bytes) — preferencias

```
u8  flags[14]     // música, sonido, vídeo, animaciones, etc. (orden pendiente)
u16 ?, u16 ?
char playerName[..]   // "Apatuka"
...
```

## 6. Recursos del EXE

- 53 diálogos Win32 (IDs 5000–25300) volcados en `re/dialogs.txt` (Borland BWCC).
- 182 bloques de string table (2798 strings): textos de ayuda contextual (`NNMINT*`), mensajes.
- Exports Borland: `MainWndProc`, `IntroWndProc`, `BackWndProc`, `CustomWnd`, `WinGWndProc` y diálogos.
