#include "game/movement_crossings.h"
#include "game/army_state.h"
#include "game/combat_stats.h"
#include "game/data_tables.h"
#include <algorithm>
#include <bit>
#include <exception>
#include <memory>
#include <new>
#include <set>
#include <stdexcept>
#include <utility>

namespace dl2::simulation {
namespace {
bool fail(save::Error& error,const char* message,save::ErrorCode code=save::ErrorCode::InvalidState) {
    error={code,0,message}; return false;
}
template<class F> bool guarded(F&& operation,save::Error& error) {
    try { return operation(); }
    catch (const std::bad_alloc&) { return fail(error,"Movement crossing allocation failed",save::ErrorCode::Limit); }
    catch (const std::length_error&) { return fail(error,"Movement crossing trace exceeds allocation limits",save::ErrorCode::Limit); }
    catch (const std::exception& e) { error={save::ErrorCode::InvalidState,0,e.what()}; return false; }
}
int32_t add(int32_t a,int32_t b) { return std::bit_cast<int32_t>(uint32_t(a)+uint32_t(b)); }
int32_t mul(int32_t a,int32_t b) { return std::bit_cast<int32_t>(uint32_t(a)*uint32_t(b)); }
int signedType(uint8_t type) { return type<128?type:int(type)-256; }
bool technology(const save::Document& d,int player,int tech) {
    return (uint32_t(int32_t(std::bit_cast<int16_t>(d.techs[size_t(tech)].knownMask))) & (1u<<unsigned(player)))!=0;
}
bool checkedDocument(const save::Document& d,save::Error& error) {
    return save::validate(d,error) && (!d.header.isMap || fail(error,"Movement crossings require a saved game"));
}
bool eligible(const Army& a,bool& result,save::Error& error) {
    const int type=signedType(a.type);
    if (type<0 || type>=data::kNumUnitTypes) return fail(error,"Crossing unit type leaves its canonical table");
    result=false;
    if (data::kUnitTypes[type].unitClass==9) return true;
    switch (a.unk_25) {
    case 1: case 2: case 3: case 4: case 5: case 6: case 15: case 16: case 19: return true;
    default: result=army::turnStart(a)!=army::current(a); return true;
    }
}
bool owner(int player,save::Error& error) {
    return (player>=0 && player<kMaxPlayers) || fail(error,"Crossing player outside physical slots0..6");
}
bool territory(const save::Document& d,uint32_t index,save::Error& error) {
    return (index>0 && index<kMaxTerritories && d.territoryByIndex(index)) ||
        fail(error,"Crossing territory reference does not resolve to a represented row");
}
bool name(const Territory& t,std::string& result,save::Error& error) {
    const auto* end=std::find(t.name,t.name+sizeof(t.name),'\0');
    if (end==t.name+sizeof(t.name)) return fail(error,"Crossing territory name lacks its original string terminator");
    result.assign(t.name,end); return true;
}
bool deliver(save::Document& d,const AiSession& bindings,MovementCrossingsReport& report,
             MovementCrossingResolution& crossing,save::Error& error) {
    auto& event=crossing.event;
    event.recipient=crossing.loser; event.winner=crossing.winner;
    event.from=crossing.from; event.retreatTo=crossing.retreatTo;
    //00457576 reads winner/race BEFORE entering either logger branch.
    const int race=d.players[size_t(crossing.winner)].race;
    if (race<0 || race>=data::kNumRaces) return fail(error,"Crossing winner race outside its canonical name table");
    if (crossing.loser==d.options.localPlayer) {
        if (!report.contextAfter.log) return fail(error,"Local crossing withdrawal requires the existing event log");
        std::string from,to;
        if (!name(d.territories[crossing.from-1].data,from,error) ||
            !name(d.territories[crossing.retreatTo-1].data,to,error)) return false;
        LocalEventRequest request; request.type=152;
        request.arguments={std::move(from),std::string(data::kRaceNames[race]),std::move(to),int32_t(0)};
        LocalEventReport local;
        if (!logLocalEvent(d,*report.contextAfter.log,{report.contextAfter.ai.rng,report.contextAfter.cities},request,
                           *report.contextAfter.log,local,error)) return false;
        report.contextAfter.ai.rng=local.rngAfter;
        report.draws.insert(report.draws.end(),local.randomDraws.begin(),local.randomDraws.end());
        event.route=MovementCrossingEventRoute::LocalLog; event.local=std::move(local);
    } else if (signedType(d.players[size_t(crossing.loser)].type)>=3) {
        AiReactionReport reaction;
        if (!bindings.reactEvent(d,{crossing.loser,152,0,0},report.contextAfter.ai,d,reaction,error)) return false;
        report.contextAfter.ai=reaction.contextAfter;
        report.draws.insert(report.draws.end(),reaction.draws.begin(),reaction.draws.end());
        event.route=MovementCrossingEventRoute::AiReaction; event.reaction=std::move(reaction);
    }
    return true;
}
} // namespace

// orig:00401108. Each underlying wrapper makes the same zero-target projection.
bool scoreArmyPower(const save::Document& source,const ArmyPowerRequest& request,
                    ArmyPowerReport& report,save::Error& error) {
    return guarded([&] {
        Combatant projected;
        if (!projectArmyCombatant(source,request.armyId,projected,error)) return false;
        const auto& a=*source.armyById(request.armyId);
        const auto& definition=data::kUnitTypes[projected.type]; const int cls=definition.unitClass;
        CombatStatsContext stats; stats.combatants.push_back(projected); ArmyPowerReport r;
        if (!combatStat(source,stats,{0},CombatStat::Defense,r.defense,error)) return false;
        r.remainingDefense=add(r.defense,-int32_t(a.unk_2c));
        if (request.flags[0] && (cls==1 || cls==6 || cls==7 || cls==11) && projected.type!=23)
            r.remainingDefense=mul(r.remainingDefense,2);
        else if (technology(source,a.owner,19) && cls==10) r.remainingDefense=mul(r.remainingDefense,2);
        if (!combatStat(source,stats,{0},CombatStat::Accuracy,r.accuracy,error)) return false;
        const int domain=definition.domain;
        if ((request.flags[1] && (domain==1 || domain==6) && cls!=10) ||
            (request.flags[2] && domain==3 && cls!=9)) r.accuracy=add(r.accuracy,15);
        // The fourth flag's domain2 && domain6 comparison is impossible in the
        // assembly. It falls through to technology23, even when nonzero.
        else if (technology(source,a.owner,23) && cls==10) r.accuracy=add(r.accuracy,15);
        if (!combatStat(source,stats,{0},CombatStat::Attack,r.attack,error)) return false;
        r.product=mul(mul(r.attack,r.remainingDefense),r.accuracy);
        if (!combatStat(source,stats,{0},CombatStat::RateOfFire,r.rateOfFire,error)) return false;
        r.score=r.product/std::max(r.rateOfFire,int32_t(1));
        if (cls==9 || cls==20) r.score/=10;
        report=r; error={}; return true;
    },error);
}

// orig:0045727c; zero snapshot, collect foreign groups, compare then withdraw.
bool resolveMovementCrossings(const save::Document& source,const AiSession& bindings,
    const MovementCrossingsContext& context,save::Document& destination,
    MovementCrossingsReport& report,save::Error& error) {
    return guarded([&] {
        if (!checkedDocument(source,error)) return false;
        SessionRng rng; if (!rng.restore(context.ai.rng,error)) return false;
        if (context.ai.pendingMessages.size()>kAiMessageCapacity)
            return fail(error,"Crossing AI message FIFO exceeds its original capacity",save::ErrorCode::Limit);
        auto d=std::make_unique<save::Document>(source); auto result=std::make_unique<MovementCrossingsReport>();
        result->contextAfter=context;
        for (const auto& record:d->territories) {
            const auto& t=record.data; if (!t.numTiles) continue;
            std::set<uint32_t> visited;
            for (uint32_t id=t.foreignArmies.raw;id;) {
                const auto* a=d->armyById(id);
                if (!a || !visited.insert(id).second) return fail(error,"Crossing snapshot follows an unresolved or cyclic foreign list");
                const uint32_t next=a->next.raw; bool accepted;
                if (!eligible(*a,accepted,error)) return false;
                if (accepted) {
                    if (!territory(*d,army::turnStart(*a),error) || !owner(a->owner,error)) return false;
                    MovementCrossingContribution contribution{t.index,id,-1,std::nullopt};
                    auto& row=result->groups[t.index];
                    for (int slot=0;slot<10;++slot)
                        if (!row[size_t(slot)].count || (row[size_t(slot)].origin==int32_t(army::turnStart(*a)) && row[size_t(slot)].player==a->owner)) {
                            contribution.group=slot; auto& group=row[size_t(slot)];
                            group.origin=int32_t(army::turnStart(*a)); group.player=a->owner;
                            ArmyPowerReport power;
                            if (!scoreArmyPower(*d,{id,{}},power,error)) return false;
                            group.power=add(group.power,power.score); group.count=add(group.count,1);
                            contribution.score=power; break;
                        }
                    result->contributions.push_back(std::move(contribution));
                }
                id=next;
            }
        }
        for (uint32_t a=1;a<=d->territories.size();++a) {
            if (!d->territories[a-1].data.numTiles) continue;
            for (uint32_t b=1;b<=d->territories.size();++b) {
                if (!d->territories[b-1].data.numTiles) continue;
                for (int ga=0;ga<10;++ga) for (int gb=0;gb<10;++gb) {
                    const auto& first=result->groups[a][size_t(ga)]; const auto& second=result->groups[b][size_t(gb)];
                    if (first.player==second.player || hasAiPact(*d,first.player,second.player,2) ||
                        first.origin!=int32_t(b) || second.origin!=int32_t(a) || a>=b) continue;
                    MovementCrossingResolution crossing;
                    crossing.territoryA=a; crossing.territoryB=b; crossing.groupA=ga; crossing.groupB=gb;
                    crossing.productA=mul(first.power,first.count); crossing.productB=mul(second.power,second.count);
                    const bool bLoses=crossing.productB<=crossing.productA;
                    crossing.loser=bLoses?second.player:first.player; crossing.winner=bLoses?first.player:second.player;
                    crossing.from=bLoses?b:a; crossing.retreatTo=bLoses?a:b;
                    // Keep exactly the pre-call next of EACH live node, not a
                    // frozen ID list. A moved passenger may redirect this walk.
                    for (uint32_t id=d->territories[crossing.from-1].data.foreignArmies.raw;id;) {
                        if (result->traversalSteps>=context.maximumTraversalSteps)
                            return fail(error,"Crossing withdrawal exceeds its explicit traversal limit",save::ErrorCode::Limit);
                        ++result->traversalSteps;
                        const auto* unit=d->armyById(id);
                        if (!unit) return fail(error,"Crossing withdrawal follows an unresolved captured-next unit");
                        const uint32_t next=unit->next.raw;
                        if (unit->owner==crossing.loser && army::turnStart(*unit)==crossing.retreatTo) {
                            bool accepted; if (!eligible(*unit,accepted,error)) return false;
                            if (accepted) {
                                UnitMovementReport movement;
                                if (!moveUnit(*d,{id,army::turnStart(*unit),0},result->contextAfter.movement,*d,movement,error)) return false;
                                result->contextAfter.movement=movement.contextAfter;
                                crossing.moves.push_back(std::move(movement));
                            }
                        }
                        id=next;
                    }
                    if (!deliver(*d,bindings,*result,crossing,error)) return false;
                    result->crossings.push_back(std::move(crossing));
                }
            }
        }
        if (!save::validate(*d,error)) return false;
        destination=std::move(*d); report=std::move(*result); error={}; return true;
    },error);
}
} // namespace dl2::simulation
