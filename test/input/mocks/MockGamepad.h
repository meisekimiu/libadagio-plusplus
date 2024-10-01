#ifndef GL_ADAGIO_MOCKGAMEPAD_H
#define GL_ADAGIO_MOCKGAMEPAD_H

#include <unordered_map>
#include "../../../src/input/gamepad/GamepadHandler.h"

struct MockGamepad : public Adagio::GamepadHandler {
    std::unordered_map<Adagio::GamepadButton, bool> buttons[5];
    std::unordered_map<Adagio::GamepadButton, float> axes[5];

    bool isButtonDown(Adagio::GamepadIndex gamepad, Adagio::GamepadButton button) override;

    bool isButtonUp(Adagio::GamepadIndex gamepad, Adagio::GamepadButton button) override;

    float getAxisValue(Adagio::GamepadIndex gamepad, Adagio::GamepadButton axis) override;

    void pressButton(Adagio::GamepadIndex gamepad, Adagio::GamepadButton button);

    void releaseButton(Adagio::GamepadIndex gamepad, Adagio::GamepadButton button);

    void setAxis(Adagio::GamepadIndex gamepad, Adagio::GamepadButton button, float value);
};

#endif //GL_ADAGIO_MOCKGAMEPAD_H
