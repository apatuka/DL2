// Assembly-derived00446084 expectations; not an executed original-game oracle.
#include "game/unit_movement.h"
#include "game/army_pool.h"
#include "game/data_tables.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include "game/runtime_state.h"
#include <cstring>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

namespace {
using namespace dl2;
using namespace dl2::simulation;
void require(bool value, const char* message) { if (!value) throw std::runtime_error(message); }
void ok(bool value, const save::Error& error) { if (!value) throw std::runtime_error(error.message); }
std::unique_ptr<save::Document> fixture(size_t count = 3) {
    auto d = std::make_unique<save::Document>();
    std::memcpy(d->header.text,save::kHeaderText,sizeof(save::kHeaderText));
    d->header.version = kSaveVersion;
    d->world.width = d->world.height = 1; d->world.numTerritories = uint16_t(count);
    d->options.numPlayers = 2; d->options.localPlayer = 0; d->options.turn = 17;
    d->tiles.resize(1); d->territories.resize(count);
    for (int p = 0; p < kMaxPlayers; ++p) {
        d->players[p].index = uint8_t(p); d->players[p].race = int8_t(p);
        d->players[p].type = p ? 3 : 1; d->ministerJobs[p].resize(1);
        for (auto& job : d->jobs[p]) job.owner = int16_t(p);
    }
    for (size_t i = 0; i < count; ++i) {
        auto& t = d->territories[i].data;
        t.index = uint16_t(i + 1); t.owner = 0; t.terrain = 1; t.flags = 0x40002001u;
        for (size_t p = 0; p < kMaxPlayers; ++p) {
            const int16_t value = int16_t(-100 - int(p));
            std::memcpy(reinterpret_cast<uint8_t*>(&t) + 0xa70 + p * 2,&value,2);
        }
    }
    return d;
}
void edge(save::Document& d, uint32_t a, uint32_t b) {
    d.territories[a - 1].data.adjacency[b / 16] |= uint16_t(1u << (b % 16));
    d.territories[b - 1].data.adjacency[a / 16] |= uint16_t(1u << (a % 16));
}
void chain(save::Document& d) {
    for (uint32_t i = 1; i < d.territories.size(); ++i) edge(d,i,i + 1);
}
uint32_t unit(save::Document& d, int type, uint32_t territory = 1, int owner = 0) {
    Army a{}; a.id = uint16_t(d.armies.size() + 1); a.type = uint8_t(type);
    a.unitClass = data::kUnitTypes[type].unitClass; a.owner = int8_t(owner); a.health = 100;
    a.territory.raw = a.dest.raw = a.origin.raw = territory;
    a.strength = 211; a.unk_25 = 11; a.unk_44.raw = 0xabcdef01;
    auto& t = d.territories[territory - 1].data;
    auto& head = owner == t.owner ? t.armies : t.foreignArmies;
    a.next.raw = head.raw;
    for (auto& old : d.armies) if (old.id == head.raw) old.prev.raw = a.id;
    head.raw = a.id; d.armies.push_back(a); return a.id;
}
Army& army(save::Document& d, uint32_t id) {
    for (auto& a : d.armies) if (a.id == id) return a;
    throw std::runtime_error("test army unresolved");
}
void bind(save::Document& d, uint32_t id, int job, int slot) {
    auto& a = army(d,id); a.job = int16_t(job + 1);
    d.jobs[size_t(a.owner)][size_t(job)].armyIds[slot] = uint16_t(id);
    d.jobs[size_t(a.owner)][size_t(job)].armies[slot].raw = 0xf0000000u + id;
}
void carry(save::Document& d, uint32_t carrier, uint32_t passenger, int slot = 0) {
    army(d,carrier).cargo[slot].raw = passenger; army(d,passenger).cargo[0].raw = carrier;
}
int16_t distance(const Territory& t, int player) {
    int16_t value; std::memcpy(&value,reinterpret_cast<const uint8_t*>(&t) + 0xa70 + size_t(player) * 2,2);
    return value;
}
std::vector<uint8_t> bytes(const save::Document& d) {
    std::vector<uint8_t> result; save::Error error; ok(save::encode(d,result,error),error);
    for (const auto& record : d.territories) {
        const auto* data = reinterpret_cast<const uint8_t*>(&record.data);
        result.insert(result.end(),data + kTerritorySavedBytes,data + sizeof(Territory));
    }
    return result;
}
std::vector<uint32_t> list(const save::Document& d, uint32_t territory, bool own = true) {
    const auto& t = d.territories[territory - 1].data; std::vector<uint32_t> result;
    for (auto* a = d.armyById(own ? t.armies.raw : t.foreignArmies.raw); a; a = d.armyById(a->next.raw)) result.push_back(a->id);
    return result;
}
struct Outcome { std::unique_ptr<save::Document> document = std::make_unique<save::Document>(); UnitMovementReport report; };
Outcome move(const save::Document& d, UnitMovementRequest request, UnitMovementContext context = {}) {
    const auto before = bytes(d); Outcome out; save::Error error{save::ErrorCode::Io,77,"old"};
    ok(moveUnit(d,request,context,*out.document,out.report,error),error);
    require(error.code == save::ErrorCode::None && error.message.empty() && bytes(d) == before,
            "move must clear error and preserve source");
    return out;
}
void totalDistanceAndScratch() {
    auto d = fixture(5); chain(*d); const auto id = unit(*d,1,2);
    army(*d,id).territory.raw = 1; army(*d,id).origin.raw = 4; army(*d,id).strength = 0;
    UnitMovementContext context; context.paths.creation.movingArmyId = id;
    context.paths.sentinelFlags = 0x80002040; context.paths.recursionDepth = 7; context.paths.maximumRecursionDepth = 8;
    auto out = move(*d,{id,3,0},context);
    require(out.report.moved && out.report.reason == UnitMovementReason::Executed &&
            out.report.paths.request.origin == 1 && out.report.paths.request.range == 3 &&
            out.report.paths.request.domain == 5 && out.report.paths.territories[3].distance == 2 &&
            out.document->armyById(id)->territory.raw == 1 && out.document->armyById(id)->dest.raw == 3 &&
            out.document->armyById(id)->origin.raw == 3 && out.document->armyById(id)->strength == 1 &&
            out.report.strengthBefore == 0 && out.report.strengthAfter == 1 && out.report.missionAfter == 0,
            "movement must spend total turn-start distance, ignoring prior strength and route anchor");
    require(out.report.contextAfter.paths.sentinelFlags == 0x80000040 &&
            out.report.contextAfter.paths.recursionDepth == 7 &&
            out.report.contextAfter.paths.maximumRecursionDepth == 10 &&
            list(*out.document,2).empty() && list(*out.document,3) == std::vector<uint32_t>{id},
            "path continuation or owning lists differ");
    for (size_t i = 0; i < d->territories.size(); ++i) {
        const auto& t = out.document->territories[i].data;
        require(t.flags == out.report.paths.territories[i + 1].flags &&
                distance(t,0) == out.report.paths.territories[i + 1].distance,
                "executor did not publish path scratch");
        for (int p = 1; p < 7; ++p) require(distance(t,p) == -100 - p,"another player's distance changed");
    }
    auto second = move(*out.document,{id,4,2},out.report.contextAfter);
    require(second.report.moved && second.document->armyById(id)->strength == 0 &&
            second.document->armyById(id)->origin.raw == 2,"explicit param3 or cumulative movement differs");
    auto denied = move(*second.document,{id,5,0});
    require(!denied.report.moved && denied.report.reason == UnitMovementReason::OutOfRange &&
            denied.report.paths.territories[5].distance == 1000 &&
            denied.document->armyById(id)->dest.raw == 4 && denied.report.relinks.empty(),
            "out-of-range native return must preserve the unit and publish search");
    second.document->techs[46].knownMask = 1;
    auto boosted = move(*second.document,{id,5,0});
    require(boosted.report.moved && boosted.report.paths.request.range == 4 &&
            boosted.document->armyById(id)->strength == 0 && boosted.document->options.turn == 17,
            "Transporters maximum must add one without advancing the turn");
}
void nativeRefusalsAndNoop() {
    auto d = fixture(); chain(*d); const auto fort = unit(*d,19);
    auto stopped = move(*d,{fort,1,0});
    require(!stopped.report.moved && stopped.report.paths.visitCount == 0 &&
            distance(stopped.document->territories[0].data,0) == 1000 &&
            !(stopped.document->territories[0].data.flags & 0x2000),
            "range-zero native search must reset even origin and refuse movement");
    d = fixture(); chain(*d); auto id = unit(*d,16);
    auto noBase = move(*d,{id,2,0});
    require(!noBase.report.moved && noBase.report.reason == UnitMovementReason::CreationDenied &&
            noBase.report.creation->reason == ArmyCreationReason::MissileBaseMissing &&
            distance(noBase.document->territories[1].data,0) == 1,
            "native creation refusal must retain completed path scratch");
    d = fixture(); chain(*d); id = unit(*d,36);
    for (int i = 0; i < 4; ++i) unit(*d,36,2);
    auto stack = move(*d,{id,2,0});
    require(!stack.report.moved && stack.report.creation->reason == ArmyCreationReason::StackLimit,
            "movement must retain missile stack cap");
    d = fixture(); d->territories[0].data.owner = 1; id = unit(*d,12);
    auto foreign = move(*d,{id,1,0});
    require(!foreign.report.moved && foreign.report.reason == UnitMovementReason::ForeignTerrain,
            "foreign land rejects sea unit after origin reaches zero distance");
    d = fixture(); d->territories[0].data.owner = 1; d->territories[0].data.terrain = 0; id = unit(*d,1);
    foreign = move(*d,{id,1,0});
    require(!foreign.report.moved && foreign.report.reason == UnitMovementReason::ForeignTerrain,
            "foreign sea rejects land unit even for target==origin");
    d = fixture(); id = unit(*d,1); army(*d,id).unk_25 = 13;
    auto same = move(*d,{id,1,0});
    require(same.report.moved && same.report.relinks.size() == 1 && same.report.relinks[0].nativeResult &&
            !same.report.relinks[0].changed && same.document->armyById(id)->strength == 3 &&
            same.document->armyById(id)->unk_25 == 13,"same-list relink must be a true no-op and retain own mission13");
    d->territories[1].data.owner = 1; edge(*d,1,2);
    auto enemy = move(*d,{id,2,0});
    require(enemy.report.moved && !enemy.report.relinks[0].targetOwn &&
            list(*enemy.document,2,false) == std::vector<uint32_t>{id} &&
            enemy.document->armyById(id)->unk_25 == 0 && enemy.document->territories[1].data.owner == 1,
            "foreign movement clears mission13 without conquest");
}
void ignoredRelinkFailure() {
    auto d = fixture(); chain(*d); const auto id = unit(*d,1);
    // Structurally reciprocal, but classified in the opposite list. The native
    // caller picks by owner, cannot find it, ignores false, then writes the unit.
    d->territories[0].data.armies.raw = 0; d->territories[0].data.foreignArmies.raw = id;
    auto out = move(*d,{id,2,0});
    require(out.report.moved && !out.report.relinks[0].nativeResult && !out.report.relinks[0].changed &&
            out.document->armyById(id)->dest.raw == 1 && out.document->armyById(id)->origin.raw == 1 &&
            out.document->armyById(id)->strength == 2 && out.document->armyById(id)->unk_25 == 0 &&
            list(*out.document,1,false) == std::vector<uint32_t>{id},
            "native return1 after failed relink must not become a fabricated relocation");
}
void boardingAndLanding() {
    auto d = fixture(); chain(*d); d->territories[1].data.terrain = 0;
    const auto carrier = unit(*d,12,2), passenger = unit(*d,1);
    UnitMovementContext context; context.paths.creation.movingArmyId = passenger;
    auto aboard = move(*d,{passenger,2,0},context);
    require(aboard.report.moved && aboard.report.paths.territories[2].distance == 2 &&
            aboard.report.transports.size() == 1 && aboard.report.transports[0].nativeResult &&
            aboard.report.transports[0].slot == 0 &&
            aboard.document->armyById(passenger)->cargo[0].raw == carrier &&
            aboard.document->armyById(passenger)->unk_44.raw == 0 &&
            aboard.document->armyById(carrier)->cargo[0].raw == passenger && aboard.report.untransported.empty(),
            "boarding needs the first free reciprocal slot and clears transient44");
    auto ashore = move(*aboard.document,{passenger,1,0},context);
    require(ashore.report.moved && ashore.report.transports[0].operation == UnitTransportOperation::Detach &&
            ashore.report.transports[0].nativeResult && !ashore.document->armyById(passenger)->cargo[0].raw &&
            !ashore.document->armyById(carrier)->cargo[0].raw && ashore.document->armyById(passenger)->strength == 3,
            "landing must detach and recompute maximum from total origin distance");
    // Nonreciprocal cargo is not silently repaired;00445a74 returns0, ignored.
    aboard.document->armies[0].cargo[0].raw = 0;
    auto stale = move(*aboard.document,{passenger,1,0},context);
    require(stale.report.moved && !stale.report.transports[0].nativeResult &&
            stale.document->armyById(passenger)->cargo[0].raw == carrier,
            "native failed detach must retain unmatched passenger reference");
    d = fixture(); chain(*d); d->territories[1].data.terrain = 0;
    const auto boat = unit(*d,12,2), land = unit(*d,1);
    // Failed relink leaves the passenger before no transport in its foreign
    // list, whereas the prior CanCreate query found the target's own boat.
    d->territories[0].data.armies.raw = 0; d->territories[0].data.foreignArmies.raw = land;
    auto unattached = move(*d,{land,2,0});
    require(unattached.report.moved && unattached.report.creation->carrierId == boat &&
            unattached.report.transports.size() == 1 && !unattached.report.transports[0].nativeResult &&
            !unattached.document->armyById(land)->cargo[0].raw,
            "attachment must start at the unit, not repeat CanCreate's own-head lookup");
}
void carriedOrderAndSiegePairs() {
    auto d = fixture(); chain(*d);
    for (auto& t : d->territories) t.data.terrain = 0;
    const auto carrier = unit(*d,12), one = unit(*d,1), two = unit(*d,5), three = unit(*d,24);
    const auto existing = unit(*d,13,2);
    carry(*d,carrier,one,0); carry(*d,carrier,two,1); carry(*d,carrier,three,2);
    auto out = move(*d,{carrier,2,3});
    require(out.report.moved && out.report.relinks.size() == 4 &&
            out.report.relinks[0].armyId == carrier && out.report.relinks[1].armyId == one &&
            out.report.relinks[2].armyId == two && out.report.relinks[3].armyId == three &&
            list(*out.document,2) == std::vector<uint32_t>({three,two,one,carrier,existing}) &&
            list(*out.document,1).empty(),"cargo must relink by slot then prepend, reversing arrival order");
    for (uint32_t id : {one,two,three}) {
        const auto* a = out.document->armyById(id);
        require(a->territory.raw == 1 && a->dest.raw == 2 && a->origin.raw == 1 && a->strength == 211 &&
                a->unk_25 == 11 && a->unk_44.raw == 0xabcdef01,"carried unit budget/order/anchors must remain unchanged");
    }
    require(out.report.untransported.empty(),"reciprocal carried units must not produce missing-transport notices");
    d = fixture(); chain(*d); for (auto& t : d->territories) t.data.terrain = 0;
    const auto cruiser = unit(*d,35), missile = unit(*d,36); carry(*d,cruiser,missile);
    auto sailed = move(*d,{cruiser,2,0});
    require(sailed.report.moved && sailed.document->armyById(missile)->dest.raw == 2 &&
            sailed.document->armyById(missile)->strength == 211,"cruiser must carry missile without spending its range");
    auto forbidden = move(*sailed.document,{missile,2,0});
    require(!forbidden.report.moved && forbidden.report.reason == UnitMovementReason::SiegeCruiserAlreadyMoved &&
            forbidden.report.siegeAdvice,"missile must refuse after its cruiser moved from turn-start");
    auto launched = move(*d,{missile,2,0});
    require(launched.report.moved && launched.document->armyById(cruiser)->dest.raw == 1 &&
            launched.document->armyById(missile)->cargo[0].raw == cruiser,"missile launch must preserve its pair");
    auto blocked = move(*launched.document,{cruiser,2,0});
    require(!blocked.report.moved && blocked.report.reason == UnitMovementReason::SiegeMissileAlreadyLaunched &&
            blocked.report.siegeAdvice,"cruiser must refuse when its missile is elsewhere");
    launched.document->players[0].type = 3;
    blocked = move(*launched.document,{cruiser,2,0}); require(!blocked.report.siegeAdvice,"AI refusal must omit human advice");
    launched.document->players[0].type = 255;
    blocked = move(*launched.document,{cruiser,2,0}); require(blocked.report.siegeAdvice,"advice type test must use signed byte");
}
void transferAndLateRollback() {
    auto d = fixture(); chain(*d); d->territories[1].data.terrain = 0;
    const auto carrier = unit(*d,12,2), passenger = unit(*d,1);
    bind(*d,carrier,0,0); bind(*d,passenger,1,0); d->jobs[0][0].goal = 3;
    save::Error error; ok(ensureArmyPool(*d,error),error);
    const auto physical = armyPoolSlot(*d,passenger);
    UnitMovementContext context; context.paths.creation.movingArmyId = passenger;
    auto aboard = move(*d,{passenger,2,0},context);
    require(aboard.report.transports[0].taskForceTransfer && aboard.document->armyById(passenger)->job == 1 &&
            !aboard.document->jobs[0][1].armyIds[0] && aboard.document->jobs[0][0].armyIds[1] == passenger &&
            aboard.document->armyPool->jobSlots[0][0][1] == physical &&
            aboard.document->armyPool->jobSlots[0][1][0] == 0,
            "boarding must transfer task-force membership without changing physical identity");
    auto destination = std::make_unique<save::Document>(*aboard.document); auto kept = aboard.report;
    const auto destinationBefore = bytes(*destination);
    d->jobs[0][0].goal = 5; const auto sourceBefore = bytes(*d);
    require(!moveUnit(*d,{passenger,2,0},context,*destination,aboard.report,error) &&
            error.message.find("freed passenger") != std::string::npos &&
            bytes(*d) == sourceBefore && bytes(*destination) == destinationBefore && aboard.report == kept,
            "late unsafe task-force branch must roll back paths, relocation, context and report");
    require(!moveUnit(*d,{passenger,2,0},context,*d,aboard.report,error) && bytes(*d) == sourceBefore &&
            aboard.report == kept,"late failure must preserve aliased document");
    d->jobs[0][0].goal = 4; d->raceStats.v[54][0] = 1;
    auto scout = move(*d,{passenger,2,0},context);
    require(scout.report.moved && scout.document->armyById(passenger)->job == 1,
            "scout goal must reuse the canonical scouting query");
    // Explicit moving context filters AI transports by job before the query.
    d->players[0].type = 3;
    auto filtered = move(*d,{passenger,2,0},context);
    require(!filtered.report.moved && filtered.report.reason == UnitMovementReason::OutOfRange &&
            filtered.report.paths.territories[2].distance == 1000,"AI moving context must filter mismatched carrier job");
    context.paths.creation.movingArmyId = 0;
    auto explicitNone = move(*d,{passenger,2,0},context);
    require(explicitNone.report.moved,"no moving context must remain explicit, not inferred from requested unit");
    d = fixture(); chain(*d); d->territories[1].data.terrain = 0;
    const auto fullCarrier = unit(*d,12,2), fresh = unit(*d,1);
    bind(*d,fullCarrier,0,0); bind(*d,fresh,1,0); d->jobs[0][0].goal = 9;
    for (int slot = 1; slot < 16; ++slot) bind(*d,unit(*d,1,3),0,slot);
    auto full = move(*d,{fresh,2,0});
    require(full.report.moved && full.document->armyById(fresh)->job == 0 &&
            full.document->armyById(fresh)->cargo[0].raw == fullCarrier && !full.document->jobs[0][1].armyIds[0],
            "full task force must leave removed passenger job0 while still boarding");
}
void diagnosticsPoolAndAliases() {
    auto d = fixture(); d->territories[0].data.terrain = 0;
    const auto boat = unit(*d,12), stranded = unit(*d,1), foreign = unit(*d,1,1,1);
    auto notices = move(*d,{boat,1,0});
    require(notices.report.moved && notices.report.untransported == std::vector<UnitMovementUntransported>({
            {stranded,1,true},{foreign,1,false},{stranded,1,true},{foreign,1,false}}),
            "debug scans must retain target then turn-start repetitions and own/foreign order");
    d = fixture(); chain(*d); const auto id = unit(*d,1);
    for (int i = 1; i < kMaxArmies; ++i) unit(*d,1,3);
    auto full = move(*d,{id,2,0});
    require(full.report.moved && full.report.creation && !full.report.creation->poolAvailable &&
            full.document->armies.size() == size_t(kMaxArmies) && !full.document->armyPool,
            "movement permission must ignore allocation capacity and must not initialize a pool");
    d = fixture(); chain(*d); const auto moving = unit(*d,1);
    UnitMovementContext context; context.paths.creation.movingArmyId = moving;
    auto expected = move(*d,{moving,2,3},context); UnitMovementReport alias;
    alias.contextAfter = context; save::Error error;
    ok(moveUnit(*d,{moving,2,3},alias.contextAfter,*d,alias,error),error);
    require(alias == expected.report && bytes(*d) == bytes(*expected.document),
            "combined document/context/report aliases changed the result");
    const auto before = bytes(*d); const auto kept = alias;
    for (const auto bad : {UnitMovementRequest{9999,2,0},UnitMovementRequest{moving,0,0},
                           UnitMovementRequest{moving,2,4}}) {
        require(!moveUnit(*d,bad,context,*d,alias,error) && bytes(*d) == before && alias == kept,
                "invalid request must leave aliased output and report intact");
    }
    context.paths.editorMode = true;
    require(!moveUnit(*d,{moving,2,0},context,*d,alias,error) && bytes(*d) == before && alias == kept,
            "unimplemented editor must reject atomically");
    context.paths.editorMode = false; context.paths.creation.movingArmyId = 9999;
    require(!moveUnit(*d,{moving,2,0},context,*d,alias,error) && bytes(*d) == before && alias == kept,
            "unresolved moving context must not leak scratch");
    context.paths.creation.movingArmyId = moving;
    d->territories[0].data.adjacency[0] |= 1; const auto sentinelBefore = bytes(*d);
    require(!moveUnit(*d,{moving,2,0},context,*d,alias,error) && bytes(*d) == sentinelBefore && alias == kept,
            "unrepresented sentinel traversal must fail atomically");
}
void runtimeMovement() {
    auto d = fixture(5); chain(*d); const auto id = unit(*d,1), other = unit(*d,1,5);
    const auto sourceBefore = bytes(*d); save::Error error;
    runtime::State state, foreign; ok(state.prepare(*d,error),error); ok(foreign.prepare(*d,error),error);
    const auto handle = state.armyById(id), survivor = state.armyById(other);
    const auto start = state.territoryByIndex(1), target = state.territoryByIndex(2);
    const auto route = state.territoryByIndex(3); const auto rng = state.sessionRng();
    UnitMovementContext context; context.paths.creation.movingArmyId = id;
    context.paths.sentinelFlags = 0x2001; context.paths.recursionDepth = 6;
    UnitMovementReport report;
    ok(state.moveUnit(handle,2,3,context,report,error),error);
    require(report.moved && state.army(handle) && state.army(survivor) && state.armyById(id) == handle &&
            state.armyLinks(handle)->current == target && state.armyLinks(handle)->turnStart == start &&
            state.armyLinks(handle)->routeOrigin == route &&
            state.graph().territories[1].savedOwnHead == handle &&
            state.stage() == runtime::Stage::EntitiesEdited && state.sessionRng() == rng &&
            state.movementContext() && *state.movementContext() == report.contextAfter && bytes(*d) == sourceBefore,
            "State movement must preserve identities, rebuild typed locations and retain scratch/RNG");
    const auto before = bytes(*state.document()); const auto* pointer = state.document(); const auto kept = report;
    require(!state.moveUnit(foreign.armyById(id),2,0,report.contextAfter,report,error) &&
            state.document() == pointer && bytes(*state.document()) == before && report == kept,
            "foreign handle must not change State or output report");
    require(!state.moveUnit(handle,2,0,context,report,error) && state.document() == pointer &&
            bytes(*state.document()) == before && report == kept,
            "rewound path scratch must not change State or report");
    ok(state.moveUnit(handle,5,0,report.contextAfter,report,error),error);
    require(!report.moved && report.reason == UnitMovementReason::OutOfRange &&
            state.army(handle)->dest.raw == 2 && state.army(handle)->territory.raw == 1 &&
            distance(state.document()->territories[3].data,0) == 3 &&
            distance(state.document()->territories[4].data,0) == 1000 &&
            bytes(*state.document()) != before && *state.movementContext() == report.contextAfter &&
            state.army(survivor) && state.armyLinks(handle)->current == target && state.sessionRng() == rng,
            "native refusal must commit new scratch without relocating or invalidating handles");
    auto captured = fixture(); const auto oldCapture = bytes(*captured);
    require(!state.capture(*captured,error) && bytes(*captured) == oldCapture && !state.advanceTurn(error),
            "movement experiment must not activate save export or a partial turn");
    runtime::State nativeFalse; auto immobile = fixture(); const auto fort = unit(*immobile,19);
    ok(nativeFalse.prepare(*immobile,error),error);
    ok(nativeFalse.moveUnit(nativeFalse.armyById(fort),1,0,{},report,error),error);
    require(!report.moved && nativeFalse.stage() == runtime::Stage::EntitiesEdited &&
            distance(nativeFalse.document()->territories[0].data,0) == 1000 &&
            !nativeFalse.capture(*captured,error),"first native refusal must still commit experimental State scratch");
}
} // namespace
int main() {
    try {
        rtl::srand(0xf1234567u); (void)rtl::lrand(); gg.rng2Seed = 0x87654321;
        const auto low = rtl::seed(), high = rtl::seedHi();
        const auto globals = std::make_unique<GameGlobals>(gg); const auto game = std::make_unique<GameState>(gs);
        totalDistanceAndScratch(); nativeRefusalsAndNoop(); ignoredRelinkFailure(); boardingAndLanding();
        carriedOrderAndSiegePairs(); transferAndLateRollback(); diagnosticsPoolAndAliases(); runtimeMovement();
        require(rtl::seed() == low && rtl::seedHi() == high && std::memcmp(&gg,globals.get(),sizeof(gg)) == 0 &&
                std::memcmp(&gs,game.get(),sizeof(gs)) == 0,"unit movement touched globals or RNG");
        std::cout << "Unit movement tests passed\n"; return 0;
    } catch (const std::exception& exception) {
        std::cerr << "Unit movement: " << exception.what() << '\n'; return 1;
    }
}
