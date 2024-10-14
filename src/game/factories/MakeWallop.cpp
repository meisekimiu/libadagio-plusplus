#include "MakeWallop.h"
#include "../../literals/HashString.h"
#include "../components/UserProjectile.h"
#include "../components/Velocity.h"
#include "../components/Position.h"
#include "../components/Sprite.h"
#include "../components/SpriteAnimation.h"
#include "../components/SpriteClip.h"
#include "../components/SpriteScale.h"
#include "../components/events/MessageInbox.h"
#include "../components/CollisionRadius.h"

entt::entity MakeWallop(const Adagio::Vector2d &position, double direction, entt::registry &registry,
                        const Adagio::AbstractTextureManager *textureManager) {
    const auto wallop = registry.create();
    registry.emplace<UserProjectile>(wallop);
    registry.emplace<Velocity>(wallop, direction, 6);
    registry.emplace<Position>(wallop, position);
    registry.emplace<Sprite>(wallop, textureManager->getTexture("assets/wallop.png"_hs),
                             Adagio::Vector2d{0, 0}, 10);
    registry.emplace<SpriteClip>(wallop);
    registry.emplace<SpriteScale>(wallop, Adagio::Vector2f{0.5, 0.5});
    registry.emplace<MessageInbox>(wallop);
    registry.emplace<CollisionRadius>(wallop, Adagio::Vector2d{16, 16}, 5);
    auto &animation = registry.emplace<SpriteAnimation>(wallop, "WALLOP"_hs);
    animation.loop = true;
    return wallop;
}
