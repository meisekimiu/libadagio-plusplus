#ifndef GL_ADAGIO_RENDERSCORE_H
#define GL_ADAGIO_RENDERSCORE_H

#include "../../../graphics/SpriteBatch.h"
#include "../../../state/GameState.h"
#include "entt/entt.hpp"

void RenderScore(entt::registry &registry, Adagio::SpriteBatch &spriteBatch,
                  Adagio::RenderingServices &services);

#endif // GL_ADAGIO_RENDERSCORE_H
