#include "EnemyEvents.h"
#include "../components/Enemy.h"
#include "../components/events/MessageInbox.h"
#include "../components/Dead.h"

void EnemyEventsSystem(entt::registry &registry, Adagio::GameServices &services,
                       Adagio::StateMachine *state) {
    auto view = registry.view<Enemy, MessageInbox>();
    for (auto [entity, enemy, inbox]: view.each()) {
        for (const Adagio::Message &message: inbox.messages) {
            if (message.name == "hit"_hs) {
                enemy.hp--;
                if (enemy.hp < 1) {
                    registry.emplace<Dead>(entity);
                    break;
                }
            }
        }
        inbox.messages.clear();
    }
}
