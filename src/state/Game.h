#ifndef GL_ADAGIO_GAME_H
#define GL_ADAGIO_GAME_H

#include "../graphics/SpriteBatch.h"
#include "./GameStats.h"
#include "./StateMachine.h"

namespace Adagio {
    class Game : public GameStats {
    public:
        SpriteBatch spriteBatch;
        StateMachine stateMachine = StateMachine(&spriteBatch, &renderingServices);

        explicit Game(SpriteBatch &sb);

        void update();

        void draw();

        [[nodiscard]] double getGameTime() const override;

        [[nodiscard]] float getFrameDelta() const override;

        [[nodiscard]] bool isRunning() const override;

        void closeGame() override;

        virtual void init() = 0;

        virtual void loadContent();

        virtual void cleanup();

        virtual void unloadContent();

    protected:
        bool running{true};
        double gameTime{0.0};
        float frameDelta{0.0};

        RenderingServices renderingServices{&spriteBatch, spriteBatch.getGraphicsDevice()->getTextureManager(), this};
    };
}

#endif //GL_ADAGIO_GAME_H
