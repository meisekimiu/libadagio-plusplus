#ifndef GL_ADAGIO_TEXTSTATE_H
#define GL_ADAGIO_TEXTSTATE_H

#include <raylib.h>
#include "RenderState.h"
#include "../math/Vector2.h"

namespace Adagio {
    struct TextState : public RenderState {
        const char *text{nullptr};
        Font *font{nullptr};
        float fontSize{16};
        float spacing{1};
        ::Adagio::Vector2d position{0, 0};
        Color tint{255, 255, 255, 255};

        void draw(GraphicsDevice *graphicsDevice) const override;

        ~TextState() override;
    };
}
#endif //GL_ADAGIO_TEXTSTATE_H
