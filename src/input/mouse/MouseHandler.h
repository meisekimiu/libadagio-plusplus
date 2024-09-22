#ifndef GL_ADAGIO_MOUSEHANDLER_H
#define GL_ADAGIO_MOUSEHANDLER_H

#include <cstdint>
#include "../../math/Vector2.h"

namespace Adagio {
    typedef std::uint8_t MouseButton;

    typedef std::int32_t MouseCursor;

    struct MouseHandler {
        virtual bool isMouseButtonDown(MouseButton) = 0;

        virtual bool isMouseButtonUp(MouseButton) = 0;

        virtual Vector2i getMouseCoords() = 0;

        virtual void setMouseCoords(Vector2i) = 0;

        virtual void setMouseCursor(MouseCursor) = 0;
    };
}

#endif //GL_ADAGIO_MOUSEHANDLER_H
