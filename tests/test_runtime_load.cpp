// Integration/transaction tests; not observations of an executing original.
#include "game/runtime_state.h"
#include "game/save_files.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include "formats/hdx_archive.h"
#include <cstring>
#include <filesystem>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
using namespace dl2;
namespace rt = runtime;
void require(bool condition, const char* message) {
    if (!condition) throw std::runtime_error(message);
}
void ok(bool condition, const save::Error& error) {
    if (!condition) throw std::runtime_error(error.message);
}
std::vector<uint8_t> bytes(const save::Document& d) {
    std::vector<uint8_t> out; save::Error e; ok(save::encode(d, out, e), e); return out;
}
std::unique_ptr<save::Document> fixture() {
    auto d = std::make_unique<save::Document>();
    std::memcpy(d->header.text, save::kHeaderText, sizeof(save::kHeaderText));
    d->header.version = kSaveVersion;
    d->options.numPlayers = 2; d->options.turn = 1; d->options.gameId = -123;
    d->options.gameSeed = 456; d->options.campaign = 6;
    d->world.width = 2; d->world.height = 1; d->world.numTerritories = 2;
    d->world.rngSeed = 789;
    d->territories.resize(2); d->tiles.resize(2);
    for (int p = 0; p < kMaxPlayers; ++p) {
        auto& player = d->players[size_t(p)];
        player.index = uint8_t(p); player.race = int8_t(p);
        player.currentResearch = 47;
        d->ministerJobs[size_t(p)].resize(1);
        for (auto& row : d->raceStats.v) row[p] = 100;
    }
    d->players[0].type = 1; d->players[1].type = 2;
    d->techs[47].availableMask = 0x7f;
    for (int i = 0; i < 2; ++i) {
        auto& t = d->territories[size_t(i)].data;
        t.index = uint16_t(i + 1); t.owner = int8_t(i); t.terrain = 1;
        t.numTiles = 1; t.tiles[0].raw = uint32_t(i); t.centerTile = 0;
        t.population = 400; t.morale = 80; t.knowledge = 100;
        t.materials[1] = 12345;
        d->tiles[size_t(i)].x = uint8_t(i); d->tiles[size_t(i)].territory = int16_t(i + 1);
    }
    d->armies.resize(1);
    auto& a = d->armies[0];
    a.id = 60000; a.type = 1; a.owner = 0; a.health = 100;
    a.territory.raw = a.dest.raw = a.origin.raw = 1;
    d->territories[0].data.armies.raw = a.id;
    d->jobs[0][4].armyIds[0] = a.id;
    return d;
}

void transactionalIntegration() {
    auto source = fixture();
    const auto original = bytes(*source);
    std::vector<uint8_t> gsBefore(sizeof(gs)), ggBefore(sizeof(gg));
    std::memcpy(gsBefore.data(), &gs, sizeof(gs)); std::memcpy(ggBefore.data(), &gg, sizeof(gg));
    const auto low = rtl::seed(), high = rtl::seedHi();
    rt::State state; save::Error e; rt::LoadReport report;
    report.core.localPlayer = 5; const auto sentinel = report;
    require(!state.normalizeLoad({}, report, e) && report == sentinel, "empty normalization must reject");
    ok(state.prepare(*source, e), e);
    auto army = state.armyById(60000); auto territory = state.territoryByIndex(1);
    const auto* oldDocument = state.document();
    require(!state.sessionRng().initialized, "archival prepare must not silently initialize RNG");
    require(!state.normalizeLoad({}, report, e, rt::LoadScope::Complete) && report == sentinel &&
        state.document() == oldDocument && bytes(*state.document()) == original, "complete activation cannot lie or mutate");
    simulation::LoadProfile profile; profile.localPlayerName = "Owned session";
    ok(state.normalizeLoad(profile, report, e), e);
    require(e.code == save::ErrorCode::None && state.stage() == rt::Stage::LoadNormalized && !report.complete,
        "partial load has a distinct, successful but nonplayable stage");
    require(report.missing.size() == 7 && report.derived.continentsRebuilt && report.derived.roadsRebuilt &&
        report.derived.shrineCountsRebuilt && !report.derived.visibilityRebuilt && !report.derived.contactsRebuilt,
        "implemented and missing capabilities are explicit");
    require(state.armyById(60000) == army && state.territoryByIndex(1) == territory && state.army(army)->job == 5,
        "load rebuild preserves handle identity and binds jobs");
    require(state.graph().jobs[0][4].armies[0] == army, "typed graph rebuilt alongside normalized document");
    require(report.core.forbiddenResearchPlayers == 3 && state.document()->players[0].currentResearch == 0 &&
        state.document()->players[1].currentResearch == 0 && state.document()->techs[47].availableMask == 0x7c,
        "campaign6 forbids47 for races0..6 and clears fixed tech47 mask");
    require(state.document()->territories[0].data.materials[1] == 10000 &&
        report.labor.territories[0].materialsBefore[1] == 12345, "load executes labor stock caps");
    require(report.rng == state.sessionRng() && report.rng.initialized && report.rng.rtlLow == uint32_t(-123) &&
        report.rng.secondary == uint32_t(-123) && report.rng.rtlHigh == 0 && !report.rng.counters.operations,
        "final offline load seeds both owned streams from gameId, not world/gameSeed");
    const auto normalized = bytes(*state.document()); const auto prior = report;
    auto destination = fixture(); const auto oldDestination = bytes(*destination);
    require(!state.capture(*destination, e) && bytes(*destination) == oldDestination,
        "normalized partial state cannot be exported as resumable");
    require(!state.normalizeLoad(profile, report, e) && report == prior, "normalization is once per preparation");
    simulation::TaxPlan tax; simulation::EnergyPlan energy; simulation::LaborBalancePlan labor;
    require(!state.collectTaxes(tax, e) && !state.consumeEnergy(energy, e) && !state.normalizeLabor(labor, e) &&
        !state.advanceTurn(e), "no partial phase may chain into a purported turn");
    rt::EntityEditReport edit; require(!state.retireArmy(army, edit, e), "no structural edits after partial load");
    require(bytes(*state.document()) == normalized && state.sessionRng() == prior.rng,
        "all rejected operations retain loaded document and RNG");
    rt::State moved = std::move(state);
    require(!state.document() && !state.sessionRng().initialized && moved.army(army) && moved.sessionRng() == prior.rng,
        "owned RNG moves with graph and invalidates moved-from state");
    source->header.version = 0;
    require(!moved.prepare(*source, e) && bytes(*moved.document()) == normalized && moved.sessionRng() == prior.rng,
        "failed replacement preserves previous normalized session");
    source->header.version = kSaveVersion;
    ok(moved.prepare(*source, e), e);
    require(!moved.sessionRng().initialized && !moved.army(army), "fresh preparation resets RNG and old identities");
    require(bytes(*source) == original && !std::memcmp(gsBefore.data(), &gs, sizeof(gs)) &&
        !std::memcmp(ggBefore.data(), &gg, sizeof(gg)) && rtl::seed() == low && rtl::seedHi() == high,
        "load source and global state/RNG are untouched");
}

void rollbackLateFailure() {
    auto d = fixture();
    // Structurally valid unowned housing with no task: original labor would
    // write slot -1; our planner must reject AFTER the earlier load stages.
    d->buildings.resize(1); auto& b = d->buildings[0];
    b.id = 77; b.type = 1; b.category = 17; b.territory = 2; b.site = 0;
    d->territories[1].data.owner = -1;
    d->territories[1].data.sites[0].building.raw = 77;
    rt::State state; save::Error e; ok(state.prepare(*d, e), e);
    const auto before = bytes(*state.document()); const auto* pointer = state.document();
    const auto handle = state.buildingById(77); const auto rng = state.sessionRng();
    rt::LoadReport report; report.core.localPlayer = 6; const auto old = report;
    require(!state.normalizeLoad({}, report, e) && !e.message.empty(), "late labor validation fails");
    require(report == old && state.document() == pointer && bytes(*state.document()) == before &&
        state.buildingById(77) == handle && state.sessionRng() == rng && state.stage() == rt::Stage::Prepared,
        "rollback covers core/derived writes before labor failure, graph, identities, RNG, report");
}

void corpus(const std::filesystem::path& directory) {
    namespace fs = std::filesystem;
    if (directory.empty()) return;
    size_t documents = 0, archivalOnly = 0;
    const auto inspect = [&](const save::Document& d, const std::string& label) {
        try {
            const auto original = bytes(d);
            rt::State first, second; save::Error e; rt::LoadReport a, b;
            ok(first.prepare(d, e), e); ok(second.prepare(d, e), e);
            const auto oldTerritory = first.territoryByIndex(1);
            if (d.header.version < 0x26) {
                a.core.localPlayer = 6; const auto previous = a;
                const auto* document = first.document();
                require(!first.normalizeLoad({}, a, e) && e.code == save::ErrorCode::UnsupportedVersion &&
                    a == previous && first.document() == document && bytes(*first.document()) == original &&
                    first.territory(oldTerritory) && !first.sessionRng().initialized &&
                    first.stage() == rt::Stage::Prepared, "older corpus version remains archival without partial mutation");
                std::cout << "archival-only corpus: " << label << " version " << d.header.version << '\n';
                ++archivalOnly; return;
            }
            ok(first.normalizeLoad({}, a, e), e); ok(second.normalizeLoad({}, b, e), e);
            require(a == b && bytes(*first.document()) == bytes(*second.document()), "deterministic load pipeline");
            require(bytes(d) == original && first.territory(oldTerritory) &&
                d.options.turn == first.document()->options.turn, "source/turn preserved and static handles stable");
            ++documents;
        } catch (const std::exception& e) { throw std::runtime_error(label + ": " + e.what()); }
    };
    for (const char* relative : {"TUTORIAL.SAV", "Saves/AUTOSAVE.SAV", "Campaign/AUTOSAVE.CPN", "Campaign/ChCht001.CPN"}) {
        if (!fs::is_regular_file(directory / relative)) continue;
        auto d = std::make_unique<save::Document>(); save::Error e;
        ok(save::readDocument(directory / relative, *d, e), e); inspect(*d, relative);
    }
    if (fs::is_regular_file(directory / "LEVELS.HDX") && fs::is_regular_file(directory / "LEVELS.HDD")) {
        HdxArchive archive; std::string why;
        require(archive.open((directory / "LEVELS").string(), &why), "open corpus archive");
        for (const auto& entry : archive.entries()) {
            auto d = std::make_unique<save::Document>(); save::Error e;
            ok(save::readScenario(directory / "LEVELS", entry.name, *d, e), e); inspect(*d, entry.name);
        }
    }
    std::cout << "runtime_load corpus: " << documents << " normalized, " << archivalOnly
              << " explicitly archival-only\n";
}
}
int main(int argc, char** argv) {
    try {
        transactionalIntegration(); rollbackLateFailure();
        corpus(argc > 1 ? std::filesystem::path(argv[1]) : std::filesystem::path{});
        std::cout << "runtime_load: explicit partial pipeline, capability gates, identity/RNG ownership and rollback passed\n";
        return 0;
    } catch (const std::exception& e) { std::cerr << "runtime_load: " << e.what() << '\n'; return 1; }
}
