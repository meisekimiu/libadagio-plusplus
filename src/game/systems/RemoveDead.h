#ifndef GL_ADAGIO_REMOVEDEAD_H
#define GL_ADAGIO_REMOVEDEAD_H

#include "entt/entt.hpp"
#include "../../state/GameStats.h"
#include "../../state/StateMachine.h"

void RemoveDead(entt::registry &registry, Adagio::GameStats &stats, Adagio::StateMachine *state);

#endif //GL_ADAGIO_REMOVEDEAD_H
