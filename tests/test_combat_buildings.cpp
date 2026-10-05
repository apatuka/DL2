// Assembly-derived expectations and read-only PE checks, not native execution.
#include "game/combat_buildings.h"
#include "game/combat_building_tables.h"
#include "game/data_tables.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include "game/save_files.h"
#include "formats/hdx_archive.h"
#include <algorithm>
#include <bit>
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
void require(bool value,const char* text) { if (!value) throw std::runtime_error(text); }
void ok(bool value,const save::Error& e) { if (!value) throw std::runtime_error(e.message); }
size_t cell(int x,int y) { return size_t((y+9)*36+x+9); }
std::unique_ptr<save::Document> fixture() {
    auto d = std::make_unique<save::Document>(); std::memcpy(d->header.text,save::kHeaderText,sizeof(save::kHeaderText));
    d->header.version = kSaveVersion; d->world.width = 2; d->world.height = 1;
    d->world.numTerritories = 2; d->tiles.resize(2); d->territories.resize(2); d->options.numPlayers = 2;
    for (size_t p = 0; p < 7; ++p) { d->players[p].index = uint8_t(p); d->players[p].type = p ? 3 : 1; d->ministerJobs[p].resize(1); }
    for (size_t i = 0; i < 2; ++i) {
        d->tiles[i].x = uint8_t(i); d->tiles[i].territory = int16_t(i+1);
        auto& t = d->territories[i].data; t.index = uint16_t(i+1); t.owner = int8_t(i); t.terrain = 1;
        t.numTiles = 1; t.secondTile = 0; t.tiles[0].raw = uint32_t(i);
    }
    return d;
}
uint32_t append(save::Document& d,uint8_t type,int8_t site = 6) {
    Building b{}; b.id = uint16_t(20+d.buildings.size()); b.type = type;
    b.category = data::kBuildingTypes[type].category; b.site = site; b.territory = 1; b.flags = 6; b.race = 5;
    d.territories[0].data.sites[size_t(site)].building.raw = b.id; d.buildings.push_back(b); return b.id;
}
CombatPreparationState state() {
    CombatPreparationState s; s.currentBattle = CombatBattleRef{0}; s.battleCount = 1;
    s.battles[0].core.territory = 1; s.battles[0].core.defender = 0;
    s.privateRng = 99; s.selectedTerrainTerritory = 999; s.grid.flags.fill(0x40); s.grid.penalty.fill(0x55);
    return s;
}
std::vector<uint8_t> bytes(const save::Document& d) {
    save::Error e; std::vector<uint8_t> v; ok(save::encode(d,v,e),e); return v;
}
CombatBuildingReport add(const save::Document& d,uint32_t id,const CombatPreparationState& s) {
    const auto archive = bytes(d); const auto old = s; save::Error e{save::ErrorCode::Io,99,"old"}; CombatBuildingReport result;
    ok(addCombatBuilding(d,id,s,result,e),e);
    require(s == old && bytes(d) == archive,"building participant preserves inputs and SAV");
    require(e.code == save::ErrorCode::None && e.offset == 0 && e.message.empty(),"building success clears Error");
    return result;
}

void footprints() {
    auto s = state(); save::Error e; CombatFootprintReport r;
    ok(markCombatBuildingFootprint(s.grid,1,1,1,r,e),e);
    require(r.markedCells == 4,"size1 occupies2x2, not3x3");
    for (int y = -9; y <= 26; ++y) for (int x = -9; x <= 26; ++x)
        require(r.after.flags[cell(x,y)] == ((x >= 1 && x <= 2 && y >= 1 && y <= 2) ? 0x43 : 0x40),"rectangular footprint OR3 only");
    require(r.after.penalty == s.grid.penalty,"footprint preserves all penalty bytes");
    ok(markCombatBuildingFootprint(s.grid,22,22,2,r,e),e); require(r.markedCells == 25,"size2 occupies5x5 including physical far edge");
    auto keep = r;
    require(!markCombatBuildingFootprint(s.grid,23,22,2,r,e) && r == keep,"partial rectangle overflow rolls back grid");
    ok(markCombatBuildingFootprint(s.grid,2147483647,2147483647,0,r,e),e);
    require(r.markedCells == 0 && r.after == s.grid,"empty loop does not validate unused coordinates");
    ok(markCombatBuildingFootprint(s.grid,2147483647,0,1,r,e),e);
    require(r.markedCells == 0 && r.after == s.grid,"wrapped signed endX can suppress every native inner loop");
    ok(markCombatSeaPlatformFootprint(s.grid,1,1,r,e),e);
    require(r.markedCells == 57,"platform uses57 active cells in its225-word mask");
    constexpr const char* rows[15]{"......###......","......###......","......###......",".......#.......",".......#.......",
        ".......#.......","###...###...###","###############","###...###...###",".......#.......",".......#.......",
        ".......#.......","......###......","......###......","......###......"};
    for (int y = 0; y < 15; ++y) for (int x = 0; x < 15; ++x)
        require(r.after.flags[cell(x+1,y+1)] == (rows[y][x] == '#' ? 0x43 : 0x40),"platform shape matches independent hand-rendered mask");
    const auto expected = r; ok(markCombatSeaPlatformFootprint(r.after,1,1,r,e),e);
    require(r == expected,"platform report.after aliases safely and counts original writes even when already occupied");
    keep = r;
    require(!markCombatSeaPlatformFootprint(s.grid,1,-10,r,e) && r == keep,"platform validates each reached write and rolls back all earlier ones");
}

void structuresAndFull() {
    auto d = fixture(); auto s = state(); const auto id = append(*d,1);
    auto& old = s.structures[0]; old.parentBuildingId = 999; old.type = -1; old.x = -22; old.y = 88;
    old.damage = -2; old.state10 = -9; old.state12 = 90; old.preserved13 = 0xe7; old.defense = -1; old.next = CombatStructureRef{7000};
    auto r = add(*d,id,s); const auto& c = r.after.structures[0];
    require(r.outcome == CombatBuildingOutcome::StructureCreated && r.structure == CombatStructureRef{0} && !r.warrior &&
            !r.syntheticArmy && !r.warriorOutcome && r.draws.empty(),"ordinary building creates structure only, without RNG");
    require(c.parentBuildingId == id && c.type == 1 && c.x == 1 && c.y == 4 && c.damage == 0 && c.state10 == 0 &&
            c.state12 == 5 && c.preserved13 == 0xe7 && c.defense == 10 && !c.next,
            "ordinary structure writes exact fields, signed coordinates and retains byte+13");
    require(r.after.structureCursor == 1 && r.after.battles[0].firstStructure == r.structure && r.after.battles[0].lastStructure == r.structure &&
            r.after.warriors == s.warriors && r.after.privateRng == s.privateRng && r.after.selectedTerrainTerritory == 999,
            "structure allocation only changes its own pool/list and footprint");
    auto wrapped = r.after; wrapped.structureCursor = 1199; wrapped.structureLimit = 500;
    const auto tail = add(*d,id,wrapped);
    require(tail.structure == CombatStructureRef{1199} && tail.after.structureCursor == 0 &&
            tail.after.structures[0].next == tail.structure,"structure ring wraps1200 and appends to existing list");
    auto full = s; full.structureCursor = full.structureLimit; full.currentBattle.reset();
    auto denied = add(*d,id,full);
    require(denied.outcome == CombatBuildingOutcome::StructurePoolFull && denied.footprintCells == 4 && !denied.structure,
            "full structure pool succeeds with footprint even without a selected Battle");
    auto expected = full; expected.grid = denied.after.grid;
    require(denied.after == expected && denied.after.grid != full.grid,"full branch changes only occupancy before its early return");
    d->buildings[0].turnsLeft = 8; full.battles[0].core.territory = 0;
    require(add(*d,id,full).outcome == CombatBuildingOutcome::StructurePoolFull,"full branch does not evaluate sprite or Battle terrain");
    d->buildings[0].turnsLeft = 0; s.battles[0].core.defender = -1234;
    require(add(*d,id,s).after.structures[0].defense == 10,"non-City-Center labor query never dereferences unused defender player");
    auto d2 = fixture(); const auto city = append(*d2,37); save::Error e; const auto keep = r;
    require(!addCombatBuilding(*d2,city,s,r,e) && r == keep,"City Center cost query rejects actual invalid Player.index access atomically");
    s.battles[0].core.defender = 1;
    require(add(*d2,city,s).after.structures[0].defense == 40,"City Center defender can differ from territory owner without changing labor");
}

void constructionSpritesAndDefense() {
    auto d = fixture(); auto s = state(); const auto id = append(*d,1); auto& b = d->buildings[0]; save::Error e;
    for (const auto item : std::array<std::array<int,3>,7>{{{{8,105,2}},{{7,106,3}},{{5,106,5}},{{4,107,6}},{{0,107,10}},{{11,105,255}},{{-1,107,11}}}}) {
        b.turnsLeft = int16_t(item[0]); uint8_t icon = 0;
        ok(combatBuildingConstructionSprite(*d,id,1,icon,e),e); require(icon == item[1],"size1 sprite uses signed completion at30/60 thresholds");
        const auto r = add(*d,id,s); const auto& c = r.after.structures[0];
        require(c.state10 == (b.turnsLeft == 0 ? 0 : item[1]*2) && c.defense == item[2],"structure sprite doubles and signed defense result narrows through low byte");
    }
    b.turnsLeft = 8; b.flags = 4; uint8_t icon = 0;
    ok(combatBuildingConstructionSprite(*d,id,1,icon,e),e); require(icon == 111,"unbuilt flag selects111 only after division");
    b.type = 5; b.category = 1; b.turnsLeft = 53; b.flags = 6;
    ok(combatBuildingConstructionSprite(*d,id,1,icon,e),e); require(icon == 108,"large size2 adds3 to built incomplete sprite");
    b.turnsLeft = 52; ok(combatBuildingConstructionSprite(*d,id,1,icon,e),e); require(icon == 109,"integer percent crosses30 only at correct labor boundary");
    b.turnsLeft = 30; ok(combatBuildingConstructionSprite(*d,id,1,icon,e),e); require(icon == 110,"size2 completion60 chooses final frame");
    b.flags = 0; ok(combatBuildingConstructionSprite(*d,id,1,icon,e),e); require(icon == 112,"unbuilt size2 chooses112");
    b.type = 39; b.turnsLeft = 0; b.site = 6;
    const auto zero = add(*d,id,s); require(zero.after.structures[0].defense == 60,"zero labor complete SeaHab copies unsigned table hit points");
    auto output = zero; const auto keep = output;
    for (const uint16_t flags : std::array<uint16_t,2>{0,2}) {
        b.flags = flags; b.turnsLeft = 1; icon = 99;
        require(!combatBuildingConstructionSprite(*d,id,1,icon,e) && icon == 99,"zero divisor rejects before either Built branch");
        require(!addCombatBuilding(*d,id,s,output,e) && output == keep,"late zero-divisor failure rolls back footprint and appended structure");
    }
    b.type = 1; b.turnsLeft = -32768;
    const auto extreme = add(*d,id,s);
    require(extreme.after.structures[0].defense == 10,"negative32768 construction labor wraps only at final byte, without saturation");
    s.battles[0].core.territory = 2; d->territories[1].data.owner = -1;
    require(add(*d,id,s).after.selectedTerrainTerritory == 999,"temporary sprite selection preserves unrelated stale selected territory");
    b.type = 37;
    require(!addCombatBuilding(*d,id,s,output,e) && output == keep,"unfinished City Center queries selected territory owner, distinct from Battle defender");
}

void fortifications() {
    for (const uint8_t type : std::array<uint8_t,5>{29,30,31,32,40}) {
        auto d = fixture(); auto s = state(); const auto id = append(*d,type,7);
        auto& old = s.warriors[0]; old.parent = CombatArmyParent{999}; old.facing = 8; old.initialFacing = 2;
        old.supplyPenalty = 1; old.preserved15 = 55; old.workNext = CombatantRef{9999}; old.secondaryArmyId = 123;
        const auto r = add(*d,id,s); const auto& w = r.after.warriors[0];
        require(r.outcome == CombatBuildingOutcome::FortificationCreated && r.warrior == CombatantRef{0} && !r.structure &&
                r.warriorOutcome == CombatCreationOutcome::Created && r.footprintCells == 4,"active completed defense creates actual Warrior");
        CombatCreationArmy expected; expected.type = type == 40 ? 32 : uint8_t(type-10);
        expected.owner = 0; expected.orders = 26; expected.retreatPercent = 100;
        require(r.syntheticArmy == expected && w.type == expected.type && w.orders == 26 && w.experience == 0 && w.damage == 0,
                "synthetic Army is zeroed except original fields, including special TorpedoFort40->32");
        require(std::get<CombatBuildingParent>(w.parent).id == id && w.x == 4 && w.y == 4 && w.currentX == 4 && w.currentY == 4 &&
                w.initialX == 4 && w.initialY == 4 && w.facing == 8 && w.initialFacing == 8,
                "fort caller fixes Building parent and all coordinate pairs after class10 leaf keeps stale position/facing");
        require(w.retreatDamage == data::kUnitTypes[expected.type].defense/2 && r.thresholdDefense == w.retreatDamage &&
                w.supplyPenalty == 0 && w.preserved15 == 55 && w.workNext == old.workNext && w.secondaryArmyId == 123,
                "real statistics consume previous supply byte and creation preserves untouched pool fields");
        require(r.after.defenderCount == 1 && r.after.attackerCount == 0 && r.after.structures == s.structures &&
                r.after.privateRng == 99 && r.draws.empty(),"canonical fort adds defender without extra draw or structure allocation");
        s.warriorCursor = s.warriorLimit; const auto full = add(*d,id,s);
        require(full.outcome == CombatBuildingOutcome::FortificationPoolFull && full.warriorOutcome == CombatCreationOutcome::PoolFull &&
                !full.warrior && full.after.grid != s.grid && full.after.warriors == s.warriors,"fort full pool retains footprint and native null outcome");
        s = state(); d->buildings[0].flags = 2;
        const auto inactive = add(*d,id,s);
        require(inactive.outcome == CombatBuildingOutcome::StructureCreated && inactive.after.structures[0].state10 == -2,
                "inactive completed defense becomes structure with exactffff-1 sprite sentinel");
        d->buildings[0].flags = 6; d->buildings[0].turnsLeft = 1;
        require(add(*d,id,s).outcome == CombatBuildingOutcome::StructureCreated,"in-progress active defense remains a structure");
    }
    auto d = fixture(); const auto id = append(*d,26); d->buildings[0].category = 18;
    const auto r = add(*d,id,state());
    require(r.outcome == CombatBuildingOutcome::FortificationNotCreated && r.warriorOutcome == CombatCreationOutcome::DefenderWarhead &&
            r.footprintCells == 25 && !r.warrior,"raw noncanonical category is preserved: type26 synthetic16 has native defending-warhead null");
}

void platformErrorsAndAlias() {
    auto d = fixture(); const auto id = append(*d,38,24); auto s = state();
    auto r = add(*d,id,s);
    require(r.footprintCells == 57 && r.after.structures[0].x == 1 && r.after.structures[0].y == 1 &&
            r.after.structures[0].defense == 1,"Sea Platform uses adjusted15x15 mask and zero-labor HP branch");
    const auto expected = add(*d,id,r.after); save::Error e;
    ok(addCombatBuilding(*d,id,r.after,r,e),e); require(r == expected,"building composition permits report.after context alias");
    const auto keep = r;
    auto fails = [&](const CombatPreparationState& bad) {
        const auto archive = bytes(*d); require(!addCombatBuilding(*d,id,bad,r,e) && r == keep && bytes(*d) == archive,
            "bad reached context preserves complete old report and document");
    };
    auto bad = s; bad.structures.pop_back(); fails(bad);
    bad = s; bad.currentBattle.reset(); fails(bad);
    bad = s; bad.currentBattle = CombatBattleRef{32}; fails(bad);
    bad = s; bad.structureCursor = 1200; fails(bad);
    bad = s; bad.structureLimit = 1200; fails(bad);
    bad = s; bad.battles[0].firstStructure = CombatStructureRef{5}; fails(bad);
    bad = s; bad.battles[0].firstStructure = bad.battles[0].lastStructure = CombatStructureRef{5}; bad.structures[5].next = CombatStructureRef{5}; fails(bad);
    bad = s; bad.battles[0].firstStructure = bad.battles[0].lastStructure = CombatStructureRef{0}; fails(bad);
    bad = s; bad.battles[0].core.territory = 0; fails(bad);
    require(!addCombatBuilding(*d,999,s,r,e) && r == keep,"missing building leaves previous output");
    d->territories[0].data.sites[24].building.raw = 0; d->buildings[0].site = 0; d->territories[0].data.sites[0].building.raw = id;
    fails(s); // platform now starts y=-11; first nonzero cell is outside physical grid.
    d->header.version = 0;
    require(!addCombatBuilding(*d,id,s,r,e) && r == keep && e.code == save::ErrorCode::UnsupportedVersion,"original codec error is preserved");
}

class Pe {
    std::vector<uint8_t> b; size_t sections; uint16_t count; uint32_t base;
    uint16_t u16(size_t p) const { require(p+2 <= b.size(),"PE short bounds"); return uint16_t(b[p]|uint16_t(b[p+1])<<8); }
    uint32_t u32(size_t p) const { require(p+4 <= b.size(),"PE word bounds"); return uint32_t(b[p])|uint32_t(b[p+1])<<8|uint32_t(b[p+2])<<16|uint32_t(b[p+3])<<24; }
    size_t offset(uint32_t va) const {
        require(va >= base,"PE base bounds"); const auto rva = va-base;
        for (size_t i = 0; i < count; ++i) { const auto p = sections+40*i, start = size_t(u32(p+12));
            if (rva >= start && rva-start < u32(p+16)) return u32(p+20)+rva-start; }
        throw std::runtime_error("unbacked PE address");
    }
public:
    explicit Pe(const std::filesystem::path& path) {
        std::ifstream f(path,std::ios::binary); require(bool(f),"open original PE");
        const auto n = std::filesystem::file_size(path); require(n < 16*1024*1024 && n >= 64,"PE length");
        b.resize(size_t(n)); require(bool(f.read(reinterpret_cast<char*>(b.data()),std::streamsize(n))),"read original PE");
        const auto pe = u32(60); require(u16(0) == 0x5a4d && u32(pe) == 0x4550,"PE signature");
        count = u16(pe+6); base = u32(pe+52); sections = pe+24+u16(pe+20);
    }
    uint32_t word(uint32_t va) const { return u32(offset(va)); }
    uint8_t byte(uint32_t va) const { const auto p = offset(va); require(p < b.size(),"PE byte bounds"); return b[p]; }
};
void evidenceAndCorpus(const std::filesystem::path& directory) {
    const Pe pe(directory/"DEADLOCK.EXE");
    for (size_t i = 0; i < 225; ++i)
        require(std::bit_cast<int32_t>(pe.word(0x4cfd68+uint32_t(i)*4)) == combat_building_tables::kSeaPlatformMask[i],"platform mask differs from original PE words");
    for (size_t i = 0; i < data::kNumBuildingTypes; ++i) {
        require(pe.byte(0x4f9dc5+uint32_t(i)*50) == data::kBuildingTypes[i].size &&
                uint16_t(pe.word(0x4f9dc6+uint32_t(i)*50)) == data::kBuildingTypes[i].buildLabor &&
                pe.byte(0x4f9de4+uint32_t(i)*50) == data::kBuildingTypes[i].hitPoints,"footprint/labor/HP canonical table values match PE");
    }
    require(pe.word(0x451f60) == 1200,"structure ring modulus is1200 in PE");
    size_t documents = 0, participants = 0; auto d = std::make_unique<save::Document>(); save::Error e;
    auto inspect = [&] {
        const auto archive = bytes(*d); size_t sampled = 0;
        for (const auto& b : d->buildings) {
            auto s = state(); s.battles[0].core.territory = uint32_t(b.territory);
            const auto owner = d->territories[size_t(b.territory)-1].data.owner;
            s.battles[0].core.defender = owner < 0 ? 0 : owner; // Explicit isolated Battle fixture, not territorial selection.
            const auto first = add(*d,b.id,s), second = add(*d,b.id,s);
            require(first == second,"real building inputs are deterministic in an explicit isolated Battle");
            ++participants; if (++sampled == 12) break;
        }
        require(bytes(*d) == archive,"read-only corpus documents stay byte-exact"); ++documents;
    };
    ok(save::readDocument(directory/"TUTORIAL.SAV",*d,e),e); inspect();
    HdxArchive archive; std::string why; require(archive.open((directory/"LEVELS").string(),&why),why.c_str());
    for (const auto& entry : archive.entries()) { ok(save::readScenario(directory/"LEVELS",entry.name,*d,e),e); inspect(); }
    require(documents == 43 && participants > 0,"all43 documents contribute real building fixtures");
    std::cout << "combat buildings: " << participants << " participant fixtures across " << documents << " documents\n";
}
} // namespace
int main(int argc,char** argv) {
    try {
        std::vector<uint8_t> gsBefore(sizeof(gs)),ggBefore(sizeof(gg));
        std::memcpy(gsBefore.data(),&gs,sizeof(gs)); std::memcpy(ggBefore.data(),&gg,sizeof(gg));
        const auto seed = rtl::seed(), high = rtl::seedHi();
        footprints(); structuresAndFull(); constructionSpritesAndDefense(); fortifications(); platformErrorsAndAlias();
        evidenceAndCorpus(argc > 1 ? std::filesystem::path(argv[1]) : std::filesystem::path("C:/GOG Games/Deadlock 2"));
        require(!std::memcmp(gsBefore.data(),&gs,sizeof(gs)) && !std::memcmp(ggBefore.data(),&gg,sizeof(gg)) &&
                seed == rtl::seed() && high == rtl::seedHi(),"building participants isolate globals and session RNG");
        std::cout << "combat_buildings: footprint, structure ring, fortification, progress, native-full effects and rollback passed\n"; return 0;
    } catch (const std::exception& e) { std::cerr << "combat_buildings: " << e.what() << '\n'; return 1; }
}
