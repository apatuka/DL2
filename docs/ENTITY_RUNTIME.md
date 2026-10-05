# Entidades propietarias y consultas de emplazamiento

Este bloque implementa gestión dinámica, construcción y fabricación en operaciones
propietarias aisladas. **No habilita un turno completo ni botones jugables.** Separa el almacenamiento
estructural en `runtime::State`, la consulta pura de casillas en
`simulation::checkBuildingPlacement` y la creación local de edificios terminados
en `simulation::createCompletedBuilding`. Esta última ya inicializa registros,
trabajadores, huellas y caminos, pero no es una orden pagada de construcción.

## Identidad y vida de las referencias

Las órdenes locales económicas (`transferLabor`/`moveLabor`/`resetLabor`,
`controlBuilding`, `movePopulation`, `orderResearch`) preservan las identidades
de entidades y los nodos de colas de producción. La lista local de investigación
no posee esos handles: reemplazarla no retira nodos de fabricación. Sus cambios
son transaccionales y se encadenan antes de `runEconomicPhase`; el sidecar de
destinos de plaga sobrevive a esas operaciones. Véase [ECONOMY_LAB.md](ECONOMY_LAB.md).

La secuencia económica ahora también alcanza crecimiento/moral/investigación,
disturbios y balance final (`State::runEconomicPhase`). Usa la misma reconciliación
de altas/bajas que el prefijo: sobreviven identidades existentes y una unidad
creada/desbandada dentro de la transacción no deja un handle público. La
investigación y los disturbios no crean entidades ni cambian dueños; el daño
de edificios se conserva hasta la reconstrucción final de tareas.
`EconomyPhaseApplied` es terminal y no exportable, igual que el corte anterior.
Véanse contratos y dominios rechazados en [ECONOMY_LAB.md](ECONOMY_LAB.md).

Los handles tipados contienen un slot y una identidad de vida no serializada.
No son IDs SAV ni direcciones del ejecutable. Un registro independiente traduce
los slots de edificios/unidades a posiciones del documento denso. Borrar un
elemento no cambia la identidad de los supervivientes; reutilizar un slot o un
ID de archivo no hace válido un handle retirado.

Los accesores rechazan handles de otra preparación/instancia, retirados o
construidos sólo con `{slot}`. Una nueva preparación exitosa invalida todos los
anteriores; una fallida conserva el estado y sus handles. Mover un estado
transfiere sus identidades al destino y deja vacío el origen. La identidad se
asigna internamente, sin consumir RNG ni modificar el contador de IDs de partida.
No es una capacidad de seguridad contra código C++ que fabrique sus propios datos.

Obtener referencias mediante `buildingById`, `armyById`, `territoryByIndex`,
`tileByIndex` o el grafo. `Graph::buildings/armies` conserva el orden denso del
documento, **no el orden de los slots estables**: utilizar `buildingLinks(handle)`
y `armyLinks(handle)` para consultar relaciones después de una retirada.

Los punteros devueltos y referencias al grafo son préstamos: deben descartarse
antes de una mutación estructural o sustitución exitosa. La estabilidad prometida
corresponde a los handles de supervivientes, no a direcciones de vectores.

## Inserción y retirada estructural

`insertBuilding`, `retireBuilding`, `insertArmy` y `retireArmy` trabajan sobre
copia candidata. Validan el dominio, modifican únicamente registros/enlaces
conocidos, reconstruyen el grafo y publican todo junto. Ante fallo se mantienen
documento, grafo, fase, informe y handle de salida anteriores. El informe identifica
operación, tipo, ID, ubicación, conteos y vecinos de lista.

El llamador suministra un registro completo y un ID explícito no nulo y no
duplicado dentro de su tipo. No se inventan nombres, tareas, experiencia, costes
ni IDs globales. Las inserciones exigen enlaces `prev/next` vacíos; se derivan
los enlaces de lista y, para edificios, el ancla de la casilla. Los demás datos
del registro no reciben inicialización implícita de gameplay.

El dominio actual es deliberadamente limitado:

- Edificios simples de tamaño uno, sin plataforma ni santuario y sin ministro
  asignado (`Building::minister` distinto de cero se rechaza); no se aplican
  marcas de huella, cambios de terreno ni carreteras. Se enlazan al final de la
  lista global coherente. La casilla ancla no puede pertenecer a otro edificio.
- Unidades sin dependencias de transporte, pareja de asedio o trabajos IA.
  La inserción se hace al principio de la lista propia/ajena según propietario
  del territorio. La retirada enlaza los vecinos y actualiza la cabecera. Se
  rechazan clases 4/19 y tipos 35/36; insertar tierra en mar o barcos en tierra
  requiere reglas aún ausentes y también se rechaza.
- Se rechazan referencias de carga entrantes/salientes, `Army::job`, IDs de
  unidades en jobs y trabajos de ministro que requieren efectos aún ausentes.
  En ministros se comprueba tipo 13 por ID de unidad y tipo 3 por territorio y
  casilla de edificio, tanto al retirar como al insertar. No se borran esas
  referencias para simular que se resolvió una baja completa ni se permite que
  una referencia antigua se vincule silenciosamente a un objeto nuevo.
- Las listas afectadas deben ser coherentes; las listas históricas permisivas
  aceptadas por `prepare` no se reparan silenciosamente al editar.
- El archivo puede conservar hasta 1200 edificios/560 unidades. La inserción
  respeta la reserva de un nodo libre del asignador original: como máximo
  1199/559 activos. El registro moderno no reproduce direcciones ni orden físico
  del pool Borland; usa slots propios reutilizables.

Estas operaciones pueden encadenarse desde `Prepared` o `EntitiesEdited`. Todo
éxito deja `EntitiesEdited`, que bloquea captura, fases económicas aisladas y
turno completo. No hay guardado de laboratorio presentado como partida jugable,
ni conexión de estas operaciones a botones del inspector.

El backend estructural no sustituye las funciones de gameplay. Las APIs nuevas
de ciclo de vida sí aplican cascadas/refunds. DeleteUnit no llama por sí mismo a
la IA: desprender taskforces es un paso explícito del llamador, y ciertos trabajos
se limpian más tarde por su scheduler original.

## Huella y comprobación de casillas

`buildingFootprint(type, site, ...)` describe el rectángulo comprobado, de
tamaño 1×1, 2×2 o 5×5: desde la fila del ancla hacia arriba y columnas hacia la
derecha. Los índices son 0..35 sobre una cuadrícula de 6×6. Fuera de ella devuelve
`fits=false` y lista vacía. El 5×5 de plataforma es el área comprobada, **no una
lista de todos los flags escritos** por la colocación original.

`checkBuildingPlacement(document, territory, type, site, ...)` reproduce
`FUN_0044d600` y sus consultas dependientes. Su `bool` indica si se pudo ejecutar
la consulta; la autorización geométrica se expresa con `reason`:

| Código | Resultado |
|---|---|
| 0 | Emplazamiento aceptado por esta consulta |
| 1 | Fuera de la cuadrícula |
| 2 | Casilla ocupada/marcada |
| 3 | Terreno no disponible |
| 4 | Ya existe centro urbano |
| 5 | Puerto sin mar adyacente elegible |
| 6 | Terreno bloqueado |
| 7 | Tipo no permitido sobre plataforma |
| 8 | Ya existe plataforma marina |
| 9 | Edificio exclusivamente marino en tierra |
| 10 | Ya existe santuario |

Se conserva la precedencia de rechazos y la salida temprana original sobre
plataforma libre. Por ello una aceptación no implica que se inspeccionaron todas
las celdas de la huella. Las búsquedas por categoría usan la categoría guardada
del edificio anclado, no requieren que esté terminado o activo.

La consulta **no comprueba propiedad, población, tecnología, fondos, materiales,
logística ni capacidad de asignación**. No elige un sitio aleatorio, no paga,
no escribe carreteras y no crea entidades. Una denegación normal no es un error
de API; un documento/tipo/territorio inválido conserva el informe anterior y
devuelve un error explícito.

Ejemplos de consulta sin escritura:

```powershell
.\build-verified\src\dl2sim.exe placement "C:\GOG Games\Deadlock 2\TUTORIAL.SAV" 1 1 0
.\build-verified\src\dl2sim.exe placement-archive "C:\GOG Games\Deadlock 2\LEVELS" CHCHT1 1 1 0
```

El JSON distingue `placement_allowed` de `complete_build_permission:false`, y
señala `read_only:true` y `applies_construction:false`. No admite destino SAV.

## Creación local de edificios terminados

`src/game/entity_creation.h/.cpp` porta el corte de `CreateBuilding` (`0044dcf4`),
distinto de `StartConstruction` (`0044db50`). La API propietaria es:

```cpp
bool simulation::createCompletedBuilding(
    const save::Document& source, const BuildingCreationRequest& request,
    save::Document& destination, BuildingCreationReport& report, save::Error& error);
```

`BuildingCreationRequest` contiene `territory`, `buildingType` y `site` explícito.
El resultado identifica ID, territorio, tipo, casilla, contador anterior/posterior,
huella y ejecución del balance local y los caminos. Todo se calcula sobre copia:
un fallo conserva fuente, destino e informe, incluso cuando fuente y destino son
el mismo documento; un éxito limpia el error. No hay acceso a `gs`, `gg`, RNG,
callbacks ni archivos. El documento candidato no equivale a una partida activada.

### Dominio admitido y restricciones deliberadas

- Partida válida, no mapa reducido; tierra/mar, tamaños uno/dos/cinco, plataformas,
  SeaHab y santuarios. Sin propietario se admiten tipos no raciales; el acceso
  racial original con owner−1 se rechaza. Ancla explícita entre0 y35.
- Huella completa libre y consulta `CheckConstructionSite` aceptada. Es una
  restricción de seguridad explícita: el `CreateBuilding` original con casilla
  explícita no vuelve a ejecutar esa comprobación. No se amplía su aceptación
  con escrituras inseguras ni se reparan casillas ocupadas. Sí se admiten los
  sockets libres de plataforma según sus reglas originales.
- Sin modo editor ni selección automática
  de casilla. No se consume azar para resolver `site=-1`.
- Lista global de edificios coherente y capacidad para mantener un nodo libre:
  como máximo 1199 activos después de insertar. El nuevo registro va al final
  de la lista, independientemente del orden del vector guardado.
- Sin edificios con `minister != 0` en el territorio que se va a balancear,
  ni trabajo de ministro tipo 3 dirigido a cualquier celda de la nueva huella.
  Las dependencias IA no se omiten silenciosamente.
- Razas, referencias e índices de tablas efectivamente utilizados deben ser
  válidos. Se rechaza el acceso original de vivienda sin tarea de destino
  (`slot=-1`) y se aplican límites explícitos de trabajo a recorridos patológicos.

Estas comprobaciones no constituyen permiso completo para construir: no se
comprueban fondos, importaciones ni disponibilidad tecnológica de una orden.
La tecnología sí interviene donde el original la usa para tareas y mejoras.

### IDs e inicialización

`NextGlobalId` (`00474cfc`) incrementa el contador de 32 bits, conservando
su wrap, y toma sus 16 bits bajos como ID. El corte nuevo reproduce ese cálculo,
pero rechaza cero o colisión con cualquier edificio **o unidad** existente.
No busca otro ID ni salta valores ocupados. Ante cualquier rechazo se revierte
también el contador: esta atomicidad es deliberada, no una afirmación de que los
wrappers originales deshacían todos los intentos fallidos. Plataforma38 reserva
primero el ID de SeaHab39, luego el suyo, pero inserta plataforma→SeaHab: el informe
`createdIds` conserva ese orden. Si sólo queda un slot, conserva plataforma sola,
ambos IDs consumidos y `companionAllocationFailed`, como el original.

`InitBuilding` (`0044d890`) aporta tipo/categoría de tabla, flags activo/recursos acopiados
(`6`), obra restante cero, raza para los tipos raciales y valores iniciales nulos.
El centro urbano cuenta los centros del mismo propietario, incluido el nuevo,
y conserva el estrechamiento con signo a byte de `cantidad-1` para `hubLevel`.
Se reconstruyen únicamente las tareas del edificio recién creado.

### Trabajadores, ocupación y caminos

El helper `prepareCreatedBuildingLabor` reutiliza las reglas portadas de labor:
refresca sólo el edificio nuevo, ejecuta `BalanceLabor` sólo en su territorio y
aplica `RedistributeLabor(T,-1,nuevo)`/`MoveHousingLabor`. El primer slot distinto
de cero y de mejora recibe los trabajadores disponibles de tarea 20, con los
límites y la aritmética firmada originales. No reparte uniformemente entre
tareas, no refresca otros edificios y no ejecuta los topes de existencias de
`EndTurnBalance`. La labor local sí puede cambiar; con población cero también
se aplica la moral 100 original. Los demás territorios no se balancean.

`PlaceBuildingOnSite` (`0044d7b4`) escribe el ID únicamente en el ancla. Tamaño
uno marca `0x3000`; tamaño dos marca ancla `0x1000`, derecha `0x2000`, arriba
`0x3000` y arriba-derecha `0x4000`, conservando los bits anteriores mediante OR.
Los ajustes iniciales de caminos se hacen en el byte `Site+0x10`, nunca en los
punteros de edificios vecinos.

`RecomputeSiteRoads` (`0047dfdc`, hojas `0047dd58`/`0047de94`/`0047ded8`) limpia
los 36 bytes de camino y busca desde el primer edificio de categoría guardada
17 hacia los demás anclajes. Conserva búsqueda en profundidad, orden de cuatro
direcciones, costes, poda y máscaras recíprocas. La búsqueda usa índices de
casilla; el trazado usa sus coordenadas persistidas con signo. También conserva
las escrituras de coste temporal en `Site+0x12` y su ausencia cuando no hay
búsquedas. No modifica caminos del mapa mundial ni tiles. Un terreno que
indexaría fuera de la tabla causa rollback, no una ruta inventada.

### Integración propietaria y CLI

`State::createCompletedBuilding(request, createdHandle, report, error)` conserva
las identidades de todas las entidades supervivientes, asigna identidad al
nuevo edificio y reconstruye sus enlaces tipados. Se admite desde `Prepared`
o `EntitiesEdited`; el éxito deja `EntitiesEdited`. Los fallos conservan estado,
grafo, fase, informe y handle de salida. La captura SAV, las fases económicas
aisladas y `advanceTurn` continúan bloqueados después de esta operación.

El CLI ejecuta el experimento sólo en memoria y devuelve JSON, sin destino SAV:

```powershell
.\build-verified\src\dl2sim.exe create-building "C:\GOG Games\Deadlock 2\TUTORIAL.SAV" 14 1 35
```

La variante de archivo es `create-building-archive <base-HDX/HDD> <entrada>
<territorio> <tipo-edificio> <casilla>`. El JSON distingue
`stage:"entities_edited_in_memory"`, `finished_building:true`,
`paid_construction_order:false` y `complete_turn:false`; muestra el ID, contador,
huella y efectos locales. No hay conexión a botones de construcción del inspector.

## Plantillas de unidades, sin inserción

`simulation::initializeArmyTemplate(document, ArmyTemplateRequest, Army&, error)`
es un inicializador de registro separado de `CreateUnit`, no una unidad fabricada.
Recibe territorio, propietario, tipo e ID explícito no usado globalmente. No
incrementa el contador, no comprueba capacidad ni ejecuta `CanCreateUnit`, no
enlaza listas, no adjunta carga y no inserta el resultado en el documento.

Porta los valores de `00445d30`/`00447190`/`004a6b48`: tipo/clase de tabla,
movimiento base y bonus de Transporters, táctica 26 para las clases de soporte
admitidas, umbral de retirada 100 —el campo heredado `health`, no salud— y cero
en experiencia/daño/carga/jobs/enlaces. Los tres territorios iniciales apuntan
al territorio indicado. El nombre combina raza completa, nombre corto de unidad
e `id & 0x3ff`: copia exactamente hasta 24 bytes, rellena con cero si sobra
espacio y no inventa terminador cuando el nombre ocupa toda la capacidad.

Se rechazan propietarios/razas/tipos inválidos, IDs ocupados, transporte,
parejas de asedio, tierra en mar que exigiría carga y barcos en tierra. Tampoco
se permite usar como salida un registro Army perteneciente al documento de
entrada. Un fallo conserva la salida anterior. Esta plantilla no supone pago,
eventos, combate, descubrimiento, integración IA ni una orden de fabricación;
no tiene comando CLI propio.

## Cobertura escrita para EST-04c

`tests/test_entity_creation.cpp` añade oráculos de registros completos, huellas,
labor local, tecnologías, caminos y coordenadas persistidas, IDs extremos,
colisiones cruzadas, reserva de capacidad y rechazo de ramas pendientes. También
comprueba rollback, alias de documentos, aislamiento de globales/RNG y la
integración con handles/grafo/captura de `State`. El corpus opcional intenta
creaciones soportadas sobre copias de las muestras originales; una negativa
explícita también debe conservar el candidato. Los tests CLI cubren el informe
de creación, entradas rechazadas y ausencia de salida SAV.

Esta sección describe las pruebas añadidas, no afirma su ejecución ni paridad
observada ejecutando el juego original. Los resultados de cada compilación se
registran en [RECOVERY.md](RECOVERY.md).

## Verificación del corte estructural anterior

La suite integrada pasó **23/23**, sin omisiones, en compilación normal y con
AddressSanitizer. `runtime_entities` comprobó 46 preparaciones exactas y un ciclo
reversible de inserción/retirada por documento. `entity_rules` consultó 2.753
territorios y las huellas de 983 edificios de esos 46 documentos. Los casos
sintéticos cubren las 36 anclas de los 47 tipos, todos los motivos, precedencia,
listas, dependencias, límites, referencias caducadas/ajenas, reutilización y
conservación de estado/informes ante fallos. El CLI comprueba entradas inválidas,
ausencia de destinos SAV e integridad del archivo original.

Esos resultados corresponden al corte estructural anterior, no a la creación
EST-04c añadida después. Son oráculos derivados del decompilado/EXE, no una
comparación de partidas completas ejecutadas en el juego original. Tiempos y
registros de ejecución: [RECOVERY.md](RECOVERY.md).

## Evidencia y próximos pasos

Las fuentes de referencia son los asignadores `0044cbec`/`0044577c`, liberación
`0044cc40`/`00445800`, creación de unidad `00445d30`, comprobación `0044d600` y
consultas `0044d1a4`, `0044d2f8`, `0044d3f4`, `0044d440`. Las identidades y
transacciones son una adaptación propietaria nueva, no un supuesto layout SAV.

No activar sin revisión el `buildings.cpp` recuperado. La auditoría detectó
enlaces `prev/next` invertidos en su reconstrucción de listas y offsets erróneos
en la colocación de tamaño dos: `0044d7b4` modifica bytes de carretera
`Site[s+1]+0x10` y `Site[s-5]+0x10`, no punteros de edificios vecinos.
Ese módulo sigue fuera de compilación; las consultas y creación propietarias
nuevas no lo invocan.

Quedan coordinación de turno/combate, órdenes de UI y ejecución programada de
las consecuencias diferidas. La demolición de santuarios con contexto vivo ya
está implementada abajo. No presentar estas operaciones como una partida exportable.

## Ciclo de vida de unidades y edificios

`entity_lifecycle` y `State::createArmy/removeArmy/removeBuilding` ejecutan listas,
capacidad, inicialización y bajas reales; no sólo el backend estructural anterior.

- CanCreateUnit: base de misiles, terreno, límites por grupo y transporte. Creación
  con ID/nombre, carga de tres slots y pareja cruiser35/missile36. Si el misil
  falla por capacidad/apilado, el cruiser solo y el ID intentado quedan como en
  el original, expuestos en el informe; errores de integridad revierten todo.
- DeleteUnit: desprende carga, cascadas recursivas, pareja y listas propias/ajenas.
  DisbandUnit añade mitad de costes y100 colonos para tipos25/31, con balance
  local. La carga destruida no recibe refunds adicionales. Remover taskforces
  es una opción explícita previa, no un callback ficticio del destructor.
- Los jobs13 de ministros se conservan para dispatch posterior. El helper
  `pruneInvalidMaintainUnitJobs` aplica sólo la rama terminal real; no simula
  las tareas activas ni acepta ID0, que el pool original puede confundir con libre.
- DeleteBuilding libera huella/restaura sockets y enlaza vecinos. Borrar una
  plataforma no borra automáticamente sus edificios. Demolish no-santuario
  devuelve la mitad del coste pagado o canónico, conserva SAR/narrowing y balancea
  labor. Tras FreeBuilding, el original consulta el territorio ya puesto a0:
  por ello no se inventa una reconstrucción de caminos en el territorio demolido.
- Demolish de santuario exige la sobrecarga con contexto vivo de campaña/cola
  pendiente. DeleteBuilding sin demolición sigue retirándolo sin esos efectos.

Las identidades de supervivientes se conservan incluso al eliminar en cascada y
en orden distinto al vector físico. Handles retirados/ajenos/caducados fallan.
Las bajas no producen batallas, recompensas ni eventos externos a sus hojas.

## Demolición de santuarios y órdenes individuales

`BuildingRemovalContext` aporta `campaignFlags`, tres estados **int32 vivos** de
objetivos y `PendingShrineState`. No se deducen del número de campaña ni de los
tres bytes archivados. `removeBuilding(..., context, ...)` reproduce0044cefc:
limpia el bit0x10 del territorio, consulta00450320 (flag12 y estado no nulo del
primer objetivo12 canónico) y encola salvo que ese objetivo ya esté cumplido.
La consulta no evalúa victoria ni modifica objetivos. Refund, baja, labor y
rareza del destino de caminos siguen la secuencia anterior.

La cola conserva pares **slot físico de jugador/territorio**, en orden y sin
deduplicar; no guarda direcciones nativas. Tiene diez entradas, según el área
0059f104..0059f153 reiniciada por0046da14/0046e730. El undécimo encolado, referencias
inválidas o flag12 sin objetivo12 causan rollback de toda la operación. La firma
sin contexto sigue rechazando santuarios. `BuildingLifecycleReport::contextAfter`
contiene la continuación; `State::buildingRemovalContext()` la retiene entre
órdenes, movimientos de State y fase económica, y rechaza rebobinarla. Una nueva
preparación la elimina. Los handles de las entidades supervivientes no cambian.
Una vez ligado ese contexto, investigación y fase económica deben usar el mismo
mask vivo de campaña; un mask distinto falla antes de aplicar cambios.

`entity_orders` añade dos órdenes individuales **ya confirmadas**, sin diálogos:

- `orderDisbandUnit`:00419924→00475854, exige unidad del actor local humano.
  No exige territorio propio ni añade desprendimiento taskforce: el llamador
  original no lo hace. Las referencias militares quedan ligadas al slot retirado
  mediante la continuación propietaria descrita abajo.
- `orderDemolishBuilding`:0045b094→00475a60. SeaHab39 redirige a la primera
  plataforma por categoría20; plataforma38 retira los ocupantes de sockets
  −22,−8,−12,+2,−10 y luego la propia plataforma. Cada retirada conserva sus
  refunds y balance; un fallo tardío revierte **toda** la orden. Después ejecuta
  realmente0046f0e0(0), incluso en tierra: reconstruye seis bytes marinos por
  territorio usando edificios43/44, adyacencias y unidades, sin RNG.

Ambas aplican la política de comando actor local/type1/índice coincidente.
Demolición requiere visibilidad4 original y añade propiedad local como política
defensiva explícita frente a visibilidad obsoleta. El refund utiliza al dueño,
no un jugador elegido por el llamador. No implementan Alt/multiselección ni el
botón separado «demoler todo». `State` y CLI las integran en `EntitiesEdited`.

Los flags marinos usan **cualquier** palabra `relations` no nula cuando hay
alianzas, no un bit específico de pacto. El vecino neutral owner−1 lee los cuatro
bytes de Player+0x276 (dentro del último ministro), conforme0044134c. Adyacencias
que leen territorio0 o filas no representadas se rechazan sin fabricar su estado.

### Consecuencias diferidas, aún sin programador de turno

`processPendingShrineConsequences` porta0044b9e4→0044b924 como operación aislada.
Resuelve el `Player.index` **actual** del slot encolado, emite80 a ese índice y81
a los otros seis slots, conserva payload/orden y ejecuta log/reacciones IA reales.
Luego aplica moral−20 con mínimo0 a sus territorios y aumenta `scores.nukesUsed`
con wrap de byte. Comparte una continuación explícita de log/IA/RNG/ciudades;
un fallo de formato o una rama IA aún ausente revierte todas las consecuencias.

El original no drena la cola en0044b9e4: `pendingAfter` queda idéntica. Repetir
manualmente la hoja repite los castigos; no hay un «consumido» ficticio. El
sentinel0 no pertenece al documento y no se inventan efectos sobre él.
**No se conecta automáticamente después de la economía**: WinMain intercala
combate00457624 antes de esta llamada. Falta ese programador; tampoco se expone
una ruta State/CLI para saltárselo y exportar un turno parcial.

### Referencias militares diferidas — CX-01, 2026-10-03

Mantenimiento0046b3dc no desprende taskforces antes de DisbandUnit. Ahora las
bajas conservan sus IDs esperados y referencias propietarias al **slot del pool**,
no a la vida de una entidad. `Document.armyPool` es una continuación opcional
tipada y no serializada: 560 celdas, lista libre y referencias de los 7×50 jobs.
Los campos `Job.armies` del archivo siguen siendo palabras inertes.

La primera alta/baja reconstruye el pool desde el orden del documento; después
se conserva por copia, sin volver a resolver los jobs por ID. El orden inicial
libre es descendente y una baja inserta al frente: la siguiente alta reutiliza
primero el último slot liberado, con la reserva nativa de una celda. Bajas de
carga/parejas conservan su orden postorder. Un pool de 560 unidades activas sin
cabeza libre se puede inspeccionar, pero su baja se rechaza: el original
escribiría a través de una cabeza nula. No se inventa una reparación.

`pruneTaskForceArmies`, `prunePlayerTaskForceArmies` y
`pruneAllTaskForceArmies` implementan0040aebc y sus recorridos explícitos.
Sólo una referencia **no nula** compara el ID16 y propietario firmado actuales
del slot con el ID/owner esperados. Una celda retirada expone ID0/owner0;
si fue reutilizada, se observa su ocupante nuevo. Mismo ID y owner sobreviven
aunque la vida sea otra. Una referencia nula con ID no cero no se limpia.
No se consulta generación, tipo ni `Army.job`, ni se pone éste a cero al limpiar.

Las operaciones de añadir/quitar miembros comparan slots, no IDs esperados,
y no consideran una celda retirada como una ranura de job vacía. Las órdenes,
mantenimiento y el resto de la fase económica preservan esta continuación.
El consumo de comida y los detectores tipo14 recorren el orden físico de las
celdas, no el orden denso del vector tras una reutilización; así conservan
prioridad de alimento y flags/distancias del último emisor respectivamente.
`Graph.jobs` expone ocupante vivo, `pointerPresent` y `poolSlots`; el handle
público de la unidad eliminada **sigue inválido**, incluso tras reutilizar ID/slot.

La validación sólo admite referencias diferidas con metadatos íntegros y una
biyeción comprobada entre celdas vivas y unidades. La lectura de SAV sin ese
contexto sigue rechazando IDs inexistentes. `encode` rechaza bindings retirados,
reutilizados con otro ID o nulos con ID no cero: nunca limpia para poder guardar.
Normalizar de nuevo la carga tampoco puede descartar esas referencias pendientes.

State permite la limpieza como edición explícita y transaccional. **No** se
ejecuta automáticamente al dar de baja ni al finalizar economía. Falta conectar
los puntos originales de IA/reclutamiento/guardado dentro del turno completo;
esta hoja no habilita `advanceTurn` ni captura de estados experimentales.

### Disolución de grupos y cierre de guerras — CL-01/CX-02, 2026-10-04

`dissolveTaskForce` integra la entrega de Claude `c5374a5` con CX-01. Recorre
16 miembros en vivo, libera o transfiere al padre sólo dominio canónico1,
reparenta15 enlaces a job0, limpia todas las coincidencias del padre original
y borra los0xc4 bytes del job **junto con sus16 bindings físicos**.
Padre lleno/AlreadyPresent no deshacen la retirada; autoenlaces y duplicados
conservan el orden original. Cada efecto incluye la celda/ocupante observados.

Con pool presente se consulta el ocupante actual, nunca el ID esperado. Un
binding nulo se omite aun con ID no cero. Una celda retirada sigue siendo no
nula: DeleteArmy deja tipo0/job0 y sólo modifica los links libres+54/+58;
disolver escribe job0 otra vez sin afectar la lista libre ni crear una entidad0.
Una reutilización del mismo propietario admite otro ID; propietario vivo ajeno
se rechaza transaccionalmente. Sin pool conserva el dominio archival validado.
No se inicializa el pool ni se ejecuta0040aebc como efecto oculto.

Hostilidad de `AiSession::reactEvent` conecta004033d0/00403350 antes de la nueva
guerra: mensaje de fin y los50 jobs cuyo destino actual coincide, incluidos
job0 y registros libres cuando se termina una guerra con jugador0. Transferir
a un job posterior puede causar que esa unidad vuelva a visitarse. Máscaras,
cola, actitudes, RNG, jobs y sidecar se publican juntos; cualquier fallo tardío
revierte el conjunto. La ampliación siguiente añade ruptura de pactos y
negociación entre IA; no habilita `RunAITurns`, guardado jugable ni un turno completo.

### Pactos y negociación entre IA — CX-02, 2026-10-05

`AiSession::reactEvent` conecta004071b0 y los handlers offline: la ruptura
secreta borra únicamente la máscara primaria del emisor; la pública borra
las cuatro máscaras bilaterales antes de notificar0x73 a las demás IA.
Conserva el transporte uint16 y los bits altos ajenos. Un ACK rechazado por
`allowAlliances=0` no detiene la guerra: el wrapper original ignora ese retorno.
Los callbacks requieren bindings propietarios instalados; jamás ejecutan las
palabras históricas de Player. Los avisos al humano local exponen un resultado
semántico con retrato categoría20 y su consumo RNG, sin inventar un LogEvent.

`ai_pact_rules` implementa valoración00406b1c, métrica00444274, consultas de
alianzas y normalización00406d10. `AiNegotiationState` aporta explícitamente
cooldowns, estados de oferta, máscaras de propuestas ya procesadas y métricas
vivas de ciudades/territorios/santuarios. No se deducen esos globals del SAV ni
se reinician al recibir un evento. Su ausencia sólo rechaza una rama que los necesita.

La negociación00406dd8 conserva el orden1/2/8/4/16, el plazo de cinco turnos,
destinatarios ocupados y respuesta de IA00406c64. Al aceptar, el emisor sigue
en estado3 y el destinatario vuelve a0 antes de romper pactos incompatibles,
emitir0x73, aplicar las cuatro máscaras y emitir0x72. Los callbacks reentrantes
leen los cambios vivos. La continuación completa viaja en `AiReactionContext`
y el consumidor existente `State::reactAiEvent` conserva su identidad exacta.

Los informes separan cambios de pactos, callbacks, avisos y ofertas. Documento,
continuación, cola, RNG e informe se publican juntos; alias y fallos tardíos
conservan los originales. Una oferta que necesita respuesta humana rechaza
atómicamente en `reactEvent`; el nuevo envoltorio explícito permite suspenderla.
La presentación de avisos y ejecución desde el turno IA siguen pendientes;
CX-02 continúa parcial. El contrato de respuesta humana está descrito
en [AI_NEGOTIATION_CONTINUATION.md](AI_NEGOTIATION_CONTINUATION.md).

`AiEventTransaction` posee documento, bindings, contexto y un historial de
respuestas en snapshots inmutables. `begin` devuelve una operación completada
o pendiente; `answer` exige el checkpoint íntegro de `AiHumanOffer` y una
decisión explícita. La repetición determinista es privada y no ejecuta efectos
externos. Publica el consumo lógico de RNG una sola vez, incluyendo el retrato
categoría15 anterior a la decisión. Conserva la ausencia de evaluación, azar
de rechazo y bonus+4 propios de una respuesta IA. Admite ofertas humanas
anidadas; una respuesta antigua o alterada falla sin perder la pendiente.

`State::beginAiEvent` y `answerAiOffer` publican el evento sólo al completarlo,
tras validar documento y grafo; mientras tanto mantienen las referencias y
el RNG publicados, y bloquean otras ediciones, `prepare` y `capture`.
`pendingAiOffer()` identifica la decisión solicitada. El contexto opcional
`BuildingRemovalContext` comparte la continuación de campaña/santuarios con
las otras operaciones: los pactos exactos2/16 con el humano local actualizan
el objetivo1 activo antes de notificar a otras IA. El resto de las máscaras
no activa ese efecto. Sigue sin diálogo gráfico, red o programación del turno.

`reconcileAiPacts` añade la operación explícita00441400: recorre pares en orden
de filas/columnas, limpia participantes inactivos, entrega el evento58 al afectado
y0x73 a terceras IA, y sólo después intersecta las máscaras actuales y actualiza
ambas referencias anteriores. Los callbacks pueden volver a negociar; sus cambios
no se sobrescriben con una copia anterior. El orden original puede conciliar una
ruptura secreta al visitar antes el par inverso, sin llegar a emitir una denuncia.

Recibe un `AiSession` y contexto propios: continuación IA/RNG, log local opcional
y contadores actuales de ciudades. Sólo exige log existente si alcanza al humano
local; usa el formateador/evento/retrato real, sin copiarlo a `Document.events`.
El informe conserva pares visitados, entregas y efectos IA anidados. No reinicia
actitudes/máscaras ni ejecuta los predecesores del turno. Una oferta humana o
fallo tardío conserva documento, log, cola, RNG e informe anteriores, también
con alias. Su API directa no suspende ofertas. El consumidor reanudable
`AiPactReconciliationTransaction` conserva un cursor de par/fase/destinatario,
los valores anteriores y el XOR capturado. Cada reacción usa una transacción
de eventos propia; ofertas dentro del mismo callback conservan identidad y
avanzan ordinal, mientras una nueva entrega obtiene identidad diferente.
Los logs previos y su RNG no se repiten al contestar. Sólo se publican los
pares intersectados; durante la espera la última reacción del informe es parcial.

`State::beginAiPactReconciliation/answerAiPactOffer` publican juntos documento,
grafo, AI/RNG, log, ciudades y campaña al finalizar todo el recorrido. Durante
la espera bloquean edición, preparación y captura, al igual que una oferta
individual. Comparten `pendingAiOffer()` y las continuaciones ya poseídas por
State; aceptar un contexto antiguo no puede rebobinar el log ni el RNG.
La programación dentro del turno completo sigue pendiente.

### Estadísticas efectivas — CL-02, 2026-10-05

`combat_stats` proyecta un Army vivo a un combatiente propietario y consulta
ataque, defensa, velocidad, cadencia, alcance al cuadrado y precisión. Usa
tablas canónicas y modificadores raciales guardados, experiencia, órdenes,
suministro, tecnología27 y objetivos explícitos de Command Corps.
Propietario actual y original tienen funciones distintas. Los resultados
conservan divisiones intermedias, mínimos y peculiaridades de cada hoja;
no se aplica un multiplicador genérico a todas las estadísticas.

Las consultas son puras y transaccionales, con referencias propias en
`CombatStatsContext`; nunca reinterpretan punteros de Warrior. Las pruebas
cubren39 tipos y7 razas, límites y referencias inválidas. El consumidor de creación se describe debajo; faltan los
consumidores de batalla, disparos, daño, bajas y secuencia de combate.
Evidencia estática nueva en [re/evidence](../re/evidence/README.md).

Ejemplos CLI (sólo memoria, sin destino SAV):

```powershell
.\build-verified\src\dl2sim.exe order-disband-unit "C:\GOG Games\Deadlock 2\TUTORIAL.SAV" 10243
.\build-verified\src\dl2sim.exe order-demolish-building "C:\GOG Games\Deadlock 2\TUTORIAL.SAV" 10241 0 0 0 0
.\build-verified\src\dl2sim.exe demolish-building-context "C:\GOG Games\Deadlock 2\TUTORIAL.SAV" 10244 0 0 0 0 0
```

Los cuatro últimos argumentos son flags y tres estados vivos de objetivo, todos
explícitos; la cola inicial de estos experimentos es vacía. El tercer comando
es la hoja de laboratorio con jugador de refund explícito, **no** permiso local
para demoler edificios ajenos. Ninguno aplica todavía el castigo diferido.

### Creación de combatientes — COM-01, 2026-10-05

`createCombatWarrior` reconstruye00451b68 con las hojas reales de colocación,
retirada, grid y estadísticas. Recibe el documento de sólo lectura, una entrada
escalar de Army y un `CombatCreationContext` completo y explícito. La entrada
puede proceder de un Army vivo —su ID y snapshot deben concordar— o ser sintética
y poseída para futuros consumidores de edificios/milicia/minas. No conserva
punteros nativos ni reinterpreta referencias históricas del SAV.

El pool posee **840 registros** (`0x348`, stride nativo`0x4c`, reset`0xf960`),
con cursor/límite y lista tipada. El reset original fija0/839; esta hoja conserva
el pool suministrado, consume la celda física y avanza módulo840. Misiones
excluidas1..6/15/16/19, warhead defensor y pool lleno son resultados nativos
sin creación, distintos de un error de API. Los campos no escritos del slot
se conservan, incluidos parent/coordenadas de fortclase10, padding y enlaces
secundarios. La primera defensa lee el suministro anterior del slot; sólo
después escribe el nuevo suministro de `foodFlags&3`. La experiencia no se
limita a1000, a diferencia de la proyección de estadísticas.

Colocación: dirección desde `Army.routeOrigin` y `Territory.secondTile`, tablas
de54/72 posiciones, empates verticales, cambio de dirección por terreno4,
defensores con lado aleatorio habilitado, warheads a±127 y minas dentro/fuera.
Si ninguna posición tiene coste menor19, el original **todavía crea** usando
`contador%longitud`; se conserva esa caída a una posición incluso ocupada.
El grid36×36, sus flags/penalizaciones y el territorio seleccionado para coste
anfibio son contextos separados. Las2.320 entradas de coordenadas, costes y
máscara se contrastan con el PE instalado.

La retirada usa órdenes/racial33, inicio de turno para aviones, acceso
`canCreateArmy` y lista extranjera/pacto2 para tierra. No inventa destino para
milicia, fort o warhead. Un avión sin inicio de turno conserva el resultado
`0xffff` y un diagnóstico semántico. Los flags de soporte, máscara de jugadores,
ocupación y contadores se actualizan en el orden original.

El RNG de combate es un LCG32 privado (`0057e240`), con extracción unsigned de
16bits y módulo; no consume el RNG de sesión ni `rtl`. El informe conserva cada
draw y estado posterior. Los bucles nativos de reintento tienen un presupuesto
explícito: agotarlo produce error atómico. El umbral de retirada usa la identidad
entera demostrada del literal80bits y truncamiento x87, con wrap32/narrow16;
velocidad y cadencia se reducen a8bits. Los errores conservan contexto e informe,
también cuando entrada/salida comparten almacenamiento.

Esta hoja no inicializa Battle/grid, ejecuta sus consumidores de edificios o
milicia, simula ticks/disparos/daños/bajas ni publica un turno. El orden y las
dependencias restantes están en [COMBAT_TURN_SEQUENCE.md](COMBAT_TURN_SEQUENCE.md).

### Preparación de batallas y grid — COM-01, 2026-10-05

`combat_preparation` posee840 Warriors,1200 registros de edificios y32 Battles,
con referencias tipadas por índice. El reset004571d4 limpia los pools, cantidad
de Battles, cursores y límites; conserva selección de Battle, grid, relojes,
contadores de bandos y RNG privado porque el original no los escribe allí.
El valor cero de un Battle reseteado incluye defensor0, distinto del valor−1
por defecto del contexto independiente de creación.

`prepareCombatPhase` porta sólo el prefijo00457624 anterior a los cruces:
modo de reproducción0, reset, copia del turno y32 Rand15 de sesión con tag
`Combat`, uno por seed de Battle. No consume Long31 ni azar privado. La palabra
RTL alta y el generador secundario permanecen iguales. Esta precisión corrige
el nombre erróneo de la primitiva en las notas anteriores.

`beginCombatBattle` reconstruye00456150: elige el siguiente slot sin wrap,
reinicia tick/deadline y contadores de bandos, escribe territorio/jugadores/modo,
limpia listas y máscaras y copia el seed a su RNG privado sin consumirlo.
Preserva soporte, padding y roads salvo las escrituras de la rama elegida.
La rama usa el modo int32 completo, aunque guarda sólo el byte bajo; modo256
construye grid de colonia y deja el byte de modo en0. No reinicia el pool de
Warriors entre batallas ni crea participantes implícitos.

Grid36×36: modo0 limpia ambos arrays; si el territorio es mar llena flags con
0x60. Todo modo distinto de0 construye el grid de colonia, incluso en mar.
El borde exterior recibe0x70; cada sitio ordinal ocupa3×3 celdas. Terreno00ff
produce6; los demás valores usan el nibble inferior, con OR de bits. Roads se
leen del byte firmado de Site+10 en ejecución normal, o del WORD previo de
Battle en reproducción. No usa coordenadas guardadas de sitio, ni añade
ocupación de edificios o reconstruye00456618 como efecto oculto.

`createPreparedCombatWarrior` conecta el Battle seleccionado y los pools a
la hoja00451b68 y publica su resultado dentro del mismo estado propietario.
Conserva otros Battles, estructuras, relojes y modo; la semilla de replay del
Battle no se actualiza todavía al RNG posterior a creación: ese write pertenece
al llamador territorial004568c8 implementado en `combat_territory`.

Las APIs conservan entradas/salidas ante errores y admiten alias de contexto e
informe. La selección territorial exterior y la unidad en movimiento siguen
siendo explícitas. No hay integración de este pool con State, ticks ni resolución. Véase
[la auditoría de preparación](COMBAT_PREPARATION_AUDIT.md).

## Participantes territoriales — 2026-10-05

`prepareTerritoryCombat` compone004568c8 hasta antes de004526b0. Publica un
documento con la proyección de sitios y un `CombatTerritoryContext` propio:
Battle/pools/grid, RNG privado y reserva de población de milicia. Conserva
selección por orden de lista y creación militar por IDs ascendentes, edificios
por sitio, milicia por estructura y24 intentos de minas. La variante
`prepareSelectedTerritoryCombat` aplica el contexto temporal00456c10 y restaura
la selección exterior. Los casos sin batalla conservan el estado anterior.

`addCombatBuilding` conserva huellas incluso cuando el pool está lleno,
estructuras y fortificaciones en sus pools distintos, sprite de obra y defensa
con los narrowings nativos. `createCombatMilitia` consume el trabajo de cinco
filas en espiral, también tras creación nula; `createCombatMines` utiliza la
creación real y su secuencia de azar. La semilla de Battle recibe el RNG final
tras todos los participantes. `rebuildCombatDefense` limpia la penalización y
suma10 por fortificación activa sobre la máscara y distancia estricta original,
con wrap de byte. No cambia flags ni RNG.

Todas las salidas conservan rollback, incluso tras creación o escrituras
anteriores. Las referencias son índices/IDs propios, nunca punteros archivados.
El resultado es preparación aislada; no habilita captura SAV, ticks, efectos de
combate ni continuación de `EconomyPhaseApplied`. Evidencia y límites en
[COMBAT_PARTICIPANTS_AUDIT.md](COMBAT_PARTICIPANTS_AUDIT.md).

## Demolición colectiva y búsqueda de movimiento — 2026-10-05

`orderDemolishColony` reproduce la rama confirmada no-editor0045b304. Recorre
los36 sitios vivos en orden, omite categoría **guardada**11 y usa el retiro con
devolución al dueño territorial y balance después de cada edificio. No comparte
las reglas adicionales de la orden individual: no redirige SeaHab, no ejecuta
cascada de plataforma ni reconstruye flags marinos. Esto también permite
conservar un edificio de categoría11 en un socket de una plataforma retirada.
La política explícita exige actor humano/local, índice coherente, propiedad
local y visibilidad4. Cero edificios elegibles sigue siendo una orden evaluada.

`State::orderDemolishColony` conserva los handles supervivientes, retira las
identidades borradas, reconstruye el grafo y conserva la continuación exacta
de campaña/santuarios. Contexto antiguo, autoridad denegada o fallo tardío
revierte todo. No ejecuta consecuencias diferidas ni habilita guardar/avanzar.

`findMovementPaths` implementa00446b08/3c/94 y00446440 como consulta const.
El resultado expone distancias signed16 y flags por índice territorial, fila0
de scratch explícita, mejor distancia al objetivo y contadores de recorrido.
Conserva DFS por bits ascendentes, mejoras estrictas, poda por objetivo,
costes1/2/5/100 y descuentos de depósitos. Cubre dominios1..6 y modo editor
explícito; pactos, ciudades terminadas y flags vivos conservan su orden.
Embarque de dominio5 reutiliza `canCreateArmy` con `movingArmyId`: disponibilidad
de transporte, capacidad y filtros de trabajos IA, sin consumir un slot de unidad.

Rango0 sólo reinicia el scratch. El valor inicial1000 limita realmente qué
distancias pueden mejorar; un rango enorme no descubre costes>=1000. La fila0
no es traversable y adyacencias hacia filas ausentes se rechazan. Esta consulta
calcula distancias; la selección de paso y el movimiento tienen APIs separadas.

CLI de laboratorio, con contexto de campaña y scratch inicial explícitos:

```powershell
.\build-verified\src\dl2sim.exe order-demolish-colony "C:\GOG Games\Deadlock 2\TUTORIAL.SAV" 14 0 0 0 0
.\build-verified\src\dl2sim.exe movement-paths "C:\GOG Games\Deadlock 2\TUTORIAL.SAV" 14 0 2 3 0 64 10243
```

El segundo argumento territorial0 significa sin objetivo; los restantes son
rango, dominio, jugador, máscara de búsqueda y unidad en movimiento (0 si no
hay una). Devuelve sólo JSON de consulta. El primer comando usa cola fría
explícita, opera en memoria y no acepta destino SAV.

## Ejecución aislada de movimiento00446084 — 2026-10-05

El módulo `unit_movement` implementa `simulation::moveUnit`: recibe un ID de
unidad, destino y `routeOrigin` explícitos, con `UnitMovementContext.paths`
para la unidad seleccionada `DAT004c5140`, flags del centinela y contadores
de recursión.
El contexto de unidad seleccionada puede ser cero o una unidad resoluble; no
se deduce silenciosamente del ID que recibe la orden.

La búsqueda comienza en `Army+38` —territorio al inicio del turno—, aunque
`+3c` ya señale otro territorio actual. Su rango es el byte de movimientos
canónico más tecnología46, con el estrechamiento y la extensión con signo de
`00447190`. El campo heredado `strength` (`+0a`) anterior no limita la búsqueda:
al terminar se escribe máximo menos distancia total desde el inicio del turno.
`+38` permanece intacto; `+3c` sólo cambia si el reenlace ocurre; `+40` recibe
`routeOrigin`, o el territorio actual resultante cuando el argumento es cero.

Se publican los flags y las distancias `Territory+a70+owner*2` de la búsqueda
incluso cuando el resultado nativo es falso por rango, permiso de creación,
terreno o exclusión entre crucero35/misil36. Las distancias de otros jugadores
permanecen intactas y el centinela0 sólo tiene representación en el informe y
contexto. Capacidad del pool no es permiso: `CanCreateUnit` puede permitir un
movimiento aun cuando no pueda reservarse otra unidad. Con rango cero, el reset
deja1000 incluso en el origen; el intento de mover allí también devuelve falso.

`report.moved` representa el retorno de `00446084`. El original ignora el
retorno de `ReLinkArmy00445898` y del embarque/desembarque: `moved=true` no
garantiza relocalización cuando la unidad está en una lista mal clasificada
pero estructuralmente válida. `relinks` conserva tanto el retorno como el
cambio efectivo; `transports` muestra los resultados de esas hojas. No se
reclasifican listas ni se reparan enlaces de transporte por conveniencia.

Reenlazar conserva `prev/next` y antepone en la lista elegida por el llamador.
Tipos12 y35 trasladan sus tres slots de carga en orden; cada anteposición
invierte su orden final, sin cambiar el presupuesto, misión o anclas de los
pasajeros. Se portan las misiones11/13, bloqueo mutuo crucero/misil y enlaces
recíprocos de transporte. `00445a04` busca el barco desde la unidad movida,
mientras `CanCreateUnit` busca desde la cabecera propia: ambos recorridos se
conservan. Cuando difieren los jobs, `0040cd0c` usa clase guardada1/2/6 para
objetivos3/9 y la consulta de exploración para objetivo4. Quita el job anterior
y luego intenta añadir; si éste está lleno, el pasajero queda sin job pero
aun así embarca. La rama nativa que disuelve al pasajero y después escribe
su registro retirado se rechaza como error de capacidad con rollback total.

Los avisos de crucero y diagnósticos de unidades terrestres sin transporte se
exponen como datos semánticos. Los escaneos conservan su orden y repeticiones:
destino propio/ajeno, luego inicio de turno propio/ajeno. No producen registros
de eventos ni respuestas de UI. Modo editor se rechaza porque requiere
`004471c0`; faltan descubrimiento, conquista, resolución de combate y secuencia
de turno. La selección de paso `004467e8` es una consulta separada, descrita
abajo. Esta hoja de laboratorio
no aplica autoridad de orden humana y no convierte el proyecto en jugable.

`State::moveUnit` valida el handle, conserva identidades y reconstruye los
enlaces tipados de territorio actual, inicio y ruta. Mantiene la continuación
en `movementContext()` y rechaza rebobinar flags del centinela o profundidades;
seleccionar otra unidad sigue siendo entrada explícita. También un rechazo
nativo publica el scratch y entra en `EntitiesEdited`, sin permitir captura
SAV ni avance de turno. Fallos de API, referencias, capacidades o grafo dejan
documento, contexto, handles e informe anteriores intactos; se soporta alias
de fuente/destino y contexto/informe. No se consume RNG ni se toca estado global.

CLI sólo en memoria, con unidad seleccionada igual al ID y scratch inicial cero:

```powershell
.\build-verified\src\dl2sim.exe move-unit "C:\GOG Games\Deadlock 2\TUTORIAL.SAV" 10243 14 0
```

Devuelve JSON con `native_result`, posiciones, gasto, reenlaces y cantidades de
avisos. Cada comando parte de nuevo del archivo y no acepta destino de guardado.
`tests/test_unit_movement.cpp` cubre hojas, errores tardíos, continuaciones y
consumidor State. Los oráculos son derivados de assembly, no de una ejecución
observada del original. Evidencia nueva en `re/evidence/movement-execution-2026-10-05`
y `re/evidence/movement-taskforce-2026-10-05`; validación del lote en curso.

### Selección del siguiente paso004467e8

`selectMovementNextStep` recibe `MovementNextStepRequest` con origen, destino,
jugador, rango signed32, flag y tipo canónico1..38. El contexto requiere
exactamente N+1 filas de flags/distancias signed16 —incluido scratch0— y
`distancePlayer` igual al jugador solicitado. Se puede reutilizar directamente
`MovementPathReport.territories`; no se calculan ni reescriben distancias y los
valores negativos son válidos. El rango es una entrada independiente del rango
usado para construir esas distancias. `creation.movingArmyId` sigue siendo
explícito para la consulta de transporte.

Los nombres corresponden a los parámetros nativos: los llamadores IA comienzan
el descenso en el objetivo deseado (`origin`) hacia el territorio de inicio del
turno (`destination`). Ambos extremos se excluyen del ranking de candidatos.
Se limpia sólo la máscara `0x2000<<player` y se marca cada nodo actual del
descenso; un candidato debe estar sin marcar, sin `NoTiles` y tener distancia
estrictamente menor que ese nodo. Se recorren adyacencias por bits ascendentes;
el ranking compara la distancia con el **mejor candidato actual**, que cambia
durante el recorrido. Los empates retienen el primer candidato, por lo que no
se sustituye por una ordenación fija por distancia. La preferencia neutral de
IA lee el signed32 vivo en `Territory+a58` y el tipo de jugador con signo.

Se reutilizan `canCreateArmy` para acceso/apilado/transporte y `canScoutOwned`
para exploración racial/tecnológica, con el mismo dominio offline no-editor.
La capacidad de asignación del pool no limita el permiso. Adyacencias mayores
que N se omiten como en el original; bit0 encontrado falla por ausencia de
metadatos nativos del centinela. `nextTerritory==-1` es un resultado nativo
válido; sólo un error de API devuelve falso y conserva el informe anterior.

`traceBuffer` es opcional: ausencia corresponde al puntero nulo nativo; cuando
existe, su vector aporta capacidad y contenido anterior exactos. Registra
cada mejora intermedia de ranking, incluso candidatos posteriormente superados,
por lo que **no representa una ruta**. Si `flag==0` y el origen ya está dentro
del rango (`startWithinRange`), retorna ese origen y sobrescribe las posiciones
0..2 con origen, destino adyacente o candidato elegido, y cero. Si fracasa,
escribe sólo cero en la posición0; en el otro éxito termina las mejoras con
cero. El contenido posterior al terminador queda intacto, incluidas mejoras
escritas antes de la sobrescritura. `traceWrites` conserva el orden exacto de
esas escrituras y `traceAfter` el buffer resultante. Capacidad insuficiente
rechaza toda la consulta en lugar de reproducir una escritura fuera de límites.

El informe posee los flags resultantes en `territoriesAfter`, ranking y
contadores de consulta. Documento, contexto, globales y RNG permanecen intactos;
esta selección no mueve unidades ni conecta por sí sola el turno. Se verifica
en `tests/test_movement_next_step.cpp` con oráculos derivados del assembly.

## Cruces de movimientos — CX-03, 2026-10-05

`movement_crossings` implementa0045727c como hoja aislada. Primero toma un
snapshot de los grupos de las listas extranjeras de territorios con tiles;
agrupa por inicio de turno y jugador, en el primer slot coincidente o vacío.
El array nativo tiene112 filas, incluida la fila0 sin uso, y diez grupos por
fila. El undécimo grupo distinto queda omitido, sin evaluar su puntuación.
El filtro0045723c excluye clase canónica9, misiones especiales y unidades cuyo
inicio de turno ya coincide con su territorio actual.

`scoreArmyPower` reconstruye00401108 con sus cinco argumentos reales. Usa
defensa menos daño, ataque, precisión y cadencia de las consultas originales,
bonificaciones tecnológicas y de los flags, productos con wrap32 y divisiones
signed. Conserva la condición imposible de dominio2 y6 simultáneos; no limita
la puntuación negativa ni aplica un nuevo tope de precisión tras el bonus.
Los cruces pasan los cuatro flags en cero.

El recorrido conserva el orden de territorios y grupos. Los grupos cruzados
de jugadores distintos sin pacto2 se comparan por `wrap32(power*count)` signed;
en empate pierde el grupo ubicado en el territorio de índice mayor. Las sumas
permanecen como snapshot, pero las retiradas recorren la lista extranjera viva
y capturan el siguiente nodo antes de moverlo, incluso cuando cambia transporte.
Reutiliza `moveUnit` con destino inicio de turno y origen de ruta0. El rechazo
nativo del movimiento no revierte sus cambios de scratch.

Después de recorrer cada grupo perdedor se entrega el evento152, aunque no se
haya movido ninguna unidad. El logger general conserva payloads previos del
slot local; su rama IA recibe extras0/0, no los argumentos del texto. Log,
RNG, IA, ciudades, campaña y selección de unidad en movimiento son contextos
explícitos. Un fallo de API conserva documento e informe completos.

`State::resolveMovementCrossings` publica juntos esos contextos, reconstruye
el grafo y conserva los handles existentes. Rechaza continuaciones rebobinadas,
ofertas humanas pendientes y etapas terminales de experimentos. El paso puede
usarse sólo desde Prepared/EntitiesEdited; no acredita que los predecesores del
turno se hayan ejecutado ni conecta directamente desde EconomyPhaseApplied.
No incrementa turno, inicializa batalla ni permite guardar el resultado parcial.
La evidencia estática y el orden exterior están en
[COMBAT_TURN_SEQUENCE.md](COMBAT_TURN_SEQUENCE.md); la verificación integrada se
registra en [RECOVERY.md](RECOVERY.md).

## Costes, importación y comienzo de obra

`construction_payment` implementa004722e0/00471e58/004720f4 y la importación00472974:
cotización, reserva, selección ordenada de proveedores, conectividad, modos de
transporte, pactos, tecnología, tarifas raciales, sustitución de metales y registro
de250 transferencias. Los IDs/fees de proveedor tienen almacenamiento propietario;
no se ejecutan punteros históricos. El territorio seleccionado se aporta porque
el diagnóstico original consulta esa selección y no siempre el destino.

Una cotización denegada puede cambiar scratch; un cobro posterior puede fallar
tras descontar dinero/materiales. `failureMask`, `paid` y el estado resultante
exponen esas consecuencias originales. `true` significa evaluado, no aprobado;
un fallo de API sí conserva todas las salidas. La tarifa0 sigue limitada por
créditos disponibles y el bucle original de metales puede consumir un metal caro
en lugar del barato: ambas rarezas están conservadas y probadas.

`startConstruction` conecta coste/pago/importación, registro canónico de eventos60
y64 o su dispatch IA real, InitBuilding, huella, labor de construcción urgente,
caminos y selección de territorio de puerto. Los callbacks IA de60/64 son defaults
RET verificados, no implementaciones ausentes reemplazadas por éxito.
`Building.cost` contiene importes **ya entregados**, no material pendiente.
Flags6 en una obra significan activo/recursos acopiados: `turnsLeft` conserva el
trabajo por realizar. Iniciar plataforma no crea inmediatamente su SeaHab.

El wrapper offline consume ID antes de denegar sitio/pool/pago. El informe
`accepted=false` conserva ese incremento y efectos de cobro auténticos, sin
entidad/handle nuevo. Errores de dominio, referencias o efectos no implementados
revierten toda la operación. State conserva log, cola/máscaras IA, RNG y colección;
las órdenes siguientes deben usar esa continuación exacta, sin rebobinarla.

`findConstructionSite` reproduce el orden36, primer sitio sin recursos o último
con recursos. Santuario47 marítimo sin otro santuario elige esquina con un Long31
etiquetado; no usa Rand15 ni inventa semilla. Es una consulta independiente:
StartConstruction original no interpreta site−1, su wrapper de autoselección sí.

CLI de laboratorio, sólo memoria y originales de sólo lectura:

```powershell
.\build-verified\src\dl2sim.exe create-unit "C:\GOG Games\Deadlock 2\TUTORIAL.SAV" 14 0 1
.\build-verified\src\dl2sim.exe disband-unit "C:\GOG Games\Deadlock 2\TUTORIAL.SAV" 10243
.\build-verified\src\dl2sim.exe demolish-building "C:\GOG Games\Deadlock 2\TUTORIAL.SAV" 10241 0
.\build-verified\src\dl2sim.exe start-building "C:\GOG Games\Deadlock 2\TUTORIAL.SAV" 14 1 35 1
.\build-verified\src\dl2sim.exe find-site "C:\GOG Games\Deadlock 2\TUTORIAL.SAV" 14 1 1
```

`start-building` recibe una semilla explícita para el replay de log del experimento,
seguido por la orden, y contexto frío de ciudades/cola/máscaras/proveedores. No
recupera transitorios ausentes del SAV. Ningún comando admite destino de guardado.
Pruebas nuevas: `entity_lifecycle`, `construction_payment`, `construction_order`,
`construction_site`, más ampliaciones de creación/State/CLI. Resultados integrados
en [RECOVERY.md](RECOVERY.md).

## Progreso de obras y mejoras

Desde el lote económico del 2026-10-02, el mismo recorrido también se usa en
los pases aplicados `processTerritoryProduction`: conserva outputs cacheados
y tareas vivas, intercalando trabajo, arte y demás rendimientos. El tramo
`State::runEconomicProductionPrefix` conecta presupuestos reales de fábricas,
comida/mantenimiento de las unidades recién creadas y financiación pendiente
de edificios después de producción2. Véase [ECONOMY_LAB.md](ECONOMY_LAB.md).
Los comandos aislados descritos a continuación mantienen sus límites previos.

`building_progress` y `State::progressBuildingWork` ejecutan las ramas de tareas
2 y 21 de `0044f3f0`, no toda la producción. Balancean labor local, recorren las
casillas en orden y calculan el trabajo a partir de los trabajadores asignados.
El output se obtiene una vez por edificio visitado; las tareas se leen vivas,
porque terminar una obra o mejorarla puede cambiarlas durante el recorrido.

Se aplican trabajo signed16, finalización/reparación, nuevas tareas y reparto de
labor, eventos canónicos, mejoras y sus cambios de huella/casilla/caminos. Una
relocalización hacia una casilla posterior puede volver a visitar el edificio.
La rama de centro urbano puede recontar ciudades/santuarios y emitir el aviso de
ciudad; en este llamador, victoria 0 excluye los avisos de santuario 77/78.
Los contadores posteriores se conservan como contexto de los nuevos retratos.
Terminar una plataforma no crea un SeaHab en esta función original.

No se aplican los demás outputs: recursos, investigación, entrenamiento y
fabricación deben encadenarse en su orden dentro de una futura fase completa.
Tampoco se simulan ataques para iniciar reparaciones ni se añaden botones de
asignación/activación de mejoras. Los efectos presentes se prueban como subpasos,
no como turnos jugados en el original.

## Colas y fabricación de unidades

`unit_manufacturing` integra QueueUnit `0044df94`, DequeueUnit `0044e0a8` y
ProduceUnits `0044e174`, con las cinco categorías originales. Añadir cobra los
costes y reserva población para colonizadores; cancelar devuelve el dinero
canónico y los materiales pagados con el estrechamiento original a signed16.
El campo heredado `QueueRecord.count` contiene **trabajo restante**, no unidades.

ProduceUnits recibe trabajo explícito de su llamador. Financia sólo la cabeza
inicial, resta trabajo, crea unidades reales con transporte/parejas y genera
avisos de terminación/cola vacía. Las unidades navales usan `portTarget`; una
creación denegada conserva la cabeza y consume el ID intentado. La repetición
automática usa los bits 1..5 de `Territory.hoverway`, nombre heredado que no
describe una carretera. Se conservan el orden de reinserción, el cobro parcial
y la peculiar máscara `0xf001` del original.

La nueva hoja `collectConstructionRequirements` porta la recaudación incremental
`004720f4`: sólo materiales pendientes y transporte, sin otra cotización, sin
comprobar tecnología ni volver a cobrar el precio monetario completo. El llamador
financia antes el déficit de créditos. Si termina de financiar la primera cabeza,
el original reinicia su trabajo pero **no escribe los nuevos importes pagados**;
se conserva esa rareza, incluso si provoca otro cobro en una visita posterior.

Límites explícitos: cola de 255 nodos por formato de archivo, guardas contra
bucles patológicos y rechazo del territorio centinela 0 como destino naval.
El byte opaco +0x01 de un nodo nuevo se pone a cero; el original no lo inicializa.
Los nodos ya cargados conservan su byte. No se afirma equivalencia con memoria
indeterminada del asignador nativo.

Las colas tienen handles estables, pero sus nodos carecen de ID persistido:
**una mutación de contenido u orden invalida todos los QueueNodeHandle**. Se
readquieren desde QueueHandle. Esto incluye sacar y reponer un nodo idéntico
durante repetición automática. Los errores de API no invalidan nada; los handles
de edificios/unidades/territorios sobreviven. El estado posee log, máscaras/cola
IA, colector, contadores de ciudades y RNG, y rechaza continuaciones rebobinadas.

CLI nuevo (siempre en memoria, sin destino SAV):

```powershell
.\build-verified\src\dl2sim.exe progress-buildings "C:\GOG Games\Deadlock 2\TUTORIAL.SAV" 14 1
.\build-verified\src\dl2sim.exe queue-unit "C:\GOG Games\Deadlock 2\TUTORIAL.SAV" 14 1 1
.\build-verified\src\dl2sim.exe dequeue-unit "C:\GOG Games\Deadlock 2\TUTORIAL.SAV" 14 1 0
.\build-verified\src\dl2sim.exe produce-units "C:\GOG Games\Deadlock 2\TUTORIAL.SAV" 14 1 30 1
```

Cada comando vuelve a partir del archivo intacto: el último ejemplo no recibe
la cola creada por el comando anterior. `produce-units` recibe trabajo de
laboratorio explícito; no lo calcula de máximos hipotéticos ni ejecuta economía.
Las pruebas de integración sí encadenan órdenes, trabajo y bajas sobre un mismo
State, sin permitir exportación o incremento de turno.
