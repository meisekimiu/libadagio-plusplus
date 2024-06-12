#include "MockGraphicsDevice.h"

MockGraphicsDevice::MockGraphicsDevice() { reset(); }

void MockGraphicsDevice::begin() {
  drawnObjects.clear();
  begun = true;
}

void MockGraphicsDevice::end() { ended = true; }

bool MockGraphicsDevice::hasBegun() const { return begun; }

bool MockGraphicsDevice::hasEnded() const { return ended; }

void MockGraphicsDevice::setClearColor(const Adagio::Color &color) {
  clearColor = color;
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

Adagio::Color MockGraphicsDevice::getClearColor() const { return clearColor; }

void MockGraphicsDevice::reset() {
  begun = false;
  ended = false;
  drawnText = nullptr;
  drawnSprite = nullptr;
  clearColor = {0, 0, 0, 255};

  for (auto obj : drawnObjects) {
    delete obj;
  }
  drawnObjects.clear();
}

void MockGraphicsDevice::drawTexture(Adagio::Texture2D &texture,
                                     const Adagio::RectF &source,
                                     const Adagio::RectF &dest,
                                     const Adagio::Vector2d &origin,
                                     float rotation,
                                     const Adagio::Color &tint) {
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

MockGraphicsDevice::~MockGraphicsDevice() { reset(); }

void MockGraphicsDevice::drawText(Font &font, const char *text,
                                  const Adagio::Vector2d &position,
                                  float fontSize, float spacing,
                                  const Adagio::Color &tint) {
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

Adagio::AbstractTextureManager *MockGraphicsDevice::getTextureManager() {
  return nullptr;
}
