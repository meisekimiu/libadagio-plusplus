#ifndef GL_ADAGIO_MESSAGECOLLECTIONITERATOR_H
#define GL_ADAGIO_MESSAGECOLLECTIONITERATOR_H

#include "Message.h"

namespace Adagio {
    class MessageCollectionIterator {
    public:
        explicit MessageCollectionIterator(Message *message);

        MessageCollectionIterator &operator++();

        Message &operator*();

        bool operator!=(const MessageCollectionIterator &other) const;

    private:
        Message *currentMessage{nullptr};
    };
}

#endif //GL_ADAGIO_MESSAGECOLLECTIONITERATOR_H
