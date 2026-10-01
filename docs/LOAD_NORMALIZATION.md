# Normalización parcial de carga, RNG y contratos compartidos

Lote EST-01..08, 2026-10-01. **No es todavía una carga jugable ni un turno.**
El inspector continúa leyendo el documento archivado, sin estas mutaciones.

## Contrato y secuencia

`State::prepare` conserva el documento y no inicializa RNG. Desde `Prepared`,
`State::normalizeLoad(LoadProfile, LoadReport, Error, LoadScope::Partial)` ejecuta:

1. Perfil local y núcleo de carga: opciones de campaña, dificultad, nombres,
   tipos de jugador offline, reinicios conocidos y vínculos de objetos/trabajos.
2. Continentes, contadores de ciudades/santuarios y caminos entre centros locales.
3. Refresco de tareas, balance laboral y topes de almacén de `labor_balance`.
4. Restricción de investigación de campaña, después del balance como en el original.
5. Reseed final offline del RNG propietario y reconstrucción del grafo tipado.

Se trabaja sobre candidatos temporales. Sólo se publican documento, grafo, RNG,
etapa e informe después de validar todo. Un fallo tardío también conserva el
estado anterior y los handles. El éxito mantiene las identidades de los objetos,
pero invalida punteros prestados a documento/grafo, como una edición estructural.
Mover la sesión transfiere también el RNG y deja el origen vacío; preparar un
documento nuevo lo vuelve a dejar sin inicializar.

La etapa resultante es `LoadNormalized`, **no `Active`**. No permite captura SAV,
ediciones estructurales, fases económicas aisladas ni avanzar turno. La petición
`LoadScope::Complete` falla explícitamente sin modificar nada. `complete=false`
y la lista de capacidades ausentes forman parte del informe, no sólo del texto
de la documentación.

### Núcleo y dominio admitido

`load_profile.*` cubre partidas generation-4 de versiones **0x26..0x120**,
offline, no editor ni reingreso de red. El codec sigue admitiendo 35..0x120;
las versiones 35..37 no se normalizan porque faltan sus conversiones de
espionaje/mercado/trabajos. No se cambia el formato de archivo.

El perfil permite seleccionar jugador 0..6 o conservar el slot guardado (`-1`),
y aporta un nombre explícito de hasta 32 bytes (`New Player` por defecto).
No lee preferencias del sistema. Aplica el clamp de dificultad 0..4, limpia
`hasWon`, conserva contadores de victoria cargados y aplica opciones de campaña.
Los tres bytes de progreso se mantienen en el informe propietario, sin escribir
la tabla mutable global heredada. Reconoce campañas 0..42.

Los nombres se ajustan antes de convertir los demás humanos en IA, igual que
`LoadPlayers` antes de `LoadJobs`. No se inventan vtables ni se ejecuta la IA.
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

- Inicialización de IA, ministros y dependencias ejecutables.
- Visibilidad y contactos con contexto racial, tecnológico, pactos y unidades.
- Inteligencia/cache de edificios y población conocida (`T+38`, snapshots de sitios).
- Reconstrucción nativa del registro de eventos y sus efectos.
- Estado transitorio: reinicios pendientes, `T+36`, flags de fase, temporizadores/UI.
- Escaneo y consumo intermedio en la rama de mundo cambiado.

La creación/baja completa de entidades, costes, huellas, transporte y empleos
sigue en EST-04c; sólo se reusan handles y se reconstruyen enlaces al cargar.
La conexión de efectos de gameplay entre todos los módulos sigue en EST-07.

## Comandos y comprobación

```powershell
.\build-verified\src\dl2sim.exe normalize-load "C:\GOG Games\Deadlock 2\TUTORIAL.SAV"
.\build-verified\src\dl2sim.exe normalize-load-archive "C:\GOG Games\Deadlock 2\LEVELS" CHCHT1
.\build-verified\src\dl2sim.exe activate "C:\GOG Games\Deadlock 2\TUTORIAL.SAV"
```

Los dos primeros sólo imprimen JSON con `can_play:false`, `complete_load:false`
y capacidades pendientes. El tercero rechaza activación completa. Ninguno acepta
destino SAV. La instalación original se mantiene de sólo lectura.

Del corpus disponible, 38 documentos pasan esta secuencia parcial. Los 8 escenarios
de versión 35 (`CYTH3`, `HUMAN5`, `RELU5`, `TARTH2/3/4`, `UVA3/4`) se prueban como
rechazos de normalización sin mutación; continúan admitidos para copia archival.

Pruebas dedicadas: `load_profile`, `load_derived`, `session_rng`, `table_contracts`,
`runtime_load` y ampliación de `simulation_cli`. Incluyen oráculos derivados de
assembly/decompilado, tablas comparadas directamente con el PE, transacciones,
aislamiento, estados sintéticos, snapshots y corpus real. Igualdad entre dos
ejecuciones del port acredita determinismo, no observación de paridad ejecutando
el original. Resultados de las suites en [RECOVERY.md](RECOVERY.md).
