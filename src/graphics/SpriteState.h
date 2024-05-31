#ifndef GL_ADAGIO_SPRITESTATE_H
#define GL_ADAGIO_SPRITESTATE_H

#include "RenderState.h"
#include "Texture2D.h"
#include "../math/Vector2.h"
#include "../math/Rect.h"

namespace Adagio {

    struct SpriteState : public RenderState {
        unsigned char opacity{255};
        float rotation{0.0};
        Texture2D *texture{};
        RectF source{};
        RectF destination{};
        Vector2d origin{};
        Color tint{255, 255, 255, 255};

        SpriteState();

        SpriteState(Texture2D &tex, const Vector2d &position, signed short int zIndex);

        void draw(GraphicsDevice *graphicsDevice) const override;

        ~SpriteState() override;
    };

} // Adagio

#endif //GL_ADAGIO_SPRITESTATE_H
