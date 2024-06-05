#ifndef GL_ADAGIO_SPRITE_H
#define GL_ADAGIO_SPRITE_H

#include "../../graphics/Texture2D.h"
#include "../../graphics/AbstractTextureManager.h"
#include "../../math/Vector2.h"
#include "../../math/Rect.h"

struct Sprite {
    Adagio::Texture2D texture;
    Adagio::Vector2d position;
    int zIndex{0};
};

#endif //GL_ADAGIO_SPRITE_H
