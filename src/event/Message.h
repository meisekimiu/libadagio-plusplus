#ifndef GL_ADAGIO_MESSAGE_H
#define GL_ADAGIO_MESSAGE_H

#include "EventArg.h"

#define MAX_EVENT_ARGS 4

namespace Adagio {
    struct Message {
        struct MessageLinks {
            Message *next{nullptr};
            Message *prev{nullptr};
        };
        std::uint32_t name{0};
        std::uint32_t from{0};
        std::uint32_t to{0};
        bool active{false};
        MessageLinks links;

        EventArg argument[MAX_EVENT_ARGS];

        [[nodiscard]] const EventArg *getArg(unsigned char index) const;

        [[nodiscard]] const EventArg *getArgByName(std::uint32_t name) const;

        Message &addBoolArg(std::uint32_t eventName, bool value);

        Message &addUintArg(std::uint32_t eventName, std::uint32_t value);

        Message &addIntArg(std::uint32_t eventName, std::int32_t value);

        Message &addFloatArg(std::uint32_t eventName, float value);

        [[nodiscard]] unsigned char getArgumentCount() const;

        void nullifyArguments();

    private:
        EventArg &getFirstFreeArgument();
    };
} // namespace Adagio

#endif // GL_ADAGIO_MESSAGE_H
