#include "game/economic_upkeep.h"
#include "game/data_tables.h"
#include <algorithm>
#include <bit>
#include <cstring>
#include <memory>
#include <new>
#include <stdexcept>
#include <string>

namespace dl2::simulation {
namespace {
bool fail(save::Error& error,const char* message) {
    error={save::ErrorCode::InvalidState,0,message}; return false;
}
int32_t add(int32_t a,int32_t b) { return std::bit_cast<int32_t>(uint32_t(a)+uint32_t(b)); }
int32_t sub(int32_t a,int32_t b) { return std::bit_cast<int32_t>(uint32_t(a)-uint32_t(b)); }
int32_t mul(int32_t a,int32_t b) { return std::bit_cast<int32_t>(uint32_t(a)*uint32_t(b)); }
int group(uint8_t canonicalClass) {
    switch (canonicalClass) {
    case 1: case 6: case 7: case 0x1a: return 0;
    case 2: case 8: case 12: return 1;
    case 3: case 13: return 2;
    case 4: case 5: case 14: case 15: case 16: case 17: case 18: case 19: return 3;
    default: return -1;
    }
}
bool compute(const save::Document& d,const std::vector<uint32_t>& order,
             PlayerUpkeepChange& change,save::Error& error) {
    for (uint32_t id:order) {
        const auto* a=d.armyById(id);
        if (!a || a->owner!=change.player) continue;
        const int bucket=group(data::kUnitTypes[a->type].unitClass);
        if (bucket>=0) ++change.unitCounts[size_t(bucket)];
    }
    // orig:0046b4d0 reads signed race through a flat RaceStats WORD address.
    // DAT0055a148 - DAT00559e00 ==840 ==60*7*2; neighboring rows are not
    // silently clamped when a signed race outside0..6 still addresses the block.
    const int address=60*kMaxPlayers*2+int(d.players[size_t(change.player)].race)*2;
    if (address<0 || size_t(address)+sizeof(int16_t)>sizeof(d.raceStats))
        return fail(error,"Upkeep racial multiplier indexes outside owned RaceStats bytes");
    int16_t racial; std::memcpy(&racial,reinterpret_cast<const uint8_t*>(&d.raceStats)+address,2);
    constexpr int32_t multipliers[]={1,2,4,3};
    for (size_t bucket=0;bucket<4;++bucket) {
        const int32_t count=change.unitCounts[bucket],over=std::max(0,sub(count,20));
        const int32_t squares=add(mul(count,count),mul(over,over)); //0046b3ac(base,2).
        change.groupCosts[bucket]=mul(mul(racial,squares),multipliers[bucket])/100;
        change.totalCost=add(change.totalCost,change.groupCosts[bucket]);
    }
    return true;
}
bool emit(save::Document& d,int recipient,const LocalEventRequest& request,
          const ConstructionOrderContext& context,EconomicUpkeepReport& result,save::Error& error) {
    ConstructionOrderEvent event; event.type=request.type; event.recipient=recipient;
    if (recipient==d.options.localPlayer) {
        auto input=context.events; input.rngBeforeEvents=result.rngAfter; event.local=true;
        if (!logLocalEvent(d,result.logAfter,input,request,result.logAfter,event.localReport,error)) return false;
        result.rngAfter=event.localReport.rngAfter;
    } else if (std::bit_cast<int8_t>(d.players[size_t(recipient)].type)>=3) {
        if (!context.aiSession || context.ai.rng!=context.events.rngBeforeEvents)
            return fail(error,"Upkeep event needs owned AI bindings and shared initial RNG");
        event.aiDispatched=true; result.aiAfter.rng=result.rngAfter;
        // All callers here use LogEvent, not Ex. Format arguments are NOT
        // extra1/extra2. The original AI cases1/3/153..156 return by default.
        if (!context.aiSession->reactEvent(d,{recipient,request.type,0,0},result.aiAfter,d,event.aiReport,error)) return false;
        result.aiAfter=event.aiReport.contextAfter; result.rngAfter=result.aiAfter.rng;
    }
    result.aiAfter.rng=result.rngAfter; result.events.push_back(std::move(event)); return true;
}
bool bounded(const char* bytes,size_t count,std::string& result,save::Error& error) {
    const auto* end=static_cast<const char*>(std::memchr(bytes,0,count));
    if (!end) return fail(error,"Upkeep local disband event name lacks bounded NUL terminator");
    result.assign(bytes,size_t(end-bytes)); return true;
}
bool disband(save::Document& d,const std::vector<uint32_t>& order,PlayerUpkeepChange& change,
             const ConstructionOrderContext& context,EconomicUpkeepReport& result,save::Error& error) {
    int32_t bestPrice=-1; int16_t bestExperience=10000; uint32_t selected=0;
    for (uint32_t id:order) {
        const auto* a=d.armyById(id);
        if (!a || a->owner!=change.player) continue;
        const int32_t price=data::kUnitTypes[a->type].cost[0];
        if (price>bestPrice || (price==bestPrice && a->experience<bestExperience)) {
            bestPrice=price; bestExperience=a->experience; selected=id;
        }
    }
    change.selectedArmyId=selected;
    if (!selected) return true; // Original still clears4 even if no army exists.
    LocalEventRequest request; request.type=3;
    if (change.player==d.options.localPlayer) {
        const auto& a=*d.armyById(selected);
        const auto* territory=d.territoryByIndex(a.dest.raw);
        if (!territory) return fail(error,"Upkeep disband event has no current territory");
        std::string armyName,territoryName;
        if (!bounded(a.name,sizeof(a.name),armyName,error) ||
            !bounded(territory->data.name,sizeof(territory->data.name),territoryName,error)) return false;
        request.arguments={armyName,territoryName};
    }
    if (!emit(d,change.player,request,context,result,error)) return false;
    // orig:SyncDisbandUnit00475898 offline directly calls00445f08. No
    // RemoveArmyFromTaskForce appears in this caller; preserve that boundary.
    if (!removeArmy(d,{selected,ArmyRemovalKind::DisbandUnit,false},d,change.disband,error)) return false;
    result.retiredIds.insert(result.retiredIds.end(),change.disband.removedIds.begin(),change.disband.removedIds.end());
    return true;
}
} // namespace

bool processEconomicUpkeep(const save::Document& source,const ConstructionOrderContext& context,
                           save::Document& destination,EconomicUpkeepReport& report,save::Error& error) try {
    if (!save::validate(source,error)) return false;
    if (source.header.isMap) return fail(error,"Military upkeep requires a saved game");
    SessionRng rng; if (!rng.restore(context.events.rngBeforeEvents,error)) return false;
    auto candidate=std::make_unique<save::Document>(source); auto& d=*candidate;
    EconomicUpkeepReport result; result.logAfter=context.log; result.aiAfter=context.ai;
    result.rngAfter=context.events.rngBeforeEvents; result.aiAfter.rng=result.rngAfter;
    for (const auto& a:d.armies) result.armyOrder.push_back(a.id);
    // orig:0046f89c/0046f85c, zero-extended WORD IDs. Freed records remain in
    // the original sorted slot array but have type0; absent owned IDs skip alike.
    std::sort(result.armyOrder.begin(),result.armyOrder.end());
    for (int p=0;p<kMaxPlayers;++p) {
        auto& change=result.players[size_t(p)]; change.player=p;
        change.creditsBefore=d.players[size_t(p)].credits; change.flagsBefore=d.players[size_t(p)].foodFlags;
        if (!compute(d,result.armyOrder,change,error)) return false;
        for (size_t bucket=0;bucket<4;++bucket) if (change.groupCosts[bucket])
            if (!emit(d,p,{uint16_t(153+bucket),{change.groupCosts[bucket],change.unitCounts[bucket]},{}},context,result,error)) return false;
        // Event dispatch may replace d: never keep a Player reference over it.
        d.players[size_t(p)].credits=sub(d.players[size_t(p)].credits,change.totalCost);
        if (d.players[size_t(p)].credits<0) {
            d.players[size_t(p)].credits=0;
            if (!(d.players[size_t(p)].foodFlags&1u)) {
                if (!emit(d,p,{1,{},{}},context,result,error)) return false;
                d.players[size_t(p)].foodFlags|=1u;
            } else d.players[size_t(p)].foodFlags|=4u;
        } else d.players[size_t(p)].foodFlags&=0xfeu;
        if (d.players[size_t(p)].foodFlags&4u) {
            if (!disband(d,result.armyOrder,change,context,result,error)) return false;
            d.players[size_t(p)].foodFlags&=0xfbu;
        }
        change.creditsAfter=d.players[size_t(p)].credits; change.flagsAfter=d.players[size_t(p)].foodFlags;
    }
    if (!save::validate(d,error)) return false;
    destination=std::move(d); report=std::move(result); error={}; return true;
} catch (const std::bad_alloc&) { error={save::ErrorCode::Limit,0,"Upkeep allocation failed"}; return false; }
  catch (const std::length_error&) { error={save::ErrorCode::Limit,0,"Upkeep container bound exceeded"}; return false; }
  catch (const std::exception& e) { error={save::ErrorCode::InvalidState,0,e.what()}; return false; }
} // namespace dl2::simulation
