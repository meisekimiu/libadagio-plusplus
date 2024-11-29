#include "FlashTimer.h"
#include "../../components/Sprite.h"
#include "../components/Flash.h"
#include "../components/Score.h"
#include "../states/FailState.h"

void FlashTimer(entt::registry &registry, Adagio::GameServices &services,
                Adagio::StateMachine *state) {
  auto view = registry.view<Muffins::Flash, Sprite>();
  unsigned int score = 0;
  for (auto [entity, gameScore]: registry.view<Muffins::Score>().each()) {
    score = gameScore.score;
    break;
  }
  for (auto [entity, flash, sprite]: view.each()) {
    flash.lifetime -= services.stats->getFrameDelta();
    flash.visibleLifetime -= services.stats->getFrameDelta();
    if (flash.visibleLifetime <= 0) {
      sprite.zIndex = -1000;
    }
    if (flash.lifetime < 0) {
      state->changeState(new Muffins::FailState(flash.isMuffinFail, score));
    }
  }
}
