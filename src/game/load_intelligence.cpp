#include "game/load_intelligence.h"
#include "game/army_state.h"
#include "game/data_tables.h"
#include <algorithm>
#include <array>
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
template<class T> T read(const void* address) {
    T value; std::memcpy(&value, address, sizeof(value)); return value;
}
template<class T> void write(void* address, T value) { std::memcpy(address, &value, sizeof(value)); }
uint8_t* bytes(Territory& t) { return reinterpret_cast<uint8_t*>(&t); }
const uint8_t* bytes(const Territory& t) { return reinterpret_cast<const uint8_t*>(&t); }
uint8_t* bytes(BuildingSite& s) { return reinterpret_cast<uint8_t*>(&s); }

// orig: FUN_004412d4 (HasPact). Arguments are directional.
bool pact(const save::Document& d, int a, int b, uint32_t mask) {
    if (!d.options.allowAlliances || a < 0 || b < 0 || a >= d.options.numPlayers || b >= d.options.numPlayers)
        return false;
    const uint32_t stored = d.players[size_t(a)].relations[size_t(b)];
    return mask == ((stored & 0x10u) ? (mask & 0x1eu) : (stored & mask));
}

struct Work {
    save::Document& document;
    // Original routines also inspect sentinel0 and unused fixed-pool slots.
    // They start zero after LoadTerritories; no opaque native pointer is used.
    std::array<Territory, kMaxTerritories> territories{};
    std::array<bool, kMaxTerritories> city{};
    std::array<uint8_t, kMaxTerritories> foreignOwners{}, airCommandOwners{};
    explicit Work(save::Document& d) : document(d) {
        for (size_t i = 0; i < d.territories.size(); ++i) territories[i + 1] = d.territories[i].data;
    }
    int16_t distance(uint32_t index, int player) const {
        return read<int16_t>(bytes(territories[index]) + 0xa70 + size_t(player) * 2);
    }
    void distance(uint32_t index, int player, int16_t value) {
        write(bytes(territories[index]) + 0xa70 + size_t(player) * 2, value);
    }
    // orig: FUN_0044d1e4 (completed category9), 0046dfd8 (foreign head),
    // 0046e004 (type28 on either head). Preserve saved-list membership rather
    // than silently replacing it with canonical owner/location enumeration.
    bool prepare(save::Error& error) {
        for (uint32_t index = 1; index <= document.territories.size(); ++index) {
            const auto& t = territories[index];
            if (t.owner < -1 || t.owner >= kMaxPlayers)
                return fail(error, "Load intelligence requires territory owners in -1..6");
            for (const auto& site : t.sites) {
                const auto* b = document.buildingById(site.building.raw);
                if (b && b->category == 9 && b->turnsLeft == 0) city[index] = true;
            }
            for (int list = 0; list < 2; ++list) {
                uint32_t id = list ? t.foreignArmies.raw : t.armies.raw;
                size_t count = 0;
                while (id) {
                    const auto* a = document.armyById(id);
                    if (!a || ++count > document.armies.size())
                        return fail(error, "Load intelligence found an invalid or cyclic army list");
                    // Other owner values simply never match original queries0..6.
                    if (a->owner >= 0 && a->owner < kMaxPlayers) {
                        if (list) foreignOwners[index] |= uint8_t(1u << a->owner);
                        if (a->type == 28) airCommandOwners[index] |= uint8_t(1u << a->owner);
                    }
                    id = a->next.raw;
                }
            }
        }
        return true;
    }
    bool adjacent(uint32_t a, uint32_t b) const {
        return (territories[a].adjacency[b >> 4] & (1u << (b & 15))) != 0;
    }
    bool usable(uint32_t index) const {
        return territories[index].numTiles != 0 && !(territories[index].flags & 0x100u);
    }
    bool foreign(uint32_t index, int player) const {
        return (foreignOwners[index] & (1u << player)) != 0;
    }
};

// orig: FUN_00446440 specialized to param4==3, as called by 00446fd4.
// Both sea and land are passable, edge cost is exactly1, no port/transport
// helper is called in this branch. Keep DFS, original adjacency order and the
// strict improvement test; depth cannot exceed the original range (4 or5).
void scan(Work& work, uint32_t index, int cost, int range, int player, uint32_t flag) {
    auto& source = work.territories[index];
    source.flags |= flag;
    work.distance(index, player, int16_t(cost));
    if (cost >= range) return;
    for (uint32_t next = 0; next < kMaxTerritories; ++next) {
        if (!work.adjacent(index, next)) continue;
        const auto& target = work.territories[next];
        if (target.flags & 0x100u) continue;
        if (target.owner != player && pact(work.document, player, target.owner, 1)) continue;
        if (target.owner != player && pact(work.document, player, target.owner, 2) &&
            !pact(work.document, player, target.owner, 0x10) && work.city[next]) continue;
        if (cost + 1 < work.distance(next, player)) scan(work, next, cost + 1, range, player, flag);
    }
}

// orig: FUN_00446fd4 / 00446b3c / 00446b08 / 0045dfb0.
bool detector(Work& work, uint32_t source, int player, LoadIntelligenceReport& report, save::Error& error) {
    if (!source || source > work.document.territories.size() || player < 0 || player >= kMaxPlayers)
        return fail(error, "Load intelligence detector has an invalid owner/current territory");
    const int range = (work.document.techs[12].knownMask & (1u << player)) ? 5 : 4; // 004fbe04
    const uint32_t flag = 0x2000u << player;
    for (auto& t : work.territories) t.flags &= ~flag;
    for (uint32_t index = 0; index <= work.document.territories.size(); ++index)
        work.distance(index, player, 1000);
    scan(work, source, 0, range, player, flag);
    for (uint32_t index = 1; index <= work.document.territories.size(); ++index) {
        const int cost = work.distance(index, player);
        if (cost > range) continue;
        const int threshold = cost == range ? 11 : (range - cost == 1 ? 10 : 9);
        auto& saved = work.territories[index].unk_6d[player];
        // 00447090 initialized this byte to12; subsequent stores are9..11.
        saved = uint8_t(std::min(int(saved), threshold));
    }
    ++report.detectorSources;
    return true;
}

// orig: FUN_00447090. Building categories are persisted, not table-derived;
// flagsActive/Built do not gate detection. Unit TYPE14, not CLASS14, is read.
bool detection(Work& work, LoadIntelligenceReport& report, save::Error& error) {
    for (uint32_t index = 1; index <= work.document.territories.size(); ++index)
        std::fill(std::begin(work.territories[index].unk_6d), std::end(work.territories[index].unk_6d), uint8_t(12));
    for (uint32_t index = 1; index <= work.document.territories.size(); ++index) {
        const auto& t = work.territories[index];
        if (t.owner == -1) continue;
        for (const auto& site : t.sites) {
            const auto* b = work.document.buildingById(site.building.raw);
            if (b && b->turnsLeft == 0 && (b->category == 12 || b->category == 8))
                if (!detector(work, index, t.owner, report, error)) return false;
        }
    }
    //00447090 advances00645370..00651cb0 by0x5c: physical cells, NOT
    // dense append order after an allocation reuses a lower cell. Thresholds
    // accumulate minima, but flags/distances retain the LAST detector source.
    const auto detectArmy = [&](const Army& a) {
        return a.type != 14 || detector(work, army::current(a), a.owner, report, error);
    };
    if (work.document.armyPool) {
        for (const auto id : work.document.armyPool->liveIds) if (id) {
            const auto* a = work.document.armyById(id);
            if (!a) return fail(error, "Load intelligence physical cell has no current army occupant");
            if (!detectArmy(*a)) return false;
        }
    } else {
        for (const auto& a : work.document.armies) if (!detectArmy(a)) return false;
    }
    return true;
}

// orig: FUN_0046c3fc (GetLaborPool). Signed population/morale, intermediate
// truncation toward zero and only a nonzero-population minimum of1.
int unavailableLabor(const Territory& t) {
    const int tens = (int(t.morale) + 9) / 10;
    int available = (int(t.population) * ((100 - tens * 10) / 4 + tens * 10)) / 10000;
    if (t.population != 0) available = std::max(1, available);
    return std::max(0, int(t.population) / 100 - available);
}

// orig: FUN_0046e730(loading=1), assembly0046e761..0046e8b8.
bool intelligence(Work& work, LoadIntelligenceReport& report, save::Error& error) {
    // Original starts at territory1 and iterates N+1 times. For N<=110 its last
    // zeroed unused slot has no persistent effect. N111 would overwrite the
    // following building pool; reject that unsafe domain instead of emulating it.
    if (work.document.territories.size() >= kMaxTerritories - 1)
        return fail(error, "Load intelligence rejects N111: original cache loop overruns its fixed territory pool");
    for (uint32_t index = 1; index <= work.document.territories.size(); ++index) {
        auto& t = work.territories[index];
        for (size_t site = 0; site < kNumSites; ++site) {
            auto& record = t.sites[site];
            auto* out = bytes(record);
            const Building* b = work.document.buildingById(record.building.raw);
            bool copy = b && data::kBuildingTypes[b->type].size == 1;
            if (!b) {
                int offset = 0;
                if ((record.terrainFlags & 0xf000u) == 0x4000u && !(record.terrainFlags & 0x0100u)) offset = 5;
                else if ((record.terrainFlags & 0xf000u) == 0x6000u) offset = 24;
                if (offset) {
                    const size_t anchor = site + size_t(offset);
                    if (anchor >= kNumSites)
                        return fail(error, "Load intelligence marked site points beyond the 36-site footprint");
                    b = work.document.buildingById(t.sites[anchor].building.raw);
                    if (!b) return fail(error, "Load intelligence marked site has no corresponding anchor building");
                    copy = true;
                } else {
                    out[0x1a] = 0;
                    std::memset(out + 0x1e, 0, 5 * sizeof(int32_t));
                    // Race/turn bytes, +18 and +1d remain exactly as saved.
                    ++report.sitesCleared;
                }
            }
            if (copy) {
                out[0x19] = b->race; out[0x1a] = b->type;
                out[0x1b] = uint8_t(uint16_t(b->turnsLeft));
                std::memcpy(out + 0x1e, b->labor, sizeof(b->labor));
                ++report.sitesCopied;
            }
            out[0x1c] = out[0x10]; // Road byte, NOT value+04 (assembly0046e870).
            write(out + 0x32, record.terrainFlags);
        }
        bytes(t)[0x36] = uint8_t(unavailableLabor(t)); // Only low byte; +37 survives.
        t.knownPopulation = t.population;
        t.flags &= ~0x40u;
    }
    return true;
}

// orig: FUN_0046e064. Knowledge0/1/2/3/4 is rebuilt, not monotonic exploredMask.
bool visibilityFor(const Work& work, uint32_t index, int viewer, const LoadIntelligenceContext& context,
                   uint8_t& result, save::Error& error) {
    const auto& d = work.document;
    const auto& t = work.territories[index];
    result = 0;
    for (int player = 0; player < kMaxPlayers; ++player) {
        if (player != viewer && !pact(d, player, viewer, 4)) continue;
        uint8_t knowledge = work.city[index] ? 1 : 0;
        // Assembly0046e0c0..0046e0e4 ORs a bit ONLY when that same bit was
        // already set. This is not a shrine discovery or treaty-sharing effect.
        if (t.owner == player || (context.revealAll && player == d.options.localPlayer)) {
            knowledge = player == viewer ? 4 : 3;
        } else {
            const uint32_t bit = 1u << player;
            bool explored = (d.techs[31].knownMask & bit) && !(d.options.netFlags & 1u) &&
                            !(bytes(t)[0x997] & bit); // OrbitalSurveillance known, jammer mask.
            if (!explored) {
                const int race = d.players[size_t(player)].race;
                // Assembly0046e16e sign-extends even inactive players' race;
                // 0046e176 reads WORD[0055a0d8 + race*2] without a type gate.
                // In particular the saved sentinel race=-1 aliases row51[6],
                // still INSIDE the owned RaceStats block. Preserve that byte
                // address, not a synthetic race0 or an out-of-row C++ subscript.
                const int offset = 52 * kMaxPlayers * int(sizeof(int16_t)) + race * int(sizeof(int16_t));
                if (offset < 0 || size_t(offset) + sizeof(int16_t) > sizeof(d.raceStats))
                    return fail(error, "Load intelligence visibility stat address is outside the owned RaceStats block");
                const auto* stats = reinterpret_cast<const uint8_t*>(&d.raceStats);
                explored = read<int16_t>(stats + offset) != 0 ||
                           (context.fogMode == 1 && d.players[size_t(player)].type == 1);
            }
            if (explored) knowledge = 2;
            if (work.foreign(index, player) || (context.fogMode == 2 && d.players[size_t(player)].type == 1)) {
                knowledge = 3;
            } else {
                // Original jumps to the next adjacency word upon a match. No
                // mutations occur in these leaves, so retaining knowledge3 and
                // finishing this pure search has the same observable result.
                for (uint32_t neighbor = 0; neighbor < kMaxTerritories && knowledge != 3; ++neighbor) {
                    if (!work.adjacent(index, neighbor)) continue;
                    if (work.usable(neighbor) && (work.territories[neighbor].owner == player || work.foreign(neighbor, player))) {
                        knowledge = 3; break;
                    }
                    for (uint32_t next = 0; next < kMaxTerritories; ++next) {
                        if (work.adjacent(neighbor, next) && work.usable(next) &&
                            (work.airCommandOwners[next] & bit)) { knowledge = 3; break; }
                    }
                }
            }
        }
        result = std::max(result, knowledge);
    }
    return true;
}

// orig: FUN_0046e338. Territory0 is a transient sentinel only; querying it has
// no side effects on saved territories (the shrine OR above is a tautology).
bool visibility(Work& work, const LoadIntelligenceContext& context, save::Error& error) {
    for (uint32_t index = 1; index <= work.document.territories.size(); ++index)
        for (int player = 0; player < kMaxPlayers; ++player)
            if (!visibilityFor(work, index, player, context, work.territories[index].visibility[player], error)) return false;
    return true;
}
} // namespace

bool rebuildLoadIntelligence(const save::Document& source, const LoadIntelligenceContext& context,
                             save::Document& destination, LoadIntelligenceReport& report, save::Error& error) {
    try {
        if (!save::validate(source, error)) return false;
        if (source.header.isMap) return fail(error, "Load intelligence requires a saved game, not a reduced map");
        if (context.fogMode < 0 || context.fogMode > 2)
            return fail(error, "Load intelligence supports explicit fog modes0,1,2 only");
        auto candidate = std::make_unique<save::Document>(source);
        auto work = std::make_unique<Work>(*candidate);
        LoadIntelligenceReport result;
        if (!work->prepare(error) || !detection(*work, result, error) ||
            !intelligence(*work, result, error) || !visibility(*work, context, error)) return false;
        for (size_t i = 0; i < candidate->territories.size(); ++i) candidate->territories[i].data = work->territories[i + 1];
        if (!save::validate(*candidate, error)) return false;
        result.detectionRebuilt = result.visibilityRebuilt = true;
        result.buildingIntelligenceRebuilt = result.populationKnownRebuilt = true;
        result.contactDiscoverySkippedOnLoad = true;
        destination = std::move(*candidate); report = result; error = {}; return true;
    } catch (const std::bad_alloc&) {
        error = {save::ErrorCode::Limit, 0, "Insufficient memory reconstructing load intelligence"};
    } catch (const std::length_error&) {
        error = {save::ErrorCode::Limit, 0, "Load intelligence allocation exceeds limits"};
    } catch (const std::exception& exception) {
        error = {save::ErrorCode::InvalidState, 0, exception.what()};
    }
    return false;
}
} // namespace dl2::simulation
