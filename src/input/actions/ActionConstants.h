#ifndef GL_ADAGIO_ACTIONCONSTANTS_H
#define GL_ADAGIO_ACTIONCONSTANTS_H

#include <cstdint>

namespace Adagio::Input {
    typedef std::uint8_t InputType;
    constexpr InputType Keyboard = 0;
    constexpr InputType Mouse = 1;
    constexpr InputType Gamepad = 2;
}

#endif //GL_ADAGIO_ACTIONCONSTANTS_H
