# Deadlock II: Shrine Wars — reconstrucción en C++/SDL2

Ingeniería inversa del `DEADLOCK.EXE` (Accolade / Cyberlore, 1998, Borland C++ 5) con Ghidra 12 y
reimplementación progresiva en C++20 sobre SDL2.

## Estado y continuación

El ejecutable abre un **inspector gráfico de partidas**: muestra el mundo, territorios, edificios
y unidades del archivo, permite seleccionarlos y guarda copias nuevas sin modificar los datos.
Todavía no activa la simulación ni permite jugar turnos. La demostración previa del motor y del
panel SMenu `D000` se conserva mediante `--demo`.

- [Recuperación de la sesión de Claude](docs/RECOVERY.md): entregables, evidencias y archivos recuperables.
- [Plan por hitos verificables](docs/ROADMAP.md): orden de continuación y criterios de cierre.
- [Integración de la lógica](docs/GAME_INTEGRATION.md): código existente que aún no puede enlazarse.
- [API del motor](docs/ENGINE_API.md): recursos, dibujo y SMenu.
- [Carga/guardado C++ verificable](docs/SAVE_CODEC.md): documentos de partida, CLI y límites.
- [Inspector gráfico del mundo](docs/WORLD_INSPECTOR.md): controles, copias seguras y límites visuales.

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

El hito previo de serialización se verificó en `build-verified` con ocho pruebas
aprobadas sin omisiones, incluidas serialización C++ sintética y contraste con 46 guardados reales.
El inspector amplía la suite a **15/15 aprobadas**, también con AddressSanitizer, e incluye
modelo, sesión, archivos, entrada y renderizado. Alcance y evidencia en `docs/RECOVERY.md`.
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

## Regenerar la exportación de Ghidra

```bat
set JAVA_HOME=C:\SDK\jdk-25.0.3
analyzeHeadless ghidra_project DL2 -process DEADLOCK.EXE -noanalysis -scriptPath ghidra_scripts -postScript ApplyNames.java re\names.tsv
analyzeHeadless ghidra_project DL2 -process DEADLOCK.EXE -noanalysis -scriptPath ghidra_scripts -postScript ExportAll.java re
```

Para usar el bridge GhidraMCP de forma interactiva: abrir `ghidra_project\DL2.gpr` en la GUI de Ghidra,
abrir `DEADLOCK.EXE` en el CodeBrowser y ejecutar `connect_instance("DL2")`.
