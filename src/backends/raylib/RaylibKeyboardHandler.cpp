#include <raylib.h>
#include "RaylibKeyboardHandler.h"

char RaylibKeyboardHandler::getNextChar() {
    return static_cast<char>(GetCharPressed() % 255);
}

Adagio::keycode RaylibKeyboardHandler::getNextKey() {
    return GetKeyPressed();
}

bool RaylibKeyboardHandler::isKeyDown(Adagio::keycode key) {
    return IsKeyDown(key);
}

bool RaylibKeyboardHandler::isKeyUp(Adagio::keycode key) {
    return IsKeyUp(key);
}
