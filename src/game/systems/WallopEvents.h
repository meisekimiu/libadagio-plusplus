#ifndef GL_ADAGIO_WALLOPEVENTS_H
#define GL_ADAGIO_WALLOPEVENTS_H

#include "../../graphics/SpriteBatch.h"
#include "../../state/GameState.h"
#include "entt/entt.hpp"

void WallopEventsSystem(entt::registry &registry, Adagio::GameServices &services,
                        Adagio::StateMachine *state);

#endif //GL_ADAGIO_WALLOPEVENTS_H
