#ifndef GL_ADAGIO_MESSAGEINBOXHOOKS_H
#define GL_ADAGIO_MESSAGEINBOXHOOKS_H

#include <entt/entt.hpp>

void RegisterInboxWithMessageService(entt::registry &registry, entt::entity id);

void UnregisterInboxWithMessageService(entt::registry &registry, entt::entity id);

#endif //GL_ADAGIO_MESSAGEINBOXHOOKS_H
