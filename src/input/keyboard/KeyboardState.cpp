#include "KeyboardState.h"

void Adagio::KeyboardState::setHandler(Adagio::KeyboardHandler *handle) {
    handler = handle;
}

bool Adagio::KeyboardState::isKeyDown(Adagio::keycode key) const {
    auto it = keys.find(key);
    if (it != keys.end()) {
        return it->second.isDown;
    }
    return false;
}

bool Adagio::KeyboardState::isKeyUp(Adagio::keycode key) const {
    return !isKeyDown(key);
}

bool Adagio::KeyboardState::hasKeyPressStarted(Adagio::keycode key) const {
    auto it = keys.find(key);
    if (it != keys.end()) {
        return it->second.isPressed;
    }
    return false;
}

bool Adagio::KeyboardState::hasKeyPressEnded(Adagio::keycode key) const {
    auto it = keys.find(key);
    if (it != keys.end()) {
        return it->second.isReleased;
    }
    return false;
}

void Adagio::KeyboardState::update() {
    if (handler == nullptr) {
        return;
    }
    updateTextBuffer();
    checkKnownKeys();
    scanForNewKeyPresses();
}

void Adagio::KeyboardState::updateTextBuffer() {
    for (auto &c: textBuffer) {
        if (c == 0) {
            break;
        }
        c = 0;
    }
    char bufferPos = 0;
    char c = handler->getNextChar();
    while (c != 0) {
        textBuffer[bufferPos++] = c;
        if (bufferPos > 8) {
            break;
        }
        c = handler->getNextChar();
    }
}

void Adagio::KeyboardState::checkKnownKeys() {
    for (auto &keyState: keys) {
        keyState.second.isPressed = false;
        keyState.second.isReleased = keyState.second.isDown && handler->isKeyUp(keyState.first);
        keyState.second.isDown = handler->isKeyDown(keyState.first);
    }
}

void Adagio::KeyboardState::scanForNewKeyPresses() {
    keycode newKey = handler->getNextKey();
    while (newKey != 0) {
        keys[newKey].isDown = true;
        keys[newKey].isPressed = true;
        keys[newKey].isReleased = false;
        newKey = handler->getNextKey();
    }
}

Adagio::KeyboardState::KeyboardState() {
    keys.reserve(256);
}

const char *Adagio::KeyboardState::readTextBuffer() const {
    return textBuffer;
}
