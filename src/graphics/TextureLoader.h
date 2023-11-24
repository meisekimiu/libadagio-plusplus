#ifndef GL_ADAGIO_TEXTURELOADER_H
#define GL_ADAGIO_TEXTURELOADER_H

#include "TextureDimensions.h"

namespace Adagio {
    template<typename T>
    struct TextureLoader {
        virtual std::pair<T, TextureDimensions> load(const char *resource) = 0;

        virtual void unload(T texture) = 0;
    };
}

#endif //GL_ADAGIO_TEXTURELOADER_H
