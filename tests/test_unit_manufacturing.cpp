// Independent0044df94/0044e0a8/0044e174 oracles, not a live original replay.
#include "game/unit_manufacturing.h"
#include "game/data_tables.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include "game/save_files.h"
#include <algorithm>
#include <bit>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
using namespace dl2;
using namespace dl2::simulation;
namespace fs=std::filesystem;
void require(bool value,const char* message) { if (!value) throw std::runtime_error(message); }
void ok(bool value,const save::Error& e) { if (!value) throw std::runtime_error(e.message); }
std::unique_ptr<save::Document> fixture() {
    auto d=std::make_unique<save::Document>();
    std::memcpy(d->header.text,save::kHeaderText,sizeof(save::kHeaderText)); d->header.version=kSaveVersion;
    d->options.numPlayers=2; d->options.localPlayer=0; d->options.turn=19; d->options.nextGlobalId=1000;
    d->world.width=2; d->world.height=1; d->world.numTerritories=2;
    d->territories.resize(2); d->tiles.resize(2);
    for (size_t p=0;p<7;++p) {
        d->players[p].index=uint8_t(p); d->players[p].race=2; d->players[p].type=p==0?1:3;
        d->players[p].credits=10000; d->ministerJobs[p].resize(1); d->ministerJobs[p][0].type=1;
        for (auto& row:d->raceStats.v) row[p]=100;
    }
    for (auto& tech:d->techs) tech.knownMask=0x7f;
    for (size_t i=0;i<2;++i) {
        auto& t=d->territories[i].data; t.index=uint16_t(i+1); t.owner=0; t.terrain=i?0:1;
        t.numTiles=1; t.tiles[0].raw=uint32_t(i); t.population=500; t.morale=100; t.portTarget=2;
        std::memcpy(t.name,"Alpha",6);
        for (int m=1;m<11;++m) t.materials[m]=1000;
        for (int s=0;s<36;++s) { t.sites[s].unk_00=uint16_t(s%6+256*(s/6)); t.sites[s].terrainFlags=1; }
        d->tiles[i].x=uint8_t(i); d->tiles[i].territory=int16_t(i+1);
    }
    d->trailing={0,255,128}; return d;
}
std::vector<uint8_t> bytes(const save::Document& d) {
    std::vector<uint8_t> result; save::Error e; ok(save::encode(d,result,e),e);
    for (const auto& r:d.territories) {
        const auto* start=reinterpret_cast<const uint8_t*>(&r.data);
        result.insert(result.end(),start+kTerritorySavedBytes,start+sizeof(Territory));
    }
    return result;
}
UnitManufacturingContext context(uint32_t seed=54) {
    UnitManufacturingContext c; c.effects.payment.selectedTerritory=1;
    SessionRng rng; save::Error e; ok(rng.initialize(seed,e),e);
    c.effects.events.rngBeforeEvents=c.effects.ai.rng=c.effects.log.rngAfterEvents=rng.snapshot();
    c.effects.log.slotPayloads[0]={71,93}; return c;
}
void paidHead(save::Document& d,int type,int queue,int16_t remaining) {
    QueueRecord row{}; row.unitType=uint8_t(type); row.count=std::bit_cast<uint16_t>(remaining);
    std::copy_n(data::kUnitTypes[type].cost,11,std::begin(row.data));
    row.unk_01=0xa5; d.territories[0].queues[size_t(queue-1)].push_back(row);
}
struct Outcome { std::unique_ptr<save::Document> document=std::make_unique<save::Document>(); UnitManufacturingReport report; };
Outcome queued(const save::Document& source,int type,UnitManufacturingContext c=context()) {
    const auto before=bytes(source); const auto log=c.effects.log; const auto ai=c.effects.ai;
    Outcome out; save::Error e{save::ErrorCode::Io,99,"old"};
    ok(queueUnit(source,{1,type},c,*out.document,out.report,e),e);
    require(e.code==save::ErrorCode::None && !e.offset && e.message.empty() && bytes(source)==before && c.effects.log==log && c.effects.ai==ai,
            "QueueUnit must clear error and preserve source/context"); return out;
}
Outcome produced(const save::Document& source,int queue,int32_t work,UnitManufacturingContext c=context()) {
    const auto before=bytes(source); Outcome out; save::Error e;
    ok(produceUnits(source,{1,queue,work},c,*out.document,out.report,e),e);
    require(bytes(source)==before && e.code==save::ErrorCode::None,"ProduceUnits changed source or retained error");
    auto alias=std::make_unique<save::Document>(source); UnitManufacturingReport repeated;
    ok(produceUnits(*alias,{1,queue,work},c,*alias,repeated,e),e);
    require(bytes(*alias)==bytes(*out.document) && repeated==out.report,"ProduceUnits in-place differs from separate transaction");
    return out;
}
void queueAndCancel() {
    auto d=fixture();
    for (const auto pair:std::vector<std::pair<int,int>>{{1,1},{5,1},{12,2},{9,3},{16,4},{25,5},{31,2},{35,2}}) {
        const auto out=queued(*d,pair.first);
        const auto& q=out.document->territories[0].queues[size_t(pair.second-1)];
        require(out.report.queued && out.report.queueStructureChanged && out.report.queue==pair.second && q.size()==1 &&
                q[0].count==data::kUnitTypes[pair.first].buildLabor && q[0].unk_01==0,
                "queue derives original five classes, allocates work (not quantity), initializes owned opaque byte");
        require(out.report.payments.size()==1 && out.report.payments[0].affordabilityEvaluated &&
                out.report.events.empty() && out.report.rngAfter==context().effects.events.rngBeforeEvents,
                "QueueUnit has full real payment but no invented start notification/draw");
        require(out.document->territories[0].data.population==((pair.first==25 || pair.first==31)?400:500),
                "colonizer population charged on queueing, not unit completion");
    }
    auto fort=queued(*d,20);
    require(!fort.report.queued && fort.report.queue==0 && !fort.report.failureMask && bytes(*fort.document)==bytes(*d),
            "class without queue is authentic result0/no append, not a fabricated unit order");
    d->territories[0].data.population=100;
    auto population=queued(*d,25);
    require(!population.report.queued && population.report.failureMask==UINT32_MAX && population.report.payments.empty(),
            "colonizer requires strictly more than100 population before any payment");
    d->territories[0].data.population=500; d->players[0].credits=0;
    auto money=queued(*d,1); require(!money.report.queued && money.report.failureMask==1,"credit refusal is evaluated, no fake API error");
    d=fixture(); paidHead(*d,1,1,17); paidHead(*d,5,1,8);
    auto& row=d->territories[0].queues[0][1]; row.data[0]=3;
    row.data[1]=0x10002; row.data[4]=0x8001; row.data[10]=-1;
    const auto before=bytes(*d); auto output=fixture(); UnitDequeueReport refund; save::Error e;
    ok(dequeueUnit(*d,{1,1,1},*output,refund,e),e);
    require(refund.removed && refund.unitType==5 && refund.creditsRefunded==75 && output->players[0].credits==10075 &&
            refund.materialsRefunded[0]==2 && refund.materialsRefunded[3]==-32767 && refund.materialsRefunded[9]==-1 &&
            output->territories[0].data.materials[4]==1000-32767 && output->territories[0].queues[0].size()==1 && bytes(*d)==before,
            "dequeue refunds canonical money rather than paid0 and MOVSX low16 of each material");
    ok(dequeueUnit(*output,{1,1,999},*output,refund,e),e);
    require(!refund.removed && output->territories[0].queues[0].size()==1,"absent queue ordinal is native false without deletion");
    d=fixture(); auto colony=queued(*d,25);
    ok(dequeueUnit(*colony.document,{1,5,0},*output,refund,e),e);
    require(refund.populationBefore==400 && refund.populationAfter==500 && output->territories[0].queues[4].empty(),
            "cancel returns colonizer population and removes one owned node");
}
void progressAndCompletion() {
    auto d=fixture(); paidHead(*d,1,1,30);
    auto partial=produced(*d,1,7);
    require(partial.document->territories[0].queues[0][0].count==23 && partial.report.productionRemaining==0 &&
            partial.report.queueStructureChanged && partial.report.createdIds.empty() && partial.report.events.empty() &&
            partial.document->territories[0].queues[0][0].unk_01==0xa5,"partial work pops/reinserts preserving semantic data and owned opaque byte");
    auto full=produced(*d,1,31);
    require(full.report.createdIds==std::vector<uint32_t>{1001} && full.document->territories[0].queues[0].empty() &&
            full.report.productionRemaining==1 && full.document->armies[0].experience==0 && full.document->armies[0].dest.raw==1 &&
            full.document->options.turn==19,"completion creates real level0 unit, no training or turn increment invented");
    require(full.report.events.size()==2 && full.report.events[0].type==68 && full.report.events[1].type==69 &&
            full.report.logAfter.entries[0].player==71 && full.report.logAfter.entries[0].param==93 &&
            full.report.rngAfter.counters.secondary15==2,"completion then queue-empty actual ordinary events and portrait draws");
    const auto& text=full.report.logAfter.entries[0].text;
    require(std::string(text.begin(),text.end())=="A new Laser Squad has been fully outfitted and armed in Alpha.  The military unit is waiting for its first order.",
            "unit completion canonical event text");
    d=fixture(); paidHead(*d,1,1,0); paidHead(*d,1,1,-1);
    auto zero=produced(*d,1,1);
    require(zero.report.createdIds.size()==2 && zero.report.productionRemaining==1,"zero/negative signed work makes units without spending positive budget");
    d=fixture(); paidHead(*d,12,2,1);
    auto ship=produced(*d,2,1);
    require(ship.document->armies[0].type==12 && ship.document->armies[0].dest.raw==2 && ship.report.events.back().type==70,
            "sea production spawns at portTarget but logs source territory and shipyard completion");
    d=fixture(); paidHead(*d,35,2,1);
    auto siege=produced(*d,2,1);
    require(siege.report.createdIds==std::vector<uint32_t>{1001,1002} && siege.report.creations[0].pairedMissileId==1002 &&
            siege.document->armies[0].cargo[0].raw==1002,"manufactured siege cruiser uses real recursive paired-missile lifecycle");
    d=fixture(); paidHead(*d,16,4,1); // No missile base.
    auto denied=produced(*d,4,7);
    require(denied.report.creationBlocked && denied.report.creationDenial==ArmyCreationReason::MissileBaseMissing &&
            denied.report.createdIds.empty() && denied.document->options.nextGlobalId==1001 &&
            denied.document->territories[0].queues[3][0].count==0 && denied.report.events.empty() && denied.report.productionRemaining==0,
            "denied physical creation consumes ID, retains completed head, stops, and emits no fake completion");
    d=fixture(); paidHead(*d,1,1,1); paidHead(*d,1,1,1); d->territories[0].queues[0][1].data[0]=0;
    auto next=produced(*d,1,2);
    require(next.report.createdIds.size()==2 && next.document->players[0].credits==10000 && next.report.payments.empty(),
            "only INITIAL head receives funding check; later underpaid popped node is not silently repaired");
}
void headFinancingAndRepeat() {
    auto d=fixture(); paidHead(*d,1,1,5); d->territories[0].queues[0][0].data[0]=0;
    auto first=produced(*d,1,1);
    require(first.document->players[0].credits==9965 && first.document->territories[0].queues[0][0].count==29 &&
            first.document->territories[0].queues[0][0].data[0]==0 && !first.report.payments[0].affordabilityEvaluated,
            "head financing success resets work but DOES NOT update old paid data");
    auto second=produced(*first.document,1,1);
    require(second.document->players[0].credits==9930 && second.document->territories[0].queues[0][0].count==29,
            "original stale paid head can charge again and reset progress next invocation");
    auto negative=produced(*d,1,-7);
    require(negative.document->players[0].credits==9965 && negative.document->territories[0].queues[0][0].count==30 &&
            negative.report.productionRemaining==-7 && !negative.report.queueStructureChanged,
            "negative production still finances/reset head before native positive-work loop");
    d->players[0].credits=0;
    auto blocked=produced(*d,1,0);
    require(blocked.report.headFinancingBlocked && blocked.report.failureMask==1 && blocked.report.events.size()==1 &&
            blocked.report.events[0].type==74 && blocked.document->territories[0].queues[0][0].count==5 &&
            !blocked.report.queueStructureChanged,"head funding runs even with zero production; blocked head is not popped");
    d=fixture(); paidHead(*d,2,1,5); d->techs[10].knownMask=0;
    d->territories[0].queues[0][0].data[8]=0; d->territories[0].data.materials[8]=2;
    auto imports=produced(*d,1,9);
    require(imports.report.headFinancingBlocked && imports.report.failureMask==0x100 && imports.report.events.size()==2 &&
            imports.report.events[0].type==60 && imports.report.events[1].type==74 &&
            imports.document->territories[0].queues[0][0].data[8]==2 && imports.document->territories[0].queues[0][0].count==5 &&
            imports.report.logAfter.entries[0].player==1 && imports.report.logAfter.entries[0].param==8,
            "collector ignores lost tech, keeps partial paid parts, dispatches importEx60 before ordinary funding74");
    d=fixture(); paidHead(*d,1,1,1); d->territories[0].data.hoverway=2;
    auto repeat=produced(*d,1,31);
    require(repeat.report.createdIds.size()==2 && repeat.report.queued && repeat.report.events.size()==4 &&
            repeat.report.events[0].type==68 && repeat.report.events[1].type==64 && repeat.report.events[2].type==68 &&
            repeat.report.events[3].type==64 && repeat.document->territories[0].queues[0].size()==1 &&
            repeat.document->territories[0].queues[0][0].count==30 && repeat.document->players[0].credits==9930,
            "repeat bit1 appends fully paid canonical work to tail and can create twice in one explicit budget");
    d->players[0].credits=0;
    auto unpaid=produced(*d,1,1);
    require(unpaid.report.createdIds.size()==1 && unpaid.report.failureMask==1 &&
            unpaid.report.events[0].type==68 && unpaid.report.events[1].type==74 &&
            unpaid.document->territories[0].queues[0][0].count==30 && unpaid.document->territories[0].queues[0][0].data[0]==0 &&
            unpaid.report.payments.size()==2,"repeat credit refusal reinserts front with resetwork and separately collected affordable remainder");
    d=fixture(); paidHead(*d,25,5,1); d->territories[0].data.hoverway=32; d->players[0].credits=50;
    d->territories[0].data.materials[3]=0;
    d->territories[0].data.adjacency[0]|=4; d->territories[1].data.adjacency[0]|=2;
    for (auto& value:d->raceStats.v[53]) value=0;
    auto materialOnly=produced(*d,5,1);
    require(materialOnly.report.failureMask==8 && !materialOnly.report.queued && materialOnly.report.createdIds.size()==1 &&
            materialOnly.document->players[0].credits==0 && materialOnly.document->territories[0].queues[4].empty() &&
            materialOnly.report.events.size()==3 && materialOnly.report.events[0].type==68 &&
            materialOnly.report.events[1].type==64 && materialOnly.report.events[2].type==73,
            "repeat material-only failure8 passes native0xf001 test, announces64 but appends nothing, then empty73");
    d=fixture(); paidHead(*d,1,1,30); d->territories[0].data.hoverway=2;
    d->territories[0].queues[0][0].unk_01=0; // Repeat produces same semantic row.
    const QueueRecord original=d->territories[0].queues[0][0];
    auto same=produced(*d,1,30);
    require(std::memcmp(&original,&same.document->territories[0].queues[0][0],kQueueRecordSaved)==0 && same.report.queueStructureChanged,
            "byte-identical repeat still retires/allocates a node and must expire borrowed node identity");
}
void aiAndFailures() {
    auto d=fixture(); d->territories[0].data.owner=1; paidHead(*d,1,1,1);
    AiSession ai; save::Error e; ok(ai.initializeAfterLoad(*d,e),e);
    auto c=context(); c.effects.aiSession=&ai; const auto snapshot=ai.snapshot();
    auto result=produced(*d,1,1,c);
    require(result.report.events.size()==2 && result.report.events[0].aiDispatched && result.report.events[1].aiDispatched &&
            !result.report.events[0].aiReport.handled && result.report.rngAfter==c.effects.events.rngBeforeEvents &&
            result.report.logAfter.entries.empty() && ai.snapshot()==snapshot,
            "AI unit events use real default handlers, not fake human logs or invented RNG");
    auto output=fixture(); UnitManufacturingReport report; report.createdIds={999}; const auto old=report;
    const auto before=bytes(*d),after=bytes(*output);
    require(!produceUnits(*d,{1,1,1},context(),*output,report,e) && bytes(*d)==before && bytes(*output)==after && report==old,
            "late missing AI after successful spawn rolls back ID, entity, queue and report");
    d=fixture(); paidHead(*d,1,1,1); d->options.nextGlobalId=65535;
    require(!produceUnits(*d,{1,1,1},context(),*output,report,e) && bytes(*output)==after && report==old,"zero wrapped ID must not publish partial unit");
    d=fixture(); paidHead(*d,12,2,1); d->territories[0].data.portTarget=0;
    require(!produceUnits(*d,{1,2,1},context(),*output,report,e) && report==old,"unsafe sentinel port spawn must reject explicitly");
    d=fixture(); paidHead(*d,1,1,1); std::fill(std::begin(d->territories[0].data.name),std::end(d->territories[0].data.name),'X');
    const auto invalidName=bytes(*d);
    require(!produceUnits(*d,{1,1,1},context(),*d,report,e) && bytes(*d)==invalidName && report==old,"bad local event name rolls back in-place creation");
    d=fixture(); paidHead(*d,1,1,1); d->territories[0].queues[0].resize(255,d->territories[0].queues[0][0]);
    require(!queueUnit(*d,{1,1},context(),*output,report,e) && e.code==save::ErrorCode::Limit && report==old && bytes(*output)==after,
            "255 codec cap rejects paid append transactionally, never presented as original pool rule");
    require(!produceUnits(*d,{1,0,1},context(),*output,report,e) && !queueUnit(*d,{1,39},context(),*output,report,e),
            "unsafe queue/table indexes must reject");
}
void optionalCorpus(const fs::path& directory) {
    if (directory.empty() || !fs::is_regular_file(directory/"TUTORIAL.SAV")) return;
    auto one=[&](const save::Document& source) {
        const auto before=bytes(source); save::Error e;
        for (const auto& region:source.territories) if (region.data.owner>=0) {
            auto output=std::make_unique<save::Document>(); UnitDequeueReport r;
            for (int q=1;q<=5;++q) {
                ok(dequeueUnit(source,{region.data.index,q,UINT32_MAX},*output,r,e),e);
                require(!r.removed && bytes(*output)==before,"corpus absent ordinal must preserve exact document");
            }
            break;
        }
        require(bytes(source)==before,"corpus mutation escaped its candidate");
    };
    size_t count=0;
    for (const char* name:{"TUTORIAL.SAV","Saves/AUTOSAVE.SAV","Campaign/AUTOSAVE.CPN","Campaign/ChCht001.CPN"}) {
        if (!fs::is_regular_file(directory/name)) continue;
        auto d=std::make_unique<save::Document>(); save::Error e; ok(save::readDocument(directory/name,*d,e),e); one(*d); ++count;
    }
    std::ifstream index(directory/"LEVELS.HDX",std::ios::binary);
    if (index) {
        uint32_t total=0; require(bool(index.read(reinterpret_cast<char*>(&total),4)) && total<=4096,"invalid corpus index");
        for (uint32_t i=0;i<total;++i) {
            char entry[12]{}; require(bool(index.read(entry,12)),"truncated corpus index");
            const std::string name(entry,std::find(entry,entry+8,'\0')); auto d=std::make_unique<save::Document>(); save::Error e;
            ok(save::readScenario(directory/"LEVELS",name,*d,e),e); one(*d); ++count;
        }
    }
    std::cout<<"unit manufacturing: "<<count<<" corpus documents, non-destructive queue reader\n";
}
}
int main(int argc,char** argv) {
    try {
        rtl::srand(0x12345678); (void)rtl::lrand(); gg.rng2Seed=0xabcdef01;
        const auto low=rtl::seed(),high=rtl::seedHi(); const auto globals=std::make_unique<GameGlobals>(gg);
        const auto game=std::make_unique<GameState>(gs);
        queueAndCancel(); progressAndCompletion(); headFinancingAndRepeat(); aiAndFailures();
        optionalCorpus(argc>1?fs::path(argv[1]):fs::path{});
        require(rtl::seed()==low && rtl::seedHi()==high && std::memcmp(globals.get(),&gg,sizeof(gg))==0 &&
                std::memcmp(game.get(),&gs,sizeof(gs))==0,"manufacturing changed global game/RNG state");
        std::cout<<"unit manufacturing tests passed\n"; return 0;
    } catch (const std::exception& e) { std::cerr<<"unit manufacturing: "<<e.what()<<'\n'; return 1; }
}
