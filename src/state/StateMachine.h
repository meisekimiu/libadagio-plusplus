#ifndef GL_ADAGIO_STATEMACHINE_H
#define GL_ADAGIO_STATEMACHINE_H

#include <vector>
#include "../graphics/SpriteBatch.h"
#include "./GameState.h"
#include "./GameStats.h"

namespace Adagio {

    class StateMachine {
    public:
        explicit StateMachine(SpriteBatch *spriteBatch);

        ~StateMachine();

        void update(GameStats *stats);

        void draw(const GameStats *stats);

        void pushState(GameState *state);

        void popState();

        void changeState(GameState *state);


    private:
        std::vector<GameState *> states;

        void addStateToVector(GameState *state);

        void popFinalState();

        SpriteBatch *spriteBatch;

        void checkGameStats(const GameStats *stats);
    };
}


#endif //GL_ADAGIO_STATEMACHINE_H
