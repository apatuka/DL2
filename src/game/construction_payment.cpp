#include "game/construction_payment.h"
#include "game/data_tables.h"
#include "game/supplemental_tables.h"
#include <algorithm>
#include <bit>
#include <cstring>
#include <exception>
#include <limits>
#include <memory>
#include <new>
#include <stdexcept>
#include <utility>

namespace dl2::simulation {
namespace {
bool fail(save::Error& error, const char* message) {
    error = {save::ErrorCode::InvalidState, 0, message}; return false;
}
int32_t wrap(uint32_t value) { return std::bit_cast<int32_t>(value); }
int32_t add(int32_t a, int32_t b) { return wrap(uint32_t(a) + uint32_t(b)); }
int32_t sub(int32_t a, int32_t b) { return wrap(uint32_t(a) - uint32_t(b)); }
int32_t mul(int32_t a, int32_t b) { return wrap(uint32_t(a) * uint32_t(b)); }
int16_t shortWord(int32_t v) { return std::bit_cast<int16_t>(uint16_t(v)); }
int32_t divide(int32_t a, int32_t b) {
    if (!b || (a == std::numeric_limits<int32_t>::min() && b == -1))
        throw std::domain_error("Construction payment would trap in original signed division");
    return a / b;
}
struct StepLimit {};
int32_t steel(const int32_t* m) {
    //00471cc0/00471fec: exact left-associative source order.
    return add(add(add(mul(m[7],10),mul(m[5],5)),mul(m[6],5)),m[4]);
}
uint8_t* raw(Territory& t) { return reinterpret_cast<uint8_t*>(&t); }
int16_t distance(Territory& t, int player) {
    int16_t value; std::memcpy(&value,raw(t)+0xa70+player*2,2); return value;
}
void distance(Territory& t, int player, int16_t value) { std::memcpy(raw(t)+0xa70+player*2,&value,2); }
bool known(const save::Document& d, int tech, int index) {
    return (uint32_t(int32_t(std::bit_cast<int16_t>(uint16_t(d.techs[size_t(tech)].knownMask)))) &
            (1u << (index & 31))) != 0;
}
bool pact(const save::Document& d, int a, int b, uint32_t mask) {
    if (!d.options.allowAlliances || a < 0 || b < 0 || a >= d.options.numPlayers || b >= d.options.numPlayers) return false;
    const auto relation = d.players[size_t(a)].relations[size_t(b)];
    return mask == ((relation & 0x10u) ? (mask & 0x1eu) : (relation & mask));
}
bool basic(const save::Document& d, uint32_t territory, save::Error& error) {
    if (!save::validate(d,error)) return false;
    if (d.header.isMap || !territory || territory > d.territories.size())
        return fail(error,"Construction payment requires a saved-game territory1..N");
    if (d.territories[territory-1].data.owner < 0 || d.territories[territory-1].data.owner >= kMaxPlayers)
        return fail(error,"Construction payment requires an owned territory");
    return true;
}

struct Work {
    save::Document& document;
    ConstructionPaymentReport& report;
    std::vector<Territory> territories; // Original zero sentinel0, then owned1..N.
    std::vector<bool> city;
    uint32_t target, selected;
    int owner;
    bool reached = false, donorStockExists = false;
    size_t steps = 0;
    Work(save::Document& d, ConstructionPaymentReport& r, uint32_t t, uint32_t selection)
        : document(d), report(r), territories(d.territories.size()+1), city(territories.size()),
          target(t), selected(selection), owner(d.territories[t-1].data.owner) {
        for (size_t i = 0; i < d.territories.size(); ++i) {
            territories[i+1] = d.territories[i].data;
            for (const auto& site : territories[i+1].sites) {
                const auto* b = d.buildingById(site.building.raw);
                //0044d1a4: ANY category9 at a site, including unfinished.
                if (b && b->category == 9) city[i+1] = true;
            }
        }
    }
    void step() { if (++steps > 1000000) throw StepLimit{}; }
    int32_t& credits() { return document.players[size_t(owner)].credits; }
    void clearReservations() { //00471bec, not production output/reset cache.
        for (size_t i = 1; i < territories.size(); ++i) std::fill_n(territories[i].production,11,0);
    }
    void resetSearch() { //0045dfb0 +00446b08(0,owner).
        for (auto& t : territories) { t.flags &= ~(0x2000u << owner); distance(t,owner,0); }
    }
    void search(uint32_t from, int hops, int mode);
    int32_t transportFee(int mode);
    bool findSupplier(int material, int maximumMode);
    int32_t collect(int material, int32_t amount, bool apply, int32_t& left, int32_t& cost);
    int32_t collectSteel(int32_t amount, bool apply);
    int32_t quote();
    uint32_t affordability();
    uint32_t collectRequired();
    void log(uint32_t from, int material, int32_t amount, int32_t cost);
    bool validate(save::Error& error, bool affordability = true);
    void publish() { for (size_t i = 1; i < territories.size(); ++i) document.territories[i-1].data = territories[i]; }
};

bool Work::validate(save::Error& error, bool affordability) {
    if (affordability && selected >= territories.size()) return fail(error,"Construction payment selected territory is outside the owned graph");
    for (size_t i = 1; i < territories.size(); ++i) {
        const auto& t = territories[i];
        if (t.owner < -1 || t.owner >= kMaxPlayers) return fail(error,"Construction payment found an invalid territory owner");
        for (uint32_t j = uint32_t(territories.size()); j < kMaxTerritories; ++j)
            if (t.adjacency[j/16] & (1u << (j%16)))
                return fail(error,"Construction payment adjacency reaches an unused original pool slot");
    }
    for (size_t i = 0; i < report.collection.suppliers.size(); ++i) {
        const auto& supplier = report.collection.suppliers[i];
        if (supplier.territory >= territories.size() || (i >= territories.size() && supplier.territory))
            return fail(error,"Construction payment supplier ID is outside the owned graph");
    }
    if (report.collection.transfers.size() > 250) {
        error = {save::ErrorCode::Limit,0,"Construction transfer log exceeds original250-record storage"}; return false;
    }
    for (const auto& entry : report.collection.transfers)
        if (!entry.from || !entry.to || entry.from >= territories.size() || entry.to >= territories.size() || entry.material < 1 || entry.material > 10)
            return fail(error,"Construction payment transfer log contains invalid entity/material references");
    if (affordability && (report.requirements.technology < 0 || report.requirements.technology >= kNumTechs))
        return fail(error,"Construction requirement technology is outside0..47");
    return true;
}

//00472578: ordered DFS. Mode0 own-only/samecontinent; mode1 permits neutral,
// destination and qualifying allies; mode2 crossescontinents; mode3 anyowner.
void Work::search(uint32_t from, int hops, int mode) {
    step(); auto& current = territories[from];
    current.flags |= 0x2000u << owner; distance(current,owner,shortWord(hops));
    if (from == target || reached) { reached = true; return; }
    for (uint32_t next = 0; next < territories.size(); ++next) {
        if (!(current.adjacency[next/16] & (1u << (next%16)))) continue;
        auto& t = territories[next];
        if (distance(t,owner) || (t.flags & 0x100u) || (current.continent != t.continent && mode <= 1)) continue;
        if (t.owner == owner) search(next,hops+1,mode);
        else if (t.owner == -1 || next == target || (pact(document,owner,t.owner,2) && !city[next]) || pact(document,owner,t.owner,0x10)) {
            if (mode > 0) search(next,hops+1,mode);
        } else if (mode > 2) search(next,hops+1,mode);
    }
}

//00472730: signed racial indexing, addressed within the owned RaceStats bytes.
int32_t Work::transportFee(int mode) {
    int value = 2 + mode;
    if (known(document,46,owner)) value -= 2;
    else if (known(document,13,owner)) --value;
    const int race = document.players[size_t(owner)].race;
    const int offset = 53 * kMaxPlayers * 2 + race * 2;
    if (offset < 0 || size_t(offset) + 2 > sizeof(document.raceStats))
        throw std::domain_error("Construction transport race indexes outside the owned RaceStats block");
    int16_t racial;
    std::memcpy(&racial,reinterpret_cast<const uint8_t*>(&document.raceStats)+offset,2);
    return std::max(0,value+racial);
}

//00472844: first affordable donor in territory order, not a globally cheapest
// source. A previously found but unaffordable donor remains the fallback.
bool Work::findSupplier(int material, int maximumMode) {
    donorStockExists = false; uint32_t donor = 0;
    for (uint32_t candidate = 1; candidate < territories.size(); ++candidate) {
        const auto& t = territories[candidate];
        if (candidate != target && t.owner == owner && t.production[material] < t.materials[material]) {
            donorStockExists = true; reached = false;
            for (int mode = 0; !reached && mode <= maximumMode; ++mode) {
                resetSearch(); search(candidate,1,mode);
                if (reached) { maximumMode = mode; donor = candidate; }
            }
        }
        if (donor) {
            const int32_t fee = transportFee(maximumMode);
            if (fee <= credits()) {
                report.collection.suppliers[target] = {donor,shortWord(fee)}; return true;
            }
        }
    }
    return false;
}

//00471a98: merge first matching record; bounded original250 entries.
void Work::log(uint32_t from, int material, int32_t amount, int32_t cost) {
    for (auto& entry : report.collection.transfers) if (entry.from == from && entry.to == target && entry.material == material) {
        entry.amount = add(entry.amount,amount); entry.credits = add(entry.credits,cost); return;
    }
    if (report.collection.transfers.size() == 250) throw StepLimit{};
    report.collection.transfers.push_back({from,target,material,amount,cost});
}

//00472974; quote restores only cached pointer, not cached signed fee. Both modes
// see the SAME credits for each quoted material, and zero fee caps by credits.
int32_t Work::collect(int material, int32_t amount, bool apply, int32_t& left, int32_t& cost) {
    auto& cache = report.collection.suppliers[target]; const uint32_t prior = cache.territory;
    int32_t total = 0; auto& stock = territories[target].materials[material];
    const int maxMode = known(document,46,owner) ? 3 : 2;
    while (amount >= 1) {
        step();
        if ((!cache.territory || territories[cache.territory].materials[material] <= territories[cache.territory].production[material]) &&
            !findSupplier(material,maxMode)) {
            if (apply && donorStockExists) report.importFailures.push_back({0x3c,target,owner,material});
            break;
        }
        if (!cache.territory || credits() < cache.fee) { cache.territory = 0; continue; }
        auto& donor = territories[cache.territory];
        int32_t quantity = std::min(amount,sub(donor.materials[material],donor.production[material]));
        quantity = std::min(quantity,cache.fee ? divide(credits(),cache.fee) : credits());
        quantity = std::max(0,std::min(quantity,sub(10000,stock)));
        if (!quantity) break;
        const int32_t payment = mul(cache.fee,quantity); total = add(total,payment); amount = sub(amount,quantity);
        if (!apply) donor.production[material] = add(donor.production[material],quantity);
        else {
            stock = add(stock,quantity); donor.materials[material] = sub(donor.materials[material],quantity);
            credits() = sub(credits(),payment); log(cache.territory,material,quantity,payment);
        }
    }
    if (!apply) cache.territory = prior;
    left = amount; cost = total;
    return amount != 0 ? -1 : total;
}

//00472018, metal import preference Triidium, Steel, Endurium, Iron.
int32_t Work::collectSteel(int32_t amount, bool apply) {
    int32_t total = 0;
    for (int i = 0; i < 4 && amount > 0; ++i) {
        step(); const int material = data::kMetalForSteel[i], weight = data::kMetalSteelValue[i];
        int32_t requested = divide(sub(add(weight,amount),1),weight);
        const int32_t before = territories[target].materials[material];
        int32_t remaining = 0, cost = 0;
        // Original local output words are uninitialized if requested<=0.
        // With wrapped positive amount this can occur; reject that undefined
        // quote domain instead of synthesizing initialized local stack values.
        if (requested <= 0) throw std::domain_error("Metal import request overflows into an indeterminate original output domain");
        collect(material,requested,apply,remaining,cost);
        if (!apply) { requested = sub(requested,remaining); total = add(total,cost); }
        else requested = std::min(requested,sub(territories[target].materials[material],before));
        amount = sub(amount,mul(requested,weight));
    }
    return amount > 0 ? -1 : total;
}

//00472ca0: resets reservations once; imports in material order, weightedmetal4.
int32_t Work::quote() {
    clearReservations(); int32_t total = 0;
    for (int material = 1; material < kNumMaterials; ++material) {
        int32_t cost = 0;
        if (material == 4) {
            const int32_t need = sub(report.requirements.materials[4],steel(territories[target].materials));
            if (need > 0) { cost = collectSteel(need,false); if (cost == -1) return -1; }
        } else if (territories[target].materials[material] < report.requirements.materials[material]) {
            int32_t left, paid;
            cost = collect(material,sub(report.requirements.materials[material],territories[target].materials[material]),false,left,paid);
            if (cost == -1) return -1;
        }
        total = add(total,cost);
    }
    return total;
}

//00471e58: peculiar diagnostic target selected rather than passed territory.
uint32_t Work::affordability() {
    uint32_t denied = 0; const auto fee = quote(); report.transportQuote = fee;
    const auto money = report.requirements.materials[0], sum = add(money,fee);
    if (fee == -1 || credits() < fee || (credits() < sum && money < credits())) denied = 0x2000;
    if (report.requirements.technology && !known(document,report.requirements.technology,document.players[size_t(owner)].index)) denied |= 0x1000;
    if (credits() < sum) denied |= 1;
    if (denied & 0x2000) {
        std::array<int32_t,11> all{};
        const int selectedOwner = territories[selected].owner;
        for (size_t i = 1; i < territories.size(); ++i) if (territories[i].owner == selectedOwner)
            for (size_t m = 0; m < all.size(); ++m) all[m] = add(all[m],territories[i].materials[m]);
        for (int material = 1; material < kNumMaterials; ++material) {
            const auto need = report.requirements.materials[material];
            if (need <= 0) continue;
            const auto local = material == 4 ? steel(territories[selected].materials) : territories[selected].materials[material];
            const auto aggregate = material == 4 ? steel(all.data()) : all[size_t(material)];
            if (local < need && aggregate < need) denied |= 1u << material;
        }
    }
    return denied;
}

//004720f4: collected counts accumulate, and steel substitutes are kept as their
// REAL material indices. High-metal direct requests/Art print a diagnostic but
// do not set a failure bit in the original; preserve that observable behavior.
uint32_t Work::collectRequired() {
    clearReservations(); uint32_t denied = 0;
    for (int material = 1; material < kNumMaterials; ++material) {
        const auto need = report.requirements.materials[material];
        if (report.paid[size_t(material)] >= need) continue;
        if (material == 5 || material == 6 || material == 7 || material == 10) continue;
        if (material == 4) {
            int32_t remaining = sub(need,steel(report.paid.data()));
            int32_t available = steel(territories[target].materials);
            if (available < remaining) collectSteel(sub(remaining,available),true);
            available = steel(territories[target].materials);
            for (int i = 0; i < 4; ++i) {
                const int kind = data::kMetalForSteel[i], weight = data::kMetalSteelValue[i];
                auto& stock = territories[target].materials[kind];
                //00472282 assigns available=without and revisits THIS metal.
                // It does not skip to the next material: even with sufficient
                // cheap stock, repeated subtraction can consume a dearer unit.
                while (remaining > 0 && available > 0 && stock != 0) {
                    step(); const int32_t without = sub(available,mul(stock,weight));
                    if (weight <= remaining || without < remaining) {
                        stock = sub(stock,1); report.paid[size_t(kind)] = add(report.paid[size_t(kind)],1);
                        remaining = sub(remaining,weight); available = sub(available,weight);
                    } else available = without;
                }
            }
            if (remaining > 0) denied |= 0x10;
        } else {
            int32_t remaining = sub(need,report.paid[size_t(material)]);
            auto& stock = territories[target].materials[material];
            const auto imported = sub(remaining,stock);
            if (imported > 0) { int32_t left, cost; collect(material,imported,true,left,cost); }
            const auto amount = std::min(remaining,stock);
            stock = sub(stock,amount); report.paid[size_t(material)] = add(report.paid[size_t(material)],amount);
            remaining = sub(remaining,amount); if (remaining) denied |= 1u << material;
        }
    }
    return denied;
}
} // namespace

bool buildingConstructionRequirements(const save::Document& source, uint32_t territory,
    int buildingType, ConstructionRequirements& destination, save::Error& error) try {
    if (!basic(source,territory,error)) return false;
    if (buildingType < 1 || buildingType >= data::kNumBuildingTypes) return fail(error,"Construction building type is outside1..47");
    const auto& def = data::kBuildingTypes[buildingType]; ConstructionRequirements result;
    result.labor = shortWord(def.buildLabor); std::copy_n(def.cost,kNumMaterials,result.materials.begin());
    result.technology = std::bit_cast<int8_t>(def.techRequired);
    if (buildingType == 37) {
        //0044dee9 MOVSX reads Player.index as signed char for city counting,
        // unlike technology shifts, which mask the physical byte with31.
        const int index = std::bit_cast<int8_t>(source.players[size_t(source.territories[territory-1].data.owner)].index);
        int count = 0;
        for (const auto& b : source.buildings) if (b.type == 37 && source.territories[size_t(b.territory-1)].data.owner == index) ++count;
        if (!count) result.materials[0] = result.materials[0] / 4;
        else for (auto& cost : result.materials) cost = mul(cost,count);
    }
    destination = result; error = {}; return true;
} catch (const std::bad_alloc&) { error = {save::ErrorCode::Limit,0,"Construction requirements allocation failed"}; return false; }
  catch (const std::exception& e) { error = {save::ErrorCode::InvalidState,0,e.what()}; return false; }

bool payConstructionRequirements(const save::Document& source, uint32_t territory,
    const ConstructionRequirements& requirements, const ConstructionPaymentContext& context,
    save::Document& destination, ConstructionPaymentReport& report, save::Error& error) try {
    if (!basic(source,territory,error)) return false;
    auto candidate = std::make_unique<save::Document>(source); ConstructionPaymentReport result;
    result.territory = territory; result.owner = source.territories[territory-1].data.owner;
    result.requirements = requirements; result.collection = context.collection;
    result.creditsBefore = source.players[size_t(result.owner)].credits;
    Work work(*candidate,result,territory,context.selectedTerritory);
    if (!work.validate(error)) return false;
    result.affordabilityEvaluated = true;
    result.failureMask = work.affordability(); result.requirementsAccepted = result.failureMask == 0;
    if (result.requirementsAccepted) {
        work.credits() = sub(work.credits(),requirements.materials[0]); result.paid[0] = requirements.materials[0];
        result.collectionAttempted = true; result.failureMask = work.collectRequired();
    }
    result.creditsAfter = work.credits(); work.publish();
    if (!save::validate(*candidate,error)) return false;
    destination = std::move(*candidate); report = std::move(result); error = {}; return true;
} catch (const StepLimit&) { error = {save::ErrorCode::Limit,0,"Construction collection exceeds traversal/transfer storage safety bound"}; return false; }
  catch (const std::bad_alloc&) { error = {save::ErrorCode::Limit,0,"Construction payment allocation failed"}; return false; }
  catch (const std::length_error&) { error = {save::ErrorCode::Limit,0,"Construction payment allocation exceeds limit"}; return false; }
  catch (const std::exception& e) { error = {save::ErrorCode::InvalidState,0,e.what()}; return false; }

bool collectConstructionRequirements(const save::Document& source, uint32_t territory,
    const ConstructionRequirements& requirements,
    const std::array<int32_t, kNumMaterials>& paidBefore,
    const ConstructionPaymentContext& context, save::Document& destination,
    ConstructionPaymentReport& report, save::Error& error) try {
    if (!basic(source,territory,error)) return false;
    auto candidate = std::make_unique<save::Document>(source); ConstructionPaymentReport result;
    result.territory = territory; result.owner = source.territories[territory-1].data.owner;
    result.requirements = requirements; result.collection = context.collection; result.paid = paidBefore;
    result.creditsBefore = source.players[size_t(result.owner)].credits;
    Work work(*candidate,result,territory,context.selectedTerritory);
    if (!work.validate(error,false)) return false;
    result.collectionAttempted = true;
    result.failureMask = work.collectRequired();
    result.creditsAfter = work.credits(); work.publish();
    if (!save::validate(*candidate,error)) return false;
    destination = std::move(*candidate); report = std::move(result); error = {}; return true;
} catch (const StepLimit&) { error = {save::ErrorCode::Limit,0,"Incremental construction collection exceeds traversal/transfer storage safety bound"}; return false; }
  catch (const std::bad_alloc&) { error = {save::ErrorCode::Limit,0,"Incremental construction collection allocation failed"}; return false; }
  catch (const std::length_error&) { error = {save::ErrorCode::Limit,0,"Incremental construction collection allocation exceeds limit"}; return false; }
  catch (const std::exception& e) { error = {save::ErrorCode::InvalidState,0,e.what()}; return false; }
} // namespace dl2::simulation
