// Independent small-map mathematical oracles; not original-game execution.
#include "game/load_world_presentation.h"
#include "game/save_files.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include "formats/hdx_archive.h"
#include <algorithm>
#include <array>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
using namespace dl2;
using namespace dl2::simulation;
void require(bool condition, const char* message) { if (!condition) throw std::runtime_error(message); }
std::unique_ptr<save::Document> fixture(int count = 1) {
    auto d = std::make_unique<save::Document>();
    std::memcpy(d->header.text, save::kHeaderText, sizeof(save::kHeaderText));
    d->header.version = kSaveVersion; d->options.numPlayers = 7; d->options.localPlayer = 0;
    d->options.turn = 31; d->options.gameId = 73; d->options.nextGlobalId = 501;
    d->world.width = uint8_t(count); d->world.height = 1;
    d->world.numTerritories = uint16_t(count); d->world.rngSeed = 123;
    d->tiles.resize(size_t(count)); d->territories.resize(size_t(count));
    for (size_t p = 0; p < 7; ++p) {
        d->ministerJobs[p].resize(1); d->players[p].index = uint8_t(p); d->players[p].race = int8_t(p);
    }
    for (int i = 0; i < count; ++i) {
        auto& tile = d->tiles[size_t(i)]; tile.x = uint8_t(i); tile.territory = int16_t(i + 1);
        auto& t = d->territories[size_t(i)].data;
        t.index = uint16_t(i + 1); t.numTiles = 1; t.centerTile = -1; t.tiles[0].raw = uint32_t(i);
        t.owner = -1; t.flags = 0xa5a5ffff; t.production[4] = -89;
    }
    d->localList = {7,0,9}; d->options.eventCount = 1;
    save::Event e; e.text = {0x61,0,0xff,0x62}; e.record.textLen = uint16_t(e.text.size()); d->events.push_back(e);
    return d;
}
std::vector<uint8_t> snapshot(const save::Document& d) {
    save::Error error; std::vector<uint8_t> result;
    if (!save::encode(d, result, error)) throw std::runtime_error("fixture snapshot: " + error.message);
    for (const auto& record : d.territories) {
        const auto* bytes = reinterpret_cast<const uint8_t*>(&record.data);
        result.insert(result.end(), bytes + kTerritorySavedBytes, bytes + sizeof(Territory));
    }
    return result;
}
LoadWorldPresentationContext context(const save::Document& d, bool changed = true) {
    LoadWorldPresentationContext result; result.previousWorld = d.world;
    if (changed) result.previousWorld.seed1 ^= 1;
    SessionRng rng; save::Error error; require(rng.initialize(0xabcde, error), "initialize explicit RNG");
    RngEvent event; require(rng.apply({RngOperation::Secondary15}, event, error), "prime separate secondary sequence");
    require(rng.apply({RngOperation::Long31}, event, error), "prime RTL high state");
    result.rng = rng.snapshot(); result.shadingSlope = 999;
    return result;
}
std::unique_ptr<save::Document> rebuild(const save::Document& source, const LoadWorldPresentationContext& ctx,
                                      LoadWorldPresentationReport& report) {
    const auto before = snapshot(source); auto out = fixture(); save::Error error{save::ErrorCode::Io,23,"old"};
    if (!rebuildLoadWorldPresentation(source, ctx, *out, report, error)) throw std::runtime_error(error.message);
    require(error.code == save::ErrorCode::None && error.offset == 0 && error.message.empty(), "success clears error");
    require(snapshot(source) == before, "source remains byte-exact including unsaved tail");
    require(report.rngAfter.secondary == ctx.rng.secondary, "world reconstruction never consumes/reseeds secondary RNG");
    return out;
}

// Independent expression of004ae5d8, deliberately no SessionRng call.
struct OracleRng {
    uint64_t value; uint64_t draws = 0;
    uint32_t draw() { value = value * 0x15a00004e35ull + 1; ++draws; return uint32_t(value >> 32) & 0x7fffffff; }
};
struct SeaOracle {
    std::vector<uint8_t> color;
    uint64_t draws = 0, colorDraws = 0, state = 0;
};
SeaOracle seaOracle(uint32_t seed) {
    //00469744 table0:40 negative cones; all1024 heights stay strictly negative.
    // Evaluate pixels against a list of cones, unlike production's in-place
    // feature rasterization. No copied production helper/table is used.
    struct Cone { int x, y, magnitude, slope; };
    std::array<Cone,40> cones{}; OracleRng rng{seed};
    for (auto& cone : cones) {
        cone.x = int(rng.draw() % 31); cone.y = int(rng.draw() % 31);
        const int sample = int(rng.draw() % 64);
        cone.magnitude = sample < 32 ? 1 : sample < 48 ? 2 : sample < 60 ? 3 : sample < 62 ? 4 : sample == 62 ? 5 : 6;
        cone.slope = rng.draw() % 16 == 0 ? 3 : 4;
    }
    std::array<int,1024> heights{};
    for (int y = 0; y < 32; ++y) for (int x = 0; x < 32; ++x) {
        int altitude = -5;
        for (const auto& cone : cones) {
            const int radius = 16 * cone.magnitude / cone.slope;
            if (x < cone.x - radius || x >= cone.x + radius || y < cone.y - radius || y >= cone.y + radius) continue;
            const int dx = std::abs(x - cone.x), dy = std::abs(y - cone.y);
            const int distance = (2 * std::max(dx,dy) + std::min(dx,dy)) * cone.slope / 4;
            if (distance < cone.magnitude * 8) altitude -= cone.magnitude * 8 - std::max(1,distance);
        }
        heights[size_t(y) * 32 + x] = altitude;
    }
    require(rng.draws == 160, "oracle forty features each consume four long31 draws");
    //All5 color slots have count/diameter/density0, but coin flips can promote
    //count to1. Position draws then still occur even though no pixel is visited.
    const uint64_t beforeColors = rng.draws;
    for (int layer = 0; layer < 5; ++layer) {
        const uint32_t firstCoin = rng.draw() % 2;
        if (firstCoin == 0) { rng.draw(); rng.draw(); rng.draw(); }
    }
    SeaOracle result; result.colorDraws = rng.draws - beforeColors; result.color.resize(1024);
    for (int y = 0; y < 32; ++y) for (int x = 31; x >= 0; --x) {
        const int h = heights[size_t(y) * 32 + x];
        //floor(h/4), not C++ truncation of negative values.
        const int quarter = -((-h + 3) / 4);
        const int shade = std::clamp(quarter + 7, 0, 5) + int(rng.draw() % 2);
        result.color[size_t(y) * 32 + x] = uint8_t(0x40 | shade);
    }
    result.draws = rng.draws; result.state = rng.value; return result;
}

void exactSeaOracle() {
    for (const uint32_t seed : {0u,1u,123u,0xffffffffu}) {
        auto d = fixture(); d->world.rngSeed = seed;
        auto ctx = context(*d); LoadWorldPresentationReport report;
        const auto expected = seaOracle(seed); auto out = rebuild(*d, ctx, report);
        require(report.changedWorld && report.mapRebuilt && report.selectionReset && report.width == 32 && report.height == 32,
                "changed-world semantic reconstruction reports actual32x32 output");
        require(report.heightMap == std::vector<uint8_t>(1024,0) && report.colorMap == expected.color,
                "entire1024-pixel sea height/color equals independent integer/cone oracle");
        require(report.long31ByPhase == std::array<uint64_t,6>{0,160,expected.colorDraws,1024,0,0},
                "sea draws exactly match phase oracle including zero-count color slots");
        require(report.rngAfter.rtlLow == uint32_t(expected.state) && report.rngAfter.rtlHigh == uint32_t(expected.state >> 32) &&
                report.rngAfter.counters.long31 == ctx.rng.counters.long31 + expected.draws &&
                report.rngAfter.counters.seedRtl == ctx.rng.counters.seedRtl + 1 &&
                report.rngAfter.counters.operations == ctx.rng.counters.operations + expected.draws + 1 &&
                report.rngAfter.counters.rand15 == ctx.rng.counters.rand15,
                "world seed resets RTLlow/high; exactLong31sequence and noRand15consumption");
        require(report.shadingSlopeAfter == 999, "water-only shading preserves previous slope scratch");
        require(out->territories[0].data.flags == 0xfff0 && report.selectedTerritory == 1 && !report.cameraTargetValid,
                "literal flagsANDfff0 and ownerless first-nonempty fallback without camera jump");
        require(report.windowRecreationRequested && report.paletteApplicationRequested && report.palettePatches.size() == 3,
                "native windows/palette application are requests, not claimed execution");
    }
}

void terrainSelectionAndPalettes() {
    // Table-driven terrain rewrites before centers; all original graphic types
    // exercised. Explicit gaps/default territory terrain retain old graphic.
    auto d = fixture(7);
    for (size_t i = 0; i < 7; ++i) { d->territories[i].data.terrain = uint8_t(i); d->tiles[i].terrain = 1; }
    d->tiles[6].terrain = 6; d->territories[4].data.owner = 0;
    auto ctx = context(*d); LoadWorldPresentationReport report; auto out = rebuild(*d,ctx,report);
    OracleRng rng{d->world.rngSeed}; const auto plains = rng.draw() % 16 ? 3 : 4; const auto forest = rng.draw() % 8 ? 2 : 4;
    const std::array<int,7> expected{0,int(plains),int(forest),1,5,6,6};
    for (size_t i = 0; i < 7; ++i) require(out->tiles[i].terrain == expected[i], "territory terrain switch matches original mapping/draw order");
    require(report.long31ByPhase[0] == 2 && report.long31ByPhase[5] == 0, "onlyplains/forestdraw;mountains suppress wasteland normalizationdraw");
    require(report.selectedTerritory == 5 && report.cameraTargetValid && report.cameraTileX == 4 && report.cameraTileY == 0 &&
            out->territories[4].data.flags == 0xfff1 && out->territories[0].data.flags == 0xfff0,
            "first-owned fallback focus replaces provisional first territory and updates flags");

    auto home = fixture(2); home->players[0].homeTerritory = 2; home->territories[1].data.centerTile = 0;
    home->territories[1].data.terrain = 4; home->tiles[1].terrain = 1;
    auto hc = context(*home); auto h = rebuild(*home,hc,report);
    require(report.long31ByPhase[0] == 2 && h->tiles[1].terrain == 3 && h->tiles[0].terrain == 0,
            "center consumes every inboundsneighbor draw including water then forces terrain3");
    require(report.selectedTerritory == 2 && report.cameraTileX == 1 && h->territories[1].data.flags == 0xfff3,
            "explicit home focus receives both selection bits");
    auto waterCenter = fixture(); waterCenter->territories[0].data.terrain = 3; waterCenter->territories[0].data.centerTile = 0;
    auto wc = context(*waterCenter); auto w = rebuild(*waterCenter,wc,report);
    require(w->tiles[0].terrain == 3 && report.long31ByPhase[0] == 1 && report.long31ByPhase[1] == 4,
            "zero graphic tile bypasses switch but nonsea centerstillforces3; flatplainhasoneheightfeature");

    auto waste = fixture(); waste->territories[0].data.terrain = 5; waste->tiles[0].terrain = 1;
    auto wa = context(*waste); auto wd = rebuild(*waste,wa,report);
    require(wd->tiles[0].terrain == 6 && report.long31ByPhase[1] == 320 && report.long31ByPhase[5] == 1 &&
            report.long31ByPhase[4] >= 1024, "wasteland80features, per-pixelrivergate, and one randomized scalingdraw");
    auto palette = fixture(); auto pc = context(*palette);
    for (int theme = 0; theme <= 7; ++theme) {
        palette->world.worldType = uint8_t(theme); auto result = rebuild(*palette,pc,report);
        (void)result;
        require(report.palettePatches.size() == (theme < 7 ? 3u : 2u), "unknownworldType doesnot invent palette theme");
        const auto& prefix = report.palettePatches[theme < 7 ? 1 : 0]; const auto& suffix = report.palettePatches.back();
        require(prefix.offset == 0 && prefix.bytes.size() == 24 && suffix.offset == 0x218 && suffix.bytes.size() == 448,
                "paletteprefix andsuffix leave exact256-bytegap untouched");
        require(prefix.bytes[0] == 0x53 && prefix.bytes[4] == 0xa7 && suffix.bytes[0] == 0xcd && suffix.bytes.back() == 0,
                "verifiedPE palette sentinels");
        if (theme < 7) require(report.palettePatches[0].offset == 0x18 && report.palettePatches[0].bytes.size() == 256,
                               "theme palette patch precisely64four-byteentries");
    }
}

void unchangedAndTransactions() {
    auto d = fixture(); auto ctx = context(*d,false); LoadWorldPresentationReport report;
    auto out = rebuild(*d,ctx,report); const auto raw = snapshot(*d);
    require(snapshot(*out) == raw && !report.changedWorld && !report.mapRebuilt && !report.selectionReset &&
            report.heightMap.empty() && report.colorMap.empty() && report.palettePatches.empty() &&
            report.rngAfter == ctx.rng && report.shadingSlopeAfter == ctx.shadingSlope,
            "identical20-byteWorldParams skips all visualwork and preserves complete archived state");
    ctx.rng = {}; out = rebuild(*d,ctx,report);
    require(report.rngAfter == RngSnapshot{}, "unchangedworld doesnot require randomdraw state");
    //Eachbyteparticipates: layout padding must not accidentally be skipped.
    for (size_t byte = 0; byte < sizeof(WorldParams); ++byte) {
        auto different = context(*d,false);
        reinterpret_cast<uint8_t*>(&different.previousWorld)[byte] ^= 1;
        auto rebuilt = rebuild(*d,different,report); (void)rebuilt;
        require(report.changedWorld, "comparison includes every one of the20archivedworldbytes");
    }
    ctx = context(*d); auto good = rebuild(*d,ctx,report); const auto expected = snapshot(*good); const auto oldReport = report;
    const auto failure = [&](const save::Document& source, const LoadWorldPresentationContext& input) {
        save::Error error;
        require(!rebuildLoadWorldPresentation(source,input,*good,report,error) && error.code != save::ErrorCode::None &&
                !error.message.empty() && snapshot(*good) == expected && report == oldReport,
                "everyfailedstage preserves destination/report transactionally");
    };
    auto bad = context(*d); bad.rng = {}; failure(*d,bad);
    bad = ctx; bad.rng.format = 2; failure(*d,bad);
    bad = ctx; bad.rng.counters = {}; bad.rng.counters.long31 = std::numeric_limits<uint64_t>::max() - 1;
    bad.rng.counters.operations = bad.rng.counters.long31; failure(*d,bad); //seed works,first actualdraw fails.
    auto invalid = std::make_unique<save::Document>(*d);
    invalid->territories[0].data.terrain = 1; invalid->territories[0].data.centerTile = 1; failure(*invalid,ctx);
    invalid = std::make_unique<save::Document>(*d); invalid->world.width = 0; failure(*invalid,ctx);
    invalid = std::make_unique<save::Document>(*d); invalid->territories[0].data.terrain = 6;
    invalid->tiles[0].terrain = 255; failure(*invalid,ctx); //switchdefault leaves invalidgraphictableindex.
    invalid = std::make_unique<save::Document>(*d); invalid->players[0].homeTerritory = 2; failure(*invalid,ctx); //late aftermap/palette.
    invalid->players[0].homeTerritory = -2; failure(*invalid,ctx);
    invalid->players[0].homeTerritory = 1; invalid->territories[0].data.numTiles = 0; failure(*invalid,ctx);
    invalid->players[0].homeTerritory = -1; failure(*invalid,ctx);
    invalid = std::make_unique<save::Document>(*d); invalid->territories[0].data.tiles[0].raw = 99; failure(*invalid,ctx);

    std::vector<uint8_t> gsBefore(sizeof(gs)), ggBefore(sizeof(gg));
    std::memcpy(gsBefore.data(),&gs,sizeof(gs)); std::memcpy(ggBefore.data(),&gg,sizeof(gg));
    const auto low = rtl::seed(), high = rtl::seedHi();
    auto repeat = rebuild(*d,ctx,report); require(report == oldReport && snapshot(*repeat) == expected, "sameinputs deterministic");
    auto alias = std::make_unique<save::Document>(*d); save::Error error;
    require(rebuildLoadWorldPresentation(*alias,ctx,*alias,report,error) && snapshot(*alias) == expected && report == oldReport,
            "source/destinationalias supported with private candidate");
    bad.rng = {}; failure(*d,bad);
    require(std::memcmp(gsBefore.data(),&gs,sizeof(gs)) == 0 && std::memcmp(ggBefore.data(),&gg,sizeof(gg)) == 0 &&
            low == rtl::seed() && high == rtl::seedHi(), "success/failure never modify legacyglobalsorRNG");
    require(snapshot(*d) == raw && good->events[0].text == d->events[0].text && good->localList == d->localList &&
            good->options.turn == 31 && good->options.gameId == 73 && good->options.nextGlobalId == 501 &&
            good->territories[0].data.production[4] == -89, "outsidegraphicterrain/flags allsession/documentdata preserved");
}

uint32_t le32(const std::vector<uint8_t>& bytes, size_t at) {
    if (at > bytes.size() || bytes.size() - at < 4) throw std::runtime_error("PEbounds");
    return uint32_t(bytes[at]) | (uint32_t(bytes[at+1]) << 8) | (uint32_t(bytes[at+2]) << 16) | (uint32_t(bytes[at+3]) << 24);
}
std::vector<uint8_t> peBytes(const std::vector<uint8_t>& image, uint32_t va, size_t length) {
    const size_t pe = le32(image,0x3c), optional = pe + 24;
    const uint32_t rva = va - le32(image,optional + 28);
    const uint16_t sections = uint16_t(image.at(pe+6) | (uint16_t(image.at(pe+7)) << 8));
    const size_t sectionTable = optional + size_t(image.at(pe+20) | (uint16_t(image.at(pe+21)) << 8));
    for (size_t i = 0; i < sections; ++i) {
        const size_t sh = sectionTable + i * 40;
        const uint32_t base = le32(image,sh+12), size = le32(image,sh+16);
        if (rva < base || uint64_t(rva-base) + length > size) continue;
        const size_t start = le32(image,sh+20) + (rva-base);
        if (start > image.size() || length > image.size() - start) throw std::runtime_error("PErawbounds");
        return {image.begin()+start,image.begin()+start+length};
    }
    throw std::runtime_error("PEnotmapped");
}
void corpus(const std::filesystem::path& directory) {
    namespace fs = std::filesystem;
    if (directory.empty()) { std::cout << "world presentation optionalcorpus: nodirectory\n"; return; }
    size_t count = 0;
    const auto unchanged = [&](const save::Document& d) {
        LoadWorldPresentationReport report; const auto ctx = context(d,false); auto result = rebuild(d,ctx,report);
        require(snapshot(*result) == snapshot(d) && !report.changedWorld && report.rngAfter == ctx.rng,
                "corpus unchangedworld path preserves rawbytes andRNG exactly"); ++count;
    };
    for (const char* relative : {"TUTORIAL.SAV","Saves/AUTOSAVE.SAV","Campaign/AUTOSAVE.CPN","Campaign/ChCht001.CPN"}) {
        if (!fs::is_regular_file(directory / relative)) continue;
        auto d = std::make_unique<save::Document>(); save::Error error;
        if (!save::readDocument(directory/relative,*d,error)) throw std::runtime_error(error.message);
        unchanged(*d);
        if (std::string(relative) == "TUTORIAL.SAV") {
            LoadWorldPresentationReport report; auto ctx = context(*d); auto transformed = rebuild(*d,ctx,report);
            require(report.mapRebuilt && report.heightMap.size() == d->tiles.size()*1024 && report.colorMap.size() == report.heightMap.size(),
                    "realTutorial changedworld generates entire originalresolutionmap");
            require(report.selectedTerritory == uint32_t(d->players[size_t(d->options.localPlayer)].homeTerritory) &&
                    transformed->options.turn == d->options.turn, "realTutorialselectshome withoutadvancingturn");
        }
    }
    if (fs::is_regular_file(directory/"LEVELS.HDX") && fs::is_regular_file(directory/"LEVELS.HDD")) {
        HdxArchive archive; std::string why;
        if (!archive.open((directory/"LEVELS").string(),&why)) throw std::runtime_error(why);
        for (const auto& entry : archive.entries()) {
            auto d = std::make_unique<save::Document>(); save::Error error;
            if (!save::readScenario(directory/"LEVELS",entry.name,*d,error)) throw std::runtime_error(error.message);
            unchanged(*d);
        }
    }
    if (fs::is_regular_file(directory/"DEADLOCK.EXE")) {
        std::ifstream stream(directory/"DEADLOCK.EXE",std::ios::binary);
        const std::vector<uint8_t> image((std::istreambuf_iterator<char>(stream)),{});
        auto d = fixture(); auto ctx = context(*d); LoadWorldPresentationReport report;
        for (int theme = 0; theme < 7; ++theme) {
            d->world.worldType = uint8_t(theme); auto out = rebuild(*d,ctx,report); (void)out;
            require(report.palettePatches[0].bytes == peBytes(image,0x519ecc+uint32_t(theme)*256,256) &&
                    report.palettePatches[1].bytes == peBytes(image,0x51a5cc,24) &&
                    report.palettePatches[2].bytes == peBytes(image,0x51a5e4,448), "all7themes pluscommonpatches exactPEbytes");
        }
    }
    std::cout << "world presentation optionalcorpus: " << count << " unchangedworlddocuments; Tutorialvisual andPEpalettes checkedwhenpresent\n";
}
} // namespace
int main(int argc, char** argv) {
    try {
        exactSeaOracle(); terrainSelectionAndPalettes(); unchangedAndTransactions();
        corpus(argc > 1 ? std::filesystem::path(argv[1]) : std::filesystem::path{});
        std::cout << "load_world_presentation: integerseaoracle, terrain/selection/palettes, RNGorder, rollback andisolation passed\n";
        return 0;
    } catch (const std::exception& exception) {
        std::cerr << "load_world_presentation: " << exception.what() << '\n'; return 1;
    }
}
