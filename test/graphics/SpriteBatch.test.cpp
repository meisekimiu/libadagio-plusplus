#include <catch2/catch.hpp>
#include "../../src/graphics/SpriteBatch.h"

class TestingSpriteBatch : public Adagio::SpriteBatch {
    int renderingQueueCapacity;

public:
    TestingSpriteBatch() {
        renderingQueueCapacity = static_cast<int>(renderingQueue.capacity());
    }

    int getCapacity() const {
        return renderingQueueCapacity;
    }
};

TEST_CASE("SpriteBatch exists", "[SpriteBatch]") {
    Adagio::SpriteBatch sb;
    REQUIRE(sb.clearColor.r == 0);
    REQUIRE(sb.clearColor.g == 0);
    REQUIRE(sb.clearColor.b == 0);
    REQUIRE(sb.clearColor.a == 255);
}

TEST_CASE("SpriteBatch reserves a specific size in rendering queue", "[SpriteBatch]") {
    Adagio::SpriteBatch::queueReservation = 42;
    TestingSpriteBatch sb;
    REQUIRE(sb.getCapacity() == 42);
}
