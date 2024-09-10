#ifndef GL_ADAGIO_ENEMYEVENTS_H
#define GL_ADAGIO_ENEMYEVENTS_H

#include "../../state/GameState.h"
#include "entt/entt.hpp"

void EnemyEventsSystem(entt::registry &registry, Adagio::GameServices &services,
                       Adagio::StateMachine *state);

#endif //GL_ADAGIO_ENEMYEVENTS_H
