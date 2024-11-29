#ifndef GL_ADAGIO_FAILSTATE_H
#define GL_ADAGIO_FAILSTATE_H

#include "../../../state/GameState.h"
#include "../../../state/StateMachine.h"

namespace Muffins {

class FailState : public Adagio::GameState {
public:
  explicit FailState(bool isMuffin, unsigned int score);

  void loadContent(Adagio::SpriteBatch &spriteBatch, Adagio::RenderingServices &services) override;

  void update(Adagio::GameServices &stats, Adagio::StateMachine *gameStates) override;

  void draw(Adagio::SpriteBatch &spriteBatch, Adagio::RenderingServices &services) override;

private:
  Adagio::Texture2D tex_gameOverMuffin;
  Adagio::Texture2D tex_gameOverCupcake;
  Adagio::Stream mus_chopin;
  Adagio::Font fnt_font;
  bool isMuffin;
  unsigned int highScore;
  std::string scoreText;
};

} // namespace Muffins

#endif // GL_ADAGIO_FAILSTATE_H
