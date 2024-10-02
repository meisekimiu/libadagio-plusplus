#include <catch2/catch.hpp>
#include "../../src/literals/HashString.h"
#include "../../src/input/InputService.h"
#include "mocks/MockInputs.h"

TEST_CASE("InputService", "[input]") {
    Adagio::InputService inputService;
    MockInputs mocks;

    inputService.addHandler(&mocks.keyboard);
    inputService.addHandler(&mocks.mouse);
    inputService.addHandler(&mocks.gamepad);

    SECTION("It can update all input methods") {
        inputService.actions.registerActionButton("test"_hs, Adagio::Input::Keyboard, 1);
        mocks.gamepad.pressButton(1, 1);
        mocks.mouse.pressButton(1);
        mocks.keyboard.pressKey(1);
        inputService.update();
        REQUIRE(inputService.actions.isActionDown("test"_hs));
        REQUIRE(inputService.gamepad.byIndex(1).isButtonDown(1));
        REQUIRE(inputService.mouse.isButtonDown(1));
        REQUIRE(inputService.keyboard.isKeyDown(1));
    }
}
