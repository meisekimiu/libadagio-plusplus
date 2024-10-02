#include "ActionState.h"

namespace Adagio {
    void ActionState::linkInput(KeyboardState *k) {
        keyboard = k;
    }

    void ActionState::linkInput(MouseState *m) {
        mouse = m;
    }

    void ActionState::linkInput(GamepadCollection *g) {
        gamepad = g;
    }

    bool ActionState::isActionDown(std::uint32_t name) const {
        auto it = buttons.find(name);
        if (it != buttons.end()) {
            return it->second.isDown;
        }
        return false;
    }

    bool ActionState::isActionUp(std::uint32_t name) const {
        return !isActionDown(name);
    }

    bool ActionState::hasActionStarted(std::uint32_t name) const {
        auto it = buttons.find(name);
        if (it != buttons.end()) {
            return it->second.isPressed;
        }
        return false;
    }

    bool ActionState::hasActionEnded(std::uint32_t name) const {
        auto it = buttons.find(name);
        if (it != buttons.end()) {
            return it->second.isReleased;
        }
        return false;
    }

    void ActionState::registerActionButton(std::uint32_t name, Input::InputType inputType, std::uint16_t buttonId) {
        buttonDirectory[name].push_back({inputType, buttonId});
        buttons[name];
    }

    void ActionState::update() {
        for (auto &buttonState: buttons) {
            Input::ButtonBitState &flags = buttonState.second;
            auto &directory = buttonDirectory[buttonState.first];
            bool isDown = false;
            for (auto &config: directory) {
                switch (config.type) {
                    case Input::Keyboard:
                        isDown = keyboard->isKeyDown(config.buttonId);
                        break;
                    case Input::Mouse:
                        isDown = mouse->isButtonDown(config.buttonId);
                        break;
                    case Input::Gamepad:
                        // TODO: support player index later lol
                        isDown = gamepad->byIndex(1).isButtonDown(config.buttonId);
                        break;
                }
                if (isDown) {
                    break;
                }
            }
            flags.isPressed = !flags.isDown && isDown;
            flags.isReleased = flags.isDown && !isDown;
            flags.isDown = isDown;
        }
    }
} // Adagio
