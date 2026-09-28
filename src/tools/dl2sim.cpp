// Execution-state laboratory. A fiscal phase is not a completed game turn.
#include "game/runtime_state.h"
#include "game/save_files.h"
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

namespace {
using namespace dl2;
void require(bool success, const save::Error& error) {
    if (!success) throw std::runtime_error(error.message);
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
int usage() {
    std::cout << "Execution preparation / isolated fiscal phase. NOT a complete turn.\n"
                 "  dl2sim prepare <save>\n"
                 "  dl2sim prepare-archive <HDX/HDD-base> <entry>\n"
                 "  dl2sim roundtrip <save> <new-copy>\n"
                 "  dl2sim taxes <save>\n"
                 "  dl2sim taxes-archive <HDX/HDD-base> <entry>\n"
                 "  dl2sim turn <save>  (explicitly unavailable)\n"
                 "Taxes run once in memory and print JSON. No partial SAV is written.\n";
    return 2;
}
}
int main(int argc, char** argv) {
    try {
        if (argc == 2 && std::string(argv[1]) == "--help") { usage(); return 0; }
        if (argc < 3) return usage();
        const std::string command = argv[1];
        const bool archive = command == "prepare-archive" || command == "taxes-archive";
        if (!((argc == 3 && (command == "prepare" || command == "taxes" || command == "turn")) ||
              (argc == 4 && (archive || command == "roundtrip")))) return usage();
        auto document = std::make_unique<save::Document>();
        save::Error error;
        require(archive ? save::readScenario(argv[2], argv[3], *document, error)
                        : save::readDocument(argv[2], *document, error), error);
        runtime::State state;
        require(state.prepare(*document, error), error);
        if (command == "turn") { require(state.advanceTurn(error), error); return 1; }
        if (command == "taxes" || command == "taxes-archive") {
            simulation::TaxPlan plan;
            const int before = document->options.turn;
            require(state.collectTaxes(plan, error), error);
            taxes(state, plan, before);
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
