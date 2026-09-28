# Convenciones para portar la lógica de DEADLOCK.EXE a C++ (src/game)

Estas reglas permiten que varios módulos se porten en paralelo y encajen sin fricción.

## Fuentes de verdad

- `re/decomp/<addr>_<name>.c`: C decompilado por Ghidra (una función por archivo; cabecera con callers/callees/strings).
- `re/functions.jsonl`, `re/function_map.txt`, `re/modules/*.txt`: inventarios por rango de direcciones.
- `re/names*.tsv`, `re/globals.tsv`: nombres originales recuperados (funciones y globales).
- `src/game/game_state.h`: layouts **exactos** de las estructuras (no cambiar tamaños ni offsets; sí se pueden
  renombrar campos `unk_XX` cuando se demuestre su significado, actualizando `docs/SAVEFORMAT.md`).
- `docs/SAVEFORMAT.md`, `docs/ARCHITECTURE.md`, `docs/ENGINE_API.md` (motor), `docs/SPRITES.md`.
- `docs/SAVE_CODEC.md`, `docs/RUNTIME_STATE.md` y `docs/ECONOMY_LAB.md`: límites entre
  formato de archivo, preparación propietaria, consultas y ejecución de fases. Los nombres de campos/tablas heredados
  pueden ser inexactos: confirmar offsets y lectores originales antes de usarlos.
- `docs/LABOR_BALANCE.md`: normalización explícita de tareas/trabajadores, prioridades,
  resultados negativos originales y dominios rechazados; no es activación completa.

## Propiedad del estado: no mezclar las representaciones

- **Documento de archivo (`save::Document`)**: posee sus arrays, listas, colas y bytes de eventos.
  Sus campos empaquetados `Ptr32` contienen IDs de archivo, coordenadas o palabras históricas opacas.
  **Nunca usar `globals.h::ptr/ref` sobre un documento** ni guardar direcciones nativas en sus structs.
  `(0,0)` codificado en una referencia de tile es una coordenada válida, no un puntero nulo.
- **Preparación nueva (`runtime::State`)**: copia propietaria más `Graph` con handles tipados locales
  a esa instancia. Convertir referencias conocidas explícitamente; no reciclar palabras opacas
  como handles ni callbacks. Los handles/punteros const dejan de ser utilizables tras reemplazar
  con éxito la preparación; no hay detección automática de handles pertenecientes a otra instancia.
  Las fases nuevas reciben su estado explícito, sin tocar `gs`, `gg` ni RNG global.
- **Código heredado global**: `dl2::gs` (`GameState`) y `dl2::gg` siguen sosteniendo módulos antiguos.
  Sólo en esa representación se usan `ptr/ref` y los pools globales de colas con índices 1-based
  (cero nulo). Cada `DAT_xxxxxxxx` se identifica con el campo correspondiente de `re/globals.tsv`.
  Si una tarea exige ampliar `GameGlobals`, añadir al final con evidencia de dirección y releer
  antes de editar; no introducir un nuevo global como atajo para las APIs propietarias.
- Preservar eventos y `localList` como datos propietarios. El texto binario usa longitud explícita,
  no `strlen`; NUL internos y bytes no ASCII forman parte del contenido guardado.
- Distinguir preparación de activación completa. Las normalizaciones de campañas/versiones/IA/RNG
  deben tener contrato y evidencia propios; no ejecutarlas implícitamente para lograr un round-trip.
  Un experimento de fase incompleta no puede exportarse como turno terminado o partida reanudable.
- Separar una consulta sobre el documento guardado de la consulta posterior a `LoadGame` original:
  éste también reconstruye tareas y balancea labor. Los planes económicos no deben hacer esas
  mutaciones ni ejecutar los reinicios de turno como efecto oculto. Las fases aisladas sólo pueden
  encadenarse cuando se hayan implementado sus predecesoras y exista un contrato de secuencia.

## Funciones

- Un módulo = `src/game/<modulo>.h` + `src/game/<modulo>.cpp` (namespace `dl2`). Añade el .cpp a
  `src/game/CMakeLists.txt` entre `# BEGIN MODULE SOURCES` y `# END MODULE SOURCES` (una línea, relee antes).
- Cada función portada lleva el comentario `// orig: FUN_xxxxxxxx (NombreOriginal)` y conserva el nombre original
  si se conoce (`re/names*.tsv` o cadenas de aserción); si no, un nombre descriptivo en PascalCase.
- Porta la **semántica exacta** (orden de evaluación, aritmética entera, `rand()` de Borland vía
  `rtl::rand()/random()`, comparaciones con signo/sin signo). El multijugador depende de que `CalculateGameCRC`
  dé el mismo resultado que el original.
- Implementar overflow y narrowing con operaciones definidas, no overflow con signo de C++.
  Conservar divisiones intermedias y rarezas demostradas del original; no sustituirlas por fórmulas
  equivalentes sólo en números reales. En fases propietarias que necesiten azar, añadir un estado RNG
  propio explícito y probado; no consumir/resembrar silenciosamente el generador global de `rtl`.
- Si el decompilado indica una lectura indeterminada, confirmar el flujo en assembly antes de
  inventar semántica. Cualquier normalización deliberada debe ser visible en el contrato y probada;
  no presentarla como paridad exacta. Caso conocido: TaskOutputs normaliza tareas vacías en el
  informe, pero TaskOutput escalar conserva su comportamiento definido y no se unifica con aquél.
- Validar índices y huellas de sitios sin corregir datos silenciosamente. `BuildingSite+0/+1`
  son coordenadas persistidas x/y, y `Territory+0x35` es porcentaje energético, pese a nombres
  heredados. Los arrays `+0xA7E/+0xAAA` son scratch de reservas/logística y saldo consultivo;
  no inferir su uso por los nombres actuales `production`/`consumption`.
- Llamadas a UI/motor (MessageBox `FUN_0042836c`, DebugMessage `FUN_00458990`, DebugLog `FUN_004587f0`,
  SMenu/InvalidateRect/sonido/animaciones) → `hooks::*` (`src/game/hooks.h`). Si necesitas un hook nuevo,
  añádelo a `UiHooks` (append) con valor por defecto no-op.
- Un hook de presentación opcional no sustituye una dependencia de simulación. Si una fase aún
  necesita producción, logística, creación de objetos, eventos o campaña no implementados, devolver
  un error de capacidad explícito; no declarar éxito con callbacks vacíos. `advanceTurn` debe seguir
  fallando hasta que exista un turno coherente, sin incrementar artificialmente `options.turn`.
- Un informe semántico de eventos no equivale a registros persistidos ni a efectos de UI/IA.
  No fabricar texto de eventos ni serializar un experimento parcial. Los modos máximos por ranura
  son consultas independientes, no planes de trabajadores ejecutables simultáneamente.
- RTL de Borland: `malloc/free/strcpy/sprintf/qsort` → C++ estándar; `rand/srand/random` → `rtl::`.
- Nada de SDL, Win32 ni `src/engine` dentro de `src/game`.

## Tests

- Registrar cada ejecutable `tests/test_<modulo>.cpp` en `tests/CMakeLists.txt`, enlazar el target
  correspondiente y añadir `add_test`. Las comprobaciones deben seguir activas en Release/NDEBUG;
  no depender de `assert` para los criterios de aceptación.
- Cargar muestras reales mediante `save::readDocument/readScenario` y preparar `runtime::State`
  cuando corresponda. `saveload.cpp` sigue excluido: no utilizar `loadGame` como si ya estuviera
  integrado. Añadir estados sintéticos para límites, referencias inválidas y ramas sin muestras.
- Verificar transacciones: fallos conservan fuente, destino e informe anteriores; éxitos limpian
  errores. Comprobar aislamiento de globales/RNG, propiedad de memoria y captura exacta cuando se
  promete. Los datos originales son entradas de sólo lectura; escribir sólo en destinos nuevos.
- Separar oráculos derivados del decompilado, comparaciones independientes y resultados observados
  ejecutando el original. Dos ejecuciones iguales del port demuestran determinismo, no por sí solas
  paridad con el juego original. No atribuir al original resultados calculados por nuestras pruebas.

## Compilación

Desde una terminal PowerShell normal, usar el script que localiza Visual Studio,
prepara MSVC y armoniza la codificación de `/showIncludes` para Ninja:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File tools/build.ps1 -BuildDir build -Test
```

Para una comprobación limpia usar otro directorio (`-BuildDir build-clean`). El script
acepta `-DataDir`, `-VcpkgRoot` y `-Configuration Debug|Release|RelWithDebInfo`; no instala
dependencias ni modifica la instalación original. Los resultados de CTest deben indicar
también pruebas omitidas, no sólo fallos. Para repetir una prueba ya compilada:

```powershell
ctest --test-dir build --output-on-failure -R "^(runtime_state|tax_phase)$"
```

Coordinar un único build por directorio cuando haya agentes trabajando en paralelo.
No configurar/compilar simultáneamente sobre la misma caché. Si se acuerda un target
individual, usar `cmake --build build --target <target>` desde una terminal que ya tenga
el entorno MSVC; el script prepara su propio proceso, no modifica la terminal padre.
