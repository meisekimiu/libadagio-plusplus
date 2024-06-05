#ifndef GL_ADAGIO_ECSMOCKGRAPHICSDEVICE_H
#define GL_ADAGIO_ECSMOCKGRAPHICSDEVICE_H

#include "../../../src/graphics/GraphicsDevice.h"
#include "../../../src/graphics/SpriteState.h"
#include "MockTextureLibrary.h"

class EcsMockGraphicsDevice : public Adagio::GraphicsDevice {
public:
    void begin() override;

    void end() override;

    void setClearColor(const Adagio::Color &color) override;

    void drawTexture(Adagio::Texture2D &texture, const Adagio::RectF &source, const Adagio::RectF &dest,
                     const Adagio::Vector2d &origin, float rotation, const Adagio::Color &tint) override;

    void drawText(Font &font, const char *text, const Adagio::Vector2d &position, float fontSize, float spacing,
                  const Adagio::Color &tint) override;

    Adagio::AbstractTextureManager *getTextureManager() override;

    [[nodiscard]] Adagio::Color getClearColor() const;

    [[nodiscard]] const std::vector<Adagio::SpriteState> *getSprites() const;

protected:
    Adagio::Color clearColor{0, 0, 0, 0};
    std::vector<Adagio::SpriteState> spritesRenderedOnFrame;
    MockTextureLibrary textureLibrary;
};


#endif //GL_ADAGIO_ECSMOCKGRAPHICSDEVICE_H
