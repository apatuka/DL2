// cygame.h - fachada "CYGame" (cygame.c / InitCYGame): abre las librerias CAM, crea el port de pantalla
// (640x480x16 RGB555 por defecto, como el juego original con -16), lo presenta en Video y traduce la entrada
// SDL a las colas de CYLib (InputQueue).
#pragma once
#include <cstdint>
#include <string>

#include "engine/offport.h"
#include "engine/palette_table.h"

namespace dl2 {
class Video;
class Audio;
struct InputState;
}

namespace dl2::engine {

class CyGame {
public:
    static CyGame& instance();

    // FUN_0048b623 + FUN_0049a760 + FUN_00490d98 + FUN_00491898: crea la pantalla de w x h a `bpp` bits y la
    // instala como port actual. video/audio pueden ser nullptr (modo sin ventana, p.ej. herramientas).
    bool init(int w = 640, int h = 480, int bpp = 16, Video* video = nullptr, Audio* audio = nullptr);
    void shutdown();

    // FUN_0046fc70: abre las librerias del juego desde dataDir (deadcyb, deadtext, dl2sound, dl2music, dl2segue,
    // deadanim, deadcine; las que falten se ignoran). Devuelve cuantas se abrieron.
    int openLibraries(const std::string& dataDir, std::string* err = nullptr);

    OffPort& screen() { return screen_; }
    // Paleta de sistema (DAT_0065e5ac / FUN_0048d391 sobre la primaria): en 8 bpp se envia a Video.
    void setSystemPalette(const ColorTablePtr& pal);

    // Vuelca la pantalla a Video (blit RGB555 o 8 bpp + paleta) y presenta.
    void present();
    // Traduce el estado de entrada del frame a InputQueue (raton en coordenadas de framebuffer, teclas CYLib).
    void feedInput(const InputState& in);
    // FUN_0048de03: ms desde el arranque.
    uint32_t ticks() const;

    Video* video() const { return video_; }
    Audio* audio() const { return audio_; }

private:
    OffPort screen_;
    Video* video_ = nullptr;
    Audio* audio_ = nullptr;
    uint64_t startMs_ = 0;
    uint32_t lastButtons_ = 0;
    bool hasLastClick_[2] = {false, false};
    uint32_t lastClickMs_[2] = {0, 0};
    int lastClickX_[2] = {0, 0}, lastClickY_[2] = {0, 0};
};

}  // namespace dl2::engine
