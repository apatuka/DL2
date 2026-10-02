#include "game/load_startup.h"
#include <memory>
#include <new>
#include <stdexcept>
#include <utility>

namespace dl2::simulation {
namespace {
bool fail(save::Error& e, const char* message) {
    e = {save::ErrorCode::InvalidState, 0, message}; return false;
}
}
bool planLoadStartup(const save::Document& loaded, const LoadStartupContext& context,
                     LoadStartupReport& destination, save::Error& error) try {
    if (!save::validate(loaded, error)) return false;
    if (loaded.header.isMap) return fail(error, "Load startup requires a game document");
    auto result = std::make_unique<LoadStartupReport>();
    SessionRng rng;
    if (!rng.restore(context.rngBeforeReset, error)) return false;
    // orig: ResetVariables consumes exactly three rand15 values. Only the
    // first wrapper has an original debug tag; secondary RNG is untouched.
    constexpr const char* tags[] = {"GameSeed", "ResetWorldSeed", "ResetWorldRngSeed"};
    for (size_t i = 0; i < 3; ++i)
        if (!rng.apply({RngOperation::Rand15, 0, 0, tags[i]}, result->resetDraws[i], error)) return false;
    result->discardedGameSeed = result->resetDraws[0].value;
    result->discardedWorldSeed = result->resetDraws[1].value;
    result->discardedWorldRngSeed = result->resetDraws[2].value;
    result->rngBeforeEvents = rng.snapshot();
    // Zero reset words from 0046da14, kept separately from loaded options:
    // 004d8264,004d8294,004d8298,004d59c4,004d59b8,004d5a9c,
    // 004d5a54,0058f200,0058f208,004d513c,004d5a50.
    // Document owns loaded scores, jobs, spies, market, tech and world arrays;
    // ResetVariables cleared those BEFORE reading them, never afterward.
    result->winCitiesEffective = loaded.options.winCities; // 004618e8 final
    destination = std::move(*result); error = {}; return true;
} catch (const std::bad_alloc&) {
    error = {save::ErrorCode::Limit, 0, "Load startup allocation failed"}; return false;
} catch (const std::length_error&) {
    error = {save::ErrorCode::Limit, 0, "Load startup allocation limit"}; return false;
}

bool planOfflineSaveRng(const RngSnapshot& before, SaveRngPlan& destination, save::Error& error) try {
    SessionRng rng; SaveRngPlan result;
    if (!rng.restore(before, error) ||
        !rng.apply({RngOperation::TaggedRange, 10000, 0, "SaveGame"}, result.operations[0], error)) return false;
    result.gameId = int32_t(result.operations[0].value);
    if (!rng.apply({RngOperation::SeedBoth, 0, uint32_t(result.gameId), "SaveGameReseed"}, result.operations[1], error)) return false;
    result.after = rng.snapshot();
    destination = std::move(result); error = {}; return true;
} catch (const std::bad_alloc&) {
    error = {save::ErrorCode::Limit, 0, "Save RNG planning allocation failed"}; return false;
} catch (const std::length_error&) {
    error = {save::ErrorCode::Limit, 0, "Save RNG planning allocation limit"}; return false;
}
}
