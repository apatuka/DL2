# Checklist de cierre: Deadlock II individual

Revisión: 2026-10-01. Base previa: `acdda61`, ampliada con el lote EST-01..08
descrito en [LOAD_NORMALIZATION.md](LOAD_NORMALIZATION.md).

## Qué significa «100% funcionando»

Poder iniciar, jugar, guardar, reanudar y terminar las modalidades individuales
del juego original, con sus reglas, adversarios IA, campañas, tutorial, interfaz,
recursos audiovisuales y editor. Referencia: la instalación local de Deadlock II
v1.20 y la evidencia del ejecutable reconstruido.

Quedan fuera multijugador, lobby, chat entre jugadores, transporte de red,
sincronización entre equipos y compatibilidad del protocolo. Las órdenes locales
que el original canalizaba por funciones llamadas `Net*` o `Sync*` sí hacen falta:
excluir la red no puede eliminar construir, mover o terminar turno en solitario.
No se añaden como requisito nuevos gráficos, nuevas reglas ni otros sistemas
operativos. La compatibilidad con versiones anteriores se declarará según las
muestras realmente verificadas; no se promete soporte universal sin evidencia.

Una casilla sólo se marca al tener **implementación, integración y pruebas**.
«Parcial» significa que existe una base reutilizable, no que la función jugable
esté terminada. Las casillas tienen tamaños muy diferentes: contarlas no produce
un porcentaje fiable de avance. Este inventario se ampliará si la comparación
funcional descubre comportamientos originales aún no identificados.

## Base ya conseguida

- [x] Recuperación del trabajo anterior, historial Git y documentación de continuidad.
- [x] Compilación C++20/SDL2 y ejecución reproducible de las pruebas mediante `tools/build.ps1`.
- [x] Lectores de recursos, tablas estáticas verificadas y primitivas de vídeo, entrada y audio.
- [x] Infraestructura de sprites, menús SMenu, colas, IDs y generadores aleatorios; todavía no es su integración en una partida.
- [x] Lectura, validación y escritura independiente de documentos guardados: round-trip exacto de las 46 muestras disponibles.
- [x] Inspector gráfico con carga, selección, cámara y guardado de copias nuevas; sin órdenes ni niebla de guerra.
- [x] Preparación propietaria y transaccional del estado, con referencias tipadas conocidas.
- [x] Cálculos de impuestos, rendimiento de edificios y necesidades; experimentos aislados de impuestos y energía.
- [x] Normalización explícita de tareas, trabajadores y topes de almacén, integrada en el estado propietario y el CLI.
- [x] Identidades estables y edición estructural limitada de edificios/unidades, con transacciones y rechazo de referencias retiradas o ajenas; todavía no son órdenes de gameplay.
- [x] Consultas de huella y emplazamiento originales, con motivos de rechazo y CLI de sólo lectura; no autorizan por sí solas construir.
- [x] Carga parcial offline transaccional: perfil/opciones, enlaces, continentes/caminos/santuarios, labor y RNG propietario; estado no jugable explícito.
- [x] Tablas canónicas compartidas, 43 campañas y pruebas de contratos entre cabeceras heredadas.

Última verificación: **28/28 pruebas sin omisiones**, normal y AddressSanitizer.
La suite incluye 46 documentos: **38** admiten el nuevo perfil de carga parcial;
**8 escenarios de versión 35** se rechazan transaccionalmente para normalización
y siguen disponibles para inspección/copia exacta. Derivados y reseed RNG aislados
se comprueban en los 46. Resultados de compilación/pruebas en
[RECOVERY.md](RECOVERY.md). No acreditan **una partida completa**.

## 1. Estado activo e integración de reglas — bloqueante

- [ ] **EST-01** Completar la activación de una partida: reinicios, jugador local, opciones y perfiles de normalización originales.
  - [x] **EST-01a** Perfil offline 0x26..0x120: jugador/nombre explícitos, dificultad, opciones de campaña, conversión de humanos a IA y reinicios conocidos. Integrado en `normalizeLoad`, sin ejecutar IA.
  - [ ] **EST-01b** Completar IA/ministros, transitorios/temporizadores, mundo cambiado y conversiones de versiones 35..37. No existe aún una etapa `Active`.
- [ ] **EST-02** Reconstruir continentes, caminos, santuarios, contactos, visibilidad y datos derivados al cargar.
  - [x] **EST-02a** Continentes, caminos de tiles, contadores de ciudades/santuarios y avisos semánticos originales, sin globales ni RNG.
  - [ ] **EST-02b** Visibilidad, contactos, población conocida, caches de edificios y demás postprocesamiento de movimiento/carga.
- [x] **EST-03** Reconstruir tareas, equilibrar trabajadores y aplicar topes de almacén como normalización explícita (`State::normalizeLabor`), también integrada en la secuencia parcial de `normalizeLoad`. La carga completa sigue en EST-01/02.
- [ ] **EST-04** Implementar creación/destrucción de edificios y unidades, listas libres/activas, límites y referencias estables durante la simulación.
  - [x] **EST-04a** Handles estables y rechazo de referencias retiradas, ajenas o de una preparación anterior, incluso tras reutilizar slots/IDs.
  - [x] **EST-04b** Backend estructural de inserción/retirada para registros simples explícitos, validación de listas, reserva de capacidad y rechazo de dependencias; sin efectos de gameplay ni exportación SAV.
  - [ ] **EST-04c** Inicialización real, IDs de partida y efectos completos de construcción/bajas: huellas, transporte, empleos, IA, costes, eventos y casos especiales.
  - [x] **EST-04d** Reconstruir enlaces de edificios y vínculos de trabajos/unidades durante la carga parcial, preservando las identidades existentes y publicando el grafo transaccionalmente.
- [ ] **EST-05** Integrar un estado RNG de partida: semillas, orden de consumo y restauración/inicialización conforme al original.
  - [x] **EST-05a** RNG propietario de sesión con primitivas originales, orden/contadores, snapshots y reseed final offline desde `options.gameId`; no altera RNG global ni la copia archival.
  - [ ] **EST-05b** Conectar y verificar el orden real de consumo en producción, combate, IA, guardado jugable y otras fases aún pendientes. No inventar reseed offline por turno.
- [x] **EST-06** Unificar tablas y contratos heredados: fuente canónica `data::*`, adaptadores de economía, 43 campañas y helpers compartidos. Contrastes de tablas con el EXE y cabeceras compiladas juntas; no implica implementar las funciones de gameplay declaradas.
- [ ] **EST-07** Conectar efectos reales entre módulos, sustituyendo los callbacks ausentes necesarios; no aceptar operaciones vacías como éxito.
  - [x] **EST-07a** Conexión directa del subconjunto de carga implementado y rechazo explícito de `Complete`; se eliminan asignaciones a fallbacks inexistentes en `turn_api.h`.
  - [ ] **EST-07b** Conectar el resto de efectos reales de gameplay. Los callbacks opcionales del cargador/edificios heredados excluidos siguen sin habilitarse; no son una ruta jugable alternativa.
- [x] **EST-08** Transacciones en las rutas propietarias implementadas: errores conservan documento, grafo, identidades, RNG e informe. Separación `Prepared`/`LoadNormalized`; la normalización parcial no puede capturarse como SAV reanudable ni avanzar turno. Una futura etapa jugable requiere cerrar EST-01/02/07.

Cierre: cargar una muestra deja una sesión coherente y utilizable por la lógica,
sin depender de punteros del EXE, de globales ajenos ni de reparaciones silenciosas.

## 2. Economía, población y logística — parcial, bloqueante

- [ ] **ECO-01** Completar asignación/reasignación de trabajadores y su conexión a órdenes e interfaz. Reconstrucción y balance automático ya implementados en EST-03; las órdenes manuales y la integración jugable siguen pendientes.
- [ ] **ECO-02** Integrar la recaudación ya calculada con niveles fiscales y efectos sobre la moral.
- [ ] **ECO-03** Aplicar el primer pase de producción: recursos, créditos, cultura, investigación, clonación, entrenamiento, curación y arte con RNG.
- [ ] **ECO-04** Registrar necesidades/reservas y realizar importaciones entre territorios, con conectividad, transportes, costes y transferencias parciales.
- [ ] **ECO-05** Consumir comida para población y unidades; resolver abastecimiento, déficit, indicadores y consecuencias de hambre.
- [ ] **ECO-06** Integrar el consumo de energía ya aislado en su lugar real del turno, con sus eventos y consecuencias.
- [ ] **ECO-07** Aplicar mantenimiento y costes de edificios/unidades, incluida la respuesta original a fondos insuficientes.
- [ ] **ECO-08** Aplicar el segundo pase: conversiones industriales y obtención/pago de insumos, sin duplicar recursos.
- [ ] **ECO-09** Implementar crecimiento, capacidad de vivienda, traslado de población y restricciones de empleo.
- [ ] **ECO-10** Calcular moral completa: impuestos, ocupación, hambre, hacinamiento, energía, policía, cultura, arte y hospitales.
- [ ] **ECO-11** Aplicar disturbios, revueltas y cambios de control con sus efectos sobre población, edificios y trabajo.
- [ ] **ECO-12** Conectar el asistente de colonia y los informes económicos a las reglas reales de producción/logística.
- [ ] **ECO-13** Ejecutar la secuencia económica completa con sus reinicios temporales y balance final, sin reutilizar saldos de otro turno.

Orden que debe preservarse: reinicios → impuestos → producción 1 → necesidades
→ importaciones → comida → energía → mantenimiento → producción 2 → costes de
edificios → población → moral → investigación → revueltas → balance final.

Cierre: varios turnos producen cambios explicables en recursos, población y
créditos; los déficits tienen efectos reales. Sumar los outputs del laboratorio
actual no satisface este bloque.

## 3. Construcción y fabricación — parcial, bloqueante

- [ ] **CON-01** Integrar o adaptar el trabajo recuperado de `buildings.cpp`, actualmente fuera de la compilación, sobre los contratos definitivos.
- [ ] **CON-02** Validar emplazamiento, huella, terreno, propiedad, tecnología y recursos antes de construir.
  - [x] **CON-02a** Consulta pura `0044d600`: huella 1×1/2×2/5×5, casillas, terreno, duplicados, mar adyacente y plataformas, con precedencia original de motivos.
  - [ ] **CON-02b** Completar propiedad, tecnología, población, fondos/materiales y logística; conectar todas las comprobaciones a la orden real.
- [ ] **CON-03** Iniciar, avanzar y finalizar construcciones y mejoras, pagando sus costes y actualizando tareas/capacidad.
- [ ] **CON-04** Resolver activación/desactivación, demolición, daños y reparación según las reglas de cada edificio.
- [ ] **CON-05** Conectar las cinco colas de fabricación: añadir, ordenar/cancelar según permita el original, progresar y producir unidades reales.
- [ ] **CON-06** Aplicar carreteras, vías mejoradas, puertos, instalaciones marinas y demás infraestructuras especiales con sus restricciones.
- [ ] **CON-07** Verificar todos los tipos construibles y unidades fabricables, no sólo los presentes en el tutorial.

Cierre: el jugador puede dar órdenes de construcción/fabricación y recibir el
resultado correcto tras los turnos necesarios, incluido un guardado intermedio.

## 4. Unidades, movimiento y exploración — pendiente

- [ ] **MOV-01** Implementar órdenes, puntos de movimiento, posturas, misiones y límites de unidades.
- [ ] **MOV-02** Calcular rutas y accesibilidad por terreno, dominio de unidad, propietario y pactos.
- [ ] **MOV-03** Ejecutar movimientos, actualizar listas/posiciones y resolver ocupación, conquista o abandono de territorios.
- [ ] **MOV-04** Implementar carga/descarga de transportes, capacidad, movimiento de pasajeros y comportamiento al perder el transporte.
- [ ] **MOV-05** Resolver exploración, descubrimientos, santuarios, escaneo y contactos entre jugadores.
- [ ] **MOV-06** Actualizar niebla de guerra y última información conocida; impedir que reglas/UI revelen datos no visibles al jugador.
- [ ] **MOV-07** Implementar misiones especiales: patrulla, colonización/plataformas, camuflaje/búsqueda, minado/desminado, sabotaje y transferencia racial, además de efectos marítimos, en sus fases correctas.
- [ ] **MOV-08** Completar el postprocesamiento de movimiento: control territorial, límites, visibilidad, caches y balance necesarios.

Cierre: las órdenes terrestres, navales y aéreas legales se ejecutan; las ilegales
se rechazan con una explicación; la información visible coincide con el estado.

## 5. Combate completo — pendiente

- [ ] **COM-01** Implementar estadísticas efectivas: raza, tecnología, experiencia, postura, terreno y estado de abastecimiento.
- [ ] **COM-02** Resolver selección de objetivos, alcance, movimiento/disparo, impactos y daño con el orden y RNG originales.
- [ ] **COM-03** Cubrir combates terrestres, navales y aéreos, defensas y enfrentamientos contra edificios/santuarios.
- [ ] **COM-04** Implementar ataques especiales, misiles, armas nucleares y minas, con restricciones y efectos asociados.
- [ ] **COM-05** Aplicar retirada, evasión, bajas, destrucción, daño a edificios/población y consecuencias territoriales.
- [ ] **COM-06** Resolver experiencia, entrenamiento, curación/reparación y limpieza de referencias tras bajas.
- [ ] **COM-07** Integrar el visor y los informes de combate; su reproducción no puede cambiar ni repetir el resultado de la simulación.
- [ ] **COM-08** Comparar casos representativos y extremos con evidencia del original, no sólo comprobar que no se bloquea.

Cierre: combates reproducibles dejan resultados correctos y persistentes; todas
las clases y acciones disponibles tienen una ruta funcional.

## 6. Investigación, diplomacia, comercio y espionaje — pendiente

- [ ] **SIS-01** Completar investigación: selección, prerrequisitos, progreso, descubrimiento y elección automática cuando corresponda.
- [ ] **SIS-02** Aplicar efectos tecnológicos y raciales a todos los sistemas, incluidas restricciones de campaña.
- [ ] **SIS-03** Implementar relaciones, propuestas, aceptación/rechazo, pactos, ruptura y vencimiento, con efectos sobre acceso y hostilidad.
- [ ] **SIS-04** Ejecutar comercio, intercambios y transferencias permitidos por el original, con pagos, límites, entrega y notificaciones.
- [ ] **SIS-05** Integrar el mercado Skirineen: disponibilidad, operaciones, costes, renovaciones y consecuencias.
- [ ] **SIS-06** Implementar espionaje y contraespionaje: asignaciones, misiones, costes, detección, resultados y repercusiones.
- [ ] **SIS-07** Implementar eventos del juego: generación cuando corresponda, duración, efectos, destinatarios y registro legible.
- [ ] **SIS-08** Conectar los eventos con reacciones de IA y actualizaciones de interfaz; una solicitud semántica de evento no basta.

Cierre: cada acción accesible tiene un efecto real, un resultado comprensible y
persistencia correcta; no hay pantallas que sólo simulen aceptar la orden.

## 7. Inteligencia artificial y automatización — pendiente

- [ ] **IA-01** Inicializar, cargar, actualizar y liberar estado de IA, ministros y trabajos pendientes.
- [ ] **IA-02** Implementar decisiones de economía, trabajo, construcción, producción e investigación.
- [ ] **IA-03** Implementar exploración, expansión, transporte y logística militar.
- [ ] **IA-04** Completar fuerzas de tarea, asignación de unidades, objetivos y ejecución de misiones ofensivas/defensivas.
- [ ] **IA-05** Completar diplomacia, comercio, espionaje y respuestas a eventos/acciones del jugador.
- [ ] **IA-06** Aplicar personalidad/modificadores raciales, dificultad y reglas especiales de escenarios, según evidencia original.
- [ ] **IA-07** Integrar el turno IA y su postprocesamiento, con terminación garantizada y sin consultar información prohibida por sus reglas.
- [ ] **IA-08** Verificar asistentes/ministros configurables por el humano y continuidad de sus trabajos tras guardar/cargar.

Cierre: adversarios funcionales juegan hasta victoria/derrota sin atascar el
turno; cambiar dificultad o raza no rompe decisiones ni objetivos de campaña.

## 8. Coordinador del turno individual — bloqueante

- [ ] **TUR-01** Establecer una única secuencia original de fases, documentando el orden y las dependencias.
- [ ] **TUR-02** Conectar órdenes humanas y de IA por una ruta local validada, sin requerir conexiones de red.
- [ ] **TUR-03** Integrar preparación, decisiones IA, pactos, llegadas de campaña, misiones, economía, movimiento/combate y postprocesamiento.
- [ ] **TUR-04** Situar eventos, transferencias, limpieza, ordenación, estadísticas y reconstrucciones en el punto correcto de esa secuencia.
- [ ] **TUR-05** Evaluar final de partida y actualizar el número de turno sólo al completar todas las fases necesarias.
- [ ] **TUR-06** Evitar doble aplicación de fases/órdenes y definir recuperación segura ante fallos; no publicar estados parciales como guardados válidos.
- [ ] **TUR-07** Habilitar `State::advanceTurn` y la acción gráfica de fin de turno con una ejecución real y determinista.

Cierre: mismo estado, órdenes y semillas producen el mismo resultado; cargar →
jugar turno → guardar → recargar conserva ese resultado. Hoy `advanceTurn`
rechaza explícitamente la operación; impuestos y energía no se pueden encadenar.

## 9. Nueva partida y ciclo de aplicación — pendiente

- [ ] **INI-01** Menú principal funcional: nueva partida, cargar, campaña, tutorial, editor, preferencias y salir.
- [ ] **INI-02** Selección de raza, nombre, adversarios, dificultad y opciones de mundo/condición de victoria.
- [ ] **INI-03** Generación de mapas: terreno, territorios, continentes, recursos, adyacencias y santuarios coherentes.
- [ ] **INI-04** Carga de mapas/escenarios personalizados y validación de su aptitud para iniciar una partida.
- [ ] **INI-05** Elección de aterrizaje humana e IA, restricciones de sitio, orden y asignación de recursos/edificios/unidades iniciales.
- [ ] **INI-06** Reiniciar o volver al menú e iniciar otra partida sin conservar estado, preferencias temporales o referencias de la anterior.

Cierre: desde la aplicación recién abierta se inicia una partida individual
válida sin comandos de desarrollo ni un SAV prefabricado obligatorio.

## 10. Tutorial, campañas y final de partida — pendiente

- [ ] **CAM-01** Tutorial jugable: instrucciones/consejos de Oolan, acciones, avance, repetición y salida, no sólo visualizar `TUTORIAL.SAV`.
- [ ] **CAM-02** Selección y arranque de campañas por raza; introducciones y objetivos del capítulo.
- [ ] **CAM-03** Aplicar restricciones, objetivos, límites temporales, territorios/recursos requeridos y condiciones especiales.
- [ ] **CAM-04** Incorporar llegadas de jugadores, refuerzos y cambios de escenario en los turnos previstos.
- [ ] **CAM-05** Resolver victoria/derrota, continuación al capítulo siguiente y persistencia del progreso.
- [ ] **CAM-06** Completar Manifest Destiny, Conquest y Shrine Wars: ciudades, eliminación, santuarios, turnos de mantenimiento, alianzas de victoria y contadores configurables.
- [ ] **CAM-07** Mostrar estadísticas, puntuaciones, resultados finales y récords, incluida su persistencia equivalente a `hiscore.dat`.
- [ ] **CAM-08** Verificar los 42 escenarios disponibles y todas las rutas de campaña; abrir sus archivos no acredita que se puedan completar.

Cierre: se puede terminar una partida libre y avanzar/finalizar las campañas
sin herramientas externas, incluidos desenlaces de derrota y reanudación.

## 11. Interfaz jugable y representación del mundo — parcial

- [ ] **UI-01** Implementar el mapa estratégico y la vista isométrica de asentamiento: terreno, capas, edificios, unidades y elementos superpuestos.
- [ ] **UI-02** Integrar animaciones y estados de sprites; completar los comportamientos de scripts requeridos por el juego.
- [ ] **UI-03** Conectar selección, cámara, minimapa, cursores, indicadores y niebla de guerra al jugador activo.
- [ ] **UI-04** Convertir el panel principal en controles reales: información, órdenes, selección de territorio/unidades y fin de turno.
- [ ] **UI-05** Completar pantallas de edificios, trabajo, fabricación, recursos, población y asistente de colonia.
- [ ] **UI-06** Completar pantallas de unidades, transporte, misiones, combate e informes.
- [ ] **UI-07** Completar pantallas de investigación, diplomacia, comercio, mercado, espionaje y ministros.
- [ ] **UI-08** Completar registro de eventos, mensajes, avisos, objetivos, estadísticas y confirmaciones.
- [ ] **UI-09** Integrar navegación de teclado/ratón, atajos, foco/modalidad y ayuda contextual; no perder ni duplicar acciones al cambiar de pantalla.
- [ ] **UI-10** Validar lectura de textos, paletas, orden de dibujo, escalado y coordenadas de entrada en los modos de pantalla soportados.
- [ ] **UI-11** Mostrar progreso/errores y mantener una salida controlada durante cargas, IA y resolución de turnos.

Cierre: todas las operaciones individuales se pueden realizar desde la interfaz.
El inspector rectangular actual y la demostración de SMenu no cumplen este cierre.

## 12. Guardado de partidas jugadas y preferencias — parcial

- [ ] **SAV-01** Capturar todo el estado persistente de una sesión jugable, no sólo conservar el documento de entrada.
- [ ] **SAV-02** Guardar/cargar después de construcción, combate, investigación, cambios de propietario y decisiones IA sin perder efectos.
- [ ] **SAV-03** Implementar autosave y copias de seguridad en los puntos correctos del flujo.
- [ ] **SAV-04** Integrar selección de archivos, nombres y directorios de partidas, campañas, escenarios y mapas.
- [ ] **SAV-05** Publicar guardados de forma segura; ante error de escritura conservar la partida anterior y evitar archivos truncados aceptados como válidos.
- [ ] **SAV-06** Verificar que guardados producidos por la simulación se abren correctamente en el original dentro de la compatibilidad declarada.
- [ ] **SAV-07** Clasificar y probar versiones/modos especiales; obtener muestras faltantes o documentar explícitamente lo no soportado/no verificado.
- [ ] **SAV-08** Cargar, aplicar y guardar preferencias equivalentes a `DL2.PRF`: nombre, sonido/música y volúmenes, vídeo/subtítulos, animaciones, detalle, ayuda emergente y opciones predeterminadas.

Cierre: cerrar y reabrir la aplicación permite continuar la misma partida y
mantiene preferencias; una operación fallida no destruye guardados existentes.

## 13. Sonido, música y cinemáticas — infraestructura parcial

- [ ] **AV-01** Vincular efectos a acciones reales, combate, avisos y elementos de interfaz, con mezcla y volúmenes correctos.
- [ ] **AV-02** Reproducir música y sus cambios entre menús, partida y demás estados relevantes.
- [ ] **AV-03** Integrar voces/mensajes y sus recursos según jugador/raza/contexto.
- [ ] **AV-04** Implementar cinemáticas y cabezas parlantes originales, incluidas las que requieren Smacker, con audio sincronizado, subtítulos y controles de reproducción/omisión.
- [ ] **AV-05** Validar apertura/cierre y cambios de pantalla sin sonidos colgados, bloqueos ni recursos retenidos; permitir jugar sin dispositivo de audio.
- [ ] **AV-06** Determinar qué pantallas offline usan celdas CY3D, omitidas por el lector actual, e implementar los usos necesarios; documentar si no son requeridas.

Cierre: la presentación audiovisual acompaña al flujo real. Reproducir un WAVE
en la demostración no acredita música, voces o cinemáticas integradas.

## 14. Editor y funciones offline restantes — pendiente

- [ ] **EDI-01** Abrir/crear mapas y escenarios desde el editor con sus opciones originales.
- [ ] **EDI-02** Editar terreno, territorios, recursos y santuarios con reconstrucción de adyacencias/datos derivados.
- [ ] **EDI-03** Editar jugadores, ubicaciones, edificios, unidades y demás propiedades expuestas por el editor original.
- [ ] **EDI-04** Guardar/reabrir mapas y escenarios y utilizarlos en partidas individuales sin perder cambios ni producir estados incoherentes.
- [ ] **EDI-05** Completar ayuda y pantallas offline restantes mediante inventario de menús/diálogos; separar herramientas internas de depuración de funciones de usuario.
- [ ] **EDI-06** Inventariar atajos especiales y trucos originales de usuario y documentar su compatibilidad; no confundirlos con comandos internos de diagnóstico.

Cierre: un escenario creado o modificado desde el editor puede guardarse,
reabrirse y jugarse. El editor no bloquea el primer prototipo jugable, pero sí el
cierre de todas las funciones offline definido aquí.

## 15. Validación, estabilidad y entrega — transversal

- [ ] **QA-01** Mantener una matriz de reglas/acciones/pantallas originales, implementación, evidencia y prueba; revisar funciones aún desconocidas relevantes.
- [ ] **QA-02** Ampliar pruebas unitarias de aritmética, límites, referencias, pools, colas y efectos de cada nueva fase.
- [ ] **QA-03** Comparar estados/resultados representativos con el original; distinguir mediciones originales, oráculos derivados y simple determinismo del port.
- [ ] **QA-04** Automatizar recorridos de integración: nueva partida, carga, órdenes, turnos, combate, guardado/reanudación y final.
- [ ] **QA-05** Cubrir todas las razas, dificultades, tamaños/opciones de mundo y clases de victoria mediante una matriz explícita de casos.
- [ ] **QA-06** Cubrir todos los tipos de edificio, unidad, tecnología y misión, además del tutorial y los 42 escenarios de campaña.
- [ ] **QA-07** Ejecutar partidas prolongadas y pruebas de estrés con muchas entidades; comprobar memoria, tiempos de turno y ausencia de bloqueos IA.
- [ ] **QA-08** Probar entradas inválidas, archivos truncados, rutas sin permiso, recursos faltantes y fallos de guardado con recuperación controlada.
- [ ] **QA-09** Ejecutar las suites completas en compilaciones normales y con comprobación de memoria; comparar escenas/transiciones con el original y revisar audio audible del flujo real.
- [ ] **QA-10** Preparar una distribución Windows reproducible con dependencias, selección de datos originales y directorios de usuario escribibles; comprobarla fuera del árbol de desarrollo.
- [ ] **QA-11** Mantener los datos originales de la instalación sin modificaciones y sin redistribuirlos inadvertidamente con el port.
- [ ] **QA-12** Documentar instalación, controles, compatibilidad y diferencias deliberadas; no ocultar fallos críticos tras limitaciones genéricas.

Cierre: no quedan bloqueos de partida ni acciones originales individuales
anunciadas como soportadas que estén sin implementar; las excepciones son
explícitas y compatibles con el alcance acordado.

## Orden recomendado de implementación

1. Cerrar gestión de entidades y los perfiles de carga restantes. El refresco
   de tareas, balance de trabajadores y topes de almacén ya tienen implementación
   explícita verificada; aún no deben confundirse con activar toda la partida.
2. Completar construcción, fabricación, logística y la secuencia económica.
3. Integrar órdenes, movimiento, combate, investigación, eventos y turnos IA
   hasta obtener una partida cargada jugable. Construir su interfaz mínima en
   paralelo con cada sistema, no dejar toda la UI para el final.
4. Cerrar el ciclo completo: nueva partida, victoria/derrota, guardado/reanudación,
   diplomacia/espionaje y todas las reglas aún no usadas por ese primer recorrido.
5. Completar tutorial y todas las campañas, interfaz/presentación restantes,
   preferencias, editor y compatibilidad declarada.
6. Ejecutar la matriz de aceptación completa y preparar la distribución.

Las pruebas acompañan cada paso. Este orden no convierte lo posterior en
opcional: una partida básica terminable es un hito intermedio, no el 100% offline.

## Prueba final de aceptación

- [ ] **FIN-01** Instalar/abrir el port con los datos originales, sin herramientas de desarrollo, y configurar preferencias.
- [ ] **FIN-02** Jugar el tutorial y una partida nueva contra IA hasta victoria o derrota.
- [ ] **FIN-03** Guardar, cerrar, reabrir y continuar antes/después de turnos con construcción, combate e investigación.
- [ ] **FIN-04** Completar la matriz de campañas y modalidades individuales, comprobando objetivos y progresión.
- [ ] **FIN-05** Crear/editar un escenario, guardarlo y jugarlo.
- [ ] **FIN-06** Confirmar funcionamiento de todas las pantallas, ayuda, audio, música y cinemáticas incluidas en el alcance.
- [ ] **FIN-07** Cerrar incidencias bloqueantes y revisar diferencias conocidas frente al original; no hay fases omitidas ni éxitos ficticios.

## Evidencia utilizada y límites de la auditoría

- [README](../README.md) y [ROADMAP](ROADMAP.md): estado público y criterios por hito.
- [GAME_INTEGRATION](GAME_INTEGRATION.md): dependencias, fuentes excluidas y discrepancias heredadas.
- [RUNTIME_STATE](RUNTIME_STATE.md), [SAVE_CODEC](SAVE_CODEC.md) y [ECONOMY_LAB](ECONOMY_LAB.md): contratos implementados y límites comprobados.
- [WORLD_INSPECTOR](WORLD_INSPECTOR.md), [ENGINE_API](ENGINE_API.md), [SPRITES](SPRITES.md) y [ARCHITECTURE](ARCHITECTURE.md): presentación disponible e inventario original.
- [CMake de lógica](../src/game/CMakeLists.txt), [CMake de aplicación](../src/CMakeLists.txt) y [pruebas](../tests/CMakeLists.txt): qué está realmente integrado.
- [economy.h](../src/game/economy.h), [turn_api.h](../src/game/turn_api.h), [newgame.h](../src/game/newgame.h), [campaign_flow.h](../src/game/campaign_flow.h) y cabeceras IA: inventario pendiente, no prueba de implementación.
- [RECOVERY](RECOVERY.md): origen del trabajo y resultados de verificaciones anteriores.

La revisión inicial sólo produjo documentación. El lote posterior de trabajo
laboral sí compiló y ejecutó las 21 pruebas en ambos builds. No ejecutó una
partida completa del port: todavía no existe esa capacidad.
Los nombres/comentarios heredados pueden ser incorrectos; cada implementación
debe confirmarse con evidencia y pruebas antes de cerrar su casilla.
Por ejemplo, algunas cabeceras citan tests, fallbacks o documentos todavía
inexistentes. También hay recursos de diálogos heredados/de depuración: su mera
presencia no convierte cada recurso en una pantalla exigible para el modo individual.
No se exige reproducir servicios retirados de red ni las comprobaciones históricas
del CD para cerrar la experiencia individual con los datos de la instalación local.
