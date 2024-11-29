#include "RenderScore.h"
#include "../components/Score.h"
#include <iomanip>

void RenderScore(entt::registry &registry, Adagio::SpriteBatch &spriteBatch,
                 Adagio::RenderingServices &services) {
  auto view = registry.view<Muffins::Score>();
  for (auto [entity, score] : view.each()) {
    std::stringstream buffer;
    buffer << "SCORE: ";
    buffer << std::setfill('0') << std::setw(3) << score.score;
    score.scoreString = buffer.str();
    auto text = spriteBatch.drawText(score.scoreString.c_str(), {1024 / 2 - 480 / 2,5}, 5);
    text->font = services.fontManager->getFont("assets/muffins/img/SuperMarioBrosNES.fnt"_hs);
    text->fontSize = 48;
  }
}
