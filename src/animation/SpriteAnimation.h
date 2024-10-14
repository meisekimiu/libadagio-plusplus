#ifndef GL_ADAGIO_SPRITEANIMATION_H
#define GL_ADAGIO_SPRITEANIMATION_H

#include <cstdint>
#include "SpriteAnimationFrame.h"

namespace Adagio {
    typedef std::uint32_t AnimationName;
    typedef std::uint8_t FrameIndex;

    struct SpriteAnimation {
        AnimationName name{0};
        FrameIndex frameLength{1};
        bool loop{false};
        SpriteAnimationFrame *frames{nullptr};
    };
}

#endif //GL_ADAGIO_SPRITEANIMATION_H
