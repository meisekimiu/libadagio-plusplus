#ifndef GL_ADAGIO_FONTMANAGER_IMPL_H
#define GL_ADAGIO_FONTMANAGER_IMPL_H

template<typename T>
FontManager<T>::FontManager(FontLoader<T> *loader) : library(loader) {

}

template<typename T>
Font FontManager<T>::load(std::string path) {
    auto asset = library.load(path);
    return Font(asset.handle, asset.getSecretId());
}

template<typename T>
void FontManager<T>::unload(Font font) {
    library.unload(font);
}

template<typename T>
T FontManager<T>::useFont(Font font) const {
    return library.useResource(font);
}

template<typename T>
Font FontManager<T>::getFont(std::uint32_t name) const {
    auto asset = library.getResource(name);
    return Font(asset.handle, asset.getSecretId());
}

#endif //GL_ADAGIO_FONTMANAGER_IMPL_H
