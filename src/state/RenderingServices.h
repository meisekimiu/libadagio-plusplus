#ifndef GL_ADAGIO_RENDERINGSERVICES_H
#define GL_ADAGIO_RENDERINGSERVICES_H

#include "../animation/SpriteAnimationLibrary.h"
#include "../graphics/AbstractTextureManager.h"
#include "../graphics/SpriteBatch.h"
#include "GameStats.h"

namespace Adagio {
    struct RenderingServices {
        SpriteBatch *spriteBatch;
        AbstractTextureManager *textureManager;
        const GameStats *gameStats;
        SpriteAnimationLibrary *animationLibrary{nullptr};
        AbstractFontManager *fontManager;
    };
} // namespace Adagio

#endif // GL_ADAGIO_RENDERINGSERVICES_H
