#ifndef GL_ADAGIO_MOUSESTATE_H
#define GL_ADAGIO_MOUSESTATE_H

#define MAX_MOUSE_BUTTONS 8

#include "MouseHandler.h"
#include "../common/ButtonBitState.h"

namespace Adagio {
    class MouseState {
    public:
        MouseState();

        void setHandler(MouseHandler *);

        [[nodiscard]] Vector2i getCursorCoords() const;

        [[nodiscard]] Vector2i getCursorDelta() const;

        [[nodiscard]] bool isButtonDown(MouseButton) const;

        [[nodiscard]] bool isButtonUp(MouseButton) const;

        [[nodiscard]] bool hasClickStarted(MouseButton) const;

        [[nodiscard]] bool hasClickEnded(MouseButton) const;

        void setCursorCoords(const Vector2i &) const;

        void setCursor(MouseCursor) const;

        void update();

    private:
        MouseHandler *handler{nullptr};
        Vector2i cursorCoords;
        Vector2i cursorDelta;
        Input::ButtonBitState buttonStates[MAX_MOUSE_BUTTONS]{};

        void updateButtonStates();

        void updateCoords();
    };
}

#endif //GL_ADAGIO_MOUSESTATE_H
