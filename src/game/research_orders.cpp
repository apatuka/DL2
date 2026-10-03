#include "game/research_orders.h"
#include "game/research_rules.h"
#include "game/data_tables.h"
#include <algorithm>
#include <bit>
#include <memory>
#include <stdexcept>

namespace dl2::simulation {
namespace {
bool fail(save::Error& e,const char* why) { e={save::ErrorCode::InvalidState,0,why}; return false; }
bool valid(const save::Document& d,save::Error& e) {
    if (!save::validate(d,e)) return false;
    return !d.header.isMap || fail(e,"Research orders require a saved game");
}
bool playerValid(int player,save::Error& e) { return (player>=0 && player<kMaxPlayers) || fail(e,"Research selection player is outside0..6"); }
bool has(uint16_t mask,int player) {
    return (uint32_t(int32_t(std::bit_cast<int16_t>(mask)))&(1u<<(uint32_t(player)&31u)))!=0;
}
void set(save::Document& d,int player,uint8_t technology) {
    // orig:0048424c, one byte only. No progress or queue side effects.
    d.players[size_t(player)].currentResearch=std::bit_cast<int8_t>(technology);
}
bool defaultResearch(const save::Document& d,int player,uint32_t flags,int& technology,save::Error& e) {
    // orig:00483cbc. Available masks are tested before level; known/campaign
    // gates belong ONLY to the fallback. Player.index is a masked byte shift.
    const auto& p=d.players[size_t(player)]; const int index=p.index;
    for (int tech=1;tech<kNumTechs;++tech) if (has(d.techs[size_t(tech)].availableMask,index)) {
        if (std::bit_cast<int8_t>(p.type)>2 || std::bit_cast<int16_t>(data::kTechs[tech].level)<10) {
            technology=tech; return true;
        }
    }
    technology=0;
    // Both original feature-limit callbacks return10 for selector3.
    if (!has(d.techs[47].knownMask,index)) {
        bool allowed;
        if (!research_detail::campaignAllowed(d,flags,p.race,47,allowed,e)) return false;
        if (allowed) technology=47;
    }
    return true;
}
template<class Operation> bool guarded(Operation&& operation,save::Error& e) {
    try { return operation(); }
    catch (const std::bad_alloc&) { e={save::ErrorCode::Limit,0,"Research order allocation failed"}; }
    catch (const std::length_error&) { e={save::ErrorCode::Limit,0,"Research order exceeds allocation limits"}; }
    catch (const std::exception& ex) { e={save::ErrorCode::InvalidState,0,ex.what()}; }
    return false;
}
} // namespace

bool setResearchSelectionOffline(const save::Document& source,int player,uint8_t technology,
    save::Document& destination,ResearchSelectionChange& report,save::Error& error) {
    return guarded([&] {
        if (!valid(source,error) || !playerValid(player,error)) return false;
        auto candidate=std::make_unique<save::Document>(source);
        ResearchSelectionChange result{player,source.players[size_t(player)].currentResearch,std::bit_cast<int8_t>(technology),true};
        set(*candidate,player,technology);
        destination=std::move(*candidate); report=result; error={}; return true;
    },error);
}
bool chooseDefaultResearch(const save::Document& source,int player,uint32_t flags,int& technology,save::Error& error) {
    return guarded([&] {
        if (!valid(source,error) || !playerValid(player,error)) return false;
        int result;
        if (!defaultResearch(source,player,flags,result,error)) return false;
        technology=result; error={}; return true;
    },error);
}
bool applyResearchOrder(const save::Document& source,const ResearchOrderRequest& request,
    const ResearchOrderContext& context,save::Document& destination,ResearchOrderReport& report,save::Error& error) {
    return guarded([&] {
        if (!valid(source,error) || !playerValid(request.actor,error)) return false;
        const auto& actor=source.players[size_t(request.actor)];
        // Authorization policy for this command, NOT validation in0048424c.
        if (request.actor!=source.options.localPlayer || actor.type!=1 || actor.index!=request.actor)
            return fail(error,"Research command requires matching local human actor and Player.index");
        switch (request.kind) {
        case ResearchOrderKind::Select: case ResearchOrderKind::ToggleQueue:
            if (request.technology<1 || request.technology>=kNumTechs) return fail(error,"Research command technology is outside1..47");
            break;
        case ResearchOrderKind::ClearQueue: break;
        default: return fail(error,"Unknown research order kind");
        }
        ResearchOrderReport result; result.actor=request.actor; result.kind=request.kind; result.technology=request.technology;
        result.researchBefore=result.researchAfter=result.candidateResearch=actor.currentResearch;
        result.queueBefore=result.queueAfter=source.localList;
        std::vector<uint32_t> draft;
        // orig:0043ca24 ->004839e4 ->004838fc: opening deduplicates in order.
        for (uint32_t tech:source.localList) {
            if (tech>=kNumTechs) return fail(error,"Research command source queue contains a noncanonical technology");
            if (std::find(draft.begin(),draft.end(),tech)==draft.end()) draft.push_back(tech);
            else result.duplicatesDiscarded.push_back(tech);
        }
        bool accepted=true;
        if (request.kind==ResearchOrderKind::ClearQueue) {
            // orig:0043cb7c non-cheat branch. No event57 or pruning here.
            result.removed=draft; draft.clear();
        } else {
            const auto existing=std::find(draft.begin(),draft.end(),uint32_t(request.technology));
            if (request.kind==ResearchOrderKind::ToggleQueue && existing!=draft.end()) {
                // orig:0043cc5c ->0048394c ->00483b84.
                result.removed.push_back(*existing); draft.erase(existing);
                if (!research_detail::pruneQueue(source,request.actor,context.campaignFlags,draft,result.removed,error)) return false;
            } else {
                bool canQueue;
                const std::span<const uint32_t> queue=request.kind==ResearchOrderKind::Select?
                    std::span<const uint32_t>{}:std::span<const uint32_t>{draft};
                if (!research_detail::canQueue(source,request.actor,queue,request.technology,context.campaignFlags,canQueue,error)) return false;
                accepted=canQueue;
                if (!accepted) {
                    bool campaign;
                    // Original denied click queries this again to decide whether
                    // Oolan's campaign advice is displayed. Report it, no fake UI.
                    if (!research_detail::campaignAllowed(source,context.campaignFlags,actor.race,request.technology,campaign,error)) return false;
                    result.denial=campaign?ResearchOrderDenial::NotQueueable:ResearchOrderDenial::CampaignRestriction;
                } else {
                    if (request.kind==ResearchOrderKind::Select) { result.removed=draft; draft.clear(); }
                    draft.push_back(uint32_t(request.technology));
                }
            }
        }
        auto candidate=std::make_unique<save::Document>(source);
        if (accepted) {
            result.accepted=true;
            // orig:0043cbf8 ->00483a10. Even a byte-identical nonempty
            // draft has newly allocated identities replacing the old list.
            result.queueStructureChanged=!source.localList.empty() || !draft.empty();
            candidate->localList=std::move(draft); result.queueAfter=candidate->localList;
            if (candidate->localList.empty()) {
                result.usedDefault=true;
                if (!defaultResearch(*candidate,request.actor,context.campaignFlags,result.candidateResearch,error)) return false;
            } else result.candidateResearch=int(candidate->localList.front());
            if (result.candidateResearch!=context.commitComparison) {
                result.setterInvoked=true; result.setterPlayer=int(actor.index);
                set(*candidate,result.setterPlayer,uint8_t(result.candidateResearch));
            }
            result.researchAfter=candidate->players[size_t(request.actor)].currentResearch;
        } else {
            // Command rejection policy: don't silently commit the opened draft.
            result.duplicatesDiscarded.clear(); result.removed.clear();
        }
        if (!save::validate(*candidate,error)) return false;
        destination=std::move(*candidate); report=std::move(result); error={}; return true;
    },error);
}
bool autoResearchLocal(const save::Document& source,uint32_t flags,
    save::Document& destination,ResearchAutoReport& report,save::Error& error) {
    return guarded([&] {
        if (!valid(source,error)) return false;
        const int player=source.options.localPlayer;
        if (!playerValid(player,error)) return false;
        ResearchAutoReport result; result.player=player;
        result.researchBefore=result.researchAfter=result.candidateResearch=source.players[size_t(player)].currentResearch;
        bool evaluate=true;
        if (!result.researchBefore) {
            // orig:0046f7d0 scans the entire physical building pool. Dense live
            // records cover the nonzero category5 cells; no owner/work filter.
            result.searchedBuildings=true;
            result.foundResearchBuilding=std::any_of(source.buildings.begin(),source.buildings.end(),[](const Building& b) {
                return b.category==5 && (b.flags&6u)==6u;
            });
            evaluate=result.foundResearchBuilding;
        }
        auto candidate=std::make_unique<save::Document>(source);
        if (evaluate) {
            if (result.researchBefore<0 || result.researchBefore>=kNumTechs)
                return fail(error,"Automatic research selection indexes outside0..47");
            // Unlike00483cbc, this guard uses LOCAL SLOT, not Player.index.
            result.knownSelection=has(source.techs[size_t(result.researchBefore)].knownMask,player);
            if (result.knownSelection) {
                if (!defaultResearch(source,player,flags,result.candidateResearch,error)) return false;
                set(*candidate,player,uint8_t(result.candidateResearch)); result.setterInvoked=true;
                result.researchAfter=candidate->players[size_t(player)].currentResearch;
            }
        }
        destination=std::move(*candidate); report=result; error={}; return true;
    },error);
}
} // namespace dl2::simulation
