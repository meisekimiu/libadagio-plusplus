#include "Runner.h"
#include <iostream>

namespace Adagio {
    Runner::Runner(Game *g, GameState *state) {
        game = g;
        initialState = state;
    }

    void Runner::run() {
        if (game) {
            game->init();
            game->loadContent();
            game->stateMachine.pushState(initialState);
            while (!WindowShouldClose()) {
                game->update();
                game->draw();
                if (!game->isRunning()) {
                    break;
                }
            }
            game->unloadContent();
            game->cleanup();
        } else {
            std::cerr << "Adagio Error: No game object defined!" << std::endl;
        }
    }
}
