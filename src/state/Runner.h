#ifndef GL_ADAGIO_RUNNER_H
#define GL_ADAGIO_RUNNER_H

#include "Game.h"

namespace Adagio {
    class Runner {
    public:
        explicit Runner(Game *g, GameState *initialState);

        void run();

    protected:
        Game *game;
        GameState *initialState;

        virtual bool shouldCloseGame();
    };
}

#endif //GL_ADAGIO_RUNNER_H
