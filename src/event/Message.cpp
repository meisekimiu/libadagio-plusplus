#include "Message.h"
#include <stdexcept>
#include <algorithm>

const Adagio::EventArg *Adagio::Message::getArg(unsigned char index) const { return &argument[index]; }

Adagio::Message &Adagio::Message::addBoolArg(std::uint32_t eventName, bool value) {
    EventArg &arg = getFirstFreeArgument();
    arg.eventName = eventName;
    arg.type = Adagio::TYPE_BOOL;
    arg.m_Bool = value;
    return *this;
}

Adagio::Message &Adagio::Message::addUintArg(std::uint32_t eventName, std::uint32_t value) {
    EventArg &arg = getFirstFreeArgument();
    arg.eventName = eventName;
    arg.type = Adagio::TYPE_UINT;
    arg.m_Uint = value;
    return *this;
}

Adagio::Message &Adagio::Message::addIntArg(std::uint32_t eventName, std::int32_t value) {
    EventArg &arg = getFirstFreeArgument();
    arg.eventName = eventName;
    arg.type = Adagio::TYPE_INT;
    arg.m_Int = value;
    return *this;
}

Adagio::Message &Adagio::Message::addFloatArg(std::uint32_t eventName, float value) {
    EventArg &arg = getFirstFreeArgument();
    arg.eventName = eventName;
    arg.type = Adagio::TYPE_FLOAT;
    arg.m_Float = value;
    return *this;
}

unsigned char Adagio::Message::getArgumentCount() const {
    for (unsigned char i = 0; i < MAX_EVENT_ARGS; i++) {
        if (argument[i].type == Adagio::TYPE_NULL) {
            return i;
        }
    }
    return MAX_EVENT_ARGS;
}

void Adagio::Message::nullifyArguments() {
    for (auto &a: argument) {
        a.eventName = 0;
        a.type = Adagio::TYPE_NULL;
        a.m_Uint = 0;
    }
}

Adagio::EventArg &Adagio::Message::getFirstFreeArgument() {
    unsigned char count = getArgumentCount();
    if (count >= MAX_EVENT_ARGS) {
        throw std::range_error("Too many arguments on event");
    }
    return argument[count];
}

const Adagio::EventArg *Adagio::Message::getArgByName(std::uint32_t argName) const {
    auto i = std::find_if(argument, argument + MAX_EVENT_ARGS, [argName](const Adagio::EventArg &arg) {
        return arg.eventName == argName;
    });
    if (i != argument + MAX_EVENT_ARGS) {
        return i;
    }
    return nullptr;
}
