#ifndef GL_ADAGIO_SPRITEANIMATION_H
#define GL_ADAGIO_SPRITEANIMATION_H

#include "../../math/Rect.h"

typedef unsigned char FrameIndex;

struct AnimationFrame {
    double duration{0.0};
    Adagio::RectI clip;
};

struct SpriteAnimation {
    FrameIndex currentFrame{0};
    FrameIndex frameLength{0};
    bool loop{false};
    bool done{false};
    double timeOnCurrentFrame{0.0};
    AnimationFrame* frames{nullptr};
};

#endif //GL_ADAGIO_SPRITEANIMATION_H
