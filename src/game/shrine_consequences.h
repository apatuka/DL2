// Owned pending-shrine penalties0044b9e4 ->0044b924, explicitly invoked.
#pragma once
#include "game/entity_creation.h"
#include "game/entity_lifecycle.h"

namespace dl2::simulation {
struct ShrineMoraleChange {
    uint32_t territory=0;
    int8_t before=0,after=0;
    bool operator==(const ShrineMoraleChange&) const = default;
};
struct ShrinePenalty {
    int playerSlot=-1,playerIndex=-1;
    uint32_t territory=0;
    uint8_t nukesUsedBefore=0,nukesUsedAfter=0;
    std::vector<ShrineMoraleChange> morale;
    bool operator==(const ShrinePenalty&) const = default;
};
struct ShrineConsequencesReport {
    std::vector<ShrinePenalty> penalties; // Pending order, including duplicates.
    PendingShrineState pendingAfter; // Original0044b9e4 does NOT clear its count.
    LoadedEventLog logAfter;
    AiReactionContext aiAfter;
    RngSnapshot rngAfter;
    std::array<int32_t,kMaxPlayers> citiesAfter{};
    std::vector<ConstructionOrderEvent> events;
    bool operator==(const ShrineConsequencesReport&) const = default;
};
// Each queued physical Player slot is resolved to its CURRENT signed index.
// Emit80 to that index, then81 to all other slots0..6 (not just active players),
// with its canonical race name and extended payload{index,0}. Actual local/AI
// dispatch precedes morale-20/clamp0 and byte-wrapped scores[index].nukesUsed++.
// Unsupported real AI branches fail the WHOLE call; no event callback is faked.
// Only saved territories1..N are owned here. Native0044b924 also visits pool
// sentinel0: its absent transient state is NOT inferred, changed or exported.
// Queue is retained verbatim. Calling again repeats the original penalties;
// caller controls the scheduling boundary, not an invented automatic dequeue.
// This isolated leaf does not execute preceding combat00457624, advance a turn,
// delete a shrine, change city counts, or imply complete turn/SAV activation.
// Inputs remain unchanged; all outputs commit atomically, source==destination
// is allowed. Success clears error; failure retains document/report/context.
bool processPendingShrineConsequences(const save::Document& source,
    const PendingShrineState& pending,const ConstructionOrderContext& context,
    save::Document& destination,ShrineConsequencesReport& report,save::Error& error);
} // namespace dl2::simulation
