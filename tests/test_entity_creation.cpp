// Independent numeric oracles derived from 0044d890/0044dcf4/0044c9a0,
// site-road routines and 00445d30. Not a live original-game comparison.
#include "game/entity_creation.h"
#include "game/data_tables.h"
#include "game/labor_balance.h"
#include "game/runtime_state.h"
#include "game/save_files.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include "formats/hdx_archive.h"

#include <algorithm>
#include <array>
#include <bit>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
using namespace dl2;
using simulation::BuildingCreationRequest;
using simulation::BuildingCreationReport;
void require(bool condition, const char* message) {
    if (!condition) throw std::runtime_error(message);
}
std::unique_ptr<save::Document> fixture(int territories = 2) {
    auto d = std::make_unique<save::Document>();
    std::memcpy(d->header.text, save::kHeaderText, sizeof(save::kHeaderText));
    d->header.version = kSaveVersion;
    d->options.numPlayers = 1; d->options.localPlayer = 0; d->options.turn = 41;
    d->options.nextGlobalId = 1000;
    d->world.width = 1; d->world.height = 1; d->world.numTerritories = uint16_t(territories);
    d->world.rngSeed = 0x12345678; d->tiles.resize(1);
    for (int p = 0; p < kMaxPlayers; ++p) {
        d->players[size_t(p)].index = uint8_t(p); d->players[size_t(p)].race = 2;
        d->ministerJobs[size_t(p)].resize(1); d->ministerJobs[size_t(p)][0].type = 1;
        d->raceStats.v[24][p] = 100;
    }
    d->players[0].type = 1; d->players[0].credits = -123;
    d->territories.resize(size_t(territories));
    for (int i = 0; i < territories; ++i) {
        auto& t = d->territories[size_t(i)].data;
        t.index = uint16_t(i + 1); t.owner = 0; t.terrain = 1;
        t.population = 500; t.morale = 100; t.materials[2] = 20000;
        t.production[3] = 1234; t.consumption[8] = -77;
        for (int site = 0; site < kNumSites; ++site) {
            t.sites[site].unk_00 = uint16_t((site % 6) | ((site / 6) << 8));
            t.sites[site].terrainFlags = 1;
            t.sites[site].unk_05[11] = 0xff;
            t.sites[site].unk_05[13] = 0x34; t.sites[site].unk_05[14] = 0x12;
        }
    }
    d->trailing = {0,0xff,0x80}; d->localList = {0,0x12345678};
    d->events.resize(1); d->options.eventCount = 1;
    d->events[0].record.textLen = 3; d->events[0].text = {'A',0,0xff};
    return d;
}
Building& addBuilding(save::Document& d, uint8_t type, int site, int territory = 1) {
    Building b{};
    b.id = uint16_t(d.buildings.size() + 1); b.type = type;
    b.category = data::kBuildingTypes[type].category;
    b.race = 2; b.flags = 6; b.site = int8_t(site); b.territory = int16_t(territory);
    if (!d.buildings.empty()) { b.prev.raw = d.buildings.back().id; d.buildings.back().next.raw = b.id; }
    d.territories[size_t(territory - 1)].data.sites[size_t(site)].building.raw = b.id;
    d.territories[size_t(territory - 1)].data.sites[size_t(site)].terrainFlags |= 0x3000;
    d.buildings.push_back(b); return d.buildings.back();
}
std::vector<uint8_t> bytes(const save::Document& d) {
    std::vector<uint8_t> result;
    save::Error error;
    if (!save::encode(d, result, error)) throw std::runtime_error("encode fixture: " + error.message);
    for (const auto& record : d.territories) {
        const auto* begin = reinterpret_cast<const uint8_t*>(&record.data);
        result.insert(result.end(), begin + kTerritorySavedBytes, begin + sizeof(Territory));
        for (const auto& queue : record.queues) for (const auto& node : queue) {
            const auto* next = reinterpret_cast<const uint8_t*>(&node.next);
            result.insert(result.end(), next, next + sizeof(node.next));
        }
    }
    return result;
}
struct Created {
    std::unique_ptr<save::Document> document = std::make_unique<save::Document>();
    BuildingCreationReport report;
};
Created create(const save::Document& d, int type, int site, uint32_t territory = 1) {
    const auto before = bytes(d);
    Created result;
    save::Error error{save::ErrorCode::Io,999,"stale"};
    if (!simulation::createCompletedBuilding(d,{territory,type,site},*result.document,result.report,error))
        throw std::runtime_error(error.message);
    require(error.code == save::ErrorCode::None && error.offset == 0 && error.message.empty(), "creation clears old errors");
    require(bytes(d) == before, "creation never mutates source, queues or unsaved tails");
    require(result.report.localLaborBalanced && result.report.siteRoadsRebuilt &&
            result.report.buildingId == uint16_t(uint32_t(d.options.nextGlobalId) + (type==38?2u:1u)), "creation identifies local completed effects and original next ID");
    return result;
}
void rejected(const save::Document& d, BuildingCreationRequest request) {
    auto destination = fixture();
    const auto oldSource = bytes(d), oldDestination = bytes(*destination);
    BuildingCreationReport report{654,9,47,35,-7,123,{3,5},true,false}, oldReport = report;
    save::Error error;
    require(!simulation::createCompletedBuilding(d,request,*destination,report,error), "unsupported/invalid creation must fail");
    require(error.code != save::ErrorCode::None && !error.message.empty(), "failure is explicit, not success without callbacks");
    require(bytes(d) == oldSource && bytes(*destination) == oldDestination && report == oldReport,
            "failed creation preserves source, destination and previous report");
    auto alias = std::make_unique<save::Document>(d);
    require(!simulation::createCompletedBuilding(*alias,request,*alias,report,error) && bytes(*alias) == oldSource && report == oldReport,
            "in-place failure also rolls back all document bytes and report");
}
int path(const BuildingSite& site) {
    return std::bit_cast<int16_t>(uint16_t(site.unk_05[13] | (uint16_t(site.unk_05[14]) << 8)));
}

void housingInitializationAndLocality() {
    auto source = fixture();
    auto& other = addBuilding(*source,1,0,2);
    other.task[1] = 0; other.labor[1] = 99; other.flags = 0x200;
    source->territories[1].data.population = 0; source->territories[1].data.morale = -33;
    const auto result = create(*source,1,0);
    const auto& b = result.document->buildings.back();
    Building expected{};
    expected.id = 1001; expected.flags = 6; expected.type = 1; expected.category = 17;
    expected.race = 2; expected.site = 0; expected.territory = 1; expected.prev.raw = 1;
    expected.task[0] = 21; expected.task[1] = 20; expected.labor[1] = 5;
    require(std::memcmp(&b,&expected,sizeof(b)) == 0, "housing full-record initialization includes upgrade20tasks and five workers, no phantom defaults");
    require(result.document->buildings[0].next.raw == 1001, "new building appends at the global active tail");
    auto expectedOther = other; expectedOther.next.raw = 1001;
    require(std::memcmp(&expectedOther,&result.document->buildings[0],sizeof(Building)) == 0,
            "another territory's tasks/labor remain byte-exact except append-tail next");
    require(std::memcmp(&source->territories[1].data,&result.document->territories[1].data,sizeof(Territory)) == 0,
            "creation does not balance other territories or reset their morale/roads/scratch");
    const auto& t = result.document->territories[0].data;
    require(t.sites[0].building.raw == 1001 && t.sites[0].terrainFlags == 0x3001 && t.materials[2] == 20000,
            "size1 anchor/occupation without EndTurnBalance stock clamp");
    for (const auto& site : t.sites) require(site.unk_05[11] == 0 && path(site) == 0x1234,
            "one housing clears roads but has no target and leaves path scratch untouched");
    require(result.document->options.turn == 41 && result.document->players[0].credits == -123 &&
            result.document->options.nextGlobalId == 1001 && result.report.footprint == std::vector<uint8_t>{0},
            "creation increments ID only: no turn or payment");
    // Compare the entire document after accounting only for documented writes.
    auto restored = std::make_unique<save::Document>(*result.document);
    restored->buildings = source->buildings; restored->territories = source->territories;
    restored->options.nextGlobalId = source->options.nextGlobalId;
    require(bytes(*restored) == bytes(*source), "all non-building/local-territory/counter bytes remain identical");
    auto alias = std::make_unique<save::Document>(*source);
    BuildingCreationReport report; save::Error error;
    require(simulation::createCompletedBuilding(*alias,{1,1,0},*alias,report,error) &&
            bytes(*alias) == bytes(*result.document) && report == result.report, "in-place success equals independent destination");
}

void footprintsLaborAndRoadOracles() {
    auto source = fixture();
    auto& housing = addBuilding(*source,1,0);
    housing.task[1] = 20; housing.labor[1] = 5;
    auto farm = create(*source,5,14);
    const auto& made = farm.document->buildings.back();
    require(made.task[0] == 0 && made.task[1] == 12 && made.task[2] == 13 && made.labor[1] == 5 && made.labor[2] == 0 &&
            farm.document->buildings[0].labor[1] == 0, "RedistributeLabor sends housing workers to FIRST nonupgrade task, not even distribution");
    const auto& t = farm.document->territories[0].data;
    require(t.sites[14].terrainFlags == 0x1001 && t.sites[15].terrainFlags == 0x2001 &&
            t.sites[8].terrainFlags == 0x3001 && t.sites[9].terrainFlags == 0x4001 &&
            t.sites[14].building.raw == 1001 && !t.sites[15].building.raw && !t.sites[8].building.raw && !t.sites[9].building.raw,
            "size2 writes exact quadrant flags and only the anchor owns its building ID");
    require(farm.report.footprint == std::vector<uint8_t>({14,15,8,9}), "size2 footprint points upward-right");
    auto culture = create(*source,21,2);
    const auto& sites = culture.document->territories[0].data.sites;
    require(sites[0].unk_05[11] == 2 && sites[1].unk_05[11] == 10 && sites[2].unk_05[11] == 8,
            "straight site road has east / east+west / west reciprocal masks");
    for (int site = 3; site < 36; ++site) require(sites[site].unk_05[11] == 0, "road trace does not fabricate extra branches");
    require(path(sites[0]) == 0 && path(sites[1]) == 4 && path(sites[2]) == 8 && path(sites[6]) == 4 && path(sites[7]) == 32767,
            "DFS cost4 prunes costs equal to best8 and retains final search scratch");
    source->territories[0].data.sites[2].unk_00 = 0xffff;
    auto corruptedCoordinates = create(*source,21,2);
    for (const auto& site : corruptedCoordinates.document->territories[0].data.sites)
        require(site.unk_05[11] == 0, "search uses site index but trace uses signed saved coordinates, stopping without lower neighbor");
    require(path(corruptedCoordinates.document->territories[0].data.sites[2]) == 8, "trace coordinate mismatch does not alter search costs");
    source->territories[0].data.sites[2].unk_00 = 2;
    source->territories[0].data.sites[1].terrainFlags = 0x2001;
    auto blocked = create(*source,21,2);
    require(path(blocked.document->territories[0].data.sites[1]) == 32767 &&
            blocked.document->territories[0].data.sites[1].unk_05[11] == 0, "exact highbyte2000 blocks traversal");
    source->territories[0].data.sites[1].terrainFlags = 0x2101;
    auto notBlocked = create(*source,21,2);
    require(path(notBlocked.document->territories[0].data.sites[1]) == 4, "highbyte2100 is not incorrectly treated as blocked2000");
    // Existing roads reset, but unavailable FF cells remain traversable at25.
    source->territories[0].data.sites[1].terrainFlags = 0xff;
    auto alternate = create(*source,21,2);
    require(alternate.document->territories[0].data.sites[1].unk_05[11] == 0 &&
            alternate.document->territories[0].data.sites[6].unk_05[11] != 0, "weighted search chooses the 16-cost detour over unavailable-cell25");
}

void tasksCityCentersAndSignedEdges() {
    auto source = fixture();
    auto first = create(*source,37,14);
    require(first.document->buildings.back().hubLevel == 0 && first.document->buildings.back().race == 2,
            "first city center counts itself then stores count minus one");
    auto second = create(*first.document,37,14,2);
    require(second.document->buildings.back().hubLevel == 1, "second same-owner city center stores level1");
    source->players[0].index = 31;
    source->techs[20].knownMask = 0x8000;
    auto mine = create(*source,8,14);
    require(mine.document->buildings.back().task[1] == 3 && mine.document->buildings.back().task[2] == 4,
            "task technology uses sign-extended16 mask and Player.index31, not owner0");
    source->techs[20].knownMask = 1;
    mine = create(*source,8,14);
    require(mine.document->buildings.back().task[2] == 0, "owner0 tech bit is not substituted for Player.index task gate");
    source->techs[16].knownMask = 1;
    mine = create(*source,8,14);
    require(mine.document->buildings.back().task[0] == 21, "upgrade technology uses owner slot independently of Player.index");
    source->territories[0].data.population = 0; source->territories[0].data.morale = -90;
    auto empty = create(*source,29,0);
    require(empty.document->territories[0].data.morale == 100, "local BalanceLabor resets morale only when population is zero");
    source->territories[0].data.population = 32767; source->territories[0].data.morale = 127;
    source->raceStats.v[24][2] = 10000;
    auto large = create(*source,1,0);
    require(large.document->buildings.back().labor[1] == 403, "signed labor-pool oracle: pop32767 morale127 yields403, no percentage clamp");
    source->raceStats.v[24][2] = -100;
    auto negative = create(*source,1,0);
    require(negative.document->buildings.back().labor[0] == -5 && negative.document->buildings.back().labor[1] == 0,
            "negative racial housing capacity preserves signed original trimming into upgrade slot");
}

void idsDomainsRollbackAndCapacity() {
    auto source = fixture();
    for (const auto counter : {int32_t(-2),int32_t(-2147483647 - 1),int32_t(65534),int32_t(65536)}) {
        source->options.nextGlobalId = counter;
        const auto result = create(*source,29,0);
        require(result.document->options.nextGlobalId == std::bit_cast<int32_t>(uint32_t(counter)+1u) &&
                result.document->buildings.back().id == uint16_t(uint32_t(counter)+1u), "ID increment wrap32 and truncation16 are defined at extremes");
    }
    for (const auto counter : {int32_t(-1),int32_t(65535),std::numeric_limits<int32_t>::max()}) {
        source->options.nextGlobalId = counter; rejected(*source,{1,29,0});
    }
    source->options.nextGlobalId = 0;
    addBuilding(*source,29,5); rejected(*source,{1,29,0}); // ID1 collision.
    source = fixture();
    Army army{}; army.id=1001; army.type=1; army.owner=0;
    army.territory.raw=army.dest.raw=army.origin.raw=1; source->armies.push_back(army);
    rejected(*source,{1,29,0}); // Cross-kind collision.
    source = fixture();
    for (const auto request : {BuildingCreationRequest{0,1,0}, {3,1,0}, {1,0,0}, {1,48,0},
                               {1,1,-1}, {1,6,0}, {1,1,36}, {1,38,25}, {1,39,0}})
        rejected(*source,request);
    source->territories[0].data.owner=-1; rejected(*source,{1,1,0}); source->territories[0].data.owner=0;
    source->territories[0].data.terrain=0; source->territories[0].data.sites[0].terrainFlags=0xff;
    rejected(*source,{1,29,0}); source->territories[0].data.terrain=1;
    source->territories[0].data.sites[0].terrainFlags=0x5201; rejected(*source,{1,19,0});
    source->territories[0].data.sites[0].terrainFlags=1;
    source->players[0].race=-1; rejected(*source,{1,1,0}); source->players[0].race=2;
    source->header.isMap=1; source->mapTerritories.resize(source->territories.size());
    rejected(*source,{1,29,0}); source->header.isMap=0; source->mapTerritories.clear();
    source->ministerJobs[0][0].type=3; source->ministerJobs[0][0].param[0]=1; source->ministerJobs[0][0].param[1]=9;
    rejected(*source,{1,5,14}); // Secondary footprint cell, not only anchor.
    source->ministerJobs[0][0].type=1;
    auto& housing=addBuilding(*source,1,0); housing.task[1]=20; housing.labor[1]=5; housing.minister=1;
    rejected(*source,{1,21,2}); source->buildings[0].minister=0;
    // Failure occurs AFTER candidate ID, anchor, task/labor and road mutations.
    source->territories[0].data.sites[1].terrainFlags=254;
    rejected(*source,{1,21,2});
    source->territories[0].data.sites[1].terrainFlags=1;
    source->buildings[0].task[1]=0; source->buildings[0].labor[1]=0;
    rejected(*source,{1,21,2}); // Original final housing slot -1.
    source=fixture(); addBuilding(*source,29,0); addBuilding(*source,29,1);
    source->buildings[0].next.raw=0; source->buildings[1].prev.raw=0;
    rejected(*source,{1,29,2}); // Archive-valid, but disconnected active list.
    source=fixture(35);
    source->options.nextGlobalId=2000;
    for (int n=0;n<1198;++n) addBuilding(*source,29,n%36,n/36+1);
    auto maximum=create(*source,29,35,35);
    require(maximum.document->buildings.size()==1199, "1198 to1199 allocation preserves original reserved pool slot");
    rejected(*maximum.document,{35,29,34});
}

void specialBuildings() {
    auto source=fixture();
    source->territories[0].data.terrain=0;
    for (auto& site : source->territories[0].data.sites) site.terrainFlags=0xff;
    auto platform=create(*source,38,25);
    const auto& report=platform.report;
    const auto& d=*platform.document;
    const auto& t=d.territories[0].data;
    require(report.buildingId==1002 && report.companionBuildingId==1001 && report.counterAfter==1002 &&
            report.createdIds==std::vector<uint32_t>({1002,1001}) && report.companionAttempted && !report.companionAllocationFailed,
            "platform reserves Hab ID first but appends platform before Hab");
    require(d.buildings[0].id==1002 && d.buildings[0].next.raw==1001 && d.buildings[1].prev.raw==1002 &&
            d.buildings[1].type==39 && d.buildings[1].race==2 && d.buildings[1].site==15 && d.buildings[1].task[1]==20 &&
            d.buildings[1].task[2]==14 && d.buildings[1].task[3]==7 && d.buildings[1].labor[1]==5,
            "SeaHab defaults, local housing labor and global links");
    require(t.sites[25].building.raw==1002 && t.sites[25].terrainFlags==0xff &&
            t.sites[3].terrainFlags==0x31ff && t.sites[13].terrainFlags==0x11ff &&
            t.sites[15].terrainFlags==0x32ff && t.sites[17].terrainFlags==0x41ff &&
            t.sites[27].terrainFlags==0x21ff && t.sites[1].terrainFlags==0x60ff,
            "exact sparse platform marks and used SeaHab socket, no anchor occupancy flag");
    for (const auto& cell:t.sites) require(cell.unk_05[11]==0 && path(cell)==0x1234,"sea roads clear bytes without path search");
    auto socket=create(d,19,3);
    require(socket.document->territories[0].data.sites[3].terrainFlags==0x32ff &&
            socket.report.createdIds==std::vector<uint32_t>{1003},"free platform socket replacement preserves low terrain");
    rejected(*socket.document,{1,19,3});
    source->options.nextGlobalId=65534; rejected(*source,{1,38,25}); // companion65535, primary0.
    source->options.nextGlobalId=65535; rejected(*source,{1,38,25}); // companion0, primary1.
    source->options.nextGlobalId=1000; source->territories[0].data.owner=-1; rejected(*source,{1,38,25});

    source=fixture();
    auto native=create(*source,45,14);
    require(native.document->buildings[0].task[1]==7 && native.document->buildings[0].task[2]==5 &&
            !(native.document->territories[0].data.flags&0x10),"normal-mode native shrine tasks do not invent editor shrine flag");
    rejected(*native.document,{1,46,0});
    auto hidden=create(*source,46,0);
    require(hidden.document->buildings[0].task[1]==15 && hidden.document->buildings[0].race==0,
            "hidden shrine low terrain1 overrides task index to4 -> energy15");
    source->territories[0].data.terrain=0; source->territories[0].data.sites[0].terrainFlags=0xff;
    auto seaShrine=create(*source,47,0);
    require(seaShrine.document->buildings[0].task[1]==8 && !(seaShrine.document->territories[0].data.flags&0x10),
            "sea shrine index(territory1+site0)%6 selects task8 without editor mutation");
    source->territories[0].data.owner=-1;
    auto unownedShrine=create(*source,47,0);
    for (uint8_t task:unownedShrine.document->buildings[0].task) require(task==0,"unowned shrine skips GetBuildingTasks");
    source=fixture(); source->territories[0].data.owner=-1;
    auto unowned=create(*source,29,0);
    require(unowned.document->buildings[0].race==0,"unowned nonracial initialization is valid");
    source->territories[0].data.owner=0; source->territories[0].data.terrain=0;
    auto seaOrdinary=create(*source,29,0);
    require(seaOrdinary.document->buildings[0].type==29,"explicit site query can permit nonmarine type on available sea terrain");

    source=fixture(35); source->options.nextGlobalId=2000;
    for (int n=0;n<1198;++n) addBuilding(*source,29,n%36,n/36+1);
    source->territories[34].data.terrain=0;
    auto bare=create(*source,38,25,35);
    require(bare.document->buildings.size()==1199 && bare.report.createdIds==std::vector<uint32_t>{2002} &&
            bare.report.companionAttempted && bare.report.companionAllocationFailed && bare.report.companionBuildingId==0 &&
            bare.document->options.nextGlobalId==2002 && bare.document->territories[34].data.sites[15].terrainFlags==0x5101,
            "one remaining slot yields explicit original platform-only result, both IDs consumed");
}

void armyTemplatesAndPurity() {
    auto source=fixture();
    const auto before=bytes(*source);
    std::vector<uint8_t> globalState(sizeof(gs)),globalMisc(sizeof(gg));
    std::memcpy(globalState.data(),&gs,sizeof(gs)); std::memcpy(globalMisc.data(),&gg,sizeof(gg));
    const auto seed=rtl::seed(), seedHi=rtl::seedHi();
    Army output{}; save::Error error;
    require(simulation::initializeArmyTemplate(*source,{1,0,1,1001},output,error), "basic laser squad template succeeds");
    Army expected{}; expected.id=1001; expected.type=1; expected.unitClass=1; expected.owner=0;
    expected.strength=3; expected.health=100; expected.territory.raw=expected.dest.raw=expected.origin.raw=1;
    std::memcpy(expected.name,"Human Laser Squad #1001",23);
    require(std::memcmp(&output,&expected,sizeof(output))==0, "full army record oracle: name, movement3, retreat100, zero damage/experience/cargo/jobs/links");
    source->techs[46].knownMask=1;
    require(simulation::initializeArmyTemplate(*source,{1,0,37,1025},output,error) && output.strength==1 &&
            std::string(output.name)=="Human Land Mine #1", "Transporters adds movement even to stationary mines and name truncates ID to10bits");
    source->players[0].race=6;
    require(simulation::initializeArmyTemplate(*source,{1,0,28,1023},output,error), "air command template");
    require(output.moves==26 && std::memcmp(output.name,"Uva Mosk Air Command #1023",24)==0 && output.name[23]=='0',
            "support tactic26 and fixed24 name copy without fabricated NUL");
    source->players[0].race=2;
    for (int type : {15,26,28}) require(simulation::initializeArmyTemplate(*source,{1,0,type,1001},output,error) && output.moves==26,
            "all supported land/air support classes receive tactic26");
    const Army old=output;
    for (const auto request : {simulation::ArmyTemplateRequest{0,0,1,1001}, {1,-1,1,1001}, {1,7,1,1001},
                              {1,0,0,1001}, {1,0,39,1001}, {1,0,1,0}, {1,0,12,1001}, {1,0,35,1001},
                              {1,0,36,1001}, {1,0,13,1001}}) {
        require(!simulation::initializeArmyTemplate(*source,request,output,error) && std::memcmp(&old,&output,sizeof(output))==0 &&
                error.code!=save::ErrorCode::None, "invalid/special army template fails with destination intact");
    }
    source->territories[0].data.terrain=0;
    require(!simulation::initializeArmyTemplate(*source,{1,0,1,1001},output,error), "land-at-sea cargo attachment cannot be silently skipped");
    require(simulation::initializeArmyTemplate(*source,{1,0,33,1001},output,error) && output.moves==26,
            "sea-command detached template preserves support tactic");
    source->territories[0].data.terrain=1;
    source->techs[46].knownMask=0;
    const auto built=create(*source,1,0);
    require(built.document->buildings.size()==1, "pure creation ran under global guard");
    require(bytes(*source)==before && std::memcmp(globalState.data(),&gs,sizeof(gs))==0 &&
            std::memcmp(globalMisc.data(),&gg,sizeof(gg))==0 && rtl::seed()==seed && rtl::seedHi()==seedHi,
            "building creation and army templates preserve gs, gg, both global RNG words and their inputs");
    source->armies.push_back(expected);
    const auto withArmy=bytes(*source);
    require(!simulation::initializeArmyTemplate(*source,{1,0,1,999},source->armies[0],error) && bytes(*source)==withArmy,
            "template destination cannot alias and overwrite an existing input army");
}

void runtimeIntegration() {
    auto source=fixture();
    auto& housing=addBuilding(*source,1,0); housing.task[1]=20; housing.labor[1]=5;
    Army a{}; a.id=44; a.type=1; a.owner=0; a.health=100;
    a.territory.raw=a.dest.raw=a.origin.raw=1; source->armies.push_back(a);
    source->territories[0].data.armies.raw=a.id;
    const auto sourceBytes=bytes(*source);
    runtime::State state; save::Error error;
    require(state.prepare(*source,error), "runtime prepares creation fixture");
    const auto originalBuilding=state.buildingById(1);
    const auto originalArmy=state.armyById(44);
    const auto originalTerritory=state.territoryByIndex(1);
    const auto originalTile=state.tileByIndex(1);
    const auto rng=state.sessionRng();
    simulation::BuildingCreationReport report;
    runtime::BuildingHandle first;
    require(state.createCompletedBuilding({1,21,2},first,report,error) && state.stage()==runtime::Stage::EntitiesEdited,
            "runtime creation enters explicitly nonplayable entity-edit stage");
    require(state.building(first) && state.building(first)->id==1001 && state.buildingById(1001)==first &&
            state.buildingLinks(first)->previous==originalBuilding && state.buildingLinks(originalBuilding)->next==first &&
            state.graph().territories[0].sites[2]==first && state.buildingLinks(first)->territory==originalTerritory,
            "runtime graph resolves appended building and reciprocal tail/site references");
    runtime::BuildingHandle second;
    require(state.createCompletedBuilding({1,29,3},second,report,error) && second!=first &&
            state.buildingLinks(first)->next==second && state.buildingLinks(second)->previous==first,
            "successive completed creations append and preserve earlier identities");
    require(state.building(originalBuilding) && state.army(originalArmy) && state.territory(originalTerritory) &&
            state.tile(originalTile) && state.buildingById(1)==originalBuilding && state.armyById(44)==originalArmy && state.sessionRng()==rng,
            "surviving building/army/static handles and session RNG stay valid across creation");
    const auto before=bytes(*state.document());
    const auto priorReport=report;
    auto created=second;
    require(!state.createCompletedBuilding({1,21,2},created,report,error) && created==second && report==priorReport &&
            bytes(*state.document())==before && state.stage()==runtime::Stage::EntitiesEdited && state.sessionRng()==rng &&
            state.building(first) && state.building(originalBuilding), "failed runtime creation preserves state/report/output handle and all lifetimes");
    auto captured=fixture(); const auto captureBefore=bytes(*captured);
    require(!state.capture(*captured,error) && bytes(*captured)==captureBefore && !state.advanceTurn(error) &&
            bytes(*state.document())==before, "creation cannot be captured as resumable SAV or claimed as a complete turn");
    simulation::TaxPlan taxes;
    require(!state.collectTaxes(taxes,error), "isolated economic phases cannot be chained after entity creation");
    runtime::State empty;
    require(!empty.createCompletedBuilding({1,1,0},created,report,error) && created==second && report==priorReport &&
            empty.stage()==runtime::Stage::Empty, "empty state creation fails transactionally");
    require(sourceBytes==bytes(*source) && source->buildings.size()==1 && source->options.nextGlobalId==1000,
            "runtime creation owns its document and leaves caller input untouched");
}

void corpus(const std::filesystem::path& directory) {
    if (directory.empty()) { std::cout<<"entity creation optional corpus: no data directory\n"; return; }
    namespace fs=std::filesystem;
    size_t documents=0, successes=0;
    const auto inspect=[&](const save::Document& d) {
        const auto original=bytes(d); ++documents;
        bool succeeded=false;
        for (const auto& tr : d.territories) {
            if (tr.data.owner<0 || !tr.data.terrain) continue;
            for (int site=0;site<36;++site) {
                if (tr.data.sites[site].building.raw || (tr.data.sites[site].terrainFlags>>8)) continue;
                auto destination=std::make_unique<save::Document>(d);
                BuildingCreationReport report; save::Error error;
                if (simulation::createCompletedBuilding(d,{tr.data.index,29,site},*destination,report,error)) {
                    save::Error validation;
                    require(save::validate(*destination,validation) && destination->buildings.size()==d.buildings.size()+1,
                            "corpus successful creation remains structurally valid");
                    auto repeated=std::make_unique<save::Document>(); BuildingCreationReport again;
                    require(simulation::createCompletedBuilding(d,{tr.data.index,29,site},*repeated,again,error) &&
                            bytes(*repeated)==bytes(*destination) && again==report, "corpus creation is deterministic");
                    ++successes; succeeded=true; break;
                }
                require(bytes(*destination)==original && report==BuildingCreationReport{}, "corpus refusal cannot leave partial changes");
                // Try another territory, not every rejected site of a managed region.
                break;
            }
            if (succeeded) break;
        }
        require(bytes(d)==original, "all corpus inputs are unchanged");
    };
    for (const char* relative : {"TUTORIAL.SAV","Saves/AUTOSAVE.SAV","Campaign/AUTOSAVE.CPN","Campaign/ChCht001.CPN"}) {
        if (!fs::is_regular_file(directory/relative)) continue;
        auto d=std::make_unique<save::Document>(); save::Error error;
        if (!save::readDocument(directory/relative,*d,error)) throw std::runtime_error(error.message);
        inspect(*d);
    }
    if (fs::is_regular_file(directory/"LEVELS.HDX") && fs::is_regular_file(directory/"LEVELS.HDD")) {
        HdxArchive archive; std::string why;
        if (!archive.open((directory/"LEVELS").string(),&why)) throw std::runtime_error(why);
        for (const auto& entry : archive.entries()) {
            auto d=std::make_unique<save::Document>(); save::Error error;
            if (!save::readScenario(directory/"LEVELS",entry.name,*d,error)) throw std::runtime_error(error.message);
            inspect(*d);
        }
    }
    std::cout<<"entity creation optional corpus: "<<documents<<" documents, "<<successes<<" supported creations\n";
    require(documents==0 || successes>0, "optional corpus exercises at least one successful completed creation");
}
} // namespace
int main(int argc,char** argv) {
    try {
        housingInitializationAndLocality(); footprintsLaborAndRoadOracles(); tasksCityCentersAndSignedEdges();
        idsDomainsRollbackAndCapacity(); specialBuildings(); armyTemplatesAndPurity(); runtimeIntegration();
        corpus(argc>1?std::filesystem::path(argv[1]):std::filesystem::path{});
        std::cout<<"entity_creation: initialization, IDs, local labor, footprints/site roads, templates and transactional purity passed\n";
        return 0;
    } catch (const std::exception& error) { std::cerr<<"entity_creation: "<<error.what()<<'\n'; return 1; }
}
