// input_queue.h - colas de teclado y raton de CYLib (FUN_0048d920 y familia): eventos de boton con posicion
// que se consultan/consumen por tipo, cola circular de teclas con modificadores, y reloj en ms y "ticks" de 14 ms.
#pragma once
#include <cstdint>
#include <deque>
#include <vector>

namespace dl2::engine {

enum MouseEventType : int {
    kMouseLeftDown = 0x201, kMouseLeftUp = 0x202, kMouseLeftDouble = 0x203,
    kMouseRightDown = 0x204, kMouseRightUp = 0x205, kMouseRightDouble = 0x206,
};

struct MouseEvent {
    int type = 0;
    int x = 0, y = 0;
    uint32_t seq = 0;   // orden de llegada (DAT_0065e80c)
};

class InputQueue {
public:
    static InputQueue& instance();

    // Alimentacion desde la capa de plataforma.
    void setMousePos(int x, int y) { mouseX_ = x; mouseY_ = y; }
    void setButtonsHeld(uint32_t mask) { held_ = mask; }
    void setModifiers(bool shift, bool ctrl, bool alt) { shift_ = shift; ctrl_ = ctrl; alt_ = alt; }
    void pushMouse(int type, int x, int y);   // FUN_0048d920 (WM_xBUTTONxxx): maximo 20 eventos
    void pushKey(uint32_t key);               // FUN_0048d920 (WM_KEYDOWN/WM_CHAR): tecla | modificadores << 16
    void setTicks(uint32_t ms) { nowMs_ = ms; }
    void clearMouse() { mouse_.clear(); }     // FUN_0048e11b
    void clearKeys() { keys_.clear(); }       // FUN_0048de7f

    // Raton
    void mousePos(int* x, int* y) const { if (x) *x = mouseX_; if (y) *y = mouseY_; }   // FUN_0048e3f1
    uint32_t buttonsHeld() const { return held_; }   // FUN_0048e4c1: 1 izq, 2 der
    // FUN_0048e1d5 / FUN_0048e169: boton pulsado pendiente (mask: 1 izq, 2 der). Devuelve 1 o 2 y su posicion,
    // 0 si no hay (entonces *x,*y = posicion actual). consume = quitar el evento y los anteriores.
    int buttonDown(uint32_t mask, int* x, int* y, bool consume);
    int doubleClick(uint32_t mask, int* x, int* y, bool consume);   // FUN_0048e385 / FUN_0048e319
    int buttonUp(uint32_t mask, int* x, int* y, bool consume);      // FUN_0048e2ad / FUN_0048e241

    // Teclado
    bool keyAvailable() const { return !keys_.empty(); }   // FUN_0048de8e
    uint32_t peekKey() const { return keys_.empty() ? 0 : keys_.front(); }   // FUN_0048df75
    uint32_t getKey();                                                       // FUN_0048dee3
    bool shiftDown() const { return shift_; }   // FUN_0048dfa7
    bool ctrlDown() const { return ctrl_; }     // FUN_0048dfdf
    bool altDown() const { return alt_; }       // FUN_0048dfc3

    // Reloj (FUN_0048dd95 / FUN_0048de03 / FUN_0048ddd1)
    uint32_t nowMs() const { return nowMs_; }
    uint32_t ticks14() const { return nowMs_ / 14; }

private:
    int find(int type, bool consume, int* x, int* y);   // FUN_0048dcbb
    std::deque<MouseEvent> mouse_;
    std::deque<uint32_t> keys_;
    int mouseX_ = 0, mouseY_ = 0;
    uint32_t held_ = 0;
    bool shift_ = false, ctrl_ = false, alt_ = false;
    uint32_t nowMs_ = 0;
    uint32_t seq_ = 0;
};

}  // namespace dl2::engine
