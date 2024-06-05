#include "RenderSprite.h"
#include "../components/Sprite.h"
#include "../components/Position.h"

void
RenderSprite(entt::registry &registry, Adagio::SpriteBatch &spriteBatch, Adagio::RenderingServices &services) {
    auto view = registry.view<Sprite>();
    for (auto [entity, sprite]: view.each()) {
        Adagio::Vector2d position = sprite.position;
        Position *posComponent = registry.try_get<Position>(entity);
        if (posComponent) {
            position += posComponent->position;
        }
        spriteBatch.draw(sprite.texture, position, static_cast<short>(sprite.zIndex));
    }
}
