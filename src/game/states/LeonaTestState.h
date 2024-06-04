#ifndef GL_ADAGIO_LEONATESTSTATE_H
#define GL_ADAGIO_LEONATESTSTATE_H

#include <raylib.h>
#include "../../state/StateMachine.h"
#include "../../state/GameState.h"
#include "../../math/Vector2.h"

class LeonaTestState : public Adagio::GameState { // NOLINT(cppcoreguidelines-pro-type-member-init)
public:
    void init() override;

    void loadContent(Adagio::SpriteBatch &spriteBatch, Adagio::RenderingServices &services) override;

    void update(Adagio::GameStats &stats, Adagio::StateMachine *gameStates) override;

    void draw(Adagio::SpriteBatch &spriteBatch, Adagio::RenderingServices &services) override;

    void unloadContent() override;

protected:
    Adagio::Vector2d leonaPos;
    Adagio::Texture2D leonaTex{0, 0, 0, 0};
};


#endif //GL_ADAGIO_LEONATESTSTATE_H
