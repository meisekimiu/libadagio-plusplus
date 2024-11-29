#include "GameplayState.h"
#include "../../components/Position.h"
#include "../../components/Sprite.h"
#include "../../components/events/MessageInbox.h"
#include "../../systems/RemoveDead.h"
#include "../../systems/RenderSprite.h"
#include "../components/Derpy.h"
#include "../components/Food.h"
#include "../components/Score.h"
#include "../systems/DerpyFloat.h"
#include "../systems/FlashTimer.h"
#include "../systems/FoodEvents.h"
#include "../systems/FoodUpdate.h"
#include "../systems/RenderScore.h"
#include "../systems/UpdateParticles.h"

namespace Muffins {
void GameplayState::init() {
  registerSystem(DerpyFloat);
  registerSystem(FoodUpdate);
  registerSystem(UpdateParticles);
  registerSystem(FlashTimer);

  registerRenderer(RenderSprite);
  registerRenderer(RenderScore);

  registerSystem(FoodEvents);
  registerSystem(RemoveDead);
}

void GameplayState::loadContent(Adagio::SpriteBatch &spriteBatch,
                                Adagio::RenderingServices &services) {
  Adagio::Texture2D tex_Derpy =
      services.textureManager->load("assets/muffins/img/derpy_thinking2.png");
  Adagio::Texture2D tex_Background =
      services.textureManager->load("assets/muffins/img/bg2.png");
  Adagio::Texture2D tex_Muffin =
      services.textureManager->load("assets/muffins/img/muffin.png");
  services.textureManager->load("assets/muffins/img/cupcake.png");
  services.textureManager->load("assets/muffins/img/flash.png");
  services.textureManager->load("assets/muffins/img/singlecrumb1.png");
  services.textureManager->load("assets/muffins/img/singlecrumb2.png");
  services.textureManager->load("assets/muffins/img/singlecrumb3.png");

  services.fontManager->load("assets/muffins/img/SuperMarioBrosNES.fnt");

  services.audioService->getAudioLibrary().loadSample(
      "assets/muffins/sound/derpeat.wav");
  services.audioService->getAudioLibrary().loadSample(
      "assets/muffins/sound/flash.ogg");
  Adagio::Stream mus_Cupcakes =
      services.audioService->getAudioLibrary().loadStream(
          "assets/muffins/sound/Cupcakes.ogg");
  services.audioService->play(mus_Cupcakes).setLooping(true);

  auto ent_Background = registry.create();
  registry.emplace<Sprite>(ent_Background, tex_Background,
                           Adagio::Vector2d{0, 0}, 0);

  auto ent_Derpy = registry.create();
  registry.emplace<Sprite>(ent_Derpy, tex_Derpy, Adagio::Vector2d{0, 0}, 1);
  registry.emplace<Position>(ent_Derpy, Adagio::Vector2d{530.0, 500.0});
  registry.emplace<Muffins::Derpy>(ent_Derpy);

  auto ent_Muffin = registry.create();
  registry.emplace<Sprite>(ent_Muffin, tex_Muffin, Adagio::Vector2d{0, 0}, 1);
  registry.emplace<Position>(ent_Muffin, Adagio::Vector2d{255, 0});
  registry.emplace<Muffins::Food>(ent_Muffin, 1.0);
  registry.emplace<MessageInbox>(ent_Muffin);

  auto ent_Score = registry.create();
  registry.emplace<Muffins::Score>(ent_Score, 0u);
}

} // namespace Muffins
