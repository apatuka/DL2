#include "game/colony_morale.h"
#include "game/data_tables.h"
#include "game/production_plan.h"
#include <algorithm>
#include <bit>
#include <cstring>
#include <memory>
#include <stdexcept>
namespace dl2::simulation {
namespace {
int32_t add(int32_t a,int32_t b) { return std::bit_cast<int32_t>(uint32_t(a)+uint32_t(b)); }
int32_t sub(int32_t a,int32_t b) { return std::bit_cast<int32_t>(uint32_t(a)-uint32_t(b)); }
int32_t mul(int32_t a,int32_t b) { return std::bit_cast<int32_t>(uint32_t(a)*uint32_t(b)); }
int16_t low16(int32_t v) { return std::bit_cast<int16_t>(uint16_t(uint32_t(v))); }
int8_t low8(int32_t v) { return std::bit_cast<int8_t>(uint8_t(uint32_t(v))); }
int32_t sar1(int32_t v) { return std::bit_cast<int32_t>((uint32_t(v)>>1)|(uint32_t(v)&0x80000000u)); }
bool fail(save::Error& e,const char* message) { e={save::ErrorCode::InvalidState,0,message}; return false; }
int16_t racial(const save::Document& d,int owner,int row) {
    if (owner<0 || owner>=kMaxPlayers) throw std::domain_error("Morale owner outside player array");
    const int word=row*kMaxPlayers+d.players[size_t(owner)].race;
    if (word<0 || word>=64*kMaxPlayers) throw std::domain_error("Morale racial address outside saved block");
    int16_t v; std::memcpy(&v,reinterpret_cast<const uint8_t*>(&d.raceStats)+size_t(word)*2,2); return v;
}
bool checked(const save::Document& d,uint32_t index,save::Error& e) {
    if (!save::validate(d,e)) return false;
    return (!d.header.isMap && d.territoryByIndex(index)) || fail(e,"Morale requires a saved-game territory");
}
bool tech(const save::Document& d,int owner,int id) {
    return (uint32_t(int32_t(std::bit_cast<int16_t>(d.techs[size_t(id)].knownMask)))&(1u<<unsigned(owner)))!=0;
}
//00416e70 branches10/13 ONLY. Stored class9 blocks orders, current terrain
// controls land eligibility, and mission13 requires exact full movement BYTE.
bool missionAllowed(const save::Document& d,const Army& a,int mission) {
    if (a.unitClass==9 || !d.territories[a.dest.raw-1].data.terrain) return false;
    if (mission==13) return a.strength==uint8_t(int(data::kUnitTypes[a.type].moves)+(tech(d,a.owner,46)?1:0));
    const int c=data::kUnitTypes[a.type].unitClass;
    return c==1 || c==6 || c==7 || c==11;
}
//00447b0c ->00447a68 ->00447c2c. Attack ignores experience/damage but uses
// order1/2 infantry racial doubling and starvation/bankruptcy arithmetic SAR.
int32_t attack(const save::Document& d,const Army& a) {
    const auto& def=data::kUnitTypes[a.type]; const int c=def.unitClass;
    int32_t value=def.attack;
    if (c==1 && ((a.moves==1 && racial(d,a.owner,33)) || (a.moves==2 && racial(d,a.owner,34)))) value=mul(value,2);
    int row=0;
    switch (c) { case 1:case 6:case 7:case 8:case 11:row=29;break;
        case 2:case 12:row=35;break; case 3:case 13:row=37;break;
        case 4:case 5:case 14:case 15:case 16:case 17:case 18:case 19:row=39;break;
        case 9:case 20:row=41;break;case 10:row=43;break;default:break; }
    int32_t adjustment=row?racial(d,a.owner,row):0;
    if (adjustment<0) adjustment=std::min(mul(adjustment,value)/10,-1);
    else if (adjustment>0) adjustment=std::max(mul(adjustment,value)/10,1);
    value=add(value,adjustment);
    if (d.players[size_t(a.owner)].foodFlags&3u) value=sar1(value);
    return std::max(value,1);
}
int32_t strength(const save::Document& d,uint32_t territory) {
    int32_t value=0;
    for (const auto* a=d.armyById(d.territories[territory-1].data.armies.raw);a;a=d.armyById(a->next.raw))
        if (a->unk_25==13 && missionAllowed(d,*a,13)) value=add(value,attack(d,*a));
    return value;
}
bool relation2(const save::Document& d,int from,int to) {
    if (!d.options.allowAlliances || from<0 || to<0 || from>=d.options.numPlayers || to>=d.options.numPlayers) return false;
    const auto bits=d.players[size_t(from)].relations2[size_t(to)];
    return (bits&0x10u) || (bits&2u);
}
//0046bd3c occupation counts each eligible mission10, not combat strength.
int32_t occupation(const save::Document& d,uint32_t index) {
    const auto& t=d.territories[index-1].data; int32_t value=0;
    for (const auto* a=d.armyById(t.armies.raw);a;a=d.armyById(a->next.raw))
        if (a->unk_25==10 && missionAllowed(d,*a,10)) value=add(value,1);
    for (const auto* a=d.armyById(t.foreignArmies.raw);a;a=d.armyById(a->next.raw))
        if (a->unk_25==10 && relation2(d,a->owner,t.owner) && missionAllowed(d,*a,10)) value=add(value,1);
    if (t.exploredMask) value=add(value,2);
    return value;
}
int32_t totalLabor(const Building& b) { int32_t n=0; for (int32_t labor:b.labor) n=add(n,labor); return n; }
bool metrics(const save::Document& d,uint32_t index,ColonyMoraleMetrics& r,save::Error& error) {
    const auto& t=d.territories[index-1].data; const int owner=t.owner; r.territory=index;
    if (owner<-1 || owner>=kMaxPlayers) return fail(error,"Morale owner outside -1..6");
    if (owner==-1) { r.components[0]=r.baseline=r.total=r.value=100; return true; }
    if (!racial(d,owner,27)) r.components[0]=80;
    else {
        r.components[0]=t.morale; int32_t culture=0,cloning=0,hospital=0; bool bunker=false;
        for (const auto& site:t.sites) {
            const auto* b=d.buildingById(site.building.raw); if (!b) continue;
            if (b->category==19 && !b->turnsLeft) bunker=true; // NO Active/Built check.
            if (!b->turnsLeft && (b->flags&4)) {
                if (b->category==13) cloning=add(cloning,totalLabor(*b));
                if (b->category==14) hospital=add(hospital,totalLabor(*b));
            }
            if ((b->flags&6)!=6) continue;
            const auto* first=std::find(std::begin(b->task),std::end(b->task),uint8_t(7));
            if (first!=std::end(b->task)) {
                std::array<int32_t,5> outputs;
                if (!assignedBuildingOutputs(d,b->id,outputs,error)) return false;
                culture=add(culture,low16(outputs[size_t(first-std::begin(b->task))]));
            }
        }
        const int terrain=std::bit_cast<int8_t>(t.terrain),food=std::bit_cast<int8_t>(t.unk_28[1]);
        if (terrain<0 || terrain>=6 || food<0 || food>=8) return fail(error,"Morale terrain/food table index outside defined domain");
        const int32_t comfortable=mul(data::kTerrainMaxPopulation[terrain],racial(d,owner,24))/100;
        if (comfortable<t.population) {
            if (!t.population) return fail(error,"Morale overcrowding division would trap");
            r.components[1]=std::max(mul(sub(comfortable,t.population),25)/t.population,-20);
        }
        r.components[2]=data::kMoraleByLevel[food];
        r.components[3]=bunker?0:sub(0,occupation(d,index));
        r.components[4]=sub(0,mul(racial(d,owner,22),cloning))/100;
        if (d.options.fastProduction) r.components[4]=mul(r.components[4],2);
        r.components[5]=data::kTaxMoraleByLevel[std::clamp(int(d.players[size_t(owner)].taxLevel)+int(t.tradeState),0,5)];
        r.components[6]=strength(d,index); r.components[7]=std::min(culture,25);
        r.components[8]=std::min(mul(t.materials[10],2),10);
        const int maximum=data::kBuildingTypes[17].maxLabor;
        hospital=std::min(hospital,maximum);
        if (hospital<0 || maximum<0 || maximum>10) return fail(error,"Morale hospital labor indexes outside production table");
        r.components[9]=mul(data::kLaborProductionTable[maximum][hospital],d.options.fastProduction?4:2)/100;
    }
    r.baseline=r.components[0]; for (int32_t part:r.components) r.total=add(r.total,part);
    r.value=std::min(std::clamp(int32_t(low16(r.total)),0,100),add(r.baseline,10)); return true;
}
}
bool colonyRevoltStrength(const save::Document& d,uint32_t index,int32_t& result,save::Error& error) try {
    if (!checked(d,index,error)) return false;
    const auto value=strength(d,index); result=value; error={}; return true;
} catch (const std::bad_alloc&) { error={save::ErrorCode::Limit,0,"Morale strength allocation failed"}; return false; }
  catch (const std::exception& ex) { return fail(error,ex.what()); }
// orig: FUN_0046bdfc (CalculateMorale), including all ten raw components.
bool colonyMoraleMetrics(const save::Document& d,uint32_t index,ColonyMoraleMetrics& result,save::Error& error) try {
    if (!checked(d,index,error)) return false;
    ColonyMoraleMetrics out; if (!metrics(d,index,out,error)) return false;
    result=out; error={}; return true;
} catch (const std::bad_alloc&) { error={save::ErrorCode::Limit,0,"Morale metrics allocation failed"}; return false; }
  catch (const std::exception& ex) { return fail(error,ex.what()); }
// orig: FUN_0046c1a8(apply1). No order-independent simultaneous update invented.
bool processColonyMorale(const save::Document& source,const ConstructionOrderContext& context,
    save::Document& destination,ColonyMoraleReport& report,save::Error& error) try {
    if (!save::validate(source,error)) return false;
    if (source.header.isMap) return fail(error,"Morale pass requires saved game");
    if (context.ai.rng!=context.events.rngBeforeEvents)
        return fail(error,"Morale pass requires one shared initial RNG");
    SessionRng rng; if (!rng.restore(context.events.rngBeforeEvents,error)) return false;
    auto candidate=std::make_unique<save::Document>(source); auto& d=*candidate;
    ColonyMoraleReport result; result.logAfter=context.log; result.aiAfter=context.ai;
    result.rngAfter=rng.snapshot(); result.aiAfter.rng=result.rngAfter;
    for (uint32_t index=1;index<=d.territories.size();++index) {
        auto& t=d.territories[index-1].data; if (t.owner==-1) continue;
        ColonyMoraleChange change; change.territory=index; change.before=t.morale;
        if (!metrics(d,index,change.metrics,error)) return false;
        t.morale=low8(change.metrics.value); change.after=t.morale; result.territories.push_back(change);
    }
    destination=std::move(d); report=std::move(result); error={}; return true;
} catch (const std::bad_alloc&) { error={save::ErrorCode::Limit,0,"Morale pass allocation failed"}; return false; }
  catch (const std::exception& ex) { return fail(error,ex.what()); }
} // namespace dl2::simulation
