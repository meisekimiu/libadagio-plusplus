#include "KeyboardState.h"

void Adagio::KeyboardState::setHandler(Adagio::KeyboardHandler *handle) {
    handler = handle;
}

bool Adagio::KeyboardState::isKeyDown(Adagio::keycode key) const {
    auto it = keys.find(key);
    if (it != keys.end()) {
        return it->second.keyDown;
    }
    return false;
}

bool Adagio::KeyboardState::isKeyUp(Adagio::keycode key) const {
    return !isKeyDown(key);
}

bool Adagio::KeyboardState::hasKeyPressStarted(Adagio::keycode key) const {
    auto it = keys.find(key);
    if (it != keys.end()) {
        return it->second.keyPressed;
    }
    return false;
}

bool Adagio::KeyboardState::hasKeyPressEnded(Adagio::keycode key) const {
    auto it = keys.find(key);
    if (it != keys.end()) {
        return it->second.keyReleased;
    }
    return false;
}

void Adagio::KeyboardState::update() {
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
        keyState.second.keyPressed = false;
        keyState.second.keyReleased = keyState.second.keyDown && handler->isKeyUp(keyState.first);
        keyState.second.keyDown = handler->isKeyDown(keyState.first);
    }
}

void Adagio::KeyboardState::scanForNewKeyPresses() {
    keycode newKey = handler->getNextKey();
    while (newKey != 0) {
        keys[newKey].keyDown = true;
        keys[newKey].keyPressed = true;
        keys[newKey].keyReleased = false;
        newKey = handler->getNextKey();
    }
}

Adagio::KeyboardState::KeyboardState() {
    keys.reserve(256);
}

const char *Adagio::KeyboardState::readTextBuffer() const {
    return textBuffer;
}
