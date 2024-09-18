#ifndef GL_ADAGIO_KEYBOARDHANDLER_H
#define GL_ADAGIO_KEYBOARDHANDLER_H

#include <cstdint>

namespace Adagio {

    typedef std::uint16_t keycode;

    struct KeyboardHandler {
        virtual keycode getNextKey() = 0;

        virtual char getNextChar() = 0;

        virtual bool isKeyDown(keycode) = 0;

        virtual bool isKeyUp(keycode) = 0;
    };

}

#endif //GL_ADAGIO_KEYBOARDHANDLER_H
