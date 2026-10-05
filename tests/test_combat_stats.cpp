// Oracles below are calculated from the listed decompiled leaves, not captured
// from an execution of DEADLOCK.EXE. Real SAV tests exercise input compatibility.
#include "game/combat_stats.h"
#include "game/data_tables.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include "game/save_files.h"
#include <algorithm>
#include <array>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>

namespace {
using namespace dl2;
using namespace dl2::simulation;
void require(bool value, const char* message) { if (!value) throw std::runtime_error(message); }
void ok(bool value, const save::Error& error) { if (!value) throw std::runtime_error(error.message); }
std::unique_ptr<save::Document> fixture() {
    auto d = std::make_unique<save::Document>();
    std::memcpy(d->header.text, save::kHeaderText, sizeof(save::kHeaderText));
    d->header.version = kSaveVersion;
    d->world.width = d->world.height = 1;
    d->world.numTerritories = 1;
    d->options.numPlayers = 2;
    d->options.localPlayer = 0;
    d->territories.resize(1);
    d->territories[0].data.index = 1;
    d->territories[0].data.owner = 0;
    d->territories[0].data.terrain = 1;
    d->tiles.resize(1);
    d->tiles[0].territory = 1;
    for (size_t p = 0; p < 7; ++p) {
        d->players[p].index = uint8_t(p);
        d->players[p].race = int8_t(p);
        d->players[p].type = p ? 3 : 1;
        d->options.playerSkill[p] = 2;
        d->ministerJobs[p].resize(1);
    }
    Army a{};
    a.id = 100;
    a.type = 1;
    a.unitClass = 9; // Deliberately stale; queries must use the canonical class1.
    a.owner = 0;
    a.territory.raw = a.dest.raw = a.origin.raw = 1;
    a.unk_44.raw = 0xdeadbeef; // Opaque historical address must remain inert.
    d->armies.push_back(a);
    d->territories[0].data.armies.raw = a.id;
    return d;
}
std::vector<uint8_t> bytes(const save::Document& d) {
    std::vector<uint8_t> result;
    save::Error e;
    ok(save::encode(d, result, e), e);
    return result;
}
CombatStatsContext context(const save::Document& d) {
    CombatStatsContext c;
    c.combatants.resize(1);
    save::Error e;
    ok(projectArmyCombatant(d, 100, c.combatants[0], e), e);
    return c;
}
CombatStats query(const save::Document& d, const CombatStatsContext& c) {
    CombatStats result;
    save::Error e{save::ErrorCode::Io, 99, "old error"};
    ok(combatStats(d, c, {0}, result, e), e);
    require(e.code == save::ErrorCode::None && e.message.empty(), "aggregate success clears old error");
    return result;
}
int32_t stat(const save::Document& d, const CombatStatsContext& c, CombatStat s) {
    int32_t result = 8877;
    save::Error e{save::ErrorCode::Io, 99, "old error"};
    ok(combatStat(d, c, {0}, s, result, e), e);
    require(e.code == save::ErrorCode::None && e.message.empty(), "scalar success clears old error");
    return result;
}
void projectionAndExperience() {
    auto d = fixture();
    auto& a = d->armies[0];
    const std::array<int, 10> experience{-32768, -1, 0, 99, 100, 400, 401, 1000, 1001, 32767};
    const std::array<int, 10> levels{0, 0, 0, 0, 1, 1, 2, 2, 2, 2};
    save::Error e;
    Combatant projection;
    for (size_t i = 0; i < experience.size(); ++i) {
        a.experience = int16_t(experience[i]);
        a.moves = 4;
        a.strength = 77;
        a.health = 88;
        a.unk_2c = -123;
        for (unsigned flags = 0; flags < 8; ++flags) {
            d->players[0].foodFlags = uint8_t(flags);
            projection.type = 38;
            projection.target = CombatantRef{100};
            e = {save::ErrorCode::Io, 1, "previous"};
            ok(projectArmyCombatant(*d, 100, projection, e), e);
            require(projection.type == 1 && projection.currentOwner == 0 && projection.originalOwner == 0 &&
                    projection.orders == 4 && projection.experience == std::min(experience[i], 1000) &&
                    projection.supplyPenalty == bool(flags & 3u) && !projection.target &&
                    e.code == save::ErrorCode::None, "projection copies exact offsets, caps only upper XP, resets target, and tests supply bits0/1");
            CombatStatsContext c{{projection}};
            const auto r = query(*d, c);
            require(combatExperienceLevel(experience[i]) == levels[i] && r.accuracy == 50 + 15 * levels[i],
                    "experience thresholds99/100/400/401, negative and upper projection bound");
            require(r.attack == (flags & 3u ? 1 : 2) && r.defense == (flags & 3u ? 2 : 5) &&
                    r.speed == 8 && r.rateOfFire == 6 && r.squaredRange == 9,
                    "supply affects only attack/defense; orders4 affect speed/cadence; XP affects only accuracy");
        }
    }
    require(combatExperienceLevel(INT32_MIN) == 0 && combatExperienceLevel(INT32_MAX) == 2,
            "experience leaf preserves its full signed32 input domain");
    const auto snapshot = bytes(*d);
    const auto projected = projection;
    require(!projectArmyCombatant(*d, 0, projection, e) && projection == projected && bytes(*d) == snapshot,
            "projection missing ID rollback");
    for (int type : {39, 127, 128, 255}) {
        a.type = uint8_t(type);
        require(!projectArmyCombatant(*d, 100, projection, e) && projection == projected,
                "projection rejects type outside canonical table including sign-extended bytes");
    }
    a.type = 1;
    for (int owner : {-128, -1, 7, 127}) {
        a.owner = int8_t(owner);
        require(!projectArmyCombatant(*d, 100, projection, e) && projection == projected,
                "projection invalid owner leaves output intact");
    }
}

void attackDefenseAndRows() {
    auto d = fixture();
    auto c = context(*d);
    for (int modifier : {0, 1, -1}) {
        d->raceStats.v[29][0] = int16_t(modifier);
        require(query(*d, c).attack == 2 + modifier, "LaserSquad2 with racial0/+1/-1 yields2/3/1, not a generic percentage factor");
    }
    d->raceStats.v[29][0] = 6;
    d->raceStats.v[30][0] = 3;
    d->raceStats.v[33][0] = -7;
    c.combatants[0].orders = 1;
    auto r = query(*d, c);
    require(r.attack == 6 && r.defense == 13, "nonzero negative order racial doubles first, before tenths adjustment");
    c.combatants[0].supplyPenalty = true;
    r = query(*d, c);
    require(r.attack == 3 && r.defense == 6, "supply SAR halves after racial adjustment, truncating positive odd defense");
    d->raceStats.v[29][0] = -11;
    d->raceStats.v[30][0] = -11;
    r = query(*d, c);
    require(r.attack == 1 && r.defense == 1, "negative adjusted values retain final minimum1 with signed shift");
    c.combatants[0].type = 5;
    c.combatants[0].supplyPenalty = false;
    require(query(*d, c).attack == 4, "infantry order modifiers do not double canonical cannon class2");

    // Explicit per-TYPE address mapping, independent of the implementation's
    // canonical-class switch. Covers every race and all39 table entries.
    constexpr std::array<int, 39> attackRows{-1,29,29,29,29,35,35,35,35,37,37,37,39,39,39,29,41,41,41,43,43,43,43,29,29,29,29,35,37,39,39,39,43,39,39,39,41,41,41};
    constexpr std::array<int, 39> defenseRows{-1,30,30,30,30,36,36,36,36,38,38,38,40,40,40,30,42,42,42,44,44,44,44,30,30,30,30,36,38,40,40,30,44,40,40,40,42,42,42};
    c.combatants[0].orders = 0;
    for (int row = 0; row < 64; ++row)
        for (int race = 0; race < 7; ++race) d->raceStats.v[row][race] = int16_t((row % 9) * 7 + race - 29);
    auto expected = [](int base, int modifier) {
        int64_t adjustment = int64_t(base) * modifier / 10;
        if (modifier < 0) adjustment = std::min<int64_t>(adjustment, -1);
        if (modifier > 0) adjustment = std::max<int64_t>(adjustment, 1);
        return int32_t(std::max<int64_t>(base + adjustment, 1));
    };
    for (int type = 0; type < 39; ++type) for (int race = 0; race < 7; ++race) {
        c.combatants[0].type = type;
        d->players[0].race = int8_t(race);
        r = query(*d, c);
        const auto& base = data::kUnitTypes[type];
        require(r.attack == expected(base.attack, attackRows[type] < 0 ? 0 : d->raceStats.v[attackRows[type]][race]) &&
                r.defense == expected(base.defense, defenseRows[type] < 0 ? 0 : d->raceStats.v[defenseRows[type]][race]),
                "all canonical types/races select saved attack and defense rows including SeaColonizer defense30");
    }
    // Extreme signed16 modifiers preserve integer arithmetic and final bounds.
    d = fixture(); c = context(*d); c.combatants[0].type = 37;
    d->raceStats.v[41][0] = 32767;
    require(query(*d,c).attack == 163885, "largest positive mine attack modifier uses signed tenths");
    d->raceStats.v[41][0] = -32768;
    require(query(*d,c).attack == 1, "lowest attack modifier safely clamps after signed arithmetic");
}

void ordersTechnologyAndOwners() {
    auto d = fixture();
    auto c = context(*d);
    auto& a = c.combatants[0];
    a.currentOwner = 1;
    a.originalOwner = 0;
    d->players[1].race = 6;
    d->options.playerSkill[1] = 4;
    d->raceStats.v[45][6] = 300;
    d->raceStats.v[46][6] = 100;
    d->techs[27].knownMask = 1; // Original owner only: deliberately not active.
    require(query(*d,c) == CombatStats{2,5,4,5,9,50}, "racial and skill owner is original; technology owner is current");
    d->techs[27].knownMask = 2;
    require(query(*d,c) == CombatStats{2,5,3,4,9,50}, "technology27 independently reduces speed25% and cadence10% with minimum1");
    a.orders = 4;
    require(query(*d,c) == CombatStats{2,5,6,5,9,50}, "order4 doubles speed before tech and increments cadence after tech");
    a.orders = 2;
    d->raceStats.v[34][0] = -1;
    d->raceStats.v[46][0] = 1;
    require(query(*d,c) == CombatStats{4,10,1,4,2,100}, "order2 racial uses boolean, signed division5/2 before tech, range2 and perfect accuracy");
    a.supplyPenalty = true;
    require(query(*d,c) == CombatStats{2,5,1,4,2,100}, "supply remains independent of order2 speed/range/accuracy");
    d->options.playerSkill[0] = 255;
    require(stat(*d,c,CombatStat::Accuracy) == 100, "order2 accuracy returns before invalid skill lookup");
    a.orders = 0;
    d->options.playerSkill[0] = 0;
    d->raceStats.v[45][0] = -32768;
    require(stat(*d,c,CombatStat::Accuracy) == -32728, "accuracy has no invented minimum0");
    d->raceStats.v[45][0] = 32767;
    require(stat(*d,c,CombatStat::Accuracy) == 100, "accuracy upper bound100");
    d->raceStats.v[45][0] = 0;
    for (int skill = 0; skill < 5; ++skill) {
        d->options.playerSkill[0] = uint8_t(skill);
        require(stat(*d,c,CombatStat::Accuracy) == 40 + 5 * skill, "all five original skill modifiers");
    }
    a.type = 9;
    d->raceStats.v[46][0] = 0;
    require(stat(*d,c,CombatStat::Speed) == 0, "technology minimum1 reduces speed1 to0");
    a.type = 19;
    a.orders = 4;
    require(stat(*d,c,CombatStat::Speed) == 0, "negative fort speed stays within final minimum0 after orders and technology");
    a.type = 16;
    require(stat(*d,c,CombatStat::RateOfFire) == -1, "missile cadence-1 applies tech then order4 before final minimum-1");
    d->techs[27].knownMask = 0;
    require(stat(*d,c,CombatStat::RateOfFire) == 0, "missile cadence order4 alone is0, not an invented exclusion");
}

void commandCorpsAndTargets() {
    auto d = fixture();
    auto c = context(*d);
    c.combatants[0].type = 15;
    c.combatants.push_back(Combatant{});
    c.combatants[1].type = 1;
    c.combatants[0].target = CombatantRef{1};
    d->raceStats.v[31][0] = 1;
    auto r = query(*d,c);
    require(r.squaredRange == 81 && r.rateOfFire == 10, "Command row31 squares base range9 and doubles cadence5");
    d->raceStats.v[32][0] = 3;
    r = query(*d,c);
    require(r.squaredRange == 9 && r.rateOfFire == 10, "Command row32 replaces range then row31 squares it, cadence doubles only once");
    d->raceStats.v[31][0] = 0;
    require(query(*d,c).squaredRange == 3, "Command row32 alone returns unsquared replacement");
    d->raceStats.v[32][0] = -3;
    require(query(*d,c).squaredRange == 0 && query(*d,c).rateOfFire == 10, "negative row32 predicates double cadence but range lower-clamps");
    d->raceStats.v[31][0] = -2;
    require(query(*d,c).squaredRange == 9, "negative nonzero row31 still squares negative replacement");
    for (int value : {-32768, 32767}) {
        d->raceStats.v[32][0] = int16_t(value);
        require(query(*d,c).squaredRange == int64_t(value) * value, "range square is defined for both signed16 extrema");
    }
    d->raceStats.v[32][0] = 7;
    for (int excluded : {16,17,18,19,20,21,22,32,36}) {
        c.combatants[1].type = excluded;
        r = query(*d,c);
        require(r.squaredRange == 9 && r.rateOfFire == 5, "all canonical missile and fortress targets exclude both Command leaves");
    }
    c.combatants[1].type = 23;
    require(query(*d,c).squaredRange == 81 && query(*d,c).rateOfFire == 10, "militia excludes row32 only, retaining row31");
    d->raceStats.v[31][0] = 0;
    require(query(*d,c).squaredRange == 9 && query(*d,c).rateOfFire == 5, "militia alone cannot trigger row32");
    c.combatants[1].type = 1;
    c.combatants[1].currentOwner = -1;
    c.combatants[1].originalOwner = 99;
    c.combatants[1].target = CombatantRef{999};
    require(query(*d,c).squaredRange == 7, "target lookup reads its type only, ignoring unaccessed owner and relationship");
    c.combatants[0].target = CombatantRef{0};
    require(query(*d,c).squaredRange == 7, "self target is a finite typed reference, no graph recursion");
    c.combatants[0].target.reset();
    require(query(*d,c).squaredRange == 9, "null target disables Command bonuses");
    c.combatants[0].target = CombatantRef{999};
    for (int otherCommand : {28,33}) {
        c.combatants[0].type = otherCommand;
        require(query(*d,c).squaredRange == data::kUnitTypes[otherCommand].range,
                "Air/Sea Command do not inherit the type15 effect or dereference target");
    }
}

void transactionsAndPurity() {
    auto d = fixture();
    auto c = context(*d);
    const auto original = bytes(*d);
    const auto beforeContext = c;
    auto result = query(*d,c);
    const auto previous = result;
    save::Error e;
    int32_t scalar = 789;
    d->options.playerSkill[0] = 255;
    require(!combatStats(*d,c,{0},result,e) && result == previous && e.code == save::ErrorCode::InvalidState,
            "late accuracy failure cannot publish earlier attack/defense/speed results");
    require(stat(*d,c,CombatStat::Attack) == 2, "scalar attack does not read accuracy-only skill");
    d->options.playerSkill[0] = 2;
    c.combatants[0].type = 15;
    c.combatants[0].target = CombatantRef{9};
    require(!combatStats(*d,c,{0},result,e) && result == previous, "late invalid Command target rolls back aggregate");
    require(stat(*d,c,CombatStat::Attack) == 2 && stat(*d,c,CombatStat::Speed) == 6,
            "attack/speed do not read Command target");
    require(!combatStat(*d,c,{0},CombatStat::SquaredRange,scalar,e) && scalar == 789,
            "scalar invalid target preserves previous output");
    c = beforeContext;
    for (int badType : {-1,39,INT32_MIN,INT32_MAX}) {
        c.combatants[0].type = badType;
        require(!combatStats(*d,c,{0},result,e) && result == previous, "invalid signed32 canonical type rollback");
    }
    c = beforeContext;
    for (int badOwner : {-1,7,INT32_MIN,INT32_MAX}) {
        c.combatants[0].currentOwner = badOwner;
        require(!combatStats(*d,c,{0},result,e) && result == previous, "invalid current owner rollback");
        c.combatants[0].currentOwner = 0;
        c.combatants[0].originalOwner = badOwner;
        require(!combatStats(*d,c,{0},result,e) && result == previous, "invalid original owner rollback");
        c.combatants[0].originalOwner = 0;
    }
    for (int race : {-1,7,127}) {
        d->players[0].race = int8_t(race);
        require(!combatStats(*d,c,{0},result,e) && result == previous, "invalid accessed race rollback");
    }
    d->players[0].race = 0;
    require(!combatStat(*d,c,{0},CombatStat(255),scalar,e) && scalar == 789, "invalid stat selector rollback");
    require(!combatStats(*d,c,{1},result,e) && result == previous, "missing combatant rollback");
    require(!combatStats(*d,c,{std::numeric_limits<size_t>::max()},result,e) && result == previous,
            "maximum reference rejected without arithmetic overflow");
    d->header.version = 0;
    require(!combatStats(*d,c,{0},result,e) && result == previous && e.code == save::ErrorCode::UnsupportedVersion,
            "document validation error survives with untouched report");
    d->header.version = kSaveVersion;
    require(query(*d,c) == previous && c == beforeContext && bytes(*d) == original,
            "queries and all failed calls preserve inputs and clear old errors on subsequent success");
}

void realSample(const std::filesystem::path& directory) {
    auto d = std::make_unique<save::Document>();
    save::Error e;
    ok(save::readDocument(directory / "TUTORIAL.SAV", *d, e), e);
    const auto before = bytes(*d);
    CombatStatsContext c;
    for (const auto& a : d->armies) {
        Combatant projection;
        ok(projectArmyCombatant(*d,a.id,projection,e),e);
        c.combatants.push_back(projection);
    }
    require(!c.combatants.empty(), "real tutorial fixture has armies");
    const auto contextBefore = c;
    const std::array<CombatStat,6> selectors{CombatStat::Attack,CombatStat::Defense,CombatStat::Speed,
                                          CombatStat::RateOfFire,CombatStat::SquaredRange,CombatStat::Accuracy};
    for (size_t i = 0; i < c.combatants.size(); ++i) {
        CombatStats first, second;
        ok(combatStats(*d,c,{i},first,e),e);
        ok(combatStats(*d,c,{i},second,e),e);
        require(first == second, "real sample query reproducibility");
        const std::array<int32_t,6> values{first.attack,first.defense,first.speed,first.rateOfFire,first.squaredRange,first.accuracy};
        for (size_t j = 0; j < selectors.size(); ++j) {
            int32_t value = 0;
            ok(combatStat(*d,c,{i},selectors[j],value,e),e);
            require(value == values[j], "real sample scalar/aggregate agreement");
        }
    }
    require(c == contextBefore && bytes(*d) == before, "real SAV and combat context remain byte-identical/unchanged");
    std::cout << "tutorial: " << c.combatants.size() << " army projections and stat sets checked\n";
}
} // namespace

int main(int argc, char** argv) {
    try {
        std::vector<uint8_t> globals(sizeof(gs)), gameGlobals(sizeof(gg));
        std::memcpy(globals.data(), &gs, sizeof(gs));
        std::memcpy(gameGlobals.data(), &gg, sizeof(gg));
        const auto seed = rtl::seed(), seedHi = rtl::seedHi();
        projectionAndExperience();
        attackDefenseAndRows();
        ordersTechnologyAndOwners();
        commandCorpsAndTargets();
        transactionsAndPurity();
        realSample(argc > 1 ? std::filesystem::path(argv[1]) : std::filesystem::path("C:/GOG Games/Deadlock 2"));
        require(!std::memcmp(globals.data(), &gs, sizeof(gs)) && !std::memcmp(gameGlobals.data(), &gg, sizeof(gg)) &&
                seed == rtl::seed() && seedHi == rtl::seedHi(), "all combat-stat queries isolate globals and RNG");
        std::cout << "combat_stats: projection, 39 types/7 races, exact stat rules, references, boundaries and transactions passed\n";
        return 0;
    } catch (const std::exception& e) { std::cerr << "combat_stats: " << e.what() << '\n'; return 1; }
}
