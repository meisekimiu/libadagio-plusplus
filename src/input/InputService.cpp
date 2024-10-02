#include "InputService.h"

namespace Adagio {
    void InputService::addHandler(KeyboardHandler *handler) {
        keyboard.setHandler(handler);
        actions.linkInput(&keyboard);
    }

    void InputService::addHandler(MouseHandler *handler) {
        mouse.setHandler(handler);
        actions.linkInput(&mouse);
    }

    void InputService::addHandler(GamepadHandler *handler) {
        gamepad.setHandler(handler);
        actions.linkInput(&gamepad);
    }

    void InputService::update() {
        gamepad.update();
        keyboard.update();
        mouse.update();
        actions.update();
    }
} // Adagio
