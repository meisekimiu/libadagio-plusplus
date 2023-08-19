#ifndef GL_ADAGIO_ENTITYGAMESTATE_H
#define GL_ADAGIO_ENTITYGAMESTATE_H

#include "entt/entt.hpp"
#include "./GameState.h"


namespace Adagio {
    typedef void (*SystemFn)(entt::registry &, GameStats &, StateMachine *);

    typedef void (*RendererFn)(entt::registry &, SpriteBatch &, const GameStats &);

    class EntityGameState : public GameState {
    public:
        void registerSystem(SystemFn);

        void registerRenderer(RendererFn);

        void update(GameStats &stats, StateMachine *gameStates) override;

        void draw(SpriteBatch &spriteBatch, const GameStats &stats) override;

    protected:
        entt::registry registry;
        
    private:
        std::vector<SystemFn> systems;
        std::vector<RendererFn> renderers;
    };
}


#endif //GL_ADAGIO_ENTITYGAMESTATE_H
