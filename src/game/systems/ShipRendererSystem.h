#ifndef GL_ADAGIO_SHIPRENDERERSYSTEM_H
#define GL_ADAGIO_SHIPRENDERERSYSTEM_H

#include "entt/entt.hpp"
#include "../../graphics/SpriteBatch.h"
#include "../../state/GameState.h"

void
ShipRendererSystem(entt::registry &registry, Adagio::SpriteBatch &spriteBatch, Adagio::RenderingServices &services);

#endif //GL_ADAGIO_SHIPRENDERERSYSTEM_H
