#ifndef GL_ADAGIO_PLAYERSHIP_H
#define GL_ADAGIO_PLAYERSHIP_H

#include "raylib.h"

struct PlayerShip {
    /*
     * Things we want in PlayerShip:
     *  Direction. Maybe a transform?
     *  Powerup State
     */
    Vector2 velocity;
    Texture2D *wallopTexture; // TODO: no
};

#endif //GL_ADAGIO_PLAYERSHIP_H
