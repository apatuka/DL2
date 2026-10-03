#include "game/shrine_consequences.h"
#include "game/data_tables.h"
#include <algorithm>
#include <bit>
#include <cstring>
#include <memory>
#include <new>
#include <stdexcept>
#include <string>
#include <utility>

namespace dl2::simulation {
namespace {
bool fail(save::Error& error,const char* message,save::ErrorCode code=save::ErrorCode::InvalidState) {
    error={code,0,message}; return false;
}
bool name(const save::Document& d,uint32_t territory,std::string& result,save::Error& error) {
    const auto& t=d.territories[territory-1].data;
    const auto* end=static_cast<const char*>(std::memchr(t.name,0,sizeof(t.name)));
    if (!end) return fail(error,"Shrine event territory name lacks a bounded terminator");
    result.assign(t.name,size_t(end-t.name)); return true;
}
// Original00423690 passes zero extended words to AI for80;004237d0 passes
// the offender index and zero for81. Formatting arguments are NOT AI payload.
bool emit(save::Document& d,int recipient,uint16_t type,uint32_t territory,int offender,
          const std::string& race,const ConstructionOrderContext& context,
          ShrineConsequencesReport& result,save::Error& error) {
    ConstructionOrderEvent event; event.type=type; event.recipient=recipient;
    if (recipient==d.options.localPlayer) {
        std::string region; if (!name(d,territory,region,error)) return false;
        LocalEventRequest request; request.type=type;
        if (type==80) request.arguments={region};
        else { request.arguments={race,region}; request.payload=EventPayload{offender,0}; }
        auto input=context.events; input.rngBeforeEvents=result.rngAfter;
        event.local=true;
        if (!logLocalEvent(d,result.logAfter,input,request,result.logAfter,event.localReport,error)) return false;
        result.rngAfter=event.localReport.rngAfter;
    } else if (std::bit_cast<int8_t>(d.players[size_t(recipient)].type)>=3) {
        if (!context.aiSession) return fail(error,"Shrine event requires initialized owned AI bindings");
        event.aiDispatched=true; result.aiAfter.rng=result.rngAfter;
        if (!context.aiSession->reactEvent(d,{recipient,type,type==81?offender:0,0},
            result.aiAfter,d,event.aiReport,error)) return false;
        result.aiAfter=event.aiReport.contextAfter; result.rngAfter=result.aiAfter.rng;
    }
    result.aiAfter.rng=result.rngAfter; result.events.push_back(std::move(event)); return true;
}
bool penalty(save::Document& d,const PendingShrineEntry& entry,const ConstructionOrderContext& context,
             ShrineConsequencesReport& result,save::Error& error) {
    //0044b9e4 dereferences Player* now, not when0044b8f8 enqueued the pair.
    const int player=std::bit_cast<int8_t>(d.players[size_t(entry.playerSlot)].index);
    if (player<0 || player>=kMaxPlayers) return fail(error,"Pending shrine player index is outside0..6");
    ShrinePenalty applied; applied.playerSlot=entry.playerSlot; applied.playerIndex=player;
    applied.territory=entry.territory;
    if (!emit(d,player,80,entry.territory,player,{},context,result,error)) return false;
    // The original race-table access uses the resolved INDEX, not queued slot.
    const int race=d.players[size_t(player)].race;
    if (race<0 || race>=kMaxPlayers) return fail(error,"Shrine offender race is outside the canonical name table");
    const std::string raceName=data::kRaceNames[size_t(race)];
    for (int recipient=0;recipient<kMaxPlayers;++recipient)
        if (recipient!=player && !emit(d,recipient,81,entry.territory,player,raceName,context,result,error)) return false;
    // AI dispatch can replace the candidate Document: acquire references only
    // AFTER all seven original event calls have completed.
    for (size_t i=0;i<d.territories.size();++i) {
        auto& t=d.territories[i].data;
        if (t.owner!=player) continue;
        const int8_t before=t.morale;
        t.morale=int8_t(std::max(0,int(before)-20));
        applied.morale.push_back({uint32_t(i+1),before,t.morale});
    }
    auto& score=d.scores[size_t(player)];
    applied.nukesUsedBefore=score.nukesUsed;
    score.nukesUsed=uint8_t(uint32_t(score.nukesUsed)+1u);
    applied.nukesUsedAfter=score.nukesUsed;
    result.penalties.push_back(std::move(applied)); return true;
}
}

bool processPendingShrineConsequences(const save::Document& source,const PendingShrineState& pending,
    const ConstructionOrderContext& context,save::Document& destination,
    ShrineConsequencesReport& report,save::Error& error) {
    try {
        if (!save::validate(source,error)) return false;
        if (source.header.isMap) return fail(error,"Shrine consequences require a saved game");
        if (pending.entries.size()>kPendingShrineCapacity)
            return fail(error,"Pending shrine queue exceeds its native ten-entry capacity",save::ErrorCode::Limit);
        for (const auto& entry:pending.entries)
            if (entry.playerSlot<0 || entry.playerSlot>=kMaxPlayers || !source.territoryByIndex(entry.territory))
                return fail(error,"Pending shrine reference lies outside the owned document");
        if (context.ai.rng!=context.events.rngBeforeEvents)
            return fail(error,"Shrine events require a shared initial AI/event RNG");
        SessionRng rng; if (!rng.restore(context.events.rngBeforeEvents,error)) return false;
        ShrineConsequencesReport result; result.pendingAfter=pending; result.logAfter=context.log;
        result.aiAfter=context.ai; result.rngAfter=rng.snapshot(); result.citiesAfter=context.events.citiesBeforeLoad;
        auto candidate=std::make_unique<save::Document>(source);
        // pending may alias report.pendingAfter, so walk the private copy.
        for (const auto& entry:result.pendingAfter.entries)
            if (!penalty(*candidate,entry,context,result,error)) return false;
        if (!save::validate(*candidate,error)) return false;
        destination=std::move(*candidate); report=std::move(result); error={}; return true;
    } catch (const std::bad_alloc&) { return fail(error,"Shrine consequences allocation failed",save::ErrorCode::Limit); }
      catch (const std::length_error&) { return fail(error,"Shrine consequences container limit exceeded",save::ErrorCode::Limit); }
      catch (const std::exception& e) { error={save::ErrorCode::InvalidState,0,e.what()}; return false; }
}
} // namespace dl2::simulation
