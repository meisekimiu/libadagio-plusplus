#include "MockMouse.h"

bool MockMouse::isMouseButtonDown(Adagio::MouseButton btn) {
    return buttons[btn];
}

bool MockMouse::isMouseButtonUp(Adagio::MouseButton btn) {
    return !buttons[btn];
}

Adagio::Vector2i MockMouse::getMouseCoords() {
    return coords;
}

void MockMouse::setMouseCoords(Adagio::Vector2i c) {
    coords = c;
}

void MockMouse::setMouseCursor(Adagio::MouseCursor i) {
    cursor = i;
}

void MockMouse::setMockCoords(int x, int y) {
    coords.x = x;
    coords.y = y;
}

void MockMouse::pressButton(Adagio::MouseButton i) {
    buttons[i] = true;
}

void MockMouse::releaseButton(Adagio::MouseButton i) {
    buttons[i] = false;
}
