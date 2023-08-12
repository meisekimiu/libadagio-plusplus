#include "SpriteState.h"

namespace Adagio {
    SpriteState::SpriteState() {
        tint = WHITE;
    }

    SpriteState::SpriteState(Texture2D &tex, const Vector2 &position, signed short int zIndex) {
        texture = &tex;
        this->zIndex = zIndex;
        const auto width = static_cast<float>(tex.width);
        const auto height = static_cast<float>(tex.height);
        source = {0, 0, width, height};
        destination = {position.x, position.y, width, height};
        tint = WHITE;
        opacity = 255;
    }

    void SpriteState::draw() const {
        const auto alpha = opacity == 255 ? tint.a : opacity;
        if (active && texture) {
            DrawTexturePro(*texture, source, destination, origin, rotation, {tint.r, tint.g, tint.b, alpha});
        }
    }
} // Adagio
