#include "ship.h"
#include "../components/Dead.h"
#include "../components/PlayerShip.h"
#include "../components/Position.h"
#include "../components/Sprite.h"
#include "../components/SpriteAnimation.h"
#include "../components/SpriteClip.h"
#include "../components/SpriteScale.h"
#include "../components/UserProjectile.h"
#include "../components/Velocity.h"
#include <iostream>

float lowerVelocity(float v);

Adagio::Vector2d normalizeVelocity(Adagio::Vector2d velocity, float magnitude);

void clampPositionToScreen(Adagio::Vector2d &pos);

void ShipSystem(entt::registry &registry, Adagio::GameServices &services,
                Adagio::StateMachine *state) {
    auto view = registry.view<PlayerShip, Position>();
    const int speed = 2; // TODO: make this a powerup
    for (auto [entity, ship, pos]: view.each()) {
        ship.velocity.x = lowerVelocity(ship.velocity.x);
        ship.velocity.y = lowerVelocity(ship.velocity.y);
        if (IsKeyDown(KEY_LEFT)) {
            ship.velocity.x = -speed;
        }
        if (IsKeyDown(KEY_RIGHT)) {
            ship.velocity.x = speed;
        }
        if (IsKeyDown(KEY_UP)) {
            ship.velocity.y = -speed;
        }
        if (IsKeyDown(KEY_DOWN)) {
            ship.velocity.y = speed;
        }
        if (IsKeyPressed(KEY_SPACE)) {
            const auto wallop = registry.create();
            registry.emplace<UserProjectile>(wallop);
            registry.emplace<Velocity>(wallop, -M_PI_2, 6);
            registry.emplace<Position>(
                    wallop, Adagio::Vector2{pos.position.x + 27 - 16, pos.position.y});
            registry.emplace<Sprite>(wallop, services.resources.textureManager->getTexture("assets/wallop.png"_hs),
                                     Adagio::Vector2d{0, 0}, 0);
            registry.emplace<SpriteClip>(wallop);
            registry.emplace<SpriteScale>(wallop, Adagio::Vector2f{0.5, 0.5});
            SpriteAnimation &anim = registry.emplace<SpriteAnimation>(wallop);
            anim.frameLength = 4;
            anim.loop = true;
            anim.frames = ship.wallopFrames;
        }
        ship.velocity = normalizeVelocity(ship.velocity, speed);
        pos.position.x += ship.velocity.x;
        pos.position.y += ship.velocity.y;
        clampPositionToScreen(pos.position);
    }
}

float lowerVelocity(float v) {
    float velocity = v;
    const float deceleration = 0.09f;
    if (fabsf(velocity) > 0) {
        velocity -= velocity / fabsf(velocity) * deceleration;
        if (fabsf(velocity) <= 0.06) {
            velocity = 0;
        }
    }
    return velocity;
}

Adagio::Vector2d normalizeVelocity(Adagio::Vector2d velocity, float magnitude) {
    float currentMagnitude = sqrtf(powf(velocity.x, 2) + powf(velocity.y, 2));
    if (currentMagnitude <= magnitude || currentMagnitude == 0) {
        return velocity;
    }
    Adagio::Vector2d vel;
    vel.x = velocity.x / currentMagnitude * magnitude;
    vel.y = velocity.y / currentMagnitude * magnitude;
    return vel;
}

void clampPositionToScreen(Adagio::Vector2d &pos) {
    // TODO: use collision boxes instead, nasty hardcoded values
    if (pos.x < 0) {
        pos.x = 0;
    }
    if (pos.x > 640 - 56) {
        pos.x = 640 - 56;
    }
    if (pos.y < 0) {
        pos.y = 0;
    }
    if (pos.y > 480 - 89) {
        pos.y = 480 - 89;
    }
}
