// anim.cpp - see anim.h. Each method carries the address of the original routine it reproduces.
#include "sprites/anim.h"

#include <cstdio>
#include <cstring>
#include <string>

#include "platform/sdl_video.h"

namespace dl2::sprites {

namespace {

void debugMessage(const std::string& msg) {   // DebugMessage FUN_00458990 (DEBUG.TXT)
    std::fprintf(stderr, "[anim] %s\n", msg.c_str());
}

// Script word access. A pointer operand occupies two words: {word offset, 0xFFFF}.
inline int scriptWord(int pc) { return (pc >= 0 && pc < kAnimScriptWords) ? kAnimScript[pc] : -1; }
inline int scriptPtr(int pc) {
    if (pc < 0 || pc + 1 >= kAnimScriptWords) return -1;
    return kAnimScript[pc + 1] == 0xFFFF ? int(kAnimScript[pc]) : -1;
}
inline int16_t scriptI16(int pc) { return int16_t(uint16_t(scriptWord(pc))); }

}  // namespace

AnimSystem::AnimSystem() : pool_(kMaxAnims) { reset(); }

// FUN_00444e88
void AnimSystem::reset() {
    Anim* a = head_;
    while (a) {
        Anim* n = a->next;
        kill(a);
        a = n;
    }
    for (int i = 0; i < kMaxAnims; ++i) {
        pool_[size_t(i)] = Anim{};
        pool_[size_t(i)].frame = -1;
        pool_[size_t(i)].pc = -1;
        pool_[size_t(i)].next = (i == kMaxAnims - 1) ? nullptr : &pool_[size_t(i) + 1];
        pool_[size_t(i)].prev = (i == 0) ? nullptr : &pool_[size_t(i) - 1];
    }
    head_ = tail_ = nullptr;
    freeHead_ = &pool_[0];
    drawn_.clear();
}

int AnimSystem::indexOf(const Anim* a) const {
    if (!a || a < pool_.data() || a >= pool_.data() + pool_.size()) return -1;
    return int(a - pool_.data());
}

Anim* AnimSystem::at(int index) {
    if (index < 0 || index >= kMaxAnims) return nullptr;
    return &pool_[size_t(index)];
}

// FUN_00444abc
bool AnimSystem::isActive(const Anim* a) const {
    for (const Anim* p = head_; p; p = p->next)
        if (p == a) return true;
    return false;
}

int AnimSystem::activeCount() const {
    int n = 0;
    for (const Anim* p = head_; p; p = p->next) ++n;
    return n;
}

void AnimSystem::unlinkActive(Anim* a) {
    if (a->prev) a->prev->next = a->next;
    if (a->next) a->next->prev = a->prev;
    if (a == tail_) tail_ = a->prev;
    if (a == head_) head_ = a->next;
    a->next = a->prev = nullptr;
}

void AnimSystem::insertSorted(Anim* a, int z) {
    if (!head_) {
        head_ = tail_ = a;
        a->next = a->prev = nullptr;
        return;
    }
    Anim* p = head_;
    while (p->z < z && p != tail_) p = p->next;
    if (p == tail_ && p->z < z) {          // append after the tail
        tail_->next = a;
        a->prev = tail_;
        a->next = nullptr;
        tail_ = a;
    } else {                               // insert before p
        if (p == head_) head_ = a;
        else p->prev->next = a;
        a->prev = p->prev;
        p->prev = a;
        a->next = p;
    }
}

// FUN_00444a00: pops the free list (keeping one sentinel, as the original) and inserts by z.
Anim* AnimSystem::alloc(int z) {
    if (!freeHead_ || !freeHead_->next) return nullptr;
    Anim* a = freeHead_;
    freeHead_ = freeHead_->next;
    freeHead_->prev = nullptr;
    insertSorted(a, z);
    return a;
}

// FUN_00444ae4 "Freeing an invalid ANIM."
void AnimSystem::free(Anim* a) {
    if (!a || !isActive(a)) {
        debugMessage("Freeing an invalid ANIM.");
        return;
    }
    unlinkActive(a);
    *a = Anim{};
    a->frame = -1;
    a->pc = -1;
    a->next = freeHead_;
    a->prev = nullptr;
    if (freeHead_) freeHead_->prev = a;
    freeHead_ = a;
}

// FUN_00444b74
void AnimSystem::setZ(Anim* a, int z) {
    if (!a) return;
    const int old = a->z;
    if (z == old) return;
    a->z = int16_t(z);
    if (head_ == tail_) return;   // single element: nothing to reorder
    Anim* p;
    if (old < z) {
        p = a->next;
        if (p && z <= p->z) return;   // already in order
    } else {
        p = a->prev;
        if (p && p->z <= z) return;
    }
    if (!p) return;
    addDirtyRect(a->sx, a->sy, a->w, a->h);
    unlinkActive(a);
    if (old < z) {
        while (p->z < z && p != tail_) {
            addDirtyRect(p->sx, p->sy, p->w, p->h);
            p = p->next;
        }
    } else {
        while (p != head_ && z < p->prev->z) {
            addDirtyRect(p->sx, p->sy, p->w, p->h);
            p = p->prev;
        }
    }
    if (p == tail_ && p->z < z) {
        tail_->next = a;
        a->prev = tail_;
        a->next = nullptr;
        tail_ = a;
    } else {
        if (p == head_) head_ = a;
        else p->prev->next = a;
        a->prev = p->prev;
        p->prev = a;
        a->next = p;
    }
}

// FUN_00444f20 CreateAnim(type, x, y, script)
Anim* AnimSystem::create(int type, int x, int y, int script) {
    if (type < 0 || type >= kTypeCount) return nullptr;
    const SpriteTypeDef& td = kSpriteTypes[type];
    Anim* a = alloc(1);
    if (!a) return nullptr;
    a->flags = uint16_t(td.flags | Anim::kActive);
    a->type = int16_t(type);
    a->z = 1;
    a->x = x << 8;
    a->y = y << 8;
    a->frame = 0;                       // frame = frames = table base
    a->timer = 1;
    a->moveDelay = 0;
    a->rate = int16_t(td.rate);
    a->pc = script >= 0 ? script : (td.script == kNoScript ? -1 : int(td.script));
    a->var[Anim::kVarParent] = int16_t(indexOf(a));
    return a;
}

// FUN_00444fd4 KillAnim: frees the object and every child linked to it.
void AnimSystem::kill(Anim* a) {
    if (!a || !isActive(a)) return;
    addDirtyRect(a->sx, a->sy, a->w, a->h);
    const int idx = indexOf(a);
    free(a);
    Anim* p = head_;
    while (p) {
        Anim* n = p->next;
        if ((p->flags & Anim::kHasParent) && p->var[Anim::kVarParent] == idx) kill(p);
        p = n;
    }
}

// FUN_00445040
void AnimSystem::setState(Anim* a, int16_t state, bool restartScript) {
    if (!a) return;
    a->var[Anim::kVarState] = state;
    if (restartScript) {
        const SpriteTypeDef& td = kSpriteTypes[a->type];
        a->pc = td.script == kNoScript ? -1 : int(td.script);
        a->timer = 1;
    }
}

// FUN_004451d4 SetAnimFrame(anim, index): falls back to frame 0 when the frame has no pixels.
void AnimSystem::setFrame(Anim* a, int frameIndex) {
    if (!a) return;
    addDirtyRect(a->sx, a->sy, a->w, a->h);
    a->timer = a->rate;
    const SpriteDef* d = SpriteBank::def(a->type, frameIndex);
    a->frame = int16_t(d ? frameIndex : 0);
    d = SpriteBank::def(a->type, a->frame);
    if (d) addDirtyRect((a->x >> 8) + d->hotX, (a->y >> 8) + d->hotY, d->w, d->h);
}

void AnimSystem::setParent(Anim* child, const Anim* parent) {   // CreateHit: puVar3[0x19] = index; flags |= 0x10
    if (!child) return;
    const int idx = indexOf(parent);
    if (idx < 0) {
        child->flags &= uint16_t(~Anim::kHasParent);
        child->var[Anim::kVarParent] = int16_t(indexOf(child));
        return;
    }
    child->var[Anim::kVarParent] = int16_t(idx);
    child->flags |= Anim::kHasParent;
}

void AnimSystem::setVelocity(Anim* a, int16_t dx, int16_t dy, int16_t delay) {
    if (!a) return;
    a->dx = dx;
    a->dy = dy;
    a->moveDelay = delay;
}

// FUN_00445074
void AnimSystem::addDirtyRect(int x, int y, int w, int h) {
    if (x < dirty_.x0 || dirty_.x0 == dirty_.x1) dirty_.x0 = x;
    if (dirty_.x1 < x + w) dirty_.x1 = x + w;
    if (y < dirty_.y0 || dirty_.y0 == dirty_.y1) dirty_.y0 = y;
    if (dirty_.y1 < y + h) dirty_.y1 = y + h;
}

// FUN_004450e0
void AnimSystem::resetDirtyRect() { dirty_ = DirtyRect{}; }

// FUN_00445100
Anim* AnimSystem::hitTest(int x, int y) {
    for (Anim* p = head_; p; p = p->next) {
        if ((p->flags & 0x0C) != 0x0C) continue;
        const int rx = x - p->sx, ry = y - p->sy;
        if (rx >= 0 && rx < p->w && ry >= 0 && ry < p->h) return p;
    }
    return nullptr;
}

// First half of DrawSprite FUN_00444cf4: screen position (with parent linkage) and size.
bool AnimSystem::computeScreenPosition(Anim* a, std::string* problem) {
    const SpriteDef* d = SpriteBank::def(a->type, a->frame);
    if (!d) {
        if (problem) *problem = "Null pointer in DrawSprite: sprite #" + std::to_string(indexOf(a)) + ", type#" + std::to_string(a->type);
        return false;
    }
    if (!(a->flags & Anim::kHasParent) || a->var[Anim::kVarParent] == -1) {
        a->sx = int16_t((a->x >> 8) + d->hotX);
        a->sy = int16_t((a->y >> 8) + d->hotY);
    } else {
        Anim* parent = at(a->var[Anim::kVarParent]);
        const SpriteDef* pd = parent ? SpriteBank::def(parent->type, parent->frame) : nullptr;
        if (!parent || !pd) {
            char buf[96];
            std::snprintf(buf, sizeof buf, "Sprite #%d, type#%d, has bad parent %d, type#%d", indexOf(a), a->type,
                          a->var[Anim::kVarParent], parent ? parent->type : -1);
            debugMessage(buf);
        } else {
            a->sx = int16_t((parent->sx - pd->hotX) + d->hotX);
            a->sy = int16_t((parent->sy - pd->hotY) + d->hotY);
            if (parent->var[Anim::kVarFacing] != a->var[Anim::kVarFacing]) {
                a->var[Anim::kVarFacing] = parent->var[Anim::kVarFacing];
                setState(a, a->var[Anim::kVarState], true);
            }
        }
    }
    a->w = d->w;
    a->h = d->h;
    return true;
}

template <typename Target>
bool AnimSystem::drawSpriteImpl(Target& target, const Clipper& clip, SpriteBank& bank, Anim* a) {
    if (!a) {
        debugMessage("Null sprite in DrawSprite");
        return false;
    }
    std::string problem;
    if (!computeScreenPosition(a, &problem)) {
        debugMessage(problem);
        return false;
    }
    const SpriteFrame f = bank.frame(a->type, a->frame);
    if (!f.valid()) {
        debugMessage("Null pointer in DrawSprite: sprite #" + std::to_string(indexOf(a)) + ", type#" + std::to_string(a->type));
        return false;
    }
    return blitSprite8(target, clip, f.pixels, a->sx, a->sy, a->w, a->h, a->w, BlitMode::ColourKey);
}

bool AnimSystem::drawSprite(Video& video, const Clipper& clip, SpriteBank& bank, Anim* a) {
    return drawSpriteImpl(video, clip, bank, a);
}

bool AnimSystem::drawSprite(Surface8& dst, const Clipper& clip, SpriteBank& bank, Anim* a) {
    return drawSpriteImpl(dst, clip, bank, a);
}

// FUN_00445190
template <typename Target>
Anim* AnimSystem::drawUpToImpl(Target& target, const Clipper& clip, SpriteBank& bank, Anim* from, int maxZ) {
    Anim* p = from;
    while (p && p->z <= maxZ) {
        drawSpriteImpl(target, clip, bank, p);
        drawn_.push_back(p);
        p = p->next;
    }
    return p;
}

Anim* AnimSystem::drawUpTo(Video& video, const Clipper& clip, SpriteBank& bank, Anim* from, int maxZ) {
    return drawUpToImpl(video, clip, bank, from ? from : head_, maxZ);
}

Anim* AnimSystem::drawUpTo(Surface8& dst, const Clipper& clip, SpriteBank& bank, Anim* from, int maxZ) {
    return drawUpToImpl(dst, clip, bank, from ? from : head_, maxZ);
}

// Script loop of FUN_00445270 for one object and one tick (only called when timer expired).
void AnimSystem::runScript(Anim* a, bool& killed) {
    int pc = a->pc;
    bool done = false;
    while (pc >= 0 && !done) {
        const int op = scriptWord(pc);
        if (op < 0) { pc = -1; break; }
        if ((op & 0x8000) == 0) {                       // FRAME n
            setFrame(a, op);
            pc += 1;
            done = true;
            continue;
        }
        switch (op & 0xFF) {
        case 1: {                                       // JUMP ptr
            pc = scriptPtr(pc + 1);
            break;
        }
        case 2: {                                       // SWITCH reg, ptr[]   (FUN_00444e70)
            const int reg = scriptI16(pc + 1);
            const int16_t sel = (reg >= 0 && reg < 4) ? a->var[reg] : 0;
            pc = scriptPtr(pc + 2 + sel * 2);
            break;
        }
        case 3: {                                       // LOOP reg, ptr
            const int reg = scriptI16(pc + 1);
            const int target = scriptPtr(pc + 2);
            int next = pc + 4;
            if (reg >= 0 && reg < 4 && a->var[reg] != 0) {
                a->var[reg]--;
                next = target;
            }
            pc = next;
            break;
        }
        case 4:                                         // STEPDOWN reg, lo, hi, ptr
        case 5: {                                       // STEPUP   reg, lo, hi, ptr
            const int reg = scriptI16(pc + 1);
            const int lo = scriptI16(pc + 2), hi = scriptI16(pc + 3);
            const int target = scriptPtr(pc + 4);
            int next = pc + 6;
            const int cur = frameIndex(a);
            if (reg >= 0 && reg < 4 && cur != a->var[reg]) {
                int idx;
                if ((op & 0xFF) == 4) idx = (cur == lo) ? hi : cur - 1;
                else idx = (cur == hi) ? lo : cur + 1;
                setFrame(a, idx);
                done = true;
                next = target;
            }
            pc = next;
            break;
        }
        case 6: {                                       // SET reg, value
            const int reg = scriptI16(pc + 1);
            if (reg >= 0 && reg < 4) a->var[reg] = scriptI16(pc + 2);
            pc += 3;
            break;
        }
        case 7: {                                       // RANDOM reg, lo, hi
            const int reg = scriptI16(pc + 1);
            const int lo = scriptI16(pc + 2), hi = scriptI16(pc + 3);
            if (reg >= 0 && reg < 4) {
                const unsigned span = unsigned(hi - lo + 1);
                a->var[reg] = int16_t(lo + int(span ? rng_.next() % span : 0));
            }
            pc += 4;
            break;
        }
        case 8: {                                       // KILL
            addDirtyRect(a->sx, a->sy, a->w, a->h);
            kill(a);
            killed = true;
            return;
        }
        case 9: {                                       // WAIT n
            a->timer = scriptI16(pc + 1);
            done = true;
            pc += 2;
            break;
        }
        case 10: {                                      // WAITVAR reg
            const int reg = scriptI16(pc + 1);
            pc += 2;
            if (reg > 0 && reg < 4) {
                a->timer = a->var[reg];
                done = true;
            }
            break;
        }
        default:                                        // unknown (0x800b in the data): skip one word
            pc += 1;
            break;
        }
    }
    a->pc = pc;
}

// Movement part of FUN_00445270.
void AnimSystem::applyMovement(Anim* a) {
    if (a->moveDelay < 1) {
        if (a->dx != 0 || a->dy != 0) {
            addDirtyRect(a->sx, a->sy, a->w, a->h);
            a->x += a->dx;
            a->y += a->dy;
            const SpriteDef* d = SpriteBank::def(a->type, a->frame);
            if (d) addDirtyRect((a->x >> 8) + d->hotX, (a->y >> 8) + d->hotY, d->w, d->h);
        }
    } else {
        a->moveDelay--;
    }
}

// FUN_00445270 UpdateAnims(ticks)
void AnimSystem::update(int ticks) {
    Anim* p = head_;
    while (p) {
        Anim* next = p->next;
        if (p->flags & Anim::kActive) {
            bool killed = false;
            for (int t = ticks; t > 0 && !killed; --t) {
                if (p->pc >= 0 && --p->timer < 1) runScript(p, killed);
                if (killed) break;
                applyMovement(p);
            }
        }
        p = next;
    }
}

}  // namespace dl2::sprites
