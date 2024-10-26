#ifndef GL_ADAGIO_FONTLOADER_H
#define GL_ADAGIO_FONTLOADER_H

#include "../../resource/AssetLoader.h"
#include "Font.h"

namespace Adagio {
    template<typename T>
    struct FontLoader : public AssetLoader<T, FontMetadata> {
        virtual std::pair<T, FontMetadata> load(const char *resource) = 0;

        virtual void unload(T font) = 0;
    };
}

#endif //GL_ADAGIO_FONTLOADER_H
