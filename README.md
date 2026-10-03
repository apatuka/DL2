# Deadlock II: Shrine Wars — reconstrucción en C++/SDL2

Ingeniería inversa del `DEADLOCK.EXE` (Accolade / Cyberlore, 1998, Borland C++ 5) con Ghidra 12 y
reimplementación progresiva en C++20 sobre SDL2.

## Estado y continuación

El ejecutable abre un **inspector gráfico de partidas**: muestra el mundo, territorios, edificios
y unidades del archivo, permite seleccionarlos y guarda copias nuevas sin modificar los datos.
Todavía no permite jugar turnos. El CLI `dl2sim` prepara un estado propio, consulta
rendimientos de edificios y necesidades de recursos, y ejecuta experimentos aislados
de impuestos, energía o normalización laboral, sin guardar ni presentar un turno parcial como completo.
También consulta emplazamientos de edificios. El estado propietario ya dispone de
inserción/retirada estructural limitada con referencias estables; aún no son órdenes jugables.
`create-building` inicializa edificios terminados y especiales; los comandos de unidades/bajas
incluyen transporte, parejas y devoluciones. `start-building` cobra/importa recursos, crea la
obra pendiente y conecta eventos, trabajadores, caminos y puertos. No permite guardar el experimento.
`progress-buildings` aplica trabajo real asignado a obras/mejoras. `queue-unit`,
`dequeue-unit` y `produce-units` conectan pago, cancelación, repetición y fabricación;
este último recibe trabajo explícito, sin ejecutar el resto de la producción económica.
`production-prefix` conecta los presupuestos reales de fábricas y obras con
impuestos, importaciones, comida, energía, mantenimiento, refinamiento y pagos
pendientes. Se detiene antes de crecimiento/moral/investigación/revueltas y no
permite guardar ni presentar ese tramo como turno completo.
`production-phase` añade crecimiento, moral, resolución de investigación,
disturbios/deserciones y balance laboral final, con rollback de la secuencia
entera. Sigue siendo un experimento económico, no un turno jugable; rechaza
dominios nativos inseguros (incluido un error de formato de deserción local).
Las órdenes locales de trabajadores, actividad/locks de edificios, traslado de
población e investigación ya están integradas en State/CLI y pueden alimentar
esa fase económica. Conservan permisos, efectos parciales nativos y continuidad
propietaria de plagas; no habilitan controles gráficos ni guardado reanudable.
`normalize-load` integra un subconjunto explícito de carga offline y RNG por sesión;
incluye migraciones, reinicio IA, visibilidad, inteligencia y avisos de santuarios.
`normalize-session` incorpora reinicio, mapa cambiado y temporizador con un contexto frío explícito.
Puede completar efectos de carga sin ventanas, pero no la activación jugable. Se distinguen
las dependencias de carga de presentación/turno IA; no permite exportar un estado parcial.
La demostración previa del motor y del panel SMenu `D000` se conserva mediante `--demo`.

- [Recuperación de la sesión de Claude](docs/RECOVERY.md): entregables, evidencias y archivos recuperables.
- [Plan por hitos verificables](docs/ROADMAP.md): orden de continuación y criterios de cierre.
- [Checklist completo de juego individual](docs/SINGLE_PLAYER_CHECKLIST.md): pendientes para el cierre funcional sin multijugador.
- [Integración de la lógica](docs/GAME_INTEGRATION.md): código existente que aún no puede enlazarse.
- [API del motor](docs/ENGINE_API.md): recursos, dibujo y SMenu.
- [Carga/guardado C++ verificable](docs/SAVE_CODEC.md): documentos de partida, CLI y límites.
- [Inspector gráfico del mundo](docs/WORLD_INSPECTOR.md): controles, copias seguras y límites visuales.
- [Estado de ejecución y primera fase fiscal](docs/RUNTIME_STATE.md): referencias propias, pruebas y CLI.
- [Laboratorio económico](docs/ECONOMY_LAB.md): consultas, experimentos y tramo conectado de producción/logística/consumo/costes.
- [Normalización de carga y RNG](docs/LOAD_NORMALIZATION.md): perfil, derivados, tablas compartidas y límites del lote EST-01..08.
- [Tareas y balance laboral](docs/LABOR_BALANCE.md): reconstrucción explícita, reparto de trabajadores y límites de almacén.
- [Entidades y emplazamiento](docs/ENTITY_RUNTIME.md): referencias estables, edición estructural limitada y consultas de casillas.

El codec C++ ya lee, valida, edita y vuelve a escribir las 46 muestras disponibles sin perder
bytes. El inspector ya consume ese documento directamente, sin convertir IDs/palabras históricas
en punteros activos ni ejecutar turnos. Muestra todos los datos, sin niebla de guerra; el plano
del mundo no pretende reproducir aún la vista isométrica original.

Git conserva el código, documentación, tablas, scripts y exportaciones de ingeniería inversa.
`build*/` y la base local `ghidra_project/` están excluidos del control de versiones y permanecen
en disco; el repositorio no sustituye una copia de seguridad de esos directorios.

```
CMakeLists.txt        build raíz (SDL2 vía vcpkg)
src/                  código C++ nuevo
  formats/            lectores de CAM, HDX/HDD, paletas, IFF-PBM, WAVE, tablas de texto
  platform/           capa SDL2: vídeo 8 bpp + paleta, audio, entrada, temporizador
  app/                inspector del mundo y sesión propietaria de archivos
  game/               lógica reconstruida desde el decompilado
  tools/dl2tool.cpp   CLI para listar/extraer recursos
tools/                utilidades Python (camtool.py, derive_names.py)
ghidra_project/       proyecto Ghidra DL2.gpr (DEADLOCK.EXE analizado)
ghidra_scripts/       ExportAll.java (exporta todo el decompilado), ApplyNames.java (renombra desde TSV)
re/                   salida de la ingeniería inversa
  decomp/*.c          C decompilado de las 3 971 funciones (una por archivo, con callers/callees/strings)
  decompiled_all.c    todo concatenado
  functions.jsonl     índice (dirección, tamaño, firma, grafo de llamadas, strings referenciadas)
  strings.tsv / symbols.tsv / data.tsv / dialogs.txt / stringtable.txt
docs/FORMATS.md       formatos de archivo verificados
docs/ARCHITECTURE.md  mapa de módulos del ejecutable original y flujo del WinMain
docs/SDL2_VIABILITY.md análisis de viabilidad de SDL2
```

## Compilar y verificar (Windows)

Con Visual Studio C++ Build Tools, CMake y `sdl2:x64-windows` instalado en vcpkg:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File tools/build.ps1 -Test
```

El script localiza Visual Studio, prepara el entorno de compilación, configura CMake, compila y
ejecuta CTest. No instala dependencias ni modifica los datos originales. Para comprobar desde cero
o usar otra instalación del juego:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File tools/build.ps1 -BuildDir build-clean -DataDir "C:\GOG Games\Deadlock 2" -Test
```

El hito de serialización pasó 8/8, el del inspector 15/15 y el de preparación/fiscalidad 18/18.
La suite actual, incluidas las órdenes locales, santuarios y la fase económica hasta balance final, pasa **60/60 sin omisiones**, tanto
en `build-verified` como con AddressSanitizer en `build-save-asan`. Incluye 46
capturas exactas, entidades/emplazamientos y experimentos económicos, además de
RNG propietario, tablas compartidas y carga parcial: 46 documentos normalizados,
incluidas ocho migraciones antiguas, inteligencia, eventos/timer y creación local.
También cubre reinicio/mundo cambiado, avisos de santuarios, reacciones IA,
transporte y bajas, cobro/importaciones, comienzo/progreso/finalización de obra,
mejoras y fabricación/repetición por colas. El tramo económico conectado se verifica
sobre cuatro partidas originales de sólo lectura y estados sintéticos de orden,
abastecimiento, financiación, bajas, continuaciones y rollback tardío.
Las órdenes económicas añaden cinco suites para labor, población, investigación,
actividad/locks e integración de decisiones→fase, además de cobertura CLI sin exportación.
EST-04c añade tres suites de demolición de santuarios, bajas individuales y
penalizaciones diferidas, incluyendo cascadas de plataforma, flags marinos,
campaña viva y continuidad propietaria. Sigue parcial por coordinación del turno,
referencias IA diferidas y controles gráficos; véase `docs/ENTITY_RUNTIME.md`.
No acredita carga jugable ni turno completo. Alcance y evidencia en `docs/RECOVERY.md`.
El script armoniza la codificación de consola para que Ninja detecte las cabeceras con MSVC
localizado. Si una caché antigua muestra cientos de líneas `Nota: inclusión del archivo`,
configurar un directorio nuevo con el script; no reutilizar esa caché defectuosa.

Parámetros adicionales: `-VcpkgRoot C:\vcpkg` y `-Configuration Debug|Release|RelWithDebInfo`.
Las pruebas de infraestructura y motor no requieren los datos originales. Las pruebas de recursos,
guardados y tablas los leen sin modificarlos; CTest señala las omitidas si no están disponibles.
Las comprobaciones Python requieren Python 3, y la de tablas además requiere `pefile`.
`original_saves` valida el **parser Python**, no la activación de partidas del juego.
`save_document` y `save_corpus` sí verifican el codec C++ independiente; no la activación de `loadGame`.

Compilación manual equivalente:

```bat
call "C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvars64.bat"
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=RelWithDebInfo ^
      -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-windows ^
      -DBUILD_TESTING=ON -DDL2_DATA_DIR="C:/GOG Games/Deadlock 2"
cmake --build build
ctest --test-dir build --output-on-failure --no-tests=error
build\src\dl2tool cam list "C:\GOG Games\Deadlock 2\deadcyb.cam"
```

La aplicación lee los datos desde `C:\GOG Games\Deadlock 2`, la variable `DL2_DATA` o un argumento.
Por defecto abre `TUTORIAL.SAV`; también acepta un guardado o un escenario de `LEVELS`:

```powershell
.\build\src\deadlock2.exe "C:\GOG Games\Deadlock 2"
.\build\src\deadlock2.exe "C:\GOG Games\Deadlock 2" --load "C:\ruta\partida.sav"
.\build\src\deadlock2.exe "C:\GOG Games\Deadlock 2" --scenario CHCHT1
```

Clic selecciona; `Tab`/`Shift+Tab` recorre objetos; rueda y `+`/`-` cambian el zoom; las flechas
desplazan el mapa. `F` ajusta la vista, `O` alterna propietarios, `R` recarga y `F5` guarda una
copia nueva en `<directorio del ejecutable>/saves/inspection-copy-N.sav`, sin cambiar la fuente.
Se pueden soltar archivos sobre la ventana. Escape cierra. Los controles y límites completos
están en [WORLD_INSPECTOR.md](docs/WORLD_INSPECTOR.md).

`--smoke-frames 3` limita la duración para pruebas automáticas; `--screenshot build/new.bmp`
guarda una captura nueva del inspector al salir. CTest usa vídeo SDL ficticio sin abrir ventana.
Para la demostración anterior usar `--demo`: sus flechas cambian imágenes y espacio reproduce
un sonido; el panel SMenu no ejecuta acciones de juego.

`dl2tool` usa `DL2_GAME_DIR` para sprites; los comandos CAM reciben la ruta explícita. Ejemplos:

```powershell
.\build\src\dl2tool.exe sprite-list
.\build\src\dl2tool.exe render-menu "C:\GOG Games\Deadlock 2\deadtext.cam" D000 build/menu_D000.bmp
.\build\src\dl2tool.exe render-tile "C:\GOG Games\Deadlock 2\deadcyb.cam" 0 build/tile_0.bmp
```

Los scripts `extract_sprites.py` y `extract_tables.py` son generadores: sobrescriben sus salidas.
Para verificar tablas sin regenerar archivos, usar CTest o
`py -3 -B tests/test_game_data.py tables "C:\GOG Games\Deadlock 2"`.

Para inspeccionar una partida o guardar una copia nueva con el codec C++:

```powershell
.\build-verified\src\dl2save.exe inspect "C:\GOG Games\Deadlock 2\TUTORIAL.SAV"
.\build-verified\src\dl2save.exe roundtrip "C:\GOG Games\Deadlock 2\TUTORIAL.SAV" build-verified/tutorial-copy.sav
.\build-verified\src\dl2save.exe inspect-archive "C:\GOG Games\Deadlock 2\LEVELS" CHCHT1
```

Los destinos deben ser nuevos; no se sobrescribe el origen ni un guardado existente. Véase
`docs/SAVE_CODEC.md` antes de editar campos o usar los datos en la simulación.

Para preparar un estado con referencias tipadas o ejecutar sólo la fase fiscal:

```powershell
.\build-verified\src\dl2sim.exe prepare "C:\GOG Games\Deadlock 2\TUTORIAL.SAV"
.\build-verified\src\dl2sim.exe taxes "C:\GOG Games\Deadlock 2\TUTORIAL.SAV"
.\build-verified\src\dl2sim.exe taxes-archive "C:\GOG Games\Deadlock 2\LEVELS" CHCHT1
```

Los comandos fiscales devuelven JSON y no escriben partidas. El turno no aumenta:
la fase económica ya conecta producción, consumo, logística, población, moral,
investigación, disturbios y balance final dentro de sus dominios seguros. Faltan
movimiento/combate, IA completa y demás fases. `dl2sim turn` devuelve un error explícito.
La aplicación gráfica permanece en modo de inspección.

El laboratorio económico añade:

```powershell
.\build-verified\src\dl2sim.exe economy "C:\GOG Games\Deadlock 2\TUTORIAL.SAV"
.\build-verified\src\dl2sim.exe energy "C:\GOG Games\Deadlock 2\TUTORIAL.SAV"
.\build-verified\src\dl2sim.exe production-prefix "C:\GOG Games\Deadlock 2\TUTORIAL.SAV" 1
.\build-verified\src\dl2sim.exe production-phase "C:\GOG Games\Deadlock 2\TUTORIAL.SAV" 1
```

`economy` devuelve el rendimiento calculado por tarea y las necesidades actuales,
sin aplicar producción ni redistribuir trabajadores. `energy` consume sólo la
energía de la instantánea guardada, sin ejecutar producción o importaciones antes.
Es un experimento independiente de impuestos, no la continuación de un turno.
Los comandos correspondientes `economy-archive` y `energy-archive` aceptan base
HDX/HDD y entrada. Detalles y límites: [ECONOMY_LAB.md](docs/ECONOMY_LAB.md).

Órdenes locales de ejemplo, cada ejecución desde una preparación nueva:

```powershell
.\build-verified\src\dl2sim.exe transfer-labor "C:\GOG Games\Deadlock 2\TUTORIAL.SAV" 14 10242 1 10241 1
.\build-verified\src\dl2sim.exe building-lock "C:\GOG Games\Deadlock 2\TUTORIAL.SAV" 10242 1
.\build-verified\src\dl2sim.exe research-clear "C:\GOG Games\Deadlock 2\TUTORIAL.SAV" 0 -1
```

También hay `move-labor`, `reset-labor`, `building-toggle`, `move-population`,
`research-select` y `research-toggle`; argumentos en `dl2sim --help`.
Investigación exige máscara de campaña y comparación de commit explícitas;
el CLI no las deduce del SAV. No escribe las decisiones en el archivo original.

Para reconstruir tareas, balancear trabajadores y aplicar el tope de almacenes
en memoria, sin producir ni completar la carga jugable:

```powershell
.\build-verified\src\dl2sim.exe labor "C:\GOG Games\Deadlock 2\TUTORIAL.SAV"
.\build-verified\src\dl2sim.exe labor-archive "C:\GOG Games\Deadlock 2\LEVELS" CHCHT1
```

El informe muestra valores antes/después; no modifica el archivo original ni
permite guardar el estado parcial. Véase [LABOR_BALANCE.md](docs/LABOR_BALANCE.md).

Para probar el subconjunto integrado de carga offline (opciones, enlaces,
continentes/caminos/santuarios, labor y RNG), sólo en memoria:

```powershell
.\build-verified\src\dl2sim.exe normalize-load "C:\GOG Games\Deadlock 2\TUTORIAL.SAV"
.\build-verified\src\dl2sim.exe normalize-load-archive "C:\GOG Games\Deadlock 2\LEVELS" CHCHT1
```

La salida declara `complete_load:false`, `can_play:false` y lo pendiente.
`activate` rechaza la activación jugable: falta la entrega de presentación y el
coordinador de turno con IA completa. Visibilidad/inteligencia de carga ya se
reconstruyen; el original omite nuevos contactos durante LoadGame. Véase
[LOAD_NORMALIZATION.md](docs/LOAD_NORMALIZATION.md).

## Regenerar la exportación de Ghidra

```bat
set JAVA_HOME=C:\SDK\jdk-25.0.3
analyzeHeadless ghidra_project DL2 -process DEADLOCK.EXE -noanalysis -scriptPath ghidra_scripts -postScript ApplyNames.java re\names.tsv
analyzeHeadless ghidra_project DL2 -process DEADLOCK.EXE -noanalysis -scriptPath ghidra_scripts -postScript ExportAll.java re
```

Para usar el bridge GhidraMCP de forma interactiva: abrir `ghidra_project\DL2.gpr` en la GUI de Ghidra,
abrir `DEADLOCK.EXE` en el CodeBrowser y ejecutar `connect_instance("DL2")`.
