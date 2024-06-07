#include "TextState.h"

namespace Adagio {
    void TextState::draw(GraphicsDevice *graphicsDevice) const {
        graphicsDevice->drawText(*font, text, position, fontSize, spacing, tint);
    }

    TextState::~TextState() = default;
}
