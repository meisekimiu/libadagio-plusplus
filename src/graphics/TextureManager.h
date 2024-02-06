#ifndef GL_ADAGIO_TEXTUREMANAGER_H
#define GL_ADAGIO_TEXTUREMANAGER_H

#include <string>
#include "Texture2D.h"
#include "TextureLoader.h"
#include "../resource/ResourceLibrary.h"

namespace Adagio {
    template<typename T>
    class TextureManager {
    public:
        explicit TextureManager(TextureLoader<T> *loader);

        Texture2D load(std::string resource);

        void unload(Texture2D texture);

        T useTexture(Texture2D texture);

    private:
        ResourceLibrary<T, TextureDimensions, TextureHandle> library;
    };
}

#include "TextureManager-impl.h"

#endif //GL_ADAGIO_TEXTUREMANAGER_H
