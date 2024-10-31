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
#include "../factories/MakeWallop.h"
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
        const Adagio::Vector2f inputMagnitude = services.input->actions.getActionDirection("move"_hs);
        if (inputMagnitude.magnitudeSquared() > 0) {
            ship.velocity.x = inputMagnitude.x * speed;
            ship.velocity.y = inputMagnitude.y * speed;
        }
        if (services.input->actions.hasActionStarted("fire"_hs)) {
            services.audio->play(services.audio->getAudioLibrary().getSample("assets/relax.wav"_hs));
            MakeWallop(
                    Adagio::Vector2{pos.position.x + 27 - 16, pos.position.y},
                    -M_PI_2,
                    registry,
                    services.resources.textureManager
            );
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
