#include <catch2/catch.hpp>
#include "../EcsTestingHarness.h"
#include "../../../src/game/components/SpriteAnimation.h"
#include "../../../src/game/components/Sprite.h"
#include "../../../src/game/components/SpriteClip.h"
#include "../../../src/game/systems/AnimateSprite.h"

static EcsTestingHarness harness;

static void assertRectEquals(SpriteClip &clip, int x, int y, int w, int h) {
    REQUIRE(clip.source.x() == x);
    REQUIRE(clip.source.y() == y);
    REQUIRE(clip.source.width() == w);
    REQUIRE(clip.source.height() == h);
}

TEST_CASE("AnimateSprite: No components defined", "[renderer][AnimateSprite]") {
    harness.reset();
    REQUIRE_NOTHROW(AnimateSprite(harness.registry, harness.stats, harness.stateMachine));
}

TEST_CASE("AnimateSprite does nothing if no frame data defined", "[renderer][AnimateSprite]") {
    harness.reset();

    auto sprite = harness.registry.create();
    harness.registry.emplace<Sprite>(sprite);
    SpriteClip& clip = harness.registry.emplace<SpriteClip>(sprite, Adagio::RectF{1,2,3,4});
    harness.registry.emplace<SpriteAnimation>(sprite);

    harness.testSystemFrame(AnimateSprite);
    harness.stats.advanceTime(1);
    harness.testSystemFrame(AnimateSprite);

    REQUIRE(clip.source.x() == 1);
    REQUIRE(clip.source.y() == 2);
    REQUIRE(clip.source.width() == 3);
    REQUIRE(clip.source.height() == 4);
}

TEST_CASE("AnimateSprite applies clipping rect when one frame defined", "[renderer][AnimateSprite]") {
    harness.reset();

    auto sprite = harness.registry.create();
    harness.registry.emplace<Sprite>(sprite);
    SpriteClip& clip = harness.registry.emplace<SpriteClip>(sprite, Adagio::RectF{1,2,3,4});
    AnimationFrame frames[] = {
            {1,Adagio::RectI{5,6,7,8}}
    };
    SpriteAnimation &animation = harness.registry.emplace<SpriteAnimation>(sprite);
    animation.frameLength = 1;
    animation.frames = frames;

    harness.testSystemFrame(AnimateSprite);

    REQUIRE(clip.source.x() == 5);
    REQUIRE(clip.source.y() == 6);
    REQUIRE(clip.source.width() == 7);
    REQUIRE(clip.source.height() == 8);
}

TEST_CASE("AnimateSprite picks the correct frame between two frames", "[renderer][AnimateSprite]") {
    harness.reset();

    auto sprite = harness.registry.create();
    harness.registry.emplace<Sprite>(sprite);
    SpriteClip& clip = harness.registry.emplace<SpriteClip>(sprite, Adagio::RectF{1,2,3,4});
    AnimationFrame frames[] = {
            {1,Adagio::RectI{5,6,7,8}},
            {1, Adagio::RectI{9,10,11,12}},
    };
    SpriteAnimation &animation = harness.registry.emplace<SpriteAnimation>(sprite);
    animation.frameLength = 2;
    animation.frames = frames;

    harness.testSystemFrame(AnimateSprite);
    assertRectEquals(clip, 5,6,7,8);
    harness.stats.advanceTime(1.01);
    harness.testSystemFrame(AnimateSprite);
    assertRectEquals(clip, 9, 10, 11, 12);
}

TEST_CASE("AnimateSprite will not go past frame boundaries", "[system][AnimatedSprite]") {
    harness.reset();

    auto sprite = harness.registry.create();
    harness.registry.emplace<Sprite>(sprite);
    SpriteClip& clip = harness.registry.emplace<SpriteClip>(sprite, Adagio::RectF{1,2,3,4});
    AnimationFrame frames[] = {
            {1,Adagio::RectI{5,6,7,8}},
            {100, Adagio::RectI{0xff,0xff,0xff,0xff}},
            // The last frame here is just a "padding frame" that should never be reached
    };
    SpriteAnimation &animation = harness.registry.emplace<SpriteAnimation>(sprite);
    animation.frameLength = 1;
    animation.frames = frames;

    harness.testSystemFrame(AnimateSprite);
    harness.stats.advanceTime(50);
    harness.testSystemFrame(AnimateSprite);

    assertRectEquals(clip, 5, 6, 7, 8);
}

TEST_CASE("AnimateSprite will skip frames if enough time passes between calls", "[system][AnimatedSprite]") {
    harness.reset();

    auto sprite = harness.registry.create();
    harness.registry.emplace<Sprite>(sprite);
    SpriteClip& clip = harness.registry.emplace<SpriteClip>(sprite, Adagio::RectF{1,2,3,4});
    AnimationFrame frames[] = {
            {1,Adagio::RectI{5,6,7,8}},
            {1, Adagio::RectI {9,10,11,12}},
            {100, Adagio::RectI{0xff,0xff,0xff,0xff}},
    };
    SpriteAnimation& animation = harness.registry.emplace<SpriteAnimation>(sprite);
    animation.frameLength = 3;
    animation.frames = frames;

    harness.stats.advanceTime(50);
    harness.testSystemFrame(AnimateSprite);

    assertRectEquals(clip, 0xff, 0xff, 0xff, 0xff);
}

TEST_CASE("AnimateSprite can loop animations", "[system][AnimateSprite]") {
    harness.reset();

    auto sprite = harness.registry.create();
    harness.registry.emplace<Sprite>(sprite);
    SpriteClip& clip = harness.registry.emplace<SpriteClip>(sprite);
    AnimationFrame frames[] = {
            {1,Adagio::RectI{5,6,7,8}},
            {1, Adagio::RectI {9,10,11,12}},
    };
    SpriteAnimation &animation = harness.registry.emplace<SpriteAnimation>(sprite);
    animation.frameLength = 2;
    animation.frames = frames;
    animation.loop = true;

    harness.stats.advanceTime(1.1);
    harness.testSystemFrame(AnimateSprite);
    harness.stats.advanceTime(1.1);
    harness.testSystemFrame(AnimateSprite);


    assertRectEquals(clip, 5, 6, 7, 8);
}

TEST_CASE("AnimateSprite will stop animating non-looping animations", "[system][AnimateSprite]") {
    harness.reset();

    auto sprite = harness.registry.create();
    harness.registry.emplace<Sprite>(sprite);
    SpriteClip& clip = harness.registry.emplace<SpriteClip>(sprite);
    AnimationFrame frames[] = {
            {1,Adagio::RectI{5,6,7,8}},
            {1, Adagio::RectI {9,10,11,12}},
    };
    SpriteAnimation& animation = harness.registry.emplace<SpriteAnimation>(sprite);
    animation.frameLength = 2;
    animation.frames = frames;

    harness.stats.advanceTime(1.5);
    harness.testSystemFrame(AnimateSprite);
    harness.stats.advanceTime(1);
    harness.testSystemFrame(AnimateSprite);

    assertRectEquals(clip, 9, 10, 11, 12);
    REQUIRE(animation.done);
}

TEST_CASE("AnimateSprite will not process an animation that is marked as done", "[system][AnimatedSprite]") {
    harness.reset();

    auto sprite = harness.registry.create();
    harness.registry.emplace<Sprite>(sprite);
    SpriteClip& clip = harness.registry.emplace<SpriteClip>(sprite, Adagio::RectF{1,2,3,4});
    AnimationFrame frames[] = {
            {1,Adagio::RectI{5,6,7,8}},
            {1, Adagio::RectI {9,10,11,12}},
    };
    SpriteAnimation& animation = harness.registry.emplace<SpriteAnimation>(sprite);
    animation.frameLength = 2;
    animation.frames = frames;
    animation.done = true;

    harness.stats.advanceTime(1.5);
    harness.testSystemFrame(AnimateSprite);

    assertRectEquals(clip, 1, 2, 3, 4);
}