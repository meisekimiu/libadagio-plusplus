#include "ShipRendererSystem.h"
#include "../components/PlayerShip.h"
#include "../components/Position.h"
#include "../components/ShipRenderer.h"
#include "../../math/Rect.h"


void
ShipRendererSystem(entt::registry &registry, Adagio::SpriteBatch &spriteBatch, Adagio::RenderingServices &services) {
    const int FRAME_WIDTH = 56;
    const int FRAME_HEIGHT = 89;
    const float secondsUntilNextFrame = 0.083333;
    const Adagio::GameStats &stats = *(services.gameStats);
    auto view = registry.view<ShipRenderer, PlayerShip, Position>();
    for (auto [entity, shipSprite, ship, pos]: view.each()) {
        Adagio::RectF clippingRect{0, 0, FRAME_WIDTH, FRAME_HEIGHT};
        clippingRect.position.x = FRAME_WIDTH * shipSprite.frame;
        auto sprite = spriteBatch.draw(shipSprite.texture, pos.position);
        sprite->source = clippingRect;
        sprite->destination.position.x = floorf(pos.position.x);
        sprite->destination.position.y = floorf(pos.position.y);
        sprite->destination.size.x = FRAME_WIDTH;
        sprite->destination.size.y = FRAME_HEIGHT;
        const float frameDelta = stats.getGameTime() - shipSprite.lastFrame;
        if (frameDelta > secondsUntilNextFrame) {
            shipSprite.lastFrame = stats.getGameTime();
            if (++shipSprite.frame > 3) {
                shipSprite.frame = 0;
            }
        }
    }
}
