#include "AnimateSprite.h"
#include "../components/SpriteAnimation.h"
#include "../components/SpriteClip.h"

void AnimateSprite(entt::registry &registry, Adagio::GameStats &stats,
                   Adagio::StateMachine *state) {
  auto view = registry.view<SpriteClip, SpriteAnimation>();
  for (auto [entity, clip, animation] : view.each()) {
    if (animation.frameLength > 0 && !animation.done) {
      animation.timeOnCurrentFrame += stats.getFrameDelta();
      while (animation.timeOnCurrentFrame >
             animation.frames[animation.currentFrame].duration) {
        animation.timeOnCurrentFrame -=
            animation.frames[animation.currentFrame].duration;
        animation.currentFrame++;
        if (animation.currentFrame > animation.frameLength - 1) {
          if (animation.loop) {
            animation.currentFrame = 0;
          } else {
            animation.currentFrame = animation.frameLength - 1;
            animation.done = true;
            break;
          }
        }
      }
      Adagio::RectI &frameClip = animation.frames[animation.currentFrame].clip;
      clip.source.position.x = static_cast<float>(frameClip.position.x);
      clip.source.position.y = static_cast<float>(frameClip.position.y);
      clip.source.size.x = static_cast<float>(frameClip.size.x);
      clip.source.size.y = static_cast<float>(frameClip.size.y);
    }
  }
}