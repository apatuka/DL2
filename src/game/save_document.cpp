// Lossless physical SAV/CPN codec. Unlike the historical LoadGame port, this
// module never activates the game, fixes up pointer words, or changes globals.
#include "game/save_document.h"

#include <bit>
#include <cstring>
#include <limits>
#include <memory>
#include <new>
#include <stdexcept>
#include <string_view>
#include <type_traits>
#include <utility>

namespace dl2::save {
namespace {

static_assert(std::endian::native == std::endian::little,
              "The packed original-game structures require a little-endian host");
static_assert(sizeof(kHeaderText) == sizeof(SaveHeader::text));
static_assert(std::is_nothrow_move_assignable_v<Document>);
constexpr size_t kQueueSavedBytes = 0x30;
constexpr uint32_t kLocalListEnd = 0xffffffffu;

bool fail(Error& error, ErrorCode code, size_t offset, std::string message) {
    error = {code, offset, std::move(message)};
    return false;
}

class Reader {
public:
    Reader(std::span<const uint8_t> bytes, Error& error) : bytes_(bytes), error_(error) {}

    size_t offset() const { return offset_; }
    size_t remaining() const { return bytes_.size() - offset_; }

    bool require(size_t length, std::string_view block) {
        if (length > remaining())
            return fail(error_, ErrorCode::Truncated, offset_,
                        std::string(block) + ": need " + std::to_string(length) +
                        " bytes, only " + std::to_string(remaining()) + " remain");
        return true;
    }

    bool readBytes(void* destination, size_t length, std::string_view block) {
        if (!require(length, block)) return false;
        // A zero-length vector may have a null data() pointer.
        if (length != 0) std::memcpy(destination, bytes_.data() + offset_, length);
        offset_ += length;
        return true;
    }

    template<class T>
    bool read(T& destination, std::string_view block) {
        static_assert(std::is_trivially_copyable_v<T>);
        return readBytes(&destination, sizeof(T), block);
    }

    template<class T>
    bool readVector(std::vector<T>& destination, size_t count, std::string_view block) {
        static_assert(std::is_trivially_copyable_v<T>);
        // Check before multiplication and allocation, even for validated counts.
        if (count > remaining() / sizeof(T))
            return fail(error_, ErrorCode::Truncated, offset_,
                        std::string(block) + ": records exceed remaining file bytes");
        destination.resize(count);
        return readBytes(destination.data(), count * sizeof(T), block);
    }

private:
    std::span<const uint8_t> bytes_;
    Error& error_;
    size_t offset_ = 0;
};

class Writer {
public:
    explicit Writer(Error& error) : error_(error) {}

    bool writeBytes(const void* source, size_t length, std::string_view block) {
        if (length > kMaxFileBytes - bytes.size())
            return fail(error_, ErrorCode::Limit, bytes.size(),
                        std::string(block) + ": encoded file exceeds 16 MiB limit");
        if (length != 0) {
            const auto* begin = static_cast<const uint8_t*>(source);
            bytes.insert(bytes.end(), begin, begin + length);
        }
        return true;
    }

    template<class T>
    bool write(const T& source, std::string_view block) {
        static_assert(std::is_trivially_copyable_v<T>);
        return writeBytes(&source, sizeof(T), block);
    }

    template<class T>
    bool writeVector(const std::vector<T>& source, std::string_view block) {
        static_assert(std::is_trivially_copyable_v<T>);
        if (source.size() > (kMaxFileBytes - bytes.size()) / sizeof(T))
            return fail(error_, ErrorCode::Limit, bytes.size(),
                        std::string(block) + ": encoded records exceed 16 MiB limit");
        return writeBytes(source.data(), source.size() * sizeof(T), block);
    }

    std::vector<uint8_t> bytes;

private:
    Error& error_;
};

bool headerSupported(const SaveHeader& header, Error& error) {
    if (std::memcmp(header.text, kHeaderText, sizeof(kHeaderText)) != 0) {
        // These are recognizable formats, but their different physical layouts
        // are deliberately outside the currently tested codec contract.
        constexpr std::string_view oldHeaders[] = {
            "Deadlock 2  (c)1997 Accolade Inc.  All Rights Reserved.\nPre-release version S (7/21/97)",
            "Deadlock 2  (c)1997 Accolade Inc.  All Rights Reserved.\nPre-release version T (7/31/97)",
            "Deadlock 2  (c)1997 Accolade Inc.  All Rights Reserved.\nPre-release version U (8/04/97)",
            "Deadlock 2  (c)1997 Accolade Inc.  All Rights Reserved.\nPre-release version V (9/05/97)"
        };
        for (const auto old : oldHeaders)
            if (old.size() <= sizeof(header.text) &&
                std::memcmp(header.text, old.data(), old.size()) == 0)
                return fail(error, ErrorCode::UnsupportedVersion, 0,
                            "Only generation 4 save files are supported");
        return fail(error, ErrorCode::InvalidHeader, 0, "Unrecognized save-file header");
    }
    if (header.version < 35 || header.version > kSaveVersion)
        return fail(error, ErrorCode::UnsupportedVersion, offsetof(SaveHeader, version),
                    "Supported generation 4 file versions are 35 through 288");
    if (header.isMap != 0 && header.isMap != 1)
        return fail(error, ErrorCode::InvalidHeader, offsetof(SaveHeader, isMap),
                    "Header isMap must be 0 or 1");
    return true;
}

bool worldBounds(const WorldParams& world, size_t offset, Error& error) {
    if (world.width == 0 || world.width > kMapMaxSize ||
        world.height == 0 || world.height > kMapMaxSize)
        return fail(error, ErrorCode::Limit, offset + offsetof(WorldParams, width),
                    "World width and height must be between 1 and 40");
    if (world.numTerritories == 0 || world.numTerritories >= kMaxTerritories)
        return fail(error, ErrorCode::Limit, offset + offsetof(WorldParams, numTerritories),
                    "World territory count must be between 1 and 111");
    return true;
}

bool readGame(Reader& r, Document& d, Error& error) {
    // Physical block order follows SaveGame FUN_00461488. All supported versions
    // share these sizes; only the final spies/black-market block is conditional.
    const size_t optionsOffset = r.offset();
    if (!r.read(d.options, "GameOptions")) return false;
    if (d.options.numPlayers < 1 || d.options.numPlayers > kMaxPlayers)
        return fail(error, ErrorCode::Limit, optionsOffset + offsetof(GameOptions, numPlayers),
                    "GameOptions numPlayers must be between 1 and 7");
    if (d.options.localPlayer < 0 || d.options.localPlayer >= kMaxPlayers)
        return fail(error, ErrorCode::InvalidState, optionsOffset + offsetof(GameOptions, localPlayer),
                    "GameOptions localPlayer must be between 0 and 6");
    if (d.options.eventCount < 0 || d.options.eventCount > kMaxEvents)
        return fail(error, ErrorCode::Limit, optionsOffset + offsetof(GameOptions, eventCount),
                    "GameOptions eventCount must be between 0 and 50");
    const size_t worldOffset = r.offset();
    if (!r.read(d.world, "WorldParams") || !worldBounds(d.world, worldOffset, error) ||
        !r.read(d.players, "Player[7]")) return false;

    for (;;) {
        uint32_t value;
        if (!r.read(value, "Local player list / terminator")) return false;
        if (value == kLocalListEnd) break;
        if (d.localList.size() >= kMaxListNodes)
            return fail(error, ErrorCode::Limit, r.offset() - sizeof(value),
                        "Local player list exceeds 4096-node resource limit");
        d.localList.push_back(value);
    }
    if (!r.read(d.raceStats, "RaceStats") || !r.read(d.techs, "TechSaved[48]")) return false;

    for (auto& list : d.ministerJobs) {
        for (;;) {
            if (list.size() >= kMaxListNodes)
                return fail(error, ErrorCode::Limit, r.offset(),
                            "Minister job list exceeds 4096 records including its head");
            MinisterJob node{};
            if (!r.read(node, "Minister job record")) return false;
            list.push_back(node);
            if (node.next.raw == 0) break;
        }
    }

    d.events.reserve(static_cast<size_t>(d.options.eventCount));
    for (int i = 0; i < d.options.eventCount; ++i) {
        Event event;
        const size_t eventOffset = r.offset();
        if (!r.read(event.record, "Event log record")) return false;
        if (event.record.textLen > 0x3ff)
            return fail(error, ErrorCode::Limit, eventOffset + offsetof(EventSaved, textLen),
                        "Event text length exceeds 1023 bytes");
        if (!r.readVector(event.text, event.record.textLen, "Event text")) return false;
        d.events.push_back(std::move(event));
    }

    if (!r.readVector(d.tiles, size_t(d.world.width) * d.world.height, "World tiles")) return false;
    int32_t count = 0;
    if (!r.read(count, "Building count")) return false;
    if (count < 0 || count > kMaxBuildings)
        return fail(error, ErrorCode::Limit, r.offset() - sizeof(count),
                    "Building count must be between 0 and 1200");
    if (!r.readVector(d.buildings, static_cast<size_t>(count), "Buildings") ||
        !r.read(count, "Army count")) return false;
    if (count < 0 || count > kMaxArmies)
        return fail(error, ErrorCode::Limit, r.offset() - sizeof(count),
                    "Army count must be between 0 and 560");
    if (!r.readVector(d.armies, static_cast<size_t>(count), "Armies")) return false;

    // Check the minimum physical size before reserving richer in-memory records.
    if (!r.require(size_t(d.world.numTerritories) * (kTerritorySavedBytes + 5),
                   "Territories and queue counts")) return false;
    d.territories.resize(d.world.numTerritories);
    for (auto& territory : d.territories) {
        if (!r.readBytes(&territory.data, kTerritorySavedBytes, "Territory persistent prefix")) return false;
        for (auto& queue : territory.queues) {
            uint8_t queueCount = 0;
            if (!r.read(queueCount, "Production queue count") ||
                !r.require(size_t(queueCount) * kQueueSavedBytes, "Production queue records")) return false;
            queue.resize(queueCount);
            for (auto& record : queue)
                if (!r.readBytes(&record, kQueueSavedBytes, "Production queue record")) return false;
        }
    }
    if (!r.read(d.jobs, "Task-force jobs") || !r.read(d.aiWarMask, "AI war masks") ||
        !r.read(d.scratchJob1, "Scratch job 1") || !r.read(d.scratchJob2, "Scratch job 2") ||
        !r.read(d.continents, "Continents") || !r.read(d.randomEvents, "Random events") ||
        !r.read(d.scores, "Player scores")) return false;
    if (d.header.version >= 0x24 &&
        (!r.read(d.spies, "Spies") || !r.read(d.blackMarket, "Black market"))) return false;
    return true;
}

bool writeGame(Writer& w, const Document& d) {
    if (!w.write(d.options, "GameOptions") || !w.write(d.world, "WorldParams") ||
        !w.write(d.players, "Player[7]") || !w.writeVector(d.localList, "Local player list") ||
        !w.write(kLocalListEnd, "Local player list terminator") ||
        !w.write(d.raceStats, "RaceStats") || !w.write(d.techs, "TechSaved[48]")) return false;
    for (const auto& list : d.ministerJobs)
        if (!w.writeVector(list, "Minister job list")) return false;
    for (const auto& event : d.events)
        if (!w.write(event.record, "Event log record") ||
            !w.writeVector(event.text, "Event text")) return false;
    const auto buildingCount = static_cast<int32_t>(d.buildings.size());
    const auto armyCount = static_cast<int32_t>(d.armies.size());
    if (!w.writeVector(d.tiles, "World tiles") || !w.write(buildingCount, "Building count") ||
        !w.writeVector(d.buildings, "Buildings") || !w.write(armyCount, "Army count") ||
        !w.writeVector(d.armies, "Armies")) return false;
    for (const auto& territory : d.territories) {
        if (!w.writeBytes(&territory.data, kTerritorySavedBytes, "Territory persistent prefix")) return false;
        for (const auto& queue : territory.queues) {
            const auto count = static_cast<uint8_t>(queue.size());
            if (!w.write(count, "Production queue count")) return false;
            for (const auto& record : queue)
                if (!w.writeBytes(&record, kQueueSavedBytes, "Production queue record")) return false;
        }
    }
    if (!w.write(d.jobs, "Task-force jobs") || !w.write(d.aiWarMask, "AI war masks") ||
        !w.write(d.scratchJob1, "Scratch job 1") || !w.write(d.scratchJob2, "Scratch job 2") ||
        !w.write(d.continents, "Continents") || !w.write(d.randomEvents, "Random events") ||
        !w.write(d.scores, "Player scores")) return false;
    if (d.header.version >= 0x24 &&
        (!w.write(d.spies, "Spies") || !w.write(d.blackMarket, "Black market"))) return false;
    return true;
}

} // namespace

bool decode(std::span<const uint8_t> bytes, Document& destination, Error& error) {
    if (bytes.size() > kMaxFileBytes)
        return fail(error, ErrorCode::Limit, 0, "Save file exceeds 16 MiB resource limit");
    Reader reader(bytes, error);
    try {
        // The fixed job table alone is almost 70 KiB. Keep the complete staging
        // document on the heap and commit only after parsing and validation.
        auto document = std::make_unique<Document>();
        if (!reader.read(document->header, "SaveHeader") ||
            !headerSupported(document->header, error)) return false;
        if (document->header.isMap == 1) {
            const size_t worldOffset = reader.offset();
            if (!reader.read(document->world, "WorldParams") ||
                !worldBounds(document->world, worldOffset, error) ||
                !reader.readVector(document->mapTerritories, document->world.numTerritories,
                                   "Map territories") ||
                !reader.readVector(document->tiles, size_t(document->world.width) * document->world.height,
                                   "World tiles")) return false;
        } else if (!readGame(reader, *document, error)) return false;
        if (!reader.readVector(document->trailing, reader.remaining(), "Trailing original bytes") ||
            !validate(*document, error)) return false;
        destination = std::move(*document);
        error = {};
        return true;
    } catch (const std::bad_alloc&) {
        return fail(error, ErrorCode::Limit, reader.offset(), "Insufficient memory while decoding save file");
    } catch (const std::length_error&) {
        return fail(error, ErrorCode::Limit, reader.offset(), "Invalid allocation size while decoding save file");
    }
}

bool encode(const Document& document, std::vector<uint8_t>& destination, Error& error) {
    Writer writer(error);
    try {
        if (!headerSupported(document.header, error) || !validate(document, error) ||
            !writer.write(document.header, "SaveHeader")) return false;
        if (document.header.isMap == 1) {
            if (!writer.write(document.world, "WorldParams") ||
                !writer.writeVector(document.mapTerritories, "Map territories") ||
                !writer.writeVector(document.tiles, "World tiles")) return false;
        } else if (!writeGame(writer, document)) return false;
        if (!writer.writeVector(document.trailing, "Trailing original bytes")) return false;
        destination.swap(writer.bytes);
        error = {};
        return true;
    } catch (const std::bad_alloc&) {
        return fail(error, ErrorCode::Limit, writer.bytes.size(), "Insufficient memory while encoding save file");
    } catch (const std::length_error&) {
        return fail(error, ErrorCode::Limit, writer.bytes.size(), "Invalid allocation size while encoding save file");
    }
}

} // namespace dl2::save
