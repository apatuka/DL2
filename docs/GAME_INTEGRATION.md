# Integración de la infraestructura de juego — 2026-09-27

## Alcance recuperado

`dl2game` incorpora `gameflow.cpp`, `queue_pool.cpp` y `queues.cpp`, además de los
globales, hooks, RTL y tablas que ya compilaban. Esta etapa proporciona RNG,
colas de producción, búsqueda/contador de IDs y niveles de experiencia. No
implementa ejecución de turnos, economía completa, carga de partidas ni UI jugable.

La API de `queue_pool.h/cpp` se recuperó de los mensajes `Write` del historial de
Claude y se contrastó con `re/decomp/00484c2c*` a `00484f48*`. La copia histórica
usaba `vector<T>`: añadir una cabecera o un nodo podía invalidar punteros nativos
que otros módulos conservaban. El pool restaurado guarda objetos de dirección
estable mediante `unique_ptr`, valida los handles libres y reutiliza huecos.
`Ptr32` sigue siendo un índice 1-based; un handle liberado no debe conservarse
después de reutilizar su hueco. `QueuePoolReset()` invalida todas las referencias.

Las operaciones de inserción, eliminación y extracción de `queues.cpp` conservan
su estrategia previa de reconstruir la cola: sus nodos pueden cambiar de handle,
pero se preservan datos, orden y posición del cursor. No se deben retener punteros
a nodos de esa misma cola durante dichas operaciones. El crecimiento del pool sí
conserva las direcciones de cabeceras y nodos existentes.

`QueueFree(..., 0)` conserva la cabecera y vacía su cursor. Esto evita el puntero
colgante que dejaba el original al liberar los nodos. `QueueAppend` conserva el
cursor y `QueueCurData` con cursor nulo deja intacto el destino, como el original.

Se incorporó `ExperienceLevel` (FUN_00447a40: umbrales 100 y 401), que
`MilitiaTrainingBonus` necesitaba para enlazar. `RandRangeTagged` utiliza resto
con signo como FUN_0046c9d8 y `NextGlobalId` reproduce el desbordamiento de 32 bits
sin depender de overflow con signo de C++.

## Pruebas

`tests/test_game.cpp` contiene comprobaciones que siguen activas con `NDEBUG`:

- Crecimiento con 2048 cabeceras/nodos adicionales, estabilidad de direcciones,
  liberación, handles fuera de rango y reutilización de huecos.
- Inserción/eliminación/extracción, cantidades, once valores de materiales y
  movimiento del cursor en listas vacías, inicio, centro y final.
- Vectores fijos de los tres RNG, semilla completa de `_lrand`, rango cero,
  resto negativo y separación entre semilla local y difusión de red.
- Búsqueda de IDs en el último elemento de cada array, IDs inexistentes,
  truncación a 16 bits y desbordamiento del contador de 32 bits.
- Umbrales de experiencia y límite acumulado de entrenamiento de milicias.

El CTest de infraestructura sólo verifica esta base. Las pruebas Python del
parser SAV no equivalen a validar `saveload.cpp` ni a un round-trip C++.

## Por qué saveload.cpp sigue fuera de CMake

El archivo conserva trabajo útil (lectores/escritores de los 16 bloques), pero
no basta añadirlo a la biblioteca. La comprobación sintáctica con MSVC
`cl /std:c++20 /EHsc /utf-8 /Zs /I src ... src/game/saveload.cpp` falla ya antes
del enlace. Se dejó intacto para integrar sus dependencias de forma explícita.

| Lugar | Bloqueo observado | Trabajo necesario |
|---|---|---|
| `saveload.h` | Utiliza `std::string` sin incluir `<string>`. | Hacer la cabecera autosuficiente. |
| `LoadPlayers` | `gg.defaultPlayerName` no existe. | Resolver las preferencias del jugador y su contrato en `GameGlobals`. |
| `SaveQueue` / `LoadQueue` / `LoadTerritories` | Llama `econ::qhead`, `econ::AllocQueueHead` y `econ::Queue*`. | Unificar con `dl2::ptr`, `QueueAlloc` y las funciones de `queue_pool.h`. |
| `LoadJobs` | `ComputeContinents` no está declarado/implementado. | Incorporar reconstrucción real de continentes. |
| `loadGameFromMemory` | `PrepareLongRangeScan` y `SelectInitialTerritory` no están declarados/implementados. | Separar preparación del estado y de la vista, o portar estas funciones. |

Dependencias adicionales visibles que aún no pueden enlazarse:

| API requerida | Declaración / estado | Motivo |
|---|---|---|
| `ResetVariables`, `ResetSpies`, `SwitchLocalPlayer` | `newgame.h`; falta `newgame.cpp`. | Reinicio previo, ficheros antiguos y guardado desde editor. |
| `kAiLeaderNames`, `kRaceStatsRows61` | `newgame.h`; no hay definiciones con esos nombres. | Nombres de IA y conversión de partidas antiguas. Las tablas `dl2::data` deben ser la fuente compartida. |
| `econ::gCampaigns`, `CampaignApplyOptions`, `CampaignClearForbiddenResearch` | `economy.h`; falta implementación de campaña. | Carga de opciones/objetivos y restricciones tecnológicas. |
| `econ::RebuildBuildingLists` | Implementado dentro de `buildings.cpp`, aún excluido. | Reconstrucción activa/libre; añadir todo `buildings.cpp` arrastra producción, logística y población incompletas. Conviene separar la gestión de pools. |
| `econ::RebuildArmyFreeList`, `AfterMovePhase` | `economy.h`; falta implementación. | Pool de ejércitos y normalización de unidades/territorios después de cargar. |
| `econ::CountShrines`, `BlackMarketReset` | `economy.h`; falta implementación. | Condiciones de victoria y formatos antiguos. |
| `BackupPath`, `CurrentSaveKind` | `campaign_flow.h`; falta `campaign_flow.cpp`. | Guardado con copia de seguridad. |

Los callbacks de IA/temporizadores en `flow::cb` siguen siendo opcionales y
actualmente no tienen módulos reales instalados. Enlazar omitiendo estas
funciones no demostraría que una partida cargada esté preparada para jugar.

Existe además una discrepancia de tablas: `econ::kNumCampaigns` es **32**,
mientras `campaign_flow.h` y `data::kNumCampaigns` describen **43** entradas
(sin campaña + 42 escenarios). Debe resolverse antes de conectar campañas;
no se debe llenar un array de 32 con los 43 valores del ejecutable.

## Correcciones necesarias antes de probar partidas en C++

La revisión de código detectó estos riesgos todavía sin corregir en el módulo
excluido:

- `LoadMinisterJobs` conserva `prev` mientras `AllocMinisterJobNode` puede
  realojar `vector<MinisterJob>`; escribir el enlace después puede acceder a
  memoria liberada. Hace falta almacenamiento estable o usar handles.
- `LoadWorld` devuelve éxito aunque su lectura falle. Debe propagar truncación.
- `LoadEventLog` pasa `textLen` del fichero a un buffer de 1024 bytes sin
  verificar antes el límite; también faltan límites de cantidad de eventos.
- `LoadOptions`, `LoadTiles`, `LoadTerritories` y los arreglos de punteros necesitan
  límites de jugadores, jugador local, dimensiones, territorios, tiles e índices
  antes de indexar los arrays. `SaveReader` debe comprobar tamaños sin overflow.
- `SaveQueue` convierte la cantidad de nodos a `uint8_t`; debe rechazar listas
  de más de 255 nodos para no producir un guardado truncado silenciosamente.
- `saveGame(makeBackup=true)` renombra el fichero anterior antes de validar y
  escribir el nuevo. El guardado debería preparar el resultado y reemplazarlo
  de forma segura; las pruebas deben usar un directorio temporal del build.

## Hito siguiente y criterio de aceptación

1. Aislar la serialización y reconstrucción de referencias del arranque de una
   partida. Un lector de estado puede existir antes que la UI, con nombre y
   contrato explícitos; no debe fingir que inicia una partida completa.
2. Unificar tablas y API de colas, portar el reinicio/pools necesarios y corregir
   validación de entradas antes de habilitar el cargador C++.
3. Cargar `TUTORIAL.SAV`, guardar en memoria, volver a cargar y comparar estado
   normalizado: objetos, referencias, colas, opciones, tecnologías y trabajos.
4. Repetir con campañas y las 42 entradas de `LEVELS.HDX/HDD`, distinguiendo
   cambios intencionales al normalizar versiones antiguas de pérdidas de datos.
5. Añadir casos truncados, índices fuera de rango y múltiples nodos de ministros.
   Una carga fallida debe producir un error controlado y estado definido.

Hasta completar este hito, el ejecutable sigue siendo una prueba de motor y
recursos. No se ha verificado cargar/guardar/cargar desde C++.
