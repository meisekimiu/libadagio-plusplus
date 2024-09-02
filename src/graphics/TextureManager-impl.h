#ifndef GL_ADAGIO_TEXTUREMANAGER_IMPL_H
#define GL_ADAGIO_TEXTUREMANAGER_IMPL_H
namespace Adagio {
    template<typename T>
    TextureManager<T>::TextureManager(TextureLoader<T> *loader) : library(loader) {}

    template<typename T>
    Texture2D TextureManager<T>::load(std::string resource) {
        auto asset = library.load(resource);
        TextureDimensions metadata = asset.getMetadata();
        return Texture2D(asset.handle, asset.getSecretId(), metadata.width,
                         metadata.height);
        // TODO: Probably use pointers instead for polymorphism
    }

    template<typename T>
    void TextureManager<T>::unload(Adagio::Texture2D texture) {
        library.unload(texture);
    }

    template<typename T>
    T TextureManager<T>::useTexture(Adagio::Texture2D texture) const {
        return library.useResource(texture);
    }

    template<typename T>
    Texture2D TextureManager<T>::getTexture(std::uint32_t textureName) const {
        auto asset = library.getResource(textureName);
        TextureDimensions metadata = asset.getMetadata();
        return Texture2D(asset.handle, asset.getSecretId(), metadata.width,
                         metadata.height);
    }
} // namespace Adagio
#endif // GL_ADAGIO_TEXTUREMANAGER_IMPL_H
