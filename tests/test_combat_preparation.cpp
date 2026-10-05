// Static assembly/PE evidence and calculated oracles; no execution of the
// original game and no claim that this partial prefix is a completed turn.
#include "game/combat_preparation.h"
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
void require(bool value, const char* text) { if (!value) throw std::runtime_error(text); }
void ok(bool value, const save::Error& e) { if (!value) throw std::runtime_error(e.message); }
size_t cell(int x,int y) { return size_t((y+9)*36+x+9); }
std::unique_ptr<save::Document> fixture() {
    auto d = std::make_unique<save::Document>();
    std::memcpy(d->header.text,save::kHeaderText,sizeof(save::kHeaderText));
    d->header.version = kSaveVersion; d->world.width = 2; d->world.height = 1;
    d->world.numTerritories = 2; d->tiles.resize(2); d->territories.resize(2);
    d->options.turn = -99; d->options.numPlayers = 2; d->options.allowAlliances = 1;
    for (size_t p = 0; p < 7; ++p) {
        d->players[p].index = uint8_t(p); d->players[p].type = p ? 3 : 1;
        d->players[p].race = 0; d->ministerJobs[p].resize(1);
    }
    for (size_t i = 0; i < 2; ++i) {
        auto& tile = d->tiles[i]; tile.x = uint8_t(i); tile.territory = int16_t(i+1);
        auto& t = d->territories[i].data;
        t.index = uint16_t(i+1); t.owner = int8_t(i); t.terrain = 1;
        t.numTiles = 1; t.secondTile = 0; t.tiles[0].raw = uint32_t(i);
    }
    return d;
}
std::vector<uint8_t> bytes(const save::Document& d) {
    std::vector<uint8_t> result; save::Error e; ok(save::encode(d,result,e),e); return result;
}
CombatPreparationState dirty() {
    CombatPreparationState s;
    CombatWarrior w;
    w.parent = CombatBuildingParent{123}; w.type = 10; w.currentOwner = 4; w.orders = 7;
    w.experience = -5; w.x = 22; w.y = -7; w.facing = 9; w.preserved15 = 0xa5;
    w.damage = -66; w.retreatDamage = 222; w.retreatTerritory = 0xffff;
    w.supplyPenalty = 0x80; w.active = 1; w.originalOwner = 4; w.preserved1f = 7;
    w.currentX = 1; w.currentY = 2; w.initialX = 3; w.initialY = 4;
    w.initialFacing = 5; w.preserved31 = 6; w.initialDamage = -8;
    w.speedCounter = 9; w.fireCounter = 10; w.state36 = 11; w.preserved37 = 12;
    w.secondaryArmyId = 987; w.target = CombatantRef{9999}; w.structureTarget = CombatStructureRef{8765};
    w.next = CombatantRef{5678}; w.workNext = CombatantRef{1234};
    std::fill(s.warriors.begin(),s.warriors.end(),w);
    CombatStructure structure;
    structure.parentBuildingId = 567; structure.type = 222; structure.x = -888; structure.y = 777;
    structure.damage = 333; structure.state10 = -5; structure.state12 = 88; structure.preserved13 = 99;
    structure.defense = -100; structure.next = CombatStructureRef{8888};
    std::fill(s.structures.begin(),s.structures.end(),structure);
    for (size_t i = 0; i < s.battles.size(); ++i) {
        auto& b = s.battles[i]; b.seed = 0xabcdef00u+uint32_t(i); b.core.territory = 77;
        b.core.defender = -1; b.attacker = -55; b.core.playerMask = 0xcc; b.core.outsidePlacement = 0xdd;
        for (auto& row : b.core.support) row.fill(0x42);
        b.preserved2a = 0xab; b.preserved2b = 0xcd; b.roads.fill(-321);
        b.core.first = CombatantRef{9876}; b.core.last = CombatantRef{6789};
        b.firstStructure = CombatStructureRef{9876}; b.lastStructure = CombatStructureRef{6789};
        b.core.approachMask = 0xff; b.preserved85 = 0xa5;
    }
    s.battleCount = 28; s.turn = 887; s.tick = -321; s.deadline = 779;
    s.attackerCount = 0x80000000u; s.defenderCount = 0xdeadbeefu;
    s.warriorCursor = 8888; s.warriorLimit = 9999; s.structureCursor = 2222; s.structureLimit = 3333;
    s.currentBattle = CombatBattleRef{987654}; s.grid.flags.fill(0xaa); s.grid.penalty.fill(0xbb);
    s.privateRng = 0x12345678u; s.replayMode = -7; s.placementDomain = -99; s.useGridPenalty = 88;
    s.selectedTerrainTerritory = 999; s.creation.movingArmyId = 12345; s.maximumRandomDraws = 3;
    return s;
}
RngSnapshot rng() {
    RngSnapshot s; s.initialized = true; s.rtlLow = 0xfedcba98; s.rtlHigh = 0x10203040;
    s.secondary = 0xdecafbad; s.counters.operations = 17; s.counters.rand15 = 17; return s;
}
CombatBattlePreparationReport begin(const save::Document& d,const CombatPreparationState& s,const CombatBattleRequest& request) {
    const auto previous = s; const auto archive = bytes(d); save::Error e{save::ErrorCode::Io,5,"old"};
    CombatBattlePreparationReport r; ok(beginCombatBattle(d,request,s,r,e),e);
    require(s == previous && bytes(d) == archive,"begin preserves all caller inputs and SAV bytes");
    require(e.code == save::ErrorCode::None && e.offset == 0 && e.message.empty(),"successful begin clears Error");
    return r;
}

void resetPools() {
    auto s = dirty(); const auto old = s;
    CombatPreparationState output; save::Error e;
    ok(resetCombatPools(s,output,e),e);
    auto expected = old;
    expected.warriors.assign(840,CombatWarrior{}); expected.structures.assign(1200,CombatStructure{});
    expected.battles.assign(32,CombatBattleRecord{}); expected.battleCount = 0;
    expected.warriorCursor = 0; expected.warriorLimit = 839;
    expected.structureCursor = 0; expected.structureLimit = 1199;
    require(kCombatWarriorCapacity*0x4c == 0xf960 && kCombatStructureCapacity*0x1a == 0x79e0 &&
            kCombatBattleCapacity*0x86 == 0x10c0,"owned capacities match all three native memset lengths");
    require(output == expected && s == old,"reset touches ONLY physical pools, battle count, cursors and limits");
    require(output.battles[31].core.defender == 0 && CombatCreationBattle{}.defender == -1,
            "zeroed Battle defender differs from standalone creation default -1");
    require(output.currentBattle == old.currentBattle,"reset preserves even an unused stale selected physical index");
    ok(resetCombatPools(s,s,e),e); require(s == expected,"reset aliases safely");
    for (int pool = 0; pool < 3; ++pool) {
        auto bad = old;
        if (pool == 0) bad.warriors.pop_back();
        if (pool == 1) bad.structures.push_back({});
        if (pool == 2) bad.battles.clear();
        require(!resetCombatPools(bad,output,e) && output == expected,"incorrect physical pool shape rejects atomically");
    }
}

void phasePrefix() {
    auto d = fixture(); auto s = dirty(); const auto oldState = s; const auto archive = bytes(*d);
    auto before = rng(); const auto oldRng = before; CombatPhasePreparationReport r; save::Error e;
    ok(prepareCombatPhase(*d,s,before,r,e),e);
    auto expected = s; ok(resetCombatPools(s,expected,e),e); expected.turn = -99; expected.replayMode = 0;
    uint32_t low = before.rtlLow;
    for (size_t i = 0; i < 32; ++i) {
        // Explicit independent recurrence; changing the primitive to Long31
        // would update rtlHigh and produce an entirely different sequence.
        low = uint32_t(uint64_t(low)*22695477u+1u);
        const uint32_t value = (low >> 16)&32767u; expected.battles[i].seed = value;
        require(r.draws[i] == RngEvent{18+i,RngOperation::Rand15,0,0,value,"Combat",true},
                "prefix consumes exactly ordered Rand15 tagged Combat, including unused Battle seeds");
    }
    auto expectedRng = before; expectedRng.rtlLow = low;
    expectedRng.counters.operations += 32; expectedRng.counters.rand15 += 32;
    require(r.after == expected && r.sessionRngAfter == expectedRng,"prefix reset/turn/seeds/private RNG preservation is exact");
    require(s == oldState && before == oldRng && bytes(*d) == archive,"prefix owns outputs without mutating inputs");
    require(r.after.currentBattle == oldState.currentBattle && r.after.privateRng == oldState.privateRng,
            "prefix does not choose a Battle or seed the private RNG");
    CombatPhasePreparationReport next; ok(prepareCombatPhase(*d,r.after,r.sessionRngAfter,next,e),e);
    ok(prepareCombatPhase(*d,r.after,r.sessionRngAfter,r,e),e);
    require(r == next,"state and RNG inputs may simultaneously alias output report");
    const auto keep = r;
    for (int kind = 0; kind < 4; ++kind) {
        auto invalid = before;
        if (kind == 0) invalid = {};
        if (kind == 1) invalid.format = 999;
        if (kind == 2) invalid.counters.operations = 18;
        if (kind == 3) { invalid.counters.operations = std::numeric_limits<uint64_t>::max()-15;
                         invalid.counters.rand15 = invalid.counters.operations; }
        require(!prepareCombatPhase(*d,s,invalid,r,e) && r == keep,"RNG failure, including exhaustion after15 draws, rolls back prefix");
    }
    require(e.code == save::ErrorCode::Limit,"late draw-counter exhaustion remains a Limit error");
    d->header.version = 0;
    require(!prepareCombatPhase(*d,s,before,r,e) && r == keep && e.code == save::ErrorCode::UnsupportedVersion,
            "prefix forwards save-validation failure without publishing");
}

void beginAndLimits() {
    auto d = fixture(); auto s = dirty(); s.battleCount = 3;
    const CombatBattleRequest request{1,-1234,2345,0};
    auto r = begin(*d,s,request); auto expected = s;
    expected.tick = 0; expected.deadline = -1; expected.attackerCount = expected.defenderCount = 0;
    expected.battleCount = 4; expected.currentBattle = CombatBattleRef{3}; expected.privateRng = s.battles[3].seed;
    expected.grid = {};
    auto& b = expected.battles[3]; b.core.territory = 1; b.core.defender = -1234; b.attacker = 2345;
    b.core.outsidePlacement = 0; b.core.first.reset(); b.core.last.reset(); b.firstStructure.reset(); b.lastStructure.reset();
    b.core.playerMask = b.core.approachMask = 0;
    require(r.created == CombatBattleRef{3} && r.after == expected,
            "begin preserves old seed/support/roads/padding, all other Battle slots, both pools and unused references");
    require(r.after.privateRng == s.battles[3].seed,"private seeding performs no draw");
    d->territories[0].data.terrain = 0;
    r = begin(*d,s,request);
    require(std::all_of(r.after.grid.flags.begin(),r.after.grid.flags.end(),[](auto v) { return v == 0x60; }) &&
            std::all_of(r.after.grid.penalty.begin(),r.after.grid.penalty.end(),[](auto v) { return v == 0; }),
            "mode0 sea fills every physical flag cell0x60 with zero penalty");
    for (const int32_t mode : {1,256,-256,std::numeric_limits<int32_t>::min(),-1}) {
        auto req = request; req.mode = mode;
        const auto result = begin(*d,s,req);
        require(result.after.battles[3].core.outsidePlacement == uint8_t(uint32_t(mode)),"stored placement mode is low byte");
        require(result.after.grid.flags[cell(-9,-9)] == 0x70 && result.after.grid.flags[cell(1,1)] == 0,
                "full nonzero mode selects colony grid even on sea with stored low byte zero");
        require(result.after.battles[3].roads == s.battles[3].roads,"nonzero replay mode retains all old road words");
    }
    d->territories[0].data.terrain = 1;
    s.battleCount = 31; s.battles[31].seed = 0;
    r = begin(*d,s,request);
    require(r.created == CombatBattleRef{31} && r.after.battleCount == 32 && r.after.privateRng == 0,
            "last physical Battle is permitted and zero seed is valid");
    save::Error e; const auto keep = r;
    require(!beginCombatBattle(*d,request,r.after,r,e) && r == keep && e.code == save::ErrorCode::Limit,
            "Battle32 rejects without wrapping, overwriting or mutating clocks");
    s.battleCount = -1;
    require(!beginCombatBattle(*d,request,s,r,e) && r == keep,"negative physical index rejects atomically");
    s.battleCount = 0;
    for (const uint32_t id : {0u,3u,0xffffffffu}) {
        auto req = request; req.territory = id;
        require(!beginCombatBattle(*d,req,s,r,e) && r == keep,"unrepresented territory never aliases sentinel0");
    }
    auto first = begin(*d,s,request); const auto second = begin(*d,first.after,request);
    ok(beginCombatBattle(*d,request,first.after,first,e),e);
    require(first == second,"begin report.after may alias its source context");
}

void gridLeaves() {
    CombatCreationGrid grid; grid.flags.fill(0xff); grid.penalty.fill(0x55); save::Error e;
    const auto empty = clearedCombatGrid();
    require(empty == CombatCreationGrid{},"004512a8 clears both entire1296-byte arrays");
    ok(setCombatGridRoad(grid,-9,-9,0,grid,e),e);
    require(grid.flags[0] == 0xfb && grid.penalty[0] == 0x55,"road clearing changes only bit2 at physical first cell");
    ok(setCombatGridRoad(grid,-9,-9,std::numeric_limits<int32_t>::min(),grid,e),e);
    require(grid.flags[0] == 0xff,"any full32-bit nonzero road flag sets bit2");
    grid.flags.back() = 1;
    ok(addCombatGridTerrain(grid,26,26,0x81,grid,e),e);
    ok(addCombatGridTerrain(grid,26,26,2,grid,e),e);
    require(grid.flags.back() == 0x31 && grid.penalty.back() == 0x55,"terrain OR preserves flags and drops high nibble after shift");
    const auto keep = grid;
    for (const auto xy : std::array<std::array<int32_t,2>,5>{{{{-10,0}},{{0,-10}},{{27,0}},{{0,27}},{{2147483647,-2147483647}}}}) {
        require(!setCombatGridRoad(grid,xy[0],xy[1],1,grid,e) && grid == keep,"road bounds fail before coordinate arithmetic");
        require(!addCombatGridTerrain(grid,xy[0],xy[1],2,grid,e) && grid == keep,"terrain bounds failure is atomic");
    }
}

struct RoadCase { uint16_t word; uint16_t cells; };
constexpr std::array<RoadCase,18> roadCases{{
    {0,0},{1,9},{2,6},{4,72},{8,3},{3,7},{5,73},{6,79},{7,79},
    {0xffff,79},{0xff80,1},{0x100,1},{0x8000,1},{0x101,1},{0x104,73},{0x108,1},{0x102,7},{0xff,79}
}};
void gridReconstruction() {
    auto d = fixture(); auto s = dirty(); s.currentBattle = CombatBattleRef{7}; s.replayMode = 0;
    constexpr std::array<uint16_t,6> terrainWords{0,1,0x00ff,0xffff,0xfff2,0x0018};
    constexpr std::array<uint8_t,6> terrainExpected{0,0x10,0x60,0xf0,0x20,0x80};
    for (size_t i = 0; i < 36; ++i) {
        auto& site = d->territories[0].data.sites[i];
        site.terrainFlags = terrainWords[i%6]; site.unk_00 = 0xabcd;
        site.unk_05[11] = uint8_t(roadCases[i%11].word); site.unk_05[12] = 0x55;
    }
    const auto archive = bytes(*d); const auto before = s; CombatPreparationState out; save::Error e;
    ok(rebuildCombatGrid(*d,1,s,out,e),e);
    auto expected = s; expected.grid = {};
    for (int y = -9; y <= 26; ++y) for (int x = -9; x <= 26; ++x) {
        if (x < 0 || y < 0 || x > 17 || y > 17) expected.grid.flags[cell(x,y)] = 0x70;
        else {
            const size_t site = size_t(y/3*6+x/3);
            const int tile = (y%3)*3+x%3;
            expected.grid.flags[cell(x,y)] = uint8_t(terrainExpected[site%6] | ((roadCases[site%11].cells&(1u<<tile)) ? 4u : 0u));
        }
    }
    for (size_t i = 0; i < 36; ++i) expected.battles[7].roads[i] = std::bit_cast<int8_t>(uint8_t(roadCases[i%11].word));
    require(out == expected && s == before && bytes(*d) == archive,
            "grid matches hand-enumerated road footprints, physical border, signed bytes and exact16-bit terrain sentinels");
    require(out.battles[7].roads[9] == -1 && out.battles[7].roads[10] == -128,
            "Site+10 sign extends into road word; adjacent byte+11 is ignored");
    require(out.battles[7].core.territory == 77,"grid input sites are explicit and do not silently replace Battle territory binding");
    s.replayMode = std::numeric_limits<int32_t>::min();
    for (size_t i = 0; i < 36; ++i) s.battles[7].roads[i] = std::bit_cast<int16_t>(roadCases[i%roadCases.size()].word);
    ok(rebuildCombatGrid(*d,1,s,out,e),e);
    require(out.battles == s.battles,"replay preserves full signed16 road words in every Battle");
    for (int y = 0; y < 18; ++y) for (int x = 0; x < 18; ++x) {
        const size_t site = size_t(y/3*6+x/3); const int tile = y%3*3+x%3;
        require((out.grid.flags[cell(x,y)]&4) == ((roadCases[site%roadCases.size()].cells&(1u<<tile)) ? 4 : 0),
                "replay compares the entire road word, including high-byte-only and high-byte-plus-small-value cases");
    }
    const auto keep = out;
    auto bad = s; bad.currentBattle.reset();
    require(!rebuildCombatGrid(*d,1,bad,out,e) && out == keep,"grid requires a selected Battle");
    bad.currentBattle = CombatBattleRef{32};
    require(!rebuildCombatGrid(*d,1,bad,out,e) && out == keep,"grid rejects unrepresented selected index only when accessed");
    require(!rebuildCombatGrid(*d,0,s,out,e) && out == keep,"grid rejects unrepresented territory atomically");
    ok(rebuildCombatGrid(*d,1,s,s,e),e); require(s == keep,"grid supports context/output aliasing");
    s.replayMode = 0; s.battleCount = 7;
    const auto started = begin(*d,s,{1,0,1,1});
    require(started.after.grid == expected.grid && started.after.battles[7].roads == expected.battles[7].roads,
            "begin non-replay colony mode actually composes grid reconstruction");
}

CombatCreationArmy input() { return {std::nullopt,4,1,1,0,0,100,1500,7,2,2}; }
void creationContinuity() {
    auto d = fixture(); CombatPreparationState s; s.selectedTerrainTerritory = 1;
    s.battles[0].seed = 1; s.battles[1].seed = 999;
    s.battles[0].preserved85 = 88; s.structures[1199].preserved13 = 77;
    auto begun = begin(*d,s,{1,0,1,0}); save::Error e;
    CombatCreationContext projected; ok(projectPreparedCombatCreation(begun.after,projected,e),e);
    require(projected.warriors == begun.after.warriors && projected.battle == begun.after.battles[0].core &&
            projected.rng == 1 && projected.selectedTerrainTerritory == 1,"projection binds current Battle and shared pool explicitly");
    CombatCreationReport leaf; const auto source = input(); ok(createCombatWarrior(*d,source,projected,leaf,e),e);
    CombatPreparedWarriorReport created; const auto original = begun.after;
    ok(createPreparedCombatWarrior(*d,source,begun.after,created,e),e);
    require(created.outcome == CombatCreationOutcome::Created && created.created == CombatantRef{0},"prepared wrapper executes real Warrior creation");
    CombatCreationContext afterLeaf; ok(projectPreparedCombatCreation(created.after,afterLeaf,e),e);
    require(afterLeaf == leaf.after && created.draws == leaf.draws && created.thresholdDefense == leaf.thresholdDefense &&
            created.testedPositions == leaf.testedPositions && created.retreatAccessQueries == leaf.retreatAccessQueries &&
            created.missingPlaneRetreat == leaf.missingPlaneRetreat && created.placementFallback == leaf.placementFallback,
            "wrapper publishes the real leaf's complete diagnostics and state");
    require(begun.after == original && created.after.structures == original.structures && created.after.battles[0].preserved85 == 88 &&
            created.after.battleCount == 1 && created.after.currentBattle == CombatBattleRef{0},"wrapper preserves unrelated preparation state");
    auto second = begin(*d,created.after,{1,0,1,0});
    require(second.after.warriors == created.after.warriors && second.after.structures == created.after.structures &&
            second.after.battles[0] == created.after.battles[0] && second.after.warriorCursor == 1 && second.after.privateRng == 999,
            "begin-create-begin retains first Battle and every pool slot while seeding the second Battle");
    CombatPreparedWarriorReport next; ok(createPreparedCombatWarrior(*d,source,second.after,next,e),e);
    require(next.created == CombatantRef{1} && next.after.battles[1].core.first == CombatantRef{1} &&
            !next.after.warriors[0].next && next.after.battles[0] == created.after.battles[0],
            "second Battle allocates the same physical pool without joining the first Battle list");
    const auto archive = bytes(*d);
    auto excluded = source; excluded.mission = 1;
    CombatPreparedWarriorReport null; ok(createPreparedCombatWarrior(*d,excluded,next.after,null,e),e);
    require(null.outcome == CombatCreationOutcome::MissionExcluded && null.after == next.after && !null.created,
            "native null outcome is successful and preserves the complete prepared state");
    auto full = next.after; full.warriorCursor = full.warriorLimit;
    ok(createPreparedCombatWarrior(*d,source,full,null,e),e);
    require(null.outcome == CombatCreationOutcome::PoolFull && null.after == full,"native ring-full outcome is not an API error");
    auto bad = second.after; bad.maximumRandomDraws = 1;
    auto mine = source; mine.type = 37; mine.owner = 0;
    const auto keep = next;
    require(!createPreparedCombatWarrior(*d,mine,bad,next,e) && next == keep && e.code == save::ErrorCode::Limit,
            "late mine failure rolls back allocated pool, Battle list, grid, counters and private RNG together");
    require(bytes(*d) == archive,"composition never changes SAV");
    bad.currentBattle = CombatBattleRef{32};
    const auto projectionKeep = projected;
    require(!projectPreparedCombatCreation(bad,projected,e) && projected == projectionKeep,"invalid selected Battle keeps old projection");
    require(!createPreparedCombatWarrior(*d,source,bad,next,e) && next == keep,"invalid selected Battle keeps old composition report");
    CombatPreparedWarriorReport expected;
    const auto& alias = std::get<CombatCreationArmy>(next.after.warriors[0].parent);
    ok(createPreparedCombatWarrior(*d,alias,next.after,expected,e),e);
    ok(createPreparedCombatWarrior(*d,alias,next.after,next,e),e);
    require(next == expected,"synthetic Army input and preparation state may both alias the output report");
}

class Pe {
    std::vector<uint8_t> data_; size_t sections_ = 0; uint16_t count_ = 0; uint32_t base_ = 0;
    uint16_t u16(size_t p) const { require(p+2 <= data_.size(),"truncated PE word"); return uint16_t(data_[p]|uint16_t(data_[p+1])<<8); }
    uint32_t u32(size_t p) const { require(p+4 <= data_.size(),"truncated PE dword"); return uint32_t(data_[p])|uint32_t(data_[p+1])<<8|uint32_t(data_[p+2])<<16|uint32_t(data_[p+3])<<24; }
    size_t offset(uint32_t va) const {
        require(va >= base_,"PE address below base"); const uint32_t rva = va-base_;
        for (size_t i = 0; i < count_; ++i) { const size_t p = sections_+i*40; const uint32_t start = u32(p+12), size = u32(p+16);
            if (rva >= start && rva-start < size) return size_t(u32(p+20))+rva-start; }
        throw std::runtime_error("unbacked PE address");
    }
public:
    explicit Pe(const std::filesystem::path& path) {
        std::ifstream file(path,std::ios::binary); require(bool(file),"cannot open original PE");
        const auto n = std::filesystem::file_size(path); require(n >= 64 && n < 16*1024*1024,"invalid PE size");
        data_.resize(size_t(n)); require(bool(file.read(reinterpret_cast<char*>(data_.data()),std::streamsize(n))),"cannot read PE");
        const auto pe = u32(0x3c); require(u16(0) == 0x5a4d && u32(pe) == 0x4550 && u16(pe+24) == 0x10b,"not original PE32");
        count_ = u16(pe+6); base_ = u32(pe+52); sections_ = size_t(pe)+24+u16(pe+20);
        require(count_ > 0 && count_ < 100 && sections_+size_t(count_)*40 <= data_.size(),"invalid PE sections");
    }
    uint8_t byte(uint32_t va) const { const auto p = offset(va); require(p < data_.size(),"PE byte outside file"); return data_[p]; }
    uint32_t word(uint32_t va) const { return u32(offset(va)); }
    uint32_t call(uint32_t va) const { require(byte(va) == 0xe8,"expected PE rel32 CALL"); return va+5+word(va+1); }
};
void originalEvidence(const std::filesystem::path& directory) {
    const Pe pe(directory/"DEADLOCK.EXE");
    require(pe.byte(0x4571d4) == 0x68 && pe.word(0x4571d5) == kCombatWarriorCapacity*0x4c &&
            pe.byte(0x4571ef) == 0x68 && pe.word(0x4571f0) == kCombatStructureCapacity*0x1a &&
            pe.byte(0x457203) == 0x68 && pe.word(0x457204) == kCombatBattleCapacity*0x86,
            "original PE encodes the three exact pool reset lengths");
    require(pe.word(0x457227) == 839 && pe.word(0x457237) == 1199,"original PE encodes both reserved ring limits");
    require(pe.call(0x45762f) == 0x4571d4 && pe.call(0x45764c) == 0x46c9cc && pe.call(0x46c9cf) == 0x4ae5b0 &&
            pe.call(0x45765f) == 0x45727c,"prefix resets, draws Rand15 through wrapper, then exits scope at crossings");
    require(pe.byte(0x45765c) == 32 && pe.word(0x4ae5b9) == 22695477u && pe.word(0x4ae5d2) == 32767u,
            "original32 iteration limit and Rand15 multiplier/mask support the calculated sequence");
    require(pe.byte(0x4521a4) == 0x0f && pe.byte(0x4521a5) == 0xbe && pe.byte(0x4521a7) == 0x0e,
            "original road load is MOVSX byte from site+2+0xe");
    require(pe.call(0x4561d5) == 0x450dd0 && pe.call(0x4561e5) == 0x45209c && pe.call(0x4561ec) == 0x4512a8,
            "begin seeds private RNG and chooses actual grid leaves");
}
void realSamples(const std::filesystem::path& directory) {
    size_t documents = 0, grids = 0; auto d = std::make_unique<save::Document>(); save::Error e;
    auto inspect = [&] {
        const auto archive = bytes(*d); CombatPreparationState initial;
        CombatPhasePreparationReport prefix; ok(prepareCombatPhase(*d,initial,rng(),prefix,e),e);
        require(prefix.after.turn == d->options.turn,"real sample prefix snapshots the actual turn");
        const size_t count = std::min<size_t>(4,d->territories.size());
        for (size_t i = 0; i < count; ++i) {
            const auto id = uint32_t(i+1); const auto& t = d->territories[i].data;
            const auto a = begin(*d,prefix.after,{id,int16_t(t.owner),-1,1});
            const auto b = begin(*d,prefix.after,{id,int16_t(t.owner),-1,1});
            require(a == b,"real site grid preparation is deterministic");
            for (size_t j = 0; j < 36; ++j) {
                require(a.after.battles[0].roads[j] == std::bit_cast<int8_t>(t.sites[j].unk_05[11]),
                        "real source site road byte is sign-extended");
                const auto terrain = t.sites[j].terrainFlags == 0xff ? 6 : t.sites[j].terrainFlags&15;
                require((a.after.grid.flags[cell(int(j%6)*3+2,int(j/6)*3+2)]&0xf0) == uint8_t(terrain<<4),
                        "real source site terrain applies to full3x3 block");
            }
            ++grids;
        }
        require(bytes(*d) == archive,"real documents remain byte-exact"); ++documents;
    };
    ok(save::readDocument(directory/"TUTORIAL.SAV",*d,e),e); inspect();
    HdxArchive archive; std::string why; require(archive.open((directory/"LEVELS").string(),&why),why.c_str());
    for (const auto& entry : archive.entries()) { ok(save::readScenario(directory/"LEVELS",entry.name,*d,e),e); inspect(); }
    require(documents == 43 && grids > 0,"tutorial and all42 campaign scenarios cover the real preparation corpus");
    std::cout << "combat preparation: " << documents << " real documents, " << grids << " explicit colony grids\n";
}
} // namespace
int main(int argc,char** argv) {
    try {
        std::vector<uint8_t> oldGs(sizeof(gs)),oldGg(sizeof(gg));
        std::memcpy(oldGs.data(),&gs,sizeof(gs)); std::memcpy(oldGg.data(),&gg,sizeof(gg));
        const auto seed = rtl::seed(), hi = rtl::seedHi();
        resetPools(); phasePrefix(); beginAndLimits(); gridLeaves(); gridReconstruction(); creationContinuity();
        const auto directory = argc > 1 ? std::filesystem::path(argv[1]) : std::filesystem::path("C:/GOG Games/Deadlock 2");
        originalEvidence(directory); realSamples(directory);
        require(!std::memcmp(oldGs.data(),&gs,sizeof(gs)) && !std::memcmp(oldGg.data(),&gg,sizeof(gg)) &&
                seed == rtl::seed() && hi == rtl::seedHi(),"preparation and composition isolate globals and shared RNG");
        std::cout << "combat_preparation: exact resets,32 Rand15, old slots, grid roads/terrain, composition and rollback passed\n";
        return 0;
    } catch (const std::exception& e) { std::cerr << "combat_preparation: " << e.what() << '\n'; return 1; }
}
