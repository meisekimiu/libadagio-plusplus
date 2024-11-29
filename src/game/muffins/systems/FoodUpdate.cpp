#include "FoodUpdate.h"
#include "../../components/Position.h"
#include "../components/Flash.h"
#include "../components/Food.h"

void FoodUpdate(entt::registry &registry, Adagio::GameServices &services,
                Adagio::StateMachine *state) {
  auto view = registry.view<Muffins::Food, Position>();
  const double delta = services.stats->getFrameDelta() * 60;
  const int cutoffPos = 667;
  if (!registry.view<Muffins::Flash>().empty()) {
    return;
  }
  for (auto [entity, food, pos]: view.each()) {
    if (pos.position.y >= cutoffPos) {
      services.messageDispatchService->dispatch(entity, entity, "PASS"_hs);
      continue;
    } else {
      pos.position.y += food.speed * delta;
    }
    if (services.input->actions.hasActionStarted("EAT"_hs)) {
      services.messageDispatchService->dispatch(entity, entity, "EAT"_hs);
      continue;
    }
  }
}
