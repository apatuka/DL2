// hooks.h - Puntos de enganche desde la lógica de juego hacia la UI/motor (sin dependencia de SDL ni del motor).
//
// La lógica portada de DEADLOCK.EXE llama a estas funciones donde el original llamaba a MessageBox,
// SMenu, sonido, animaciones, log de depuración, etc. La capa de UI (src/ui) instala implementaciones
// reales en `hooks::ui`; por defecto todo son no-ops que escriben en el log de depuración.
#pragma once
#include <cstdint>
#include <functional>
#include <string>

namespace dl2::hooks {

struct UiHooks {
    // MessageBox del original (FUN_0042836c(title, text, flags, ...)); devuelve el id del botón (1 OK, 2 Cancel, 6 Yes, 7 No).
    std::function<int(const char* title, const char* text, unsigned flags)> messageBox;
    // DebugMessage (FUN_00458990): errores internos / aserciones del juego.
    std::function<void(const char* text)> debugMessage;
    // DebugLog (FUN_004587f0 / FUN_004589a0): "Turn %3d: <tag>" en DEBUG.TXT.
    std::function<void(const char* tag)> debugLog;
    // Refresco de pantallas del original (InvalidateRect / SMenu redraw) por área lógica.
    std::function<void(const char* what)> refresh;
    // Sonido/voz por id de recurso (WAVE de dl2sound.cam / SOUND.HDD) y música.
    std::function<void(int soundId)> playSound;
    std::function<void(const char* name)> playSpeech;   // entradas SOUND.HDD ("CCACPTA"...)
    // Progreso ("Sending Game Data\r%d%% complete", "Preparing Long Range Scan"...).
    std::function<void(const char* text, int percent)> progress;
    // Bomba de mensajes / espera cooperativa (MessagePump FUN_0046cff8, WaitMessage): la red y los
    // temporizadores del original la usan; en el port la UI puede procesar eventos SDL aquí.
    std::function<void()> pump;
    // Reloj en ms (timeGetTime).
    std::function<uint32_t()> ticks;
};

extern UiHooks ui;

// Helpers con valores por defecto seguros.
int  messageBox(const char* title, const char* text, unsigned flags = 0);
void debugMessage(const char* text);
void debugLog(const char* tag);
void refresh(const char* what);
void playSound(int soundId);
void playSpeech(const char* name);
void progress(const char* text, int percent);
void pump();
uint32_t ticks();

// printf-style para DebugMessage (muchas llamadas del original usan wsprintfA + DebugMessage).
void debugMessagef(const char* fmt, ...);

} // namespace dl2::hooks
