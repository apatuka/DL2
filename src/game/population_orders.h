// Owned offline population relocation; no native pointers, network or RNG.
#pragma once
#include "game/save_document.h"
#include <array>
#include <optional>
#include <vector>

namespace dl2::simulation {
using PopulationEventBindings=std::array<std::optional<uint32_t>,kNumRandomEvents>;
struct PopulationMoveContext {
    // Known live plague targets. Missing bindings leave archival event+04
    // opaque; this leaf never guesses a territory from its historical address.
    PopulationEventBindings bindings;
    bool operator==(const PopulationMoveContext&) const = default;
};
struct PopulationMoveRequest {
    uint32_t from=0,to=0;
    int32_t amount=0,mode=0; // Population in hundredths; negatives are native.
    int16_t fromSite=-1,fromSlot=-1;
    bool operator==(const PopulationMoveRequest&) const = default;
};
enum class PopulationMoveDenial {
    None,Unowned,SameTerritory,DifferentOwner,Credits,Population,Capacity,
    NoHousing,NotLocalActor,MissingSourceBuildingAfterTransfer
};
struct PopulationMoveState {
    int32_t credits=0;
    int16_t fromPopulation=0,toPopulation=0;
    int8_t fromMorale=0,toMorale=0;
    bool operator==(const PopulationMoveState&) const = default;
};
struct PlagueSchedule {
    uint32_t slot=0,territory=0;
    int32_t turns=-4;
    bool operator==(const PlagueSchedule&) const = default;
};
struct PopulationMoveReport {
    bool nativeResult=false;
    PopulationMoveDenial denial=PopulationMoveDenial::None;
    int32_t fee=0,capacity=0;
    PopulationMoveState before,after;
    bool plagueAttempted=false;
    std::optional<PlagueSchedule> scheduledPlague;
    PopulationEventBindings bindingsAfter;
    bool adjustedLabor=false,nativeLaborResult=false;
    std::vector<uint32_t> balancedTerritories; // Original call order.
    bool operator==(const PopulationMoveReport&) const = default;
};
// orig: _MovePopulation0046ae9c, offline RequestMovePopulation00476448.
// Applies wrapped signed fee (amount+3)/4, weighted morale, plague scheduling,
// signed16 population updates, optional source labor removal and EXACT balance.
// mode0's0044c238 is only a BalanceLabor wrapper, so both modes balance alike.
// fromSite==-1 skips reading fromSlot and balances both territories; specifying
// a site edits its chosen labor only, then balances the destination alone.
// Native denials return APItrue/nativeResultfalse. The missing-source-building
// denial is deliberately AFTER payment/morale/plague/population: those effects
// are committed even though the native result is false. This is not an error.
// Unsafe indices/division traps/unknown domains return APIfalse transactionally.
// Plague0047ca98 scans50 native records although only25 are owned/saved; a full
// owned25-slot pool is an explicit error, NEVER a silent success or Spy overwrite.
// New event+04 is neutralized0 and its target is in bindingsAfter. Existing raw
// words remain untouched. This is live owned state, NOT archival/save encoding.
// No event dispatch, plague execution, ownership transfer, turn advance or RNG.
bool movePopulationOffline(const save::Document& source,const PopulationMoveRequest& request,
    const PopulationMoveContext& context,save::Document& destination,
    PopulationMoveReport& report,save::Error& error);
// Deliberate user-command permission boundary: actor must be options.localPlayer
// AND source owner. The original low-level offline wrapper has no actor check.
// No additional positive-count, active-housing, route or affordability rules.
bool commandMovePopulation(const save::Document& source,int actor,const PopulationMoveRequest& request,
    const PopulationMoveContext& context,save::Document& destination,
    PopulationMoveReport& report,save::Error& error);
} // namespace dl2::simulation
