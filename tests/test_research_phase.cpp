// Independent00484114/00483d58/0048514c oracles, not an EXE execution claim.
#include "game/research_phase.h"
#include "game/data_tables.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include "game/save_files.h"
#include "game/load_profile.h"
#include <algorithm>
#include <bit>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>

namespace {
using namespace dl2;
using namespace dl2::simulation;
namespace fs=std::filesystem;
void require(bool value,const char* message) { if (!value) throw std::runtime_error(message); }
void ok(bool value,const save::Error& e) { if (!value) throw std::runtime_error(e.message); }
std::unique_ptr<save::Document> fixture() {
    auto d=std::make_unique<save::Document>();
    std::memcpy(d->header.text,save::kHeaderText,sizeof(save::kHeaderText)); d->header.version=kSaveVersion;
    d->options.numPlayers=1; d->options.localPlayer=0; d->options.turn=19; d->options.nextGlobalId=1000;
    d->world.width=4; d->world.height=1; d->world.numTerritories=4; d->territories.resize(4); d->tiles.resize(4);
    for (int p=0;p<7;++p) {
        d->players[size_t(p)].index=uint8_t(p); d->players[size_t(p)].race=2; d->players[size_t(p)].type=p?0:1;
        d->ministerJobs[size_t(p)].resize(1); d->ministerJobs[size_t(p)][0].type=1;
        for (auto& job:d->jobs[size_t(p)]) job.owner=int16_t(p);
    }
    for (int i=0;i<4;++i) {
        auto& t=d->territories[size_t(i)].data; t.index=uint16_t(i+1); t.owner=0; t.terrain=1;
        t.population=500; t.numTiles=1; t.tiles[0].raw=uint32_t(i); std::memcpy(t.name,"Alpha",6);
        for (int s=0;s<36;++s) { t.sites[s].unk_00=uint16_t(s%6+256*(s/6)); t.sites[s].terrainFlags=1; }
        d->tiles[size_t(i)].x=uint8_t(i); d->tiles[size_t(i)].territory=int16_t(i+1);
    }
    d->trailing={0,255,128}; return d;
}
ConstructionOrderContext context() {
    ConstructionOrderContext c; SessionRng rng; save::Error e; ok(rng.initialize(1,e),e);
    c.events.rngBeforeEvents=c.ai.rng=c.log.rngAfterEvents=rng.snapshot();
    c.log.slotPayloads[0]={71,93}; c.log.slotPayloads[1]={72,94}; return c;
}
std::vector<uint8_t> bytes(const save::Document& d) {
    std::vector<uint8_t> out; save::Error e; ok(save::encode(d,out,e),e);
    for (const auto& t:d.territories) { const auto* p=reinterpret_cast<const uint8_t*>(&t.data);
        out.insert(out.end(),p+kTerritorySavedBytes,p+sizeof(Territory)); }
    return out;
}
int32_t word(const Territory& t,size_t offset) { int32_t out; std::memcpy(&out,reinterpret_cast<const uint8_t*>(&t)+offset,4); return out; }
void word(Territory& t,size_t offset,int32_t value) { std::memcpy(reinterpret_cast<uint8_t*>(&t)+offset,&value,4); }
int32_t attitude(const Job& block,int p,int other) {
    int32_t out; std::memcpy(&out,reinterpret_cast<const uint8_t*>(&block)+size_t(p*7+other)*4,4); return out;
}
void attitude(Job& block,int p,int other,int32_t value) {
    std::memcpy(reinterpret_cast<uint8_t*>(&block)+size_t(p*7+other)*4,&value,4);
}
struct Outcome { std::unique_ptr<save::Document> d=std::make_unique<save::Document>(); ResearchReport r; };
Outcome run(const save::Document& d,ConstructionOrderContext c=context(),int player=-1,int technology=0) {
    const auto before=bytes(d); const auto priorLog=c.log; const auto priorAi=c.ai;
    Outcome out; save::Error e{save::ErrorCode::Io,9,"old"};
    auto call=[&](const save::Document& source,save::Document& dest,ResearchReport& report) {
        return player<0?processResearch(source,c,dest,report,e):acquireTechnology(source,player,technology,c,dest,report,e);
    };
    ok(call(d,*out.d,out.r),e);
    require(bytes(d)==before && c.log==priorLog && c.ai==priorAi && e.code==save::ErrorCode::None && !e.offset && e.message.empty(),
            "research preserves source/context and clears error");
    auto alias=std::make_unique<save::Document>(d); ResearchReport repeated;
    ok(call(*alias,*alias,repeated),e);
    require(bytes(*alias)==bytes(*out.d) && repeated==out.r,"research source/destination alias differs"); return out;
}
void steal() {
    auto d=fixture(); auto c=context(); save::Error e{save::ErrorCode::Io,1,"old"}; StealableTechnologyReport r;
    d->techs[9].knownMask=2; d->techs[12].knownMask=2; d->techs[10].knownMask=3;
    const auto source=bytes(*d);
    ok(chooseStealableTechnology(*d,0,1,c.ai.rng,r,e),e);
    require(r.technology==12 && r.draw.value==10 && r.draw.tag=="Steal Tech" && r.draw.operation==RngOperation::TaggedRange &&
            r.draw.bound==48 && r.draw.consumed && r.rngAfter.rtlLow==0x4e36 && r.rngAfter.rtlHigh==346 &&
            r.rngAfter.secondary==1 && r.rngAfter.counters.long31==1 && r.rngAfter.counters.taggedRange==1 &&
            bytes(*d)==source && e.code==save::ErrorCode::None,"steal scan must start at golden346%48=10 and consume one long draw");
    d->techs[12].knownMask=0; ok(chooseStealableTechnology(*d,0,1,c.ai.rng,r,e),e);
    require(r.technology==9,"steal scan must wrap from47 to0");
    d->techs[9].knownMask=0; d->techs[0].knownMask=2;
    ok(chooseStealableTechnology(*d,0,1,c.ai.rng,r,e),e); require(r.technology==0 && r.draw.consumed,"technology0 is eligible, not excluded");
    d->techs[0].knownMask=0; ok(chooseStealableTechnology(*d,0,1,c.ai.rng,r,e),e);
    require(r.technology==0 && r.rngAfter.counters.operations==1,"empty steal still consumes draw");
    d->techs[15].knownMask=0x8000; ok(chooseStealableTechnology(*d,32,255,c.ai.rng,r,e),e);
    require(r.technology==15,"steal sign-extends known WORD and masks original byte player shifts");
    const auto old=r; require(!chooseStealableTechnology(*d,-1,1,c.ai.rng,r,e) && r==old,"invalid steal player changes output");
    auto bad=c.ai.rng; bad.format=99;
    require(!chooseStealableTechnology(*d,0,1,bad,r,e) && r==old,"bad steal snapshot changes output");
}
void progressAndDiscovery() {
    auto d=fixture(); d->players[0].currentResearch=1; d->players[0].lastIncome=12; d->techs[1].progress[0]=37;
    auto incomplete=run(*d);
    require(incomplete.d->techs[1].progress[0]==49 && incomplete.r.acquisitions.empty() && incomplete.r.events.empty() &&
            incomplete.r.players[0].required==50 && !incomplete.r.players[0].thresholdReached,"partial50-point research");
    d->players[0].lastIncome=13;
    auto completed=run(*d);
    require(completed.d->techs[1].progress[0]==50 && completed.d->techs[1].knownMask==1 &&
            completed.d->players[0].currentResearch==1 && completed.r.events.size()==2 &&
            completed.r.events[0].type==54 && completed.r.events[1].type==57 && completed.r.players[0].thresholdReached,
            "discovery logs54 then empty-queue57, retains progress AND currentResearch");
    const auto& log=completed.r.logAfter.entries;
    require(log.size()==2 && log[0].player==1 && log[0].param==0 && log[1].player==72 && log[1].param==94 &&
            std::string(log[0].text.begin(),log[0].text.end())==
            "Advanced Medicine technology has been thoroughly researched!  This technology is yours to use.  Congratulations, colony leader!",
            "discovery uses Ex technology payload and canonical name; ordinary57 preserves inactive-slot payload");
    require(completed.r.rngAfter.counters.secondary15==2 && completed.r.rngAfter.secondary==2524885223u &&
            log[0].portraitResource=="HHTECHC" && log[1].portraitResource=="HHTECHE" && completed.r.rngAfter.rtlLow==1,
            "discovery and empty-queue portraits consume ordered golden secondary draws16838/5758");
    d->techs[1].knownMask=1; auto known=run(*d);
    require(known.r.events.empty() && known.r.acquisitions.size()==1 && !known.r.acquisitions[0].newlyKnown,
            "known completed research does not rediscover or clear progress");
    d=fixture(); d->players[0].currentResearch=1; d->players[0].lastIncome=1; d->techs[1].progress[0]=32767;
    auto wrapped=run(*d); require(wrapped.r.players[0].progressAfter==-32768 && wrapped.r.events.empty(),"progress wraps signed16 before threshold compare");
    d->techs[1].progress[0]=0; d->players[0].lastIncome=-1; wrapped=run(*d);
    require(wrapped.r.players[0].progressAfter==-1,"negative research budget is not clamped");
    d=fixture(); d->players[0].index=1; d->players[0].type=0; d->players[0].currentResearch=2; d->players[0].lastIncome=50;
    auto indexed=run(*d);
    require(indexed.d->techs[2].progress[0]==0 && indexed.d->techs[2].progress[1]==50 && indexed.d->techs[2].knownMask==2 &&
            indexed.r.events.size()==1 && indexed.r.events[0].recipient==1,"research addresses signed Player.index, not physical slot");
    d=fixture(); auto none=run(*d); require(none.r.players.size()==1 && !none.r.players[0].thresholdReached && bytes(*none.d)==bytes(*d),"zero budget/tech0 is evaluated without threshold work");
    d->players[0].lastIncome=25; d->techs[4].knownMask=1; auto nothing=run(*d);
    require(nothing.d->techs[0].progress[0]==25 && nothing.r.acquisitions.empty() && nothing.r.excess.size()==4 &&
            nothing.d->territories[0].data.materials[8]==1,"tech0 progress/overflow are real even without acquiring technology0");
}
void queuesAndAvailability() {
    auto d=fixture(); d->players[0].currentResearch=1; d->localList={1,5,46};
    auto out=run(*d,context(),0,1);
    require(out.d->localList==std::vector<uint32_t>{5} && out.d->players[0].currentResearch==5 && out.r.events.empty() &&
            out.r.acquisitions[0].removedFromLocalQueue==std::vector<uint32_t>({1,46}) && (out.d->techs[5].availableMask&1),
            "local queue pruned and selected before availability recomputation");
    d=fixture(); d->localList={1,2,2,7};
    out=run(*d,context(),0,1);
    require(out.d->localList==std::vector<uint32_t>({2,2,7}),"queue counts duplicate dependencies: two Metallurgy entries match Fusion Cannon's two missing prerequisites");
    d->localList={1,0,5}; out=run(*d,context(),0,1);
    require(out.d->localList==std::vector<uint32_t>{5} && out.r.acquisitions[0].removedFromLocalQueue==std::vector<uint32_t>({1,0}),
            "zero prerequisites match queued0 four times, removing0; then acquired prereq with no queued match allows5");
    // With0 available its short circuit preserves it. Three zero prerequisite
    // matches make5 ineligible even though its actual prerequisite1 is known.
    d->techs[0].availableMask=1; out=run(*d,context(),0,1);
    require(out.d->localList==std::vector<uint32_t>{0} && out.d->players[0].currentResearch==0,
            "available short-circuit and literal zero-prerequisite queue matches are preserved");
    d=fixture(); d->localList={1,1,5}; out=run(*d,context(),0,1);
    require(out.d->localList==std::vector<uint32_t>{5} && out.r.acquisitions[0].removedFromLocalQueue==std::vector<uint32_t>({1,1}),
            "acquisition removes first duplicate then pruning removes remaining known duplicate");
    d=fixture(); out=run(*d,context(),1,2);
    require((out.d->techs[7].availableMask&2)==0 && (out.d->techs[8].availableMask&2)!=0 &&
            (out.d->techs[1].availableMask&2)!=0,"ordinary availability requires ALL prerequisites or none");
    d->raceStats.v[55][2]=-1; out=run(*d,context(),1,2);
    require((out.d->techs[7].availableMask&2)!=0 && (out.d->techs[14].availableMask&2)==0,
            "racial nonzero bonus grants any-known prerequisite, not every technology");
    d=fixture(); d->players[6].race=-1; d->raceStats.v[54][6]=1;
    out=run(*d,context(),6,2); require((out.d->techs[7].availableMask&64)!=0,"research accepts signed-race neighbor inside owned saved RaceStats");
    d=fixture(); for (int i=1;i<46;++i) d->techs[size_t(i)].knownMask=2;
    out=run(*d,context(),1,46); require((out.d->techs[47].availableMask&2)!=0,"Time Dilation requires all46 normal technologies");
    auto campaign=context(); campaign.researchCampaignFlags=16;
    d->options.campaign=6; out=run(*d,campaign,1,46);
    require((out.d->techs[47].availableMask&2)==0,"campaign6 blocks Time Dilation for matching race");
    out=run(*d,context(),1,46);
    require((out.d->techs[47].availableMask&2)!=0,"explicit flag4 disabled permits Time Dilation even in campaign6");
    d=fixture(); d->options.campaign=15; out=run(*d,campaign,1,1);
    require((out.d->techs[2].availableMask&2)==0 && (out.d->techs[3].availableMask&2)!=0,"campaign15 payload race2 blocks technology2, not an invented list interpretation");
    out=run(*d,context(),1,1); require((out.d->techs[2].availableMask&2)!=0,"explicit flag4 disabled permits campaign15's restricted technology");
    out=run(*d,campaign,1,2); require((out.d->techs[2].knownMask&2)!=0,"campaign gate controls availability, not explicit AcquireTech");
    d->localList={1,2}; out=run(*d,campaign,0,1); require(out.d->localList.empty(),"live flag4 also controls research queue pruning");
    out=run(*d,context(),0,1); require(out.d->localList==std::vector<uint32_t>{2},"disabled flag4 permits queue entry without deriving campaign state");
    d=fixture(); out=run(*d,context(),1,0);
    require(out.d->techs[0].knownMask==2 && out.r.acquisitions[0].newlyKnown,"AcquireTech0 performs real mask and availability updates");
    auto again=run(*out.d,context(),1,0); require(bytes(*again.d)==bytes(*out.d) && !again.r.acquisitions[0].newlyKnown,"known AcquireTech0 authentic early return");
}
void shrinesAndExcess() {
    auto d=fixture(); Building b{}; b.id=60; b.type=46; b.category=11; b.territory=2; b.site=7; b.turnsLeft=99;
    d->buildings.push_back(b); d->territories[1].data.owner=-1; d->territories[1].data.sites[7].building.raw=60;
    for (auto& t:d->territories) { word(t.data,0x8b0,0x40); word(t.data,0x978+4,99); word(t.data,0x978+8,77); }
    auto revealed=run(*d,context(),1,33);
    require(revealed.r.acquisitions[0].revealedShrines==std::vector<uint32_t>{2} && word(revealed.d->territories[1].data,0x8b0)==0x42 &&
            word(revealed.d->territories[1].data,0x978+4)==1 && word(revealed.d->territories[0].data,0x978+4)==0 &&
            word(revealed.d->territories[0].data,0x8b0)==0x40 && word(revealed.d->territories[1].data,0x978+8)==77,
            "Native Languages reveals unowned/unfinished/inactive shrine category and clears only absent per-player markers");
    d=fixture(); d->players[0].currentResearch=1; d->players[0].lastIncome=77; d->techs[1].knownMask=d->techs[4].knownMask=1;
    d->territories[1].data.population=-1; d->territories[2].data.population=0; d->territories[3].data.numTiles=0;
    d->territories[0].data.materials[8]=std::numeric_limits<int32_t>::max();
    auto excess=run(*d);
    require(excess.r.excess.size()==2 && excess.r.excess[0].amount==2 && excess.r.excess[1].amount==2 &&
            excess.d->territories[0].data.materials[8]==-2147483647 && excess.d->territories[1].data.materials[8]==2 &&
            excess.d->territories[2].data.materials[8]==0 && excess.d->territories[3].data.materials[8]==0,
            "excess (77-50)/5/2 discards remainders, counts negative population, wraps stocks and excludes no-tile/zero-pop");
    for (auto& t:d->territories) t.data.population=0;
    auto empty=run(*d); require(empty.r.excess.empty(),"no eligible territory does not divide by zero");
}
void sharingAndAttitudes() {
    auto d=fixture(); d->options.numPlayers=3; d->options.allowAlliances=1;
    d->players[0].type=3; d->players[1].type=3; d->players[2].type=3; d->players[6].type=1; d->options.localPlayer=6;
    d->players[0].currentResearch=1; d->players[0].lastIncome=50;
    d->players[0].relations[1]=8; d->players[0].relations[2]=16;
    AiSession ai; save::Error e; ok(ai.initializeAfterLoad(*d,e),e); auto c=context(); c.aiSession=&ai;
    auto out=run(*d,c);
    require(out.d->techs[1].knownMask==7 && out.r.events.size()==3 && out.r.events[0].type==54 &&
            out.r.events[1].type==56 && out.r.events[1].recipient==1 && out.r.events[2].recipient==2 &&
            out.r.acquisitions[0].player==1 && out.r.acquisitions[1].player==2 && out.r.acquisitions[2].player==0,
            "research shares in ascending recipient order, full pact16 implies8, researcher acquires LAST");
    // seed1 secondary values16838(even),5758(chat),10113(odd): receiver1
    // gratitude applies+4/+2; receiver2 skips. Researcher gets-4/-2 for each.
    require(out.r.rngAfter.counters.secondary15==3 && out.r.rngAfter.secondary==662824084u &&
            out.r.rngAfter.rtlLow==1 && out.r.rngAfter.counters.long31==0 &&
            attitude(out.d->scratchJob1,1,0)==4 && attitude(out.d->scratchJob2,1,0)==2 &&
            attitude(out.d->scratchJob1,2,0)==0 && attitude(out.d->scratchJob1,0,1)==-4 && attitude(out.d->scratchJob2,0,2)==-2 &&
            out.r.aiAfter.relationChangeMask[0]==6 && out.r.aiAfter.relationChangeMask[1]==1 && out.r.attitudes.size()==2,
            "sharing consumes real AI gratitude/chat draws and asymmetric original attitude effects");
    c.ai.relationChangeMask[0]=2; d->options.playerSkill[1]=4; auto blocked=run(*d,c);
    require(!blocked.r.attitudes[0].applied && blocked.r.attitudes[1].applied && attitude(blocked.d->scratchJob1,1,0)==0,
            "explicit prior mask and playerSkill4 suppress attitude independently without suppressing AI draws");
    d->options.allowAlliances=0; auto noPacts=run(*d,c);
    require(noPacts.d->techs[1].knownMask==1 && noPacts.r.events.size()==1 && noPacts.r.rngAfter==c.ai.rng,"disabled alliances do not share or draw");
    // Direct helper has no personality callback: preserves the arithmetic even
    // when Player.index aliases another (including human) physical player.
    d=fixture(); attitude(d->scratchJob1,0,1,-49); attitude(d->scratchJob2,0,1,49); AiReactionReport report;
    ok(changeAiAttitude(*d,{0,1,-3},context().ai,*d,report,e),e);
    require(attitude(d->scratchJob1,0,1)==-50 && attitude(d->scratchJob2,0,1)==48 && report.draws.empty() &&
            report.contextAfter.rng==context().ai.rng,"shared attitude leaf clamps and divides negative odd delta toward zero without RNG");
    d=fixture(); d->options.numPlayers=2; d->options.allowAlliances=1; d->players[0].index=1;
    d->players[0].type=3; d->players[0].currentResearch=1; d->players[0].lastIncome=50; d->players[1].relations[0]=8;
    d->techs[0].availableMask=1; d->localList={1,0};
    auto live=run(*d);
    require(live.d->techs[1].knownMask==1 && live.d->techs[1].progress[1]==50 && live.d->players[0].currentResearch==0 &&
            live.r.acquisitions.size()==1 && live.r.acquisitions[0].player==0 && attitude(live.d->scratchJob1,1,0)==-4,
            "ally acquisition changing physical Player* selection suppresses final own acquisition; original tech pointer/index stay distinct");
}
void failures() {
    auto d=fixture(), destination=fixture(); destination->options.turn=99;
    const auto prior=bytes(*destination); ResearchReport report; report.excess.push_back({6,1,2,3,4}); const auto old=report; save::Error e;
    d->players[0].currentResearch=48;
    require(!processResearch(*d,context(),*destination,report,e) && report==old && bytes(*destination)==prior,"bad selected technology is transactional");
    d->players[0].currentResearch=0; d->players[0].index=255;
    require(!processResearch(*d,context(),*destination,report,e) && report==old && bytes(*destination)==prior,"signed progress index outside array is rejected");
    d=fixture(); d->localList={1,999}; const auto invalid=bytes(*d);
    require(!acquireTechnology(*d,0,1,context(),*d,report,e) && bytes(*d)==invalid && report==old,"late queue failure restores known bit and in-place document");
    d=fixture(); d->players[6].race=127; const auto unsafe=bytes(*d);
    require(!acquireTechnology(*d,0,1,context(),*d,report,e) && bytes(*d)==unsafe && report==old,
            "unsafe inactive race after local57 rolls back log, markers, availability and RNG");
    d=fixture(); d->options.numPlayers=2; d->options.allowAlliances=1; d->players[0].currentResearch=1;
    d->players[0].lastIncome=50; d->players[0].relations[1]=8; d->players[1].type=3; const auto source=bytes(*d);
    require(!processResearch(*d,context(),*destination,report,e) && bytes(*d)==source && bytes(*destination)==prior && report==old,
            "late missing AI after local discovery is atomic");
    auto bad=context(); bad.ai.rng.secondary=2;
    require(!acquireTechnology(*d,1,0,bad,*destination,report,e) && bytes(*destination)==prior && report==old,"mismatched initial event/AI stream is rejected");
    d=fixture(); d->options.campaign=43; auto campaign=context(); campaign.researchCampaignFlags=16;
    require(!acquireTechnology(*d,1,0,campaign,*destination,report,e) && bytes(*destination)==prior && report==old,"enabled campaign table address rejected transactionally");
    require(!acquireTechnology(*d,7,1,context(),*destination,report,e) && report==old,"acquire player outside owned arrays rejected");
    d->options.campaign=1;
    require(!acquireTechnology(*d,1,0,campaign,*destination,report,e) && bytes(*destination)==prior && report==old,
            "explicit flag4 without a type4 goal rejects native out-of-object lookup");
    d->options.campaign=43; auto skipped=run(*d,context(),1,0);
    require(skipped.d->techs[0].knownMask==2,"disabled flag4 short circuits before touching an invalid campaign selector");
}

// Minimal read-only PE reader, equivalent checked mapping to table-contracts.
class OriginalPe {
    std::vector<uint8_t> data_; uint32_t base_=0; size_t sections_=0; uint16_t count_=0;
    uint8_t byte(size_t at) const { require(at<data_.size(),"truncated original PE"); return data_[at]; }
    uint16_t half(size_t at) const { return uint16_t(byte(at)|uint16_t(byte(at+1))<<8); }
    uint32_t full(size_t at) const { return uint32_t(half(at))|uint32_t(half(at+2))<<16; }
    size_t offset(uint32_t address) const {
        require(address>=base_,"original PE address below image"); const auto rva=address-base_;
        for (size_t i=0;i<count_;++i) { const auto at=sections_+i*40; const auto start=full(at+12);
            if (rva>=start && rva-start<full(at+16)) return size_t(full(at+20))+rva-start; }
        throw std::runtime_error("original PE research table unmapped");
    }
public:
    explicit OriginalPe(const fs::path& path) {
        const auto size=fs::file_size(path); require(size>=64 && size<=16*1024*1024,"invalid original PE size"); data_.resize(size_t(size));
        std::ifstream in(path,std::ios::binary); require(bool(in.read(reinterpret_cast<char*>(data_.data()),std::streamsize(data_.size()))),"cannot read PE");
        const size_t pe=full(0x3c); require(half(0)==0x5a4d && full(pe)==0x4550 && half(pe+24)==0x10b,"not original PE32");
        base_=full(pe+52); count_=half(pe+6); sections_=pe+24+half(pe+20);
        require(count_>0 && count_<100 && sections_<=data_.size() && size_t(count_)*40<=data_.size()-sections_,"invalid PE sections");
    }
    uint16_t at(uint32_t address) const { return half(offset(address)); }
};
void pe(const fs::path& directory) {
    if (directory.empty() || !fs::is_regular_file(directory/"DEADLOCK.EXE")) return;
    OriginalPe exe(directory/"DEADLOCK.EXE");
    for (uint32_t i=0;i<48;++i) { const uint32_t address=0x4fbbac+i*0x32;
        require(exe.at(address+0x20)==data::kTechs[i].level && exe.at(address+0x22)==data::kTechs[i].cost,"research cost/level differs from original PE");
        for (uint32_t j=0;j<3;++j) require(exe.at(address+0x24+j*2)==data::kTechs[i].prereq[j],"research prerequisite differs from original PE");
        require(exe.at(address+0x2a)==0,"original fourth prerequisite is NOT zero; owned projection must be extended");
    }
    std::cout<<"research: all48 canonical costs/levels/four prerequisites verified against PE\n";
}
void corpus(const fs::path& directory) {
    if (directory.empty() || !fs::is_regular_file(directory/"TUTORIAL.SAV")) return;
    size_t count=0;
    auto one=[&](const save::Document& source) {
        const auto archival=bytes(source); auto d=std::make_unique<save::Document>(); save::Error e; LoadCoreReport loaded;
        ok(normalizeLoadCore(source,{-1,"Corpus"},*d,loaded,e),e);
        AiSession ai; ok(ai.initializeAfterLoad(*d,e),e); auto c=context(); c.aiSession=&ai;
        // Explicit post-LoadOptions0044fd14 context, not a mask guessed by the
        // research API from the document or global process state.
        c.researchCampaignFlags=loaded.campaignGoalMask;
        auto out=run(*d,c);
        require(out.r.players.size()==size_t(d->options.numPlayers) && bytes(source)==archival,"corpus research preserves archival source");
        StealableTechnologyReport stealReport; ok(chooseStealableTechnology(*d,0,1,c.ai.rng,stealReport,e),e); ++count;
    };
    for (const char* name:{"TUTORIAL.SAV","Saves/AUTOSAVE.SAV","Campaign/AUTOSAVE.CPN","Campaign/ChCht001.CPN"})
        if (fs::is_regular_file(directory/name)) { auto d=std::make_unique<save::Document>(); save::Error e; ok(save::readDocument(directory/name,*d,e),e); one(*d); }
    std::ifstream index(directory/"LEVELS.HDX",std::ios::binary);
    if (index) { uint32_t total=0; require(bool(index.read(reinterpret_cast<char*>(&total),4)) && total<=4096,"invalid corpus index");
        for (uint32_t i=0;i<total;++i) { char entry[12]{}; require(bool(index.read(entry,12)),"truncated corpus index");
            auto d=std::make_unique<save::Document>(); save::Error e; const std::string name(entry,std::find(entry,entry+8,'\0'));
            ok(save::readScenario(directory/"LEVELS",name,*d,e),e); one(*d); }
    }
    std::cout<<"research: "<<count<<" core-normalized corpus variants\n";
}
} // namespace
int main(int argc,char** argv) {
    try {
        rtl::srand(0x12345678); (void)rtl::lrand(); gg.rng2Seed=0xabcdef01;
        const auto low=rtl::seed(),high=rtl::seedHi(); const auto globals=std::make_unique<GameGlobals>(gg); const auto game=std::make_unique<GameState>(gs);
        steal(); progressAndDiscovery(); queuesAndAvailability(); shrinesAndExcess(); sharingAndAttitudes(); failures();
        const fs::path directory=argc>1?fs::path(argv[1]):fs::path{}; pe(directory); corpus(directory);
        require(rtl::seed()==low && rtl::seedHi()==high && std::memcmp(globals.get(),&gg,sizeof(gg))==0 && std::memcmp(game.get(),&gs,sizeof(gs))==0,
                "research changed legacy globals/RNG");
        std::cout<<"research tests passed\n"; return 0;
    } catch (const std::exception& e) { std::cerr<<"research: "<<e.what()<<'\n'; return 1; }
}
