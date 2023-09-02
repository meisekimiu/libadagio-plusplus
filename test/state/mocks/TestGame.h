#ifndef GL_ADAGIO_TESTGAME_H
#define GL_ADAGIO_TESTGAME_H

#include "../../../src/state/Game.h"

class TestGame : public Adagio::Game {
public:
    explicit TestGame(Adagio::SpriteBatch sb);

    void init() override;

    void loadContent() override;

    void unloadContent() override;

    void cleanup() override;

    bool calledInit{false};
    bool calledLoadContent{false};
    bool calledCleanup{false};
    bool calledUnloadContent{false};
};

#endif //GL_ADAGIO_TESTGAME_H
