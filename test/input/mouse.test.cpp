#include <catch2/catch.hpp>
#include "../../src/input/mouse/MouseState.h"
#include <unordered_map>

struct MockMouse : public Adagio::MouseHandler {
    Adagio::Vector2i coords{0, 0};
    std::unordered_map<Adagio::MouseButton, bool> buttons;
    int cursor{0};

    bool isMouseButtonDown(Adagio::MouseButton btn) override {
        return buttons[btn];
    }

    bool isMouseButtonUp(Adagio::MouseButton btn) override {
        return !buttons[btn];
    }

    Adagio::Vector2i getMouseCoords() override {
        return coords;
    }

    void setMouseCoords(Adagio::Vector2i c) override {
        coords = c;
    }

    void setMouseCursor(Adagio::MouseCursor i) override {
        cursor = i;
    }

    void setMockCoords(int x, int y) {
        coords.x = x;
        coords.y = y;
    }

    void pressButton(Adagio::MouseButton i) {
        buttons[i] = true;
    }

    void releaseButton(Adagio::MouseButton i) {
        buttons[i] = false;
    }
};

TEST_CASE("MouseState", "[input][mouse]") {
    Adagio::MouseState mouseState;
    MockMouse mouse;
    mouseState.setHandler(&mouse);

    SECTION("It can get mouse coords") {
        mouse.setMockCoords(1336, 1235);
        auto nonUpdatedCoords = mouseState.getCursorCoords();
        mouseState.update();
        mouse.setMockCoords(1337, 1234);
        mouseState.update();
        auto result = mouseState.getCursorCoords();
        auto delta = mouseState.getCursorDelta();
        REQUIRE(nonUpdatedCoords.x == 0);
        REQUIRE(nonUpdatedCoords.y == 0);
        REQUIRE(result.x == 1337);
        REQUIRE(result.y == 1234);
        REQUIRE(delta.x == 1);
        REQUIRE(delta.y == -1);
    }

    SECTION("It can query an empty mouse button state") {
        for (char i = 0; i < 3; i++) {
            REQUIRE_FALSE(mouseState.isButtonDown(i));
            REQUIRE(mouseState.isButtonUp(i));
            REQUIRE_FALSE(mouseState.hasClickStarted(i));
            REQUIRE_FALSE(mouseState.hasClickEnded(i));
        }
    }

    SECTION("It can detect a mouse button press") {
        for (char i = 0; i < 3; i++) {
            mouse.pressButton(i);
            mouseState.update();
            REQUIRE(mouseState.isButtonDown(i));
            REQUIRE(mouseState.hasClickStarted(i));
            REQUIRE_FALSE(mouseState.isButtonUp(i));
            REQUIRE_FALSE(mouseState.hasClickEnded(i));
            mouseState.update();
            REQUIRE_FALSE(mouseState.hasClickStarted(i));
            mouse.releaseButton(i);
        }
    }

    SECTION("It can detect a mouse button release") {
        for (char i = 0; i < 3; i++) {
            mouse.pressButton(i);
            mouseState.update();
            mouse.releaseButton(i);
            mouseState.update();
            REQUIRE_FALSE(mouseState.isButtonDown(i));
            REQUIRE_FALSE(mouseState.hasClickStarted(i));
            REQUIRE(mouseState.isButtonUp(i));
            REQUIRE(mouseState.hasClickEnded(i));
            mouseState.update();
            REQUIRE_FALSE(mouseState.hasClickEnded(i));
        }
    }

    SECTION("It can set mouse cursor") {
        mouseState.setCursor(1337);
        REQUIRE(mouse.cursor == 1337);
    }

    SECTION("It can set mouse coords") {
        mouseState.setCursorCoords({123, 456});
        REQUIRE(mouse.coords.x == 123);
        REQUIRE(mouse.coords.y == 456);
    }
}
