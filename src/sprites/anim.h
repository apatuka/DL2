// anim.h - the ANIM system of DEADLOCK.EXE (sprite objects with z-ordered draw list, parent linkage,
// position in 24.8 fixed point, velocity and a small script interpreter driving the frame sequence).
//
// Original data: 150 (0x96) objects of 64 bytes at DAT_00561a34; active list head DAT_00561a30, tail
// DAT_00563fb4, free list head DAT_00563fb8; dirty rectangle DAT_00561a20..2c; drawn list DAT_00563fbc
// with count DAT_004c50a8.
//
// Object layout (offsets in the original, kept as field comments):
//   +0x00 u16 flags     bit 2 (0x04) active/animating, bit 3 (0x08) hit-testable with bit 2, bit 4 (0x10) has parent
//   +0x02 i16 type      sprite type (index into the type table 0x004D02F4)
//   +0x04 i16 z         draw order (ascending)
//   +0x06 i32 x, +0x0a i32 y   position, 24.8 fixed point
//   +0x0e i16 sx, +0x10 i16 sy  screen position of the last draw (x >> 8 + hotX)
//   +0x12 i16 w, +0x14 i16 h
//   +0x16 SpriteDef* frame, +0x1a SpriteDef* frames (table of the type)
//   +0x1e i16 timer, +0x20 i16 rate
//   +0x22 i16 dx, +0x24 i16 dy  velocity per tick (24.8)
//   +0x2a i16 moveDelay  ticks before the velocity applies
//   +0x2c i16 var[4]     script variables: 0 = state, 1 = aux, 2 = facing (children restart when the
//                        parent's changes), 3 = parent object index (self on creation)
//   +0x34 u16* pc        script pointer, +0x38 next, +0x3c prev
//
// Functions: FUN_00444e88 Reset, FUN_00444a00 Alloc, FUN_00444abc IsActive, FUN_00444ae4 Free
// ("Freeing an invalid ANIM."), FUN_00444b74 SetZ, FUN_00444f20 Create, FUN_00444fd4 Kill,
// FUN_00445040 SetState, FUN_00445074 AddDirtyRect, FUN_004450e0 ResetDirtyRect, FUN_00445100 HitTest,
// FUN_00445190 DrawUpTo, FUN_004451cc ResetDrawnList, FUN_004451d4 SetFrame, FUN_00445270 Update,
// FUN_00444e70 ScriptTableJump, DrawSprite FUN_00444cf4, FUN_0046ca40 Random (LCG of DAT_0058f1f8).
#pragma once
#include <cstdint>
#include <vector>

#include "sprites/sprite_bank.h"
#include "sprites/sprite_draw.h"

namespace dl2 {
class Video;
}

namespace dl2::sprites {

struct Anim {
    enum : uint16_t { kActive = 0x04, kHitTestable = 0x08, kHasParent = 0x10 };
    enum { kVarState = 0, kVarAux = 1, kVarFacing = 2, kVarParent = 3 };

    uint16_t flags = 0;         // +0x00
    int16_t type = 0;           // +0x02
    int16_t z = 0;              // +0x04
    int32_t x = 0, y = 0;       // +0x06, +0x0a (24.8)
    int16_t sx = 0, sy = 0;     // +0x0e, +0x10
    int16_t w = 0, h = 0;       // +0x12, +0x14
    int16_t frame = 0;          // +0x16 as a frame index of `type` (-1 = none)
    int16_t timer = 0;          // +0x1e
    int16_t rate = 0;           // +0x20
    int16_t dx = 0, dy = 0;     // +0x22, +0x24
    int16_t moveDelay = 0;      // +0x2a
    int16_t var[4] = {};        // +0x2c
    int32_t pc = -1;            // +0x34 word offset into kAnimScript, -1 = no script
    Anim* next = nullptr;       // +0x38
    Anim* prev = nullptr;       // +0x3c

    int screenX() const { return sx; }
    int screenY() const { return sy; }
    void setPosition(int px, int py) { x = px << 8; y = py << 8; }
    int posX() const { return x >> 8; }
    int posY() const { return y >> 8; }
};

// FUN_0046ca40: the game's LCG (seed DAT_0058f1f8).
class GameRandom {
public:
    explicit GameRandom(uint32_t seed = 0) : state_(seed) {}
    uint32_t next() {
        state_ = state_ * 0x41C64E6Du + 0x3039u;
        return (state_ >> 16) & 0x7FFF;
    }
    uint32_t state() const { return state_; }
    void seed(uint32_t s) { state_ = s; }

private:
    uint32_t state_;
};

struct DirtyRect {
    int x0 = 0, y0 = 0, x1 = 0, y1 = 0;   // DAT_00561a20 (left), 24 (top), 28 (right), 2c (bottom)
    bool empty() const { return x0 == x1 || y0 == y1; }
};

class AnimSystem {
public:
    static constexpr int kMaxAnims = 0x96;   // 150
    static constexpr int kDrawAllZ = 0x7FFF;

    AnimSystem();

    // FUN_00444e88: kills everything and rebuilds the free list.
    void reset();
    // FUN_00444f20 CreateAnim(type, x, y, script): script < 0 uses the type's default script. Returns null
    // when the type is invalid or the pool (149 usable objects) is exhausted.
    Anim* create(int type, int x, int y, int script = -1);
    // FUN_00444fd4: removes the object (and, recursively, every child linked to it).
    void kill(Anim* a);
    // FUN_00444ae4: unlink and return to the free list without touching children.
    void free(Anim* a);
    bool isActive(const Anim* a) const;             // FUN_00444abc
    int indexOf(const Anim* a) const;               // (a - DAT_00561a34) / 64
    Anim* at(int index);                            // object by index (parent links use indices)
    void setZ(Anim* a, int z);                      // FUN_00444b74
    void setState(Anim* a, int16_t state, bool restartScript);   // FUN_00445040
    void setFrame(Anim* a, int frameIndex);         // FUN_004451d4
    // CreateHit / BirthCombatSprites pattern: child follows the parent's screen position and restarts its
    // script when the parent's facing (var[2]) changes.
    void setParent(Anim* child, const Anim* parent);
    void setVelocity(Anim* a, int16_t dx, int16_t dy, int16_t delay = 0);

    // FUN_00445270 UpdateAnims(ticks): runs the scripts and applies the velocities.
    void update(int ticks);
    // FUN_00445190: draws from `from` (or the head) while z <= maxZ, returns the first object not drawn.
    Anim* drawUpTo(Video& video, const Clipper& clip, SpriteBank& bank, Anim* from, int maxZ);
    Anim* drawUpTo(Surface8& dst, const Clipper& clip, SpriteBank& bank, Anim* from, int maxZ);
    void drawAll(Video& video, const Clipper& clip, SpriteBank& bank) { drawUpTo(video, clip, bank, head_, kDrawAllZ); }
    void drawAll(Surface8& dst, const Clipper& clip, SpriteBank& bank) { drawUpTo(dst, clip, bank, head_, kDrawAllZ); }
    // DrawSprite FUN_00444cf4 for one object (also refreshes sx/sy/w/h).
    bool drawSprite(Video& video, const Clipper& clip, SpriteBank& bank, Anim* a);
    bool drawSprite(Surface8& dst, const Clipper& clip, SpriteBank& bank, Anim* a);

    Anim* hitTest(int x, int y);                    // FUN_00445100 (flags & 0x0c == 0x0c)
    void addDirtyRect(int x, int y, int w, int h);  // FUN_00445074
    void resetDirtyRect();                          // FUN_004450e0
    const DirtyRect& dirtyRect() const { return dirty_; }
    void resetDrawnList() { drawn_.clear(); }       // FUN_004451cc
    const std::vector<Anim*>& drawnList() const { return drawn_; }   // DAT_00563fbc

    Anim* head() { return head_; }
    Anim* tail() { return tail_; }
    int activeCount() const;
    GameRandom& random() { return rng_; }
    // Frame index of the current frame relative to the type's table ((frame - frames) / 16).
    static int frameIndex(const Anim* a) { return a->frame < 0 ? 0 : a->frame; }

private:
    Anim* alloc(int z);                             // FUN_00444a00
    void unlinkActive(Anim* a);
    void insertSorted(Anim* a, int z);
    bool computeScreenPosition(Anim* a, std::string* problem);   // first half of DrawSprite
    void runScript(Anim* a, bool& killed);         // the script loop of FUN_00445270
    void applyMovement(Anim* a);
    template <typename Target>
    Anim* drawUpToImpl(Target& target, const Clipper& clip, SpriteBank& bank, Anim* from, int maxZ);
    template <typename Target>
    bool drawSpriteImpl(Target& target, const Clipper& clip, SpriteBank& bank, Anim* a);

    std::vector<Anim> pool_;
    Anim* head_ = nullptr;      // DAT_00561a30
    Anim* tail_ = nullptr;      // DAT_00563fb4
    Anim* freeHead_ = nullptr;  // DAT_00563fb8
    DirtyRect dirty_;
    std::vector<Anim*> drawn_;
    GameRandom rng_;
};

// Script opcodes (word values; operands follow). Pointer operands are stored as {offset, 0xFFFF}.
enum AnimOp : uint16_t {
    kOpJump = 0x8001,       // ptr
    kOpSwitch = 0x8002,     // reg, ptr[]  -> goto ptr[var[reg]]
    kOpLoop = 0x8003,       // reg, ptr    -> if (var[reg]) { var[reg]--; goto ptr }
    kOpStepDown = 0x8004,   // reg, lo, hi, ptr -> if (cur != var[reg]) { setFrame(cur == lo ? hi : cur - 1); goto ptr; end tick }
    kOpStepUp = 0x8005,     // reg, lo, hi, ptr -> if (cur != var[reg]) { setFrame(cur == hi ? lo : cur + 1); goto ptr; end tick }
    kOpSet = 0x8006,        // reg, value
    kOpRandom = 0x8007,     // reg, lo, hi -> var[reg] = lo + rand % (hi - lo + 1)
    kOpKill = 0x8008,       // destroy the object
    kOpWait = 0x8009,       // ticks -> timer = ticks; end tick
    kOpWaitVar = 0x800A,    // reg -> if (var[reg] > 0) { timer = var[reg]; end tick }
};

}  // namespace dl2::sprites
