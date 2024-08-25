#ifndef GL_ADAGIO_MESSAGEDISPATCHSERVICE_H
#define GL_ADAGIO_MESSAGEDISPATCHSERVICE_H

#include <cstdint>
#include <unordered_map>
#include "Message.h"
#include "MessageCollection.h"

#define MSGPOOL_MAX 32

namespace Adagio {

    typedef std::uint32_t InboxId;

    class MessageDispatchService {
    public:
        void registerInbox(InboxId id, MessageCollection *inboxDestination);

        template<typename T, typename U>
        void registerInbox(T id, U &inboxObject) {
            registerInbox(static_cast<InboxId>(id), &inboxObject.messages);
        }

        template<typename T>
        void registerInbox(T id, MessageCollection *inboxDestination) {
            registerInbox(static_cast<InboxId>(id), inboxDestination);
        }

        void unregisterInbox(InboxId id);

        template<typename T>
        void unregisterInbox(T id) {
            unregisterInbox(static_cast<InboxId>(id));
        }

        Message &dispatch(InboxId to, InboxId from, std::uint32_t eventName);

        template<typename T, typename U>
        Message &dispatch(T to, U from, std::uint32_t eventName) {
            return dispatch(static_cast<InboxId>(to), static_cast<InboxId>(from), eventName);
        }

    private:
        Message eventPool[MSGPOOL_MAX];
        Message invalidMessage;
        std::unordered_map<InboxId, MessageCollection *> inboxMap;
    };

} // namespace Adagio

#endif // GL_ADAGIO_MESSAGEDISPATCHSERVICE_H
