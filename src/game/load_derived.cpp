#include "game/load_derived.h"
#include "game/data_tables.h"
#include <cstring>
#include <exception>
#include <memory>
#include <new>
#include <stdexcept>
#include <string>
#include <utility>

namespace dl2::simulation {
namespace {
bool fail(save::Error& error, std::string message) {
    error = {save::ErrorCode::InvalidState, 0, std::move(message)};
    return false;
}
uint32_t readWord(const uint8_t* bytes) {
    uint32_t result;
    std::memcpy(&result, bytes, sizeof(result));
    return result;
}
void writeWord(uint8_t* bytes, uint32_t value) { std::memcpy(bytes, &value, sizeof(value)); }

// The original resets its entire fixed 112-territory array before loading 1..N.
// Adjacency may mention sentinel 0 or an unused slot: these read as zero, not as
// an additional saved territory. Do not invent an owned sentinel in Document.
const Territory& territory(const save::Document& d, uint32_t index) {
    static const Territory empty{};
    return index && index <= d.territories.size() ? d.territories[index - 1].data : empty;
}
bool walkMask(uint32_t mask, save::Error& error) {
    // Assembly 004425b7/004425be/00442636/0044263d uses SAR until zero,
    // WITHOUT a 32-bit iteration limit. Bit31 therefore never terminates.
    return !(mask & 0x80000000u) || fail(error, "Load-derived continent mask has bit31: original signed walk cannot terminate");
}

// orig: FUN_004423b4 (ComputeContinents), called inside LoadJobs 00461078.
bool continents(save::Document& d, save::Error& error) {
    d.continents = {};
    for (auto& record : d.territories) {
        auto& t = record.data;
        if (t.continent < 0 || t.continent >= 32) continue;
        auto& c = d.continents[size_t(t.continent)];
        c.hasLand = 1; // Overwritten for EACH territory, not OR of land presence.
        switch (t.terrain) {
        case 0: c.hasLand = 0; break;
        case 1: c.terrainMask |= 8; break;
        case 2: c.terrainMask |= 4; break;
        case 3: c.terrainMask |= 1; break;
        case 4: c.terrainMask |= 2; break;
        case 5: c.terrainMask |= 0x16; break;
        default: break;
        }
        for (uint32_t other = 0; other < kMaxTerritories; ++other) {
            if (!(t.adjacency[other >> 4] & (1u << (other & 15)))) continue;
            const auto neighbor = territory(d, other).continent;
            if (neighbor == t.continent) continue;
            t.adjContinents |= 1u << (uint8_t(neighbor) & 31u);
            c.adjContinents |= t.adjContinents; // Includes the previously saved bits.
        }
    }
    for (uint32_t i = 0; i < d.continents.size(); ++i) {
        auto& c = d.continents[i];
        if (!c.hasLand || !c.adjContinents) continue;
        if (!walkMask(c.adjContinents, error)) return false;
        uint32_t secondHop = 0;
        for (uint32_t neighbor = 0; neighbor < 31; ++neighbor) {
            if (!(c.adjContinents & (1u << neighbor))) continue;
            const uint32_t next = d.continents[neighbor].adjContinents;
            if (!walkMask(next, error)) return false;
            secondHop |= next & ~(1u << i);
        }
        writeWord(c.unk_0c, secondHop);
    }
    for (auto& record : d.territories) {
        auto& t = record.data;
        if (!t.terrain || !t.adjContinents) continue;
        if (!walkMask(t.adjContinents, error)) return false;
        for (uint32_t neighbor = 0; neighbor < 31; ++neighbor) {
            if (!(t.adjContinents & (1u << neighbor))) continue;
            const uint32_t next = d.continents[neighbor].adjContinents;
            if (!walkMask(next, error)) return false;
            // Original ESI remains 32 after the preceding loop (00442623).
            // Its comparison excludes NO valid bit: do not remove own continent.
            t.unk_8a4 |= next;
        }
    }
    return true;
}

// orig: FUN_004412d4 (HasPact). A full alliance implies bits 0x1e, not bit1.
bool pact(const save::Document& d, int player, int other, uint32_t required) {
    if (!d.options.allowAlliances || player < 0 || other < 0 ||
        player >= d.options.numPlayers || other >= d.options.numPlayers) return false;
    const uint32_t relations = d.players[size_t(player)].relations[size_t(other)];
    return required == ((relations & 0x10u) ? (required & 0x1eu) : (relations & required));
}

// orig: FUN_00486964 (CountShrines), searches 0044d1a4 / 0044d1e4.
bool shrines(save::Document& d, LoadDerivedReport& report, save::Error& error) {
    for (auto& record : d.territories) {
        auto& t = record.data;
        if (t.owner < -1 || t.owner >= kMaxPlayers)
            return fail(error, "Load-derived shrine count requires a territory owner in -1..6");
        if (!t.numTiles || (t.flags & 0x100u)) continue;
        bool completedCity = false;
        for (const auto& site : t.sites) {
            const auto* b = d.buildingById(site.building.raw);
            if (b && b->category == 9 && b->turnsLeft == 0) completedCity = true;
        }
        if (t.owner >= 0) {
            ++report.territories[size_t(t.owner)];
            if (completedCity) ++report.cities[size_t(t.owner)];
        }
        for (const auto& site : t.sites) {
            const auto* b = d.buildingById(site.building.raw);
            if (!b || b->category != 11) continue;
            ++report.totalShrines; // All shrines, including unfinished ones.
            uint32_t known = readWord(t.unk_8b0);
            if (b->turnsLeft || t.owner < 0 || !(known & (1u << t.owner))) continue;
            for (int player = 0; player < kMaxPlayers; ++player) {
                if (player == t.owner || !d.players[size_t(player)].type) continue;
                const bool allied = pact(d, player, t.owner, 0x10);
                if (allied) ++report.shrines[size_t(player)];
                if (!(known & (1u << player)) && d.options.victory == 2)
                    report.notices.push_back({t.index, player, t.owner, uint8_t(allied ? 0x4d : 0x4e)});
            }
            ++report.shrines[size_t(t.owner)];
            writeWord(t.unk_8b0, 0xffu); // Original replaces ALL32 bits, not OR 0x7f.
        }
    }
    return true;
}

// Original signed WORD tables verified directly in DEADLOCK.EXE. These are
// NOT data::kTileMoveCost (004dcbe8): the roads leaf reads 004dcc04 instead.
constexpr int16_t kRoadCost[7] = {10, 4, 3, 2, 3, 5, 30}; // 004dcc04
constexpr uint8_t kRoadOut[4] = {1, 2, 4, 8};             // low bytes, 004dcbc8
constexpr uint8_t kRoadBack[4] = {4, 8, 1, 2};            // low bytes, 004dcbd0

size_t tileIndex(const save::Document& d, int x, int y) {
    return size_t(y) * d.world.width + size_t(x);
}
bool inMap(const save::Document& d, int x, int y) {
    return x >= 0 && y >= 0 && x < d.world.width && y < d.world.height;
}
bool roadEligible(const save::Document& d, int x, int y) {
    if (!inMap(d, x, y)) return false;
    const auto& t = territory(d, uint32_t(d.tiles[tileIndex(d, x, y)].territory));
    return t.population != 0 && t.owner == d.options.localPlayer;
}

// orig: FUN_0047da24, FIFO leaves 0047d8f0/0047d930, 0047d988/0047d9f8.
bool roadCosts(save::Document& d, const Tile& start, const Tile& goal, save::Error& error) {
    const int goalX = goal.x, goalY = goal.y;
    const int startX = start.x, startY = start.y;
    for (auto& tile : d.tiles) tile.pathCost = 0x7fff;
    struct Point { int x = 0, y = 0; };
    std::array<Point, 160> queue{};
    size_t read = 0, write = 0;
    const auto enqueue = [&](int x, int y) { queue[write] = {x, y}; write = (write + 1) % queue.size(); };
    d.tiles[tileIndex(d, startX, startY)].pathCost = 0;
    enqueue(startX, startY);
    int best = 0x7fff;
    while (read != write) {
        const Point at = queue[read]; read = (read + 1) % queue.size();
        const int previous = d.tiles[tileIndex(d, at.x, at.y)].pathCost;
        for (size_t direction = 0; direction < 4; ++direction) {
            const int x = at.x + data::kPathDelta1[direction];
            const int y = at.y + data::kPathDelta2[direction];
            if (!roadEligible(d, x, y)) continue;
            auto& tile = d.tiles[tileIndex(d, x, y)];
            if (tile.terrain >= 7)
                return fail(error, "Load-derived tile road cost requires Tile::terrain in 0..6");
            const int cost = previous + kRoadCost[tile.terrain];
            if (cost >= best) continue;
            if (x == goalX && y == goalY) {
                best = cost; // Original deliberately does NOT assign goal.pathCost.
            } else if (cost < tile.pathCost) {
                tile.pathCost = int16_t(cost); // 0 <= cost < 0x7fff, no narrowing ambiguity.
                enqueue(x, y); // Original overwrite/full==empty behavior is retained.
            }
        }
    }
    return true;
}

// orig: FUN_0047d7a4. Trace chooses the lowest neighboring cost, in N/E/S/W
// order, NOT necessarily the predecessor used by the weighted cost search.
bool traceRoad(save::Document& d, size_t goal, save::Error& error) {
    size_t current = goal;
    int cost = d.tiles[current].pathCost;
    size_t direction = 0; // Retained between steps in the original.
    size_t iterations = 0;
    while (cost != 0) {
        if (++iterations > d.tiles.size() + 2)
            return fail(error, "Load-derived road trace did not descend or terminate");
        const auto& at = d.tiles[current];
        size_t next = current;
        for (size_t n = 0; n < 4; ++n) {
            const int x = at.x + data::kPathDelta1[n];
            const int y = at.y + data::kPathDelta2[n];
            if (!inMap(d, x, y)) continue;
            const size_t candidate = tileIndex(d, x, y);
            const auto& tile = d.tiles[candidate];
            if (territory(d, uint32_t(tile.territory)).owner != d.options.localPlayer || tile.pathCost >= cost) continue;
            cost = tile.pathCost; direction = n; next = candidate;
        }
        if (d.tiles[next].overlay) cost = 0;
        d.tiles[current].overlay |= kRoadOut[direction];
        d.tiles[next].overlay |= kRoadBack[direction];
        current = next;
        // No descending neighbor: original marks this same tile twice. On the
        // following iteration its nonzero overlay terminates (even unreachable).
    }
    return true;
}

// orig: FUN_0047dd24 (RebuildMapRoads), clear 0047dce0, per-territory 0047db84.
bool roads(save::Document& d, save::Error& error) {
    for (const auto& record : d.territories) {
        const auto& t = record.data;
        for (size_t i = 0; i < t.numTiles; ++i) {
            const uint32_t xy = t.tiles[i].raw;
            d.tiles[tileIndex(d, int(xy & 0xffffu), int(xy >> 16))].overlay = 0;
        }
    }
    const auto center = [&](const Territory& t, size_t& result) {
        if (t.centerTile < 0 || t.centerTile >= t.numTiles)
            return fail(error, "Load-derived roads require a valid centerTile for each connected populated local territory");
        const uint32_t xy = t.tiles[size_t(t.centerTile)].raw;
        result = tileIndex(d, int(xy & 0xffffu), int(xy >> 16));
        return true;
    };
    for (const auto& record : d.territories) {
        const auto& t = record.data;
        if (t.owner != d.options.localPlayer || !t.population || !t.numTiles || !t.terrain) continue;
        for (uint32_t other = 0; other <= d.world.numTerritories; ++other) {
            if (!(t.adjacency[other >> 4] & (1u << (other & 15)))) continue;
            const auto& neighbor = territory(d, other);
            if (neighbor.owner != t.owner || !neighbor.population || !neighbor.terrain) continue;
            size_t start = 0, end = 0;
            if (!center(t, start) || !center(neighbor, end)) return false;
            if (!roadCosts(d, d.tiles[start], d.tiles[end], error) || !traceRoad(d, end, error)) return false;
        }
    }
    return true;
}
} // namespace

bool rebuildLoadDerived(const save::Document& source, save::Document& destination,
                        LoadDerivedReport& report, save::Error& error, LoadDerivedScope scope) {
    try {
        if (scope != LoadDerivedScope::Core)
            return fail(error, "Complete load-derived reconstruction unavailable: visibility, contacts and after-move intelligence need explicit context and remaining rules");
        if (!save::validate(source, error)) return false;
        if (source.header.isMap) return fail(error, "Load-derived reconstruction requires a saved game, not a map");
        // Heap-own the large fixed AI arrays; also supports source==destination.
        auto candidate = std::make_unique<save::Document>(source);
        LoadDerivedReport result;
        if (!continents(*candidate, error)) return false;
        result.continentsRebuilt = true;
        if (!shrines(*candidate, result, error)) return false;
        result.shrineCountsRebuilt = true;
        if (!roads(*candidate, error)) return false;
        result.roadsRebuilt = true;
        if (!save::validate(*candidate, error)) return false;
        // Standard-allocator Document and report move assignments cannot throw.
        destination = std::move(*candidate);
        report = std::move(result);
        error = {};
        return true;
    } catch (const std::bad_alloc&) {
        error = {save::ErrorCode::Limit, 0, "Insufficient memory reconstructing load-derived data"};
    } catch (const std::length_error&) {
        error = {save::ErrorCode::Limit, 0, "Load-derived allocation exceeds limits"};
    } catch (const std::exception& exception) {
        error = {save::ErrorCode::InvalidState, 0, exception.what()};
    }
    return false;
}
} // namespace dl2::simulation
