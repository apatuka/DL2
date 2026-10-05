// Expected distances below are derived from00446440's decompiled control flow
// and confirmed assembly, NOT observations of a live DEADLOCK.EXE replay.
#include "game/movement_paths.h"
#include "game/data_tables.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include "game/save_files.h"
#include "formats/hdx_archive.h"
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
std::unique_ptr<save::Document> fixture(size_t count = 3) {
    auto d = std::make_unique<save::Document>();
    std::memcpy(d->header.text, save::kHeaderText, sizeof(save::kHeaderText));
    d->header.version = kSaveVersion;
    d->world.width = d->world.height = 1;
    d->world.numTerritories = uint16_t(count);
    d->options.numPlayers = 2;
    d->options.localPlayer = 0;
    d->tiles.resize(1);
    d->territories.resize(count);
    for (int p = 0; p < 7; ++p) {
        d->players[p].index = uint8_t(p);
        d->players[p].type = p ? 3 : 1;
        d->players[p].race = int8_t(p);
        d->ministerJobs[p].resize(1);
    }
    for (size_t i = 0; i < count; ++i) {
        auto& t = d->territories[i].data;
        t.index = uint16_t(i + 1);
        t.owner = 0;
        t.terrain = 1;
        t.flags = 0x40002001u;
        for (size_t p = 0; p < 7; ++p) {
            const int16_t distance = int16_t(p ? 32767 : -32768);
            std::memcpy(reinterpret_cast<uint8_t*>(&t) + 0xa70 + p * 2, &distance, 2);
        }
    }
    return d;
}
void edge(save::Document& d, uint32_t a, uint32_t b) {
    d.territories[a - 1].data.adjacency[b / 16] |= uint16_t(1u << (b % 16));
    d.territories[b - 1].data.adjacency[a / 16] |= uint16_t(1u << (a % 16));
}
void chain(save::Document& d) {
    for (uint32_t i = 1; i < d.territories.size(); ++i) edge(d,i,i+1);
}
Building& building(save::Document& d, uint32_t territory, uint8_t category, int16_t turns = 0, int site = 0) {
    Building b{};
    b.id = uint16_t(40000 + d.buildings.size());
    b.type = 1; // Canonical Farm, intentionally unrelated to stored category.
    b.category = category;
    b.site = int8_t(site);
    b.territory = int16_t(territory);
    b.turnsLeft = turns;
    b.flags = 0; // Completed-category queries do not require Built or Active.
    if (!d.buildings.empty()) { b.prev.raw = d.buildings.back().id; d.buildings.back().next.raw = b.id; }
    d.territories[territory-1].data.sites[site].building.raw = b.id;
    d.buildings.push_back(b);
    return d.buildings.back();
}
uint32_t unit(save::Document& d, uint32_t territory, int type, int owner = 0) {
    Army a{};
    a.id = uint16_t(d.armies.size()+1);
    a.type = uint8_t(type);
    a.unitClass = data::kUnitTypes[type].unitClass;
    a.owner = int8_t(owner);
    a.territory.raw = a.dest.raw = a.origin.raw = territory;
    auto& t = d.territories[territory-1].data;
    auto& head = t.owner == owner ? t.armies : t.foreignArmies;
    a.next.raw = head.raw;
    for (auto& old : d.armies) if (old.id == head.raw) old.prev.raw = a.id;
    head.raw = a.id;
    d.armies.push_back(a);
    return a.id;
}
Army& army(save::Document& d, uint32_t id) {
    for (auto& a : d.armies) if (a.id == id) return a;
    throw std::runtime_error("missing test Army");
}
std::vector<uint8_t> bytes(const save::Document& d) {
    std::vector<uint8_t> result;
    save::Error e;
    ok(save::encode(d,result,e),e);
    for (const auto& record : d.territories) {
        const auto* start = reinterpret_cast<const uint8_t*>(&record.data);
        result.insert(result.end(), start + kTerritorySavedBytes, start + sizeof(Territory));
    }
    return result;
}
MovementPathRequest request(int domain = 1, int32_t range = 20) {
    MovementPathRequest r;
    r.origin = 1; r.range = range; r.domain = domain; r.player = 0; r.markMask = 0x2000;
    return r;
}
MovementPathReport query(const save::Document& d, const MovementPathRequest& r,
                         const MovementPathContext& c = {}) {
    const auto original = bytes(d);
    save::Error error{save::ErrorCode::Io,99,"previous"};
    MovementPathReport result;
    ok(findMovementPaths(d,r,c,result,error),error);
    require(error.code == save::ErrorCode::None && error.offset == 0 && error.message.empty(),
            "movement success clears previous error");
    require(bytes(d) == original, "movement query preserves document bytes and territorial scratch");
    return result;
}
int distance(const MovementPathReport& r, size_t index) { return r.territories.at(index).distance; }

void resetAndBoundaries() {
    auto d = fixture(); chain(*d);
    auto req = request(3,0); req.target = 1;
    MovementPathContext c;
    c.sentinelFlags = 0xabcdefffu;
    c.recursionDepth = 4; c.maximumRecursionDepth = 9;
    auto r = query(*d,req,c);
    require(r.territories.size() == 4 && r.visitCount == 0 && r.bestTargetDistance == 10000 &&
            r.recursionDepthAfter == 4 && r.maximumRecursionDepthAfter == 9,
            "range0 resets without entering origin, target update or depth accounting");
    require(r.territories[0].flags == (c.sentinelFlags & ~req.markMask), "sentinel flags come from explicit context");
    for (size_t i = 0; i < r.territories.size(); ++i) {
        require(distance(r,i) == 1000 && !(r.territories[i].flags & req.markMask),
                "range0 resets signed words and marks including sentinel0");
    }
    req.range = -1;
    r = query(*d,req,c);
    require(distance(r,1) == 1000 && !(r.territories[1].flags & req.markMask) &&
            r.visitCount == 1 && r.bestTargetDistance == 0 && r.maximumRecursionDepthAfter == 9,
            "negative range enters unmarked origin and still updates coinciding target");
    req.target.reset(); req.range = INT32_MIN;
    r = query(*d,req);
    require(r.visitCount == 1 && r.maximumRecursionDepthAfter == 1 && r.bestTargetDistance == 10000 && distance(r,1) == 1000,
            "signed minimum range makes no expansion or narrowing overflow");
    req.range = 1;
    r = query(*d,req);
    require(distance(r,0) == 1000 && distance(r,1) == 0 && distance(r,2) == 1 && distance(r,3) == 1000 && r.visitCount == 2,
            "exact range frontier is marked but never expanded");
    req.range = 2;
    r = query(*d,req);
    require(distance(r,3) == 2 && r.maximumRecursionDepthAfter == 3 && r.recursionDepthAfter == 0,
            "positive range explores exact bound and restores recursive depth");
    c.recursionDepth = INT32_MAX; c.maximumRecursionDepth = INT32_MIN;
    r = query(*d,req,c);
    require(r.recursionDepthAfter == INT32_MAX && r.maximumRecursionDepthAfter == INT32_MIN + 2,
            "recursion counters wrap32 and compare signed without C++ overflow");
    d->territories[0].data.flags |= 0x100;
    require(distance(query(*d,req),3) == 2, "origin itself is not excluded by its NoTiles flag");
}

void terrainDomainsAndEditor() {
    // Entry cost for each source/target terrain pair, all owned. Domain5 has
    // no carrier here. In particular domain4 leaves water but cannot enter it.
    const std::array<std::array<int,6>,4> expected{{
        {{1,1000,1,1,1,1}}, // land -> land
        {{1000,1,1,1000,1000,1}}, // land -> sea
        {{2,1000,1,2,2,1}}, // sea -> land
        {{1000,1,1,1000,1000,1}} // sea -> sea
    }};
    for (int pair = 0; pair < 4; ++pair) for (int domain = 1; domain <= 6; ++domain) {
        auto d = fixture(2); edge(*d,1,2);
        d->territories[0].data.terrain = pair < 2 ? 1 : 0;
        d->territories[1].data.terrain = pair % 2 ? 0 : 1;
        const auto req = request(domain);
        require(distance(query(*d,req),2) == expected[pair][domain-1], "all six domains preserve the four land/sea transition branches");
        MovementPathContext c; c.editorMode = true;
        require(distance(query(*d,req,c),2) == 0, "explicit editor context permits all terrain with cost0");
        d->territories[1].data.flags |= 0x100;
        require(distance(query(*d,req,c),2) == 1000, "editor still respects excluded territory flags");
    }
    auto d = fixture(2); edge(*d,1,2);
    d->territories[1].data.terrain = 255;
    require(distance(query(*d,request(4)),2) == 1, "terrain uses zero/nonzero byte rather than a fabricated terrain-table lookup");
    d->territories[1].data.owner = 1;
    d->options.allowAlliances = 1; d->players[0].relations[1] = 1;
    MovementPathContext c; c.editorMode = true;
    require(distance(query(*d,request(3),c),2) == 1000, "editor does not bypass directional pact veto");
}

void costsPactsAndBuildings() {
    auto d = fixture(5); chain(*d);
    d->territories[0].data.owner = 1;
    d->territories[1].data.owner = -1;
    d->territories[2].data.owner = 1;
    auto req = request(1,200);
    auto r = query(*d,req);
    require(distance(r,1) == 0 && distance(r,2) == 2 && distance(r,3) == 7 && distance(r,4) == 107 && distance(r,5) == 108,
            "edge costs read departure owner: origin2, neutral5, foreign100, own1");
    d->options.allowAlliances = 1; d->players[0].relations[1] = 2;
    r = query(*d,req);
    require(distance(r,2) == 2 && distance(r,3) == 7 && distance(r,4) == 8 && distance(r,5) == 9,
            "directional transit pact makes allied departure/arrival friendly");
    d->players[0].relations[1] = 1;
    require(distance(query(*d,req),3) == 1000, "pact bit1 veto prevents entering foreign node even from neutral");

    d = fixture(2); edge(*d,1,2);
    d->options.allowAlliances = 1; d->territories[1].data.owner = 1;
    d->players[0].relations[1] = 2;
    auto& city = building(*d,2,9);
    require(distance(query(*d,request()),2) == 1000, "completed stored-category9 city blocks pact2 despite inactive Farm canonical type");
    for (int turns : {1,-1}) {
        city.turnsLeft = int16_t(turns);
        require(distance(query(*d,request()),2) == 1, "city requires exact zero remaining work");
    }
    city.turnsLeft = 0;
    for (uint32_t mask : {0x10u,0x11u,0x12u}) {
        d->players[0].relations[1] = mask;
        require(distance(query(*d,request()),2) == 1, "effective pact16 implies2, suppresses1, and bypasses completed city restriction");
    }
    d->players[0].relations[1] = 3;
    require(distance(query(*d,request()),2) == 1000, "pact1 wins over pact2 when16 absent");
    d->options.allowAlliances = 0;
    require(distance(query(*d,request()),2) == 2, "disabled alliances disable city and war-pact vetoes");
    d->options.allowAlliances = 1; d->players[0].relations[1] = 0;
    d->players[1].relations[0] = 2;
    require(distance(query(*d,request()),2) == 2, "reverse relation does not grant forward transit");

    d = fixture(3); chain(*d); building(*d,2,12); building(*d,3,12,0,35);
    for (int domain : {1,6}) {
        r = query(*d,request(domain));
        require(distance(r,2) == 0 && distance(r,3) == 0 && r.visitCount == 3,
                "own completed fuel depots reduce total arrival distance by1 and zero-cost cycles require strict improvement");
    }
    for (int domain : {3,4,5}) require(distance(query(*d,request(domain)),3) == 2,
                                       "fuel depot reduction belongs only to domains1 and6");
    d->buildings[0].turnsLeft = -1;
    require(distance(query(*d,request()),2) == 1, "unfinished fuel depot does not reduce distance");
    d->buildings[0].turnsLeft = 0; d->territories[1].data.owner = 1;
    require(distance(query(*d,request()),2) == 2, "foreign fuel depot gives no reduction");
    d->options.allowAlliances = 1; d->players[0].relations[1] = 2;
    require(distance(query(*d,request()),2) == 1, "allied fuel depot gives no own-only reduction");
}

void depthFirstOrderAndDistanceSentinel() {
    auto d = fixture(4);
    edge(*d,1,2); edge(*d,2,3); edge(*d,3,4); edge(*d,1,4);
    auto req = request(3,10);
    auto r = query(*d,req);
    require(distance(r,2) == 1 && distance(r,3) == 2 && distance(r,4) == 1 &&
            r.visitCount == 5 && r.maximumRecursionDepthAfter == 4,
            "ascending DFS first takes long branch, then performs only a strict shorter revisit");
    req.markMask = 0x100;
    r = query(*d,req);
    require(distance(r,4) == 3 && r.visitCount == 4,
            "mark overlap with NoTiles affects live passability and prevents later shortcut revisit");
    for (auto& t : d->territories) t.data.flags |= 0x100;
    require(distance(query(*d,req),4) == 3, "reset clears requested bits before exclusion checks");

    d = fixture(4); edge(*d,1,2); edge(*d,2,4); edge(*d,4,3); edge(*d,1,3);
    req = request(3,10); req.target = 3;
    r = query(*d,req);
    require(r.bestTargetDistance == 1 && distance(r,4) == 2 && r.visitCount == 5,
            "target improves3->1 while earlier farther scratch remains, target itself does not expand");
    req.target = 2;
    r = query(*d,req);
    require(r.bestTargetDistance == 1 && distance(r,3) == 1000 && distance(r,4) == 1000 && r.visitCount == 2,
            "first ascending direct target prunes equal-cost sibling and all target outgoing edges");
    d = fixture(17); edge(*d,1,15); edge(*d,1,16);
    req.target = 15;
    r = query(*d,req);
    require(distance(r,15) == 1 && distance(r,16) == 1000, "signed WORD highbit15 is visited before next WORD lowbit16");
    d = fixture(111); edge(*d,1,111); req.target.reset(); req.range = 1;
    require(distance(query(*d,req),111) == 1, "seventh adjacency word high bit reaches highest represented territory111");

    d = fixture(13); chain(*d);
    for (auto& t : d->territories) t.data.owner = 1;
    req = request(4,INT32_MAX);
    r = query(*d,req);
    require(distance(r,2) == 2 && distance(r,11) == 902 && distance(r,12) == 1000 &&
            distance(r,13) == 1000 && r.visitCount == 11,
            "initialized signed distance1000 is a strict upper bound even with rangeINT32_MAX");
    req.range = 32767;
    require(query(*d,req).territories == r.territories, "signed16 maximum range does not cause narrowing or fictitious long paths");
}

void transportsAndMovingUnit() {
    auto d = fixture(4);
    edge(*d,1,2); edge(*d,2,3); edge(*d,2,4);
    d->territories[1].data.terrain = d->territories[2].data.terrain = 0;
    auto req = request(5,10);
    require(distance(query(*d,req),2) == 1000, "domain5 cannot board own sea without transport");
    const auto ship = unit(*d,2,12); unit(*d,3,12);
    auto r = query(*d,req);
    require(distance(r,2) == 2 && distance(r,3) == 1000 && distance(r,4) == 4,
            "domain5 boards from land and exits onto land but cannot chain sea-to-sea even with another ship");
    std::array<uint32_t,3> passengers{};
    for (size_t i = 0; i < passengers.size(); ++i) {
        passengers[i] = unit(*d,2,1);
        army(*d,ship).cargo[i].raw = passengers[i];
        army(*d,passengers[i]).cargo[0].raw = ship;
    }
    require(distance(query(*d,req),2) == 1000, "all three occupied cargo slots deny boarding");
    army(*d,ship).cargo[1].raw = 0;
    require(distance(query(*d,req),2) == 2, "any vacant cargo slot permits boarding");
    const auto moving = unit(*d,1,1);
    army(*d,moving).job = 1; army(*d,ship).job = 2;
    MovementPathContext c; c.creation.movingArmyId = moving;
    require(distance(query(*d,req,c),2) == 2, "human moving army ignores mismatched ship job");
    d->players[0].type = 3;
    require(distance(query(*d,req,c),2) == 1000, "AI moving army requires matching ship job in authoritative offline context");
    army(*d,ship).job = 1;
    require(distance(query(*d,req,c),2) == 2, "matching AI taskforce permits transport");
    army(*d,ship).job = 2;
    require(distance(query(*d,req),2) == 2, "explicit no-moving-army context bypasses AI job constraint");
    d->players[0].type = 255;
    require(distance(query(*d,req,c),2) == 2, "player type uses signed char comparison in transport lookup");
    army(*d,ship).type = 13;
    require(distance(query(*d,req),2) == 1000, "ship eligibility uses actual type12, not saved transport class");
    army(*d,ship).type = 12;
    d->territories[1].data.owner = 1;
    require(distance(query(*d,req),2) == 1000, "domain5 only boards sea owned by querying player");

    d = fixture(2); edge(*d,1,2); d->territories[1].data.terrain = 0;
    unit(*d,2,12,1);
    require(distance(query(*d,req),2) == 1000, "foreign army list transports are not inspected by CanCreateUnit");
    unit(*d,2,12);
    while (d->armies.size() < size_t(kMaxArmies)) unit(*d,1,1);
    ArmyCreationQuery creation; save::Error e;
    ok(canCreateArmy(*d,2,23,{},creation,e),e);
    require(!creation.poolAvailable && creation.reason == ArmyCreationReason::Allowed && distance(query(*d,req),2) == 2,
            "full army pool is not a path permission check; original asks transport accessibility only");
}

void errorsAndRollback() {
    auto d = fixture(); chain(*d);
    auto req = request(3,20);
    MovementPathReport result = query(*d,req), previous = result;
    save::Error e;
    auto fails = [&](const MovementPathRequest& r, const MovementPathContext& c = MovementPathContext{}) {
        require(!findMovementPaths(*d,r,c,result,e) && result == previous && e.code != save::ErrorCode::None,
                "movement error preserves the entire prior report");
    };
    for (int domain : {0,7,-1,INT32_MAX}) { auto bad = req; bad.domain = domain; fails(bad); }
    for (int player : {-1,7}) { auto bad = req; bad.player = player; fails(bad); }
    for (uint32_t index : {0u,4u,UINT32_MAX}) {
        auto bad = req; bad.origin = index; fails(bad);
        bad = req; bad.target = index; fails(bad);
    }
    MovementPathContext c; c.creation.movingArmyId = 555; fails(req,c);
    d->territories[2].data.adjacency[0] |= 1u << 4;
    const auto before = bytes(*d);
    fails(req);
    require(bytes(*d) == before, "late absent-neighbor error preserves document and all scratch");
    req.range = 2;
    require(distance(query(*d,req),3) == 2, "invalid adjacency beyond exact frontier is not dereferenced");
    req.range = 20; req.target = 3;
    require(query(*d,req).bestTargetDistance == 2, "target early return does not inspect its unused adjacency");
    req.target.reset(); d->territories[2].data.adjacency[0] &= uint16_t(0xffffu ^ (1u << 4));
    d->territories[0].data.adjacency[0] |= 1;
    fails(req);
    req.range = 0;
    require(query(*d,req).visitCount == 0, "range0 resets without traversing invalid sentinel adjacency");
    d->territories[0].data.adjacency[0] &= uint16_t(0xfffeu);
    d->territories[2].data.terrain = 0;
    unit(*d,1,1);
    d->territories[0].data.armies.raw = 0; // Archive accepts an unlisted army; lifecycle does not.
    req = request(5,20);
    fails(req);
    d->header.version = 0;
    fails(req);
    require(e.code == save::ErrorCode::UnsupportedVersion, "underlying structural-validation error is retained");
}

void realSamples(const std::filesystem::path& directory) {
    size_t documents = 0, queries = 0;
    auto inspect = [&](const save::Document& d) {
        const auto before = bytes(d);
        for (int domain = 1; domain <= 6; ++domain) {
            auto req = request(domain,4);
            req.origin = d.armies.empty() ? 1 : d.armies.front().dest.raw;
            req.player = d.options.localPlayer;
            MovementPathContext c;
            if (!d.armies.empty()) c.creation.movingArmyId = d.armies.front().id;
            auto first = query(d,req,c);
            auto second = query(d,req,c);
            require(first == second, "real samples preserve deterministic distance and scratch results");
            for (const auto& t : first.territories)
                require(t.distance == 1000 || (t.distance >= 0 && t.distance <= req.range), "real-sample distances lie within frontier or retain1000");
            ++queries;
        }
        require(bytes(d) == before, "real sample remains unchanged across all domain queries");
        ++documents;
    };
    auto d = std::make_unique<save::Document>(); save::Error e;
    ok(save::readDocument(directory / "TUTORIAL.SAV",*d,e),e); inspect(*d);
    HdxArchive archive; std::string why;
    require(archive.open((directory / "LEVELS").string(), &why), why.c_str());
    require(!archive.entries().empty(), "campaign archive contains real movement fixtures");
    size_t sampled = 0;
    for (const auto& entry : archive.entries()) {
        ok(save::readScenario(directory / "LEVELS",entry.name,*d,e),e);
        inspect(*d);
        if (++sampled == 3) break;
    }
    std::cout << "movement real samples: " << documents << " documents, " << queries << " domain queries\n";
}
} // namespace

int main(int argc, char** argv) {
    try {
        std::vector<uint8_t> globals(sizeof(gs)), gameGlobals(sizeof(gg));
        std::memcpy(globals.data(),&gs,sizeof(gs)); std::memcpy(gameGlobals.data(),&gg,sizeof(gg));
        const auto seed = rtl::seed(), seedHi = rtl::seedHi();
        resetAndBoundaries(); terrainDomainsAndEditor(); costsPactsAndBuildings();
        depthFirstOrderAndDistanceSentinel(); transportsAndMovingUnit(); errorsAndRollback();
        realSamples(argc > 1 ? std::filesystem::path(argv[1]) : std::filesystem::path("C:/GOG Games/Deadlock 2"));
        require(!std::memcmp(globals.data(),&gs,sizeof(gs)) && !std::memcmp(gameGlobals.data(),&gg,sizeof(gg)) &&
                seed == rtl::seed() && seedHi == rtl::seedHi(), "movement searches isolate global state and RNG");
        std::cout << "movement_paths: domains1..6, DFS order, costs, pacts, transport, scratch and rollback passed\n";
        return 0;
    } catch (const std::exception& e) { std::cerr << "movement_paths: " << e.what() << '\n'; return 1; }
}
