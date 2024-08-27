#ifndef GL_ADAGIO_ENTITYGAMESTATE_H
#define GL_ADAGIO_ENTITYGAMESTATE_H

#include "./GameState.h"
#include "../event/MessageDispatchService.h"
#include "entt/entt.hpp"

namespace Adagio {
    typedef void (*SystemFn)(entt::registry &, GameStats &, StateMachine *);

    typedef void (*RendererFn)(entt::registry &, SpriteBatch &,
                               RenderingServices &);

    class EntityGameState : public GameState {
    public:
        EntityGameState();

        void registerSystem(SystemFn);

        void registerRenderer(RendererFn);

        void update(GameStats &stats, StateMachine *gameStates) override;

        void draw(SpriteBatch &spriteBatch, RenderingServices &services) override;

    protected:
        entt::registry registry;

        MessageDispatchService messageService;

        void initializeRegistryContext();

        [[nodiscard]] const std::vector<SystemFn> *getSystems() const;

        [[nodiscard]] const std::vector<RendererFn> *getRenderers() const;

    private:
        std::vector<SystemFn> systems;
        std::vector<RendererFn> renderers;
    };
} // namespace Adagio

#endif // GL_ADAGIO_ENTITYGAMESTATE_H
