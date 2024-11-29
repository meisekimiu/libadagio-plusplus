#include "DerpyFloat.h"
#include "../../components/Position.h"
#include "../components/Derpy.h"
#include "../components/Flash.h"

void DerpyFloat(entt::registry &registry, Adagio::GameServices &services,
                Adagio::StateMachine *state) {
  auto view = registry.view<Muffins::Derpy, Position>();
  const double delta = services.stats->getFrameDelta() * 60;
  if (!registry.view<Muffins::Flash>().empty()) {
    return;
  }
  for (auto [entity, derpy, pos]: view.each()) {
    pos.position.y = derpy.baseY + derpy.floatingFactor * sin(derpy.t);
    derpy.t += delta * derpy.frequency;
  }
}
