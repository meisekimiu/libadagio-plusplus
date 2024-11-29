#include "FailState.h"
#include <iomanip>
#include <string>

namespace Muffins {
FailState::FailState(bool muffin, unsigned int score) : isMuffin(muffin), highScore(score) {
  memoryManaged = false;
}

void FailState::loadContent(Adagio::SpriteBatch &spriteBatch,
                            Adagio::RenderingServices &services) {
  tex_gameOverCupcake = services.textureManager->load("assets/muffins/img/muffinmare_gameovercupcake.png");
  tex_gameOverMuffin = services.textureManager->load("assets/muffins/img/muffinmare_gameovermuffin.png");
  mus_chopin = services.audioService->getAudioLibrary().loadStream("assets/muffins/sound/preludeop28no4chopin2.ogg");

  fnt_font = services.fontManager->getFont("assets/muffins/img/SuperMarioBrosNES.fnt"_hs);

  services.audioService->play(mus_chopin).setLooping(true);
}

void FailState::update(Adagio::GameServices &services,
                       Adagio::StateMachine *gameStates) {
  if (services.input->actions.hasActionStarted("EAT"_hs)) {
    services.audio->stopAll();
    gameStates->popState();
  }
}

void FailState::draw(Adagio::SpriteBatch &spriteBatch,
                     Adagio::RenderingServices &services) {
  Adagio::Texture2D &tex = isMuffin ? tex_gameOverMuffin : tex_gameOverCupcake;
  spriteBatch.draw(tex, {0, 0}, 1);

  std::stringstream buffer;
  buffer << "SCORE: ";
  buffer << std::setfill('0') << std::setw(3) << highScore;
  scoreText = buffer.str();
  auto text = spriteBatch.drawText(scoreText.c_str(), {1024 / 2 - 480 / 2, 768 - 48 - 10}, 2);
  text->font = fnt_font;
  text->fontSize = 48;
}

} // namespace Muffins
