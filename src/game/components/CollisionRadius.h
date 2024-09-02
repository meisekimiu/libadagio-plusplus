#ifndef GL_ADAGIO_COLLISIONRADIUS_H
#define GL_ADAGIO_COLLISIONRADIUS_H

#include "../../math/Vector2.h"

struct CollisionRadius {
    Adagio::Vector2d offset{0, 0};
    double radius{0};
};

#endif //GL_ADAGIO_COLLISIONRADIUS_H
