#ifndef GL_ADAGIO_GRACILISGAME_H
#define GL_ADAGIO_GRACILISGAME_H

#include "../components/SpriteAnimation.h"
#include "../../state/EntityGameState.h"

class GracilisGame : public Adagio::EntityGameState {
public:
    void init() override;

    void loadContent(Adagio::SpriteBatch &spriteBatch, Adagio::RenderingServices &services) override;

    void unloadContent(Adagio::RenderingServices &services) override;

private:
    Adagio::Texture2D shipTex;
    Adagio::Texture2D wallopTex;
    AnimationFrame* shipFrames{nullptr};
    AnimationFrame* wallopFrames{nullptr};
};


#endif //GL_ADAGIO_GRACILISGAME_H
