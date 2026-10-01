# Normalización parcial de carga, RNG y contratos compartidos

Lotes EST-01..08 y continuación EST-01b/02b/04c/05b/07b, 2026-10-01.
**No es todavía una carga jugable ni un turno.**
El inspector continúa leyendo el documento archivado, sin estas mutaciones.

## Contrato y secuencia

`State::prepare` conserva el documento y no inicializa RNG. Desde `Prepared`,
`State::normalizeLoad(LoadProfile, LoadReport, Error, LoadScope::Partial, LoadContext)` ejecuta:

1. Perfil local y núcleo de carga: opciones de campaña, dificultad, nombres,
   tipos de jugador offline, reinicios conocidos y vínculos de objetos/trabajos.
2. Reconstrucción propietaria del registro de eventos, si está vacío o se aporta
   su contexto previo explícito. Nunca se adivina una semilla ausente del SAV.
3. Continentes, contadores de ciudades/santuarios y caminos entre centros locales.
4. Detección, visibilidad, población conocida y snapshots de edificios/sitios.
5. Refresco de tareas, balance laboral y topes de almacén de `labor_balance`.
6. Restricción de investigación de campaña, después del balance como en el original.
7. Planificación del temporizador, cuando se aporta el reloj explícito.
8. Reseed final offline del RNG propietario y reconstrucción del grafo tipado.

Se trabaja sobre candidatos temporales. Sólo se publican documento, grafo, RNG,
etapa e informe después de validar todo. Un fallo tardío también conserva el
estado anterior y los handles. El éxito mantiene las identidades de los objetos,
pero invalida punteros prestados a documento/grafo, como una edición estructural.
Mover la sesión transfiere también RNG, metadatos de IA, eventos y temporizador,
y deja el origen vacío; preparar un documento nuevo elimina esas proyecciones.

La etapa resultante es `LoadNormalized`, **no `Active`**. No permite captura SAV,
ediciones estructurales, fases económicas aisladas ni avanzar turno. La petición
`LoadScope::Complete` falla explícitamente sin modificar nada. `complete=false`
y la lista de capacidades ausentes forman parte del informe, no sólo del texto
de la documentación.

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
`aiExecutable=false`: no se inventan vtables ni se ejecutan decisiones de IA.
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
construcción (`0047dfdc`). Sus salidas de eventos son avisos semánticos: no textos
SAV ni efectos de UI/IA. Los contadores pertenecen al informe, no a `gs/gg`.

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
los siete contadores previos. No es la semilla del comienzo de LoadGame: quedan
consumos anteriores y mundo cambiado por integrar. El resultado posee trazas
RNG y snapshot posterior, separados de la resembra final desde gameId.
Sin contexto y con eventos no vacíos, `NativeEventLog` continúa pendiente.
Con contexto incorrecto se rechaza toda la transacción, no se publica media carga.

Dominio de replay actual: pool total con terminadores menor que 3071 bytes;
textos sin NUL interno; se rechaza ID 0x646c, que en el original coincide con
una fila fantasma fuera de tabla. La expulsión del pool lleno aún no está portada.
Estas restricciones no cambian el codec archival, que conserva los bytes.
Versiones anteriores a 0x120 descartan eventos sin consumir RNG, como el original.
La reconstrucción del registro no genera los futuros eventos de gameplay ni UI.

`planLoadTimer` usa reloj y estado anterior explícitos: autoTimer reinicia;
lastPlayerTimer sólo inicia si no corría y queda un jugador sin terminar.
Se conserva la asimetría original: activos hasta numPlayers, terminados en los
siete slots. `LoadContext.clockMs` integra el plan en State; no inicia un hilo
ni finaliza automáticamente turnos. El resto de transitorios sigue pendiente.

## RNG de sesión

`SessionRng` posee low/high de RTL y el segundo generador. Implementa rand15,
lrand31, secundario15, rango etiquetado y reseeds separados/conjunto. Las semillas
son explícitas: no hay reloj, RNG global ni seed automática por turno.
Las operaciones producen ordinal, etiqueta propia y contadores comprobables;
un rango cero registra la operación sin consumir un valor aleatorio.
Snapshots versionados permiten restaurar exactamente **nuestro** estado propio.

La rama final offline de `LoadGame` (`004618e8` → `00477394`) inicializa ambos
generadores desde **options.gameId**, con RTL high=0. No usa gameSeed/world.rngSeed
ni restaura del SAV una secuencia interna que el formato no guarda. El escaneo
anterior de mundo cambiado puede consumir otra secuencia y sigue pendiente.
Los contadores del RNG normalizado comienzan en cero tras el reseed final.

`SaveGame` original consume `lrand()%10000`, escribe gameId y resembra antes de
serializar. Eso corresponde a un futuro guardado jugable completo: ni el codec
ni `prepare/capture` pueden introducir ese consumo al hacer una copia archival.
El orden real de llamadas de producción, combate, IA y turnos queda pendiente
con cada módulo; los tests de primitivas no acreditan un turno entero.

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

- Dependencias ejecutables de IA/ministros; los reinicios de datos ya están portados.
- Registro de eventos cuando falta contexto previo, y dominios de expulsión aún excluidos.
- Estado transitorio: scratch de sesión, flags de fase, selección y UI; el timer
  ya tiene plan nativo opcional, no ejecutor de turnos.
- Generación visual de alturas/colores y consumo intermedio de la rama de mundo
  cambiado. No confundirla con la visibilidad territorial ya implementada.

EST-04c ya crea edificios terminados ordinarios con ID, huella, balance laboral
local y caminos de sitios, y dispone de plantillas de unidad. Costes, órdenes
de construcción, transporte y bajas siguen pendientes; ver `ENTITY_RUNTIME.md`.
La conexión de efectos de gameplay entre todos los módulos sigue en EST-07.

## Comandos y comprobación

```powershell
.\build-verified\src\dl2sim.exe normalize-load "C:\GOG Games\Deadlock 2\TUTORIAL.SAV"
.\build-verified\src\dl2sim.exe normalize-load-archive "C:\GOG Games\Deadlock 2\LEVELS" CHCHT1
.\build-verified\src\dl2sim.exe normalize-load-seeded "C:\GOG Games\Deadlock 2\TUTORIAL.SAV" 123
.\build-verified\src\dl2sim.exe activate "C:\GOG Games\Deadlock 2\TUTORIAL.SAV"
```

Los comandos normalize sólo imprimen JSON con `can_play:false`, `complete_load:false`
y capacidades pendientes. `normalize-load-seeded` define un contexto de prueba:
semilla explícita anterior a los eventos y siete contadores previos cero; no
afirma recuperar el contexto histórico ausente del SAV. `activate` rechaza la
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
