#ifndef GL_ADAGIO_MESSAGECOLLECTION_H
#define GL_ADAGIO_MESSAGECOLLECTION_H

#include "Message.h"
#include "MessageCollectionIterator.h"

namespace Adagio {
    class MessageCollection {
    public:
        Message *first{nullptr};
        Message *last{nullptr};

        void append(Message *e);

        void remove(size_t index);

        Message *shift();

        void clear();

        [[nodiscard]] bool empty() const;

        [[nodiscard]] size_t size() const;

        [[nodiscard]] Message *at(size_t i) const;

        Message *operator[](size_t i) const;

        [[nodiscard]] MessageCollectionIterator begin() const;

        [[nodiscard]] MessageCollectionIterator end() const;

    private:
        size_t length{0};
    };

} // Adagio

#endif //GL_ADAGIO_MESSAGECOLLECTION_H
