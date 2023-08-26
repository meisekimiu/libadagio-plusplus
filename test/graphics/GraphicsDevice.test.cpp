#include <catch2/catch.hpp>
#include "../../src/graphics/SpriteState.h"
#include "../../src/graphics/TextState.h"
#include "MockGraphicsDevice.h"

TEST_CASE("GraphicsDevice exists", "[GraphicsDevice]") {
    MockGraphicsDevice gd;
    REQUIRE_FALSE(gd.hasBegun());
    REQUIRE_FALSE(gd.hasEnded());
    REQUIRE_FALSE(gd.getDrawnSprite());
    REQUIRE_FALSE(gd.getDrawnText());
    Color clearColor = gd.getClearColor();
    REQUIRE(clearColor.r == 0);
    REQUIRE(clearColor.g == 0);
    REQUIRE(clearColor.b == 0);
    REQUIRE(clearColor.a == 255);
}

TEST_CASE("GraphicsDevice can begin", "[GraphicsDevice]") {
    MockGraphicsDevice mockGraphicsDevice;
    Adagio::GraphicsDevice *gd = &mockGraphicsDevice;
    gd->begin();
    REQUIRE(mockGraphicsDevice.hasBegun());
}

TEST_CASE("GraphicsDevice can end", "[GraphicsDevice]") {
    MockGraphicsDevice mockGraphicsDevice;
    Adagio::GraphicsDevice *gd = &mockGraphicsDevice;
    gd->begin();
    gd->end();
    REQUIRE(mockGraphicsDevice.hasEnded());
}

TEST_CASE("GraphicsDevice can draw a sprite", "[GraphicsDevice]") {
    MockGraphicsDevice mockGraphicsDevice;
    Adagio::GraphicsDevice *gd = &mockGraphicsDevice;
    Texture2D tex;
    Adagio::SpriteState sprite;
    sprite.texture = &tex;
    sprite.active = true;
    sprite.rotation = 1337;
    sprite.draw(gd);
    auto drawnSprite = mockGraphicsDevice.getDrawnSprite();
    REQUIRE(drawnSprite->rotation == 1337);
    REQUIRE(drawnSprite->texture == &tex);
}

TEST_CASE("GraphicsDevice can draw text", "[GraphicsDevice]") {
    MockGraphicsDevice mockGraphicsDevice;
    Adagio::GraphicsDevice *gd = &mockGraphicsDevice;
    Adagio::TextState text;
    text.text = "Potato";
    text.active = true;
    text.draw(gd);
    auto drawnText = mockGraphicsDevice.getDrawnText();
    std::string drawnString(drawnText->text);
    REQUIRE(drawnString == "Potato");
}

TEST_CASE("MockGraphicsDevice registers renders in call order", "[GraphicsDevice]") {
    MockGraphicsDevice mockGraphicsDevice;
    Adagio::GraphicsDevice *gd = &mockGraphicsDevice;
    Adagio::SpriteState sprite1;
    Adagio::SpriteState sprite2;
    Adagio::TextState text;
    Texture2D tex;
    Texture2D tex2;
    sprite1.texture = &tex;
    sprite2.texture = &tex2;
    sprite1.active = true;
    sprite2.active = true;
    text.active = true;
    text.text = "Potatey";

    sprite1.draw(gd);
    text.draw(gd);
    sprite2.draw(gd);

    std::vector<Adagio::RenderState *> renders = *mockGraphicsDevice.getDrawnObjects();
    REQUIRE(renders.size() == 3);

    auto *drawnSprite1 = dynamic_cast<Adagio::SpriteState *>(renders[0]);
    auto *drawnText = dynamic_cast<Adagio::TextState *>(renders[1]);
    auto *drawnSprite2 = dynamic_cast<Adagio::SpriteState *>(renders[2]);
    std::string drawnString(drawnText->text);

    REQUIRE(drawnSprite1->texture == &tex);
    REQUIRE(drawnString == "Potatey");
    REQUIRE(drawnSprite2->texture == &tex2);
}

TEST_CASE("MockGraphicsDevice clears the drawnObjects list after begin()", "[GraphicsDevice]") {
    MockGraphicsDevice mockGraphicsDevice;
    Adagio::GraphicsDevice *gd = &mockGraphicsDevice;
    Adagio::SpriteState s;
    s.draw(gd);
    mockGraphicsDevice.begin();
    REQUIRE(mockGraphicsDevice.getDrawnObjects()->empty());
}

TEST_CASE("GraphicsDevice can set clear color", "[GraphicsDevice]") {
    MockGraphicsDevice mockGraphicsDevice;
    Adagio::GraphicsDevice *gd = &mockGraphicsDevice;
    gd->setClearColor(1, 2, 3, 4);
    Color clearColor = mockGraphicsDevice.getClearColor();
    REQUIRE(clearColor.r == 1);
    REQUIRE(clearColor.g == 2);
    REQUIRE(clearColor.b == 3);
    REQUIRE(clearColor.a == 4);
}
