// Console access to the physical save codec. Does NOT activate a running game.
#include "game/save_document.h"

#include <charconv>
#include <chrono>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

namespace {
namespace fs = std::filesystem;
using namespace dl2;

std::vector<uint8_t> readFile(const fs::path& path) {
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file) throw std::runtime_error("cannot open input: " + path.string());
    const auto length = file.tellg();
    if (length < 0 || static_cast<uint64_t>(length) > save::kMaxFileBytes)
        throw std::runtime_error("input exceeds the 16 MiB limit or cannot be sized");
    std::vector<uint8_t> bytes(static_cast<size_t>(length));
    file.seekg(0);
    if (!bytes.empty() && !file.read(reinterpret_cast<char*>(bytes.data()), std::streamsize(bytes.size())))
        throw std::runtime_error("short input read");
    return bytes;
}

uint32_t u32(const std::vector<uint8_t>& data, size_t offset) {
    if (offset > data.size() || data.size() - offset < 4) throw std::runtime_error("truncated HDX/HDD");
    return uint32_t(data[offset]) | (uint32_t(data[offset + 1]) << 8) |
           (uint32_t(data[offset + 2]) << 16) | (uint32_t(data[offset + 3]) << 24);
}

std::vector<uint8_t> readEntry(const std::string& base, const std::string& name) {
    const auto index = readFile(base + ".HDX");
    const uint32_t count = u32(index, 0);
    if (count > (index.size() - 4) / 12) throw std::runtime_error("invalid HDX entry count");
    for (size_t i = 0; i < count; ++i) {
        const size_t pos = 4 + i * 12;
        size_t n = 0;
        while (n < 8 && index[pos + n]) ++n;
        if (std::string(reinterpret_cast<const char*>(index.data() + pos), n) != name) continue;
        const auto data = readFile(base + ".HDD");
        const size_t offset = u32(index, pos + 8);
        const size_t size = u32(data, offset);
        const size_t begin = offset + 4; // u32() already proved these four bytes exist.
        if (size > data.size() - begin) throw std::runtime_error("truncated HDD entry");
        return {data.begin() + begin, data.begin() + begin + size};
    }
    throw std::runtime_error("HDX entry not found: " + name);
}

// Stage a complete sibling file, then publish with an exclusive hard link. Never
// truncate/rename an existing save. Failure leaves an existing destination intact.
// This is atomic publication, not a power-loss durability guarantee. A filesystem
// without hard-link support fails safely; there is no unsafe overwrite fallback.
void writeNewFile(const fs::path& destination, const std::vector<uint8_t>& bytes) {
    if (destination.filename().empty()) throw std::runtime_error("output must be a new filename");
    fs::path temporary;
    std::FILE* file = nullptr;
    const auto nonce = std::chrono::steady_clock::now().time_since_epoch().count();
    for (int attempt = 0; attempt < 16 && !file; ++attempt) {
        temporary = destination;
        temporary += ".dl2tmp-" + std::to_string(nonce) + "-" + std::to_string(attempt);
#ifdef _WIN32
        file = _wfopen(temporary.c_str(), L"wbx");
#else
        file = std::fopen(temporary.c_str(), "wbx");
#endif
    }
    if (!file) throw std::runtime_error("cannot create temporary output beside destination");
    struct Cleanup {
        fs::path path;
        ~Cleanup() { std::error_code ignored; fs::remove(path, ignored); }
    } cleanup{temporary};
    const bool written = std::fwrite(bytes.data(), 1, bytes.size(), file) == bytes.size();
    const bool closed = std::fclose(file) == 0;
    if (!written || !closed) throw std::runtime_error("output write failed");
    std::error_code error;
    fs::create_hard_link(temporary, destination, error);
    if (error) throw std::runtime_error("output must not exist and filesystem must support hard links: " + error.message());
}

void inspect(const save::Document& d) {
    size_t queues = 0;
    for (const auto& t : d.territories) for (const auto& q : t.queues) queues += q.size();
    std::cout << "{\"version\":" << d.header.version << ",\"is_map\":" << d.header.isMap
              << ",\"turn\":" << d.options.turn << ",\"players\":" << d.options.numPlayers
              << ",\"local_player\":" << d.options.localPlayer
              << ",\"width\":" << int(d.world.width) << ",\"height\":" << int(d.world.height)
              << ",\"territories\":" << d.world.numTerritories
              << ",\"buildings\":" << d.buildings.size() << ",\"armies\":" << d.armies.size()
              << ",\"events\":" << d.events.size() << ",\"local_values\":" << d.localList.size()
              << ",\"queue_records\":" << queues << ",\"trailing_bytes\":" << d.trailing.size()
              << ",\"minister_nodes\":[";
    for (int p = 0; p < kMaxPlayers; ++p)
        std::cout << (p ? "," : "") << (d.ministerJobs[p].empty() ? 0 : d.ministerJobs[p].size() - 1);
    std::cout << "],\"credits\":[";
    for (int p = 0; p < kMaxPlayers; ++p) std::cout << (p ? "," : "") << d.players[p].credits;
    std::cout << "]}\n";
}

int32_t number(const char* text) {
    int32_t value = 0;
    const char* end = text + std::strlen(text);
    const auto result = std::from_chars(text, end, value);
    if (result.ec != std::errc{} || result.ptr != end) throw std::runtime_error("expected a signed 32-bit integer");
    return value;
}

int usage() {
    std::cout << "Physical SAV/CPN codec; no gameplay activation. Outputs must be new files.\n"
                 "  dl2save inspect <file>\n"
                 "  dl2save roundtrip <input> <new-output>\n"
                 "  dl2save set-credits <input> <new-output> <player 0..6> <int32 credits>\n"
                 "  dl2save inspect-archive <HDX/HDD-base> <entry>\n"
                 "  dl2save extract-save <HDX/HDD-base> <entry> <new-output>\n";
    return 2;
}
} // namespace

int main(int argc, char** argv) {
    try {
        if (argc == 2 && std::string(argv[1]) == "--help") { usage(); return 0; }
        if (argc < 3) return usage();
        const std::string command = argv[1];
        const bool archive = command == "inspect-archive" || command == "extract-save";
        if (!((command == "inspect" && argc == 3) || (command == "roundtrip" && argc == 4) ||
              (command == "set-credits" && argc == 6) || (command == "inspect-archive" && argc == 4) ||
              (command == "extract-save" && argc == 5))) return usage();
        const auto bytes = archive ? readEntry(argv[2], argv[3]) : readFile(argv[2]);
        auto doc = std::make_unique<save::Document>();
        save::Error error;
        if (!save::decode(bytes, *doc, error))
            throw std::runtime_error("decode at byte " + std::to_string(error.offset) + ": " + error.message);
        if (command == "inspect" || command == "inspect-archive") { inspect(*doc); return 0; }
        if (command == "set-credits") {
            const int player = number(argv[4]);
            if (doc->header.isMap || player < 0 || player >= kMaxPlayers)
                throw std::runtime_error("credits require a saved game and a player index 0..6");
            doc->players[player].credits = number(argv[5]);
        }
        std::vector<uint8_t> encoded;
        if (!save::encode(*doc, encoded, error)) throw std::runtime_error("encode: " + error.message);
        writeNewFile(argv[command == "extract-save" ? 4 : 3], encoded);
        inspect(*doc);
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "dl2save: " << error.what() << '\n';
        return 1;
    }
}
