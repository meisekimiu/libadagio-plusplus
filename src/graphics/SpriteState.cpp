#include "SpriteState.h"

namespace Adagio {
SpriteState::SpriteState() { tint = WHITE; }

SpriteState::SpriteState(Texture2D &tex, const Vector2d &position,
                         signed short int zIndex) {
  texture = &tex;
  this->zIndex = zIndex;
  const auto width = static_cast<float>(tex.getWidth());
  const auto height = static_cast<float>(tex.getHeight());
  source = {0, 0, width, height};
  destination = {static_cast<float>(position.x), static_cast<float>(position.y),
                 width, height};
  tint = WHITE;
  opacity = 255;
}

void SpriteState::draw(GraphicsDevice *graphicsDevice) const {
  const auto alpha = opacity == 255 ? tint.a : opacity;
  if (active && texture) {
    graphicsDevice->drawTexture(*texture, source, destination, origin, rotation,
                                {tint.r, tint.g, tint.b, alpha});
  }
}

SpriteState::~SpriteState() = default;
} // namespace Adagio
