// sdl_audio.h - Audio: SDL output device (44100 Hz stereo s16) mixing up to 8 PCM sound voices plus one music voice.
#pragma once
#include <SDL.h>

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "formats/wave.h"

namespace dl2 {

class Audio {
public:
    static constexpr int kMaxVoices = 8;
    static constexpr int kMusicVoice = kMaxVoices;  // handle of the dedicated music voice
    static constexpr int kOutputRate = 44100;

    Audio() = default;
    ~Audio();
    Audio(const Audio&) = delete;
    Audio& operator=(const Audio&) = delete;

    // Opens the default output device, or the named one (SDL device name).
    bool init(std::string* err = nullptr, const char* deviceName = nullptr);
    void shutdown();
    bool isOpen() const { return device_ != 0; }

    // Starts a sound on a free voice; returns its handle (0..7) or -1 if none is free.
    // Accepts 8-bit unsigned / 16-bit signed PCM, mono or stereo, any rate; resampling is done by SDL_AudioStream.
    int playSound(std::shared_ptr<const PcmSound> sound, float volume = 1.0f, bool loop = false);
    int playSound(const PcmSound& sound, float volume = 1.0f, bool loop = false);  // copies the data
    // Replaces whatever is playing on the music voice. Returns false if the format is unsupported.
    bool playMusic(std::shared_ptr<const PcmSound> music, float volume = 1.0f, bool loop = true);

    void stop(int voice);
    void stopMusic() { stop(kMusicVoice); }
    void stopAll();
    bool isPlaying(int voice) const;
    void setVolume(int voice, float volume);
    void setMasterVolume(float volume) { master_ = volume; }

private:
    struct Voice {
        std::shared_ptr<const PcmSound> sound;
        SDL_AudioStream* stream = nullptr;
        size_t pos = 0;        // bytes of source data fed into the stream so far
        float volume = 1.0f;
        bool loop = false;
        bool active = false;
        bool drained = false;  // source exhausted and stream flushed
    };

    static void SDLCALL mixCallback(void* userdata, Uint8* stream, int len);
    void mix(int16_t* out, int frames);
    void feed(Voice& v, int wantBytes);
    bool startVoice(Voice& v, std::shared_ptr<const PcmSound> sound, float volume, bool loop);
    void freeVoice(Voice& v);

    SDL_AudioDeviceID device_ = 0;
    SDL_AudioSpec spec_{};
    Voice voices_[kMaxVoices + 1];
    std::vector<int32_t> accum_;
    std::vector<int16_t> tmp_;
    std::vector<uint8_t> conv_;   // 8-bit -> 16-bit conversion scratch (audio thread only)
    float master_ = 1.0f;
};

}  // namespace dl2
