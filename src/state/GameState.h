#ifndef GL_ADAGIO_GAMESTATE_H
#define GL_ADAGIO_GAMESTATE_H

#include "entt/entt.hpp"
#include "../graphics/SpriteBatch.h"
#include "./GameStats.h"
#include "./GameState.h"
#include "RenderingServices.h"

namespace Adagio {
    class StateMachine;

    class GameState {
    public:
        bool transparent{false};

        virtual void init();

        virtual void loadContent(SpriteBatch &spriteBatch);

        virtual void pause();

        virtual void resume();

        virtual void update(GameStats &stats, StateMachine *gameStates);

        virtual void draw(SpriteBatch &spriteBatch, RenderingServices &services);

        virtual void cleanup();

        virtual void unloadContent();
    };

} // Adagio

#endif //GL_ADAGIO_GAMESTATE_H
