# Evidencia enfocada — 2026-10-05

Binario de entrada: `C:/GOG Games/Deadlock 2/DEADLOCK.EXE`, PE32 x86.
SHA-256: `7da13cf4ac15c2d6004a0e2172a525b9f1d27a0cb1d73590dd1fadff5d453a58`.
El archivo original se mantuvo sin cambios.

Se reconstruyó `ghidra_project/DL2.gpr` con Ghidra 12.1.4, JDK 25.0.2,
lenguaje `x86:LE:32:default` y compilador `borlandcpp`. Proyecto y logs locales
están excluidos de Git; estas exportaciones conservan la evidencia relevante.
`ghidra_scripts/InspectFunctions.java` exporta a archivos nuevos, sin sustituir
los 3.971 decompilados históricos de `re/decomp`.

| Carpeta | Funciones | Uso |
| --- | ---: | --- |
| `cx02-2026-10-05` | 8 | Ruptura, valoración y negociación de pactos; eventos IA. |
| `cx02-handlers-2026-10-05` | 11 | Handlers offline, notificaciones, respuesta, máscaras y retratos. |
| `cl02-2026-10-05` | 13 | Proyección del combatiente, experiencia y seis estadísticas efectivas. |
| `cl03-cl04-2026-10-05` | 11 | Búsqueda/distancias, consultas auxiliares, orden colectiva y conciliación de pactos. |
| `cx02-human-2026-10-05` | 4 | Diálogo/respuesta humana y consulta de objetivo. |
| `movement-execution-2026-10-05` | 12 | Selección del siguiente paso, movimiento/relink/transporte, consultas de campaña y estudio de creación de combatiente. |
| `movement-taskforce-2026-10-05` | 2 | Transferencia de grupo al embarcar y mantenimiento de lista libre. |
| `combat-creation-2026-10-05` | 22 | Colocación, retirada, consultas de combate, RNG y costes de la creación de Warriors; `constants.json` conserva cinco bloques del PE con offset y hash. |
| `combat-sequence-2026-10-05` | 9 | Bucle principal, secuencia/preparación de batallas y conversión x87. |
| `combat-preparation-2026-10-05` | 9 | Reset de grid, terreno/carreteras, reconstrucción de sitios, semilla privada y distinción Rand15/Long31. |
| `movement-crossings-2026-10-05` | 2 | Filtro de cruces y logger general; complementan puntuación/recorrido del lote anterior. |
| `combat-participants-2026-10-05` | 12 | Edificios, huellas, milicia, minas, trabajo asignado, defensa y selección temporal; `platform-mask.json` conserva los225 DWORD de la plataforma marina con offset/hash. |

Cada archivo incluye dirección, pseudocódigo y ensamblado. El decompilador
puede omitir argumentos de llamadas cuya firma no reconstruyó: los PUSH,
accesos y saltos del ensamblado son la referencia para esas discrepancias.
Los tests usan oráculos derivados de estas instrucciones, tablas y exportaciones
históricas; no representan una ejecución observada del juego original.

## REA MCP

`open_binary` con proveedor `ghidra` devolvió `capability_unavailable` /
`unsupported_provider`. El diagnóstico detectó falta de `GHIDRA_INSTALL_DIR`
y Java 17, pero también un bloqueo independiente:
`architecture_unsupported`: Windows Ghidra P0 sólo admite destinos PE x86-64.
Hopper informa `unsupported_host` en Windows. No se abrió sesión nativa ni
se generó un Evidence ID de REA. Corregir las variables de entorno no elimina
la restricción de arquitectura. Se continuó por Ghidra headless directo,
sin modificar ni eludir los controles del proveedor.

## Límites de la implementación

CX-02 implementa efectos offline de ruptura privada/pública y negociación
entre IA, con contexto vivo explícito y callbacks sincrónicos en orden.
El ACK nativo rechazado cuando las alianzas están deshabilitadas no se
confunde con un fallo de la API: la guerra puede continuar. El nuevo envoltorio
`AiEventTransaction` suspende las ofertas humanas hasta una respuesta explícita,
con checkpoint, retrato y RNG propios. La API antigua y la conciliación sin
continuación siguen rechazando esas ofertas de forma atómica. Una personalidad
no instalada o una tabla fuera de dominio rechaza la operación.

CL-02 contiene proyección y consultas puras. Su consumidor `combat_creation`
implementa00451b68 con pool de840 Warriors, colocación, retirada, RNG privado y
registro en el contexto de batalla explícito. Las tablas y constantes se
contrastan con el PE. `combat_preparation` añade reset, semillas, inicio de
Battle y grid, conectado a creación; `movement_crossings` añade puntuación,
retiradas y avisos. `combat_territory` compone selección, sitios, edificios,
milicia, minas y defensa hasta antes de004526b0. Faltan ticks, disparos, daño y bajas. Ninguno de estos paquetes activa
un turno jugable. El orden recuperado está en
[`COMBAT_TURN_SEQUENCE.md`](../../docs/COMBAT_TURN_SEQUENCE.md).

CL-03 añade búsquedas const, selección004467e8 sobre distancias explícitas y la
hoja00446084 con State/CLI, relinks, transporte y restricciones de asedio.
El buffer de selección registra candidatos intermedios y sobrescrituras; no es
una ruta completa. La rama nativa que libera un pasajero antes de seguir
escribiéndolo se rechaza de forma atómica. No se reconstruyen todavía
descubrimiento, conquista ni combate. CL-04 añade la orden colectiva y su
consumidor State/CLI, conservando categoría guardada, recorrido por sitios y
retiros/balances individuales. La conciliación00441400 usa log y callbacks
reales en su orden original; su API directa rechaza ofertas humanas pendientes.
`AiPactReconciliationTransaction` conserva el cursor y delega esas ofertas a
transacciones de eventos, con publicación conjunta desde State al completar.
Las115 exportaciones enfocadas conservan las mismas herramientas/hash;
no se volvió a intentar abrir REA tras confirmar su restricción PE32.

La auditoría de preparación corrigió una inferencia documental anterior:
`00457624→0046c9cc→004ae5b0` consume32 **Rand15**, no Long31. La semilla privada
de combate se copia después mediante00450dd0, sin draw adicional. La evidencia
y sus límites se reúnen en
[`COMBAT_PREPARATION_AUDIT.md`](../../docs/COMBAT_PREPARATION_AUDIT.md).

El cuerpo de milicia sigue separado en los exports004522c0 (prólogo de6 bytes)
y004522c6 (resto del cuerpo): se contrastan juntos con el ensamblado. Esta
separación de Ghidra no representa dos llamadas nativas. Los participantes se
auditan en [`COMBAT_PARTICIPANTS_AUDIT.md`](../../docs/COMBAT_PARTICIPANTS_AUDIT.md).
