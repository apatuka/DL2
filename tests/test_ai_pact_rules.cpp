// Decompilation/assembly-derived pact-rule cases, not an executed-game oracle.
#include "game/ai_pact_rules.h"
#include "game/globals.h"
#include "game/rtl_compat.h"
#include <bit>
#include <cstring>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>
#include <vector>

namespace {
using namespace dl2;
using namespace dl2::simulation;
void require(bool condition,const char* message) {
    if (!condition) throw std::runtime_error(message);
}
std::unique_ptr<save::Document> fixture() {
    auto d = std::make_unique<save::Document>();
    std::memcpy(d->header.text,save::kHeaderText,sizeof(save::kHeaderText));
    d->header.version = kSaveVersion; d->header.minusOne = -1;
    d->options.numPlayers = 3; d->options.allowAlliances = 1;
    d->world.width = d->world.height = 1; d->world.numTerritories = 1;
    d->tiles.resize(1); d->tiles[0].territory = 1;
    d->territories.resize(1); d->territories[0].data.index = 1;
    for (int p = 0; p < kMaxPlayers; ++p) {
        d->players[size_t(p)].index = uint8_t(p);
        d->players[size_t(p)].type = p == 0 ? 1 : p < 3 ? 3 : 0;
        d->ministerJobs[size_t(p)].resize(1);
    }
    save::Error error; require(save::validate(*d,error),"invalid pact fixture"); return d;
}
std::vector<uint8_t> bytes(const save::Document& d) {
    std::vector<uint8_t> result; save::Error error;
    if (!save::encode(d,result,error)) throw std::runtime_error(error.message);
    return result;
}
void attitude(save::Document& d,int p,int other,int32_t value) {
    std::memcpy(reinterpret_cast<uint8_t*>(&d.scratchJob1) + size_t(p*7+other)*4,&value,4);
}
RngSnapshot seeded(uint32_t seed) {
    SessionRng rng; save::Error error;
    require(rng.initialize(seed,error),"cannot initialize pact RNG"); return rng.snapshot();
}
AiPactAssessmentReport assess(const save::Document& d,uint32_t mask,bool initiating = true,
                              const AiVictoryMetrics& metrics = {},uint32_t seed = 0) {
    AiPactAssessmentReport report; save::Error error;
    if (!assessAiPact(d,{1,2,mask,initiating},metrics,seeded(seed),report,error))
        throw std::runtime_error(error.message);
    return report;
}
void predicatesAndMetrics() {
    auto d = fixture(); auto& p = d->players[1];
    p.relations[2] = 0x80000011u; p.relations2[2] = 9;
    require(hasAiPact(*d,1,2,0x1e) && !hasAiPact(*d,1,2,1) &&
            !hasAiPact(*d,1,2,0x80000000u) && hasAiPact(*d,1,2,0),
            "alliance did not imply precisely bits1e");
    require(hasAiPact(*d,1,2,9,true) && !hasAiPact(*d,1,2,2,true),
            "primary and secondary relations conflated");
    require(!hasAiPact(*d,-1,2,0) && !hasAiPact(*d,1,7,0) && !hasAiPact(*d,1,3,0),
            "invalid or logical-end pact index accepted");
    d->options.allowAlliances = 0;
    require(!hasAiPact(*d,1,2,0),"disabled alliances allowed even empty request");
    AiVictoryMetrics metrics; metrics.cities = {1,11,12,13,14,15,16};
    metrics.territories = {2,21,22,23,24,25,26}; metrics.shrines = {3,31,32,33,34,35,36};
    require(aiVictoryMetric(*d,1,metrics) == 11,"city metric used a derived or saved score");
    d->options.victory = 1; require(aiVictoryMetric(*d,1,metrics) == 21,"territory metric mismatch");
    d->options.victory = 2; require(aiVictoryMetric(*d,1,metrics) == 31,"shrine metric mismatch");
    require(aiVictoryMetric(*d,3,metrics) == 0,"inactive player has metric");
    d->players[3].type = 255;
    require(aiVictoryMetric(*d,3,metrics) == 33,"strict original metric boundary changed");
    d->players[4].type = 3;
    require(aiVictoryMetric(*d,4,metrics) == 0 && aiVictoryMetric(*d,-1,metrics) == 0 &&
            aiVictoryMetric(*d,7,metrics) == 0,"unsafe or logical-outside metric address accepted");
    d->options.victory = 255;
    require(aiVictoryMetric(*d,1,metrics) == 0,"unknown victory invented a metric");
}
void assessmentSemantics() {
    auto d = fixture(); attitude(*d,1,2,25);
    const auto source = bytes(*d);
    const std::pair<uint32_t,int32_t> terms[]{{0,50},{1,50},{2,30},{8,40},{4,40},{16,20},{31,-20},{0x80000000u,50}};
    for (const auto [mask,threshold] : terms) {
        const auto r = assess(*d,mask);
        require(r.threshold == threshold && !r.warBlocked && r.accepted == (threshold > 0) &&
                r.draws.size() == 1 && r.draws[0].operation == RngOperation::Secondary15 &&
                r.draws[0].value == 0 && r.draws[0].consumed && r.rngAfter.secondary == 12345 &&
                r.rngAfter.counters.secondary15 == 1 && r.rngAfter.rtlLow == 0,
                "pact terms or exact secondary draw differs");
        require(assess(*d,mask,false).threshold == threshold+20,"recipient bonus missing");
    }
    require(bytes(*d) == source,"pact assessment changed source");
    const auto below = assess(*d,0,true,{},58),equal = assess(*d,0,true,{},27);
    require(below.draws[0].value%100 == 49 && below.accepted &&
            equal.draws[0].value%100 == 50 && !equal.accepted,
            "strict probability boundary changed");
    d->players[1].relations2[2] = 16;
    require(assess(*d,0).threshold == 50,"assessment used secondary relations");
    d->players[1].relations[2] = 15;
    require(assess(*d,0).threshold == 100,"existing individual treaty bonuses differ");
    d->players[1].relations[2] = 16;
    require(assess(*d,0).threshold == 70,"alliance effective terms or active-target penalty differ");
    d->players[1].relations[0] = 16;
    require(assess(*d,0).threshold == 50,"active human alliance penalty omitted");
    d->players[0].type = 0;
    require(assess(*d,0).threshold == 70,"inactive alliance still penalized");
    d->players[0].type = 255;
    require(assess(*d,0).threshold == 50,"nonzero signed-negative player skipped by active predicate");
    d->players[1].relations[1] = 16;
    require(assess(*d,0).threshold == 30,"self alliance excluded from original seven-slot scan");
    d->options.allowAlliances = 0;
    require(assess(*d,0).threshold == 50,"disabled alliances supplied bonuses or penalties");
    d->options.allowAlliances = 1;
    for (auto& player : d->players) for (auto& relation : player.relations) relation = 0;
    AiVictoryMetrics metrics; metrics.cities[1] = 2; metrics.cities[2] = 3;
    require(assess(*d,0,true,metrics).threshold == 60,"stronger target bonus inverted");
    metrics.cities[1] = 4;
    require(assess(*d,0,true,metrics).threshold == 40,"weaker target penalty inverted");
    metrics.cities[2] = 4;
    require(assess(*d,0,true,metrics).threshold == 50,"tied metric modified willingness");
    const std::pair<int32_t,int32_t> arithmetic[]{
        {INT32_MAX,-2},{INT32_MIN,0},{21474837,-42949671},{-21474837,42949671},{-1,-2},{51,102}
    };
    for (const auto [value,threshold] : arithmetic) {
        attitude(*d,1,2,value); const auto r = assess(*d,0,true,{},194);
        require(r.threshold == threshold && r.draws.size() == 1 && r.draws[0].value%100 == 99 &&
                r.accepted == (threshold > 99),"wrapping multiplication/division or extreme chance draw differs");
    }
}
void normalization() {
    auto d = fixture(); save::Error error; uint32_t result = 0;
    auto check = [&](uint32_t candidate,uint32_t expected) {
        const auto before = bytes(*d);
        error = {save::ErrorCode::Io,99,"old"};
        require(normalizeAiPactOffer(*d,1,2,candidate,result,error) && result == expected &&
                error.code == save::ErrorCode::None && bytes(*d) == before,"offer normalization differs or mutated source");
    };
    check(16,30); check(17,30); check(3,2); check(1,1); check(0x80000010u,0x8000001eu);
    d->players[1].relations[0] = 16; check(16,30);
    d->players[1].relations2[2] = 2; check(16,28); check(1,0);
    d->players[1].relations2[2] = 8; check(16,22);
    d->players[1].relations2[2] = 14; check(16,16);
    d->players[1].relations2[2] = 0;
    d->players[2].relations2[0] = 16; check(16,0); check(0x80000019u,0x80000009u);
    d->players[0].type = 0; check(16,30);
    d->players[0].type = 255; check(16,0);
    d->players[2].relations2[0] = 0; d->players[1].relations2[1] = 16; check(16,0);
    d->options.allowAlliances = 0; check(16,30); check(1,1);
}
void transactionsAndWar() {
    auto d = fixture(); d->aiWarMask[1] = 4; save::Error error;
    AiPactAssessmentReport result; result.accepted = true; result.threshold = 999;
    const auto source = bytes(*d);
    require(assessAiPact(*d,{1,2,31,true},{},{},result,error) && result.warBlocked && !result.accepted &&
            result.draws.empty() && result.rngAfter == RngSnapshot{},"war early return consumed or required initialized RNG");
    const auto kept = result;
    auto invalid = seeded(1); invalid.counters.operations = 1;
    require(!assessAiPact(*d,{1,2,0,true},{},invalid,result,error) && result == kept,
            "malformed RNG failed without retaining report");
    require(!assessAiPact(*d,{1,7,0,true},{},seeded(1),result,error) && result == kept,
            "invalid player did not reject transactionally");
    d->aiWarMask[1] = 0;
    require(!assessAiPact(*d,{1,2,0,true},{},{},result,error) && result == kept,
            "nonwar assessment invented RNG");
    auto exhausted = seeded(1); exhausted.counters.operations = exhausted.counters.secondary15 = UINT64_MAX;
    require(!assessAiPact(*d,{1,2,0,true},{},exhausted,result,error) && result == kept,
            "exhausted draw leaked report");
    d->aiWarMask[1] = 4;
    require(bytes(*d) == source,"failed assessment changed source");
    uint32_t output = 0xdeadbeef;
    require(!normalizeAiPactOffer(*d,-1,2,16,output,error) && output == 0xdeadbeef,
            "normalization invalid index changed output");
    d->header.text[0] = 0;
    require(!normalizeAiPactOffer(*d,1,2,16,output,error) && output == 0xdeadbeef &&
            !assessAiPact(*d,{1,2,0,true},{},seeded(1),result,error) && result == kept,
            "invalid document accepted or changed output");
}
} // namespace
int main() {
    try {
        rtl::srand(0xf1234567u); (void)rtl::lrand(); gg.rng2Seed = 0xabcd0123;
        const auto low = rtl::seed(),high = rtl::seedHi();
        const auto globals = std::make_unique<GameGlobals>(gg); const auto game = std::make_unique<GameState>(gs);
        predicatesAndMetrics(); assessmentSemantics(); normalization(); transactionsAndWar();
        require(rtl::seed() == low && rtl::seedHi() == high && std::memcmp(&gg,globals.get(),sizeof(gg)) == 0 &&
                std::memcmp(&gs,game.get(),sizeof(gs)) == 0,"pact helpers changed globals or RNG");
        std::cout << "AI pact rule tests passed\n"; return 0;
    } catch (const std::exception& exception) {
        std::cerr << "AI pact rules: " << exception.what() << '\n'; return 1;
    }
}
