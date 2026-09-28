# Inspector gráfico de partidas

La aplicación abre documentos de guardado en una vista del mundo de sólo lectura.
Es un hito de inspección: permite recorrer territorios, consultar edificios y
unidades, ver sus sprites originales y guardar una copia sin modificar la partida.
**No activa la simulación ni permite jugar turnos.**

## Arranque

La instalación de datos se obtiene del argumento posicional, de `DL2_DATA` o, como
última opción, de `C:\GOG Games\Deadlock 2`. Los recursos originales se leen sin
modificarlos. El inspector usa fuentes de `deadtext.cam` y sprites de `SPRITENW.DAT`.

```powershell
# Sin selección explícita se abre TUTORIAL.SAV dentro de la instalación.
.\build\src\deadlock2.exe "C:\GOG Games\Deadlock 2"

# Abrir un SAV, CPN o documento de mapa compatible.
.\build\src\deadlock2.exe "C:\GOG Games\Deadlock 2" --load "C:\ruta\partida.sav"

# Leer un escenario directamente de LEVELS.HDX + LEVELS.HDD.
.\build\src\deadlock2.exe "C:\GOG Games\Deadlock 2" --scenario CHCHT1
```

`--load` y `--scenario` son excluyentes. El nombre del escenario es la entrada
exacta, sensible a mayúsculas, del archivo `LEVELS`; no es un nombre de archivo.
También se puede arrastrar un archivo a la ventana. Las rutas recibidas por SDL
se interpretan como UTF-8, incluidos nombres de archivo no ASCII. La interfaz
usa texto ASCII y sustituye caracteres no representables, pero no cambia los
bytes almacenados en el documento.

Al cargar se selecciona el territorio de origen del jugador local, si existe;
en su defecto, el primero con objetos, o el territorio 1. Si contiene objetos,
se selecciona primero un edificio y después las unidades, en orden de archivo.
Un fallo al cargar o recargar conserva el documento anterior, su fuente,
selección y cámara, y muestra el error. Si falla la primera carga interactiva,
la ventana permanece disponible para soltar otro archivo.

## Controles

| Acción | Control |
|---|---|
| Seleccionar tile y territorio; mostrar su primer objeto | Clic izquierdo en el mapa |
| Seleccionar un objeto de la página visible | Clic en su fila debajo del mapa |
| Objeto siguiente / anterior del territorio | `Tab` / `Shift+Tab`, o `Obj >` / `< Obj` |
| Territorio anterior / siguiente | `[` / `]`, o `< T` / `T >` |
| Acercar / alejar | Rueda sobre el mapa, `+` / `-` |
| Desplazar la vista | Flechas |
| Ajustar y centrar el mundo | `F` o `Fit` |
| Alternar colores por terreno / propietario | `O` o `Owners` |
| Recargar la misma fuente original | `R` o `Reload` |
| Guardar una copia nueva sin cambios | `F5` o `Save copy` |
| Cerrar | `Escape` o cierre de ventana |

La rueda mantiene el punto de zoom bajo el cursor. Los límites de cámara impiden
perder el mapa; cuando cabe completo se mantiene centrado. El listado presenta
cuatro objetos por página y cambia de página al recorrerlos. Al recargar con
éxito se restablecen la selección inicial y el encuadre.

## Guardado seguro

`F5` crea `saves/inspection-copy-N.sav` **junto al ejecutable**, buscando el primer
número libre del 1 al 10000. Por ejemplo, con el build habitual:

```text
C:\Games\DL2\build\src\saves\inspection-copy-1.sav
```

La copia contiene el documento cargado, sin cambios de economía, turnos ni
normalizaciones. La fuente de la sesión sigue siendo el archivo original o la
entrada de `LEVELS`; `R` no pasa a leer la copia. No se sobrescriben destinos
existentes, ni siquiera ante una colisión entre comprobación y escritura.

La escritura compartida de `save_files.cpp` codifica primero, prepara un archivo
completo vecino y lo publica exclusivamente mediante un enlace duro. Requiere
un sistema de archivos que soporte esa operación y permisos para crear archivos
junto al ejecutable. Si no puede guardar, informa del fallo y conserva la sesión;
no existe una alternativa que sobrescriba archivos. La publicación atómica no es
una garantía de durabilidad frente a un corte eléctrico.

## Qué representa la vista

- Es un plano rectangular coloreado por el terreno **del territorio**, no una
  reconstrucción del renderizado isométrico original. `Tile::terrain` tiene una
  enumeración gráfica distinta y no se interpreta como el nombre del terreno.
- Los bordes separan territorios. El contorno dorado señala el territorio elegido
  y el blanco, el tile seleccionado.
- Los marcadores son agregados por territorio: cuadrado para edificios y línea
  para unidades. No indican posiciones exactas de objetos dentro de un tile ni
  inventan coordenadas a partir de las casillas de construcción.
- Las unidades se agrupan, seleccionan y marcan por el territorio actual
  (+0x3C, alias físico `Army::dest`), mostrado como `At`. `Start` es el territorio
  al inicio del turno (+0x38, alias `territory`), no un destino pendiente. Una
  unidad que se movió no aparece también en su territorio inicial.
- En unidades, `Moves` es el movimiento restante (+0x0A, alias `strength`) y
  `Retreat` es el umbral de retirada (+0x26, alias `health`), no la salud.
  El campo físico `moves` (+0x24) representa órdenes de combate.
- El panel consulta población, moral, comida, energía, cantidades y atributos
  del objeto directamente del archivo. No calcula producción ni resultados de
  turno. Los mapas reducidos no muestran economía que no contienen.
- Las previsualizaciones son frames estáticos de `SPRITENW.DAT`, no animaciones
  de combate o movimiento. Un recurso sin correspondencia muestra un aviso.
- Todos los datos del archivo son visibles. No se aplica niebla de guerra,
  conocimiento del jugador ni reglas de visibilidad del juego.

## Pruebas automáticas y capturas

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File tools/build.ps1 -Test

# Arranque limitado; se captura el último frame al salir.
.\build\src\deadlock2.exe "C:\GOG Games\Deadlock 2" --smoke-frames 3 --screenshot build/inspector-new.bmp
```

`--smoke-frames N` acepta de 1 a 10000 frames y evita diálogos bloqueantes de
errores de arranque. `--screenshot` sólo admite un destino BMP nuevo y escribible;
no sobrescribe una captura anterior. Su directorio padre debe existir. Sin un
límite de frames, la captura se guarda al cerrar normalmente el inspector.

La demostración previa de imágenes, audio y panel SMenu `D000` se conserva
explícitamente como otro modo:

```powershell
.\build\src\deadlock2.exe "C:\GOG Games\Deadlock 2" --demo --smoke-frames 3
```

`--demo` no admite `--load`, `--scenario` ni `--screenshot`. Sus flechas siguen
cambiando imágenes y espacio reproduce el sonido de prueba: no son los controles
del inspector.

Las pruebas nuevas separan `world_view` (cámara, selección y ausencia de cambios
en los bytes), `inspector_session` (carga transaccional, archivos y copias),
`save_files` (I/O compartido), `input` (entrada SDL) y `world_inspector` (vista y
recursos). Los smoke tests distinguen demo, tutorial y escenario. Las pruebas
con datos originales necesitan la instalación indicada por `DL2_DATA_DIR`; las
de modelo y sesión construyen documentos sintéticos. El resultado de la ejecución
integrada se registra en [RECOVERY.md](RECOVERY.md).
Las regresiones de unidades usan campos asimétricos y, si está disponible,
Army 8204 de `Campaign/ChCht001.CPN`: inicio 15, actual 4, ancla de ruta 15.

## Separación de responsabilidades y siguiente hito

`game/world_view.*` sólo conserva IDs, coordenadas y cámara; recibe un
`const save::Document&` por operación. No retiene punteros a vectores que puedan
realojarse. `app/inspector_session.*` posee el documento y cambia de fuente sólo
cuando una carga completa tiene éxito. `app/world_inspector.*` dibuja y procesa
acciones; `app/inspector_main.cpp` conecta SDL, archivos soltados y las copias.
Ni la selección ni el renderizado interpretan los `Ptr32` guardados como
direcciones nativas o handles de `globals.h`.

El siguiente hito es convertir el documento validado a un estado de ejecución
propietario, de forma transaccional, y completar un turno local determinista.
Siguen pendientes la reconstrucción real de listas/pools y postprocesamiento,
economía, movimiento, combate, IA/campañas y la UI necesaria para operarlos.
Véanse [SAVE_CODEC.md](SAVE_CODEC.md), [GAME_INTEGRATION.md](GAME_INTEGRATION.md)
y [ROADMAP.md](ROADMAP.md).
