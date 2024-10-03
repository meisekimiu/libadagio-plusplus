#ifndef GL_ADAGIO_RAYLIBGAMEPADHANDLER_H
#define GL_ADAGIO_RAYLIBGAMEPADHANDLER_H

#include "../../input/gamepad/GamepadHandler.h"

class RaylibGamepadHandler : public Adagio::GamepadHandler {
    float getAxisValue(Adagio::GamepadIndex gamepad, Adagio::GamepadButton axis) override;

    bool isButtonDown(Adagio::GamepadIndex gamepad, Adagio::GamepadButton button) override;

    bool isButtonUp(Adagio::GamepadIndex gamepad, Adagio::GamepadButton button) override;
};


#endif //GL_ADAGIO_RAYLIBGAMEPADHANDLER_H
