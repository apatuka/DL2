#include "game/session_rng.h"
#include <exception>
#include <limits>
#include <new>
#include <stdexcept>
#include <utility>

namespace dl2::simulation {
namespace {
bool fail(save::Error& error, save::ErrorCode code, const char* message) {
    error = {code, 0, message};
    return false;
}
template<class F> bool guarded(F&& operation, save::Error& error) {
    try { return operation(); }
    catch (const std::bad_alloc&) {
        return fail(error, save::ErrorCode::Limit, "Insufficient memory for owned RNG operation");
    } catch (const std::length_error&) {
        return fail(error, save::ErrorCode::Limit, "Owned RNG diagnostic exceeds allocation limits");
    } catch (const std::exception& exception) {
        error = {save::ErrorCode::InvalidState, 0, exception.what()};
        return false;
    }
}
bool add(uint64_t& total, uint64_t value) {
    if (value > std::numeric_limits<uint64_t>::max() - total) return false;
    total += value;
    return true;
}
bool increment(uint64_t& count, save::Error& error) {
    if (add(count, 1)) return true;
    return fail(error, save::ErrorCode::Limit, "Owned RNG counter exhausted");
}
bool validSnapshot(const RngSnapshot& snapshot, save::Error& error) {
    if (snapshot.format != kRngSnapshotFormat)
        return fail(error, save::ErrorCode::UnsupportedVersion, "Unsupported owned RNG snapshot format");
    if (!snapshot.initialized) {
        if (snapshot != RngSnapshot{})
            return fail(error, save::ErrorCode::InvalidState, "Uninitialized RNG snapshot must be canonical empty state");
        return true;
    }
    const auto& c = snapshot.counters;
    if (c.zeroRanges > c.taggedRange || c.taggedRange - c.zeroRanges > c.long31)
        return fail(error, save::ErrorCode::InvalidState, "RNG tagged-range counters disagree with primitive draws");
    uint64_t operations = 0;
    for (const auto count : {c.rand15, c.long31, c.secondary15, c.zeroRanges,
                             c.seedRtl, c.seedSecondary, c.seedBoth})
        if (!add(operations, count))
            return fail(error, save::ErrorCode::InvalidState, "RNG snapshot counter sum overflows");
    if (operations != c.operations)
        return fail(error, save::ErrorCode::InvalidState, "RNG operation ordinal disagrees with its counters");
    return true;
}

// orig: FUN_004ae5b0. Shared RTL low word only; leave the high word untouched.
uint32_t rand15(RngSnapshot& state) {
    state.rtlLow = state.rtlLow * 0x015a4e35u + 1u;
    return (state.rtlLow >> 16) & 0x7fffu;
}
// orig: FUN_004ae5d8, confirmed by its low-product/carry/high-product operations.
// The multiplier is 0x0000015a00004e35, NOT rand15's 0x015a4e35.
uint32_t long31(RngSnapshot& state) {
    uint64_t value = (uint64_t(state.rtlHigh) << 32) | state.rtlLow;
    value = value * 0x0000015a00004e35ull + 1ull;
    state.rtlLow = uint32_t(value);
    state.rtlHigh = uint32_t(value >> 32);
    return state.rtlHigh & 0x7fffffffu;
}
// orig: FUN_0046ca40, independent DAT_0058f1f8 recurrence.
uint32_t secondary15(RngSnapshot& state) {
    state.secondary = state.secondary * 0x41c64e6du + 0x3039u;
    return (state.secondary >> 16) & 0x7fffu;
}
} // namespace

bool SessionRng::initialize(uint32_t seed, save::Error& error) {
    // orig: FUN_00477394 local branch -> 004ae594 + 0046ca60.
    Snapshot candidate;
    candidate.initialized = true;
    candidate.rtlLow = candidate.secondary = seed;
    state_ = candidate;
    error = {};
    return true;
}

bool SessionRng::initializeAfterLegacyLoad(const save::Document& source, save::Error& error) {
    return guarded([&] {
        if (!save::validate(source, error)) return false;
        if (source.header.isMap)
            return fail(error, save::ErrorCode::InvalidState, "Legacy-load RNG initialization requires a saved game, not a map");
        // orig: 004618e8 final offline branch -> 00477394(DAT_0059f15c).
        // 0045f828 copies that word from options+08; 00462100 reads the same
        // 0xac-byte options block for ALL supported versions (35..0x120).
        // Earlier world-change branch: srand(world.rngSeed), long-range scan,
        // other load work. That sequence is superseded by this final reseed.
        // Do not manufacture an exact saved PRNG state from gameSeed/world seed.
        return initialize(uint32_t(source.options.gameId), error);
    }, error);
}

bool SessionRng::restore(const Snapshot& source, save::Error& error) {
    if (!validSnapshot(source, error)) return false;
    state_ = source;
    error = {};
    return true;
}

bool SessionRng::apply(const RngRequest& request, RngEvent& event, save::Error& error) {
    return guarded([&] {
        if (!state_.initialized)
            return fail(error, save::ErrorCode::InvalidState, "Owned RNG requires explicit initialization");
        bool seedOperation = false;
        switch (request.operation) {
        case RngOperation::Rand15: case RngOperation::Long31:
        case RngOperation::Secondary15: case RngOperation::TaggedRange: break;
        case RngOperation::SeedRtl: case RngOperation::SeedSecondary:
        case RngOperation::SeedBoth: seedOperation = true; break;
        default: return fail(error, save::ErrorCode::InvalidState, "Unknown owned RNG operation");
        }
        if ((request.operation != RngOperation::TaggedRange && request.bound != 0) ||
            (!seedOperation && request.seed != 0))
            return fail(error, save::ErrorCode::InvalidState, "Owned RNG request has arguments for a different operation");
        if (request.tag.size() > kMaxRngTagBytes)
            return fail(error, save::ErrorCode::Limit, "Owned RNG diagnostic tag exceeds 256 bytes");
        Snapshot candidate = state_;
        auto& counts = candidate.counters;
        if (!increment(counts.operations, error)) return false;
        RngEvent result;
        result.ordinal = counts.operations;
        result.operation = request.operation;
        result.bound = request.bound;
        result.seed = request.seed;
        result.tag = std::string(request.tag); // Allocate before any live state write.
        switch (request.operation) {
        case RngOperation::Rand15:
            if (!increment(counts.rand15, error)) return false;
            result.value = rand15(candidate); result.consumed = true;
            break;
        case RngOperation::Long31:
            if (!increment(counts.long31, error)) return false;
            result.value = long31(candidate); result.consumed = true;
            break;
        case RngOperation::Secondary15:
            if (!increment(counts.secondary15, error)) return false;
            result.value = secondary15(candidate); result.consumed = true;
            break;
        case RngOperation::TaggedRange:
            // orig: 0046c9d8. Tag has no effect; signed remainder also for
            // negative n. lrand's numerator is nonnegative, so INT_MIN/-1 UB
            // cannot occur. Zero n returns zero without touching either LCG.
            if (!increment(counts.taggedRange, error)) return false;
            if (!request.bound) {
                if (!increment(counts.zeroRanges, error)) return false;
            } else {
                if (!increment(counts.long31, error)) return false;
                result.value = uint32_t(int32_t(long31(candidate)) % request.bound);
                result.consumed = true;
            }
            break;
        case RngOperation::SeedRtl:
            // orig: 004ae594: low=seed, high=0, no secondary change.
            if (!increment(counts.seedRtl, error)) return false;
            candidate.rtlLow = request.seed; candidate.rtlHigh = 0;
            break;
        case RngOperation::SeedSecondary:
            // orig: 0046ca60: only secondary changes.
            if (!increment(counts.seedSecondary, error)) return false;
            candidate.secondary = request.seed;
            break;
        case RngOperation::SeedBoth:
            // orig: offline 00477394; network receive 0047733c has same seeds.
            if (!increment(counts.seedBoth, error)) return false;
            candidate.rtlLow = candidate.secondary = request.seed; candidate.rtlHigh = 0;
            break;
        }
        // Event's string move and scalar snapshot assignment are no-throw.
        event = std::move(result);
        state_ = candidate;
        error = {};
        return true;
    }, error);
}
} // namespace dl2::simulation
