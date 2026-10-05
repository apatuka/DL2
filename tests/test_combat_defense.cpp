// Static PE/assembly anchors and geometric oracles; no original execution.
#include "game/combat_defense.h"
#include "game/combat_creation_tables.h"
#include "game/data_tables.h"
#include "game/save_files.h"
#include "formats/hdx_archive.h"
#include <algorithm>
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
void require(bool v,const char* message) { if (!v) throw std::runtime_error(message); }
void ok(bool v,const save::Error& e) { if (!v) throw std::runtime_error(e.message); }
size_t cell(int x,int y) { return size_t((y+9)*36+x+9); }
std::unique_ptr<save::Document> fixture() {
    auto d = std::make_unique<save::Document>();
    std::memcpy(d->header.text,save::kHeaderText,sizeof(save::kHeaderText));
    d->header.version=kSaveVersion; d->world.width=1; d->world.height=1;
    d->world.numTerritories=1; d->tiles.resize(1); d->territories.resize(1); d->options.numPlayers=1;
    d->tiles[0].territory=1; d->territories[0].data.index=1;
    for (auto& jobs:d->ministerJobs) jobs.resize(1);
    return d;
}
CombatPreparationState state(int type=19,int x=9,int y=9) {
    CombatPreparationState s; s.currentBattle=CombatBattleRef{0};
    s.battles[0].core.first=CombatantRef{7}; s.battles[0].core.last=CombatantRef{9999};
    s.battles[0].seed=4321; s.privateRng=1234; s.grid.penalty.fill(99); s.grid.flags.fill(0xf3);
    auto& w=s.warriors[7]; w.type=type; w.active=0x80; w.currentX=x; w.currentY=y;
    w.x=-7; w.y=-8; w.initialX=22; w.initialY=23;
    // These fields are not read by any class10 range branch.
    w.currentOwner=w.originalOwner=255; w.orders=2; w.target=CombatantRef{9999};
    w.structureTarget=CombatStructureRef{9999}; w.workNext=CombatantRef{7};
    return s;
}
void geometry() {
    auto d=fixture(); save::Error e;
    constexpr int types[]{19,20,21,22,32}, ranges[]{49,64,64,81,81};
    for (size_t t=0;t<5;++t) for (const auto [cx,cy]:{std::pair{9,9},{-9,-9},{26,26},{0,0},{50,50}}) {
        auto s=state(types[t],cx,cy); const auto old=s; CombatDefenseReport out;
        ok(rebuildCombatDefense(*d,s,out,e),e);
        auto expected=s; expected.grid.penalty.fill(0); std::vector<size_t> touched;
        // Independent disk oracle across the physical grid, using int64 and
        // literal PE range values. Does not reproduce the native box loops.
        for (int y=-9;y<=26;++y) for (int x=-9;x<=26;++x) {
            const int64_t dx=int64_t(cx)-x,dy=int64_t(cy)-y;
            if (combat_creation_tables::kValidCells[cell(x,y)] && dx*dx+dy*dy<ranges[t]) {
                expected.grid.penalty[cell(x,y)]=10; touched.push_back(cell(x,y));
            }
        }
        require(out.after==expected && s==old,"only penalty changes, around CURRENT coordinates");
        require(out.sources==std::vector<CombatDefenseSource>{{{7},ranges[t],touched}},"fort sources and native write order");
        require(e.code==save::ErrorCode::None,"success clears Error");
    }
    auto s=state(); CombatDefenseReport out; ok(rebuildCombatDefense(*d,s,out,e),e);
    require(out.after.grid.penalty[cell(15,9)]==10 && out.after.grid.penalty[cell(16,9)]==0,
            "range49 includes distance6, excludes exact squared boundary49");
    require(out.after.grid.penalty[cell(9,16)]==0,"strict boundary applies to both axes");
    for (int32_t x:{std::numeric_limits<int32_t>::min(),std::numeric_limits<int32_t>::max()}) {
        s=state(32,x,9); ok(rebuildCombatDefense(*d,s,out,e),e);
        require(out.sources[0].cells.empty(),"wrapped half-open endpoints form an empty signed loop");
        require(std::all_of(out.after.grid.penalty.begin(),out.after.grid.penalty.end(),[](auto p){return p==0;}),"empty wrapped loop still clears all penalty");
    }
}
void chainAndAtomicity() {
    auto d=fixture(); save::Error e; auto s=state();
    const auto prototype=s.warriors[7]; s.battles[0].core.first=CombatantRef{0};
    for (size_t i=0;i<26;++i) { s.warriors[i]=prototype; s.warriors[i].next=CombatantRef{i+1}; }
    s.warriors[26].active=0; s.warriors[26].type=-999; s.warriors[26].next=CombatantRef{27};
    s.warriors[27].active=1; s.warriors[27].type=15; s.warriors[27].target=CombatantRef{9999};
    CombatDefenseReport out; ok(rebuildCombatDefense(*d,s,out,e),e);
    require(out.sources.size()==26 && out.after.grid.penalty[cell(9,9)]==4,"26 overlapping forts add260 and wrap to4");
    require(out.after.warriors==s.warriors && out.after.battles==s.battles,"list order, ignored targets and pools remain intact");
    CombatDefenseReport again; ok(rebuildCombatDefense(*d,out.after,again,e),e);
    ok(rebuildCombatDefense(*d,out.after,out,e),e); require(out==again,"report input alias is safe and rebuild does not accumulate old penalty");
    const auto keep=out;
    for (int kind=0;kind<7;++kind) {
        auto bad=s;
        if (kind==0) bad.currentBattle.reset();
        if (kind==1) bad.currentBattle=CombatBattleRef{32};
        if (kind==2) bad.warriors.pop_back();
        if (kind==3) bad.battles[0].core.first=CombatantRef{840};
        if (kind==4) bad.warriors[27].next=CombatantRef{0};
        if (kind==5) bad.warriors[27].next=CombatantRef{9999};
        if (kind==6) bad.warriors[27].type=39;
        const auto before=bad;
        require(!rebuildCombatDefense(*d,bad,out,e) && out==keep && bad==before,"early/late failures preserve input and full report");
    }
    s.battles[0].core.first.reset(); s.warriors[0].next=CombatantRef{9999};
    ok(rebuildCombatDefense(*d,s,out,e),e); require(out.sources.empty(),"empty selected chain ignores stale pool references");
    require(std::all_of(out.after.grid.penalty.begin(),out.after.grid.penalty.end(),[](auto p){return p==0;}),"empty chain clears penalty");
}
void originalEvidence(const std::filesystem::path& directory) {
    std::ifstream file(directory/"DEADLOCK.EXE",std::ios::binary);
    require(bool(file),"open original PE");
    std::vector<uint8_t> bytes((std::istreambuf_iterator<char>(file)),{});
    auto u16=[&](size_t p){return uint16_t(bytes.at(p)|uint16_t(bytes.at(p+1))<<8);};
    auto u32=[&](size_t p){return uint32_t(bytes.at(p))|uint32_t(bytes.at(p+1))<<8|uint32_t(bytes.at(p+2))<<16|uint32_t(bytes.at(p+3))<<24;};
    const size_t pe=u32(0x3c),sections=pe+24+u16(pe+20); const auto base=u32(pe+52);
    require(u16(0)==0x5a4d && u32(pe)==0x4550 && u16(pe+24)==0x10b,"PE32 signature");
    auto at=[&](uint32_t va) -> uint8_t {
        const auto rva=va-base;
        for (size_t i=0;i<u16(pe+6);++i) { const auto p=sections+40*i; const auto start=u32(p+12);
            if (rva>=start && rva-start<u32(p+16)) return bytes.at(u32(p+20)+rva-start); }
        throw std::runtime_error("unbacked PE address");
    };
    for (size_t i=0;i<1296;++i) require(at(0x4cf858+uint32_t(i))==combat_creation_tables::kValidCells[i],"all1296 mask bytes match original");
    constexpr int types[]{19,20,21,22,32},ranges[]{49,64,64,81,81};
    for (size_t i=0;i<5;++i) require(at(0x4faf7c+types[i]*0x24+0xb)==10 &&
        at(0x4faf7c+types[i]*0x24+0x17)==ranges[i],"five class10 range constants agree with literal geometry oracle");
    require(at(0x451417)==0x68 && at(0x451418)==0x10 && at(0x451419)==5,"original clears1296 penalty bytes");
    require(at(0x4514d7)==0x7d && at(0x4514d9)==0x80 && at(0x4514dc)==10,"original uses signed strict distance comparison and byte ADD10");
}
void realSamples(const std::filesystem::path& directory) {
    auto d=std::make_unique<save::Document>(); save::Error e; size_t count=0;
    auto inspect=[&] {
        std::vector<uint8_t> old,after; ok(save::encode(*d,old,e),e);
        auto s=state(); CombatDefenseReport a,b; ok(rebuildCombatDefense(*d,s,a,e),e);
        ok(rebuildCombatDefense(*d,s,b,e),e); require(a==b,"real document defense is deterministic");
        ok(save::encode(*d,after,e),e); require(old==after,"all SAV bytes preserved"); ++count;
    };
    ok(save::readDocument(directory/"TUTORIAL.SAV",*d,e),e); inspect();
    HdxArchive archive; std::string why; require(archive.open((directory/"LEVELS").string(),&why),why.c_str());
    for (const auto& entry:archive.entries()) { ok(save::readScenario(directory/"LEVELS",entry.name,*d,e),e); inspect(); }
    require(count==43,"tutorial and42 scenarios");
}
} // namespace
int main(int argc,char** argv) {
    try {
        const auto directory=argc>1?std::filesystem::path(argv[1]):std::filesystem::path("C:/GOG Games/Deadlock 2");
        geometry(); chainAndAtomicity(); originalEvidence(directory); realSamples(directory);
        std::cout<<"combat_defense: disks, strict boundary, byte wrap, linked order, rollback, PE and43 SAVs passed\n"; return 0;
    } catch (const std::exception& e) { std::cerr<<"combat_defense: "<<e.what()<<'\n'; return 1; }
}
