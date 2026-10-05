#include "game/combat_territory.h"
#include "game/ai_pact_rules.h"
#include "game/combat_defense.h"
#include "game/data_tables.h"
#include <algorithm>
#include <bit>
#include <memory>
#include <new>
#include <set>
#include <stdexcept>
#include <utility>

namespace dl2::simulation {
namespace {
bool fail(save::Error& e,const char* message,save::ErrorCode code=save::ErrorCode::InvalidState) {
    e={code,0,message}; return false;
}
template<class F> bool guarded(F&& f,save::Error& e) {
    try { return f(); }
    catch (const std::bad_alloc&) { return fail(e,"Combat territory allocation failed",save::ErrorCode::Limit); }
    catch (const std::length_error&) { return fail(e,"Combat territory allocation exceeds limits",save::ErrorCode::Limit); }
}
bool valid(const save::Document& d,save::Error& e) {
    return save::validate(d,e) && (!d.header.isMap || fail(e,"Combat territory preparation requires a full saved game"));
}
const Territory* territory(const save::Document& d,uint32_t id,save::Error& e) {
    const auto* t=d.territoryByIndex(id);
    if (!t) { fail(e,"Combat territory reference does not resolve (including sentinel0)"); return nullptr; }
    return &t->data;
}
bool excluded(uint8_t mission) {
    switch(mission) { case 1: case 2: case 3: case 4: case 5: case 6: case 15: case 16: case 19: return true; default: return false; }
}
int signedByte(uint8_t value) { return std::bit_cast<int8_t>(value); }
bool list(const save::Document& d,uint32_t head,std::vector<uint32_t>& ids,save::Error& e) {
    std::set<uint32_t> visited;
    for (uint32_t id=head;id;) {
        const auto* a=d.armyById(id);
        if (!a || !visited.insert(id).second) return fail(e,"Combat Army enumeration encountered an unresolved or cyclic link");
        ids.push_back(id); id=a->next.raw;
    }
    return true;
}
// orig:00456214; compare the unsigned16 saved ID as a signed32 integer.
bool next(const save::Document& d,uint32_t head,int32_t after,std::optional<uint32_t>& result,save::Error& e) {
    std::vector<uint32_t> ids; if (!list(d,head,ids,e)) return false;
    result.reset();
    for (const auto id:ids) if (int32_t(id)>after && (!result || id<*result)) result=id;
    return true;
}
// orig:0044d230. Saved category is authoritative, including its signed byte.
bool activeCategory(const save::Document& d,const Territory& t,int32_t category,int32_t from,int32_t& out,save::Error& e) {
    if (from<0) return fail(e,"Combat active-category search starts before site0");
    out=-1;
    for (int32_t i=from;i<36;++i) {
        const auto id=t.sites[size_t(i)].building.raw;
        if (!id) continue;
        const auto* b=d.buildingById(id);
        if (!b) return fail(e,"Combat active-category search encountered an unresolved building");
        if (category==signedByte(b->category) && b->turnsLeft==0 && (b->flags&4u)) { out=i; break; }
    }
    return true;
}
// orig:00456618. In particular, the race byte is NOT cleared along with type.
bool projectSites(save::Document& d,uint32_t id,std::vector<CombatSiteProjection>& report,save::Error& e) {
    auto& t=d.territories[id-1].data;
    for (size_t i=0;i<36;++i) {
        auto& site=t.sites[i];
        CombatSiteProjection change{i,site.unk_18[0],site.unk_18[1],0,site.unk_18[1],{}};
        site.unk_18[0]=0;
        uint32_t source=site.building.raw;
        if (source) {
            const auto* b=d.buildingById(source);
            if (!b) return fail(e,"Combat site projection encountered an unresolved building");
            if (data::kBuildingTypes[b->type].size!=1) source=0;
        } else {
            const uint16_t bits=site.terrainFlags;
            size_t offset=0;
            if ((bits&0xf000u)==0x4000u && !(bits&0x100u)) offset=5;
            else if ((bits&0xf000u)==0x6000u) offset=24;
            if (offset) {
                if (i+offset>=36) return fail(e,"Combat socket projection references a site beyond the36-site territory");
                source=t.sites[i+offset].building.raw;
                if (!source) return fail(e,"Combat socket projection requires the original source building binding");
            }
        }
        if (source) {
            const auto* b=d.buildingById(source);
            if (!b) return fail(e,"Combat socket projection encountered an unresolved source building");
            site.unk_18[0]=b->type; site.unk_18[1]=b->race; change.sourceBuilding=source;
        }
        change.afterType=site.unk_18[0]; change.afterRace=site.unk_18[1]; report.push_back(change);
    }
    return true;
}
// orig:004568c8 selection prefix. Linked order matters for the last candidates.
bool select(const save::Document& d,const Territory& t,CombatTerritorySelection& s,save::Error& e) {
    std::vector<uint32_t> foreign;
    if (!list(d,t.foreignArmies.raw,foreign,e)) return false;
    for (const auto id:foreign) {
        const auto& a=*d.armyById(id);
        if (a.owner==t.owner || excluded(a.unk_25)) continue;
        auto& count=s.foreignCounts[size_t(a.owner)]; count=std::bit_cast<int32_t>(uint32_t(count)+1u);
        if (hasAiPact(d,a.owner,t.owner,2)) continue;
        if (data::kUnitTypes[a.type].unitClass==9 && a.cargo[0].raw==0) s.warheadOwner=a.owner;
        else { if (data::kUnitTypes[a.type].domain!=3) s.airOnly=false; s.attacker=a.owner; }
    }
    if (s.attacker==-1) s.attacker=s.warheadOwner;
    if (s.attacker==-1) return true;
    const auto* own=t.armies.raw?d.armyById(t.armies.raw):nullptr;
    if (t.armies.raw && !own) return fail(e,"Combat selection own Army head does not resolve");
    if (own && !hasAiPact(d,s.attacker,own->owner,2)) s.opponent=own->owner;
    else if (t.population!=0 && !hasAiPact(d,s.attacker,t.owner,2)) s.opponent=t.owner;
    else {
        for (int a=0;a<7;++a) if (s.foreignCounts[size_t(a)])
            for (int b=0;b<7;++b) if (a!=b && s.foreignCounts[size_t(b)] && !hasAiPact(d,a,b,2))
                { s.attacker=a; s.opponent=b; }
    }
    for (int p=0;p<7;++p) if (t.exploredMask&(1u<<unsigned(p))) s.mineOwner=p;
    if (s.mineOwner!=-1) for (const auto id:foreign) {
        const auto& a=*d.armyById(id);
        if (!excluded(a.unk_25) && a.owner!=s.mineOwner && !hasAiPact(d,s.mineOwner,a.owner,2)) s.minesFriendly=false;
    }
    s.prepared=s.opponent!=-1 || s.warheadOwner!=-1 || (!s.airOnly && !s.minesFriendly);
    return true;
}
void appendDraws(CombatTerritoryReport& r,const std::vector<CombatCreationDraw>& draws) {
    r.draws.insert(r.draws.end(),draws.begin(),draws.end());
}
bool armyPass(const save::Document& d,uint32_t head,bool foreign,bool sea,CombatTerritoryReport& r,save::Error& e) {
    int32_t after=-1;
    for (;;) {
        std::optional<uint32_t> id;
        if (!next(d,head,after,id,e)) return false;
        if (!id) break;
        after=int32_t(*id); const auto& a=*d.armyById(*id);
        CombatTerritoryArmyCall call; call.armyId=*id; call.foreign=foreign; call.drawBegin=r.draws.size();
        call.seaDomainSkipped=sea && data::kUnitTypes[a.type].domain==1;
        if (!call.seaDomainSkipped) {
            CombatCreationArmy input; if (!projectCombatCreationArmy(d,*id,input,e)) return false;
            CombatPreparedWarriorReport created;
            if (!createPreparedCombatWarrior(d,input,r.contextAfter.preparation,created,e)) return false;
            r.contextAfter.preparation=std::move(created.after);
            call.outcome=created.outcome; call.created=created.created; call.drawCount=created.draws.size();
            call.placementFallback=created.placementFallback; call.missingPlaneRetreat=created.missingPlaneRetreat;
            call.testedPositions=created.testedPositions; call.retreatAccessQueries=created.retreatAccessQueries;
            call.thresholdDefense=created.thresholdDefense; appendDraws(r,created.draws);
        }
        r.armies.push_back(call);
    }
    return true;
}
void auxiliary(CombatTerritoryReport& r,CombatAuxiliaryReport&& out,bool mines,std::optional<CombatStructureRef> structure) {
    CombatTerritoryAuxiliaryCall call;
    call.mines=mines; call.structure=structure; call.syntheticArmy=out.syntheticArmy;
    call.laborBefore=out.laborBefore; call.laborRemaining=out.laborRemaining;
    call.attempts=std::move(out.attempts); call.occupancy=std::move(out.occupancy);
    call.drawBegin=r.draws.size(); call.drawCount=out.draws.size(); appendDraws(r,out.draws);
    r.contextAfter.preparation=std::move(out.after); r.auxiliaries.push_back(std::move(call));
}
bool prepare(const save::Document& source,uint32_t id,const CombatTerritoryContext& context,
             bool selectedWrapper,save::Document& destination,CombatTerritoryReport& report,save::Error& e) {
    if (!valid(source,e)) return false;
    const auto* initial=territory(source,id,e); if (!initial) return false;
    auto result=std::make_unique<CombatTerritoryReport>(); result->contextAfter=context;
    if (!select(source,*initial,result->selection,e)) return false;
    auto d=std::make_unique<save::Document>(source);
    if (result->selection.prepared) {
        if (selectedWrapper) result->contextAfter.preparation.selectedTerrainTerritory=id;
        if (!projectSites(*d,id,result->siteProjection,e)) return false;
        const auto& t=d->territories[id-1].data;
        CombatBattlePreparationReport begun;
        if (!beginCombatBattle(*d,{id,t.owner,int16_t(result->selection.attacker),1},result->contextAfter.preparation,begun,e)) return false;
        result->battle=begun.created; result->contextAfter.preparation=std::move(begun.after);
        if (!armyPass(*d,t.foreignArmies.raw,true,t.terrain==0,*result,e)) return false;
        for (size_t i=0;i<36;++i) if (const auto building=t.sites[i].building.raw) {
            CombatBuildingReport out;
            if (!addCombatBuilding(*d,building,result->contextAfter.preparation,out,e)) return false;
            CombatTerritoryBuildingCall call;
            call.buildingId=building; call.site=i; call.outcome=out.outcome; call.warriorOutcome=out.warriorOutcome;
            call.structure=out.structure; call.warrior=out.warrior; call.drawBegin=result->draws.size(); call.drawCount=out.draws.size();
            appendDraws(*result,out.draws); result->contextAfter.preparation=std::move(out.after);
            result->buildings.push_back(call);
        }
        if (!armyPass(*d,t.armies.raw,false,t.terrain==0,*result,e)) return false;
        auto& population=result->contextAfter.militiaPopulation;
        population=0;
        if (t.terrain!=0) {
            int32_t site;
            if (!activeCategory(*d,t,19,0,site,e)) return false;
            if (site!=-1) population=int32_t(t.population);
            else {
                auto current=result->contextAfter.preparation.battles[result->battle->index].firstStructure;
                std::set<size_t> visited;
                while (current) {
                    auto& state=result->contextAfter.preparation;
                    if (current->index>=state.structures.size() || !visited.insert(current->index).second)
                        return fail(e,"Combat militia traversal encountered an unresolved or cyclic structure link");
                    CombatAuxiliaryReport out;
                    if (!createCombatMilitia(*d,current,state,out,e)) return false;
                    auxiliary(*result,std::move(out),false,current);
                    current=result->contextAfter.preparation.structures[current->index].next;
                }
            }
        }
        if (result->selection.mineOwner!=-1) {
            CombatAuxiliaryReport out;
            if (!createCombatMines(*d,int8_t(result->selection.mineOwner),id,result->contextAfter.preparation,out,e)) return false;
            auxiliary(*result,std::move(out),true,{});
        }
        auto& state=result->contextAfter.preparation;
        result->replaySeed=state.privateRng; state.battles[result->battle->index].seed=state.privateRng;
        CombatDefenseReport defense;
        if (!rebuildCombatDefense(*d,state,defense,e)) return false;
        state=std::move(defense.after); result->defenseRebuilt=true;
        if (selectedWrapper) state.selectedTerrainTerritory=context.preparation.selectedTerrainTerritory;
    }
    if (!save::validate(*d,e)) return false;
    destination=std::move(*d); report=std::move(*result); e={}; return true;
}
} // namespace

// orig:00456214.
bool nextCombatArmyById(const save::Document& d,uint32_t head,int32_t after,std::optional<uint32_t>& out,save::Error& e) {
    return guarded([&] { if (!valid(d,e)) return false; std::optional<uint32_t> result;
        if (!next(d,head,after,result,e)) return false; out=result; e={}; return true; },e);
}
// orig:0044d230.
bool findActiveCombatBuildingCategory(const save::Document& d,uint32_t id,int32_t category,int32_t from,int32_t& out,save::Error& e) {
    return guarded([&] { if (!valid(d,e)) return false; const auto* t=territory(d,id,e); if (!t) return false;
        int32_t result; if (!activeCategory(d,*t,category,from,result,e)) return false; out=result; e={}; return true; },e);
}
// orig:00456618.
bool rebuildCombatSiteProjection(const save::Document& d,uint32_t id,save::Document& out,
                                 std::vector<CombatSiteProjection>& report,save::Error& e) {
    return guarded([&] { if (!valid(d,e) || !territory(d,id,e)) return false;
        auto result=std::make_unique<save::Document>(d); std::vector<CombatSiteProjection> changes;
        if (!projectSites(*result,id,changes,e)) return false;
        out=std::move(*result); report=std::move(changes); e={}; return true; },e);
}
// orig:004568c8 prefix through00451410;004526b0 is deliberately outside this API.
bool prepareTerritoryCombat(const save::Document& d,uint32_t id,const CombatTerritoryContext& context,
                           save::Document& out,CombatTerritoryReport& report,save::Error& e) {
    return guarded([&] { return prepare(d,id,context,false,out,report,e); },e);
}
// orig:00456c10, restoring the selected territory after the bounded preparation.
bool prepareSelectedTerritoryCombat(const save::Document& d,uint32_t id,const CombatTerritoryContext& context,
                                   save::Document& out,CombatTerritoryReport& report,save::Error& e) {
    return guarded([&] { return prepare(d,id,context,true,out,report,e); },e);
}
} // namespace dl2::simulation
