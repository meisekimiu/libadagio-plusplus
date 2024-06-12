#include "GracilisGame.h"
#include "../components/PlayerShip.h"
#include "../components/Position.h"
#include "../components/Sprite.h"
#include "../components/SpriteAnimation.h"
#include "../components/SpriteClip.h"
#include "../systems/AnimateSprite.h"
#include "../systems/RemoveDead.h"
#include "../systems/RenderSprite.h"
#include "../systems/Wallop.h"
#include "../systems/ship.h"
#include <iostream>

void GracilisGame::init() {
  std::cout << "GracilisGame init" << std::endl;
  registerSystem(AnimateSprite);
  registerRenderer(RenderSprite);
  registerSystem(ShipSystem);
  registerSystem(WallopSystem);
  registerSystem(RemoveDead);
}

void GracilisGame::loadContent(Adagio::SpriteBatch &spriteBatch,
                               Adagio::RenderingServices &services) {
  spriteBatch.setClearColor({0, 0, 0, 255});
  shipTex = services.textureManager->load("assets/ship.png");
  wallopTex = services.textureManager->load("assets/wallop.png");
  wallopFrames = new AnimationFrame[4]{
      {0.083333, Adagio::RectI{0, 0, 64, 56}},
      {0.083333, Adagio::RectI{64, 0, 64, 56}},
      {0.083333, Adagio::RectI{64 * 2, 0, 64, 56}},
      {0.083333, Adagio::RectI{64 * 3, 0, 64, 56}},
  };

  const auto ship = registry.create();
  registry.emplace<PlayerShip>(ship, Adagio::Vector2d{0, 0}, wallopTex,
                               wallopFrames);
  registry.emplace<Position>(ship, Adagio::Vector2d{320, 240});
  registry.emplace<Sprite>(ship, shipTex, Adagio::Vector2d{0, 0}, 0);
  registry.emplace<SpriteClip>(ship);
  SpriteAnimation &animation = registry.emplace<SpriteAnimation>(ship);
  animation.frameLength = 4;
  animation.loop = true;
  shipFrames = new AnimationFrame[4]{
      {0.083333, Adagio::RectI{0, 0, 56, 89}},
      {0.083333, Adagio::RectI{56, 0, 56, 89}},
      {0.083333, Adagio::RectI{56 * 2, 0, 56, 89}},
      {0.083333, Adagio::RectI{56 * 3, 0, 56, 89}},
  };
  animation.frames = shipFrames;
}

void GracilisGame::unloadContent(Adagio::RenderingServices &services) {
  std::cout << "GracilisGame quit" << std::endl;
  services.textureManager->unload(shipTex);
  services.textureManager->unload(wallopTex);
  delete shipFrames;
  delete wallopFrames;
}
