#ifndef GL_ADAGIO_WALLOPERRENDERERSYSTEM_H
#define GL_ADAGIO_WALLOPERRENDERERSYSTEM_H

#include "entt/entt.hpp"
#include "../../graphics/SpriteBatch.h"
#include "../../state/GameState.h"

void WallopRendererSystem(entt::registry &registry, Adagio::SpriteBatch &spriteBatch, const Adagio::GameStats &stats);

#endif //GL_ADAGIO_WALLOPERRENDERERSYSTEM_H
