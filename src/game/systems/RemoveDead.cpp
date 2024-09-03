#include "RemoveDead.h"
#include "../components/Dead.h"

void RemoveDead(entt::registry &registry, Adagio::GameServices &services,
                Adagio::StateMachine *state) {
    const auto view = registry.view<Dead>();
    registry.destroy(view.begin(), view.end());
    // BRING OUT YOUR DEAD! https://www.youtube.com/watch?v=zEmfsmasjVA
}
