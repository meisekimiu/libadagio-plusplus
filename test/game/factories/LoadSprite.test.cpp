#include <catch2/catch.hpp>
#include "../../../src/game/factories/LoadSprite.h"
#include "../harness/MockTextureLibrary.h"


TEST_CASE("It can make a basic Sprite object", "[factory][LoadSprite]") {
    auto textureMan = MockTextureLibrary();
    auto sprite = loadSprite("test.jpg", textureMan);

    REQUIRE(sprite.texture.handle == 0xcafe);
    REQUIRE(sprite.texture.getSecretId() == 0xcafe);
    REQUIRE(sprite.position.x == 0);
    REQUIRE(sprite.position.y == 0);
    REQUIRE(sprite.zIndex == 0);
}
