#ifndef GL_ADAGIO_MOCKMOUSE_H
#define GL_ADAGIO_MOCKMOUSE_H

#include "../../../src/input/mouse/MouseState.h"
#include <unordered_map>

struct MockMouse : public Adagio::MouseHandler {
    Adagio::Vector2i coords{0, 0};
    std::unordered_map<Adagio::MouseButton, bool> buttons;
    int cursor{0};

    bool isMouseButtonDown(Adagio::MouseButton btn) override;

    bool isMouseButtonUp(Adagio::MouseButton btn) override;

    Adagio::Vector2i getMouseCoords() override;

    void setMouseCoords(Adagio::Vector2i c) override;

    void setMouseCursor(Adagio::MouseCursor i) override;

    void setMockCoords(int x, int y);

    void pressButton(Adagio::MouseButton i);

    void releaseButton(Adagio::MouseButton i);
};


#endif //GL_ADAGIO_MOCKMOUSE_H
