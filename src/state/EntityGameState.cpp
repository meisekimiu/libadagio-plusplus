#include "EntityGameState.h"
#include "../game/components/events/hooks/MessageInboxHooks.h"
#include "../game/components/events/MessageInbox.h"
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

    void EntityGameState::update(GameServices &services, StateMachine *gameStates) {
        if (!gameStates) {
            throw std::invalid_argument("StateMachine cannot be null.");
        }
        MessageDispatchService *prevValue = services.messageDispatchService;
        services.messageDispatchService = &messageService;
        for (SystemFn system: systems) {
            system(registry, services, gameStates);
        }
        services.messageDispatchService = prevValue;
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
        registry.on_construct<MessageInbox>().connect<&RegisterInboxWithMessageService>();
        registry.on_destroy<MessageInbox>().connect<&UnregisterInboxWithMessageService>();
    }

    EntityGameState::EntityGameState() {
        initializeRegistryContext();
    }
} // namespace Adagio
