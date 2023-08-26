#include "Wallop.h"
#include "../components/Dead.h"
#include "../components/Position.h"
#include "../components/UserProjectile.h"

void WallopSystem(entt::registry &registry, Adagio::GameStats &stats, Adagio::StateMachine *state) {
    auto view = registry.view<UserProjectile, Position>();
    for (auto [entity, projectile, pos]: view.each()) {
        pos.position.y -= projectile.speed;
        if (pos.position.x < -64 || pos.position.x > 640) {
            registry.emplace<Dead>(entity);
        }
        if (pos.position.y < -56 || pos.position.y > 480) {
            registry.emplace<Dead>(entity);
        }
    }
}
