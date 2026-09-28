# Deadlock II: Shrine Wars — reconstrucción en C++/SDL2

Ingeniería inversa del `DEADLOCK.EXE` (Accolade / Cyberlore, 1998, Borland C++ 5) con Ghidra 12 y
reimplementación progresiva en C++20 sobre SDL2.

## Estado y continuación

El ejecutable actual es una demostración del motor: dibuja imágenes y el panel SMenu `D000`,
procesa la entrada y reproduce sonido. Todavía no permite jugar una partida completa.

- [Recuperación de la sesión de Claude](docs/RECOVERY.md): entregables, evidencias y archivos recuperables.
- [Plan por hitos verificables](docs/ROADMAP.md): orden de continuación y criterios de cierre.
- [Integración de la lógica](docs/GAME_INTEGRATION.md): código existente que aún no puede enlazarse.
- [API del motor](docs/ENGINE_API.md): recursos, dibujo y SMenu.

Git conserva el código, documentación, tablas, scripts y exportaciones de ingeniería inversa.
`build*/` y la base local `ghidra_project/` están excluidos del control de versiones y permanecen
en disco; el repositorio no sustituye una copia de seguridad de esos directorios.

```
CMakeLists.txt        build raíz (SDL2 vía vcpkg)
src/                  código C++ nuevo
  formats/            lectores de CAM, HDX/HDD, paletas, IFF-PBM, WAVE, tablas de texto
  platform/           capa SDL2: vídeo 8 bpp + paleta, audio, entrada, temporizador
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

La recuperación se verificó desde cero en `build-verified`: seis pruebas aprobadas sin omisiones.
El script armoniza la codificación de consola para que Ninja detecte las cabeceras con MSVC
localizado. Si una caché antigua muestra cientos de líneas `Nota: inclusión del archivo`,
configurar un directorio nuevo con el script; no reutilizar esa caché defectuosa.

Parámetros adicionales: `-VcpkgRoot C:\vcpkg` y `-Configuration Debug|Release|RelWithDebInfo`.
Las pruebas de infraestructura y motor no requieren los datos originales. Las pruebas de recursos,
guardados y tablas los leen sin modificarlos; CTest señala las omitidas si no están disponibles.
Las dos comprobaciones Python requieren Python 3, y la de tablas además requiere `pefile`.
La prueba de guardados valida el **parser Python**, no el nuevo cargador C++ todavía sin integrar.

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

La demostración lee los datos desde `C:\GOG Games\Deadlock 2`, la variable `DL2_DATA` o un argumento:

```powershell
.\build\src\deadlock2.exe "C:\GOG Games\Deadlock 2"
```

Escape cierra, las flechas cambian la imagen de fondo, espacio reproduce un sonido y Alt+Enter
alterna pantalla completa. El panel procesa botones, pero aún no ejecuta acciones de juego.
`--smoke-frames 3` permite un arranque de duración limitada para pruebas automáticas. CTest lo
ejecuta con vídeo/audio SDL ficticios, sin abrir una ventana.

`dl2tool` usa `DL2_GAME_DIR` para sprites; los comandos CAM reciben la ruta explícita. Ejemplos:

```powershell
.\build\src\dl2tool.exe sprite-list
.\build\src\dl2tool.exe render-menu "C:\GOG Games\Deadlock 2\deadtext.cam" D000 build/menu_D000.bmp
.\build\src\dl2tool.exe render-tile "C:\GOG Games\Deadlock 2\deadcyb.cam" 0 build/tile_0.bmp
```

Los scripts `extract_sprites.py` y `extract_tables.py` son generadores: sobrescriben sus salidas.
Para verificar tablas sin regenerar archivos, usar CTest o
`py -3 -B tests/test_game_data.py tables "C:\GOG Games\Deadlock 2"`.

## Regenerar la exportación de Ghidra

```bat
set JAVA_HOME=C:\SDK\jdk-25.0.3
analyzeHeadless ghidra_project DL2 -process DEADLOCK.EXE -noanalysis -scriptPath ghidra_scripts -postScript ApplyNames.java re\names.tsv
analyzeHeadless ghidra_project DL2 -process DEADLOCK.EXE -noanalysis -scriptPath ghidra_scripts -postScript ExportAll.java re
```

Para usar el bridge GhidraMCP de forma interactiva: abrir `ghidra_project\DL2.gpr` en la GUI de Ghidra,
abrir `DEADLOCK.EXE` en el CodeBrowser y ejecutar `connect_instance("DL2")`.
