#include "game/combat_auxiliaries.h"
#include <bit>
#include <memory>
#include <new>
#include <stdexcept>
#include <utility>

namespace dl2::simulation {
namespace {
bool fail(save::Error& e, const char* text, save::ErrorCode code = save::ErrorCode::InvalidState) {
    e = {code,0,text}; return false;
}
int32_t add(int32_t a,int32_t b) { return std::bit_cast<int32_t>(uint32_t(a)+uint32_t(b)); }
bool inside(int32_t v) { return v >= 0 && v < 18; }
bool physical(int32_t v) { return v >= -9 && v <= 26; }
size_t cell(int32_t x,int32_t y) { return size_t((y+9)*36+x+9); }
bool validate(const save::Document& d,const CombatPreparationState& s,save::Error& e) {
    if (!save::validate(d,e)) return false;
    if (d.header.isMap) return fail(e,"Combat auxiliaries require a full saved-game document");
    if (s.warriors.size()!=kCombatWarriorCapacity || s.structures.size()!=kCombatStructureCapacity ||
        s.battles.size()!=kCombatBattleCapacity)
        return fail(e,"Combat auxiliaries require the complete physical preparation pools");
    if (!s.currentBattle || s.currentBattle->index>=s.battles.size())
        return fail(e,"Combat auxiliaries require a represented selected Battle");
    return true;
}
struct Work {
    const save::Document& d;
    CombatAuxiliaryReport result;
    save::Error& error;
    bool attempt(std::optional<CombatAuxiliaryPosition> position) {
        CombatPreparedWarriorReport creation;
        if (!createPreparedCombatWarrior(d,result.syntheticArmy,result.after,creation,error)) return false;
        CombatAuxiliaryAttempt a;
        a.outcome=creation.outcome; a.created=creation.created; a.overridePosition=position;
        a.drawBegin=result.draws.size(); a.drawCount=creation.draws.size();
        a.placementFallback=creation.placementFallback; a.missingPlaneRetreat=creation.missingPlaneRetreat;
        a.testedPositions=creation.testedPositions; a.retreatAccessQueries=creation.retreatAccessQueries;
        a.thresholdDefense=creation.thresholdDefense;
        result.draws.insert(result.draws.end(),creation.draws.begin(),creation.draws.end());
        result.after=std::move(creation.after);
        if (a.created) {
            if (position) {
                auto& w=result.after.warriors[a.created->index];
                w.initialX=w.x=w.currentX=position->x;
                w.initialY=w.y=w.currentY=position->y;
                // orig:0045233d..51 et al. Generic militia placement does NOT
                // mark its discarded position; this caller marks only this one.
                result.after.grid.flags[cell(position->x,position->y)] |= 1u;
            }
            result.created.push_back(*a.created);
        }
        result.attempts.push_back(a); return true;
    }
    bool probe(int32_t x,int32_t y) {
        // Initial and final probes have weaker geometric guards in the EXE.
        // Only physical backing is required; do not clamp to the colony18x18.
        if (!physical(x) || !physical(y))
            return fail(error,"Militia occupancy probe lies outside the owned36x36 grid");
        CombatAuxiliaryOccupancy trace{{x,y},bool(result.after.grid.flags[cell(x,y)]&1u),{}};
        if (!trace.occupied) {
            trace.attemptIndex=result.attempts.size();
            if (!attempt(trace.position)) return false;
            // DEC/JZ happens even if00451b68 returns native NULL. Negative
            // totals remain negative and can exhaust the complete spiral.
            result.laborRemaining=add(result.laborRemaining,-1);
        }
        result.occupancy.push_back(trace); return true;
    }
    bool militia(std::optional<CombatStructureRef> ref) {
        auto& input=result.syntheticArmy;
        const auto defender=result.after.battles[result.after.currentBattle->index].core.defender;
        input.owner=std::bit_cast<int8_t>(uint8_t(uint16_t(defender)));
        input.type=23; input.retreatPercent=100;
        if (!ref) return true;
        if (ref->index>=result.after.structures.size()) return fail(error,"Militia structure reference is outside its physical pool");
        const auto& s=result.after.structures[ref->index];
        int32_t x=s.x,y=s.y;
        if (s.parentBuildingId) {
            const auto* b=d.buildingById(*s.parentBuildingId);
            if (!b) return fail(error,"Militia structure parent building is unresolved");
            // orig:0044ba18, five DWORD additions, including negative values.
            for (int32_t value:b->labor) result.laborBefore=add(result.laborBefore,value);
        }
        result.laborRemaining=result.laborBefore;
        if (!result.laborRemaining) return true;
        if (!probe(x,y)) return false;
        if (!result.laborRemaining) return true;
        for (int32_t length=1;length<36;++length) {
            const int32_t direction=(length&1) ? -1 : 1;
            if (!inside(x)) y=add(y,length*direction);
            else for (int32_t i=0;i<length;++i) {
                y=add(y,direction);
                if (inside(y)) {
                    if (!probe(x,y)) return false;
                    if (!result.laborRemaining) return true;
                }
            }
            if (!inside(y)) x=add(x,length*direction);
            else for (int32_t i=0;i<length;++i) {
                x=add(x,direction);
                if (inside(x)) {
                    if (!probe(x,y)) return false;
                    if (!result.laborRemaining) return true;
                }
            }
        }
        // orig:00452471 tests ONLY signed x<18, without x>=0.
        if (x<18) for (int32_t i=0;i<36;++i) {
            y=add(y,-1);
            if (inside(y)) {
                if (!probe(x,y)) return false;
                if (!result.laborRemaining) return true;
            }
        }
        return true;
    }
};
} // namespace

bool createCombatMilitia(const save::Document& d,std::optional<CombatStructureRef> ref,
                         const CombatPreparationState& before,CombatAuxiliaryReport& report,save::Error& e) try {
    if (!validate(d,before,e)) return false;
    auto work=std::make_unique<Work>(Work{d,{},e}); work->result.after=before;
    if (!work->militia(ref)) return false;
    report=std::move(work->result); e={}; return true;
} catch (const std::bad_alloc&) { return fail(e,"Militia allocation failed",save::ErrorCode::Limit);
} catch (const std::length_error&) { return fail(e,"Militia allocation exceeds limits",save::ErrorCode::Limit); }

bool createCombatMines(const save::Document& d,int8_t owner,uint32_t territory,
                       const CombatPreparationState& before,CombatAuxiliaryReport& report,save::Error& e) try {
    if (!validate(d,before,e)) return false;
    if (!territory || territory>d.territories.size()) return fail(e,"Mine source territory is unresolved");
    auto work=std::make_unique<Work>(Work{d,{},e}); work->result.after=before;
    auto& input=work->result.syntheticArmy;
    input.type=d.territories[territory-1].data.terrain==0 ? 38 : 37;
    input.owner=owner; input.retreatPercent=100; input.turnStart=input.routeOrigin=territory;
    for (int i=0;i<24;++i) if (!work->attempt({})) return false;
    report=std::move(work->result); e={}; return true;
} catch (const std::bad_alloc&) { return fail(e,"Mine allocation failed",save::ErrorCode::Limit);
} catch (const std::length_error&) { return fail(e,"Mine allocation exceeds limits",save::ErrorCode::Limit); }
} // namespace dl2::simulation
