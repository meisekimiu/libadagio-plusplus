#include "EntityGameState.h"
#include <stdexcept>

namespace Adagio {
    void EntityGameState::registerSystem(SystemFn system) {
        if (!system) {
            throw std::invalid_argument("System cannot be null.");
        }
        systems.push_back(system);
    }

    void EntityGameState::registerRenderer(RendererFn renderer) {
        if (!renderer) {
            throw std::invalid_argument("Renderer cannot be null.");
        }
        renderers.push_back(renderer);
    }

    void EntityGameState::update(GameStats &stats, StateMachine *gameStates) {
        if (!gameStates) {
            throw std::invalid_argument("StateMachine cannot be null.");
        }
        for (SystemFn system: systems) {
            system(registry, stats, gameStates);
        }
    }

    void EntityGameState::draw(SpriteBatch &spriteBatch,
                               RenderingServices &services) {
        for (RendererFn renderer: renderers) {
            renderer(registry, spriteBatch, services);
        }
    }

    const std::vector<SystemFn> *EntityGameState::getSystems() const {
        return &systems;
    }

    const std::vector<RendererFn> *EntityGameState::getRenderers() const {
        return &renderers;
    }

    void EntityGameState::initializeRegistryContext() {
        registry.ctx().emplace<Adagio::MessageDispatchService *>(&messageService);
    }

    EntityGameState::EntityGameState() {
        initializeRegistryContext();
    }
} // namespace Adagio
