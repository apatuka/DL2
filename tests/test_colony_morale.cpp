#include "game/colony_morale.h"
#include "game/labor_balance.h"
#include "game/data_tables.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include <cstring>
#include <iostream>
#include <memory>
#include <stdexcept>
namespace {
using namespace dl2;using namespace dl2::simulation;
void require(bool v,const char* t){if(!v)throw std::runtime_error(t);}
void ok(bool v,const save::Error& e){if(!v)throw std::runtime_error(e.message);}
std::unique_ptr<save::Document> fixture(){
    auto d=std::make_unique<save::Document>();std::memcpy(d->header.text,save::kHeaderText,sizeof(save::kHeaderText));d->header.version=kSaveVersion;
    d->world.width=2;d->world.height=1;d->world.numTerritories=2;d->territories.resize(2);d->tiles.resize(2);d->options.numPlayers=2;d->options.localPlayer=0;
    for(size_t p=0;p<7;++p){d->players[p].index=uint8_t(p);d->players[p].race=2;d->players[p].type=p?3:1;d->players[p].taxLevel=2;
        d->ministerJobs[p].resize(1);d->ministerJobs[p][0].type=1;}
    d->raceStats.v[24][2]=100;d->raceStats.v[25][2]=100;d->raceStats.v[27][2]=20;d->raceStats.v[22][2]=100;d->raceStats.v[7][2]=100;
    for(size_t i=0;i<2;++i){auto& t=d->territories[i].data;t.index=uint16_t(i+1);t.owner=i?-1:0;t.population=1000;t.morale=50;t.terrain=1;t.knowledge=100;t.numTiles=1;t.tiles[0].raw=uint32_t(i);
        std::memcpy(t.name,"Alpha",6);d->tiles[i].x=uint8_t(i);d->tiles[i].territory=int16_t(i+1);
        for(int s=0;s<36;++s){t.sites[s].unk_00=uint16_t(s%6+256*(s/6));t.sites[s].terrainFlags=1;}}
    return d;
}
uint32_t building(save::Document& d,int type,int site,uint16_t flags=6){
    Building b{};b.id=uint16_t(d.buildings.size()+1);b.type=uint8_t(type);b.category=data::kBuildingTypes[type].category;b.race=2;b.territory=1;b.site=int8_t(site);b.flags=flags;
    if(!d.buildings.empty()){b.prev.raw=d.buildings.back().id;d.buildings.back().next.raw=b.id;}d.territories[0].data.sites[site].building.raw=b.id;d.buildings.push_back(b);return b.id;
}
Building& b(save::Document& d,uint32_t id){for(auto& v:d.buildings)if(v.id==id)return v;throw std::runtime_error("test building missing");}
uint32_t unit(save::Document& d,int mission,bool foreign=false){
    Army a{};a.id=uint16_t(300+d.armies.size());a.type=1;a.unitClass=1;a.owner=foreign?1:0;a.strength=3;a.unk_25=uint8_t(mission);a.territory.raw=a.dest.raw=a.origin.raw=1;
    auto& head=foreign?d.territories[0].data.foreignArmies:d.territories[0].data.armies;a.next.raw=head.raw;
    for(auto& old:d.armies)if(old.id==head.raw)old.prev.raw=a.id;head.raw=a.id;d.armies.push_back(a);return a.id;
}
std::vector<uint8_t> bytes(const save::Document& d){std::vector<uint8_t> out;save::Error e;ok(save::encode(d,out,e),e);
    for(const auto& t:d.territories){const auto* p=reinterpret_cast<const uint8_t*>(&t.data);out.insert(out.end(),p+kTerritorySavedBytes,p+sizeof(Territory));}return out;}
ConstructionOrderContext context(){ConstructionOrderContext c;SessionRng rng;save::Error e;ok(rng.initialize(54,e),e);c.ai.rng=c.events.rngBeforeEvents=c.log.rngAfterEvents=rng.snapshot();return c;}
ColonyMoraleMetrics query(const save::Document& d){const auto before=bytes(d);ColonyMoraleMetrics r;save::Error e;ok(colonyMoraleMetrics(d,1,r,e),e);require(bytes(d)==before && e.code==save::ErrorCode::None,"morale query is pure");return r;}
void components(){
    auto d=fixture();auto simple=query(*d);require(simple.baseline==50 && simple.total==50 && simple.value==50,"plain morale remains50");
    auto& t=d->territories[0].data;t.population=3000;t.unk_28[1]=3;t.exploredMask=1;t.materials[10]=3;d->players[0].taxLevel=3;
    const auto clone=building(*d,4,0,4);b(*d,clone).labor[1]=2;
    const auto hospital=building(*d,17,1,4);b(*d,hospital).labor[1]=3;
    const auto culture=building(*d,21,2);b(*d,culture).task[1]=7;b(*d,culture).labor[1]=5;
    unit(*d,10);unit(*d,10,true);unit(*d,13);d->options.allowAlliances=1;d->players[1].relations2[0]=2;
    auto r=query(*d);const std::array<int32_t,10> expected{50,-8,-3,-4,-2,-5,2,10,6,2};
    require(r.components==expected && r.total==48 && r.value==48,"all ten exact morale components: signed crowd, food, occupation, clone,tax,army,culture,art,hospital");
    building(*d,36,3,0);r=query(*d);require(r.components[3]==0 && r.total==52,"finished bunker suppresses occupation even inactive/unbuilt");
    d->options.fastProduction=1;r=query(*d);require(r.components[4]==-4 && r.components[9]==4 && r.components[7]==10,"fast doubles clone/hospital but culture task7 exempt");
    d->raceStats.v[27][2]=0;t.unk_28[1]=255;t.terrain=255;b(*d,hospital).labor[1]=-1;
    r=query(*d);require(r.baseline==80 && r.total==80 && r.value==80,"row27zero bypasses otherwise unsafe modifier domains entirely");
    d=fixture();d->territories[0].data.morale=-128;r=query(*d);require(r.total==-128 && r.value==-118,"final baseline+10 cap is AFTER0..100 clamp, can yield negative");
    d->territories[0].data.morale=50;d->territories[0].data.materials[10]=INT32_MAX;r=query(*d);require(r.components[8]==-2 && r.total==48,"art uses wrapped signed2*stock with only uppercap10");
    d=fixture();const auto id=building(*d,21,0);b(*d,id).task[1]=b(*d,id).task[2]=7;b(*d,id).labor[1]=b(*d,id).labor[2]=1;
    r=query(*d);require(r.components[7]==2,"culture counts FIRST matching task7 only, not both slots");
    b(*d,id).flags=4;r=query(*d);require(r.components[7]==0,"culture requires both Active and Built bits");
}
void garrisonAndLabor(){
    auto d=fixture();const auto id=unit(*d,13);save::Error e;int32_t value=99;ok(colonyRevoltStrength(*d,1,value,e),e);require(value==2,"normal laser attack is2");
    d->raceStats.v[29][2]=10;d->raceStats.v[33][2]=1;d->armies[0].moves=1;ok(colonyRevoltStrength(*d,1,value,e),e);require(value==8,"infantry order1 doublesbase2 then racial10 adds4");
    d->players[0].foodFlags=2;ok(colonyRevoltStrength(*d,1,value,e),e);require(value==4,"starvation halves attack after racial bonus");
    d->techs[46].knownMask=1;ok(colonyRevoltStrength(*d,1,value,e),e);require(value==0,"transporters fullmovement4 invalidates savedremaining3");
    d->armies[0].strength=4;ok(colonyRevoltStrength(*d,1,value,e),e);require(value==4,"fullmovement uses canonical type plus owner tech");
    d->armies[0].unitClass=9;ok(colonyRevoltStrength(*d,1,value,e),e);require(value==0,"storedclass9 veto preserved even when canonicalclass1");
    d->armies[0].unitClass=1;d->territories[0].data.terrain=0;ok(colonyRevoltStrength(*d,1,value,e),e);require(value==0,"mission13 requires current land");
    (void)id;d=fixture();d->territories[0].data.population=32767;d->territories[0].data.morale=127;LaborAvailability labor;
    ok(territoryLaborAvailability(*d,1,labor,e),e);require(labor.available==403 && labor.unavailable==0,"morale127 uses signed (100-130)/4=-7, percent123, pool403");
    d->territories[0].data.morale=-128;ok(territoryLaborAvailability(*d,1,labor,e),e);require(labor.available==1 && labor.unavailable==326,"negative morale pool has minimum1 when populationnonzero");
}
void passAndRollback(){
    auto d=fixture();d->players[0].taxLevel=0;d->territories[0].data.materials[10]=5;
    const auto original=bytes(*d);auto out=fixture();ColonyMoraleReport r;save::Error e;const auto c=context();
    ok(processColonyMorale(*d,c,*out,r,e),e);require(bytes(*d)==original && out->territories[0].data.morale==60 && r.territories[0].metrics.total==70 &&
        r.events.empty() && r.rngAfter==c.events.rngBeforeEvents && r.logAfter==c.log,"morale pass caps improvement+10 without events,RNG or source mutation");
    auto alias=std::make_unique<save::Document>(*d);ColonyMoraleReport rr;ok(processColonyMorale(*alias,c,*alias,rr,e),e);require(bytes(*alias)==bytes(*out) && rr==r,"morale alias output deterministic");
    auto mismatch=c;SessionRng different;ok(different.initialize(55,e),e);mismatch.ai.rng=different.snapshot();
    const auto beforeMismatch=bytes(*out);const auto reportBeforeMismatch=r;
    require(!processColonyMorale(*d,mismatch,*out,r,e) && e.code==save::ErrorCode::InvalidState &&
        bytes(*d)==original && bytes(*out)==beforeMismatch && r==reportBeforeMismatch,
        "no-event morale rejects divergent RNG continuations transactionally");
    d->territories[1].data.owner=0;d->territories[1].data.unk_28[1]=255;
    const auto before=bytes(*out);const auto previous=r;require(!processColonyMorale(*d,c,*out,r,e) && r==previous && bytes(*out)==before,"late malformed food leaves prior territory and report untouched");
    for(int owner:{-2,7}) {d->territories[0].data.owner=int8_t(owner);ColonyMoraleMetrics metrics;metrics.total=771;const auto old=metrics;
        require(!colonyMoraleMetrics(*d,1,metrics,e) && metrics==old,"invalid owner rejected before player indexing");}
    d=fixture();const auto hospital=building(*d,17,0);b(*d,hospital).labor[1]=-1;ColonyMoraleMetrics metrics;
    require(!colonyMoraleMetrics(*d,1,metrics,e),"negative hospital production index explicitly rejected");
    d->territories[0].data.owner=-1;ok(colonyMoraleMetrics(*d,1,metrics,e),e);require(metrics.value==100,"unowned query bypasses modifiers and returns100");
    auto malformed=c;malformed.events.rngBeforeEvents.format=2;malformed.ai.rng=malformed.events.rngBeforeEvents;
    require(!processColonyMorale(*d,malformed,*out,r,e),"malformed RNG is rejected even on no-event pass");
}
}
int main(){try{std::vector<uint8_t> g(sizeof(gs)),h(sizeof(gg));std::memcpy(g.data(),&gs,sizeof(gs));std::memcpy(h.data(),&gg,sizeof(gg));const auto seed=rtl::seed(),hi=rtl::seedHi();
    components();garrisonAndLabor();passAndRollback();require(!std::memcmp(g.data(),&gs,sizeof(gs)) && !std::memcmp(h.data(),&gg,sizeof(gg)) && seed==rtl::seed() && hi==rtl::seedHi(),"morale global isolation");
    std::cout<<"colony_morale: ten components, raw/clamped totals, military strength, labor, transaction and isolation passed\n";return 0;
}catch(const std::exception& e){std::cerr<<"colony_morale: "<<e.what()<<'\n';return 1;}}
