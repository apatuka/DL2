#include "game/unit_movement.h"
#include "game/ai_session.h"
#include "game/data_tables.h"
#include <bit>
#include <cstring>
#include <exception>
#include <memory>
#include <new>
#include <stdexcept>
#include <unordered_set>
#include <utility>

namespace dl2::simulation {
namespace {
bool fail(save::Error& error, const char* message) {
    error = {save::ErrorCode::InvalidState, 0, message}; return false;
}
Army* army(save::Document& d, uint32_t id) {
    for (auto& value : d.armies) if (value.id == id) return &value;
    return nullptr;
}
bool listsValid(const save::Document& d, save::Error& error) {
    std::unordered_set<uint32_t> seen;
    for (const auto& record : d.territories) {
        const auto& t = record.data;
        for (uint32_t head : {t.armies.raw, t.foreignArmies.raw}) {
            uint32_t previous = 0;
            for (auto* a = d.armyById(head); a; a = d.armyById(a->next.raw)) {
                if (!seen.insert(a->id).second || a->prev.raw != previous || a->dest.raw != t.index)
                    return fail(error, "Unit movement requires reciprocal, unique current-territory army lists");
                previous = a->id;
            }
        }
    }
    return seen.size() == d.armies.size() || fail(error, "Unit movement army is absent from its current-territory list");
}
// orig:00447190. Callers consume AL, and MOVSX AL for range comparisons.
uint8_t maximumMoves(const save::Document& d, const Army& a) {
    const uint32_t extra = (d.techs[46].knownMask & (1u << unsigned(a.owner))) != 0;
    return uint8_t(uint32_t(uint8_t(data::kUnitTypes[a.type].moves)) + extra);
}
struct List { uint32_t territory; bool own; };
uint32_t& head(save::Document& d, List list) {
    auto& t = d.territories[list.territory - 1].data;
    return list.own ? t.armies.raw : t.foreignArmies.raw;
}
int vacantCargo(const Army& a) {
    for (int i = 0; i < 3; ++i) if (!a.cargo[i].raw) return i;
    return -1;
}
struct Movement {
    save::Document& d;
    UnitMovementReport& result;
    save::Error& error;

    // orig:00445898 (ReLinkArmy). Source/destination are the caller's list
    // addresses, not recomputed from each passenger's owner or destination.
    void relink(uint32_t id, List from, List to) {
        UnitMovementRelink event{id,from.territory,to.territory,from.own,to.own};
        if (from.territory == to.territory && from.own == to.own) {
            event.nativeResult = true;
        } else {
            bool found = false;
            for (auto* a = d.armyById(head(d,from)); a; a = d.armyById(a->next.raw))
                if (a->id == id) { found = true; break; }
            if (found) {
                auto* a = army(d,id);
                if (auto* previous = army(d,a->prev.raw)) previous->next = a->next;
                if (auto* next = army(d,a->next.raw)) next->prev = a->prev;
                if (head(d,from) == id) head(d,from) = a->next.raw;
                if (auto* first = army(d,head(d,to))) first->prev.raw = id;
                a->next.raw = head(d,to); a->prev.raw = 0;
                head(d,to) = id; a->dest.raw = to.territory;
                event.nativeResult = event.changed = true;
            }
        }
        result.relinks.push_back(event);
    }
    // orig:00445a74. A nonreciprocal carrier reference is a native false result;
    // the caller deliberately ignores it, without inventing a detach.
    void detach(uint32_t id) {
        auto* a = army(d,id);
        UnitMovementTransport event{UnitTransportOperation::Detach,id,a->cargo[0].raw};
        if (auto* transport = army(d,event.carrierId)) {
            for (int slot = 0; slot < 3; ++slot) if (transport->cargo[slot].raw == id) {
                transport->cargo[slot].raw = 0; a->cargo[0].raw = 0;
                event.slot = slot; event.nativeResult = true; break;
            }
        }
        result.transports.push_back(event);
    }
    // orig:00445940. Attachment starts at the moved unit, not the own-list
    // head used by CanCreateUnit; the explicit moving context may differ.
    uint32_t findTransport(uint32_t first) const {
        const auto* moving = d.armyById(result.contextAfter.paths.creation.movingArmyId);
        for (auto* a = d.armyById(first); a; a = d.armyById(a->next.raw)) {
            if (a->type != 12 || vacantCargo(*a) < 0) continue;
            if (!moving || std::bit_cast<int8_t>(d.players[size_t(moving->owner)].type) < 3 || moving->job == a->job)
                return a->id;
        }
        return 0;
    }
    // orig:00445a04 ->0040cd0c. The original writes the passenger even if
    //0040cd0c just disbanded it. Only its safe task-force transfer is supported.
    bool attach(uint32_t id) {
        UnitMovementTransport event{UnitTransportOperation::Attach,id,findTransport(id)};
        if (!event.carrierId) { result.transports.push_back(event); return true; }
        auto* a = army(d,id); auto* transport = army(d,event.carrierId);
        for (int slot = 0; slot < 3; ++slot) if (transport->cargo[slot].raw == id) {
            event.slot = slot; event.nativeResult = true;
            result.transports.push_back(event); return true;
        }
        if (transport->job != a->job) {
            if (transport->job < 1 || transport->job > kJobsPerPlayer)
                return fail(error, "Movement transport task force would disband then write the freed passenger");
            const int player = transport->owner, jobIndex = transport->job - 1;
            const auto& job = d.jobs[size_t(player)][size_t(jobIndex)];
            bool eligible = (job.goal == 3 || job.goal == 9) &&
                            (a->unitClass == 1 || a->unitClass == 2 || a->unitClass == 6);
            if (job.goal == 4 && !canScoutOwned(d,*a,eligible,error)) return false;
            if (!eligible)
                return fail(error, "Movement transport task force would disband then write the freed passenger");
            if (a->owner != player)
                return fail(error, "Movement transport task-force transfer crosses player-local ownership");
            TaskForceEditReport ignored;
            if (!removeArmyFromTaskForce(d,id,ignored,error) ||
                !addArmyToTaskForce(d,player,jobIndex,id,ignored,error)) return false;
            event.taskForceTransfer = true;
            a = army(d,id); transport = army(d,event.carrierId);
        }
        const int slot = vacantCargo(*transport);
        if (slot >= 0) {
            a->unk_44.raw = 0; a->cargo[0].raw = event.carrierId;
            transport->cargo[slot].raw = id;
            event.slot = slot; event.nativeResult = true;
        }
        result.transports.push_back(event); return true;
    }
    void debugSea(uint32_t index) {
        const auto& t = d.territories[index - 1].data;
        if (t.terrain != 0) return;
        for (bool own : {true,false}) {
            for (auto* a = d.armyById(own ? t.armies.raw : t.foreignArmies.raw); a; a = d.armyById(a->next.raw))
                if (data::kUnitTypes[a->type].domain == 1 && !a->cargo[0].raw)
                    result.untransported.push_back({a->id,index,own});
        }
    }
    bool execute() {
        const auto request = result.request;
        auto* a = army(d,request.armyId);
        const int domain = data::kUnitTypes[a->type].domain == 1 ? 5 : data::kUnitTypes[a->type].domain;
        const int player = a->owner;
        const List from{a->dest.raw,d.territories[a->dest.raw - 1].data.owner == player};
        const List to{request.target,d.territories[request.target - 1].data.owner == player};
        const int distance = result.paths.territories[request.target].distance;
        if (int(std::bit_cast<int8_t>(maximumMoves(d,*a))) < distance) {
            result.reason = UnitMovementReason::OutOfRange; return true;
        }
        if (to.own) {
            ArmyCreationQuery query;
            if (!canCreateArmy(d,request.target,a->type,result.contextAfter.paths.creation,query,error)) return false;
            result.creation = query;
            if (query.reason != ArmyCreationReason::Allowed) {
                result.reason = UnitMovementReason::CreationDenied; return true;
            }
        } else {
            const bool sea = d.territories[request.target - 1].data.terrain == 0;
            if ((sea && domain == 5) || (!sea && domain == 2)) {
                result.reason = UnitMovementReason::ForeignTerrain; return true;
            }
        }
        const auto* paired = d.armyById(a->cargo[0].raw);
        if ((a->type == 36 && paired && paired->territory.raw != paired->dest.raw) ||
            (a->type == 35 && paired && paired->dest.raw != a->dest.raw)) {
            result.reason = a->type == 36 ? UnitMovementReason::SiegeCruiserAlreadyMoved :
                                           UnitMovementReason::SiegeMissileAlreadyLaunched;
            result.siegeAdvice = std::bit_cast<int8_t>(d.players[size_t(player)].type) < 3;
            return true;
        }
        relink(request.armyId,from,to);
        if (a->unk_25 == 11 || (a->unk_25 == 13 && !to.own)) a->unk_25 = 0;
        if (a->type == 12 || a->type == 35) {
            // orig:00445aac. Read each slot live, relinking prepends in slot order.
            for (int slot = 0; slot < 3; ++slot) if (a->cargo[slot].raw) relink(a->cargo[slot].raw,from,to);
        } else if (domain == 5) {
            const bool sea = d.territories[request.target - 1].data.terrain == 0;
            if (!sea && a->cargo[0].raw) detach(request.armyId);
            if (sea && !attach(request.armyId)) return false;
        }
        a = army(d,request.armyId); // Task-force transactions may replace storage.
        a->strength = uint8_t(uint32_t(maximumMoves(d,*a)) - uint32_t(distance));
        a->origin.raw = request.routeOrigin ? request.routeOrigin : a->dest.raw;
        debugSea(request.target); debugSea(a->territory.raw);
        result.moved = true; result.reason = UnitMovementReason::Executed; return true;
    }
};
} // namespace

bool moveUnit(const save::Document& source, const UnitMovementRequest& request,
              const UnitMovementContext& context, save::Document& destination,
              UnitMovementReport& report, save::Error& error) try {
    if (!save::validate(source,error) || !listsValid(source,error)) return false;
    if (source.header.isMap) return fail(error, "Unit movement requires a saved game");
    if (context.paths.editorMode) return fail(error, "Editor movement requires unimplemented004471c0 resolution");
    const auto* initial = source.armyById(request.armyId);
    if (!initial || !request.target || request.target > source.territories.size() ||
        request.routeOrigin > source.territories.size())
        return fail(error, "Unit movement requires a resolving army, target and optional route origin");
    auto candidate = std::make_unique<save::Document>(source);
    UnitMovementReport result;
    result.request = request; result.contextAfter = context;
    result.strengthBefore = result.strengthAfter = initial->strength;
    result.missionBefore = result.missionAfter = initial->unk_25;
    MovementPathRequest search;
    search.origin = initial->territory.raw; search.target = request.target;
    search.range = std::bit_cast<int8_t>(maximumMoves(source,*initial));
    search.domain = data::kUnitTypes[initial->type].domain;
    if (search.domain == 1) search.domain = 5;
    search.player = initial->owner; search.markMask = 0x2000u << unsigned(initial->owner);
    if (!findMovementPaths(source,search,context.paths,result.paths,error)) return false;
    result.contextAfter.paths.sentinelFlags = result.paths.territories[0].flags;
    result.contextAfter.paths.recursionDepth = result.paths.recursionDepthAfter;
    result.contextAfter.paths.maximumRecursionDepth = result.paths.maximumRecursionDepthAfter;
    for (size_t i = 0; i < candidate->territories.size(); ++i) {
        auto& t = candidate->territories[i].data;
        t.flags = result.paths.territories[i + 1].flags;
        const int16_t distance = result.paths.territories[i + 1].distance;
        std::memcpy(reinterpret_cast<uint8_t*>(&t) + 0xa70 + size_t(search.player) * 2,&distance,2);
    }
    Movement work{*candidate,result,error};
    if (!work.execute() || !save::validate(*candidate,error) || !listsValid(*candidate,error)) return false;
    result.strengthAfter = candidate->armyById(request.armyId)->strength;
    result.missionAfter = candidate->armyById(request.armyId)->unk_25;
    destination = std::move(*candidate); report = std::move(result); error = {}; return true;
} catch (const std::bad_alloc&) {
    error = {save::ErrorCode::Limit,0,"Unit movement allocation failed"}; return false;
} catch (const std::length_error&) {
    error = {save::ErrorCode::Limit,0,"Unit movement trace exceeds allocation limits"}; return false;
} catch (const std::exception& exception) {
    error = {save::ErrorCode::InvalidState,0,exception.what()}; return false;
}
} // namespace dl2::simulation
