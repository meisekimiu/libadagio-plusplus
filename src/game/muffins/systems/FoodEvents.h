#ifndef GL_ADAGIO_FOODEVENTS_H
#define GL_ADAGIO_FOODEVENTS_H

#include "../../../state/GameStats.h"
#include "../../../state/StateMachine.h"
#include "entt/entt.hpp"

void FoodEvents(entt::registry &registry, Adagio::GameServices &services,
                Adagio::StateMachine *state);

#endif // GL_ADAGIO_FOODEVENTS_H
