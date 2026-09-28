// Filesystem integration of the owning inspector session; only test-owned files.
#include "app/inspector_session.h"
#include "game/save_files.h"

#include <chrono>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>

namespace {
namespace fs = std::filesystem;
using namespace dl2;
using namespace dl2::worldview;

void require(bool condition, const char* message) {
    if (!condition) throw std::runtime_error(message);
}

struct Scratch {
    fs::path path;
    Scratch() {
        const auto parent = fs::temp_directory_path();
        const auto nonce = std::chrono::steady_clock::now().time_since_epoch().count();
        for (int attempt = 0; attempt < 100; ++attempt) {
            auto candidate = parent / ("dl2-session-test-" + std::to_string(nonce) + "-" + std::to_string(attempt));
            if (fs::create_directory(candidate)) { path = std::move(candidate); return; }
        }
        throw std::runtime_error("could not create exclusive test directory");
    }
    ~Scratch() {
        // path is assigned only after exclusive creation of one test child.
        if (!path.empty()) { std::error_code ignored; fs::remove_all(path, ignored); }
    }
};

std::unique_ptr<save::Document> fixture() {
    auto d = std::make_unique<save::Document>();
    std::memcpy(d->header.text, save::kHeaderText, sizeof(save::kHeaderText));
    d->header.version = kSaveVersion;
    d->header.minusOne = -1;
    d->options.turn = 25;
    d->options.numPlayers = 1;
    d->options.localPlayer = 0;
    d->players[0].type = 1;
    d->players[0].homeTerritory = 3;
    d->world.width = 4;
    d->world.height = 2;
    d->world.numTerritories = 3;
    for (auto& jobs : d->ministerJobs) jobs.resize(1);
    d->territories.resize(3);
    for (size_t i = 0; i < 3; ++i) d->territories[i].data.index = uint16_t(i + 1);
    d->tiles.resize(8);
    for (int y = 0; y < 2; ++y) {
        for (int x = 0; x < 4; ++x) {
            auto& tile = d->tiles[size_t(y * 4 + x)];
            tile.x = uint8_t(x);
            tile.y = uint8_t(y);
            tile.territory = x < 2 ? 1 : int16_t(x);
            auto& t = d->territories[size_t(tile.territory - 1)].data;
            t.tiles[t.numTiles++].raw = uint32_t(x) | (uint32_t(y) << 16);
        }
    }
    d->buildings.resize(1);
    auto& b = d->buildings[0];
    b.id = 120;
    b.type = 1;
    b.territory = 2;
    b.site = 0;
    d->territories[1].data.sites[0].building.raw = b.id;
    d->armies.resize(1);
    auto& a = d->armies[0];
    a.id = 300;
    a.type = 1;
    a.health = 100;
    a.owner = 0;
    a.territory.raw = a.dest.raw = a.origin.raw = 2;
    return d;
}

std::vector<uint8_t> bytes(const save::Document& document) {
    std::vector<uint8_t> result;
    save::Error error;
    require(save::encode(document, result, error), "test document encoding");
    return result;
}

void createDocument(const fs::path& path, const save::Document& document) {
    save::Error error;
    if (!save::writeDocumentCopy(path, document, error))
        throw std::runtime_error("test fixture write: " + error.message);
}

void writeBytes(const fs::path& path, const std::vector<uint8_t>& data) {
    require(!fs::exists(path), "test raw output must be new");
    std::ofstream output(path, std::ios::binary);
    output.write(reinterpret_cast<const char*>(data.data()), std::streamsize(data.size()));
    output.close();
    require(bool(output), "test raw output complete");
}

void appendU32(std::vector<uint8_t>& data, uint32_t value) {
    for (int shift = 0; shift < 32; shift += 8) data.push_back(uint8_t(value >> shift));
}

void archive(const fs::path& base, const save::Document& document) {
    std::vector<uint8_t> index;
    appendU32(index, 1);
    const char name[8] = {'S', 'C', 'E', 'N', '0', '0', '1', '\0'};
    index.insert(index.end(), name, name + sizeof(name));
    appendU32(index, 0);
    auto indexPath = base;
    indexPath += ".HDX";
    writeBytes(indexPath, index);
    const auto payload = bytes(document);
    std::vector<uint8_t> data;
    appendU32(data, uint32_t(payload.size()));
    data.insert(data.end(), payload.begin(), payload.end());
    auto dataPath = base;
    dataPath += ".HDD";
    writeBytes(dataPath, data);
}

struct Snapshot {
    const save::Document* address;
    std::vector<uint8_t> encoded;
    std::string source;
    Selection selected;
    Rect origin;
    int tileSize;
    explicit Snapshot(const app::InspectorSession& session)
        : address(session.document()), encoded(bytes(*address)), source(session.sourceLabel()),
          selected(session.selection().selection()), origin(session.camera().tileRect({0, 0})),
          tileSize(session.camera().tileSize()) {}
    void unchanged(const app::InspectorSession& session) const {
        require(session.document() == address, "failure/copy keeps owning document address");
        require(bytes(*session.document()) == encoded, "failure/copy keeps save bytes");
        require(session.sourceLabel() == source, "failure/copy keeps source");
        const auto& s = session.selection().selection();
        require(s.tile == selected.tile && s.territory == selected.territory && s.kind == selected.kind &&
                s.objectId == selected.objectId, "failure/copy keeps selection");
        const auto current = session.camera().tileRect({0, 0});
        require(current.x == origin.x && current.y == origin.y && session.camera().tileSize() == tileSize,
                "failure/copy keeps camera");
    }
};

void run() {
    Scratch scratch;
    auto d = fixture();
    const auto input = scratch.path / "original.sav";
    const auto copy = scratch.path / "copy.sav";
    const auto corrupt = scratch.path / "corrupt.sav";
    createDocument(input, *d);
    writeBytes(corrupt, {'b', 'a', 'd'});

    app::InspectorSession session;
    require(!session.document() && !session.failed(), "empty session begins without error");
    require(!session.reload() && session.failed(), "reload without source fails");
    require(!session.saveCopy(copy) && !fs::exists(copy), "save without document writes nothing");
    require(session.load(input) && !session.failed(), "load valid document clears errors");
    require(bytes(*session.document()) == bytes(*d), "loaded bytes match source");
    require(session.selection().selection().territory == 3, "local home territory takes priority over objects");
    require(session.selection().selection().kind == ObjectKind::None, "empty home has no automatic object");

    require(session.selection().selectObject(*session.document(), ObjectKind::Army, 300), "manual object selection");
    session.camera().fit(*session.document(), {8, 76, 120, 70});
    session.camera().zoom(3, 250, 150, *session.document(), app::InspectorSession::kMapViewport);
    session.camera().pan(-30, -20, *session.document(), app::InspectorSession::kMapViewport);
    const Snapshot prior(session);
    require(!session.load(corrupt) && session.failed(), "corrupt load fails");
    prior.unchanged(session);
    require(!session.load(scratch.path / "missing.sav"), "missing load fails");
    prior.unchanged(session);
    require(!session.loadScenario(scratch.path / "missing", "SCEN001"), "missing scenario fails");
    prior.unchanged(session);
    require(!session.saveCopy(input) && session.failed(), "cannot overwrite source");
    prior.unchanged(session);
    require(session.saveCopy(copy) && !session.failed(), "save new copy succeeds");
    prior.unchanged(session);
    auto copied = std::make_unique<save::Document>();
    save::Error error;
    require(save::readDocument(copy, *copied, error) && bytes(*copied) == bytes(*d), "saved copy is byte-identical");
    require(!session.saveCopy(copy), "cannot overwrite previous copy");
    prior.unchanged(session);

    const auto temporarilyMoved = scratch.path / "held-original.sav";
    fs::rename(input, temporarilyMoved);
    require(!session.reload() && session.failed(), "reload failure preserves current view");
    prior.unchanged(session);
    fs::rename(temporarilyMoved, input);
    fs::remove(copy); // This is exclusively created by this test above.
    require(session.reload(), "reload reads original source rather than saved copy");
    require(session.selection().selection().territory == 3, "successful reload reinitializes selection");
    require(session.sourceLabel() == prior.source, "reload retains original source label");

    // Without a valid home, the first territory containing objects is preferred.
    d->players[0].homeTerritory = 999;
    d->options.turn = 77;
    const auto base = scratch.path / "LEVELS";
    archive(base, *d);
    require(session.loadScenario(base, "SCEN001"), "archive scenario load succeeds");
    require(session.document()->options.turn == 77, "scenario document is selected");
    require(session.sourceLabel().find("SCEN001") != std::string::npos, "scenario entry appears in source label");
    require(session.selection().selection().territory == 2 &&
            session.selection().selection().kind == ObjectKind::Building &&
            session.selection().selection().objectId == 120, "fallback chooses occupied territory and first object");
    const Snapshot scenarioPrior(session);
    require(!session.loadScenario(base, "UNKNOWN"), "missing archive entry fails");
    scenarioPrior.unchanged(session);
    require(session.reload(), "reload remembers archive source and entry");
    require(session.document()->options.turn == 77, "reload reads scenario again");
    const auto scenarioCopy = scratch.path / "scenario-copy.sav";
    const Snapshot beforeCopy(session);
    require(session.saveCopy(scenarioCopy), "archive payload can be saved as independent new copy");
    beforeCopy.unchanged(session);

    auto map = std::make_unique<save::Document>();
    std::memcpy(map->header.text, save::kHeaderText, sizeof(save::kHeaderText));
    map->header.version = kSaveVersion;
    map->header.isMap = 1;
    map->world.width = map->world.height = 1;
    map->world.numTerritories = 1;
    map->mapTerritories.resize(1);
    map->tiles.resize(1);
    map->tiles[0].territory = 1;
    const auto mapPath = scratch.path / "small.map";
    createDocument(mapPath, *map);
    require(session.load(mapPath), "map loads without game-style territories");
    require(session.selection().selection().territory == 1 && session.selection().selection().objectId == 0,
            "map fallback picks first territory without objects");
    session.fit();
    require(session.document()->header.isMap == 1, "fit does not activate or change map");
}

} // namespace

int main() {
    try {
        run();
        std::cout << "inspector_session: transactional load/reload, selection, archive, maps and safe copies passed\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "inspector_session: " << error.what() << '\n';
        return 1;
    }
}
