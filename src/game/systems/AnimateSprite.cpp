#include "AnimateSprite.h"
#include "../components/SpriteAnimation.h"
#include "../components/SpriteClip.h"

void AnimateSprite(entt::registry &registry, Adagio::GameServices &services,
                   Adagio::StateMachine *state) {
    auto view = registry.view<SpriteClip, SpriteAnimation>();
    for (auto [entity, clip, animation]: view.each()) {
        try {
            const auto &resource = services.resources.animationLibrary->getAnimation(animation.resourceName);
            const Adagio::FrameIndex &frameLength = resource.frameLength;
            const Adagio::SpriteAnimationFrame *const &frames = resource.frames;
            if (frameLength > 0 && !animation.done) {
                animation.timeOnCurrentFrame += services.stats->getFrameDelta();
                while (animation.timeOnCurrentFrame >
                       frames[animation.currentFrame].duration) {
                    animation.timeOnCurrentFrame -=
                            frames[animation.currentFrame].duration;
                    animation.currentFrame++;
                    if (animation.currentFrame > frameLength - 1) {
                        if (animation.loop) {
                            animation.currentFrame = 0;
                        } else {
                            animation.currentFrame = frameLength - 1;
                            animation.done = true;
                            break;
                        }
                    }
                }
                const Adagio::RectI &frameClip = frames[animation.currentFrame].clip;
                clip.source.position.x = static_cast<float>(frameClip.position.x);
                clip.source.position.y = static_cast<float>(frameClip.position.y);
                clip.source.size.x = static_cast<float>(frameClip.size.x);
                clip.source.size.y = static_cast<float>(frameClip.size.y);
            }
        } catch (...) {
            // TODO: Output debug log about invalid animation name
        }
    }
}
