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

## Participantes y defensa de batallas — 2026-10-05

Sexta continuación sobre `27a4b44`, conservando los cambios anteriores.
`combat_territory` compone004568c8 hasta justo antes de004526b0: selección
territorial, proyección de sitios, ejércitos por ID, edificios por sitio,
milicias,24 intentos de minas, semilla posterior y reconstrucción de defensa.
El wrapper00456c10 restaura la selección exterior. Un resultado sin batalla
conserva documento y contexto; los errores revierten ambos incluso después
de escrituras o draws previos.

Las nuevas hojas `combat_buildings`, `combat_auxiliaries` y `combat_defense`
conservan ocupación antes del rechazo por capacidad, pools/slots anteriores,
la espiral y consumo de labor ante creación nula, narrowings de defensa y
sumas con wrap de byte. Las fortificaciones y auxiliares reutilizan la creación
real00451b68. No se añaden callbacks ficticios, ejecución de ticks ni resultados
de batalla inventados.

Verificación vigente:

- **84/84 normal**,97,71s; **84/84 AddressSanitizer**,82,37s. Cero fallos u
  omisiones; build ASAN instrumentado con `/fsanitize=address`.
- **46/46 comparaciones binarias exactas**,43 documentos y3 vectores RNG,
  **11.706.282 bytes**, cero distintos/ignorados y cero regresiones contra
  `results/crossings-preparation-2026-10-05/results.json`.
- Cuatro pruebas nuevas: edificios, auxiliares, defensa y preparación territorial.
  Incluyen anclas/tablas PE, oráculos geométricos y de RNG, orden de participantes,
  límites, referencias no leídas, pool lleno, alias y rollback tardío.
- Se corrigieron una declaración mixta de `auto` en el test territorial y el
  número de jugadores omitido en una fixture de defensa. Ningún guard se relajó.
  Las suites completas se ejecutaron después de esas correcciones.

Informe: [results/combat-participants-2026-10-05/results.html](../results/combat-participants-2026-10-05/results.html)
y JSON. Recibos válidos de84 aprobadas en ambos builds, con fingerprint
`8c1fd02b32429ec864ab0df394fab441738b462713dc038a71cb57c00283d2b2`.
Logs: `.recovery/combat-participants-normal-build-final.log`,
`.recovery/combat-participants-asan-build.log`,
`.recovery/combat-participants-{normal,asan}-tests.log` y
`.recovery/combat-participants-matching.log`. Los logs focales conservan el
fallo inicial de fixture y su corrección aprobada.

Se añadieron12 exports enfocados (total115) y la máscara marina225 DWORD en
`re/evidence/combat-participants-2026-10-05`. Milicia se contrasta con el prólogo
004522c0 y el cuerpo004522c6 juntos. El ejecutable original conserva SHA-256
`7da13cf4ac15c2d6004a0e2172a525b9f1d27a0cb1d73590dd1fadff5d453a58`.
REA mantiene su restricción PE32; se reutilizó Ghidra directo, sin nuevos
intentos de apertura MCP. La [auditoría de participantes](COMBAT_PARTICIPANTS_AUDIT.md)
documenta evidencia estática y revisión cruzada; no representa combates
observados en ejecución del original.

Siguiente bloque:004526b0, condición de final00451034 y ticks00457048/004570e0,
con blancos, disparos, daño, bajas y consecuencias. La preparación conserva un
contexto separado de State. Siguen pendientes el contrato de fases y AfterMove;
`EconomyPhaseApplied` permanece terminal. No se habilitaron `advanceTurn`,
activación jugable ni exportación de estados parciales.

## Cruces y preparación de batallas — 2026-10-05

Quinta continuación sobre `27a4b44`, preservando las entregas anteriores.

- `movement_crossings`:0045727c y puntuación00401108 con sus cinco argumentos
  reales. Snapshot de112 filas y diez grupos, filtros de misión/clase, pactos
  direccionales, productos signed con wrap32 y desempate original. Recorre las
  listas vivas con `next` capturado antes de mover; conserva las revisitas
  producidas por transporte y emite un evento152 por grupo incluso si los
  movimientos devuelven falso. Log local real, payload anterior sin Ex y rama
  IA con extras0/0. Un presupuesto explícito de recorrido falla atómicamente;
  no se presenta como un límite nativo.
- `State::resolveMovementCrossings`: publicación conjunta de documento, grafo,
  scratch, IA/RNG, log, ciudades y campaña, preservando handles. Rechaza
  continuaciones rebobinadas, ofertas humanas pendientes y etapas económicas
  terminales. La hoja no acredita sus predecesores de turno.
- `combat_preparation`: reset selectivo de840 Warriors,1200 estructuras y32
  Battles, prefijo de fase con32 semillas, comienzo de Battle y grid36×36.
  Conserva campos y referencias no escritos; distingue modo32 de su byte
  almacenado, mar abierto de colonia, terreno00ff de ffff y roads firmados de
  ejecución frente a WORDs de reproducción.
- `createPreparedCombatWarrior`: composición de preparación y creación real
  dentro de los mismos pools. Conserva los otros Battles, las estructuras,
  relojes y seed de replay; no inventa participantes ni resuelve combate.

Corrección de evidencia: las notas anteriores identificaban las32 semillas
como Long31. El nuevo assembly demuestra `0046c9cc→004ae5b0`, es decir,
**32 Rand15 de sesión**, conservando la palabra alta y el generador secundario.
El RNG privado se siembra desde el Battle elegido, sin draw adicional.
La implementación y sus oráculos usan la primitiva corregida.

Verificación del conjunto:

- Normal: **80/80**, cero fallos u omisiones, **87,86s**.
- AddressSanitizer: **80/80**, cero fallos u omisiones, **81,03s**, sin hallazgos.
  Compilación instrumentada con `/fsanitize=address` y `/INCREMENTAL:NO`.
- **46/46 comparaciones binarias exactas**,43 documentos y3 vectores RNG,
  **11.706.282 bytes**, cero distintos/ignorados, sin regresiones frente a
  `results/pact-combat-2026-10-05/results.json`.
- Nuevas pruebas: `movement_crossings`, `movement_crossings_runtime` y
  `combat_preparation`. Ampliados los bloqueos de oferta humana y fase económica.
  Preparación incluye43 documentos originales, anclas de instrucciones PE,
  grid/roads, límites, alias y agotamiento tardío de contadores. Cruces verifica
  overflow alcanzable, daño signed, fila111/fila0, transporte con revisitas,
  fallo posterior a movimiento y evento tras rechazo nativo.
- Corregidas coordenadas de una fixture sintética y la preparación explícita
  offline de la copia del tutorial antes de inicializar IA. El original no se
  modifica ni se relajan los guards. Compilaciones finales sin advertencias
  nuevas; `git diff --check` sin errores.

Informe: `results/crossings-preparation-2026-10-05/results.html` y JSON.
Recibos válidos de80 aprobadas en `build-verified/status-ctest.json` y
`build-save-asan/status-ctest.json`, ambos con fingerprint
`804051d34104f175d02a7b40c24c3bf3ae1908bc472fe5e68c1020c84f5e926f`.
Logs finales: `.recovery/crossings-preparation-*-build-final.log` y
`.recovery/crossings-preparation-*-tests.log`.

Se añadieron11 exports Ghidra:9 en `re/evidence/combat-preparation-2026-10-05`
y2 en `re/evidence/movement-crossings-2026-10-05`; total enfocado103.
El ejecutable original conserva SHA-256
`7da13cf4ac15c2d6004a0e2172a525b9f1d27a0cb1d73590dd1fadff5d453a58`.
REA no se reintentó tras su restricción PE32 ya confirmada.
[COMBAT_PREPARATION_AUDIT.md](COMBAT_PREPARATION_AUDIT.md) registra la revisión
independiente, fuentes y límites. Son oráculos derivados estáticos, no una
comparación de combates ejecutados en el juego original.

Siguiente bloque: selección territorial004568c8, reconstrucción de sitios
00456618 y consumidores de edificios/milicia/minas00451de4/004522c0/00452250;
después resolución004526b0, ticks, daños, bajas, consecuencias y AfterMove.
La preparación de combate aún posee un estado independiente de State; integrar
las fases exige conservar sus predecesores y continuaciones. No se habilitaron
`advanceTurn`, activación jugable ni exportación de estados parciales.

## Conciliación reanudable y creación de combatientes — 2026-10-05

Cuarta continuación sobre `27a4b44`, conservando los cambios anteriores.

- `AiPactReconciliationTransaction`: recorrido completo de00441400 con cursor
  de pareja/fase/destinatario y ofertas humanas reanudables. Conserva los valores
  anteriores a los callbacks y relee las máscaras vivas antes de intersectarlas.
  Cada entrega posee su transacción de evento; responder no duplica el log ni
  los consumos de RNG. Copias, respuestas obsoletas y fallos tardíos están probados.
- `State::beginAiPactReconciliation/answerAiPactOffer`: exclusión compartida con
  eventos individuales, continuidad de contextos y publicación conjunta de
  documento, RNG, IA, log, ciudades y campaña. Mantiene los handles y conserva
  el estado publicado durante la espera. La API directa anterior sigue rechazando
  ofertas que requieren una respuesta humana.
- `combat_creation`: creación00451b68 y sus consultas de colocación, retirada,
  estadísticas y registro. Pool propietario de840 slots, entradas Army reales
  o sintéticas explícitas, preservación de campos no escritos, clases especiales,
  suministro previo y umbral de retirada con la conversión x87 original.
  El RNG de combate es privado y distinto del RNG de sesión. Se conservan el
  fallback de colocación y la aritmética original; los errores revierten el informe.
- [COMBAT_TURN_SEQUENCE.md](COMBAT_TURN_SEQUENCE.md) registra el orden estático
  de la fase de combate y del turno, las dependencias de cruces y preparación de
  batallas y los dos caminos distintos de penalización de santuarios. La fase
  económica terminal requiere un contrato nuevo antes de poder encadenar combate.

Verificación del conjunto:

- Normal: **77/77**, cero fallos u omisiones, **91,29s**.
- AddressSanitizer: **77/77**, cero fallos u omisiones, **79,96s**, sin hallazgos.
  La compilación mantiene `/fsanitize=address` y `/INCREMENTAL:NO`.
- **46/46 comparaciones binarias exactas**,43 documentos y3 vectores RNG,
  **11.706.282 bytes**, cero distintos/ignorados; sin regresiones frente a
  `results/movement-human-2026-10-05/results.json`.
- Pruebas nuevas: `ai_pact_transaction`, `ai_pact_runtime`, `combat_creation`.
  La última contrasta2320 valores de tablas contra el PE, las constantes x87
  y el módulo del pool; usa también Army de `TUTORIAL.SAV` con un contexto de
  batalla sintético explícito. Se corrigió la geometría de un fixture antes de
  la regresión final, sin cambiar la implementación.
- Compilaciones finales sin nuevas advertencias; `git diff --check` sin errores.

Informe: `results/pact-combat-2026-10-05/results.html` y JSON. Recibos válidos en
`build-verified/status-ctest.json` y `build-save-asan/status-ctest.json`, ambos
con fingerprint `6eb44dc7e5fd0431eedeb57517cc7b5f30df4d02bc2225be84de5bf11cf1aa13`.
Logs: `.recovery/pact-combat-normal-build-final.log`,
`pact-combat-asan-build.log` y `pact-combat-*-tests.log`.

Ghidra directo añadió31 exports:22 en `re/evidence/combat-creation-2026-10-05`
y9 en `re/evidence/combat-sequence-2026-10-05`; total enfocado92.
`constants.json` conserva cinco bloques del PE con direcciones y offsets.
El SHA-256 original permanece
`7da13cf4ac15c2d6004a0e2172a525b9f1d27a0cb1d73590dd1fadff5d453a58`.
REA no se reintentó por su restricción PE32 ya confirmada. Esta evidencia y los
oráculos son estáticos; no acreditan una ejecución equivalente del combate nativo.

Próximos paquetes: cruces0045727c y puntuación00401108; reinicio/preparación de
Battle y grid004571d4/00456150/0045209c; después ticks, disparos, daño, bajas y
consecuencias, además de presentación y secuencia IA. La creación implementada
no inicializa por sí sola una batalla ni conecta sus llamadores de edificios,
milicia y minas. Siguen pendientes el turno completo, la activación jugable y el
guardado reanudable. No se habilitó `advanceTurn` ni exportación de estados parciales.

## Movimiento y respuesta humana reanudable — 2026-10-05

Tercera continuación sobre `27a4b44`, preservando las entregas anteriores.

- `movement_next_step`: selección004467e8 con distancias signed16 explícitas,
  ranking y empates originales, consultas de acceso/scouting y buffer de traza
  con capacidad y contenido previo. Conserva las escrituras intermedias y
  sobrescrituras nativas; el buffer no se presenta como una ruta completa.
- `unit_movement`: ejecución00446084, relink, embarque/desembarque, carga y
  restricciones35/36. Distancia calculada desde inicio del turno, presupuesto
  recalculado desde el máximo, misiones y referencias de ruta por separado.
  `State::moveUnit` conserva handles, reconstruye el grafo y continúa scratch.
  El rechazo nativo publica flags/distancias; los errores de API revierten todo.
  CLI `move-unit <save> <unit> <territory> <route-origin-or-0>` con resultado
  nativo separado del resultado de cada relink, sin exportar una partida parcial.
- `AiEventTransaction`: snapshots privados e inmutables, pausa en ofertas
  humanas y decisiones explícitas con identidad/checkpoint exactos. Reanuda
  callbacks y ofertas anidadas sin duplicar efectos lógicos o RNG. Categoría15
  recuperada:104 nombres contrastados directamente con el PE. Conserva el
  objetivo de campaña1 para máscaras exactas2/16 antes de los callbacks.
- `State::beginAiEvent/answerAiOffer`: bloquean otras ediciones, preparación y
  captura durante la espera; conservan documento/RNG/handles publicados hasta
  completar el evento. Campaña y penalizaciones pendientes comparten la
  continuación ya usada por demolición/economía. Las respuestas inválidas o
  fallos tardíos mantienen la misma oferta pendiente.

Verificación del conjunto:

- Normal: **74/74**, cero fallos u omisiones, **80,36s**.
- AddressSanitizer: **74/74**, cero fallos u omisiones, **71,94s**; sin hallazgos,
  con `/fsanitize=address` confirmado en la configuración.
- **46/46 comparaciones binarias exactas**,43 documentos y3 vectores RNG,
  **11.706.282 bytes**, cero distintos/ignorados y ninguna regresión frente a
  `results/cl03-cl04-reconciliation-2026-10-05/results.json`.
- Compilación final sin nuevas advertencias. Corregidos narrowings constantes
  en pruebas de rutas sin cambiar sus máscaras. `git diff --check` sin errores.

Informe: `results/movement-human-2026-10-05/results.html` y JSON. Recibos en
`build-verified/status-ctest.json` y `build-save-asan/status-ctest.json`.
Logs `.recovery/movement-human-*-build*.log`, `movement-human-*-tests.log`
y `movement-human-byte-matching.log`.

Ghidra directo añadió14 exports de ensamblado/pseudocódigo:12 en
`re/evidence/movement-execution-2026-10-05` y2 en `movement-taskforce-2026-10-05`.
El SHA-256 original permanece `7da13cf4ac15c2d6004a0e2172a525b9f1d27a0cb1d73590dd1fadff5d453a58`.
REA no se reintentó: persiste la restricción PE32 documentada. Las pruebas son
oráculos derivados de evidencia estática, no una comparación de ejecución nativa.

Pendientes: envolver la conciliación completa en la continuación humana,
presentación y secuencia IA; autoridad/controles de movimiento, descubrimiento,
conquista, creación de combatientes00451b68, combate y coordinación CX-03.
La rama nativa de transporte que libera un pasajero y después lo escribe se
rechaza atómicamente; el modo editor sigue fuera de alcance. No se habilitó
`advanceTurn`, activación jugable ni guardado de estados parciales.

## Distancias, demolición colectiva y conciliación — 2026-10-05

Segunda continuación sobre `27a4b44`, conservando los cambios anteriores.
CL-03 y CL-04 quedan integradas dentro de sus contratos; CX-02 avanza con
conciliación explícita, pero sigue pendiente la interacción humana y el turno IA.

- `movement_paths`: búsquedas00446b3c/94 y DFS00446440, dominios1..6, costes
  originales, pactos, ciudades/depósitos, transporte disponible y contexto de
  unidad en movimiento. Scratch de flags/distancias separado del documento,
  sentinel0 explícito no traversable, límites signed16 y profundidad signed32.
  CLI `movement-paths` consulta sin mover unidades. Además de fixtures, se
  ejecutaron24 consultas de dominio sobre tutorial y tres escenarios reales.
- `colony_demolition_orders`: orden confirmada0045b304 no-editor, recorrido
  vivo de36 sitios, exclusión por categoría guardada11 y devolución/balance
  por retiro. Conserva las diferencias con la demolición individual. Conectada
  a `State::orderDemolishColony` y CLI `order-demolish-colony`, con retiro de
  handles, grafo coherente, contexto continuado y rollback de la orden completa.
- `ai_pact_reconciliation`:00441400 como operación propietaria completa,
  callbacks58/73 reales, log humano con retrato/RNG y conciliación posterior
  de máscaras vivas. Orden por filas/columnas, parejas inversas y diagonales,
  inactivos, bits altos y negociación reentrante probados. No se programa aún
  desde State/turno ni se reinician máscaras implícitamente.
- Documentado el siguiente contrato de
  [respuesta humana/reanudación](AI_NEGOTIATION_CONTINUATION.md): retrato antes
  de la decisión, estados de oferta, efectos de campaña y operaciones anidadas
  pendientes. Las ofertas humanas actuales siguen rechazando toda la transacción;
  no se fabricó una aceptación/rechazo para cerrar la dependencia.

Ghidra directo produjo15 exports adicionales con ensamblado, en
`re/evidence/cl03-cl04-2026-10-05` y `cx02-human-2026-10-05`.
SHA-256 del original intacto. Se reutilizó la base local ya reconstruida;
la restricción PE32 del proveedor REA sigue documentada, sin repetir su apertura.

Verificación final:

- Normal: **70/70**, cero fallos u omisiones, **79,64s**.
- AddressSanitizer: **70/70**, cero fallos u omisiones, **71,10s**, sin hallazgos
  de memoria; compilación realmente instrumentada con `/fsanitize=address`.
- **46/46 comparaciones binarias exactas**,43 documentos originales y3 vectores
  RNG, **11.706.282 bytes**, cero distintos/ignorados. Sin regresiones del
  informe frente a `results/cx02-cl02-2026-10-05/results.json`.
- `git diff --check` sin errores de whitespace. Las dos advertencias C4310
  del test de rutas son narrowing explícito de máscaras unsigned a16bits,
  sin advertencias nuevas en la implementación. Los oráculos siguen siendo
  derivados estáticos; no acreditan ejecución equivalente de una partida nativa.

Informe: `results/cl03-cl04-reconciliation-2026-10-05/results.html` y JSON.
Recibos vigentes: `build-verified/status-ctest.json`,
`build-save-asan/status-ctest.json` y XML/logs correspondientes. Logs locales
de esta entrega: `.recovery/continuation-*-build*.log`,
`continuation-*-tests.log`, `continuation-byte-matching.log` y exports Ghidra.

Pendientes siguientes: respuesta humana CX-02, siguiente paso004467e8 y
ejecutor00446084, creación de combatientes00451b68 y coordinación CX-03.
No se habilitaron controles gráficos, guardado jugable ni `advanceTurn`.

## Continuación con REA, pactos y estadísticas — 2026-10-05

Tras la revisión del entorno se reconstruyó `ghidra_project/DL2.gpr` desde el
PE32 original, con Ghidra12.1.4/JDK25 y compilador `borlandcpp`. Se exportaron
32 funciones enfocadas con pseudocódigo y ensamblado; véase
[el registro de evidencia](../re/evidence/README.md). Se conservaron los 3.971
exports históricos y el SHA-256 del ejecutable original permanece intacto.

El MCP de REA está accesible, pero `open_binary` no admite este destino:
`capability_unavailable` / `unsupported_provider`, con
`architecture_unsupported` porque su proveedor Ghidra P0 en Windows sólo admite
PE x86-64. También detecta `GHIDRA_INSTALL_DIR` ausente y Java17; corregir esos
dos puntos no soluciona la restricción PE32. No se abrió sesión ni se obtuvo un
Evidence ID nativo de REA. `npx rea-agents doctor` falló con `spawn EINVAL`.
La alternativa Ghidra headless directa funcionó, sin alterar el proveedor.

Implementación añadida:

- CX-02: ruptura privada/pública, máscaras bilaterales, ACK offline, avisos
  semánticos y callbacks0x72/0x73. Valoración y negociación entre IA con
  cooldown, destinatario ocupado, propuestas ya procesadas y continuación
  explícita. Reentrada, signed32, transporte16bit, RNG y rollback conservados.
  Los callbacks comprueban personalidad instalada; no ejecutan punteros SAV.
- CL-02: proyección propietaria del combatiente y consultas de ataque, defensa,
  velocidad, cadencia, alcance al cuadrado y precisión. Modificadores guardados,
  experiencia, suministro, órdenes, tecnología27 y Command Corps comprobados.
- Categoría20:35 nombres originales de retratos añadidos; el contraste con
  el PE cubre ahora490 nombres. Las consecuencias de santuarios usan los
  nuevos efectos de pactos; actualizada la expectativa antigua de rechazo.

Verificación del lote final:

- Normal: **67/67 aprobadas, cero fallidas y cero omitidas**,77,21s.
- AddressSanitizer: **67/67 aprobadas, cero fallidas y cero omitidas**,69,57s,
  sin diagnósticos de memoria; recompilado con `/fsanitize=address`.
- Byte matching: **46/46 exactos**,43 documentos originales y3 vectores RNG,
  **11.706.282 bytes, cero diferentes o ignorados**.
- Revisión independiente del orden de pactos/negociación sin discrepancias
  sustantivas; oráculos estáticos derivados, no ejecución comparativa del EXE.

Recibos actuales: `build-verified/status-ctest.json`,
`build-save-asan/status-ctest.json` y respectivos XML/logs. Informe:
`results/cx02-cl02-2026-10-05/results.html` y `results.json`.
Los archivos `.recovery/cx02-*-tests.log`, `cx02-asan-build.log` y
`ghidra-cx02*.log`/`ghidra-cl02.log` conservan las ejecuciones locales.

**CX-02 sigue parcial:** faltan respuesta humana/reanudación, presentación,
reconciliación posterior de máscaras secretas y ejecución desde el turno IA.
CL-02 cierra su contrato de consultas, pero no crea Warriors ni ejecuta combate.
No se habilitaron `Active`, `advanceTurn`, guardado jugable ni controles de
partida. El tablero conserva CL-03 (rutas), CL-04 (demolición colectiva) y
CX-03 (secuencia completa) como pendientes. El dashboard de funciones sigue
acreditando sólo contratos con golden binario registrado; CTest por sí solo
no añade estas funciones a su porcentaje conservador.

## Revisión del entorno y base de continuación — 2026-10-05

Revisión sobre `27a4b44`, en `C:\Games\DL2`, solicitada antes de retomar los
pendientes. La instalación original está en `C:\GOG Games\Deadlock 2` y se usa
como entrada de sólo lectura. Su `DEADLOCK.EXE` conserva el SHA-256
`7da13cf4ac15c2d6004a0e2172a525b9f1d27a0cb1d73590dd1fadff5d453a58`.

Entorno comprobado:

- Visual Studio Community 2026, MSVC 19.51, CMake 4.2.3 y Ninja.
- SDK oficial SDL2 2.32.10 en `.recovery/sdl2/SDL2-2.32.10`, descargado de
  [la publicación oficial](https://github.com/libsdl-org/SDL/releases/tag/release-2.32.10).
  No se requiere instalar vcpkg para esta configuración.
- Python 3.12.14 en
  `C:/Users/enryq/.cache/codex-runtimes/codex-primary-runtime/dependencies/python/python.exe`;
  `pefile` 2024.8.26 en `.recovery/python-packages` mediante `PYTHONPATH`.
- Ghidra 12.1.4 en `C:/ghidra_12.1.4_PUBLIC`: arranque headless verificado con el
  JDK 25.0.2 de `C:/Program Files/JetBrains/IntelliJ IDEA 2026.1.2/jbr`.
  El Java 17 de PATH no satisface su mínimo Java 21. No se descargó otro Ghidra.

El entorno heredado de esta sesión tenía entradas duplicadas `Path`/`PATH`:
MSBuild fallaba antes de identificar el compilador. El lanzador local
`.recovery/run_local.py` normaliza las claves del entorno, importa VsDevCmd y
expone CMake, Python, SDL2 y pefile sólo a sus procesos hijos. No modifica el PATH
permanente. `.recovery/`, `build*/` y `results/` están excluidos de Git: guardar
una copia si se migra de máquina; no forman parte del código distribuido.

Correcciones realizadas durante la comprobación:

- `tools/build.ps1` localiza también CMake/Ninja dentro de Visual Studio y acepta
  `-Sdl2Dir`/`SDL2_DIR` y `-PythonExecutable`/`Python3_EXECUTABLE`.
- CMake copia la DLL compartida de SDL2 junto a `deadlock2` y `dl2tool`.
  Antes, CTest encontraba la copia de `tests/`, ocultando que el ejecutable no
  arrancaba desde otro directorio. Los smoke tests ahora parten de `src/`.
- El SDK oficial devolvía `SDL not compiled with stdio support` en
  `SDL_RWFromFP`. La captura usa callbacks de archivo de la aplicación y sigue
  creando el destino exclusivamente. `inspector_capture` comprueba BMP real de
  640×480, contenido, rechazo de sobrescritura y ruta inexistente.

Resultado final, incluyendo esas correcciones:

- `build-verified`: **64/64**, sin omisiones, **47,02 s**.
- `build-save-asan`: **64/64**, sin omisiones, **65,11 s**, sin hallazgos de
  AddressSanitizer. Flags comprobados: `/DWIN32 /D_WINDOWS /EHsc /fsanitize=address`,
  configuración RelWithDebInfo y linker `/INCREMENTAL:NO`.
- Tablas originales: **53 grupos, cero discrepancias**.
- Corpus actual: **43 documentos**, tutorial más los 42 escenarios.
  No están los tres archivos opcionales históricos `Saves/AUTOSAVE.SAV`,
  `Campaign/AUTOSAVE.CPN` y `Campaign/ChCht001.CPN`; las 46 muestras de otras
  secciones pertenecen a la máquina anterior.
- Byte matching: **46/46 casos exactos**, 43 documentos originales más tres
  vectores RNG derivados. **11.706.282 bytes comparados, cero distintos o
  ignorados**. Sin baseline independiente de la máquina anterior; no se afirma
  una comparación entre commits ni ejecución equivalente del juego original.
- Captura del tutorial inspeccionada visualmente; mapa, panel y sprite visibles.

Recibos: `build-verified/status-ctest.json`, `build-save-asan/status-ctest.json`
y sus XML/logs. Informe final:
`results/readiness-2026-10-05-final/results.html` y `results.json`.
La captura está en `results/readiness-2026-10-05/inspector.bmp`.
Los informes anteriores al sufijo `-final` son verificaciones intermedias.

Para repetir desde esta sesión, usando el lanzador local preparado:

```powershell
$python = 'C:/Users/enryq/.cache/codex-runtimes/codex-primary-runtime/dependencies/python/python.exe'
& $python -B .recovery/run_local.py python -B run-tests --build-dir build-verified --data-dir 'C:/GOG Games/Deadlock 2'
& $python -B .recovery/run_local.py python -B run-tests --build-dir build-save-asan --data-dir 'C:/GOG Games/Deadlock 2'
# Usar un destino nuevo para cada informe.
& $python -B .recovery/run_local.py python -B run-byte-matching --build-dir build-verified --data-dir 'C:/GOG Games/Deadlock 2' --require-originals --output results/next-check
```

El aislamiento de herramientas bloqueó la lectura de pefile instalado y la
escritura inicial de configuración de Ghidra; estas comprobaciones se ejecutaron
con la autorización de ejecución fuera del aislamiento. No se cambiaron los
permisos del sistema ni los archivos originales del juego.

Pendientes al terminar esa revisión (base Ghidra reconstruida en la continuación
documentada arriba): faltaba `ghidra_project/DL2.gpr`, recuperable mediante
una nueva importación para inspección interactiva/assembly. Las 3.971
funciones exportadas, símbolos y tablas están disponibles y permiten retomar
los paquetes actuales. Faltan también los tres guardados opcionales anteriores;
no impiden usar la instalación y el corpus actuales. No se reconstruyó la base
Ghidra en esa primera revisión ni se verificaron interacción gráfica manual/audio
o una partida real.

Orden de continuación confirmado: **CX-02** (ruptura de pactos y negociación),
**CL-02/CL-03** (estadísticas de combate y rutas), **CL-04** (demolición colectiva)
y **CX-03** (coordinador de movimiento/combate/economía, después activación,
guardado y UI). CL-01 y CX-01 ya están integradas. El checklist individual sigue
vigente: no se cerró ningún sistema jugable por aprobar esta revisión técnica.

## Retoma de tareas, CL-01 y cierre de guerras — 2026-10-04

El usuario suspendió la delegación: Codex retoma CL-02/03/04 y la integración,
sin esperar créditos ni documentación adicional de Claude. El tablero vigente
es [CLAUDE_TASKS.MD](CLAUDE_TASKS.MD); el mensaje para iniciar Claude queda inactivo.
Se conserva intacto su worktree y la entrega `c5374a5`, basada en `fe956f4`.
La revisión previa recompiló esa entrega desde cero:61/61,99.37s,sin omisiones.

Integración sobre `68e8588`:

- Incorporado `ai_taskforce_dissolution` y sus pruebas/informe originales.
  Lectura live de celdas en vez de IDs esperados; vaciado de `jobSlots` junto
  con los0xc4 bytes del job. Celdas retiradas admitidas como escritura inerte
  de job0: tipo0/dominio0 confirmado en PE y memset/free-list de00445800.
  Reutilización observa la unidad actual; propietario vivo ajeno sigue rechazado.
- Fuente/destino/informe transaccionales, autoenlaces, Full/AlreadyPresent,
  alias y celdas nulas con ID residual probados. El snapshot de pruebas cubre
  todos los campos propietarios, sidecar y cola runtime de Territory, incluso
  cuando el codec rechaza el documento. Corpus real exige éxito, no sólo
  rechazos deterministas:46 documentos,2 jobs referenciados disueltos.
- CX-02 conecta004033d0/00403350 con la hostilidad existente: fin de guerra,
  mensaje, recorrido live de50 jobs y después nueva guerra, preservando RNG y
  bits altos opacos. `AiReactionReport.warsEnded` informa máscaras y jobs.
  Pruebas de guerra0/registros vacíos, transferencia hacia un job posterior,
  varias guerras, cola llena, gate denegado y rollback tardío/in-place.
- Integración probada en `State::reactAiEvent`: grafo sin bindings residuales,
  handles supervivientes intactos y continuación RNG/IA conservada. Las
  consecuencias de santuarios pueden ahora cambiar de guerra realmente.
  Se sustituyó la antigua expectativa de «función no implementada» por una
  comprobación de éxito y otra de rollback por job inválido tardío.
- Evidencia adicional: assembly directo de00403350/004033d0/00445800 y bytes
  PE comprobados por las pruebas. Son oráculos derivados, no replay del juego.

**CX-02 sigue parcial.** Próximo tramo:004071b0 y los handlers offline
NetBreakPact00476970/00476a70. No basta borrar bits:004415d0 actualiza relaciones
bilaterales y emite eventos0x73 a otras IA;00441590 tiene semántica unilateral.
Faltan también negociación00407290/004073a4/00406dd8 y presentación de avisos.
No se sustituirán por callbacks vacíos ni respuestas humanas automáticas.
EST-04c y el turno completo siguen abiertos; no se habilitaron Active,
advanceTurn, captura de estados editados ni nuevos controles gráficos.

Verificación final: **62/62 aprobadas,0 fallidas,0 omitidas**, normal y
AddressSanitizer, con código de salida0. Comandos:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File tools/build.ps1 -BuildDir build-verified -Test
powershell -NoProfile -ExecutionPolicy Bypass -File tools/build.ps1 -BuildDir build-save-asan -Test
```

Tiempos CTest:121.38s normal y276.02s ASAN. La caché ASAN mantiene
`/fsanitize=address` realmente activo; sólo aparece el aviso históricoD9025
de `/W3` reemplazado por `/W4`. Sin diagnósticos del sanitizador. Logs en
`build-verified/Testing/Temporary/LastTest.log` y
`build-save-asan/Testing/Temporary/LastTest.log`.
La pasada intermedia detectó1 fallo por la expectativa antigua de santuarios;
se corrigió el caso como se explica arriba y se repitieron ambas suites completas.

## CX-01: referencias militares diferidas — continuación 2026-10-03

Continuación sobre `fe956f4`, mientras Claude desarrolla CL-01 en su worktree
separado. Codex conserva la integración del núcleo y el tablero
[CLAUDE_TASKS.MD](CLAUDE_TASKS.MD); no se han integrado cambios de esa rama.

`army_pool` representa 560 celdas físicas propietarias, lista libre nativa LIFO
y bindings de jobs independientes de los handles públicos por vida. Las bajas
ya no rechazan por dejar un ID de taskforce: conservan el ID esperado y la celda
hasta la limpieza explícita0040aebc. Reutilizar una celda cambia el ocupante
observado, pero no revive el handle de la unidad anterior. Las hojas de limpieza
por job/jugador/todos mantienen la comparación original ID16/owner firmado,
incluidas referencias nulas con ID no cero y reutilización con mismo ID/owner.

Creación, transporte, bajas, órdenes, mantenimiento y fase económica completa
conservan la continuación. Add/Remove de taskforces comparan celdas, no los IDs
esperados. Comida y detectores tipo14 recorren el pool físico tras reutilización;
se conservan prioridad de abastecimiento y scratch final del último detector.
El backend estructural sigue rechazando dependencias, incluso si sólo quedan
en un binding diferido a una celda reutilizada con ID distinto.

El codec no escribe metadatos de simulación ni limpia jobs para poder guardar.
Archivos sin sidecar siguen sujetos a referencias estrictas; bindings no
representables se rechazan al codificar, preparar o reiniciar carga. Capture y
advanceTurn siguen bloqueados para experimentos. La futura integración SaveGame
debe proyectar registros en orden físico y ejecutar sus predecesores reales.

Nueva suite `army_pool`, ampliaciones de IA/lifecycle/órdenes/economía e
inteligencia/comida: límites/reserva, bajas/reutilización, corrupción de
metadatos, alias, rollback tardío tras una baja, fabricación posterior aislada,
handles obsoletos, 15 pasos económicos y aislamiento de globales/RNG. Son
oráculos derivados del decompilado/assembly, no replay observado del original.
El pool nativo sin ninguna celda libre es un dominio de baja inseguro rechazado,
no una normalización inventada. EST-04c aún requiere programación de limpieza,
IA, combate, controles y guardado del turno; ECO-07 ya no tiene el rechazo por
referencias militares diferidas.

Verificación final de CX-01: **61/61 sin omisiones** en `build-verified`
(**113,40 s**) y **61/61 sin omisiones** con AddressSanitizer en
`build-save-asan` (**293,31 s**), sin hallazgos. Comandos:
`powershell -NoProfile -ExecutionPolicy Bypass -File tools/build.ps1 -BuildDir build-verified -Test`
y el mismo con `-BuildDir build-save-asan`. Cache ASAN comprobada con
`/fsanitize=address`; ejecución mediante el script para conservar su runtime.
Ambos directorios terminan sin recompilación pendiente (`ninja: no work to do`).
Normal sin avisos de código finales; ASAN conserva D9025 de `/W3`→`/W4`.
Se corrigió previamente un warning de narrowing en una fixture. Enlaces locales
de documentación verificados y `git diff --check` limpio. Logs en
`build-verified/Testing/Temporary/LastTest.log` y
`build-save-asan/Testing/Temporary/LastTest.log`.

## EST-04c: santuarios y órdenes de bajas — continuación 2026-10-02

Continuación sobre `5f6c8f3`, centrada en el parcial señalado por el usuario.
`entity_lifecycle` ahora permite demolición de santuarios con flags/estados vivos
de campaña y cola tipada; `entity_orders` añade las órdenes individuales confirmadas
de desbandar y demoler, con cascada SeaHab/plataforma y reconstrucción marina.
State/CLI incorporan las órdenes, los handles y la continuación antirrebobinado.
La fase económica y las órdenes de investigación rechazan flags de campaña que
contradigan el contexto de santuarios ya ligado a State.

`shrine_consequences` porta la penalización diferida0044b9e4→0044b924: siete
llamadas de eventos80/81 en orden, log/reacciones IA reales, moral firmada−20
con mínimo0 y wrap de `nukesUsed`. No drena la cola (el original tampoco), no
inventa el sentinel0 ni procesa esta hoja antes de su predecesor de combate.
Errores tardíos, ruptura de pactos/disolución IA aún ausentes o estados inseguros
revierten toda la operación. No se añadió flush al State/CLI ni guardado parcial.

Tres nuevos ejecutables de pruebas cubren campaña viva vs bytes SAV, capacidad
de cola10, aliases, refunds, flags, autoridad, cascadas y fallos tardíos;
continuidad de State/move/prepare/economía, retiro de handles, orden de eventos/RNG,
límites firmados y aislamiento de globales. CLI verifica tres nuevos comandos,
rechazo de destinos de guardado e integridad del tutorial original.
Son oráculos del decompilado/assembly, no una partida comparada en el ejecutable.

La revisión cruzada confirmó por qué EST-04c **sigue parcial**: faltan referencias
taskforce diferidas y limpieza0040aebc en los momentos originales, ramas IA
adicionales, órdenes colectivas y coordinación de combate/turno/UI. Mantenimiento
no llama detach; activarlo anticipadamente sería una alteración de reglas.
La entrada del checklist ahora desglosa esos pendientes, sin ocultarlos bajo
una marca de completado. Contratos y CLI en [ENTITY_RUNTIME.md](ENTITY_RUNTIME.md).

Verificación final: **60/60 sin omisiones** en `build-verified` (**89,52 s**) y
**60/60** en `build-save-asan` (**245,62 s**), sin hallazgos de AddressSanitizer.
Build normal sin advertencias de código; ASAN conserva sólo D9025 de `/W3`→`/W4`.
Los resultados finales incluyen la regresión de flags de campaña cruzados.
Se corrigieron antes del relanzamiento un warning de cast constante en una
prueba y una comparación de informe sin operador de igualdad; no fueron errores
de simulación ni se contaron builds fallidos como verificaciones aprobadas.
Registros: `build-*/Testing/Temporary/LastTest.log`; `git diff --check` limpio.

## Órdenes económicas locales — continuación 2026-10-02

Continuación sobre `85a29fc`. Se añadieron cuatro módulos propietarios y su
integración en State/CLI: `colony_labor_orders`, `building_orders`,
`population_orders`, `research_orders`. Ya permiten asignar/reasignar/resetear
trabajadores, activar/desactivar y bloquear tareas, trasladar población y
elegir/editar la cola tecnológica antes de ejecutar la fase económica existente.
No se añadió interfaz ni se habilitó una partida jugable.

Contratos importantes:

- Actor local humano con índice consistente, propiedad de las colonias y estado
  `Prepared`/`EntitiesEdited`. Un rechazo sin efectos no cambia la etapa; una
  orden aceptada o retorno falso con efectos conserva lo ejecutado en memoria.
- Labor comparte las hojas originales de ajuste/prioridad, respeta slots0..4,
  locks y la bandera de actividad. Activación/bloqueo incluye balance; no es el
  cierre de ventana de edificio ni una simulación de UI.
- Población conserva coste, moral, narrowing, vivienda y labor; incluye el
  fallo original por edificio fuente ausente DESPUÉS de modificar población.
  La programación de plaga neutraliza sólo el puntero nuevo y conserva un
  destino tipado en State. El pool de25 lleno falla antes de tocar Spies;
  no se afirma compatibilidad de serialización ni ejecución del evento.
- Investigación reproduce apertura/deduplicación, toggle/limpieza/poda/commit.
  `Select` es una política de comodidad explícita. Flags vivos de campaña y
  `DAT00559db0` son contexto del llamador; este último NO se reemplaza por
  currentResearch. Hojas de setter/default/autoselección implementadas aparte;
  no sustituyen planificación ministerial IA0040cea4.
- Los handles existentes sobreviven y la lista de investigación no invalida
  nodos de fabricación. El sidecar de plagas continúa entre órdenes/fase/movimientos
  de State, rechaza contexto obsoleto y se limpia en una nueva preparación.

Se añadieron cinco ejecutables de prueba y casos CLI: valores negativos/extremos,
permisos, empates, locks, prioridades distintas entre traslado explícito y
automático, falsas denegaciones con mutación, pool lleno, fallo tardío, alias y
aislamiento de globales/RNG; secuencia completa órdenes→economía y conservación
de referencias. Corpus adicional de población (cuatro partidas) e investigación
(46 documentos) de sólo lectura. Son oráculos derivados de las funciones/assembly,
no una comparación observada ejecutando el original.

ECO-01/09, CON-04 y SIS-01 avanzan en backend; conservan sus pendientes de
interfaz/turno y dominios explícitos. No se cierran EST parciales artificialmente.
Siguen movimiento, combate, turno IA, presentación/campañas/eventos y guardado
jugable. Véase [ECONOMY_LAB.md](ECONOMY_LAB.md) para API y comandos.

Verificación final: **57/57 sin omisiones** en `build-verified` (**83,43 s**) y
**57/57** en `build-save-asan` (**238,07 s**), sin hallazgos de AddressSanitizer.
Build normal sin advertencias de código; ASAN conserva sólo D9025 de `/W3`→`/W4`.
Los tests CLI confirman prioridades automáticas distintas de la ranura explícita,
rechazo de destinos SAV e igualdad SHA-256 del tutorial original. `git diff --check`
limpio. Resultados en `build-*/Testing/Temporary/LastTest.log`.

Nota de entorno: el primer CTest ASAN directo no llegó al cuerpo de la primera
prueba porque faltaba su DLL en PATH. Se detuvieron sólo esos procesos propios
y se relanzó `tools/build.ps1 -BuildDir build-save-asan -Test`, que importa el
entorno de Visual Studio. El resultado57/57 anterior corresponde al relanzamiento
completo, no a la ejecución interrumpida.

## Fase económica hasta balance final — corte anterior 2026-10-02

Continuación sobre `1f45bfd`. `economic_phase.*` conecta los quince pasos
propietarios de `0046c7d4`: el prefijo existente más crecimiento, moral,
resolución de investigación, disturbios/deserciones y EndTurnBalance. El comando
`dl2sim production-phase <save> <seed-int32>` ejecuta la secuencia en memoria.
`EconomyPhaseApplied` es terminal y NO es `Active`, turno completo ni SAV
reanudable. Mantiene handles supervivientes y una continuación real de
log/IA/RNG/logística/ciudades; cualquier error revierte incluso producción,
entidades nuevas, bajas y cambios de colas anteriores.

Nuevos módulos:

- `population_growth`:0046b074/0046b0e4/0046b1ac, límites físicos/vivienda,
  hambre/raza/fastProduction, eventos52/53, campaña y balance condicional.
  Assembly confirma `new/100-(old-100)`: se conserva, no se corrige la fórmula.
- `colony_morale`:0046bdfc/0046c1a8, diez componentes, total bruto, clamp y
  límite de mejora; hojas reales de fuerza militar/ocupación y disponibilidad
  de trabajadores compartidas con disturbios.
- `research_phase`:00484114, adquisición00483d58, selector robable0048514c,
  cola local/autoselección, prerequisitos, pactos y cambio real de actitud IA,
  excedentes a piezas8 y revelación de santuarios tech33. El cuarto requisito
  de las48 filas PE es0; ambos selectores nativos de límites devuelven10.
- `colony_unrest`:0046c49c/DoRiot, migración por distancia/pactos, población,
  daño, avisos y robo/adquisición (incluida tecnología0). No cambia propietarios
  ni crea/elimina entidades, porque esas acciones no aparecen en esta función.
- `economic_phase`: secuencia completa y aplicación final de tareas/labor/topes,
  integrada con State/CLI y la reconciliación de identidades del prefijo.

Dos límites importantes:

1. Los flags vivos de campaña `DAT0059f100` no están en el SAV. El contexto de
   fase los exige explícitos: bit10 controla crecimiento y bit4 restricciones
   de tecnología, también en adquisiciones por deserción. El CLI declara0.
   Para hojas aisladas, `ConstructionOrderContext::researchCampaignFlags`
   recibe esa máscara; no se deduce del número de campaña. Los tests de corpus
   de investigación toman explícitamente `LoadCoreReport::campaignGoalMask`.
2. Assembly0046c5dc/0046c60c y la tabla física de eventos confirman formatos
   intercambiados87/86: una deserción hacia local intentaría usar un entero como
   puntero de texto. Se rechaza la transacción completa. No se intercambian IDs
   sin una política explícita ni se declara esa rama completada. Permanecen
   además los dominios seguros de fases anteriores, como la baja con referencia
   taskforce viva.

Las pruebas nuevas cubren aritmética/narrowing, componentes de moral, RNG,
prerrequisitos y campañas on/off, progreso con Player.index distinto del slot,
eventos y cola real, daño/migración, rollback tardío, alias, aislamiento de
globales e integración de fábricas→comida/mantenimiento→crecimiento/investigación
→disturbios→balance. Incluyen cuatro partidas originales de sólo lectura para
la fase completa,48 filas tecnológicas contra PE y46 variantes de investigación
con núcleo de carga normalizado. Son oráculos derivados del ejecutable y
pruebas del port, no una comparación observada ejecutando el juego original.

Checklist: ECO-02/05/10/13 cerrados dentro del contrato económico; ECO-09/11 y
SIS-01 avanzan, manteniendo pendientes los traslados manuales, deserción local
segura, selección jugable e integración del turno/UI. EST-04c/05b/07b siguen
parciales por sus dependencias del juego completo, no por faltar el orden
económico. Siguientes áreas: órdenes/activación, movimiento, combate, turno IA,
presentación y guardado jugable.

Verificación final, después del ajuste de flags vivos de campaña: **52/52 sin
omisiones** en `build-verified` (**92,33 s**) y **52/52** en
`build-save-asan` (**228,08 s**), sin hallazgos de AddressSanitizer. Compilación
normal sin advertencias de código; ASAN conserva sólo el aviso de configuración
D9025 (`/W3` sustituido por `/W4`). `git diff --check` limpio. Logs en
`build-*/Testing/Temporary/LastTest.log`. Los cuatro comandos `production-phase`
con semilla1 publicaron15 pasos, turno sin incrementar, `complete_turn:false`
y `can_save:false`, sin escribir partidas originales.

## Producción económica conectada — corte anterior 2026-10-02

Continuación sobre `728ee94`. Se integra `economic_prefix.*` en State/CLI:
reinicios → impuestos → producción1 → necesidades → importaciones → comida →
energía → mantenimiento → producción2 → financiación de obras pendientes.
No es la fase completa: se detiene antes de crecimiento, moral, resolución de
investigación, revueltas y balance final. **No se habilitan Active, advanceTurn
ni exportación de partidas parciales.**

Implementación nueva:

- `territory_production.*` y recorrido compartido con `building_progress`:
  obras/mejoras, tareas vivas con outputs cacheados, arte/Long31 y eventos
  intercalados, fábrica→colas antes de ingresos, recursos, cultura/investigación
  acumuladas, clonación, entrenamiento y curación. Ambos pases conservan clamp
  poblacional/TrainMilitia(0); el segundo importa antes de refinar.
- `economic_logistics.*`: hojas CollectMaterial/FindSupplier, registro de
  necesidades, reinicios e importaciones por material/rondas. Proveedores y
  transferencias son datos propietarios; eventos60 se entregan realmente.
- `economic_consumption.*`: civiles y unidades en orden físico propietario,
  suministro gratuito por misión/aviación, fallback pagado, hambre y flags;
  energía con stock/porcentaje y eventos51 reales.
- `economic_upkeep.*`: mantenimiento cuadrático por clase canónica, avisos,
  fondos insuficientes y desbandado por precio/experiencia/ID, cascadas y
  devoluciones. Referencias taskforce que quedarían inválidas provocan rechazo
  atómico; no se inventa detach que no existe en ese caller original.
- `building_costs.*`: financiación parcial por ID unsigned16, escala de City
  Center guardada, flags y limpieza de paid, sin volver a cobrar dinero base.
- `EconomyPrefixApplied`: una sola continuación log/AI/RNG/ciudades/logística,
  reconciliación de identidades tras fabricación y bajas, y rollback del tramo
  completo si falla una etapa tardía. No permite repetir ni seguir editando.

CLI nuevo: `dl2sim production-prefix <save> <seed-int32>`. Contexto frío explícito
con reconstrucción de eventos guardados, no recuperación de transitorios del SAV.
Declara el siguiente paso `population_growth` y rechaza un destino de guardado.

Pruebas: oráculos de tareas/cache, orden art→obra, cola antes de ingresos,
conversión/imports, desbordamientos, consumo civil/unidades, déficit/repetición,
costes/selección/bajas y error tardío. La integración conecta fábrica→unidad→
comida→mantenimiento, pago de obras después de ambos pases y creación seguida
de desbandado dentro de una única transacción. Se conservan handles supervivientes.
El tramo completo implementado se ejecuta sobre **cuatro archivos originales**
de sólo lectura (tutorial, autosave de partida y dos campañas). Costes y
mantenimiento recorren además el corpus de **46 documentos**, con perfil de
carga explícito; el ensayo de mantenimiento dota créditos y limpia la solicitud
de baja para aislar el cobro. No se presenta como replay diferencial del EXE ni
como prueba de todos los casos de turnos reales.

Checklist: **ECO-03/04/06/08** implementados e integrados dentro del tramo;
ECO-05/07/13 y CON-03c/05c avanzan con los límites precisados. Los EST parcialmente
abiertos no se cierran de forma cosmética: faltan activación/presentación, resto
económico, combate/movimiento, IA completa y guardado jugable.

Verificación final: **47/47 pruebas sin omisiones** en `build-verified`
(**86,09 s**) y **47/47** en `build-save-asan` (**219,15 s**), sin hallazgos de
AddressSanitizer. Compilación normal sin advertencias de código; ASAN conserva
el aviso previo de configuración `/W3` sustituido por `/W4`. Logs en
`Testing/Temporary/LastTest.log` de cada build. Los primeros ensayos detectaron
expectativas/fixtures incorrectos (rendimiento task6, enlaces/adyacencia y
contexto de carga), corregidos antes de ambas suites finales completas.

## Progreso de obras y fabricación — 2026-10-02 (corte anterior)

Continuación sobre `6750c22`. Se incorporan dos módulos propietarios y sus
integraciones State/CLI, sin modificar la instalación original:

- `building_progress`: ramas 2/21 de `ProcessTerritoryProduction`, trabajo
  asignado, finalización/reparación, mejoras, reparto laboral, relocalización,
  caminos y eventos. Centros urbanos bajo victoria 0 recontabilizan ciudades y
  santuarios antes del retrato; no se inventa un SeaHab al terminar plataforma.
- `unit_manufacturing`: cinco colas, añadir/cancelar, reserva/devolución de
  colonizadores, financiación incremental, trabajo signed16, unidades reales,
  salida naval, repetición y eventos. El presupuesto de trabajo lo da el llamador.
- `construction_payment` añade la hoja incremental `004720f4` sin otra
  cotización ni cobro del precio base. Se conservan créditos canónicos frente a
  materiales signed16 al cancelar, pagos parciales, máscara de repetición
  `0xf001` y la financiación que reinicia trabajo sin actualizar el paid guardado.
- Hojas locales de producción/labor/caminos evitan consultar máximos o productores
  ajenos al edificio que avanza. Conservan aritmética y accesos raciales originales
  dentro de dominios seguros; los índices o bucles inseguros fallan con rollback.
- State conserva también los contadores de ciudades. Un cambio o reemplazo de
  nodos de cola retira sus handles posicionales incluso cuando los bytes finales
  coinciden; edificios, unidades, territorios y cabeceras de cola conservan identidad.

CLI: `progress-buildings`, `queue-unit`, `dequeue-unit` y `produce-units`, siempre
en memoria y sin destino SAV. Los comandos independientes no comparten sus
experimentos: cada uno lee de nuevo el archivo original intacto.

Cobertura nueva: obra/reparación, upgrades y cambio de huella, bloqueos y
overflow, eventos de investigación/ciudad/AI, pagos parciales e importaciones,
repetición con reemplazo idéntico, puerto/parejas/límites y rollback tardío tras
crear una unidad. Las pruebas de State encadenan pago→trabajo→entidad/eventos y
rechazan rebobinado de RNG/log/ciudades. Se conservan los round-trips de los 46
documentos; la comprobación de fabricación sobre ese corpus es lectura/no-op de
colas, no una ejecución de turnos completos. Las ramas activas usan fixtures
con oráculos derivados de decompilado/assembly, no replay diferencial del EXE.

Se cierran los subpasos **CON-03a/03b y CON-05a/05b**, no sus bloques jugables
completos. Faltan financiación/órdenes de mejora, restantes outputs y secuencia
de producción, UI y guardado intermedio; también siguen pendientes combate,
movimiento, IA completa y campaña. **No se habilitan Active, advanceTurn ni
exportación de un experimento parcial.**

Verificación final: **41/41 pruebas sin omisiones**, tanto en `build-verified`
(**82,99 s**) como en `build-save-asan` (**202,96 s**, `/fsanitize=address`), sin
hallazgos de AddressSanitizer. Antes pasó el subconjunto de siete pruebas de
producción/labor/pagos/obras/fabricación/State/CLI (**17,87 s**). Compilación normal
sin advertencias de código; ASAN conserva el aviso previo de configuración
`/W3` sustituido por `/W4`. Logs: `Testing/Temporary/LastTest.log` de cada build.

## Ampliación de los EST pendientes — 2026-10-01 (corte anterior)

Sobre `e92af09`, la continuación incorpora implementación, integración propietaria
y pruebas de las siguientes ramas reales, sin modificar la instalación original:

- Reinicio de sesión/combate/victoria con sus tres Rand15, mapa cambiado con
  Long31, paletas parciales y selección; se encadenan después de los eventos y
  antes de la resembra final de carga. Los buffers pertenecen al State.
- Inicialización/bindings IA y 24 fases RET8 verificados en el PE, diplomacia con
  respuestas/actitudes/cola de 42 slots (41 útiles), reacciones de eventos y mantenimiento de
  taskforces. Las matrices guardadas en scratchJobs no se tratan como punteros.
- Registro canónico de eventos con qsort/expulsión, payloads inactivos originales,
  textos tipados, retratos y RNG. Los avisos de CountShrines ahora llegan de
  verdad a LogEventEx o IA; antes sólo existían como avisos semánticos.
- Unidades con transporte/carga, pares cruiser/misil, límites, Delete/Disband,
  refunds y población. Edificios especiales/plataforma/SeaHab/santuarios y
  Delete/Demolish no-santuario, con handles estables tras cascadas.
- Costes y cobro con reservas, proveedor propietario, rutas/tarifas, importación,
  sustitución de metales y transferencias. StartConstruction conecta pago,
  eventos/IA, obra pendiente, urgencia laboral, caminos y puerto.
- Selección automática de sitios, incluida la rama marina aleatoria de santuario,
  y plan RNG de SaveGame. No son un permiso implícito para guardar experimentos.

La revisión contra assembly conservó rarezas que no deben «arreglarse»: tarifa 0
todavía limitada por créditos, metal caro consumido por el bucle original,
plataforma sin compañero cuando queda un solo slot, y caminos de demolición
dirigidos al territorio 0 después de borrar el registro. Denegaciones originales
de obra pueden consumir ID o parte del pago; se distinguen de errores de API,
que sí revierten todo. Ninguna ausencia de gameplay se sustituye por no-op.

`normalize-session`, `create-unit`, `delete-unit`, `disband-unit`,
`delete-building`, `demolish-building`, `start-building` y `find-site` exponen
estas rutas sin destino SAV. `headlessComplete` sólo acredita efectos de carga
sin ventanas; LoadGame original no llama RunAITurns. Presentación y turno IA
continúan siendo requisitos de juego, sin figurar falsamente como draws de carga.

Verificación final: **38/38 pruebas sin omisiones** en `build-verified`
(**78,47 s**) y `build-save-asan` (**196,07 s**, `/fsanitize=address`), sin
hallazgos de AddressSanitizer. Los logs locales están en
`Testing/Temporary/LastTest.log` de cada build. El pase previo detectó dos
expectativas incorrectas de pruebas, corregidas contra las tablas y el recorrido
original: madera en el índice 3 y último sitio legal de una huella 2×2 en 30.

Se conservaron los 46 round-trips exactos y se probaron creación/baja de unidades
sobre 46 documentos, mundo sin cambios sobre los 46 y cambio de mundo sobre el
tutorial, además de consultas de costes de 47 tipos por cada documento. Ninguna
muestra del corpus produjo avisos nuevos de santuarios; sus ramas activas se
verificaron mediante casos sintéticos, no mediante avisos observados en el corpus.

**No cierra todo EST ni habilita una partida jugable.** Siguen pendientes entrega
UI/briefing/timer, progreso/finalización/fabricación por colas, demolición de
santuarios con campaña, producción/movimiento/combate, turno IA completo y guardado
de sesión jugada. El checklist conserva esas casillas abiertas. Las pruebas son
oráculos derivados de decompilado/assembly/tablas PE y determinismo del port,
no una comparación de partidas completas ejecutadas en el original.

Contratos: [LOAD_NORMALIZATION.md](LOAD_NORMALIZATION.md),
[ENTITY_RUNTIME.md](ENTITY_RUNTIME.md), [RUNTIME_STATE.md](RUNTIME_STATE.md).

## Continuación EST-01b/02b/04c/05b/07b — 2026-10-01 (corte anterior)

Sobre `c06197a`, se incorporaron cuatro módulos propietarios y sus integraciones:

- `load_profile`: migraciones 35..37, espías/mercado ausentes y datos de reinicio
  IA/ministros. La versión 35 se representa como 36 sólo en el candidato parcial,
  conservando versión fuente y copia archival; no ejecuta decisiones IA.
- `load_intelligence`: detección, visibilidad, población conocida y caché de
  edificios/sitios. El original omite nuevos descubrimientos de contactos al
  cargar. Los slots inactivos con raza −1 usan la dirección original dentro de
  RaceStats; no se normalizan las entradas para hacer pasar el corpus.
- `load_session`/`event_portraits`: registro de eventos, páginas, retratos y
  consumo secundario en orden con snapshot previo explícito; 455 nombres
  contrastados directamente contra el PE. Timer auto/último jugador con estado
  previo y reloj explícitos. Sin activación UI ni avance automático del turno.
- `entity_creation`: inicialización terminada ordinaria, ID global, huella,
  balance laboral local y caminos de sitios; plantilla de unidad sin inserción.
  No se confunde con iniciar una construcción pagada ni fabricar/bajar unidades.

Se mantienen las transacciones, handles, aislamiento de globales, documentos
originales intactos y bloqueo de captura/turno parcial. Las proyecciones de IA,
eventos y timer pertenecen al State y se transfieren/reinician con la sesión.
El CLI añade `create-building` y `normalize-load-seeded`, ambos sin destino SAV.

Verificación final: **31/31 sin omisiones** en `build-verified` (**47,85 s**) y
`build-save-asan` (**146,42 s**, `/fsanitize=address`), sin hallazgos de memoria.
Logs locales en `Testing/Temporary/LastTest.log` de cada build. La primera
ejecución detectó la peculiaridad racial de slots inactivos; se corrigió contra
assembly y se añadieron oráculos de dirección y límites. Las pruebas CLI usan
un territorio sin edificios gestionados por ministro para el caso admitido y
comprueban que el otro dominio se rechaza explícitamente.

El corpus ahora pasa **46 normalizaciones parciales**, con **8 migraciones
antiguas explícitas**, **46 reconstrucciones de inteligencia** y **46 creaciones
soportadas** sobre copias. Los 46 originales mantienen sus round-trips exactos.
Se añadieron `load_intelligence`, `entity_creation` y `load_session`, y se
ampliaron pruebas de perfil, runtime y CLI. También se comprueban límites de
pool, NUL internos, rollback tardío tras RNG, contexto de ciudades previo,
asignación de IDs, huellas, caminos y límites de direcciones raciales.

EST-02b queda cubierto para la rama de carga. EST-01b/04c/05b/07b avanzan pero
siguen parciales: faltan IA ejecutable, mundo cambiado visual y transitorios,
órdenes pagadas/fabricación/bajas y consumidores/efectos de las futuras fases.
No se habilita una partida jugable. Las referencias numéricas provienen del
assembly/decompilado y bytes del EXE, no de ejecutar una partida del original.
Contratos y límites: [LOAD_NORMALIZATION.md](LOAD_NORMALIZATION.md) y
[ENTITY_RUNTIME.md](ENTITY_RUNTIME.md).

## Lote EST-01..08 — 2026-10-01 (corte anterior)

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
