#ifndef GL_ADAGIO_GRAPHICSDEVICE_H
#define GL_ADAGIO_GRAPHICSDEVICE_H

#include <raylib.h>

namespace Adagio {

    class GraphicsDevice {
    public:
        virtual void begin() = 0;

        virtual void end() = 0;

        virtual void setClearColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) = 0;

        virtual void
        drawTexture(Texture &texture, const Rectangle &source, const Rectangle &dest, const Vector2 &origin,
                    float rotation,
                    const Color &tint) = 0;

        virtual void
        drawText(Font &font, const char *text, const Vector2 &position, float fontSize, float spacing,
                 const Color &tint) = 0;
    };

} // Adagio

#endif //GL_ADAGIO_GRAPHICSDEVICE_H
