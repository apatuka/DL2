# Integración de la infraestructura de juego — 2026-09-27

## Producción y costes conectados — 2026-10-02

Sobre `728ee94`, `economic_prefix.*` conecta un tramo original de diez pasos en
`runtime::State`, desde reinicios hasta financiación de obras. Añade producción
territorial intercalada (no suma posterior de consultas), necesidades/imports,
alimentación de civiles/unidades, energía con eventos, mantenimiento/desbandado
y refinamiento. CLI: `production-prefix <save> <seed-int32>`.

El estado final `EconomyPrefixApplied` impide repetir cobros, editar o exportar
una fase incompleta. Conserva identidades supervivientes y una única continuación
RNG/log/IA/logística/ciudades; los fallos tardíos revierten la operación entera.
No activa `Active` ni `advanceTurn`: faltan crecimiento, moral, investigación,
revueltas y balance final, además del resto del turno/UI. Alcance y límites
actuales en [ECONOMY_LAB.md](ECONOMY_LAB.md). Las secciones inferiores conservan
los cortes históricos de integración, no sustituyen este estado actualizado.

## Alcance recuperado

`dl2game` incorpora `gameflow.cpp`, `queue_pool.cpp` y `queues.cpp`, además de los
globales, hooks, RTL y tablas que ya compilaban. Esta etapa proporciona RNG,
colas de producción, búsqueda/contador de IDs y niveles de experiencia. No
implementa ejecución de turnos, economía completa ni UI jugable.

## Avance posterior: serialización C++ independiente

`dl2game` también compila `save_document.cpp` y `save_validation.cpp`. Esta API
lee los 16 bloques en un documento propietario, valida cantidades/referencias y
los vuelve a escribir sin modificar el estado activo. El CLI `dl2save` inspecciona
archivos y escenarios HDX/HDD, guarda copias nuevas y permite comprobar ediciones.

Las 46 muestras pasan roundtrip exacto y edición aislada de créditos. Las pruebas
sintéticas cubren eventos binarios, colas, ministros, límites, truncaciones,
mapas y conservación del estado ante errores. Ese hito pasó 8/8.
Consulte `SAVE_CODEC.md`: esto **no habilita el `loadGame` histórico**, sus hooks,
normalizaciones ni dependencias de campaña/IA. Los bloqueos siguientes pertenecen
a ese intento de activación, no al codec ya integrado.

## Avance posterior: inspector gráfico sin activación

`save_files.h/.cpp` centraliza la lectura acotada de archivos/escenarios y la
publicación exclusiva de copias, compartida por `dl2save` y la aplicación.
`world_view.h/.cpp` aporta cámara y selección headless sobre `const Document&`:
guarda sólo coordenadas/IDs, no referencias a elementos de vectores ni punteros
del estado global. Los edificios se asocian por `Building::territory`; las
unidades, por `army::current` (+0x3C, alias físico `Army::dest`). Los getters
de `army_state.h` mantienen el ABI y distinguen el inicio de turno (+0x38)
del territorio actual: lo demuestran `ReLinkArmy`/`MoveUnit` y Army 8204 del
corpus (inicio 15, actual 4). La vista muestra `At`/`Start`, movimiento de +0x0A
y umbral de retirada de +0x26; no interpreta +0x24 como movimiento ni +0x26
como salud. Las listas de territorio describen ubicación actual, no destinos.

`app/inspector_session.*` posee el documento y prepara la nueva selección/cámara
antes de reemplazarlo. Si falla una carga, conserva fuente y sesión anteriores.
`app/world_inspector.*` presenta una vista rectangular de territorios, atributos,
objetos y sprites estáticos. `app/inspector_main.cpp` conecta SDL, arrastre de
archivos, recarga y copias nuevas junto al ejecutable. No se escriben cambios de
turno ni se aplica niebla de guerra; tampoco se simulan posiciones de objetos en
tiles a partir de sus marcadores agregados por territorio.

Esta capa ya consume el codec desde la aplicación, pero no introduce llamadas
a `loadGame`, reinicios de `gs`/`gg`, callbacks de IA o fases de turno. Véase
`WORLD_INSPECTOR.md` para controles, garantías de copia y pruebas del hito.

## Avance posterior: preparación propia y fase fiscal

`runtime_state.h/.cpp` añade `runtime::State`: copia propietaria del documento y
grafo separado de handles tipados para referencias conocidas. La preparación es
transaccional; colas y ministros se reconstruyen sin conservar direcciones del
ejecutable original. Los IDs, palabras opacas y bytes archivados permanecen en
el documento. No se conecta el estado global heredado ni se llama a `loadGame`.

`tax_phase.h/.cpp` calcula la recaudación a partir de la población, nivel fiscal,
estadísticas raciales guardadas, centros urbanos y opción de producción rápida.
Conserva las divisiones, truncación a 16 bits y desbordamiento de créditos del
original. Usa la tabla canónica `data::kTaxIncomePercent`, no los nombres
históricos incorrectos `kTaxRates` o `kPopGrowthTable`.

`State::collectTaxes` permite aplicar esa fase una sola vez por preparación;
sólo modifica créditos y no incrementa el turno. La captura para guardar se
bloquea después de esa fase parcial. `dl2sim` permite probar preparación,
roundtrip y recaudación desde consola; el turno completo sigue rechazándose
explícitamente. Véase `RUNTIME_STATE.md` para alcance y comandos.

Esto resuelve la propiedad, referencias y rollback de la preparación, pero no
las normalizaciones de carga, campañas/IA, RNG local ni el resto del turno.

## Avance posterior: consultas económicas y energía aislada

`production_plan.*` porta las consultas de rendimiento `TaskOutputs` y
`TaskOutput`, con sus dependencias de labor, capacidad poblacional, recursos de
casillas, santuarios y modificadores. Consulta las tareas guardadas y máximos por
ranura; no llama a `ProcessTerritoryProduction`, no balancea trabajadores y no
aplica recursos, construcción o fabricación de unidades. El comportamiento
indeterminado de TaskOutputs para tarea cero se normaliza expresamente a cero.

`resource_needs.*` calcula necesidades civiles de comida, necesidades energéticas
y reservas truncadas. También proyecta la subfase `ConsumeEnergy`, incluidos
porcentaje energético y solicitudes semánticas de déficit. `State::consumeEnergy`
puede aplicarla una vez desde `Prepared`, pasando a `EnergyApplied`; no se permite
encadenarla con impuestos ni exportar el estado parcial. Los eventos del informe
no se convierten en textos SAV ni callbacks ficticios de IA.

El CLI `economy`/`energy` y sus variantes de archivo HDX/HDD exponen estas
capacidades. `ECONOMY_LAB.md` documenta fórmulas, validación y diferencias respecto
de cargar/normalizar en el original. Las nuevas consultas no cierran los dos pases
de producción aplicada ni el resto de dependencias de este inventario.

## Avance posterior: reconstrucción de tareas y balance laboral

`labor_balance.*` porta `GetBuildingTasks`, sus dependencias de mejora/reparto y
el conjunto `EndTurnBalance`. Trabaja sobre copia temporal, refresca tareas en
territorios con propietario, balancea todos los territorios y limita materiales
1..10 por arriba a 10000. Usa las tablas canónicas y las colas del documento;
no incorpora el `buildings.cpp` heredado ni sus dependencias globales.

`State::normalizeLabor` aplica únicamente tareas, labor, flags, moral y almacenes
desde `Prepared`, pasando a `LaborBalanced`. Conserva IDs, referencias, colas,
RNG, turno y archivo de entrada. El CLI `labor`/`labor-archive` no exporta SAV.
No es la activación completa de `loadGame` ni hace jugable el inspector. Véase
[LABOR_BALANCE.md](LABOR_BALANCE.md), especialmente los límites firmados y rechazos
de dominios inseguros; las órdenes manuales y el asistente completo siguen pendientes.

## Avance posterior: entidades estables y emplazamiento

El estado propietario añade identidades de vida y tablas slot→posición densa,
rechazando referencias retiradas/ajenas sin cambiar el formato guardado. Las
operaciones estructurales limitadas de inserción/retirada validan listas y
dependencias, conservan identidades supervivientes y publican documento/grafo
transaccionalmente. `EntitiesEdited` no permite exportar una partida parcial.

`entity_rules.*` porta la consulta de emplazamiento `0044d600`, su precedencia de
rechazos y geometría. `dl2sim placement`/`placement-archive` la exponen sin
mutaciones. No comprueba todavía propiedad, tecnología o pago. No se integra
`buildings.cpp`: la auditoría encontró además errores de enlaces y offsets que
deben corregirse antes de aprovechar ese código. Véase [ENTITY_RUNTIME.md](ENTITY_RUNTIME.md).

Esto no implementa `StartConstruction`, fabricación, transporte, demolición o
bajas con efectos IA. Los registros insertados son suministrados por el llamador,
no inicializados mediante callbacks o defaults incompletos de gameplay.

## Avance posterior: obra y fabricación propietarias — 2026-10-02

Sobre el backend estructural anterior, las APIs nuevas ya ejecutan comienzo
pagado de construcción, transporte/bajas, demolición no-santuario y sus efectos
locales. `building_progress` añade el subpaso de finalización/reparación/mejora
y `unit_manufacturing` las cinco colas con pagos, cancelación, trabajo, unidades
reales y repetición. No se ha activado el `buildings.cpp` heredado ni callbacks
sin implementación. Contratos y restricciones en [ENTITY_RUNTIME.md](ENTITY_RUNTIME.md).

El estado y CLI integran esas operaciones en memoria, con RNG/eventos/IA,
contadores de ciudades y logística propietarios. El presupuesto de fabricación
es explícito; falta coordinar los outputs y restantes efectos de ambos pases
económicos, así como las órdenes de UI y el guardado de una sesión jugable.

## Detalle de la infraestructura recuperada

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

El CTest de infraestructura sólo verifica esta base. `save_document` y
`save_corpus` verifican por separado el codec C++; las pruebas Python solas no
validan `saveload.cpp` ni la activación jugable. Las pruebas `world_view`,
`inspector_session`, `save_files`, `input` y `world_inspector` cubren las capas
añadidas para inspección; el resultado integrado actual se registra por separado
en `RECOVERY.md`, sin atribuirles garantías de simulación.

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

**Actualización EST-06 (2026-10-01):** la discrepancia histórica de 32 frente a
43 campañas está resuelta. `economy_tables.cpp` compilado usa adaptadores de las
tablas canónicas, con 43 defaults inmutables y un único puente mutable heredado.
`newgame.h` y `turn_api.h` comparten los contratos; sus declaraciones de lógica
ausente no se convierten en callbacks vacíos. Las filas anteriores describen los
bloqueos del cargador global histórico, no todos los módulos propietarios nuevos.

El lote EST-01..08 añade núcleo offline de carga, continentes/caminos/santuarios,
normalización laboral encadenada, restricciones de investigación y RNG de sesión.
`State::normalizeLoad` publica todo transaccionalmente como `LoadNormalized` y
enumera dependencias pendientes. No habilita `saveload.cpp` global ni activación
jugable. Alcance y evidencia en [LOAD_NORMALIZATION.md](LOAD_NORMALIZATION.md).

La continuación EST-01b/02b/04c/05b/07b porta migraciones 35..37, metadatos de
reinicio IA/ministros, detección/visibilidad/inteligencia de carga, replay de
eventos con retratos y RNG en orden y planificación de timer con contexto
explícito. La rama load=1 no ejecuta descubrimientos de contactos. También
integra creación terminada ordinaria con huella, labor y caminos locales.
La continuación sobre `e92af09` incorpora inicio pagado de obra, cobro/importación,
bajas/transporte, edificios especiales, mundo cambiado y reacciones diplomáticas/IA
propietarias. También entrega los avisos de santuarios de carga a eventos/IA reales.
No habilita producción, combate ni turno IA completos, presentación o SAV jugable.
Estas rutas propietarias sustituyen hojas verificadas; las tablas de bloqueos
anteriores siguen describiendo el cargador global excluido, no su reemplazo parcial.

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

## Trabajo pendiente de activación y criterios de aceptación

El consumo de documentos desde una vista del mundo ya está implementado mediante
el inspector de sólo lectura. Para pasar de inspección a juego falta:

1. Completar las referencias y normalizaciones pendientes sobre la preparación
   transaccional ya implementada en `runtime::State`; no activar palabras opacas.
2. Unificar tablas/API de colas, portar reinicio y reconstrucción de listas,
   resolver las dependencias reales de postprocesamiento y probarlas.
3. Comparar las normalizaciones de escenarios/versiones antiguas con el original:
   nombres, IA, campañas, eventos, flags y temporizadores. Son distintas de la
   conservación del formato físico que garantiza el codec.
4. Extender el recorrido ya verificado de cargar → preparar → capturar → guardar
   → recargar hasta un turno completo, incluyendo fallos sin alterar la partida
   anterior. La captura de la fase fiscal incompleta está prohibida.

El ejecutable gráfico ahora es un inspector de documentos; la prueba anterior de
motor y recursos sigue disponible con `--demo`. Cargar y guardar un documento,
aunque ya tenga una vista gráfica, no demuestra poder activar ni jugar la partida.
