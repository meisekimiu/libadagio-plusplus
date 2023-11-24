#ifndef GL_ADAGIO_TEXTUREMANAGER_H
#define GL_ADAGIO_TEXTUREMANAGER_H

#include <string>
#include <vector>
#include <unordered_map>
#include "TextureLoader.h"
#include "Texture2D.h"

namespace Adagio {
    template<typename T>
    struct TextureWithSecret {
        TextureHandle secret;
        TextureDimensions dimensions;
        T texture;
    };

    template<typename T>
    class TextureManager {
    public:
        explicit TextureManager(TextureLoader<T> *loader);

        Texture2D load(std::string resource);

        void unload(Texture2D texture);

        T useTexture(Texture2D texture);

    private:
        TextureLoader<T> *textureLoader;
        std::vector<TextureWithSecret<T>> textureLibrary;
        std::vector<TextureHandle> freeHandles;
        std::unordered_map<std::string, TextureHandle> loadedFilenames;

        TextureHandle nextSecret;
    };
}

#include "TextureManager-impl.h"

#endif //GL_ADAGIO_TEXTUREMANAGER_H
