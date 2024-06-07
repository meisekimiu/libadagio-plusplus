#ifndef GL_ADAGIO_LOADSPRITE_H
#define GL_ADAGIO_LOADSPRITE_H

#include "../components/Sprite.h"
#include "../../graphics/AbstractTextureManager.h"

Sprite loadSprite(const std::string &resource, Adagio::AbstractTextureManager &textureManager);

#endif //GL_ADAGIO_LOADSPRITE_H
