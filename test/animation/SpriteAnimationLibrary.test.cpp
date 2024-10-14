#include "../../src/animation/SpriteAnimationLibrary.h"
#include "../../src/literals/HashString.h"
#include <catch2/catch.hpp>

TEST_CASE("SpriteAnimationLibrary", "[animation]") {
    Adagio::SpriteAnimationLibrary animLibrary;

    SECTION("It throws an error when fetching an unregisterd animation") {
        REQUIRE_THROWS(animLibrary.getAnimation("unregistered"_hs));
    }

    SECTION("It can create an animation") {
        Adagio::SpriteAnimationFrame frames[] = {{1.0, {0, 0, 32, 32}}};
        animLibrary.createAnimation("moveLeft"_hs, 1, frames);
        const Adagio::SpriteAnimation &animation = animLibrary.getAnimation("moveLeft"_hs);
        REQUIRE(animation.name == "moveLeft"_hs);
        REQUIRE(animation.frameLength == 1);
        REQUIRE_FALSE(animation.loop);
        REQUIRE(animation.frames[0].duration == 1.0);
        REQUIRE(animation.frames[0].clip.x() == 0);
        REQUIRE(animation.frames[0].clip.y() == 0);
        REQUIRE(animation.frames[0].clip.width() == 32);
        REQUIRE(animation.frames[0].clip.height() == 32);
        REQUIRE(animation.frames != frames);
    }

    SECTION("It can store multiple animations") {
        Adagio::SpriteAnimationFrame framesA[] = {{1.0, {0, 0, 32, 32}}};
        Adagio::SpriteAnimationFrame framesB[] = {{1.0, {0, 0, 64, 64}}};
        animLibrary.createAnimation("moveLeft"_hs, 1, framesA);
        animLibrary.createAnimation("moveRight"_hs, 1, framesB);
        REQUIRE(animLibrary.getAnimation("moveRight"_hs).frames - animLibrary.getAnimation("moveLeft"_hs).frames == 1);
    }

    SECTION("It can free a specific animation") {
        Adagio::SpriteAnimationFrame framesA[] = {{1.0, {0, 0, 32, 32}}};
        Adagio::SpriteAnimationFrame framesB[] = {{1.0, {0, 0, 64, 64}}};
        Adagio::SpriteAnimationFrame framesC[] = {{1.0, {0,  0,  32, 32}},
                                                  {1.0, {32, 32, 32, 32}}};
        animLibrary.createAnimation("moveLeft"_hs, 1, framesA);
        animLibrary.createAnimation("moveRight"_hs, 1, framesB);
        animLibrary.freeAnimation("moveLeft"_hs);
        REQUIRE_THROWS(animLibrary.getAnimation("moveLeft"_hs));
        animLibrary.createAnimation("moveUp"_hs, 2, framesC);
        animLibrary.createAnimation("moveLeft"_hs, 1, framesA);
        REQUIRE(animLibrary.getAnimation("moveRight"_hs).frames - animLibrary.getAnimation("moveLeft"_hs).frames == 1);
    }

    SECTION("It can free all animations") {
        Adagio::SpriteAnimationFrame frames[] = {{1.0, {0, 0, 32, 32}}};
        auto initialLeft = animLibrary.createAnimation("moveLeft"_hs, 1, frames);
        animLibrary.createAnimation("moveRight"_hs, 1, frames);
        animLibrary.clear();
        REQUIRE_THROWS(animLibrary.getAnimation("moveLeft"_hs));
        REQUIRE_THROWS(animLibrary.getAnimation("moveRight"_hs));
        auto newLeft = animLibrary.createAnimation("moveLeft"_hs, 1, frames);
        REQUIRE(initialLeft.frames == newLeft.frames);
    }
}
