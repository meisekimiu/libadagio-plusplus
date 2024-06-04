#ifndef GL_ADAGIO_EMPTYGAMESTATE_H
#define GL_ADAGIO_EMPTYGAMESTATE_H

#include "../../../src/state/StateMachine.h"
#include "../../graphics/MockGraphicsDevice.h"
#include "../../../src/graphics/SpriteBatch.h"
#include "../../../src/state/GameState.h"

class EmptyGameState : public Adagio::GameState {
public:
    void init() override;

    void loadContent(Adagio::SpriteBatch &sb, Adagio::RenderingServices &services) override;

    void update(Adagio::GameStats &stats, Adagio::StateMachine *gameStates) override;

    void draw(Adagio::SpriteBatch &sb, Adagio::RenderingServices &services) override;

    void pause() override;

    void resume() override;

    void unloadContent(Adagio::RenderingServices &services) override;

    void cleanup() override;

    void reset();

    [[nodiscard]] bool calledInit() const;

    [[nodiscard]] bool calledCleanup() const;

    [[nodiscard]] bool calledLoadContent() const;

    [[nodiscard]] bool calledUnloadContent() const;

    [[nodiscard]] bool calledUpdate() const;

    [[nodiscard]] bool calledDraw() const;

    [[nodiscard]] bool calledPause() const;

    [[nodiscard]] bool calledResume() const;

    [[nodiscard]] float lastFrameTime() const;

    [[nodiscard]] double lastGameTime() const;

protected:
    bool initCalled{false};
    bool loadContentCalled{false};
    bool updateCalled{false};
    bool drawCalled{false};
    bool pauseCalled{false};
    bool resumeCalled{false};
    bool unloadContentCalled{false};
    bool cleanupCalled{false};
    float frameDelta{-1.0};
    double gameTime{-1.0};
};

#endif //GL_ADAGIO_EMPTYGAMESTATE_H
