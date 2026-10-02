// Integer/order oracles derived from00472974/00472844/00472bf0/0046b9a0.
// These are not observations from running DEADLOCK.EXE.
#include "game/economic_logistics.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include "game/save_files.h"
#include <algorithm>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>

namespace {
using namespace dl2;
using namespace dl2::simulation;
void check(bool value,const char* message) { if (!value) throw std::runtime_error(message); }
void ok(bool value,const save::Error& error) { if (!value) throw std::runtime_error(error.message); }
std::unique_ptr<save::Document> fixture(int count=3) {
    auto d=std::make_unique<save::Document>();
    std::memcpy(d->header.text,save::kHeaderText,sizeof(save::kHeaderText)); d->header.version=kSaveVersion;
    d->options.numPlayers=2; d->options.localPlayer=0; d->options.turn=19; d->options.nextGlobalId=411;
    d->world.width=uint8_t(count); d->world.height=1; d->world.numTerritories=uint16_t(count);
    d->territories.resize(size_t(count)); d->tiles.resize(size_t(count));
    for (size_t p=0;p<7;++p) {
        d->players[p].index=uint8_t(p); d->players[p].race=int8_t(p); d->players[p].type=p?3:1;
        d->players[p].credits=100; d->ministerJobs[p].resize(1); d->ministerJobs[p][0].type=1;
        d->raceStats.v[61][p]=100;
    }
    for (int i=0;i<count;++i) {
        auto& t=d->territories[size_t(i)].data; t.index=uint16_t(i+1); t.owner=0; t.terrain=1;
        t.numTiles=1; t.tiles[0].raw=uint32_t(i); t.population=1000; t.morale=100;
        std::memcpy(t.name,"Alpha",6); t.consumption[7]=991;
        std::memset(t.unk_ad6,0xa5,sizeof(t.unk_ad6)); // NEVER native supplier pointers.
        d->tiles[size_t(i)].x=uint8_t(i); d->tiles[size_t(i)].territory=int16_t(i+1);
    }
    d->localList={0,0xff,0x80}; d->events.resize(1); d->options.eventCount=1;
    d->events[0].text={'a',0,0xff}; d->events[0].record.textLen=3;
    return d;
}
Territory& t(save::Document& d,int index) { return d.territories[size_t(index-1)].data; }
const Territory& t(const save::Document& d,int index) { return d.territories[size_t(index-1)].data; }
void edge(save::Document& d,int a,int b) {
    t(d,a).adjacency[b/16]|=uint16_t(1u<<(b%16)); t(d,b).adjacency[a/16]|=uint16_t(1u<<(a%16));
}
void building(save::Document& d,int type,int site,uint16_t flags=4,int16_t work=0) {
    Building b{}; b.id=uint16_t(1000+d.buildings.size()); b.type=uint8_t(type); b.territory=1;
    b.site=int8_t(site); b.flags=flags; b.turnsLeft=work;
    t(d,1).sites[site].building.raw=b.id; d.buildings.push_back(b);
}
std::vector<uint8_t> bytes(const save::Document& d) {
    save::Error error; std::vector<uint8_t> result; ok(save::encode(d,result,error),error);
    for (const auto& record:d.territories) {
        const auto* start=reinterpret_cast<const uint8_t*>(&record.data);
        result.insert(result.end(),start+kTerritorySavedBytes,start+sizeof(Territory));
    }
    return result;
}
ConstructionOrderContext context() {
    ConstructionOrderContext c; SessionRng rng; save::Error error; ok(rng.initialize(54,error),error);
    c.events.rngBeforeEvents=c.ai.rng=c.log.rngAfterEvents=rng.snapshot(); return c;
}
struct Outcome { std::unique_ptr<save::Document> document=fixture(); EconomicLogisticsReport report; };
Outcome collect(const save::Document& source,MaterialCollectionRequest request,ConstructionOrderContext c=context()) {
    const auto before=bytes(source); const auto log=c.log, aiLog=c.log; const auto ai=c.ai;
    Outcome out; save::Error error{save::ErrorCode::Io,99,"old"};
    ok(collectMaterial(source,request,c,*out.document,out.report,error),error);
    check(error.code==save::ErrorCode::None && !error.offset && error.message.empty(),"collection clears stale error");
    check(bytes(source)==before && c.log==log && c.log==aiLog && c.ai==ai,"collection preserves source/context");
    auto alias=std::make_unique<save::Document>(source); EconomicLogisticsReport repeat;
    ok(collectMaterial(*alias,request,c,*alias,repeat,error),error);
    check(bytes(*alias)==bytes(*out.document) && repeat==out.report,"in-place collection is identical and deterministic");
    return out;
}
void directCollection() {
    auto d=fixture(); edge(*d,1,2); t(*d,1).materials[3]=5; t(*d,2).materials[3]=20; t(*d,2).production[3]=7;
    auto out=collect(*d,{1,0,3,10,true}); const auto& r=out.report.collections[0];
    check(r.result==20 && r.cost==20 && r.remaining==0 && t(*out.document,1).materials[3]==15 &&
          t(*out.document,2).materials[3]==10 && t(*out.document,2).production[3]==7 && out.document->players[0].credits==80,
          "explicit amount imports10 IN ADDITION to local5; donor reserve7 is not cleared");
    check(out.report.collectionAfter.transfers==std::vector<MaterialTransfer>{{2,1,3,10,20}} &&
          out.report.collectionAfter.suppliers[1]==MaterialSupplier{2,2} && out.report.events.empty() &&
          out.report.rngAfter==context().events.rngBeforeEvents,"canonical fee2, owned cache/ledger, no extra RNG/events");
    check(std::memcmp(t(*out.document,1).unk_ad6,t(*d,1).unk_ad6,sizeof(t(*d,1).unk_ad6))==0,
          "opaque native supplier words are never read or overwritten");
    auto next=context(); next.payment.collection=out.report.collectionAfter;
    auto more=collect(*out.document,{1,0,3,2,true},next);
    check(more.report.collectionAfter.transfers==std::vector<MaterialTransfer>{{2,1,3,12,24}} && more.document->players[0].credits==76,
          "persistent ledger merges same donor/target/material in place");
    d=fixture(); edge(*d,1,2); t(*d,1).owner=-1; t(*d,2).owner=1; t(*d,2).materials[1]=5;
    out=collect(*d,{1,1,1,2,true});
    check(out.report.collections[0].cost==6 && out.document->players[1].credits==94 && out.document->players[0].credits==100 &&
          t(*out.document,1).materials[1]==2 && t(*out.document,2).materials[1]==3,
          "explicit payer1 imports food into unowned territory via mode1 fee3");
    d=fixture(); edge(*d,1,2); t(*d,2).materials[3]=20;
    auto quoted=context(); quoted.payment.collection.suppliers[1]={3,91};
    out=collect(*d,{1,0,3,7,false},quoted);
    check(out.report.collections[0].result==14 && t(*out.document,2).production[3]==7 && t(*out.document,2).materials[3]==20 &&
          t(*out.document,1).materials[3]==0 && out.document->players[0].credits==100 &&
          out.report.collectionAfter.suppliers[1]==MaterialSupplier{3,2} && out.report.collectionAfter.transfers.empty(),
          "quote reserves donor, preserves credits/stock, restores pointer3 but NOT old fee91");
    for (int32_t amount:{0,-1,std::numeric_limits<int32_t>::min()}) {
        out=collect(*d,{1,0,3,amount,true});
        check(out.report.collections[0].remaining==amount && out.report.collections[0].cost==0 &&
              out.report.collections[0].result==(amount? -1:0) && bytes(*out.document)==bytes(*d),
              "nonpositive request writes exact native remaining/cost/return without search");
    }
}
void limitsAndSupplierOrder() {
    auto d=fixture(); edge(*d,1,2); edge(*d,1,3);
    t(*d,1).continent=t(*d,3).continent=1; t(*d,2).continent=2;
    t(*d,2).materials[3]=t(*d,3).materials[3]=20;
    auto dest=fixture(); SupplierSearchReport search; save::Error error;
    ok(findMaterialSupplier(*d,{1,0,3,2},{},*dest,search,error),error);
    check(search.found && search.stockExists && search.collection.suppliers[1]==MaterialSupplier{2,4} &&
          dest->players[0].credits==100 && t(*dest,2).materials[3]==20,
          "supplier2 mode2 wins before cheaper supplier3 mode0; search itself never pays");
    d->players[0].credits=3;
    ok(findMaterialSupplier(*d,{1,0,3,2},{},*dest,search,error),error);
    check(search.found && search.collection.suppliers[1]==MaterialSupplier{3,2},"unaffordable first donor falls back to later affordable route");
    d=fixture(); edge(*d,1,2); t(*d,2).materials[3]=20; d->techs[46].knownMask=1; d->players[0].credits=3;
    auto out=collect(*d,{1,0,3,5,true});
    check(out.report.collections[0].result==0 && out.report.collections[0].cost==0 && out.document->players[0].credits==3 &&
          t(*out.document,1).materials[3]==5,"zero fee caps EACH chunk by credits, not total requested");
    d->players[0].credits=0; out=collect(*d,{1,0,3,1,true});
    check(out.report.collections[0].remaining==1 && out.report.collections[0].result==-1 && out.report.events.empty(),
          "zero fee with zero credits cannot move one unit, without blockade notice");
    d=fixture(); edge(*d,1,2); t(*d,2).materials[3]=50; d->players[0].credits=5;
    out=collect(*d,{1,0,3,4,true});
    check(out.report.collections[0].cost==4 && out.report.collections[0].remaining==2 && out.report.collections[0].result==-1 &&
          t(*out.document,1).materials[3]==2 && out.document->players[0].credits==1 && out.report.events.size()==1,
          "partial delivery remains committed and exhausted freight money yields real60");
    d->players[0].credits=100; t(*d,1).materials[3]=9998;
    out=collect(*d,{1,0,3,5,true});
    check(t(*out.document,1).materials[3]==10000 && out.report.collections[0].remaining==3 &&
          out.report.collections[0].cost==4 && out.report.events.empty(),"stock10000 cap preserves partial cost without fake blockade");
    // Mission/domain food path may request mode3 without tech46.
    d=fixture(); edge(*d,1,2); edge(*d,2,3); t(*d,2).owner=1; t(*d,3).materials[1]=5;
    ok(findMaterialSupplier(*d,{1,0,1,2},{},*dest,search,error),error);
    check(!search.found && search.stockExists,"enemy intermediate cannot pass modes0..2");
    ok(findMaterialSupplier(*d,{1,0,1,3},{},*dest,search,error),error);
    check(search.found && search.collection.suppliers[1]==MaterialSupplier{3,5},"explicit mode3 crosses enemy intermediate at fee5");
}
void deficitRounds() {
    auto d=fixture(); edge(*d,1,3); edge(*d,2,3);
    t(*d,1).production[1]=t(*d,2).production[1]=15; t(*d,3).production[1]=10; t(*d,3).materials[1]=40;
    t(*d,1).production[2]=3; t(*d,3).materials[2]=5;
    auto c=context(); c.payment.collection.suppliers[0]={1,83}; c.payment.collection.suppliers[1]={3,-99};
    auto out=fixture(); EconomicLogisticsReport r; save::Error error; const auto before=bytes(*d);
    ok(importDeficits(*d,c,*out,r,error),error);
    check(r.collections.size()==5,"four food chunks then one energy chunk");
    const int territories[]={1,2,1,2,1}, materials[]={1,1,1,1,2}, amounts[]={10,10,5,5,3};
    for (size_t i=0;i<5;++i)
        check(r.collections[i].request.territory==uint32_t(territories[i]) && r.collections[i].request.material==materials[i] &&
              r.collections[i].request.amount==amounts[i] && r.collections[i].remaining==0,"material-major round-robin ten-unit oracle");
    check(t(*out,1).materials[1]==15 && t(*out,2).materials[1]==15 && t(*out,3).materials[1]==10 &&
          t(*out,1).materials[2]==3 && t(*out,3).materials[2]==2 && out->players[0].credits==34,
          "reserves protect donorfood10; original freight66 across5calls");
    check(r.collectionAfter.transfers==std::vector<MaterialTransfer>{{3,1,1,15,30},{3,2,1,15,30},{3,1,2,3,6}},
          "transfer order is first occurrence while later rounds merge");
    check(r.collectionAfter.suppliers[0]==MaterialSupplier{1,83} && r.collectionAfter.suppliers[1]==MaterialSupplier{} &&
          r.collectionAfter.suppliers[2]==MaterialSupplier{} && r.collectionAfter.suppliers[3]==MaterialSupplier{},
          "each material resets owned1..N ID+fee, not sentinel0 cache");
    check(bytes(*d)==before && out->options.turn==19 && out->events[0].text==d->events[0].text && out->localList==d->localList,
          "needs/import phase does not mutate source, persist runtime events, or advance turn");
    d=fixture(); edge(*d,1,2); t(*d,1).production[1]=10; t(*d,2).materials[1]=5;
    ok(importDeficits(*d,context(),*out,r,error),error);
    check(r.collections.size()==1 && r.collections[0].remaining==5 && r.collections[0].cost==10 &&
          t(*out,1).materials[1]==5 && r.events.empty(),"a partial-only round returns-1 and MUST NOT trigger another pass");
    d=fixture(); t(*d,1).production[1]=std::numeric_limits<int32_t>::max(); t(*d,1).materials[1]=-1;
    ok(importDeficits(*d,context(),*out,r,error),error);
    check(r.collections.size()==1 && r.collections[0].request.amount==std::numeric_limits<int32_t>::min() &&
          r.collections[0].result==-1 && t(*out,1).materials[1]==-1,"signed deficit wraps BEFORE min(deficit,10), no infinite retry");
}
void needsAndReset() {
    auto d=fixture(); t(*d,1).population=32767; d->raceStats.v[61][0]=32767;
    for (auto& region:d->territories) { std::fill_n(region.data.production,11,77); region.data.materials[2]=123; }
    building(*d,20,0,4); building(*d,7,1,2); building(*d,16,2,4); building(*d,4,3,6,1); building(*d,7,35,4);
    auto out=fixture(); NeedsPlan needs; save::Error error; const auto before=bytes(*d);
    ok(recordFoodEnergyNeeds(*d,*out,needs,error),error);
    check(needs.territories[0].foodNeed==107367 && t(*out,1).production[1]==-23705 && t(*out,1).production[2]==75 &&
          t(*out,1).materials[2]==123 && t(*out,1).production[3]==77,"needs narrow107367 to-23705, energy40+25+10, no stock consumption");
    check(bytes(*d)==before,"record needs preserves source");
    ResourceCollectionState c; c.suppliers[1]={2,17}; c.transfers={{2,1,3,5,10}}; ResourceCollectionState after;
    ok(resetEconomicLogistics(*out,c,*out,after,error),error);
    for (const auto& region:out->territories) {
        check(std::all_of(std::begin(region.data.production),std::end(region.data.production),[](int32_t v){return v==0;}),"all11 reservations reset");
        check(region.data.consumption[7]==991 && region.data.materials[2]==123,"reset does not clear consultive cache or material stock");
    }
    check(after.transfers.empty() && after.suppliers==c.suppliers && c.transfers.size()==1,"reset ledger only, preserving supplier fees/IDs and inputstate");
    d->players[0].race=127; const auto old=bytes(*out); const auto prior=needs.territories[0].foodNeed;
    check(!recordFoodEnergyNeeds(*d,*out,needs,error) && bytes(*out)==old && needs.territories[0].foodNeed==prior,
          "out-of-block race rejects need recording transactionally");
}
void eventsAndRollback() {
    auto d=fixture(); t(*d,2).materials[3]=50; //disconnected stock triggers60, unlike no donorstock.
    auto out=collect(*d,{1,0,3,1,true});
    check(out.report.events.size()==1 && out.report.events[0].local && out.report.logAfter.entries.size()==1 &&
          out.report.logAfter.entries[0].type==60 && out.report.logAfter.entries[0].player==1 && out.report.logAfter.entries[0].param==3,
          "blockade is real local extended60 with territory/material payload");
    const auto& text=out.report.logAfter.entries[0].text;
    check(std::string(text.begin(),text.end())=="A blockade of Alpha has cut off our much needed shipments of wood!",
          "canonical event60 string, not placeholder notification");
    check(out.report.rngAfter.counters.secondary15==1,"blockade event executes one real portrait draw");
    t(*d,1).owner=t(*d,2).owner=1; AiSession ai; save::Error error; ok(ai.initializeAfterLoad(*d,error),error);
    auto c=context(); c.aiSession=&ai; const auto beforeAi=ai.snapshot();
    out=collect(*d,{1,1,3,1,true},c);
    check(out.report.events.size()==1 && out.report.events[0].aiDispatched && !out.report.events[0].aiReport.handled &&
          out.report.logAfter.entries.empty() && out.report.rngAfter==c.events.rngBeforeEvents && ai.snapshot()==beforeAi,
          "nonlocal AI60 executes verified default handler without fake local log/RNG");
    auto output=fixture(); EconomicLogisticsReport prior; prior.collections.resize(1); prior.collections[0].cost=123;
    const auto old=prior; const auto before=bytes(*output), input=bytes(*d);
    check(!collectMaterial(*d,{1,1,3,1,true},context(),*output,prior,error) && bytes(*d)==input && bytes(*output)==before && prior==old,
          "late missing AI event rolls back search scratch/document/report");
    d=fixture(); t(*d,1).production[1]=1; t(*d,2).materials[1]=4;
    std::fill(std::begin(t(*d,1).name),std::end(t(*d,1).name),'X');
    check(!importDeficits(*d,context(),*output,prior,error) && bytes(*output)==before && prior==old,
          "late bad event formatter rolls back complete deficit phase");
    d=fixture(); edge(*d,1,2); t(*d,2).materials[3]=1;
    c=context(); c.payment.collection.transfers.assign(250,{2,1,1,1,2});
    check(!collectMaterial(*d,{1,0,3,1,true},c,*output,prior,error) && error.code==save::ErrorCode::Limit &&
          bytes(*output)==before && prior==old,"new251st transfer fails AFTER internal debit without publishing partial state");
    c=context(); c.payment.collection.suppliers[1]={99,2};
    check(!collectMaterial(*d,{1,0,3,1,true},c,*output,prior,error) && bytes(*output)==before && prior==old,"foreign supplier ID rejects atomically");
    check(!collectMaterial(*d,{1,7,3,1,true},context(),*output,prior,error) && prior==old,"invalid explicit payer rejects");
    check(!collectMaterial(*d,{1,0,11,1,true},context(),*output,prior,error) && prior==old,"invalid material rejects");
    c=context(); c.events.rngBeforeEvents.initialized=false;
    check(!importDeficits(*d,c,*output,prior,error) && bytes(*output)==before && prior==old,"invalid RNG rejects even when no notice would fire");
}
void corpus(const std::filesystem::path& path) {
    if (path.empty() || !std::filesystem::is_regular_file(path/"TUTORIAL.SAV")) {
        std::cout<<"economic logistics: optional Tutorial corpus unavailable\n"; return;
    }
    auto source=std::make_unique<save::Document>(),output=std::make_unique<save::Document>(); save::Error error;
    ok(save::readDocument(path/"TUTORIAL.SAV",*source,error),error); const auto original=bytes(*source);
    ResourceCollectionState state; ok(resetEconomicLogistics(*source,state,*output,state,error),error);
    NeedsPlan recorded; ok(recordFoodEnergyNeeds(*output,*output,recorded,error),error);
    check(recorded.territories.size()==source->territories.size() && bytes(*source)==original,"real corpus resets/needs remain owned and complete");
    for (size_t i=0;i<recorded.territories.size();++i)
        check(output->territories[i].data.production[1]==recorded.territories[i].foodReserve &&
              output->territories[i].data.production[2]==recorded.territories[i].energyReserve,"corpus records report at physical reservation offsets");
}
}
int main(int argc,char** argv) {
    try {
        std::vector<uint8_t> gsBefore(sizeof(gs)),ggBefore(sizeof(gg));
        std::memcpy(gsBefore.data(),&gs,sizeof(gs)); std::memcpy(ggBefore.data(),&gg,sizeof(gg));
        const auto seed=rtl::seed(),high=rtl::seedHi();
        directCollection(); limitsAndSupplierOrder(); deficitRounds(); needsAndReset(); eventsAndRollback();
        corpus(argc>1?std::filesystem::path(argv[1]):std::filesystem::path{});
        check(std::memcmp(gsBefore.data(),&gs,sizeof(gs))==0 && std::memcmp(ggBefore.data(),&gg,sizeof(gg))==0 &&
              rtl::seed()==seed && rtl::seedHi()==high,"logistics must never change native globals/RNG");
        std::cout<<"economic logistics: collection, supplier order, deficit rounds, needs/reset, real events and rollback passed\n";
        return 0;
    } catch (const std::exception& error) { std::cerr<<error.what()<<'\n'; return 1; }
}
