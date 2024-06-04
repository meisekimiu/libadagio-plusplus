#ifndef GL_ADAGIO_GRAPHICSDEVICE_H
#define GL_ADAGIO_GRAPHICSDEVICE_H

#include "Color.h"
#include "Texture2D.h"
#include "TextureManager.h"
#include "../math/Vector2.h"
#include "../math/Rect.h"
#include <raylib.h>

namespace Adagio {

    class GraphicsDevice {
    public:
        virtual void begin() = 0;

        virtual void end() = 0;

        virtual void setClearColor(const Adagio::Color &color) = 0;

        [[nodiscard]] virtual AbstractTextureManager *getTextureManager() = 0;

        virtual void drawTexture(Texture2D &texture, const RectF &source, const RectF &dest, const Vector2d &origin,
                                 float rotation,
                                 const Color &tint) = 0;

        virtual void drawText(Font &font, const char *text, const Vector2d &position, float fontSize, float spacing,
                              const Color &tint) = 0;
    };

} // Adagio

#endif //GL_ADAGIO_GRAPHICSDEVICE_H
