#ifndef GL_ADAGIO_SPRITEANIMATIONLIBRARY_H
#define GL_ADAGIO_SPRITEANIMATIONLIBRARY_H

#include <cstdint>
#include <unordered_map>
#include <deque>
#include "SpriteAnimation.h"

#define ADAGIO_ALLOCATED_SPRITEANIM_FRAMES 100

namespace Adagio {

    typedef std::uint32_t AnimationName;

    class SpriteAnimationLibrary {
    public:
        SpriteAnimationLibrary();

        const SpriteAnimation &getAnimation(AnimationName name) const;

        SpriteAnimation &createAnimation(AnimationName name, FrameIndex frameCount, SpriteAnimationFrame *frameArray);

        void freeAnimation(AnimationName name);

        void clear();

    private:
        struct FreeFrameSpace {
            std::uint16_t index;
            std::uint16_t size;
        };
        SpriteAnimationFrame frames[ADAGIO_ALLOCATED_SPRITEANIM_FRAMES];
        std::unordered_map<AnimationName, SpriteAnimation> animations;
        std::deque<FreeFrameSpace> freeChunks;
    };

} // Adagio

#endif //GL_ADAGIO_SPRITEANIMATIONLIBRARY_H
