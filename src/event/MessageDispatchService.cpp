#include "MessageDispatchService.h"
#include <algorithm>

namespace Adagio {
    Message &MessageDispatchService::dispatch(InboxId to, InboxId from, std::uint32_t eventName) {
        auto inbox = inboxMap.find(to);
        auto it = std::find_if(eventPool, eventPool + MSGPOOL_MAX, [](Message &e) {
            return !e.active;
        });
        if (it == eventPool + MSGPOOL_MAX || inbox == inboxMap.end()) {
            invalidMessage.name = 0xdeadbeef;
            invalidMessage.active = false;
            return invalidMessage;
        }
        it->active = true;
        it->from = from;
        it->to = to;
        it->name = eventName;
        inbox->second->append(it);
        return *it;
    }

    void MessageDispatchService::registerInbox(InboxId id, MessageCollection *inboxDestination) {
        inboxMap[id] = inboxDestination;
    }

    void MessageDispatchService::unregisterInbox(InboxId id) {
        inboxMap.erase(id);
    }
} // namespace Adagio
