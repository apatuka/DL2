# ¿Es viable reimplementar Deadlock II sobre SDL2?

**Conclusión: sí, es viable y es la opción natural.** El motor original ("Xeno" sobre la librería
interna *CYLib* de Cyberlore) usa un modelo de presentación muy simple que SDL2 cubre por completo.

## Dependencias del ejecutable original (DEADLOCK.EXE, Borland C++ 5.x, 1998)

| Subsistema original | API usada | Equivalente SDL2 | Dificultad |
|---|---|---|---|
| Vídeo | `DirectDrawCreate` (DDRAW.dll), superficie primaria 640×480×8 bpp con paleta; fallback GDI (`CreateDIBSection`, `SetDIBColorTable`, `StretchBlt`, `RealizePalette`) — la propia CYLib abstrae esto en `offport.c`/`pixel.c` | Framebuffer de 8 bpp en memoria + paleta de 256 entradas → `SDL_Texture` streaming RGBA (o `SDL_Surface` indexada + `SDL_SetPaletteColors`). Escalado entero, ventana o pantalla completa. | Baja |
| Audio | `waveOutOpen/Write` (WINMM) y DirectSound opcional (`glsound.c`): mezcla propia de voces PCM 8/16 bits, 11 025 / 22 050 Hz | `SDL_OpenAudioDevice` + mezclador propio con `SDL_AudioStream` para conversión de tasa/formato. | Baja |
| Temporización | `timeGetTime`, `timeSetEvent` (callback periódico), `timeBeginPeriod` | `SDL_GetTicks64`, `SDL_AddTimer` o bucle de juego con delta. | Baja |
| Entrada | Mensajes `WM_*` (teclado/ratón), `GetAsyncKeyState`, `SetCursorPos`, `ShowCursor` | `SDL_PollEvent`, `SDL_WarpMouseInWindow`, `SDL_ShowCursor`. | Baja |
| Vídeo FMV | `SMACKW32.DLL` (Smacker 2, RAD) para intros y animaciones de razas (`deadcine.cam`, `deadanim.cam`) | `libsmacker` (LGPL, C puro) o FFmpeg (decoder `smacker`). Se decodifica a 8 bpp + paleta y se pinta en el framebuffer. | Media (dependencia externa) |
| UI Win32 | 53 diálogos de recursos (BWCC32.DLL, `DialogBoxParamA`), `MessageBoxA`, controles Win32 (edit, listbox, botones) | Hay que reimplementarlos como diálogos dibujados en el framebuffer (el juego ya dibuja el 95 % de su UI con el sistema `SMenu` de CYLib; los diálogos Win32 son pantallas auxiliares: opciones de partida, nombre del jugador, editor, depuración). | Media-Alta (trabajo, no riesgo técnico) |
| Red multijugador | `CGNET.DLL` (wrapper propio sobre DirectPlay/`DPLAYX.dll`), NetAccolade, TEN, mplayer | Fuera de alcance de SDL2. Opciones: `SDL_net`/ENet reemplazando `CGNet_*` (20 funciones, API sencilla de sesiones/mensajes garantizados). El juego es *lockstep* por turnos con `CHECKSUM.SAV`/`CalculateGameCRC`, muy apto para TCP. | Media |
| Ficheros/registro | `CreateFileA`, `FindFirstFileA`, `GetPrivateProfileStringA` (deadlock.ini), `RegOpenKeyExA` (NetAccolade), CD-ROM check (`GetDriveTypeA`) | `std::filesystem` + parser INI propio; eliminar comprobación de CD. | Baja |
| Memoria | Gestor propio (`Memory Manager`, `Native memory manager`) con `GlobalAlloc`/`VirtualAlloc` | `new`/`std::vector`. | Baja |

## Formatos de datos

Todos los formatos están decodificados (ver `FORMATS.md`) y no dependen de Windows:
CAM (`CYLBPC`), HDX/HDD, IFF-PBM, RIFF WAVE, PCM crudo, BMP, Smacker. El código de carga es portable.

## Riesgos reales

1. **Volumen de código**: ~2 560 funciones de juego (520 KB de código) + 590 de CYLib. La lógica
   de juego (economía, IA "ministros", combate, diplomacia, eventos, red) es la parte grande; la capa
   de plataforma es pequeña.
2. **Diálogos Win32**: 53 plantillas + procedimientos exportados (`GameStyleDialog`, `PlayerNameDialog`,
   `TransferDialog`, `TaskForceDialog`, editor…). Se pueden reimplementar con un mini-toolkit inmediato
   sobre el framebuffer, o mantener temporalmente Win32 en la build de Windows.
3. **Smacker**: licencia de RAD impide redistribuir SMACKW32; `libsmacker` resuelve la reproducción.
4. **Sincronía multijugador**: la reimplementación debe ser determinista (mismo RNG `Reseeded with seed %lX`,
   mismo orden de evaluación) para que el `CalculateGameCRC` siga cuadrando entre máquinas.

## Recomendación de arquitectura

```
src/platform/   Video (8bpp+paleta→SDL_Texture), Audio (mezclador), Input, Timer     ← SDL2
src/formats/    cam_package, hdx_archive, palette, iff_pbm, tile_image, wave, font  ← portable
src/engine/     port de CYLib: offport (superficies), pixel (blits/clip), font, smenu, cylib (handles)
src/game/       lógica reconstruida desde el decompilado (territorios, edificios, unidades, IA, red)
src/ui/         pantallas SMenu + reimplementación de los 53 diálogos
```

Se compila hoy en esta máquina con MSVC 14.50 + CMake + vcpkg (`sdl2:x64-windows` ya instalado), y
con el mismo CMake en Linux/macOS (SDL2 del sistema).
