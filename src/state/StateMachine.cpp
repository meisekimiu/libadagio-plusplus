#include "StateMachine.h"
#include <stdexcept>

namespace Adagio {
    StateMachine::StateMachine(SpriteBatch *sb) {
        if (!sb) {
            throw std::invalid_argument("SpriteBatch must not be null.");
        }
        spriteBatch = sb;
    }

    void StateMachine::update(GameStats *stats) {
        checkGameStats(stats);
        if (!states.empty()) {
            states.back()->update(*stats, this);
        }
    }

    void StateMachine::draw(RenderingServices &services) {
        for (auto it = states.rbegin(); it != states.rend(); ++it) {
            GameState *state = *it;
            state->draw(*spriteBatch, services);
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
        if (!state) {
            throw std::invalid_argument("GameState must not be null");
        }
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

    void StateMachine::checkGameStats(const GameStats *stats) {
        if (!stats) {
            throw std::invalid_argument("GameStats must not be null");
        }
    }

    StateMachine::~StateMachine() {
        while (!states.empty()) {
            popFinalState();
        }
    }

    void GameState::update(GameStats &stats, StateMachine *gameStates) {

    }
}
