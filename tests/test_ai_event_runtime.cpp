// Owned runtime publication/locking for the explicit human-response profile.
#include "game/runtime_state.h"
#include <cstring>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>
namespace {
using namespace dl2;
using namespace dl2::simulation;
void require(bool value,const char* message) { if (!value) throw std::runtime_error(message); }
void word(Job& job,int p,int q,int32_t value) {
    std::memcpy(reinterpret_cast<uint8_t*>(&job)+size_t(p*7+q)*4,&value,4);
}
int32_t word(const Job& job,int p,int q) {
    int32_t value; std::memcpy(&value,reinterpret_cast<const uint8_t*>(&job)+size_t(p*7+q)*4,4); return value;
}
std::unique_ptr<save::Document> fixture(bool military=false) {
    auto d=std::make_unique<save::Document>();
    std::memcpy(d->header.text,save::kHeaderText,sizeof(save::kHeaderText));
    d->header.version=kSaveVersion; d->header.minusOne=-1;
    d->options.numPlayers=2; d->options.localPlayer=0; d->options.turn=7; d->options.allowAlliances=1;
    d->world.width=d->world.height=1; d->world.numTerritories=1;
    d->tiles.resize(1); d->tiles[0].territory=1; d->territories.resize(1); d->territories[0].data.index=1;
    for (int p=0;p<7;++p) {
        d->players[size_t(p)].index=uint8_t(p); d->players[size_t(p)].race=int8_t(p);
        d->players[size_t(p)].type=p==0?1:p==1?3:0; d->ministerJobs[size_t(p)].resize(1);
        for (int q=0;q<7;++q) word(d->scratchJob1,p,q,-50);
        for (auto& job:d->jobs[size_t(p)]) { job.owner=int16_t(p); job.targetPlayer=-1; }
    }
    word(d->scratchJob1,1,0,50); d->players[1].relations2[0]=d->players[0].relations2[1]=military?13:6;
    d->armies.resize(1); auto& army=d->armies[0];
    army.id=101; army.type=1; army.owner=1; army.unitClass=1; army.health=100;
    army.territory.raw=army.origin.raw=army.dest.raw=1;
    save::Error error; require(save::validate(*d,error),"invalid runtime human fixture"); return d;
}
std::vector<uint8_t> bytes(const save::Document& d) {
    std::vector<uint8_t> result; save::Error error;
    if (!save::encode(d,result,error)) throw std::runtime_error(error.message); return result;
}
AiReactionContext context() {
    AiReactionContext c; c.rng.initialized=true; c.negotiation.emplace();
    c.pendingMessages.push_back({1,1,31,3,{9,8,7}}); return c;
}
void locksMoveAndReject() {
    auto d=fixture(); auto captured=fixture(); runtime::State state; save::Error error;
    require(state.prepare(*d,error),"cannot prepare human runtime");
    const auto original=bytes(*state.document()); const auto pointer=state.document();
    const auto rng=state.sessionRng(); const auto army=state.armyById(101),emptyArmy=runtime::ArmyHandle{};
    const auto territory=state.territoryByIndex(1); AiReactionReport report;
    require(army!=emptyArmy && state.beginAiEvent({1,0x73,2,0},context(),std::nullopt,report,error),
            "runtime failed to suspend human offer");
    const auto offer=*state.pendingAiOffer(); const auto pendingReport=report;
    auto unchanged=[&] {
        require(state.document()==pointer && bytes(*state.document())==original && state.stage()==runtime::Stage::Prepared &&
                state.sessionRng()==rng && !state.aiReactionContext() && !state.aiSession() && state.army(army) &&
                state.armyById(101)==army && state.territoryByIndex(1)==territory &&
                state.pendingAiOffer() && *state.pendingAiOffer()==offer,"pending operation changed public baseline or identities");
    };
    unchanged();
    const auto capturedBefore=bytes(*captured);
    require(!state.capture(*captured,error) && bytes(*captured)==capturedBefore,"pending operation escaped through capture");
    require(!state.prepare(*d,error),"prepare discarded the pending offer");
    TaxPlan taxes; EnergyPlan energy; LaborBalancePlan labor; runtime::LoadReport load;
    require(!state.collectTaxes(taxes,error) && !state.consumeEnergy(energy,error) && !state.normalizeLabor(labor,error) &&
            !state.normalizeLoad({},load,error),"pending offer allowed economy/load mutation");
    ArmyLifecycleReport removal;
    require(!state.removeArmy(army,ArmyRemovalKind::DeleteUnit,true,removal,error) &&
            !state.reactAiEvent({1,0x40,0,0},context(),report,error) && report==pendingReport &&
            !state.beginAiEvent({1,0x73,2,0},context(),std::nullopt,report,error) && report==pendingReport &&
            !state.advanceTurn(error),"pending offer allowed concurrent edits or another transaction");
    auto forged=offer; forged.mask=16;
    require(!state.answerAiOffer(forged,AiHumanAnswer::Accept,report,error) && report==pendingReport,
            "runtime accepted fabricated offer payload");
    runtime::State foreign; require(foreign.prepare(*d,error),"foreign prepare failed"); AiReactionReport foreignReport;
    require(foreign.beginAiEvent({1,0x73,2,0},context(),std::nullopt,foreignReport,error) &&
            !state.answerAiOffer(*foreign.pendingAiOffer(),AiHumanAnswer::Reject,report,error) && report==pendingReport,
            "runtime accepted a token from an independent state");
    unchanged();
    runtime::State moved=std::move(state);
    require(!state.document() && !state.pendingAiOffer() && moved.pendingAiOffer() && *moved.pendingAiOffer()==offer &&
            moved.army(army) && moved.territoryByIndex(1)==territory,"pending state move lost offer identity or handles");
    require(moved.answerAiOffer(offer,AiHumanAnswer::Reject,report,error) && !moved.pendingAiOffer() &&
            moved.stage()==runtime::Stage::EntitiesEdited && moved.sessionRng()==report.contextAfter.rng &&
            moved.aiReactionContext() && *moved.aiReactionContext()==report.contextAfter && moved.aiSession() &&
            moved.army(army) && word(moved.document()->scratchJob1,1,0)==42 &&
            moved.document()->players[1].relations[0]==0 && report.draws.size()==3,
            "explicit rejection did not publish its whole continuation atomically");
    const auto complete=bytes(*moved.document()); const auto completedReport=report;
    require(!moved.answerAiOffer(offer,AiHumanAnswer::Accept,report,error) && report==completedReport &&
            bytes(*moved.document())==complete && !moved.capture(*captured,error),"stale response or partial export was accepted");
}
void acceptAndCampaignContinuation() {
    auto d=fixture(true); d->options.campaign=1; runtime::State state; save::Error error; AiReactionReport report;
    require(state.prepare(*d,error),"campaign state preparation failed");
    BuildingRemovalContext campaign; campaign.campaignFlags=2; campaign.campaignProgress={40000,-70000,99999};
    campaign.pendingShrines.entries.push_back({0,1});
    const auto army=state.armyById(101);
    require(state.beginAiEvent({1,0x73,2,0},context(),campaign,report,error) && state.pendingAiOffer(),
            "campaign state did not suspend");
    const auto offer=*state.pendingAiOffer();
    require(!state.buildingRemovalContext() && offer.campaignCheckpoint==campaign,"pending campaign published before answer");
    require(state.answerAiOffer(offer,AiHumanAnswer::Accept,report,error),"campaign state acceptance failed");
    auto expected=campaign; expected.campaignProgress[0]=1;
    require(!state.pendingAiOffer() && state.buildingRemovalContext() && *state.buildingRemovalContext()==expected &&
            state.document()->players[1].relations[0]==2 && state.document()->players[0].relations[1]==2 && state.army(army) &&
            state.sessionRng()==report.contextAfter.rng,"campaign continuation was not shared/preserved at commit");
    const auto before=bytes(*state.document()); const auto saved=report;
    require(!state.beginAiEvent({1,0x40,0,0},*state.aiReactionContext(),campaign,report,error) && report==saved &&
            bytes(*state.document())==before,"runtime rewound the live campaign continuation");
    require(state.beginAiEvent({1,0x40,0,0},*state.aiReactionContext(),expected,report,error) && !state.pendingAiOffer() &&
            *state.buildingRemovalContext()==expected,"completed no-op event lost shared campaign state");
    // Failure after an explicit accept must preserve pending token/report and
    // baseline, allowing a subsequent real rejection on the same checkpoint.
    runtime::State missing; require(missing.prepare(*d,error),"missing campaign prepare failed");
    require(missing.beginAiEvent({1,0x73,2,0},context(),std::nullopt,report,error),"missing campaign begin failed");
    const auto pending=*missing.pendingAiOffer(); const auto pendingReport=report;
    const auto baseline=bytes(*missing.document()); const auto initialRng=missing.sessionRng();
    require(!missing.answerAiOffer(pending,AiHumanAnswer::Accept,report,error) && report==pendingReport &&
            *missing.pendingAiOffer()==pending && bytes(*missing.document())==baseline && missing.sessionRng()==initialRng,
            "failed acceptance destroyed runtime pending transaction");
    require(missing.answerAiOffer(pending,AiHumanAnswer::Reject,report,error) && !missing.pendingAiOffer(),
            "failed acceptance prevented real rejection");
}
}
int main() {
    try { locksMoveAndReject(); acceptAndCampaignContinuation(); std::cout<<"AI event runtime tests passed\n"; return 0; }
    catch (const std::exception& e) { std::cerr<<"AI event runtime: "<<e.what()<<'\n'; return 1; }
}
