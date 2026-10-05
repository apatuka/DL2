#include "game/combat_creation.h"
#include "game/combat_creation_tables.h"
#include "game/ai_pact_rules.h"
#include "game/data_tables.h"
#include <algorithm>
#include <bit>
#include <memory>
#include <new>
#include <stdexcept>
#include <utility>

namespace dl2::simulation {
namespace {
bool fail(save::Error& error, const char* message, save::ErrorCode code = save::ErrorCode::InvalidState) {
    error = {code, 0, message}; return false;
}
int32_t signed32(uint32_t value) { return std::bit_cast<int32_t>(value); }
int16_t signed16(uint32_t value) { return std::bit_cast<int16_t>(uint16_t(value)); }
int32_t signed8(uint8_t value) { return std::bit_cast<int8_t>(value); }
bool documentValid(const save::Document& d, save::Error& error) {
    return save::validate(d,error) && (!d.header.isMap || fail(error,"Combat creation requires a full saved-game document"));
}
CombatCreationArmy project(const Army& a) {
    return {a.id,a.id,a.type,a.owner,a.moves,a.unk_25,a.health,a.experience,a.unk_2c,a.territory.raw,a.origin.raw};
}
// orig:00446bf0; strategic mission, NOT Warrior orders.
bool excluded(uint8_t mission) {
    switch (mission) { case 1: case 2: case 3: case 4: case 5: case 6: case 15: case 16: case 19: return true; default: return false; }
}
bool coordinate(int32_t x, int32_t y) { return x >= -9 && x <= 26 && y >= -9 && y <= 26; }
size_t cell(int32_t x, int32_t y) { return size_t((y+9)*36+x+9); }
// orig:004511a4.
bool validCell(int32_t x, int32_t y) { return coordinate(x,y) && combat_creation_tables::kValidCells[cell(x,y)] != 0; }

struct Creation {
    const save::Document& d;
    const CombatCreationArmy& input;
    CombatCreationReport result;
    save::Error& error;
    CombatCreationContext& c() { return result.after; }
    const data::UnitDef& definition() const { return data::kUnitTypes[input.type]; }
    bool attacking() const { return input.owner != result.after.battle.defender; } //00450de0/e04
    const Territory* territory(uint32_t index) {
        if (index == 0 || index > d.territories.size()) {
            fail(error,"Combat creation reached an unrepresented territory (including sentinel0)"); return nullptr;
        }
        return &d.territories[index-1].data;
    }
    bool stat(const CombatWarrior& w, CombatStat which, int32_t& value) {
        CombatStatsContext stats;
        stats.combatants.push_back({w.type,w.currentOwner,w.originalOwner,w.orders,w.experience,w.supplyPenalty != 0,w.target});
        return combatStat(d,stats,{0},which,value,error);
    }
    bool draw(uint32_t bound, uint32_t& value) {
        if (result.draws.size() >= c().maximumRandomDraws)
            return fail(error,"Combat placement exceeded its explicit random-draw budget",save::ErrorCode::Limit);
        // orig:00450da4, SHR16 (all16 bits), unsigned DIV. NOT Borland rand15.
        const uint32_t before = c().rng;
        c().rng = c().rng * 0x41c64e6du + 0x3039u;
        value = (c().rng >> 16) % bound;
        result.draws.push_back({before,c().rng,bound,value}); return true;
    }
    bool tilePosition(const Territory& t, int32_t& x, int32_t& y) {
        if (t.secondTile < 0 || t.secondTile >= t.numTiles)
            return fail(error,"Combat approach requires the territory's explicit valid secondTile");
        const uint32_t packed = t.tiles[size_t(t.secondTile)].raw;
        const auto* tile = d.tileAt(packed & 0xffffu,packed >> 16);
        if (!tile) return fail(error,"Combat approach tile coordinate does not resolve");
        x = signed8(tile->x); y = signed8(tile->y); return true;
    }
    // orig:00451508 ->00448314, using Army+40 (route origin), T+75 and
    // actual Tile+0/+1. Diagonal ties choose the vertical direction.
    bool approach(uint8_t& direction) {
        direction = 0;
        if (!attacking()) return true;
        const auto* from = territory(input.routeOrigin);
        const auto* to = territory(c().battle.territory);
        if (!from || !to) return false;
        int32_t x1,y1,x2,y2;
        if (!tilePosition(*from,x1,y1) || !tilePosition(*to,x2,y2)) return false;
        if (std::abs(x2-x1) > std::abs(y2-y1)) direction = x2 < x1 ? 2 : 8;
        else direction = y2 < y1 ? 4 : 1;
        if (to->terrain == 4 && definition().unitClass != 9) {
            if (direction == 8) direction = 4;
            if (direction == 1) direction = 2;
        }
        c().battle.approachMask |= direction; return true;
    }
    // orig:00454c2c +004511d8/fc,00451220/44/6c/8c. Placement sets
    // domain3->1 and useGridPenalty=0, exactly before calling this real leaf.
    bool positionCost(int32_t x, int32_t y, uint32_t& cost) {
        ++result.testedPositions;
        if (!validCell(x,y)) { cost = 0x8000; return true; }
        const uint8_t flags = c().grid.flags[cell(x,y)];
        if (flags & 2u) { cost = 0x8000; return true; }
        if (c().placementDomain != 3 && (flags & 1u)) { cost = 50; return true; }
        if (c().placementDomain == 3) { cost = 1; return true; }
        if (c().placementDomain == 2) { cost = (flags >> 4) == 6 ? 1u : 50u; return true; }
        if (c().placementDomain == 6) {
            if (!c().selectedTerrainTerritory)
                return fail(error,"Amphibious combat placement needs the explicit selected-territory context");
            const auto* selected = territory(*c().selectedTerrainTerritory);
            if (!selected) return false;
            if (selected->terrain == 0) { cost = 1; return true; }
        } else if (c().placementDomain != 1) { cost = 50; return true; }
        cost = (flags & 4u) ? 1u : uint32_t(combat_creation_tables::kTerrainCost[flags >> 4]);
        if (c().useGridPenalty != 0) cost += c().grid.penalty[cell(x,y)];
        return true;
    }
    // orig:00451550. Complete ordinary/missile/mine positioning.
    bool position(CombatWarrior& w) {
        uint8_t direction;
        if (!approach(direction)) return false;
        if (definition().unitClass == 20) {
            const auto* t = territory(c().battle.territory);
            if (!t) return false;
            for (;;) {
                uint32_t rx,ry;
                if (!draw(36,rx) || !draw(36,ry)) return false;
                w.x = int32_t(rx)-9; w.y = int32_t(ry)-9;
                if (!validCell(w.x,w.y)) continue;
                const bool inside = w.x >= 0 && w.x < 18 && w.y >= 0 && w.y < 18;
                if (inside == (c().battle.outsidePlacement != 0)) continue;
                if (t->terrain == 4 && (w.x < 0 || w.y < 0)) continue;
                return true;
            }
        }
        if (definition().unitClass == 9) {
            switch (direction) {
            case 1: w.x = 9; w.y = -127; w.facing = 4; break;
            case 2: w.x = 127; w.y = 9; w.facing = 8; break;
            case 4: w.x = 9; w.y = 127; w.facing = 1; break;
            case 8: w.x = -127; w.y = 9; w.facing = 2; break;
            default: break; // Original preserves coordinates on absent direction.
            }
            return true;
        }
        size_t base = 0; uint32_t length = 0;
        if (attacking()) {
            length = 54;
            switch (direction) {
            case 2: base = 0; w.facing = 8; break;
            case 8: base = 108; w.facing = 2; break;
            case 1: base = 216; w.facing = 4; break;
            case 4: base = 324; w.facing = 1; break;
            default: return fail(error,"Combat approach would use an uninitialized native placement table");
            }
        } else {
            length = 72;
            // Original retries until the draw selects an enabled approach.
            // A zero low nibble would loop forever; report a domain failure.
            if (!(c().battle.approachMask & 15u)) return fail(error,"Defender placement has no enabled approach side");
            constexpr uint8_t sides[] = {2,8,1,4};
            uint32_t index;
            do { if (!draw(4,index)) return false; } while (!(c().battle.approachMask & sides[index]));
            base = 432 + size_t(index)*144; w.facing = sides[index];
        }
        c().placementDomain = definition().domain == 3 ? 1 : definition().domain;
        c().useGridPenalty = 0;
        const uint32_t count = attacking() ? c().attackerCount : c().defenderCount;
        uint32_t index = count + (input.id & 3u); // Wrap32 before signed comparison.
        if (signed32(index) < 0)
            return fail(error,"Combat placement would address a negative native table index");
        const auto& xy = combat_creation_tables::kPlacementXY;
        while (index < length) {
            uint32_t cost;
            if (!positionCost(xy[base+index],xy[base+length+index],cost)) return false;
            if (cost < 19) break; // Native unsigned comparison.
            ++index;
        }
        if (index >= length) { index = count % length; result.placementFallback = true; }
        w.x = xy[base+index]; w.y = xy[base+length+index];
        if ((definition().unitClass == 3 || definition().unitClass == 13) && c().battle.outsidePlacement != 0) {
            switch (w.facing) {
            case 1: w.y = signed32(uint32_t(w.y)+5u); break;
            case 2: w.x = signed32(uint32_t(w.x)-5u); break;
            case 4: w.y = signed32(uint32_t(w.y)-5u); break;
            case 8: w.x = signed32(uint32_t(w.x)+5u); break;
            default: break;
            }
        }
        return true;
    }
    // orig:00451928. Only the stored low WORD matters to00451b68.
    bool retreat(CombatWarrior& w) {
        w.retreatTerritory = 0xffff;
        if (w.type == 23 || definition().unitClass == 10 || definition().unitClass == 9) return true;
        if (w.orders == 1 && definition().unitClass == 1) { //00448284
            const int race = d.players[w.originalOwner].race;
            if (race < 0 || race >= data::kNumRaces) return fail(error,"Retreat racial address is outside races0..6");
            if (d.raceStats.v[33][race] != 0) return true;
        }
        if (definition().domain == 3) {
            if (!input.turnStart) { result.missingPlaneRetreat = true; return true; }
            const auto* t = territory(input.turnStart);
            if (!t) return false;
            w.retreatTerritory = t->index; return true;
        }
        const auto* battle = territory(c().battle.territory);
        if (!battle) return false;
        for (uint32_t group = 0; group < 7; ++group) for (uint32_t bit = 0; bit < 16; ++bit) {
            if (!(battle->adjacency[group] & (uint32_t(1) << bit))) continue;
            const uint32_t index = group*16+bit;
            const auto* t = territory(index); // No native upper-bound check here.
            if (!t) return false;
            if (t->owner != w.originalOwner || !t->numTiles || (t->flags & 0x100u)) continue;
            ArmyCreationQuery access;
            ++result.retreatAccessQueries;
            if (!canCreateArmy(d,index,w.type,c().creation,access,error)) return false;
            if (access.reason != ArmyCreationReason::Allowed) continue;
            // Canonical air classes return above, but these original filters
            // remain here to preserve the actual dependency order.
            if (definition().unitClass == 3 && signed8(t->unk_6d[w.originalOwner]) > w.type) continue;
            if (definition().unitClass == 13 && signed8(t->unk_6d[w.originalOwner]) > 10) continue;
            bool enemy = false; size_t walked = 0;
            uint32_t id = t->foreignArmies.raw;
            while (id && !enemy) {
                const auto* a = d.armyById(id);
                if (!a || ++walked > d.armies.size()) return fail(error,"Retreat foreign-army list does not resolve or cycles");
                if (!excluded(a->unk_25) && !hasAiPact(d,w.originalOwner,a->owner,2)) enemy = true;
                id = a->next.raw;
            }
            if (!enemy) { w.retreatTerritory = t->index; return true; }
        }
        return true;
    }
    bool pool() {
        if (c().warriors.size() != kCombatWarriorCapacity || c().cursor >= kCombatWarriorCapacity || c().limit >= kCombatWarriorCapacity)
            return fail(error,"Combat creation requires840 physical slots and cursors0..839");
        if (c().cursor == c().limit) { result.outcome = CombatCreationOutcome::PoolFull; return true; }
        if (bool(c().battle.first) != bool(c().battle.last)) return fail(error,"Combat list has inconsistent head/tail");
        std::array<bool,kCombatWarriorCapacity> seen{};
        std::optional<CombatantRef> last;
        for (auto at = c().battle.first; at; at = c().warriors[at->index].next) {
            if (at->index >= c().warriors.size() || seen[at->index] || at->index == c().cursor)
                return fail(error,"Combat list contains an invalid, cyclic or allocating pool-cell reference");
            seen[at->index] = true; last = at;
        }
        if (last != c().battle.last) return fail(error,"Combat list tail does not match its owning chain");
        return true;
    }
    // orig:00451b68, with all allocation and side effects on private candidate.
    bool run() {
        if (excluded(input.mission)) { result.outcome = CombatCreationOutcome::MissionExcluded; return true; }
        if (c().battle.defender < -1 || c().battle.defender >= kMaxPlayers)
            return fail(error,"Battle defender must be-1 or a player slot0..6");
        if (definition().unitClass == 9 && !attacking()) { result.outcome = CombatCreationOutcome::DefenderWarhead; return true; }
        if (!pool()) return false;
        if (c().cursor == c().limit) return true;
        const CombatantRef slot{c().cursor};
        c().cursor = (c().cursor+1u) % uint32_t(kCombatWarriorCapacity);
        if (c().battle.last) c().warriors[c().battle.last->index].next = slot;
        else c().battle.first = slot;
        c().battle.last = slot;
        auto& w = c().warriors[slot.index];
        w.next.reset(); w.type = input.type;
        w.originalOwner = w.currentOwner = uint8_t(input.owner);
        c().battle.playerMask |= uint8_t(1u << w.originalOwner);
        w.orders = !attacking() && input.orders == 2 ? 3 : input.orders;
        w.experience = input.experience; w.damage = input.damage;
        if (!stat(w,CombatStat::Defense,result.thresholdDefense)) return false;
        const int32_t product = signed32(uint32_t(result.thresholdDefense)*uint32_t(signed8(input.retreatPercent)));
        //00451c64 stores LOW32 IMUL, FILD; K is the exact binary64 0.01
        // encoded as80-bit00d8a3703d0ad7a3f83f, followed by+0.5 and004ae068
        // truncation. For every signed32 P, |P*(K-1/100)|<4.5e-10 (<.01).
        // At integral boundaries P%100=+/-50 the displacement has P's sign,
        // so truncation still gives the same integer. Integer identity avoids
        // depending on MSVC's64-bit long double or the host FPU control word.
        w.retreatDamage = signed16(uint32_t((int64_t(product)+50)/100));
        if (signed8(input.retreatPercent) > 0 && w.retreatDamage == 0) w.retreatDamage = 1;
        w.supplyPenalty = (d.players[size_t(input.owner)].foodFlags & 3u) ? 0xff : 0;
        if (definition().unitClass != 10) {
            if (input.liveArmyId) w.parent = CombatArmyParent{*input.liveArmyId};
            else w.parent = input;
            if (!position(w)) return false;
        }
        //004518f8 overrides only defender air; otherwise facing stays as-is.
        if (!attacking() && definition().domain == 3) w.facing = 2;
        w.active = 1; w.originalOwner = w.currentOwner;
        w.initialX = w.currentX = w.x; w.initialY = w.currentY = w.y;
        w.initialFacing = w.facing; w.initialDamage = w.damage;
        w.target.reset(); w.structureTarget.reset();
        int32_t value;
        if (!stat(w,CombatStat::Speed,value)) return false;
        w.speedCounter = uint8_t(uint32_t(value));
        if (!stat(w,CombatStat::RateOfFire,value)) return false;
        w.fireCounter = uint8_t(uint32_t(value)); w.state36 = 0;
        if (!retreat(w)) return false;
        if (definition().unitClass == 9) {
            if (!stat(w,CombatStat::Defense,value)) return false;
            w.retreatDamage = int16_t(uint8_t(uint32_t(value)));
            //004fc02a is technology23 knownMask (base004fbbac+23*0x32).
            if (!(d.techs[23].knownMask & (1u << w.originalOwner))) w.orders = 23;
        }
        //00451b00 support flags, using original owner+1e.
        if (w.type == 15) c().battle.support[0][w.originalOwner] = 1;
        if (w.type == 33) c().battle.support[1][w.originalOwner] = 1;
        if (w.type == 28) c().battle.support[2][w.originalOwner] = 1;
        if (w.type == 26) c().battle.support[3][w.originalOwner] = 1;
        if (definition().domain != 3 && definition().unitClass != 20 && w.type != 23 && definition().unitClass != 10) {
            if (!coordinate(w.currentX,w.currentY)) return fail(error,"Combat occupancy write lies outside the owned36x36 grid");
            c().grid.flags[cell(w.currentX,w.currentY)] |= 1u; //004512d4
        }
        if (definition().unitClass != 20) {
            if (attacking()) ++c().attackerCount; else ++c().defenderCount;
        }
        result.created = slot; result.outcome = CombatCreationOutcome::Created; return true;
    }
};
} // namespace

bool CombatCreationContext::operator==(const CombatCreationContext& other) const {
    return warriors == other.warriors && cursor == other.cursor && limit == other.limit && battle == other.battle &&
        grid == other.grid && attackerCount == other.attackerCount && defenderCount == other.defenderCount && rng == other.rng &&
        placementDomain == other.placementDomain && useGridPenalty == other.useGridPenalty &&
        selectedTerrainTerritory == other.selectedTerrainTerritory && creation.movingArmyId == other.creation.movingArmyId &&
        maximumRandomDraws == other.maximumRandomDraws;
}
bool projectCombatCreationArmy(const save::Document& d, uint32_t id, CombatCreationArmy& destination, save::Error& error) {
    if (!documentValid(d,error)) return false;
    const auto* a = d.armyById(id);
    if (!a) return fail(error,"Combat creation projection requires a live Army ID");
    const auto result = project(*a);
    destination = result; error = {}; return true;
}
bool createCombatWarrior(const save::Document& d, const CombatCreationArmy& input,
                         const CombatCreationContext& context, CombatCreationReport& report, save::Error& error) try {
    if (!documentValid(d,error)) return false;
    if (input.type < 1 || input.type >= data::kNumUnitTypes || input.owner < 0 || input.owner >= kMaxPlayers)
        return fail(error,"Combat creation requires canonical type1..38 and owner0..6");
    if (input.liveArmyId) {
        const auto* a = d.armyById(*input.liveArmyId);
        if (!a || project(*a) != input) return fail(error,"Combat creation live binding differs from its supplied Army snapshot");
    }
    // Heap allocation avoids coupling maximum pool size to a thread's stack.
    auto work = std::make_unique<Creation>(Creation{d,input,{},error});
    work->result.after = context;
    if (!work->run()) return false;
    report = std::move(work->result); error = {}; return true;
} catch (const std::bad_alloc&) {
    return fail(error,"Combat creation allocation failed",save::ErrorCode::Limit);
} catch (const std::length_error&) {
    return fail(error,"Combat creation allocation exceeds limits",save::ErrorCode::Limit);
}
} // namespace dl2::simulation
