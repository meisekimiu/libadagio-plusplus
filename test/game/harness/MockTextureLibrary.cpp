#include "MockTextureLibrary.h"

Adagio::Texture2D MockTextureLibrary::load(std::string resource) {
    return Adagio::Texture2D(0xcafe, 0xcafe, 256, 128);
}

Adagio::Texture2D MockTextureLibrary::getTexture(std::uint32_t resourceName) const {
    return Adagio::Texture2D(0xcafe, 0xcafe, 256, 128);
}

void MockTextureLibrary::unload(Adagio::Texture2D texture) {
    // do nothing
}
