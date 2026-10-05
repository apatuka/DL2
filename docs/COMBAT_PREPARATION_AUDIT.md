# Auditoría de cruces y preparación de combate

Fecha: 2026-10-05. Auditoría independiente basada en assembly local y lectura de
las APIs propietarias. No se ejecutó el binario original. Esta nota complementa
[la secuencia de turno](COMBAT_TURN_SEQUENCE.md); no acredita una batalla ni un
turno completos.

## Corrección crítica: semillas de batalla

La versión inicial de `COMBAT_TURN_SEQUENCE.md` identificó erróneamente como
Long31 los 32 draws de `00457624`. El export nuevo confirma **Rand15**:
`00457624 → 0046c9cc("Combat") → 004ae5b0`. Se actualiza únicamente la palabra
RTL baja: `low = wrap32(low * 0x015a4e35 + 1)`; el resultado es
`(low >> 16) & 0x7fff`. La palabra alta y el RNG secundario quedan intactos.
`004ae5d8` es la primitiva Long31, distinta de la llamada aquí.

Se consumen los 32 draws en orden, aun cuando no haya combates. Cada resultado
se escribe en `Battle[i]+0`, con stride `0x86`, después de resetear los pools
y copiar el turno a `005649d0`, antes de resolver los cruces. El tag `Combat`
no altera el cálculo. El RNG privado de combate tampoco avanza en este prefijo.

Evidencia: [00457624](../re/evidence/combat-sequence-2026-10-05/00457624.txt),
[0046c9cc](../re/evidence/combat-preparation-2026-10-05/0046c9cc.txt),
[004ae5b0](../re/evidence/combat-preparation-2026-10-05/004ae5b0.txt) y
[004ae5d8](../re/evidence/combat-preparation-2026-10-05/004ae5d8.txt).
La primitiva existente es `SessionRng::apply(RngOperation::Rand15)`;
no corresponde `TaggedRange`, `Long31`, `Secondary15` ni un reseed de sesión.

## Puntuación estratégica `00401108`

El original recibe **cinco argumentos**, confirmado por accesos a
`[EBP+08..18]` y `RET 0x14`. El decompilado que declara cuatro argumentos es
incompleto. El llamador de cruces pasa Army y cuatro ceros.

Las cuatro consultas originales crean por separado un Warrior temporal mediante
`00447a68` y consultan sólo el stat necesario:

| Wrapper | Consulta | Hoja |
| --- | --- | --- |
| `00447b30` | Defensa | `00447da4` |
| `00447bc0` | Precisión | `00448118` |
| `00447b0c` | Ataque | `00447c2c` |
| `00447b9c` | Cadencia | `00448008` |

La proyección limpia `0x4c` bytes, toma tipo y propietario de Army, copia órdenes
`+24`, conserva XP signed16 hasta un máximo de 1000, pone objetivo `+3c` a cero
y obtiene suministro de `Player.foodFlags & 3`. Coincide con
`projectArmyCombatant`; no usar la creación `00451b68`, que conserva campos
anteriores del slot y no limita XP de la misma manera. Los wrappers se conocen
por su decompilado; la proyección está confirmada además en
[assembly00447a68](../re/evidence/cl02-2026-10-05/00447a68.txt).

Orden de cálculo confirmado en
[00401108](../re/evidence/combat-sequence-2026-10-05/00401108.txt):

1. `remaining = wrap32(defense - signExtend16(Army+2c))`. No limitar a cero.
2. Si flag1 es no cero, clase en `{1,6,7,11}` y tipo distinto de 23, duplicar
   `remaining` con wrap32. Si esa rama no aplica, tecnología **19** conocida
   por el propietario duplica sólo clase10. No incluir clase8 ni acumular ambas
   duplicaciones. `004fbf62 = 004fbbac + 19*0x32` es su knownMask.
3. Consultar precisión y añadir como máximo un bonus de 15, con esta prioridad:
   flag2 y dominio1/6 salvo clase10; luego flag3 y dominio3 salvo clase9; luego
   flag4 en la condición muerta que exige simultáneamente dominio2 y dominio6;
   finalmente tecnología **23** para clase10. `004fc02a` es su knownMask.
   No convertir la condición muerta en un OR ni aplicar otro tope de precisión
   después del bonus.
4. Consultar ataque, multiplicarlo por `remaining`, conservar sólo los 32 bits
   bajos, multiplicar por precisión y volver a conservar los 32 bits bajos.
   Los dos `IMUL` no producen una fórmula de 64 bits hasta la división.
5. Consultar cadencia y dividir el numerador interpretado signed32 por
   `max(cadence,1)`, truncando hacia cero. Después, para clases9/20, dividir
   nuevamente por 10, también signed. No combinar divisores ni saturar.

La puntuación puede ser negativa por daño, precisión o wrapping. El reporte
debe distinguir stats, valores intermedios y resultado; un `uint64_t` acumulado
o un clamp de valores negativos cambia quién se retira. No hay RNG en esta hoja.

## Cruces `0045727c`

La función borra `0x4600` bytes: 112 filas × 10 grupos × 16 bytes. Cada grupo
contiene cuatro palabras32: índice territorial de origen, propietario, suma de
puntuaciones y número de unidades. La fila0 es scratch del pool original, no
un territorio jugable inventado. Los documentos actuales admiten territorios
1..111; sus índices deben resolver explícitamente.

Primer pase: territorios 1..N en orden, sólo `numTiles != 0`; recorrer sus listas
extranjeras por enlaces, no ordenar IDs. El filtro
[0045723c](../re/evidence/movement-crossings-2026-10-05/0045723c.txt) evalúa
primero clase distinta de9, después misión no especial y por último
`Army.turnStart(+38) != Army.current(+3c)`. Las misiones excluidas son
1,2,3,4,5,6,15,16,19 por `00446bf0`.

Se toma el primer grupo con contador cero o clave `(turnStart.index, owner)`
coincidente. Si los diez están ocupados, se omite esa unidad, incluso su consulta
de puntuación. La suma y el incremento se hacen con wrap32. Todos los grupos
se construyen antes de cualquier retirada y no se recalculan después.

Segundo pase: bucles `A, B, grupoA, grupoB`, cada uno ascendente. La condición
se evalúa en este orden: propietarios diferentes, ausencia de pacto2 direccional
`hasAiPact(ownerA,ownerB,2)`, origenA igual a índiceB, origenB igual a índiceA y
`A.index < B.index` con comparación signed16. No existe un guard adicional de
contador positivo; los grupos vacíos no cruzan porque su origen es cero.

Se calculan `weightA = wrap32(sumA*countA)` y `weightB = wrap32(sumB*countB)`.
La comparación es signed32 `CMP/JLE`: si `weightB <= weightA`, pierde el grupo
situado en B; el empate retira el flujo A→B. En otro caso pierde el de A.
Es una comparación de productos ya truncados, no del signo de su resta.

La lista extranjera perdedora se vuelve a leer del documento vivo. Para cada
nodo se guarda `next` **antes** de mover; se comprueban propietario, puntero de
turnStart igual al territorio de retorno y filtro `0045723c`. Se llama
`moveUnit(army, turnStart, 0)` y se ignora el retorno nativo. Una denegación que
publica scratch sigue siendo una operación evaluada; el siguiente movimiento
debe continuar ese scratch. Las retiradas no actualizan el snapshot de grupos.

Después se entrega siempre evento152 (`0x98`), incluso si no se movió ninguna
unidad. El destinatario es el propietario perdedor. Los cuatro argumentos son:
nombre del territorio actual del perdedor, nombre de la raza del ganador,
nombre del territorio de retorno y cero. La llamada es al logger general
`00423690`: los extras de callback IA son **0/0** y no hay payloadEx nuevo.
El registro local conserva los payloads históricos de slots según su API; no
inventar campos perdedor/ganador/origen/destino como payload del evento.

Evidencia del orden, aritmética y stack de argumentos:
[0045727c](../re/evidence/combat-sequence-2026-10-05/0045727c.txt), especialmente
`00457354..5d`, `004574c2..ea` y `0045752f..a4`;
[00423690](../re/evidence/movement-crossings-2026-10-05/00423690.txt) confirma
los cuatro argumentos y extras0/0. El evento conserva el formato original,
incluida la errata textual `were forces to retreat!` de la tabla canónica.

## Reset e inicio de Battle

[004571d4](../re/evidence/combat-sequence-2026-10-05/004571d4.txt) limpia sólo:

| Objeto | Dirección | Tamaño | Cursor/límite tras reset |
| --- | --- | --- | --- |
| Warrior | `005649e8` | `0xf960 = 840*0x4c` | `0 / 839` |
| Edificio de batalla | `00574350` | `0x79e0 = 1200*0x1a` | `0 / 1199` |
| Battle | `0057bd38` | `0x10c0 = 32*0x86` | contador Battle `0` |

El reset no escribe el selector actual `0057cdf8`, grids, RNG privado, tick,
deadline ni contadores de atacante/defensor. Conservarlos cuando formen parte
del contexto recibido. Poner a cero los bytes de Battle también significa
defensor/atacante0; el default defensor−1 de `CombatCreationBattle` no representa
el reset binario. Los cursores iguales representan pool lleno; el pool físico
no debe confundirse con el máximo de unidades estratégicas del SAV.

[00456150](../re/evidence/combat-sequence-2026-10-05/00456150.txt) hace, en orden:

1. Tick `005649d4=0`, deadline `005649d8=-1`, contadores atacante/defensor0.
2. Selecciona `Battle[battleCount]` e incrementa el contador; el original no
   comprueba límite. La API debe rechazar el intento de usar índice32 sin
   escribir fuera del pool, preservando outputs.
3. Escribe territorio `+4`, defensor WORD `+8`, atacante WORD `+a`, byte bajo
   de param4 `+d`; limpia heads/tails `+74/+78/+7c/+80`, playerMask `+c` y
   approachMask `+84`. No hace memset del registro: seed, soportes, roads y
   restantes campos no tocados se conservan.
4. Siembra RNG privado con el seed de ese Battle mediante `00450dd0`, sin
   consumir RNG de sesión ni hacer un draw privado.
5. Elige rama usando **param4 completo de 32 bits**, no el byte almacenado.
   Param4=0 limpia ambos grids y, si territorio mar, llena flags con `0x60`.
   Param4 distinto de0 reconstruye grid de colonia mediante `0045209c`.
   Caso que distingue ambos usos: param4=256 elige colonia pero almacena0 en+d.

Por tanto reset de pools, prefijo de resolución e inicio de una batalla son
operaciones diferentes. Una API que las combine debe conservar su orden real
y sus campos intactos; no resembrar ni vaciar pools por cada Battle.

## Grid de colonia y caminos `0045209c`

Ambos grids contienen 36×36 bytes. La dirección lógica `(0,0)` de flags es
`0057cf4d`; su array físico comienza en `0057ce00` y representa coordenadas
−9..26. El índice propietario es `(y+9)*36+(x+9)`. El grid de penalización
tiene el mismo mapeo desde `0057d310`/`0057d45d`.

[004512a8](../re/evidence/combat-preparation-2026-10-05/004512a8.txt) pone ambos
arrays a cero. Después [0045209c](../re/evidence/combat-preparation-2026-10-05/0045209c.txt)
marca el exterior del cuadrado lógico0..17 con `0x70`, incluyendo las posiciones
fuera de la máscara geométrica. No limitar la escritura a `validCell`.

Procesa sitios0..35 por índice, sin usar sus coordenadas persistidas. Cada sitio
se expande a 3×3 celdas en `x=3*(site%6)`, `y=3*(site/6)`. Si su WORD de terreno
es exactamente `0x00ff`, escribe tipo6; cualquier otro patrón usa sus cuatro
bits bajos. `0xffff` produce tipo15, no tipo6. El helper
[00451340](../re/evidence/combat-preparation-2026-10-05/00451340.txt) hace OR
del nibble alto, no reemplaza el byte ni consume azar.

En modo resolución (`004cf850==0`), se copia el **byte signed de Site+0x10** a
`Battle.roads[site]`, WORD en `Battle+0x2c+site*2`. En modo replay no se copia:
se dibujan los valores WORD conservados del Battle. En particular un byte `ff`
se almacena como `ffff`; usar uint8 o normalizar a una máscara pierde evidencia.

Se agrega bit `0x04` a las siguientes posiciones relativas de cada bloque:

| Condición sobre el WORD roads | Celdas añadidas |
| --- | --- |
| distinto de0,2,4 | `(0,0)` |
| bit4 presente | `(0,1)`, `(0,2)` |
| exactamente1 | `(0,1)` |
| bit2 presente | `(1,0)`, `(2,0)` |
| exactamente8 | `(1,0)` |

Estas condiciones se ejecutan todas y en ese orden, con OR idempotente mediante
[0045130c](../re/evidence/combat-preparation-2026-10-05/0045130c.txt). No aplicar
una interpretación genérica de conectividad ni consultar edificios para corregir
los caminos recibidos. La penalización permanece cero; ni esta función ni sus
helpers consumen RNG, modifican sitios o colocan combatientes.

`00456618` es una operación anterior y diferente en el consumidor territorial:
limpia Site+18 y proyecta tipo/propietario de edificios a Site+18/+19. En ciertos
sockets lee el binding de edificio del sitio+5 (`+118`) o sitio+24 (`+4f4`),
sin comprobar límites. El futuro consumidor completo debe validar esos bindings
cuando la rama los alcance; no inferirlos por cercanía ni ejecutar esta hoja
como efecto oculto de `00456150`. Evidencia:
[00456618](../re/evidence/combat-preparation-2026-10-05/00456618.txt).

## Integración y pruebas que debe cubrir el lote

Las APIs existentes aportan `projectArmyCombatant`/`combatStat`, pactos,
`moveUnit`, log local, reacciones IA, `SessionRng` y `CombatCreationContext`.
Las nuevas hojas deben poseer sus contextos y publicar transaccionalmente
documento, scratch, RNG, registro e informe. Las referencias de Battle y pools
deben ser índices/bindings tipados, nunca direcciones del ejecutable.

Casos de prueba que distinguen las ramas auditadas:

- Scoring: cinco argumentos, bonus excluyendo clase8/tipo23, tecnologías19/23,
  prioridad de bonuses, flag4 sin efecto, daño firmado, dos productos32 y
  división hacia cero; XP fuera de rango, suministro y objetivo nulo.
- Cruces: empate, producto con signo distinto tras wrap, direccionalidad del
  pacto, diez grupos y undécimo omitido, lista frente a orden ID, snapshots
  conservados, retirada que devuelve false, evento sin ninguna unidad movida,
  payload anterior del slot y rollback si falla un evento posterior.
- Preparación: exactamente32 Rand15 aun sin batallas, high/secondary/private
  sin avance, reset selectivo con campos anteriores no cero, slots840/1200/32,
  límite agotado, Battle seed/soportes/roads conservados y param4=256.
- Grid: mar modo0 frente a colonia modo!=0, flags exteriores0x70, terreno00ff
  frente a ffff, roads1/2/4/8/combinaciones/byteff, replay WORD previo, geometría
  por índice de sitio, penalización limpia y ausencia de draws.

La validación 77/77 del lote anterior no acredita por sí sola estos consumidores
nuevos. Sus pruebas y build integrador deben registrarse por separado.

## Revisión de las implementaciones del lote

Archivos leídos: [movement_crossings.h](../src/game/movement_crossings.h),
[movement_crossings.cpp](../src/game/movement_crossings.cpp),
[combat_preparation.h](../src/game/combat_preparation.h),
[combat_preparation.cpp](../src/game/combat_preparation.cpp), integración
[runtime_state.cpp](../src/game/runtime_state.cpp) y
[prueba de State](../tests/test_movement_crossings_runtime.cpp).

No se detectó una divergencia sustantiva pendiente en las ramas auditadas:

- `scoreArmyPower` consulta sólo defensa, precisión, ataque y cadencia. Conserva
  la proyección, tecnologías19/23, flags y sus prioridades, productos32 y
  divisiones signed; no añade clamp ni consumo RNG.
- `resolveMovementCrossings` conserva grupos, orden, desempate, consulta de
  pactos y lectura de listas vivas con next previo al movimiento. Entrega152
  después del recorrido, mantiene payload sinEx y comparte log/IA/RNG/scratch.
- La primera versión detectaba ciclos mediante `(id,next,current,mission)`.
  La revisión señaló que esos campos no describen todos los datos leídos por
  movimiento: transportes, pares y otros nodos pueden cambiar entre visitas.
  El implementador lo reemplazó por `maximumTraversalSteps`, límite explícito
  de recursos con error `Limit` atómico. No se presenta ese límite como una
  regla nativa ni se rechazan revisitas basándose en un estado local incompleto.
- `State::resolveMovementCrossings` exige la continuación propietaria, usa
  copia privada, comprueba tamaños/orden de IDs antes del commit y publica
  documento/grafo/handles junto con scratch, AI/RNG, log, ciudades y campaña.
  `copyForEdit` mantiene los bloqueos por oferta humana pendiente y por etapas
  económicas terminales. Alias entre contexto de entrada e informe permanece
  válido porque se publica después de terminar su uso.
- `resetCombatPools` conserva exactamente los campos no escritos por el reset;
  cada Battle reseteado tiene defensor0. `prepareCombatPhase` hace32 Rand15 y
  conserva high/secondary/private. `beginCombatBattle` usa el parámetro32 para
  decidir la rama y almacena sólo su byte bajo, preservando seed/soportes y
  campos no tocados.
- La reconstrucción del grid conserva ubicación por índice, los nueve writes
  por sitio, `00ff` frente a `ffff`, OR de terreno/caminos, words de replay y
  byte signed de resolución. No filtra el marco exterior por máscara geométrica.
- `createPreparedCombatWarrior` proyecta el Battle seleccionado y sus pools,
  llama a la hoja existente y publica el resultado en ese mismo estado. No
  borra otros Battles ni altera su semilla/replay/clocks/structures; no simula
  los callers faltantes de edificios/milicia/minas.

Esta revisión es estática y no incluye ejecutar pruebas, Ghidra ni el original.
Los errores de dominio documentados (límites físicos, bindings ausentes,
guard de recorrido) siguen siendo rechazos explícitos de la API. Permanecen
fuera del lote selección territorial, creación de edificios/milicia/minas,
ticks, daño/bajas/consecuencias, AfterMove y el coordinador de turno.

## Revisión independiente de las pruebas

Se leyeron [test_movement_crossings.cpp](../tests/test_movement_crossings.cpp),
[test_movement_crossings_runtime.cpp](../tests/test_movement_crossings_runtime.cpp)
y [test_combat_preparation.cpp](../tests/test_combat_preparation.cpp), contrastando
sus oráculos con el assembly anterior. Esta revisión no ejecutó los tests.

Los dos casos principales de overflow de cruces son alcanzables con los campos
signed16 admitidos y distinguen el cálculo nativo de una fórmula en64 bits:
`6555 * 16388 * 100` conserva el patrón signed32 `-2142567888`, que al dividir
por5 produce `-428513577`; el producto de grupo `100200100 * 25` conserva
`-1789964796` y hace perder al grupo aparentemente más potente. No son escenarios
que dependan de escribir fuera del rango de los modificadores guardados.

La revisión detectó el uso del nombre inexistente `Army.damage`: el layout
compartido conserva `int16_t unk_2c` para Army+0x2c. El implementador corrigió
la hoja y sus pruebas sin renombrar el layout. El caso de raza inválida verifica
rechazo atómico durante scoring; no acredita un fallo tardío al formar el nombre
del ganador. La falta de log explícito sí se alcanza después de una retirada y
comprueba su rollback. La prueba de transportes conserva la lectura de `next`
anterior al movimiento y permite revisitar el portador.

Las dos mejoras de cobertura señaladas durante la revisión ya están añadidas:
`unk_2c=-1` produce defensa restante6 y puntuación120, distinguiendo extensión
signed16 de una lectura unsigned; un documento con111 territorios y dos tiles
cruza entre1 y111, verifica la fila111 del snapshot de112 filas y conserva la
fila0 vacía. Los territorios intermedios sin tiles no se convierten en celdas
de mundo artificiales. Estos casos cierran los extremos solicitados sin cambiar
la implementación.

Los oráculos de preparación coinciden con la evidencia: recurrencia Rand15
independiente con32 valores de15 bits, conservación de high/secondary/private,
anchors de instrucciones PE, reset selectivo840/1200/32 y último Battle31 frente
al rechazo de32. Los modos256, -256 e INT_MIN prueban la decisión con el parámetro
completo; los caminos prueban byte firmado, WORD de replay y footprints literales,
incluyendo valores con sólo el byte alto activo. Los tests de alias, fallo tardío
de RNG y continuidad begin/create/begin verifican publicación conjunta y pools
compartidos. No se detectó un oráculo incorrecto pendiente en preparación.

El coordinador informó build normal correcto y prueba focal
`combat_preparation` correcta en1,67s, con43 documentos reales. Ese resultado es
del build central; no acredita todavía la regresión completa de este lote ni una
comparación mediante ejecución del juego original.
