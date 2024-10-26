#include "Runner.h"
#include <iostream>
#include <raylib.h>

namespace Adagio {
    Runner::Runner(Game *g, GameState *state) {
        if (!g) {
            throw std::invalid_argument("Game cannot be null");
        }
        if (!state) {
            throw std::invalid_argument("Initial state cannot be null");
        }
        game = g;
        initialState = state;
    }

    void Runner::run() {
        game->init();
        game->loadContent();
        game->stateMachine.pushState(initialState);
        while (!shouldCloseGame()) {
            game->update();
            game->draw();
            if (!game->isRunning()) {
                break;
            }
        }
        game->unloadContent();
        game->cleanup();
    }

    bool Runner::shouldCloseGame() { return WindowShouldClose(); }
} // namespace Adagio
