#include <catch2/catch.hpp>
#include "../../src/graphics/SpriteBatch.h"
#include "MockGraphicsDevice.h"

class TestingSpriteBatch : public Adagio::SpriteBatch {
    int renderingQueueCapacity;

public:
    explicit TestingSpriteBatch(MockGraphicsDevice *gd) : Adagio::SpriteBatch(gd) {
        gd->reset();
        renderingQueueCapacity = static_cast<int>(renderingQueue.capacity());
    }

    [[nodiscard]] int getCapacity() const {
        return renderingQueueCapacity;
    }

    [[nodiscard]] Adagio::GraphicsDevice *getGraphicsDevice() const {
        return graphicsDevice;
    }
};

MockGraphicsDevice gd;

TEST_CASE("SpriteBatch exists", "[SpriteBatch]") {
    Adagio::SpriteBatch::queueReservation = 5;
    TestingSpriteBatch sb(&gd);
    REQUIRE(sb.getGraphicsDevice() == &gd);
}

TEST_CASE("SpriteBatch reserves a specific size in rendering queue", "[SpriteBatch]") {
    Adagio::SpriteBatch::queueReservation = 42;
    TestingSpriteBatch sb(&gd);
    REQUIRE(sb.getCapacity() == 42);
    Adagio::SpriteBatch::queueReservation = 5;
}

TEST_CASE("TestingSpriteBatch resets the GraphicsDevice", "[SpriteBatch]") {
    Adagio::SpriteState sprite;
    gd.setClearColor(127, 127, 127, 127);
    sprite.draw(&gd);
//    gd.drawTexture(&sprite);
    TestingSpriteBatch sb(&gd);
    Color clearColor = gd.getClearColor();
    REQUIRE(clearColor.r == 0);
    REQUIRE(clearColor.g == 0);
    REQUIRE(clearColor.b == 0);
    REQUIRE(clearColor.a == 255);
    REQUIRE(gd.getDrawnObjects()->empty());
}

TEST_CASE("SpriteBatch can call begin", "[SpriteBatch]") {
    TestingSpriteBatch testSb(&gd);
    Adagio::SpriteBatch *sb = &testSb;
    sb->begin();
    REQUIRE(gd.hasBegun());
}

TEST_CASE("SpriteBatch can call end", "[SpriteBatch]") {
    TestingSpriteBatch testSb(&gd);
    Adagio::SpriteBatch *sb = &testSb;
    sb->end();
    REQUIRE(gd.hasEnded());
}

TEST_CASE("SpriteBatch can set clear color", "[SpriteBatch]") {
    TestingSpriteBatch testSb(&gd);
    Adagio::SpriteBatch *sb = &testSb;
    sb->setClearColor(1, 2, 3, 4);
    Color c = gd.getClearColor();
    REQUIRE(c.r == 1);
    REQUIRE(c.g == 2);
    REQUIRE(c.b == 3);
    REQUIRE(c.a == 4);
}

TEST_CASE("SpriteBatch can generate a SpriteState", "[SpriteBatch]") {
    TestingSpriteBatch testSb(&gd);
    Adagio::SpriteBatch *sb = &testSb;
    Texture2D texture;
    auto sprite = sb->draw(texture, {42, 151}, 3);
    REQUIRE(sprite->destination.x == 42);
    REQUIRE(sprite->destination.y == 151);
    REQUIRE(sprite->zIndex == 3);
}

TEST_CASE("SpriteBatch can generate a TextState", "[SpriteBatch]") {
    TestingSpriteBatch testSb(&gd);
    Adagio::SpriteBatch *sb = &testSb;
    auto text = sb->drawText("Potato", {42, 151}, 3);
    REQUIRE(text->position.x == 42);
    REQUIRE(text->position.y == 151);
    REQUIRE(text->zIndex == 3);
    std::string drawnString(text->text);
    REQUIRE(drawnString == "Potato");
}

TEST_CASE("SpriteBatch renders things in order after calling end()", "[SpriteBatch]") {
    TestingSpriteBatch testSb(&gd);
    Adagio::SpriteBatch *sb = &testSb;
    Texture2D texture;
    sb->begin();
    sb->draw(texture, {0, 0});
    sb->drawText("Potato", {0, 0});
    sb->end();

    std::vector<Adagio::RenderState *> renders = *gd.getDrawnObjects();
    REQUIRE(renders.size() == 2);
    auto *drawnSprite = dynamic_cast<Adagio::SpriteState *>(renders[0]);
    auto *drawnText = dynamic_cast<Adagio::TextState *>(renders[1]);
    std::string drawnString = drawnText->text;

    REQUIRE(drawnSprite->texture == &texture);
    REQUIRE(drawnString == "Potato");
}

TEST_CASE("SpriteBatch sorts by z-order", "[SpriteBatch]") {
    TestingSpriteBatch testSb(&gd);
    Adagio::SpriteBatch *sb = &testSb;
    Texture2D texture;
    sb->begin();
    sb->draw(texture, {0, 0}, 2);
    sb->drawText("Potato", {0, 0}, 1);
    sb->end();

    std::vector<Adagio::RenderState *> renders = *gd.getDrawnObjects();
    auto *drawnSprite = dynamic_cast<Adagio::SpriteState *>(renders[1]);
    auto *drawnText = dynamic_cast<Adagio::TextState *>(renders[0]);
    std::string drawnString = drawnText->text;

    REQUIRE(drawnSprite->texture == &texture);
    REQUIRE(drawnString == "Potato");
}

TEST_CASE("SpriteBatch preserves call order when z-indexes are equal", "[SpriteBatch]") {
    TestingSpriteBatch testSb(&gd);
    Adagio::SpriteBatch *sb = &testSb;
    Texture2D texture;
    sb->begin();
    sb->draw(texture, {0, 0}, 2);
    sb->drawText("Potato", {0, 0}, 1);
    sb->drawText("Tomato", {0, 0}, 1);
    sb->end();

    std::vector<Adagio::RenderState *> renders = *gd.getDrawnObjects();
    auto *drawnText = dynamic_cast<Adagio::TextState *>(renders[0]);
    auto *drawnText2 = dynamic_cast<Adagio::TextState *>(renders[1]);
    std::string drawnString = drawnText->text;
    std::string drawnString2 = drawnText2->text;


    REQUIRE(drawnString == "Potato");
    REQUIRE(drawnString2 == "Tomato");
}

TEST_CASE("SpriteBatch pools SpriteState objects", "[SpriteBatch]") {
    TestingSpriteBatch testSb(&gd);
    Adagio::SpriteBatch *sb = &testSb;
    Adagio::SpriteState *spritePtr1;
    Adagio::SpriteState *spritePtr2;
    Texture2D tex;
    sb->begin();
    spritePtr1 = sb->draw(tex, {0, 0});
    sb->end();
    sb->begin();
    spritePtr2 = sb->draw(tex, {0, 0});
    sb->end();
    REQUIRE(spritePtr1 == spritePtr2);
}

TEST_CASE("SpriteBatch pools TextState objects", "[SpriteBatch]") {
    TestingSpriteBatch testSb(&gd);
    Adagio::SpriteBatch *sb = &testSb;
    Adagio::TextState *textPtr1;
    Adagio::TextState *textPtr2;
    sb->begin();
    textPtr1 = sb->drawText("Hello World", {0, 0});
    sb->end();
    sb->begin();
    textPtr2 = sb->drawText("why do they call it oven when you of in the cold food of out hot eat the food", {0, 0});
    sb->end();
    REQUIRE(textPtr1 == textPtr2);
}
