// Binary adapter for the real session RNG. Reference bytes live outside this executable.
#include "game/session_rng.h"
#include <array>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>

int main(int argc, char** argv) {
    try {
        if (argc != 3) throw std::runtime_error("usage: golden_probe input.bin new-output.bin");
        std::ifstream input(argv[1], std::ios::binary);
        std::array<unsigned char, 9> bytes{};
        if (!input.read(reinterpret_cast<char*>(bytes.data()), bytes.size()) || input.peek() != EOF)
            throw std::runtime_error("expected operation byte, LE32 seed and LE32 count");
        auto word = [&](int at) {
            return uint32_t(bytes[at]) | uint32_t(bytes[at+1]) << 8 |
                   uint32_t(bytes[at+2]) << 16 | uint32_t(bytes[at+3]) << 24;
        };
        using namespace dl2::simulation;
        const RngOperation ops[]{RngOperation::Rand15, RngOperation::Long31, RngOperation::Secondary15};
        if (bytes[0] >= std::size(ops) || word(5) > 1000000)
            throw std::runtime_error("invalid operation/count");
        if (std::filesystem::exists(argv[2])) throw std::runtime_error("output must be new");
        SessionRng rng; dl2::save::Error error;
        if (!rng.initialize(word(1), error)) throw std::runtime_error(error.message);
        std::ofstream output(argv[2], std::ios::binary);
        for (uint32_t i = 0; i < word(5); ++i) {
            RngEvent event;
            if (!rng.apply({ops[bytes[0]]}, event, error)) throw std::runtime_error(error.message);
            for (int shift = 0; shift < 32; shift += 8) output.put(char((event.value >> shift) & 255));
        }
        output.close();
        if (!output) throw std::runtime_error("cannot write output");
        return 0;
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
