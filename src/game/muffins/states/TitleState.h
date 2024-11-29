#ifndef GL_ADAGIO_TITLESTATE_H
#define GL_ADAGIO_TITLESTATE_H

#include "../../../state/GameState.h"
#include "../../../state/StateMachine.h"
#include "GameplayState.h"

namespace Muffins {

class TitleState : public Adagio::GameState {
public:
  void init() override;

  void loadContent(Adagio::SpriteBatch &spriteBatch, Adagio::RenderingServices &services) override;

  void update(Adagio::GameServices &stats, Adagio::StateMachine *gameStates) override;

  void draw(Adagio::SpriteBatch &spriteBatch, Adagio::RenderingServices &services) override;

  void resume(Adagio::RenderingServices &services) override;

private:
  Adagio::Texture2D titleTex;
  Adagio::Texture2D helpTex;
  Adagio::Stream titleMus;
  Adagio::PlayingSound bgm;
  Adagio::RectI eagBox{735, 740, 15, 5};
  GameplayState gameplayState;
  bool helpActive{false};
};

} // namespace Muffins

#endif // GL_ADAGIO_TITLESTATE_H
