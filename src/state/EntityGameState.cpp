#include "EntityGameState.h"

namespace Adagio {
    void EntityGameState::registerSystem(SystemFn system) {
        systems.push_back(system);
    }

    void EntityGameState::registerRenderer(RendererFn renderer) {
        renderers.push_back(renderer);
    }

    void EntityGameState::update(GameStats &stats, StateMachine *gameStates) {
        for (SystemFn system: systems) {
            system(registry, stats, gameStates);
        }
    }

    void EntityGameState::draw(SpriteBatch &spriteBatch, const GameStats &stats) {
        for (RendererFn renderer: renderers) {
            renderer(registry, spriteBatch, stats);
        }
    }
}
