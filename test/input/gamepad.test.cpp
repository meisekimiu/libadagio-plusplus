#include <catch2/catch.hpp>
#include "../../src/input/gamepad/GamepadState.h"

struct MockGamepad : public Adagio::GamepadHandler {
    std::unordered_map<Adagio::GamepadButton, bool> buttons;
    std::unordered_map<Adagio::GamepadButton, float> axes;

    bool
    isButtonDown(Adagio::GamepadIndex gamepad, Adagio::GamepadButton button) override {
        if (buttons.find(button) != buttons.end()) {
            return buttons[button];
        }
        return false;
    }

    bool
    isButtonUp(Adagio::GamepadIndex gamepad, Adagio::GamepadButton button) override {
        return !isButtonDown(gamepad, button);
    }

    float getAxisValue(Adagio::GamepadIndex gamepad, Adagio::GamepadButton axis) override {
        if (axes.find(axis) != axes.end()) {
            return axes[axis];
        }
        return 0.f;
    }

    void pressButton(Adagio::GamepadButton button) {
        buttons[button] = true;
    }

    void releaseButton(Adagio::GamepadButton button) {
        buttons[button] = false;
    }

    void setAxis(Adagio::GamepadButton button, float value) {
        axes[button] = value;
    }
};

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
            gamepad.pressButton(1);
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
            gamepad.pressButton(1);
            gamepadState.update();
            gamepad.releaseButton(1);
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
            gamepad.setAxis(1, 0.5f);
            REQUIRE(gamepadState.getAxisValue(1) == 0);
            gamepadState.update();
            REQUIRE(gamepadState.getAxisValue(1) == 0.5f);
            gamepad.setAxis(1, -0.5f);
            gamepadState.update();
            REQUIRE(gamepadState.getAxisValue(1) == -0.5f);
        }
    }
}
