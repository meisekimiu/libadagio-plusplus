#ifndef GL_ADAGIO_MOCKGRAPHICSDEVICE_H
#define GL_ADAGIO_MOCKGRAPHICSDEVICE_H

#include <vector>
#include "../../src/graphics/GraphicsDevice.h"

class MockGraphicsDevice : public Adagio::GraphicsDevice {
public:
    MockGraphicsDevice();

    void begin() override;

    void end() override;

    void drawTexture(Adagio::SpriteState *sprite) override;

    void drawText(Adagio::TextState *text) override;

    std::vector<Adagio::RenderState *> *getDrawnObjects();

    [[nodiscard]] bool hasBegun() const;

    [[nodiscard]] bool hasEnded() const;

    [[nodiscard]] Adagio::SpriteState *getDrawnSprite() const;

    [[nodiscard]] Adagio::TextState *getDrawnText() const;


protected:
    bool begun;
    bool ended;
    Adagio::SpriteState *drawnSprite;
    Adagio::TextState *drawnText;
    std::vector<Adagio::RenderState *> drawnObjects;
};


#endif //GL_ADAGIO_MOCKGRAPHICSDEVICE_H
