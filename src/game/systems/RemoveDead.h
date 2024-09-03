#ifndef GL_ADAGIO_REMOVEDEAD_H
#define GL_ADAGIO_REMOVEDEAD_H

#include "../../state/GameStats.h"
#include "../../state/StateMachine.h"
#include "entt/entt.hpp"

void RemoveDead(entt::registry &registry, Adagio::GameServices &services,
                Adagio::StateMachine *state);

#endif // GL_ADAGIO_REMOVEDEAD_H
