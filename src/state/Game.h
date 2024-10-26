#ifndef GL_ADAGIO_GAME_H
#define GL_ADAGIO_GAME_H

#include "../input/InputService.h"
#include "../graphics/SpriteBatch.h"
#include "../event/MessageDispatchService.h"
#include "GameServices.h"
#include "GameStats.h"
#include "StateMachine.h"

namespace Adagio {
    class Game : public GameStats {
    public:
        SpriteBatch spriteBatch;
        InputService input;
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

        MessageDispatchService messageDispatchService;

        SpriteAnimationLibrary animationLibrary;

        RenderingServices renderingServices{
                &spriteBatch, spriteBatch.getGraphicsDevice()->getTextureManager(), this, &animationLibrary,
                spriteBatch.getGraphicsDevice()->getFontManager()};

        GameServices gameServices{
                &messageDispatchService, this,
                {spriteBatch.getGraphicsDevice()->getTextureManager(), &animationLibrary}, &input
        };
    };
} // namespace Adagio

#endif // GL_ADAGIO_GAME_H
