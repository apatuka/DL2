#include "game/population_growth.h"
#include "game/data_tables.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include <cstring>
#include <iostream>
#include <memory>
#include <stdexcept>
namespace {
using namespace dl2; using namespace dl2::simulation;
void require(bool v,const char* text) { if (!v) throw std::runtime_error(text); }
void ok(bool v,const save::Error& e) { if (!v) throw std::runtime_error(e.message); }
std::unique_ptr<save::Document> fixture() {
    auto d=std::make_unique<save::Document>(); std::memcpy(d->header.text,save::kHeaderText,sizeof(save::kHeaderText)); d->header.version=kSaveVersion;
    d->world.width=2;d->world.height=1;d->world.numTerritories=2;d->territories.resize(2);d->tiles.resize(2);
    d->options.numPlayers=2;d->options.localPlayer=0;d->options.turn=18;
    for (size_t p=0;p<7;++p) { d->players[p].index=uint8_t(p);d->players[p].race=2;d->players[p].type=p?3:1;
        d->ministerJobs[p].resize(1);d->ministerJobs[p][0].type=1; for (auto& row:d->raceStats.v) row[p]=100; }
    for (size_t i=0;i<2;++i) {
        auto& t=d->territories[i].data;t.index=uint16_t(i+1);t.owner=i?-1:0;t.population=1000;t.morale=100;t.terrain=1;t.numTiles=1;t.tiles[0].raw=uint32_t(i);
        std::memcpy(t.name,"Alpha",6);t.unk_32=77;t.production[1]=123;t.materials[1]=321;
        d->tiles[i].x=uint8_t(i);d->tiles[i].territory=int16_t(i+1);
        for (int s=0;s<36;++s) {t.sites[s].unk_00=uint16_t(s%6+256*(s/6));t.sites[s].terrainFlags=1;}
    }
    return d;
}
void housing(save::Document& d,int territory=1) {
    Building b{};b.id=uint16_t(d.buildings.size()+1);b.type=3;b.category=17;b.race=2;b.site=35;b.territory=int16_t(territory);b.flags=6;b.task[1]=20;
    if (!d.buildings.empty()) {b.prev.raw=d.buildings.back().id;d.buildings.back().next.raw=b.id;}
    d.territories[size_t(territory-1)].data.sites[35].building.raw=b.id;d.buildings.push_back(b);
}
PopulationGrowthContext context() {
    PopulationGrowthContext c;SessionRng rng;save::Error e;ok(rng.initialize(54,e),e);
    c.effects.ai.rng=c.effects.events.rngBeforeEvents=c.effects.log.rngAfterEvents=rng.snapshot();return c;
}
std::vector<uint8_t> bytes(const save::Document& d) {
    std::vector<uint8_t> out;save::Error e;ok(save::encode(d,out,e),e);
    for (const auto& t:d.territories) {const auto* p=reinterpret_cast<const uint8_t*>(&t.data);out.insert(out.end(),p+kTerritorySavedBytes,p+sizeof(Territory));}return out;
}
struct Output {std::unique_ptr<save::Document> d=std::make_unique<save::Document>();PopulationGrowthReport report;};
Output run(const save::Document& d,PopulationGrowthContext c=context()) {
    const auto before=bytes(d);Output out;save::Error e{save::ErrorCode::Io,7,"old"};ok(processPopulationGrowth(d,c,*out.d,out.report,e),e);
    require(bytes(d)==before && e.code==save::ErrorCode::None && e.message.empty(),"growth preserves source and clears error");
    auto alias=std::make_unique<save::Document>(d);PopulationGrowthReport again;ok(processPopulationGrowth(*alias,c,*alias,again,e),e);
    require(bytes(*alias)==bytes(*out.d) && again==out.report,"growth alias and report deterministic");return out;
}
void deny(const save::Document& d,PopulationGrowthContext c=context()) {
    const auto original=bytes(d);auto out=fixture();const auto old=bytes(*out);PopulationGrowthReport r;r.events.resize(1);const auto before=r;save::Error e;
    require(!processPopulationGrowth(d,c,*out,r,e) && e.code!=save::ErrorCode::None && !e.message.empty(),"growth unsafe domain explicit");
    require(bytes(d)==original && bytes(*out)==old && r==before,"growth failure rollback includes previous territories/effects");
}
void numeric() {
    auto d=fixture();housing(*d);auto out=run(*d);
    const auto& c=out.report.territories[0];
    require(c.before==1000 && c.after==1080 && c.growthPercent==8 && c.rateAfter==8 && c.laborTrigger==-890 && !c.balancedLabor,
            "1000/1500: density66/2=33,percent8,next1080; ORIGINAL unusual labor trigger skips rebalance");
    require(out.d->buildings[0].labor[1]==0 && out.d->territories[0].data.production[1]==123 && out.d->territories[0].data.materials[1]==321 && out.d->options.turn==18,
            "growth does not implicitly allocate normal new workers, reset scratch, consume food or advance turn");
    d->territories[0].data.population=50;out=run(*d);
    require(out.report.territories[0].after==75 && out.report.territories[0].balancedLabor && out.d->buildings[0].labor[1]==1 && out.report.territories[0].rateAfter==50,
            "small colony adds20 only after positive growth, calls no-target RedistributeLabor->Balance");
    d->territories[0].data.population=1;d->territories[0].data.unk_28[1]=1;out=run(*d);
    require(out.report.territories[0].growthPercent==-10 && out.report.territories[0].after==26 && out.report.territories[0].rateAfter==2500,
            "starvation -10 percent truncates to same1 then original unconditional stagnation +25");
    d->territories[0].data.unk_28[1]=0;d->territories[0].data.population=100;d->raceStats.v[25][2]=0;out=run(*d);
    require(out.report.territories[0].after==125 && out.report.territories[0].balancedLabor,"zero growth still stagnation+25 and positive odd labor trigger");
    d->territories[0].data.population=101;out=run(*d);
    require(out.report.territories[0].after==126 && !out.report.territories[0].balancedLabor,"old101 crosses unusual rebalance boundary exactly");
    d->raceStats.v[25][2]=100;d->territories[0].data.population=1000;d->options.fastProduction=1;out=run(*d);
    require(out.report.territories[0].growthPercent==16 && out.report.territories[0].after==1160,"fastProduction doubles rounded integer percentage");
}
void limitsAndEvents() {
    auto d=fixture();housing(*d);d->territories[0].data.population=1600;auto out=run(*d);
    require(out.report.territories[0].after==1500 && out.report.events.size()==1 && out.report.events[0].type==53 && out.report.logAfter.entries[0].player==1,
            "overhousing population is reduced and Ex53 retains territory payload");
    d->territories[0].data.population=590;
    for (int s=0;s<36;++s) d->territories[0].data.sites[s].terrainFlags=s<4?1:5;
    out=run(*d);require(out.report.territories[0].limits.land==600 && out.report.territories[0].after==600 && out.report.events[0].type==52,
            "land ceiling takes notice52 precedence over housing notice53");
    d=fixture();housing(*d);d->territories[1].data.owner=1;housing(*d,2);auto c=context();c.campaignFlags=1u<<10;out=run(*d,c);
    require(out.report.territories[0].campaignSkipped && out.d->territories[0].data.population==1000 && out.d->territories[0].data.unk_32==77 &&
            out.d->territories[1].data.population==1080,"campaign bit10 inhibits only local owner, including growth-rate rewrite");
    d->territories[1].data.population=1600;deny(*d); // T1 changes first; missing AI53 rolls entire sweep back.
    AiSession ai;save::Error e;ok(ai.initializeAfterLoad(*d,e),e);c=context();c.effects.aiSession=&ai;out=run(*d,c);
    require(out.report.events[0].aiDispatched && out.report.events[0].aiReport.contextAfter.rng==out.report.rngAfter,"AI capacity notice uses actual handler and continuation");
    d=fixture();d->territories[0].data.population=-1;deny(*d); // max0 with negative old reaches IDIV0.
    for (int owner:{-2,7}) {d->territories[0].data.owner=int8_t(owner);deny(*d);}
    d=fixture();housing(*d);c=context();
    SessionRng different;ok(different.initialize(55,e),e);c.effects.ai.rng=different.snapshot();
    deny(*d,c); // Valid no-event growth must not silently discard the AI continuation.
    c=context();c.effects.events.rngBeforeEvents.format=99;c.effects.ai.rng=c.effects.events.rngBeforeEvents;deny(*d,c);
}
}
int main() {try {
    std::vector<uint8_t> g(sizeof(gs)),h(sizeof(gg));std::memcpy(g.data(),&gs,sizeof(gs));std::memcpy(h.data(),&gg,sizeof(gg));const auto s=rtl::seed(),hi=rtl::seedHi();
    numeric();limitsAndEvents();require(!std::memcmp(g.data(),&gs,sizeof(gs)) && !std::memcmp(h.data(),&gg,sizeof(gg)) && s==rtl::seed() && hi==rtl::seedHi(),"growth global isolation");
    std::cout<<"population_growth: original arithmetic/labor trigger, capacity, notices, campaign and rollback passed\n";return 0;
}catch(const std::exception& e){std::cerr<<"population_growth: "<<e.what()<<'\n';return 1;}}
