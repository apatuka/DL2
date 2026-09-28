// Console access to the physical save codec. Does NOT activate a running game.
#include "game/save_files.h"

#include <charconv>
#include <cstring>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

namespace {
using namespace dl2;

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
        auto doc = std::make_unique<save::Document>();
        save::Error error;
        const bool loaded = archive ? save::readScenario(argv[2], argv[3], *doc, error)
                                    : save::readDocument(argv[2], *doc, error);
        if (!loaded)
            throw std::runtime_error("read at byte " + std::to_string(error.offset) + ": " + error.message);
        if (command == "inspect" || command == "inspect-archive") { inspect(*doc); return 0; }
        if (command == "set-credits") {
            const int player = number(argv[4]);
            if (doc->header.isMap || player < 0 || player >= kMaxPlayers)
                throw std::runtime_error("credits require a saved game and a player index 0..6");
            doc->players[player].credits = number(argv[5]);
        }
        if (!save::writeDocumentCopy(argv[command == "extract-save" ? 4 : 3], *doc, error))
            throw std::runtime_error("write: " + error.message);
        inspect(*doc);
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "dl2save: " << error.what() << '\n';
        return 1;
    }
}
