#include "game/session_rng.h"
#include "game/save_files.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include <algorithm>
#include <array>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
using namespace dl2;
using namespace dl2::simulation;
namespace fs = std::filesystem;
void require(bool value, const char* message) {
    if (!value) throw std::runtime_error(message);
}
void cleared(const save::Error& error) {
    require(error.code == save::ErrorCode::None && error.offset == 0 && error.message.empty(), "success must clear RNG error");
}
RngEvent sentinel() {
    return {99, RngOperation::TaggedRange, -11, 0xabcdef12u, 83, "previous result", true};
}
void initialize(SessionRng& rng, uint32_t seed) {
    save::Error error{save::ErrorCode::Io, 123, "old error"};
    require(rng.initialize(seed, error), "explicit RNG initialization failed");
    cleared(error);
    require(rng.snapshot().initialized && rng.snapshot().rtlLow == seed && rng.snapshot().rtlHigh == 0 &&
            rng.snapshot().secondary == seed && rng.snapshot().counters == RngCounters{}, "initial seeds or counters differ");
}
RngEvent apply(SessionRng& rng, RngOperation operation, int32_t bound = 0, uint32_t seed = 0,
               std::string_view tag = "test") {
    auto event = sentinel(); save::Error error{save::ErrorCode::Io, 42, "old"};
    require(rng.apply({operation, bound, seed, tag}, event, error), "valid RNG request rejected");
    cleared(error);
    require(event.operation == operation && event.bound == bound && event.seed == seed && event.tag == tag &&
            event.ordinal == rng.snapshot().counters.operations, "RNG event metadata differs from request");
    return event;
}
void reject(SessionRng& rng, const RngRequest& request) {
    const auto before = rng.snapshot(); auto event = sentinel(); const auto oldEvent = event;
    save::Error error;
    require(!rng.apply(request, event, error), "invalid RNG request succeeded");
    require(error.code != save::ErrorCode::None && !error.message.empty(), "RNG rejection lacks diagnostic");
    require(rng.snapshot() == before && event == oldEvent, "failed RNG operation changed state or output");
}
void rejectSnapshot(SessionRng& rng, const RngSnapshot& snapshot) {
    const auto before = rng.snapshot(); save::Error error;
    require(!rng.restore(snapshot, error) && error.code != save::ErrorCode::None && !error.message.empty(),
            "invalid snapshot must fail with a diagnostic");
    require(rng.snapshot() == before, "invalid snapshot changed RNG state");
}

void goldenSequences() {
    // Independent fixed recurrence vectors, not equality between two port runs.
    constexpr uint32_t randExpected[]{346,130,10982,1090,11656,7117,17595,6415};
    constexpr uint32_t longExpected[]{346,13854878,1621890440,816282396,1778554774,821126358,1407482132,991758756};
    constexpr uint32_t secondaryExpected[]{16838,5758,10113,17515,31051,5627,23010,7419};
    SessionRng rng;
    initialize(rng, 1);
    for (const auto expected : randExpected) require(apply(rng, RngOperation::Rand15).value == expected, "rand15 golden mismatch");
    require(rng.snapshot().rtlHigh == 0 && rng.snapshot().secondary == 1 && rng.snapshot().counters.rand15 == 8,
            "rand15 changed independent state");
    initialize(rng, 1);
    for (const auto expected : longExpected) require(apply(rng, RngOperation::Long31).value == expected, "long31 golden mismatch");
    require(rng.snapshot().rtlLow == 1558657561u && rng.snapshot().rtlHigh == 991758756u &&
            rng.snapshot().secondary == 1 && rng.snapshot().counters.long31 == 8, "long31 final state mismatch");
    initialize(rng, 1);
    for (const auto expected : secondaryExpected)
        require(apply(rng, RngOperation::Secondary15).value == expected, "secondary15 golden mismatch");
    require(rng.snapshot().rtlLow == 1 && rng.snapshot().rtlHigh == 0 && rng.snapshot().secondary == 2633739833u &&
            rng.snapshot().counters.secondary15 == 8, "secondary generator changed RTL or final state");
}

void mixedOrderAndSnapshots() {
    struct Step { RngOperation operation; int32_t bound; uint32_t seed, value, low, high, secondary; };
    // Low-product/high-product/carry arithmetic evaluated independently for
    // this specific mixed call order. rand15 MUST preserve long31's high word.
    const Step steps[]{
        {RngOperation::Long31,0,0,346,0x00004e36u,0x0000015au,0x00000001u},
        {RngOperation::Rand15,0,0,19680,0xcce0a52fu,0x0000015au,0x00000001u},
        {RngOperation::Secondary15,0,0,16838,0xcce0a52fu,0x0000015au,0x41c67ea6u},
        {RngOperation::TaggedRange,7,0,5,0xdcd684bcu,0xe80933beu,0x41c67ea6u},
        {RngOperation::Rand15,0,0,31474,0x7af2c2edu,0xe80933beu,0x41c67ea6u},
        {RngOperation::TaggedRange,-7,0,6,0x6ba69112u,0x03c73437u,0x41c67ea6u},
        {RngOperation::TaggedRange,0,0,0,0x6ba69112u,0x03c73437u,0x41c67ea6u},
        {RngOperation::SeedRtl,0,0x89abcdefu,0,0x89abcdefu,0,0x41c67ea6u},
        {RngOperation::Long31,0,0,305430292,0xd950747cu,0x12347f14u,0x41c67ea6u},
        {RngOperation::SeedSecondary,0,0xffffffffu,0,0xd950747cu,0x12347f14u,0xffffffffu},
        {RngOperation::Secondary15,0,0,15929,0xd950747cu,0x12347f14u,0xbe39e1ccu},
        {RngOperation::SeedBoth,0,1234,0,0x000004d2u,0,0x000004d2u},
        {RngOperation::Long31,0,0,426964,0x0178fb7bu,0x000683d4u,0x000004d2u},
        {RngOperation::Rand15,0,0,3817,0x0ee98a78u,0x000683d4u,0x000004d2u},
        {RngOperation::Long31,0,0,623447458,0x3e8a3ad9u,0x25290da2u,0x000004d2u}
    };
    SessionRng rng; initialize(rng, 1);
    std::vector<RngEvent> events;
    RngSnapshot halfway;
    for (size_t i = 0; i < std::size(steps); ++i) {
        const auto& step = steps[i];
        auto event = apply(rng, step.operation, step.bound, step.seed, "mixed");
        const auto current = rng.snapshot();
        require(event.value == step.value && event.ordinal == i + 1 && current.rtlLow == step.low &&
                current.rtlHigh == step.high && current.secondary == step.secondary, "mixed RNG order golden mismatch");
        const bool consumes = step.operation == RngOperation::Rand15 || step.operation == RngOperation::Long31 ||
            step.operation == RngOperation::Secondary15 || (step.operation == RngOperation::TaggedRange && step.bound != 0);
        require(event.consumed == consumes, "RNG consumption report differs");
        events.push_back(event);
        if (i == 6) halfway = current;
    }
    const RngCounters expected{15,3,6,2,3,1,1,1,1};
    require(rng.snapshot().counters == expected, "mixed primitive, zero-range and seed counters differ");
    const auto final = rng.snapshot();
    SessionRng restored; save::Error error;
    require(restored.restore(halfway, error), "restore mixed snapshot failed"); cleared(error);
    for (size_t i = 7; i < std::size(steps); ++i)
        require(apply(restored, steps[i].operation, steps[i].bound, steps[i].seed, "mixed") == events[i],
                "snapshot did not restore complete sequence and ordinals");
    require(restored.snapshot() == final, "snapshot restored only part of RNG state");
    auto independent = restored;
    apply(restored, RngOperation::Rand15);
    require(independent.snapshot() == final, "copying session RNG aliases mutable state");
}

void boundsTagsAndErrors() {
    SessionRng rng;
    reject(rng, {RngOperation::Rand15});
    reject(rng, {RngOperation::SeedBoth,0,123}); // Seeding after construction is explicit initialize().
    initialize(rng, 1);
    const auto zero = apply(rng, RngOperation::TaggedRange, 0);
    require(!zero.consumed && zero.value == 0 && rng.snapshot().rtlLow == 1 && rng.snapshot().rtlHigh == 0,
            "zero range consumed RNG");
    require(apply(rng, RngOperation::TaggedRange,-7).value == 3, "negative tagged bound differs from signed remainder");
    initialize(rng, 1);
    require(apply(rng, RngOperation::TaggedRange,std::numeric_limits<int32_t>::min()).value == 346,
            "INT_MIN range must preserve nonnegative signed remainder");
    initialize(rng, 1);
    require(apply(rng, RngOperation::TaggedRange,-1).value == 0 && rng.snapshot().counters.long31 == 1,
            "unit bound must still consume RNG");
    initialize(rng, 1);
    require(apply(rng, RngOperation::TaggedRange,std::numeric_limits<int32_t>::max()).value == 346, "maximum bound differs");
    SessionRng other; initialize(rng,0xffffffffu); initialize(other,0xffffffffu);
    std::string tag("a\0b",3);
    auto tagged = apply(rng,RngOperation::TaggedRange,100,0,tag);
    const auto differentlyTagged = apply(other,RngOperation::TaggedRange,100,0,"different tag");
    tag.assign("changed");
    require(tagged.tag == std::string("a\0b",3) && tagged.value == differentlyTagged.value &&
            rng.snapshot() == other.snapshot(), "diagnostic tag changed RNG or retained borrowed memory");
    const std::string longest(kMaxRngTagBytes,'x'); apply(rng,RngOperation::Rand15,0,0,longest);
    const std::string tooLong(kMaxRngTagBytes+1,'x');
    reject(rng,{RngOperation::Rand15,0,0,tooLong});
    reject(rng,{static_cast<RngOperation>(999)});
    reject(rng,{RngOperation::Rand15,1});
    reject(rng,{RngOperation::Long31,0,1});
    reject(rng,{RngOperation::SeedBoth,1,7});
    auto bad = rng.snapshot(); bad.format = 2; rejectSnapshot(rng,bad);
    bad = rng.snapshot(); bad.counters.operations++; rejectSnapshot(rng,bad);
    bad = rng.snapshot(); bad.counters.zeroRanges = bad.counters.taggedRange + 1; rejectSnapshot(rng,bad);
    bad = rng.snapshot(); bad.counters.taggedRange = bad.counters.long31 + bad.counters.zeroRanges + 1; rejectSnapshot(rng,bad);
    bad = RngSnapshot{}; bad.rtlLow=1; rejectSnapshot(rng,bad);
    bad = rng.snapshot(); bad.initialized=false; rejectSnapshot(rng,bad);
    bad = RngSnapshot{}; bad.initialized=true;
    bad.counters.operations = bad.counters.rand15 = std::numeric_limits<uint64_t>::max();
    save::Error error;
    require(rng.restore(bad,error), "consistent exhausted counter snapshot should be restorable");
    reject(rng,{RngOperation::Rand15}); reject(rng,{RngOperation::TaggedRange}); reject(rng,{RngOperation::SeedBoth,0,9});
    bad.counters.long31=1; rejectSnapshot(rng,bad); // Sum overflows instead of wrapping.
    require(rng.restore(RngSnapshot{},error) && rng.snapshot() == RngSnapshot{}, "canonical empty snapshot restoration failed");
    reject(rng,{RngOperation::Long31});
    initialize(rng,0); require(apply(rng,RngOperation::Long31).value == 0 && rng.snapshot().rtlLow == 1,
                              "zero is a valid seed, not an absent seed");
}

std::unique_ptr<save::Document> fixture() {
    auto d=std::make_unique<save::Document>();
    std::memcpy(d->header.text,save::kHeaderText,sizeof(save::kHeaderText));
    d->header.version=kSaveVersion; d->options.numPlayers=1;
    d->world.width=d->world.height=1; d->world.numTerritories=1;
    d->territories.resize(1); d->territories[0].data.index=1; d->territories[0].data.owner=0;
    d->tiles.resize(1); d->tiles[0].territory=1;
    for(auto& jobs:d->ministerJobs) { jobs.resize(1); jobs[0].type=1; }
    return d;
}
std::vector<uint8_t> encoded(const save::Document& d) {
    std::vector<uint8_t> bytes; save::Error error;
    if(!save::encode(d,bytes,error)) throw std::runtime_error(error.message);
    return bytes;
}
void legacyLoadSeeds() {
    auto d=fixture(); d->options.gameId=-123; d->options.gameSeed=0xabcdef12u;
    d->world.rngSeed=0x98765432u; d->world.seed1=0x45678901u;
    SessionRng rng; initialize(rng,77); apply(rng,RngOperation::Long31);
    save::Error error;
    for(const uint32_t version:{35u,36u,0x120u}) {
        d->header.version=version;
        const auto original=encoded(*d);
        require(rng.initializeAfterLegacyLoad(*d,error), "legacy-load final reseed failed"); cleared(error);
        const auto s=rng.snapshot();
        require(s.initialized && s.rtlLow==uint32_t(-123) && s.rtlHigh==0 && s.secondary==uint32_t(-123) &&
                s.counters==RngCounters{}, "legacy load used wrong seed or manufactured prior draw counters");
        require(encoded(*d)==original, "RNG initialization edited archival document");
    }
    const auto before=rng.snapshot();
    d->header.version=34;
    require(!rng.initializeAfterLegacyLoad(*d,error) && rng.snapshot()==before, "unsupported load version altered RNG");
    d->header.version=kSaveVersion; d->header.isMap=1; d->mapTerritories.resize(1);
    require(!rng.initializeAfterLegacyLoad(*d,error) && rng.snapshot()==before, "map seed was accepted as saved-game RNG");
    d->header.isMap=0; d->world.width=0;
    require(!rng.initializeAfterLegacyLoad(*d,error) && rng.snapshot()==before, "invalid document changed RNG");
}

std::vector<std::string> scenarioNames(const fs::path& path) {
    const auto size=fs::file_size(path);
    require(size>=4 && size<=save::kMaxFileBytes,"invalid corpus index size");
    std::ifstream in(path,std::ios::binary); uint8_t b[4]{};
    require(bool(in.read(reinterpret_cast<char*>(b),4)),"cannot read corpus index");
    const uint32_t count=uint32_t(b[0])|(uint32_t(b[1])<<8)|(uint32_t(b[2])<<16)|(uint32_t(b[3])<<24);
    require(count<=(size-4)/12,"truncated corpus index");
    std::vector<std::string> names;
    for(uint32_t i=0;i<count;++i) {
        char entry[12]{}; require(bool(in.read(entry,12)),"cannot read corpus index entry");
        names.emplace_back(entry,std::find(entry,entry+8,'\0'));
    }
    return names;
}
void corpusOne(const save::Document& d) {
    const auto before=encoded(d);
    SessionRng loaded,explicitSeed; save::Error error;
    if(!loaded.initializeAfterLegacyLoad(d,error)) throw std::runtime_error(error.message);
    initialize(explicitSeed,uint32_t(d.options.gameId));
    require(loaded.snapshot()==explicitSeed.snapshot(),"corpus load seed differs from saved gameId");
    for(int i=0;i<16;++i)
        require(apply(loaded,RngOperation::Long31)==apply(explicitSeed,RngOperation::Long31),"corpus explicit seeding differs");
    require(encoded(d)==before,"corpus document changed during RNG operations");
}
void optionalCorpus(const fs::path& directory) {
    if(directory.empty() || !fs::is_regular_file(directory/"TUTORIAL.SAV")) {
        std::cout<<"session RNG: optional corpus unavailable; synthetic tests ran\n"; return;
    }
    size_t count=0;
    for(const char* name:{"TUTORIAL.SAV","Saves/AUTOSAVE.SAV","Campaign/AUTOSAVE.CPN","Campaign/ChCht001.CPN"}) {
        if(!fs::is_regular_file(directory/name)) continue;
        auto d=std::make_unique<save::Document>(); save::Error error;
        if(!save::readDocument(directory/name,*d,error)) throw std::runtime_error(error.message);
        corpusOne(*d); ++count;
    }
    if(fs::is_regular_file(directory/"LEVELS.HDX") && fs::is_regular_file(directory/"LEVELS.HDD"))
        for(const auto& name:scenarioNames(directory/"LEVELS.HDX")) {
            auto d=std::make_unique<save::Document>(); save::Error error;
            if(!save::readScenario(directory/"LEVELS",name,*d,error)) throw std::runtime_error(error.message);
            corpusOne(*d); ++count;
        }
    std::cout<<"session RNG corpus: "<<count<<" gameId initializations, source bytes preserved\n";
}
} // namespace

int main(int argc,char** argv) {
    try {
        // Module operations never read or mutate either legacy RNG or gs/gg.
        rtl::srand(0x19384756u); (void)rtl::lrand();
        const auto low=rtl::seed(), high=rtl::seedHi();
        gg.rng2Seed=0xf1234567u;
        const auto globals=std::make_unique<GameGlobals>(gg);
        const auto game=std::make_unique<GameState>(gs);
        goldenSequences(); mixedOrderAndSnapshots(); boundsTagsAndErrors(); legacyLoadSeeds();
        optionalCorpus(argc>1 ? fs::path(argv[1]) : fs::path{});
        require(rtl::seed()==low && rtl::seedHi()==high,"owned RNG touched global Borland state");
        require(std::memcmp(&gg,globals.get(),sizeof(gg))==0 && std::memcmp(&gs,game.get(),sizeof(gs))==0,
                "owned RNG touched legacy game globals");
        std::cout<<"session RNG tests passed\n"; return 0;
    } catch(const std::exception& exception) {
        std::cerr<<"session RNG: "<<exception.what()<<'\n'; return 1;
    }
}
