// iff_pbm.cpp - IFF PBM (ByteRun1) and raw RGB555 picture decoding.
#include "formats/iff_pbm.h"

#include <cstring>

#include "formats/binary.h"

namespace dl2 {

namespace {

constexpr size_t kPict1Header = 48;
constexpr int kMaxDim = 4096;

// Unpacks ByteRun1 (PackBits) data until `out` holds `outSize` bytes. Returns false on truncation.
bool unpackByteRun1(const uint8_t* src, size_t srcSize, uint8_t* out, size_t outSize) {
    size_t i = 0, o = 0;
    while (o < outSize && i < srcSize) {
        const uint8_t n = src[i++];
        if (n < 128) {
            const size_t run = size_t(n) + 1;
            if (i + run > srcSize || o + run > outSize) return false;
            std::memcpy(out + o, src + i, run);
            i += run;
            o += run;
        } else if (n > 128) {
            const size_t run = 257 - size_t(n);
            if (i >= srcSize || o + run > outSize) return false;
            std::memset(out + o, src[i++], run);
            o += run;
        }  // 128 is a no-op
    }
    return o == outSize;
}

}  // namespace

uint32_t pictType(std::span<const uint8_t> pict) {
    return pict.size() >= 4 ? bin::u32le(pict.data()) : 0;
}

bool decodeIffPbm(std::span<const uint8_t> iff, Image8& out, std::string* err) {
    if (iff.size() < 12 || std::memcmp(iff.data(), "FORM", 4) != 0)
        return bin::fail(err, "not an IFF FORM");
    if (std::memcmp(iff.data() + 8, "PBM ", 4) != 0)
        return bin::fail(err, "IFF form type is not PBM");

    size_t formEnd = size_t(bin::u32be(iff.data() + 4)) + 8;
    if (formEnd > iff.size()) formEnd = iff.size();

    int width = 0, height = 0, compression = 0;
    bool haveHeader = false, haveBody = false;
    out.hasPalette = false;

    size_t p = 12;
    while (p + 8 <= formEnd) {
        const uint8_t* ck = iff.data() + p;
        const size_t len = bin::u32be(ck + 4);
        const uint8_t* body = ck + 8;
        if (p + 8 + len > formEnd) return bin::fail(err, "IFF chunk overruns FORM");

        if (std::memcmp(ck, "BMHD", 4) == 0) {
            if (len < 11) return bin::fail(err, "BMHD too short");
            width = bin::u16be(body);
            height = bin::u16be(body + 2);
            compression = body[10];
            if (width <= 0 || height <= 0 || width > kMaxDim || height > kMaxDim)
                return bin::fail(err, "BMHD has implausible size");
            haveHeader = true;
        } else if (std::memcmp(ck, "CMAP", 4) == 0) {
            const size_t n = len / 3 < 256 ? len / 3 : 256;
            for (size_t i = 0; i < n; ++i) out.palette.colors[i] = Rgb{body[i * 3], body[i * 3 + 1], body[i * 3 + 2]};
            out.hasPalette = true;
        } else if (std::memcmp(ck, "BODY", 4) == 0) {
            if (!haveHeader) return bin::fail(err, "BODY before BMHD");
            const size_t rowBytes = size_t(width) + (size_t(width) & 1);  // PBM rows are padded to even length
            const size_t packedSize = rowBytes * size_t(height);
            std::vector<uint8_t> rows(packedSize);
            if (compression == 1) {
                if (!unpackByteRun1(body, len, rows.data(), packedSize)) return bin::fail(err, "ByteRun1 data truncated");
            } else if (compression == 0) {
                if (len < packedSize) return bin::fail(err, "uncompressed BODY too short");
                std::memcpy(rows.data(), body, packedSize);
            } else {
                return bin::fail(err, "unknown BMHD compression " + std::to_string(compression));
            }
            out.width = width;
            out.height = height;
            out.pixels.resize(size_t(width) * size_t(height));
            for (int y = 0; y < height; ++y)
                std::memcpy(out.pixels.data() + size_t(y) * width, rows.data() + size_t(y) * rowBytes, size_t(width));
            haveBody = true;
        }
        p += 8 + len + (len & 1);
    }
    if (!haveBody) return bin::fail(err, "IFF PBM has no BODY");
    return true;
}

bool decodePictType2(std::span<const uint8_t> pict, Image8& out, std::string* err) {
    if (pictType(pict) != uint32_t(PictType::IffPbm)) return bin::fail(err, "PICT is not type 2");
    return decodeIffPbm(pict.subspan(4), out, err);
}

bool decodePictType1(std::span<const uint8_t> pict, Image16& out, std::string* err) {
    if (pictType(pict) != uint32_t(PictType::Rgb555)) return bin::fail(err, "PICT is not type 1");
    if (pict.size() < kPict1Header) return bin::fail(err, "PICT type 1 header too short");
    const int width = bin::u16le(pict.data() + 16);
    const int height = bin::u16le(pict.data() + 18);
    if (width <= 0 || height <= 0 || width > kMaxDim || height > kMaxDim)
        return bin::fail(err, "PICT type 1 has implausible size");
    const size_t count = size_t(width) * size_t(height);
    if (pict.size() < kPict1Header + count * 2) return bin::fail(err, "PICT type 1 pixel data truncated");

    out.width = width;
    out.height = height;
    out.pixels.resize(count);
    // Rows are stored bottom-up (DIB order); flip to top-down while decoding.
    for (int y = 0; y < height; ++y) {
        const uint8_t* src = pict.data() + kPict1Header + size_t(height - 1 - y) * size_t(width) * 2;
        uint16_t* dst = out.pixels.data() + size_t(y) * size_t(width);
        for (int x = 0; x < width; ++x) dst[x] = bin::u16le(src + size_t(x) * 2);
    }
    return true;
}

}  // namespace dl2
