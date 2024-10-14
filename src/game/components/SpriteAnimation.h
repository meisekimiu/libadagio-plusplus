#ifndef GL_ADAGIO_SPRITEANIMATIONCOMPONENT_H
#define GL_ADAGIO_SPRITEANIMATIONCOMPONENT_H

#include "../../math/Rect.h"
#include "../../animation/SpriteAnimation.h"

struct SpriteAnimation {
    Adagio::AnimationName resourceName{0};
    Adagio::FrameIndex currentFrame{0};
    bool loop{false};
    bool done{false};
    double timeOnCurrentFrame{0.0};
};

#endif // GL_ADAGIO_SPRITEANIMATIONCOMPONENT_H
