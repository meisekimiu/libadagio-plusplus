#include "EcsMockGraphicsDevice.h"

void EcsMockGraphicsDevice::begin() {
    spritesRenderedOnFrame.clear();
}

void EcsMockGraphicsDevice::end() {
    // do nothing
}

void EcsMockGraphicsDevice::setClearColor(const Adagio::Color &color) {
    clearColor = color;
}

void
EcsMockGraphicsDevice::drawTexture(Adagio::Texture2D &texture, const Adagio::RectF &source, const Adagio::RectF &dest,
                                   const Adagio::Vector2d &origin, float rotation, const Adagio::Color &tint) {
    Adagio::SpriteState sprite;
    sprite.texture = &texture;
    sprite.rotation = rotation;
    sprite.tint = tint;
    sprite.origin = origin;
    sprite.destination = dest;
    sprite.source = source;
    spritesRenderedOnFrame.push_back(sprite);
}

Adagio::AbstractTextureManager *EcsMockGraphicsDevice::getTextureManager() {
    return &textureLibrary;
}

Adagio::Color EcsMockGraphicsDevice::getClearColor() const {
    return clearColor;
}

const std::vector<Adagio::SpriteState> *EcsMockGraphicsDevice::getSprites() const {
    return &spritesRenderedOnFrame;
}

void EcsMockGraphicsDevice::drawText(Font &font, const char *text, const Adagio::Vector2d &position, float fontSize,
                                     float spacing, const Adagio::Color &tint) {
    // do nothing for now
}
