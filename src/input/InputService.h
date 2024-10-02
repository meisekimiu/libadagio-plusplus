#ifndef GL_ADAGIO_INPUTSERVICE_H
#define GL_ADAGIO_INPUTSERVICE_H

#include "actions/ActionState.h"
#include "gamepad/GamepadCollection.h"
#include "keyboard/KeyboardState.h"
#include "mouse/MouseState.h"

namespace Adagio {

    struct InputService {
        ActionState actions;
        GamepadCollection gamepad;
        KeyboardState keyboard;
        MouseState mouse;

        void addHandler(KeyboardHandler *handler);

        void addHandler(MouseHandler *handler);

        void addHandler(GamepadHandler *handler);

        void update();
    };

} // Adagio

#endif //GL_ADAGIO_INPUTSERVICE_H
