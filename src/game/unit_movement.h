// Owned offline MoveUnit leaf; no order authority, combat or turn resolution.
#pragma once
#include "game/movement_paths.h"
#include <optional>
#include <vector>

namespace dl2::simulation {
struct UnitMovementRequest {
    uint32_t armyId = 0, target = 0;
    uint32_t routeOrigin = 0; // Native param3: zero writes the resulting current territory.
    bool operator==(const UnitMovementRequest&) const = default;
};
struct UnitMovementContext {
    // Explicit DAT004c5140 plus path scratch. It is not inferred from armyId.
    MovementPathContext paths;
    bool operator==(const UnitMovementContext& other) const {
        return paths.creation.movingArmyId == other.paths.creation.movingArmyId &&
            paths.editorMode == other.paths.editorMode && paths.sentinelFlags == other.paths.sentinelFlags &&
            paths.recursionDepth == other.paths.recursionDepth &&
            paths.maximumRecursionDepth == other.paths.maximumRecursionDepth;
    }
};
enum class UnitMovementReason {
    Executed, OutOfRange, CreationDenied, ForeignTerrain,
    SiegeCruiserAlreadyMoved, SiegeMissileAlreadyLaunched
};
struct UnitMovementRelink {
    uint32_t armyId = 0, from = 0, target = 0;
    bool fromOwn = false, targetOwn = false;
    bool nativeResult = false, changed = false;
    bool operator==(const UnitMovementRelink&) const = default;
};
enum class UnitTransportOperation { Attach, Detach };
struct UnitMovementTransport {
    UnitTransportOperation operation = UnitTransportOperation::Attach;
    uint32_t armyId = 0, carrierId = 0;
    int slot = -1;
    bool nativeResult = false, taskForceTransfer = false;
    bool operator==(const UnitMovementTransport&) const = default;
};
struct UnitMovementUntransported {
    uint32_t armyId = 0, territory = 0;
    bool ownList = false;
    bool operator==(const UnitMovementUntransported&) const = default;
};
struct UnitMovementReport {
    UnitMovementRequest request;
    UnitMovementContext contextAfter;
    MovementPathReport paths;
    // This is00446084's return value, not a promise that ReLinkArmy succeeded.
    // The native caller ignores relink/attachment failures; inspect their traces.
    bool moved = false;
    UnitMovementReason reason = UnitMovementReason::OutOfRange;
    std::optional<ArmyCreationQuery> creation;
    std::vector<UnitMovementRelink> relinks;
    std::vector<UnitMovementTransport> transports;
    // Native debug scans: target own/foreign, then turn-start own/foreign.
    // Repeated notices are retained when target equals turn-start.
    std::vector<UnitMovementUntransported> untransported;
    bool siegeAdvice = false; // Presentation only; no fabricated event/UI answer.
    uint8_t strengthBefore = 0, strengthAfter = 0, missionBefore = 0, missionAfter = 0;
    bool operator==(const UnitMovementReport&) const = default;
};

// orig:00446084,00445898,00445a74,00445a04,00445aac,00447190.
// Full valid saved document, all armies in reciprocal current-territory lists;
// army/target/optional routeOrigin must resolve. Offline host, non-editor only.
// Reuses the exact DFS from TURN-START(+38), not current(+3c) or route(+40).
// The maximum is canonical moves plus tech46, narrowed/signed like native AL;
// prior strength is not a budget. A successful move writes max-total distance.
// Every valid call publishes path flags/distances, even native moved=false.
// Existing other-player distances and every unit's turn-start are preserved.
// TYPE12/35 carry slots0..2 in order; their passengers' orders/budgets do not reset.
// TYPE35/36 mutual movement exclusion, missions11/13 and transport task-force
// reassignment follow the original. The unsafe disband-then-write-freed-record
// branch of0040cd0c is a capability error, never hidden partial success.
// No discovery, conquest, combat, editor004471c0, allocation, RNG or globals.
// API errors preserve destination/report; source/destination and context/report
// aliases are supported. Native refusal is API success with moved=false.
bool moveUnit(const save::Document& source, const UnitMovementRequest& request,
              const UnitMovementContext& context, save::Document& destination,
              UnitMovementReport& report, save::Error& error);
} // namespace dl2::simulation
