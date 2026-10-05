#include "game/combat_defense.h"
#include "game/combat_creation_tables.h"
#include "game/data_tables.h"
#include <algorithm>
#include <bit>
#include <new>
#include <stdexcept>
#include <utility>

namespace dl2::simulation {
namespace {
bool fail(save::Error& e,const char* message,save::ErrorCode code = save::ErrorCode::InvalidState) {
    e = {code,0,message}; return false;
}
int32_t signed32(uint32_t v) { return std::bit_cast<int32_t>(v); }
} // namespace

bool rebuildCombatDefense(const save::Document& d,const CombatPreparationState& before,
                          CombatDefenseReport& report,save::Error& e) try {
    if (!save::validate(d,e)) return false;
    if (d.header.isMap) return fail(e,"Combat defense requires a full saved-game document");
    if (before.warriors.size() != kCombatWarriorCapacity ||
        before.structures.size() != kCombatStructureCapacity || before.battles.size() != kCombatBattleCapacity)
        return fail(e,"Combat defense requires the physical840/1200/32 pool shapes");
    if (!before.currentBattle || before.currentBattle->index >= before.battles.size())
        return fail(e,"Combat defense requires a represented selected Battle");
    CombatDefenseReport result; result.after = before;
    result.after.grid.penalty.fill(0);
    std::array<bool,kCombatWarriorCapacity> visited{};
    auto next = before.battles[before.currentBattle->index].core.first;
    while (next) {
        const size_t index = next->index;
        if (index >= before.warriors.size()) return fail(e,"Combat defense reached an invalid Warrior reference");
        if (visited[index]) return fail(e,"Combat defense Warrior chain contains a cycle");
        visited[index] = true;
        const auto& w = before.warriors[index]; next = w.next;
        if (!w.active) continue; // The type is not read on this branch.
        if (w.type < 0 || w.type >= data::kNumUnitTypes)
            return fail(e,"Combat defense reached an invalid active Warrior type");
        const auto& def = data::kUnitTypes[w.type];
        if (def.unitClass != 10) continue;
        // Specialize004480a8 for class10: no type15 command bonus or class1
        // order bonus is possible. It reads no owner, race, skill or target.
        // Calling the broader stats API would unnecessarily restrict owners.
        const int32_t range = std::max<int32_t>(def.range,0);
        CombatDefenseSource source{{index},range,{}};
        const int32_t left = signed32(uint32_t(w.currentX)-uint32_t(range));
        const int32_t right = signed32(uint32_t(w.currentX)+uint32_t(range));
        const int32_t top = signed32(uint32_t(w.currentY)-uint32_t(range));
        const int32_t bottom = signed32(uint32_t(w.currentY)+uint32_t(range));
        // Intersect the native half-open loops with004511a4's physical bounds.
        // The discarded iterations cannot write or consume randomness.
        for (int32_t y = std::max(top,-9); y < std::min(bottom,27); ++y) {
            for (int32_t x = std::max(left,-9); x < std::min(right,27); ++x) {
                const size_t cell = size_t((y+9)*36+x+9);
                if (!combat_creation_tables::kValidCells[cell]) continue;
                const uint32_t dx = uint32_t(w.currentX)-uint32_t(x);
                const uint32_t dy = uint32_t(w.currentY)-uint32_t(y);
                if (signed32(dx*dx+dy*dy) < range) {
                    auto& penalty = result.after.grid.penalty[cell];
                    penalty = uint8_t(uint32_t(penalty)+10u);
                    source.cells.push_back(cell);
                }
            }
        }
        result.sources.push_back(std::move(source));
    }
    report = std::move(result); e = {}; return true;
} catch (const std::bad_alloc&) { return fail(e,"Combat defense allocation failed",save::ErrorCode::Limit);
} catch (const std::length_error&) { return fail(e,"Combat defense allocation exceeds limits",save::ErrorCode::Limit); }
} // namespace dl2::simulation
