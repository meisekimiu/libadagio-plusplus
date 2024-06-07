#include "RenderSprite.h"
#include "../components/Sprite.h"
#include "../components/SpriteClip.h"
#include "../components/Position.h"
#include "../components/SpriteScale.h"
#include "../components/SpriteRotation.h"
#include "../components/SpriteTint.h"

static void offsetRenderPosition(entt::registry &registry, entt::entity entity, Adagio::Vector2d &position);
static void applyClipping(entt::registry &registry, entt::entity entity, Adagio::SpriteState *spriteState);
static void applyScaling(entt::registry &registry, entt::entity entity, Adagio::SpriteState *spriteState);
static void applyRotation(entt::registry &registry, entt::entity entity, Adagio::SpriteState *spriteState);
static void applyTint(entt::registry &registry, entt::entity entity, Adagio::SpriteState *spriteState);

void
RenderSprite(entt::registry &registry, Adagio::SpriteBatch &spriteBatch, Adagio::RenderingServices &services) {
    auto view = registry.view<Sprite>();
    for (auto [entity, sprite]: view.each()) {
        Adagio::Vector2d position = sprite.position;
        offsetRenderPosition(registry, entity, position);

        auto spriteState = spriteBatch.draw(sprite.texture, position, static_cast<short>(sprite.zIndex));

        applyClipping(registry, entity, spriteState);
        applyScaling(registry, entity, spriteState);
        applyRotation(registry, entity, spriteState);
        applyTint(registry, entity, spriteState);
    }
}

static void applyTint(entt::registry &registry, entt::entity entity, Adagio::SpriteState *spriteState) {
    SpriteTint *tint = registry.try_get<SpriteTint>(entity);
    if (tint) {
        spriteState->tint = tint->tint;
        spriteState->opacity = tint->opacity;
    }
}

static void applyRotation(entt::registry &registry, entt::entity entity, Adagio::SpriteState *spriteState) {
    // SPEEeeEEeeeEN!
    SpriteRotation *rotation = registry.try_get<SpriteRotation>(entity);
    if (rotation) {
        spriteState->rotation = rotation->rotation;
        spriteState->origin = rotation->origin;
    }
}

static void applyScaling(entt::registry &registry, entt::entity entity, Adagio::SpriteState *spriteState) {
    SpriteScale *scale = registry.try_get<SpriteScale>(entity);
    if (scale) {
        spriteState->destination.size.x *= scale->scale.x;
        spriteState->destination.size.y *= scale->scale.y;
    }
}

static void applyClipping(entt::registry &registry, entt::entity entity, Adagio::SpriteState *spriteState) {
    SpriteClip *clipping = registry.try_get<SpriteClip>(entity);
    if (clipping) {
        spriteState->source = clipping->source;
        spriteState->destination.size = clipping->source.size;
    }
}

static void offsetRenderPosition(entt::registry &registry, entt::entity entity, Adagio::Vector2d &position) {
    Position *posComponent = registry.try_get<Position>(entity);
    if (posComponent) {
        position += posComponent->position;
    }
}