// sdl_audio.cpp - software mixer over an SDL audio device; each voice streams its PCM through an SDL_AudioStream.
#include "platform/sdl_audio.h"

#include <algorithm>
#include <cstring>

namespace dl2 {

namespace {

// Bytes of source PCM pushed per SDL_AudioStreamPut. SDL 2.32's stream silently drops the tail of a
// put that converts to >= 4096 output frames (measured: 1024 frames at 11025 Hz, 2048 at 22050 Hz),
// so each put is sized to at most ~2048 output frames.
size_t feedChunkBytes(const PcmFormat& f) {
    const size_t frames = std::max<size_t>(1, size_t(2048) * f.sampleRate / size_t(Audio::kOutputRate));
    return frames * f.blockAlign();
}

// Every stream is fed signed 16-bit little-endian: 8-bit unsigned sources are converted while feeding,
// because SDL_AudioStreamFlush zero-pads the source-format staging buffer, and a zero byte is full
// negative for AUDIO_U8 (audible click at the end of 8-bit sounds).
bool supported(const PcmFormat& f) {
    return (f.bitsPerSample == 8 || f.bitsPerSample == 16) && (f.channels == 1 || f.channels == 2) && f.sampleRate != 0;
}

}  // namespace

Audio::~Audio() { shutdown(); }

bool Audio::init(std::string* err, const char* deviceName) {
    shutdown();
    if (!SDL_WasInit(SDL_INIT_AUDIO) && SDL_InitSubSystem(SDL_INIT_AUDIO) != 0) {
        if (err) *err = SDL_GetError();
        return false;
    }
    SDL_AudioSpec want{};
    want.freq = kOutputRate;
    want.format = AUDIO_S16SYS;
    want.channels = 2;
    want.samples = 1024;
    want.callback = &Audio::mixCallback;
    want.userdata = this;
    device_ = SDL_OpenAudioDevice(deviceName, 0, &want, &spec_, 0);  // no changes allowed: we get exactly `want`
    if (device_ == 0) {
        if (err) *err = SDL_GetError();
        return false;
    }
    accum_.assign(size_t(spec_.samples) * 2, 0);
    tmp_.assign(size_t(spec_.samples) * 2, 0);
    SDL_PauseAudioDevice(device_, 0);
    return true;
}

void Audio::shutdown() {
    if (!device_) return;
    SDL_CloseAudioDevice(device_);  // stops the callback before returning
    device_ = 0;
    for (Voice& v : voices_) freeVoice(v);
}

bool Audio::startVoice(Voice& v, std::shared_ptr<const PcmSound> sound, float volume, bool loop) {
    if (!sound || sound->data.empty() || !supported(sound->format)) return false;
    SDL_AudioStream* stream = SDL_NewAudioStream(AUDIO_S16LSB, Uint8(sound->format.channels),
                                                 int(sound->format.sampleRate), AUDIO_S16SYS, 2, kOutputRate);
    if (!stream) return false;
    freeVoice(v);
    v.sound = std::move(sound);
    v.stream = stream;
    v.pos = 0;
    v.volume = std::clamp(volume, 0.0f, 1.0f);
    v.loop = loop;
    v.drained = false;
    v.active = true;
    return true;
}

void Audio::freeVoice(Voice& v) {
    if (v.stream) SDL_FreeAudioStream(v.stream);
    v.stream = nullptr;
    v.sound.reset();
    v.active = false;
    v.drained = false;
    v.pos = 0;
}

int Audio::playSound(std::shared_ptr<const PcmSound> sound, float volume, bool loop) {
    if (!device_) return -1;
    int handle = -1;
    SDL_LockAudioDevice(device_);
    for (int i = 0; i < kMaxVoices; ++i) {
        if (!voices_[i].active) {
            if (startVoice(voices_[i], std::move(sound), volume, loop)) handle = i;
            break;
        }
    }
    SDL_UnlockAudioDevice(device_);
    return handle;
}

int Audio::playSound(const PcmSound& sound, float volume, bool loop) {
    return playSound(std::make_shared<const PcmSound>(sound), volume, loop);
}

bool Audio::playMusic(std::shared_ptr<const PcmSound> music, float volume, bool loop) {
    if (!device_) return false;
    SDL_LockAudioDevice(device_);
    const bool ok = startVoice(voices_[kMusicVoice], std::move(music), volume, loop);
    SDL_UnlockAudioDevice(device_);
    return ok;
}

void Audio::stop(int voice) {
    if (!device_ || voice < 0 || voice > kMusicVoice) return;
    SDL_LockAudioDevice(device_);
    freeVoice(voices_[voice]);
    SDL_UnlockAudioDevice(device_);
}

void Audio::stopAll() {
    if (!device_) return;
    SDL_LockAudioDevice(device_);
    for (Voice& v : voices_) freeVoice(v);
    SDL_UnlockAudioDevice(device_);
}

bool Audio::isPlaying(int voice) const {
    if (voice < 0 || voice > kMusicVoice) return false;
    return voices_[voice].active;
}

void Audio::setVolume(int voice, float volume) {
    if (!device_ || voice < 0 || voice > kMusicVoice) return;
    SDL_LockAudioDevice(device_);
    voices_[voice].volume = std::clamp(volume, 0.0f, 1.0f);
    SDL_UnlockAudioDevice(device_);
}

void Audio::feed(Voice& v, int wantBytes) {
    while (!v.drained && SDL_AudioStreamAvailable(v.stream) < wantBytes) {
        const std::vector<uint8_t>& src = v.sound->data;
        if (v.pos >= src.size()) {
            if (v.loop && !src.empty()) {
                v.pos = 0;
            } else {
                SDL_AudioStreamFlush(v.stream);
                v.drained = true;
                break;
            }
        }
        const size_t n = std::min(feedChunkBytes(v.sound->format), src.size() - v.pos);
        const uint8_t* chunk = src.data() + v.pos;
        size_t chunkBytes = n;
        if (v.sound->format.bitsPerSample == 8) {  // unsigned 8-bit -> signed 16-bit little-endian
            conv_.resize(n * 2);
            for (size_t i = 0; i < n; ++i) {
                conv_[i * 2] = 0;
                conv_[i * 2 + 1] = uint8_t(chunk[i] ^ 0x80);
            }
            chunk = conv_.data();
            chunkBytes = n * 2;
        }
        if (SDL_AudioStreamPut(v.stream, chunk, int(chunkBytes)) != 0) {
            SDL_AudioStreamFlush(v.stream);
            v.drained = true;
            break;
        }
        v.pos += n;
    }
}

void Audio::mix(int16_t* out, int frames) {
    const size_t samples = size_t(frames) * 2;
    if (accum_.size() < samples) { accum_.resize(samples); tmp_.resize(samples); }
    std::fill_n(accum_.data(), samples, 0);
    const int wantBytes = int(samples * sizeof(int16_t));

    for (Voice& v : voices_) {
        if (!v.active) continue;
        feed(v, wantBytes);
        const int got = SDL_AudioStreamGet(v.stream, tmp_.data(), wantBytes);
        if (got <= 0) {
            if (v.drained) freeVoice(v);
            continue;
        }
        const int gain = int(v.volume * master_ * 256.0f + 0.5f);
        const size_t n = size_t(got) / sizeof(int16_t);
        for (size_t i = 0; i < n; ++i) accum_[i] += (int32_t(tmp_[i]) * gain) >> 8;
        if (got < wantBytes && v.drained && SDL_AudioStreamAvailable(v.stream) == 0) freeVoice(v);
    }
    for (size_t i = 0; i < samples; ++i) out[i] = int16_t(std::clamp(accum_[i], -32768, 32767));
}

void SDLCALL Audio::mixCallback(void* userdata, Uint8* stream, int len) {
    Audio* self = static_cast<Audio*>(userdata);
    std::memset(stream, 0, size_t(len));
    self->mix(reinterpret_cast<int16_t*>(stream), len / int(2 * sizeof(int16_t)));
}

}  // namespace dl2
