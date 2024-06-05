#include <catch2/catch.hpp>
#include "../../../src/game/components/Sprite.h"
#include "../../../src/game/components/Position.h"
#include "../../../src/game/systems/RenderSprite.h"
#include "../EcsTestingHarness.h"

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

TEST_CASE("A sprite's position property is offset off of the `Position` component if it exists") {
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
