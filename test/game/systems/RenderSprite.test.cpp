#include "../../../src/game/systems/RenderSprite.h"
#include "../../../src/game/components/Position.h"
#include "../../../src/game/components/Sprite.h"
#include "../../../src/game/components/SpriteClip.h"
#include "../../../src/game/components/SpriteRotation.h"
#include "../../../src/game/components/SpriteScale.h"
#include "../../../src/game/components/SpriteTint.h"
#include "../EcsTestingHarness.h"
#include <catch2/catch.hpp>

static EcsTestingHarness harness;
static const Adagio::SpriteState &getFirstRenderedSprite();

TEST_CASE("No components defined", "[renderer][RenderSprite]") {
  harness.reset();
  REQUIRE_NOTHROW(RenderSprite(harness.registry, harness.spriteBatch,
                               harness.renderingServices));
}

TEST_CASE("It renders a basic sprite", "[renderer][RenderSprite]") {
  harness.reset();
  auto sprite = harness.registry.create();
  auto &spriteComponent = harness.registry.emplace<Sprite>(sprite);
  spriteComponent.texture = Adagio::Texture2D{1, 1, 128, 128};
  spriteComponent.position = Adagio::Vector2d{1, 2};

  harness.testRendererFrame(RenderSprite);

  auto renderedSprite = getFirstRenderedSprite();
  REQUIRE(harness.graphicsDevice.getSprites()->size() == 1);
  REQUIRE(renderedSprite.texture->handle == 1);
  REQUIRE(renderedSprite.texture->getSecretId() == 1);
  REQUIRE(renderedSprite.texture->getWidth() == 128);
  REQUIRE(renderedSprite.texture->getHeight() == 128);
  REQUIRE(renderedSprite.destination.position.x == 1);
  REQUIRE(renderedSprite.destination.position.y == 2);
  REQUIRE(renderedSprite.destination.size.x == 128);
  REQUIRE(renderedSprite.destination.size.y == 128);
}

TEST_CASE("A sprite's position property is offset off of the `Position` "
          "component if it exists",
          "[renderer][RenderSprite]") {
  harness.reset();
  auto sprite = harness.registry.create();
  auto &spriteComponent = harness.registry.emplace<Sprite>(sprite);
  auto &position = harness.registry.emplace<Position>(sprite);
  spriteComponent.texture = Adagio::Texture2D{1, 1, 128, 128};
  spriteComponent.position = Adagio::Vector2d{1, 2};
  position.position = Adagio::Vector2d{300, 300};

  harness.testRendererFrame(RenderSprite);

  auto renderedSprite = getFirstRenderedSprite();
  REQUIRE(renderedSprite.destination.position.x == 301);
  REQUIRE(renderedSprite.destination.position.y == 302);
}

TEST_CASE("It will apply a clipping rectangle from a SpriteClip component",
          "[renderer][RenderSprite]") {
  harness.reset();
  auto sprite = harness.registry.create();
  auto &spriteComponent = harness.registry.emplace<Sprite>(sprite);
  auto &clipping = harness.registry.emplace<SpriteClip>(sprite);
  spriteComponent.texture = Adagio::Texture2D{1, 1, 128, 128};
  spriteComponent.position = {0, 0};
  clipping.source.position.x = 10;
  clipping.source.position.y = 20;
  clipping.source.size.x = 30;
  clipping.source.size.y = 40;

  harness.testRendererFrame(RenderSprite);

  auto renderedSprite = getFirstRenderedSprite();
  REQUIRE(renderedSprite.source.position.x == 10);
  REQUIRE(renderedSprite.source.position.y == 20);
  REQUIRE(renderedSprite.source.size.x == 30);
  REQUIRE(renderedSprite.source.size.y == 40);
  REQUIRE(renderedSprite.destination.position.x == 0);
  REQUIRE(renderedSprite.destination.position.y == 0);
  REQUIRE(renderedSprite.destination.size.x == 30);
  REQUIRE(renderedSprite.destination.size.y == 40);
}

TEST_CASE("It can scale a sprite if the SpriteScale component exists",
          "[renderer][RenderSprite]") {
  harness.reset();
  auto sprite = harness.registry.create();
  auto &spriteComponent = harness.registry.emplace<Sprite>(sprite);
  auto &scale = harness.registry.emplace<SpriteScale>(sprite);
  spriteComponent.texture = Adagio::Texture2D{1, 1, 128, 128};
  scale.scale = Adagio::Vector2f{2, 3};

  harness.testRendererFrame(RenderSprite);

  auto renderedSprite = getFirstRenderedSprite();
  REQUIRE(renderedSprite.destination.size.x == 256);
  REQUIRE(renderedSprite.destination.size.y == 384);
}

TEST_CASE("It scales properly with a clipping rect also applied",
          "[renderer][RenderSprite]") {
  harness.reset();
  auto sprite = harness.registry.create();
  auto &spriteComponent = harness.registry.emplace<Sprite>(sprite);
  auto &scale = harness.registry.emplace<SpriteScale>(sprite);
  auto &clipping = harness.registry.emplace<SpriteClip>(sprite);
  spriteComponent.texture = Adagio::Texture2D{1, 1, 128, 128};
  scale.scale = Adagio::Vector2f{2, 3};
  clipping.source = Adagio::RectF{0, 0, 10, 10};

  harness.testRendererFrame(RenderSprite);

  auto renderedSprite = getFirstRenderedSprite();
  REQUIRE(renderedSprite.destination.size.x == 20);
  REQUIRE(renderedSprite.destination.size.y == 30);
}

TEST_CASE("It rotates the sprite properly", "[renderer][RenderSprite]") {
  harness.reset();
  auto sprite = harness.registry.create();
  auto &spriteComponent = harness.registry.emplace<Sprite>(sprite);
  auto &rotation = harness.registry.emplace<SpriteRotation>(sprite);
  spriteComponent.texture = Adagio::Texture2D{1, 1, 128, 128};
  rotation.origin.x = 64;
  rotation.origin.y = 64;
  rotation.rotation = 3;

  harness.testRendererFrame(RenderSprite);

  auto renderedSprite = getFirstRenderedSprite();
  REQUIRE(renderedSprite.origin.x == 64);
  REQUIRE(renderedSprite.origin.y == 64);
  REQUIRE(renderedSprite.rotation == 3);
}

TEST_CASE("It tints the sprite properly", "[renderer][RenderSprite]") {
  harness.reset();
  auto sprite = harness.registry.create();
  harness.registry.emplace<Sprite>(sprite);
  auto &tint = harness.registry.emplace<SpriteTint>(sprite);
  tint.tint = {0xab, 0xcd, 0xef, 0xff};
  tint.opacity = 128;

  harness.testRendererFrame(RenderSprite);

  auto renderedSprite = getFirstRenderedSprite();
  REQUIRE(renderedSprite.tint.r == 0xab);
  REQUIRE(renderedSprite.tint.g == 0xcd);
  REQUIRE(renderedSprite.tint.b == 0xef);
  REQUIRE(renderedSprite.tint.a == 128);
}

static const Adagio::SpriteState &getFirstRenderedSprite() {
  return (*(harness.graphicsDevice.getSprites()))[0];
}
