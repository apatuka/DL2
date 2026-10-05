// Assembly-derived literal/calculated oracles; no execution of DEADLOCK.EXE.
#include "game/combat_auxiliaries.h"
#include "game/data_tables.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include "game/save_files.h"
#include <algorithm>
#include <bit>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <limits>
#include <memory>
#include <set>
#include <stdexcept>

namespace {
using namespace dl2;
using namespace dl2::simulation;
void require(bool v,const char* message) { if (!v) throw std::runtime_error(message); }
void ok(bool v,const save::Error& e) { if (!v) throw std::runtime_error(e.message); }
size_t cell(int x,int y) { return size_t((y+9)*36+x+9); }
std::unique_ptr<save::Document> fixture() {
    auto d=std::make_unique<save::Document>();
    std::memcpy(d->header.text,save::kHeaderText,sizeof(save::kHeaderText));
    d->header.version=kSaveVersion; d->world.width=2; d->world.height=1;
    d->world.numTerritories=2; d->tiles.resize(2); d->territories.resize(2);
    d->options.numPlayers=2; d->options.allowAlliances=1;
    for (size_t p=0;p<7;++p) {
        d->players[p].index=uint8_t(p); d->players[p].race=0; d->players[p].type=p?3:1;
        d->ministerJobs[p].resize(1);
    }
    for (size_t i=0;i<2;++i) {
        d->tiles[i].x=uint8_t(i); d->tiles[i].territory=int16_t(i+1);
        auto& t=d->territories[i].data; t.index=uint16_t(i+1); t.owner=int8_t(i);
        t.terrain=1; t.numTiles=1; t.secondTile=0; t.tiles[0].raw=uint32_t(i);
    }
    Building b{}; b.id=123; b.type=1; b.category=data::kBuildingTypes[1].category;
    b.flags=6; b.territory=1; b.site=0; b.labor[0]=1;
    d->territories[0].data.sites[0].building.raw=b.id; d->buildings.push_back(b);
    return d;
}
CombatPreparationState context() {
    CombatPreparationState s; s.currentBattle=CombatBattleRef{2}; s.battleCount=3;
    s.battles[2].core.territory=1; s.battles[2].core.defender=0; s.battles[2].core.approachMask=15;
    s.battles[2].preserved85=0xbb; s.battles[2].roads.fill(-33); s.battles[1].seed=1234567;
    s.structures[1199].parentBuildingId=123; s.structures[1199].x=9; s.structures[1199].y=9;
    s.structures[1199].preserved13=0xac; s.structureCursor=77; s.structureLimit=88;
    s.privateRng=1; s.turn=444; s.tick=-7; s.deadline=999; s.replayMode=1;
    s.warriors[0].preserved15=15; s.warriors[0].preserved1f=31; s.warriors[0].preserved31=49;
    s.warriors[0].preserved37=55; s.warriors[0].secondaryArmyId=54321;
    s.warriors[0].workNext=CombatantRef{654321}; return s;
}
std::vector<uint8_t> bytes(const save::Document& d) {
    std::vector<uint8_t> result; save::Error e; ok(save::encode(d,result,e),e); return result;
}
CombatAuxiliaryReport militia(const save::Document& d,const CombatPreparationState& s,
                             std::optional<CombatStructureRef> ref=CombatStructureRef{1199}) {
    const auto archive=bytes(d); const auto before=s; CombatAuxiliaryReport r;
    save::Error e{save::ErrorCode::Io,99,"old"}; ok(createCombatMilitia(d,ref,s,r,e),e);
    require(e.code==save::ErrorCode::None && e.offset==0 && e.message.empty() &&
            bytes(d)==archive && s==before,"militia mutated inputs or retained old Error"); return r;
}
CombatAuxiliaryReport mines(const save::Document& d,const CombatPreparationState& s,int8_t owner=0,uint32_t territory=1) {
    const auto archive=bytes(d); const auto before=s; CombatAuxiliaryReport r; save::Error e;
    ok(createCombatMines(d,owner,territory,s,r,e),e);
    require(bytes(d)==archive && s==before,"mines mutated inputs"); return r;
}
void spiralAndSyntheticParent() {
    auto d=fixture(); auto s=context(); d->buildings[0].labor[0]=9;
    const auto r=militia(*d,s);
    constexpr std::array<CombatAuxiliaryPosition,9> positions{{{9,9},{9,8},{8,8},{8,9},{8,10},{9,10},{10,10},{10,9},{10,8}}};
    require(r.laborBefore==9 && r.laborRemaining==0 && r.attempts.size()==9 && r.created.size()==9 &&
            r.occupancy.size()==9 && r.draws.size()==9,"militia counts or spiral stop differs");
    CombatCreationArmy synthetic; synthetic.type=23; synthetic.owner=0; synthetic.retreatPercent=100;
    require(r.syntheticArmy==synthetic,"militia synthetic Army has invented start/route/ID/parent data");
    uint32_t seed=1; auto expectedGrid=s.grid;
    constexpr uint8_t sides[]={2,8,1,4};
    for (size_t i=0;i<positions.size();++i) {
        const uint32_t before=seed; seed=seed*1103515245u+12345u; const uint32_t value=(seed>>16)%4u;
        require(r.draws[i]==CombatCreationDraw{before,seed,4,value},"militia changed exact generic-placement RNG order");
        const auto& a=r.attempts[i]; const auto& w=r.after.warriors[i]; const auto p=positions[i];
        require(a.created==CombatantRef{i} && r.created[i]==CombatantRef{i} && a.overridePosition==p &&
                a.outcome==CombatCreationOutcome::Created && a.drawBegin==i && a.drawCount==1 &&
                r.occupancy[i]==CombatAuxiliaryOccupancy{p,false,i},"physical creation/occupancy trace differs");
        require(w.x==p.x && w.currentX==p.x && w.initialX==p.x && w.y==p.y && w.currentY==p.y && w.initialY==p.y &&
                w.facing==sides[value] && w.initialFacing==w.facing && w.type==23 && w.currentOwner==0 &&
                std::get<CombatCreationArmy>(w.parent)==synthetic && w.retreatTerritory==0xffff,
                "militia failed to override all coordinates after real creation or changed its synthetic parent/facing");
        const auto next=i+1<positions.size()?std::optional<CombatantRef>{CombatantRef{i+1}}:std::nullopt;
        require(w.next==next,"militia physical list order differs");
        expectedGrid.flags[cell(p.x,p.y)]|=1;
    }
    require(r.after.grid==expectedGrid && r.after.privateRng==seed && r.after.warriorCursor==9 &&
            r.after.defenderCount==9 && r.after.attackerCount==0 && r.after.battles[2].core.playerMask==1,
            "militia left generic-position occupancy or failed side counter/RNG publication");
    require(r.after.structures==s.structures && r.after.structureCursor==77 && r.after.structureLimit==88 &&
            r.after.battles[1]==s.battles[1] && r.after.battles[2].roads==s.battles[2].roads &&
            r.after.turn==444 && r.after.tick==-7 && r.after.deadline==999 && r.after.replayMode==1 &&
            r.after.warriors[0].secondaryArmyId==s.warriors[0].secondaryArmyId &&
            r.after.warriors[0].workNext==s.warriors[0].workNext && r.after.warriors[0].preserved15==15 &&
            r.after.warriors[0].preserved1f==31 && r.after.warriors[0].preserved31==49 && r.after.warriors[0].preserved37==55,
            "auxiliary creation changed unrelated physical cells, clocks or stale slot data");
    // The caller tests occupancy bit0 only, not building/terrain bits or geometry.
    d->buildings[0].labor[0]=1; s.grid.flags[cell(9,9)]=1; s.grid.flags[cell(9,8)]=0xfe;
    const auto skipped=militia(*d,s);
    require(skipped.occupancy.size()==2 && skipped.occupancy[0].occupied && !skipped.occupancy[0].attemptIndex &&
            skipped.attempts[0].overridePosition==CombatAuxiliaryPosition{9,8} && skipped.after.grid.flags[cell(9,8)]==0xff,
            "occupied center consumed labor or other grid bits blocked militia override");
    s=context(); s.structures[1199].x=18; s.structures[1199].y=18;
    const auto outer=militia(*d,s);
    require(outer.attempts[0].overridePosition==CombatAuxiliaryPosition{18,18} && outer.after.grid.flags[cell(18,18)]==1,
            "initial physical occupancy query was incorrectly clamped to colony18x18");
}
void nullFullAndSignedLabor() {
    auto d=fixture(); auto s=context();
    s.battles[2].core.defender=0x100; // Caller truncates byte even for zero-labor calls.
    auto no=militia(*d,s,std::nullopt);
    require(no.after==s && no.syntheticArmy.owner==0 && no.attempts.empty() && no.occupancy.empty(),"null militia changed context");
    s.structures[1199].parentBuildingId.reset(); s.structures[1199].x=INT32_MIN;
    no=militia(*d,s);
    require(no.after==s && no.laborBefore==0 && no.occupancy.empty(),"null building parent dereferenced coordinates");
    s=context(); d->buildings[0].labor[0]=INT32_MAX; d->buildings[0].labor[1]=INT32_MAX; d->buildings[0].labor[2]=2;
    no=militia(*d,s); require(no.laborBefore==0 && no.after==s,"labor total did not wrap32 before zero predicate");
    std::fill_n(d->buildings[0].labor,5,0); d->buildings[0].labor[0]=-1;
    s.warriorCursor=s.warriorLimit; s.battles[2].core.first=CombatantRef{9000}; s.battles[2].core.last=CombatantRef{8000};
    no=militia(*d,s);
    require(no.laborBefore==-1 && no.laborRemaining==-325 && no.attempts.size()==324 && no.occupancy.size()==324 &&
            no.created.empty() && no.draws.empty() && no.after==s,"negative labor/full-pool null did not exhaust the physical spiral");
    std::set<std::pair<int32_t,int32_t>> visited;
    for (const auto& p:no.occupancy) visited.emplace(p.position.x,p.position.y);
    require(visited.size()==324 && *visited.begin()==std::pair<int32_t,int32_t>{0,0} &&
            *visited.rbegin()==std::pair<int32_t,int32_t>{17,17},"spiral failed to visit each colony cell exactly once");
    for (const auto& a:no.attempts) require(a.outcome==CombatCreationOutcome::PoolFull && !a.created,"native null became an error/creation");
    d->buildings[0].labor[0]=INT32_MIN; s.grid.flags.fill(1); s.grid.flags[cell(9,9)]=0;
    no=militia(*d,s);
    require(no.laborBefore==INT32_MIN && no.laborRemaining==INT32_MAX && no.attempts.size()==1 && no.draws.empty(),
            "labor decrement failed to wrap INT32_MIN or occupied cells consumed labor");
    // Physical last cell839 can allocate when the ring limit differs.
    s=context(); s.warriorCursor=839; s.warriorLimit=400; d->buildings[0].labor[0]=2;
    const auto wrapped=militia(*d,s);
    require(wrapped.created==std::vector<CombatantRef>{{839},{0}} && wrapped.after.warriorCursor==1 &&
            wrapped.after.battles[2].core.first==CombatantRef{839} && wrapped.after.warriors[839].next==CombatantRef{0},
            "militia physical Warrior ring did not wrap839 to0");
    s=context(); s.warriorCursor=838; d->buildings[0].labor[0]=3;
    const auto partial=militia(*d,s);
    require(partial.created.size()==1 && partial.attempts.size()==3 && partial.laborRemaining==0 && partial.draws.size()==1 &&
            partial.after.grid.flags[cell(9,9)]==1 && partial.after.grid.flags[cell(9,8)]==0 &&
            partial.attempts[1].outcome==CombatCreationOutcome::PoolFull && partial.attempts[2].outcome==CombatCreationOutcome::PoolFull,
            "partial full pool stopped labor progress or marked cells for failed allocations");
}
void twentyFourMines() {
    auto d=fixture(); auto s=context(); s.grid.flags.fill(0xff); s.grid.penalty.fill(0xa5);
    const auto r=mines(*d,s);
    constexpr std::array<CombatAuxiliaryPosition,24> positions{{{5,2},{11,9},{4,14},{8,5},{1,9},{2,6},{8,15},{10,5},
        {8,10},{5,13},{17,6},{8,0},{13,6},{11,8},{1,15},{0,3},{3,6},{6,4},{5,4},{7,13},{15,8},{17,12},{8,17},{2,10}}};
    constexpr std::array<size_t,24> draws{{8,2,2,8,2,2,16,6,2,8,2,2,6,2,6,10,2,10,12,10,2,4,2,26}};
    require(r.attempts.size()==24 && r.created.size()==24 && r.occupancy.empty() && r.draws.size()==152 &&
            r.after.privateRng==0xda2f5329 && r.after.grid==s.grid && r.after.attackerCount==0 && r.after.defenderCount==0 &&
            r.syntheticArmy.type==37 && r.syntheticArmy.owner==0 && r.syntheticArmy.turnStart==1 &&
            r.syntheticArmy.routeOrigin==1 && r.syntheticArmy.retreatPercent==100,"24-mine synthetic input/RNG/occupancy differs");
    size_t offset=0;
    for (size_t i=0;i<positions.size();++i) {
        const auto& w=r.after.warriors[i]; const auto& a=r.attempts[i];
        require(a.created==CombatantRef{i} && !a.overridePosition && a.drawBegin==offset && a.drawCount==draws[i] &&
                w.x==positions[i].x && w.y==positions[i].y && w.initialX==w.x && w.currentY==w.y &&
                std::get<CombatCreationArmy>(w.parent)==r.syntheticArmy,"mine literal positions or per-attempt draw partition differs");
        offset+=draws[i];
    }
    uint32_t seed=1;
    for (const auto& draw:r.draws) {
        const auto before=seed; seed=seed*1103515245u+12345u;
        require(draw==CombatCreationDraw{before,seed,36,(seed>>16)%36},"mine private LCG does not match full16-bit oracle");
    }
    d->territories[1].data.terrain=0;
    const auto sea=mines(*d,s,0,2);
    require(sea.syntheticArmy.type==38 && sea.syntheticArmy.turnStart==2 && sea.syntheticArmy.routeOrigin==2 &&
            sea.draws==r.draws && sea.after.grid==s.grid && sea.after.warriors[0].x==5,
            "mine type/source territory was inferred from the selected Battle");
    s.warriorCursor=s.warriorLimit; s.battles[2].core.first=CombatantRef{9999}; s.battles[2].core.last.reset();
    const auto full=mines(*d,s);
    require(full.attempts.size()==24 && full.created.empty() && full.draws.empty() && full.after==s,
            "full mine pool did not preserve all24 native-null calls");
    s=context(); s.warriorCursor=837;
    const auto partial=mines(*d,s);
    require(partial.created==std::vector<CombatantRef>{{837},{838}} && partial.attempts.size()==24 && partial.draws.size()==10 &&
            partial.after.warriorCursor==839 && partial.attempts[2].outcome==CombatCreationOutcome::PoolFull,
            "mine partial allocation incorrectly stopped subsequent calls or consumed null RNG");
}
void atomicityAndAlias() {
    auto d=fixture(); auto s=context(); save::Error e;
    auto r=militia(*d,s); const auto expected=militia(*d,r.after);
    ok(createCombatMilitia(*d,CombatStructureRef{1199},r.after,r,e),e);
    require(r==expected,"militia context aliases report atomically");
    auto mineReport=mines(*d,s); const auto next=mines(*d,mineReport.after);
    ok(createCombatMines(*d,0,1,mineReport.after,mineReport,e),e);
    require(mineReport==next,"mine context aliases report atomically");
    const auto keep=r; const auto archive=bytes(*d);
    auto bad=s; bad.maximumRandomDraws=10; // first six mines succeed, seventh needs16 draws.
    require(!createCombatMines(*d,0,1,bad,r,e) && e.code==save::ErrorCode::Limit && r==keep && bytes(*d)==archive,
            "late seventh-mine draw failure leaked completed creations or RNG");
    d->buildings[0].labor[0]=3; bad=s; bad.battles[2].core.approachMask=1; bad.maximumRandomDraws=1;
    // Seed1 draws side1 twice; the third draw chooses side8 and exhausts the cap.
    require(!createCombatMilitia(*d,CombatStructureRef{1199},bad,r,e) && e.code==save::ErrorCode::Limit && r==keep,
            "late third militia retry failure leaked preceding relocated warriors");
    bad=s; bad.structures[1199].parentBuildingId=99999;
    require(!createCombatMilitia(*d,CombatStructureRef{1199},bad,r,e) && r==keep,"unknown live building was silently treated as null");
    bad=s; bad.currentBattle.reset();
    require(!createCombatMilitia(*d,std::nullopt,bad,r,e) && r==keep,"null militia ignored mandatory selected Battle read");
    bad=s; bad.structures.pop_back();
    require(!createCombatMilitia(*d,std::nullopt,bad,r,e) && r==keep,"incorrect physical pool shape succeeded");
    require(!createCombatMilitia(*d,CombatStructureRef{1200},s,r,e) && r==keep,"structure index1200 resolved outside pool");
    require(!createCombatMines(*d,0,0,s,r,e) && r==keep,"mine territory sentinel0 was invented");
    d->buildings[0].labor[0]=-1; bad=s; bad.warriorCursor=bad.warriorLimit;
    bad.structures[1199].x=-9; bad.structures[1199].y=26;
    require(!createCombatMilitia(*d,CombatStructureRef{1199},bad,r,e) && r==keep,
            "unbacked final spiral column was silently clamped or changed output");
}
void corpus(const std::filesystem::path& directory) {
    if (directory.empty() || !std::filesystem::is_regular_file(directory/"TUTORIAL.SAV")) {
        std::cout<<"Combat auxiliaries: optional corpus unavailable\n"; return;
    }
    auto d=std::make_unique<save::Document>(); save::Error e; ok(save::readDocument(directory/"TUTORIAL.SAV",*d,e),e);
    const auto archive=bytes(*d); size_t checked=0;
    for (const auto& b:d->buildings) {
        if (b.territory<1 || size_t(b.territory)>d->territories.size()) continue;
        const auto& t=d->territories[size_t(b.territory)-1].data;
        if (t.owner<0 || t.owner>=7) continue;
        auto s=context(); s.battles[2].core.territory=uint32_t(b.territory); s.battles[2].core.defender=t.owner;
        s.structures[1199].parentBuildingId=b.id;
        const auto r=militia(*d,s); int32_t total=0;
        for (int32_t value:b.labor) total=std::bit_cast<int32_t>(uint32_t(total)+uint32_t(value));
        require(r.laborBefore==total && r.created.size()==r.attempts.size() &&
                r.after.defenderCount==r.created.size(),"corpus militia lost labor or creation counters");
        const auto m=mines(*d,s,t.owner,uint32_t(b.territory));
        require(m.created.size()==24 && m.after.grid==s.grid,"corpus mines failed complete batch");
        ++checked; if (checked==3) break;
    }
    require(checked>0 && bytes(*d)==archive,"corpus auxiliary checks unavailable or changed original document");
    std::cout<<"Combat auxiliaries corpus: "<<checked<<" building militia/mine batches\n";
}
} // namespace
int main(int argc,char** argv) {
    try {
        rtl::srand(0xf1234567); (void)rtl::lrand(); gg.rng2Seed=0xabcdef01;
        const auto low=rtl::seed(),high=rtl::seedHi(); const auto globals=std::make_unique<GameGlobals>(gg);
        const auto state=std::make_unique<GameState>(gs);
        spiralAndSyntheticParent(); nullFullAndSignedLabor(); twentyFourMines(); atomicityAndAlias();
        corpus(argc>1?std::filesystem::path(argv[1]):std::filesystem::path{});
        require(rtl::seed()==low && rtl::seedHi()==high && std::memcmp(&gg,globals.get(),sizeof(gg))==0 &&
                std::memcmp(&gs,state.get(),sizeof(gs))==0,"auxiliaries changed global state/RNG");
        std::cout<<"Combat auxiliaries tests passed\n"; return 0;
    } catch (const std::exception& e) { std::cerr<<"Combat auxiliaries: "<<e.what()<<'\n'; return 1; }
}
