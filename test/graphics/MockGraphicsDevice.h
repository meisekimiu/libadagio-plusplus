#ifndef GL_ADAGIO_MOCKGRAPHICSDEVICE_H
#define GL_ADAGIO_MOCKGRAPHICSDEVICE_H

#include "../../src/graphics/GraphicsDevice.h"
#include "../../src/graphics/SpriteState.h"
#include "../../src/graphics/TextState.h"
#include <vector>

class MockGraphicsDevice : public Adagio::GraphicsDevice {
public:
    MockGraphicsDevice();

    ~MockGraphicsDevice();

    void begin() override;

    void end() override;

    void setClearColor(const Adagio::Color &color) override;

    void drawTexture(Adagio::Texture2D &texture, const Adagio::RectF &source,
                     const Adagio::RectF &dest, const Adagio::Vector2d &origin,
                     float rotation, const Adagio::Color &tint) override;

    void drawText(const Adagio::Font &font, const char *text, const Adagio::Vector2d &position,
                  float fontSize, float spacing,
                  const Adagio::Color &tint) override;

    Adagio::AbstractTextureManager *getTextureManager() override;

    Adagio::AbstractFontManager *getFontManager() override;

    std::vector<Adagio::RenderState *> *getDrawnObjects();

    [[nodiscard]] bool hasBegun() const;

    [[nodiscard]] bool hasEnded() const;

    [[nodiscard]] Adagio::Color getClearColor() const;

    [[nodiscard]] Adagio::SpriteState *getDrawnSprite() const;

    [[nodiscard]] Adagio::TextState *getDrawnText() const;

    void reset();

protected:
    bool begun;
    bool ended;
    Adagio::SpriteState *drawnSprite;
    Adagio::TextState *drawnText;
    std::vector<Adagio::RenderState *> drawnObjects;
    Adagio::Color clearColor;
};

#endif // GL_ADAGIO_MOCKGRAPHICSDEVICE_H
