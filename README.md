# Deadlock II: Shrine Wars — reconstrucción en C++/SDL2

Ingeniería inversa del `DEADLOCK.EXE` (Accolade / Cyberlore, 1998, Borland C++ 5) con Ghidra 12 y
reimplementación progresiva en C++20 sobre SDL2.

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

## Compilar

```bat
call "C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvars64.bat"
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=RelWithDebInfo ^
      -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-windows
ninja -C build
build\src\dl2tool cam list "C:\GOG Games\Deadlock 2\deadcyb.cam"
```

Los datos del juego se leen desde `C:\GOG Games\Deadlock 2` (variable `DL2_DATA` o primer argumento).

## Regenerar la exportación de Ghidra

```bat
set JAVA_HOME=C:\SDK\jdk-25.0.3
analyzeHeadless ghidra_project DL2 -process DEADLOCK.EXE -noanalysis -scriptPath ghidra_scripts -postScript ApplyNames.java re\names.tsv
analyzeHeadless ghidra_project DL2 -process DEADLOCK.EXE -noanalysis -scriptPath ghidra_scripts -postScript ExportAll.java re
```

Para usar el bridge GhidraMCP de forma interactiva: abrir `ghidra_project\DL2.gpr` en la GUI de Ghidra,
abrir `DEADLOCK.EXE` en el CodeBrowser y ejecutar `connect_instance("DL2")`.
