#include "WallopEvents.h"
#include "../components/Dead.h"
#include "../components/UserProjectile.h"
#include "../components/events/MessageInbox.h"

void WallopEventsSystem(entt::registry &registry, Adagio::GameServices &services,
                        Adagio::StateMachine *state) {
    auto view = registry.view<UserProjectile, MessageInbox>();
    for (auto [entity, inbox]: view.each()) {
        for (const Adagio::Message &message: inbox.messages) {
            if (message.name == "COLLISION"_hs) {
                registry.emplace<Dead>(entity);
                services.messageDispatchService->dispatch(message.from, entity, "hit"_hs);
            }
        }
        inbox.messages.clear();
    }
}
