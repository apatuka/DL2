#include "game/ai_pact_reconciliation.h"
#include <bit>
#include <exception>
#include <memory>
#include <new>
#include <stdexcept>
#include <utility>

namespace dl2::simulation {
namespace {
bool fail(save::Error& error,const char* message,
          save::ErrorCode code = save::ErrorCode::InvalidState) {
    error = {code,0,message}; return false;
}
int signedType(uint8_t type) { return type < 128 ? type : int(type)-256; }
std::array<uint32_t,4> pairWords(const save::Document& d,int p,int q) {
    return {d.players[size_t(p)].relations[q],d.players[size_t(q)].relations[p],
            d.players[size_t(p)].relations2[q],d.players[size_t(q)].relations2[p]};
}
} // namespace

// orig: FUN_00441400. No precomputed change list: notifications are reentrant.
bool reconcileAiPacts(const save::Document& source,const AiSession& ai,
    const AiPactReconciliationContext& context,save::Document& destination,
    AiPactReconciliationReport& report,save::Error& error) try {
    if (!save::validate(source,error)) return false;
    if (source.header.isMap) return fail(error,"AI pact reconciliation requires a saved game");
    if (context.ai.pendingMessages.size()>kAiMessageCapacity)
        return fail(error,"AI pact reconciliation message FIFO exceeds its original capacity",save::ErrorCode::Limit);
    SessionRng rng;
    if (!rng.restore(context.ai.rng,error)) return false;
    auto candidate=std::make_unique<save::Document>(source);
    AiPactReconciliationReport result; result.contextAfter=context;
    auto dispatch=[&](int recipient,int eventType,int p,int q,uint32_t changed)->bool {
        AiPactReconciliationDelivery delivery;
        delivery.recipient=recipient; delivery.eventType=eventType;
        delivery.player=p; delivery.other=q; delivery.changed=changed;
        if (recipient==candidate->options.localPlayer) {
            // Only the direct victim event58 routes to a local log; the
            // third-party loop below selects signed AI types, not humans.
            if (eventType!=0x3a)
                return fail(error,"AI pact reconciliation local slot must retain its offline human type");
            if (!result.contextAfter.log)
                return fail(error,"AI pact betrayal requires the explicit existing local event log");
            LocalEventRequest request;
            request.type=0x3a;
            request.arguments={int32_t(p),std::bit_cast<int32_t>(changed),int32_t(0),int32_t(0)};
            request.payload=EventPayload{p,std::bit_cast<int32_t>(changed)};
            LocalEventReport local;
            if (!logLocalEvent(*candidate,*result.contextAfter.log,
                    {result.contextAfter.ai.rng,result.contextAfter.cities},request,
                    *result.contextAfter.log,local,error)) return false;
            result.contextAfter.ai.rng=local.rngAfter;
            result.draws.insert(result.draws.end(),local.randomDraws.begin(),local.randomDraws.end());
            delivery.route=AiPactDeliveryRoute::LocalLog; delivery.stored=local.stored;
        } else if (signedType(candidate->players[size_t(recipient)].type)>=3) {
            AiReactionReport reaction;
            const int32_t extra2=eventType==0x3a ? std::bit_cast<int32_t>(changed) : q;
            if (!ai.reactEvent(*candidate,{recipient,eventType,p,extra2},result.contextAfter.ai,
                               *candidate,reaction,error)) return false;
            result.contextAfter.ai=reaction.contextAfter;
            result.draws.insert(result.draws.end(),reaction.draws.begin(),reaction.draws.end());
            delivery.route=AiPactDeliveryRoute::AiReaction;
            delivery.reaction=std::move(reaction);
        }
        result.deliveries.push_back(std::move(delivery)); return true;
    };
    for (int p=0;p<candidate->options.numPlayers;++p) {
        for (int q=0;q<candidate->options.numPlayers;++q) {
            AiPactReconciliationPair pair;
            pair.player=p; pair.other=q; pair.before=pairWords(*candidate,p,q);
            //0044144a..0044146d tests byte==0, not signed-positive or numPlayers.
            if (candidate->players[size_t(p)].type==0 || candidate->players[size_t(q)].type==0) {
                candidate->players[size_t(p)].relations[q]=0;
                candidate->players[size_t(q)].relations[p]=0;
                candidate->players[size_t(p)].relations2[q]=0;
                candidate->players[size_t(q)].relations2[p]=0;
                pair.clearedInactive=true;
            }
            pair.changed=candidate->players[size_t(p)].relations[q] ^ candidate->players[size_t(p)].relations2[q];
            if (pair.changed) {
                if (!dispatch(q,0x3a,p,q,pair.changed)) return false;
                for (int recipient=0;recipient<kMaxPlayers;++recipient) {
                    if (recipient==p || recipient==q || signedType(candidate->players[size_t(recipient)].type)<3) continue;
                    if (!dispatch(recipient,0x73,p,q,pair.changed)) return false;
                }
            }
            //0044152c..00441548 deliberately rereads both words after all
            // callbacks; intersect before copying BOTH secondary words.
            if (candidate->players[size_t(q)].relations[p]!=candidate->players[size_t(p)].relations[q]) {
                candidate->players[size_t(p)].relations[q]&=candidate->players[size_t(q)].relations[p];
                candidate->players[size_t(q)].relations[p]&=candidate->players[size_t(p)].relations[q];
            }
            candidate->players[size_t(p)].relations2[q]=candidate->players[size_t(p)].relations[q];
            candidate->players[size_t(q)].relations2[p]=candidate->players[size_t(q)].relations[p];
            pair.after=pairWords(*candidate,p,q); result.pairs.push_back(pair);
        }
    }
    if (!save::validate(*candidate,error)) return false;
    destination=std::move(*candidate); report=std::move(result); error={}; return true;
} catch (const std::bad_alloc&) {
    return fail(error,"Insufficient memory reconciling AI pacts",save::ErrorCode::Limit);
} catch (const std::length_error&) {
    return fail(error,"AI pact reconciliation trace exceeds allocation limits",save::ErrorCode::Limit);
} catch (const std::exception& exception) {
    error={save::ErrorCode::InvalidState,0,exception.what()}; return false;
}
} // namespace dl2::simulation
