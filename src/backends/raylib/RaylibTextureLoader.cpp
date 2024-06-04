#include "RaylibTextureLoader.h"
#include <utility>

std::pair<RaylibTexture, Adagio::TextureDimensions> RaylibTextureLoader::load(const char *resource) {
    RaylibTexture tex = LoadTexture(resource);
    Adagio::TextureDimensions dims{static_cast<unsigned int>(tex.width), static_cast<unsigned int>(tex.height)};
    return std::make_pair(tex, dims);
}

void RaylibTextureLoader::unload(RaylibTexture texture) {
    UnloadTexture(texture);
}
