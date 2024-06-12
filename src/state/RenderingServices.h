#ifndef GL_ADAGIO_RENDERINGSERVICES_H
#define GL_ADAGIO_RENDERINGSERVICES_H

#include "../graphics/AbstractTextureManager.h"
#include "../graphics/SpriteBatch.h"
#include "GameStats.h"

namespace Adagio {
struct RenderingServices {
  SpriteBatch *spriteBatch;
  AbstractTextureManager *textureManager;
  const GameStats *gameStats;
};
} // namespace Adagio

#endif // GL_ADAGIO_RENDERINGSERVICES_H
