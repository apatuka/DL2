// wave.h - PCM sound container: RIFF WAVE (dl2sound/dl2music .cam) and raw SOUND.HDD entries (PCMWAVEFORMAT + samples).
#pragma once
#include <cstddef>
#include <cstdint>
#include <span>
#include <string>
#include <vector>

namespace dl2 {

struct PcmFormat {
    uint16_t channels = 1;        // 1 or 2
    uint32_t sampleRate = 11025;
    uint16_t bitsPerSample = 16;  // 8 (unsigned) or 16 (signed little-endian)
    size_t blockAlign() const { return size_t(channels) * (bitsPerSample / 8); }
};

struct PcmSound {
    PcmFormat format;
    std::vector<uint8_t> data;    // interleaved PCM frames
    size_t frames() const { const size_t b = format.blockAlign(); return b ? data.size() / b : 0; }
    double seconds() const { return format.sampleRate ? double(frames()) / format.sampleRate : 0.0; }
};

// RIFF/WAVE with "fmt " (PCM, tag 1) and "data" chunks.
bool decodeRiffWave(std::span<const uint8_t> riff, PcmSound& out, std::string* err = nullptr);
// SOUND.HDD payload: 16-byte PCMWAVEFORMAT (tag, channels, rate, avgBytes, blockAlign, bits) then samples.
bool decodeRawSound(std::span<const uint8_t> raw, PcmSound& out, std::string* err = nullptr);

}  // namespace dl2
