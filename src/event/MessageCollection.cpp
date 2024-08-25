#include "MessageCollection.h"

namespace Adagio {
    size_t MessageCollection::size() const {
        return length;
    }

    void MessageCollection::append(Message *e) {
        e->links.next = nullptr;
        if (first == nullptr) {
            e->links.prev = nullptr;
            first = e;
        } else {
            e->links.prev = last;
            last->links.next = e;
        }
        last = e;
        length++;
    }

    Message *MessageCollection::operator[](size_t i) const {
        return at(i);
    }

    void MessageCollection::remove(size_t index) {
        Message *event = at(index);
        Message *prev = event->links.prev;
        Message *next = event->links.next;
        if (index == 0) {
            first = next;
        }
        if (index == length - 1) {
            last = prev;
        }
        if (prev && next) {
            prev->links.next = next;
            next->links.prev = prev;
        }
        event->nullifyArguments();
        event->active = false;
        event->name = 0;
        event->from = 0;
        event->to = 0;
        length--;
    }

    Message *MessageCollection::at(size_t i) const {
        Message *event = first;
        for (size_t j = 0; j < i; j++) {
            event = event->links.next;
        }
        return event;
    }

    Message *MessageCollection::shift() {
        Message *e = first;
        if (first) {
            remove(0);
        }
        return e;
    }

    bool MessageCollection::empty() const {
        return size() == 0;
    }
} // Adagio
