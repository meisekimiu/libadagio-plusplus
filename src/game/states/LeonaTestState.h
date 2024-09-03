#ifndef GL_ADAGIO_LEONATESTSTATE_H
#define GL_ADAGIO_LEONATESTSTATE_H

#include "../../math/Vector2.h"
#include "../../state/GameState.h"
#include "../../state/StateMachine.h"
#include <raylib.h>

class LeonaTestState
        : public Adagio::
        GameState { // NOLINT(cppcoreguidelines-pro-type-member-init)
public:
    void init() override;

    void loadContent(Adagio::SpriteBatch &spriteBatch,
                     Adagio::RenderingServices &services) override;

    void update(Adagio::GameServices &stats,
                Adagio::StateMachine *gameStates) override;

    void draw(Adagio::SpriteBatch &spriteBatch,
              Adagio::RenderingServices &services) override;

    void unloadContent(Adagio::RenderingServices &services) override;

protected:
    Adagio::Vector2d leonaPos;
    Adagio::Texture2D leonaTex{0, 0, 0, 0};
};

#endif // GL_ADAGIO_LEONATESTSTATE_H
