#include "../../../../event/MessageDispatchService.h"
#include "../MessageInbox.h"
#include "MessageInboxHooks.h"

void RegisterInboxWithMessageService(entt::registry &registry, entt::entity id) {
    Adagio::MessageDispatchService *eventService = registry.ctx().get<Adagio::MessageDispatchService *>();
    if (eventService) {
        MessageInbox &component = registry.get<MessageInbox>(id);
        eventService->registerInbox(id, component);
    }
}

void UnregisterInboxWithMessageService(entt::registry &registry, entt::entity id) {
    Adagio::MessageDispatchService *eventService = registry.ctx().get<Adagio::MessageDispatchService *>();
    if (eventService) {
        eventService->unregisterInbox(id);
    }
}
