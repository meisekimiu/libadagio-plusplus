#ifndef GL_ADAGIO_GAMEPADSTATE_H
#define GL_ADAGIO_GAMEPADSTATE_H

#include <unordered_map>
#include "../common/ButtonBitState.h"
#include "GamepadHandler.h"

#define MAX_BUTTONS 16

namespace Adagio {

    class GamepadState {
    public:
        explicit GamepadState(GamepadIndex index);

        void setHandler(GamepadHandler *h);

        [[nodiscard]] bool isButtonDown(GamepadButton button) const;

        [[nodiscard]] bool isButtonUp(GamepadButton button) const;

        [[nodiscard]] bool hasButtonPressStarted(GamepadButton button) const;

        [[nodiscard]] bool hasButtonPressEnded(GamepadButton button) const;

        void update();

    private:
        GamepadHandler *handler{nullptr};
        GamepadIndex index{0};
        Input::ButtonBitState buttons[MAX_BUTTONS]{};
    };

} // Adagio

#endif //GL_ADAGIO_GAMEPADSTATE_H
