#include "GamepadState.h"

namespace Adagio {
    GamepadState::GamepadState(GamepadIndex index) {
        this->index = index;
    }

    void GamepadState::setHandler(GamepadHandler *h) {
        handler = h;
    }

    bool GamepadState::isButtonDown(GamepadButton button) const {
        return buttons[button].isDown;
    }

    bool GamepadState::isButtonUp(GamepadButton button) const {
        return !isButtonDown(button);
    }

    bool GamepadState::hasButtonPressStarted(GamepadButton button) const {
        return buttons[button].isPressed;
    }

    bool GamepadState::hasButtonPressEnded(GamepadButton button) const {
        return buttons[button].isReleased;
    }

    void GamepadState::update() {
        for (char i = 0; i < MAX_BUTTONS; i++) {
            const bool isDown = handler->isButtonDown(index, i);
            buttons[i].isPressed = !buttons[i].isDown && isDown;
            buttons[i].isReleased = buttons[i].isDown && handler->isButtonUp(index, i);
            buttons[i].isDown = isDown;
        }
        for (char i = 0; i < MAX_AXES; i++) {
            axes[i] = handler->getAxisValue(index, i);
        }
    }

    float GamepadState::getAxisValue(GamepadButton axis) const {
        return axes[axis];
    }
} // Adagio
