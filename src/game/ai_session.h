// Owned AI initialization/bindings and explicit task-force maintenance.
// Never executes addresses or callback words from the archival Document.
#pragma once
#include "game/load_profile.h"
#include "game/session_rng.h"
#include "game/ai_pact_rules.h"
#include <array>
#include <cstdint>
#include <vector>
#include <optional>
#include <string>

namespace dl2::simulation {
namespace ai_event_detail { struct ReplayState; }
enum class AiBinding : uint8_t {
    None, InitializeMachiavelli, TurnMachiavelli, DiplomacyMachiavelli,
    VerifiedReturn, EventMachiavelli
};
enum class AiOperation : uint8_t { Initialize, MinisterPhase, Turn, Diplomacy, Event };
struct AiRequest { int player = -1; AiOperation operation = AiOperation::Initialize; int phase = 0; };
struct AiInvocation {
    AiBinding binding = AiBinding::None;
    int minister = -1, phase = -1;
    uint32_t originalAddress = 0; // Evidence only, never a function pointer.
    bool operator==(const AiInvocation&) const = default;
};
struct AiDispatchReport {
    std::vector<AiInvocation> invocations;
    bool stateChanged = false;
    bool operator==(const AiDispatchReport&) const = default;
};
struct AiSessionSnapshot {
    bool initializationComplete = false;
    bool aiTurnImplemented = false; // RunAITurns is NOT ported here.
    bool diplomacyImplemented = false;
    LoadSessionResetMetadata data;
    std::array<std::array<AiBinding, 5>, kMaxPlayers> personalityBindings{};
    std::array<std::array<std::array<AiBinding, 4>, 6>, kMaxPlayers> ministerBindings{};
    bool operator==(const AiSessionSnapshot&) const = default;
};
// 0045093c ring spans00564530..005649c7:42 records, one reserved empty cell.
inline constexpr size_t kAiMessageCapacity = 41;
struct AiDiplomacyMessage {
    int sender = -1;
    uint32_t recipients = 0;
    int category = 0, variant = 0; // category-1: semantic command in variant.
    std::array<int32_t,3> arguments{};
    bool operator==(const AiDiplomacyMessage&) const = default;
};
// Live globals, not SAV fields. The caller supplies their actual continuation;
// missing state rejects only a branch that needs it, never invents a cold reset.
struct AiNegotiationState {
    std::array<std::array<int32_t,kMaxPlayers>,kMaxPlayers> lastOfferTurn{}; //0052245c
    std::array<int32_t,kMaxPlayers> offerState{}; //006534fc: idle,busy,pending,accept,reject
    std::array<uint32_t,kMaxPlayers> processedOfferMask{}; //00522264, reset per AI turn
    AiVictoryMetrics victory;
    bool operator==(const AiNegotiationState&) const = default;
};
struct AiReactionContext {
    RngSnapshot rng;
    // 00522248 is not saved/reset by LoadGame: explicit previous-session state.
    std::array<uint32_t,kMaxPlayers> relationChangeMask{};
    // Logical FIFO of the original42-cell ring. Delivery/UI is separate;
    // pending human messages/requests are not silently answered or discarded.
    std::vector<AiDiplomacyMessage> pendingMessages;
    bool gameAborted = false;
    std::optional<AiNegotiationState> negotiation;
    bool operator==(const AiReactionContext&) const = default;
};
enum class AiMessageOutcome { Queued, NoHumanRecipient, Full };
struct AiMessageAttempt {
    AiDiplomacyMessage message;
    AiMessageOutcome outcome = AiMessageOutcome::Queued;
    bool operator==(const AiMessageAttempt&) const = default;
};
struct AiAttitudeChange {
    int player = -1, other = -1;
    int32_t before = 0, after = 0, baselineBefore = 0, baselineAfter = 0;
    bool applied = false;
    bool operator==(const AiAttitudeChange&) const = default;
};
struct AiWarEnd {
    int player = -1, other = -1;
    uint32_t maskBefore = 0, maskAfter = 0;
    std::vector<int> dissolvedJobs; // Physical job indices, in original live traversal order.
    bool operator==(const AiWarEnd&) const = default;
};
enum class AiPactAction { SecretBreak, PublicBreak, Make };
struct AiPactEdit {
    int player = -1, other = -1;
    AiPactAction action = AiPactAction::SecretBreak;
    uint32_t requested = 0, applied = 0; // Network leaf truncates to uint16.
    bool accepted = false; // Original ACK; false does not imply API failure.
    bool operator==(const AiPactEdit&) const = default;
};
struct AiPactEvent {
    int recipient = -1, eventType = 0, player = -1, other = -1;
    bool operator==(const AiPactEvent&) const = default;
};
struct AiPactNotice {
    int player = -1, recipient = -1;
    uint32_t mask = 0;
    std::string portrait;
    bool operator==(const AiPactNotice&) const = default;
};
enum class AiOfferOutcome { Busy, Accepted, Rejected, AwaitingHuman };
struct AiPactOffer {
    int player = -1, other = -1;
    uint32_t mask = 0;
    AiOfferOutcome outcome = AiOfferOutcome::Busy;
    bool operator==(const AiPactOffer&) const = default;
};
struct AiReactionReport {
    AiReactionContext contextAfter;
    std::vector<RngEvent> draws;
    std::vector<AiAttitudeChange> attitudes;
    std::vector<AiMessageAttempt> messages;
    std::vector<AiWarEnd> warsEnded;
    std::vector<AiPactEdit> pacts;
    std::vector<AiPactEvent> pactEvents; // Synchronous AI callbacks, not human log records.
    std::vector<AiPactNotice> pactNotices;
    std::vector<AiPactOffer> offers;
    bool handled = false;
    bool operator==(const AiReactionReport&) const = default;
};
struct AiDiplomacyRequest { int player = -1, other = -1, category = 0; };
struct AiAttitudeRequest { int player = -1, other = -1; int32_t delta = 0; };
//0040526c/004051c4 offline leaf, shared by diplomacy and research sharing.
// No personality callback is invoked by this helper: callers may supply a
// physical Player.index differing from their Player* slot. Enforces the actual
// campaign/skill/relation-change mask, clamping and signed arithmetic through
// the same implementation used by AiSession. Never draws or guesses a mask.
bool changeAiAttitude(const save::Document& source,const AiAttitudeRequest& request,
                      const AiReactionContext& context,save::Document& destination,
                      AiReactionReport& report,save::Error& error);
struct AiEventRequest {
    int player = -1, eventType = 0;
    // Actual arguments7/8 at004047a9/[ebp+20] and004049f8/[ebp+24].
    // Logger00423690 supplies ZERO,ZERO, NOT its four formatting arguments.
    int32_t extra1 = 0, extra2 = 0;
};
class AiSession {
public:
    // Final LoadGame point, after offline profile conversion: live human slots
    // other than options.localPlayer are rejected. Runs actual data initializers
    // 00401830 -> 00408784 -> 0040233c; no RunAITurns invocation. Per-player
    // initializations starts at1 here, not the earlier LoadJobs conversion count.
    bool initializeAfterLoad(const save::Document& document, save::Error& error);
    AiSessionSnapshot snapshot() const { return state_; }
    // Initialize really resets owned strategy/minister data. MinisterPhase
    // reproduces 00402494: order0,5,1,4,3,2, phase0..3. All24 canonical targets
    // are verified RET bodies, not fabricated missing-implementation fallbacks.
    // Turn rejects until its actual dependencies are ported. The parameterless
    // Diplomacy/Event requests reject: use the explicit-context methods below.
    bool dispatch(const AiRequest& request, AiDispatchReport& report, save::Error& error);
    // Complete offline00404cec, including00404c74,0040526c,004504a4,0045093c.
    // The two archival scratchJob blocks are physically attitude[7][7] int32;
    // only addressed words are changed, never resolved as fake Job pointers.
    // All outputs are atomic and source==destination is supported. Context is
    // supplied explicitly, never inferred from gameId, an empty queue or masks.
    bool reactDiplomacy(const save::Document& source, const AiDiplomacyRequest& request,
                        const AiReactionContext& context, save::Document& destination,
                        AiReactionReport& report, save::Error& error) const;
    //004047a0: ordinary random chat, gratitude, pact-break penalty and event74
    // implemented. Hostility ends previous wars via004033d0/00403350, including
    // messages and live traversal of all50 jobs through0040beb4. Dissolution
    // preserves the owned physical pool; no cleanup or ID relookup is invented.
    // Offline secret/public pact breaks and recursive72/73 negotiation are
    // supported with explicit live negotiation state. Human offers reject
    // atomically here; AiEventTransaction is the explicit response API.
    // Unsupported branches roll back Document, queue, masks and every RNG draw.
    // Unknown event IDs are the authentic default return, reported handled=false.
    bool reactEvent(const save::Document& source, const AiEventRequest& request,
                    const AiReactionContext& context, save::Document& destination,
                    AiReactionReport& report, save::Error& error) const;
private:
    friend class AiEventTransaction;
    bool replayEvent(const save::Document& source,const AiEventRequest& request,
        const AiReactionContext& context,ai_event_detail::ReplayState& replay,
        save::Document& destination,AiReactionReport& report,save::Error& error) const;
    AiSessionSnapshot state_;
};

enum class TaskForceOutcome { Removed, AlreadyDetached, Added, AlreadyPresent, Full };
struct TaskForceEditReport {
    TaskForceOutcome outcome = TaskForceOutcome::AlreadyDetached;
    uint32_t armyId = 0;
    int player = -1, jobIndex = -1, slot = -1; // Jobs are zero-based in this API.
    std::vector<uint32_t> detachedArmyIds; // Original recursion order, root first.
    bool operator==(const TaskForceEditReport&) const = default;
};
// Offline host semantics of 0040adf4/0040b0c0/0040b074. Mutates only the
// explicit document, transactionally even when recursive cargo removal fails.
// With ArmyPool metadata, membership/free tests use physical-cell bindings,
// NOT expected Job.armyIds: retired cells remain nonnull and reused cells can
// resolve another ID. Without metadata, validated archival IDs supply the
// initial loaded resolution. This helper never initializes or cleans the pool.
// Touched bindings/IDs are changed together; touched historical Job.armies
// words become zero, never pointers/handles. Remove follows the owner's
// Army.job and FIRST pointer match, recursing only for unit TYPE12; job0 stops.
// Add returns explicit AlreadyPresent/Full without changing the source, exactly
// like the original early returns. Adding into a free slot first removes the
// previous task force, then stores the new owner-local 1-based Army.job.
// No entity deletion, refunds, AI decisions, ministers or RNG effects implied.
bool removeArmyFromTaskForce(save::Document& document, uint32_t armyId,
                             TaskForceEditReport& report, save::Error& error);
bool addArmyToTaskForce(save::Document& document, int player, int jobIndex, uint32_t armyId,
                        TaskForceEditReport& report, save::Error& error);
// 00416ca4 -> 00416c28. Reads canonical class for Army.type, owner (not
// Player.index), saved race modifier at flat word54*7+signed race, and tech43.
// The signed-race address must remain inside RaceStats; no clamp is invented.
// Army may be an explicit prospective record not yet inserted in document.
bool canScoutOwned(const save::Document& document, const Army& army,
                   bool& result, save::Error& error);

struct MaintainUnitPruneReport {
    std::array<uint32_t, kMaxPlayers> removed{};
    bool operator==(const MaintainUnitPruneReport&) const = default;
};
// EXPLICIT deferred cleanup, NOT an invented DeleteUnit callback. Only the
// terminal missing-army/wrong-owner branch of HandleMaintainUnit00410870 and
// scheduler00405aac/FreeMinisterJob00405760. Valid type13 jobs and other types
// remain untouched; their real gameplay handlers are not replaced by no-ops.
// List heads survive; next/prev remain inert file-layout words, next nonzero
// means another owned node. Failure preserves document/report.
// A type13 target ID0 is rejected: original lookup can match an unowned free
// pool cell, which this dense live-entity Document intentionally does not model.
bool pruneInvalidMaintainUnitJobs(save::Document& document,
                                 MaintainUnitPruneReport& report, save::Error& error);
} // namespace dl2::simulation
