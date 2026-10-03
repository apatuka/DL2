#include "game/building_orders.h"
#include <bit>
#include <memory>
#include <stdexcept>
namespace dl2::simulation {
const char* buildingControlDenialName(BuildingControlDenial v) {
    switch(v) {
    case BuildingControlDenial::None:return "none";
    case BuildingControlDenial::NotLocalActor:return "not_local_actor";
    case BuildingControlDenial::NotOwner:return "not_owner";
    case BuildingControlDenial::Inactive:return "inactive";
    case BuildingControlDenial::EmptyTask:return "empty_task";
    }
    return "unknown";
}
namespace {
bool fail(save::Error& e,const char* m) { e={save::ErrorCode::InvalidState,0,m}; return false; }
Building& building(save::Document& d,uint32_t id) {
    for(auto& b:d.buildings) if(b.id==id) return b;
    throw std::logic_error("Building control lost its existing entity");
}
BuildingLaborState snapshot(const Building& b) {
    BuildingLaborState s; s.flags=b.flags;
    for(size_t i=0;i<5;++i) {s.tasks[i]=b.task[i];s.labor[i]=b.labor[i];} return s;
}
}
bool applyBuildingControl(const save::Document& source,const BuildingControlRequest& request,
    save::Document& destination,BuildingControlReport& report,save::Error& error) try {
    if(!save::validate(source,error)) return false;
    const auto* initial=source.buildingById(request.building);
    if(source.header.isMap || !initial) return fail(error,"Building control requires an existing saved-game building");
    if(request.control!=BuildingControl::ToggleActive && request.control!=BuildingControl::ToggleTaskLock)
        return fail(error,"Unknown building control");
    if(request.control==BuildingControl::ToggleTaskLock && (request.slot<0 || request.slot>=5))
        return fail(error,"Building lock slot must be0..4");
    BuildingControlReport r; r.building=request.building; r.territory=uint32_t(initial->territory); r.control=request.control;
    r.flagsBefore=r.flagsAfter=initial->flags;
    r.moraleBefore=r.moraleAfter=source.territories[r.territory-1].data.morale;
    const int actor=request.actor;
    if(actor<0 || actor>=kMaxPlayers || actor!=source.options.localPlayer ||
        source.players[size_t(actor)].type!=1 || source.players[size_t(actor)].index!=actor)
        r.denial=BuildingControlDenial::NotLocalActor;
    else if(source.territories[r.territory-1].data.owner!=actor) r.denial=BuildingControlDenial::NotOwner;
    else if(request.control==BuildingControl::ToggleTaskLock && !(initial->flags&4)) r.denial=BuildingControlDenial::Inactive;
    else if(request.control==BuildingControl::ToggleTaskLock && !initial->task[request.slot]) r.denial=BuildingControlDenial::EmptyTask;
    auto owned=std::make_unique<save::Document>(source); auto& d=*owned;
    if(r.denial==BuildingControlDenial::None) {
        r.accepted=true;
        if(request.control==BuildingControl::ToggleTaskLock) {
            // orig: CheckBuilding0041d834 buttons11/14/17/20/23 ->0044c44c.
            building(d,r.building).flags^=uint16_t(0x100u<<request.slot);
        } else {
            // orig: FUN_0041d2bc. Omitted calls update widgets/unused displayed
            // output only; no gameplay dependency is replaced by a callback.
            building(d,r.building).flags^=4;
            if(!(building(d,r.building).flags&4)) for(int slot=0;slot<5;++slot) {
                building(d,r.building).flags&=uint16_t(~(0x100u<<slot));
                const int32_t count=building(d,r.building).labor[slot];
                if(count>1000000-int32_t(r.housingAttempts)) {
                    error={save::ErrorCode::Limit,0,"Building deactivation exceeds1000000 housing attempts"}; return false;
                }
                for(int32_t i=0;i<count;++i) {
                    bool moved=false;
                    if(!moveBuildingLaborToHousing(d,r.building,slot,d,moved,error)) return false;
                    ++r.housingAttempts; if(moved) ++r.housingTransfers;
                }
            }
            //004761b0 offline ->0044c3fc: copy current labor, skip negative,
            // narrow accepted entries signed16. Territory+9ae is copied to itself.
            for(auto& value:building(d,r.building).labor)
                if(value>=0) value=std::bit_cast<int16_t>(uint16_t(uint32_t(value)));
        }
        //004762a8 offline ->0044c44c. Flags/+10 already carry desired values.
        if(!balanceTerritoryLabor(d,r.territory,d,error)) return false;
        r.flagsAfter=building(d,r.building).flags; r.moraleAfter=d.territories[r.territory-1].data.morale;
        for(size_t i=0;i<d.buildings.size();++i) {
            const auto a=snapshot(source.buildings[i]),b=snapshot(d.buildings[i]);
            if(a!=b) r.buildings.push_back({d.buildings[i].id,uint32_t(d.buildings[i].territory),uint8_t(d.buildings[i].site),a,b});
        }
    }
    if(!save::validate(d,error)) return false;
    destination=std::move(d); report=std::move(r); error={}; return true;
} catch(const std::bad_alloc&) { error={save::ErrorCode::Limit,0,"Building control allocation failed"}; return false; }
  catch(const std::exception& ex) { error={save::ErrorCode::InvalidState,0,ex.what()}; return false; }
} // namespace dl2::simulation
