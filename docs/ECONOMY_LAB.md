# Laboratorio económico sobre documentos guardados

El laboratorio separa las **consultas sobre una instantánea guardada** de los
experimentos que aplican una subfase o un tramo económico explícito. No ejecuta un turno, no sustituye la
normalización original de carga y no convierte el inspector en una partida
jugable. Las entradas originales son de sólo lectura.

## Capacidades y límites

| Operación | Resultado | Mutaciones |
|---|---|---|
| `simulation::planProduction` | Tareas y outputs por edificio, con asignación guardada y consulta máxima por ranura | Ninguna |
| `simulation::taskOutput` | Output escalar de una ranura con labor proporcionada | Ninguna |
| `simulation::planNeeds` | Necesidad actual de comida/energía y su representación como reserva `s16` | Ninguna |
| `simulation::planEnergy` | Proyección de consumo energético y solicitudes semánticas de déficit | Ninguna |
| `State::consumeEnergy` | Aplica la proyección energética una sola vez desde `Prepared` | Sólo almacén de energía y porcentaje energético, en memoria |
| `State::runEconomicProductionPrefix` | Reinicios → impuestos → producción 1 → necesidades/importaciones → comida → energía → mantenimiento → producción 2 → financiación de obras | Tramo conectado y transaccional; se detiene antes de crecimiento, moral, investigación y revueltas |
| `State::runEconomicPhase` | Secuencia anterior → crecimiento → moral → investigación → disturbios/deserciones → balance final | Fase económica transaccional dentro de sus dominios seguros; NO turno completo ni exportación |

Todos los planes reciben `const save::Document&`, devuelven errores explícitos y
conservan el informe anterior si fallan. No usan `gs`, `gg`, RNG, callbacks ni
punteros históricos. Rechazan mapas reducidos y los dominios que su cálculo no
puede evaluar con seguridad; no reparan silenciosamente la entrada.

La consulta no modifica materiales, créditos, población, trabajo pendiente,
colas, tareas ni eventos. **Sumar sus outputs no implementa producción**: los
outputs de tareas tienen significados distintos, y aplicarlos exige construcción,
logística, creación de unidades, investigación, eventos y otras reglas.

## Órdenes económicas locales — 2026-10-02

`State::transferLabor`, `moveLabor`, `resetLabor`, `controlBuilding`,
`movePopulation` y `orderResearch` operan desde `Prepared`/`EntitiesEdited`.
Exigen actor local humano (`type1`, `Player.index` igual al slot); las órdenes
territoriales también exigen propiedad. Es una frontera deliberada del comando,
no una condición atribuida a todos los setters internos del original.
Sus resultados alimentan `runEconomicPhase`; no abren ventanas ni habilitan
turno completo, guardado reanudable o edición tras una fase terminal.

- Labor: transferencia explícita entre ranuras0..4, movimiento automático de
  un trabajador y reinicio a vivienda, con las prioridades, empates, locks y
  efectos parciales originales. No se confunden ranuras con IDs de tareas.
  Se comparte `adjustBuildingLabor` con el traslado de población.
- Edificios: cuerpo headless de activación0041d2bc y bloqueo0041d834, setters
  0044c3fc/0044c44c y balance real. Desactivar borra locks y solicita trasladar
  la labor a vivienda, luego hace narrowing firmado16. Una vivienda puede
  transferir a su propia ranura: éxito no significa necesariamente trabajador
  retirado. No se ejecutan el cierre de ventana ni sus efectos independientes.
- Población:0046ae9c/00476448, coste y moral con wrap/narrowing originales,
  capacidad/vivienda, ajuste laboral y balances. Se conservan importes negativos
  del dominio nativo. El caso de edificio fuente ausente devuelve falso DESPUÉS
  de pago/población/plaga; esos efectos se publican, no se descartan como rechazo.
- Investigación: borrador deduplicado004839e4, toggle0043cc5c, clear0043cb7c,
  poda00483b84 y commit0043cbf8/00483a10. `Select` es una comodidad explícita
  que reemplaza el borrador por una tecnología permitida contra cola vacía;
  un clic rechazado no confirma el borrador. El commit compara con el valor
  vivo **`DAT00559db0` proporcionado por el llamador**, no con currentResearch.
  La máscara viva de campaña también es explícita. Compartir reglas de cola
  con `research_phase` evita predicados incompatibles.

Las hojas de investigación internas incluyen el setter de byte0048424c, el
selector00483cbc y autoResearchLocal0046f804. El selector por defecto conserva
la primera tecnología disponible aunque sea conocida/prohibida; sólo el fallback
47 aplica los filtros originales. AutoResearch sigue su guard exacto y no es
planificación IA0040cea4. Estas hojas no añaden progreso, eventos ni RNG.

La plaga0047ca98 usa un array nativo de50, pero el documento posee25 registros;
si se llenan, se rechaza atómicamente antes de invadir el bloque Spies. Una nueva
plaga conserva los campos originales salvo `event+04`, neutralizado a0: su destino
vive en `PopulationEventBindings`. Los punteros históricos ya guardados permanecen
opacos. State conserva este sidecar y exige igualdad en la continuación; no se
presenta como codificación SAV equivalente ni como ejecución de la plaga.

Errores de API revierten documento, informe, handles y metadatos. Rechazos
ordinarios sin cambios mantienen el estado anterior; una orden aceptada o un
retorno falso con efectos pasa a `EntitiesEdited`. Las colas de investigación
no invalidan los handles de nodos de producción. Índices inseguros, divisiones
que atrapan, búsquedas sin progreso y bucles de más de un millón de operaciones
se rechazan explícitamente, sin inventar resultados.

Ejemplos sobre TUTORIAL.SAV, cada uno desde una preparación nueva en memoria:

```powershell
build-verified/src/dl2sim transfer-labor "C:/GOG Games/Deadlock 2/TUTORIAL.SAV" 14 10242 1 10241 1
build-verified/src/dl2sim reset-labor "C:/GOG Games/Deadlock 2/TUTORIAL.SAV" 14
build-verified/src/dl2sim building-toggle "C:/GOG Games/Deadlock 2/TUTORIAL.SAV" 10242
build-verified/src/dl2sim building-lock "C:/GOG Games/Deadlock 2/TUTORIAL.SAV" 10242 1
build-verified/src/dl2sim research-clear "C:/GOG Games/Deadlock 2/TUTORIAL.SAV" 0 -1
```

`research-select/research-toggle` añaden tecnología1..47 antes de flags/comparación.
`move-labor` recibe territorio, edificio origen y destino. `move-population`
recibe origen, destino, cantidad, modo, sitio fuente y ranura (`-1` como sentinel).
El CLI declara bindings fríos de plaga, no recupera direcciones de una sesión
histórica y publica `can_save:false`/`complete_turn:false`. Los controles y
órdenes aún no están conectados a la interfaz gráfica del inspector.

## Producción consultiva

Las fuentes principales son `FUN_0044eb4c` (TaskOutputs), `FUN_0044eeb4`
(TaskOutput), `FUN_0044e9e4` (SiteYield) y sus dependencias de tareas especiales,
labor y capacidad de población. Se usan las tablas compartidas de
`data_tables.*` y los modificadores raciales guardados en el documento.

El informe `ProductionPlan` agrupa `TerritoryProduction` por territorio y
`BuildingProduction` por edificio. Incluye ID, sitio, tipo, categoría, flags
Active/Built, `evaluated`, `maxLabor` y cinco ranuras en `assigned` y `maximum`.
Cada `SlotProduction` conserva `task`, `labor` y `output`.

- `assigned` consulta las tareas y la labor guardadas, con las excepciones
  originales de tareas especiales. No llama a `GetBuildingTasks` ni redistribuye
  trabajadores mediante `BalanceLabor`.
- `maximum` consulta cada ranura por separado, usando tareas de las tablas y la
  labor que permite el modo máximo original. **No es una asignación simultánea
  factible**: no se deben sumar sus trabajadores como un plan de empleo.
- Los edificios sin propietario evaluable se marcan `evaluated=false`; los
  campos numéricos vacíos no deben interpretarse como una producción calculada.
- Active y Built son conceptos distintos. Las funciones de consulta tienen sus
  propias condiciones; el modo máximo puede consultar un edificio inactivo.
  El informe no afirma que el primer pase vaya a ejecutar todo lo consultado.

Se preservan el orden de las multiplicaciones/divisiones, los casts originales
y el wrap definido de 32 bits. El rendimiento combina la tabla de labor,
porcentaje energético cuando corresponde, modificador racial de la tarea y
tasa base. Después intervienen los multiplicadores de santuarios/tecnología,
recursos del sitio, producción rápida y los redondeos propios de cada rama.
Comida envenenada se reduce a la mitad. El mínimo final de output con labor
distinta de cero también forma parte del comportamiento original.

Hay dos diferencias importantes entre las funciones originales:

- TaskOutputs aplica a comida/madera el bonus firmado de `Territory+0x994`,
  incluido su narrowing; TaskOutput escalar no lo aplica. No deben unificarse
  suponiendo que siempre dan el mismo resultado.
- En TaskOutputs, una ranura con tarea cero llega a la comprobación final de
  labor sin inicializar esa variable en la primera iteración, o reutilizándola
  de otra ranura. El flujo se confirmó en assembly. El informe nuevo **normaliza
  deliberadamente las ranuras vacías a labor/output cero**, en lugar de
  reproducir un valor indeterminado. No se promete paridad absoluta de ese caso.
  El pase aplicado distingue esa consulta: al completar una obra puede activarse
  una tarea posterior que usa el output cacheado de una ranura anteriormente
  vacía. Conserva el arrastre definido de labor de la tarea anterior, sin
  sustituirlo por cero ni recalcular el rendimiento después de terminar la obra.
  TaskOutput escalar sí tiene un caso definido: edificio activo, tarea cero y
  labor positiva puede devolver uno; el port lo conserva.

Un oráculo manual ilustra la diferencia del bonus: Hydroponic Farm (tipo 6),
terminada y activa, tarea de comida, capacidad de labor 6, tres trabajadores,
energía 100%, modificador racial 100 y tasa 120. Sin producción rápida ni veneno,
con cuatro sitios de la huella 2×2 a recurso Food 10000 y `value=1`, la tabla de
labor da 54: el resultado inicial es 648 y se divide a 64 antes de SiteYield.
Éste calcula `64 × (2+4) × 40000 / (4×20000) = 192`. Un bonus local de 25 añade
48: `assigned` da 240 y `taskOutput` escalar da 192. Con capacidad poblacional
suficiente, el máximo independiente de seis trabajadores da 450. Es una
derivación del código y las tablas, no una captura de ejecución del original.

### Coordenadas y energía: nombres históricos engañosos

Los dos primeros bytes de `BuildingSite` son coordenadas **persistidas** `x/y`.
`FUN_0046686c` las inicializa como `sitio % 6` y `sitio / 6`; `SaveTerritories`
(`00460870`) las guarda y `LoadTerritories` (`00460a74`) las lee sin regenerarlas.
El antiguo comentario de que eran siempre cero no era correcto. SiteYield
recorre la huella hacia la derecha y hacia filas decrecientes: una huella de
tamaño `n` debe caber en `x..x+n-1` e `y..y-n+1`. La consulta valida los datos que
lee, sin reconstruir coordenadas ni invertir el eje para ocultar inconsistencias.

El byte `Territory+0x35`, todavía llamado `knowledge` en el layout heredado, es
el **porcentaje energético**, no conocimiento tecnológico. Los cálculos
originales lo leen con signo en las ramas correspondientes. `assigned` y el
escalar conservan el valor guardado; el modo `maximum` usa 100 conforme a su
regla original. El experimento energético puede modificar el byte persistente.

## Necesidades y consumo energético aislado

`NeedsPlan` contiene `TerritoryNeeds` con `foodNeed`, `energyNeed`, `foodReserve`
y `energyReserve`, para los territorios físicos 1..N. No inventa el registro
sentinela 0 que existe en los arrays globales del ejecutable.

- `FUN_0046b958`: comida = población firmada × modificador racial guardado de
  fila 61 / 10000, con truncamiento hacia cero; territorio sin dueño necesita
  cero. Esto sólo calcula la necesidad civil, no alimenta unidades.
- `FUN_0046b910`: energía suma, en orden de sitios, los edificios con trabajo
  restante exactamente cero y Active (`flags & 4`). No exige Built (`flags & 2`).
  Lee el **byte bajo con signo** de `BuildingDef+0x0c`, aunque la declaración de
  tabla use un campo más ancho.
- `FUN_0046b9a0`: antes de registrar las reservas convierte cada necesidad a
  `s16` y la extiende a 32 bits. El plan expone esa distinción sin escribir los
  contadores transitorios originales.

`EnergyPlan` conserva por territorio almacén anterior/posterior, necesidad,
cantidad consumida y porcentaje energético anterior/posterior. Sigue
`FUN_0046bc28`: compara `min(almacén, necesidad)` en 32 bits, pero convierte a
`s16` únicamente la cantidad que resta del almacén. Si hay déficit, calcula
`max(50, cantidad * 100 / necesidad)`; si se cubre, fija el porcentaje en 100.
Se conservan signos, narrowing y wrap; una división indefinida se rechaza.

Como ejemplo aritmético derivado, para necesidad 10 y almacén 7 consume 7,
deja 0 y fija 70%; con almacén 2 fija el mínimo de 50%. Son ejemplos de la
fórmula, **no mediciones de una ejecución del juego original**.

Los déficits se exponen como `EnergyShortfall`: tipo `0x33`, destinatario,
territorio y argumento de déficit. El argumento original es 100 menos la
interpretación firmada del nuevo byte de porcentaje. Son solicitudes semánticas
de evento: no se fabrican textos, no se añaden registros a `Document::events`
y no se ejecutan efectos de UI/IA.

`State::consumeEnergy` exige una preparación nueva y aplica el plan sólo después
de que hayan terminado las validaciones y asignaciones. Pasa a `EnergyApplied`
sin cambiar `options.turn`. No puede repetirse ni encadenarse después de
`TaxesApplied`; tampoco se pueden aplicar impuestos después de energía.
`capture` rechaza ambos estados parciales. Preparar de nuevo crea otra
instantánea, no continúa una secuencia de turno.

## Orden original y límites de la secuencia conectada

La secuencia de `FUN_0046c7d4` es:

```text
reinicios → impuestos → producción 1 → registrar necesidades → importar déficits
→ comida → energía → mantenimiento → producción 2 → costes de edificios
→ población → moral → investigación → revueltas → balance final
```

Por eso el experimento `energy` consume el almacén **tal como está guardado**:
no incluye la producción/importación ni la comida que lo preceden en un turno.
Una consulta de necesidades tampoco predice automáticamente las necesidades
después de terminar edificios en producción 1. `ConsumeFood` incluye población,
unidades y abastecimiento; su fase completa no puede reemplazarse por restar
únicamente la necesidad civil.

Los reinicios económicos originales no son opcionales al integrar esa secuencia,
pero tampoco deben ejecutarse silenciosamente en una consulta o en `prepare`:

| Reinicio original | Significado y alcance |
|---|---|
| `00471b20` | Limpia 5000 bytes de registro de transferencias y pone su contador a cero; esa evidencia no acredita por sí sola la capacidad declarada por un header heredado |
| `00471bec` | Limpia 11 enteros de `Territory+0xA7E` en territorios 1..N; también se reutiliza dentro de logística |
| Inicio de `0046c7d4` | Borra `Player+0x40` (`s16`) para slots menores que `numPlayers`, y `Territory+0x9B2`, `+0xA7E` y `+0xAAA` para 1..N |
| `004455fc` | Comprueba/reconstruye la lista libre de Army, identificando huecos por `type==0`; es relevante para creación de unidades, no para estas consultas |

Los nombres `production[11]` en `+0xA7E` y `consumption[11]` en `+0xAAA` son
engañosos. El primero sirve para demandas/reservas y scratch logístico:
`RecordFoodEnergyNeeds` lo rellena e `ImportDeficits` compara contra él. El segundo
recibe el saldo calculado de producción en el modo consultivo de
`ProcessTerritoryProduction`, incluidas conversiones con signo. No deben
reinterpretarse como «producción bruta» y «consumo» basándose en esos nombres.
Ambos pertenecen a la cola no persistida del territorio. `Player+0x40` es el
acumulador de investigación, y `Territory+0x9B2` acumula curación.

La carga original también hace más que resolver referencias. Tras leer,
`LoadGame` (`004618e8`) llama a CountShrines y a AfterMovePhase (`0046e730(1)`),
que actualiza visibilidad, snapshots de sitios/población, contactos y caminos,
y termina en EndTurnBalance (`0046c780`). Este último reconstruye tareas
(`GetBuildingTasks`, `0044e7ec`), redistribuye/recorta labor (`0044bea8`) y limita
materiales 1..10 a 10000. Estos efectos de carga cuentan con su implementación
propietaria explícita en [LOAD_NORMALIZATION.md](LOAD_NORMALIZATION.md); no se
ejecutan como efecto oculto de una consulta ni de `production-prefix`.

Por tanto, una consulta del archivo no afirma ser idéntica a una consulta
**después de abrirlo y normalizarlo en el ejecutable original**. La preparación
propietaria conserva el documento para su round-trip; las normalizaciones se
solicitan mediante las operaciones de carga documentadas, sin activación jugable.

## CLI y verificación

```powershell
.\build\src\dl2sim.exe economy "C:\GOG Games\Deadlock 2\TUTORIAL.SAV"
.\build\src\dl2sim.exe economy-archive "C:\GOG Games\Deadlock 2\LEVELS" CHCHT1
.\build\src\dl2sim.exe energy "C:\GOG Games\Deadlock 2\TUTORIAL.SAV"
.\build\src\dl2sim.exe energy-archive "C:\GOG Games\Deadlock 2\LEVELS" CHCHT1
.\build\src\dl2sim.exe production-prefix "C:\GOG Games\Deadlock 2\TUTORIAL.SAV" 1
```

`economy` imprime JSON de outputs y necesidades, con `read_only:true` y
`complete_turn:false`. También declara `snapshot:"as_saved"`,
`applies_production:false` y `empty_task_slots:"normalized_zero"` para que los
consumidores no confundan el informe con una fase aplicada ni omitan la
normalización deliberada de las ranuras vacías. `energy` imprime efectos energéticos y déficits, con
`isolated:true`, turno anterior/posterior sin avance y `complete_turn:false`.
Ninguno admite un destino SAV ni publica una partida parcial. Impuestos,
preparación y round-trip siguen documentados en [RUNTIME_STATE.md](RUNTIME_STATE.md).
El comando `turn` continúa fallando explícitamente.

Las pruebas deben distinguir oráculos numéricos derivados, rollback, aislamiento
de globales/RNG, normalizaciones deliberadas y muestras reales. Dos ejecuciones
iguales del port no demuestran paridad con el original. Los resultados del build
y de CTest se registran en [RECOVERY.md](RECOVERY.md), sin inferir éxito de la
mera existencia de una prueba ni atribuir aquí un conteo pendiente.

## Avance: normalización laboral explícita

La reconstrucción de tareas, el balance de labor y el tope superior de materiales
de `EndTurnBalance` están implementados separadamente en `labor_balance.*`.
`State::normalizeLabor` aplica su plan desde una preparación nueva y el CLI
`labor` muestra sus cambios, sin producción ni avance de turno. No altera el
contrato de `economy`: éste continúa consultando la instantánea tal como se guardó.
Reglas, límites y pruebas: [LABOR_BALANCE.md](LABOR_BALANCE.md).

## Tramo de producción aplicado — 2026-10-02

`economic_prefix.*` conecta los diez primeros pasos de `0046c7d4`, desde sus
reinicios hasta `0044f110`. La API exige una instantánea que represente la entrada
a producción y un único contexto vivo de log, IA, ciudades, proveedores y RNG.
No ejecuta movimiento ni IA anteriores, ni normaliza una partida a escondidas.
`production-prefix` proporciona un **contexto frío de laboratorio**, con semilla
explícita y reconstrucción del log guardado; no recupera transitorios ausentes del SAV.

- `territory_production.*` recorre territorios 1..N y sitios/ranuras en orden.
  Comparte el recorrido de obras/mejoras: tareas vivas y outputs cacheados por
  edificio; arte consume Long31 y sus eventos se intercalan con las obras.
  Las cinco colas reciben trabajo asignado real antes de sumar créditos,
  clonación, investigación, entrenamiento, curación y materiales.
- El segundo pase importa hierro y endurium antes de ambas conversiones y
  preserva los narrowing signed16. **Ambos pases** balancean labor, limitan
  población y ejecutan TrainMilitia incluso con cero entrenamiento. Las
  conversiones son hierro→acero y endurium→triidium; `electronics` en el informe
  de refinamiento es un nombre interno, no cambio del material7.
- `economic_logistics.*` registra necesidades, importa por material/rondas de
  territorios y conserva proveedores/transferencias. FindSupplier elige el
  primer candidato viable; CollectMaterial puede transferir parcialmente y
  devolver −1, con límites por créditos incluso cuando el flete es cero.
- `economic_consumption.*` alimenta civiles y luego unidades en el orden físico
  propietario. La búsqueda gratuita consulta la misión `Army+25`, no su clase;
  el fallback cobra/importa realmente. Aplica hambre, flags y eventos50/60/2.
  La energía aplica stock/porcentaje y entrega los eventos51 reales.
- `economic_upkeep.*` agrupa unidades canónicas y calcula el mantenimiento
  cuadrático original, no una suma de la columna upkeep. Procesa los siete
  jugadores, avisa de déficit y desbanda por precio/experiencia/ID, con bajas en
  cascada y devoluciones. Una referencia viva de task force que quedaría inválida
  provoca rechazo transaccional; no se inventa una desvinculación.
- `building_costs.*` financia obras pendientes en orden unsigned16 de ID, con
  escala guardada para City Center, cobros parciales y eventos60. No vuelve a
  cobrar dinero base ni comprobar tecnología. Al completar el pago activa bit2
  y limpia los once paid; el trabajo empezará en una pasada posterior.

Todos los pasos comparten el mismo log y RNG; los avisos se entregan a los
implementadores reales locales/IA, sin callbacks ficticios. Un error tardío
revierte el tramo entero, incluidas entidades creadas, bajas, colas e identidades.
Una unidad creada y desbandada dentro del mismo tramo no deja handles colgantes.

State termina en `EconomyPrefixApplied`, con consultas permitidas pero sin
repetición, nuevas ediciones, exportación SAV ni avance de turno. La salida JSON
declara `complete_turn:false`, `complete_economic_phase:false`, `can_save:false`
y `next_step:"population_growth"`. Los comandos previos conservan sus contratos.

El comando anterior conserva ese corte. La API/comando siguiente añade sus cinco
pasos pendientes sin saltar predecesores ni repetir impuestos/producción.

## Fase económica hasta balance final — 2026-10-02

`economic_phase.*` / `State::runEconomicPhase` completan los quince pasos de
`0046c7d4` dentro de un único rollback. Reciben `EconomicPhaseContext`: el contexto
anterior más los flags vivos de campaña `DAT0059f100`, ausentes del SAV.
La máscara controla tanto bit10 de crecimiento como bit4 de restricción de
tecnologías, también durante robo/adquisición en deserciones. Es autoritativa
sobre `effects.researchCampaignFlags`, entrada explícita para las hojas aisladas
de investigación; ninguna hoja deduce que bit4 esté activo sólo por el número
de campaña guardado.

```powershell
.\build-verified\src\dl2sim.exe production-phase "C:\GOG Games\Deadlock 2\TUTORIAL.SAV" 1
```

El CLI declara contexto frío, semilla explícita y `campaign_flags:0`; no pretende
recuperar la sesión histórica. No normaliza carga ni ejecuta movimiento/IA antes
de producción. `complete_economic_phase:true` sólo se publica tras ejecutar todos
los pasos; `complete_turn:false` y `can_save:false` siguen siendo obligatorios.

- `population_growth.*`: capacidad física/vivienda, hambre, tasa racial,
  producción rápida, narrowing, avisos52/53 y restricción local de campaña bit10.
  Conserva el trigger nativo confirmado en assembly `new/100-(old-100)`, aunque
  no sea la diferencia de centenas esperable. El balance temprano sólo ocurre
  cuando ese valor es positivo.
- `colony_morale.*`: diez componentes originales y total sin clamp, además del
  resultado limitado. Impuestos, hambre, ocupación, hacinamiento, clonación,
  guarnición, cultura, arte y hospitales; la energía afecta los outputs previos,
  no se inventa un componente adicional. La rama racial fija80 permanece.
- `research_phase.*`: presupuesto signed16 real de `lastIncome`, descubrimiento,
  reparto por pactos, cambios de actitud IA, excedente a piezas electrónicas,
  tecnología33/santuarios, prerrequisitos, restricciones de campaña, cola local y
  autoselección. Tecnología0 conserva su semántica; no se trata como no-op universal.
- `colony_unrest.*`: RNG y ramas de agitación, disturbios/daño, deserción a otro
  territorio y posible tecnología robada. La búsqueda usa pactos, adyacencia y
  distancias originales. No cambia propietarios: ese efecto NO está en0046c49c.
- `planLaborBalance`: se aplica al final, después del daño a edificios y cambios
  de población; reconstruye tareas, reparte trabajo y limita materiales1..10.

Límite descubierto: `0046c5dc` envía evento87 con un entero donde el formato del
PE espera `%s`; `0046c60c` envía86 con la forma inversa. Assembly y tabla binaria
confirman un bug del original. Una deserción **hacia el jugador local** se rechaza
atómicamente, sin intercambiar IDs ni fabricar texto. Hacia IA se conserva el
dispatch nativo, que no formatea esos argumentos. También permanecen los dominios
rechazados de hojas anteriores (p.ej. baja que dejaría task force colgante).

`EconomyPhaseApplied` es terminal: mantiene handles supervivientes, retira las
colas/unidades realmente consumidas y posee log/IA/RNG/logística/ciudades finales.
No admite repetición, edición posterior, captura ni `advanceTurn`. Faltan órdenes
jugables, activación/presentación, movimiento, combate, turno IA y persistencia
del turno completo. La fase económica no equivale a terminar ese trabajo.
