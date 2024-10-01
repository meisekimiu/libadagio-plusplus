#ifndef GL_ADAGIO_GAMEPADCOLLECTION_H
#define GL_ADAGIO_GAMEPADCOLLECTION_H

#include "../../math/Vector2.h"
#include "GamepadState.h"

#define ADAGIO_MAX_GAMEPADS 4

namespace Adagio {
    class GamepadCollection {
    public:
        GamepadCollection();

        void setHandler(GamepadHandler *handler);

        void createAxisPair(std::uint32_t name, GamepadButton axisX, GamepadButton axisY);

        void setAxisPairDeadzone(std::uint32_t name, float deadzone);

        void setAxisPairMaxzone(std::uint32_t name, float maxzone);

        [[nodiscard]] const GamepadState &byIndex(GamepadIndex index) const;

        Vector2f readAxisPair(std::uint32_t name, GamepadIndex gamepad = 1) const;

        void update();

    private:
        struct AxisPairConfig {
            GamepadButton axisX{1};
            GamepadButton axisY{1};
            float deadzone{0};
            float maxZone{1};
        };
        GamepadState gamepads[ADAGIO_MAX_GAMEPADS];
        std::unordered_map<std::uint32_t, AxisPairConfig> axisPairs;
    };
}

#endif //GL_ADAGIO_GAMEPADCOLLECTION_H
