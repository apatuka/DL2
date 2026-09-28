# Motor CYLib: API y alcance del port

Estado revisado el 2026-09-27. La biblioteca `dl2engine` agrupa los lectores de archivos,
la plataforma SDL2 y el port de CYLib. La lógica de `src/game` debe acceder a la UI
mediante `hooks`; no debe depender directamente de SDL ni del motor. Las direcciones
originales se conservan en comentarios de los headers y se contrastan con `re/decomp`.

## Arranque y ciclo de vida

`engine::CyGame::instance()` es la fachada. `init(640, 480, 16, video, audio)` crea una
superficie RGB555, instala el destino de dibujo y conecta opcionalmente la presentación
y el mezclador. Ambos punteros pueden ser nulos: así funcionan las pruebas sin ventana
ni dispositivo de audio. En modo interactivo, la aplicación inicializa SDL y mantiene
vivos `Video` y `Audio` mientras los utilice `CyGame`.

`openLibraries(dataDir, &error)` intenta abrir, por orden, `deadcyb.cam`, `deadtext.cam`,
`dl2sound.cam`, `dl2music.cam`, `dl2segue.cam`, `deadanim.cam` y `deadcine.cam`. Devuelve
el número de aperturas exitosas; las bibliotecas ausentes son opcionales y `error`
puede describir una ausencia aunque se hayan abierto las necesarias. Para una pantalla
SMenu se requieren en concreto `deadcyb.cam` y `deadtext.cam`: compruébense con
`resources().findLibrary(...)`, además del contador.

Por frame: obtener `InputState`, llamar `feedInput`, procesar los menús, actualizar
`SoundSystem`, dibujar en `screen()` y llamar `present()`. `shutdown()` detiene sonidos
y desconecta la presentación. Las CAM y la caché de recursos son globales y no se
cierran automáticamente con `shutdown()`.

## Superficies, colores y dibujo

| Componente | Contrato principal |
| --- | --- |
| `Rect` | Coordenadas `{x0,y0,x1,y1}`; extremos derecho e inferior exclusivos. |
| `OffPort` | Buffer de 8 bits indexado o 16 bits RGB555/RGB565; pitch alineado a 4 bytes. |
| `ColorTable` | Paleta CYLib, conversión 555/565 y búsqueda de color por distancia ponderada. |
| `Pixel` | Destino, clip, modo de blit, rellenos, líneas y tablas de sombra/mezcla globales. |
| `TileView` | Vista no propietaria del payload TILE; tipos lineales y por runs. |
| `ImagView` | Vistas de capas/celdas de un IMAG que referencian índices TILE. |
| `Text` / `FontView` | Fuente bitmap, medición, ajuste de línea, dibujo y posición del cursor. |

`ColorRef` sin bits altos es un color nativo del destino. `colorRgb(r,g,b)` fija el
bit 31 y solicita conversión; el bit 30 expresa un color no definido/heredado en SMenu.
Un índice de paleta no equivale automáticamente a su RGB sobre un `OffPort` de 16 bits.

Antes de dibujar directamente se fija `Pixel::setPort(&port)`, `Pixel::resetClip()` y
`Pixel::setBlitMode(Pixel::blitModeFor(sourceBpp))`. `fillRaw` no recorta; úsese
`Pixel::fillRect` con un clip válido contenido en la superficie. Las pilas de port y
clip son independientes: cambiar el port no adapta automáticamente el clip.

`drawTile(tile, x, y, mode)` resta el hotspot del TILE y aplica el clip actual. El modo
`-1` selecciona el modo almacenado en el recurso. `drawTileTo` utiliza un destino
explícito y su rectángulo de vista. `drawImag` compone una columna de una capa; su
`TileLookup` normalmente procede de `resources().tileLookup()`.

`OffPort::blitFrom` permite copia 8→8, conversión con paleta 8→16 y copia 16→16, con
recorte y sin escalado. Sólo implementa el modo 0 para estas copias de superficies;
los demás modos pertenecen a los blitters TILE. La copia 16→16 no convierte entre
RGB555 y RGB565. `toRgb555()` sí produce una copia lineal convertida para presentar
o inspeccionar el resultado.

## Recursos y propiedad

`resources()` devuelve el `ResourceManager` global. Los handles de bibliotecas son
1-based; 0 en una búsqueda significa recorrer las bibliotecas abiertas. Un recurso
se identifica por tag (`kTagIMAG`, `kTagTILE`, etc.) y por los cuatro primeros caracteres
del nombre (`makeTag("D000")`) o el índice de una sección sin nombres.

`get` devuelve un `ResPtr` con bytes originales y vistas decodificadas. Los translators
registrados validan TILE, IMAG, FONT, PALT, STRT, SMNU y WAVE. PICT requiere los decoders
de `formats/iff_pbm.h`. `getByName` resuelve nombres de directorio; los accesos por ID
comparten la misma caché.

`kResRef` aumenta un contador explícito, distinto del `shared_ptr`. `release` baja ese
contador y retira la entrada de la caché al llegar a cero; `purge` elimina las entradas
sin referencias y sin otros propietarios. Los helpers `tile`, `imag`, `font`, `palette`
y `string` toman referencias. La política de retención de esos helpers sigue siendo
conservadora y necesita revisión antes de usar ciclos prolongados de carga/descarga.

`TileView`, `ImagView` y `FontView` contienen vistas a bytes del recurso. Manténgase vivo
el recurso propietario y su biblioteca durante su uso; conservar sólo una vista no
garantiza la vida de los bytes al cerrar la biblioteca. `closeLibrary` invalida las
futuras búsquedas y vacía sus entradas de caché. `kResStream` conserva el identificador
de API original, pero no implementa lectura de audio por bloques: los WAVE se cargan
y decodifican completos.

## SMenu

`SMenu::load(makeTag("D000"))` carga una descripción SMNU y sus recursos auxiliares.
`fromWords` permite construirla en memoria. `show()` resuelve tamaños y posiciones;
`draw()` dibuja el conjunto. Los menús quedan registrados en `SMenu::all()` hasta su
destrucción. Destruirlos antes de cerrar las bibliotecas que contienen sus recursos.

Los items incluyen botones, casillas, radio, listas, campos de texto, grids, barras
de desplazamiento y atajos. `itemById`, `sendMessage`, `setAttribute`, `setDisabled`,
`setChecked` y `setFocus` constituyen la API para el código de interfaz. Los gráficos
pueden ser IMAG, PICT o texto; un item con `kStateReturnsId` devuelve su ID al activarse.

`process(&hoverId)` consume la cola de entrada y devuelve si hay un botón mantenido.
El resultado de activación está en `result()`; el llamador lo recoge y limpia con
`clearResult()`. El código de aplicación decide qué acción del juego corresponde al
ID. Cargar/dibujar D000 no conecta por sí solo producción, mundo ni turnos.

`ItemProc`, `MenuHook` y `KeyHook` permiten personalizar mensajes, fondo/geometría y
teclado. `setSoundPlayer` conecta sonidos de interacción. `redrawDirty` compone menús
visibles sobre rectángulos invalidados; el smoke test puede optar por redibujar todo.

## Entrada y audio

`CyGame::feedInput` convierte teclas SDL a los códigos CYLib declarados en `smenu.h`
y alimenta `InputQueue`. La cola de ratón guarda hasta 20 eventos; la de teclado, 19.
Los tiempos de UI se expresan en milisegundos o ticks de 14 ms. No son el reloj de
simulación determinista de `src/game`.

`SoundSystem::load` obtiene PCM de un WAVE; `play`, `stop`, `release` y `update` gestionan
su reproducción. `playOnce` sirve para sonidos de UI y `playMusic` emplea una voz
dedicada. Sin `Audio*`, la reproducción devuelve fallo/silencio. Las pruebas de recursos
verifican decodificación de WAVE, no salida audible ni latencia del mezclador.

## Verificación y límites

`test_engine` verifica píxeles esperados de conversión/recorte, hotspot TILE, colas y
traducción de entrada, primer clic tras inicialización y pulsación de un botón SMenu
sintético. Usa comprobaciones activas también en Release.

`test_resources <directorio>` abre las CAM externas en lectura, recorre los payloads de
`deadcyb.cam` y `deadtext.cam`, decodifica PICT tipo 1/2, dibuja sus SMNU en memoria y
comprueba un WAVE, además del ciclo caché/cierre/reapertura. También acepta `DL2_DATA`;
sin ruta o si faltan las CAM originales requeridas devuelve 77 con un mensaje `SKIP`
para que CTest lo marque omitido. Esto permite ejecutar las pruebas sintéticas sin
una instalación del juego. Un recurso presente que no se puede decodificar sigue
siendo un fallo. No extrae ni escribe assets.

En la instalación local GOG, el recorrido del 2026-09-27 comprendió 2.141 payloads
(3 PALT, 52 IMAG, 1.953 TILE, 9 PICT, 60 SMNU, 59 STRT y 5 FONT), con los 9 PICT
decodificados y los 60 menús dibujados en memoria. Las regresiones detectaron y
motivaron dos correcciones: reabrir realmente una biblioteca después de cerrarla,
y distinguir un primer clic de un doble clic durante los primeros 400 ms del motor.
Tras ambas correcciones, el build `RelWithDebInfo` y los seis tests CTest de
`build-recovery` pasaron sin omisiones; esto incluye `engine`, `resources` y tres
frames de la aplicación con los drivers dummy de SDL.

Estas pruebas cubren una base de integración, no equivalencia visual completa contra
el ejecutable original. Quedan por validar exhaustivamente estados de edición,
listas, grids, scrollbars, animaciones, sombras y hotkeys con datos de partida reales.
La gestión de rectángulos sucios está simplificada y la retención de recursos exige
revisión. Los decoders presuponen principalmente assets originales conocidos; estas
pruebas no constituyen validación de archivos arbitrarios o dañados. Las celdas CY3D
y las cinemáticas Smacker tampoco están implementadas como una experiencia jugable.
