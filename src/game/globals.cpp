// globals.cpp - definición del estado global del juego.
#include "game/globals.h"

namespace dl2 {

GameState   gs{};
GameGlobals gg{};

void resetGameState() {
    std::memset(&gs, 0, sizeof(gs));
    gg = GameGlobals{};
}

} // namespace dl2
