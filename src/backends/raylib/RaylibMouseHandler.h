#ifndef GL_ADAGIO_RAYLIBMOUSEHANDLER_H
#define GL_ADAGIO_RAYLIBMOUSEHANDLER_H

#include "../../input/mouse/MouseHandler.h"

class RaylibMouseHandler : public Adagio::MouseHandler {
    void setMouseCursor(Adagio::MouseCursor cursor) override;

    void setMouseCoords(Adagio::Vector2i coords) override;

    Adagio::Vector2i getMouseCoords() override;

    bool isMouseButtonUp(Adagio::MouseButton button) override;

    bool isMouseButtonDown(Adagio::MouseButton button) override;
};


#endif //GL_ADAGIO_RAYLIBMOUSEHANDLER_H
