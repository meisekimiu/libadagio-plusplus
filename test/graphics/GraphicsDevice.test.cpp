#include <catch2/catch.hpp>
#include "MockGraphicsDevice.h"

TEST_CASE("GraphicsDevice exists", "[GraphicsDevice]") {
    MockGraphicsDevice gd;
    REQUIRE_FALSE(gd.hasBegun());
    REQUIRE_FALSE(gd.hasEnded());
    REQUIRE_FALSE(gd.getDrawnSprite());
    REQUIRE_FALSE(gd.getDrawnText());
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
    Adagio::SpriteState sprite;
    gd->drawTexture(&sprite);
    REQUIRE(mockGraphicsDevice.getDrawnSprite() == &sprite);
}

TEST_CASE("GraphicsDevice can draw text", "[GraphicsDevice]") {
    MockGraphicsDevice mockGraphicsDevice;
    Adagio::GraphicsDevice *gd = &mockGraphicsDevice;
    Adagio::TextState text;
    gd->drawText(&text);
    REQUIRE(mockGraphicsDevice.getDrawnText() == &text);
}

TEST_CASE("MockGraphicsDevice registers renders in call order", "[GraphicsDevice]") {
    MockGraphicsDevice mockGraphicsDevice;
    Adagio::SpriteState sprite1;
    Adagio::SpriteState sprite2;
    Adagio::TextState text;
    mockGraphicsDevice.drawTexture(&sprite1);
    mockGraphicsDevice.drawText(&text);
    mockGraphicsDevice.drawTexture(&sprite2);
    std::vector<Adagio::RenderState *> renders = *mockGraphicsDevice.getDrawnObjects();
    REQUIRE(renders.size() == 3);
    REQUIRE(renders[0] == &sprite1);
    REQUIRE(renders[1] == &text);
    REQUIRE(renders[2] == &sprite2);
}

TEST_CASE("MockGraphicsDevice clears the drawnObjects list after begin()", "[GraphicsDevice]") {
    MockGraphicsDevice mockGraphicsDevice;
    Adagio::SpriteState s;
    mockGraphicsDevice.drawTexture(&s);
    mockGraphicsDevice.begin();
    REQUIRE(mockGraphicsDevice.getDrawnObjects()->size() == 0);
}
