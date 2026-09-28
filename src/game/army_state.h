// Semantic, read-only access to legacy Army records in save::Document.
// Physical field names stay unchanged for ABI and parser compatibility.
#pragma once
#include "game/game_state.h"

namespace dl2::army {

// File territory indices, NOT globals.h handles or native pointers. Resolve
// against Document::territoryByIndex; do not use these on activated raw records.
// ReLinkArmy (00445898) stores the linked/current territory at +0x3c;
// MoveUnit (00446084) spends movement from +0x38, retained until the turn reset
// (004471c0) copies current into both +0x38 and +0x40.
constexpr uint32_t current(const Army& value) { return value.dest.raw; }
constexpr uint32_t turnStart(const Army& value) { return value.territory.raw; }
// MoveUnit's third argument: route origin/friendly anchor chosen by 00401ac0,
// or the new current territory when that argument is null. Not always previous.
constexpr uint32_t routeOrigin(const Army& value) { return value.origin.raw; }

// Base moves from 00447190; MoveUnit writes remaining movement to +0x0a.
constexpr uint8_t movementPoints(const Army& value) { return value.strength; }
// Orders UI 00417c00 writes 0/25/50/75/100 to +0x26. This is a retreat
// threshold (percentage of defense lost), not remaining health.
constexpr uint8_t retreatThreshold(const Army& value) { return value.health; }
// 00447a68 copies +0x24 into the Warrior's combat-order field.
constexpr uint8_t combatOrders(const Army& value) { return value.moves; }

static_assert(offsetof(Army, strength) == 0x0a);
static_assert(offsetof(Army, moves) == 0x24);
static_assert(offsetof(Army, health) == 0x26);
static_assert(offsetof(Army, territory) == 0x38);
static_assert(offsetof(Army, dest) == 0x3c);
static_assert(offsetof(Army, origin) == 0x40);

} // namespace dl2::army
