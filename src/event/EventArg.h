#ifndef GL_ADAGIO_EVENTVARIANTTYPE_H
#define GL_ADAGIO_EVENTVARIANTTYPE_H

#include "../literals/HashString.h"
#include <cstdint>

namespace Adagio {
    enum Type {
        TYPE_NULL, TYPE_UINT, TYPE_INT, TYPE_FLOAT, TYPE_BOOL, TYPE_HASH
    };

    struct EventArg {
        std::uint32_t eventName{0};

        Type type{TYPE_NULL};

        union {
            std::uint32_t m_Uint{0};
            std::int32_t m_Int;
            float m_Float;
            bool m_Bool;
        };
    };
} // namespace Adagio
#endif // GL_ADAGIO_EVENTVARIANTTYPE_H
