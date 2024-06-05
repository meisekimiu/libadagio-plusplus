#include "LoadSprite.h"

Sprite loadSprite(const std::string &resource, Adagio::AbstractTextureManager &textureManager) {
    Sprite s;
    s.texture = textureManager.load(resource);
    s.zIndex = 0;
    s.position = {0, 0};
    return s;
}
