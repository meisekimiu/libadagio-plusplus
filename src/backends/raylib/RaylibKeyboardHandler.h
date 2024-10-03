#ifndef GL_ADAGIO_RAYLIBKEYBOARDHANDLER_H
#define GL_ADAGIO_RAYLIBKEYBOARDHANDLER_H

#include "../../input/keyboard/KeyboardHandler.h"

class RaylibKeyboardHandler : public Adagio::KeyboardHandler {
    char getNextChar() override;

    Adagio::keycode getNextKey() override;

    bool isKeyDown(Adagio::keycode key) override;

    bool isKeyUp(Adagio::keycode key) override;
};


#endif //GL_ADAGIO_RAYLIBKEYBOARDHANDLER_H
