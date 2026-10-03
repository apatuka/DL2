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

Quedan coordinación de las fases completas de producción/turno, órdenes de UI,
demolición de santuarios con efectos de campaña y su integración completa. No presentar las
operaciones aisladas siguientes como un turno ni una partida exportable.

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
- Demolish de santuario rechaza los efectos aún ausentes de campaña/cola pendiente.
  DeleteBuilding sin demolición sí puede retirarlo sin inventar esa secuencia.

Las identidades de supervivientes se conservan incluso al eliminar en cascada y
en orden distinto al vector físico. Handles retirados/ajenos/caducados fallan.
Las bajas no producen batallas, recompensas ni eventos externos a sus hojas.

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
