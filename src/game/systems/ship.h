#ifndef GL_ADAGIO_SHIP_H
#define GL_ADAGIO_SHIP_H

#include "../../state/GameStats.h"
#include "../../state/StateMachine.h"
#include "entt/entt.hpp"

void ShipSystem(entt::registry &registry, Adagio::GameStats &stats,
                Adagio::StateMachine *state);

#endif // GL_ADAGIO_SHIP_H
