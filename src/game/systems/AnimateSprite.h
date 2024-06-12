#ifndef GL_ADAGIO_ANIMATESPRITE_H
#define GL_ADAGIO_ANIMATESPRITE_H

#include "entt/entt.hpp"
#include "../../graphics/SpriteBatch.h"
#include "../../state/GameState.h"

void AnimateSprite(entt::registry &registry, Adagio::GameStats &stats, Adagio::StateMachine *state);

#endif //GL_ADAGIO_ANIMATESPRITE_H
