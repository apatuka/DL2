// Synthetic filesystem tests; no original installation or SDL is required.
// Checks remain active in Release builds, and all files live in an owned directory.
#include "game/save_files.h"

#include <chrono>
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

void require(bool value, const char* message) {
    if (!value) throw std::runtime_error(message);
}

class TestDirectory {
public:
    explicit TestDirectory(const fs::path& parent) {
        const auto absoluteParent = fs::absolute(parent);
        require(fs::is_directory(absoluteParent), "test parent must already be a directory");
        const auto nonce = std::chrono::steady_clock::now().time_since_epoch().count();
        for (int attempt = 0; attempt < 16; ++attempt) {
            const auto candidate = absoluteParent /
                ("save-files-test-" + std::to_string(nonce) + "-" + std::to_string(attempt));
            if (fs::create_directory(candidate)) {
                path = candidate;
                return;
            }
        }
        throw std::runtime_error("cannot create exclusive test directory");
    }

    ~TestDirectory() {
        // Every test fixture is a direct child of this exclusively-created path.
        // Never recurse or remove its caller-owned parent directory.
        std::error_code error;
        auto iterator = fs::directory_iterator(path, error);
        while (!error && iterator != fs::directory_iterator{}) {
            std::error_code ignored;
            fs::remove(iterator->path(), ignored);
            iterator.increment(error);
        }
        fs::remove(path, error);
    }

    fs::path path;
};

std::unique_ptr<save::Document> fixture() {
    auto document = std::make_unique<save::Document>();
    std::memcpy(document->header.text, save::kHeaderText, sizeof(save::kHeaderText));
    document->header.version = kSaveVersion;
    document->header.minusOne = -1;
    document->header.isMap = 1;
    document->header.pad[7] = 0x91;
    document->world.width = 2;
    document->world.height = 1;
    document->world.numTerritories = 1;
    document->world.rngSeed = 0x01234567;
    document->mapTerritories.resize(1);
    document->mapTerritories[0].terrain = 1;
    document->mapTerritories[0].sites[0] = {1, 4, 0xee};
    document->tiles.resize(2);
    for (size_t i = 0; i < document->tiles.size(); ++i) {
        document->tiles[i].x = uint8_t(i);
        document->tiles[i].territory = 1;
        document->tiles[i].terrain = 1;
    }
    document->trailing = {0xde, 0xad, 0x00, 0xff};
    return document;
}

std::vector<uint8_t> encoded(const save::Document& document) {
    save::Error error;
    std::vector<uint8_t> bytes;
    if (!save::encode(document, bytes, error)) throw std::runtime_error(error.message);
    return bytes;
}

void writeRaw(const fs::path& path, const std::vector<uint8_t>& bytes) {
    std::ofstream file(path, std::ios::binary);
    if (!bytes.empty())
        file.write(reinterpret_cast<const char*>(bytes.data()), std::streamsize(bytes.size()));
    file.close();
    require(bool(file), "cannot create test fixture");
}

std::vector<uint8_t> readRaw(const fs::path& path) {
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    require(bool(file), "cannot open generated file");
    const auto length = file.tellg();
    require(length >= 0, "cannot size generated file");
    std::vector<uint8_t> bytes(static_cast<size_t>(length));
    file.seekg(0);
    if (!bytes.empty())
        file.read(reinterpret_cast<char*>(bytes.data()), std::streamsize(bytes.size()));
    require(bool(file), "cannot read generated file");
    return bytes;
}

void append32(std::vector<uint8_t>& bytes, uint32_t value) {
    for (unsigned shift = 0; shift < 32; shift += 8) bytes.push_back(uint8_t(value >> shift));
}

save::Error previousError() { return {save::ErrorCode::Io, 99, "previous failure"}; }

void requireCleared(const save::Error& error) {
    require(error.code == save::ErrorCode::None && error.offset == 0 && error.message.empty(),
            "success must clear all error fields");
}

void requireNoStagedFiles(const fs::path& directory) {
    for (const auto& entry : fs::directory_iterator(directory))
        require(entry.path().filename().u8string().find(u8".dl2tmp-") == std::u8string::npos,
                "publication left a temporary staging file");
}

void filesAndFailures(const fs::path& directory) {
    auto source = fixture();
    const auto expected = encoded(*source);
    // Exercise the native filesystem::path API rather than a narrow argv conversion.
    const auto path = directory / fs::path(u8"original-\u00f1-\u4e16.sav");
    save::Error error = previousError();
    require(save::writeDocumentCopy(path, *source, error), "write new Unicode-path document");
    requireCleared(error);
    require(readRaw(path) == expected, "filesystem write changed serialized bytes");
    requireNoStagedFiles(directory);

    auto target = std::make_unique<save::Document>();
    error = previousError();
    require(save::readDocument(path, *target, error), "read Unicode-path document");
    requireCleared(error);
    require(encoded(*target) == expected, "filesystem read changed serialized bytes");
    source->header.pad[7] ^= 0xff;
    require(!save::writeDocumentCopy(path, *source, error), "existing output was accepted");
    require(error.code == save::ErrorCode::Io && !error.message.empty(), "missing overwrite diagnostic");
    require(readRaw(path) == expected, "failed write replaced an existing save");
    requireNoStagedFiles(directory);

    const auto before = encoded(*target);
    auto rejected = [&](const fs::path& input, save::ErrorCode code) {
        error = previousError();
        require(!save::readDocument(input, *target, error), "invalid input was accepted");
        require(error.code == code && !error.message.empty(), "wrong input failure diagnostic");
        require(encoded(*target) == before, "failed file read changed destination document");
    };
    rejected(directory / "missing.sav", save::ErrorCode::Io);
    const auto invalid = directory / "invalid.sav";
    writeRaw(invalid, {});
    rejected(invalid, save::ErrorCode::Truncated);
    auto wrongMagic = expected;
    wrongMagic[0] ^= 0xff;
    writeRaw(invalid, wrongMagic);
    rejected(invalid, save::ErrorCode::InvalidHeader);
    writeRaw(invalid, {expected.begin(), expected.begin() + 91});
    rejected(invalid, save::ErrorCode::Truncated);
    const auto tooLarge = directory / "too-large.sav";
    {
        std::ofstream file(tooLarge, std::ios::binary);
        file.seekp(std::streamoff(save::kMaxFileBytes));
        file.put('\0');
        file.close();
        require(bool(file), "cannot create oversized test fixture");
    }
    rejected(tooLarge, save::ErrorCode::Limit);

    source->world.width = 0;
    const auto badOutput = directory / "must-not-be-created.sav";
    require(!save::writeDocumentCopy(badOutput, *source, error), "invalid document was written");
    require(error.code == save::ErrorCode::Limit && !fs::exists(badOutput),
            "invalid encode should fail before output creation");
    source->world.width = 2;
    require(!save::writeDocumentCopy(directory / "absent-parent" / "copy.sav", *source, error),
            "output under missing parent was accepted");
    require(error.code == save::ErrorCode::Io, "wrong missing output parent diagnostic");
    require(!save::writeDocumentCopy({}, *source, error), "empty output path was accepted");
    require(error.code == save::ErrorCode::Io, "wrong empty output path diagnostic");
    requireNoStagedFiles(directory);
    require(readRaw(path) == expected, "failure checks changed original file");

    error = previousError();
    require(save::readDocument(path, *target, error), "valid read must recover after failure");
    requireCleared(error);
}

void archivesAndFailures(const fs::path& directory) {
    auto source = fixture();
    const auto expected = encoded(*source);
    const auto base = directory / fs::path(u8"levels-\u00f1-\u4e16");
    auto indexPath = base; indexPath += ".HDX";
    auto dataPath = base; dataPath += ".HDD";
    std::vector<uint8_t> index;
    append32(index, 1);
    for (const char value : std::string("EXACT8NM")) index.push_back(uint8_t(value));
    append32(index, 3); // Nonzero offset checks the entry-length word's positioning.
    std::vector<uint8_t> data = {0x9a, 0, 0xbc};
    append32(data, uint32_t(expected.size()));
    data.insert(data.end(), expected.begin(), expected.end());
    writeRaw(indexPath, index);
    writeRaw(dataPath, data);

    auto target = fixture();
    target->header.pad[7] = 0xff;
    save::Error error = previousError();
    require(save::readScenario(base, "EXACT8NM", *target, error), "read exact eight-byte archive entry");
    requireCleared(error);
    require(encoded(*target) == expected, "archive read changed serialized bytes");
    const auto before = encoded(*target);
    auto rejected = [&](std::string_view name, save::ErrorCode code) {
        require(!save::readScenario(base, name, *target, error), "invalid scenario was accepted");
        require(error.code == code && !error.message.empty(), "wrong archive failure diagnostic");
        require(encoded(*target) == before, "failed archive read changed destination document");
    };
    rejected("exact8nm", save::ErrorCode::Io);
    rejected("../EXACT8NM", save::ErrorCode::Io);
    writeRaw(indexPath, {1, 0, 0});
    rejected("EXACT8NM", save::ErrorCode::Truncated);
    writeRaw(indexPath, {0xff, 0xff, 0xff, 0xff});
    rejected("EXACT8NM", save::ErrorCode::Truncated);
    writeRaw(indexPath, index);
    writeRaw(dataPath, {0, 0, 0, 0});
    rejected("EXACT8NM", save::ErrorCode::Truncated);
    writeRaw(dataPath, {data.begin(), data.end() - 1});
    rejected("EXACT8NM", save::ErrorCode::Truncated);
    auto invalidSave = data;
    invalidSave[7] ^= 0xff;
    writeRaw(dataPath, invalidSave);
    rejected("EXACT8NM", save::ErrorCode::InvalidHeader);
    writeRaw(dataPath, data);
    error = previousError();
    require(save::readScenario(base, "EXACT8NM", *target, error), "archive recovers after failure");
    requireCleared(error);
    require(readRaw(indexPath) == index && readRaw(dataPath) == data, "archive reading modified inputs");
    requireNoStagedFiles(directory);
}
} // namespace

int main(int argc, char** argv) {
    try {
        const TestDirectory directory(argc > 1 ? fs::path(argv[1]) : fs::temp_directory_path());
        filesAndFailures(directory.path);
        archivesAndFailures(directory.path);
        std::cout << "save files: exact read/write, Unicode paths, archives, bounds, transactional failures, "
                     "overwrite protection and staging cleanup passed\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "save files failure: " << error.what() << '\n';
        return 1;
    }
}
