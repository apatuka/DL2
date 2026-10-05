# Preparación territorial de participantes

Fecha: 2026-10-05. Evidencia estática de `DEADLOCK.EXE`, exportada con Ghidra,
y composición de las APIs propietarias del proyecto. No se ejecutó el original
para obtener estos resultados. El build y la regresión del lote los registra
el coordinador central por separado.

## Frontera implementada

[combat_territory](../src/game/combat_territory.h) porta
[`004568c8`](../re/evidence/combat-sequence-2026-10-05/004568c8.txt) **hasta justo
antes de la llamada `004526b0` en `00456c00`**. Incluye la selección, proyección
de sitios, creación real de participantes, captura de semilla y penalizaciones
defensivas. No ejecuta resolución, ticks, disparos, daño, bajas, efectos sobre
población, retirada posterior ni consecuencias estratégicas. No constituye una
batalla terminada ni permite continuar o capturar un turno completo.

El contexto posee `CombatPreparationState` e `int32_t militiaPopulation`,
equivalente explícito de `005649c8`. Las escrituras de sitios pertenecen al
`save::Document`; se publican junto con pools, Battle, grid, RNG privado, scalar
de población e informe. Cualquier error de API conserva todos los outputs,
incluyendo cuando documento y contexto de entrada son partes del resultado.

La rama nativa sin batalla es un éxito de API: conserva íntegramente el
documento, el contexto y los pools, incluso referencias previas que esa rama
no desreferencia. No limpia la población diferida ni ejecuta preparadores vacíos.

`prepareTerritoryCombat` conserva la selección territorial recibida; las hojas
que la necesitan la leen explícitamente. `prepareSelectedTerritoryCombat` porta
el wrapper [`00456c10`](../re/evidence/combat-participants-2026-10-05/00456c10.txt):
selecciona temporalmente el territorio solicitado y restaura exactamente la
selección anterior antes de publicar. La selección anterior puede estar ausente
o no representada si no se consulta después de restaurarla.

## Selección y condiciones

La primera pasada recorre la lista extranjera en orden de enlaces. Omite dueños
iguales al territorial y misiones especiales `1,2,3,4,5,6,15,16,19`. Cuenta por
propietario **antes** de consultar pacto2 direccional extranjero→territorial.
Los conteos no implican que todas esas unidades sean atacantes enemigos.

Una unidad canónica de clase9 sin enlace `Army+48` fija el último propietario
de warhead. El resto fija el último atacante principal y pone `airOnly=false`
si su dominio no es3. El atacante principal tiene prioridad; sólo si falta se
usa el warhead. Si faltan ambos, la función retorna sin preparar.

El oponente se determina con esta prioridad:

1. Propietario del primer nodo de la lista propia, si no hay pacto2 desde el
   atacante. Esta prueba no filtra la misión del nodo.
2. Dueño territorial, si `Territory.population` WORD es distinto de0 y no hay
   pacto2 desde el atacante.
3. Último par hostil de propietarios con conteos no cero, recorriendo ambos
   índices `0..6` de forma ascendente. El lazo continúa tras encontrar pares.

Este oponente es una condición de selección. **El defensor escrito en Battle
es siempre el dueño territorial**, no el oponente seleccionado. Battle.attacker
recibe el atacante final, que puede haber sido reemplazado por el último par.

`Territory+8a8`, cuyo nombre heredado es `exploredMask`, es la máscara de minas
en este consumidor. Se conserva el último bit activo entre0 y6; bits superiores
no eligen propietario. Las minas se consideran hostiles cuando existe una unidad
extranjera no especial de otro dueño sin pacto2 desde propietario de minas hacia
ese dueño. Se prepara si hay oponente, warhead o la combinación de atacante no
exclusivamente aéreo y minas hostiles.

La revisión independiente de esta selección y su dirección de pactos no detectó
divergencias con el assembly. No se añadió hostilidad simétrica ni orden por ID
a la pasada que escoge al último atacante.

## Orden de composición y RNG

Una selección positiva ejecuta:

1. `00456618`, proyección de tipo/raza en36 sitios.
2. `00456150(territory, territory.owner, attacker, 1)`. El modo es siempre1,
   incluso en mar, y por tanto reconstruye el grid de colonia.
3. Unidades extranjeras por ID unsigned16 ascendente, mediante `00456214` y la
   creación real `00451b68`. En mar omite dominio1; en tierra no filtra dominio.
4. Edificios presentes, sitios0..35 ascendentes, mediante `addCombatBuilding`
   (`00451de4`). No filtra por actividad/construcción antes de llamar la hoja.
5. Unidades propias por ID ascendente, con el mismo filtro marítimo.
6. Tierra: buscar categoría guardada19 terminada y activa. Si existe, copiar
   población signed16 a `005649c8`; si falta, poner0 y recorrer la lista de
   estructuras de Battle mediante `createCombatMilitia` (`004522c0`). Mar pone0.
7. Si hay propietario de minas, llamar `createCombatMines` (`00452250`), que
   efectúa24 intentos reales, incluidos los retornos nativos nulos.
8. Guardar el estado **posterior** de RNG privado `0057e240` en `Battle.seed`.
9. `rebuildCombatDefense` (`00451410`), sin consumir azar.
10. Terminar antes de `004526b0`.

Los resultados nativos `MissionExcluded`, `DefenderWarhead` y pools llenos no
son errores de API. Se conservan los efectos de sus callers, por ejemplo las
huellas de edificios marcadas antes de comprobar capacidad. La milicia no
descuenta trabajadores del documento. No se confunde su contador local de labor
con la población diferida `005649c8`.

Los draws se concatenan en orden, con rangos por llamada y diagnósticos ligeros;
no se duplican pools completos dentro de cada intento. El RNG privado sigue
`seed = wrap32(seed*1103515245 + 12345)` y usa los16 bits altos para el módulo.
Es diferente de los32 Rand15 de semillas previas de `prepareCombatPhase`.
Esta preparación no avanza el RNG de sesión ni los generadores globales.

## Hojas territoriales y límites

[`00456214`](../re/evidence/combat-sequence-2026-10-05/00456214.txt) busca el
menor ID unsigned16 estrictamente mayor que el umbral signed32 recibido,
releyendo la lista. No devuelve directamente el siguiente enlace ni enumera el
pool completo. Un head nulo produce resultado nulo. IDs, listas y ciclos deben
estar representados; no se convierten palabras históricas en punteros.

[`0044d230`](../re/evidence/combat-participants-2026-10-05/0044d230.txt) compara
la categoría **guardada signed8**, no la tabla canónica. Exige turnsLeft WORD0
y `flags & 0x04`. El sitio inicial es inclusivo; desde36 devuelve−1. Un inicio
negativo se rechaza porque el acceso previo al array nativo carece de backing
propietario, sin corregirlo a0.

[`00456618`](../re/evidence/combat-preparation-2026-10-05/00456618.txt) limpia
sólo `Site+18` (tipo). Conserva `Site+19` (raza) salvo cuando copia un edificio:

- Binding directo: copia tipo/raza únicamente si el tamaño canónico es1.
- Sitio vacío con terreno high nibble4000 y bit0100 ausente: copia el edificio
  del sitio exactamente5 posiciones después.
- Sitio vacío con high nibble6000: copia el edificio exactamente24 después.

No se usan coordenadas persistidas para resolver sockets. Un socket cuyo origen
salga de los36 sitios o tenga binding nulo/no representado causa error atómico
cuando se alcanza esa rama. No se infiere un edificio vecino ni se inventa una
raza vacía. El informe registra los36 cambios y su binding fuente cuando existe.

## Pruebas y revisión

Además de la composición, se implementaron y revisaron estas hojas:

- `combat_buildings`:00451de4, huellas00451360/004513b8 y sprite0047f440.
  La huella se marca antes de comprobar capacidad; la rama de estructuras
  llenas no consulta Battle. Las fortificaciones usan una Army sintética y la
  creación real; luego sustituyen parent y las tres parejas de coordenadas.
  El sprite divide antes de leer flags. La defensa sin labor extiende HP sin
  signo; con labor lo lee firmado, divide y conserva sólo el byte bajo.
  La máscara marina tiene225 DWORD y57 celdas, extraídos del PE con hash.
- `combat_auxiliaries`:00452250,004522c0+004522c6 y labor0044ba18. La milicia
  suma cinco DWORD con wrap32, recorre la espiral y descuenta labor aun ante
  creación nula. Su última pata comprueba sólo x<18; los accesos sin backing
  36×36 se rechazan atómicamente, sin corregir la geometría. Las minas hacen24
  intentos. Un oráculo literal comprueba coordenadas,152 draws y seed`da2f5329`.
- `combat_defense`:00451410/00451180 y máscara004511a4. Limpia1296 bytes y
  sigue first/next. Sólo forts canónicos activos usan su rango49/64/81 y
  currentX/Y. Distancia signed con wrap32 estrictamente menor que el rango;
  cada contribución suma10 con wrap de byte. La especialización de004480a8
  para clase10 no lee owners ni targets. Se omiten iteraciones fuera del
  backing que004511a4 siempre rechaza, conservando todas las escrituras y su
  orden. No consume RNG ni modifica flags/pools.

La revisión cruzada de edificios y defensa contra el assembly no detectó
discrepancias. Sus suites contrastan también tablas/máscaras contra el PE,
el corpus de43 documentos, campos anteriores, alias y errores tardíos. Son
pruebas de reconstrucción estática, sin observación de una batalla nativa.

[test_combat_territory.cpp](../tests/test_combat_territory.cpp) cubre orden de
enlaces frente a ID, categorías signed y activas, sockets y raza conservada,
ramas sin batalla, warhead con/sin enlace48, último par hostil, dirección de
pactos, último bit de minas, filtro dominio1 en mar, categoría19/población
negativa, creación intercalada real, semilla posterior, defensa y pools llenos.
La composición se contrasta con llamadas explícitas a las hojas en el orden
original, además de oráculos literales de selección, participantes y RNG.

Los fallos tardíos comprueban rollback de sitios, pools, listas, RNG e informe;
se cubren alias entre documento/destino y contexto/informe, selección explícita
frente al wrapper y un rechazo de minas tras su primer draw. El corpus de
TUTORIAL se usa para consultas y territorios sin lista extranjera; no se presenta
como ejecución nativa ni como una resolución completa de sus combates.

La auditoría independiente y el coordinador revisaron selección y orden de
composición sin detectar discrepancias estáticas. El build central final y la
prueba focal `combat_territory` pasaron (0,69s), según el coordinador. Antes se
corrigió una declaración mixta de `auto` en el test. No se ejecutaron builds
adicionales desde esta tarea. El resultado de las regresiones globales normal y
ASAN se registra por el coordinador en `RECOVERY`, fuera de esta auditoría.
