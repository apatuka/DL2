// Offline research orders and exact internal selection leaves, no UI activation.
#pragma once
#include "game/save_document.h"
#include <vector>

namespace dl2::simulation {
struct ResearchSelectionChange {
    int player=-1, before=0, after=0;
    bool setterInvoked=false;
    bool operator==(const ResearchSelectionChange&) const = default;
};
// orig:004764dc offline ->0048424c. No authorization, known/available test,
// queue edit, progress reset, event or RNG. ALL byte patterns are accepted;
// the stored currentResearch is their signed-byte interpretation. Only the
// explicit player array boundary and owning-document validity are enforced.
bool setResearchSelectionOffline(const save::Document&,int player,uint8_t technology,
    save::Document& destination,ResearchSelectionChange&,save::Error&);
// orig:00483cbc. Uses Player.index&31 for available/known masks, not player slot.
// First available1..47 wins (including already known and campaign-forbidden).
// If none, native feature limit10 permits unknown47 when live campaign allows,
// even though47 is NOT available. Otherwise returns0. No queue/prereq repair.
bool chooseDefaultResearch(const save::Document&,int player,uint32_t campaignFlags,
                           int& technology,save::Error&);

enum class ResearchOrderKind { Select, ToggleQueue, ClearQueue };
enum class ResearchOrderDenial { None, NotQueueable, CampaignRestriction };
struct ResearchOrderRequest {
    int actor=-1;
    ResearchOrderKind kind=ResearchOrderKind::Select;
    int technology=0; // Select/Toggle1..47. Clear does not read this field.
};
struct ResearchOrderContext {
    uint32_t campaignFlags=0; // Live DAT0059f100; bit4 controls00450150.
    int32_t commitComparison=0; // Explicit DAT00559db0, NOT currentResearch.
};
struct ResearchOrderReport {
    int actor=-1;
    ResearchOrderKind kind=ResearchOrderKind::Select;
    int technology=0;
    bool accepted=false;
    ResearchOrderDenial denial=ResearchOrderDenial::None;
    int researchBefore=0,researchAfter=0,candidateResearch=0,setterPlayer=-1;
    bool setterInvoked=false,queueStructureChanged=false,usedDefault=false;
    std::vector<uint32_t> queueBefore,queueAfter;
    std::vector<uint32_t> duplicatesDiscarded,removed;
    bool operator==(const ResearchOrderReport&) const = default;
};
// Authorized HEADLESS command policy: actor==localPlayer, type1, index==actor.
// These are explicit authority restrictions, NOT tests in the native setter.
// Select is an explicit convenience policy: replace draft with[technology]
// only when00483a30 permits it against an EMPTY queue. No invented Stop0.
// Toggle/Clear:0043ca24/004839e4 copy-first-dedup;0043cc5c toggle append or
// remove-first+00483b84 pruning;0043cb7c clear. Accepted commands commit via
//0043cbf8/00483a10: replace localList, use head or00483cbc when empty, and call
// setter iff candidate!=commitComparison. This is NOT comparison with current.
// A rejected click returns true/accepted=false with unchanged document and no
// implicit commit (command policy, not a claim that the native UI commits then).
// Reports duplicates removed during accepted opening and explicit/pruned removals.
// queueStructureChanged reports actual draft replacement, even byte-identical.
// Noncanonical saved queue values outside0..47 reject the unsafe command domain.
// No cheating/revocation, AI planning0040cea4, UI delivery, progress, RNG, events,
// turn, or serialization. Source==destination supported; all outputs atomic.
bool applyResearchOrder(const save::Document&,const ResearchOrderRequest&,
    const ResearchOrderContext&,save::Document& destination,ResearchOrderReport&,save::Error&);

struct ResearchAutoReport {
    int player=-1,researchBefore=0,researchAfter=0,candidateResearch=0;
    bool searchedBuildings=false,foundResearchBuilding=false,knownSelection=false,setterInvoked=false;
    bool operator==(const ResearchAutoReport&) const = default;
};
// orig:0046f804 +0046f7d0. Local internal phase, NOT actor authorization or
// a complete turn. If current0, scan ANY building category5/flags&6==6,
// independent of owner/type/work. With no such building, return. Otherwise,
// only a KNOWN current technology (including0) selects00483cbc and sets BYTE.
// No queue, income, event or RNG side effects. Unsafe current tech rejects only
// when the original would index it. Source/destination/report transactional.
bool autoResearchLocal(const save::Document&,uint32_t campaignFlags,
    save::Document& destination,ResearchAutoReport&,save::Error&);
} // namespace dl2::simulation
