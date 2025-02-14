#ifndef GL_ADAGIO_GAMESTATE_H
#define GL_ADAGIO_GAMESTATE_H

#include "../graphics/SpriteBatch.h"
#include "./GameState.h"
#include "./GameStats.h"
#include "RenderingServices.h"
#include "entt/entt.hpp"
#include "GameServices.h"

namespace Adagio {
    class StateMachine;

    class GameState {
    public:
        bool transparent{false};
        bool memoryManaged{true};
        
        virtual void init();

        virtual void loadContent(SpriteBatch &spriteBatch,
                                 RenderingServices &services);

        virtual void pause();

        virtual void resume(RenderingServices &services);

        virtual void update(GameServices &stats, StateMachine *gameStates);

        virtual void draw(SpriteBatch &spriteBatch, RenderingServices &services);

        virtual void cleanup();

        virtual void unloadContent(RenderingServices &services);
    };

} // namespace Adagio

#endif // GL_ADAGIO_GAMESTATE_H
