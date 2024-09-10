#ifndef GL_ADAGIO_MAKEWALLOP_H
#define GL_ADAGIO_MAKEWALLOP_H

#include "../../math/Vector2.h"
#include "../../graphics/AbstractTextureManager.h"
#include <entt/entt.hpp>

entt::entity MakeWallop(const Adagio::Vector2d &position, double direction, entt::registry &registry,
                        const Adagio::AbstractTextureManager *textureManager);


#endif //GL_ADAGIO_MAKEWALLOP_H
