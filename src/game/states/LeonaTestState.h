#ifndef GL_ADAGIO_LEONATESTSTATE_H
#define GL_ADAGIO_LEONATESTSTATE_H

#include <raylib.h>
#include "../../state/StateMachine.h"
#include "../../state/GameState.h"

class LeonaTestState : public Adagio::GameState { // NOLINT(cppcoreguidelines-pro-type-member-init)
public:
    void init() override;

    void loadContent(Adagio::SpriteBatch &spriteBatch) override;

    void update(Adagio::GameStats &stats, Adagio::StateMachine *gameStates) override;

    void draw(Adagio::SpriteBatch &spriteBatch, const Adagio::GameStats &stats) override;

    void unloadContent() override;

protected:
    Vector2 leonaPos;
    Texture2D leonaTex;
};


#endif //GL_ADAGIO_LEONATESTSTATE_H
