#include <raylib.h>
#include "RaylibMouseHandler.h"

void RaylibMouseHandler::setMouseCursor(Adagio::MouseCursor cursor) {
    SetMouseCursor(cursor);
}

void RaylibMouseHandler::setMouseCoords(Adagio::Vector2i coords) {
    SetMousePosition(coords.x, coords.y);
}

Adagio::Vector2i RaylibMouseHandler::getMouseCoords() {
    Vector2 pos = GetMousePosition();
    return {static_cast<int>(pos.x), static_cast<int>(pos.y)};
}

bool RaylibMouseHandler::isMouseButtonUp(Adagio::MouseButton button) {
    return IsMouseButtonUp(button);
}

bool RaylibMouseHandler::isMouseButtonDown(Adagio::MouseButton button) {
    return IsMouseButtonDown(button);
}
