# Formato de partida guardada (.SAV / .CPN / LEVELS.HDD / mapas del editor) — Deadlock II v1.20

Especificación derivada de `SaveGame` (`FUN_00461488`), `LoadGame` (`FUN_004618e8`) y sus 16 pares
escritor/lector (direcciones en `re/names_structs.tsv`). Los layouts en memoria están en
`src/game/game_state.h`; el validador `tools/savparse.py` reproduce esta lectura y se ha comprobado
contra `TUTORIAL.SAV`, `Saves\AUTOSAVE.SAV`, `Campaign\*.CPN` y las 42 entradas de `LEVELS.HDD`.

Todo es little-endian y **sin relleno**: el juego vuelca con `WriteFile` los bloques tal cual están en
la sección DATA del EXE (structs Borland empaquetados: `Unit`=0x122, `Army`=0x5c, `Territory`=0xadc…).
Los punteros de 32 bits que hay dentro de las estructuras se sustituyen al guardar por índices o IDs
globales y se reconstruyen al cargar (§ 4).

## 1. Cabecera (0x9C bytes) — `FUN_00461f74` / `FUN_00461ff4`

| Off | Tam | Campo | Valor |
|---|---|---|---|
| 0x00 | 88 | `text` | `"Deadlock 2  (c)1997 Accolade Inc.  All Rights Reserved.\nPre-release version XXXXXXXXXXX"` + `\0` |
| 0x58 | u32 | `version` | `DAT_004d5ae8` = **0x120** (v1.20) al guardar. Al cargar → `DAT_00583da8`; si es mayor que 0x120 se rechaza ("savefile from a newer version"). Los escenarios GOG tienen 35..68, `TUTORIAL.SAV` 48 |
| 0x5C | i32 | `isMap` | 1 = fichero de mapa del editor (§ 6); debe coincidir con `DAT_004d5a88` (cargando mapa) |
| 0x60 | i32 | 0 | |
| 0x64 | i32 | -1 | |
| 0x68 | 52 | relleno | los primeros 20 bytes a 0; el resto basura de pila |

El texto determina la **generación de formato** `DAT_00583da4` (`FUN_00461ff4`): texto actual → 4
(`DAT_004d1d3c`); `"…version S (7/21/97)"` → 0, `T (7/31/97)` → 1, `U (8/04/97)` → 2, `V (9/05/97)` → 3.
Todos los ficheros de la instalación son de generación 4. Las variantes antiguas se indican en cursiva.

## 2. Secuencia de bloques de una partida (`isMap == 0`)

| # | Escritor → Lector | Bytes | Global | Contenido |
|---|---|---|---|---|
| 1 | `FUN_0045f5e4`/`FUN_00461f74` → `FUN_0045f608`/`FUN_00461ff4` | 0x9C | — | cabecera (§ 1) |
| 2 | `FUN_0045f664`/`FUN_004620dc` → `FUN_0045f828`/`FUN_00462100` | 0xAC | varios | **GameOptions** (§ 3.1). *gen<4: 0x74 bytes; version<3: 0x88; version<7: 0xA6; version<9: 0xAA* |
| 3 | `FUN_0045fa10`/`FUN_00462308` → `FUN_0045fa34`/`FUN_00462328` | 0x14 | `DAT_004d5b10` | **WorldParams** (§ 3.2) |
| 4 | `FUN_0045fa4c` → `FUN_0045fae4` | 7×0x2D8 + lista | `DAT_0059f160` | **Player[7]** (§ 3.3) volcados tal cual (*gen<3: numPlayers×0x2D8*). Después, si `version ≥ 7`: la lista enlazada `Player[local].localList` como u32 por nodo, terminada en `0xFFFFFFFF` |
| 5 | `FUN_0045fd04` → `FUN_0045fd28` | 0x380 | `DAT_00559e00` | **RaceStats** `int16[64][7]` (modificadores por fila y raza; `FUN_00441128` los genera a partir de `DAT_004fc50c` según *Racial Abilities*). *version<0x23: 0x356 (gen 0) ó 0x364 bytes y las filas 61-63 se rellenan de `DAT_004fc8dc`* |
| 6 | `FUN_0045fe58` → `FUN_0045fecc` | 48×0x12 | `DAT_004fbbac` (paso 0x32) | **Tecnologías**: por entrada `u16 knownMask` (+0), `u16 availableMask` (+2), `u16 progress[7]` (+6) |
| 7 | `FUN_0045ff40` → `FUN_0045ff94` | 7 listas | `DAT_00522280` | **Trabajos de ministros** (IA): por jugador se escribe la cabecera de 0x44 bytes y, mientras el campo `next` (+0x14) del último registro escrito sea ≠ 0, otro nodo de 0x44. Los punteros van crudos; al cargar se re-enlazan (`next`/`prev` +0x18). *gen 0/1: no existe; se reinicializa* |
| 8 | `FUN_0046002c` → `FUN_004600d0` | n×(0xC+len) | `DAT_00651cb4`, n=`eventCount` | **Event Log**: `u16 type; u16 len (≤0x3FF); i32 player; i32 param;` + `len` bytes de texto sin `\0`. Al cargar sólo se reconstruye si `version == 0x120` (`FUN_004234d4` re-registra el texto) |
| 9 | `FUN_00460188` → `FUN_004601f0` | h×w×10 | `DAT_005a0550` | **Tiles**: fila a fila (`y<height`, `x<width`) 10 bytes cada uno (§ 3.4); en memoria las filas miden 400 bytes |
| 10 | `FUN_00460258` → `FUN_00460330` | 4 + n×0x122 | `DAT_005f0410` | `i32 n` = nº de **Building** con `type≠0`, seguido de esos n registros (§ 3.5). Punteros `prev` (+0x11A) y `next` (+0x11E) → ID global (u16 en +0 del apuntado). *gen 0/1: registros de 0x136* |
| 11 | `FUN_004605e0` → `FUN_004606f4` | 4 + n×0x5C | `DAT_00645370` | `i32 n` = nº de **Army** con `type≠0` (+6), y sus registros (§ 3.6). +0x38/+0x3C/+0x40 → `Territory::index` (u16 en +0x1A del apuntado); +0x48/+0x4C/+0x50/+0x54/+0x58 → ID global de Army |
| 12 | `FUN_00460870` → `FUN_00460a74` | por territorio | `DAT_005a43d0` | **Territory** `i = 1..numTerritories`: 0x9B2 bytes (= 0xADC − `DAT_004d1cf8`(0x12A)) + 5 colas (§ 3.7). *gen 0/1: 0x99A bytes y sin colas* |
| 13 | `FUN_00460fa4` → `FUN_00461078` | 0x10BF8 + 0x1C + 0xC4 + 0xC4 + 0x3440 | `DAT_00522584`, `DAT_0052222c`, `DAT_005220a4`, `DAT_00522168`, `DAT_0055a820` | **Jobs** (task forces IA) `Job[7][50]` con `destination` (+0x10) convertido a índice de territorio (`FUN_00460f24`) y `armies[16]` (+0x44) validados; `u32 aiWarMask[7]`; dos `Job` de trabajo; tabla de **continentes** `Continent[32]`. *gen<3: 0xC40 bytes de jobs; version<0x26: los jobs se leen pero se ponen a 0* |
| 14 | `FUN_004612b0` → `FUN_004612d4` | 700 | `DAT_00654804` | **RandomEvent[25]** (28 bytes: `i32 type; i32; i32 turnsLeft; i32[4]`). *gen<3: ausente* |
| 15 | `FUN_00461308` → `FUN_00461328` | 0x2A | `DAT_00657df4` | **PlayerScore[7]** (`i32 score; u8 nukesUsed; u8`). *version<0x11: ausente* |
| 16 | `FUN_0046136c` → `FUN_00461418` | 0x578 + 0x38 | `DAT_00654ac0`, `DAT_005644f8` | **Spy[7][25]** (`i16 owner, territory, mission, turns`) y **BlackMarketState[7]** (`i32 pending; i32 turn`; en partidas de red se escriben `{0,-1}`). *version<0x24: ausente* |

`LoadGame` no comprueba el final del fichero: varias entradas de `LEVELS.HDD` conservan bytes sobrantes de
versiones anteriores del mismo escenario (p. ej. `CHCHT3`: 276 bytes = 69 territorios × 4; `CHCHT1`:
135 614 bytes), que el juego ignora.

Tras leer, `LoadGame` llama a `FUN_0046147c` (= `FUN_0044cabc` reconstruye las listas activa/libre de
edificios + `FUN_00445710` la lista libre de ejércitos), compara `WorldParams` con la copia previa,
`FUN_004ae594(rngSeed)` (srand), `FUN_0046a844` ("Preparing Long Range Scan"), y limpia `Territory::flags &= 0xFFF0`.

## 3. Estructuras

### 3.1 GameOptions (0xAC) — `FUN_0045f664` / `FUN_0045f828`; mismos offsets que el parser de `[Scenario Options]` (`FUN_00471170`)

| Off | Tipo | Global | Campo | Evidencia |
|---|---|---|---|---|
| 0x00 | i32 | `DAT_0059f154` | `turn` | "Turn %3d" (DEBUG.TXT); `SaveGame` pone 1 en modo editor |
| 0x04 | u32 | `DAT_0059f158` | `gameSeed` | `ResetVariables`: `FUN_0046c9cc("GameSeed")` |
| 0x08 | i32 | `DAT_0059f15c` | `gameId` | `FUN_0046c9d8(10000,"SaveGame")` al guardar; `FUN_00477394` lo aplica como semilla (`srand`) o lo difunde por red (msg 0x4b) |
| 0x0C | i32 | `DAT_004d5aec` | `numPlayers` | INI `Players` (2..7) |
| 0x10 | i32 | `DAT_004d5af0` | `winCities` | INI `Win Cities` ∈ {2,3,5,7,10} (`DAT_004c425c`); "Cities" en DEBUG.TXT |
| 0x14 | i32 | `DAT_004d5af8` | `winShrines` | INI `Win Shrines`; "Shrine Conditions : %d for %d turns" |
| 0x18 | i32 | `DAT_004d5afc` | `winTurns` | INI `Win Turns` |
| 0x1C | u8 | `DAT_004d5b00` | `victory` | 0 Manifest Destiny, 1 Conquest, 2 Shrine Wars (`DumpGameOptions`) |
| 0x1D | u8 | — | relleno | |
| 0x1E | i32 | `DAT_004d5b08` | `fastProduction` | INI `Fast Production` |
| 0x22 | i32 | `DAT_004d5b04` | `randomEvents` | INI `Random Events`; `CreateRandomEvents` lo exige |
| 0x26 | i32 | `DAT_004d5b0c` | `aiSkill` | INI `AI Skill Level` (0..4; al cargar se acota a 0..4) |
| 0x2A | 16 | — | reservado | ceros (*formato antiguo: 8×u16 contadores de ID, cuyo máximo pasa a `nextGlobalId`*) |
| 0x3A | u32 | `DAT_004d5b24` | `netFlags` | bit 0 alternado en `FUN_0047d2f0` |
| 0x3E | i32 | `DAT_0058f1f4` | `localPlayer` | sólo se restaura si `LoadGame(param_2 != 0)` |
| 0x42 | i32 | `DAT_00651cb0` | `eventLogFirst` | primer evento visible (`FUN_00403310`) |
| 0x46 | i32 | `DAT_0065209c` | `eventCount` | nº de entradas del bloque 8 (≤ 50) |
| 0x4A | i32 | `DAT_004d5b2c` | `autoTimer` | INI `Auto Timer` |
| 0x4E | i32 | `DAT_004d5b28` | reservado | sólo save/load (0x7F en todos los ficheros) |
| 0x52 | i32 | `DAT_004d5b30` | `autoTimerClock` | INI `Auto Timer Clock` (3..960 s; 300 por defecto en red) |
| 0x56 | i32 | `DAT_004d5b34` | `lastPlayerTimer` | INI `Last Player Timer` (excluyente con `autoTimer`) |
| 0x5A | i32 | `DAT_004d5b38` | `lastPlayerClock` | INI `Last Player Clock` (3..960 s) |
| 0x5E | i32 | `DAT_004d5b3c` | `racialAbilities` | INI `Racial Abilities`: 0 standard, 1 best, 2 none (`FUN_00441128`) |
| 0x62 | 4 | — | reservado | |
| 0x66 | u16[7] | `DAT_0065e42c` | `hasWon` | =1 cuando el jugador cumple la victoria (`FUN_00486e34`) |
| 0x74 | i32 | `DAT_004d5a90` | `worldResources` | INI `World Resources` (`FUN_004669d8`) |
| 0x78 | i32 | `DAT_004d825c` | `nextGlobalId` | `FUN_00474cfc` lo incrementa y trunca a u16 (IDs de Building/Army) |
| 0x7C | i32 | `DAT_004d5a94` | `campaign` | índice de campaña (0 = ninguna); decide `saves\` vs `campaign\` |
| 0x80 | u8[7] | `DAT_005a0548` | `playerSkill` | "Player Name (Skill Level)"; 2 por defecto |
| 0x87 | u8 | `DAT_0059f0fc` | `playersMask` | bit i = jugador i presente |
| 0x88 | i32[7] | `DAT_0065e404` | `shrineTurns` | turnos consecutivos cumpliendo Shrine Wars |
| 0xA4 | u8[3] | tabla campaña | `campaignBytes` | `*(u32*)(DAT_004c61e0 + camp*0xD8 + k*0x44)` (k=0..2), truncados a byte |
| 0xA7 | u8 | — | relleno | |
| 0xA8 | i32 | `DAT_004d5af4` | `allowAlliances` | INI `Allow Alliances`; si 0 se borran `Player::relations` |

### 3.2 WorldParams (0x14) — `DAT_004d5b10..23`

`u32 seed1` (+0), `u32 rngSeed` (+4, `srand` al cargar), `u16 numTerritories` (+8, `DAT_004d5b18`),
`u8 width` (+0xA), `u8 height` (+0xB), `u8 worldType` (+0xC, 0..5), `u8 terrainPct[6]` (+0xD: % de
Sea/Plains/Forest/Swamp/Mountains/Wasteland, suman 100), `u8 numColonySites` (+0x13, = tamaño×2+12).

### 3.3 Player (0x2D8) — `DAT_0059f160 + i*0x2D8`

| Off | Tipo | Campo | Evidencia |
|---|---|---|---|
| 0x000 | u8 | `index` | `FUN_00474718`: `Player[i]+0 = i` |
| 0x001 | u8 | `type` | 0 ninguno, 1 humano local, 2 humano remoto, ≥3 IA (`FUN_0045add0` cuenta 0<type<3) |
| 0x002 | i8 | `race` | 0 ChCh't, 1 Cyth, 2 Human, 3 Maug, 4 Re'lu, 5 Tarth, 6 Uva Mosk (`PTR_s_ChCh_t_00509038`) |
| 0x004 | u16 | `netId` | `BroadcastDirect`/`BroadcastText` |
| 0x006 | i16 | `homeTerritory` | `FUN_0046d2e8` (= `Territory::index` del aterrizaje) |
| 0x008 | u8 | `turnDone` | `SyncBeginTurn`, `RunAITurns` |
| 0x009 | u8 | `foodFlags` | bits de hambruna (`ConsumeFood`, `FUN_0046b818`) |
| 0x00A | u8 | `scandals` | `FUN_0047d49c` ("Scandal") |
| 0x00B | i8 | `taxLevel` | índice en `DAT_004d57ec` (2 por defecto) |
| 0x00C | i32 | `credits` | "%d Cr." (`FUN_00432fc0`); 500 iniciales |
| 0x038 | u8 | — | 0x7F al crear |
| 0x03A | ptr | `localList` | lista `{u32 val; next}` sólo del jugador local (bloque 4) |
| 0x03E | i8 | `currentResearch` | tecnología en curso (`FUN_0046ac44`) |
| 0x040 | i16 | `lastIncome` | `FUN_0046ac44` |
| 0x046 | 4×ptr + 2×u32 | IA | tabla de personalidad `PTR_DAT_004b502c[type*6]` (`FUN_00401830`, se reconstruye al cargar) |
| 0x05E | 6×0x5A | `ministers[6]` | `{u8 index; u8; fnptr[4]; …}` con punteros a función → **no válidos tras cargar**; `FUN_00401830` los regenera para las IA |
| 0x27A | u32[7] | `relations` | máscaras de pactos (`FUN_004412d4`: bit 4 = ?, 0x1E = tipos de pacto) |
| 0x296 | u32[7] | `relations2` | segunda máscara (`FUN_004415d0`) |
| 0x2B3 | char[33] | `name` | "New Player" / nombre de líder IA `PTR_s_Sting_00509938[race]` |
| 0x2D4 | i32 | `defeated` | ≠0 → puntuación 0 (`CalculatePlayersScores`); se limpia al empezar campaña |

### 3.4 Tile (10 bytes) — `DAT_005a0550 + y*400 + x*10`

`u8 x; u8 y; i16 territory; u8 borderFlags` (bits de frontera, `FUN_0046237c`); `u8 terrain` (0..6, tabla
gráfica `DAT_004d553c`); `u8 overlay; u8; i16 pathCost` (temporal, 0x7FFF).

### 3.5 Building (0x122) — `DAT_005f0410 + i*0x122` (`FindBuildingByGlobalID` = `FUN_004750c4`)

| Off | Tipo | Campo | Evidencia |
|---|---|---|---|
| 0x000 | u16 | `id` | ID global |
| 0x002 | u16 | `flags` | bit1 construido, bit2 activo, bit5 obra ("Construction Site"), bits 8..12 tareas |
| 0x004 | u8 | `type` | `BuildingType` (0 libre; 0x25 City Center, 0x26 Sea Platform, 0x2D..0x2F shrines) |
| 0x005 | u8 | `category` | copia de `BuildingTypeDef+7` |
| 0x006 | u8 | `race` | raza del dueño (viviendas/hub) |
| 0x007 | i8 | `site` | casilla 0..35 |
| 0x008 | i16 | `territory` | índice del territorio |
| 0x00C | i16 | `hubLevel` | sólo City Center |
| 0x00E | i8 | `minister` | "Run By" |
| 0x014 | i16 | `turnsLeft` | 0 = terminado |
| 0x018 | i32[5] | `labor` | "Labor Assigned %d/%d" |
| 0x02C | u8[5] | `task` | `BuildingTask` por ranura |
| 0x03E | i32[11] | `cost` | dinero/materiales ya entregados; `004720f4` acumula, demolición devuelve la mitad |
| 0x06A | i32[4][11] | `taskData` | |
| 0x11A | ptr | `prev` | → ID global al guardar |
| 0x11E | ptr | `next` | → ID global al guardar |

### 3.6 Army (0x5C) — `DAT_00645370 + i*0x5C` (`FindArmyByGlobalID` = `FUN_0047510c`; `FUN_00445d30` crea)

`u16 id` (+0); `u8 type` (+6, `UnitType`, 0 = libre); `u8 unitClass` (+7); `i8 owner` (+8); `u8 strength`
(+0xA); `char name[24]` (+0xB, "%s %s #%d"); `u8 moves` (+0x24); `u8 health` (+0x26, 100); `i16 experience`
(+0x28); `i16 job` (+0x36, índice+1 del Job; el cargador lo reasigna); `Territory* territory/dest/origin`
(+0x38/+0x3C/+0x40 → índice); `ptr` (+0x44, se pone a 0); `Army* cargo[3]` (+0x48 → ID); `Army* next/prev`
(+0x54/+0x58 → ID). Listas por territorio: `Territory::armies` (+0x76, propios) y `foreignArmies` (+0x7A).

Los nombres físicos anteriores son **aliases legacy**, conservados por compatibilidad
binaria y con las claves JSON de `savparse.py`; no describen todos su significado.
`game/army_state.h` ofrece lecturas semánticas de los registros del documento:

| Offset | Campo físico | Getter | Significado demostrado |
|---|---|---|---|
| +0x0A | `strength` | `movementPoints` | Movimiento restante, no fuerza de ataque |
| +0x24 | `moves` | `combatOrders` | Código de orden de combate, no movimiento |
| +0x26 | `health` | `retreatThreshold` | Umbral de retirada (% de defensa perdida), no salud restante |
| +0x38 | `territory` | `turnStart` | Territorio al inicio del turno, base del coste de movimiento |
| +0x3C | `dest` | `current` | Territorio actual/enlazado, no destino pendiente |
| +0x40 | `origin` | `routeOrigin` | Origen/ancla amiga de ruta, no necesariamente el territorio anterior |

`ReLinkArmy` (`00445898`) escribe +0x3C; `DeleteUnit` (`00445fd4`) usa ese
territorio para retirar la unidad de su lista. `MoveUnit` (`00446084`) calcula
el coste desde +0x38, cambia +0x3C y actualiza +0x0A; `004471c0` copia +0x3C a
+0x38 y +0x40 al restablecer movimiento. Su parámetro de origen procede de la
ruta evaluada por `00401ac0`. `00447a68` copia +0x24 a la orden del combatiente.
El panel de órdenes (`00417c00`/`00418f74`) escribe/lee +0x26 con las opciones
0/25/50/75/100; el daño acumulado está en +0x2C (`00451b68`/`004526b0`).

Comprobación del corpus local: las 504 unidades enlazadas en 46 documentos
coinciden con +0x3C. En `Campaign/ChCht001.CPN`, Army 8204 está en la lista del
territorio 4, con +0x38=15, +0x3C=4 y +0x40=15. No se deben agrupar unidades
por +0x38 ni derivar su salud a partir del umbral de retirada.

### 3.7 Territory (0xADC) — `DAT_005a43d0 + i*0xADC`; se guardan 0x9B2 bytes + colas

| Off | Tipo | Campo | Evidencia |
|---|---|---|---|
| 0x000 | char[25] | `name` | "%s Landing", "Morale in %s" |
| 0x01A | u16 | `index` | índice propio (destino de los punteros convertidos) |
| 0x01C | u32 | `flags` | 0x10 shrine colocado, 0x100 sin tiles, bit8 (`+0x1D & 1`) inválido; `LoadGame` hace `&= 0xFFF0` |
| 0x020 | i8 | `owner` | -1 ninguno |
| 0x021 | u8 | `terrain` | 0 Sea, 1 Plains, 2 Forest, 3 Swamp, 4 Mountains, 5 Wasteland |
| 0x022 | i8 | `continent` | 0..31 (`FUN_004423b4`) |
| 0x026 | i8 | `tradeState` (alias histórico) | ajuste local del **nivel fiscal**: `FUN_0046adac` lo suma a `Player::taxLevel` y limita a 0..5 |
| 0x027 | i8 | `morale` | "Morale in %s"; 100 inicial |
| 0x02A | i16 | `taxAdjust` (alias histórico) | valor monetario mostrado por `FUN_00436a44` y agregado por `FUN_0046ab18`; **no** es el byte de nivel fiscal |
| 0x02E | i16 | `tradeIncome` | `FUN_0046ab18` |
| 0x030 | i16 | `population` | "Population %d/%d" |
| 0x035 | u8 | `knowledge` (alias histórico) | porcentaje de energía disponible: `FUN_0046bc28` lo actualiza; producción lee el byte con signo; =100 al colonizar / en editor |
| 0x038 | i16 | `knownPopulation` | última población vista |
| 0x03A | i32[11] | `materials` | Money, Food, Energy, Wood, Iron, Steel, Endurium, Triidium, Electronic Parts, Anti-Matter Pods, Art |
| 0x066 | u8[7] | `visibility` | por jugador: >2 visible, 4 = propio |
| 0x074 | i8 | `centerTile` | índice en `tiles[]` |
| 0x075 | i8 | `secondTile` | |
| 0x076 | ptr | `armies` | → ID de Army |
| 0x07A | ptr | `foreignArmies` | → ID de Army |
| 0x07E | u8 | `numTiles` | ≤ 48 |
| 0x080 | ptr[48] | `tiles` | → `x \| (y<<16)`; al cargar `&Tiles + y*400 + x*10` |
| 0x140 | 36×0x34 | `sites` | `BuildingSite`: bytes x/y (+0/+1, índice%6 e índice/6), `u16 terrainFlags` (+2, bits 0-3 terreno), `u8 value` (+4), `Building*` (+0x14 → ID global) |
| 0x890 | u16[7] | `adjacency` | máscara de 112 bits de territorios adyacentes (simétrica) |
| 0x89F | u8 | `freeSites` | |
| 0x8A0 | u32 | `adjContinents` | |
| 0x8A8 | u32 | `exploredMask` | jugadores que lo han explorado |
| 0x8AC | u32 | `coastal` | 0/1 |
| 0x99A | ptr[5] | `queues` | punteros a 5 `QueueHead {ptr first; ptr cursor}` en heap (`malloc(8)`); van crudos y se reconstruyen |
| 0x9AE | u8 | `hoverway` | `FUN_0044c3fc`; 0 en formato antiguo |
| 0x9B0 | u16 | `portTarget` | `FUN_0044da3c` |
| 0x9B2.. | — | **no se guarda** | `colonyFlag`, datos de IA, `production[11]` (+0xA7E), `consumption[11]` (+0xAAA) |

Tras los 0x9B2 bytes se escriben las **5 colas** (`FUN_004607d8`/`FUN_004609e8`): por cola `u8 n` y `n`
registros de 0x30 bytes (`u8 unitType; u8; u16 count; i32 data[11]`); en memoria cada nodo mide 0x34
(`next` en +0x30, `FUN_00484da8`). En modo editor (`DAT_004d5aa0 ≠ 0`) `knowledge` se fuerza a 100.

Los nombres heredados de los dos arrays no persistentes están invertidos:
`production` (+0xA7E) es demanda/reserva/scratch para importar materiales
(`0046b9a0`, `00472974`), mientras `consumption` (+0xAAA) acumula el saldo
producido en la consulta de `0044f3f0`. No se deben leer como previsiones guardadas.
Las coordenadas de casilla sí están en el archivo: `0046686c` genera x=índice%6,
y=índice/6 y `00460a74` las carga sin normalizarlas. Una huella de producción se
extiende hacia x creciente e y decreciente. Véase `ECONOMY_LAB.md`.

### 3.8 Job / task force (0xC4) — `DAT_00522584 + player*0x2648 + j*0xC4`

`i32 goal` (+0, `TaskForceGoal`: NO_TF_GOAL, RESERVE, LAND_EXPAND…); `i32 status` (+4, NEED_SPACE…);
`i16 targetPlayer` (+8); `i16 owner` (+0xA); `i16` (+0xC); `i16` (+0xE); `Territory* destination` (+0x10);
`i32 strengthWanted` (+0x14); `u16 armyIds[16]` (+0x24); `Army* armies[16]` (+0x44); `i32 parentJob` (+0x84).

### 3.9 Trabajo de ministro (0x44) — listas en `DAT_00522280`

`i32 type` (NULL_JOB, HEAD_JOB, CREATE_BLDG, BUILD_BLDG, FILL_TASKFORCE, CREATE_UNIT, BUILD_UNIT,
LEARN_TECH, GET_MATERIAL, MAINTAIN_MORALE, GROW_POPULATION, HEAL_PLAGUE, STOCKPILE, MAINTAIN_UNIT);
`i32 minister` (DEFENSE, WAR, GOVERNMENT, ECONOMIC, TECH, LABOR); `i32 priority`; +0x14 `next`; +0x18 `prev`;
+0x1C..0x24 parámetros.

## 4. Conversión puntero ↔ índice

| Estructura / campo | Al guardar | Al cargar |
|---|---|---|
| `Building::prev/next` | `*(u16*)ptr` = `Building::id` | `FindBuildingByGlobalID(id)` (`FUN_004750c4`, recorre `DAT_005f0410`) |
| `Army::territory/dest/origin` | `*(i16*)(ptr+0x1A)` = `Territory::index` | `&DAT_005a43d0 + idx*0xADC` (en `FUN_00460a74`, tras leer territorios) |
| `Army::cargo[3]/next/prev` | `Army::id` | `FindArmyByGlobalID` (`FUN_0047510c`) |
| `Territory::armies/foreignArmies` | `Army::id` | `FindArmyByGlobalID` |
| `Territory::tiles[i]` | `Tile::x \| Tile::y<<16` | `&DAT_005a0550 + y*400 + x*10` |
| `BuildingSite::building` | `Building::id` | `FindBuildingByGlobalID` |
| `Territory::queues[k]` | crudo (se ignora) | `malloc(8)` + `FUN_00484c2c` (cabecera vacía) + nodos leídos (`FUN_00484da8`) |
| `Job::destination` | `(ptr − DAT_005a43d0) / 0xADC` (`FUN_00460f24`; se deshace tras escribir con `FUN_00460f68`) | `FUN_00460f68` |
| `Job::armies[i]` | crudo (`FUN_0040aebc` invalida los que no coinciden con `armyIds`) | `FindArmyByGlobalID(armyIds[i])` y `Army::job = i+1` |
| `Player::localList` | valores u32 + `-1` | nodos `malloc(8)` |
| `MinisterJob::next/prev` | crudo | reencadenados al leer |
| `Player::ministers[].fn`, `aiVtbl` | crudo (punteros a código) | `FUN_00401830(i)` para cada IA (`LoadGame(param_2≠0)`) |

IDs globales: `FUN_00474cfc` (`DAT_004d825c++`, truncado a u16); los ficheros GOG tienen IDs de 8192
en adelante. `FindBuildingByGlobalID`/`FindArmyByGlobalID` devuelven NULL (y escriben en DEBUG.TXT) si
no lo encuentran, por lo que un ID inexistente se convierte en puntero nulo.

## 5. Post-carga (`LoadGame`)

1. `ResetVariables` (`FUN_0046da14`) antes de leer: pone a 0 todos los arrays.
2. Tras los 16 bloques: `FUN_0046147c` reconstruye listas de edificios/ejércitos; `FUN_00401830` para las
   IA; `FUN_00486964` recuenta shrines; `DAT_0065e424 = winCities`; si `autoTimer` arranca el reloj
   (`FUN_0045efd0(autoTimerClock)`); en red se reenvía `gameId`; si `turn == 1` y hay campaña se muestra
   la intro (`FUN_0042f0c4((camp−1) % 6)`).
3. En `Player`: si `version < 7` se regeneran los nombres ("New Player" / líder IA). Si `version < 4`
   o (campaña y turno 1) se recalcula `playersMask` y se limpia `defeated`. Al cargar con `param_2 ≠ 0`
   (partida nueva desde escenario) `FUN_00461078` convierte los jugadores tipo 1/2 ≠ local en IA (3)
   salvo en modo editor.

## 6. Variante de mapa del editor (`isMap == 1`) — `SaveGame` con `local_8 ≠ 0`

```
SaveHeader (0x9C, isMap = 1)
WorldParams (0x14)
MapTerritory[numTerritories]  (0xAA cada uno, FUN_00460d84):
    char name[25]      Territory::name (strcpy; resto basura)
    u8   terrain       Territory+0x21
    36 × { u16 terrain (BuildingSite+2 & 0xF); u8 value (BuildingSite+4); u8 pad }
Tile[height][width]  (10 bytes cada uno, FUN_00460188)
```

El cargador de mapas es `FUN_00461c68` (usa `FUN_0045f608`, `FUN_0045fa34`, `FUN_004601f0`).

## 7. Contenedores

- `saves\*.SAV`, `campaign\*.CPN` (campaña; también `%sBackup.bak` antes de sobrescribir),
  `Custom\`/`Maps\` para mapas. Nombre automático `"%s%03d"` con la raza corta (`ChCht`, `Cyth`, `Human`,
  `Maug`, `ReLu`, `Tarth`, `UvMsk`) + turno.
- `LEVELS.HDX/HDD`: `u32 count; {char name[8]; u32 offset}[count]`; en el HDD `u32 length` + payload,
  que es un `.SAV` completo (42 escenarios `CHCHT1`…`UVA6`, versiones 35..68).
