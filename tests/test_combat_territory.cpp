// Assembly-derived branch and ordering oracles. The original EXE is not run.
#include "game/combat_territory.h"
#include "game/combat_defense.h"
#include "game/data_tables.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include "game/save_files.h"
#include <algorithm>
#include <bit>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <memory>
#include <stdexcept>

namespace {
using namespace dl2;
using namespace dl2::simulation;
void require(bool value,const char* message) { if (!value) throw std::runtime_error(message); }
void ok(bool value,const save::Error& e) { if (!value) throw std::runtime_error(e.message); }
size_t cell(int x,int y) { return size_t((y+9)*36+x+9); }
std::unique_ptr<save::Document> fixture() {
    auto d=std::make_unique<save::Document>();
    std::memcpy(d->header.text,save::kHeaderText,sizeof(save::kHeaderText)); d->header.version=kSaveVersion;
    d->world.width=3; d->world.height=1; d->world.numTerritories=3; d->tiles.resize(3); d->territories.resize(3);
    d->options.numPlayers=7; d->options.allowAlliances=1; d->options.turn=41;
    for (size_t p=0;p<7;++p) {
        d->players[p].index=uint8_t(p); d->players[p].type=p?3:1; d->players[p].race=0;
        d->options.playerSkill[p]=2; d->ministerJobs[p].resize(1);
    }
    for (size_t i=0;i<3;++i) {
        d->tiles[i].x=uint8_t(i); d->tiles[i].territory=int16_t(i+1);
        auto& t=d->territories[i].data; t.index=uint16_t(i+1); t.owner=int8_t(i); t.terrain=1;
        t.numTiles=1; t.secondTile=0; t.tiles[0].raw=uint32_t(i);
        for (size_t s=0;s<36;++s) {
            t.sites[s].unk_00=uint16_t(s%6+((s/6)<<8)); t.sites[s].unk_18[0]=0xaa; t.sites[s].unk_18[1]=0x55;
        }
    }
    d->trailing={0x12,0xab,0x00,0xef}; return d;
}
Army& army(save::Document& d,uint32_t id) {
    for (auto& a:d.armies) if (a.id==id) return a; throw std::runtime_error("fixture Army missing");
}
void unit(save::Document& d,uint16_t id,uint8_t type,int8_t owner,uint8_t mission=0) {
    Army a{}; a.id=id; a.type=type; a.unitClass=255; a.owner=owner; a.health=100; a.unk_25=mission;
    a.territory.raw=a.origin.raw=owner==0?1:2; a.dest.raw=1;
    auto& t=d.territories[0].data; auto& head=owner==t.owner?t.armies:t.foreignArmies;
    a.next.raw=head.raw; if (head.raw) army(d,head.raw).prev.raw=id;
    head.raw=id; d.armies.push_back(a);
}
void building(save::Document& d,uint16_t id,uint8_t type,int site,int labor=0) {
    Building b{}; b.id=id; b.type=type; b.category=data::kBuildingTypes[type].category; b.race=3;
    b.flags=6; b.site=int8_t(site); b.territory=1; b.labor[0]=labor;
    d.territories[0].data.sites[size_t(site)].building.raw=id; d.buildings.push_back(b);
}
CombatTerritoryContext context() {
    CombatTerritoryContext c; c.preparation.battles[0].seed=1; c.preparation.battles[1].seed=54321;
    c.preparation.selectedTerrainTerritory=999; c.preparation.privateRng=777; c.preparation.grid.penalty.fill(99);
    c.preparation.turn=41; c.militiaPopulation=-887; return c;
}
std::vector<uint8_t> bytes(const save::Document& d) {
    std::vector<uint8_t> out; save::Error e; ok(save::encode(d,out,e),e);
    for (const auto& t:d.territories) {
        const auto* p=reinterpret_cast<const uint8_t*>(&t.data);
        out.insert(out.end(),p+kTerritorySavedBytes,p+sizeof(Territory));
    }
    return out;
}
struct Outcome { std::unique_ptr<save::Document> document=std::make_unique<save::Document>(); CombatTerritoryReport report; };
Outcome run(const save::Document& d,const CombatTerritoryContext& c=context(),bool wrapper=true) {
    const auto archive=bytes(d); const auto before=c; Outcome out; save::Error e{save::ErrorCode::Io,33,"previous"};
    const auto f=wrapper?prepareSelectedTerritoryCombat:prepareTerritoryCombat;
    ok(f(d,1,c,*out.document,out.report,e),e);
    require(bytes(d)==archive && c==before,"territorial preparation changed caller document/context");
    require(e.code==save::ErrorCode::None && e.offset==0 && e.message.empty(),"territorial success did not clear error");
    return out;
}
void enumeratorAndCategory() {
    auto d=fixture(); unit(*d,30,1,1); unit(*d,10,1,1); unit(*d,20,1,1);
    const auto head=d->territories[0].data.foreignArmies.raw; save::Error e; std::optional<uint32_t> id=999;
    ok(nextCombatArmyById(*d,head,-1,id,e),e); require(id==10,"enumerator returned list head instead of minimum ID");
    ok(nextCombatArmyById(*d,head,10,id,e),e); require(id==20,"enumerator threshold is not strict");
    ok(nextCombatArmyById(*d,head,30,id,e),e); require(!id,"enumerator did not return native NULL at end");
    ok(nextCombatArmyById(*d,0,-1,id,e),e); require(!id,"NULL head enumerated unrelated Army pool");
    id=123; require(!nextCombatArmyById(*d,999,-1,id,e) && id==123,"unresolved head changed prior result");
    building(*d,100,1,1); building(*d,101,1,2); building(*d,102,1,3);
    d->buildings[0].category=255; d->buildings[1].category=d->buildings[2].category=19;
    d->buildings[1].turnsLeft=-1; int32_t site=777;
    ok(findActiveCombatBuildingCategory(*d,1,-1,0,site,e),e); require(site==1,"category was not signed stored byte");
    ok(findActiveCombatBuildingCategory(*d,1,19,0,site,e),e); require(site==3,"negative construction counter treated as completed");
    d->buildings[1].turnsLeft=0; d->buildings[1].flags=2;
    ok(findActiveCombatBuildingCategory(*d,1,19,0,site,e),e); require(site==3,"inactive building treated as active");
    d->buildings[1].flags=4;
    ok(findActiveCombatBuildingCategory(*d,1,19,2,site,e),e); require(site==2,"category start was not inclusive");
    ok(findActiveCombatBuildingCategory(*d,1,19,36,site,e),e); require(site==-1,"end start did not return native-1");
    site=777; require(!findActiveCombatBuildingCategory(*d,1,19,-1,site,e) && site==777,"negative start did not reject atomically");
}
void siteProjection() {
    auto d=fixture(); building(*d,100,1,5); building(*d,101,5,24); building(*d,102,1,1);
    auto& t=d->territories[0].data; t.sites[0].terrainFlags=0x4000; t.sites[2].terrainFlags=0x4100;
    t.sites[3].terrainFlags=0x6000; building(*d,103,1,27);
    save::Error e; auto out=std::make_unique<save::Document>(); std::vector<CombatSiteProjection> report;
    const auto original=bytes(*d); ok(rebuildCombatSiteProjection(*d,1,*out,report,e),e);
    require(report.size()==36 && report[0].sourceBuilding==100 && report[0].afterType==1 && report[0].afterRace==3,
            "size2 socket did not copy exact site+5 binding");
    require(report[3].sourceBuilding==103 && report[3].afterType==1 && report[24].afterType==0 && report[24].afterRace==0x55,
            "size5 socket or direct non-size1 projection differs");
    require(report[2].afterType==0 && report[2].afterRace==0x55 && !report[2].sourceBuilding &&
            report[1].sourceBuilding==102 && report[1].afterType==1,"type-only clearing or size1 direct binding differs");
    require(bytes(*d)==original,"site projection changed its source");
    const auto keep=bytes(*out); const auto previous=report;
    t.sites[35].terrainFlags=0x4000;
    require(!rebuildCombatSiteProjection(*d,1,*out,report,e) && report==previous && bytes(*out)==keep,
            "late beyond-territory socket leaked earlier cache writes");
    t.sites[35].terrainFlags=0; t.sites[2].terrainFlags=0x4000; // site7 has no source.
    require(!rebuildCombatSiteProjection(*d,1,*out,report,e) && report==previous && bytes(*out)==keep,
            "missing socket source was silently replaced by an empty cache");
    t.sites[2].terrainFlags=0x4100; ok(rebuildCombatSiteProjection(*d,1,*d,report,e),e);
    require(bytes(*d)==keep && report==previous,"site source/destination alias changed result");
}
void selectionGates() {
    auto d=fixture(); auto c=context(); c.preparation.warriors.clear(); c.preparation.battleCount=-123;
    d->territories[0].data.sites[35].terrainFlags=0x4000;
    auto no=run(*d,c);
    require(!no.report.selection.prepared && no.report.contextAfter==c && bytes(*no.document)==bytes(*d) &&
            no.report.siteProjection.empty() && !no.report.battle,"no-battle branch validated/rewrote unused state");
    d=fixture(); d->territories[0].data.owner=-1; unit(*d,1,9,1);
    no=run(*d); require(!no.report.selection.prepared && no.report.selection.airOnly && no.report.selection.attacker==1,
            "air-only attack without defending force invented battle");
    army(*d,1).type=16;
    auto missile=run(*d);
    require(missile.report.selection.prepared && missile.report.selection.warheadOwner==1 &&
            missile.report.selection.opponent==-1 && missile.report.contextAfter.preparation.battles[0].core.defender==-1,
            "lone warhead did not force preparation against neutral owner");
    unit(*d,2,1,1,1); army(*d,1).cargo[0].raw=2;
    no=run(*d); require(!no.report.selection.prepared && no.report.selection.warheadOwner==-1 && no.report.selection.airOnly,
            "nonzero Army+48 did not divert warhead into primary attacker branch");
    d=fixture(); d->territories[0].data.population=1; unit(*d,1,1,1);
    d->players[1].relations[0]=2;
    no=run(*d); require(!no.report.selection.prepared && no.report.selection.foreignCounts[1]==1,
            "friendly attacker was selected or count was taken after pact filtering");
    d->players[1].relations[0]=0; d->players[0].relations[1]=2;
    auto reverse=run(*d); require(reverse.report.selection.prepared && reverse.report.selection.opponent==0,
            "reverse military pact incorrectly suppressed directional selection");
    d=fixture(); unit(*d,30,1,1); unit(*d,10,1,2);
    auto pair=run(*d); require(pair.report.selection.attacker==2 && pair.report.selection.opponent==1 &&
            pair.report.contextAfter.preparation.battles[0].core.defender==0 &&
            pair.report.contextAfter.preparation.battles[0].attacker==2,"last ordered hostile pair or actual Battle defender differs");
    d=fixture(); d->territories[0].data.population=1; unit(*d,30,1,2); unit(*d,10,1,1);
    auto order=run(*d); require(order.report.selection.attacker==2 && order.report.armies[0].armyId==10 &&
            order.report.armies[1].armyId==30,"selection linked order was confused with creation ascending-ID order");
    d=fixture(); d->territories[0].data.owner=-1; d->territories[0].data.exploredMask=(1u<<2)|(1u<<6)|(1u<<31);
    unit(*d,1,1,1); auto mines=run(*d);
    require(mines.report.selection.prepared && mines.report.selection.mineOwner==6 && !mines.report.selection.minesFriendly &&
            mines.report.selection.opponent==-1 && mines.report.auxiliaries.size()==1 && mines.report.auxiliaries[0].mines &&
            mines.report.auxiliaries[0].attempts.size()==24,"last mine-owner bit or ground/mine-only gate differs");
    d->players[6].relations[1]=2;
    no=run(*d); require(!no.report.selection.prepared && no.report.selection.minesFriendly,"mine pact direction was reversed");
}
std::unique_ptr<save::Document> populated() {
    auto d=fixture(); d->territories[0].data.population=17;
    unit(*d,30,9,1); unit(*d,10,1,1); unit(*d,40,1,0,1); unit(*d,20,1,0);
    building(*d,900,29,5); building(*d,902,1,2,1); return d;
}
void compositionAndReplaySeed() {
    auto d=populated(); auto c=context(); const auto original=bytes(*d); auto out=run(*d,c);
    const auto& r=out.report; const auto& state=r.contextAfter.preparation;
    require(r.selection.prepared && r.battle==CombatBattleRef{0} && state.battleCount==1 &&
            state.selectedTerrainTerritory==999 && r.contextAfter.militiaPopulation==0 && r.defenseRebuilt,
            "composed Battle or selected-territory restoration differs");
    require(r.armies.size()==4 && r.armies[0].armyId==10 && r.armies[1].armyId==30 && r.armies[2].armyId==20 &&
            r.armies[3].armyId==40 && r.armies[0].foreign && !r.armies[2].foreign &&
            r.armies[3].outcome==CombatCreationOutcome::MissionExcluded,"Army enumeration/order or native null outcome differs");
    require(r.buildings.size()==2 && r.buildings[0].buildingId==902 && r.buildings[1].buildingId==900 &&
            r.buildings[0].structure==CombatStructureRef{0} && r.buildings[1].warrior==CombatantRef{2},
            "buildings did not execute by site between foreign and own Army passes");
    require(state.warriorCursor==5 && std::get<CombatArmyParent>(state.warriors[0].parent).id==10 &&
            std::get<CombatArmyParent>(state.warriors[1].parent).id==30 &&
            std::get<CombatBuildingParent>(state.warriors[2].parent).id==900 &&
            std::get<CombatArmyParent>(state.warriors[3].parent).id==20 && state.warriors[4].type==23,
            "participant pool order differs from foreign/building/own/militia sequence");
    require(r.auxiliaries.size()==1 && !r.auxiliaries[0].mines && r.auxiliaries[0].structure==CombatStructureRef{0} &&
            r.auxiliaries[0].laborBefore==1 && r.auxiliaries[0].laborRemaining==0 && r.auxiliaries[0].attempts.size()==1,
            "structure-linked militia did not use the real labor/placement leaf");
    require(state.grid.penalty[cell(16,1)]==10 && state.battles[1]==c.preparation.battles[1] &&
            out.document->buildings[1].labor[0]==1 && bytes(*d)==original,"defense composition or unrelated state preservation differs");
    uint32_t seed=1;
    for (const auto& draw:r.draws) {
        require(draw.before==seed,"private draw order has a discontinuity"); seed=seed*1103515245u+12345u;
        require(draw.after==seed && draw.value==(seed>>16)%draw.bound,"private draw recurrence/order differs");
    }
    require(!r.draws.empty() && seed==state.privateRng && r.replaySeed==seed && state.battles[0].seed==seed,
            "Battle replay seed was captured before participant creation completed");
    // Independently compose the existing leaves in the original caller order.
    auto manual=std::make_unique<save::Document>(); std::vector<CombatSiteProjection> changes; save::Error e;
    ok(rebuildCombatSiteProjection(*d,1,*manual,changes,e),e); auto expected=c.preparation; expected.selectedTerrainTerritory=1;
    CombatBattlePreparationReport begun; ok(beginCombatBattle(*manual,{1,0,1,1},expected,begun,e),e); expected=std::move(begun.after);
    auto addArmy=[&](uint32_t id) { CombatCreationArmy input; ok(projectCombatCreationArmy(*manual,id,input,e),e);
        CombatPreparedWarriorReport leaf; ok(createPreparedCombatWarrior(*manual,input,expected,leaf,e),e); expected=std::move(leaf.after); };
    addArmy(10); addArmy(30);
    for (uint32_t id:{902u,900u}) { CombatBuildingReport leaf; ok(addCombatBuilding(*manual,id,expected,leaf,e),e); expected=std::move(leaf.after); }
    addArmy(20); addArmy(40); CombatAuxiliaryReport militia;
    ok(createCombatMilitia(*manual,CombatStructureRef{0},expected,militia,e),e); expected=std::move(militia.after);
    expected.battles[0].seed=expected.privateRng; CombatDefenseReport defense;
    ok(rebuildCombatDefense(*manual,expected,defense,e),e); expected=std::move(defense.after); expected.selectedTerrainTerritory=999;
    require(state==expected && bytes(*out.document)==bytes(*manual),"territorial caller differs from real leaf composition");
    auto alias=std::make_unique<save::Document>(*d); CombatTerritoryReport aliasReport; aliasReport.contextAfter=c;
    ok(prepareSelectedTerritoryCombat(*alias,1,aliasReport.contextAfter,*alias,aliasReport,e),e);
    require(aliasReport==r && bytes(*alias)==bytes(*out.document),"document and nested context/report alias changed publication");
}
void reservesSeaAndNativeNull() {
    auto d=populated(); d->buildings[1].category=19; auto out=run(*d);
    require(out.report.contextAfter.militiaPopulation==17 && out.report.auxiliaries.empty() &&
            out.report.contextAfter.preparation.warriorCursor==4,"saved active category19 did not reserve population and suppress militia");
    d->territories[0].data.population=-12; out=run(*d);
    require(out.report.contextAfter.militiaPopulation==-12,"militia population was not signed16");
    d->buildings[1].flags=2; out=run(*d);
    require(out.report.contextAfter.militiaPopulation==0 && out.report.auxiliaries.size()==1,"inactive category19 still reserved population");
    d=fixture(); d->territories[0].data.terrain=0; d->territories[0].data.population=1;
    unit(*d,1,1,1); unit(*d,2,13,1); unit(*d,3,1,0); unit(*d,4,13,0); auto sea=run(*d);
    require(sea.report.armies.size()==4 && sea.report.armies[0].seaDomainSkipped && sea.report.armies[2].seaDomainSkipped &&
            !sea.report.armies[1].seaDomainSkipped && !sea.report.armies[3].seaDomainSkipped &&
            sea.report.contextAfter.preparation.warriorCursor==2 && sea.report.contextAfter.militiaPopulation==0,
            "sea preparation did not skip only domain1 in both passes");
    d=populated(); auto c=context(); c.preparation.warriorLimit=0; c.preparation.structureLimit=0;
    auto full=run(*d,c);
    require(full.report.contextAfter.preparation.warriorCursor==0 && full.report.contextAfter.preparation.structureCursor==0 &&
            full.report.buildings[0].outcome==CombatBuildingOutcome::StructurePoolFull &&
            full.report.buildings[1].outcome==CombatBuildingOutcome::FortificationPoolFull &&
            (full.report.contextAfter.preparation.grid.flags[cell(7,1)]&3)==3 && full.report.draws.empty() &&
            full.report.replaySeed==1 && full.report.defenseRebuilt,"native pool-full erased footprint effects or became API failure");
}
void atomicFailuresAndExplicitSelection() {
    auto d=populated(); auto good=run(*d); const auto kept=bytes(*good.document);
    const auto report=good.report; const auto archive=bytes(*d);
    save::Error e;
    auto check=[&](const CombatTerritoryContext& c) {
        require(!prepareSelectedTerritoryCombat(*d,1,c,*good.document,good.report,e) && good.report==report &&
                bytes(*good.document)==kept && bytes(*d)==archive,"late preparation failure leaked document/pools/RNG/report");
    };
    auto c=context(); c.preparation.battleCount=32; check(c);
    c=context(); c.preparation.maximumRandomDraws=0; check(c); // foreign slots and buildings precede defender draw.
    auto mines=fixture(); mines->territories[0].data.population=1; mines->territories[0].data.exploredMask=4; unit(*mines,1,1,1);
    c=context(); c.preparation.maximumRandomDraws=1; const auto mineBytes=bytes(*mines);
    require(!prepareSelectedTerritoryCombat(*mines,1,c,*mines,good.report,e) && bytes(*mines)==mineBytes &&
            good.report==report && e.code==save::ErrorCode::Limit,"mine second draw failure leaked prior participants/aliased sites");
    auto amphib=fixture(); amphib->territories[0].data.population=1; unit(*amphib,1,27,1); c=context();
    require(!prepareTerritoryCombat(*amphib,1,c,*good.document,good.report,e) && good.report==report && bytes(*good.document)==kept,
            "raw leaf silently inferred selected terrain for amphibious placement");
    auto selected=run(*amphib,c); require(selected.report.contextAfter.preparation.selectedTerrainTerritory==999,
            "wrapper failed to restore unrepresented but unused prior selection");
    c.preparation.selectedTerrainTerritory=1; auto direct=run(*amphib,c,false);
    require(direct.report.contextAfter.preparation.selectedTerrainTerritory==1,"raw leaf changed explicit selection");
    require(!prepareSelectedTerritoryCombat(*d,0,c,*good.document,good.report,e) && good.report==report,
            "sentinel0 became a represented territory");
}
void corpus(const std::filesystem::path& directory) {
    if (directory.empty() || !std::filesystem::is_regular_file(directory/"TUTORIAL.SAV")) return;
    auto d=std::make_unique<save::Document>(); save::Error e; ok(save::readDocument(directory/"TUTORIAL.SAV",*d,e),e);
    const auto archive=bytes(*d); size_t skipped=0;
    for (size_t i=0;i<d->territories.size();++i) {
        const auto id=uint32_t(i+1); const auto& t=d->territories[i].data; int32_t site; std::optional<uint32_t> unitId;
        ok(findActiveCombatBuildingCategory(*d,id,19,0,site,e),e); ok(nextCombatArmyById(*d,t.foreignArmies.raw,-1,unitId,e),e);
        if (t.foreignArmies.raw) continue;
        auto out=std::make_unique<save::Document>(); CombatTerritoryReport report; const auto c=context();
        ok(prepareSelectedTerritoryCombat(*d,id,c,*out,report,e),e);
        require(!report.selection.prepared && report.contextAfter==c && bytes(*out)==archive,"real empty foreign list invented a Battle"); ++skipped;
    }
    require(bytes(*d)==archive,"real sample was modified");
    std::cout<<"combat territory: real tutorial query/no-battle territories "<<skipped<<'\n';
}
} // namespace
int main(int argc,char** argv) {
    try {
        const auto oldGs=std::make_unique<GameState>(gs); const auto oldGg=std::make_unique<GameGlobals>(gg);
        const auto low=rtl::seed(),high=rtl::seedHi();
        enumeratorAndCategory(); siteProjection(); selectionGates(); compositionAndReplaySeed(); reservesSeaAndNativeNull();
        atomicFailuresAndExplicitSelection(); corpus(argc>1?std::filesystem::path(argv[1]):std::filesystem::path{});
        require(!std::memcmp(oldGs.get(),&gs,sizeof(gs)) && !std::memcmp(oldGg.get(),&gg,sizeof(gg)) &&
                low==rtl::seed() && high==rtl::seedHi(),"territory preparation touched global state or shared RNG");
        std::cout<<"combat_territory: participant selection, ordered real composition, sites, seeds and rollback passed\n"; return 0;
    } catch (const std::exception& e) { std::cerr<<"combat_territory: "<<e.what()<<'\n'; return 1; }
}
