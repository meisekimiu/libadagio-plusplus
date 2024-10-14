#ifndef GL_ADAGIO_SPRITEANIMATIONFRAME_H
#define GL_ADAGIO_SPRITEANIMATIONFRAME_H

#include "../math/Rect.h"

namespace Adagio {
    struct SpriteAnimationFrame {
        double duration{0.0};
        RectI clip;
    };
}

#endif //GL_ADAGIO_SPRITEANIMATIONFRAME_H
