// Execution-state laboratory. Isolated experiments are not completed game turns.
#include "game/runtime_state.h"
#include "game/construction_site.h"
#include "game/production_plan.h"
#include "game/entity_rules.h"
#include "game/save_files.h"
#include <charconv>
#include <bit>
#include <iostream>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>

namespace {
using namespace dl2;
void require(bool success, const save::Error& error) {
    if (!success) throw std::runtime_error(error.message);
}
int integer(std::string_view value) {
    int result = 0;
    const auto parsed = std::from_chars(value.data(), value.data() + value.size(), result);
    if (parsed.ec != std::errc{} || parsed.ptr != value.data() + value.size())
        throw std::runtime_error("Numeric arguments must be decimal integers in int32 range");
    return result;
}
void placement(const runtime::State& state, const simulation::BuildingPlacement& result) {
    std::cout << std::boolalpha
              << "{\"stage\":\"prepared\",\"read_only\":true,\"complete_turn\":false,"
                 "\"complete_build_permission\":false,\"applies_construction\":false,\"turn\":"
              << state.document()->options.turn << ",\"territory\":" << result.territory
              << ",\"building_type\":" << result.buildingType << ",\"site\":" << result.site
              << ",\"placement_allowed\":" << (result.reason == simulation::PlacementReason::Allowed)
              << ",\"reason\":" << int(result.reason) << ",\"footprint\":{\"size\":" << int(result.footprint.size)
              << ",\"fits\":" << result.footprint.fits << ",\"sites\":[";
    for (size_t i = 0; i < result.footprint.sites.size(); ++i)
        std::cout << (i ? "," : "") << int(result.footprint.sites[i]);
    std::cout << "]}}\n";
}
void summary(const runtime::State& state) {
    const auto& d = *state.document(); const auto& g = state.graph();
    size_t tileRefs = 0;
    for (const auto& t : g.territories) tileRefs += t.tiles.size();
    std::cout << "{\"stage\":\"prepared\",\"complete_turn\":false,\"turn\":" << d.options.turn
              << ",\"territories\":" << g.territories.size() << ",\"buildings\":" << g.buildings.size()
              << ",\"armies\":" << g.armies.size() << ",\"tile_refs\":" << tileRefs
              << ",\"queues\":" << g.queues.size() << ",\"queue_nodes\":" << g.queueNodes.size()
              << ",\"minister_nodes\":" << g.ministers.size() << "}\n";
}
void taxes(const runtime::State& state, const simulation::TaxPlan& plan, int before) {
    std::cout << "{\"stage\":\"taxes_applied_in_memory\",\"complete_turn\":false,\"turn_before\":" << before
              << ",\"turn_after\":" << state.document()->options.turn << ",\"players\":[";
    for (size_t p = 0; p < kMaxPlayers; ++p)
        std::cout << (p ? "," : "") << "{\"player\":" << p << ",\"before\":" << plan.creditsBefore[p]
                  << ",\"collected\":" << plan.collected[p] << ",\"after\":" << plan.creditsAfter[p] << "}";
    std::cout << "],\"territories\":[";
    for (size_t i = 0; i < plan.territories.size(); ++i) {
        const auto& t = plan.territories[i];
        std::cout << (i ? "," : "") << "{\"territory\":" << t.territory << ",\"owner\":" << t.owner
                  << ",\"calculated\":" << t.calculated << ",\"applied\":" << t.applied << "}";
    }
    std::cout << "]}\n";
}
void energy(const runtime::State& state, const simulation::EnergyPlan& plan, int before) {
    std::cout << "{\"stage\":\"energy_applied_in_memory\",\"isolated\":true,\"complete_turn\":false,\"turn_before\":" << before
              << ",\"turn_after\":" << state.document()->options.turn << ",\"territories\":[";
    for (size_t i = 0; i < plan.territories.size(); ++i) {
        const auto& t = plan.territories[i];
        std::cout << (i ? "," : "") << "{\"territory\":" << t.territory << ",\"before\":" << t.energyBefore
                  << ",\"need\":" << t.need << ",\"consumed\":" << t.consumed << ",\"after\":" << t.energyAfter
                  << ",\"percent_before\":" << int(t.energyPercentBefore)
                  << ",\"percent_after\":" << int(t.energyPercentAfter) << "}";
    }
    std::cout << "],\"shortfalls\":[";
    for (size_t i = 0; i < plan.shortfalls.size(); ++i) {
        const auto& e = plan.shortfalls[i];
        std::cout << (i ? "," : "") << "{\"type\":" << e.type << ",\"recipient\":" << e.recipient
                  << ",\"territory\":" << e.territory << ",\"shortage\":" << e.shortage << "}";
    }
    std::cout << "]}\n";
}
template<class Range> void numbers(const Range& values) {
    std::cout << "[";
    for (size_t i = 0; i < std::size(values); ++i) std::cout << (i ? "," : "") << int64_t(values[i]);
    std::cout << "]";
}
void laborSnapshot(const simulation::BuildingLaborState& state) {
    std::cout << "{\"flags\":" << state.flags << ",\"tasks\":";
    numbers(state.tasks); std::cout << ",\"labor\":"; numbers(state.labor); std::cout << "}";
}
void labor(const runtime::State& state, const simulation::LaborBalancePlan& plan, int before) {
    std::cout << "{\"stage\":\"labor_balanced_in_memory\",\"isolated\":true,"
                 "\"complete_turn\":false,\"complete_load\":false,\"applies_production\":false,\"turn_before\":"
              << before << ",\"turn_after\":" << state.document()->options.turn << ",\"buildings\":[";
    for (size_t i = 0; i < plan.buildings.size(); ++i) {
        const auto& b = plan.buildings[i];
        std::cout << (i ? "," : "") << "{\"id\":" << b.buildingId << ",\"territory\":" << b.territory
                  << ",\"site\":" << int(b.site) << ",\"before\":";
        laborSnapshot(b.before); std::cout << ",\"after\":"; laborSnapshot(b.after); std::cout << "}";
    }
    std::cout << "],\"territories\":[";
    for (size_t i = 0; i < plan.territories.size(); ++i) {
        const auto& t = plan.territories[i];
        std::cout << (i ? "," : "") << "{\"territory\":" << t.territory << ",\"labor_pool\":" << t.laborPool
                  << ",\"unavailable_labor\":" << t.unavailableLabor << ",\"assigned_labor\":" << t.assignedLabor
                  << ",\"unassigned_labor\":" << t.unassignedLabor << ",\"morale_before\":" << int(t.moraleBefore)
                  << ",\"morale_after\":" << int(t.moraleAfter) << ",\"materials_before\":";
        numbers(t.materialsBefore); std::cout << ",\"materials_after\":"; numbers(t.materialsAfter); std::cout << "}";
    }
    std::cout << "]}\n";
}
void slots(const std::array<simulation::SlotProduction, 5>& values) {
    std::cout << "[";
    for (size_t i = 0; i < values.size(); ++i) {
        const auto& s = values[i];
        std::cout << (i ? "," : "") << "{\"task\":" << int(s.task) << ",\"labor\":" << s.labor
                  << ",\"output\":" << s.output << "}";
    }
    std::cout << "]";
}
void economy(const runtime::State& state, const simulation::ProductionPlan& production,
             const simulation::NeedsPlan& needs) {
    std::cout << std::boolalpha
              << "{\"stage\":\"prepared\",\"read_only\":true,\"complete_turn\":false,"
                 "\"snapshot\":\"as_saved\",\"applies_production\":false,\"empty_task_slots\":\"normalized_zero\",\"turn\":"
              << state.document()->options.turn << ",\"needs\":[";
    for (size_t i = 0; i < needs.territories.size(); ++i) {
        const auto& n = needs.territories[i];
        std::cout << (i ? "," : "") << "{\"territory\":" << n.territory << ",\"food\":" << n.foodNeed
                  << ",\"energy\":" << n.energyNeed << ",\"food_reserve\":" << n.foodReserve
                  << ",\"energy_reserve\":" << n.energyReserve << "}";
    }
    std::cout << "],\"production\":[";
    for (size_t i = 0; i < production.territories.size(); ++i) {
        const auto& t = production.territories[i];
        std::cout << (i ? "," : "") << "{\"territory\":" << t.territory << ",\"owner\":" << t.owner << ",\"buildings\":[";
        for (size_t j = 0; j < t.buildings.size(); ++j) {
            const auto& b = t.buildings[j];
            std::cout << (j ? "," : "") << "{\"id\":" << b.buildingId << ",\"site\":" << int(b.site)
                      << ",\"type\":" << int(b.type) << ",\"category\":" << int(b.category)
                      << ",\"active\":" << b.active << ",\"built\":" << b.built << ",\"evaluated\":" << b.evaluated
                      << ",\"max_labor\":" << b.maxLabor << ",\"assigned\":";
            slots(b.assigned); std::cout << ",\"maximum\":"; slots(b.maximum); std::cout << "}";
        }
        std::cout << "]}";
    }
    std::cout << "]}\n";
}
void load(const runtime::State& state, const runtime::LoadReport& report, int before) {
    std::cout << std::boolalpha << "{\"stage\":\"load_normalized_in_memory\",\"complete_load\":false,\"can_play\":false,"
                 "\"complete_turn\":false,\"turn_before\":" << before
              << ",\"turn_after\":" << state.document()->options.turn
              << ",\"local_player\":" << report.core.localPlayer
              << ",\"ai_skill\":" << report.core.aiSkillAfter
              << ",\"source_version\":" << report.core.version << ",\"normalized_version\":" << report.core.normalizedVersion
              << ",\"legacy_jobs_discarded\":" << report.core.discardedLegacyJobs
              << ",\"ai_data_initialized\":" << report.core.session.initialized
              << ",\"ai_executable\":" << report.core.session.aiExecutable
              << ",\"ai_initialization_complete\":" << report.aiInitialized
              << ",\"startup_rebuilt\":" << report.startupRebuilt
              << ",\"world_presentation_rebuilt\":" << report.worldPresentationRebuilt
              << ",\"timer_planned\":" << report.timerPlanned
              << ",\"headless_load_complete\":" << report.headlessComplete
              << ",\"shrine_notices_delivered\":" << report.shrineNoticesDelivered
              << ",\"shrine_random_draws\":" << report.shrineRandomDraws
              << ",\"campaign_goal_mask\":" << report.core.campaignGoalMask
              << ",\"campaign_progress\":";
    numbers(report.core.campaignProgress);
    std::cout << ",\"continents_rebuilt\":true,\"roads_rebuilt\":true,\"shrines_rebuilt\":true,"
                 "\"labor_normalized\":true,\"territories\":" << report.labor.territories.size()
              << ",\"buildings\":" << report.labor.buildings.size()
              << ",\"shrine_notices\":" << report.derived.notices.size()
              << ",\"visibility_rebuilt\":" << report.intelligence.visibilityRebuilt
              << ",\"building_intelligence_rebuilt\":" << report.intelligence.buildingIntelligenceRebuilt
              << ",\"contact_discovery_skipped_on_load\":" << report.intelligence.contactDiscoverySkippedOnLoad
              << ",\"events_rebuilt\":" << report.eventsRebuilt << ",\"loaded_events\":" << report.loadedEvents
              << ",\"event_random_draws\":" << report.eventRandomDraws
              << ",\"evicted_events\":" << report.evictedEvents
              << ",\"rng\":{\"seed_source\":\"options.gameId\",\"rtl_low\":" << report.rng.rtlLow
              << ",\"rtl_high\":" << report.rng.rtlHigh << ",\"secondary\":" << report.rng.secondary
              << ",\"operations\":" << report.rng.counters.operations << "},\"missing\":[";
    for (size_t i = 0; i < report.missing.size(); ++i)
        std::cout << (i ? "," : "") << '"' << runtime::missingLoadCapabilityName(report.missing[i]) << '"';
    std::cout << "],\"playability_missing\":[\"ai_turn\",\"complete_turn\",\"native_presentation\"]}\n";
}
void createdBuilding(const runtime::State& state, const simulation::BuildingCreationReport& report) {
    std::cout << std::boolalpha << "{\"stage\":\"entities_edited_in_memory\",\"complete_turn\":false,\"paid_construction_order\":false,"
                 "\"finished_building\":true,\"building_id\":" << report.buildingId
              << ",\"territory\":" << report.territory << ",\"building_type\":" << report.buildingType
              << ",\"site\":" << report.site << ",\"counter_before\":" << report.counterBefore
              << ",\"counter_after\":" << report.counterAfter << ",\"building_count\":" << state.document()->buildings.size()
              << ",\"local_labor_balanced\":" << report.localLaborBalanced << ",\"site_roads_rebuilt\":" << report.siteRoadsRebuilt
              << ",\"companion_id\":" << report.companionBuildingId << ",\"companion_attempted\":" << report.companionAttempted
              << ",\"companion_allocation_failed\":" << report.companionAllocationFailed << ",\"turn\":" << state.document()->options.turn
              << ",\"footprint\":[";
    for (size_t i = 0; i < report.footprint.size(); ++i) std::cout << (i ? "," : "") << int(report.footprint[i]);
    std::cout << "]}\n";
}
void buildingLifecycle(const runtime::State& state, const simulation::BuildingLifecycleReport& report) {
    std::cout << std::boolalpha << "{\"stage\":\"entities_edited_in_memory\",\"complete_turn\":false,\"building_id\":"
              << report.primaryId << ",\"building_count\":" << state.document()->buildings.size()
              << ",\"territory\":" << report.territory << ",\"refund_player\":" << report.refundPlayer
              << ",\"refund_credits\":" << report.credits << ",\"refund_materials\":";
    numbers(report.materials);
    std::cout << ",\"local_labor_balanced\":" << report.localLaborBalanced
              << ",\"roads_target_was_sentinel\":" << report.originalRoadsTargetWasSentinel
              << ",\"deferred_build_jobs\":" << report.deferredBuildJobs << ",\"turn\":" << state.document()->options.turn << "}\n";
}
void constructionOrder(const runtime::State& state, const simulation::ConstructionOrderReport& report) {
    const auto* building = state.document()->buildingById(report.attemptedId);
    std::cout << std::boolalpha << "{\"stage\":\"entities_edited_in_memory\",\"complete_turn\":false,\"paid_construction_order\":true,"
                 "\"accepted\":" << report.accepted << ",\"denial\":" << int(report.denial)
              << ",\"attempted_id\":" << report.attemptedId << ",\"building_count\":" << state.document()->buildings.size()
              << ",\"counter_before\":" << report.counterBefore << ",\"counter_after\":" << report.counterAfter
              << ",\"payment_evaluated\":" << report.paymentEvaluated << ",\"failure_mask\":" << report.payment.failureMask
              << ",\"credits_before\":" << report.payment.creditsBefore << ",\"credits_after\":" << report.payment.creditsAfter
              << ",\"work_remaining\":" << (building ? building->turnsLeft : 0) << ",\"paid\":";
    numbers(report.payment.paid);
    std::cout << ",\"local_labor_balanced\":" << report.localLaborBalanced << ",\"site_roads_rebuilt\":" << report.siteRoadsRebuilt
              << ",\"events_dispatched\":" << report.events.size() << ",\"logged_events\":" << report.logAfter.entries.size()
              << ",\"rng_operations\":" << report.rngAfter.counters.operations << ",\"turn\":" << state.document()->options.turn << "}\n";
}
void armyLifecycle(const runtime::State& state, const simulation::ArmyLifecycleReport& report) {
    std::cout << std::boolalpha << "{\"stage\":\"entities_edited_in_memory\",\"complete_turn\":false,\"manufacturing_order\":false,"
        "\"primary_id\":" << report.primaryId << ",\"created_ids\":";
    numbers(report.createdIds); std::cout << ",\"removed_ids\":"; numbers(report.removedIds);
    std::cout << ",\"army_count\":" << state.document()->armies.size()
              << ",\"counter_before\":" << report.counterBefore << ",\"counter_after\":" << report.counterAfter
              << ",\"carrier_id\":" << report.carrierId << ",\"paired_missile_id\":" << report.pairedMissileId
              << ",\"paired_missile_attempted\":" << report.pairedMissileAttempted
              << ",\"refund_count\":" << report.refunds.size() << ",\"deferred_maintain_jobs\":" << report.deferredMaintainJobs
              << ",\"turn\":" << state.document()->options.turn << "}\n";
}
simulation::ConstructionOrderContext coldOrderContext(const save::Document& document, uint32_t territory,
                                                       int seed, save::Error& error) {
    simulation::ConstructionOrderContext context;
    simulation::SessionRng rng;
    require(rng.initialize(uint32_t(seed), error), error);
    context.events.rngBeforeEvents = rng.snapshot();
    require(simulation::rebuildLoadedEvents(document, context.events, context.log, error), error);
    context.events.rngBeforeEvents = context.log.rngAfterEvents;
    context.ai.rng = context.events.rngBeforeEvents;
    context.payment.selectedTerritory = territory;
    return context; // Explicit cold context, not recovery of absent SAV transients.
}
void queueContents(const runtime::State& state, uint32_t territory, int category) {
    std::cout << ",\"queue_records\":[";
    if (category >= 1 && category <= 5) {
        const auto& records = state.document()->territories[territory - 1].queues[size_t(category - 1)];
        for (size_t n = 0; n < records.size(); ++n) {
            std::cout << (n ? "," : "") << "{\"unit_type\":" << int(records[n].unitType)
                      << ",\"work_remaining\":" << std::bit_cast<int16_t>(records[n].count) << ",\"paid\":";
            numbers(records[n].data); std::cout << "}";
        }
    }
    std::cout << "]";
}
void manufacturing(const runtime::State& state, const simulation::UnitManufacturingReport& report) {
    const auto& d = *state.document();
    const int owner = d.territories[report.territory - 1].data.owner;
    std::cout << std::boolalpha << "{\"stage\":\"entities_edited_in_memory\",\"isolated\":true,\"complete_turn\":false,"
                 "\"manufacturing_substep\":true,\"can_save\":false,\"queued\":" << report.queued
              << ",\"territory\":" << report.territory << ",\"queue\":" << report.queue
              << ",\"failure_mask\":" << report.failureMask << ",\"head_financing_blocked\":" << report.headFinancingBlocked
              << ",\"creation_blocked\":" << report.creationBlocked << ",\"production_supplied\":" << report.productionBefore
              << ",\"production_remaining\":" << report.productionRemaining << ",\"created_ids\":";
    numbers(report.createdIds);
    std::cout << ",\"army_count\":" << d.armies.size() << ",\"credits_after\":" << d.players[size_t(owner)].credits
              << ",\"population_before\":" << report.populationBefore << ",\"population_after\":" << report.populationAfter
              << ",\"events_dispatched\":" << report.events.size() << ",\"logged_events\":" << report.logAfter.entries.size()
              << ",\"rng_operations\":" << report.rngAfter.counters.operations << ",\"turn\":" << d.options.turn;
    queueContents(state, report.territory, report.queue); std::cout << "}\n";
}
void buildingProgress(const runtime::State& state, const simulation::BuildingProgressReport& report) {
    std::cout << std::boolalpha << "{\"stage\":\"entities_edited_in_memory\",\"isolated\":true,\"complete_turn\":false,"
                 "\"complete_production_pass\":false,\"can_save\":false,\"territory\":" << report.territory
              << ",\"initial_labor_balanced\":" << report.initialLaborBalanced << ",\"changes\":[";
    for (size_t i = 0; i < report.changes.size(); ++i) {
        const auto& c = report.changes[i];
        std::cout << (i ? "," : "") << "{\"building_id\":" << c.buildingId << ",\"slot\":" << c.slot
                  << ",\"task\":" << int(c.task) << ",\"output\":" << c.output
                  << ",\"type_before\":" << int(c.typeBefore) << ",\"type_after\":" << int(c.typeAfter)
                  << ",\"site_before\":" << int(c.siteBefore) << ",\"site_after\":" << int(c.siteAfter)
                  << ",\"work_before\":" << c.workBefore << ",\"work_after\":" << c.workAfter
                  << ",\"upgrade_before\":" << c.upgradeBefore << ",\"upgrade_after\":" << c.upgradeAfter
                  << ",\"completed\":" << c.completed << ",\"upgraded\":" << c.upgraded << "}";
    }
    std::cout << "],\"events_dispatched\":" << report.events.size() << ",\"logged_events\":" << report.logAfter.entries.size()
              << ",\"rng_operations\":" << report.rngAfter.counters.operations
              << ",\"turn\":" << state.document()->options.turn << "}\n";
}
void economicPrefix(const runtime::State& state, const simulation::EconomicPrefixReport& r) {
    std::cout << std::boolalpha << "{\"stage\":\"economic_prefix_applied\",\"complete_turn\":false,"
        "\"complete_economic_phase\":false,\"can_save\":false,\"cold_lab_context\":true,\"completed_steps\":[";
    for (size_t i = 0; i < r.completed.size(); ++i)
        std::cout << (i ? "," : "") << '"' << simulation::economicStepName(r.completed[i]) << '"';
    std::cout << "],\"next_step\":\"population_growth\",\"created_ids\":"; numbers(r.createdIds);
    std::cout << ",\"retired_ids\":"; numbers(r.retiredIds);
    std::cout << ",\"primary_territories\":" << r.primary.territories.size()
              << ",\"refinement_territories\":" << r.refinement.territories.size()
              << ",\"import_attempts\":" << r.imports.collections.size()
              << ",\"transfers\":" << r.collectionAfter.transfers.size()
              << ",\"pending_buildings_evaluated\":" << r.costs.buildings.size()
              << ",\"logged_events\":" << r.logAfter.entries.size()
              << ",\"rng_operations\":" << r.rngAfter.counters.operations
              << ",\"army_count\":" << state.document()->armies.size() << ",\"credits_after\":[";
    for (int p = 0; p < kMaxPlayers; ++p) std::cout << (p ? "," : "") << state.document()->players[size_t(p)].credits;
    std::cout << "],\"turn\":" << state.document()->options.turn << "}\n";
}
int usage() {
    std::cout << "Execution preparation / economic laboratory. NOT a complete turn.\n"
                 "  dl2sim prepare <save>\n"
                 "  dl2sim prepare-archive <HDX/HDD-base> <entry>\n"
                 "  dl2sim roundtrip <save> <new-copy>\n"
                 "  dl2sim taxes <save>\n"
                 "  dl2sim taxes-archive <HDX/HDD-base> <entry>\n"
                 "  dl2sim economy <save>  (read-only building outputs and current needs)\n"
                 "  dl2sim economy-archive <HDX/HDD-base> <entry>\n"
                 "  dl2sim energy <save>  (isolated consumption, without production/imports)\n"
                 "  dl2sim energy-archive <HDX/HDD-base> <entry>\n"
                 "  dl2sim labor <save>  (isolated task/labor normalization and stock caps)\n"
                 "  dl2sim labor-archive <HDX/HDD-base> <entry>\n"
                 "  dl2sim normalize-load <save>  (partial offline load; NOT playable)\n"
                 "  dl2sim normalize-load-archive <HDX/HDD-base> <entry>\n"
                 "  dl2sim normalize-load-seeded <save> <seed-int32>\n"
                 "    Explicit pre-event RNG seed, zero prior city counts; NOT replay of an unknown previous session.\n"
                 "  dl2sim normalize-session <save> <seed-int32>\n"
                 "    Explicit cold context: pre-reset seed, zero prior world/cities/shading, clock0. Still not playable.\n"
                 "  dl2sim create-building <save> <territory> <building-type> <site>\n"
                 "  dl2sim create-building-archive <HDX/HDD-base> <entry> <territory> <building-type> <site>\n"
                 "    Finished-building initializer with local effects; NOT paid construction or SAV export.\n"
                 "  dl2sim create-unit <save> <territory> <owner> <unit-type>\n"
                 "  dl2sim delete-building <save> <building-id>\n"
                 "  dl2sim demolish-building <save> <building-id> <refund-player>\n"
                 "  dl2sim start-building <save> <territory> <building-type> <site> <seed-int32>\n"
                 "  dl2sim find-site <save> <territory> <building-type> <seed-int32>\n"
                 "  dl2sim progress-buildings <save> <territory> <seed-int32>\n"
                 "    Construction/upgrade work from assigned labor; NOT the whole production pass.\n"
                 "  dl2sim queue-unit <save> <territory> <unit-type> <seed-int32>\n"
                 "  dl2sim dequeue-unit <save> <territory> <queue1..5> <index0-based>\n"
                 "  dl2sim produce-units <save> <territory> <queue1..5> <work-int32> <seed-int32>\n"
                 "  dl2sim production-prefix <save> <seed-int32>\n"
                 "    Original economic order from resets through building costs; stops BEFORE growth/morale/research/riots.\n"
                 "    Work is an explicit laboratory input, not an executed economic turn.\n"
                 "  dl2sim delete-unit <save> <unit-id>\n"
                 "  dl2sim disband-unit <save> <unit-id>\n"
                 "    Lifecycle with task-force detachment/cascades; NOT manufacturing, combat or SAV export.\n"
                 "  dl2sim activate <save>  (complete load explicitly unavailable)\n"
                 "  dl2sim placement <save> <territory> <building-type> <site>\n"
                 "  dl2sim placement-archive <HDX/HDD-base> <entry> <territory> <building-type> <site>\n"
                 "    Read-only placement/footprint, NOT ownership/technology/affordability permission.\n"
                 "  dl2sim turn <save>  (explicitly unavailable)\n"
                 "Experiments print JSON. No partial SAV is written.\n";
    return 2;
}
}
int main(int argc, char** argv) {
    try {
        if (argc == 2 && std::string(argv[1]) == "--help") { usage(); return 0; }
        if (argc < 3) return usage();
        const std::string command = argv[1];
        const bool isPlacement = command == "placement" || command == "placement-archive";
        const bool isCreation = command == "create-building" || command == "create-building-archive";
        const bool archive = command == "prepare-archive" || command == "taxes-archive" ||
                             command == "economy-archive" || command == "energy-archive" || command == "labor-archive" ||
                             command == "placement-archive" || command == "normalize-load-archive" || command == "create-building-archive";
        if (!((argc == 3 && (command == "prepare" || command == "taxes" || command == "turn" ||
                            command == "economy" || command == "energy" || command == "labor" ||
                            command == "normalize-load" || command == "activate")) ||
              (argc == 4 && ((!isPlacement && !isCreation && archive) || command == "roundtrip" || command == "normalize-load-seeded" ||
                             command == "normalize-session" || command == "production-prefix" || command == "delete-unit" || command == "disband-unit" || command == "delete-building")) ||
              (argc == 5 && (command == "demolish-building" || command == "progress-buildings")) ||
              (argc == 7 && (command == "start-building" || command == "produce-units")) ||
              (argc == 6 && (command == "create-unit" || command == "find-site" || command == "queue-unit" || command == "dequeue-unit")) ||
              ((isPlacement || isCreation) && argc == (archive ? 7 : 6)))) return usage();
        auto document = std::make_unique<save::Document>();
        save::Error error;
        require(archive ? save::readScenario(argv[2], argv[3], *document, error)
                        : save::readDocument(argv[2], *document, error), error);
        runtime::State state;
        require(state.prepare(*document, error), error);
        if (command == "turn") { require(state.advanceTurn(error), error); return 1; }
        if (command == "normalize-load" || command == "normalize-load-archive" || command == "normalize-load-seeded" ||
            command == "normalize-session" || command == "activate") {
            runtime::LoadReport report;
            runtime::LoadContext context;
            if (command == "normalize-load-seeded" || command == "normalize-session") {
                simulation::SessionRng rng;
                require(rng.initialize(uint32_t(integer(argv[3])), error), error);
                if (command == "normalize-session") {
                    context.startup = simulation::LoadStartupContext{rng.snapshot()};
                    context.previousWorld = WorldParams{}; context.clockMs = 0;
                    context.previousAi.emplace(); // Explicit cold laboratory context, not historical recovery.
                } else { context.events.emplace(); context.events->rngBeforeEvents = rng.snapshot(); }
            }
            require(state.normalizeLoad({}, report, error,
                command == "activate" ? runtime::LoadScope::Complete : runtime::LoadScope::Partial, context), error);
            load(state, report, document->options.turn);
        } else if (command == "find-site") {
            const int territory = integer(argv[3]);
            if (territory <= 0) throw std::runtime_error("Territory index must be positive");
            simulation::SessionRng rng; simulation::ConstructionSiteReport report;
            require(rng.initialize(uint32_t(integer(argv[5])), error), error);
            require(simulation::findConstructionSite(*document,uint32_t(territory),integer(argv[4]),rng.snapshot(),report,error),error);
            std::cout << std::boolalpha << "{\"read_only\":true,\"applies_construction\":false,\"complete_turn\":false,\"found\":"
                      << report.found << ",\"site\":" << report.site << ",\"rng_operations\":" << report.rngAfter.counters.operations << "}\n";
        } else if (command == "production-prefix") {
            simulation::EconomicPrefixContext context;
            context.effects = coldOrderContext(*document, 0, integer(argv[3]), error);
            auto report = std::make_unique<simulation::EconomicPrefixReport>();
            require(state.runEconomicProductionPrefix(context, *report, error), error);
            economicPrefix(state, *report);
        } else if (command == "progress-buildings") {
            const int territory = integer(argv[3]);
            if (territory <= 0) throw std::runtime_error("Territory index must be positive");
            const auto shared = coldOrderContext(*document, uint32_t(territory), integer(argv[4]), error);
            simulation::BuildingProgressContext context{shared.log, shared.events, shared.ai};
            simulation::BuildingProgressReport report;
            require(state.progressBuildingWork(uint32_t(territory), context, report, error), error);
            buildingProgress(state, report);
        } else if (command == "queue-unit" || command == "produce-units") {
            const int territory = integer(argv[3]);
            if (territory <= 0) throw std::runtime_error("Territory index must be positive");
            simulation::UnitManufacturingContext context;
            context.effects = coldOrderContext(*document, uint32_t(territory), integer(argv[argc - 1]), error);
            simulation::UnitManufacturingReport report;
            if (command == "queue-unit")
                require(state.queueUnit({uint32_t(territory), integer(argv[4])}, context, report, error), error);
            else require(state.produceUnits({uint32_t(territory), integer(argv[4]), integer(argv[5])}, context, report, error), error);
            manufacturing(state, report);
        } else if (command == "dequeue-unit") {
            const int territory = integer(argv[3]), index = integer(argv[5]);
            if (territory <= 0 || index < 0) throw std::runtime_error("Territory must be positive and queue index nonnegative");
            simulation::UnitDequeueReport report;
            require(state.dequeueUnit({uint32_t(territory), integer(argv[4]), uint32_t(index)}, report, error), error);
            std::cout << std::boolalpha << "{\"stage\":\"entities_edited_in_memory\",\"complete_turn\":false,\"can_save\":false,"
                         "\"removed\":" << report.removed << ",\"territory\":" << report.territory << ",\"queue\":" << report.queue
                      << ",\"unit_type\":" << report.unitType << ",\"refund_credits\":" << report.creditsRefunded
                      << ",\"refund_materials\":";
            numbers(report.materialsRefunded);
            std::cout << ",\"population_before\":" << report.populationBefore << ",\"population_after\":" << report.populationAfter
                      << ",\"turn\":" << state.document()->options.turn;
            queueContents(state, report.territory, report.queue); std::cout << "}\n";
        } else if (command == "start-building") {
            const int territory = integer(argv[3]);
            if (territory <= 0) throw std::runtime_error("Territory index must be positive");
            const auto context = coldOrderContext(*document, uint32_t(territory), integer(argv[6]), error);
            simulation::ConstructionOrderReport report; runtime::BuildingHandle handle;
            require(state.startConstruction({uint32_t(territory),integer(argv[4]),integer(argv[5])}, context, handle, report, error), error);
            constructionOrder(state, report);
        } else if (command == "create-unit") {
            const int territory = integer(argv[3]);
            if (territory <= 0) throw std::runtime_error("Territory index must be positive");
            simulation::ArmyLifecycleReport report; runtime::ArmyHandle handle;
            require(state.createArmy({uint32_t(territory), integer(argv[4]), integer(argv[5])}, {}, handle, report, error), error);
            armyLifecycle(state, report);
        } else if (command == "delete-unit" || command == "disband-unit") {
            const int id = integer(argv[3]);
            if (id <= 0) throw std::runtime_error("Unit ID must be positive");
            simulation::ArmyLifecycleReport report;
            require(state.removeArmy(state.armyById(uint32_t(id)), command == "delete-unit" ? simulation::ArmyRemovalKind::DeleteUnit :
                simulation::ArmyRemovalKind::DisbandUnit, true, report, error), error);
            armyLifecycle(state, report);
        } else if (command == "delete-building" || command == "demolish-building") {
            const int id = integer(argv[3]);
            if (id <= 0) throw std::runtime_error("Building ID must be positive");
            simulation::BuildingLifecycleReport report;
            const bool demolition = command == "demolish-building";
            require(state.removeBuilding(state.buildingById(uint32_t(id)), demolition ? simulation::BuildingRemovalKind::DemolishBuilding :
                simulation::BuildingRemovalKind::DeleteBuilding, demolition ? integer(argv[4]) : -1, report, error), error);
            buildingLifecycle(state, report);
        } else if (isCreation) {
            const int offset = archive ? 4 : 3;
            const int territory = integer(argv[offset]);
            if (territory <= 0) throw std::runtime_error("Territory index must be positive");
            simulation::BuildingCreationReport report; runtime::BuildingHandle handle;
            require(state.createCompletedBuilding({uint32_t(territory), integer(argv[offset + 1]), integer(argv[offset + 2])},
                handle, report, error), error);
            createdBuilding(state, report);
        } else if (isPlacement) {
            const int offset = archive ? 4 : 3;
            const int territory = integer(argv[offset]);
            if (territory <= 0) throw std::runtime_error("Territory index must be positive");
            simulation::BuildingPlacement result;
            require(simulation::checkBuildingPlacement(*state.document(), uint32_t(territory),
                integer(argv[offset + 1]), integer(argv[offset + 2]), result, error), error);
            placement(state, result);
        } else if (command == "taxes" || command == "taxes-archive") {
            simulation::TaxPlan plan;
            const int before = document->options.turn;
            require(state.collectTaxes(plan, error), error);
            taxes(state, plan, before);
        } else if (command == "energy" || command == "energy-archive") {
            simulation::EnergyPlan plan;
            const int before = document->options.turn;
            require(state.consumeEnergy(plan, error), error);
            energy(state, plan, before);
        } else if (command == "labor" || command == "labor-archive") {
            simulation::LaborBalancePlan plan;
            const int before = document->options.turn;
            require(state.normalizeLabor(plan, error), error);
            labor(state, plan, before);
        } else if (command == "economy" || command == "economy-archive") {
            simulation::ProductionPlan production;
            simulation::NeedsPlan needs;
            require(simulation::planProduction(*state.document(), production, error), error);
            require(simulation::planNeeds(*state.document(), needs, error), error);
            economy(state, production, needs);
        } else {
            if (command == "roundtrip") {
                require(state.capture(*document, error), error);
                require(save::writeDocumentCopy(argv[3], *document, error), error);
            }
            summary(state);
        }
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "dl2sim: " << e.what() << '\n'; return 1;
    }
}
