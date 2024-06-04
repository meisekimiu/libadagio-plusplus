#ifndef GL_ADAGIO_SHIPRENDERER_H
#define GL_ADAGIO_SHIPRENDERER_H

#include "raylib.h"

struct ShipRenderer {
    Adagio::Texture2D texture;
    unsigned char frame;
    float lastFrame;
};

#endif //GL_ADAGIO_SHIPRENDERER_H
