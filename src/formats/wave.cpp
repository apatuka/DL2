// wave.cpp - RIFF WAVE chunk walking and raw PCMWAVEFORMAT sound decoding.
#include "formats/wave.h"

#include <cstring>

#include "formats/binary.h"

namespace dl2 {

namespace {

constexpr uint16_t kWaveFormatPcm = 1;

bool parseFormat(const uint8_t* p, PcmFormat& fmt, std::string* err) {
    const uint16_t tag = bin::u16le(p);
    if (tag != kWaveFormatPcm) return bin::fail(err, "unsupported wave format tag " + std::to_string(tag));
    fmt.channels = bin::u16le(p + 2);
    fmt.sampleRate = bin::u32le(p + 4);
    fmt.bitsPerSample = bin::u16le(p + 14);
    if (fmt.channels < 1 || fmt.channels > 2) return bin::fail(err, "unsupported channel count");
    if (fmt.bitsPerSample != 8 && fmt.bitsPerSample != 16) return bin::fail(err, "unsupported bits per sample");
    if (fmt.sampleRate == 0) return bin::fail(err, "zero sample rate");
    return true;
}

}  // namespace

bool decodeRiffWave(std::span<const uint8_t> riff, PcmSound& out, std::string* err) {
    if (riff.size() < 12 || std::memcmp(riff.data(), "RIFF", 4) != 0 || std::memcmp(riff.data() + 8, "WAVE", 4) != 0)
        return bin::fail(err, "not a RIFF WAVE");
    size_t end = size_t(bin::u32le(riff.data() + 4)) + 8;
    if (end > riff.size()) end = riff.size();

    bool haveFmt = false, haveData = false;
    size_t p = 12;
    while (p + 8 <= end) {
        const uint8_t* ck = riff.data() + p;
        size_t len = bin::u32le(ck + 4);
        const uint8_t* body = ck + 8;
        if (p + 8 + len > end) len = end - p - 8;  // tolerate a truncated final chunk
        if (std::memcmp(ck, "fmt ", 4) == 0) {
            if (len < 16) return bin::fail(err, "fmt chunk too short");
            if (!parseFormat(body, out.format, err)) return false;
            haveFmt = true;
        } else if (std::memcmp(ck, "data", 4) == 0) {
            out.data.assign(body, body + len);
            haveData = true;
        }
        p += 8 + len + (len & 1);
    }
    if (!haveFmt) return bin::fail(err, "WAVE has no fmt chunk");
    if (!haveData) return bin::fail(err, "WAVE has no data chunk");
    out.data.resize(out.data.size() - out.data.size() % out.format.blockAlign());
    return true;
}

bool decodeRawSound(std::span<const uint8_t> raw, PcmSound& out, std::string* err) {
    if (raw.size() < 16) return bin::fail(err, "raw sound too short");
    if (!parseFormat(raw.data(), out.format, err)) return false;
    out.data.assign(raw.begin() + 16, raw.end());
    out.data.resize(out.data.size() - out.data.size() % out.format.blockAlign());
    return true;
}

}  // namespace dl2
