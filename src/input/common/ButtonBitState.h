#ifndef GL_ADAGIO_BUTTONBITSTATE_H
#define GL_ADAGIO_BUTTONBITSTATE_H

namespace Adagio::Input {
    // Encodes the state of a digital button, shared by various input state objects.
    struct ButtonBitState {
        bool isDown: 1;
        bool isPressed: 1;
        bool isReleased: 1;
    };
}

#endif //GL_ADAGIO_BUTTONBITSTATE_H
