#ifndef GL_ADAGIO_MOCKGRAPHICSDEVICE_H
#define GL_ADAGIO_MOCKGRAPHICSDEVICE_H

#include <vector>
#include "../../src/graphics/GraphicsDevice.h"
#include "../../src/graphics/SpriteState.h"
#include "../../src/graphics/TextState.h"

class MockGraphicsDevice : public Adagio::GraphicsDevice {
public:
    MockGraphicsDevice();

    ~MockGraphicsDevice();

    void begin() override;

    void end() override;

    void setClearColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) override;

    void
    drawTexture(Texture &texture, const Rectangle &source, const Rectangle &dest, const Vector2 &origin, float rotation,
                const Color &tint) override;

    void drawText(Font &font, const char *text, const Vector2 &position, float fontSize, float spacing,
                  const Color &tint) override;

    std::vector<Adagio::RenderState *> *getDrawnObjects();

    [[nodiscard]] bool hasBegun() const;

    [[nodiscard]] bool hasEnded() const;

    [[nodiscard]] Color getClearColor() const;

    [[nodiscard]] Adagio::SpriteState *getDrawnSprite() const;

    [[nodiscard]] Adagio::TextState *getDrawnText() const;

    void reset();


protected:
    bool begun;
    bool ended;
    Adagio::SpriteState *drawnSprite;
    Adagio::TextState *drawnText;
    std::vector<Adagio::RenderState *> drawnObjects;
    Color clearColor;
};


#endif //GL_ADAGIO_MOCKGRAPHICSDEVICE_H
