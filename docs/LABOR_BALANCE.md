# Reconstrucción de tareas y balance de trabajadores

Este módulo implementa la normalización de `EndTurnBalance` sobre un documento
propietario: reconstrucción de tareas, balance laboral y límite superior de
almacenes. Es una pieza reutilizable para la carga y el turno, **no la activación
completa de LoadGame, la producción aplicada ni un turno terminado**.

## API e integración

- `simulation::planLaborBalance(const Document&, LaborBalancePlan&, Error&)`
  calcula un resultado sobre una copia temporal. Conserva la entrada y el
  informe anterior si falla. No usa globales, RNG, callbacks ni archivos.
- `runtime::State::normalizeLabor` aplica ese resultado una vez desde `Prepared`.
  Cambia tareas, trabajadores y flags de edificios, moral y almacenes de
  territorios. La validación y las asignaciones de memoria preceden a la escritura.
- El estado resultante es `LaborBalanced`. No se puede repetir, encadenar con
  los experimentos fiscales/energéticos ni exportar mediante `capture` como una
  partida reanudable. El número de turno no cambia.
- No cambian entidades, IDs, localizaciones, colas ni enlaces; el grafo de
  referencias conserva su validez. `prepare` sigue preservando los bytes del
  documento, sin ejecutar la normalización a escondidas.

El informe contiene todos los edificios en orden del documento, con sus tareas,
trabajadores y flags antes/después. Los territorios se informan en orden 1..N,
con moral y materiales antes/después, mano de obra disponible, no disponible,
asignada y disponible sin asignar. No hay territorio sentinela 0 persistido que
deba inventarse.

## Reglas reconstruidas

Fuentes principales: `GetBuildingTasks` (`0044e7ec`), refresco de tareas
(`0046c1f0`), `BalanceLabor` (`0044bea8`) y `EndTurnBalance` (`0046c780`). Las
dependencias incluyen `CanUpgradeBuilding`, reparto de labor, traslado a vivienda,
capacidad de edificio, selección de cola y cálculo de población trabajadora.

1. Se refrescan los edificios de territorios con propietario, en orden de
   territorio y casilla. Las obras concentran su trabajo en construcción. Los
   edificios terminados usan tareas de tabla, tecnologías y reglas de mejora.
   Los santuarios ocultos/marinos tienen su tarea especial dependiente del sitio.
2. El trabajo de tareas eliminadas se redistribuye respetando los bloqueos y la
   disponibilidad de la cola correspondiente. El traslado a viviendas puede
   afectar un edificio que se refrescará más tarde: el orden importa.
3. Después se balancean **todos** los territorios, también los que no tienen
   propietario. Con población cero se fija moral 100. La población y moral
   determinan la mano de obra disponible según la aritmética original.
4. Se ejecutan cuatro pasadas: tareas de energía/cultura/comida; otras tareas de
   edificios no residenciales; viviendas; devolución del sobrante a viviendas.
   No son una asignación proporcional ni un optimizador nuevo.
5. Se limitan sólo por arriba a 10000 los materiales 1..10. Material 0 y
   valores negativos permanecen intactos; no se produce ni consume ningún recurso.

Detalles importantes de fidelidad:

- Las ranuras de los edificios no residenciales se recorren `1,2,3,4,0` en su
  segunda pasada. Las tareas prioritarias descuentan capacidad cuando se alcanza
  su ranura; no se adelanta ese descuento.
- Las viviendas usan capacidad normal en la tercera pasada, incluso si están
  inactivas. La última pasada sí usa capacidad activa y no fuerza a cero un
  espacio libre negativo.
- Si el balance recorta una asignación, elimina el bloqueo de esa ranura según
  el original. No todos los cambios de tarea borran indiscriminadamente bloqueos.
- El refresco usa el bit `Player.index & 31` para sus requisitos tecnológicos;
  la mejora usa el propietario del territorio. Las máscaras tecnológicas de 16
  bits se extienden con signo antes de la prueba del bit.
- Se conservan wrap de 32 bits y estrechamientos firmados de 16/8 bits sin
  depender del overflow indefinido de C++.

## Casos extraños y límites deliberados

No se presupone que el resultado tenga siempre trabajadores no negativos ni que
normalizar dos veces sea equivalente a una vez. Por ejemplo, un City Center con
capacidad 8, seis trabajadores en comercio y seis en cultura, con población
suficiente, puede terminar con `[0,6,6,-4,0]`: la segunda pasada conserva comercio
antes de descontar cultura y escribe la capacidad negativa en la ranura siguiente.
Una vivienda inactiva también puede perder labor en la última pasada. Son casos
derivados del código original, no resultados medidos en una sesión de ese juego.

La API acepta labor firmada, tanto negativa en la entrada como generada durante
el cálculo, incluidos extremos de 32 bits. En este algoritmo labor no indexa
arrays y la división del reparto tiene denominador positivo. Las consultas de
producción actuales, en cambio, rechazan labor negativa de entrada porque sus
cálculos sí dependen de índices de labor: integrar ambos sistemas en todas las
situaciones requiere resolver/documentar ese límite, no aplicar un clamp
silencioso ni declarar paridad completa.

Si una vivienda requiere la ranura de fallback y no tiene ninguna tarea válida,
el original puede obtener índice -1 y escribir fuera del array. El port devuelve
un error sin publicar cambios. Un límite de trabajo también evita bucles de
transferencia patológicos; no los convierte en un resultado parcial exitoso.
Estos rechazos son límites seguros declarados, no emulación de corrupción de memoria.

## Uso desde consola

```powershell
.\build-verified\src\dl2sim.exe labor "C:\GOG Games\Deadlock 2\TUTORIAL.SAV"
.\build-verified\src\dl2sim.exe labor-archive "C:\GOG Games\Deadlock 2\LEVELS" CHCHT1
```

La salida JSON identifica `labor_balanced_in_memory`, `isolated:true`,
`complete_load:false`, `complete_turn:false` y `applies_production:false`.
Presenta cambios antes/después y no admite destino SAV. Los archivos originales
siguen siendo entradas de sólo lectura. El inspector gráfico no recibe órdenes
de juego como consecuencia de este cambio.

## Verificación y continuación

Las pruebas del módulo usan oráculos derivados independientes para tecnologías,
mejoras, obras, bloqueos, colas, prioridades, viviendas, signos y límites.
Las de estado comprueban aplicación exacta de campos, estabilidad del grafo,
transiciones, rechazo de guardado parcial y recuperación después de un fallo.
El CLI comprueba determinismo y protección de los archivos originales.

La suite integrada aprobó **21/21 sin omisiones**, normal y con AddressSanitizer.
La prueba laboral recorrió **46 documentos y 983 edificios**, además de los
oráculos sintéticos, y la integración runtime se verificó sobre las 46 muestras.
Los resultados ejecutados se registran en [RECOVERY.md](RECOVERY.md). Una prueba
del corpus confirma el comportamiento sobre esas muestras, no todas las
combinaciones de una partida futura ni paridad completa con el original.

Las rutas propietarias posteriores ya incorporan ciclo de vida, comienzo pagado
de obra, logística, RNG, visibilidad y normalización de campaña/IA. El helper
`prepareStartedBuildingLabor` refresca tareas y aplica la urgencia de construcción
humana sin fingir progreso de obra. `building_progress` reutiliza hojas locales
de refresh/reparto/movimiento a viviendas para completar y mejorar edificios;
`unit_manufacturing` balancea al reservar/devolver población de colonizadores.
Siguen pendientes los dos pases completos de producción, IA completa y órdenes
manuales/interfaz. Las hojas nuevas no ejecutan un balance global implícito.
