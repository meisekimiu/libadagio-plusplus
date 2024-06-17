#include "ApplyVelocity.h"
#include "../components/Position.h"
#include "../components/Velocity.h"
#include <cmath>

void ApplyVelocity(entt::registry &registry, Adagio::GameStats &stats,
                   Adagio::StateMachine *state) {
    auto view = registry.view<Position, Velocity>();
    for (auto [entity, pos, velocity]: view.each()) {
        // Speed is in "1 pixel per 1/60 of a second"
        const double delta = stats.getFrameDelta() * 60;
        pos.position.x += delta * velocity.speed * std::cos(velocity.direction);
        pos.position.y += delta * velocity.speed * std::sin(velocity.direction);
    }
}
