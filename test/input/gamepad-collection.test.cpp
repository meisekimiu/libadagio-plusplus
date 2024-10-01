#include <catch2/catch.hpp>
#include "../../src/input/gamepad/GamepadCollection.h"
#include "../../src/literals/HashString.h"
#include "mocks/MockGamepad.h"

TEST_CASE("GamepadCollection", "[input][gamepad]") {
    Adagio::GamepadCollection gamepads;
    MockGamepad gamepad;
    gamepads.setHandler(&gamepad);

    SECTION("It can get a gamepad by index") {
        gamepad.pressButton(2, 1);
        gamepads.update();
        auto &gamepadState = gamepads.byIndex(2);
        REQUIRE(gamepadState.isButtonDown(1));
    }

    SECTION("It can create an axis pair") {
        Adagio::Vector2f vec;
        gamepads.createAxisPair("test"_hs, 1, 2);
        gamepad.setAxis(1, 1, 0.5f);
        gamepad.setAxis(1, 2, -0.5f);
        gamepads.update();
        vec = gamepads.readAxisPair("test"_hs, 1);
        REQUIRE(vec.x == 0.5f);
        REQUIRE(vec.y == -0.5f);
        gamepad.setAxis(1, 1, 0.f);
        gamepad.setAxis(1, 2, 0.f);
        gamepads.update();
        vec = gamepads.readAxisPair("test"_hs, 1);
        REQUIRE(vec.x == 0.f);
        REQUIRE(vec.y == 0.f);
    }

    SECTION("It can configure a deadzone for an axis pair") {
        Adagio::Vector2f vec;
        gamepads.createAxisPair("test"_hs, 1, 2);
        gamepads.setAxisPairDeadzone("test"_hs, 0.5);
        gamepad.setAxis(1, 1, 0.25f);
        gamepad.setAxis(1, 2, 0);
        gamepads.update();
        vec = gamepads.readAxisPair("test"_hs, 1);
        REQUIRE(vec.x == 0);
        REQUIRE(vec.y == 0);
        gamepad.setAxis(1, 1, 0.5f);
        gamepads.update();
        vec = gamepads.readAxisPair("test"_hs, 1);
        REQUIRE(vec.x == 0.5f);
        REQUIRE(vec.y == 0);
        gamepad.setAxis(1, 1, 0.4f);
        gamepad.setAxis(1, 2, 0.4f);
        gamepads.update();
        vec = gamepads.readAxisPair("test"_hs, 1);
        REQUIRE(vec.x > 0);
        REQUIRE(vec.y > 0);
    }

    SECTION("It can configure a maxzone for an axis pair") {
        Adagio::Vector2f vec;
        gamepads.createAxisPair("test"_hs, 1, 2);
        gamepads.setAxisPairMaxzone("test"_hs, 0.5f);
        gamepad.setAxis(1, 1, 0.5f);
        gamepad.setAxis(1, 2, 0);
        gamepads.update();
        vec = gamepads.readAxisPair("test"_hs, 1);
        REQUIRE(vec.x == 1);
        REQUIRE(vec.y == 0);
        gamepad.setAxis(1, 1, 0.4f);
        gamepads.update();
        vec = gamepads.readAxisPair("test"_hs, 1);
        REQUIRE(vec.x - 0.4f < 0.001f);
        REQUIRE(vec.y == 0);
        gamepad.setAxis(1, 1, 120);
        gamepad.setAxis(1, 2, 120);
        gamepads.update();
        vec = gamepads.readAxisPair("test"_hs, 1);
        REQUIRE(std::abs(vec.magnitude() - 1) < 0.00001f);
    }
}
