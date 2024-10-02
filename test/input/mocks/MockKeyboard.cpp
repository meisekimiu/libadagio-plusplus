#include "MockKeyboard.h"

void MockKeyboard::writeChars(const std::string &input) {
    buffer += input;
}

void MockKeyboard::pressKey(Adagio::keycode key) {
    keys[key] = true;
    pressedKeys.push_back(key);
}

void MockKeyboard::releaseKey(Adagio::keycode key) {
    keys[key] = false;
}

Adagio::keycode MockKeyboard::getNextKey() {
    if (!pressedKeys.empty()) {
        Adagio::keycode key = pressedKeys.back();
        pressedKeys.pop_back();
        return key;
    }
    return 0;
}

char MockKeyboard::getNextChar() {
    if (buffer.empty()) {
        return 0;
    }
    char c = buffer[0];
    buffer.erase(buffer.begin());
    return c;
}

bool MockKeyboard::isKeyDown(Adagio::keycode key) {
    if (keys.find(key) != keys.end()) {
        return keys[key];
    }
    return false;
}

bool MockKeyboard::isKeyUp(Adagio::keycode key) {
    if (keys.find(key) != keys.end()) {
        return !keys[key];
    }
    return true;
}

