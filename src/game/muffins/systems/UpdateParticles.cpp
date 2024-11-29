#include "UpdateParticles.h"
#include "../../components/Dead.h"
#include "../../components/Position.h"
#include "../../components/SpriteRotation.h"
#include "../../components/SpriteTint.h"
#include "../components/Flash.h"
#include "../components/Particle.h"

void UpdateParticles(entt::registry &registry, Adagio::GameServices &services,
                     Adagio::StateMachine *state) {
  auto view = registry.view<Muffins::Particle, SpriteTint, SpriteRotation, Position>();
  const double delta = services.stats->getFrameDelta() * 60;
  if (!registry.view<Muffins::Flash>().empty()) {
    return;
  }
  for (auto [entity, particle, sprTint, sprRot, pos] : view.each()) {
    particle.time += services.stats->getFrameDelta();
    sprRot.rotation += delta * particle.angularVel;
    sprTint.opacity = static_cast<unsigned char>(255.0 * (1.0 - std::pow(std::min(particle.time / particle.lifeTime, 1.0), 2)));
    pos.position.x += delta * particle.xVel;
    pos.position.y += delta * particle.yVel;
    particle.yVel += delta * particle.gravity;
    if (particle.time > particle.lifeTime) {
      registry.emplace<Dead>(entity);
    }
  }
}
