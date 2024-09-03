#ifndef GL_ADAGIO_ANIMATESPRITE_H
#define GL_ADAGIO_ANIMATESPRITE_H

#include "../../graphics/SpriteBatch.h"
#include "../../state/GameState.h"
#include "entt/entt.hpp"

void AnimateSprite(entt::registry &registry, Adagio::GameServices &services,
                   Adagio::StateMachine *state);

#endif // GL_ADAGIO_ANIMATESPRITE_H
