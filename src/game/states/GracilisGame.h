#ifndef GL_ADAGIO_GRACILISGAME_H
#define GL_ADAGIO_GRACILISGAME_H

#include "../../state/EntityGameState.h"
#include "../components/SpriteAnimation.h"

class GracilisGame : public Adagio::EntityGameState {
public:
    void init() override;

    void loadContent(Adagio::SpriteBatch &spriteBatch,
                     Adagio::RenderingServices &services) override;

    void unloadContent(Adagio::RenderingServices &services) override;

private:
    Adagio::Texture2D shipTex;
    Adagio::Texture2D wallopTex;
};

#endif // GL_ADAGIO_GRACILISGAME_H
