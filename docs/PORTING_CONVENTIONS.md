# Convenciones para portar la lógica de DEADLOCK.EXE a C++ (src/game)

Estas reglas permiten que varios módulos se porten en paralelo y encajen sin fricción.

## Fuentes de verdad
- `re/decomp/<addr>_<name>.c`: C decompilado por Ghidra (una función por archivo; cabecera con callers/callees/strings).
- `re/functions.jsonl`, `re/function_map.txt`, `re/modules/*.txt`: inventarios por rango de direcciones.
- `re/names*.tsv`, `re/globals.tsv`: nombres originales recuperados (funciones y globales).
- `src/game/game_state.h`: layouts **exactos** de las estructuras (no cambiar tamaños ni offsets; sí se pueden
  renombrar campos `unk_XX` cuando se demuestre su significado, actualizando `docs/SAVEFORMAT.md`).
- `docs/SAVEFORMAT.md`, `docs/ARCHITECTURE.md`, `docs/ENGINE_API.md` (motor), `docs/SPRITES.md`.

## Estado global
- Todo el estado persistente está en `dl2::gs` (`GameState`, `src/game/globals.h`); los globales sueltos en `dl2::gg`.
  Cada `DAT_xxxxxxxx` del decompilado se traduce al campo correspondiente (ver `re/globals.tsv`). Si un global
  no existe todavía, añádelo a `GameGlobals` (append, con el `DAT_` original en el comentario) — relee el archivo
  justo antes de editarlo porque otros módulos también lo amplían.
- Punteros del original (`Ptr32<T>`): contienen el índice 1-based en el array global (0 = null). Usa `ptr(p)` /
  `ref(obj)` de `globals.h`. Nunca guardes punteros nativos dentro de las structs empaquetadas.
- Objetos de heap del original (colas de producción `QueueHead/QueueRecord`, textos de eventos, listas de
  mensajes) → pools propios del módulo con índices 1-based en los `Ptr32`.

## Funciones
- Un módulo = `src/game/<modulo>.h` + `src/game/<modulo>.cpp` (namespace `dl2`). Añade el .cpp a
  `src/game/CMakeLists.txt` entre `# BEGIN MODULE SOURCES` y `# END MODULE SOURCES` (una línea, relee antes).
- Cada función portada lleva el comentario `// orig: FUN_xxxxxxxx (NombreOriginal)` y conserva el nombre original
  si se conoce (`re/names*.tsv` o cadenas de aserción); si no, un nombre descriptivo en PascalCase.
- Porta la **semántica exacta** (orden de evaluación, aritmética entera, `rand()` de Borland vía
  `rtl::rand()/random()`, comparaciones con signo/sin signo). El multijugador depende de que `CalculateGameCRC`
  dé el mismo resultado que el original.
- Llamadas a UI/motor (MessageBox `FUN_0042836c`, DebugMessage `FUN_00458990`, DebugLog `FUN_004587f0`,
  SMenu/InvalidateRect/sonido/animaciones) → `hooks::*` (`src/game/hooks.h`). Si necesitas un hook nuevo,
  añádelo a `UiHooks` (append) con valor por defecto no-op.
- RTL de Borland: `malloc/free/strcpy/sprintf/qsort` → C++ estándar; `rand/srand/random` → `rtl::`.
- Nada de SDL, Win32 ni `src/engine` dentro de `src/game`.

## Tests
- Cada módulo aporta un ejecutable de consola `test_<modulo>.cpp` (registrado entre `# BEGIN MODULE TESTS` y
  `# END MODULE TESTS` con `add_executable(test_x test_x.cpp)` + `target_link_libraries(test_x PRIVATE dl2game)`)
  que carga partidas reales con `loadgame` (módulo `saveload`) o construye estados sintéticos y verifica
  invariantes/valores conocidos (p. ej. producción de un territorio del TUTORIAL.SAV).

## Compilación
`cmd /c "call \"C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvars64.bat\" && ninja -C C:\Games\DL2\build <target>"`.
Compila sólo tu target (`ninja -C build dl2game` o `test_<modulo>`) para no interferir con otros módulos en curso.
