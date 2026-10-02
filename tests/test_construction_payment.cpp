// Numeric oracles derived from original integer operations/assembly, not
// observations obtained by executing DEADLOCK.EXE or self-expected snapshots.
#include "game/construction_payment.h"
#include "game/data_tables.h"
#include "game/save_files.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include "formats/hdx_archive.h"
#include <array>
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
using namespace dl2::simulation;
void require(bool condition,const char* message) { if (!condition) throw std::runtime_error(message); }
std::unique_ptr<save::Document> fixture(int n = 3) {
    auto d = std::make_unique<save::Document>();
    std::memcpy(d->header.text,save::kHeaderText,sizeof(save::kHeaderText));
    d->header.version = kSaveVersion; d->options.numPlayers = 7; d->options.localPlayer = 0;
    d->options.turn = 19; d->options.gameId = 54; d->options.nextGlobalId = 411;
    d->world.width = uint8_t(n); d->world.height = 1; d->world.numTerritories = uint16_t(n);
    d->territories.resize(size_t(n)); d->tiles.resize(size_t(n));
    for (int p = 0; p < 7; ++p) {
        d->ministerJobs[size_t(p)].resize(1); d->players[size_t(p)].index = uint8_t(p);
        d->players[size_t(p)].race = int8_t(p); d->players[size_t(p)].credits = 100;
    }
    for (int i = 0; i < n; ++i) {
        auto& t = d->territories[size_t(i)].data; t.index = uint16_t(i+1); t.owner = 0;
        t.numTiles = 1; t.tiles[0].raw = uint32_t(i); t.centerTile = 0; t.terrain = 1;
        t.flags = 0x40000002; t.consumption[7] = 991;
        std::memset(t.unk_ad6,0xda,sizeof(t.unk_ad6)); //Never interpreted as native suppliers.
        for (auto& value : t.production) value = 77;
        d->tiles[size_t(i)].x = uint8_t(i); d->tiles[size_t(i)].territory = int16_t(i+1);
    }
    d->localList = {0,97}; d->events.resize(1); d->options.eventCount = 1;
    d->events[0].text = {'a',0,0xff}; d->events[0].record.textLen = 3;
    return d;
}
Territory& t(save::Document& d,int index) { return d.territories[size_t(index-1)].data; }
const Territory& t(const save::Document& d,int index) { return d.territories[size_t(index-1)].data; }
void adjacent(save::Document& d,int a,int b) {
    t(d,a).adjacency[b/16] |= uint16_t(1u << (b%16));
    t(d,b).adjacency[a/16] |= uint16_t(1u << (a%16));
}
void building(save::Document& d,int territory,int type,int site=0) {
    Building b{}; b.id = uint16_t(900+d.buildings.size()); b.type = uint8_t(type);
    b.category = data::kBuildingTypes[type].category; b.territory = int16_t(territory); b.site = int8_t(site);
    b.turnsLeft = 100; t(d,territory).sites[site].building.raw = b.id;
    d.buildings.push_back(b);
}
std::vector<uint8_t> snapshot(const save::Document& d) {
    save::Error error; std::vector<uint8_t> result;
    if (!save::encode(d,result,error)) throw std::runtime_error(error.message);
    for (const auto& record : d.territories) {
        const auto* bytes = reinterpret_cast<const uint8_t*>(&record.data);
        result.insert(result.end(),bytes+kTerritorySavedBytes,bytes+sizeof(Territory));
    }
    return result;
}
ConstructionRequirements requirements(const save::Document& d,int type) {
    ConstructionRequirements result; save::Error error{save::ErrorCode::Io,13,"old"};
    require(buildingConstructionRequirements(d,1,type,result,error),"building requirements query succeeds");
    require(error.code == save::ErrorCode::None && error.message.empty() && error.offset == 0,"requirements clear error");
    return result;
}
ConstructionPaymentContext context() { ConstructionPaymentContext ctx; ctx.selectedTerritory = 1; return ctx; }
std::unique_ptr<save::Document> pay(const save::Document& d,const ConstructionRequirements& req,
                                   ConstructionPaymentReport& report,ConstructionPaymentContext ctx=context()) {
    const auto before = snapshot(d); auto out = fixture(); save::Error error{save::ErrorCode::Io,8,"old"};
    if (!payConstructionRequirements(d,1,req,ctx,*out,report,error)) throw std::runtime_error(error.message);
    require(error.code == save::ErrorCode::None && error.offset == 0 && error.message.empty(),"payment success clears error");
    require(snapshot(d) == before,"payment never mutates source including scratch and opaque donor words");
    require(out->events[0].text == d.events[0].text && out->localList == d.localList && out->options.turn == 19 &&
            out->options.gameId == 54 && out->options.nextGlobalId == 411,"no event fabrication, turn or ID changes");
    return out;
}

void costAndLocalOracles() {
    auto d = fixture(); auto req = requirements(*d,1);
    require(req.labor == 10 && req.technology == 0 && req.materials[0] == 50 && req.materials[3] == 10,
            "Housing:50credits,10wood,10work from original table");
    auto farm = requirements(*d,5);
    require(farm.labor == 75 && farm.materials[0] == 50 && farm.materials[3] == 0,"Farm original requirements");
    auto hydro = requirements(*d,6);
    require(hydro.labor == 150 && hydro.technology == 11 && hydro.materials[0] == 100 &&
            hydro.materials[3] == 50 && hydro.materials[4] == 50,"Hydroponic original material/tech/work oracle");
    auto city = requirements(*d,37);
    require(city.materials[0] == 125 && city.materials[2] == 50 && city.materials[4] == 250,
            "first City Center discounts ONLY money by4");
    building(*d,2,37); city = requirements(*d,37);
    require(city.materials[0] == 500 && city.materials[2] == 50 && city.materials[4] == 250,"one prior City Center multiplier1");
    building(*d,3,37); city = requirements(*d,37);
    require(city.materials[0] == 1000 && city.materials[2] == 100 && city.materials[4] == 500,"two prior City Centers multiplier2");
    d->players[0].index = 31; city = requirements(*d,37);
    require(city.materials[0] == 125,"City price counts Player.index owner, not physical slot");
    d->players[0].index = 255; t(*d,2).owner = t(*d,3).owner = -1; city = requirements(*d,37);
    require(city.materials[0] == 1000,"signed Player.index255 counts two unowned City Centers as owner-1");
    d->players[0].index = 0; t(*d,2).owner = t(*d,3).owner = 0;
    t(*d,1).materials[3] = 20; ConstructionPaymentReport report; auto out = pay(*d,req,report);
    require(!report.failureMask && report.requirementsAccepted && report.collectionAttempted && report.transportQuote == 0 &&
            report.paid[0] == 50 && report.paid[3] == 10 && report.creditsAfter == 50 && t(*out,1).materials[3] == 10,
            "local Housing payment exact, without creating a building or finishing work");
    for (const auto& territory : out->territories) for (const int reserve : territory.data.production)
        require(reserve == 0,"quote and collection clear ALL territory reservation scratch");
    require(t(*out,1).consumption[7] == 991 && std::memcmp(t(*out,1).unk_ad6,t(*d,1).unk_ad6,6) == 0,
            "other preview scratch and opaque native supplier words untouched");
    require(report.collection.transfers.empty(),"local payment has no fake imports");
}

void ordinaryImportsAndMasks() {
    auto d = fixture(); adjacent(*d,1,2); t(*d,2).materials[3] = 20;
    const auto req = requirements(*d,1); ConstructionPaymentReport report; auto out = pay(*d,req,report);
    require(!report.failureMask && report.transportQuote == 20 && report.creditsAfter == 30 && report.paid[3] == 10 &&
            t(*out,1).materials[3] == 0 && t(*out,2).materials[3] == 10,"same-continent own road fee2 per wood, base50+freight20");
    require(report.collection.suppliers[1] == MaterialSupplier{2,2} &&
            report.collection.transfers == std::vector<MaterialTransfer>{{2,1,3,10,20}},"native IDs/fees and exact transfer log");
    require((t(*out,1).flags & 0x2000) && (t(*out,2).flags & 0x2000),"transport DFS scratch flags preserved");
    auto ctx = context(); ctx.collection.transfers.push_back({2,1,3,7,14}); out = pay(*d,req,report,ctx);
    require(report.collection.transfers == std::vector<MaterialTransfer>{{2,1,3,17,34}},"existing matching transfer accumulates not duplicates");
    for (const auto [credits,mask] : std::array<std::pair<int,uint32_t>,3>{{{70,0},{60,0x2001},{50,1}}}) {
        d->players[0].credits = credits; out = pay(*d,req,report);
        require(report.failureMask == mask,"original affordability strict inequalities at credit thresholds");
        if (mask) require(report.paid[0] == 0 && t(*out,2).materials[3] == 20 && report.creditsAfter == credits,
                          "refused quote has no debit despite reservation scratch mutation");
    }
    d->players[0].credits = 100; t(*d,2).materials[3] = 5; out = pay(*d,req,report);
    require(report.failureMask == 0x2008 && report.transportQuote == -1 && t(*out,2).production[3] == 5 &&
            report.collection.suppliers[1] == MaterialSupplier{0,2},"insufficient supply:negativequote,wooddiagnostic,reservations and retainedfee but donorIDrestored");
    t(*d,3).owner = 1; t(*d,3).materials[3] = 100; ctx = context(); ctx.selectedTerritory = 3;
    out = pay(*d,req,report,ctx);
    require(report.failureMask == 0x2000,"shortage diagnostic deliberately uses selected owner's stocks, not requesting owner");
    ctx.selectedTerritory = 0; out = pay(*d,req,report,ctx);
    require(report.failureMask == 0x2008,"zero sentinel selection has owner0 and zero local materials");
}

void routesAndTechnology() {
    auto d = fixture(); adjacent(*d,1,2); adjacent(*d,2,3);
    t(*d,2).owner = -1; t(*d,3).materials[3] = 20; auto req = requirements(*d,1);
    ConstructionPaymentReport report; auto out = pay(*d,req,report);
    require(!report.failureMask && report.transportQuote == 30 && report.creditsAfter == 20,"neutral same-continent requiresmode1 fee3");
    d->techs[13].knownMask = 1; out = pay(*d,req,report);
    require(report.transportQuote == 20 && report.creditsAfter == 30,"tech13 reduces freight1");
    d->techs[46].knownMask = 1; out = pay(*d,req,report);
    require(report.transportQuote == 10 && report.creditsAfter == 40,"tech46 takes precedence, reducing2 not3");
    d->techs[13].knownMask = d->techs[46].knownMask = 0;
    t(*d,2).continent = 1; out = pay(*d,req,report);
    require(report.transportQuote == 40 && !report.failureMask,"cross-continent requiresmode2 fee4");
    t(*d,2).continent = 0; t(*d,2).owner = 1; out = pay(*d,req,report);
    require(report.failureMask == 0x2000,"foreign nonallied intermediate blocks ordinary maxmode2 despite available stocks");
    d->options.allowAlliances = 1; d->players[0].relations[1] = 2; out = pay(*d,req,report);
    require(report.transportQuote == 30 && !report.failureMask,"pact2 permits intermediate without City Center");
    building(*d,2,37); out = pay(*d,req,report);
    require(report.failureMask == 0x2000,"even UNFINISHED category9 blocks pact2 route");
    d->players[0].relations[1] = 0x10; out = pay(*d,req,report);
    require(report.transportQuote == 30 && !report.failureMask,"pact10 traverses City Center");
    d->players[0].relations[1] = 0; d->players[1].relations[0] = 0x10; out = pay(*d,req,report);
    require(report.failureMask == 0x2000,"pacts are directional, reverse-only does not qualify");
    d->techs[46].knownMask = 1; out = pay(*d,req,report);
    require(report.transportQuote == 30 && !report.failureMask,"tech46 enables unrestrictedmode3 with fee5-2");
    t(*d,1).flags |= 0x100; out = pay(*d,req,report);
    require(report.failureMask == 0x2000,"blocked destination remains unreachable even with technology46");
    t(*d,1).flags &= ~0x100u; t(*d,2).owner = 0; d->techs[46].knownMask = 0;
    d->raceStats.v[53][0] = -7; out = pay(*d,req,report);
    require(report.transportQuote == 0 && report.creditsAfter == 50 && !report.failureMask,"negative racial transport modifier clamps finalfee0");
    d->players[0].race = -1; d->raceStats.v[52][6] = 1; out = pay(*d,req,report);
    require(report.transportQuote == 30,"signed race-1 addresses preceding row52[6], not a guessed default race");
}

void cachedSupplierAndPartialCollection() {
    auto d = fixture(); adjacent(*d,1,2); adjacent(*d,1,3);
    t(*d,2).materials[3] = t(*d,3).materials[3] = 20; d->players[0].credits = 150;
    auto req = requirements(*d,1); auto ctx = context(); ctx.collection.suppliers[1] = {3,7};
    ConstructionPaymentReport report; auto out = pay(*d,req,report,ctx);
    require(!report.failureMask && report.transportQuote == 70 && report.creditsAfter == 30 &&
            t(*out,2).materials[3] == 20 && t(*out,3).materials[3] == 10,
            "valid cached donor/fee precedes cheaper earlier territory, even without rerunning routes");
    d->techs[46].knownMask = 1; d->players[0].credits = 50;
    out = pay(*d,req,report);
    require(report.requirementsAccepted && report.collectionAttempted && report.transportQuote == 0 && report.failureMask == 8 &&
            report.paid[0] == 50 && report.paid[3] == 0 && report.creditsAfter == 0 && t(*out,2).materials[3] == 20,
            "zero-fee transport still caps by credits: accepted quote can fail after basecost spent, with partialpayment retained");
    require(report.importFailures.empty(),"quantity0 after affordability is NOT a route-failure event");
    d->players[0].credits = 0; req.materials[0] = 0; out = pay(*d,req,report);
    require(report.failureMask == 0x2000 && !report.collectionAttempted,"zero credits cannot quote even freeimports");
    d->techs[46].knownMask = 0; d->players[0].credits = 100000; t(*d,2).materials[3] = 20000;
    t(*d,3).materials[3] = 0; req.materials[3] = 20000; out = pay(*d,req,report);
    require(report.transportQuote == 40000 && report.requirementsAccepted && report.failureMask == 8 && report.paid[3] == 10000 &&
            report.creditsAfter == 80000 && t(*out,2).materials[3] == 10000 && t(*out,1).materials[3] == 0,
            "quote doesn't grow destinationstock; actual imports cap10000 and return faithfully partialcollection");
}

void metalAndSignedDomains() {
    auto d = fixture(); ConstructionRequirements req; req.materials[4] = 1;
    t(*d,1).materials[7] = 1; t(*d,1).materials[4] = 100; ConstructionPaymentReport report;
    auto out = pay(*d,req,report);
    require(!report.failureMask && report.paid[7] == 1 && report.paid[4] == 0 && t(*out,1).materials[4] == 100 &&
            t(*out,1).materials[7] == 0,"00472282 repeatedlysubtracts same metal stock; cost1 consumes1Triidium despite100Iron");
    d = fixture(); adjacent(*d,1,2); t(*d,2).materials[7] = 2; req.materials[4] = 15;
    out = pay(*d,req,report);
    require(!report.failureMask && report.transportQuote == 4 && report.paid[7] == 2 && report.paid[4] == 0 &&
            report.creditsAfter == 96 && t(*out,2).materials[7] == 0,"metal importceil(15/10)=2Triidium charged2units*fee2, not15metalunits");
    d = fixture(); t(*d,1).materials[3] = -3; req = {}; req.materials[3] = -2;
    //Quote sees -3<-2 and requests1 from a nonexistent supplier: diagnostic
    //only includes positive requirements, so no woodbit is synthesized.
    out = pay(*d,req,report);
    require(report.failureMask == 0x2000 && report.paid[3] == 0,"negative requirements use original comparisons, no invented stock clamp");
    d = fixture(); req = {}; req.technology = 20; d->players[0].index = 31;
    d->techs[20].knownMask = 0x8000; out = pay(*d,req,report);
    require(!report.failureMask,"signed16 tech mask allows Player.index31 via signextension");
    d->techs[20].knownMask = 0x4000; out = pay(*d,req,report);
    require(report.failureMask == 0x1000,"positive known mask does not contain bit31");
    d->players[0].index = 0; req = {}; req.materials[0] = -1; d->players[0].credits = std::numeric_limits<int32_t>::max();
    out = pay(*d,req,report);
    require(!report.failureMask && report.creditsAfter == std::numeric_limits<int32_t>::min(),"defined32-bitwrap on signed credit subtraction");
    req = {}; req.materials[5] = 2; t(*d,1).materials[5] = 2; out = pay(*d,req,report);
    require(!report.failureMask && report.paid[5] == 0 && t(*out,1).materials[5] == 2,
            "original illegal direct steel request prints diagnostic but doesnot debit or invent a failure bit");
}

void failuresAndIsolation() {
    auto d = fixture(); adjacent(*d,1,2); t(*d,2).materials[3] = 20;
    auto req = requirements(*d,1); auto ctx = context(); ConstructionPaymentReport report;
    auto out = pay(*d,req,report); const auto expected = snapshot(*out), input = snapshot(*d); const auto old = report;
    const auto fails = [&](const save::Document& source,const ConstructionRequirements& r,const ConstructionPaymentContext& c) {
        save::Error error;
        require(!payConstructionRequirements(source,1,r,c,*out,report,error) && error.code != save::ErrorCode::None &&
                !error.message.empty() && report == old && snapshot(*out) == expected,"domain/resource error rolls back BOTH outputs");
    };
    auto badContext = ctx; badContext.selectedTerritory = 99; fails(*d,req,badContext);
    badContext = ctx; badContext.collection.suppliers[1] = {99,2}; fails(*d,req,badContext);
    badContext = ctx; badContext.collection.transfers.resize(251); fails(*d,req,badContext);
    badContext = ctx; badContext.collection.transfers.assign(250,{2,1,1,1,1}); fails(*d,req,badContext); //late newwoodlog251.
    auto badReq = req; badReq.technology = 48; fails(*d,badReq,ctx);
    badReq = {}; badReq.materials[4] = std::numeric_limits<int32_t>::max(); fails(*d,badReq,ctx);
    auto bad = std::make_unique<save::Document>(*d); bad->players[0].race = 127; fails(*bad,req,ctx);
    bad = std::make_unique<save::Document>(*d); t(*bad,3).owner = 7; fails(*bad,req,ctx);
    bad = std::make_unique<save::Document>(*d); t(*bad,1).adjacency[6] = 0x8000; fails(*bad,req,ctx);
    bad = std::make_unique<save::Document>(*d); t(*bad,1).owner = -1; fails(*bad,req,ctx);
    ConstructionRequirements prior = req; save::Error error;
    require(!buildingConstructionRequirements(*d,1,48,prior,error) && prior == req,"requirements failure preserves previousresult");
    require(!buildingConstructionRequirements(*d,0,1,prior,error) && prior == req,"nulltarget requirements rejected transactionally");
    //Native globals and global RNG must remain completely untouched.
    std::vector<uint8_t> gb(sizeof(gs)), gl(sizeof(gg)); std::memcpy(gb.data(),&gs,sizeof(gs)); std::memcpy(gl.data(),&gg,sizeof(gg));
    const auto low = rtl::seed(), high = rtl::seedHi();
    auto repeat = pay(*d,req,report); require(report == old && snapshot(*repeat) == expected,"deterministic payment including scratch/ledger");
    auto alias = std::make_unique<save::Document>(*d);
    require(payConstructionRequirements(*alias,1,req,ctx,*alias,report,error) && report == old && snapshot(*alias) == expected,
            "source/destination alias uses a private candidate");
    fails(*d,badReq,ctx);
    require(std::memcmp(gb.data(),&gs,sizeof(gs)) == 0 && std::memcmp(gl.data(),&gg,sizeof(gg)) == 0 &&
            rtl::seed() == low && rtl::seedHi() == high && snapshot(*d) == input,"no global state or input mutation on success/failure");
}

void corpus(const std::filesystem::path& directory) {
    namespace fs = std::filesystem;
    if (directory.empty()) { std::cout << "construction payment optional corpus: no directory\n"; return; }
    size_t count = 0;
    const auto inspect = [&](const save::Document& d) {
        uint32_t territory = 0;
        for (const auto& record : d.territories) if (record.data.owner >= 0 && record.data.owner < 7) { territory = record.data.index; break; }
        if (!territory) return;
        const auto before = snapshot(d); save::Error error;
        for (int type = 1; type < 48; ++type) {
            ConstructionRequirements req;
            if (!buildingConstructionRequirements(d,territory,type,req,error)) throw std::runtime_error(error.message);
            require(req.labor == int16_t(data::kBuildingTypes[type].buildLabor),"corpus allbuilding work requirements preserve signedtableword");
        }
        require(snapshot(d) == before,"corpus47costqueries remain readonly"); ++count;
    };
    for (const char* relative : {"TUTORIAL.SAV","Saves/AUTOSAVE.SAV","Campaign/AUTOSAVE.CPN","Campaign/ChCht001.CPN"}) {
        if (!fs::is_regular_file(directory/relative)) continue;
        auto d = std::make_unique<save::Document>(); save::Error error;
        if (!save::readDocument(directory/relative,*d,error)) throw std::runtime_error(error.message);
        inspect(*d);
    }
    if (fs::is_regular_file(directory/"LEVELS.HDX") && fs::is_regular_file(directory/"LEVELS.HDD")) {
        HdxArchive archive; std::string why;
        if (!archive.open((directory/"LEVELS").string(),&why)) throw std::runtime_error(why);
        for (const auto& entry : archive.entries()) {
            auto d = std::make_unique<save::Document>(); save::Error error;
            if (!save::readScenario(directory/"LEVELS",entry.name,*d,error)) throw std::runtime_error(error.message);
            inspect(*d);
        }
    }
    std::cout << "construction payment optional corpus: " << count << " documents,47costqueries each\n";
}
} // namespace
int main(int argc,char** argv) {
    try {
        costAndLocalOracles(); ordinaryImportsAndMasks(); routesAndTechnology(); cachedSupplierAndPartialCollection();
        metalAndSignedDomains(); failuresAndIsolation(); corpus(argc>1?std::filesystem::path(argv[1]):std::filesystem::path{});
        std::cout << "construction_payment: costs/imports/routes/metals/partialpayment oracles, rollback and isolation passed\n"; return 0;
    } catch (const std::exception& e) { std::cerr << "construction_payment: " << e.what() << '\n'; return 1; }
}
