# CX-03: secuencia de movimiento, preparación y combate

Fecha: 2026-10-05. Revisión independiente y sólo lectura de código compartido.
Fuentes: [convenciones](../docs/PORTING_CONVENTIONS.md), `re/decomp/<address>_*.c`,
exports Ghidra y consumidores propietarios actuales. Evidencia nueva:
[WinMain00470804](../re/evidence/combat-sequence-2026-10-05/00470804.txt),
[entrada00457624](../re/evidence/combat-sequence-2026-10-05/00457624.txt),
[cruces0045727c](../re/evidence/combat-sequence-2026-10-05/0045727c.txt),
[selección004568c8](../re/evidence/combat-sequence-2026-10-05/004568c8.txt),
[inicio Battle00456150](../re/evidence/combat-sequence-2026-10-05/00456150.txt),
[reset004571d4](../re/evidence/combat-sequence-2026-10-05/004571d4.txt),
[puntuación00401108](../re/evidence/combat-sequence-2026-10-05/00401108.txt) y
[enumeración00456214](../re/evidence/combat-sequence-2026-10-05/00456214.txt).
No se ejecutó DEADLOCK.EXE ni se afirma una comparación diferencial nativa.

## Conclusión de integración

La economía completa **precede al combate** en la resolución de turno. La cola
de demoliciones de santuarios se procesa inmediatamente después del combate,
pero se vacía más tarde, en AfterMove. La hoja `moveUnit` y la creación reconstruida
`00451b68` permiten construir consumidores acotados; aún no permiten resolver
una batalla o completar CX-03. `EconomyPhaseApplied` es actualmente terminal y
bloquea una continuación fiel hacia combate mediante State. La continuación
actual implementa los cruces con State y la preparación propietaria de pools,
semillas, Battle y grid, más su composición con creación de Warriors. La ampliación
`combat_territory` añade participantes de004568c8, sitios, edificios, milicia,
minas y defensa, con seed final de preparación; se detiene antes de004526b0.
No resuelve combate. Cambiar ese guard
sin agregar un contrato de fases no acredita los demás predecesores.

## Orden exterior confirmado en assembly

En WinMain `00470804`, rama de resolución sin abortar, después de RunAITurns,
autosave, reset/deriva IA `00405378` y espera/sincronización de órdenes:

| Callsite en WinMain | Función | Efecto / contrato pendiente |
| --- | --- | --- |
| `00470da6` | `0046f938` | Reconstruye orden de edificios `0046f908` y unidades `0046f89c`. |
| `00470dab` | `00441400` | Conciliación de pactos, callbacks/log antes de las fases siguientes. |
| `00470db0` | `0046f404` SeaManipulationEffects | Efectos marinos; no equivalen al movimiento individual. |
| `00470dc3` | `0047c730` | Progresión/restricciones de campaña; no saltar por ser offline. |
| `00470dd4` | `00485668(1)` | Primer pase de misiones: espionaje, sabotaje, etc. |
| `00470de3` | `0046c7d4` | Fase económica completa, incluidos crecimiento, investigación, disturbios y balance. |
| Entre economía y combate | sincronización sólo en red | WaitSync/SynchronizeGame, listas edificios/unidades; no necesaria como red en perfil offline. |
| `00470e1e` | `00457624` | Cruces/retiradas, selección y resolución territorial de batallas. |
| `00470e23` | `0044b9e4` | Aplica cada demolición pendiente mediante `0044b924`; no vacía la cola. |
| `00470e32` | `0046c780` | EndTurnBalance posterior al combate/castigos. |
| `00470e43` | `00485668(2)` | Segundo pase de misiones. |
| `00470e54` | `0046e730(0)` | AfterMove: descubrimiento, listas/conquista, reinicios, cola de santuarios y datos derivados. |
| `00470e63` | `00486e34` | Victoria/eliminación/fin, antes de incrementar turno. |
| `00470e72` y siguientes | `0046ac44` por jugador | Estadísticas finales; luego sincronización condicional. |
| `00470f45`, `00470f4a` | `004152ec`; `INC [0059f154]` | Cierre UI y recién entonces incremento del turno. |

Los calls exactos economía→combate→santuarios→balance→misiones2→AfterMove→victoria
están confirmados, no inferidos del nombre de funciones.
`0046c7d4` también acaba en `0046c780`; el balance de `00470e32` es una llamada
adicional, posterior a cambios del combate. No deduplicarla por similitud.

`0046e730(0)` es más que un reset de Army: reconstruye inteligencia, recorre
territorios/sitios y llama `004471c0`, `0046e6b8`, `004474b0`; luego hace
`memset(0059f104,0,0x50)` y pone `004d5a9c=0`, reconstruye derivados, vuelve a
balancear y puede ejecutar `004837fc` después del primer turno. Su bucle antiguo
con cabecera `local_c=territory1` y `local_8<=N` necesita assembly antes de portar
para fijar el último elemento/pool no representado; no asumir filas inventadas.

## Entrada real de combate:00457624

Confirmación `00457628..0045765f`:

1. Pone `004cf850=0`: modo resolución, no reproducción visual de batalla.
2. `004571d4` limpia pools y cursores de combate.
3. Copia el turno a `005649d0`.
4. Consume **32 Rand15 de sesión** mediante `0046c9cc("Combat")→004ae5b0`,
   escribiendo un seed por Battle de stride `0x86` en `0057bd38`.
   Es consumo real aun si después no hay batalla; no sustituir por una semilla
   compartida, por un hash, por Long31, Secondary15 ni por RNG privado de combate.
5. Ejecuta los cruces de movimientos `0045727c`.
6. Recorre territorios1..N en orden. En la lista extranjera, `00456214` elige
   repetidamente el ID unsigned16 menor que sea mayor al anterior (inicial−1),
   de modo que el orden no es el del vector ni el de la lista enlazada.
7. Detecta parejas de jugadores distintos con pacto1 que no tienen misión
   especial `00446bf0` ni clase canónica9 `00450fa8`. Envía evento35 (`0x23`)
   una sola vez por jugador y territorio: texto raza del otro/territorio y
   **extras7/8 ambos cero**, confirmado en `00457713..43` y `00457764..94`.
8. Recorre de nuevo por ID los miembros de jugadores marcados, escribe
   `Army+44=Army+38` y llama `00446084(army,turnStart,0)`; ignora el retorno.
   La escritura a +44 es un binding territorial transitorio real: en una API
   nueva debe ser tipada, no una dirección nativa ni un supuesto ID de Army.
9. Si queda lista extranjera, `00456c10` guarda la selección territorial global,
   la sustituye temporalmente y llama `004568c8`, restaurándola al salir.

No hay llamada de la cadena activa anterior a las alternativas `00456258`,
`00456508→0045640c` o `004566c4`. Esos callers de creación existen, pero aparecen
sin caller de entrada en este inventario; no incorporar su lógica de torneo o
combate de cruce al flujo activo sin nuevas xrefs.

### Cruces0045727c

Limpia `0057f254`, 112 filas ×10 grupos ×16 bytes. Recorre únicamente territorios
con `numTiles!=0`; agrupa su lista extranjera por `(turnStart.index, Army.owner)`.
`0045723c` admite sólo tipo de clase canónica distinta9, misión no especial y
turnStart distinto de current. Acumula puntuación `00401108(army,0,0,0,0)` y
contador en el primer grupo vacío/coincidente; si los diez están ocupados, no
agrega el undécimo. Los grupos son un snapshot previo a las retiradas.

Luego bucle territorial A ascendente, B ascendente, grupoA0..9, grupoB0..9:
jugadores diferentes/no pacto2, orígenes cruzados y `A.index<B.index` permiten
comparar `wrap32(sumPower*count)` con comparación signed `CMP/JLE`
(`004574c2..004574ea`). El grupo situado en B se retira si su producto es menor
o igual al situado en A; en empate pierde el flujo A→B, el que está en B.
Se conserva `next` antes de mover cada nodo seleccionado de la lista extranjera
del territorio perdedor. Llama MoveUnit a su +38 con param3=0 y, después de
recorrer todo el grupo perdedor, emite un evento152 (`0x98`) al jugador retirado
mediante logger general `00423690`,
extras IA nativos0/0. El evento no depende de que MoveUnit haya retornado1.

`00401108` no es el simple stat attack: usa defensa menos daño, ataque, accuracy
y rate-of-fire, con wrapping/división signed y modificaciones por tecnología.
Assembly nuevo demuestra **cinco argumentos** y `RET0x14`; el decomp antiguo
con cuatro argumentos y retorno undefined8 es inexacto. En estos cruces se
pasan los cuatro flags cero. La condición muerta que compara dominio2 y luego6
en `00401220..3e` se conserva, no se "corrige" para facilitar un cálculo.

## Selección y preparación territorial activa004568c8

El prefijo inspecciona la lista extranjera en orden enlazado, contabiliza siete
jugadores no excluidos por misión y elige candidatos según pacto2, clase9,
parent/cargo0, población y cabecera propia. Es selección de varios participantes,
no necesariamente sólo dos ejércitos; el segundo barrido por pares de jugadores
retiene la **última** pareja encontrada. La máscara `Territory+8a8` sirve aquí
para minas: elige el último bit0..6, no cualquier jugador al azar.

La rama activa confirmada `00456ab1..00456c00`:

1. Registra terreno mar/tierra, fija `local_20=1` **también en mar**.
2. `00456618` reconstruye presentación por sitio, incluidos sockets de edificios.
3. `00456150(territory,owner,attacker,1)` inicia Battle, siempre con modo colonia1
   en esta entrada. No sustituir el argumento4 por `terrain!=0`, que corresponde
   a otra rutina antigua `004566c4`.
4. Lista extranjera en ID unsigned16 ascendente: llamar `00451b68` para todos
   en tierra, y sólo dominio canónico distinto1 en mar.
5. Sitios0..35, no IDs ordenados: cada edificio vivo llama `00451de4`.
6. Lista propia en ID ascendente: mismo filtro de terreno y `00451b68`.
7. En tierra, si falta categoría19 de `0044d230`, `005649c8=0` y cada registro
   de edificio de Battle llama `004522c0` para milicia. Si está, guarda población
   en `005649c8`; en mar también lo pone a cero.
8. Si hay dueño de minas por máscara+8a8, `00452250(owner,territory)` intenta
   crear 24 combatientes sintéticos tipo37/38 según terreno.
9. Copia el estado RNG privado `0057e240` a `Battle+0` **después** de creación
   de participantes (`00456bed..00456bf2`), luego `00451410` y `004526b0`.
   Su papel como semilla del replay es coherente con `00456e44`, que vuelve a
   sembrar el RNG privado desde Battle+0 sin recrear las colocaciones.

### Pools, Battle y grid

`004571d4` limpia 840×`0x4c` Warriors (`005649e8`), 1200×`0x1a` registros de
edificios de combate (`00574350`) y32×`0x86` Battles (`0057bd38`). Pone cursor
Warrior0/límite839 y cursor edificios0/límite1199. El tamaño de reset es
`0xf960=840×0x4c`, límite `0x347=839` y módulo de creación `0x348=840`.
Los nombres heredados
`LoadStartupReport.combatActions/combatEffects` no prueban sus semánticas:
la lectura/stride muestran edificio de batalla y Battle respectivamente.

`00456150` reinicia tick0, deadline−1 y dos contadores vivos; elige Battle por
`005649cc`, incrementa ese índice, guarda territorio/+8defensor/+a atacante,
byte+d modo y limpia mask+c, heads/tails+74/+78/+7c/+80 y máscara direccional+84.
**No hace memset de Battle** ni reescribe su seed; los campos no tocados se
conservan hasta las hojas correspondientes. Si modo0: limpia ambos grids36×36
con `004512a8`; en mar llena el grid principal con0x60. Si modo!=0 llama
`0045209c(sites)` para construir terreno/carreteras y guardar roads en Battle.

RNG privado `00450da4`: `seed=seed*0x41c64e6d+0x3039` y `(seed>>16)%bound`,
sin máscara0x7fff. Es independiente del RNG de sesión usado para semillas y
eventos. Divisor0 es error de dominio cuando una rama lo exige, no draw inventado.
La nota anterior nombraba erróneamente Long31 para las32 semillas. El assembly
de `combat-preparation-2026-10-05/0046c9cc.txt` confirma la llamada a004ae5b0:
`low=low*0x015a4e35+1`, `(low>>16)&0x7fff`, conservando high y secondary.
Long31 corresponde a004ae5d8; son primitivas distintas.

`00451b68` está implementada en `combat_creation` con pool/estado propietario,
con grid, colocación, retirada y RNG privado explícitos. Según su auditoría,
la creación no limpia el slot y la primera consulta de defensa usa el antiguo
byte de penalización de suministro antes de escribir el nuevo; no reemplazarla
por `projectArmyCombatant`. Los fuertes conservan parent/coords hasta que su
caller los cambia. Su API final debe reutilizarse en los consumidores siguientes.

## Lo que falta para una batalla offline completa

Preparar unidades no basta. `004526b0` ejecuta combate automático real en
modo0: `00451034` detecta final, luego bucle `00457048`/`004570e0`. Un tick
construye dos listas de pendientes por contadores +34/+35, consume selección
`00456054`, movimiento táctico `004556b0` y fuego `00455c88`. Timeout750 y
cola de20 ticks tras fin son reglas activas, no tiempos de UI.

Después aplica eventos35/36..46/116/148 y textos, daño persistente +2c,
veteranía `004851ec`, bajas `DeleteUnit`, cambios de dueño/desvinculación de
taskforces, reenlaces, población/milicia, daños/retirada de edificios y limpieza
de minas. Retirada `0045539c` ya vuelve a movimiento estratégico00446084; pone
strength127, +44=0 y puede escribir sentinel táctico126 si el movimiento falla.
Esto exige una transacción que reúna documento, pools, RNGs, log, callbacks IA,
campaña, santuarios y referencias físicas retiradas, no sólo un vector de stats.

Además, `00453568` al destruir un santuario llama **inmediatamente** `0044b924`
con el atacante antes de `_DeleteBuilding`. Esa penalización no pasa por la
cola de demoliciones. La cola posterior0044b9e4 y esta hoja inmediata deben
compartir contexto y orden de log/IA/RNG, sin fusionar ni duplicar sus efectos.
La rama plataforma de53568 tiene `unaff_ESI` en decomp antiguo: requiere assembly
antes de portar, especialmente al retirar varios edificios en el mismo loop.

## Limitaciones concretas del State actual

- `copyForEdit` sólo permite Prepared/EntitiesEdited, bloquea estados con oferta
  IA pendiente y también LoadNormalized/EconomyPhaseApplied. El bloqueo pendiente
  protege la continuación y debe mantenerse durante preparación/resolución.
- `runEconomicPhase` conserva RNG/log/IA/colección/ciudades y handles, pero entra
  en EconomyPhaseApplied terminal. No hay transición autorizada a "combate listo".
- `moveUnit` es una hoja de edición y conserva scratch/IDs; no acredita paso por
  conciliación, efectos de mar, misiones1 o economía. Tampoco inicializa Battle.
- `prepare` sobre una copia del documento económico borraría los contextos y
  cambiaría las identidades. No es una solución legítima para saltar ese límite.
- No hay propiedad activa de Battle/grid/RNG privado/pools1200/840 en State.
  LoadStartup guarda bytes de reset, no un runtime de combate tipado.
- No hay consumidor State de consecuencias de santuario ni AfterMove completo,
  y sus efectos no deben dispararse al terminar economía sin el combate previo.
- `advanceTurn` y capture deben seguir rechazando el experimento. Para una futura
  integración conviene una transacción específica con etapas verificables y un
  cursor de resolución, preservando handles y continuaciones entre fases.

## Paquetes implementados en esta continuación

1. **Cruces de movimientos0045727c**: `movement_crossings` implementa
   puntuación00401108 (cinco argumentos), filtro0045723c y agrupación/productos
   signed; reutiliza moveUnit, stats y pactos.
   Contexto explícito de scratch/moving selection, log/IA/RNG; reportar grupos,
   comparaciones y resultados nativos de cada retirada. Evento152 real con
   extras0/0, sin inventar éxito de movimientos. Pruebas: diez grupos+desborde
   omitido, empates, IDs/lista orden distintos, wraps negativos, pactos
   direccionales, retorno nativo falso con aviso y rollback de callback tardío.
   No llamar a57624 ni representar esta hoja como una batalla completada.
2. **Inicialización y grid de Battle**: `combat_preparation` implementa
   `004571d4`, prefix32seed de57624,
   `00456150`, `004512a8`, `0045209c/0045130c/00451340`, con Battle/Warrior/grid
   de `combat_creation`. Separa el prefijo de fase (limpia pools y consume
   los32 Rand15) de beginBattle (lee seed del slot, conserva campos no escritos).
   No colocar edificios/milicia mediante callbacks vacíos. El consumidor completo
   posterior568c8 requerirá51de4/522c0/52250/51410 antes de entrar a526b0.
   Pruebas: modo0mar0x60 frente modo1mar, roads/sites, reset exacto, ring y slots
   viejos, independencia RNG sesión/privado, límites de32 Battle y rollback.

La integración State de cruces publica continuaciones y preserva identidades;
no ejecuta el prefijo de fase ni sus otros predecesores. La preparación mantiene
su estado propietario independiente y `createPreparedCombatWarrior` conecta la
creación real dentro de los mismos pools. Ninguno de estos pasos habilita una
partida jugable. Detalle contractual en [ENTITY_RUNTIME.md](ENTITY_RUNTIME.md)
y revisión independiente en [COMBAT_PREPARATION_AUDIT.md](COMBAT_PREPARATION_AUDIT.md).

## Assembly ya obtenido y siguientes paquetes

El inventario de callers de `00451b68` contiene `0045640c`, `00452250`,
`00456258`, `004522c6` (cuerpo real de `004522c0`), `004566c4`, `00451de4`
y `004568c8`; el de `00457624` contiene únicamente WinMain `00470804`.
Fuentes: [creación decompilada](../re/decomp/00451b68_FUN_00451b68.c) y
[entrada decompilada](../re/decomp/00457624_FUN_00457624.c). Es un inventario
estático acotado a las xrefs recuperadas; no prueba ausencia de llamadas indirectas.

Disponible en `re/evidence/combat-sequence-2026-10-05`: `00470804`, `00457624`,
`0045727c`, `004568c8`, `00456150`, `004571d4`, `00401108`, `00456214`
y la conversión x87 `004ae068`.

Añadidos `0045723c` y `00423690` en `movement-crossings-2026-10-05`;
`004512a8`, `0045209c`, `0045130c`, `00451340`, `00456618`, `00450dd0`,
`0046c9cc`, `004ae5b0` y `004ae5d8` en `combat-preparation-2026-10-05`.
La reconstrucción de sitios00456618 está implementada como API explícita y
consumida por `combat_territory`; no es un efecto implícito de beginBattle.

Implementados con evidencia en `combat-participants-2026-10-05`: `00451de4`,
`00452250`, **`004522c0` junto con el cuerpo separado en522c6**,
`0044ba18`, `0047f440`, `00451410`, `0044d230` y hojas de geometría.
El wrapper00456c10 restaura la selección exterior después de preparar;
la fase propietaria aún no está programada dentro del turno de State.

Antes de resolver/commitear batallas: `004526b0`, `00451034`, `00457048`,
`004570e0`, `00456054`, `004556b0`, `00455c88`, `0045539c`, `00453568`,
`00453350` y descendientes reales. Para cerrar orden exterior/limpieza:
`0046e730`, `004471c0`, `0046e6b8`, `004474b0`, `0046e56c` y `00486e34`.
El siguiente bloque concreto es resolver004526b0 y sus ticks/hojas reales,
apoyándose en los participantes ya preparados. Véase
[la auditoría de participantes](COMBAT_PARTICIPANTS_AUDIT.md).
