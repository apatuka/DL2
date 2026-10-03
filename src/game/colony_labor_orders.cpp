#include "game/colony_labor_orders.h"
#include <algorithm>
#include <memory>
#include <stdexcept>

namespace dl2::simulation {
namespace {
bool fail(save::Error& e,const char* text) { e={save::ErrorCode::InvalidState,0,text}; return false; }
BuildingLaborState state(const Building& b) {
    BuildingLaborState s; s.flags=b.flags;
    std::copy_n(b.task,5,s.tasks.begin()); std::copy_n(b.labor,5,s.labor.begin()); return s;
}
template<class Action>
bool order(const save::Document& source,uint32_t territory,LaborOrderKind kind,
           save::Document& destination,ColonyLaborOrderReport& report,save::Error& error,Action action) try {
    if (!save::validate(source,error)) return false;
    if (source.header.isMap || !source.territoryByIndex(territory))
        return fail(error,"Labor order requires a saved-game territory");
    auto candidate=std::make_unique<save::Document>();
    ColonyLaborOrderReport result; result.kind=kind; result.territory=territory;
    result.moraleBefore=source.territories[territory-1].data.morale;
    if (!action(*candidate,result,error)) return false;
    result.moraleAfter=candidate->territories[territory-1].data.morale;
    for (size_t i=0;i<source.buildings.size();++i) {
        const auto& before=source.buildings[i]; const auto old=state(before),now=state(candidate->buildings[i]);
        if (old!=now) result.buildings.push_back({before.id,uint32_t(before.territory),uint8_t(before.site),old,now});
    }
    if (!save::validate(*candidate,error)) return false;
    destination=std::move(*candidate); report=std::move(result); error={}; return true;
} catch (const std::bad_alloc&) { error={save::ErrorCode::Limit,0,"Labor order allocation failed"}; return false; }
  catch (const std::exception& ex) { error={save::ErrorCode::InvalidState,0,std::string("Labor order: ")+ex.what()}; return false; }
bool buildings(const save::Document& d,uint32_t territory,uint32_t from,uint32_t to,save::Error& error) {
    const auto* a=d.buildingById(from); const auto* b=d.buildingById(to);
    return (a && b && uint32_t(a->territory)==territory && uint32_t(b->territory)==territory) ||
        fail(error,"Labor order buildings must belong to the requested territory");
}
}
// orig: FUN_00475ce8 offline -> FUN_0044c320;00475bf4 payload slots are not task IDs.
bool transferColonyLabor(const save::Document& source,const LaborTransferRequest& request,
                         save::Document& destination,ColonyLaborOrderReport& report,save::Error& error) {
    return order(source,request.territory,LaborOrderKind::TransferSlots,destination,report,error,
        [&](save::Document& d,ColonyLaborOrderReport& r,save::Error& e) {
            if (!buildings(source,request.territory,request.fromBuilding,request.toBuilding,e)) return false;
            LaborMoveResult result;
            if (!transferBuildingLabor(source,request.fromBuilding,request.fromSlot,request.toBuilding,request.toSlot,d,result,e)) return false;
            r.accepted=result.accepted; r.denial=result.denial; return true;
        });
}
// orig: FUN_00475ba4 offline -> FUN_0044c2c0.
bool moveColonyLabor(const save::Document& source,const LaborMoveRequest& request,
                     save::Document& destination,ColonyLaborOrderReport& report,save::Error& error) {
    return order(source,request.territory,LaborOrderKind::MoveOne,destination,report,error,
        [&](save::Document& d,ColonyLaborOrderReport& r,save::Error& e) {
            if (!buildings(source,request.territory,request.fromBuilding,request.toBuilding,e)) return false;
            LaborMoveResult result;
            if (!moveOneBuildingLabor(source,request.fromBuilding,request.toBuilding,d,result,e)) return false;
            r.accepted=result.accepted; r.denial=result.denial; return true;
        });
}
// orig: FUN_00475d60 offline -> FUN_0044bacc.
bool resetColonyLabor(const save::Document& source,uint32_t territory,
                      save::Document& destination,ColonyLaborOrderReport& report,save::Error& error) {
    return order(source,territory,LaborOrderKind::ResetToHousing,destination,report,error,
        [&](save::Document& d,ColonyLaborOrderReport& r,save::Error& e) {
            if (!resetTerritoryLabor(source,territory,d,e)) return false;
            r.accepted=true; return true;
        });
}
} // namespace dl2::simulation
