# Preparación propietaria del estado y subfase fiscal

`runtime::State` prepara un documento de partida y un grafo de referencias
tipadas, separado de los globales heredados `gs` y `gg`. Ya permite resolver
objetos, consultar sus relaciones, capturar una preparación sin cambios y
ejecutar **experimentos fiscales, energéticos y de balance laboral aislados, sólo en memoria**.
También puede consultarse rendimiento de edificios y necesidades sobre el
documento preparado; véase [ECONOMY_LAB.md](ECONOMY_LAB.md).

Esto no equivale a activar completamente `LoadGame` ni a ejecutar un turno.
No hay incremento ficticio del contador de turno ni éxito silencioso para las
fases aún ausentes. El inspector gráfico sigue siendo de sólo lectura.

Los lotes EST añaden `normalizeLoad`: núcleo offline con migraciones antiguas y
metadatos de IA, continentes/caminos/santuarios, visibilidad/inteligencia, balance
laboral y RNG propietario. Eventos y timer admiten contexto previo explícito;
las capacidades ausentes siguen enumeradas.
Contrato, versiones y comandos en [LOAD_NORMALIZATION.md](LOAD_NORMALIZATION.md).

## Propiedad y preparación transaccional

`State::prepare(const save::Document&, Error&)` valida el documento, construye una
copia propia y resuelve sus referencias en un `Graph` independiente. Sólo sustituye
el estado anterior después de completar toda la operación. Los errores de
validación, referencias o asignación conservan el estado anterior. Un documento
de mapa reducido puede inspeccionarse, pero se rechaza como estado de ejecución.

El documento de origen no se modifica ni queda compartido mediante punteros. El
estado preparado tampoco escribe en `gs`, `gg`, pools globales o generadores RNG,
y no invoca callbacks históricos. Los campos que el archivo conserva como
direcciones antiguas nunca se convierten en código ejecutable.

Los `Handle<Tag>` son slots tipados con identidad de vida, con cero como nulo.
No son IDs de archivo: `buildingById` y `armyById` realizan la conversión.
Los accesores rechazan handles retirados, de otra instancia o de una preparación
anterior. Una preparación fallida no los invalida. Los supervivientes conservan
su identidad tras insertar/retirar entidades, incluso si cambia su posición en
el documento denso. No indexar `Graph::buildings/armies` mediante `handle.slot`:
usar `buildingLinks`/`armyLinks`. Los punteros prestados sí deben descartarse tras
una mutación estructural o sustitución exitosa. Mover un `State` transfiere juntos
documento, identidades, grafo y RNG y deja vacío el origen. La normalización parcial
también conserva handles, pero invalida punteros prestados tras su commit.
Contrato detallado y límites: [ENTITY_RUNTIME.md](ENTITY_RUNTIME.md).

## Referencias resueltas y palabras conservadas

| Dato de archivo | Representación preparada |
|---|---|
| ID de edificio/unidad | Handle tipado dentro del array propietario correspondiente |
| Índice de territorio 1..N | `TerritoryHandle`; asociaciones por propietario en `playerTerritories` |
| Coordenada de tile `x \| y<<16` | `TileHandle` sobre el array denso de ancho × alto; `(0,0)` es válido, no nulo |
| Casillas de construcción y adyacencias | Handles de edificio y territorio verificados |
| Cinco colas de cada territorio | Cabeceras y nodos propios; cursor inicial en el primer nodo |
| Lista de ministros de cada jugador | Enlaces prev/next reconstruidos por orden de archivo, incluida la cabecera |
| Jobs | Destino por índice y unidades por `armyIds`; no por las palabras crudas de `Job::armies` |
| Enlaces prev/next, carga de unidades y cabeceras guardadas | Referencias conocidas resueltas, conservadas aparte de la pertenencia canónica |

La pertenencia de edificios se obtiene de `Building::territory`, no recorriendo
listas históricas para enumerarlos. Para unidades, la evidencia de `ReLinkArmy`
(`FUN_00445898`) distingue tres ubicaciones: `+0x3c` es la actual, `+0x38` la
base/al inicio del turno y `+0x40` el origen de ruta. Los nombres antiguos de
`Army::dest` y `Army::territory` pueden inducir a error. El grafo expone
`current`, `turnStart` y `routeOrigin` y agrupa por la ubicación actual.

Los nodos de cola copiados al grafo tienen `record.next.raw` limpio; el enlace
válido es `QueueNode::next`. El documento archivado conserva sus propios bytes.
Las cabeceras crudas `Territory::queues`, direcciones de IA, vtables, funciones
de ministros y otros campos opacos no se interpretan como handles ni punteros
nativos. No se completan mediante callbacks vacíos.

`localList` y los eventos continúan dentro del documento propietario: no se
recrean listas con direcciones del ejecutable original. El texto de eventos es
un vector de bytes con longitud explícita; se conservan NUL internos y bytes
no ASCII. La presentación de texto de la UI no cambia estos datos binarios.
La proyección nativa opcional `loadedEvents()` exige un dominio más limitado
(sin NUL interno ni expulsión del pool); no modifica el contrato archival.
`loadCore()` y `loadTimer()` exponen también metadatos propietarios, no globales.

## Estados y operaciones permitidas

| Estado en memoria | Significado y restricciones |
|---|---|
| `Empty` | Sin documento preparado; no permite captura ni experimentos |
| `Prepared` | Documento validado y referencias resueltas; permite captura exacta o un experimento aislado |
| `TaxesApplied` | Sólo créditos modificados por impuestos; no permite repetir la subfase ni exportar una partida reanudable |
| `EnergyApplied` | Sólo stock y porcentaje energético modificados; no permite repetir, encadenar impuestos ni capturar para guardar |
| `LaborBalanced` | Tareas/labor/flags, moral y topes de almacén normalizados explícitamente; no es activación completa ni permite encadenar fases o capturar para guardar |
| `EntitiesEdited` | Ediciones estructurales y creación limitada de edificios terminados; admite más ediciones de ese dominio, no captura ni fases económicas ni turno completo |
| `LoadNormalized` | Subconjunto explícito de carga offline y RNG inicializado; capacidades incompletas, sin captura SAV, edición, encadenamiento de fases ni turno |

`prepare` puede construir una preparación nueva desde cualquier estado. La fase
actual es una propiedad **en memoria**, no una marca añadida al formato SAV.
También reinicia el RNG propietario a no inicializado; `normalizeLoad` lo siembra
al final desde `options.gameId`. Pedir carga completa falla sin modificar estado.
`collectTaxes` requiere `Prepared` y, al tener éxito, pasa a `TaxesApplied` sin
modificar `options.turn`. El informe y el estado permanecen intactos ante fallo.

`consumeEnergy` también requiere una preparación nueva y pasa a `EnergyApplied`.
No puede ejecutarse después de impuestos ni viceversa: faltan producción,
importaciones y consumo alimentario entre esas fases del turno original. Su
informe incluye solicitudes semánticas de evento 0x33; no se añaden textos
inventados al log SAV ni se ejecutan callbacks de IA.

`normalizeLabor` requiere `Prepared` y pasa a `LaborBalanced`: aplica refresco de
tareas, balance de trabajadores y tope de materiales. No cambia las identidades
ni referencias del grafo, y no se encadena con los otros experimentos. El contrato,
los casos firmados peculiares del original y los límites seguros se describen en
[LABOR_BALANCE.md](LABOR_BALANCE.md). No sustituye la normalización completa de carga.

`insertBuilding`/`retireBuilding`/`insertArmy`/`retireArmy` requieren `Prepared` o
`EntitiesEdited`. Son operaciones transaccionales de almacenamiento, con registros
completos y IDs explícitos; no son construcción, fabricación, demolición o bajas
de combate. Su dominio limitado y las dependencias rechazadas se detallan en
[ENTITY_RUNTIME.md](ENTITY_RUNTIME.md). El inspector sigue sin estas órdenes.

`createCompletedBuilding` comparte ese dominio de etapas, pero sí inicializa un
edificio terminado ordinario, asigna ID de partida y aplica huella, labor local
y caminos de sitios. No es iniciar una construcción pagada; no fabrica unidades
ni resuelve bajas. Los casos especiales no implementados fallan transaccionalmente.

`capture` sólo acepta `Prepared`: copia el documento conservado, valida el
resultado y reemplaza su destino al finalizar. Tras aplicar cualquier experimento falla
explícitamente; una partida con sólo una fase económica aplicada no puede
presentarse como un turno terminado o reanudable. `advanceTurn` devuelve siempre
un error explícito hasta integrar el turno completo, sin modificar el estado.

Es un contrato del API de captura y del CLI, no una frontera de seguridad:
`document()` ofrece una vista const para diagnóstico, que un consumidor C++
podría copiar y serializar por su cuenta. Los consumidores no deben usar esa
vista para eludir el estado de fase ni volver a preparar datos parcialmente
simulados. El CLI no expone esa ruta.

## Subfase fiscal fiel al original

`simulation::planTaxes` calcula un `TaxPlan` sin mutaciones. `State::collectTaxes`
prepara primero ese plan y, cuando ya no quedan operaciones susceptibles de
fallo, escribe únicamente los siete campos `Player::credits`. El plan conserva
`creditsBefore`, `creditsAfter`, `collected` y un informe por territorio con
`calculated` (`int32_t`) y `applied` (`int16_t`).

Fuentes de la implementación:

- `FUN_0046c728`, `CollectTaxes`: recorre territorios 1..N, omite propietario -1,
  convierte cada ingreso a entero con signo de 16 bits y lo suma al jugador.
- `FUN_0046adac`, `EffectiveTaxLevel`: suma el nivel de impuestos del jugador y
  el byte **con signo de `Territory+0x26`**, limitado a 0..5. El nombre heredado
  de ese campo es `tradeState`; no debe sustituirse por `taxAdjust` en `+0x2a`.
- `FUN_0046ae1c`, `TerritoryTaxIncome`: aplica la raíz original, tasas, modificador
  racial guardado en fila 26 y multiplicadores, conservando el orden.
- `FUN_0046a9d8`, `ISqrt`: su algoritmo conserva incluso el caso peculiar en que
  `2` devuelve `2` y `-2` devuelve `-2`; no se reemplaza por `std::sqrt`.
- `FUN_0044d1e4`, búsqueda de edificio terminado por categoría: categoría 9 y
  trabajo restante exactamente cero habilitan el multiplicador City Center,
  sin exigir flags Built o Active. Varios centros no apilan el multiplicador.

La tabla compartida `data::kTaxIncomePercent` en `DAT_004d5838` es
`{0,40,75,100,125,150}`. El extractor también identifica por separado
`data::kTaxMoraleByLevel` y `data::kPopulationGrowthByTerrain`; esta última es
`{3,12,10,7,7,1}`. Se conservan por compatibilidad dos nombres históricos
equívocos: `data::kTaxRates` contiene efectos sobre la moral y `kPopGrowthTable`
corresponde a las posiciones 1..5 de ingresos, no al crecimiento poblacional.
El port fiscal usa la tabla canónica compartida, sin duplicarla localmente.

Se conservan dos divisiones enteras consecutivas, truncadas hacia cero: primero
raíz × tasa / 100, después ese resultado × modificador racial / 100. City Center
duplica el resultado y cualquier `fastProduction` distinto de cero lo duplica
otra vez. El cast con signo de 16 bits ocurre **por territorio**, antes de sumar
créditos; las operaciones de 32 bits reproducen el wrap de forma definida, sin
overflow con signo indefinido de C++.

La fase usa modificadores raciales del archivo, no impone los predeterminados.
Preserva la semántica firmada de población y modificadores, incluso para valores
negativos. Rechaza expresamente propietarios fuera de -1..6, razas fuera de 0..6
cuando tienen un territorio y discrepancias entre slot del propietario y
`Player::index`; no normaliza silenciosamente esos dominios.

Como oráculo del tutorial, la derivación independiente del decompilado y de los
datos de `TUTORIAL.SAV` da **jugador 0: +20, jugador 1: +32**, pasando sus créditos
de 500 a 520 y de 500 a 532. Es un resultado derivado y usado como comprobación;
**no es una captura de ejecución del juego original** ni una prueba de paridad
de un turno completo.

## CLI de laboratorio

Después de compilar, `dl2sim` separa preparación, round-trip e impuestos:

```powershell
.\build\src\dl2sim.exe prepare "C:\GOG Games\Deadlock 2\TUTORIAL.SAV"
.\build\src\dl2sim.exe prepare-archive "C:\GOG Games\Deadlock 2\LEVELS" CHCHT1
.\build\src\dl2sim.exe roundtrip "C:\GOG Games\Deadlock 2\TUTORIAL.SAV" build/prepared-copy.sav
.\build\src\dl2sim.exe taxes "C:\GOG Games\Deadlock 2\TUTORIAL.SAV"
.\build\src\dl2sim.exe taxes-archive "C:\GOG Games\Deadlock 2\LEVELS" CHCHT1
.\build\src\dl2sim.exe turn "C:\GOG Games\Deadlock 2\TUTORIAL.SAV"
```

`prepare` y `prepare-archive` imprimen un resumen JSON del grafo y del turno
guardado. `roundtrip` prepara, captura y publica una copia nueva mediante la
escritura exclusiva de `save_files`; no sobrescribe destinos existentes.
`taxes` y `taxes-archive` ejecutan la subfase una vez, imprimen el informe JSON y
terminan: **no escriben un SAV parcial ni admiten un destino de guardado**.
`turn` falla con un mensaje que enumera lo pendiente. Los datos originales sólo
se leen. `--help` describe las formas admitidas por el CLI.

`economy`/`economy-archive` consultan rendimientos y necesidades sin modificar la
preparación. `energy`/`energy-archive` realizan el experimento energético aislado,
sin producir ni importar antes; tampoco escriben SAV. Ambos contratos se detallan
en `ECONOMY_LAB.md`.

`labor`/`labor-archive` aplican sólo la normalización laboral y de almacén en
memoria. Informan `complete_load:false` y `complete_turn:false`, no aceptan un
destino de guardado y no cambian el inspector gráfico.

`placement`/`placement-archive` consultan emplazamiento y huella de un edificio sin
mutación. Requieren territorio, tipo e índice de casilla. No autorizan por sí solos
construir: no comprueban propiedad, tecnología o recursos. Ejemplos y códigos de
rechazo en `ENTITY_RUNTIME.md`.

`create-building`/`create-building-archive` ejecutan en memoria el inicializador
terminado y sus efectos locales. No aceptan destino SAV. `normalize-load-seeded`
aporta un contexto explícito de prueba para retratos de eventos; no recupera
una secuencia histórica que el archivo no contiene.

## Verificación y límites pendientes

Las pruebas de `tax_phase` contienen oráculos numéricos de redondeo, tasas,
modificadores, centros, producción rápida, narrowing y overflow de créditos,
además de rollback de errores y aislamiento de globales/RNG. Las de
`runtime_state` comprueban el grafo tipado, preparación/captura, propiedad de
datos, transacciones, aplicación fiscal única y bloqueo de exportaciones
parciales. El resultado de las ejecuciones integradas se registra en
[RECOVERY.md](RECOVERY.md), sin deducirlo de que exista el código de pruebas.

Existe un perfil parcial offline para 35..0x120, opciones/campañas, inteligencia
y reseed final de RNG. Las conversiones antiguas y los reinicios de datos IA
ya están portados, junto con mundo cambiado, reinicios y avisos de santuarios.
Con contexto completo se distingue carga headless de activación/UI y del turno
IA aún pendiente (ver `LOAD_NORMALIZATION.md`). La preparación archival
conserva los datos; no afirma que cada palabra histórica sea
semánticamente correcta para una nueva simulación. Tampoco incorpora todavía
el resto de fases. Ya dispone de creación especial, unidades/transporte/cascadas,
demolición no-santuario y comienzo pagado de construcción con eventos/logística,
además de reacciones IA con continuación explícita y rechazo de rebobinado.
`progressBuildingWork` añade trabajo/finalización/reparación y mejoras a partir
de la labor asignada. `queueUnit`, `dequeueUnit` y `produceUnits` añaden colas,
cobros, devoluciones, repetición y creación real de unidades. Son subpasos
explícitos, no un pase económico completo; `produceUnits` recibe su presupuesto
de trabajo del llamador. Las continuaciones conservan también los contadores
de ciudades utilizados al seleccionar retratos de eventos.

Los nodos de cola no tienen ID persistido. Tras modificar contenido/orden o
reemplazar nodos se retiran todos sus handles posicionales, incluso si los bytes
resultantes son idénticos. Los handles de las colas, territorios, edificios y
unidades supervivientes siguen siendo válidos. Una operación fallida no cambia
ninguna identidad; una edición ajena a colas no las invalida.
Las operaciones aisladas e identidades estables no son
una reproducción del layout ni del orden físico de los pools Borland.

La secuencia económica observada en `FUN_0046c7d4` es impuestos, producción 1,
registro de necesidades, importación de déficits, comida, energía, mantenimiento,
producción 2, costes de edificios, población, moral, investigación, revueltas y
balance final. Ejecutar sólo impuestos no permite omitir ese resto ni incrementar
el turno. Las colas ya utilizan logística, creación de entidades y eventos reales,
pero falta integrarlas con el presupuesto producido en el pase económico;
comida incluye unidades y suministro, no sólo población.

Para ampliar la capacidad, seguir [ROADMAP.md](ROADMAP.md) y
[GAME_INTEGRATION.md](GAME_INTEGRATION.md), con criterios de aceptación por fase
y exportación habilitada sólo cuando exista un punto coherente para reanudar.
