#ifndef GL_ADAGIO_KEYBOARDSTATE_H
#define GL_ADAGIO_KEYBOARDSTATE_H

#include <unordered_map>
#include <cstdint>
#include "KeyboardHandler.h"

namespace Adagio {
    class KeyboardState {
    public:
        KeyboardState();

        void setHandler(KeyboardHandler *h);

        bool isKeyDown(keycode) const;

        bool isKeyUp(keycode) const;

        bool hasKeyPressStarted(keycode) const;

        bool hasKeyPressEnded(keycode) const;

        const char *readTextBuffer() const;

        void update();

    private:
        struct KeyBitState {
            bool keyDown: 1;
            bool keyPressed: 1;
            bool keyReleased: 1;
        };

        char textBuffer[8]{0, 0, 0, 0, 0, 0, 0, 0};
        KeyboardHandler *handler{nullptr};
        std::unordered_map<keycode, KeyBitState> keys;

        void scanForNewKeyPresses();

        void checkKnownKeys();

        void updateTextBuffer();
    };
}


#endif //GL_ADAGIO_KEYBOARDSTATE_H
