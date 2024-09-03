#include "../../../src/game/systems/ApplyVelocity.h"
#include "../../../src/game/components/Position.h"
#include "../../../src/game/components/Velocity.h"
#include "../EcsTestingHarness.h"
#include <catch2/catch.hpp>
#include <cmath>

static EcsTestingHarness harness;

static Position &setUpComponents(double direction, double speed);

static bool doubleEquals(double a, double b);

TEST_CASE("ApplyVelocity: No components defined", "[system][ApplyVelocity]") {
    harness.reset();
    REQUIRE_NOTHROW(
            ApplyVelocity(harness.registry, harness.gameServices, harness.stateMachine));
}

TEST_CASE("ApplyVelocity: Does nothing with 0 speed",
          "[system][ApplyVelocity]") {
    Position &pos = setUpComponents(0, 0);

    harness.stats.advanceTime(1);
    harness.testSystemFrame(ApplyVelocity);

    REQUIRE(pos.position.x == 0);
    REQUIRE(pos.position.y == 0);
}

TEST_CASE("ApplyVelocity moves in direction 0", "[system][ApplyVelocity]") {
    Position &pos = setUpComponents(0, 1);

    harness.stats.advanceTime(1.0 / 60);
    harness.testSystemFrame(ApplyVelocity);

    REQUIRE(pos.position.x == 1);
    REQUIRE(pos.position.y == 0);
}

TEST_CASE("ApplyVelocity moves in direction PI/2", "[system][ApplyVelocity]") {
    Position &pos = setUpComponents(M_PI_2, 1);

    harness.stats.advanceTime(1.0 / 60);
    harness.testSystemFrame(ApplyVelocity);

    REQUIRE(doubleEquals(pos.position.x, 0));
    REQUIRE(doubleEquals(pos.position.y, 1));
}

TEST_CASE("ApplyVelocity moves in direction PI/4", "[system][ApplyVelocity]") {
    Position &pos = setUpComponents(M_PI_4, 1);

    harness.stats.advanceTime(1.0 / 60);
    harness.testSystemFrame(ApplyVelocity);

    REQUIRE(doubleEquals(pos.position.x, 1.0 / std::sqrt(2)));
    REQUIRE(doubleEquals(pos.position.y, 1.0 / std::sqrt(2)));
}

TEST_CASE("ApplyVelocity applies speed every 1/60th of a second",
          "[system][ApplyVelocity]") {
    Position &pos = setUpComponents(0, 1);

    harness.stats.advanceTime(1);
    harness.testSystemFrame(ApplyVelocity);

    REQUIRE(doubleEquals(pos.position.x, 60));
    REQUIRE(doubleEquals(pos.position.y, 0));
}

static Position &setUpComponents(double direction, double speed) {
    harness.reset();
    auto entity = harness.registry.create();
    Position &pos =
            harness.registry.emplace<Position>(entity, Adagio::Vector2d{0, 0});
    harness.registry.emplace<Velocity>(entity, direction, speed);

    return pos;
}

static bool doubleEquals(double a, double b) {
    const double delta = 0.0005;
    return std::abs(a - b) < delta;
}
