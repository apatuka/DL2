# Entidades propietarias y consultas de emplazamiento

Este bloque prepara la gestión dinámica que necesitarán construcción y
fabricación. **No habilita todavía esas órdenes de juego.** Separa dos contratos:
almacenamiento estructural en `runtime::State` y consulta pura de casillas en
`simulation::checkBuildingPlacement`.

## Identidad y vida de las referencias

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

La restricción es importante: `DeleteUnit` incluye cascadas de carga y efectos
IA, `DisbandUnit` puede devolver población/materiales, y construir incluye pago,
empleo, eventos y caminos. El backend estructural no sustituye esas funciones.

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

## Verificación ejecutada

La suite integrada pasó **23/23**, sin omisiones, en compilación normal y con
AddressSanitizer. `runtime_entities` comprobó 46 preparaciones exactas y un ciclo
reversible de inserción/retirada por documento. `entity_rules` consultó 2.753
territorios y las huellas de 983 edificios de esos 46 documentos. Los casos
sintéticos cubren las 36 anclas de los 47 tipos, todos los motivos, precedencia,
listas, dependencias, límites, referencias caducadas/ajenas, reutilización y
conservación de estado/informes ante fallos. El CLI comprueba entradas inválidas,
ausencia de destinos SAV e integridad del archivo original.

Son pruebas de este corte y oráculos derivados del decompilado/EXE, no una
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
Ese módulo sigue fuera de compilación; las consultas nuevas no lo invocan.

El siguiente paso es integrar inicialización real de registros, huellas y caminos,
asignación local de trabajadores, pago/importaciones y eventos de construcción;
después finalización y fabricación con capacidad/transporte y trabajos IA.
EST-04, CON-02 y las órdenes de construcción/fabricación siguen parcialmente
pendientes en [SINGLE_PLAYER_CHECKLIST.md](SINGLE_PLAYER_CHECKLIST.md).
