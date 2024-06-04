#ifndef GL_ADAGIO_PLAYERSHIP_H
#define GL_ADAGIO_PLAYERSHIP_H

#include "raylib.h"

struct PlayerShip {
    /*
     * Things we want in PlayerShip:
     *  Direction. Maybe a transform?
     *  Powerup State
     */
    Adagio::Vector2d velocity;
    Adagio::Texture2D wallopTexture;
};

#endif //GL_ADAGIO_PLAYERSHIP_H
