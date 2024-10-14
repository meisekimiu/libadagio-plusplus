#include "SpriteAnimationLibrary.h"
#include <algorithm>
#include <stdexcept>

namespace Adagio {
    const SpriteAnimation & SpriteAnimationLibrary::getAnimation(AnimationName name) const {
        const auto &it = animations.find(name);
        if (it == animations.end()) {
            throw std::runtime_error("No animation with hash found");
        }
        return it->second;
    }

    SpriteAnimation &
    SpriteAnimationLibrary::createAnimation(AnimationName name, FrameIndex frameCount,
                                            SpriteAnimationFrame *frameArray) {
        SpriteAnimationFrame *freeOffset = frames;
        const auto it = std::find_if(freeChunks.begin(), freeChunks.end(), [frameCount](const FreeFrameSpace &chunk) {
            return chunk.size >= frameCount;
        });
        if (it != freeChunks.end()) {
            freeOffset += it->index;
            std::copy(frameArray, frameArray + frameCount, freeOffset);
            it->index += frameCount;
            it->size -= frameCount;
            if (it->size == 0) {
                freeChunks.erase(it);
            }
        }
        animations[name] = {name, frameCount, false, freeOffset};
        return animations[name];
    }

    SpriteAnimationLibrary::SpriteAnimationLibrary() {
        freeChunks.push_back({0, ADAGIO_ALLOCATED_SPRITEANIM_FRAMES});
    }

    void SpriteAnimationLibrary::freeAnimation(AnimationName name) {
        const SpriteAnimation &anim = getAnimation(name);
        std::uint16_t offset = anim.frames - frames;
        freeChunks.push_front({offset, anim.frameLength});
        animations.erase(name);
    }

    void SpriteAnimationLibrary::clear() {
        animations.clear();
        freeChunks.clear();
        freeChunks.push_front({0, ADAGIO_ALLOCATED_SPRITEANIM_FRAMES});
    }
} // Adagio
