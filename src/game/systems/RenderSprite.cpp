#include "RenderSprite.h"
#include "../components/Sprite.h"
#include "../components/SpriteClip.h"
#include "../components/Position.h"
#include "../components/SpriteScale.h"

static void offsetRenderPosition(entt::registry &registry, entt::entity entity, Adagio::Vector2d &position);
static void applyClipping(entt::registry &registry, entt::entity entity, Adagio::SpriteState *spriteState);
static void applyScaling(entt::registry &registry, entt::entity entity, Adagio::SpriteState *spriteState);

void
RenderSprite(entt::registry &registry, Adagio::SpriteBatch &spriteBatch, Adagio::RenderingServices &services) {
    auto view = registry.view<Sprite>();
    for (auto [entity, sprite]: view.each()) {
        Adagio::Vector2d position = sprite.position;
        offsetRenderPosition(registry, entity, position);

        auto spriteState = spriteBatch.draw(sprite.texture, position, static_cast<short>(sprite.zIndex));

        applyClipping(registry, entity, spriteState);
        applyScaling(registry, entity, spriteState);
    }
}

void applyScaling(entt::registry &registry, entt::entity entity, Adagio::SpriteState *spriteState) {
    SpriteScale *scale = registry.try_get<SpriteScale>(entity);
    if (scale) {
        spriteState->destination.size.x *= scale->scale.x;
        spriteState->destination.size.y *= scale->scale.y;
    }
}

void applyClipping(entt::registry &registry, entt::entity entity, Adagio::SpriteState *spriteState) {
    SpriteClip *clipping = registry.try_get<SpriteClip>(entity);
    if (clipping) {
        spriteState->source = clipping->source;
        spriteState->destination.size = clipping->source.size;
    }
}

void offsetRenderPosition(entt::registry &registry, entt::entity entity, Adagio::Vector2d &position) {
    Position *posComponent = registry.try_get<Position>(entity);
    if (posComponent) {
        position += posComponent->position;
    }
}