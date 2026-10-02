#include "game/load_world_presentation.h"
#include <algorithm>
#include <array>
#include <bit>
#include <cstring>
#include <exception>
#include <memory>
#include <new>
#include <stdexcept>
#include <string>
#include <utility>

namespace dl2::simulation {
namespace {
bool fail(save::Error& error, const char* message) {
    error = {save::ErrorCode::InvalidState, 0, message}; return false;
}
// Immutable bytes verified from the installed DEADLOCK.EXE; no executable
// addresses or external runtime file dependency. Original tables004d52bc..553b.
constexpr int16_t kDistribution[5][64] = {
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-4,-4,-5,-6},
    {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5},
    {1,1,1,1,1,1,2,2,1,1,1,1,1,1,2,2,2,2,2,2,3,3,3,3,4,4,4,5,5,5,6,6,4,4,4,5,5,5,6,6,6,7,7,8,8,9,9,10,-2,-2,-2,-2,-3,-3,-3,-3,-4,-4,-4,-5,-5,-5,-6,-6},
    {1,1,2,2,2,3,3,3,3,4,4,5,5,6,6,7,3,4,4,5,5,6,6,7,7,7,8,8,8,9,9,9,7,7,8,8,8,9,9,9,10,10,11,11,11,12,12,12,-3,-4,-4,-5,-5,-6,-6,-7,-7,-7,-8,-8,-8,-9,-9,-9},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,2,2,1,1,1,1,2,2,2,3,1,1,1,2,2,2,3,3,1,2,2,2,3,3,4,8,4,4,4,4,4,4,4,4,1,1,1,1,1,-1,-1,-1}
};
struct HeightConfig { int base, count, slopeMin, slopeMax, floor, distribution; };
//004d553c, stride32; original+8/+12 are unused by00469744.
constexpr HeightConfig kHeight[7] = {
    {-5,40,3,4,1,0}, {2,10,8,16,16,0}, {1,2,1,2,16,1},
    {1,1,1,2,16,1}, {1,25,6,8,4,2}, {1,150,8,16,0,3}, {2,80,14,16,0,4}
};
constexpr int kThreshold[9] = {10,30,20,30,100,100,20,100,100}; //004d5298
constexpr uint8_t kColor[5] = {32,24,40,56,72}; //004d561c
constexpr int kCount[7][5] = { //004d5630
    {0,0,0,0,0},{0,8,12,0,32},{0,8,8,32,0},{0,8,24,4,0},
    {0,0,4,0,0},{0,8,8,4,0},{70,1,0,0,0}
};
constexpr int kDiameter[7][5] = { //004d56bc
    {0,0,0,0,0},{0,16,16,0,16},{0,16,16,16,0},{0,12,16,8,0},
    {0,0,8,0,0},{0,8,8,8,0},{8,28,0,0,0}
};
constexpr int kDensity[7][5] = { //004d5748
    {0,0,0,0,0},{0,25,45,0,45},{0,10,65,90,0},{0,80,65,65,0},
    {0,0,30,0,0},{0,25,45,15,0},{95,55,0,0,0}
};
//0046338c: byte patches, not a replacement for the untouched palette gap.
constexpr const char* kTheme[7] = { //00519ecc, stride256
    "634f4300735f53008373630097877700a79b8b00bbafa300cbc3b700dfdbd3003b5b5b00476b6b00537b7f005f8b8f006f9fa3007bafb3008bbfc7009bcfdb002b2323003b3333004b4343005f5353006f676700837b7b00938f8f00a7a7a7003b4b4f004b5f63005b7377006b878b007b9b9f008bb3b3009bc7c300afdbd700233b43002f4b53003f5f630053737700678387007b979b0093abab00afbfbf00273723002f432b00374f2f003f5b37004b673f00537347005b7f4f00678b57006f4707007b4f0b0087571300935f17009f671f00ab732b00b77b3300c3873f0000000000171713002f2f2700474b3b005f634f00777b63008f937700a7af8b00",
    "3f4b470053635f006b7b770083938f009bafab00b7c7c300cfdfdb00ebfbf700234b5b0027535f002f5b670033676f003b6f7700437b7f004b838700538f8f00173b2f001b4743001f475300233f630033537300476787005b7f9b007397af001f331f00233f23002b4b2b00335b33003b6b4b00477b6b004f838b005b7f9b00173b2f001f3f57002b53630037636b00437777004f7f77005f8b7f0073978700273b2300273f23002b4727002b4b27002f532b002f5f3300376b3b003f7f47007b3b1300873f1300934717009f4f1700af531b00bb5b1f00c7631f00d76b230000000000131f0000172f00001b3b07001b4b0f001b5f33002f736f0047678700",
    "0f1f3300172b4700233b5b002f4f73003f5f87004b739b005787b300679fcb001f2b630027336f002f3f7f00374b8b003f579b004b63a7005773b7006383c700171743001f235300272f6700333f7b003f4f8b004b639f005b77b3006b8fc700172347001f2f5b00273f6f00334f83003f5f9b004767ab004f73bb005783cb000f133300171f47001f2b5b002b3f6f003b4f830047639700577bab006b93c3000f172700131f33001b2b3f0027374b002f435b003b4f6700475b7300536b8300436f97003b638b00375b830033537b0027436b001f335b0017274b00131b3b000f0f2700131733001b233f00272f4b002f3b5b003b4f77004b6393005b77b300",
    "63433b0077574b008f6b6300a3837b00bb9b9300cfb7af00e7d3cf00fff3ef00331f0b004f3317006b472300875b3700a3734b00bf8f6300dba77f00fbc79f001f1b1300332f23004b433300635743007b6f570093836b00ab9b8300c3b39b00673b1f00774b2b00875f3f0097735300a7876700b79b7f00c7b39b00d7cbbb003f2b2700533b33006b5343007f675300977f6300ab977700c3af8700dbcb9b004b370000534700005f57070067670f006b7313006b7b1f006f87270073933300d3937f00d3978300d79f8b00dba78f00dfab9700e7bfb300f3d7cf00fff3ef001f231b002b332700374333003f533f004b674f0057775f00638773006f9b8700",
    "0b17230017273700273f4f003b5763004f737b006b8b8f008ba7a700afbfbf003b4b630043576f004b677f0053738b005b839b006393a7006ba3b70073b7c700070f170013232f002337470037535f004f6b77006b878f008ba3a700afbfbf00334f53003f5f67004b737b0053878f005f97a3006b9ba3007ba3a3008ba7a700233b3f002f4b4f003f5f630053737300678387007b97970093abab00afbfbf0017271b001f332300233f2f002b4b3f0033574b003f635b00476f6b004f7b7b00573b2b00634333006f4f3b007b5743008b634b00976f5300a37b5b00b38767001f2723002b3733003747430047575300536763005f7777006b8787007b979b00",
    "b3b7bb00afbbcf009fabd700878fab0057638b004f67d30043538f000f173300333753003b3f5b00474b67005357730063637f006f6f8b007f7f97008f8fa3002f2f3b003f3f4f004f53630063677700777b8b00878f9f009ba3b7008b93a7000b0f13000f1317001b1f2b002317170023272f0013171b004b4f5b00373b43000f171b0017232700232f37002f3747003b4357004b4f67005b5b77006b6b87000b0b0f0017171b002f2f3b003f434f00676b7b008b93ab00576b97007f8bab00007f970007839b000f8ba3001b93ab00279bb30033afc70047c3db005bd7ef000b0b3f00171793005b5ba70000138700002faf00274bb3002b579b007b83a300",
    "3f4b470053635f006b7bc70083938f009bafab00b7c7c300cfdfdb00ebfbf7001b334b00233f57002b476300335373003f637f004b6f8f00537b9b00638bab0017233b001f2b1f002b375b0037436b00434f7b00535b8b005f679b007377af0017132b00231f3f00372f5700473f6f005f4f870073639f008b77b700a38fcf002f3b37003b434700474757005b536700635f73006f6b7f007b7b8b008b8f97001f1b3b000700530043436f002f2b8b004b47a300534fbf007373db006f6ff7002f1f0000433300005b33000073670700878307009b9f0b00a3b70f00abcf1700000000001f1717003f2f2f00634b470083635f00a37b7700c39393009b8f9700"
};
constexpr const char* kPalettePrefix = "53535300a7a7a7000f272f0000dfdf005f8b4b00ab000000"; //0051a5cc
constexpr const char* kPaletteSuffix = "cddeac009cb4ac008b834a00946a6200948b8b00aca48b009cb45a00ac945a0094836a007b946a005a836a007b9494008ba4a4006a8bac004a94bd005283b4004a6aa40052739400396294002952830041735a004a626a006a5262006231410062623900525a52004a4a4100293131003129180018201000000839001018730000185a000831620020317300204a620018399400184abd003152b400316ac5004183d5004a94de006a9cde0083b4d50094c5de0094c5c500acc5c500c5dede00efefef00e7e7e700cecece00c6c6c600bdbdbd00adadad00a5a5a5009c9c9c00949494008484840073737300636363005a5a5a0052525200424242000000000023232300474747006b6b6b008f8f8f00b3b3b300dbdbdb00007bff009300d300d3a38f00c7ff3f000000d70000730b00b7c3ff005b57bb002b1b77001f0043005ba3e3003f77c300274fa700132b8b00070f6f006febff0063b7cf00538b9f003b5f6f002737430087ebab0067bb67005f8b4b004b5b2f002f2f1700d75b2f00afb39f009f9f87008b8373007b6b5f0067534b00573b3b00ff00ff00ff00ff00ff00ff00ff00ff00ff00ff00ff00ff00ff00ff00ff00ff00ff00ff00ffffff00"; //0051a5e4
std::vector<uint8_t> unhex(const char* string) {
    const auto nibble = [](char c) { return c <= '9' ? c - '0' : c - 'a' + 10; };
    std::vector<uint8_t> result;
    for (; *string; string += 2) result.push_back(uint8_t(nibble(string[0]) * 16 + nibble(string[1])));
    return result;
}
int16_t narrow16(int value) { return std::bit_cast<int16_t>(uint16_t(value)); }
int absolute(int value) { return value < 0 ? -value : value; }
int sar2(int value) { return value >= 0 ? value / 4 : -int((unsigned(-value) + 3) / 4); }
struct RngFailure {};

struct Work {
    save::Document& d;
    LoadWorldPresentationReport& out;
    SessionRng rng;
    save::Error& error;
    int width, height, slope;
    std::vector<int16_t> heights;
    explicit Work(save::Document& document, LoadWorldPresentationReport& report,
                  save::Error& e, int initialSlope)
        : d(document), out(report), error(e), width(document.world.width * 32),
          height(document.world.height * 32), slope(initialSlope),
          heights(size_t(width) * height, -1) {}
    size_t at(int x, int y) const { return size_t(y) * width + x; }
    bool inside(int x, int y) const { return x >= 0 && y >= 0 && x < width && y < height; }
    Tile& tile(int x, int y) { return d.tiles[size_t(y) * d.world.width + x]; }
    Tile& listedTile(const Territory& t, int index) {
        const auto packed = t.tiles[index].raw;
        return tile(int(packed & 0xffff), int(packed >> 16));
    }
    int draw() {
        RngEvent event;
        if (!rng.apply({RngOperation::Long31, 0, 0, {}}, event, error)) throw RngFailure{};
        return int(event.value);
    }
    void terrain();
    void generateHeights();
    void flatten();
    void colorPatch(int x, int y, uint8_t color, int diameter, int density);
    void colors();
    int shade(int current, int right, int above, int& horizon);
    void shading();
    void rivers();
    void scale();
    bool selection();
};

//0046a1ac: the sentinel territory0 is zero after load and has no listed tiles.
void Work::terrain() {
    for (auto& record : d.territories) {
        auto& t = record.data;
        for (int i = 0; i < t.numTiles; ++i) {
            auto& current = listedTile(t, i);
            if (!current.terrain) continue;
            switch (t.terrain) {
            case 0: current.terrain = 0; break;
            case 1: current.terrain = draw() % 16 ? 3 : 4; break;
            case 2: current.terrain = draw() % 8 ? 2 : 4; break;
            case 3: current.terrain = 1; break;
            case 4: current.terrain = 5; break;
            case 5: current.terrain = 6; break;
            default: break; // Original switch has no default mutation.
            }
        }
    }
    for (auto& record : d.territories) {
        auto& t = record.data;
        if (!t.terrain || t.centerTile == -1) continue;
        auto& center = listedTile(t, t.centerTile);
        const int x = center.x, y = center.y;
        for (int dy = -1; dy <= 1; ++dy) for (int dx = -1; dx <= 1; ++dx) {
            if (x + dx < 0 || y + dy < 0 || x + dx >= d.world.width || y + dy >= d.world.height) continue;
            // Draw precedes the terrain test, including non-mountain neighbors.
            const bool convert = draw() % 100 < kThreshold[4 + dx * 3 + dy];
            auto& neighbor = tile(x + dx, y + dy);
            if (convert && neighbor.terrain == 5) neighbor.terrain = 4;
        }
        center.terrain = 3;
    }
}

//00469744; short writes intentionally wrap. All wider products are bounded by
// immutable tables and the validated40x40 tile domain, not signed-overflow UB.
void Work::generateHeights() {
    for (int ty = 0; ty < d.world.height; ++ty) for (int tx = 0; tx < d.world.width; ++tx) {
        const auto& cfg = kHeight[tile(tx, ty).terrain];
        for (int y = ty * 32; y < ty * 32 + 32; ++y)
            for (int x = tx * 32; x < tx * 32 + 32; ++x) heights[at(x, y)] = int16_t(cfg.base);
    }
    for (int ty = 0; ty < d.world.height; ++ty) for (int tx = 0; tx < d.world.width; ++tx) {
        const auto& cfg = kHeight[tile(tx, ty).terrain];
        for (int feature = 0; feature < cfg.count; ++feature) {
            const int cx = draw() % 31 + tx * 32;
            const int cy = draw() % 31 + ty * 32;
            const int sample = kDistribution[cfg.distribution][draw() % 64];
            const int amplitude = absolute(sample) * 8, sign = sample < 0 ? -1 : 1;
            const int gradient = std::min(draw() % 16 + cfg.slopeMin, cfg.slopeMax);
            const int radius = (amplitude / 8 * 16) / gradient;
            // Original order is X outer, Y inner, unlike the color pass.
            for (int x = std::max(0, cx - radius); x < cx + radius && x < width; ++x)
                for (int y = std::max(0, cy - radius); y < cy + radius && y < height; ++y) {
                    const int dx = absolute(x - cx) * 8, dy = absolute(y - cy) * 8;
                    const int distance = (std::max(dx, dy) + std::min(dx, dy) / 2) * gradient / 16;
                    if (distance < amplitude) {
                        auto& h = heights[at(x, y)];
                        h = narrow16(h + (amplitude - std::max(distance, cfg.floor)) * sign);
                    }
                }
        }
    }
}

//0046a39c; the inclusive+32 plateau (33pixels) is an original peculiarity.
void Work::flatten() {
    for (const auto& record : d.territories) {
        const auto& t = record.data;
        if (!t.terrain || t.centerTile == -1) continue;
        const auto& center = listedTile(t, t.centerTile);
        const int x0 = center.x * 32, y0 = center.y * 32;
        const int level = std::max(2, int(heights[at(x0 + 16, y0 + 16)]));
        for (int y = y0 - 10; y < y0 + 42; ++y) for (int x = x0 - 10; x < x0 + 42; ++x) {
            if (!inside(x, y)) continue;
            auto& h = heights[at(x, y)];
            if (h <= 0) continue;
            if (x < x0 || x > x0 + 32 || y < y0 || y > y0 + 32) {
                const int dx = x < x0 ? (x0 - x) * 10 : x > x0 + 32 ? (x - x0 - 32) * 10 : 0;
                const int dy = y < y0 ? (y0 - y) * 10 : y > y0 + 32 ? (y - y0 - 32) * 10 : 0;
                const int16_t delta = narrow16((100 - std::max(dx, dy)) * (level - h) / 100);
                h = narrow16(h + delta);
            } else h = narrow16(level);
        }
    }
}

//004693b0; consume a draw for EVERY point of the square before water/octagon tests.
void Work::colorPatch(int cx, int cy, uint8_t color, int diameter, int density) {
    const int radius = diameter / 2;
    for (int y = std::max(0, cy - radius); y < cy + radius && y < height; ++y)
        for (int x = std::max(0, cx - radius); x < cx + radius && x < width; ++x) {
            const bool chosen = draw() % 100 < density;
            auto& pixel = out.colorMap[at(x, y)];
            if (!chosen || pixel == 0x40) continue;
            const int dx = absolute(x - cx), dy = absolute(y - cy);
            if (std::max(dx, dy) + std::min(dx, dy) / 2 <= radius) pixel = color;
        }
}

//00469ff4 then004694c0. Zero-count slots still flip coins and can become1;
// zero half-diameter/density skips that draw, not the two position draws.
void Work::colors() {
    out.colorMap.resize(heights.size());
    for (size_t i = 0; i < heights.size(); ++i) out.colorMap[i] = heights[i] < 1 ? 0x40 : 0x30;
    for (int layer = 0; layer < 5; ++layer)
        for (int ty = 0; ty < d.world.height; ++ty) for (int tx = 0; tx < d.world.width; ++tx) {
            const int terrain = tile(tx, ty).terrain;
            int count = kCount[terrain][layer], diameter = kDiameter[terrain][layer];
            const int density = kDensity[terrain][layer];
            for (int coin = 0; coin < 2; ++coin) {
                if (draw() % 2) break;
                count = std::max(1, count / 2); diameter *= 2;
            }
            for (int i = 0; i < count; ++i) {
                const int x = draw() % 64 + tx * 32 - 16;
                const int y = draw() % 64 + ty * 32 - 16;
                const int halfDiameter = diameter / 2, halfDensity = density / 2;
                const int dd = halfDiameter ? draw() % halfDiameter : 0;
                const int dc = halfDensity ? draw() % halfDensity : 0;
                colorPatch(x, y, kColor[layer], dd + halfDiameter, dc + halfDensity);
            }
        }
}

//00469e84: arithmetic shift for negative water heights; other divisions use
// truncation toward zero. slope is session scratch, horizon resets each row.
int Work::shade(int current, int right, int above, int& horizon) {
    int result;
    if (current < 1) {
        result = std::clamp(sar2(current) + 7, 0, 5) + draw() % 2;
        current = 0;
    } else {
        const int vertical = draw() % 9 + above - current - 5;
        const int horizontal = draw() % 9 + right - current - 5;
        slope = std::max(absolute(vertical), absolute(horizontal)) + std::min(absolute(vertical), absolute(horizontal)) / 2;
        if (!slope) slope = 1;
        const int a = 141 - horizontal * 100 / slope;
        const int b = -(vertical * 100 / slope) - 141;
        const int combined = std::max(a, b) + std::min(a, b) / 2;
        result = combined / 150 + 3 - (right - current) / 16;
    }
    if (current < horizon) {
        result -= (horizon - current) / 8;
        current = horizon;
    }
    horizon = current - 24;
    return std::clamp(result, 0, 7);
}

//0046a020 /00469e50: right-to-left scan with unmodified height neighbors.
void Work::shading() {
    for (int y = 0; y < height; ++y) {
        int horizon = 0;
        for (int x = width - 1; x >= 0; --x) {
            auto& color = out.colorMap[at(x, y)];
            int current = heights[at(x, y)];
            if ((color & 0xf8) == 0x38 && draw() % 6 == 0) current += draw() % 8 + 32;
            const int right = x < width - 2 ? heights[at(x + 2, y)] : current;
            const int above = y > 1 ? heights[at(x, y - 2)] : current;
            int light = shade(current, right, above, horizon);
            int kind = current < 0 ? 0x40 : current >= 640 ? 0x10 : slope > 100 ? 0x20 : 0;
            if (!kind) kind = color & 0xf8;
            else if (kind == 0x20 && light > 2) light -= draw() % 2;
            color = uint8_t(kind | light);
        }
    }
}

//00469b2c; mark a2x2 footprint and darken its left neighbor. Equal-height
// ties select the LAST neighbor in row-major order, not the first.
void Work::rivers() {
    for (int y = 0; y < height; ++y) for (int x = 0; x < width; ++x) {
        if (tile(x / 32, y / 32).terrain == 6 && draw() % 300 != 0) continue;
        if (heights[at(x, y)] != 1 || draw() % 40 != 0) continue;
        int px = x, py = y, level = heights[at(x, y)];
        size_t steps = 0;
        while (level >= 0) {
            int best = 0, nx = 0, ny = 0;
            for (int cy = py - 1; cy <= py + 1; ++cy) for (int cx = px - 1; cx <= px + 1; ++cx) {
                if ((cx == px && cy == py) || !inside(cx, cy)) continue;
                const int candidate = heights[at(cx, cy)];
                if (candidate > level - 2 && candidate >= best && (out.colorMap[at(cx, cy)] & 0xf8) != 0x40) {
                    best = candidate; nx = cx; ny = cy;
                }
            }
            if (!best) break;
            // Each chosen next pixel was not a river. This finite upper bound
            // is defensive and does not truncate any defined original path.
            if (++steps > heights.size()) throw std::runtime_error("Long-range river traversal exceeded its finite pixel domain");
            for (int oy = 0; oy <= 1; ++oy) for (int ox = 0; ox <= 1; ++ox) if (inside(px + ox, py + oy)) {
                auto& color = out.colorMap[at(px + ox, py + oy)]; color = uint8_t((color & 7) | 0x40);
            }
            if (px) {
                auto& left = out.colorMap[at(px - 1, py)];
                left = uint8_t((left & 0xf8) | std::max(0, int(left & 7) - 1));
            }
            px = nx; py = ny; level = best;
        }
    }
}

//0046a700: normalize signed heights, then keep the low byte, exactly as the
// original in-place compaction. Wasteland-only denominator also consumes RNG.
void Work::scale() {
    int divisor = 127;
    for (const int h : heights) divisor = std::max(divisor, h);
    bool mountains = false, wasteland = false;
    for (const auto& record : d.territories) {
        mountains |= record.data.terrain == 4; wasteland |= record.data.terrain == 5;
    }
    if (!mountains && wasteland) divisor = draw() % 400 + 900;
    out.heightMap.resize(heights.size());
    for (size_t i = 0; i < heights.size(); ++i)
        out.heightMap[i] = uint8_t(std::max(0, sar2(int(heights[i]) * 127 / divisor)));
}

//0046f5d4's successful offline branch. Window callbacks are intentionally NOT
// invoked; the report carries their semantic focus request for a native UI.
bool Work::selection() {
    const int local = d.options.localPlayer;
    if (local < 0 || local >= kMaxPlayers) return fail(error, "World presentation requires an offline local player0..6");
    int selected = d.players[size_t(local)].homeTerritory;
    auto focus = [&](int territory) {
        auto& t = d.territories[size_t(territory - 1)].data;
        if (!t.numTiles) return fail(error, "World presentation home territory has no first tile");
        const auto& target = listedTile(t, 0);
        const int next = target.territory;
        if (next <= 0 || size_t(next) > d.territories.size()) return fail(error, "World presentation focus tile has no live territory");
        //0045dfd4 updates selection to the territory of the target tile, even
        // when fallback previously selected the first nonempty territory.
        if (next != selected) {
            for (auto& record : d.territories) record.data.flags &= ~2u;
            if (selected > 0) d.territories[size_t(selected - 1)].data.flags &= ~1u;
            selected = next; d.territories[size_t(selected - 1)].data.flags |= 1;
        }
        out.cameraTargetValid = true; out.cameraTileX = target.x; out.cameraTileY = target.y;
        return true;
    };
    if (selected == 0 || selected == -1) {
        for (size_t i = 0; i < d.territories.size(); ++i) {
            const auto& t = d.territories[i].data;
            if (!t.numTiles) continue;
            if (selected == 0 || selected == -1) selected = int(i + 1);
            if (t.owner == local) {
                if (!focus(int(i + 1))) return false;
                d.territories[size_t(selected - 1)].data.flags |= 1;
                break;
            }
        }
        // An empty map keeps the original sentinel selection instead of a
        // native out-of-allocation pointer; -1 has no owned sentinel and fails.
        if (selected == -1) return fail(error, "World presentation has an unresolved negative home selection");
    } else {
        if (selected < 1 || size_t(selected) > d.territories.size()) return fail(error, "World presentation home territory is out of range");
        if (!focus(selected)) return false;
        d.territories[size_t(selected - 1)].data.flags |= 3;
    }
    out.selectedTerritory = uint32_t(selected); out.selectionReset = true;
    return true;
}

bool validateDomain(const save::Document& d, save::Error& error) {
    if (!save::validate(d, error)) return false;
    if (d.header.isMap) return fail(error, "World presentation load requires a saved game, not an editor map");
    // Document validation establishes dimensions, vector size and coordinate
    // references. The algorithm additionally dereferences each nonsea center.
    for (const auto& t : d.territories) if (t.data.terrain && t.data.centerTile != -1)
        if (t.data.centerTile < 0 || t.data.centerTile >= t.data.numTiles)
            return fail(error, "World presentation center tile is outside its territory list");
    return true;
}
} // namespace

bool rebuildLoadWorldPresentation(const save::Document& source,
    const LoadWorldPresentationContext& context, save::Document& destination,
    LoadWorldPresentationReport& report, save::Error& error) {
    try {
        if (!save::validate(source, error)) return false;
        LoadWorldPresentationReport result;
        result.changedWorld = std::memcmp(&source.world, &context.previousWorld, sizeof(WorldParams)) != 0;
        result.rngAfter = context.rng; result.shadingSlopeAfter = context.shadingSlope;
        SessionRng checked;
        if (!checked.restore(context.rng, error)) return false;
        auto candidate = std::make_unique<save::Document>(source);
        if (result.changedWorld) {
            if (!validateDomain(*candidate, error)) return false;
            if (!context.rng.initialized) return fail(error, "Changed world requires an explicit initialized RNG snapshot");
            Work work(*candidate, result, error, context.shadingSlope);
            if (!work.rng.restore(context.rng, error)) return false;
            RngEvent seed;
            if (!work.rng.apply({RngOperation::SeedRtl, 0, source.world.rngSeed, {}}, seed, error)) return false;
            auto phase = [&](size_t index, auto&& operation) {
                const uint64_t before = work.rng.snapshot().counters.long31;
                operation(); result.long31ByPhase[index] = work.rng.snapshot().counters.long31 - before;
            };
            phase(0, [&] { work.terrain(); });
            // Validation must happen AFTER terrain reconstruction; arbitrary
            // archived graphic terrain may be replaced by a defined value.
            for (const auto& tile : candidate->tiles) if (tile.terrain > 6)
                return fail(error, "World presentation graphic terrain is outside table0..6");
            phase(1, [&] { work.generateHeights(); }); work.flatten();
            phase(2, [&] { work.colors(); }); phase(3, [&] { work.shading(); });
            phase(4, [&] { work.rivers(); }); phase(5, [&] { work.scale(); });
            result.width = uint32_t(work.width); result.height = uint32_t(work.height); result.mapRebuilt = true;
            if (source.world.worldType <= 6)
                result.palettePatches.push_back({0x18, unhex(kTheme[source.world.worldType])});
            result.palettePatches.push_back({0, unhex(kPalettePrefix)});
            result.palettePatches.push_back({0x218, unhex(kPaletteSuffix)});
            // Literal AND0x0000fff0 verified at00461b41, not merely flags&~15.
            for (auto& t : candidate->territories) t.data.flags &= 0xfff0u;
            if (!work.selection()) return false;
            result.windowRecreationRequested = result.paletteApplicationRequested = true;
            result.rngAfter = work.rng.snapshot(); result.shadingSlopeAfter = work.slope;
        }
        if (!save::validate(*candidate, error)) return false;
        destination = std::move(*candidate); report = std::move(result); error = {}; return true;
    } catch (const RngFailure&) { return false; }
    catch (const std::bad_alloc&) { error = {save::ErrorCode::Limit, 0, "Insufficient memory for long-range world presentation"}; }
    catch (const std::length_error&) { error = {save::ErrorCode::Limit, 0, "World presentation exceeds allocation limits"}; }
    catch (const std::exception& exception) { error = {save::ErrorCode::InvalidState, 0, exception.what()}; }
    return false;
}
} // namespace dl2::simulation
