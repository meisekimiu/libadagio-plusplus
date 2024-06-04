#ifndef GL_ADAGIO_SANDBOXGAME_H
#define GL_ADAGIO_SANDBOXGAME_H

#include "../state/Game.h"
#include "../state/StateMachine.h"

class SandboxGame : public Adagio::Game {
public:
    explicit SandboxGame(Adagio::SpriteBatch &sb);
    
    void init() override;

    void loadContent() override;

    void cleanup() override;
};

#endif //GL_ADAGIO_SANDBOXGAME_H
