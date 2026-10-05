// Calculated oracles from004467e8/00416c28 plus exported assembly. These are
// not measurements from executing the original game.
#include "game/movement_next_step.h"
#include "game/data_tables.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include "game/save_files.h"
#include <algorithm>
#include <array>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <memory>
#include <stdexcept>

namespace {
using namespace dl2;
using namespace dl2::simulation;
void require(bool value, const char* message) { if (!value) throw std::runtime_error(message); }
void ok(bool value, const save::Error& error) { if (!value) throw std::runtime_error(error.message); }
std::unique_ptr<save::Document> fixture(size_t count = 5) {
    auto d = std::make_unique<save::Document>();
    std::memcpy(d->header.text,save::kHeaderText,sizeof(save::kHeaderText));
    d->header.version = kSaveVersion;
    d->world.width = d->world.height = 1;
    d->world.numTerritories = uint16_t(count);
    d->tiles.resize(1); d->territories.resize(count);
    d->options.numPlayers = 2;
    for (int p = 0; p < 7; ++p) {
        d->players[p].index = uint8_t(p); d->players[p].type = p ? 3 : 1;
        d->players[p].race = 0; d->ministerJobs[p].resize(1);
    }
    for (size_t i = 0; i < count; ++i) {
        auto& t = d->territories[i].data;
        t.index = uint16_t(i+1); t.owner = 0; t.terrain = 1;
        t.flags = 0x40002001u;
    }
    return d;
}
void edge(save::Document& d, uint32_t a, uint32_t b) {
    d.territories[a-1].data.adjacency[b/16] |= uint16_t(1u << (b%16));
    d.territories[b-1].data.adjacency[a/16] |= uint16_t(1u << (a%16));
}
void chain(save::Document& d) { for (uint32_t i = 1; i < d.territories.size(); ++i) edge(d,i,i+1); }
void defense(save::Document& d, uint32_t territory, int32_t value) {
    std::memcpy(reinterpret_cast<uint8_t*>(&d.territories[territory-1].data)+0xa58,&value,4);
}
uint32_t unit(save::Document& d, uint32_t territory, int type = 1) {
    Army a{}; a.id = uint16_t(d.armies.size()+1); a.type = uint8_t(type);
    a.unitClass = data::kUnitTypes[type].unitClass;
    a.territory.raw = a.dest.raw = a.origin.raw = territory;
    auto& head = d.territories[territory-1].data.armies;
    a.next.raw = head.raw;
    for (auto& old : d.armies) if (old.id == head.raw) old.prev.raw = a.id;
    head.raw = a.id; d.armies.push_back(a); return a.id;
}
Army& army(save::Document& d, uint32_t id) {
    for (auto& a : d.armies) if (a.id == id) return a;
    throw std::runtime_error("missing test army");
}
std::vector<uint8_t> bytes(const save::Document& d) {
    std::vector<uint8_t> result; save::Error e; ok(save::encode(d,result,e),e);
    for (const auto& record : d.territories) {
        const auto* start = reinterpret_cast<const uint8_t*>(&record.data);
        result.insert(result.end(),start+kTerritorySavedBytes,start+sizeof(Territory));
    }
    return result;
}
MovementNextStepRequest request(uint32_t anchor = 5) {
    return {1,anchor,0,50,1,24}; // Scout permits hostile candidates for ranking tests.
}
MovementNextStepContext context(const save::Document& d) {
    MovementNextStepContext c;
    c.distancePlayer = 0; c.territories.resize(d.territories.size()+1);
    c.territories[0].flags = 0xaabbffffu;
    for (size_t i = 1; i < c.territories.size(); ++i) {
        c.territories[i].flags = d.territories[i-1].data.flags | 0x4000u;
        c.territories[i].distance = int16_t(100-i);
    }
    c.traceBuffer = std::vector<uint32_t>(50,0xdeadbeefu);
    return c;
}
MovementNextStepReport query(const save::Document& d, const MovementNextStepRequest& r,
                             const MovementNextStepContext& c) {
    const auto original = bytes(d);
    const auto originalScratch = c.territories; const auto originalTrace = c.traceBuffer;
    save::Error e{save::ErrorCode::Io,99,"previous"}; MovementNextStepReport out;
    ok(selectMovementNextStep(d,r,c,out,e),e);
    require(e.code == save::ErrorCode::None && e.offset == 0 && e.message.empty(),"next-step success clears stale error");
    require(bytes(d) == original && c.territories == originalScratch && c.traceBuffer == originalTrace,
            "next-step query preserves document and all caller scratch/trace data");
    for (size_t i = 0; i < c.territories.size(); ++i)
        require(out.territoriesAfter[i].distance == c.territories[i].distance,"next-step never rewrites any signed distance");
    return out;
}
std::vector<uint32_t> prefix(const MovementNextStepReport& r, size_t count) {
    require(r.traceAfter && count <= r.traceAfter->size(),"trace prefix exists");
    return {r.traceAfter->begin(),r.traceAfter->begin()+count};
}

void descentAndNativeTrace() {
    auto d = fixture(); chain(*d);
    auto req = request(); req.unitType = 1; req.range = 1;
    auto c = context(*d);
    for (size_t i = 1; i < c.territories.size(); ++i) c.territories[i].distance = int16_t(5-i);
    auto r = query(*d,req,c);
    require(r.nextTerritory == 4 && r.iterations == 3 && r.rankingImprovements == 3 && r.finalRanking == 22 &&
            r.creationQueryCount == 4 && r.scoutQueryCount == 3,
            "descent scans closer nodes until one is within range and creatable, with exact repeated access call");
    require(prefix(r,5) == std::vector<uint32_t>{2,3,4,0,0xdeadbeefu},"normal trace appends successive improvements and one terminator");
    require(r.traceWrites == std::vector<MovementNextStepTraceWrite>{{0,2},{1,3},{2,4},{3,0}},"trace writes preserve original order");
    for (size_t i = 1; i <= 5; ++i)
        require(bool(r.territoriesAfter[i].flags & 0x2000u) == (i <= 3),"only entered nodes are marked; returned candidate is not entered");
    require(r.territoriesAfter[0].flags == (c.territories[0].flags & ~0x2000u) &&
            (r.territoriesAfter[5].flags & 0x4000u),"sentinel and other-player flags are retained except queried-player clearing");

    req.range = 0;
    r = query(*d,req,c);
    require(r.nextTerritory == -1 && r.iterations == 4 && r.creationQueryCount == 3 && r.finalRanking == 0 &&
            prefix(r,4) == std::vector<uint32_t>{0,3,4,0xdeadbeefu},
            "failure after descent writes only trace word0, preserving previously written tail");
    require(r.traceWrites.back() == MovementNextStepTraceWrite{0,0},"failure overwrite is visible in native write log");
    req.flag = 0; req.range = 4;
    r = query(*d,req,c);
    require(r.nextTerritory == 1 && r.startWithinRange && !r.destinationAdjacent && r.iterations == 1 &&
            r.creationQueryCount == 2 && prefix(r,4) == std::vector<uint32_t>{1,2,0,0xdeadbeefu},
            "zero flag and inclusive range return origin after scanning and replace first three trace words");
    require(r.traceWrites == std::vector<MovementNextStepTraceWrite>{{0,2},{0,1},{1,2},{2,0}},"origin-in-range rewrites an intermediate ranking write");
    auto noTrace = c; noTrace.traceBuffer.reset();
    auto silent = query(*d,req,noTrace);
    require(silent.nextTerritory == r.nextTerritory && silent.territoriesAfter == r.territoriesAfter &&
            !silent.traceAfter && silent.traceWrites.empty() && silent.rankingImprovements == r.rankingImprovements,
            "null native trace pointer leaves selection and scratch unchanged");
    req.flag = -1;
    require(!query(*d,req,c).startWithinRange,"any nonzero signed flag disables origin-in-range branch");
}

void rankingAndTies() {
    auto d = fixture(); edge(*d,1,2); edge(*d,1,3); edge(*d,1,4);
    auto req = request(); auto c = context(*d); c.territories[1].distance = 100;
    c.territories[2].distance = 20; c.territories[3].distance = 10; c.territories[4].distance = 15;
    d->territories[1].data.owner = 1; d->territories[2].data.owner = -1;
    auto r = query(*d,req,c);
    require(r.nextTerritory == 4 && r.finalRanking == 20 && r.rankingImprovements == 3 &&
            prefix(r,4) == std::vector<uint32_t>{2,3,4,0},
            "ranking6->14->20 prefers farther owned node over nearer neutral, preserving interim choices not a route");
    require(!(d->territories[1].data.adjacency[0] & (1u<<3)),"intermediate trace entries intentionally need not be adjacent");
    c.territories[2].distance = c.territories[3].distance = c.territories[4].distance = 10;
    r = query(*d,req,c);
    require(r.nextTerritory == 4 && r.finalRanking == 21,"equal-to-current-best distance contributes bit1 for later stronger ownership rank");
    d->territories[1].data.owner = d->territories[2].data.owner = 0;
    c.territories[4].distance = 9;
    r = query(*d,req,c);
    require(r.nextTerritory == 2 && r.finalRanking == 22 && r.rankingImprovements == 1 &&
            prefix(r,2) == std::vector<uint32_t>{2,0},
            "equal rank preserves first ascending candidate EVEN when a later candidate is closer");
    c.territories[2].distance = 100;
    c.territories[3].distance = 101;
    r = query(*d,req,c);
    require(r.nextTerritory == 4 && r.creationQueryCount == 2,"only strictly closer-than-current neighbors reach access/ranking");

    // More than three native improvement writes survive the fast-path rewrite.
    d = fixture(6); for (uint32_t i = 2; i <= 5; ++i) edge(*d,1,i);
    req = request(6); req.flag = 0; req.range = 100; c = context(*d);
    c.territories[1].distance = 100;
    for (uint32_t i = 2; i <= 5; ++i) c.territories[i].distance = 10;
    d->territories[1].data.owner = 1; d->territories[1].data.terrain = 0; // Scout cannot board, rank2.
    d->territories[2].data.owner = 1; // rank5 (equal+access).
    d->territories[3].data.owner = -1; // rank13.
    d->territories[4].data.owner = 0; // rank21.
    r = query(*d,req,c);
    require(r.rankingImprovements == 4 && r.nextTerritory == 1 &&
            prefix(r,5) == std::vector<uint32_t>{1,5,0,5,0xdeadbeefu},
            "native tail retains fourth interim selection after fast-path terminator at index2");
    require(r.traceWrites.size() == 7 && r.traceWrites[3] == MovementNextStepTraceWrite{3,5},
            "all four intermediate writes and three overwrites are observable");
}

void neutralScoutAndPacts() {
    auto d = fixture(3); edge(*d,1,2);
    auto req = request(3); req.unitType = 1;
    auto c = context(*d); c.territories[1].distance = 100; c.territories[2].distance = 10;
    d->territories[1].data.owner = -1; d->players[0].type = 3;
    for (int32_t value : {1,-1,256,INT32_MIN}) {
        defense(*d,2,value);
        require(query(*d,req,c).nextTerritory == -1,"neutral AI preference needs entire defense int32 to be zero, not byte/sign checks");
    }
    defense(*d,2,0);
    require(query(*d,req,c).finalRanking == 14,"AI grants neutral bit8 when current defense scratch is exactly0");
    defense(*d,2,9);
    for (int playerType : {0,1,2,255}) {
        d->players[0].type = uint8_t(playerType);
        require(query(*d,req,c).nextTerritory == 2,"signed player types below3 allow neutral bit8 despite nonzero defense");
    }
    d->players[0].type = 3; req.unitType = 24;
    require(query(*d,req,c).finalRanking == 6,"Scout can enter neutral AI candidate without neutral bonus");

    d->territories[1].data.owner = 1; req.unitType = 1;
    require(query(*d,req,c).nextTerritory == -1,"ordinary land unit without scout ability zeros hostile rank below8");
    for (int16_t racial : {int16_t(1),int16_t(-1)}) {
        d->raceStats.v[54][0] = racial;
        for (int type : {1,26}) {
            req.unitType = type;
            require(query(*d,req,c).nextTerritory == 2,"nonzero saved racial54 allows canonical infantry and medic scouting");
        }
        req.unitType = 5;
        require(query(*d,req,c).nextTerritory == -1,"racial scout bonus does not apply to canonical cannon class2");
    }
    d->raceStats.v[54][0] = 0; d->techs[43].knownMask = 1; d->players[0].index = 6;
    for (int type : {1,26}) {
        req.unitType = type;
        require(query(*d,req,c).nextTerritory == 2,"tech43 uses requested player slot, not saved Player.index");
    }
    req.unitType = 12; d->territories[1].data.terrain = 0;
    require(query(*d,req,c).nextTerritory == 2,"tech43 grants scouting to canonical sea transport on sea");
    d->techs[43].knownMask = 2;
    require(query(*d,req,c).nextTerritory == -1,"other player's technology does not grant scouting");
    d->territories[1].data.terrain = 1; d->players[0].race = 127;
    for (int type : {9,11,28}) {
        req.unitType = type;
        const auto air = query(*d,req,c);
        require(air.nextTerritory == 2 && air.scoutQueryCount == 0,"canonical air domain bypasses scout helper and invalid racial address");
    }
    req.unitType = 24;
    require(query(*d,req,c).nextTerritory == 2,"explicit Scout bypasses racial-word read in existing helper");
    d->players[0].race = 0; req.unitType = 1;
    d->options.allowAlliances = 1;
    for (uint32_t mask : {2u,0x10u,0x11u}) {
        d->players[0].relations[1] = mask;
        require(query(*d,req,c).finalRanking == 22,"effective transit pact adds16 and avoids low-rank scout veto");
    }
    d->players[0].relations[1] = 0; d->players[1].relations[0] = 2;
    require(query(*d,req,c).nextTerritory == -1,"pact preference is directional");
    d->players[0].relations[1] = 1; req.unitType = 24;
    require(query(*d,req,c).nextTerritory == 2,"selector does not invent a war-pact veto absent from004467e8");
}

void accessAndEndpoints() {
    auto d = fixture(4); edge(*d,1,2); edge(*d,2,3);
    auto req = request(4); req.unitType = 1;
    auto c = context(*d); c.territories[1].distance = 100; c.territories[2].distance = 10; c.territories[3].distance = 5;
    d->territories[1].data.terrain = 0;
    auto r = query(*d,req,c);
    require(r.nextTerritory == 3 && r.iterations == 2 && r.creationQueryCount == 4 &&
            prefix(r,3) == std::vector<uint32_t>{2,3,0},
            "uncreatable owned candidate can win rank18, but descent continues until a creatable landing");
    const auto moving = unit(*d,1,1), ship = unit(*d,2,12);
    army(*d,moving).job = 1; army(*d,ship).job = 2;
    c.creation.movingArmyId = moving; d->players[0].type = 3;
    require(query(*d,req,c).nextTerritory == 3,"canCreateArmy reuses moving AI job filter rather than assuming all carriers available");
    army(*d,ship).job = 1;
    require(query(*d,req,c).nextTerritory == 2,"matching moving AI and ship job stops at accessible sea candidate");
    std::array<uint32_t,3> cargo{};
    for (size_t i = 0; i < cargo.size(); ++i) { cargo[i] = unit(*d,2,1); army(*d,ship).cargo[i].raw = cargo[i]; }
    require(query(*d,req,c).nextTerritory == 3,"full three-slot transport forces further descent");

    d = fixture(2); edge(*d,1,2); req = request(2); req.flag = 0; req.range = 0;
    c = context(*d); c.territories[1].distance = 0; c.territories[2].distance = 32767;
    c.territories[2].flags |= 0x100;
    r = query(*d,req,c);
    require(r.startWithinRange && r.destinationAdjacent && r.nextTerritory == 1 &&
            r.creationQueryCount == 0 && prefix(r,3) == std::vector<uint32_t>{1,2,0},
            "fast destination adjacency is recorded before exclusion and distance checks; destination is never ranked");
    req.flag = 1;
    r = query(*d,req,c);
    require(!r.destinationAdjacent && r.nextTerritory == -1,"destination-only adjacency yields native-1 when fast branch disabled");
    d->territories[0].data.adjacency[0] = d->territories[1].data.adjacency[0] = 0;
    req.flag = 0;
    require(prefix(query(*d,req,c),3) == std::vector<uint32_t>{1,0,0},"origin within range returns itself with null successor when no candidate exists");
}

void signedDistancesAndAdjacency() {
    auto d = fixture(4); edge(*d,1,2); edge(*d,2,3); edge(*d,3,1);
    auto req = request(4); req.unitType = 1; req.range = -2;
    auto c = context(*d);
    c.territories[1].distance = 0; c.territories[2].distance = -1; c.territories[3].distance = -32768;
    auto r = query(*d,req,c);
    require(r.nextTerritory == 3 && r.iterations == 2 && prefix(r,3) == std::vector<uint32_t>{2,3,0},
            "signed distance ordering preserves negative range and INT16_MIN while equal rank keeps first branch");
    req.range = INT32_MIN;
    r = query(*d,req,c);
    require(r.nextTerritory == -1 && r.iterations == 3,"strict distance descent and marks terminate cycles even below INT16_MIN range");
    d->territories[0].data.adjacency[6] |= uint16_t(1u<<15);
    require(query(*d,req,c).nextTerritory == -1,"native explicit upper-bound check ignores adjacency111 above represented N");
    c.territories[2].flags |= 0x100;
    req.range = 0;
    r = query(*d,req,c);
    require(r.nextTerritory == 3 && r.rankingImprovements == 1,"candidate exclusion uses explicit scratch flags rather than document flags");
    d = fixture(17); edge(*d,1,15); edge(*d,1,16);
    req = request(17); c = context(*d); c.territories[15].distance = c.territories[16].distance = 1;
    require(query(*d,req,c).nextTerritory == 15,"ascending adjacency order preserves highbit15 before next WORD bit16");
    req.player = c.distancePlayer = 6;
    for (auto& t : d->territories) t.data.owner = 6;
    r = query(*d,req,c);
    require((r.territoriesAfter[1].flags & 0x80000u) && (r.territoriesAfter[1].flags & 0x2000u),
            "player6 uses exact mark0x80000 and does not clear player0 marks");
}

void errorsAndTransactions() {
    auto d = fixture(); chain(*d);
    auto req = request(); auto c = context(*d); req.range = 97;
    auto previous = query(*d,req,c), result = previous;
    save::Error e;
    auto fails = [&](const MovementNextStepRequest& r, const MovementNextStepContext& ctx) {
        require(!selectMovementNextStep(*d,r,ctx,result,e) && result == previous && e.code != save::ErrorCode::None,
                "next-step error retains prior report, trace writes, flags and native result");
    };
    for (int value : {-1,7}) { auto bad = req; bad.player = value; fails(bad,c); }
    for (int type : {0,-1,39,INT32_MAX}) { auto bad = req; bad.unitType = type; fails(bad,c); }
    for (uint32_t index : {0u,6u,UINT32_MAX}) {
        auto bad = req; bad.origin = index; fails(bad,c);
        bad = req; bad.destination = index; fails(bad,c);
    }
    auto bad = c; bad.distancePlayer = 1; fails(req,bad);
    bad = c; bad.territories.pop_back(); fails(req,bad);
    bad = c; bad.territories.push_back({}); fails(req,bad);
    bad = c; bad.creation.movingArmyId = 333; fails(req,bad);
    // Two choices fit; the terminator at word2 does not.
    bad = c; bad.traceBuffer = std::vector<uint32_t>(2,777);
    fails(req,bad);
    require(e.code == save::ErrorCode::Limit,"trace capacity failure is explicit, not silent truncation");
    req.flag = 0; req.range = 100; bad = c; bad.traceBuffer = std::vector<uint32_t>(2,888);
    fails(req,bad); // Interim write and two final writes succeed before final word2 fails.
    const auto before = bytes(*d);
    require(bad.traceBuffer && *bad.traceBuffer == std::vector<uint32_t>{888,888} && bytes(*d) == before,
            "late trace overflow leaves caller buffer and document untouched");
    d->territories[0].data.adjacency[0] |= 1;
    fails(req,c);
    d->territories[0].data.adjacency[0] &= uint16_t(0xfffeu);
    d->players[0].race = 127; req.unitType = 1;
    fails(req,c); // Invalid flat racial address is reached even for an owned rank>=8.
    d->players[0].race = 0;
    unit(*d,1,1); d->territories[0].data.armies.raw = 0;
    fails(req,c); // Archive is valid, access helper requires complete live lists.
    d->header.version = 0; fails(req,c);
    require(e.code == save::ErrorCode::UnsupportedVersion,"structural codec error survives query boundary");
}

void realPipeline(const std::filesystem::path& directory) {
    auto d = std::make_unique<save::Document>(); save::Error e;
    ok(save::readDocument(directory/"TUTORIAL.SAV",*d,e),e);
    size_t count = 0;
    for (const auto& a : d->armies) {
        MovementPathRequest distances;
        distances.origin = a.territory.raw; distances.player = a.owner;
        distances.domain = data::kUnitTypes[a.type].domain; distances.range = 100;
        distances.markMask = 0x2000u << unsigned(a.owner);
        MovementPathContext pc; pc.creation.movingArmyId = a.id;
        MovementPathReport paths;
        ok(findMovementPaths(*d,distances,pc,paths,e),e);
        uint32_t goal = distances.origin; int best = -1;
        for (uint32_t i = 1; i < paths.territories.size(); ++i)
            if (paths.territories[i].distance < 1000 && paths.territories[i].distance > best) {
                goal = i; best = paths.territories[i].distance;
            }
        MovementNextStepContext c; c.distancePlayer = a.owner; c.territories = paths.territories; c.creation.movingArmyId = a.id;
        const MovementNextStepRequest req{goal,distances.origin,a.owner,data::kUnitTypes[a.type].moves,0,a.type};
        const auto first = query(*d,req,c), second = query(*d,req,c);
        require(first == second && (first.nextTerritory == -1 ||
                (first.nextTerritory > 0 && size_t(first.nextTerritory) <= d->territories.size())),
                "real path-search/next-step pipeline is deterministic and returns represented index or-1");
        ++count;
    }
    require(count != 0,"tutorial includes real movement-query units");
    std::cout << "movement next-step real pipeline: " << count << " units\n";
}
} // namespace

int main(int argc, char** argv) {
    try {
        std::vector<uint8_t> globals(sizeof(gs)), gameGlobals(sizeof(gg));
        std::memcpy(globals.data(),&gs,sizeof(gs)); std::memcpy(gameGlobals.data(),&gg,sizeof(gg));
        const auto seed = rtl::seed(), seedHi = rtl::seedHi();
        descentAndNativeTrace(); rankingAndTies(); neutralScoutAndPacts(); accessAndEndpoints();
        signedDistancesAndAdjacency(); errorsAndTransactions();
        realPipeline(argc > 1 ? std::filesystem::path(argv[1]) : std::filesystem::path("C:/GOG Games/Deadlock 2"));
        require(!std::memcmp(globals.data(),&gs,sizeof(gs)) && !std::memcmp(gameGlobals.data(),&gg,sizeof(gg)) &&
                seed == rtl::seed() && seedHi == rtl::seedHi(),"next-step selection isolates globals and RNG");
        std::cout << "movement_next_step: ranking, exact trace writes, descent, scout/access rules and rollback passed\n";
        return 0;
    } catch (const std::exception& e) { std::cerr << "movement_next_step: " << e.what() << '\n'; return 1; }
}
