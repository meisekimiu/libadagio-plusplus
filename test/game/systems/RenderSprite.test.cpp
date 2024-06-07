#include <catch2/catch.hpp>
#include "../../../src/game/components/Sprite.h"
#include "../../../src/game/components/SpriteClip.h"
#include "../../../src/game/components/Position.h"
#include "../../../src/game/systems/RenderSprite.h"
#include "../EcsTestingHarness.h"
#include "../../../src/game/components/SpriteScale.h"

static EcsTestingHarness harness;

TEST_CASE("No components defined", "[renderer][RenderSprite]") {
    harness.reset();
    REQUIRE_NOTHROW(RenderSprite(harness.registry, harness.spriteBatch, harness.renderingServices));
}

TEST_CASE("It renders a basic sprite", "[renderer][RenderSprite]") {
    harness.reset();
    auto sprite = harness.registry.create();
    auto &spriteComponent = harness.registry.emplace<Sprite>(sprite);
    spriteComponent.texture = Adagio::Texture2D{1, 1, 128, 128};
    spriteComponent.position = Adagio::Vector2d{1, 2};

    harness.testRendererFrame(RenderSprite);

    auto renderedSprites = *(harness.graphicsDevice.getSprites());
    REQUIRE(renderedSprites.size() == 1);
    REQUIRE(renderedSprites[0].texture->handle == 1);
    REQUIRE(renderedSprites[0].texture->getSecretId() == 1);
    REQUIRE(renderedSprites[0].texture->getWidth() == 128);
    REQUIRE(renderedSprites[0].texture->getHeight() == 128);
    REQUIRE(renderedSprites[0].destination.position.x == 1);
    REQUIRE(renderedSprites[0].destination.position.y == 2);
    REQUIRE(renderedSprites[0].destination.size.x == 128);
    REQUIRE(renderedSprites[0].destination.size.y == 128);
}

TEST_CASE("A sprite's position property is offset off of the `Position` component if it exists", "[renderer][RenderSprite]") {
    harness.reset();
    auto sprite = harness.registry.create();
    auto &spriteComponent = harness.registry.emplace<Sprite>(sprite);
    auto &position = harness.registry.emplace<Position>(sprite);
    spriteComponent.texture = Adagio::Texture2D{1, 1, 128, 128};
    spriteComponent.position = Adagio::Vector2d{1, 2};
    position.position = Adagio::Vector2d{300, 300};

    harness.testRendererFrame(RenderSprite);

    auto renderedSprite = (*(harness.graphicsDevice.getSprites()))[0];
    REQUIRE(renderedSprite.destination.position.x == 301);
    REQUIRE(renderedSprite.destination.position.y == 302);
}

TEST_CASE("It will apply a clipping rectangle from a SpriteClip component", "[renderer][RenderSprite]") {
    harness.reset();
    auto sprite = harness.registry.create();
    auto &spriteComponent = harness.registry.emplace<Sprite>(sprite);
    auto &clipping = harness.registry.emplace<SpriteClip>(sprite);
    spriteComponent.texture = Adagio::Texture2D{1, 1, 128, 128};
    spriteComponent.position = {0,0};
    clipping.source.position.x = 10;
    clipping.source.position.y = 20;
    clipping.source.size.x = 30;
    clipping.source.size.y = 40;

    harness.testRendererFrame(RenderSprite);

    auto renderedSprite = (*(harness.graphicsDevice.getSprites()))[0];
    REQUIRE(renderedSprite.source.position.x == 10);
    REQUIRE(renderedSprite.source.position.y == 20);
    REQUIRE(renderedSprite.source.size.x == 30);
    REQUIRE(renderedSprite.source.size.y == 40);
    REQUIRE(renderedSprite.destination.position.x == 0);
    REQUIRE(renderedSprite.destination.position.y == 0);
    REQUIRE(renderedSprite.destination.size.x == 30);
    REQUIRE(renderedSprite.destination.size.y == 40);
}

TEST_CASE("It can scale a sprite if the SpriteScale component exists", "[renderer][RenderSprite]") {
    harness.reset();
    auto sprite = harness.registry.create();
    auto &spriteComponent = harness.registry.emplace<Sprite>(sprite);
    auto &scale = harness.registry.emplace<SpriteScale>(sprite);
    spriteComponent.texture = Adagio::Texture2D{1, 1, 128, 128};
    scale.scale = Adagio::Vector2f{2,3};

    harness.testRendererFrame(RenderSprite);

    auto renderedSprite = (*(harness.graphicsDevice.getSprites()))[0];
    REQUIRE(renderedSprite.destination.size.x == 256);
    REQUIRE(renderedSprite.destination.size.y == 384);
}

TEST_CASE("It scales properly with a clipping rect also applied", "[renderer][RenderSprite]") {
    harness.reset();
    auto sprite = harness.registry.create();
    auto &spriteComponent = harness.registry.emplace<Sprite>(sprite);
    auto &scale = harness.registry.emplace<SpriteScale>(sprite);
    auto &clipping = harness.registry.emplace<SpriteClip>(sprite);
    spriteComponent.texture = Adagio::Texture2D{1, 1, 128, 128};
    scale.scale = Adagio::Vector2f{2,3};
    clipping.source = Adagio::RectF{0,0, 10, 10};

    harness.testRendererFrame(RenderSprite);

    auto renderedSprite = (*(harness.graphicsDevice.getSprites()))[0];
    REQUIRE(renderedSprite.destination.size.x == 20);
    REQUIRE(renderedSprite.destination.size.y == 30);
}
