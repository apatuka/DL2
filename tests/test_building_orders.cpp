// Numeric oracles from0041d2bc,CheckBuilding0041d834,0044c3fc/0044c44c;
// these are not observations obtained by running the original executable.
#include "game/building_orders.h"
#include "game/data_tables.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include <cstring>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <type_traits>

namespace {
using namespace dl2;using namespace dl2::simulation;
void require(bool v,const char* text) {if(!v)throw std::runtime_error(text);}
void ok(bool v,const save::Error& e) {if(!v)throw std::runtime_error(e.message);}
template<class T> void append(std::vector<uint8_t>& out,const T& v) {
    static_assert(std::is_trivially_copyable_v<T>);
    const auto* p=reinterpret_cast<const uint8_t*>(&v);out.insert(out.end(),p,p+sizeof(T));
}
std::vector<uint8_t> bytes(const save::Document& d) {
    std::vector<uint8_t> out;save::Error e;ok(save::encode(d,out,e),e);
    for(const auto& b:d.buildings)append(out,b);
    for(const auto& t:d.territories){append(out,t.data);for(const auto& q:t.queues)for(const auto& n:q)append(out,n);}
    append(out,d.jobs);return out;
}
std::unique_ptr<save::Document> fixture() {
    auto d=std::make_unique<save::Document>();std::memcpy(d->header.text,save::kHeaderText,sizeof(save::kHeaderText));d->header.version=kSaveVersion;
    d->world.width=2;d->world.height=1;d->world.numTerritories=2;d->options.numPlayers=2;d->options.localPlayer=0;d->options.turn=81;
    d->territories.resize(2);d->tiles.resize(2);d->buildings.reserve(16);
    for(size_t p=0;p<7;++p){d->players[p].index=uint8_t(p);d->players[p].race=2;d->players[p].type=p?3:1;
        d->ministerJobs[p].resize(1);d->ministerJobs[p][0].type=1;for(auto& row:d->raceStats.v)row[p]=100;}
    for(size_t i=0;i<2;++i){auto& t=d->territories[i].data;t.index=uint16_t(i+1);t.owner=0;t.terrain=1;t.population=300;t.morale=100;t.knowledge=100;
        t.numTiles=1;t.tiles[0].raw=uint32_t(i);t.materials[1]=12000;t.production[2]=29;t.hoverway=0x3e;
        d->tiles[i].x=uint8_t(i);d->tiles[i].territory=int16_t(i+1);std::memcpy(t.name,"Colony",7);
        for(int s=0;s<36;++s){t.sites[s].unk_00=uint16_t(s%6+256*(s/6));t.sites[s].terrainFlags=1;}}
    return d;
}
Building& add(save::Document& d,int type,int site,int territory=1) {
    Building b{};b.id=uint16_t(200+d.buildings.size());b.type=uint8_t(type);b.category=data::kBuildingTypes[type].category;
    b.flags=6;b.race=2;b.territory=int16_t(territory);b.site=int8_t(site);
    if(!d.buildings.empty()){b.prev.raw=d.buildings.back().id;d.buildings.back().next.raw=b.id;}
    d.territories[size_t(territory-1)].data.sites[size_t(site)].building.raw=b.id;d.buildings.push_back(b);return d.buildings.back();
}
struct Result {std::unique_ptr<save::Document> d=std::make_unique<save::Document>();BuildingControlReport report;};
Result run(const save::Document& source,BuildingControlRequest request) {
    const auto before=bytes(source);Result out;save::Error e{save::ErrorCode::Io,8,"old"};ok(applyBuildingControl(source,request,*out.d,out.report,e),e);
    require(bytes(source)==before && e.code==save::ErrorCode::None && e.message.empty(),"building control preserves source and clears error");
    auto alias=std::make_unique<save::Document>(source);BuildingControlReport again;ok(applyBuildingControl(*alias,request,*alias,again,e),e);
    require(bytes(*alias)==bytes(*out.d) && again==out.report,"building control alias operation is deterministic");return out;
}
void rejected(const save::Document& source,BuildingControlRequest request,save::ErrorCode code=save::ErrorCode::InvalidState) {
    const auto before=bytes(source);auto dest=fixture();const auto old=bytes(*dest);BuildingControlReport r;r.building=777;r.accepted=true;r.housingAttempts=19;
    const auto prior=r;save::Error e;require(!applyBuildingControl(source,request,*dest,r,e) && e.code==code && !e.message.empty(),"unsafe building control returns an explicit error");
    require(bytes(source)==before && bytes(*dest)==old && r==prior,"building-control failure rolls back destination/report/source");
    auto alias=std::make_unique<save::Document>(source);require(!applyBuildingControl(*alias,request,*alias,r,e) && bytes(*alias)==before && r==prior,"alias failure also rolls back");
}
void denied(const save::Document& d,BuildingControlRequest q,BuildingControlDenial reason) {
    auto out=run(d,q);require(!out.report.accepted && out.report.denial==reason && out.report.buildings.empty() &&
        out.report.housingAttempts==0 && out.report.housingTransfers==0 && bytes(*out.d)==bytes(d),"ordinary control denial is evaluated and byte-exact unchanged");
}
void activity() {
    auto d=fixture();auto& industry=add(*d,9,0);industry.task[1]=3;industry.labor[1]=2;industry.flags=0x1f06;
    auto& house=add(*d,2,1);house.task[1]=20;house.labor[1]=1;
    auto& other=add(*d,9,0,2);other.labor[1]=19;
    auto out=run(*d,{0,industry.id,BuildingControl::ToggleActive,0});
    require(out.report.accepted && out.report.housingAttempts==2 && out.report.housingTransfers==2 && out.report.flagsBefore==0x1f06 && out.report.flagsAfter==2,
        "deactivation clears all five locks and attempts each original positive worker");
    auto expected=std::make_unique<save::Document>(*d);expected->buildings[0].flags=2;expected->buildings[0].labor[1]=0;expected->buildings[1].labor[1]=3;
    require(bytes(*out.d)==bytes(*expected) && out.report.buildings.size()==2,"deactivation touches exact labor/flags only; other colony, stocks, repeat flags and turn preserved");
    out=run(*expected,{0,industry.id,BuildingControl::ToggleActive,INT32_MIN});
    expected->buildings[0].flags=6;
    require(out.report.housingAttempts==0 && out.report.housingTransfers==0 && bytes(*out.d)==bytes(*expected),"activation does not steal housing labor; slot argument is irrelevant to activity");
    d=fixture();auto& alone=add(*d,9,0);alone.task[1]=3;alone.labor[1]=2;
    out=run(*d,{0,alone.id,BuildingControl::ToggleActive,0});
    require(out.report.housingAttempts==2 && out.report.housingTransfers==0 && out.d->buildings[0].labor[1]==0 && out.report.flagsAfter==2,
        "housing failure does not stop fixed-attempt loop; subsequent BalanceLabor clears inactive ordinary labor");
    d=fixture();auto& wide=add(*d,9,0);wide.flags=0x202;wide.task[1]=3;wide.labor[1]=65537;
    auto& housing=add(*d,2,1);housing.task[1]=20;housing.labor[1]=2;
    out=run(*d,{0,wide.id,BuildingControl::ToggleActive,0});
    require(out.d->buildings[0].labor[1]==1 && out.d->buildings[1].labor[1]==2 && out.report.flagsAfter==0x206,
        "activation callback narrows65537 to signed16 value1 BEFORE balancing; unchanged lock survives");
}
void selfHousing() {
    auto d=fixture();auto& house=add(*d,2,0);house.task[1]=20;house.labor[1]=3;house.flags=0x1f06;
    auto out=run(*d,{0,house.id,BuildingControl::ToggleActive,0});
    require(out.report.housingAttempts==3 && out.report.housingTransfers==3 && out.d->buildings[0].labor[1]==3 && out.report.flagsAfter==2,
        "same-slot housing transfer reports native success without removing workers; inactive housing keeps labor when pool is exhausted");
    d->territories[0].data.population=200;house.labor[1]=1;house.task[0]=3;house.labor[0]=1;
    out=run(*d,{0,house.id,BuildingControl::ToggleActive,0});
    require(out.report.housingAttempts==3 && out.report.housingTransfers==3 && out.d->buildings[0].labor[0]==0 && out.d->buildings[0].labor[1]==2,
        "later slot count is read live after earlier self-transfer, not captured simultaneously");
}
void locks() {
    for(int slot=0;slot<5;++slot){
        auto d=fixture();auto& b=add(*d,9,0);b.task[slot]=3;b.labor[slot]=1;
        auto& h=add(*d,2,1);h.task[1]=20;h.labor[1]=2;
        auto out=run(*d,{0,b.id,BuildingControl::ToggleTaskLock,slot});
        require(out.report.accepted && out.report.flagsAfter==uint16_t(6|(0x100u<<slot)) && out.report.housingAttempts==0 && out.d->buildings[0].labor[slot]==1,
            "each lock uses correct slot bit, retains unchanged labor and never calls housing");
        auto undone=run(*out.d,{0,b.id,BuildingControl::ToggleTaskLock,slot});require(bytes(*undone.d)==bytes(*d),"unlock restores unchanged baseline exactly");
    }
    auto d=fixture();auto& b=add(*d,9,0);b.task[1]=3;b.labor[1]=2;d->territories[0].data.population=100;
    auto out=run(*d,{0,b.id,BuildingControl::ToggleTaskLock,1});
    require(out.report.accepted && out.report.flagsAfter==6 && out.d->buildings[0].labor[1]==1,"BalanceLabor can immediately clear newly requested lock when it trims labor");
    b.flags=4;b.labor[1]=1;out=run(*d,{0,b.id,BuildingControl::ToggleTaskLock,1});
    require(out.report.accepted && out.report.flagsAfter==0x204,"enabled lock requires Active but not Built");
}
void denialsAndFailures() {
    auto d=fixture();auto& b=add(*d,9,0);b.task[1]=3;d->territories[0].data.population=0;d->territories[0].data.morale=13;
    for(int actor:{-1,1,7})denied(*d,{actor,b.id,BuildingControl::ToggleActive,0},BuildingControlDenial::NotLocalActor);
    d->players[0].type=3;denied(*d,{0,b.id,BuildingControl::ToggleActive,0},BuildingControlDenial::NotLocalActor);
    d->players[0].type=1;d->players[0].index=1;denied(*d,{0,b.id,BuildingControl::ToggleActive,0},BuildingControlDenial::NotLocalActor);d->players[0].index=0;
    for(int owner:{-1,1}){d->territories[0].data.owner=int8_t(owner);denied(*d,{0,b.id,BuildingControl::ToggleActive,0},BuildingControlDenial::NotOwner);}d->territories[0].data.owner=0;
    b.flags=2;denied(*d,{0,b.id,BuildingControl::ToggleTaskLock,1},BuildingControlDenial::Inactive);
    b.flags=6;denied(*d,{0,b.id,BuildingControl::ToggleTaskLock,0},BuildingControlDenial::EmptyTask);
    for(int slot:{-1,5})rejected(*d,{0,b.id,BuildingControl::ToggleTaskLock,slot});
    rejected(*d,{0,99999,BuildingControl::ToggleActive,0});rejected(*d,{0,b.id,static_cast<BuildingControl>(99),0});
    auto accepted=run(*d,{0,b.id,BuildingControl::ToggleTaskLock,1});
    require(accepted.report.moraleBefore==13 && accepted.report.moraleAfter==100,"accepted lock invokes actual empty-population balance unlike denied controls");
    b.labor[1]=1000001;rejected(*d,{0,b.id,BuildingControl::ToggleActive,0},save::ErrorCode::Limit);
    // First worker really leaves industry. An earlier taskless housing record
    // then makes final balance's fallback slot-1 unsafe, so EVERY effect rolls back.
    d=fixture();auto& broken=add(*d,1,0);(void)broken;
    auto& from=add(*d,9,1);from.task[1]=3;from.labor[1]=1;
    auto& target=add(*d,2,2);target.task[1]=20;
    rejected(*d,{0,from.id,BuildingControl::ToggleActive,0});
    require(std::string(buildingControlDenialName(BuildingControlDenial::NotOwner))=="not_owner" &&
        std::string(buildingControlDenialName(BuildingControlDenial::Inactive))=="inactive","denial labels stable for callers");
}
}
int main(){try{
    std::vector<uint8_t> g(sizeof(gs)),h(sizeof(gg));std::memcpy(g.data(),&gs,sizeof(gs));std::memcpy(h.data(),&gg,sizeof(gg));const auto seed=rtl::seed(),high=rtl::seedHi();
    activity();selfHousing();locks();denialsAndFailures();
    require(!std::memcmp(g.data(),&gs,sizeof(gs)) && !std::memcmp(h.data(),&gg,sizeof(gg)) && seed==rtl::seed() && high==rtl::seedHi(),"building controls leave legacy globals and RNG untouched");
    std::cout<<"building_orders: activity, self-housing, locks, denials, signed narrowing, rollback and alias passed\n";return 0;
}catch(const std::exception& e){std::cerr<<"building_orders: "<<e.what()<<'\n';return 1;}}
