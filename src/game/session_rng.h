// Owned RNG state: no gs/gg, process RNG, clock, network or hidden callbacks.
// Evidence: Borland RTL 004ae594/004ae5b0/004ae5d8; game 0046ca40/0046ca60.
#pragma once
#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>
#include "game/save_document.h"

namespace dl2::simulation {

inline constexpr uint32_t kRngSnapshotFormat = 1;
inline constexpr size_t kMaxRngTagBytes = 256; // Diagnostic resource cap, not a game rule.

enum class RngOperation {
    Rand15, Long31, Secondary15, TaggedRange, SeedRtl, SeedSecondary, SeedBoth
};
struct RngCounters {
    uint64_t operations = 0; // Every successful apply, including zero-range and seeds.
    uint64_t rand15 = 0, long31 = 0, secondary15 = 0; // Actual primitive draws.
    uint64_t taggedRange = 0, zeroRanges = 0;
    uint64_t seedRtl = 0, seedSecondary = 0, seedBoth = 0;
    bool operator==(const RngCounters&) const = default;
};
struct RngSnapshot {
    uint32_t format = kRngSnapshotFormat;
    bool initialized = false;
    uint32_t rtlLow = 0, rtlHigh = 0, secondary = 0;
    RngCounters counters;
    bool operator==(const RngSnapshot&) const = default;
};
struct RngRequest {
    RngOperation operation = RngOperation::Rand15;
    int32_t bound = 0; // TaggedRange only. Zero skips RNG; negatives are valid.
    uint32_t seed = 0; // Seed* only. All 32-bit patterns, including zero, are valid.
    std::string_view tag; // Diagnostic only: never hashed into a seed or stream.
};
struct RngEvent {
    uint64_t ordinal = 0; // Global operation order within this initialized session.
    RngOperation operation = RngOperation::Rand15;
    int32_t bound = 0;
    uint32_t seed = 0, value = 0; // Seed operations have value zero.
    std::string tag; // Owned copy; callers may retain an explicit replay/audit log.
    bool consumed = false; // True only when a primitive actually advances.
    bool operator==(const RngEvent&) const = default;
};

class SessionRng {
public:
    using Snapshot = RngSnapshot;
    // Explicit fresh session: same seeding as offline SyncSetRandomSeed, with
    // counters reset. No implicit wall-clock or guessed default seed.
    bool initialize(uint32_t seed, save::Error& error);
    // The FINAL offline LoadGame reseed, not execution of all load-time draws.
    // Supported generation-4 SAV versions 35..0x120 use options.gameId (+0x08).
    // gameSeed and world.rngSeed are NOT the resumed gameplay seed. Loading does
    // not restore the exact pre-save internal RTL/secondary state from the SAV.
    bool initializeAfterLegacyLoad(const save::Document& source, save::Error& error);
    Snapshot snapshot() const { return state_; }
    // Exact restoration is available for OUR own versioned snapshot only.
    // Counter consistency/format are checked, not historical reachability from
    // some unknown seed. A canonical empty snapshot restores an empty session.
    bool restore(const Snapshot& source, save::Error& error);
    // Transactional: failure preserves the RNG and previous event. Ordinals and
    // counters reject exhaustion instead of wrapping; PRNG arithmetic wraps
    // exactly. No internal log grows as calls accumulate.
    bool apply(const RngRequest& request, RngEvent& event, save::Error& error);
private:
    Snapshot state_;
};

// SaveGame 00461488 is intentionally NOT implicit here: offline it draws
// TaggedRange(10000,"SaveGame"), writes gameId, then SeedBoth(gameId) before I/O.
// A future complete save workflow must orchestrate that explicitly. Archival
// codec/prepare/capture must not consume RNG or rewrite a seed as a side effect.
} // namespace dl2::simulation
