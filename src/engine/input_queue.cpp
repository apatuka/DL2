// input_queue.cpp - colas de raton/teclado de CYLib.
#include "engine/input_queue.h"

namespace dl2::engine {

InputQueue& InputQueue::instance() {
    static InputQueue q;
    return q;
}

void InputQueue::pushMouse(int type, int x, int y) {
    // FUN_0048d920: anillo de 20 eventos; los mas antiguos se pierden.
    if (mouse_.size() >= 20) mouse_.pop_front();
    mouse_.push_back(MouseEvent{type, x, y, ++seq_});
}

void InputQueue::pushKey(uint32_t key) {
    if (key == 0) return;
    if (keys_.size() >= 19) keys_.pop_front();   // anillo de 20 (una posicion libre)
    keys_.push_back(key);
}

int InputQueue::find(int type, bool consume, int* x, int* y) {
    // FUN_0048dcbb: busca el evento mas reciente del tipo; al consumir se eliminan el y todos los anteriores.
    for (size_t i = mouse_.size(); i-- > 0;) {
        if (mouse_[i].type != type) continue;
        if (x) *x = mouse_[i].x;
        if (y) *y = mouse_[i].y;
        if (consume) mouse_.erase(mouse_.begin(), mouse_.begin() + std::ptrdiff_t(i) + 1);
        return 1;
    }
    return 0;
}

int InputQueue::buttonDown(uint32_t mask, int* x, int* y, bool consume) {
    if ((mask & 1) && find(kMouseLeftDown, consume, x, y)) return 1;
    if ((mask & 2) && find(kMouseRightDown, consume, x, y)) return 2;
    mousePos(x, y);
    return 0;
}

int InputQueue::doubleClick(uint32_t mask, int* x, int* y, bool consume) {
    if ((mask & 1) && find(kMouseLeftDouble, consume, x, y)) return 1;
    if ((mask & 2) && find(kMouseRightDouble, consume, x, y)) return 2;
    mousePos(x, y);
    return 0;
}

int InputQueue::buttonUp(uint32_t mask, int* x, int* y, bool consume) {
    if ((mask & 1) && find(kMouseLeftUp, consume, x, y)) return 1;
    if ((mask & 2) && find(kMouseRightUp, consume, x, y)) return 2;
    mousePos(x, y);
    return 0;
}

uint32_t InputQueue::getKey() {
    if (keys_.empty()) return 0;
    const uint32_t k = keys_.front();
    keys_.pop_front();
    return k;
}

}  // namespace dl2::engine
