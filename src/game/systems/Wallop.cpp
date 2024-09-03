#include "Wallop.h"
#include "../components/Dead.h"
#include "../components/Position.h"
#include "../components/UserProjectile.h"

void WallopSystem(entt::registry &registry, Adagio::GameServices &services,
                  Adagio::StateMachine *state) {
    auto view = registry.view<UserProjectile, Position>();
    for (auto [entity, pos]: view.each()) {
        if (pos.position.x < -64 || pos.position.x > 640) {
            registry.emplace<Dead>(entity);
        }
        if (pos.position.y < -56 || pos.position.y > 480) {
            registry.emplace<Dead>(entity);
        }
    }
}
