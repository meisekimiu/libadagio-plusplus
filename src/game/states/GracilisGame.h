#ifndef GL_ADAGIO_GRACILISGAME_H
#define GL_ADAGIO_GRACILISGAME_H

#include "../../state/EntityGameState.h"

class GracilisGame : public Adagio::EntityGameState {
public:
    void init() override;

    void loadContent(Adagio::SpriteBatch &spriteBatch) override;

    void unloadContent() override;

private:
    Texture2D shipTex;
    Texture2D wallopTex;
};


#endif //GL_ADAGIO_GRACILISGAME_H
