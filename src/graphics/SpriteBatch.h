#ifndef GL_ADAGIO_SPRITEBATCH_H
#define GL_ADAGIO_SPRITEBATCH_H

#include <raylib.h>
#include "RenderPool.h"
#include "SpriteState.h"
#include "TextState.h"

namespace Adagio {

    class SpriteBatch {
    public:
        SpriteBatch();

        SpriteState *draw(Texture2D &texture, const Vector2 &pos, short int zIndex = 0);

        TextState *drawText(const char *text, const Vector2 &pos, short int zIndex = 0);

//        RectState* drawRect(const SDL_Rect& rect, const SDL_Colour& color, RectType type = RECT_FILLED, int zIndex = 0);
        void begin();

        void end();

        Color clearColor{0, 0, 0, 255};

    protected:
        std::vector<RenderState *> renderingQueue;
        RenderPool<SpriteState> spritePool;
        RenderPool<TextState> textPool;
//        RenderPool<RectState> rectPool;

        void addToRenderingQueue(RenderState *r);
    };


} // Adagio

#endif //GL_ADAGIO_SPRITEBATCH_H
