#ifndef GL_ADAGIO_ABSTRACTFONTMANAGER_H
#define GL_ADAGIO_ABSTRACTFONTMANAGER_H

#include "Font.h"
#include <string>
#include <cstdint>

namespace Adagio {
    struct AbstractFontManager {
        virtual Font load(std::string resource) = 0;

        [[nodiscard]] virtual Font getFont(std::uint32_t resourceName) const = 0;

        virtual void unload(Font texture) = 0;
    };
}

#endif //GL_ADAGIO_ABSTRACTFONTMANAGER_H
