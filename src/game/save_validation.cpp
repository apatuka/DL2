// Validation of the owning file document, never of the live gs/gg state.
// orig: FUN_00460258 .. FUN_00461078; see SAVEFORMAT.md and savparse.deep_check.
#include "game/save_document.h"
#include "game/army_pool.h"

#include <cstring>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

namespace dl2::save {

const Building* Document::buildingById(uint32_t id) const {
    if (id == 0 || id > UINT16_MAX) return nullptr;
    for (const auto& building : buildings)
        if (building.id == id) return &building;
    return nullptr;
}

const Army* Document::armyById(uint32_t id) const {
    if (id == 0 || id > UINT16_MAX) return nullptr;
    for (const auto& army : armies)
        if (army.id == id) return &army;
    return nullptr;
}

const TerritoryRecord* Document::territoryByIndex(uint32_t index) const {
    if (index == 0 || index > territories.size()) return nullptr;
    const auto& record = territories[index - 1];
    return record.data.index == index ? &record : nullptr;
}

const Tile* Document::tileAt(uint32_t x, uint32_t y) const {
    if (x >= world.width || y >= world.height) return nullptr;
    const size_t index = size_t(y) * world.width + x;
    return index < tiles.size() ? &tiles[index] : nullptr;
}

namespace {

bool fail(Error& error, ErrorCode code, size_t offset, std::string message) {
    error = {code, offset, std::move(message)};
    return false;
}

std::string item(const char* block, size_t index, const char* field) {
    return std::string(block) + "[" + std::to_string(index) + "]." + field;
}

bool validateTiles(const Document& d, size_t offset, Error& error) {
    const auto width = d.world.width;
    const auto height = d.world.height;
    if (d.tiles.size() != size_t(width) * height)
        return fail(error, ErrorCode::InvalidState, offset, "Tiles count differs from world dimensions");
    for (size_t i = 0; i < d.tiles.size(); ++i) {
        const auto& tile = d.tiles[i];
        const size_t recordOffset = offset + i * sizeof(Tile);
        if (tile.x != i % width || tile.y != i / width)
            return fail(error, ErrorCode::InvalidState, recordOffset, item("Tiles", i, "coordinates do not match row-major position"));
        if (tile.territory < 0 || tile.territory > d.world.numTerritories)
            return fail(error, ErrorCode::InvalidState, recordOffset + offsetof(Tile, territory), item("Tiles", i, "territory is out of range"));
    }
    return true;
}

} // namespace

bool validate(const Document& d, Error& error) {
    error = {};
    static_assert(sizeof(kHeaderText) == sizeof(SaveHeader::text));
    if (std::memcmp(d.header.text, kHeaderText, sizeof(kHeaderText)) != 0)
        return fail(error, ErrorCode::InvalidHeader, 0, "Only the generation-4 save signature is supported");
    if (d.header.version < 35 || d.header.version > kSaveVersion)
        return fail(error, ErrorCode::UnsupportedVersion, offsetof(SaveHeader, version), "Supported save versions are 35 through 0x120");
    if (d.header.isMap != 0 && d.header.isMap != 1)
        return fail(error, ErrorCode::InvalidHeader, offsetof(SaveHeader, isMap), "Header isMap must be zero or one");

    const bool isMap = d.header.isMap == 1;
    const size_t worldOffset = sizeof(SaveHeader) + (isMap ? 0 : sizeof(GameOptions));
    const uint32_t nTerritories = d.world.numTerritories;
    if (d.world.width == 0 || d.world.width > kMapMaxSize ||
        d.world.height == 0 || d.world.height > kMapMaxSize)
        return fail(error, ErrorCode::Limit, worldOffset + offsetof(WorldParams, width), "World dimensions must be 1 through 40");
    if (nTerritories == 0 || nTerritories >= kMaxTerritories)
        return fail(error, ErrorCode::Limit, worldOffset + offsetof(WorldParams, numTerritories), "World territory count must be 1 through 111");
    if (d.trailing.size() > kMaxFileBytes)
        return fail(error, ErrorCode::Limit, 0, "Trailing bytes exceed the file size limit");

    if (isMap) {
        if (d.armyPool)
            return fail(error, ErrorCode::InvalidState, 0, "Reduced maps cannot own an army simulation pool");
        const size_t mapOffset = sizeof(SaveHeader) + sizeof(WorldParams);
        if (d.mapTerritories.size() != nTerritories)
            return fail(error, ErrorCode::InvalidState, mapOffset, "Map territory count differs from WorldParams");
        const size_t tileOffset = mapOffset + d.mapTerritories.size() * sizeof(MapTerritory);
        if (!validateTiles(d, tileOffset, error)) return false;
        const size_t end = tileOffset + d.tiles.size() * sizeof(Tile);
        if (d.trailing.size() > kMaxFileBytes - end)
            return fail(error, ErrorCode::Limit, end, "Encoded map exceeds the file size limit");
        return true;
    }

    const auto& options = d.options;
    if (options.numPlayers < 1 || options.numPlayers > kMaxPlayers)
        return fail(error, ErrorCode::Limit, sizeof(SaveHeader) + offsetof(GameOptions, numPlayers), "Player count must be 1 through 7");
    if (options.localPlayer < 0 || options.localPlayer >= kMaxPlayers)
        return fail(error, ErrorCode::InvalidState, sizeof(SaveHeader) + offsetof(GameOptions, localPlayer), "Local player slot is out of range");
    if (options.eventCount < 0 || options.eventCount > kMaxEvents || d.events.size() > kMaxEvents)
        return fail(error, ErrorCode::Limit, sizeof(SaveHeader) + offsetof(GameOptions, eventCount), "Event count exceeds 50");
    if (size_t(options.eventCount) != d.events.size())
        return fail(error, ErrorCode::InvalidState, sizeof(SaveHeader) + offsetof(GameOptions, eventCount), "Event count differs from the event records");
    if (d.localList.size() > kMaxListNodes)
        return fail(error, ErrorCode::Limit, worldOffset + sizeof(WorldParams) + sizeof(d.players), "Local list exceeds 4096 entries");
    for (size_t i = 0; i < d.localList.size(); ++i)
        if (d.localList[i] == UINT32_MAX)
            return fail(error, ErrorCode::InvalidState, worldOffset + sizeof(WorldParams) + sizeof(d.players) + i * sizeof(uint32_t), "Local list value collides with its terminator");
    if (d.buildings.size() > kMaxBuildings)
        return fail(error, ErrorCode::Limit, 0, "Building count exceeds 1200");
    if (d.armies.size() > kMaxArmies)
        return fail(error, ErrorCode::Limit, 0, "Army count exceeds 560");
    if (d.territories.size() != nTerritories)
        return fail(error, ErrorCode::InvalidState, 0, "Territory count differs from WorldParams");

    size_t offset = worldOffset + sizeof(WorldParams) + sizeof(d.players) +
                    (d.localList.size() + 1) * sizeof(uint32_t) + sizeof(RaceStats) + sizeof(d.techs);
    for (size_t p = 0; p < d.ministerJobs.size(); ++p) {
        const auto& list = d.ministerJobs[p];
        if (list.empty())
            return fail(error, ErrorCode::InvalidState, offset, item("MinisterJobs", p, "missing list head"));
        if (list.size() > kMaxListNodes)
            return fail(error, ErrorCode::Limit, offset, item("MinisterJobs", p, "exceeds 4096 records including its head"));
        for (size_t i = 0; i < list.size(); ++i) {
            // The original addresses are opaque. Only their zero/nonzero flag
            // controls how many physical records the original reader consumes.
            if ((list[i].next.raw != 0) != (i + 1 < list.size()))
                return fail(error, ErrorCode::InvalidState, offset + i * sizeof(MinisterJob) + offsetof(MinisterJob, next), item("MinisterJobs", p, "next flag disagrees with list length"));
        }
        offset += list.size() * sizeof(MinisterJob);
    }
    for (size_t i = 0; i < d.events.size(); ++i) {
        const auto& event = d.events[i];
        if (event.text.size() > 0x3ff || event.record.textLen > 0x3ff)
            return fail(error, ErrorCode::Limit, offset + offsetof(EventSaved, textLen), item("Events", i, "text exceeds 1023 bytes"));
        if (event.record.textLen != event.text.size())
            return fail(error, ErrorCode::InvalidState, offset + offsetof(EventSaved, textLen), item("Events", i, "textLen differs from its bytes"));
        offset += sizeof(EventSaved) + event.text.size();
    }
    if (!validateTiles(d, offset, error)) return false;
    offset += d.tiles.size() * sizeof(Tile);
    const size_t buildingOffset = offset + sizeof(int32_t);
    offset = buildingOffset + d.buildings.size() * sizeof(Building);
    const size_t armyOffset = offset + sizeof(int32_t);
    offset = armyOffset + d.armies.size() * sizeof(Army);

    std::array<size_t, kMaxTerritories> territoryOffsets{};
    for (size_t i = 0; i < d.territories.size(); ++i) {
        territoryOffsets[i + 1] = offset;
        offset += kTerritorySavedBytes;
        for (size_t q = 0; q < d.territories[i].queues.size(); ++q) {
            const auto count = d.territories[i].queues[q].size();
            if (count > UINT8_MAX)
                return fail(error, ErrorCode::Limit, offset, item("Territories", i + 1, "queue exceeds 255 records"));
            offset += sizeof(uint8_t) + count * kQueueRecordSaved;
        }
    }
    const size_t jobsOffset = offset;
    offset += sizeof(d.jobs) + sizeof(d.aiWarMask) + sizeof(Job) * 2 + sizeof(d.continents) +
              sizeof(d.randomEvents) + sizeof(d.scores);
    if (d.header.version >= 0x24) {
        offset += sizeof(d.spies) + sizeof(d.blackMarket);
    } else {
        // Version 35 has no physical spy/black-market block. Decoding leaves
        // these members zero, and encoding must not silently discard edits or
        // a caller's attempted downgrade from a newer document.
        for (const auto& playerSpies : d.spies)
            for (const auto& spy : playerSpies)
                if (spy.owner != 0 || spy.territory != 0 || spy.mission != 0 || spy.turns != 0)
                    return fail(error, ErrorCode::InvalidState, offset, "Version 35 cannot store nonzero spy data");
        for (const auto& market : d.blackMarket)
            if (market.pending != 0 || market.turn != 0)
                return fail(error, ErrorCode::InvalidState, offset, "Version 35 cannot store nonzero black-market data");
    }
    if (offset > kMaxFileBytes || d.trailing.size() > kMaxFileBytes - offset)
        return fail(error, ErrorCode::Limit, offset, "Encoded save exceeds the file size limit");

    std::unordered_map<uint32_t, size_t> buildingIds;
    std::unordered_map<uint32_t, size_t> armyIds;
    for (size_t i = 0; i < d.buildings.size(); ++i) {
        const auto& b = d.buildings[i];
        if (b.id == 0 || !buildingIds.emplace(b.id, i).second)
            return fail(error, ErrorCode::InvalidState, buildingOffset + i * sizeof(Building), item("Buildings", i, "zero or duplicate ID"));
        if (b.type == 0 || b.type >= 48)
            return fail(error, ErrorCode::InvalidState, buildingOffset + i * sizeof(Building) + offsetof(Building, type), item("Buildings", i, "type is out of range"));
    }
    for (size_t i = 0; i < d.armies.size(); ++i) {
        const auto& a = d.armies[i];
        if (a.id == 0 || !armyIds.emplace(a.id, i).second)
            return fail(error, ErrorCode::InvalidState, armyOffset + i * sizeof(Army), item("Armies", i, "zero or duplicate ID"));
    }

    for (size_t i = 0; i < d.territories.size(); ++i) {
        const auto& t = d.territories[i].data;
        const size_t base = territoryOffsets[i + 1];
        if (t.index != i + 1)
            return fail(error, ErrorCode::InvalidState, base + offsetof(Territory, index), item("Territories", i + 1, "index differs from file position"));
        if (t.numTiles > kMaxTilesPerTerr)
            return fail(error, ErrorCode::Limit, base + offsetof(Territory, numTiles), item("Territories", i + 1, "tile count exceeds 48"));
        for (size_t k = 0; k < t.numTiles; ++k) {
            const uint32_t xy = t.tiles[k].raw;
            const Tile* tile = d.tileAt(xy & 0xffffu, xy >> 16);
            if (!tile || tile->territory != t.index)
                return fail(error, ErrorCode::InvalidState, base + offsetof(Territory, tiles) + k * sizeof(Ptr32<Tile>), item("Territories", i + 1, "tile reference is invalid or belongs to another territory"));
        }
        for (size_t k = 0; k < kNumSites; ++k) {
            const uint32_t id = t.sites[k].building.raw;
            if (!id) continue;
            const auto found = buildingIds.find(id);
            if (found == buildingIds.end())
                return fail(error, ErrorCode::InvalidState, base + offsetof(Territory, sites) + k * sizeof(BuildingSite) + offsetof(BuildingSite, building), item("Territories", i + 1, "site references a missing building"));
            const auto& building = d.buildings[found->second];
            if (building.territory != t.index || building.site != int(k))
                return fail(error, ErrorCode::InvalidState, base + offsetof(Territory, sites) + k * sizeof(BuildingSite), item("Territories", i + 1, "site and building disagree on their location"));
        }
        for (uint32_t other = 1; other <= nTerritories; ++other) {
            if (!(t.adjacency[other >> 4] & (1u << (other & 15)))) continue;
            const auto& neighbor = d.territories[other - 1].data;
            if (!(neighbor.adjacency[t.index >> 4] & (1u << (t.index & 15))))
                return fail(error, ErrorCode::InvalidState, base + offsetof(Territory, adjacency), item("Territories", i + 1, "adjacency is not symmetric"));
        }
        for (uint32_t head : {t.armies.raw, t.foreignArmies.raw}) {
            std::unordered_set<uint32_t> visited;
            for (uint32_t id = head; id != 0;) {
                const auto found = armyIds.find(id);
                if (found == armyIds.end())
                    return fail(error, ErrorCode::InvalidState, base + offsetof(Territory, armies), item("Territories", i + 1, "army list references a missing army"));
                if (!visited.insert(id).second)
                    return fail(error, ErrorCode::InvalidState, base + offsetof(Territory, armies), item("Territories", i + 1, "army list contains a cycle"));
                const auto& army = d.armies[found->second];
                // Legacy aliases: dest (+0x3c) is current/linked territory;
                // territory (+0x38) is turn-start. Keep this codec's permissive
                // historical check; stricter activation is a separate concern.
                if (army.territory.raw != t.index && army.dest.raw != t.index)
                    return fail(error, ErrorCode::InvalidState, base + offsetof(Territory, armies), item("Territories", i + 1, "army list contains an army at a different location"));
                id = army.next.raw;
            }
        }
    }

    for (size_t i = 0; i < d.buildings.size(); ++i) {
        const auto& b = d.buildings[i];
        const size_t base = buildingOffset + i * sizeof(Building);
        if (b.territory < 1 || b.territory > int(nTerritories) || b.site < 0 || b.site >= kNumSites)
            return fail(error, ErrorCode::InvalidState, base + offsetof(Building, site), item("Buildings", i, "territory or site is out of range"));
        if (d.territories[size_t(b.territory) - 1].data.sites[size_t(b.site)].building.raw != b.id)
            return fail(error, ErrorCode::InvalidState, base, item("Buildings", i, "site does not refer back to this building"));
        // These are +0x11a/+0x11e, confirmed by FUN_00460330 (ushort* +0x8d/+0x8f).
        // The unrelated +0x116 word remains opaque (savparse's former label was wrong).
        if (b.prev.raw != 0 && !buildingIds.contains(b.prev.raw))
            return fail(error, ErrorCode::InvalidState, base + offsetof(Building, prev), item("Buildings", i, "previous ID does not exist"));
        if (b.next.raw != 0 && !buildingIds.contains(b.next.raw))
            return fail(error, ErrorCode::InvalidState, base + offsetof(Building, next), item("Buildings", i, "next ID does not exist"));
    }
    for (size_t i = 0; i < d.armies.size(); ++i) {
        const auto& a = d.armies[i];
        const size_t base = armyOffset + i * sizeof(Army);
        // Legacy health (+0x26) is the retreat threshold, not health. The
        // percentage bound and existing diagnostic vocabulary stay compatible.
        if (a.type == 0 || a.type >= 39 || a.owner < 0 || a.owner >= kMaxPlayers || a.health > 100)
            return fail(error, ErrorCode::InvalidState, base, item("Armies", i, "type, owner or health is out of range"));
        for (uint32_t territory : {a.territory.raw, a.dest.raw, a.origin.raw})
            if (territory == 0 || territory > nTerritories)
                return fail(error, ErrorCode::InvalidState, base + offsetof(Army, territory), item("Armies", i, "territory, destination or origin is out of range"));
        for (uint32_t id : {a.cargo[0].raw, a.cargo[1].raw, a.cargo[2].raw, a.next.raw, a.prev.raw})
            if (id != 0 && !armyIds.contains(id))
                return fail(error, ErrorCode::InvalidState, base + offsetof(Army, cargo), item("Armies", i, "cargo or list ID does not exist"));
    }
    if (!simulation::validateArmyPool(d, error)) return false;
    for (size_t p = 0; p < d.jobs.size(); ++p) {
        for (size_t j = 0; j < d.jobs[p].size(); ++j) {
            const auto& job = d.jobs[p][j];
            const size_t base = jobsOffset + (p * kJobsPerPlayer + j) * sizeof(Job);
            if (job.destination.raw > nTerritories)
                return fail(error, ErrorCode::InvalidState, base + offsetof(Job, destination), item("Jobs", p * kJobsPerPlayer + j, "destination is out of range"));
            for (size_t k = 0; k < 16; ++k)
                if (!d.armyPool && job.armyIds[k] != 0 && !armyIds.contains(job.armyIds[k]))
                    return fail(error, ErrorCode::InvalidState, base + offsetof(Job, armyIds) + k * sizeof(uint16_t), item("Jobs", p * kJobsPerPlayer + j, "army ID does not exist"));
            // job.armies, scratch jobs, Player AI functions and all ignored words
            // are retained exactly. They are not executable/runtime pointers.
        }
    }
    return true;
}

} // namespace dl2::save
