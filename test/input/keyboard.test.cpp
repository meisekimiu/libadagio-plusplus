#include <catch2/catch.hpp>
#include "../../src/input/keyboard/KeyboardState.h"

class MockKeyboard : public Adagio::KeyboardHandler {
public:
    std::unordered_map<Adagio::keycode, bool> keys;
    std::vector<Adagio::keycode> pressedKeys;
    std::string buffer;

    void writeChars(const std::string &input) {
        buffer += input;
    }

    void pressKey(Adagio::keycode key) {
        keys[key] = true;
        pressedKeys.push_back(key);
    }

    void releaseKey(Adagio::keycode key) {
        keys[key] = false;
    }

    Adagio::keycode getNextKey() override {
        if (!pressedKeys.empty()) {
            Adagio::keycode key = pressedKeys.back();
            pressedKeys.pop_back();
            return key;
        }
        return 0;
    }

    char getNextChar() override {
        if (buffer.empty()) {
            return 0;
        }
        char c = buffer[0];
        buffer.erase(buffer.begin());
        return c;
    }

    bool isKeyDown(Adagio::keycode key) override {
        if (keys.find(key) != keys.end()) {
            return keys[key];
        }
        return false;
    }

    bool isKeyUp(Adagio::keycode key) override {
        if (keys.find(key) != keys.end()) {
            return !keys[key];
        }
        return true;
    }
};

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
