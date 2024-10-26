#ifndef GL_ADAGIO_TEXTSTATE_H
#define GL_ADAGIO_TEXTSTATE_H

#include "../math/Vector2.h"
#include "RenderState.h"

namespace Adagio {
    struct TextState : public RenderState {
        const char *text{nullptr};
        Font font;
        float fontSize{16};
        float spacing{1};
        Vector2d position{0, 0};
        Color tint{255, 255, 255, 255};

        void draw(GraphicsDevice *graphicsDevice) const override;

        ~TextState() override;
    };
} // namespace Adagio
#endif // GL_ADAGIO_TEXTSTATE_H
