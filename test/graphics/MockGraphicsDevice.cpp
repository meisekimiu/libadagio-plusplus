#include "MockGraphicsDevice.h"

MockGraphicsDevice::MockGraphicsDevice() {
    begun = false;
    ended = false;
    drawnText = nullptr;
    drawnSprite = nullptr;
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

void MockGraphicsDevice::drawTexture(Adagio::SpriteState *sprite) {
    drawnObjects.push_back(sprite);
    drawnSprite = sprite;
}

void MockGraphicsDevice::drawText(Adagio::TextState *text) {
    drawnObjects.push_back(text);
    drawnText = text;
}

Adagio::SpriteState *MockGraphicsDevice::getDrawnSprite() const {
    return drawnSprite;
}

Adagio::TextState *MockGraphicsDevice::getDrawnText() const {
    return drawnText;
}

std::vector<Adagio::RenderState *> *MockGraphicsDevice::getDrawnObjects() {
    return &drawnObjects;
}
