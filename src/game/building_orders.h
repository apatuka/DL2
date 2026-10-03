// Offline player controls, separated from the native window/network transport.
#pragma once
#include "game/labor_balance.h"
namespace dl2::simulation {
enum class BuildingControl { ToggleActive, ToggleTaskLock };
enum class BuildingControlDenial { None, NotLocalActor, NotOwner, Inactive, EmptyTask };
const char* buildingControlDenialName(BuildingControlDenial);
struct BuildingControlRequest {
    int actor=0;
    uint32_t building=0;
    BuildingControl control=BuildingControl::ToggleActive;
    int slot=0; // Only ToggleTaskLock, 0..4 (not the task ID).
};
struct BuildingControlReport {
    bool accepted=false;
    BuildingControlDenial denial=BuildingControlDenial::None;
    uint32_t building=0,territory=0;
    BuildingControl control=BuildingControl::ToggleActive;
    uint16_t flagsBefore=0,flagsAfter=0;
    int8_t moraleBefore=0,moraleAfter=0;
    uint32_t housingAttempts=0,housingTransfers=0;
    std::vector<BuildingLaborChange> buildings;
    bool operator==(const BuildingControlReport&) const = default;
};
// Gameplay body of0041d2bc (activity) and CheckBuilding0041d834 lock buttons,
// followed by original offline setters0044c3fc/0044c44c and BalanceLabor.
// Deactivation clears each lock, attempts to house EACH initially positive
// worker, writes nonnegative labor as signed16, then balances the colony.
// Lock controls require an active nonempty task, matching enabled UI controls.
// Explicit player-command authority: local human with matching Player.index,
// owning this building. This is NOT a restriction added to the native setter.
// TRUE includes an evaluated denial (unchanged document). FALSE rolls back all
// outputs, including late failure while housing/balancing. Source may alias dest.
// No task refresh, stock cap, costs, RNG/events, UI windows, turn or save claim.
bool applyBuildingControl(const save::Document&,const BuildingControlRequest&,
    save::Document&,BuildingControlReport&,save::Error&);
} // namespace dl2::simulation
