#ifndef GL_ADAGIO_WALLOP_H
#define GL_ADAGIO_WALLOP_H

#include "../../graphics/SpriteBatch.h"
#include "../../state/GameState.h"
#include "entt/entt.hpp"

void WallopSystem(entt::registry &registry, Adagio::GameStats &stats,
                  Adagio::StateMachine *state);

#endif // GL_ADAGIO_WALLOP_H
