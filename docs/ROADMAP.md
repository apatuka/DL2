# Hoja de ruta de la reconstrucción

Punto de partida: estado recuperado en `7eb27de`, documentado en `RECOVERY.md`.
La prioridad es convertir las implementaciones parciales en capacidades
comprobables. No se asigna un porcentaje global: archivos escritos, funciones
decompiladas y módulos compilados miden cosas distintas de una partida jugable.

El [checklist de cierre individual](SINGLE_PLAYER_CHECKLIST.md) desglosa los
pendientes funcionales y sus criterios de aceptación, excluyendo multijugador.

## 0. Base reproducible y recuperación

Completado durante esta recuperación:

- Preservar el baseline con Git y documentar lo terminado, lo parcial y su origen.
- Centralizar configuración/build/pruebas en `tools/build.ps1` y CTest.
- Verificar formatos, recursos, renderizado de motor y arranque/cierre acotado de
  la demostración SDL, además de las tablas y el parser Python.
- Recuperar el soporte de colas y RNG con pruebas concretas y documentar las
  dependencias pendientes en `GAME_INTEGRATION.md`.
- Mantener las pruebas independientes de los directorios temporales de Claude.

Criterio de cierre: build reproducible con las herramientas instaladas y pruebas
registradas cuyo resultado se pueda repetir. Debe quedar explícito qué fuentes
siguen excluidas y por qué. Un build correcto no cierra las etapas siguientes.

Resultado: CTest 6/6 aprobado sin omisiones con la instalación GOG local. Incluye
regresiones para el pool de colas, RNG, primer clic y reapertura de bibliotecas.
Ese fue el resultado de la recuperación inicial. La suite ampliada descrita abajo
incorpora serialización C++ independiente; no se añadieron implementaciones vacías
para ocultar los bloqueos de la activación jugable.

## 1. Cargar y guardar una partida en C++

Completada la lectura/escritura **del documento de archivo** para las 46 muestras
disponibles: carga → guardado → carga con igualdad byte a byte y edición comprobada.
CTest incorporó `save_document` y `save_corpus`; ese hito pasó 8/8. Los
detalles, formatos soportados y límites están en `SAVE_CODEC.md`.

Decisión de integración: se aisló el codec en `save_document.*`/`save_validation.cpp`
porque el intento de `saveload.cpp` mezcla serialización y arranque de sistemas aún
ausentes. El documento posee sus datos, conserva IDs/palabras históricas y ofrece
resolución de referencias sin tocar `gs`, `gg`, pools globales ni RNG. El avance de
preparación propietaria descrito en la etapa 3 ya resuelve referencias conocidas;
las normalizaciones y la activación completa de una partida jugable siguen
pendientes y no se consideran implementadas.

Plan de referencia del hito (la activación se mantiene como trabajo pendiente):

1. Revisar `saveload.cpp` y contrastarlo con `SAVEFORMAT.md`, `savparse.py` y los
   lectores/escritores decompilados. Usar el inventario de `GAME_INTEGRATION.md`
   para cerrar dependencias de forma explícita.
2. Unificar el uso de tablas estáticas y resolver pools, índices `Ptr32`, IDs,
   listas libres/activas y reinicialización del estado. Revisar los límites de
   arrays y los errores de lectura con datos truncados o inconsistentes.
3. Distinguir decodificación de archivo y postprocesamiento de partida: si falta
   lógica de campañas, IA o turnos, exponer esa limitación en la API/prueba; no
   declarar una partida lista para jugar porque callbacks nulos se omitan.
4. Incorporar el lector/escritor al target apropiado y añadir una prueba de
   consola con datos reales y estados sintéticos para las referencias y colas.
5. Comparar los resultados C++ con el parser Python en las muestras disponibles.
   Realizar load → save → load y revisar las diferencias binarias en los bloques
   persistentes contra el formato original.

Criterio de cierre:

- `TUTORIAL.SAV`, los 42 escenarios de `LEVELS.HDD` y las partidas/campañas de
  muestra disponibles se cargan en C++ y sus invariantes coinciden con Python.
- El round-trip conserva el estado persistente. Toda diferencia binaria permitida
  está identificada por campo y justificada por el formato o el decompilado;
  padding histórico y datos transitorios no se ignoran indiscriminadamente.
- Las entradas inválidas producen un error controlado y no un estado aceptado
  como válido. El contrato especifica qué ocurre con el estado anterior al fallo.
- Los resultados se reproducen desde CTest. Los datos originales se leen sin
  sobrescribirlos; las salidas de prueba van al directorio de build.

## 2. Inspeccionar una partida desde la aplicación

Implementado un inspector que consume directamente el documento sin simular turnos
ni activar IA/campañas. Abre por defecto `TUTORIAL.SAV`, archivos mediante `--load`
o arrastre, y escenarios de `LEVELS` mediante `--scenario`. Ofrece plano del mundo,
selección de territorios/objetos, zoom, desplazamiento, datos y sprites estáticos
originales. `F5` guarda una copia nueva, sin modificar el documento ni cambiar su
fuente. Los fallos de carga conservan la sesión anterior.

El terreno es una vista rectangular de inspección, no el renderer isométrico del
original. Los marcadores agregan objetos por territorio y todos los datos están
visibles sin niebla de guerra. Los límites y controles figuran en
`WORLD_INSPECTOR.md`. Se conserva la demostración SMenu mediante `--demo`.

Las pruebas de modelo, sesión, I/O, entrada y vista se añaden a CTest, junto con
arranques acotados del tutorial y de un escenario. Su resultado integrado se
registra en `RECOVERY.md`; no debe confundirse una prueba visual con la activación
de una partida jugable.

Criterio de cierre: abrir una muestra conocida, inspeccionar territorios y objetos
con datos correctos y volver a guardarla desde la aplicación. Esta etapa todavía
no exige una simulación completa ni IA.

## 3. Simulación de un turno local determinista

**En curso; todavía no hay turno completo.** `runtime::State` ya prepara una copia
propietaria y un grafo tipado de referencias de edificios, unidades, territorios,
tiles, colas, ministros y jobs. La preparación es transaccional, deja intacto el
estado anterior si falla y no interpreta palabras históricas como código ni
activa `gs`/`gg`. Una captura en estado `Prepared` conserva el documento.

La primera subfase económica implementada es la recaudación original de impuestos
(`FUN_0046c728` y sus dependencias), con orden de redondeo, modificadores guardados,
cast por territorio y wrap definido. Se aplica una sola vez por preparación,
únicamente en memoria. No avanza el contador de turno; el estado `TaxesApplied`
no puede exportarse como partida reanudable y `advanceTurn` falla explícitamente.
El CLI `dl2sim` permite examinar el grafo, copiar una preparación y consultar el
experimento fiscal. Contratos y límites: `RUNTIME_STATE.md`.

El laboratorio económico incorpora consultas de outputs por edificio/ranura y
necesidades actuales de comida/energía, sin mutar el documento. `economy` no es
un pase de producción aplicado: no termina construcciones ni fabrica unidades.
También incorpora consumo energético aislado desde `Prepared`, con efectos
numéricos y solicitudes semánticas de déficit `0x33`; pasa a `EnergyApplied`
sólo en memoria. No se encadena con impuestos, no publica SAV parciales y no
avanza el turno. API, aritmética, desviación deliberada de ranuras vacías y CLI:
[ECONOMY_LAB.md](ECONOMY_LAB.md). Los resultados integrados de las nuevas pruebas
se registran en `RECOVERY.md`.

Los perfiles de normalización del cargador para versiones antiguas, campañas,
IA, visibilidad y RNG ya tienen un subconjunto propietario explícito. Su entrega
al motor y la activación jugable siguen pendientes. Resolver referencias
conocidas no demuestra haber realizado ese postprocesamiento.
La reconstrucción de tareas, el balance laboral y el tope de almacenes ya tienen
una operación explícita y transaccional: `State::normalizeLabor`, con consultas
puras en `labor_balance.*` y CLI `labor`. Véase [LABOR_BALANCE.md](LABOR_BALANCE.md).
No se aplican implícitamente al preparar; `economy` sigue consultando la asignación
guardada. `LaborBalanced` no habilita todavía carga jugable, guardado parcial ni
encadenamiento con fases fiscales/energéticas aisladas.

El bloque de entidades añade handles estables, inserción/retirada estructural
restringida y consultas puras de emplazamiento/huella. Véase
[ENTITY_RUNTIME.md](ENTITY_RUNTIME.md). La creación terminada ordinaria ya aplica
ID, huella, labor local y caminos de sitios. También hay casos especiales,
pagos, fabricación y bajas con dominios seguros explícitos; faltan órdenes de UI,
demolición de santuarios/campaña y cierre jugable. `EntitiesEdited` permite estos
experimentos y el inicio explícito del tramo económico, sin exportación SAV.

`production-prefix` conecta reinicios→impuestos→producción1→necesidades/imports
→comida→energía→mantenimiento→producción2→costes. Usa recorridos intercalados
de obras/tareas, presupuestos reales de colas, efectos de abastecimiento y un
único contexto de eventos/IA/RNG. No sustituye el primer pase por sumar outputs.
`production-phase` extiende esa secuencia con crecimiento, moral, investigación,
disturbios/deserciones y balance final. `EconomyPrefixApplied` y
`EconomyPhaseApplied` impiden repetir/capturar experimentos. La fase completa
mantiene dominios seguros explícitos: error nativo de texto de deserción local
y bajas con referencias taskforce vivas se rechazan sin cambios parciales.
Siguen faltando el resto del turno y su activación/UI/guardado jugables.

El lote EST-01..08 integra `normalizeLoad` parcial: opciones/perfil offline,
enlaces de objetos/trabajos, continentes/caminos/santuarios, labor y RNG propietario
inicializado al final desde gameId. Las tablas heredadas ya comparten la fuente
canónica de 43 campañas. Véase [LOAD_NORMALIZATION.md](LOAD_NORMALIZATION.md).
La continuación incorpora migraciones 35..37, datos de reinicio IA, visibilidad/
inteligencia de carga y replay de eventos/timer con contexto explícito. Contactos
nuevos se omiten en carga, igual que el original. Ya están conectados mundo
cambiado visual, reinicio propietario, avisos de santuarios y reacciones IA.
Faltan turno IA completo y entrega nativa de la presentación;
`LoadNormalized` no se exporta ni juega.

Completar primero economía, población, recursos, trabajo y colas de producción;
después unidades, movimiento y las fases de turno que los coordinan. Establecer
una única secuencia de fases a partir de `WinMain` y sus llamadas originales.

Integrar RNG, investigación y las reglas necesarias para el escenario de prueba.
No reemplazar sistemas ausentes por callbacks vacíos o un incremento del turno.
Las pruebas deben observar cambios verificables: consumo/producción, progreso de
colas, creación de entidades, movimiento y persistencia tras guardar/cargar.

Criterio de cierre: dos ejecuciones desde el mismo estado y semillas producen el
mismo resultado persistente. Cargar → ejecutar un turno → guardar → recargar
conserva ese resultado. La UI puede mostrar los efectos de un turno sin depender
de funciones de simulación omitidas silenciosamente.

## 4. Partida individual completa

Completar los sistemas necesarios para empezar y terminar una partida:

- Combate, efectos y bajas; investigación completa, eventos, espionaje y victoria.
- Ministros IA, jobs, task forces, misiones y diplomacia, integrados con la misma
  simulación que usa el jugador.
- Nueva partida, generación de mundo, aterrizaje, opciones, preferencias y
  campañas. Comparar semillas y secuencias RNG con evidencia original cuando sea
  posible, no sólo con dos ejecuciones del port.
- Pantallas y diálogos que permitan operar esas funciones desde la aplicación.

Criterio de cierre: una partida nueva y una partida cargada pueden desarrollarse
hasta una condición de victoria/derrota sin intervención de herramientas de
desarrollo. Una campaña de muestra puede avanzar entre escenarios. Registrar
pruebas de regresión para los errores encontrados durante esas sesiones.

## 5. Compatibilidad, presentación y editor

Completar preferencias/atajos, audio y música, cinemáticas, mensajes y pantallas
restantes. Verificar campañas adicionales, variantes del formato guardado y el
editor de mapas. Priorizar aquí lo que no haya sido imprescindible para completar
la etapa anterior.

Criterio de cierre: lista explícita de funciones originales soportadas, diferencias
conocidas y muestras de verificación. Los formatos antiguos sin archivos de prueba
deben seguir marcados como no verificados.

## 6. Multijugador

Completar protocolo, serialización, sesión, sincronización y checksum sobre el
transporte abstracto existente. Probar primero dos peers con loopback y luego un
transporte real entre procesos, conservando el orden y las garantías requeridas.

Criterio de cierre: mensajes y barreras probados, estado consistente entre peers,
partida sincronizada con intercambio de turnos y tratamiento de desconexión o
desincronización. La igualdad entre dos peers del port no prueba por sí sola
compatibilidad de protocolo/CRC con el original; esa compatibilidad necesita una
comparación independiente.

## Criterios de trabajo compartidos

- Una capacidad se considera terminada cuando tiene implementación, integración,
  verificación adecuada y límites documentados; una cabecera no cierra un módulo.
- Respetar tamaños y offsets de estructuras persistentes y registrar la evidencia
  al cambiar la interpretación de un campo, siguiendo `PORTING_CONVENTIONS.md`.
- Evitar múltiples tablas o pools con distinta semántica para la misma entidad.
  Resolver primero la propiedad de las APIs compartidas.
- Conservar los archivos originales de la instalación como entradas de sólo
  lectura. No depender de scratchpad ni de logs privados para compilar o probar.
- Usar paralelismo en tareas separadas por archivos y contratos; integrar cada
  entrega con pruebas antes de acumular nuevos módulos interdependientes.
- Actualizar este documento y `GAME_INTEGRATION.md` cuando una dependencia se
  cierre o un criterio de aceptación cambie con nueva evidencia.
