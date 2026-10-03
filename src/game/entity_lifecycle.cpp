#include "game/entity_lifecycle.h"
#include "game/ai_session.h"
#include "game/army_pool.h"
#include "game/data_tables.h"
#include "game/entity_rules.h"
#include "game/supplemental_tables.h"
#include "game/labor_balance.h"

#include <algorithm>
#include <bit>
#include <cstring>
#include <memory>
#include <new>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <utility>

namespace dl2::simulation {
namespace {
bool fail(save::Error& error, const std::string& message) {
    error = {save::ErrorCode::InvalidState, 0, "Entity lifecycle: " + message}; return false;
}
int32_t add(int32_t a, int32_t b) { return std::bit_cast<int32_t>(uint32_t(a) + uint32_t(b)); }
int32_t multiply(int32_t a, int32_t b) { return std::bit_cast<int32_t>(uint32_t(a) * uint32_t(b)); }
int16_t short16(int32_t value) { return std::bit_cast<int16_t>(uint16_t(uint32_t(value))); }
int32_t halfShort(int32_t value) {
    // Original SAR1, then MOVSX low WORD (not a C++ division toward zero).
    const uint32_t shifted = (uint32_t(value) >> 1) | (uint32_t(value) & 0x80000000u);
    return short16(std::bit_cast<int32_t>(shifted));
}
Army* army(save::Document& d, uint32_t id) {
    for (auto& a : d.armies) if (a.id == id) return &a;
    return nullptr;
}
bool carrier(const Army& a) { return a.unitClass == 4 || a.unitClass == 19; }
bool knows(const save::Document& d, int tech, int player) {
    return (uint32_t(int32_t(std::bit_cast<int16_t>(d.techs[size_t(tech)].knownMask))) & (1u << unsigned(player))) != 0;
}
bool sourceValid(const save::Document& d, save::Error& error) {
    if (!save::validate(d, error)) return false;
    return !d.header.isMap || fail(error, "requires a saved game, not a reduced map");
}
// Stronger than archival validation: every live record must have one owning
// list. Keep actual list membership, not a reclassification by current owner.
bool listsValid(const save::Document& d, save::Error& error) {
    std::unordered_set<uint32_t> seen;
    for (const auto& record : d.territories) {
        const auto& t = record.data;
        for (uint32_t head : {t.armies.raw, t.foreignArmies.raw}) {
            uint32_t previous = 0;
            for (auto* a = d.armyById(head); a; a = d.armyById(a->next.raw)) {
                if (!seen.insert(a->id).second || a->prev.raw != previous || a->dest.raw != t.index)
                    return fail(error, "current-territory army lists are cyclic, shared or nonreciprocal");
                previous = a->id;
            }
        }
    }
    return seen.size() == d.armies.size() || fail(error, "some live armies are absent from their current-territory lists");
}
bool contextValid(const save::Document& d, const ArmyCreationContext& context, save::Error& error) {
    return !context.movingArmyId || d.armyById(context.movingArmyId) || fail(error, "moving-army context does not resolve");
}
int vacantCargo(const Army& a) {
    for (int slot = 0; slot < 3; ++slot) if (!a.cargo[slot].raw) return slot;
    return -1;
}
// orig: 00445940. The supplied starting node matters: CanCreateUnit starts at
// the OWN head; attaching a newly created foreign unit starts at that unit.
uint32_t findTransport(const save::Document& d, uint32_t first, const ArmyCreationContext& context) {
    const Army* moving = d.armyById(context.movingArmyId);
    for (auto* a = d.armyById(first); a; a = d.armyById(a->next.raw)) {
        if (a->type != 12 || vacantCargo(*a) < 0) continue;
        if (!moving || std::bit_cast<int8_t>(d.players[size_t(moving->owner)].type) < 3 || moving->job == a->job) return a->id;
    }
    return 0;
}
// orig: 004594b8 / 0045951c. Groups use stored CLASS, not unit TYPE.
int stackGroup(uint8_t unitClass, bool sea) {
    if (unitClass == 9) return 3;
    if (unitClass == 3 || unitClass == 13) return 2;
    if (sea) {
        switch (unitClass) { case 0: case 1: case 2: case 6: case 7: case 8: case 10: case 11: return 1; default: return 0; }
    }
    return unitClass == 2 || unitClass == 8 || unitClass == 12 ? 1 : 0;
}
bool category(const save::Document& d, const Territory& t, int value, bool completed = false) {
    for (const auto& site : t.sites) {
        const auto* b = d.buildingById(site.building.raw);
        if (b && b->category == value && (!completed || b->turnsLeft == 0)) return true;
    }
    return false;
}
ArmyCreationQuery query(const save::Document& d, uint32_t territory, int type, const ArmyCreationContext& context) {
    const auto& t = d.territories[territory - 1].data;
    const auto& definition = data::kUnitTypes[type];
    ArmyCreationQuery result;
    result.poolAvailable = d.armies.size() < size_t(kMaxArmies - 1);
    if (definition.unitClass == 9 && type != 36 && !category(d, t, 10, true)) {
        result.reason = ArmyCreationReason::MissileBaseMissing;
    } else if (t.terrain == 0 && definition.domain == data::kDomainLand) {
        result.carrierId = findTransport(d, t.armies.raw, context);
        if (!result.carrierId) result.reason = ArmyCreationReason::CarrierUnavailable;
    } else if (t.terrain != 0 && definition.domain == data::kDomainSea) {
        result.reason = ArmyCreationReason::SeaUnitOnLand;
    } else {
        result.stackGroup = stackGroup(definition.unitClass, t.terrain == 0);
        // Physical addresses: sea reads004faf6c, land reads004faf5c. The
        // historical table labels are reversed; both contain10000,10000,10000,4.
        result.limit = (t.terrain == 0 ? data::kMaxUnitsPerTerritoryLand : data::kMaxUnitsPerTerritorySea)[result.stackGroup];
        for (auto* a = d.armyById(t.armies.raw); a; a = d.armyById(a->next.raw))
            if (stackGroup(a->unitClass, t.terrain == 0) == result.stackGroup) ++result.sameGroup;
        if (result.sameGroup >= result.limit) result.reason = ArmyCreationReason::StackLimit;
    }
    return result;
}
bool nextId(save::Document& d, uint16_t& id, save::Error& error) {
    const int32_t next = add(d.options.nextGlobalId, 1);
    id = uint16_t(uint32_t(next));
    if (!id || d.armyById(id) || d.buildingById(id)) return fail(error, "NextGlobalId produced zero or a global collision; no ID search is performed");
    // A deferred MaintainUnit job can resolve this new ID in the original too.
    // Refuse that unsafe lifetime reuse explicitly, not by deleting the job.
    for (const auto& jobs : d.ministerJobs) for (const auto& job : jobs)
        if (job.type == 13 && job.param[0] == id) return fail(error, "new ID is retained by a deferred MaintainUnit job");
    d.options.nextGlobalId = next; return true;
}
bool initialize(const save::Document& d, const ArmyCreationRequest& request, uint16_t id, Army& result, save::Error& error) {
    const int race = d.players[size_t(request.owner)].race;
    if (race < 0 || race >= kMaxPlayers) return fail(error, "unit naming requires an owner race in0..6");
    result = {};
    const auto& def = data::kUnitTypes[request.unitType];
    result.id = id; result.type = uint8_t(request.unitType); result.unitClass = def.unitClass;
    result.owner = int8_t(request.owner); result.strength = uint8_t(int(def.moves) + (knows(d,46,request.owner) ? 1 : 0));
    result.health = 100;
    if (def.unitClass == 4 || def.unitClass == 6 || def.unitClass == 11 || def.unitClass == 13 || def.unitClass == 17) result.moves = 26;
    result.territory.raw = result.dest.raw = result.origin.raw = request.territory;
    const std::string name = std::string(data::kRaceNames[race]) + " " + data::kUnitShortNames[request.unitType] + " #" + std::to_string(id & 0x3ffu);
    std::memcpy(result.name, name.data(), std::min(name.size(), sizeof(result.name)));
    return true;
}
bool attach(save::Document& d, uint32_t id, const ArmyCreationContext& context, ArmyLifecycleReport& report, save::Error& error) {
    const uint32_t transportId = findTransport(d, id, context);
    if (!transportId) return true; // Original attachment failure is ignored by CreateUnit.
    auto* unit = army(d,id); auto* transport = army(d,transportId);
    if (transport->unitClass != 4) return fail(error, "transport TYPE12 has a conflicting stored carrier class");
    for (const auto& cargo : transport->cargo) if (cargo.raw == id) { report.carrierId = transportId; return true; }
    if (transport->job != unit->job) {
        if (transport->job < 1 || transport->job > kJobsPerPlayer) return fail(error, "carrier task-force index is outside1..50");
        const int player = transport->owner, jobIndex = transport->job - 1;
        const auto& job = d.jobs[size_t(player)][size_t(jobIndex)];
        bool eligible = (job.goal == 3 || job.goal == 9) && (unit->unitClass == 1 || unit->unitClass == 2 || unit->unitClass == 6);
        if (job.goal == 4 && !canScoutOwned(d,*unit,eligible,error)) return false;
        if (!eligible) return fail(error, "0040cd0c would disband the new passenger then00445a04 write the freed record; unsafe original branch rejected");
        if (unit->owner != player) return fail(error, "carrier task-force transfer crosses player-local job ownership");
        TaskForceEditReport ignored;
        if (!removeArmyFromTaskForce(d,id,ignored,error) || !addArmyToTaskForce(d,player,jobIndex,id,ignored,error)) return false;
        unit = army(d,id); transport = army(d,transportId); // Helpers may replace storage.
    }
    const int slot = vacantCargo(*transport);
    if (slot >= 0) {
        unit->unk_44.raw = 0; unit->cargo[0].raw = transportId;
        transport->cargo[slot].raw = id; report.carrierId = transportId;
    }
    return true;
}
bool createOne(save::Document& d, const ArmyCreationRequest& request, const ArmyCreationContext& context,
               uint32_t& id, ArmyCreationReason& denial, ArmyLifecycleReport& report, save::Error& error) {
    uint16_t newId = 0;
    if (!nextId(d,newId,error)) return false; // Sync wrapper attempts ID before CanCreate/Alloc.
    const auto allowed = query(d,request.territory,request.unitType,context);
    denial = allowed.reason;
    if (denial != ArmyCreationReason::Allowed) { id = 0; return true; }
    if (!allowed.poolAvailable) { id = 0; denial = ArmyCreationReason::ReservedPoolSlot; return true; }
    Army value;
    if (!initialize(d,request,newId,value,error)) return false;
    auto& t = d.territories[request.territory - 1].data;
    auto& head = t.owner == request.owner ? t.armies : t.foreignArmies;
    value.next.raw = head.raw;
    if (auto* oldHead = army(d,head.raw)) oldHead->prev.raw = newId;
    head.raw = newId; d.armies.push_back(value);
    if (!allocateArmyPoolSlot(d, newId, error)) return false;
    report.createdIds.push_back(newId); id = newId;
    if (t.terrain == 0 && data::kUnitTypes[request.unitType].domain == data::kDomainLand)
        if (!attach(d,newId,context,report,error)) return false;
    if (request.unitType == 35) {
        report.pairedMissileAttempted = true;
        uint32_t missile = 0;
        if (!createOne(d,{request.territory,request.owner,36},context,missile,report.pairedMissileDenial,report,error)) return false;
        if (missile) {
            army(d,newId)->cargo[0].raw = missile; army(d,missile)->cargo[0].raw = newId;
            report.pairedMissileId = missile;
        }
    }
    return true;
}

bool cascade(const save::Document& d, uint32_t id, std::unordered_set<uint32_t>& active,
             std::unordered_set<uint32_t>& seen, std::vector<uint32_t>& order, save::Error& error) {
    if (active.contains(id)) return fail(error, "cargo graph contains a recursive carrier cycle");
    if (seen.contains(id)) return true;
    const auto* a = d.armyById(id);
    if (!a) return fail(error, "cargo cascade refers to a missing army");
    active.insert(id); seen.insert(id);
    if (carrier(*a)) {
        for (const auto& cargo : a->cargo) if (cargo.raw) {
            const auto* child = d.armyById(cargo.raw);
            if (!child || child->cargo[0].raw != id) return fail(error, "carrier cargo is not reciprocal");
            if (!cascade(d,cargo.raw,active,seen,order,error)) return false;
        }
    } else {
        if (a->cargo[1].raw || a->cargo[2].raw) return fail(error, "noncarrier has unsupported cargo slots1/2");
        if (a->cargo[0].raw) {
            const auto* parent = d.armyById(a->cargo[0].raw);
            if (!parent || !carrier(*parent) || std::none_of(std::begin(parent->cargo),std::end(parent->cargo),[&](auto p){return p.raw==id;}))
                return fail(error, "passenger cargo does not resolve a reciprocal carrier");
        }
    }
    active.erase(id); order.push_back(id); return true;
}
// orig: 00445a74,00445fd4,00445800. Postorder is the original cascade order.
bool eraseOne(save::Document& d, uint32_t id, save::Error& error) {
    const Army value = *d.armyById(id);
    if (!carrier(value) && value.cargo[0].raw) {
        auto* parent = army(d,value.cargo[0].raw);
        for (auto& slot : parent->cargo) if (slot.raw == id) { slot.raw = 0; break; }
    }
    // For a valid reciprocal missile, DetachCargo already cleared the backlink;
    // the original's later special36 condition is then false.
    auto& t = d.territories[value.dest.raw - 1].data;
    if (auto* previous = army(d,value.prev.raw)) previous->next.raw = value.next.raw;
    if (auto* next = army(d,value.next.raw)) next->prev.raw = value.prev.raw;
    if (t.armies.raw == id) t.armies.raw = value.next.raw;
    else if (t.foreignArmies.raw == id) t.foreignArmies.raw = value.next.raw;
    const auto found = std::find_if(d.armies.begin(),d.armies.end(),[&](const auto& a){return a.id==id;});
    if (found == d.armies.end()) return fail(error,"deletion lost its live army record");
    // DeleteArmy clears the pool cell and pushes it onto the free-list head.
    // Job pointers remain bound to that cell, even through its next allocation.
    if (!retireArmyPoolSlot(d, id, error)) return false;
    d.armies.erase(found); return true;
}
// orig: 0046b074/0046b0e4. No Active flag or construction-tech gate.
bool maximumPopulation(const save::Document& d, const Territory& t, int32_t& result, save::Error& error) {
    int32_t housing = 0;
    for (const auto& site : t.sites) {
        const auto* b = d.buildingById(site.building.raw);
        if (!b || !(b->flags & 2u) || b->turnsLeft != 0) continue;
        if (b->type == 1) housing = add(housing,500);
        else if (b->type == 2) housing = add(housing,1000);
        else if (b->type == 3 || b->type == 39) housing = add(housing,1500);
    }
    if (t.owner != -1) {
        if (t.owner < 0 || t.owner >= kMaxPlayers) return fail(error,"population owner outside0..6");
        const int flat = 24 * 7 + int(d.players[size_t(t.owner)].race);
        if (flat < 0 || flat >= 64 * 7) return fail(error,"population racial lookup outside saved block");
        int16_t racial; std::memcpy(&racial,reinterpret_cast<const uint8_t*>(&d.raceStats)+size_t(flat)*2,2);
        housing = multiply(housing,racial)/100;
    }
    int32_t land = 0;
    if (t.terrain == 0 && category(d,t,20)) land = 2000;
    else {
        for (const auto& site : t.sites) if ((site.terrainFlags & 0xffu) < 5) ++land;
        land = ((land * 139 + 50) / 100) * 100;
    }
    result = std::min(land,housing); return true;
}
bool disbandRefund(save::Document& d, uint32_t id, ArmyLifecycleReport& report, save::Error& error) {
    const Army value = *d.armyById(id);
    auto& t = d.territories[value.dest.raw - 1].data;
    ArmyRefund result;
    result.armyId = id; result.territory = value.dest.raw; result.owner = value.owner;
    result.populationBefore = t.population; result.populationAfter = t.population;
    if ((value.type == 25 || value.type == 31) && (t.terrain != 0 || category(d,t,20))) {
        t.population = short16(add(t.population,100));
        int32_t maximum = 0;
        if (!maximumPopulation(d,t,maximum,error)) return false;
        if (maximum < t.population) t.population = short16(maximum);
        result.populationAfter = t.population; result.populationReturned = true;
        if (!balanceTerritoryLabor(d,value.dest.raw,d,error)) return false;
        result.laborBalanced = true;
    }
    result.credits = halfShort(data::kUnitTypes[value.type].cost[0]);
    d.players[size_t(value.owner)].credits = add(d.players[size_t(value.owner)].credits,result.credits);
    for (size_t material = 0; material < 10; ++material) {
        result.materials[material] = halfShort(data::kUnitTypes[value.type].cost[material+1]);
        auto& stock = d.territories[value.dest.raw - 1].data.materials[material+1];
        stock = add(stock,result.materials[material]);
    }
    report.refunds.push_back(result); return true;
}
} // namespace

bool canCreateArmy(const save::Document& source, uint32_t territory, int unitType,
                   const ArmyCreationContext& context, ArmyCreationQuery& destination, save::Error& error) try {
    if (!sourceValid(source,error) || !listsValid(source,error) || !contextValid(source,context,error)) return false;
    if (!territory || territory > source.territories.size() || unitType <= 0 || unitType >= data::kNumUnitTypes)
        return fail(error,"query requires valid territory and unit type1..38");
    destination = query(source,territory,unitType,context); error = {}; return true;
} catch (const std::bad_alloc&) { error={save::ErrorCode::Limit,0,"Unit query allocation failed"}; return false; }
  catch (const std::length_error&) { error={save::ErrorCode::Limit,0,"Unit query exceeds limits"}; return false; }

bool createArmy(const save::Document& source, const ArmyCreationRequest& request,
                const ArmyCreationContext& context, save::Document& destination,
                ArmyLifecycleReport& report, save::Error& error) try {
    ArmyCreationQuery allowed;
    if (!canCreateArmy(source,request.territory,request.unitType,context,allowed,error)) return false;
    if (request.owner < 0 || request.owner >= kMaxPlayers) return fail(error,"creation owner outside0..6");
    if (allowed.reason != ArmyCreationReason::Allowed || !allowed.poolAvailable)
        return fail(error,"creation denied by CanCreateUnit or the reserved pool slot");
    auto candidate = std::make_unique<save::Document>(source);
    if (!ensureArmyPool(*candidate, error)) return false;
    ArmyLifecycleReport result; result.territory = request.territory; result.counterBefore = source.options.nextGlobalId;
    ArmyCreationReason denial;
    if (!createOne(*candidate,request,context,result.primaryId,denial,result,error)) return false;
    if (!result.primaryId) return fail(error,"primary creation was unexpectedly denied");
    result.counterAfter = candidate->options.nextGlobalId;
    if (!save::validate(*candidate,error) || !listsValid(*candidate,error)) return false;
    destination = std::move(*candidate); report = std::move(result); error = {}; return true;
} catch (const std::bad_alloc&) { error={save::ErrorCode::Limit,0,"Unit creation allocation failed"}; return false; }
  catch (const std::length_error&) { error={save::ErrorCode::Limit,0,"Unit creation exceeds limits"}; return false; }

bool removeArmy(const save::Document& source, const ArmyRemovalRequest& request,
                save::Document& destination, ArmyLifecycleReport& report, save::Error& error) try {
    if (!sourceValid(source,error) || !listsValid(source,error)) return false;
    const auto* root = source.armyById(request.armyId);
    if (!root) return fail(error,"removal requires an existing army ID");
    if (request.kind != ArmyRemovalKind::DeleteUnit && request.kind != ArmyRemovalKind::DisbandUnit)
        return fail(error,"unknown removal operation");
    std::unordered_set<uint32_t> active, removed;
    std::vector<uint32_t> order;
    if (!cascade(source,request.armyId,active,removed,order,error)) return false;
    auto candidate = std::make_unique<save::Document>(source);
    if (!ensureArmyPool(*candidate, error)) return false;
    ArmyLifecycleReport result;
    result.primaryId = request.armyId; result.territory = root->dest.raw;
    result.counterBefore = result.counterAfter = source.options.nextGlobalId;
    if (request.detachTaskForces) {
        // Explicit high-level caller preparation, not smuggled into DeleteUnit.
        TaskForceEditReport ignored;
        for (uint32_t id : order) if (!removeArmyFromTaskForce(*candidate,id,ignored,error)) return false;
    }
    if (request.kind == ArmyRemovalKind::DisbandUnit && !disbandRefund(*candidate,request.armyId,result,error)) return false;
    for (uint32_t id : order) {
        if (!eraseOne(*candidate,id,error)) return false;
        result.removedIds.push_back(id);
    }
    for (const auto& jobs : candidate->ministerJobs) for (const auto& job : jobs)
        if (job.type == 13 && removed.contains(uint32_t(job.param[0]))) ++result.deferredMaintainJobs;
    if (!save::validate(*candidate,error) || !listsValid(*candidate,error)) return false;
    destination = std::move(*candidate); report = std::move(result); error = {}; return true;
} catch (const std::bad_alloc&) { error={save::ErrorCode::Limit,0,"Unit removal allocation failed"}; return false; }
  catch (const std::length_error&) { error={save::ErrorCode::Limit,0,"Unit removal exceeds limits"}; return false; }

namespace {
bool removalContextValid(const save::Document& source,const BuildingRemovalContext& context,save::Error& error) {
    if (context.pendingShrines.entries.size()>kPendingShrineCapacity) {
        error={save::ErrorCode::Limit,0,"Pending shrine queue exceeds original ten-entry storage"}; return false;
    }
    for (const auto& entry:context.pendingShrines.entries)
        if (entry.playerSlot<0 || entry.playerSlot>=kMaxPlayers || !source.territoryByIndex(entry.territory))
            return fail(error,"pending shrine queue contains an invalid player slot or territory");
    return true;
}
// orig:00450320 ->0044fe1c/0044febc/0044fdf0. A flag alone is not completion.
bool shrineCampaignProtected(const save::Document& source,const BuildingRemovalContext& context,
                             bool& protectedByCampaign,save::Error& error) {
    protectedByCampaign=false;
    if (!(context.campaignFlags&(1u<<12))) return true;
    const int campaign=source.options.campaign;
    if (campaign<0 || campaign>=data::kNumCampaigns) return fail(error,"shrine campaign query indexes outside canonical table0..42");
    for (size_t slot=0;slot<3;++slot) if (data::kCampaigns[campaign].goals[slot].type==12) {
        protectedByCampaign=context.campaignProgress[slot]!=0; return true;
    }
    // Original FindCampaignGoal returns3, then reads outside this campaign row.
    return fail(error,"live campaign flag12 has no corresponding goal12 (original out-of-row state read)");
}
bool removeBuildingImpl(const save::Document& source, const BuildingRemovalRequest& request,
                    const BuildingRemovalContext* context, save::Document& destination,
                    BuildingLifecycleReport& report, save::Error& error) try {
    if (!sourceValid(source,error)) return false;
    const auto* found = source.buildingById(request.buildingId);
    if (!found || found->type == 0 || found->type >= data::kNumBuildingTypes)
        return fail(error,"building removal requires an existing typed record");
    if (request.kind != BuildingRemovalKind::DeleteBuilding && request.kind != BuildingRemovalKind::DemolishBuilding)
        return fail(error,"unknown building removal operation");
    const bool demolish = request.kind == BuildingRemovalKind::DemolishBuilding;
    if (demolish && (request.refundPlayer < 0 || request.refundPlayer >= kMaxPlayers))
        return fail(error,"demolition requires the explicit refund player slot0..6");
    if (context && !removalContextValid(source,*context,error)) return false;
    const bool shrine=demolish && found->category==11;
    bool protectedByCampaign=false;
    if (shrine) {
        if (!context) return fail(error,"shrine demolition requires explicit live campaign and pending shrine context");
        if (!shrineCampaignProtected(source,*context,protectedByCampaign,error)) return false;
        if (!protectedByCampaign && context->pendingShrines.entries.size()==kPendingShrineCapacity) {
            error={save::ErrorCode::Limit,0,"Shrine demolition would overflow original ten-entry pending queue"}; return false;
        }
    }
    // Alloc/FreeBuilding operate on one reciprocal global active list. Dense
    // archival order need not be list order, and disconnected lists are refused.
    const Building* head = nullptr;
    for (const auto& b : source.buildings) if (b.prev.raw == 0) {
        if (head) return fail(error,"building active list has multiple heads");
        head = &b;
    }
    uint32_t previous = 0; size_t count = 0;
    for (auto* b = head; b; b = source.buildingById(b->next.raw)) {
        if (++count > source.buildings.size() || b->prev.raw != previous)
            return fail(error,"building active list is cyclic or nonreciprocal");
        previous = b->id;
    }
    if (count != source.buildings.size()) return fail(error,"building active list is disconnected");
    const Building value = *found;
    BuildingFootprint footprint;
    if (!buildingFootprint(value.type,value.site,footprint,error)) return false;
    const auto& originalTerritory = source.territories[size_t(value.territory - 1)].data;
    int platformSite = -1;
    for (int site = 0; site < kNumSites; ++site) {
        const auto* b = source.buildingById(originalTerritory.sites[site].building.raw);
        if (b && b->category == 20) { platformSite = site; break; }
    }
    const bool restoreSocket = data::kBuildingTypes[value.type].size != 5 && platformSite >= 0 &&
                              (originalTerritory.sites[size_t(value.site)].terrainFlags & 0x0f00u) == 0x200u;
    if (!restoreSocket && !footprint.fits) return fail(error,"deleted footprint would extend outside the site grid");
    auto candidate = std::make_unique<save::Document>(source);
    BuildingLifecycleReport result;
    result.primaryId = value.id; result.territory = uint32_t(value.territory); result.site = value.site;
    result.removedIds.push_back(value.id);
    if (context) result.contextAfter=*context;
    auto& t = candidate->territories[size_t(value.territory - 1)].data;
    if (demolish) {
        if (shrine) {
            //0044cefc clears this even for a campaign-protected shrine. The
            // queued identity is the supplied Player*, not the territory owner.
            t.flags&=~uint32_t(0x10); result.shrineFlagCleared=true;
            result.campaignProtected=protectedByCampaign;
            if (!protectedByCampaign) {
                result.contextAfter->pendingShrines.entries.push_back({request.refundPlayer,uint32_t(value.territory)});
                result.shrinePenaltyQueued=true;
            }
        }
        // orig: 0044cefc, costs 0044de9c/0044df30. Uncovered buildings refund
        // paid/accrued B.cost, not canonical requirements or remaining work.
        std::array<int32_t,11> costs{};
        if (!(value.flags & 2)) std::copy_n(value.cost,11,costs.begin());
        else {
            std::copy_n(data::kBuildingTypes[value.type].cost,11,costs.begin());
            if (value.type == 37) {
                if (value.hubLevel < 1) {
                    const uint32_t bits = uint32_t(costs[0]);
                    costs[0] = std::bit_cast<int32_t>((bits >> 2) | ((bits & 0x80000000u) ? 0xc0000000u : 0u));
                } else for (auto& cost : costs) cost = multiply(cost,value.hubLevel);
            }
        }
        result.refundPlayer = request.refundPlayer; result.credits = halfShort(costs[0]);
        auto& credits = candidate->players[size_t(request.refundPlayer)].credits;
        credits = add(credits,result.credits);
        for (size_t material = 0; material < result.materials.size(); ++material) {
            result.materials[material] = halfShort(costs[material + 1]);
            t.materials[material + 1] = add(t.materials[material + 1],result.materials[material]);
        }
    }
    // orig: _DeleteBuilding 0044cd50 / ClearSiteArea 0044cce4. Only the removed
    // anchor ID is cleared: deleting a platform leaves its other buildings.
    if (restoreSocket) {
        uint16_t flags = 0;
        // Exact two-stage switch decoded at 0044ce2e/0044ce47 in DEADLOCK.EXE.
        switch (platformSite - int(value.site)) {
        case -2: flags = 0x2100; break;
        case 8: flags = 0x4100; break;
        case 10: flags = 0x5100; break;
        case 12: flags = 0x1100; break;
        case 22: flags = 0x3100; break;
        default: break; // Original default leaves high flags intact.
        }
        if (flags) t.sites[size_t(value.site)].terrainFlags = uint16_t((t.sites[size_t(value.site)].terrainFlags & 0xffu) | flags);
    } else for (uint8_t site : footprint.sites) t.sites[site].terrainFlags &= 0xff;
    t.sites[size_t(value.site)].building.raw = 0;
    for (auto& b : candidate->buildings) {
        if (b.id == value.prev.raw) b.next.raw = value.next.raw;
        if (b.id == value.next.raw) b.prev.raw = value.prev.raw;
    }
    std::erase_if(candidate->buildings,[&](const Building& b){ return b.id == value.id; });
    if (demolish) {
        if (!balanceTerritoryLabor(*candidate,uint32_t(value.territory),*candidate,error)) return false;
        result.localLaborBalanced = true;
        // Verified 0044d015 reads B+8 AFTER FreeBuilding memset: territory0.
        // Its zero-filled sentinel roads are not part of the saved Document.
        result.originalRoadsTargetWasSentinel = true;
    }
    for (const auto& jobs : candidate->ministerJobs) for (const auto& job : jobs)
        if (job.type == 3 && job.param[0] == value.territory && job.param[1] == value.site) ++result.deferredBuildJobs;
    if (!save::validate(*candidate,error)) return false;
    destination = std::move(*candidate); report = std::move(result); error = {}; return true;
} catch (const std::bad_alloc&) { error={save::ErrorCode::Limit,0,"Building removal allocation failed"}; return false; }
  catch (const std::length_error&) { error={save::ErrorCode::Limit,0,"Building removal exceeds limits"}; return false; }
} // namespace
bool removeBuilding(const save::Document& source,const BuildingRemovalRequest& request,
                    save::Document& destination,BuildingLifecycleReport& report,save::Error& error) {
    return removeBuildingImpl(source,request,nullptr,destination,report,error);
}
bool removeBuilding(const save::Document& source,const BuildingRemovalRequest& request,
                    const BuildingRemovalContext& context,save::Document& destination,
                    BuildingLifecycleReport& report,save::Error& error) {
    return removeBuildingImpl(source,request,&context,destination,report,error);
}
} // namespace dl2::simulation
