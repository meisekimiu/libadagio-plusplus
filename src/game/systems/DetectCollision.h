#ifndef GL_ADAGIO_DETECTCOLLISION_H
#define GL_ADAGIO_DETECTCOLLISION_H

#include "../../event/MessageDispatchService.h"
#include "../../state/GameStats.h"
#include "../../state/StateMachine.h"
#include "../components/CollisionRadius.h"
#include "entt/entt.hpp"

template<class Target, class Filter>
void DetectCollision(entt::registry &registry, Adagio::GameStats &stats,
                     Adagio::StateMachine *state) {
    auto getCollisionCenter = [&registry](const CollisionRadius &collision, entt::entity entity) {
        Adagio::Vector2d collisionCenter = collision.offset;
        Position *pos = registry.try_get<Position>(entity);
        if (pos) {
            collisionCenter += pos->position;
        }
        return collisionCenter;
    };

    auto view = registry.view<CollisionRadius, Target>();
    auto filterView = registry.view<CollisionRadius, Filter>();
    for (auto entity: view) {
        const CollisionRadius &collision = registry.get<CollisionRadius>(entity);
        const Adagio::Vector2d collisionCenter = getCollisionCenter(collision, entity);
        for (auto id: filterView) {
            const CollisionRadius &otherCollision = registry.get<CollisionRadius>(id);
            const Adagio::Vector2d otherCollisionCenter = getCollisionCenter(otherCollision, id) - collisionCenter;
            const double minDistance = collision.radius + otherCollision.radius;
            if (otherCollisionCenter.magnitudeSquared() <= minDistance * minDistance) {
                registry.ctx().get<Adagio::MessageDispatchService *>()->dispatch(entity, id, "COLLISION"_hs);
            }
        }
    }
}

#endif //GL_ADAGIO_DETECTCOLLISION_H
