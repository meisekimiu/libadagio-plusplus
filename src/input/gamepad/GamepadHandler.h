#ifndef GL_ADAGIO_GAMEPADHANDLER_H
#define GL_ADAGIO_GAMEPADHANDLER_H

#include <cstdint>

namespace Adagio {
    typedef std::uint8_t GamepadButton;
    typedef std::uint8_t GamepadIndex;

    struct GamepadHandler {
        virtual bool isButtonDown(GamepadIndex gamepad, GamepadButton button) = 0;

        virtual bool isButtonUp(GamepadIndex gamepad, GamepadButton button) = 0;

        virtual float getAxisValue(GamepadIndex gamepad, GamepadButton axis) = 0;
    };
}

#endif //GL_ADAGIO_GAMEPADHANDLER_H
