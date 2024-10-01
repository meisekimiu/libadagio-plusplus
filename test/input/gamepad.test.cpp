#include <catch2/catch.hpp>
#include "../../src/input/gamepad/GamepadState.h"
#include "mocks/MockGamepad.h"

TEST_CASE("GamepadState", "[input][gamepad]") {
    Adagio::GamepadState gamepadState(1);
    MockGamepad gamepad;
    gamepadState.setHandler(&gamepad);

    SECTION("Button state") {
        SECTION("It can query an empty gamepad state") {
            REQUIRE_FALSE(gamepadState.isButtonDown(1));
            REQUIRE(gamepadState.isButtonUp(1));
            REQUIRE_FALSE(gamepadState.hasButtonPressStarted(1));
            REQUIRE_FALSE(gamepadState.hasButtonPressEnded(1));
        }

        SECTION("It can detect a button press") {
            gamepad.pressButton(1, 1);
            REQUIRE_FALSE(gamepadState.isButtonDown(1));
            gamepadState.update();
            REQUIRE(gamepadState.isButtonDown(1));
            REQUIRE(gamepadState.hasButtonPressStarted(1));
            REQUIRE_FALSE(gamepadState.isButtonUp(1));
            REQUIRE_FALSE(gamepadState.hasButtonPressEnded(1));
            gamepadState.update();
            REQUIRE(gamepadState.isButtonDown(1));
            REQUIRE_FALSE(gamepadState.hasButtonPressStarted(1));
            REQUIRE_FALSE(gamepadState.isButtonUp(1));
            REQUIRE_FALSE(gamepadState.hasButtonPressEnded(1));
        }

        SECTION("It can detect a button release") {
            gamepad.pressButton(1, 1);
            gamepadState.update();
            gamepad.releaseButton(1, 1);
            gamepadState.update();
            REQUIRE_FALSE(gamepadState.isButtonDown(1));
            REQUIRE_FALSE(gamepadState.hasButtonPressStarted(1));
            REQUIRE(gamepadState.isButtonUp(1));
            REQUIRE(gamepadState.hasButtonPressEnded(1));
            gamepadState.update();
            REQUIRE_FALSE(gamepadState.isButtonDown(1));
            REQUIRE_FALSE(gamepadState.hasButtonPressStarted(1));
            REQUIRE(gamepadState.isButtonUp(1));
            REQUIRE_FALSE(gamepadState.hasButtonPressEnded(1));
        }
    }

    SECTION("Axis state") {
        SECTION("It can query an empty axis state") {
            REQUIRE(gamepadState.getAxisValue(1) == 0);
        }

        SECTION("It can query a single axis") {
            gamepad.setAxis(1, 1, 0.5f);
            REQUIRE(gamepadState.getAxisValue(1) == 0);
            gamepadState.update();
            REQUIRE(gamepadState.getAxisValue(1) == 0.5f);
            gamepad.setAxis(1, 1, -0.5f);
            gamepadState.update();
            REQUIRE(gamepadState.getAxisValue(1) == -0.5f);
        }
    }
}
