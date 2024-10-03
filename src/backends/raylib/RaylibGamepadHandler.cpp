#include <raylib.h>
#include "RaylibGamepadHandler.h"

float RaylibGamepadHandler::getAxisValue(Adagio::GamepadIndex gamepad, Adagio::GamepadButton axis) {
    if (IsGamepadAvailable(gamepad)) {
        return GetGamepadAxisMovement(gamepad, axis);
    }
    return 0;
}

bool RaylibGamepadHandler::isButtonDown(Adagio::GamepadIndex gamepad, Adagio::GamepadButton button) {
    if (IsGamepadAvailable(gamepad)) {
        return IsGamepadButtonDown(gamepad, button);
    }
    return false;
}

bool RaylibGamepadHandler::isButtonUp(Adagio::GamepadIndex gamepad, Adagio::GamepadButton button) {
    if (IsGamepadAvailable(gamepad)) {
        return IsGamepadButtonUp(gamepad, button);
    }
    return true;
}
