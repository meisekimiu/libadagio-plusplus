#include "MockGamepad.h"

bool MockGamepad::isButtonDown(Adagio::GamepadIndex gamepad, Adagio::GamepadButton button) {
    auto &map = buttons[gamepad];
    if (map.find(button) != map.end()) {
        return map[button];
    }
    return false;
}

bool MockGamepad::isButtonUp(Adagio::GamepadIndex gamepad, Adagio::GamepadButton button) {
    return !isButtonDown(gamepad, button);
}

float MockGamepad::getAxisValue(Adagio::GamepadIndex gamepad, Adagio::GamepadButton axis) {
    auto &map = axes[gamepad];
    if (map.find(axis) != map.end()) {
        return map[axis];
    }
    return 0.f;
}

void MockGamepad::pressButton(Adagio::GamepadIndex gamepad, Adagio::GamepadButton button) {
    buttons[gamepad][button] = true;
}

void MockGamepad::releaseButton(Adagio::GamepadIndex gamepad, Adagio::GamepadButton button) {
    buttons[gamepad][button] = false;
}

void MockGamepad::setAxis(Adagio::GamepadIndex gamepad, Adagio::GamepadButton button, float value) {
    axes[gamepad][button] = value;
}
