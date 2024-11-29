#include "FoodEvents.h"
#include "../../components/Dead.h"
#include "../../components/Position.h"
#include "../../components/Sprite.h"
#include "../../components/SpriteRotation.h"
#include "../../components/SpriteScale.h"
#include "../../components/SpriteTint.h"
#include "../../components/events/MessageInbox.h"
#include "../components/Flash.h"
#include "../components/Food.h"
#include "../components/Particle.h"
#include "../components/Score.h"

static void CreateNewFood(entt::registry &registry, Adagio::GameServices &services, double speed,
                   double xPos) {
  services.audio->play(services.audio->getAudioLibrary().getSample("assets/muffins/sound/derpeat.wav"_hs));

  auto view = registry.view<Muffins::Score>();
  for (auto [_, score]: view.each()) {
    score.score++;
  }

  const auto ent_Muffin = registry.create();
  const bool isMuffin = rand() > (RAND_MAX / 2);
  const std::uint32_t textureName = isMuffin ? "assets/muffins/img/muffin.png"_hs : "assets/muffins/img/cupcake.png"_hs;
  registry.emplace<Sprite>(ent_Muffin, services.resources.textureManager->getTexture(textureName),
                           Adagio::Vector2d{0, 0}, 1);
  registry.emplace<Position>(ent_Muffin, Adagio::Vector2d{xPos, 0});
  registry.emplace<Muffins::Food>(ent_Muffin, speed + 2.0/7.0, !isMuffin);
  registry.emplace<MessageInbox>(ent_Muffin);
}

static void CreateFlash(entt::registry &registry, Adagio::GameServices &services, bool isMuffinFail) {
  services.audio->stopAll();
  services.audio->play(services.audio->getAudioLibrary().getSample("assets/muffins/sound/flash.ogg"_hs));

  const auto ent_Flash = registry.create();
  registry.emplace<Sprite>(ent_Flash, services.resources.textureManager->getTexture("assets/muffins/img/flash.png"_hs), Adagio::Vector2d{0, 0}, 1000);
  registry.emplace<SpriteScale>(ent_Flash, Adagio::Vector2f{1024,1024});
  Muffins::Flash &flash = registry.emplace<Muffins::Flash>(ent_Flash);
  flash.isMuffinFail = isMuffinFail;
}

static double randDouble() {
  return static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
}

static void CreateCrumbParticles(entt::registry &registry, Adagio::GameServices &services, const Adagio::Vector2d &position, double speedMod) {
  const std::uint32_t sprites[] = {"assets/muffins/img/singlecrumb1.png"_hs, "assets/muffins/img/singlecrumb2.png"_hs, "assets/muffins/img/singlecrumb3.png"_hs};
  int crumbNumber = rand() % 8 + 10;
  for (int i = 0; i < crumbNumber; i++) {
    Adagio::Texture2D sprite = services.resources.textureManager->getTexture(sprites[rand() % 3]);
    const auto ent_Crumb = registry.create();
    registry.emplace<Muffins::Particle>(ent_Crumb, (randDouble() - 0.5) * (5.5 + speedMod / 3), (-6 + speedMod) * randDouble() - 0.5, (randDouble() - 0.5) * (20 + speedMod / 2), randDouble() * M_PI + 1.0);
    auto &p =registry.emplace<Position>(ent_Crumb, Adagio::Vector2d{position.x + randDouble()*210, position.y + randDouble()*180 + 30});
    registry.emplace<SpriteTint>(ent_Crumb, Adagio::Color{255, 255, 255, 255});
    registry.emplace<SpriteRotation>(ent_Crumb, Adagio::Vector2d{static_cast<double>(sprite.getWidth() / 2), static_cast<double>(sprite.getHeight() / 2)}, randDouble() * M_PI);
    registry.emplace<SpriteScale>(ent_Crumb, Adagio::Vector2f{static_cast<float>(randDouble() / 1.5 + 0.5), static_cast<float>(randDouble() / 1.5 + 0.5)});
    registry.emplace<Sprite>(ent_Crumb, sprite, Adagio::Vector2d {0, 0}, 10);
  }
}

void FoodEvents(entt::registry &registry, Adagio::GameServices &services,
                Adagio::StateMachine *state) {
  auto view = registry.view<Muffins::Food, Position, MessageInbox>();
  for (auto [entity, food, pos, inbox]: view.each()) {
    for (const Adagio::Message &message: inbox.messages) {
      if (message.name == "EAT"_hs) {
        if (!food.canHitGround) {
          registry.emplace<Dead>(entity);
          CreateNewFood(registry, services, food.speed, pos.position.x);
          CreateCrumbParticles(registry, services, pos.position, food.speed);
        } else {
          CreateFlash(registry, services, !food.canHitGround);
        }
      } else if (message.name == "PASS"_hs) {
        if (food.canHitGround) {
          registry.emplace<Dead>(entity);
          CreateNewFood(registry, services, food.speed, pos.position.x);
        } else {
          CreateFlash(registry, services, !food.canHitGround);
        }
      }
      inbox.messages.clear();
    }
  }
}
