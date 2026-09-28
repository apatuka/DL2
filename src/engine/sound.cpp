// sound.cpp - glsound.c sobre la capa Audio.
#include "engine/sound.h"

#include <algorithm>

#include "engine/input_queue.h"
#include "platform/sdl_audio.h"

namespace dl2::engine {

SoundSystem& SoundSystem::instance() {
    static SoundSystem s;
    return s;
}

SoundPtr SoundSystem::load(uint32_t waveId, int lib) {
    ResPtr r = resources().get(kTagWAVE, waveId, lib, kResRef);
    if (!r || !r->sound) return nullptr;
    auto s = std::make_shared<SoundObject>();
    s->pcm = r->sound;
    s->resource = r;
    s->flags = 1;
    return s;
}

SoundPtr SoundSystem::loadRaw(std::span<const uint8_t> data) {
    auto pcm = std::make_shared<PcmSound>();
    std::string err;
    if (!decodeRiffWave(data, *pcm, &err) && !decodeRawSound(data, *pcm, &err)) return nullptr;
    auto s = std::make_shared<SoundObject>();
    s->pcm = pcm;
    return s;
}

bool SoundSystem::play(const SoundPtr& s, bool loop, float volume) {
    if (!audio_ || !s || !s->pcm) return false;
    if (s->voice >= 0 && audio_->isPlaying(s->voice)) audio_->stop(s->voice);
    s->voice = audio_->playSound(s->pcm, volume, loop);
    s->loop = loop;
    s->startMs = InputQueue::instance().nowMs();
    if (s->voice >= 0 && std::find(active_.begin(), active_.end(), s) == active_.end()) active_.push_back(s);
    return s->voice >= 0;
}

void SoundSystem::stop(const SoundPtr& s) {
    if (!audio_ || !s || s->voice < 0) return;
    audio_->stop(s->voice);
    s->voice = -1;
}

bool SoundSystem::isPlaying(const SoundPtr& s) const {
    return audio_ && s && s->voice >= 0 && audio_->isPlaying(s->voice);
}

void SoundSystem::release(SoundPtr& s) {
    if (!s) return;
    stop(s);
    s->flags |= 4;
    active_.erase(std::remove(active_.begin(), active_.end(), s), active_.end());
    if (s->resource) resources().release(s->resource);
    s.reset();
}

void SoundSystem::update() {
    for (size_t i = 0; i < active_.size();) {
        SoundPtr& s = active_[i];
        if (!isPlaying(s)) {
            s->voice = -1;
            if (s->flags & 2) {
                if (s->resource) resources().release(s->resource);
                active_.erase(active_.begin() + std::ptrdiff_t(i));
                continue;
            }
        }
        ++i;
    }
}

void SoundSystem::stopAll() {
    for (SoundPtr& s : active_) stop(s);
    if (audio_) audio_->stopAll();
}

bool SoundSystem::playMusic(uint32_t waveId, int lib, bool loop, float volume) {
    if (!audio_) return false;
    ResPtr r = resources().get(kTagWAVE, waveId, lib, 0);
    if (!r || !r->sound) return false;
    return audio_->playMusic(r->sound, volume, loop);
}

void SoundSystem::stopMusic() {
    if (audio_) audio_->stopMusic();
}

void SoundSystem::playOnce(uint32_t waveId, int lib) {
    SoundPtr s = load(waveId, lib);
    if (!s) return;
    s->flags |= 2;   // liberar al terminar
    play(s, false, 1.0f);
}

}  // namespace dl2::engine
