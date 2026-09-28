// Execution-state laboratory. Isolated experiments are not completed game turns.
#include "game/runtime_state.h"
#include "game/production_plan.h"
#include "game/entity_rules.h"
#include "game/save_files.h"
#include <charconv>
#include <iostream>
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
        throw std::runtime_error("Placement arguments must be decimal integers in int32 range");
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
template<class T, size_t N> void numbers(const std::array<T, N>& values) {
    std::cout << "[";
    for (size_t i = 0; i < N; ++i) std::cout << (i ? "," : "") << int64_t(values[i]);
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
        const bool archive = command == "prepare-archive" || command == "taxes-archive" ||
                             command == "economy-archive" || command == "energy-archive" || command == "labor-archive" ||
                             command == "placement-archive";
        if (!((argc == 3 && (command == "prepare" || command == "taxes" || command == "turn" ||
                            command == "economy" || command == "energy" || command == "labor")) ||
              (argc == 4 && ((!isPlacement && archive) || command == "roundtrip")) ||
              (isPlacement && argc == (archive ? 7 : 6)))) return usage();
        auto document = std::make_unique<save::Document>();
        save::Error error;
        require(archive ? save::readScenario(argv[2], argv[3], *document, error)
                        : save::readDocument(argv[2], *document, error), error);
        runtime::State state;
        require(state.prepare(*document, error), error);
        if (command == "turn") { require(state.advanceTurn(error), error); return 1; }
        if (isPlacement) {
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
