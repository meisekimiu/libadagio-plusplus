#ifndef GL_ADAGIO_TEXTUREMANAGER_IMPL_H
#define GL_ADAGIO_TEXTUREMANAGER_IMPL_H
namespace Adagio {
    template<typename T>
    TextureManager<T>::TextureManager(TextureLoader<T> *loader) {
        textureLoader = loader;
        textureLibrary.reserve(64);
        nextSecret = 1;
    }

    template<typename T>
    Texture2D TextureManager<T>::load(std::string resource) {
        if (loadedFilenames.find(resource) != loadedFilenames.end()) {
            TextureHandle handle = loadedFilenames[resource] - 1;
            auto internalTexture = textureLibrary[handle];
            return Texture2D(handle + 1,
                             internalTexture.secret,
                             internalTexture.dimensions.width,
                             internalTexture.dimensions.height);
        }
        auto internalTexture = textureLoader->load(resource.c_str());
        auto dimensions = internalTexture.second;
        TextureHandle secret = nextSecret++;
        TextureHandle id;
        if (!freeHandles.empty()) {
            id = freeHandles.back();
            freeHandles.pop_back();
            textureLibrary[id - 1] = {secret, dimensions, internalTexture.first};
        } else {
            id = textureLibrary.size() + 1;
            textureLibrary.push_back({secret, dimensions, internalTexture.first});
        }
        loadedFilenames[resource] = id;
        Texture2D handle(id, secret, dimensions.width, dimensions.height);
        return handle;
    }

    template<typename T>
    void TextureManager<T>::unload(Adagio::Texture2D texture) {
        auto internalTexture = textureLibrary[texture.handle - 1];
        internalTexture.secret = 0;
        textureLoader->unload(internalTexture.texture);
        freeHandles.push_back(texture.handle);
        for (auto it = loadedFilenames.begin(); it != loadedFilenames.end(); it++) {
            if (it->second == texture.handle) {
                loadedFilenames.erase(it);
                break;
            }
        }
    }

    template<typename T>
    T TextureManager<T>::useTexture(Adagio::Texture2D texture) {
        auto internalTexture = textureLibrary[texture.handle - 1];
        if (texture.getSecretId() != internalTexture.secret) {
            throw std::invalid_argument("Unloaded texture used.");
        }
        return internalTexture.texture;
    }
}
#endif //GL_ADAGIO_TEXTUREMANAGER_IMPL_H
