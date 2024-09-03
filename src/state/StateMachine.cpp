#include "StateMachine.h"
#include "GameServices.h"
#include <stdexcept>

namespace Adagio {
    StateMachine::StateMachine(SpriteBatch *sb, RenderingServices *rs) {
        if (!sb) {
            throw std::invalid_argument("SpriteBatch must not be null.");
        }
        spriteBatch = sb;
        services = rs;
    }

    void StateMachine::update(GameServices &services) {
        checkGameStats(services.stats);
        if (!states.empty()) {
            states.back()->update(services, this);
        }
    }

    void StateMachine::draw() {
        for (auto it = states.rbegin(); it != states.rend(); ++it) {
            GameState *state = *it;
            state->draw(*spriteBatch, *services);
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
        state->loadContent(*spriteBatch, *services);
        states.push_back(state);
    }

    void StateMachine::popFinalState() {
        if (!states.empty()) {
            GameState *finalState = states.back();
            finalState->unloadContent(*services);
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

    void GameState::update(GameServices &stats, StateMachine *gameStates) {}
} // namespace Adagio
