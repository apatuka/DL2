// Explicit owned offline labor orders; not a turn, UI or network protocol.
#pragma once
#include "game/labor_balance.h"

namespace dl2::simulation {
struct LaborTransferRequest {
    uint32_t territory=0, fromBuilding=0, toBuilding=0;
    int fromSlot=0, toSlot=0;
    bool operator==(const LaborTransferRequest&) const = default;
};
struct LaborMoveRequest {
    uint32_t territory=0, fromBuilding=0, toBuilding=0;
    bool operator==(const LaborMoveRequest&) const = default;
};
enum class LaborOrderKind { TransferSlots, MoveOne, ResetToHousing };
struct ColonyLaborOrderReport {
    LaborOrderKind kind=LaborOrderKind::TransferSlots;
    uint32_t territory=0;
    bool accepted=false;
    LaborMoveDenial denial=LaborMoveDenial::None;
    int8_t moraleBefore=0, moraleAfter=0;
    std::vector<BuildingLaborChange> buildings; // Changed records, physical order.
    bool operator==(const ColonyLaborOrderReport&) const = default;
};
// Explicit bounded command contract: both IDs belong to the requested colony.
// The native TransferLabor leaf ignores its Territory* argument; no additional
// actor authorization is invented here. Slots are 0..4, NOT task IDs despite
// the legacy NetReassignLaborByTask name. Negative nonzero labor is preserved.
// TRUE means evaluated, including ordinary denied/native-false outcomes which
// may contain real partial effects for MoveOne. FALSE preserves all outputs.
// No callbacks/events/turn increment, implicit refresh or final stock clamp.
bool transferColonyLabor(const save::Document&, const LaborTransferRequest&,
                         save::Document&, ColonyLaborOrderReport&, save::Error&);
bool moveColonyLabor(const save::Document&, const LaborMoveRequest&,
                     save::Document&, ColonyLaborOrderReport&, save::Error&);
bool resetColonyLabor(const save::Document&, uint32_t territory,
                      save::Document&, ColonyLaborOrderReport&, save::Error&);
} // namespace dl2::simulation
