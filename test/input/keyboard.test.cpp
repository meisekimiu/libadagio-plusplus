#include <catch2/catch.hpp>
#include "../../src/input/keyboard/KeyboardState.h"
#include "mocks/MockKeyboard.h"

TEST_CASE("KeyboardState", "[input][keyboard]") {
    const Adagio::keycode TEST_KEY_1 = 128;
    MockKeyboard mockKeyboard;
    Adagio::KeyboardState keyboard;
    keyboard.setHandler(&mockKeyboard);

    SECTION("It can query an empty keyboard state") {
        REQUIRE_FALSE(keyboard.isKeyDown(TEST_KEY_1));
        REQUIRE(keyboard.isKeyUp(TEST_KEY_1));
        REQUIRE_FALSE(keyboard.hasKeyPressStarted(TEST_KEY_1));
        REQUIRE_FALSE(keyboard.hasKeyPressEnded(TEST_KEY_1));
    }

    SECTION("It can detect a key press") {
        mockKeyboard.pressKey(TEST_KEY_1);
        keyboard.update();
        REQUIRE(keyboard.isKeyDown(TEST_KEY_1));
        REQUIRE(keyboard.hasKeyPressStarted(TEST_KEY_1));
        keyboard.update();
        REQUIRE(keyboard.isKeyDown(TEST_KEY_1));
        REQUIRE_FALSE(keyboard.hasKeyPressStarted(TEST_KEY_1));
    }

    SECTION("It can detect a key release") {
        mockKeyboard.pressKey(TEST_KEY_1);
        keyboard.update();
        REQUIRE_FALSE(keyboard.isKeyUp(TEST_KEY_1));
        mockKeyboard.releaseKey(TEST_KEY_1);
        keyboard.update();
        REQUIRE(keyboard.isKeyUp(TEST_KEY_1));
        REQUIRE(keyboard.hasKeyPressEnded(TEST_KEY_1));
        keyboard.update();
        REQUIRE(keyboard.isKeyUp(TEST_KEY_1));
        REQUIRE_FALSE(keyboard.hasKeyPressEnded(TEST_KEY_1));
    }

    SECTION("It can read from a text input buffer") {
        mockKeyboard.writeChars("potato");
        keyboard.update();
        std::string input = keyboard.readTextBuffer();
        REQUIRE(input == "potato");
        keyboard.update();
        input = keyboard.readTextBuffer();
        REQUIRE(input.empty());
    }
}
