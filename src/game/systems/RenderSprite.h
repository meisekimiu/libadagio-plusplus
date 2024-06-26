#ifndef GL_ADAGIO_RENDERSPRITE_H
#define GL_ADAGIO_RENDERSPRITE_H

#include "../../graphics/SpriteBatch.h"
#include "../../state/GameState.h"
#include "entt/entt.hpp"

void RenderSprite(entt::registry &registry, Adagio::SpriteBatch &spriteBatch,
                  Adagio::RenderingServices &services);

#endif // GL_ADAGIO_RENDERSPRITE_H
