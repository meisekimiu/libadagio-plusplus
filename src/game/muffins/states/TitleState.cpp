#include "TitleState.h"
#include "GameplayState.h"
#include <iostream>
#include <raylib.h>

namespace Muffins {
void TitleState::init() {
  std::cout << "Muffins::TitleState::init" << std::endl;
}

void TitleState::loadContent(Adagio::SpriteBatch &spriteBatch,
                             Adagio::RenderingServices &services) {
  titleTex = services.textureManager->load(
      "assets/muffins/img/muffinmare_titlescreen.png");
  helpTex =
      services.textureManager->load("assets/muffins/img/muffinmare_abou.png");
  titleMus = services.audioService->getAudioLibrary().loadStream(
      "assets/muffins/sound/title.ogg");
  bgm = services.audioService->play(titleMus).setLooping(true);
}

void TitleState::update(Adagio::GameServices &services,
                        Adagio::StateMachine *gameStates) {
  services.input->mouse.setCursor(MOUSE_CURSOR_DEFAULT);
  if (services.input->actions.hasActionStarted("HELP"_hs)) {
    helpActive = !helpActive;
  }
  if (helpActive) {
    auto coords = services.input->mouse.getCursorCoords();
    if (eagBox.contains(coords)) {
      services.input->mouse.setCursor(MOUSE_CURSOR_POINTING_HAND);
      if (services.input->mouse.hasClickStarted(MOUSE_BUTTON_LEFT)) {
        OpenURL("https://www.mew151.net/games/games/muffin/eag.html");
      }
    }
  } else {
    if (services.input->actions.hasActionStarted("EAT"_hs)) {
      services.audio->stopAll();
      gameStates->pushState(&gameplayState);
    }
  }
}

void TitleState::draw(Adagio::SpriteBatch &spriteBatch,
                      Adagio::RenderingServices &services) {
  spriteBatch.draw(titleTex, {0, 0}, 0);
  if (helpActive) {
    spriteBatch.draw(helpTex, {0, 0}, 0);
  }
}

void TitleState::resume(Adagio::RenderingServices &services) {
  bgm = services.audioService->play(titleMus).setLooping(true);
  new (&gameplayState) GameplayState();
}

} // namespace Muffins
