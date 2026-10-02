# Normalización parcial de carga, RNG y contratos compartidos

Lotes EST-01..08 y continuación EST-01b/02b/04c/05b/07b, 2026-10-01.
**No es todavía una carga jugable ni un turno.**
El inspector continúa leyendo el documento archivado, sin estas mutaciones.

## Contrato y secuencia

`State::prepare` conserva el documento y no inicializa RNG. Desde `Prepared`,
`State::normalizeLoad(LoadProfile, LoadReport, Error, LoadScope::Partial, LoadContext)` ejecuta:

1. Perfil local y núcleo de carga: opciones de campaña, dificultad, nombres,
   tipos de jugador offline, reinicios conocidos y vínculos de objetos/trabajos.
2. Reinicio propietario de sesión/combate y tres Rand15 de ResetVariables, con
   snapshot pre-reset; es alternativa al snapshot pre-eventos, no otra semilla.
3. Registro de eventos con su contexto explícito; nunca se adivina una semilla del SAV.
4. Mundo cambiado: alturas/colores, parches de paleta y selección, con WorldParams
   y pendiente de sombreado anteriores; consume la continuación RNG de eventos.
5. Inicialización ejecutable de datos/bindings IA; no ejecuta RunAITurns.
6. Continentes, ciudades/santuarios y caminos; entrega de avisos de santuarios
   al registro local o a reacciones IA, con su contexto transitorio explícito.
7. Detección, visibilidad, población conocida y snapshots de edificios/sitios.
8. Tareas, balance laboral y topes de almacén; restricción de investigación de campaña.
9. Temporizador con reloj explícito; reseed final offline y reconstrucción del grafo.

Se trabaja sobre candidatos temporales. Sólo se publican documento, grafo, RNG,
etapa e informe después de validar todo. Un fallo tardío también conserva el
estado anterior y los handles. El éxito mantiene las identidades de los objetos,
pero invalida punteros prestados a documento/grafo, como una edición estructural.
Mover la sesión transfiere RNG, IA, eventos, temporizador, buffers de reinicio,
mapa generado, contadores derivados y avisos entregados. Deja el origen vacío;
preparar un documento nuevo elimina esas proyecciones.

La etapa resultante es `LoadNormalized`, **no `Active`**. No permite captura SAV,
ediciones estructurales, fases económicas aisladas ni avanzar turno. La petición
`LoadScope::Complete` falla explícitamente sin modificar nada. `complete=false`
y la lista de capacidades ausentes forman parte del informe, no sólo del texto
de la documentación.

`headlessComplete=true` significa efectos de carga sin ventanas completados;
puede quedar `NativePresentation`. No equivale a `complete`, `Active` ni `can_play`.
La auditoría confirmó que **LoadGame no ejecuta un turno IA**: `AiExecution` no
figura como efecto de carga ausente, aunque RunAITurns sigue siendo necesario
para jugar. La CLI separa `missing` de `playability_missing`.

### Núcleo y dominio admitido

`load_profile.*` cubre partidas generation-4 de versiones **35..0x120**,
offline, no editor ni reingreso de red. Las versiones 35..37 descartan los
trabajos normales cargados; no borran ministerJobs, aiWarMask ni scratchJobs.
Versión 35 inicializa espías con propietario −1 y mercado con turno −1.
Para representar esos bloques en un documento validable, el candidato parcial
promueve **35 → 36**; el informe conserva ambas versiones. Es una adaptación
del documento en memoria, no un cambio del archivo original ni una ruta de
exportación. La copia archival conserva exactamente la versión y bytes recibidos.

El perfil permite seleccionar jugador 0..6 o conservar el slot guardado (`-1`),
y aporta un nombre explícito de hasta 32 bytes (`New Player` por defecto).
No lee preferencias del sistema. Aplica el clamp de dificultad 0..4, limpia
`hasWon`, conserva contadores de victoria cargados y aplica opciones de campaña.
Los tres bytes de progreso se mantienen en el informe propietario, sin escribir
la tabla mutable global heredada. Reconoce campañas 0..42.

Los nombres se ajustan antes de convertir los demás humanos en IA, igual que
`LoadPlayers` antes de `LoadJobs`. `LoadCoreReport::session` posee los reinicios
de sesión y metadatos de IA/ministros: personalidad, estrategia, contador 40,
seis configuraciones y scratch cero. Distingue una inicialización para IA ya
cargada y dos para humanos convertidos. La evidencia confirma que las seis
hojas de reset de ministros son RET, no callbacks que se hayan omitido.
`aiExecutable=false` indica que no existe RunAITurns completo. `AiSession` sí
ejecuta la inicialización final y conserva bindings tipados; sus 24 entradas de
fase de ministros son RET8 verificados en el PE, en orden 0,5,1,4,3,2, no
callbacks ausentes sustituidos por no-ops.
Las palabras históricas de Player/ministros siguen siendo datos archivados inertes.
Eventos de versiones anteriores a 0x120 se descartan explícitamente; el codec
archival los sigue conservando. Se limpia la cola no serializada de territorios,
`Army+44`, y se asigna `Army.job` por los IDs de trabajos: lectura sin signo,
última referencia gana. Los enlaces de edificios siguen el orden físico cargado.

Evidencia: `0045f828`, `0044fd14`, `0045fae4`, `004606f4`, `00461078`,
`0044cabc`, `00486910`, `004600d0`. Assembly confirma el clamp tras leer aiSkill
y el `MOVZX` de IDs de ejército, aunque el decompilado los muestra incorrectamente.
Las metas tipo 4 usan +04 como cantidad de razas y payload desde +08: no inferir
semántica de los nombres `turns`/`count` de la tabla. `004501b0` cancela la
investigación prohibida y limpia el bit de **tech[47].availableMask** en dirección
fija, no el de la tecnología prohibida; se conserva esa peculiaridad original.

### Datos derivados

`load_derived.*` reconstruye `ComputeContinents` (`004423b4`), `CountShrines`
(`00486964`) y caminos de **tiles** (`0047dd24`), no carreteras de sitios de
construcción (`0047dfdc`). Sus avisos son semánticos; `load_shrine_events` los
entrega a LogEventEx/IA reales antes de AfterMove. Sin contexto necesario de
RNG/cola/máscaras, `ShrineEventDelivery` queda pendiente. Los contadores pertenecen
al informe y a `State::loadDerived()`, no a `gs/gg`.

Conserva OR de máscaras guardadas, la peculiaridad del segundo salto de
continentes, costes de caminos de la tabla `004dcc04`, FIFO de 160 entradas y
desempate N/E/S/W. No sustituye esos algoritmos por otros aparentemente mejores.
El dominio con bit31 que haría infinito el bucle firmado original se rechaza,
y los recorridos tienen guardas de recursos. El destino vial inaccesible conserva
la marca local peculiar del original; no se convierte arbitrariamente en éxito
de una ruta de movimiento. Estas carreteras no implementan rutas de unidades.

### Inteligencia durante la carga

`load_intelligence.*` reproduce la rama **load=1** de `0046e730` y sus hojas
`00447090`, `00446fd4`, `00446440` (mode3), `0046e338` y `0046e064`.
Reconstruye detección con radio 4/5, visibilidad por propiedad, adyacencias,
unidades, tecnología, raza, pactos direccionales y los contextos explícitos de
revelado. Copia/limpia los snapshots de sitios, incluyendo el byte de camino
`Site+10 → +1c`, labor y flags; actualiza población conocida y `T+36`.
No consume RNG ni usa globales; se publica junto al resto de la normalización.

El original **omite descubrimientos de contactos al cargar**. El informe dice
`contactDiscoverySkippedOnLoad=true`; no afirma haber ejecutado descubrimientos
de movimiento. Esos efectos y la niebla en interfaz pertenecen a MOV-05/06/08.
La secuencia derivados → inteligencia → labor conserva las dependencias: las
hojas de inteligencia no consultan los caminos reconstruidos por derivados.
Se rechazan referencias de huella inseguras y N=111: el bucle original N+1
desbordaría su almacenamiento. No se reproduce esa corrupción de memoria.
La consulta racial usa la dirección firmada original dentro del bloque RaceStats:
raza −1 de un slot inactivo lee fila 51/columna 6, no se normaliza a raza cero
ni se omite el slot. Direcciones fuera del bloque propietario se rechazan.

### Registro de eventos y temporizador

`load_session.*` reconstruye texto binario, payload, páginas, posición inicial
y retratos de los eventos guardados. `event_portraits.*` contiene 455 nombres
en 105 combinaciones raza/categoría, contrastados directamente con el PE.
El RNG secundario se consume por evento y en orden; categorías sin retrato y
categoría 7 no consumen. Esta última compara contadores de ciudades **previos a
la carga**, con pactos originales, no los santuarios recién reconstruidos.

`EventLoadContext` aporta snapshot **inmediatamente anterior a LoadEventLog** y
los siete contadores previos. No es la semilla del comienzo de LoadGame:
`LoadContext.startup` permite aportar esa otra frontera y ejecutar los tres
Rand15 originales. Aportar ambos contextos se rechaza. El resultado posee trazas
RNG y snapshot posterior, separados de la resembra final desde gameId.
Sin contexto y con eventos no vacíos, `NativeEventLog` continúa pendiente.
Con contexto incorrecto se rechaza toda la transacción, no se publica media carga.

Dominio de replay actual: pool total con terminadores menor que 3071 bytes;
textos sin NUL interno; se rechaza ID 0x646c, que en el original coincide con
una fila fantasma fuera de tabla. La expulsión usa qsort Borland, incluido −1
en empates, no std::sort. Conserva el desplazamiento peculiar del payload por
índice de archivo y los datos en ranuras inactivas. La prioridad que impide
desalojar se rechaza, igual que LoadEventLog.
Estas restricciones no cambian el codec archival, que conserva los bytes.
Versiones anteriores a 0x120 descartan eventos sin consumir RNG, como el original.
`logLocalEvent` genera texto canónico (%s/%d), expulsa por límite50/pool, consume
retratos una vez, convierte jugador/pacto del evento58 y aplica la pareja racial
del123 después del draw original. Un rechazo de prioridad conserva la ordenación
y no consume RNG. No enruta automáticamente a IA ni entrega ventanas. Argumentos
inválidos o textos que desbordarían el buffer original fallan antes de mutar.

`planLoadTimer` usa reloj y estado anterior explícitos: autoTimer reinicia;
lastPlayerTimer sólo inicia si no corría y queda un jugador sin terminar.
Se conserva la asimetría original: activos hasta numPlayers, terminados en los
siete slots. `LoadContext.clockMs` integra el plan en State; no inicia un hilo
ni finaliza automáticamente turnos. `load_startup` posee buffers/scalars de
reinicio, victoria, combate, flags finales y EventLog activo. No borra los arrays
cargados después de ResetVariables ni confunde una petición UI con su entrega.

### Mundo cambiado y reacciones IA

`load_world_presentation` compara los 20 bytes de WorldParams. Si cambió, aplica
SeedRtl(world.rngSeed), generación original de terreno/alturas/colores/sombreado/
ríos/escalado con Long31, parches físicos de paleta, AND0x0000fff0 en flags y
selección/cámara. La pendiente previa de sombreado es contexto explícito y los
huecos de paleta no se rellenan. Sin cambio, documento/RNG/pendiente quedan iguales.
Bitmaps y parches son datos propietarios: ventanas, sprites, aplicación de paleta,
temporizador nativo y briefing de campaña siguen pendientes en presentación.

`AiSession::reactDiplomacy` porta00404cec, respuestas, matrices de actitudes de los
dos bloques llamados scratchJob, máscaras de cambio y cola42/41 útil. Consume el
draw antes de descartar por cola llena/destinatario no humano. No contesta mensajes
humanos pendientes. `reactEvent` cubre chat, gratitud, penalización y hostilidad
sin disolución de guerras/pactos previos; negociación y esas dependencias fallan
sin publicar documento, cola, máscaras ni RNG. No equivale a RunAITurns.
Máscaras/cola no se reinician por LoadGame: deben aportarse. LogEventEx usa sus
argumentos7/8, no los del formato; LogEvent ordinario aporta0,0.
`State::reactDiplomacy/reactAiEvent` conserva la continuación y rechaza rebobinarla.

## RNG de sesión

`SessionRng` posee low/high de RTL y el segundo generador. Implementa rand15,
lrand31, secundario15, rango etiquetado y reseeds separados/conjunto. Las semillas
son explícitas: no hay reloj, RNG global ni seed automática por turno.
Las operaciones producen ordinal, etiqueta propia y contadores comprobables;
un rango cero registra la operación sin consumir un valor aleatorio.
Snapshots versionados permiten restaurar exactamente **nuestro** estado propio.

La rama final offline de `LoadGame` (`004618e8` → `00477394`) inicializa ambos
generadores desde **options.gameId**, con RTL high=0. No usa gameSeed/world.rngSeed
ni restaura del SAV una secuencia interna que el formato no guarda. Mundo cambiado
y avisos de santuarios ya consumen la secuencia anterior a esa resembra final.
Los contadores del RNG normalizado comienzan en cero tras el reseed final.

`SaveGame` original consume `lrand()%10000`, escribe gameId y resembra antes de
serializar. `planOfflineSaveRng` reproduce esa frontera sin permitir exportar un
experimento. Su integración en guardado jugable sigue pendiente: ni el codec
ni `prepare/capture` pueden introducir ese consumo al hacer una copia archival.
Producción, combate y turno IA completo deben conectar sus consumidores; las
primitivas y reacciones aisladas no acreditan un turno entero.

## Tablas y capacidades ausentes

`data::*` es la fuente canónica. `economy_tables.cpp` ahora sólo construye
adaptadores compatibles; no conserva otra copia literal divergente. Campañas
son 43 en todos los contratos, con defaults inmutables y una copia mutable
heredada separada. `turn_api.h`/`newgame.h` comparten tablas canónicas y
`supplemental_tables.*` define las pequeñas tablas restantes verificadas del EXE.
Esto no activa los módulos globales ni implementa objetivos de campaña completos.

Los wrappers inline incompatibles de `turn_api.h` quedan declarados para futura
implementación real; no se reemplazan por stubs que aparenten éxito.
Las capacidades ausentes de la carga se enumeran explícitamente:

- Registro/reinicio/mundo/timer cuando faltan sus contextos explícitos.
- Avisos de santuarios cuando falta RNG o cola/máscaras de IA.
- Presentación: ventanas, sprites/paleta, timer y briefing. Generar el mapa no
  equivale a entregarlo al motor gráfico.

EST-04c incorpora edificios especiales, unidades con transporte/parejas, bajas,
demolición no-santuario, pagos/importaciones y comienzo de obra; ver
`ENTITY_RUNTIME.md`. Fabricación y finalización de obra todavía no son turnos.
La conexión de efectos de gameplay entre todos los módulos sigue en EST-07.

## Comandos y comprobación

```powershell
.\build-verified\src\dl2sim.exe normalize-load "C:\GOG Games\Deadlock 2\TUTORIAL.SAV"
.\build-verified\src\dl2sim.exe normalize-load-archive "C:\GOG Games\Deadlock 2\LEVELS" CHCHT1
.\build-verified\src\dl2sim.exe normalize-load-seeded "C:\GOG Games\Deadlock 2\TUTORIAL.SAV" 123
.\build-verified\src\dl2sim.exe normalize-session "C:\GOG Games\Deadlock 2\TUTORIAL.SAV" 123
.\build-verified\src\dl2sim.exe activate "C:\GOG Games\Deadlock 2\TUTORIAL.SAV"
```

Los comandos normalize sólo imprimen JSON con `can_play:false`, `complete_load:false`
y capacidades pendientes. `normalize-load-seeded` define un contexto de prueba:
semilla explícita anterior a los eventos y siete contadores previos cero; no
afirma recuperar el contexto histórico ausente del SAV. `normalize-session` usa
un contexto frío explícito: semilla pre-reset y mundo anterior/ciudades/pendiente/
reloj/máscaras/cola cero. `activate` rechaza la
activación completa. Ninguno acepta destino SAV. Originales de sólo lectura.

El corpus incluye 46 documentos; los ocho escenarios de versión 35 son `CYTH3`,
`HUMAN5`, `RELU5`, `TARTH2/3/4`, `UVA3/4`. Sus migraciones se verifican además
de la conservación archival exacta. Resultados de ejecución en `RECOVERY.md`.

Pruebas dedicadas: `load_profile`, `load_derived`, `session_rng`, `table_contracts`,
`runtime_load`, `load_intelligence`, `load_session`, `entity_creation` y ampliación
de `simulation_cli`. Incluyen oráculos derivados de
assembly/decompilado, tablas comparadas directamente con el PE, transacciones,
aislamiento, estados sintéticos, snapshots y corpus real. Igualdad entre dos
ejecuciones del port acredita determinismo, no observación de paridad ejecutando
el original. Resultados de las suites en [RECOVERY.md](RECOVERY.md).
