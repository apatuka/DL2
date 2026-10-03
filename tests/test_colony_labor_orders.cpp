// Numeric oracles derived from0044c320/c2c0/bddc/bc68/bd0c/bacc and assembly,
// not results observed by running the original executable.
#include "game/colony_labor_orders.h"
#include "game/data_tables.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include <algorithm>
#include <cstring>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <type_traits>

namespace {
using namespace dl2; using namespace dl2::simulation;
void require(bool v,const char* text) { if (!v) throw std::runtime_error(text); }
void ok(bool v,const save::Error& e) { if (!v) throw std::runtime_error(e.message); }
template<class T> void append(std::vector<uint8_t>& out,const T& v) {
    static_assert(std::is_trivially_copyable_v<T>);
    const auto* p=reinterpret_cast<const uint8_t*>(&v); out.insert(out.end(),p,p+sizeof(T));
}
template<class T> void list(std::vector<uint8_t>& out,const std::vector<T>& v) {
    append(out,uint64_t(v.size())); for (const auto& item:v) append(out,item);
}
std::vector<uint8_t> bytes(const save::Document& d) {
    std::vector<uint8_t> out; save::Error e; ok(save::encode(d,out,e),e);
    // Include all transient/opaque record bytes that serialization may omit.
    list(out,d.buildings); list(out,d.armies); append(out,d.jobs);
    for (const auto& t:d.territories) { append(out,t.data); for (const auto& q:t.queues) list(out,q); }
    return out;
}
std::unique_ptr<save::Document> fixture() {
    auto d=std::make_unique<save::Document>();
    std::memcpy(d->header.text,save::kHeaderText,sizeof(save::kHeaderText));d->header.version=kSaveVersion;
    d->world.width=2;d->world.height=1;d->world.numTerritories=2;d->options.numPlayers=1;d->options.localPlayer=0;d->options.turn=73;
    d->territories.resize(2);d->tiles.resize(2);d->buildings.reserve(36);
    for (size_t p=0;p<7;++p) {
        d->players[p].type=p?3:1;d->players[p].index=uint8_t(p);d->players[p].race=2;
        d->ministerJobs[p].resize(1);d->ministerJobs[p][0].type=1;
        for (auto& row:d->raceStats.v) row[p]=100;
    }
    for (size_t i=0;i<2;++i) {
        auto& t=d->territories[i].data;t.index=uint16_t(i+1);t.owner=0;t.population=300;t.morale=100;t.terrain=1;t.knowledge=100;
        t.numTiles=1;t.tiles[0].raw=uint32_t(i);std::memcpy(t.name,"Colony",7);t.materials[1]=13000;t.production[2]=17;
        d->tiles[i].x=uint8_t(i);d->tiles[i].territory=int16_t(i+1);
        for (int s=0;s<36;++s) {t.sites[s].unk_00=uint16_t(s%6+256*(s/6));t.sites[s].terrainFlags=1;}
    }
    return d;
}
Building& add(save::Document& d,int type,int site,int territory=1) {
    Building b{};b.id=uint16_t(100+d.buildings.size());b.type=uint8_t(type);b.category=data::kBuildingTypes[type].category;
    b.territory=int16_t(territory);b.site=int8_t(site);b.flags=6;b.race=2;
    if (!d.buildings.empty()) {b.prev.raw=d.buildings.back().id;d.buildings.back().next.raw=b.id;}
    d.territories[size_t(territory-1)].data.sites[size_t(site)].building.raw=b.id;d.buildings.push_back(b);return d.buildings.back();
}
struct Result { std::unique_ptr<save::Document> d=std::make_unique<save::Document>();ColonyLaborOrderReport report; };
template<class Call> Result run(const save::Document& source,Call call) {
    const auto before=bytes(source);Result r;save::Error e{save::ErrorCode::Io,7,"old"};ok(call(source,*r.d,r.report,e),e);
    require(bytes(source)==before && e.code==save::ErrorCode::None,"labor order preserves source and clears error");
    auto alias=std::make_unique<save::Document>(source);ColonyLaborOrderReport again;ok(call(*alias,*alias,again,e),e);
    require(bytes(*alias)==bytes(*r.d) && again==r.report,"labor alias and report are deterministic");return r;
}
template<class Call> void deny(const save::Document& source,Call call) {
    const auto before=bytes(source);auto out=fixture();const auto old=bytes(*out);ColonyLaborOrderReport r;r.territory=99;r.accepted=true;
    const auto report=r;save::Error e;require(!call(source,*out,r,e) && e.code!=save::ErrorCode::None,"unsafe labor order explicitly rejected");
    require(bytes(source)==before && bytes(*out)==old && r==report,"API failure preserves all labor outputs");
}
Result transfer(const save::Document& d,LaborTransferRequest request) {
    return run(d,[&](const auto& src,auto& dst,auto& r,auto& e){return transferColonyLabor(src,request,dst,r,e);});
}
Result move(const save::Document& d,LaborMoveRequest request) {
    return run(d,[&](const auto& src,auto& dst,auto& r,auto& e){return moveColonyLabor(src,request,dst,r,e);});
}
void explicitTransfer() {
    auto d=fixture();auto& from=add(*d,1,0);auto& to=add(*d,9,1);
    from.labor[1]=2;from.flags|=0x200;to.flags=0x400; // Both slots locked; target inactive/unbuilt/taskless.
    const LaborTransferRequest req{1,from.id,to.id,1,2};auto out=transfer(*d,req);
    require(out.report.accepted && out.report.buildings.size()==2 && out.d->buildings[0].labor[1]==1 && out.d->buildings[1].labor[2]==1,
        "explicit transfer ignores task/lock/Active/Built checks and moves exactly one");
    auto expected=std::make_unique<save::Document>(*d);expected->buildings[0].labor[1]--;expected->buildings[1].labor[2]++;
    require(bytes(*out.d)==bytes(*expected),"explicit transfer touches only two labor words, no flags/materials/turn");
    to.labor[2]=4;out=transfer(*d,req);require(!out.report.accepted && out.report.denial==LaborMoveDenial::DestinationFull && bytes(*out.d)==bytes(*d),"capacity denial is evaluated unchanged");
    from.labor[1]=0;out=transfer(*d,req);require(out.report.denial==LaborMoveDenial::SourceEmpty,"empty source has precedence over full destination");
    from.labor[1]=9;out=transfer(*d,{1,from.id,from.id,1,3});
    require(out.report.accepted && out.d->buildings[0].labor[1]==8 && out.d->buildings[0].labor[3]==1,"same-building transfer bypasses overcapacity");
    out=transfer(*d,{1,from.id,from.id,1,1});require(out.report.accepted && out.report.buildings.empty() && bytes(*out.d)==bytes(*d),"same slot native success is a byte-exact no-op");
    from.labor[1]=INT32_MIN;to.labor[2]=0;out=transfer(*d,req);
    require(out.d->buildings[0].labor[1]==INT32_MAX && out.d->buildings[1].labor[2]==1,"negative source is nonempty and decrement wraps");
    from.labor[1]=1;to.labor[2]=INT32_MAX;to.labor[3]=INT32_MAX;out=transfer(*d,req);
    require(out.report.accepted && out.d->buildings[1].labor[2]==INT32_MIN,"capacity total and destination increment both wrap32");
    to.labor[2]=0;to.labor[3]=3;to.turnsLeft=1;out=transfer(*d,req);require(out.report.accepted,"unfinished MaxLabor is4 regardless of canonical capacity");
    for (int bad:{-1,5,INT32_MAX}) deny(*d,[&](const auto& src,auto& dst,auto& r,auto& e){auto q=req;q.fromSlot=bad;return transferColonyLabor(src,q,dst,r,e);});
    const auto foreign=add(*d,9,0,2).id;
    deny(*d,[&](const auto& src,auto& dst,auto& r,auto& e){return transferColonyLabor(src,{1,from.id,foreign,1,1},dst,r,e);});
    deny(*d,[&](const auto& src,auto& dst,auto& r,auto& e){return transferColonyLabor(src,{1,99999,to.id,1,1},dst,r,e);});
}
void automatic() {
    auto d=fixture();auto& from=add(*d,15,0);auto& to=add(*d,9,1);
    from.task[1]=3;from.labor[1]=4;from.task[2]=20;from.labor[2]=1;
    to.task[0]=21;to.task[1]=3;to.task[2]=4;to.flags=2;
    const LaborMoveRequest req{1,from.id,to.id};auto out=move(*d,req);
    require(out.report.accepted && out.d->buildings[0].labor[1]==4 && out.d->buildings[0].labor[2]==0 &&
        out.d->buildings[1].labor[1]==1 && out.d->buildings[1].flags==6,"remove prefers housing and add chooses first ordinary tied slot; auto activates energy building");
    from.task[2]=11;from.task[4]=0;from.labor[2]=1;
    out=move(*d,req);require(out.d->buildings[0].labor[1]==3 && out.d->buildings[0].labor[2]==1,"EMPTY manufacturing queue gives no immediate removal priority");
    QueueRecord item{};item.unitType=1;d->territories[0].queues[0].push_back(item);
    out=move(*d,req);require(out.d->buildings[0].labor[1]==4 && out.d->buildings[0].labor[2]==0,"NONEMPTY manufacturing queue gives immediate removal priority");
    from.flags|=0x200|0x400;out=move(*d,req);require(!out.report.accepted && out.report.denial==LaborMoveDenial::SourceLockedOrEmpty,"automatic honors source locks");
    from.flags=6;to.flags|=0x100|0x200|0x400;out=move(*d,req);
    require(out.report.denial==LaborMoveDenial::DestinationLockedOrTaskless,"automatic honors destination task locks");
    // The native destination selector can fail despite AllTasksNoneOrLocked==0.
    // Its initial score1000 excludes ordinary labor>=1000; a locked negative
    // slot makes total0, so capacity precheck still passes. Source removal and
    // positive-delta energy activation are NOT rolled back by native false.
    std::fill_n(to.task,5,0);std::fill_n(to.labor,5,0);to.task[1]=3;to.labor[1]=1000;to.labor[2]=-1000;to.flags=0x400;
    out=move(*d,req);require(!out.report.accepted && out.report.denial==LaborMoveDenial::DestinationAdjustmentFailed &&
        out.d->buildings[0].labor[2]==0 && out.d->buildings[1].labor[1]==1000 && out.d->buildings[1].flags==0x404 && out.report.buildings.size()==2,
        "native failed addition retains removed worker and actual activation effect");
    from.task[1]=from.task[2]=0;out=move(*d,req);require(out.report.denial==LaborMoveDenial::SourceAdjustmentFailed && bytes(*out.d)==bytes(*d),"nonzero taskless source passes precheck but selector denies");
    from.task[1]=3;from.labor[1]=0;from.labor[2]=2;
    deny(*d,[&](const auto& src,auto& dst,auto& r,auto& e){return moveColonyLabor(src,req,dst,r,e);}); // selected task has0; original loop hangs.
}
void adjustmentLeaves() {
    auto d=fixture();auto& b=add(*d,15,0);b.task[0]=21;b.task[1]=3;b.task[2]=4;b.task[4]=11;b.labor[1]=b.labor[2]=2;
    auto out=std::make_unique<save::Document>();save::Error e;bool native=false;
    ok(adjustBuildingLabor(*d,b.id,3,*out,native,e),e);require(native && out->buildings[0].labor[1]==5,"addition applies entire delta to first minimum, not round-robin");
    b.labor[1]=b.labor[2]=3;QueueRecord item{};item.unitType=1;d->territories[0].queues[0].push_back(item);
    ok(adjustBuildingLabor(*d,b.id,1,*out,native,e),e);require(out->buildings[0].labor[4]==1,"queued task11 participates in minimum addition score");
    d->territories[0].queues[0].clear();ok(adjustBuildingLabor(*d,b.id,1,*out,native,e),e);require(out->buildings[0].labor[1]==4,"empty task11 is score999, not minimum0");
    b.flags=2;std::fill_n(b.task,5,0);std::fill_n(b.labor,5,0);
    ok(adjustBuildingLabor(*d,b.id,1,*out,native,e),e);require(!native && out->buildings[0].flags==6,"positive failed adjustment still activates zero-total energy consumer");
    ok(adjustBuildingLabor(*d,b.id,0,*out,native,e),e);require(!native && bytes(*out)==bytes(*d),"zero delta is evaluated native false without activation");
    b.task[1]=3;b.labor[1]=1;ok(adjustBuildingLabor(*d,b.id,INT32_MIN,*out,native,e),e);
    require(native && out->buildings[0].labor[1]==INT32_MIN+1,"INT_MIN removal negation wraps then signed minimum follows original");
    b.labor[1]=0;const auto old=bytes(*out);native=true;
    require(!adjustBuildingLabor(*d,b.id,-1,*out,native,e) && e.code==save::ErrorCode::Limit && native && bytes(*out)==old,"no-progress selector fails atomically, preserves nativeResult");
    b.flags=6;b.turnsLeft=10;b.task[0]=2;b.labor[0]=2;b.task[1]=3;b.labor[1]=3;
    ok(adjustBuildingLabor(*d,b.id,-1,*out,native,e),e);
    require(native && out->buildings[0].labor[0]==1 && out->buildings[0].labor[1]==3,"construction output50/25 both finish10 in1 turn; redundant labor removed first");
    b.turnsLeft=100;ok(adjustBuildingLabor(*d,b.id,-1,*out,native,e),e);
    require(out->buildings[0].labor[0]==2 && out->buildings[0].labor[1]==2,"construction output50/25 changes turns2/4; larger ordinary slot wins");
    b.labor[0]=0;const auto safe=bytes(*out);native=true;
    require(!adjustBuildingLabor(*d,b.id,-1,*out,native,e) && bytes(*out)==safe && native,"construction selector rejects unsafe negative scalar table index before mutation");
    d=fixture();auto& house=add(*d,1,0);house.task[0]=21;house.labor[0]=2;house.unk_16=110;house.task[2]=3;house.labor[2]=3;
    ok(adjustBuildingLabor(*d,house.id,-1,*out,native,e),e);
    require(out->buildings[0].labor[0]==1 && out->buildings[0].labor[2]==3,"upgrade remaining120-110 and outputs40/20 finish equally; selector prefers upgrade");
}
void reset() {
    auto d=fixture();auto& house=add(*d,2,0);house.task[1]=20;house.labor[1]=1;house.flags|=0x200;
    auto& industry=add(*d,9,1);industry.task[1]=3;industry.labor[1]=7;industry.flags|=0x200;
    auto& untouched=add(*d,9,0,2);untouched.labor[1]=12;
    auto out=run(*d,[](const auto& src,auto& dst,auto& r,auto& e){return resetColonyLabor(src,1,dst,r,e);});
    require(out.report.accepted && out.report.kind==LaborOrderKind::ResetToHousing && out.d->buildings[0].labor[1]==3 && out.d->buildings[1].labor[1]==0 &&
        out.d->buildings[2].labor[1]==12 && out.d->buildings[0].flags==house.flags && out.d->buildings[1].flags==industry.flags,
        "reset places amount3 before subtracting pool, clears other work, preserves untrimmed locks and other colony");
    require(out.d->territories[0].data.materials[1]==13000 && out.d->territories[0].data.production[2]==17 && out.d->options.turn==73,"reset has no stock clamp, scratch reset or turn increment");
    d->territories[0].data.population=0;d->territories[0].data.morale=22;
    out=run(*d,[](const auto& src,auto& dst,auto& r,auto& e){return resetColonyLabor(src,1,dst,r,e);});
    require(out.report.moraleBefore==22 && out.report.moraleAfter==100 && out.d->buildings[0].labor[1]==0,"reset delegates actual BalanceLabor empty-colony morale effect");
    d->territories[0].data.population=300;house.task[1]=0;
    deny(*d,[](const auto& src,auto& dst,auto& r,auto& e){return resetColonyLabor(src,1,dst,r,e);}); // Late balance fallback -1.
    deny(*d,[](const auto& src,auto& dst,auto& r,auto& e){return resetColonyLabor(src,0,dst,r,e);});
}
}
int main() {try {
    std::vector<uint8_t> g(sizeof(gs)),h(sizeof(gg));std::memcpy(g.data(),&gs,sizeof(gs));std::memcpy(h.data(),&gg,sizeof(gg));
    const auto seed=rtl::seed(),high=rtl::seedHi();
    explicitTransfer();automatic();adjustmentLeaves();reset();
    require(!std::memcmp(g.data(),&gs,sizeof(gs)) && !std::memcmp(h.data(),&gg,sizeof(gg)) && seed==rtl::seed() && high==rtl::seedHi(),"labor commands leave legacy globals and RNG untouched");
    std::cout<<"colony_labor_orders: explicit/automatic transfers, selectors, signed arithmetic, reset, denial and rollback passed\n";return 0;
} catch (const std::exception& e) {std::cerr<<"colony_labor_orders: "<<e.what()<<'\n';return 1;}}
