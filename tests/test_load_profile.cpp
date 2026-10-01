// Derived oracles from the original loaders, not a claim of full activation.
#include "game/load_profile.h"
#include "game/data_tables.h"
#include "game/save_files.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include <algorithm>
#include <array>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

namespace {
using namespace dl2;
using namespace dl2::simulation;
using save::Document;
namespace fs = std::filesystem;
void require(bool condition, const char* message) {
    if (!condition) throw std::runtime_error(message);
}
template<class T> void append(std::vector<uint8_t>& bytes, const T& value) {
    static_assert(std::is_trivially_copyable_v<T>);
    const auto* first = reinterpret_cast<const uint8_t*>(&value);
    bytes.insert(bytes.end(), first, first + sizeof(T));
}
template<class T> void appendVector(std::vector<uint8_t>& bytes, const std::vector<T>& values) {
    append(bytes, uint64_t(values.size()));
    for (const auto& value : values) append(bytes, value);
}
// Unlike encode(), this also observes unsaved territory tails and queue.next.
std::vector<uint8_t> snapshot(const Document& d) {
    std::vector<uint8_t> bytes;
    append(bytes,d.header); append(bytes,d.options); append(bytes,d.world); append(bytes,d.players);
    appendVector(bytes,d.localList); append(bytes,d.raceStats); append(bytes,d.techs);
    for (const auto& list : d.ministerJobs) appendVector(bytes,list);
    append(bytes,uint64_t(d.events.size()));
    for (const auto& event : d.events) { append(bytes,event.record); appendVector(bytes,event.text); }
    appendVector(bytes,d.tiles); appendVector(bytes,d.buildings); appendVector(bytes,d.armies);
    append(bytes,uint64_t(d.territories.size()));
    for (const auto& t : d.territories) {
        append(bytes,t.data);
        for (const auto& queue : t.queues) appendVector(bytes,queue);
    }
    append(bytes,d.jobs); append(bytes,d.aiWarMask); append(bytes,d.scratchJob1); append(bytes,d.scratchJob2);
    append(bytes,d.continents); append(bytes,d.randomEvents); append(bytes,d.scores);
    append(bytes,d.spies); append(bytes,d.blackMarket); appendVector(bytes,d.mapTerritories); appendVector(bytes,d.trailing);
    return bytes;
}
LoadCoreReport sentinel() {
    LoadCoreReport report;
    report.version=123; report.localPlayer=5; report.aiSkillBefore=-4; report.aiSkillAfter=8;
    report.campaignGoalMask=0xabcdefu; report.campaignProgress={17,18,19};
    report.playerTypesBefore.fill(9); report.playerTypesAfter.fill(8);
    report.discardedEvents=77; report.armyJobBindings=22; report.forbiddenResearchPlayers=0x66;
    return report;
}
std::unique_ptr<Document> fixture() {
    auto d=std::make_unique<Document>();
    std::memcpy(d->header.text,save::kHeaderText,sizeof(save::kHeaderText));
    d->header.version=kSaveVersion; d->header.minusOne=-1; d->header.pad[17]=0xab;
    d->options.numPlayers=4; d->options.localPlayer=0; d->options.turn=41; d->options.aiSkill=9;
    d->options.gameId=7151; d->options.gameSeed=0x12345678;
    d->options.victory=2; d->options.winCities=777; d->options.winShrines=888; d->options.winTurns=999;
    d->options.playersMask=0x80; d->options.eventLogFirst=17;
    d->options.campaignBytes[0]=7; d->options.campaignBytes[1]=129; d->options.campaignBytes[2]=255;
    d->world.width=d->world.height=1; d->world.numTerritories=1; d->world.rngSeed=0xf1234567;
    d->territories.resize(1); auto& t=d->territories[0].data;
    t.index=1; t.owner=0; t.terrain=1; t.population=1234; t.morale=91; t.knowledge=63;
    t.numTiles=1; t.tiles[0].raw=0;
    auto* raw=reinterpret_cast<uint8_t*>(&t);
    std::fill(raw+kTerritorySavedBytes,raw+sizeof(Territory),uint8_t(0xa5));
    d->tiles.resize(1); d->tiles[0].territory=1;
    for (size_t p=0;p<kMaxPlayers;++p) {
        auto& player=d->players[p]; player.index=uint8_t(p); player.race=int8_t(p);
        player.type=p<3?uint8_t(p+1):0; player.credits=int32_t(100+p); player.currentResearch=23;
        player.defeated=int32_t(9+p); player.aiVtbl[1]=0xaabbccdd; player.localList.raw=0xdead1200u+uint32_t(p);
        std::memset(player.name,int('A'+p),sizeof(player.name)); player.name[8]='\0';
        d->options.hasWon[p]=uint16_t(p+1); d->options.shrineTurns[p]=int32_t(100+p);
        d->ministerJobs[p].resize(1); d->ministerJobs[p][0].type=1;
    }
    // Dormant signed-byte sentinel: never interpreted as a live AI personality.
    d->players[4].type=255; d->players[4].race=-1; d->players[4].index=222;
    d->players[5].type=128; d->players[5].race=-1; d->players[5].index=223;
    d->localList={17,0xdeadbeef}; d->trailing={0xaa,0,0xff};
    d->events.resize(1); d->options.eventCount=1;
    d->events[0].record={12,4,0,99}; d->events[0].text={'a',0,'b',0xff};
    d->buildings.resize(3);
    constexpr uint16_t buildingIds[]{60000,7,32769};
    for (size_t i=0;i<3;++i) {
        auto& b=d->buildings[i]; b.id=buildingIds[i]; b.type=1; b.category=17;
        b.site=int8_t(i); b.territory=1; b.flags=6; b.labor[1]=int32_t(i+2); b.task[1]=20;
        b.taskData[3][10]=-77; t.sites[i].building.raw=b.id;
    }
    // Reverse historical chain: normalized order must be FILE order, not ID/list order.
    d->buildings[0].prev.raw=7;
    d->buildings[1].prev.raw=32769; d->buildings[1].next.raw=60000;
    d->buildings[2].next.raw=7;
    constexpr uint16_t armyIds[]{60000,42,555,65535};
    d->armies.resize(4);
    for (size_t i=0;i<4;++i) {
        auto& a=d->armies[i]; a.id=armyIds[i]; a.type=1; a.unitClass=1; a.owner=0; a.health=100;
        a.territory.raw=a.dest.raw=a.origin.raw=1; a.unk_44.raw=0xabcdef00u+uint32_t(i); a.job=-17;
        a.prev.raw=i?armyIds[i-1]:0; a.next.raw=i+1<4?armyIds[i+1]:0;
    }
    t.armies.raw=60000;
    d->jobs[0][0].armyIds[0]=d->jobs[0][0].armyIds[1]=60000;
    d->jobs[0][49].armyIds[0]=42; d->jobs[5][0].armyIds[0]=42;
    d->jobs[6][3].armyIds[2]=60000; d->jobs[6][49].armyIds[15]=65535;
    d->jobs[0][0].armies[0].raw=0xdeadbeef; d->jobs[0][0].armies[1].raw=0xffffffff;
    d->scratchJob1.armyIds[0]=65001; d->scratchJob1.armies[0].raw=0xcafe1234;
    d->scratchJob2.destination.raw=0xbadabc12;
    d->territories[0].queues[2].resize(1);
    d->territories[0].queues[2][0].unitType=1; d->territories[0].queues[2][0].count=3;
    d->territories[0].queues[2][0].next.raw=0x87654321;
    return d;
}
void expectedName(Player& player,const std::string& value) {
    // Only the prefix THROUGH its terminator is part of the original write.
    std::copy(value.begin(),value.end(),player.name); player.name[value.size()]=0;
}
void normalize(const Document& source,const LoadProfile& profile,Document& result,LoadCoreReport& report) {
    save::Error error{save::ErrorCode::Io,77,"old"};
    if (!normalizeLoadCore(source,profile,result,report,error)) throw std::runtime_error(error.message);
    require(error.code==save::ErrorCode::None && !error.offset && error.message.empty(),"load normalization did not clear error");
    require(save::validate(result,error),"normalized core document is structurally invalid");
}
void rejected(const Document& source,const LoadProfile& profile) {
    const auto sourceBefore=snapshot(source);
    auto destination=fixture(); destination->options.turn=90210;
    const auto destinationBefore=snapshot(*destination);
    auto report=sentinel(); const auto reportBefore=report; save::Error error;
    require(!normalizeLoadCore(source,profile,*destination,report,error),"unsafe load profile unexpectedly succeeded");
    require(error.code!=save::ErrorCode::None && !error.message.empty(),"load failure lacks a diagnostic");
    require(snapshot(source)==sourceBefore && snapshot(*destination)==destinationBefore && report==reportBefore,
            "load failure changed source, destination or report");
    auto inPlace=std::make_unique<Document>(source);
    require(!normalizeLoadCore(*inPlace,profile,*inPlace,report,error) && snapshot(*inPlace)==sourceBefore && report==reportBefore,
            "in-place load failure was not transactional");
}

void goldenCoreAndAliasing() {
    auto source=fixture(); const auto original=snapshot(*source);
    auto expected=std::make_unique<Document>(*source);
    LoadProfile profile; profile.localPlayerName="Local Oracle";
    expected->options.aiSkill=4;
    std::fill(std::begin(expected->options.hasWon),std::end(expected->options.hasWon),uint16_t(0));
    expectedName(expected->players[0],"Local Oracle");
    expectedName(expected->players[2],"Commander Jameson");
    expected->players[1].type=3; // Converted AFTER naming, retaining the old human name.
    for (auto& t:expected->territories) {
        auto* raw=reinterpret_cast<uint8_t*>(&t.data);
        std::fill(raw+kTerritorySavedBytes,raw+sizeof(Territory),uint8_t(0));
    }
    constexpr int16_t jobs[]{4,1,0,50};
    for (size_t i=0;i<4;++i) { expected->armies[i].job=jobs[i]; expected->armies[i].unk_44.raw=0; }
    for (size_t i=0;i<3;++i) {
        expected->buildings[i].prev.raw=i?expected->buildings[i-1].id:0;
        expected->buildings[i].next.raw=i+1<3?expected->buildings[i+1].id:0;
    }
    auto destination=fixture(); auto report=sentinel();
    normalize(*source,profile,*destination,report);
    require(snapshot(*destination)==snapshot(*expected),"load normalization changed bytes outside its documented core writes");
    require(snapshot(*source)==original,"load normalization mutated source");
    LoadCoreReport wanted;
    wanted.version=kSaveVersion; wanted.localPlayer=0; wanted.aiSkillBefore=9; wanted.aiSkillAfter=4;
    wanted.campaignProgress={7,129,255}; wanted.armyJobBindings=6;
    wanted.playerTypesBefore={1,2,3,0,255,128,0}; wanted.playerTypesAfter={1,3,3,0,255,128,0};
    require(report==wanted,"core normalization report differs from independent expected fields");
    require(destination->armies[0].job==4 && destination->armies[3].job==50,
            "high-bit global IDs must be zero-extended, and the last job reference must win");
    require(destination->players[1].name[0]=='B' && destination->players[1].type==3,
            "human-to-AI conversion must not retroactively rename a human record");
    auto inPlace=std::make_unique<Document>(*source); auto inPlaceReport=sentinel();
    normalize(*inPlace,profile,*inPlace,inPlaceReport);
    require(snapshot(*inPlace)==snapshot(*expected) && inPlaceReport==report,"in-place normalization differs from separate destination");
}

void profileAndVersionDomains() {
    auto source=fixture(); auto destination=fixture(); LoadCoreReport report; LoadProfile profile;
    for (const int skill:{std::numeric_limits<int>::min(),-1,0,1,4,5,std::numeric_limits<int>::max()}) {
        source->options.aiSkill=skill;
        normalize(*source,profile,*destination,report);
        require(report.aiSkillBefore==skill && report.aiSkillAfter==std::clamp(skill,0,4) &&
                destination->options.aiSkill==std::clamp(skill,0,4),"AI skill clamp must be [0,4] with signed bounds");
    }
    profile.localPlayer=2; profile.localPlayerName="Override";
    normalize(*source,profile,*destination,report);
    require(report.localPlayer==2 && destination->options.localPlayer==2 && destination->players[2].type==1 &&
            std::string(destination->players[2].name)=="Override" && destination->players[0].type==3 &&
            std::memcmp(destination->players[0].name,source->players[0].name,33)==0,
            "explicit local slot did not override file profile before names/types");
    source->options.localPlayer=1; profile.localPlayer=-1; profile.localPlayerName="";
    normalize(*source,profile,*destination,report);
    require(report.localPlayer==1 && destination->players[1].type==1 && destination->players[1].name[0]==0 &&
            destination->players[1].name[1]=='B',"file local slot or empty preference name semantics differ");
    profile.localPlayerName=std::string(32,'Z');
    normalize(*source,profile,*destination,report);
    require(destination->players[1].name[31]=='Z' && destination->players[1].name[32]==0,"32-byte local name boundary failed");
    profile.localPlayerName=std::string(33,'Z'); rejected(*source,profile);
    profile.localPlayerName=std::string("bad\0name",8); rejected(*source,profile);
    profile=LoadProfile{}; profile.localPlayer=-2; rejected(*source,profile);
    profile.localPlayer=7; rejected(*source,profile);
    profile.localPlayer=4; rejected(*source,profile); // Dormant invalid race/index must be checked when selected.
    profile=LoadProfile{};
    auto bad=fixture(); bad->players[0].race=-1; rejected(*bad,profile);
    bad=fixture(); bad->players[1].index=6; rejected(*bad,profile);
    bad=fixture(); bad->players[3].type=4; rejected(*bad,profile);
    bad=fixture(); bad->players[2].race=7; rejected(*bad,profile);
    for (const uint32_t version:{35u,36u,37u}) {
        source->header.version=version; rejected(*source,profile);
    }
    for (const uint32_t version:{0x26u,0x119u,0x11fu,kSaveVersion}) {
        source->header.version=version; normalize(*source,profile,*destination,report);
        const bool discard=version!=kSaveVersion;
        require(report.discardedEvents==(discard?1u:0u) && destination->events.size()==(discard?0u:1u) &&
                destination->options.eventCount==(discard?0:1),"version-specific stored-event discard differs");
        if (!discard) require(destination->events[0].text==source->events[0].text,"current-version binary event text changed");
    }
    bad=fixture(); bad->header.isMap=1; bad->mapTerritories.resize(1); rejected(*bad,profile);
    bad=fixture(); bad->world.width=0; rejected(*bad,profile);
    bad=fixture(); bad->jobs[0][0].armyIds[0]=60001; rejected(*bad,profile);
    bad=fixture(); bad->options.campaign=-1; rejected(*bad,profile);
    bad=fixture(); bad->options.campaign=43; rejected(*bad,profile);
}

void campaignOracles() {
    auto d=fixture(); auto out=fixture(); LoadCoreReport report; LoadProfile profile;
    for (int campaign=0;campaign<43;++campaign) {
        d->options.campaign=campaign;
        normalize(*d,profile,*out,report);
        require(report.campaignProgress==std::array<uint8_t,3>{7,129,255} &&
                out->options.campaign==campaign,"campaign boundary/progress bytes changed");
    }
    d->options.campaign=0;
    normalize(*d,profile,*out,report);
    require(out->options.victory==2 && out->options.winCities==777 && out->options.winShrines==888 &&
            out->options.winTurns==999 && report.campaignGoalMask==0,"noncampaign options overwritten by table row zero");
    d->options.campaign=42;
    normalize(*d,profile,*out,report);
    require(out->options.victory==2 && out->options.winShrines==2 && out->options.winTurns==10 &&
            out->options.winCities==777 && report.campaignGoalMask==((1u<<2)|(1u<<4)),"campaign42 complete table row differs");
    d->options.campaign=15;
    d->players[0].race=0; d->players[0].currentResearch=2;
    d->players[1].race=2; d->players[1].currentResearch=2;
    d->players[2].race=2; d->players[2].currentResearch=3;
    d->players[3].race=2; d->players[3].currentResearch=2; // Original loop includes an inactive player slot.
    normalize(*d,profile,*out,report);
    require(out->options.victory==0 && out->options.winCities==5 && out->options.winShrines==888 &&
            out->options.winTurns==999 && report.campaignGoalMask==((1u<<4)|(1u<<8)) &&
            report.forbiddenResearchPlayers==0x0a,"campaign15 forbids technology2 only for race2");
    // 00450000/00450150: type4 uses +04 as count and payload begins +08.
    // Row6's {4,7,0,{1,2,3,4,5,6,47}} means races0..6 then forbidden tech47.
    d->options.campaign=6; d->options.turn=1;
    for (size_t p=0;p<4;++p) { d->players[p].race=int8_t(p); d->players[p].currentResearch=47; }
    normalize(*d,profile,*out,report);
    require(report.forbiddenResearchPlayers==0x0f && report.campaignGoalMask==(1u<<4),
            "campaign6 race list/payload offset is misinterpreted");
    require(out->options.playersMask==0x87 && out->players[0].defeated==0 && out->players[1].defeated==0 &&
            out->players[2].defeated==0 && out->players[3].defeated==12,
            "first-turn campaign activation must use saved positive player types only");
    for (size_t p=0;p<kMaxPlayers;++p)
        require(out->players[p].currentResearch==d->players[p].currentResearch,"core stage applied research mask before derived/labor stage");
    require(std::memcmp(out->techs.data(),d->techs.data(),sizeof(d->techs))==0,"core research query modified technology data");
    d->options.turn=2;
    normalize(*d,profile,*out,report);
    require(out->options.playersMask==0x80 && out->players[0].defeated==9 && out->players[1].defeated==10,
            "campaign revival repeated after first turn");
}

std::vector<std::string> scenarioNames(const fs::path& path) {
    const auto size=fs::file_size(path); require(size>=4 && size<=save::kMaxFileBytes,"invalid corpus index size");
    std::ifstream in(path,std::ios::binary); uint8_t raw[4]{};
    require(bool(in.read(reinterpret_cast<char*>(raw),4)),"cannot read corpus index");
    const uint32_t n=uint32_t(raw[0])|(uint32_t(raw[1])<<8)|(uint32_t(raw[2])<<16)|(uint32_t(raw[3])<<24);
    require(n<=(size-4)/12,"truncated corpus index");
    std::vector<std::string> names;
    for(uint32_t i=0;i<n;++i) { char e[12]{}; require(bool(in.read(e,12)),"cannot read corpus entry"); names.emplace_back(e,std::find(e,e+8,'\0')); }
    return names;
}
void corpusOne(const Document& d) {
    const auto original=snapshot(d);
    if (d.header.version<0x26) { rejected(d,{}); return; }
    auto first=std::make_unique<Document>(), second=std::make_unique<Document>();
    LoadCoreReport a,b; normalize(d,{},*first,a); normalize(d,{},*second,b);
    require(snapshot(*first)==snapshot(*second) && a==b,"load core is not deterministic");
    require(snapshot(d)==original,"corpus source changed");
    for (const auto& t:first->territories) {
        const auto* raw=reinterpret_cast<const uint8_t*>(&t.data);
        require(std::all_of(raw+kTerritorySavedBytes,raw+sizeof(Territory),[](uint8_t v){return v==0;}),"corpus transient tail retained stale bytes");
    }
    for (size_t i=0;i<first->buildings.size();++i)
        require(first->buildings[i].prev.raw==(i?uint32_t(first->buildings[i-1].id):0u) &&
                first->buildings[i].next.raw==(i+1<first->buildings.size()?uint32_t(first->buildings[i+1].id):0u),"corpus active list is not file ordered");
}
void optionalCorpus(const fs::path& directory) {
    if(directory.empty() || !fs::is_regular_file(directory/"TUTORIAL.SAV")) {
        std::cout<<"load profile: optional corpus unavailable; synthetic tests ran\n"; return;
    }
    size_t count=0;
    for(const char* name:{"TUTORIAL.SAV","Saves/AUTOSAVE.SAV","Campaign/AUTOSAVE.CPN","Campaign/ChCht001.CPN"}) {
        if(!fs::is_regular_file(directory/name)) continue;
        auto d=std::make_unique<Document>(); save::Error error;
        if(!save::readDocument(directory/name,*d,error)) throw std::runtime_error(error.message);
        try { corpusOne(*d); } catch(const std::exception& ex) { throw std::runtime_error(std::string(name)+": "+ex.what()); }
        ++count;
    }
    if(fs::is_regular_file(directory/"LEVELS.HDX") && fs::is_regular_file(directory/"LEVELS.HDD"))
        for(const auto& name:scenarioNames(directory/"LEVELS.HDX")) {
            auto d=std::make_unique<Document>(); save::Error error;
            if(!save::readScenario(directory/"LEVELS",name,*d,error)) throw std::runtime_error(error.message);
            try { corpusOne(*d); } catch(const std::exception& ex) { throw std::runtime_error(name+": "+ex.what()); }
            ++count;
        }
    std::cout<<"load profile corpus: "<<count<<" documents, source preserved\n";
}
} // namespace

int main(int argc,char** argv) {
    try {
        rtl::srand(0xf1234567u); (void)rtl::lrand();
        const auto lo=rtl::seed(),hi=rtl::seedHi(); gg.rng2Seed=0xabcd0123;
        const auto globals=std::make_unique<GameGlobals>(gg);
        const auto game=std::make_unique<GameState>(gs);
        goldenCoreAndAliasing(); profileAndVersionDomains(); campaignOracles();
        optionalCorpus(argc>1?fs::path(argv[1]):fs::path{});
        require(rtl::seed()==lo && rtl::seedHi()==hi && std::memcmp(&gg,globals.get(),sizeof(gg))==0 &&
                std::memcmp(&gs,game.get(),sizeof(gs))==0,"load normalization modified global game/RNG state");
        std::cout<<"load profile tests passed\n"; return 0;
    } catch(const std::exception& ex) { std::cerr<<"load profile: "<<ex.what()<<'\n'; return 1; }
}
