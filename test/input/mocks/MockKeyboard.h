#ifndef GL_ADAGIO_MOCKKEYBOARD_H
#define GL_ADAGIO_MOCKKEYBOARD_H

#include <unordered_map>
#include <vector>
#include <string>
#include "../../../src/input/keyboard/KeyboardState.h"


class MockKeyboard : public Adagio::KeyboardHandler {
public:
    std::unordered_map<Adagio::keycode, bool> keys;
    std::vector<Adagio::keycode> pressedKeys;
    std::string buffer;

    void writeChars(const std::string &input);

    void pressKey(Adagio::keycode key);

    void releaseKey(Adagio::keycode key);

    Adagio::keycode getNextKey() override;

    char getNextChar() override;

    bool isKeyDown(Adagio::keycode key) override;

    bool isKeyUp(Adagio::keycode key) override;
};


#endif //GL_ADAGIO_MOCKKEYBOARD_H
