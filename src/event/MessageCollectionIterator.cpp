#include "MessageCollectionIterator.h"

Adagio::MessageCollectionIterator::MessageCollectionIterator(Adagio::Message *message) {
    currentMessage = message;
}

Adagio::MessageCollectionIterator &Adagio::MessageCollectionIterator::operator++() {
    currentMessage = currentMessage->links.next;
    return *this;
}

Adagio::Message &Adagio::MessageCollectionIterator::operator*() {
    return *currentMessage;
}

bool Adagio::MessageCollectionIterator::operator!=(const Adagio::MessageCollectionIterator &other) const {
    return currentMessage != other.currentMessage;
}
