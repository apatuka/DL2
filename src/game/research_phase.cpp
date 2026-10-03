#include "game/research_phase.h"
#include "game/research_rules.h"
#include "game/data_tables.h"
#include <algorithm>
#include <array>
#include <bit>
#include <cstring>
#include <memory>
#include <new>
#include <stdexcept>

namespace dl2::simulation {
namespace {
bool fail(save::Error& e,const char* why) { e={save::ErrorCode::InvalidState,0,why}; return false; }
int32_t add(int32_t a,int32_t b) { return std::bit_cast<int32_t>(uint32_t(a)+uint32_t(b)); }
int16_t short16(int32_t n) { return std::bit_cast<int16_t>(uint16_t(uint32_t(n))); }
bool has(uint16_t value,int player) { return (uint32_t(int32_t(std::bit_cast<int16_t>(value)))&(1u<<(uint32_t(player)&31u)))!=0; }
bool valid(const save::Document& d,save::Error& e) {
    if (!save::validate(d,e)) return false;
    return !d.header.isMap || fail(e,"Research requires a saved game");
}
bool techValid(int tech,save::Error& e) { return (tech>=0 && tech<kNumTechs) || fail(e,"Research technology is outside0..47"); }
bool playerValid(int p,save::Error& e) { return (p>=0 && p<kMaxPlayers) || fail(e,"Research player is outside0..6"); }
std::array<int,4> prerequisites(int tech) {
    const auto& row=data::kTechs[tech];
    // Original reads FOUR WORDs +24,+26,+28,+2a. All48 PE +2a words are0;
    // do not reinterpret the native-pointer-bearing C++ canonical struct.
    return {row.prereq[0],row.prereq[1],row.prereq[2],0};
}
bool allowed(const save::Document& d,uint32_t flags,int race,int tech,bool& result,save::Error& e) {
    result=true;
    //0044fe1c(4) tests the explicit live campaign goal mask BEFORE looking up
    // a campaign table. A cold caller may deliberately supply the disabled bit.
    if (!(flags&16u)) return true;
    if (d.options.campaign<0 || d.options.campaign>=data::kNumCampaigns) return fail(e,"Research campaign is outside0..42");
    //00450150/00450000: first type4 goal; +04 is race count, payload starts+08.
    for (const auto& goal:data::kCampaigns[d.options.campaign].goals) if (goal.type==4) {
        if (goal.turns<0 || goal.turns>=14) return fail(e,"Research campaign payload leaves its canonical goal");
        const auto item=[&](int i){return i?goal.list[i-1]:goal.count;};
        for (int i=0;i<goal.turns;++i) if (race==item(i) && tech==item(goal.turns)) result=false;
        return true;
    }
    //0044fdf0 returns3 when no type4 exists, so the following native lookup
    // leaves this campaign's three-goal object. Do not invent a fourth goal.
    return fail(e,"Research campaign flag4 has no matching owned campaign goal");
}
bool bonusMask(const save::Document& d,uint32_t& result,save::Error& e) {
    result=0;
    //0048389c: DAT0055a102 ==RaceStats+55*7*2, signed race/WORD.
    for (int p=0;p<kMaxPlayers;++p) {
        const int word=55*kMaxPlayers+int(d.players[size_t(p)].race);
        if (word<0 || word>=int(sizeof(RaceStats)/2)) return fail(e,"Research racial bonus address leaves owned RaceStats");
        int16_t value; std::memcpy(&value,reinterpret_cast<const uint8_t*>(&d.raceStats)+size_t(word)*2,2);
        if (value) result|=1u<<p;
    }
    return true;
}
bool pact(const save::Document& d,int a,int b) {
    if (!d.options.allowAlliances || a<0 || b<0 || a>=d.options.numPlayers || b>=d.options.numPlayers) return false;
    return (d.players[size_t(a)].relations[size_t(b)]&0x18u)!=0;
}
template<class Range,class Value>
bool queueAllowedRaw(const save::Document& d,int player,const Range& queue,Value value,
                     int tech,uint32_t flags,bool& result,save::Error& e) {
    if (!techValid(tech,e)) return false;
    if (has(d.techs[size_t(tech)].availableMask,player)) { result=true; return true; }
    result=false; bool campaign=true;
    //00457a58(3) and00457ac0(3) BOTH return10 in original PE.
    if (has(d.techs[size_t(tech)].knownMask,player) || std::bit_cast<int16_t>(data::kTechs[tech].level)>=10 || tech==47) return true;
    if (!allowed(d,flags,d.players[size_t(player)].race,tech,campaign,e)) return false;
    if (!campaign) return true;
    uint32_t bonus;
    if (!bonusMask(d,bonus,e)) return false;
    int missing=0,present=0; const auto required=prerequisites(tech);
    for (int dependency:required) if (dependency && !has(d.techs[size_t(dependency)].knownMask,player)) ++missing;
    // Native queue matching intentionally includes zero prerequisites and
    // duplicate entries; this is not a normalized dependency set.
    for (const auto& node:queue) for (int dependency:required) if (uint32_t(dependency)==value(node)) {
        if (bonus&(1u<<player)) { result=true; return true; }
        ++present;
    }
    result=present==missing; return true;
}
bool pruneQueueRaw(const save::Document& d,int player,uint32_t flags,
                   std::vector<uint32_t>& values,std::vector<uint32_t>& removed,save::Error& e) {
    std::vector<std::pair<size_t,uint32_t>> queue;
    for (size_t i=0;i<values.size();++i) queue.emplace_back(i,values[i]);
    //00483b84 preserves node identity while removing FIRST matching value,
    // not necessarily the currently visited duplicate node.
    size_t current=queue.empty()?SIZE_MAX:queue.front().first;
    while (current!=SIZE_MAX) {
        const auto at=std::find_if(queue.begin(),queue.end(),[&](auto node){return node.first==current;});
        if (at==queue.end()) return fail(e,"Research queue cursor lost its owned node");
        const size_t following=at+1==queue.end()?SIZE_MAX:(at+1)->first;
        const uint32_t value=at->second;
        if (value>=kNumTechs) return fail(e,"Research queue entry indexes outside canonical technology table");
        bool permitted;
        if (!queueAllowedRaw(d,player,queue,[](auto node){return node.second;},int(value),flags,permitted,e)) return false;
        if (!permitted) {
            const auto first=std::find_if(queue.begin(),queue.end(),[&](auto node){return node.second==value;});
            removed.push_back(value); queue.erase(first);
        }
        current=following;
    }
    values.clear(); for (const auto& node:queue) values.push_back(node.second);
    return true;
}
struct Work {
    save::Document& d; const ConstructionOrderContext& context; ResearchReport& r; save::Error& e;
    bool emit(int recipient,uint16_t type,int tech=0,int extra=0) {
        if (!playerValid(recipient,e)) return false;
        ConstructionOrderEvent event; event.type=type; event.recipient=recipient;
        if (recipient==d.options.localPlayer) {
            LocalEventRequest request; request.type=type;
            if (type!=57) { request.arguments={std::string(data::kTechs[tech].name)}; request.payload=EventPayload{extra,0}; }
            auto input=context.events; input.rngBeforeEvents=r.rngAfter; event.local=true;
            if (!logLocalEvent(d,r.logAfter,input,request,r.logAfter,event.localReport,e)) return false;
            r.rngAfter=event.localReport.rngAfter;
        } else if (std::bit_cast<int8_t>(d.players[size_t(recipient)].type)>=3) {
            if (!context.aiSession || context.ai.rng!=context.events.rngBeforeEvents)
                return fail(e,"Research event requires owned AI bindings and shared initial RNG");
            event.aiDispatched=true; r.aiAfter.rng=r.rngAfter;
            if (!context.aiSession->reactEvent(d,{recipient,type,type==57?0:extra,0},r.aiAfter,d,event.aiReport,e)) return false;
            r.aiAfter=event.aiReport.contextAfter; r.rngAfter=r.aiAfter.rng;
        }
        r.aiAfter.rng=r.rngAfter; r.events.push_back(std::move(event)); return true;
    }
    bool localQueue(int tech,TechnologyAcquisition& change) {
        auto queue=d.localList;
        const auto first=std::find(queue.begin(),queue.end(),uint32_t(tech));
        if (first!=queue.end()) { change.removedFromLocalQueue.push_back(uint32_t(tech)); queue.erase(first); }
        if (!pruneQueueRaw(d,d.options.localPlayer,context.researchCampaignFlags,queue,change.removedFromLocalQueue,e)) return false;
        d.localList=queue;
        if (queue.empty()) {
            //00483bd4 DOES NOT clear currentResearch when the queue is empty.
            if (!emit(d.options.localPlayer,57)) return false;
        } else d.players[size_t(d.options.localPlayer)].currentResearch=int8_t(queue.front()); //0048424c offline.
        return true;
    }
    bool acquire(int player,int tech) {
        if (!playerValid(player,e) || !techValid(tech,e)) return false;
        TechnologyAcquisition change; change.player=player; change.technology=tech;
        change.researchBefore=change.researchAfter=d.players[size_t(player)].currentResearch;
        if (has(d.techs[size_t(tech)].knownMask,player)) { r.acquisitions.push_back(std::move(change)); return true; }
        change.newlyKnown=true; const uint16_t bit=uint16_t(1u<<player);
        if (tech==33) for (auto& record:d.territories) {
            bool shrine=false;
            for (const auto& site:record.data.sites) { const auto* b=d.buildingById(site.building.raw); if (b && b->category==11) { shrine=true; break; } }
            auto* bytes=reinterpret_cast<uint8_t*>(&record.data); const int32_t present=shrine?1:0;
            std::memcpy(bytes+0x978+player*4,&present,4);
            if (shrine) { uint32_t mask; std::memcpy(&mask,bytes+0x8b0,4); mask|=bit; std::memcpy(bytes+0x8b0,&mask,4); change.revealedShrines.push_back(record.data.index); }
        }
        d.techs[size_t(tech)].knownMask|=bit; d.techs[size_t(tech)].availableMask&=uint16_t(~bit);
        if (player==d.options.localPlayer && !localQueue(tech,change)) return false;
        uint32_t bonus;
        if (!bonusMask(d,bonus,e)) return false;
        const auto makeAvailable=[&](int technology) {
            if (!(d.techs[size_t(technology)].availableMask&bit)) change.newlyAvailable.push_back(technology);
            d.techs[size_t(technology)].availableMask|=bit;
        };
        for (int candidate=1;candidate<47;++candidate) {
            if (has(d.techs[size_t(candidate)].knownMask,player) || std::bit_cast<int16_t>(data::kTechs[candidate].level)>=10) continue;
            bool campaign;
            if (!allowed(d,context.researchCampaignFlags,d.players[size_t(player)].race,candidate,campaign,e)) return false;
            if (!campaign) continue;
            bool all=true;
            for (int dependency:prerequisites(candidate)) if (dependency) {
                if (!has(d.techs[size_t(dependency)].knownMask,player)) all=false;
                else if (bonus&bit) makeAvailable(candidate);
            }
            if (all) makeAvailable(candidate);
        }
        if (!has(d.techs[47].knownMask,player)) {
            bool campaign;
            if (!allowed(d,context.researchCampaignFlags,d.players[size_t(player)].race,47,campaign,e)) return false;
            if (campaign) { bool all=true; for (int i=1;i<47;++i) if (!has(d.techs[size_t(i)].knownMask,player)) all=false;
                if (all) makeAvailable(47); }
        }
        change.researchAfter=d.players[size_t(player)].currentResearch;
        r.acquisitions.push_back(std::move(change)); return true;
    }
    bool player(int slot) {
        const int index=std::bit_cast<int8_t>(d.players[size_t(slot)].index);
        const int tech=d.players[size_t(slot)].currentResearch;
        if (!playerValid(index,e) || !techValid(tech,e)) return false;
        const int32_t points=d.players[size_t(slot)].lastIncome;
        auto& progress=d.techs[size_t(tech)].progress[index];
        ResearchPlayerChange change{slot,index,tech,points,std::bit_cast<int16_t>(data::kTechs[tech].cost),std::bit_cast<int16_t>(progress),0,false};
        progress=uint16_t(uint32_t(add(std::bit_cast<int16_t>(progress),short16(points)))); change.progressAfter=std::bit_cast<int16_t>(progress);
        if ((points || tech) && change.required<=change.progressAfter) {
            change.thresholdReached=true;
            if (has(d.techs[4].knownMask,index)) {
                const int32_t excess=(int32_t(change.progressAfter)-change.required)/5;
                int count=0; for (const auto& t:d.territories) if (t.data.numTiles && t.data.owner==index && t.data.population) ++count;
                if (count) for (auto& t:d.territories) if (t.data.numTiles && t.data.owner==index && t.data.population) {
                    auto& stock=t.data.materials[8]; const int32_t before=stock; stock=add(stock,excess/count);
                    r.excess.push_back({index,t.data.index,before,stock,excess/count});
                }
            }
            if (tech && !has(d.techs[size_t(tech)].knownMask,index)) {
                if (!emit(index,54,tech,tech)) return false;
                for (int other=0;other<kMaxPlayers;++other) if (other!=index && pact(d,index,other)) {
                    if (!emit(other,56,tech,index) || !acquire(other,tech)) return false;
                    if (std::bit_cast<int8_t>(d.players[size_t(slot)].type)>2) {
                        AiReactionReport attitude; r.aiAfter.rng=r.rngAfter;
                        if (!changeAiAttitude(d,{index,other,-4},r.aiAfter,d,attitude,e)) return false;
                        r.aiAfter=attitude.contextAfter; r.rngAfter=r.aiAfter.rng;
                        r.attitudes.insert(r.attitudes.end(),attitude.attitudes.begin(),attitude.attitudes.end());
                    }
                }
            }
            if (d.players[size_t(slot)].currentResearch && !acquire(index,tech)) return false;
        }
        r.players.push_back(change); return true;
    }
};
bool initialize(const ConstructionOrderContext& context,ResearchReport& r,save::Error& e) {
    SessionRng rng; if (!rng.restore(context.events.rngBeforeEvents,e)) return false;
    if (context.ai.rng!=context.events.rngBeforeEvents) return fail(e,"Research requires one shared event/AI RNG");
    r.logAfter=context.log; r.aiAfter=context.ai; r.rngAfter=rng.snapshot(); return true;
}
template<class Operation> bool guarded(Operation&& operation,save::Error& e) {
    try { return operation(); }
    catch (const std::bad_alloc&) { e={save::ErrorCode::Limit,0,"Research allocation failed"}; }
    catch (const std::exception& ex) { e={save::ErrorCode::InvalidState,0,ex.what()}; }
    return false;
}
} // namespace

namespace research_detail {
bool campaignAllowed(const save::Document& source,uint32_t flags,int race,int technology,
                     bool& result,save::Error& error) {
    return guarded([&] {
        if (!valid(source,error) || !techValid(technology,error)) return false;
        bool answer;
        if (!allowed(source,flags,race,technology,answer,error)) return false;
        result=answer; error={}; return true;
    },error);
}
bool canQueue(const save::Document& source,int player,std::span<const uint32_t> queue,
              int technology,uint32_t flags,bool& result,save::Error& error) {
    return guarded([&] {
        if (!valid(source,error) || !playerValid(player,error)) return false;
        if (queue.size()>save::kMaxListNodes) { error={save::ErrorCode::Limit,0,"Research queue exceeds owned4096-node limit"}; return false; }
        bool answer;
        if (!queueAllowedRaw(source,player,queue,[](uint32_t value){return value;},technology,flags,answer,error)) return false;
        result=answer; error={}; return true;
    },error);
}
bool pruneQueue(const save::Document& source,int player,uint32_t flags,
                std::vector<uint32_t>& queue,std::vector<uint32_t>& removed,save::Error& error) {
    return guarded([&] {
        if (!valid(source,error) || !playerValid(player,error)) return false;
        if (&queue==&removed) return fail(error,"Research queue and removal report must be distinct outputs");
        if (&queue==&source.localList || &removed==&source.localList)
            return fail(error,"Research pruning output must not alias the read-only source queue");
        if (queue.size()>save::kMaxListNodes) { error={save::ErrorCode::Limit,0,"Research queue exceeds owned4096-node limit"}; return false; }
        auto candidate=queue, discarded=removed;
        if (!pruneQueueRaw(source,player,flags,candidate,discarded,error)) return false;
        queue=std::move(candidate); removed=std::move(discarded); error={}; return true;
    },error);
}
} // namespace research_detail

bool chooseStealableTechnology(const save::Document& source,int thief,int victim,const RngSnapshot& rng,
    StealableTechnologyReport& report,save::Error& error) {
    return guarded([&] {
        if (!valid(source,error)) return false;
        if (thief<0 || thief>255 || victim<0 || victim>255) return fail(error,"Stealable-technology players must fit original byte arguments");
        SessionRng random; if (!random.restore(rng,error)) return false;
        StealableTechnologyReport result;
        if (!random.apply({RngOperation::TaggedRange,48,0,"Steal Tech"},result.draw,error)) return false;
        for (int n=0;n<48;++n) { const int tech=(int(result.draw.value)+n)%48;
            if (has(source.techs[size_t(tech)].knownMask,victim) && !has(source.techs[size_t(tech)].knownMask,thief)) { result.technology=tech; break; } }
        result.rngAfter=random.snapshot(); report=std::move(result); error={}; return true;
    },error);
}
bool acquireTechnology(const save::Document& source,int player,int technology,const ConstructionOrderContext& context,
    save::Document& destination,ResearchReport& report,save::Error& error) {
    return guarded([&] {
        if (!valid(source,error)) return false;
        auto candidate=std::make_unique<save::Document>(source); ResearchReport result;
        if (!initialize(context,result,error)) return false;
        Work work{*candidate,context,result,error};
        if (!work.acquire(player,technology) || !save::validate(*candidate,error)) return false;
        destination=std::move(*candidate); report=std::move(result); error={}; return true;
    },error);
}
bool processResearch(const save::Document& source,const ConstructionOrderContext& context,
    save::Document& destination,ResearchReport& report,save::Error& error) {
    return guarded([&] {
        if (!valid(source,error)) return false;
        if (source.options.numPlayers<0 || source.options.numPlayers>kMaxPlayers) return fail(error,"Research player count is outside0..7");
        auto candidate=std::make_unique<save::Document>(source); ResearchReport result;
        if (!initialize(context,result,error)) return false;
        Work work{*candidate,context,result,error};
        for (int player=0;player<candidate->options.numPlayers;++player) if (!work.player(player)) return false;
        if (!save::validate(*candidate,error)) return false;
        destination=std::move(*candidate); report=std::move(result); error={}; return true;
    },error);
}
} // namespace dl2::simulation
