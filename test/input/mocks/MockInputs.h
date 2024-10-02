#ifndef GL_ADAGIO_MOCKINPUTS_H
#define GL_ADAGIO_MOCKINPUTS_H

#include "MockGamepad.h"
#include "MockKeyboard.h"
#include "MockMouse.h"

struct MockInputs {
    MockGamepad gamepad;
    MockKeyboard keyboard;
    MockMouse mouse;
};

#endif //GL_ADAGIO_MOCKINPUTS_H
