# Recuperación de la sesión de Claude

Fecha de recuperación: 27 de septiembre de 2026, zona `America/Asuncion` (UTC−03).

Actualizaciones posteriores a la recuperación inicial: `SAVE_CODEC.md` documenta
el codec C++ independiente, con 46 roundtrips exactos; `WORLD_INSPECTOR.md` describe
la vista gráfica de partidas y escenarios. Las tablas de esta nota conservan el
estado/evidencia del primer hito; `saveload.cpp` integrado con activación de juego
sigue pendiente.

El proyecto conserva una base C++20/SDL2 que compila y permite inspeccionar recursos,
sprites y el panel SMenu D000. Ahora también carga una partida como documento de
inspección: mapa, territorios, edificios, unidades y copias sin modificación. La
lógica de partida está parcialmente escrita y todavía no está integrada. Cargar
el documento no equivale a activar el estado de juego, simular un turno ni jugar.

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
