// sound.h - glsound.c: objetos de sonido creados a partir de recursos WAVE (dl2sound/dl2music .cam) o de entradas
// PCM crudas de SOUND.HDD, reproducidos con la capa Audio (mezclador SDL). Sustituye a DirectSound/waveOut.
#pragma once
#include <cstdint>
#include <memory>
#include <span>
#include <string>
#include <vector>

#include "engine/resources.h"
#include "formats/wave.h"

namespace dl2 {
class Audio;
}

namespace dl2::engine {

// Objeto de sonido (FUN_0048a667 / FUN_00496199): un WAVE decodificado y su voz activa.
struct SoundObject {
    std::shared_ptr<const PcmSound> pcm;
    ResPtr resource;      // recurso WAVE de origen (para liberar la referencia)
    int voice = -1;       // voz del mezclador (-1 = parado)
    uint32_t flags = 0;   // +0xc: bit0 = propiedad de la libreria, bit1 = liberar al terminar, bit2 = liberado
    uint32_t startMs = 0; // +0x10
    bool loop = false;
    bool music = false;
};
using SoundPtr = std::shared_ptr<SoundObject>;

class SoundSystem {
public:
    static SoundSystem& instance();
    // FUN_00496284 / FUN_004962e7: asocia el mezclador (nullptr = silencio).
    void init(Audio* audio) { audio_ = audio; }
    Audio* audio() const { return audio_; }
    bool enabled() const { return audio_ != nullptr; }

    // FUN_00496199: sonido a partir del WAVE `id` (indice de la seccion) de la libreria `lib` (0 = cualquiera).
    SoundPtr load(uint32_t waveId, int lib = 0);
    // Sonido a partir de un payload de SOUND.HDD (PCMWAVEFORMAT + muestras) o RIFF.
    SoundPtr loadRaw(std::span<const uint8_t> data);
    // FUN_0048a333: reproduce (loop = repetir). Devuelve false si no hay audio.
    bool play(const SoundPtr& s, bool loop = false, float volume = 1.0f);
    // FUN_0048a3ef: detiene.
    void stop(const SoundPtr& s);
    // FUN_0048a316: sigue sonando.
    bool isPlaying(const SoundPtr& s) const;
    // FUN_00495fc5: libera (detiene y suelta el recurso).
    void release(SoundPtr& s);
    // FUN_0049604c / FUN_004960fd: mantenimiento de la lista (libera los que terminaron con flag "auto").
    void update();
    // FUN_00496024: para todo.
    void stopAll();
    // Musica: reproduce el WAVE `id` de dl2music.cam en la voz de musica (FUN_004961e8 en streaming).
    bool playMusic(uint32_t waveId, int lib = 0, bool loop = true, float volume = 1.0f);
    void stopMusic();

    // Reproduccion "dispara y olvida" por id (para SMenu::setSoundPlayer).
    void playOnce(uint32_t waveId, int lib = 0);

private:
    Audio* audio_ = nullptr;
    std::vector<SoundPtr> active_;   // DAT_0051e08c
};

}  // namespace dl2::engine
