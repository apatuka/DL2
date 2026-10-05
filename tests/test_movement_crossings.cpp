// Original assembly-derived expectations; no executed-EXE oracle is claimed.
#include "game/movement_crossings.h"
#include "game/army_state.h"
#include "game/data_tables.h"
#include "game/globals.h"
#include "game/load_profile.h"
#include "game/rtl_compat.h"
#include "game/save_files.h"
#include <algorithm>
#include <bit>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

namespace {
using namespace dl2;
using namespace dl2::simulation;
void require(bool v,const char* m) { if (!v) throw std::runtime_error(m); }
void ok(bool v,const save::Error& e) { if (!v) throw std::runtime_error(e.message); }
std::unique_ptr<save::Document> fixture(size_t count=2) {
    auto d=std::make_unique<save::Document>();
    std::memcpy(d->header.text,save::kHeaderText,sizeof(save::kHeaderText));
    d->header.version=kSaveVersion; d->header.minusOne=-1;
    d->options.numPlayers=2; d->options.localPlayer=0; d->options.turn=17; d->options.allowAlliances=1;
    d->world.width=uint8_t(count); d->world.height=1; d->world.numTerritories=uint16_t(count);
    d->tiles.resize(count); d->territories.resize(count);
    for (int p=0;p<7;++p) {
        d->players[size_t(p)].index=uint8_t(p); d->players[size_t(p)].race=int8_t(p);
        d->players[size_t(p)].type=p==0?1:3; d->options.playerSkill[p]=2; d->ministerJobs[size_t(p)].resize(1);
        for (auto& job:d->jobs[size_t(p)]) { job.owner=int16_t(p); job.targetPlayer=-1; }
    }
    for (size_t i=0;i<count;++i) {
        auto& t=d->territories[i].data; t.index=uint16_t(i+1); t.owner=int8_t(i%2); t.terrain=1;
        t.numTiles=1; t.tiles[0].raw=uint32_t(i); d->tiles[i].territory=int16_t(t.index);
        d->tiles[i].x=uint8_t(i); d->tiles[i].y=0;
        const std::string name="Territory"+std::to_string(i+1); std::memcpy(t.name,name.c_str(),name.size()+1);
    }
    d->trailing={0xab,0xcd}; return d;
}
Army& army(save::Document& d,uint32_t id) {
    for (auto& a:d.armies) if (a.id==id) return a; throw std::runtime_error("missing fixture army");
}
uint32_t unit(save::Document& d,int type,int owner,uint32_t current,uint32_t origin) {
    Army a{}; a.id=uint16_t(d.armies.size()+1); a.type=uint8_t(type); a.owner=int8_t(owner);
    a.unitClass=255; a.health=100; a.strength=111; a.territory.raw=origin; a.dest.raw=a.origin.raw=current;
    auto& t=d.territories[current-1].data; auto& head=owner==t.owner?t.armies:t.foreignArmies;
    a.next.raw=head.raw; if (head.raw) army(d,head.raw).prev.raw=a.id;
    head.raw=a.id; d.armies.push_back(a); return a.id;
}
std::vector<uint8_t> bytes(const save::Document& d) {
    std::vector<uint8_t> out; save::Error e; ok(save::encode(d,out,e),e);
    for (const auto& t:d.territories) {
        const auto* p=reinterpret_cast<const uint8_t*>(&t.data);
        out.insert(out.end(),p+kTerritorySavedBytes,p+sizeof(Territory));
    }
    return out;
}
MovementCrossingsContext context() {
    MovementCrossingsContext c; c.ai.rng.initialized=true; c.ai.negotiation.emplace(); c.log.emplace();
    c.log->slotPayloads[0]={123456,-98765}; c.campaign.emplace();
    c.campaign->campaignFlags=0xabcdef; c.campaign->campaignProgress={12345,-54321,777};
    c.campaign->pendingShrines.entries={{0,1}}; return c;
}
struct Outcome {
    std::unique_ptr<save::Document> document=std::make_unique<save::Document>();
    MovementCrossingsReport report;
};
Outcome run(const save::Document& d,const MovementCrossingsContext& c=context()) {
    AiSession ai; save::Error e; ok(ai.initializeAfterLoad(d,e),e); Outcome out;
    const auto source=bytes(d); e={save::ErrorCode::Io,77,"previous"};
    ok(resolveMovementCrossings(d,ai,c,*out.document,out.report,e),e);
    require(e.code==save::ErrorCode::None && bytes(d)==source,"crossing changed source or retained old error"); return out;
}
ArmyPowerReport power(const save::Document& d,uint32_t id,std::array<int32_t,4> flags={}) {
    ArmyPowerReport r; save::Error e; ok(scoreArmyPower(d,{id,flags},r,e),e); return r;
}
void scoring() {
    auto d=fixture(); const auto id=unit(*d,1,0,1,1);
    require(power(*d,id)==ArmyPowerReport{5,5,50,2,5,500,100},"Laser power differs from derived literal oracle");
    require(power(*d,id,{1,1,0,0}).score==260 && power(*d,id,{0,1,0,0}).accuracy==65 &&
            power(*d,id,{0,0,0,1})==power(*d,id),"power flags differ or impossible naval branch was corrected");
    army(*d,id).unk_2c=-1;
    require(power(*d,id).remainingDefense==6 && power(*d,id).score==120,"Army+2c was not read as signed16");
    army(*d,id).unk_2c=6;
    require(power(*d,id).remainingDefense==-1 && power(*d,id).score==-20,"negative remaining defense was clamped");
    army(*d,id).unk_2c=0; d->raceStats.v[45][0]=-100;
    require(power(*d,id).score==-100 && power(*d,id,{0,1,0,0}).score==-70,"negative accuracy/post-bonus sign changed");
    d->raceStats.v[45][0]=100;
    require(power(*d,id,{0,1,0,0}).accuracy==115,"accuracy bonus was incorrectly capped after100");
    d->raceStats.v[45][0]=0; army(*d,id).type=19;
    require(power(*d,id,{1,1,1,1}).score==625,"fortress incorrectly received infantry/air bonuses");
    d->techs[19].knownMask=1; d->techs[23].knownMask=1;
    require(power(*d,id,{1,1,1,1})==ArmyPowerReport{25,50,65,4,8,13000,1625},"fortress tech19/23 or modifier order differs");
    army(*d,id).type=16;
    require(power(*d,id,{0,0,1,0}).score==400 && power(*d,id).rateOfFire==-1,
            "missile rate floor/class9 division or air exclusion differs");
    army(*d,id).type=23; require(power(*d,id,{1,0,0,0}).score==40,"militia received first-flag double defense");
    army(*d,id).type=25; require(power(*d,id,{1,0,0,0}).score==40,"class8 colonizer received first-flag double defense");
    army(*d,id).type=1; d->raceStats.v[29][0]=32767; d->raceStats.v[30][0]=32767; d->raceStats.v[45][0]=100;
    const auto overflow=power(*d,id); const auto low=uint32_t((uint64_t(6555)*16388*100)&0xffffffffu);
    require(overflow.product==std::bit_cast<int32_t>(low) && overflow.score==std::bit_cast<int32_t>(low)/5 && overflow.score<0,
            "power multiplication did not discard high32 bits before signed division");
    ArmyPowerReport old=overflow; save::Error e; d->players[0].race=-1;
    require(!scoreArmyPower(*d,{id,{}},old,e) && old==overflow,"late stat error changed score output");
}
void tiesEventsAndAtomicity() {
    auto d=fixture(); const auto left=unit(*d,1,1,1,2),right=unit(*d,1,0,2,1);
    auto c=context(); c.movement.paths.creation.movingArmyId=left;
    auto out=run(*d,c);
    require(out.report.groups[1][0]==MovementCrossingGroup{2,1,100,1} &&
            out.report.groups[2][0]==MovementCrossingGroup{1,0,100,1} &&
            out.report.crossings.size()==1,"crossing snapshot or pair enumeration differs");
    const auto& x=out.report.crossings[0];
    require(x.loser==0 && x.winner==1 && x.from==2 && x.retreatTo==1 && x.productA==100 && x.productB==100 &&
            x.moves.size()==1 && x.moves[0].request==UnitMovementRequest{right,1,0} && x.moves[0].moved &&
            army::current(*out.document->armyById(right))==1 && army::turnStart(*out.document->armyById(right))==1 &&
            army::current(*out.document->armyById(left))==1 && out.report.contextAfter.movement.paths.creation.movingArmyId==left,
            "tie did not withdraw A-to-B flow or implicit moving context changed");
    const auto& log=*out.report.contextAfter.log;
    require(x.event.route==MovementCrossingEventRoute::LocalLog && x.event.local && x.event.local->stored && log.entries.size()==1 &&
            log.entries[0].type==152 && log.entries[0].player==123456 && log.entries[0].param==-98765 &&
            std::string(log.entries[0].text.begin(),log.entries[0].text.end())==
              "Our forces attacking Territory2 encountered Cyth forces on their way to Territory1 and were forces to retreat!" &&
            out.report.draws.size()==1 && out.report.draws[0].tag=="LogEventPortrait" && out.report.draws[0].value==0 &&
            out.report.contextAfter.ai.rng.counters.secondary15==1 && out.document->events.empty() &&
            out.report.contextAfter.campaign==c.campaign,"event152 payload/name/RNG/campaign behavior differs");
    AiSession ai; save::Error e; ok(ai.initializeAfterLoad(*d,e),e);
    const auto source=bytes(*d),kept=bytes(*out.document); const auto saved=out.report;
    c.log.reset();
    require(!resolveMovementCrossings(*d,ai,c,*out.document,out.report,e) && out.report==saved && bytes(*out.document)==kept &&
            bytes(*d)==source,"missing late event log leaked completed withdrawal");
    c=context(); d->players[1].race=-1;
    require(!resolveMovementCrossings(*d,ai,c,*out.document,out.report,e) && out.report==saved && bytes(*out.document)==kept,
            "invalid winner race leaked crossing effects");
    d->players[1].race=1; auto alias=std::make_unique<save::Document>(*d); MovementCrossingsReport aliasReport;
    aliasReport.contextAfter=context(); aliasReport.contextAfter.movement.paths.creation.movingArmyId=left;
    ok(resolveMovementCrossings(*alias,ai,aliasReport.contextAfter,*alias,aliasReport,e),e);
    require(bytes(*alias)==kept && aliasReport==saved,"source/report aliases changed crossing result");
    // Give B more power: A's AI owner withdraws; logger passes extras0/0 and
    // original152 is a real default handler, with no fabricated RNG/chat.
    army(*d,right).type=3; auto aiOut=run(*d);
    require(aiOut.report.crossings[0].loser==1 && aiOut.report.crossings[0].moves[0].request.armyId==left &&
            aiOut.report.crossings[0].event.route==MovementCrossingEventRoute::AiReaction &&
            aiOut.report.crossings[0].event.reaction && !aiOut.report.crossings[0].event.reaction->handled &&
            aiOut.report.draws.empty() && aiOut.report.contextAfter.log->entries.empty(),"nonlocal152 invented effects or wrong side withdrew");
}
void masksFiltersAndFullGroups() {
    auto d=fixture(); unit(*d,1,1,1,2); const auto id=unit(*d,1,0,2,1);
    for (uint32_t mask:{2u,16u}) {
        d->players[1].relations[0]=mask; auto out=run(*d);
        require(out.report.crossings.empty() && out.report.draws.empty(),"military/alliance pact did not suppress crossing");
    }
    d->players[1].relations[0]=2; d->options.allowAlliances=0;
    require(run(*d).report.crossings.size()==1,"disabled alliances still suppressed raw military relation");
    d->options.allowAlliances=1; d->players[1].relations[0]=0;
    for (uint8_t mission:std::array<uint8_t,9>{1,2,3,4,5,6,15,16,19}) {
        army(*d,id).unk_25=mission; auto out=run(*d);
        require(out.report.contributions.size()==1 && out.report.crossings.empty(),"special mission participated in crossing");
    }
    army(*d,id).unk_25=0; army(*d,id).type=16;
    require(run(*d).report.contributions.size()==1,"canonical class9 was not filtered");
    army(*d,id).type=1; army(*d,id).territory.raw=2;
    require(run(*d).report.contributions.size()==1,"unmoved unit entered crossing group");
    d=fixture(13); d->territories[0].data.owner=1;
    for (size_t i=1;i<d->territories.size();++i) d->territories[i].data.numTiles=0;
    const auto ignored=unit(*d,1,6,1,12); d->players[6].race=-1;
    for (uint32_t origin=2;origin<=11;++origin) unit(*d,1,0,1,origin);
    auto full=run(*d);
    require(full.report.contributions.size()==11 && full.report.contributions.back().armyId==ignored &&
            full.report.contributions.back().group==-1 && !full.report.contributions.back().score && full.report.crossings.empty(),
            "eleventh group was added or its forbidden stats were evaluated");
    for (int i=0;i<10;++i) require(full.report.groups[1][size_t(i)].origin==11-i && full.report.groups[1][size_t(i)].count==1,
            "snapshot did not use native linked-list/first-empty order");
    unit(*d,1,6,2,3); // numTiles0 avoids the invalid race's score lookup entirely.
    require(run(*d).report.contributions.size()==11,"zero-tile territory was evaluated");
}
void wrapProductsAndBudget() {
    auto d=fixture(); unit(*d,1,1,1,2);
    for (int i=0;i<5;++i) unit(*d,1,0,2,1);
    d->raceStats.v[29][0]=10000; d->raceStats.v[30][0]=10000;
    auto out=run(*d); const auto& x=out.report.crossings[0];
    require(out.report.groups[2][0].power==501000500 && x.productB==std::bit_cast<int32_t>(uint32_t(100200100)*25u) &&
            x.productB<0 && x.loser==0 && x.moves.size()==5 && out.report.contextAfter.log->entries.size()==1,
            "signed wrapped score*count comparison or one-event-per-group behavior differs");
    AiSession ai; save::Error e; ok(ai.initializeAfterLoad(*d,e),e);
    auto c=context(); c.maximumTraversalSteps=1;
    const auto saved=out.report; const auto kept=bytes(*out.document),source=bytes(*d);
    require(!resolveMovementCrossings(*d,ai,c,*out.document,out.report,e) && e.code==save::ErrorCode::Limit &&
            out.report==saved && bytes(*out.document)==kept && bytes(*d)==source,"budget failure after first move leaked effects");
    require(!resolveMovementCrossings(*d,ai,c,*d,out.report,e) && bytes(*d)==source && out.report==saved,
            "budget failure leaked aliased source mutation");
}
void lastTerritoryRow() {
    auto d=fixture(); const auto lastTemplate=d->territories[1].data;
    d->world.numTerritories=111; d->territories.resize(111); d->territories[1].data.numTiles=0;
    for (size_t i=2;i<111;++i) d->territories[i].data.index=uint16_t(i+1);
    auto& last=d->territories[110].data; last=lastTemplate; last.index=111;
    std::memcpy(last.name,"Territory111",13); d->tiles[1].territory=111;
    unit(*d,1,1,1,111); const auto right=unit(*d,1,0,111,1); auto out=run(*d);
    require(out.report.groups[0]==std::array<MovementCrossingGroup,10>{} &&
            out.report.groups[1][0]==MovementCrossingGroup{111,1,100,1} &&
            out.report.groups[111][0]==MovementCrossingGroup{1,0,100,1} && out.report.crossings.size()==1 &&
            out.report.crossings[0].from==111 && out.report.crossings[0].retreatTo==1 &&
            army::current(*out.document->armyById(right))==1,"last physical group row111 was skipped or shifted into sentinel0");
}
void falseMoveStillLogsAndCapturedNext() {
    auto d=fixture(); unit(*d,13,1,1,2); const auto id=unit(*d,12,0,2,1);
    d->territories[1].data.terrain=0;
    // A ship's turn-start destination is owned land: withdrawal's native
    // refusal still changes scratch and produces an event after the loop.
    auto denied=run(*d);
    require(denied.report.crossings[0].moves.size()==1 && !denied.report.crossings[0].moves[0].moved &&
            denied.report.crossings[0].moves[0].reason==UnitMovementReason::CreationDenied &&
            army::current(*denied.document->armyById(id))==2 && denied.report.contextAfter.log->entries.size()==1,
            "native false MoveUnit suppressed crossing notification");
    d=fixture(); for (auto& t:d->territories) t.data.terrain=0;
    unit(*d,13,1,1,2); const auto tail=unit(*d,12,0,2,1);
    const auto passenger=unit(*d,1,0,2,1),carrier=unit(*d,12,0,2,1);
    army(*d,carrier).cargo[0].raw=passenger; army(*d,passenger).cargo[0].raw=carrier;
    auto transported=run(*d); const auto& crossing=transported.report.crossings[0];
    require(crossing.loser==0 && crossing.moves.size()==1 && crossing.moves[0].request.armyId==carrier &&
            army::current(*transported.document->armyById(carrier))==1 &&
            army::current(*transported.document->armyById(passenger))==1 &&
            army::current(*transported.document->armyById(tail))==2 && transported.report.traversalSteps==3,
            "captured-next traversal was replaced by a frozen list or rejected the carrier revisit");
}
void corpus(const std::filesystem::path& directory) {
    if (directory.empty() || !std::filesystem::is_regular_file(directory/"TUTORIAL.SAV")) {
        std::cout<<"Movement crossings: optional corpus unavailable\n"; return;
    }
    auto d=std::make_unique<save::Document>(); save::Error e;
    ok(save::readDocument(directory/"TUTORIAL.SAV",*d,e),e); const auto original=bytes(*d);
    size_t count=0;
    for (const auto& a:d->armies) { const auto r=power(*d,a.id); require(r.score==r.product/std::max(r.rateOfFire,1)/
            ((data::kUnitTypes[a.type].unitClass==9 || data::kUnitTypes[a.type].unitClass==20)?10:1),"corpus score divisions differ"); ++count; }
    // Archival saves can contain nonlocal humans. Apply the explicit offline
    // load profile to an owned copy before binding its AI personalities.
    auto normalized=std::make_unique<save::Document>(); LoadCoreReport loaded;
    ok(normalizeLoadCore(*d,{-1,"Crossings corpus"},*normalized,loaded,e),e);
    const auto normalizedBefore=bytes(*normalized);
    AiSession ai; ok(ai.initializeAfterLoad(*normalized,e),e); auto output=std::make_unique<save::Document>(); MovementCrossingsReport r;
    auto c=context(); ok(resolveMovementCrossings(*normalized,ai,c,*output,r,e),e);
    require(bytes(*d)==original && bytes(*normalized)==normalizedBefore,"corpus crossing changed read-only input");
    std::cout<<"Movement crossings corpus: "<<count<<" unit scores, "<<r.crossings.size()<<" crossings\n";
}
}
int main(int argc,char** argv) {
    try {
        rtl::srand(0xf1234567); (void)rtl::lrand(); gg.rng2Seed=0xabcdef01;
        const auto low=rtl::seed(),high=rtl::seedHi();
        const auto globals=std::make_unique<GameGlobals>(gg); const auto game=std::make_unique<GameState>(gs);
        scoring(); tiesEventsAndAtomicity(); masksFiltersAndFullGroups(); wrapProductsAndBudget(); lastTerritoryRow(); falseMoveStillLogsAndCapturedNext();
        corpus(argc>1?std::filesystem::path(argv[1]):std::filesystem::path{});
        require(rtl::seed()==low && rtl::seedHi()==high && std::memcmp(&gg,globals.get(),sizeof(gg))==0 &&
                std::memcmp(&gs,game.get(),sizeof(gs))==0,"crossings touched globals/RNG");
        std::cout<<"Movement crossings tests passed\n"; return 0;
    } catch (const std::exception& e) { std::cerr<<"Movement crossings: "<<e.what()<<'\n'; return 1; }
}
