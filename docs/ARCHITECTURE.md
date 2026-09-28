# Arquitectura del DEADLOCK.EXE original (v1.20) — mapa de ingeniería inversa

Binario PE32, Borland C++ 5.x (TLINK 2.25), base 0x400000, sección CODE 0x401000–0x4B5000 (737 KB).
Proyecto Ghidra: `ghidra_project/DL2.gpr` (spec `x86:LE:32:windows`; ver nota abajo).
Exportación completa del decompilado: `re/decomp/<addr>_<nombre>.c`, índice `re/functions.jsonl`.

## Regiones de código

| Rango | Funciones | Contenido |
|---|---|---|
| 0x401000–0x487000 | 2 561 (520 KB) | **Juego** ("Xeno"): lógica, UI SMenu, diálogos Win32, red |
| 0x487000–0x49B000 | 591 (73 KB) | **CYLib** (Cyberlore Game library): `cygame` (ventana "CYGame"/"Cyberlore Game"), `offport.c` (superficies off-screen DirectDraw/DIB), `pixel.c` (blits), `img.c` (IMAG/TILE), `font.c`, `cylib.c` (gestor de paquetes CAM + *translators* por tipo), `bread.c` (lector binario), `glsound.c` (DirectSound/waveOut), memoria (`Memory Manager`, `Native memory manager`), reloj, teclado/ratón, `err.log`, Smacker |
| 0x49B000–0x4B5000 | 819 (91 KB) | **RTL Borland C++** (malloc/free, stdio, string, qsort, EH) + el sistema **SMenu** (`Disposed SMenu %c%c%c%c`, `Could not set font for item ID %d`) en 0x49B000–0x4A7000 |

### RTL identificada (por comportamiento)

| Dirección | Función |
|---|---|
| 0x4B02DC | `malloc` |
| 0x4B0274 | `free` |
| 0x4AA074 | `fopen` |
| 0x4A9BE0 | `fclose` |
| 0x4AA33C | `fread` |
| 0x4AB450 | `sprintf` |
| 0x4A6994 | `strlen` |
| 0x4A6838 | `memset`/fill (138 B, 142 llamadores) |
| 0x4A67C8 | `memcpy` |
| 0x4B14E8 | `qsort` |
| 0x4B1210 | `__assertfail` ("Assertion failed: , file , line ") |

## Flujo principal (WinMain = `FUN_00470804`)

```
WinMain
  FindWindowA("XenoMainWnd")            → si ya existe, SetForegroundWindow y salir
  FUN_004586f4  InitDebugLog            → DEBUG.TXT / COMBAT.TXT / REPLAY.TXT
  FUN_0046fa7c / FUN_0046fae4           → FindCD, comprobaciones iniciales
  FUN_0046cb4c  RegisterClasses         → "XenoMainWnd", "XenoBackground", "XenoIntro" (+ "XenoWinG" en CYLib)
  FUN_0046cc6c  CreatePalette/InitGDI
  FUN_0046cca4  CreateMainWindow        → "Deadlock 2: Shrine Wars", acelerador, bitmap de fondo
  FUN_0046fca4  InitCYGame              → DirectDraw (FUN_0048b623), sonido, temporizador
  FUN_00467078  LoadPrefs (DL2.PRF)
  FUN_00487bdc / FUN_00487b80           → LoadSmacker (SMACKW32.DLL)
  FUN_00470050  OpenDataFiles           → HDX/HDD (FUN_00411e28), "CYHMRTUOSchat", diccionario
  bucle de partidas:
     FUN_0046ffec  Intro window (XenoIntro) → menú principal
     FUN_00425690 / FUN_00465e54          → PreloadSprite2 / LoadGlobalSprites
     FUN_00470554  GetGameOptions        → red, nombre jugador, opciones
     FUN_00469074  NewGame/LoadGame      → si falla, salir del bucle
     FUN_0046d4ac  RaceInit / landing
     FUN_00458840  DumpGameOptions       → bloque "Players/World W./…" del DEBUG.TXT
     bucle de turnos (mientras !gameOver):
        FUN_0045add0  ProcessTurnEvents
        FUN_0046ed64  SyncBeginTurn      (WaitSync en red)
        FUN_0046f804 / FUN_0046c780 / FUN_0046eea0   fases de logística / producción / mar
        FUN_0045f2d8  AI turns ("Your silicon-based opponents…")
        FUN_00470740  autosave
        FUN_00405378  (ministros / IA)
        FUN_004238c8  combate,  FUN_0046ee88, FUN_004878a8 (bomba de mensajes CYLib)
        FUN_0047c730  eventos aleatorios (Plague/Flood/Earthquake…), FUN_00485668 espionaje
        FUN_00457624  fin de turno, FUN_0044b9e4, FUN_00486e34 victoria
        red: FUN_0046e9f4 WaitSync, FUN_0047b3a8 SyncGame, FUN_00427ee8/FUN_00427eb4
     FUN_00467754  SavePrefs
  FUN_0046ced4  Shutdown
```

Las cadenas del `DEBUG.TXT` ("Turn %3d: <fase>") se escriben con `FUN_004587f0(tag)` justo antes de
cada fase, lo que permite nombrar las funciones de fase con su nombre original.

## Módulos del juego (por rango de direcciones y strings)

| Rango | Módulo (nombre original inferido de las aserciones) |
|---|---|
| 0x401000–0x40A000 | Ayuda contextual, diálogos de depuración de ministros (`DebugMinisterDialog`, `DebugJobsDialog`: "Job Type / Minister / Priority") |
| 0x40A000–0x410000 | Task forces (`RemoveArmyFromTaskForce`, `TaskForceDialog`), misiones ("No Destination", "No Enemy") |
| 0x410000–0x413000 | Lectura de datos: HDX/HDD, parser de scripts (`tmp.sct`, `BEGIN`), audio waveOut (`FUN_00412f74`), temporizador |
| 0x413000–0x41A000 | Editor de escenarios ("Specify Ter", landing sites), morale (`Morale in %s`), estadísticas de unidades (ROF, rango) |
| 0x41A000–0x420000 | UI de edificios y colas de producción (`SetItemStats`, `CheckBuildingList`, "Iron -> Steel"), chat personalizado, Colony Assistant (`DrawCAGuyPool`) |
| 0x420000–0x426000 | Colony Assistant, informes de combate (`CombatReport`), Event Log (`CheckEventLog`), pantalla de apertura ("NNOPENA") |
| 0x426000–0x430000 | Landing (selección de sitio), mensajes de usuario (`UserMessageObject`), pactos ("Proposing a %s pact"), selección de raza/dificultad, alta puntuaciones, puertos |
| 0x430000–0x437000 | Mercado negro Skirineen (`CheckSubRes/SubInfo/SubTech`), nombre de jugador |
| 0x437000–0x43B000 | Comercio ("Selling Materials"), lista de unidades, guardar/cargar mapas (`custom\`, `maps\`), detalle de tecnologías |
| 0x43B000–0x43F000 | Colocación de edificios, `MainInterface` (`DisableMainInterface`), visor de combate (`PauseWarrior`, `CreateHit`, `CheckViewCombat`) |
| 0x441000–0x446000 | Gestor de memoria del juego, sistema de sprites/animación (`DrawSprite`, ANIM), ejércitos (`DeleteArmy`, `freeArmies`) |
| 0x446000–0x453000 | Unidades: movimiento, misiles, cruceros, Shrines (`DetectsShrine`), trabajo (`TotalUnitLabor`), edificios (`_SetBuildingFlags`, `FindConstructionSite`, `ProduceUnits`, `GetBuildingTasks`), retirada (`SetRetreat`) |
| 0x457000–0x45A000 | Combate, red (CGNet: "Deadlock 2 Host/Player"), log de depuración |
| 0x45A000–0x460000 | Carreteras, demolición, misiles, minas, fin de investigación, turno IA |
| 0x461000–0x463000 | Guardar/cargar partidas y campañas (`SaveGame`, `saves\`, `campaign\`), generación de mundo (WorldSeed, "Launching Colony Ship") |
| 0x463000–0x467000 | Capa gráfica GDI/DirectDraw del juego (`ClipBlit`, paletas), sprites (`SPRITENW.DAT`), alta puntuaciones (`hiscore.dat`), colocación ("Place3/4/5", "RemoveB") |
| 0x467000–0x471000 | Arranque, prefs (`DL2.PRF`), NetAccolade, `deadlock.ini`, población (`_MovePopulation`, `ConsumeFood`, `DoRiot`, Revolt), sincronía de red (`WaitSync`), efectos de mar, WinMain |
| 0x471000–0x47E000 | Opciones de escenario (INI: "File Type/saved_game/map_file"), ministros ("Collect Material"), tecnologías, cheats ("PILE IT ON", "GREEBLIE"…), editor de recursos, mensajes de red (`NetBuildingTasks`, `MasterDispatchNetMessage`, `ResetNetGame1`, `CalculateGameCRC`, `SyncGame`, `NetStartState`), eventos aleatorios (Plague, Earthquake, Flood, Bonus) |
| 0x47E000–0x487000 | Dibujo de la vista de asentamiento (`DrawSTileBuilding`), mini-mapa ("Mini Ter"), puntuaciones (`CalculatePlayersScores`), carga de sprites de fase (`LoadPhaseSprites`, "P Sprite"/"G Sprite"), transferencias, espionaje ("Steal Tech", `Uncloak`) |

## Sprites (`SPRITENW.DAT`)

Tablas de 16 bytes en la sección DATA del EXE (p. ej. 0x4E2AAC, 0x4E2E1C):
`struct SpriteDef { int16 hotX, hotY; int16 w, h; uint32 ptr/flags; uint32 fileOffset; }` — terminador `w=h=0`.
El píxel data es 8 bpp crudo (`w*h`), color clave 0. Cargador de fase: `FUN_004836fc` (`Load Phase Sprites`),
`FUN_00483340` ("P Sprite"), `FUN_00483600` ("G Sprite" = globales). Blit: `FUN_004647a0(buf,x,y,w,h,pitch,flags)`.

## Nota sobre el compiler spec

La spec `borlandcpp` de Ghidra asume `__fastcall` (EAX/EDX/ECX) por defecto, pero este binario
usa `__cdecl` en el código de juego y `__stdcall` en los `WndProc` (mangling `$qqs`). Con `borlandcpp`
el 96 % de los parámetros aparecían como `in_stack_XXXX`; con la spec `windows` se infieren correctamente.
