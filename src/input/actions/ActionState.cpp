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
        updateButtons();
        updateDirections();
    }

    void ActionState::updateDirections() {
        for (auto &direction: directions) {
            Vector2f dir{0, 0};
            for (const auto &keys: directionKeys[direction.first]) {
                if (keyboard->isKeyDown(keys.keys[0])) {
                    dir.x -= 1;
                }
                if (keyboard->isKeyDown(keys.keys[1])) {
                    dir.y += 1;
                }
                if (keyboard->isKeyDown(keys.keys[2])) {
                    dir.y -= 1;
                }
                if (keyboard->isKeyDown(keys.keys[3])) {
                    dir.x += 1;
                }
            }
            for (const auto &btns: directionButtons[direction.first]) {
                if (gamepad->byIndex(0).isButtonDown(btns.keys[0])) {
                    dir.x -= 1;
                }
                if (gamepad->byIndex(0).isButtonDown(btns.keys[1])) {
                    dir.y += 1;
                }
                if (gamepad->byIndex(0).isButtonDown(btns.keys[2])) {
                    dir.y -= 1;
                }
                if (gamepad->byIndex(0).isButtonDown(btns.keys[3])) {
                    dir.x += 1;
                }
            }
            for (const auto axis: directionAxes[direction.first]) {
                dir += gamepad->readAxisPair(axis, 0);
            }
            if (dir.magnitudeSquared() > 1) {
                dir = dir.normalized();
            }
            direction.second = dir;
        }
    }

    void ActionState::updateButtons() {
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
                        isDown = gamepad->byIndex(0).isButtonDown(config.buttonId);
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

    void ActionState::registerActionDirectionKeys(std::uint32_t name, Adagio::keycode left, Adagio::keycode down,
                                                  Adagio::keycode up, Adagio::keycode right) {
        directionKeys[name].push_back({left, down, up, right});
        directions[name];
    }

    Vector2f ActionState::getActionDirection(std::uint32_t name) const {
        auto it = directions.find(name);
        if (it != directions.end()) {
            return it->second;
        }
        return {0, 0};
    }

    void ActionState::registerActionDirectionAxes(std::uint32_t name, std::uint32_t axisName) {
        directionAxes[name].push_back(axisName);
        directions[name];
    }

    void ActionState::registerActionDirectionGamepadButtons(std::uint32_t name, Adagio::GamepadButton left,
                                                            Adagio::GamepadButton down, Adagio::GamepadButton up,
                                                            Adagio::GamepadButton right) {
        directionButtons[name].push_back({left, down, up, right});
        directions[name];
    }
} // Adagio
