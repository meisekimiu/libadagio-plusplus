#ifndef GL_ADAGIO_GRAPHICSDEVICE_H
#define GL_ADAGIO_GRAPHICSDEVICE_H

#include "SpriteState.h"
#include "TextState.h"

namespace Adagio {

    class GraphicsDevice {
    public:
        virtual void begin() = 0;

        virtual void end() = 0;

        virtual void drawTexture(SpriteState *sprite) = 0;

        virtual void drawText(TextState *text) = 0;
    };

} // Adagio

#endif //GL_ADAGIO_GRAPHICSDEVICE_H
