# Codec C++ de partidas: documentos, no partidas activas

## Alcance

`src/game/save_document.h` define `dl2::save::Document`: una representación con
propiedad de sus datos para inspeccionar, modificar y serializar `.SAV`, `.CPN`
y los escenarios extraídos de `LEVELS.HDX/HDD`. Es independiente de `gs`, `gg`,
los pools de ejecución, el RNG, la interfaz y los callbacks del juego.

La API conserva el formato físico de generación **4**, versiones **35..288**
(`0x23..0x120`). Rechaza generaciones S/T/U/V y versiones fuera del intervalo;
no intenta convertirlas silenciosamente. No aplica las normalizaciones que
realizaba `LoadGame` al activar una partida antigua.

El guardado conserva cabecera y bytes opacos, texto de eventos con su longitud
exacta, palabras históricas de punteros y bytes finales que el original ignora.
Estos últimos son especialmente importantes en algunos escenarios GOG: no son
necesariamente una señal de corrupción y no deben eliminarse en un roundtrip.

Los campos `Ptr32` del documento representan IDs de fichero, coordenadas o
palabras históricas inertes. **No son punteros nativos ni handles de `dl2::ptr`.**
Las listas de ministros incluyen su cabecera; las colas conservan los registros
de `0x30` bytes que realmente se guardan. Los tiles se almacenan de manera densa,
por filas de `width` elementos, no con el stride de 40 del estado de ejecución.

## API

- `decode(bytes, document, error)` lee y valida un documento. En caso de fallo,
  deja el destino intacto.
- `encode(document, bytes, error)` valida antes de serializar y deja el destino
  intacto en caso de fallo.
- `validate(document, error)` comprueba estructura, cantidades y referencias
  persistentes conocidas; los campos opacos no adquieren significado nuevo.
- `buildingById`, `armyById`, `territoryByIndex` y `tileAt` permiten consultar los
  objetos sin activar globals ni reconstruir punteros de ejecución.

`Error` comunica categoría, offset y descripción. Los límites de recursos
declarados en la API incluyen 16 MiB por documento y 4096 nodos de lista; son
medidas defensivas del port, no límites históricos deducidos del juego.

Al editar, conservar la coherencia de contadores y listas: `eventCount` debe
coincidir con `events`, `textLen` con el texto y los flags `next` de ministros
con la cantidad de registros. Las colas admiten hasta 255 registros. La versión
35 no tiene espías/mercado negro: datos no cero en esos bloques se rechazan para
no perder cambios silenciosamente al bajar la versión. El tail transitorio de
`Territory` y `QueueRecord::next` no pertenecen al formato persistente.

La variante de mapa (`isMap == 1`) sólo contiene cabecera, mundo, territorios
reducidos y tiles, además de bytes finales. No debe tratarse como una partida
con jugadores. Su cobertura es sintética: el corpus de instalación utilizado
en este proyecto contiene partidas/escenarios, no mapas reales del editor.

## Herramienta `dl2save`

Después de compilar con `tools/build.ps1`, el ejecutable está bajo
`build/src/` (o el directorio de build elegido).

```powershell
.\build\src\dl2save.exe inspect 'C:\GOG Games\Deadlock 2\TUTORIAL.SAV'
.\build\src\dl2save.exe roundtrip 'C:\GOG Games\Deadlock 2\TUTORIAL.SAV' '.\build\tutorial-copy.sav'
.\build\src\dl2save.exe set-credits '.\build\tutorial-copy.sav' '.\build\tutorial-edited.sav' 0 12345
.\build\src\dl2save.exe inspect-archive 'C:\GOG Games\Deadlock 2\LEVELS' CHCHT1
.\build\src\dl2save.exe extract-save 'C:\GOG Games\Deadlock 2\LEVELS' CHCHT1 '.\build\chcht1.sav'
```

El índice de jugador de `set-credits` va de 0 a 6 y los créditos son un entero
con signo de 32 bits. Los comandos que escriben requieren un destino nuevo:
rechazan un fichero existente, incluido el propio origen. Use copias fuera de
la instalación original; la herramienta no crea backups ni reemplaza partidas.

La escritura prepara primero un archivo temporal hermano (`.dl2tmp-*`), lo
cierra y publica el destino mediante un **hard link exclusivo**. Si el destino
ya existe, la operación falla y elimina el temporal sin tocar el destino.
Esto requiere un sistema de archivos con soporte de hard links; si no lo hay,
se rechaza la escritura, sin recurrir a un reemplazo inseguro. La publicación
atómica no garantiza durabilidad frente a un corte de energía. No hay reemplazo,
backup automático ni protocolo de recuperación después de un fallo del sistema.

Los comandos de archivo reciben la ruta base sin extensión y un nombre exacto
de entrada. El lector valida tamaño del índice, cantidad de entradas, offset y
longitud antes de extraer; el límite de 16 MiB se aplica también a cada archivo
completo `.HDX`/`.HDD`, no sólo al escenario seleccionado. `LEVELS.HDD` de esta
instalación ocupa 11 516 454 bytes y está dentro del límite.

`inspect` emite un objeto JSON con `version`, `is_map`, `turn`, `players`,
`local_player`, `width`, `height`, `territories`, `buildings`, `armies`, `events`,
`local_values`, `minister_nodes`, `queue_records`, `trailing_bytes` y `credits`.
`players` indica el número de jugadores de las opciones; `local_values` es la
cantidad de elementos de la lista local; `minister_nodes` contiene siete
cantidades, **sin** contar cada cabecera. `credits` contiene siete valores.

## Verificación del corpus

`tests/test_save_corpus.py` contrasta el CLI C++ con `tools/savparse.py` y los
bytes originales. Recibe el ejecutable, la instalación y el directorio de build:

```powershell
python -B .\tests\test_save_corpus.py .\build\src\dl2save.exe 'C:\GOG Games\Deadlock 2' .\build
```

El test usa `TUTORIAL.SAV`, las 42 entradas de `LEVELS.HDD` y, cuando existen,
`Saves/AUTOSAVE.SAV`, `Campaign/AUTOSAVE.CPN` y `Campaign/ChCht001.CPN`: 46
documentos en la instalación de trabajo. La ausencia de los archivos básicos
produce salida 77 (prueba omitida), no un éxito ficticio. Los tres guardados
opcionales no son necesarios para otras instalaciones; el resultado indica
la cantidad real comprobada.

Para cada documento, la prueba:

1. Ejecuta las comprobaciones cruzadas del parser Python: sitios, edificios,
   tiles, adyacencias, ejércitos y sus listas.
2. Compara el resumen JSON de C++ con los campos y cantidades del parser Python.
3. Exige igualdad **byte a byte** tras leer y volver a escribir, incluidos los
   bytes finales sin interpretar.
4. Cambia los créditos del jugador local, vuelve a leerlos con Python y C++, y
   exige que el archivo sólo cambie en los cuatro bytes de ese campo.
5. Comprueba que el origen permanezca intacto.

También comprueba el rechazo de sobrescrituras y cinco entradas defectuosas:
vacía, cabecera truncada, firma inválida, versión futura y bloque de jugadores
truncado. Ejecuta `inspect-archive` sobre las 42 entradas y `extract-save` sobre
dos escenarios, incluido `CHCHT1` con bytes finales, exigiendo extracción exacta
y rechazo de sobrescritura. Tres pares HDX/HDD sintéticos comprueban conteo de
entradas enorme, offset inválido y longitud mayor que los datos. Los fallos no
deben publicar salida ni dejar temporales `.dl2tmp-*`.

Las pruebas unitarias C++ amplían la cobertura sintética del formato: eventos
con NUL embebido, 255 registros por cola, textos de 1023 bytes, 4096 registros de
ministros, versiones 35/36, mapas, enlaces de edificios, truncaciones y 256
mutaciones deterministas. Toda mutación aceptada debe volver a producir sus
bytes exactos; todo rechazo debe preservar el documento anterior. Comprueban
también que el codec no cambie globals, RNG ni pools de la partida activa;
el corpus por sí solo no demuestra la seguridad de todas las entradas posibles.

El test materializa los escenarios y todas sus salidas en un directorio temporal
dentro del build, que elimina al finalizar. Nunca escribe en la instalación GOG.

### Evidencia de ejecución

En el build `build-verified`, la ejecución inicial del hito aprobó **8/8 pruebas
CTest**, sin omisiones. El primer test de corpus verificó 46 inspecciones,
roundtrips exactos y ediciones aisladas en 6,85 segundos. Después se ejecutó de
nuevo el script ampliado contra `build-verified/src/dl2save.exe`: **46/46**
documentos, **42** inspecciones directas del archivo, **2** extracciones exactas,
**5** guardados defectuosos y **3** archivos corruptos comprobados, además del
rechazo de sobrescritura y la limpieza de temporales. Todos pasaron.

La suite final normal volvió a aprobar **8/8** tras ampliar los casos límite y
corregir el offset del parser Python. Se compiló además `test_save_document` y
`dl2save` desde cero en `build-save-asan` con MSVC AddressSanitizer y excepciones
C++ (`/EHsc`): **2/2** pruebas de guardado aprobadas, sin diagnósticos de memoria.
Esto amplía la evidencia de las entradas probadas; no sustituye una auditoría
de seguridad de cualquier archivo posible.

Para repetir la comprobación de memoria desde una Developer PowerShell x64 con
AddressSanitizer instalado en Visual Studio (mantener `/EHsc`, necesario para
limpiar recursos al lanzar excepciones):

```powershell
[Console]::InputEncoding = [Console]::OutputEncoding = [Text.UTF8Encoding]::new($false)
cmake -S . -B build-save-asan -G Ninja -DCMAKE_BUILD_TYPE=RelWithDebInfo `
  -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-windows `
  -DBUILD_TESTING=ON '-DDL2_DATA_DIR=C:/GOG Games/Deadlock 2' `
  '-DCMAKE_CXX_FLAGS=/DWIN32 /D_WINDOWS /W3 /GR /EHsc /fsanitize=address' `
  '-DCMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO=/DEBUG /INCREMENTAL:NO'
cmake --build build-save-asan --target test_save_document dl2save
ctest --test-dir build-save-asan -R '^(save_document|save_corpus)$' --output-on-failure
```

### Corrección del parser de referencia

Se corrigió `savparse.parse_building`: antes llamaba `prev` al campo opaco
`+0x116`. `Building::prev` está en **`+0x11a`** y `next` en `+0x11e`, confirmado
por `FUN_00460330` (offsets de `ushort*` `0x8d`/`0x8f`), el escritor original y
el layout C++. El campo desconocido se expone ahora como `unk116`.

La prueba de corpus valida ambos IDs con Python; la sintética C++ incluye dos
edificios enlazados y bytes opacos que no son IDs en `+0x116`. No se confunde esto
con reconstruir la lista activa de edificios de una partida en ejecución.

## Qué falta para cargar una partida jugable

Este codec **no implementa `loadGame`**, no inicia una partida y no conecta el
demo visual a una simulación. Es una base verificable para la siguiente etapa:

- Convertir IDs persistentes a referencias/pools de ejecución de manera
  transaccional, sin dejar estado parcial cuando una carga falla.
- Reconstruir listas activas/libres, ministros, colas, mapas y estado derivado.
- Definir y probar las normalizaciones de escenarios/versiones antiguas que
  el cargador original aplicaba antes de jugar.
- Resolver opciones de campaña, mundo, selección inicial y vista sin stubs que
  aparenten éxito.
- Conectar turnos, economía, combate e IA y verificar el ciclo jugable completo.

`saveload.cpp` conserva el intento anterior de carga integrada y sus dependencias
pendientes; este codec no lo habilita implícitamente. Consulte
[GAME_INTEGRATION.md](GAME_INTEGRATION.md) para los bloqueos de esa integración y
[SAVEFORMAT.md](SAVEFORMAT.md) para los offsets y funciones originales.
