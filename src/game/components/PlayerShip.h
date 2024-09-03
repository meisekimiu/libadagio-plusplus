#ifndef GL_ADAGIO_PLAYERSHIP_H
#define GL_ADAGIO_PLAYERSHIP_H

#include "SpriteAnimation.h"

struct PlayerShip {
    /*
     * Things we want in PlayerShip:
     *  Direction. Maybe a transform?
     *  Powerup State
     */
    Adagio::Vector2d velocity;
    AnimationFrame *wallopFrames{nullptr};
};

#endif // GL_ADAGIO_PLAYERSHIP_H
