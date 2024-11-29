#ifndef GL_ADAGIO_FLASHTIMER_H
#define GL_ADAGIO_FLASHTIMER_H

#include "../../../state/GameStats.h"
#include "../../../state/StateMachine.h"
#include "entt/entt.hpp"

void FlashTimer(entt::registry &registry, Adagio::GameServices &services,
                Adagio::StateMachine *state);

#endif // GL_ADAGIO_FLASHTIMER_H
