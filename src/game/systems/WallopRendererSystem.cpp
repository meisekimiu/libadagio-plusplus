#include "WallopRendererSystem.h"
#include "../components/Position.h"
#include "../components/WallopRenderer.h"

void WallopRendererSystem(entt::registry &registry, Adagio::SpriteBatch &spriteBatch, const Adagio::GameStats &stats) {
    const int FRAME_WIDTH = 64;
    const int FRAME_HEIGHT = 56;
    const float secondsUntilNextFrame = 0.083333;
    auto view = registry.view<WallopRenderer, Position>();
    for (auto [entity, wallopSprite, pos]: view.each()) {
        Rectangle clippingRect{0, 0, FRAME_WIDTH, FRAME_HEIGHT};
        clippingRect.x = FRAME_WIDTH * wallopSprite.frame;
        auto sprite = spriteBatch.draw(*(wallopSprite.texture), pos.position);
        sprite->source = clippingRect;
        sprite->destination.x = floorf(pos.position.x);
        sprite->destination.y = floorf(pos.position.y);
        sprite->destination.width = FRAME_WIDTH * 0.5;
        sprite->destination.height = FRAME_HEIGHT * 0.5;
        const float frameDelta = stats.getGameTime() - wallopSprite.lastFrame;
        if (frameDelta > secondsUntilNextFrame) {
            wallopSprite.lastFrame = stats.getGameTime();
            if (++wallopSprite.frame > 3) {
                wallopSprite.frame = 0;
            }
        }
    }
}
