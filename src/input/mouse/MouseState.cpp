#include "MouseState.h"

Adagio::MouseState::MouseState() {
    for (auto &button: buttonStates) {
        button.isDown = false;
        button.isPressed = false;
        button.isReleased = false;
    }
}

void Adagio::MouseState::setHandler(Adagio::MouseHandler *h) {
    handler = h;
}

void Adagio::MouseState::update() {
    updateCoords();
    updateButtonStates();
}

void Adagio::MouseState::updateCoords() {
    Vector2i prevCoords = cursorCoords;
    cursorCoords = handler->getMouseCoords();
    cursorDelta = cursorCoords - prevCoords;
}

void Adagio::MouseState::updateButtonStates() {
    for (Input::ButtonBitState &button: buttonStates) {
        const long buttonIndex = &button - buttonStates;
        const bool isDown = handler->isMouseButtonDown(buttonIndex);
        button.isPressed = !button.isPressed && isDown;
        button.isReleased = button.isDown && handler->isMouseButtonUp(buttonIndex);
        button.isDown = isDown;
    }
}

Adagio::Vector2i Adagio::MouseState::getCursorCoords() const {
    return cursorCoords;
}

Adagio::Vector2i Adagio::MouseState::getCursorDelta() const {
    return cursorDelta;
}

bool Adagio::MouseState::isButtonDown(MouseButton btn) const {
    return buttonStates[btn].isDown;
}

bool Adagio::MouseState::isButtonUp(MouseButton btn) const {
    return !buttonStates[btn].isDown;
}

bool Adagio::MouseState::hasClickStarted(MouseButton btn) const {
    return buttonStates[btn].isPressed;
}

bool Adagio::MouseState::hasClickEnded(Adagio::MouseButton btn) const {
    return buttonStates[btn].isReleased;
}

void Adagio::MouseState::setCursorCoords(const Vector2i &coords) const {
    handler->setMouseCoords(coords);
}

void Adagio::MouseState::setCursor(Adagio::MouseCursor c) const {
    handler->setMouseCursor(c);
}

