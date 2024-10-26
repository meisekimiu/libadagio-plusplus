#ifndef GL_ADAGIO_RAYLIBGRAPHICSDEVICE_H
#define GL_ADAGIO_RAYLIBGRAPHICSDEVICE_H

#include "../../graphics/GraphicsDevice.h"
#include "../../graphics/font/FontManager.h"
#include "RaylibTextureLoader.h"
#include "raylib.h"
#include "RaylibFontLoader.h"

typedef Texture2D RaylibTexture;

class RaylibGraphicsDevice : public Adagio::GraphicsDevice {
private:
    RaylibTextureLoader loader;
    RaylibFontLoader fontLoader;
    Adagio::TextureManager<RaylibTexture> textureManager{&loader};
    Adagio::FontManager<RaylibFont> fontManager{&fontLoader};
    Adagio::Color clearColor{0, 0, 0, 255};

public:
    void begin() override;

    void end() override;

    void setClearColor(const Adagio::Color &color) override;

    Adagio::AbstractTextureManager *getTextureManager() override;

    Adagio::AbstractFontManager *getFontManager() override;

    void drawTexture(Adagio::Texture2D &texture, const Adagio::RectF &source,
                     const Adagio::RectF &dest, const Adagio::Vector2d &origin,
                     float rotation, const Adagio::Color &tint) override;

    void drawText(const Adagio::Font &font, const char *text, const Adagio::Vector2d &position,
                  float fontSize, float spacing,
                  const Adagio::Color &tint) override;
};

#endif // GL_ADAGIO_RAYLIBGRAPHICSDEVICE_H
