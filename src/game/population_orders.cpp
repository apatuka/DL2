#include "game/population_orders.h"
#include "game/labor_balance.h"
#include "game/population_growth.h"
#include <bit>
#include <memory>
#include <new>
#include <stdexcept>
#include <utility>

namespace dl2::simulation {
namespace {
int32_t add(int32_t a,int32_t b) { return std::bit_cast<int32_t>(uint32_t(a)+uint32_t(b)); }
int32_t sub(int32_t a,int32_t b) { return std::bit_cast<int32_t>(uint32_t(a)-uint32_t(b)); }
int32_t mul(int32_t a,int32_t b) { return std::bit_cast<int32_t>(uint32_t(a)*uint32_t(b)); }
int16_t short16(int32_t n) { return std::bit_cast<int16_t>(uint16_t(uint32_t(n))); }
int8_t byte8(int32_t n) { return std::bit_cast<int8_t>(uint8_t(uint32_t(n))); }
int32_t sar2(int32_t n) { return std::bit_cast<int32_t>((uint32_t(n)>>2)|((uint32_t(n)&0x80000000u)?0xc0000000u:0u)); }
bool fail(save::Error& error,const char* why,save::ErrorCode code=save::ErrorCode::InvalidState) {
    error={code,0,why}; return false;
}
int32_t fee(int32_t amount) {
    // Preserve BOTH wrapped additions and the compiler's signed division fixup.
    // Replacing with (amount+3)/4 has C++ overflow UB and misses wrap+6 extremes.
    const int32_t rounded=add(amount,3);
    return sar2(rounded<0?add(amount,6):rounded);
}
PopulationMoveState state(const save::Document& d,const PopulationMoveRequest& request) {
    const auto& from=d.territories[request.from-1].data;
    const auto& to=d.territories[request.to-1].data;
    return {from.owner>=0 && from.owner<kMaxPlayers?d.players[size_t(from.owner)].credits:0,
            from.population,to.population,from.morale,to.morale};
}
bool bindingsValid(const save::Document& d,const PopulationMoveContext& context,save::Error& error) {
    for (size_t i=0;i<context.bindings.size();++i) if (context.bindings[i]) {
        if (!d.territoryByIndex(*context.bindings[i]) || d.randomEvents[i].type!=1 || d.randomEvents[i].unk_04!=0)
            return fail(error,"Population move plague binding does not match an owned type1 event/territory");
    }
    return true;
}
// orig: FUN0047ca98. Its unused tail words are NOT initialized by the original.
bool plague(save::Document& d,uint32_t territory,PopulationMoveReport& r,save::Error& error) {
    r.plagueAttempted=true;
    for (size_t i=0;i<d.randomEvents.size();++i) if (d.randomEvents[i].type==0) {
        auto& event=d.randomEvents[i]; event.type=1; event.unk_04=0; event.turnsLeft=-4;
        r.bindingsAfter[i]=territory; r.scheduledPlague=PlagueSchedule{uint32_t(i),territory,-4}; return true;
    }
    return fail(error,"Population plague scheduling exceeds25 owned events; original50-slot scan would enter Spies",save::ErrorCode::Limit);
}
Building* building(save::Document& d,uint32_t id) {
    for (auto& b:d.buildings) if (b.id==id) return &b;
    return nullptr;
}
bool perform(save::Document& d,const PopulationMoveRequest& request,PopulationMoveReport& r,save::Error& error) {
    const auto& source=d.territories[request.from-1].data;
    const int owner=source.owner;
    const auto deny=[&](PopulationMoveDenial reason){r.denial=reason;return true;};
    if (owner==-1) return deny(PopulationMoveDenial::Unowned);
    if (request.from==request.to) return deny(PopulationMoveDenial::SameTerritory);
    if (owner!=d.territories[request.to-1].data.owner) return deny(PopulationMoveDenial::DifferentOwner);
    if (owner<0 || owner>=kMaxPlayers) return fail(error,"Population move owner lies outside0..6");
    r.fee=fee(request.amount);
    if (r.fee>d.players[size_t(owner)].credits) return deny(PopulationMoveDenial::Credits);
    if (request.amount>source.population) return deny(PopulationMoveDenial::Population);
    PopulationLimits limits;
    if (!territoryPopulationLimits(d,request.to,limits,error)) return false;
    r.capacity=limits.maximum;
    const auto& target=d.territories[request.to-1].data;
    if (add(target.population,request.amount)>r.capacity) return deny(PopulationMoveDenial::Capacity);
    bool housing=false;
    //0044d1a4(category17): NO active/built/completed requirement here.
    for (const auto& site:target.sites) {
        const auto* b=d.buildingById(site.building.raw); if (b && b->category==17) {housing=true;break;}
    }
    if (!housing) return deny(PopulationMoveDenial::NoHousing);
    const int32_t denominator=add(request.amount,target.population);
    const int32_t numerator=add(mul(target.population,target.morale),mul(request.amount,source.morale));
    if (!denominator || (numerator==INT32_MIN && denominator==-1))
        return fail(error,"Population move weighted-morale signed division would trap");
    d.players[size_t(owner)].credits=sub(d.players[size_t(owner)].credits,r.fee);
    d.territories[request.to-1].data.morale=byte8(numerator/denominator);
    if ((source.flags&0x20u) && !plague(d,request.to,r,error)) return false;
    d.territories[request.from-1].data.population=short16(sub(source.population,short16(request.amount)));
    auto& targetPopulation=d.territories[request.to-1].data.population;
    targetPopulation=short16(add(targetPopulation,short16(request.amount)));
    if (request.fromSite!=-1) {
        if (request.fromSite<0 || request.fromSite>=kNumSites) return fail(error,"Population source site lies outside0..35 or sentinel-1");
        const uint32_t id=d.territories[request.from-1].data.sites[request.fromSite].building.raw;
        if (!id) return deny(PopulationMoveDenial::MissingSourceBuildingAfterTransfer);
        auto* b=building(d,id); if (!b) return fail(error,"Population source site has no owned building");
        const int32_t workers=request.amount/100;
        if (request.fromSlot==-1) {
            int32_t total=0; for (int32_t n:b->labor) total=add(total,n);
            if (workers<=total) {
                r.adjustedLabor=true;
                if (!adjustBuildingLabor(d,id,sub(0,workers),d,r.nativeLaborResult,error)) return false;
            }
        } else {
            if (request.fromSlot<0 || request.fromSlot>=5) return fail(error,"Population source labor slot lies outside0..4 or sentinel-1");
            if (workers<=b->labor[request.fromSlot]) {
                b->labor[request.fromSlot]=sub(b->labor[request.fromSlot],workers);
                r.adjustedLabor=true; r.nativeLaborResult=true;
            }
        }
    } else {
        //0044c238(mode0) is a direct BalanceLabor call, identical to mode!=0.
        if (!balanceTerritoryLabor(d,request.from,d,error)) return false;
        r.balancedTerritories.push_back(request.from);
    }
    if (!balanceTerritoryLabor(d,request.to,d,error)) return false;
    r.balancedTerritories.push_back(request.to); r.nativeResult=true; return true;
}
bool move(const save::Document& source,const PopulationMoveRequest& request,const PopulationMoveContext& context,
          std::optional<int> actor,save::Document& destination,PopulationMoveReport& report,save::Error& error) try {
    if (!save::validate(source,error)) return false;
    if (source.header.isMap || !source.territoryByIndex(request.from) || !source.territoryByIndex(request.to))
        return fail(error,"Population move requires saved-game source/destination territories1..N");
    if (!bindingsValid(source,context,error)) return false;
    PopulationMoveReport result; result.before=result.after=state(source,request); result.bindingsAfter=context.bindings;
    auto candidate=std::make_unique<save::Document>(source);
    if (actor && (*actor<0 || *actor>=kMaxPlayers || *actor!=source.options.localPlayer ||
                  *actor!=source.territories[request.from-1].data.owner))
        result.denial=PopulationMoveDenial::NotLocalActor;
    else if (!perform(*candidate,request,result,error)) return false;
    result.after=state(*candidate,request);
    if (!save::validate(*candidate,error)) return false;
    destination=std::move(*candidate); report=std::move(result); error={}; return true;
} catch (const std::bad_alloc&) { return fail(error,"Population order allocation failed",save::ErrorCode::Limit); }
  catch (const std::length_error&) { return fail(error,"Population order container limit exceeded",save::ErrorCode::Limit); }
  catch (const std::exception& ex) { error={save::ErrorCode::InvalidState,0,ex.what()}; return false; }
}
bool movePopulationOffline(const save::Document& source,const PopulationMoveRequest& request,
    const PopulationMoveContext& context,save::Document& destination,PopulationMoveReport& report,save::Error& error) {
    return move(source,request,context,{},destination,report,error);
}
bool commandMovePopulation(const save::Document& source,int actor,const PopulationMoveRequest& request,
    const PopulationMoveContext& context,save::Document& destination,PopulationMoveReport& report,save::Error& error) {
    return move(source,request,context,actor,destination,report,error);
}
} // namespace dl2::simulation
