#include "game/economic_consumption.h"
#include "game/economic_logistics.h"
#include "game/army_state.h"
#include "game/data_tables.h"
#include <algorithm>
#include <bit>
#include <cstring>
#include <memory>
#include <stdexcept>

namespace dl2::simulation {
namespace {
bool fail(save::Error& error, const char* text) {
    error = {save::ErrorCode::InvalidState, 0, text}; return false;
}
int32_t sub(int32_t a, int32_t b) { return std::bit_cast<int32_t>(uint32_t(a) - uint32_t(b)); }
int16_t short16(int32_t a) { return std::bit_cast<int16_t>(uint16_t(uint32_t(a))); }
template<class F> bool guarded(F&& f, save::Error& error) {
    try { return f(); }
    catch (const std::bad_alloc&) { error = {save::ErrorCode::Limit, 0, "Economic consumption allocation failed"}; }
    catch (const std::exception& e) { error = {save::ErrorCode::InvalidState, 0, std::string("Economic consumption: ") + e.what()}; }
    return false;
}
template<class Report> bool emit(save::Document& d, const ConstructionOrderContext& context, Report& r,
                                 int recipient, uint16_t type, uint32_t territory, int32_t detail, save::Error& error) {
    if (recipient < 0 || recipient >= kMaxPlayers) return fail(error, "Economic consumption event recipient outside0..6");
    ConstructionOrderEvent event; event.type = type; event.recipient = recipient;
    if (recipient == d.options.localPlayer) {
        LocalEventRequest request; request.type = type;
        if (territory) {
            const auto& t = d.territories[territory - 1].data;
            const auto* end = static_cast<const char*>(std::memchr(t.name, 0, sizeof(t.name)));
            if (!end) return fail(error, "Economic consumption event name lacks a bounded terminator");
            request.arguments.emplace_back(std::string(t.name, size_t(end - t.name)));
            if (type == 51) request.arguments.emplace_back(detail);
            request.payload = EventPayload{int32_t(territory), 0};
        }
        event.local = true;
        auto next = context.events; next.rngBeforeEvents = r.rngAfter;
        if (!logLocalEvent(d, r.logAfter, next, request, r.logAfter, event.localReport, error)) return false;
        r.rngAfter = event.localReport.rngAfter;
    } else if (std::bit_cast<int8_t>(d.players[size_t(recipient)].type) >= 3) {
        if (!context.aiSession || context.ai.rng != context.events.rngBeforeEvents)
            return fail(error, "Economic consumption requires owned AI bindings and a single initial RNG");
        event.aiDispatched = true; r.aiAfter.rng = r.rngAfter;
        if (!context.aiSession->reactEvent(d, {recipient, type, int32_t(territory), 0}, r.aiAfter, d, event.aiReport, error)) return false;
        r.aiAfter = event.aiReport.contextAfter; r.rngAfter = r.aiAfter.rng;
    }
    r.aiAfter.rng = r.rngAfter; r.events.push_back(std::move(event)); return true;
}
bool mobileMission(uint8_t mission) {
    //00446bf0 reads Army+25, NOT the similarly named Army.unitClass+07.
    switch (mission) {
    case 1: case 2: case 3: case 4: case 5: case 6: case 15: case 16: case 19: return true;
    default: return false;
    }
}
bool validContext(const ConstructionOrderContext& context, save::Error& error) {
    SessionRng rng;
    if (!rng.restore(context.events.rngBeforeEvents, error)) return false;
    return context.ai.rng == context.events.rngBeforeEvents ||
        fail(error, "Economic consumption requires one shared event/AI RNG");
}
}

// orig: ConsumeFood0046b9e8
bool consumeFood(const save::Document& source, const ConstructionOrderContext& context,
                 save::Document& destination, FoodConsumptionReport& report, save::Error& error) {
    return guarded([&] {
        if (!validContext(context, error)) return false;
        NeedsPlan needs;
        if (!planNeeds(source, needs, error)) return false;
        auto owned = std::make_unique<save::Document>(source); auto& d = *owned;
        FoodConsumptionReport r; r.logAfter = context.log; r.aiAfter = context.ai;
        r.rngAfter = context.events.rngBeforeEvents; r.collectionAfter = context.payment.collection;
        for (const auto& n : needs.territories) {
            auto& t = d.territories[n.territory - 1].data;
            TerritoryFoodChange change; change.territory = n.territory; change.need = n.foodNeed;
            change.stockBefore = t.materials[1]; change.reserveBefore = t.production[1]; change.hungerBefore = t.unk_28[1];
            const int32_t available = std::min(t.materials[1], n.foodNeed);
            change.consumed = short16(available);
            t.materials[1] = change.stockAfter = sub(t.materials[1], change.consumed);
            t.production[1] = change.reserveAfter = sub(t.production[1], change.consumed);
            const int hunger = std::bit_cast<int8_t>(t.unk_28[1]);
            const int next = available < n.foodNeed ? std::min(hunger + 1, 7) : std::max(hunger - 1, 0);
            t.unk_28[1] = change.hungerAfter = uint8_t(next);
            // Dispatch before the next territory. AI50 default does not mutate d,
            // but no reference into d is retained across the owned callback.
            const int owner = t.owner;
            r.territories.push_back(change);
            if (available < n.foodNeed && next == 1 && !emit(d, context, r, owner, 50, n.territory, 0, error)) return false;
        }
        for (size_t p = 0; p < kMaxPlayers; ++p) {
            r.flagsBefore[p] = d.players[p].foodFlags; d.players[p].foodFlags &= uint8_t(0xfd);
        }
        // No food callback creates/deletes armies. Preserve physical document
        // order, the owned allocator representation, rather than sorting by ID.
        const size_t count = d.armies.size();
        for (size_t i = 0; i < count; ++i) {
            const Army a = d.armies[i];
            if (!a.type) continue;
            if (a.owner < 0 || a.owner >= kMaxPlayers || a.type >= data::kNumUnitTypes)
                return fail(error, "ConsumeFood army owner/type outside canonical bounds");
            UnitFoodChange change; change.army = a.id; change.territory = army::current(a);
            if (!change.territory) { r.armies.push_back(change); continue; }
            if (change.territory > d.territories.size()) return fail(error, "ConsumeFood army current territory is invalid");
            const auto& local = d.territories[change.territory - 1].data;
            if (local.owner == a.owner && local.materials[1] > 0) {
                d.territories[change.territory - 1].data.materials[1] = sub(local.materials[1], 1);
                change.source = UnitFoodSource::LocalStock; r.armies.push_back(change); continue;
            }
            if (mobileMission(a.unk_25) || data::kUnitTypes[a.type].domain == 3) {
                SupplierSearchReport search;
                if (!findMaterialSupplier(d, {change.territory, a.owner, 1, 3}, r.collectionAfter, d, search, error)) return false;
                r.collectionAfter = search.collection;
                if (search.found) {
                    const uint32_t supplier = r.collectionAfter.suppliers[change.territory].territory;
                    if (!supplier || supplier > d.territories.size()) return fail(error, "ConsumeFood supplier search returned an invalid territory");
                    auto& stock = d.territories[supplier - 1].data.materials[1]; stock = sub(stock, 1);
                    r.collectionAfter.suppliers[change.territory].territory = 0; // fee survives, exactly as +ad6=0.
                    change.source = UnitFoodSource::FreeSupplier; change.supplier = supplier;
                    r.armies.push_back(change); continue;
                }
            }
            auto next = context; next.log = r.logAfter; next.ai = r.aiAfter; next.events.rngBeforeEvents = r.rngAfter;
            next.payment.collection = r.collectionAfter;
            EconomicLogisticsReport collected;
            if (!collectMaterial(d, {change.territory, a.owner, 1, 1, true}, next, d, collected, error)) return false;
            r.logAfter = std::move(collected.logAfter); r.aiAfter = std::move(collected.aiAfter);
            r.rngAfter = collected.rngAfter; r.collectionAfter = std::move(collected.collectionAfter);
            r.events.insert(r.events.end(), collected.events.begin(), collected.events.end());
            if (collected.collections.size() != 1) return fail(error, "ConsumeFood collector did not report exactly one call");
            change.collectionResult = collected.collections.front().result;
            if (change.collectionResult == -1) {
                d.players[size_t(a.owner)].foodFlags |= 2; change.source = UnitFoodSource::Starved;
            } else {
                auto& stock = d.territories[change.territory - 1].data.materials[1]; stock = sub(stock, 1);
                change.source = UnitFoodSource::Collected;
            }
            r.armies.push_back(change);
        }
        for (size_t p = 0; p < kMaxPlayers; ++p) {
            if (d.players[p].foodFlags & 2) {
                if (!(r.flagsBefore[p] & 2)) {
                    if (!emit(d, context, r, int(p), 2, 0, 0, error)) return false;
                } else d.players[p].foodFlags |= 4;
            }
            r.flagsAfter[p] = d.players[p].foodFlags;
        }
        r.aiAfter.rng = r.rngAfter;
        if (!save::validate(d, error)) return false;
        destination = std::move(d); report = std::move(r); error = {}; return true;
    }, error);
}

// orig: FUN_0046bc28 (ConsumeEnergy)
bool consumeEconomicEnergy(const save::Document& source, const ConstructionOrderContext& context,
                           save::Document& destination, EnergyConsumptionReport& report, save::Error& error) {
    return guarded([&] {
        if (!validContext(context, error)) return false;
        EnergyConsumptionReport r;
        if (!planEnergy(source, r.energy, error)) return false;
        auto owned = std::make_unique<save::Document>(source); auto& d = *owned;
        r.logAfter = context.log; r.aiAfter = context.ai; r.rngAfter = context.events.rngBeforeEvents;
        size_t notice = 0;
        for (const auto& change : r.energy.territories) {
            auto& t = d.territories[change.territory - 1].data;
            t.materials[2] = change.energyAfter; t.knowledge = change.energyPercentAfter;
            if (notice < r.energy.shortfalls.size() && r.energy.shortfalls[notice].territory == change.territory) {
                const auto& event = r.energy.shortfalls[notice++];
                if (!emit(d, context, r, event.recipient, event.type, event.territory, event.shortage, error)) return false;
            }
        }
        r.aiAfter.rng = r.rngAfter;
        if (!save::validate(d, error)) return false;
        destination = std::move(d); report = std::move(r); error = {}; return true;
    }, error);
}
} // namespace dl2::simulation
