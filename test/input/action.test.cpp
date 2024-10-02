#include <catch2/catch.hpp>
#include "../../src/literals/HashString.h"
#include "../../src/input/gamepad/GamepadCollection.h"
#include "../../src/input/actions/ActionState.h"
#include "mocks/MockInputs.h"

TEST_CASE("Input Actions", "[input][actions]") {
    MockInputs mocks;

    Adagio::KeyboardState keyboard;
    Adagio::MouseState mouse;
    Adagio::GamepadCollection gamepad;
    Adagio::ActionState actions;

    keyboard.setHandler(&mocks.keyboard);
    mouse.setHandler(&mocks.mouse);
    gamepad.setHandler(&mocks.gamepad);

    actions.linkInput(&keyboard);
    actions.linkInput(&mouse);
    actions.linkInput(&gamepad);

    SECTION("It can query an undefined button action") {
        REQUIRE_FALSE(actions.isActionDown("undefined"_hs));
        REQUIRE(actions.isActionUp("undefined"_hs));
        REQUIRE_FALSE(actions.hasActionStarted("undefined"_hs));
        REQUIRE_FALSE(actions.hasActionEnded("undefined"_hs));
    }

    SECTION("It can query an undefined direction action") {
        Adagio::Vector2f vec = actions.getActionDirection("undefined"_hs);
        REQUIRE(vec.x == 0);
        REQUIRE(vec.y == 0);
    }

    SECTION("It can register an action to a keyboard button") {
        actions.registerActionButton("keyboardKeyOne"_hs, Adagio::Input::Keyboard, 1);
        mocks.keyboard.pressKey(1);
        keyboard.update();
        actions.update();
        REQUIRE(actions.isActionDown("keyboardKeyOne"_hs));
        REQUIRE_FALSE(actions.isActionUp("keyboardKeyOne"_hs));
        REQUIRE(actions.hasActionStarted("keyboardKeyOne"_hs));
        REQUIRE_FALSE(actions.hasActionEnded("keyboardKeyOne"_hs));
        actions.update();
        REQUIRE(actions.isActionDown("keyboardKeyOne"_hs));
        REQUIRE_FALSE(actions.isActionUp("keyboardKeyOne"_hs));
        REQUIRE_FALSE(actions.hasActionStarted("keyboardKeyOne"_hs));
        REQUIRE_FALSE(actions.hasActionEnded("keyboardKeyOne"_hs));
        mocks.keyboard.releaseKey(1);
        keyboard.update();
        actions.update();
        REQUIRE_FALSE(actions.isActionDown("keyboardKeyOne"_hs));
        REQUIRE(actions.isActionUp("keyboardKeyOne"_hs));
        REQUIRE_FALSE(actions.hasActionStarted("keyboardKeyOne"_hs));
        REQUIRE(actions.hasActionEnded("keyboardKeyOne"_hs));
        actions.update();
        REQUIRE_FALSE(actions.isActionDown("keyboardKeyOne"_hs));
        REQUIRE(actions.isActionUp("keyboardKeyOne"_hs));
        REQUIRE_FALSE(actions.hasActionStarted("keyboardKeyOne"_hs));
        REQUIRE_FALSE(actions.hasActionEnded("keyboardKeyOne"_hs));
    }

    SECTION("It can register an action to a mouse button") {
        actions.registerActionButton("mouseBtnOne"_hs, Adagio::Input::Mouse, 1);
        mocks.mouse.pressButton(1);
        mouse.update();
        actions.update();
        REQUIRE(actions.isActionDown("mouseBtnOne"_hs));
        REQUIRE(actions.hasActionStarted("mouseBtnOne"_hs));
    }

    SECTION("It can register an action to a gamepad button") {
        actions.registerActionButton("gamepadButtonA"_hs, Adagio::Input::Gamepad, 1);
        mocks.gamepad.pressButton(1, 1);
        gamepad.update();
        actions.update();
        REQUIRE(actions.isActionDown("gamepadButtonA"_hs));
        REQUIRE(actions.hasActionStarted("gamepadButtonA"_hs));
    }

    SECTION("It can register multiple input buttons to one action") {
        actions.registerActionButton("jump"_hs, Adagio::Input::Keyboard, 1);
        actions.registerActionButton("jump"_hs, Adagio::Input::Mouse, 1);
        actions.registerActionButton("jump"_hs, Adagio::Input::Gamepad, 1);
        mocks.keyboard.pressKey(1);
        keyboard.update();
        actions.update();
        REQUIRE(actions.isActionDown("jump"_hs));
        REQUIRE(actions.hasActionStarted("jump"_hs));
        mocks.mouse.pressButton(1);
        mocks.keyboard.releaseKey(1);
        keyboard.update();
        mouse.update();
        actions.update();
        REQUIRE(actions.isActionDown("jump"_hs));
        REQUIRE_FALSE(actions.hasActionStarted("jump"_hs));
        mocks.mouse.releaseButton(1);
        mocks.gamepad.pressButton(1, 1);
        mouse.update();
        gamepad.update();
        actions.update();
        REQUIRE(actions.isActionDown("jump"_hs));
        REQUIRE_FALSE(actions.hasActionStarted("jump"_hs));
        mocks.gamepad.releaseButton(1, 1);
        gamepad.update();
        actions.update();
        REQUIRE_FALSE(actions.isActionDown("jump"_hs));
        REQUIRE(actions.hasActionEnded("jump"_hs));
    }

    SECTION("It can register a 2D directional input on keyboard") {
        Adagio::Vector2f vec;
        actions.registerActionDirectionKeys("move"_hs, 1, 2, 3, 4);
        mocks.keyboard.pressKey(1);
        keyboard.update();
        actions.update();
        vec = actions.getActionDirection("move"_hs);
        REQUIRE(vec.x == -1);
        REQUIRE(vec.y == 0);
        mocks.keyboard.releaseKey(1);
        mocks.keyboard.pressKey(2);
        keyboard.update();
        actions.update();
        vec = actions.getActionDirection("move"_hs);
        REQUIRE(vec.x == 0);
        REQUIRE(vec.y == 1);
        mocks.keyboard.releaseKey(2);
        mocks.keyboard.pressKey(3);
        keyboard.update();
        actions.update();
        vec = actions.getActionDirection("move"_hs);
        REQUIRE(vec.x == 0);
        REQUIRE(vec.y == -1);
        mocks.keyboard.releaseKey(3);
        mocks.keyboard.pressKey(4);
        keyboard.update();
        actions.update();
        vec = actions.getActionDirection("move"_hs);
        REQUIRE(vec.x == 1);
        REQUIRE(vec.y == 0);
    }

    SECTION("It normalizes diagonal keyboard input") {
        Adagio::Vector2f vec;
        actions.registerActionDirectionKeys("move"_hs, 1, 2, 3, 4);
        mocks.keyboard.pressKey(1);
        mocks.keyboard.pressKey(3);
        keyboard.update();
        actions.update();
        vec = actions.getActionDirection("move"_hs);
        REQUIRE(vec.x == vec.y);
        REQUIRE(std::abs(vec.magnitude() - 1) < 0.00001);
    }

    SECTION("It can register a 2D directional input on gamepad") {
        Adagio::Vector2f vec;
        gamepad.createAxisPair("move"_hs, 1, 2);
        actions.registerActionDirectionAxes("move"_hs, "move"_hs);
        mocks.gamepad.setAxis(1, 1, 0.5);
        mocks.gamepad.setAxis(1, 2, -0.5);
        gamepad.update();
        actions.update();
        vec = actions.getActionDirection("move"_hs);
        REQUIRE(vec.x == 0.5);
        REQUIRE(vec.y == -0.5);
    }

    SECTION("It can handle both keyboard and gamepad directional input") {
        Adagio::Vector2f vec;
        gamepad.createAxisPair("move"_hs, 1, 2);
        actions.registerActionDirectionAxes("move"_hs, "move"_hs);
        actions.registerActionDirectionKeys("move"_hs, 1, 2, 3, 4);
        mocks.keyboard.pressKey(1);
        keyboard.update();
        actions.update();
        vec = actions.getActionDirection("move"_hs);
        REQUIRE(vec.x == -1);
        REQUIRE(vec.y == 0);
        mocks.gamepad.setAxis(1, 2, -1);
        keyboard.update();
        gamepad.update();
        actions.update();
        vec = actions.getActionDirection("move"_hs);
        REQUIRE(vec.x == vec.y);
        REQUIRE(std::abs(vec.magnitude() - 1) < 0.00001);
    }
}
