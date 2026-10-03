// Typed, owning representation of the SAV/CPN file, separate from running gs/gg.
// orig: FUN_00461488 / FUN_004618e8 and their block writers/readers; SAVEFORMAT.md.
// Historical Ptr32 fields here are FILE IDs, coordinates or inert legacy words,
// never native pointers or handles for globals.h::ptr(). No gameplay activation.
#pragma once
#include <array>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <span>
#include <string>
#include <vector>

#include "game/game_state.h"

namespace dl2::save {

inline constexpr char kHeaderText[] =
    "Deadlock 2  (c)1997 Accolade Inc.  All Rights Reserved.\nPre-release version XXXXXXXXXXX";
inline constexpr size_t kMaxFileBytes = 16 * 1024 * 1024;
inline constexpr size_t kMaxListNodes = 4096; // Resource cap, not an inferred original limit.

enum class ErrorCode { None, InvalidHeader, UnsupportedVersion, Truncated, Limit, InvalidState, Io };
struct Error {
    ErrorCode code = ErrorCode::None;
    size_t offset = 0;
    std::string message;
};

struct Event {
    EventSaved record{};
    std::vector<uint8_t> text; // Exactly textLen bytes; may contain NUL, never strlen().
};
struct TerritoryRecord {
    Territory data{}; // Only [0, kTerritorySavedBytes) is persisted; tail stays zero.
    std::array<std::vector<QueueRecord>, 5> queues; // Only first 0x30 bytes per record.
};

// Optional owned simulation metadata, NEVER a SAV block or a native pointer.
// A task force retains a physical pool-cell reference after DeleteArmy and
// observes that SAME cell if AllocArmy reuses it. Public runtime handles still
// have separate lifetime identities. Cells are 1-based; zero means null.
struct ArmyPoolState {
    std::vector<uint16_t> liveIds; // kMaxArmies cells; zero is a cleared/free cell.
    std::vector<uint32_t> freeSlots; // Native free-list order, back() is the head.
    std::array<std::array<std::array<uint32_t, 16>, kJobsPerPlayer>, kMaxPlayers> jobSlots{};
    bool operator==(const ArmyPoolState&) const = default;
};

struct Document {
    SaveHeader header{};
    GameOptions options{};
    WorldParams world{};
    std::array<Player, kMaxPlayers> players{};
    std::vector<uint32_t> localList;
    RaceStats raceStats{};
    std::array<TechSaved, kNumTechs> techs{};
    // Each list includes its HEAD_JOB. next/prev words are kept, not dereferenced.
    std::array<std::vector<MinisterJob>, kMaxPlayers> ministerJobs;
    std::vector<Event> events;
    std::vector<Tile> tiles; // Dense row-major width*height, unlike gs's stride of 40.
    std::vector<Building> buildings;
    std::vector<Army> armies;
    std::vector<TerritoryRecord> territories; // Entry 0 has file index 1.
    std::array<std::array<Job, kJobsPerPlayer>, kMaxPlayers> jobs{};
    std::array<uint32_t, kMaxPlayers> aiWarMask{};
    Job scratchJob1{}, scratchJob2{};
    std::array<Continent, 32> continents{};
    std::array<RandomEvent, kNumRandomEvents> randomEvents{};
    std::array<PlayerScore, kMaxPlayers> scores{};
    std::array<std::array<Spy, kSpiesPerPlayer>, kMaxPlayers> spies{};
    std::array<BlackMarketState, kMaxPlayers> blackMarket{};
    std::vector<MapTerritory> mapTerritories; // Used only when header.isMap==1.
    std::vector<uint8_t> trailing; // Original loader ignores these; lossless codec keeps them.
    std::optional<ArmyPoolState> armyPool; // Simulation continuation, not encoded.

    const Building* buildingById(uint32_t id) const;
    const Army* armyById(uint32_t id) const;
    const TerritoryRecord* territoryByIndex(uint32_t index) const;
    const Tile* tileAt(uint32_t x, uint32_t y) const;
};

// Supported physical layout: generation 4, versions 35..0x120. Older generations
// are rejected, not silently normalized. No RNG, global state or callbacks touched.
// Failure leaves the destination unchanged. Error resets on success.
bool decode(std::span<const uint8_t> bytes, Document& destination, Error& error);
bool encode(const Document& document, std::vector<uint8_t>& destination, Error& error);
// Checks structure/counts and known references. Without armyPool all saved job
// IDs must resolve. With it, rigorously validates the pool and permits deferred
// job bindings to cleared/reused cells. encode additionally requires bindings
// representable by file IDs; it never silently cleans a job or drops a binding.
bool validate(const Document& document, Error& error);

} // namespace dl2::save
