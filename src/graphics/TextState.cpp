#include "TextState.h"

namespace Adagio {
    void TextState::draw(GraphicsDevice *graphicsDevice) const {
        graphicsDevice->drawText(*font, text, position, fontSize, spacing, tint);
//        if (text) {
//            if (font) {
//                DrawTextEx(*font, text, position, fontSize, spacing, tint);
//                return;
//            }
//            int x, y;
//            x = static_cast<int>(position.x);
//            y = static_cast<int>(position.y);
//            DrawText(text, x, y, static_cast<int>(fontSize), tint);
//        }
    }

    TextState::~TextState() = default;
}
