#include "GamepadCollection.h"

namespace Adagio {

    GamepadCollection::GamepadCollection() {
        for (char i = 0; i < ADAGIO_MAX_GAMEPADS; i++) {
            gamepads[i].setIndex(i);
        }
    }

    void GamepadCollection::setHandler(GamepadHandler *handler) {
        for (auto &gamepad: gamepads) {
            gamepad.setHandler(handler);
        }
    }

    const GamepadState &GamepadCollection::byIndex(GamepadIndex index) const {
        return gamepads[index];
    }

    void GamepadCollection::update() {
        for (auto &gamepad: gamepads) {
            gamepad.update();
        }
    }

    void GamepadCollection::createAxisPair(std::uint32_t name, GamepadButton axisX, GamepadButton axisY) {
        axisPairs[name] = {axisX, axisY, 0, 1};
    }

    Vector2f GamepadCollection::readAxisPair(std::uint32_t name, GamepadIndex gamepad) const {
        const auto it = axisPairs.find(name);
        if (it != axisPairs.end()) {
            const auto &axis = it->second;
            const auto &g = byIndex(gamepad);
            const Vector2f result = {g.getAxisValue(axis.axisX), g.getAxisValue(axis.axisY)};
            if (result.magnitude() < axis.deadzone) {
                return {0.f, 0.f};
            }
            if (result.magnitude() >= axis.maxZone) {
                return result.normalized();
            }
            return result;
        }
        return {0.f, 0.f};
    }

    void GamepadCollection::setAxisPairDeadzone(std::uint32_t name, float deadzone) {
        axisPairs[name].deadzone = deadzone;
    }

    void GamepadCollection::setAxisPairMaxzone(std::uint32_t name, float maxzone) {
        axisPairs[name].maxZone = maxzone;
    }
}
