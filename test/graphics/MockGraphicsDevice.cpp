#include "MockGraphicsDevice.h"

MockGraphicsDevice::MockGraphicsDevice() {
    reset();
}

void MockGraphicsDevice::begin() {
    drawnObjects.clear();
    begun = true;
}

void MockGraphicsDevice::end() {
    ended = true;
}

bool MockGraphicsDevice::hasBegun() const {
    return begun;
}

bool MockGraphicsDevice::hasEnded() const {
    return ended;
}

void MockGraphicsDevice::setClearColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
    clearColor = {r, g, b, a};
}

//void MockGraphicsDevice::drawTexture(Adagio::SpriteState *sprite) {
//    drawnObjects.push_back(sprite);
//    drawnSprite = sprite;
//}
//
//void MockGraphicsDevice::drawText(Adagio::TextState *text) {
//    drawnObjects.push_back(text);
//    drawnText = text;
//}

Adagio::SpriteState *MockGraphicsDevice::getDrawnSprite() const {
    return drawnSprite;
}

Adagio::TextState *MockGraphicsDevice::getDrawnText() const {
    return drawnText;
}

std::vector<Adagio::RenderState *> *MockGraphicsDevice::getDrawnObjects() {
    return &drawnObjects;
}

Color MockGraphicsDevice::getClearColor() const {
    return clearColor;
}

void MockGraphicsDevice::reset() {
    begun = false;
    ended = false;
    drawnText = nullptr;
    drawnSprite = nullptr;
    clearColor = BLACK;

    for (auto obj: drawnObjects) {
        delete obj;
    }
    drawnObjects.clear();
}

void
MockGraphicsDevice::drawTexture(Texture &texture, const Rectangle &source, const Rectangle &dest, const Vector2 &origin,
                                float rotation,
                                const Color &tint) {
    auto sprite = new Adagio::SpriteState;
    sprite->texture = &texture;
    sprite->source = source;
    sprite->destination = dest;
    sprite->origin = origin;
    sprite->rotation = rotation;
    sprite->tint = tint;
    drawnSprite = sprite;
    drawnObjects.push_back(drawnSprite);
}

MockGraphicsDevice::~MockGraphicsDevice() {
    reset();
}

void
MockGraphicsDevice::drawText(Font &font, const char *text, const Vector2 &position, float fontSize, float spacing,
                             const Color &tint) {
    auto txt = new Adagio::TextState;
    txt->font = &font;
    txt->text = text;
    txt->position = position;
    txt->fontSize = fontSize;
    txt->spacing = spacing;
    txt->tint = tint;
    drawnText = txt;
    drawnObjects.push_back(txt);
}
