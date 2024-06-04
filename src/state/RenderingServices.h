#ifndef GL_ADAGIO_RENDERINGSERVICES_H
#define GL_ADAGIO_RENDERINGSERVICES_H

#include "../graphics/SpriteBatch.h"
#include "../graphics/AbstractTextureManager.h"
#include "GameStats.h"

namespace Adagio {
    struct RenderingServices {
        SpriteBatch *spriteBatch;
        AbstractTextureManager *textureManager;
        const GameStats *gameStats;
    };
}

#endif //GL_ADAGIO_RENDERINGSERVICES_H
