#include "RaylibGraphicsDevice.h"

void RaylibGraphicsDevice::begin() {
    ClearBackground({clearColor.r, clearColor.g, clearColor.b, clearColor.a});
    BeginDrawing();
}

void RaylibGraphicsDevice::end() {
    EndDrawing();
}

void RaylibGraphicsDevice::setClearColor(const Adagio::Color &color) {
    clearColor = color;
}

static Rectangle AdagioRectToRaylibRect(const Adagio::RectF &rect) {
    return {rect.x(), rect.y(), rect.width(), rect.height()};
}

void
RaylibGraphicsDevice::drawTexture(Adagio::Texture2D &texture, const Adagio::RectF &source, const Adagio::RectF &dest,
                                  const Adagio::Vector2d &origin, float rotation, const Adagio::Color &tint) {
    RaylibTexture raylibTex = textureManager.useTexture(texture);
    DrawTexturePro(raylibTex, AdagioRectToRaylibRect(source), AdagioRectToRaylibRect(dest),
                   {static_cast<float>(origin.x), static_cast<float>(origin.y)}, rotation,
                   {tint.r, tint.g, tint.b, tint.a});
}

Adagio::AbstractTextureManager *RaylibGraphicsDevice::getTextureManager() {
    return &textureManager;
}

void RaylibGraphicsDevice::drawText(Font &font, const char *text, const Adagio::Vector2d &position, float fontSize,
                                    float spacing, const Adagio::Color &tint) {

}
