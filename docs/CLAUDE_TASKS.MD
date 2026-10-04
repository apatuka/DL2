# Plan de trabajo — tareas retomadas por Codex

Actualizado: 2026-10-04. Base de integración: `68e8588`.
Responsable técnico, implementador e integrador: Codex.
Por indicación del usuario, Codex retoma todos los paquetes pendientes. **No hay
tareas activas asignadas a Claude y no debe iniciarse otro paquete suyo.**
Se conserva el nombre de este archivo y los IDs para no romper la continuidad.
Claude entregó CL-01 en `c5374a5`; su rama/worktree se conserva sin modificaciones.

## Objetivo y situación real

Terminar el juego individual, excluyendo multijugador. El siguiente gran hito es
cargar una partida, dar órdenes, resolver un turno completo y guardar/reanudar
su resultado desde la aplicación. Ese hito tampoco sustituye el cierre posterior
de campañas, victoria/derrota y los demás requisitos del
[checklist individual](SINGLE_PLAYER_CHECKLIST.md).

Existe un inspector, un codec de partidas, estado propietario y una fase
económica verificable. **Todavía no existe un turno completo jugable**.
La base `fe956f4` tenía 60/60 pruebas. Tras integrar CX-01, la verificación del
2026-10-03 pasa **61/61 sin omisiones**, normal y AddressSanitizer.
La integración CL-01/CX-02 del 2026-10-04 pasa **62/62 sin omisiones** en ambas
configuraciones (121.38s normal,276.02s ASAN); detalle en `RECOVERY.md`.
EST-04c sigue parcial: disponer de órdenes individuales y consecuencias de
santuarios aisladas no resuelve IA, orden del turno e interfaz. CX-01 añade
referencias militares diferidas y limpieza explícita; su programación en el
turno completo sigue reservada al integrador.

La prioridad será desbloquear capacidades integrables, no aumentar el número de
funciones portadas. No reabrir la investigación general de la sesión antigua:
el código y los contratos actuales son el punto de partida.

## Reparto y tablero

| ID | Prioridad / estado | Responsable | Entrega y conexión posterior |
| --- | --- | --- | --- |
| CL-01 | P0 / INTEGRADA | Codex (entrega base de Claude) | Disolución con celdas vivas, retiradas y reutilizadas;62/62 normal y ASAN. |
| CL-02 | P1 / EN COLA | Codex | Estadísticas efectivas; base para resolución de combate, COM-01. |
| CL-03 | P1 / EN COLA | Codex | Distancias/rutas; base para el ejecutor de movimiento, MOV-02. |
| CL-04 | P2 / EN COLA | Codex | Orden colectiva de demolición; backend de EST-04c/CON-04. |
| CX-01 | P0 / INTEGRADA | Codex | Pool/referencias diferidas y limpieza explícita; 61/61 normal y ASAN. Programación de turno reservada a CX-02/03. |
| CX-02 | P0 / PARCIAL — siguiente prioridad | Codex | Cierre de guerras y disolución conectados; faltan ruptura de pactos y negociación, sin simular sus efectos. |
| CX-03 | P1 / RESERVADA | Codex | Secuencia completa de movimiento, combate, consecuencias y economía; después activación, guardado y UI. |

**Prioridad actual: finalizar CL-01/CX-02.** Después seguir con CL-02/CL-03 y sus
consumidores de combate/movimiento; CL-04 también queda a cargo de Codex.
No se requiere esperar créditos ni una nueva entrega de Claude.
«RESERVADA» identifica propiedad del trabajo, no significa que esté ejecutándose.

Codex define contratos compartidos, implementa, integra, ejecuta regresiones
y actualiza el checklist central. La entrega histórica de Claude conserva su autoría.
Una dependencia nueva se comunica con una propuesta concreta; no se amplía el
ticket ni se altera el núcleo unilateralmente.

Estados: `LISTA → EN CURSO → LISTA PARA REVISIÓN → INTEGRADA`.
Sólo Codex declara `INTEGRADA` tras la revisión y las pruebas del conjunto.
Si algo impide avanzar, registrar `BLOQUEADA`, causa, evidencia y decisión requerida.
Una hoja integrada no cierra por sí sola EST-04c, COM-01, MOV-02 ni un turno.

## Preparación y aislamiento del trabajo

Las instrucciones de delegación de esta sección y el mensaje del final son
**históricos/inactivos** desde 2026-10-04. Sólo se usarán si el usuario vuelve a
pedir colaboración de Claude. Los contratos técnicos de los paquetes siguen vigentes.

1. Leer esta ficha desde `C:\Games\DL2\docs\CLAUDE_TASKS.MD` antes de crear la rama.
   Si aún no está incluida en el commit base, seguir consultando esta copia central.
2. Leer completas [PORTING_CONVENTIONS.md](PORTING_CONVENTIONS.md), las secciones
   pertinentes de [RUNTIME_STATE.md](RUNTIME_STATE.md) y
   [ENTITY_RUNTIME.md](ENTITY_RUNTIME.md), y los contratos de las APIs reutilizadas.
   Leer los originales indicados y sus dependencias antes de implementar.
3. Revisar estado, base y worktrees sin limpiar ni guardar cambios ajenos:

   ```powershell
   git -C C:\Games\DL2 status --short
   git -C C:\Games\DL2 log -1 --oneline
   git -C C:\Games\DL2 worktree list
   ```

4. Trabajar en una rama y carpeta propias. Ejemplo para CL-01, sólo si no existen:

   ```powershell
   git -C C:\Games\DL2 worktree add -b claude/cl-01 C:\Games\DL2-claude-cl-01 HEAD
   Set-Location C:\Games\DL2-claude-cl-01
   git rev-parse HEAD
   ```

   Registrar el commit real de partida. Si difiere de `fe956f4`, revisar los cambios
   relacionados antes de aplicar el contrato; no retroceder la rama principal.
   Una carpeta/rama existente se inspecciona, nunca se sobrescribe o reutiliza a ciegas.
   Si no es posible aislar el trabajo, comunicarlo antes de editar archivos compartidos.
5. Dentro de su worktree, Claude puede añadir los archivos de su ticket y su
   informe `docs/claude_reports/CL-XX.md`. También puede hacer **sólo el registro
   mínimo** del módulo/target/test en `src/game/CMakeLists.txt` y `tests/CMakeLists.txt`,
   siguiendo el patrón existente, incluida la disponibilidad de DLLs de las pruebas.
   Codex conciliará estos registros al integrar. No reformatear esos archivos.

Reservados a Codex: `runtime_state.*`, representación/validación del documento y
grafo, layouts de `game_state.h`, `globals.*`, `ai_session.*`, `entity_lifecycle.*`,
CLI, UI, secuenciador del turno y documentación central. Las APIs de esos módulos
se pueden **usar**, no modificar sin coordinación. Tampoco tocar otros módulos
para refactorizar, optimizar o resolver avisos ajenos al ticket.

No cambiar la rama del directorio principal, hacer `reset --hard`, `checkout --`,
`clean`, borrar worktrees ni incluir cambios ajenos. Los commits locales de Claude
deben contener sólo su entrega; no hacer push, merge ni integración en `main`.
Los datos de `C:\GOG Games\Deadlock 2` son entradas de sólo lectura.

## CL-01 — Disolución propietaria de taskforces vivos

**Objetivo:** portar la operación completa `0040beb4` y enlaces `0040b000` /
`0040afa4`, sobre grupos cuyas referencias a unidades vivas estén resueltas.
Desbloquea una dependencia de hostilidad; no implementa toda la reacción de IA.

Archivos exclusivos: `src/game/ai_taskforce_dissolution.h`,
`src/game/ai_taskforce_dissolution.cpp`, `tests/test_ai_taskforce_dissolution.cpp`.
Nombre CTest: `ai_taskforce_dissolution`.

Leer `re/decomp/0040beb4_FUN_0040beb4.c`,
`0040b000_FUN_0040b000.c` y `0040afa4_FUN_0040afa4.c` en la misma carpeta;
`ai_session.h/.cpp`, `game_state.h` y las tablas canónicas de unidades.
Reutilizar `addArmyToTaskForce` / `removeArmyFromTaskForce` públicos.

Contrato propuesto: fuente `const save::Document&`, jugador físico, índice de
job **0-based**, destino, informe y error. El informe identifica liberaciones,
transferencias y cambios de enlaces en su orden real. Éxito publica la candidata;
error de dominio conserva fuente, destino e informe, también si fuente y destino
son el mismo objeto. No retener referencias C++ entre llamadas que reemplacen la candidata.

Criterios de aceptación:

- [x] Recorrer las 16 ranuras en orden; sin padre liberar las unidades. Con padre,
  sólo el dominio **canónico** de unidad `1` se transfiere, no la clase guardada.
- [x] Conservar la rama de padre lleno: retirar de origen no garantiza incorporación
  al padre. Informar el resultado real, sin inventar una transferencia exitosa.
- [x] Reparentar los 15 enlaces de hijos al job base del propietario. Conservar
  que `0040b000` escribe el padre del hijo incluso si la lista del nuevo padre está llena.
- [x] Eliminar todas las coincidencias del job en la lista del padre y poner a
  cero los `0xc4` bytes del job disuelto, sin restaurar artificialmente `owner`.
- [x] Pruebas de padre ausente/lleno, tierra/mar/aire, cargo tipo 12, enlaces
  repetidos, hijos y lista de hijos llena, orden de efectos y bytes ajenos intactos.
- [x] Índices/propietarios/referencias fuera del dominio: error explícito y rollback
  incluso tardío; alias, error previo y aislamiento de globales/RNG cubiertos.

Fuera del alcance **original de la entrega de Claude**: referencias a unidades ya retiradas, limpieza `0040aebc`,
`00403350/004033d0`, guerra/pactos/mensajes, `AiSession`, turnos y runtime/CLI.
No interpretar `Job.armies` histórico como punteros. Las referencias diferidas
necesitan CX-01; **no** sustituirlas por desvinculación temprana o borrado de IDs inválidos.

Integración completada2026-10-04: se admiten celdas retiradas/reutilizadas y
bindings nulos con ID residual; el job y su fila `jobSlots` se vacían juntos.
Se mantiene rechazo explícito de ocupantes vivos de propietario ajeno.

Nota histórica de integración CX-01: Codex añade `Document.armyPool` y compara bindings por
celda física en Add/Remove. La rama CL-01 parte de la base acordada y no necesita
editar ese núcleo. Antes de integrar, Codex adaptará la lectura de miembros y el
vaciado del job para conservar/sincronizar `jobSlots`; probará además celdas
retiradas/reutilizadas o rechazará explícitamente ese dominio. No asumir que un
ID esperado siempre identifica al ocupante actual de un slot.

## CL-02 — Estadísticas efectivas de combate

**Objetivo:** proyección propietaria del combatiente y consultas puras de ataque,
defensa, velocidad, cadencia, alcance y precisión. Sin ejecutar un combate.

Archivos exclusivos: `src/game/combat_stats.h`, `src/game/combat_stats.cpp`,
`tests/test_combat_stats.cpp`. Nombre CTest: `combat_stats`.

Fuentes en `re/decomp/`: `00447a68` (proyección), `00447a40` (experiencia),
`00447c2c`, `00447da4`, `00447f44`, `00448008`, `004480a8`, `00448118`,
y hojas `00447f1c`, `004481a4`, `00448210`, `00448284`, `004482cc`.
Leer `economy.h`, `data_tables.*`, `supplemental_tables.*` y el ataque privado
de `colony_morale.cpp` como contraste; no modificar este último en el ticket.

Contrato: documento const y combatiente/contexto explícitos, resultado tipado y
error transaccional. Las relaciones entre combatientes son referencias propias,
no conversiones a puntero de `Warrior+0x3c`. Confirmar campos por dirección:
`00447f44` calcula velocidad pese a nombres heredados que sugieren alcance.

Criterios de aceptación:

- [ ] Separar proyección de Army y consultas; conservar el límite superior de
  experiencia 1000, órdenes y desabastecimiento según cada original.
- [ ] Cubrir tipos/races canónicos y modificadores guardados; LaserSquad con ataque
  base 2 y modificador racial 0/+1/-1 produce 2/3/1 antes de otros efectos.
- [ ] Verificar duplicación racial antes del ajuste y desabastecimiento después;
  experiencia 99/100/400/401, negativa y superior a 1000.
- [ ] Cubrir tecnología 27, CommandCorps y exclusiones específicas misil/fortaleza/milicia.
  No aplicar un multiplicador genérico a estadísticas con reglas diferentes.
- [ ] Preservar divisiones intermedias, mínimos, shifts firmados y overflow definido;
  clase canónica frente a guardada y propietarios actual/original explícitos.
- [ ] Errores sin publicar resultados parciales; entradas, globales y RNG intactos.
  Identificar los oráculos calculados desde decompilado, no atribuirlos a una
  ejecución del juego original que no se haya realizado.

Fuera de alcance: daño, elección de blancos, disparos, bajas, animación y turnos.
Codex integrará las consultas con sus consumidores; no cerrar todo COM-01 por esta hoja.

## CL-03 — Distancias y búsqueda de movimiento

**Objetivo:** búsquedas desde origen o hacia destino, con distancias firmadas y
marcas de búsqueda explícitas. No mover unidades ni cambiar propietarios.

Archivos exclusivos: `src/game/movement_paths.h`, `src/game/movement_paths.cpp`,
`tests/test_movement_paths.cpp`. Nombre CTest: `movement_paths`.

Fuentes en `re/decomp/`: `00446b08`, `00446b3c`, `00446b94`, `00446440`,
`0045dfb0`, pactos `004412d4`, edificios terminados `0044d1e4` y acceso/embarque
`00445b94`. Reutilizar `canCreateArmy` y `ArmyCreationContext`; leer
`entity_lifecycle.*`, `army_state.h` y tablas canónicas.

Contrato: consulta const con contexto de `movingArmyId`, distancias y scratch en
el resultado, sin ocultar mutaciones del documento. Los recorridos especializados
de inteligencia/deserción no reemplazan todos los dominios de movimiento.

Criterios de aceptación:

- [ ] Portar todas las ramas de dominio de la búsqueda original, incluida la 4;
  costes 1/2/5/100, tratamiento del origen y reducción por depósito de combustible.
- [ ] Pactos 1/2/0x10, ciudades terminadas, territorios excluidos y dominio 5 con
  barco disponible/no disponible, capacidad y unidad que se está moviendo.
- [ ] Rango 0 sólo reinicia; frontera exacta de rango, mejora estricta de distancia
  y recorrido por bits en orden ascendente. No sustituir por A* con desempates distintos.
- [ ] Ciclos, desconectados, adyacencias inválidas y límites de distancias firmadas;
  errores seguros sin aproximar una referencia inválida a territorio 0.
- [ ] Fixtures sintéticos y consultas sobre muestras reales; informe transaccional,
  fuente/globales/RNG intactos y resultados reproducibles.

Fuera de alcance: siguiente paso `004467e8`, ejecutor `_MoveUnit00446084`, conquista,
descubrimiento, transporte ejecutado, combate y turnos. Codex programará su integración;
la búsqueda por sí sola no cierra MOV-02 ni permite una orden de movimiento jugable.

## CL-04 — Orden confirmada «demoler todo»

**Objetivo:** rama colectiva no-editor de `0045b304`, sin diálogos.

Archivos exclusivos: `src/game/colony_demolition_orders.h`,
`src/game/colony_demolition_orders.cpp`, `tests/test_colony_demolition_orders.cpp`.
Nombre CTest: `colony_demolition_orders`.

Leer `re/decomp/0045b304_FUN_0045b304.c`, `entity_orders.*` y
`entity_lifecycle.*`. Reutilizar **`removeBuilding(..., context, ...)`**, no la
orden individual: las ramas colectiva e individual tienen semánticas diferentes.
Contrato: actor/territorio explícitos, `BuildingRemovalContext`, documento destino
e informe con retiros/devoluciones ordenados y `contextAfter`.

Criterios de aceptación:

- [ ] Recorrer los 36 sitios vivos en orden ascendente, no el orden del vector.
  Omitir categoría **guardada** 11, incluso si discrepa del tipo canónico.
- [ ] Devolución al propietario territorial y balance tras cada demolición.
  No añadir redirección SeaHab, cascada de plataforma ni reconstrucción marina:
  esta rama original no las llama.
- [ ] Separar visibilidad 4 nativa de política defensiva local: actor humano/local,
  índice coherente y propiedad local, conforme a las órdenes existentes.
- [ ] Casos mixtos, plataformas/sockets, santuarios omitidos, costes pagados/canónicos,
  orden de sitios y contexto; cero edificios elegibles produce cero retiros explícitos.
- [ ] Fallo tardío revierte la orden entera; alias, informe y contexto transaccionales,
  sin tocar globales/RNG ni aplicar consecuencias diferidas de santuarios.

Fuera de alcance: editor, multiselección de unidades, State/CLI/UI, turno y captura SAV.

## Pruebas y definición de entrega

Antes de programar, anotar en el informe la API propuesta y el dominio admitido.
Se puede proceder sin otra aprobación si respeta este contrato y no modifica
interfaces compartidas; una discrepancia semántica relevante se devuelve a Codex.

Cada entrega debe implementar su alcance completo, sin stubs ni callbacks vacíos
que simulen éxito. Respetar layouts, orden de evaluación, narrowing y RNG original;
documentar rechazos seguros. Nada de SDL/Win32 dentro de `src/game`, punteros de
archivo ejecutables ni acceso al estado global desde la API propietaria.
No habilitar `Active`, `advanceTurn` ni guardado de fases incompletas.
Las comprobaciones deben funcionar en Release: no basarlas sólo en `assert`.

Ejemplo de validación para CL-01, **desde su worktree**:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File tools/build.ps1 -BuildDir build-claude-cl01
ctest --test-dir build-claude-cl01 --output-on-failure --no-tests=error -R "^ai_taskforce_dissolution$"
git diff --check
git status --short
```

Registrar salidas/códigos y parar si falla la compilación; no probar binarios viejos.
Cambiar sufijo y regex para cada ticket. Ejecutar también las pruebas existentes
afectadas por las APIs reutilizadas. Un único build por caché; no usar
`build-verified` ni `build-save-asan` del directorio principal.
Codex repetirá la suite completa normal y ASAN al integrar. ASAN exige compilación
realmente instrumentada, no sólo un nombre de carpeta, y pruebas mediante
`tools/build.ps1 -Test` para disponer del runtime en PATH.

Informe obligatorio `docs/claude_reports/CL-XX.md`:

- Ticket, estado, commit base real, rama/worktree y archivos cambiados.
- API final, direcciones originales consultadas y decisiones de representación.
- Criterios cubiertos, dominios rechazados y dependencias aún no implementadas.
- Comandos ejecutados, conteos aprobados/fallidos/omitidos, códigos de salida y logs.
  Marcar como **no ejecutada** cualquier validación que no se haya realizado.
- Instrucciones de integración y consumidores pendientes; sin declarar jugable el juego.

Entregar ese informe junto con el commit local de código/pruebas, y comunicar
el hash en el mensaje de entrega. No vaciar contextos/colas para hacer pasar tests,
corregir datos silenciosamente ni ocultar fallos. Un bloqueo debe incluir función,
caso reproducible y propuesta mínima. No hace falta volcar historiales privados de sesiones.

Codex revisará semántica, diff y pruebas; integrará o devolverá correcciones;
después actualizará este tablero y el checklist. La coordinación entre sesiones
se hace mediante el informe y su ubicación: este archivo no arranca Claude ni
envía tareas automáticamente. No iniciar el siguiente ticket sin asignación.

## Mensaje histórico para iniciar Claude — NO usar mientras la delegación esté suspendida

```text
Lee C:\Games\DL2\docs\CLAUDE_TASKS.MD y las convenciones indicadas.
Implementa únicamente CL-01, incluida su suite, en una rama/worktree propios.
Respeta los archivos reservados a Codex; no cambies main ni implementes otras tareas.
Sigue el contrato de la ficha y consulta si necesitas ampliar una interfaz compartida.
Entrega código, pruebas realmente ejecutadas y docs/claude_reports/CL-01.md.
Indica la ruta del worktree y el hash del commit local para que Codex pueda revisarlo.
No publiques ni integres tu rama y no declares cerrado EST-04c.
```
