#include "ApplyVelocity.h"
#include "../components/Position.h"
#include "../components/Velocity.h"
#include <cmath>

void ApplyVelocity(entt::registry &registry, Adagio::GameStats &stats,
                   Adagio::StateMachine *state) {
  auto view = registry.view<Position, Velocity>();
  for (auto [entity, pos, velocity] : view.each()) {
    const double delta =
        stats.getFrameDelta() * 60; // Speed is in "1 pixel per 1/60 of a frame"
    pos.position.x += delta * velocity.speed * std::cos(velocity.direction);
    pos.position.y += delta * velocity.speed * std::sin(velocity.direction);
  }
}