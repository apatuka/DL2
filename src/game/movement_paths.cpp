#include "game/movement_paths.h"
#include "game/ai_pact_rules.h"
#include <algorithm>
#include <bit>
#include <new>
#include <stdexcept>
#include <utility>

namespace dl2::simulation {
namespace {
bool fail(save::Error& error, const char* message, save::ErrorCode code = save::ErrorCode::InvalidState) {
    error = {code, 0, message};
    return false;
}
int32_t add(int32_t a, int32_t b) { return std::bit_cast<int32_t>(uint32_t(a) + uint32_t(b)); }
int16_t word(int32_t value) { return std::bit_cast<int16_t>(uint16_t(uint32_t(value))); }

struct Search {
    const save::Document& source;
    const MovementPathRequest& request;
    const MovementPathContext& context;
    MovementPathReport result;
    save::Error& error;

    const Territory* territory(uint32_t index) {
        if (!index || index > source.territories.size()) {
            fail(error, "Movement adjacency reaches sentinel0 or an unrepresented territory");
            return nullptr;
        }
        return &source.territories[index - 1].data;
    }
    // orig: FUN_0044d1e4. Saved category and exact zero remaining work; neither
    // canonical type/category nor Built/Active flags replace these conditions.
    bool completedCategory(const Territory& t, uint8_t category) const {
        for (const auto& site : t.sites) {
            const auto* building = source.buildingById(site.building.raw);
            if (building && building->category == category && building->turnsLeft == 0) return true;
        }
        return false;
    }
    bool pact(int owner, uint32_t mask) const {
        return hasAiPact(source, request.player, owner, mask);
    }
    bool friendly(int owner) const { return owner == request.player || pact(owner, 2); }

    // Terrain branches of00446440, including domain4 (land-only, like1 here).
    bool permittedTerrain(const Territory& from, const Territory& to, bool& permitted) {
        if (context.editorMode) { permitted = true; return true; }
        if (to.terrain != 0) { permitted = request.domain != 2; return true; }
        permitted = request.domain == 2 || request.domain == 3 || request.domain == 6;
        if (!permitted && request.domain == 5 && from.terrain != 0 && to.owner == request.player) {
            ArmyCreationQuery query;
            // Original passes Militia23, not the type of the moving unit.
            if (!canCreateArmy(source, to.index, 23, context.creation, query, error)) return false;
            permitted = query.reason == ArmyCreationReason::Allowed;
        }
        return true;
    }
    // orig: FUN_00446440. Recursive entries have nonnegative cost<1000 in
    // this wrapper domain; distance>=1000 cannot improve initialized words.
    bool visit(uint32_t index, int32_t distance) {
        const auto* from = territory(index);
        if (!from) return false;
        ++result.visitCount;
        result.recursionDepthAfter = add(result.recursionDepthAfter, 1);
        result.maximumRecursionDepthAfter = std::max(result.maximumRecursionDepthAfter, result.recursionDepthAfter);
        if (distance <= request.range) {
            result.territories[index].flags |= request.markMask;
            result.territories[index].distance = word(distance);
        }
        if (request.target && index == *request.target) {
            result.bestTargetDistance = std::min(result.bestTargetDistance, distance);
        } else if (distance < result.bestTargetDistance && distance < request.range) {
            // The native loop SARs a signed WORD but stops after16 bits; direct
            // ascending bit tests preserve its exact visits without signed-shift UB.
            for (uint32_t group = 0; group < 7; ++group) {
                for (uint32_t bit = 0; bit < 16; ++bit) {
                    if (!(from->adjacency[group] & (uint32_t(1) << bit))) continue;
                    const uint32_t next = group * 16 + bit;
                    const auto* to = territory(next);
                    if (!to) return false;
                    // Read LIVE scratch: reset can clear NoTiles, and the mark
                    // itself may set it. Reading source.flags here would differ.
                    if (result.territories[next].flags & 0x100u) continue;
                    bool permitted = false;
                    if (!permittedTerrain(*from, *to, permitted)) return false;
                    if (to->owner != request.player && pact(to->owner, 1)) permitted = false;
                    if (to->owner != request.player && pact(to->owner, 2) &&
                        !pact(to->owner, 0x10) && completedCategory(*to, 9)) permitted = false;
                    if (!permitted) continue;

                    int32_t candidate = distance;
                    if (!context.editorMode) {
                        if (request.domain == 3 ||
                            (friendly(to->owner) && friendly(from->owner) &&
                             (request.domain == 2 || request.domain == 6 ||
                              (to->terrain != 0 && from->terrain != 0)))) {
                            candidate = add(distance, 1);
                        } else if (from->owner == request.player || index == request.origin || pact(from->owner, 2)) {
                            candidate = add(distance, 2);
                        } else if (from->owner == -1) {
                            candidate = add(distance, 5);
                        } else {
                            candidate = add(distance, 100);
                        }
                    }
                    if (to->owner == request.player && (request.domain == 6 || request.domain == 1) &&
                        completedCategory(*to, 12)) candidate = std::max(add(candidate, -1), 0);
                    if (candidate <= request.range && candidate < result.bestTargetDistance &&
                        candidate < result.territories[next].distance && !visit(next, candidate)) return false;
                }
            }
        }
        result.recursionDepthAfter = add(result.recursionDepthAfter, -1);
        return true;
    }
};
} // namespace

// orig: FUN_00446b3c / FUN_00446b94, with0045dfb0 and00446b08 resets.
bool findMovementPaths(const save::Document& source, const MovementPathRequest& request,
                       const MovementPathContext& context, MovementPathReport& report,
                       save::Error& error) try {
    if (!save::validate(source, error)) return false;
    if (source.header.isMap) return fail(error, "Movement search requires a full saved-game document");
    if (!request.origin || request.origin > source.territories.size() ||
        (request.target && (!*request.target || *request.target > source.territories.size())))
        return fail(error, "Movement origin/target must address a represented territory1..N");
    if (request.player < 0 || request.player >= kMaxPlayers || request.domain < 1 || request.domain > 6)
        return fail(error, "Movement search requires player0..6 and domain1..6");
    if (context.creation.movingArmyId && !source.armyById(context.creation.movingArmyId))
        return fail(error, "Movement moving-army context does not resolve");
    Search search{source, request, context, {}, error};
    search.result.request = request;
    search.result.recursionDepthAfter = context.recursionDepth;
    search.result.maximumRecursionDepthAfter = context.maximumRecursionDepth;
    search.result.territories.resize(source.territories.size() + 1);
    search.result.territories[0].flags = context.sentinelFlags & ~request.markMask;
    for (size_t i = 0; i < source.territories.size(); ++i)
        search.result.territories[i + 1].flags = source.territories[i].data.flags & ~request.markMask;
    if (request.range != 0 && !search.visit(request.origin, 0)) return false;
    report = std::move(search.result);
    error = {};
    return true;
} catch (const std::bad_alloc&) {
    return fail(error, "Movement search allocation failed", save::ErrorCode::Limit);
} catch (const std::length_error&) {
    return fail(error, "Movement search allocation exceeds limits", save::ErrorCode::Limit);
}
} // namespace dl2::simulation
