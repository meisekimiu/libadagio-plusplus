#include "StateMachine.h"

namespace Adagio {
    StateMachine::StateMachine(SpriteBatch *sb) {
        spriteBatch = sb;
    }

    void StateMachine::update(GameStats *stats) {
        if (!states.empty()) {
            states.back()->update(*stats, this);
        }
    }

    void StateMachine::draw(const GameStats *stats) {
        for (auto it = states.rbegin(); it != states.rend(); ++it) {
            GameState *state = *it;
            state->draw(*spriteBatch, *stats);
            if (!state->transparent) {
                break;
            }
        }
    }

    void StateMachine::pushState(GameState *state) {
        if (!states.empty()) {
            states.back()->pause();
        }
        addStateToVector(state);
    }

    void StateMachine::popState() {
        popFinalState();
        if (!states.empty()) {
            states.back()->resume();
        }
    }

    void StateMachine::changeState(GameState *state) {
        popFinalState();
        pushState(state);
    }

    void StateMachine::addStateToVector(GameState *state) {
        state->init();
        state->loadContent(*spriteBatch);
        states.push_back(state);
    }

    void StateMachine::popFinalState() {
        if (!states.empty()) {
            GameState *finalState = states.back();
            finalState->unloadContent();
            finalState->cleanup();
            states.pop_back();
        }
    }

    void GameState::update(GameStats &stats, StateMachine *gameStates) {
        
    }
}
