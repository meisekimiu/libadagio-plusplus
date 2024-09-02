#include "../../../src/game/components/events/hooks/MessageInboxHooks.h"
#include "../../../src/game/components/events/MessageInbox.h"
#include "../../../src/game/components/CollisionRadius.h"
#include "../../../src/game/components/Position.h"
#include "../../../src/game/systems/DetectCollision.h"
#include "../EcsTestingHarness.h"
#include <catch2/catch.hpp>

static EcsTestingHarness harness;

struct TagA {
};
struct TagB {
};
struct TestStruct {
    bool importantData{false};
};

TEST_CASE("DetectCollision: No components defined", "[system][Collision]") {
    harness.reset();
    REQUIRE_NOTHROW(DetectCollision<TagA, TagB>(harness.registry, harness.stats,
                                                harness.stateMachine));
    REQUIRE_NOTHROW(DetectCollision<TagA, TestStruct>(harness.registry, harness.stats,
                                                      harness.stateMachine));
}

TEST_CASE("Detect Collision: Fires if components fully intersect", "[system][Collision]") {
    harness.reset();
    harness.registry.on_construct<MessageInbox>().connect<&RegisterInboxWithMessageService>();
    harness.registry.on_destroy<MessageInbox>().connect<&UnregisterInboxWithMessageService>();
    auto entityA = harness.registry.create();
    auto entityB = harness.registry.create();
    harness.registry.emplace<Position>(entityA, Adagio::Vector2d{0, 0});
    auto &positionB = harness.registry.emplace<Position>(entityB, Adagio::Vector2d{0, 0});
    harness.registry.emplace<CollisionRadius>(entityA, Adagio::Vector2d{0, 0}, 1);
    harness.registry.emplace<CollisionRadius>(entityB, Adagio::Vector2d{0, 0}, 1);
    harness.registry.emplace<TagA>(entityA);
    harness.registry.emplace<TagB>(entityB);
    auto &inbox = harness.registry.emplace<MessageInbox>(entityA);

    harness.testSystemFrame(DetectCollision<TagA, TagB>);

    REQUIRE(inbox.messages.size() == 1);

    SECTION("Include both radii in the equation") {
        inbox.messages.shift();
        positionB.position.x = 1.5;

        harness.testSystemFrame(DetectCollision<TagA, TagB>);

        REQUIRE(inbox.messages.size() == 1);
    }

    SECTION("Do not fire once an entity is too far away") {
        inbox.messages.shift();
        positionB.position.x = 2.5;

        harness.testSystemFrame(DetectCollision<TagA, TagB>);

        REQUIRE(inbox.messages.empty());
    }
}
