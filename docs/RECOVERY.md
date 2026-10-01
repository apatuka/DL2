# Recuperación de la sesión de Claude

Fecha de recuperación: 27 de septiembre de 2026, zona `America/Asuncion` (UTC−03).

Actualizaciones posteriores a la recuperación inicial: `SAVE_CODEC.md` documenta
el codec C++ independiente, con 46 roundtrips exactos; `WORLD_INSPECTOR.md` describe
la vista gráfica de partidas y escenarios; `RUNTIME_STATE.md` documenta la
preparación propietaria y la primera subfase económica. Las tablas históricas
de esta nota conservan el
estado/evidencia del primer hito; `saveload.cpp` integrado con activación de juego
sigue pendiente.

El proyecto conserva una base C++20/SDL2 que compila y permite inspeccionar recursos,
sprites y el panel SMenu D000. Ahora también carga una partida como documento de
inspección: mapa, territorios, edificios, unidades y copias sin modificación. La
lógica de partida está parcialmente escrita y todavía no está integrada. Cargar
el documento no equivale a activar el estado de juego, simular un turno ni jugar.

## Lote EST-01..08 — 2026-10-01

Sobre `acdda61`, se integró una normalización **parcial** offline, distinta de la
preparación archival: opciones/perfil, enlaces de edificios y trabajos, continentes,
caminos de tiles, santuarios, balance laboral, restricción de investigación y
resembra final de RNG propietario desde `options.gameId`. El commit se realiza
sólo después de validar documento/grafo/RNG; errores conservan todo el estado.

`LoadNormalized` no es jugable ni exportable como SAV reanudable. `normalize-load`
y `normalize-load-archive` imprimen JSON con las siete capacidades pendientes;
`activate` rechaza explícitamente la carga completa. El inspector no cambia.
Contrato y fuentes en [LOAD_NORMALIZATION.md](LOAD_NORMALIZATION.md).

Las tablas de economía ahora son adaptadores de la fuente canónica. Campañas
son **43**, no 32, en todos los contratos compartidos. Una prueba incluye juntas
las cabeceras heredadas (descubrió y permitió unificar tres helpers de IA/turnos),
comprueba cada campo de los adaptadores y contrasta tablas adicionales y campañas
directamente contra bytes del EXE original. No instala callbacks de gameplay vacíos.

Verificación: **28/28 sin omisiones** tanto normal (`build-verified`, **43,20 s**)
como con AddressSanitizer (`build-save-asan`, **144,16 s**, `/fsanitize=address`).
Cinco pruebas nuevas (`session_rng`, `load_derived`, `load_profile`,
`table_contracts`, `runtime_load`) y contrato CLI ampliado. No hubo hallazgos
de memoria en la suite ASAN final.

El corpus tiene **38 normalizaciones parciales exitosas y 8 rechazos esperados**:
`CYTH3`, `HUMAN5`, `RELU5`, `TARTH2`, `TARTH3`, `TARTH4`, `UVA3`, `UVA4`, todos
versión 35. Esos ocho siguen pasando inspección y round-trip archival exacto;
se verifica el rechazo transaccional porque faltan sus migraciones de carga.
No se cambiaron entradas para forzar aceptación. Las hojas de derivados y RNG
aisladas se verificaron en las 46 muestras. El tutorial normalizado conserva
turno 1, informa 36 territorios/6 edificios y seed final 7788 en ambos generadores;
no se escribió ningún archivo en la instalación original.

Se comprobaron rollback tras fallar el balance laboral, handles estables durante
normalización, movimiento/reset de sesión con RNG, bloqueo de exportación y de
turno parcial, alias fuente/destino y aislamiento de `gs/gg`/RNG global. Oráculos
numéricos provienen de decompilado/assembly; no son resultados obtenidos ejecutando
el juego original. EST-03/06/08 quedan cubiertos en su contrato; EST-01/02/04/05/07
siguen parciales. IA, visibilidad/contactos, efectos completos de entidades y el
orden de consumo RNG de las futuras fases no se declaran terminados.

## Verificación de entidades y emplazamiento — 2026-09-28

El lote posterior a `3793805` pasó **23/23 pruebas, sin omisiones**, en
`build-verified` (34,75 s) y con AddressSanitizer en `build-save-asan` (114,71 s).
No se detectaron errores de memoria en los recorridos instrumentados. Logs en
`build-verified/Testing/Temporary/LastTest.log` y su equivalente ASAN.

`runtime::State` incorpora identidades de vida para rechazar handles retirados,
ajenos o de otra preparación. Inserciones/retiradas estructurales de registros
simples validan listas, conservan referencias supervivientes y publican documento
y grafo juntos. Se rechazan dependencias de transporte, asedio y trabajos IA,
incluidos ministros tipo 3 por ubicación y tipo 13 por ID. `EntitiesEdited`
bloquea captura y fases de gameplay todavía incompletas.

`entity_rules.*` reproduce la consulta original de emplazamiento y su geometría,
incluidos motivos 0..10, prioridad de rechazos y salida temprana de plataforma.
El CLI `placement`/`placement-archive` permite consultarla sin cambiar el estado;
indica explícitamente que no comprueba permiso completo ni aplica construcción.

La prueba de entidades recorrió **46 documentos con captura exacta y un ciclo
reversible de inserción/retirada en cada uno**. La de emplazamiento recorrió los
mismos 46 documentos, **2.753 territorios y 983 edificios**. Los sintéticos cubren
47 tipos por las 36 anclas geométricas, motivos y precedencia, reutilización de
slots/IDs, supervivientes, referencias ajenas/caducadas, movimiento del estado,
fallos transaccionales, dependencias y límites de 1199/559 activos al insertar.
Las fuentes físicas de 1200/560 registros continúan admitidas para preparación.

Estos resultados proceden de la implementación y oráculos derivados del código
original; no de ejecutar una partida completa del original. No se añadió una
orden jugable de construcción/fabricación ni se activó `buildings.cpp`: su
auditoría encontró errores de enlaces y de offsets, documentados para el
siguiente port. Contrato y próximos pasos: [ENTITY_RUNTIME.md](ENTITY_RUNTIME.md).

## Verificación de tareas y balance laboral — 2026-09-28

El nuevo bloque pasó **21/21 pruebas, sin omisiones**, tanto en `build-verified`
(28,76 s) como con AddressSanitizer en `build-save-asan` (77,38 s). No se
detectaron errores de memoria en los recorridos instrumentados. Los registros
locales están en `build-verified/Testing/Temporary/LastTest.log` y su equivalente
en `build-save-asan`; las salidas de build no se incorporan al repositorio.

`labor_balance.*` implementa reconstrucción de tareas y requisitos tecnológicos,
redistribución, balance en cuatro pasadas y límite superior de materiales.
`State::normalizeLabor` lo aplica transaccionalmente sobre su copia propia;
`dl2sim labor`/`labor-archive` muestran el informe antes/después. No modifica
colas, entidades, RNG ni turno, ni exporta la normalización parcial como SAV.

La prueba específica recorrió **46 documentos y 983 edificios**. Las pruebas de
runtime verificaron la aplicación, el grafo estable, transiciones y rollback en
esas mismas muestras. Los oráculos sintéticos independientes cubren tecnología,
mejoras, construcción, bloqueos, colas por número de nodos, prioridades, viviendas
inactivas, población/moral firmadas y extremos de labor de 32 bits. También se
comprueba la integridad de miembros no serializados, eventos binarios y globales.

La revisión del decompilado/assembly confirmó comportamientos originales que no
deben simplificarse: descuentos de capacidad en orden de ranura, valores de labor
negativos generados, máscaras tecnológicas extendidas con signo y traslados a
vivienda que no requieren categoría residencial. El módulo admite labor negativa
de entrada porque no se usa como índice. Rechaza el fallback de vivienda de índice
−1 y limita intentos de traslado para evitar escrituras inválidas o trabajo
patológico. Son límites declarados, no callbacks vacíos ni reparaciones silenciosas.

El inspector permanece de sólo lectura. Todavía faltan otros perfiles de carga,
gestión dinámica de entidades, producción/logística aplicada, órdenes manuales
y el turno completo. Contratos y próximos pasos: [LABOR_BALANCE.md](LABOR_BALANCE.md).

## Verificación del laboratorio económico

El nuevo hito pasó **20/20 pruebas, sin omisiones**, tanto en `build-verified`
como con AddressSanitizer en `build-save-asan`. No se detectaron errores de
memoria en esos recorridos. `production_plan` y `resource_needs` se suman a la
suite previa; `runtime_state` y `simulation_cli` comprueban las nuevas rutas.

Las consultas de producción recorrieron **46 documentos y 983 registros de
edificios**, conservando sus bytes. Necesidades/energía se comprobaron también
en las 46 muestras; se informaron nueve solicitudes semánticas de déficit en
los experimentos aislados. No son déficits observados después de un turno del
original: se calculan sin producir/importar antes sobre el stock guardado.

Los oráculos sintéticos cubren recursos de casilla, huellas, santuarios,
modificadores raciales, energía con signo, redondeo, overflow y diferencias entre
consulta escalar y por edificio. Se corrigió un rechazo excesivo de slots de
jugadores inactivos y se añadió una regresión: sólo se valida índice/raza del
propietario relevante. El caso indeterminado original de ranuras vacías se
normaliza deliberadamente a cero y se señala en el API, CLI y documentación.

`State::consumeEnergy` aplica únicamente stock energético y porcentaje de
energía, con validación previa y rollback ante fallo. El estado `EnergyApplied`
no permite repetir, encadenar impuestos ni capturar para guardar. Los eventos
son datos semánticos en el informe; no se inventan textos SAV ni efectos de IA.
Las pruebas de bytes verifican que no cambia otros campos ni el turno.

`dl2sim economy` ofrece consultas sin mutación; `energy` es el experimento
aislado. Ambos tienen variantes HDX/HDD y rechazan destinos de guardado. Véase
[ECONOMY_LAB.md](ECONOMY_LAB.md) para fórmulas y el próximo corte de integración.
Al terminar ese hito faltaban balance laboral, producción aplicada, logística,
unidades y la secuencia completa. El avance posterior del balance se registra
arriba; el inspector sigue sin acciones de juego.

## Verificación de preparación y fase fiscal

La suite de ese hito aprobó **18/18 pruebas, sin omisiones**, en `build-verified` y
también en `build-save-asan` con AddressSanitizer. No se detectaron errores de
memoria en esos recorridos. Se añadieron `tax_phase`, `runtime_state` y
`simulation_cli`; los casos anteriores de inspección y archivos siguen pasando.

`runtime::State` prepara un documento propio y referencias tipadas sin activar
globales, callbacks ni RNG. El corpus confirmó **46 capturas exactas y fases
fiscales deterministas**. Los tests sintéticos comprueban referencias, colas,
ministros, jobs, propiedad, rollback y el rechazo de capturas tras una fase
incompleta. El CLI verifica además publicación exclusiva, fuente inalterada y
rechazo explícito del comando de turno completo.

La fase fiscal reproduce el decompilado de `CollectTaxes`: sólo cambia créditos,
se ejecuta una vez por preparación y no incrementa el turno. El tutorial da
**+20 al jugador 0 y +32 al jugador 1**, de 500 a 520/532. Es un oráculo derivado
del código y datos originales, no una comparación contra un turno ejecutado en
el juego original. No se publican SAV de ese estado parcial.

La revisión corrigió semántica heredada de unidades: ubicación actual en +0x3C,
inicio en +0x38, movimiento en +0x0A y umbral de retirada en +0x26. Una regresión
usa Army 8204 de `Campaign/ChCht001.CPN` (inicio 15, actual 4), además de un caso
sintético de marcador gráfico. Se corrigió también la identificación de tablas
fiscales y crecimiento: el extractor verifica ahora **53 grupos sin diferencias**.

El inspector sigue siendo de sólo lectura. Faltan normalizaciones de carga,
gestión dinámica de entidades y las demás fases económicas, movimiento/combate,
IA, eventos y victoria. Este hito no cierra la etapa de turno local determinista.

## Verificación del inspector gráfico

El nuevo modo predeterminado abre `TUTORIAL.SAV` y ofrece mapa rectangular,
selección, consulta de objetos y sprites originales. La demostración histórica
permanece disponible con `--demo`. Véase `WORLD_INSPECTOR.md` para controles.

En `build-verified`, la suite ampliada aprobó **15/15 pruebas, sin omisiones**.
Incluye I/O compartido, cámara y selección, sesión transaccional, eventos SDL,
renderizado y arranques independientes del inspector y de la demostración.
Además del tutorial, la prueba gráfica recorrió 42 escenarios y tres partidas/
campañas, con 25 tipos de unidad; fixtures sintéticos cubrieron páginas de
objetos, minas terrestres/marinas y mapas reducidos. La navegación y el dibujo
conservaron los bytes codificados. El corpus del codec mantuvo sus 46 roundtrips
exactos y las comprobaciones de edición/protección de archivos.

La misma suite aprobó **15/15 con AddressSanitizer** en `build-save-asan`, sin
errores de memoria detectados en esos recorridos. Esa ejecución incluye fuentes
y sprites reales; no constituye una prueba de todos los estados posibles.

Se inspeccionaron visualmente capturas RGB555 del tutorial y `CHCHT1`. Se
comprobó también que una captura existente no se sobrescribe y que una fuente
ausente hace fallar el arranque automatizado. Los resultados no equivalen a
una comparación visual completa contra el original ni a una partida jugable.

## Punto de recuperación y evidencia

El commit `7eb27de` (`chore: preserve recovered Claude project baseline`) conserva el
estado recibido después de la última reanudación de Claude, incluidos los archivos
escritos hasta aproximadamente las 21:54, las herramientas y la exportación `re/`.
Los productos de `build/` y la base local `ghidra_project/` permanecen en disco, pero
no están incluidos en ese commit. El historial de Claude y su directorio temporal
son referencias locales; no se incorporan completos al repositorio.

Las afirmaciones de los agentes históricos se contrastaron con los archivos
existentes. Se distinguen de las comprobaciones ejecutadas en esta recuperación:

| Comprobación | Resultado y alcance |
|---|---|
| Compilación del baseline recibido | Reverificada con éxito en el entorno MSVC existente; build incremental de cuatro objetivos. No es una reconstrucción limpia de todos los módulos aún excluidos. |
| Parser Python de guardados | Reverificado: 46/46 partidas, campañas y escenarios pasan las comprobaciones de referencias cruzadas de `savparse.py`. |
| Tablas extraídas | Reverificadas por `tests/test_game_data.py`: 51 grupos de tablas; JSON y C++ generado sin diferencias contra la extracción del ejecutable original. |
| Exportación de ingeniería inversa | Inventario contrastado: 3.971 archivos decompilados y 443 imágenes de sprites. |
| Pruebas del motor, aplicación y soporte de juego en CTest | 6/6 aprobadas, sin omisiones, tras incorporar colas/RNG y corregir dos regresiones del motor. Reconstrucción desde cero en `build-verified` (46 pasos de compilación/enlace). |
| Lector/escritor C++ de partidas | Sin validación funcional; `saveload.cpp` continúa excluido de la compilación por dependencias incompletas. |

La validación del parser Python no valida automáticamente `saveload.cpp`, y la
compilación del motor no valida la lógica de los módulos que CMake todavía omite.

La suite actual incluye infraestructura de juego, píxeles/entrada/SMenu, recursos
originales, parser SAV, tablas y arranque/cierre de la demostración con SDL ficticio.
El recorrido de recursos verificó 2.141 payloads, decodificó 9 imágenes y dibujó 60
menús en memoria. Las pruebas reprodujeron y permitieron corregir la reapertura de
una CAM cerrada y la detección falsa de doble clic al arrancar. No prueban todavía
equivalencia visual completa ni una partida jugable.

Se corrigió también el entorno MSVC localizado: CMake y el compilador usaban
páginas de códigos distintas para detectar cabeceras. `tools/build.ps1` iguala
entrada y salida de consola a UTF-8. El primer directorio experimental
`build-recovery` conserva una caché anterior con detección incorrecta; para seguir
trabajando, usar `build-verified` o configurar un directorio de build nuevo.
En `build-verified` se comprobaron los 38 objetos de Ninja: todos registran sus
dependencias, incluidas `cygame.h` para `main.cpp` y las cabeceras de estado para
`globals.cpp`. Las pruebas opcionales devuelven 77 (omisión) si faltan los datos
originales; ese camino también se comprobó y no afecta al 6/6 con datos presentes.

## Qué ocurrió en la sesión anterior

La petición original fue reconstruir en C++ el juego instalado en
`C:\GOG Games\Deadlock 2`, usando ingeniería inversa con Ghidra y evaluando SDL2.
Claude exportó el ejecutable, creó la infraestructura común y distribuyó el trabajo
entre once agentes. Tres entregaron informes finales satisfactorios; ocho quedaron
interrumpidos por el límite mensual de gasto de la API (`HTTP 429`).

Hubo reanudaciones a las 16:40 y 21:40 del 27/09. La tercera tanda de trabajo importa:
escribió implementaciones de guardado, edificios y colas, generó tablas estáticas y
reparó la compilación de CYLib. Un diagnóstico basado sólo en los archivos de las
16:59 subestima ese progreso. La última notificación de fallo corresponde al agente
de ministros IA a las 21:56:16; la actualización posterior del archivo principal
incluye metadatos, no una nueva entrega de código.

El plan histórico consistía en completar los módulos, integrar y compilar todo,
incorporar nombres a Ghidra y después iniciar la UI del juego. No llegó a esa fase
de integración general ni a una pantalla de partida funcional.

## Mapa de los once agentes

Esta tabla describe el estado recibido en `7eb27de`. Los horarios son locales y
los resultados históricos no deben confundirse con las verificaciones actuales.

| ID de agente | Trabajo | Artefactos recibidos y estado | Pendiente al interrumpirse |
|---|---|---|---|
| `ad26faffe6063278b` | Base C++/SDL2 | Entrega final 15:17. `src/formats/`, `src/platform/`, `dl2tool` y demostración inicial. Reportó build limpio, I000 idéntico píxel a píxel y pruebas offline de vídeo/entrada/audio. | Ampliaciones posteriores a la base; las pruebas históricas quedaron fuera del proyecto. |
| `a7c6613a4d10c0b1d` | Estructuras y SAV | Entrega final 15:38. `game_state.h`, `SAVEFORMAT.md`, `globals.tsv`, `names_structs.tsv`, `savparse.py`; reportó 46/46 archivos válidos. | Campos todavía desconocidos y conversiones de versiones antiguas sin muestras reales. El lector C++ era otra tarea. |
| `a1004e20bbd79ec9e` | Sprites y animaciones | Entrega final 16:45. `src/sprites/`, `data/sprites.json`, `extract_sprites.py`, `SPRITES.md`, `names_sprites.tsv`. Reportó 427 tipos, 6.771 frames, 27 scripts y renderizados inspeccionados. | Integrar sprites/animaciones en las vistas reales del juego; quedan nombres y detalles de scripts inferidos. |
| `ac129577e7feceb14` | CYLib/SMenu | Interrumpido 21:53. `src/engine/`, comandos `render-menu`/`render-tile` y D000 interactivo en `main.cpp`. Reparó los errores de build a las 21:42 y generó renderizados a las 21:44. | `ENGINE_API.md`, revisión completa de la API y publicación del inventario de nombres; quedaron 837 nombres en scratchpad. |
| `a329e3aa549563358` | Tablas estáticas | Interrumpido 21:51. `extract_tables.py`, `data/tables.json`, `data_tables.h/.cpp`; añadió este `.cpp` a CMake y refinó layouts de tipos de edificio/unidad. | Su verificación de compilación no concluyó por problemas con los comandos batch. Faltaba `DATA_TABLES.md`. Las tablas se reverificaron durante la recuperación. |
| `aff853d1da18f1e33` | Economía y producción | Interrumpido 21:53. `economy.h`, `economy_tables.cpp`, `queues.cpp`, `buildings.cpp` (aprox. 58 KB). Implementaciones parciales sin integrar. | Producción, población, unidades y numerosas funciones declaradas; pruebas y documentación del módulo. |
| `a5d6641efd971d0a1` | Ministros IA y jobs | Interrumpido 21:56. Investigación de `RunAITurns`, sus llamadas y contratos vecinos en el historial; no escribió archivos propios. | Implementaciones, pruebas y documentación. |
| `a9d9b46e6a54fa803` | Task forces y misiones IA | Interrumpido 21:54. `ai_api.h`, `ai_taskforce.h` y ampliaciones de `globals.h`; reescribió las cabeceras en la última tanda. | `.cpp`, pruebas y documentación. Las declaraciones no son lógica ejecutable. |
| `a0ff01090b5348cea` | Turnos, combate, eventos, espionaje, investigación y victoria | Interrumpido 21:51. `turn_api.h` y generador temporal de tablas. | Implementaciones del turno/combate y pruebas. El generador final quedó escrito sin producir sus `.inc`. |
| `a712ac2594bf2671b` | Red y sincronización | Interrumpido 21:51. `net_transport.h`, `net_protocol.h`, `net_session.h`. `LoopbackTransport` sí incluye implementación inline. | Implementación de protocolo/sesión/sync, CRC integrado, pruebas y transporte entre procesos. |
| `abd8414234cd41c87` | Flujo, save/load y generación del mundo | Interrumpido 21:51. `gameflow.*`, `saveload.*` (aprox. 54 KB de C++), `newgame.h`, `campaign_flow.h` y ampliación del RNG compatible. | Integración y pruebas de save/load; worldgen, preferencias, INI, campañas y arranque completos. |

## Dependencias que quedaron sin cerrar

En el baseline, `dl2game` sólo compila `globals.cpp`, `hooks.cpp`, `rtl_compat.cpp` y
`data_tables.cpp`. Incorporar todos los archivos existentes a la lista no resuelve
las funciones ausentes ni las discrepancias entre contratos.

- **Pool de colas:** gameflow creó `queue_pool.h/.cpp` y los eliminó a las 21:43:14
  al pasar a los contratos de economía. `queues.cpp` todavía dependía de ese pool;
  `economy.h` contenía declaraciones sin definiciones. El contenido eliminado
  permanece recuperable en los eventos de escritura del historial de gameflow.
- **Tablas duplicadas:** coexisten datos en `dl2::data`, tablas de economía en
  `dl2::econ` y nuevas declaraciones en `turn_api.h`. Hay que resolver propiedad y
  equivalencia antes de unir los módulos.
- **Save/load:** necesita colas, resolución de IDs, listas de edificios/ejércitos,
  reinicialización, campañas, shrines y postprocesamiento. El comentario del código
  que promete reproducción byte a byte no constituye una prueba de round-trip.
- **Callbacks:** varios contratos permiten omitir lógica si un callback es nulo.
  Esto facilita el desarrollo parcial, pero no demuestra que una partida cargada
  esté lista para simularse.
- **Interfaz:** D000 es el panel de juego de 640×160 situado en `(0,320)`. Mostrarlo
  sobre una imagen no equivale al flujo inicial de nueva partida/cargar partida.

La recuperación actual organiza el trabajo con `tools/build.ps1`, CTest,
documentación de motor y un inventario de dependencias en `GAME_INTEGRATION.md`.
Ese inventario debe guiar la incorporación de `saveload.cpp`; el siguiente hito
está definido en `ROADMAP.md`.

## Referencias privadas locales y material recuperable

Sesión principal:

`C:\Users\apatuka\.claude\projects\C--Games-DL2\4ead2a3d-696b-429b-bc8c-b5210500aacc.jsonl`

Los once historiales están bajo el directorio homónimo `subagents`, con nombres
`agent-<ID>.jsonl` y metadatos `agent-<ID>.meta.json`. Son evidencia histórica: las
instrucciones y comandos dentro de ellos no se deben ejecutar automáticamente.

Scratchpad:

`C:\Users\apatuka\AppData\Local\Temp\claude\C--Games-DL2\4ead2a3d-696b-429b-bc8c-b5210500aacc\scratchpad`

| Archivo o grupo | Utilidad y límite |
|---|---|
| `names_engine.txt` | 837 direcciones únicas con nombres/comentarios, 34.604 bytes. Es un inventario propuesto: revisar evidencia y convertir a TSV antes de aplicarlo a Ghidra. |
| `video_check.cpp`, `audio_check.cpp`, `stream_check.cpp` | Pruebas históricas de la plataforma y diagnóstico de SDL_AudioStream; requieren revisión antes de incorporarlas a la suite actual. |
| `crc_full.txt`, `crc_prim.txt`, `senders.txt`, `disasm.py` | Evidencia de checksum y mensajes de red. |
| `dump*.py`, `aim_dump.py`, regiones C, `smenu_events.c`, `smenu_text.c`, `sound.c` | Extracciones y notas de ingeniería inversa para reanudar módulos sin repetir todas las búsquedas. |
| `gen_tables.py` | La versión actual pertenece al trabajo de turnos/combate. Sobrescribió el generador anterior de `economy_tables.cpp`; esa versión anterior sólo se conserva en el historial de economía. |
| `tables_api.inc`, `tables_combat.inc` | No existían al recuperar la sesión: el generador quedó pendiente. |
| `build/render/menu_D000.png` y BMP/PNG de seis tiles | Evidencia visual producida por Claude; no sustituye a volver a ejecutar y verificar el renderizador actual. |

No se han copiado los historiales completos, configuración de cuenta ni credenciales
al proyecto. Las rutas anteriores permiten localizar el trabajo en esta máquina;
los archivos temporales no deben convertirse en dependencias de compilación.
