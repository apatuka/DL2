#include "game/save_files.h"

#include <chrono>
#include <cstdio>
#include <fstream>
#include <new>
#include <stdexcept>
#include <system_error>
#include <utility>

namespace dl2::save {
namespace {
namespace fs = std::filesystem;

bool fail(Error& error, ErrorCode code, size_t offset, std::string message) {
    error = {code, offset, std::move(message)};
    return false;
}

// Keep exceptions from filesystem conversion/allocation outside the UI and CLI.
// The codec itself reports format errors without replacing the destination.
template<class Operation>
bool ioOperation(Operation&& operation, Error& error) {
    try {
        return operation();
    } catch (const std::bad_alloc&) {
        return fail(error, ErrorCode::Limit, 0, "Insufficient memory while accessing save file");
    } catch (const std::length_error&) {
        return fail(error, ErrorCode::Limit, 0, "Invalid allocation size while accessing save file");
    } catch (const std::exception& exception) {
        return fail(error, ErrorCode::Io, 0, exception.what());
    }
}

bool readFile(const fs::path& path, std::vector<uint8_t>& bytes, Error& error) {
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file) return fail(error, ErrorCode::Io, 0, "Cannot open input file");
    const auto length = file.tellg();
    if (length < 0) return fail(error, ErrorCode::Io, 0, "Cannot determine input file size");
    if (static_cast<uint64_t>(length) > kMaxFileBytes)
        return fail(error, ErrorCode::Limit, 0, "Input exceeds the 16 MiB resource limit");
    bytes.resize(static_cast<size_t>(length));
    file.seekg(0);
    if (!file || (!bytes.empty() &&
        !file.read(reinterpret_cast<char*>(bytes.data()), std::streamsize(bytes.size()))))
        return fail(error, ErrorCode::Io, 0, "Short input file read");
    return true;
}

bool readU32(std::span<const uint8_t> data, size_t offset, uint32_t& value, Error& error) {
    if (offset > data.size() || data.size() - offset < 4)
        return fail(error, ErrorCode::Truncated, offset, "Truncated HDX/HDD word");
    value = uint32_t(data[offset]) | (uint32_t(data[offset + 1]) << 8) |
            (uint32_t(data[offset + 2]) << 16) | (uint32_t(data[offset + 3]) << 24);
    return true;
}

struct StagedFile {
    fs::path path;
    std::FILE* stream = nullptr;
    bool owned = false;

    ~StagedFile() {
        if (stream) std::fclose(stream);
        if (owned) {
            std::error_code ignored;
            fs::remove(path, ignored);
        }
    }
};

bool writeNewFile(const fs::path& destination, const std::vector<uint8_t>& bytes,
                  Error& error) {
    if (destination.filename().empty())
        return fail(error, ErrorCode::Io, 0, "Output must be a new filename");
    StagedFile temporary;
    const auto nonce = std::chrono::steady_clock::now().time_since_epoch().count();
    for (int attempt = 0; attempt < 16 && !temporary.stream; ++attempt) {
        temporary.path = destination;
        temporary.path += ".dl2tmp-" + std::to_string(nonce) + "-" + std::to_string(attempt);
#ifdef _WIN32
        temporary.stream = _wfopen(temporary.path.c_str(), L"wbx");
#else
        temporary.stream = std::fopen(temporary.path.c_str(), "wbx");
#endif
        temporary.owned = temporary.stream != nullptr;
    }
    if (!temporary.stream)
        return fail(error, ErrorCode::Io, 0, "Cannot create temporary output beside destination");
    const bool written = bytes.empty() ||
        std::fwrite(bytes.data(), 1, bytes.size(), temporary.stream) == bytes.size();
    const bool closed = std::fclose(temporary.stream) == 0;
    temporary.stream = nullptr;
    if (!written || !closed)
        return fail(error, ErrorCode::Io, 0, "Output write failed");
    std::error_code filesystemError;
    fs::create_hard_link(temporary.path, destination, filesystemError);
    if (filesystemError)
        return fail(error, ErrorCode::Io, 0,
                    "Output must not exist and filesystem must support hard links: " +
                    filesystemError.message());
    error = {};
    return true;
}

} // namespace

bool readDocument(const fs::path& path, Document& destination, Error& error) {
    return ioOperation([&] {
        std::vector<uint8_t> bytes;
        return readFile(path, bytes, error) && decode(bytes, destination, error);
    }, error);
}

bool readScenario(const fs::path& archiveBase, std::string_view entry,
                  Document& destination, Error& error) {
    return ioOperation([&] {
        auto indexPath = archiveBase;
        indexPath += ".HDX";
        std::vector<uint8_t> index;
        if (!readFile(indexPath, index, error)) return false;
        uint32_t count = 0;
        if (!readU32(index, 0, count, error)) return false;
        if (count > (index.size() - 4) / 12)
            return fail(error, ErrorCode::Truncated, 0, "Invalid HDX entry count");
        for (size_t i = 0; i < count; ++i) {
            const size_t position = 4 + i * 12;
            size_t length = 0;
            while (length < 8 && index[position + length] != 0) ++length;
            const std::string_view name(reinterpret_cast<const char*>(index.data() + position), length);
            if (name != entry) continue;
            auto dataPath = archiveBase;
            dataPath += ".HDD";
            std::vector<uint8_t> data;
            if (!readFile(dataPath, data, error)) return false;
            uint32_t offset = 0, size = 0;
            if (!readU32(index, position + 8, offset, error) ||
                !readU32(data, offset, size, error)) return false;
            const size_t begin = size_t(offset) + 4; // readU32 proved this is inside data.
            if (size > data.size() - begin)
                return fail(error, ErrorCode::Truncated, begin, "Truncated HDD entry");
            return decode(std::span<const uint8_t>(data).subspan(begin, size), destination, error);
        }
        return fail(error, ErrorCode::Io, 0, "HDX entry not found: " + std::string(entry));
    }, error);
}

bool writeDocumentCopy(const fs::path& destination, const Document& document, Error& error) {
    return ioOperation([&] {
        std::vector<uint8_t> bytes;
        return encode(document, bytes, error) && writeNewFile(destination, bytes, error);
    }, error);
}

} // namespace dl2::save
